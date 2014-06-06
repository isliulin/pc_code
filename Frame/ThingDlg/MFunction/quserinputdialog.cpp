#include "quserinputdialog.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QUserInputDialog::QUserInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QUserInputDialog)
{
    ui->setupUi(this);

    ui->comboBox_datastyle->addItem(tr("16λ������"));
    ui->comboBox_datastyle->addItem(tr("32λ������"));
    ui->comboBox_datastyle->addItem(tr("16λ����"));
    ui->comboBox_datastyle->addItem(tr("32λ����"));
    ui->comboBox_datastyle->addItem(tr("16λBCD������"));
    ui->comboBox_datastyle->addItem(tr("32λBCD������"));
    ui->comboBox_datastyle->addItem(tr("32λ������"));
}

QUserInputDialog::~QUserInputDialog()
{
    delete ui;
}

void QUserInputDialog::on_pushButton_2_clicked()
{
    if(! pwnd->IsAddressCheckRight(intput_address,tr("д���ַ"),ui->lineEdit,1))
     {
         return;
     }
    accept();
}

void QUserInputDialog::on_pushButton_3_clicked()
{
    reject();
}

void QUserInputDialog::on_pushButton_clicked()
{
    pwnd->Addr_Type=1;
    AddressInputDialog addressintputdlg_writeaddress(intput_address,this);
    QString sTmp=ui->lineEdit->text();
    int res=addressintputdlg_writeaddress.exec();
    if(res==QDialog::Accepted)
    {
        ui->lineEdit->setText(intput_address.sShowAddr);
    }
    else
    {
        ui->lineEdit->setText(sTmp);
    }

}
