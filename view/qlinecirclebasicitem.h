#ifndef QLINECIRCLEBASICITEM_H
#define QLINECIRCLEBASICITEM_H

#include "view/qpolygonitem.h"
#include "Frame/DrawDlg/qbasicgraphicsitem.h"

class QLineCircleBasicItem : public QLineCircleItem, public QBasicGraphicsItem
{
public:
    QLineCircleBasicItem();
    QLineCircleBasicItem(const QPainterPath &path, QGraphicsItem *parent = 0);

    enum { Type = UserType + 42 };
    int type() const
      { return Type;}

    QLineCircleBasicItem *Clone();

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);
private:
    friend QDataStream &operator<<(QDataStream &stream, QLineCircleBasicItem *pLineCircleItem);
    friend QDataStream &operator>>(QDataStream &stream, QLineCircleBasicItem *pLineCircleItem);
};
#endif // QLINECIRCLEBASICITEM_H
