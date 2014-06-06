#ifndef ADDCMDDLG_H
#define ADDCMDDLG_H

#include <QDialog>
#include "schedulers.h"
class ScheItem;
namespace Ui {
    class AddCmdDLg;
}

class AddCmdDLg : public QDialog
{
    Q_OBJECT

public:
    explicit AddCmdDLg(E_WEEKDAY weekday,ScheItem *item = NULL,QWidget *parent = 0);
    ~AddCmdDLg();

    void resetEdit();
    QList<ScheItem> m_items;
private:
    Ui::AddCmdDLg *ui;


private slots:
    void on_comboBox_dataType_currentIndexChanged(int index);
    void on_btn_cancel_clicked();
    void on_btn_CtlAddr_clicked();
    void on_btn_ValueAddr_clicked();
    void on_btn_ActionAddr_clicked();
    void on_btn_wordAddr_const_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_radio_3_clicked(bool checked);
    void on_radio_4_clicked(bool checked);
    void on_radio_2_clicked(bool checked);
    void on_radio_clicked(bool checked);
    void on_btn_ok_clicked();
};

#endif // ADDCMDDLG_H
