#ifndef INSERTALARM_H
#define INSERTALARM_H

#include <QDialog>
#include "Frame/qprogectmanager.h"
namespace Ui {
    class InsertAlarm;
}

class InsertAlarm : public QDialog
{
    Q_OBJECT

public:
    explicit InsertAlarm(stAlarm alarm,QWidget *parent = 0);
    ~InsertAlarm();

    QVector <Keyboard> getAddrs();
    QList<stAlarm > getAlarms();
	void initUi();
    bool isDigitString(const QString& src);

private:
    Ui::InsertAlarm *ui;
    stAlarm m_alarm;
    E_ALARM_CONDTION m_type;
    int languageCount;

private slots:
    void on_groupBox_4_clicked(bool checked);
    void on_btn_del_clicked();
    void on_btn_add_clicked();
    void on_check_print_clicked(bool checked);
    void on_check_sms_clicked(bool checked);
 void on_openSceneClicked(bool checked);
    void on_language_changed(int index);
    void on_edit_msg_editingFinished();
    void on_btn_cancel_clicked();
    void on_btn_ok_clicked();
    void on_combo_Condtion_currentIndexChanged(int index);
    void on_btn_addr_clicked();
    void on_combo_datatype_currentIndexChanged(int index);
};

#endif // INSERTALARM_H
