#ifndef SCHEDULEDLG_H
#define SCHEDULEDLG_H

#include <QDialog>
#include "stablemodel.h"

namespace Ui {
    class ScheduleDlg;
}
class QTableView;
class ScheduleDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ScheduleDlg(QWidget *parent = 0);
    ~ScheduleDlg();

private:
    Ui::ScheduleDlg *ui;
    QVector<QTableView *> views;
    QTableView *currentView;
    StableModel *model;
    QWidget *currentWidget;
    E_WEEKDAY weekday;
    Schedulers *schedulers;

private slots:
    void on_btn_AddMulti_clicked();
    void on_btn_continue_clicked();
    void on_btn_Del_clicked();
    void on_btn_Add_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_itemDoubleClick(QModelIndex index);
};

#endif // SCHEDULEDLG_H
