#ifndef QPIXMAPITEM_H
#define QPIXMAPITEM_H

#include <QGraphicsPixmapItem>

class QPixmapItem : public QGraphicsPixmapItem
{
public:
    QPixmapItem();
    QPixmapItem(const QPixmap &pixmap,QSize size);
    enum { Type = UserType + 24 };
    int type() const
    {
        return Type;
    }
    QRectF boundRect;
    QPixmap * pic;
    QPixmapItem *Clone();
    void compile(QSqlDatabase &db, int nSceneId,int &count,int index);

    void updatePic(QRectF scaleRect);
    QPixmap getPixmap();
    void SavePixmap(QPixmap pixmap);
    QPixmap GetFixPixmap();
    void SetRect(QRectF rect);
    void updateSize(QRectF rect);
    void UpdataPos();
    void SetName(QString sName);
    QString GetName();

private:
    friend QDataStream &operator<<(QDataStream &stream, QPixmapItem *pPixmap);
    friend QDataStream &operator>>(QDataStream &stream, QPixmapItem *pPixmap);
};

#endif // QPIXMAPITEM_H

