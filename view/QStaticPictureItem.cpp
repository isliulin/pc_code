#include "QStaticPictureItem.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

QStaticPictureItem::QStaticPictureItem(QGraphicsItem *parent):QVisableItem(parent)
{
}

int QStaticPictureItem::GroupType()
{
    return SAM_DRAW_GROUP_STATICPIC;
}

QGraphicsItem *QStaticPictureItem::Clone()//复制item
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    QStaticPictureItem *itemGroup = new QStaticPictureItem();

    QList<QGraphicsItem *> itemList;
    itemList = childItems();
    int size = itemList.size();

    for(int i=0;i<size;i++)
    {
        pItem = itemList.at(i);

        switch(pItem->type())
        {
        case SAM_DRAW_OBJECT_RECT:              //矩形
            {
                QRectItem *rectItem = dynamic_cast<QRectItem *>(pItem);
                if(rectItem)
                {
                    pCopy = rectItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_ELIPSE:              //圆
            {
                QElipseItem *elipseItem = dynamic_cast<QElipseItem *>(pItem);
                if(elipseItem)
                {
                    pCopy = elipseItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_LINE:                 //直线
            {
                QLineItem * lineItem = dynamic_cast<QLineItem *>(pItem);
                if(lineItem)
                {
                    pCopy = lineItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_POLYGON:              //多边形
            {
                QPolygonItem *polygonItem = dynamic_cast<QPolygonItem *>(pItem);
                if(polygonItem)
                {
                    pCopy = polygonItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_FOLDLINE:             //19
            {
                QFoldLineItem *foldlineItem = dynamic_cast<QFoldLineItem *>(pItem);
                if(foldlineItem)
                {
                    pCopy = foldlineItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_FREELINE:             //20
            {
                QFreeLineItem * freelineItem = dynamic_cast<QFreeLineItem *>(pItem);
                if(freelineItem)
                {
                    pCopy = freelineItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_TEXT:                 //22
            {
                QSimpleTextItem * textItem = dynamic_cast<QSimpleTextItem *>(pItem);
                if(textItem)
                {
                    pCopy = textItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_PIXMAP:
            {

                QPixmapItem *pixmapItem = dynamic_cast<QPixmapItem *>(pItem);
                if(pixmapItem)
                {
                    pCopy = pixmapItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_LINECIRCLE:           //25
            {
                QLineCircleItem *circleItem = dynamic_cast<QLineCircleItem *>(pItem);
                if(circleItem)
                {
                    pCopy = circleItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
            {
                QRoundedRect *roundedrectItem = dynamic_cast<QRoundedRect *>(pItem);
                if(roundedrectItem)
                {
                    pCopy = roundedrectItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_ARC:
            {
                QArcItem *arcItem = dynamic_cast<QArcItem *>(pItem);
                if(arcItem)
                {
                    pCopy = arcItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_GROUP:                //23
            {

                QItemGroup *group = dynamic_cast<QItemGroup *>(pItem);
                if(group)
                {
                    pCopy = group->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        default:
            break;
        }
        if(pCopy)
            pCopy->setFlag(QGraphicsItem::ItemIsSelectable,false);

    }

    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    itemGroup->setData(GROUP_TYPE_KEY,data(GROUP_TYPE_KEY).toInt());

    itemGroup->m_PicInfo = m_PicInfo;
    itemGroup->SaveSecurityPro(&sPro);
    itemGroup->setId(id());
    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }
    return itemGroup;
}

void QStaticPictureItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)//编译的时候保存item到数据库
{
    count++;
    QVisableItem::compile(db, nSceneId, count,index);
    int itemId = count;

    if(sPro.enableTouch && !sPro.byGroups_T)
    {
        //触控受位控制 增一个地址表
        count++;
    }
    if(sPro.bNotice)
    {
        //触控解锁通知到地址 增加一个地址表
        count++;
    }
    if(sPro.enableVisable && !sPro.byGroups_V)
    {
        //显现受位控制 增加一个地址表
        count++;
    }

    QSqlQuery sqlquery(db);

    QRectF rect = sceneBoundingRect();

    sqlquery.prepare("INSERT INTO imageShow(nItemId, nSceneId, nLp, nTp, nWidth,"
                          "nHeight, nFunType, bUseFlicker, nBackColor, nChangeCondition,"
                          "nWatchAddr, nStatusTotal, nTimeInterval, bIsLoopType, nOrigWidth, nOrigHeight, nIsBitCtrl,nValidBit,nCtrlAddr,nRCount,nZvalue, nCollidindId)"
                          "VALUES (:nItemId, :nSceneId, :nLp, :nTp, :nWidth,"
                          ":nHeight, :nFunType, :bUseFlicker, :nBackColor, :nChangeCondition,"
                          ":nWatchAddr, :nStatusTotal, :nTimeInterval, :bIsLoopType, :nOrigWidth, :nOrigHeight,:nIsBitCtrl,:nValidBit,:nCtrlAddr,:nRCount, :nZvalue, :nCollidindId)");

    sqlquery.bindValue(":nItemId",QVariant(itemId));
    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));
    sqlquery.bindValue(":nLp",QVariant(rect.x()));
    sqlquery.bindValue(":nTp",QVariant(rect.y()));
    sqlquery.bindValue(":nWidth",QVariant(rect.width()));
    sqlquery.bindValue(":nHeight",QVariant(rect.height()));
    sqlquery.bindValue(":nBackColor",QVariant(0));
    sqlquery.bindValue(":nOrigWidth",QVariant(m_PicInfo.nOrigWidth));
    sqlquery.bindValue(":nOrigHeight",QVariant(m_PicInfo.nOrigHeight));
    sqlquery.bindValue(":nIsBitCtrl",QVariant(m_PicInfo.nIsBitCtrl));
    if(1 == m_PicInfo.nIsBitCtrl)
    {
        count++;
        ADDR_PARAMENTS stParams;
        stParams.id = count;
        stParams.itemId = itemId;
        stParams.eType = OBJ_ITEM;
        stParams.addrNum = -1;
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
        m_PicInfo.CtrlAddr.Length = 1;
                //修改地址编译参数
        m_PicInfo.CtrlAddr.compile(db,stParams);
        sqlquery.bindValue(":nValidBit",QVariant(m_PicInfo.nValidBit));
        sqlquery.bindValue(":nCtrlAddr",QVariant(count));
    }
    sqlquery.bindValue(":nRCount",QVariant(m_PicInfo.nRCount));
    sqlquery.bindValue(":nZvalue",QVariant(zValue()));
    sqlquery.bindValue(":nCollidindId",QVariant(index));

    sqlquery.exec();

    sqlquery.prepare("INSERT INTO imagePath(nItemId, nSceneId, nStatusId, nCmpFactor, sPicPath)"
                              "VALUES (:nItemId, :nSceneId, :nStatusId, :nCmpFactor, :sPicPath)");

    sqlquery.bindValue(":nItemId",QVariant(itemId));
    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));

    QString newPath = pwnd->SavePath(m_PicInfo.sPicPath,boundingRect().size(),false);
    if("" != newPath)
    {
        newPath = newPath.replace("\\","/");
        newPath = newPath.section("/",-1);
        newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
    }
    sqlquery.bindValue(":sPicPath",QVariant(newPath));
    sqlquery.exec();


}

void QStaticPictureItem::save(QDataStream &stream)//将item存入数据流
{
    QVisableItem::save(stream);

    stream << m_PicInfo.nIsBitCtrl;
    stream << m_PicInfo.nValidBit;
    stream << m_PicInfo.sCtrlAddr;
    stream << m_PicInfo.CtrlAddr;
    stream << m_PicInfo.sPicPath;
    stream << m_PicInfo.nOrigHeight;
    stream << m_PicInfo.nOrigWidth;
    stream << m_PicInfo.nRCount;
}

void QStaticPictureItem::load(QDataStream &stream)//从数据流导出item
{
    QVisableItem::load(stream);

    stream >> m_PicInfo.nIsBitCtrl;
    stream >> m_PicInfo.nValidBit;
    stream >> m_PicInfo.sCtrlAddr;
    stream >> m_PicInfo.CtrlAddr;
    stream >> m_PicInfo.sPicPath;
    stream >> m_PicInfo.nOrigHeight;
    stream >> m_PicInfo.nOrigWidth;
    if (pwnd->getProVersion() < 2389)
    {
        m_PicInfo.nRCount = 0;
    }
    else
    {
        stream >> m_PicInfo.nRCount;
    }

}

QVector<ADDRPRO> QStaticPictureItem::getAllItemAddr()
{
    lsX.clear();
    ADDRPRO Addr;

    if(1 == m_PicInfo.nIsBitCtrl)
    {
        Addr.pAddr = &m_PicInfo.CtrlAddr;
        Addr.str   = QObject::tr("GIF显示器位控制地址");
        Addr.type  = 0;
        lsX << Addr;
    }

    QVector<ADDRPRO> AddrList;
    AddrList = QVisableItem::getAllItemAddr();
    for(int i = 0; i < AddrList.size(); i++)
    {
        Addr.pAddr = AddrList.at(i).pAddr;
        Addr.str   = QObject::tr("GIF显示器") + AddrList.at(i).str;
        Addr.type  = AddrList.at(i).type;
        lsX << Addr;
    }
    return lsX;
}

QString  QStaticPictureItem::getItemName()
{
    return QObject::tr("GIF显示器");
}

void QStaticPictureItem::redrawForChangeStatus(int index, int lan)
{

    if("" == m_PicInfo.sPicPath)
    {
        return;
    }
    QGraphicsItem *pNewItem = NULL;
    QGraphicsItem *pOldItem = NULL;
    foreach(QGraphicsItem *pItem,this->childItems())
    {
        if(SAM_DRAW_OBJECT_PIXMAP == pItem->type())
        {
            pOldItem = pItem;
            break;
        }
    }

    if(!pOldItem)
    {
        return;
    }

    QRectF rect = pOldItem->sceneBoundingRect();
    QPixmap picture = QPixmap(m_PicInfo.sPicPath);
    if (!picture)
    {
       return ;
    }
    QPixmapItem *PicItem = new QPixmapItem(picture,QSize(rect.width(),rect.height()));
    pNewItem = PicItem;

    pNewItem->setPos(rect.topLeft() - pNewItem->boundingRect().topLeft());

    //this->removeFromGroup(pOldItem);

    QGraphicsItem *pItem = this->topLevelItem();
    QItemGroup *pArentItem = dynamic_cast<QItemGroup *> (pItem);
    if(pArentItem)
    {
        pArentItem->removeFromGroup(pOldItem);
    }

    this->addToGroup(pNewItem);
    if(this->scene())
    {
        this->scene()->removeItem(pOldItem);
    }
}
