#ifndef QELIPSEITEM_H
#define QELIPSEITEM_H

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

class QElipseItem : public GraphicsEllipseItemSamExt/*, public QBasicGraphicsItem*/
{
public:
    QElipseItem();
    QElipseItem(QRectF &rect);

    enum { Type = UserType + 16 };
    int type() const { return Type;}

    void init();

    QElipseItem *Clone();

    void compile(QSqlDatabase &db, int nSceneId,int &count,int index);

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

    void SetSpanAngle(int nAngle);
    int GetSpanAngle();

    void SetStartAngle(int nAngle);
    int GetStartAngle();

    void SetFrontColor(QColor nColor);
    QColor GetFrontColor();

    void SetDescription(QStringList sListStr);
    QStringList GetDescription();
    void setRectA(const QRectF &rect);
    virtual QRectF boundingRect() const
    {
        return this->rect();
    }
    QRectF sceneBoundingRect() const
    {
        return this->mapRectToScene(this->rect());
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                     QWidget *widget);

    float getPropor();
    void setPropor(float nPro,int nPatternType);
public:
    QColor nBackColor;    //������ɫ
    QColor nFrontColor;   //ǰ��ɫ
    int nPatternType;     //��ʽ����
    int nLineType;        //������ʽ����
    float nPropor;          //����Բ�뾶����
private:
    friend QDataStream &operator<<(QDataStream &stream, QElipseItem *pElipseItem);
    friend QDataStream &operator>>(QDataStream &stream, QElipseItem *pElipseItem);
};

#endif // QELIPSEITEM_H
