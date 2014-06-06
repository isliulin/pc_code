#ifndef QCHARTMETER_H
#define QCHARTMETER_H

#include <QWidget>
#include "Frame/addressinputdialog.h"
#include "Frame/mainwindow.h"
#include "view/ChartItem.h"



namespace Ui {
    class QChartMeter;
}

class QChartMeter : public QWidget
{
    Q_OBJECT

public:
    explicit QChartMeter(QWidget *parent = 0);
    ~QChartMeter();
    void Init(ChartItem *pItem);
    void OnReDrawMeter();//对仪表进行重绘函数
    void OnSetMeterProperty();//接收仪表颜色界面指针颜色改变消息
    bool MeterGenSave(struct METER_INFORMATION &meter_st);
    void OnDrawScal(QGraphicsItemGroup *pGroup,METER_STRU meter, int nPointCount,int nFontSize,bool bShow);
    void OnDrawPointer(QGraphicsItemGroup *pGroup,METER_STRU meter,bool bShow);
    ChartItem* OnDrawMeter(QGraphicsScene *pScene,METER_STRU meter, int nPointCount,int nFontSize);
    void setdataRange(double dMax, double dMin,int type);
    Keyboard Monitor_Address_Keyboard;
    Keyboard m_minAddress_EntryBtn;
    Keyboard m_maxAddress_EntryBtn;
    QGraphicsScene *pScene;
    ChartItem *pOldItem;
    ChartItem *pChartItem;
    QGroupItem *pBaseItem;

    int nMeterType;         //仪表类型
    int nPointType;         //仪表指针类型
    int nDirection;         //方向
    int nMainScal;          //主刻度数
    int nSubScal;           //次刻度数
    double dMax;            //最大值
    double dMin;            //最小值
    QString sPointColor;    //仪表指针颜色
    QString sBackColor;     //仪表背景颜色

    METER_STRU meter;        //仪表信息结构体

signals:
  void  commonclick();
  void setRange(double dMax, double dMin, int type);//type: 0浮点型
  void onGetShowValue(bool &bShow);//获取是否显示刻度值
  void onGetPointType(int &nType);//获取指针类型

private:
    Ui::QChartMeter *ui;
    QGraphicsItem * pCopyItem;
    bool nInitFlag;

private slots:
    void on_m_TransparentspBox_valueChanged(int );
    void on_m_TransparentCKBox_clicked(bool checked);
    void on_max_numEdit_textChanged(QString );
    void on_min_numEdit_textChanged(QString );
    void on_datatype_comboBox_currentIndexChanged(int index);
    void on_m_maxAddress_EntryBtn_clicked();
    void on_m_minAddress_EntryBtn_clicked();
    void on_rang_comboBox_currentIndexChanged(int index);
    void on_direction_comboBox_currentIndexChanged(int index);
    void on_max_numEdit_lostFocus();
    void on_min_numEdit_lostFocus();
    void on_symbol_checkBox_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_Monitor_Address_EntryBtn_clicked();
    void on_m_CommonButton_2_clicked();
    void on_m_checkBox_showFrame_clicked(bool checked);
};

#endif // QCHARTMETER_H
