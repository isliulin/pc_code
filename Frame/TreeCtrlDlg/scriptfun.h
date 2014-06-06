#ifndef SCRIPTFUN_H
#define SCRIPTFUN_H

#include <QDialog>
#include  "Frame\MainWindow.h"

namespace Ui {
    class scriptFun;
}

class scriptFun : public QDialog
{
    Q_OBJECT

public:
    explicit scriptFun(int type, int index, bool bNewScreen, QWidget *parent = 0);
    ~scriptFun();

private:
    Ui::scriptFun *ui;

public:
    int  openType;
    int  iRowIndex;
    bool bInit;
    bool bCheckType;
    Keyboard CtrlAddr;

public:
    SCRIPT_PROP script;
    bool isInputRight();

private slots:
    void on_pushButton_addr_clicked();
    void on_checkBox_type_clicked(bool checked);
    void on_pushButton_cancel_clicked();
    void on_pushButton_sure_clicked();
	void on_add_macro();
};

#endif // SCRIPTFUN_H
