#include "qpixmapitem.h"

QPixmapItem::QPixmapItem():QGraphicsPixmapItem()
{
    pic = new QPixmap();
}

QPixmapItem::QPixmapItem(const QPixmap &pixmap,QSize size)
    :QGraphicsPixmapItem(pixmap.scaled(size))
{
    pic = new QPixmap();
    *pic = pixmap;
    boundRect = this->sceneBoundingRect();
}

void QPixmapItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{}
QPixmapItem *QPixmapItem::Clone()
{
    QRectF pixmapRect = this->sceneBoundingRect();
    qDebug()<<this->sceneBoundingRect()<<"pixmap";
    QPixmap pPixmap = this->getPixmap();
    if(pPixmap.isNull())
        pPixmap = QPixmap(pixmapRect.size().toSize());
        //return NULL;
    QPixmapItem *pClone =new QPixmapItem(pPixmap,QSize(pixmapRect.width(),pixmapRect.height()));
    if(!pClone)
    {
        return NULL;
    }
    pClone->setPos(pixmapRect.x(),pixmapRect.y());
    pClone->SetRect(pixmapRect);
    pClone->SetName(this->GetName());

    return pClone;
}
void QPixmapItem::updatePic(QRectF scaleRect)
{
    QPointF ItemPos = this->mapFromScene(scaleRect.topLeft());
    ItemPos = this->mapToParent(ItemPos);
    QRectF rect = this->boundingRect();
    QPixmap newPicture;
    if (!pic)
    {
        return ;
    }
    newPicture = pic->scaled(scaleRect.width(),scaleRect.height());
    this->setPixmap(newPicture);
    this->setPos(ItemPos.x(),ItemPos.y());
}
void QPixmapItem::updateSize(QRectF rect)
{
    QRectF rc = this->boundRect;
    rc = QRectF(rc.topLeft(),rect.size());
    this->boundRect = rc;
    QPixmap newPicture;
    if (!pic)
    {
        return ;
    }
    newPicture = pic->scaled(rect.width(),rect.height());
    this->setPixmap(newPicture);
}
QPixmap QPixmapItem::getPixmap()
{
    return *pic;
}
void QPixmapItem::SavePixmap(QPixmap pixmap)
{

}
QPixmap QPixmapItem::GetFixPixmap()
{
    QPixmap picInDataarea;
    QSize size = this->pixmap().size();
    picInDataarea = pic->scaled(size);
    return picInDataarea;
}
void QPixmapItem::SetRect(QRectF rect)
{
    this->boundRect = rect;
    this->updatePic(rect);
}
void QPixmapItem::UpdataPos()
{
    this->boundRect=this->sceneBoundingRect();
}
QDataStream &operator<<(QDataStream &stream, QPixmapItem *pPixmap)
{
    stream << pPixmap->boundingRect().size().toSize();
    qDebug() <<"QPixmapItem operator<<size"<< pPixmap->boundingRect().size();
    stream << pPixmap->getPixmap();
    stream << pPixmap->scenePos();
    stream << pPixmap->isVisible();
    stream << pPixmap->GetName();
    stream << pPixmap->data(GROUP_TYPE_KEY).toInt();
    stream << pPixmap->data(GROUP_DATALIST_KEY).toStringList();
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QPixmapItem *pPixmap)
{
    QSize size;
    QPixmap pixmap;
    QPointF scenePos;
    QString name ;
    int typeKey = 0;
    QStringList dataList;
    bool bVisible = true;

    stream >> size;
    stream >> pixmap;
    *(pPixmap->pic) = pixmap;
    stream >> scenePos;
    stream >> bVisible;
    stream >> name;
    stream >> typeKey;
    stream >> dataList;

    if(!pixmap.isNull())
    {
        pixmap = pixmap.scaled(size);
        qDebug() <<"QPixmapItem operator>>size"<< pPixmap->boundingRect().size();
    }
    pPixmap->setPixmap(pixmap);
    pPixmap->setPos(scenePos);
    pPixmap->setVisible(bVisible);
    pPixmap->SetName(name);
    pPixmap->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pPixmap->setData(GROUP_DATALIST_KEY,QVariant(dataList));


    return stream;
}

void QPixmapItem::SetName(QString sName)
{
    setData(GROUP_NAME_KEY,QVariant(sName));
}

QString QPixmapItem::GetName()
{
    return data(GROUP_NAME_KEY).toString();
}
