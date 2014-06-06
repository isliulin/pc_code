#include "qresetbitdialog.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
QResetBitDialog::QResetBitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QResetBitDialog)
{
    ui->setupUi(this);
}

QResetBitDialog::~QResetBitDialog()
{
    delete ui;
}

void QResetBitDialog::on_pushButton_2_clicked()
{
    if(! pwnd->IsAddressCheckRight(retBit_address,tr("¸´Î»µØÖ·"),ui->lineEdit,0))
     {
         return;
     }
    accept();
}

void QResetBitDialog::on_pushButton_3_clicked()
{
    reject();
}

void QResetBitDialog::on_pushButton_clicked()
{
    pwnd->Addr_Type=0;
    AddressInputDialog addressintputdlg_writeaddress(retBit_address,this);
    QString sTmp=ui->lineEdit->text();
    int res=addressintputdlg_writeaddress.exec();
    if(res==QDialog::Accepted)
    {
        ui->lineEdit->setText(retBit_address.sShowAddr);
    }
    else
    {
        ui->lineEdit->setText(sTmp);
    }

}
