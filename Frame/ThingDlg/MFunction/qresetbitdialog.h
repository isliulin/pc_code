#ifndef QRESETBITDIALOG_H
#define QRESETBITDIALOG_H
#include "ui_qresetbitdialog.h"

#include <QDialog>

namespace Ui {
    class QResetBitDialog;
}

class QResetBitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QResetBitDialog(QWidget *parent = 0);
    ~QResetBitDialog();

    Keyboard retBit_address;
public:
    Ui::QResetBitDialog *ui;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
};

#endif // QRESETBITDIALOG_H
