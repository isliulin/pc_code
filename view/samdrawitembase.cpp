/************************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2010
 *
 * Description: SamDrawItemBase class implementation .cpp file.
 *
 * Functions:
 *
 * Modification Log:
 * Date             Name             Description Of Change
 * 2010-10-22       Bruce nie        Creation.
 ***********************************************************************/
#include "view/samdrawitembase.h"

static const unsigned short SAMDRAW_OBJ_TRACKER_COUNT = 8;
static const unsigned short SAMDRAW_TRACKER_POS_OFT   = 3;
//static const unsigned short SAMDRAW_TRACKER_SIZE      = 5;

/***********************************************************************
 Class SamDrawItemBase constructor
 **********************************************************************/
SamDrawItemBase::SamDrawItemBase()
{
    m_bResizable = true;
    bFlag = false;
    bLockVisiable = true;
    m_LockTracker = NULL;
    m_id = 0;
}

/***********************************************************************
 Class SamDrawItemBase destructor
 **********************************************************************/
SamDrawItemBase::~SamDrawItemBase()
{
    int iSize = m_pvecTrackers.size();
    SamDrawTackerRect *pTracker = NULL;
    for (int i = 0; i < iSize; i++)
    {
        pTracker = m_pvecTrackers.at(i);
        if (pTracker)
        {
            //delete pTracker;
            pTracker = NULL;
        }
    }
    if(m_LockTracker)
    {
        delete m_LockTracker;
        m_LockTracker = NULL;
    }
}

/***********************************************************************
 *Funtion : Get the object handle count
 *Return  : integer handle count.
 *Parameter: none.
 **********************************************************************/
int SamDrawItemBase::getHandleCount() const
{
    return SAMDRAW_OBJ_TRACKER_COUNT;
}

/***********************************************************************
 *Funtion : Get the handle point
 *Return  : QPointF handle position.
 *Parameter: handle id.
 **********************************************************************/
QPointF SamDrawItemBase::getHandle(int iHandle, QRectF &qrcBondingRect) const
{
    double dx = 0.0, dy = 0.0, dxCenter = 0.0, dyCenter = 0.0;

    /*Scene rect of this object*/
    //QRectF CurPosRect = this->sceneBoundingRect();
    QRectF CurPosRect = qrcBondingRect;
    // this gets the center regardless of left/right and top/bottom ordering
    dxCenter = CurPosRect.left() + CurPosRect.width() / 2;
    dyCenter = CurPosRect.top() + CurPosRect.height() / 2;

    switch (iHandle)
    {
    default:
            break;
    case HANDLE_LEFT_TOP:
            dx = CurPosRect.left();
            dy = CurPosRect.top();
            break;

    case HANDLE_CENTER_TOP:
            dx = dxCenter;
            dy = CurPosRect.top();
            break;

    case HANDLE_RIGHT_TOP:
            dx = CurPosRect.right();
            dy = CurPosRect.top();
            break;

    case HANDLE_RIGHT_CENTER:
            dx = CurPosRect.right();
            dy = dyCenter;
            break;

    case HANDLE_RIGHT_BOTTOM:
            dx = CurPosRect.right();
            dy = CurPosRect.bottom();
            break;

    case HANDLE_CENTER_BOTTOM:
            dx = dxCenter;
            dy = CurPosRect.bottom();
            break;

    case HANDLE_LEFT_BOTTOM:
            dx = CurPosRect.left();
            dy = CurPosRect.bottom();
            break;

    case HANDLE_LEFT_CENTER:
            dx = CurPosRect.left();
            dy = dyCenter;
            break;
    }

    return QPointF(dx, dy);
}

/***********************************************************************
 *Funtion : Get the handle rect
 *Return  : QRectF handle rect.
 *Parameter: handle id.
 **********************************************************************/
QRectF SamDrawItemBase::getHandleRect(int iHandleID, QRectF &qrcBondingRect)
{
    QRectF qrRect;
    // get the center of the handle in logical coords
    QPointF qpPoint = getHandle(iHandleID, qrcBondingRect);

    /*Set the rect and normalize it*/
    qrRect.setRect(qpPoint.rx()-SAMDRAW_TRACKER_POS_OFT, qpPoint.ry()-SAMDRAW_TRACKER_POS_OFT, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
    qrRect = qrRect.normalized();

    return qrRect;
}

/***********************************************************************
 *Funtion : Get the handle cursor
 *Return  : Qt::CursorShape cursor.
 *Parameter: handle id.
 **********************************************************************/
QCursor SamDrawItemBase::getHandleCursor(int iHandle) const
{
    Qt::CursorShape eCurShape = Qt::ArrowCursor;

    switch (iHandle)
    {
    case HANDLE_LEFT_TOP:
    case HANDLE_RIGHT_BOTTOM:
        eCurShape = Qt::SizeFDiagCursor;
        break;
    case HANDLE_CENTER_TOP:
    case HANDLE_CENTER_BOTTOM:
        eCurShape = Qt::SizeVerCursor;
        break;
    case HANDLE_RIGHT_TOP:
    case HANDLE_LEFT_BOTTOM:
        eCurShape = Qt::SizeBDiagCursor;
        break;
    case HANDLE_RIGHT_CENTER:
    case HANDLE_LEFT_CENTER:
        eCurShape = Qt::SizeHorCursor;
        break;
    default:
        eCurShape = Qt::ArrowCursor;
        break;
    }

    return QCursor(eCurShape);
}

/***********************************************************************
 *Funtion : Hit test for the object
 *Return  : integer handle id.
 *Parameter: QPoint local mouse point, scene bonding rect, bool selected flag.
 **********************************************************************/
int SamDrawItemBase::hitTest(QPointF qpPoint, QRectF &qrcBondingRect, bool bSelected)
{
    if (this->getResizable() == false)
    {
        return 0;
    }

    /*Object is selected*/
    if (bSelected)
    {
        /*Check the handle, if the mouse point in it's area*/
        int iHandleCount = getHandleCount();
        for (int iHandle = 1; iHandle <= iHandleCount; iHandle++)
        {
            // GetHandleRect returns in logical coords
            QRectF qrcRect = getHandleRect(iHandle, qrcBondingRect);
            if ( (qpPoint.rx() >= qrcRect.left())
                && (qpPoint.rx() <= qrcRect.right())
                && (qpPoint.ry() >= qrcRect.top())
                && (qpPoint.ry() <= qrcRect.bottom()) )
            {
                return iHandle;
            }
        }
    }
    /*Object is not selected*/
    else
    {
        /*if ( qpPoint.rx() >= this->sceneBoundingRect().left()
            && qpPoint.rx() < this->sceneBoundingRect().right()
            && qpPoint.ry() <= this->sceneBoundingRect().top()
            && qpPoint.ry() > this->sceneBoundingRect().bottom() )*/
        if ( qpPoint.rx() >= qrcBondingRect.left()
                 && qpPoint.rx() < qrcBondingRect.right()
                 && qpPoint.ry() <= qrcBondingRect.top()
                 && qpPoint.ry() > qrcBondingRect.bottom() )
        {
            return 1;
        }
    }

    return 0;
}

/***********************************************************************
 *Funtion : Draw the trackers of object (common function in base calss)
 *Return  : none
 *Parameter: Tracker state, QGraphicsScene
 **********************************************************************/
void SamDrawItemBase::drawTracker(eTrackerState eState, QGraphicsScene *pScene, QRectF &qrcBondingRect)
{
    if (!pScene)
    {
        return;
    }

    if (this->getResizable() == false)
    {
        return;
    }

    m_pvecTrackers.clear();
    switch (eState)
    {
    case TRK_NORMAL:
        break;
    case TRK_SELECTED:
    case TRK_ACTIVE:
        {
            int iHandleCount = getHandleCount();
            for (int iHandle = 1; iHandle <= iHandleCount; iHandle++)
            {
                QPointF qpHandle = getHandle(iHandle, qrcBondingRect);
                SamDrawTackerRect *pItem = new SamDrawTackerRect(qpHandle);
                pScene->addItem(pItem);
                if (pItem)
                {
                    //item->setCursor(getHandleCursor(nHandle));
                    m_pvecTrackers.push_back(pItem);
                }
            }
        }
        break;
    default:
        break;
    }
}

/***********************************************************************
 *Funtion : Move the draged handle to mouse point
 *Return  : DRAG_CROSS_TYPE_E cross type
 *Parameter: integer draged handle id, QPointF mouse local point, scene bonding rect
 **********************************************************************/
QRectF SamDrawItemBase::moveHandleTo(int iDragHandle, QPointF qpLocal, QRectF &qrcBondingRect, bool bFoursquare)
{
    QRectF qrcPosition;

    //qrcPosition = this->sceneBoundingRect();
    qrcPosition = qrcBondingRect;
    switch (iDragHandle)
    {
    case HANDLE_LEFT_TOP:
            qrcPosition.setLeft(qpLocal.x());
            qrcPosition.setTop(qpLocal.y());
            if (bFoursquare)
            {
                qrcPosition.setLeft(qpLocal.x());
                qrcPosition.setTop(qpLocal.y());
                if (qrcPosition.height() > qrcPosition.width())
                {
                    qrcPosition.setLeft(qrcPosition.right() - qrcPosition.height());
                }
                else if (qrcPosition.height() < qrcPosition.width())
                {
                    qrcPosition.setTop(qrcPosition.bottom() - qrcPosition.width());
                }
            }
            break;
    case HANDLE_CENTER_TOP:
            qrcPosition.setTop(qpLocal.y());
            if (bFoursquare)
            {
                qrcPosition.setWidth(qrcPosition.height());
            }
            break;
    case HANDLE_RIGHT_TOP:
            qrcPosition.setRight(qpLocal.x());
            qrcPosition.setTop(qpLocal.y());
            if (bFoursquare)
            {
                if (qrcPosition.height() > qrcPosition.width())
                {
                    qrcPosition.setWidth(qrcPosition.height());
                }
                else if (qrcPosition.height() < qrcPosition.width())
                {
                    qrcPosition.setTop(qrcPosition.bottom() - qrcPosition.width());
                }
            }
            break;
    case HANDLE_RIGHT_CENTER:
            qrcPosition.setRight(qpLocal.x());
            if (bFoursquare)
            {
                qrcPosition.setHeight(qrcPosition.width());
            }
            break;
    case HANDLE_RIGHT_BOTTOM:
            qrcPosition.setRight(qpLocal.x());
            qrcPosition.setBottom(qpLocal.y());
            if (bFoursquare)
            {
                if (qrcPosition.height() > qrcPosition.width())
                {
                    qrcPosition.setWidth(qrcPosition.height());
                }
                else if (qrcPosition.height() < qrcPosition.width())
                {
                    qrcPosition.setHeight(qrcPosition.width());
                }
            }
            break;
    case HANDLE_CENTER_BOTTOM:
            qrcPosition.setBottom(qpLocal.y());
            if (bFoursquare)
            {
                qrcPosition.setWidth(qrcPosition.height());
            }
            break;
    case HANDLE_LEFT_BOTTOM:
            qrcPosition.setLeft(qpLocal.x());
            qrcPosition.setBottom(qpLocal.y());
            if (bFoursquare)
            {
                if (qrcPosition.height() > qrcPosition.width())
                {
                    qrcPosition.setLeft(qrcPosition.right() - qrcPosition.height());
                }
                else if (qrcPosition.height() < qrcPosition.width())
                {
                    qrcPosition.setHeight(qrcPosition.width());
                }
            }
            break;
    case HANDLE_LEFT_CENTER:
            qrcPosition.setLeft(qpLocal.x());
            if (bFoursquare)
            {
                qrcPosition.setHeight(qrcPosition.width());
            }
            break;
    default:
            return qrcPosition;
    }

    return qrcPosition;
}

/***********************************************************************
 *Funtion : Normalize the rect
 *Return  : DRAG_CROSS_TYPE_E cross type
 *Parameter: QRectF rect
 **********************************************************************/
DRAG_CROSS_TYPE_E SamDrawItemBase::NormalizeDragedRect(QRectF &qrRect)
{
    double dTemp = 0.0;
    DRAG_CROSS_TYPE_E eDragCrossType = DRAG_CROSS_TYPE_BUTT;

    if (qrRect.left() > qrRect.right())
    {
        dTemp = qrRect.left();
        qrRect.setLeft(qrRect.right());
        qrRect.setRight(dTemp);
        eDragCrossType = (DRAG_CROSS_TYPE_E) (eDragCrossType | DRAG_CROSS_LEFT_RIGHT);
    }
    if (qrRect.top() > qrRect.bottom())
    {
        dTemp = qrRect.top();
        qrRect.setTop(qrRect.bottom());
        qrRect.setBottom(dTemp);
        eDragCrossType = (DRAG_CROSS_TYPE_E) (eDragCrossType | DRAG_CROSS_TOP_BOTTON);
    }

    return eDragCrossType;
}

/***********************************************************************
 *Funtion : move all trackers rect
 *Return  : none
 *Parameter: QPointF delta point (point - last point)
 **********************************************************************/
void SamDrawItemBase::moveAllTrackersPos(const QPointF &qrcDelta)
{
    QPointF qrcCurPos;

    unsigned long ulSize = m_pvecTrackers.size();
    for (unsigned long i = 0; i < ulSize; i++)
    {
        if (m_pvecTrackers[i])
        {
            qrcCurPos = m_pvecTrackers[i]->scenePos();
            qrcCurPos += qrcDelta;
            m_pvecTrackers[i]->setPos(qrcCurPos);
        }
    }
}

/***********************************************************************
 *Funtion : Set the visiable property of trackers rect item
 *Return  : none
 *Parameter: bool bVisiable
 **********************************************************************/
void SamDrawItemBase::setTrackersVisiable(bool bVisiable)
{
    unsigned long ulSize = m_pvecTrackers.size();
    for (unsigned long i = 0; i < ulSize; i++)
    {
        if (m_pvecTrackers[i])
        {
            m_pvecTrackers[i]->setVisible(bVisiable);
        }
    }
}

/*********************************************************************************
 * Function: refresh trackers' position
 * Parameters: bonding rect
 * Return: none
 ********************************************************************************/
void SamDrawItemBase::refreshTrackers(const QRectF &qrcCurBndRect, QGraphicsScene *pScene)
{
    QRectF qrcRect = qrcCurBndRect;

    if (false == this->getResizable()) return;

    if (m_pvecTrackers.size() <= 0)
    {
        this->drawTracker(TRK_SELECTED, pScene, qrcRect);
        return;
    }

    int iHandleCnt = this->getHandleCount();
    for (int i = 1; i <= iHandleCnt; i++)
    {
        QPointF qrcPoint = getHandle(i, qrcRect);
        if (m_pvecTrackers[i-1] != NULL)
        {
            QRectF rect(qrcPoint.x()-3, qrcPoint.y()-3, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
            m_pvecTrackers[i-1]->setRect(rect);
            QBrush br = m_pvecTrackers[i-1]->brush();
            QPen pen = m_pvecTrackers[i-1]->pen();
            if(bFlag && br.color() != Qt::black)
            {
                br.setColor(Qt::black);
                pen.setColor(Qt::white);
                m_pvecTrackers[i-1]->setPen(pen);
                m_pvecTrackers[i-1]->setBrush(br);
            }
            else if(!bFlag && br.color() != Qt::green)
            {
                pen.setColor(Qt::black);
                m_pvecTrackers[i-1]->setPen(pen);
                br.setColor(Qt::green);
                m_pvecTrackers[i-1]->setBrush(br);
            }
        }
    }
}

/*********************************************************************************
 * Function: calculate the line parameters according to 2 points on line.
 * Parameters: point1, point2, k, b (y = kx + b)
 * Return: none
 ********************************************************************************/
void SamDrawItemBase::calculateLinePara(const QPointF &qpP1, const QPointF &qpP2,
    qreal &dK, qreal &dB, qreal &dXdirect, qreal &dYdirect)
{
    dB = dK = 0.0;
    const qreal dDelta = 0.5;

    /*Record the line X/Y direct*/
    qpP2.x() >= qpP1.x() ? dXdirect = 1 : dXdirect = -1;
    qpP2.y() >= qpP1.y() ? dYdirect = 1 : dYdirect = -1;

    /*Calculate the K value of the line*/
    qreal dDeltaX = qpP1.x() - qpP2.x();
    qreal dDeltaY = qpP1.y() - qpP2.y();
    if ( dDeltaX < -dDelta
         || dDeltaX > dDelta )
    {
        dB = (qpP2.y() * qpP1.x() - qpP1.y() * qpP2.x()) / dDeltaX;
    }

    /*The line is closed to Y axis*/
    else
    {
        dK = 99999;
        return;
    }

    /*The line is closed to X axis*/
    if ( (dDeltaY >= -dDelta)
        && (dDeltaY <= dDelta) )
    {
        dK = 0;
        return;
    }

    /*The line is between X and Y axis*/
    if (qpP1.x() > dDelta || qpP1.x() < -dDelta)
    {
        dK = (qpP1.y() - dB) / qpP1.x();
    }
}

/*********************************************************************************
 * Function: get the keypoints of end-arrow.
 * Parameters: k, end-point, key-point1, key-point2
 * Return: none
 ********************************************************************************/
void SamDrawItemBase::getEndArrowKeypoints(const qreal &dK, const QPointF &qpEndPt,
    LINE_KEY_POINT_T &stKeyppoints, const qreal dXdirect, const qreal dYdirect)
{
    const qreal dL = 12.0;
    qreal dKFactor = 0.0;
    qreal dVAngle = 0.0;
    const qreal dDelta = 0.01;
    QPointF qpKpt0, qpKpt1, qpKpt2, qpKpt3, qpKpt4, qpKpt5;

    /*K factor -1 or +1*/
    if (qFabs(dK) > 0)
    {
        dKFactor = qFabs(dK) / dK;
    }
    else
    {
        dKFactor = 1.0;
    }

    /*The angle according to K value*/
    qreal dAngle = qAtan(dK);

    /*Calculate the key point0*/
    if (dKFactor > 0)
    {
        qpKpt0.rx() = qpEndPt.x() - dKFactor * dXdirect * (dL * qCos(dAngle));
        qpKpt0.ry() = qpEndPt.y() - dKFactor * dYdirect * (dL * qSin(dAngle));
    }
    else
    {
        qpKpt0.rx() = qpEndPt.x() + dKFactor * dXdirect * (dL * qCos(dAngle));
        qpKpt0.ry() = qpEndPt.y() - dKFactor * dYdirect * (dL * qSin(dAngle));
    }

    /*The angle according to the K value of vertical line*/
    if (dK >= 99999)
    {
        dVAngle = 90;
    }
    else if (dK > dDelta || dK < -dDelta)
    {
        dVAngle = qAtan(-1 / dK);
    }
    else if (dK > -dDelta && dK < dDelta)
    {
        dVAngle = 0;
    }

    /*Calculate the key point1 and key point2*/
    qpKpt1.rx() = qpKpt0.x() - ((dL/2) * qCos(dVAngle));
    qpKpt1.ry() = qpKpt0.y() - ((dL/2) * qSin(dVAngle));

    qpKpt2.rx() = qpKpt0.x() + ((dL/2) * qCos(dVAngle));
    qpKpt2.ry() = qpKpt0.y() + ((dL/2) * qSin(dVAngle));


    QPointF qpCenter;
    qpCenter.rx() = (qpEndPt.x() + qpKpt0.x()) / 2;
    qpCenter.ry() = (qpEndPt.y() + qpKpt0.y()) / 2;

    /*
    qpKpt3.rx() = qpCenter.x() - ((2*dL/3) * qCos(dVAngle));
    qpKpt3.ry() = qpCenter.y() - ((2*dL/3) * qSin(dVAngle));

    qpKpt4.rx() = qpCenter.x() + ((2*dL/3) * qCos(dVAngle));
    qpKpt4.ry() = qpCenter.y() + ((2*dL/3) * qSin(dVAngle));
    */

    qpKpt3.rx() = qpCenter.x() - (dL * qCos(dVAngle));
    qpKpt3.ry() = qpCenter.y() - (dL * qSin(dVAngle));

    qpKpt4.rx() = qpCenter.x() + (dL * qCos(dVAngle));
    qpKpt4.ry() = qpCenter.y() + (dL * qSin(dVAngle));

    qpKpt5.rx() = (qpCenter.x() + qpKpt0.x()) / 2;
    qpKpt5.ry() = (qpCenter.y() + qpKpt0.y()) / 2;

    stKeyppoints.qpKeyPoint0 = qpKpt0;
    stKeyppoints.qpKeyPoint1 = qpKpt1;
    stKeyppoints.qpKeyPoint2 = qpKpt2;
    stKeyppoints.qpKeyPoint3 = qpKpt3;
    stKeyppoints.qpKeyPoint4 = qpKpt4;
    stKeyppoints.qpKeyPoint5 = qpKpt5;
}

void SamDrawItemBase::qt_graphicsItem_highlightSelected(
    QGraphicsItem *item, QPainter *painter, const QStyleOptionGraphicsItem *option)
{
    const QRectF murect = painter->transform().mapRect(QRectF(0, 0, 1, 1));
    if (qFuzzyIsNull(qMax(murect.width(), murect.height())))
        return;

    const QRectF mbrect = painter->transform().mapRect(item->boundingRect());
    if (qMin(mbrect.width(), mbrect.height()) < qreal(1.0))
        return;

    qreal itemPenWidth;
    switch (item->type()) {
        case QGraphicsEllipseItem::Type:
            itemPenWidth = static_cast<QGraphicsEllipseItem *>(item)->pen().widthF();
            break;
        case QGraphicsPathItem::Type:
            itemPenWidth = static_cast<QGraphicsPathItem *>(item)->pen().widthF();
            break;
        case QGraphicsPolygonItem::Type:
            itemPenWidth = static_cast<QGraphicsPolygonItem *>(item)->pen().widthF();
            break;
        case QGraphicsRectItem::Type:
            itemPenWidth = static_cast<QGraphicsRectItem *>(item)->pen().widthF();
            break;
        case QGraphicsSimpleTextItem::Type:
            itemPenWidth = static_cast<QGraphicsSimpleTextItem *>(item)->pen().widthF();
            break;
        case QGraphicsLineItem::Type:
            itemPenWidth = static_cast<QGraphicsLineItem *>(item)->pen().widthF();
            break;
        default:
            itemPenWidth = 1.0;
    }
    const qreal pad = itemPenWidth / 2;

    const qreal penWidth = 0; // cosmetic pen

    const QColor fgcolor = option->palette.windowText().color();
    const QColor bgcolor( // ensure good contrast against fgcolor
        fgcolor.red()   > 127 ? 0 : 255,
        fgcolor.green() > 127 ? 0 : 255,
        fgcolor.blue()  > 127 ? 0 : 255);

    painter->setPen(QPen(bgcolor, penWidth, Qt::NoPen));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(item->boundingRect().adjusted(pad, pad, -pad, -pad));

    painter->setPen(QPen(option->palette.windowText(), 0, Qt::NoPen));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(item->boundingRect().adjusted(pad, pad, -pad, -pad));
}
/*********************************************************************************
 * SamDrawTackerRect constructor
 ********************************************************************************/
SamDrawTackerRect::SamDrawTackerRect(const QPointF qpPoint, QGraphicsItem *parent)
    :QGraphicsRectItem(QRectF(QPointF(qpPoint.x()-3,qpPoint.y()-3), QSizeF(SAMDRAW_TRACKER_SIZE,SAMDRAW_TRACKER_SIZE)), parent)
{
    this->setBrush(QBrush(Qt::green));
    this->setFlag(QGraphicsItem::ItemIsSelectable, false);
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    this->setZValue(9999);
}

/*********************************************************************************
 * Function: Clone tracker itself
 * Parameters: none
 * Return: tracker type pointer
 ********************************************************************************/
SamDrawTackerRect* SamDrawTackerRect::Clone()
{
    SamDrawTackerRect *pClone = new SamDrawTackerRect(this->scenePos());
    pClone->setBrush(this->brush());
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, false);

    return pClone;
}

/* Class for SamDraw line tracker item*/
SamDrawLineTackerRect::SamDrawLineTackerRect(const QPointF qpPoint, QGraphicsItem *parent)
    :QGraphicsEllipseItem(QRectF(QPointF(qpPoint.x()-3,qpPoint.y()-3), QSizeF(SAMDRAW_TRACKER_SIZE,SAMDRAW_TRACKER_SIZE)),parent)
{
    this->setBrush(QBrush(Qt::darkGreen));
}

/*********************************************************************************
 * SamDrawLineEx constructor
 ********************************************************************************/
SamDrawLineEx::SamDrawLineEx(const QPointF first, const QPointF back, QGraphicsItem *parent)
    :QGraphicsLineItem(QLineF(first,back),parent)
{
    this->setPen(QPen(Qt::DotLine));
}

SamDrawLockRect::SamDrawLockRect(const QPointF qpPoint,QString sPath,QGraphicsItem *parent)
    :QGraphicsPixmapItem(parent)
{
    QPixmap picture = QPixmap(sPath);
    QPixmap newimage = picture.scaled(QSize(15,15));
    this->setPixmap(newimage);
    this->setPos(qpPoint.x(),qpPoint.y());
    this->setFlag(QGraphicsItem::ItemIsSelectable, false);
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    this->setZValue(10000);
}

void SamDrawItemBase::refreshLockRect(QPointF qpPoint, QGraphicsScene *pScene,bool bLock)
{
    if (false == this->getResizable() || !bLockVisiable) return;

    QString sPath = ":/btn/images/lock.png";
    if(bLock)
    {
        if(!m_LockTracker)
        {
            m_LockTracker = new SamDrawLockRect(qpPoint,sPath,0);
            pScene->addItem(m_LockTracker);
        }
        else
        {
            m_LockTracker->setPos(qpPoint.x(),qpPoint.y());
        }
    }
    else
    {
        if(m_LockTracker)
        {
           pScene->removeItem(m_LockTracker);
           m_LockTracker = NULL;
        }
    }
}

void SamDrawItemBase::setLockVisiable(bool bVisiable)
{
    bLockVisiable = bVisiable;
}
