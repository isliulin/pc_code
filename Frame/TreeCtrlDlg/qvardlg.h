#ifndef QVARDLG_H
#define QVARDLG_H

#include <QDialog>
#include <QVector>
#include <QTableWidgetItem>
#include "ui_qvardlg.h"
#include "Frame/qprogectmanager.h"
namespace Ui {
    class QVardlg;
}

class QVardlg : public QDialog
{
    Q_OBJECT

public:
    explicit QVardlg(QWidget *parent = 0);
    ~QVardlg();
    void init();
    void settableview(VarRecord record,int rows);
    QVector<VarRecord > m_qvcRecordTemp;
private:
    Ui::QVardlg *ui;
    QVector<QTableWidgetItem> m_qvecItem;
    QString connectTypeToStr(int type);
private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem* item);
    void on_m_del_all_clicked();
    void on_m_modify_clicked();
    void on_m_delete_clicked();
    void on_m_create_new_clicked();
};

#endif // QVARDLG_H
