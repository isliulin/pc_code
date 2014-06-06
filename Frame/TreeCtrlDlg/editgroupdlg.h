#ifndef EDITGROUPDLG_H
#define EDITGROUPDLG_H

#include <QDialog>
#include "Frame/qprogectmanager.h"

namespace Ui {
    class EditGroupDlg;
}

class EditGroupDlg : public QDialog
{
    Q_OBJECT

public:
    explicit EditGroupDlg(int iType,QWidget *parent = 0);
    ~EditGroupDlg();
    void init();

public:
    GroupPermiss m_group;
private:
    Ui::EditGroupDlg *ui;
    int iOpenType; //-1标示新建，大于等于0的数表示打开属性修改
private:
    bool isNameRight();
private slots:
    void on_tableWidget_cellClicked(int row, int column);
    void on_checkBox_clicked(bool checked);
    void on_btn_cancel_clicked();
    void on_btn_ok_clicked();
};

#endif // EDITGROUPDLG_H
