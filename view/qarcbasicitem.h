#ifndef QARCBASICITEM_H
#define QARCBASICITEM_H

#include "view/QArcItem.h"
#include "Frame/DrawDlg/qbasicgraphicsitem.h"
class QArcBasicItem : public QArcItem, public QBasicGraphicsItem
{
public:
    QArcBasicItem();

    enum { Type = UserType + 44 };
    int type() const
      { return Type;}

    QArcBasicItem *Clone();

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);
private:
    friend QDataStream &operator<<(QDataStream &stream, QArcBasicItem *pArcItem);
    friend QDataStream &operator>>(QDataStream &stream, QArcBasicItem *pArcItem);
};

#endif // QARCBASICITEM_H
