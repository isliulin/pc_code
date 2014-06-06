#include "newencryaccess.h"
#include "ui_newencryaccess.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

//--------���ʼ���---------------------------------------
//bool            m_bEncryAccess;         //�Ƿ����÷��ʼ���
//QString         m_strAccessPassword;    //��������
NewEncryAccess::NewEncryAccess(QWidget *parent):QDialog(parent),ui(new Ui::NewEncryAccess)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setFixedSize(size());
    setWindowTitle(tr("���ʼ���"));

    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bEncryAccess == false)
    {
        ui->groupBox->setChecked(false);
    }
    else
    {
        ui->groupBox->setChecked(true);
    }

    QRegExp regx("^\\w+$");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEdit);
    ui->lineEdit->setValidator( validator );
    ui->lineEdit->setEchoMode(QLineEdit::Password);

    ui->lineEdit->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strAccessPassword);
}

NewEncryAccess::~NewEncryAccess()
{
    delete ui;
}

void NewEncryAccess::on_pushButton_sure_clicked()
{
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bEncryAccess = ui->groupBox->isChecked();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strAccessPassword = ui->lineEdit->text();

    this->accept();
}

void NewEncryAccess::on_pushButton_cancel_clicked()
{
    this->close();
}
