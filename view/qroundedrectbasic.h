#ifndef QROUNDEDRECTBASIC_H
#define QROUNDEDRECTBASIC_H

#include "view/QRoundedRect.h"
#include "Frame/DrawDlg/qbasicgraphicsitem.h"

class QRoundedRectBasic : public QRoundedRect, public QBasicGraphicsItem
{
public:
    QRoundedRectBasic();
    //QRoundedRectBasic(const QRectF &rect, QGraphicsItem *parent = 0);

    enum { Type = UserType + 43 };
    int type() const
      { return Type;}

    QRoundedRectBasic *Clone();

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);
private:
    friend QDataStream &operator<<(QDataStream &stream, QRoundedRectBasic *pRoundRectItem);
    friend QDataStream &operator>>(QDataStream &stream, QRoundedRectBasic *pRoundRectItem);

};
#endif // QROUNDEDRECTBASIC_H
