#ifndef QELIPSEBASICITEM_H
#define QELIPSEBASICITEM_H

#include "view/qelipseitem.h"
#include "Frame/DrawDlg/qbasicgraphicsitem.h"
class QElipseBasicItem : public QElipseItem, public QBasicGraphicsItem
{
public:
    QElipseBasicItem();
    QElipseBasicItem(QRectF &rect);

    enum { Type = UserType + 36 };
    int type() const
      { return Type;}

    QElipseBasicItem *Clone();

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);
private:
    friend QDataStream &operator<<(QDataStream &stream, QElipseBasicItem *pElipseItem);
    friend QDataStream &operator>>(QDataStream &stream, QElipseBasicItem *pElipseItem);
};

#endif // QELIPSEBASICITEM_H
