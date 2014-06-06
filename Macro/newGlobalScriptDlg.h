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
    int iOpenType;//1-��ʾ�½���2-��ʾ�����޸�
    int iRowIndex; //�޸������±꣬-1Ϊ�½�������Ϊ�޸��±�
    bool binitFlag; //��ʼ����־
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
