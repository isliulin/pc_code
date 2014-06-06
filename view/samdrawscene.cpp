#include "samdrawscene.h"
#include "QGraphicsSceneMouseEvent"
#include "QGraphicsScene"
#include <QMessageBox>
#include "Frame/mainwindow.h"
#include "QGraphicsItem"
#include <QGraphicsView>
#include <QPainterPath>
#include "math.h"
#include <QDrag>
#include <QMimeData>
#include <QLinearGradient>
#include <QRadialGradient>
//#include <QDebug>
#include "qrectitem.h"
//#include "HeadFile/DefineGlobalVariable.h"
//#include "qgroup.h"
#include "view/samdrawitembase.h"
#include "headfile/allgraphics.h"
#include  "Frame\mainwindow.h"
#include "view/statictextitem.h"
#include <QClipboard>
#include "view/QRecipeItem.h"
#include "view/QRecipetableItem.h"
#include "view/ImageItem.h"
#include "view/animationitem.h"
#include "view/calibrationitem.h"
#include "view/SliderItem.h"
#include "view/alarmbar.h"
#include "view/alarmitem.h"
#include "view/hisalarmitem.h"
#include "view/qmessageshowattr.h"
#include "view/dyncircleattr.h"
#include "view/dynrectattr.h"
#include "view/qtrendattr.h"
#include "view/qtrenddatagroupattr.h"
#include "view/flowblockitem.h"
#include "view/qhistorydatashowattr.h"
#include "view/qmessageboradattr.h"
extern  MainWindow *pwnd;
#include "Command/unandrestack.h"
#include "switchitem.h"
#include "view/QtableItem.h"
#include "view/qdropdownattr.h"
#include "mfbtnitem.h"
#include "view/DataDisplayItem.h"
#include "view/ChartItem.h"
#include "view/akcomboitem.h"
#include "xytrend.h"
QRectItem *pBoundRect = NULL;

#define MAX_DISTANCE      15
#define MIN_MOUSEMOVE     1

SamDrawScene::SamDrawScene(QObject *parent)
    :QGraphicsScene(parent)
{
    m_bChangePicPath = true;
    is_paste_singleItem=false;
    SamDrawSceneForUndo();
    bMousePress = false;
    bResize = false;
    pAniMageItam = NULL;
    m_dTopZValue = 0;
    bIsLibrary = true;
    pTableItam = NULL;
    pTableLine = NULL;
    bMoveFlag = false;
    m_qvecPrimaryItems.clear();
    connect(this, SIGNAL(selectionChanged()), this, SLOT(selItemsChanged()));
    connect(this,SIGNAL(key_paste(QGraphicsItem*,QGraphicsItem *)),this,SLOT(Onkey_paste(QGraphicsItem*,QGraphicsItem *)));
}

SamDrawScene::~SamDrawScene()
{
    QList<QGraphicsItem *> itemList = this->items();
    foreach(QGraphicsItem *pItem, itemList)
    {
        //this->removeItem(pItem);
        //this->deleteSamItem(pItem);
    }
}

/*add by tanghaiguo at 2010.11.10*/
void SamDrawScene::SetPattern(QPainter *painter) //set the line pattern
{
    if(m_sceneRect.isEmpty())
        return;
    QLinearGradient gradient(m_sceneRect.topLeft(),m_sceneRect.bottomRight());
    QRadialGradient Radial(m_sceneRect.center(),m_sceneRect.width()/2,m_sceneRect.center());
    gradient.setSpread(QGradient::PadSpread);//	RepeatSpread
    QBrush br=this->backgroundBrush();
    br.setColor(m_sceneBackColor); //设置前景色即样式颜色

    int pt;
    if(nIsSceneOrWindow == 0 || nIsSceneOrWindow == 1)
    {
        pt = nPattern + 1;//去掉透明，窗口，画面
    }
    else//键盘不去掉透明
    {
        pt = nPattern;
    }
    switch(pt)
    {

//    case 2:br.setStyle(Qt::Dense1Pattern);break;
//    case 3:br.setStyle(Qt::Dense2Pattern);break;
//    case 4:br.setStyle(Qt::Dense3Pattern);break;
//    case 5:br.setStyle(Qt::Dense4Pattern);break;
//    case 6:br.setStyle(Qt::Dense5Pattern);break;
//    case 7:br.setStyle(Qt::Dense6Pattern);break;
//    case 8:br.setStyle(Qt::Dense7Pattern);break;
//    case 9:br.setStyle(Qt::HorPattern);break;//setBrush(Qt::HorPattern);break;
//    case 10:br.setStyle(Qt::VerPattern);break;
//    case 11:br.setStyle(Qt::CrossPattern);break;
//    case 12:br.setStyle(Qt::BDiagPattern);break;
//    case 13:br.setStyle(Qt::FDiagPattern);break;
//    case 14:br.setStyle(Qt::DiagCrossPattern);break;
    case 0:br.setStyle(Qt::NoBrush);break;
    case 1:br.setStyle(Qt::SolidPattern);break;
    case 2: //横向过度
        gradient.setStart(m_sceneRect.x(),m_sceneRect.bottom());
        gradient.setColorAt(0,m_sceneStyleColor );
        gradient.setColorAt(1,m_sceneBackColor );
        break;
    case 3: //横向对称过度
        gradient.setStart(m_sceneRect.x(),m_sceneRect.bottom());
        gradient.setColorAt(0,m_sceneStyleColor );
        gradient.setColorAt(0.5,m_sceneBackColor );
        gradient.setColorAt(1,m_sceneStyleColor );
        break;
    case 4: //纵向过度
        gradient.setStart(m_sceneRect.right(),m_sceneRect.y());
        gradient.setColorAt(0,m_sceneStyleColor  );
        gradient.setColorAt(1,m_sceneBackColor);
        break;
    case 5: //纵向对称过度
        gradient.setStart(m_sceneRect.right(),m_sceneRect.y());
        gradient.setColorAt(0,m_sceneStyleColor  );
        gradient.setColorAt(0.5,m_sceneBackColor);
        gradient.setColorAt(1,m_sceneStyleColor );
        break;
    case 6: //斜上过度
        gradient.setColorAt(0,m_sceneStyleColor );
        gradient.setColorAt(1,m_sceneBackColor );
        break;
    case 7: //斜上对称过度
        gradient.setColorAt(0,m_sceneStyleColor );
        gradient.setColorAt(0.5,m_sceneBackColor );
        gradient.setColorAt(1,m_sceneStyleColor );
        break;
    case 8: //斜下过度
        gradient.setStart(m_sceneRect.x(),m_sceneRect.bottom());
        gradient.setFinalStop(m_sceneRect.right(),m_sceneRect.y());
        gradient.setColorAt(0,m_sceneBackColor );
        gradient.setColorAt(1,m_sceneStyleColor);
        break;
    case 9: //斜下对称过度
        gradient.setStart(m_sceneRect.x(),m_sceneRect.bottom());
        gradient.setFinalStop(m_sceneRect.right(),m_sceneRect.y());
        gradient.setColorAt(0,m_sceneStyleColor );
        gradient.setColorAt(0.5,m_sceneBackColor );
        gradient.setColorAt(1,m_sceneStyleColor );
        break;
    case 10: //右上角辐射

        gradient.setStart(m_sceneRect.right(),m_sceneRect.y());
        gradient.setFinalStop(m_sceneRect.x(),m_sceneRect.bottom());
        gradient.setColorAt(0,m_sceneBackColor );
        gradient.setColorAt(1,m_sceneStyleColor );
        break;
    case 11: //左上角辐射
        gradient.setColorAt(0,m_sceneBackColor );
        gradient.setColorAt(1, m_sceneStyleColor);
        break;
    case 12: //中心辐射
        Radial.setColorAt(0,m_sceneBackColor );
        Radial.setColorAt(1,m_sceneStyleColor );
        break;
    case 13: //待操作
        Radial.setFocalPoint(m_sceneRect.x(),m_sceneRect.center().y());
        Radial.setColorAt(0,m_sceneBackColor );
        Radial.setColorAt(1,m_sceneStyleColor );
        break;
    default:
        break;
    }
    if(pt>13)
        return ;
    else if(pt>=2 && pt <= 11)
        painter->setBrush(gradient);
    else if(pt == 12)
        painter->setBrush(Radial);
    else if(pt==0 || pt==1)
        painter->setBrush(br);
    else
        return ;
}
/*画场景的背景*/
void SamDrawScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(nSelectType == 0)//0表示默认选择
    {
        SetPattern(painter);
        painter->drawRect(m_sceneRect);
    }
    else if(nSelectType == 1)//1表示选择图片作为背景
    {
        if(m_backPicPixmap.isNull() || m_bChangePicPath)
        {
            m_bChangePicPath = false;
            if(!m_picturePath.isEmpty())
            {
                m_backPicPixmap.load(m_picturePath);
                m_backPicPixmap = m_backPicPixmap.convertToFormat(QImage::Format_RGB32);
            }
        }
        if(!m_backPicPixmap.isNull() && !m_sceneRect.isEmpty())
        {
            painter->drawRect(m_sceneRect);
            painter->drawImage(m_sceneRect.toRect(),m_backPicPixmap);
        }
        else
        {
            SetPattern(painter);
            painter->drawRect(m_sceneRect);
        }
    }
    QGraphicsScene::drawBackground(painter,m_sceneRect);//不能去掉这句代码,去掉之后网格功能无效.edit by zqh
}

void SamDrawScene::setSceneRect(qreal x, qreal y, qreal w, qreal h)
{
    m_sceneRect.setRect(x,y,w,h);
    QGraphicsScene::setSceneRect(x,y,w,h);
}
/*end add by tanghaiguo at 2010.11.10*/
void SamDrawScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    LastMousePoint = mouseEvent->scenePos();
    CurMousePoint = mouseEvent->scenePos();
    prMousePoint = mouseEvent->scenePos();
    if(this->selectedItems().size() == 1)
    {
        pwnd->ResetPic(selectedItems().at(0));
    }
 //   if(pwnd->qLanguagecmb->currentIndex() != 0)
  //      pwnd->qLanguagecmb->setCurrentIndex(0);


    foreach(QGraphicsItem *pItem,items())
    {
        if (pItem->type() == SAM_DRAW_OBJECT_PIXMAP)
        {
            QPixmapItem *pTmp = NULL;
            pTmp = dynamic_cast<QPixmapItem *> (pItem);
            pTmp->boundRect = pTmp->sceneBoundingRect();
        }

    }
    if(mouseEvent->button() == Qt::LeftButton)
    {
        bMousePress = true;
        MousePressPos = mouseEvent->scenePos();
        mousePressMove();
        /*调整图元不能超出画图范围开始*/
        bool bSuccess = false;
        qreal temp = 0;
        m_pressVale.clear();
        QGraphicsItem *pItemAt = this->itemAt(MousePressPos);
        bool bSel = false;
        if(pItemAt)
        {
            pItemAt = pItemAt->topLevelItem();
            bSel = pItemAt->isSelected();
            if(mouseEvent->modifiers() == Qt::ControlModifier)
            {
                pItemAt->setSelected(true);
            }
            foreach(QGraphicsItem *pItem, selectedItems())
            {
                if(pItem == pItemAt)
                {
                    bSuccess = true;
                    break;
                }
            }
            if(!bSuccess)
            {
                QRectF rc = pItemAt->sceneBoundingRect();
                temp = MousePressPos.x() - rc.left();
                m_pressVale.push_back(temp);
                temp = MousePressPos.y() - rc.top();
                m_pressVale.push_back(temp);
                temp = MousePressPos.x() - rc.right();
                m_pressVale.push_back(temp);
                temp = MousePressPos.y() - rc.bottom();
                m_pressVale.push_back(temp);
            }
        }

        if(bSuccess && !selectedItems().isEmpty())
        {
            QRectF Rect;
            if(2 == nIsSceneOrWindow)
            {
                Rect = this->m_sceneRect;
            }
            else
            {
                QGraphicsView *pView = this->views().first();
                if(pView)
                {
                    Rect = pView->rect();
                }
                else
                {
                    Rect = this->m_sceneRect;
                }

            }

            QGraphicsItem *pfirstItem = selectedItems().first();
            qreal minX = Rect.right();
            qreal minY = Rect.bottom();
            qreal maxX = Rect.x();
            qreal maxY = Rect.y();
            foreach(QGraphicsItem *pItem, selectedItems())
            {
                this->SetSelectFlag(pItem,false);
                if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
                {
                    continue;
                }
                if(minX>pItem->sceneBoundingRect().left())
                {
                    minX = pItem->sceneBoundingRect().left();
                }
                if(minY>pItem->sceneBoundingRect().top())
                {
                    minY = pItem->sceneBoundingRect().top();
                }
                if(maxX<pItem->sceneBoundingRect().right())
                {
                    maxX = pItem->sceneBoundingRect().right();
                }
                if(maxY<pItem->sceneBoundingRect().bottom())
                {
                    maxY = pItem->sceneBoundingRect().bottom();
                }
            }
            temp = MousePressPos.x() - minX;
            m_pressVale.push_back(temp);
            temp = MousePressPos.y() - minY;
            m_pressVale.push_back(temp);
            temp = MousePressPos.x() - maxX;
            m_pressVale.push_back(temp);
            temp = MousePressPos.y() - maxY;
            m_pressVale.push_back(temp);

            if(selectedItems().size() > 1 && !pBoundRect)
            {
                QColor Color = m_sceneBackColor;
                int r = 0;
                int g = 0;
                int b = 0;
                Color.getRgb(&r,&g,&b);
                Color.setRgb(255 - r,255 - g,255 - b);
                QRectF rect(minX - 1,minY -1 ,maxX - minX +1,maxY - minY +1);
                pBoundRect = new QRectItem(rect);
                pBoundRect->setBrush(Qt::NoBrush);
                //pBoundRect->SetBackColor(m_sceneBackColor);
                pBoundRect->setData(GROUP_NAME_KEY,QVariant("BOUNDRECT"));
                addItem(pBoundRect);
                pBoundRect->setZValue(0);
                pBoundRect->SetLineType(3);
                pBoundRect->SetLineColor(Color);
                pBoundRect->setSelected(true);

            }
        }
        if(pItemAt)
        {
            pItemAt->setSelected(bSel);
        }
        /*调整图元不能超出画图范围结束*/
    }
    if (!this->isActive())
        return;

    SamDrawTool *pTool = SamDrawTool::FindTool(SamDrawTool::s_eDrawActType);
    if (pTool != NULL)
    {
        pTool->mousePressEvent((QGraphicsScene *)this, mouseEvent);
        /* If selection tool, call QGraphicsScene::mousePressEvent
         * depend on the current select mode.
         */
        if (pTool->s_eDrawActType == SAM_DRAW_SELECTION)
        {
            SamDrawSelectTool *pSelectTool =
                    dynamic_cast<SamDrawSelectTool *>(pTool);
            if (pSelectTool != NULL)
            {
                if (pSelectTool->m_eSelectMode != SEL_MOD_SIZE
                    && mouseEvent->button() == Qt::LeftButton)
                {
                    QGraphicsScene::mousePressEvent(mouseEvent);
                }

            }
        }
    }

   // pwnd->PreviewWindow();
    if(is_paste_singleItem)
    {
       //this->views().first()->setCursor(Qt::ArrowCursor);
       //mouseEvent->setAccepted(true);
       //pwnd->PasteItemToScene();
    }

    if (pwnd->pDrawToSceneItem&&(SamDrawTool::s_eDrawActType == SAM_DRAW_ASSY_COMPONENT))
    {
        mouseEvent->setAccepted(true);
    }
    else
    {
        if(is_paste_singleItem)
        {
            MousePressPos = mouseEvent->scenePos();
            bMousePress = true;
            this->views().first()->setCursor(Qt::ArrowCursor);
            mouseEvent->setAccepted(true);
        }
        emit SingleClickItem();
    }
    mousePressEventForUndo(mouseEvent);
}

void SamDrawScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(pwnd->isCompiled)
    {
        event->ignore();
        return ;
    }
    SamDrawTool *pTool = SamDrawTool::FindTool(SamDrawTool::s_eDrawActType);
    if (pTool != NULL)
    {
        pTool->mouseDoubleClickEvent((QGraphicsScene *)this, event);
    }
    QPointF qpClickedPt = event->scenePos();
    QGraphicsItem *pItem;
    if(itemAt(qpClickedPt))
    {
        pItem =TopmostParentItem(itemAt(qpClickedPt)) ;
       emit DoubleClickItem(pItem);
        // pwnd->SlotItemDBClick(pItem);

    }
    event->setAccepted(true);
}

void SamDrawScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!this->isActive())
        return;

    for(int i = 0; i < pShowLineItems.size(); i++)
    {
        this->removeItem(pShowLineItems.at(i));
    }
    pShowLineItems.clear();

    LastMousePoint = CurMousePoint;

    CurMousePoint = event->scenePos();
    moveLineWhenMouseMove();

    /*调整鼠标不移出工作区*/

    /*调整图元不能超出画图范围开始*/

    if ((bMousePress && (!this->selectedItems().isEmpty()))
        && (SamDrawTool::s_eDrawActType == SAM_DRAW_SELECTION))
    {

        CurMousePoint = event->scenePos();
        QGraphicsItem *pfirstItem = this->selectedItems().first();
        qreal minX = pfirstItem->sceneBoundingRect().left();
        qreal minY = pfirstItem->sceneBoundingRect().top();
        qreal maxX = pfirstItem->sceneBoundingRect().right();
        qreal maxY = pfirstItem->sceneBoundingRect().bottom();
        foreach(QGraphicsItem *pItem, this->selectedItems())
        {
            if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
            {
                continue;
            }
            if(minX>pItem->sceneBoundingRect().left())
            {
                minX = pItem->sceneBoundingRect().left();
            }
            if(minY>pItem->sceneBoundingRect().top())
            {
                minY = pItem->sceneBoundingRect().top();
            }
            if(maxX<pItem->sceneBoundingRect().right())
            {
                maxX = pItem->sceneBoundingRect().right();
            }
            if(maxY<pItem->sceneBoundingRect().bottom())
            {
                maxY = pItem->sceneBoundingRect().bottom();
            }
        }
        QCursor icursor;
        QPointF point = event->scenePos();

        //加入移动方向判断防止拖动多个item时在边界无法拖动情况
        QRectF Rect;
        if(2 == nIsSceneOrWindow)
        {
            Rect = this->m_sceneRect;
        }
        else
        {
            QGraphicsView *pView = this->views().first();
            if(pView)
            {
                Rect = pView->sceneRect();
            }
            else
            {
                Rect = this->m_sceneRect;
            }
        }
        if(minX < Rect.left() -1)
        {
            int cursor = Rect.left() + icursor.pos().x() - point.x();
            if(m_pressVale.size() > 0)
            {
                cursor += m_pressVale.at(0);
            }
            icursor.setPos(cursor,icursor.pos().y());
        }
        if(minY < Rect.top() -1)
        {
            int cursor = Rect.top() + icursor.pos().y() - point.y();
            if(m_pressVale.size() > 1)
            {
                cursor += m_pressVale.at(1);
            }
            icursor.setPos(icursor.pos().x(), cursor);
        }
        if(maxX > Rect.right() +1)
        {
            int cursor = Rect.right() + icursor.pos().x() - point.x();
            if(m_pressVale.size() > 2)
            {
                cursor += m_pressVale.at(2);
            }
            icursor.setPos(cursor,icursor.pos().y());
        }
        if(maxY > Rect.bottom() +1)
        {
            int cursor = Rect.bottom() + icursor.pos().y() - point.y();
            if(m_pressVale.size() > 3)
            {
                cursor += m_pressVale.at(3);
            }
            icursor.setPos(icursor.pos().x(), cursor);
        }

        QList <QGraphicsItem*> pItemlist;
        pItemlist = this->TopItems();
        int count = pItemlist.size();
        QList <QGraphicsItem*> pSelectItems;
        pSelectItems = this->selectedItems();

        bool bMove = false;
        SamDrawTool *pTool = SamDrawTool::FindTool(SamDrawTool::s_eDrawActType);
        if (pTool != NULL)
        {
            SamDrawSelectTool *pSelectTool =
                    dynamic_cast<SamDrawSelectTool *>(pTool);
            if (pSelectTool != NULL)
            {
                if (pSelectTool->m_eSelectMode == SEL_MOD_MOVE)
                {
                    bMove = true;
                }

            }
        }
        if(bMove && (pSelectItems.size() >= 1)
            && (pSelectItems.at(0)->flags() & QGraphicsItem::ItemIsMovable)
            && (abs(prMousePoint.x() -event->scenePos().x()) > MIN_MOUSEMOVE
                || abs(prMousePoint.y() -event->scenePos().y()) > MIN_MOUSEMOVE))
        {
            QGraphicsItem *pItem = pSelectItems.at(0);
            int top = pItem->boundingRect().top() + pItem->scenePos().y();
            int bottom = pItem->boundingRect().bottom() + pItem->scenePos().y();
            int left = pItem->boundingRect().left() + pItem->scenePos().x();
            int right = pItem->boundingRect().right() + pItem->scenePos().x();
            foreach(QGraphicsItem *pItem, this->selectedItems())
            {
                if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
                {
                    continue;
                }
                if(left>pItem->sceneBoundingRect().left())
                {
                    left = pItem->sceneBoundingRect().left();
                }
                if(top>pItem->sceneBoundingRect().top())
                {
                    top = pItem->sceneBoundingRect().top();
                }
                if(right<pItem->sceneBoundingRect().right())
                {
                    right = pItem->sceneBoundingRect().right();
                }
                if(bottom<pItem->sceneBoundingRect().bottom())
                {
                    bottom = pItem->sceneBoundingRect().bottom();
                }
            }
            bool bLeft = false;
            bool bTop = false;
            bool bRight = false;
            bool bBottom = false;

            //顶线对齐 向上向下移动
            if(LastMousePoint.y() - CurMousePoint.y() > 0 && !bTop)//向上移动
            {
                QGraphicsItem *pMinItem = NULL;
                for (int i = 0; i<count; i++)
                {
                    if(pItemlist.at(i)->isSelected())
                    {
                        continue;
                    }
                    int y1 = pItemlist.at(i)->sceneBoundingRect().top();
                    if((y1 - top < 0) && (top - y1 < MAX_DISTANCE))
                    {
                        if(pMinItem)
                        {
                            if(top - y1 < top - pMinItem->sceneBoundingRect().top())
                            {
                                pMinItem = pItemlist.at(i);
                            }
                        }
                        else
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                }
                if(pMinItem)
                {
                    int y1 = pMinItem->sceneBoundingRect().top();
                    qreal x1= Rect.left();
                    qreal x2 = Rect.right();

                    QPainterPath *path = new QPainterPath();
                    path->moveTo(x1, y1);
                    path->lineTo(x2, y1);
                    QLineItem *pItem = new QLineItem(*path);
                    pItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
                    pItem->setLineType(3);
                    pShowLineItems.append(pItem);
                    this->addItem(pItem);
                    bTop = true;
                }
            }
            if((LastMousePoint.y() - CurMousePoint.y() < 0) && !bTop)//向下移动
            {
                QGraphicsItem *pMinItem = NULL;
                for (int i = 0; i<count; i++)
                {
                    if(pItemlist.at(i)->isSelected())
                    {
                        continue;
                    }
                    int y1 = pItemlist.at(i)->sceneBoundingRect().top();
                    if((y1 - top > 0) && (y1 - top < MAX_DISTANCE))
                    {
                        if(pMinItem)
                        {
                            if(y1 - top < pMinItem->sceneBoundingRect().top() - top)
                            {
                                pMinItem = pItemlist.at(i);
                            }
                        }
                        else
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                }
                if(pMinItem)
                {
                    int y1 = pMinItem->sceneBoundingRect().top();
                    qreal x1= Rect.left();
                    qreal x2 = Rect.right();

                    QPainterPath *path = new QPainterPath();
                    path->moveTo(x1, y1);
                    path->lineTo(x2, y1);
                    QLineItem *pItem = new QLineItem(*path);
                    pItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
                    pItem->setLineType(3);
                    pShowLineItems.append(pItem);
                    this->addItem(pItem);
                    bTop = true;
                }
            }

            if(LastMousePoint.y() - CurMousePoint.y() > 0 && !bTop)//向上移动
            {
                QGraphicsItem *pMinItem = NULL;
                for (int i = 0; i<count; i++)
                {
                    if(pItemlist.at(i)->isSelected())
                    {
                        continue;
                    }
                    int y1 = pItemlist.at(i)->sceneBoundingRect().bottom();
                    if((y1 - bottom < 0) && (bottom - y1 < MAX_DISTANCE))
                    {
                        if(pMinItem)
                        {
                            if(bottom - y1 < top - pMinItem->sceneBoundingRect().bottom())
                            {
                                pMinItem = pItemlist.at(i);
                            }
                        }
                        else
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                }
                if(pMinItem)
                {
                    int y1 = pMinItem->sceneBoundingRect().bottom();
                    qreal x1= Rect.left();
                    qreal x2 = Rect.right();

                    QPainterPath *path = new QPainterPath();
                    path->moveTo(x1, y1);
                    path->lineTo(x2, y1);
                    QLineItem *pItem = new QLineItem(*path);
                    pItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
                    pItem->setLineType(3);
                    pShowLineItems.append(pItem);
                    this->addItem(pItem);
                    bTop = true;
                }
            }
            if((LastMousePoint.y() - CurMousePoint.y() < 0) && !bTop)//向下移动
            {
                QGraphicsItem *pMinItem = NULL;
                for (int i = 0; i<count; i++)
                {
                    if(pItemlist.at(i)->isSelected())
                    {
                        continue;
                    }
                    int y1 = pItemlist.at(i)->sceneBoundingRect().bottom();
                    if((y1 - bottom > 0) && (y1 - bottom < MAX_DISTANCE))
                    {
                        if(pMinItem)
                        {
                            if(y1 - bottom < pMinItem->sceneBoundingRect().bottom() - bottom)
                            {
                                pMinItem = pItemlist.at(i);
                            }
                        }
                        else
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                }
                if(pMinItem)
                {
                    int y1 = pMinItem->sceneBoundingRect().bottom();
                    qreal x1= Rect.left();
                    qreal x2 = Rect.right();

                    QPainterPath *path = new QPainterPath();
                    path->moveTo(x1, y1);
                    path->lineTo(x2, y1);
                    QLineItem *pItem = new QLineItem(*path);
                    pItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
                    pItem->setLineType(3);
                    pShowLineItems.append(pItem);
                    this->addItem(pItem);
                    bTop = true;
                }
            }

            //for x left
            if((LastMousePoint.x() - CurMousePoint.x() < 0) &&!bRight)//向右移动
            {
                QGraphicsItem *pMinItem = NULL;
                for (int i = 0; i<count; i++)
                {
                    if(pItemlist.at(i)->isSelected())
                    {
                        continue;
                    }
                    int x1 = pItemlist.at(i)->sceneBoundingRect().left();
                    if((x1 - left > 0) && (x1 - left < MAX_DISTANCE))
                    {
                        if(pMinItem)
                        {
                            if(x1 - left < pMinItem->sceneBoundingRect().left() - left)
                            {
                                pMinItem = pItemlist.at(i);
                            }
                        }
                        else
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                }
                if(pMinItem)
                {
                    int x1 = pMinItem->sceneBoundingRect().left();
                    qreal y1= Rect.top();
                    qreal y2 = Rect.bottom();

                    QPainterPath *path = new QPainterPath();
                    path->moveTo(x1, y1);
                    path->lineTo(x1, y2);
                    QLineItem *pItem = new QLineItem(*path);
                    pItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
                    pItem->setLineType(3);
                    pShowLineItems.append(pItem);
                    this->addItem(pItem);
                    bRight = true;
                }
            }
            if((LastMousePoint.x() - CurMousePoint.x() < 0) &&!bRight)//向右移动
            {
                QGraphicsItem *pMinItem = NULL;
                for (int i = 0; i<count; i++)
                {
                    if(pItemlist.at(i)->isSelected())
                    {
                        continue;
                    }
                    int x1 = pItemlist.at(i)->sceneBoundingRect().right();
                    if((x1 - right > 0) && (x1 - right < MAX_DISTANCE))
                    {
                        if(pMinItem)
                        {
                            if(x1 - right < pMinItem->sceneBoundingRect().left() - right)
                            {
                                pMinItem = pItemlist.at(i);
                            }
                        }
                        else
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                }
                if(pMinItem)
                {
                    int x1 = pMinItem->sceneBoundingRect().right();
                    qreal y1= Rect.top();
                    qreal y2 = Rect.bottom();

                    QPainterPath *path = new QPainterPath();
                    path->moveTo(x1, y1);
                    path->lineTo(x1, y2);
                    QLineItem *pItem = new QLineItem(*path);
                    pItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
                    pItem->setLineType(3);
                    pShowLineItems.append(pItem);
                    this->addItem(pItem);
                    bRight = true;
                }
            }

            //for x right //向左移动
            if((LastMousePoint.x() - CurMousePoint.x() > 0) &&!bRight)//向左移动
            {
                QGraphicsItem *pMinItem = NULL;
                for (int i = 0; i<count; i++)
                {
                    if(pItemlist.at(i)->isSelected())
                    {
                        continue;
                    }
                    int x1 = pItemlist.at(i)->sceneBoundingRect().left();
                    if((x1 - left < 0) && (left  - x1 < MAX_DISTANCE))
                    {
                        if(pMinItem)
                        {
                            if(left - x1< left - pMinItem->sceneBoundingRect().left() )
                            {
                                pMinItem = pItemlist.at(i);
                            }
                        }
                        else
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                }
                if(pMinItem)
                {
                    int x1 = pMinItem->sceneBoundingRect().left();
                    qreal y1= Rect.top();
                    qreal y2 = Rect.bottom();

                    QPainterPath *path = new QPainterPath();
                    path->moveTo(x1, y1);
                    path->lineTo(x1, y2);
                    QLineItem *pItem = new QLineItem(*path);
                    pItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
                    pItem->setLineType(3);
                    pShowLineItems.append(pItem);
                    this->addItem(pItem);
                    bRight = true;
                }
            }
            if((LastMousePoint.x() - CurMousePoint.x() > 0) &&!bRight)//向左移动
            {
                QGraphicsItem *pMinItem = NULL;
                for (int i = 0; i<count; i++)
                {
                    if(pItemlist.at(i)->isSelected())
                    {
                        continue;
                    }
                    int x1 = pItemlist.at(i)->sceneBoundingRect().right();
                    if((x1 - right < 0) && (right - x1  < MAX_DISTANCE))
                    {
                        if(pMinItem)
                        {
                            if(right - x1 <right - pMinItem->sceneBoundingRect().right() )
                            {
                                pMinItem = pItemlist.at(i);
                            }
                        }
                        else
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                }
                if(pMinItem)
                {
                    int x1 = pMinItem->sceneBoundingRect().right();
                    qreal y1= Rect.top();
                    qreal y2 = Rect.bottom();

                    QPainterPath *path = new QPainterPath();
                    path->moveTo(x1, y1);
                    path->lineTo(x1, y2);
                    QLineItem *pItem = new QLineItem(*path);
                    pItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
                    pItem->setLineType(3);
                    pShowLineItems.append(pItem);
                    this->addItem(pItem);
                    bRight = true;
                }
            }
        }
        QColor Color = m_sceneBackColor;
        int r = 0;
        int g = 0;
        int b = 0;
        Color.getRgb(&r,&g,&b);
        Color.setRgb(255 - r,255 - g,255 - b);
        for(int i = 0; i < pShowLineItems.size(); i++)
        {
            pShowLineItems.at(i)->setLineColor(Color);
        }
    }
    /*调整图元不能超出画图范围结束*/

    SamDrawTool *pTool = SamDrawTool::FindTool(SamDrawTool::s_eDrawActType);
    if (pTool != NULL)
    {
        pTool->mouseMoveEvent((QGraphicsScene *)this, event);
        QGraphicsScene::mouseMoveEvent(event);

        if (pTool->s_eDrawActType == SAM_DRAW_SELECTION)
        {
            if (true == bMousePress && this->selectedItems().size() > 0)
            {
                this->reBondingTrackers(true);
            }
        }
    }

    else if (SamDrawTool::s_eDrawActType == SAM_DRAW_ASSY_COMPONENT)
    {
        //onReDrawRect(event->scenePos(),(QGraphicsScene *)this);
        pTool = SamDrawTool::FindTool(SAM_DRAW_RECT);//画虚线矩形框
        if (pTool != NULL && bMousePress)
        {
            pTool->onReDrawRect(event->scenePos(),(QGraphicsScene *)this);
        }
        this->views().first()->setCursor(Qt::CrossCursor);
    }

    if(is_paste_singleItem)
    {
        this->views().first()->setCursor(Qt::CrossCursor);
    }

    QString status_control=QString("x=%1,y=%2").arg(event->scenePos().x()).arg(event->scenePos().y());
    pwnd->ui->statusBar->showMessage(status_control);

    //QGraphicsScene::mouseMoveEvent(event);
}

void SamDrawScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(pTableItam)
    {
        //qDebug()<<"tableitem moved "<<bMoveFlag;
        if(pTableItam->data(TABLE_ITEM_MOVE).toInt() == 100 && bMoveFlag)//TABLE_ITEM_MOVE
        {
            TabeRect = pTableItam->sceneBoundingRect();
            pTableItam->setFlag(QGraphicsItem::ItemIsMovable, true);
            QList<QRectF >nItemRects;
            QRectF nRect;
            foreach(QGraphicsItem* cItem,pTableItam->childItems())
            {
                nRect.setTopLeft(cItem->pos());
                nRect.setSize(cItem->boundingRect().size());
                nItemRects.append(nRect);
            }
            //qDebug()<<"tableitem moved "<<nItemRects;
            //qDebug()<<"tableitem moved "<<oItemRects;
            pwnd->undoStack->push(
                    new tableMovedCommand(this,pTableItam,nItemRects,oItemRects));
            pTableItam = NULL;
        }
    }
    if(pTableLine)
    {
        pTableLine = NULL;
        iVHFlag = -1;
    }
    if(pAniMageItam)
    {
        foreach(QGraphicsItem *pItem, pAniMageItam->childItems())
        {
            if( SAM_DRAW_OBJECT_PIXMAP == pItem->type())
            {
                QPixmapItem *pPix = dynamic_cast<QPixmapItem *> (pItem);
                if (pPix)
                {
                    QRectF rc = pAniMageItam->sceneBoundingRect();
                    //pPix->updateSize(rc);
                    //rc = QRectF(rc.top(),rc.left(),rc.width(),nHeight);
                    pPix->updatePic(rc);
                    pPix->updateSize(rc);
                }
            }
        }
        QList<QRectF >nItemRects;
        QRectF nRect;
        foreach(QGraphicsItem* cItem,pAniMageItam->childItems())
        {
            nRect.setTopLeft(cItem->pos());
            nRect.setSize(cItem->boundingRect().size());
            nItemRects.append(nRect);
        }
        pwnd->undoStack->push(
                new tableMovedCommand(this,pAniMageItam,nItemRects,oItemRects));
        pAniMageItam->topLevelItem()->setFlag(QGraphicsItem::ItemIsMovable, true);
        pAniMageItam = NULL;
    }

    if(pBackItam)
    {
        pBackItam = NULL;
    }
    if(pRecipeItem)
    {
        pRecipeItem = NULL;
    }

    for(int i = 0; i < pShowLineItems.size(); i++)
    {
        this->removeItem(pShowLineItems.at(i));
    }
    pShowLineItems.clear();
    MouseReleasePos = mouseEvent->scenePos();
//    if(MouseReleasePos.x() < m_sceneRect.left())
//    {
//        MouseReleasePos.setX(m_sceneRect.left());
//    }
//    if(MouseReleasePos.y() < m_sceneRect.top())
//    {
//        MouseReleasePos.setY(m_sceneRect.top());
//    }
//    if(MouseReleasePos.x() > m_sceneRect.right())
//    {
//        MouseReleasePos.setX(m_sceneRect.right());
//    }
//    if(MouseReleasePos.y() > m_sceneRect.bottom())
//    {
//        MouseReleasePos.setY(m_sceneRect.bottom());
//    }

    if(this->selectedItems().size() == 1)
    {
        pwnd->ResetPic(selectedItems().at(0));
        pwnd->ui->action_copym->setEnabled(true);
    }
    else
        pwnd->ui->action_copym->setEnabled(false);

    if(pBoundRect)
    {
        pBoundRect->setSelected(false);
        removeItem(pBoundRect);
        pBoundRect = NULL;
    }
    foreach(QGraphicsItem *pItem,items())
    {
        if (pItem->type() == SAM_DRAW_OBJECT_PIXMAP)
        {
            QPixmapItem *pTmp = NULL;
            pTmp = dynamic_cast<QPixmapItem *> (pItem);
            pTmp->boundRect = pTmp->sceneBoundingRect();
        }

    }
    if (!this->isActive())
        return;

    if (mouseEvent->button() != Qt::LeftButton && SamDrawTool::s_eDrawActType != SAM_DRAW_ANIMATION)
    {
        if(mouseEvent->scenePos().x()<=this->width()
            &&mouseEvent->scenePos().y()<=this->height()
            &&this->views().at(0)==pwnd->pView)
        {
            QGraphicsItem *pItemAt = itemAt(MouseReleasePos);
            if (pItemAt)
            {
                //clearSelection();
                while (pItemAt->parentItem())
                {
                    pItemAt = pItemAt->parentItem();
                }
                pItemAt->setSelected(true);
            }

            SamDrawScene_rightMenu(mouseEvent);//场景的右键菜单
            return;
        }

    }

    if(this->selectedItems().isEmpty())
    {
        pwnd->lab_control_statusBar->setText(tr("          "));
    }
    else //选择的是用户自定义组合的时候，工具栏上的"拆分"按钮可以使用
    {
        QList<QGraphicsItem *>listitem = selectedItems();
        if(listitem.size() == 1)
        {
            QGraphicsItem *group = listitem.at(0);
            if(group->data(GROUP_TYPE_KEY).toInt() == USER_DEFINE_GROUP)
                pwnd->ui->action_split->setEnabled(true);
        }
    }
    /*调整图元不能超出画图范围开始*/
    if(bMousePress && (!this->selectedItems().isEmpty()))
    {
        bMousePress = false;
        QGraphicsItem *pfirstItem = this->selectedItems().first();
        qreal minX = pfirstItem->sceneBoundingRect().left();
        qreal minY = pfirstItem->sceneBoundingRect().top();
        qreal maxX = pfirstItem->sceneBoundingRect().right();
        qreal maxY = pfirstItem->sceneBoundingRect().bottom();
        foreach(QGraphicsItem *pItem, this->selectedItems())
        {
            if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
            {
                continue;
            }
            if(minX>pItem->sceneBoundingRect().left())
            {
                minX = pItem->sceneBoundingRect().left();
            }
            if(minY>pItem->sceneBoundingRect().top())
            {
                minY = pItem->sceneBoundingRect().top();
            }
            if(maxX<pItem->sceneBoundingRect().right())
            {
                maxX = pItem->sceneBoundingRect().right();
            }
            if(maxY<pItem->sceneBoundingRect().bottom())
            {
                maxY = pItem->sceneBoundingRect().bottom();
            }
        }

        QRectF Rect;
        if(2 == nIsSceneOrWindow)
        {
            Rect = this->m_sceneRect;
        }
        else
        {
            QGraphicsView *pView = this->views().first();
            if(pView)
            {
                Rect = pView->sceneRect();
            }
            else
            {
                Rect = this->m_sceneRect;
            }
        }
        if(minX<Rect.left())
        {
            qreal dx = Rect.left()-minX;
            foreach(QGraphicsItem *pItem, this->selectedItems())
            {
                qreal idx = pItem->scenePos().x()+dx;
                pItem->setPos(idx,pItem->scenePos().y());
            }
        }
        if(minY<Rect.top())
        {
            qreal dy = Rect.top()-minY;
            foreach(QGraphicsItem *pItem, this->selectedItems())
            {
                qreal idy = pItem->scenePos().y()+dy;
                pItem->setPos(pItem->scenePos().x(),idy);
            }
        }
        if(maxX>Rect.right())
        {
            qreal dx = Rect.right() - maxX;
            foreach(QGraphicsItem *pItem, this->selectedItems())
            {
                qreal idx = pItem->scenePos().x()+dx;
                pItem->setPos(idx,pItem->scenePos().y());
            }
        }
        if(maxY>Rect.bottom())
        {
            qreal dy = Rect.bottom()-maxY;
            foreach(QGraphicsItem *pItem, this->selectedItems())
            {
                qreal idy = pItem->scenePos().y()+dy;
                pItem->setPos(pItem->scenePos().x(),idy);
            }
        }
        if(this->selectedItems().size() > 1)
        {
            bool bflag = false;
            foreach(QGraphicsItem *pItem,selectedItems())
            {
                bflag = this->GetSelectFlag(pItem);
                if(bflag)
                {
                    break;
                }
            }
            if(!bflag)
            {
                this->SetSelectFlag(pfirstItem,true);
            }
        }
        this->reBondingTrackers();
    }

    QList <QGraphicsItem*> pItemlist;
    pItemlist = this->TopItems();
    int count = pItemlist.size();
    QList <QGraphicsItem*> pSelectItems;
    pSelectItems = this->selectedItems();

    bool bMove = false;
    SamDrawTool *pTool = SamDrawTool::FindTool(SamDrawTool::s_eDrawActType);
    if (pTool != NULL)
    {
        SamDrawSelectTool *pSelectTool =
                dynamic_cast<SamDrawSelectTool *>(pTool);
        if (pSelectTool != NULL)
        {
            if (pSelectTool->m_eSelectMode == SEL_MOD_MOVE)
            {
                bMove = true;
            }

        }
    }

    if(bMove && (pSelectItems.size() >= 1)
        && (abs(prMousePoint.x() -mouseEvent->scenePos().x()) > MIN_MOUSEMOVE
            || abs(prMousePoint.y() -mouseEvent->scenePos().y()) > MIN_MOUSEMOVE))
    {
        QGraphicsItem *pItem = pSelectItems.at(0);
        int top = pItem->boundingRect().top() + pItem->scenePos().y();
        int bottom = pItem->boundingRect().bottom() + pItem->scenePos().y();
        int left = pItem->boundingRect().left() + pItem->scenePos().x();
        int right = pItem->boundingRect().right() + pItem->scenePos().x();
        foreach(QGraphicsItem *pItem, this->selectedItems())
        {
            if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
            {
                continue;
            }
            if(left>pItem->sceneBoundingRect().left())
            {
                left = pItem->sceneBoundingRect().left();
            }
            if(top>pItem->sceneBoundingRect().top())
            {
                top = pItem->sceneBoundingRect().top();
            }
            if(right<pItem->sceneBoundingRect().right())
            {
                right = pItem->sceneBoundingRect().right();
            }
            if(bottom<pItem->sceneBoundingRect().bottom())
            {
                bottom = pItem->sceneBoundingRect().bottom();
            }
        }

        bool bLeft = false;
        bool bTop = false;
        bool bRight = false;
        bool bBottom = false;

        //顶线对齐 向上向下移动
        if(LastMousePoint.y() - CurMousePoint.y() > 0 && !bTop)//向上移动
        {
            QGraphicsItem *pMinItem = NULL;
            for (int i = 0; i<count; i++)
            {
                if(pItemlist.at(i)->isSelected())
                {
                    continue;
                }
                int y1 = pItemlist.at(i)->sceneBoundingRect().top();
                if((y1 - top < 0) && (top - y1 < MAX_DISTANCE))
                {
                    if(pMinItem)
                    {
                        if(top - y1 < top - pMinItem->sceneBoundingRect().top())
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                    else
                    {
                        pMinItem = pItemlist.at(i);
                    }
                }
            }
            if(pMinItem)
            {
                int y1 = pMinItem->sceneBoundingRect().top();
                int nMove = top - y1;
                foreach(QGraphicsItem *pItem,this->selectedItems())
                {
                    if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
                    {
                        continue;
                    }
                    int nTop = pItem->sceneBoundingRect().top() - nMove;
                    pItem->setY(nTop - pItem->boundingRect().top());
                }
                this->reBondingTrackers();
                bTop = true;
            }
        }
        if((LastMousePoint.y() - CurMousePoint.y() < 0) && !bTop)//向下移动
        {
            QGraphicsItem *pMinItem = NULL;
            for (int i = 0; i<count; i++)
            {
                if(pItemlist.at(i)->isSelected())
                {
                    continue;
                }
                int y1 = pItemlist.at(i)->sceneBoundingRect().top();
                if((y1 - top > 0) && (y1 - top < MAX_DISTANCE))
                {
                    if(pMinItem)
                    {
                        if(y1 - top < pMinItem->sceneBoundingRect().top() - top)
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                    else
                    {
                        pMinItem = pItemlist.at(i);
                    }
                }
            }
            if(pMinItem)
            {
                int y1 = pMinItem->sceneBoundingRect().top();
                int nMove = y1 - top;
                foreach(QGraphicsItem *pItem,this->selectedItems())
                {
                    if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
                    {
                        continue;
                    }
                    int nTop = pItem->sceneBoundingRect().top() + nMove;
                    pItem->setY(nTop - pItem->boundingRect().top());
                }
                this->reBondingTrackers();
                bTop = true;
            }
        }

        if(LastMousePoint.y() - CurMousePoint.y() > 0 && !bTop)//向上移动
        {
            QGraphicsItem *pMinItem = NULL;
            for (int i = 0; i<count; i++)
            {
                if(pItemlist.at(i)->isSelected())
                {
                    continue;
                }
                int y1 = pItemlist.at(i)->sceneBoundingRect().bottom();
                if((y1 - bottom < 0) && (bottom - y1 < MAX_DISTANCE))
                {
                    if(pMinItem)
                    {
                        if(bottom - y1 < top - pMinItem->sceneBoundingRect().bottom())
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                    else
                    {
                        pMinItem = pItemlist.at(i);
                    }
                }
            }
            if(pMinItem)
            {
                int y1 = pMinItem->sceneBoundingRect().bottom();
                int nMove = bottom - y1;
                foreach(QGraphicsItem *pItem,this->selectedItems())
                {
                    if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
                    {
                        continue;
                    }
                    int nBottom = pItem->sceneBoundingRect().top() - nMove;
                    pItem->setY(nBottom - pItem->boundingRect().top());
                }
                this->reBondingTrackers();
                bTop = true;
            }
        }
        if((LastMousePoint.y() - CurMousePoint.y() < 0) && !bTop)//向下移动
        {
            QGraphicsItem *pMinItem = NULL;
            for (int i = 0; i<count; i++)
            {
                if(pItemlist.at(i)->isSelected())
                {
                    continue;
                }
                int y1 = pItemlist.at(i)->sceneBoundingRect().bottom();
                if((y1 - bottom > 0) && (y1 - bottom < MAX_DISTANCE))
                {
                    if(pMinItem)
                    {
                        if(y1 - bottom < pMinItem->sceneBoundingRect().bottom() - bottom)
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                    else
                    {
                        pMinItem = pItemlist.at(i);
                    }
                }
            }
            if(pMinItem)
            {
                int y1 = pMinItem->sceneBoundingRect().bottom();
                int nMove = y1 - bottom;
                foreach(QGraphicsItem *pItem,this->selectedItems())
                {
                    if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
                    {
                        continue;
                    }
                    int nBottom = pItem->sceneBoundingRect().bottom() + nMove;
                    pItem->setY(nBottom - pItem->boundingRect().bottom());
                }
                //pItem->setY(y1 - pItem->boundingRect().bottom());
                this->reBondingTrackers();
                bTop = true;
            }
        }

        //for x left
        if((LastMousePoint.x() - CurMousePoint.x() < 0) &&!bRight)//向右移动
        {
            QGraphicsItem *pMinItem = NULL;
            for (int i = 0; i<count; i++)
            {
                if(pItemlist.at(i)->isSelected())
                {
                    continue;
                }
                int x1 = pItemlist.at(i)->sceneBoundingRect().left();
                if((x1 - left > 0) && (x1 - left < MAX_DISTANCE))
                {
                    if(pMinItem)
                    {
                        if(x1 - left < pMinItem->sceneBoundingRect().left() - left)
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                    else
                    {
                        pMinItem = pItemlist.at(i);
                    }
                }
            }
            if(pMinItem)
            {
                int x1 = pMinItem->sceneBoundingRect().left();
                int nMove = x1 - left;
                foreach(QGraphicsItem *pItem,this->selectedItems())
                {
                    if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
                    {
                        continue;
                    }
                    int nLeft = pItem->sceneBoundingRect().left() + nMove;
                    pItem->setX(nLeft - pItem->boundingRect().left());
                }
                //pItem->setX(x1 - pItem->boundingRect().left());
                this->reBondingTrackers();
                bRight = true;
            }
        }
        if((LastMousePoint.x() - CurMousePoint.x() < 0) &&!bRight)//向右移动
        {
            QGraphicsItem *pMinItem = NULL;
            for (int i = 0; i<count; i++)
            {
                if(pItemlist.at(i)->isSelected())
                {
                    continue;
                }
                int x1 = pItemlist.at(i)->sceneBoundingRect().right();
                if((x1 - right > 0) && (x1 - right < MAX_DISTANCE))
                {
                    if(pMinItem)
                    {
                        if(x1 - right < pMinItem->sceneBoundingRect().left() - right)
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                    else
                    {
                        pMinItem = pItemlist.at(i);
                    }
                }
            }
            if(pMinItem)
            {
                int x1 = pMinItem->sceneBoundingRect().right();
                int nMove = x1 - right;
                foreach(QGraphicsItem *pItem,this->selectedItems())
                {
                    if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
                    {
                        continue;
                    }
                    int nRight = pItem->sceneBoundingRect().right() + nMove;
                    pItem->setX(nRight - pItem->boundingRect().right());
                }
                //pItem->setX(x1 - pItem->boundingRect().right());
                this->reBondingTrackers();
                bRight = true;
            }
        }

        //for x right //向左移动
        if((LastMousePoint.x() - CurMousePoint.x() > 0) &&!bRight)//向左移动
        {
            QGraphicsItem *pMinItem = NULL;
            for (int i = 0; i<count; i++)
            {
                if(pItemlist.at(i)->isSelected())
                {
                    continue;
                }
                int x1 = pItemlist.at(i)->sceneBoundingRect().left();
                if((x1 - left < 0) && (left  - x1 < MAX_DISTANCE))
                {
                    if(pMinItem)
                    {
                        if(left - x1< left - pMinItem->sceneBoundingRect().left() )
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                    else
                    {
                        pMinItem = pItemlist.at(i);
                    }
                }
            }
            if(pMinItem)
            {
                int x1 = pMinItem->sceneBoundingRect().left();
                int nMove = left - x1;
                foreach(QGraphicsItem *pItem,this->selectedItems())
                {
                    if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
                    {
                        continue;
                    }
                    int nLeft = pItem->sceneBoundingRect().left() - nMove;
                    pItem->setX(nLeft - pItem->boundingRect().left());
                }
                //pItem->setX(x1 - pItem->boundingRect().left());
                this->reBondingTrackers();
                bRight = true;
            }
        }
        if((LastMousePoint.x() - CurMousePoint.x() > 0) &&!bRight)//向左移动
        {
            QGraphicsItem *pMinItem = NULL;
            for (int i = 0; i<count; i++)
            {
                if(pItemlist.at(i)->isSelected())
                {
                    continue;
                }
                int x1 = pItemlist.at(i)->sceneBoundingRect().right();
                if((x1 - right < 0) && (right - x1  < MAX_DISTANCE))
                {
                    if(pMinItem)
                    {
                        if(right - x1 <right - pMinItem->sceneBoundingRect().right() )
                        {
                            pMinItem = pItemlist.at(i);
                        }
                    }
                    else
                    {
                        pMinItem = pItemlist.at(i);
                    }
                }
            }
            if(pMinItem)
            {
                int x1 = pMinItem->sceneBoundingRect().right();
                int nMove = right - x1;
                foreach(QGraphicsItem *pItem,this->selectedItems())
                {
                    if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
                    {
                        continue;
                    }
                    int nRight = pItem->sceneBoundingRect().right() - nMove;
                    pItem->setX(nRight - pItem->boundingRect().right());
                }
                //pItem->setX(x1 - pItem->boundingRect().right());
                this->reBondingTrackers();
                bRight = true;
            }
        }
    }

    /*调整图元不能超出画图范围结束*/
    //pTool = SamDrawTool::FindTool(SamDrawTool::s_eDrawActType);
    if (pTool != NULL)
    {
        pTool->mouseReleaseEvent((QGraphicsScene *)this, mouseEvent);
    }
    else if (SamDrawTool::s_eDrawActType == SAM_DRAW_ASSY_COMPONENT)
    {
        if(mouseEvent->button() == Qt::LeftButton)
            pwnd->AddItemToScene();
        this->views().first()->setCursor(Qt::ArrowCursor);
        SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;

        pTool = SamDrawTool::FindTool(SAM_DRAW_RECT);//去掉虚线矩形框
        if (pTool != NULL)
        {
            if(pTool->pBackRect)
            {
                this->removeItem(pTool->pBackRect);
                pTool->pBackRect = NULL;
            }
        }
        //mouseEvent->setAccepted(true);
        qDebug()<<"clicked end";
    }

    mouseReleaseEventForUndo(this,mouseEvent);
    QList <QGraphicsItem*> pItems = this->selectedItems();
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
    QGraphicsItem *pItemAt = this->itemAt(MousePressPos);
    if(mouseEvent->modifiers() == Qt::ControlModifier)
    {
        if(this->selectedItems().size() > 1)
        {
            QGraphicsItem* pItem = this->selectedItems().first();
            foreach(QGraphicsItem* pItem,this->selectedItems())
            {
                this->SetSelectFlag(pItem,false);
            }
            this->SetSelectFlag(pItem,true);
            this->reBondingTrackers(true);
        }
        else if(this->selectedItems().size() == 1)
        {
            QGraphicsItem* pItem = this->selectedItems().first();
            this->SetSelectFlag(pItem,false);
            this->reBondingTrackers(true);
        }
    }
    else
    {
        if(pItemAt)
        {
            pItemAt = pItemAt->topLevelItem();
            if((pItems.contains(pItemAt) && pItems.size() > 1))
            {
                foreach(QGraphicsItem* pItem,pItems)
                {
                    pItem->setSelected(true);
                    this->SetSelectFlag(pItem,false);
                }
                this->SetSelectFlag(pItemAt,true);
                this->reBondingTrackers(true);
            }
        }
    }

    this->update();
    pwnd->PreviewWindow();
    bMousePress = false;
    //upDate_stutas();
}

void SamDrawScene::wheelEvent ( QGraphicsSceneWheelEvent * wheelEvent )
{
    int nDelta = wheelEvent->delta();
    //qDebug()<<"nDelta = "<<nDelta;
    if(wheelEvent->modifiers() == Qt::ControlModifier)
    {
        if(nDelta < 0)//向下
        {
            pwnd->OnSetZoomSmall();
        }
        else if(nDelta > 0)//向上
        {
            pwnd->OnSetZoomEnlarge();
        }
    }
    QGraphicsScene::wheelEvent(wheelEvent);
}

void SamDrawScene::selItemsChanged()
{
    //qDebug()<< "selItemsChanged start";
    if (this->isActive())
    {
        m_qvecPrimaryItems.clear();
        foreach(QGraphicsItem *pselItem, this->TopItems())
        {
            if (SAM_DRAW_OBJECT_LOCK == pselItem->type()
                || pselItem->type() == SAM_DRAW_OBJECT_TRACKER
                        || pselItem->type() == 65536 + 998
                        || pselItem->type() == 65536 + 997) continue;
			if (pselItem->parentItem() != NULL) continue;
            m_qvecPrimaryItems.push_back(pselItem);
        }
    }

        /*visiable/unvisiable/rebonding trackers*/
        this->reBondingTrackers();

        multiStatus();
    //qDebug()<< "selItemsChanged ing";
    upDate_stutas();
    //qDebug()<< "selItemsChanged end";
}

void SamDrawScene::multiStatus()
{
    if(pwnd->isCompiled ||this->selectedItems().isEmpty())
    {
        //qDebug()<< "upDate_stutas -- isCompiled";
        return;
    }

    QList<QGraphicsItem*> items;
    short maxStatus = 0;
    short state = pwnd->statusButtoncmb->currentIndex();
    if(state < 0)
    {
        state = 0;
    }
    items = this->items();
    pwnd->statusButtoncmb->clear();//多状态更新
    //Items = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->items();//当前页面所有的item
    foreach(QGraphicsItem *pItem, items)
    {
        if(!pItem)
        {
            continue;
        }

        if(SAM_DRAW_OBJECT_GROUP == pItem->type())
        {
            if(pItem->parentItem() == 0 && pItem->type() != SAM_DRAW_OBJECT_TRACKER && pItem->type() != SAM_DRAW_OBJECT_LOCK)
            {
                QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
                QStringList ls = item->getItemStates();
                int nItemStatu = ls.size();
                if(nItemStatu > maxStatus)
                {
                    maxStatus = nItemStatu;
                }
            }
        }
    }

    if(maxStatus <= state)
    {
        state = 0;
    }
    disconnect(pwnd->statusButtoncmb,SIGNAL(currentIndexChanged(int)),pwnd,SLOT(onFrmStatecmbChange(int)));
    pwnd->statusButtoncmb->setEnabled(true);
    int k = 0;
    while(maxStatus > 0)
    {
        QString str =  tr("状态") + QString::number(k);
        pwnd->statusButtoncmb->addItem(str);
        k++;
        maxStatus--;
    }
    pwnd->statusButtoncmb->setCurrentIndex(state);
    connect(pwnd->statusButtoncmb,SIGNAL(currentIndexChanged(int)),pwnd,SLOT(onFrmStatecmbChange(int)));

    //pwnd->AddCurrentItemStatusList(pItem, k);

    /*if(items.size() > 1 || items.size() == 0)
    {
        pwnd->statusButtoncmb->setEnabled(false);
    }
    else
    {
         pItem = this->selectedItems().first();

         if(SAM_DRAW_OBJECT_GROUP == pItem->type())
         {
             pwnd->statusButtoncmb->setEnabled(true);

             QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
             int k = item->getCurrentState();
             if(k == -1)
             {
                 return;
             }
             pwnd->AddCurrentItemStatusList(pItem, k);
         }
         else
         {
             pwnd->statusButtoncmb->setEnabled(false);
         }
    }*/
}

void SamDrawScene::reBondingTrackers(bool bKeepSelected)
{
    QRectBasicItem *pRect     = 0;
    QElipseBasicItem *pElipse = 0;
    QLineBasicItem *pLine     = 0;
    QPolygonBasicItem *pPolygon   = 0;
    QFoldLineBasicItem *pFoldLine = 0;
    QFreeLineBasicItem *pFreeLine = 0;
    QItemGroup *pItemGroup   = 0;
    QLineCircleBasicItem *pLineCircle = 0;   //add by tanghaiguo
    QSimpleTextItem *pText = 0;
    QRoundedRectBasic *pRoundedRect = 0;
    QArcBasicItem *pArc = 0;

    QRectItem *pRectOld    = 0;
    QElipseItem *pElipseOld = 0;
    QLineItem *pLineOld     = 0;
    QPolygonItem *pPolygonOld   = 0;
    QFoldLineItem *pFoldLineOld = 0;
    QFreeLineItem *pFreeLineOld = 0;
    QLineCircleItem *pLineCircleOld = 0;   //add by tanghaiguo
    QRoundedRect *pRoundedRectOld = 0;
    QArcItem *pArcOld = 0;

    bool bSelected = false;
    QRectF qrcBndRect;

    foreach(QGraphicsItem *pselItem, m_qvecPrimaryItems)
    {
        qrcBndRect = pselItem->sceneBoundingRect();
        bSelected = pselItem->isSelected();
        bool bIsLocked = !(pselItem->flags() & QGraphicsItem::ItemIsMovable);
        switch (pselItem->type())
        {
        case SAM_DRAW_OBJECT_RECT_NEW:
            pRect = dynamic_cast<QRectBasicItem *> (pselItem);
            if (pRect)
            {
                if("BOUNDRECT" == pRect->data(GROUP_NAME_KEY).toString())
                {
                    continue;
                }
                if (bSelected)
                {
                    pRect->refreshTrackers(qrcBndRect, this);
                    pRect->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pRect->SetselectFlag(false);
                    }
                    pRect->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_ELIPSE_NEW:
            pElipse = dynamic_cast<QElipseBasicItem *> (pselItem);
            if (pElipse)
            {
                if (bSelected)
                {
                    pElipse->refreshTrackers(qrcBndRect, this);
                    pElipse->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pElipse->SetselectFlag(false);
                    }
                    pElipse->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINE_NEW:
            pLine = dynamic_cast<QLineBasicItem *> (pselItem);
            if (pLine)
            {
                if (bSelected)
                {
                    //pLine->refreshLineTrackers();
                    pLine->refreshPathTrackers(this);
                    pLine->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pLine->SetselectFlag(false);
                    }
                    pLine->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_POLYGON_NEW:
            pPolygon = dynamic_cast<QPolygonBasicItem *> (pselItem);
            if (pPolygon)
            {
                if (bSelected)
                {
                    pPolygon->refreshPolygonTrackers(this);
                    pPolygon->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pPolygon->SetselectFlag(false);
                    }
                    pPolygon->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:
            pFoldLine = dynamic_cast<QFoldLineBasicItem *> (pselItem);
            if (pFoldLine)
            {
                if (bSelected)
                {
                    pFoldLine->refreshPathTrackers(this);
                    pFoldLine->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }

                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pFoldLine->SetselectFlag(false);
                    }
                    pFoldLine->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_FREELINE_NEW:
            pFreeLine = dynamic_cast<QFreeLineBasicItem *> (pselItem);
            if (pFreeLine)
            {
                if (bSelected)
                {
                    pFreeLine->refreshPathTrackers(this);
                    pFreeLine->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }

                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pFreeLine->SetselectFlag(false);
                    }
                    pFreeLine->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_GROUP:
            pItemGroup = dynamic_cast<QItemGroup *> (pselItem);
            if (pItemGroup)
            {
                if (bSelected)
                {
                    pItemGroup->refreshTrackers(qrcBndRect, this);
                    pItemGroup->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pItemGroup->SetselectFlag(false);
                    }
                    pItemGroup->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
            pLineCircle = dynamic_cast<QLineCircleBasicItem *> (pselItem);
            if (pLineCircle)
            {
                if (bSelected)
                {
                    pLineCircle->refreshLineCircleTrackers(this);
                    pLineCircle->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pLineCircle->SetselectFlag(false);
                    }
                    pLineCircle->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_TEXT:
            pText = dynamic_cast<QSimpleTextItem *> (pselItem);
            if (pText)
            {
                if (bSelected)
                {
                    pText->refreshTrackers(qrcBndRect, this);
                    pText->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pText->SetselectFlag(false);
                    }
                    pText->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
            pRoundedRect = dynamic_cast<QRoundedRectBasic *> (pselItem);
            if (pRoundedRect)
            {
                if (bSelected)
                {
                    pRoundedRect->refreshTrackers(qrcBndRect, this);
                    pRoundedRect->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pRoundedRect->SetselectFlag(false);
                    }
                    pRoundedRect->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_ARC_NEW:
            pArc = dynamic_cast<QArcBasicItem *> (pselItem);
            if (pArc)
            {
                if (bSelected)
                {
                    qrcBndRect = pArc->getEllipseRect();
                    qrcBndRect = pArc->mapRectToScene(qrcBndRect);
                    pArc->refreshTrackers(qrcBndRect, this);
                    pArc->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pArc->SetselectFlag(false);
                    }
                    pArc->setTrackersVisiable(bSelected);
                }
            }
            break;
 ///////////////////wxy add start
        case SAM_DRAW_OBJECT_RECT:
            pRectOld = dynamic_cast<QRectItem *> (pselItem);
            if (pRectOld)
            {
                if("BOUNDRECT" == pRectOld->data(GROUP_NAME_KEY).toString())
                {
                    continue;
                }
                if (bSelected)
                {
                    pRectOld->refreshTrackers(qrcBndRect, this);
                    pRectOld->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pRectOld->SetselectFlag(false);
                    }
                    pRectOld->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_ELIPSE:
            pElipseOld = dynamic_cast<QElipseItem *> (pselItem);
            if (pElipseOld)
            {
                if (bSelected)
                {
                    pElipseOld->refreshTrackers(qrcBndRect, this);
                    pElipseOld->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pElipseOld->SetselectFlag(false);
                    }
                    pElipseOld->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINE:
            pLineOld = dynamic_cast<QLineItem *> (pselItem);
            if (pLineOld)
            {
                if (bSelected)
                {
                    //pLine->refreshLineTrackers();
                    pLineOld->refreshPathTrackers(this);
                    pLineOld->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pLineOld->SetselectFlag(false);
                    }
                    pLineOld->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_POLYGON:
            pPolygonOld = dynamic_cast<QPolygonItem *> (pselItem);
            if (pPolygonOld)
            {
                if (bSelected)
                {
                    pPolygonOld->refreshPolygonTrackers(this);
                    pPolygonOld->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pPolygonOld->SetselectFlag(false);
                    }
                    pPolygonOld->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_FOLDLINE:
            pFoldLineOld = dynamic_cast<QFoldLineItem *> (pselItem);
            if (pFoldLineOld)
            {
                if (bSelected)
                {
                    pFoldLineOld->refreshPathTrackers(this);
                    pFoldLineOld->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }

                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pFoldLineOld->SetselectFlag(false);
                    }
                    pFoldLineOld->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_FREELINE:
            pFreeLineOld = dynamic_cast<QFreeLineItem *> (pselItem);
            if (pFreeLineOld)
            {
                if (bSelected)
                {
                    pFreeLineOld->refreshPathTrackers(this);
                    pFreeLineOld->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }

                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pFreeLineOld->SetselectFlag(false);
                    }
                    pFreeLineOld->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINECIRCLE:
            pLineCircleOld = dynamic_cast<QLineCircleItem *> (pselItem);
            if (pLineCircleOld)
            {
                if (bSelected)
                {
                    pLineCircleOld->refreshLineCircleTrackers(this);
                    pLineCircleOld->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pLineCircleOld->SetselectFlag(false);
                    }
                    pLineCircleOld->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
            pRoundedRectOld = dynamic_cast<QRoundedRect *> (pselItem);
            if (pRoundedRectOld)
            {
                if (bSelected)
                {
                    pRoundedRectOld->refreshTrackers(qrcBndRect, this);
                    pRoundedRectOld->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pRoundedRectOld->SetselectFlag(false);
                    }
                    pRoundedRectOld->setTrackersVisiable(bSelected);
                }
            }
            break;
        case SAM_DRAW_OBJECT_ARC:
            pArcOld = dynamic_cast<QArcItem *> (pselItem);
            if (pArcOld)
            {
                if (bSelected)
                {
                    qrcBndRect = pArcOld->getEllipseRect();
                    qrcBndRect = pArcOld->mapRectToScene(qrcBndRect);
                    pArcOld->refreshTrackers(qrcBndRect, this);
                    pArcOld->refreshLockRect(qrcBndRect.topLeft(),this,bIsLocked);
                }
                if (bKeepSelected == false)
                {
                    if(!bSelected)
                    {
                        pArcOld->SetselectFlag(false);
                    }
                    pArcOld->setTrackersVisiable(bSelected);
                }
            }
            break;
 //////////////////wxy add end
        default:
            break;
        }
    }
}
bool SamDrawScene::event ( QEvent * event )
{
    QKeyEvent *keyevent = dynamic_cast<QKeyEvent*>(event);
    if(keyevent)
    {
        if(keyevent->key() == Qt::Key_Z && keyevent->modifiers() == Qt::ControlModifier)
        {
            SamDrawTool *pTool = NULL;
            pTool = SamDrawTool::FindTool(SamDrawTool::s_eDrawActType);
            if (pTool != NULL)
            {
                pTool->onCancel(this);

            }
            else if (SamDrawTool::s_eDrawActType == SAM_DRAW_ASSY_COMPONENT)
            {
                SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
                this->views().first()->setCursor(Qt::ArrowCursor);
            }
        }
    }
    if(!pwnd->FocusInStatusbar() && this->isActive())
    {
        upDate_stutas();
    }
    return QGraphicsScene::event(event);
}
void SamDrawScene::keyPressEvent(QKeyEvent *event)
{

    if (!this->isActive())
        return;
    /*****************
      *ADD By Dylan
      *2012-2-28
      *以下
      ****************/
    if ((event->modifiers() == Qt::ShiftModifier )&& (event->key()==Qt::Key_Left))
    {//Shift+←
        QList <QGraphicsItem *> selList;
        selList = this->selectedItems();
        QRectF rect,rc1;
        if (selList.size() != 0)
        {
            foreach(QGraphicsItem * pItem,selList)
            {
                if(pItem->data(GROUP_TYPE_KEY)==GROUP_TYPE_TIMER)//定时器不改变大小
                {
                    continue;
                }
                rect = pItem->sceneBoundingRect();
                rc1 = pItem->boundingRect();
                if(pItem->flags() & QGraphicsItem::ItemIsMovable)
                    //pItem->setPos(rect.x()-rc1.x()+1,rect.y()-rc1.y());
                {
                    if(pItem->sceneBoundingRect().width()-1<=0)
                    {
                        continue;
                    }
                    QGroupItem *group;
                    group=new QGroupItem(pItem);
                    group->SetWidth(pItem->sceneBoundingRect().width()-1);
                    delete group;
                    group=NULL;
                }
            }
            this->reBondingTrackers();
            pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
            pwnd->is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
        }
        this->update();
        return;
    }   if ((event->modifiers() == Qt::ShiftModifier )&& (event->key()==Qt::Key_Right))
    {//Shift+→
        QList <QGraphicsItem *> selList;
        selList = this->selectedItems();
        QRectF rect,rc1;
        if (selList.size() != 0)
        {
            foreach(QGraphicsItem * pItem,selList)
            {
                if(pItem->data(GROUP_TYPE_KEY)==GROUP_TYPE_TIMER)//定时器不改变大小
                {
                    continue;
                }
                rect = pItem->sceneBoundingRect();
                rc1 = pItem->boundingRect();
                if(pItem->flags() & QGraphicsItem::ItemIsMovable)
                    //pItem->setPos(rect.x()-rc1.x()+1,rect.y()-rc1.y());
                {
                    if(pItem->sceneBoundingRect().right() >= this->m_sceneRect.right())
                    {
                        continue;
                    }
                    QGroupItem *group;
                    group=new QGroupItem(pItem);
                    group->SetWidth(pItem->sceneBoundingRect().width()+1);
                    delete group;
                    group=NULL;
                }
            }
            this->reBondingTrackers();
            pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
            pwnd->is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
        }
        this->update();
        return;
    }
    if ((event->modifiers() == Qt::ShiftModifier )&& (event->key()==Qt::Key_Up))
    {//Shift+↑
        QList <QGraphicsItem *> selList;
        selList = this->selectedItems();
        QRectF rect,rc1;
        if (selList.size() != 0)
        {
            foreach(QGraphicsItem * pItem,selList)
            {
                if(pItem->data(GROUP_TYPE_KEY)==GROUP_TYPE_TIMER)//定时器不改变大小
                {
                    continue;
                }
                rect = pItem->sceneBoundingRect();
                rc1 = pItem->boundingRect();
                if(pItem->flags() & QGraphicsItem::ItemIsMovable)
                    //pItem->setPos(rect.x()-rc1.x()+1,rect.y()-rc1.y());
                {

                    if(pItem->sceneBoundingRect().height()-1<=0)
                    {
                        continue;
                    }
                    QGroupItem *group;
                     group=new QGroupItem(pItem);
                   group->SetHeigth(pItem->sceneBoundingRect().height()-1);
                   delete group;
                   group=NULL;
                }
            }
            this->reBondingTrackers();
            pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
            pwnd->is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
        }
        this->update();
        return;
    }
    if ((event->modifiers() == Qt::ShiftModifier )&& (event->key()==Qt::Key_Down))
    {//Shift+↓
        QList <QGraphicsItem *> selList;
        selList = this->selectedItems();
        QRectF rect,rc1;
        if (selList.size() != 0)
        {
            foreach(QGraphicsItem * pItem,selList)
            {
                if(pItem->data(GROUP_TYPE_KEY)==GROUP_TYPE_TIMER)//定时器不改变大小
                {
                    continue;
                }
                rect = pItem->sceneBoundingRect();
                rc1 = pItem->boundingRect();
                if(pItem->flags() & QGraphicsItem::ItemIsMovable)
                    //pItem->setPos(rect.x()-rc1.x()+1,rect.y()-rc1.y());
                {
                    if(pItem->sceneBoundingRect().bottom() >= this->m_sceneRect.bottom())
                    {
                        continue;
                    }
                    QGroupItem *group;
                    group=new QGroupItem(pItem);
                    group->SetHeigth(pItem->sceneBoundingRect().height()+1);
                    delete group;
                    group=NULL;
                }
            }
            this->reBondingTrackers();
            pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
            pwnd->is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
        }
        this->update();
        return;
    }
    ///////////////////以上 2012-2-28 Dylan
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Down
       || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
    {
        movingItems.clear();
        movingItems = this->selectedItems();
        if(!movingItems.isEmpty())
        {
            oldPoss.clear();
            foreach(QGraphicsItem * pItem,movingItems)
            {
                oldPoss<< pItem->pos();
            }
        }
    }
    QGraphicsItem *pfirstItem = NULL;
    if(this->selectedItems().size()>0)
    {
        pfirstItem = this->selectedItems().first();
    }
    qreal minX  = 0;
    qreal minY  = 0;
    qreal maxX = 0;
    qreal maxY = 0 ;
    if(pfirstItem)
    {
        minX = pfirstItem->sceneBoundingRect().left();
        minY = pfirstItem->sceneBoundingRect().top();
        maxX = pfirstItem->sceneBoundingRect().right();
        maxY = pfirstItem->sceneBoundingRect().bottom();
        foreach(QGraphicsItem *pItem, this->selectedItems())
        {
            if(minX>pItem->sceneBoundingRect().left())
            {
                minX = pItem->sceneBoundingRect().left();
            }
            if(minY>pItem->sceneBoundingRect().top())
            {
                minY = pItem->sceneBoundingRect().top();
            }
            if(maxX<pItem->sceneBoundingRect().right())
            {
                maxX = pItem->sceneBoundingRect().right();
            }
            if(maxY<pItem->sceneBoundingRect().bottom())
            {
                maxY = pItem->sceneBoundingRect().bottom();
            }
        }
    }

    if (event->key() == Qt::Key_Escape)
    {
        SamDrawTool *pTool = NULL;
        pTool = SamDrawTool::FindTool(SamDrawTool::s_eDrawActType);
        if (pTool != NULL)
        {
            pTool->onCancel(this);
        }
        else if (SamDrawTool::s_eDrawActType == SAM_DRAW_ASSY_COMPONENT)
        {
            SamDrawTool::s_eDrawActType = SAM_DRAW_SELECTION;
            this->views().first()->setCursor(Qt::ArrowCursor);
        }
    }
    else if (event->key() == Qt::Key_Up &&(minY > this->m_sceneRect.top()))
    {
        QList <QGraphicsItem *> selList;
        selList = this->selectedItems();
        QRectF rect,rc1;
        if (selList.size() != 0)
        {
            foreach(QGraphicsItem * pItem,selList)
            {
                rect = pItem->sceneBoundingRect();
                rc1 = pItem->boundingRect();
                if(pItem->flags() & QGraphicsItem::ItemIsMovable)
                {
                    pItem->setPos(rect.x()-rc1.x(),rect.y()-rc1.y()-1);
                }

            }
            this->reBondingTrackers();
            pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
            pwnd->is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
        }
        this->update();
        return;
    }
    else if (event->key() == Qt::Key_Down &&(maxY < (pwnd->pView != NULL? pwnd->pView->sceneRect().bottom() : this->m_sceneRect.bottom())))
    {
        QList <QGraphicsItem *> selList;
        selList = this->selectedItems();
        QRectF rect,rc1;
        if (selList.size() != 0)
        {
            foreach(QGraphicsItem * pItem,selList)
            {
                rect = pItem->sceneBoundingRect();
                rc1 = pItem->boundingRect();
                if(pItem->flags() & QGraphicsItem::ItemIsMovable)
                    pItem->setPos(rect.x()-rc1.x(),rect.y()-rc1.y()+1);
            }
            this->reBondingTrackers();
            pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
            pwnd->is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
        }
        this->update();
        return;
    }
    else if (event->key() == Qt::Key_Left &&(minX > this->m_sceneRect.left()))
    {
        QList <QGraphicsItem *> selList;
        selList = this->selectedItems();
        QRectF rect,rc1;
        if (selList.size() != 0)
        {
            foreach(QGraphicsItem * pItem,selList)
            {
                rect = pItem->sceneBoundingRect();
                rc1 = pItem->boundingRect();
                if(pItem->flags() & QGraphicsItem::ItemIsMovable)
                    pItem->setPos(rect.x()-rc1.x()-1,rect.y()-rc1.y());
            }
            this->reBondingTrackers();
            pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
            pwnd->is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
        }
        this->update();
        return;
    }
    else if (event->key() == Qt::Key_Right &&(maxX < (pwnd->pView != NULL? pwnd->pView->sceneRect().right() : this->m_sceneRect.right())))
    {
        QList <QGraphicsItem *> selList;
        selList = this->selectedItems();
        QRectF rect,rc1;
        if (selList.size() != 0)
        {
            foreach(QGraphicsItem * pItem,selList)
            {
                rect = pItem->sceneBoundingRect();
                rc1 = pItem->boundingRect();
                if(pItem->flags() & QGraphicsItem::ItemIsMovable)
                    pItem->setPos(rect.x()-rc1.x()+1,rect.y()-rc1.y());
            }
            this->reBondingTrackers();
            pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
            pwnd->is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
        }
        this->update();
        return;
    }
    else if(event->key() == Qt::Key_End || event->key() == Qt::Key_Tab)
    {
        QGraphicsItem * pTmp = NULL;
        QList <QGraphicsItem *> selList;
        selList = this->selectedItems();
        QList<QGraphicsItem *> list = this->TopItems();
        int a = list.size();
        if (selList.size() != 1)
        {
            if(a != 0)
            {
                list.at(0)->setSelected(true);
            }

            return;
        }
        pTmp = selList.at(0);

        //QList<QGraphicsItem *> TopList ;
        QGraphicsItem * pNextselItem = NULL;
        int i;

        qDebug()<<a<<"items in scene";


        for (i = 0; i < a; i++)
        {
            if (list.at(i) == pTmp)
            {
                if (i == list.size()-1)//是最后一个
                {
                    pNextselItem = list.at(0);
                }
                else
                {
                    pNextselItem = list.at(i+1);
                }
                pTmp->setSelected (false);
                pNextselItem->setSelected (true);
                break;
            }
        }
        this->update();
    }//


    else if(event->key() == Qt::Key_A && (event->modifiers() ==(Qt::ShiftModifier|Qt::ControlModifier) ))
    {

        QPainterPath path;
        path.addRect(0,0,width(),height());
        setSelectionArea(path);

    }

    QGraphicsScene::keyPressEvent(event);
}
void SamDrawScene::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsScene::keyReleaseEvent(event);
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Down
       || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
    {
        newPoss.clear();
        foreach(QGraphicsItem *pItem,movingItems)
        {
            newPoss += pItem->pos();
        }
        if(!movingItems.isEmpty() && oldPoss != newPoss)
        {
            emit itemsMoved(this,movingItems,oldPoss);
        }
        oldPoss.clear();
        movingItems.clear();
    }
}
 qreal SamDrawScene::getTopOrder()
{
    qreal z = 0;
    if(!TopItems().isEmpty())
      z = TopItems().first()->zValue();
    return z;
}
//重载QGraphicsScene的 additem函数，增加设置item到顶层的操作
void SamDrawScene::addItem(QGraphicsItem *item, qreal zValue)
{
    QGraphicsScene::addItem(item);

    if(item->type() == SAM_DRAW_OBJECT_TRACKER
       || item->type() == SAM_DRAW_OBJECT_LOCK)
        return;


    if(zValue == -1)//如果zValue是默认值，添加一个item则设置为最顶层
    {
        qreal dCurZValue = this->getTopOrder();
        dCurZValue++;
        item->setZValue(dCurZValue);
        this->setTopOrder(dCurZValue);
    }
    else//如果zValue不是默认值，则设置当前层次为zValue
    {
        item->setZValue(zValue);
    }
/*

	QVariant value = item->data(GROUP_TYPE_KEY);
	QGroupItem *groupFun = new QGroupItem(item);
	QString path;
	QStringList datalist;
	int i;
	datalist = qVariantValue<QStringList>(item->data(GROUP_DATALIST_KEY));
	switch(value.toInt())
	{
	case GROUP_TYPE_BITBTN:
	case GROUP_TYPE_BITLAMP:
		if (groupFun->PictrueOn())
		{
			//添加路径
                        path = datalist.at(164);
			path = pwnd->SavePicPath(path);
                        datalist.replace(164,path);
		}
		if (groupFun->PictrueOff())
		{
                        path = datalist.at(163);
			path = pwnd->SavePicPath(path);
                        datalist.replace(163,path);

		}
		item->setData(GROUP_DATALIST_KEY,datalist);
		break;
	case GROUP_TYPE_WORDBTN:
	case GROUP_TYPE_SCREENBTN:
	case GROUP_TYPE_FUNCTIONBTN:
	case GROUP_TYPE_MFUNCTION:
		if (groupFun->Pictrue())
		{
			path = datalist.at(151);
			path = pwnd->SavePicPath(path);
			datalist.replace(151,path);
		}
		item->setData(GROUP_DATALIST_KEY,datalist);
		break;
	case GROUP_TYPE_STATICPIC:
		if (groupFun->Pictrue())
		{
			path = datalist.at(4);
			path = pwnd->SavePicPath(path);
			datalist.replace(4,path);
		}
		item->setData(GROUP_DATALIST_KEY,datalist);
		break;
	case GROUP_TYPE_GIFPIC:
		if (groupFun->Pictrue())
		{
			path = datalist.at(61);
			path = pwnd->SavePicPath(path);
			datalist.replace(61,path);
		}
		item->setData(GROUP_DATALIST_KEY,datalist);
		break;
	case GROUP_TYPE_MULSTATELAMP:
	case GROUP_TYPE_MULSTATEBTN:

	case GROUP_TYPE_PICTUREMOVE:
	case GROUP_TYPE_STEPING:
	case GROUP_TYPE_SINGLESELECT:
		int nStatus,nLang,nVal;
		nStatus = datalist.at(41).toInt();//获取总状态数
		nLang = datalist.at(99).toInt();
		nVal = 101+4*nStatus+3*nStatus+nStatus*3*nLang;
		for (i = 0; i < nStatus; i++)
		{
			path = datalist.at(nVal+(8*i)+2);
			path = pwnd->SavePicPath(path);
			datalist.replace(nVal+(8*i)+2,path);
		}
		item->setData(GROUP_DATALIST_KEY,datalist);
		break;
case GROUP_TYPE_PICTUREDISPLAY:
                {
                    int nStatus,nVal;
                    nStatus = datalist.at(48).toInt();//获取总状态数
                    nVal = 101;
                    for (i = 0; i < nStatus; i++)
                    {
                            path = datalist.at(nVal+(8*i)+2);
                            path = pwnd->SavePicPath(path);
                            datalist.replace(nVal+(8*i)+2,path);
                    }
                    item->setData(GROUP_DATALIST_KEY,datalist);
                }
                break;
	default:
		break;
	}
        */
}
//=====================================================
//重新设置层次，item：当前操作的item；
//op ：1表示移到底层 2表示下移一层 3表示上移一层 4表示移到顶层
void SamDrawScene::ResetOder(QGraphicsItem *item,int op)
{
    QList<QGraphicsItem *> items = this->TopItems();
    int size = items.size();
    int index = items.indexOf(item);
    int prevIndex = 0;
    int nextIndex = size - 1;
    foreach (QGraphicsItem * pItem, items)
    {
        if (!pItem || pItem == item)
            continue;
        int cIdx = items.indexOf(pItem);
        if (cIdx < nextIndex && cIdx > index)
            nextIndex = cIdx;
        else if (cIdx > prevIndex && cIdx < index)
            prevIndex = cIdx;
    }
    switch (op) {
        case 1: // 最底层
            items.append(items.takeAt(index));
            break;
        case 2: // 下移一层
            if (index >= size - 1)
                return;
            items.insert(nextIndex, items.takeAt(index));
            break;
        case 3: // 上移一层
            if (index <= 0)
                return;
            items.insert(prevIndex, items.takeAt(index));
            break;
        case 4: // 最顶层
            items.prepend(items.takeAt(index));
            break;
    }

    //重新设置层次
    int z = size;
    foreach (QGraphicsItem * pItem, items)
        pItem->setZValue(z--);

    update();
}
//=====================================================
//当前控件item上移到顶层
void SamDrawScene::OnOderTop()
{
    QGraphicsItem *item;
    item = ItemSelected();
    if(!item)
    {
        return;
    }
    this->ResetOder(item,4);

}

//=====================================================
//当前控件item下移到底层
void SamDrawScene::OnOderBotton()
{
    QGraphicsItem *item;
    item = ItemSelected();
    if(!item)
    {
        return;
    }
    this->ResetOder(item,1);
}

//=====================================================
//当前控件item上移一层
void SamDrawScene::OnOderUp()
{
    QGraphicsItem *item;
    item = ItemSelected();
    if(!item)
    {
        return;
    }
    this->ResetOder(item,3);
}

//=====================================================
//当前控件item下移一层
void SamDrawScene::OnOderDown()
{
    QGraphicsItem *item;
    item = ItemSelected();
    if(!item)
    {
        return;
    }
    this->ResetOder(item,2);
}

//派生createItemGroup函数，增加改变层次的操作
QGraphicsItemGroup* SamDrawScene::createItemGroup(const QList<QGraphicsItem *> &items)
{
    QGraphicsItemGroup *Group;
    Group = QGraphicsScene::createItemGroup(items);
    Group->setZValue(this->getTopOrder()+1);
    return Group;
}

//组合已选择的item
void SamDrawScene::GroupItem()
{
    QList<QGraphicsItem *> qlstSelectedItems;
        QItemGroup *Group = new QItemGroup();
        qlstSelectedItems = selectedItems();
        int i = 0;
        if(qlstSelectedItems.size() <= 1)
        {
            return;
        }
        for(i=0;i < qlstSelectedItems.size();i++)
        {
            //在组合之前清除选择状态框
            qlstSelectedItems.at(i)->setFlag(QGraphicsItem::ItemIsSelectable, false);
            Group->addToGroup(qlstSelectedItems.at(i));
        }
        this->addItem(Group);
        Group->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
        Group->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
        /*Create the handle rects when a new group borned*/
        QRectF qrcBndRect = Group->sceneBoundingRect();
        Group->drawTracker(TRK_SELECTED, (QGraphicsScene *)this, qrcBndRect);
        Group->setSelected(true);

        Group->setData(GROUP_TYPE_KEY,QVariant(USER_DEFINE_GROUP)); //设置用户自定义组合的key值
        pwnd->ui->action_split->setEnabled(true);
}

//拆分已选择的Group
void SamDrawScene::DisGroupItem()
{
    int nTmp=0;

    QList <QGraphicsItem *>selectedlist;
    selectedlist = this->selectedItems(); //方法2
    if(selectedlist.size() != 1)
    {
        return ;
    }
    QGraphicsItem *item = selectedlist.at(0);

    QList<QGraphicsItem *> childitem = item->childItems();
    QVector<QPointF> vpos;
    vpos.clear();
    int nCount=childitem.size();
    int i = 0;
    if (nCount<1)
    {
        return;
    }
    for( i=0;i < nCount;i++)
    {
        QPointF  pos = childitem[i]->boundingRect().topLeft() + childitem[i]->scenePos();
        vpos.append(pos);
    }

    removeItem(item);
    nTmp = this->getTopOrder();
    for( i=0;i < nCount;i++)
    {
        addItem(childitem[i]);
        childitem[i]->setPos(vpos.at(i) - childitem[i]->boundingRect().topLeft());

        childitem.at(i)->setFlag(QGraphicsItem::ItemIsSelectable, true);
        childitem.at(i)->setFlag(QGraphicsItem::ItemIsMovable, true);
        childitem.at(i)->setSelected(true);
        childitem.at(i)->setZValue(nTmp+1+childitem.at(i)->zValue());
    }
}

//返回当前选中的ITEM，如果选中多个或者未选中，返回空NULL
QGraphicsItem * SamDrawScene::ItemSelected()
{
    QGraphicsItem *item;
    if(selectedItems().size() != 1)
    {
        return NULL;
    }
    item = selectedItems().first();
    return item;
}

//返回item的最终父节点
QGraphicsItem * SamDrawScene::TopmostParentItem (QGraphicsItem * item)
{
    QGraphicsItem * parentitem = item;
    while (parentitem && parentitem->parentItem())
    {
        parentitem = parentitem->parentItem();
    }
    return parentitem;
}

/*********************************************************************************
 * Function: remove item from scene
 * Parameters: item
 * Return: none
 ********************************************************************************/
void SamDrawScene::removeItem(QGraphicsItem *pItem)
{
    QRectItem *pRect     = 0;
    QElipseItem *pElipse = 0;
    QLineItem *pLine     = 0;
    QPolygonItem *pPolygon   = 0;
    QFoldLineItem *pFoldLine = 0;
    QFreeLineItem *pFreeLine = 0;
    QItemGroup *pItemGroup   = 0;
    QLineCircleItem *pLineCircle = 0;   //add by tanghaiguo
    QSimpleTextItem *pTextItem = 0;
    QRoundedRect *pRoundedRect = 0;
    QArcItem *pArc = 0;

    QRectBasicItem *pRectNew    = 0;
    QElipseBasicItem *pElipseNew = 0;
    QLineBasicItem *pLineNew     = 0;
    QPolygonBasicItem *pPolygonNew   = 0;
    QFoldLineBasicItem *pFoldLineNew = 0;
    QFreeLineBasicItem *pFreeLineNew = 0;
    QLineCircleBasicItem *pLineCircleNew = 0;   //add by tanghaiguo
    QRoundedRectBasic *pRoundedRectNew = 0;
    QArcBasicItem *pArcNew = 0;
    if (!pItem)
    {
        return;
    }
    switch (pItem->type())
    {
    case SAM_DRAW_OBJECT_RECT:
        pRect = dynamic_cast<QRectItem *> (pItem);
        if (pRect)
        {
            int iSize = pRect->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pRect->m_pvecTrackers[i]);
            }
            if(pRect->m_LockTracker)
            {
                QGraphicsScene::removeItem(pRect->m_LockTracker);
                pRect->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_ELIPSE:
        pElipse = dynamic_cast<QElipseItem *> (pItem);
        if (pElipse)
        {
            int iSize = pElipse->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pElipse->m_pvecTrackers[i]);
            }
            if(pElipse->m_LockTracker)
            {
                QGraphicsScene::removeItem(pElipse->m_LockTracker);
                pElipse->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_LINE:
        pLine = dynamic_cast<QLineItem *> (pItem);
        if (pLine)
        {
            int iSize = pLine->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pLine->m_pvecTrackers[i]);
            }
            if(pLine->m_LockTracker)
            {
                QGraphicsScene::removeItem(pLine->m_LockTracker);
                pLine->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_POLYGON:
        pPolygon = dynamic_cast<QPolygonItem *> (pItem);
        if (pPolygon)
        {
            int iSize = pPolygon->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pPolygon->m_pvecTrackers[i]);
            }
            if(pPolygon->m_LockTracker)
            {
                QGraphicsScene::removeItem(pPolygon->m_LockTracker);
                pPolygon->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_FOLDLINE:
        pFoldLine = dynamic_cast<QFoldLineItem *> (pItem);
        if (pFoldLine)
        {
            int iSize = pFoldLine->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pFoldLine->m_pvecTrackers[i]);
            }
            if(pFoldLine->m_LockTracker)
            {
                QGraphicsScene::removeItem(pFoldLine->m_LockTracker);
                pFoldLine->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_FREELINE:
        pFreeLine = dynamic_cast<QFreeLineItem *> (pItem);
        if (pFreeLine)
        {
            int iSize = pFreeLine->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pFreeLine->m_pvecTrackers[i]);
            }
            if(pFreeLine->m_LockTracker)
            {
                QGraphicsScene::removeItem(pFreeLine->m_LockTracker);
                pFreeLine->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_GROUP:
        pItemGroup = dynamic_cast<QItemGroup *> (pItem);
        if (pItemGroup)
        {
            int iSize = pItemGroup->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pItemGroup->m_pvecTrackers[i]);
            }
            if(pItemGroup->m_LockTracker)
            {
                QGraphicsScene::removeItem(pItemGroup->m_LockTracker);
                pItemGroup->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE:
        pLineCircle = dynamic_cast<QLineCircleItem *> (pItem);
        if (pLineCircle)
        {
            int iSize = pLineCircle->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pLineCircle->m_pvecTrackers[i]);
            }
            if(pLineCircle->m_LockTracker)
            {
                QGraphicsScene::removeItem(pLineCircle->m_LockTracker);
                pLineCircle->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_TEXT:
        pTextItem = dynamic_cast<QSimpleTextItem *> (pItem);
        if (pTextItem)
        {
            int iSize = pTextItem->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pTextItem->m_pvecTrackers[i]);
            }
            if(pTextItem->m_LockTracker)
            {
                QGraphicsScene::removeItem(pTextItem->m_LockTracker);
                pTextItem->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
        pRoundedRect = dynamic_cast<QRoundedRect *> (pItem);
        if (pRoundedRect)
        {
            int iSize = pRoundedRect->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pRoundedRect->m_pvecTrackers[i]);
            }
            if(pRoundedRect->m_LockTracker)
            {
                QGraphicsScene::removeItem(pRoundedRect->m_LockTracker);
                pRoundedRect->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_ARC:
        pArc = dynamic_cast<QArcItem *> (pItem);
        if (pArc)
        {
            int iSize = pArc->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pArc->m_pvecTrackers[i]);
            }
            if(pArc->m_LockTracker)
            {
                QGraphicsScene::removeItem(pArc->m_LockTracker);
                pArc->m_LockTracker = NULL;
            }
        }
        break;
////////////////wxy add start
    case SAM_DRAW_OBJECT_RECT_NEW:
        pRectNew = dynamic_cast<QRectBasicItem *> (pItem);
        if (pRectNew)
        {
            int iSize = pRectNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pRectNew->m_pvecTrackers[i]);
            }
            if(pRectNew->m_LockTracker)
            {
                QGraphicsScene::removeItem(pRectNew->m_LockTracker);
                pRectNew->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_ELIPSE_NEW:
        pElipseNew = dynamic_cast<QElipseBasicItem *> (pItem);
        if (pElipseNew)
        {
            int iSize = pElipseNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pElipseNew->m_pvecTrackers[i]);
            }
            if(pElipseNew->m_LockTracker)
            {
                QGraphicsScene::removeItem(pElipseNew->m_LockTracker);
                pElipseNew->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_LINE_NEW:
        pLineNew = dynamic_cast<QLineBasicItem *> (pItem);
        if (pLineNew)
        {
            int iSize = pLineNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pLineNew->m_pvecTrackers[i]);
            }
            if(pLineNew->m_LockTracker)
            {
                QGraphicsScene::removeItem(pLineNew->m_LockTracker);
                pLineNew->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_POLYGON_NEW:
        pPolygonNew = dynamic_cast<QPolygonBasicItem *> (pItem);
        if (pPolygonNew)
        {
            int iSize = pPolygonNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pPolygonNew->m_pvecTrackers[i]);
            }
            if(pPolygonNew->m_LockTracker)
            {
                QGraphicsScene::removeItem(pPolygonNew->m_LockTracker);
                pPolygonNew->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_FOLDLINE_NEW:
        pFoldLineNew = dynamic_cast<QFoldLineBasicItem *> (pItem);
        if (pFoldLineNew)
        {
            int iSize = pFoldLineNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pFoldLineNew->m_pvecTrackers[i]);
            }
            if(pFoldLineNew->m_LockTracker)
            {
                QGraphicsScene::removeItem(pFoldLineNew->m_LockTracker);
                pFoldLineNew->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_FREELINE_NEW:
        pFreeLineNew = dynamic_cast<QFreeLineBasicItem *> (pItem);
        if (pFreeLineNew)
        {
            int iSize = pFreeLineNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pFreeLineNew->m_pvecTrackers[i]);
            }
            if(pFreeLineNew->m_LockTracker)
            {
                QGraphicsScene::removeItem(pFreeLineNew->m_LockTracker);
                pFreeLineNew->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
        pLineCircleNew = dynamic_cast<QLineCircleBasicItem *> (pItem);
        if (pLineCircleNew)
        {
            int iSize = pLineCircleNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pLineCircleNew->m_pvecTrackers[i]);
            }
            if(pLineCircleNew->m_LockTracker)
            {
                QGraphicsScene::removeItem(pLineCircleNew->m_LockTracker);
                pLineCircleNew->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
        pRoundedRectNew = dynamic_cast<QRoundedRectBasic *> (pItem);
        if (pRoundedRectNew)
        {
            int iSize = pRoundedRectNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pRoundedRectNew->m_pvecTrackers[i]);
            }
            if(pRoundedRectNew->m_LockTracker)
            {
                QGraphicsScene::removeItem(pRoundedRectNew->m_LockTracker);
                pRoundedRectNew->m_LockTracker = NULL;
            }
        }
        break;
    case SAM_DRAW_OBJECT_ARC_NEW:
        pArcNew = dynamic_cast<QArcBasicItem *> (pItem);
        if (pArcNew)
        {
            int iSize = pArcNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                QGraphicsScene::removeItem(pArcNew->m_pvecTrackers[i]);
            }
            if(pArcNew->m_LockTracker)
            {
                QGraphicsScene::removeItem(pArcNew->m_LockTracker);
                pArcNew->m_LockTracker = NULL;
            }
        }
        break;
///////////////wxy add end
    default:
        break;
    }

    QGraphicsScene::removeItem(pItem);
}
void SamDrawScene::OnSetLeftAlign() //设置所选控件左对齐
{
    QList<QGraphicsItem *> selectedlist;
    QGraphicsItem *item;
    selectedlist.clear();
    qreal qMin = 0; //存最小值
    qreal qVal = 0; //临时变量
    int i=0;
    int count = 0;  //存所有的图形数目

    selectedlist = this->selectedItems();    //所选控件
    count = selectedlist.size();
    if(count < 2) //没有选择的时候返回
        return;

    QList <QPointF > poss;
    QGraphicsItem *pSelectedItem = NULL;
    foreach(QGraphicsItem *pItem,selectedlist)
    {
        poss << pItem->pos();
        if(this->GetSelectFlag(pItem))
        {
            pSelectedItem = pItem;
        }
    }

    if(pSelectedItem)
    {
       qMin = pSelectedItem->boundingRect().left()+pSelectedItem->scenePos().x();
    }
    else
    {
        item = selectedlist.at(0);
        //图形在场景上的坐标等于boundingRect所得到的x坐标加上scenePos的x坐标
        qMin = item->boundingRect().left()+item->scenePos().x();
        for(i = 1;i < count;i++)   //求出所选择的图形中左坐标最小值
        {
            if(qMin > selectedlist.at(i)->boundingRect().left()+selectedlist.at(i)->scenePos().x())
                qMin = selectedlist.at(i)->boundingRect().left()+selectedlist.at(i)->scenePos().x();
        }
    }

    for(i = 0; i < count; i++)  //移动所有图形的左坐标到最小值处
    {
        item = selectedlist.at(i);
        if(!(item->flags() & QGraphicsItem::ItemIsMovable))
        {
            continue;
        }
        qVal = qMin - item->boundingRect().x();
        selectedlist.at(i)->setX(qVal);
    }
    this->reBondingTrackers();

    emit itemsMoved(this,selectedlist,poss);
}

void SamDrawScene::OnSetRightAlign()  //所选图形右对齐
{
    QList<QGraphicsItem *> selectedlist;
    QGraphicsItem *item;
    selectedlist.clear();
    qreal qMax = 0; //存最大值
    qreal qVal = 0; //临时变量
    int i=0;
    int count = 0;  //存所有的图形数目

    selectedlist = this->selectedItems();    //所选控件
    count = selectedlist.size();
    if(count < 2) //没有选择的时候返回
        return;

    QList <QPointF > poss;
    QGraphicsItem *pSelectedItem = NULL;
    foreach(QGraphicsItem *pItem,selectedlist)
    {
        poss << pItem->pos();
        if(this->GetSelectFlag(pItem))
        {
            pSelectedItem = pItem;
        }
    }

    if(pSelectedItem)
    {
        qMax = pSelectedItem->boundingRect().right()+pSelectedItem->scenePos().rx();
    }
    else
    {
        item = selectedlist.at(0);
        //图形在场景上的坐标等于boundingRect所得到的x坐标加上scenePos的x坐标
        qMax = item->boundingRect().right()+item->scenePos().rx();
        for(i = 1;i < count;i++)   //求出所选择的图形中左坐标最大值
        {
            if(qMax < selectedlist.at(i)->boundingRect().right()+selectedlist.at(i)->scenePos().rx())
                qMax = selectedlist.at(i)->boundingRect().right()+selectedlist.at(i)->scenePos().rx();
        }
    }

    for(i = 0; i < count; i++)  //移动所有图形的左坐标到最大值处
    {
        item = selectedlist.at(i);
        if(!(item->flags() & QGraphicsItem::ItemIsMovable))
        {
            continue;
        }
        qVal = qMax - item->boundingRect().right();
        selectedlist.at(i)->setX(qVal);
    }
    this->reBondingTrackers();
    emit itemsMoved(this,selectedlist,poss);
}

void SamDrawScene::OnSetTopAlign() //图形上对齐
{
    QList<QGraphicsItem *> selectedlist;
    QGraphicsItem *item;
    selectedlist.clear();
    qreal qMin = 0; //存最小值
    qreal qVal = 0; //临时变量
    int i=0;
    int count = 0;  //存所有的图形数目

    selectedlist = this->selectedItems();    //所选控件
    count = selectedlist.size();
    if(count < 2) //没有选择的时候返回
        return;

    QList <QPointF > poss;
    QGraphicsItem *pSelectedItem = NULL;
    foreach(QGraphicsItem *pItem,selectedlist)
    {
        poss << pItem->pos();
        if(this->GetSelectFlag(pItem))
        {
            pSelectedItem = pItem;
        }
    }

    if(pSelectedItem)
    {
        qMin = pSelectedItem->boundingRect().top()+pSelectedItem->scenePos().y();
    }
    else
    {
        item = selectedlist.at(0);
        //图形在场景上的坐标等于boundingRect所得到的x坐标加上scenePos的x坐标
        qMin = item->boundingRect().top()+item->scenePos().y();
        for(i = 1;i < count;i++)   //求出所选择的图形中左坐标最小值
        {
            if(qMin > selectedlist.at(i)->boundingRect().top()+selectedlist.at(i)->scenePos().y())
                qMin = selectedlist.at(i)->boundingRect().top()+selectedlist.at(i)->scenePos().y();
        }
    }

    for(i = 0; i < count; i++)  //移动所有图形的左坐标到最小值处
    {
        item = selectedlist.at(i);
        if(!(item->flags() & QGraphicsItem::ItemIsMovable))
        {
            continue;
        }
        qVal = qMin - item->boundingRect().top();
        selectedlist.at(i)->setY(qVal);
    }
    this->reBondingTrackers();
    emit itemsMoved(this,selectedlist,poss);
}

void SamDrawScene::OnSetButtomAlign() //下对齐
{
    QList<QGraphicsItem *> selectedlist;
    QGraphicsItem *item;
    selectedlist.clear();
    qreal qMax = 0; //存最大值
    qreal qVal = 0; //临时变量
    int i=0;
    int count = 0;  //存所有的图形数目

    selectedlist = this->selectedItems();    //所选控件
    count = selectedlist.size();
    if(count < 2) //没有选择的时候返回
        return;

    QList <QPointF > poss;
    QGraphicsItem *pSelectedItem = NULL;
    foreach(QGraphicsItem *pItem,selectedlist)
    {
        poss << pItem->pos();
        if(this->GetSelectFlag(pItem))
        {
            pSelectedItem = pItem;
        }
    }

    if(pSelectedItem)
    {
       qMax = pSelectedItem->boundingRect().bottom()+pSelectedItem->scenePos().y();
    }
    else
    {
        item = selectedlist.at(0);
        //图形在场景上的坐标等于boundingRect所得到的x坐标加上scenePos的x坐标
        qMax = item->boundingRect().bottom()+item->scenePos().y();
        for(i = 1;i < count;i++)   //求出所选择的图形中左坐标最大值
        {
            if(qMax < selectedlist.at(i)->boundingRect().bottom()+selectedlist.at(i)->scenePos().y())
                qMax = selectedlist.at(i)->boundingRect().bottom()+selectedlist.at(i)->scenePos().y();
        }
    }


    for(i = 0; i < count; i++)  //移动所有图形的左坐标到最大值处
    {
        item = selectedlist.at(i);
        if(!(item->flags() & QGraphicsItem::ItemIsMovable))
        {
            continue;
        }
        qVal = qMax - item->boundingRect().bottom();
        selectedlist.at(i)->setY(qVal);
    }
    this->reBondingTrackers();
    emit itemsMoved(this,selectedlist,poss);
}

void SamDrawScene::OnSetHCenterAlign() //水平居中
{
    QList<QGraphicsItem *> selectedlist;
    QGraphicsItem *item;
    selectedlist.clear();
    qreal qMin = 0;     //存最小值
    qreal qMax = 0;     //存最大值
    qreal qVal = 0;     //临时变量
    qreal qWidth = 0;   //最小值与最大值的差值
    int i=0;
    int count = 0;      //存所有的图形数目

    selectedlist = this->selectedItems();    //所选控件
    count = selectedlist.size();
    if(count < 2)                           //没有选择的时候返回
        return;

    QList <QPointF > poss;
    foreach(QGraphicsItem *pItem,selectedlist)
    {
        poss << pItem->pos();
    }

    /*************************************************************************
	*以下是求所有选择图形左坐标最小值
	************************************************************************/
    item = selectedlist.at(0);
    //图形在场景上的坐标等于boundingRect所得到的x坐标加上scenePos的x坐标
    qMin = item->boundingRect().left()+item->scenePos().x();
    for(i = 1;i < count;i++)   //求出所选择的图形中左坐标最小值
    {
        if(qMin > selectedlist.at(i)->boundingRect().left()+selectedlist.at(i)->scenePos().x())
            qMin = selectedlist.at(i)->boundingRect().left()+selectedlist.at(i)->scenePos().x();
    }

    /*************************************************************************
	*以下是求所有选择图形右坐标最大值
	************************************************************************/
    item = selectedlist.at(0);
    //图形在场景上的坐标等于boundingRect所得到的x坐标加上scenePos的x坐标
    qMax = item->boundingRect().right()+item->scenePos().rx();
    for(i =1;i<count;i++)   //求出所选择的图形中左坐标最大值
    {
        if(qMax < selectedlist.at(i)->boundingRect().right()+selectedlist.at(i)->scenePos().rx())
            qMax = selectedlist.at(i)->boundingRect().right()+selectedlist.at(i)->scenePos().rx();
    }

    qWidth = qMax - qMin;   //最小值与最大值的差值

    for(i = 0;i < count;i++)
    {
        item = selectedlist.at(i);
        if(!(item->flags() & QGraphicsItem::ItemIsMovable))
        {
            continue;
        }
        qVal = (qWidth - item->boundingRect().width())/2;
        qVal = qMin+qVal;
        qVal -= item->boundingRect().x();
        item->setX(qVal);
    }
    this->reBondingTrackers();
    emit itemsMoved(this,selectedlist,poss);
}


void SamDrawScene::OnSetVCenterAlign() //垂直居中对齐
{
    QList<QGraphicsItem *> selectedlist;
    QGraphicsItem *item;
    selectedlist.clear();
    qreal qMin = 0;     //存最小值
    qreal qMax = 0;     //存最大值
    qreal qVal = 0;     //临时变量
    qreal qHeight = 0;  //最小值与最大值的差值
    int i=0;
    int count = 0;      //存所有的图形数目

    selectedlist = this->selectedItems();    //所选控件
    count = selectedlist.size();
    if(count < 2) //没有选择的时候返回
        return;

    QList <QPointF > poss;
    foreach(QGraphicsItem *pItem,selectedlist)
    {
        poss << pItem->pos();
    }

    /*************************************************************************
	*以下是求所有选择图形上坐标最小值
	************************************************************************/
    item = selectedlist.at(0);
    //图形在场景上的坐标等于boundingRect所得到的x坐标加上scenePos的x坐标
    qMin = item->boundingRect().top()+item->scenePos().y();
    for(i = 1;i < count;i++)   //求出所选择的图形中左坐标最小值
    {
        if(qMin > selectedlist.at(i)->boundingRect().top()+selectedlist.at(i)->scenePos().y())
            qMin = selectedlist.at(i)->boundingRect().top()+selectedlist.at(i)->scenePos().y();
    }

    /*************************************************************************
	*以下是求所有选择图形下坐标最大值
	************************************************************************/
    item = selectedlist.at(0);
    //图形在场景上的坐标等于boundingRect所得到的x坐标加上scenePos的x坐标
    qMax = item->boundingRect().bottom()+item->scenePos().y();
    for(i = 1;i < count;i++)   //求出所选择的图形中左坐标最大值
    {
        if(qMax < selectedlist.at(i)->boundingRect().bottom()+selectedlist.at(i)->scenePos().y())
            qMax = selectedlist.at(i)->boundingRect().bottom()+selectedlist.at(i)->scenePos().y();
    }

    qHeight = qMax - qMin;   //最小值与最大值的差值

    for(i = 0;i < count;i++)
    {
        item = selectedlist.at(i);
        if(!(item->flags() & QGraphicsItem::ItemIsMovable))
        {
            continue;
        }
        qVal = (qHeight - item->boundingRect().height())/2;
        qVal = qMin+qVal;
        qVal -= item->boundingRect().y();
        item->setY(qVal);
    }
    this->reBondingTrackers();
    emit itemsMoved(this,selectedlist,poss);
}


void SamDrawScene::OnSetHSpacingAlign() //水平等间距对齐
{
    QList<QGraphicsItem *> selectedlist;
    QGraphicsItem *item;
    selectedlist.clear();
    int i = 0;
    int j = 0;
    int count = 0;      //存所有的图形数目
    qreal val = 0;
    double nspace=0; //控件之间的间隔大小
    double ntotal=0; //间隔之间的控件宽度总和
    double nLength=0; //最左边和最右边的控件之间的距离

    struct ItemList
    {
        qreal qX;           //图形左坐标
        qreal qWidth;       //图形的宽度
        QGraphicsItem *qItem; //图形
    }pItem[200];

    selectedlist = this->selectedItems();    //所选控件
    count = selectedlist.size();
    if(count <= 2 )
        return;

    if(count > 200)
        count = 200;

    QList <QPointF > poss;
    foreach(QGraphicsItem *pItem,selectedlist)
    {
        poss << pItem->pos();
    }

    for(i = 0;i < count;i++)   //把所有图形的左坐标和宽度放入结构体中
    {
        item = selectedlist.at(i);
        pItem[i].qX = item->boundingRect().left()+item->scenePos().x();
        pItem[i].qWidth = item->boundingRect().width();
        pItem[i].qItem = item;
    }

    for(i=0;i < count-1;i++)//采用冒泡排序的方法优化整个数组,从小到大排列
    {
        for(j=0;j < count-1-i;j++)
        {
            if(pItem[j].qX > pItem[j+1].qX)
            {
                val = pItem[j+1].qX;
                pItem[j+1].qX = pItem[j].qX ;
                pItem[j].qX  = val;

                val=pItem[j+1].qWidth;
                pItem[j+1].qWidth = pItem[j].qWidth;
                pItem[j].qWidth = val;

                item = pItem[j+1].qItem;
                pItem[j+1].qItem = pItem[j].qItem;
                pItem[j].qItem = item;
            }//endif
        }//endfor
    }//endfor

    //求出最左边和最右边的控件之间的距离
    nLength=pItem[count-1].qX-(pItem[0].qX+pItem[0].qWidth);
    for(i = 1;i < count-1;i++)
    {
        ntotal=ntotal+pItem[i].qWidth; //间隔之间的控件宽度总和
    }

    nspace=(nLength-ntotal)/(count-1); //控件之间的间隔大小
    for(i=0;i < count-2;i++) //重新设置中间控件的左坐标的数值
    {
        pItem[i+1].qX = pItem[i].qX + pItem[i].qWidth + nspace;
    }

    for(i=1;i < count-1;i++) //重新设置控件的位置
    {
        if(!(pItem[i].qItem->flags() & QGraphicsItem::ItemIsMovable))
        {
            continue;
        }
        val = pItem[i].qX - pItem[i].qItem->boundingRect().x();
        pItem[i].qItem->setX(val);
    }
    this->reBondingTrackers();
    emit itemsMoved(this,selectedlist,poss);
}

void SamDrawScene::OnSetVSpacingAlign() //垂直等间距对齐
{
    QList<QGraphicsItem *> selectedlist;
    QGraphicsItem *item;
    selectedlist.clear();
    int i = 0;
    int j = 0;
    int count = 0;      //存所有的图形数目
    qreal val = 0;
    double nspace=0; //控件之间的间隔大小
    double ntotal=0; //间隔之间的控件宽度总和
    double nLength=0; //最左边和最右边的控件之间的距离

    struct ItemList
    {
        qreal qY;           //图形上坐标
        qreal qHeight;       //图形的宽度
        QGraphicsItem *qItem; //图形
    }pItem[200];

    selectedlist = this->selectedItems();    //所选控件
    count = selectedlist.size();
    if(count <= 2 )
        return;

    if(count > 200)
        count = 200;

    QList <QPointF > poss;
    foreach(QGraphicsItem *pItem,selectedlist)
    {
        poss << pItem->pos();
    }

    for(i = 0;i < count;i++)   //把所有图形的左坐标和宽度放入结构体中
    {
        item = selectedlist.at(i);
        pItem[i].qY = item->boundingRect().top()+item->scenePos().y();
        pItem[i].qHeight = item->boundingRect().height();
        pItem[i].qItem = item;
    }

    for(i=0;i < count-1;i++)//采用冒泡排序的方法优化整个数组,从小到大排列
    {
        for(j=0;j < count-1-i;j++)
        {
            if(pItem[j].qY > pItem[j+1].qY)
            {
                val = pItem[j+1].qY;
                pItem[j+1].qY = pItem[j].qY ;
                pItem[j].qY  = val;

                val=pItem[j+1].qHeight;
                pItem[j+1].qHeight = pItem[j].qHeight;
                pItem[j].qHeight = val;

                item = pItem[j+1].qItem;
                pItem[j+1].qItem = pItem[j].qItem;
                pItem[j].qItem = item;
            }//endif
        }//endfor
    }//endfor

    //求出最左边和最右边的控件之间的距离
    nLength=pItem[count-1].qY-(pItem[0].qY+pItem[0].qHeight);
    for(i = 1;i < count-1;i++)
    {
        ntotal=ntotal+pItem[i].qHeight; //间隔之间的控件宽度总和
    }

    nspace=(nLength-ntotal)/(count-1); //控件之间的间隔大小
    for(i=0;i < count-2;i++) //重新设置中间控件的左坐标的数值
    {
        pItem[i+1].qY = pItem[i].qY + pItem[i].qHeight + nspace;
    }

    for(i=1;i < count-1;i++) //重新设置控件的位置
    {
        if(!(pItem[i].qItem->flags() & QGraphicsItem::ItemIsMovable))
        {
            continue;
        }
        val = pItem[i].qY - pItem[i].qItem->boundingRect().y();
        pItem[i].qItem->setY(val);
    }
    this->reBondingTrackers();
    emit itemsMoved(this,selectedlist,poss);
}



void SamDrawScene::mousePressEventForUndo(QGraphicsSceneMouseEvent *event)
{
    if(pTableItam)//表格拖动目前不做CTRL+Z撤销处理
    {
        return;
    }

    if (event->button() == Qt::LeftButton)
    {
        startPos = event->screenPos();
    }

    /*获取鼠标单击时的位置*/
    QPointF mousePos(event->buttonDownScenePos(Qt::LeftButton).x(),
                     event->buttonDownScenePos(Qt::LeftButton).y());
    oldMousePoint.setX(event->scenePos().x());   /*保存鼠标单击时的场景坐标位置*/
    oldMousePoint.setY(event->scenePos().y());

    movingItem = itemAt(oldMousePoint.x(), oldMousePoint.y());   /*根据鼠标位置获取选中的控件*/
    movingItems.clear();

    movingItems<<selectedItems();  /*将选中的控件的保存在movingItems容器中*/

    if(movingItem != NULL)
    {
        movingItems<<movingItem;
    }
    /*进一步判断是否有控件按下并且是右键*/
    if (movingItems.count() != 0 && event->button() == Qt::LeftButton)
    {
        oldSize = movingItems.first()->boundingRect().size();

        oldPos = movingItems.first()->sceneBoundingRect().topLeft();
        oldPoss.clear();

        if(movingItems.count() == 2)
        {
            QLineBasicItem *pLineItem = NULL;
            QFreeLineBasicItem *pFreeLineItem = NULL;
            QFoldLineBasicItem *pFoldlineItem = NULL;
            QPolygonBasicItem *pPolygonItem = NULL;
            QLineCircleBasicItem *pLineCircleItem = NULL;

            QLineItem *pLineItemOld = NULL;
            QFreeLineItem *pFreeLineItemOld = NULL;
            QFoldLineItem *pFoldlineItemOld = NULL;
            QPolygonItem *pPolygonItemOld = NULL;
            QLineCircleItem *pLineCircleItemOld = NULL;

            QGraphicsItem *pItem = movingItems.first();
            int type = movingItems.first()->type();
            oldPath = QPainterPath();
            oldPolygon.clear();
            switch(type)
            {
            case SAM_DRAW_OBJECT_LINE_NEW:
                pLineItem = dynamic_cast<QLineBasicItem *>(pItem);
                oldPath = pLineItem->path();
                break;
            case SAM_DRAW_OBJECT_FREELINE_NEW:
                pFreeLineItem = dynamic_cast<QFreeLineBasicItem *>(pItem);
                oldPath = pFreeLineItem->path();
                break;
            case SAM_DRAW_OBJECT_FOLDLINE_NEW:
                pFoldlineItem = dynamic_cast<QFoldLineBasicItem *>(pItem);
                oldPath = pFoldlineItem->path();
                break;
            case SAM_DRAW_OBJECT_POLYGON_NEW:
                pPolygonItem = dynamic_cast<QPolygonBasicItem *>(pItem);
                oldPolygon = pPolygonItem->polygon();
                break;
            case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
                pLineCircleItem = dynamic_cast<QLineCircleBasicItem *>(pItem);
                oldPath = pLineCircleItem->path();
                break;
///////////////////wxy add start
            case SAM_DRAW_OBJECT_LINE:
                pLineItemOld = dynamic_cast<QLineItem *>(pItem);
                oldPath = pLineItemOld->path();
                break;
            case SAM_DRAW_OBJECT_FREELINE:
                pFreeLineItemOld = dynamic_cast<QFreeLineItem *>(pItem);
                oldPath = pFreeLineItemOld->path();
                break;
            case SAM_DRAW_OBJECT_FOLDLINE:
                pFoldlineItemOld = dynamic_cast<QFoldLineItem *>(pItem);
                oldPath = pFoldlineItemOld->path();
                break;
            case SAM_DRAW_OBJECT_POLYGON:
                pPolygonItemOld = dynamic_cast<QPolygonItem *>(pItem);
                oldPolygon = pPolygonItemOld->polygon();
                break;
            case SAM_DRAW_OBJECT_LINECIRCLE:
                pLineCircleItemOld = dynamic_cast<QLineCircleItem *>(pItem);
                oldPath = pLineCircleItemOld->path();
                break;
////////////////wxy add end
            default :break;
            }
        }
        foreach (QGraphicsItem *item, movingItems)
        {
            oldPoss+=item->pos();/*将所有选中状态的控件起始保存在oldPoss容器中*/
        }

    }
}



void SamDrawScene::mouseReleaseEventForUndo(SamDrawScene *scene,QGraphicsSceneMouseEvent *event)
{
    newMousePoint.setX(event->scenePos().x());   /*保存鼠标释放时的场景坐标位置*/
    newMousePoint.setY(event->scenePos().y());

    if (movingItems.count() > 0 && event->button() && event->button() == Qt::LeftButton)/*进一步判断是否有控件按下并且是右键*/
    {

        if(movingItems.count() == 2)
        {
            QLineBasicItem *pLineItem = NULL;
            QFreeLineBasicItem *pFreeLineItem = NULL;
            QFoldLineBasicItem *pFoldlineItem = NULL;
            QPolygonBasicItem *pPolygonItem = NULL;
            QLineCircleBasicItem *pLineCircleItem = NULL;

            QLineItem *pLineItemOld = NULL;
            QFreeLineItem *pFreeLineItemOld = NULL;
            QFoldLineItem *pFoldlineItemOld = NULL;
            QPolygonItem *pPolygonItemOld = NULL;
            QLineCircleItem *pLineCircleItemOld = NULL;

            QGraphicsItem *item = movingItems.first();
            newPath = QPainterPath();
            newPolygon.clear();
            switch(item->type())
            {
            case SAM_DRAW_OBJECT_LINE_NEW:
                pLineItem = dynamic_cast<QLineBasicItem *>(item);
                newPath = pLineItem->path();
                break;
            case SAM_DRAW_OBJECT_FREELINE_NEW:
                pFreeLineItem = dynamic_cast<QFreeLineBasicItem *>(item);
                newPath = pFreeLineItem->path();
                break;
            case SAM_DRAW_OBJECT_FOLDLINE_NEW:
                pFoldlineItem = dynamic_cast<QFoldLineBasicItem *>(item);
                newPath = pFoldlineItem->path();
                break;
            case SAM_DRAW_OBJECT_POLYGON_NEW:
                pPolygonItem = dynamic_cast<QPolygonBasicItem *>(item);
                newPolygon = pPolygonItem->polygon();
                break;
            case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
                pLineCircleItem = dynamic_cast<QLineCircleBasicItem *>(item);
                newPath = pLineCircleItem->path();
                break;
/////////////////wxy add start
            case SAM_DRAW_OBJECT_LINE:
                pLineItemOld = dynamic_cast<QLineItem *>(item);
                newPath = pLineItemOld->path();
                break;
            case SAM_DRAW_OBJECT_FREELINE:
                pFreeLineItemOld = dynamic_cast<QFreeLineItem *>(item);
                newPath = pFreeLineItemOld->path();
                break;
            case SAM_DRAW_OBJECT_FOLDLINE:
                pFoldlineItemOld = dynamic_cast<QFoldLineItem *>(item);
                newPath = pFoldlineItemOld->path();
                break;
            case SAM_DRAW_OBJECT_POLYGON:
                pPolygonItemOld = dynamic_cast<QPolygonItem *>(item);
                newPolygon = pPolygonItemOld->polygon();
                break;
            case SAM_DRAW_OBJECT_LINECIRCLE:
                pLineCircleItemOld = dynamic_cast<QLineCircleItem *>(item);
                newPath = pLineCircleItemOld->path();
                break;
/////////////////wxy add end
            default :break;
            }
        }
        newPoss.clear();
        foreach(QGraphicsItem *pItem,movingItems)
        {
            newPoss += pItem->pos();
        }
        if(newPath != oldPath && !newPath.isEmpty() && !oldPath.isEmpty())
        {
            emit lineItemDrag(scene,movingItems.first(),oldPath,newPath);
            newPath = QPainterPath();
        }
        else if(newPolygon != oldPolygon && !oldPolygon.isEmpty()
            && !newPolygon.isEmpty())
        {
            emit polygonDrag(scene,movingItems.first(),oldPolygon,newPolygon);
            newPolygon.clear();
        }
        else if(oldSize != movingItems.first()->boundingRect().size())
        {
            QGraphicsItem *resizeItem = movingItems.first();
            emit itemResize(scene,resizeItem,oldSize,oldPos);
        }
        else if(!movingItems.isEmpty() && oldPoss != newPoss)
        {
            emit itemsMoved(scene,movingItems,oldPoss);
        }
    }
    oldPoss.clear();
    movingItems.clear();
}

void SamDrawScene:: SamDrawSceneForUndo(void)
{
    movingItem = 0;         /*当前移动的控件*/
    oldPoss.clear();        /*清空开始移动时刻的位置的容器*/
    movingItems.clear();    /*清空处于移动状态控件存储容器*/
}


void SamDrawScene::sendSelectionChangeSignal(void)
{
    this->reBondingTrackers(true);
}

/*********************************************************************************
 * Function: set all selected items the same width with the leftmost one (add by bruce nie)
 * Parameters: none
 * Return: none
 ********************************************************************************/
void SamDrawScene::setWidthSame()
{
    m_selectTool.setSelSameWidth(this);
    this->reBondingTrackers();
    //emit this->selectionChanged();
    this->update();
}

/*********************************************************************************
 * Function: set all selected items the same height with the leftmost one (add by bruce nie)
 * Parameters: none
 * Return: none
 ********************************************************************************/
void SamDrawScene::setHeightSame()
{
    m_selectTool.setSelSameheight(this);
    this->reBondingTrackers();
    //emit this->selectionChanged();
    this->update();
}

/*********************************************************************************
 * Function: set all selected items the same width/height with the leftmost one (add by bruce nie)
 * Parameters: none
 * Return: none
 ********************************************************************************/
void SamDrawScene::setWidthHeightSame()
{
    m_selectTool.setSelSameWidthHeight(this);
    this->reBondingTrackers();
    //emit this->selectionChanged();
    this->update();
}

/**************************************************************
 * Function: delete samkoon item
 * Parameters: pItem
 * Return: null
 ***************************************************************/
/*
void SamDrawScene::deleteSamItem(QGraphicsItem *pItem)
{
    switch(pItem->type())
    {
    case SAM_DRAW_OBJECT_RECT:              //15
        {
            QRectItem *pRectItem = dynamic_cast<QRectItem *>(pItem);
            if(pRectItem)
            {
                delete pRectItem;
                pRectItem = NULL;
            }
            break;
        }
    case SAM_DRAW_OBJECT_ELIPSE:              //16
        {
            QElipseItem *pElipseItem = dynamic_cast<QElipseItem *>(pItem);
            if(pElipseItem)
            {
                delete pElipseItem;
                pElipseItem = NULL;
            }
            break;
        }
    case SAM_DRAW_OBJECT_LINE:                 //17
        {
            QLineItem *pLineItem = dynamic_cast<QLineItem *>(pItem);
            if(pLineItem)
            {
                delete pLineItem;
                pLineItem = NULL;
            }
            break;
        }
    case SAM_DRAW_OBJECT_POLYGON:              //18
        {
            QPolygonItem *pPolygonItem = dynamic_cast<QPolygonItem *>(pItem);
            if(pPolygonItem)
            {
                delete pPolygonItem;
                pPolygonItem = NULL;
            }
            break;
        }
    case SAM_DRAW_OBJECT_FOLDLINE:             //19
        {
            QFoldLineItem *pFoldLineItem = dynamic_cast<QFoldLineItem *>(pItem);
            if(pFoldLineItem)
            {
                delete pFoldLineItem;
                pFoldLineItem = NULL;
            }
            break;
        }
    case SAM_DRAW_OBJECT_FREELINE:             //20
        {
            QFreeLineItem *pFreeLineItem = dynamic_cast<QFreeLineItem *>(pItem);
            if(pFreeLineItem)
            {
                delete pFreeLineItem;
                pFreeLineItem = NULL;
            }
            break;
        }
    case SAM_DRAW_OBJECT_TEXT:                 //22
        {
            QSimpleTextItem *pTextItem = dynamic_cast<QSimpleTextItem *>(pItem);
            delete pTextItem;
            pTextItem = NULL;
            break;
        }
    case SAM_DRAW_OBJECT_PIXMAP:
        {
            QPixmapItem *pPixmapItem = dynamic_cast<QPixmapItem *>(pItem);
            if(pPixmapItem)
            {
                delete pPixmapItem;
                pPixmapItem = NULL;
            }
            break;
        }
    case SAM_DRAW_OBJECT_LINECIRCLE:           //25
        {
            QLineCircleItem *pLineCircleItem = dynamic_cast<QLineCircleItem *>(pItem);
            if(pLineCircleItem)
            {
                delete pLineCircleItem;
                pLineCircleItem = NULL;
            }
            break;
        }
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
        {
            QRoundedRect *pRoundItem = dynamic_cast<QRoundedRect *>(pItem);
            if(pRoundItem)
            {
                delete pRoundItem;
                pRoundItem = NULL;
            }
            break;
        }
    case SAM_DRAW_OBJECT_ARC:
        {
            QArcItem *pArcItem = dynamic_cast<QArcItem *>(pItem);
            if(pArcItem)
            {
                delete pArcItem;
                pArcItem = NULL;
            }
            break;
        }
    case SAM_DRAW_OBJECT_GROUP:                //23
        {
            QItemGroup *pGroupItem = dynamic_cast<QItemGroup *>(pItem);
            if(pGroupItem)
            {
                delete pGroupItem;
                pGroupItem = NULL;
            }
            break;
        }
    default:
        {
            break;
        }
    }
}*/


QDataStream &operator<<(QDataStream &stream, SamDrawScene *pScene)
{
    //save scene background style
    stream << pScene->m_sceneRect << pScene->m_sceneBackColor;
    stream << pScene->m_sceneStyleColor << pScene->nSelectType;
    stream << pScene->nPattern << pScene->m_picturePath;
    stream << pScene->bShowMiddle;
    stream << pScene->bshowTitle;
    //stream << pScene->bShowOtherPos;
    //stream << pScene->bUseCloseBtn;
    //stream << pScene->bUseTitleStr;
    stream << pScene->mWindownShowPos;
    stream << pScene->nIsSceneOrWindow;
    stream << pScene->sNewScreenName;
    stream << pScene->sNumberName;
    stream << pScene->bLogout;
    //脚本
    int scriptSize=pScene->listScript.size();
    stream << scriptSize;
    for(int i=0;i<scriptSize;i++){
        stream << pScene->listScript[i].scriptAddr;
        stream << pScene->listScript[i].scriptBShow;
        stream << pScene->listScript[i].scriptCondition;
        stream << pScene->listScript[i].scriptFreq;
        stream << pScene->listScript[i].scriptCount;
        stream << pScene->listScript[i].scriptFuncName;
        stream << pScene->listScript[i].scriptName;
        stream << pScene->listScript[i].scriptType;
    }
    //画面属性
    stream << pScene->bIsAddMenu;
    stream << pScene->bSlide;
    stream << pScene->nTowardLeftId;
    stream << pScene->nTowardRIghtId;
    stream << pScene->nSlideStyle;
    //stream << pScene->sTitleStr;
    //end save scene background style
    QList<QGraphicsItem *> tmpList;
    QVector<QGraphicsItem *> itemList;
    tmpList.clear();
    itemList.clear();
    tmpList = pScene->items();
    int tmpSize = tmpList.size();
    for(int i=0;i < tmpSize;i++)
    {
        QGraphicsItem *pItem = tmpList.at(i);
        if(!pItem) continue;
        QGraphicsItem *pParentItem= pItem->parentItem();
        if(pParentItem != 0)
            continue;
        if(pItem->type() == SAM_DRAW_OBJECT_TRACKER
           || pItem->type() == SAM_DRAW_OBJECT_LOCK)
            continue;
        itemList.push_back(pItem);
    }

    int sceneItemsize = itemList.size();
    stream << sceneItemsize;

    for(int i=0; i < sceneItemsize; i++)
    {
        QGraphicsItem *pItem = itemList.at(i);
        if(!pItem) continue;
//        QGraphicsItem *pParentItem= itemList.at(i)->parentItem();
//        if(pParentItem != 0)
//            continue;

//        if(pItem->type() == SAM_DRAW_OBJECT_TRACKER)
//            continue;

        bool bIsMoved = true;
        if(!(pItem->flags() & QGraphicsItem::ItemIsMovable))
        {
            bIsMoved = false;
        }
        stream << bIsMoved;
        switch(pItem->type())
        {
        case SAM_DRAW_OBJECT_RECT_NEW:              //15
            {
                stream << QRectBasicItem::Type;
                QRectBasicItem *pRectItem = dynamic_cast<QRectBasicItem *>(pItem);
                stream << pRectItem;
                stream << pRectItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_ELIPSE_NEW:              //16
            {
                stream << QElipseBasicItem::Type;
                QElipseBasicItem *pElipseItem = dynamic_cast<QElipseBasicItem *>(pItem);
                stream << pElipseItem;
                stream << pElipseItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_LINE_NEW:                 //17
            {
                stream << QLineBasicItem::Type;
                QLineBasicItem *pLineItem = dynamic_cast<QLineBasicItem *>(pItem);
                stream << pLineItem;
                stream << pLineItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_POLYGON_NEW:              //18
            {
                stream << QPolygonBasicItem::Type;
                QPolygonBasicItem *pPolygonItem = dynamic_cast<QPolygonBasicItem *>(pItem);
                stream << pPolygonItem;
                stream << pPolygonItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:             //19
            {
                stream << QFoldLineBasicItem::Type;
                QFoldLineBasicItem *pFoldLineItem = dynamic_cast<QFoldLineBasicItem *>(pItem);
                stream << pFoldLineItem;
                stream << pFoldLineItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_FREELINE_NEW:             //20
            {
                stream << QFreeLineBasicItem::Type;
                QFreeLineBasicItem *pFreeLineItem = dynamic_cast<QFreeLineBasicItem *>(pItem);
                stream << pFreeLineItem;
                stream << pFreeLineItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_TEXT:                 //22
            {
                stream << QSimpleTextItem::Type;
                QSimpleTextItem *pTextItem = dynamic_cast<QSimpleTextItem *>(pItem);
                stream << pTextItem;
                stream << pTextItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_PIXMAP:
            {
                stream << QPixmapItem::Type;
                QPixmapItem *pPixmap = dynamic_cast<QPixmapItem *>(pItem);
                stream << pPixmap;
                stream << pPixmap->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_LINECIRCLE_NEW:           //25
            {
                stream << QLineCircleBasicItem::Type;
                QLineCircleBasicItem *pLineCircleItem = dynamic_cast<QLineCircleBasicItem *>(pItem);
                stream << pLineCircleItem;
                stream << pLineCircleItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
            {
                stream << QRoundedRectBasic::Type;
                QRoundedRectBasic *pRoundRect = dynamic_cast<QRoundedRectBasic *>(pItem);
                stream << pRoundRect;
                stream << pRoundRect->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_ARC_NEW:
            {
                stream << QArcBasicItem::Type;
                QArcBasicItem *pArcItem = dynamic_cast<QArcBasicItem *>(pItem);
                stream << pArcItem;
                stream << pArcItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_GROUP:                //23
            {
                //stream << QItemGroup::Type;
                QItemGroup *pItemGroup = dynamic_cast<QItemGroup *>(pItem);
                stream << pItemGroup->GroupType();
                pItemGroup->save(stream);
                stream << pItemGroup->zValue();
                break;
            }
////////////////wxy add start
        case SAM_DRAW_OBJECT_RECT:              //15
            {
                stream << QRectItem::Type;
                QRectItem *pRectItem = dynamic_cast<QRectItem *>(pItem);
                stream << pRectItem;
                stream << pRectItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_ELIPSE:              //16
            {
                stream << QElipseItem::Type;
                QElipseItem *pElipseItem = dynamic_cast<QElipseItem *>(pItem);
                stream << pElipseItem;
                stream << pElipseItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_LINE:                 //17
            {
                stream << QLineItem::Type;
                QLineItem *pLineItem = dynamic_cast<QLineItem *>(pItem);
                stream << pLineItem;
                stream << pLineItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_POLYGON:              //18
            {
                stream << QPolygonItem::Type;
                QPolygonItem *pPolygonItem = dynamic_cast<QPolygonItem *>(pItem);
                stream << pPolygonItem;
                stream << pPolygonItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_FOLDLINE:             //19
            {
                stream << QFoldLineItem::Type;
                QFoldLineItem *pFoldLineItem = dynamic_cast<QFoldLineItem *>(pItem);
                stream << pFoldLineItem;
                stream << pFoldLineItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_FREELINE:             //20
            {
                stream << QFreeLineItem::Type;
                QFreeLineItem *pFreeLineItem = dynamic_cast<QFreeLineItem *>(pItem);
                stream << pFreeLineItem;
                stream << pFreeLineItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_LINECIRCLE:           //25
            {
                stream << QLineCircleItem::Type;
                QLineCircleItem *pLineCircleItem = dynamic_cast<QLineCircleItem *>(pItem);
                stream << pLineCircleItem;
                stream << pLineCircleItem->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
            {
                stream << QRoundedRect::Type;
                QRoundedRect *pRoundRect = dynamic_cast<QRoundedRect *>(pItem);
                stream << pRoundRect;
                stream << pRoundRect->zValue();
                break;
            }
        case SAM_DRAW_OBJECT_ARC:
            {
                stream << QArcItem::Type;
                QArcItem *pArcItem = dynamic_cast<QArcItem *>(pItem);
                stream << pArcItem;
                stream << pArcItem->zValue();
                break;
            }
//////////////////wxy add end
        default:
            break;
        }
    }
    return stream;
}
QDataStream &operator>>(QDataStream &stream, SamDrawScene *pScene)
{
    //recover scene background style
    stream >> pScene->m_sceneRect >> pScene->m_sceneBackColor;
    stream >> pScene->m_sceneStyleColor >> pScene->nSelectType;
    stream >> pScene->nPattern >> pScene->m_picturePath;
    pScene->setSceneRect(pScene->m_sceneRect.x(),pScene->m_sceneRect.y(),
                         pScene->m_sceneRect.width(),pScene->m_sceneRect.height());

    stream >> pScene->bShowMiddle;
    if(pwnd->getProVersion() < 2681)
    {
        pScene->bshowTitle = false;
    }
    else
    {
        stream >> pScene->bshowTitle;
    }
    //s0tream >> pScene->bShowOtherPos;
    //stream >> pScene->bUseCloseBtn;
    //stream >> pScene->bUseTitleStr;
    stream >> pScene->mWindownShowPos;
    stream >> pScene->nIsSceneOrWindow;
    stream >> pScene->sNewScreenName;
    stream >> pScene->sNumberName;
    qDebug()<<"version ---"<<pwnd->getProVersion();
    if(pwnd->getProVersion() < 2054)
    {
        pScene->bLogout = false;

    }
    else
    {
        stream >> pScene->bLogout;
    }
    //脚本
    int scriptSize=0;
    stream >> scriptSize;
    for(int i=0;i<scriptSize;i++){
        SCRIPT_PROP scipt;
        stream >> scipt.scriptAddr;
        stream >> scipt.scriptBShow;
        stream >> scipt.scriptCondition;
        stream >> scipt.scriptFreq;
        if(pwnd->getProVersion() < 2052)
        {
            scipt.scriptCount = 0;
        }
        else
        {
            stream >> scipt.scriptCount;
        }

        stream >> scipt.scriptFuncName;
        stream >> scipt.scriptName;
        stream >> scipt.scriptType;
        pScene->listScript.append(scipt);
    }
    //画面属性
    stream >> pScene->bIsAddMenu;
    stream >> pScene->bSlide;
    stream >> pScene->nTowardLeftId;
    stream >> pScene->nTowardRIghtId;
    stream >> pScene->nSlideStyle;
    //stream >> pScene->sTitleStr;
    //end recover scene background style
    int sceneItemsize = 0;
    stream >> sceneItemsize;

    while(sceneItemsize > 0 && !stream.atEnd())
    {
        sceneItemsize-- ;
        int type = -1;//item加锁保存打开后重新加锁
        bool bIsMoved = true;
        stream >> bIsMoved;
        stream >> type;

        //qDebug() << "SAM_DRAW_OBJECT_TYPE:"<< type;
        switch(type)
        {
            case SAM_DRAW_OBJECT_RECT_NEW:              //15
            {
                QRectBasicItem *rectItem = new QRectBasicItem();
                stream >> rectItem;
                qreal zValue;
                stream >> zValue;
                rectItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                rectItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(rectItem,zValue);
                rectItem->refreshLockRect(rectItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //rectItem->setZValue(zValue);
            }
            break;
            case SAM_DRAW_OBJECT_ELIPSE_NEW:              //16
            {
                QElipseBasicItem *elipseItem = new QElipseBasicItem();
                stream >> elipseItem;
                qreal zValue;
                stream >> zValue;
                elipseItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                elipseItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(elipseItem,zValue);
                elipseItem->refreshLockRect(elipseItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //elipseItem->setZValue(zValue);
            }
            break;
            case SAM_DRAW_OBJECT_LINE_NEW:                 //17
            {
                QLineBasicItem *lineItem = new QLineBasicItem();
                stream >> lineItem;
                qreal zValue;
                stream >> zValue;
                lineItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                lineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(lineItem,zValue);
                lineItem->refreshLockRect(lineItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //lineItem->setZValue(zValue);
            }
            break;
            case SAM_DRAW_OBJECT_POLYGON_NEW:              //18
            {
                QPolygonBasicItem *polygonItem = new QPolygonBasicItem();
                stream >> polygonItem;
                qreal zValue;
                stream >> zValue;
                polygonItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                polygonItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(polygonItem,zValue);
                polygonItem->refreshLockRect(polygonItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //polygonItem->setZValue(zValue);
            }
            break;
            case SAM_DRAW_OBJECT_FOLDLINE_NEW:             //19
            {
                QFoldLineBasicItem *foldLineItem = new QFoldLineBasicItem();
                stream >> foldLineItem;
                qreal zValue;
                stream >> zValue;
                foldLineItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                foldLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(foldLineItem,zValue);
                foldLineItem->refreshLockRect(foldLineItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //foldLineItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_OBJECT_FREELINE_NEW:             //20
            {
                QFreeLineBasicItem *freeLineItem = new QFreeLineBasicItem();
                stream >> freeLineItem;
                qreal zValue;
                stream >> zValue;
                freeLineItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                freeLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(freeLineItem,zValue);
                freeLineItem->refreshLockRect(freeLineItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //freeLineItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_OBJECT_TEXT:                 //22
            {
                QSimpleTextItem *textItem = new QSimpleTextItem();
                stream >> textItem;
                qreal zValue;
                stream >> zValue;
                textItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                textItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(textItem,zValue);
                textItem->refreshLockRect(textItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //textItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_OBJECT_PIXMAP:
            {
                QPixmapItem *pPixmap = new QPixmapItem();
                stream >> pPixmap;
                qreal zValue;
                stream >> zValue;
                pPixmap->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                pPixmap->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(pPixmap,zValue);
                //pPixmap->setZValue(zValue);
                break;
            }
            case SAM_DRAW_OBJECT_LINECIRCLE_NEW:           //25
            {
                QLineCircleBasicItem *lineCircleItem = new QLineCircleBasicItem();
                stream >> lineCircleItem;
                qreal zValue;
                stream >> zValue;
                lineCircleItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                lineCircleItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(lineCircleItem,zValue);
                lineCircleItem->refreshLockRect(lineCircleItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //lineCircleItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
            {
                QRoundedRectBasic *pRoundItem = new QRoundedRectBasic();
                stream >> pRoundItem;
                qreal zValue;
                stream >> zValue;
                pRoundItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                pRoundItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(pRoundItem,zValue);
                pRoundItem->refreshLockRect(pRoundItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //pRoundItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_OBJECT_ARC_NEW:
            {
                QArcBasicItem *pArcItem = new QArcBasicItem();
                stream >> pArcItem;
                qreal zValue;
                stream >> zValue;
                pArcItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                pArcItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(pArcItem,zValue);
                pArcItem->refreshLockRect(pArcItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //pArcItem->setZValue(zValue);
                break;
            }

/////////////wxy add start
        case SAM_DRAW_OBJECT_RECT:              //15
        {
            QRectItem *rectItem = new QRectItem();
            stream >> rectItem;
            if(pwnd->getProVersion() >= 3257 && pwnd->getProVersion() < 3439)
            {
                QBasicGraphicsItem* pBasicItem = new QBasicGraphicsItem();
                pBasicItem->load(stream);
            }
            qreal zValue;
            stream >> zValue;
            rectItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
            rectItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            pScene->addItem(rectItem,zValue);
            rectItem->refreshLockRect(rectItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            //rectItem->setZValue(zValue);
        }
        break;
        case SAM_DRAW_OBJECT_ELIPSE:              //16
        {
            QElipseItem *elipseItem = new QElipseItem();
            stream >> elipseItem;
            if(pwnd->getProVersion() >= 3257 && pwnd->getProVersion() < 3439)
            {
                QBasicGraphicsItem* pBasicItem = new QBasicGraphicsItem();
                pBasicItem->load(stream);
            }
            qreal zValue;
            stream >> zValue;
            elipseItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
            elipseItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            pScene->addItem(elipseItem,zValue);
            elipseItem->refreshLockRect(elipseItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            //elipseItem->setZValue(zValue);
        }
        break;
        case SAM_DRAW_OBJECT_LINE:                 //17
        {
            QLineItem *lineItem = new QLineItem();
            stream >> lineItem;
            if(pwnd->getProVersion() >= 3257 && pwnd->getProVersion() < 3439)
            {
                QBasicGraphicsItem* pBasicItem = new QBasicGraphicsItem();
                pBasicItem->load(stream);
            }
            qreal zValue;
            stream >> zValue;
            lineItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
            lineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            pScene->addItem(lineItem,zValue);
            lineItem->refreshLockRect(lineItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            //lineItem->setZValue(zValue);
        }
        break;
        case SAM_DRAW_OBJECT_POLYGON:              //18
        {
            QPolygonItem *polygonItem = new QPolygonItem();
            stream >> polygonItem;
            if(pwnd->getProVersion() >= 3257 && pwnd->getProVersion() < 3439)
            {
                QBasicGraphicsItem* pBasicItem = new QBasicGraphicsItem();
                pBasicItem->load(stream);
            }
            qreal zValue;
            stream >> zValue;
            polygonItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
            polygonItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            pScene->addItem(polygonItem,zValue);
            polygonItem->refreshLockRect(polygonItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            //polygonItem->setZValue(zValue);
        }
        break;
        case SAM_DRAW_OBJECT_FOLDLINE:             //19
        {
            QFoldLineItem *foldLineItem = new QFoldLineItem();
            stream >> foldLineItem;
            if(pwnd->getProVersion() >= 3257 && pwnd->getProVersion() < 3439)
            {
                QBasicGraphicsItem* pBasicItem = new QBasicGraphicsItem();
                pBasicItem->load(stream);
            }
            qreal zValue;
            stream >> zValue;
            foldLineItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
            foldLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            pScene->addItem(foldLineItem,zValue);
            foldLineItem->refreshLockRect(foldLineItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            //foldLineItem->setZValue(zValue);
            break;
        }
        case SAM_DRAW_OBJECT_FREELINE:             //20
        {
            QFreeLineItem *freeLineItem = new QFreeLineItem();
            stream >> freeLineItem;
            if(pwnd->getProVersion() >= 3257 && pwnd->getProVersion() < 3439)
            {
                QBasicGraphicsItem* pBasicItem = new QBasicGraphicsItem();
                pBasicItem->load(stream);
            }
            qreal zValue;
            stream >> zValue;
            freeLineItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
            freeLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            pScene->addItem(freeLineItem,zValue);
            freeLineItem->refreshLockRect(freeLineItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            //freeLineItem->setZValue(zValue);
            break;
        }
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
        {
            QRoundedRect *pRoundItem = new QRoundedRect();
            stream >> pRoundItem;
            if(pwnd->getProVersion() >= 3257 && pwnd->getProVersion() < 3439)
            {
                QBasicGraphicsItem* pBasicItem = new QBasicGraphicsItem();
                pBasicItem->load(stream);
            }
            qreal zValue;
            stream >> zValue;
            pRoundItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
            pRoundItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            pScene->addItem(pRoundItem,zValue);
            pRoundItem->refreshLockRect(pRoundItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            //pRoundItem->setZValue(zValue);
            break;
        }
        case SAM_DRAW_OBJECT_ARC:
        {
            QArcItem *pArcItem = new QArcItem();
            stream >> pArcItem;
            if(pwnd->getProVersion() >= 3257 && pwnd->getProVersion() < 3439)
            {
                QBasicGraphicsItem* pBasicItem = new QBasicGraphicsItem();
                pBasicItem->load(stream);
            }
            qreal zValue;
            stream >> zValue;
            pArcItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
            pArcItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            pScene->addItem(pArcItem,zValue);
            pArcItem->refreshLockRect(pArcItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            //pArcItem->setZValue(zValue);
            break;
        }
        case SAM_DRAW_OBJECT_LINECIRCLE:           //25
        {
            QLineCircleItem *lineCircleItem = new QLineCircleItem();
            stream >> lineCircleItem;
            if(pwnd->getProVersion() >= 3257 && pwnd->getProVersion() < 3439)
            {
                QBasicGraphicsItem* pBasicItem = new QBasicGraphicsItem();
                pBasicItem->load(stream);
            }
            qreal zValue;
            stream >> zValue;
            lineCircleItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
            lineCircleItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            pScene->addItem(lineCircleItem,zValue);
            lineCircleItem->refreshLockRect(lineCircleItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            //lineCircleItem->setZValue(zValue);
            break;
        }
///////////wxy add end

            case SAM_DRAW_OBJECT_GROUP:
            case SAM_DRAW_GROUP_USER:                //23
            {
                QItemGroup *groupItem = new QItemGroup();
                //groupItem->loadEx(stream);
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->redrawForChangeStatus(groupItem->getCurrentState(),0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_KEY:
            {
                KeyBoardItem *groupItem = new KeyBoardItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->redrawForChangeStatus(0, 0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_STATICTEXT:
            {
                StaticTextItem *groupItem = new StaticTextItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_MESSAGE:
            {
                QMessageShowAttr *groupItem = new QMessageShowAttr;
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_FLOW://流动块
            {
                FlowBlockItem *groupItem = new FlowBlockItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_CALIBRATION://刻度
            {
                CalibrationItem *groupItem = new CalibrationItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_SLIDER://滑动块
            {
                SliderItem *groupItem = new SliderItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_ALARMBAR://动态报警条
            {
                AlarmBar *groupItem = new AlarmBar();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_ALARMITEM://动态报警条item
            {
                AlarmItem *groupItem = new AlarmItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_HISALARMITEM://动态报警条item
            {
                HisAlarmItem *groupItem = new HisAlarmItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_SWITCH://开关
            {
                SwitchItem *groupItem = new SwitchItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->redrawForChangeStatus(groupItem->curSta,0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_VALUE:
            case SAM_DRAW_GROUP_TIME:
            case SAM_DRAW_GROUP_ASCII:
            {
                DataDisplayItem *groupItem = new DataDisplayItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->textItem = groupItem->GetTextItem();
                groupItem->redrawForChangeStatus(groupItem->getCurrentState(),0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_RECIPE:
            {
                QRcipeItem *groupItem = new QRcipeItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_RECIPESHOW:
            {
                QRecipeTableItem *groupItem = new QRecipeTableItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_STATICPIC:
            {
                QStaticPictureItem *groupItem = new QStaticPictureItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->redrawForChangeStatus(0,0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_IMAGE:
            {
                ImageItem *groupItem = new ImageItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->redrawForChangeStatus(groupItem->getCurrentState(),0);
                //groupItem->setZValue(zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                break;
            }
            case SAM_DRAW_GROUP_ANIMATION:
            {
                AnimationItem *groupItem = new AnimationItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->redrawForChangeStatus(groupItem->getCurrentState(),0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_CHART:
            {
                ChartItem *groupItem = new ChartItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                //groupItem->setZValue(zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                break;
            }
            case SAM_DRAW_GROUP_DYNCIRCLE://动态圆
            {
                DynCircleAttr *groupItem = new DynCircleAttr();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_DYNRECT://动态矩形
            {
                DynRectAttr *groupItem = new DynRectAttr();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_TREND://曲线
            {
                QTrendAttr *groupItem = new QTrendAttr();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                //groupItem->setZValue(zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                break;
            }
            case SAM_DRAW_GROUP_GROUPDATA://数据群组
            {
                QTrendDataGroupAttr *groupItem = new QTrendDataGroupAttr();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                //groupItem->setZValue(zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                break;
            }
            case SAM_DRAW_GROUP_TABLE://表格
            {
                QTableItem *groupItem = new QTableItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                //groupItem->setZValue(zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                break;
            }
            case SAM_DRAW_GROUP_DROPDOWN://下拉框
            {
                QDropdownAttr *groupItem = new QDropdownAttr;
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
				break;
            }
            case SAM_DRAW_GROUP_HISTORYDATE://历史数据显示器
            {
                QHistoryDataShowAttr *groupItem = new QHistoryDataShowAttr;
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            }
            break;
            case SAM_DRAW_GROUP_TEXTBOARD://留言板
            {
                qMessageBoradAttr *groupItem = new qMessageBoradAttr;
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            }
            break;
            case SAM_DRAW_GROUP_MFBTN://多功能按钮
            {
                MfBtnItem *groupItem = new MfBtnItem;
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->redrawForChangeStatus(0, 0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            }
            break;

            case SAM_DRAW_GROUP_COMBOBOX://下拉框
            {
                AkComboItem *groupItem = new AkComboItem;
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->redrawForChangeStatus(0, 0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            }
            break;
            case SAM_DRAW_GROUP_XYTREND://曲线
            {
                XYtrend *groupItem = new XYtrend();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                //groupItem->setZValue(zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                break;
            }
            default:
            break;
        }//switch end
    }//while end
    return stream;
}
QGraphicsItem* SamDrawScene::loadItemFromStream(QDataStream &stream,int type)
{
    QGraphicsItem *item = NULL;
    qreal zValue = 0;
    switch(type)
    {
        case SAM_DRAW_OBJECT_RECT_NEW:              //15
        {
            QRectBasicItem *rectItem = new QRectBasicItem();
            stream >> rectItem;

            stream >> zValue;
            rectItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            rectItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = rectItem;
            item->setZValue(zValue);
            break;
        }
        case SAM_DRAW_OBJECT_ELIPSE_NEW:              //16
        {
            QElipseBasicItem *elipseItem = new QElipseBasicItem();
            stream >> elipseItem;

            stream >> zValue;
            elipseItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            elipseItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = elipseItem;
            item->setZValue(zValue);
            break;
        }
        case SAM_DRAW_OBJECT_LINE_NEW:                 //17
        {
            QLineBasicItem *lineItem = new QLineBasicItem();
            stream >> lineItem;

            stream >> zValue;
            lineItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            lineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = lineItem;
            item->setZValue(zValue);
            break;
        }
        case SAM_DRAW_OBJECT_POLYGON_NEW:              //18
        {
            QPolygonBasicItem*polygonItem = new QPolygonBasicItem();
            stream >> polygonItem;

            stream >> zValue;
            polygonItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            polygonItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = polygonItem;
            item->setZValue(zValue);
            break;
        }
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:             //19
        {
            QFoldLineBasicItem *foldLineItem = new QFoldLineBasicItem();
            stream >> foldLineItem;

            stream >> zValue;
            foldLineItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            foldLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = foldLineItem;
            item->setZValue(zValue);
            break;
        }
        case SAM_DRAW_OBJECT_FREELINE_NEW:             //20
        {
            QFreeLineBasicItem *freeLineItem = new QFreeLineBasicItem();
            stream >> freeLineItem;

            stream >> zValue;
            freeLineItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            freeLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = freeLineItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_OBJECT_TEXT:                 //22
        {
            QSimpleTextItem *textItem = new QSimpleTextItem();
            stream >> textItem;

            stream >> zValue;
            textItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            textItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = textItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_OBJECT_PIXMAP:
        {
            QPixmapItem *pPixmap = new QPixmapItem();
            stream >> pPixmap;

            stream >> zValue;
            pPixmap->setFlag(QGraphicsItem::ItemIsMovable, true);
            pPixmap->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = pPixmap;
            item->setZValue(zValue);
            break;
        }
        case SAM_DRAW_OBJECT_LINECIRCLE_NEW:           //25
        {
            QLineCircleBasicItem *lineCircleItem = new QLineCircleBasicItem();
            stream >> lineCircleItem;

            stream >> zValue;
            lineCircleItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            lineCircleItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = lineCircleItem;
            item->setZValue(zValue);
            break;
        }
        case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
        {
            QRoundedRectBasic *pRoundItem = new QRoundedRectBasic();
            stream >> pRoundItem;

            stream >> zValue;
            pRoundItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            pRoundItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = pRoundItem;
            item->setZValue(zValue);
            break;
        }
        case SAM_DRAW_OBJECT_ARC_NEW:
        {
            QArcBasicItem *pArcItem = new QArcBasicItem();
            stream >> pArcItem;

            stream >> zValue;
            pArcItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            pArcItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = pArcItem;
            item->setZValue(zValue);
            break;
        }
/////////////wxy add start
    case SAM_DRAW_OBJECT_RECT:              //15
    {
        QRectItem *rectItem = new QRectItem();
        stream >> rectItem;

        stream >> zValue;
        rectItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        rectItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        item = rectItem;
        item->setZValue(zValue);
        break;
    }
    case SAM_DRAW_OBJECT_ELIPSE:              //16
    {
        QElipseItem *elipseItem = new QElipseItem();
        stream >> elipseItem;

        stream >> zValue;
        elipseItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        elipseItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        item = elipseItem;
        item->setZValue(zValue);
        break;
    }
    case SAM_DRAW_OBJECT_LINE:                 //17
    {
        QLineItem *lineItem = new QLineItem();
        stream >> lineItem;

        stream >> zValue;
        lineItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        lineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        item = lineItem;
        item->setZValue(zValue);
        break;
    }
    case SAM_DRAW_OBJECT_POLYGON:              //18
    {
        QPolygonItem*polygonItem = new QPolygonItem();
        stream >> polygonItem;

        stream >> zValue;
        polygonItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        polygonItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        item = polygonItem;
        item->setZValue(zValue);
        break;
    }
    case SAM_DRAW_OBJECT_FOLDLINE:             //19
    {
        QFoldLineItem *foldLineItem = new QFoldLineItem();
        stream >> foldLineItem;

        stream >> zValue;
        foldLineItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        foldLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        item = foldLineItem;
        item->setZValue(zValue);
        break;
    }
    case SAM_DRAW_OBJECT_FREELINE:             //20
    {
        QFreeLineItem *freeLineItem = new QFreeLineItem();
        stream >> freeLineItem;

        stream >> zValue;
        freeLineItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        freeLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        item = freeLineItem;
        item->setZValue(zValue);
        break;
    }
    case SAM_DRAW_OBJECT_LINECIRCLE:           //25
    {
        QLineCircleItem *lineCircleItem = new QLineCircleItem();
        stream >> lineCircleItem;

        stream >> zValue;
        lineCircleItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        lineCircleItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        item = lineCircleItem;
        item->setZValue(zValue);
        break;
    }
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
    {
        QRoundedRect *pRoundItem = new QRoundedRect();
        stream >> pRoundItem;

        stream >> zValue;
        pRoundItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        pRoundItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        item = pRoundItem;
        item->setZValue(zValue);
        break;
    }
    case SAM_DRAW_OBJECT_ARC:
    {
        QArcItem *pArcItem = new QArcItem();
        stream >> pArcItem;

        stream >> zValue;
        pArcItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        pArcItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        item = pArcItem;
        item->setZValue(zValue);
        break;
    }
/////////////wxy add end
	case SAM_DRAW_GROUP_USER:                //23
        {
            QItemGroup *groupItem = new QItemGroup();
            //groupItem->loadEx(stream);
            groupItem->load(stream);
            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_KEY:
        {
            KeyBoardItem *groupItem = new KeyBoardItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_STATICTEXT:
        {
            StaticTextItem *groupItem = new StaticTextItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_MESSAGE:
        {
            QMessageShowAttr *groupItem = new QMessageShowAttr;
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_FLOW://流动块
        {
            FlowBlockItem *groupItem = new FlowBlockItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_CALIBRATION://刻度
        {
            CalibrationItem *groupItem = new CalibrationItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_SLIDER://滑动块
        {
            SliderItem *groupItem = new SliderItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_ALARMBAR://动态报警条
        {
            AlarmBar *groupItem = new AlarmBar();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_ALARMITEM://动态报警条item
        {
            AlarmItem *groupItem = new AlarmItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_HISALARMITEM://动态报警条item
        {
            HisAlarmItem *groupItem = new HisAlarmItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_SWITCH://开关
        {
            SwitchItem *groupItem = new SwitchItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_VALUE:
	case SAM_DRAW_GROUP_TIME:
	case SAM_DRAW_GROUP_ASCII:
        {
            DataDisplayItem *groupItem = new DataDisplayItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_RECIPE:
        {
            QRcipeItem *groupItem = new QRcipeItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_RECIPESHOW:
        {
            QRecipeTableItem *groupItem = new QRecipeTableItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_STATICPIC:
        {
            QStaticPictureItem *groupItem = new QStaticPictureItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_IMAGE:
        {
            ImageItem *groupItem = new ImageItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_ANIMATION:
        {
            AnimationItem *groupItem = new AnimationItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
	case SAM_DRAW_GROUP_CHART:
        {
            ChartItem *groupItem = new ChartItem();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
        case SAM_DRAW_GROUP_DYNCIRCLE://动态圆
        {
            DynCircleAttr *groupItem = new DynCircleAttr();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
        case SAM_DRAW_GROUP_DYNRECT://动态矩形
        {
            DynRectAttr *groupItem = new DynRectAttr();
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }
        case SAM_DRAW_GROUP_DROPDOWN://
        {
            QDropdownAttr *groupItem = new QDropdownAttr;
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }

        case SAM_DRAW_GROUP_COMBOBOX://
        {
            AkComboItem *groupItem = new AkComboItem;
            groupItem->load(stream);

            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item = groupItem;
            item->setZValue(zValue);
            break;
        }

    case SAM_DRAW_GROUP_TABLE://表格
    {
        QTableItem *groupItem = new QTableItem();
        groupItem->load(stream);
        qreal zValue;
        stream >> zValue;
        groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        groupItem->setZValue(zValue);
        item = groupItem;
        //groupItem->setZValue(zValue);
        break;
    }
    case SAM_DRAW_GROUP_TREND://曲线
    {
        QTrendAttr *groupItem = new QTrendAttr();
        groupItem->load(stream);
        qreal zValue;
        stream >> zValue;
        groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        groupItem->setZValue(zValue);
        item = groupItem;
        break;
    }
    case SAM_DRAW_GROUP_GROUPDATA://数据群组
    {
        QTrendDataGroupAttr *groupItem = new QTrendDataGroupAttr();
        groupItem->load(stream);
        qreal zValue;
        stream >> zValue;
        groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        groupItem->setZValue(zValue);
        item = groupItem;
        break;
    }
    case SAM_DRAW_GROUP_HISTORYDATE://历史数据显示器
    {
        QHistoryDataShowAttr *groupItem = new QHistoryDataShowAttr;
        groupItem->load(stream);
        qreal zValue;
        stream >> zValue;
        groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        groupItem->setZValue(zValue);
        item = groupItem;
        break;
    }
    case SAM_DRAW_GROUP_TEXTBOARD://留言板
    {
        qMessageBoradAttr *groupItem = new qMessageBoradAttr;
        groupItem->load(stream);
        qreal zValue;
        stream >> zValue;
        groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        groupItem->setZValue(zValue);
        item = groupItem;
        break;
    }
    case SAM_DRAW_GROUP_MFBTN://多功能按钮
        {
            MfBtnItem *groupItem = new MfBtnItem;
            groupItem->load(stream);
            qreal zValue;
            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            groupItem->setZValue(zValue);
            item = groupItem;
            break;
        }
    case SAM_DRAW_GROUP_XYTREND://曲线
        {
            XYtrend *groupItem = new XYtrend();
            groupItem->load(stream);
            qreal zValue;
            stream >> zValue;
            groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            groupItem->setZValue(zValue);
            item = groupItem;
            break;
        }
    default:
        break;
    }
    return item;
}
void SamDrawScene::actionCopy()
{
        QList <QGraphicsItem *> selList;
        selList = this->selectedItems();
        QGraphicsItem * pTem_leftMin = NULL;
        QGraphicsItem * pTem_origin = NULL;
        qreal nleftPos;
        if (selList.size() != 0)
        {
            for(int i=0;i<selList.size();i++)//选择的项根据x值从左排到右
            {
                nleftPos=selList.at(i)->zValue();
                for(int j=i+1;j<selList.size();j++)
                {
                    if(selList.at(j)->zValue()<=nleftPos)
                    {
                        nleftPos=selList.at(j)->zValue();
                        pTem_leftMin=selList.at(j);
                        pTem_origin=selList.at(i);
                        selList.replace(i,pTem_leftMin);
                        selList.replace(j,pTem_origin);
                    }
                }
            }
            QByteArray CopyBuf;
            QDataStream out(&CopyBuf,QIODevice::WriteOnly);
            //DrawItemToScene CopyFun;
            //CopyList.clear();
            //out<<"Samkoon_Item_data";
            out<<selList.size();
            //qDebug() << "copy size ======="<< selList.size();
            foreach(QGraphicsItem * pItem,selList)
            {
                switch(pItem->type())
                {
                case SAM_DRAW_OBJECT_RECT_NEW:              //15
                    {
                        out << QRectBasicItem::Type;
                        QRectBasicItem *pRectItem = dynamic_cast<QRectBasicItem *>(pItem);
                        out << pRectItem;
                        out << pRectItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_ELIPSE_NEW:              //16
                    {
                        out << QElipseBasicItem::Type;
                        QElipseBasicItem *pElipseItem = dynamic_cast<QElipseBasicItem *>(pItem);
                        out << pElipseItem;
                        out << pElipseItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_LINE_NEW:                 //17
                    {
                        out << QLineBasicItem::Type;
                        QLineBasicItem *pLineItem = dynamic_cast<QLineBasicItem *>(pItem);
                        out << pLineItem;
                        out << pLineItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_POLYGON_NEW:              //18
                    {
                        out << QPolygonBasicItem::Type;
                        QPolygonBasicItem *pPolygonItem = dynamic_cast<QPolygonBasicItem *>(pItem);
                        out << pPolygonItem;
                        out << pPolygonItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_FOLDLINE_NEW:             //19
                    {
                        out << QFoldLineBasicItem::Type;
                        QFoldLineBasicItem *pFoldLineItem = dynamic_cast<QFoldLineBasicItem *>(pItem);
                        out << pFoldLineItem;
                        out << pFoldLineItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_FREELINE_NEW:             //20
                    {
                        out << QFreeLineBasicItem::Type;
                        QFreeLineBasicItem *pFreeLineItem = dynamic_cast<QFreeLineBasicItem *>(pItem);
                        out << pFreeLineItem;
                        out << pFreeLineItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_TEXT:                 //22
                    {
                        out << QSimpleTextItem::Type;
                        QSimpleTextItem *pTextItem = dynamic_cast<QSimpleTextItem *>(pItem);
                        out << pTextItem;
                        out << pTextItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_PIXMAP:
                    {
                        out << QPixmapItem::Type;
                        QPixmapItem *pPixmap = dynamic_cast<QPixmapItem *>(pItem);
                        out << pPixmap;
                        out << pPixmap->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_LINECIRCLE_NEW:           //25
                    {
                        out << QLineCircleBasicItem::Type;
                        QLineCircleBasicItem *pLineCircleItem = dynamic_cast<QLineCircleBasicItem *>(pItem);
                        out << pLineCircleItem;
                        out << pLineCircleItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
                    {
                        out << QRoundedRectBasic::Type;
                        QRoundedRectBasic *pRoundRect = dynamic_cast<QRoundedRectBasic *>(pItem);
                        out << pRoundRect;
                        out << pRoundRect->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_ARC_NEW:
                    {
                        out << QArcBasicItem::Type;
                        QArcBasicItem *pArcItem = dynamic_cast<QArcBasicItem *>(pItem);
                        out << pArcItem;
                        out << pArcItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_GROUP:                //23
                    {
                        pwnd->bCpyAndPaste = true;
                        QItemGroup *pItemGroup = dynamic_cast<QItemGroup *>(pItem);
                                                out << pItemGroup->GroupType();
                        pItemGroup->save(out);
                        out << pItemGroup->zValue();
                        pwnd->bCpyAndPaste = false;
                        break;
                    }
///////////////////wxy add start
                case SAM_DRAW_OBJECT_RECT:              //15
                    {
                        out << QRectItem::Type;
                        QRectItem *pRectItem = dynamic_cast<QRectItem *>(pItem);
                        out << pRectItem;
                        out << pRectItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_ELIPSE:              //16
                    {
                        out << QElipseItem::Type;
                        QElipseItem *pElipseItem = dynamic_cast<QElipseItem *>(pItem);
                        out << pElipseItem;
                        out << pElipseItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_LINE:                 //17
                    {
                        out << QLineItem::Type;
                        QLineItem *pLineItem = dynamic_cast<QLineItem *>(pItem);
                        out << pLineItem;
                        out << pLineItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_POLYGON:              //18
                    {
                        out << QPolygonItem::Type;
                        QPolygonItem *pPolygonItem = dynamic_cast<QPolygonItem *>(pItem);
                        out << pPolygonItem;
                        out << pPolygonItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_FOLDLINE:             //19
                    {
                        out << QFoldLineItem::Type;
                        QFoldLineItem *pFoldLineItem = dynamic_cast<QFoldLineItem *>(pItem);
                        out << pFoldLineItem;
                        out << pFoldLineItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_FREELINE:             //20
                    {
                        out << QFreeLineItem::Type;
                        QFreeLineItem *pFreeLineItem = dynamic_cast<QFreeLineItem *>(pItem);
                        out << pFreeLineItem;
                        out << pFreeLineItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_LINECIRCLE:           //25
                    {
                        out << QLineCircleItem::Type;
                        QLineCircleItem *pLineCircleItem = dynamic_cast<QLineCircleItem *>(pItem);
                        out << pLineCircleItem;
                        out << pLineCircleItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_ROUNDEDRECT:
                    {
                        out << QRoundedRect::Type;
                        QRoundedRect *pRoundRect = dynamic_cast<QRoundedRect *>(pItem);
                        out << pRoundRect;
                        out << pRoundRect->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_ARC:
                    {
                        out << QArcItem::Type;
                        QArcItem *pArcItem = dynamic_cast<QArcItem *>(pItem);
                        out << pArcItem;
                        out << pArcItem->zValue();
                        break;
                    }
//////////////////wxy  add end
                default:
                    break;
                }

                //CopyFun.CopyItem(&pTem,pItem);
                //CopyList.append(pTem);
                //pTem = NULL;
            }
            QMimeData *mimeData = new QMimeData;
            mimeData->setData("Samkoon_Item",CopyBuf);
            QClipboard *cb = QApplication::clipboard();
            cb->setMimeData(mimeData);
        }
}
void SamDrawScene::actionCut()
{
    if(pwnd->isCompiled)
    {
        return;
    }
    QList <QGraphicsItem *> selList;
    selList = this->selectedItems();
    QGraphicsItem * pTem_leftMin = NULL;
    QGraphicsItem * pTem_origin = NULL;
    qreal nleftPos;
    if (selList.size() != 0)
    {
            //DrawItemToScene CopyFun;

            foreach(QGraphicsItem * pItem,selList)
            {
                    removeItem(pItem);
            }
            for(int i=0;i<selList.size();i++)//选择的项根据x值从左排到右
            {
                nleftPos=selList.at(i)->zValue();
                for(int j=i+1;j<selList.size();j++)
                {
                    if(selList.at(j)->zValue()<=nleftPos)
                    {
                        nleftPos=selList.at(j)->zValue();
                        pTem_leftMin=selList.at(j);
                        pTem_origin=selList.at(i);
                        selList.replace(i,pTem_leftMin);
                        selList.replace(j,pTem_origin);
                    }
                }
            }
            QByteArray CopyBuf;
            QDataStream out(&CopyBuf,QIODevice::WriteOnly);
            //DrawItemToScene CopyFun;
            //CopyList.clear();
            //out<<"Samkoon_Item_data";
            out<<selList.size();
            foreach(QGraphicsItem * pItem,selList)
            {
                switch(pItem->type())
                {
                case SAM_DRAW_OBJECT_RECT_NEW:              //15
                    {
                        out << QRectBasicItem::Type;
                        QRectBasicItem *pRectItem = dynamic_cast<QRectBasicItem *>(pItem);
                        out << pRectItem;
                        out << pRectItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_ELIPSE_NEW:              //16
                    {
                        out << QElipseBasicItem::Type;
                        QElipseBasicItem *pElipseItem = dynamic_cast<QElipseBasicItem *>(pItem);
                        out << pElipseItem;
                        out << pElipseItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_LINE_NEW:                 //17
                    {
                        out << QLineBasicItem::Type;
                        QLineBasicItem *pLineItem = dynamic_cast<QLineBasicItem *>(pItem);
                        out << pLineItem;
                        out << pLineItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_POLYGON_NEW:              //18
                    {
                        out << QPolygonBasicItem::Type;
                        QPolygonBasicItem *pPolygonItem = dynamic_cast<QPolygonBasicItem *>(pItem);
                        out << pPolygonItem;
                        out << pPolygonItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_FOLDLINE_NEW:             //19
                    {
                        out << QFoldLineBasicItem::Type;
                        QFoldLineBasicItem *pFoldLineItem = dynamic_cast<QFoldLineBasicItem *>(pItem);
                        out << pFoldLineItem;
                        out << pFoldLineItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_FREELINE_NEW:             //20
                    {
                        out << QFreeLineBasicItem::Type;
                        QFreeLineBasicItem *pFreeLineItem = dynamic_cast<QFreeLineBasicItem *>(pItem);
                        out << pFreeLineItem;
                        out << pFreeLineItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_TEXT:                 //22
                    {
                        out << QSimpleTextItem::Type;
                        QSimpleTextItem *pTextItem = dynamic_cast<QSimpleTextItem *>(pItem);
                        out << pTextItem;
                        out << pTextItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_PIXMAP:
                    {
                        out << QPixmapItem::Type;
                        QPixmapItem *pPixmap = dynamic_cast<QPixmapItem *>(pItem);
                        out << pPixmap;
                        out << pPixmap->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_LINECIRCLE_NEW:           //25
                    {
                        out << QLineCircleBasicItem::Type;
                        QLineCircleBasicItem *pLineCircleItem = dynamic_cast<QLineCircleBasicItem *>(pItem);
                        out << pLineCircleItem;
                        out << pLineCircleItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
                    {
                        out << QRoundedRectBasic::Type;
                        QRoundedRectBasic *pRoundRect = dynamic_cast<QRoundedRectBasic *>(pItem);
                        out << pRoundRect;
                        out << pRoundRect->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_ARC_NEW:
                    {
                        out << QArcBasicItem::Type;
                        QArcBasicItem *pArcItem = dynamic_cast<QArcBasicItem *>(pItem);
                        out << pArcItem;
                        out << pArcItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_GROUP:                //23
                    {
                        //out << QItemGroup::Type;
                        pwnd->bCpyAndPaste = true;
                        QItemGroup *pItemGroup = dynamic_cast<QItemGroup *>(pItem);
                        out << pItemGroup->GroupType();
                        //out << pItemGroup;
                        pItemGroup->save(out);
                        out << pItemGroup->zValue();
                        pwnd->bCpyAndPaste = false;
                        break;
                    }
///////////////////wxy add start
                case SAM_DRAW_OBJECT_RECT:              //15
                    {
                        out << QRectItem::Type;
                        QRectItem *pRectItem = dynamic_cast<QRectItem *>(pItem);
                        out << pRectItem;
                        out << pRectItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_ELIPSE:              //16
                    {
                        out << QElipseItem::Type;
                        QElipseItem *pElipseItem = dynamic_cast<QElipseItem *>(pItem);
                        out << pElipseItem;
                        out << pElipseItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_LINE:                 //17
                    {
                        out << QLineItem::Type;
                        QLineItem *pLineItem = dynamic_cast<QLineItem *>(pItem);
                        out << pLineItem;
                        out << pLineItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_POLYGON:              //18
                    {
                        out << QPolygonItem::Type;
                        QPolygonItem *pPolygonItem = dynamic_cast<QPolygonItem *>(pItem);
                        out << pPolygonItem;
                        out << pPolygonItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_FOLDLINE:             //19
                    {
                        out << QFoldLineItem::Type;
                        QFoldLineItem *pFoldLineItem = dynamic_cast<QFoldLineItem *>(pItem);
                        out << pFoldLineItem;
                        out << pFoldLineItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_FREELINE:             //20
                    {
                        out << QFreeLineItem::Type;
                        QFreeLineItem *pFreeLineItem = dynamic_cast<QFreeLineItem *>(pItem);
                        out << pFreeLineItem;
                        out << pFreeLineItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_LINECIRCLE:           //25
                    {
                        out << QLineCircleItem::Type;
                        QLineCircleItem *pLineCircleItem = dynamic_cast<QLineCircleItem *>(pItem);
                        out << pLineCircleItem;
                        out << pLineCircleItem->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_ROUNDEDRECT:
                    {
                        out << QRoundedRect::Type;
                        QRoundedRect *pRoundRect = dynamic_cast<QRoundedRect *>(pItem);
                        out << pRoundRect;
                        out << pRoundRect->zValue();
                        break;
                    }
                case SAM_DRAW_OBJECT_ARC:
                    {
                        out << QArcItem::Type;
                        QArcItem *pArcItem = dynamic_cast<QArcItem *>(pItem);
                        out << pArcItem;
                        out << pArcItem->zValue();
                        break;
                    }
///////////////////wxy add end
                default:
                    break;
                }

                //CopyFun.CopyItem(&pTem,pItem);
                //CopyList.append(pTem);
                //pTem = NULL;
            }
            QMimeData *mimeData = new QMimeData;
            mimeData->setData("Samkoon_Item",CopyBuf);
            QClipboard *cb = QApplication::clipboard();
            cb->setMimeData(mimeData);
    }
    pwnd->deleteItem_upDateTreeContrl(selList);
    pwnd->undoStack->push(new cutItemCommand(this,selList,true));
    update();
}
void SamDrawScene::actionPaste()
{
    if(pwnd->isCompiled)
    {
        return;
    }
    QClipboard *cb = QApplication::clipboard();
    QByteArray CopyBuf = cb->mimeData()->data("Samkoon_Item");
    //QByteArray CopyBuf = mimeData->data("Samkoon_Item");
    QDataStream in(&CopyBuf,QIODevice::ReadOnly);
    int size;
    in>>size;
    //qDebug() << "copy size ======="<< size;
    QList <QGraphicsItem *> selList;
    for(int i = 0; i < size; i++)
    {
        int type = -1;
        in >> type;
        QGraphicsItem *item = loadItemFromStream(in,type);
		if (item)
		{
                    if(SAM_DRAW_OBJECT_GROUP == item->type())
                    {
                        QItemGroup *pItem = dynamic_cast<QItemGroup *> (item);
                        if(pItem)
                        {
                            pItem->redrawForChangeStatus(pItem->getCurrentState(),0);
                            pItem->changeItemLanguageAttr(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size());

                            if(SAM_DRAW_GROUP_VALUE == pItem->GroupType() || SAM_DRAW_GROUP_ASCII == pItem->GroupType())
                            {
                                DataDisplayItem *pDataItem = dynamic_cast<DataDisplayItem*> (item);
                                if(pDataItem)
                                {
                                    pDataItem->UpdateKeyboardInfo();
                                }
                            }

                        }
                    }
			selList << item;
		}
    }
        if (selList.size() != 0)
        {
                QGraphicsItem * pTem = NULL;
                DrawItemToScene CopyFun;
                pasteList.clear();
                parentItem_list.clear();

                foreach(QGraphicsItem * pItem,selList)
                {
                        CopyFun.CopyItem(&pTem,pItem);
                        parentItem_list.append(pItem);
                        emit key_paste(pTem,pItem);// 键盘Ctrl+V粘贴事件
                        pasteList.append(pTem);
                        pTem->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
                        pTem->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
                        pTem = NULL;
                }
                is_paste_singleItem = true;
        }
        pwnd->pDrawToSceneItem=NULL;


}//

/****************状态栏更新******************************/
void SamDrawScene::upDate_stutas()
{
    if(pwnd->isCompiled ||this->selectedItems().isEmpty())
    {
        //qDebug()<< "upDate_stutas -- isCompiled";
        return;
    }

    QList<QGraphicsItem*> items;
    QGraphicsItem *pItem;
    items = this->selectedItems();
    int nItemNum = items.size();

    //if(items.size()>1||items.size()==0)
    if(nItemNum <= 0)
    {
        pwnd->lab_control_statusBar->setEnabled(false);
        pwnd->lab_width_space_statusBar->setEnabled(false);
        pwnd->lab_hidth_space_statusBar->setEnabled(false);
        pwnd->lab_left_space_statusBar->setEnabled(false);
        pwnd->lab_up_space_statusBar->setEnabled(false);

        pwnd->lab_control_statusBar->setText("");
        pwnd->lab_width_space_statusBar->setText("");
        pwnd->lab_hidth_space_statusBar->setText("");
        pwnd->lab_left_space_statusBar->setText("");
        pwnd->lab_up_space_statusBar->setText("");

        return;
    }
    else if(nItemNum == 1)
    {
        pItem = this->selectedItems().first();

        pwnd->lab_control_statusBar->setEnabled(true);
        pwnd->lab_width_space_statusBar->setEnabled(true);
        pwnd->lab_hidth_space_statusBar->setEnabled(true);
        pwnd->lab_left_space_statusBar->setEnabled(true);
        pwnd->lab_up_space_statusBar->setEnabled(true);
    }
    else//items.size() > 1
    {
        pwnd->lab_control_statusBar->setEnabled(true);
        pwnd->lab_width_space_statusBar->setEnabled(true);
        pwnd->lab_hidth_space_statusBar->setEnabled(true);
        pwnd->lab_left_space_statusBar->setEnabled(true);
        pwnd->lab_up_space_statusBar->setEnabled(true);
    }

    if(nItemNum == 1)
    {
        switch (pItem->type())
        {
            case SAM_DRAW_OBJECT_RECT:
                pwnd->lab_control_statusBar->setText(tr("矩形"));
                break;
            case SAM_DRAW_OBJECT_ELIPSE:
                pwnd->lab_control_statusBar->setText(tr("椭圆"));
                break;
            case SAM_DRAW_OBJECT_POLYGON:
                pwnd->lab_control_statusBar->setText(tr("多边形"));
                break;
            case SAM_DRAW_OBJECT_LINE :
                pwnd->lab_control_statusBar->setText(tr("直线"));
                break;
            case SAM_DRAW_OBJECT_FOLDLINE:
                pwnd->lab_control_statusBar->setText(tr("折线"));
                break;
            case SAM_DRAW_OBJECT_LINECIRCLE:
                pwnd->lab_control_statusBar->setText(tr("曲线"));
                break;
            case SAM_DRAW_OBJECT_FREELINE:
                pwnd->lab_control_statusBar->setText(tr("自由直线"));
                break;
             case SAM_DRAW_OBJECT_ARC:
                pwnd->lab_control_statusBar->setText(tr("基本扇形"));
                break;
            case SAM_DRAW_OBJECT_ROUNDEDRECT:
                pwnd->lab_control_statusBar->setText(tr("圆角矩形"));
                break;
            case SAM_DRAW_OBJECT_TEXT :
                pwnd->lab_control_statusBar->setText(tr("静态文本"));
                break;
            case SAM_DRAW_OBJECT_GROUP:
                {
                    QItemGroup* item = dynamic_cast<QItemGroup*>(pItem);
                    if(item)
                    {
                        pwnd->lab_control_statusBar->setText(item->getItemName());
                    }
                }
                break;
////////////////wxy add start
        case SAM_DRAW_OBJECT_RECT_NEW:
            pwnd->lab_control_statusBar->setText(tr("矩形"));
            break;
        case SAM_DRAW_OBJECT_ELIPSE_NEW:
            pwnd->lab_control_statusBar->setText(tr("椭圆"));
            break;
        case SAM_DRAW_OBJECT_POLYGON_NEW:
            pwnd->lab_control_statusBar->setText(tr("多边形"));
            break;
        case SAM_DRAW_OBJECT_LINE_NEW:
            pwnd->lab_control_statusBar->setText(tr("直线"));
            break;
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:
            pwnd->lab_control_statusBar->setText(tr("折线"));
            break;
        case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
            pwnd->lab_control_statusBar->setText(tr("曲线"));
            break;
        case SAM_DRAW_OBJECT_FREELINE_NEW:
            pwnd->lab_control_statusBar->setText(tr("自由直线"));
            break;
         case SAM_DRAW_OBJECT_ARC_NEW:
            pwnd->lab_control_statusBar->setText(tr("基本扇形"));
            break;
        case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
            pwnd->lab_control_statusBar->setText(tr("圆角矩形"));
            break;
///////////////wxy add end
            default:
                break;
        }
    }
    else
    {
        pwnd->lab_control_statusBar->setText(tr("图形组"));
    }

    if(nItemNum == 1)
    {
        setStatus_LineValue(pItem);//设置状态栏编辑框的值
    }
    else
    {
        qreal leftMin   = 10000;
        qreal topMin    = 10000;
        qreal rightMax  = 0;
        qreal bottomMax = 0;
        QString str="";
        for(int i = 0; i < nItemNum; i++)
        {
            pItem = items.at(i);
            if(!pItem)
            {
                continue;
            }

            if(pItem->sceneBoundingRect().left() >= 0)
            {
                if(leftMin > pItem->sceneBoundingRect().left())
                {
                    leftMin = pItem->sceneBoundingRect().left();
                }
            }

            if(pItem->sceneBoundingRect().top() >= 0)
            {
                if(topMin > pItem->sceneBoundingRect().top())
                {
                    topMin = pItem->sceneBoundingRect().top();
                }
            }

            if(pItem->sceneBoundingRect().right() >= 0)
            {
                if(rightMax < pItem->sceneBoundingRect().right())
                {
                    rightMax = pItem->sceneBoundingRect().right();
                }
            }

            if(pItem->sceneBoundingRect().bottom() >= 0)
            {
                if(bottomMax < pItem->sceneBoundingRect().bottom())
                {
                    bottomMax = pItem->sceneBoundingRect().bottom();
                }
            }
        }

        str.setNum(leftMin,'f',1);
        pwnd->lab_left_space_statusBar->setText(str);

        str.setNum(topMin,'f',1);
        pwnd->lab_up_space_statusBar->setText(str);

        rightMax = rightMax - leftMin;
        str.setNum(rightMax,'f',1);
        pwnd->lab_width_space_statusBar->setText(str);

        bottomMax = bottomMax - topMin;
        str.setNum(bottomMax,'f',1);
        pwnd->lab_hidth_space_statusBar->setText(str);
    }
    //状态栏的更新
//    switch(nID)
//    {
//    case GROUP_TYPE_BITBTN : pwnd->lab_control_statusBar->setText(tr("位按钮")); break;
//    case GROUP_TYPE_WORDBTN : pwnd->lab_control_statusBar->setText(tr("字按钮")); break;
//    case GROUP_TYPE_SCREENBTN : pwnd->lab_control_statusBar->setText(tr("画面按钮")); break;
//    case GROUP_TYPE_FUNCTIONBTN : pwnd->lab_control_statusBar->setText(tr("功能按钮")); break;
//    case GROUP_TYPE_BITLAMP : pwnd->lab_control_statusBar->setText(tr("位指示灯")); break;
//    case GROUP_TYPE_WEEKBTN  : pwnd->lab_control_statusBar->setText(tr("星期按钮")); break;
//    case GROUP_TYPE_DYNCIRCLE  : pwnd->lab_control_statusBar->setText(tr("动态圆")); break;
//    case GROUP_TYPE_DYNRECT  : pwnd->lab_control_statusBar->setText(tr("动态矩形")); break;
//    case GROUP_TYPE_MFUNCTION  : pwnd->lab_control_statusBar->setText(tr("多功能按钮")); break;
//    case GROUP_TYPE_MULSTATELAMP : pwnd->lab_control_statusBar->setText(tr("多状态指示灯")); break;
//    case GROUP_TYPE_MULSTATEBTN  : pwnd->lab_control_statusBar->setText(tr("多态按钮")); break;
//    case GROUP_TYPE_PICTUREDISPLAY : pwnd->lab_control_statusBar->setText(tr("图片显示器")); break;
//    case GROUP_TYPE_PICTUREMOVE   : pwnd->lab_control_statusBar->setText(tr("图形移动")); break;
//    case GROUP_TYPE_NUMDISPLAY : pwnd->lab_control_statusBar->setText(tr("数值显示")); break;
//    case GROUP_TYPE_NUMENTRY : pwnd->lab_control_statusBar->setText(tr("数值输入")); break;
//    case GROUP_TYPE_ASCIIDISPLAY : pwnd->lab_control_statusBar->setText(tr("ASCII码显示")); break;
//    case GROUP_TYPE_ASCIIENTRY : pwnd->lab_control_statusBar->setText(tr("ASCII码输入")); break;
//    case GROUP_TYPE_BARGRAPH : pwnd->lab_control_statusBar->setText(tr("柱状图")); break;
//    case GROUP_TYPE_TIMEDISPLAY : pwnd->lab_control_statusBar->setText(tr("时间显示")); break;
//    case GROUP_TYPE_DATEDISPLAY : pwnd->lab_control_statusBar->setText(tr("日期显示")); break;
//    case GROUP_TYPE_ALARMCONTROL : pwnd->lab_control_statusBar->setText(tr("报警显示器")); break;
//    case GROUP_TYPE_DYNALARMBAR : pwnd->lab_control_statusBar->setText(tr("动态报警条")); break;
//    case GROUP_TYPE_HISALARM : pwnd->lab_control_statusBar->setText(tr("历史报警显示器")); break;
//    case GROUP_TYPE_METER : pwnd->lab_control_statusBar->setText(tr("仪表")); break;
//    case GROUP_TYPE_FLOWBLOCK : pwnd->lab_control_statusBar->setText(tr("流动条")); break;
//    case GROUP_TYPE_MSGDISPLAY : pwnd->lab_control_statusBar->setText(tr("消息显示")); break;
//    case GROUP_TYPE_STATICPIC : pwnd->lab_control_statusBar->setText(tr("静态图片")); break;
//    case GROUP_TYPE_GIFPIC : pwnd->lab_control_statusBar->setText(tr("GIF显示器")); break;
//    case GROUP_TYPE_PIE : pwnd->lab_control_statusBar->setText(tr("扇形图")); break;
//    case GROUP_TYPE_STEPING : pwnd->lab_control_statusBar->setText(tr("步进按钮")); break;
//    case GROUP_TYPE_TABLE : pwnd->lab_control_statusBar->setText(tr("表格")); break;
//    case GROUP_TYPE_SCALES : pwnd->lab_control_statusBar->setText(tr("刻度")); break;
//    case GROUP_TYPE_STATICTEXT : pwnd->lab_control_statusBar->setText(tr("静态文本")); break;
//    case GROUP_TYPE_TRENDCHART : pwnd->lab_control_statusBar->setText(tr("趋势图")); break;
//    case GROUP_TYPE_XYTRENDCHART : pwnd->lab_control_statusBar->setText(tr("XY趋势图")); break;
//    case GROUP_TYPE_HISTRENDCHART : pwnd->lab_control_statusBar->setText(tr("历史趋势图")); break;
//    case GROUP_TYPE_HISDATAALARM : pwnd->lab_control_statusBar->setText(tr("历史数据显示器")); break;
//    case GROUP_TYPE_SINGLESELECT : pwnd->lab_control_statusBar->setText(tr("单选按钮")); break;
//    case GROUP_TYPE_COMBOBOX : pwnd->lab_control_statusBar->setText(tr("下拉框按钮"));break;
//    case GROUP_TYPE_SLIDER : pwnd->lab_control_statusBar->setText(tr("滑块模拟量开")); break;

//    case GROUP_TYPE_ANIMATE:pwnd->lab_control_statusBar->setText(tr("动画")); break;
//    case GROUP_TYPE_MESSAGEBOARD:pwnd->lab_control_statusBar->setText(tr("留言板")); break;
//    case GROUP_TYPE_DATAGROUPDISPLAY:pwnd->lab_control_statusBar->setText(tr("数据群组")); break;
//    case GROUP_TYPE_ASCII_KEYBOARD:pwnd->lab_control_statusBar->setText(tr("键盘组件")); break;
//    case LIBRARY_LIB_GROUP:pwnd->lab_control_statusBar->setText(tr("图库")); break;
//    case GROUP_TYPE_RECIPE_CHOICE :  pwnd->lab_control_statusBar->setText(tr("配方选择器")); break;
//    case GROUP_TYPE_RECIPE_DISPLAY :pwnd->lab_control_statusBar->setText(tr("配方显示器")); break;
//    case USER_DEFINE_GROUP:pwnd->lab_control_statusBar->setText(tr("组合图形")); break;
//    case GROUP_TYPE_OPERATE_RECORD:pwnd->lab_control_statusBar->setText(tr("操作记录")); break;
//    default:   break;
//    }//
    //QString sZ = QString::number(pItem->zValue());
    //pwnd->lab_control_statusBar->setText(sZ);
    //setStatus_LineValue(pItem);//设置状态栏编辑框的值
}//

//场景的右键菜单
void SamDrawScene::SamDrawScene_rightMenu(QGraphicsSceneMouseEvent *mouseEvent)
{
    //QMenu *menu_map_storage=new QMenu(tr("图库"));//图库
//    menu_map_storage->addAction(pwnd->ui->action_open_mapstorage);
 //   menu_map_storage->addAction(pwnd->ui->action_create_map_storage);

    QMenu *menu_imitate=new QMenu(tr("模拟状态"));//模拟状态
    menu_imitate->addAction(pwnd->ui->action_stateon);
    menu_imitate->addAction(pwnd->ui->action_state0);

    QMenu *menu = new QMenu(pwnd);
    QAction *property=menu->addAction(tr("属性"));
    if(this->selectedItems().isEmpty())
    {

        if(nIsSceneOrWindow ==0)
        {
            connect(property,SIGNAL(triggered()),pwnd,SLOT(newscreen_property()));
        }
        else if(nIsSceneOrWindow ==1)
        {
            connect(property,SIGNAL(triggered()),pwnd,SLOT(newswindow_property()));//窗口属性
        }
        else if(nIsSceneOrWindow ==2)
        {
            connect(property,SIGNAL(triggered()),pwnd,SLOT(tree_UserKeyboardproperty()));//窗口属性
        }
    }
    else
    {
        connect(property,SIGNAL(triggered()),this,SLOT(Thing_property()));//窗口属性
    }
    menu->addSeparator();
    QAction *thing=menu->addMenu(pwnd->ui->menu_thing);
    thing->setText(tr("插入"));
    //menu.addSeparator();
    //menu.addMenu(menu_map_storage);//图库菜单
    menu->addSeparator();
    menu->addAction(pwnd->ui->action_cut);//剪切
    menu->addAction(pwnd->ui->action_copy);//复制
    menu->addAction(pwnd->ui->action_copym);//多重复制
    if(this->selectedItems().size()==1)
    {
        pwnd->ui->action_copym->setDisabled(false);
    }
    else
    {
        pwnd->ui->action_copym->setDisabled(true);
    }
    menu->addAction(pwnd->ui->action_paste);//粘贴
    menu->addAction(pwnd->ui->action_delete);//删除
    menu->addSeparator();
    menu->addAction(pwnd->ui->action_checkall);//全选
    menu->addSeparator();
    menu->addMenu(pwnd->ui->menu_subalign);//对齐
    menu->addMenu(pwnd->ui->menu_sublayout);//层次
    //menu.addMenu(pwnd->ui->menu_subxuanjuan);//旋转
    menu->addSeparator();
    menu->addMenu(pwnd->ui->menu_subgroup);//组合
    menu->addSeparator();
    menu->addMenu(pwnd->ui->menu_subpictureratio);//图像比例
    menu->addSeparator();
    menu->addAction(pwnd->ui->action_grid);//网格
    menu->addSeparator();
    menu->addMenu(menu_imitate);//模拟状态
    menu->addSeparator();
    //menu.addMenu(pwnd->ui->menu_P);//画面
    menu->exec(QCursor::pos());
}//

//当点击场景的右键菜单属性时候点击在Item上的响应函数
void SamDrawScene::Thing_property()
{
    QGraphicsItem *pItem;
    if(this->selectedItems().size()==1)
    {
       pItem=this->selectedItems().first();
       pwnd->SlotItemDBClick(pItem);
    }
}//

void SamDrawScene::setNewItem_ID(QGraphicsItem * pTem,QGraphicsItem * pItem)
{
    //alter by zqh
    QStringList sList;
    QString str="";
    QString sTmp="";
    sList=pTem->data(GROUP_DATALIST_KEY).toStringList();
    if(sList.size() < 20)//if(sList.isEmpty())
    {
        return;
    }
    str = sList.at(19); //取编号
    if(str != "")
    {
        str = str.left(str.length()-4);//除掉编号后四位数字
        sTmp= pwnd->ControlNO(str); //获得新编号

        sList.replace(19,sTmp);
        pTem->setData(GROUP_DATALIST_KEY,sList);
    }
}

void SamDrawScene::Onkey_paste(QGraphicsItem * pTem,QGraphicsItem * pItem)// 键盘Ctrl+V粘贴事件
{
    DrawItemToScene FunClass;
    FunClass.CopyItem(&(pwnd->pDrawToSceneItem),pTem);
    SamDrawTool::s_eDrawActType = SAM_DRAW_ASSY_COMPONENT;

 }//

/*******************************************************
 *函数名称：SetBaseItemMirror(int nType)
 *函数功能：设置基本图形镜像
 *参数含义：nType=1表示水平镜像，nType=2表示垂直镜像
 *edit by zqh
 *2011-03-04
 ******************************************************/
void SamDrawScene::SetBaseItemMirror(int nType)
{
    QList<QGraphicsItem *> items;
    QGraphicsItem *pItem = NULL;

    items = this->selectedItems();
    if(items.size() != 1 )
        return;

    pItem = items.at(0); //取出要镜像的基本图形

    QLineItem *pLine = NULL;
    QFoldLineItem *pFoldLine = NULL;
    QFreeLineItem *pFreeLine = NULL;
    QPolygonItem *pPolyRect = NULL;
    QLineCircleItem *pCirlceLine = NULL;

    QPainterPath path ;
    QPolygonF pointList ;
    int nCount = 0;
    QPointF point;
    int i = 0;
    QRectF rc = pItem->sceneBoundingRect();

    QVector <QPointF>vPoint;
    QList<QPolygonF> CircleLinePonit;
    QList<QPolygonF> NewLinePonit;

    QPointF hPos;
    QPointF vPos;
    qreal qVal = 0;

    switch(pItem->type())
    {
    case SAM_DRAW_OBJECT_LINE_NEW://直线 m_eLineEndArrowType
        pLine = qgraphicsitem_cast<QLineBasicItem*>(pItem);
        if(pLine->getEndArrow() != LINE_END_STYLE_NONE)
            return;
        path = pLine->path();
        pointList = path.toFillPolygon();
        break;
    case SAM_DRAW_OBJECT_FOLDLINE_NEW://折线
        pFoldLine = qgraphicsitem_cast<QFoldLineBasicItem*>(pItem);
        if(pFoldLine->getEndArrow() != LINE_END_STYLE_NONE)
            return;
        path = pFoldLine->path();
        pointList = path.toFillPolygon();
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW://曲线、圆弧
        pCirlceLine= qgraphicsitem_cast<QLineCircleBasicItem *>(pItem);
        if(pCirlceLine->getEndArrow() != LINE_END_STYLE_NONE)
            return;
        path = pCirlceLine->path();
        CircleLinePonit = path.toSubpathPolygons();
        break;
    case SAM_DRAW_OBJECT_FREELINE_NEW://自由直线
        pFreeLine = qgraphicsitem_cast<QFreeLineBasicItem*>(pItem);
        if(pFreeLine->getEndArrow() != LINE_END_STYLE_NONE)
            return;
        path = pFreeLine->path();
        pointList = path.toFillPolygon();
        break;
    case SAM_DRAW_OBJECT_RECT_NEW://矩形
    case SAM_DRAW_OBJECT_ELIPSE_NEW://椭圆
    case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW: //圆角矩形
        return; //矩形和椭圆镜像后和原图一样，所以不用处理其镜像
    case SAM_DRAW_OBJECT_POLYGON_NEW://多边形
        pPolyRect = qgraphicsitem_cast<QPolygonBasicItem*>(pItem);
        pointList = pPolyRect->polygon();
         break;
    default:
        break;
    }

    nCount = pointList.size();
    if(pItem->type() != SAM_DRAW_OBJECT_POLYGON_NEW)
        nCount--;

    hPos.setX(rc.left()+rc.width()/2); //求水平镜像时中点位置
    hPos.setY(rc.top());
    hPos = pItem->mapFromScene(hPos);

    vPos.setX(rc.left());
    vPos.setY(rc.top()+rc.height()/2); //求垂直镜像时中点位置
    vPos = pItem->mapFromScene(vPos);

    if(nType == 1) //水平镜像
    {
        if(pItem->type() != SAM_DRAW_OBJECT_LINECIRCLE_NEW)
        {
            for(i = 0;i < nCount;i++)
            {
                point = pointList.at(i);
                qVal = hPos.x()-point.x();
                point.setX(hPos.x()+qVal);
                vPoint.append(point);
            }
        }
        else//对曲线、圆弧进行特殊处理
        {
            for(i = 0;i < CircleLinePonit.size();i++)
            {
                pointList = CircleLinePonit.at(i);
                QPolygonF subList;
                for(int j = 0;j < pointList.size();j++)
                {
                    point = pointList.at(j);
                    qVal = hPos.x()-point.x();
                    point.setX(hPos.x()+qVal);
                    subList.append(point);
                }
                NewLinePonit.append(subList);
            }
        }
    }
    else if(nType == 2)//垂直镜像
    {
        if(pItem->type() != SAM_DRAW_OBJECT_LINECIRCLE_NEW)
        {
            for(i = 0;i < nCount;i++)
            {
                point = pointList.at(i);
                qVal = vPos.y()-point.y();
                point.setY(vPos.y()+qVal);
                vPoint.append(point);
            }
        }
        else//对曲线、圆弧进行特殊处理
        {
            for(i = 0;i < CircleLinePonit.size();i++)
            {
                pointList = CircleLinePonit.at(i);
                QPolygonF subList;
                for(int j = 0;j < pointList.size();j++)
                {
                    point = pointList.at(j);
                    qVal = vPos.y()-point.y();
                    point.setY(vPos.y()+qVal);
                    subList.append(point);
                }
                NewLinePonit.append(subList);
            }
        }
    }

    if(pItem->type() != SAM_DRAW_OBJECT_POLYGON_NEW &&
       pItem->type() != SAM_DRAW_OBJECT_LINECIRCLE_NEW)
    {
        for(i = 0; i < vPoint.size();i++)
        {
            point = vPoint.at(i);
            path.setElementPositionAt(i, point.x(), point.y());
        }
    }
    if(pItem->type() == SAM_DRAW_OBJECT_LINECIRCLE_NEW)//对曲线、圆弧进行特殊处理
    {
        QPainterPath allPath;
        for(int i=0;i<NewLinePonit.size();i++)
        {
                QPainterPath subPath = QPainterPath();
                subPath.addPolygon(NewLinePonit.at(i));
                allPath.addPath(subPath);
        }
        path = allPath;
    }

    switch(pItem->type())
    {
    case SAM_DRAW_OBJECT_LINE_NEW://直线
        pLine->setPath(path);
        break;
    case SAM_DRAW_OBJECT_FOLDLINE_NEW://折线
        pFoldLine->setPath(path);
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW://曲线、圆弧
        pCirlceLine->setPath(path);
        break;
    case SAM_DRAW_OBJECT_FREELINE_NEW://自由直线
        pFreeLine->setPath(path);
        break;
    case SAM_DRAW_OBJECT_POLYGON_NEW://多边形
        {
            QPolygonF mPoly(vPoint);
            pPolyRect->setPolygon(mPoly);
        }
         break;
    default:
        break;
    }
    this->reBondingTrackers();
}
//从文件载入外形
QList <QGraphicsItem *> SamDrawScene::loadItems(QDataStream &stream)
{
	int sceneItemsize = 0;
	stream >> sceneItemsize;
	QList <QGraphicsItem *>list;
	while(sceneItemsize > 0 && !stream.atEnd())
	{
		sceneItemsize-- ;
		int type = -1;
		stream >> type;
		switch(type)
		{
		case SAM_DRAW_OBJECT_GROUP:                //23
			{
				QItemGroup *groupItem = new QItemGroup();
                                groupItem->load(stream);
				groupItem->setFlag(QGraphicsItem::ItemIsMovable, true);
				groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
				list.append(groupItem);
				break;
			}
		default:
			break;
		}
	}
	return list;
}

void SamDrawScene::setStatus_LineValue(QGraphicsItem * pItem)//设置状态栏编辑框的值
{
    if(!this->isActive()){
        //qDebug() << "scene is not active!";
        return ;
    }
    QString sw="";
    QString sh="";
    if(pItem->sceneBoundingRect().left()<0)
    {
        pwnd->lab_left_space_statusBar->setText("0.0");
    }
    else
    {
        sw.setNum(pItem->sceneBoundingRect().left(),'f',1);
        pwnd->lab_left_space_statusBar->setText(sw);
    }

    if(pItem->sceneBoundingRect().top()<0)
    {
        pwnd->lab_up_space_statusBar->setText("0.0");
    }
    else
    {
       sh.setNum(pItem->sceneBoundingRect().top(),'f',1);
       pwnd->lab_up_space_statusBar->setText(sh);
    }

    if(pItem->type()== SAM_DRAW_OBJECT_RECT)
    {
        QRectItem *pRect = dynamic_cast<QRectItem *> (pItem);
        sw.setNum(pRect->GetWidth(),'f',1);
        sh.setNum(pRect->GetHeight(),'f',1);
    }
    else if(pItem->type()== SAM_DRAW_OBJECT_ROUNDEDRECT)
    {
        QRoundedRect *pRoundedRect = dynamic_cast<QRoundedRect *> (pItem);
        sw.setNum(pRoundedRect->GetWidth(),'f',1);
        sh.setNum(pRoundedRect->GetHeight(),'f',1);
    }
    else if(pItem->type()== SAM_DRAW_OBJECT_ELIPSE)
    {
        QElipseItem *pElipse = dynamic_cast<QElipseItem *> (pItem);
        sw.setNum(pElipse->GetWidth(),'f',1);
        sh.setNum(pElipse->GetHeight(),'f',1);

    }
    else if(pItem->type()== SAM_DRAW_OBJECT_TEXT)
    {
        sw.setNum(pItem->sceneBoundingRect().width(),'f',1);
        sh.setNum(pItem->sceneBoundingRect().height(),'f',1);
    }
    else if(pItem->type()==SAM_DRAW_OBJECT_ARC)
    {
        QArcItem * pArc = dynamic_cast<QArcItem *> (pItem);
        sw.setNum(pArc->GetWidth(),'f',1);
        sh.setNum(pArc->GetHeight(),'f',1);
        pwnd->lab_width_space_statusBar->setText(sw);
        pwnd->lab_hidth_space_statusBar->setText(sh);

        sw.setNum(pItem->sceneBoundingRect().x(),'f',1);
        pwnd->lab_left_space_statusBar->setText(sw);
        sh.setNum(pItem->sceneBoundingRect().y(),'f',1);
        pwnd->lab_up_space_statusBar->setText(sh);

        pwnd->lab_width_space_statusBar->setCursorPosition(0);
        pwnd->lab_hidth_space_statusBar->setCursorPosition(0);
        pwnd->lab_left_space_statusBar->setCursorPosition(0);
        pwnd->lab_up_space_statusBar->setCursorPosition(0);
        return;
    }
///////////////wxy add start
    else if(pItem->type()== SAM_DRAW_OBJECT_RECT_NEW)
    {
        QRectBasicItem *pRect = dynamic_cast<QRectBasicItem *> (pItem);
        sw.setNum(pItem->sceneBoundingRect().width(),'f',1);
        sh.setNum(pItem->sceneBoundingRect().height(),'f',1);
    }
    else if(pItem->type()== SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)
    {
        QRoundedRectBasic *pRoundedRect = dynamic_cast<QRoundedRectBasic *> (pItem);
        sw.setNum(pItem->sceneBoundingRect().width(),'f',1);
        sh.setNum(pItem->sceneBoundingRect().height(),'f',1);
    }
    else if(pItem->type()== SAM_DRAW_OBJECT_ELIPSE_NEW)
    {
        QElipseBasicItem *pElipse = dynamic_cast<QElipseBasicItem *> (pItem);
        sw.setNum(pElipse->GetWidth(),'f',1);
        sh.setNum(pElipse->GetHeight(),'f',1);

    }
    else if(pItem->type()==SAM_DRAW_OBJECT_ARC_NEW)
    {
        QArcBasicItem * pArc = dynamic_cast<QArcBasicItem *> (pItem);
        sw.setNum(pArc->GetWidth(),'f',1);
        sh.setNum(pArc->GetHeight(),'f',1);
        pwnd->lab_width_space_statusBar->setText(sw);
        pwnd->lab_hidth_space_statusBar->setText(sh);

        sw.setNum(pItem->sceneBoundingRect().x(),'f',1);
        pwnd->lab_left_space_statusBar->setText(sw);
        sh.setNum(pItem->sceneBoundingRect().y(),'f',1);
        pwnd->lab_up_space_statusBar->setText(sh);

        pwnd->lab_width_space_statusBar->setCursorPosition(0);
        pwnd->lab_hidth_space_statusBar->setCursorPosition(0);
        pwnd->lab_left_space_statusBar->setCursorPosition(0);
        pwnd->lab_up_space_statusBar->setCursorPosition(0);
        return;
    }
///////////////wxy add end
    else
    {
        sw.setNum(pItem->sceneBoundingRect().width(),'f',1);
        sh.setNum(pItem->sceneBoundingRect().height(),'f',1);
    }
    pwnd->lab_width_space_statusBar->setText(sw);
    pwnd->lab_hidth_space_statusBar->setText(sh);


}

QList <QGraphicsItem *> SamDrawScene::TopItems()
{
    QList <QGraphicsItem *> list;
    foreach(QGraphicsItem *pItem,items())
    {
        if(pItem->parentItem() == 0 && pItem->type() != SAM_DRAW_OBJECT_TRACKER
           && pItem->type() != SAM_DRAW_OBJECT_LOCK)
        {
            list.append(pItem);
        }
    }
    return list;
}
bool SamDrawScene::compile(QSqlDatabase &db, int nSceneId, int &count)
{

    switch(nIsSceneOrWindow)
    {
    case 0:
        pwnd->information(tr("开始编译画面：%1").arg(sNewScreenName), MSG_NORMAL);
        compileScreen(count, db, nSceneId);
        pwnd->information(tr("结束编译画面：%1").arg(sNewScreenName), MSG_NORMAL);
        break;
    case 1:
        pwnd->information(tr("开始编译窗口：%1").arg(sNewScreenName), MSG_NORMAL);
        compileWindow(count, db, nSceneId);
        pwnd->information(tr("结束编译窗口：%1").arg(sNewScreenName), MSG_NORMAL);
        break;
    case 2:
        pwnd->information(tr("开始编译自定义键盘：%1").arg(sNewScreenName), MSG_NORMAL);
        compileKeyboard(db,nSceneId);
        pwnd->information(tr("结束编译自定义键盘：%1").arg(sNewScreenName), MSG_NORMAL);
        break;
    default:
        break;
    }

    int index = 0;
    QList <QGraphicsItem *> items = TopItems();
    while(!items.isEmpty())
    {
        QList <QGraphicsItem *> colliditems;
        QGraphicsItem *firstitem = items.first();

        //items.removeFirst();
        if(firstitem)
        {
            addCollidItems(firstitem,colliditems);
            foreach(QGraphicsItem* pItem,colliditems)
            {
                //在这里添加编译单个item的代码
                items.removeOne(pItem);
                compileItem(pItem,db,nSceneId,count,index);
            }
        }
        index++;
    }
	return true;
}

//取所有跟pItem有相互碰撞关系的item
QList<QGraphicsItem*> SamDrawScene::SDCollidItems(QGraphicsItem *pItem)
{
    QList<QGraphicsItem*> colItems;
    QList<QGraphicsItem*> allItems = TopItems();
    foreach(QGraphicsItem *item,allItems)
    {
        if (item->collidesWithItem(pItem,Qt::IntersectsItemBoundingRect)
                || pItem->collidesWithItem(item,Qt::IntersectsItemBoundingRect))
        {
            colItems << item;
        }
    }
    return colItems;
}

//编译画面属性
void SamDrawScene::compileScreen(int &count, QSqlDatabase &db, int nSceneId)
{
    QSqlQuery sqlquery(db);

    sqlquery.prepare("INSERT INTO scene(nSceneId,sScreenName,bLogout ,sNumber,nSceneWidth,nSceneHeight,"
                     "eBackType,nBackColor,nForeColor,eDrawStyle,sPicturePath,"
                     "bIsAddMenu,bSlide,nTowardLeftId,nTowardRIghtId,nSlideStyle)"
                     "VALUES(:nSceneId,:sScreenName,:bLogout,:sNumber,:nSceneWidth,:nSceneHeight,"
                     ":eBackType,:nBackColor,:nForeColor,:eDrawStyle,:sPicturePath,"
                     ":bIsAddMenu,:bSlide,:nTowardLeftId,:nTowardRIghtId,:nSlideStyle)");

    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));
    sqlquery.bindValue(":sScreenName",QVariant(sNewScreenName));
    sqlquery.bindValue(":bLogout",QVariant(bLogout));
    sqlquery.bindValue(":sNumber",QVariant(sNumberName.toInt()));
    sqlquery.bindValue(":nSceneWidth",QVariant(sceneRect().width()));
    sqlquery.bindValue(":nSceneHeight",QVariant(sceneRect().height()));
    sqlquery.bindValue(":eBackType",QVariant(nSelectType + 1));
    sqlquery.bindValue(":nBackColor",QVariant(ColorToInt(m_sceneBackColor)));
    sqlquery.bindValue(":nForeColor",QVariant(ColorToInt(m_sceneStyleColor)));
    sqlquery.bindValue(":eDrawStyle",QVariant(nPattern + 2));
    QString newPath = pwnd->SavePath(m_picturePath, QSizeF(sceneRect().width(), sceneRect().height()), false);
    if("" != newPath)
    {
        newPath = newPath.replace("\\","/");
        newPath = newPath.section("/",-1);
        newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
    }
    sqlquery.bindValue(":sPicturePath",QVariant(newPath));
    sqlquery.bindValue(":bIsAddMenu",QVariant(bIsAddMenu));
    sqlquery.bindValue(":bSlide",QVariant(bSlide));
    sqlquery.bindValue(":nTowardLeftId",QVariant(nTowardLeftId));
    sqlquery.bindValue(":nTowardRIghtId",QVariant(nTowardRIghtId));
    sqlquery.bindValue(":nSlideStyle",QVariant(nSlideStyle + 1));

    bool result = false;
    result = sqlquery.exec();
    qDebug() << "insert scene table :" << result;

    sqlquery.prepare("INSERT INTO macro(MacroID,MacroLibName,MacroName,MacroType,TimeInterval,"
                     "ControlAddr,ControlAddrType,ExecCondition,nCmpFactor,nCompID,SceneID,scriptCount)"
              "VALUES(:MacroID,:MacroLibName,:MacroName,:MacroType,:TimeInterval,"
              ":ControlAddr,:ControlAddrType,:ExecCondition,:nCmpFactor,:nCompID,:SceneID,:scriptCount)");
    int scriptCount = listScript.size();
    int oldValue = count;
    int k = 1;
    for(int i = 0; i < scriptCount; i++)
    {
        count++;
        SCRIPT_PROP script = listScript.at(i);

        sqlquery.bindValue(":MacroID",QVariant(count));
        sqlquery.bindValue(":MacroLibName",QVariant(script.scriptName));
        sqlquery.bindValue(":MacroName",QVariant("MACRO_MAIN"));
        //sqlquery.bindValue(":MacroType",QVariant(script.scriptType));
        if(script.scriptBShow)
        {
            sqlquery.bindValue(":MacroType",QVariant(4));
        }
        else
        {
            sqlquery.bindValue(":MacroType",QVariant(3));
        }
        sqlquery.bindValue(":TimeInterval",QVariant(script.scriptFreq * 100));
        sqlquery.bindValue(":ControlAddrType",QVariant(0));//位地址
        if(script.scriptBShow)
        {
            sqlquery.bindValue(":ControlAddr",QVariant(oldValue + scriptCount + k));
            k++;
            sqlquery.bindValue(":ExecCondition",QVariant(script.scriptCondition));
        }
        else
        {
            sqlquery.bindValue(":ControlAddr",QVariant(-1));
            sqlquery.bindValue(":ExecCondition",QVariant(-1));
        }

        sqlquery.bindValue(":nCmpFactor",QVariant(0));
        sqlquery.bindValue(":nCompID",QVariant(oldValue));
        sqlquery.bindValue(":SceneID",QVariant(nSceneId));
        sqlquery.bindValue(":scriptCount",QVariant(script.scriptCount));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "----------->>>>>>>>>" << result;
    }

    for(int i = 0; i < scriptCount; i++)
    {
        SCRIPT_PROP script = listScript.at(i);
        if(script.scriptBShow)
        {
            count++;
            ADDR_PARAMENTS stParams;
            stParams.id         = count;
            stParams.itemId     = count;
            stParams.eType      = OBJ_MACRO;
            stParams.eRWtype    = SCENE_CONTROL_LOOP_R;
            stParams.addrNum    = -1;
            script.scriptAddr.compile(db, stParams);
        }
    }
}

//编译窗口属性
void SamDrawScene::compileWindow(int &count, QSqlDatabase &db, int nSceneId)
{
    QSqlQuery sqlquery(db);
    bool XX = sqlquery.prepare("INSERT INTO windown(nSceneId,sScreenName,bLogout,sNumber,nShowPosX,nShowPosY,nWindownWidth,"
                     "nWindownHeight,bShowTitle,bShowShutBtn,sTileName,nBackColor,bShowMiddle,"
                     "eBackType,nForeColor,sPicturePath,eDrawStyle)"
                     "VALUES(:nSceneId,:sScreenName,:bLogout,:sNumber,:nShowPosX,:nShowPosY,:nWindownWidth,"
                     ":nWindownHeight,:bShowTitle,:bShowShutBtn,:sTileName,:nBackColor,:bShowMiddle,"
                     ":eBackType,:nForeColor,:sPicturePath,:eDrawStyle)");
    qDebug() << "+++++++++++++++++++XX-------------" << XX;

    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));
    sqlquery.bindValue(":sScreenName",QVariant(sNewScreenName));
    sqlquery.bindValue(":bLogout",QVariant(bLogout));
    sqlquery.bindValue(":sNumber",QVariant(sNumberName.toInt()));
    if(bShowMiddle)
    {
        sqlquery.bindValue(":nShowPosX",QVariant(0));
        sqlquery.bindValue(":nShowPosY",QVariant(0));
    }
    else
    {
        sqlquery.bindValue(":nShowPosX",QVariant(mWindownShowPos.x()));
        sqlquery.bindValue(":nShowPosY",QVariant(mWindownShowPos.y()));
    }
    sqlquery.bindValue(":nWindownWidth",QVariant(sceneRect().width()));
    sqlquery.bindValue(":nWindownHeight",QVariant(sceneRect().height()));
    sqlquery.bindValue(":bShowTitle",QVariant(bshowTitle));
    sqlquery.bindValue(":bShowShutBtn",QVariant(true));
    sqlquery.bindValue(":sTileName",QVariant(tr("")));
    sqlquery.bindValue(":nBackColor",QVariant(ColorToInt(m_sceneBackColor)));
    sqlquery.bindValue(":bShowMiddle",QVariant(bShowMiddle));
    sqlquery.bindValue(":eBackType",QVariant(nSelectType + 1));
    sqlquery.bindValue(":nForeColor",QVariant(ColorToInt(m_sceneStyleColor)));
    sqlquery.bindValue(":eDrawStyle",QVariant(nPattern + 2));
    QString newPath = pwnd->SavePath(m_picturePath, QSizeF(sceneRect().width(), sceneRect().height()), false);
    if("" != newPath)
    {
        newPath = newPath.replace("\\","/");
        newPath = newPath.section("/",-1);
        newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
    }
    sqlquery.bindValue(":sPicturePath",QVariant(newPath));

    bool result = false;
    result = sqlquery.exec();
    qDebug() << "insert windown table :"<<result;

    bool bShit = sqlquery.prepare("INSERT INTO macro(MacroID,MacroLibName,MacroName,MacroType,TimeInterval,"
                     "ControlAddr,ControlAddrType,ExecCondition,nCmpFactor,nCompID,SceneID,scriptCount)"
              "VALUES(:MacroID,:MacroLibName,:MacroName,:MacroType,:TimeInterval,"
                     ":ControlAddr,:ControlAddrType,:ExecCondition,:nCmpFactor,:nCompID,:SceneID,:scriptCount)");
    //qDebug() << "+++++++++++++++++++bShit-------------" << bShit;
    int scriptCount = listScript.size();
    int oldValue = count;
    int k = 1;
    for(int i = 0; i < scriptCount; i++)
    {
        count++;
        SCRIPT_PROP script = listScript.at(i);

        sqlquery.bindValue(":MacroID",QVariant(count));
        sqlquery.bindValue(":MacroLibName",QVariant(script.scriptName));
        sqlquery.bindValue(":MacroName",QVariant("MACRO_MAIN"));
        //sqlquery.bindValue(":MacroType",QVariant(script.scriptType));
        if(script.scriptBShow)
        {
            sqlquery.bindValue(":MacroType",QVariant(4));
        }
        else
        {
            sqlquery.bindValue(":MacroType",QVariant(3));
        }
        sqlquery.bindValue(":TimeInterval",QVariant(script.scriptFreq * 100));
        sqlquery.bindValue(":ControlAddrType",QVariant(0));//位地址
        if(script.scriptBShow)
        {
            sqlquery.bindValue(":ControlAddr",QVariant(oldValue + scriptCount + k));
            k++;
            sqlquery.bindValue(":ExecCondition",QVariant(script.scriptCondition));
        }
        else
        {
            sqlquery.bindValue(":ControlAddr",QVariant(-1));
            sqlquery.bindValue(":ExecCondition",QVariant(-1));
        }

        sqlquery.bindValue(":nCmpFactor",QVariant(0));
        sqlquery.bindValue(":nCompID",QVariant(oldValue));
        sqlquery.bindValue(":SceneID",QVariant(nSceneId));
        sqlquery.bindValue(":scriptCount",QVariant(script.scriptCount));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "----------->>>>>>>>>" << result;
    }

    for(int i = 0; i < scriptCount; i++)
    {
        SCRIPT_PROP script = listScript.at(i);
        if(script.scriptBShow)
        {
            count++;
            ADDR_PARAMENTS stParams;
            stParams.id         = count;
            stParams.itemId     = count;
            stParams.eType      = OBJ_MACRO;
            stParams.eRWtype    = SCENE_CONTROL_LOOP_R;
            stParams.addrNum    = -1;
            script.scriptAddr.compile(db, stParams);
        }
    }
}

//编译自定义键盘属性
void SamDrawScene::compileKeyboard(QSqlDatabase &db, int nSceneId)
{
    QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO keyBoard (nSceneId,skeyName,nkeyWidth,nkeyHeight,ekeyStyle,"
                     "nkeyBackColor,nkeyForeColor,eBackType,sPicturePath,nMaxStartX,"
                     "nMaxStartY,nMaxWidth,nMaxHeight,nMaxFont,nMaxAlign,nMaxFontSize,"
                     "nMaxFontPro,nMaxFontColor,nMaxStyle,nMaxAlpha,nMaxForeColor,"
                     "nMaxBackColor,nMaxAdapt,nMinStartX,nMinStartY,nMinWidth,"
                     "nMinHeight,nMinFont,nMinAlign,nMinFontSize,nMinFontPro,nMinFontColor,"
                     "nMinStyle,nMinAlpha,nMinForeColor,nMinBackColor,nMinAdapt,nTextStartX,"
                     "nTextStartY,nTextWidth,nTextHeight,nTextFont,nTextAlign,nTextFontSize,"
                     "nTextFontPro,nTextFontColor,nTextStyle,nTextAlpha,nTextForeColor,"
                     "nTextBackColor,nTextAdapt)"
                     "VALUES (:nSceneId,:skeyName,:nkeyWidth,:nkeyHeight,:ekeyStyle,"
                     ":nkeyBackColor,:nkeyForeColor,:eBackType,:sPicturePath,:nMaxStartX,"
                     ":nMaxStartY,:nMaxWidth,:nMaxHeight,:nMaxFont,:nMaxAlign,:nMaxFontSize,"
                     ":nMaxFontPro,:nMaxFontColor,:nMaxStyle,:nMaxAlpha,:nMaxForeColor,"
                     ":nMaxBackColor,:nMaxAdapt,:nMinStartX,:nMinStartY,:nMinWidth,"
                     ":nMinHeight,:nMinFont,:nMinAlign,:nMinFontSize,:nMinFontPro,:nMinFontColor,"
                     ":nMinStyle,:nMinAlpha,:nMinForeColor,:nMinBackColor,:nMinAdapt,:nTextStartX,"
                     ":nTextStartY,:nTextWidth,:nTextHeight,:nTextFont,:nTextAlign,:nTextFontSize,"
                     ":nTextFontPro,:nTextFontColor,:nTextStyle,:nTextAlpha,:nTextForeColor,"
                     ":nTextBackColor,:nTextAdapt)");

    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));
    sqlquery.bindValue(":skeyName",QVariant(sNewScreenName));
    sqlquery.bindValue(":nkeyWidth",QVariant(sceneRect().width()));
    sqlquery.bindValue(":nkeyHeight",QVariant(sceneRect().height()));
    sqlquery.bindValue(":ekeyStyle",QVariant(nPattern+1));
    sqlquery.bindValue(":nkeyBackColor",QVariant(ColorToInt(m_sceneBackColor)));
    sqlquery.bindValue(":nkeyForeColor",QVariant(ColorToInt(m_sceneStyleColor)));
    sqlquery.bindValue(":eBackType",QVariant(nSelectType));
    //sqlquery.bindValue(":eDrawStyle",QVariant(nPattern+1));
    QString newPath = "";
    if("" != m_picturePath)
    {
        QSizeF size(sceneRect().width(),sceneRect().height());
        newPath = pwnd->SavePath(m_picturePath,size,false);
        newPath = newPath.replace("\\","/");
        newPath = newPath.section("/",-1);
        newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
    }
    sqlquery.bindValue(":sPicturePath",QVariant(newPath));
    QRectF rectmax;
    QRectF rectmin;
    QRectF recttxt;
    StaticTextItem *pMaxTextItem = NULL;
    StaticTextItem *pMinTextItem = NULL;
    StaticTextItem *pInpTextItem = NULL;
    foreach(QGraphicsItem* pItem,TopItems())
    {
        if(SAM_DRAW_OBJECT_GROUP == pItem->type())
        {
            QItemGroup *itemgoup = dynamic_cast<QItemGroup *> (pItem);
            if(SAM_DRAW_GROUP_STATICTEXT == itemgoup->GroupType())
            {
                StaticTextItem *item = dynamic_cast<StaticTextItem *> (itemgoup);
                if("MIN" == item->data(GROUP_NAME_KEY).toString())
                {
                    rectmin = item->sceneBoundingRect();
                    pMinTextItem = item;
                }
                else if("MAX" == item->data(GROUP_NAME_KEY).toString())
                {
                    rectmax = item->sceneBoundingRect();
                    pMaxTextItem = item;
                }
                else if("TEXT" == item->data(GROUP_NAME_KEY).toString())
                {
                    recttxt = item->sceneBoundingRect();
                    pInpTextItem = item;
                }
            }
        }

    }

    sqlquery.bindValue(":nMaxStartX",QVariant(rectmax.x()));
    sqlquery.bindValue(":nMaxStartY",QVariant(rectmax.y()));
    sqlquery.bindValue(":nMaxWidth",QVariant(rectmax.width()));
    sqlquery.bindValue(":nMaxHeight",QVariant(rectmax.height()));

    QColor mColor;
    int align;
    if(pMaxTextItem)
    {
        sqlquery.bindValue(":nMaxFont",QVariant(pMaxTextItem->m_text.sFontFamly));
        if(pMaxTextItem->m_text.eTextAlign==0){
            align=2;
        }else if(pMaxTextItem->m_text.eTextAlign==1){
            align=1;
        }else if(pMaxTextItem->m_text.eTextAlign==2){
            align=3;
        }
        sqlquery.bindValue(":nMaxAlign",QVariant(align));
        sqlquery.bindValue(":nMaxFontSize",QVariant(pMaxTextItem->m_text.sFontSize));
        sqlquery.bindValue(":nMaxFontPro",QVariant(pMaxTextItem->m_text.eTextPro));
        mColor=pwnd->StringTOColor(pMaxTextItem->m_text.nFontColor);
        sqlquery.bindValue(":nMaxFontColor",QVariant(ColorToInt(mColor)));
        sqlquery.bindValue(":nMaxStyle",QVariant(pMaxTextItem->m_text.nStylePadding+1));
        sqlquery.bindValue(":nMaxAlpha",QVariant(pMaxTextItem->m_text.nAlphaPadding));
        mColor=pwnd->StringTOColor(pMaxTextItem->m_text.nForeColorPadding);
        sqlquery.bindValue(":nMaxForeColor",QVariant(ColorToInt(mColor)));
        mColor=pwnd->StringTOColor(pMaxTextItem->m_text.nBackColorPadding);
        sqlquery.bindValue(":nMaxBackColor",QVariant(ColorToInt(mColor)));
        sqlquery.bindValue(":nMaxAdapt",QVariant(pMaxTextItem->m_text.adaptTexts));
    }


    sqlquery.bindValue(":nMinStartX",QVariant(rectmin.x()));
    sqlquery.bindValue(":nMinStartY",QVariant(rectmin.y()));
    sqlquery.bindValue(":nMinWidth",QVariant(rectmin.width()));
    sqlquery.bindValue(":nMinHeight",QVariant(rectmin.height()));


    if(pMinTextItem)
    {
        sqlquery.bindValue(":nMinFont",QVariant(pMinTextItem->m_text.sFontFamly));
        if(pMinTextItem->m_text.eTextAlign==0){
            align=2;
        }else if(pMinTextItem->m_text.eTextAlign==1){
            align=1;
        }else if(pMinTextItem->m_text.eTextAlign==2){
            align=3;
        }
        sqlquery.bindValue(":nMinAlign",QVariant(align));
        sqlquery.bindValue(":nMinFontSize",QVariant(pMinTextItem->m_text.sFontSize));
        sqlquery.bindValue(":nMinFontPro",QVariant(pMinTextItem->m_text.eTextPro));
        mColor=pwnd->StringTOColor(pMinTextItem->m_text.nFontColor);
        sqlquery.bindValue(":nMinFontColor",QVariant(ColorToInt(mColor)));
        sqlquery.bindValue(":nMinStyle",QVariant(pMinTextItem->m_text.nStylePadding+1));
        sqlquery.bindValue(":nMinAlpha",QVariant(pMinTextItem->m_text.nAlphaPadding));
        mColor=pwnd->StringTOColor(pMinTextItem->m_text.nForeColorPadding);
        sqlquery.bindValue(":nMinForeColor",QVariant(ColorToInt(mColor)));
        mColor=pwnd->StringTOColor(pMinTextItem->m_text.nBackColorPadding);
        sqlquery.bindValue(":nMinBackColor",QVariant(ColorToInt(mColor)));
        sqlquery.bindValue(":nMinAdapt",QVariant(pMinTextItem->m_text.adaptTexts));
    }

    sqlquery.bindValue(":nTextStartX",QVariant(recttxt.x()));
    sqlquery.bindValue(":nTextStartY",QVariant(recttxt.y()));
    sqlquery.bindValue(":nTextWidth",QVariant(recttxt.width()));
    sqlquery.bindValue(":nTextHeight",QVariant(recttxt.height()));

    if(pInpTextItem)
    {
        sqlquery.bindValue(":nTextFont",QVariant(pInpTextItem->m_text.sFontFamly));
        if(pInpTextItem->m_text.eTextAlign==0){
            align=2;
        }else if(pInpTextItem->m_text.eTextAlign==1){
            align=1;
        }else if(pInpTextItem->m_text.eTextAlign==2){
            align=3;
        }
        sqlquery.bindValue(":nTextAlign",QVariant(align));
        sqlquery.bindValue(":nTextFontSize",QVariant(pInpTextItem->m_text.sFontSize));
        sqlquery.bindValue(":nTextFontPro",QVariant(pInpTextItem->m_text.eTextPro));
        mColor=pwnd->StringTOColor(pInpTextItem->m_text.nFontColor);
        sqlquery.bindValue(":nTextFontColor",QVariant(ColorToInt(mColor)));
        sqlquery.bindValue(":nTextStyle",QVariant(pInpTextItem->m_text.nStylePadding+1));
        sqlquery.bindValue(":nTextAlpha",QVariant(pInpTextItem->m_text.nAlphaPadding));
        mColor=pwnd->StringTOColor(pInpTextItem->m_text.nForeColorPadding);
        sqlquery.bindValue(":nTextForeColor",QVariant(ColorToInt(mColor)));
        mColor=pwnd->StringTOColor(pInpTextItem->m_text.nBackColorPadding);
        sqlquery.bindValue(":nTextBackColor",QVariant(ColorToInt(mColor)));
        sqlquery.bindValue(":nTextAdapt",QVariant(pInpTextItem->m_text.adaptTexts));
    }
    else
    {
        sqlquery.bindValue(":nTextAdapt",QVariant(false));
    }


    bool result = false;
    result = sqlquery.exec();
    qDebug() << "insert keyBoard table :"<<result;
}

//查找所有碰撞item
void SamDrawScene::addCollidItems(QGraphicsItem* pItem,QList <QGraphicsItem *> &list)
{
    if(!list.contains(pItem))
    {
        list << pItem;
    }
    QList <QGraphicsItem *> cItems = SDCollidItems(pItem);
    foreach(QGraphicsItem* item,cItems)
    {
        if(!list.contains(item) && item->parentItem() == 0)
            addCollidItems(item,list);
    }
}
//将所有碰撞item按index相同分组
void SamDrawScene::compileItem(QGraphicsItem* pItem,QSqlDatabase &db, int nSceneId,int &count,int index)
{
    QString sType = "";
    switch(pItem->type())
    {
    case SAM_DRAW_OBJECT_RECT_NEW:              //15
        {
            sType = tr("矩形");
            QRectBasicItem *rectItem = dynamic_cast<QRectBasicItem *>(pItem);
            if(rectItem)
                rectItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_ELIPSE_NEW:              //16
        {
            sType = tr("圆/椭圆");
            QElipseBasicItem *elipseItem = dynamic_cast<QElipseBasicItem *>(pItem);
            if(elipseItem)
                elipseItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_LINE_NEW:                 //17
        {
            sType = tr("直线");
            QLineBasicItem *lineItem = dynamic_cast<QLineBasicItem *>(pItem);
            if(lineItem)
                lineItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_POLYGON_NEW:              //18
        {
            sType = tr("多边形");
            QPolygonBasicItem *polygonItem = dynamic_cast<QPolygonBasicItem *>(pItem);
            if(polygonItem)
                polygonItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_FOLDLINE_NEW:             //19
        {
            sType = tr("折线");
            QFoldLineBasicItem *foldLineItem = dynamic_cast<QFoldLineBasicItem *>(pItem);
            if(foldLineItem)
                foldLineItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_FREELINE_NEW:             //20
        {
            sType = tr("自由曲线");
            QFreeLineBasicItem *freeLineItem = dynamic_cast<QFreeLineBasicItem *>(pItem);
            if(freeLineItem)
                freeLineItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_TEXT:                 //22
        {
            sType = tr("静态文本");
            QSimpleTextItem *textItem = dynamic_cast<QSimpleTextItem *>(pItem);
            if(textItem)
                textItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_PIXMAP:
        {
            sType = tr("图片");
            QPixmapItem *pPixmap = dynamic_cast<QPixmapItem *>(pItem);
            if(pPixmap)
                pPixmap->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW:           //25
        {
            sType = tr("曲线/圆弧");
            QLineCircleBasicItem *lineCircleItem = dynamic_cast<QLineCircleBasicItem *>(pItem);
            if(lineCircleItem)
                lineCircleItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
        {
            sType = tr("圆角矩形");
            QRoundedRectBasic *pRoundItem = dynamic_cast<QRoundedRectBasic *>(pItem);
            if(pRoundItem)
                pRoundItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_ARC_NEW:
        {
            sType = tr("扇形");
            QArcBasicItem *pArcItem = dynamic_cast<QArcBasicItem *>(pItem);
            if(pArcItem)
                pArcItem->compile(db,nSceneId,count,index);
            break;
        }
///////////////wxy add start
    case SAM_DRAW_OBJECT_RECT:              //15
        {
            sType = tr("矩形");
            QRectItem *rectItem = dynamic_cast<QRectItem *>(pItem);
            if(rectItem)
                rectItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_ELIPSE:              //16
        {
            sType = tr("圆/椭圆");
            QElipseItem *elipseItem = dynamic_cast<QElipseItem *>(pItem);
            if(elipseItem)
                elipseItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_LINE:                 //17
        {
            sType = tr("直线");
            QLineItem *lineItem = dynamic_cast<QLineItem *>(pItem);
            if(lineItem)
                lineItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_POLYGON:              //18
        {
            sType = tr("多边形");
            QPolygonItem *polygonItem = dynamic_cast<QPolygonItem *>(pItem);
            if(polygonItem)
                polygonItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_FOLDLINE:             //19
        {
            sType = tr("折线");
            QFoldLineItem *foldLineItem = dynamic_cast<QFoldLineItem *>(pItem);
            if(foldLineItem)
                foldLineItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_FREELINE:             //20
        {
            sType = tr("自由曲线");
            QFreeLineItem *freeLineItem = dynamic_cast<QFreeLineItem *>(pItem);
            if(freeLineItem)
                freeLineItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_LINECIRCLE:           //25
        {
            sType = tr("曲线/圆弧");
            QLineCircleItem *lineCircleItem = dynamic_cast<QLineCircleItem *>(pItem);
            if(lineCircleItem)
                lineCircleItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
        {
            sType = tr("圆角矩形");
            QRoundedRect *pRoundItem = dynamic_cast<QRoundedRect *>(pItem);
            if(pRoundItem)
                pRoundItem->compile(db,nSceneId,count,index);
            break;
        }
    case SAM_DRAW_OBJECT_ARC:
        {
            sType = tr("扇形");
            QArcItem *pArcItem = dynamic_cast<QArcItem *>(pItem);
            if(pArcItem)
                pArcItem->compile(db,nSceneId,count,index);
            break;
        }
///////////////wxy add end
    case SAM_DRAW_OBJECT_GROUP:                //23
        {
            QItemGroup *groupItem = dynamic_cast<QItemGroup *>(pItem);
            if(groupItem)
            {
                groupItem->compile(db,nSceneId,count,index);
                sType = groupItem->getItemName();
            }

            break;
        }
    default:
        break;
    }
    QRectF rect = this->sceneRect();
    QRectF itemRect = pItem->sceneBoundingRect();
    if(itemRect.right() > rect.right()+1 || itemRect.bottom() > rect.bottom()+1)
    {
        //pwnd->MessageOut(tr("[")+ this->sNewScreenName + tr("]:[") + sType + tr("] 超出画面"));
        int iSheetIndex = -1;
        for(int i = 0; i < pwnd->pSceneSheet.size(); i++)
        {
            if(pwnd->pSceneSheet[i]->sNewScreenName == this->sNewScreenName)
            {
                iSheetIndex = i;
                break;
            }
        }
        MsgOutPut* pMsgOutPut = new MsgOutPut ;//信息输出窗口双击要处理的类
        pMsgOutPut->pItem = pItem;
        pMsgOutPut->nSheetIndex = iSheetIndex;
        emit Messageout("["+ this->sNewScreenName + "]:[" + sType + tr("] 超出画面"), MSG_WARNING, pMsgOutPut);
    }
}

void SamDrawScene::SetSelectFlag(QGraphicsItem* pItem,bool flag)
{
    switch(pItem->type())
    {
    case SAM_DRAW_OBJECT_RECT:              //15
        {
            QRectItem *rectItem = dynamic_cast<QRectItem *>(pItem);
            if(rectItem)
                rectItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_ELIPSE:              //16
        {
            QElipseItem *elipseItem = dynamic_cast<QElipseItem *>(pItem);
            if(elipseItem)
                elipseItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_LINE:                 //17
        {
            QLineItem *lineItem = dynamic_cast<QLineItem *>(pItem);
            if(lineItem)
                lineItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_POLYGON:              //18
        {
            QPolygonItem *polygonItem = dynamic_cast<QPolygonItem *>(pItem);
            if(polygonItem)
                polygonItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_FOLDLINE:             //19
        {
            QFoldLineItem *foldLineItem = dynamic_cast<QFoldLineItem *>(pItem);
            if(foldLineItem)
                foldLineItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_FREELINE:             //20
        {
            QFreeLineItem *freeLineItem = dynamic_cast<QFreeLineItem *>(pItem);
            if(freeLineItem)
                freeLineItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_TEXT:                 //22
        {
            QSimpleTextItem *textItem = dynamic_cast<QSimpleTextItem *>(pItem);
            if(textItem)
                textItem->SetselectFlag(flag);
            break;
        }
//    case SAM_DRAW_OBJECT_PIXMAP:
//        {
//            QPixmapItem *pPixmap = dynamic_cast<QPixmapItem *>(pItem);
//            if(pPixmap)
//                pPixmap->SetselectFlag(flag);
//            break;
//        }
    case SAM_DRAW_OBJECT_LINECIRCLE:           //25
        {
            QLineCircleItem *lineCircleItem = dynamic_cast<QLineCircleItem *>(pItem);
            if(lineCircleItem)
                lineCircleItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
        {
            QRoundedRect *pRoundItem = dynamic_cast<QRoundedRect *>(pItem);
            if(pRoundItem)
                pRoundItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_ARC:
        {
            QArcItem *pArcItem = dynamic_cast<QArcItem *>(pItem);
            if(pArcItem)
                pArcItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_GROUP:                //23
        {
            QItemGroup *groupItem = dynamic_cast<QItemGroup *>(pItem);
            if(groupItem)
                groupItem->SetselectFlag(flag);

            break;
        }
/////////////wxy add start
    case SAM_DRAW_OBJECT_RECT_NEW:              //15
        {
            QRectBasicItem *rectItem = dynamic_cast<QRectBasicItem *>(pItem);
            if(rectItem)
                rectItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_ELIPSE_NEW:              //16
        {
            QElipseBasicItem *elipseItem = dynamic_cast<QElipseBasicItem *>(pItem);
            if(elipseItem)
                elipseItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_LINE_NEW:                 //17
        {
            QLineBasicItem *lineItem = dynamic_cast<QLineBasicItem *>(pItem);
            if(lineItem)
                lineItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_POLYGON_NEW:              //18
        {
            QPolygonBasicItem *polygonItem = dynamic_cast<QPolygonBasicItem *>(pItem);
            if(polygonItem)
                polygonItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_FOLDLINE_NEW:             //19
        {
            QFoldLineBasicItem *foldLineItem = dynamic_cast<QFoldLineBasicItem *>(pItem);
            if(foldLineItem)
                foldLineItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_FREELINE_NEW:             //20
        {
            QFreeLineBasicItem *freeLineItem = dynamic_cast<QFreeLineBasicItem *>(pItem);
            if(freeLineItem)
                freeLineItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW:           //25
        {
            QLineCircleBasicItem *lineCircleItem = dynamic_cast<QLineCircleBasicItem *>(pItem);
            if(lineCircleItem)
                lineCircleItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
        {
            QRoundedRectBasic *pRoundItem = dynamic_cast<QRoundedRectBasic *>(pItem);
            if(pRoundItem)
                pRoundItem->SetselectFlag(flag);
            break;
        }
    case SAM_DRAW_OBJECT_ARC_NEW:
        {
            QArcBasicItem *pArcItem = dynamic_cast<QArcBasicItem *>(pItem);
            if(pArcItem)
                pArcItem->SetselectFlag(flag);
            break;
        }
////////////wxy add end
    default:
        break;
    }
}

bool SamDrawScene::GetSelectFlag(QGraphicsItem* pItem)
{
    bool bflag = false;
    switch(pItem->type())
    {
    case SAM_DRAW_OBJECT_RECT:              //15
        {
            QRectItem *rectItem = dynamic_cast<QRectItem *>(pItem);
            if(rectItem)
                bflag = rectItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_ELIPSE:              //16
        {
            QElipseItem *elipseItem = dynamic_cast<QElipseItem *>(pItem);
            if(elipseItem)
               bflag = elipseItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_LINE:                 //17
        {
            QLineItem *lineItem = dynamic_cast<QLineItem *>(pItem);
            if(lineItem)
                bflag = lineItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_POLYGON:              //18
        {
            QPolygonItem *polygonItem = dynamic_cast<QPolygonItem *>(pItem);
            if(polygonItem)
                bflag = polygonItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_FOLDLINE:             //19
        {
            QFoldLineItem *foldLineItem = dynamic_cast<QFoldLineItem *>(pItem);
            if(foldLineItem)
                bflag = foldLineItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_FREELINE:             //20
        {
            QFreeLineItem *freeLineItem = dynamic_cast<QFreeLineItem *>(pItem);
            if(freeLineItem)
                bflag = freeLineItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_TEXT:                 //22
        {
            QSimpleTextItem *textItem = dynamic_cast<QSimpleTextItem *>(pItem);
            if(textItem)
                bflag = textItem->GetselectFlag();
            break;
        }
//    case SAM_DRAW_OBJECT_PIXMAP:
//        {
//            QPixmapItem *pPixmap = dynamic_cast<QPixmapItem *>(pItem);
//            if(pPixmap)
//                pPixmap->SetselectFlag(flag);
//            break;
//        }
    case SAM_DRAW_OBJECT_LINECIRCLE:           //25
        {
            QLineCircleItem *lineCircleItem = dynamic_cast<QLineCircleItem *>(pItem);
            if(lineCircleItem)
                bflag = lineCircleItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
        {
            QRoundedRect *pRoundItem = dynamic_cast<QRoundedRect *>(pItem);
            if(pRoundItem)
                bflag = pRoundItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_ARC:
        {
            QArcItem *pArcItem = dynamic_cast<QArcItem *>(pItem);
            if(pArcItem)
                bflag = pArcItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_GROUP:                //23
        {
            QItemGroup *groupItem = dynamic_cast<QItemGroup *>(pItem);
            if(groupItem)
                bflag = groupItem->GetselectFlag();

            break;
        }
 ////////////////wxy add start
    case SAM_DRAW_OBJECT_RECT_NEW:              //15
        {
            QRectBasicItem *rectItem = dynamic_cast<QRectBasicItem *>(pItem);
            if(rectItem)
                bflag = rectItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_ELIPSE_NEW:              //16
        {
            QElipseBasicItem *elipseItem = dynamic_cast<QElipseBasicItem *>(pItem);
            if(elipseItem)
               bflag = elipseItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_LINE_NEW:                 //17
        {
            QLineBasicItem *lineItem = dynamic_cast<QLineBasicItem *>(pItem);
            if(lineItem)
                bflag = lineItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_POLYGON_NEW:              //18
        {
            QPolygonBasicItem *polygonItem = dynamic_cast<QPolygonBasicItem *>(pItem);
            if(polygonItem)
                bflag = polygonItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_FOLDLINE_NEW:             //19
        {
            QFoldLineBasicItem *foldLineItem = dynamic_cast<QFoldLineBasicItem *>(pItem);
            if(foldLineItem)
                bflag = foldLineItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_FREELINE_NEW:             //20
        {
            QFreeLineBasicItem *freeLineItem = dynamic_cast<QFreeLineBasicItem *>(pItem);
            if(freeLineItem)
                bflag = freeLineItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW:           //25
        {
            QLineCircleBasicItem *lineCircleItem = dynamic_cast<QLineCircleBasicItem *>(pItem);
            if(lineCircleItem)
                bflag = lineCircleItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
        {
            QRoundedRectBasic *pRoundItem = dynamic_cast<QRoundedRectBasic *>(pItem);
            if(pRoundItem)
                bflag = pRoundItem->GetselectFlag();
            break;
        }
    case SAM_DRAW_OBJECT_ARC_NEW:
        {
            QArcBasicItem *pArcItem = dynamic_cast<QArcBasicItem *>(pItem);
            if(pArcItem)
                bflag = pArcItem->GetselectFlag();
            break;
        }
 ///////////////wxy add end
    default:
        break;
    }
	return bflag;
}

/***************************************************************
 *函数名称：mousePressMove
 *函数功能：鼠标按下时，表格拖拉处理
 *参数含义：NULL
 *返回值:       NULL
 *编辑作者：郑启红
 *编辑日期：2012.9.24
 **************************************************************/
void SamDrawScene::mousePressMove()
{
    oItemRects.clear();
    //处理表格拖拉 bMousePressTable = false;//鼠标按下表格控件
    if(this->selectedItems().size() == 1)
    {
        QGraphicsItem *pressitem = this->selectedItems().at(0);//所选择的图形
        QItemGroup *itemGroup = dynamic_cast<QItemGroup *>(pressitem);
        int iKey  = 0;
        if(itemGroup)
            iKey = itemGroup->GroupType();
        if(iKey == SAM_DRAW_GROUP_TABLE || iKey == SAM_DRAW_GROUP_ALARMITEM
           || iKey == SAM_DRAW_GROUP_HISALARMITEM || iKey == SAM_DRAW_GROUP_HISTORYDATE
           || iKey == SAM_DRAW_GROUP_RECIPESHOW || iKey == SAM_DRAW_GROUP_TEXTBOARD) //表格、报警显示器、历史报警显示器、配方显示器
        {
            TabeRect = pressitem->sceneBoundingRect();

            //当鼠标按下时没在item上方或者在8个包围小矩形上时直接返回
            if(itemGroup->hitTest(MousePressPos,TabeRect,true) > 0
               || !TabeRect.contains(MousePressPos))
            {
                return;
            }

            QList<QGraphicsItem *> list = pressitem->childItems();
            QString sName = "";
            QCursor cur = pwnd->pView->cursor();

            vVLine.clear();
            vHLine.clear();
            vTileTex.clear();

            foreach(QGraphicsItem *pItem,list)
            {
                QPointF pos = pItem->boundingRect().topLeft()+pItem->scenePos();
                sName = pItem->data(GROUP_NAME_KEY).toString();
                if(sName.contains("VLine")) //垂直线
                {
                    TablePro odata;
                    odata.pItem = pItem;
                    odata.pos = pos;
                    if(pos.x() >= MousePressPos.x()-2 && pos.x() < MousePressPos.x()+2)
                    {
                        odata.bMark = true;
                        bMoveFlag = (QGraphicsItem::ItemIsMovable == (pressitem->flags() & QGraphicsItem::ItemIsMovable));
                        pressitem->setFlag(QGraphicsItem::ItemIsMovable, false);
                        cur.setShape(Qt::SplitHCursor);
                        pwnd->pView->setCursor(cur);
                        iVHFlag = 1;
                        pTableItam = pressitem;
                        pTableItam->setData(TABLE_ITEM_MOVE,QVariant(100));
                        pTableLine = dynamic_cast<QLineItem *>(pItem);
                        QRectF oRect;
                        foreach(QGraphicsItem* cItem,pTableItam->childItems())
                        {
                            oRect.setTopLeft(cItem->pos());
                            oRect.setSize(cItem->boundingRect().size());
                            oItemRects.append(oRect);
                        }
                    }
                    else
                        odata.bMark = false;
                    vVLine.append(odata);
                }
                if(sName.contains("HLine")) //水平线
                {
                    TablePro odata;
                    odata.pItem = pItem;
                    odata.pos = pos;
                    if(pos.y() >= MousePressPos.y()-2 && pos.y()< MousePressPos.y()+2)
                    {
                        odata.bMark = true;
                        bMoveFlag = (QGraphicsItem::ItemIsMovable == (pressitem->flags() & QGraphicsItem::ItemIsMovable));
                        pressitem->setFlag(QGraphicsItem::ItemIsMovable, false);
                        cur.setShape(Qt::SplitVCursor);
                        pwnd->pView->setCursor(cur);
                        iVHFlag = 2;
                        pTableItam = pressitem;
                        pTableItam->setData(TABLE_ITEM_MOVE,QVariant(100));
                        pTableLine = dynamic_cast<QLineItem *>(pItem);
                        QRectF oRect;
                        foreach(QGraphicsItem* cItem,pTableItam->childItems())
                        {
                            oRect.setTopLeft(cItem->pos());
                            oRect.setSize(cItem->boundingRect().size());
                            oItemRects.append(oRect);
                        }
                    }
                    else
                        odata.bMark = false;
                    vHLine.append(odata);
                }
                if(sName.contains("mTitleRect"))
                {
                    pBackItam = pItem;
                }
                if(sName.contains("mCloumRect"))
                {
                    pRecipeItem = pItem;
                }
                if(pItem->type() == SAM_DRAW_OBJECT_TEXT)//文本
                {
                    TablePro odata;
                    odata.pItem = pItem;
                    odata.pos = pos;
                    odata.bMark = true;
                    vTileTex.append(odata);
                }
            }
        }
        if(iKey == SAM_DRAW_GROUP_ANIMATION)
        {
            QList<QGraphicsItem *> list = pressitem->childItems();
            QString sName = "";
            QCursor cur = pwnd->pView->cursor();

            foreach(QGraphicsItem *pItem,list)
            {
                sName = pItem->data(GROUP_NAME_KEY).toString();
                if("mMain" == sName) //垂直线
                {
                    QPointF pos = pItem->boundingRect().bottomRight()+pItem->scenePos();
                    if(pos.x() >= MousePressPos.x()-4
                       && pos.x() <= MousePressPos.x()+4
                       && pos.y() >= MousePressPos.y()-4
                       && pos.y() <= MousePressPos.y()+4)
                    {
                        cur.setShape(Qt::SizeFDiagCursor);
                        pressitem->setFlag(QGraphicsItem::ItemIsMovable, false);
                        pwnd->pView->setCursor(cur);
                        pAniMageItam = pItem;
                        QRectF oRect;
                        foreach(QGraphicsItem* cItem,pAniMageItam->childItems())
                        {
                            oRect.setTopLeft(cItem->pos());
                            oRect.setSize(cItem->boundingRect().size());
                            oItemRects.append(oRect);
                        }
                    }
                    break;
                }
            }
        }
    }
}

/***************************************************************
 *函数名称：moveLineWhenMouseMove
 *函数功能：鼠标按下时，表格拖拉处理
 *参数含义：NULL
 *返回值:       NULL
 *编辑作者：郑启红
 *编辑日期：2012.9.24
 **************************************************************/
void SamDrawScene::moveLineWhenMouseMove()
{
    if(pTableLine && bMousePress)
    {
        int ii = 0;
        bool flag = false;
        int index = -1;
        int isize = 0;
        int ispace = 10;
        int itextW = 0;

        if(iVHFlag == 1) //垂直线
        {
            qreal nXDerict = CurMousePoint.x() - LastMousePoint.x();//大于0向右移动
            qreal mMoveX = CurMousePoint.x();
            isize = vVLine.size();
            for(ii = 0; ii < isize;ii++)
            {
                flag = vVLine.at(ii).bMark;
                if(flag)
                {
                    index = ii;
                    break;
                }
            }

            if(isize == 1)
            {
                if(mMoveX > (TabeRect.right()-ispace)
                   && mMoveX < (TabeRect.left()+ispace))
                    return;
                if(mMoveX >= TabeRect.right()-ispace
                   && TabeRect.right()-ispace >= TabeRect.left()+ispace)
                    mMoveX = TabeRect.right()-ispace;
                if(mMoveX <= TabeRect.left()+ispace
                   && TabeRect.left()+ispace <= TabeRect.right()-ispace)
                    mMoveX = TabeRect.left()+ispace;
                setTextPosVWhenMouseMove(mMoveX,index,isize);
            }
            else if(isize > 1)
            {
                if(index == 0) //第一条垂直线
                {
                    if(vVLine.at(index).pos.x() < (TabeRect.left()+ispace)
                        && (vVLine.at(index).pos.x() + ispace) > vVLine.at(index + 1).pos.x())
                        return;
                    if(mMoveX <= TabeRect.left()+ispace
                       && mMoveX >= vVLine.at(index+1).pos.x()-ispace)
                    {
                        return;
                    }
                    else if(mMoveX <= TabeRect.left()+ispace
                            && nXDerict < 0)
                    {
                        return;
                    }
                    else if(mMoveX >= vVLine.at(index+1).pos.x()-ispace
                            && nXDerict > 0)
                    {
                        return;
                    }
                    if(mMoveX >= vVLine.at(index+1).pos.x()-ispace)
                    {
                        mMoveX = vVLine.at(index+1).pos.x()-ispace;
                    }
                    if(mMoveX <= TabeRect.left()+ispace)
                    {
                        mMoveX = TabeRect.left()+ispace;
                    }
                    setTextPosVWhenMouseMove(mMoveX,index,isize);
                }
                else if(index == isize-1) //最后一条垂直线
                {
                    if(vVLine.at(index).pos.x() > (TabeRect.right()-ispace)
                        && (vVLine.at(index).pos.x() - ispace) < vVLine.at(index - 1).pos.x())
                        return;
                    if(mMoveX >= TabeRect.right()-ispace
                       && mMoveX <= vVLine.at(index-1).pos.x()+ispace)
                    {
                        return;
                    }
                    else if(mMoveX <= vVLine.at(index-1).pos.x()+ispace
                            && nXDerict < 0)
                    {
                        return;
                    }
                    else if(mMoveX >= TabeRect.right()-ispace
                            && nXDerict > 0)
                    {
                        return;
                    }
                    if(mMoveX >= TabeRect.right()-ispace)
                    {
                        mMoveX = TabeRect.right()-ispace;
                    }
                    if(mMoveX <= vVLine.at(index-1).pos.x()+ispace)
                    {
                        mMoveX = vVLine.at(index-1).pos.x()+ispace;
                    }
                    setTextPosVWhenMouseMove(mMoveX,index,isize);
                }
                else
                {
                    if(vVLine.at(index).pos.x() > (vVLine.at(index + 1).pos.x()-ispace)
                        && (vVLine.at(index).pos.x() - ispace) < vVLine.at(index - 1).pos.x())
                        return;

                    if(mMoveX <= vVLine.at(index-1).pos.x()+ispace
                       && mMoveX >= vVLine.at(index+1).pos.x()-ispace)
                    {
                        return;
                    }
                    else if(mMoveX <= vVLine.at(index-1).pos.x()+ispace
                            && nXDerict < 0)
                    {
                        return;
                    }
                    else if(mMoveX >= vVLine.at(index+1).pos.x()-ispace
                            && nXDerict > 0)
                    {
                        return;
                    }
                    if(mMoveX >= vVLine.at(index+1).pos.x()-ispace)
                    {
                        mMoveX = vVLine.at(index+1).pos.x()-ispace;
                    }
                    if(mMoveX <= vVLine.at(index-1).pos.x()+ispace)
                    {
                        mMoveX = vVLine.at(index-1).pos.x()+ispace;
                    }
                    setTextPosVWhenMouseMove(mMoveX,index,isize);
                }
            }

            if(pTableLine)
            {
                QPointF jj = pTableLine->boundingRect().topLeft();
                jj = pTableLine->mapFromParent(jj);
                CurMousePoint.setX(mMoveX);
                QPointF aa = pTableLine->mapFromScene(CurMousePoint);
                pTableLine->setX(aa.x()-jj.x());
            }
        }
        else if(iVHFlag == 2) //水平
        {
            qreal nYDerict = CurMousePoint.y() - LastMousePoint.y();//大于0向下移动
            qreal mMoveY = CurMousePoint.y();
            isize = vHLine.size();
            for(ii = 0; ii < isize;ii++)
            {
                flag = vHLine.at(ii).bMark;
                if(flag)
                {
                    index = ii;
                    break;
                }
            }
            if(isize == 1)
            {
                if(vHLine.at(index).pos.y() > (TabeRect.bottom()-ispace)
                   && vHLine.at(index).pos.y() < (TabeRect.top()+ispace))
                    return;
                if(mMoveY <= TabeRect.top()+ispace
                   && TabeRect.top()+ispace <  TabeRect.bottom()-ispace)
                    mMoveY = TabeRect.top()+ispace;
                if(mMoveY >= TabeRect.bottom()-ispace
                   && TabeRect.bottom()-ispace > TabeRect.top()+ispace)
                    mMoveY = TabeRect.bottom()-ispace;
                setTextPosHWhenMouseMove(mMoveY,index,isize);
            }
            else if(isize > 1)
            {
                if(index == 0)//第一条
                {
                    if(vHLine.at(index).pos.y() < (TabeRect.top()+ispace)
                       && vHLine.at(index).pos.y() > (vHLine.at(index+1).pos.y()-ispace))
                    {
                        return;
                    }
                    if(mMoveY <= TabeRect.top()+ispace
                       && mMoveY >= vHLine.at(index+1).pos.y()-ispace)
                    {
                        return;
                    }
                    else if(mMoveY <= TabeRect.top()+ispace
                       && nYDerict < 0)
                    {
                        return;
                    }
                    else if(mMoveY >= vHLine.at(index+1).pos.y()-ispace
                       && nYDerict > 0)
                    {
                        return;
                    }
                    if(mMoveY <= TabeRect.top()+ispace)
                        mMoveY = TabeRect.top()+ispace;
                    if(mMoveY >= vHLine.at(index+1).pos.y()-ispace)
                        mMoveY = vHLine.at(index+1).pos.y()-ispace;
                    setTextPosHWhenMouseMove(mMoveY,index,isize);
                }
                else if(index == isize-1)//最后一条
                {
                    if(vHLine.at(index).pos.y() < (vHLine.at(index-1).pos.y()+ispace)
                        && vHLine.at(index).pos.y() > (TabeRect.bottom()-ispace))
                    {
                        return;
                    }
                    if(mMoveY <= vHLine.at(index-1).pos.y()+ispace
                       && mMoveY >= TabeRect.bottom()-ispace)
                    {
                        return;
                    }
                    else if(mMoveY <= vHLine.at(index-1).pos.y()+ispace
                            && nYDerict < 0)
                    {
                        return;
                    }
                    else if(mMoveY >= TabeRect.bottom()-ispace
                            && nYDerict > 0)
                    {
                        return;
                    }
                    if(mMoveY <= vHLine.at(index-1).pos.y()+ispace)
                        mMoveY = vHLine.at(index-1).pos.y()+ispace;
                    if(mMoveY >= TabeRect.bottom()-ispace)
                        mMoveY = TabeRect.bottom()-ispace;
                    setTextPosHWhenMouseMove(mMoveY,index,isize);
                }
                else
                {
                    if(vHLine.at(index).pos.y() < (vHLine.at(index-1).pos.y()+ispace)
                        || vHLine.at(index).pos.y() > (vHLine.at(index + 1).pos.y() - ispace))
                    {
                        return;
                    }
                    if(mMoveY <= vHLine.at(index-1).pos.y()+ispace
                       && mMoveY >= vHLine.at(index+1).pos.y()-ispace)
                    {
                        return;
                    }
                    else if(mMoveY <= vHLine.at(index-1).pos.y()+ispace
                            && nYDerict < 0)
                    {
                        return;
                    }
                    else if(mMoveY >= vHLine.at(index+1).pos.y()-ispace
                            && nYDerict > 0)
                    {
                        return;
                    }
                    if(mMoveY <= vHLine.at(index-1).pos.y()+ispace)
                        mMoveY = vHLine.at(index-1).pos.y()+ispace;
                    if(mMoveY >= vHLine.at(index+1).pos.y()-ispace)
                        mMoveY = vHLine.at(index+1).pos.y()-ispace;
                    setTextPosHWhenMouseMove(mMoveY,index,isize);
                }
            }

            if(pTableLine)
            {
                QPointF jj = pTableLine->boundingRect().topLeft();
                jj = pTableLine->mapFromParent(jj);

                CurMousePoint.setY(mMoveY);
                QPointF aa = pTableLine->mapFromScene(CurMousePoint);
                pTableLine->setY(aa.y()-jj.y());
            }
        }
    }
    if(pAniMageItam && bMousePress)
    {
        QGraphicsItem * parentItem = pAniMageItam->topLevelItem();
        QPointF bottom = parentItem->sceneBoundingRect().bottomRight();
        QGroupItem *pnewItem = new QGroupItem(pAniMageItam);
        QPointF pos = pAniMageItam->sceneBoundingRect().topLeft();
        if(CurMousePoint.y() - pos.y() > 20 && CurMousePoint.y() < bottom.y())
        pnewItem->SetHeigth(CurMousePoint.y() - pos.y());
        if(CurMousePoint.x() - pos.x() > 20 && CurMousePoint.x() < bottom.x())
        pnewItem->SetWidth(CurMousePoint.x() - pos.x());
    }
}

/***************************************************************
 *函数名称：setTextPosVWhenMouseMove
 *函数功能：鼠标按下时，处理垂直线的拖拉
 *参数含义：
 *mMoveX:    X方向鼠标移动的距离
 *index：       垂直线在vVLine容器的下标，即第几条垂直线
 *isize:           垂直线的数目，即vVLine容器大小
 *返回值:       NULL
 *编辑作者：郑启红
 *编辑日期：2012.9.24
 *更改时间：2012.9.25
 **************************************************************/
void SamDrawScene::setTextPosVWhenMouseMove(qreal mMoveX, int index, int isize)
{
    qreal  itextW = 0;
    QPointF pos;
    QGroupItem *pnewItem = NULL;
    QItemGroup *itemGroup = dynamic_cast<QItemGroup *>(pTableItam);
    int iKey  = 0;
    HisAlarmItem *HisalarmItem = NULL;
    QHistoryDataShowAttr* HisDatapItem =NULL;
    qMessageBoradAttr *pMessageItem = NULL;
    stAlarmItemPro alarmPro;
    int icount = 0;
    QString sName = "";
    bool bHisdataNo = false;
    bool bMessageNo = false;


    if(itemGroup)
    {
        iKey = itemGroup->GroupType();
        if(iKey == SAM_DRAW_GROUP_HISALARMITEM)//历史报警显示器
        {
            HisalarmItem = dynamic_cast<HisAlarmItem *> (pTableItam);
            if (HisalarmItem)
            {
                alarmPro = HisalarmItem->alarmPro;
            }
        }
        else if(iKey == SAM_DRAW_GROUP_HISTORYDATE)//历史数据显示器
        {
            HisDatapItem = dynamic_cast<QHistoryDataShowAttr *> (pTableItam);
            if (HisDatapItem)
            {
                bHisdataNo = HisDatapItem->m_bShowCode;
            }
        }
        else if(iKey == SAM_DRAW_GROUP_TEXTBOARD)//留言本
        {
            pMessageItem = dynamic_cast<qMessageBoradAttr *> (pTableItam);
            if (pMessageItem)
            {
                bMessageNo = pMessageItem->m_bShowId;
            }
        }
    }

    if(isize == 1)
    {
        if(iKey == SAM_DRAW_GROUP_ALARMITEM ||
           (HisalarmItem && false == alarmPro.bShowNumber) || (HisDatapItem && false == bHisdataNo )
           || (false == bMessageNo && pMessageItem)) //报警显示器、历史报警显示器、历史数据显示器
        {
            itextW = mMoveX-TabeRect.left();
            pnewItem = new QGroupItem(vTileTex.at(0).pItem);
            pnewItem->SetWidth(itextW);

            pnewItem = new QGroupItem(vTileTex.at(1).pItem);
            itextW = TabeRect.right()-mMoveX;
            pnewItem->SetWidth(itextW);

            pos.setX(mMoveX);
            QPointF aa =  vTileTex.at(1).pItem->mapFromScene(pos);
            QPointF jj = vTileTex.at(1).pItem->boundingRect().topLeft();
            jj = vTileTex.at(1).pItem->mapFromParent(jj);
            vTileTex.at(1).pItem->setX(aa.x()-jj.x());

            //为历史数据显示器第二行时间增加 begein
            if(iKey == SAM_DRAW_GROUP_HISTORYDATE || iKey == SAM_DRAW_GROUP_HISALARMITEM
               || iKey == SAM_DRAW_GROUP_ALARMITEM)
            {
                QVector<QGraphicsItem*>pDateitem;;//保存历史数据显示器的日期文本，在时间存在的情况下
                pDateitem.clear();
                for(int i = 0 ; i < vTileTex.size(); i++)
                {
                     QString sName = vTileTex.at(i).pItem->data(GROUP_NAME_KEY).toString();
                     if(sName.contains("DateText"))
                     {
                         pDateitem.append(vTileTex.at(i).pItem);
                     }
                }
                if(pDateitem.size() == 2)
                {
                    itextW = mMoveX-TabeRect.left();
                    pnewItem = new QGroupItem(pDateitem.at(0));
                    pnewItem->SetWidth(itextW);

                    pnewItem = new QGroupItem(pDateitem.at(1));
                    itextW =  TabeRect.right()-mMoveX;
                    pnewItem->SetWidth(itextW);

                    pos.setX(mMoveX);
                    aa =  pDateitem.at(1)->mapFromScene(pos);
                    jj = pDateitem.at(1)->boundingRect().topLeft();
                    jj = pDateitem.at(1)->mapFromParent(jj);
                    pDateitem.at(1)->setX(aa.x()-jj.x());
                }
            }
            //为历史数据显示器第二行时间增加 end
        }
       else if( (HisalarmItem && alarmPro.bShowNumber) || (HisDatapItem && bHisdataNo)
           || iKey == SAM_DRAW_GROUP_RECIPESHOW || (bMessageNo && pMessageItem))//是历史数据显示器并且选择了有编号
        {
            icount = vTileTex.size();
            for(int i = 0; i< icount;i++)
            {
                 sName = vTileTex.at(i).pItem->data(GROUP_NAME_KEY).toString();
                 if(sName.contains("NoText"))//编号列表文本
                 {
                      itextW = mMoveX-TabeRect.left();
                     pnewItem = new QGroupItem(vTileTex.at(i).pItem);
                     pnewItem->SetWidth(itextW);
                 }
                 else if( sName == "Text1")//第2列标题栏
                 {
                     itextW = TabeRect.right()-mMoveX;
                     pnewItem = new QGroupItem(vTileTex.at(i).pItem);
                     pnewItem->SetWidth(itextW);

                     pos.setX(mMoveX);
                     QPointF aa =  vTileTex.at(i).pItem->mapFromScene(pos);
                     QPointF jj = vTileTex.at(i).pItem->boundingRect().topLeft();
                     jj = vTileTex.at(i).pItem->mapFromParent(jj);
                     vTileTex.at(i).pItem->setX(aa.x()-jj.x());
                 }

                 //为历史数据显示器第二行时间增加 begein
                 if(iKey == SAM_DRAW_GROUP_HISTORYDATE || iKey == SAM_DRAW_GROUP_HISALARMITEM
                    || iKey == SAM_DRAW_GROUP_ALARMITEM)
                 {
                     QVector<QGraphicsItem*>pDateitem;;//保存历史数据显示器的日期文本，在时间存在的情况下
                     pDateitem.clear();
                     for(int i = 0 ; i < vTileTex.size(); i++)
                     {
                          QString sName = vTileTex.at(i).pItem->data(GROUP_NAME_KEY).toString();
                          if(sName.contains("DateText"))
                          {
                              pDateitem.append(vTileTex.at(i).pItem);
                          }
                     }
                     if(pDateitem.size() > 0)
                     {
                         pnewItem = new QGroupItem(pDateitem.at(0));
                         itextW =  TabeRect.right()-mMoveX;
                         pnewItem->SetWidth(itextW);

                         pos.setX(mMoveX);
                         QPointF aa =  pDateitem.at(0)->mapFromScene(pos);
                         QPointF jj = pDateitem.at(0)->boundingRect().topLeft();
                         jj = pDateitem.at(0)->mapFromParent(jj);
                         pDateitem.at(0)->setX(aa.x()-jj.x());
                     }
                 }
                 //为历史数据显示器第二行时间增加 end
                 if(pRecipeItem)
                 {
                     itextW = mMoveX-TabeRect.left();
                     pnewItem = new QGroupItem(pRecipeItem);
                     pnewItem->SetWidth(itextW);
                 }
            }//end for
        }//end else if
    }

   else if(isize > 1)
    {
        if(index == 0) //第一条垂直线
        {
            if(iKey == SAM_DRAW_GROUP_ALARMITEM ||
               (HisalarmItem && false == alarmPro.bShowNumber) || (HisDatapItem && false == bHisdataNo )
               || (false == bMessageNo && pMessageItem)) //报警显示器/历史报警显示器
            {
                itextW = mMoveX-TabeRect.left();
                pnewItem = new QGroupItem(vTileTex.at(0).pItem);
                pnewItem->SetWidth(itextW);

                pnewItem = new QGroupItem(vTileTex.at(1).pItem);
                itextW =  vVLine.at(1).pos.x()-mMoveX;
                pnewItem->SetWidth(itextW);

                pos.setX(mMoveX);
                QPointF aa =  vTileTex.at(1).pItem->mapFromScene(pos);
                QPointF jj = vTileTex.at(1).pItem->boundingRect().topLeft();
                jj = vTileTex.at(1).pItem->mapFromParent(jj);
                vTileTex.at(1).pItem->setX(aa.x()-jj.x());

                //为历史数据显示器第二行时间增加 begein
                if(iKey == SAM_DRAW_GROUP_HISTORYDATE || iKey == SAM_DRAW_GROUP_HISALARMITEM
                   || iKey == SAM_DRAW_GROUP_ALARMITEM)
                {
                    QVector<QGraphicsItem*>pDateitem;;//保存历史数据显示器的日期文本，在时间存在的情况下
                    pDateitem.clear();
                    for(int i = 0 ; i < vTileTex.size(); i++)
                    {
                         QString sName = vTileTex.at(i).pItem->data(GROUP_NAME_KEY).toString();
                         if(sName.contains("DateText"))
                         {
                             pDateitem.append(vTileTex.at(i).pItem);
                         }
                    }
                    if(pDateitem.size() < 2)
                    {
                        return;
                    }
                    itextW = mMoveX-TabeRect.left();
                    pnewItem = new QGroupItem(pDateitem.at(0));
                    pnewItem->SetWidth(itextW);

                    pnewItem = new QGroupItem(pDateitem.at(1));
                    itextW =  vVLine.at(1).pos.x()-mMoveX;
                    pnewItem->SetWidth(itextW);

                    pos.setX(mMoveX);
                    aa =  pDateitem.at(1)->mapFromScene(pos);
                    jj = pDateitem.at(1)->boundingRect().topLeft();
                    jj = pDateitem.at(1)->mapFromParent(jj);
                    pDateitem.at(1)->setX(aa.x()-jj.x());
                }
                //为历史数据显示器第二行时间增加 end
            }
           else if( (HisalarmItem&& alarmPro.bShowNumber) || (HisDatapItem && bHisdataNo)
               || iKey == SAM_DRAW_GROUP_RECIPESHOW || (bMessageNo && pMessageItem))//是历史数据显示器并且选择了有编号
            {
                icount = vTileTex.size();
                for(int i = 0; i< icount;i++)
                {
                     sName = vTileTex.at(i).pItem->data(GROUP_NAME_KEY).toString();
                     if(sName.contains("NoText"))//编号列表文本
                     {
                          itextW = mMoveX-TabeRect.left();
                         pnewItem = new QGroupItem(vTileTex.at(i).pItem);
                         pnewItem->SetWidth(itextW);
                     }
                     else if( sName == "Text1" || sName == "DateText1")//第2列标题栏 || 历史数据显示器加入的时间显示，第二行第二列
                     {
                         itextW = vVLine.at(1).pos.x()-mMoveX;
                         pnewItem = new QGroupItem(vTileTex.at(i).pItem);
                         pnewItem->SetWidth(itextW);

                         pos.setX(mMoveX);
                         QPointF aa =  vTileTex.at(i).pItem->mapFromScene(pos);
                         QPointF jj = vTileTex.at(i).pItem->boundingRect().topLeft();
                         jj = vTileTex.at(i).pItem->mapFromParent(jj);
                         vTileTex.at(i).pItem->setX(aa.x()-jj.x());
                     }
                     if(pRecipeItem)
                     {
                         itextW = mMoveX-TabeRect.left();
                         pnewItem = new QGroupItem(pRecipeItem);
                         pnewItem->SetWidth(itextW);
                     }
                }//end for
            }//end else if
        }
        else if(index == isize-1) //最后一条垂直线
        {
            if(iKey == SAM_DRAW_GROUP_ALARMITEM || iKey == SAM_DRAW_GROUP_HISALARMITEM
               || iKey == SAM_DRAW_GROUP_HISTORYDATE || iKey == SAM_DRAW_GROUP_RECIPESHOW || iKey == SAM_DRAW_GROUP_TEXTBOARD) //报警显示器
            {
                QVector<QGraphicsItem*>listitem;
                listitem.clear();
                //为历史数据显示器第二行时间增加 begein
                QVector<QGraphicsItem*>pDateitem;;//保存历史数据显示器的日期文本，在时间存在的情况下
                pDateitem.clear();
                //为历史数据显示器第二行时间增加 end
//                if(iKey == SAM_DRAW_GROUP_ALARMITEM)
//                {
//                    for(int i = 0 ; i < vTileTex.size(); i++)
//                        listitem.append(vTileTex.at(i).pItem);
//                }
                if(iKey == SAM_DRAW_GROUP_HISALARMITEM || iKey == SAM_DRAW_GROUP_HISTORYDATE
                        || iKey == SAM_DRAW_GROUP_RECIPESHOW  || iKey == SAM_DRAW_GROUP_TEXTBOARD
                        || iKey == SAM_DRAW_GROUP_ALARMITEM)
                {
                    for(int i = 0 ; i < vTileTex.size(); i++)
                    {
                         sName = vTileTex.at(i).pItem->data(GROUP_NAME_KEY).toString();
                         if( sName.left(4) ==("Text"))
                               listitem.append(vTileTex.at(i).pItem);
                         //为历史数据显示器第二行时间增加 begein
                         if(sName.contains("DateText"))
                         {
                             pDateitem.append(vTileTex.at(i).pItem);
                         }
                         //为历史数据显示器第二行时间增加 end
                    }
                }
                //为历史数据显示器第二行时间增加 begein
                if(iKey == SAM_DRAW_GROUP_HISTORYDATE || iKey == SAM_DRAW_GROUP_HISALARMITEM
                   || iKey == SAM_DRAW_GROUP_ALARMITEM)
                {
                    itextW = TabeRect.right() - mMoveX;
                    pnewItem = new QGroupItem(pDateitem.last());
                    pnewItem->SetWidth(itextW);

                    pos.setX(mMoveX);
                    QPointF aa =  pDateitem.last()->mapFromScene(pos);
                    QPointF jj = pDateitem.last()->boundingRect().topLeft();
                    jj = pDateitem.last()->mapFromParent(jj);
                    pDateitem.last()->setX(aa.x()-jj.x());

                    pnewItem = new QGroupItem(pDateitem.at(pDateitem.size()-2));
                    itextW = mMoveX - vVLine.at(vVLine.size()-2).pos.x();
                    pnewItem->SetWidth(itextW);
                }
                //为历史数据显示器第二行时间增加 end
                itextW = TabeRect.right() - mMoveX;
                pnewItem = new QGroupItem(listitem.last());
                pnewItem->SetWidth(itextW);

                pos.setX(mMoveX);
                QPointF aa =  listitem.last()->mapFromScene(pos);
                QPointF jj = listitem.last()->boundingRect().topLeft();
                jj = listitem.last()->mapFromParent(jj);
                listitem.last()->setX(aa.x()-jj.x());

                pnewItem = new QGroupItem(listitem.at(listitem.size()-2));
                itextW = mMoveX - vVLine.at(vVLine.size()-2).pos.x();
                pnewItem->SetWidth(itextW);
            }
        }
        else
        {
            int val = index;
            if(iKey == SAM_DRAW_GROUP_ALARMITEM || iKey == SAM_DRAW_GROUP_HISALARMITEM || iKey == SAM_DRAW_GROUP_HISTORYDATE
               || iKey == SAM_DRAW_GROUP_RECIPESHOW || iKey == SAM_DRAW_GROUP_TEXTBOARD) //报警显示器
            {
                QVector<QGraphicsItem*>listitem;
                //为历史数据显示器第二行时间增加 begein
                QVector<QGraphicsItem*>pDateitem;;//保存历史数据显示器的日期文本，在时间存在的情况下
                pDateitem.clear();
                //为历史数据显示器第二行时间增加 end
                listitem.clear();
//                if(iKey == SAM_DRAW_GROUP_ALARMITEM)
//                {
//                    for(int i = 0 ; i < vTileTex.size(); i++)
//                        listitem.append(vTileTex.at(i).pItem);
//                }
                if(iKey == SAM_DRAW_GROUP_HISALARMITEM  || iKey == SAM_DRAW_GROUP_HISTORYDATE
                        || iKey == SAM_DRAW_GROUP_RECIPESHOW || iKey == SAM_DRAW_GROUP_TEXTBOARD
                        || iKey == SAM_DRAW_GROUP_ALARMITEM)
                {
                    for(int i = 0 ; i < vTileTex.size(); i++)
                    {
                         sName = vTileTex.at(i).pItem->data(GROUP_NAME_KEY).toString();
                         if( sName.left(4) ==("Text"))
                               listitem.append(vTileTex.at(i).pItem);
                         //为历史数据显示器第二行时间增加 begein
                         if(sName.contains("DateText"))
                         {
                             pDateitem.append(vTileTex.at(i).pItem);
                         }
                         //为历史数据显示器第二行时间增加 end
                    }
                    if( HisalarmItem && alarmPro.bShowNumber)
                        val--;
                    if(bHisdataNo && iKey == SAM_DRAW_GROUP_HISTORYDATE)
                    {
                        val--;
                    }
                    if(bMessageNo && iKey == SAM_DRAW_GROUP_TEXTBOARD)
                    {
                        val--;
                    }
                    if(iKey == SAM_DRAW_GROUP_RECIPESHOW )
                        val--;
                }

                //为历史数据显示器第二行时间增加 begin
                if(iKey == SAM_DRAW_GROUP_HISTORYDATE || iKey == SAM_DRAW_GROUP_HISALARMITEM
                   || iKey == SAM_DRAW_GROUP_ALARMITEM)
                {
                    pnewItem = new QGroupItem(pDateitem.at(val));
                    itextW = mMoveX - vVLine.at(index-1).pos.x();
                    pnewItem->SetWidth(itextW);

                    pnewItem = new QGroupItem(pDateitem.at(val+1));
                    itextW = vVLine.at(index+1).pos.x() - mMoveX;
                    pnewItem->SetWidth(itextW);

                    pos.setX(mMoveX);
                    QPointF aa =  pDateitem.at(val+1)->mapFromScene(pos);
                    QPointF jj = pDateitem.at(val+1)->boundingRect().topLeft();
                    jj = pDateitem.at(val+1)->mapFromParent(jj);
                    pDateitem.at(val+1)->setX(aa.x()-jj.x());
                }
                //为历史数据显示器第二行时间增加 end
                pnewItem = new QGroupItem(listitem.at(val));
                itextW = mMoveX - vVLine.at(index-1).pos.x();
                pnewItem->SetWidth(itextW);

                pnewItem = new QGroupItem(listitem.at(val+1));
                itextW = vVLine.at(index+1).pos.x() - mMoveX;
                pnewItem->SetWidth(itextW);

                pos.setX(mMoveX);
                QPointF aa =  listitem.at(val+1)->mapFromScene(pos);
                QPointF jj = listitem.at(val+1)->boundingRect().topLeft();
                jj = listitem.at(val+1)->mapFromParent(jj);
                listitem.at(val+1)->setX(aa.x()-jj.x());
            }
        }
    }
}

/***************************************************************
 *函数名称：setTextPosHWhenMouseMove
 *函数功能：鼠标按下时，处理水平线的拖拉
 *参数含义：
 *mMoveY:    Y方向鼠标移动的距离
 *index：       水平线在vHLine容器的下标，即第几条水平线
 *isize:           水平线的数目，即vHLine容器大小
 *返回值:       NULL
 *编辑作者：郑启红
 *编辑日期：2012.9.24
 *更改时间：2012.9.25
 **************************************************************/
void SamDrawScene::setTextPosHWhenMouseMove(qreal mMoveY, int index, int isize)
{
    qreal  itextW = 0;
    QPointF pos;
    QGroupItem *pnewItem = NULL;
    QItemGroup *itemGroup = dynamic_cast<QItemGroup *>(pTableItam);
    int iKey  = 0;
    HisAlarmItem *HisalarmItem = NULL;
    stAlarmItemPro alarmPro;
    QString sName = "";
    QHistoryDataShowAttr *HisDatapItem = NULL;
    qMessageBoradAttr *pMessageItem = NULL;
    bool bHisdataNo = false;
    bool bIsRecipe = false;
    bool bMessageNo = false;

    //为历史数据显示器第二行时间增加 begein
    QVector<QGraphicsItem*>pDateitem;;//保存历史数据显示器的日期文本，在时间存在的情况下
    pDateitem.clear();
    //为历史数据显示器第二行时间增加 end

    if(itemGroup)
    {
        iKey = itemGroup->GroupType();
        if(iKey == SAM_DRAW_GROUP_HISALARMITEM)
        {
            HisalarmItem = dynamic_cast<HisAlarmItem *> (pTableItam);
            if (HisalarmItem)
            {
                alarmPro = HisalarmItem->alarmPro;
            }
        }
        else if(iKey == SAM_DRAW_GROUP_HISTORYDATE)//历史数据显示器
        {
            HisDatapItem = dynamic_cast<QHistoryDataShowAttr *> (pTableItam);
            if (HisDatapItem)
            {
                bHisdataNo = HisDatapItem->m_bShowCode;
            }
        }
        else if(iKey == SAM_DRAW_GROUP_TEXTBOARD)//留言本
        {
            pMessageItem = dynamic_cast<qMessageBoradAttr *> (pTableItam);
            if (pMessageItem)
            {
                bMessageNo = pMessageItem->m_bShowId;
            }
        }
        else if(iKey == SAM_DRAW_GROUP_RECIPESHOW)
        {
            bIsRecipe = true;
        }
    }

    QVector<QGraphicsItem*>listitem;
    listitem.clear();
    QVector<QGraphicsItem*>nolistitem;
    nolistitem.clear();
//    if(iKey == SAM_DRAW_GROUP_ALARMITEM)
//    {
//        for(int i = 0 ; i < vTileTex.size(); i++)
//            listitem.append(vTileTex.at(i).pItem);
//    }
    if(iKey == SAM_DRAW_GROUP_HISALARMITEM  || iKey == SAM_DRAW_GROUP_HISTORYDATE
            || iKey == SAM_DRAW_GROUP_RECIPESHOW  || iKey == SAM_DRAW_GROUP_TEXTBOARD
            || iKey == SAM_DRAW_GROUP_ALARMITEM)
    {
        for(int i = 0 ; i < vTileTex.size(); i++)
        {
             sName = vTileTex.at(i).pItem->data(GROUP_NAME_KEY).toString();
             if( sName.left(4) ==("Text"))
                   listitem.append(vTileTex.at(i).pItem);
             else if(sName.contains("NoText"))
             {
                 nolistitem.append(vTileTex.at(i).pItem);
             }
             //为历史数据显示器第二行时间增加 begein
             else if(sName.contains("DateText"))
             {
                 pDateitem.append(vTileTex.at(i).pItem);
             }
             //为历史数据显示器第二行时间增加 end
        }
    }

    if(isize == 1)
    {
        if(iKey == SAM_DRAW_GROUP_ALARMITEM || iKey == SAM_DRAW_GROUP_HISALARMITEM || iKey == SAM_DRAW_GROUP_HISTORYDATE
           || iKey == SAM_DRAW_GROUP_RECIPESHOW || iKey == SAM_DRAW_GROUP_TEXTBOARD) //报警显示器/历史报警显示器、历史数据显示器
        {
            itextW = mMoveY-TabeRect.top();
            for(int i = 0; i < listitem.size();i++)
            {
                pnewItem = new QGroupItem(listitem.at(i));
                pnewItem->SetHeigth(itextW);
            }
            if(pBackItam)
            {
                pnewItem = new QGroupItem(pBackItam);
                pnewItem->SetHeigth(itextW);
            }
            if((HisalarmItem &&alarmPro.bShowNumber) || (HisDatapItem && bHisdataNo)
                || bIsRecipe || (bMessageNo && pMessageItem))
            {
                int ival = 0;
                if(bIsRecipe)
                {
                    pnewItem = new QGroupItem(nolistitem.at(ival));
                    itextW = mMoveY - TabeRect.top();
                    pnewItem->SetHeigth(itextW);
                    ival = 1;

                    if(pRecipeItem)
                    {
                        pnewItem = new QGroupItem(pRecipeItem);
                        itextW = TabeRect.bottom() - mMoveY;
                        pnewItem->SetHeigth(itextW);

                        pos.setY(mMoveY);
                        QPointF aa =  pRecipeItem->mapFromScene(pos);
                        QPointF jj = pRecipeItem->boundingRect().topLeft();
                        jj = pRecipeItem->mapFromParent(jj);
                        pRecipeItem->setY(aa.y()-jj.y());
                    }
                }
                //为历史数据显示器第二行时间增加 begin

                else if(iKey == SAM_DRAW_GROUP_HISTORYDATE || iKey == SAM_DRAW_GROUP_HISALARMITEM
                        || iKey == SAM_DRAW_GROUP_ALARMITEM || iKey == SAM_DRAW_GROUP_TEXTBOARD)
                {
                    pnewItem = new QGroupItem(nolistitem.at(ival));
                    itextW = mMoveY - TabeRect.top();
                    pnewItem->SetHeigth(itextW);
                    ival = 1;
                }
                //为历史数据显示器第二行时间增加 end

                pnewItem = new QGroupItem(nolistitem.at(ival));
                itextW = TabeRect.bottom() - mMoveY;
                pnewItem->SetHeigth(itextW);

                pos.setY(mMoveY);
                QPointF aa =  nolistitem.at(ival)->mapFromScene(pos);
                QPointF jj = nolistitem.at(ival)->boundingRect().topLeft();
                jj = nolistitem.at(ival)->mapFromParent(jj);
                nolistitem.at(ival)->setY(aa.y()-jj.y());
                //为历史数据显示器第二行时间增加 begin
                if(iKey == SAM_DRAW_GROUP_HISTORYDATE || iKey == SAM_DRAW_GROUP_HISALARMITEM
                   || iKey == SAM_DRAW_GROUP_ALARMITEM)
                {
                    int ival = 0;
                    if((HisalarmItem &&alarmPro.bShowNumber) || (HisDatapItem && bHisdataNo))//显示编号
                    {
                        if(nolistitem.size() != 2)
                        {
                            return;
                        }
                        pnewItem = new QGroupItem(nolistitem.at(ival));
                        itextW = mMoveY - TabeRect.top();
                        pnewItem->SetHeigth(itextW);
                        ival = 1;

                        pnewItem = new QGroupItem(nolistitem.at(ival));
                        itextW =  TabeRect.bottom() - mMoveY;
                        pnewItem->SetHeigth(itextW);
                        pos.setY(mMoveY);
                        QPointF aa =  nolistitem.at(ival)->mapFromScene(pos);
                        QPointF jj = nolistitem.at(ival)->boundingRect().topLeft();
                        jj = nolistitem.at(ival)->mapFromParent(jj);
                        nolistitem.at(ival)->setY(aa.y()-jj.y());
                    }

                    for(int i = 0 ; i < vTileTex.size(); i++)
                    {
                         QString sName = vTileTex.at(i).pItem->data(GROUP_NAME_KEY).toString();
                         if(sName.contains("DateText"))
                         {
                             pDateitem.append(vTileTex.at(i).pItem);
                         }
                    }

                    for(int i = 0; i < pDateitem.size(); i++)
                    {
                        pnewItem = new QGroupItem(pDateitem.at(i));
                        itextW = TabeRect.bottom() - mMoveY;
                        pnewItem->SetHeigth(itextW);

                        pos.setY(mMoveY);
                        QPointF aa =  pDateitem.at(i)->mapFromScene(pos);
                        QPointF jj = pDateitem.at(i)->boundingRect().topLeft();
                        jj = pDateitem.at(i)->mapFromParent(jj);
                        pDateitem.at(i)->setY(aa.y()-jj.y());
                    }
                }
                //为历史数据显示器第二行时间增加 end
            }
            else if((HisalarmItem && false == alarmPro.bShowNumber) || (HisDatapItem && false == bHisdataNo))
            {
                pDateitem.clear();
                for(int i = 0 ; i < vTileTex.size(); i++)
                {
                     QString sName = vTileTex.at(i).pItem->data(GROUP_NAME_KEY).toString();
                     if(sName.contains("DateText"))
                     {
                         pDateitem.append(vTileTex.at(i).pItem);
                     }
                }

                for(int i = 0; i < pDateitem.size(); i++)
                {
                    pnewItem = new QGroupItem(pDateitem.at(i));
                    itextW = TabeRect.bottom() - mMoveY;
                    pnewItem->SetHeigth(itextW);

                    pos.setY(mMoveY);
                    QPointF aa =  pDateitem.at(i)->mapFromScene(pos);
                    QPointF jj = pDateitem.at(i)->boundingRect().topLeft();
                    jj = pDateitem.at(i)->mapFromParent(jj);
                    pDateitem.at(i)->setY(aa.y()-jj.y());
                }
            }
        }
    }
    else if(isize > 1)
    {
        if(index == 0)//第一条
        {
            if(iKey == SAM_DRAW_GROUP_ALARMITEM || iKey == SAM_DRAW_GROUP_HISALARMITEM || iKey == SAM_DRAW_GROUP_HISTORYDATE
               || iKey == SAM_DRAW_GROUP_RECIPESHOW || iKey == SAM_DRAW_GROUP_TEXTBOARD) //报警显示器
            {
                itextW = mMoveY-TabeRect.top();
                for(int i = 0; i < listitem.size();i++)
                {
                    pnewItem = new QGroupItem(listitem.at(i));//vTileTex.at(i).pItem);
                    pnewItem->SetHeigth(itextW);
                }
                if(pBackItam)
                {
                    pnewItem = new QGroupItem(pBackItam);
                    pnewItem->SetHeigth(itextW);
                }
                if((HisalarmItem &&alarmPro.bShowNumber) || (HisDatapItem && bHisdataNo)
                    || bIsRecipe || (bMessageNo && pMessageItem))
                {
                    int ival = 0;
                    if(bIsRecipe)
                    {
                        pnewItem = new QGroupItem(nolistitem.at(ival));
                        itextW = mMoveY - TabeRect.top();
                        pnewItem->SetHeigth(itextW);
                        ival = 1;
                        if(pRecipeItem)
                        {
                            pnewItem = new QGroupItem(pRecipeItem);
                            itextW = TabeRect.bottom() - mMoveY;
                            pnewItem->SetHeigth(itextW);

                            pos.setY(mMoveY);
                            QPointF aa =  pRecipeItem->mapFromScene(pos);
                            QPointF jj = pRecipeItem->boundingRect().topLeft();
                            jj = pRecipeItem->mapFromParent(jj);
                            pRecipeItem->setY(aa.y()-jj.y());
                        }
                    }
                    //为历史数据显示器第二行时间增加 begin
                    else if(iKey == SAM_DRAW_GROUP_HISTORYDATE || iKey == SAM_DRAW_GROUP_HISALARMITEM
                            || iKey == SAM_DRAW_GROUP_ALARMITEM)
                    {
                        pnewItem = new QGroupItem(nolistitem.at(ival));
                        itextW = mMoveY - TabeRect.top();
                        pnewItem->SetHeigth(itextW);
                        ival = 1;
                    }
                    //为历史数据显示器第二行时间增加 end
                    else if(iKey == SAM_DRAW_GROUP_TEXTBOARD)
                    {
                        pnewItem = new QGroupItem(nolistitem.at(ival));
                        itextW = mMoveY - TabeRect.top();
                        pnewItem->SetHeigth(itextW);
                        ival = 1;
                    }
                    pnewItem = new QGroupItem(nolistitem.at(ival));
                    itextW = vHLine.at(1).pos.y() - mMoveY;
                    pnewItem->SetHeigth(itextW);

                    pos.setY(mMoveY);
                    QPointF aa =  nolistitem.at(ival)->mapFromScene(pos);
                    QPointF jj = nolistitem.at(ival)->boundingRect().topLeft();
                    jj = nolistitem.at(ival)->mapFromParent(jj);
                    nolistitem.at(ival)->setY(aa.y()-jj.y());
                }
                //为历史数据显示器第二行时间增加 begin
                if(iKey == SAM_DRAW_GROUP_HISTORYDATE || iKey == SAM_DRAW_GROUP_HISALARMITEM
                   || iKey == SAM_DRAW_GROUP_ALARMITEM)
                {
                    for(int i = 0; i < pDateitem.size(); i++)
                    {
                        pnewItem = new QGroupItem(pDateitem.at(i));
                        itextW = vHLine.at(1).pos.y() - mMoveY;
                        pnewItem->SetHeigth(itextW);

                        pos.setY(mMoveY);
                        QPointF aa =  pDateitem.at(i)->mapFromScene(pos);
                        QPointF jj = pDateitem.at(i)->boundingRect().topLeft();
                        jj = pDateitem.at(i)->mapFromParent(jj);
                        pDateitem.at(i)->setY(aa.y()-jj.y());
                    }
                }
                //为历史数据显示器第二行时间增加 end
            }
        }
        else if(index == isize-1)//最后一条
         {
            if((HisalarmItem &&alarmPro.bShowNumber) || (HisDatapItem && bHisdataNo)
                || bIsRecipe || (bMessageNo && pMessageItem))
            {
                pnewItem = new QGroupItem(nolistitem.at(nolistitem.size()-2));
                itextW = mMoveY - vHLine.at(index-1).pos.y();
                pnewItem->SetHeigth(itextW);

                pnewItem = new QGroupItem(nolistitem.last());
                itextW = TabeRect.bottom()- mMoveY;
                pnewItem->SetHeigth(itextW);

                pos.setY(mMoveY);
                QPointF aa =  nolistitem.last()->mapFromScene(pos);
                QPointF jj = nolistitem.last()->boundingRect().topLeft();
                jj = nolistitem.last()->mapFromParent(jj);
                nolistitem.last()->setY(aa.y()-jj.y());

                //为历史数据显示器第二行时间增加 begin
                if((iKey == SAM_DRAW_GROUP_HISTORYDATE && isize == 2) || (iKey == SAM_DRAW_GROUP_HISALARMITEM && isize == 2)
                    || (iKey == SAM_DRAW_GROUP_ALARMITEM && isize == 2))
                {
                    for(int i = 0; i < pDateitem.size(); i++)
                    {
                        pnewItem = new QGroupItem(pDateitem.at(i));
                        itextW = TabeRect.bottom() - mMoveY;
                        pnewItem->SetHeigth(itextW);
                    }
                }
                //为历史数据显示器第二行时间增加 end
            }
         }
         else
        {
             if((HisalarmItem &&alarmPro.bShowNumber) || (HisDatapItem && bHisdataNo)
                 || bIsRecipe || (bMessageNo && pMessageItem))
             {
                 if((HisalarmItem &&alarmPro.bShowNumber))
                 {
                     //nolistitem.insert(0,listitem.at(0));
                 }
                 pnewItem = new QGroupItem(nolistitem.at(index));
                 itextW = mMoveY - vHLine.at(index - 1).pos.y();
                 pnewItem->SetHeigth(itextW);

                 pnewItem = new QGroupItem(nolistitem.at(index + 1));
                 itextW = vHLine.at(index + 1).pos.y()- mMoveY;
                 pnewItem->SetHeigth(itextW);

                 pos.setY(mMoveY);
                 QPointF aa =  nolistitem.at(index + 1)->mapFromScene(pos);
                 QPointF jj = nolistitem.at(index + 1)->boundingRect().topLeft();
                 jj = nolistitem.at(index + 1)->mapFromParent(jj);
                 nolistitem.at(index + 1)->setY(aa.y()-jj.y());
             }
             //为历史数据显示器第二行时间增加 begin
             qDebug()<<"index \==="<<index;
             if((iKey == SAM_DRAW_GROUP_HISTORYDATE && index == 1) || (iKey == SAM_DRAW_GROUP_HISALARMITEM && index == 1)
                 || (iKey == SAM_DRAW_GROUP_ALARMITEM && index == 1))
             {
                 for(int i = 0; i < pDateitem.size(); i++)
                 {
                     pnewItem = new QGroupItem(pDateitem.at(i));
                     itextW = mMoveY - vHLine.at(0).pos.y();
                     pnewItem->SetHeigth(itextW);
                 }
             }
             //为历史数据显示器第二行时间增加 end
         }
        }
}

void SamDrawScene::DrawScreenSize()
{
    int Width = 320;
    int nHight = 230;
    QString sModel = pwnd->newpro->newprowizard_model;//SA型号例如：SA--10.4A (800*600 10.4')
    if(sModel.contains("043") || sModel.contains("050") || sModel.contains("035"))
    {
        Width = 260;
        nHight = 180;
    }
    else if(sModel.contains("070") ||sModel.contains("102"))
    {
        Width = 320;
        nHight = 230;
    }
    else
    {
        return;
    }

    qreal qPointx = 0; //左坐标
    qreal qPointy = 0; //右坐标
    qreal qVal = 0; //临时变量
    QGraphicsItem *item;

    int nSceneWidth = this->width();   //宽度
    int nSceneHeight = this->height(); //高度

    double iScalex;//X方向的缩放比例
    double iScaley;//Y方向的缩放比例

    //计算水平模式下的缩放比例
    iScalex=(double)nSceneWidth/Width;//X方向的缩放比例
    iScaley=(double)nSceneHeight/nHight;//Y方向的缩放比例

    QList <QGraphicsItem *> selList;
    QGroupItem * group;
    selList=this->TopItems();
    foreach(QGraphicsItem *pitem,selList)
        pitem->setSelected(false);
    for(int i = 0; i <selList.size(); i++)  //根据缩放比例重新调整控件的位置和大小
    {
        item = selList.at(i);
        qPointx=item->boundingRect().left()+item->scenePos().x();//得到当前X坐标
        qPointx=qPointx/iScalex;//除缩放比例，得到新的位置
        qVal = qPointx - item->boundingRect().x();
        selList.at(i)->setX(qVal);

        qPointy=item->boundingRect().top()+item->scenePos().y();//得到当前y坐标
        qPointy=qPointy/iScaley;//除缩放比例，得到新的位置
        qVal = qPointy - item->boundingRect().y();
        selList.at(i)->setY(qVal);
        foreach(QGraphicsItem *pItem,selList.at(i)->childItems())
        {
            if (pItem->type() == SAM_DRAW_OBJECT_PIXMAP)
            {
                QPixmapItem *pTmp = NULL;
                pTmp = dynamic_cast<QPixmapItem *> (pItem);
                pTmp->boundRect = pTmp->sceneBoundingRect();
            }

        }
        group=new QGroupItem(selList.at(i));
        group->SetWidth(item->sceneBoundingRect().width()/iScalex);
        group->SetHeigth(item->sceneBoundingRect().height()/iScaley);
    }
    this->setSceneRect(0,0,Width,nHight);
    this->reBondingTrackers();
}

void SamDrawScene::load (QDataStream &stream, SamDrawScene *pScene)
{
    //recover scene background style
    stream >> pScene->m_sceneRect >> pScene->m_sceneBackColor;
    stream >> pScene->m_sceneStyleColor >> pScene->nSelectType;
    stream >> pScene->nPattern >> pScene->m_picturePath;
    pScene->setSceneRect(pScene->m_sceneRect.x(),pScene->m_sceneRect.y(),
                         pScene->m_sceneRect.width(),pScene->m_sceneRect.height());

    stream >> pScene->bShowMiddle;
    if(pwnd->getProVersion() < 2681)
    {
        pScene->bshowTitle = false;
    }
    else
    {
        stream >> pScene->bshowTitle;
    }
    //s0tream >> pScene->bShowOtherPos;
    //stream >> pScene->bUseCloseBtn;
    //stream >> pScene->bUseTitleStr;
    stream >> pScene->mWindownShowPos;
    stream >> pScene->nIsSceneOrWindow;
    stream >> pScene->sNewScreenName;
    stream >> pScene->sNumberName;
    //qDebug()<<"version ---"<<pwnd->getProVersion();
    if(pwnd->getProVersion() < 2054)
    {
        pScene->bLogout = false;

    }
    else
    {
        stream >> pScene->bLogout;
    }
    //脚本
    int scriptSize=0;
    stream >> scriptSize;
    for(int i=0;i<scriptSize;i++){
        SCRIPT_PROP scipt;
        stream >> scipt.scriptAddr;
        stream >> scipt.scriptBShow;
        stream >> scipt.scriptCondition;
        stream >> scipt.scriptFreq;
        if(pwnd->getProVersion() < 2052)
        {
            scipt.scriptCount = 0;
        }
        else
        {
            stream >> scipt.scriptCount;
        }

        stream >> scipt.scriptFuncName;
        stream >> scipt.scriptName;
        stream >> scipt.scriptType;
        pScene->listScript.append(scipt);
    }
    //画面属性
    stream >> pScene->bIsAddMenu;
    stream >> pScene->bSlide;
    stream >> pScene->nTowardLeftId;
    stream >> pScene->nTowardRIghtId;
    stream >> pScene->nSlideStyle;
    //stream >> pScene->sTitleStr;
    //end recover scene background style
    int sceneItemsize = 0;
    stream >> sceneItemsize;

    while(sceneItemsize > 0 && !stream.atEnd())
    {
        sceneItemsize-- ;
        int type = -1;//item加锁保存打开后重新加锁
        bool bIsMoved = true;
        stream >> bIsMoved;
        stream >> type;

        switch(type)
        {
            case SAM_DRAW_OBJECT_RECT:              //15
            {
                QRectItem *rectItem = new QRectItem();
                stream >> rectItem;
                qreal zValue;
                stream >> zValue;
                rectItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                rectItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(rectItem,zValue);
                rectItem->refreshLockRect(rectItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //rectItem->setZValue(zValue);
            }
            break;
            case SAM_DRAW_OBJECT_ELIPSE:              //16
            {
                QElipseItem *elipseItem = new QElipseItem();
                stream >> elipseItem;
                qreal zValue;
                stream >> zValue;
                elipseItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                elipseItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(elipseItem,zValue);
                elipseItem->refreshLockRect(elipseItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //elipseItem->setZValue(zValue);
            }
            break;
            case SAM_DRAW_OBJECT_LINE:                 //17
            {
                QLineItem *lineItem = new QLineItem();
                stream >> lineItem;
                qreal zValue;
                stream >> zValue;
                lineItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                lineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(lineItem,zValue);
                lineItem->refreshLockRect(lineItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //lineItem->setZValue(zValue);
            }
            break;
            case SAM_DRAW_OBJECT_POLYGON:              //18
            {
                QPolygonItem *polygonItem = new QPolygonItem();
                stream >> polygonItem;
                qreal zValue;
                stream >> zValue;
                polygonItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                polygonItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(polygonItem,zValue);
                polygonItem->refreshLockRect(polygonItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //polygonItem->setZValue(zValue);
            }
            break;
            case SAM_DRAW_OBJECT_FOLDLINE:             //19
            {
                QFoldLineItem *foldLineItem = new QFoldLineItem();
                stream >> foldLineItem;
                qreal zValue;
                stream >> zValue;
                foldLineItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                foldLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(foldLineItem,zValue);
                foldLineItem->refreshLockRect(foldLineItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //foldLineItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_OBJECT_FREELINE:             //20
            {
                QFreeLineItem *freeLineItem = new QFreeLineItem();
                stream >> freeLineItem;
                qreal zValue;
                stream >> zValue;
                freeLineItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                freeLineItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(freeLineItem,zValue);
                freeLineItem->refreshLockRect(freeLineItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //freeLineItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_OBJECT_TEXT:                 //22
            {
                QSimpleTextItem *textItem = new QSimpleTextItem();
                stream >> textItem;
                qreal zValue;
                stream >> zValue;
                textItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                textItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(textItem,zValue);
                textItem->refreshLockRect(textItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //textItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_OBJECT_PIXMAP:
            {
                QPixmapItem *pPixmap = new QPixmapItem();
                stream >> pPixmap;
                qreal zValue;
                stream >> zValue;
                pPixmap->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                pPixmap->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(pPixmap,zValue);
                //pPixmap->setZValue(zValue);
                break;
            }
            case SAM_DRAW_OBJECT_LINECIRCLE:           //25
            {
                QLineCircleItem *lineCircleItem = new QLineCircleItem();
                stream >> lineCircleItem;
                qreal zValue;
                stream >> zValue;
                lineCircleItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                lineCircleItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(lineCircleItem,zValue);
                lineCircleItem->refreshLockRect(lineCircleItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //lineCircleItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_OBJECT_ROUNDEDRECT:
            {
                QRoundedRect *pRoundItem = new QRoundedRect();
                stream >> pRoundItem;
                qreal zValue;
                stream >> zValue;
                pRoundItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                pRoundItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(pRoundItem,zValue);
                pRoundItem->refreshLockRect(pRoundItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //pRoundItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_OBJECT_ARC:
            {
                QArcItem *pArcItem = new QArcItem();
                stream >> pArcItem;
                qreal zValue;
                stream >> zValue;
                pArcItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                pArcItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(pArcItem,zValue);
                pArcItem->refreshLockRect(pArcItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //pArcItem->setZValue(zValue);
                break;
            }
                        case SAM_DRAW_OBJECT_GROUP:
            case SAM_DRAW_GROUP_USER:                //23
            {
                QItemGroup *groupItem = new QItemGroup();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->redrawForChangeStatus(groupItem->getCurrentState(),0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_KEY:
            {
                KeyBoardItem *groupItem = new KeyBoardItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->redrawForChangeStatus(0, 0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_STATICTEXT:
            {
                StaticTextItem *groupItem = new StaticTextItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_MESSAGE:
            {
                QMessageShowAttr *groupItem = new QMessageShowAttr;
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_FLOW://流动块
            {
                FlowBlockItem *groupItem = new FlowBlockItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_CALIBRATION://刻度
            {
                CalibrationItem *groupItem = new CalibrationItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_SLIDER://滑动块
            {
                SliderItem *groupItem = new SliderItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_ALARMBAR://动态报警条
            {
                AlarmBar *groupItem = new AlarmBar();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_ALARMITEM://动态报警条item
            {
                AlarmItem *groupItem = new AlarmItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_HISALARMITEM://动态报警条item
            {
                HisAlarmItem *groupItem = new HisAlarmItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_SWITCH://开关
            {
                SwitchItem *groupItem = new SwitchItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->redrawForChangeStatus(groupItem->curSta,0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_VALUE:
            case SAM_DRAW_GROUP_TIME:
            case SAM_DRAW_GROUP_ASCII:
            {
                DataDisplayItem *groupItem = new DataDisplayItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->textItem = groupItem->GetTextItem();
                groupItem->redrawForChangeStatus(groupItem->getCurrentState(),0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_RECIPE:
            {
                QRcipeItem *groupItem = new QRcipeItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_RECIPESHOW:
            {
                QRecipeTableItem *groupItem = new QRecipeTableItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_STATICPIC:
            {
                QStaticPictureItem *groupItem = new QStaticPictureItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->redrawForChangeStatus(0,0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_IMAGE:
            {
                ImageItem *groupItem = new ImageItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->redrawForChangeStatus(groupItem->getCurrentState(),0);
                //groupItem->setZValue(zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                break;
            }
            case SAM_DRAW_GROUP_ANIMATION:
            {
                AnimationItem *groupItem = new AnimationItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->redrawForChangeStatus(groupItem->getCurrentState(),0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_CHART:
            {
                ChartItem *groupItem = new ChartItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                //groupItem->setZValue(zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                break;
            }
            case SAM_DRAW_GROUP_DYNCIRCLE://动态圆
            {
                DynCircleAttr *groupItem = new DynCircleAttr();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_DYNRECT://动态矩形
            {
                DynRectAttr *groupItem = new DynRectAttr();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                //groupItem->setZValue(zValue);
                break;
            }
            case SAM_DRAW_GROUP_TREND://曲线
            {
                QTrendAttr *groupItem = new QTrendAttr();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                //groupItem->setZValue(zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                break;
            }
            case SAM_DRAW_GROUP_GROUPDATA://数据群组
            {
                QTrendDataGroupAttr *groupItem = new QTrendDataGroupAttr();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                //groupItem->setZValue(zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                break;
            }
            case SAM_DRAW_GROUP_TABLE://表格
            {
                QTableItem *groupItem = new QTableItem();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                //groupItem->setZValue(zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                break;
            }
            case SAM_DRAW_GROUP_DROPDOWN://下拉框
            {
                QDropdownAttr *groupItem = new QDropdownAttr;
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                                break;
            }

            case SAM_DRAW_GROUP_COMBOBOX://下拉框
            {
                AkComboItem *groupItem = new AkComboItem;
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                break;
            }

            case SAM_DRAW_GROUP_HISTORYDATE://历史数据显示器
            {
                QHistoryDataShowAttr *groupItem = new QHistoryDataShowAttr;
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            }
            break;
            case SAM_DRAW_GROUP_TEXTBOARD://留言板
            {
                qMessageBoradAttr *groupItem = new qMessageBoradAttr;
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            }
            break;
            case SAM_DRAW_GROUP_MFBTN://多功能按钮
            {
                MfBtnItem *groupItem = new MfBtnItem;
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                groupItem->redrawForChangeStatus(0, 0);
                pScene->addItem(groupItem,zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
            }
            break;
            case SAM_DRAW_GROUP_XYTREND://曲线
            {
                XYtrend *groupItem = new XYtrend();
                groupItem->load(stream);
                qreal zValue;
                stream >> zValue;
                groupItem->setFlag(QGraphicsItem::ItemIsMovable, bIsMoved);
                groupItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                pScene->addItem(groupItem,zValue);
                //groupItem->setZValue(zValue);
                groupItem->refreshLockRect(groupItem->sceneBoundingRect().topLeft(),pScene,!bIsMoved);
                break;
            }
            default:
            break;
        }//switch end
    }//wh
}

LibRaryScene::LibRaryScene(QObject *parent)
    : QGraphicsScene(parent)
{

}

LibRaryScene::~LibRaryScene()
{
    QList<QGraphicsItem *> itemList = this->items();
    foreach(QGraphicsItem *pItem, itemList)
    {
        this->removeItem(pItem);
        //this->deleteSamItem(pItem);
    }
}

void LibRaryScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF qpClickedPt = event->scenePos();
    QGraphicsItem *pItem;
    if(itemAt(qpClickedPt))
    {
        pItem =TopmostParentItem(itemAt(qpClickedPt)) ;
       emit DoubleClickItem(pItem);

    }
    event->setAccepted(true);
}

//返回item的最终父节点
QGraphicsItem * LibRaryScene::TopmostParentItem (QGraphicsItem * item)
{
    QGraphicsItem * parentitem = item;
    while (parentitem && parentitem->parentItem())
    {
        parentitem = parentitem->parentItem();
    }
    return parentitem;
}
