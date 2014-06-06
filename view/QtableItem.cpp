
#include "Frame/mainwindow.h"
#include "QtableItem.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;


QTableItem::QTableItem(QGraphicsItem *parent)
    :QVisableItem(parent)
{

}

int QTableItem::GroupType()//控件类型 位开关 字开关
{
    return SAM_DRAW_GROUP_TABLE;
}
QString QTableItem::getItemName()
{
    return QObject::tr("表格");
}

QGraphicsItem *QTableItem::Clone()//复制item
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    QTableItem *itemGroup = new QTableItem();

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

    itemGroup->SaveSecurityPro(&this->sPro);
    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    itemGroup->setData(GROUP_TYPE_KEY,data(GROUP_TYPE_KEY).toInt());
    itemGroup->m_Table = m_Table;
    itemGroup->setId(id());

    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }
    return itemGroup;
}

void QTableItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)//编译的时候保存item到数据库
{
    count++;
    int itemId = count;
    QRectF rect = this->sceneBoundingRect();
    /*QItemGroup*/QVisableItem::compile(db,nSceneId,count, index);

    QSqlQuery sqlquery(db);

    sqlquery.prepare("INSERT INTO tableShow(nItemId ,nSceneId ,nOrientationCount ,nPortraitCount ,bShowFrameLine,"
                     "bShowOrientationLine ,bShowPortraitCount ,nBackColor ,nTableWidth ,nTableHeight ,"
                     "nLeftTopX ,nLeftTopY ,nWShowColor ,eNLineType ,nNShowColor ,nTransparent ,"
                     "nZvalue ,nCollidindId, bHControl, nAddrHControl, bVControl, nAddrVControl)"
                     "VALUES (:nItemId ,:nSceneId ,:nOrientationCount ,:nPortraitCount ,:bShowFrameLine,"
                     ":bShowOrientationLine ,:bShowPortraitCount ,:nBackColor ,:nTableWidth ,:nTableHeight ,"
                     ":nLeftTopX ,:nLeftTopY ,:nWShowColor ,:eNLineType ,:nNShowColor ,:nTransparent ,"
                     ":nZvalue ,:nCollidindId , :bHControl, :nAddrHControl, :bVControl, :nAddrVControl)");

    sqlquery.bindValue(":nItemId",QVariant(itemId));
    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));
    sqlquery.bindValue(":nOrientationCount",QVariant(m_Table.nOrientationCount));
    sqlquery.bindValue(":nPortraitCount",QVariant(m_Table.nPortraitCount));
    sqlquery.bindValue(":bShowFrameLine",QVariant(m_Table.bShowFrameLine));
    sqlquery.bindValue(":bShowOrientationLine",QVariant(m_Table.bShowOrientationLine));
    sqlquery.bindValue(":bShowPortraitCount",QVariant(m_Table.bShowPortraitCount));
    sqlquery.bindValue(":nBackColor",QVariant(ColorToInt(m_Table.nBackColor)));
    sqlquery.bindValue(":nTableWidth",QVariant(rect.width()));
    sqlquery.bindValue(":nTableHeight",QVariant(rect.height()));
    sqlquery.bindValue(":nLeftTopX",QVariant(rect.x()));
    sqlquery.bindValue(":nLeftTopY",QVariant(rect.y()));
    sqlquery.bindValue(":nWShowColor",QVariant(ColorToInt(m_Table.nFramecolor)));
    sqlquery.bindValue(":eNLineType",QVariant(m_Table.eNLineType + 1));
    sqlquery.bindValue(":nNShowColor",QVariant(ColorToInt(m_Table.nWShowColor)));
    sqlquery.bindValue(":nTransparent",QVariant(ColorToInt(m_Table.nTransparent)));
    sqlquery.bindValue(":nZvalue",QVariant(zValue()));
    sqlquery.bindValue(":nCollidindId",QVariant(index));

    //add by wxy
    sqlquery.bindValue(":bHControl", QVariant(m_Table.bHDynamicControl));
    if(m_Table.bHDynamicControl)
    {
        count++;
        ADDR_PARAMENTS stParams;
        stParams.id = count;
        stParams.itemId = itemId;
        stParams.eType = OBJ_ITEM;
        stParams.addrNum = -1;
        stParams.eRWtype = SCENE_CONTROL_ONCE_R;
        m_Table.addrHDynamic.compile(db,stParams);//插入地址表
    }
    sqlquery.bindValue(":nAddrHControl", QVariant(count));

    sqlquery.bindValue(":bVControl", QVariant(m_Table.bVDynamicControl));
    if(m_Table.bVDynamicControl)
    {
        count++;
        ADDR_PARAMENTS stParams;
        stParams.id = count;
        stParams.itemId = itemId;
        stParams.eType = OBJ_ITEM;
        stParams.addrNum = -1;
        stParams.eRWtype = SCENE_CONTROL_ONCE_R;
        m_Table.addrVDynamic.compile(db,stParams);//插入地址表
    }
    sqlquery.bindValue(":nAddrVControl", QVariant(count));
    sqlquery.exec();

    QList<QGraphicsItem *> list = childItems();
    QString sName = "";

    QVector<qreal> vVLine;              //用来存垂直线的数据
    QVector<qreal> vHLine;             //用来存水平线的数据
    vVLine.clear();
    vHLine.clear();
    vVLine.append(rect.x());
    vHLine.append(rect.y());
    //vTileTex.clear();

    foreach(QGraphicsItem *pItem,list)
    {
        QPointF pos = pItem->boundingRect().topLeft()+pItem->scenePos();
        sName = pItem->data(GROUP_NAME_KEY).toString();
        if(sName.contains("VLine")) //垂直线
        {
            vVLine.append(pos.x());
        }
        if(sName.contains("HLine")) //水平线
        {
            vHLine.append(pos.y());
        }
    }

    for(int i = 0; i < vVLine.size(); i++)
    {
        for(int j = i + 1; j < vVLine.size(); j++)
        {
            if(vVLine.at(i) > vVLine.at(j))
            {
                qreal odata;
                odata = vVLine.at(i);
                vVLine.replace(i,vVLine.at(j));
                vVLine.replace(j,odata);
            }
        }
    }
    vVLine.append(rect.x() + rect.width());
    for(int i = 0; i < vVLine.size() - 1; i++)
    {
        //qDebug()<<"i:"<<i<<"pos:"<<vVLine.at(i);
        sqlquery.prepare("INSERT INTO tableProp(nItemId,nIsRow,nNo,nWidth)"
                                    "VALUES (:nItemId,:nIsRow,:nNo,:nWidth)");
            sqlquery.bindValue(":nItemId",QVariant(itemId));
            sqlquery.bindValue(":nIsRow",QVariant(0));
            sqlquery.bindValue(":nNo",QVariant(i));
            sqlquery.bindValue(":nWidth",QVariant(vVLine.at(i + 1) - vVLine.at(i)));
            sqlquery.exec();
    }

    //横直线
    for(int i = 0; i < vHLine.size(); i++)
    {
        for(int j = i + 1; j < vHLine.size(); j++)
        {
            if(vHLine.at(i) > vHLine.at(j))
            {
                qreal odata;
                odata = vHLine.at(i);
                vHLine.replace(i,vHLine.at(j));
                vHLine.replace(j,odata);
            }
        }
    }
    vHLine.append(rect.y() + rect.height());
    for(int i = 0; i < vHLine.size() - 1; i++)
    {
        //qDebug()<<"i:"<<i<<"pos:"<<vHLine.at(i);
        sqlquery.prepare("INSERT INTO tableProp(nItemId,nIsRow,nNo,nWidth)"
                                    "VALUES (:nItemId,:nIsRow,:nNo,:nWidth)");
            sqlquery.bindValue(":nItemId",QVariant(itemId));
            sqlquery.bindValue(":nIsRow",QVariant(1));
            sqlquery.bindValue(":nNo",QVariant(i));
            sqlquery.bindValue(":nWidth",QVariant(vHLine.at(i + 1) - vHLine.at(i)));
            sqlquery.exec();
    }

}

void QTableItem::save(QDataStream &stream)//将item存入数据流
{
    if(pwnd->getProVersion() >= 3271)
    {
        QVisableItem::save(stream);
    }
    else
    {
        QItemGroup::save(stream);
    }

    stream << m_Table.nOrientationCount;
    stream << m_Table.nPortraitCount;
    stream << m_Table.bShowFrameLine;
    stream << m_Table.bShowOrientationLine;
    stream << m_Table.bShowPortraitCount;
    stream << m_Table.nBackColor;
    stream << m_Table.nFramecolor;
    stream << m_Table.nWShowColor;
    stream << m_Table.eNLineType;
    stream << m_Table.nTransparent;

    stream << m_Table.bHDynamicControl;
    stream << m_Table.addrHDynamic;
    stream << m_Table.bVDynamicControl;
    stream << m_Table.addrVDynamic;
}

void QTableItem::load(QDataStream &stream)//从数据流导出item
{

    if(pwnd->getProVersion() >= 3271)
    {
        QVisableItem::load(stream);
    }
    else
    {
        QItemGroup::load(stream);
        sPro.bNotice = false;
        sPro.bDelay = false;
        sPro.enableTouch = false;
        sPro.enableVisable = false;
    }

    stream >> m_Table.nOrientationCount;
    stream >> m_Table.nPortraitCount;
    stream >> m_Table.bShowFrameLine;
    stream >> m_Table.bShowOrientationLine;
    stream >> m_Table.bShowPortraitCount;
    stream >> m_Table.nBackColor;
    stream >> m_Table.nFramecolor;
    stream >> m_Table.nWShowColor;
    stream >> m_Table.eNLineType;
    stream >> m_Table.nTransparent;
    if(pwnd->getProVersion() >= 3453)
    {
        stream >> m_Table.bHDynamicControl;
        stream >> m_Table.addrHDynamic;
        stream >> m_Table.bVDynamicControl;
        stream >> m_Table.addrVDynamic;
    }
    else
    {
        m_Table.bHDynamicControl = false;
        m_Table.addrHDynamic.sShowAddr = "LW0";
        m_Table.bVDynamicControl = false;
        m_Table.addrVDynamic.sShowAddr = "LW0";
    }
}
