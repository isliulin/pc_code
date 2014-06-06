#ifndef NEWDATACONTROL_H
#define NEWDATACONTROL_H

#include <QDialog>
#include "Frame/qprotocoltool.h"
#include <QTableView>
#include <QStandardItemModel>
#include "subdatacontrol.h"

namespace Ui {
    class NewDataControl;
}

class NewDataControl : public QDialog
{
    Q_OBJECT

public:
    explicit NewDataControl(QWidget *parent = 0);
    ~NewDataControl();

    void InitScreenIndex(QComboBox *Cbox, QString str);

public:
    QStandardItemModel *model;
    QAction *New_action;
    QAction *Edit_action;
    QAction *Del_action;
    QMenu   menu;
    int     currentRow;//当前选择的行

private:
    Ui::NewDataControl *ui;

private:
    Keyboard ScreenAddr;
    Keyboard RecipeAddr;
    Keyboard LanguageAddr;
    Keyboard WCtrlAddr;

private slots:
    void on_pushButton_help_clicked();
    void on_checkBox_clicked(bool checked);
    void on_pushButton_addrBegin_4_clicked();
    void on_pushButton_addrBegin_3_clicked();
    void on_pushButton_addrBegin_2_clicked();
    void on_pushButton_addrBegin_clicked();
    void on_groupBox_2_clicked(bool checked);
    void on_checkBox_3_clicked(bool checked);
    void on_checkBox_2_clicked(bool checked);
    void on_checkBox_1_clicked(bool checked);
    void on_pushButton_cancel_clicked();
    void on_pushButton_sure_clicked();

    void newTableItem();
    void editTableItem();
    void delTableItem();
    void table_rightMenu(QModelIndex);
    void tableThing();
    void TableDouble(QModelIndex);
};

#endif // NEWDATACONTROL_H
