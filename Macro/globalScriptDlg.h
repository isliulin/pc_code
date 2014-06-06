#ifndef GLOBALSCRIPTDLG_H
#define GLOBALSCRIPTDLG_H

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
    class globalScriptDlg;
}

class globalScriptDlg : public QDialog
{
    Q_OBJECT

public:
    explicit globalScriptDlg(QWidget *parent = 0);
    ~globalScriptDlg();

private:
    Ui::globalScriptDlg *ui;
private:
    void insertDataToTable(int iIndex);
    void alterDataToTable(int iIndex);
private slots:
    void on_table_itemPressed(QTableWidgetItem* item);
    void on_table_cellDoubleClicked(int row, int column);
    void on_helpbtn_clicked();
    void on_exsitbtn_clicked();
    void on_alterbtn_clicked();
    void on_deletebtn_clicked();
    void on_newadd_clicked();

    void openScriptLib();
};

#endif // GLOBALSCRIPTDLG_H
