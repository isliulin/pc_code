#include "qfoldlinebasicitem.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QFoldLineBasicItem::QFoldLineBasicItem()
    :QFoldLineItem()
{
}

QFoldLineBasicItem::QFoldLineBasicItem(const QPainterPath &path, QGraphicsItem *parent /*= 0*/)
    :QFoldLineItem(path, parent)
{

}

QFoldLineBasicItem * QFoldLineBasicItem::Clone()
{
    QFoldLineBasicItem *pClone = new QFoldLineBasicItem();
    if (!pClone)
    {
        return NULL;
    }

    QPainterPath path = this->path();
    path = this->mapToScene(path);
    pClone->SetName(this->GetName());
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

void QFoldLineBasicItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    QFoldLineItem::compile(db, nSceneId, count, index);
    QBasicGraphicsItem::compile(db, nSceneId, count, index);
}

QDataStream &operator<<(QDataStream &stream, QFoldLineBasicItem *pFoldLineItem)
{
    stream << pFoldLineItem->path();
    stream << pFoldLineItem->getAlpha();
    stream << pFoldLineItem->pen().width() << pFoldLineItem->pen().color();
    stream << pFoldLineItem->scenePos();
    stream << pFoldLineItem->isVisible();
    stream << pFoldLineItem->GetName() << pFoldLineItem->nLineType;
    stream << pFoldLineItem->getEndArrow() << pFoldLineItem->getEndPointShape();
    stream << pFoldLineItem->data(GROUP_TYPE_KEY).toInt();
    stream << pFoldLineItem->data(GROUP_DATALIST_KEY).toStringList();
    if(pwnd->getProVersion() >= 3271)
    {
       pFoldLineItem->save(stream);
    }
    stream << pFoldLineItem->id();
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QFoldLineBasicItem *pFoldLineItem)
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
    stream >> pos >> bVisible >> name >> pFoldLineItem->nLineType;
    stream >> nEndArrow >> nEndShape >> typeKey >> dataList;
    if(pwnd->getProVersion() >= 3271)
    {
        pFoldLineItem->load(stream);
    }

    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }
    pen.setWidth(penWidth);
    pen.setColor(penColor);
    pFoldLineItem->setPath(path);
    pFoldLineItem->setPen(pen);
    pFoldLineItem->setAlpha(alpha);
    pFoldLineItem->setPos(pos);
    pFoldLineItem->setVisible(bVisible);
    pFoldLineItem->SetName(name);
    pFoldLineItem->setLineType(pFoldLineItem->nLineType);
    pFoldLineItem->setEndArrow(nEndArrow);
    pFoldLineItem->setEndPointShape(nEndShape);
    pFoldLineItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pFoldLineItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pFoldLineItem->setId(id);
    return stream;
}
