#include "hisalarmitem.h"
extern MainWindow *pwnd;
HisAlarmItem::HisAlarmItem()
    :QVisableItem(0)
{
}
int HisAlarmItem::GroupType()
{
    return SAM_DRAW_GROUP_HISALARMITEM;
}
QString  HisAlarmItem::getItemName()
{
    return QObject::tr("历史报警显示器");
}
void HisAlarmItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
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
	sqlquery.prepare("INSERT INTO hisAlarmShow(nItemId ,nSceneId ,nFrameColor ,nTableColor ,"
		"bControl ,eControlAddr ,"
		"nTitleBackcolor ,nTitleColor ,bShowTime ,eTimeFormat ,bShowDate ,eDateFormat ,"
		"bNumber ,nFontSize ,nTextColor ,nRowCount ,bClearDate ,eClearDateFormat ,"
		"bClearTime ,eClearTimeFormat ,nClearColor ,nConfirmColor ,nLeftTopX ,"
		"nLeftTopY ,nWidth ,nHeight ,nZvalue ,nCollidindId )"
		"VALUES (:nItemId ,:nSceneId ,:nFrameColor ,:nTableColor ,"
		":bControl ,:eControlAddr ,"
		":nTitleBackcolor ,:nTitleColor ,:bShowTime ,:eTimeFormat ,:bShowDate ,:eDateFormat ,"
		":bNumber ,:nFontSize ,:nTextColor ,:nRowCount ,:bClearDate ,:eClearDateFormat ,"
		":bClearTime ,:eClearTimeFormat ,:nClearColor ,:nConfirmColor ,:nLeftTopX ,"
		":nLeftTopY ,:nWidth ,:nHeight ,:nZvalue ,:nCollidindId )");

	sqlquery.bindValue(":nItemId",QVariant(itemId));//item id
	sqlquery.bindValue(":nSceneId",QVariant(nSceneId));//scene id
	sqlquery.bindValue(":nFrameColor",QVariant(ColorToInt(alarmPro.frameColor)));//边框色
	sqlquery.bindValue(":nTableColor",QVariant(ColorToInt(alarmPro.tableColor)));//背景色

	sqlquery.bindValue(":bControl",QVariant(alarmPro.bControl));//是否控制
    if(alarmPro.bControl)
    {
        count++;
        ADDR_PARAMENTS stParams;
        stParams.id = count;
        stParams.itemId = itemId;
        stParams.eType = OBJ_ITEM;
        stParams.addrNum = -1;
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
        alarmPro.controlAddr.compile(db,stParams);
        sqlquery.bindValue(":eControlAddr",QVariant(count));//控制地址
    }


	sqlquery.bindValue(":nTitleBackcolor",QVariant(ColorToInt(alarmPro.titleBackcolor)));//标题栏颜色
	sqlquery.bindValue(":nTitleColor",QVariant(ColorToInt(alarmPro.titleColor)));//标题颜色
	sqlquery.bindValue(":bShowTime",QVariant(alarmPro.bShowTime));//是否显示时间

	sqlquery.bindValue(":eTimeFormat",QVariant(alarmPro.eTimeFormat+1));//显示时间格式
    sqlquery.bindValue(":bShowDate",QVariant((short)alarmPro.bShowDate));//是否显示日期
	sqlquery.bindValue(":eDateFormat",QVariant(alarmPro.eDateFormat+1));//显示日期格式

	sqlquery.bindValue(":bNumber",QVariant(alarmPro.bShowNumber));//是否显示时间

	sqlquery.bindValue(":nFontSize",QVariant(alarmPro.nFontSize));//文本字体
	sqlquery.bindValue(":nTextColor",QVariant(ColorToInt(alarmPro.textColor)));//文本色
	sqlquery.bindValue(":nRowCount",QVariant(alarmPro.rowCount));//行数

	sqlquery.bindValue(":bClearDate",QVariant(alarmPro.bClearDate));//是否显示清除日期列
    sqlquery.bindValue(":eClearDateFormat",QVariant(alarmPro.eClearDateFormat+1));//显示清除日期格式
	sqlquery.bindValue(":bClearTime",QVariant(alarmPro.bClearTime));//是否显示清除时间列
    sqlquery.bindValue(":eClearTimeFormat",QVariant(alarmPro.eClearTimeFormat+1));//显示清除时间格式
	sqlquery.bindValue(":nClearColor",QVariant(ColorToInt(alarmPro.clearedColor)));//已清除报警的颜色
	sqlquery.bindValue(":nConfirmColor",QVariant(ColorToInt(alarmPro.confirmColor)));//已确认报警的颜色

	QRectF rect = sceneBoundingRect();
	sqlquery.bindValue(":nLeftTopX",QVariant((short)rect.left()));//left
	sqlquery.bindValue(":nLeftTopY",QVariant((short)rect.top()));//top
	sqlquery.bindValue(":nWidth",QVariant((short)rect.width()));//width
	sqlquery.bindValue(":nHeight",QVariant((short)rect.height()));//height
	sqlquery.bindValue(":nZvalue",QVariant(zValue()));//层次

	sqlquery.bindValue(":nCollidindId",QVariant(index));//碰撞ID
	bool result = false;
	result = sqlquery.exec();
	qDebug() << "insert hisAlarmShow table :"<<result;

	sqlquery.prepare("INSERT INTO alarmTitle(nItemId ,nLanguageIndex ,nFontSize ,"
		"sFont ,sTime ,sDate ,sMessage ,sClearTime ,sClearDate ) "
		"VALUES (:nItemId ,:nLanguageIndex ,:nFontSize ,:sFont ,:sTime ,:sDate ,"
		":sMessage ,:sClearTime ,:sClearDate )");
	int languageId = 0;
	foreach (stAlarmTitles title,alarmPro.titles)
	{
		sqlquery.bindValue(":nItemId",QVariant(itemId));
		sqlquery.bindValue(":nLanguageIndex",QVariant(languageId));
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

void HisAlarmItem::save(QDataStream &stream)
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
}
void HisAlarmItem::load(QDataStream &stream)
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
}

QGraphicsItem *HisAlarmItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    HisAlarmItem *itemGroup = new HisAlarmItem();

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
    //itemGroup->gType = gType;
	itemGroup->alarmPro = alarmPro;
	itemGroup->sPro = sPro;
    itemGroup->setId(id());

    return itemGroup;

}


QStringList HisAlarmItem::getAllFonts()
{
	QStringList ls;
	ls.clear();
	foreach(stAlarmTitles title,alarmPro.titles)
	{
		ls << title.sFont;
	}
	return ls;
}
QVector<ADDRPRO> HisAlarmItem::getAllItemAddr()
{
    kb.clear();
    kb = QVisableItem::getAllItemAddr();
    if (alarmPro.bControl)
    {
        ADDRPRO addpro;
        addpro.pAddr = &alarmPro.controlAddr;
        addpro.str   = QObject::tr("历史报警显示器-控制地址");
        addpro.type  = 1;
        kb << addpro;
    }
    return kb;
}

TEXTPRO HisAlarmItem::getAllItemText()
{
    //  int iStaCount = 1; //总状态数目
      int iLan = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //多语言总数

      vText.sCtrlName = this->getItemName(); //控件名称
      vText.iLanguage.clear();
      vText.vStatus.clear();
      vText.vText.clear();
      vText.vMsg.clear();

      for(int i = 0; i < iLan; i++) //总的语言扫描
      {
          for(int j = 0; j < 4; j++)
              vText.iLanguage.append(i);

              vText.vStatus.append(0);
              vText.vMsg.append(QObject::tr("时间:"));
              vText.vText.append(alarmPro.titles[i].sTime);

              vText.vStatus.append(1);
              vText.vMsg.append(QObject::tr("日期:"));
              vText.vText.append(alarmPro.titles[i].sDate);

              vText.vStatus.append(2);
              vText.vMsg.append(QObject::tr("清除日期:"));
              vText.vText.append(alarmPro.titles[i].sClearDate);

              vText.vStatus.append(3);
              vText.vMsg.append(QObject::tr("清除时间:"));
              vText.vText.append(alarmPro.titles[i].sClearTime);

              vText.vStatus.append(4);
              vText.vMsg.append(QObject::tr("消息:"));
              vText.vText.append(alarmPro.titles[i].sMessage);
      }
      return vText;
}

void HisAlarmItem::replaceAllItemText(int iLan, int iSta, QString sNewText)
{
    int iL = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //多语言总数
    if( iLan >= 0 && iLan < iL)
    {
        if(iSta == 0)
            alarmPro.titles[iLan].sTime = sNewText;
        else if(iSta == 1)
            alarmPro.titles[iLan].sDate = sNewText;
        else if(iSta == 2)
            alarmPro.titles[iLan].sClearDate = sNewText;
        else if(iSta == 3)
            alarmPro.titles[iLan].sClearTime = sNewText;
        else if(iSta == 4)
            alarmPro.titles[iLan].sMessage = sNewText;
    }
}

void HisAlarmItem::redrawForChangeLanguage(int index)
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
	QStringList titles;
	if (alarmPro.bShowTime)
	{
		titles << alarmPro.titles[index].sTime;
	}
	if (alarmPro.bShowDate)
	{
		titles << alarmPro.titles[index].sDate;
	}	
	if (alarmPro.bClearDate)
	{
		titles << alarmPro.titles[index].sClearDate;
	}
	if (alarmPro.bClearTime)
	{
		titles << alarmPro.titles[index].sClearTime;
	}
	titles << alarmPro.titles[index].sMessage;
	for(int i=0; i< titles.size(); i++)
	{
		//QString sName = QString("Text%1").arg(i);
		foreach (QSimpleTextItem *tItem,texts)
		{
			if (!tItem)
			{
				continue;
			}
			QString sName = tItem->data(GROUP_NAME_KEY).toString();
			if (sName == QString("Text%1").arg(i+alarmPro.bShowNumber))
			{
				tItem->SetText(titles[i]);
				tItem->SetFontSize(alarmPro.titles[index].nFontSize);
				tItem->SetFontName(alarmPro.titles[index].sFont);
			}
			
		}
	}

}

//获得操作地址
QList<Keyboard> HisAlarmItem::getAddress()
{
	QList<Keyboard> addrs;
	if (alarmPro.bControl)
	{
		addrs << alarmPro.controlAddr;
	}
	
	return addrs;
}
//设置操作地址
void HisAlarmItem::setAddress(QList<Keyboard> addr)
{
	if (addr.size() <1)
		return ;
	if (alarmPro.bControl)
	{
		alarmPro.controlAddr = addr.first();
	}
}
