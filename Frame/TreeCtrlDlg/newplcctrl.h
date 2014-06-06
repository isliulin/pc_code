#ifndef NEWPLCCTRL_H
#define NEWPLCCTRL_H

#include <QDialog>

namespace Ui {
    class NewPLCCtrl;
}

class NewPLCCtrl : public QDialog
{
    Q_OBJECT

public:
    explicit NewPLCCtrl(int index ,QWidget *parent = 0);
    ~NewPLCCtrl();
	void setConnect(stConnect con,bool bInit = false);
	void refreshUi();

public:
	stConnect m_Connect;
private:
    Ui::NewPLCCtrl *ui;
    int m_Index;

private slots:
    void on_m_LinkFromScreenradioBtn_clicked(bool checked);
    void on_m_LinkPLCradioBtn_clicked(bool checked);
    void on_m_FromScreenradioBtn_clicked(bool checked);
    void on_m_MainScreenradioBtn_clicked(bool checked);
    void on_check_transmit_clicked(bool checked);
    void on_pushButton_sure_2_clicked();
    void showIpLabel(bool checked);
    void on_combo_serialport_currentIndexChanged(int index);
    void on_check_transmit_stateChanged(int checked);
    void on_DefaultSet_clicked();
    void on_pushButton_cancel_clicked();
    void on_pushButton_sure_clicked();
};

#endif // NEWPLCCTRL_H
