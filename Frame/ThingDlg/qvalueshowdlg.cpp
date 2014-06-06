#include "qvalueshowdlg.h"
#include "ui_qvalueshowdlg.h"
#include <QFontDatabase>
#include "Frame/addressinputdialog.h"

extern MainWindow *pwnd;
QValueShowDlg::QValueShowDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QValueShowDlg)
{
    ui->setupUi(this);
    ui->m_fontCbBox->addItems(QFontDatabase().families(QFontDatabase::Any));
    pwnd->InitFontSize(ui->m_fontSizecbBox);//初始化字体大小下拉列表框
    ui->m_fontSizecbBox->setCurrentIndex(9);
}

QValueShowDlg::~QValueShowDlg()
{
    delete ui;
}

void QValueShowDlg::Init(DataDisplayItem *pItem)
{
    bInitFlag = false;
    if(pItem)
    {
        if(DATAINPUTSHOW == pItem->m_etabPag)
        {
            int nIndex = ui->m_fontCbBox->findText(pItem->m_data.sFontType);
            if(nIndex >= 0)
            {
                ui->m_fontCbBox->setCurrentIndex(nIndex);
            }
            ui->m_fontSizecbBox->setCurrentIndex(pItem->m_data.nFontSize);
            //ui->m_textcbBox->setCurrentIndex(pItem->m_data.eFontCss);
            if(!(pItem->m_data.eFontCss&1) &&  !(pItem->m_data.eFontCss&2) && !(pItem->m_data.eFontCss&8))
            {
                ui->m_OrdinaryckBox->setChecked(true);
            }
            else
            {
                ui->m_OrdinaryckBox->setChecked(false);
                if((1&(pItem->m_data.eFontCss)))
                {
                    ui->m_BoldckBox->setChecked(true);
                }
                if((2&(pItem->m_data.eFontCss)))
                {
                    ui->m_ItalicckBox->setChecked(true);
                }
                if((8&(pItem->m_data.eFontCss)))
                {
                    ui->m_UnderlineckBox->setChecked(true);
                }
            }
            if((128&(pItem->m_data.eFontCss)))//0x0080 /1000 0000
            {
                ui->m_HideInputCKBox->setChecked(true);
            }

            ui->m_totalspBox->setValue(pItem->m_data.nAllbytelength);
            ui->m_sDecimalTypecbBox->setCurrentIndex(pItem->m_data.sDecimalType);
            ui->m_AddresslineEdit->setText(pItem->m_data.addrDicmal.sShowAddr);//小数位数地址
            ui->m_DecimalspBox->setValue(pItem->m_data.sDecimalLength);
            //ui->m_preLineEdit->setText(pItem->m_data.nPreView);        //预览显示字符串
        }
        else if(ASCIIINPUTSHOW == pItem->m_etabPag)
        {
            int nIndex = ui->m_fontCbBox->findText(pItem->m_ascii.sFontType);
            if(nIndex >= 0)
            {
                ui->m_fontCbBox->setCurrentIndex(nIndex);
            }     //字体类型
            ui->m_fontSizecbBox->setCurrentIndex(pItem->m_ascii.nFontsize);  //字体大小
            //ui->m_textcbBox->setCurrentIndex(pItem->m_ascii.eFontCss);       //文本属性
            if(0 == pItem->m_ascii.eFontCss)
            {
                ui->m_OrdinaryckBox->setChecked(true);
            }
            else
            {
                ui->m_OrdinaryckBox->setChecked(false);
                if((1&(pItem->m_ascii.eFontCss)))
                {
                    ui->m_BoldckBox->setChecked(true);
                }
                if((2&(pItem->m_ascii.eFontCss)))
                {
                    ui->m_ItalicckBox->setChecked(true);
                }
                if((8&(pItem->m_ascii.eFontCss)))
                {
                    ui->m_UnderlineckBox->setChecked(true);
                }
            }
            ui->m_totalspBox->setValue(pItem->m_ascii.nShowCharNumber);      //总位数
            //ui->m_codeFomatcmbBox->setCurrentIndex(pItem->m_ascii.nCode);//编码格式
        }
        int nTextAligent = pItem->GetTextAlign();
        {
            if(4 == nTextAligent)
            {
                ui->m_AligentCbBox->setCurrentIndex(1);
            }
            else if(6 == nTextAligent)
            {
                ui->m_AligentCbBox->setCurrentIndex(2);
            }
            else
            {
                ui->m_AligentCbBox->setCurrentIndex(0);
            }
        }
    }
    else
    {
        ui->m_totalspBox->setValue(5);
        ui->m_DecimalspBox->setValue(0);
        QString pText = "";
        for(int i = 0; i < ui->m_totalspBox->value(); i++)
        {
            pText = pText + "8";
        }
        //ui->m_preLineEdit->setText(pText);
        ui->m_OrdinaryckBox->setChecked(true);
        ui->m_AddresslineEdit->setEnabled(false);//小数地址
        ui->Monitor_Address_EntryBtn->setEnabled(false);

        int index = ui->m_fontCbBox->findText(tr("Droid Sans Fallback"));
        if(index >= 0)
        {
            ui->m_fontCbBox->setCurrentIndex(index);
        }
        else
        {
            ui->m_fontCbBox->setCurrentIndex(ui->m_fontCbBox->findText(tr("System")));

        }
    }
    bInitFlag = true;
}

int QValueShowDlg::onGetTotaldigit()
{
    return ui->m_totalspBox->value();
}

int QValueShowDlg::onGetDecimaldigit()
{
    return ui->m_DecimalspBox->value();
}

int QValueShowDlg::onGetFontSize()//获取字体大小
{
    int nfontsize = (ui->m_fontSizecbBox->currentText()).toInt();
    return nfontsize;
}
/***************************************************/
//input: index 代表需要获取的属性状态 0：无效果 1：粗体 2：斜体 3：下划线
/***************************************************/
bool QValueShowDlg::onGetFontType(int index)//获取字体属性 粗体 斜体 下划线
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

void QValueShowDlg::onTabWightSwitch(int eType)
{
    switch(eType)
    {
    case DATAINPUTSHOW:
        ui->m_HideInputCKBox->setEnabled(true);
        ui->m_sDecimalTypelabel->setEnabled(true);//显示小数位数指定
        ui->m_sDecimalTypecbBox->setEnabled(true);
        //ui->m_Decimallabel->show();//显示小数位数
        ui->m_totallabel->setText(tr("总显示位数"));
        if(0 == ui->m_sDecimalTypecbBox->currentIndex())
        {
            //ui->m_Decimallabel->setText(tr("小数位数"));
            ui->m_DecimalspBox->setEnabled(true);
            ui->m_AddresslineEdit->setEnabled(false);//小数地址
            ui->Monitor_Address_EntryBtn->setEnabled(false);
        }
        else
        {
            ui->m_DecimalspBox->setEnabled(false);
            //ui->m_Decimallabel->setText(tr("小数位数地址"));
            ui->m_AddresslineEdit->setEnabled(true);//小数地址
            ui->Monitor_Address_EntryBtn->setEnabled(true);
        }
        break;
    case ASCIIINPUTSHOW:
        ui->m_sDecimalTypelabel->setEnabled(false);//隐藏小数位数指定
        ui->m_HideInputCKBox->setEnabled(false);
        ui->m_sDecimalTypecbBox->setEnabled(false);
        //ui->m_Decimallabel->hide();//隐藏小数位数
        ui->m_DecimalspBox->setEnabled(false);
        ui->m_totallabel->setText(tr("显示字符数"));
        ui->m_AddresslineEdit->setEnabled(false);//小数地址
        ui->Monitor_Address_EntryBtn->setEnabled(false);
        break;
    case DATETIMEINPUT:
        break;
    default:
        return;
    }
}

void QValueShowDlg::on_m_totalspBox_valueChanged(int )
{
    if(bInitFlag)
    {
        QString pText = "";
        int nTotal = ui->m_totalspBox->value();
        int nDecimal = ui->m_DecimalspBox->value();
        for(int i = 0; i < nTotal; i++)
        {
            pText = pText + "8";
        }
        if(nDecimal > 0 && nDecimal < nTotal)
        {
            pText.insert(nTotal - nDecimal,'.');
        }
        //ui->m_preLineEdit->setText(pText);
        emit onDrawSence("Text");

        if(nTotal <= nDecimal)
        {
            ui->m_DecimalspBox->setValue(nTotal - 1);
        }
        setDatadefault(nTotal,true);
    }
}

void QValueShowDlg::on_m_DecimalspBox_valueChanged(int )
{
    if(bInitFlag)
    {
        QString pText = "";
        int nTotal = ui->m_totalspBox->value();
        int nDecimal = ui->m_DecimalspBox->value();
        for(int i = 0; i < nTotal; i++)
        {
            pText = pText + "8";
        }
        if(nDecimal >= 0 && nDecimal < nTotal)
        {
            if(nDecimal)
            {
                pText.insert(nTotal - nDecimal,'.');
            }
        }
        else
        {
            ui->m_DecimalspBox->setValue(nTotal - 1);
            return;
        }
        //ui->m_preLineEdit->setText(pText);
        emit onDrawSence("Text");
    }
}

void QValueShowDlg::on_m_OrdinaryckBox_clicked(bool checked)
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

void QValueShowDlg::on_m_BoldckBox_clicked(bool checked)
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

void QValueShowDlg::on_m_ItalicckBox_clicked(bool checked)
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

void QValueShowDlg::on_m_UnderlineckBox_clicked(bool checked)
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

void QValueShowDlg::on_m_LeftAlignBtn_clicked()
{
    if(bInitFlag)
    {
        emit onDrawSence("4");
    }
}

void QValueShowDlg::on_m_centerAlignBtn_clicked()
{
    if(bInitFlag)
    {
        emit onDrawSence("5");
    }
}

void QValueShowDlg::on_m_rightAlignBtn_clicked()
{
    if(bInitFlag)
    {
        emit onDrawSence("6");
    }
}

void QValueShowDlg::on_m_fontSizecbBox_currentIndexChanged(int index)
{
    if(bInitFlag)
    {
        emit onDrawSence("FontSize");
    }
}

void QValueShowDlg::on_m_textcbBox_currentIndexChanged(int index)
{
    if(bInitFlag)
    {
        emit onDrawSence("FontType");
    }
}
void QValueShowDlg::on_m_codeFomatcmbBox_currentIndexChanged(int index)
{

}

void QValueShowDlg::on_m_fontCbBox_currentIndexChanged(int index)
{
    if(bInitFlag)
    {
        emit onDrawSence("Font");
    }
}

QString QValueShowDlg::onGetFont(VALUESHOWTYPE type)
{
    return ui->m_fontCbBox->currentText();
}

bool QValueShowDlg::onDataGenSave(DataInfo &data_st)
{
    if(1 == ui->m_sDecimalTypecbBox->currentIndex())
    {
        if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("小数位数地址"),ui->m_AddresslineEdit,1))
        {
            ui->m_AddresslineEdit->setFocus();
            return false;
        }
    }
    data_st.addrDicmal = Monitor_Address_Keyboard;

    data_st.nFontType = ui->m_fontCbBox->currentIndex();      //字体类型
    data_st.sFontType = ui->m_fontCbBox->currentText();
    data_st.nFontSize = ui->m_fontSizecbBox->currentIndex();  //字体大小
    if(ui->m_OrdinaryckBox->isChecked())//文本属性
    {
        data_st.eFontCss = 0;
    }
    else
    {
        data_st.eFontCss = 0;
        short int nflag = 0;
        if(ui->m_BoldckBox->isChecked())
        {
            nflag = 1;
            data_st.eFontCss = (data_st.eFontCss)|nflag;
        }
        if(ui->m_ItalicckBox->isChecked())
        {
            nflag = 2;
            data_st.eFontCss = (data_st.eFontCss)|nflag;
        }
        if(ui->m_UnderlineckBox->isChecked())
        {
            nflag = 8;
            data_st.eFontCss = (data_st.eFontCss)|nflag;
        }
    }
    if(ui->m_HideInputCKBox->isChecked())
    {
        int nflag = 128;
        data_st.eFontCss = (data_st.eFontCss)|nflag;
    }
    //data_st.eFontCss = ui->m_textcbBox->currentIndex();       //文本属性
    data_st.nAllbytelength = ui->m_totalspBox->value();//总位数
    data_st.sDecimalType = ui->m_sDecimalTypecbBox->currentIndex();//小数指定位数 常量/地址
    data_st.sDecimalLength = ui->m_DecimalspBox->value();//小数位数
    data_st.sDecimalAddress = ui->m_AddresslineEdit->text();//小数位数地址
    //data_st.nPreView = ui->m_preLineEdit->text();        //预览显示字符串
    return true;
}

bool QValueShowDlg::onAsciiGenSave(ASCIIINFO &ascii_st)  //保存ascii显示信息
{

    //ascii_st.nCode = ui->m_codeFomatcmbBox->currentIndex();
    ascii_st.nFontStyle = ui->m_fontCbBox->currentIndex();      //字体类型
    ascii_st.sFontType = ui->m_fontCbBox->currentText();
    ascii_st.nFontsize = ui->m_fontSizecbBox->currentIndex();  //字体大小
    //ascii_st.eFontCss = ui->m_textcbBox->currentIndex();       //文本属性
    if(ui->m_OrdinaryckBox->isChecked())
    {
        ascii_st.eFontCss = 0;
    }
    else
    {
        ascii_st.eFontCss = 0;
        short int nflag = 0;
        if(ui->m_BoldckBox->isChecked())
        {
            nflag = 1;//粗体
            ascii_st.eFontCss = (ascii_st.eFontCss)|nflag;
        }
        if(ui->m_ItalicckBox->isChecked())
        {
            nflag = 2;//斜体
            ascii_st.eFontCss = (ascii_st.eFontCss)|nflag;
        }
        if(ui->m_UnderlineckBox->isChecked())
        {
            nflag = 8;//下划线
            ascii_st.eFontCss = (ascii_st.eFontCss)|nflag;
        }
    }
    ascii_st.nShowCharNumber = ui->m_totalspBox->value();//总位数
    return true;
}

void QValueShowDlg::on_m_sDecimalTypecbBox_currentIndexChanged(int index)
{
    if(0 == index)
    {
        ui->m_DecimalspBox->setEnabled(true);
        ui->m_AddresslineEdit->setEnabled(false);//小数地址
        ui->Monitor_Address_EntryBtn->setEnabled(false);
        //ui->m_Decimallabel->setText(tr("小数位数"));
    }
    else if(1 == index)
    {
        ui->m_DecimalspBox->setEnabled(false);
        ui->m_AddresslineEdit->setEnabled(true);//小数地址
        ui->Monitor_Address_EntryBtn->setEnabled(true);
        //ui->m_Decimallabel->setText(tr("小数位数地址"));
    }
}

void QValueShowDlg::on_Monitor_Address_EntryBtn_clicked()
{
    QString addrStr = ui->m_AddresslineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_AddresslineEdit->setText(Monitor_Address_Keyboard.sShowAddr);
    }
}

void QValueShowDlg::setDataLength(int minlength, int naxlength,bool bInitFlag, bool bEnableDecimal)
{
    int nValue = ui->m_totalspBox->value();
    ui->m_totalspBox->setRange(minlength,naxlength);
    if(128 != naxlength)
    {
        if(false == bInitFlag)//初始化不改变当前值
        {
            if(nValue < minlength || nValue > naxlength)//当前数据不在数据类型范围内
                ui->m_totalspBox->setValue(naxlength);
            else
            {
                ui->m_totalspBox->setValue(nValue);
            }
        }
        else
        {
            if(nValue < minlength || nValue > naxlength)
                ui->m_totalspBox->setValue(naxlength);
        }
    }
    if(bEnableDecimal)
    {
        ui->m_sDecimalTypecbBox->setEnabled(true);
        if(ui->m_sDecimalTypecbBox->currentIndex() == 0)
        {
            ui->m_DecimalspBox->setEnabled(true);
        }
        else
        {
            ui->m_AddresslineEdit->setEnabled(true);
            ui->Monitor_Address_EntryBtn->setEnabled(true);
        }
    }
    else
    {
        ui->m_sDecimalTypecbBox->setEnabled(false);
        ui->m_sDecimalTypecbBox->setCurrentIndex(0);
        ui->m_DecimalspBox->setEnabled(false);
        ui->m_DecimalspBox->setValue(0);
    }
}



void QValueShowDlg::on_m_AligentCbBox_currentIndexChanged(int index)
{
    if(!bInitFlag)
    {
        return;
    }
    if(0 == index)
    {
        emit onDrawSence("5");
    }
    else if(1 == index)
    {
        emit onDrawSence("4");
    }
    else if(2 == index)
    {
        emit onDrawSence("6");
    }
}

void QValueShowDlg::getDataLength(int &nLength)
{
    nLength = ui->m_totalspBox->value();
}
