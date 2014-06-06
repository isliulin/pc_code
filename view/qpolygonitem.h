#ifndef QPOLYGONITEM_H
#define QPOLYGONITEM_H

#include <view/graphicsitemsamext.h>
//#include "Frame/DrawDlg/qbasicgraphicsitem.h"

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

class QPolygonItem : public GraphicsPolygonItemSamExt/*, public QBasicGraphicsItem*/
{
public:
    QPolygonItem();
    QPolygonItem(QPolygonF &qpsPolygonF);

    enum { Type = UserType + 18 };
    int type() const { return Type;}

    QPolygonItem *Clone();
    void compile(QSqlDatabase &db, int nSceneId,int &count,int index);
   

public:
    int  getAlpha();                //get line styles transparency
    void setAlpha(int nAlpha);      //set line styles transparency

    int  getLineType();             //get line style
    void setLineType(int nType);    //set line style

    int  getLineWidth();            //get line width
    void setLineWidth(int nWidth);  //set line width

    QColor getLineColor();               //get line color
    void   setLineColor(QColor color);   //set line color

    QColor getBackColor();           //get back color
    void setBackColor(QColor color); //set back color

    QColor getFrontColor();            //get front color
    void setFrontColor(QColor color);  //set front color

    int  getPattern();               //get background pattern style
    void setPattern(int nPattern);   //set background pattern style

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	void SetName(QString sName);
	QString GetName();
public:
    int nLineType;
    QColor m_backColor;
    QColor m_frontColor;
    int m_nPattern;
private:
    friend QDataStream &operator<<(QDataStream &stream, QPolygonItem *pPolygonItem);
    friend QDataStream &operator>>(QDataStream &stream, QPolygonItem *pPolygonItem);

};

class QFoldLineItem : public GraphicsPathItemExt/*, public QBasicGraphicsItem*/
{
public:
    QFoldLineItem();
    QFoldLineItem(const QPainterPath &path, QGraphicsItem *parent = 0);
    enum { Type = UserType + 19 };
    int type() const { return Type;}

    QFoldLineItem *Clone();
    void compile(QSqlDatabase &db, int nSceneId,int &count,int index);
    QList<QPointF > points();

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

    void paint(QPainter *painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *widget);

public:
    int nLineType;
    int nEndArrow;           //from 0 to 5
    int nEndPointShape;      //0 or 1
private:
    friend QDataStream &operator<<(QDataStream &stream, QFoldLineItem *pFoldLineItem);
    friend QDataStream &operator>>(QDataStream &stream, QFoldLineItem *pFoldLineItem);
};

class QFreeLineItem : public GraphicsPathItemExt/*, public QBasicGraphicsItem*/
{
public:
    QFreeLineItem();
    QFreeLineItem(const QPainterPath &path, QGraphicsItem *parent = 0);
    enum { Type = UserType + 20 };
    int type() const { return Type;}

    void compile(QSqlDatabase &db, int nSceneId,int &count,int index);
    QList<QPointF > points();

    QFreeLineItem *Clone();
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

    void setName(QString sName);
    QString getName();

    void paint(QPainter *painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *widget);

public:
    int nLineType;
    int nEndArrow;           //from 0 to 5
    int nEndPointShape;      //0 or 1
private:
    friend QDataStream &operator<<(QDataStream &stream, QFreeLineItem *pFreeLineItem);
    friend QDataStream &operator>>(QDataStream &stream, QFreeLineItem *pFreeLineItem);
};

class QLineCircleItem : public GraphicsMultiPathItem/*, public QBasicGraphicsItem*/
{
public:
    QLineCircleItem();
    QLineCircleItem(const QPainterPath &path, QGraphicsItem *parent = 0);
        enum { Type = UserType + 25 };
        int type() const { return Type;}
        void compile(QSqlDatabase &db, int nSceneId,int &count,int index);
        QList<QPointF > points();
    QLineCircleItem *Clone();
    void InsertPointTable(QSqlDatabase &db, int nItemId,QPolygonF polygon,int &order);

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

    void setName(QString sName);
    QString getName();

    void paint(QPainter *painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *widget);

public:
    int nLineType;
    int nEndArrow;           //from 0 to 5
    int nEndPointShape;      //0 or 1
private:
    friend QDataStream &operator<<(QDataStream &stream, QLineCircleItem *pLineCircleItem);
    friend QDataStream &operator>>(QDataStream &stream, QLineCircleItem *pLineCircleItem);
};
#endif // QPOLYGONITEM_H
