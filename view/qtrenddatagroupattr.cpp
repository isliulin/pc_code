#include "qtrenddatagroupattr.h"

extern MainWindow *pwnd;

QTrendDataGroupAttr::QTrendDataGroupAttr(QGraphicsItem *parent):QVisableItem(parent)
{
}

QTrendDataGroupAttr::~QTrendDataGroupAttr()
{

}

int QTrendDataGroupAttr::GroupType()//控件类型 数据群组
{
    //return GROUP_TYPE_DATAGROUPDISPLAY;
    return SAM_DRAW_GROUP_GROUPDATA;
}

QTrendDataGroupAttr* QTrendDataGroupAttr::Clone()//复制item
{
    QGraphicsItem* pCopy = NULL;
    QGraphicsItem* pItem = NULL;

    QTrendDataGroupAttr *itemGroup = new QTrendDataGroupAttr;

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
        {
            pCopy->setFlag(QGraphicsItem::ItemIsSelectable,false);
        }
    }

    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }

    itemGroup->SaveSecurityPro(&sPro);

    itemGroup->m_bIsAll             = m_bIsAll;
    itemGroup->m_sCurChnnel      = m_sCurChnnel;
    itemGroup->m_sChnnelBegin       = m_sChnnelBegin;
    itemGroup->m_nTotalTrendNumber  = m_nTotalTrendNumber;
    itemGroup->m_vecChannelGroups   = m_vecChannelGroups;
    itemGroup->m_vecDisplayGroups   = m_vecDisplayGroups;
    itemGroup->m_selGroups          = m_selGroups;
    itemGroup->m_nDisplayMax          = m_nDisplayMax;
    itemGroup->m_nDisplayMin          = m_nDisplayMin;

    itemGroup->m_bSelectVertMinor   = m_bSelectVertMinor;
    itemGroup->m_bSelectHorMinor    = m_bSelectHorMinor;
    itemGroup->m_bMainHor           = m_bMainHor;
    itemGroup->m_bMainVer           = m_bMainVer;
    itemGroup->m_nDataSample        = m_nDataSample;
    itemGroup->m_nVertMajorScale    = m_nVertMajorScale;
    itemGroup->m_nVertMinorScale    = m_nVertMinorScale;
    itemGroup->m_nHorMajorScale     = m_nHorMajorScale;
    itemGroup->m_nHorMinorScale     = m_nHorMinorScale;

    itemGroup->m_bGrade             = m_bGrade;
    itemGroup->m_nVerColor          = m_nVerColor;
    itemGroup->m_nHorColor          = m_nHorColor;
    itemGroup->m_nBoradColor        = m_nBoradColor;
    itemGroup->m_nScaleColor        = m_nScaleColor;
    itemGroup->m_nGraphColor        = m_nGraphColor;
    itemGroup->m_nFontSize          = m_nFontSize;
    itemGroup->m_vecGroupColor      = m_vecGroupColor;
    itemGroup->m_nMarkedColor       = m_nMarkedColor;
    itemGroup->m_alpha              = m_alpha;
    itemGroup->setId(id());

    return itemGroup;
    //return QVisableItem::Clone();
}

void QTrendDataGroupAttr::compile(QSqlDatabase &db, int nSceneId,int &count, int index)//编译的时候保存item到数据库
{
    int ck;
    count++;
    QVisableItem::compile(db, nSceneId, count, index);

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
    bool r = sqlquery.prepare("INSERT INTO trends(nItemId,nSceneId,nTopLeftX,nTopLeftY,nWidth,nHeight,nCurveX,nCurveY,nCurveWd,nCurveHt,"
            "nCurveType,nGroupNum,nChannelNum,nDisplayMax,nDisplayMin,nDataSample,nScrollSample,nVertMajorScale,bSelectVertMinor,nVertMinorScale,nHorMajorScale,"
            "bSelectHorMinor,nHorMinorScale,bSelectNet,nVertNetColor,nHorNetColor,nBoradColor,nScaleColor,nGraphColor,sFontType,nFontSize,"
            "nFontAttri,nDate,nTime,nMarkColor,bXmark,nTimeRange,nRecentYear,nRecentMonth,nRecentDay,nRecentHour,"
            "nRecentMinute,nStartYear,nStartMonth,nStartDay,nStartHour,nStartMinute,nEndYear,nEndMonth,nEndDay,nEndHour,"
    "nEndMinute,nCurveAlpha,nZvalue,nCollidindId,nShowPropId,bMainVer,bMainHor,mFromAddr,mToAddr)"
            "VALUES(:nItemId,:nSceneId,:nTopLeftX,:nTopLeftY,:nWidth,:nHeight,:nCurveX,:nCurveY,:nCurveWd,:nCurveHt,"
            ":nCurveType,:nGroupNum,:nChannelNum,:nDisplayMax,:nDisplayMin,:nDataSample,:nScrollSample,:nVertMajorScale,:bSelectVertMinor,:nVertMinorScale,:nHorMajorScale,"
            ":bSelectHorMinor,:nHorMinorScale,:bSelectNet,:nVertNetColor,:nHorNetColor,:nBoradColor,:nScaleColor,:nGraphColor,:sFontType,:nFontSize,"
            ":nFontAttri,:nDate,:nTime,:nMarkColor,:bXmark,:nTimeRange,:nRecentYear,:nRecentMonth,:nRecentDay,:nRecentHour,"
            ":nRecentMinute,:nStartYear,:nStartMonth,:nStartDay,:nStartHour,:nStartMinute,:nEndYear,:nEndMonth,:nEndDay,:nEndHour,"
            ":nEndMinute,:nCurveAlpha,:nZvalue,:nCollidindId,:nShowPropId,:bMainVer,:bMainHor,:mFromAddr,:mToAddr)");

    qDebug() << "sqlquery.prepare" << r;
    sqlquery.bindValue(":nItemId", QVariant(itemId));                //表id
    sqlquery.bindValue(":nSceneId", QVariant(nSceneId));            //scene id

    QRectF rect = sceneBoundingRect();//相对场景的坐标及高宽
    sqlquery.bindValue(":nTopLeftX", QVariant((short)rect.left()));//left
    sqlquery.bindValue(":nTopLeftY", QVariant((short)rect.top()));//top
    sqlquery.bindValue(":nWidth", QVariant((short)rect.width()));//width
    sqlquery.bindValue(":nHeight", QVariant((short)rect.height()));//height

    //QRectF rect1 = sceneBoundingRect();//相对场景的坐标及高宽
    double leftSmall = rect.width() * 60 / 400;
    double topSmall  = rect.height() * 20 / 250;
    double wd = rect.width()-leftSmall-leftSmall/2;
    double hd = rect.height()-topSmall-2*topSmall;

    foreach (QGraphicsItem *child,childItems())
    {
        if (child->data(GROUP_NAME_KEY).toString() == "backRect")
        {
            QRectF rc = child->sceneBoundingRect();
            qDebug() << "backRect" << rc;
            leftSmall = rc.left()- rect.left();
            topSmall  = rc.top()-rect.top();
            wd		  = rc.width();
            hd        = rc.height();
            break;
        }
    }

    sqlquery.bindValue(":nCurveX", QVariant(leftSmall));//left
    sqlquery.bindValue(":nCurveY", QVariant(topSmall));//top
    sqlquery.bindValue(":nCurveWd", QVariant(wd));//width
    sqlquery.bindValue(":nCurveHt", QVariant(hd));//height

    sqlquery.bindValue(":nCurveType", QVariant(3));                     //图表类型,数据群组
    sqlquery.bindValue(":nGroupNum", QVariant(0));          //组号
    sqlquery.bindValue(":nChannelNum", QVariant(m_selGroups.size()));         //组数（通道数）
	sqlquery.bindValue(":nDisplayMax", QVariant(m_nDisplayMax)); //显示范围最大值
	sqlquery.bindValue(":nDisplayMin", QVariant(m_nDisplayMin)); //显示范围最小值

    sqlquery.bindValue(":nDataSample", QVariant(m_nDataSample));            //数据样本数
    sqlquery.bindValue(":nScrollSample", QVariant(0));      //滚动样本数
    sqlquery.bindValue(":nVertMajorScale", QVariant(m_nVertMajorScale));    //垂直主标尺
    sqlquery.bindValue(":bMainVer", QVariant(m_bMainVer));    //垂直主标尺
    sqlquery.bindValue(":bSelectVertMinor", QVariant(m_bSelectVertMinor));  //是否显示垂直次标尺
    sqlquery.bindValue(":nVertMinorScale", QVariant(m_nVertMinorScale));    //垂直次标尺
    sqlquery.bindValue(":nHorMajorScale", QVariant(m_nHorMajorScale));      //水平主标尺
    sqlquery.bindValue(":bMainHor", QVariant(m_bMainHor));      //水平主标尺
    sqlquery.bindValue(":bSelectHorMinor", QVariant(m_bSelectHorMinor));    //是否显示水平次标尺
    sqlquery.bindValue(":nHorMinorScale", QVariant(m_nHorMinorScale));      //水平次标尺

    sqlquery.bindValue(":bSelectNet", QVariant(m_bGrade));          //是否需要网格
    ck = ColorToInt(m_nVerColor);
    sqlquery.bindValue(":nVertNetColor", QVariant(ck));    //水平网格颜色
    ck = ColorToInt(m_nHorColor);
    sqlquery.bindValue(":nHorNetColor", QVariant(ck));     //垂直网格颜色
    ck = ColorToInt(m_nBoradColor);
    sqlquery.bindValue(":nBoradColor", QVariant(ck));      //边框颜色
    ck = ColorToInt(m_nScaleColor);
    sqlquery.bindValue(":nScaleColor", QVariant(ck));      //标尺颜色
    ck = ColorToInt(m_nGraphColor);
    sqlquery.bindValue(":nGraphColor", QVariant(ck));      //图表区颜色
    ck = ColorToInt(m_nMarkedColor);
    sqlquery.bindValue(":nMarkColor", QVariant(ck));      //标注颜色

    sqlquery.bindValue(":sFontType", QVariant(""));    //字体类型
    sqlquery.bindValue(":nFontSize", QVariant(m_nFontSize));    //字体大小
    sqlquery.bindValue(":nFontAttri", QVariant(0));    //文本属性
    sqlquery.bindValue(":nDate", QVariant(0));      //日期格式
    sqlquery.bindValue(":nTime", QVariant(0));      //时间格式
    sqlquery.bindValue(":bXmark", QVariant(true));        //是否X轴标注
    sqlquery.bindValue(":nTimeRange", QVariant(0));      //那种时间采集方式

    sqlquery.bindValue(":nRecentMinute", QVariant(0));  //最近时间
    sqlquery.bindValue(":nRecentHour", QVariant(0));
    sqlquery.bindValue(":nRecentDay", QVariant(0));
    sqlquery.bindValue(":nRecentMonth", QVariant(0));
    sqlquery.bindValue(":nRecentYear", QVariant(0));

    sqlquery.bindValue(":nStartYear", QVariant(0));  //起始日期
    sqlquery.bindValue(":nStartMonth", QVariant(0));  //起始日期
    sqlquery.bindValue(":nStartDay", QVariant(0));  //起始日期
    sqlquery.bindValue(":nStartHour", QVariant(0));  //起始时间
    sqlquery.bindValue(":nStartMinute", QVariant(0));  //起始时间
    sqlquery.bindValue(":nEndYear", QVariant(0));  //终止日期
    sqlquery.bindValue(":nEndMonth", QVariant(0));  //终止日期
    sqlquery.bindValue(":nEndDay", QVariant(0));  //终止日期
    sqlquery.bindValue(":nEndHour", QVariant(0));  //终止时间
    sqlquery.bindValue(":nEndMinute", QVariant(0));  //终止时间
    sqlquery.bindValue(":nCurveAlpha", QVariant(m_alpha));  //透明度
    sqlquery.bindValue(":nShowPropId", QVariant(0));  //这个没有显示属性*/
    sqlquery.bindValue(":mFromAddr", QVariant(0));
    sqlquery.bindValue(":mToAddr", QVariant(0));

    sqlquery.bindValue(":nZvalue", QVariant(zValue()));      //Z序
    sqlquery.bindValue(":nCollidindId", QVariant(index));      //index

    bool result = sqlquery.exec();

    bool re = sqlquery.prepare("INSERT INTO trendsChannelSet(nItemId,nStartAddrX ,nStartAddrY ,nNumOfChannel,"
		"nDisplayCondition,nDisplayAddr,nLineType,nLineThickness,nDisplayColor)"
        "VALUES(:nItemId,:nStartAddrX ,:nStartAddrY ,:nNumOfChannel,"
		":nDisplayCondition,:nDisplayAddr,:nLineType,:nLineThickness,:nDisplayColor)");
	qDebug() << "sqlquery.prepare" << re;

    ChannelGroupInfo info1;
    int k = count;
    int temp = count;
    for(int i = 0; i < m_vecChannelGroups.size(); i++)
    {
        k++;
        info1 = m_vecChannelGroups.at(i);

        sqlquery.bindValue(":nItemId", QVariant(itemId));             //表id
        sqlquery.bindValue(":nStartAddrX", QVariant(-1));
        sqlquery.bindValue(":nStartAddrY", QVariant(-1));

		int nGroupIndex = 0;
		int groupNum = pwnd->m_pSamSysParame->m_loadDataSampling.size();
		for(int nIndex =0; nIndex < groupNum; nIndex++)
		{
			if(pwnd->m_pSamSysParame->m_vecDataSamplingStr[nIndex] == info1.m_sGroupName)
			{
				for(int j=0; j<nIndex;j++)
				{
					if(pwnd->m_pSamSysParame->m_loadDataSampling[j].nDataSampType ==
						pwnd->m_pSamSysParame->m_loadDataSampling[nIndex].nDataSampType)
					{
                        nGroupIndex++;
					}
				}
				sqlquery.bindValue(":nNumOfChannel", QVariant(nGroupIndex));        //组号
				break;
			}
		}
        sqlquery.bindValue(":nDataType", QVariant(info1.m_eDataType));              //数据类型
        sqlquery.bindValue(":nSourceMin", QVariant(info1.m_nSourceMin));            //输入范围最小值
        sqlquery.bindValue(":nSourceMax", QVariant(info1.m_nSourceMax));            //输入范围最大值
        sqlquery.bindValue(":nDisplayMin", QVariant(info1.m_nDisplayMin));          //显示符号最小值
        sqlquery.bindValue(":nDisplayMax", QVariant(info1.m_nDisplayMax));          //显示符号最大值

        sqlquery.bindValue(":nDisplayCondition", QVariant(info1.eDisplayCondition));      //显示条件
        sqlquery.bindValue(":nDisplayAddr", QVariant(k));//显示ON/OFF地址

        sqlquery.bindValue(":nLineType", QVariant(info1.eLineType));      //线型
        sqlquery.bindValue(":nLineThickness", QVariant(info1.nLineThickness));      //线条宽度
        ck = ColorToInt(info1.nDisplayColor);
        sqlquery.bindValue(":nDisplayColor", QVariant(ck));      //显示颜色

        bool mb = sqlquery.exec();
    }

    //插入监视地址表
    for(int i = 0; i < m_vecChannelGroups.size(); i++)
    {
        count++;

        //修改地址编译参数
        ADDR_PARAMENTS stParams;
        stParams.id         = count;
        stParams.itemId     = itemId;
        stParams.eType      = OBJ_ITEM;
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
        stParams.addrNum    = i;

        Keyboard kb = m_vecChannelGroups.at(i).KeyAddr;
        kb.compile(db,stParams);

        //m_vecDisplayGroups.at(i).KeyAddr.compile(db,count,0,OBJ_ITEM);
        //sqlquery.bindValue(":nWatchAddr", QVariant(count));
        //sqlquery.exec();
    }
}

void QTrendDataGroupAttr::save(QDataStream &stream)//将item存入数据流
{
    QVisableItem::save(stream);

    //曲线外观
    stream << m_bIsAll;             //个别，全部
    stream << m_sCurChnnel;      //当前组名
    stream << m_sChnnelBegin;       //起始组号
    stream << m_nTotalTrendNumber;  //曲线总组数
    stream << m_nDisplayMax;
    stream << m_nDisplayMin;
    stream << m_selGroups.size();
    for(int i=0; i<m_selGroups.size(); i++)
    {
        stream << m_selGroups.at(i);
    }
    for(int i = 0; i < m_vecChannelGroups.size(); i++)
    {
        stream << (int)m_vecChannelGroups.at(i).m_eDataType;
        stream << m_vecChannelGroups.at(i).m_sGroupName;
        stream << m_vecChannelGroups.at(i).m_nSourceMin;
        stream << m_vecChannelGroups.at(i).m_nSourceMax;
        stream << m_vecChannelGroups.at(i).m_nDisplayMin;
        stream << m_vecChannelGroups.at(i).m_nDisplayMax;
		stream << (int)m_vecChannelGroups.at(i).eDisplayCondition;
		
		Keyboard kb = m_vecChannelGroups.at(i).KeyAddr;
		stream << kb;
		stream << (int)m_vecChannelGroups.at(i).eLineType;
		stream << m_vecChannelGroups.at(i).nLineThickness;
		stream << m_vecChannelGroups.at(i).nDisplayColor;
    }


    //显示区
    stream << m_bSelectVertMinor;   //是否显示垂直次标尺
    stream << m_bSelectHorMinor;    //是否显示水平次标尺
    stream << m_bMainVer;
    stream << m_bMainHor;


    stream << m_nDataSample;        //数据样本数
    stream << m_nVertMajorScale;    //垂直主标尺
    stream << m_nVertMinorScale;    //垂直次标尺
    stream << m_nHorMajorScale;     //水平次标尺
    stream << m_nHorMinorScale;     //水平主标尺

    //颜色
    stream << m_bGrade;
    stream << m_nVerColor;
    stream << m_nHorColor;
    stream << m_nBoradColor;
    stream << m_nScaleColor;
    stream << m_nGraphColor;
    stream << m_nFontSize;
    stream << m_nMarkedColor;
    stream << m_alpha;
}

void QTrendDataGroupAttr::load(QDataStream &stream)//从数据流导出item
{
    int temp;
    QVisableItem::load(stream);

    //曲线外观
    stream >> m_bIsAll;             //个别，全部
    stream >> m_sCurChnnel;      //当前组名
    stream >> m_sChnnelBegin;       //起始组名
    stream >> m_nTotalTrendNumber;  //曲线总组数
    stream >> m_nDisplayMax;
    stream >> m_nDisplayMin;
    stream >> temp;
    m_selGroups.clear();
    for(int i = 0; i < temp; i++)
    {
        QString sTmp;
        stream >> sTmp;
        m_selGroups.append(sTmp);
    }
    m_vecChannelGroups.clear();
    ChannelGroupInfo info_1;
	for(int i = 0; i < m_selGroups.size(); i++)
    {
        stream >> temp;
        info_1.m_eDataType = (CurveDataType)temp;
        stream >> info_1.m_sGroupName;
        stream >> info_1.m_nSourceMin;
        stream >> info_1.m_nSourceMax;
        stream >> info_1.m_nDisplayMin;
        stream >> info_1.m_nDisplayMax;
        stream >> temp;
        info_1.eDisplayCondition = (DisConType)temp;

        stream >> info_1.KeyAddr;
        stream >> temp;
        info_1.eLineType = (LineStyleType)temp;
        stream >> info_1.nLineThickness;
        stream >> info_1.nDisplayColor;

        m_vecChannelGroups.push_back(info_1);
    }

    

    //显示区
    stream >> m_bSelectVertMinor;
    stream >> m_bSelectHorMinor;
    if(pwnd->getProVersion() < 2764)//旧版本
    {
        m_bMainVer = true;
        m_bMainHor = true;
    }
    else
    {
        stream >> m_bMainVer;         //是否显示垂直主标尺
        stream >> m_bMainHor;         //是否显示水平主标尺
    }
    //stream >> m_bMainHor;
    //stream >> m_bMainVer;
    stream >> m_nDataSample;
    stream >> m_nVertMajorScale;
    stream >> m_nVertMinorScale;
    stream >> m_nHorMajorScale;
    stream >> m_nHorMinorScale;

    //颜色
    stream >> m_bGrade;
    stream >> m_nVerColor;
    stream >> m_nHorColor;
    stream >> m_nBoradColor;
    stream >> m_nScaleColor;
    stream >> m_nGraphColor;
    stream >> m_nFontSize;
    if(pwnd->getProVersion() >= 2527)//旧版本
    {
        QString str;
        stream >> m_nMarkedColor;
    }

    if(pwnd->getProVersion() >= 2667)//新版本
    {
        stream >> m_alpha;
    }
    else{
        m_alpha = 255;
    }

}

QVector<ADDRPRO> QTrendDataGroupAttr::getAllItemAddr()
{
    kb.clear();
    kb = QVisableItem::getAllItemAddr();

	for (int i=0; i<m_vecChannelGroups.size(); i++)
	{
	
        ADDRPRO addrPro;
        QString str;
        if (m_vecChannelGroups[i].eDisplayCondition != DisplayKeep)
        {
            addrPro.pAddr = &m_vecChannelGroups[i].KeyAddr;
            addrPro.str   = QObject::tr("通道")+m_vecChannelGroups[i].m_sGroupName+QObject::tr("控制地址");
            addrPro.type  = 0;
            kb << addrPro;
        }
        if (m_bIsAll)
        {
            break;
        }
    }
    return kb;
}

QString  QTrendDataGroupAttr::getItemName()
{
    return QObject::tr("数据群组");
}
//数据采样的一组数据被改变。刷新控件
void QTrendDataGroupAttr::sampChanged(QString oldName,QString newName,int sampType)
{
	if (m_selGroups.contains(oldName))
	{
		if (newName.isEmpty() || sampType == 2)//删除了该组数据 或者改变为历史数据
		{
			int index = m_selGroups.indexOf(oldName);
			if (index >=0)
			{
				m_selGroups.remove(index);
			}
			
			for(int i=0; i<m_vecChannelGroups.size();i++)
			{
				if (m_vecChannelGroups[i].m_sGroupName == oldName)
				{
					m_vecChannelGroups.remove(i);
					break;
				}
			}
		}
		else//修改了组属性
		{
			int index = m_selGroups.indexOf(oldName);
			if (index >=0)
			{
				m_selGroups.replace(index,newName);
			}
			
			for(int i=0; i<m_vecChannelGroups.size();i++)
			{
				if (m_vecChannelGroups[i].m_sGroupName == oldName)
				{
					m_vecChannelGroups[i].m_sGroupName = oldName;
					break;
				}
			}
		}
	}
}
