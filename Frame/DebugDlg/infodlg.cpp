#include "infodlg.h"
#include "ui_infodlg.h"
#include "downloadtrd.h"

InfoDlg::InfoDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDlg)
{
    ui->setupUi(this);
    setWindowTitle(tr("HMI信息"));
    setFixedSize(size());
    thread = new downloadTrd();
    connect(thread,SIGNAL(serial(QString,int)),this,SLOT(Serial(QString,int)));
    thread->setprarm(999,"");
    thread->start();
}

InfoDlg::~InfoDlg()
{
    delete ui;
    if(thread->isRunning())
    {
        thread->terminate();
    }
    thread->deleteLater();
}
void InfoDlg::Serial(QString sNumber,int type)
{
    qDebug() << "InfoDlg::Serial";
    QString serial = sNumber.remove("\n");
    switch(type)
    {
    case 1:
        ui->label_3->setText(serial);
        break;
    case 2:
        ui->label_4->setText(serial);
        break;
    case 3:
        ui->label_3->setText(tr("获取序列号失败"));
        break;
    case 4:
        ui->label_4->setText(tr("获取型号失败"));
        break;
    case 5:
        ui->label_3->setText(tr("HMI未连接"));
        ui->label_4->setText(tr("HMI未连接"));
        break;
    }

}

void InfoDlg::on_pushButton_clicked()
{
    ui->label_3->setText("");
    ui->label_4->setText("");
    thread->setprarm(999,"");
    thread->start();
}
