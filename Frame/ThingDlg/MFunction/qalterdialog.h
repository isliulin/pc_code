#ifndef QALTERDIALOG_H
#define QALTERDIALOG_H
#include "ui_qalterdialog.h"
#include <QDialog>

namespace Ui {
    class QAlterDialog;
}

class QAlterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QAlterDialog(QWidget *parent = 0);
    ~QAlterDialog();
    Keyboard alter_address;

public:
    Ui::QAlterDialog *ui;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
};

#endif // QALTERDIALOG_H
