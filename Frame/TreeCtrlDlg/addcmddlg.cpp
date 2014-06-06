#include "addcmddlg.h"
#include "ui_addcmddlg.h"
#include "Frame/addressinputdialog.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
AddCmdDLg::AddCmdDLg(E_WEEKDAY weekday,ScheItem *item,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCmdDLg)
{
    ui->setupUi(this);
    ui->buttonGroup->setId(ui->check_SUN,SUN);
    ui->buttonGroup->setId(ui->check_MON,MONDAY);
    ui->buttonGroup->setId(ui->check_TUE,TUESDAT);
    ui->buttonGroup->setId(ui->check_WED,WEDNESDAY);
    ui->buttonGroup->setId(ui->check_THU,THURSDAY);
    ui->buttonGroup->setId(ui->check_FRI,FRIDAY);
    ui->buttonGroup->setId(ui->check_SAT,SATURDAY);

    if(item)//打开已有项
    {
        ui->radio->setChecked(!item->timeType);
        on_radio_clicked(!item->timeType);

        if(item->timeType)//从地址获取时间
        {
            ui->edit_AddrTime->setText(item->kTimeAddr.sShowAddr);
        }
        else
        {
            ui->timeEdit->setTime(item->time);
        }


        ui->comboBox->setCurrentIndex(item->eActionType);
        ui->comboBox_dataType->setCurrentIndex(item->eDataType);
        on_comboBox_currentIndexChanged(item->eActionType);

        ui->edit_ActionAddr->setText(item->kActionAddr.sShowAddr);

        ui->radio_3->setChecked(item->valueType);
        on_radio_3_clicked(item->valueType);
        if(item->valueType)
        {
            ui->edit_Value->setText(item->kValueAddr.sShowAddr);
        }
        else
        {
            ui->edit_Value->setText(QString::number(item->nValue));
        }

        ui->group_Ctl->setChecked(item->bControl);
        if(item->bControl)
        {
            ui->edit_CtlAddr->setText(item->kControlAddr.sShowAddr);
            qDebug() <<"kControlAddr: "<< item->kControlAddr.sShowAddr;
        }
    }
    else//默认设置
    {
        on_radio_clicked(true);
        on_radio_4_clicked(true);
        ui->comboBox->setCurrentIndex(0);
        on_comboBox_currentIndexChanged(0);

    }

    if(weekday == WEEKDAYERROR)//添加多个
    {
        foreach(QAbstractButton *btn,ui->buttonGroup->buttons())
        {
            btn->setChecked(true);
        }
    }
    else
    {
        if(ui->buttonGroup->button(weekday))
        {
            ui->buttonGroup->button(weekday)->setChecked(true);
        }

        foreach(QAbstractButton *btn,ui->buttonGroup->buttons())
        {
            btn->setEnabled(false);
        }
    }

}

AddCmdDLg::~AddCmdDLg()
{
    delete ui;
}

void AddCmdDLg::on_btn_ok_clicked()
{
    ScheItem item;
    Keyboard addr;
    if(!ui->radio->isChecked())
    {
        if(!pwnd->IsAddressCheckRight(item.kTimeAddr,tr("时间地址"),ui->edit_AddrTime,1))
        {
            return;
        }
        item.kTimeAddr.Length = 3;
    }

    item.eDataType = ui->comboBox_dataType->currentIndex();
    int addrLen = 1;
    switch(item.eDataType )
    {
    case 1:
    case 3:
    case 5:
    case 6:
        addrLen = 2;
        break;
    default :
        break;
    }
    int type = 1;
    if(ui->comboBox->currentIndex() <= BITXOR)
       type = 0;

    if(!pwnd->IsAddressCheckRight(item.kActionAddr,tr("写入地址"),ui->edit_ActionAddr,type))
    {
        return;
    }
    item.kActionAddr.Length = addrLen;
    if(!ui->radio_4->isChecked())
    {
        if( !pwnd->IsAddressCheckRight(item.kValueAddr,tr("写入值"),ui->edit_Value,type))
        {
            return;
        }
        item.kValueAddr.Length = addrLen;
    }

    if(ui->group_Ctl->isChecked() && !pwnd->IsAddressCheckRight(item.kControlAddr,tr("写入值"),ui->edit_CtlAddr,0))
    {
        return;
    }


    item.timeType = !ui->radio->isChecked();
    item.time = ui->timeEdit->time();
    //item.kTimeAddr.sShowAddr = ui->edit_AddrTime->text();
    item.eActionType = (E_ACTION_TYPE)ui->comboBox->currentIndex();
    //item.kActionAddr.sShowAddr = ui->edit_ActionAddr->text();


    item.valueType = ui->radio_3->isChecked();
    item.nValue = ui->edit_Value->text().toDouble();
    item.bControl = ui->group_Ctl->isChecked();
    //item.kControlAddr.sShowAddr = ui->edit_CtlAddr->text();
    for(int i=SUN; i<=SATURDAY;i++)
    {
        if(ui->buttonGroup->button(i)->isChecked())
        {
            item.eWeek = (E_WEEKDAY)i;
            m_items << item;
        }
    }
    accept();
}

void AddCmdDLg::on_radio_clicked(bool checked)
{
    ui->timeEdit->setVisible(checked);
    ui->edit_AddrTime->setVisible(!checked);
    ui->btn_wordAddr_const->setVisible(!checked);
}

void AddCmdDLg::on_radio_2_clicked(bool checked)
{
    ui->timeEdit->setVisible(!checked);
    ui->edit_AddrTime->setVisible(checked);
    ui->btn_wordAddr_const->setVisible(checked);
}

void AddCmdDLg::on_radio_4_clicked(bool checked)
{
    ui->btn_ValueAddr->setVisible(!checked);
    resetEdit();
}

void AddCmdDLg::on_radio_3_clicked(bool checked)
{
    ui->btn_ValueAddr->setVisible(checked);
    resetEdit();
}

void AddCmdDLg::resetEdit()
{
    int nActionType = ui->comboBox->currentIndex();
    int nDataType = ui->comboBox_dataType->currentIndex();
    bool bConst = ui->radio_4->isChecked();

    ui->edit_Value->setMaxLength(256);

    DoubleValidator *validator = 0;
    double nMax = 2147483647L;
    double nMin = -2147483648L;
    int decLen = 0;

    switch(nActionType)
    {
    case BITSET://设置位
        if(bConst)
        {
            nMax = 1;
            nMin = 0;
            validator = new DoubleValidator(nMin,nMax,decLen,this);
            ui->edit_Value->setMaxLength(1);
        }
        else
        {
            ui->edit_Value->setText("LB0");
        }

        break;
    case BITXOR://位取反
        break;
    case SETWORD://设置字
        if(bConst)
        {
            switch(nDataType)
            {
            case 0://16位整数
                {
                    nMax = 32767;
                    nMin = -32768;
                     decLen = 0;
                }
                break;
            case 1://32位整数
                {
                    nMax = 2147483647L;
                    nMin = -2147483648L;
                     decLen = 0;
                }
                break;
            case 2://16位正整数
                {
                    nMax = 65535;
                    nMin = 0;
                     decLen = 0;
                }
                break;
            case 3://32位正整数
                {
                    nMax = 4294967295UL;
                    nMin = 0;
                    decLen = 0;
                }
                break;
            case 4://32位浮点数
                {
                    nMax = 2147483647L;
                    nMin = -2147483648L;
                    decLen = 10;
                }
                break;
            }
            if (nMin>0)
            {
                nMin = nMin*-1;
            }
            validator = new DoubleValidator(nMin,nMax,decLen,this);
        }
        else
            ui->edit_Value->setText("LW0");
        break;
    default:break;
    }

    ui->edit_Value->setValidator(validator);

}

void AddCmdDLg::on_comboBox_currentIndexChanged(int index)
{
    ui->comboBox_dataType->setEnabled(index < 0 || index > BITXOR);
    ui->radio_3->setEnabled(index != BITXOR);
    ui->radio_4->setEnabled(index != BITXOR);
    ui->edit_Value->setEnabled(index != BITXOR);
    ui->btn_ValueAddr->setEnabled(index != BITXOR);
    ui->label_3->setEnabled(index < 0 || index > BITXOR);
    resetEdit();


}

void AddCmdDLg::on_btn_wordAddr_const_clicked()
{
    Keyboard addr;

    int addrType = 1;

    QString addrStr = ui->edit_AddrTime->text();
    AddressInputDialog addressintputdlg_writeaddress(addr,addrStr,addrType,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->edit_AddrTime->setText(addr.sShowAddr);
    }
}

void AddCmdDLg::on_btn_ActionAddr_clicked()
{
    Keyboard addr;

    int addrType = 1;
    if(ui->comboBox->currentIndex() <= BITXOR)
    {
        addrType = 0;
    }
    QString addrStr = ui->edit_ActionAddr->text();
    AddressInputDialog addressintputdlg_writeaddress(addr,addrStr,addrType,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->edit_ActionAddr->setText(addr.sShowAddr);
    }
}

void AddCmdDLg::on_btn_ValueAddr_clicked()
{
    Keyboard addr;

    int addrType = 1;
    if(ui->comboBox->currentIndex() <= BITXOR)
    {
        addrType = 0;
    }

    QString addrStr = ui->edit_Value->text();
    AddressInputDialog addressintputdlg_writeaddress(addr,addrStr,addrType,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->edit_Value->setText(addr.sShowAddr);
    }
}

void AddCmdDLg::on_btn_CtlAddr_clicked()
{
    Keyboard addr;

    int addrType = 0;

    QString addrStr = ui->edit_CtlAddr->text();
    AddressInputDialog addressintputdlg_writeaddress(addr,addrStr,addrType,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->edit_CtlAddr->setText(addr.sShowAddr);
    }
}

void AddCmdDLg::on_btn_cancel_clicked()
{
    reject();
}

void AddCmdDLg::on_comboBox_dataType_currentIndexChanged(int index)
{
    if(ui->comboBox->currentIndex() == SETWORD
       && ui->radio_4->isChecked())
    {
        DoubleValidator *validator = 0;
        double nMax = 2147483647L;
        double nMin = -2147483648L;
        int decLen = 0;
        switch(index)
        {
        case 0://16位整数
            {
                nMax = 32767;
                nMin = -32768;
                 decLen = 0;
            }
            break;
        case 1://32位整数
            {
                nMax = 2147483647L;
                nMin = -2147483648L;
                 decLen = 0;
            }
            break;
        case 2://16位正整数
            {
                nMax = 65535;
                nMin = 0;
                 decLen = 0;
            }
            break;
        case 3://32位正整数
            {
                nMax = 4294967295UL;
                nMin = 0;
                decLen = 0;
            }
            break;
        case 4://32位浮点数
            {
                nMax = 2147483647L;
                nMin = -2147483648L;
                decLen = 10;
            }
            break;
        }
        if (nMin>0)
        {
            nMin = nMin*-1;
        }
        validator = new DoubleValidator(nMin,nMax,decLen,this);
        ui->edit_Value->setValidator(validator);

        double value = ui->edit_Value->text().toDouble();
        if (value > nMax || value < nMin)
        {
            ui->edit_Value->setText("0");
        }
    }
}
