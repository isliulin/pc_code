#ifndef NEWGLOBALSCRIPTDLG_H
#define NEWGLOBALSCRIPTDLG_H

#include <QDialog>
#include <Frame/qprogectmanager.h>

namespace Ui {
    class newGlobalScriptDlg;
}

class newGlobalScriptDlg : public QDialog
{
    Q_OBJECT

public:
    explicit newGlobalScriptDlg(int Type,int iIndex,QWidget *parent = 0);
    ~newGlobalScriptDlg();

private:
    Ui::newGlobalScriptDlg *ui;
private:
    int iOpenType;//1-标示新建，2-标示属性修改
    int iRowIndex; //修改属性下标，-1为新建，否则为修改下标
    bool binitFlag; //初始化标志
    Keyboard CtrlAddr;
private:
    void initDlgParament();
    bool isInputRight();
private slots:
    void on_btn_new_clicked();
    void on_bctrlcheck_clicked(bool checked);
    void on_Cancel_clicked();
    void on_Ok_clicked();
    void on_addrbtn_clicked();
};

#endif // NEWGLOBALSCRIPTDLG_H
