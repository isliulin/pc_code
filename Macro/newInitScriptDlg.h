#ifndef NEWINITSCRIPTDLG_H
#define NEWINITSCRIPTDLG_H

#include <QDialog>

namespace Ui {
    class newInitScriptDlg;
}

class newInitScriptDlg : public QDialog
{
    Q_OBJECT

public:
    explicit newInitScriptDlg(int Type,int iIndex,QWidget *parent = 0);
    ~newInitScriptDlg();

private:
    Ui::newInitScriptDlg *ui;
private:
    int iOpenType;//1-标示新建，2-标示属性修改
    int iRowIndex; //修改属性下标，-1为新建，否则为修改下标
    bool binitFlag; //初始化标志
private:
    void initDlgParament();
    bool isInputRight();
private slots:
    void on_btn_new_clicked();
    void on_Cancel_clicked();
    void on_Ok_clicked();
};

#endif // NEWINITSCRIPTDLG_H
