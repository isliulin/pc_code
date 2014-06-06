/************************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2010
 *
 * Description: SamDrawItemBase class define .h file.
 *
 * Functions: None.
 *
 * Modification Log:
 * Date             Name             Description Of Change
 * 2010-10-22       Bruce nie        Creation.
 ***********************************************************************/
#ifndef SAMDRAWITEMBASE_H
#define SAMDRAWITEMBASE_H

#include <QPointF>
#include <QRectF>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <qmath.h>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

#define SAMDRAW_TRACKER_SIZE      5
enum eDRAG_CROSS_TYPE_E
{
    DRAG_CROSS_LEFT_RIGHT = 0x01,
    DRAG_CROSS_TOP_BOTTON = 0x10,
    DRAG_CROSS_ALL        = 0x11,
    DRAG_CROSS_TYPE_BUTT  = 0x00
};
typedef enum eDRAG_CROSS_TYPE_E DRAG_CROSS_TYPE_E;

enum eTrackerState { TRK_NORMAL, TRK_SELECTED, TRK_ACTIVE };

/*Line type object end-arrow type define*/
enum eLINE_END_ARROW_STYLE_E
{
    LINE_END_STYLE_NONE         = 0x00,
    LINE_END_FILLED_TRIANGLE    = 0x01,
    LINE_END_FOLD_LINE_TRIANGLE = 0x02,
    LINE_END_FILLED_SCISSORS    = 0x03,
    LINE_END_FILLED_RECT        = 0x04,
    LINE_END_FILLED_ELLIPSE     = 0x05,
    LINE_END_ARROW_STYLE_BUTT
};
typedef enum eLINE_END_ARROW_STYLE_E LINE_END_ARROW_STYLE_E;

struct stLineKeyPoints
{
    QPointF qpKeyPoint0;
    QPointF qpKeyPoint1;
    QPointF qpKeyPoint2;
    QPointF qpKeyPoint3;
    QPointF qpKeyPoint4;
    QPointF qpKeyPoint5;
};
typedef struct stLineKeyPoints LINE_KEY_POINT_T;

class SamDrawTackerRect;

class SamDrawLockRect;

/*SamDraw object base class(virtual class),
 *Caution: can not create object by this class!
 */
class SamDrawItemBase
{
public:
    enum eDRAGE_HANDLE_ID
    {
        HANDLE_LEFT_TOP      = 1,
        HANDLE_CENTER_TOP    = 2,
        HANDLE_RIGHT_TOP     = 3,
        HANDLE_RIGHT_CENTER  = 4,
        HANDLE_RIGHT_BOTTOM  = 5,
        HANDLE_CENTER_BOTTOM = 6,
        HANDLE_LEFT_BOTTOM   = 7,
        HANDLE_LEFT_CENTER   = 8,
        HANDLE_ID_BUTT
    };

    SamDrawItemBase();
    ~SamDrawItemBase();
    /*Get the handle rect by handle id*/
    QRectF getHandleRect(int iHandleID, QRectF &qrcBondingRect);
    DRAG_CROSS_TYPE_E NormalizeDragedRect(QRectF &qrRect);
    /*Draw trackers of samdraw object*/
    void drawTracker(eTrackerState state, QGraphicsScene *pScene, QRectF &qrcBondingRect);
    /*Get the handle count of the object*/
    virtual int getHandleCount() const;
    /*Get the handle point by handle id*/
    virtual QPointF getHandle(int iHandle, QRectF &qrcBondingRect) const;
    /*Get the mouse cursor by handle id*/
    virtual QCursor getHandleCursor(int iHandle) const;
    /*Hit the handle by mouse courrent point*/
    virtual int hitTest(QPointF point, QRectF &qrcBondingRect, bool bSelected);
    /*To drag the samdraw object, drag some a handle to a different place*/
    virtual QRectF moveHandleTo(int iDragHandle, QPointF qpLocal, QRectF &qrcBondingRect, bool bFoursquare = false);
    /*Clone the object*/
    virtual QGraphicsItem *Clone() = 0;
    /*Move the trackers by delta point*/
    void moveAllTrackersPos(const QPointF &qrcDelta);
    /*Set trackers visiable property*/
    void setTrackersVisiable(bool bVisiable);
    /*Refresh trackers postion when move handle*/
    void refreshTrackers(const QRectF &qrcCurBndRect, QGraphicsScene *pScene);
    /*Get the line parameters according to 2 points*/
    void calculateLinePara(const QPointF &qpP1, const QPointF &qpP2, qreal &dK, qreal &dB, qreal &dXdirect, qreal &dYdirect);
    /*Get the key points of end-arrow*/
    void getEndArrowKeypoints(const qreal &dK, const QPointF &qpEndPt, LINE_KEY_POINT_T &stKeyppoints, const qreal dXdirect, const qreal dYdirect);

    void qt_graphicsItem_highlightSelected(
        QGraphicsItem *item, QPainter *painter, const QStyleOptionGraphicsItem *option);
    QVector <SamDrawTackerRect *> m_pvecTrackers;
    /*Line type object end-arrows*/
    //QVector <QPainterPath *> m_pvcLineEndArrows;
    LINE_END_ARROW_STYLE_E m_eLineEndArrowType;

    /*The property of resizable*/
    void setResizableOn()  { this->m_bResizable = true; }
    void setResizableOff() { this->m_bResizable = false; }
    bool getResizable() const { return this->m_bResizable; }
    void SetselectFlag(bool flag) { bFlag = flag; }
    bool GetselectFlag() { return bFlag; }

    SamDrawLockRect *m_LockTracker;
    void refreshLockRect(QPointF qpPoint, QGraphicsScene *pScene,bool bLock);
    void setLockVisiable(bool bVisiable);
    inline void setId(int id)
    {
        m_id = id;
    }
    inline int id()
    {
        return m_id;
    }

private:
    bool m_bResizable;
    bool bFlag;
    bool bLockVisiable;
    int  m_id;
};

/* Class for SamDraw tracker item*/
class SamDrawTackerRect : public QGraphicsRectItem
{
public:
    SamDrawTackerRect(const QPointF qpPoint, QGraphicsItem *parent = 0);
    enum { Type = UserType + 999 };
    int type() const { return Type;}
    SamDrawTackerRect* Clone();
private:
};

/* Class for SamDraw line tracker item*/
class SamDrawLineTackerRect : public QGraphicsEllipseItem
{
public:
    SamDrawLineTackerRect(const QPointF qpPoint, QGraphicsItem *parent = 0);
    enum { Type = UserType + 997 };
    int type() const { return Type;}
private:
};

/*********************************************************************************
 * Class for SamDrawLineEx
 ********************************************************************************/
class SamDrawLineEx : public QGraphicsLineItem
{
public:
    SamDrawLineEx(const QPointF first,const QPointF back,QGraphicsItem *parent = 0);
    enum { Type = UserType + 998 };
    int type() const { return Type;}
private:
};

class SamDrawLockRect : public QGraphicsPixmapItem
{
public:
   SamDrawLockRect(const QPointF qpPoint,QString sPath,QGraphicsItem *parent = 0);
   enum { Type = UserType + 1000};
   int type()const {return Type;}
private:
};

#endif // SAMDRAWITEMBASE_H
