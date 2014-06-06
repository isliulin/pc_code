#ifndef QUSERINPUTDIALOG_H
#define QUSERINPUTDIALOG_H
#include "ui_quserinputdialog.h"
#include <QDialog>

namespace Ui {
    class QUserInputDialog;
}

class QUserInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QUserInputDialog(QWidget *parent = 0);
    ~QUserInputDialog();
    Keyboard intput_address;

public:
    Ui::QUserInputDialog *ui;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
};

#endif // QUSERINPUTDIALOG_H
