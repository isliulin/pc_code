#include "qtrendattr.h"

extern MainWindow *pwnd;

QTrendAttr::QTrendAttr(QGraphicsItem *parent):QVisableItem(parent)//QItemGroup(parent)//
{

}

QTrendAttr::~QTrendAttr()
{

}

int QTrendAttr::GroupType()//�ؼ����� ����ͼ
{
    //return GROUP_TYPE_TRENDCHART;
    return SAM_DRAW_GROUP_TREND;
}

QTrendAttr* QTrendAttr::Clone()//����item
{
    QGraphicsItem* pCopy = NULL;
    QGraphicsItem* pItem = NULL;

    QTrendAttr *itemGroup = new QTrendAttr;

    QList<QGraphicsItem *> itemList;
    itemList = childItems();
    int size = itemList.size();

    for(int i=0;i<size;i++)
    {
        pItem = itemList.at(i);

        switch(pItem->type())
        {
        case SAM_DRAW_OBJECT_RECT:              //����
            {
                QRectItem *rectItem = dynamic_cast<QRectItem *>(pItem);
                if(rectItem)
                {
                    pCopy = rectItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_ELIPSE:              //Բ
            {
                QElipseItem *elipseItem = dynamic_cast<QElipseItem *>(pItem);
                if(elipseItem)
                {
                    pCopy = elipseItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_LINE:                 //ֱ��
            {
                QLineItem * lineItem = dynamic_cast<QLineItem *>(pItem);
                if(lineItem)
                {
                    pCopy = lineItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_POLYGON:              //�����
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
    itemGroup->m_Channels             = m_Channels;
    itemGroup->m_eTableType         = m_eTableType;
    itemGroup->m_sGroupNum          = m_sGroupNum;
    itemGroup->m_nCurChnnelNum      = m_nCurChnnelNum;
    itemGroup->m_nChnnelBegin       = m_nChnnelBegin;
    itemGroup->m_nTotalTrendNumber  = m_nTotalTrendNumber;
    itemGroup->m_vecChannelGroups   = m_vecChannelGroups;
    //for(int i = 0; i < m_vecChannelGroups.size(); i++)

    itemGroup->m_bSelectVertMinor   = m_bSelectVertMinor;
    itemGroup->m_bSelectHorMinor    = m_bSelectHorMinor;
    itemGroup->m_bMainVer           = m_bMainVer;
    itemGroup->m_bMainHor           = m_bMainHor;
    itemGroup->m_nDataSample        = m_nDataSample;
    itemGroup->m_nScrollSample      = m_nScrollSample;
    itemGroup->m_nVertMajorScale    = m_nVertMajorScale;
    itemGroup->m_nVertMinorScale    = m_nVertMinorScale;
    itemGroup->m_nHorMajorScale     = m_nHorMajorScale;
    itemGroup->m_nHorMinorScale     = m_nHorMinorScale;
    itemGroup->m_vecDisplayGroups   = m_vecDisplayGroups;

    itemGroup->m_bGrade             = m_bGrade;
    itemGroup->m_nVerColor          = m_nVerColor;
    itemGroup->m_nHorColor          = m_nHorColor;
    itemGroup->m_nBoradColor        = m_nBoradColor;
    itemGroup->m_nScaleColor        = m_nScaleColor;
    itemGroup->m_nGraphColor        = m_nGraphColor;
    itemGroup->m_alpha              = m_alpha;
    itemGroup->m_vecGroupColor      = m_vecGroupColor;
    //for(int i = 0; i < m_vecGroupColor.size(); i++)

    //itemGroup->m_eTimeUnit      = m_eTimeUnit;  //X��ʱ�䵥λ
    itemGroup->m_eTimeFormat    = m_eTimeFormat;  //ʱ���ʽ
    itemGroup->m_eDateFormat    = m_eDateFormat;  //���ڸ�ʽ
    itemGroup->m_eFontType      = m_eFontType;    //��������
    itemGroup->m_eTxtAttr       = m_eTxtAttr;     //�ı�����
    itemGroup->m_eStart         = m_eStart;       //����ʱ��ɼ���ʽ
    //itemGroup->m_eCurTime       = m_eCurTime;   //�ӿ�ʼ�õ�ʱ�䵥λ
    itemGroup->m_bXMarked       = m_bXMarked;     //�Ƿ�X���ע
    itemGroup->m_nFontSize      = m_nFontSize;    //�����С
    itemGroup->m_nMarkedColor   = m_nMarkedColor; //��ע��ɫ
    itemGroup->m_nTimeLen       = m_nTimeLen;     //���ʱ��
    itemGroup->m_eTimeUnitNear  = m_eTimeUnitNear;//���ʱ�䵥λ
    itemGroup->m_dFromDate      = m_dFromDate;    //��ʼ����
    itemGroup->m_tFromTime      = m_tFromTime;    //��ʼʱ��
    itemGroup->m_dToDate        = m_dToDate;      //��ֹ����
    itemGroup->m_tToTime        = m_tToTime;      //��ֹʱ��
    itemGroup->m_nDisplayMax    = m_nDisplayMax;
    itemGroup->m_nDisplayMin    = m_nDisplayMin;
    itemGroup->m_Channels       = m_Channels;
    itemGroup->m_kbFrom         = m_kbFrom;
    itemGroup->m_kbTo           = m_kbTo;
    itemGroup->m_bDateFormat    = this->m_bDateFormat;
    itemGroup->m_bTimeFormat    = this->m_bTimeFormat;
    itemGroup->setId(id());

    return itemGroup;
}

void QTrendAttr::compile(QSqlDatabase &db, int nSceneId, int &count, int index)//�����ʱ�򱣴�item�����ݿ�
{
    count++;
    QVisableItem::compile(db, nSceneId, count, index);

    int itemId = count;
    if(sPro.enableTouch && !sPro.byGroups_T)
    {
            //������λ���� ��һ����ַ��
            count++;
    }
    if(sPro.bNotice)
    {
            //���ؽ���֪ͨ����ַ ����һ����ַ��
            count++;
    }
    if(sPro.enableVisable && !sPro.byGroups_V)
    {
            //������λ���� ����һ����ַ��
            count++;
    }

    int ck;
    QSqlQuery sqlquery(db);
    bool r = sqlquery.prepare("INSERT INTO trends(nItemId,nSceneId,nTopLeftX,nTopLeftY,nWidth,nHeight,nCurveX,nCurveY,nCurveWd,nCurveHt,"               
                    "nCurveType,nGroupNum,nChannelNum,nDisplayMax,nDisplayMin,nDataSample,nScrollSample,nVertMajorScale,bSelectVertMinor,nVertMinorScale,nHorMajorScale,"
                    "bSelectHorMinor,nHorMinorScale,bSelectNet,nVertNetColor,nHorNetColor,nBoradColor,nScaleColor,nGraphColor,sFontType,nFontSize,"
                    "nFontAttri,nDate,nTime,nMarkColor,bXmark,nTimeRange,nRecentYear,nRecentMonth,nRecentDay,nRecentHour,"
                    "nRecentMinute,nStartYear,nStartMonth,nStartDay,nStartHour,nStartMinute,nEndYear,nEndMonth,nEndDay,nEndHour,"
                    "nEndMinute,nCurveAlpha,nZvalue,nCollidindId,nShowPropId,bMainVer,bMainHor,mFromAddr,mToAddr,bDate,bTime)"
                "VALUES(:nItemId,:nSceneId,:nTopLeftX,:nTopLeftY,:nWidth,:nHeight,:nCurveX,:nCurveY,:nCurveWd,:nCurveHt,"
				":nCurveType,:nGroupNum,:nChannelNum,:nDisplayMax,:nDisplayMin,:nDataSample,:nScrollSample,:nVertMajorScale,:bSelectVertMinor,:nVertMinorScale,:nHorMajorScale,"
                    ":bSelectHorMinor,:nHorMinorScale,:bSelectNet,:nVertNetColor,:nHorNetColor,:nBoradColor,:nScaleColor,:nGraphColor,:sFontType,:nFontSize,"
                    ":nFontAttri,:nDate,:nTime,:nMarkColor,:bXmark,:nTimeRange,:nRecentYear,:nRecentMonth,:nRecentDay,:nRecentHour,"
                    ":nRecentMinute,:nStartYear,:nStartMonth,:nStartDay,:nStartHour,:nStartMinute,:nEndYear,:nEndMonth,:nEndDay,:nEndHour,"
                    ":nEndMinute,:nCurveAlpha,:nZvalue,:nCollidindId,:nShowPropId,:bMainVer,:bMainHor,:mFromAddr,:mToAddr,:bDate,:bTime)");

    qDebug() << "sqlquery.prepare" << r;
    sqlquery.bindValue(":nItemId", QVariant(itemId));                //��id
    sqlquery.bindValue(":nSceneId", QVariant(nSceneId));            //scene id

    QRectF rect = sceneBoundingRect();//��Գ��������꼰�߿�
    sqlquery.bindValue(":nTopLeftX", QVariant((short)rect.left()));//left
    sqlquery.bindValue(":nTopLeftY", QVariant((short)rect.top()));//top
    sqlquery.bindValue(":nWidth", QVariant((short)rect.width()));//width
    sqlquery.bindValue(":nHeight", QVariant((short)rect.height()));//height

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

    sqlquery.bindValue(":nCurveType", QVariant(m_eTableType));      //ͼ������
    int num = pwnd->m_pSamSysParame->m_loadDataSampling.size();
    int nGroupIndex = 0;
	QVector<int> sampleNumbers;
    for(int i = 0; i < num; i++)
    {
        qDebug() <<"string size"<< pwnd->m_pSamSysParame->m_vecDataSamplingStr.size();
        qDebug() <<"sampling size"<< pwnd->m_pSamSysParame->m_loadDataSampling.size();
        if(pwnd->m_pSamSysParame->m_vecDataSamplingStr[i] == m_sGroupNum)
        {
            for(int j=0; j<i;j++)
            {
                if(pwnd->m_pSamSysParame->m_loadDataSampling[j].nDataSampType ==
                   pwnd->m_pSamSysParame->m_loadDataSampling[i].nDataSampType)
                {
                    nGroupIndex++;
                }
            }
			foreach(DATA_ADDRESS_ITEM item,pwnd->m_pSamSysParame->m_loadDataSampling[i].m_dataTable)
			{
				sampleNumbers << item.nAddrNumber;
			}
            sqlquery.bindValue(":nGroupNum", QVariant(nGroupIndex));        //���
            break;
        }
    }
    sqlquery.bindValue(":nChannelNum", QVariant(m_nTotalTrendNumber));     //ͨ����
    sqlquery.bindValue(":nDisplayMax", QVariant(m_nDisplayMax)); //��ʾ��Χ���ֵ
	sqlquery.bindValue(":nDisplayMin", QVariant(m_nDisplayMin)); //��ʾ��Χ��Сֵ

    sqlquery.bindValue(":nDataSample", QVariant(m_nDataSample));     //����������
    sqlquery.bindValue(":nScrollSample", QVariant(m_nScrollSample));   //����������
    sqlquery.bindValue(":nVertMajorScale", QVariant(m_nVertMajorScale)); //��ֱ�����
    sqlquery.bindValue(":bMainVer", QVariant(m_bMainVer)); //�Ƿ�ֱ�����
    sqlquery.bindValue(":bSelectVertMinor", QVariant(m_bSelectVertMinor));//�Ƿ���ʾ��ֱ�α��
    sqlquery.bindValue(":nVertMinorScale", QVariant(m_nVertMinorScale)); //��ֱ�α��
    sqlquery.bindValue(":bMainHor", QVariant(m_bMainHor)); //�Ƿ�ֱ�����
    sqlquery.bindValue(":nHorMajorScale", QVariant(m_nHorMajorScale));  //ˮƽ�����
    sqlquery.bindValue(":bSelectHorMinor", QVariant(m_bSelectHorMinor)); //�Ƿ���ʾˮƽ�α��
    sqlquery.bindValue(":nHorMinorScale", QVariant(m_nHorMinorScale));  //ˮƽ�α��

    sqlquery.bindValue(":bSelectNet", QVariant(m_bGrade));  //�Ƿ���Ҫ����
    ck = ColorToInt(m_nVerColor);
    sqlquery.bindValue(":nVertNetColor", QVariant(ck));  //ˮƽ������ɫ
    ck = ColorToInt(m_nHorColor);
    sqlquery.bindValue(":nHorNetColor", QVariant(ck));  //��ֱ������ɫ
    ck = ColorToInt(m_nBoradColor);
    sqlquery.bindValue(":nBoradColor", QVariant(ck));      //�߿���ɫ
    ck = ColorToInt(m_nScaleColor);
    sqlquery.bindValue(":nScaleColor", QVariant(ck));      //�����ɫ
    ck = ColorToInt(m_nGraphColor);
    sqlquery.bindValue(":nGraphColor", QVariant(ck));      //ͼ������ɫ

    sqlquery.bindValue(":sFontType", QVariant(m_eFontType));    //��������
    sqlquery.bindValue(":nFontSize", QVariant(m_nFontSize));    //�����С
    sqlquery.bindValue(":nFontAttri", QVariant(m_eTxtAttr));    //�ı�����
    sqlquery.bindValue(":nDate", QVariant(m_eDateFormat));      //���ڸ�ʽ
    sqlquery.bindValue(":nTime", QVariant(m_eTimeFormat));      //ʱ���ʽ
    sqlquery.bindValue(":nMarkColor", QVariant(ColorToInt(m_nMarkedColor)));//��ע��ɫ
    sqlquery.bindValue(":bXmark", QVariant(m_bXMarked));        //�Ƿ�X���ע
    sqlquery.bindValue(":nTimeRange", QVariant(m_eStart));      //����ʱ��ɼ���ʽ
    switch(m_eTimeUnitNear)//���ʱ�䵥λ
    {
        case UNIT_MINUTE:
        {
            sqlquery.bindValue(":nRecentMinute", QVariant(m_nTimeLen));  //���ʱ��
            sqlquery.bindValue(":nRecentHour", QVariant(0));
            sqlquery.bindValue(":nRecentDay", QVariant(0));
            sqlquery.bindValue(":nRecentMonth", QVariant(0));
            sqlquery.bindValue(":nRecentYear", QVariant(0));
        }
        break;

        case UNIT_HOUR:
        {
            sqlquery.bindValue(":nRecentHour", QVariant(m_nTimeLen));  //���ʱ��
            sqlquery.bindValue(":nRecentMinute", QVariant(0));
            sqlquery.bindValue(":nRecentDay", QVariant(0));
            sqlquery.bindValue(":nRecentMonth", QVariant(0));
            sqlquery.bindValue(":nRecentYear", QVariant(0));
        }
        break;

        case UNIT_DAY:
        {
            sqlquery.bindValue(":nRecentDay", QVariant(m_nTimeLen));  //���ʱ��
            sqlquery.bindValue(":nRecentMinute", QVariant(0));
            sqlquery.bindValue(":nRecentHour", QVariant(0));
            sqlquery.bindValue(":nRecentMonth", QVariant(0));
            sqlquery.bindValue(":nRecentYear", QVariant(0));
        }
        break;

        case UNIT_MONTH:
        {
            sqlquery.bindValue(":nRecentMonth", QVariant(m_nTimeLen));  //���ʱ��
            sqlquery.bindValue(":nRecentMinute", QVariant(0));
            sqlquery.bindValue(":nRecentHour", QVariant(0));
            sqlquery.bindValue(":nRecentDay", QVariant(0));
            sqlquery.bindValue(":nRecentYear", QVariant(0));
        }
        break;

        case UNIT_YEAR:
        {
            sqlquery.bindValue(":nRecentYear", QVariant(m_nTimeLen));  //���ʱ��
            sqlquery.bindValue(":nRecentMinute", QVariant(0));
            sqlquery.bindValue(":nRecentHour", QVariant(0));
            sqlquery.bindValue(":nRecentDay", QVariant(0));
            sqlquery.bindValue(":nRecentMonth", QVariant(0));
        }
        break;

        default:
        {
            sqlquery.bindValue(":nRecentMinute", QVariant(m_nTimeLen));  //���ʱ��
            sqlquery.bindValue(":nRecentHour", QVariant(0));
            sqlquery.bindValue(":nRecentDay", QVariant(0));
            sqlquery.bindValue(":nRecentMonth", QVariant(0));
            sqlquery.bindValue(":nRecentYear", QVariant(0));
        }
        break;
    }

    sqlquery.bindValue(":nStartYear", QVariant(m_dFromDate.year()));  //��ʼ����
    sqlquery.bindValue(":nStartMonth", QVariant(m_dFromDate.month()));  //��ʼ����
    sqlquery.bindValue(":nStartDay", QVariant(m_dFromDate.day()));  //��ʼ����
    sqlquery.bindValue(":nStartHour", QVariant(m_tFromTime.hour()));  //��ʼʱ��
    sqlquery.bindValue(":nStartMinute", QVariant(m_tFromTime.minute()));  //��ʼʱ��
    sqlquery.bindValue(":nEndYear", QVariant(m_dToDate.year()));  //��ֹ����
    sqlquery.bindValue(":nEndMonth", QVariant(m_dToDate.month()));  //��ֹ����
    sqlquery.bindValue(":nEndDay", QVariant(m_dToDate.day()));  //��ֹ����
    sqlquery.bindValue(":nEndHour", QVariant(m_tToTime.hour()));  //��ֹʱ��
    sqlquery.bindValue(":nEndMinute", QVariant(m_tToTime.minute()));  //��ֹʱ��
    sqlquery.bindValue(":nCurveAlpha", QVariant(255));  //͸����
    //sqlquery.bindValue(":nShowPropId", QVariant());  //���û����ʾ����

    sqlquery.bindValue(":nZvalue", QVariant(zValue()));      //Z��
    sqlquery.bindValue(":nCollidindId", QVariant(index));      //index
    sqlquery.bindValue(":nShowPropId", QVariant(0));         //shit

    ck = count;
    if(m_eStart == START_ADDR)
    {
        //ck = count;
        ck++;
        sqlquery.bindValue(":mFromAddr", QVariant(ck));
        ck++;
        sqlquery.bindValue(":mToAddr", QVariant(ck));
    }
    else
    {
        sqlquery.bindValue(":mFromAddr", QVariant(-1));
        sqlquery.bindValue(":mToAddr", QVariant(-1));
    }

    sqlquery.bindValue(":bDate", QVariant(m_bDateFormat));
    sqlquery.bindValue(":bTime", QVariant(m_bTimeFormat));

    bool result = false;
    result = sqlquery.exec();
    qDebug() << "-------------insert trends table :" << result << endl;
    //sqlquery.exec();
    bool re = sqlquery.prepare("INSERT INTO trendsChannelSet(nItemId,nStartAddrX ,nStartAddrY ,nNumOfChannel,"
                 "nDisplayCondition,nDisplayAddr,nLineType,nLineThickness,nDisplayColor)"
                 "VALUES(:nItemId,:nStartAddrX ,:nStartAddrY ,:nNumOfChannel,"
                 ":nDisplayCondition,:nDisplayAddr,:nLineType,:nLineThickness,:nDisplayColor)");
    qDebug() << "sqlquery.prepare" << re;

    ChannelGroupInfo info1;
    DisplayGroupInfo info2;
    ColorGroupInfo   info3;
    int k = ck;

    for(int i = 0; i < m_vecChannelGroups.size(); i++)
    {
        k++;
        info1 = m_vecChannelGroups.at(i);
        //info2 = m_vecDisplayGroups.at(i);
        //info3 = m_vecGroupColor.at(i);

        sqlquery.bindValue(":nItemId", QVariant(itemId));             //��id
        sqlquery.bindValue(":nStartAddrX", QVariant(-1));
        sqlquery.bindValue(":nStartAddrY", QVariant(-1));
        sqlquery.bindValue(":nNumOfChannel", QVariant(sampleNumbers.indexOf(info1.m_nNumOfChannel)));      //ͨ����
        
        sqlquery.bindValue(":nDisplayCondition", QVariant(info1.eDisplayCondition));      //��ʾ����
        sqlquery.bindValue(":nDisplayAddr", QVariant(k));//��ʾON/OFF��ַ

        sqlquery.bindValue(":nLineType", QVariant(info1.eLineType));      //����
        sqlquery.bindValue(":nLineThickness", QVariant(info1.nLineThickness));      //�������
        ck = ColorToInt(info1.nDisplayColor);
        sqlquery.bindValue(":nDisplayColor", QVariant(ck));      //��ʾ��ɫ

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "-------------insert nDisplayColor table :" << result << endl;
    }

    if(m_eStart == START_ADDR)
    {
        count++;
        ADDR_PARAMENTS stParams;
        stParams.id         = count;
        stParams.itemId     = itemId;
        stParams.eType      = OBJ_ITEM;
        stParams.eRWtype    = SCENE_CONTROL_LOOP_R;
        stParams.addrNum    = -1;
        m_kbFrom.Length     = 6;
        m_kbFrom.compile(db,stParams);

        count++;
        stParams.id         = count;
        stParams.itemId     = itemId;
        stParams.eType      = OBJ_ITEM;
        stParams.eRWtype    = SCENE_CONTROL_LOOP_R;
        stParams.addrNum    = -1;
        m_kbTo.Length       = 6;
        m_kbTo.compile(db,stParams);
    }

    //������ӵ�ַ��
    for(int i = 0; i < m_vecChannelGroups.size(); i++)
    {
        count++;

        //�޸ĵ�ַ�������
        ADDR_PARAMENTS stParams;
        stParams.id         = count;
        stParams.itemId     = itemId;
        stParams.eType      = OBJ_ITEM;
        stParams.eRWtype    = SCENE_CONTROL_LOOP_R;
        stParams.addrNum    = i;

        Keyboard kb = m_vecChannelGroups.at(i).KeyAddr;
        kb.compile(db,stParams);
        sqlquery.bindValue(":nWatchAddr", QVariant(count));
        sqlquery.exec();
    }
}

void QTrendAttr::save(QDataStream &stream)//��item����������
{
    QVisableItem::save(stream);
    //QItemGroup::save(stream);

    //�������
    stream << m_bIsAll;       //����ȫ��
    stream << (int)m_eTableType;
    stream << m_sGroupNum;
    stream << m_nCurChnnelNum;  //ͨ����
    stream << m_nChnnelBegin;   //
    stream << m_vecChannelGroups.size();//

    for(int i = 0; i < m_vecChannelGroups.size(); i++)
    {
        stream << (int)m_vecChannelGroups.at(i).m_eDataType;
        stream << m_vecChannelGroups.at(i).m_nNumOfChannel;
        stream << m_vecChannelGroups.at(i).m_nSourceMin;
        stream << m_vecChannelGroups.at(i).m_nSourceMax;
        stream << m_vecChannelGroups.at(i).m_nDisplayMin;
        stream << m_vecChannelGroups.at(i).m_nDisplayMax;

		stream << m_vecChannelGroups.at(i).nLineThickness;
		stream << m_vecChannelGroups.at(i).nDisplayColor;
		stream << (int)m_vecChannelGroups.at(i).eLineType;
		stream << (int)m_vecChannelGroups.at(i).eDisplayCondition;
		Keyboard kb = m_vecChannelGroups.at(i).KeyAddr;
		stream << kb;
    }

    //��ʾ��
    stream << m_bSelectVertMinor;
    stream << m_bSelectHorMinor;
    stream << m_bMainVer;         //�Ƿ���ʾ��ֱ�����
    stream << m_bMainHor;         //�Ƿ���ʾˮƽ�����
    stream << m_nDataSample;
    stream << m_nScrollSample;
    stream << m_nVertMajorScale;
    stream << m_nVertMinorScale;
    stream << m_nHorMajorScale;
    stream << m_nHorMinorScale;
    

    //��ɫ
    stream << m_bGrade;
    stream << m_nVerColor;
    stream << m_nHorColor;
    stream << m_nBoradColor;
    stream << m_nScaleColor;
    stream << m_nGraphColor;
    

    //ʱ����ʾ
    //stream << (short)m_eTimeUnit;    //X��ʱ�䵥λ
    stream << (int)m_eTimeFormat;  //ʱ���ʽ
    stream << (int)m_eDateFormat;  //���ڸ�ʽ
    stream << (int)m_eFontType;    //��������
    stream << (int)m_eTxtAttr;     //�ı�����
    stream << (int)m_eStart;       //����ʱ��ɼ���ʽ
    //stream << (short)m_eCurTime;   //�ӿ�ʼ�õ�ʱ�䵥λ
    stream << m_bXMarked;            //�Ƿ�X���ע
    stream << m_nFontSize;           //�����С
    stream << m_nMarkedColor;        //��ע��ɫ
    stream << m_nTimeLen;            //���ʱ��
    stream << (int)m_eTimeUnitNear;//���ʱ�䵥λ
    stream << m_dFromDate;           //��ʼ����
    stream << m_tFromTime;           //��ʼʱ��
    stream << m_dToDate;             //��ֹ����
    stream << m_tToTime;             //��ֹʱ��
    stream << m_kbFrom;
    stream << m_kbTo;
    stream << this->m_bDateFormat;
    stream << this->m_bTimeFormat;
    stream << m_nDisplayMin;
    stream << m_nDisplayMax;
    stream << m_Channels.size();
    qDebug() <<"save trend end" <<m_Channels.size();
    foreach (int number,m_Channels)
    {
            stream << number;
    }
    stream << m_alpha;
}

void QTrendAttr::load(QDataStream &stream)//������������item
{
    int temp;
    QVisableItem::load(stream);
    //QItemGroup::load(stream);

    //�������
    stream >> m_bIsAll;       //����ȫ��
	
    stream >> temp;
    m_eTableType = (CurveType)temp;
    stream >> m_sGroupNum;
    stream >> m_nCurChnnelNum;//
    stream >> m_nChnnelBegin;//
    stream >> m_nTotalTrendNumber;//
    m_vecChannelGroups.clear();
    ChannelGroupInfo info_1;
    for(int i = 0; i < m_nTotalTrendNumber; i++)
    {
        stream >> temp;
        info_1.m_eDataType = (CurveDataType)temp;
        stream >> info_1.m_nNumOfChannel;
        stream >> info_1.m_nSourceMin;
        stream >> info_1.m_nSourceMax;
        stream >> info_1.m_nDisplayMin;
        stream >> info_1.m_nDisplayMax;

        stream >> info_1.nLineThickness;
        stream >> info_1.nDisplayColor;
        stream >> temp;
        info_1.eLineType = (LineStyleType)temp;
        stream >> temp;
        info_1.eDisplayCondition = (DisConType)temp;
        stream >> info_1.KeyAddr;
        m_vecChannelGroups.push_back(info_1);
    }

    //��ʾ��
    stream >> m_bSelectVertMinor;
    stream >> m_bSelectHorMinor;
    if(pwnd->getProVersion() < 2764)//�ɰ汾
    {
        m_bMainVer = true;
        m_bMainHor = true;
    }
    else
    {
        stream >> m_bMainVer;         //�Ƿ���ʾ��ֱ�����
        stream >> m_bMainHor;         //�Ƿ���ʾˮƽ�����
    }
    //stream >> m_bMainVer;         //�Ƿ���ʾ��ֱ�����
    //stream >> m_bMainHor;         //�Ƿ���ʾˮƽ�����
    stream >> m_nDataSample;
    stream >> m_nScrollSample;
    stream >> m_nVertMajorScale;
    stream >> m_nVertMinorScale;
    stream >> m_nHorMajorScale;
    stream >> m_nHorMinorScale;
    

    //��ɫ
    stream >> m_bGrade;
    stream >> m_nVerColor;
    stream >> m_nHorColor;
    stream >> m_nBoradColor;
    stream >> m_nScaleColor;
    stream >> m_nGraphColor;
    

    //stream << temp;
    //m_eTimeUnit = (TimeUnitType)temp;;      //X��ʱ�䵥λ
    stream >> temp;
    m_eTimeFormat = (TimeType)temp;;        //ʱ���ʽ
    stream >> temp;
    m_eDateFormat = (DateType)temp;;        //���ڸ�ʽ
    stream >> temp;
    m_eFontType = (FontType)temp;;          //��������
    stream >> temp;
    m_eTxtAttr = (TxtAttrType)temp;         //�ı�����
    stream >> temp;
    m_eStart = (CurveStartType)temp;        //����ʱ��ɼ���ʽ
    //stream << temp;
    //m_eCurTime = (TimeUnitType)temp;      //�ӿ�ʼ�õ�ʱ�䵥λ
    stream >> m_bXMarked;                   //�Ƿ�X���ע
    stream >> m_nFontSize;                  //�����С
    stream >> m_nMarkedColor;               //��ע��ɫ
    stream >> m_nTimeLen;                   //���ʱ��
    stream >> temp;
    m_eTimeUnitNear = (TimeUnitType)temp;   //���ʱ�䵥λ
    stream >> m_dFromDate;                  //��ʼ����
    stream >> m_tFromTime;                  //��ʼʱ��
    stream >> m_dToDate;                    //��ֹ����
    stream >> m_tToTime;                    //��ֹʱ��

    if(pwnd->getProVersion() < 3020)//�ɰ汾
    {
        /*Keyboard kb;
        m_kbFrom = kb;
        m_kbTo   = kb;*/
    }
    else
    {
        stream >> m_kbFrom;
        stream >> m_kbTo;
    }

    if(pwnd->getProVersion() < 3077)
    {
        this->m_bDateFormat = true;
        this->m_bTimeFormat = true;
    }
    else
    {
        stream >> this->m_bDateFormat;
        stream >> this->m_bTimeFormat;
    }

    stream >> m_nDisplayMin;
    stream >> m_nDisplayMax;
    stream >> temp;
    qDebug() <<"load trend end" <<temp;
    m_Channels.clear();
    int chlIndex =0;
    for (int i=0;i<temp;i++)
    {
            stream >> chlIndex;
            m_Channels << chlIndex;
    }

    if(pwnd->getProVersion() >= 2667)//�°汾
    {
        stream >> m_alpha;
    }
    else{
        m_alpha = 255;
    }

}

QVector<ADDRPRO> QTrendAttr::getAllItemAddr()
{
    kb.clear();
    kb = QVisableItem::getAllItemAddr();

    if(pwnd->getProVersion() < 3020)//�ɰ汾
    {
    }
    else
    {
        if(m_eStart == START_ADDR)
        {
            ADDRPRO addrPro;

            addrPro.pAddr = &m_kbFrom;
            addrPro.str   = QObject::tr("����ʱ�䷶Χ������ʼʱ���ַ");
            addrPro.type  = 1;
            kb << addrPro;

            addrPro.pAddr = &m_kbTo;
            addrPro.str   = QObject::tr("����ʱ�䷶Χ������ֹʱ���ַ");
            addrPro.type  = 1;
            kb << addrPro;
        }
    }

    for (int i=0; i<m_vecChannelGroups.size(); i++)
    {
        ADDRPRO addrPro;
        QString str;
        if (m_vecChannelGroups[i].eDisplayCondition != DisplayKeep)
        {
            addrPro.pAddr = &m_vecChannelGroups[i].KeyAddr;
            addrPro.str   = QObject::tr("ͨ��")+QString::number(m_vecChannelGroups[i].m_nNumOfChannel)+QObject::tr("���Ƶ�ַ");
            addrPro.type  = 1;
            kb << addrPro;
        }
        if (m_bIsAll)
        {
            break;
        }
    }
    return kb;
}

QString  QTrendAttr::getItemName()
{
    return QObject::tr("����");
}

void QTrendAttr::sampChanged(QString oldName,QString newName,int sampType)
{
    if (oldName == m_sGroupNum)//��ǰ���߸��޸ĵĲ��������
    {
        m_sGroupNum = newName;
        if (newName.isEmpty())//ɾ��
        {
            m_vecChannelGroups.clear();
            m_nTotalTrendNumber = 0;
            m_Channels.clear();
        }
        else//�޸�
        {
            m_eTableType = (CurveType)sampType;
            DATA_SAMPLING datasample;
            int index = pwnd->m_pSamSysParame->m_vecDataSamplingStr.indexOf(newName);
            if (index >= 0 && index <pwnd->m_pSamSysParame->m_loadDataSampling.size())
            {
                datasample = pwnd->m_pSamSysParame->m_loadDataSampling[index];
                QVector<int >samples;
                QList<int >newChannels;
                QVector<ChannelGroupInfo >validchls;
                foreach(DATA_ADDRESS_ITEM item,datasample.m_dataTable)
                {
                    samples << item.nAddrNumber;
                }

                foreach(ChannelGroupInfo info,m_vecChannelGroups)
                {
                    if (samples.contains(info.m_nNumOfChannel))
                    {
                        validchls << info;
                        newChannels << info.m_nNumOfChannel;
                    }
                }
                m_vecChannelGroups = validchls;
                m_nTotalTrendNumber = validchls.size();
                m_Channels = newChannels;
            }
        }
    }
}
