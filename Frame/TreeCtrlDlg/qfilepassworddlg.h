#ifndef QFILEPASSWORDDLG_H
#define QFILEPASSWORDDLG_H

#include <QDialog>

namespace Ui {
    class QFilePassWordDlg;
}

class QFilePassWordDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QFilePassWordDlg(QString FilePassword,QWidget *parent);
    ~QFilePassWordDlg();
QString password;
private:
    Ui::QFilePassWordDlg *ui;

private slots:
    void on_CancelBtn_clicked();
    void on_OKBtn_clicked();
};

#endif // QFILEPASSWORDDLG_H
