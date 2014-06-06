#include "addrchangedlg.h"
#include "ui_addrchangedlg.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

addrChangeDlg::addrChangeDlg(AddrMsg* pAMsg, int addrId, QWidget *parent):QDialog(parent),ui(new Ui::addrChangeDlg)
{
    ui->setupUi(this);

    setFixedSize(size());
    this->setWindowTitle(tr("地址替换"));
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    replaceType = 0;//那种方式替换
    replaceAddr = "";//替换地址

    ui->lineEdit_info->setText(pAMsg->Address[addrId].str);
    ui->lineEdit_info->setEnabled(false);

    ui->lineEdit_addrOld->setText(pAMsg->Address[addrId].pAddr->sShowAddr);
    ui->lineEdit_addrOld->setEnabled(false);

    ui->lineEdit_addrNew->setText(replaceAddr);

    ui->radioButton_1->setChecked(true);
    ui->radioButton_2->setChecked(false);
    ui->radioButton_3->setChecked(false);
    ui->radioButton_4->setChecked(false);

    type = pAMsg->Address[addrId].type;//老地址的类型
}

addrChangeDlg::~addrChangeDlg()
{
    delete ui;
}

void addrChangeDlg::on_pushButton_sure_clicked()
{
    replaceAddr = ui->lineEdit_addrNew->text();
    if(!pwnd->IsAddressCheckRight(key,tr("地址"),ui->lineEdit_addrNew,type))
    {
        return;
    }

    if(ui->radioButton_1->isChecked())
    {
        replaceType = 0;
    }
    else if(ui->radioButton_2->isChecked())
    {
        replaceType = 1;
    }
    else if(ui->radioButton_3->isChecked())
    {
        replaceType = 2;
    }
    else//if(ui->radioButton_4->isChecked())
    {
        replaceType = 3;
    }

    accept();
}

void addrChangeDlg::on_pushButton_cancel_clicked()
{
    close();
}

void addrChangeDlg::on_pushButton_addr_clicked()
{
    QString str = ui->lineEdit_addrNew->text();
    AddressInputDialog dlg_readaddress(key,str,type,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_addrNew->setText(key.sShowAddr);
    }
}
