/********************************************************************
类名：QGroupItem
作用：组合类，对组合图形的操作，该类只针对由矩形，圆，扇形和文本这四个基本图形组合
             的操作，且只针对由两层组合操作，多余两层的组合不实现,SetDescription
             函数可用来存组合图形的属性信息
作者：郑启红
时间：2010-11-01
********************************************************************/
#ifndef QGROUPITEM_H
#define QGROUPITEM_H

#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QString>
#include <QVariant>
#include <QStringList>
#include "view/qsimpletextitem.h"
#include "view/samdrawscene.h"
#include "view/qpixmapitem.h"
//#include "view/qrectitem.h"
//#include "view/qelipseitem.h"
//#include "view/QRoundedRect.h"
//#include "view/QArcItem.h"
#include "view/qrectbasicitem.h"
#include "view/qelipsebasicitem.h"
#include "view/qroundedrectbasic.h"
#include "view/qarcbasicitem.h"
#include "view/qlinebasicitem.h"
#include "view/qfoldlinebasicitem.h"
#include "view/qpolygonbasicitem.h"
#include "view/qfreelinebasicitem.h"
#include "view/qlinecirclebasicitem.h"

class QGroupItem : public QGraphicsItemGroup
{
public:
    QGraphicsItem * groupItem;
    QGroupItem(QGraphicsItem * item);
    enum { Type = UserType + 500};
    int type() const
      { return Type;}
    void SetPropertyValue(QString qstr,QVariant value); //QVariant value QColor Color
    void SetProerty(QRectItem *pRECT,QString SNAME,QVariant VALUE);
    void SetProerty(QElipseItem *pCIRCLE,QString SNAME,QVariant VALUE);
    void SetProerty(QSimpleTextItem *pTEXT,QString SNAME,QVariant VALUE);

    void SetProerty(QLineItem *pLINE,QString SNAME,QVariant VALUE);
    void SetProerty(QPolygonItem *pPOLY,QString SNAME,QVariant VALUE);

    void SetProerty(QRoundedRect *pRoundRect,QString SNAME,QVariant VALUE);

    void setItemPattern(int nPattern); //设置样式

    void SetGroupVisible(bool nFLAG);
    void SetShapeVisible(QString name,bool nFLAG);
    void SetLeft(int nLeft);
    void SetTop(int nTop);
    int GetLeft();
    int GetTop();
	void SetWidth(qreal nWidth);
	void SetHeigth(qreal nHeight);

	void SetName(QString sName);
    QString GetName();

    void SetId(int nID);
    int GetId();

	QColor StringTOColor(QString sColor);

	QString Text();
	QString TextOn();
	QString TextOff();

	QPixmap* Pictrue();
	QPixmap* PictrueOn();
	QPixmap* PictrueOff();
    void SetDescription(QStringList sListStr);
    QStringList GetDescription();
};

class DrawItemToScene
{
public:
	 QItemGroup*  DrawItem(
			 int nAppr,QPixmap *pImage,QString sTxt,QString sName);
	 QGraphicsItem*  DrawSamItem(
			 int appr,QPixmap *image,SamDrawScene *pScene,int status);
	 void CopyItem(
		 QGraphicsItem ** pNewItem, QGraphicsItem *pOldItem);
         void CopyItemForChart(QGraphicsItem ** pNewItem,
                                        QGraphicsItem *pOldItem);
	 QItemGroup* ReSetPic(QGraphicsItem* pItem,QPixmap* pictrue,int status,PicPosInfo posinfo);
	 QItemGroup* ReSetPic(QGraphicsItem* pOldItem,QPixmap* pictrue,PicPosInfo posinfo);
	 QRectF TransPicPos(PicPosInfo posinfo,QRectF rect);
	 QGraphicsItem* Clone(QLineItem *lineItem);
	 QGraphicsItem* Clone(QSimpleTextItem *textItem);
	 QGraphicsItem* Clone(QElipseItem *elipseItem);
	 QGraphicsItem* Clone(QRectItem *rectItem);
	 QGraphicsItem* Clone(QPixmapItem *imageItem);
	 QGraphicsItem* Clone(QPolygonItem *PolygonItem);
	 QGraphicsItem* Clone(QFoldLineItem *FoldLineItem);
         QGraphicsItem* Clone(QRoundedRect *RoundedrectItem);
         QGraphicsItem* Clone(QArcItem *ArcItem);
         QGraphicsItem* Clone(QFreeLineItem *FreeLineItem);
         QGraphicsItem* Clone(QLineCircleItem *LineCircleItem);

         QGraphicsItem* Clone(QLineBasicItem *pItem);
         QGraphicsItem* Clone(QRectBasicItem *pItem);
         QGraphicsItem* Clone(QElipseBasicItem *pItem);
         QGraphicsItem* Clone(QFoldLineBasicItem *pItem);
         QGraphicsItem* Clone(QPolygonBasicItem *pItem);
         QGraphicsItem* Clone(QRoundedRectBasic *pItem);
         QGraphicsItem* Clone(QArcBasicItem *pItem);
         QGraphicsItem* Clone(QFreeLineBasicItem *pItem);
         QGraphicsItem* Clone(QLineCircleBasicItem *pItem);
};
#endif // QGROUPITEM_H
