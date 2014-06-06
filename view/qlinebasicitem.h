#ifndef QLINEBASICITEM_H
#define QLINEBASICITEM_H

#include "view/qlineitem.h"
#include "Frame/DrawDlg/qbasicgraphicsitem.h"
#include "Frame/qprogectmanager.h"

class QLineBasicItem : public QLineItem, public QBasicGraphicsItem
{
public:
    QLineBasicItem();
    QLineBasicItem(const QPainterPath &path, QGraphicsItem *parent = 0);

    enum { Type = UserType + 37 };
    int type() const
      { return Type;}

    QLineBasicItem *Clone();

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);
private:
    friend QDataStream &operator<<(QDataStream &stream, QLineBasicItem *pLineItem);
    friend QDataStream &operator>>(QDataStream &stream, QLineBasicItem *pLineItem);
};

#endif // QLINEBASICITEM_H
