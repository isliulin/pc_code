#ifndef QPOLYGONBASICITEM_H
#define QPOLYGONBASICITEM_H

#include "view/qpolygonitem.h"
#include "Frame/DrawDlg/qbasicgraphicsitem.h"

class QPolygonBasicItem : public QPolygonItem, public QBasicGraphicsItem
{
public:
    QPolygonBasicItem();
    QPolygonBasicItem(QPolygonF &qpsPolygonF);

    enum { Type = UserType + 38 };
    int type() const
      { return Type;}

    QPolygonBasicItem *Clone();

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);
private:
    friend QDataStream &operator<<(QDataStream &stream, QPolygonBasicItem *pPolygonItem);
    friend QDataStream &operator>>(QDataStream &stream, QPolygonBasicItem *pPolygonItem);
};

#endif // QPOLYGONBASICITEM_H
