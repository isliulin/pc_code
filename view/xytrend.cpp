#include "xytrend.h"

extern MainWindow *pwnd;

XYtrend::XYtrend(QGraphicsItem *parent):QVisableItem(parent)//QItemGroup(parent)//
{

}

XYtrend::~XYtrend()
{

}

int XYtrend::GroupType()//�ؼ����� ����ͼ
{
    //return GROUP_TYPE_TRENDCHART;
    return SAM_DRAW_GROUP_XYTREND;
}

XYtrend* XYtrend::Clone()//����item
{
    QGraphicsItem* pCopy = NULL;
    QGraphicsItem* pItem = NULL;

    XYtrend *itemGroup = new XYtrend;

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
    itemGroup->m_bIsAll        = m_bIsAll;
    itemGroup->chlCount        = chlCount;//ͨ������
    itemGroup->addrLength      = addrLength;//��ַ���ȣ��൱�ڲ�������
    itemGroup->m_dataType      = m_dataType;//��������
    itemGroup->m_TriggerAddr   = m_TriggerAddr;//������ַ
    itemGroup->m_bReset        = m_bReset;//�Ƿ��Զ���λ

    itemGroup->m_bScale        = m_bScale;//�Ƿ�����

    itemGroup->m_bDisplayConst  = m_bDisplayConst;
    itemGroup->m_DisplayMaxAddrX= m_DisplayMaxAddrX;
    itemGroup->m_DisplayMinAddrX= m_DisplayMinAddrX;

    itemGroup->m_nDisplayMinX   = m_nDisplayMinX;	//��ʾ��Сֵ
    itemGroup->m_nDisplayMaxX   = m_nDisplayMaxX;	//��ʾ���ֵ
    itemGroup->m_bConstX        = m_bConstX;//�Ƿ�����Χ
    itemGroup->m_SourceMaxAddrX = m_SourceMaxAddrX;//Դ��Χ���ֵ ��ַ
    itemGroup->m_SourceMinAddrX = m_SourceMinAddrX;//Դ��Χ��Сֵ ��ַ
    itemGroup->m_nSourceMaxX    = m_nSourceMaxX;	//Դ��Χ���ֵ
    itemGroup->m_nSourceMinX    = m_nSourceMinX;	//Դ��Χ��Сֵ

    itemGroup->m_bDisplayConstY  = m_bDisplayConstY;
    itemGroup->m_DisplayMaxAddrY= m_DisplayMaxAddrY;
    itemGroup->m_DisplayMinAddrY= m_DisplayMinAddrY;
    itemGroup->m_nDisplayMinY   = m_nDisplayMinY;	//��ʾ��Сֵ
    itemGroup->m_nDisplayMaxY   = m_nDisplayMaxY;	//��ʾ���ֵ
    itemGroup->m_bConstY        = m_bConstY;//�Ƿ�����Χ
    itemGroup->m_SourceMaxAddrY = m_SourceMaxAddrY;//Դ��Χ���ֵ ��ַ
    itemGroup->m_SourceMinAddrY = m_SourceMinAddrY;//Դ��Χ��Сֵ ��ַ
    itemGroup->m_nSourceMaxY    = m_nSourceMaxY;	//Դ��Χ���ֵ
    itemGroup->m_nSourceMinY    = m_nSourceMinY;	//Դ��Χ��Сֵ

    itemGroup->m_vecChannels   = m_vecChannels;//����ͨ�������������

    //������ʾ������
    itemGroup->m_bSelectVertMinor  = m_bSelectVertMinor;  //�Ƿ���ʾ��ֱ�α��
    itemGroup->m_bSelectHorMinor   = m_bSelectHorMinor;   //�Ƿ���ʾˮƽ�α��
    itemGroup->m_bMainHor          = m_bMainHor;
    itemGroup->m_bMainVer          = m_bMainVer;
    itemGroup->m_TextColor         = m_TextColor;
    itemGroup->m_textSize          = m_textSize;
    itemGroup->m_nVertMajorScale   = m_nVertMajorScale;   //��ֱ�����
    itemGroup->m_nVertMinorScale   = m_nVertMinorScale;   //��ֱ�α��
    itemGroup->m_nHorMajorScale    = m_nHorMajorScale;    //ˮƽ�����
    itemGroup->m_nHorMinorScale    = m_nHorMinorScale;    //ˮƽ�α��

    //������ɫ����
    itemGroup->m_bGrade      = m_bGrade;       //�Ƿ���Ҫ����
    itemGroup->m_nVerColor   = m_nVerColor;    //��ֱ������ɫ
    itemGroup->m_nHorColor   = m_nHorColor;    //ˮƽ������ɫ
    itemGroup->m_nBoradColor = m_nBoradColor;	//�߿���ɫ
    itemGroup->m_nScaleColor = m_nScaleColor;	//�����ɫ
    itemGroup->m_nGraphColor = m_nGraphColor;	//ͼ������ɫ
    itemGroup->m_alpha       = m_alpha;	//ͼ����͸����


    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }

    itemGroup->SaveSecurityPro(&sPro);

    itemGroup->setId(id());


    return itemGroup;
}

void XYtrend::compile(QSqlDatabase &db, int nSceneId, int &count, int index)//�����ʱ�򱣴�item�����ݿ�
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
    bool r = sqlquery.prepare("INSERT INTO xytrends(nItemId ,nSceneId ,nTopLeftX ,nTopLeftY ,"
                          "nWidth ,nHeight ,nCurveX ,nCurveY ,nCurveWd ,nCurveHt ,"
                          "nAddrLength ,nChannelNum , nTrigAddr ,bAutoReset ,eDataType ,bDisplayConst,"
                          "nDisplayMaxX ,nDisplayMinX ,bDisplayConstY, nDisplayMaxY ,nDisplayMinY ,bScale,"
                          " eNumberTypeX ,nSourceMaxX ,nSourceMinX , eNumberTypeY ,nSourceMaxY,"
                          "nSourceMinY,bMainVer,nVertMajorScale,bSelectVertMinor,"
                          "nVertMinorScale,bMainHor,nHorMajorScale,bSelectHorMinor,"
                          "nHorMinorScale,bSelectNet,nVertNetColor,nHorNetColor,nBoradColor,"
                          "nScaleColor,nGraphColor,nFontSize,nMarkColor,nZvalue,nCollidindId)"

            "VALUES(:nItemId ,:nSceneId ,:nTopLeftX ,:nTopLeftY ,"
                ":nWidth ,:nHeight ,:nCurveX ,:nCurveY ,:nCurveWd ,:nCurveHt ,"
                ":nAddrLength ,:nChannelNum ,:nTrigAddr ,:bAutoReset ,:eDataType ,:bDisplayConst,"
                ":nDisplayMaxX ,:nDisplayMinX ,:bDisplayConstY,:nDisplayMaxY ,:nDisplayMinY ,:bScale,"
                ":eNumberTypeX ,:nSourceMaxX ,:nSourceMinX ,:eNumberTypeY ,:nSourceMaxY,"
                ":nSourceMinY,:bMainVer,:nVertMajorScale,:bSelectVertMinor,"
                ":nVertMinorScale,:bMainHor,:nHorMajorScale,:bSelectHorMinor,"
                ":nHorMinorScale,:bSelectNet,:nVertNetColor,:nHorNetColor,:nBoradColor,"
                ":nScaleColor,:nGraphColor,:nFontSize,:nMarkColor,:nZvalue,:nCollidindId)");

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


    sqlquery.bindValue(":nAddrLength", QVariant(addrLength));     //����
    sqlquery.bindValue(":nChannelNum", QVariant(chlCount));     //ͨ����
    count++;
    ADDR_PARAMENTS stParams;
    stParams.id         = count;
    stParams.itemId     = itemId;
    stParams.eType      = OBJ_ITEM;
    stParams.eRWtype    = SCENE_CONTROL_LOOP_R;
    stParams.addrNum    = -1;
    m_TriggerAddr.compile(db,stParams);
    sqlquery.bindValue(":nTrigAddr", QVariant(count));     //������ַ
    sqlquery.bindValue(":bAutoReset", QVariant(m_bReset));     //�Ƿ��Զ���λ
    short datatype = m_dataType + 2 ;
    sqlquery.bindValue(":eDataType", QVariant(datatype));     //��������

    sqlquery.bindValue(":bDisplayConst", QVariant(m_bDisplayConst+1));     //�Ƿ�Ϊ����
    if(!m_bDisplayConst)//����
    {
        count++;
        stParams.id         = count;
        m_DisplayMaxAddrX.compile(db,stParams);
        sqlquery.bindValue(":nDisplayMaxX", QVariant(count));
        count++;
        stParams.id         = count;
        m_DisplayMinAddrX.compile(db,stParams);
        sqlquery.bindValue(":nDisplayMinX", QVariant(count));
    }
    else//��ַ
    {
        sqlquery.bindValue(":nDisplayMaxX", QVariant(m_nDisplayMaxX));
        sqlquery.bindValue(":nDisplayMinX", QVariant(m_nDisplayMinX));
    }
    sqlquery.bindValue(":bDisplayConstY", QVariant(m_bDisplayConstY+1));     //�Ƿ�Ϊ����
    if(!m_bDisplayConstY)//����
    {
        count++;
        stParams.id         = count;
        m_DisplayMaxAddrY.compile(db,stParams);
        sqlquery.bindValue(":nDisplayMaxY", QVariant(count));
        count++;
        stParams.id         = count;
        m_DisplayMinAddrY.compile(db,stParams);
        sqlquery.bindValue(":nDisplayMinY", QVariant(count));
    }
    else//��ַ
    {
        sqlquery.bindValue(":nDisplayMaxY", QVariant(m_nDisplayMaxY));
        sqlquery.bindValue(":nDisplayMinY", QVariant(m_nDisplayMinY));
    }

    sqlquery.bindValue(":bScale", QVariant(m_bScale));     //�Ƿ�����
    if(m_bScale)//����
    {
        sqlquery.bindValue(":eNumberTypeX", QVariant(m_bConstX+1));     //�Ƿ�Ϊ����
        if(!m_bConstX)//����
        {
            qDebug() << "m_bConstX:"<< m_bConstX;
            count++;
            stParams.id         = count;
            m_SourceMaxAddrX.compile(db,stParams);
            sqlquery.bindValue(":nSourceMaxX", QVariant(count));
            count++;
            stParams.id         = count;
            m_SourceMinAddrX.compile(db,stParams);
            sqlquery.bindValue(":nSourceMinX", QVariant(count));
        }
        else//��ַ
        {
            sqlquery.bindValue(":nSourceMaxX", QVariant(m_nSourceMaxX));
            sqlquery.bindValue(":nSourceMinX", QVariant(m_nSourceMinX));
        }
        sqlquery.bindValue(":eNumberTypeY", QVariant(m_bConstY+1));     //�Ƿ�Ϊ����
        if(!m_bConstY)//����
        {
            qDebug() << "m_bConstY:"<< m_bConstY;
            count++;
            stParams.id         = count;
            m_SourceMaxAddrY.compile(db,stParams);
            sqlquery.bindValue(":nSourceMaxY", QVariant(count));
            count++;
            stParams.id         = count;
            m_SourceMinAddrY.compile(db,stParams);
            sqlquery.bindValue(":nSourceMinY", QVariant(count));
        }
        else//��ַ
        {
            sqlquery.bindValue(":nSourceMaxY", QVariant(m_nSourceMaxY));
            sqlquery.bindValue(":nSourceMinY", QVariant(m_nSourceMinY));
        }
    }
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

    sqlquery.bindValue(":nFontSize", QVariant(m_textSize));    //�����С
    sqlquery.bindValue(":nMarkColor", QVariant(ColorToInt(m_TextColor)));//��ע��ɫ

    sqlquery.bindValue(":nZvalue", QVariant(zValue()));      //Z��
    sqlquery.bindValue(":nCollidindId", QVariant(index));      //index

    bool result = false;
    result = sqlquery.exec();
    qDebug() << "--insert trends table :" << result;
    //sqlquery.exec();
    bool re = sqlquery.prepare("INSERT INTO trendsChannelSet(nItemId,nStartAddrX ,nStartAddrY ,nNumOfChannel,"
                 "nDisplayCondition,nDisplayAddr,nLineType,nLineThickness,nDisplayColor)"
                 "VALUES(:nItemId,:nStartAddrX ,:nStartAddrY ,:nNumOfChannel,"
                 ":nDisplayCondition,:nDisplayAddr,:nLineType,:nLineThickness,:nDisplayColor)");
    qDebug() << "sqlquery.prepare" << re;

    ChannelInfo info;

    for(int i = 0; i < m_vecChannels.size(); i++)
    {
        info = m_vecChannels.at(i);

        sqlquery.bindValue(":nItemId", QVariant(itemId));             //��id
        count++;
        stParams.id         = count;
        stParams.addrNum    = i;
        info.m_AddrX.compile(db,stParams);
        sqlquery.bindValue(":nStartAddrX", QVariant(count));
        count++;
        stParams.id         = count;
        info.m_AddrY.compile(db,stParams);
        sqlquery.bindValue(":nStartAddrY", QVariant(count));
        sqlquery.bindValue(":nNumOfChannel", QVariant(info.m_nNumOfChannel));      //ͨ����

        sqlquery.bindValue(":nDisplayCondition", QVariant(info.eDisplayCondition));      //��ʾ����

        count++;
        stParams.id         = count;
        info.KeyAddr.compile(db,stParams);
        sqlquery.bindValue(":nDisplayAddr", QVariant(count));//��ʾON/OFF��ַ

        sqlquery.bindValue(":nLineType", QVariant(info.eLineType));      //����
        sqlquery.bindValue(":nLineThickness", QVariant(info.nLineThickness));      //�������
        ck = ColorToInt(info.nDisplayColor);
        sqlquery.bindValue(":nDisplayColor", QVariant(ck));      //��ʾ��ɫ

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "-------------insert nDisplayColor table :" << result << endl;
    }


}

void XYtrend::save(QDataStream &stream)//��item����������
{
    QVisableItem::save(stream);
    //QItemGroup::save(stream);

    stream <<  m_bIsAll;
    stream <<  chlCount;//ͨ������
    stream <<  addrLength;//��ַ���ȣ��൱�ڲ�������
    stream <<  (int)m_dataType;//��������
    stream <<  m_TriggerAddr;//������ַ
    stream <<  m_bReset;//�Ƿ��Զ���λ

    stream <<  m_bScale;//�Ƿ�����

    stream <<  m_bDisplayConst;
    stream <<  m_DisplayMaxAddrX;
    stream <<  m_DisplayMinAddrX;
    stream <<  m_nDisplayMinX;	//��ʾ��Сֵ
    stream <<  m_nDisplayMaxX;	//��ʾ���ֵ
    stream <<  m_bConstX;//�Ƿ�����Χ
    stream <<  m_SourceMaxAddrX;//Դ��Χ���ֵ ��ַ
    stream <<  m_SourceMinAddrX;//Դ��Χ��Сֵ ��ַ
    stream <<  m_nSourceMaxX;	//Դ��Χ���ֵ
    stream <<  m_nSourceMinX;	//Դ��Χ��Сֵ

    stream <<  m_bDisplayConstY;
    stream <<  m_DisplayMaxAddrY;
    stream <<  m_DisplayMinAddrY;
    stream <<  m_nDisplayMinY;	//��ʾ��Сֵ
    stream <<  m_nDisplayMaxY;	//��ʾ���ֵ
    stream <<  m_bConstY;//�Ƿ�����Χ
    stream <<  m_SourceMaxAddrY;//Դ��Χ���ֵ ��ַ
    stream <<  m_SourceMinAddrY;//Դ��Χ��Сֵ ��ַ
    stream <<  m_nSourceMaxY;	//Դ��Χ���ֵ
    stream <<  m_nSourceMinY;	//Դ��Χ��Сֵ

    for(int i=0; i<chlCount; i++)
    {
        Keyboard kb = m_vecChannels.at(i).m_AddrX;
        stream << kb;
        kb = m_vecChannels.at(i).m_AddrY;
        stream << kb;

        stream << m_vecChannels.at(i).nLineThickness;
        stream << m_vecChannels.at(i).nDisplayColor;
        stream << (int)m_vecChannels.at(i).eLineType;
        stream << (int)m_vecChannels.at(i).eDisplayCondition;
        kb = m_vecChannels.at(i).KeyAddr;
        stream << kb;
    }

    //������ʾ������
    stream <<  m_bSelectVertMinor;  //�Ƿ���ʾ��ֱ�α��
    stream <<  m_bSelectHorMinor;   //�Ƿ���ʾˮƽ�α��
    stream <<  m_bMainHor;
    stream <<  m_bMainVer;
    stream <<  m_TextColor;
    stream <<  m_textSize;
    stream <<  m_nVertMajorScale;   //��ֱ�����
    stream <<  m_nVertMinorScale;   //��ֱ�α��
    stream <<  m_nHorMajorScale;    //ˮƽ�����
    stream <<  m_nHorMinorScale;    //ˮƽ�α��

    //������ɫ����
    stream <<  m_bGrade;       //�Ƿ���Ҫ����
    stream <<  m_nVerColor;    //��ֱ������ɫ
    stream <<  m_nHorColor;    //ˮƽ������ɫ
    stream <<  m_nBoradColor;	//�߿���ɫ
    stream <<  m_nScaleColor;	//�����ɫ
    stream <<  m_nGraphColor;	//ͼ������ɫ
    stream <<  m_alpha;	//ͼ����͸����


}

void XYtrend::load(QDataStream &stream)//������������item
{
    int temp;
    QVisableItem::load(stream);
    //QItemGroup::load(stream);

    stream >>  m_bIsAll;
    stream >>  chlCount;//ͨ������
    stream >>  addrLength;//��ַ���ȣ��൱�ڲ�������
    stream >>  temp;
    m_dataType = (DATA_TYPE)temp;//��������
    stream >>  m_TriggerAddr;//������ַ
    stream >>  m_bReset;//�Ƿ��Զ���λ

    stream >>  m_bScale;//�Ƿ�����

    stream >>  m_bDisplayConst;
    stream >>  m_DisplayMaxAddrX;
    stream >>  m_DisplayMinAddrX;
    stream >>  m_nDisplayMinX;	//��ʾ��Сֵ
    stream >>  m_nDisplayMaxX;	//��ʾ���ֵ
    stream >>  m_bConstX;//�Ƿ�����Χ
    stream >>  m_SourceMaxAddrX;//Դ��Χ���ֵ ��ַ
    stream >>  m_SourceMinAddrX;//Դ��Χ��Сֵ ��ַ
    stream >>  m_nSourceMaxX;	//Դ��Χ���ֵ
    stream >>  m_nSourceMinX;	//Դ��Χ��Сֵ

    stream >>  m_bDisplayConstY;
    stream >>  m_DisplayMaxAddrY;
    stream >>  m_DisplayMinAddrY;
    stream >>  m_nDisplayMinY;	//��ʾ��Сֵ
    stream >>  m_nDisplayMaxY;	//��ʾ���ֵ
    stream >>  m_bConstY;//�Ƿ�����Χ
    stream >>  m_SourceMaxAddrY;//Դ��Χ���ֵ ��ַ
    stream >>  m_SourceMinAddrY;//Դ��Χ��Сֵ ��ַ
    stream >>  m_nSourceMaxY;	//Դ��Χ���ֵ
    stream >>  m_nSourceMinY;	//Դ��Χ��Сֵ

    ChannelInfo chl;
    for(int i=0; i<chlCount; i++)
    {
        stream >> chl.m_AddrX;

        stream >> chl.m_AddrY;

        stream >> chl.nLineThickness;
        stream >> chl.nDisplayColor;
        stream >> temp;
        chl.eLineType = (LineStyleType)temp;
        stream >> temp;
        chl.eDisplayCondition = (DisConType)temp;
        stream >> chl.KeyAddr;
        chl.m_nNumOfChannel = i;
        m_vecChannels.push_back(chl);

    }

    //������ʾ������
    stream >>  m_bSelectVertMinor;  //�Ƿ���ʾ��ֱ�α��
    stream >>  m_bSelectHorMinor;   //�Ƿ���ʾˮƽ�α��
    stream >>  m_bMainHor;
    stream >>  m_bMainVer;
    stream >>  m_TextColor;
    stream >>  m_textSize;
    stream >>  m_nVertMajorScale;   //��ֱ�����
    stream >>  m_nVertMinorScale;   //��ֱ�α��
    stream >>  m_nHorMajorScale;    //ˮƽ�����
    stream >>  m_nHorMinorScale;    //ˮƽ�α��

    //������ɫ����
    stream >>  m_bGrade;       //�Ƿ���Ҫ����
    stream >>  m_nVerColor;    //��ֱ������ɫ
    stream >>  m_nHorColor;    //ˮƽ������ɫ
    stream >>  m_nBoradColor;	//�߿���ɫ
    stream >>  m_nScaleColor;	//�����ɫ
    stream >>  m_nGraphColor;	//ͼ������ɫ
    stream >>  m_alpha;	//ͼ����͸����



}

QVector<ADDRPRO> XYtrend::getAllItemAddr()
{
    kb.clear();
    kb = QVisableItem::getAllItemAddr();

    ADDRPRO addrPro;

    addrPro.pAddr = &m_TriggerAddr;
    addrPro.str   = QObject::tr("X-Y����ˢ�´�����ַ");
    addrPro.type  = 0;
    kb << addrPro;

    if(m_bScale)//����
    {
        if(!m_bConstX)
        {
            addrPro.pAddr = &m_SourceMaxAddrX;
            addrPro.str   = QObject::tr("X��Դ��Χ���ֵ��ַ");
            addrPro.type  = 1;
            kb << addrPro;
            addrPro.pAddr = &m_SourceMinAddrX;
            addrPro.str   = QObject::tr("X��Դ��Χ��Сֵ��ַ");
            kb << addrPro;
        }
        if(!m_bConstY)
        {
            addrPro.pAddr = &m_SourceMaxAddrY;
            addrPro.str   = QObject::tr("Y��Դ��Χ���ֵ��ַ");
            addrPro.type  = 1;
            kb << addrPro;
            addrPro.pAddr = &m_SourceMinAddrY;
            addrPro.str   = QObject::tr("Y��Դ��Χ��Сֵ��ַ");
            kb << addrPro;
        }

    }

    for (int i=0; i<m_vecChannels.size(); i++)
    {
        ADDRPRO addrPro;
        QString str;
        if (m_vecChannels[i].eDisplayCondition != DisplayKeep && !m_bIsAll)
        {
            addrPro.pAddr = &m_vecChannels[i].KeyAddr;
            addrPro.str   = QObject::tr("ͨ��")+QString::number(m_vecChannels[i].m_nNumOfChannel)+QObject::tr("���Ƶ�ַ");
            addrPro.type  = 0;
            kb << addrPro;
        }
        addrPro.pAddr = &m_vecChannels[i].m_AddrX;
        addrPro.str   = QObject::tr("ͨ��")+QString::number(m_vecChannels[i].m_nNumOfChannel)+QObject::tr("X����ʼ��ַ");
        addrPro.type  = 1;
        kb << addrPro;
        addrPro.pAddr = &m_vecChannels[i].m_AddrY;
        addrPro.str   = QObject::tr("ͨ��")+QString::number(m_vecChannels[i].m_nNumOfChannel)+QObject::tr("Y����ʼ��ַ");
        kb << addrPro;
    }
    return kb;
}

QString  XYtrend::getItemName()
{
    return QObject::tr("X-Y����");
}


