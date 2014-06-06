#include "qroundedrectbasic.h"
#include "Frame/mainwindow.h"
extern  MainWindow *pwnd;

QRoundedRectBasic::QRoundedRectBasic()
    :QRoundedRect()
{
}

QRoundedRectBasic * QRoundedRectBasic::Clone()
{
    QRoundedRectBasic *pClone = new QRoundedRectBasic();
    if (!pClone)
    {
        return NULL;
    }

    QRectF qrcRect = this->sceneBoundingRect();
    pClone->setPath(RectPath);
    pClone->SetxRadius(this->GetxRadius());
    pClone->SetyRadius(this->GetyRadius());
    pClone->SetBackColor(this->GetBackColor());
    pClone->SetFrontColor(this->GetFrontColor());
    pClone->SetPattern(this->GetPattern());
    pClone->SetLineType(this->GetLineType());
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->SetName(this->GetName());
    pClone->SetLineColor(this->GetLineColor());
    pClone->SetLineWidth(this->GetLineWidth());
    pClone->SetHeight(this->GetHeight());
    pClone->SetWidth(this->GetWidth());
    QPointF pt = pClone->boundingRect().topLeft();
    pClone->setPos(qrcRect.topLeft()-pt);
    pClone->SetAlpha(pClone->GetAlpha());
    pClone->setId(id());

    pClone->SaveSecurityPro(&(this->sPro));
    return pClone;
}

void QRoundedRectBasic::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    QRoundedRect::compile(db, nSceneId, count, index);
    QBasicGraphicsItem::compile(db, nSceneId, count, index);
}

QDataStream &operator<<(QDataStream &stream, QRoundedRectBasic *pRoundRectItem)
{
    stream << pRoundRectItem->path();
    stream << pRoundRectItem->qWidth << pRoundRectItem->qHeight;
    stream << pRoundRectItem->xRadius << pRoundRectItem->yRadius;
    stream << pRoundRectItem->pen().color() << pRoundRectItem->pen().width();
    stream << pRoundRectItem->nBackColor << pRoundRectItem->nFrontColor;
    stream << pRoundRectItem->nPatternType << pRoundRectItem->scenePos();
    stream << pRoundRectItem->nLineType;
    stream << pRoundRectItem->GetName();
    stream << pRoundRectItem->isVisible();
    stream << pRoundRectItem->data(GROUP_TYPE_KEY).toInt();
    stream << pRoundRectItem->data(GROUP_DATALIST_KEY).toStringList();


    if(pwnd->getProVersion() >= 3271)
    {
        pRoundRectItem->save(stream);
    }
    stream << pRoundRectItem->id();
    return stream ;
}

QDataStream &operator>>(QDataStream &stream, QRoundedRectBasic *pRoundRectItem)
{
    QPainterPath rectPath;
    QString name;
    QColor penColor;
    int penWidth;
    QPen  pen;
    QPointF pos;
    int typeKey = 0;
    QStringList dataList;
    bool bVisible = true;

    stream >> rectPath;
    stream >> pRoundRectItem->qWidth >> pRoundRectItem->qHeight;
    stream >> pRoundRectItem->xRadius >> pRoundRectItem->yRadius;
    stream >> penColor >> penWidth;
    stream >> pRoundRectItem->nBackColor >> pRoundRectItem->nFrontColor;
    stream >> pRoundRectItem->nPatternType >> pos >> pRoundRectItem->nLineType;
    stream >> name >> bVisible >> typeKey >> dataList;

    if(pwnd->getProVersion() >= 3271)
    {
        pRoundRectItem->load(stream);
    }
    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }

    pen.setColor(penColor);
    pen.setWidth(penWidth);

    pRoundRectItem->setPath(rectPath);
//    pRoundRectItem->SetWidth(pRoundRectItem->qWidth);
//    pRoundRectItem->SetHeight(pRoundRectItem->qHeight);
//    pRoundRectItem->SetxRadius(pRoundRectItem->xRadius);
//    pRoundRectItem->SetyRadius(pRoundRectItem->yRadius);
    pRoundRectItem->setPen(pen);
    pRoundRectItem->SetPattern(pRoundRectItem->nPatternType);
    pRoundRectItem->setPos(pos);
    pRoundRectItem->SetLineType(pRoundRectItem->nLineType);
    pRoundRectItem->SetName(name);
    pRoundRectItem->setVisible(bVisible);
    pRoundRectItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pRoundRectItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pRoundRectItem->setId(id);
    return stream ;
}
