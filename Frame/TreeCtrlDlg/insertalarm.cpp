#include "insertalarm.h"
#include "ui_insertalarm.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
InsertAlarm::InsertAlarm(stAlarm alarm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertAlarm)
{
    ui->setupUi(this);
	setWindowTitle(tr("报警设定"));
    //

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    QDoubleValidator * doubleValidator = new QDoubleValidator(this);

    ui->edit_low->setValidator(doubleValidator);
    ui->edit_high->setValidator(doubleValidator);


	QString stotal="";
	int nTmp=0;
	QString sTmp="";
	int totalSceneNum = pwnd->pSceneSheet.size();
	for(int i=0;i<totalSceneNum;i++)
	{
		if(pwnd->newScreen[i]->parent()==pwnd->TreeKeyboard||pwnd->newScreen[i]->parent() == pwnd->copyUserKeyboard)
			continue;
		stotal=pwnd->newScreen[i]->text(0).split(":").at(0);

		nTmp=stotal.toInt();
		sTmp=pwnd->newScreen[i]->text(0).split(":").at(1);

		ui->combo_screen->addItem(sTmp);
	}

    QVector<QString>language_vector;
    languageCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();

    for(int i=0; i<languageCount; i++)
    {
        language_vector.push_back(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }
    for(int i=0; i<languageCount; i++)
    {
        ui->combo_language->addItem(language_vector.at(i));
    }
    m_alarm = alarm;

    ui->listWidget->setInputMethodHints(Qt::ImhPreferNumbers);
	initUi();
    while(m_alarm.messages.size()<languageCount)
    {
        m_alarm.messages << "alarm message";
    }
	connect(ui->check_screen,SIGNAL(clicked(bool)),this,SLOT(on_openSceneClicked(bool)));
    connect(ui->combo_language,SIGNAL(currentIndexChanged(int)),this,SLOT(on_language_changed(int)));

}

InsertAlarm::~InsertAlarm()
{
    delete ui;
}


void InsertAlarm::initUi()
{
	int index = m_alarm.dataType -1;
	ui->combo_datatype->setCurrentIndex(index);
	switch (m_alarm.eCondtion)
	{
	case ALARM_ON:
		ui->combo_Condtion->setCurrentIndex(0);
		on_combo_Condtion_currentIndexChanged(0);
		break;
	case ALARM_OFF:
		ui->combo_Condtion->setCurrentIndex(1);
		on_combo_Condtion_currentIndexChanged(1);
		break;
	case ALARM_VALUE:
		ui->combo_Condtion->setCurrentIndex(0);
		on_combo_Condtion_currentIndexChanged(0);
        ui->edit_low->setText(QString::number(m_alarm.rangeLow,'g',10));
		break;
	case ALARM_RANGE:
		ui->combo_Condtion->setCurrentIndex(1);
		on_combo_Condtion_currentIndexChanged(1);
        ui->edit_low->setText(QString::number(m_alarm.rangeLow,'g',10));
        ui->edit_high->setText(QString::number(m_alarm.rangeHigh,'g',10));
		break;
	case ALARM_RANGE_OUT:
		ui->combo_Condtion->setCurrentIndex(2);
		on_combo_Condtion_currentIndexChanged(2);
        ui->edit_low->setText(QString::number(m_alarm.rangeLow,'g',10));
        ui->edit_high->setText(QString::number(m_alarm.rangeHigh,'g',10));
		break;

	}
	ui->edit_msg->setText(m_alarm.messages.first());
    ui->edit_addr->setText(m_alarm.addr.sShowAddr);
	ui->check_screen->setChecked(m_alarm.bOpenScene);
	if (m_alarm.bOpenScene)
	{
		index = ui->combo_screen->findText(m_alarm.sceneName);
		if (index >= 0)
		{
			ui->combo_screen->setCurrentIndex(index);
		}
	}
	else{
                ui->combo_screen->setEnabled(false);
	}

    ui->groupBox_4->setChecked(m_alarm.bSeneMsg);
    if (m_alarm.bSeneMsg)
    {
        ui->listWidget->clear();
        foreach(QString sPhone,m_alarm.sPhoneNums)
        {
            if(!sPhone.isEmpty())
            {
                ui->listWidget->addItem(sPhone);
            }
        }
    }
    else{
        //ui->label_9->setEnabled(false);
        //ui->edit_dest->setEnabled(false);
    }
    ui->check_add->setChecked(m_alarm.bAddtoDB);

    ui->check_print->setChecked(m_alarm.bPrint);
    ui->check_date->setChecked(m_alarm.bPrintDate);
    ui->check_Time->setChecked(m_alarm.bPrintTime);
    on_check_print_clicked(m_alarm.bPrint);
    this->on_groupBox_4_clicked(m_alarm.bSeneMsg);


}

void InsertAlarm::on_btn_addr_clicked()
{
    Keyboard addr;

    int addrType = 1;
    if(ui->combo_datatype->currentIndex() == 0)
    {
        addrType = 0;
    }
    QString addrStr = ui->edit_addr->text();
    AddressInputDialog addressintputdlg_writeaddress(addr,addrStr,addrType,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->edit_addr->setText(addr.sShowAddr);
    }
}
//获得一个连续地址的报警项
QList<stAlarm > InsertAlarm::getAlarms()
{
    QList<stAlarm >alarms;
    QVector<Keyboard> addrs;

    stAlarm cAlarm = m_alarm;
    if(ui->spin_length->value() == 1)
    {
        alarms << cAlarm;
        return alarms;
    }

    addrs = getAddrs();
    int startIndex = m_alarm.index;


    for(int i=0; i<addrs.size(); i++)
    {
        cAlarm.index = i+startIndex;
        cAlarm.addr = addrs.at(i);
        alarms << cAlarm;
    }
    return alarms;
}

QVector <Keyboard> InsertAlarm::getAddrs()
{
    Keyboard kb = m_alarm.addr;
    QVector <Keyboard> Vaddrs;
    Vaddrs << kb;

    int count = ui->spin_length->value();
    int nIntervl = 1;

    switch(m_alarm.dataType)
    {
    case POSITIVE_INT_32:
    case INT_32:
    case BCD_32:
    case FLOAT_32:
        nIntervl = 2;
        break;
    }

    QVector<ADDR_CHECK_SOURCE_PROP> multiAddrs = kb.getMultiAddrs(nIntervl,count-1);
    foreach(ADDR_CHECK_SOURCE_PROP addrPro,multiAddrs)
    {
        kb.sPlcAddrValue = QString::fromStdString(addrPro.sAddrValue);
        kb.refreshShowAddr();
        Vaddrs<< kb;
    }
    return Vaddrs;
}

void InsertAlarm::on_combo_datatype_currentIndexChanged(int index)
{
    double dMax;
    double dMin;
    ui->combo_Condtion->clear();

    QStringList items;
    if(index == 0)
    {
        items << tr("位ON报警") << tr("位OFF报警");
    }
    else
    {
        items << tr("固定值报警") << tr("范围内报警")<< tr("超出范围报警");
    }
    ui->combo_Condtion->addItems(items);
    switch(index)
    {
    case 1://16位整数
        {
            DoubleValidator *validator = new DoubleValidator(-32768,32767,5,this);
            ui->edit_low->setValidator(validator);
            ui->edit_high->setValidator(validator);
        }
        break;
    case 2://32位整数
        {
            dMax=2147483647L;
            long temp = -2147483648;
            dMin=temp;
            DoubleValidator *validator = new DoubleValidator(dMin,dMax,5,this);
            ui->edit_low->setValidator(validator);
            ui->edit_high->setValidator(validator);
        }
        break;
    case 3://16位正整数
        {
            DoubleValidator *validator = new DoubleValidator(0,65535,5,this);
            ui->edit_low->setValidator(validator);
            ui->edit_high->setValidator(validator);
        }
        break;
    case 4://32位正整数
        {
            dMax=4294967295L;
            dMin=0;
            DoubleValidator *validator = new DoubleValidator(dMin,dMax,5,this);
            ui->edit_low->setValidator(validator);
            ui->edit_high->setValidator(validator);
        }
        break;
    case 5://16位BCD码
        {
            DoubleValidator *validator = new DoubleValidator(0,9999,4,this);
            ui->edit_low->setValidator(validator);
            ui->edit_high->setValidator(validator);
        }
        break;
    case 6://32位BCD码
        {
            DoubleValidator *validator = new DoubleValidator(0,99999999,8,this);
            ui->edit_low->setValidator(validator);
            ui->edit_high->setValidator(validator);
        }
        break;
    case 7://32位浮点数
        {
            dMax=2147483647L;
            long temp = -2147483648;
            dMin=temp;
            DoubleValidator *validator = new DoubleValidator(dMin,dMax,5,this);
            ui->edit_low->setValidator(validator);
            ui->edit_high->setValidator(validator);
        }
        break;
    }
}

void InsertAlarm::on_combo_Condtion_currentIndexChanged(int index)
{

    if(ui->combo_datatype->currentIndex() == 0)
    {
        if(index == 0)
        {
            m_type = ALARM_ON;
        }
        else
            m_type = ALARM_OFF;

    }
    else
    {
        if(index == 0)
        {
            m_type = ALARM_VALUE;
        }
        else if(index == 1)
        {
            m_type = ALARM_RANGE;
        }
        else
        {
            m_type = ALARM_RANGE_OUT;
        }

    }
    switch(m_type)
    {
    case ALARM_ON:
    case ALARM_OFF:
        ui->label_5->setEnabled(false);
        ui->edit_low->setEnabled(false);
        ui->label_7->setEnabled(false);
        ui->edit_high->setEnabled(false);
        break;
    case ALARM_VALUE:
        ui->label_5->setEnabled(true);
        ui->label_5->setText(tr("报警值"));
        ui->edit_low->setEnabled(true);
        ui->label_7->setEnabled(false);
        ui->edit_high->setEnabled(false);
        break;
    case ALARM_RANGE:
    case ALARM_RANGE_OUT:
        ui->label_5->setEnabled(true);
        ui->label_5->setText(tr("下限值"));
        ui->edit_low->setEnabled(true);
        ui->label_7->setEnabled(true);
        ui->edit_high->setEnabled(true);
        break;
    }
}

void InsertAlarm::on_btn_ok_clicked()
{
    QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr(""),0,this,
                    Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.addButton(tr("确定"),QMessageBox::AcceptRole);


    QString sAddr = ui->edit_addr->text();
    int type = 1;
    if(ui->combo_datatype->currentIndex() == 0)
       type = 0;

    Keyboard addr;
    if(!pwnd->IsAddressCheckRight(addr,tr("报警地址"),ui->edit_addr,type))
    {
        return;
    }

    if( m_type == ALARM_VALUE  )
    {
        if(ui->edit_low->text().isEmpty())
        {
            box.setText(tr("报警值不能为空"));
            box.exec();
            return;
        }
        m_alarm.rangeLow = ui->edit_low->text().toDouble();
    }
    if(m_type == ALARM_RANGE || m_type == ALARM_RANGE_OUT)
    {
        if(ui->edit_low->text().isEmpty())
        {
            box.setText(tr("报警范围：下限值不能为空"));
            box.exec();
            return;
        }
        if(ui->edit_high->text().isEmpty())
        {
            box.setText(tr("报警范围：上限值不能为空"));
            box.exec();
            return;
        }

        m_alarm.rangeLow = ui->edit_low->text().toDouble();
        m_alarm.rangeHigh = ui->edit_high->text().toDouble();
    }

    m_alarm.sPhoneNums.clear();
    if(ui->groupBox_4->isChecked())
    {
        for(int i=0; i<ui->listWidget->count(); i++)
        {
            QListWidgetItem *item = ui->listWidget->item(i);
            if(item && isDigitString(item->text()))
            {
                m_alarm.sPhoneNums << item->text();
            }
            else
            {
                box.setText(tr("发送短信：号码有误"));
                box.exec();
                return;
            }
        }
    }


    switch(ui->combo_datatype->currentIndex())
    {
    case 2:
    case 4:
    case 7:
    case 6:
        addr.Length = 2;
        break;
    default:
        addr.Length = 1;
    }

    m_alarm.addr = addr;
    m_alarm.eCondtion = m_type;
    m_alarm.dataType = (DATA_TYPE)(ui->combo_datatype->currentIndex()+1);
	m_alarm.bOpenScene = ui->check_screen->isChecked();
	if (m_alarm.bOpenScene)
	{
		m_alarm.sceneName = ui->combo_screen->currentText();
	}
    m_alarm.bSeneMsg = ui->groupBox_4->isChecked();
    if (!m_alarm.bSeneMsg)
    {
        m_alarm.sPhoneNums.clear();
    }
    m_alarm.bAddtoDB = ui->check_add->isChecked();

    m_alarm.bPrint = ui->check_print->isChecked();
    m_alarm.bPrintDate = ui->check_date->isChecked();
    m_alarm.bPrintTime = ui->check_Time->isChecked();
    accept();
}

void InsertAlarm::on_btn_cancel_clicked()
{
    reject();
}
void InsertAlarm::on_language_changed(int index)
{
    if(m_alarm.messages.size()>index)
    {
        ui->edit_msg->setText(m_alarm.messages[index]);
    }
}
void InsertAlarm::on_edit_msg_editingFinished()
{
    int index = ui->combo_language->currentIndex();
    if(m_alarm.messages.size()>index)
    {
        m_alarm.messages.replace(index,ui->edit_msg->text());
    }
}
void InsertAlarm::on_openSceneClicked(bool checked)
{
        ui->combo_screen->setEnabled(checked);
}

void InsertAlarm::on_check_sms_clicked(bool checked)
{
    //ui->edit_dest->setEnabled(checked);
    //ui->label_9->setEnabled(checked);
}

void InsertAlarm::on_check_print_clicked(bool checked)
{
    ui->check_date->setVisible(checked);
    ui->check_Time->setVisible(checked);
}

void InsertAlarm::on_btn_add_clicked()
{
    QListWidgetItem *item = new QListWidgetItem(tr("电话号码"));
    ui->listWidget->addItem(item);
    Qt::ItemFlags flags = item->flags();
    item->setFlags(flags|Qt::ItemIsEditable);


}

void InsertAlarm::on_btn_del_clicked()
{
    int row = ui->listWidget->currentRow();
    if(row >= 0)
    {
        ui->listWidget->takeItem(row);
    }
}

void InsertAlarm::on_groupBox_4_clicked(bool checked)
{
    QRectF rc = ui->groupBox_4->geometry();
    QRectF rcBtnOk = ui->btn_ok->geometry();
    QRectF rcBtnCancel = ui->btn_cancel->geometry();
    //QPoint pos= ui->groupBox_4->parentWidget()->mapToGlobal(rc.topLeft().toPoint());
    ui->btn_add->setVisible(checked);
    ui->btn_del->setVisible(checked);
    ui->listWidget->setVisible(checked);
    ui->label_9->setVisible(checked);

    if(checked)
    {
        ui->groupBox_4->setGeometry(rc.x(),rc.y(),rc.width(),121);
    }
    else
    {
        ui->groupBox_4->setGeometry(rc.x(),rc.y(),rc.width(),20);
    }
    rc = ui->groupBox_4->geometry();
    ui->btn_ok->setGeometry(rcBtnOk.x(),rc.bottom()+10,rcBtnOk.width()
                            ,rcBtnOk.height());
    ui->btn_cancel->setGeometry(rcBtnCancel.x(),rc.bottom()+10
                                ,rcBtnCancel.width(),rcBtnCancel.height());
    QSize rcWnd = size();
    if(checked)
    {
        rcWnd.setHeight(438);
        //qDebug() <<"rcWnd.height() " <<rcWnd.height();
    }
    else
    {
        rcWnd.setHeight(338);
        //qDebug() <<"rcWnd.height() " <<rcWnd.height();
    }

    setFixedSize(rcWnd);
    //qDebug() << size();

}
bool InsertAlarm::isDigitString(const QString& src)
{
    const char *s = src.toUtf8().data();

    while(*s && *s>='0' && *s<='9')s++;

    return !bool(*s);
}
