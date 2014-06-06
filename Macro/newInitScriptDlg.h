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
    int iOpenType;//1-��ʾ�½���2-��ʾ�����޸�
    int iRowIndex; //�޸������±꣬-1Ϊ�½�������Ϊ�޸��±�
    bool binitFlag; //��ʼ����־
private:
    void initDlgParament();
    bool isInputRight();
private slots:
    void on_btn_new_clicked();
    void on_Cancel_clicked();
    void on_Ok_clicked();
};

#endif // NEWINITSCRIPTDLG_H
