#ifndef EDITUSERDLG_H
#define EDITUSERDLG_H

#include <QDialog>
#include "Frame/qprogectmanager.h"
namespace Ui {
    class EditUserDlg;
}

class EditUserDlg : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserDlg(int iType,QWidget *parent = 0);
    ~EditUserDlg();
    void init();

public:
    UserPermiss m_user;
    QStringList m_groupNames;

private:
    Ui::EditUserDlg *ui;
     int iOpenType; //-1标示新建，大于等于0的数表示打开属性修改
private:
     bool isNameRight();
private slots:
    void on_btn_cancel_clicked();
    void on_btn_ok_clicked();
};

#endif // EDITUSERDLG_H
