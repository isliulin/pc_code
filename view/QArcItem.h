/********************************************************************
  作用：生成扇形基类
  作者：郑启红/Bruce nie
  时间：2011-03-15
********************************************************************/

#ifndef QARCITEM_H
#define QARCITEM_H

#include <QGraphicsPathItem>
#include <view/samdrawitembase.h>
//#include "Frame/DrawDlg/qbasicgraphicsitem.h"

#define ARC_ITEM_HANDLE_COUNT 10
#define PI_ANGLE 360

class QArcItem : public QGraphicsPathItem, public SamDrawItemBase/*, public QBasicGraphicsItem*/
{
public:
    QArcItem();
    enum { Type = UserType + 27 };
    int type() const
      { return Type;}

    /*Add by Bruce nie 2011-03-30*/
    virtual int getHandleCount() const;
    virtual QPointF getHandle(int iHandle, QRectF &qrcBondingRect) const;
    /*To drag the samdraw object, drag some a handle to a different place*/
    virtual QRectF moveHandleTo(int iDragHandle, QPointF qpLocal, QRectF &qrcBondingRect, bool bFoursquare = false);
    virtual QCursor getHandleCursor(int iHandle) const;
    qreal getAngle(qreal dDeltaX, qreal dDeltaY) const;
    virtual QRectF boundingRect() const
    {
        return this->m_qrcEllipseBndRect;
    }
    QRectF sceneBoundingRect() const
    {
        return this->mapRectToScene(this->m_qrcEllipseBndRect);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                  QWidget *widget);
    /*Add end*/
public:
    QPainterPath m_ArcPath;

    qreal m_dStartAngle;     //起始角度
    qreal m_dSpanAngle;       //跨度

    QColor nBackColor;    //背景颜色
    QColor nFrontColor;   //前景色
    int nPatternType;     //样式类型
    int nLineType;        //线条样式类型
    QRectF m_qrcEllipseBndRect; // Bonding rect of the ellpise which the arc in.

public:
    void SetStartAngle(qreal qStartAngle);
    qreal GetStartAngle();

    void SetSpanAngle(qreal qSpanAngle);
    qreal GetSpanAngle();

    void SetWidth(qreal Width);
    qreal GetWidth();

    void SetHeight(qreal Height);
    qreal GetHeight();

    void SetName(QString qstr);
    QString GetName();

    void SetPattern(int nPATTERN);
    int GetPattern();

    void SetLineType(int nTYPE);
    int GetLineType();

    void SetLineWidth(int nWidth);
    int GetLineWidth();

    void SetLineColor(QColor nColor);
    QColor GetLineColor();

    void SetAlpha(int nAlpha);
    int GetAlpha();

    void SetBackColor(QColor nColor);
    QColor GetBackColor();

    void SetFrontColor(QColor nColor);
    QColor GetFrontColor();

    void refreshArc();

    virtual QGraphicsItem *Clone();
    QRectF getEllipseRect() const {return m_qrcEllipseBndRect;}
    void setRectA(const QRectF &rect);
    void compile(QSqlDatabase &db, int nSceneId,int &count,int index);

    friend QDataStream &operator<<(QDataStream &stream, QArcItem *pArcItem);
    friend QDataStream &operator>>(QDataStream &stream, QArcItem *pArcItem);
};

#endif // QARCITEM_H
