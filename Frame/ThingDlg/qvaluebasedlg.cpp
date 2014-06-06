#include "qvaluebasedlg.h"
#include "ui_qvaluebasedlg.h"
#include "Frame/addressinputdialog.h"
#include <QFontDatabase>
#include "Macro/macroedit.h"
#include "qvaluescaledlg.h"
#include "ui_qvaluescaledlg.h"
#include "expressiondlg.h"

extern MainWindow *pwnd;

QValueBaseDlg::QValueBaseDlg(QWidget *parent, QValueScaleDlg *pScaleDlg) :
    QWidget(parent),
    ui(new Ui::QValueBaseDlg)
{
    ui->setupUi(this);
    bInitFlag = false;
    pScaleWidget = pScaleDlg;

    ui->m_fontCbBox->addItems(QFontDatabase().families(QFontDatabase::Any));
    pwnd->InitFontSize(ui->m_FontSizecbBox);//初始化字体大小下拉列表框
    ui->m_roundckBox->setEnabled(false);
    ui->m_dateInputBtn->setEnabled(false);
    ui->m_DateckBox->setChecked(true);//日期時間初始化選中
    ui->m_FontTypegroupBox->hide();
    ui->m_DateTimegroupBox->hide();
    ui->m_FontstygroupBox->hide();
    ui->m_CodeTypegroupBox->hide();

    ui->m_FontstygroupBox->setGeometry(QRect(10, 280, 571, 41));

    ui->m_FontTypegroupBox->setGeometry(QRect(320, 130, 261, 131));
    ui->m_DateTimegroupBox->setGeometry(QRect(10, 130, 281, 131));

    ui->m_CodeTypegroupBox->setGeometry(QRect(10, 280, 571, 61));
    //ui->m_UseMacroCkkgroupBox->setGeometry(QRect(20, 240, 561, 61));
    //ui->m_scalSetgroupBox->setGeometry(QRect(10, 250, 571, 141));
    ui->Monitor_Address->setText("LW0");


    on_m_SourcecbBox_currentIndexChanged(0);
    on_m_ShowcbBox_currentIndexChanged(0);
    on_m_LimitSourcecbBox_currentIndexChanged(0);
    ui->m_OrdinaryckBox->setChecked(true);

    foreach(Macro lib,pwnd->macros)
    {
        if (lib.type && lib.isCompiled())
        {
            ui->m_MacroCmBox->addItem(lib.libName);
        }
    }

    int index = ui->m_fontCbBox->findText(tr("Droid Sans Fallback"));
    if(index >= 0)
    {
        ui->m_fontCbBox->setCurrentIndex(index);
    }
    else
    {
        ui->m_fontCbBox->setCurrentIndex(ui->m_fontCbBox->findText(tr("System")));

    }

    on_checkBox_clicked(false);
    //connect(ui->m_MacroCmBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(libraryChanged(QString)));

    onSetPreview();//设置日期时间格式的预览字符串
    ui->edit_expression->setDisabled(true);
}

QValueBaseDlg::~QValueBaseDlg()
{
    delete ui;
}

void QValueBaseDlg::on_m_asciiInputBtn_clicked()
{   
    ui->m_offsetAddress->show();
    ui->Offset_Address_EntryBtn->show();
    ui->m_UseMacroCkkgroupBox->show();
    ui->m_InputPromptckBox->show();

    ui->checkBox->show();
    if(ui->checkBox->isChecked())
    {
        ui->m_offsetAddress->setEnabled(true);
        ui->Offset_Address_EntryBtn->setEnabled(true);
    }
    else
    {
        ui->m_offsetAddress->setEnabled(false);
        ui->Offset_Address_EntryBtn->setEnabled(false);
    }

    //ui->m_InputPromptckBox->hide();
    ui->m_AllowInputgroupBox->hide();
    ui->m_scalSetckBox->hide();
    ui->m_FontTypegroupBox->hide();
    ui->m_MonitorAddresslabel->show();
    ui->Monitor_Address->show();
    ui->Monitor_Address_EntryBtn->show();
    ui->m_AllowInputckBox->show();

    ui->check_expression->hide();
    ui->edit_expression->hide();
    ui->btn_expression->hide();
    ui->checkBox_2->show();
    ui->label_16->show();
    ui->m_offsetAddress_2->show();
    ui->Offset_Address_EntryBtn_2->show();
    if(ui->checkBox_2->isChecked())
    {
        ui->m_offsetAddress_2->setEnabled(false);
        ui->Offset_Address_EntryBtn_2->setEnabled(false);
    }
    else
    {
        ui->m_offsetAddress_2->setEnabled(true);
        ui->Offset_Address_EntryBtn_2->setEnabled(true);
    }

    ui->m_DataTypelabel->hide();
    ui->m_DataTypefontCmbBox->hide();
    ui->m_roundckBox->hide();
    ui->m_DateTimegroupBox->hide();
    ui->m_FontstygroupBox->hide();
    ui->m_CodeTypegroupBox->show();
    //ui->checkBox->setGeometry(QRect(14, 154, 91, 16));
    //ui->m_offsetAddress->setGeometry(QRect(110, 151, 111, 21));
    //ui->Offset_Address_EntryBtn->setGeometry(QRect(220, 151, 20, 21));
    //ui->checkBox_2->setGeometry(QRect(14, 188, 180, 16));
    //ui->m_offsetAddress_2->setGeometry(QRect(430, 110, 121, 21));
    //ui->Offset_Address_EntryBtn_2->setGeometry(QRect(550, 110, 20, 21));
    ui->m_UseMacroCkkgroupBox->setGeometry(QRect(10, 360, 571, 51));
    if(getAllowInputState())
    {
        ui->m_UseMacroCkkgroupBox->setEnabled(true);
    }
    else
    {
        ui->m_UseMacroCkkgroupBox->setEnabled(false);
    }
    ui->m_dateInputBtn->setEnabled(true);
    ui->m_asciiInputBtn->setEnabled(false);
    ui->m_timeInputBtn->setEnabled(true);
    emit onTabWightSwitch(ASCIIINPUTSHOW);
    emit setDataLength(0 , 128,bInitFlag, true);
    //on_m_DataTypefontCmbBox_currentIndexChanged(ui->m_DataTypefontCmbBox->currentIndex());
    on_m_AllowInputckBox_clicked(ui->m_AllowInputckBox->isChecked());
}

void QValueBaseDlg::on_m_dateInputBtn_clicked()
{
    ui->m_offsetAddress->show();
    ui->Offset_Address_EntryBtn->show();
    ui->m_UseMacroCkkgroupBox->show();
    ui->check_expression->show();

    ui->checkBox->show();
    if(ui->checkBox->isChecked())
    {
        ui->m_offsetAddress->setEnabled(true);
        ui->Offset_Address_EntryBtn->setEnabled(true);
    }
    else
    {
        ui->m_offsetAddress->setEnabled(false);
        ui->Offset_Address_EntryBtn->setEnabled(false);
    }

    ui->m_InputPromptckBox->show();
    ui->m_AllowInputgroupBox->show();
    ui->m_scalSetckBox->show();
    ui->m_MonitorAddresslabel->show();
    ui->Monitor_Address->show();
    ui->Monitor_Address_EntryBtn->show();
    ui->m_AllowInputckBox->show();
    ui->m_DataTypelabel->show();
    ui->m_DataTypefontCmbBox->show();
    ui->m_roundckBox->show();

    ui->checkBox_2->show();
    ui->label_16->show();
    ui->m_offsetAddress_2->show();
    ui->Offset_Address_EntryBtn_2->show();
    if(ui->checkBox_2->isChecked())
    {
        ui->m_offsetAddress_2->setEnabled(false);
        ui->Offset_Address_EntryBtn_2->setEnabled(false);
    }
    else
    {
        ui->m_offsetAddress_2->setEnabled(true);
        ui->Offset_Address_EntryBtn_2->setEnabled(true);
    }

    ui->m_DateTimegroupBox->hide();
    ui->m_FontstygroupBox->hide();
    ui->m_CodeTypegroupBox->hide();
    //ui->checkBox->setGeometry(QRect(14, 154, 91, 16));
    //ui->m_offsetAddress->setGeometry(QRect(110, 151, 111, 21));
    //ui->Offset_Address_EntryBtn->setGeometry(QRect(220, 151, 20, 21));
    //ui->checkBox->setGeometry(QRect(14, 188, 91, 16));
    //ui->m_offsetAddress->setGeometry(QRect(110, 185, 111, 21));
    //ui->Offset_Address_EntryBtn->setGeometry(QRect(220, 185, 20, 21));
    //ui->checkBox_2->setGeometry(QRect(14, 222, 180, 16));
    //ui->m_offsetAddress_2->setGeometry(QRect(430, 110, 121, 21));
    //ui->Offset_Address_EntryBtn_2->setGeometry(QRect(550, 110, 20, 21));
    ui->m_UseMacroCkkgroupBox->setGeometry(QRect(10, 360, 571, 51));
    ui->m_UseMacroCkkgroupBox->setGeometry(QRect(10, 400, 571, 51));
    if(getAllowInputState())
    {
        ui->m_UseMacroCkkgroupBox->setEnabled(true);
    }
    else
    {
        ui->m_UseMacroCkkgroupBox->setEnabled(false);
    }

    ui->m_FontTypegroupBox->hide();

    ui->m_dateInputBtn->setEnabled(false);
    ui->m_asciiInputBtn->setEnabled(true);
    ui->m_timeInputBtn->setEnabled(true);
    emit onTabWightSwitch(DATAINPUTSHOW);
    if(bInitFlag)
    on_m_DataTypefontCmbBox_currentIndexChanged(ui->m_DataTypefontCmbBox->currentIndex());
    on_m_AllowInputckBox_clicked(ui->m_AllowInputckBox->isChecked());
}

void QValueBaseDlg::on_m_timeInputBtn_clicked()
{
    ui->m_offsetAddress->hide();
    ui->Offset_Address_EntryBtn->hide();
    ui->checkBox->hide();

    ui->m_InputPromptckBox->hide();
    ui->m_AllowInputgroupBox->hide();
    ui->m_CodeTypegroupBox->hide();
    ui->m_MonitorAddresslabel->hide();
    ui->Monitor_Address->hide();
    ui->Monitor_Address_EntryBtn->hide();
    ui->m_AllowInputckBox->hide();
    ui->m_scalSetckBox->hide();
    ui->m_DataTypelabel->hide();
    ui->m_DataTypefontCmbBox->hide();
    ui->m_roundckBox->hide();
    ui->m_FontTypegroupBox->show();
    ui->m_DateTimegroupBox->show();
    ui->m_FontstygroupBox->show();
    ui->m_UseMacroCkkgroupBox->hide();
    ui->checkBox_2->hide();
    ui->label_16->hide();
    ui->m_offsetAddress_2->hide();
    ui->Offset_Address_EntryBtn_2->hide();
    ui->check_expression->hide();
    ui->edit_expression->hide();
    ui->btn_expression->hide();

    ui->m_dateInputBtn->setEnabled(true);
    ui->m_asciiInputBtn->setEnabled(true);
    ui->m_timeInputBtn->setEnabled(false);
    emit onTabWightSwitch(DATETIMEINPUT);
    on_m_AllowInputckBox_clicked(ui->m_AllowInputckBox->isChecked());
    //on_m_DataTypefontCmbBox_currentIndexChanged(ui->m_DataTypefontCmbBox->currentIndex());
}
//选择缩放
void QValueBaseDlg::on_m_scalSetckBox_clicked(bool checked)
{
    emit scaleClicked(checked);
}

void QValueBaseDlg::Init(DataDisplayItem *pItem)
{
    if(pItem)
    {
        if(DATAINPUTSHOW == pItem->m_etabPag)
        {
           ui->m_AllowInputckBox->setChecked(pItem->m_data.bIsInput);  //允许输入
           on_m_dateInputBtn_clicked();  //数值输入
        }
        else if(ASCIIINPUTSHOW == pItem->m_etabPag)
        {
            ui->m_AllowInputckBox->setChecked(pItem->m_ascii.bIsinput);         //允许输入
            on_m_asciiInputBtn_clicked(); //ascii输入
        }
        else if(DATETIMEINPUT == pItem->m_etabPag)
        {
            on_m_timeInputBtn_clicked();  //日期时间显示
        }

        if(DATAINPUTSHOW == pItem->m_etabPag)
        {
            ui->m_offsetAddress->show();
            ui->Offset_Address_EntryBtn->show();
            ui->m_UseMacroCkkgroupBox->show();

            //初始化偏移地址相关
            ui->checkBox->setChecked(pItem->m_data.bOffset);
            if(pItem->m_data.bOffset)
            {
                ui->m_offsetAddress->setText(pItem->m_data.addrOffset.sShowAddr);
            }
            on_checkBox_clicked(pItem->m_data.bOffset);

            ui->checkBox_2->setChecked(pItem->m_data.bInputIsShow);
            if(pItem->m_data.bIsInput && !pItem->m_data.bInputIsShow)
            {
                ui->m_offsetAddress_2->setText(pItem->m_data.addrInputSame.sShowAddr);
            }
            on_checkBox_2_clicked(pItem->m_data.bInputIsShow);

            if(pItem->m_data.bIsInput)
            {
                if(!pItem->m_data.bInputIsShow)
                {
                    ui->m_offsetAddress_2->setEnabled(false);
                    ui->Offset_Address_EntryBtn_2->setEnabled(false);
                }
                else
                {
                    ui->m_offsetAddress_2->setEnabled(true);
                    ui->Offset_Address_EntryBtn_2->setEnabled(true);
                }
            }

            int nType = pItem->m_data.eNumberType;
            ui->m_DataTypefontCmbBox->setCurrentIndex(nType); //数据类型

            ui->Monitor_Address->setText(pItem->m_data.addr.sShowAddr);         //监控字地址
            //ui->m_AllowInputckBox->setChecked(pItem->m_data.bIsInput);  //允许输入

            ui->m_scalSetckBox->setChecked(pItem->m_data.bIsScale);     //缩放设置
            on_m_scalSetckBox_clicked(pItem->m_data.bIsScale);

            ui->m_UseMacroCkkgroupBox->setChecked(pItem->m_data.bUseMacro);
            int index = ui->m_MacroCmBox->findText(pItem->m_data.macroName);
            //if(index >= 0)
            {
                ui->m_MacroCmBox->setCurrentIndex(index);
            }

            bInitFlag = true;
            on_m_DataTypefontCmbBox_currentIndexChanged(nType);

            ///////////--------------------------
            if(pItem->m_data.bIsInput)
            {
                ui->m_InputPromptckBox->setChecked(pItem->m_data.bInputSign);
                ui->m_LimitSourcecbBox->setCurrentIndex(pItem->m_data.eInputAreaType);;
                if(1 == ui->m_LimitSourcecbBox->currentIndex())
                {
                    ui->m_MaxLimitlineEdit->setText(pItem->m_data.sInputMax);
                    ui->m_MinLimitlineEdit->setText(pItem->m_data.sInputMin);
                }
                else
                {
                    ui->m_MaxLimitspBox->setText(pItem->m_data.sInputMax);
                    ui->m_MinLimitspBox->setText(pItem->m_data.sInputMin);
                }
            }
            ///////////--------------------------

            pScaleWidget->ui->m_SourcecbBox->setCurrentIndex(pItem->m_data.nByteLength);        //源范围:指定源范围
            if(0 == pItem->m_data.nByteLength)
            {
                pScaleWidget->ui->m_SMaxspBox->setText(pItem->m_data.sSourceMax);                   //源范围:最大
                pScaleWidget->ui->m_SMinspBox->setText(pItem->m_data.sSourceMin);                    //源范围:最小
            }
            else
            {
                pScaleWidget->ui->m_SMaxlineEdit->setText(pItem->m_data.sSourceMax);                   //源范围:最大
                pScaleWidget->ui->m_SMinlineEdit->setText(pItem->m_data.sSourceMin);                   //源范围:最小
            }
            on_m_SourcecbBox_currentIndexChanged(pItem->m_data.nByteLength);

            pScaleWidget->ui->m_ShowcbBox->setCurrentIndex(pItem->m_data.sShow);                //显示范围:指定显示范围
            if(0 == pItem->m_data.sShow)
            {
                pScaleWidget->ui->m_ShowMaxspBox->setText(pItem->m_data.sShowMax);                  //显示范围:最大
                pScaleWidget->ui->m_ShowMinspBox->setText(pItem->m_data.sShowMin);                  //显示范围:最小
                on_m_ShowcbBox_currentIndexChanged(0);
            }
            else
            {
                pScaleWidget->ui->m_ShowMaxlineEdit->setText(pItem->m_data.sShowMax);                  //显示范围:最大
                pScaleWidget->ui->m_ShowMinlineEdit->setText(pItem->m_data.sShowMin);                  //显示范围:最小
                on_m_ShowcbBox_currentIndexChanged(1);
            }

            ui->m_roundckBox->setChecked(pItem->m_data.bRound);             //显示范围:四舍五入
            ui->check_expression->setChecked(pItem->m_data.bOutExpression);
            m_outExp = pItem->m_data.m_outputExp;
            m_inputExp = pItem->m_data.m_inputExp;
            on_check_expression_clicked(pItem->m_data.bOutExpression);
            if(pItem->m_data.bOutExpression)//表达式显示
            {
                ui->edit_expression->setText(m_outExp.getExpString());
            }
        }
        else if(ASCIIINPUTSHOW == pItem->m_etabPag)
        {
            ui->m_offsetAddress->show();
            ui->Offset_Address_EntryBtn->show();
            ui->m_UseMacroCkkgroupBox->show();
            ui->m_InputPromptckBox->show();
            ui->check_expression->hide();
            ui->edit_expression->hide();
            ui->btn_expression->hide();

            //初始化偏移地址相关
            ui->checkBox->setChecked(pItem->m_ascii.bOffset);
            if(pItem->m_ascii.bOffset)
            {
                ui->m_offsetAddress->setText(pItem->m_ascii.addrOffset.sShowAddr);
            }
            on_checkBox_clicked(pItem->m_ascii.bOffset);

            ui->checkBox_2->setChecked(pItem->m_ascii.bInputIsShow);
            if(pItem->m_data.bIsInput && !pItem->m_data.bInputIsShow)
            {
                ui->m_offsetAddress_2->setText(pItem->m_ascii.addrInputSame.sShowAddr);
            }
            on_checkBox_2_clicked(pItem->m_ascii.bInputIsShow);
            /*if(pItem->m_ascii.bIsinput)
            {
                if(!pItem->m_ascii.bInputIsShow)
                {
                    ui->m_offsetAddress_2->setEnabled(false);
                    ui->Offset_Address_EntryBtn_2->setEnabled(false);
                }
                else
                {
                    ui->m_offsetAddress_2->setEnabled(true);
                    ui->Offset_Address_EntryBtn_2->setEnabled(true);
                }
            }*/

            ui->m_DataTypefontCmbBox->setCurrentIndex(pItem->m_ascii.eNumberType); //数据类型

            if((pItem->m_ascii.nCode)&1)
            {
                ui->m_secretCkBox->setChecked(true);
            }
            if((pItem->m_ascii.nCode)&2)
            {
                ui->m_unicodeCkBox->setChecked(true);
            }
            if((pItem->m_ascii.nCode)&8)
            {
                ui->m_HtoLCkBox->setChecked(true);
            }
            if((pItem->m_ascii.nCode)&16)
            {
                ui->m_showHtoLCkBox->setChecked(true);
            }

            ui->Monitor_Address->setText(pItem->m_ascii.addr.sShowAddr);                //监控字地址
            //ui->m_AllowInputckBox->setChecked(pItem->m_ascii.bIsinput);         //允许输入
            if(pItem->m_ascii.bIsinput)
            {
                ui->m_InputPromptckBox->setChecked(pItem->m_ascii.bInputSign);
            }
            ui->m_UseMacroCkkgroupBox->setChecked(pItem->m_ascii.bUseMacro);
            int index = ui->m_MacroCmBox->findText(pItem->m_ascii.macroName);
            if(index >= 0)
            {
                ui->m_MacroCmBox->setCurrentIndex(index);
            }
        }
        else if(DATETIMEINPUT == pItem->m_etabPag)
        {
            ui->check_expression->hide();
            ui->edit_expression->hide();
            ui->btn_expression->hide();

            ui->m_DateckBox->setChecked(pItem->m_time.bDateMark);//日期选中状态
            ui->m_WeekckBox->setChecked(pItem->m_time.bWeekMark);//星期选中状态
            ui->m_TimeckBox->setChecked(pItem->m_time.bTimeMark);//时间选中状态
            ui->m_DatecbBox->setCurrentIndex(pItem->m_time.eShowDate);//日期index
            ui->m_TimecbBox->setCurrentIndex(pItem->m_time.eShowTime);//时间index
            ui->m_ShowlineEdit->setText(pItem->m_time.nPreView);//预览文本
            ui->m_fontCbBox->setCurrentIndex(pItem->m_time.nFontStyle);//字体类型
            ui->m_FontSizecbBox->setCurrentIndex(pItem->m_time.nFontSize);//字体大小
            //ui->m_FonttypecbBox->setCurrentIndex(pItem->m_time.eFontCss);//文本属性
            if(0 == pItem->m_time.eFontCss)
            {
                ui->m_OrdinaryckBox->setChecked(true);
            }
            else
            {
                ui->m_OrdinaryckBox->setChecked(false);
                if((1&(pItem->m_time.eFontCss)))
                {
                    ui->m_BoldckBox->setChecked(true);
                }
                if((2&(pItem->m_time.eFontCss)))
                {
                    ui->m_ItalicckBox->setChecked(true);
                }
                if((8&(pItem->m_time.eFontCss)))
                {
                    ui->m_UnderlineckBox->setChecked(true);
                }
            }

            ui->m_LanguagecbBox->setCurrentIndex(pItem->m_time.nLanguageTypeId);
        }
    }
    else
    {
       on_m_dateInputBtn_clicked();
       bInitFlag = true;
       on_m_DataTypefontCmbBox_currentIndexChanged(ui->m_DataTypefontCmbBox->currentIndex());
       ui->check_expression->setChecked(false);
       on_check_expression_clicked(false);
    }
    on_m_AllowInputckBox_clicked(ui->m_AllowInputckBox->isChecked());

    if(pItem)
    {
        if(ui->m_AllowInputckBox->isChecked())
        {
            if(DATAINPUTSHOW == pItem->m_etabPag)
            {
                ui->checkBox_2->setChecked(pItem->m_data.bInputIsShow);
                if(pItem->m_data.bInputIsShow)
                {
                    ui->checkBox_2->setChecked(pItem->m_data.bInputIsShow);
                    ui->m_offsetAddress_2->setEnabled(false);
                    ui->Offset_Address_EntryBtn_2->setEnabled(false);
                }
                else
                {
                    ui->m_offsetAddress_2->setEnabled(true);
                    ui->Offset_Address_EntryBtn_2->setEnabled(true);
                    ui->m_offsetAddress_2->setText(pItem->m_data.addrInputSame.sShowAddr);
                }
            }
            else if(ASCIIINPUTSHOW == pItem->m_etabPag)
            {
                ui->checkBox_2->setChecked(pItem->m_ascii.bInputIsShow);
                if(pItem->m_ascii.bInputIsShow)
                {
                    ui->checkBox_2->setChecked(pItem->m_ascii.bInputIsShow);
                    ui->m_offsetAddress_2->setEnabled(false);
                    ui->Offset_Address_EntryBtn_2->setEnabled(false);
                }
                else
                {
                    ui->m_offsetAddress_2->setEnabled(true);
                    ui->Offset_Address_EntryBtn_2->setEnabled(true);
                    ui->m_offsetAddress_2->setText(pItem->m_ascii.addrInputSame.sShowAddr);
                }
            }
        }
    }

    qDebug() << "333333333333\n";
    bInitFlag = true;
    qDebug() << "444444444444\n";
}

bool QValueBaseDlg::onDateInputState()
{
    if(ui->m_AllowInputckBox->isChecked())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void QValueBaseDlg::on_m_AllowInputckBox_clicked(bool checked)
{
    if(checked)
    {
        if(!(ui->m_dateInputBtn->isEnabled()))
        {
            ui->m_AllowInputgroupBox->setEnabled(true);
        }

        if(bInitFlag == false)//初始化完成之前
        {
            qDebug() << "1111111111111111\n";
            //if(pItem)
            {
                ui->checkBox_2->setEnabled(true);
                if(ui->checkBox_2->isChecked())
                {
                    ui->m_offsetAddress_2->setEnabled(false);
                    ui->Offset_Address_EntryBtn_2->setEnabled(false);
                }
                else
                {
                    ui->m_offsetAddress_2->setEnabled(true);
                    ui->Offset_Address_EntryBtn_2->setEnabled(true);
                }
            }
        }
        else
        {
            qDebug() << "222222222222\n";
            ui->checkBox_2->setChecked(true);
            ui->checkBox_2->setEnabled(true);
            ui->m_offsetAddress_2->setEnabled(false);
            ui->Offset_Address_EntryBtn_2->setEnabled(false);
            ui->m_offsetAddress_2->setText(ui->Monitor_Address->text());
        }

        if(!(ui->m_timeInputBtn->isEnabled()))
        {
            ui->m_UseMacroCkkgroupBox->setEnabled(false);
            ui->m_InputPromptckBox->setEnabled(false);
        }
        else
        {
            ui->m_InputPromptckBox->setEnabled(true);
            ui->m_UseMacroCkkgroupBox->setEnabled(true);
        }
    }
    else
    {
        ui->m_InputPromptckBox->setEnabled(false);
        ui->m_AllowInputgroupBox->setEnabled(false);
        ui->m_UseMacroCkkgroupBox->setEnabled(false);

        ui->checkBox_2->setChecked(false);
        ui->checkBox_2->setEnabled(false);
        ui->m_offsetAddress_2->setEnabled(false);
        ui->Offset_Address_EntryBtn_2->setEnabled(false);
    }
}

bool QValueBaseDlg::getAllowInputState()
{
    return ui->m_AllowInputckBox->isChecked();
}

void QValueBaseDlg::on_m_AllowInputckBox_stateChanged(int )
{
    if(!bInitFlag)
    {
        return;
    }
    if(!(ui->m_dateInputBtn->isEnabled()))
    {
        emit onTabWightSwitch(DATAINPUTSHOW);
    }
    else if(!(ui->m_asciiInputBtn->isEnabled()))
    {
        emit onTabWightSwitch(ASCIIINPUTSHOW);
    }
    else if(!(ui->m_timeInputBtn->isEnabled()))
    {
        emit onTabWightSwitch(DATETIMEINPUT);
    }
}

bool QValueBaseDlg::isScaleEnable()
{
    return ui->m_scalSetckBox->isChecked();
}
void QValueBaseDlg::on_Monitor_Address_EntryBtn_clicked()
{
    QString addrStr = ui->Monitor_Address->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->Monitor_Address->setText(Monitor_Address_Keyboard.sShowAddr);
    }
}
/**************************************/
/*选中数据类型为浮点数时，允许设置四舍五入*/
/**************************************/
void QValueBaseDlg::on_m_DataTypefontCmbBox_currentIndexChanged(int index)
{
    if(!bInitFlag)
    {
        return;
    }
    if(8 == index)
    {
        ui->m_roundckBox->setEnabled(true);
    }
    else
    {
        ui->m_roundckBox->setEnabled(false);
    }
    double nMax = 0;
    double nMin = 0;
    int length = 0;
    int type = 1;
    int base = 10;//10进制数
    bool bEnableDecimal = true;
    switch(index)
    {
    case 0://16位整数
        nMin = -32768;
        nMax = 32767;
        length = 5;
        break;
    case 1://16位正整数
        nMin = 0;
        nMax = 65535;
        length = 5;
        break;
    case 2://16位BCD码
        nMin = 0;
        nMax = 9999;
        length = 4;
        break;
    case 3://16位8进制数
        nMin = 0;
        nMax = 177777;
        length = 6;
        base = 8;
        bEnableDecimal = false;
        break;
    case 4://16位16进制数
        nMin = 0;
        nMax = 65535;
        length = 4;
        base = 16;
        bEnableDecimal = false;
        break;
    case 5://32位整数
        nMin = -2147483648L;
        nMax = 2147483647L;
        length = 10;
        break;
    case 6://32位正整数
        nMin = 0;
        nMax = 4294967295UL;
        length = 10;
        break;
    case 7://32位BCD码
        nMin = 0;
        nMax = 99999999L;
        length = 8;
        break;
    case 8://32位浮点数
        nMin = -2147483648L;
        nMax = 2147483647L;
        type = 0;
        length = 10;
        break;
    case 9://32位8进制数
        nMin = 0;
        nMax = 2147483647L;
        length = 11;
        base = 8;
        bEnableDecimal = false;
        break;
    case 10://32位16进制数
        nMin = 0;
        nMax = 2147483647L;
        length = 8;
        base = 16;
        bEnableDecimal = false;
        break;
    default:
        return;
    }
    if(nMin > 0) nMin = -1*nMin;
    emit setRange(nMax, nMin, type,base);
    if(!(ui->m_dateInputBtn->isEnabled()))
    {
       emit setDataLength(1 , length,bInitFlag, bEnableDecimal);//数值输入
    }
    else
    {
        emit setDataLength(0 , 128,bInitFlag, bEnableDecimal);
    }
    setdataRange(nMax,nMin,type,base);
}

void QValueBaseDlg::on_m_DateckBox_clicked(bool checked)
{
    if(!checked)
    {
        if((false == (ui->m_WeekckBox->isChecked()))
            && (false == (ui->m_TimeckBox->isChecked())))
        {
            QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("不能隐藏所有时间和星期"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("确定"));
            box.exec();
            ui->m_DateckBox->setChecked(true);
            return;
        }
    }
    onSetPreview();
}

void QValueBaseDlg::on_m_WeekckBox_clicked(bool checked)
{
    if(!checked)
    {
        if((false == (ui->m_DateckBox->isChecked()))
            && (false == (ui->m_TimeckBox->isChecked())))
        {
            QMessageBox box(QMessageBox::Information,tr("日期/时间显示"),tr("不能隐藏所有时间和星期"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("确定"));
            box.exec();
            ui->m_WeekckBox->setChecked(true);
            return;
        }
    }
    onSetPreview();
}

void QValueBaseDlg::on_m_TimeckBox_clicked(bool checked)
{
    if(!checked)
    {
        if((false == (ui->m_DateckBox->isChecked()))
            && (false == (ui->m_WeekckBox->isChecked())))
        {
            QMessageBox box(QMessageBox::Information,tr("日期/时间显示"),tr("不能隐藏所有时间和星期"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("确定"));
            box.exec();
            ui->m_TimeckBox->setChecked(true);
            return;
        }
    }
    onSetPreview();
}
//设置日期时间格式的预览字符串
void QValueBaseDlg::onSetPreview()
{
    QString sTimeFormat = "";
    if(ui->m_DateckBox->isChecked())
    {
        sTimeFormat = sTimeFormat + ui->m_DatecbBox->currentText();
    }

    if(ui->m_WeekckBox->isChecked())
    {
        if(ui->m_DateckBox->isChecked())
        {
            sTimeFormat = sTimeFormat + " ";
        }
        sTimeFormat = sTimeFormat + "(Mon)";
    }
    if(ui->m_TimeckBox->isChecked())
    {
        sTimeFormat = sTimeFormat + " ";
        sTimeFormat = sTimeFormat + ui->m_TimecbBox->currentText();
    }
    ui->m_ShowlineEdit->setText(sTimeFormat);
    if(bInitFlag)
    {
        emit onDrawSence("Text");
    }
}

void QValueBaseDlg::on_m_DatecbBox_currentIndexChanged(QString )
{
    onSetPreview();
}

void QValueBaseDlg::on_m_TimecbBox_currentIndexChanged(QString )
{
    onSetPreview();
}

QString QValueBaseDlg::onGetpreText()
{
    return ui->m_ShowlineEdit->text();
}

void QValueBaseDlg::on_m_fontCbBox_currentIndexChanged(int index)
{
    if(bInitFlag)
    {
        emit onDrawSence("Font");
    }
}

QString QValueBaseDlg::onGetFontType()
{
    return ui->m_fontCbBox->currentText();
}

bool QValueBaseDlg::onDataGenSave(DataInfo &data_st)
{
    if(ui->check_expression->isChecked())//表达式
    {
        if(pwnd->CheckString(Monitor_Address_Keyboard,m_outExp.var1.sShowAddr,1) != ADDR_CORRECT)
        {
            QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr("变量地址有误"),
                            0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            msg.addButton(tr("确定"),QMessageBox::AcceptRole);
            msg.exec();
            ui->edit_expression->setFocus();
            return false;
        }
    }
    else
    {
        if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("监视地址"),ui->Monitor_Address,1))
        {
            ui->Monitor_Address->setFocus();
            return false;
        }
    }

    data_st.addr = Monitor_Address_Keyboard;

    if(ui->checkBox->isChecked())//使用偏移地址
    {
        data_st.bOffset = true;
        if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("偏移地址"),ui->m_offsetAddress,1))
        {
            ui->m_offsetAddress->setFocus();
            return false;
        }
        data_st.addrOffset = Monitor_Address_Keyboard;
    }
    else
    {
        data_st.bOffset = false;
    }

    //if(data_st.bIsInput)
    {

    }

    if(ui->m_AllowInputckBox->isChecked())
    {
        if(!pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("输入地址"),ui->m_offsetAddress_2,1))
        {
            ui->m_offsetAddress_2->setFocus();
            return false;
        }
        data_st.addrInputSame = Monitor_Address_Keyboard;

        data_st.bInputSign = ui->m_InputPromptckBox->isChecked();
        data_st.eInputAreaType = ui->m_LimitSourcecbBox->currentIndex();
        if(1 == ui->m_LimitSourcecbBox->currentIndex())
        {
            if(! pwnd->IsAddressCheckRight(SMax_Address_Keyboard,tr("输入最大值地址"),ui->m_MaxLimitlineEdit,1))
            {
                ui->m_MaxLimitlineEdit->setFocus();
                return false;
            }
            data_st.addrInputMax = SMax_Address_Keyboard;

            if(! pwnd->IsAddressCheckRight(SMin_Address_Keyboard,tr("输入最小值地址"),ui->m_MinLimitlineEdit,1))
            {
                ui->m_MinLimitlineEdit->setFocus();
                return false;
            }
            data_st.addrInputMin = SMin_Address_Keyboard;
            data_st.sInputMax = ui->m_MaxLimitlineEdit->text();
            data_st.sInputMin = ui->m_MinLimitlineEdit->text();
        }
        else
        {
            data_st.sInputMax = ui->m_MaxLimitspBox->text();
            data_st.sInputMin = ui->m_MinLimitspBox->text();
        }
    }
    if(ui->m_scalSetckBox->isChecked() && 1 == pScaleWidget->ui->m_SourcecbBox->currentIndex())
    {
        if(! pwnd->IsAddressCheckRight(SMax_Address_Keyboard,tr("源最大值地址"),pScaleWidget->ui->m_SMaxlineEdit,1))
        {
            pScaleWidget->ui->m_SMaxlineEdit->setFocus();
            return false;
        }
        data_st.addrSourceMax = SMax_Address_Keyboard;

        if(! pwnd->IsAddressCheckRight(SMin_Address_Keyboard,tr("源最小值地址"),pScaleWidget->ui->m_SMinlineEdit,1))
        {
            pScaleWidget->ui->m_SMinlineEdit->setFocus();
            return false;
        }
        data_st.addrSourceMin = SMin_Address_Keyboard;
    }

    if(ui->m_scalSetckBox->isChecked() && 1 == pScaleWidget->ui->m_ShowcbBox->currentIndex())
    {
        if(! pwnd->IsAddressCheckRight(vMax_Address_Keyboard,tr("显示最大值地址"),pScaleWidget->ui->m_ShowMaxlineEdit,1))
        {
            pScaleWidget->ui->m_ShowMaxlineEdit->setFocus();
            return false;
        }
        data_st.addrShowMax = vMax_Address_Keyboard;

        if(! pwnd->IsAddressCheckRight(vMin_Address_Keyboard,tr("显示最小值地址"),pScaleWidget->ui->m_ShowMinlineEdit,1))
        {
            pScaleWidget->ui->m_ShowMinlineEdit->setFocus();
            return false;
        }
        data_st.addrShowMin = vMin_Address_Keyboard;
    }

    data_st.nAddress = ui->Monitor_Address->text();         //监控字地址
    data_st.bIsInput = ui->m_AllowInputckBox->isChecked();  //允许输入
    data_st.bIsScale = ui->m_scalSetckBox->isChecked();     //缩放设置
    data_st.eNumberType = ui->m_DataTypefontCmbBox->currentIndex(); //数据类型
    data_st.nByteLength = pScaleWidget->ui->m_SourcecbBox->currentIndex();        //源范围:指定源范围
    if(0 == data_st.nByteLength)
    {
        data_st.sSourceMax = pScaleWidget->ui->m_SMaxspBox->text();                   //源范围:最大
        data_st.sSourceMin = pScaleWidget->ui->m_SMinspBox->text();                   //源范围:最小
    }
    else
    {
        data_st.sSourceMax = pScaleWidget->ui->m_SMaxlineEdit->text();                   //源范围:最大
        data_st.sSourceMin = pScaleWidget->ui->m_SMinlineEdit->text();                   //源范围:最小
    }
    data_st.sShow = pScaleWidget->ui->m_ShowcbBox->currentIndex();                //显示范围:指定显示范围
    if(0 == data_st.sShow)
    {
        data_st.sShowMax = pScaleWidget->ui->m_ShowMaxspBox->text();                  //显示范围:最大
        data_st.sShowMin = pScaleWidget->ui->m_ShowMinspBox->text();                  //显示范围:最小
    }
    else
    {
        data_st.sShowMax = pScaleWidget->ui->m_ShowMaxlineEdit->text();                  //显示范围:最大
        data_st.sShowMin = pScaleWidget->ui->m_ShowMinlineEdit->text();                  //显示范围:最小
    }
    data_st.bRound = ui->m_roundckBox->isChecked();             //显示范围:四舍五入
    if(!(ui->m_dateInputBtn->isEnabled()))
    {
       data_st.etabPag = DATAINPUTSHOW;//数值输入
    }
    else if(!(ui->m_asciiInputBtn->isEnabled()))
    {
        data_st.etabPag = ASCIIINPUTSHOW;//ascii输入
    }
    else if(!(ui->m_timeInputBtn->isEnabled()))
    {
        data_st.etabPag = DATETIMEINPUT;//日期时间显示
    }

    data_st.bInputIsShow = ui->checkBox_2->isChecked();
    data_st.bUseMacro = ui->m_UseMacroCkkgroupBox->isChecked();
    data_st.macroName = ui->m_MacroCmBox->currentText();
    data_st.functionName = "MACRO_MAIN";
    data_st.bOutExpression = ui->check_expression->isChecked();
    if(data_st.bOutExpression)
    {
        data_st.m_inputExp = m_inputExp;
        data_st.m_outputExp = m_outExp;
    }
    return true;
}

bool QValueBaseDlg::onAsciiGenSave(ASCIIINFO &ascii_st)  //保存ascii显示信息
{
    if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("写入地址"),ui->Monitor_Address,1))
    {
        ui->Monitor_Address->setFocus();
        return false;
    }

    ascii_st.addr = Monitor_Address_Keyboard;

    if(ui->checkBox->isChecked())//使用偏移地址
    {
        ascii_st.bOffset = true;
        if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("偏移地址"),ui->m_offsetAddress,1))
        {
            ui->m_offsetAddress->setFocus();
            return false;
        }
        ascii_st.addrOffset = Monitor_Address_Keyboard;
    }
    else
    {
        ascii_st.bOffset = false;
    }

    //if(ascii_st.bIsinput)
    {

    }

    ascii_st.sAddress = ui->Monitor_Address->text();                //监控字地址
    ascii_st.bIsinput = ui->m_AllowInputckBox->isChecked();         //允许输入
    if(ascii_st.bIsinput)
    {
        if(!pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("输入地址"),ui->m_offsetAddress_2,1))
        {
            ui->m_offsetAddress_2->setFocus();
            return false;
        }
        ascii_st.addrInputSame = Monitor_Address_Keyboard;
        ascii_st.bInputSign = ui->m_InputPromptckBox->isChecked();
    }
    ascii_st.eNumberType = ui->m_DataTypefontCmbBox->currentIndex(); //数据类型
    if(!(ui->m_dateInputBtn->isEnabled()))
    {
       ascii_st.etabPag = DATAINPUTSHOW;//数值输入
    }
    else if(!(ui->m_asciiInputBtn->isEnabled()))
    {
        ascii_st.etabPag = ASCIIINPUTSHOW;//ascii输入
    }
    else if(!(ui->m_timeInputBtn->isEnabled()))
    {
        ascii_st.etabPag = DATETIMEINPUT;//日期时间显示
    }

    ascii_st.nCode = 0;
    if(ui->m_secretCkBox->isChecked())
    {
        ascii_st.nCode = (ascii_st.nCode)|1;
    }
    if(ui->m_unicodeCkBox->isChecked())
    {
        ascii_st.nCode = (ascii_st.nCode)|2;
    }
    if(ui->m_HtoLCkBox->isChecked())
    {
        ascii_st.nCode = (ascii_st.nCode)|8;
    }
    if(ui->m_showHtoLCkBox->isChecked())
    {
        ascii_st.nCode = (ascii_st.nCode)|16;
    }

    ascii_st.bInputIsShow = ui->checkBox_2->isChecked();

    ascii_st.bUseMacro = ui->m_UseMacroCkkgroupBox->isChecked();
    ascii_st.macroName = ui->m_MacroCmBox->currentText();
    ascii_st.functionName = "MACRO_MAIN";
    return true;
}

bool QValueBaseDlg::onTimeGenSave(TIMEINFO &time_st)
{
    /*if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("写入地址"),ui->Monitor_Address,1))
    {
        ui->Monitor_Address->setFocus();
        return false;
    }

    time_st.addr = Monitor_Address_Keyboard;*/

    time_st.bDateMark = ui->m_DateckBox->isChecked();//日期选中状态
    time_st.bWeekMark = ui->m_WeekckBox->isChecked();//星期选中状态
    time_st.bTimeMark = ui->m_TimeckBox->isChecked();//时间选中状态
    time_st.eShowDate = ui->m_DatecbBox->currentIndex();//日期index
    time_st.eShowTime = ui->m_TimecbBox->currentIndex();//时间index
    time_st.nPreView = ui->m_ShowlineEdit->text();//预览文本
    time_st.nFontStyle = ui->m_fontCbBox->currentIndex();//字体类型
    time_st.sFontType = ui->m_fontCbBox->currentText();
    time_st.nFontSize = ui->m_FontSizecbBox->currentIndex();//字体大小
    //time_st.eFontCss = ui->m_FonttypecbBox->currentIndex();//文本属性
    if(ui->m_OrdinaryckBox->isChecked())//文本属性
    {
        time_st.eFontCss = 0;
    }
    else
    {
        time_st.eFontCss = 0;
        short int nflag = 0;
        if(ui->m_BoldckBox->isChecked())
        {
            nflag = 1;
            time_st.eFontCss = (time_st.eFontCss)|nflag;
        }
        if(ui->m_ItalicckBox->isChecked())
        {
            nflag = 2;
            time_st.eFontCss = (time_st.eFontCss)|nflag;
        }
        if(ui->m_UnderlineckBox->isChecked())
        {
            nflag = 8;
            time_st.eFontCss = (time_st.eFontCss)|nflag;
        }
    }
    if(!(ui->m_dateInputBtn->isEnabled()))
    {
       time_st.etabPag = DATAINPUTSHOW;//数值输入
    }
    else if(!(ui->m_asciiInputBtn->isEnabled()))
    {
        time_st.etabPag = ASCIIINPUTSHOW;//ascii输入
    }
    else if(!(ui->m_timeInputBtn->isEnabled()))
    {
        time_st.etabPag = DATETIMEINPUT;//日期时间显示
    }
    time_st.nLanguageTypeId = ui->m_LanguagecbBox->currentIndex();
    return true;
}

void QValueBaseDlg::on_m_SourcecbBox_currentIndexChanged(int index)
{
    if(0 == index)
    {
        pScaleWidget->ui->m_SMaxlineEdit->hide();
        pScaleWidget->ui->m_SMinlineEdit->hide();
        pScaleWidget->ui->m_sMaxAddress_EntryBtn->hide();
        pScaleWidget->ui->m_sMinAddress_EntryBtn->hide();
        pScaleWidget->ui->m_SMaxspBox->show();
        pScaleWidget->ui->m_SMinspBox->show();
    }
    else
    {
        pScaleWidget->ui->m_SMaxlineEdit->show();
        pScaleWidget->ui->m_SMinlineEdit->show();
        pScaleWidget->ui->m_sMaxAddress_EntryBtn->show();
        pScaleWidget->ui->m_sMinAddress_EntryBtn->show();
        pScaleWidget->ui->m_SMaxspBox->hide();
        pScaleWidget->ui->m_SMinspBox->hide();
    }
}

void QValueBaseDlg::on_m_ShowcbBox_currentIndexChanged(int index)
{
    if(0 == index)
    {
        pScaleWidget->ui->m_ShowMaxlineEdit->hide();
        pScaleWidget->ui->m_ShowMinlineEdit->hide();
        pScaleWidget->ui->m_showMaxAddress_EntryBtn->hide();
        pScaleWidget->ui->m_showMinAddress_EntryBtn->hide();
        pScaleWidget->ui->m_ShowMaxspBox->show();
        pScaleWidget->ui->m_ShowMinspBox->show();
    }
    else
    {
        pScaleWidget->ui->m_ShowMaxlineEdit->show();
        pScaleWidget->ui->m_ShowMinlineEdit->show();
        pScaleWidget->ui->m_showMaxAddress_EntryBtn->show();
        pScaleWidget->ui->m_showMinAddress_EntryBtn->show();
        pScaleWidget->ui->m_ShowMaxspBox->hide();
        pScaleWidget->ui->m_ShowMinspBox->hide();
    }
}

void QValueBaseDlg::on_m_sMaxAddress_EntryBtn_clicked()
{
    QString addrStr = pScaleWidget->ui->m_SMaxlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(SMax_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        pScaleWidget->ui->m_SMaxlineEdit->setText(SMax_Address_Keyboard.sShowAddr);
    }
}

void QValueBaseDlg::on_m_sMinAddress_EntryBtn_clicked()
{
    QString addrStr = pScaleWidget->ui->m_SMinlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(SMin_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        pScaleWidget->ui->m_SMinlineEdit->setText(SMin_Address_Keyboard.sShowAddr);
    }
}

void QValueBaseDlg::on_m_showMaxAddress_EntryBtn_clicked()
{
    QString addrStr = pScaleWidget->ui->m_ShowMaxlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(vMax_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        pScaleWidget->ui->m_ShowMaxlineEdit->setText(vMax_Address_Keyboard.sShowAddr);
    }
}

void QValueBaseDlg::on_m_showMinAddress_EntryBtn_clicked()
{
    QString addrStr = pScaleWidget->ui->m_ShowMinlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(vMin_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        pScaleWidget->ui->m_ShowMinlineEdit->setText(vMin_Address_Keyboard.sShowAddr);
    }
}
int QValueBaseDlg::onGetFontSize()
{
    int nFontSize = ui->m_FontSizecbBox->currentText().toInt();
    return nFontSize;
}

void QValueBaseDlg::on_m_FontSizecbBox_currentIndexChanged(int index)
{
    if(bInitFlag)
    {
        emit onDrawSence("FontSize");
    }
}

/***************************************************/
//input: index 代表需要获取的属性状态 0：无效果 1：粗体 2：斜体 3：下划线
/***************************************************/
bool QValueBaseDlg::onGetFontStyl(int index)//获取字体属性 粗体 斜体 下划线
{
    bool bchecked;
    switch(index)
    {
    case 0:
        bchecked = ui->m_OrdinaryckBox->isChecked();
        break;
    case 1:
        bchecked = ui->m_BoldckBox->isChecked();
        break;
    case 2:
        bchecked = ui->m_ItalicckBox->isChecked();
        break;
    case 3:
        bchecked = ui->m_UnderlineckBox->isChecked();
        break;
    default:
        bchecked = false;
        break;
    }
    return bchecked;
}

void QValueBaseDlg::on_m_OrdinaryckBox_clicked(bool checked)
{
    if(checked)
    {
        ui->m_BoldckBox->setChecked(false);
        ui->m_UnderlineckBox->setChecked(false);
        ui->m_ItalicckBox->setChecked(false);
    }
    if(bInitFlag)
    {
        emit onDrawSence("FontType");
    }
}

void QValueBaseDlg::on_m_BoldckBox_clicked(bool checked)
{
    if(ui->m_OrdinaryckBox->isChecked())
    {
        ui->m_OrdinaryckBox->setChecked(false);
    }
    if(bInitFlag)
    {
        emit onDrawSence("FontType");
    }
}

void QValueBaseDlg::on_m_ItalicckBox_clicked(bool checked)
{
    if(ui->m_OrdinaryckBox->isChecked())
    {
        ui->m_OrdinaryckBox->setChecked(false);
    }
    if(bInitFlag)
    {
        emit onDrawSence("FontType");
    }
}

void QValueBaseDlg::on_m_UnderlineckBox_clicked(bool checked)
{
    if(ui->m_OrdinaryckBox->isChecked())
    {
        ui->m_OrdinaryckBox->setChecked(false);
    }
    if(bInitFlag)
    {
        emit onDrawSence("FontType");
    }
}

void QValueBaseDlg::setdataRange(double dMax, double dMin,int type,int base)
{
    DoubleValidator *aDoubleValidator = new DoubleValidator(this,base);
    aDoubleValidator->setNotation(QDoubleValidator::StandardNotation);
    if(0 == type)
    {
        aDoubleValidator->setRange(dMin,dMax,4);
    }
    else
    {
        aDoubleValidator->setRange(dMin,dMax);
    }

    pScaleWidget->ui->m_SMinspBox->setValidator(aDoubleValidator);
    pScaleWidget->ui->m_SMaxspBox->setValidator(aDoubleValidator);
    pScaleWidget->ui->m_ShowMinspBox->setValidator(aDoubleValidator);
    pScaleWidget->ui->m_ShowMaxspBox->setValidator(aDoubleValidator);
    ui->m_MaxLimitspBox->setValidator(aDoubleValidator);
    ui->m_MinLimitspBox->setValidator(aDoubleValidator);

    int nlength = 0;//获取设置的数据显示位数
    emit getDataLength(nlength);

//    if(ui->m_MaxLimitspBox->text().isEmpty())
//    {
//        QString sNamber = "";
//        for(int i = 0; i < nlength; i++)
//        {
//            sNamber += "9";
//        }
//        ui->m_MaxLimitspBox->setText(sNamber);
//    }
//    if(ui->m_MaxLimitspBox->text().toDouble() > dMax
//                || ui->m_MaxLimitspBox->text().toDouble() < dMin)
//    {
//        ui->m_MaxLimitspBox->setText(QString::number(dMax,'g',base));
//    }

    setDatadefault(nlength,true);

    if(10 == base)
    {
        ui->m_MinLimitspBox->setText(QString::number(0,'g',base));

        pScaleWidget->ui->m_SMinspBox->setText(QString::number(dMin,'g',base));

        pScaleWidget->ui->m_SMaxspBox->setText(QString::number(dMax,'g',base));

        pScaleWidget->ui->m_ShowMinspBox->setText(QString::number(dMin,'g',base));

        pScaleWidget->ui->m_ShowMaxspBox->setText(QString::number(dMax,'g',base));
    }
    else if(16 == base || 8 == base)
    {
        unsigned int nMin = dMin;
        unsigned int nMax = dMax;

        ui->m_MinLimitspBox->setText(QString::number(0,base));

        pScaleWidget->ui->m_SMinspBox->setText(QString::number(nMin,base));

        pScaleWidget->ui->m_SMaxspBox->setText(QString::number(nMax,base));

        pScaleWidget->ui->m_ShowMinspBox->setText(QString::number(nMin,base));

        pScaleWidget->ui->m_ShowMaxspBox->setText(QString::number(nMax,base));
    }
    else if( 4 == base)
    {

    }
}

void QValueBaseDlg::on_m_LimitSourcecbBox_currentIndexChanged(int index)
{
    if(0 == index)
    {
        ui->m_MaxLimitlineEdit->hide();
        ui->m_MinLimitlineEdit->hide();
        ui->m_MaxLimitAddress_EntryBtn->hide();
        ui->m_MinLimitAddress_EntryBtn->hide();
        ui->m_MaxLimitspBox->show();
        ui->m_MinLimitspBox->show();
    }
    else
    {
        ui->m_MaxLimitlineEdit->show();
        ui->m_MinLimitlineEdit->show();
        ui->m_MaxLimitAddress_EntryBtn->show();
        ui->m_MinLimitAddress_EntryBtn->show();
        ui->m_MaxLimitspBox->hide();
        ui->m_MinLimitspBox->hide();
    }
}

void QValueBaseDlg::on_m_MinLimitAddress_EntryBtn_clicked()
{
    QString addrStr = ui->m_MinLimitlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(SMin_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_MinLimitlineEdit->setText(SMin_Address_Keyboard.sShowAddr);
    }
}

void QValueBaseDlg::on_m_MaxLimitAddress_EntryBtn_clicked()
{
    QString addrStr = ui->m_MaxLimitlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(SMax_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_MaxLimitlineEdit->setText(SMax_Address_Keyboard.sShowAddr);
    }
}

void QValueBaseDlg::setDatadefault(int nLength,bool bUser)
{
    //设置默认值位数等于最大长度 begin
    int type = ui->m_DataTypefontCmbBox->currentIndex(); //数据类型下标
    const QValidator *pValidator = ui->m_MaxLimitspBox->validator();
    if(!pValidator)
    {
        return;
    }
    QValidator *pV = const_cast<QValidator*> (pValidator);
    DoubleValidator *pDoubleValidator = dynamic_cast<DoubleValidator*> (pV);
    if(!pDoubleValidator)
    {
        return;
    }

    int base = pDoubleValidator->nBase;
    double dMax = pDoubleValidator->top();

    QString sNumber;
    sNumber.clear();
    if(10 == base)
    {
        for(int i = 0; i < nLength; i++)
        {
            sNumber = sNumber + "9";
        }
    }
    else if(16 == base)
    {
        for(int i = 0; i < nLength; i++)
        {
            sNumber = sNumber + "F";
        }
    }
    else if(8 == base)
    {
        for(int i = 0; i < nLength; i++)
        {
            if(nLength == 11 && i == 0)//最长11位 "177777777777"
            {
                sNumber = sNumber + "1";
            }
            else
            {
                sNumber = sNumber + "7";
            }
        }
    }

    if(bUser)
    {
        if(10 == base)
        {
            if(sNumber.toDouble() > dMax)
            {
                ui->m_MaxLimitspBox->setText(QString::number(dMax,'g',10));
            }
            else
            {
                ui->m_MaxLimitspBox->setText(QString::number(sNumber.toDouble(),'g',10));
            }
        }
        else if(16 == base)
        {
            bool ok;
            unsigned int n = sNumber.toUInt(&ok,16);
            if(sNumber.toUInt(&ok,16) > dMax)
            {
                qlonglong nMax = dMax;
                ui->m_MaxLimitspBox->setText(QString::number(nMax,16));
            }
            else
            {
                ui->m_MaxLimitspBox->setText(sNumber);
            }
        }
        else if(8 == base)
        {
            bool ok;
            unsigned int n = sNumber.toUInt(&ok,8);
            if(sNumber.toUInt(&ok,8) > dMax)
            {
                qlonglong nMax = dMax;
                ui->m_MaxLimitspBox->setText(QString::number(nMax,8));
            }
            else
            {
                ui->m_MaxLimitspBox->setText(sNumber);
            }
        }

    }
    else
    {
        if(ui->m_MaxLimitspBox->text().length() > nLength)
        {
            if(10 == base)
            {
                ui->m_MaxLimitspBox->setText(QString::number(sNumber.toDouble(),'g',10));
            }
            else if(16 == base)
            {
                ui->m_MaxLimitspBox->setText(sNumber);
            }
            else if(8 == base)
            {
                ui->m_MaxLimitspBox->setText(sNumber);
            }
        }
    }
    //设置默认值位数等于最大长度 end
}

void QValueBaseDlg::on_btn_new_clicked()
{
    Macro lib;
    AddLib addWzrd(pwnd->macros,this);
    addWzrd.setWindowTitle(tr("添加脚本"));
    if(addWzrd.exec() == QDialog::Accepted)
    {
        lib.libName = addWzrd.libName;
        lib.type = true;
        lib.setCompipiled(false);
        lib.setCode(SCRIPT_HEADER);
        pwnd->macros.append(lib);
        MacroEdit *dlg = new MacroEdit(lib.libName,this);
        dlg->exec();
        pwnd->is_Save=false;
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
    }
    QString libname = ui->m_MacroCmBox->currentText();
    ui->m_MacroCmBox->clear();
    foreach(Macro lib,pwnd->macros) //初始化库名称
    {
        if (lib.type && lib.isCompiled())
        {
            ui->m_MacroCmBox->addItem(lib.libName);
        }
    }
    int index = ui->m_MacroCmBox->findText(libname);
    if(index >= 0)
    {
        ui->m_MacroCmBox->setCurrentIndex(index);
    }
}

void QValueBaseDlg::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->m_offsetAddress->setEnabled(true);
        ui->Offset_Address_EntryBtn->setEnabled(true);
    }
    else
    {
        ui->m_offsetAddress->setEnabled(false);
        ui->Offset_Address_EntryBtn->setEnabled(false);
    }
}

void QValueBaseDlg::on_Offset_Address_EntryBtn_clicked()
{
    QString addrStr = ui->m_offsetAddress->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_offsetAddress->setText(Monitor_Address_Keyboard.sShowAddr);
    }
}

void QValueBaseDlg::on_checkBox_2_clicked(bool checked)
{
    ui->m_offsetAddress_2->setEnabled(!checked);
    ui->Offset_Address_EntryBtn_2->setEnabled(!checked);
    if(checked)
    {
        ui->m_offsetAddress_2->setText(ui->Monitor_Address->text());
    }
}

void QValueBaseDlg::on_Monitor_Address_textChanged(QString str)
{
    if(ui->checkBox_2->isChecked())
    {
        ui->m_offsetAddress_2->setText(str);
    }
}

void QValueBaseDlg::on_Offset_Address_EntryBtn_2_clicked()
{
    QString addrStr = ui->m_offsetAddress_2->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_offsetAddress_2->setText(Monitor_Address_Keyboard.sShowAddr);
    }
}

bool QValueBaseDlg::IsCanInput()
{
    bool ret = ui->m_AllowInputckBox->isChecked();

    return ret;
}

void QValueBaseDlg::on_check_expression_clicked(bool checked)
{
    if(checked)
    {
        ui->edit_expression->show();
        ui->btn_expression->show();
        ui->edit_expression->setText(this->m_outExp.getExpString());
    }
    else
    {
        ui->edit_expression->hide();
        ui->btn_expression->hide();
    }

}

void QValueBaseDlg::on_btn_expression_clicked(bool checked)
{
    ExpressionDlg dlg(ui->m_DataTypefontCmbBox->currentIndex()+1,m_outExp);
    dlg.setWindowTitle(tr("编辑表达式"));
    if(dlg.exec() == QDialog::Accepted)
    {
        m_outExp = dlg.getExp();
        qDebug() << "m_outExp.getExpString()" <<m_outExp.getExpString();
        ui->edit_expression->setText(m_outExp.getExpString());
    }
}
