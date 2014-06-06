#ifndef GROUPSELDLG_H
#define GROUPSELDLG_H

#include <QDialog>

namespace Ui {
    class GroupSelDlg;
}

class GroupSelDlg : public QDialog
{
    Q_OBJECT

public:
    explicit GroupSelDlg(QStringList names,bool bSelectAll,QWidget *parent = 0);
    ~GroupSelDlg();
    QStringList getNames(bool &isAll);
    void initTable(QStringList names,bool bSelectAll);

private:
    Ui::GroupSelDlg *ui;


private slots:
    void on_btn_cancel_clicked();
    void on_btn_ok_clicked();
    void chlSelected(int row,int col);
};

#endif // GROUPSELDLG_H
