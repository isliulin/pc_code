/****************************************************************************
**
** Copyright (C) 2010 Samkoon LTD.
** All rights reserved.
** 供应商 : 显控电子有限公司
** 作者   : 王 金 亮
** 日期  : 2010. 11.01
** 功能  :撤销 恢复功能实现
****************************************************************************/

#include <QtGui>

#include "commands.h"
#include "View/samdrawscene.h"
#include "view/samdrawitembase.h"
//#include "stdafx.h"
#include "Frame\mainwindow.h"
extern MainWindow *pwnd;
#include <QMessageBox>
#if 0
//! [0]
/*========================

 MoveCommand类构造函数

函数功能:实现单个控件的移动撤销与恢复

函数参数:
  DiagramItem *diagramItem ：控件指针
  const QPointF &oldPos    :控件的
  QUndoCommand *parent :父类指针

 返回值:无
=========================*/

 MoveCommand::MoveCommand(SamDrawScene *scene,QGraphicsItem *diagramItem, const QPointF &oldPos,
                 QUndoCommand *parent)
    : QUndoCommand(parent)
{
    myDiagramItem = diagramItem;   /*保存当前移动的控件对象*/
    newPos = diagramItem->pos();   /*保存当前移动的控件对象的新位置*/
    myOldPos = oldPos;             /*保存当前移动的控件对象的原始位置*/
}

//! [0]

//! [1]

bool MoveCommand::mergeWith(const QUndoCommand *command)
{

    const MoveCommand *moveCommand = dynamic_cast<const MoveCommand *>(command);
    DiagramItem *item = moveCommand->myDiagramItem;

    if (myDiagramItem != item)
    return false;

    newPos = item->pos();
    //setText(QObject::tr("移动 %1")
    //    .arg(createCommandString(myDiagramItem, newPos)));

    return true;
}

//! [1]

//! [2]
 /*=========================
   MoveCommand::undo()

函数功能:实现移动撤销功能

参数:无

返回值:无
============================*/

void MoveCommand::undo()
{
    myDiagramItem->setPos(myOldPos);/*恢复移动前时控件坐标*/
    myDiagramItem->scene()->update();/*刷新场控件参数*/
    //setText(QObject::tr("移动 %1")   /*在命令列表打印所操作命令信息*/
        //.arg(createCommandString(myDiagramItem, newPos)));
    pwnd->pView->setScene(myDiagramItem->scene());
}
//! [2]

//! [3]
/*=========================
  MoveCommand::redo()

函数功能:实现移动恢复功能

参数:无

返回值:无
============================*/
void MoveCommand::redo()
{
    myDiagramItem->setPos(newPos);/*还原移动时控件坐标*/
    myDiagramItem->scene()->update();/*刷新场控件参数*/
    //setText(QObject::tr("移动 %1")    /*在命令列表打印所操作命令信息*/
        //.arg(createCommandString(myDiagramItem, newPos)));
    pwnd->pView->setScene(myDiagramItem->scene());
}
//! [3]
#endif
void add_edgepoints(SamDrawScene  *myGraphicsScene,QGraphicsItem * pSelItem)
{
    if(!myGraphicsScene || !pSelItem)
    {
        return ;
    }
    QRectItem *pRect     = 0;
    QElipseItem *pElipse = 0;
    QLineItem *pLine     = 0;
    QPolygonItem *pPolygon   = 0;
    QFoldLineItem *pFoldLine = 0;
    QFreeLineItem *pFreeLine = 0;
    QItemGroup *pItemGroup   = 0;
    QLineCircleItem *pLineCircle = 0;
    QSimpleTextItem *pText = 0;
    QRoundedRect *pRoundedRect = 0;
    QArcItem *pArc = 0;

    QRectBasicItem *pRectNew     = 0;
    QElipseBasicItem *pElipseNew  = 0;
    QLineBasicItem *pLineNew     = 0;
    QPolygonBasicItem *pPolygonNew    = 0;
    QFoldLineBasicItem *pFoldLineNew  = 0;
    QFreeLineBasicItem *pFreeLineNew  = 0;
    QLineCircleBasicItem *pLineCircleNew  = 0;
    QRoundedRectBasic *pRoundedRectNew  = 0;
    QArcBasicItem *pArcNew  = 0;

    switch (pSelItem->type())
    {
    case SAM_DRAW_OBJECT_RECT:
        pRect = dynamic_cast<QRectItem *> (pSelItem);
        if (pRect)
        {
            int iSize = pRect->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pRect->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_ELIPSE:
        pElipse = dynamic_cast<QElipseItem *> (pSelItem);
        if (pElipse)
        {
            int iSize = pElipse->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pElipse->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_LINE:
        pLine = dynamic_cast<QLineItem *> (pSelItem);
        if (pLine)
        {
            int iSize = pLine->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pLine->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_POLYGON:
        pPolygon = dynamic_cast<QPolygonItem *> (pSelItem);
        if (pPolygon)
        {
            int iSize = pPolygon->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pPolygon->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_FOLDLINE:
        pFoldLine = dynamic_cast<QFoldLineItem *> (pSelItem);
        if (pFoldLine)
        {
            int iSize = pFoldLine->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pFoldLine->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_FREELINE:
        pFreeLine = dynamic_cast<QFreeLineItem *> (pSelItem);
        if (pFreeLine)
        {
            int iSize = pFreeLine->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pFreeLine->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_GROUP:
        pItemGroup = dynamic_cast<QItemGroup *> (pSelItem);
        if (pItemGroup)
        {
            int iSize = pItemGroup->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pItemGroup->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE:
        pLineCircle = dynamic_cast<QLineCircleItem *> (pSelItem);
        if (pLineCircle)
        {
            int iSize = pLineCircle->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pLineCircle->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_TEXT:
        pText = dynamic_cast<QSimpleTextItem *> (pSelItem);
        if (pText)
        {
            int iSize = pText->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pText->m_pvecTrackers[i]);
            }
        }
        break;
   case SAM_DRAW_OBJECT_ROUNDEDRECT:
       pRoundedRect = dynamic_cast<QRoundedRect *> (pSelItem);
       if (pRoundedRect)
       {
           int iSize = pRoundedRect->m_pvecTrackers.size();
           for (int i = 0; i < iSize; i++)
           {
               myGraphicsScene->addItem(pRoundedRect->m_pvecTrackers[i]);
           }
       }
       break;
   case SAM_DRAW_OBJECT_ARC:
       pArc = dynamic_cast<QArcItem *> (pSelItem);
       if (pArc)
       {
           int iSize = pArc->m_pvecTrackers.size();
           for (int i = 0; i < iSize; i++)
           {
               myGraphicsScene->addItem(pArc->m_pvecTrackers[i]);
           }
       }
       break;
//////////////wxy add start
    case SAM_DRAW_OBJECT_RECT_NEW:
        pRectNew = dynamic_cast<QRectBasicItem *> (pSelItem);
        if (pRectNew)
        {
            int iSize = pRectNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pRectNew->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_ELIPSE_NEW:
        pElipseNew = dynamic_cast<QElipseBasicItem *> (pSelItem);
        if (pElipseNew)
        {
            int iSize = pElipseNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pElipseNew->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_LINE_NEW:
        pLineNew = dynamic_cast<QLineBasicItem *> (pSelItem);
        if (pLineNew)
        {
            int iSize = pLineNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pLineNew->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_POLYGON_NEW:
        pPolygonNew = dynamic_cast<QPolygonBasicItem *> (pSelItem);
        if (pPolygonNew)
        {
            int iSize = pPolygonNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pPolygonNew->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_FOLDLINE_NEW:
        pFoldLineNew = dynamic_cast<QFoldLineBasicItem *> (pSelItem);
        if (pFoldLineNew)
        {
            int iSize = pFoldLineNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pFoldLineNew->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_FREELINE_NEW:
        pFreeLineNew = dynamic_cast<QFreeLineBasicItem *> (pSelItem);
        if (pFreeLineNew)
        {
            int iSize = pFreeLineNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pFreeLineNew->m_pvecTrackers[i]);
            }
        }
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
        pLineCircleNew = dynamic_cast<QLineCircleBasicItem *> (pSelItem);
        if (pLineCircleNew)
        {
            int iSize = pLineCircleNew->m_pvecTrackers.size();
            for (int i = 0; i < iSize; i++)
            {
                myGraphicsScene->addItem(pLineCircleNew->m_pvecTrackers[i]);
            }
        }
        break;
   case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
       pRoundedRectNew = dynamic_cast<QRoundedRectBasic *> (pSelItem);
       if (pRoundedRectNew)
       {
           int iSize = pRoundedRectNew->m_pvecTrackers.size();
           for (int i = 0; i < iSize; i++)
           {
               myGraphicsScene->addItem(pRoundedRectNew->m_pvecTrackers[i]);
           }
       }
       break;
   case SAM_DRAW_OBJECT_ARC_NEW:
       pArcNew = dynamic_cast<QArcBasicItem *> (pSelItem);
       if (pArcNew)
       {
           int iSize = pArcNew->m_pvecTrackers.size();
           for (int i = 0; i < iSize; i++)
           {
               myGraphicsScene->addItem(pArcNew->m_pvecTrackers[i]);
           }
       }
       break;
/////////////wxy add end
    default:
       break;
   }
}
//! [4]
/*=========================
  DeleteCommand()构造函数

  函数功能:实现控件删除撤销，恢复功能

  参数:
  QGraphicsScene*scene:控件所属的场景
  QUndoCommand *parent:命令发起的父类对象指针

  返回值:无
============================*/
DeleteCommand::DeleteCommand(SamDrawScene *scene, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    if(!scene )
    {
        return ;
    }

    myGraphicsScene = scene;   /*保存删除操作是的场景*/
    QRectItem *pRect     = 0;
    QElipseItem *pElipse = 0;
    QLineItem *pLine     = 0;
    QPolygonItem *pPolygon   = 0;
    QFoldLineItem *pFoldLine = 0;
    QFreeLineItem *pFreeLine = 0;
    QItemGroup *pItemGroup   = 0;
    QLineCircleItem *pLineCircle = 0;
    QSimpleTextItem *pText = 0;
    QGraphicsItem *pSelItem = 0;
    QRoundedRect *pRoundedRect = 0;
    QArcItem *pArc = 0;

    QRectBasicItem *pRectNew     = 0;
    QElipseBasicItem *pElipseNew = 0;
    QLineBasicItem *pLineNew     = 0;
    QPolygonBasicItem *pPolygonNew   = 0;
    QFoldLineBasicItem *pFoldLineNew = 0;
    QFreeLineBasicItem *pFreeLineNew = 0;
    QLineCircleBasicItem *pLineCircleNew = 0;
    QRoundedRectBasic *pRoundedRectNew = 0;
    QArcBasicItem *pArcNew = 0;

    QList<QGraphicsItem *> list = myGraphicsScene->selectedItems();/*保存选中的将要删除的控件*/
    myDiagramItems=list;

    for (int i =0 ; i <list.size();i++)
    {
        // list.at(i)->setSelected(false);
        pSelItem = myDiagramItems.at(i);
        myGraphicsScene->removeItem(pSelItem);

        switch (pSelItem->type())
        {
        case SAM_DRAW_OBJECT_RECT:
            pRect = dynamic_cast<QRectItem *> (pSelItem);
            if (pRect)
            {
                int iSize = pRect->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pRect->m_pvecTrackers[i]);
                }
            }
            break;
           case SAM_DRAW_OBJECT_ELIPSE:
            pElipse = dynamic_cast<QElipseItem *> (pSelItem);
            if (pElipse)
            {
                int iSize = pElipse->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pElipse->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINE:
            pLine = dynamic_cast<QLineItem *> (pSelItem);
            if (pLine)
            {
                int iSize = pLine->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pLine->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_POLYGON:
            pPolygon = dynamic_cast<QPolygonItem *> (pSelItem);
            if (pPolygon)
            {
                int iSize = pPolygon->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pPolygon->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_FOLDLINE:
            pFoldLine = dynamic_cast<QFoldLineItem *> (pSelItem);
            if (pFoldLine)
            {
                int iSize = pFoldLine->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pFoldLine->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_FREELINE:
            pFreeLine = dynamic_cast<QFreeLineItem *> (pSelItem);
            if (pFreeLine)
            {
                int iSize = pFreeLine->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pFreeLine->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_GROUP:
            pItemGroup = dynamic_cast<QItemGroup *> (pSelItem);
            if (pItemGroup)
            {
                int iSize = pItemGroup->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pItemGroup->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINECIRCLE:
            pLineCircle = dynamic_cast<QLineCircleItem *> (pSelItem);
            if (pLineCircle)
            {
                int iSize = pLineCircle->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pLineCircle->m_pvecTrackers[i]);
                }
            }
            break;
       case SAM_DRAW_OBJECT_TEXT:
           pText = dynamic_cast<QSimpleTextItem *> (pSelItem);
           if (pText)
           {
               int iSize = pText->m_pvecTrackers.size();
               for (int i = 0; i < iSize; i++)
               {
                   myGraphicsScene->removeItem(pText->m_pvecTrackers[i]);
               }
           }
           break;
       case SAM_DRAW_OBJECT_ROUNDEDRECT:
           pRoundedRect = dynamic_cast<QRoundedRect *> (pSelItem);
           if (pRoundedRect)
           {
               int iSize = pRoundedRect->m_pvecTrackers.size();
               for (int i = 0; i < iSize; i++)
               {
                   myGraphicsScene->removeItem(pRoundedRect->m_pvecTrackers[i]);
               }
           }
           break;
       case SAM_DRAW_OBJECT_ARC:
           pArc = dynamic_cast<QArcItem *> (pSelItem);
           if (pArc)
           {
               int iSize = pArc->m_pvecTrackers.size();
               for (int i = 0; i < iSize; i++)
               {
                   myGraphicsScene->removeItem(pArc->m_pvecTrackers[i]);
               }
           }
           break;
/////////////////wxy add start
        case SAM_DRAW_OBJECT_RECT_NEW:
            pRectNew = dynamic_cast<QRectBasicItem *> (pSelItem);
            if (pRectNew)
            {
                int iSize = pRectNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pRectNew->m_pvecTrackers[i]);
                }
            }
            break;
           case SAM_DRAW_OBJECT_ELIPSE_NEW:
            pElipseNew = dynamic_cast<QElipseBasicItem *> (pSelItem);
            if (pElipseNew)
            {
                int iSize = pElipseNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pElipseNew->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINE_NEW:
            pLineNew = dynamic_cast<QLineBasicItem *> (pSelItem);
            if (pLineNew)
            {
                int iSize = pLineNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pLineNew->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_POLYGON_NEW:
            pPolygonNew = dynamic_cast<QPolygonBasicItem *> (pSelItem);
            if (pPolygonNew)
            {
                int iSize = pPolygonNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pPolygonNew->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:
            pFoldLineNew = dynamic_cast<QFoldLineBasicItem *> (pSelItem);
            if (pFoldLineNew)
            {
                int iSize = pFoldLineNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pFoldLineNew->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_FREELINE_NEW:
            pFreeLineNew = dynamic_cast<QFreeLineBasicItem *> (pSelItem);
            if (pFreeLineNew)
            {
                int iSize = pFreeLineNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pFreeLineNew->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
            pLineCircleNew = dynamic_cast<QLineCircleBasicItem *> (pSelItem);
            if (pLineCircleNew)
            {
                int iSize = pLineCircleNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->removeItem(pLineCircleNew->m_pvecTrackers[i]);
                }
            }
            break;
       case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
           pRoundedRectNew = dynamic_cast<QRoundedRectBasic *> (pSelItem);
           if (pRoundedRectNew)
           {
               int iSize = pRoundedRectNew->m_pvecTrackers.size();
               for (int i = 0; i < iSize; i++)
               {
                   myGraphicsScene->removeItem(pRoundedRectNew->m_pvecTrackers[i]);
               }
           }
           break;
       case SAM_DRAW_OBJECT_ARC_NEW:
           pArcNew = dynamic_cast<QArcBasicItem *> (pSelItem);
           if (pArcNew)
           {
               int iSize = pArcNew->m_pvecTrackers.size();
               for (int i = 0; i < iSize; i++)
               {
                   myGraphicsScene->removeItem(pArcNew->m_pvecTrackers[i]);
               }
           }
           break;
/////////////////wxy add end
       default:
           break;
       }
   }
   //setText(QObject::tr("Delete Item"));

   //emit myGraphicsScene->selectionChanged();
}
//! [4]

//! [5]
/*=========================
  undo()

  函数功能:实现控件删除撤销功能

  参数:无

  返回值:无
============================*/
void DeleteCommand::undo()
{
    QRectItem *pRect     = 0;
    QElipseItem *pElipse = 0;
    QLineItem *pLine     = 0;
    QPolygonItem *pPolygon   = 0;
    QFoldLineItem *pFoldLine = 0;
    QFreeLineItem *pFreeLine = 0;
    QItemGroup *pItemGroup   = 0;
    QLineCircleItem *pLineCircle = 0;
    QSimpleTextItem *pText = 0;
    QGraphicsItem *pSelItem = 0;
    QRoundedRect *pRoundedRect = 0;
    QArcItem *pArc = 0;

    QRectBasicItem *pRectNew     = 0;
    QElipseBasicItem *pElipseNew  = 0;
    QLineBasicItem *pLineNew     = 0;
    QPolygonBasicItem *pPolygonNew    = 0;
    QFoldLineBasicItem *pFoldLineNew  = 0;
    QFreeLineBasicItem *pFreeLineNew  = 0;
    QLineCircleBasicItem *pLineCircleNew  = 0;
    QRoundedRectBasic *pRoundedRectNew  = 0;
    QArcBasicItem *pArcNew  = 0;

    for (int i =0 ; i <myDiagramItems.size();i++)
    {
        /*将删除的控件重新添加到场景中*/
        pSelItem = myDiagramItems.at(i);
        myGraphicsScene->addItem(pSelItem,pSelItem->zValue());
        pSelItem = myDiagramItems.at(i);
        //更新树形控件
        if(myDiagramItems[i]->data(GROUP_TYPE_KEY).toInt()==USER_DEFINE_GROUP)
        {
            for(int j=0;j<myDiagramItems[i]->childItems().size();j++)
            {
                pwnd->AndTreeSubItem(myDiagramItems[i]->childItems().at(j));
                pwnd->upDatetreeScreenItem();//更新画面的子项
                pwnd->PreviewWindow();
            }
        }
        else
        {
            pwnd->AndTreeSubItem(myDiagramItems[i]);
            pwnd->upDatetreeScreenItem();//更新画面的子项
            pwnd->PreviewWindow();
        }
        switch (pSelItem->type())
        {
        case SAM_DRAW_OBJECT_RECT:
            pRect = dynamic_cast<QRectItem *> (pSelItem);
            if (pRect)
            {
                int iSize = pRect->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pRect->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_ELIPSE:
            pElipse = dynamic_cast<QElipseItem *> (pSelItem);
            if (pElipse)
            {
                int iSize = pElipse->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pElipse->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINE:
            pLine = dynamic_cast<QLineItem *> (pSelItem);
            if (pLine)
            {
                int iSize = pLine->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pLine->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_POLYGON:
            pPolygon = dynamic_cast<QPolygonItem *> (pSelItem);
            if (pPolygon)
            {
                int iSize = pPolygon->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pPolygon->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_FOLDLINE:
            pFoldLine = dynamic_cast<QFoldLineItem *> (pSelItem);
            if (pFoldLine)
            {
                int iSize = pFoldLine->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pFoldLine->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_FREELINE:
            pFreeLine = dynamic_cast<QFreeLineItem *> (pSelItem);
            if (pFreeLine)
            {
                int iSize = pFreeLine->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pFreeLine->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_GROUP:
            pItemGroup = dynamic_cast<QItemGroup *> (pSelItem);
            if (pItemGroup)
            {
                int iSize = pItemGroup->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pItemGroup->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINECIRCLE:
            pLineCircle = dynamic_cast<QLineCircleItem *> (pSelItem);
            if (pLineCircle)
            {
                int iSize = pLineCircle->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pLineCircle->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_TEXT:
            pText = dynamic_cast<QSimpleTextItem *> (pSelItem);
            if (pText)
            {
                int iSize = pText->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pText->m_pvecTrackers[i]);
                }
            }
            break;
       case SAM_DRAW_OBJECT_ROUNDEDRECT:
           pRoundedRect = dynamic_cast<QRoundedRect *> (pSelItem);
           if (pRoundedRect)
           {
               int iSize = pRoundedRect->m_pvecTrackers.size();
               for (int i = 0; i < iSize; i++)
               {
                   myGraphicsScene->addItem(pRoundedRect->m_pvecTrackers[i]);
               }
           }
           break;
       case SAM_DRAW_OBJECT_ARC:
           pArc = dynamic_cast<QArcItem *> (pSelItem);
           if (pArc)
           {
               int iSize = pArc->m_pvecTrackers.size();
               for (int i = 0; i < iSize; i++)
               {
                   myGraphicsScene->addItem(pArc->m_pvecTrackers[i]);
               }
           }
           break;
 ///////////////////wxy add start
        case SAM_DRAW_OBJECT_RECT_NEW:
            pRectNew  = dynamic_cast<QRectBasicItem *> (pSelItem);
            if (pRectNew )
            {
                int iSize = pRectNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pRectNew->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_ELIPSE_NEW:
            pElipseNew = dynamic_cast<QElipseBasicItem *> (pSelItem);
            if (pElipseNew)
            {
                int iSize = pElipseNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pElipseNew->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINE_NEW:
            pLineNew = dynamic_cast<QLineBasicItem *> (pSelItem);
            if (pLineNew)
            {
                int iSize = pLineNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pLineNew->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_POLYGON_NEW:
            pPolygonNew = dynamic_cast<QPolygonBasicItem *> (pSelItem);
            if (pPolygonNew)
            {
                int iSize = pPolygonNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pPolygonNew->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:
            pFoldLineNew = dynamic_cast<QFoldLineBasicItem *> (pSelItem);
            if (pFoldLineNew)
            {
                int iSize = pFoldLineNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pFoldLineNew->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_FREELINE_NEW:
            pFreeLineNew = dynamic_cast<QFreeLineBasicItem *> (pSelItem);
            if (pFreeLineNew)
            {
                int iSize = pFreeLineNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pFreeLineNew->m_pvecTrackers[i]);
                }
            }
            break;
        case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
            pLineCircleNew = dynamic_cast<QLineCircleBasicItem *> (pSelItem);
            if (pLineCircleNew)
            {
                int iSize = pLineCircleNew->m_pvecTrackers.size();
                for (int i = 0; i < iSize; i++)
                {
                    myGraphicsScene->addItem(pLineCircleNew->m_pvecTrackers[i]);
                }
            }
            break;
       case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
           pRoundedRectNew = dynamic_cast<QRoundedRectBasic *> (pSelItem);
           if (pRoundedRectNew)
           {
               int iSize = pRoundedRectNew->m_pvecTrackers.size();
               for (int i = 0; i < iSize; i++)
               {
                   myGraphicsScene->addItem(pRoundedRectNew->m_pvecTrackers[i]);
               }
           }
           break;
       case SAM_DRAW_OBJECT_ARC_NEW:
           pArcNew = dynamic_cast<QArcBasicItem *> (pSelItem);
           if (pArcNew)
           {
               int iSize = pArcNew->m_pvecTrackers.size();
               for (int i = 0; i < iSize; i++)
               {
                   myGraphicsScene->addItem(pArcNew->m_pvecTrackers[i]);
               }
           }
           break;
 //////////////////wxy add end
        default:
            break;
        }
    }
    myGraphicsScene->update();
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    //emit myGraphicsScene->selectionChanged();
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}
//! [5]

//! [6]
/*=========================
  undo()

  函数功能:实现控件删除撤销功能

  参数:无

  返回值:无
============================*/
void DeleteCommand::redo()
{
    for (int i =0 ; i <myDiagramItems.size();i++)
        {
          /*将选中的控件从场景的移除*/
          myGraphicsScene->removeItem(myDiagramItems[i]);
        }
    myGraphicsScene->update(); /*刷新场景控件的参数*/
  // emit myGraphicsScene->selectionChanged();
    pwnd->deleteItem_upDateTreeContrl(myDiagramItems);
    pwnd->PreviewWindow();
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}
//! [6]

//! [7]

/*=========================
  AddCommand()

  函数功能:实现控件删除撤销,恢复功能

  参数:
  DiagramItem::DiagramType addType : 新增控件的类型
  QGraphicsScene *scene  :新增控件所属场景
  QUndoCommand *parent   :
  返回值:无
============================*/
/*
AddCommand::AddCommand(DiagramItem::DiagramType addType,
                       QGraphicsScene *scene, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    static int itemCount = 0;

    myGraphicsScene = scene;
    myDiagramItem = new DiagramItem(addType);
    initialPosition = QPointF((itemCount * 15) % int(scene->width()),
                              (itemCount * 15) % int(scene->height()));
    scene->update();
    ++itemCount;
    setText(QObject::tr("添加 %1")
        .arg(createCommandString(myDiagramItem, initialPosition)));
}
//! [7]

//! [8]
void AddCommand::undo()
{
    myGraphicsScene->removeItem(myDiagramItem);
    myGraphicsScene->update();
}
//! [8]

//! [9]
void AddCommand::redo()
{
    myGraphicsScene->addItem(myDiagramItem);
    myDiagramItem->setPos(initialPosition);
    myGraphicsScene->clearSelection();
    myGraphicsScene->update();
}
*/
//! [9]


//! [10]

QString AddCommand::createCommandString(DiagramItem *item, const QPointF &pos)
{
    return QObject::tr("%1 ;坐标 (%2, %3)")
        .arg(item->Elipse)
        .arg(pos.x()).arg(pos.y());
}

//! [10]

//! [11]
/*=========================
  MovesCommand()

  函数功能:实现控件移动撤销,恢复功能

  参数:
  SamDrawScene *scene : 移动控件所属场景
  QList <QPointF >oldPoss : 保存所选控件的原始坐标
  QUndoCommand *parent   : 执行命令的父指针
  返回值:无
============================*/
MovesCommand::MovesCommand(SamDrawScene *scene,QList <QGraphicsItem *> movingItems,QList <QPointF >oldPoss,
                           QUndoCommand *parent)
             : QUndoCommand(parent)
{

    if(!scene || movingItems.count()<0 )
    {
        return ;
    }
    myDiagramItems=movingItems;  //将移动的控件保存在容器中

    myScene=scene;              //移动控件所在的场景

    foreach (QGraphicsItem *item, myDiagramItems)

    {
         mynewPoss<<item->pos();  //保存控件的当前坐标
    }

  myOldPoss=oldPoss;               //保存控件的原始坐标

  //setText(QObject::tr("Move an Item"));    //在命令列表设置一命令对应命令
}
//! [11]

//! [12]
void MovesCommand::undo()
{
    for (int i =0 ; i <myDiagramItems.size() ;i++)
    {
        myDiagramItems.at(i)->setPos(myOldPoss.at(i));
        //myDiagramItems.at(i)->scene()->update();
    }

    if (myScene)
    {
        myScene->sendSelectionChangeSignal();
        myScene->update();
    }
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myScene);
    pwnd->setActiveScreenIndex(myScene);

    //setText(QObject::tr("Moving"));
}
//! [12]

//! [13]

/*Modified by Bruce nie 06 30th 2011*/
void MovesCommand::redo()
{
    bool bChanged = false;

    for (int i = 0; i < myDiagramItems.size(); i++)
    {
        if (myDiagramItems.at(i)->pos() == mynewPoss.at(i))
        {
            continue;
        }

        myDiagramItems.at(i)->setPos(mynewPoss.at(i));
        bChanged = true;
    }

    if (bChanged && myScene)
    {
        myScene->sendSelectionChangeSignal();
        myScene->update();
    }
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myScene);
    pwnd->setActiveScreenIndex(myScene);
}
/*Modified end*/

//algin command
//对齐 的undo，redo
AlignCommand::AlignCommand(SamDrawScene *scene,QList <QGraphicsItem *> movingItems,
             QList <QSizeF > oldSize,QList <QPointF >oldPoss)
{
    myDiagramItems = movingItems;  //将移动的控件保存在容器中

    myScene = scene;              //移动控件所在的场景

    foreach (QGraphicsItem *item, myDiagramItems)

    {
         mynewPoss << item->sceneBoundingRect().topLeft();  //保存控件的当前坐标
         mynewSize << item->boundingRect().size();
    }

  myOldPoss = oldPoss;               //保存控件的原始坐标
  myoldSize = oldSize;
}

void AlignCommand::redo()
{
    bool bChanged = false;

    QGroupItem *gfun = NULL;
    for (int i = 0; i < myDiagramItems.size(); i++)
    {
        QGraphicsItem * pItem = myDiagramItems.at(i);

        foreach(QGraphicsItem *pt,pItem->childItems())
        {
            if (pt->type() == SAM_DRAW_OBJECT_PIXMAP)
            {
                QPixmapItem *pTmp = NULL;
                pTmp = dynamic_cast<QPixmapItem *> (pt);
                pTmp->boundRect = pTmp->sceneBoundingRect();
            }

        }

        if (pItem->sceneBoundingRect().topLeft() == mynewPoss.at(i)
            && pItem->sceneBoundingRect().size() == mynewSize.at(i))
        {
            continue;
        }


        gfun = new QGroupItem(pItem);
        gfun->SetWidth(mynewSize.at(i).width());
        gfun->SetHeigth(mynewSize.at(i).height());

        pItem->setPos(mynewPoss.at(i)-pItem->boundingRect().topLeft());
        delete gfun;
        gfun = NULL;
        bChanged = true;
    }

    if (bChanged && myScene)
    {
        myScene->sendSelectionChangeSignal();
        myScene->update();
    }
    pwnd->pView->setScene(myScene);
    pwnd->setActiveScreenIndex(myScene);
}
void AlignCommand::undo()
{
    bool bChanged = false;

    QGroupItem *gfun = NULL;
    for (int i = 0; i < myDiagramItems.size(); i++)
    {
        QGraphicsItem * pItem = myDiagramItems.at(i);

        foreach(QGraphicsItem *pt,pItem->childItems())
        {
            if (pt->type() == SAM_DRAW_OBJECT_PIXMAP)
            {
                QPixmapItem *pTmp = NULL;
                pTmp = dynamic_cast<QPixmapItem *> (pt);
                pTmp->boundRect = pTmp->sceneBoundingRect();
            }

        }

        if (pItem->sceneBoundingRect().topLeft() == myOldPoss.at(i)
            && pItem->sceneBoundingRect().size() == myoldSize.at(i))
        {
            continue;
        }

        gfun = new QGroupItem(pItem);
        gfun->SetWidth(myoldSize.at(i).width());
        gfun->SetHeigth(myoldSize.at(i).height());

        pItem->setPos(myOldPoss.at(i)-pItem->boundingRect().topLeft());
        delete gfun;
        gfun = NULL;
        bChanged = true;
    }

    if (bChanged && myScene)
    {
        myScene->sendSelectionChangeSignal();
        myScene->update();
    }
    pwnd->pView->setScene(myScene);
    pwnd->setActiveScreenIndex(myScene);
}
//size command
//设置item大小的undo，redo

SizeCommand::SizeCommand(SamDrawScene *scene,QGraphicsItem * pItem,QSizeF size,QPointF oldPos)
{
    item = pItem;
    oldSize = size;
    newSize = pItem->boundingRect().size();
    oPos = oldPos;
    nPos = pItem->sceneBoundingRect().topLeft();
    myScene = scene;
}
void SizeCommand::redo()
{
    qDebug() << "SizeCommand" << item->boundingRect();
    if(item != NULL){
        foreach(QGraphicsItem *pItem,item->childItems())
        {
            if (pItem->type() == SAM_DRAW_OBJECT_PIXMAP)
            {
                QPixmapItem *pTmp = NULL;
                pTmp = dynamic_cast<QPixmapItem *> (pItem);
                pTmp->boundRect = pTmp->sceneBoundingRect();
            }

        }
        QGroupItem *gfun = new QGroupItem(item);
        gfun->SetWidth(newSize.width());
        gfun->SetHeigth(newSize.height());
        delete gfun;
        gfun = NULL;
        item->setPos(nPos-item->boundingRect().topLeft());
    }
    if(myScene){
        myScene->sendSelectionChangeSignal();
        myScene->update();
    }
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myScene);
    pwnd->setActiveScreenIndex(myScene);
}
void SizeCommand::undo()
{
    if(item != NULL){
        foreach(QGraphicsItem *pItem,item->childItems())
        {
            if (pItem->type() == SAM_DRAW_OBJECT_PIXMAP)
            {
                QPixmapItem *pTmp = NULL;
                pTmp = dynamic_cast<QPixmapItem *> (pItem);
                pTmp->boundRect = pTmp->sceneBoundingRect();
            }

        }
        QGroupItem *gfun = new QGroupItem(item);
        gfun->SetWidth(oldSize.width());
        gfun->SetHeigth(oldSize.height());
        delete gfun;
        gfun = NULL;
        item->setPos(oPos-item->boundingRect().topLeft());
    }
    if(myScene){
        myScene->sendSelectionChangeSignal();
        myScene->update();
    }
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myScene);
    pwnd->setActiveScreenIndex(myScene);
}
//! [13]
#if 1
AddCommand::AddCommand(QGraphicsItem *pItem,
                       QGraphicsScene *scene,QString itemName,QUndoCommand *parent)
    : QUndoCommand(parent)
{
    if(!pItem  || !scene )
    {
        return ;
    }

  // static int itemCount = 0;
   myGraphicsScene = scene;

   commandName=itemName;
   myDiagramItem=pItem;

   /*initialPosition = QPointF((itemCount * 15) % int(scene->width()),
                             (itemCount * 15) % int(scene->height()));*/
   scene->update();
}

void AddCommand::undo()
{
    myGraphicsScene->removeItem(myDiagramItem);
    myGraphicsScene->update();

    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}
void AddCommand::redo()
{
    myGraphicsScene->addItem(myDiagramItem);
   // myDiagramItem->setPos(initialPosition);
    myGraphicsScene->clearSelection();
    myGraphicsScene->update();

    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}

#endif

ModifyItemCommand::ModifyItemCommand(QGraphicsItem *poldItem,QGraphicsItem *pnewItem, SamDrawScene *samdrawscene,QString itemName, QUndoCommand *parent /* = 0 */)
{
        if(!poldItem || !pnewItem || !samdrawscene)
        {
            return ;
        }
	// QMessageBox::information(NULL,"OK","ModifyItemCommand");
	this->mySamDrawScene=samdrawscene;
	this->myoldItem=poldItem;
	this->mynewItem=pnewItem;
}

void ModifyItemCommand::redo()
{
	//QMessageBox::information(NULL,"OK","redo");
    qreal zValue = myoldItem->zValue();
        mySamDrawScene->addItem(mynewItem,zValue);
	mySamDrawScene->removeItem(myoldItem);
        add_edgepoints(mySamDrawScene,mynewItem);
        mynewItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        //mynewItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        mynewItem->setSelected(true);
	mySamDrawScene->update();
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        pwnd->pView->setScene(mySamDrawScene);
        pwnd->setActiveScreenIndex(mySamDrawScene);
}

void ModifyItemCommand::undo()
{
	//QMessageBox::information(NULL,"OK","Undo");
        qreal zValue = myoldItem->zValue();
        mySamDrawScene->addItem(myoldItem,zValue);
        mySamDrawScene->removeItem(mynewItem);
        add_edgepoints(mySamDrawScene,myoldItem);
        myoldItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        //myoldItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        myoldItem->setSelected(true);
	mySamDrawScene->update();
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        pwnd->pView->setScene(mySamDrawScene);
        pwnd->setActiveScreenIndex(mySamDrawScene);
}

LineItemCommand::LineItemCommand(SamDrawScene *scene,QGraphicsItem *item,
                                 QPainterPath oldPath,QPainterPath newPath)
{
    myScene = scene;
    myItem = item;
    oPath = oldPath;
    nPath = newPath;
}
void LineItemCommand::redo()
{
    QLineItem *pLineItem = NULL;
    QFreeLineItem *pFreeLineItem = NULL;
    QFoldLineItem *pFoldlineItem = NULL;
    QLineCircleItem *pLineCircleItem = NULL;
    switch(myItem->type())
    {
    case SAM_DRAW_OBJECT_LINE:
        pLineItem = dynamic_cast<QLineItem *>(myItem);
        pLineItem->setPath(nPath);
        break;
    case SAM_DRAW_OBJECT_FREELINE:
        pFreeLineItem = dynamic_cast<QFreeLineItem *>(myItem);
        pFreeLineItem->setPath(nPath);
        break;
    case SAM_DRAW_OBJECT_FOLDLINE:
        pFoldlineItem = dynamic_cast<QFoldLineItem *>(myItem);
        pFoldlineItem->setPath(nPath);
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE:
        pLineCircleItem = dynamic_cast<QLineCircleItem *>(myItem);
        pLineCircleItem->setPath(nPath);
        pLineCircleItem->removeLineTracker(myScene);
        break;
    default :break;
    }
    myScene->sendSelectionChangeSignal();

    myItem->setSelected(true);
    myScene->update();
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myScene);
    pwnd->setActiveScreenIndex(myScene);
}

void LineItemCommand::undo()
{
    QLineItem *pLineItem = NULL;
    QFreeLineItem *pFreeLineItem = NULL;
    QFoldLineItem *pFoldlineItem = NULL;
    QLineCircleItem *pLineCircleItem = NULL;
    switch(myItem->type())
    {
    case SAM_DRAW_OBJECT_LINE:
        pLineItem = dynamic_cast<QLineItem *>(myItem);
        pLineItem->setPath(oPath);
        break;
    case SAM_DRAW_OBJECT_FREELINE:
        pFreeLineItem = dynamic_cast<QFreeLineItem *>(myItem);
        pFreeLineItem->setPath(oPath);
        break;
    case SAM_DRAW_OBJECT_FOLDLINE:
        pFoldlineItem = dynamic_cast<QFoldLineItem *>(myItem);
        pFoldlineItem->setPath(oPath);
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE:
        pLineCircleItem = dynamic_cast<QLineCircleItem *>(myItem);
        pLineCircleItem->setPath(oPath);
        pLineCircleItem->removeLineTracker(myScene);
        break;
    default :break;
    }
    myScene->sendSelectionChangeSignal();

    myItem->setSelected(true);
    myScene->update();
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myScene);
    pwnd->setActiveScreenIndex(myScene);
}

PolygonItemCommand::PolygonItemCommand(SamDrawScene *scene,QGraphicsItem *item,
                                 QPolygonF oldPolygon,QPolygonF newPolygon)
{
    myScene = scene;
    myItem = item;
    oPolygon = oldPolygon;
    nPolygon = newPolygon;
}
void PolygonItemCommand::undo()
{
    QPolygonItem *pPolygonItem = NULL;
    QPolygonF polygon;
    switch(myItem->type())
    {
    case SAM_DRAW_OBJECT_POLYGON:
        pPolygonItem = dynamic_cast<QPolygonItem *>(myItem);
        polygon = myItem->mapToScene(oPolygon);
        pPolygonItem->setPolygon(polygon);

        break;
    default :break;
    }
    myScene->sendSelectionChangeSignal();

    myItem->setSelected(true);
    myScene->update();
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myScene);
    pwnd->setActiveScreenIndex(myScene);
}

void PolygonItemCommand::redo()
{
    QPolygonItem *pPolygonItem = NULL;
    QPolygonF polygon;
    switch(myItem->type())
    {
    case SAM_DRAW_OBJECT_POLYGON:
        pPolygonItem = dynamic_cast<QPolygonItem *>(myItem);
        polygon = myItem->mapToScene(nPolygon);
        pPolygonItem->setPolygon(polygon);

        break;
    default :break;
    }
    myScene->sendSelectionChangeSignal();

    myItem->setSelected(true);
    myScene->update();
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myScene);
    pwnd->setActiveScreenIndex(myScene);
}
