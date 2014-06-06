/********************************************************************
  作用：生成矩形的类
  作者：郑启红
  时间：2010-10-28
********************************************************************/

#ifndef QRECTITEM_H
#define QRECTITEM_H

#include <QGraphicsRectItem>
#include <QString>
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

class QRectItem : public GraphicsRectItemSamExt/*, public QBasicGraphicsItem*/
{
public:
    QRectItem();
    QRectItem(const QRectF &rect, QGraphicsItem *parent = 0);

    enum { Type = UserType + 15 };
    int type() const
      { return Type;}
public:
    QColor nBackColor;    //背景颜色
    QColor nFrontColor;   //前景色
    int nPatternType;     //样式类型
    int nLineType;        //线条样式类型

public:
    void SetName(QString qstr);
    QString GetName();

    void SetId(int nID);
    int GetID();

    void SetPattern(int nPATTERN);
    int GetPattern();

    void SetLineType(int nTYPE);
    int GetLineType();

    void SetLineWidth(int nWidth);
    int GetLineWidth();

    void SetHeight(qreal nHeight);
    qreal GetHeight();

    void SetWidth(qreal nWIDTH);
    qreal GetWidth();

    void SetLeft(qreal nLeft);
    qreal GetLeft();

    void SetTop(qreal nTop);
    qreal GetTop();

    void SetLineColor(QColor nColor);
    QColor GetLineColor();

    void SetAlpha(int nAlpha);
    int GetAlpha();

    void SetAngle(qreal nAngle);
    qreal GetAngle();

    void SetBackColor(QColor nColor);
    QColor GetBackColor();

    void SetFrontColor(QColor nColor);
    QColor GetFrontColor();

    void SetDescription(QStringList sListStr);
    QStringList GetDescription();
    //QRectItem *Clone();
    virtual QGraphicsItem *Clone();

    void compile(QSqlDatabase &db, int nSceneId,int &count,int index);

    void setRectA(const QRectF &rect);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                  QWidget *widget);

    friend QDataStream &operator<<(QDataStream &stream, QRectItem *pRectItem);
    friend QDataStream &operator>>(QDataStream &stream, QRectItem *pRectItem);
};

#endif // QRECTITEM_H
