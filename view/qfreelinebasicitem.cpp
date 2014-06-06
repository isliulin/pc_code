#include "qfreelinebasicitem.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QFreeLineBasicItem::QFreeLineBasicItem()
    :QFreeLineItem()
{
}

QFreeLineBasicItem::QFreeLineBasicItem(const QPainterPath &path, QGraphicsItem *parent /*= 0*/)
    :QFreeLineItem(path, parent)
{

}

QFreeLineBasicItem * QFreeLineBasicItem::Clone()
{
    QFreeLineBasicItem *pClone = new QFreeLineBasicItem();
    if (!pClone)
    {
        return NULL;
    }

    QPainterPath path = this->path();
    path = this->mapToScene(path);
//    pClone->SetName(this->GetName());
    pClone->setPath(path);
    pClone->setPen(this->pen());
    pClone->setLineType(this->getLineType());
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->m_eLineEndArrowType = this->m_eLineEndArrowType;
    pClone->setId(id());

    pClone->SaveSecurityPro(&(this->sPro));
    return pClone;
}

void QFreeLineBasicItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    QFreeLineItem::compile(db, nSceneId, count, index);
    QBasicGraphicsItem::compile(db, nSceneId, count, index);
}

QDataStream &operator<<(QDataStream &stream, QFreeLineBasicItem *pFreeLineItem)
{
    stream << pFreeLineItem->path();
    stream << pFreeLineItem->getAlpha();
    stream << pFreeLineItem->pen().width() << pFreeLineItem->pen().color();
    stream << pFreeLineItem->scenePos();
    stream << pFreeLineItem->isVisible();
    stream << pFreeLineItem->getName() << pFreeLineItem->nLineType;
    stream << pFreeLineItem->getEndArrow() << pFreeLineItem->getEndPointShape();
    stream << pFreeLineItem->data(GROUP_TYPE_KEY).toInt();
    stream << pFreeLineItem->data(GROUP_DATALIST_KEY).toStringList();

    if(pwnd->getProVersion() >= 3271)
    {
        pFreeLineItem->save(stream);
    }
    stream << pFreeLineItem->id();
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QFreeLineBasicItem *pFreeLineItem)
{
    QPainterPath path;
    QColor penColor;
    int penWidth;
    QPen pen;
    int alpha;
    QPointF pos;
    QString name ;
    int nEndArrow, nEndShape;
    int typeKey = 0;
    QStringList dataList;
    dataList.clear();
    bool bVisible = true;

    stream >> path >> alpha >> penWidth >> penColor;
    stream >> pos >> bVisible >> name >> pFreeLineItem->nLineType;
    stream >> nEndArrow >> nEndShape >> typeKey >> dataList;
    if(pwnd->getProVersion() >= 3271)
    {
         pFreeLineItem->load(stream);
    }
    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }

    pen.setWidth(penWidth);
    pen.setColor(penColor);
    pFreeLineItem->setPath(path);
    pFreeLineItem->setPen(pen);
    pFreeLineItem->setAlpha(alpha);
    pFreeLineItem->setPos(pos);
    pFreeLineItem->setVisible(bVisible);
    pFreeLineItem->setName(name);
    pFreeLineItem->setLineType(pFreeLineItem->nLineType);
    pFreeLineItem->setEndArrow(nEndArrow);
    pFreeLineItem->setEndPointShape(nEndShape);
    pFreeLineItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pFreeLineItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pFreeLineItem->setId(id);
    return stream;
}
