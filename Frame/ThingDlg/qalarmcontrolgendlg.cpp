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
    //ui->groupBox_3->setHidden(true);//隐藏格线
    pwnd->InitFontSize(ui->m_tfontsizecmb);//初始化字体大小
    pwnd->InitFontSize(ui->m_fontsizecmb);//初始化字体大小

    QVector<QString>language_vector;
	int languageCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    for(i=0;i < languageCount;i++)
    {
        language_vector.push_back(
			pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }
    for(i=0;i<languageCount;i++)//初始化语言选项
    {
        ui->m_languagecmb->addItem(language_vector.at(i));
    }

    ui->m_tfontcmb->addItems(QFontDatabase().families(QFontDatabase::Any));//初始化字体

    QString sFontName = tr("Droid Sans Fallback");
    i = ui->m_tfontcmb->findText(sFontName);//字体设置默认为宋体
    if(i < 0)
    {
        sFontName = "System";
        i = ui->m_tfontcmb->findText(sFontName);
    }
    ui->m_tfontcmb->setCurrentIndex(i);

    //初始化结构体
	
	TitleText.clear();
	TitleText.resize(languageCount);
    for(i = 0; i < TitleText.size(); i++)
    {
        TitleText[i].nFontSize = 10;           //字体大小
        TitleText[i].sFont = sFontName;//        //字体
        TitleText[i].sTime = tr("时间");       //时间
        TitleText[i].sDate = tr("日期");       //日期
        TitleText[i].sMessage = tr("消息"); //消息

        TitleText[i].sClearDate = tr("消除报警日期");       //清除报警日期
        TitleText[i].sClearTime = tr("消除报警时间");      //清除报警时间
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

    //ui->m_verticalcheck->setChecked(true);    //选中垂直
    //ui->m_horizontalcheck->setChecked(true);  //选中水平
    ui->m_tfontsizecmb->setCurrentIndex(5);   //标题列的字体大小
    ui->m_fontsizecmb->setCurrentIndex(5);    //文本列的字体大小
    ui->m_timecheck->setChecked(true);
    ui->m_timeedit->setText(tr("时间"));      //初始化时间edit
    ui->m_datecheck->setChecked(true);
    ui->m_dateedit->setText(tr("日期"));      //初始化日期edit
    ui->m_msgedit->setText(tr("消息"));    //初始化消息edit


    on_If_Use_Control_Add_clicked(false);

    ui->m_cleardate->setText(tr("清除报警日期"));
    ui->m_cleartime->setText(tr("清除报警时间"));
    on_If_Clean_Alarm_Data_clicked(false);
    on_If_Clean_Alarm_Time_clicked(false);

}

void QAlarmControlGenDlg::on_m_timecheck_clicked() //时间显示
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

void QAlarmControlGenDlg::on_m_datecheck_clicked() //日期显示
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

void QAlarmControlGenDlg::on_m_languagecmb_currentIndexChanged(int index)//语言
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
        ui->m_tfontsizecmb->setCurrentIndex(nIndex);      //标题列的字体大小

    nIndex = ui->m_tfontcmb->findText(TitleText[index].sFont);
    if(nIndex != -1)
    {
        ui->m_tfontcmb->setCurrentIndex(nIndex);          //文本列的字体大小
    }
    else
    {
        ui->m_tfontcmb->setCurrentIndex(0);
    }

    ui->m_timeedit->setText(TitleText[index].sTime);      //初始化时间edit
    ui->m_dateedit->setText(TitleText[index].sDate);      //初始化日期edit
    ui->m_msgedit->setText(TitleText[index].sMessage);    //初始化消息edit

    ui->m_cleardate->setText(TitleText[index].sClearDate);
    ui->m_cleartime->setText(TitleText[index].sClearTime);
}

void QAlarmControlGenDlg::on_m_timeedit_textChanged(QString ) //时间显示
{
    int nLanguage = ui->m_languagecmb->currentIndex();
    TitleText[nLanguage].sTime = ui->m_timeedit->text();
}

void QAlarmControlGenDlg::on_m_dateedit_textChanged(QString ) //日期显示
{
    int nLanguage = ui->m_languagecmb->currentIndex();
    TitleText[nLanguage].sDate = ui->m_dateedit->text();
}

void QAlarmControlGenDlg::on_m_msgedit_textChanged(QString )  //消息显示
{
    int nLanguage = ui->m_languagecmb->currentIndex();
    TitleText[nLanguage].sMessage = ui->m_msgedit->text();
}

void QAlarmControlGenDlg::on_m_tfontsizecmb_currentIndexChanged(int index)//字体大小
{
    if(!nFlg)
    {
        return;
    }
    QString str = ui->m_tfontsizecmb->currentText();
    int nLanguage = ui->m_languagecmb->currentIndex();
    TitleText[nLanguage].nFontSize = str.toInt();
}

void QAlarmControlGenDlg::on_m_tfontcmb_currentIndexChanged(int index)  //字体
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

        ui->m_timecmb->setCurrentIndex(alarmPro.eTimeFormat);//时间选择格式
        ui->m_datacmb->setCurrentIndex(alarmPro.eDateFormat);//日期选择格式

        int digitalSize = pwnd->m_pSamSysParame->m_qvcAlarm.size();

        on_m_timecheck_clicked();
        on_m_datecheck_clicked(); //日期显示

        ui->If_Use_Control_Add->setChecked(alarmPro.bControl);//是否使用报警地址

		Control_Address_Keyboard = alarmPro.controlAddr;
        //pwnd->StringToKeyboard(Control_Address_Keyboard,pdataList.at(65));
        if(alarmPro.bControl)
            ui->Control_Add->setText(Control_Address_Keyboard.sShowAddr);

        ui->If_Clean_Alarm_Data->setChecked(alarmPro.bClearDate);//是否显示消除警报日期

        ui->If_Clean_Alarm_Time->setChecked(alarmPro.bClearTime);//是否显示消除警报时间

        ui->m_cleardatecmb->setCurrentIndex(alarmPro.eClearDateFormat);//清除报警日期格式
        ui->m_cleartimecmb->setCurrentIndex(alarmPro.eClearTimeFormat);//清除报警时间格式

        ui->IFNO->setChecked(alarmPro.bShowNumber);//编号
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
       ! pwnd->IsAddressCheckRight(Control_Address_Keyboard,tr("控制地址"),ui->Control_Add,1))
    {
        ui->Control_Add->setFocus();
        return false;
    }
    return true;
}
void QAlarmControlGenDlg::AlarmControlGenSave()
{
    QString sTmp;
    //sTmp=ui->ID->text();//控件ID
    //datalist->replace(index,sTmp);
    //datalist->replace(19,sTmp);

    sTmp.clear();
    
    alarmPro.tableColor = ui->m_fbackcolorbtn->palette().background().color();//背景色
    
    alarmPro.frameColor =ui->m_fframcolorbtn->palette().background().color();//边框色
    
    
    
    alarmPro.titleBackcolor = ui->m_tbackcolorbtn->palette().background().color();//标题栏背景色
    
    alarmPro.titleColor = ui->m_ttextcolorbtn->palette().background().color();//标题颜色
    
    alarmPro.textColor = ui->m_fontcolorbtn->palette().background().color();//文本色
    
    int nState=ui->m_timecheck->isChecked();//时间复选框
    alarmPro.bShowTime = nState;

    
    nState=ui->m_datecheck->isChecked();//日期复选框
    alarmPro.bShowDate = nState;

    sTmp=ui->m_fontsizecmb->currentText();
    alarmPro.nFontSize = sTmp.toInt();

    nState=ui->m_rowspin->value();//行数
    alarmPro.rowCount = nState;

    //新增加内容
    nState=ui->m_timecmb->currentIndex();//时间选择格式
    alarmPro.eTimeFormat = nState;

    nState=ui->m_datacmb->currentIndex();//日期选择格式
    alarmPro.eDateFormat = nState;


    //alarmPro.groupName = ui->combo_groupname->currentText();

    nState=ui->If_Use_Control_Add->isChecked();//是否使用报警地址
    alarmPro.bControl = nState;

    if(alarmPro.bControl)
    {
        alarmPro.controlAddr = Control_Address_Keyboard;
        alarmPro.controlAddr.Length = 13;
    }


    nState=ui->If_Clean_Alarm_Data->isChecked();//是否显示消除警报日期
    alarmPro.bClearDate = nState;

    nState=ui->If_Clean_Alarm_Time->isChecked();//是否显示消除警报时间
    alarmPro.bClearTime = nState;

    alarmPro.clearedColor = ui->Clear_Alarm_Color->palette().background().color();//已消除报警的颜色
     
    alarmPro.confirmColor = ui->Receive_Note_Color->palette().background().color();//已确认报警的颜色
     

    alarmPro.eClearDateFormat = ui->m_cleardatecmb->currentIndex(); //清除报警日期格式
    

    alarmPro.eClearTimeFormat = ui->m_cleartimecmb->currentIndex(); //清除报警时间格式
    

    alarmPro.bShowNumber = ui->IFNO->isChecked(); //是否使用编号
    

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
void QAlarmControlGenDlg::setfbackcolorbtnColor(const QColor & mColor)       //设置边框色
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
void QAlarmControlGenDlg::setfframcolorbtnColor(const QColor & mColor)       //设置边框色
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
void QAlarmControlGenDlg::setlinecolorbtnColor(const QColor & mColor)       //设置边框色
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
void QAlarmControlGenDlg::settbackcolorbtnColor(const QColor & mColor)       //设置边框色
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
void QAlarmControlGenDlg::setttextcolorbtnColor(const QColor & mColor)       //设置边框色
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
void QAlarmControlGenDlg::setfontcolorbtnColor(const QColor & mColor)       //设置边框色
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
void QAlarmControlGenDlg::setClear_AlarmColor(const QColor & mColor)       //设置边框色
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
void QAlarmControlGenDlg::setReceive_Note_ColorColor(const QColor & mColor)       //设置边框色
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
