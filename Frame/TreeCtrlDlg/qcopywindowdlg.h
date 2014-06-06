#ifndef QCOPYWINDOWDLG_H
#define QCOPYWINDOWDLG_H
#include "ui_qcopywindowdlg.h"
#include <QDialog>

namespace Ui {
    class QCopyWindowDlg;
}

class QCopyWindowDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QCopyWindowDlg(QWidget *parent = 0);
    ~QCopyWindowDlg();

public:
    Ui::QCopyWindowDlg *ui;

private slots:
    void on_pushButton_cancle_clicked();
    void on_pushButton_ok_clicked();
};

#endif // QCOPYWINDOWDLG_H
