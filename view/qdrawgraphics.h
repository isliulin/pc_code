/********************************************************************
  作用：封装生成仪表画图和生成只有一个状态页面图形的类
  作者：郑启红
  时间：2010-11-24
********************************************************************/
#ifndef QDRAWGRAPHICS_H
#define QDRAWGRAPHICS_H

#include "view/qrectitem.h"
#include "view/qsimpletextitem.h"
#include <QGraphicsScene>
#include <QList>
#include <view/qitemgroup.h>
//#include "qtrendattr.h"

class QTrendAttr;
class QTrendDataGroupAttr;
class XYtrend;

class QDrawGraphics
{
public:
    QDrawGraphics();
public:
    /************************************************************
     *画一般页面基本图形函数
     ***********************************************************/
    QGraphicsItem* OnDrawRectAndText(QGraphicsScene *pScene);
    QList<QGraphicsItem*> OnDrawRectAndText();
    QItemGroup* AlterGraphics(QGraphicsItem* pOldItem,QPixmap* pictrue,
                              int nPicPosition,int nBorderInterval,bool ifFit,
                              bool ifDeletePic);
    QRectF SetPicPosition(QGraphicsItem *pPicItem,int nPicPosition,
                        int nBorderInterval,bool ifFit,int nSpace,QRectF rect);

    QItemGroup* AlterGraphics(QGraphicsItem* pOldItem,QPixmap* pictrue,QGraphicsItem* pLibItem,
                              int nPicPosition,int nBorderInterval,bool ifFit);
    /************************************************************
     *画仪表函数
     ***********************************************************/
    QGraphicsItem* OnDrawMeter(QGraphicsScene *pScene,int nMeterType,int nPointerType,int nDirection,int nMainScal,
                               int nSubScal, double dMax, double dMin, int nPointCount,
                               int nFontSize);
    /************************************************************
     *画仪表函数
     ***********************************************************/
    void OnDrawPointer(int nPointerType,int nMeterType);
    void OnDrawScal(int nMeterType,int nDirection,int nMainScal,int nSubScal,double dMax,double dMin,int nPointCount,int nFontSize);

    /************************************************************
     *画扇形图函数
     ***********************************************************/
    QGraphicsItem* OnDrawPie(QGraphicsScene *pScene,int nMeterType,int nDirection,int nMainScal,
                               int nSubScal, double dMax, double dMin, int nPointCount,
                               int nFontSize);


    /************************************************************
     *画图片显示器加载图片函数
     ***********************************************************/
    QItemGroup* OnAddPicture(QGraphicsItem* pOldItem,QPixmap* pictrue,
                              int nPicPosition,int nBorderInterval,bool ifFit,
                              bool ifDeletePic);

    /************************************************************
     *画趋势图、XY趋势图以及历史趋势图函数
     ***********************************************************/
    void OnDrawTrendChart(QTrendAttr *pItem);//新趋势图调用函数
    void OnDrawDataGroup(QTrendDataGroupAttr *pItem);//新的数据群组调用函数
    void OnDrawXYTrend(XYtrend *pItem);//画XY曲线
    QGraphicsItem* OnDrawTrendChart(int nType,QStringList *pList);
    QString GetText(double Min,double Max,int nMain,int nPointNum,int nType,
                    int nIndex,int nKey);

    QSimpleTextItem* DrawTrendText(QSimpleTextItem *pText, int nIndex,
                    double LineX, double LineY,QString sText,int nFontSize,
                    QColor mTextColor,int nTtype);

    QSimpleTextItem *drawHisTrendDate(int nIndex,
                                      double LineX, double LineY,QString sText,int nFontSize,
                                      QColor mTextColor, bool haveTime);
	QString GetTimeText(QDateTime tStart, QDateTime tEnd, int nMain,
		int nIndex,int format,int nType);
	void getDateTime(QTrendAttr *pItem,QDateTime &tStart,QDateTime &tEnd);
    /************************************************************
     *画滑动模拟量开关图形函数
     ***********************************************************/
    QItemGroup* DrawSlider(QStringList sList);
    QString GetSliderText(int nIndex,double Min,double Max,int nMain,
                          int nTextDirection,int nPointNum);
    int GetTextLength(QString sText,QSimpleTextItem* pText,int nFontSize);
    QSimpleTextItem* DrawSliderText(QSimpleTextItem *pText, int nIndex,
                                   double LineX, double LineY,QString sText,
                                   int nFontSize,QColor mTextColor);

    /************************************************************
     *画配方选择器,配方显示器函数
     ***********************************************************/
    QItemGroup* drawRecipeSelect(QStringList* pList);
    QItemGroup* drawRecipeDisplay(QStringList* pList);
    /************************************************************
     *绘制历史数据显示器函数
     ***********************************************************/
    QGraphicsItem* drawHistroyDataDisplayItem(QStringList *pList);
public:
    QGraphicsItemGroup *pGroup;

};

#endif // QDRAWGRAPHICS_H
