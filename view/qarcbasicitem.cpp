#include "qarcbasicitem.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QArcBasicItem::QArcBasicItem()
    :QArcItem()
{
}

QArcBasicItem * QArcBasicItem::Clone()
{
    QArcBasicItem *pClone = new QArcBasicItem();
    if (!pClone)
    {
        return NULL;
    }

    QRectF qrcRect = this->sceneBoundingRect();
    pClone->setPath(this->m_ArcPath);
//    pClone->qHeight = this->qHeight;
//    pClone->qWidth = this->qWidth;
    pClone->m_qrcEllipseBndRect = this->m_qrcEllipseBndRect;
    pClone->SetStartAngle(this->GetStartAngle());
    pClone->SetSpanAngle(this->GetSpanAngle());
    pClone->SetBackColor(this->GetBackColor());
    pClone->SetFrontColor(this->GetFrontColor());
    pClone->SetPattern(this->GetPattern());
    pClone->SetLineType(this->GetLineType());
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->SetName(this->GetName());
    pClone->SetLineColor(this->GetLineColor());
    pClone->SetLineWidth(this->GetLineWidth());
    QPointF pt = pClone->boundingRect().topLeft();
    pClone->setPos(qrcRect.topLeft()-pt);
    pClone->SetAlpha(this->GetAlpha());

    pClone->setId(id());
    pClone->SaveSecurityPro(&(this->sPro));
    return pClone;
}

void QArcBasicItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    QArcItem::compile(db, nSceneId, count, index);
    QBasicGraphicsItem::compile(db, nSceneId, count, index);
}

QDataStream &operator<<(QDataStream &stream, QArcBasicItem *pArcItem)
{
    stream << pArcItem->path();
    //stream << pArcItem->GetWidth() << pArcItem->GetHeight();
    stream << pArcItem->getEllipseRect();
    stream << pArcItem->GetStartAngle() << pArcItem->GetSpanAngle();
    stream << pArcItem->pen().color() << pArcItem->pen().width();
    stream << pArcItem->nBackColor << pArcItem->nFrontColor;
    stream << pArcItem->nPatternType << pArcItem->scenePos();
    stream << pArcItem->nLineType << pArcItem->GetAlpha();
    stream << pArcItem->GetName();
    stream << pArcItem->isVisible();
    stream << pArcItem->data(GROUP_TYPE_KEY).toInt();
    stream << pArcItem->data(GROUP_DATALIST_KEY).toStringList();
    if(pwnd->getProVersion() >= 3271)
    {
        pArcItem->save(stream);
    }
    stream << pArcItem->id();
    return stream ;
}

QDataStream &operator>>(QDataStream &stream, QArcBasicItem *pArcItem)
{
    QPainterPath path;
    QColor lineColor;
    int lineWidth,patternType,alpha;
    qreal startAngle,spanAngle;
    QPointF scenePos;
    QString name ;
    int typeKey = 0;
    QStringList dataList;
    QRectF qrcRect;
    bool bVisible = true;

    stream >> path;
    //stream >> pArcItem->qWidth >> pArcItem->qHeight;
    stream >> qrcRect;
    stream >> startAngle >> spanAngle;
    stream >> lineColor >> lineWidth;
    stream >> pArcItem->nBackColor >> pArcItem->nFrontColor;
    stream >> patternType >> scenePos;
    stream >> pArcItem->nLineType >> alpha;
    stream >> name >> bVisible >> typeKey >> dataList;
    if(pwnd->getProVersion() >= 3271)
    {
        pArcItem->load(stream);
    }
    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }
    pArcItem->setRectA(qrcRect);
    pArcItem->setPath(path);
    pArcItem->SetSpanAngle(spanAngle);
    pArcItem->SetStartAngle(startAngle);
    pArcItem->SetLineColor(lineColor);
    pArcItem->SetLineWidth(lineWidth);
    pArcItem->SetLineType(pArcItem->nLineType);
    pArcItem->SetAlpha(alpha);
    pArcItem->setPos(scenePos);
    pArcItem->SetName(name);
    pArcItem->setVisible(bVisible);
    pArcItem->SetPattern(patternType);
    pArcItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pArcItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pArcItem->setId(id);
    return stream ;
}

