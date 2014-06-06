#include "qalarmcontrolgendlg.h"
#include <QFontDatabase>
#include "Frame/mainwindow.h"
#include "groupseldlg.h"
extern MainWindow *pwnd;

QAlarmControlGenDlg::QAlarmControlGenDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QAlarmControlGenDlg)
{
    ui->setupUi(this);
    nFlg=false;
    int i = 0;
    bAll = true;
    //ui->groupBox_3->setHidden(true);//���ظ���
    pwnd->InitFontSize(ui->m_tfontsizecmb);//��ʼ�������С
    pwnd->InitFontSize(ui->m_fontsizecmb);//��ʼ�������С

    QVector<QString>language_vector;
	int languageCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    for(i=0;i < languageCount;i++)
    {
        language_vector.push_back(
			pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }
    for(i=0;i<languageCount;i++)//��ʼ������ѡ��
    {
        ui->m_languagecmb->addItem(language_vector.at(i));
    }

    ui->m_tfontcmb->addItems(QFontDatabase().families(QFontDatabase::Any));//��ʼ������

    QString sFontName = tr("Droid Sans Fallback");
    i = ui->m_tfontcmb->findText(sFontName);//��������Ĭ��Ϊ����
    if(i < 0)
    {
        sFontName = "System";
        i = ui->m_tfontcmb->findText(sFontName);
    }
    ui->m_tfontcmb->setCurrentIndex(i);

    //��ʼ���ṹ��
	
	TitleText.clear();
	TitleText.resize(languageCount);
    for(i = 0; i < TitleText.size(); i++)
    {
        TitleText[i].nFontSize = 10;           //�����С
        TitleText[i].sFont = sFontName;//        //����
        TitleText[i].sTime = tr("ʱ��");       //ʱ��
        TitleText[i].sDate = tr("����");       //����
        TitleText[i].sMessage = tr("��Ϣ"); //��Ϣ

        TitleText[i].sClearDate = tr("������������");       //�����������
        TitleText[i].sClearTime = tr("��������ʱ��");      //�������ʱ��
    }

    //   InitParament();
    nFlg=true;


}

QAlarmControlGenDlg::~QAlarmControlGenDlg()
{
    delete ui;
}

void QAlarmControlGenDlg::InitParament()
{
    //int i = 0;
    ui->m_fbackcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(224,224,224).name()));
    ui->m_fframcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    //ui->m_linecolorbtn->setStyleSheet( QString("background:%1").arg(QColor(192,192,192).name()));
    ui->m_tbackcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(255,255,0).name()));
    ui->m_ttextcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    ui->m_fontcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    ui->Clear_Alarm_Color->setStyleSheet( QString("background:%1").arg(QColor(0,255,0).name()));
    ui->Receive_Note_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,255).name()));

    //ui->m_verticalcheck->setChecked(true);    //ѡ�д�ֱ
    //ui->m_horizontalcheck->setChecked(true);  //ѡ��ˮƽ
    ui->m_tfontsizecmb->setCurrentIndex(5);   //�����е������С
    ui->m_fontsizecmb->setCurrentIndex(5);    //�ı��е������С
    ui->m_timecheck->setChecked(true);
    ui->m_timeedit->setText(tr("ʱ��"));      //��ʼ��ʱ��edit
    ui->m_datecheck->setChecked(true);
    ui->m_dateedit->setText(tr("����"));      //��ʼ������edit
    ui->m_msgedit->setText(tr("��Ϣ"));    //��ʼ����Ϣedit


    on_If_Use_Control_Add_clicked(false);

    ui->m_cleardate->setText(tr("�����������"));
    ui->m_cleartime->setText(tr("�������ʱ��"));
    on_If_Clean_Alarm_Data_clicked(false);
    on_If_Clean_Alarm_Time_clicked(false);

}

void QAlarmControlGenDlg::on_m_timecheck_clicked() //ʱ����ʾ
{
    bool nFlag = ui->m_timecheck->checkState();
    if(nFlag)
    {
        ui->m_timeedit->setEnabled(true);
        ui->m_timelable->setEnabled(true);
        ui->m_timecmb->setEnabled(true);
    }
    else
    {
        ui->m_timeedit->setEnabled(false);
        ui->m_timelable->setEnabled(false);
        ui->m_timecmb->setEnabled(false);
    }
}

void QAlarmControlGenDlg::on_m_datecheck_clicked() //������ʾ
{
    bool nFlag = ui->m_datecheck->checkState();
    if(nFlag)
    {
        ui->m_dateedit->setEnabled(true);
        ui->m_datalable->setEnabled(true);
        ui->m_datacmb->setEnabled(true);
    }
    else
    {
        ui->m_dateedit->setEnabled(false);
        ui->m_datalable->setEnabled(false);
        ui->m_datacmb->setEnabled(false);
    }
}

void QAlarmControlGenDlg::on_m_languagecmb_currentIndexChanged(int index)//����
{
	if (!nFlg)
	{
		return;
	}
    QString str = "";
    int nIndex = 0;

    if(index == 0)
    {
        ui->label_16->setEnabled(true);
        ui->m_tbackcolorbtn->setEnabled(true);
        ui->label_19->setEnabled(true);
        ui->m_ttextcolorbtn->setEnabled(true);
    }
    else
    {
        ui->label_16->setEnabled(false);
        ui->m_tbackcolorbtn->setEnabled(false);
        ui->label_19->setEnabled(false);
        ui->m_ttextcolorbtn->setEnabled(false);
    }
    str = QString("%1").arg(TitleText[index].nFontSize);
    nIndex = ui->m_tfontsizecmb->findText(str);
    if(nIndex != -1)
        ui->m_tfontsizecmb->setCurrentIndex(nIndex);      //�����е������С

    nIndex = ui->m_tfontcmb->findText(TitleText[index].sFont);
    if(nIndex != -1)
    {
        ui->m_tfontcmb->setCurrentIndex(nIndex);          //�ı��е������С
    }
    else
    {
        ui->m_tfontcmb->setCurrentIndex(0);
    }

    ui->m_timeedit->setText(TitleText[index].sTime);      //��ʼ��ʱ��edit
    ui->m_dateedit->setText(TitleText[index].sDate);      //��ʼ������edit
    ui->m_msgedit->setText(TitleText[index].sMessage);    //��ʼ����Ϣedit

    ui->m_cleardate->setText(TitleText[index].sClearDate);
    ui->m_cleartime->setText(TitleText[index].sClearTime);
}

void QAlarmControlGenDlg::on_m_timeedit_textChanged(QString ) //ʱ����ʾ
{
    int nLanguage = ui->m_languagecmb->currentIndex();
    TitleText[nLanguage].sTime = ui->m_timeedit->text();
}

void QAlarmControlGenDlg::on_m_dateedit_textChanged(QString ) //������ʾ
{
    int nLanguage = ui->m_languagecmb->currentIndex();
    TitleText[nLanguage].sDate = ui->m_dateedit->text();
}

void QAlarmControlGenDlg::on_m_msgedit_textChanged(QString )  //��Ϣ��ʾ
{
    int nLanguage = ui->m_languagecmb->currentIndex();
    TitleText[nLanguage].sMessage = ui->m_msgedit->text();
}

void QAlarmControlGenDlg::on_m_tfontsizecmb_currentIndexChanged(int index)//�����С
{
    if(!nFlg)
    {
        return;
    }
    QString str = ui->m_tfontsizecmb->currentText();
    int nLanguage = ui->m_languagecmb->currentIndex();
    TitleText[nLanguage].nFontSize = str.toInt();
}

void QAlarmControlGenDlg::on_m_tfontcmb_currentIndexChanged(int index)  //����
{
	if(!nFlg)
	{
		return;
	}
    QString str = ui->m_tfontcmb->currentText();
    int nLanguage = ui->m_languagecmb->currentIndex();
    TitleText[nLanguage].sFont = str;
}
void QAlarmControlGenDlg::Init(QGraphicsItem *pItem)
{
    if(pItem)   
    {
		QItemGroup *aItem = dynamic_cast<QItemGroup *> (pItem);
		if (aItem && aItem->GroupType() == SAM_DRAW_GROUP_ALARMITEM)
		{
			AlarmItem *alarmItem = dynamic_cast<AlarmItem *> (pItem);
			if (alarmItem)
			{
				alarmPro = alarmItem->alarmPro;
			}
		}
		if (aItem && aItem->GroupType() == SAM_DRAW_GROUP_HISALARMITEM)
		{
			HisAlarmItem *alarmItem = dynamic_cast<HisAlarmItem *> (pItem);
			if (alarmItem)
			{
				alarmPro = alarmItem->alarmPro;
			}
		}
		
        int defSize = TitleText.size();
		int proSize = alarmPro.titles.size();
		int nSize = (defSize < proSize) ? defSize:proSize;
		for (int i=0; i<nSize; i++)
		{
			TitleText[i] = alarmPro.titles[i];
		}	     
        ui->m_fbackcolorbtn->setStyleSheet(QString("background:%1").arg(alarmPro.tableColor.name()));
        ui->m_fframcolorbtn->setStyleSheet(QString("background:%1").arg(alarmPro.frameColor.name()));
        //ui->m_linecolorbtn->setStyleSheet(QString("background:%1").arg());
        ui->m_tbackcolorbtn->setStyleSheet(QString("background:%1").arg(alarmPro.titleBackcolor.name()));
        ui->m_ttextcolorbtn->setStyleSheet(QString("background:%1").arg(alarmPro.titleColor.name()));
        ui->m_fontcolorbtn->setStyleSheet(QString("background:%1").arg(alarmPro.textColor.name()));
        ui->Clear_Alarm_Color->setStyleSheet(QString("background:%1").arg(alarmPro.clearedColor.name()));
        ui->Receive_Note_Color->setStyleSheet(QString("background:%1").arg(alarmPro.confirmColor.name()));
        
        on_m_languagecmb_currentIndexChanged(0);
        ui->m_timecheck->setChecked(alarmPro.bShowTime);
        ui->m_datecheck->setChecked(alarmPro.bShowDate);
		ui->m_fontsizecmb->setCurrentIndex(
			ui->m_fontsizecmb->findText(QString::number(alarmPro.nFontSize)));
        ui->m_rowspin->setValue(alarmPro.rowCount);

        ui->m_timecmb->setCurrentIndex(alarmPro.eTimeFormat);//ʱ��ѡ���ʽ
        ui->m_datacmb->setCurrentIndex(alarmPro.eDateFormat);//����ѡ���ʽ

        int digitalSize = pwnd->m_pSamSysParame->m_qvcAlarm.size();

        on_m_timecheck_clicked();
        on_m_datecheck_clicked(); //������ʾ

        ui->If_Use_Control_Add->setChecked(alarmPro.bControl);//�Ƿ�ʹ�ñ�����ַ

		Control_Address_Keyboard = alarmPro.controlAddr;
        //pwnd->StringToKeyboard(Control_Address_Keyboard,pdataList.at(65));
        if(alarmPro.bControl)
            ui->Control_Add->setText(Control_Address_Keyboard.sShowAddr);

        ui->If_Clean_Alarm_Data->setChecked(alarmPro.bClearDate);//�Ƿ���ʾ������������

        ui->If_Clean_Alarm_Time->setChecked(alarmPro.bClearTime);//�Ƿ���ʾ��������ʱ��

        ui->m_cleardatecmb->setCurrentIndex(alarmPro.eClearDateFormat);//����������ڸ�ʽ
        ui->m_cleartimecmb->setCurrentIndex(alarmPro.eClearTimeFormat);//�������ʱ���ʽ

        ui->IFNO->setChecked(alarmPro.bShowNumber);//���
        on_If_Clean_Alarm_Data_clicked(alarmPro.bClearDate);
        on_If_Clean_Alarm_Time_clicked(alarmPro.bClearTime);
        on_If_Use_Control_Add_clicked(alarmPro.bControl);

        bAll = alarmPro.bSelectAll;
        groupNames = alarmPro.groupName;
        //int index = ui->combo_groupname->findText(alarmPro.groupName);

        //if(index>=0)
        {
            //ui->combo_groupname->setCurrentIndex(index);
        }
    }
    else
    {
        InitParament();
    }

}
bool QAlarmControlGenDlg::isAllRight()
{
    if(ui->If_Use_Control_Add->isChecked() &&
       ! pwnd->IsAddressCheckRight(Control_Address_Keyboard,tr("���Ƶ�ַ"),ui->Control_Add,1))
    {
        ui->Control_Add->setFocus();
        return false;
    }
    return true;
}
void QAlarmControlGenDlg::AlarmControlGenSave()
{
    QString sTmp;
    //sTmp=ui->ID->text();//�ؼ�ID
    //datalist->replace(index,sTmp);
    //datalist->replace(19,sTmp);

    sTmp.clear();
    
    alarmPro.tableColor = ui->m_fbackcolorbtn->palette().background().color();//����ɫ
    
    alarmPro.frameColor =ui->m_fframcolorbtn->palette().background().color();//�߿�ɫ
    
    
    
    alarmPro.titleBackcolor = ui->m_tbackcolorbtn->palette().background().color();//����������ɫ
    
    alarmPro.titleColor = ui->m_ttextcolorbtn->palette().background().color();//������ɫ
    
    alarmPro.textColor = ui->m_fontcolorbtn->palette().background().color();//�ı�ɫ
    
    int nState=ui->m_timecheck->isChecked();//ʱ�临ѡ��
    alarmPro.bShowTime = nState;

    
    nState=ui->m_datecheck->isChecked();//���ڸ�ѡ��
    alarmPro.bShowDate = nState;

    sTmp=ui->m_fontsizecmb->currentText();
    alarmPro.nFontSize = sTmp.toInt();

    nState=ui->m_rowspin->value();//����
    alarmPro.rowCount = nState;

    //����������
    nState=ui->m_timecmb->currentIndex();//ʱ��ѡ���ʽ
    alarmPro.eTimeFormat = nState;

    nState=ui->m_datacmb->currentIndex();//����ѡ���ʽ
    alarmPro.eDateFormat = nState;


    //alarmPro.groupName = ui->combo_groupname->currentText();

    nState=ui->If_Use_Control_Add->isChecked();//�Ƿ�ʹ�ñ�����ַ
    alarmPro.bControl = nState;

    if(alarmPro.bControl)
    {
        alarmPro.controlAddr = Control_Address_Keyboard;
        alarmPro.controlAddr.Length = 13;
    }


    nState=ui->If_Clean_Alarm_Data->isChecked();//�Ƿ���ʾ������������
    alarmPro.bClearDate = nState;

    nState=ui->If_Clean_Alarm_Time->isChecked();//�Ƿ���ʾ��������ʱ��
    alarmPro.bClearTime = nState;

    alarmPro.clearedColor = ui->Clear_Alarm_Color->palette().background().color();//��������������ɫ
     
    alarmPro.confirmColor = ui->Receive_Note_Color->palette().background().color();//��ȷ�ϱ�������ɫ
     

    alarmPro.eClearDateFormat = ui->m_cleardatecmb->currentIndex(); //����������ڸ�ʽ
    

    alarmPro.eClearTimeFormat = ui->m_cleartimecmb->currentIndex(); //�������ʱ���ʽ
    

    alarmPro.bShowNumber = ui->IFNO->isChecked(); //�Ƿ�ʹ�ñ��
    

    alarmPro.titles = TitleText;
    alarmPro.bSelectAll = bAll;
    if(!bAll)
    {
        alarmPro.groupName = groupNames;
    }
}


void QAlarmControlGenDlg::on_If_Use_Control_Add_clicked(bool checked)
{
    if(checked)
    {
        ui->label_12->setEnabled(true);
        ui->Control_Add->setEnabled(true);
        ui->Control_Add_Keyboard->setEnabled(true);
    }
    else
    {
        ui->label_12->setEnabled(false);
        ui->Control_Add->setEnabled(false);
        ui->Control_Add_Keyboard->setEnabled(false);

    }
}

void QAlarmControlGenDlg::on_Control_Add_Keyboard_clicked()
{
    QString addrStr = ui->Control_Add->text();
    AddressInputDialog addressintputdlg_writeaddress(Control_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->Control_Add->setText(Control_Address_Keyboard.sShowAddr);
    }
}

void QAlarmControlGenDlg::on_If_Clean_Alarm_Data_clicked(bool checked)
{
    if(checked)
    {
        ui->m_cleardatelable->setEnabled(true);
        ui->m_cleardate->setEnabled(true);
        ui->m_cleardatecmb->setEnabled(true);
    }
    else
    {
        ui->m_cleardatelable->setEnabled(false);
        ui->m_cleardate->setEnabled(false);
        ui->m_cleardatecmb->setEnabled(false);
    }
}

void QAlarmControlGenDlg::on_If_Clean_Alarm_Time_clicked(bool checked)
{
    if(checked)
    {
        ui->m_cleartimelable->setEnabled(true);
        ui->m_cleartime->setEnabled(true);
        ui->m_cleartimecmb->setEnabled(true);
    }
    else
    {
        ui->m_cleartimelable->setEnabled(false);
        ui->m_cleartime->setEnabled(false);
        ui->m_cleartimecmb->setEnabled(false);
    }
}

void QAlarmControlGenDlg::on_m_cleardate_textChanged(QString sContent)
{
    int nLanguage = ui->m_languagecmb->currentIndex();
    TitleText[nLanguage].sClearDate = sContent;
}

void QAlarmControlGenDlg::on_m_cleartime_textChanged(QString sContent)
{
    int nLanguage = ui->m_languagecmb->currentIndex();
    TitleText[nLanguage].sClearTime = sContent;
}

void QAlarmControlGenDlg::on_m_fbackcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_fbackcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setfbackcolorbtnColor(const QColor &)));

}
void QAlarmControlGenDlg::setfbackcolorbtnColor(const QColor & mColor)       //���ñ߿�ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_fbackcolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QAlarmControlGenDlg::on_m_fframcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_fframcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setfframcolorbtnColor(const QColor &)));

}
void QAlarmControlGenDlg::setfframcolorbtnColor(const QColor & mColor)       //���ñ߿�ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_fframcolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QAlarmControlGenDlg::on_m_linecolorbtn_clicked()
{
    //ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    //pwnd->OnAddColorDlg(ui->m_linecolorbtn ,colorPicker);
    //connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setlinecolorbtnColor(const QColor &)));

}
void QAlarmControlGenDlg::setlinecolorbtnColor(const QColor & mColor)       //���ñ߿�ɫ
{
    //QString nColor = pwnd->ColorTOString(mColor);
    //ui->m_linecolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QAlarmControlGenDlg::on_m_tbackcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_tbackcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(settbackcolorbtnColor(const QColor &)));

}
void QAlarmControlGenDlg::settbackcolorbtnColor(const QColor & mColor)       //���ñ߿�ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_tbackcolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QAlarmControlGenDlg::on_m_ttextcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_ttextcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setttextcolorbtnColor(const QColor &)));

}
void QAlarmControlGenDlg::setttextcolorbtnColor(const QColor & mColor)       //���ñ߿�ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_ttextcolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QAlarmControlGenDlg::on_m_fontcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_fontcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setfontcolorbtnColor(const QColor &)));

}
void QAlarmControlGenDlg::setfontcolorbtnColor(const QColor & mColor)       //���ñ߿�ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_fontcolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QAlarmControlGenDlg::on_Clear_Alarm_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->Clear_Alarm_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setClear_AlarmColor(const QColor &)));

}
void QAlarmControlGenDlg::setClear_AlarmColor(const QColor & mColor)       //���ñ߿�ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->Clear_Alarm_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QAlarmControlGenDlg::on_Receive_Note_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->Receive_Note_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setReceive_Note_ColorColor(const QColor &)));

}
void QAlarmControlGenDlg::setReceive_Note_ColorColor(const QColor & mColor)       //���ñ߿�ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->Receive_Note_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}


void QAlarmControlGenDlg::on_btn_groupset_clicked()
{
    GroupSelDlg dlg(groupNames,bAll,this);
    if(dlg.exec() == QDialog::Accepted)
    {
        groupNames = dlg.getNames(bAll);
    }
}
