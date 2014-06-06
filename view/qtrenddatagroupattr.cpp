#include "qtrenddatagroupattr.h"

extern MainWindow *pwnd;

QTrendDataGroupAttr::QTrendDataGroupAttr(QGraphicsItem *parent):QVisableItem(parent)
{
}

QTrendDataGroupAttr::~QTrendDataGroupAttr()
{

}

int QTrendDataGroupAttr::GroupType()//�ؼ����� ����Ⱥ��
{
    //return GROUP_TYPE_DATAGROUPDISPLAY;
    return SAM_DRAW_GROUP_GROUPDATA;
}

QTrendDataGroupAttr* QTrendDataGroupAttr::Clone()//����item
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

void QTrendDataGroupAttr::compile(QSqlDatabase &db, int nSceneId,int &count, int index)//�����ʱ�򱣴�item�����ݿ�
{
    int ck;
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
    sqlquery.bindValue(":nItemId", QVariant(itemId));                //��id
    sqlquery.bindValue(":nSceneId", QVariant(nSceneId));            //scene id

    QRectF rect = sceneBoundingRect();//��Գ��������꼰�߿�
    sqlquery.bindValue(":nTopLeftX", QVariant((short)rect.left()));//left
    sqlquery.bindValue(":nTopLeftY", QVariant((short)rect.top()));//top
    sqlquery.bindValue(":nWidth", QVariant((short)rect.width()));//width
    sqlquery.bindValue(":nHeight", QVariant((short)rect.height()));//height

    //QRectF rect1 = sceneBoundingRect();//��Գ��������꼰�߿�
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

    sqlquery.bindValue(":nCurveType", QVariant(3));                     //ͼ������,����Ⱥ��
    sqlquery.bindValue(":nGroupNum", QVariant(0));          //���
    sqlquery.bindValue(":nChannelNum", QVariant(m_selGroups.size()));         //������ͨ������
	sqlquery.bindValue(":nDisplayMax", QVariant(m_nDisplayMax)); //��ʾ��Χ���ֵ
	sqlquery.bindValue(":nDisplayMin", QVariant(m_nDisplayMin)); //��ʾ��Χ��Сֵ

    sqlquery.bindValue(":nDataSample", QVariant(m_nDataSample));            //����������
    sqlquery.bindValue(":nScrollSample", QVariant(0));      //����������
    sqlquery.bindValue(":nVertMajorScale", QVariant(m_nVertMajorScale));    //��ֱ�����
    sqlquery.bindValue(":bMainVer", QVariant(m_bMainVer));    //��ֱ�����
    sqlquery.bindValue(":bSelectVertMinor", QVariant(m_bSelectVertMinor));  //�Ƿ���ʾ��ֱ�α��
    sqlquery.bindValue(":nVertMinorScale", QVariant(m_nVertMinorScale));    //��ֱ�α��
    sqlquery.bindValue(":nHorMajorScale", QVariant(m_nHorMajorScale));      //ˮƽ�����
    sqlquery.bindValue(":bMainHor", QVariant(m_bMainHor));      //ˮƽ�����
    sqlquery.bindValue(":bSelectHorMinor", QVariant(m_bSelectHorMinor));    //�Ƿ���ʾˮƽ�α��
    sqlquery.bindValue(":nHorMinorScale", QVariant(m_nHorMinorScale));      //ˮƽ�α��

    sqlquery.bindValue(":bSelectNet", QVariant(m_bGrade));          //�Ƿ���Ҫ����
    ck = ColorToInt(m_nVerColor);
    sqlquery.bindValue(":nVertNetColor", QVariant(ck));    //ˮƽ������ɫ
    ck = ColorToInt(m_nHorColor);
    sqlquery.bindValue(":nHorNetColor", QVariant(ck));     //��ֱ������ɫ
    ck = ColorToInt(m_nBoradColor);
    sqlquery.bindValue(":nBoradColor", QVariant(ck));      //�߿���ɫ
    ck = ColorToInt(m_nScaleColor);
    sqlquery.bindValue(":nScaleColor", QVariant(ck));      //�����ɫ
    ck = ColorToInt(m_nGraphColor);
    sqlquery.bindValue(":nGraphColor", QVariant(ck));      //ͼ������ɫ
    ck = ColorToInt(m_nMarkedColor);
    sqlquery.bindValue(":nMarkColor", QVariant(ck));      //��ע��ɫ

    sqlquery.bindValue(":sFontType", QVariant(""));    //��������
    sqlquery.bindValue(":nFontSize", QVariant(m_nFontSize));    //�����С
    sqlquery.bindValue(":nFontAttri", QVariant(0));    //�ı�����
    sqlquery.bindValue(":nDate", QVariant(0));      //���ڸ�ʽ
    sqlquery.bindValue(":nTime", QVariant(0));      //ʱ���ʽ
    sqlquery.bindValue(":bXmark", QVariant(true));        //�Ƿ�X���ע
    sqlquery.bindValue(":nTimeRange", QVariant(0));      //����ʱ��ɼ���ʽ

    sqlquery.bindValue(":nRecentMinute", QVariant(0));  //���ʱ��
    sqlquery.bindValue(":nRecentHour", QVariant(0));
    sqlquery.bindValue(":nRecentDay", QVariant(0));
    sqlquery.bindValue(":nRecentMonth", QVariant(0));
    sqlquery.bindValue(":nRecentYear", QVariant(0));

    sqlquery.bindValue(":nStartYear", QVariant(0));  //��ʼ����
    sqlquery.bindValue(":nStartMonth", QVariant(0));  //��ʼ����
    sqlquery.bindValue(":nStartDay", QVariant(0));  //��ʼ����
    sqlquery.bindValue(":nStartHour", QVariant(0));  //��ʼʱ��
    sqlquery.bindValue(":nStartMinute", QVariant(0));  //��ʼʱ��
    sqlquery.bindValue(":nEndYear", QVariant(0));  //��ֹ����
    sqlquery.bindValue(":nEndMonth", QVariant(0));  //��ֹ����
    sqlquery.bindValue(":nEndDay", QVariant(0));  //��ֹ����
    sqlquery.bindValue(":nEndHour", QVariant(0));  //��ֹʱ��
    sqlquery.bindValue(":nEndMinute", QVariant(0));  //��ֹʱ��
    sqlquery.bindValue(":nCurveAlpha", QVariant(m_alpha));  //͸����
    sqlquery.bindValue(":nShowPropId", QVariant(0));  //���û����ʾ����*/
    sqlquery.bindValue(":mFromAddr", QVariant(0));
    sqlquery.bindValue(":mToAddr", QVariant(0));

    sqlquery.bindValue(":nZvalue", QVariant(zValue()));      //Z��
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

        sqlquery.bindValue(":nItemId", QVariant(itemId));             //��id
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
				sqlquery.bindValue(":nNumOfChannel", QVariant(nGroupIndex));        //���
				break;
			}
		}
        sqlquery.bindValue(":nDataType", QVariant(info1.m_eDataType));              //��������
        sqlquery.bindValue(":nSourceMin", QVariant(info1.m_nSourceMin));            //���뷶Χ��Сֵ
        sqlquery.bindValue(":nSourceMax", QVariant(info1.m_nSourceMax));            //���뷶Χ���ֵ
        sqlquery.bindValue(":nDisplayMin", QVariant(info1.m_nDisplayMin));          //��ʾ������Сֵ
        sqlquery.bindValue(":nDisplayMax", QVariant(info1.m_nDisplayMax));          //��ʾ�������ֵ

        sqlquery.bindValue(":nDisplayCondition", QVariant(info1.eDisplayCondition));      //��ʾ����
        sqlquery.bindValue(":nDisplayAddr", QVariant(k));//��ʾON/OFF��ַ

        sqlquery.bindValue(":nLineType", QVariant(info1.eLineType));      //����
        sqlquery.bindValue(":nLineThickness", QVariant(info1.nLineThickness));      //�������
        ck = ColorToInt(info1.nDisplayColor);
        sqlquery.bindValue(":nDisplayColor", QVariant(ck));      //��ʾ��ɫ

        bool mb = sqlquery.exec();
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
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
        stParams.addrNum    = i;

        Keyboard kb = m_vecChannelGroups.at(i).KeyAddr;
        kb.compile(db,stParams);

        //m_vecDisplayGroups.at(i).KeyAddr.compile(db,count,0,OBJ_ITEM);
        //sqlquery.bindValue(":nWatchAddr", QVariant(count));
        //sqlquery.exec();
    }
}

void QTrendDataGroupAttr::save(QDataStream &stream)//��item����������
{
    QVisableItem::save(stream);

    //�������
    stream << m_bIsAll;             //����ȫ��
    stream << m_sCurChnnel;      //��ǰ����
    stream << m_sChnnelBegin;       //��ʼ���
    stream << m_nTotalTrendNumber;  //����������
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


    //��ʾ��
    stream << m_bSelectVertMinor;   //�Ƿ���ʾ��ֱ�α��
    stream << m_bSelectHorMinor;    //�Ƿ���ʾˮƽ�α��
    stream << m_bMainVer;
    stream << m_bMainHor;


    stream << m_nDataSample;        //����������
    stream << m_nVertMajorScale;    //��ֱ�����
    stream << m_nVertMinorScale;    //��ֱ�α��
    stream << m_nHorMajorScale;     //ˮƽ�α��
    stream << m_nHorMinorScale;     //ˮƽ�����

    //��ɫ
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

void QTrendDataGroupAttr::load(QDataStream &stream)//������������item
{
    int temp;
    QVisableItem::load(stream);

    //�������
    stream >> m_bIsAll;             //����ȫ��
    stream >> m_sCurChnnel;      //��ǰ����
    stream >> m_sChnnelBegin;       //��ʼ����
    stream >> m_nTotalTrendNumber;  //����������
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
    //stream >> m_bMainHor;
    //stream >> m_bMainVer;
    stream >> m_nDataSample;
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
    stream >> m_nFontSize;
    if(pwnd->getProVersion() >= 2527)//�ɰ汾
    {
        QString str;
        stream >> m_nMarkedColor;
    }

    if(pwnd->getProVersion() >= 2667)//�°汾
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
            addrPro.str   = QObject::tr("ͨ��")+m_vecChannelGroups[i].m_sGroupName+QObject::tr("���Ƶ�ַ");
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
    return QObject::tr("����Ⱥ��");
}
//���ݲ�����һ�����ݱ��ı䡣ˢ�¿ؼ�
void QTrendDataGroupAttr::sampChanged(QString oldName,QString newName,int sampType)
{
	if (m_selGroups.contains(oldName))
	{
		if (newName.isEmpty() || sampType == 2)//ɾ���˸������� ���߸ı�Ϊ��ʷ����
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
		else//�޸���������
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
