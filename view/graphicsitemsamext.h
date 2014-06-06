/************************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2010
 *
 * Description: SDWorkshop draw object base class define .h file.
 *
 * Functions: None.
 *
 * Modification Log:
 * Date             Name             Description Of Change
 * 2010-10-27       Bruce nie        Creation.
 ***********************************************************************/
#ifndef GRAPHICSITEMSAMEXT_H
#define GRAPHICSITEMSAMEXT_H

#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItemGroup>
#include <view/samdrawitembase.h>
#include <headfile/global_types.h>

QT_BEGIN_NAMESPACE
class SamDrawItemBase;
QT_END_NAMESPACE

/* Class for SamDraw rect item*/
class GraphicsRectItemSamExt : public QGraphicsRectItem, public SamDrawItemBase
{
    //Q_OBJECT

public:
    GraphicsRectItemSamExt();
    GraphicsRectItemSamExt(const QRectF &rect, QGraphicsItem *parent = 0);
};

/* Class for SamDraw ellipse item*/
class GraphicsEllipseItemSamExt : public QGraphicsEllipseItem, public SamDrawItemBase
{
    //Q_OBJECT

public:
    GraphicsEllipseItemSamExt();
    GraphicsEllipseItemSamExt(const QRectF &rect, QGraphicsItem *parent = 0);
};

/* Class for SamDraw line item*/
class GraphicsLineItemSamExt : public QGraphicsLineItem, public SamDrawItemBase
{
    //Q_OBJECT

public:
    GraphicsLineItemSamExt();
    GraphicsLineItemSamExt(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = 0);

    QCursor getHandleCursor(int iHandle) const;
    virtual void drawTracker(eTrackerState state, QGraphicsScene *pScene, QRectF &qrcBondingRect);
    /*Get the handle point by handle id*/
    virtual QPointF getHandle(int iHandle, QRectF &qrcBondingRect) const;
    /*Get the handle count of the object*/
    virtual int getHandleCount() const;
    /*Hit the handle by mouse courrent point*/
    virtual int hitTest(QPointF point, QRectF &qrcBondingRect, bool bSelected);
    /*To drag the samdraw object, drag some a handle to a different place*/
    virtual QRectF moveHandleTo(int iDragHandle, QPointF qpLocal, QRectF &qrcBondingRect);
    void moveLineHandleTo(int iDragHandle, QPointF qpLocal);
    /*Refresh trackers*/
    void moveLineTrackers(const unsigned long &ulHandle, const QPointF &qpPoint);
    void refreshLineTrackers();
};

/* Class for SamDraw polygon item */
class GraphicsPolygonItemSamExt : public QGraphicsPolygonItem, public SamDrawItemBase
{
    //Q_OBJECT

public:
    GraphicsPolygonItemSamExt();
    GraphicsPolygonItemSamExt(const QPolygonF &polygon, QGraphicsItem *parent = 0);

    /*Get the handle count of the object*/
    virtual int getHandleCount() const;
    /*Get the handle point by handle id*/
    virtual QPointF getHandle(int iHandle, QRectF &qrcBondingRect) const;
    /*Get the mouse cursor by handle id*/
    virtual QCursor getHandleCursor(int iHandle) const;
    /*To drag the samdraw object, drag some a handle to a different place*/
    virtual QRectF moveHandleTo(int iDragHandle, QPointF qpLocal, QRectF &qrcBondingRect);
    void movePolygonTrackers(const unsigned long &ulHandle, const QPointF &qpPoint);
    void refreshPolygonTrackers(QGraphicsScene *pScene);
    void drawPolygonTrackers(QGraphicsScene *pScene);
private:

};

/* Class for SamDraw path item */
class GraphicsPathItemExt : public QGraphicsPathItem, public SamDrawItemBase
{
public:
    GraphicsPathItemExt();
    GraphicsPathItemExt(const QPainterPath &path, QGraphicsItem *parent = 0);
    /*Get the handle count of the object*/
    virtual int getHandleCount() const;
    /*Get the handle point by handle id*/
    virtual QPointF getHandle(int iHandle, QRectF &qrcBondingRect) const;
    /*Get the mouse cursor by handle id*/
    virtual QCursor getHandleCursor(int iHandle) const;
    /*To drag the samdraw object, drag some a handle to a different place*/
    virtual QRectF moveHandleTo(int iDragHandle, QPointF qpLocal, QRectF &qrcBondingRect);
    /*Move the trackers while object is draged by handle*/
    void movePathTrackers(const unsigned long &ulHandle, const QPointF &qpPoint);
    /*Refresh all trackers*/
    void refreshPathTrackers(QGraphicsScene *pScene);
    /*Set line end-arrow style*/
    void setLineEndArrow(LINE_END_ARROW_STYLE_E eStyle);
    /*Refresh line end-arrow, according to current setted style*/
    void refreshEndArrow();
    /*Create trackers if trackers array is empty*/
    void drawPathTrackers(QGraphicsScene *pScene);
    QPainterPath getEndArrowPath();
private:
};

/*Class for SamDraw group item*/
class GraphicsItemGroupSamExt : public QGraphicsItemGroup, public SamDrawItemBase
{
    //Q_OBJECT

public:
    GraphicsItemGroupSamExt();
    GraphicsItemGroupSamExt(QGraphicsItem *parent = 0);
};

/*Class for SamDraw text item*/
class GraphicsSimpleTextItemSamExt : public QGraphicsItem, public SamDrawItemBase
{
public:
    //GraphicsSimpleTextItemSamExt(QGraphicsItem *parent = 0);
    GraphicsSimpleTextItemSamExt(QGraphicsItem *parent = 0);
 //   GraphicsSimpleTextItemSamExt(const QRectF &rect, QString sText = "");
};

class SamDrawLineEx;
class SamDrawLineTackerRect;

/*********************************************************************************
 * Class GraphicsMultiPathItem for SamDraw multi path item(line-circle)
 * Design by tanghaiguo at 2010.11.8
 ********************************************************************************/
class GraphicsMultiPathItem : public QGraphicsPathItem, public SamDrawItemBase
{
public:
    GraphicsMultiPathItem();
    GraphicsMultiPathItem(const QPainterPath &path, QGraphicsItem *parent = 0);

    /*Draw the little rect at the path */
    void drawTracker(eTrackerState state, QGraphicsScene *pScene);
    /*Get the mouse cursor shape when you move your mouse */
    QCursor getHandleCursor(QPointF point);
    /*Refreash all trackers according to object position*/
    void refreshLineCircleTrackers(QGraphicsScene *pScene);
    /*Set line end-arrow style*/
    void setLineEndArrow(LINE_END_ARROW_STYLE_E eStyle);
    /*Refresh line end-arrow, according to current setted style*/
    void refreshEndArrow(LINE_END_ARROW_STYLE_E eStyle = LINE_END_ARROW_STYLE_BUTT);
    /*add item to scene */
    void addItemtoscane(QGraphicsItem *pItem,QGraphicsScene *pScene);
    /*remove Line Tracker*/
    void removeLineTracker(QGraphicsScene *pScene);

    int itemSelectMousePress(QPointF pos);
    void itemSelectMouseMove(QGraphicsScene *pScene, QPointF pos);
    void itemSelectMouseRelease();

    QList<QPolygonF> getHandleList() const;
private:
    /*Get circle mid control point at subPath */
    QPointF getMidPoint(QPointF first,QPointF back,QPainterPath subpath) const;
    /*Get the point pos at which subPath after use getHandleList function *
      *the fun return 0 show not at the path,so it is from 1 to n */
    int getSubPathNum(QPointF point);
    /*Get the point pos at subPath pos first mid or end */
    int getSubPathPos(QPointF point);
    /*Move one control point to another pos and the path chang */
    void moveHandleToEx(int iDragHandle, QPointF qpLocal, QGraphicsScene *pScene,int pathPos);
    /*Move the tracker rects when resize the object*/
    void moveLineCircleTrackers(const unsigned long &ulHandle, const QPointF &qpPoint);
    /*Draw the circle line and control point */
    void DrawLineTracker(int subPathNum,QGraphicsScene *pScene);
    /*Get the handle list,the list contain handle to control the path */


public:
    /*this list save handleList when you move the control point */
    QList<QPolygonF> m_handPolygonList;

private:
    int m_pathIndex;
    int m_subPathIndex;
    /*circle line to control point property */
    SamDrawLineEx *m_lineItem1;
    SamDrawLineEx *m_lineItem2;
    /*control point property*/
    SamDrawLineTackerRect *m_trackerItem;
};

#endif // GRAPHICSITEMSAMEXT_H
