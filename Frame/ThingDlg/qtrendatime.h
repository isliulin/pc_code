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

public://ʱ����ʾ
    //TimeUnitType    m_eTimeUnit;    //X��ʱ�䵥λ //���ڲ�Ҫ��
    TimeType        m_eTimeFormat;  //ʱ���ʽ
    DateType        m_eDateFormat;  //���ڸ�ʽ
    FontType        m_eFontType;    //��������
    TxtAttrType     m_eTxtAttr;     //�ı�����
    CurveStartType  m_eStart;       //����ʱ��ɼ���ʽ
    //TimeUnitType    m_eCurTime;     //�ӿ�ʼ�õ�ʱ�䵥λ
    bool            m_bXMarked;     //�Ƿ�X���ע
    short           m_nFontSize;    //�����С
    QColor          m_nMarkedColor; //��ע��ɫ
    int             m_nTimeLen;     //���ʱ��
    TimeUnitType    m_eTimeUnitNear;//���ʱ�䵥λ
    QDate           m_dFromDate;    //��ʼ����
    QTime           m_tFromTime;    //��ʼʱ��
    QDate           m_dToDate;      //��ֹ����
    QTime           m_tToTime;      //��ֹʱ��
    Keyboard        m_kbFrom;       //��ʼʱ���ַ
    Keyboard        m_kbTo;         //��ֹʱ���ַ
    bool            m_bDateFormat;  //�Ƿ���ʾ���ڸ�ʽ
    bool            m_bTimeFormat;  //�Ƿ���ʾʱ���ʽ

private:
    void cleanOldFocus();
    bool strIsNumber(QString &);

private slots:
    void on_checkBox_dateFormat_clicked(bool checked);
    void on_checkBox_timeFormat_clicked(bool checked);
    void on_pushButton_from_clicked();
    void on_timeEdit_2_editingFinished();//�� ʱ��
    void on_dateEdit_2_editingFinished();//�� ����
    void on_timeEdit_editingFinished();//�� ʱ��
    void on_dateEdit_editingFinished();//�� ����
    void on_radioButton_clicked();//�ӡ�����������������
    void on_comboBox_dateFormat_currentIndexChanged(int index);//���ڸ�ʽ
    void on_comboBox_timeFormat_currentIndexChanged(int index);//ʱ���ʽ
    void on_pushButton_color_clicked();                        //��ע��ɫ
    void set_pushButton_showColor(const QColor &);
    void on_comboBox_fontType_currentIndexChanged(int index);  //��������
    void on_spinBox_fontSize_valueChanged(int value);           //�����С
    void on_comboBox_fontTxtAttr_currentIndexChanged(int index);//�ı�����
    void on_checkBox_hideMarked_clicked(bool checked);          //�Ƿ�X���ע
    //void on_comboBox_timeUnit_currentIndexChanged(int index);   //X��ʱ�䵥λ
    void on_radioButton_diskBegin_clicked();                    //�Ӵ������ݿ�ʼ
    void on_radioButton_near_clicked();                         //���
    void on_comboBox_near_currentIndexChanged(int index);       //���ʱ�䵥λ

public slots:
    void setTrendType(bool bIsHistoryTrend);

private slots:
    void on_radioButton_from_clicked();
    void on_pushButton_to_clicked();
};

#endif // QTRENDATIME_H
