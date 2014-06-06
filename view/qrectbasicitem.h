#ifndef QRECTBASICITEM_H
#define QRECTBASICITEM_H

#include "view/qrectitem.h"
#include "Frame/DrawDlg/qbasicgraphicsitem.h"

class QRectBasicItem : public QRectItem,public QBasicGraphicsItem
{
public:
    QRectBasicItem();
    QRectBasicItem(const QRectF &rect, QGraphicsItem *parent = 0);

    enum { Type = UserType + 35 };
    int type() const
      { return Type;}

    QRectBasicItem *Clone();

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);
private:
    friend QDataStream &operator<<(QDataStream &stream, QRectBasicItem *pRectItem);
    friend QDataStream &operator>>(QDataStream &stream, QRectBasicItem *pRectItem);

};

#endif // QRECTBASICITEM_H
