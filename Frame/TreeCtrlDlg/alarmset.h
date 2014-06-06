#ifndef ALARMSET_H
#define ALARMSET_H

#include <QDialog>
#include "Frame/qprogectmanager.h"
namespace Ui {
    class AlarmSet;
}

class AlarmSet : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmSet(QWidget *parent = 0);
    ~AlarmSet();

    void Init(ALARM_GROUP alarmGroup,int index);
    QString CondString(stAlarm alarm);
    void setAlarms(QList<stAlarm> mAlarms);
    void setTableItem(stAlarm cAlarm);
    void removeRow(int row);

private:
    Ui::AlarmSet *ui;
    int languageCount;

    bool bInit;
	int m_index;
public :
    ALARM_GROUP alarmGrp;
private slots:
    void on_btn_help_clicked();
    void on_btn_deleteall_clicked();
    void on_btn_delete_clicked();
    void on_btn_add_clicked();
    void on_table_cellDoubleClicked(int row, int column);
    void on_btn_cancel_clicked();
    void on_btn_ok_clicked();
    void reloadMsgs(int languageIndex);
};

#endif // ALARMSET_H
