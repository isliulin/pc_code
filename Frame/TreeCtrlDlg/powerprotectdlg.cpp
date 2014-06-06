#include "powerprotectdlg.h"
#include "ui_powerprotectdlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

PowerProtectDlg::PowerProtectDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PowerProtectDlg)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    this->setWindowTitle(tr("µôµç´æ´¢ÇøÉèÖÃ"));
    QIntValidator *validator = new QIntValidator(0,65535,this);
    ui->edit_lb->setValidator(validator);

    validator = new QIntValidator(0,65535,this);
    ui->edit_lw->setValidator(validator);
    validator = new QIntValidator(0,1024,this);
    ui->edit_length_lb->setValidator(validator);
    validator = new QIntValidator(0,1024,this);
    ui->edit_length_lw->setValidator(validator);

    ui->edit_lb->setText(QString::number(pwnd->m_pSamSysParame->m_PowerProtect.startLB));
    ui->edit_lw->setText(QString::number(pwnd->m_pSamSysParame->m_PowerProtect.startLW));
    ui->edit_length_lb->setText(QString::number(pwnd->m_pSamSysParame->m_PowerProtect.lengthLB));
    ui->edit_length_lw->setText(QString::number(pwnd->m_pSamSysParame->m_PowerProtect.lengthLW));

}

PowerProtectDlg::~PowerProtectDlg()
{
    delete ui;
}

void PowerProtectDlg::on_btn_ok_clicked()
{
    int nValue = 0;
    nValue = ui->edit_lb->text().toInt();
    pwnd->m_pSamSysParame->m_PowerProtect.startLB = nValue;
    nValue = ui->edit_lw->text().toInt();
    pwnd->m_pSamSysParame->m_PowerProtect.startLW = nValue;
    nValue = ui->edit_length_lb->text().toInt();
    pwnd->m_pSamSysParame->m_PowerProtect.lengthLB = nValue;
    nValue = ui->edit_length_lw->text().toInt();
    pwnd->m_pSamSysParame->m_PowerProtect.lengthLW = nValue;
    accept();
}

void PowerProtectDlg::on_btn_cancel_clicked()
{
    reject();
}

void PowerProtectDlg::on_btn_help_clicked()
{
    pwnd->loadHelpHtm(TREE_DOWNPOWER);
}
