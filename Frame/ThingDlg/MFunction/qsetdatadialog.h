#ifndef QSETDATADIALOG_H
#define QSETDATADIALOG_H
#include "ui_qsetdatadialog.h"
#include <QDialog>

namespace Ui {
    class QSetDataDialog;
}

class QSetDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QSetDataDialog(int iType,QWidget *parent = 0);
    ~QSetDataDialog();
    Keyboard setData_address;
public:
    Ui::QSetDataDialog *ui;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
};

#endif // QSETDATADIALOG_H
