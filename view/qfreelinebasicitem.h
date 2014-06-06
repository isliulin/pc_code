#ifndef QFREELINEBASICITEM_H
#define QFREELINEBASICITEM_H

#include "view/qpolygonitem.h"
#include "Frame/DrawDlg/qbasicgraphicsitem.h"

class QFreeLineBasicItem : public QFreeLineItem, public QBasicGraphicsItem
{
public:
    QFreeLineBasicItem();
    QFreeLineBasicItem(const QPainterPath &path, QGraphicsItem *parent = 0);

    enum { Type = UserType + 40 };
    int type() const
      { return Type;}

    QFreeLineBasicItem *Clone();

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);
private:
    friend QDataStream &operator<<(QDataStream &stream, QFreeLineBasicItem *pFreeLineItem);
    friend QDataStream &operator>>(QDataStream &stream, QFreeLineBasicItem *pFreeLineItem);
};
#endif // QFREELINEBASICITEM_H
