#ifndef QSCREENDIALOG_H
#define QSCREENDIALOG_H
#include "ui_qscreendialog.h"
#include <QDialog>
#include <QButtonGroup>
namespace Ui {
    class QScreenDialog;
}

class QScreenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QScreenDialog(QWidget *parent = 0);
    ~QScreenDialog();

    QButtonGroup  *btn;
public:
    Ui::QScreenDialog *ui;

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void BtnSelect(int);
};

#endif // QSCREENDIALOG_H
