#include "qfilepassworddlg.h"
#include "ui_qfilepassworddlg.h"

QFilePassWordDlg::QFilePassWordDlg(QString FilePassword,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QFilePassWordDlg)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    password=FilePassword;
    this->setWindowTitle(tr("����"));
    ui->OKBtn->setDefault(true);
    ui->FilePassWordEntry->setFocus();
}

QFilePassWordDlg::~QFilePassWordDlg()
{
    delete ui;
}

void QFilePassWordDlg::on_OKBtn_clicked()
{
    if(password != ui->FilePassWordEntry->text())
    {
        QMessageBox box(QMessageBox::Warning,PRO_FULL_NAME,tr("��������ȷ���ļ����룡"),
                               0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
               box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
               box.exec();
               return;

    }
    accept();
}

void QFilePassWordDlg::on_CancelBtn_clicked()
{
    this->close();
}
