#include "qalterdialog.h"

#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
QAlterDialog::QAlterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QAlterDialog)
{
    ui->setupUi(this);
}

QAlterDialog::~QAlterDialog()
{
    delete ui;
}

void QAlterDialog::on_pushButton_2_clicked()
{
    if(! pwnd->IsAddressCheckRight(alter_address,tr("½»ÌæµØÖ·"),ui->lineEdit,0))
     {
         return;
     }
    accept();
}

void QAlterDialog::on_pushButton_3_clicked()
{
    reject();
}

void QAlterDialog::on_pushButton_clicked()
{
    pwnd->Addr_Type=0;
    AddressInputDialog addressintputdlg_writeaddress(alter_address,this);
    QString sTmp=ui->lineEdit->text();
    int res=addressintputdlg_writeaddress.exec();
    if(res==QDialog::Accepted)
    {
        ui->lineEdit->setText(alter_address.sShowAddr);
    }
    else
    {
        ui->lineEdit->setText(sTmp);
    }
}
