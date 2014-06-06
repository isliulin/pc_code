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

    int nMainScale;        //���̶�
    int nSubScale;         //�ο̶�
    QString sCaleColor;     //�̶���ɫ

    CIRCLE_TYPE circle; //Բ��ͼ�Ͱ�Բͼ��ʼ������
    bool bScaleFlag;
    int nMeterType;
    int nLocation;     //��״ͼ�Ͳ���ͼ�̶�����߻������ұ߱��0����� 1���ұ�
    int nDirectionType;//��ʾ����

signals:
    void onGetDirection(int &nIndex);
    void onGetroleCheck(bool &bCheck, int &nRadius);//bCheck:true���ð뾶��false��ȡ�뾶
    void onGetdataRange(double &dMin, double &dMax);//��ȡ�����Сֵ
    void onGetShowValue(bool &bShow);
    void onGetPointType(int &nType);//��ȡԲ�Ƿ�ָ�룬0����ʾ��䣬1����ʾָ��
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
    void setshowcolorbtnColor(const QColor &mColor);//������ʾ��ɫ����
    void setshowframebtnColor(const QColor &mColor);//������ʾ�߿���ɫ
    void setbackgroudbtnColor(const QColor &mColor);//���ñ�����ɫ
    void setshapecolorbtnColor(const QColor &mColor);//����ͼ����ɫ
    void setAlarmShowBtnColor(const QColor &mColor);//���ñ�����ʾ��ɫ
    void setAlarmShapeBtnColor(const QColor &mColor);//���ñ���ͼ����ɫ
    void drawCenterCircle(bool bCircle, int nRadiu);
    void setdataRange(double dMax, double dMin,int type);
    void enablePointType(bool bable);//true ����   false ����
};

#endif // QCHARTCMCOLOR_H
