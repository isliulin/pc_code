#include "qdotdialog.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QDotDialog::QDotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDotDialog)
{
    ui->setupUi(this);
    ui->comboBox->addItem(tr("按下为0"));
    ui->comboBox->addItem(tr("按下为1"));
}

QDotDialog::~QDotDialog()
{
    delete ui;
}

void QDotDialog::on_pushButton_2_clicked()
{
    if(! pwnd->IsAddressCheckRight(dot_address,tr("点动地址"),ui->lineEdit,0))
     {
         return;
     }
    accept();
}

void QDotDialog::on_pushButton_3_clicked()
{
    reject();
}

void QDotDialog::on_pushButton_clicked()
{
    pwnd->Addr_Type=0;
    AddressInputDialog addressintputdlg_writeaddress(dot_address,this);
    QString sTmp=ui->lineEdit->text();
    int res=addressintputdlg_writeaddress.exec();
    if(res==QDialog::Accepted)
    {
        ui->lineEdit->setText(dot_address.sShowAddr);
    }
    else
    {
        ui->lineEdit->setText(sTmp);
    }
}
