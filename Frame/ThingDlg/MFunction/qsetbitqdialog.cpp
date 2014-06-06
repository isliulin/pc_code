#include "qsetbitqdialog.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QSetBitQDialog::QSetBitQDialog(int iType,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSetBitQDialog)
{
    ui->setupUi(this);
    QString str = tr("功能-");
    switch(iType)
    {
    case 0:
             sFunName = tr("置位线圈");
             ui->label->setText(sFunName);
             break;
         case 1:
             sFunName = tr("复位线圈");
             ui->label->setText(sFunName);
             break;
         case 2:
             sFunName = tr("线圈交替");
             ui->label->setText(sFunName);
             break;
         default:
             sFunName = tr("线圈交替");
             ui->label->setText(sFunName);iType = 0;
             break;
    }
     this->setWindowTitle(str+sFunName);
    iType = iType;
}

QSetBitQDialog::~QSetBitQDialog()
{
    delete ui;
}

void QSetBitQDialog::on_pushButton_2_clicked()
{
    if(! pwnd->IsAddressCheckRight(setBit_address,sFunName,ui->lineEdit,0))
     {
         return;
     }
    accept();
}

void QSetBitQDialog::on_pushButton_3_clicked()
{
    reject();
}

void QSetBitQDialog::on_pushButton_clicked()
{

    pwnd->Addr_Type=0;
    AddressInputDialog addressintputdlg_writeaddress(setBit_address,this);
    QString sTmp=ui->lineEdit->text();
    int res=addressintputdlg_writeaddress.exec();
    if(res==QDialog::Accepted)
    {
           ui->lineEdit->setText(setBit_address.sShowAddr);

    }
    else
    {
        ui->lineEdit->setText(sTmp);
    }
}
