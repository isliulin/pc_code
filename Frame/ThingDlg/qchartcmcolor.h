#ifndef QCHARTCMCOLOR_H
#define QCHARTCMCOLOR_H

#include <QWidget>
#include <qfile.h>
#include <QGraphicsScene>
#include "view/qitemgroup.h"
#include "color.h"
#include "view/qrectitem.h"
#include "view/qgroupitem.h"
#include "view/ChartItem.h"
#include "Frame/DrawDlg/LoadShape.h"

namespace Ui {
    class QChartCmColor;
}

class QChartCmColor : public QWidget
{
    Q_OBJECT

public:
    explicit QChartCmColor(QWidget *parent = 0);
    void Init(ChartItem *pItem);
    void DrawBar();
    bool SplitItem(QGraphicsItem **pItem,QString sname);
    void changeDirection(int nDirection);
    void setCommonShapeType(int nType);
    bool InitScene(QString sPath);
    void OnDrawScal(ChartItem **pGroupItem,int iDrawMain,int iDrawSun,int iDerection,QPointF leftPoint,QPointF rbottomPoint);
    void onDrawCircleScale(ChartItem **pGroupItem,CIRCLE_TYPE circle);
    void DrawCircal(ChartItem **pGroupItem,CIRCLE_TYPE circle);
    void onDrawCirclePoint(ChartItem **pGroupItem,CIRCLE_TYPE circle,int index);
    void setCircleProperty(ChartItem **newGroup,int index);
    void onDrawBackRect(ChartItem **pGroupItem, QGraphicsItem *pBackItem = 0);
    void onDrawFrontRect(ChartItem **pGroupItem,QRectF rect);
    bool CommonGenSave(struct COMMON_INFORMATION &common_st);
    QGraphicsItem *getItemFromFile(const int nIndex,QString sPath);
    QString GetText(int nIndex,double Min, double Max,int nMain);
    ~QChartCmColor();

public:
    QGraphicsItem * pCopyItem;
    ChartItem *pCommonItem;
    QItemGroup *pGroup;
    QGroupItem *pBaseItem;
    QGraphicsScene *pScene;
    int m_nLoadShapeType;
    bool bInitFlag;

    int nMainScale;        //主刻度
    int nSubScale;         //次刻度
    QString sCaleColor;     //刻度颜色

    CIRCLE_TYPE circle; //圆形图和半圆图初始化属性
    bool bScaleFlag;
    int nMeterType;
    int nLocation;     //柱状图和槽型图刻度在左边还是在右边标记0：左边 1：右边
    int nDirectionType;//显示方向

signals:
    void onGetDirection(int &nIndex);
    void onGetroleCheck(bool &bCheck, int &nRadius);//bCheck:true设置半径，false获取半径
    void onGetdataRange(double &dMin, double &dMax);//获取最大最小值
    void onGetShowValue(bool &bShow);
    void onGetPointType(int &nType);//获取圆是否画指针，0：显示填充，1：显示指针
    void onGetStartAngle(short &nStart,short &nSpan);
    void onGetCircleAlpha(short &nAlpha);
    void onGetShowFrame(bool &bShowFrame);
private:
    Ui::QChartCmColor *ui;
    Keyboard Min_Address_Keyboard;
    Keyboard Max_Address_Keyboard;
    bool nInitFlag;


private slots:
    void on_m_PointTypecbBox_currentIndexChanged(int index);
    void on_m_AlarmcbBox_currentIndexChanged(int index);
    void on_m_AddressMax_EntryBtn_clicked();
    void on_m_AddressMin_EntryBtn_clicked();
    void on_m_AlarmckBox_clicked();
    void on_m_Alarmshapecolorbtn_clicked();
    void on_m_Alarmshowcolorbtn_clicked();
    void on_shape_selectBtn_clicked();
    void on_m_patterncmbox_currentIndexChanged(int index);
    void on_m_shapecolorbtn_clicked();
    void on_m_backgroudcolorbtn_clicked();
    void on_m_framecolorbtn_clicked();
    void on_m_showcolorbtn_clicked();

public slots:
    void reDrawBar();
    void setshowcolorbtnColor(const QColor &mColor);//设置显示颜色设置
    void setshowframebtnColor(const QColor &mColor);//设置显示边框颜色
    void setbackgroudbtnColor(const QColor &mColor);//设置背景颜色
    void setshapecolorbtnColor(const QColor &mColor);//设置图案颜色
    void setAlarmShowBtnColor(const QColor &mColor);//设置报警显示颜色
    void setAlarmShapeBtnColor(const QColor &mColor);//设置报警图案颜色
    void drawCenterCircle(bool bCircle, int nRadiu);
    void setdataRange(double dMax, double dMin,int type);
    void enablePointType(bool bable);//true 启用   false 禁用
};

#endif // QCHARTCMCOLOR_H
