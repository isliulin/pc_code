#include "alarmbar.h"
#include "qdrawgraphics.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;
AlarmBar::AlarmBar()
    :QVisableItem(0)
{

}
QString  AlarmBar::getItemName()
{
    return QObject::tr("动态报警条");
}
int AlarmBar::SetDefault()
{
    QDrawGraphics Draw;
    QList<QGraphicsItem *>childrens;
    childrens = Draw.OnDrawRectAndText();
    foreach(QGraphicsItem *pItem,childrens)
    {
        addToGroup(pItem);
    }
	return 0;
}
int AlarmBar::GroupType()
{
    return SAM_DRAW_GROUP_ALARMBAR;
}

void AlarmBar::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    count++;
	QVisableItem::compile(db,nSceneId,count,index);
	int itemId = count;
	//在权限页面已经增加了地址表，需要再这里计算并重新设定count

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
    sqlquery.prepare("INSERT INTO alarmSlip(nItemId,nSceneId ,sApperIndex ,nBackcolor ,nFramecolor ,nForecolor,nFontSize ,nTextColor ,bSelectall ,sNames,"
        "nSpeed ,eDirection ,eSort ,nLeftTopX ,nLeftTopY ,nWidth ,nHeight ,nTextLeftTopX ,nTextLeftTopY ,nTextWidth ,"
		"nTextHeight ,nZvalue ,nCollidindId ) "
        "VALUES (:nItemId ,:nSceneId ,:sApperIndex ,:nBackcolor ,:nFramecolor ,:nForecolor,:nFontSize ,:nTextColor ,:bSelectall ,:sNames ,"
        ":nSpeed ,:eDirection ,:eSort ,:nLeftTopX ,:nLeftTopY ,:nWidth ,:nHeight ,:nTextLeftTopX ,:nTextLeftTopY ,:nTextWidth ,"
		":nTextHeight ,:nZvalue ,:nCollidindId)");

	sqlquery.bindValue(":nItemId",QVariant(itemId));// 表 id
	sqlquery.bindValue(":nSceneId",QVariant(nSceneId));// scene id
    sqlquery.bindValue(":sApperIndex",QVariant(stPro.nPattern+1));
	sqlquery.bindValue(":nBackcolor",QVariant(ColorToInt(stPro.backColor)));
    sqlquery.bindValue(":nFramecolor",QVariant(ColorToInt(stPro.frameColor)));
    sqlquery.bindValue(":nForecolor",QVariant(ColorToInt(stPro.frColor)));
	sqlquery.bindValue(":nFontSize",QVariant(stPro.fontSize));
	sqlquery.bindValue(":nTextColor",QVariant(ColorToInt(stPro.textColor)));
    sqlquery.bindValue(":bSelectall",QVariant(stPro.bSelectall));

    QString names ;
    if(!stPro.bSelectall)
    {
        for(int i=0; i<pwnd->m_pSamSysParame->m_qvcAlarm.size(); i++)
        {
            QString name = pwnd->m_pSamSysParame->m_qvcAlarm[i].alarmName;
            if(stPro.groupName.contains(name))
            {
                names.append(QString::number(i));
                names.append(",");
            }
        }
    }

    sqlquery.bindValue(":sNames",QVariant(names));//显示范围下限

	sqlquery.bindValue(":nSpeed",QVariant(stPro.speed));
	sqlquery.bindValue(":eDirection",QVariant(stPro.direction));
    sqlquery.bindValue(":eSort",QVariant(stPro.sort));

	QRectF rect = sceneBoundingRect();
	sqlquery.bindValue(":nLeftTopX",QVariant(rect.x()));
	sqlquery.bindValue(":nLeftTopY",QVariant(rect.y()));
	sqlquery.bindValue(":nWidth",QVariant(rect.width()));
	sqlquery.bindValue(":nHeight",QVariant(rect.height()));
    qDebug() << "item_rect===========" << rect;
    foreach(QGraphicsItem* child,childItems())
    {
        if(child->type() == SAM_DRAW_OBJECT_TEXT)
        {
            rect = child->boundingRect();
            rect = child->mapRectToScene(rect);
            break;
        }
    }
    qDebug() << "text_rect===========" << rect;
	sqlquery.bindValue(":nTextLeftTopX",QVariant(rect.x()));
	sqlquery.bindValue(":nTextLeftTopY",QVariant(rect.y()));
	sqlquery.bindValue(":nTextWidth",QVariant(rect.width()));
	sqlquery.bindValue(":nTextHeight",QVariant(rect.height()));
	sqlquery.bindValue(":nZvalue",QVariant(zValue()));
	sqlquery.bindValue(":nCollidindId",QVariant(index));
	bool result = false;
	result = sqlquery.exec();
	qDebug() << "insert alarmSlip table :"<<result;

}

void AlarmBar::save(QDataStream &stream)
{
    QVisableItem::save(stream);
    stream << stPro.appearIndex;
    stream << stPro.backColor;
    stream << stPro.bSelectall;
    stream << stPro.direction;
    stream << stPro.fontSize;
    stream << stPro.frameColor;
    stream << stPro.frColor;
    stream << stPro.nPattern;
    stream << stPro.nRangHigh;
    stream << stPro.nRangLow;
    stream << stPro.sort;
    stream << stPro.speed;
    stream << stPro.textColor;
    stream << stPro.groupName;
}
void AlarmBar::load(QDataStream &stream)
{
    QVisableItem::load(stream);
    stream >> stPro.appearIndex;
    stream >> stPro.backColor;
    stream >> stPro.bSelectall;
    stream >> stPro.direction;
    stream >> stPro.fontSize;
    stream >> stPro.frameColor;
    stream >> stPro.frColor;
    stream >> stPro.nPattern;
    stream >> stPro.nRangHigh;
    stream >> stPro.nRangLow;
    stream >> stPro.sort;
    stream >> stPro.speed;
    stream >> stPro.textColor;

    if(pwnd->getProVersion() < 2053)//旧版本
    {
        QString str;
        stream >> str;
        if(!str.isEmpty())
            stPro.groupName = QStringList(str);
    }
    else
    {
        stream >> stPro.groupName;
    }
}

QGraphicsItem *AlarmBar::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    AlarmBar *itemGroup = new AlarmBar();

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
    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
		return NULL;
    }
    //添加复制基类属性的代码
    //itemGroup->gType = gType;
    itemGroup->SaveSecurityPro(&sPro);
    itemGroup->stPro = stPro;
    itemGroup->setId(id());

    return itemGroup;

}

QVector<ADDRPRO> AlarmBar::getAllItemAddr()
{
    kb.clear();
    kb = QVisableItem::getAllItemAddr();
    return kb;
}
