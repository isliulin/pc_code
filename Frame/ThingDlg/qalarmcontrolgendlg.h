#ifndef QALARMCONTROLGENDLG_H
#define QALARMCONTROLGENDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include "ui_qalarmcontrolgendlg.h"
#include <QGraphicsScene>
#include "view/alarmitem.h"
#include "view/hisalarmitem.h"


namespace Ui {
    class QAlarmControlGenDlg;
}

class QAlarmControlGenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QAlarmControlGenDlg(QWidget *parent = 0);
    ~QAlarmControlGenDlg();
    bool nFlg;
public://private:
    Ui::QAlarmControlGenDlg *ui;
    void Init(QGraphicsItem *pItem);
    void AlarmControlGenSave();
    bool isAllRight();
    Keyboard Control_Address_Keyboard;
public slots:
    void on_If_Use_Control_Add_clicked(bool checked);

private slots:
    void on_btn_groupset_clicked();
    void on_Receive_Note_Color_clicked();
    void on_Clear_Alarm_Color_clicked();
    void on_m_fontcolorbtn_clicked();
    void on_m_ttextcolorbtn_clicked();
    void on_m_tbackcolorbtn_clicked();
    void on_m_linecolorbtn_clicked();
    void on_m_fframcolorbtn_clicked();
    void on_m_fbackcolorbtn_clicked();
    void on_m_cleartime_textChanged(QString sContent);
    void on_m_cleardate_textChanged(QString sContent);
    void on_If_Clean_Alarm_Time_clicked(bool checked);
    void on_If_Clean_Alarm_Data_clicked(bool checked);
    void on_Control_Add_Keyboard_clicked();
    void on_m_tfontcmb_currentIndexChanged(int index);
    void on_m_tfontsizecmb_currentIndexChanged(int index);
    void on_m_msgedit_textChanged(QString );
    void on_m_dateedit_textChanged(QString );
    void on_m_timeedit_textChanged(QString );
    void on_m_languagecmb_currentIndexChanged(int index);
    void on_m_datecheck_clicked();
    void on_m_timecheck_clicked();
    void setfbackcolorbtnColor(const QColor & mColor);       //设置边框色
    void setfframcolorbtnColor(const QColor & mColor);       //设置边框色
    void setlinecolorbtnColor(const QColor & mColor);       //设置边框色
    void settbackcolorbtnColor(const QColor & mColor);       //设置边框色
    void setttextcolorbtnColor(const QColor & mColor);       //设置边框色
    void setfontcolorbtnColor(const QColor & mColor);       //设置边框色
    void setClear_AlarmColor(const QColor & mColor);       //设置边框色
    void setReceive_Note_ColorColor(const QColor & mColor);       //设置边框色

public:


    stAlarmItemPro alarmPro;
	QVector<stAlarmTitles> TitleText;
    bool bAll;
    QStringList groupNames;

public:
    void InitParament();
};

#endif // QALARMCONTROLGENDLG_H
