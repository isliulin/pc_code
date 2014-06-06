#include "newdownload.h"
#include "ui_newdownload.h"
#include "Frame/mainwindow.h"
#include "Frame/akipedit.h"

extern MainWindow *pwnd;

NewDownload::NewDownload(QWidget *parent):QDialog(parent),ui(new Ui::NewDownload)
{
    ui->setupUi(this);

    setFixedSize(size());

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    QRegExp regExp("[0-9A-Za-z_]*");
    QValidator *validator = new QRegExpValidator(regExp, this);
    ui->lineEdit->setValidator(validator);
    ui->lineEdit->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));

    pType = NULL;
    pType = new QButtonGroup();
    pType->addButton(ui->radioButton,0);
    pType->addButton(ui->radioButton_2,1);
    connect(pType,SIGNAL(buttonClicked(int)),this,SLOT(downTypeSelect(int)));

    //QRegExp regExp("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$");
    //QRegExpValidator *pValidator = new QRegExpValidator(regExp, this);
    //ui->IP->setValidator(pValidator);
    //ui->IP->setInputMask("000.000.000.000;");
    //

    QVBoxLayout *layout = new QVBoxLayout;
    ui->groupBox_5->setLayout(layout);
    ipEdit = new IpAddressWidget(this);
    layout->addWidget(ipEdit);
    //ui->IP->setVisible(false);

    setWindowTitle(tr("上下载设置"));

    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_eDownload == UsbDownload)
    {
        downTypeSelect(0);
        pType->button(0)->setChecked(true);
    }
    else
    {
        downTypeSelect(1);
        pType->button(1)->setChecked(true);
    }
    ipEdit->setIp(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp1
                  ,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp2
                  ,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp3
                  ,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp4);
    //ipEdit->setText(QString("%1.%2.%3.%4").arg(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp1)
     //           .arg(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp2)
     //           .arg(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp3)
     //           .arg(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp4));

    //ui->port->setText(QString::number(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nPort));

    //ui->comboBox->addItem(tr("JPEG"));
    //ui->comboBox->addItem(tr("BMP"));
    //ui->comboBox->setCurrentIndex((int)pwnd->m_pSamSysParame->m_mixGlobalVar.m_ePicMode - 1);
    //ui->comboBox->hide();
    //ui->label_7->hide();


    ui->checkBox_3->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bClearAlarm);
    ui->checkBox_4->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bWriteFormula);

    ui->groupBox_2->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bUpLoad);
    ui->checkBox_5->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bUploadPassword);
    ui->lineEdit->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strUploadPassword);

    on_groupBox_2_clicked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bUpLoad);
}

NewDownload::~NewDownload()
{
    if(pType)
    {
        delete pType;
        pType = NULL;
    }
    delete ui;
}

void NewDownload::downTypeSelect(int iCheckId)
{
    switch(iCheckId)
    {
    case 0://USB下载
        //ui->label_2->setVisible(false);
        //ui->label_6->setVisible(false);
        //ui->IP->setVisible(false);
        //ui->port->setVisible(false);
        break;
    case 1://以太网下载
        //ui->label_2->setVisible(true);
        //ui->label_6->setVisible(false);
        //ui->IP->setVisible(true);
        //ui->port->setVisible(false);
        break;
    }
}

void NewDownload::on_pushButton_sure_clicked()
{
    if(ui->radioButton->isChecked())
    {
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_eDownload = UsbDownload;
    }
    else
    {
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_eDownload = NetDownload;
    }

    QString sIP = ipEdit->GetIpAddressString();
    QStringList slit = sIP.split(".");
    if(slit.size() == 4)
    {
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp1 = slit.at(0).toInt();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp2 = slit.at(1).toInt();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp3 = slit.at(2).toInt();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nIp4 = slit.at(3).toInt();
    }

    //pwnd->m_pSamSysParame->m_mixGlobalVar.m_nPort = ui->port->text().toInt();

    //pwnd->m_pSamSysParame->m_mixGlobalVar.m_ePicMode = (PicSaveMode)(ui->comboBox->currentIndex() + 1);

    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bStartHMI       = false;
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bClearData      = false;
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bClearAlarm     = ui->checkBox_3->isChecked();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bWriteFormula   = ui->checkBox_4->isChecked();

    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bUpLoad = ui->groupBox_2->isChecked();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bUploadPassword = ui->checkBox_5->isChecked();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strUploadPassword = ui->lineEdit->text();

    accept();
}

void NewDownload::on_pushButton_cancel_clicked()
{
    close();
}

void NewDownload::on_groupBox_2_clicked(bool checked)
{
    ui->checkBox_5->setVisible(checked);
    on_checkBox_5_clicked(ui->checkBox_5->isChecked());   
}

void NewDownload::on_checkBox_5_clicked(bool checked)
{
    if(ui->groupBox_2->isChecked())
    {
        ui->label->setVisible(checked);
        ui->lineEdit->setVisible(checked);
    }
    else
    {
        ui->label->setVisible(false);
        ui->lineEdit->setVisible(false);
    }
}

void NewDownload::on_pushButton_help_clicked()
{
    pwnd->loadHelpHtm(TREE_DOWNSET);
}
