#ifndef EXPRESSIONDLG_H
#define EXPRESSIONDLG_H

#include <QDialog>
#include "view/DataDisplayItem.h"
namespace Ui {
    class ExpressionDlg;
}

class ExpressionDlg : public QDialog
{
    Q_OBJECT

public:
    explicit ExpressionDlg(int datatype,Expression exp,QWidget *parent = 0);
    ~ExpressionDlg();
    Expression getExp();
    bool isDouble(QString txt);

private:
    Ui::ExpressionDlg *ui;

    Expression m_Exp;

    QString tempAddr1;
    QString tempAddr2;
    QString tempAddr3;

    QString tempConst1;
    QString tempConst2;
    QString tempConst3;

private slots:
    void on_combo_Type_3_currentIndexChanged(int index);
    void on_combo_Type_2_currentIndexChanged(int index);
    void on_combo_Type_currentIndexChanged(int index);
    void on_btn_addr4_clicked();
    void on_btn_addr3_clicked();
    void on_btn_addr2_clicked();
    void on_btn_addr_clicked();
    void on_btn_cancel_clicked();
    void on_btn_ok_clicked();
    void on_comboBox_changed(int index);
    void on_comboBox_2_changed(int index);
    void on_comboBox_3_changed(int index);
};

#endif // EXPRESSIONDLG_H
