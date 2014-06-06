#ifndef QTRENDATIME_H
#define QTRENDATIME_H

#include <QWidget>
#include <color.h>
#include "view/qtrendattr.h"
#include "ui_qtrendatime.h"

namespace Ui {
    class QTrendaTime;
}

class QTrendaTime : public QWidget
{
    Q_OBJECT

public:
    explicit QTrendaTime(QWidget *parent = 0);
    ~QTrendaTime();

public:
    Ui::QTrendaTime *ui;
    int             m_nOldFocus;

public:
    void Init(QTrendAttr *pItem);
    int getTime_near();

public://时间显示
    //TimeUnitType    m_eTimeUnit;    //X轴时间单位 //现在不要了
    TimeType        m_eTimeFormat;  //时间格式
    DateType        m_eDateFormat;  //日期格式
    FontType        m_eFontType;    //字体类型
    TxtAttrType     m_eTxtAttr;     //文本属性
    CurveStartType  m_eStart;       //那种时间采集方式
    //TimeUnitType    m_eCurTime;     //从开始用的时间单位
    bool            m_bXMarked;     //是否X轴标注
    short           m_nFontSize;    //字体大小
    QColor          m_nMarkedColor; //标注颜色
    int             m_nTimeLen;     //最近时间
    TimeUnitType    m_eTimeUnitNear;//最近时间单位
    QDate           m_dFromDate;    //起始日期
    QTime           m_tFromTime;    //起始时间
    QDate           m_dToDate;      //终止日期
    QTime           m_tToTime;      //终止时间
    Keyboard        m_kbFrom;       //起始时间地址
    Keyboard        m_kbTo;         //终止时间地址
    bool            m_bDateFormat;  //是否显示日期格式
    bool            m_bTimeFormat;  //是否显示时间格式

private:
    void cleanOldFocus();
    bool strIsNumber(QString &);

private slots:
    void on_checkBox_dateFormat_clicked(bool checked);
    void on_checkBox_timeFormat_clicked(bool checked);
    void on_pushButton_from_clicked();
    void on_timeEdit_2_editingFinished();//到 时间
    void on_dateEdit_2_editingFinished();//到 日期
    void on_timeEdit_editingFinished();//从 时间
    void on_dateEdit_editingFinished();//从 日期
    void on_radioButton_clicked();//从。。。。到。。。。
    void on_comboBox_dateFormat_currentIndexChanged(int index);//日期格式
    void on_comboBox_timeFormat_currentIndexChanged(int index);//时间格式
    void on_pushButton_color_clicked();                        //标注颜色
    void set_pushButton_showColor(const QColor &);
    void on_comboBox_fontType_currentIndexChanged(int index);  //字体类型
    void on_spinBox_fontSize_valueChanged(int value);           //字体大小
    void on_comboBox_fontTxtAttr_currentIndexChanged(int index);//文本属性
    void on_checkBox_hideMarked_clicked(bool checked);          //是否X轴标注
    //void on_comboBox_timeUnit_currentIndexChanged(int index);   //X轴时间单位
    void on_radioButton_diskBegin_clicked();                    //从存盘数据开始
    void on_radioButton_near_clicked();                         //最近
    void on_comboBox_near_currentIndexChanged(int index);       //最近时间单位

public slots:
    void setTrendType(bool bIsHistoryTrend);

private slots:
    void on_radioButton_from_clicked();
    void on_pushButton_to_clicked();
};

#endif // QTRENDATIME_H
