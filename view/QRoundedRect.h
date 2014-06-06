/********************************************************************
  作用：生成圆角矩形的类
  作者：郑启红
  时间：2011-03-15
********************************************************************/

#ifndef QROUNDEDRECT_H
#define QROUNDEDRECT_H

#include <QGraphicsPathItem>
#include <view/samdrawitembase.h>
//#include "Frame/DrawDlg/qbasicgraphicsitem.h"

class QRoundedRect : public QGraphicsPathItem, public SamDrawItemBase/*, public QBasicGraphicsItem*/
{
public:
    QRoundedRect();
    enum { Type = UserType + 26 };
    int type() const
      { return Type;}
public:
    QPainterPath RectPath ;
    qreal xRadius;
    qreal yRadius;
    qreal qWidth;
    qreal qHeight;
    QPointF Rpos;
    QColor nBackColor;    //背景颜色
    QColor nFrontColor;   //前景色
    int nPatternType;     //样式类型
    int nLineType;        //线条样式类型

public:
    void SetWidth(qreal Width);
    qreal GetWidth();

    void SetHeight(qreal Height);
    qreal GetHeight();

    void SetxRadius(qreal qxRadius);
    qreal GetxRadius();

    void SetyRadius(qreal qyRadius);
    qreal GetyRadius();

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

    virtual QGraphicsItem *Clone();
    void setRectA(const QRectF &rect);

    void compile(QSqlDatabase &db, int nSceneId,int &count,int index);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                  QWidget *widget);
private:
    friend QDataStream &operator<<(QDataStream &stream, QRoundedRect *pRoundRectItem);
    friend QDataStream &operator>>(QDataStream &stream, QRoundedRect *pRoundRectItem);
};

#endif // QROUNDEDRECT_H
