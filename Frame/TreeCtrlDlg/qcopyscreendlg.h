#ifndef QCOPYSCREENDLG_H
#define QCOPYSCREENDLG_H
#include "ui_qcopyscreendlg.h"
#include <QDialog>

namespace Ui {
    class QCopyScreenDlg;
}

class QCopyScreenDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QCopyScreenDlg(QWidget *parent = 0);
    ~QCopyScreenDlg();

public:
    Ui::QCopyScreenDlg *ui;

private slots:
    void on_pushButton_cancle_clicked();
    void on_pushButton_ok_clicked();
};

#endif // QCOPYSCREENDLG_H
