#include "qpolygonbasicitem.h"
#include "Frame/mainwindow.h"
extern  MainWindow *pwnd;

QPolygonBasicItem::QPolygonBasicItem()
    :QPolygonItem()
{
}

QPolygonBasicItem::QPolygonBasicItem(QPolygonF &qpsPolygonF)
    :QPolygonItem(qpsPolygonF)
{

}

QPolygonBasicItem * QPolygonBasicItem::Clone()
{
    QPolygonBasicItem *pClone = new QPolygonBasicItem();
    if (!pClone)
    {
        return NULL;
    }

    QPolygonF polygon = this->polygon();
    polygon = this->mapToScene(polygon);
    pClone->SetName(this->GetName());
    pClone->setPolygon(polygon);
    pClone->setPen(this->pen());
    pClone->setLineType(this->getLineType());
    pClone->setBackColor(this->getBackColor());
    pClone->setFrontColor(this->getFrontColor());
    pClone->setPattern(this->getPattern());
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->setId(id());

    pClone->SaveSecurityPro(&(this->sPro));

    return pClone;
}

void QPolygonBasicItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    QPolygonItem::compile(db, nSceneId, count, index);
    QBasicGraphicsItem::compile(db, nSceneId, count, index);
}

QDataStream &operator<<(QDataStream &stream, QPolygonBasicItem *pPolygonItem)
{
    stream << pPolygonItem->GetName();
    stream << pPolygonItem->polygon();
    stream << pPolygonItem->getAlpha();
    stream << pPolygonItem->getLineType();
    stream << pPolygonItem->getLineWidth();
    stream << pPolygonItem->getLineColor();
    stream << pPolygonItem->getBackColor();
    stream << pPolygonItem->getFrontColor();
    stream << pPolygonItem->getPattern();
    stream << pPolygonItem->scenePos();
    stream << pPolygonItem->isVisible();
    stream << pPolygonItem->data(GROUP_TYPE_KEY).toInt();
    stream << pPolygonItem->data(GROUP_DATALIST_KEY).toStringList();
    if(pwnd->getProVersion() >= 3271)
    {
        pPolygonItem->save(stream);
    }
    stream << pPolygonItem->id();
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QPolygonBasicItem *pPolygonItem)
{
    int nAlpha, lineType,lineWidth;
    QColor lineColor;
    QPointF pos;
    QPolygonF polygon;
    QString name ;
    int typeKey = 0;
    QStringList dataList;
    dataList.clear();
    bool bVisible = true;

    stream >> name ;
    stream >> polygon >> nAlpha >> lineType >> lineWidth >> lineColor;
    stream >> pPolygonItem->m_backColor >> pPolygonItem->m_frontColor;
    stream >> pPolygonItem->m_nPattern >> pos >> bVisible >> typeKey >> dataList;
    if(pwnd->getProVersion()>= 3271)
    {
        pPolygonItem->load(stream);
    }
    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }
    pPolygonItem->SetName(name);
    pPolygonItem->setPolygon(polygon);
    pPolygonItem->setAlpha(nAlpha);
    pPolygonItem->setLineType(lineType);
    pPolygonItem->setLineWidth(lineWidth);
    pPolygonItem->setLineColor(lineColor);
    pPolygonItem->setPattern(pPolygonItem->m_nPattern);
    pPolygonItem->setPos(pos);
    pPolygonItem->setVisible(bVisible);
    pPolygonItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pPolygonItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pPolygonItem->setId(id);

    return stream;
}

