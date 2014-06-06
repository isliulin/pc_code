#ifndef ALARMDLG_H
#define ALARMDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QButtonGroup>
#include <QComboBox>
#include <QLabel>
#include "Frame/qprogectmanager.h"
namespace Ui {
    class AlarmDlg;
}

class AddWidget : public QWidget
{
    Q_OBJECT

public:
    QLineEdit   *pEdit;
    QPushButton *pBtn;

public:
    Keyboard addr;
    bool addType;
    inline void SetAddrType(bool type)
    {addType = type;}

public:
    AddWidget(int width = 100, int height = 30,bool type = false, QWidget* parent = 0);
    ~AddWidget();
    QString getString();
    void setEditFocus(QString text);
    bool check(bool type);
private slots:
    void btnAddr();
};

class CondWidget : public QWidget
{
    Q_OBJECT

public:
    QLineEdit *pEdit;
    QLabel    *pLabel;
    QComboBox *pCombox;

public:
    CondWidget(int width = 100, int height = 30, QWidget* parent = 0);
    ~CondWidget();
    void SetValues(QString sAddr,QString sRel,QString sValue);
    QString getString();
private slots:
};

class AlarmDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmDlg(QWidget *parent = 0);
    ~AlarmDlg();
    void CellDClick_Bit(int row, int column);
    void CellDClick_Word(int row, int column);
    void CellChanged_Bit(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void CellChanged_Word(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void Init(ALARM_GROUP alarmGroup);
    void addAlarm(int row);
    void EditAlarm(int row);
    stAlarm getAlarm(int row);
    QString CondString(stAlarm alarm);
public:
    ALARM_GROUP alarmGrp;
    QVector<stAlarm >alarms;
private:
    Ui::AlarmDlg *ui;
    QButtonGroup *RadioGroup;
    bool bInit;
    bool bDisableSlot;
    int languageCount;
    void accept();
    //bool event(QEvent *event);
    bool eventFilter ( QObject * o, QEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void keyPressEvent ( QKeyEvent * event );
private slots:
    void on_btn_help_clicked();
    void on_btn_cancel_clicked();
    void on_btn_ok_clicked();
    void on_btn_reset_clicked();
    void on_combo_language_currentIndexChanged(int index);
    void on_btn_bat_clicked();
    void tableFocusOut();
    void radioChanged(int index);
    void on_table_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void on_table_cellDoubleClicked(int row, int column);
};

#endif // ALARMDLG_H
