#include "qnewdatatransfer.h"
#include "ui_qnewdatatransfer.h"
#include "Frame/addressinputdialog.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
QNewDataTransfer::QNewDataTransfer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewDataTransfer)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    R_Group = new QButtonGroup(this);
    R_Group->addButton(ui->Timed,1);
    R_Group->addButton(ui->Triggered,2);
    ui->Timed->setChecked(true);
    on_Timed_clicked(true);
    //connect(ui->Accept, SIGNAL(accepted()), this, SLOT(on_Accept_clicked()));
//    connect(ui->cancel, SIGNAL(rejected()), this, SLOT(reject()));
    iFlg=0;//新建数据
    this->setWindowTitle(tr("资料传输"));
    ui->Accept->setFocus();
    on_check_length_clicked(false);
}
QNewDataTransfer::QNewDataTransfer(int CheckRow,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QNewDataTransfer)
{
    ui->setupUi(this);
    R_Group = new QButtonGroup(this);
    R_Group->addButton(ui->Timed,1);
    R_Group->addButton(ui->Triggered,2);
    //connect(ui->Accept, SIGNAL(accepted()), this, SLOT(on_Accept_clicked()));

    //计时、触发
    R_Group->button(pwnd->m_pSamSysParame->m_qvcdataTransProp.at(CheckRow).nTriggerType)->setChecked(true);
    ui->bAutomatismOff->setChecked(pwnd->m_pSamSysParame->m_qvcdataTransProp.at(CheckRow).bAutomatismOff);
    //间隔
    ui->Interval_Time->setValue(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].nTriggerSpace);
    //触发Keyboard
    kTriggerBit=pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].mTriggerAddr;
    //触发地址输入框
    ui->Trigger_Bit->setText(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].mTriggerAddr.sShowAddr);
    //地址类型索引
    ui->Address_Type->setCurrentIndex(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].nAddrType);
    //字、位数
    ui->Word_Bit_Number->setValue(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].nWordBitPos);
    //源地址Keyboard
    kSourceAddress=pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].mSourceAddr;
    //源地址
    ui->Source_Address->setText(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].mSourceAddr.sShowAddr);
    //源地址Keyboard
    kDestinationAdderss=pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].mTargetAddr;
     //源地址
    ui->Destination_Address->setText(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].mTargetAddr.sShowAddr);
       iFlg=1;//修改数据
    ui->check_length->setChecked(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].bDynLength);


    on_check_length_clicked(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].bDynLength);
    if(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].bDynLength)
    {
        ui->length_Address->setText(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].mLengthAddr.sShowAddr);
    }

    iCurrentRow=CheckRow;
    if(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].nTriggerType ==1)
    {
        on_Timed_clicked(true);
    }
    else if(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].nTriggerType ==2)
    {
        on_Triggered_clicked(true);
    }
    this->setWindowTitle(tr("资料传输"));
}

QNewDataTransfer::~QNewDataTransfer()
{
    if(R_Group)
    {
        delete R_Group;
        R_Group=NULL;
    }
    delete ui;
}

void QNewDataTransfer::on_Timed_clicked(bool checked)
{
    if(checked)
    {
        //ui->label->setHidden(false);
        ui->Interval_Time->setHidden(false);
        ui->label_3->setHidden(false);
        //ui->label_2->setHidden(true);
        ui->Trigger_Bit->setHidden(true);
        ui->Trigger_Bit_Keyboard->setHidden(true);
        ui->bAutomatismOff->setHidden(true);
    }
}

void QNewDataTransfer::on_Triggered_clicked(bool checked)
{
    if(checked)
    {
        //ui->label->setHidden(true);
        ui->Interval_Time->setHidden(true);
        ui->label_3->setHidden(true);
        //ui->label_2->setHidden(false);
        ui->Trigger_Bit->setHidden(false);
        ui->Trigger_Bit_Keyboard->setHidden(false);
        ui->bAutomatismOff->setHidden(false);
    }
}

void QNewDataTransfer::on_Trigger_Bit_Keyboard_clicked()
{
    pwnd->Addr_Type=0;
    AddressInputDialog  dlg_triggered(kTriggerBit,this);
    dlg_triggered.exec();
    ui->Trigger_Bit->setText(kTriggerBit.sShowAddr);
}

void QNewDataTransfer::on_Source_Address_Keyboard_clicked()
{
    if(ui->Address_Type->currentIndex()==0)
    {
        pwnd->Addr_Type=0;

    }
    else if(ui->Address_Type->currentIndex()==1||ui->Address_Type->currentIndex()==2)
    {
        pwnd->Addr_Type=1;
    }
    AddressInputDialog  dlg_triggered(kSourceAddress,this);
    dlg_triggered.exec();
    ui->Source_Address->setText(kSourceAddress.sShowAddr);

}

void QNewDataTransfer::on_Destination_Address_Keyboard_clicked()
{
    if(ui->Address_Type->currentIndex()==0)
    {
        pwnd->Addr_Type=0;

    }
    else if(ui->Address_Type->currentIndex()==1||ui->Address_Type->currentIndex()==2)
    {
        pwnd->Addr_Type=1;
    }
    AddressInputDialog  dlg_triggered(kDestinationAdderss,this);
    dlg_triggered.exec();
    ui->Destination_Address->setText(kDestinationAdderss.sShowAddr);
}

void QNewDataTransfer::on_Accept_clicked()
{
    if(ui->Triggered->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(kTriggerBit,tr("触发位"),ui->Trigger_Bit,0))
        {
            return;
        }
    }
    if(ui->Address_Type->currentIndex()==0)
    {
        if(! pwnd->IsAddressCheckRight(kSourceAddress,tr("源地址"),ui->Source_Address,0))
        {
            return;
        }
        if(! pwnd->IsAddressCheckRight(kDestinationAdderss,tr("目标地址"),ui->Destination_Address,0))
        {
            return;
        }
    }
    else if(ui->Address_Type->currentIndex()==1||ui->Address_Type->currentIndex()==2)
    {
        if(! pwnd->IsAddressCheckRight(kSourceAddress,tr("源地址"),ui->Source_Address,1))
        {
            return;
        }
        if(! pwnd->IsAddressCheckRight(kDestinationAdderss,tr("目标地址"),ui->Destination_Address,1))
        {
            return;
        }

    }
    if(ui->check_length->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(kLengthAddress,tr("长度地址"),ui->length_Address,1))
        {
            return;
        }

    }
//     if(kSourceAddress.nConnectType!=0&&kDestinationAdderss.nConnectType!=0)//源地址和目标地址都不是内部存储区的话
//     {
//         if(kSourceAddress.nConnectType==kDestinationAdderss.nConnectType)//若是同一个连接
//             {
//             QMessageBox box(QMessageBox::Warning,PRO_FULL_NAME,tr("源地址和目标地址不能为同一PLC！"),
//                                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
//                    box.addButton(tr("确定"),QMessageBox::AcceptRole);
//                    box.exec();
//                 return;
//         }
//     }
    if(iFlg==0)
    {
        DATA_TRANSFER_PROP newDataTransfer;
        pwnd->m_pSamSysParame->m_qvcdataTransProp.append(newDataTransfer);
        int dataTranSize = pwnd->m_pSamSysParame->m_qvcdataTransProp.size();
        DataSive(dataTranSize-1);//用做数组下标的时候应该减1

    }
    else if(iFlg==1)
    {
        DataSive(iCurrentRow);
    }
    accept();

}

void QNewDataTransfer::on_cancel_clicked()
{

    this->close();
}
void QNewDataTransfer::DataSive(int index)
{
    if(index < 0 || index > pwnd->m_pSamSysParame->m_qvcdataTransProp.size()) return ;
    //计时、触发
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].nTriggerType =R_Group->checkedId();
    //间隔
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].nTriggerSpace =ui->Interval_Time->value();
    //触发地址输入框
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].mTriggerAddr.sShowAddr =ui->Trigger_Bit->text();
    //触发Keyboard
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].mTriggerAddr = kTriggerBit;
    //地址类型索引
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].nAddrType = ui->Address_Type->currentIndex();
    //字、位数
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].nWordBitPos = ui->Word_Bit_Number->value();
    //源地址
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].mSourceAddr.sShowAddr = ui->Source_Address->text();
    //源地址Keyboard
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].mSourceAddr = kSourceAddress;
    //源地址
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].mTargetAddr.sShowAddr = ui->Destination_Address->text();
    //源地址Keyboard
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].mTargetAddr = kDestinationAdderss;
    //自动复位
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].bAutomatismOff=ui->bAutomatismOff->isChecked();
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].bDynLength = ui->check_length->isChecked();
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].mLengthAddr = kLengthAddress;
    return;
}

void QNewDataTransfer::on_check_length_clicked(bool checked)
{
    ui->btn_length->setVisible(checked);
    ui->length_Address->setVisible(checked);
    ui->Word_Bit_Number->setVisible(!checked);
}

void QNewDataTransfer::on_btn_length_clicked()
{
    Keyboard wordAddr;
    QString addrStr = ui->length_Address->text();
    AddressInputDialog addressintputdlg_writeaddress(wordAddr,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->length_Address->setText(wordAddr.sShowAddr);
    }
}
