#include "qrectbasicitem.h"
#include "Frame/mainwindow.h"
extern  MainWindow *pwnd;

QRectBasicItem::QRectBasicItem()
    :QRectItem()
{
}

QRectBasicItem::QRectBasicItem(const QRectF &rect, QGraphicsItem *parent/* = 0*/)
    :QRectItem(rect, parent)
{

}

QRectBasicItem * QRectBasicItem::Clone()
{
    QRectBasicItem *pClone = new QRectBasicItem();
    if (!pClone)
    {
        return NULL;
    }

    QRectF qrcRect = this->rect();
    pClone->setRect(this->mapRectToScene(qrcRect));
    pClone->SetBackColor(this->GetBackColor());
    pClone->SetFrontColor(this->GetFrontColor());
    pClone->SetPattern(this->GetPattern());
    pClone->SetLineType(this->GetLineType());
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->SetName(this->GetName());
    pClone->SetLineColor(this->GetLineColor());
    pClone->SetLineWidth(this->GetLineWidth());
    pClone->SetId(this->GetID());
    pClone->setId(id());

    pClone->SaveSecurityPro(&(this->sPro));
    return pClone;
}

void QRectBasicItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    QRectItem::compile(db, nSceneId, count, index);
    QBasicGraphicsItem::compile(db, nSceneId, count, index);
}

QDataStream &operator<<(QDataStream &stream, QRectBasicItem *pRectItem)
{
    //    stream << pRectItem->rect() << pRectItem->pen();
    stream << pRectItem->rect().topLeft() << pRectItem->rect().bottomRight();
    stream << pRectItem->pen().color() << pRectItem->pen().width();
    stream << pRectItem->GetBackColor() << pRectItem->GetFrontColor();
    stream << pRectItem->GetPattern() << pRectItem->scenePos();
    stream << pRectItem->GetLineType();
    stream << pRectItem->isVisible();
    stream << pRectItem->GetName() << pRectItem->GetID();
    stream << pRectItem->data(GROUP_TYPE_KEY).toInt();
    stream << pRectItem->data(GROUP_DATALIST_KEY).toStringList();
    if(pwnd->getProVersion() >= 3271)
    {
        pRectItem->save(stream);
    }
    stream << pRectItem->id();
    return stream ;
}

QDataStream &operator>>(QDataStream &stream, QRectBasicItem *pRectItem)
{
    QString name;
    int id ;
    QColor penColor;
    int penWidth;
    QPen  pen;
    QPointF pos;
    QPointF ptopLeft,pbottomRight;
    int typeKey = 0;
    QStringList dataList;
    bool bVisible = true;
   // stream >> rect >> pen;
    stream >> ptopLeft >> pbottomRight >> penColor >> penWidth;
    stream >> pRectItem->nBackColor >> pRectItem->nFrontColor;
    stream >> pRectItem->nPatternType >> pos >> pRectItem->nLineType;
    stream >> bVisible >> name >> id >> typeKey >> dataList;

    if(pwnd->getProVersion() >= 3271)
    {
        pRectItem->load(stream);
    }

    int nId = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> nId;
    }
    QRectF rect = QRectF(ptopLeft,pbottomRight);
    pen.setColor(penColor);
    pen.setWidth(penWidth);


    pRectItem->setPen(pen);
    pRectItem->setRect(rect);
    pRectItem->SetPattern(pRectItem->nPatternType);
    pRectItem->setPos(pos);
    pRectItem->SetLineType(pRectItem->nLineType);
    pRectItem->SetName(name);
    pRectItem->setVisible(bVisible);
    pRectItem->SetId(id);
    pRectItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pRectItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pRectItem->setId(nId);
    return stream ;
}
