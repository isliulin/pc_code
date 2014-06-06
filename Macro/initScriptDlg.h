#ifndef INITSCRIPTDLG_H
#define INITSCRIPTDLG_H

#include <QDialog>

namespace Ui {
    class initScriptDlg;
}

class initScriptDlg : public QDialog
{
    Q_OBJECT

public:
    explicit initScriptDlg(QWidget *parent = 0);
    ~initScriptDlg();

private:
    Ui::initScriptDlg *ui;
private:
    void insertDataToTable(int iIndex);
    void alterDataToTable(int iIndex);

private slots:
    void on_table_cellDoubleClicked(int row, int column);
    void on_table_itemPressed(QTableWidgetItem* item);
    void on_helpbtn_clicked();
    void on_exsitbtn_clicked();
    void on_alterbtn_clicked();
    void on_deletebtn_clicked();
    void on_newadd_clicked();
};

#endif // INITSCRIPTDLG_H
