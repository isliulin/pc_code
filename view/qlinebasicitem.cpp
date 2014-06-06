#include "qlinebasicitem.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QLineBasicItem::QLineBasicItem()
    :QLineItem()
{
}

QLineBasicItem::QLineBasicItem(const QPainterPath &path, QGraphicsItem *parent /*= 0*/)
    :QLineItem(path, parent)
{

}

QLineBasicItem * QLineBasicItem::Clone()
{
    QLineBasicItem *pClone = new QLineBasicItem();
    if (!pClone)
    {
        return NULL;
    }
    QPainterPath path = this->path();
    pClone->setPath(this->mapToScene(path));
    pClone->setPen(this->pen());

    pClone->setLineType(this->getLineType());
    pClone->setLineWidth(this->getLineWidth());
    //pClone->setEndArrow(this->getEndArrow());

    pClone->SetName(this->GetName());
    pClone->setPos(this->mapFromScene(this->scenePos()));
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->setVisible(this->isVisible());
    pClone->m_eLineEndArrowType = this->m_eLineEndArrowType;
    pClone->SaveSecurityPro(&(this->sPro));
    pClone->setId(id());

    return pClone;
}

void QLineBasicItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    QLineItem::compile(db, nSceneId, count, index);
    QBasicGraphicsItem::compile(db, nSceneId, count, index);
}

QDataStream &operator<<(QDataStream &stream, QLineBasicItem *pLineItem)
{
    stream << pLineItem->path();
    stream << pLineItem->getAlpha();
    stream << pLineItem->pen().width() << pLineItem->pen().color();
    stream << pLineItem->scenePos();
    stream << pLineItem->isVisible();
    stream << pLineItem->GetName() << pLineItem->getLineType();
    stream << pLineItem->getEndArrow() << pLineItem->getEndPointShape();
    stream << pLineItem->data(GROUP_TYPE_KEY).toInt();
    stream << pLineItem->data(GROUP_DATALIST_KEY).toStringList();

    if(pwnd->getProVersion() >= 3271)
    {
       pLineItem->save(stream);
    }
    stream << pLineItem->id();

    return stream;
}

QDataStream &operator>>(QDataStream &stream, QLineBasicItem *pLineItem)
{
    QPainterPath path;
    QPen pen;
    QColor penColor;
    int penWidth;
    int alpha;
    QPointF pos;
    QString name ;
    int nEndArrow, nEndShape;
    int typeKey = 0;
    QStringList dataList;
    dataList.clear();
    bool bVisible = true;
    int iLineType = -1;

    stream >> path >> alpha >> penWidth >>penColor;
    stream >> pos >> bVisible >> name >> iLineType;
    stream >> nEndArrow >> nEndShape >> typeKey >> dataList;

    pLineItem->setLineType(iLineType);

    if(pwnd->getProVersion() >= 3271)
    {
        pLineItem->load(stream);
    }

    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }
    pen.setColor(penColor);
    pen.setWidth(penWidth);
    pLineItem->setPath(path);
    pLineItem->setPen(pen);
    pLineItem->setAlpha(alpha);
    pLineItem->setPos(pos);
    pLineItem->setVisible(bVisible);
    pLineItem->SetName(name);
    pLineItem->setLineType(pLineItem->getLineType());
    pLineItem->setEndArrow(nEndArrow);
    pLineItem->setEndPointShape(nEndShape);
    pLineItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pLineItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pLineItem->setId(id);
    return stream;
}
