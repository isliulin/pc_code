#include "qlinecirclebasicitem.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QLineCircleBasicItem::QLineCircleBasicItem()
    :QLineCircleItem()
{
}

QLineCircleBasicItem::QLineCircleBasicItem(const QPainterPath &path, QGraphicsItem *parent /*= 0*/)
    :QLineCircleItem(path, parent)
{

}

QLineCircleBasicItem * QLineCircleBasicItem::Clone()
{
    QPainterPath path = this->path();
    path = this->mapToScene(path);
    QLineCircleBasicItem *pCircleItem = new QLineCircleBasicItem(path);
    pCircleItem->setPen(this->pen());
    pCircleItem->setLineType(this->getLineType());
    pCircleItem->m_eLineEndArrowType = this->m_eLineEndArrowType;

    pCircleItem->SaveSecurityPro(&(this->sPro));
    pCircleItem->setId(id());
    pCircleItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pCircleItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    return pCircleItem;
}

void QLineCircleBasicItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    QLineCircleItem::compile(db, nSceneId, count, index);
    QBasicGraphicsItem::compile(db, nSceneId, count, index);
}

QDataStream &operator<<(QDataStream &stream, QLineCircleBasicItem *pLineCircleItem)
{
    stream << pLineCircleItem->path();
    stream << pLineCircleItem->getAlpha();
    stream << pLineCircleItem->pen().width() << pLineCircleItem->pen().color();
    stream << pLineCircleItem->scenePos();
    stream << pLineCircleItem->isVisible();
    stream << pLineCircleItem->getName() << pLineCircleItem->nLineType;
    stream << pLineCircleItem->getEndArrow() << pLineCircleItem->getEndPointShape();
    stream << pLineCircleItem->data(GROUP_TYPE_KEY).toInt();
    stream << pLineCircleItem->data(GROUP_DATALIST_KEY).toStringList();

    if(pwnd->getProVersion() >= 3271)
    {
        pLineCircleItem->save(stream);
    }
    stream << pLineCircleItem->id();
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QLineCircleBasicItem *pLineCircleItem)
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
    stream >> pos >> bVisible >> name >> pLineCircleItem->nLineType;
    stream >> nEndArrow >> nEndShape >> typeKey >> dataList;
    if(pwnd->getProVersion() >= 3271)
    {
        pLineCircleItem->load(stream);
    }

    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }
    pen.setWidth(penWidth);
    pen.setColor(penColor);
    pLineCircleItem->setPath(path);
    pLineCircleItem->setPen(pen);
    pLineCircleItem->setAlpha(alpha);
    pLineCircleItem->setPos(pos);
    pLineCircleItem->setVisible(bVisible);
    pLineCircleItem->setName(name);
    pLineCircleItem->setLineType(pLineCircleItem->nLineType);
    pLineCircleItem->m_eLineEndArrowType = (LINE_END_ARROW_STYLE_E)nEndArrow;
    pLineCircleItem->setEndArrow(nEndArrow);
//    pLineCircleItem->setEndPointShape(nEndShape);
    pLineCircleItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pLineCircleItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pLineCircleItem->setId(id);
    return stream;
}
