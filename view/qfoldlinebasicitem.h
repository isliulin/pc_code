#ifndef QFOLDLINEBASICITEM_H
#define QFOLDLINEBASICITEM_H

#include "view/qpolygonitem.h"
#include "Frame/DrawDlg/qbasicgraphicsitem.h"

class QFoldLineBasicItem : public QFoldLineItem, public QBasicGraphicsItem
{
public:
    QFoldLineBasicItem();
    QFoldLineBasicItem(const QPainterPath &path, QGraphicsItem *parent = 0);

    enum { Type = UserType + 39 };
    int type() const
      { return Type;}

    QFoldLineBasicItem *Clone();

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);
private:
    friend QDataStream &operator<<(QDataStream &stream, QFoldLineBasicItem *pFoldLineItem);
    friend QDataStream &operator>>(QDataStream &stream, QFoldLineBasicItem *pFoldLineItem);
};

#endif // QFOLDLINEBASICITEM_H
