#include "unandrestack.h"
#include "view/samdrawitembase.h"
//#include "stdafx.h"
#include "Frame\mainwindow.h"
#include "view/DataDisplayItem.h"
#include <qmessagebox.h>
#include <QObject>

extern MainWindow *pwnd;
void update_edgepoints(SamDrawScene  *myGraphicsScene,QGraphicsItem * pSelItem)
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
    QRoundedRect *pRoundedRect = 0;
    QArcItem *pArc = 0;

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
    default:
       break;
   }
}
pasteCommand::pasteCommand(SamDrawScene *samdrawscene,QList<QGraphicsItem *> pastItems,bool bflag)
{
    b_flag=bflag;
    myDiagramItems=pastItems;
    myGraphicsScene=samdrawscene;
}

void pasteCommand::undo()
{
    for(int i=0;i<myDiagramItems.size();i++)
    {
        myGraphicsScene->removeItem(myDiagramItems[i]);
    }
    pwnd->deleteItem_upDateTreeContrl(myDiagramItems);//处理树形控件
    pwnd->PreviewWindow();
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);

}

void pasteCommand::redo()
{
    if(b_flag)
    {
        b_flag=false;
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    QGraphicsItem * pSelItem=NULL;
    myGraphicsScene->clearSelection();
    for (int i =0 ; i <myDiagramItems.size();i++)
    {
        pSelItem = myDiagramItems.at(i);
        myGraphicsScene->addItem(pSelItem);
        pSelItem = myDiagramItems.at(i);
        update_edgepoints(myGraphicsScene,pSelItem);//添加边缘的8个点

        pSelItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        pSelItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        pSelItem->setSelected(true);

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
    }
    myGraphicsScene->update();
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}//

groupCommand::groupCommand(SamDrawScene *samdrawscene)
{
    myGraphicsScene=samdrawscene;
    selectedChildItems = myGraphicsScene->selectedItems();
    selectedGroup = new QItemGroup();
}

void groupCommand::redo()
{
    if(selectedChildItems.size() <= 1)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    //selectedGroup = new QItemGroup();
    int i = 0;


    //在组合之前先去掉锁状态和锁item
    for(i=0;i < selectedChildItems.size();i++)
    {
        selectedChildItems.at(i)->setFlag(QGraphicsItem::ItemIsMovable, true);
    }
    myGraphicsScene->reBondingTrackers();


    myGraphicsScene->clearSelection();
    for(i=0;i < selectedChildItems.size();i++)
    {
        //在组合之前清除选择状态框
        selectedChildItems.at(i)->setFlag(QGraphicsItem::ItemIsSelectable, false);
        selectedGroup->addToGroup(selectedChildItems.at(i));
    }
    myGraphicsScene->addItem(selectedGroup);
    selectedGroup->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
    selectedGroup->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
    /*Create the handle rects when a new group borned*/
    QRectF qrcBndRect = selectedGroup->sceneBoundingRect();
    selectedGroup->drawTracker(TRK_SELECTED, (QGraphicsScene *)myGraphicsScene, qrcBndRect);
    selectedGroup->setSelected(true);

    selectedGroup->setData(GROUP_TYPE_KEY,QVariant(USER_DEFINE_GROUP)); //设置用户自定义组合的key值
    //selectedItem=dynamic_cast<QGraphicsItem *>(Group);
    pwnd->ui->action_split->setEnabled(true);
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}

void groupCommand::undo()
{
    if(selectedChildItems.size() <= 1)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    myGraphicsScene->removeItem(selectedGroup);
    myGraphicsScene->clearSelection();
    foreach(QGraphicsItem * pItem,selectedGroup->childItems())
    {
        selectedGroup->removeFromGroup(pItem);
        myGraphicsScene->addItem(pItem,pItem->zValue());
        update_edgepoints(myGraphicsScene,pItem);
        pItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        pItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        pItem->setSelected(true);
    }
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}

disgroupCommand::disgroupCommand(SamDrawScene *samdrawscene)
{
    myGraphicsScene=samdrawscene;
    selectedlist = myGraphicsScene->selectedItems(); //方法2
    z = 0;
    if(selectedlist.size() != 1)
    {
        return ;
    }
    if(selectedlist.first()->data(GROUP_TYPE_KEY).toInt() != USER_DEFINE_GROUP)
        return;
    selectedGroup = dynamic_cast<QItemGroup *>(selectedlist.first());
    z = selectedGroup->zValue();
}
void disgroupCommand::redo()
{
    myGraphicsScene->removeItem(selectedGroup);
    myGraphicsScene->clearSelection();
    this->disgroupCommand_childitemList.clear();
    disgroupCommand_childitemList = selectedGroup->childItems();

    foreach(QGraphicsItem * pItem,selectedGroup->childItems())
    {
        selectedGroup->removeFromGroup(pItem);
        myGraphicsScene->addItem(pItem);
        update_edgepoints(myGraphicsScene,pItem);
        pItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
        pItem->setFlag(QGraphicsItem::ItemIsMovable, true);
        pItem->setSelected(true);
    }
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);

}

void disgroupCommand::undo()
{
    if(selectedlist.size() != 1)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return ;
    }
    myGraphicsScene->clearSelection();
    QList<QGraphicsItem *> qlstSelectedItems;
    //QItemGroup *Group = new QItemGroup();
    qlstSelectedItems=disgroupCommand_childitemList;
    int i = 0;
    if(qlstSelectedItems.size() <= 1)
    {
        return;
    }
    for(i=0;i < qlstSelectedItems.size();i++)
    {
        //在组合之前清除选择状态框
        qlstSelectedItems.at(i)->setFlag(QGraphicsItem::ItemIsSelectable, false);
        selectedGroup->addToGroup(qlstSelectedItems.at(i));
    }
    myGraphicsScene->addItem(selectedGroup,z);
    selectedGroup->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
    selectedGroup->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
    /*Create the handle rects when a new group borned*/
    QRectF qrcBndRect = selectedGroup->sceneBoundingRect();
    selectedGroup->drawTracker(TRK_SELECTED, (QGraphicsScene *)myGraphicsScene, qrcBndRect);
    selectedGroup->setSelected(true);

    selectedGroup->setData(GROUP_TYPE_KEY,QVariant(USER_DEFINE_GROUP)); //设置用户自定义组合的key值
   // selectedGroup = Group;
    pwnd->ui->action_split->setEnabled(true);
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}

addItemToScence::addItemToScence(SamDrawScene *samdrawscene,QGraphicsItem *pItem,bool bflag)
{
    myGraphicsScene=samdrawscene;
    b_flag=bflag;
    pAddItem=pItem;
}

void addItemToScence::redo()
{
    if(b_flag)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }

    if(pAddItem==NULL)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }

    myGraphicsScene->clearSelection();;
    myGraphicsScene->addItem(pAddItem);
    //pAddItem->setPos(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->MousePressPos);
    pwnd->AndTreeSubItem(pAddItem);
    pwnd->upDatetreeScreenItem();;//更新画面的子项

    pAddItem->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
    pAddItem->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
    pAddItem->setSelected(true);

    int nID = pAddItem->data(GROUP_TYPE_KEY).toInt();
    if(nID == GROUP_TYPE_BITBTN || nID == GROUP_TYPE_BITLAMP
       || nID == GROUP_TYPE_MULSTATELAMP || nID == GROUP_TYPE_MULSTATEBTN
       || GROUP_TYPE_PICTUREMOVE || nID == GROUP_TYPE_MSGDISPLAY
       || nID == GROUP_TYPE_WEEKBTN) //位按钮 位指示灯 多态指示灯、多态按钮、图形移动 消息显示 星期显示
    {
        pwnd->OnSingleClickItem();//更新工具栏上的状态组合框内容
    }
    update_edgepoints(myGraphicsScene,pAddItem);//添加边缘的8个点
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}

void addItemToScence::undo()
{
    if(pAddItem==NULL)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    myGraphicsScene->removeItem(pAddItem);
    b_flag=false;
    QList<QGraphicsItem *>  list;
    list.push_back(pAddItem);
    pwnd->deleteItem_upDateTreeContrl(list);
    pwnd->PreviewWindow();
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}//

cutItemCommand::cutItemCommand(SamDrawScene *samdrawscene,QList<QGraphicsItem *> selectItemList,bool bflag)
{
    myGraphicsScene=samdrawscene;
    CutItemList=selectItemList;
    b_flag=bflag;
}

void cutItemCommand::redo()
{
  if(b_flag)
  {
      pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
      pwnd->is_NeedCompiled = true;
      pwnd->ui->action_save->setDisabled(false);
    return;
  }

  if(CutItemList.size()==NULL)
  {
      b_flag=false;
      pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
      pwnd->is_NeedCompiled = true;
      pwnd->ui->action_save->setDisabled(false);
      return;
  }
  for(int i=0;i<CutItemList.size();i++)
  {
      myGraphicsScene->removeItem(CutItemList[i]);
  }
  pwnd->deleteItem_upDateTreeContrl(CutItemList);//处理树形控件
  pwnd->PreviewWindow();
  b_flag=true;
  pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
  pwnd->is_NeedCompiled = true;
  pwnd->ui->action_save->setDisabled(false);
  pwnd->pView->setScene(myGraphicsScene);
  pwnd->setActiveScreenIndex(myGraphicsScene);
}

void cutItemCommand::undo()
{
    if(b_flag)
    {
        b_flag=false;
        myGraphicsScene->clearSelection();
        QGraphicsItem * pSelItem=NULL;
        for (int i =0 ; i <CutItemList.size();i++)
        {
            pSelItem = CutItemList.at(i);
            myGraphicsScene->addItem(pSelItem,pSelItem->zValue());
            update_edgepoints(myGraphicsScene,pSelItem);//添加边缘的8个点
            pSelItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            pSelItem->setFlag(QGraphicsItem::ItemIsMovable, true);
            pSelItem->setSelected(true);
            if(CutItemList[i]->data(GROUP_TYPE_KEY).toInt()==USER_DEFINE_GROUP)
            {
                for(int j=0;j<CutItemList[i]->childItems().size();j++)
                {
                    pwnd->AndTreeSubItem(CutItemList[i]->childItems().at(j));
                    pwnd->upDatetreeScreenItem();//更新画面的子项
                    pwnd->PreviewWindow();
                }
            }
            else
            {
                pwnd->AndTreeSubItem(CutItemList[i]);
                pwnd->upDatetreeScreenItem();//更新画面的子项
                pwnd->PreviewWindow();
            }
        }
        myGraphicsScene->update();
    }
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);

}//

zValueDownChangeCommand::zValueDownChangeCommand(SamDrawScene * samdrawscene)
{
    myGraphicsScene=samdrawscene;
    pSelectItem = myGraphicsScene->ItemSelected();
    foreach(QGraphicsItem *pItem,myGraphicsScene->TopItems())
    {
        oder.insert(pItem,pItem->zValue());
    }
}

void zValueDownChangeCommand::redo()
{
    if(!pSelectItem)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }

    QGraphicsItem *item = pSelectItem  ;
    myGraphicsScene->ResetOder(item,2);
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}

void zValueDownChangeCommand::undo()
{
    if(!pSelectItem)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }

    foreach(QGraphicsItem *pItem,myGraphicsScene->TopItems())
    {
        //oder.insert(pItem,pItem->zValue());
        if(oder.contains(pItem))
        {
            pItem->setZValue(oder.value(pItem));
        }
    }
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}

zValueUpChangeCommand::zValueUpChangeCommand(SamDrawScene * samdrawscene)
{
   myGraphicsScene=samdrawscene;
   pSelectItem = myGraphicsScene->ItemSelected();
   foreach(QGraphicsItem *pItem,myGraphicsScene->TopItems())
   {
       oder.insert(pItem,pItem->zValue());
   }
}

void zValueUpChangeCommand::redo()
{
    if(!pSelectItem)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    QGraphicsItem *item = pSelectItem;
    pSelectItem = item;
    myGraphicsScene->ResetOder(item,3);
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);

}

void zValueUpChangeCommand::undo()
{
    if(!pSelectItem)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }

    foreach(QGraphicsItem *pItem,myGraphicsScene->TopItems())
    {
        //oder.insert(pItem,pItem->zValue());
        if(oder.contains(pItem))
        {
            pItem->setZValue(oder.value(pItem));
        }
    }
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}

bringtopCommand::bringtopCommand(SamDrawScene * samdrawscene)
{
    myGraphicsScene = samdrawscene;
    pSelectItem = myGraphicsScene->ItemSelected();
    foreach(QGraphicsItem *pItem,myGraphicsScene->TopItems())
    {
        oder.insert(pItem,pItem->zValue());
    }
}


void bringtopCommand::redo()
{
    if(!pSelectItem)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    QGraphicsItem *item = pSelectItem;
    nVal= item->zValue();
    myGraphicsScene->ResetOder(item,4);
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);

}

void bringtopCommand::undo()
{
    if(!pSelectItem)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }

    foreach(QGraphicsItem *pItem,myGraphicsScene->TopItems())
    {
        //oder.insert(pItem,pItem->zValue());
        if(oder.contains(pItem))
        {
            pItem->setZValue(oder.value(pItem));
        }
    }
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}

bringBottomCommand::bringBottomCommand(SamDrawScene * samdrawscene)
{
    myGraphicsScene = samdrawscene;
    pSelectItem = myGraphicsScene->ItemSelected();
    foreach(QGraphicsItem *pItem,myGraphicsScene->TopItems())
    {
        oder.insert(pItem,pItem->zValue());
    }
}

void bringBottomCommand::redo()
{
    if(!pSelectItem)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    QGraphicsItem *item = pSelectItem;
     nVal= item->zValue();
    myGraphicsScene->ResetOder(item,1);
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}

void bringBottomCommand::undo()
{
    if(!pSelectItem)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }

    foreach(QGraphicsItem *pItem,myGraphicsScene->TopItems())
    {
        //oder.insert(pItem,pItem->zValue());
        if(oder.contains(pItem))
        {
            pItem->setZValue(oder.value(pItem));
        }
    }
     pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
     pwnd->is_NeedCompiled = true;
     pwnd->ui->action_save->setDisabled(false);
     pwnd->pView->setScene(myGraphicsScene);
     pwnd->setActiveScreenIndex(myGraphicsScene);
}

multiCopyCommand::multiCopyCommand(SamDrawScene *samdrawscene,QList<QGraphicsItem *> addItemsList,QGraphicsItem * pItem,bool bflag)
{
    myGraphicsScene = samdrawscene;
    addList= addItemsList;
    b_flag = bflag;
    pSelectItem = pItem ;

}

void multiCopyCommand::redo()
{
   if(b_flag)
   {
       b_flag=false;
       pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
       pwnd->is_NeedCompiled = true;
       pwnd->ui->action_save->setDisabled(false);
       return;
   }

   if (addList.size() != 0)
   {
       for(int i=0;i<addList.size();i++)
       {
           myGraphicsScene->addItem(addList[i]);
           pwnd->AndTreeSubItem(addList[i]);
           pwnd->upDatetreeScreenItem();;//更新画面的子项
       }
   }
   pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
   pwnd->is_NeedCompiled = true;
   pwnd->ui->action_save->setDisabled(false);
   pwnd->pView->setScene(myGraphicsScene);
   pwnd->setActiveScreenIndex(myGraphicsScene);

}

void multiCopyCommand::undo()
{
    for(int i=0;i<addList.size();i++)
    {
        myGraphicsScene->removeItem(addList[i]);
    }
    pwnd->deleteItem_upDateTreeContrl(addList);//处理树形控件
    pwnd->PreviewWindow();
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
    pwnd->pView->setScene(myGraphicsScene);
    pwnd->setActiveScreenIndex(myGraphicsScene);
}


ModifyBaseItemCommand::ModifyBaseItemCommand(SamDrawScene *samdrawscene,QGraphicsItem *oldItem,QGraphicsItem *newItem)
{
    Scene = samdrawscene;
    oItem = oldItem;
    nItem = newItem;
    z = oldItem->zValue();
}

void ModifyBaseItemCommand::redo()
{
    if(!(oItem->flags() & QGraphicsItem::ItemIsMovable))
    {
        nItem->setFlag(QGraphicsItemGroup::ItemIsMovable, false);
    }
    else
    {
        nItem->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
    }
    Scene->removeItem(oItem);
    Scene->addItem(nItem,oItem->zValue());
    update_edgepoints(Scene,nItem);
    nItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    //nItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    nItem->setSelected(true);
    Scene->update();
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
}
void ModifyBaseItemCommand::undo()
{
    Scene->removeItem(nItem);
    Scene->addItem(oItem,nItem->zValue());
    update_edgepoints(Scene,oItem);
    oItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    //oItem->setFlag(QGraphicsItem::ItemIsMovable, true);
    oItem->setSelected(true);
    Scene->update();
    pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);
}

ModifyItemsCommand::ModifyItemsCommand(SamDrawScene *samdrawscene,QList<bool>selValues,
                                       QList<QGraphicsItem *>oldItems,QList<QGraphicsItem *>newItems)
{
    Scene = samdrawscene;
    oItems = oldItems;
    nItems = newItems;
    b_flag = true;
    values = selValues;
}

void ModifyItemsCommand::redo()
{
    if(b_flag)
    {
        b_flag=false;
        pwnd->is_Save=false;
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    qDebug() <<"ModifyItemsCommand::redo()";
    if(oItems.size() == nItems.size())
    {
        for(int i=0; i<oItems.size(); i++)
        {
            qreal z = oItems.at(i)->zValue();
            Scene->removeItem(oItems.at(i));
            Scene->addItem(nItems.at(i),z);

            nItems.at(i)->setFlag(QGraphicsItem::ItemIsMovable, true);
            nItems.at(i)->setFlag(QGraphicsItem::ItemIsSelectable, true);
            update_edgepoints(Scene,nItems.at(i));
            nItems.at(i)->setSelected(values.at(i));

            Scene->reBondingTrackers();
            pwnd->AndTreeSubItem(nItems.at(i));
            pwnd->upDatetreeScreenItem();

            pwnd->is_Save=false;
            pwnd->is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
            pwnd->pView->setScene(Scene);
        }
    }
    pwnd->setActiveScreenIndex(Scene);
}
void ModifyItemsCommand::undo()
{
    qDebug() <<"ModifyItemsCommand::undo()";
    if(oItems.size() == nItems.size())
    {
        for(int i=0; i<oItems.size(); i++)
        {
            qreal z = oItems.at(i)->zValue();
            Scene->removeItem(nItems.at(i));
            Scene->addItem(oItems.at(i),z);

            oItems.at(i)->setFlag(QGraphicsItem::ItemIsMovable, true);
            oItems.at(i)->setFlag(QGraphicsItem::ItemIsSelectable, true);
            update_edgepoints(Scene,oItems.at(i));
            oItems.at(i)->setSelected(values.at(i));


            pwnd->AndTreeSubItem(oItems.at(i));
            pwnd->upDatetreeScreenItem();

            pwnd->is_Save=false;
            pwnd->is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
            pwnd->pView->setScene(Scene);
        }
    }
    pwnd->setActiveScreenIndex(Scene);
}

/********************************************AddSceneCommand start*/
AddSceneCommand::AddSceneCommand(SamDrawScene *samdrawscene, int iActiveSheetIndex, int iTreeIndex, bool bflag)
{
    Scene = samdrawscene;
    m_iActiveSheetIndex = iActiveSheetIndex;
    m_iTreeIndex = iTreeIndex;
    m_bFlag = bflag;
}

void AddSceneCommand::redo()
{
    if(m_bFlag)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    QString str     = "";
    QString stotal  = "";
    int     nTmp    = 0;
    int iSheetNum = pwnd->pSceneSheet.size();

    pwnd->pSceneSheet.insert(m_iActiveSheetIndex, Scene);
    pwnd->nActiveSheetIndex = m_iActiveSheetIndex;
    pwnd->pView->setScene(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]);

    //wxy newScreen相应的插入一个
    for(int i = iSheetNum; i >pwnd->nActiveSheetIndex; i--)
    {
        pwnd->newScreen[i] = pwnd->newScreen[i-1];
        QTreeWidgetItem *parentItem=pwnd->newScreen[i]->parent();//取后一个父类型
        if(parentItem->text(0)!=QObject::tr("自定义键盘"))
        {
            //若不是为自定义键盘的话
            stotal=pwnd->newScreen[i]->text(0).split(":").at(0);
            nTmp=stotal.toInt();
            stotal=QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
            str=stotal+":"+pwnd->newScreen[i]->text(0).split(":").at(1);
            pwnd->newScreen[i]->setText(0,str);
        }
    }

    //wxy 创建时应该不指定parent结点，否则会加到最后面
    str = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNumberName;
    pwnd->newScreen[pwnd->nActiveSheetIndex] = new QTreeWidgetItem(/*pwnd->screen,*/QStringList(str + ":" + pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
    pwnd->screen->insertChild(m_iTreeIndex, pwnd->newScreen[pwnd->nActiveSheetIndex]);

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    pwnd->handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);

    pwnd->is_Save=false;//
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

    pwnd->upDatetreeScreenItem();//更新画面的子项
    QString sTmp=pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(1);
    pwnd->updateChScreen();
    pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(pwnd->nActiveSheetIndex));
    pwnd->tree0->setFocus(Qt::MouseFocusReason);
    for(int j=0;j<pwnd->copyScreen_Item->childCount();j++)
    {
        QString sNo=pwnd->copyScreen_Item->child(j)->text(0).split(":").at(1);
        if(sTmp==sNo)
        {
            pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(j),0,QItemSelectionModel::SelectCurrent);
            pwnd->tree0->setFocus(Qt::ActiveWindowFocusReason);
        }
    }
    m_bFlag = true;
}

void AddSceneCommand::undo()
{
    if(m_bFlag)
    {
        m_bFlag = false;
        QString str     = "";
        QString stotal  = "";
        int     nTmp    = 0;
        int totalSceneNum   = pwnd->pSceneSheet.size();
        pwnd->nActiveSheetIndex = m_iActiveSheetIndex;
        if(pwnd->nActiveSheetIndex+1 > totalSceneNum)
        {
            QMessageBox box(pwnd);
            box.setText(QObject::tr("请选择一个要删除的项"));
            box.exec();
            return;
        }
        if(totalSceneNum == 1)
        {
            QMessageBox box(pwnd);
            box.setText(QObject::tr("最后一个画面不可以删除"));
            box.exec();
            return;
        }
        pwnd->screen->removeChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);//删除树控件点击的子菜单
        pwnd->pSceneSheet.remove(pwnd->nActiveSheetIndex);//删除场景中的数据
        pwnd->deleteScreen_upDateIndex();

        for(int i = pwnd->nActiveSheetIndex; i < totalSceneNum - 1; i++)
        {
            pwnd->newScreen[i] = pwnd->newScreen[i+1];
            QTreeWidgetItem *parentItem=pwnd->newScreen[i]->parent();//取后一个父类型
            if((parentItem != pwnd->TreeKeyboard) && (parentItem != pwnd->copyUserKeyboard))
            {
                //若不是为自定义键盘的话
                stotal = pwnd->newScreen[i]->text(0).split(":").at(0);
                nTmp   = stotal.toInt();
                stotal = QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
                str    = stotal + ":" + pwnd->newScreen[i]->text(0).split(":").at(1);
                pwnd->newScreen[i]->setText(0,str);
            }
        }

        if(!pwnd->label.isEmpty() && pwnd->nActiveSheetIndex < pwnd->label.size())
        {
            pwnd->label.remove(pwnd->nActiveSheetIndex);
        }
        if(!pwnd->titlelabel.isEmpty() && pwnd->nActiveSheetIndex < pwnd->titlelabel.size())
        {
            pwnd->titlelabel.remove(pwnd->nActiveSheetIndex);
        }
        if(!pwnd->priviewWidget.isEmpty() && pwnd->nActiveSheetIndex < pwnd->priviewWidget.size())
        {
            pwnd->priviewWidget.remove(pwnd->nActiveSheetIndex);
        }

        pwnd->DealWithDeleteScreen();//处理删除画面窗口自定义键盘的时候树形控件刷新问题

        QString strDest;
        QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
        pwnd->handleWinTitle(strDest, strtemp);
        pwnd->setWindowTitle(strDest);

        pwnd->upDatetreeScreenItem();//更新画面的子项
        pwnd->updateChScreen();
    }
}
/********************************************AddSceneCommand end*/

/********************************************DeleteSceneCommand start*/
DeleteSceneCommand::DeleteSceneCommand(SamDrawScene *samdrawscene, int iActiveSheetIndex, int iTreeIndex, bool bflag)
{
    Scene = samdrawscene;
    m_iActiveSheetIndex = iActiveSheetIndex;
    m_iTreeIndex = iTreeIndex;
    m_bFlag = bflag;
}

void DeleteSceneCommand::redo()
{
    if(m_bFlag)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    QString str     = "";
    QString stotal  = "";
    int     nTmp    = 0;
    int totalSceneNum   = pwnd->pSceneSheet.size();
    pwnd->nActiveSheetIndex = m_iActiveSheetIndex;
    if(pwnd->nActiveSheetIndex+1 > totalSceneNum)
    {
        QMessageBox box(pwnd);
        box.setText(QObject::tr("请选择一个要删除的项"));
        box.exec();
        return;
    }
    if(totalSceneNum == 1)
    {
        QMessageBox box(pwnd);
        box.setText(QObject::tr("最后一个画面不可以删除"));
        box.exec();
        return;
    }
    pwnd->screen->removeChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);//删除树控件点击的子菜单
    pwnd->pSceneSheet.remove(pwnd->nActiveSheetIndex);//删除场景中的数据
    pwnd->deleteScreen_upDateIndex();

    for(int i = pwnd->nActiveSheetIndex; i < totalSceneNum - 1; i++)
    {
        pwnd->newScreen[i] = pwnd->newScreen[i+1];
        QTreeWidgetItem *parentItem=pwnd->newScreen[i]->parent();//取后一个父类型
        if((parentItem != pwnd->TreeKeyboard) && (parentItem != pwnd->copyUserKeyboard))
        {
            //若不是为自定义键盘的话
            stotal = pwnd->newScreen[i]->text(0).split(":").at(0);
            nTmp   = stotal.toInt();
            stotal = QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
            str    = stotal + ":" + pwnd->newScreen[i]->text(0).split(":").at(1);
            pwnd->newScreen[i]->setText(0,str);
        }
    }

    if(!pwnd->label.isEmpty() && pwnd->nActiveSheetIndex < pwnd->label.size())
    {
        pwnd->label.remove(pwnd->nActiveSheetIndex);
    }
    if(!pwnd->titlelabel.isEmpty() && pwnd->nActiveSheetIndex < pwnd->titlelabel.size())
    {
        pwnd->titlelabel.remove(pwnd->nActiveSheetIndex);
    }
    if(!pwnd->priviewWidget.isEmpty() && pwnd->nActiveSheetIndex < pwnd->priviewWidget.size())
    {
        pwnd->priviewWidget.remove(pwnd->nActiveSheetIndex);
    }

    pwnd->DealWithDeleteScreen();//处理删除画面窗口自定义键盘的时候树形控件刷新问题

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    pwnd->handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);

    pwnd->upDatetreeScreenItem();//更新画面的子项
    pwnd->updateChScreen();
    m_bFlag = true;
}

void DeleteSceneCommand::undo()
{
    if(m_bFlag)
    {
        m_bFlag = false;
        QString str     = "";
        QString stotal  = "";
        int     nTmp    = 0;
        int iSheetNum = pwnd->pSceneSheet.size();

        pwnd->pSceneSheet.insert(m_iActiveSheetIndex, Scene);
        pwnd->nActiveSheetIndex = m_iActiveSheetIndex;
        pwnd->pView->setScene(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]);

        //wxy newScreen相应的插入一个
        for(int i = iSheetNum; i >pwnd->nActiveSheetIndex; i--)
        {
            pwnd->newScreen[i] = pwnd->newScreen[i-1];
            QTreeWidgetItem *parentItem=pwnd->newScreen[i]->parent();//取后一个父类型
            if(parentItem->text(0)!=QObject::tr("自定义键盘"))
            {
                //若不是为自定义键盘的话
                stotal=pwnd->newScreen[i]->text(0).split(":").at(0);
                nTmp=stotal.toInt();
                stotal=QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
                str=stotal+":"+pwnd->newScreen[i]->text(0).split(":").at(1);
                pwnd->newScreen[i]->setText(0,str);
            }
        }

        //wxy 创建时应该不指定parent结点，否则会加到最后面
        str = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNumberName;
        pwnd->newScreen[pwnd->nActiveSheetIndex] = new QTreeWidgetItem(/*pwnd->screen,*/QStringList(str + ":" + pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
        pwnd->screen->insertChild(m_iTreeIndex, pwnd->newScreen[pwnd->nActiveSheetIndex]);

        QString strDest;
        QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
        pwnd->handleWinTitle(strDest, strtemp);
        pwnd->setWindowTitle(strDest);

        pwnd->is_Save=false;//
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

        pwnd->upDatetreeScreenItem();//更新画面的子项
        QString sTmp=pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(1);
        pwnd->updateChScreen();
        pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(pwnd->nActiveSheetIndex));
        pwnd->tree0->setFocus(Qt::MouseFocusReason);
        for(int j=0;j<pwnd->copyScreen_Item->childCount();j++)
        {
            QString sNo=pwnd->copyScreen_Item->child(j)->text(0).split(":").at(1);
            if(sTmp==sNo)
            {
                pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                pwnd->tree0->setFocus(Qt::ActiveWindowFocusReason);
            }
        }
    }
}

/********************************************DeleteSceneCommand end*/

/********************************************AddWindowCommand start*/
AddWindowCommand::AddWindowCommand(SamDrawScene *samdrawscene, int iActiveSheetIndex, int iTreeIndex, bool bflag)
{
    Scene = samdrawscene;
    m_iActiveSheetIndex = iActiveSheetIndex;
    m_iTreeIndex = iTreeIndex;
    m_bFlag = bflag;
}

void AddWindowCommand::redo()
{
    if(m_bFlag)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    QString str     = "";
    QString stotal  = "";
    int     nTmp    = 0;
    int iSheetNum = pwnd->pSceneSheet.size();
    pwnd->pSceneSheet.insert(m_iActiveSheetIndex, Scene);
    pwnd->nActiveSheetIndex = m_iActiveSheetIndex;
    pwnd->pView->setScene(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]);

    //wxy newScreen相应的插入一个
    for(int i = iSheetNum; i >pwnd->nActiveSheetIndex; i--)
    {
        pwnd->newScreen[i] = pwnd->newScreen[i-1];
        QTreeWidgetItem *parentItem=pwnd->newScreen[i]->parent();//取后一个父类型
        if(parentItem->text(0)!=QObject::tr("自定义键盘"))
        {
            //若不是为自定义键盘的话
            stotal=pwnd->newScreen[i]->text(0).split(":").at(0);
            nTmp=stotal.toInt();
            stotal=QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
            str=stotal+":"+pwnd->newScreen[i]->text(0).split(":").at(1);
            pwnd->newScreen[i]->setText(0,str);
        }
    }
    //wxy 创建时应该不指定parent结点，否则会加到最后面
    str = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNumberName;
    pwnd->newScreen[pwnd->nActiveSheetIndex] = new QTreeWidgetItem(/*pwnd->window,*/QStringList(str + ":" + pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
    pwnd->window->insertChild(m_iTreeIndex, pwnd->newScreen[pwnd->nActiveSheetIndex]);

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    pwnd->handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);

    pwnd->is_Save=false;//
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

    pwnd->upDatetreeScreenItem();//更新画面的子项
    QString sTmp=pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(1);
    pwnd->updateChScreen();
    pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(pwnd->nActiveSheetIndex));
    pwnd->tree0->setFocus(Qt::MouseFocusReason);
    for(int j=0;j<pwnd->copyScreen_Item->childCount();j++)
    {
        QString sNo=pwnd->copyScreen_Item->child(j)->text(0).split(":").at(1);
        if(sTmp==sNo)
        {
            pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(j),0,QItemSelectionModel::SelectCurrent);
            pwnd->tree0->setFocus(Qt::ActiveWindowFocusReason);
        }
    }
    m_bFlag = true;
}

void AddWindowCommand::undo()
{
    if(m_bFlag)
    {
        m_bFlag = false;
        QString str     = "";
        QString stotal  = "";
        int     nTmp    = 0;

        int totalSceneNum   = pwnd->pSceneSheet.size();
        pwnd->nActiveSheetIndex = m_iActiveSheetIndex;
        pwnd->window->removeChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);//删除树控件点击的子菜单
        pwnd->pSceneSheet.remove(pwnd->nActiveSheetIndex);//删除场景中的数据
        pwnd->deleteScreen_upDateIndex();

        for(int i = pwnd->nActiveSheetIndex; i < totalSceneNum - 1; i++)
        {
            pwnd->newScreen[i] = pwnd->newScreen[i+1];
            QTreeWidgetItem *parentItem=pwnd->newScreen[i]->parent();//取后一个父类型
            if((parentItem != pwnd->TreeKeyboard) && (parentItem != pwnd->copyUserKeyboard))
            {
                //若不是为自定义键盘的话
                stotal = pwnd->newScreen[i]->text(0).split(":").at(0);
                nTmp   = stotal.toInt();
                stotal = QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
                str    = stotal + ":" + pwnd->newScreen[i]->text(0).split(":").at(1);
                pwnd->newScreen[i]->setText(0,str);
            }
        }

        if(!pwnd->label.isEmpty() && pwnd->nActiveSheetIndex < pwnd->label.size())
        {
            pwnd->label.remove(pwnd->nActiveSheetIndex);
        }
        if(!pwnd->titlelabel.isEmpty() && pwnd->nActiveSheetIndex < pwnd->titlelabel.size())
        {
            pwnd->titlelabel.remove(pwnd->nActiveSheetIndex);
        }
        if(!pwnd->priviewWidget.isEmpty() && pwnd->nActiveSheetIndex < pwnd->priviewWidget.size())
        {
            pwnd->priviewWidget.remove(pwnd->nActiveSheetIndex);
        }

        pwnd->DealWithDeleteScreen();//处理删除画面窗口自定义键盘的时候树形控件刷新问题

        QString strDest;
        QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
        pwnd->handleWinTitle(strDest, strtemp);
        pwnd->setWindowTitle(strDest);

        pwnd->upDatetreeScreenItem();//更新画面的子项
        pwnd->updateChScreen();
    }
}
/********************************************AddWindowCommand end*/

/********************************************DeleteWindowCommand start*/
DeleteWindowCommand::DeleteWindowCommand(SamDrawScene *samdrawscene, int iActiveSheetIndex, int iTreeIndex, bool bflag)
{
    Scene = samdrawscene;
    m_iActiveSheetIndex = iActiveSheetIndex;
    m_iTreeIndex = iTreeIndex;
    m_bFlag = bflag;
}

void DeleteWindowCommand::redo()
{
    if(m_bFlag)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    QString str     = "";
    QString stotal  = "";
    int     nTmp    = 0;

    int totalSceneNum   = pwnd->pSceneSheet.size();
    pwnd->nActiveSheetIndex = m_iActiveSheetIndex;
    pwnd->window->removeChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);//删除树控件点击的子菜单
    pwnd->pSceneSheet.remove(pwnd->nActiveSheetIndex);//删除场景中的数据
    pwnd->deleteScreen_upDateIndex();

    for(int i = pwnd->nActiveSheetIndex; i < totalSceneNum - 1; i++)
    {
        pwnd->newScreen[i] = pwnd->newScreen[i+1];
        QTreeWidgetItem *parentItem=pwnd->newScreen[i]->parent();//取后一个父类型
        if((parentItem != pwnd->TreeKeyboard) && (parentItem != pwnd->copyUserKeyboard))
        {
            //若不是为自定义键盘的话
            stotal = pwnd->newScreen[i]->text(0).split(":").at(0);
            nTmp   = stotal.toInt();
            stotal = QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
            str    = stotal + ":" + pwnd->newScreen[i]->text(0).split(":").at(1);
            pwnd->newScreen[i]->setText(0,str);
        }
    }

    if(!pwnd->label.isEmpty() && pwnd->nActiveSheetIndex < pwnd->label.size())
    {
        pwnd->label.remove(pwnd->nActiveSheetIndex);
    }
    if(!pwnd->titlelabel.isEmpty() && pwnd->nActiveSheetIndex < pwnd->titlelabel.size())
    {
        pwnd->titlelabel.remove(pwnd->nActiveSheetIndex);
    }
    if(!pwnd->priviewWidget.isEmpty() && pwnd->nActiveSheetIndex < pwnd->priviewWidget.size())
    {
        pwnd->priviewWidget.remove(pwnd->nActiveSheetIndex);
    }

    pwnd->DealWithDeleteScreen();//处理删除画面窗口自定义键盘的时候树形控件刷新问题

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    pwnd->handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);

    pwnd->upDatetreeScreenItem();//更新画面的子项
    pwnd->updateChScreen();
    m_bFlag = true;
}

void DeleteWindowCommand::undo()
{
    if(m_bFlag)
    {
        m_bFlag = false;
        QString str     = "";
        QString stotal  = "";
        int     nTmp    = 0;
        int iSheetNum = pwnd->pSceneSheet.size();
        pwnd->pSceneSheet.insert(m_iActiveSheetIndex, Scene);
        pwnd->nActiveSheetIndex = m_iActiveSheetIndex;
        pwnd->pView->setScene(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]);

        //wxy newScreen相应的插入一个
        for(int i = iSheetNum; i >pwnd->nActiveSheetIndex; i--)
        {
            pwnd->newScreen[i] = pwnd->newScreen[i-1];
            QTreeWidgetItem *parentItem=pwnd->newScreen[i]->parent();//取后一个父类型
            if(parentItem->text(0)!=QObject::tr("自定义键盘"))
            {
                //若不是为自定义键盘的话
                stotal=pwnd->newScreen[i]->text(0).split(":").at(0);
                nTmp=stotal.toInt();
                stotal=QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
                str=stotal+":"+pwnd->newScreen[i]->text(0).split(":").at(1);
                pwnd->newScreen[i]->setText(0,str);
            }
        }
        //wxy 创建时应该不指定parent结点，否则会加到最后面
        str = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNumberName;
        pwnd->newScreen[pwnd->nActiveSheetIndex] = new QTreeWidgetItem(/*pwnd->window,*/QStringList(str + ":" + pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
        pwnd->window->insertChild(m_iTreeIndex, pwnd->newScreen[pwnd->nActiveSheetIndex]);

        QString strDest;
        QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
        pwnd->handleWinTitle(strDest, strtemp);
        pwnd->setWindowTitle(strDest);

        pwnd->is_Save=false;//
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色

        pwnd->upDatetreeScreenItem();//更新画面的子项
        QString sTmp=pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(1);
        pwnd->updateChScreen();
        pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(pwnd->nActiveSheetIndex));
        pwnd->tree0->setFocus(Qt::MouseFocusReason);
        for(int j=0;j<pwnd->copyScreen_Item->childCount();j++)
        {
            QString sNo=pwnd->copyScreen_Item->child(j)->text(0).split(":").at(1);
            if(sTmp==sNo)
            {
                pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                pwnd->tree0->setFocus(Qt::ActiveWindowFocusReason);
            }
        }
    }
}

/********************************************DeleteWindowCommand end*/

/********************************************DeleteKeyBoardCommand start*/
DeleteKeyBoardCommand::DeleteKeyBoardCommand(SamDrawScene *samdrawscene, int iActiveSheetIndex, int iTreeIndex,QString strNum, bool bflag)
{
    Scene = samdrawscene;
    m_iActiveSheetIndex = iActiveSheetIndex;
    m_iTreeIndex = iTreeIndex;
    m_bFlag = bflag;
    m_strNum = strNum;
}

void DeleteKeyBoardCommand::redo()
{
    if(m_bFlag)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    QString str     = "";
    QString stotal  = "";
    int     nTmp    = 0;
    QStringList sNamelist;
    sNamelist.clear();

    pwnd->nActiveSheetIndex = m_iActiveSheetIndex;
    pwnd->TreeKeyboard->removeChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);//删除树控件点击的子菜单
    pwnd->pSceneSheet.remove(pwnd->nActiveSheetIndex);//删除场景中的数据
    pwnd->deleteScreen_upDateIndex();

    if(pwnd->m_pSamSysParame->nUserDefKeyboardCount > 0)
        pwnd->m_pSamSysParame->nUserDefKeyboardCount--;

    for(int i = 0; i< pwnd->pSceneSheet.size(); i++)
    {
        if(2 == pwnd->pSceneSheet[i]->nIsSceneOrWindow)
        {
            sNamelist.append(pwnd->pSceneSheet[i]->sNewScreenName);
        }
    }

    for(int i = 0; i < pwnd->m_pSamSysParame->m_qvcRecipe.size();i++)
    {
        if(pwnd->m_pSamSysParame->m_qvcRecipe[i].nKeyMark)
        {
            QString sname = pwnd->m_pSamSysParame->m_qvcRecipe[i].sKeyname;
            if(sNamelist.size() <= 0)
            {
                pwnd->m_pSamSysParame->m_qvcRecipe[i].nKeyMark = false;
                pwnd->m_pSamSysParame->m_qvcRecipe[i].nKeyId = 0;
                pwnd->m_pSamSysParame->m_qvcRecipe[i].sKeyname = "";
            }
            else
            {
                int index = sNamelist.indexOf(sname);
                if(index >= 0)
                {
                    pwnd->m_pSamSysParame->m_qvcRecipe[i].nKeyId = index;
                }
                else
                {
                    pwnd->m_pSamSysParame->m_qvcRecipe[i].nKeyId = 0;
                    pwnd->m_pSamSysParame->m_qvcRecipe[i].sKeyname = sNamelist.at(0);
                }
            }
        }
    }

    for(int i = 0; i< pwnd->pSceneSheet.size(); i++)
    {
        if(2 == pwnd->pSceneSheet[i]->nIsSceneOrWindow)
        {
            continue;
        }
        if(0 == pwnd->pSceneSheet[i]->nIsSceneOrWindow)
        {
            QList <QGraphicsItem *> items = pwnd->pSceneSheet[i]->TopItems();
            foreach(QGraphicsItem* pItem,items)
            {
                if(SAM_DRAW_OBJECT_GROUP == pItem->type())
                {
                    DataDisplayItem *itemgoup = dynamic_cast<DataDisplayItem *> (pItem);
                    if(!itemgoup)
                    {
                        continue;
                    }
                    if(SAM_DRAW_GROUP_VALUE  == itemgoup->GroupType()
                        || SAM_DRAW_GROUP_ASCII == itemgoup->GroupType())
                    {
                        QString sname = itemgoup->GetKeyboardName();
                        if(sNamelist.size() <= 0)
                        {
                            //自定义键盘不存在
                            itemgoup->SetKeyBoardInfo("",-1);
                        }
                        else
                        {
                            int index = sNamelist.indexOf(sname);
                            if(index >= 0)
                            {
                                itemgoup->SetKeyBoardInfo(sname,index);
                            }
                            else
                            {
                                itemgoup->SetKeyBoardInfo(sNamelist.at(0),0);
                            }
                        }
                    }
                }

            }
        }
    }

    int totalSceneNum = pwnd->pSceneSheet.size();//取总数
    for(int i=pwnd->nActiveSheetIndex;i<totalSceneNum;i++)
    {
        pwnd->newScreen[i]=pwnd->newScreen[i+1];
        QTreeWidgetItem *parentItem=pwnd->newScreen[i+1]->parent();//取后一个父类型
        if((parentItem==pwnd->TreeKeyboard)||(parentItem==pwnd->copyUserKeyboard))
        {//若为自定义键盘的话
            stotal=pwnd->newScreen[i]->text(0).split(":").at(0);
            nTmp=stotal.toInt()-1;
            stotal=QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
            str=stotal+":"+pwnd->newScreen[i]->text(0).split(":").at(1);
            pwnd->newScreen[i]->setText(0,str);
        }
    }

    if(pwnd->TreeKeyboard->childCount()<1)//当所有的用户自定义键盘都被删除时
    {
        pwnd->TreeKeyboard->setHidden(true);//隐藏树形控件的自定义键盘项
    }

    if(!pwnd->label.isEmpty() && pwnd->nActiveSheetIndex < pwnd->label.size())
    {
        pwnd->label.remove(pwnd->nActiveSheetIndex);
    }
    if(!pwnd->titlelabel.isEmpty() && pwnd->nActiveSheetIndex < pwnd->titlelabel.size())
    {
        pwnd->titlelabel.remove(pwnd->nActiveSheetIndex);
    }
    if(!pwnd->priviewWidget.isEmpty() && pwnd->nActiveSheetIndex < pwnd->priviewWidget.size())
    {
        pwnd->priviewWidget.remove(pwnd->nActiveSheetIndex);
    }

    pwnd->DealWithDeleteScreen();//处理删除画面窗口自定义键盘的时候树形控件刷新问题

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    pwnd->handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);

    pwnd->upDatetreeScreenItem();//更新画面的子项
    pwnd->updateChScreen();
    m_bFlag = true;
}

void DeleteKeyBoardCommand::undo()
{
    if(m_bFlag)
    {
        m_bFlag = false;
        QString str     = "";
        QString stotal  = "";
        int     nTmp    = 0;
        int iSheetNum = pwnd->pSceneSheet.size();

        pwnd->pSceneSheet.insert(m_iActiveSheetIndex, Scene);
        pwnd->nActiveSheetIndex = m_iActiveSheetIndex;
        pwnd->pView->setScene(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]);

        //wxy newScreen相应的插入一个
        for(int i = iSheetNum; i >pwnd->nActiveSheetIndex; i--)
        {
            pwnd->newScreen[i] = pwnd->newScreen[i-1];
            QTreeWidgetItem *parentItem=pwnd->newScreen[i]->parent();//取后一个父类型
            if((parentItem==pwnd->TreeKeyboard)||(parentItem==pwnd->copyUserKeyboard))
            {//若为自定义键盘的话
                stotal=pwnd->newScreen[i]->text(0).split(":").at(0);
                nTmp=stotal.toInt()+1;//wxy 增加的话值要加一
                stotal=QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
                str=stotal+":"+pwnd->newScreen[i]->text(0).split(":").at(1);
                pwnd->newScreen[i]->setText(0,str);
            }
        }

        //wxy 在树上添加结点
        int nscenecount=/*pwnd->pSceneSheet.size()-1*/m_iActiveSheetIndex;
        pwnd->newScreen[nscenecount]=new QTreeWidgetItem(/*pwnd->TreeKeyboard,*/QStringList(QObject::tr("")));

        //pwnd->newScreen[nscenecount]->setText(0,m_strNum+":"+QObject::tr("数字键盘")+QString("%1").arg(str.mid(4,1)));
        //pwnd->pSceneSheet[nscenecount]->sNewScreenName=QObject::tr("数字键盘")+QString("%1").arg(str.mid(4,1));
        //wxy 修改中文版本、英文版本长度不一样导致撤消后名字显示不正确
        pwnd->newScreen[nscenecount]->setText(0,m_strNum);
        pwnd->pSceneSheet[nscenecount]->sNewScreenName = m_strNum.right(m_strNum.length()-m_strNum.lastIndexOf(":")-1);
        pwnd->TreeKeyboard->insertChild(m_iTreeIndex, pwnd->newScreen[nscenecount]);

        pwnd->pSceneSheet[nscenecount]->sNewScreenName=pwnd->newScreen[nscenecount]->text(0).split(":").last();
        pwnd->m_pSamSysParame->nUserDefKeyboardCount++;
        pwnd->PreviewWindow();

        QString strDest;
        QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
        pwnd->handleWinTitle(strDest, strtemp);
        pwnd->setWindowTitle(strDest);

        pwnd->is_Save=false;//
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
        //emit  newscreen_Assign();

        pwnd->upDatetreeScreenItem();//更新画面的子项
        QString sTmp=pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(1);
        pwnd->updateChScreen();
        pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(pwnd->nActiveSheetIndex));
        pwnd->tree0->setFocus(Qt::MouseFocusReason);
        for(int j=0;j<pwnd->copyScreen_Item->childCount();j++)
        {
            QString sNo=pwnd->copyScreen_Item->child(j)->text(0).split(":").at(1);
            if(sTmp==sNo)
            {
                pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(j),0,QItemSelectionModel::SelectCurrent);
                pwnd->tree0->setFocus(Qt::ActiveWindowFocusReason);
            }
        }
    }
}

/********************************************DeleteKeyBoardCommand end*/

/********************************************AddKeyBoardCommand start*/
AddKeyBoardCommand::AddKeyBoardCommand(SamDrawScene *samdrawscene, int iActiveSheetIndex, int iTreeIndex,QString strNum, bool bflag)
{
    Scene = samdrawscene;
    m_iActiveSheetIndex = iActiveSheetIndex;
    m_iTreeIndex = iTreeIndex;
    m_bFlag = bflag;
    m_strNum = strNum;
}

void AddKeyBoardCommand::redo()
{
    if(m_bFlag)
    {
        pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);
        return;
    }
    QString str     = "";
    QString stotal  = "";
    int     nTmp    = 0;
    int iSheetNum = pwnd->pSceneSheet.size();

    pwnd->pSceneSheet.insert(m_iActiveSheetIndex, Scene);
    pwnd->nActiveSheetIndex = m_iActiveSheetIndex;
    pwnd->pView->setScene(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]);

    //wxy newScreen相应的插入一个
    for(int i = iSheetNum; i >pwnd->nActiveSheetIndex; i--)
    {
        pwnd->newScreen[i] = pwnd->newScreen[i-1];
        QTreeWidgetItem *parentItem=pwnd->newScreen[i]->parent();//取后一个父类型
        if((parentItem==pwnd->TreeKeyboard)||(parentItem==pwnd->copyUserKeyboard))
        {//若为自定义键盘的话
            stotal=pwnd->newScreen[i]->text(0).split(":").at(0);
            nTmp=stotal.toInt()+1;//wxy 增加的话值要加一
            stotal=QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
            str=stotal+":"+pwnd->newScreen[i]->text(0).split(":").at(1);
            pwnd->newScreen[i]->setText(0,str);
        }
    }

    //wxy 在树上添加结点
    int nscenecount=/*pwnd->pSceneSheet.size()-1*/m_iActiveSheetIndex;
    pwnd->newScreen[nscenecount]=new QTreeWidgetItem(/*pwnd->TreeKeyboard,*/QStringList(QObject::tr("")));

    //pwnd->newScreen[nscenecount]->setText(0,m_strNum+":"+QObject::tr("数字键盘")+QString("%1").arg(str.mid(4,1)));
    //pwnd->pSceneSheet[nscenecount]->sNewScreenName=QObject::tr("数字键盘")+QString("%1").arg(str.mid(4,1));
    //wxy 修改中文版本、英文版本长度不一样导致撤消后名字显示不正确
    pwnd->newScreen[nscenecount]->setText(0,m_strNum);
    pwnd->pSceneSheet[nscenecount]->sNewScreenName = m_strNum.right(m_strNum.length()-m_strNum.lastIndexOf(":")-1);
    pwnd->TreeKeyboard->insertChild(m_iTreeIndex, pwnd->newScreen[nscenecount]);

    pwnd->pSceneSheet[nscenecount]->sNewScreenName=pwnd->newScreen[nscenecount]->text(0).split(":").last();
    pwnd->m_pSamSysParame->nUserDefKeyboardCount++;
    pwnd->PreviewWindow();

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    pwnd->handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);

    pwnd->is_Save=false;//
    pwnd->is_NeedCompiled = true;
    pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
    //emit  newscreen_Assign();

    pwnd->upDatetreeScreenItem();//更新画面的子项
    QString sTmp=pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(1);
    pwnd->updateChScreen();
    pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(pwnd->nActiveSheetIndex));
    pwnd->tree0->setFocus(Qt::MouseFocusReason);
    for(int j=0;j<pwnd->copyScreen_Item->childCount();j++)
    {
        QString sNo=pwnd->copyScreen_Item->child(j)->text(0).split(":").at(1);
        if(sTmp==sNo)
        {
            pwnd->tree0->setCurrentItem(pwnd->copyScreen_Item->child(j),0,QItemSelectionModel::SelectCurrent);
            pwnd->tree0->setFocus(Qt::ActiveWindowFocusReason);
        }
    }
    m_bFlag = true;
}

void AddKeyBoardCommand::undo()
{
    if(m_bFlag)
    {
        m_bFlag = false;
        QString str     = "";
        QString stotal  = "";
        int     nTmp    = 0;
        QStringList sNamelist;
        sNamelist.clear();

        pwnd->nActiveSheetIndex = m_iActiveSheetIndex;
        pwnd->TreeKeyboard->removeChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);//删除树控件点击的子菜单
        pwnd->pSceneSheet.remove(pwnd->nActiveSheetIndex);//删除场景中的数据
        pwnd->deleteScreen_upDateIndex();

        if(pwnd->m_pSamSysParame->nUserDefKeyboardCount > 0)
            pwnd->m_pSamSysParame->nUserDefKeyboardCount--;

        for(int i = 0; i< pwnd->pSceneSheet.size(); i++)
        {
            if(2 == pwnd->pSceneSheet[i]->nIsSceneOrWindow)
            {
                sNamelist.append(pwnd->pSceneSheet[i]->sNewScreenName);
            }
        }

        for(int i = 0; i < pwnd->m_pSamSysParame->m_qvcRecipe.size();i++)
        {
            if(pwnd->m_pSamSysParame->m_qvcRecipe[i].nKeyMark)
            {
                QString sname = pwnd->m_pSamSysParame->m_qvcRecipe[i].sKeyname;
                if(sNamelist.size() <= 0)
                {
                    pwnd->m_pSamSysParame->m_qvcRecipe[i].nKeyMark = false;
                    pwnd->m_pSamSysParame->m_qvcRecipe[i].nKeyId = 0;
                    pwnd->m_pSamSysParame->m_qvcRecipe[i].sKeyname = "";
                }
                else
                {
                    int index = sNamelist.indexOf(sname);
                    if(index >= 0)
                    {
                        pwnd->m_pSamSysParame->m_qvcRecipe[i].nKeyId = index;
                    }
                    else
                    {
                        pwnd->m_pSamSysParame->m_qvcRecipe[i].nKeyId = 0;
                        pwnd->m_pSamSysParame->m_qvcRecipe[i].sKeyname = sNamelist.at(0);
                    }
                }
            }
        }

        for(int i = 0; i< pwnd->pSceneSheet.size(); i++)
        {
            if(2 == pwnd->pSceneSheet[i]->nIsSceneOrWindow)
            {
                continue;
            }
            if(0 == pwnd->pSceneSheet[i]->nIsSceneOrWindow)
            {
                QList <QGraphicsItem *> items = pwnd->pSceneSheet[i]->TopItems();
                foreach(QGraphicsItem* pItem,items)
                {
                    if(SAM_DRAW_OBJECT_GROUP == pItem->type())
                    {
                        DataDisplayItem *itemgoup = dynamic_cast<DataDisplayItem *> (pItem);
                        if(!itemgoup)
                        {
                            continue;
                        }
                        if(SAM_DRAW_GROUP_VALUE  == itemgoup->GroupType()
                            || SAM_DRAW_GROUP_ASCII == itemgoup->GroupType())
                        {
                            QString sname = itemgoup->GetKeyboardName();
                            if(sNamelist.size() <= 0)
                            {
                                //自定义键盘不存在
                                itemgoup->SetKeyBoardInfo("",-1);
                            }
                            else
                            {
                                int index = sNamelist.indexOf(sname);
                                if(index >= 0)
                                {
                                    itemgoup->SetKeyBoardInfo(sname,index);
                                }
                                else
                                {
                                    itemgoup->SetKeyBoardInfo(sNamelist.at(0),0);
                                }
                            }
                        }
                    }

                }
            }
        }

        int totalSceneNum = pwnd->pSceneSheet.size();//取总数
        for(int i=pwnd->nActiveSheetIndex;i<totalSceneNum;i++)
        {
            pwnd->newScreen[i]=pwnd->newScreen[i+1];
            QTreeWidgetItem *parentItem=pwnd->newScreen[i+1]->parent();//取后一个父类型
            if((parentItem==pwnd->TreeKeyboard)||(parentItem==pwnd->copyUserKeyboard))
            {//若为自定义键盘的话
                stotal=pwnd->newScreen[i]->text(0).split(":").at(0);
                nTmp=stotal.toInt()-1;
                stotal=QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
                str=stotal+":"+pwnd->newScreen[i]->text(0).split(":").at(1);
                pwnd->newScreen[i]->setText(0,str);
            }
        }

        if(pwnd->TreeKeyboard->childCount()<1)//当所有的用户自定义键盘都被删除时
        {
            pwnd->TreeKeyboard->setHidden(true);//隐藏树形控件的自定义键盘项
        }

        if(!pwnd->label.isEmpty() && pwnd->nActiveSheetIndex < pwnd->label.size())
        {
            pwnd->label.remove(pwnd->nActiveSheetIndex);
        }
        if(!pwnd->titlelabel.isEmpty() && pwnd->nActiveSheetIndex < pwnd->titlelabel.size())
        {
            pwnd->titlelabel.remove(pwnd->nActiveSheetIndex);
        }
        if(!pwnd->priviewWidget.isEmpty() && pwnd->nActiveSheetIndex < pwnd->priviewWidget.size())
        {
            pwnd->priviewWidget.remove(pwnd->nActiveSheetIndex);
        }

        pwnd->DealWithDeleteScreen();//处理删除画面窗口自定义键盘的时候树形控件刷新问题

        QString strDest;
        QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
        pwnd->handleWinTitle(strDest, strtemp);
        pwnd->setWindowTitle(strDest);

        pwnd->upDatetreeScreenItem();//更新画面的子项
        pwnd->updateChScreen();
    }
}

tableMovedCommand::tableMovedCommand(SamDrawScene *samdrawscene,QGraphicsItem *movedItem,
                   QList<QRectF >nRects,QList<QRectF >oRects,bool bflag)
{
    //qDebug() << "tableMovedCommand";
    Scene = samdrawscene;
    m_movedItem = movedItem;
    oItemRects = oRects;
    nItemRects = nRects;
    b_flag = bflag;
}

void tableMovedCommand::redo()
{
    if(m_movedItem)
    {
        QList<QGraphicsItem *>childitems = m_movedItem->childItems();
        if(childitems.size() == nItemRects.size())
        {
            int i = 0;
            foreach(QGraphicsItem *item,childitems)
            {
                QGroupItem gfun(item);
                gfun.SetWidth(nItemRects[i].width());
                gfun.SetHeigth(nItemRects[i].height());
                item->setPos(nItemRects[i].topLeft());
                i++;
            }
            m_movedItem->setSelected(true);
            Scene->update();
            pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
            pwnd->is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
        }
    }


    //update_edgepoints(Scene,nItem);
    //nItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    //nItem->setFlag(QGraphicsItem::ItemIsMovable, true);

}
void tableMovedCommand::undo()
{
    if(m_movedItem)
    {
        QList<QGraphicsItem *>childitems = m_movedItem->childItems();
        if(childitems.size() == oItemRects.size())
        {
            int i=0;
            foreach(QGraphicsItem *item,childitems)
            {
                QGroupItem gfun(item);
                gfun.SetWidth(oItemRects[i].width());
                gfun.SetHeigth(oItemRects[i].height());
                item->setPos(oItemRects[i].topLeft());
                i++;
            }
            m_movedItem->setSelected(true);
            Scene->update();
            pwnd->is_Save=false;// 画面改变 同时来改变保存按钮的颜色
            pwnd->is_NeedCompiled = true;
            pwnd->ui->action_save->setDisabled(false);
        }
    }
}

/********************************************AddKeyBoardCommand end*/
