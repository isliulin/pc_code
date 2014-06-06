#include "ImageItem.h"
#include "Frame/mainwindow.h"
#include <QGraphicsScene>

extern MainWindow *pwnd;

ImageItem::ImageItem():QVisableItem(0)
{

}

void ImageItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    int nAdrrID;
    count++;
    QVisableItem::compile(db, nSceneId, count,index);
    int nItemID = count;

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

    if(0 != m_SaveInfo.nChangeCondition)
    {
        count++;
        ADDR_PARAMENTS stParams;
        stParams.id = count;
        stParams.itemId = nItemID;
        stParams.eType = OBJ_ITEM;
        stParams.addrNum = -1;
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
		//修改地址编译参数
        m_SaveInfo.addr.compile(db,stParams);
        nAdrrID = count;
    }

    onGetPosition();

    bool bflag;
    QSqlQuery sqlquery(db);

    bflag = sqlquery.prepare("INSERT INTO imageShow(nItemId, nSceneId, nLp, nTp, nWidth,"
                      "nHeight, nFunType, bUseFlicker, nBackColor, nChangeCondition,"
                      "nWatchAddr, nStatusTotal, nTimeInterval, bIsLoopType, nOrigWidth, nOrigHeight,nIsBitCtrl,nValidBit,nCtrlAddr,nRCount, nZvalue, nCollidindId)"
                      "VALUES (:nItemId, :nSceneId, :nLp, :nTp, :nWidth,"
                      ":nHeight, :nFunType, :bUseFlicker, :nBackColor, :nChangeCondition,"
                      ":nWatchAddr, :nStatusTotal, :nTimeInterval, :bIsLoopType, :nOrigWidth, :nOrigHeight, :nIsBitCtrl,:nValidBit,:nCtrlAddr,:nRCount,:nZvalue, :nCollidindId)");
    sqlquery.bindValue(":nItemId",QVariant(nItemID));
    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));
    sqlquery.bindValue(":nLp",QVariant(m_SaveInfo.nLp));
    sqlquery.bindValue(":nTp",QVariant(m_SaveInfo.nTp));
    sqlquery.bindValue(":nWidth",QVariant(m_SaveInfo.nWidth));
    sqlquery.bindValue(":nHeight",QVariant(m_SaveInfo.nHeight));
    sqlquery.bindValue(":nFunType",QVariant(m_SaveInfo.nFunType));
    sqlquery.bindValue(":bUseFlicker",QVariant(m_SaveInfo.bUseFlicker));
    //sqlquery.bindValue(":nBackColor",QVariant(ColorToInt(m_SaveInfo.nBackColor)));
    sqlquery.bindValue(":nChangeCondition",QVariant(m_SaveInfo.nChangeCondition));
    if(0 != m_SaveInfo.nChangeCondition)
    {
        sqlquery.bindValue(":nWatchAddr",QVariant(nAdrrID));
    }
    else
    {
        sqlquery.bindValue(":nWatchAddr",QVariant(-1));
    }
    sqlquery.bindValue(":nStatusTotal",QVariant(m_SaveInfo.nStatusTotal));
    sqlquery.bindValue(":nTimeInterval",QVariant(m_SaveInfo.nTimeInterval*100));
    sqlquery.bindValue(":bIsLoopType",QVariant(m_SaveInfo.bIsLoopType));
    sqlquery.bindValue(":nOrigWidth",QVariant(0));//保存0用来区分图片显示器和GIF，0：表示图片 大于0表示GIF ，Ps下位用
    sqlquery.bindValue(":nOrigHeight",QVariant(0));
    sqlquery.bindValue(":nZvalue",QVariant(zValue()));
    sqlquery.bindValue(":nCollidindId",QVariant(index));
    //sqlquery.bindValue(":nShowPropId",QVariant(count));
    bflag = sqlquery.exec();

    for(int i = 0; i < m_PicInfo.size(); i++)
    {
        if("" == m_PicInfo[i].name )
        {
            continue;
        }
        QSqlQuery sqlImagePathquery(db);
        bflag = sqlImagePathquery.prepare("INSERT INTO imagePath(nItemId, nSceneId, nStatusId, nCmpFactor, sPicPath)"
                          "VALUES (:nItemId, :nSceneId, :nStatusId, :nCmpFactor, :sPicPath)");
        sqlImagePathquery.bindValue(":nItemId",QVariant(nItemID));
        sqlImagePathquery.bindValue(":nSceneId",QVariant(nSceneId));
        sqlImagePathquery.bindValue(":nStatusId",QVariant(i));//关联的状态
        sqlImagePathquery.bindValue(":nCmpFactor",QVariant(m_PicInfo[i].nCmpFactor));//预设固定值
        bool bPic = false;
        if(0 == m_PicInfo[i].bIspic || USERDEFINE == m_PicInfo[i].bIspic)
        {
            bPic = false;
        }
        else
        {
            bPic = true;
        }
        QString newPath = pwnd->SavePath(m_PicInfo[i].path,boundingRect().size(),bPic);
        if("" != newPath)
        {
            newPath = newPath.replace("\\","/");
            newPath = newPath.section("/",-1);
            newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
        }
        sqlImagePathquery.bindValue(":sPicPath",QVariant(newPath));
        bflag = sqlImagePathquery.exec();
    }

}

QGraphicsItem *ImageItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    ImageItem *itemGroup = new ImageItem();

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
    itemGroup->onSetCurrentNum(onGetCurrentNum());
    itemGroup->m_SaveInfo = m_SaveInfo;
    itemGroup->SaveSecurityPro(&sPro);
    itemGroup->setId(id());
    if(itemGroup->childItems().size() == 0)
    {
        //delete itemGroup;
        //itemGroup = NULL;
    }

    return itemGroup;
}

int ImageItem::GroupType()
{
    return SAM_DRAW_GROUP_IMAGE;
}

void ImageItem::save(QDataStream &stream)
{
    QVisableItem::save(stream);

    stream << number;
    stream << m_SaveInfo.nFunType;
    stream << m_SaveInfo.bUseFlicker;
    stream << m_SaveInfo.nChangeCondition;
    stream << m_SaveInfo.mWatchAddr;
    stream << m_SaveInfo.addr;
    stream << m_SaveInfo.nStatusTotal;
    stream << m_SaveInfo.nTimeInterval;
    //stream << m_SaveInfo.nPicType;
    stream << m_SaveInfo.bIsLoopType;
    stream << m_SaveInfo.nCmpFactor;
    //stream << m_SaveInfo.nBackColor;

    int nPicNum = m_PicInfo.size();
    stream << nPicNum;
    for(int i = 0; i < nPicNum; i++)
    {
        stream << m_PicInfo[i].name;
        stream << m_PicInfo[i].path;
        int nType = int(m_PicInfo[i].bIspic);
        stream << nType;
        stream << m_PicInfo[i].nCmpFactor;
    }
}
void ImageItem::load(QDataStream &stream)
{
    QVisableItem::load(stream);

    stream >> number;
    stream >> m_SaveInfo.nFunType;
    stream >> m_SaveInfo.bUseFlicker;
    stream >> m_SaveInfo.nChangeCondition;
    stream >> m_SaveInfo.mWatchAddr;
    stream >> m_SaveInfo.addr;
    stream >> m_SaveInfo.nStatusTotal;
    stream >> m_SaveInfo.nTimeInterval;
    //stream >> m_SaveInfo.nPicType;
    stream >> m_SaveInfo.bIsLoopType;
    stream >> m_SaveInfo.nCmpFactor;
    //stream >> m_SaveInfo.nBackColor;

    int nPicNum = 0;
    stream >> nPicNum;
    m_PicInfo.resize(nPicNum);
    for(int i = 0; i < nPicNum; i++)
    {
        stream >> m_PicInfo[i].name;
        stream >> m_PicInfo[i].path;
        int nType = 0;
        stream >> nType;
        m_PicInfo[i].bIspic = EITEM_TYPE(nType);
        stream >> m_PicInfo[i].nCmpFactor;
    }
}

void ImageItem::onSavePicInfo(INTOSAVE picInfo)
{
    m_SaveInfo = picInfo;
}

int ImageItem::onGetCurrentNum()
{
    return number;
}

void ImageItem::onSetCurrentNum(short int num)
{
    number = num;
}

void ImageItem::onGetPosition()
{
    QRectF oldpos = sceneBoundingRect();
    m_SaveInfo.nLp = oldpos.topLeft().x();
    m_SaveInfo.nTp = oldpos.topLeft().y();
    m_SaveInfo.nWidth = oldpos.width();
    m_SaveInfo.nHeight = oldpos.height();
}

void ImageItem::redrawForChangeStatus(int index, int lan)
{
    int totalState = this->getItemStates().size();
    if(totalState <= index)
    {
        return;//目前没有这个状态
    }

    qDebug()<<"into selected:"<<this->GetselectFlag();
    if(index >= m_PicInfo.size()) //|| index == this->onGetCurrentNum())
    {
        return;
    }
    if("" == m_PicInfo[index].name)
    {
        return;
    }
    QGraphicsItem *pNewItem = NULL;
    QGraphicsItem *pOldItem = NULL;
    DrawItemToScene GroupFunction;
    QString sPath = m_PicInfo[index].path;

    foreach(QGraphicsItem * pItem, this->childItems())
    {
        if(SAM_DRAW_OBJECT_PIXMAP == pItem->type() || LIBRARY_LIB_GROUP == pItem->data(GROUP_TYPE_KEY).toInt())
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
    if(LIBRARY == m_PicInfo[index].bIspic)
    {
        QList <QGraphicsItem*> listItem;
        QStringList str = sPath.split('-');
        if(str.isEmpty())
        {
            return;
        }
        int nLoadPag = str.at(0).toInt();
        if(pwnd->vBaseLibraryScene.isEmpty())
        {
            return;
        }
        listItem = pwnd->vBaseLibraryScene.at(nLoadPag)->TopItems();
        foreach (QGraphicsItem * pItem, listItem)
        {
            QString sname = pItem->data(GROUP_NAME_KEY).toString();
            if (sPath == sname)
            {
                GroupFunction.CopyItem(&pNewItem,pItem);
                QGroupItem *pBase = new QGroupItem(pNewItem);
                pBase->SetWidth(rect.width());
                pBase->SetHeigth(rect.height());
                break;
            }
        }
    }
    else if(PIC == m_PicInfo[index].bIspic || USERDEFINE == m_PicInfo[index].bIspic)
    {
        QPixmap picture = QPixmap(m_PicInfo[index].path);
        QPixmapItem *PicItem = new QPixmapItem(picture,QSize(rect.width(),rect.height()));
        pNewItem = PicItem;
    }
    if(pNewItem )
    {
        pNewItem->setFlag(QGraphicsItem::ItemIsMovable,true);
        pNewItem->setFlag(QGraphicsItem::ItemIsSelectable,false);
        //this->removeFromGroup(pOldItem);

        QGraphicsItem *pItem = this->topLevelItem();
        QItemGroup *pArentItem = dynamic_cast<QItemGroup *> (pItem);
        if(pArentItem)
        {
            pArentItem->removeFromGroup(pOldItem);
        }

        QGraphicsScene *pScence = this->scene();
        pNewItem->setPos(rect.topLeft() - pNewItem->boundingRect().topLeft());
        this->addToGroup(pNewItem);
        this->onSetCurrentNum(index);
        if(pScence)
        pScence->removeItem(pOldItem);
    }
    qDebug()<<"end selected:"<<this->GetselectFlag();
}

int ImageItem::getCurrentState()
{
    return number;
}

QStringList ImageItem::getItemStates()
{
    QStringList ls;
    ls.clear();
    for(int i = 0; i < m_PicInfo.size(); i++)
    {
        ls.append(QString("%1").arg(i));
    }
    return ls;
}

QVector<ADDRPRO> ImageItem::getAllItemAddr()
{
    lsX.clear();
    ADDRPRO Addr;

    if(0 != m_SaveInfo.nChangeCondition)
    {
        Addr.pAddr = &m_SaveInfo.addr;
        Addr.str   = QObject::tr("图片显示器监视地址");
        if(1 == m_SaveInfo.nChangeCondition)
        {
            Addr.type  = 0;
        }
        else if(2 == m_SaveInfo.nChangeCondition)
        {
            Addr.type  = 1;
        }
        lsX << Addr;
    }

    QVector<ADDRPRO> AddrList;
    AddrList = QVisableItem::getAllItemAddr();
    for(int i = 0; i < AddrList.size(); i++)
    {
        Addr.pAddr = AddrList.at(i).pAddr;
        Addr.str   = QObject::tr("图片显示器") + AddrList.at(i).str;
        Addr.type  = AddrList.at(i).type;
        lsX << Addr;
    }
    return lsX;
}
//获得操作地址
QList<Keyboard> ImageItem::getAddress()
{
    QList<Keyboard> addrs;
    if(m_SaveInfo.nFunType == 1 && (m_SaveInfo.nChangeCondition != 0))
    {
        addrs << m_SaveInfo.addr;
    }
    return addrs;
}
//设置操作地址
void ImageItem::setAddress(QList<Keyboard> addr)
{
    if (addr.size() <= 0)
        return ;
    if(m_SaveInfo.nFunType == 1 && (m_SaveInfo.nChangeCondition != 0))
    {
        m_SaveInfo.addr = addr.first();
        m_SaveInfo.mWatchAddr = m_SaveInfo.addr.sShowAddr;
    }
}

QString  ImageItem::getItemName()
{
    return QObject::tr("图片显示器");
}
