#include "alarmdlg.h"
#include "ui_alarmdlg.h"
//#include <QPlainTextEdit>
#include <QKeyEvent>
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

#define MAX_ALARM_SIZE 512
AddWidget::AddWidget(int width, int height,bool type, QWidget* parent) : QWidget(parent)
{
    pEdit  = new QLineEdit(this);
    pBtn   = new QPushButton(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    addType = type;
    pEdit->resize(width * 4 / 5, height);
    pBtn->move(width * 4 / 5, 0);
    pBtn->setFlat(true);
    pBtn->setIcon(QIcon(":/standardtool/images/address.bmp"));
    pBtn->resize(width / 5 -1, height-1);


    connect(pBtn, SIGNAL(clicked()), this, SLOT(btnAddr()));
}

AddWidget::~AddWidget()
{
    delete pEdit;
    delete pBtn;
}

void AddWidget::btnAddr()
{
    QString addrStr = pEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(addr,addrStr,addType,this);
    if(addressintputdlg_writeaddress.exec())
    {
        pEdit->setText(addr.sShowAddr);
    }

}

void AddWidget::setEditFocus(QString text)
{
    pEdit->setText(text);
    pEdit->selectAll();
    pEdit->setFocus();
}

QString AddWidget::getString()
{
    QString str;
    if(pEdit)
    {
        str = pEdit->text();
    }
    return str;
}
bool AddWidget::check(bool type)
{
    QString msg;
    if(type)
    {
        msg = tr("�ֵ�ַ");
    }
    else
    {
        msg = tr("λ��ַ");
    }

    if(pEdit)
    {
        if(pEdit->text().isEmpty())
        {
            return true;
        }
        else
        {
           return pwnd->IsAddressCheckRight(addr,msg,pEdit,type);
        }
    }
    else
        return false;
}
CondWidget::CondWidget(int width, int height, QWidget* parent) : QWidget(parent)
{

    pEdit  = new QLineEdit(this);
    pLabel   = new QLabel(this);
    pCombox = new QComboBox(this);

    pEdit->setText("0");
    pLabel->setText("X");
    QStringList values;
    values <<tr("=") <<tr(">") <<tr(">=") <<tr("<") <<tr("<=");
    pCombox->addItems(values);
    pCombox->setCurrentIndex(0);

    pLabel->resize(width * 1 / 3, height);
    pCombox->resize(width * 1 / 3, height);
    pCombox->move(width * 1 / 3, 0);
    pEdit->resize(width * 1 / 3, height);
    pEdit->move(width * 2 / 3, 0);
    QDoubleValidator * validator = new QDoubleValidator(this);
    pEdit->setValidator(validator);

}

CondWidget::~CondWidget()
{
    delete pEdit;
    delete pLabel;
    delete pCombox;
}
void CondWidget::SetValues(QString sAddr,QString sRel,QString sValue)
{
    pEdit->setText(sValue);
    pLabel->setText(sAddr);
    int index = pCombox->findText(sRel);
    if(index != -1)
    {
        pCombox->setCurrentIndex(index);
    }
}
QString CondWidget::getString()
{
    QString str;
    str += pLabel->text();
    str += " ";
    str += pCombox->currentText();
    str += " ";
    str += pEdit->text();

    str += tr(" ����");
    return str;
}

AlarmDlg::AlarmDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlarmDlg)
{
    ui->setupUi(this);

    bInit = false;
    bDisableSlot = false;

    languageCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    alarmGrp.alarmName = tr("������¼1");
    QSize sz = size();
    setFixedSize(sz);//��ֹ�ϷŴ��ڴ�С

    setWindowTitle(tr("������¼"));
    RadioGroup =new QButtonGroup(this);
    RadioGroup->addButton(ui->radio_bit,0);
    RadioGroup->addButton(ui->radio_word,1);
    ui->radio_bit->setChecked(true);
	ui->label_2->setVisible(false);
	ui->combo_datatype->setVisible(false);

    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setColumnWidth(0, ui->table->sizeHint().width()*1/6);
    ui->table->setColumnWidth(1, ui->table->sizeHint().width()*1/2);
    ui->table->setColumnWidth(2, ui->table->sizeHint().width());
    ui->table->setColumnWidth(3, ui->table->sizeHint().width()*4/3);


    ui->table->setRowCount(MAX_ALARM_SIZE);

    for(int i = 0; i < MAX_ALARM_SIZE; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(i));
        ui->table->setItem(i, 0, item);
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

    connect(RadioGroup,SIGNAL(buttonClicked(int)),SLOT(radioChanged(int)));
    ui->btn_help->installEventFilter(this);
    ui->btn_ok->installEventFilter(this);
    ui->edit_name->installEventFilter(this);
    ui->combo_datatype->installEventFilter(this);
    ui->combo_language->installEventFilter(this);
    //ui->radio_bit->installEventFilter(this);
    //ui->radio_word->installEventFilter(this);
}

AlarmDlg::~AlarmDlg()
{
    delete ui;
}
//˫�� ��ʼ������
void AlarmDlg::on_table_cellDoubleClicked(int row, int column)
{
    if(RadioGroup->checkedId() == 0)
    {
        CellDClick_Bit(row,column);
    }
    else
    {
        CellDClick_Word(row,column);
    }
}

//����ѡ�� �Ƴ���ַ��ť�� �������ݵ�tableitem
void AlarmDlg::on_table_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if(bDisableSlot)
        return;
    if(RadioGroup->checkedId() == 0)
    {
        CellChanged_Bit(currentRow, currentColumn, previousRow, previousColumn);
    }
    else
    {
        CellChanged_Word(currentRow, currentColumn, previousRow, previousColumn);
    }

    QTableWidgetItem *item = ui->table->item(previousRow,1);
    if(item && !item->text().isEmpty())
        EditAlarm(previousRow);
}

//���ĵ�ַ����
void AlarmDlg::radioChanged(int index)
{
    QStringList headers;
    alarms.clear();
    bDisableSlot = true;
    ui->table->clear();

	ui->label_2->setVisible(index);
	ui->combo_datatype->setVisible(index);
    if(index)
    {
        headers <<tr("���") <<tr("�ֵ�ַ") <<tr("��������") <<tr("��Ϣ") ;
		
    }
    else
    {
        headers <<tr("���") <<tr("λ��ַ") <<tr("��������") <<tr("��Ϣ") ;
    }
    ui->table->setHorizontalHeaderLabels(headers);
    ui->table->setRowCount(MAX_ALARM_SIZE);

    for(int i = 0; i < MAX_ALARM_SIZE; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(i));
        ui->table->setItem(i, 0, item);
    }
    bDisableSlot = false;
}

//ѡ��λ��ַ������¼��ʱ�� ��˫��item�Ĵ���
//��ʼ������
void AlarmDlg::CellDClick_Bit(int row, int column)
{
    QString txt;
    QTableWidgetItem *item = ui->table->item(row,column);

    if(item)
    {
        txt = item->text();
    }

    int  width      = ui->table->columnWidth(column);
    int  height     = ui->table->rowHeight(row);

    if(column == 1)//˫��ѡ���ַ��
    {
        AddWidget *wgt = new AddWidget(width,height,0,this);
        ui->table->setCellWidget(row,column,wgt);

        if(txt.isEmpty()){
            txt = "LB0";
            QTableWidgetItem *newitem = new QTableWidgetItem(tr("λON����"));
            ui->table->setItem(row,2,newitem);
            newitem = new QTableWidgetItem("Alarm Message");
            ui->table->setItem(row,3,newitem);
            addAlarm(row);
        }
        wgt->setEditFocus(txt);
    }
    else if(column == 2)//˫��ѡ�񱨾�������
    {
        QComboBox *combox = new QComboBox(this);
        combox->setBaseSize(width,height);
        QStringList values;
        values <<tr("λON����") <<tr("λOFF����") ;
        combox->addItems(values);
        combox->setCurrentIndex(0);

        int index = combox->findText(txt);
        if(index != -1)
        {
            combox->setCurrentIndex(index);
        }
        ui->table->setCellWidget(row,column,combox);

        if(txt.isEmpty()){
            QTableWidgetItem *newitem = new QTableWidgetItem("LB0");
            ui->table->setItem(row,1,newitem);
            newitem = new QTableWidgetItem("Alarm Message");
            ui->table->setItem(row,3,newitem);
            addAlarm(row);
        }

    }
    else if(column == 3)//˫��ѡ�񱨾���Ϣ��
    {
        QTableWidgetItem *addrItem = ui->table->item(row,1);
        if(addrItem && !addrItem->text().isEmpty())
        {
            if(txt.isEmpty())
            {
                //txt = "Alarm Message";
            }
            QLineEdit *edit = new QLineEdit(txt,this);

            ui->table->setCellWidget(row,column,edit);

            edit->setFixedSize(width,height);

            edit->selectAll();
            edit->setFocus();
        }

    }
}

//ѡ���ֵ�ַ������¼��ʱ�� ��˫��item�Ĵ���
//��ʼ������
void AlarmDlg::CellDClick_Word(int row, int column)
{
    QString txt;
    QTableWidgetItem *item = ui->table->item(row,column);

    if(item)
    {
        txt = item->text();
    }

    int  width      = ui->table->columnWidth(column);
    int  height     = ui->table->rowHeight(row);

    if(column == 1)//˫��ѡ���ַ��
    {
        AddWidget *wgt = new AddWidget(width,height,1,this);
        ui->table->setCellWidget(row,column,wgt);

        if(txt.isEmpty()){
            txt = "LW0";
            QTableWidgetItem *newitem = new QTableWidgetItem(tr("X = 0 ����"));
            ui->table->setItem(row,2,newitem);
            newitem = new QTableWidgetItem("Alarm Message");
            ui->table->setItem(row,3,newitem);
            addAlarm(row);
        }
        wgt->setEditFocus(txt);
    }
    else if(column == 2)//˫��ѡ�񱨾�������
    {
        CondWidget *wgt = new CondWidget(width,height,this);

        QStringList lst = txt.split(" ");
        if(lst.size() == 3)
        {
            wgt->SetValues(lst[0],lst[1],lst[2]);
        }

        if(item)
            item->setText("");
        ui->table->setCellWidget(row,column,wgt);

        if(txt.isEmpty()){
            QTableWidgetItem *newitem = new QTableWidgetItem("LW0");
            ui->table->setItem(row,1,newitem);
            newitem = new QTableWidgetItem("Alarm Message");
            ui->table->setItem(row,3,newitem);
            addAlarm(row);
        }

    }
    else if(column == 3)//˫��ѡ�񱨾���Ϣ��
    {
        QTableWidgetItem *addrItem = ui->table->item(row,1);
        if(addrItem && !addrItem->text().isEmpty())
        {
            if(txt.isEmpty())
            {
                //txt = "Alarm Message";
            }
            QLineEdit *edit = new QLineEdit(txt,this);

            ui->table->setCellWidget(row,column,edit);

            edit->setFixedSize(width,height);

            edit->selectAll();
            edit->setFocus();
        }

    }
}

//ѡ��λ��ַ������¼��ʱ�� ��itemchanged�Ĵ���
void AlarmDlg::CellChanged_Bit(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if(previousColumn == 1)
    {
        QWidget *wgt = ui->table->cellWidget(previousRow,previousColumn);
        AddWidget *addrWgt = dynamic_cast<AddWidget *>(wgt);
        QString str;
        if(addrWgt)
        {
            if(!addrWgt->check(0))
            {
                ui->table->setCurrentCell(previousRow,previousColumn,QItemSelectionModel::NoUpdate);

                return;
            }
            str = addrWgt->getString();
            ui->table->removeCellWidget(previousRow,previousColumn);
            wgt->deleteLater();
        }
        else
        {
            QTableWidgetItem *oItem = ui->table->item(previousRow,previousColumn);
            if(oItem)
                str = oItem->text();
        }

        if(str.isEmpty())
        {
            //ɾ��һ������
            QTableWidgetItem *oItem = ui->table->item(previousRow,1);
            if(oItem)
                oItem->setText("");
            oItem = ui->table->item(previousRow,2);
            if(oItem)
                oItem->setText("");
            oItem = ui->table->item(previousRow,3);
            if(oItem)
                oItem->setText("");
        }
        else
        {
            QTableWidgetItem *newitem = new QTableWidgetItem(str);
            ui->table->setItem(previousRow,previousColumn,newitem);
        }
    }
    else if(previousColumn == 2)
    {
        QString str;
        QWidget *wgt = ui->table->cellWidget(previousRow,previousColumn);
        QComboBox *combox = dynamic_cast<QComboBox *>(wgt);
        if(combox)
        {
            str = combox->currentText();
            ui->table->removeCellWidget(previousRow,previousColumn);
            wgt->deleteLater();
        }
        else
        {
            QTableWidgetItem *oItem = ui->table->item(previousRow,previousColumn);
            if(oItem)
                str = oItem->text();
        }
        QTableWidgetItem *newitem = new QTableWidgetItem(str);
        ui->table->setItem(previousRow,previousColumn,newitem);
    }
    else if(previousColumn == 3)
    {
        QString str;
        QWidget *wgt = ui->table->cellWidget(previousRow,previousColumn);
        QLineEdit *edit = dynamic_cast<QLineEdit *>(wgt);
        if(edit)
        {
            str = edit->text();
            ui->table->removeCellWidget(previousRow,previousColumn);
            wgt->deleteLater();
        }
        else
        {
            QTableWidgetItem *oItem = ui->table->item(previousRow,previousColumn);
            if(oItem)
                str = oItem->text();
        }
        QTableWidgetItem *newitem = new QTableWidgetItem(str);
        ui->table->setItem(previousRow,previousColumn,newitem);
    }
}

//ѡ���ֵ�ַ������¼��ʱ�� ��itemchanged�Ĵ���
void AlarmDlg::CellChanged_Word(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if(previousColumn == 1)
    {
        QWidget *wgt = ui->table->cellWidget(previousRow,previousColumn);
        AddWidget *addrWgt = dynamic_cast<AddWidget *>(wgt);
        QString str;
        if(addrWgt)
        {
            str = addrWgt->getString();
            if(!addrWgt->check(1))
            {
                ui->table->setCurrentCell(previousRow,previousColumn,QItemSelectionModel::NoUpdate);

                return;
            }
            ui->table->removeCellWidget(previousRow,previousColumn);
            wgt->deleteLater();

        }
        else
        {
            QTableWidgetItem *oItem = ui->table->item(previousRow,previousColumn);
            if(oItem)
                str = oItem->text();
        }

        if(str.isEmpty())
        {
            //ɾ��һ������
            QTableWidgetItem *oItem = ui->table->item(previousRow,1);
            if(oItem)
                oItem->setText("");
            oItem = ui->table->item(previousRow,2);
            if(oItem)
                oItem->setText("");
            oItem = ui->table->item(previousRow,3);
            if(oItem)
                oItem->setText("");
        }
        else
        {
            QTableWidgetItem *newitem = new QTableWidgetItem(str);
            ui->table->setItem(previousRow,previousColumn,newitem);
        }
    }
    else if(previousColumn == 2)
    {
        QString str;
        QWidget *wgt = ui->table->cellWidget(previousRow,previousColumn);
        CondWidget *condwgt = dynamic_cast<CondWidget *>(wgt);
        if(condwgt)
        {
            str = condwgt->getString();
            ui->table->removeCellWidget(previousRow,previousColumn);
            wgt->deleteLater();
        }
        else
        {
            QTableWidgetItem *oItem = ui->table->item(previousRow,previousColumn);
            if(oItem)
                str = oItem->text();
        }
        QTableWidgetItem *newitem = new QTableWidgetItem(str);
        ui->table->setItem(previousRow,previousColumn,newitem);
    }
    else if(previousColumn == 3)
    {
        QString str;
        QWidget *wgt = ui->table->cellWidget(previousRow,previousColumn);
        QLineEdit *edit = dynamic_cast<QLineEdit *>(wgt);
        if(edit)
        {
            str = edit->text();
            ui->table->removeCellWidget(previousRow,previousColumn);
            wgt->deleteLater();
        }
        else
        {
            QTableWidgetItem *oItem = ui->table->item(previousRow,previousColumn);
            if(oItem)
                str = oItem->text();
        }
        QTableWidgetItem *newitem = new QTableWidgetItem(str);
        ui->table->setItem(previousRow,previousColumn,newitem);
    }
}

bool AlarmDlg::eventFilter(QObject * o,QEvent *event)
{
    switch(event->type())
    {
    case QEvent::KeyPress:
        {
            QKeyEvent *kEvent = dynamic_cast<QKeyEvent *>(event);
            if(kEvent && kEvent->key() == Qt::Key_Return)
            {
                int row,column;
                row = ui->table->currentRow();
                column = ui->table->currentColumn();
                on_table_currentCellChanged(row,column,row,column);
                return false;
            }
        }
        break;
    case QEvent::MouseButtonPress:
        {
            QMouseEvent *mEvent = dynamic_cast<QMouseEvent *>(event);
            if(mEvent)
            {
                QRectF rect = ui->table->geometry();
                QPointF mousePos = mEvent->posF();
                if(!rect.contains(mousePos))
                {
                    int row,column;
                    row = ui->table->currentRow();
                    column = ui->table->currentColumn();
                    on_table_currentCellChanged(row,column,row,column);
                    return false;
                }
            }
        }
        break;
    case QEvent::MouseButtonDblClick:
        {
            QMouseEvent *mEvent = dynamic_cast<QMouseEvent *>(event);
            if(mEvent)
            {
                QRectF rect = ui->table->geometry();
                QPointF mousePos = mEvent->posF();
                if(!rect.contains(mousePos))
                {
                    int row,column;
                    row = ui->table->currentRow();
                    column = ui->table->currentColumn();
                    on_table_currentCellChanged(row,column,row,column);
                    return false;
                }
            }
        }
        break;
    default:
		break;
        
    }
	return QDialog::eventFilter(o,event);
}
void AlarmDlg::mousePressEvent ( QMouseEvent * event )
{
    QRectF rect = ui->table->geometry();
    QPointF mousePos = event->posF();
    if(!rect.contains(mousePos))
    {
        int row,column;
        row = ui->table->currentRow();
        column = ui->table->currentColumn();
        on_table_currentCellChanged(row,column,row,column);
        qDebug() << "$#$#&$^*@&#^*@#";
    }
}
void AlarmDlg::keyPressEvent ( QKeyEvent * event )
{
    if(event->key() == Qt::Key_Return)
    {
        int row,column;
        row = ui->table->currentRow();
        column = ui->table->currentColumn();
        on_table_currentCellChanged(row,column,row,column);
    }
	QDialog::keyPressEvent(event);
}
void AlarmDlg::tableFocusOut()
{
    int row,column;
    row = ui->table->currentRow();
    column = ui->table->currentColumn();
    on_table_currentCellChanged(row,column,row,column);
}

//����һ��������ַ
void AlarmDlg::on_btn_bat_clicked()
{

}

//�����л�
void AlarmDlg::on_combo_language_currentIndexChanged(int index)
{

}

//ȫ������
void AlarmDlg::on_btn_reset_clicked()
{
    int index = RadioGroup->checkedId();
    radioChanged(index);
}

//ȷ��
void AlarmDlg::on_btn_ok_clicked()
{
    QString alarmName = ui->edit_name->text();
    if(alarmName.isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("�������Ʋ���Ϊ��"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }
    QStringList names;
    foreach(ALARM_GROUP grp,pwnd->m_pSamSysParame->m_qvcAlarm)
    {
        names << grp.alarmName;
    }
    if(!bInit && names.contains(alarmName))
    {
        QString warning;
        warning +=tr("���� ");
        warning += alarmName;
        warning +=tr(" �Ѿ�����");
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,warning,0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }
    bool type = RadioGroup->checkedId();
    int dataType = ui->combo_datatype->currentIndex()+2;
    alarmGrp.alarmName = alarmName;
    alarmGrp.addrType = type;
    alarmGrp.dataType = (DATA_TYPE)dataType;
    int addrLen = 1;
    if(type)
    {
        switch(dataType)
        {
        case 1:
        case 3:
        case 5:
        case 6:
            addrLen = 2;
            break;
        }
    }
    foreach(stAlarm cAlarm,alarms)
    {
        cAlarm.addr.Length = addrLen;
    }
    alarmGrp.alarms = alarms;

    accept();
}

//����һ��Ĭ�ϱ���
void AlarmDlg::addAlarm(int row)
{
    if(row <0 || row >=MAX_ALARM_SIZE)
        return;
    stAlarm alarm;
    int index = RadioGroup->checkedId();
    //if(index)
    {
        alarm.addr = Keyboard();
        alarm.index = row;
        alarm.symb = 0;
        alarm.value = 0;
        QStringList msgs;
        for(int i=0; i<languageCount; i++)
        {
            msgs << "Alarm Message";
        }
        alarm.messages = msgs;
    }

    bool bExist = false;
    int i = 0;
    for(i = 0; i < alarms.size(); i++)
    {
        if(alarms[i].index == row)
        {
            bExist = true;
            break;
        }
    }

    if(bExist)//����alarm,�滻
    {
        alarms.replace(i,alarm);
    }else//������alarm��׷��
    {
        alarms.append(alarm);
    }
}

//�޸ı�������
void AlarmDlg::EditAlarm(int row)
{

    bool bExist = false;
    int i = 0;
    for(i = 0; i < alarms.size(); i++)
    {
        if(alarms[i].index == row)
        {
            bExist = true;
            break;
        }
    }
    //�����ǰ����δ��ӽ��б��������
    if(!bExist)
        addAlarm(row);

    //�޸ı�������

    stAlarm alarm = getAlarm(row);
    if(alarm.index != -1)
    {
        alarms.replace(i,alarm);
    }
    else
    {
        for(i=0;i<alarms.size();i++)
        {
            if(alarms[i].index == row)
            {
                alarms.remove(i);
            }
        }
    }
}
//ȡ��
void AlarmDlg::on_btn_cancel_clicked()
{
    reject();
}

//����
void AlarmDlg::on_btn_help_clicked()
{

}

//������������
void AlarmDlg::accept()
{
    QDialog::accept();
}

//��ʼ����������
void AlarmDlg::Init(ALARM_GROUP alarmGroup)
{
    bInit = true;
    alarms = alarmGroup.alarms;

    //��ʼ��UI
    ui->edit_name->setText(alarmGroup.alarmName);

	ui->label_2->setVisible(alarmGroup.addrType);
	ui->combo_datatype->setVisible(alarmGroup.addrType);

    if(alarmGroup.addrType)
    {
        ui->radio_word->setChecked(true);
    }
    else
    {
        ui->radio_bit->setChecked(true);
    }
    ui->combo_datatype->setCurrentIndex(alarmGroup.dataType -1);

    foreach(stAlarm pAlarm,alarms)
    {
        int row = pAlarm.index;
        if( row >= 0 && row < MAX_ALARM_SIZE)
        {
            //������ַ��
            QTableWidgetItem *item = ui->table->item(row,1);
            if(item)
            {
                item->setText(pAlarm.addr.sShowAddr);

            }
            else
            {
                item = new QTableWidgetItem(pAlarm.addr.sShowAddr);
                ui->table->setItem(row,1,item);
            }
            //����������
            item = ui->table->item(row,2);
            if(item)
            {
                item->setText(CondString(pAlarm));

            }
            else
            {
                item = new QTableWidgetItem(CondString(pAlarm));
                ui->table->setItem(row,2,item);
            }
            //������Ϣ��
            item = ui->table->item(row,3);
            QString msg = "Alarm Message";
            int index = ui->combo_language->currentIndex();
            if(index>=0 && index < pAlarm.messages.size())
            {
                msg = pAlarm.messages.at(index);
            }

            if(item)
            {
                item->setText(msg);

            }
            else
            {
                item = new QTableWidgetItem(msg);
                ui->table->setItem(row,3,item);
            }
        }
    }
}

//���ݱ���ȡ�ñ�������string
QString AlarmDlg::CondString(stAlarm alarm)
{
    QString txt;
    if(RadioGroup->checkedId())
    {
        txt.append(alarm.addr.sShowAddr);
        txt.append("\ ");

        switch(alarm.symb)
        {
        case 1:
            txt.append(tr(">"));
            break;
        case 2:
            txt.append(tr(">="));
            break;
        case 3:
            txt.append(tr("<"));
            break;
        case 4:
            txt.append(tr("<="));
            break;
        //case 0:
        default:
            txt.append(tr("="));
            break;
        }

        txt.append("\ ");
        txt.append(QString::number(alarm.value));
        txt.append("\ ");
        txt.append(tr("����"));
    }
    else
    {
        if(alarm.symb)
        {
            txt = tr("λOFF����");
        }
        else
        {
            txt = tr("λON����");
        }
    }
    return txt;
}
//ȡ�õ��б�����Ϣ
stAlarm AlarmDlg::getAlarm(int row)
{
    QStringList oMsgs;
    for(int i=0; i<languageCount; i++)
    {
        oMsgs << "Alarm Message";
    }

    for(int i=0;i<alarms.size();i++)
    {
        if(alarms[i].index == row)
        {
            oMsgs = alarms[i].messages;
        }
    }

    stAlarm alarm;
    Keyboard kb;
    QString sAddr;
    bool type = RadioGroup->checkedId();

    QTableWidgetItem *item = ui->table->item(row,1);
    if(item)
    {
        sAddr = item->text();
    }

    if(sAddr.isEmpty() || !pwnd->IsCheckAddressRight(kb,tr("�������ӵ�ַ"),0,type,sAddr))
    {
        alarm.index = -1;
        return alarm;
    }
    alarm.index = row;
    alarm.addr = kb;
    QString sCondition;
    item = ui->table->item(row,2);
    if(item)
    {
        sCondition = item->text();
    }
    if(type)//�ֵ�ַ�ı�������
    {

        QStringList strings = sCondition.split("\ ");
        if(strings.size() != 4)
        {
            alarm.index = -1;
            return alarm;
        }
        if(strings.at(1) == tr("="))
        {
            alarm.symb = 0;
        }
        else if(strings.at(1) == tr(">"))
        {
            alarm.symb = 1;
        }
        else if(strings.at(1) == tr(">="))
        {
            alarm.symb = 2;
        }
        else if(strings.at(1) == tr("<"))
        {
            alarm.symb = 3;
        }
        else if(strings.at(1) == tr("<="))
        {
            alarm.symb = 4;
        }
        alarm.value = strings.at(2).toDouble();
    }
    else
    {
        if(sCondition == tr("λOFF����"))
        {
            alarm.symb = 1;
        }
        else
            alarm.symb = 0;
    }

    QString msg;
    item = ui->table->item(row,3);
    if(item)
    {
        msg = item->text();
        int index = ui->combo_language->currentIndex();
        int size = oMsgs.size();
        if(size >index)
        {
            oMsgs.replace(index,msg);

        }
        alarm.messages = oMsgs;
    }
    return alarm;
}
