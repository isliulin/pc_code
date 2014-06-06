/************************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2010
 *
 * Description: SamDraw tools classes implemention, to process the
 *              mouse/keyboard events, create the items & move items
 *              & resize one selected item.
 *
 * Functions:
 *
 * Modification Log:
 * Date             Name             Description Of Change
 * 2010-10-30       Bruce nie        Creation.
 ***********************************************************************/
#include "view/samdrawtool.h"
#include "view/samdrawscene.h"
#include "Frame/mainwindow.h"
#include "view/animationitem.h"
#include "view/ChartItem.h"
extern  MainWindow *pwnd;
#include "Command/unandrestack.h"
/*SamDraw tools static/global construct*/
QVector<SamDrawTool *> SamDrawTool::m_drawTools;
static SamDrawRectTool m_rectTool;
static SamDrawElipseTool m_elipseTool;
static SamDrawLineTool m_lineTool;
static SamDrawPolygonTool m_polygonTool;
//static SamDrawSelectTool m_selectTool;
SamDrawSelectTool m_selectTool;
static SamDrawFoldLineTool m_foldlineTool;
static SamDrawFreeLineTool m_freelineTool;
static SamDrawLineCircleTool m_lineCircleTool;
static SamDrawTextTool m_simpleTextTool;
static SamDrawAnimationTool m_animationTool;

static SamDrawRoundedRectTool m_roundedRectTool;
static SamDrawArcTool m_ArcTool;

/* Default tool is selection tool(m_selectTool) */
SAM_DRAW_ACT_TYPE_E SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;

/* Default tool status is unlocked*/
SAM_DRAW_TOOL_STATUS_E SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_UNLOCKED;

/*********************************************************************************
 * Function: Translate the coordinate for items in group
 * Parameters: ref. point, position of item, point of refernce, xfactor, yfactor
 * Return: translated point
 ********************************************************************************/
QPointF SamDrawTool::coordTranslateInGrp(const SAM_DRAW_RECT_POINT_TYPE_E &eRefPoint,
    const QPointF &qpPoint, const QRectF &qrcGrpBndRect,
    const qreal &dXfactor, const qreal &dYfactor)
{
    qreal dxp = 0.0, dyp = 0.0;
    qreal dXdiff = 0.0, dYdiff = 0.0;

    switch (eRefPoint)
    {
    case SAM_DRAW_RECT_TOP_LEFT:     /* ref. point 1 */
        dxp = ((qpPoint.x() - qrcGrpBndRect.x()) * dXfactor) + qrcGrpBndRect.x();
        dyp = ((qpPoint.y() - qrcGrpBndRect.y()) * dYfactor) + qrcGrpBndRect.y();
        break;
    case SAM_DRAW_RECT_TOP_RIGHT:    /* ref. point 3 */
        dXdiff = (qrcGrpBndRect.right() - qpPoint.x()) * dXfactor;
        dxp = (qrcGrpBndRect.right() - dXdiff);
        dyp = ((qpPoint.y() - qrcGrpBndRect.y()) * dYfactor) + qrcGrpBndRect.y();
        break;
    case SAM_DRAW_RECT_BOTTOM_RIGHT: /* ref. point 5 */
        dXdiff = (qrcGrpBndRect.right() - qpPoint.x()) * dXfactor;
        dxp = (qrcGrpBndRect.right() - dXdiff);
        dYdiff = (qrcGrpBndRect.bottom() - qpPoint.y()) * dYfactor;
        dyp = (qrcGrpBndRect.bottom() - dYdiff);
        break;
    case SAM_DRAW_RECT_BOTTOM_LEFT:  /* ref. point 7 */
        dxp = ((qpPoint.x() - qrcGrpBndRect.left()) * dXfactor) + qrcGrpBndRect.left();
        dYdiff = (qrcGrpBndRect.bottom() - qpPoint.y()) * dYfactor;
        dyp = (qrcGrpBndRect.bottom() - dYdiff);
        break;
    default :
        break;
    }

    return QPointF(dxp, dyp);
}

/********************************************************************************
 *Class SamDrawTool constructor
 ********************************************************************************/
SamDrawTool::SamDrawTool(SAM_DRAW_ACT_TYPE_E eDrawActType)
{
    pBackRect = NULL;
    m_eDrawActType = eDrawActType;
    m_drawTools.push_back(this);
}

/*********************************************************************************
 * Function: Find the tool by action type
 * Parameters: action type
 * Return: tool pointer
 ********************************************************************************/
SamDrawTool* SamDrawTool::FindTool(SAM_DRAW_ACT_TYPE_E eDrawActType)
{
    SamDrawTool *pTool = NULL;

    int iToolSize = m_drawTools.size();
    for (int i = 0; i < iToolSize; i++)
    {
        pTool = (SamDrawTool *)m_drawTools.at(i);
        if (pTool->m_eDrawActType == eDrawActType)
        {
            return pTool;
        }
    }

    return NULL;
}

/*********************************************************************************
 * Function: draw tool mouse press event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawTool::mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
}

/*********************************************************************************
 * Function: draw tool mouse move event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawTool::mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    pScene->views().first()->setCursor(Qt::CrossCursor);
}

/*********************************************************************************
 * Function: draw tool mouse release event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawTool::mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    s_eDrawActType = SAM_DRAW_SELECTION;
}

/*********************************************************************************
 * Function: draw tool mouse double click event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawTool::mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
}

/********************************************************************************
 * Function: Cancel the selected draw tool, and select selection tool
 * Parameters: scene pointer
 * Return: none
 *******************************************************************************/
void SamDrawTool::onCancel(QGraphicsScene *pScene)
{
    s_eDrawActType = SAM_DRAW_SELECTION;
    pScene->views().first()->setCursor(Qt::ArrowCursor);
}
/********************************************************************************
 * Function: Draw the backgroud Rect
 * Parameters: rect pointer
 * Return: none
 *******************************************************************************/
void   SamDrawTool::onReDrawRect(QPointF pos,QGraphicsScene *pScene)
{
    SamDrawScene *pSamscene = dynamic_cast<SamDrawScene *> (pScene);
    if(pBackRect)
    {
        pSamscene->removeItem(pBackRect);
    }
    QColor Color = pSamscene->m_sceneBackColor;
    int r = 0;
    int g = 0;
    int b = 0;
    Color.getRgb(&r,&g,&b);
    Color.setRgb(255 - r,255 - g,255 - b);
    qreal dWsize = 1.0;
    qreal dHsize = 1.0;

    dWsize = abs(pos.x() - pSamscene->prMousePoint.x());
    dHsize = abs(pos.y() - pSamscene->prMousePoint.y());

    QRectF qrcRect = QRectF(pSamscene->prMousePoint, QSize(dWsize,dHsize));
    qrcRect.setX(pos.x() < pSamscene->prMousePoint.x()? pos.x():pSamscene->prMousePoint.x());
    qrcRect.setY(pos.y() < pSamscene->prMousePoint.y()? pos.y():pSamscene->prMousePoint.y());
    qrcRect.setWidth(dWsize);
    qrcRect.setHeight(dHsize);
    pBackRect = new QRectItem(qrcRect);
    pBackRect->SetPattern(0);
    pBackRect->SetLineType(3);
    pBackRect->setZValue(1000);
    pBackRect->SetLineColor(Color);
    pSamscene->addItem(pBackRect);
    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pBackRect->setFlag(QGraphicsItem::ItemIsMovable, false);
}

/********************************************************************************
 *Class SamDrawElipseTool constructor
 ********************************************************************************/
SamDrawElipseTool::SamDrawElipseTool()
    :SamDrawTool(SAM_DRAW_ELLIPSE)
{
}

/*********************************************************************************
 * Function: elipse tool mouse press event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawElipseTool::mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
    {
        SamDrawTool::mousePressEvent(pScene, mouseEvent);
        return;
    }
    pScene->clearSelection();
    mouseEvent->setAccepted(true);
    //m_selectTool.mousePressEvent(pScene, mouseEvent);
}

/*********************************************************************************
 * Function: elipse tool mouse move event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawElipseTool::mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    SamDrawScene *pSamscene = dynamic_cast<SamDrawScene *> (pScene);
    if(pSamscene->bMousePress)
    onReDrawRect(mouseEvent->scenePos(),pScene);
    SamDrawTool::mouseMoveEvent(pScene, mouseEvent);
}

/*********************************************************************************
 * Function: elipse tool mouse release event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawElipseTool::mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    qreal dWsize = 1.0;
    qreal dHsize = 1.0;
    SamDrawScene *pSamscene;
    pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    if(pBackRect)
    {
        pSamscene->removeItem(pBackRect);
        pBackRect = NULL;
    }

    dWsize = abs(pSamscene->MouseReleasePos.x() - pSamscene->MousePressPos.x());
    dHsize = abs(pSamscene->MouseReleasePos.y() - pSamscene->MousePressPos.y());

    QPointF qpDownPoint;
    qpDownPoint.setX(pSamscene->MouseReleasePos.x() < pSamscene->MousePressPos.x()? pSamscene->MouseReleasePos.x():pSamscene->MousePressPos.x());
    qpDownPoint.setY(pSamscene->MouseReleasePos.y() < pSamscene->MousePressPos.y()? pSamscene->MouseReleasePos.y():pSamscene->MousePressPos.y());
    QGraphicsItem *pDrawItem = drawElipse(qpDownPoint, pScene);

    if (pDrawItem)
    {
        QElipseBasicItem *pElipse = dynamic_cast<QElipseBasicItem *>(pDrawItem);
        if(dWsize > 10.0 || dHsize > 10.0)
        {
            pElipse->SetWidth(dWsize);
            pElipse->SetHeight(dHsize);
        }
        pDrawItem->setSelected(true);
    }

    pScene->views().first()->setCursor(Qt::ArrowCursor);
    SamDrawTool::mouseReleaseEvent(pScene, mouseEvent);
}

/*********************************************************************************
 * Function: elipse tool mose double click event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawElipseTool::mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
}

/*********************************************************************************
 * Function: Draw elipse (construct elipse type object)
 * Parameters: scene pointer, mounse event
 * Return: qgraphicsitem pointer
 ********************************************************************************/
QGraphicsItem * SamDrawElipseTool::drawElipse(const QPointF qpPressedPt, QGraphicsScene *pScene)
{
    QRectF rc(qpPressedPt.x(),qpPressedPt.y(), 100, 100);
    QElipseBasicItem *pItem = new QElipseBasicItem(rc);
    SamDrawScene *pSamscene;
    pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    pItem->setId(pwnd->getNewId());
    pSamscene->addItem(pItem);
    pwnd->insertId(pItem->id());

//    pItem->setBrush(QBrush(QColor(0,0,255)));
    pItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pItem->setFlag(QGraphicsItem::ItemIsMovable, true);

    QRectF qrcBondingRect = pItem->sceneBoundingRect();
    pItem->drawTracker(TRK_SELECTED, pScene, qrcBondingRect);

    //控件新建的撤销和删除
    QGraphicsItem *pAddItem=dynamic_cast<QGraphicsItem *> (pItem);
    if(pAddItem)
    {
        pwnd->undoStack->push(new addItemToScence(pSamscene,pAddItem,true));
    }

    return pItem;
}

/********************************************************************************
 *Class SamDrawRectTool constructor
 ********************************************************************************/
SamDrawRectTool::SamDrawRectTool()
    :SamDrawTool(SAM_DRAW_RECT)
{
}

/*********************************************************************************
 * Function: Rect tool mouse press event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawRectTool::mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
    {
        SamDrawTool::mousePressEvent(pScene, mouseEvent);
        return;
    }
    pScene->clearSelection();
    mouseEvent->setAccepted(true);
}

/*********************************************************************************
 * Function: Rect tool mouse move event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawRectTool::mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    SamDrawScene *pSamscene = dynamic_cast<SamDrawScene *> (pScene);
    if(pSamscene->bMousePress)
    onReDrawRect(mouseEvent->scenePos(),pScene);
    SamDrawTool::mouseMoveEvent(pScene, mouseEvent);
}

/*********************************************************************************
 * Function: Rect tool mouse release event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawRectTool::mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    SamDrawScene *pSene = dynamic_cast<SamDrawScene *> (pScene);
    if(pBackRect)
    {
        pSene->removeItem(pBackRect);
        pBackRect = NULL;
    }
     QPointF qpDownPoint = pSene->MousePressPos;
    QGraphicsItem *pDrawItem = drawRect(qpDownPoint, pScene);

    if (pDrawItem)
    {
        pDrawItem->setSelected(true);
    }

    pScene->views().first()->setCursor(Qt::ArrowCursor);
    SamDrawTool::mouseReleaseEvent(pScene, mouseEvent);
}

/*********************************************************************************
 * Function: Rect tool mouse duble click event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawRectTool::mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
}

/*********************************************************************************
 * Function: Draw rect (construct rect type object)
 * Parameters: pressed point, scene pointer
 * Return: qgraphicsitem pointer
 ********************************************************************************/
QGraphicsItem * SamDrawRectTool::drawRect(const QPointF qpPressedPt, QGraphicsScene *pScene)
{
    qreal dWsize = 1.0;
    qreal dHsize = 1.0;
    SamDrawScene *pSamscene;
    pSamscene = dynamic_cast<SamDrawScene *>(pScene);

    dWsize = abs(pSamscene->MouseReleasePos.x() - pSamscene->MousePressPos.x());
    dHsize = abs(pSamscene->MouseReleasePos.y() - pSamscene->MousePressPos.y());

    QRectF qrcRect = QRectF(qpPressedPt, QSize(100,100));
    qrcRect.setX(pSamscene->MouseReleasePos.x() < pSamscene->MousePressPos.x()? pSamscene->MouseReleasePos.x():pSamscene->MousePressPos.x());
    qrcRect.setY(pSamscene->MouseReleasePos.y() < pSamscene->MousePressPos.y()? pSamscene->MouseReleasePos.y():pSamscene->MousePressPos.y());
    if(dWsize > 10.0 || dHsize > 10.0)
    {
        qrcRect.setWidth(dWsize);
        qrcRect.setHeight(dHsize);
    }
    QRectBasicItem *pItem = new QRectBasicItem(qrcRect);
    pItem->setId(pwnd->getNewId());
    pSamscene->addItem(pItem);
    pwnd->insertId(pItem->id());

    pItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pItem->setFlag(QGraphicsItem::ItemIsMovable, true);

    QRectF qrcBondingRect = pItem->sceneBoundingRect();
    pItem->drawTracker(TRK_SELECTED, pScene, qrcBondingRect);

    //控件新建的撤销和删除
    QGraphicsItem *pAddItem=dynamic_cast<QGraphicsItem *> (pItem);
    if(pAddItem)
    {
        pwnd->undoStack->push(new addItemToScence(pSamscene,pAddItem,true));
    }

    return pItem;
}

/********************************************************************************
 *Class SamDrawLineTool constructor
 ********************************************************************************/
SamDrawLineTool::SamDrawLineTool()
    :SamDrawTool(SAM_DRAW_LINE)
{
}

/*********************************************************************************
 * Function: Line tool mouse press event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawLineTool::mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
    {
        SamDrawTool::mousePressEvent(pScene, mouseEvent);
        return;
    }
    pScene->clearSelection();
    mouseEvent->setAccepted(true);
}

/*********************************************************************************
 * Function: Line tool mouse move event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawLineTool::mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    SamDrawScene *pSamscene = dynamic_cast<SamDrawScene *> (pScene);
    if(pSamscene->bMousePress)
    onReDrawRect(mouseEvent->scenePos(),pScene);
    SamDrawTool::mouseMoveEvent(pScene, mouseEvent);
}

/*********************************************************************************
 * Function: Line tool mouse release event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawLineTool::mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    SamDrawScene *pSamscene;
    pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    if(pBackRect)
    {
        pSamscene->removeItem(pBackRect);
        pBackRect = NULL;
    }
    QGraphicsItem *pDrawItem = drawLine(pSamscene->MousePressPos, pSamscene->MouseReleasePos,pScene);

    if (pDrawItem)
    {
        pDrawItem->setSelected(true);
    }
    mouseEvent->setAccepted(true);

    pScene->views().first()->setCursor(Qt::ArrowCursor);
    SamDrawTool::mouseReleaseEvent(pScene, mouseEvent);
}

/*********************************************************************************
 * Function: Line tool mouse double click event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawLineTool::mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{

}

/*********************************************************************************
 * Function: Draw line (construct a line type object)
 * Parameters: pressed point, scene pointer
 * Return: graphicsitem pointer
 ********************************************************************************/
QGraphicsItem* SamDrawLineTool::drawLine(const QPointF qpPressedPt, const QPointF qpReleasedPt,QGraphicsScene *pScene)
{
    qreal x1=qpPressedPt.x();
    qreal y1=qpPressedPt.y();
    qreal x2;
    qreal y2;
    if(qpPressedPt == qpReleasedPt)
    {
        x2 =  x1 + 100;
        y2 =  y1 + 100;
    }
    else
    {
        x2 = qpReleasedPt.x();
        y2 = qpReleasedPt.y();
    }

    QPainterPath *path = new QPainterPath();
    path->moveTo(x1, y1);
    path->lineTo(x2, y2);
    QLineBasicItem *pItem = new QLineBasicItem(*path);
    SamDrawScene *pSamscene;
    pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    pItem->setId(pwnd->getNewId());
    pSamscene->addItem(pItem);
    pwnd->insertId(pItem->id());
    pItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pItem->setFlag(QGraphicsItem::ItemIsMovable, true);

    SamDrawTackerRect *pItemTracker = NULL;
    if (pItem->getResizable() == true)
    {
        pItemTracker = new SamDrawTackerRect(qpPressedPt);
        if (pItemTracker)
        {
            pScene->addItem(pItemTracker);
            pItem->m_pvecTrackers.push_back(pItemTracker);
        }
    }

    QPointF qpPt2(x2, y2);
    pItemTracker = NULL;

    if (pItem->getResizable() == true)
    {
        pItemTracker = new SamDrawTackerRect(qpPt2);
        if (pItemTracker)
        {
            pScene->addItem(pItemTracker);
            pItem->m_pvecTrackers.push_back(pItemTracker);
        }
    }

    //控件新建的撤销和删除
    QGraphicsItem *pAddItem=dynamic_cast<QGraphicsItem *> (pItem);
    if(pAddItem)
    {
        pwnd->undoStack->push(new addItemToScence(pSamscene,pAddItem,true));
    }

    return pItem;
}

/********************************************************************************
 *Class SamDrawPolygonTool constructor
 ********************************************************************************/
SamDrawPolygonTool::SamDrawPolygonTool()
    :SamDrawTool(SAM_DRAW_POLYGON)
{
    m_pPolygonItem = NULL;
    m_qpsPolygon.clear();
    m_ulPressedCnt = 0;
}

/*********************************************************************************
 * Function: Polygon tool mouse press event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawPolygonTool::mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF qpDownPoint = mouseEvent->scenePos();
    if (m_qpLastPt == qpDownPoint)
    {
        if (mouseEvent->button() == Qt::LeftButton)
        {
            if (m_pPolygonItem)
                m_pPolygonItem->setSelected(true);
            mouseEvent->setAccepted(true);
            return;
        }
        else if (mouseEvent->button() == Qt::RightButton)
        {
            if (m_pPolygonItem)
                m_pPolygonItem->setSelected(true);
            mouseEvent->setAccepted(true);

            m_pPolygonItem = NULL;
            m_qpsPolygon.clear();
            m_ulPressedCnt = 0;
            SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_UNLOCKED;
            s_eDrawActType = SAM_DRAW_SELECTION;
            return;
        }
    }

    m_qpLastPt = qpDownPoint;

    if (mouseEvent->button() == Qt::LeftButton)
    {
        if (m_pPolygonItem == NULL)
        {
            QGraphicsItem *pPolygonItem = drawPolygon(qpDownPoint, pScene);
            pScene->clearSelection();
            if (pPolygonItem)
                pPolygonItem->setSelected(true);
            mouseEvent->setAccepted(true);
            SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_LOCKED;
        }
        else
        {
            m_qpsPolygon.push_back(qpDownPoint);
            m_pPolygonItem->setSelected(true);
            mouseEvent->setAccepted(true);

            if (m_pPolygonItem->getResizable() == true)
            {
                SamDrawTackerRect *pItem = new SamDrawTackerRect(qpDownPoint);
                if (pItem)
                {
                    pScene->addItem(pItem);
                    m_pPolygonItem->m_pvecTrackers.push_back(pItem);
                }
            }
        }
        m_ulPressedCnt++;
    }
    else if (mouseEvent->button() == Qt::RightButton)
    {
        if (m_pPolygonItem)
        {
            if (m_pPolygonItem->getResizable() == true)
            {
                SamDrawTackerRect *pItem = new SamDrawTackerRect(qpDownPoint);
                if (pItem)
                {
                    pScene->addItem(pItem);
                    m_pPolygonItem->m_pvecTrackers.push_back(pItem);
                }
            }

            pScene->clearSelection();
            if (m_pPolygonItem)
                m_pPolygonItem->setSelected(true);
            mouseEvent->setAccepted(true);
        }
        m_pPolygonItem = NULL;
        m_qpsPolygon.clear();
        m_ulPressedCnt = 0;
        s_eDrawActType = SAM_DRAW_SELECTION;
        SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_UNLOCKED;
        SamDrawTool::mousePressEvent(pScene, mouseEvent);
    }
}

/*********************************************************************************
 * Function: Polygon mouse move event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawPolygonTool::mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF qpCurPoint = mouseEvent->scenePos();
    if (m_pPolygonItem)
    {
        //if (m_qpsPolygon.size() <= 1 || (m_qpsPolygon.size() <= (int)m_ulPressedCnt))
        if (m_qpsPolygon.size() <= 1)
        {
            m_qpsPolygon.push_back(qpCurPoint);
        }
        else
        {
            //m_qpsPolygon[m_ulPressedCnt] = qpCurPoint;
            m_qpsPolygon[m_qpsPolygon.size() - 1] = qpCurPoint;
        }

        QPolygonF qpsCurPolygon = m_qpsPolygon;
        for (int i = 0; i < qpsCurPolygon.size(); i++)
        {
            qpsCurPolygon[i] = m_pPolygonItem->mapFromScene(qpsCurPolygon[i]);
        }

        m_pPolygonItem->setPolygon(qpsCurPolygon);
        m_pPolygonItem->setSelected(true);
        mouseEvent->setAccepted(true);
    }

    SamDrawTool::mouseMoveEvent(pScene, mouseEvent);
}

/*********************************************************************************
 * Function: Polygon tool mouse release event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawPolygonTool::mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
}

/*********************************************************************************
 * Function: Draw polygon (construct polygon type object)
 * Parameters: pressed point, scene pointer
 * Return: graphicsitem pointer
 ********************************************************************************/
QGraphicsItem *SamDrawPolygonTool::drawPolygon(const QPointF qpPressedPt, QGraphicsScene *pScene)
{
    m_qpsPolygon.clear();
    m_qpsPolygon.push_back(qpPressedPt);
    QPolygonBasicItem *pItem = new QPolygonBasicItem(m_qpsPolygon);
    SamDrawScene *pSamscene;
    pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    pItem->setId(pwnd->getNewId());
    pSamscene->addItem(pItem);
    pwnd->insertId(pItem->id());
    pItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_pPolygonItem = pItem;

    if (pItem->getResizable() == true)
    {
        SamDrawTackerRect *pItemTracker = new SamDrawTackerRect(qpPressedPt);
        if (pItemTracker)
        {
            pScene->addItem(pItemTracker);
            m_pPolygonItem->m_pvecTrackers.push_back(pItemTracker);
        }
    }

    //控件新建的撤销和删除
    QGraphicsItem *pAddItem=dynamic_cast<QGraphicsItem *> (pItem);
    if(pAddItem)
    {
        pwnd->undoStack->push(new addItemToScence(pSamscene,pAddItem,true));
    }

    return pItem;
}

/*********************************************************************************
 * Function: Polygon tool mouse duble click event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawPolygonTool::mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
}

/*********************************************************************************
 * Function: Polygon tool onCancel
 * Parameters: scene pointer
 * Return: none
 ********************************************************************************/
void SamDrawPolygonTool::onCancel(QGraphicsScene *pScene)
{
    if (m_pPolygonItem)
    {
        //delete m_pPolygonItem;
    }

    if (m_pPolygonItem)
    {
        //修改为按esc按键退出后 少加入一个绿色小矩形问题
        if(m_qpsPolygon.size() > m_pPolygonItem->m_pvecTrackers.size())
        {
            QVector<QPointF> qpCurPoints = m_qpsPolygon;
            for (int i = 0; i < m_qpsPolygon.size(); i++)
            {
                qpCurPoints[i] = m_pPolygonItem->mapFromScene(qpCurPoints[i]);
            }
            if (m_pPolygonItem->getResizable() == true)
            {
                SamDrawTackerRect *pItem = new SamDrawTackerRect(qpCurPoints.at(qpCurPoints.size() -1));
                if (pItem)
                {
                    pScene->addItem(pItem);
                    m_pPolygonItem->m_pvecTrackers.push_back(pItem);
                }
            }
        }
    }

    m_pPolygonItem = NULL;
    m_qpsPolygon.clear();
    m_ulPressedCnt = 0;
    SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_UNLOCKED;

    SamDrawTool::onCancel(pScene);
}

/********************************************************************************
 *Class SamDrawSelectTool constructor
 ********************************************************************************/
SamDrawSelectTool::SamDrawSelectTool()
    :SamDrawTool(SAM_DRAW_SELECTION)
{
    m_eExpType = EXPD_BUTT;
    m_uiGrpTypeKey = 0;
}

/*********************************************************************************
 * Function: selection mouse press event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawSelectTool::mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsItem *pSizeItem = 0;
    QRectBasicItem *pRectNew = 0;
    QElipseBasicItem *pElipseNew = 0;
    QLineBasicItem *pLineNew = 0;
    QPolygonBasicItem *pPolygonNew = 0;
    QFoldLineBasicItem *pFoldLineNew = 0;
    QFreeLineBasicItem *pFreeLineNew = 0;
    QItemGroup *pItemGroup = 0;
    QLineCircleBasicItem *pLineCircleNew = 0;   //add by tanghaiguo
    QSimpleTextItem *pText = 0;
    QRoundedRectBasic *pRoundedRectNew = 0;
    QArcBasicItem *pArcNew = 0;

    QRectItem *pRect = 0;
    QElipseItem *pElipse = 0;
    QLineItem *pLine = 0;
    QPolygonItem *pPolygon = 0;
    QFoldLineItem *pFoldLine = 0;
    QFreeLineItem *pFreeLine = 0;
    QLineCircleItem *pLineCircle = 0;   //add by tanghaiguo
    QRoundedRect *pRoundedRect = 0;
    QArcItem *pArc = 0;

    m_uiGrpTypeKey = 0;

    SamDrawScene *myScene = dynamic_cast<SamDrawScene *>(pScene);
    //QPointF qpLocalPt = mouseEvent->scenePos();
    QPointF qpLocalPt = myScene->prMousePoint;
    m_eSelectMode = SEL_MOD_NONE;

    if (mouseEvent->button() != Qt::LeftButton)
    {
        QGraphicsItem *pItemAt = pScene->itemAt(qpLocalPt);
        if (pItemAt)
        {
            QList <QGraphicsItem *> pSelectItems;
            pSelectItems = pScene->selectedItems();

            while (pItemAt->parentItem())
            {
                pItemAt = pItemAt->parentItem();
            }
            if(!pSelectItems.contains(pItemAt))
            {
                pScene->clearSelection();
            }
            pItemAt->setSelected(true);
            mouseEvent->setAccepted(true);
        }

        return;
    }

    //add by tanghaiguo
    foreach (QGraphicsItem *pItem, pScene->items())
    {
        if (pItem && ((pItem->type() == (QGraphicsItem::UserType + 998))
            || (pItem->type() == (QGraphicsItem::UserType + 997))))
            {
            pScene->removeItem(pItem);
        }
    }
    //end add by tanghaiguo

    /* If pressed shift add the item to selected items. */
    if (mouseEvent->modifiers() == Qt::ShiftModifier)
    {
        QGraphicsItem *pItemAt = pScene->itemAt(qpLocalPt);
        if (pItemAt)
        {
            pItemAt = pItemAt->topLevelItem();
            pItemAt->setSelected(true);
            mouseEvent->setAccepted(true);
            //m_eSelectMode = SEL_MOD_SIZE;
            m_eSelectMode = SEL_MOD_MOVE;
        }
    }

    /* Only one object was selected. */
    if (pScene->selectedItems().size() == 1)
    {
        /* Hit test the selected object */
        pSizeItem = pScene->selectedItems().first();
        QRectF qrcBondingRect = pSizeItem->sceneBoundingRect();
        switch (pSizeItem->type())
        {
        case SAM_DRAW_OBJECT_RECT_NEW:
          pRectNew = dynamic_cast<QRectBasicItem *> (pSizeItem);
          if (pRectNew)
          {
             m_ulDragHandle = pRectNew->hitTest(qpLocalPt, qrcBondingRect, true);
          }
          break;
        case SAM_DRAW_OBJECT_ELIPSE_NEW:
          pElipseNew = dynamic_cast<QElipseBasicItem *> (pSizeItem);
          if (pElipseNew)
          {
             m_ulDragHandle = pElipseNew->hitTest(qpLocalPt, qrcBondingRect, true);
          }
          break;
        case SAM_DRAW_OBJECT_LINE_NEW:
          pLineNew = dynamic_cast<QLineBasicItem *> (pSizeItem);
          if (pLineNew)
          {
             m_ulDragHandle = pLineNew->hitTest(qpLocalPt, qrcBondingRect, true);
          }
          break;
        case SAM_DRAW_OBJECT_POLYGON_NEW:
          pPolygonNew = dynamic_cast<QPolygonBasicItem *> (pSizeItem);
          if (pPolygonNew)
          {
              m_ulDragHandle = pPolygonNew->hitTest(qpLocalPt, qrcBondingRect, true);
          }
          break;
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:
          pFoldLineNew = dynamic_cast<QFoldLineBasicItem *> (pSizeItem);
          if (pFoldLineNew)
          {
              m_ulDragHandle = pFoldLineNew->hitTest(qpLocalPt, qrcBondingRect, true);
          }
          break;
        case SAM_DRAW_OBJECT_FREELINE_NEW:
          pFreeLineNew = dynamic_cast<QFreeLineBasicItem *> (pSizeItem);
          if (pFreeLineNew)
          {
              m_ulDragHandle = pFreeLineNew->hitTest(qpLocalPt, qrcBondingRect, true);
          }
          break;
        case SAM_DRAW_OBJECT_GROUP:
          pItemGroup = dynamic_cast<QItemGroup *> (pSizeItem);
          if (pItemGroup)
          {
              m_ulDragHandle = pItemGroup->hitTest(qpLocalPt, qrcBondingRect, true);
              if (m_ulDragHandle > 0)
              {
                  if(SAM_DRAW_GROUP_CHART == pItemGroup->GroupType())
                  {
                      ChartItem *pChartItem = dynamic_cast<ChartItem *> (pSizeItem);
                      if(ENCOMMON_TYPE == pChartItem->m_eGraphType)
                      {
                          if(CIRCLE == pChartItem->common_st.eShapeType
                             || SECTOR == pChartItem->common_st.eShapeType)
                          {
                              m_uiGrpTypeKey = 1;
                          }
                      }
                      else if(ENMETER_TYPE == pChartItem->m_eGraphType)
                      {
                          m_uiGrpTypeKey = 1;
                      }
                  }
              }
          }
          break;
         case SAM_DRAW_OBJECT_LINECIRCLE_NEW:   //add by tanghaiguo
            pLineCircleNew = dynamic_cast<QLineCircleBasicItem *> (pSizeItem);
            if (pLineCircleNew)
            {
                m_ulDragHandle = pLineCircleNew->itemSelectMousePress(qpLocalPt);
            }
            break;
        case SAM_DRAW_OBJECT_TEXT:
          pText = dynamic_cast<QSimpleTextItem *> (pSizeItem);
          if (pText)
          {
              m_ulDragHandle = pText->hitTest(qpLocalPt, qrcBondingRect, true);
          }
          break;
        case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
            pRoundedRectNew = dynamic_cast<QRoundedRectBasic *> (pSizeItem);
            if (pRoundedRectNew)
            {
                m_ulDragHandle = pRoundedRectNew->hitTest(qpLocalPt, qrcBondingRect, true);
            }
            break;
        case SAM_DRAW_OBJECT_ARC_NEW:
            pArcNew = dynamic_cast<QArcBasicItem *> (pSizeItem);
            if (pArcNew)
            {
                qrcBondingRect = pArcNew->getEllipseRect();
                qrcBondingRect = pArcNew->mapRectToScene(qrcBondingRect);
                m_ulDragHandle = pArcNew->hitTest(qpLocalPt, qrcBondingRect, true);
            }
            break;
////////////////////wxy add start
        case SAM_DRAW_OBJECT_RECT:
          pRect = dynamic_cast<QRectItem *> (pSizeItem);
          if (pRect)
          {
             m_ulDragHandle = pRect->hitTest(qpLocalPt, qrcBondingRect, true);
          }
          break;
        case SAM_DRAW_OBJECT_ELIPSE:
          pElipse = dynamic_cast<QElipseItem *> (pSizeItem);
          if (pElipse)
          {
             m_ulDragHandle = pElipse->hitTest(qpLocalPt, qrcBondingRect, true);
          }
          break;
        case SAM_DRAW_OBJECT_LINE:
          pLine = dynamic_cast<QLineItem *> (pSizeItem);
          if (pLine)
          {
             m_ulDragHandle = pLine->hitTest(qpLocalPt, qrcBondingRect, true);
          }
          break;
        case SAM_DRAW_OBJECT_POLYGON:
          pPolygon = dynamic_cast<QPolygonItem *> (pSizeItem);
          if (pPolygon)
          {
              m_ulDragHandle = pPolygon->hitTest(qpLocalPt, qrcBondingRect, true);
          }
          break;
        case SAM_DRAW_OBJECT_FOLDLINE:
          pFoldLine = dynamic_cast<QFoldLineItem *> (pSizeItem);
          if (pFoldLine)
          {
              m_ulDragHandle = pFoldLine->hitTest(qpLocalPt, qrcBondingRect, true);
          }
          break;
        case SAM_DRAW_OBJECT_FREELINE:
          pFreeLine = dynamic_cast<QFreeLineItem *> (pSizeItem);
          if (pFreeLine)
          {
              m_ulDragHandle = pFreeLine->hitTest(qpLocalPt, qrcBondingRect, true);
          }
          break;
         case SAM_DRAW_OBJECT_LINECIRCLE:   //add by tanghaiguo
            pLineCircle = dynamic_cast<QLineCircleItem *> (pSizeItem);
            if (pLineCircle)
            {
                m_ulDragHandle = pLineCircle->itemSelectMousePress(qpLocalPt);
            }
            break;
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
            pRoundedRect = dynamic_cast<QRoundedRect *> (pSizeItem);
            if (pRoundedRect)
            {
                m_ulDragHandle = pRoundedRect->hitTest(qpLocalPt, qrcBondingRect, true);
            }
            break;
        case SAM_DRAW_OBJECT_ARC:
            pArc = dynamic_cast<QArcItem *> (pSizeItem);
            if (pArc)
            {
                qrcBondingRect = pArc->getEllipseRect();
                qrcBondingRect = pArc->mapRectToScene(qrcBondingRect);
                m_ulDragHandle = pArc->hitTest(qpLocalPt, qrcBondingRect, true);
            }
            break;
////////////////////wxy add end
        default:
          break;
        }
        //nDragHandle = pSizeItem->hitTest(qpoint, true);
        if (m_ulDragHandle > 0)
        {
            /* mouse postion on tracker, set mouse accepted */
            m_eSelectMode = SEL_MOD_SIZE;
            mouseEvent->setAccepted(true);
        }
        /* Pressed ctrl, clone the object */
        else if (mouseEvent->modifiers() == Qt::ControlModifier
                 && myScene->bIsLibrary == true)//图库则不复制
        {
            if (myScene->itemAt(qpLocalPt) && pSizeItem == myScene->itemAt(qpLocalPt)->topLevelItem())
            {
                if (pRect)
                {
                    QGraphicsItem *pClone = pRect->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pRect->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pRectNew)
                {
                    QGraphicsItem *pClone = pRectNew->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pRectNew->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pElipse)
                {
                    QGraphicsItem *pClone = pElipse->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pElipse->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pElipseNew)
                {
                    QGraphicsItem *pClone = pElipseNew->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pElipseNew->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pLine)
                {
                    QGraphicsItem *pClone = pLine->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pLine->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pLineNew)
                {
                    QGraphicsItem *pClone = pLineNew->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pLineNew->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pPolygon)
                {
                    QGraphicsItem *pClone = pPolygon->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pPolygon->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pPolygonNew)
                {
                    QGraphicsItem *pClone = pPolygonNew->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pPolygonNew->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pRoundedRect)
                {
                    QGraphicsItem *pClone = pRoundedRect->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pRoundedRect->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pRoundedRectNew)
                {
                    QGraphicsItem *pClone = pRoundedRectNew->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pRoundedRectNew->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pArc)
                {
                    QGraphicsItem *pClone = pArc->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pArc->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pArcNew)
                {
                    QGraphicsItem *pClone = pArcNew->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pArcNew->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pFoldLine)
                {
                    QGraphicsItem *pClone = pFoldLine->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pFoldLine->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pFoldLineNew)
                {
                    QGraphicsItem *pClone = pFoldLineNew->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pFoldLineNew->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pFreeLine)
                {
                    QGraphicsItem *pClone = pFreeLine->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pClone->setSelected(false);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pFreeLineNew)
                {
                    QGraphicsItem *pClone = pFreeLineNew->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pClone->setSelected(false);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pText)
                {
//                    QGraphicsItem *pClone = pText->Clone();
//                    pScene->addItem(pClone);
//                    pClone->setSelected(false);
                    DrawItemToScene GroupFunction;
                    QGraphicsItem *pTextItem;
                    GroupFunction.CopyItem(&pTextItem, pText);
                    myScene->addItem(pTextItem);
                    pTextItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                    pTextItem->setFlag(QGraphicsItem::ItemIsMovable, true);
                    pText->setSelected(false);
                    pTextItem->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pTextItem,true));
                }
                else if (pLineCircle)
                {
                    QGraphicsItem *pClone = pLineCircle->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pLineCircle->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pLineCircleNew)
                {
                    QGraphicsItem *pClone = pLineCircleNew->Clone();
                    myScene->addItem(pClone);
                    myScene->clearSelection();
                    pLineCircleNew->setSelected(false);
                    pClone->setSelected(true);
                    pwnd->undoStack->push(new addItemToScence(myScene,pClone,true));
                }
                else if (pItemGroup)
                {
                    DrawItemToScene GroupFunction;
                    QGraphicsItem *pGroup;
                    GroupFunction.CopyItem(&pGroup, pItemGroup);
                    myScene->addItem(pGroup);
                    pGroup->setFlag(QGraphicsItem::ItemIsSelectable, true);
                    pGroup->setFlag(QGraphicsItem::ItemIsMovable, true);
                    pItemGroup->setSelected(false);
                    pwnd->undoStack->push(new addItemToScence(myScene,pGroup,true));
                    pGroup->setSelected(true);
                }
            }
        }
    }
    else if(pScene->selectedItems().size() > 1)
    {
        QGraphicsItem *pItem = pScene->itemAt(qpLocalPt);
        if(pItem)
        {
            pItem = pItem->topLevelItem();
            QList <QGraphicsItem *> pSelectItems;
            pSelectItems = pScene->selectedItems();
            if(pSelectItems.contains(pItem))
            {
                mouseEvent->setAccepted(true);
            }
        }
    }
    // See if the click was on an item, select and start move if so
    if (m_eSelectMode == SEL_MOD_NONE)
    {
        QGraphicsItem *pItem = pScene->itemAt(qpLocalPt);
        if (pItem != NULL)
        {
            m_eSelectMode = SEL_MOD_MOVE;

            // SHIFT not pressed, clear selection and re-select object
            if (mouseEvent->modifiers() == Qt::ShiftModifier)
            {
                if (!pItem->isSelected())
                {
                    pItem->setSelected(true);
                }
            }
        }
    }

    // Click on background, start a net-selection
    if (m_eSelectMode == SEL_MOD_NONE)
    {
        // 如果此时没有按下键盘 SHIFT 键, clear selection
        if (mouseEvent->modifiers() != Qt::ShiftModifier)
        {
            pScene->clearSelection();
        }
        m_eSelectMode = SEL_MOD_NET_SELECT;
    }
}

/*********************************************************************************
 * Function: selection mouse move event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawSelectTool::mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    QRectBasicItem *pRectNew = 0;
    QElipseBasicItem *pElipseNew = 0;
    QLineBasicItem *pLineNew = 0;
    QPolygonBasicItem *pPolygonNew = 0;
    QFoldLineBasicItem *pFoldLineNew = 0;
    QFreeLineBasicItem *pFreeLineNew = 0;
    QItemGroup *pItemGroup = 0;
    QLineCircleBasicItem *pLineCircleNew = 0;   //add by tanghaiguo
    QSimpleTextItem *pText = 0;
    QRoundedRectBasic *pRoundedRectNew = 0;
    QArcBasicItem *pArcNew = 0;

    QRectItem *pRect = 0;
    QElipseItem *pElipse = 0;
    QLineItem *pLine = 0;
    QPolygonItem *pPolygon = 0;
    QFoldLineItem *pFoldLine = 0;
    QFreeLineItem *pFreeLine = 0;
    QLineCircleItem *pLineCircle = 0;   //add by tanghaiguo
    QRoundedRect *pRoundedRect = 0;
    QArcItem *pArc = 0;

    const qreal dDelta = 0.5;
    QPointF local = mouseEvent->scenePos();

    QRectF qrcBondingRect, qrcCurBondingRect, qrcGrpBndRect, qrcGrpBndRectCur;
    int DragHandle = 0;
    bool bFoursquare = false;
	bool bShiftMode = false;

    /*Only one item is selected*/
    if (pScene->selectedItems().size() == 1
        && m_eSelectMode != SEL_MOD_MOVE
        && m_eSelectMode != SEL_MOD_NET_SELECT
        && (pScene->selectedItems().first()->flags()
            & QGraphicsItem::ItemIsMovable) )
    {
        /*location validity checking*/
//        if (local.x() > pScene->sceneRect().right())
//        {
//            local.rx() = pScene->sceneRect().right();
//        }
//        else if (local.x() < pScene->sceneRect().left())
//        {
//            local.rx() = pScene->sceneRect().left();
//        }

//        if (local.y() > pScene->sceneRect().bottom())
//        {
//            local.ry() = pScene->sceneRect().bottom();
//        }
//        else if (local.y() < pScene->sceneRect().top())
//        {
//            local.ry() = pScene->sceneRect().top();
//        }

        DRAG_CROSS_TYPE_E eCrossType = DRAG_CROSS_TYPE_BUTT;
        QGraphicsItem *pItem = pScene->selectedItems().first();
        qrcBondingRect = pItem->sceneBoundingRect();

        /*The width or height changed*/
        switch (m_ulDragHandle)
        {
        case SAM_DRAW_RECT_TOP_LEFT:
        case SAM_DRAW_RECT_TOP_RIGHT:
        case SAM_DRAW_RECT_BOTTOM_RIGHT:
        case SAM_DRAW_RECT_BOTTOM_LEFT:
            {
                m_eExpType = EXPD_ALL;
            }
            break;
        case SAM_DRAW_RECT_TOP_CENTER:
        case SAM_DRAW_RECT_BOTTOM_CENTER:
            {
                m_eExpType = EXPD_HEIGHT;
            }
            break;
        case SAM_DRAW_RECT_CENTER_RIGHT:
        case SAM_DRAW_RECT_CENTER_LEFT:
            {
                m_eExpType = EXPD_WIDTH;
            }
            break;
        default :
            break;
        }

        /*Ctrl pressed while resize selected item*/
        if (mouseEvent->modifiers() == Qt::ControlModifier)
        {
            bFoursquare = true;
        }
		if (mouseEvent->modifiers() == Qt::ShiftModifier)
		{
			bShiftMode = true;
		}
        /*Deal with the selected item (resize)*/
        switch (pItem->type())
        {
        case SAM_DRAW_OBJECT_RECT_NEW:
            pRectNew = dynamic_cast<QRectBasicItem *> (pItem);
            if (!pRectNew)
            {
                break;
            }

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pRectNew->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pRectNew->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                //pScene->views().first()->setCursor(pRect->getHandleCursor(m_ulDragHandle));
                qrcCurBondingRect = pRectNew->moveHandleTo(m_ulDragHandle, local, qrcBondingRect, bFoursquare);
                qrcCurBondingRect = pRectNew->mapRectFromScene(qrcCurBondingRect);
                eCrossType = pRectNew->NormalizeDragedRect(qrcCurBondingRect);

                pRectNew->setRectA(qrcCurBondingRect);
                pScene->update();
                pRectNew->refreshTrackers(qrcCurBondingRect, pScene);
                this->exchgDraghandle(eCrossType);
            }
            break;
        case SAM_DRAW_OBJECT_ELIPSE_NEW:
            pElipseNew = dynamic_cast<QElipseBasicItem *> (pItem);
            if (!pElipseNew)
            {
                break;
            }

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pElipseNew->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pElipseNew->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                //pScene->views().first()->setCursor(pElipse->getHandleCursor(m_ulDragHandle));
                qrcCurBondingRect = pElipseNew->moveHandleTo(m_ulDragHandle, local, qrcBondingRect, bFoursquare);
                /* Avoid 0 size item issue when calculate the position */
                int iPenWidth = pElipseNew->GetLineWidth();
                if (iPenWidth > 0)
                {
                    iPenWidth = iPenWidth * 2;
                    if (qFabs(qrcCurBondingRect.height()) <= iPenWidth
                        || qFabs(qrcCurBondingRect.width()) <= iPenWidth)
                    {
                        break;
                    }
                }

                qrcCurBondingRect = pElipseNew->mapRectFromScene(qrcCurBondingRect);
                //pElipse->refreshTrackers(qrcCurBondingRect);
                eCrossType = pElipseNew->NormalizeDragedRect(qrcCurBondingRect);

                pElipseNew->setRectA(qrcCurBondingRect);
                pScene->update();
                pElipseNew->refreshTrackers(qrcCurBondingRect, pScene);
                this->exchgDraghandle(eCrossType);
            }
            break;
        case SAM_DRAW_OBJECT_LINE_NEW:
            pLineNew = dynamic_cast<QLineBasicItem *> (pItem);
            if (!pLineNew)
            {
                break;
            }

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pLineNew->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pLineNew->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                pLineNew->setShiftMode(bShiftMode);
                pLineNew->moveHandleTo(m_ulDragHandle, local, qrcBondingRect);
                QPointF qpPoint = pLineNew->mapFromScene(local);
                pLineNew->movePathTrackers(m_ulDragHandle, qpPoint);
                pLineNew->setShiftMode(false);
                pLineNew->refreshEndArrow();
                pScene->update();
            }
            break;
        case SAM_DRAW_OBJECT_POLYGON_NEW:
            pPolygonNew = dynamic_cast<QPolygonBasicItem *> (pItem);
            if (!pPolygonNew)
            {
                break;
            }

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pPolygonNew->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pPolygonNew->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                pPolygonNew->moveHandleTo(m_ulDragHandle, local, qrcBondingRect);
                QPointF qpPoint = pPolygonNew->mapFromScene(local);
                pPolygonNew->movePolygonTrackers(m_ulDragHandle, qpPoint);
                pPolygonNew->setPattern(pPolygonNew->getPattern());
                pScene->update();
            }
            break;
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:
            pFoldLineNew = dynamic_cast<QFoldLineBasicItem *> (pItem);
            if (!pFoldLineNew)
            {
                break;
            }

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pFoldLineNew->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pFoldLineNew->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                pFoldLineNew->moveHandleTo(m_ulDragHandle, local, qrcBondingRect);
                QPointF qpPoint = pFoldLineNew->mapFromScene(local);
                pFoldLineNew->movePathTrackers(m_ulDragHandle, qpPoint);
                pFoldLineNew->refreshEndArrow();
                pScene->update();
            }
            break;
        case SAM_DRAW_OBJECT_FREELINE_NEW:
            pFreeLineNew = dynamic_cast<QFreeLineBasicItem *> (pItem);
            if (!pFreeLineNew)
            {
                break;
            }

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pFreeLineNew->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pFreeLineNew->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                pFreeLineNew->moveHandleTo(m_ulDragHandle, local, qrcBondingRect);
                QPointF qpPoint = pFreeLineNew->mapFromScene(local);
                pFreeLineNew->movePathTrackers(m_ulDragHandle, qpPoint);
                pFreeLineNew->refreshEndArrow();
                pScene->update();
            }
            break;
        case SAM_DRAW_OBJECT_GROUP:
            pItemGroup = dynamic_cast<QItemGroup *> (pItem);
            if (!pItemGroup)
            {
                break;
            }

            qrcGrpBndRect = qrcBondingRect;

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pItemGroup->hitTest(local, qrcGrpBndRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pItemGroup->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle) > 0 && (m_eSelectMode == SEL_MOD_SIZE))
            {
                //pScene->views().first()->setCursor(pItemGroup->getHandleCursor(m_ulDragHandle));
                qreal dFactorW = 0.0, dFactorH = 0.0;

                /*if (m_uiGrpTypeKey == GROUP_TYPE_PIE || m_uiGrpTypeKey == GROUP_TYPE_METER)
                {
                    bFoursquare = true;
                }

                qrcGrpBndRectCur = pItemGroup->moveHandleTo(m_ulDragHandle, local, qrcBondingRect, bFoursquare);*/

                qrcGrpBndRectCur = pItemGroup->moveHandleTo(m_ulDragHandle, local, qrcBondingRect);
                // If pressed "Ctrl", width = height when resize.
                if (mouseEvent->modifiers() == Qt::ControlModifier
                    || 1 == m_uiGrpTypeKey)
                {
                    qreal dHSize = 0.0, dWSize = 0.0;
                    qreal dHWFactor = 1.0, dDelta = 0.05;

                    if (1 == m_uiGrpTypeKey)
                    {
                        if (qrcBondingRect.width() > dDelta)
                        {
                            dHWFactor = qrcBondingRect.height() / qrcBondingRect.width();
                        }
                    }

                    if (m_eExpType & EXPD_HEIGHT)
                    {
                        dHSize = qrcGrpBndRectCur.height();
                        if (dHWFactor > dDelta)
                        {
                            dWSize = dHSize / dHWFactor;
                        }
                    }
                    else if (m_eExpType & EXPD_WIDTH)
                    {
                        dWSize = qrcGrpBndRectCur.width();
                        dHSize = dWSize * dHWFactor;
                    }

                    qrcGrpBndRectCur.setWidth(dWSize);
                    qrcGrpBndRectCur.setHeight(dHSize);

                }

                if (qFabs(qrcGrpBndRect.width()) <= 0 || qFabs(qrcGrpBndRect.height()) <= 0)
                {
                    break;
                }

                if(qrcGrpBndRectCur.width() <= MIN_ITEM_SIZE || qrcGrpBndRectCur.height() <= MIN_ITEM_SIZE)
                {
                    //m_ulDragHandle = 0;
                    //mouseEvent->setAccepted(true);
                    //pScene->views().first()->setCursor(Qt::ArrowCursor);
                    break;
                }

                dFactorW = qrcGrpBndRectCur.width() / qrcGrpBndRect.width();
                dFactorH = qrcGrpBndRectCur.height() / qrcGrpBndRect.height();

                qrcGrpBndRectCur = pItemGroup->mapRectFromScene(qrcGrpBndRectCur);
                pItemGroup->refreshTrackers(qrcGrpBndRectCur, pScene);
                eCrossType = pItemGroup->NormalizeDragedRect(qrcGrpBndRectCur);

                /* Avoid 0 size item issue when calculate the position */
                qreal dPenWidth = this->getMaxLinWidthInGrp(pItemGroup);
                if (dPenWidth > 0)
                {
                    dPenWidth = dPenWidth * 2;
                    if (qFabs(qrcGrpBndRectCur.height()) <= dPenWidth || qFabs(qrcGrpBndRectCur.width()) <= dPenWidth)
                    {
                        break;
                    }
                }
                else
                {
                    if (qFabs(qrcGrpBndRectCur.height()) <= dDelta || qFabs(qrcGrpBndRectCur.width() <= dDelta))
                    {
                        break;
                    }
                }

                this->moveGroupHandle(pItemGroup, qrcGrpBndRect, dFactorW, dFactorH, m_ulDragHandle);
                pScene->update();
                exchgDraghandle(eCrossType);
            }
            break;
         case SAM_DRAW_OBJECT_LINECIRCLE_NEW:  //add by tanghaiguo
             {
                 pLineCircleNew = dynamic_cast<QLineCircleBasicItem *> (pItem);
                 if (pLineCircleNew)
                 {
                     pLineCircleNew->itemSelectMouseMove(pScene, local);
                 }
                 pScene->update();
                 /*add by chengzhihua 增加防止曲线圆弧修改path后崩溃问题 begin*/
                 SamDrawScene *pDrawScene = dynamic_cast<SamDrawScene*> (pScene);
                 if(pDrawScene)
                 {
                     pDrawScene->selItemsChanged();
                 }
                 /*add by chengzhihua 增加防止曲线圆弧修改path后崩溃问题 end*/
            }
            break;
        /*Deal with text item expand event*/
        case SAM_DRAW_OBJECT_TEXT:
            pText = dynamic_cast<QSimpleTextItem *> (pItem);
            if (!pText)
            {
                break;
            }

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pText->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pText->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                qrcCurBondingRect = pText->moveHandleTo(m_ulDragHandle, local, qrcBondingRect, bFoursquare);
                qrcCurBondingRect = pText->mapRectFromScene(qrcCurBondingRect);
                eCrossType = pText->NormalizeDragedRect(qrcCurBondingRect);

                pText->setRect(qrcCurBondingRect);
                pText->refreshTrackers(qrcCurBondingRect, pScene);
                pScene->update();
                this->exchgDraghandle(eCrossType);
            }
            break;
        /*Deal with round rect item expand event*/
        case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
            pRoundedRectNew = dynamic_cast<QRoundedRectBasic *> (pItem);
            if (!pRoundedRectNew) break;

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pRoundedRectNew->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pRoundedRectNew->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                qrcCurBondingRect = pRoundedRectNew->moveHandleTo(m_ulDragHandle, local, qrcBondingRect, bFoursquare);

                /* Avoid 0 size item issue when calculate the position */
                int iPenWidth = pRoundedRectNew->GetLineWidth();
                if (iPenWidth > 0)
                {
                    iPenWidth = iPenWidth * 2;
                    if (qFabs(qrcCurBondingRect.height()) <= iPenWidth
                        || qFabs(qrcCurBondingRect.width()) <= iPenWidth)
                    {
                        break;
                    }
                }

                qrcCurBondingRect = pRoundedRectNew->mapRectFromScene(qrcCurBondingRect);
                eCrossType = pRoundedRectNew->NormalizeDragedRect(qrcCurBondingRect);
                pRoundedRectNew->setRectA(qrcCurBondingRect);
                pRoundedRectNew->refreshTrackers(qrcCurBondingRect, pScene);
                pScene->update();
                this->exchgDraghandle(eCrossType);
            }
            break;
        /*Deal with arc item expand event*/
        case SAM_DRAW_OBJECT_ARC_NEW:
            pArcNew = dynamic_cast<QArcBasicItem *> (pItem);
            if (!pArcNew) break;

            qrcBondingRect = pArcNew->getEllipseRect();
            qrcBondingRect = pArcNew->mapRectToScene(qrcBondingRect);

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pArcNew->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pArcNew->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                //pScene->views().first()->setCursor(pArc->getHandleCursor(m_ulDragHandle));
                qrcCurBondingRect = pArcNew->moveHandleTo(m_ulDragHandle, local, qrcBondingRect, true);
                if (qFabs(qrcCurBondingRect.width()) <= dDelta || qFabs(qrcCurBondingRect.height()) <= dDelta)
                {
                    pScene->update();
                    break;
                }

                QRectF rect = pArcNew->mapRectFromScene(qrcCurBondingRect);
                eCrossType = pArcNew->NormalizeDragedRect(rect); //
                pArcNew->setRectA(rect);
                pArcNew->refreshTrackers(qrcCurBondingRect, pScene);
                pScene->update();
                this->exchgDraghandle(eCrossType);
            }
            break;
////////////////////wxy add start
        case SAM_DRAW_OBJECT_RECT:
            pRect = dynamic_cast<QRectItem *> (pItem);
            if (!pRect)
            {
                break;
            }

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pRect->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pRect->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                //pScene->views().first()->setCursor(pRect->getHandleCursor(m_ulDragHandle));
                qrcCurBondingRect = pRect->moveHandleTo(m_ulDragHandle, local, qrcBondingRect, bFoursquare);
                qrcCurBondingRect = pRect->mapRectFromScene(qrcCurBondingRect);
                eCrossType = pRect->NormalizeDragedRect(qrcCurBondingRect);

                pRect->setRectA(qrcCurBondingRect);
                pScene->update();
                pRect->refreshTrackers(qrcCurBondingRect, pScene);
                this->exchgDraghandle(eCrossType);
            }
            break;
        case SAM_DRAW_OBJECT_ELIPSE:
            pElipse = dynamic_cast<QElipseItem *> (pItem);
            if (!pElipse)
            {
                break;
            }

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pElipse->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pElipse->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                //pScene->views().first()->setCursor(pElipse->getHandleCursor(m_ulDragHandle));
                qrcCurBondingRect = pElipse->moveHandleTo(m_ulDragHandle, local, qrcBondingRect, bFoursquare);
                /* Avoid 0 size item issue when calculate the position */
                int iPenWidth = pElipse->GetLineWidth();
                if (iPenWidth > 0)
                {
                    iPenWidth = iPenWidth * 2;
                    if (qFabs(qrcCurBondingRect.height()) <= iPenWidth
                        || qFabs(qrcCurBondingRect.width()) <= iPenWidth)
                    {
                        break;
                    }
                }

                qrcCurBondingRect = pElipse->mapRectFromScene(qrcCurBondingRect);
                //pElipse->refreshTrackers(qrcCurBondingRect);
                eCrossType = pElipse->NormalizeDragedRect(qrcCurBondingRect);

                pElipse->setRectA(qrcCurBondingRect);
                pScene->update();
                pElipse->refreshTrackers(qrcCurBondingRect, pScene);
                this->exchgDraghandle(eCrossType);
            }
            break;
        case SAM_DRAW_OBJECT_LINE:
            pLine = dynamic_cast<QLineItem *> (pItem);
            if (!pLine)
            {
                break;
            }

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pLine->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pLine->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                                pLine->setShiftMode(bShiftMode);
                pLine->moveHandleTo(m_ulDragHandle, local, qrcBondingRect);
                QPointF qpPoint = pLine->mapFromScene(local);
                pLine->movePathTrackers(m_ulDragHandle, qpPoint);
                                pLine->setShiftMode(false);
                pLine->refreshEndArrow();
                pScene->update();
            }
            break;
        case SAM_DRAW_OBJECT_POLYGON:
            pPolygon = dynamic_cast<QPolygonItem *> (pItem);
            if (!pPolygon)
            {
                break;
            }

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pPolygon->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pPolygon->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                pPolygon->moveHandleTo(m_ulDragHandle, local, qrcBondingRect);
                QPointF qpPoint = pPolygon->mapFromScene(local);
                pPolygon->movePolygonTrackers(m_ulDragHandle, qpPoint);
                pPolygon->setPattern(pPolygon->getPattern());
                pScene->update();
            }
            break;
        case SAM_DRAW_OBJECT_FOLDLINE:
            pFoldLine = dynamic_cast<QFoldLineItem *> (pItem);
            if (!pFoldLine)
            {
                break;
            }

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pFoldLine->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pFoldLine->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                pFoldLine->moveHandleTo(m_ulDragHandle, local, qrcBondingRect);
                QPointF qpPoint = pFoldLine->mapFromScene(local);
                pFoldLine->movePathTrackers(m_ulDragHandle, qpPoint);
                pFoldLine->refreshEndArrow();
                pScene->update();
            }
            break;
        case SAM_DRAW_OBJECT_FREELINE:
            pFreeLine = dynamic_cast<QFreeLineItem *> (pItem);
            if (!pFreeLine)
            {
                break;
            }

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pFreeLine->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pFreeLine->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                pFreeLine->moveHandleTo(m_ulDragHandle, local, qrcBondingRect);
                QPointF qpPoint = pFreeLine->mapFromScene(local);
                pFreeLine->movePathTrackers(m_ulDragHandle, qpPoint);
                pFreeLine->refreshEndArrow();
                pScene->update();
            }
            break;
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
            pRoundedRect = dynamic_cast<QRoundedRect *> (pItem);
            if (!pRoundedRect) break;

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pRoundedRect->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pRoundedRect->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                qrcCurBondingRect = pRoundedRect->moveHandleTo(m_ulDragHandle, local, qrcBondingRect, bFoursquare);

                /* Avoid 0 size item issue when calculate the position */
                int iPenWidth = pRoundedRect->GetLineWidth();
                if (iPenWidth > 0)
                {
                    iPenWidth = iPenWidth * 2;
                    if (qFabs(qrcCurBondingRect.height()) <= iPenWidth
                        || qFabs(qrcCurBondingRect.width()) <= iPenWidth)
                    {
                        break;
                    }
                }

                qrcCurBondingRect = pRoundedRect->mapRectFromScene(qrcCurBondingRect);
                eCrossType = pRoundedRect->NormalizeDragedRect(qrcCurBondingRect);
                pRoundedRect->setRectA(qrcCurBondingRect);
                pRoundedRect->refreshTrackers(qrcCurBondingRect, pScene);
                pScene->update();
                this->exchgDraghandle(eCrossType);
            }
            break;
        /*Deal with arc item expand event*/
        case SAM_DRAW_OBJECT_ARC:
            pArc = dynamic_cast<QArcItem *> (pItem);
            if (!pArc) break;

            qrcBondingRect = pArc->getEllipseRect();
            qrcBondingRect = pArc->mapRectToScene(qrcBondingRect);

            if (m_eSelectMode == SEL_MOD_NONE)
            {
                DragHandle = pArc->hitTest(local, qrcBondingRect, true);
                if (DragHandle > 0)
                {
                    pScene->views().first()->setCursor(pArc->getHandleCursor(DragHandle));
                }
                else
                {
                    pScene->views().first()->setCursor(Qt::ArrowCursor);
                }
            }

            if ((m_ulDragHandle > 0) && (m_eSelectMode == SEL_MOD_SIZE))
            {
                //pScene->views().first()->setCursor(pArc->getHandleCursor(m_ulDragHandle));
                qrcCurBondingRect = pArc->moveHandleTo(m_ulDragHandle, local, qrcBondingRect, true);
                if (qFabs(qrcCurBondingRect.width()) <= dDelta || qFabs(qrcCurBondingRect.height()) <= dDelta)
                {
                    pScene->update();
                    break;
                }

                QRectF rect = pArc->mapRectFromScene(qrcCurBondingRect);
                eCrossType = pArc->NormalizeDragedRect(rect); //
                pArc->setRectA(rect);
                pArc->refreshTrackers(qrcCurBondingRect, pScene);
                pScene->update();
                this->exchgDraghandle(eCrossType);
            }
            break;
         case SAM_DRAW_OBJECT_LINECIRCLE:  //add by tanghaiguo
             {
                 pLineCircle = dynamic_cast<QLineCircleItem *> (pItem);
                 if (pLineCircle)
                 {
                     pLineCircle->itemSelectMouseMove(pScene, local);
                 }
                 pScene->update();
                 /*add by chengzhihua 增加防止曲线圆弧修改path后崩溃问题 begin*/
                 SamDrawScene *pDrawScene = dynamic_cast<SamDrawScene*> (pScene);
                 if(pDrawScene)
                 {
                     pDrawScene->selItemsChanged();
                 }
                 /*add by chengzhihua 增加防止曲线圆弧修改path后崩溃问题 end*/
            }
            break;
////////////////////wxy add end
        default:
            break;
        }
    }

    /* Load the "SizeAllCursor" cursor while mouse moving on some a item */
    if (m_ulDragHandle <= 0 && m_eSelectMode == SEL_MOD_NONE)
    {
        QGraphicsItem *pItemAt = 0;
        QTransform qTrans = pScene->views().first()->transform();
        pItemAt = pScene->itemAt(local, qTrans);
        if (pItemAt && pItemAt->type() != SAM_DRAW_OBJECT_TRACKER  && SAM_DRAW_OBJECT_LINETRACKER != pItemAt->type())
        {
            pScene->views().first()->setCursor(Qt::SizeAllCursor);
        }
        else if (!pItemAt)
        {
            pScene->views().first()->setCursor(Qt::ArrowCursor);
        }
    }
    else if (SEL_MOD_MOVE == m_eSelectMode)
    {
        pScene->update();
    }
}

/*********************************************************************************
 * Function: resize the group by handle id
 * Parameters: scene pointer, handle id
 * Return: none
 ********************************************************************************/
void SamDrawSelectTool::moveGroupHandle(QItemGroup *pItemGroup, const QRectF &qrcGrpBndRect,
    const qreal &dFactorX, const qreal &dFactorY, unsigned long ulDragHdl)
{
    QRectItem *pRect     = 0;
    QElipseItem *pElipse = 0;
    QLineItem *pLine     = 0;
    QPolygonItem *pPolygon   = 0;
    QFoldLineItem *pFoldLine = 0;
    QFreeLineItem *pFreeLine = 0;
    QItemGroup *pGroup       = 0;
    QLineCircleItem *pLineCircle = 0;
    QSimpleTextItem *pText = 0;
    QPixmapItem *pPicItem = 0;
    QPixmapItem *pTmp = 0;
    QList<QPolygonF> polygonList;
    QRoundedRect *pRoundedRect = 0;
    QArcItem *pArcItem = 0;

    QRectBasicItem *pRectNew     = 0;
    QElipseBasicItem *pElipseNew = 0;
    QLineBasicItem *pLineNew     = 0;
    QPolygonBasicItem *pPolygonNew   = 0;
    QFoldLineBasicItem *pFoldLineNew = 0;
    QFreeLineBasicItem *pFreeLineNew = 0;
    QLineCircleBasicItem *pLineCircleNew = 0;
    QRoundedRectBasic *pRoundedRectNew = 0;
    QArcBasicItem *pArcItemNew = 0;

    if (NULL == pItemGroup)
    {
        return;
    }

    /* Move the group items and reset them to group */
    foreach (QGraphicsItem *pGrpItem, pItemGroup->childItems())
    {
        QRectF qrcItemBndRect = pGrpItem->sceneBoundingRect();
        if (pGrpItem->type() == SAM_DRAW_OBJECT_PIXMAP)
        {
            pTmp = dynamic_cast<QPixmapItem *> (pGrpItem);
            qrcItemBndRect = pTmp->boundRect;
        }
        else if (pGrpItem->type() == SAM_DRAW_OBJECT_ARC)
        {
            pArcItem = dynamic_cast<QArcItem *> (pGrpItem);
            if (NULL == pArcItem) continue;

            qrcItemBndRect = pArcItem->getEllipseRect();
            qrcItemBndRect = pArcItem->mapRectToScene(qrcItemBndRect);
        }
        else if (pGrpItem->type() == SAM_DRAW_OBJECT_ARC_NEW)////wxy add
        {
            pArcItemNew = dynamic_cast<QArcBasicItem *> (pGrpItem);
            if (NULL == pArcItemNew) continue;

            qrcItemBndRect = pArcItemNew->getEllipseRect();
            qrcItemBndRect = pArcItemNew->mapRectToScene(qrcItemBndRect);
        }
        qreal dw = qrcItemBndRect.width() * dFactorX;
        qreal dh = qrcItemBndRect.height() * dFactorY;
        SAM_DRAW_RECT_POINT_TYPE_E eRefPoint = SAM_DRAW_RECT_POINT_TYPE_BUTT;

        switch (ulDragHdl)
        {
        case SAM_DRAW_RECT_CENTER_RIGHT:
        case SAM_DRAW_RECT_BOTTOM_RIGHT:
        case SAM_DRAW_RECT_BOTTOM_CENTER: // ref 1
            eRefPoint = SAM_DRAW_RECT_TOP_LEFT;
            break;
        case SAM_DRAW_RECT_BOTTOM_LEFT:
        case SAM_DRAW_RECT_CENTER_LEFT:   // ref 3
            eRefPoint = SAM_DRAW_RECT_TOP_RIGHT;
            break;
        case SAM_DRAW_RECT_TOP_LEFT:
        case SAM_DRAW_RECT_TOP_CENTER:    // ref 5
            eRefPoint = SAM_DRAW_RECT_BOTTOM_RIGHT;
            break;
        case SAM_DRAW_RECT_TOP_RIGHT:     // ref 7
            eRefPoint = SAM_DRAW_RECT_BOTTOM_LEFT;
            break;
        default :
            break;
        }

        /* Get the item's new position */
        QPointF qpCurPos = coordTranslateInGrp(eRefPoint, qrcItemBndRect.topLeft(), qrcGrpBndRect, dFactorX, dFactorY);
        /* Move the item bonding rect to new position and set the new size */
        qrcItemBndRect.moveTo(qpCurPos);
        qrcItemBndRect.setWidth(dw);
        qrcItemBndRect.setHeight(dh);
        if (pGrpItem->type() != SAM_DRAW_OBJECT_PIXMAP)
        {
            qrcItemBndRect = pGrpItem->mapRectFromScene(qrcItemBndRect);
        }
        qrcItemBndRect = qrcItemBndRect.normalized();

        /* Reset the size of items in the group */
        switch (pGrpItem->type())
        {
        /* The item is rect */
        case SAM_DRAW_OBJECT_RECT:
            pRect = dynamic_cast<QRectItem *> (pGrpItem);
            if (pRect)
            {
                pRect->setRectA(qrcItemBndRect);
            }
            break;
        case SAM_DRAW_OBJECT_PIXMAP:
            pPicItem = dynamic_cast<QPixmapItem *> (pGrpItem);
            if (pPicItem)
            {
                pPicItem->SetRect(qrcItemBndRect);
            }
            break;
        /* The item is elipse */
        case SAM_DRAW_OBJECT_ELIPSE:
            pElipse = dynamic_cast<QElipseItem *> (pGrpItem);
            if (pElipse)
            {
                pElipse->setRectA(qrcItemBndRect);
            }
            break;
        /* The item is line */
        case SAM_DRAW_OBJECT_LINE:
            pLine = dynamic_cast<QLineItem *> (pGrpItem);
            if (pLine)
            {
                /*QLineF qlLine = pLine->line();
                QPointF qpP1 = qlLine.p1();
                QPointF qpP2 = qlLine.p2();
                qpP1 = pLine->mapToScene(qpP1);
                qpP2 = pLine->mapToScene(qpP2);
                qpP1 = coordTranslateInGrp(eRefPoint, qpP1, qrcGrpBndRect, dFactorX, dFactorY);
                qpP2 = coordTranslateInGrp(eRefPoint, qpP2, qrcGrpBndRect, dFactorX, dFactorY);
                qpP1 = pLine->mapFromScene(qpP1);
                qpP2 = pLine->mapFromScene(qpP2);
                pLine->setLine(qpP1.x(), qpP1.y(), qpP2.x(), qpP2.y());*/
                QPainterPath path = pLine->path();
                QList<QPolygonF> polygons = path.toSubpathPolygons();
                if (polygons.size() <= 0)
                {
                    break;
                }

                int iSize = polygons[0].size();
                for (int j = 0; j < iSize; j++)
                {
                    polygons[0][j] = pLine->mapToScene(polygons[0][j]);
                    polygons[0][j] = coordTranslateInGrp(eRefPoint, polygons[0][j], qrcGrpBndRect, dFactorX, dFactorY);
                    polygons[0][j] = pLine->mapFromScene(polygons[0][j]);
                    path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
                }
                pLine->setPath(path);
                pLine->refreshEndArrow();
            }
            break;
        /* The item is polygon */
        case SAM_DRAW_OBJECT_POLYGON:
            pPolygon = dynamic_cast<QPolygonItem *> (pGrpItem);
            if (pPolygon)
            {
                QPolygonF polygonPoints = pPolygon->polygon();
                for (int i = 0; i < polygonPoints.size(); i++)
                {
                    polygonPoints[i] = pPolygon->mapToScene(polygonPoints[i]);
                    polygonPoints[i] = coordTranslateInGrp(eRefPoint, polygonPoints[i], qrcGrpBndRect, dFactorX, dFactorY);
                    polygonPoints[i] = pPolygon->mapFromScene(polygonPoints[i]);
                }
                pPolygon->setPolygon(polygonPoints);
                pPolygon->setPattern(pPolygon->getPattern());
            }
            break;
        /* The item is fold line */
        case SAM_DRAW_OBJECT_FOLDLINE:
            pFoldLine = dynamic_cast<QFoldLineItem *> (pGrpItem);
            if (pFoldLine)
            {
                QPainterPath path = pFoldLine->path();
                QList<QPolygonF> polygons = path.toSubpathPolygons();
                if (polygons.size() <= 0)
                {
                    break;
                }

                int iSize = polygons[0].size();
                for (int j = 0; j < iSize; j++)
                {
                    polygons[0][j] = pFoldLine->mapToScene(polygons[0][j]);
                    polygons[0][j] = coordTranslateInGrp(eRefPoint, polygons[0][j], qrcGrpBndRect, dFactorX, dFactorY);
                    polygons[0][j] = pFoldLine->mapFromScene(polygons[0][j]);
                    path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
                }
                pFoldLine->setPath(path);
                pFoldLine->refreshEndArrow();
            }
            break;
        /* The item is free line */
        case SAM_DRAW_OBJECT_FREELINE:
            pFreeLine = dynamic_cast<QFreeLineItem *> (pGrpItem);
            if (pFreeLine)
            {
                QPainterPath path = pFreeLine->path();
                QList<QPolygonF> polygons = path.toSubpathPolygons();
                if (polygons.size() <= 0)
                {
                    break;
                }

                int iSize = polygons[0].size();
                for (int j = 0; j < iSize; j++)
                {
                    polygons[0][j] = pFreeLine->mapToScene(polygons[0][j]);
                    polygons[0][j] = coordTranslateInGrp(eRefPoint, polygons[0][j], qrcGrpBndRect, dFactorX, dFactorY);
                    polygons[0][j] = pFreeLine->mapFromScene(polygons[0][j]);
                    path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
                }
                pFreeLine->setPath(path);
                pFreeLine->refreshEndArrow();
            }
            break;
        /* The item is a arc/line circle */
        case SAM_DRAW_OBJECT_LINECIRCLE:
            pLineCircle = dynamic_cast<QLineCircleItem *> (pGrpItem);
            if (pLineCircle)
            {
                QPainterPath ipath = pLineCircle->path();
                polygonList = ipath.toSubpathPolygons();
                int iPolygonListSize = polygonList.size();
                if (pLineCircle->m_eLineEndArrowType != LINE_END_STYLE_NONE)
                {
                    iPolygonListSize--;
                }
                for (int i = 0; i < iPolygonListSize; i++)
                {
                    for (int j = 0; j < polygonList[i].size(); j++)
                    {
                        polygonList[i][j] = pLineCircle->mapToScene(polygonList[i][j]);
                        polygonList[i][j] = coordTranslateInGrp(eRefPoint, polygonList[i][j], qrcGrpBndRect, dFactorX, dFactorY);
                        polygonList[i][j] = pLineCircle->mapFromScene(polygonList[i][j]);
                    }
                }

                QPainterPath allPath;
                for(int i = 0; i < iPolygonListSize; i++)
                {
                    QPainterPath subPath = QPainterPath();
                    subPath.addPolygon(polygonList.at(i));
                    allPath.addPath(subPath);
                }
                pLineCircle->setPath(allPath);
                pLineCircle->refreshEndArrow();
            }
            break;
        /* The item is text */
        case SAM_DRAW_OBJECT_TEXT:
            pText = dynamic_cast<QSimpleTextItem *> (pGrpItem);
            if (pText)
            {
                pText->setRect(qrcItemBndRect);
            }
            break;
        /* The item is rounded rect */
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
            pRoundedRect = dynamic_cast<QRoundedRect *> (pGrpItem);
            if (pRoundedRect)
            {
                pRoundedRect->setRectA(qrcItemBndRect);
            }
            break;
        /* The item is rounded rect */
        case SAM_DRAW_OBJECT_ARC:
            pArcItem = dynamic_cast<QArcItem *> (pGrpItem);
            if (pArcItem)
            {
                pArcItem->setRectA(qrcItemBndRect);
            }
            break;
        /* The item is a group */
        case SAM_DRAW_OBJECT_GROUP:
            pGroup = dynamic_cast<QItemGroup *> (pGrpItem);
            if (pGroup)
            {
                /* Recursion for child group */
                QRectF rcRect = qrcGrpBndRect;
                moveGroupHandle(pGroup, rcRect, dFactorX, dFactorY, ulDragHdl);
            }
            break;
///////////////////wxy add start
        case SAM_DRAW_OBJECT_RECT_NEW:
            pRectNew = dynamic_cast<QRectBasicItem *> (pGrpItem);
            if (pRectNew)
            {
                pRectNew->setRectA(qrcItemBndRect);
            }
            break;
        case SAM_DRAW_OBJECT_ELIPSE_NEW:
            pElipseNew = dynamic_cast<QElipseBasicItem *> (pGrpItem);
            if (pElipseNew)
            {
                pElipseNew->setRectA(qrcItemBndRect);
            }
            break;
        case SAM_DRAW_OBJECT_LINE_NEW:
            pLineNew = dynamic_cast<QLineBasicItem *> (pGrpItem);
            if (pLineNew)
            {
                QPainterPath path = pLineNew->path();
                QList<QPolygonF> polygons = path.toSubpathPolygons();
                if (polygons.size() <= 0)
                {
                    break;
                }

                int iSize = polygons[0].size();
                for (int j = 0; j < iSize; j++)
                {
                    polygons[0][j] = pLineNew->mapToScene(polygons[0][j]);
                    polygons[0][j] = coordTranslateInGrp(eRefPoint, polygons[0][j], qrcGrpBndRect, dFactorX, dFactorY);
                    polygons[0][j] = pLineNew->mapFromScene(polygons[0][j]);
                    path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
                }
                pLineNew->setPath(path);
                pLineNew->refreshEndArrow();
            }
            break;
        case SAM_DRAW_OBJECT_POLYGON_NEW:
            pPolygonNew = dynamic_cast<QPolygonBasicItem *> (pGrpItem);
            if (pPolygonNew)
            {
                QPolygonF polygonPoints = pPolygonNew->polygon();
                for (int i = 0; i < polygonPoints.size(); i++)
                {
                    polygonPoints[i] = pPolygonNew->mapToScene(polygonPoints[i]);
                    polygonPoints[i] = coordTranslateInGrp(eRefPoint, polygonPoints[i], qrcGrpBndRect, dFactorX, dFactorY);
                    polygonPoints[i] = pPolygonNew->mapFromScene(polygonPoints[i]);
                }
                pPolygonNew->setPolygon(polygonPoints);
                pPolygonNew->setPattern(pPolygonNew->getPattern());
            }
            break;
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:
            pFoldLineNew = dynamic_cast<QFoldLineBasicItem *> (pGrpItem);
            if (pFoldLineNew)
            {
                QPainterPath path = pFoldLineNew->path();
                QList<QPolygonF> polygons = path.toSubpathPolygons();
                if (polygons.size() <= 0)
                {
                    break;
                }

                int iSize = polygons[0].size();
                for (int j = 0; j < iSize; j++)
                {
                    polygons[0][j] = pFoldLineNew->mapToScene(polygons[0][j]);
                    polygons[0][j] = coordTranslateInGrp(eRefPoint, polygons[0][j], qrcGrpBndRect, dFactorX, dFactorY);
                    polygons[0][j] = pFoldLineNew->mapFromScene(polygons[0][j]);
                    path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
                }
                pFoldLineNew->setPath(path);
                pFoldLineNew->refreshEndArrow();
            }
            break;
        case SAM_DRAW_OBJECT_FREELINE_NEW:
            pFreeLineNew = dynamic_cast<QFreeLineBasicItem *> (pGrpItem);
            if (pFreeLineNew)
            {
                QPainterPath path = pFreeLineNew->path();
                QList<QPolygonF> polygons = path.toSubpathPolygons();
                if (polygons.size() <= 0)
                {
                    break;
                }

                int iSize = polygons[0].size();
                for (int j = 0; j < iSize; j++)
                {
                    polygons[0][j] = pFreeLineNew->mapToScene(polygons[0][j]);
                    polygons[0][j] = coordTranslateInGrp(eRefPoint, polygons[0][j], qrcGrpBndRect, dFactorX, dFactorY);
                    polygons[0][j] = pFreeLineNew->mapFromScene(polygons[0][j]);
                    path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
                }
                pFreeLineNew->setPath(path);
                pFreeLineNew->refreshEndArrow();
            }
            break;
        case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
            pLineCircleNew = dynamic_cast<QLineCircleBasicItem *> (pGrpItem);
            if (pLineCircleNew)
            {
                QPainterPath ipath = pLineCircleNew->path();
                polygonList = ipath.toSubpathPolygons();
                int iPolygonListSize = polygonList.size();
                if (pLineCircleNew->m_eLineEndArrowType != LINE_END_STYLE_NONE)
                {
                    iPolygonListSize--;
                }
                for (int i = 0; i < iPolygonListSize; i++)
                {
                    for (int j = 0; j < polygonList[i].size(); j++)
                    {
                        polygonList[i][j] = pLineCircleNew->mapToScene(polygonList[i][j]);
                        polygonList[i][j] = coordTranslateInGrp(eRefPoint, polygonList[i][j], qrcGrpBndRect, dFactorX, dFactorY);
                        polygonList[i][j] = pLineCircleNew->mapFromScene(polygonList[i][j]);
                    }
                }

                QPainterPath allPath;
                for(int i = 0; i < iPolygonListSize; i++)
                {
                    QPainterPath subPath = QPainterPath();
                    subPath.addPolygon(polygonList.at(i));
                    allPath.addPath(subPath);
                }
                pLineCircleNew->setPath(allPath);
                pLineCircleNew->refreshEndArrow();
            }
            break;
        case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
            pRoundedRectNew = dynamic_cast<QRoundedRectBasic *> (pGrpItem);
            if (pRoundedRectNew)
            {
                pRoundedRectNew->setRectA(qrcItemBndRect);
            }
            break;
        case SAM_DRAW_OBJECT_ARC_NEW:
            pArcItemNew = dynamic_cast<QArcBasicItem *> (pGrpItem);
            if (pArcItemNew)
            {
                pArcItemNew->setRectA(qrcItemBndRect);
            }
            break;
///////////////////wxy add end
        default:
            break;
        }

        /* Refresh this item in group */
        if (pGrpItem)
        {
            pItemGroup->removeFromGroup(pGrpItem);
            pItemGroup->addToGroup(pGrpItem);
        }
    }
}

/*********************************************************************************
 * Function: selection mouse release event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawSelectTool::mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    //add by tanghaiguo
    if(mouseEvent->button() == Qt::LeftButton)
    {
        QList<QGraphicsItem *> sceneList = pScene->selectedItems();
        if(sceneList.size() == 1)
        {
            QLineCircleItem *pLineCircle = dynamic_cast<QLineCircleItem *>(sceneList.first());
            if(pLineCircle)
            {
                pLineCircle->itemSelectMouseRelease();
            }
        }
    }
    //end of add by tanghaiguo

    m_eSelectMode = SEL_MOD_NONE;
    m_ulDragHandle = 0;
    pScene->views().first()->setCursor(Qt::ArrowCursor);
}

/*********************************************************************************
 * Function: selection mouse duble click event
 * Parameters: scene pointer, mounse event
 * Return: none
 ********************************************************************************/
void SamDrawSelectTool::mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    QPointF qpClickedPt = mouseEvent->scenePos();
    QGraphicsItem *pItem = pScene->itemAt(qpClickedPt);
    if (mouseEvent->modifiers() == Qt::ShiftModifier)
    {
        if (pItem != NULL)
        {
            if (!pItem->isSelected())
                pItem->setSelected(true);
        }
    }
}

/*********************************************************************************
 * Function: exchange drag handle when draged rect item, while
 *           cross right <-> left or top <-> bottom or all
 * Parameters: cross type
 * Return: none
 ********************************************************************************/
void SamDrawSelectTool::exchgDraghandle(DRAG_CROSS_TYPE_E eCrossType)
{
    switch(eCrossType)
    {
    case DRAG_CROSS_LEFT_RIGHT:
        switch(m_ulDragHandle)
        {
        case SAM_DRAW_RECT_TOP_LEFT:
            m_ulDragHandle = SAM_DRAW_RECT_TOP_RIGHT;
            break;
        case SAM_DRAW_RECT_TOP_RIGHT:
            m_ulDragHandle = SAM_DRAW_RECT_TOP_LEFT;
            break;
        case SAM_DRAW_RECT_BOTTOM_RIGHT:
            m_ulDragHandle = SAM_DRAW_RECT_BOTTOM_LEFT;
            break;
        case SAM_DRAW_RECT_BOTTOM_LEFT:
            m_ulDragHandle = SAM_DRAW_RECT_BOTTOM_RIGHT;
            break;
        case SAM_DRAW_RECT_CENTER_RIGHT:
            m_ulDragHandle = SAM_DRAW_RECT_CENTER_LEFT;
            break;
        case SAM_DRAW_RECT_CENTER_LEFT:
            m_ulDragHandle = SAM_DRAW_RECT_CENTER_RIGHT;
            break;
        default:
            break;
        }
        break;
    case DRAG_CROSS_TOP_BOTTON:
        switch(m_ulDragHandle)
        {
        case SAM_DRAW_RECT_TOP_LEFT:
            m_ulDragHandle = SAM_DRAW_RECT_BOTTOM_LEFT;
            break;
        case SAM_DRAW_RECT_BOTTOM_LEFT:
            m_ulDragHandle = SAM_DRAW_RECT_TOP_LEFT;
            break;
        case SAM_DRAW_RECT_TOP_RIGHT:
            m_ulDragHandle = SAM_DRAW_RECT_BOTTOM_RIGHT;
            break;
        case SAM_DRAW_RECT_BOTTOM_RIGHT:
            m_ulDragHandle = SAM_DRAW_RECT_TOP_RIGHT;
            break;
        case SAM_DRAW_RECT_TOP_CENTER:
            m_ulDragHandle = SAM_DRAW_RECT_BOTTOM_CENTER;
            break;
        case SAM_DRAW_RECT_BOTTOM_CENTER:
            m_ulDragHandle = SAM_DRAW_RECT_TOP_CENTER;
            break;
        default:
            break;
        }
        break;
    case DRAG_CROSS_ALL:
        switch (m_ulDragHandle)
        {
        case SAM_DRAW_RECT_TOP_RIGHT:
            m_ulDragHandle = SAM_DRAW_RECT_BOTTOM_LEFT;
            break;
        case SAM_DRAW_RECT_BOTTOM_LEFT:
            m_ulDragHandle = SAM_DRAW_RECT_TOP_RIGHT;
            break;
        case SAM_DRAW_RECT_BOTTOM_RIGHT:
            m_ulDragHandle = SAM_DRAW_RECT_TOP_LEFT;
            break;
        case SAM_DRAW_RECT_TOP_LEFT:
            m_ulDragHandle = SAM_DRAW_RECT_BOTTOM_RIGHT;
            break;
        case SAM_DRAW_RECT_TOP_CENTER:
            m_ulDragHandle = SAM_DRAW_RECT_BOTTOM_CENTER;
            break;
        case SAM_DRAW_RECT_CENTER_RIGHT:
            m_ulDragHandle = SAM_DRAW_RECT_CENTER_LEFT;
            break;
        case SAM_DRAW_RECT_BOTTOM_CENTER:
            m_ulDragHandle = SAM_DRAW_RECT_TOP_CENTER;
            break;
        case SAM_DRAW_RECT_CENTER_LEFT:
            m_ulDragHandle = SAM_DRAW_RECT_CENTER_RIGHT;
            break;
        default :
            break;
        }
        break;
    default:
        break;
    }
}

/*********************************************************************************
 * Function: set the selected items same width with the leftmost one (add by bruce nie)
 * Parameters: none
 * Return: item
 ********************************************************************************/
void SamDrawSelectTool::setSelSameWidth(QGraphicsScene *pScene)
{
    this->adjustObjectSize(ADJUST_OBJ_WIDTH, pScene);
}

/*********************************************************************************
 * Function: set the selected items same height with the leftmost one (add by bruce nie)
 * Parameters: none
 * Return: item
 ********************************************************************************/
void SamDrawSelectTool::setSelSameheight(QGraphicsScene *pScene)
{
    this->adjustObjectSize(ADJUST_OBJ_HEIGHT, pScene);
}

/*********************************************************************************
 * Function: set the selected items same width/height with the leftmost one (add by bruce nie)
 * Parameters: none
 * Return: item
 ********************************************************************************/
void SamDrawSelectTool::setSelSameWidthHeight(QGraphicsScene *pScene)
{
    this->adjustObjectSize(ADJUST_OBJ_WIDTH_HEIGHT, pScene);
}

/*********************************************************************************
 * Function: get the leftmost item from the selected items (add by bruce nie)
 * Parameters: none
 * Return: item
 ********************************************************************************/
QGraphicsItem *SamDrawSelectTool::getTheLeftmostItem(QGraphicsScene *pScene)
{
    QList<QGraphicsItem *> selectedlist;
    QGraphicsItem *pItem = 0;
    QGraphicsItem *pLeftmostItem = 0;
    int iCnt = 0;
    qreal dLeftXCoord = 0;

    if (!pScene)
    {
        return NULL;
    }

    selectedlist.clear();
    selectedlist = pScene->selectedItems(); //all selected items
    iCnt = selectedlist.size();
    if (iCnt < 2 )
    {
        return NULL;
    }

    pLeftmostItem = selectedlist.at(0);
    dLeftXCoord = pLeftmostItem->sceneBoundingRect().left() + pLeftmostItem->scenePos().x();
    /*Find the leftmost object*/
    for(int i = 0; i < iCnt; i++)
    {
        pItem = selectedlist.at(i);
        if (dLeftXCoord > (pItem->sceneBoundingRect().left() + pItem->scenePos().x()))
        {
            dLeftXCoord = pItem->sceneBoundingRect().left() + pItem->scenePos().x();
            pLeftmostItem = pItem;
        }
    }

    return pLeftmostItem;
}

/*********************************************************************************
 * Function: adjust the selected items' size according to eAdjustType (add by bruce nie)
 * Parameters: adjust type
 * Return: none
 ********************************************************************************/
void SamDrawSelectTool::adjustObjectSize(ADJUST_OBJ_SIZE_TYPE_E eAdjustType, QGraphicsScene *pScene)
{
    qreal dStdW = 0.0, dW = 0.0, dStdH = 0.0, dH = 0.0;
    /*X/Y factor*/
    qreal dXFactor = 1.0, dYFactor = 1.0;
    QGraphicsItem *pSelItem = 0;
    unsigned char ucWFlag = 0, ucHFlag = 0;
    QRectBasicItem *pRectNew       = NULL;
    QElipseBasicItem *pElipseNew   = NULL;
    QLineBasicItem *pLineNew       = NULL;
    QPolygonBasicItem *pPolygonNew   = NULL;
    QFoldLineBasicItem *pFoldLineNew = NULL;
    QFreeLineBasicItem *pFreeLineNew = NULL;
    QItemGroup *pItemGroup   = NULL;
    QLineCircleBasicItem *pLineCircleNew = 0;
    QSimpleTextItem *pText = NULL;
    QRoundedRectBasic *pRoundedRectNew = NULL;
    QArcBasicItem *pArcItemNew = NULL;

    QRectItem *pRect       = NULL;
    QElipseItem *pElipse   = NULL;
    QLineItem *pLine       = NULL;
    QPolygonItem *pPolygon   = NULL;
    QFoldLineItem *pFoldLine = NULL;
    QFreeLineItem *pFreeLine = NULL;
    QLineCircleItem *pLineCircle = 0;
    QRoundedRect *pRoundedRect = NULL;
    QArcItem *pArcItem = NULL;

    QList<QPolygonF> polygonList;
    QRectF qrcBndRect, qrcSetRect;

    SamDrawScene *pSene = dynamic_cast<SamDrawScene *> (pScene);
    QGraphicsItem *pSelectedItem = NULL;
    foreach(QGraphicsItem *pItem,pSene->selectedItems())
    {
        if(pSene->GetSelectFlag(pItem))
        {
            pSelectedItem = pItem;
        }
    }

    QGraphicsItem *pLeftmostItem = NULL;
    if(pSelectedItem)
    {
        pLeftmostItem = pSelectedItem;
    }
    else
    {
        pLeftmostItem = this->getTheLeftmostItem(pScene);
    }
    if (NULL == pLeftmostItem)
    {
        return;
    }

    ucWFlag = (unsigned char)eAdjustType & 0x0F;
    ucHFlag = (unsigned char)eAdjustType & 0xF0;
    ucHFlag = ucHFlag >> 4;

    /*Get the leftmost item's width*/
    dStdW = pLeftmostItem->sceneBoundingRect().width();
    dStdH = pLeftmostItem->sceneBoundingRect().height();

    int iSize = pScene->selectedItems().size();
    for(int i = 0; i < iSize; i++)
    {
        pSelItem = pScene->selectedItems().at(i);
        if(!(pSelItem->flags() & QGraphicsItem::ItemIsMovable))
        {
            continue;
        }
        qrcBndRect = pSelItem->sceneBoundingRect();
        dW = qrcBndRect.width();
        dH = qrcBndRect.height();
        /*Get the factor*/
        if ((dW <= 0) || (dH <= 0))
        {
            continue;
        }
        dXFactor = dStdW / dW;
        dYFactor = dStdH / dH;

        dXFactor = dXFactor * ucWFlag;
        dYFactor = dYFactor * ucHFlag;
        if (dXFactor <= 0) dXFactor = 1.0;
        if (dYFactor <= 0) dYFactor = 1.0;

        switch (pSelItem->type())
        {
        case SAM_DRAW_OBJECT_RECT_NEW:
            pRectNew = dynamic_cast<QRectBasicItem *> (pSelItem);
            if (!pRectNew)
            {
                break;
            }
            qrcSetRect = qrcBndRect;
            qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
            qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
            qrcSetRect = pRectNew->mapRectFromScene(qrcSetRect);
            pRectNew->setRectA(qrcSetRect);
            break;
        case SAM_DRAW_OBJECT_ELIPSE_NEW:
            pElipseNew = dynamic_cast<QElipseBasicItem *> (pSelItem);
            if (!pElipseNew)
            {
                break;
            }
            qrcSetRect = qrcBndRect;
            qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
            qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
            qrcSetRect = pElipseNew->mapRectFromScene(qrcSetRect);
            pElipseNew->setRect(qrcSetRect);
            break;
        case SAM_DRAW_OBJECT_LINE_NEW:
            pLineNew = dynamic_cast<QLineBasicItem *> (pSelItem);
            if (pLineNew)
            {
                QPainterPath path = pLineNew->path();
                QList<QPolygonF> polygons = path.toSubpathPolygons();
                if (polygons.size() <= 0)
                {
                    break;
                }

                int iSize = polygons[0].size();
                for (int j = 0; j < iSize; j++)
                {
                    polygons[0][j] = pLineNew->mapToScene(polygons[0][j]);
                    polygons[0][j] = coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                    polygons[0][j] = pLineNew->mapFromScene(polygons[0][j]);
                    path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
                }
                pLineNew->setPath(path);
                pLineNew->refreshEndArrow();
            }
            break;
        case SAM_DRAW_OBJECT_POLYGON_NEW:
            pPolygonNew = dynamic_cast<QPolygonBasicItem *> (pSelItem);
            if (pPolygonNew)
            {
                QPolygonF polygonPoints = pPolygonNew->polygon();
                for (int i = 0; i < polygonPoints.size(); i++)
                {
                    polygonPoints[i] = pPolygonNew->mapToScene(polygonPoints[i]);
                    polygonPoints[i] = coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygonPoints[i], qrcBndRect, dXFactor, dYFactor);
                    polygonPoints[i] = pPolygonNew->mapFromScene(polygonPoints[i]);
                }
                pPolygonNew->setPolygon(polygonPoints);
            }
            break;
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:
            pFoldLineNew = dynamic_cast<QFoldLineBasicItem *> (pSelItem);
            if (pFoldLineNew)
            {
                QPainterPath path = pFoldLineNew->path();
                QList<QPolygonF> polygons = path.toSubpathPolygons();
                if (polygons.size() <= 0)
                {
                    break;
                }

                int iSize = polygons[0].size();
                for (int j = 0; j < iSize; j++)
                {
                    polygons[0][j] = pFoldLineNew->mapToScene(polygons[0][j]);
                    polygons[0][j] = coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                    polygons[0][j] = pFoldLineNew->mapFromScene(polygons[0][j]);
                    path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
                }
                pFoldLineNew->setPath(path);
                pFoldLineNew->refreshEndArrow();
            }
            break;
        case SAM_DRAW_OBJECT_FREELINE_NEW:
            pFreeLineNew = dynamic_cast<QFreeLineBasicItem *> (pSelItem);
            if (pFreeLineNew)
            {
                QPainterPath path = pFreeLineNew->path();
                QList<QPolygonF> polygons = path.toSubpathPolygons();
                if (polygons.size() <= 0)
                {
                    break;
                }

                int iSize = polygons[0].size();
                for (int j = 0; j < iSize; j++)
                {
                    polygons[0][j] = pFreeLineNew->mapToScene(polygons[0][j]);
                    polygons[0][j] = coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                    polygons[0][j] = pFreeLineNew->mapFromScene(polygons[0][j]);
                    path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
                }
                pFreeLineNew->setPath(path);
                pFreeLineNew->refreshEndArrow();
            }
            break;
        case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
            pLineCircleNew= dynamic_cast<QLineCircleBasicItem *> (pSelItem);
            if (pLineCircleNew)
            {
                QPainterPath ipath = pLineCircleNew->path();
                polygonList = ipath.toSubpathPolygons();
                int iPolygonListSize = polygonList.size();
                if (pLineCircleNew->m_eLineEndArrowType != LINE_END_STYLE_NONE)
                {
                    iPolygonListSize--;
                }
                for (int i = 0; i < iPolygonListSize; i++)
                {
                    for (int j = 0; j < polygonList[i].size(); j++)
                    {
                        polygonList[i][j] = pLineCircleNew->mapToScene(polygonList[i][j]);
                        polygonList[i][j] = coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygonList[i][j], qrcBndRect, dXFactor, dYFactor);
                        polygonList[i][j] = pLineCircleNew->mapFromScene(polygonList[i][j]);
                    }
                }

                QPainterPath allPath;
                for(int i = 0; i < iPolygonListSize; i++)
                {
                    QPainterPath subPath = QPainterPath();
                    subPath.addPolygon(polygonList.at(i));
                    allPath.addPath(subPath);
                }
                pLineCircleNew->setPath(allPath);
                pLineCircleNew->refreshEndArrow();
            }
            break;
        case SAM_DRAW_OBJECT_TEXT:
            pText = dynamic_cast<QSimpleTextItem *> (pSelItem);
            if (pText)
            {
                qrcSetRect = qrcBndRect;
                qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
                qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
                qrcSetRect = pText->mapRectFromScene(qrcSetRect);
                pText->setRect(qrcSetRect);
            }
            break;
        case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
            pRoundedRectNew = dynamic_cast<QRoundedRectBasic *> (pSelItem);
            if (pRoundedRectNew)
            {
                qrcSetRect = qrcBndRect;
                qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
                qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
                qrcSetRect = pRoundedRectNew->mapRectFromScene(qrcSetRect);
                pRoundedRectNew->setRectA(qrcSetRect);
            }
            break;
        case SAM_DRAW_OBJECT_ARC_NEW:
            pArcItemNew = dynamic_cast<QArcBasicItem *> (pSelItem);
            if (pArcItemNew)
            {
                qrcSetRect = pArcItemNew->getEllipseRect();
                qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
                qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
                pArcItemNew->setRectA(qrcSetRect);
            }
            break;
        case SAM_DRAW_OBJECT_GROUP:
            pItemGroup = dynamic_cast<QItemGroup *> (pSelItem);
            if(pItemGroup == NULL)
            {
                break;
            }
            this->moveGroupHandle(pItemGroup, qrcBndRect, dXFactor, dYFactor, (unsigned long)SAM_DRAW_RECT_BOTTOM_RIGHT);
            break;

/////////////wxy add start
        case SAM_DRAW_OBJECT_RECT:
            pRect = dynamic_cast<QRectItem *> (pSelItem);
            if (!pRect)
            {
                break;
            }
            qrcSetRect = qrcBndRect;
            qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
            qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
            qrcSetRect = pRect->mapRectFromScene(qrcSetRect);
            pRect->setRectA(qrcSetRect);
            break;
        case SAM_DRAW_OBJECT_ELIPSE:
            pElipse = dynamic_cast<QElipseItem *> (pSelItem);
            if (!pElipse)
            {
                break;
            }
            qrcSetRect = qrcBndRect;
            qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
            qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
            qrcSetRect = pElipse->mapRectFromScene(qrcSetRect);
            pElipse->setRect(qrcSetRect);
            break;
        case SAM_DRAW_OBJECT_LINE:
            pLine = dynamic_cast<QLineItem *> (pSelItem);
            if (pLine)
            {
                QPainterPath path = pLine->path();
                QList<QPolygonF> polygons = path.toSubpathPolygons();
                if (polygons.size() <= 0)
                {
                    break;
                }

                int iSize = polygons[0].size();
                for (int j = 0; j < iSize; j++)
                {
                    polygons[0][j] = pLine->mapToScene(polygons[0][j]);
                    polygons[0][j] = coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                    polygons[0][j] = pLine->mapFromScene(polygons[0][j]);
                    path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
                }
                pLine->setPath(path);
                pLine->refreshEndArrow();
            }
            break;
        case SAM_DRAW_OBJECT_POLYGON:
            pPolygon = dynamic_cast<QPolygonItem *> (pSelItem);
            if (pPolygon)
            {
                QPolygonF polygonPoints = pPolygon->polygon();
                for (int i = 0; i < polygonPoints.size(); i++)
                {
                    polygonPoints[i] = pPolygon->mapToScene(polygonPoints[i]);
                    polygonPoints[i] = coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygonPoints[i], qrcBndRect, dXFactor, dYFactor);
                    polygonPoints[i] = pPolygon->mapFromScene(polygonPoints[i]);
                }
                pPolygon->setPolygon(polygonPoints);
            }
            break;
        case SAM_DRAW_OBJECT_FOLDLINE:
            pFoldLine = dynamic_cast<QFoldLineItem *> (pSelItem);
            if (pFoldLine)
            {
                QPainterPath path = pFoldLine->path();
                QList<QPolygonF> polygons = path.toSubpathPolygons();
                if (polygons.size() <= 0)
                {
                    break;
                }

                int iSize = polygons[0].size();
                for (int j = 0; j < iSize; j++)
                {
                    polygons[0][j] = pFoldLine->mapToScene(polygons[0][j]);
                    polygons[0][j] = coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                    polygons[0][j] = pFoldLine->mapFromScene(polygons[0][j]);
                    path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
                }
                pFoldLine->setPath(path);
                pFoldLine->refreshEndArrow();
            }
            break;
        case SAM_DRAW_OBJECT_FREELINE:
            pFreeLine = dynamic_cast<QFreeLineItem *> (pSelItem);
            if (pFreeLine)
            {
                QPainterPath path = pFreeLine->path();
                QList<QPolygonF> polygons = path.toSubpathPolygons();
                if (polygons.size() <= 0)
                {
                    break;
                }

                int iSize = polygons[0].size();
                for (int j = 0; j < iSize; j++)
                {
                    polygons[0][j] = pFreeLine->mapToScene(polygons[0][j]);
                    polygons[0][j] = coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                    polygons[0][j] = pFreeLine->mapFromScene(polygons[0][j]);
                    path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
                }
                pFreeLine->setPath(path);
                pFreeLine->refreshEndArrow();
            }
            break;
        case SAM_DRAW_OBJECT_LINECIRCLE:
            pLineCircle = dynamic_cast<QLineCircleItem *> (pSelItem);
            if (pLineCircle)
            {
                QPainterPath ipath = pLineCircle->path();
                polygonList = ipath.toSubpathPolygons();
                int iPolygonListSize = polygonList.size();
                if (pLineCircle->m_eLineEndArrowType != LINE_END_STYLE_NONE)
                {
                    iPolygonListSize--;
                }
                for (int i = 0; i < iPolygonListSize; i++)
                {
                    for (int j = 0; j < polygonList[i].size(); j++)
                    {
                        polygonList[i][j] = pLineCircle->mapToScene(polygonList[i][j]);
                        polygonList[i][j] = coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygonList[i][j], qrcBndRect, dXFactor, dYFactor);
                        polygonList[i][j] = pLineCircle->mapFromScene(polygonList[i][j]);
                    }
                }

                QPainterPath allPath;
                for(int i = 0; i < iPolygonListSize; i++)
                {
                    QPainterPath subPath = QPainterPath();
                    subPath.addPolygon(polygonList.at(i));
                    allPath.addPath(subPath);
                }
                pLineCircle->setPath(allPath);
                pLineCircle->refreshEndArrow();
            }
            break;
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
            pRoundedRect = dynamic_cast<QRoundedRect *> (pSelItem);
            if (pRoundedRect)
            {
                qrcSetRect = qrcBndRect;
                qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
                qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
                qrcSetRect = pRoundedRect->mapRectFromScene(qrcSetRect);
                pRoundedRect->setRectA(qrcSetRect);
            }
            break;
        case SAM_DRAW_OBJECT_ARC:
            pArcItem = dynamic_cast<QArcItem *> (pSelItem);
            if (pArcItem)
            {
                qrcSetRect = pArcItem->getEllipseRect();
                qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
                qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
                pArcItem->setRectA(qrcSetRect);
            }
            break;
/////////////wxy add end
        default :
            break;
        }
    }
}

/*********************************************************************************
 * Function: Get the max penwidth in group.
 * Parameters: group pointer
 * Return: the max penwidth.
 ********************************************************************************/
qreal SamDrawSelectTool::getMaxLinWidthInGrp(QItemGroup *pGrp)
{
    qreal dMaxPenWidth = 0.0;
    qreal dCurPenWidth = 0.0;
    QRectItem *pRect       = NULL;
    QElipseItem *pElipse   = NULL;
    QLineItem *pLine       = NULL;
    QPolygonItem *pPolygon   = NULL;
    QFoldLineItem *pFoldLine = NULL;
    QFreeLineItem *pFreeLine = NULL;
    QLineCircleItem *pLineCircle = NULL;
    QRoundedRect *pRoundedRect   = NULL;
    QArcItem *pArcItem           = NULL;

    QRectBasicItem *pRectNew       = NULL;
    QElipseBasicItem *pElipseNew   = NULL;
    QLineBasicItem *pLineNew       = NULL;
    QPolygonBasicItem *pPolygonNew   = NULL;
    QFoldLineBasicItem *pFoldLineNew = NULL;
    QFreeLineBasicItem *pFreeLineNew = NULL;
    QLineCircleBasicItem *pLineCircleNew = NULL;
    QRoundedRectBasic *pRoundedRectNew   = NULL;
    QArcBasicItem *pArcItemNew           = NULL;

    if (NULL == pGrp) return dMaxPenWidth;

    QList<QGraphicsItem *> qlstItems = pGrp->childItems();
    int iSize = qlstItems.size();

    for (int i = 0; i < iSize; i++)
    {
        QGraphicsItem *pItem = qlstItems.at(i);
        switch (pItem->type())
        {
        case SAM_DRAW_OBJECT_RECT:
            {
                pRect = dynamic_cast<QRectItem *> (pItem);
                if (pRect)
                {
                    dCurPenWidth = pRect->GetLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_ELIPSE:
            {
                pElipse = dynamic_cast<QElipseItem *> (pItem);
                if (pElipse)
                {
                    dCurPenWidth = pElipse->GetLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINE:
            {
                pLine = dynamic_cast<QLineItem *> (pItem);
                if (pLine)
                {
                    dCurPenWidth = pLine->getLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_POLYGON:
            {
                pPolygon = dynamic_cast<QPolygonItem *> (pItem);
                if (pPolygon)
                {
                    dCurPenWidth = pPolygon->getLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_FOLDLINE:
            {
                pFoldLine = dynamic_cast<QFoldLineItem *> (pItem);
                if (pFoldLine)
                {
                    dCurPenWidth = pFoldLine->getLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_FREELINE:
            {
                pFreeLine = dynamic_cast<QFreeLineItem *> (pItem);
                if (pFreeLine)
                {
                    dCurPenWidth = pFreeLine->getLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINECIRCLE:
            {
                pLineCircle = dynamic_cast<QLineCircleItem *> (pItem);
                if (pLineCircle)
                {
                    dCurPenWidth = pLineCircle->getLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
            {
                pRoundedRect = dynamic_cast<QRoundedRect *> (pItem);
                if (pRoundedRect)
                {
                    dCurPenWidth = pRoundedRect->GetLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_ARC:
            {
                pArcItem = dynamic_cast<QArcItem *> (pItem);
                if (pArcItem)
                {
                    dCurPenWidth = pArcItem->GetLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
//////////////////wxy add start
        case SAM_DRAW_OBJECT_RECT_NEW:
            {
                pRectNew = dynamic_cast<QRectBasicItem *> (pItem);
                if (pRectNew)
                {
                    dCurPenWidth = pRectNew->GetLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_ELIPSE_NEW:
            {
                pElipseNew = dynamic_cast<QElipseBasicItem *> (pItem);
                if (pElipseNew)
                {
                    dCurPenWidth = pElipseNew->GetLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINE_NEW:
            {
                pLineNew = dynamic_cast<QLineBasicItem *> (pItem);
                if (pLineNew)
                {
                    dCurPenWidth = pLineNew->getLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_POLYGON_NEW:
            {
                pPolygonNew = dynamic_cast<QPolygonBasicItem *> (pItem);
                if (pPolygonNew)
                {
                    dCurPenWidth = pPolygonNew->getLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:
            {
                pFoldLineNew = dynamic_cast<QFoldLineBasicItem *> (pItem);
                if (pFoldLineNew)
                {
                    dCurPenWidth = pFoldLineNew->getLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_FREELINE_NEW:
            {
                pFreeLineNew = dynamic_cast<QFreeLineBasicItem *> (pItem);
                if (pFreeLineNew)
                {
                    dCurPenWidth = pFreeLineNew->getLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
            {
                pLineCircleNew = dynamic_cast<QLineCircleBasicItem *> (pItem);
                if (pLineCircleNew)
                {
                    dCurPenWidth = pLineCircleNew->getLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
            {
                pRoundedRectNew = dynamic_cast<QRoundedRectBasic *> (pItem);
                if (pRoundedRectNew)
                {
                    dCurPenWidth = pRoundedRectNew->GetLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
        case SAM_DRAW_OBJECT_ARC_NEW:
            {
                pArcItemNew = dynamic_cast<QArcBasicItem *> (pItem);
                if (pArcItemNew)
                {
                    dCurPenWidth = pArcItemNew->GetLineWidth();
                    if (dMaxPenWidth < dCurPenWidth)
                    {
                        dMaxPenWidth = dCurPenWidth;
                    }
                }
            }
            break;
/////////////////wxy add end
        default:
            break;
        }
    }

    return dMaxPenWidth;
}

/********************************************************************************
 *Class SamDrawFoldLineTool
 ********************************************************************************/
SamDrawFoldLineTool::SamDrawFoldLineTool()
    :SamDrawTool(SAM_DRAW_FOLDLINE)
{
    m_pFoldLineItem = NULL;
    m_qpPoints.clear();
    m_ulPressedCnt = 0;
}

/*********************************************************************************
 * Function: Foldline mouse press event
 * Parameters: scene pointer, event pointer
 * Return: none
 ********************************************************************************/
void SamDrawFoldLineTool::mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF qpDownPoint = mouseEvent->scenePos();
    if (m_qpLastPt == qpDownPoint)
    {
        if (mouseEvent->button() == Qt::LeftButton)
        {
            if (m_pFoldLineItem)
                m_pFoldLineItem->setSelected(true);
            mouseEvent->setAccepted(true);
            return;
        }
        else if (mouseEvent->button() == Qt::RightButton)
        {
            if (m_pFoldLineItem)
                m_pFoldLineItem->setSelected(true);
            mouseEvent->setAccepted(true);

            m_pFoldLineItem = NULL;
            m_qpPoints.clear();
            m_ulPressedCnt = 0;
            SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_UNLOCKED;
            s_eDrawActType = SAM_DRAW_SELECTION;
            return;
        }
    }

    m_qpLastPt = qpDownPoint;

    if (mouseEvent->button() == Qt::LeftButton)
    {
        if (m_pFoldLineItem == NULL)
        {
            QGraphicsItem *pFoldLineItem = drawFoldLine(qpDownPoint, pScene);
            pScene->clearSelection();
            if (pFoldLineItem)
                pFoldLineItem->setSelected(true);
            mouseEvent->setAccepted(true);
            SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_LOCKED;
        }
        else
        {
            m_qpPoints.push_back(qpDownPoint);

            if (m_pFoldLineItem->getResizable() == true)
            {
                SamDrawTackerRect *pItem = new SamDrawTackerRect(qpDownPoint);
                if (pItem)
                {
                    pScene->addItem(pItem);
                    m_pFoldLineItem->m_pvecTrackers.push_back(pItem);
                }
            }
            m_pFoldLineItem->setSelected(true);
            mouseEvent->setAccepted(true);
        }
        m_ulPressedCnt++;
    }
    else if (mouseEvent->button() == Qt::RightButton)
    {
        if (m_pFoldLineItem)
        {
            if (m_pFoldLineItem->getResizable() == true)
            {
                SamDrawTackerRect *pItem = new SamDrawTackerRect(qpDownPoint);
                if (pItem)
                {
                    pScene->addItem(pItem);
                    m_pFoldLineItem->m_pvecTrackers.push_back(pItem);
                }
            }

            pScene->clearSelection();
            m_pFoldLineItem->setSelected(true);

            mouseEvent->setAccepted(true);
        }

        m_pFoldLineItem = NULL;
        m_qpPoints.clear();
        m_ulPressedCnt = 0;
        s_eDrawActType = SAM_DRAW_SELECTION;
        SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_UNLOCKED;
        SamDrawTool::mousePressEvent(pScene, mouseEvent);
    }
}

/*********************************************************************************
 * Function: Foldline mouse move event
 * Parameters: scene pointer, event pointer
 * Return: none
 ********************************************************************************/
void SamDrawFoldLineTool::mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    QPointF qpCurPoint = mouseEvent->scenePos();
    if (m_pFoldLineItem)
    {
        if (m_qpPoints.size() <= 1)
        {
            m_qpPoints.push_back(qpCurPoint);
        }
        else
        {
            //m_qpPoints[m_ulPressedCnt] = qpCurPoint;
            m_qpPoints[m_qpPoints.size() - 1] = qpCurPoint;
        }

        QVector<QPointF> qpCurPoints = m_qpPoints;
        for (int i = 0; i < m_qpPoints.size(); i++)
        {
            qpCurPoints[i] = m_pFoldLineItem->mapFromScene(qpCurPoints[i]);
        }
        QPainterPath path = QPainterPath();
        path.moveTo(qpCurPoints[0]);
        for (int i = 1; i < m_qpPoints.size(); i++)
        {
            path.lineTo(qpCurPoints[i]);
        }
        m_pFoldLineItem->setPath(path);
        m_pFoldLineItem->setSelected(true);
        mouseEvent->setAccepted(true);
    }

    SamDrawTool::mouseMoveEvent(pScene, mouseEvent);
}

/*********************************************************************************
 * Function: Foldline mouse release event
 * Parameters: scene pointer, event pointer
 * Return: none
 ********************************************************************************/
void SamDrawFoldLineTool::mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    /*pScene->views().first()->setCursor(Qt::ArrowCursor);
    SamDrawTool::mouseReleaseEvent(pScene, event);*/
}

/*********************************************************************************
 * Function: Foldline mouse double click event
 * Parameters: scene pointer, event pointer
 * Return: none
 ********************************************************************************/
void SamDrawFoldLineTool::mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
}

/*********************************************************************************
 * Function: Foldline cancel event
 * Parameters: pScene
 * Return: none
 ********************************************************************************/
void SamDrawFoldLineTool::onCancel(QGraphicsScene *pScene)
{
    if (m_pFoldLineItem)
    {
        //修改为按esc按键退出后 少加入一个绿色小矩形问题
        if(m_qpPoints.size() > m_pFoldLineItem->m_pvecTrackers.size())
        {
            QVector<QPointF> qpCurPoints = m_qpPoints;
            for (int i = 0; i < m_qpPoints.size(); i++)
            {
                qpCurPoints[i] = m_pFoldLineItem->mapFromScene(qpCurPoints[i]);
            }
            if (m_pFoldLineItem->getResizable() == true)
            {
                SamDrawTackerRect *pItem = new SamDrawTackerRect(qpCurPoints.at(qpCurPoints.size() -1));
                if (pItem)
                {
                    pScene->addItem(pItem);
                    m_pFoldLineItem->m_pvecTrackers.push_back(pItem);
                }
            }
        }
    }

    m_pFoldLineItem = NULL;
    m_qpPoints.clear();
    m_ulPressedCnt = 0;
    SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_UNLOCKED;

    SamDrawTool::onCancel(pScene);
}

/*********************************************************************************
 * Function: draw foldline (construct foldline type object)
 * Parameters: pressed point, scene pointer
 * Return: graphicsitem pointer
 ********************************************************************************/
QGraphicsItem *SamDrawFoldLineTool::drawFoldLine(const QPointF qpPressedPt, QGraphicsScene *pScene)
{
    m_qpPoints.clear();
    m_qpPoints.push_back(qpPressedPt);
    QPainterPath path = QPainterPath();
    path.moveTo(qpPressedPt);
    QFoldLineBasicItem *pItem = new QFoldLineBasicItem(path);
    SamDrawScene *pSamscene;
    pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    pItem->setId(pwnd->getNewId());
    pSamscene->addItem(pItem);
    pwnd->insertId(pItem->id());

    pItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_pFoldLineItem = pItem;

    if (m_pFoldLineItem->getResizable() == true)
    {
        SamDrawTackerRect *pItemTracker = new SamDrawTackerRect(qpPressedPt);
        if (pItemTracker)
        {
            pScene->addItem(pItemTracker);
            m_pFoldLineItem->m_pvecTrackers.push_back(pItemTracker);
        }
    }

    //控件新建的撤销和删除
    QGraphicsItem *pAddItem=dynamic_cast<QGraphicsItem *> (pItem);
    if(pAddItem)
    {
        pwnd->undoStack->push(new addItemToScence(pSamscene,pAddItem,true));
    }

    return pItem;
}

/********************************************************************************
 *Class SamDrawFreeLineTool
 ********************************************************************************/
SamDrawFreeLineTool::SamDrawFreeLineTool()
    :SamDrawTool(SAM_DRAW_FREELINE)
{
    m_qpPoints.clear();
    m_pFreeLineItem = NULL;
    m_ulPressedCnt = 0;
}

/*********************************************************************************
 * Function: Freeline mouse press event
 * Parameters: scene pointer, event pointer
 * Return: none
 ********************************************************************************/
void SamDrawFreeLineTool::mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() == Qt::LeftButton)
    {
        QPointF qpDownPoint = mouseEvent->scenePos();
        if (m_pFreeLineItem == NULL)
        {
            QGraphicsItem *pFreeLineItem = drawFreeLine(qpDownPoint, pScene);
            pScene->clearSelection();
            if (pFreeLineItem)
                pFreeLineItem->setSelected(true);
            mouseEvent->setAccepted(true);
        }
        else
        {
            pScene->clearSelection();
            m_pFreeLineItem->setSelected(true);
            mouseEvent->setAccepted(true);
            m_pFreeLineItem = NULL;
            m_qpPoints.clear();
            m_ulPressedCnt = 0;
            s_eDrawActType = SAM_DRAW_SELECTION;
        }
    }
    else if (mouseEvent->button() == Qt::RightButton)
    {
        if (m_pFreeLineItem)
        {
            pScene->clearSelection();
            m_pFreeLineItem->setSelected(true);
            mouseEvent->setAccepted(true);
        }

        m_pFreeLineItem = NULL;
        m_qpPoints.clear();
        m_ulPressedCnt = 0;
        s_eDrawActType = SAM_DRAW_SELECTION;
        SamDrawTool::mousePressEvent(pScene, mouseEvent);
    }
}

/*********************************************************************************
 * Function: Freeline mouse move event
 * Parameters: scene pointer, event pointer
 * Return: none
 ********************************************************************************/
void SamDrawFreeLineTool::mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_pFreeLineItem)
    {
        QPointF qpCurMousept = mouseEvent->scenePos();
        if (m_pFreeLineItem->getResizable() == true)
        {
            if (++m_ulPressedCnt < 4)
            {
                SamDrawTool::mouseMoveEvent(pScene, mouseEvent);
                return;
            }

            m_ulPressedCnt = 0;
            SamDrawTackerRect *pItem = new SamDrawTackerRect(qpCurMousept);
            if (pItem)
            {
                pScene->addItem(pItem);
                m_pFreeLineItem->m_pvecTrackers.push_back(pItem);
            }
        }
        m_qpPoints.push_back(qpCurMousept);

        QVector<QPointF> qpPoints = m_qpPoints;
        for (int i = 0; i < qpPoints.size(); i++)
        {
            qpPoints[i] = m_pFreeLineItem->mapFromScene(qpPoints[i]);
        }
        QPainterPath path = QPainterPath();
        path.moveTo(qpPoints[0]);
        for (int i = 1; i < qpPoints.size(); i++)
        {
            path.lineTo(qpPoints[i]);
        }
        m_pFreeLineItem->setPath(path);
        m_pFreeLineItem->setSelected(true);
        mouseEvent->setAccepted(true);
    }

    SamDrawTool::mouseMoveEvent(pScene, mouseEvent);
}

/*********************************************************************************
 * Function: Freeline mouse release event
 * Parameters: scene pointer, event pointer
 * Return: none
 ********************************************************************************/
void SamDrawFreeLineTool::mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    pScene->clearSelection();
    if (m_pFreeLineItem)
        m_pFreeLineItem->setSelected(true);
    mouseEvent->setAccepted(true);

    m_pFreeLineItem = NULL;
    m_qpPoints.clear();
    m_ulPressedCnt = 0;
    s_eDrawActType = SAM_DRAW_SELECTION;
}

/*********************************************************************************
 * Function: Freeline mouse duble click event
 * Parameters: scene pointer, event pointer
 * Return: none
 ********************************************************************************/
void SamDrawFreeLineTool::mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
}

/*********************************************************************************
 * Function: cancel fre line.
 * Parameters: scene pointer
 * Return: none
 ********************************************************************************/
void SamDrawFreeLineTool::onCancel(QGraphicsScene *pScene)
{
    if (m_pFreeLineItem)
    {
        //delete m_pFreeLineItem;
    }

    m_pFreeLineItem = NULL;
    m_qpPoints.clear();
    m_ulPressedCnt = 0;

    SamDrawTool::onCancel(pScene);
}

/*********************************************************************************
 * Function: Draw freeline (construct freeline type object)
 * Parameters: pressed point, scene pointer
 * Return: graphicsitem pointer
 ********************************************************************************/
QGraphicsItem *SamDrawFreeLineTool::drawFreeLine(const QPointF qpPressedPt, QGraphicsScene *pScene)
{
    if (pScene == NULL)
    {
        return NULL;
    }

    m_qpPoints.clear();
    m_qpPoints.push_back(qpPressedPt);
    QPainterPath path = QPainterPath();
    path.moveTo(qpPressedPt);
    QFreeLineBasicItem *pItem = new QFreeLineBasicItem(path);
    SamDrawScene *pSamscene;
    pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    pItem->setId(pwnd->getNewId());
    pSamscene->addItem(pItem);
    pwnd->insertId(pItem->id());

    pItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_pFreeLineItem = pItem;

    if (m_pFreeLineItem->getResizable() == true)
    {
        SamDrawTackerRect *pItemTracker = new SamDrawTackerRect(qpPressedPt);
        if (pItemTracker)
        {
            pScene->addItem(pItemTracker);
            m_pFreeLineItem->m_pvecTrackers.push_back(pItemTracker);
        }
    }

    //控件新建的撤销和删除
    QGraphicsItem *pAddItem=dynamic_cast<QGraphicsItem *> (pItem);
    if(pAddItem)
    {
        pwnd->undoStack->push(new addItemToScence(pSamscene,pAddItem,true));
    }

    return pItem;
}

/********************************************************************************
 *Class SamDrawRoundRectTool constructor
 ********************************************************************************/
SamDrawRoundedRectTool::SamDrawRoundedRectTool()
    :SamDrawTool(SAM_DRAW_ROUNDED_RECT)
{
}

/*********************************************************************************
 * Function: roundrect tool mousepress event
 * Parameters: scene pointer, mouse event
 * Return: none
 ********************************************************************************/
void SamDrawRoundedRectTool::mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
    {
        SamDrawTool::mousePressEvent(pScene, mouseEvent);
        return;
    }
    pScene->clearSelection();
    mouseEvent->setAccepted(true);
    //mouseEvent->setAccepted(true);
}

/*********************************************************************************
 * Function: roundrect tool mousemove event
 * Parameters: scene pointer, mouse event
 * Return: none
 ********************************************************************************/
void SamDrawRoundedRectTool::mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event)
{
    SamDrawScene *pSamscene = dynamic_cast<SamDrawScene *> (pScene);
    if(pSamscene->bMousePress)
    onReDrawRect(event->scenePos(),pScene);
    SamDrawTool::mouseMoveEvent(pScene, event);
}

/*********************************************************************************
 * Function: roundrect tool mouserelease event
 * Parameters: scene pointer, mouse event
 * Return: none
 ********************************************************************************/
void SamDrawRoundedRectTool::mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event)
{
    qreal dWsize = 1.0;
    qreal dHsize = 1.0;
    SamDrawScene *pSamscene;
    pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    if(pBackRect)
    {
        pSamscene->removeItem(pBackRect);
        pBackRect = NULL;
    }

    dWsize = abs(pSamscene->MouseReleasePos.x() - pSamscene->MousePressPos.x());
    dHsize = abs(pSamscene->MouseReleasePos.y() - pSamscene->MousePressPos.y());

    QPointF qpDownPoint;
    qpDownPoint.setX(pSamscene->MouseReleasePos.x() < pSamscene->MousePressPos.x()? pSamscene->MouseReleasePos.x():pSamscene->MousePressPos.x());
    qpDownPoint.setY(pSamscene->MouseReleasePos.y() < pSamscene->MousePressPos.y()? pSamscene->MouseReleasePos.y():pSamscene->MousePressPos.y());

    QGraphicsItem *pDrawItem = drawRoundedRect(qpDownPoint, pScene);

    if (pDrawItem)
    {
        QRoundedRectBasic *pRect = dynamic_cast<QRoundedRectBasic *>(pDrawItem);
        if(dWsize > 10.0 || dHsize > 10.0)
        {
            pRect->SetWidth(dWsize);
            pRect->SetHeight(dHsize);
        }
        pDrawItem->setSelected(true);
    }

    pScene->views().first()->setCursor(Qt::ArrowCursor);
    SamDrawTool::mouseReleaseEvent(pScene, event);
}

/*********************************************************************************
 * Function: draw roundrect
 * Parameters: mouse point, scene pointer
 * Return: graphicsitem pointer
 ********************************************************************************/
QGraphicsItem *SamDrawRoundedRectTool::drawRoundedRect(const QPointF qpPressedPt, QGraphicsScene *pScene)
{
    QRoundedRectBasic *pRoundRect = new QRoundedRectBasic();
    pRoundRect->SetBackColor(QColor(255,255,255));
    pRoundRect->setPos(qpPressedPt);
    SamDrawScene *pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    if (NULL == pSamscene) return NULL;
    pRoundRect->setId(pwnd->getNewId());
    pSamscene->addItem(pRoundRect);
    pwnd->insertId(pRoundRect->id());

    pRoundRect->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pRoundRect->setFlag(QGraphicsItem::ItemIsMovable, true);

    QRectF qrcBondingRect = pRoundRect->sceneBoundingRect();
    pRoundRect->drawTracker(TRK_SELECTED, pScene, qrcBondingRect);

    //控件新建的撤销和删除
    QGraphicsItem *pAddItem= dynamic_cast<QGraphicsItem *> (pRoundRect);
    if(pAddItem)
    {
        pwnd->undoStack->push(new addItemToScence(pSamscene, pAddItem, true));
    }

    return pRoundRect;
}

/********************************************************************************
 *Class SamDrawArcTool constructor
 ********************************************************************************/
SamDrawArcTool::SamDrawArcTool()
        :SamDrawTool(SAM_DRAW_ARC)
{
}

/*********************************************************************************
 * Function: SamDrawArcTool mousepress event
 * Parameters: scene pointer, mouse event
 * Return: none
 ********************************************************************************/
void SamDrawArcTool::mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
    {
        SamDrawTool::mousePressEvent(pScene, mouseEvent);
        return;
    }
    pScene->clearSelection();
    mouseEvent->setAccepted(true);
}

/*********************************************************************************
 * Function: SamDrawArcTool mousemove event
 * Parameters: scene pointer, mouse event
 * Return: none
 ********************************************************************************/
void SamDrawArcTool::mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event)
{
    SamDrawScene *pSamscene = dynamic_cast<SamDrawScene *> (pScene);
    if(pSamscene->bMousePress)
    onReDrawRect(event->scenePos(),pScene);
    SamDrawTool::mouseMoveEvent(pScene, event);
}

/*********************************************************************************
 * Function: SamDrawArcTool mouserelease event
 * Parameters: scene pointer, mouse event
 * Return: none
 ********************************************************************************/
void SamDrawArcTool::mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event)
{
    qreal dWsize = 1.0;
    qreal dHsize = 1.0;
    qreal dDelta = 1.0;
    SamDrawScene *pSamscene;
    pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    if(pBackRect)
    {
        pSamscene->removeItem(pBackRect);
        pBackRect = NULL;
    }

    dWsize = abs(pSamscene->MouseReleasePos.x() - pSamscene->MousePressPos.x());
    dHsize = abs(pSamscene->MouseReleasePos.y() - pSamscene->MousePressPos.y());

    QPointF qpDownPoint;
    qpDownPoint.setX(pSamscene->MouseReleasePos.x() < pSamscene->MousePressPos.x()? pSamscene->MouseReleasePos.x():pSamscene->MousePressPos.x());
    qpDownPoint.setY(pSamscene->MouseReleasePos.y() < pSamscene->MousePressPos.y()? pSamscene->MouseReleasePos.y():pSamscene->MousePressPos.y());
    QGraphicsItem *pDrawItem = drawArc(qpDownPoint, pScene);

    if (pDrawItem)
    {
        dDelta = pDrawItem->boundingRect().width()/pDrawItem->boundingRect().height();
        QArcBasicItem *pArc = dynamic_cast<QArcBasicItem *>(pDrawItem);
        if(dWsize > 10.0 || dHsize > 10.0)
        {
            if(dWsize > dHsize)
            {
                dHsize = dWsize/dDelta;
            }
            else
            {
                dWsize = dHsize * dDelta;
            }
            pArc->SetWidth(dWsize);
            pArc->SetHeight(dHsize);
        }
        pDrawItem->setSelected(true);
    }

    pScene->views().first()->setCursor(Qt::ArrowCursor);
    SamDrawTool::mouseReleaseEvent(pScene, event);
}

/*********************************************************************************
 * Function: draw arc
 * Parameters: press point, scene pointer
 * Return: graphicsitem
 ********************************************************************************/
QGraphicsItem *SamDrawArcTool::drawArc(const QPointF qpPressedPt, QGraphicsScene *pScene)
{
    QArcBasicItem *pArc = new QArcBasicItem();
    pArc->SetBackColor(QColor(255,255,255));
    SamDrawScene *pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    if (NULL == pSamscene) return NULL;
    pArc->setId(pwnd->getNewId());
    pSamscene->addItem(pArc);
    pwnd->insertId(pArc->id());

    pArc->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pArc->setFlag(QGraphicsItem::ItemIsMovable, true);
    pArc->SetLineType(0);
    pArc->setPos(qpPressedPt);

    QRectF qrcBondingRect = pArc->sceneBoundingRect();
    pArc->drawTracker(TRK_SELECTED, pScene, qrcBondingRect);

    //控件新建的撤销和删除
    QGraphicsItem *pAddItem= dynamic_cast<QGraphicsItem *> (pArc);
    if(pAddItem)
    {
        pwnd->undoStack->push(new addItemToScence(pSamscene, pAddItem, true));
    }

    return pArc;
}

/*********************************************************************************
 * Class SamDrawLineCircleTool for SamDraw multi path item(line-circle)
 * Design by tanghaiguo at 2010.11.8
 *
 ********************************************************************************/
SamDrawLineCircleTool::SamDrawLineCircleTool()
    :SamDrawTool(SAM_DRAW_LINE_CIRCLE)
{
    m_pPath             = NULL;
    m_pLineCircleItem   = NULL;
    pMoveItem           = NULL;
    bMousePressed       = false ;
    bMouseMove          = false;
    bMouseMovePressed   = false;
    m_points.clear();
}

/*********************************************************************************
 * Function: linecircle tool mouse press event
 * Parameters: scene pointer, mouse point
 * Return: none
 ********************************************************************************/
void SamDrawLineCircleTool::mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    if(!pScene || !mouseEvent)  return;

    if (mouseEvent->button() == Qt::LeftButton)
    {
        bMousePressed = true;
        qPressPoint = mouseEvent->scenePos();
        m_points.push_back(qPressPoint);
        if(m_pLineCircleItem == NULL)
        {
            QLineCircleBasicItem *pLineCircleItem = drawLineCircle(qPressPoint,pScene);
            pScene->clearSelection();
            if (pLineCircleItem)
                pLineCircleItem->setSelected(true);
      //      mouseEvent->setAccepted(true);
            SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_LOCKED;
        }

        if(pMoveItem ==NULL)
        {
            QPainterPath pMovePath = QPainterPath(qPressPoint);
            pMoveItem = new QLineCircleBasicItem(pMovePath);
            pScene->addItem(pMoveItem);
        }

        if (m_pLineCircleItem->getResizable() == true)
        {
            SamDrawTackerRect *pItemTracker = new SamDrawTackerRect(qPressPoint);
            if (pItemTracker)
            {
                pScene->addItem(pItemTracker);
                m_pLineCircleItem->m_pvecTrackers.push_back(pItemTracker);
            }
        }

        mouseEvent->setAccepted(true);
    }
    else if (mouseEvent->button() == Qt::RightButton)
    {
        s_eDrawActType = SAM_DRAW_SELECTION;
        if(m_pLineCircleItem)
        {
            m_pLineCircleItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            m_pLineCircleItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            m_pLineCircleItem->setSelected(true);
        }
        m_points.clear();
        pScene->removeItem(pMoveItem);
        if(pMoveItem)
        {
            delete pMoveItem;
            pMoveItem = NULL;
        }
        m_pLineCircleItem = NULL;
        if(m_pPath)
        {
            delete m_pPath;
            m_pPath = NULL;
        }
        SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_UNLOCKED;
        pScene->views().first()->setCursor(Qt::ArrowCursor);
    }
}

/*********************************************************************************
 * Function: linecircle tool mouse release event
 * Parameters: scene pointer, mouse point
 * Return: none
 ********************************************************************************/
void SamDrawLineCircleTool::mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event)
{
    if(!pScene || !event)
        return ;

    if (event->button() == Qt::LeftButton)
    {
        bMousePressed = false ;
        if(m_points.size() > 1 && m_pPath && m_pLineCircleItem)
        {
            QPointF mousepoint = event->scenePos();
            if(bMouseMovePressed)
            {
                bMouseMovePressed = false ;
                QPointF midPoint = m_points.at(m_points.size()-1);
                QPointF addpoint;
                addpoint.setX(2*midPoint.x() - mousepoint.x());
                addpoint.setY(2*midPoint.y() - mousepoint.y());
                m_points.insert(m_points.size()-1,addpoint);

                QPainterPath pTempPath = QPainterPath();
                pTempPath.moveTo(m_points.at(m_points.size()-3));
                pTempPath.cubicTo(m_points.at(m_points.size()-3),m_points.at(m_points.size()-2),m_points.at(m_points.size()-1));
                m_pPath->addPath(pTempPath);
                m_pLineCircleItem->setPath(*m_pPath);

                if(pMoveItem)
                {
                    QPainterPath pMovePath = QPainterPath();
                    pMovePath.moveTo(midPoint);
                    pMovePath.lineTo(midPoint);
                    pMoveItem->setPath(pMovePath);
                }
            }
            else
            {
                if(pMoveItem)
                {
                    QPainterPath pMovePath = QPainterPath();
                    pMovePath.moveTo(mousepoint);
                    pMovePath.lineTo(mousepoint);
                    pMoveItem->setPath(pMovePath);
                }
                QPainterPath pTempPath = QPainterPath();
                pTempPath.moveTo(m_points.at(m_points.size()-2));
                pTempPath.lineTo(m_points.at(m_points.size()-1));
                m_pPath->addPath(pTempPath);
                m_pLineCircleItem->setPath(*m_pPath);
            }
        }
    }

    /*
    SamDrawTool::mouseMoveEvent(pScene, event);*/
}


/*********************************************************************************
 * Function: linecircle tool mouse move event
 * Parameters: scene pointer, mouse point
 * Return: none
 ********************************************************************************/
void SamDrawLineCircleTool::mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event)
{
    SamDrawTool::mouseMoveEvent(pScene, event);

    if(!pScene || !event) return ;
    if(m_points.isEmpty()) return ;

    if(!bMouseMove && QPointF(qPressPoint - event->scenePos()).manhattanLength() > 25)
    {
        bMouseMove = true ;
    }
    if(bMouseMove && pMoveItem)
    {
        bMouseMove = false ;
        if(bMousePressed)
        {
            QPointF midPoint,mousepoint,addpoint;

            if(m_points.size()>1)
            {
                if(bMouseMovePressed == false)
                    bMouseMovePressed = true;

                midPoint = m_points.at(m_points.size()-1);
                mousepoint =event->scenePos();
                addpoint.setX((2*midPoint.x()-mousepoint.x())/1);
                addpoint.setY((2*midPoint.y()-mousepoint.y())/1);

                QPainterPath pMovePath = QPainterPath();
                pMovePath.moveTo(m_points.at(m_points.size()-2));
                pMovePath.cubicTo(m_points.at(m_points.size()-2),addpoint,midPoint);
                pMoveItem->setPath(pMovePath);
            }
        }
        else
        {
            QPainterPath pMovePath = QPainterPath();
            pMovePath.moveTo(m_points.back());
            pMovePath.lineTo(event->scenePos());
            pMoveItem->setPath(pMovePath);
        }
    }
}

/*********************************************************************************
 * Function: linecircle tool mouse double click event
 * Parameters: scene pointer, mouse point
 * Return: none
 ********************************************************************************/
void SamDrawLineCircleTool::mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event)
{
    if(!pScene || !event)
        return ;
}

/*********************************************************************************
 * Function: click on cancel esc
 * Parameters: scene
 * Return: none
 ********************************************************************************/
void SamDrawLineCircleTool::onCancel(QGraphicsScene *pScene)
{
#if 0
    s_eDrawActType = SAM_DRAW_SELECTION;

    if(m_points.size() > 1 && m_pPath && m_pLineCircleItem)
    {
        if(bMouseMovePressed)
        {
            bMouseMovePressed = false ;
            QPainterPath pTempPath = QPainterPath();
            pTempPath.moveTo(m_points.at(m_points.size()-2));
            pTempPath.lineTo(m_points.at(m_points.size()-1));
            m_pPath->addPath(pTempPath);
            m_pLineCircleItem->setPath(*m_pPath);
        }
    }

    if(m_pLineCircleItem)
    {
        m_pLineCircleItem->setSelected(true);
    }

    m_points.clear();
    pScene->removeItem(pMoveItem);
    if(pMoveItem)
    {
        delete pMoveItem;
        pMoveItem = NULL;
    }
    m_pLineCircleItem = NULL;
    if(m_pPath)
    {
        delete m_pPath;
        m_pPath = NULL;
    }

#endif

    if(pMoveItem)
    {
        pScene->removeItem(pMoveItem);
        delete pMoveItem;
        pMoveItem = NULL;
    }
    if(m_pPath)
    {
        delete m_pPath;
        m_pPath = NULL;
    }
    if(m_pLineCircleItem)
    {
        //pScene->removeItem(m_pLineCircleItem);
        //delete m_pLineCircleItem;
        m_pLineCircleItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        m_pLineCircleItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        m_pLineCircleItem->setSelected(true);
    }
    m_pLineCircleItem = NULL;
    m_points.clear();
    SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_UNLOCKED;
    SamDrawTool::onCancel(pScene);
}

/*********************************************************************************
 * Function: draw arc-line
 * Parameters: mouse point, scene pointer
 * Return: none
 ********************************************************************************/
QLineCircleBasicItem *SamDrawLineCircleTool::drawLineCircle(const QPointF qpPressedPt, QGraphicsScene *pScene)
{
    m_pPath = new QPainterPath(qpPressedPt);
    QLineCircleBasicItem *pItem = new QLineCircleBasicItem(*m_pPath);
    SamDrawScene *pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    if(!pSamscene) return NULL;

    pItem->setId(pwnd->getNewId());
    pSamscene->addItem(pItem);
    pwnd->insertId(pItem->id());

//    pItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
//    pItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_pLineCircleItem = pItem;

    //控件新建的撤销和删除
    QGraphicsItem *pAddItem = dynamic_cast<QGraphicsItem *>(pItem);
    if(pAddItem)
    {
        pwnd->undoStack->push(new addItemToScence(pSamscene,pAddItem,true));
    }

    return pItem;
}

/********************************************************************************
 *Class SamDrawTextTool
 ********************************************************************************/
SamDrawTextTool::SamDrawTextTool()
    :SamDrawTool(SAM_DRAW_SAMPLE_TEXT)
{
}

/*********************************************************************************
 * Function: Simple text mouse press event
 * Parameters: scene pointer, event pointer
 * Return: none
 ********************************************************************************/
void SamDrawTextTool::mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    QPointF qpDownPoint = mouseEvent->scenePos();
    QGraphicsItem *pDrawItem = drawText(qpDownPoint, pScene);
    pScene->clearSelection();
    if (pDrawItem)
        pDrawItem->setSelected(true);
    mouseEvent->setAccepted(true);
}

/*********************************************************************************
 * Function: Freeline mouse move event
 * Parameters: scene pointer, event pointer
 * Return: none
 ********************************************************************************/
void SamDrawTextTool::mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    SamDrawScene *pSamscene = dynamic_cast<SamDrawScene *> (pScene);
    if(pSamscene->bMousePress)
    onReDrawRect(mouseEvent->scenePos(),pScene);
    SamDrawTool::mouseMoveEvent(pScene, mouseEvent);
}

/*********************************************************************************
 * Function: Freeline mouse release event
 * Parameters: scene pointer, event pointer
 * Return: none
 ********************************************************************************/
void SamDrawTextTool::mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    SamDrawScene *pSamscene = dynamic_cast<SamDrawScene *> (pScene);
    if(pBackRect)
    {
        pSamscene->removeItem(pBackRect);
        pBackRect = NULL;
    }
    pScene->views().first()->setCursor(Qt::ArrowCursor);

    SamDrawTool::mouseReleaseEvent(pScene, mouseEvent);
}

/*********************************************************************************
 * Function: Freeline mouse double clikck event
 * Parameters: scene pointer, event pointer
 * Return: none
 ********************************************************************************/
void SamDrawTextTool::mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event)
{
}

/*********************************************************************************
 * Function: draw text item
 * Parameters: mouse point, scene pointer
 * Return: none
 ********************************************************************************/
QGraphicsItem *SamDrawTextTool::drawText(const QPointF qpPressedPt, QGraphicsScene *pScene)
{
    QRectF rect(qpPressedPt, QSize(100, 100));
    QString str("Simple Text");
    QSimpleTextItem *pItem = new QSimpleTextItem(rect, str);
    SamDrawScene *pSamscene;
    pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    pItem->setId(pwnd->getNewId());
    pSamscene->addItem(pItem);
    pwnd->insertId(pItem->id());

    //pItem->setBrush(QBrush(QColor(0,0,255)));

    QRectF qrcBondingRect = pItem->sceneBoundingRect();
    pItem->drawTracker(TRK_SELECTED, pScene, qrcBondingRect);

    //控件新建的撤销和删除
    QGraphicsItem *pAddItem=dynamic_cast<QGraphicsItem *> (pItem);
    if(pAddItem)
    {
        pwnd->undoStack->push(new addItemToScence(pSamscene,pAddItem,true));
    }

    return pItem;
}

/*********************************************************************************
 * Class SamDrawAnimationTool for animation constructor
 ********************************************************************************/
SamDrawAnimationTool::SamDrawAnimationTool()
    :SamDrawTool(SAM_DRAW_ANIMATION)
{
    m_pEllipseItems.clear();
}

/*********************************************************************************
 * Class SamDrawAnimationTool for animation destructor
 ********************************************************************************/
SamDrawAnimationTool::~SamDrawAnimationTool()
{
    int iSize = m_pEllipseItems.size();
    QElipseItem *pEllipseItem = NULL;
    for (int i = 0; i < iSize; i++)
    {
        pEllipseItem = m_pEllipseItems.at(i);
        if (pEllipseItem)
        {
            delete pEllipseItem;
            pEllipseItem = NULL;
        }
    }
    m_pEllipseItems.clear();
}

/*********************************************************************************
 * Function: draw text item
 * Parameters: mouse point, scene pointer
 * Return: none
 ********************************************************************************/
void SamDrawAnimationTool::mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent)
{
    int nPoint = 0;
    SamDrawScene *pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    if (pSamscene == NULL) return;

    QPointF qpDownPoint = mouseEvent->scenePos();
    if (m_qpLastPt == qpDownPoint)
    {
        if (mouseEvent->button() == Qt::LeftButton)
        {
            return;
        }
    }

    m_qpLastPt = qpDownPoint;

    AnInfo aninfo;
    AnimationItem *pCopyItem      = dynamic_cast<AnimationItem *> (pwnd->pOldItem);
    if(pCopyItem)
    {
        pCopyItem->onGetAnimatInfo(aninfo);
        if(0 == aninfo.nTrackType)
        {
            nPoint = 64;
        }
        else
        {
            nPoint = 2;
        }
    }

    if (mouseEvent->button() == Qt::LeftButton)
    {
        if(m_pEllipseItems.size() < nPoint)
        {
            QRectF qrcRect(QPoint(0,0), QSize(5,5));
            QElipseItem *pEllipse = new QElipseItem(qrcRect);//绘制一个底圆
            if (NULL == pEllipse) return;

            pEllipse->SetBackColor(QColor(0,0,0));        //设置背景色
            pEllipse->SetLineType(1);
            //pEllipse->SetLineWidth(1);
            pEllipse->SetLineColor(QColor(0,0,0));
            pEllipse->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pEllipse->setData(GROUP_NAME_KEY,QVariant(m_pEllipseItems.size()));
            m_pEllipseItems.push_back(pEllipse);
            pEllipse->setPos(qpDownPoint);
            pSamscene->addItem(pEllipse);

            SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_LOCKED;
        }
    }
    else if (mouseEvent->button() == Qt::RightButton)
    {
        if(2 == nPoint && 1 == m_pEllipseItems.size())//区域轨迹且只录制了一个轨迹点
        {
            return;
        }
        this->finishAnimation(pScene);
        s_eDrawActType = SAM_DRAW_SELECTION;
        SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_UNLOCKED;
        m_pEllipseItems.clear();
        SamDrawTool::mousePressEvent(pScene, mouseEvent);
        pScene->views().first()->setCursor(Qt::ArrowCursor);
    }
}

/*********************************************************************************
 * Function: cancel draw animation
 * Parameters: mouse point, scene pointer
 * Return: none
 ********************************************************************************/
void SamDrawAnimationTool::onCancel(QGraphicsScene *pScene)
{
    QElipseItem *pEllipse = NULL;

    if (m_pEllipseItems.size() > 0)
    {
        int iSize = m_pEllipseItems.size();
        for (int i = 0; i < iSize; i++)
        {
            pEllipse = m_pEllipseItems.at(i);
            if (pEllipse)
            {
                delete pEllipse;
                pEllipse = NULL;
            }
        }
    }
    m_pEllipseItems.clear();

    SamDrawTool::s_eToolStat = SAM_DRAW_TOOL_UNLOCKED;

    SamDrawTool::onCancel(pScene);
}

/*********************************************************************************
 * Function: finish the current animation
 * Parameters: mouse point, scene pointer
 * Return: none
 ********************************************************************************/
void SamDrawAnimationTool::finishAnimation(QGraphicsScene *pScene)
{
    QPointF qpPonit;
    AnInfo aninfo;
    AnimationItem *pCopyItem      = dynamic_cast<AnimationItem *> (pwnd->pOldItem);
    pCopyItem->onGetAnimatInfo(aninfo);
    AnimationItem *pGroup = NULL;
    QGraphicsItem *pOldItem = NULL;
    QDrawGraphics *pDraw    = NULL;
    QGroupItem *pBaseItem   = NULL;
    QItemGroup *pItemGoup = NULL;
    DrawItemToScene GroupFunction;
    QVector<TrackPointInfo> TrackInfo;

    if (m_pEllipseItems.size() <= 0) return;

    SamDrawScene *pSamscene = dynamic_cast<SamDrawScene *>(pScene);
    if (pSamscene == NULL) return;

    pGroup = new AnimationItem;
    pGroup->onSaveAnimatInfo(aninfo);
    pGroup->SaveSecurityPro(&(pCopyItem->sPro));
    pGroup->onSetCurrentNum(pCopyItem->onGetCurrentNum());
    pGroup->setId(pCopyItem->id());
    if (NULL == pGroup) return;

    pDraw = new QDrawGraphics;
    if (NULL == pDraw)
    {
        delete pGroup;
        pGroup = NULL;
        return;
    }

    qpPonit = m_pEllipseItems.at(0)->scenePos();

    QList<QGraphicsItem *> itemList;
    itemList = pCopyItem->childItems();
    foreach(QGraphicsItem *pItem,itemList)
    {
        if("mMain" == pItem->data(GROUP_NAME_KEY).toString())
        {
            pItemGoup = new QItemGroup;
            foreach(QGraphicsItem *pChildItem,pItem->childItems())
            {
                QGraphicsItem *item;
                GroupFunction.CopyItem(&item,pChildItem);
                pItemGoup->addToGroup(item);
            }

            pItemGoup->setData(GROUP_NAME_KEY,pItem->data(GROUP_NAME_KEY).toString());
            pItemGoup->setData(GROUP_TYPE_KEY,pItem->data(GROUP_TYPE_KEY).toInt());
            pOldItem = pItemGoup;
            break;
        }
    }
    if(!pOldItem)
    {
        pOldItem = pDraw->OnDrawRectAndText(pSamscene);
        pBaseItem = new QGroupItem(pOldItem);
        if (NULL == pBaseItem)
        {
            delete pGroup;
            pGroup = NULL;

            delete pDraw;
            pDraw = NULL;

            return;
        }

        pBaseItem->SetWidth(60);
        pBaseItem->SetHeigth(60);
        pBaseItem->SetPropertyValue("mText.Text", QVariant("0"));
        pOldItem->setPos(qpPonit.x() + 5, qpPonit.y());
        pOldItem->setData(GROUP_NAME_KEY, QVariant("mMain"));
    }
    else
    {
        pBaseItem = new QGroupItem(pOldItem);
        if (NULL == pBaseItem)
        {
            delete pGroup;
            pGroup = NULL;

            delete pDraw;
            pDraw = NULL;

            return;
        }
        pBaseItem->SetWidth(60);
        pBaseItem->SetHeigth(60);
        QPointF pos = pOldItem->boundingRect().topLeft();
        pOldItem->setPos(qpPonit.x() + 5 - pos.x(),qpPonit.y() - pos.y());
    }


    pOldItem->setFlag(QGraphicsItem::ItemIsSelectable, false);

    pGroup->addToGroup(pOldItem);


    foreach (QElipseItem * pItem, m_pEllipseItems)
    {
        pGroup->addToGroup(pItem);
    }

    QSimpleTextItem *pTxt = NULL;
    int nCount = m_pEllipseItems.size();
    QString sText;
    QRectF rect(QPointF(0,0), QSize(10,10));
    TrackInfo.resize(nCount);
    for(int i = 0; i < nCount;i++)
    {
        sText = QString("%1").arg(i);
        pTxt = new QSimpleTextItem(rect,sText);
        pTxt->SetFontSize(8);
        QFont nfont = pTxt->GetTextFont(); //设置文本外框的大小
        nfont.setPointSize(8);
        QFontMetrics fontM(nfont);
        QRect rc = fontM.boundingRect(sText);
        rect.setSize(QSize(rc.width(),rc.height()));

        QPointF point = m_pEllipseItems.at(i)->scenePos();
        pTxt->setPos(point.x(), point.y()+5);
        pTxt->SetFontColor(QColor(255,0,0));
        pTxt->SetRectOutLine(false);
        pTxt->setData(GROUP_NAME_KEY,QVariant(i));
        pTxt->setFlag(QGraphicsItem::ItemIsSelectable, false);
        TrackInfo[i].nOrbitId = i;
        TrackInfo[i].nXPos = point.x();
        TrackInfo[i].nYPos = point.y();
        pGroup->onSetTrackInfo(TrackInfo);
        pGroup->addToGroup(pTxt);
    }
    pGroup->m_AnimatInfo.nTrackPointTotal = nCount;

    //pGroup->setData(GROUP_DATALIST_KEY, QVariant(sList));
    //pGroup->setData(GROUP_TYPE_KEY, QVariant(GROUP_TYPE_ANIMATE));

    pGroup->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pGroup->setFlag(QGraphicsItem::ItemIsMovable, true);
    pSamscene->addItem(pGroup);

    //控件新建的撤销和删除
    QGraphicsItem *pAddItem=dynamic_cast<QGraphicsItem *> (pGroup);
    if(pAddItem)
    {
        pwnd->undoStack->push(new addItemToScence(pSamscene, pAddItem, true));
    }

    QGraphicsItem *oldItem = dynamic_cast<QGraphicsItem *>(pGroup);
    if (oldItem)
    {
        pwnd->AndTreeSubItem(oldItem);
        pwnd->upDatetreeScreenItem();
        //emit upDate_treeScreenItem();//更新画面的子项
    }
    delete pCopyItem;
    pwnd->pOldItem = NULL;
}

/*********************************************************************************
 * Function: draw text item
 * Parameters: mouse point, scene pointer
 * Return: none
 ********************************************************************************/
void SamDrawAnimationTool::mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event)
{
    SamDrawTool::mouseMoveEvent(pScene, event);
}

/*********************************************************************************
 * Function: draw text item
 * Parameters: mouse point, scene pointer
 * Return: none
 ********************************************************************************/
void SamDrawAnimationTool::mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event)
{
    (void) pScene;
    (void) event;
}

/*********************************************************************************
 * Function: draw text item
 * Parameters: mouse point, scene pointer
 * Return: none
 ********************************************************************************/
void SamDrawAnimationTool::mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event)
{
    (void) pScene;
    (void) event;
}
