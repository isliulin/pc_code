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
    iFlg=0;//�½�����
    this->setWindowTitle(tr("���ϴ���"));
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

    //��ʱ������
    R_Group->button(pwnd->m_pSamSysParame->m_qvcdataTransProp.at(CheckRow).nTriggerType)->setChecked(true);
    ui->bAutomatismOff->setChecked(pwnd->m_pSamSysParame->m_qvcdataTransProp.at(CheckRow).bAutomatismOff);
    //���
    ui->Interval_Time->setValue(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].nTriggerSpace);
    //����Keyboard
    kTriggerBit=pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].mTriggerAddr;
    //������ַ�����
    ui->Trigger_Bit->setText(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].mTriggerAddr.sShowAddr);
    //��ַ��������
    ui->Address_Type->setCurrentIndex(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].nAddrType);
    //�֡�λ��
    ui->Word_Bit_Number->setValue(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].nWordBitPos);
    //Դ��ַKeyboard
    kSourceAddress=pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].mSourceAddr;
    //Դ��ַ
    ui->Source_Address->setText(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].mSourceAddr.sShowAddr);
    //Դ��ַKeyboard
    kDestinationAdderss=pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].mTargetAddr;
     //Դ��ַ
    ui->Destination_Address->setText(pwnd->m_pSamSysParame->m_qvcdataTransProp[CheckRow].mTargetAddr.sShowAddr);
       iFlg=1;//�޸�����
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
    this->setWindowTitle(tr("���ϴ���"));
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
        if(! pwnd->IsAddressCheckRight(kTriggerBit,tr("����λ"),ui->Trigger_Bit,0))
        {
            return;
        }
    }
    if(ui->Address_Type->currentIndex()==0)
    {
        if(! pwnd->IsAddressCheckRight(kSourceAddress,tr("Դ��ַ"),ui->Source_Address,0))
        {
            return;
        }
        if(! pwnd->IsAddressCheckRight(kDestinationAdderss,tr("Ŀ���ַ"),ui->Destination_Address,0))
        {
            return;
        }
    }
    else if(ui->Address_Type->currentIndex()==1||ui->Address_Type->currentIndex()==2)
    {
        if(! pwnd->IsAddressCheckRight(kSourceAddress,tr("Դ��ַ"),ui->Source_Address,1))
        {
            return;
        }
        if(! pwnd->IsAddressCheckRight(kDestinationAdderss,tr("Ŀ���ַ"),ui->Destination_Address,1))
        {
            return;
        }

    }
    if(ui->check_length->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(kLengthAddress,tr("���ȵ�ַ"),ui->length_Address,1))
        {
            return;
        }

    }
//     if(kSourceAddress.nConnectType!=0&&kDestinationAdderss.nConnectType!=0)//Դ��ַ��Ŀ���ַ�������ڲ��洢���Ļ�
//     {
//         if(kSourceAddress.nConnectType==kDestinationAdderss.nConnectType)//����ͬһ������
//             {
//             QMessageBox box(QMessageBox::Warning,PRO_FULL_NAME,tr("Դ��ַ��Ŀ���ַ����ΪͬһPLC��"),
//                                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
//                    box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
//                    box.exec();
//                 return;
//         }
//     }
    if(iFlg==0)
    {
        DATA_TRANSFER_PROP newDataTransfer;
        pwnd->m_pSamSysParame->m_qvcdataTransProp.append(newDataTransfer);
        int dataTranSize = pwnd->m_pSamSysParame->m_qvcdataTransProp.size();
        DataSive(dataTranSize-1);//���������±��ʱ��Ӧ�ü�1

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
    //��ʱ������
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].nTriggerType =R_Group->checkedId();
    //���
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].nTriggerSpace =ui->Interval_Time->value();
    //������ַ�����
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].mTriggerAddr.sShowAddr =ui->Trigger_Bit->text();
    //����Keyboard
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].mTriggerAddr = kTriggerBit;
    //��ַ��������
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].nAddrType = ui->Address_Type->currentIndex();
    //�֡�λ��
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].nWordBitPos = ui->Word_Bit_Number->value();
    //Դ��ַ
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].mSourceAddr.sShowAddr = ui->Source_Address->text();
    //Դ��ַKeyboard
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].mSourceAddr = kSourceAddress;
    //Դ��ַ
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].mTargetAddr.sShowAddr = ui->Destination_Address->text();
    //Դ��ַKeyboard
    pwnd->m_pSamSysParame->m_qvcdataTransProp[index].mTargetAddr = kDestinationAdderss;
    //�Զ���λ
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
