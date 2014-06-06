#include "qvaluedateinputdlg.h"
#include "ui_qvaluedateinputdlg.h"

extern MainWindow *pwnd;

QValueDateInputDlg::QValueDateInputDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QValueDateInputDlg)
{
    ui->setupUi(this);
    ui->m_keyspBox->clear();
    int totalNum = pwnd->pSceneSheet.size();
    bool bfalg = false;
    int nWidth = 0;
    int nHight = 0;
    for(int i = 0; i< totalNum; i++)
    {
        if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 2)
        {
            if(!bfalg)
            {
                nWidth = pwnd->pSceneSheet[i]->width();
                nHight = pwnd->pSceneSheet[i]->height();
            }
            bfalg = true;
            ui->m_keyspBox->addItem(pwnd->pSceneSheet[i]->sNewScreenName);
        }
    }
    if(!bfalg)
    {
        ui->m_KeygroupBox->setEnabled(false);
        ui->m_keyspBox->setEnabled(false);
        ui->m_PouupckBox->setChecked(false);
        ui->m_PouupckBox->setEnabled(false);
    }
    else
    {
        ui->m_PouupckBox->setChecked(true);
        ui->m_PouupckBox->setEnabled(true);
        on_m_PouupckBox_clicked(true);
    }
    int nxValue = pwnd->m_pSamSysParame->m_projectProp.nSceneWidth - nWidth;
    int nyValue = pwnd->m_pSamSysParame->m_projectProp.nSceneHeight - nHight ;

    ui->m_xKeyspinBox->setRange(0,nxValue);
    ui->m_yKeyspinBox->setRange(0,nyValue);
    ui->m_xKeyspinBox->setValue(pwnd->m_pSamSysParame->m_projectProp.nSceneWidth/2 - nWidth/2);
    ui->m_yKeyspinBox->setValue(pwnd->m_pSamSysParame->m_projectProp.nSceneHeight/2 - nHight/2);
}

QValueDateInputDlg::~QValueDateInputDlg()
{
    delete ui;
}

void QValueDateInputDlg::Init(DataDisplayItem *pItem)
{
    bInitFlag = false;
    if(pItem)
    {
        if(DATAINPUTSHOW == pItem->m_etabPag)
        {
            if(Touch == pItem->m_data.eInputTypeId)
            {
                on_m_touchradioBtn_clicked();
            }
            else
            {
                ui->m_AutoChangeBitckBox->setChecked(pItem->m_data.bAutoChangeBit);
                on_m_BitradioBtn_clicked();
            }
            ui->m_PouupckBox->setChecked(pItem->m_data.nKeyMark);

            int index = ui->m_keyspBox->findText(pItem->m_data.sKeyname);
            if(index >= 0 )
            {
                ui->m_keyspBox->setCurrentIndex(index);
                on_m_keyspBox_currentIndexChanged(index);
            }
            else
            {
                ui->m_keyspBox->setCurrentIndex(0);
                on_m_keyspBox_currentIndexChanged(0);
            }

            //ui->m_keyspBox->setCurrentIndex(pItem->m_data.nKeyId);
            ui->m_AllowInputBitlineEdit->setText(pItem->m_data.addrBit.sShowAddr);
            ui->m_xKeyspinBox->setValue(pItem->m_data.nBoardX);
            ui->m_yKeyspinBox->setValue(pItem->m_data.nBoardY);
        }
        else if(ASCIIINPUTSHOW == pItem->m_etabPag)
        {
            if(Touch == pItem->m_ascii.eInputTypeId)
            {
                on_m_touchradioBtn_clicked();
            }
            else
            {
                ui->m_AutoChangeBitckBox->setChecked(pItem->m_ascii.bAutoChangeBit);
                on_m_BitradioBtn_clicked();
            }
            ui->m_PouupckBox->setChecked(pItem->m_ascii.nKeyMark);
            int index = ui->m_keyspBox->findText(pItem->m_ascii.sKeyname);
            if(index >= 0 )
            {
                ui->m_keyspBox->setCurrentIndex(index);
                on_m_keyspBox_currentIndexChanged(index);
            }
            else
            {
                ui->m_keyspBox->setCurrentIndex(0);
                on_m_keyspBox_currentIndexChanged(0);
            }
            ui->m_AllowInputBitlineEdit->setText(pItem->m_ascii.addrBit.sShowAddr);
            ui->m_xKeyspinBox->setValue(pItem->m_ascii.nBoardX);
            ui->m_yKeyspinBox->setValue(pItem->m_ascii.nBoardY);
        }
    }
    else
    {
        on_m_touchradioBtn_clicked();
    }
    if(!ui->m_PouupckBox->isEnabled())
    {
        on_m_PouupckBox_clicked(false);
    }
    else
    {
        on_m_PouupckBox_clicked(ui->m_PouupckBox->isChecked());
    }

    bInitFlag = true;
}

bool QValueDateInputDlg::onDataGenSave(DataInfo &data_st)//保存数值显示信息
{
    data_st.sAddrBit = ui->m_AllowInputBitlineEdit->text();
    if(ui->m_touchradioBtn->isChecked())
    {
        data_st.eInputTypeId = Touch;
    }
    else
    {
        if(data_st.bIsInput)
        {
            if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("位地址"),ui->m_AllowInputBitlineEdit,0))
            {
                ui->m_AllowInputBitlineEdit->setFocus();
                return false;
            }
            data_st.addrBit = Monitor_Address_Keyboard;
        }
        data_st.eInputTypeId = Bit;
        data_st.bAutoChangeBit = ui->m_AutoChangeBitckBox->isChecked();
    }
    data_st.nKeyMark = ui->m_PouupckBox->isChecked();
    if(data_st.nKeyMark)
    {
        data_st.nKeyId = ui->m_keyspBox->currentIndex();
        data_st.sKeyname = ui->m_keyspBox->currentText();
    }
    else
    {
        data_st.nKeyId = 0;
        data_st.sKeyname = "";
    }
    data_st.nBoardX = ui->m_xKeyspinBox->value();
    data_st.nBoardY = ui->m_yKeyspinBox->value();
    data_st.sAddrBit = ui->m_AllowInputBitlineEdit->text();
    return true;
}

bool QValueDateInputDlg::onAsciiGenSave(ASCIIINFO &ascii_st)  //保存ascii显示信息
{
    if(ui->m_touchradioBtn->isChecked())
    {
        ascii_st.eInputTypeId = Touch;
    }
    else
    {
        if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("位地址"),ui->m_AllowInputBitlineEdit,0))
        {
            ui->m_AllowInputBitlineEdit->setFocus();
            return false;
        }
        ascii_st.addrBit = Monitor_Address_Keyboard;
        ascii_st.eInputTypeId = Bit;
        ascii_st.bAutoChangeBit = ui->m_AutoChangeBitckBox->isChecked();
    }
    ascii_st.nKeyMark = ui->m_PouupckBox->isChecked();
    if(ascii_st.nKeyMark)
    {
        ascii_st.nKeyId = ui->m_keyspBox->currentIndex();
        ascii_st.sKeyname = ui->m_keyspBox->currentText();
    }
    else
    {
        ascii_st.nKeyId = 0;
        ascii_st.sKeyname = "";
    }
    ascii_st.sAddrBit = ui->m_AllowInputBitlineEdit->text();
    ascii_st.nBoardX = ui->m_xKeyspinBox->value();
    ascii_st.nBoardY = ui->m_yKeyspinBox->value();
    return true;
}

void QValueDateInputDlg::on_m_touchradioBtn_clicked()
{
    ui->m_touchradioBtn->setChecked(true);
    ui->m_BitradioBtn->setChecked(false);
    //ui->m_PouupckBox->show();
    //ui->m_keyspBox->show();

    ui->m_AutoChangeBitckBox->setEnabled(false);
    ui->m_allowinputbitlabel->setEnabled(false);
    ui->m_AllowInputBitlineEdit->setEnabled(false);
    ui->Monitor_Address_EntryBtn->setEnabled(false);
}

void QValueDateInputDlg::on_m_BitradioBtn_clicked()
{
    ui->m_touchradioBtn->setChecked(false);
    ui->m_BitradioBtn->setChecked(true);

    //ui->m_PouupckBox->hide();
    //ui->m_keyspBox->hide();

    ui->m_AutoChangeBitckBox->setEnabled(true);
    ui->m_allowinputbitlabel->setEnabled(true);
    ui->m_AllowInputBitlineEdit->setEnabled(true);
    ui->Monitor_Address_EntryBtn->setEnabled(true);
}

void QValueDateInputDlg::on_Monitor_Address_EntryBtn_clicked()
{
    QString addrStr = ui->m_AllowInputBitlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,0,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_AllowInputBitlineEdit->setText(Monitor_Address_Keyboard.sShowAddr);
    }
}

void QValueDateInputDlg::on_m_PouupckBox_clicked(bool checked)
{
    if(checked)
    {
        ui->m_KeygroupBox->setEnabled(true);
        ui->m_keyspBox->setEnabled(true);
    }
    else
    {
        ui->m_KeygroupBox->setEnabled(false);
        ui->m_keyspBox->setEnabled(false);
    }
}

void QValueDateInputDlg::on_m_keyspBox_currentIndexChanged(int index)
{
    QString sKeyName = ui->m_keyspBox->currentText();
    if("" == sKeyName)
    {
        return ;
    }

    int totalNum = pwnd->pSceneSheet.size();
    for(int i = 0; i< totalNum; i++)
    {
        if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 2 && sKeyName == pwnd->pSceneSheet[i]->sNewScreenName)
        {
            int nWidth = pwnd->pSceneSheet[i]->width();
            int nHight = pwnd->pSceneSheet[i]->height();
            int nxValue = pwnd->m_pSamSysParame->m_projectProp.nSceneWidth  - nWidth;
            int nyValue = pwnd->m_pSamSysParame->m_projectProp.nSceneHeight - nHight;

            ui->m_xKeyspinBox->setRange(0,nxValue);
            ui->m_yKeyspinBox->setRange(0,nyValue);
            ui->m_xKeyspinBox->setValue(pwnd->m_pSamSysParame->m_projectProp.nSceneWidth/2 - nWidth/2);
            ui->m_yKeyspinBox->setValue(pwnd->m_pSamSysParame->m_projectProp.nSceneHeight/2 - nHight/2);

            break;
        }
    }
}

bool QValueDateInputDlg::IsHaveKeyboard()
{
    bool ret = ui->m_PouupckBox->isChecked();

    return ret;
}
