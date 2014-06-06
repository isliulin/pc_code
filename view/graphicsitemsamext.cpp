/************************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2010
 *
 * Description: SDWorkshop draw object base class implemention
 *
 * Functions:
 *
 * Modification Log:
 * Date             Name             Description Of Change
 * 2010-10-22       Bruce nie        Creation.
 ***********************************************************************/
#include <view/graphicsitemsamext.h>
#include <view/samdrawscene.h>
#include <QGraphicsView>

static const unsigned short LINE_HANDLE_COUNT = 2;

/* Class GraphicsRectItemSamExt */
/*********************************************************************************
 * Class GraphicsRectItemSamExt constructor
 ********************************************************************************/
GraphicsRectItemSamExt::GraphicsRectItemSamExt(const QRectF &rect, QGraphicsItem *parent)
    :QGraphicsRectItem(rect, parent)
{
}

GraphicsRectItemSamExt::GraphicsRectItemSamExt()
    :QGraphicsRectItem()
{
}

/* Class GraphicsEllipseItemSamExt */
/*********************************************************************************
 * Class GraphicsEllipseItemSamExt constructor
 ********************************************************************************/
GraphicsEllipseItemSamExt::GraphicsEllipseItemSamExt(const QRectF &rect, QGraphicsItem *parent)
    :QGraphicsEllipseItem(rect, parent)
{
}

GraphicsEllipseItemSamExt::GraphicsEllipseItemSamExt()
    :QGraphicsEllipseItem()
{
}

/* Class GraphicsLineItemSamExt */
/*********************************************************************************
 * Class GraphicsLineItemSamExt constructor
 ********************************************************************************/
GraphicsLineItemSamExt::GraphicsLineItemSamExt(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent)
    :QGraphicsLineItem(x1, y1, x2, y2, parent)

{
}

GraphicsLineItemSamExt::GraphicsLineItemSamExt()
    :QGraphicsLineItem()
{
}

/*********************************************************************************
 * Function: Get line handle count
 * Parameters: none
 * Return: integer handle count
 ********************************************************************************/
int GraphicsLineItemSamExt::getHandleCount() const
{
    return LINE_HANDLE_COUNT;
}

/*********************************************************************************
 * Function: Get line handle point
 * Parameters: handle id
 * Return: QPointF handle point
 ********************************************************************************/
QPointF GraphicsLineItemSamExt::getHandle(int iHandle, QRectF &qrcBondingRect) const
{
    /*Fix the 2 handle to 5 handle for line object*/
    if (iHandle == HANDLE_CENTER_TOP)
    {
        iHandle = HANDLE_RIGHT_BOTTOM;
    }
    return SamDrawItemBase::getHandle(iHandle, qrcBondingRect);
}

/*********************************************************************************
 * Function: Line hit test
 * Parameters: mouse current point, select flag
 * Return: integer polygon handle count
 ********************************************************************************/
int GraphicsLineItemSamExt::hitTest(QPointF qpPoint, QRectF &qrcBondingRect, bool bSelected)
{
    QLineF qlLine = this->line();
    QPointF qpPointFrom = qlLine.p1();
    QPointF qpPointTo   = qlLine.p2();
    QRectF qrcRectFrom, qrcRectTo;
    int iHitedHdl = 0; /* Line only have 1(p1), 2(p2) 2 handles */

    qpPointFrom = this->mapToScene(qpPointFrom);
    qpPointTo = this->mapToScene(qpPointTo);

    /*Set the rect and normalize it*/
    qrcRectFrom.setRect(qpPointFrom.rx()-3, qpPointFrom.ry()-3, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
    qrcRectFrom = qrcRectFrom.normalized();

    qrcRectTo.setRect(qpPointTo.rx()-3, qpPointTo.ry()-3, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
    qrcRectTo = qrcRectTo.normalized();

    if ( (qpPoint.rx() >= qrcRectFrom.left())
        && (qpPoint.rx() <= qrcRectFrom.right())
        && (qpPoint.ry() >= qrcRectFrom.top())
        && (qpPoint.ry() <= qrcRectFrom.bottom()) )
    {
        iHitedHdl = 1;
    }
    else if ( (qpPoint.rx() >= qrcRectTo.left())
        && (qpPoint.rx() <= qrcRectTo.right())
        && (qpPoint.ry() >= qrcRectTo.top())
        && (qpPoint.ry() <= qrcRectTo.bottom()) )
    {
        iHitedHdl = 2;
    }

    /*int iHandle = SamDrawItemBase::hitTest(point, qrcBondingRect, bSelected);
     *return (iHandle == HANDLE_CENTER_TOP) ? HANDLE_RIGHT_BOTTOM : iHandle;
     */
    return iHitedHdl;
}

/***********************************************************************
 *Funtion : Get the handle cursor
 *Return  : Qt::CursorShape cursor.
 *Parameter: handle id.
 **********************************************************************/
QCursor GraphicsLineItemSamExt::getHandleCursor(int iHandle) const
{
    int iHdlId = 0;

    (iHandle == 2) ? iHdlId = 5 : iHdlId = iHandle;

    return SamDrawItemBase::getHandleCursor(iHdlId);
}

/*********************************************************************************
 * Function: Drag the line handle to new position
 * Parameters: draghandle, mouse point, bonding rect.
 * Return: QRectF new rect
 ********************************************************************************/
QRectF GraphicsLineItemSamExt::moveHandleTo(int iDragHandle, QPointF qpLocal, QRectF &qrcBondingRect)
{
    QRectF qrcPosition;
    //QPointF qpTopLeft, qpBottomRight;
    //qrcPosition = this->sceneBoundingRect();
    qrcPosition = qrcBondingRect;
    //qpTopLeft = qrcPosition.topLeft();
    //qpBottomRight = qrcPosition.bottomRight();
    /*Line only have 1,5 handles*/
    switch (iDragHandle)
    {
    case HANDLE_LEFT_TOP:
        qrcPosition.setLeft(qpLocal.rx());
        qrcPosition.setTop(qpLocal.ry());
        //qpTopLeft = qpLocal;
        break;
    case HANDLE_RIGHT_TOP:
        qrcPosition.setRight(qpLocal.rx());
        qrcPosition.setTop(qpLocal.ry());
        //qpTopLeft = qpLocal;
        break;
    case HANDLE_RIGHT_BOTTOM:
        qrcPosition.setRight(qpLocal.rx());
        qrcPosition.setBottom(qpLocal.ry());
        //qpBottomRight = qpLocal;
        break;
    case HANDLE_LEFT_BOTTOM:
        qrcPosition.setLeft(qpLocal.rx());
        qrcPosition.setBottom(qpLocal.ry());
        //qpBottomRight = qpLocal;
        break;
    default:
        return qrcPosition;
    }

    /*qrcPosition = this->mapRectFromScene(qrcPosition);
    DRAG_CROSS_TYPE_E eDragCrossType = NormalizeDragedRect(qrcPosition);
    this->setLine(qrcPosition.topLeft().rx(), qrcPosition.topLeft().ry(), qrcPosition.bottomRight().rx(), qrcPosition.bottomRight().ry());
    */
    //QRectF qrcRect(qpTopLeft, qpBottomRight);
    return qrcPosition;
}

/*********************************************************************************
 * Function: Drag the line trackers
 * Parameters: handle id, mouse point, line new p1,p2
 * Return: none
 ********************************************************************************/
void GraphicsLineItemSamExt::moveLineHandleTo(int iDragHandle, QPointF qpLocal)
{
    QLineF qlLine = this->line();
    QPointF qpP1 = qlLine.p1();
    QPointF qpP2 = qlLine.p2();
    QPointF qpNewPos = this->mapFromScene(qpLocal);

    switch(iDragHandle)
    {
    case 1:
        qpP1 = qpNewPos;
        break;
    case 2:
        qpP2 = qpNewPos;
        break;
    default:
        break;
    }

    this->setLine(qpP1.rx(), qpP1.ry(), qpP2.rx(), qpP2.ry());
    /*qpP1 = this->mapToScene(qpP1);
    qpP2 = this->mapToScene(qpP2);

    switch(iDragHandle)
    {
    case 1:
        qpP1 = qpLocal;
        break;
    case 2:
        qpP2 = qpLocal;
        break;
    default:
        break;
    }
    qpP1 = this->mapFromScene(qpP1);
    qpP2 = this->mapFromScene(qpP2);

    this->setLine(qpP1.rx(), qpP1.ry(), qpP2.rx(), qpP2.ry());
    */
}

/*********************************************************************************
 * Function: Drag the line trackers (overlap the base class function)
 * Parameters: tracker state, scene, bonding rect
 * Return: none
 ********************************************************************************/
void GraphicsLineItemSamExt::drawTracker(eTrackerState state, QGraphicsScene *pScene, QRectF &qrcBondingRect)
{
    QLineF qlLine = this->line();
    QPointF qpFrom = qlLine.p1();
    QPointF qpTo = qlLine.p2();

    qpFrom = this->mapToScene(qpFrom);
    qpTo = this->mapToScene(qpTo);

    m_pvecTrackers.clear();
    if (state == TRK_SELECTED)
    {
        SamDrawTackerRect *pItem = new SamDrawTackerRect(qpFrom);
        pScene->addItem(pItem);
        if (pItem)
        {
            pItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
            //item->setCursor(getHandleCursor(nHandle));
            m_pvecTrackers.push_back(pItem);
        }

        pItem = 0;
        pItem = new SamDrawTackerRect(qpTo);
        pScene->addItem(pItem);
        if (pItem)
        {
            pItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
            //item->setCursor(getHandleCursor(nHandle));
            m_pvecTrackers.push_back(pItem);
        }
    }
}

/*********************************************************************************
 * Function: move the line trackers' position
 * Parameters: draged handle id, new position
 * Return: none
 *******************************************************************************/
void GraphicsLineItemSamExt::moveLineTrackers(const unsigned long &ulHandle, const QPointF &qpPoint)
{
    unsigned long ulIndex = ulHandle - 1;

    if (ulIndex >= (unsigned long)this->m_pvecTrackers.size())
    {
        return;
    }

    SamDrawTackerRect *pTracker = this->m_pvecTrackers[ulIndex];
    if (pTracker)
    {
        QRectF rect(qpPoint.x()-3, qpPoint.y()-3, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
        pTracker->setRect(rect);
    }
}

/*********************************************************************************
 * Function: Refresh the line trackers' position
 * Parameters: none
 * Return: none
 *******************************************************************************/
void GraphicsLineItemSamExt::refreshLineTrackers()
{
    QLineF qlLine = this->line();
    QPointF qpPt1 = qlLine.p1();
    QPointF qpPt2 = qlLine.p2();

    qpPt1 = this->mapToScene(qpPt1);
    qpPt2 = this->mapToScene(qpPt2);

    if (this->m_pvecTrackers.size() < 2)
    {
        return;
    }

    if (this->m_pvecTrackers[0])
    {
        QRectF rect(qpPt1.x()-3, qpPt1.y()-3, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
        this->m_pvecTrackers[0]->setRect(rect);
    }
    if (this->m_pvecTrackers[1])
    {
        QRectF rect(qpPt2.x()-3, qpPt2.y()-3, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
        this->m_pvecTrackers[1]->setRect(rect);
    }
}

/* Class GraphicsPolygonItemExt */
/*********************************************************************************
 * Class GraphicsPolygonItemExt constructor
 ********************************************************************************/
GraphicsPolygonItemSamExt::GraphicsPolygonItemSamExt(const QPolygonF &polygon, QGraphicsItem *parent)
    :QGraphicsPolygonItem(polygon, parent)
{

}

GraphicsPolygonItemSamExt::GraphicsPolygonItemSamExt()
    :QGraphicsPolygonItem()
{
}

/*********************************************************************************
 * Function: Get polygon handle count
 * Parameters: none
 * Return: integer polygon handle count
 ********************************************************************************/
int GraphicsPolygonItemSamExt::getHandleCount() const
{
    QPolygonF qpolygonPoints;
    qpolygonPoints.clear();
    qpolygonPoints = polygon();

    return qpolygonPoints.size();
}

/*********************************************************************************
 * Function: Get polygon handle point
 * Parameters: handle id
 * Return: QPointF point of handle
 ********************************************************************************/
QPointF GraphicsPolygonItemSamExt::getHandle(int iHandle, QRectF &qrcBondingRect) const
{
    QPolygonF qpolygonPoints;
    int iIndex = 0;

    iIndex = iHandle - 1;
    qpolygonPoints.clear();
    qpolygonPoints = this->polygon();
    if (iHandle <= qpolygonPoints.size())
    {
        QPointF qpPoint = qpolygonPoints.at(iIndex);
        /*Map the point to scene*/
        qpPoint = this->mapToScene(qpPoint);
        return qpPoint;
    }

    return QPointF(0, 0);
}

/*********************************************************************************
 * Function: Get polygon handle mouse cursor
 * Parameters: handle id
 * Return: Qt mouse cursor
 ********************************************************************************/
QCursor GraphicsPolygonItemSamExt::getHandleCursor(int iHandle) const
{
    //return Qt::SizeAllCursor;
    QString sMapFile = ":cursor/images/cursor/sizeall.ico";
    QPixmap qmapMap(sMapFile);
    return QCursor(qmapMap);
}

/*********************************************************************************
 * Function: Drag the polygon handle to new position
 * Parameters:
 * Return: DRAG_CROSS_TYPE_BUTT no meaning for polygon
 ********************************************************************************/
QRectF GraphicsPolygonItemSamExt::moveHandleTo(int iDragHandle, QPointF qpLocal, QRectF &qrcBondingRect)
{
    QPolygonF qpolygonPoints;
    QRectF qrcRect = QRectF();
    int iHandleIdx = 0;

    iHandleIdx = iDragHandle - 1;
    if (iDragHandle > this->polygon().size())
    {
        return qrcRect;
    }

    qpolygonPoints = this->polygon();

    qpLocal = this->mapFromScene(qpLocal);
    qpolygonPoints[iHandleIdx] = qpLocal;

    this->setPolygon(qpolygonPoints);

    return qrcRect;
}

/*********************************************************************************
 * Function: move the polygon trackers' position
 * Parameters: draged handle id, new position
 * Return: none
 *******************************************************************************/
void GraphicsPolygonItemSamExt::movePolygonTrackers(const unsigned long &ulHandle, const QPointF &qpPoint)
{
    unsigned long ulIndex = ulHandle - 1;
    if (ulIndex >= (unsigned long)this->m_pvecTrackers.size())
    {
        return;
    }
    SamDrawTackerRect *pTracker = this->m_pvecTrackers[ulIndex];
    if (pTracker)
    {
        QRectF rect(qpPoint.x()-3, qpPoint.y()-3, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
        pTracker->setRect(rect);
    }
}

/*********************************************************************************
 * Function: Draw polygon trackers
 * Parameters: scene pointer
 * Return: none
 *******************************************************************************/
void GraphicsPolygonItemSamExt::drawPolygonTrackers(QGraphicsScene *pScene)
{
    QPolygonF polygon = this->polygon();
    int iSize = polygon.size();

    for (int i = 0; i < iSize; i++)
    {
        QPointF qpPoint = polygon[i];
        SamDrawTackerRect *pItem = new SamDrawTackerRect(qpPoint);
        pScene->addItem(pItem);
        if (pItem)
        {
            this->m_pvecTrackers.push_back(pItem);
        }
    }
}

/*********************************************************************************
 * Function: Refresh the polygon trackers' position
 * Parameters: none
 * Return: none
 *******************************************************************************/
void GraphicsPolygonItemSamExt::refreshPolygonTrackers(QGraphicsScene *pScene)
{
    QPolygonF qpolygonPoints = this->polygon();
    QPointF qpPoint;

    int iSize = qpolygonPoints.size();
    if (iSize <= 0)
    {
        return;
    }

    if (m_pvecTrackers.size() <= 0)
    {
        this->drawPolygonTrackers(pScene);
        return;
    }

    if (m_pvecTrackers.size() < iSize)
    {
        return;
    }

    for (int i = 0; i < iSize; i++)
    {
        qpPoint = qpolygonPoints[i];
        QRectF rect(qpPoint.x()-3, qpPoint.y()-3, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
        rect = this->mapRectToScene(rect);
        if (this->m_pvecTrackers[i])
        {
            this->m_pvecTrackers[i]->setRect(rect);
        }

        QBrush br = this->m_pvecTrackers[i]->brush();
        QPen pen = this->m_pvecTrackers[i]->pen();
        if(this->GetselectFlag() && br.color() != Qt::black)
        {
            pen.setColor(Qt::white);
            br.setColor(Qt::black);
            this->m_pvecTrackers[i]->setPen(pen);
            this->m_pvecTrackers[i]->setBrush(br);
        }
        else if(!this->GetselectFlag() && br.color() != Qt::green)
        {
            pen.setColor(Qt::black);
            br.setColor(Qt::green);
            this->m_pvecTrackers[i]->setPen(pen);
            this->m_pvecTrackers[i]->setBrush(br);
        }
    }
}

/* Class GraphicsPathItemExt */
/*********************************************************************************
 * Class GraphicsPathItemExt constructor
 ********************************************************************************/
GraphicsPathItemExt::GraphicsPathItemExt()
    :QGraphicsPathItem()
{
    //this->setBrush(QBrush(Qt::red));
    //this->setPen(QPen(Qt::red));
    this->m_eLineEndArrowType = LINE_END_STYLE_NONE;
    QPen pen = this->pen();
    pen.setWidth(1);
    this->setPen(pen);
}

GraphicsPathItemExt::GraphicsPathItemExt(const QPainterPath &path, QGraphicsItem *parent)
    :QGraphicsPathItem(path, parent)
{
    //this->setBrush(QBrush(Qt::red));
    //this->setPen(QPen(Qt::red));
    this->m_eLineEndArrowType = LINE_END_STYLE_NONE;
    QPen pen = this->pen();
    pen.setWidth(1);
    this->setPen(pen);
}

/*********************************************************************************
 * Function: Get path handle count
 * Parameters: none
 * Return: path handle count
 ********************************************************************************/
int GraphicsPathItemExt::getHandleCount() const
{
    QPainterPath path = this->path();
    QPolygonF polygon = path.toFillPolygon();
    return polygon.size();
}

/*********************************************************************************
 * Function: Get path handle point by handle id
 * Parameters: handle id & bondingrect(not used)
 * Return: path handle count
 ********************************************************************************/
QPointF GraphicsPathItemExt::getHandle(int iHandle, QRectF &qrcBondingRect) const
{
    QPolygonF qpolygonPoints;
    int iIndex = 0;

    QPainterPath path = this->path();
    qpolygonPoints = path.toFillPolygon();
    iIndex = iHandle - 1;
    if (iHandle <= qpolygonPoints.size())
    {
        QPointF qpPoint = qpolygonPoints.at(iIndex);
        qpPoint = this->mapToScene(qpPoint);
        return qpPoint;
    }

    return QPointF(0, 0);
}

/*********************************************************************************
 * Function: Get mouse cursor
 * Parameters: handle id (not used)
 * Return: mouse cursor
 ********************************************************************************/
QCursor GraphicsPathItemExt::getHandleCursor(int iHandle) const
{
    //return Qt::SizeAllCursor;
    QString sMapFile = ":cursor/images/cursor/sizeall.ico";
    QPixmap qmapMap(sMapFile);
    return QCursor(qmapMap);
}

/*********************************************************************************
 * Function: move the path object by draged handle id
 * Parameters: handle id, bonding rect(not used in this type object)
 * Return: Rect (not used in this type object)
 ********************************************************************************/
QRectF GraphicsPathItemExt::moveHandleTo(int iDragHandle, QPointF qpLocal, QRectF &qrcBondingRect)
{
    //QPolygonF qpolygonPoints;
    QRectF qrcRect = QRectF();
    int iHandleIdx = iDragHandle - 1;

    qpLocal = this->mapFromScene(qpLocal);
    QPainterPath path = this->path();
    path.setElementPositionAt(iHandleIdx, qpLocal.x(), qpLocal.y());
    this->setPath(path);
    /*
    QPainterPath path = this->path();
    qpolygonPoints = path.toFillPolygon();

    iHandleIdx = iDragHandle - 1;
    if (iDragHandle > qpolygonPoints.size())
    {
        return qrcRect;
    }

    qpLocal = this->mapFromScene(qpLocal);
    qpolygonPoints[iHandleIdx] = qpLocal;

    QPainterPath NewPath = QPainterPath();
    NewPath.moveTo(qpolygonPoints[0]);
    for (int i = 1; i < qpolygonPoints.size()-1; i++)
    {
        NewPath.lineTo(qpolygonPoints[i]);
    }

    this->setPath(NewPath);
    */

    return qrcRect;
}

/*********************************************************************************
 * Function: Refresh the path trackers' position
 * Parameters: draged handle id, new position
 * Return: none
 *******************************************************************************/
void GraphicsPathItemExt::movePathTrackers(const unsigned long &ulHandle, const QPointF &qpPoint)
{
    unsigned long ulIndex = ulHandle - 1;
    if (ulIndex >= (unsigned long)this->m_pvecTrackers.size())
    {
        return;
    }
    SamDrawTackerRect *pTracker = this->m_pvecTrackers[ulIndex];
    if (pTracker)
    {
        QRectF rect(qpPoint.x()-3, qpPoint.y()-3, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
        pTracker->setRect(rect);
    }
}

/*********************************************************************************
 * Function: Refresh the path trackers' position
 * Parameters: none
 * Return: none
 *******************************************************************************/
void GraphicsPathItemExt::refreshPathTrackers(QGraphicsScene *pScene)
{
    QPainterPath path = this->path();
    QList<QPolygonF> polygons = path.toSubpathPolygons();
    if (polygons.size() <= 0)
    {
        return;
    }

    int iSize = polygons[0].size();

    QPointF qpPoint;
    int iTrackSize = this->m_pvecTrackers.size();
    if (iTrackSize <= 0)
    {
        this->drawPathTrackers(pScene);
        return;
    }

    //int iSize = polygons[0].size();
    if (iTrackSize != iSize)
    {
        return;
    }

    for (int i = 0; i < iTrackSize; i++)
    {
        qpPoint = polygons[0][i];
        QRectF rect(qpPoint.x()-3, qpPoint.y()-3, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
        rect = this->mapRectToScene(rect);
        this->m_pvecTrackers[i]->setRect(rect);

        QBrush br = this->m_pvecTrackers[i]->brush();
        QPen pen = this->m_pvecTrackers[i]->pen();
        if(this->GetselectFlag() && br.color() != Qt::black)
        {
            pen.setColor(Qt::white);
            br.setColor(Qt::black);
            this->m_pvecTrackers[i]->setPen(pen);
            this->m_pvecTrackers[i]->setBrush(br);
        }
        else if(!this->GetselectFlag() && br.color() != Qt::green)
        {
            pen.setColor(Qt::black);
            br.setColor(Qt::green);
            this->m_pvecTrackers[i]->setPen(pen);
            this->m_pvecTrackers[i]->setBrush(br);
        }
    }
}

/********************************************************************************
 * Function: Set line end-arrow style
 * Parameters: enum end-arow style
 * Return: none
 *******************************************************************************/
void GraphicsPathItemExt::setLineEndArrow(LINE_END_ARROW_STYLE_E eStyle)
{
    this->m_eLineEndArrowType = eStyle;
    this->refreshEndArrow();
}

/********************************************************************************
 * Function: Set line end-arrow style
 * Parameters: enum end-arow style
 * Return: none
 *******************************************************************************/
void GraphicsPathItemExt::refreshEndArrow()
{
    QPainterPath pathArrow;
    QPainterPath path = this->path();
    QList<QPolygonF> polygons = path.toSubpathPolygons();
    if (polygons.size() <= 0)
    {
        return;
    }
    QPainterPath pathOrg;
    pathOrg.addPolygon(polygons[0]);
    qreal dK = 0.0, dB = 0.0, dXdirect = 0.0, dYdirect = 0.0;
    QPointF qpKpt0, qpKpt1, qpKpt2, qpKpt3, qpKpt4, qpKpt5;
    QPolygonF polygonArrow;
    LINE_KEY_POINT_T stKeyPoints;

    int ipolygonSize = polygons.size();
    int iPoints = polygons[0].size();
    if (iPoints < 2)
    {
        return;
    }

    /*Create the end-arrows*/
    QPointF qpP1 = polygons.at(0).at(iPoints - 2);
    QPointF qpP2 = polygons.at(0).at(iPoints - 1);

    memset(&stKeyPoints, 0x00, sizeof(LINE_KEY_POINT_T));
    /*Get the line parameter and the key points*/
    this->calculateLinePara(qpP1, qpP2, dK, dB, dXdirect, dYdirect);
    if (dK == 0 || qFabs(dK) < 0.01)
    {
        qpKpt0.rx() = qpP2.x() - dXdirect * 12;
        qpKpt0.ry() = qpP2.y();

        qpKpt1.rx() = qpKpt0.rx();
        qpKpt1.ry() = qpKpt0.ry() - 6;

        qpKpt2.rx() = qpKpt0.rx();
        qpKpt2.ry() = qpKpt0.ry() + 6;

        qpKpt3.rx() = (qpKpt0.x() + qpP2.x()) / 2;
        qpKpt3.ry() = ((qpKpt0.y() + qpP2.y()) / 2 - 12);

        qpKpt4.rx() = (qpKpt0.x() + qpP2.x()) / 2;
        qpKpt4.ry() = ((qpKpt0.y() + qpP2.y()) / 2 + 12);

        qpKpt5.rx() = (((qpKpt0.x() + qpP2.x()) / 2) + qpKpt0.x()) / 2;
        qpKpt5.ry() = qpP2.y();
    }
    else if (dK >= 99999)
    {
        qpKpt0.rx() = qpP2.x();
        qpKpt0.ry() = qpP2.y() - dYdirect * 12;

        qpKpt1.rx() = qpKpt0.rx() + 6;
        qpKpt1.ry() = qpKpt0.ry();

        qpKpt2.rx() = qpKpt0.rx() - 6;
        qpKpt2.ry() = qpKpt0.ry();

        qpKpt3.rx() = ((qpKpt0.x() + qpP2.x()) / 2) + 12;
        qpKpt3.ry() = (qpKpt0.y() + qpP2.y()) / 2;

        qpKpt4.rx() = ((qpKpt0.x() + qpP2.x()) / 2) - 12;
        qpKpt4.ry() = (qpKpt0.y() + qpP2.y()) / 2;

        qpKpt5.rx() = qpP2.x();
        qpKpt5.ry() = (((qpKpt0.y() + qpP2.y()) / 2) + qpKpt0.y()) / 2;
    }
    else
    {
        this->getEndArrowKeypoints(dK, qpP2, stKeyPoints, dXdirect, dYdirect);
        qpKpt0 = stKeyPoints.qpKeyPoint0;
        qpKpt1 = stKeyPoints.qpKeyPoint1;
        qpKpt2 = stKeyPoints.qpKeyPoint2;
        qpKpt3 = stKeyPoints.qpKeyPoint3;
        qpKpt4 = stKeyPoints.qpKeyPoint4;
        qpKpt5 = stKeyPoints.qpKeyPoint5;
    }

    switch (m_eLineEndArrowType)
    {
    case LINE_END_STYLE_NONE:
        if (ipolygonSize >= 2)
        {
            QPainterPath path;
            path.addPolygon(polygons[0]);
            this->setPath(path);
        }
        return;
    case LINE_END_FILLED_TRIANGLE:
        polygonArrow.clear();
        polygonArrow.push_back(qpP2);
        polygonArrow.push_back(qpKpt1);
        polygonArrow.push_back(qpKpt2);
        polygonArrow.push_back(qpP2);
        pathArrow.addPolygon(polygonArrow);
        break;
    case LINE_END_FOLD_LINE_TRIANGLE:
        pathArrow.moveTo(qpKpt1);
        pathArrow.lineTo(qpP2);
        pathArrow.lineTo(qpKpt2);
        this->setBrush(Qt::transparent);
        break;
    case LINE_END_FILLED_SCISSORS:
        polygonArrow.clear();
        polygonArrow.push_back(qpKpt1);
        polygonArrow.push_back(qpP2);
        polygonArrow.push_back(qpKpt2);
        polygonArrow.push_back(qpKpt5);
        polygonArrow.push_back(qpKpt1);
        pathArrow.addPolygon(polygonArrow);
        break;
    case LINE_END_FILLED_RECT:
        polygonArrow.clear();
        polygonArrow.push_back(qpKpt0);
        polygonArrow.push_back(qpKpt3);
        polygonArrow.push_back(qpP2);
        polygonArrow.push_back(qpKpt4);
        polygonArrow.push_back(qpKpt0);
        pathArrow.addPolygon(polygonArrow);
        break;
    case LINE_END_FILLED_ELLIPSE:
        pathArrow.addEllipse(qpP2, 6, 6);
        break;
    default:
        break;
    }

    //Set the end-arrow
    pathOrg.addPath(pathArrow);
    this->setPath(pathOrg);
}

QPainterPath GraphicsPathItemExt::getEndArrowPath()
{
    QPainterPath pathArrow;
    QPainterPath path = this->path();
    QList<QPolygonF> polygons = path.toSubpathPolygons();
    if (polygons.size() <= 0)
    {
        return pathArrow;
    }
    qreal dK = 0.0, dB = 0.0, dXdirect = 0.0, dYdirect = 0.0;
    QPointF qpKpt0, qpKpt1, qpKpt2, qpKpt3, qpKpt4, qpKpt5;
    QPolygonF polygonArrow;
    LINE_KEY_POINT_T stKeyPoints;

    int ipolygonSize = polygons.size();
    int iPoints = polygons[0].size();
    if (iPoints < 2)
    {
        return pathArrow;
    }

    /*Create the end-arrows*/
    QPointF qpP1 = polygons.at(0).at(iPoints - 2);
    QPointF qpP2 = polygons.at(0).at(iPoints - 1);

    memset(&stKeyPoints, 0x00, sizeof(LINE_KEY_POINT_T));
    /*Get the line parameter and the key points*/
    this->calculateLinePara(qpP1, qpP2, dK, dB, dXdirect, dYdirect);
    if (dK == 0 || qFabs(dK) < 0.01)
    {
        qpKpt0.rx() = qpP2.x() - dXdirect * 12;
        qpKpt0.ry() = qpP2.y();

        qpKpt1.rx() = qpKpt0.rx();
        qpKpt1.ry() = qpKpt0.ry() - 6;

        qpKpt2.rx() = qpKpt0.rx();
        qpKpt2.ry() = qpKpt0.ry() + 6;

        qpKpt3.rx() = (qpKpt0.x() + qpP2.x()) / 2;
        qpKpt3.ry() = ((qpKpt0.y() + qpP2.y()) / 2 - 12);

        qpKpt4.rx() = (qpKpt0.x() + qpP2.x()) / 2;
        qpKpt4.ry() = ((qpKpt0.y() + qpP2.y()) / 2 + 12);

        qpKpt5.rx() = (((qpKpt0.x() + qpP2.x()) / 2) + qpKpt0.x()) / 2;
        qpKpt5.ry() = qpP2.y();
    }
    else if (dK >= 99999)
    {
        qpKpt0.rx() = qpP2.x();
        qpKpt0.ry() = qpP2.y() - dYdirect * 12;

        qpKpt1.rx() = qpKpt0.rx() + 6;
        qpKpt1.ry() = qpKpt0.ry();

        qpKpt2.rx() = qpKpt0.rx() - 6;
        qpKpt2.ry() = qpKpt0.ry();

        qpKpt3.rx() = ((qpKpt0.x() + qpP2.x()) / 2) + 12;
        qpKpt3.ry() = (qpKpt0.y() + qpP2.y()) / 2;

        qpKpt4.rx() = ((qpKpt0.x() + qpP2.x()) / 2) - 12;
        qpKpt4.ry() = (qpKpt0.y() + qpP2.y()) / 2;

        qpKpt5.rx() = qpP2.x();
        qpKpt5.ry() = (((qpKpt0.y() + qpP2.y()) / 2) + qpKpt0.y()) / 2;
    }
    else
    {
        getEndArrowKeypoints(dK, qpP2, stKeyPoints, dXdirect, dYdirect);
        qpKpt0 = stKeyPoints.qpKeyPoint0;
        qpKpt1 = stKeyPoints.qpKeyPoint1;
        qpKpt2 = stKeyPoints.qpKeyPoint2;
        qpKpt3 = stKeyPoints.qpKeyPoint3;
        qpKpt4 = stKeyPoints.qpKeyPoint4;
        qpKpt5 = stKeyPoints.qpKeyPoint5;
    }

    switch (m_eLineEndArrowType)
    {
    case LINE_END_STYLE_NONE:

        break;
    case LINE_END_FILLED_TRIANGLE:
        polygonArrow.clear();
        polygonArrow.push_back(qpP2);
        polygonArrow.push_back(qpKpt1);
        polygonArrow.push_back(qpKpt2);
        polygonArrow.push_back(qpP2);
        pathArrow.addPolygon(polygonArrow);
        break;
    case LINE_END_FOLD_LINE_TRIANGLE:
        pathArrow.moveTo(qpKpt1);
        pathArrow.lineTo(qpP2);
        pathArrow.lineTo(qpKpt2);
        pathArrow.lineTo(qpP2);
        this->setBrush(Qt::transparent);
        break;
    case LINE_END_FILLED_SCISSORS:
        polygonArrow.clear();
        polygonArrow.push_back(qpKpt1);
        polygonArrow.push_back(qpP2);
        polygonArrow.push_back(qpKpt2);
        polygonArrow.push_back(qpKpt5);
        polygonArrow.push_back(qpKpt1);
        pathArrow.addPolygon(polygonArrow);
        break;
    case LINE_END_FILLED_RECT:
        polygonArrow.clear();
        polygonArrow.push_back(qpKpt0);
        polygonArrow.push_back(qpKpt3);
        polygonArrow.push_back(qpP2);
        polygonArrow.push_back(qpKpt4);
        polygonArrow.push_back(qpKpt0);
        pathArrow.addPolygon(polygonArrow);
        break;
    case LINE_END_FILLED_ELLIPSE:
        pathArrow.addEllipse(qpP2, 6, 6);
        break;
    default:
        break;
    }
    return pathArrow;
}
/********************************************************************************
 * Function: Create path trackers if trackers array is empty
 * Parameters: scene
 * Return: none
 *******************************************************************************/
void GraphicsPathItemExt::drawPathTrackers(QGraphicsScene *pScene)
{
    QPainterPath path = this->path();
    QList<QPolygonF> polygons = path.toSubpathPolygons();
    int iSize = polygons.size();
    if (iSize <= 0)
    {
        return;
    }

    iSize = polygons[0].size();
    for (int j = 0; j < iSize; j++)
    {
        QPointF qpPoint = polygons[0][j];
        SamDrawTackerRect *pItem = new SamDrawTackerRect(qpPoint);
        pScene->addItem(pItem);
        if (pItem)
        {
            this->m_pvecTrackers.push_back(pItem);
        }
    }
}

/* Class GraphicsItemGroupSamExt */
/*********************************************************************************
 * Class GraphicsItemGroupSamExt constructor
 ********************************************************************************/
GraphicsItemGroupSamExt::GraphicsItemGroupSamExt()
    :QGraphicsItemGroup()
{
}

GraphicsItemGroupSamExt::GraphicsItemGroupSamExt(QGraphicsItem *parent)
    :QGraphicsItemGroup(parent)
{
}

/* Class GraphicsSimpleTextItemSamExt */
/*********************************************************************************
 * Class GraphicsSimpleTextItemSamExt constructor
 ********************************************************************************/
//GraphicsSimpleTextItemSamExt::GraphicsSimpleTextItemSamExt(QGraphicsItem *parent)
//    :QGraphicsSimpleTextItem(parent)
//{
//}
//GraphicsSimpleTextItemSamExt::GraphicsSimpleTextItemSamExt(const QRectF &rect, QString sText)
//    :QGraphicsSimpleTextItem(rect, sText)
//{

//}

GraphicsSimpleTextItemSamExt::GraphicsSimpleTextItemSamExt(QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
}
/*********************************************************************************
 * Class GraphicsMultiPathItem for SamDraw multi path item(line-circle)
 * Design by tanghaiguo at 2010.11.8
 *
 ********************************************************************************/
GraphicsMultiPathItem::GraphicsMultiPathItem()
{
    m_lineItem1 = NULL;
    m_lineItem2 = NULL;
    m_trackerItem = NULL;
    m_handPolygonList.clear();
    m_eLineEndArrowType = LINE_END_STYLE_NONE;
    m_pathIndex = -1;
    m_subPathIndex = -1;
}

GraphicsMultiPathItem::GraphicsMultiPathItem(const QPainterPath &path, QGraphicsItem *parent)
    :QGraphicsPathItem(path,parent)
{
    m_lineItem1 = NULL;
    m_lineItem2 = NULL;
    m_trackerItem = NULL;
    m_handPolygonList.clear();
    m_eLineEndArrowType = LINE_END_STYLE_NONE;
    m_pathIndex = -1;
    m_subPathIndex = -1;
}


/*************************************************************************
 *
 *this function get subpath circle control point
 *
 *************************************************************************/
QPointF GraphicsMultiPathItem::getMidPoint(QPointF first, QPointF back,QPainterPath subpath) const
{
    QPointF mid;
    if(first.isNull() || back.isNull() || subpath.isEmpty())  return mid;

    qreal kfirst = subpath.slopeAtPercent(0);
    qreal kback = subpath.slopeAtPercent(1);
    qreal midx = (back.y()-first.y()+kfirst*first.x()-kback*back.x())/(kfirst-kback);
    qreal midy = kfirst*midx + (first.y()-kfirst*first.x());
    mid.setX(midx);
    mid.setY(midy);
    return mid;
}
/*************************************************************************
 *
 *this function get subpath numble
 *
 *************************************************************************/
int GraphicsMultiPathItem::getSubPathNum(QPointF point)
{
    QPainterPath fullPath = this->path();
    QList<QPolygonF> iPolygonList = fullPath.toSubpathPolygons();
    if(iPolygonList.isEmpty())
        return 0;
    int i = 0;
    int iSize = iPolygonList.size();
    if (this->m_eLineEndArrowType != LINE_END_STYLE_NONE)
    {
        iSize--;
    }
    for(i = 0; i < iSize; i++)
    {
        QPolygonF subPathPoint = iPolygonList.at(i);
        subPathPoint = this->mapToScene(subPathPoint); //change to scece point
        int subPathPointSize = subPathPoint.size();
        if(subPathPointSize > 2)
        {
            QPainterPath subPath = QPainterPath();
            subPath.addPolygon(subPathPoint);
            QPointF mid = getMidPoint(subPathPoint.first(),subPathPoint.back(),subPath);

            if ( ((mid.x()-3 < point.x()) && (point.x() < mid.x() + 3))
                && ((mid.y()-3< point.y())&& (point.y()<mid.y()+3)))
            {
                return (i+1);
            }
        }
        for(int j = 0; j < subPathPointSize; j++)
        {
            QPointF pathpoint = subPathPoint.at(j);
            if ( ((pathpoint.x()-3 < point.x()) && (point.x() < pathpoint.x() + 3))
                && ((pathpoint.y()-3 < point.y())&& (point.y() < pathpoint.y() +3)))
                {
                return (i+1);
            }
        }

  /*      else if(subPathPoint.size()==2)
        {
            QPointF linePointBegin = subPathPoint.first();
            QPointF linePointEnd = subPathPoint.back();
            qreal k = (linePointEnd.y()-linePointBegin.y())/(linePointEnd.x()-linePointBegin.x());
            qreal b = linePointBegin.y()-linePointBegin.x()*k;
            qreal y = point.x()*k + b;
            if(linePointBegin.x()<linePointEnd.x())
            {
                if ((linePointBegin.x()) < point.x() && point.x()< (linePointEnd.x())
                    && (y-0.5) < point.y() && point.y()< (y+0.5))
                    {
                    return (i+1);
                }
            }
            else
            {
                if ((linePointEnd.x()) < point.x() && point.x()< (linePointBegin.x())
                    && (y-0.5) < point.y() && point.y()< (y+0.5))
                    {
                    return (i+1);
                }
            }
        }*/
    }
    return 0;
}

/*************************************************************************
 *
 *this function get subpath pos point :first(return 0),mid(return 1) or back(return 2) point
 *
 *************************************************************************/
int GraphicsMultiPathItem::getSubPathPos(QPointF point)
{
    QList<QPolygonF> iPolygonList = getHandleList();
    if(iPolygonList.isEmpty())  return -1;

    int subPathNum = getSubPathNum(point) -1;
    if(subPathNum < 0) return -1;

    QPolygonF subPathPoints = iPolygonList.at(subPathNum);
    subPathPoints = this->mapToScene(subPathPoints);    //change to scece point
    for(int j=0; j < subPathPoints.size(); j++)
    {
        QPointF pathpoint = subPathPoints.at(j);
        if ( ((pathpoint.x()-3 < point.x()) && (point.x() < pathpoint.x() + 3))
            && ((pathpoint.y()-3 < point.y())&& (point.y()<pathpoint.y()+3)))
        {
            return j;
        }
    }
    return -1;
}

/*************************************************************************
 *
 *this function add a Item to this scane
 *
 *************************************************************************/
void GraphicsMultiPathItem::addItemtoscane(QGraphicsItem *pItem, QGraphicsScene *pScene)
{
    if(!pItem || !pScene)
        return ;

    SamDrawScene *pSceneTmp = dynamic_cast<SamDrawScene *> (pScene);
    if(!pSceneTmp) return ;

    pSceneTmp->addItem(pItem);
    pItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
    //item->setCursor(getHandleCursor(nHandle));
}

/*************************************************************************
 *this function draw line and Tracker
 *the subPathNum from 1 to iPolygonList.size()
 *
 *************************************************************************/
void GraphicsMultiPathItem::removeLineTracker(QGraphicsScene *pScene)
{
    if(!pScene) return ;

    if(m_lineItem1)
    {
        pScene->removeItem(m_lineItem1);
        delete m_lineItem1;
        m_lineItem1 = NULL;
    }
    if(m_lineItem2)
    {
        pScene->removeItem(m_lineItem2);
        delete m_lineItem2;
        m_lineItem2 = NULL;
    }
    if(m_trackerItem)
    {
        pScene->removeItem(m_trackerItem);
        delete m_trackerItem;
        m_trackerItem = NULL;
    }
}

/*************************************************************************
 *this function draw line and Tracker
 *the subPathNum from 1 to iPolygonList.size()
 *
 *************************************************************************/
void GraphicsMultiPathItem::DrawLineTracker(int subPathNum, QGraphicsScene *pScene)
{
    if(!pScene) return ;

    if(subPathNum < 1)  return ;

    QList<QPolygonF> iPolygonList = getHandleList();
    if(iPolygonList.isEmpty()) return ;

    if(subPathNum > iPolygonList.size()) return ;

    QPolygonF subPathPoint = iPolygonList.at(subPathNum -1);
    if(subPathPoint.size() < 3) return;
    if(m_lineItem1)
    {
        pScene->removeItem(m_lineItem1);
        delete m_lineItem1;
        m_lineItem1 = NULL;
    }
    if(m_lineItem2)
    {
        pScene->removeItem(m_lineItem2);
        delete m_lineItem2;
        m_lineItem2 = NULL;
    }
    if(m_trackerItem)
    {
        pScene->removeItem(m_trackerItem);
        delete m_trackerItem;
        m_trackerItem = NULL;
    }

    /*refreash line 1 and line 2 and hand tracker */
    subPathPoint = this->mapToScene(subPathPoint);     //change to scece point

    m_lineItem1 = new SamDrawLineEx(subPathPoint.at(0), subPathPoint.at(1));
    addItemtoscane(m_lineItem1,pScene);

    m_lineItem2 = new SamDrawLineEx(subPathPoint.at(1), subPathPoint.at(2));
    addItemtoscane(m_lineItem2,pScene);

    m_trackerItem = new SamDrawLineTackerRect(subPathPoint.at(1));
    addItemtoscane(m_trackerItem,pScene);
}

/*************************************************************************
 *
 *the function get the fullPath all control point
 *
 *************************************************************************/
QList<QPolygonF> GraphicsMultiPathItem::getHandleList() const
{
    QPolygonF ctlSubPathPoint;
    QList<QPolygonF> ctlPathPoint;
    ctlSubPathPoint.clear();
    ctlPathPoint.clear();
    QPainterPath path = this->path();
    QList<QPolygonF> polygonList = path.toSubpathPolygons();
    if(polygonList.isEmpty())
        return ctlPathPoint;
    int iSize = polygonList.size();
    if (m_eLineEndArrowType != LINE_END_STYLE_NONE && m_eLineEndArrowType != LINE_END_ARROW_STYLE_BUTT)
    {
        iSize--;
    }

    for (int i = 0; i < iSize; i++)
    {
        QPolygonF subPathList = polygonList.at(i);
        int subPathSize = subPathList.size();
        QPointF first = subPathList.first();
        QPointF back  = subPathList.back();
        if(subPathSize < 2)
        {
            continue ;
        }
        else if(subPathSize == 2)
        {
            ctlSubPathPoint.clear();
            ctlSubPathPoint.push_back(first);
            ctlSubPathPoint.push_back(back);
            ctlPathPoint.push_back(ctlSubPathPoint);
        }
        else
        {
            QPainterPath subpath;
            subpath.addPolygon(subPathList);
            QPointF mid;
            mid = getMidPoint(first,back,subpath);
            if(!mid.isNull())
            {
                ctlSubPathPoint.clear();
                ctlSubPathPoint.push_back(first);
                ctlSubPathPoint.push_back(mid);
                ctlSubPathPoint.push_back(back);
                ctlPathPoint.push_back(ctlSubPathPoint);
            }
        }
    }
    return ctlPathPoint;
}

/*************************************************************************
 *
 *the function draw Tracker at path control point
 *
 *************************************************************************/
void GraphicsMultiPathItem::drawTracker(eTrackerState eState, QGraphicsScene *pScene)
{
    if (!pScene)
    {
        return;
    }

    switch (eState)
    {
    case TRK_NORMAL:
        break;
    case TRK_SELECTED:
    case TRK_ACTIVE:
        {
            QList<QPolygonF> iPolygonList;
            iPolygonList.clear();
            iPolygonList = getHandleList();
            if(iPolygonList.isEmpty())
                return ;
            int iPolygonListSize = iPolygonList.size();
            SamDrawTackerRect *pItem;
            for(int i = 0;i<iPolygonListSize; i++)
            {
                QPolygonF subPathPoints = iPolygonList.at(i);
                subPathPoints = this->mapToScene(subPathPoints);
                if(i==0)
                {
                    pItem = new SamDrawTackerRect(subPathPoints.first());
                    addItemtoscane(pItem,pScene);
                    this->m_pvecTrackers.push_back(pItem);
                    pItem = new SamDrawTackerRect(subPathPoints.back());
                    addItemtoscane(pItem,pScene);
                    this->m_pvecTrackers.push_back(pItem);
                }
                else
                {
                    pItem = new SamDrawTackerRect(subPathPoints.back());
                    addItemtoscane(pItem,pScene);
                    this->m_pvecTrackers.push_back(pItem);
                }
            }
        }
        break;
    default:
        break;
    }
}

/*************************************************************************
 *
 *the function Move one control point to another pos and the path chang
 *
 *************************************************************************/
void GraphicsMultiPathItem::moveHandleToEx(int subPathNum, QPointF qpLocal, QGraphicsScene *pScene, int pathPos)
{
 //   QList<QPolygonF> iPolygonList;
 //   iPolygonList.clear();

    /*if not have hand point list ,so get it*/
    if(m_handPolygonList.isEmpty())
        m_handPolygonList = getHandleList();

    if(m_handPolygonList.isEmpty()) return ;

    int iPolygonListSize = m_handPolygonList.size();
    subPathNum = subPathNum -1;
    if(subPathNum < 0 || subPathNum >= iPolygonListSize) return ;

    /*draw line and Tacker*/
    QPolygonF subPathPoint = m_handPolygonList.at(subPathNum);
    subPathPoint = this->mapToScene(subPathPoint);

    /*draw line and Tacker*/
    QPointF ipLocal = this->mapFromScene(qpLocal);

    if(m_lineItem1)
    {
        pScene->removeItem(m_lineItem1);
        delete m_lineItem1;
        m_lineItem1 = NULL;
    }
    if(m_lineItem2)
    {
        pScene->removeItem(m_lineItem2);
        delete m_lineItem2;
        m_lineItem2 = NULL;
    }
    if(m_trackerItem)
    {
        pScene->removeItem(m_trackerItem);
        delete m_trackerItem;
        m_trackerItem = NULL;
    }

    if(subPathPoint.size() >2)
    {
        switch(pathPos)
        {
        case 0:
            m_lineItem1 = new SamDrawLineEx(qpLocal,subPathPoint.at(1));
            addItemtoscane(m_lineItem1,pScene);

            m_lineItem2 = new SamDrawLineEx(subPathPoint.back(),subPathPoint.at(1));
            addItemtoscane(m_lineItem2,pScene);

            m_trackerItem = new SamDrawLineTackerRect(subPathPoint.at(1));
            addItemtoscane(m_trackerItem,pScene);
            break;
        case 1:
            m_lineItem1 = new SamDrawLineEx(subPathPoint.first(),qpLocal);
            addItemtoscane(m_lineItem1,pScene);

            m_lineItem2 = new SamDrawLineEx(subPathPoint.back(),qpLocal);
            addItemtoscane(m_lineItem2,pScene);

            m_trackerItem = new SamDrawLineTackerRect(qpLocal);
            addItemtoscane(m_trackerItem,pScene);
            break;
        case 2:
            m_lineItem1 = new SamDrawLineEx(subPathPoint.first(),subPathPoint.at(1));
            addItemtoscane(m_lineItem1,pScene);

            m_lineItem2 = new SamDrawLineEx(subPathPoint.at(1),qpLocal);
            addItemtoscane(m_lineItem2,pScene);

            m_trackerItem = new SamDrawLineTackerRect(subPathPoint.at(1));
            addItemtoscane(m_trackerItem,pScene);
            break;
        default:
            break;
        }
    }
    //end draw line and Tacker

    QPainterPath allPath ;
    switch(pathPos)
    {
    case 0:
        {
            if(subPathNum > 0)
            {
                m_handPolygonList[subPathNum -1][2] = ipLocal;
            }
            m_handPolygonList[subPathNum][0] = ipLocal;
            break;
        }
    case 1:
        {
            m_handPolygonList[subPathNum][1] = ipLocal;
            if(subPathPoint.size() == 2)
            {
                if(subPathNum +1 < iPolygonListSize)
                {
                    m_handPolygonList[subPathNum+1][0] = ipLocal;
                }
            }
            break;
        }
    case 2:
        {
            m_handPolygonList[subPathNum][2] = ipLocal;
            if(subPathNum+1 < iPolygonListSize)
            {
                m_handPolygonList[subPathNum+1][0] = ipLocal;
            }
            break;
        }
    default:
        break;
    }
    for(int i = 0; i < iPolygonListSize; i++)
    {
        if(m_handPolygonList.at(i).size() == 2)
        {
            QPainterPath subPath = QPainterPath();
            subPath.moveTo(m_handPolygonList.at(i).first());
            subPath.lineTo(m_handPolygonList.at(i).back());
            allPath.addPath(subPath);
        }
        else if(m_handPolygonList.at(i).size() == 3)
        {
            QPainterPath subPath = QPainterPath();
            subPath.moveTo(m_handPolygonList.at(i).first());
            subPath.cubicTo(m_handPolygonList.at(i).first(),m_handPolygonList.at(i).at(1),m_handPolygonList.at(i).back());
            allPath.addPath(subPath);
        }
    }

    if (m_eLineEndArrowType != LINE_END_STYLE_NONE && m_eLineEndArrowType != LINE_END_ARROW_STYLE_BUTT)
    {
        QPainterPath path = this->path();
        QList<QPolygonF> polygonList = path.toSubpathPolygons();
        QPainterPath subPath;
        if(!polygonList.isEmpty())
        {
           subPath.addPolygon(polygonList.back());
           allPath.addPath(subPath);
        }
    }
    this->setPath(allPath);
    refreshEndArrow();
}

/*************************************************************************
 *
 *the function Get the mouse cursor shape when you move your mouse
 *
 *************************************************************************/
QCursor GraphicsMultiPathItem::getHandleCursor(QPointF point)
{
    QList<QPolygonF> iPolygonList;
    QString sMapFile = ":cursor/images/cursor/sizeall.ico";
    QPixmap qmapMap(sMapFile);

    iPolygonList.clear();
    iPolygonList = getHandleList();
    if(iPolygonList.isEmpty())
        //return Qt::ArrowCursor;
        return QCursor(Qt::ArrowCursor);

    int subNum = getSubPathNum(point) -1;
    if(subNum < 0)
        //return Qt::ArrowCursor;
        return QCursor(Qt::ArrowCursor);

    QPolygonF subPathPoint = iPolygonList.at(subNum);
    subPathPoint = this->mapToScene(subPathPoint);

    if(subNum > iPolygonList.size() -1)
        //return Qt::ArrowCursor;
        return QCursor(Qt::ArrowCursor);

    if(subPathPoint.isEmpty())
        //return Qt::ArrowCursor;
        return QCursor(Qt::ArrowCursor);

    int j = 0;
    for(j = 0; j<subPathPoint.size();j++)
    {
        QPointF pathpoint = subPathPoint.at(j);
        if ( ((pathpoint.x()-3 < point.x()) && (point.x() < pathpoint.x() + 3))
            && ((pathpoint.y()-3< point.y())&& (point.y()<pathpoint.y()+3)))
        {
            //return Qt::PointingHandCursor;
            return QCursor(qmapMap);
        }
    }

    if(j == subPathPoint.size())
        //return Qt::SizeAllCursor;
        return QCursor(Qt::SizeAllCursor);

    //return Qt::ArrowCursor;
    return QCursor(Qt::ArrowCursor);
}

/*********************************************************************************
 * Function: Move the arc trackers' position
 * Parameters: draged handle id, new position
 * Return: none
 *******************************************************************************/
void GraphicsMultiPathItem::moveLineCircleTrackers(const unsigned long &ulHandle, const QPointF &qpPoint)
{
    unsigned long ulIndex = ulHandle;
    if (ulIndex >= (unsigned long)this->m_pvecTrackers.size())
    {
        return;
    }
    SamDrawTackerRect *pTracker = this->m_pvecTrackers[ulIndex];
    if (pTracker)
    {
        QRectF rect(qpPoint.x()-3, qpPoint.y()-3, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
        pTracker->setRect(rect);
    }
}

/*********************************************************************************
 * Function: Refresh the arc trackers' position
 * Parameters: draged handle id, new position
 * Return: none
 *******************************************************************************/
void GraphicsMultiPathItem::refreshLineCircleTrackers(QGraphicsScene *pScene)
{
    QList<QPolygonF> list = this->getHandleList();
    QVector<QPointF> points;

    points.clear();
    if (list.isEmpty())
    {
        return;
    }

    for(int i = 0; i < list.size(); i++)
    {
        points.push_back(list.at(i).first());
    }
    points.push_back(list.at((list.size()-1)).back());

    if (this->m_pvecTrackers.size() != points.size())
    {
        if (this->m_pvecTrackers.size() <= 0)
        {
            this->drawTracker(TRK_SELECTED, pScene);
            return;
        }
    }

    QPointF qpPoint;
    int size = m_pvecTrackers.size();
    if(size > points.size())
    {
        size = points.size();
    }
    //for (int j = 0; j < points.size(); j++)
    for (int j = 0; j < size; j++)
    {
        qpPoint = points[j];
        QRectF rect(qpPoint.x()-3, qpPoint.y()-3, SAMDRAW_TRACKER_SIZE, SAMDRAW_TRACKER_SIZE);
        rect = this->mapRectToScene(rect);
        if (this->m_pvecTrackers[j])
        {
            this->m_pvecTrackers[j]->setRect(rect);
            QBrush br = m_pvecTrackers[j]->brush();
            QPen pen  = m_pvecTrackers[j]->pen();
            if(this->GetselectFlag() && br.color() != Qt::black)
            {
                br.setColor(Qt::black);
                pen.setColor(Qt::white);
                m_pvecTrackers[j]->setPen(pen);
                m_pvecTrackers[j]->setBrush(br);
            }
            else if(!this->GetselectFlag() && br.color() != Qt::green)
            {
                br.setColor(Qt::green);
                pen.setColor(Qt::black);
                m_pvecTrackers[j]->setPen(pen);
                m_pvecTrackers[j]->setBrush(br);
            }
        }
    }
}

/********************************************************************************
 * Function: Set line end-arrow style
 * Parameters: enum end-arow style
 * Return: none
 *******************************************************************************/
void GraphicsMultiPathItem::setLineEndArrow(LINE_END_ARROW_STYLE_E eStyle)
{
    this->refreshEndArrow(eStyle);
    this->m_eLineEndArrowType = eStyle;
}

/********************************************************************************
 * Function: Set line end-arrow style
 * Parameters: enum end-arow style
 * Return: none
 *******************************************************************************/
void GraphicsMultiPathItem::refreshEndArrow(LINE_END_ARROW_STYLE_E eStyle)
{
    QPainterPath pathOrg;
    QPainterPath pathArrow;
    QPainterPath path = this->path();
    QList<QPolygonF> polygons = path.toSubpathPolygons();
    if(polygons.isEmpty()) return;

    switch (m_eLineEndArrowType)
    {
    case LINE_END_STYLE_NONE:
        break;
    case LINE_END_FILLED_TRIANGLE:
    case LINE_END_FOLD_LINE_TRIANGLE:
    case LINE_END_FILLED_SCISSORS:
    case LINE_END_FILLED_RECT:
    case LINE_END_FILLED_ELLIPSE:
        {
            polygons.removeLast();
            break;
        }
    default:
            break;
    }

    if (polygons.isEmpty()) return ;

    int iSize = polygons.size();
    for (int i = 0; i < iSize; i++)
    {
        QPainterPath subpath;
        subpath.addPolygon(polygons[i]);
        pathOrg.addPath(subpath);
    }

    QPolygonF polygon = polygons.back();
    QPainterPath pathTail;
    pathTail.addPolygon(polygon);
    QPointF qpMid = this->getMidPoint(polygon.first(), polygon.back(), pathTail);

    qreal dK = 0.0, dB = 0.0, dXdirect = 0.0, dYdirect = 0.0;
    QPointF qpKpt0, qpKpt1, qpKpt2, qpKpt3, qpKpt4, qpKpt5;
    QPolygonF polygonArrow;
    LINE_KEY_POINT_T stKeyPoints;

    /*Create the end-arrows*/
    QPointF qpP1 = qpMid;
    QPointF qpP2 = polygon.back();

    memset(&stKeyPoints, 0x00, sizeof(LINE_KEY_POINT_T));
    /*Get the line parameter and the key points*/
    this->calculateLinePara(qpP1, qpP2, dK, dB, dXdirect, dYdirect);
    if (dK == 0 || qFabs(dK) < 0.01)
    {
        qpKpt0.rx() = qpP2.x() - dXdirect * 12;
        qpKpt0.ry() = qpP2.y();

        qpKpt1.rx() = qpKpt0.rx();
        qpKpt1.ry() = qpKpt0.ry() - 6;

        qpKpt2.rx() = qpKpt0.rx();
        qpKpt2.ry() = qpKpt0.ry() + 6;

        qpKpt3.rx() = (qpKpt0.x() + qpP2.x()) / 2;
        qpKpt3.ry() = ((qpKpt0.y() + qpP2.y()) / 2 - 12);

        qpKpt4.rx() = (qpKpt0.x() + qpP2.x()) / 2;
        qpKpt4.ry() = ((qpKpt0.y() + qpP2.y()) / 2 + 12);

        qpKpt5.rx() = (((qpKpt0.x() + qpP2.x()) / 2) + qpKpt0.x()) / 2;
        qpKpt5.ry() = qpP2.y();
    }
    else if (dK >= 99999)
    {
        qpKpt0.rx() = qpP2.x();
        qpKpt0.ry() = qpP2.y() - dYdirect * 12;

        qpKpt1.rx() = qpKpt0.rx() + 6;
        qpKpt1.ry() = qpKpt0.ry();

        qpKpt2.rx() = qpKpt0.rx() - 6;
        qpKpt2.ry() = qpKpt0.ry();

        qpKpt3.rx() = ((qpKpt0.x() + qpP2.x()) / 2) + 12;
        qpKpt3.ry() = (qpKpt0.y() + qpP2.y()) / 2;

        qpKpt4.rx() = ((qpKpt0.x() + qpP2.x()) / 2) - 12;
        qpKpt4.ry() = (qpKpt0.y() + qpP2.y()) / 2;

        qpKpt5.rx() = qpP2.x();
        qpKpt5.ry() = (((qpKpt0.y() + qpP2.y()) / 2) + qpKpt0.y()) / 2;
    }
    else
    {
        this->getEndArrowKeypoints(dK, qpP2, stKeyPoints, dXdirect, dYdirect);
        qpKpt0 = stKeyPoints.qpKeyPoint0;
        qpKpt1 = stKeyPoints.qpKeyPoint1;
        qpKpt2 = stKeyPoints.qpKeyPoint2;
        qpKpt3 = stKeyPoints.qpKeyPoint3;
        qpKpt4 = stKeyPoints.qpKeyPoint4;
        qpKpt5 = stKeyPoints.qpKeyPoint5;
    }

    if(eStyle == LINE_END_ARROW_STYLE_BUTT)
    {
        eStyle = m_eLineEndArrowType;
    }
    switch(eStyle)
    {
    case LINE_END_STYLE_NONE:
        this->setPath(pathOrg);
        return;
    case LINE_END_FILLED_TRIANGLE:
        polygonArrow.clear();
        polygonArrow.push_back(qpP2);
        polygonArrow.push_back(qpKpt1);
        polygonArrow.push_back(qpKpt2);
        polygonArrow.push_back(qpP2);
        pathArrow.addPolygon(polygonArrow);
        break;
    case LINE_END_FOLD_LINE_TRIANGLE:
        pathArrow.moveTo(qpKpt1);
        pathArrow.lineTo(qpP2);
        pathArrow.lineTo(qpKpt2);
        this->setBrush(Qt::transparent);
        break;
    case LINE_END_FILLED_SCISSORS:
        polygonArrow.clear();
        polygonArrow.push_back(qpKpt1);
        polygonArrow.push_back(qpP2);
        polygonArrow.push_back(qpKpt2);
        polygonArrow.push_back(qpKpt5);
        polygonArrow.push_back(qpKpt1);
        pathArrow.addPolygon(polygonArrow);
        break;
    case LINE_END_FILLED_RECT:
        polygonArrow.clear();
        polygonArrow.push_back(qpKpt0);
        polygonArrow.push_back(qpKpt3);
        polygonArrow.push_back(qpP2);
        polygonArrow.push_back(qpKpt4);
        polygonArrow.push_back(qpKpt0);
        pathArrow.addPolygon(polygonArrow);
        break;
    case LINE_END_FILLED_ELLIPSE:
        pathArrow.addEllipse(qpP2, 6, 6);
        break;
    default:
        {
            break;
        }
    }

    polygons = pathOrg.toSubpathPolygons();
    //Set the end-arrow
    pathOrg.addPath(pathArrow);
    polygons = pathOrg.toSubpathPolygons();
    this->setPath(pathOrg);
}

/********************************************************************************
 * Function: mouse press item
 * Parameters: item presss pos
 * Return: none
 *******************************************************************************/
int GraphicsMultiPathItem::itemSelectMousePress(QPointF pos)
{
    m_handPolygonList.clear();
    m_pathIndex = getSubPathNum(pos);
    if (m_pathIndex == 1)
    {
        QRectF qrcRect = m_pvecTrackers[0]->sceneBoundingRect();
        QPointF qpPos = qrcRect.topLeft();
        if ((pos.x() >= qpPos.x())
            && (pos.x() <= (qpPos.x()+SAMDRAW_TRACKER_SIZE))
            && (pos.y() >= qpPos.y())
            && (pos.y() <= (qpPos.y()+SAMDRAW_TRACKER_SIZE)))
        {
            m_pathIndex = 0;
        }
    }
    if(m_pathIndex < 1) return 0;

    m_subPathIndex = getSubPathPos(pos);
    return m_pathIndex;
}

/********************************************************************************
 * Function: mouse move to item
 * Parameters: pScene , pos
 * Return: none
 *******************************************************************************/
void GraphicsMultiPathItem::itemSelectMouseMove(QGraphicsScene *pScene, QPointF pos)
{
    QGraphicsView *pView = pScene->views().first();
    if(pView)
    {
        if(m_pathIndex > 0)
        {
            QString sMapFile = ":cursor/images/cursor/sizeall.ico";
            QPixmap qmapMap(sMapFile);
            pView->setCursor(QCursor(qmapMap));
        }
        else
        {
            QCursor handCursor = getHandleCursor(pos);
            pView->setCursor(handCursor);
        }
    }

    if(m_pathIndex > 0 && m_subPathIndex < 3 && m_subPathIndex > 0)
    {
        moveHandleToEx(m_pathIndex, pos, pScene,m_subPathIndex);
        QPointF qpPoint = mapFromScene(pos);
        moveLineCircleTrackers(m_pathIndex, qpPoint);
        refreshEndArrow();
    }
    else
    {
        QGraphicsItem *pItemAt = pScene->itemAt(pos);
        if (pItemAt)
        {
            int subPathNum = getSubPathNum(pos);
            DrawLineTracker(subPathNum,pScene);
        }
    }
}

/********************************************************************************
 * Function: mouse release to item
 * Parameters: null
 * Return: none
 *******************************************************************************/
void GraphicsMultiPathItem::itemSelectMouseRelease()
{
    m_pathIndex = 0;
    m_handPolygonList.clear();
}
