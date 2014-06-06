#ifndef QCHARTMECOLOR_H
#define QCHARTMECOLOR_H

#include <QWidget>
#include "color.h"
#include "view/ChartItem.h"
#include "Frame/DrawDlg/LoadShape.h"

namespace Ui {
    class QChartMeColor;
}

class QChartMeColor : public QWidget
{
    Q_OBJECT

public:
    explicit QChartMeColor(QWidget *parent = 0);
    ~QChartMeColor();
    void Init(ChartItem *pItem);
    bool MeterColorSave(struct METER_INFORMATION &meter_st);
    QString onGetShapeName();

public:
    QString nPointColor;//�Ǳ�ָ����ɫ
    QString nBackColor; //�Ǳ�����ɫ
    int nMeterType;//����ѡ����Ǳ������±�
    bool bInitFlag;

public slots:
    void setdataRange(double dMax, double dMin,int type);
    void onGetPointType(int &nType);
private:
    Ui::QChartMeColor *ui;
    Keyboard AlarmMin_Address_Keyboard;
    Keyboard AlarmMax_Address_Keyboard;
    QString shapename;

signals:
    void SetMeterPointColor();//����ָ����ɫ
    void SetMeterBackColor();//���ñ�����ɫ
    void reDrawMeter();
private slots:
    void on_m_PointTypecbBox_currentIndexChanged(int index);
    void on_m_AddressMax_EntryBtn_clicked();
    void on_m_AddressMin_EntryBtn_clicked();
    void on_m_Alarmshapecolorbtn_clicked();
    void on_m_Alarmshowcolorbtn_clicked();
    void on_m_AlarmcbBox_currentIndexChanged(int index);
    void on_m_alarmckBox_clicked();
    void on_load_shapeBtn_clicked();
    void on_m_backcolorbtn_clicked();
    void on_m_showcolorbtn_clicked();
    void setshowcolorbtnColor(const QColor &mColor);//����ָ����ɫ
    void setbackcolorbtnColor(const QColor &mColor);//���ñ�����ɫ
    void setAlarmShowBtnColor(const QColor &mColor);
    void setAlarmShapeBtnColor(const QColor &mColor);
};

#endif // QCHARTMECOLOR_H
