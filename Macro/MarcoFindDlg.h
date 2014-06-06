#ifndef MARCOFINDDLG_H
#define MARCOFINDDLG_H

#include <QDialog>

namespace Ui {
    class MarcoFindDlg;
}

class MarcoFindDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MarcoFindDlg(QWidget *parent = 0);
    ~MarcoFindDlg();

private:
    Ui::MarcoFindDlg *ui;

public:
    QString libName;    //¿âÃû
    QString funcName;   //º¯ÊýÃû

private slots:
    void on_pushButton_cancel_clicked();
    void on_m_Ok_clicked();
};

#endif // MARCOFINDDLG_H
