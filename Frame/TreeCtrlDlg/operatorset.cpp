#include "operatorset.h"
#include "ui_operatorset.h"
//#include "Frame/qprogectmanager.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

//ÊÇ·ñ¿ªÆô´¥ÃşÉùÒô
operatorSet::operatorSet(QWidget *parent):QDialog(parent),ui(new Ui::operatorSet)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setFixedSize(size());
    setWindowTitle(tr("²Ù×÷ÉèÖÃ"));

    QRegExp regExp("[0-9A-Za-z_]*");
    QValidator *validator = new QRegExpValidator(regExp, this);
    ui->lineEdit->setValidator(validator);
    ui->lineEdit->setToolTip(tr("ÓĞĞ§×Ö·û:A-Z,a-z,0-9,_"));

    QRegExp regExpPort("[1-9][0-9]*");
    QValidator *validatorPort = new QRegExpValidator(regExpPort, this);
    ui->lineEditPort->setValidator(validatorPort);
    ui->lineEditPort->setToolTip(tr("ÓĞĞ§×Ö·û:0-9"));

    ui->checkBox->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bTouchVoice);
    ui->check_autologin->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_autoLogin);
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_autoLogin)
    {
        ui->lineEdit->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strMonitor);
        ui->check_multivisitor->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bMultiVisitor);
        ui->lineEditPort->setText(QString("%1").arg(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nMonitorPort));
    }
    else
    {
        ui->lineEdit->setText("");
        ui->check_multivisitor->setChecked(false);
        ui->lineEditPort->setText("743");
    }

    on_check_autologin_clicked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_autoLogin);
}

operatorSet::~operatorSet()
{
    delete ui;
}

void operatorSet::on_pushButton_sure_clicked()
{
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bTouchVoice = ui->checkBox->isChecked();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_autoLogin = ui->check_autologin->isChecked();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bMultiVisitor = ui->check_multivisitor->isChecked();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strMonitor = ui->lineEdit->text();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_nMonitorPort = ui->lineEditPort->text().toInt();
    this->accept();
}

void operatorSet::on_pushButton_cancel_clicked()
{
    this->close();
}

//void operatorSet::on_checkBox_clicked(bool checked)
//{
//    ui->checkBox->setChecked(checked);
//}

void operatorSet::on_check_autologin_clicked(bool checked)
{
    ui->label->setEnabled(checked);
    ui->lineEdit->setEnabled(checked);
    ui->lineEditPort->setEnabled(checked);
    if(!checked)
    {
        ui->check_multivisitor->setChecked(false);
    }
    ui->check_multivisitor->setEnabled(checked);
}
