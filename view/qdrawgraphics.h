/********************************************************************
  ���ã���װ�����Ǳ�ͼ������ֻ��һ��״̬ҳ��ͼ�ε���
  ���ߣ�֣����
  ʱ�䣺2010-11-24
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
     *��һ��ҳ�����ͼ�κ���
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
     *���Ǳ���
     ***********************************************************/
    QGraphicsItem* OnDrawMeter(QGraphicsScene *pScene,int nMeterType,int nPointerType,int nDirection,int nMainScal,
                               int nSubScal, double dMax, double dMin, int nPointCount,
                               int nFontSize);
    /************************************************************
     *���Ǳ���
     ***********************************************************/
    void OnDrawPointer(int nPointerType,int nMeterType);
    void OnDrawScal(int nMeterType,int nDirection,int nMainScal,int nSubScal,double dMax,double dMin,int nPointCount,int nFontSize);

    /************************************************************
     *������ͼ����
     ***********************************************************/
    QGraphicsItem* OnDrawPie(QGraphicsScene *pScene,int nMeterType,int nDirection,int nMainScal,
                               int nSubScal, double dMax, double dMin, int nPointCount,
                               int nFontSize);


    /************************************************************
     *��ͼƬ��ʾ������ͼƬ����
     ***********************************************************/
    QItemGroup* OnAddPicture(QGraphicsItem* pOldItem,QPixmap* pictrue,
                              int nPicPosition,int nBorderInterval,bool ifFit,
                              bool ifDeletePic);

    /************************************************************
     *������ͼ��XY����ͼ�Լ���ʷ����ͼ����
     ***********************************************************/
    void OnDrawTrendChart(QTrendAttr *pItem);//������ͼ���ú���
    void OnDrawDataGroup(QTrendDataGroupAttr *pItem);//�µ�����Ⱥ����ú���
    void OnDrawXYTrend(XYtrend *pItem);//��XY����
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
     *������ģ��������ͼ�κ���
     ***********************************************************/
    QItemGroup* DrawSlider(QStringList sList);
    QString GetSliderText(int nIndex,double Min,double Max,int nMain,
                          int nTextDirection,int nPointNum);
    int GetTextLength(QString sText,QSimpleTextItem* pText,int nFontSize);
    QSimpleTextItem* DrawSliderText(QSimpleTextItem *pText, int nIndex,
                                   double LineX, double LineY,QString sText,
                                   int nFontSize,QColor mTextColor);

    /************************************************************
     *���䷽ѡ����,�䷽��ʾ������
     ***********************************************************/
    QItemGroup* drawRecipeSelect(QStringList* pList);
    QItemGroup* drawRecipeDisplay(QStringList* pList);
    /************************************************************
     *������ʷ������ʾ������
     ***********************************************************/
    QGraphicsItem* drawHistroyDataDisplayItem(QStringList *pList);
public:
    QGraphicsItemGroup *pGroup;

};

#endif // QDRAWGRAPHICS_H
