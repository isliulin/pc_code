#ifndef QDOTDIALOG_H
#define QDOTDIALOG_H
#include "ui_qdotdialog.h"
#include <QDialog>

namespace Ui {
    class QDotDialog;
}

class QDotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QDotDialog(QWidget *parent = 0);
    ~QDotDialog();
    Keyboard dot_address;

public:
    Ui::QDotDialog *ui;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
};

#endif // QDOTDIALOG_H
