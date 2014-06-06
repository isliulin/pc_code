#ifndef QCHARTCOMMON_H
#define QCHARTCOMMON_H

#include <QWidget>
#include "Frame/addressinputdialog.h"
#include "view/ChartItem.h"


namespace Ui {
    class QChartCommon;
}

class QChartCommon : public QWidget
{
    Q_OBJECT

public:
    explicit QChartCommon(QWidget *parent = 0);
    ~QChartCommon();
    void Init(ChartItem *pItem = NULL);
    bool CommonGenSave(struct COMMON_INFORMATION &common_st);
    void setdataRange(double dMax, double dMin,int type);
    QGraphicsItem * pCopyItem;
    Keyboard Monitor_Address_Keyboard;
    Keyboard m_minAddress_EntryBtn;
    Keyboard m_maxAddress_EntryBtn;
    bool holecheck;
    int ndirection;//柱状图显示方向
    int nShapeType;//图形类型 0：[柱状图]、1：[圆形图]、2：[半圆图]和 3：[槽状图]

signals:
    void meterclick();//仪表按钮选中发送该消息重载tab标签页
    void directionchange();//方向改变发送消息
    void setCommonShapeType();//发送普通图形类型改变消息
    void drawCenterCircle(bool bCircle, int nRadiu);
    void setRange(double dMax, double dMin, int type);//type: 0浮点型
    void reDrawBar();//发送重新绘制柱状图槽型图消息
    void enablePointType(bool bable);//true 启用   false 禁用

private:
    Ui::QChartCommon *ui;
    bool bInitFlag;
    bool bValueChange;//是否发送半径改变消息

public slots:
    void onGetDirection(int &nIndex);
    void onGetroleCheck(bool &bCheck, int &nRadius);
    void onGetdataRange(double &dMin, double &dMax);//获取最大最小值
    void onGetPointType(int &nType);//获取圆是否画指针，0：显示填充，1：显示指针
    void onGetStartAngle(short &nStart,short &nSpan);
    void onGetCircleAlpha(short &nAlpha);
    void onGetShowFrame(bool &bShowFrame);
private slots:
    void on_m_SpanAngleSpBox_valueChanged(int );
    void on_m_StartAngleSpBox_valueChanged(int );
    void on_max_numEdit_textChanged(QString );
    void on_min_numEdit_textChanged(QString );
    void on_start_Checkbox_clicked(bool checked);
    void on_Date_type_currentIndexChanged(int index);
    void on_hole_Checkbox_clicked(bool checked);
    void on_radiu_Spinbox_valueChanged(int );
    void on_filling_Checkbox_clicked(bool checked);
    void on_m_maxAddress_EntryBtn_clicked();
    void on_m_minAddress_EntryBtn_clicked();
    void on_range_Combox_currentIndexChanged(int index);
    void on_direct_Combobox_currentIndexChanged(int index);
    void on_type_Combobox_currentIndexChanged(int index);
    void on_symbol_checkBox_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_Monitor_Address_EntryBtn_clicked();
    void on_m_CommonButton_2_clicked();
    void on_m_MeterButton_2_clicked();

    void on_m_checkBox_showFrame_clicked(bool checked);
    void on_m_TransparentspBox_valueChanged(int );
};

#endif // QCHARTCOMMON_H
