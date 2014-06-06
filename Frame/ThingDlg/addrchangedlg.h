#ifndef ADDRCHANGEDLG_H
#define ADDRCHANGEDLG_H

#include <QDialog>
#include "Frame/mainwindow.h"

namespace Ui {
    class addrChangeDlg;
}

class addrChangeDlg : public QDialog
{
    Q_OBJECT

public:
    explicit addrChangeDlg(AddrMsg* pAMsg, int addrNum, QWidget *parent = 0);
    ~addrChangeDlg();

public:
    short    replaceType;//那种方式替换
    QString  replaceAddr;//替换地址
    short    type;
    Keyboard key;

private:
    Ui::addrChangeDlg *ui;

private slots:
    void on_pushButton_addr_clicked();
    void on_pushButton_cancel_clicked();
    void on_pushButton_sure_clicked();
};

#endif // ADDRCHANGEDLG_H
