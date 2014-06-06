#ifndef QLINEITEM_H
#define QLINEITEM_H

#include <view/graphicsitemsamext.h>
#include "Frame/DrawDlg/qbasicgraphicsitem.h"

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QGraphicsSceneContextMenuEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QPolygonF;
QT_END_NAMESPACE

class QLineItem : public GraphicsPathItemExt
{
public:
    QLineItem();
    QLineItem(const QPainterPath &path, QGraphicsItem *parent = 0);

    enum { Type = UserType + 17 };
    int type() const
    { return Type;}

    QLineItem *Clone();

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);

public:
    int  getAlpha();                //get line styles transparency
    void setAlpha(int nAlpha);      //set line styles transparency

    int  getLineType();             //get line style
    void setLineType(int nType);    //set line style

    int  getLineWidth();            //get line width
    void setLineWidth(int nWidth);  //set line width

    QColor getLineColor();               //get line color
    void   setLineColor(QColor color);   //set line color

    int getEndArrow();              //get end arrow type ,int from 0 to 5
    void setEndArrow(int nArrow);   //set end arrow type ,int from 0 to 5

    int getEndPointShape();              //get end point shape,0 for flat,1 for round;
    void setEndPointShape(int pShape);   //set end point shape,0 for flat,1 for round;

    void SetName(QString sName);
    QString GetName();

    QPainterPath  shape () const;

    QRectF moveHandleTo(int iDragHandle, QPointF qpLocal, QRectF &qrcBondingRect);

    void paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *option,
                               QWidget *widget);
	inline void setShiftMode(bool isShift)
	{
		bShiftMode = isShift;
	};

private:
	bool bShiftMode;
    int nLineType;
    int nEndArrow;           //from 0 to 5
    int nEndPointShape;      //0 or 1

    friend QDataStream &operator<<(QDataStream &stream, QLineItem *pLineItem);
    friend QDataStream &operator>>(QDataStream &stream, QLineItem *pLineItem);
};

#endif // QLINEITEM_H
