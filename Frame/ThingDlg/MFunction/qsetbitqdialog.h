#ifndef QSETBITQDIALOG_H
#define QSETBITQDIALOG_H
#include "ui_qsetbitqdialog.h"
#include <QDialog>

namespace Ui {
    class QSetBitQDialog;
}

class QSetBitQDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QSetBitQDialog(int iType,QWidget *parent = 0);
    ~QSetBitQDialog();

public:
    Ui::QSetBitQDialog *ui;
    Keyboard  setBit_address;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
public:
    int iType; //功能类型
private:
    QString sFunName; //功能名称
};

#endif // QSETBITQDIALOG_H
