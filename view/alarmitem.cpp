#include "alarmitem.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;
AlarmItem::AlarmItem()
        :QVisableItem(0)
{
}
int AlarmItem::GroupType()
{
    return SAM_DRAW_GROUP_ALARMITEM;
}

void AlarmItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
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
	sqlquery.prepare("INSERT INTO alarmControl(nItemId ,nSceneId ,nFrameColor ,nTableColor ,"
		"nTitleBackcolor ,nTitleColor ,bShowTime ,eTimeFormat ,bShowDate ,eDateFormat ,"
        "nFontSize ,nTextColor ,nRowCount ,bShowall ,sNames,nLeftTopX ,"
		"nLeftTopY ,nWidth ,nHeight ,nZvalue ,nCollidindId ) "
		"VALUES (:nItemId ,:nSceneId ,:nFrameColor ,:nTableColor ,:nTitleBackcolor ,"
		":nTitleColor ,:bShowTime,:eTimeFormat,:bShowDate ,:eDateFormat ,"
        ":nFontSize,:nTextColor,:nRowCount,:bShowall,:sNames ,:nLeftTopX ,"
		":nLeftTopY ,:nWidth ,:nHeight ,:nZvalue ,:nCollidindId )");
	
	sqlquery.bindValue(":nItemId",QVariant(itemId));//item id
	sqlquery.bindValue(":nSceneId",QVariant(nSceneId));//scene id
	sqlquery.bindValue(":nFrameColor",QVariant(ColorToInt(alarmPro.frameColor)));//边框色
	sqlquery.bindValue(":nTableColor",QVariant(ColorToInt(alarmPro.tableColor)));//背景色
	sqlquery.bindValue(":nTitleBackcolor",QVariant(ColorToInt(alarmPro.titleBackcolor)));//标题栏颜色
	sqlquery.bindValue(":nTitleColor",QVariant(ColorToInt(alarmPro.titleColor)));//标题颜色
	sqlquery.bindValue(":bShowTime",QVariant(alarmPro.bShowTime));//是否显示时间

	sqlquery.bindValue(":eTimeFormat",QVariant(alarmPro.eTimeFormat+1));//显示时间格式
	sqlquery.bindValue(":bShowDate",QVariant(alarmPro.bShowDate));//是否显示日期
	sqlquery.bindValue(":eDateFormat",QVariant(alarmPro.eDateFormat+1));//显示日期格式
	sqlquery.bindValue(":nFontSize",QVariant(alarmPro.nFontSize));//文本字体
	sqlquery.bindValue(":nTextColor",QVariant(ColorToInt(alarmPro.textColor)));//文本色
	sqlquery.bindValue(":nRowCount",QVariant(alarmPro.rowCount));//行数
	sqlquery.bindValue(":bShowall",QVariant(alarmPro.bSelectAll));//是否显示所有报警

    QString names ;
    if(!alarmPro.bSelectAll)
    {
        for(int i=0; i<pwnd->m_pSamSysParame->m_qvcAlarm.size(); i++)
        {
            QString name = pwnd->m_pSamSysParame->m_qvcAlarm[i].alarmName;
            if(alarmPro.groupName.contains(name))
            {
                names.append(QString::number(i));
                names.append(",");
            }
        }
    }

    sqlquery.bindValue(":sNames",QVariant(names));//显示范围下限

	QRectF rect = sceneBoundingRect();
	sqlquery.bindValue(":nLeftTopX",QVariant((short)rect.left()));//left
	sqlquery.bindValue(":nLeftTopY",QVariant((short)rect.top()));//top
	sqlquery.bindValue(":nWidth",QVariant((short)rect.width()));//width
	sqlquery.bindValue(":nHeight",QVariant((short)rect.height()));//height
	sqlquery.bindValue(":nZvalue",QVariant(zValue()));//层次

	sqlquery.bindValue(":nCollidindId",QVariant(index));//碰撞ID
	bool result = false;
	result = sqlquery.exec();
	qDebug() << "insert alarmControl table :"<<result;

	sqlquery.prepare("INSERT INTO alarmTitle(nItemId ,nLanguageIndex ,nFontSize ,"
		"sFont ,sTime ,sDate ,sMessage ,sClearTime ,sClearDate ) "
		"VALUES (:nItemId ,:nLanguageIndex ,:nFontSize ,:sFont ,:sTime ,:sDate ,"
		":sMessage ,:sClearTime ,:sClearDate )");
    int languageId = 0;
	foreach (stAlarmTitles title,alarmPro.titles)
	{
		sqlquery.bindValue(":nItemId",QVariant(itemId));
        sqlquery.bindValue(":nLanguageIndex",QVariant(languageId++));
		sqlquery.bindValue(":nFontSize",QVariant(title.nFontSize));
		sqlquery.bindValue(":sFont",QVariant(title.sFont));
		sqlquery.bindValue(":sTime",QVariant(title.sTime));
		sqlquery.bindValue(":sDate",QVariant(title.sDate));
		sqlquery.bindValue(":sMessage",QVariant(title.sMessage));
		sqlquery.bindValue(":sClearTime",QVariant(title.sClearTime));
		sqlquery.bindValue(":sClearDate",QVariant(title.sClearDate));
		result = false;
		result = sqlquery.exec();
		qDebug() << "insert alarmTitle table :"<<result;
	}
	

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

void AlarmItem::save(QDataStream &stream)
{
    QVisableItem::save(stream);
    int titleList=alarmPro.titles.size();
    stream << titleList;
    for(int i=0;i<titleList;i++){
        stream << alarmPro.titles[i].nFontSize;
        stream << alarmPro.titles[i].sClearDate;
        stream << alarmPro.titles[i].sClearTime;
        stream << alarmPro.titles[i].sDate;
        stream << alarmPro.titles[i].sFont;
        stream << alarmPro.titles[i].sMessage;
        stream << alarmPro.titles[i].sTime;
    }
    stream << alarmPro.bClearDate;
    stream << alarmPro.bClearTime;
    stream << alarmPro.bControl;
    stream << alarmPro.bSelectAll;
    stream << alarmPro.bShowDate;
    stream << alarmPro.bShowNumber;
    stream << alarmPro.bShowTime;
    stream << alarmPro.clearedColor;
    stream << alarmPro.confirmColor;
    stream << alarmPro.controlAddr;
    stream << alarmPro.eClearDateFormat;
    stream << alarmPro.eClearTimeFormat;
    stream << alarmPro.eDateFormat;
    stream << alarmPro.eTimeFormat;
    stream << alarmPro.frameColor;
    stream << alarmPro.nFontSize;
    stream << alarmPro.nRangeHigh;
    stream << alarmPro.nRangeLow;
    stream << alarmPro.rowCount;
    stream << alarmPro.sFont;
    stream << alarmPro.tableColor;
    stream << alarmPro.textColor;
    stream << alarmPro.titleBackcolor;
    stream << alarmPro.titleColor;
    stream << alarmPro.groupName;

}
void AlarmItem::load(QDataStream &stream)
{
    QVisableItem::load(stream);
    int titleList=0;
    stream >> titleList;
    alarmPro.titles.resize(titleList);
    for(int i=0;i<titleList;i++){
        stream >> alarmPro.titles[i].nFontSize;
        stream >> alarmPro.titles[i].sClearDate;
        stream >> alarmPro.titles[i].sClearTime;
        stream >> alarmPro.titles[i].sDate;
        stream >> alarmPro.titles[i].sFont;
        stream >> alarmPro.titles[i].sMessage;
        stream >> alarmPro.titles[i].sTime;
    }
    stream >> alarmPro.bClearDate;
    stream >> alarmPro.bClearTime;
    stream >> alarmPro.bControl;
    stream >> alarmPro.bSelectAll;
    stream >> alarmPro.bShowDate;
    stream >> alarmPro.bShowNumber;
    stream >> alarmPro.bShowTime;
    stream >> alarmPro.clearedColor;
    stream >> alarmPro.confirmColor;
    stream >> alarmPro.controlAddr;
    stream >> alarmPro.eClearDateFormat;
    stream >> alarmPro.eClearTimeFormat;
    stream >> alarmPro.eDateFormat;
    stream >> alarmPro.eTimeFormat;
    stream >> alarmPro.frameColor;
    stream >> alarmPro.nFontSize;
    stream >> alarmPro.nRangeHigh;
    stream >> alarmPro.nRangeLow;
    stream >> alarmPro.rowCount;
    stream >> alarmPro.sFont;
    stream >> alarmPro.tableColor;
    stream >> alarmPro.textColor;
    stream >> alarmPro.titleBackcolor;
    stream >> alarmPro.titleColor;
    if(pwnd->getProVersion() < 2053)//旧版本
    {
        QString str;
        stream >> str;
        if(!str.isEmpty())
            alarmPro.groupName = QStringList(str);
    }
    else
    {
        stream >> alarmPro.groupName;
    }
}

QGraphicsItem *AlarmItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    AlarmItem *itemGroup = new AlarmItem();

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
    }
    //添加复制基类属性的代码
    itemGroup->alarmPro = alarmPro;
	itemGroup->sPro = sPro;
    itemGroup->setId(id());

    return itemGroup;

}


TEXTPRO AlarmItem::getAllItemText()
{
    int iLan = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //多语言总数

    vText.sCtrlName = this->getItemName(); //控件名称
    vText.iLanguage.clear();
    vText.vStatus.clear();
    vText.vText.clear();
    vText.vMsg.clear();

    for(int i = 0; i < iLan; i++) //总的语言扫描
    {
        for(int j = 0; j < 3; j++)
            vText.iLanguage.append(i);

            vText.vStatus.append(0);
            vText.vMsg.append(QObject::tr("时间:"));
            vText.vText.append(alarmPro.titles[i].sTime);

            vText.vStatus.append(1);
            vText.vMsg.append(QObject::tr("日期:"));
            vText.vText.append(alarmPro.titles[i].sDate);

            vText.vStatus.append(2);
            vText.vMsg.append(QObject::tr("消息:"));
            vText.vText.append(alarmPro.titles[i].sMessage);
    }
    return vText;
}

void AlarmItem::replaceAllItemText(int iLan, int iSta, QString sNewText)
{
    int iL = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //多语言总数
    if( iLan >= 0 && iLan < iL)
    {
        if(iSta == 0)
            alarmPro.titles[iLan].sTime = sNewText;
        else if(iSta == 1)
            alarmPro.titles[iLan].sDate = sNewText;
        else if(iSta == 2)
            alarmPro.titles[iLan].sMessage = sNewText;
    }
}

void AlarmItem::redrawForChangeLanguage(int index)
{
	if (index >= alarmPro.titles.size())
	{
		return ;
	}
	QVector<QSimpleTextItem *> texts;
	QSimpleTextItem *textItem = NULL;
	foreach (QGraphicsItem *childitem,childItems())
	{
		textItem = dynamic_cast<QSimpleTextItem *>(childitem);
		texts << textItem;
	}
	
	QString sTime;
	QString sDate;
	QString sMessage;
	if (alarmPro.bShowTime)
	{
		sTime = "Text0";
	}
	if (alarmPro.bShowDate)
	{
		int col = alarmPro.bShowTime;
		sDate = QString("Text%1").arg(QString::number(col));
	}
	sMessage = QString("Text%1").arg(QString::number(alarmPro.bShowTime+alarmPro.bShowDate));
	//for(int i=0; i< titles.size(); i++)
	{
		//QString sName = QString("Text%1").arg(i);
		foreach (QSimpleTextItem *tItem,texts)
		{
			if (!tItem)
			{
				continue;
			}
			QString sName = tItem->data(GROUP_NAME_KEY).toString();
			if (sName == sDate && !sDate.isEmpty())
			{
				tItem->SetText(alarmPro.titles[index].sDate);
				tItem->SetFontSize(alarmPro.titles[index].nFontSize);
				tItem->SetFontName(alarmPro.titles[index].sFont);
			}
			if (sName == sTime && !sTime.isEmpty())
			{
				tItem->SetText(alarmPro.titles[index].sTime);
				tItem->SetFontSize(alarmPro.titles[index].nFontSize);
				tItem->SetFontName(alarmPro.titles[index].sFont);
			}
			if (sName == sMessage && !sMessage.isEmpty())
			{
				tItem->SetText(alarmPro.titles[index].sMessage);
				tItem->SetFontSize(alarmPro.titles[index].nFontSize);
				tItem->SetFontName(alarmPro.titles[index].sFont);
			}
		}
	}
	
}

QStringList AlarmItem::getAllFonts()
{
    QStringList ls;
    ls.clear();
    foreach(stAlarmTitles title,alarmPro.titles)
    {
        ls << title.sFont;
    }
    return ls;
}

QVector<ADDRPRO> AlarmItem::getAllItemAddr()
{
    kb.clear();
    kb = QVisableItem::getAllItemAddr();
    return kb;
}

QString  AlarmItem::getItemName()
{
    return QObject::tr("报警显示器");
}
