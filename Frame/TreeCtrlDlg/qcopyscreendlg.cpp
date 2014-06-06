#include "qcopyscreendlg.h"
#include <QMessageBox>
#include  "Frame\mainwindow.h"
extern  MainWindow *pwnd;
QCopyScreenDlg::QCopyScreenDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QCopyScreenDlg)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
}

QCopyScreenDlg::~QCopyScreenDlg()
{
    delete ui;
}

void QCopyScreenDlg::on_pushButton_ok_clicked()
{
    bool is_HaveName;
    if(ui->lineEdit->text()=="")
    {
        QMessageBox box(this);
        box.setText(tr("画面名字不可以为空，请输入一个名字"));
        box.exec();
        ui->lineEdit->setFocus(Qt::ActiveWindowFocusReason);
        return;
    }

  is_HaveName=pwnd->review_ScreenAndWindow_Name(ui->lineEdit->text());
  ui->lineEdit->setFocus(Qt::ActiveWindowFocusReason);

  if(is_HaveName)
  {
   return;
  }
  else
  {
      accept();
  }

}

void QCopyScreenDlg::on_pushButton_cancle_clicked()
{
  reject();
}
