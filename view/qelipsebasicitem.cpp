#include "qelipsebasicitem.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QElipseBasicItem::QElipseBasicItem()
    :QElipseItem()
{
}

QElipseBasicItem::QElipseBasicItem(QRectF &rect)
    :QElipseItem(rect)
{

}

QElipseBasicItem * QElipseBasicItem::Clone()
{
    QElipseBasicItem *pClone = NULL;
    int angle = this->GetSpanAngle();
    if (angle != 360)//ÉÈÐÎ
    {
        QRectF qrcRect = this->rect();
        //qrcRect = this->mapRectToScene(qrcRect);
        QRectF rc = this->sceneBoundingRect();
        //QPointF ItemPos = this->mapFromScene(rc.topLeft());
         //ItemPos = this->mapToParent(ItemPos);
        pClone = new QElipseBasicItem(qrcRect);
        if (!pClone)
        {
                return NULL;
        }
        pClone->SetSpanAngle(this->GetSpanAngle());
        pClone->SetStartAngle(this->GetStartAngle());
        QRectF rect = pClone->boundingRect();
        pClone->setPos(rc.topLeft()-rect.topLeft());
    }
    else//Ô²
    {
        QRectF rc = this->sceneBoundingRect();
        pClone = new QElipseBasicItem(rc);
        if (!pClone)
        {
            return NULL;
        }
    }

    pClone->setPen(this->pen());
    pClone->SetBackColor(this->GetBackColor());
    pClone->SetFrontColor(this->GetFrontColor());
    pClone->SetPattern(this->GetPattern());
    pClone->SetName(this->GetName());

    pClone->SetLineType(this->GetLineType());
    pClone->setPropor(this->getPropor(),this->GetPattern());
   // pClone->SetLineWidth(this->GetLineWidth());
    //pClone->SetLineColor(this->GetLineColor());

    pClone->SaveSecurityPro(&(this->sPro));

    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->setId(id());

    return pClone;
}

void QElipseBasicItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    QElipseItem::compile(db, nSceneId, count, index);
    QBasicGraphicsItem::compile(db, nSceneId, count, index);
}

QDataStream &operator<<(QDataStream &stream, QElipseBasicItem *pElipseItem)
{
    stream << pElipseItem->pen().color();
    stream << pElipseItem->pen().width();
    stream << pElipseItem->rect().topLeft();
    stream << pElipseItem->rect().bottomRight();
    stream << pElipseItem->GetName(); //get item name, type:QString;
    stream << pElipseItem->GetID();   //get the item id,type:int
    stream << pElipseItem->GetPattern();  //get style,type:int
//    stream << pElipseItem->pen();         //get pen ,type:QPen
    stream << pElipseItem->GetLineType();
    stream << pElipseItem->GetAngle();    //get circle Rotation type:qreal
    stream << pElipseItem->nBackColor;    //get backcolor
    stream << pElipseItem->nFrontColor;   //get frontcolor
    stream << pElipseItem->GetSpanAngle(); //get Span Angle,need by 16,type:int
    stream << pElipseItem->GetStartAngle(); //get start angle, type:int
    stream << pElipseItem->GetDescription(); //get Graphic storage properties, type:QStringList
//    stream << pElipseItem->rect();           //get the circle Bounding rectangle,type:QRectF
    stream << pElipseItem->scenePos();
    stream << pElipseItem->isVisible();
    stream << pElipseItem->data(GROUP_TYPE_KEY).toInt();
    stream << pElipseItem->data(GROUP_DATALIST_KEY).toStringList();
    stream << pElipseItem->getPropor();

    if(pwnd->getProVersion() >= 3271)
    {
        pElipseItem->save(stream);
    }
    stream << pElipseItem->id();
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QElipseBasicItem *pElipseItem)
{
    QString name;
    int id,pattern;
    float nPropor;
    QPen pen;
    int lineType;
    qreal angle;
    QColor penColor;
    int penWidth;
    int spanAngle,startAngle;
    QStringList description;
    QPointF pos, topLeft, bottomRight;
    int typeKey = 0;
    QStringList dataList;
    dataList.clear();
    bool bVisible = true;

    stream >> penColor >> penWidth >> topLeft >> bottomRight;
    stream >> name >> id >> pattern >> lineType >> angle >> pElipseItem->nBackColor;
    stream >> pElipseItem->nFrontColor >> spanAngle >> startAngle >> description >> pos;
    stream >> bVisible >> typeKey >> dataList;
    stream >> nPropor;

    if(pwnd->getProVersion() >= 3271)
    {
        pElipseItem->load(stream);
    }

    int nId = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> nId;
    }
    pen.setColor(penColor);
    pen.setWidth(penWidth);
    pElipseItem->setRect(QRectF(topLeft, bottomRight));
    pElipseItem->SetName(name);
    pElipseItem->SetId(id);
    pElipseItem->SetPattern(pattern);
    pElipseItem->setPen(pen);
    pElipseItem->SetLineType(lineType);
    pElipseItem->SetAngle(angle);
    pElipseItem->SetSpanAngle(spanAngle);
    pElipseItem->SetStartAngle(startAngle);
    pElipseItem->SetDescription(description);
    pElipseItem->setPos(pos);
    pElipseItem->setVisible(bVisible);
    pElipseItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pElipseItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pElipseItem->setPropor(nPropor,pattern);
    pElipseItem->setId(nId);
    return stream;
}
