/*********************************************************************************/
//filename  DataDisPlayItem.cpp
/*********************************************************************************/
#include "DataDisplayItem.h"
#include "Frame/mainwindow.h"
#include "Macro/macro.h"

extern MainWindow *pwnd;
DataDisplayItem::DataDisplayItem()
    :QVisableItem(0)
{
    m_ascii.bOffset = false;
    m_data.bOffset = false;
}

QGraphicsItem *DataDisplayItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    DataDisplayItem *itemGroup = new DataDisplayItem();

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
            pCopy->setFlag(QGraphicsItem::ItemIsSelectable,false);

    }

    itemGroup->m_data = m_data;
    itemGroup->m_ascii = m_ascii;
    itemGroup->m_time = m_time;
    itemGroup->textItem = itemGroup->GetTextItem();
    itemGroup->backItem = itemGroup->GetBackItem();
    itemGroup->m_etabPag = m_etabPag;
    itemGroup->m_eIspic = m_eIspic;
    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    itemGroup->setData(GROUP_TYPE_KEY,data(GROUP_TYPE_KEY).toString());
    itemGroup->SaveSecurityPro(&sPro);
    itemGroup->setId(id());
    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }
    return itemGroup;
}

void DataDisplayItem::compile(QSqlDatabase &db,int nSceneId,int &count,int index)
{
    int nTextAligent = GetTextAlign();
    int naddrID;
    int naddrMinID;
    int naddrMaxID;//��¼Դ���ֵ��ID��
    int naddrShowMinID;//��ʾ��Χ��С��ַ��ID
    int naddrShowMaxID;
    int naddrBit;//λ�����ַ
    int nDecimalID;//С��λ����ַ
    int nInputMaxID;//��Χ���͵�ַ
    int nInputAddrID;//��ص�ַ����ͬ
    int nOffsetID = -1;
    int nInputMinID;
    int nAddrLength = 1;

    count++;
    QVisableItem::compile(db,nSceneId,count, index);
    int nItemId = count;

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

    onGetPosition();

    QMap<QString,QVariant> mapQuery;
    //QSqlQuery sqlquery(db);
    QColor mColor;
    if(DATAINPUTSHOW == m_etabPag)
    {
        count++;
        naddrID = count;
		//�޸ĵ�ַ�������
        ADDR_PARAMENTS stParams;
        stParams.id = count;
        stParams.itemId = nItemId;
        stParams.eType = OBJ_ITEM;
        stParams.addrNum = -1;
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
        if(m_data.eNumberType >= 0 && m_data.eNumberType <= 4)
        {
            nAddrLength = 1;
        }
        else
        {
            nAddrLength = 2;
        }
        m_data.addr.Length = nAddrLength;
        m_data.addr.compile(db,stParams);

        if(1 == m_data.nByteLength)
        {
            count++;
            naddrMinID = count;
			//�޸ĵ�ַ�������
            stParams.id = count;
            m_data.addrSourceMin.Length = nAddrLength;
            m_data.addrSourceMin.compile(db,stParams);//Դ��Сֵ��ַ��
            count++;
            naddrMaxID = count;
            stParams.id = count;
			//�޸ĵ�ַ�������
            m_data.addrSourceMax.Length = nAddrLength;
            m_data.addrSourceMax.compile(db,stParams);

        }
        if(1 == m_data.sShow)
        {
            count++;
            naddrShowMinID = count;
            stParams.id = count;
			//�޸ĵ�ַ�������
            m_data.addrShowMin.Length = nAddrLength;
            m_data.addrShowMin.compile(db,stParams);
            count++;
            naddrShowMaxID = count;
            stParams.id = count;
			//�޸ĵ�ַ�������
            m_data.addrShowMax.Length = nAddrLength;
            m_data.addrShowMax.compile(db,stParams);
        }
        if(m_data.bIsInput &&(Bit == m_data.eInputTypeId))
        {
            count++;
            naddrBit = count;
            stParams.id = count;
			//�޸ĵ�ַ�������
            m_data.addrBit.Length = 1;
            m_data.addrBit.compile(db,stParams);
        }
        if(1 == m_data.sDecimalType)
        {
            count++;
            nDecimalID = count;
            stParams.id = count;
			//�޸ĵ�ַ�������
            m_data.addrDicmal.Length = 1;
            m_data.addrDicmal.compile(db,stParams);
        }
        if(m_data.bIsInput)//��������
        {
            if(1 == m_data.eInputAreaType)
            {
                count++;
                nInputMaxID = count;
                stParams.id = count;
                            //�޸ĵ�ַ�������
                m_data.addrInputMax.Length = nAddrLength;
                m_data.addrInputMax.compile(db,stParams);

                count++;
                nInputMinID = count;
                stParams.id = count;
                            //�޸ĵ�ַ�������
                m_data.addrInputMin.Length = nAddrLength;
                m_data.addrInputMin.compile(db,stParams);
            }
        }
        if(m_data.bOffset)
        {
            count++;
            nOffsetID = count;
            stParams.id = count;
                        //�޸ĵ�ַ�������
            m_data.addrOffset.Length = 1;
            m_data.addrOffset.compile(db,stParams);
        }
        if(!m_data.bInputIsShow && m_data.bIsInput)
        {
            count++;
            nInputAddrID = count;
            stParams.id = count;
            m_data.addrInputSame.Length = 1;
            m_data.addrInputSame.compile(db,stParams);
        }
        else
        {
            nInputAddrID = -1;
        }

        //QSqlQuery sqldataquery(db);
//        bool shit = false;
//        shit = sqldataquery.prepare("INSERT INTO number(nItemId, nAddress, bIsInput, bIsScale, eNumberType,"
//                             "nByteLength, eSourceArea, nSourceMax, nSourceMin, nShow,"
//                             "bRound, nShowMax, nShowMin, nAllbytelength,"
//                             "eDecimalType, nDecimalLength, eShowStyle, nFontColor, nBackColor,"
//                             "nHightColor, nLowerColor, eInputTypeId, nKeyId, sBitAddress,bAutoChangeBit,"
//                             "eInputAreaType,nInputMax,nInputMin,bInputSign,nBoardX,nBoardY,nLowerNumber,"
//                             "nHightNumber,bInputIsShow,nInputAddr)"
//                             "VALUES(:nItemId,:nAddress,:bIsInput,:bIsScale,:eNumberType,"
//                             ":nByteLength,:eSourceArea,:nSourceMax,:nSourceMin,:nShow,"
//                             ":bRound,:nShowMax,:nShowMin,:nAllbytelength,"
//                             ":eDecimalType,:nDecimalLength,:eShowStyle,:nFontColor,:nBackColor,"
//                             ":nHightColor,:nLowerColor,:eInputTypeId,:nKeyId,:sBitAddress,:bAutoChangeBit,"
//                             ":eInputAreaType,:nInputMax,:nInputMin,:bInputSign,:nBoardX,:nBoardY,:nLowerNumber,"
//                             ":nHightNumber,:bInputIsShow,:nInputAddr)");

//        qDebug() << "+++++++++++++++shit++++++++++++\n";
//        qDebug() << shit;
        mapQuery.insert(":nItemId",QVariant(nItemId));
        mapQuery.insert(":nAddress",QVariant(naddrID));//��ַ��Ҫת��
        mapQuery.insert(":bIsInput",QVariant(m_data.bIsInput));
        mapQuery.insert(":bIsScale",QVariant(m_data.bIsScale));
        //��������ת���ɽṹ���ж�Ӧ����������
        int eDataType;
        double dSourceMax = 0;
        double dSourceMin = 0;
        double dShowMax = 0;
        double dShowMin = 0;
        double dLimitMax = 0;
        double dLimitMin = 0;
        double dHightMax = 0;
        double dLowMin = 0;
        const int base = 10;
        if(0 == m_data.eNumberType)//16λ����
        {
            eDataType = 2;

            dLowMin = m_data.nLowerNumber.toDouble();
            dHightMax = m_data.nHightNumber.toDouble();

            if(0 == m_data.nByteLength)
            {
                dSourceMax = m_data.sSourceMax.toDouble();
                dSourceMin = m_data.sSourceMin.toDouble();
            }

            if(0 == m_data.sShow)
            {
                dShowMax = m_data.sShowMax.toDouble();
                dShowMin = m_data.sShowMin.toDouble();
            }

            if(m_data.bIsInput && 0 == m_data.eInputAreaType)//��������
            {
                dLimitMax = m_data.sInputMax.toDouble();
                dLimitMin = m_data.sInputMin.toDouble();
            }
        }
        else if(1 == m_data.eNumberType)//16λ������
        {
            eDataType = 4;

            dLowMin = m_data.nLowerNumber.toDouble();
            dHightMax = m_data.nHightNumber.toDouble();
            if(0 == m_data.nByteLength)
            {
                dSourceMax = m_data.sSourceMax.toDouble();
                dSourceMin = m_data.sSourceMin.toDouble();
            }

            if(0 == m_data.sShow)
            {
                dShowMax = m_data.sShowMax.toDouble();
                dShowMin = m_data.sShowMin.toDouble();
            }

            if(m_data.bIsInput && 0 == m_data.eInputAreaType)//��������
            {
                dLimitMax = m_data.sInputMax.toDouble();
                dLimitMin = m_data.sInputMin.toDouble();
            }
        }
        else if(2 == m_data.eNumberType)//16λBCD��
        {
            eDataType = 6;
            bool ok;
            dLowMin = m_data.nLowerNumber.toUInt(&ok,16);
            dHightMax = m_data.nHightNumber.toUInt(&ok,16);

            if(0 == m_data.nByteLength)
            {
                dSourceMax = m_data.sSourceMax.toUInt(&ok,16);
                dSourceMin = m_data.sSourceMin.toUInt(&ok,16);
            }

            if(0 == m_data.sShow)
            {
                dShowMax = m_data.sShowMax.toUInt(&ok,16);
                dShowMin = m_data.sShowMin.toUInt(&ok,16);
            }

            if(m_data.bIsInput && 0 == m_data.eInputAreaType)//��������
            {
                dLimitMax = m_data.sInputMax.toUInt(&ok,base);
                dLimitMin = m_data.sInputMin.toUInt(&ok,base);
            }
        }
        else if(3 == m_data.eNumberType)//16λ8������
        {
            eDataType = 12;
            bool ok;
            dLowMin = m_data.nLowerNumber.toUInt(&ok,8);
            dHightMax = m_data.nHightNumber.toUInt(&ok,8);
            if(0 == m_data.nByteLength)
            {
                dSourceMax = m_data.sSourceMax.toUInt(&ok,8);
                dSourceMin = m_data.sSourceMin.toUInt(&ok,8);
            }

            if(0 == m_data.sShow)
            {
                dShowMax = m_data.sShowMax.toUInt(&ok,8);
                dShowMin = m_data.sShowMin.toUInt(&ok,8);
            }

            if(m_data.bIsInput && 0 == m_data.eInputAreaType)//��������
            {
                dLimitMax = m_data.sInputMax.toUInt(&ok,base);
                dLimitMin = m_data.sInputMin.toUInt(&ok,base);
            }
        }
        else if(4 == m_data.eNumberType)//16λ16������
        {
            eDataType = 10;

            bool ok;
            dLowMin = m_data.nLowerNumber.toUInt(&ok,16);
            dHightMax = m_data.nHightNumber.toUInt(&ok,16);

            if(0 == m_data.nByteLength)
            {
                dSourceMax = m_data.sSourceMax.toUInt(&ok,16);
                dSourceMin = m_data.sSourceMin.toUInt(&ok,16);
            }

            if(0 == m_data.sShow)
            {
                dShowMax = m_data.sShowMax.toUInt(&ok,16);
                dShowMin = m_data.sShowMin.toUInt(&ok,16);
            }

            if(m_data.bIsInput && 0 == m_data.eInputAreaType)//��������
            {
                bool ok;
                dLimitMax = m_data.sInputMax.toUInt(&ok,16);
                dLimitMin = m_data.sInputMin.toUInt(&ok,16);
            }
        }
        else if(5 == m_data.eNumberType)//32λ����
        {
            eDataType = 3;

            dLowMin = m_data.nLowerNumber.toDouble();
            dHightMax = m_data.nHightNumber.toDouble();

            if(0 == m_data.nByteLength)
            {
                dSourceMax = m_data.sSourceMax.toDouble();
                dSourceMin = m_data.sSourceMin.toDouble();
            }

            if(0 == m_data.sShow)
            {
                dShowMax = m_data.sShowMax.toDouble();
                dShowMin = m_data.sShowMin.toDouble();
            }

            if(m_data.bIsInput && 0 == m_data.eInputAreaType)//��������
            {
                dLimitMax = m_data.sInputMax.toDouble();
                dLimitMin = m_data.sInputMin.toDouble();
            }
        }
        else if(6 == m_data.eNumberType)//32λ����
        {
            eDataType = 5;
            dLowMin = m_data.nLowerNumber.toDouble();
            dHightMax = m_data.nHightNumber.toDouble();

            if(0 == m_data.nByteLength)
            {
                dSourceMax = m_data.sSourceMax.toDouble();
                dSourceMin = m_data.sSourceMin.toDouble();
            }

            if(0 == m_data.sShow)
            {
                dShowMax = m_data.sShowMax.toDouble();
                dShowMin = m_data.sShowMin.toDouble();
            }

            if(m_data.bIsInput && 0 == m_data.eInputAreaType)//��������
            {
                dLimitMax = m_data.sInputMax.toDouble();
                dLimitMin = m_data.sInputMin.toDouble();
            }
        }
        else if(7 == m_data.eNumberType)//32λBCD
        {
            eDataType = 7;

            bool ok;
            dLowMin = m_data.nLowerNumber.toUInt(&ok,16);
            dHightMax = m_data.nHightNumber.toUInt(&ok,16);

            if(0 == m_data.nByteLength)
            {
                dSourceMax = m_data.sSourceMax.toUInt(&ok,16);
                dSourceMin = m_data.sSourceMin.toUInt(&ok,16);
            }

            if(0 == m_data.sShow)
            {
                dShowMax = m_data.sShowMax.toUInt(&ok,16);
                dShowMin = m_data.sShowMin.toUInt(&ok,16);
            }

            if(m_data.bIsInput && 0 == m_data.eInputAreaType)//��������
            {
                dLimitMax = m_data.sInputMax.toUInt(&ok,base);
                dLimitMin = m_data.sInputMin.toUInt(&ok,base);
            }
        }
        else if(8 == m_data.eNumberType)//32λ������
        {
            eDataType = 8;

            dLowMin = m_data.nLowerNumber.toDouble();
            dHightMax = m_data.nHightNumber.toDouble();

            if(0 == m_data.nByteLength)
            {
                dSourceMax = m_data.sSourceMax.toDouble();
                dSourceMin = m_data.sSourceMin.toDouble();
            }

            if(0 == m_data.sShow)
            {
                dShowMax = m_data.sShowMax.toDouble();
                dShowMin = m_data.sShowMin.toDouble();
            }

            if(m_data.bIsInput && 0 == m_data.eInputAreaType)//��������
            {
                dLimitMax = m_data.sInputMax.toDouble();
                dLimitMin = m_data.sInputMin.toDouble();
            }
        }
        else if(9 == m_data.eNumberType)//32λ8����
        {
            eDataType = 13;

            bool ok;
            dLowMin = m_data.nLowerNumber.toUInt(&ok,8);
            dHightMax = m_data.nHightNumber.toUInt(&ok,8);
            if(0 == m_data.nByteLength)
            {
                dSourceMax = m_data.sSourceMax.toUInt(&ok,8);
                dSourceMin = m_data.sSourceMin.toUInt(&ok,8);
            }

            if(0 == m_data.sShow)
            {
                dShowMax = m_data.sShowMax.toUInt(&ok,8);
                dShowMin = m_data.sShowMin.toUInt(&ok,8);
            }

            if(m_data.bIsInput && 0 == m_data.eInputAreaType)//��������
            {
                dLimitMax = m_data.sInputMax.toUInt(&ok,base);
                dLimitMin = m_data.sInputMin.toUInt(&ok,base);
            }
        }
        else if(10 == m_data.eNumberType)//32λ16����
        {
            eDataType = 11;

            bool ok;
            dLowMin = m_data.nLowerNumber.toUInt(&ok,16);
            dHightMax = m_data.nHightNumber.toUInt(&ok,16);

            if(0 == m_data.nByteLength)
            {
                dSourceMax = m_data.sSourceMax.toUInt(&ok,16);
                dSourceMin = m_data.sSourceMin.toUInt(&ok,16);
            }

            if(0 == m_data.sShow)
            {
                dShowMax = m_data.sShowMax.toUInt(&ok,16);
                dShowMin = m_data.sShowMin.toUInt(&ok,16);
            }

            if(m_data.bIsInput && 0 == m_data.eInputAreaType)//��������
            {
                dLimitMax = m_data.sInputMax.toUInt(&ok,16);
                dLimitMin = m_data.sInputMin.toUInt(&ok,16);
            }
        }
        mapQuery.insert(":eNumberType",QVariant(eDataType));
        int nByteLength = 32;
        if(0 <= m_data.eNumberType && m_data.eNumberType <= 4)
        {
            nByteLength = 16;
        }
        mapQuery.insert(":nByteLength",QVariant(nByteLength));
        mapQuery.insert(":eSourceArea",QVariant(m_data.nByteLength + 1));//Դ��Χ ��ַ ����
        if(0 == m_data.nByteLength)
        {
            mapQuery.insert(":nSourceMax",QVariant(dSourceMax));
            mapQuery.insert(":nSourceMin",QVariant(dSourceMin));
        }
        else
        {
            mapQuery.insert(":nSourceMax",QVariant(naddrMaxID));
            mapQuery.insert(":nSourceMin",QVariant(naddrMinID));
        }

        mapQuery.insert(":nShow",QVariant(m_data.sShow + 1));
        mapQuery.insert(":bRound",QVariant(m_data.bRound));
        if(0 == m_data.sShow)
        {
            mapQuery.insert(":nShowMax",QVariant(dShowMax));//��Ҫת��������ȷ��
            mapQuery.insert(":nShowMin",QVariant(dShowMin));
        }
        else
        {
            mapQuery.insert(":nShowMax",QVariant(naddrShowMaxID));//��Ҫת��������ȷ��
            mapQuery.insert(":nShowMin",QVariant(naddrShowMinID));
        }

        mapQuery.insert(":nAllbytelength",QVariant(m_data.nAllbytelength));
        mapQuery.insert(":eDecimalType",QVariant(m_data.sDecimalType + 1));
        if(0 == m_data.sDecimalType)
        {
           mapQuery.insert(":nDecimalLength",QVariant(m_data.sDecimalLength));
        }
        else
        {
            mapQuery.insert(":nDecimalLength",QVariant(nDecimalID));
        }
        if(4 == nTextAligent)
        {
            mapQuery.insert(":eShowStyle",QVariant(1));
        }
        else if(6 == nTextAligent)
        {
            mapQuery.insert(":eShowStyle",QVariant(3));
        }
        else
        {
            mapQuery.insert(":eShowStyle",QVariant(2));
        }

        mColor = pwnd->StringTOColor(m_data.nFontColor);
        mapQuery.insert(":nFontColor",QVariant(ColorToInt(mColor)));
        mColor = pwnd->StringTOColor(m_data.nBackColor);
        if(0 == GetPattern())
        {
            mapQuery.insert(":nBackColor",QVariant(0));
        }
        else
        {
            mapQuery.insert(":nBackColor",QVariant(ColorToInt(mColor)));
        }
        mColor = pwnd->StringTOColor(m_data.nHightColor);
        mapQuery.insert(":nHightColor",QVariant(ColorToInt(mColor)));
        mColor = pwnd->StringTOColor(m_data.nLowerColor);
        mapQuery.insert(":nLowerColor",QVariant(ColorToInt(mColor)));
        mapQuery.insert(":eInputTypeId",QVariant(m_data.eInputTypeId));
        if(m_data.nKeyMark)
        {
            mapQuery.insert(":nKeyId",QVariant(m_data.nKeyId +1));
        }
        else
        {
           mapQuery.insert(":nKeyId",QVariant(-1));
        }
        if(m_data.bIsInput &&(Bit == m_data.eInputTypeId))
        {
            mapQuery.insert(":sBitAddress",QVariant(naddrBit));
        }
        else
        {
            mapQuery.insert(":sBitAddress",QVariant(-1));
        }

        mapQuery.insert(":bAutoChangeBit",QVariant(m_data.bAutoChangeBit));
        if(m_data.bIsInput)//��������
        {
            mapQuery.insert(":eInputAreaType",QVariant(m_data.eInputAreaType + 1));
            if(1 == m_data.eInputAreaType)
            {
                mapQuery.insert(":nInputMax",QVariant(nInputMaxID));
                mapQuery.insert(":nInputMin",QVariant(nInputMinID));
            }
            else
            {
                mapQuery.insert(":nInputMax",QVariant(dLimitMax));
                mapQuery.insert(":nInputMin",QVariant(dLimitMin));
            }

            mapQuery.insert(":bInputSign",QVariant(m_data.bInputSign));

        }
        mapQuery.insert(":nBoardX",QVariant(m_data.nBoardX));
        mapQuery.insert(":nBoardY",QVariant(m_data.nBoardY));
        mapQuery.insert(":nLowerNumber",QVariant(dLowMin));
        mapQuery.insert(":nHightNumber",QVariant(dHightMax));
        mapQuery.insert(":bInputIsShow",QVariant(m_data.bInputIsShow));
        mapQuery.insert(":nInputAddr",QVariant(nInputAddrID));

        mapQuery.insert(":bShowExp",QVariant(m_data.bOutExpression));
        mapQuery.insert(":bInputExp",QVariant(m_data.bInExpression));
        if(m_data.bOutExpression)
        {
            count++;
            mapQuery.insert(":nShowExpId",QVariant(count));
            insertExpressTable(db,m_data.m_outputExp,count,nAddrLength,nItemId);
        }
        if(m_data.bInExpression)
        {
            count++;
            mapQuery.insert(":nInputExpId",QVariant(count));
            insertExpressTable(db,m_data.m_inputExp,count,nAddrLength,nItemId);
        }

        //if(!m_data.bInputIsShow)
        //{
        //    mapQuery.insert(":nInputAddr",QVariant(nInputAddrID));
        //}
        pwnd->inSertDbQuery("number",mapQuery);
//        bool ss = sqldataquery.exec();
//        qDebug() << "+++++++++++++++ssss++++++++++++\n";
//        qDebug() << ss;


        mapQuery.clear();
//        sqlquery.prepare("INSERT INTO dataShow(nItemId, nSceneId, eItemType, nStartX, nStartY, nWidth,"
//                          "nHeight, nTextStartX, nTextStartY, nTextWidth, nTextHeight,"
//                          "sShapId, nTransparent,sFontStyle, nFontSize, eFontCss, bIsStartStatement, nScriptId, nOffsetAddrID,nZvalue, nCollidindId, nShowPropId,"
//                          "nTouchPropId)"
//                          "VALUES (:nItemId, :nSceneId,:eItemType, :nStartX, :nStartY, :nWidth,"
//                          ":nHeight, :nTextStartX, :nTextStartY, :nTextWidth, :nTextHeight,"
//                          ":sShapId, :nTransparent, :sFontStyle, :nFontSize, :eFontCss, :bIsStartStatement, :nScriptId, :nOffsetAddrID,:nZvalue, :nCollidindId, :nShowPropId,"
//                          ":nTouchPropId)");

        mapQuery.insert(":nItemId",QVariant(nItemId));
        mapQuery.insert(":nSceneId",QVariant(nSceneId));
        mapQuery.insert(":eItemType",QVariant(m_etabPag + 1));
        mapQuery.insert(":nStartX",QVariant(m_data.nStartX));
        mapQuery.insert(":nStartY",QVariant(m_data.nStartY));
        mapQuery.insert(":nWidth",QVariant(m_data.nWidth));
        mapQuery.insert(":nHeight",QVariant(m_data.nHeight));
        mapQuery.insert(":nTextStartX",QVariant(m_data.nTextStartX));
        mapQuery.insert(":nTextStartY",QVariant(m_data.nTextStartY));
        mapQuery.insert(":nTextWidth",QVariant(m_data.nTextWidth));
        mapQuery.insert(":nTextHeight",QVariant(m_data.nTextHeight));

        QString newPath = "";
        if("" != m_data.nShapId)
        {
            bool bLib = false;
            if(LIBRARY == m_eIspic)
            {
                bLib = true;
            }
            newPath = pwnd->SavePath(m_data.nShapId,boundingRect().size(),bLib);
            if("" != newPath)
            {
                newPath = newPath.replace("\\","/");
                newPath = newPath.section("/",-1);
                newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
            }
        }
        mapQuery.insert(":sShapId",QVariant(newPath));//��ʱû��ͼ��
        mapQuery.insert(":nTransparent",QVariant(m_data.nTransparent));
        mapQuery.insert(":sFontStyle",QVariant(m_data.sFontType));//��������
        mapQuery.insert(":nFontSize",QVariant(m_data.nFontSize + 5));
        mapQuery.insert(":eFontCss",QVariant(m_data.eFontCss));
        mapQuery.insert(":bIsStartStatement",QVariant(m_data.bUseMacro));

        bool isExist = false;
        if(m_data.bUseMacro)
        {
            foreach(Macro lib,pwnd->macros)
            {
                if(lib.libName == m_data.macroName)
                {
                    isExist = true;
                }
            }

            if(!isExist)
            {
                pwnd->information(QObject::tr("��ֵ��ʾ��ʹ�õĺ�") + m_data.macroName +QObject::tr("����") + m_data.functionName + QObject::tr("��ɾ��"), MSG_WARNING);
                //QMessageBox::about(this, QObject::tr("����"), QObject::tr("������걻ɾ��"));
            }
        }
        if(m_data.bUseMacro && isExist)
        {
            count++;
            insertMacroTable(db,nItemId,count,nSceneId,m_data.macroName,m_data.functionName);
            mapQuery.insert(":nScriptId",QVariant(count));//��ָ�����
        }
        else
            mapQuery.insert(":nScriptId",QVariant(0));//��ָ�����

        mapQuery.insert(":nOffsetAddrID",QVariant(nOffsetID));//��ָ�����
        mapQuery.insert(":nShowPropId",QVariant(m_data.nShowPropId));
        mapQuery.insert(":nZvalue",QVariant(zValue()));
        mapQuery.insert(":nCollidindId",QVariant(index));
        mapQuery.insert(":nTouchPropId",QVariant(m_data.nTouchPropId));
        pwnd->inSertDbQuery("dataShow",mapQuery);
        //sqlquery.exec();

    }
    else if(ASCIIINPUTSHOW == m_etabPag)
    {
        count++;
        naddrID = count;
        ADDR_PARAMENTS stParams;
        stParams.id = count;
        stParams.itemId = nItemId;
        stParams.eType = OBJ_ITEM;
        stParams.addrNum = -1;
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
        if(m_ascii.nCode == 0x0002)//unicode ����
        {
            m_ascii.addr.Length = m_ascii.nShowCharNumber;
        }
        else
        {
            if(m_ascii.nShowCharNumber%2)
            {
                m_ascii.addr.Length = m_ascii.nShowCharNumber/2 + 1;
            }
            else
            {
                m_ascii.addr.Length = m_ascii.nShowCharNumber/2;
            }
        }
		//�޸ĵ�ַ�������
        m_ascii.addr.compile(db,stParams);

        if(m_ascii.bIsinput &&(Bit == m_ascii.eInputTypeId))//λ��ַ
        {
            count++;
            naddrBit = count;
            stParams.id = count;
            stParams.itemId = nItemId;
            stParams.eType = OBJ_ITEM;
            stParams.addrNum = -1;

            m_ascii.addrBit.compile(db,stParams);
        }

        if(m_ascii.bOffset)
        {
            count++;
            nOffsetID = count;
            stParams.id = count;
                        //�޸ĵ�ַ�������
            m_ascii.addrOffset.Length = 1;
            m_ascii.addrOffset.compile(db,stParams);
        }

        if(!m_ascii.bInputIsShow)
        {
            count++;
            nInputAddrID = count;
            stParams.id = count;
            m_ascii.addrInputSame.Length = m_ascii.addr.Length;
            m_ascii.addrInputSame.compile(db,stParams);
        }
        else
        {
            nInputAddrID = -1;
        }

        mapQuery.clear();
        //QSqlQuery sqlAsciiquery(db);
//        sqlAsciiquery.prepare("INSERT INTO ascii(nItemId, nAddress, bIsinput, nLanguageTypeId,"
//                              "nShowCharNumber, nShowStyle, nCode, nKeyId, nFontColor,"
//                              "eInputTypeId, bInputSign, nBoardX, nBoardY,sBitAddress,bAutoChangeBit,"
//                              "nBackColor,bInputIsShow,nInputAddr)"
//                              "VALUES (:nItemId, :nAddress, :bIsinput, :nLanguageTypeId,"
//                              ":nShowCharNumber, :nShowStyle, :nCode, :nKeyId, :nFontColor,"
//                              ":eInputTypeId,:bInputSign,:nBoardX,:nBoardY,:sBitAddress,:bAutoChangeBit,"
//                              ":nBackColor,:bInputIsShow,:nInputAddr)");

        mapQuery.insert(":nItemId",QVariant(nItemId));
        mapQuery.insert(":nAddress",QVariant(naddrID));//��Ҫת��
        mapQuery.insert(":bIsinput",QVariant(m_ascii.bIsinput));
        mapQuery.insert(":nLanguageTypeId",QVariant(m_ascii.nLanguageTypeId));
        mapQuery.insert(":nShowCharNumber",QVariant(m_ascii.nShowCharNumber));
        if(4 == nTextAligent)
        {
            mapQuery.insert(":nShowStyle",QVariant(1));
        }
        else if(6 == nTextAligent)
        {
            mapQuery.insert(":nShowStyle",QVariant(3));
        }
        else
        {
            mapQuery.insert(":nShowStyle",QVariant(2));
        }

        mapQuery.insert(":nCode",QVariant(m_ascii.nCode));
        if(m_ascii.nKeyMark)
        {
            mapQuery.insert(":nKeyId",QVariant(m_ascii.nKeyId + 1));
        }
        else
        {
            mapQuery.insert(":nKeyId",QVariant(-1));
        }
        mColor = pwnd->StringTOColor(m_ascii.nFontColor);
        mapQuery.insert(":nFontColor",QVariant(ColorToInt(mColor)));
        mColor = pwnd->StringTOColor(m_ascii.nBackColor);

        mapQuery.insert(":eInputTypeId",QVariant(m_ascii.eInputTypeId));
        if(m_ascii.bIsinput)//��������
        {
            mapQuery.insert(":bInputSign",QVariant(m_ascii.bInputSign));
        }
        mapQuery.insert(":nBoardX",QVariant(m_ascii.nBoardX));
        mapQuery.insert(":nBoardY",QVariant(m_ascii.nBoardY));

        if(m_ascii.bIsinput &&(Bit == m_ascii.eInputTypeId))
        {
            mapQuery.insert(":sBitAddress",QVariant(naddrBit));
        }
        else
        {
            mapQuery.insert(":sBitAddress",QVariant(-1));
        }

        mapQuery.insert(":bAutoChangeBit",QVariant(m_ascii.bAutoChangeBit));
        if(0 == GetPattern())
        {
            mapQuery.insert(":nBackColor",QVariant(0));
        }
        else
        {
            mapQuery.insert(":nBackColor",QVariant(ColorToInt(mColor)));
        }

        mapQuery.insert(":bInputIsShow",QVariant(m_ascii.bInputIsShow));
        mapQuery.insert(":nInputAddr",QVariant(nInputAddrID));
        //sqlAsciiquery.exec();
        pwnd->inSertDbQuery("ascii",mapQuery);

//        sqlquery.prepare("INSERT INTO dataShow(nItemId, nSceneId,eItemType, nStartX, nStartY, nWidth,"
//                          "nHeight, nTextStartX, nTextStartY, nTextWidth, nTextHeight,"
//                          "sShapId, nTransparent, sFontStyle, nFontSize, eFontCss, bIsStartStatement, nScriptId,nOffsetAddrID, nZvalue, nCollidindId, nShowPropId,"
//                          "nTouchPropId)"
//                          "VALUES (:nItemId, :nSceneId, :eItemType,:nStartX, :nStartY, :nWidth,"
//                          ":nHeight, :nTextStartX, :nTextStartY, :nTextWidth, :nTextHeight,"
//                          ":sShapId, :nTransparent, :sFontStyle, :nFontSize, :eFontCss, :bIsStartStatement, :nScriptId,:nOffsetAddrID, :nZvalue, :nCollidindId, :nShowPropId,"
//                          ":nTouchPropId)");

        mapQuery.clear();
        mapQuery.insert(":nItemId",QVariant(nItemId));
        mapQuery.insert(":nSceneId",QVariant(nSceneId));
        mapQuery.insert(":eItemType",QVariant(m_etabPag + 1));
        mapQuery.insert(":nStartX",QVariant(m_ascii.nStartX));
        mapQuery.insert(":nStartY",QVariant(m_ascii.nStartY));
        mapQuery.insert(":nWidth",QVariant(m_ascii.nWidth));
        mapQuery.insert(":nHeight",QVariant(m_ascii.nHeight));
        mapQuery.insert(":nTextStartX",QVariant(m_ascii.nTextStartX));
        mapQuery.insert(":nTextStartY",QVariant(m_ascii.nTextStartY));
        mapQuery.insert(":nTextWidth",QVariant(m_ascii.nTextWidth));
        mapQuery.insert(":nTextHeight",QVariant(m_ascii.nTextHeight));
        QString newPath = "";
        if("" != m_ascii.nShapId)
        {
            bool bLib = false;
            if(LIBRARY == m_eIspic)
            {
                bLib = true;
            }
            newPath = pwnd->SavePath(m_ascii.nShapId,boundingRect().size(),bLib);
            newPath = newPath.replace("\\","/");
            newPath = newPath.section("/",-1);
            newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
        }
        mapQuery.insert(":sShapId",QVariant(newPath));//��ʱû��ͼ��
        mapQuery.insert(":nTransparent",QVariant(m_ascii.nTransparent));
        mapQuery.insert(":sFontStyle",QVariant(m_ascii.sFontType));//��������~~~~~~~~~~
        mapQuery.insert(":nFontSize",QVariant(m_ascii.nFontsize + 5));
        mapQuery.insert(":eFontCss",QVariant(m_ascii.eFontCss));

        mapQuery.insert(":bIsStartStatement",QVariant(m_ascii.bUseMacro));

        bool isExist = false;
        if(m_ascii.bUseMacro)
        {
            foreach(Macro lib,pwnd->macros)
            //foreach(MacroLibrary lib,pwnd->librarys)
            {
                //if(lib.libName == m_ascii.macroName && lib.functions.contains(m_ascii.functionName))
                if(lib.libName == m_ascii.macroName)
                {
                    isExist = true;
                }
            }

            if(!isExist)
            {
                //pwnd->information(QObject::tr("ASCII��ʾ���걻ɾ��"));
                pwnd->information(QObject::tr("ASCII��ʾ��ʹ�õĺ�") + m_ascii.macroName +QObject::tr("����") + m_ascii.functionName + QObject::tr("��ɾ��"), MSG_WARNING);
                //QMessageBox::about(this, QObject::tr("����"), QObject::tr("������걻ɾ��"));
            }
        }

        if(m_ascii.bUseMacro && isExist)
        {
            count++;
            insertMacroTable(db,nItemId,count,nSceneId,m_ascii.macroName,m_ascii.functionName);
            mapQuery.insert(":nScriptId",QVariant(count));//��ָ�����
        }
        else
            mapQuery.insert(":nScriptId",QVariant(0));//��ָ�����

        mapQuery.insert(":nOffsetAddrID",QVariant(nOffsetID));//��ָ�����
        mapQuery.insert(":nZvalue",QVariant(zValue()));
        mapQuery.insert(":nCollidindId",QVariant(index));
        mapQuery.insert(":nShowPropId",QVariant(m_ascii.nShowPropId));
        mapQuery.insert(":nTouchPropId",QVariant(m_ascii.nTouchPropId));
        pwnd->inSertDbQuery("dataShow",mapQuery);
    }
    else if(DATETIMEINPUT == m_etabPag)
    {

        mapQuery.clear();
//        sqlTimequery.prepare("INSERT INTO time(nItemId, eShowDate, eShowWeek, eShowTime,"
//                              "nFontColor, nBackground)"
//                              "VALUES (:nItemId, :eShowDate, :eShowWeek, :eShowTime,"
//                              ":nFontColor, :nBackground)");
        mapQuery.insert(":nItemId",QVariant(nItemId));
        if(m_time.bDateMark)
        {
           mapQuery.insert(":eShowDate",QVariant(m_time.eShowDate + 1));
        }
        else
        {
           mapQuery.insert(":eShowDate",QVariant(-1));
        }

        if(m_time.bWeekMark)
        {
            if(0 == m_time.nLanguageTypeId)
            {
                mapQuery.insert(":eShowWeek",QVariant(1));//���ĸ�ʽ��1
            }
            else
            {
                mapQuery.insert(":eShowWeek",QVariant(2));//Ӣ�ĸ�ʽ���ڴ�2
            }

        }
        else
        {
            mapQuery.insert(":eShowWeek",QVariant(-1));
        }
        if(m_time.bTimeMark)
        {
            mapQuery.insert(":eShowTime",QVariant(m_time.eShowTime + 1));
        }
        else
        {
            mapQuery.insert(":eShowTime",QVariant(-1));
        }
        mColor = pwnd->StringTOColor(m_time.nFontColor);
        mapQuery.insert(":nFontColor",QVariant(ColorToInt(mColor)));
        mColor = pwnd->StringTOColor(m_time.nBackground);
        if(0 == GetPattern())
        {
            mapQuery.insert(":nBackground",QVariant(0));
        }
        else
        {
            mapQuery.insert(":nBackground",QVariant(ColorToInt(mColor)));
        }
        pwnd->inSertDbQuery("time",mapQuery);

        mapQuery.clear();
//        sqlquery.prepare("INSERT INTO dataShow(nItemId, nSceneId,eItemType, nStartX, nStartY, nWidth,"
//                          "nHeight, nTextStartX, nTextStartY, nTextWidth, nTextHeight,"
//                          "sShapId, nTransparent, sFontStyle, nFontSize, eFontCss, bIsStartStatement, nScriptId,nOffsetAddrID, nZvalue, nCollidindId, nShowPropId,"
//                          "nTouchPropId)"
//                          "VALUES (:nItemId, :nSceneId, :eItemType,:nStartX, :nStartY, :nWidth,"
//                          ":nHeight, :nTextStartX, :nTextStartY, :nTextWidth, :nTextHeight,"
//                          ":sShapId, :nTransparent, :sFontStyle, :nFontSize, :eFontCss, :bIsStartStatement, :nScriptId,:nOffsetAddrID, :nZvalue, :nCollidindId, :nShowPropId,"
//                          ":nTouchPropId)");

        mapQuery.insert(":nItemId",QVariant(nItemId));
        mapQuery.insert(":nSceneId",QVariant(nSceneId));
        mapQuery.insert(":eItemType",QVariant(m_etabPag + 1));
        mapQuery.insert(":nStartX",QVariant(m_time.nStartX));
        mapQuery.insert(":nStartY",QVariant(m_time.nStartY));
        mapQuery.insert(":nWidth",QVariant(m_time.nWidth));
        mapQuery.insert(":nHeight",QVariant(m_time.nHeight));
        mapQuery.insert(":nTextStartX",QVariant(m_time.nTextStartX));
        mapQuery.insert(":nTextStartY",QVariant(m_time.nTextStartY));
        mapQuery.insert(":nTextWidth",QVariant(m_time.nTextWidth));
        mapQuery.insert(":nTextHeight",QVariant(m_time.nTextHeight));
        QString newPath = "";
        if("" != m_time.nShapId)
        {
            bool bLib = false;
            if(LIBRARY == m_eIspic)
            {
                bLib = true;
            }
            newPath = pwnd->SavePath(m_time.nShapId,boundingRect().size(),bLib);
            newPath = newPath.replace("\\","/");
            newPath = newPath.section("/",-1);
            newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
        }
        mapQuery.insert(":sShapId",QVariant(newPath));//��ʱû��ͼ��
        mapQuery.insert(":nTransparent",QVariant(m_time.nTransparent));
        mapQuery.insert(":sFontStyle",QVariant(m_time.sFontType));//��������~~~~~~~~~~
        mapQuery.insert(":nFontSize",QVariant(m_time.nFontSize + 5));
        mapQuery.insert(":eFontCss",QVariant(m_time.eFontCss));
        mapQuery.insert(":nZvalue",QVariant(zValue()));
        mapQuery.insert(":nCollidindId",QVariant(index));
        mapQuery.insert(":nShowPropId",QVariant(1));
        mapQuery.insert(":nTouchPropId",QVariant(1));
        pwnd->inSertDbQuery("dataShow",mapQuery);
    }
    //�ڴ���ӱ���Ȩ��ҳ�����Դ���
}

int DataDisplayItem::GroupType()
{
    if(DATAINPUTSHOW == m_etabPag)
    {
        return SAM_DRAW_GROUP_VALUE;
    }
    else if(ASCIIINPUTSHOW == m_etabPag)
    {
        return SAM_DRAW_GROUP_ASCII;
    }
    else
    {
        return SAM_DRAW_GROUP_TIME;
    }
}

void DataDisplayItem::save(QDataStream &stream)
{
    QVisableItem::save(stream);

    int nType = 0;
    nType = int(m_etabPag);
    stream << nType;

    nType = int(m_eIspic);
    stream<< nType;
    if(ASCIIINPUTSHOW == m_etabPag)
    {
        nType = (int)m_ascii.etabPag;
        stream << nType;
        stream << m_ascii.nShapId;
        stream << m_ascii.sAddress;
        stream << m_ascii.eNumberType;
        stream << m_ascii.bIsinput;
        stream << m_ascii.nFontStyle;
        stream << m_ascii.sFontType;
        stream << m_ascii.nFontsize;
        stream << m_ascii.nLanguageTypeId;
        stream << m_ascii.eFontCss;
        stream << m_ascii.nShowCharNumber;
        nType = int(m_ascii.nShowStyle);
        stream << nType;
        stream << m_ascii.nCode;
        stream << m_ascii.nFontColor;
        stream << m_ascii.nBackColor;
        nType = (int)m_ascii.eInputTypeId;
        stream << nType;
        stream << m_ascii.nKeyId;
        stream << m_ascii.sKeyname;
        stream << m_ascii.nKeyMark;
        stream << m_ascii.addr;
        stream << m_ascii.sAddrBit;
        stream << m_ascii.addrBit;
        stream << m_ascii.bUseMacro;
        stream << m_ascii.macroName;
        stream << m_ascii.functionName;
        stream << m_ascii.nTransparent;
        stream << m_ascii.bInputSign;
        stream << m_ascii.nBoardX;
        stream << m_ascii.nBoardY;
        stream << m_ascii.bAutoChangeBit;

        stream << m_ascii.bOffset;
        stream << m_ascii.addrOffset;

        stream << m_ascii.bInputIsShow;
        stream << m_ascii.addrInputSame;
    }
    else if(DATAINPUTSHOW == m_etabPag)
    {
        nType = (int)m_data.etabPag;
        stream << nType;
        stream << m_data.nShapId;
        stream << m_data.nAddress;
        stream << m_data.bIsInput;
        stream << m_data.bIsScale;
        stream << m_data.eNumberType;
        stream << m_data.nByteLength;
        stream << m_data.sSourceMax;
        stream << m_data.sSourceMin;
        stream << m_data.sShow;
        stream << m_data.bRound;
        stream << m_data.sShowMax;
        stream << m_data.sShowMin;
        stream << m_data.nFontType;
        stream << m_data.sFontType;
        stream << m_data.nFontSize;
        stream << m_data.eFontCss;
        stream << m_data.nAllbytelength;
        stream << m_data.sDecimalType;
        stream << m_data.sDecimalLength;
        stream << m_data.sDecimalAddress;
        nType = int(m_data.eShowStyle);
        stream << nType;
        stream << m_data.nFontColor;
        stream << m_data.nBackColor;
        stream << m_data.nHightColor;
        stream << m_data.nLowerColor;
        nType = int(m_data.eInputTypeId);
        stream << nType;
        stream << m_data.nKeyMark;
        stream << m_data.nKeyId;
        stream << m_data.sKeyname;
        stream << m_data.nPreView;
        stream << m_data.addr;
        stream << m_data.addrSourceMax;
        stream << m_data.addrSourceMin;
        stream << m_data.addrShowMin;
        stream << m_data.addrShowMax;
        stream << m_data.sAddrBit;
        stream << m_data.addrBit;
        stream << m_data.addrDicmal;
        stream << m_data.nHightNumber;
        stream << m_data.nLowerNumber;
        stream << m_data.bUseMacro;
        stream << m_data.macroName;
        stream << m_data.functionName;
        stream << m_data.nTransparent;

        stream << m_data.eInputAreaType;
        stream << m_data.addrInputMax;
        stream << m_data.addrInputMin;
        stream << m_data.sInputMax;
        stream << m_data.sInputMin;
        stream << m_data.bInputSign;
        stream << m_data.nBoardX;
        stream << m_data.nBoardY;
        stream << m_data.bAutoChangeBit;

        stream << m_data.bOffset;
        stream << m_data.addrOffset;

        stream << m_data.bInputIsShow;
        stream << m_data.addrInputSame;

        stream << m_data.bOutExpression;//�Ƿ�ʹ�ñ��ʽ
        stream << m_data.bInExpression;//�Ƿ�ʹ�ñ���
        stream << m_data.m_inputExp;
        stream << m_data.m_outputExp;
    }
    else if(DATETIMEINPUT == m_etabPag)
    {
        nType = (int)m_time.etabPag;
        stream << nType;
        stream << m_time.nShapId;
        stream << m_time.nFontStyle;
        stream << m_time.sFontType;
        stream << m_time.nFontSize;
        stream << m_time.eFontCss;
        stream << m_time.eShowDate;
        stream << m_time.eShowTime;
        stream << m_time.nFontColor;
        stream << m_time.nBackground;
        stream << m_time.bDateMark;
        stream << m_time.bTimeMark;
        stream << m_time.bWeekMark;
        nType = (int)m_time.nShowStyle;
        stream << nType;
        stream << m_time.nPreView;
        stream << m_time.nLanguageTypeId;
        stream << m_time.nTransparent;
        //stream << m_time.addr;
    }
}

void DataDisplayItem::load(QDataStream &stream)
{
    QVisableItem::load(stream);

    int nType = 0;
    stream >> nType;
    m_etabPag = VALUESHOWTYPE(nType);

    stream >>nType;
    m_eIspic = EITEM_TYPE(nType);
    if(ASCIIINPUTSHOW == m_etabPag)
    {
        stream >> nType;
        m_ascii.etabPag = VALUESHOWTYPE(nType);
        stream >> m_ascii.nShapId;
        stream >> m_ascii.sAddress;
        stream >> m_ascii.eNumberType;
        stream >> m_ascii.bIsinput;
        stream >> m_ascii.nFontStyle;
        stream >> m_ascii.sFontType;
        stream >> m_ascii.nFontsize;
        stream >> m_ascii.nLanguageTypeId;
        stream >> m_ascii.eFontCss;
        stream >> m_ascii.nShowCharNumber;
        stream >> nType;
        m_ascii.nShowStyle = TextPosition(nType);
        stream >> m_ascii.nCode;
        stream >> m_ascii.nFontColor;
        stream >> m_ascii.nBackColor;
        stream >> nType;
        m_ascii.eInputTypeId = InputMode(nType);
        stream >> m_ascii.nKeyId;
        stream >> m_ascii.sKeyname;
        stream >> m_ascii.nKeyMark;
        stream >> m_ascii.addr;
        stream >> m_ascii.sAddrBit;
        stream >> m_ascii.addrBit;
        stream >> m_ascii.bUseMacro;
        stream >> m_ascii.macroName;
        stream >> m_ascii.functionName;
        stream >> m_ascii.nTransparent;

        m_data.nShapId = m_ascii.nShapId;
        m_time.nShapId = m_ascii.nShapId;

        if (pwnd->getProVersion() < 2467)
        {
            m_ascii.bInputSign = false;
            m_ascii.nBoardX = 0;
            m_ascii.nBoardY = 0;
        }
        else
        {
            stream >> m_ascii.bInputSign;
            stream >> m_ascii.nBoardX;
            stream >> m_ascii.nBoardY;
        }

        if (pwnd->getProVersion() < 2562)
        {
            m_ascii.bAutoChangeBit = true;
        }
        else
        {
            stream >> m_ascii.bAutoChangeBit;
        }

        if (pwnd->getProVersion() < 2850)
        {
            m_ascii.bOffset = false;
        }
        else
        {
            stream >> m_ascii.bOffset;
            stream >> m_ascii.addrOffset;
        }

        if (pwnd->getProVersion() < 3258)
        {
            m_ascii.bInputIsShow = true;
            m_ascii.addrInputSame = m_ascii.addr;
        }
        else
        {
            stream >> m_ascii.bInputIsShow;
            stream >> m_ascii.addrInputSame;
        }
    }
    else if(DATAINPUTSHOW == m_etabPag)
    {
        stream >> nType;
        m_data.etabPag = (VALUESHOWTYPE)nType;
        stream >> m_data.nShapId;
        stream >> m_data.nAddress;
        stream >> m_data.bIsInput;
        stream >> m_data.bIsScale;
        stream >> m_data.eNumberType;
        stream >> m_data.nByteLength;
        stream >> m_data.sSourceMax;
        stream >> m_data.sSourceMin;
        stream >> m_data.sShow;
        stream >> m_data.bRound;
        stream >> m_data.sShowMax;
        stream >> m_data.sShowMin;
        stream >> m_data.nFontType;
        stream >> m_data.sFontType;
        stream >> m_data.nFontSize;
        stream >> m_data.eFontCss;
        stream >> m_data.nAllbytelength;
        stream >> m_data.sDecimalType;
        stream >> m_data.sDecimalLength;
        stream >> m_data.sDecimalAddress;
        stream >> nType;
        m_data.eShowStyle = (TextPosition)nType;
        stream >> m_data.nFontColor;
        stream >> m_data.nBackColor;
        stream >> m_data.nHightColor;
        stream >> m_data.nLowerColor;
        stream >> nType;
        m_data.eInputTypeId = (InputMode)nType;
        stream >> m_data.nKeyMark;
        stream >> m_data.nKeyId;
        stream >> m_data.sKeyname;
        stream >> m_data.nPreView;
        stream >> m_data.addr;
        stream >> m_data.addrSourceMax;
        stream >> m_data.addrSourceMin;
        stream >> m_data.addrShowMin;
        stream >> m_data.addrShowMax;
        stream >> m_data.sAddrBit;
        stream >> m_data.addrBit;
        stream >> m_data.addrDicmal;
        stream >> m_data.nHightNumber;
        stream >> m_data.nLowerNumber;
        stream >> m_data.bUseMacro;
        stream >> m_data.macroName;
        stream >> m_data.functionName;
        stream >> m_data.nTransparent;

        m_ascii.nShapId = m_data.nShapId;
        m_time.nShapId = m_data.nShapId;

        if (pwnd->getProVersion() < 2467)
        {
            m_data.eInputAreaType = 0;
            m_data.addrInputMax = m_data.addrSourceMax;
            m_data.addrInputMin = m_data.addrSourceMin;
            m_data.sInputMax = m_data.sSourceMax;
            m_data.sInputMin = m_data.sSourceMin;
            m_data.bInputSign = false;
            m_data.nBoardX = 0;
            m_data.nBoardY = 0;
        }
        else
        {
            if(pwnd->getProVersion() < 2520)
            {
                m_data.eInputAreaType = 0;
            }
            else
            {
                stream >> m_data.eInputAreaType;
            }
            stream >> m_data.addrInputMax;
            stream >> m_data.addrInputMin;
            stream >> m_data.sInputMax;
            stream >> m_data.sInputMin;
            stream >> m_data.bInputSign;
            stream >> m_data.nBoardX;
            stream >> m_data.nBoardY;
        }

        if (pwnd->getProVersion() < 2562)
        {
            m_data.bAutoChangeBit = true;
        }
        else
        {
            stream >> m_data.bAutoChangeBit;
        }

        if (pwnd->getProVersion() < 2850)
        {
            m_data.bOffset = false;
        }
        else
        {
            stream >> m_data.bOffset;
            stream >> m_data.addrOffset;
        }

        if (pwnd->getProVersion() < 3258)
        {
            m_data.bInputIsShow = true;
            m_data.addrInputSame = m_data.addr;
        }
        else
        {
            stream >> m_data.bInputIsShow;
            stream >> m_data.addrInputSame;
        }
        if (pwnd->getProVersion() < 3441)
        {
            m_data.bOutExpression = false;
            m_data.bInExpression = false;
        }
        else
        {
            stream >> m_data.bOutExpression;//�Ƿ�ʹ�ñ��ʽ
            stream >> m_data.bInExpression;//�Ƿ�ʹ�ñ���
            stream >> m_data.m_inputExp;
            stream >> m_data.m_outputExp;
        }

    }
    else if(DATETIMEINPUT == m_etabPag)
    {
        stream >> nType;
        m_time.etabPag = (VALUESHOWTYPE)nType;
        stream >> m_time.nShapId;
        stream >> m_time.nFontStyle;
        stream >> m_time.sFontType;
        stream >> m_time.nFontSize;
        stream >> m_time.eFontCss;
        stream >> m_time.eShowDate;
        stream >> m_time.eShowTime;
        stream >> m_time.nFontColor;
        stream >> m_time.nBackground;
        stream >> m_time.bDateMark;
        stream >> m_time.bTimeMark;
        stream >> m_time.bWeekMark;
        stream >> nType;
        m_time.nShowStyle = (TextPosition)nType;
        stream >> m_time.nPreView;
        stream >> m_time.nLanguageTypeId;
        stream >> m_time.nTransparent;
        //stream >> m_time.addr;

        m_ascii.nShapId = m_time.nShapId;
        m_data.nShapId = m_time.nShapId;
    }
}

void DataDisplayItem::onSaveDataInfo(DataInfo data_st)    //������ֵ��ʾ��Ϣ
{
    m_data = data_st;
    m_etabPag = data_st.etabPag;
}

void DataDisplayItem::onSaveAsciiInfo(ASCIIINFO ascii_st)        //����ASCII������Ϣ
{
    m_ascii = ascii_st;
    m_etabPag = ascii_st.etabPag;
}

void DataDisplayItem::onSaveTimeInfo(TIMEINFO time_st)        //����ʱ����ʾ��Ϣ
{
    m_time = time_st;
    m_etabPag = time_st.etabPag;
}

void DataDisplayItem::onGetPosition()
{
    QRectF oldpos = sceneBoundingRect();
    QRectF textOldpos;

    QList <QGraphicsItem *> itemList;
    itemList = childItems();
    foreach(QGraphicsItem *pItem,itemList)
    {
        if("mText" == pItem->data(GROUP_NAME_KEY).toString())
        {
           textOldpos = pItem->sceneBoundingRect();
           break;
        }
    }

    if(DATAINPUTSHOW == m_etabPag)
    {
        m_data.nStartX = oldpos.x();
        m_data.nStartY = oldpos.y();
        m_data.nWidth = oldpos.width();
        m_data.nHeight = oldpos.height();

        m_data.nTextStartX = textOldpos.x();
        m_data.nTextStartY = textOldpos.y();
        m_data.nTextWidth = textOldpos.width();
        m_data.nTextHeight = textOldpos.height();
    }
    else if(ASCIIINPUTSHOW == m_etabPag)
    {
        m_ascii.nStartX = oldpos.x();
        m_ascii.nStartY = oldpos.y();
        m_ascii.nWidth = oldpos.width();
        m_ascii.nHeight = oldpos.height();

        m_ascii.nTextStartX = textOldpos.x();
        m_ascii.nTextStartY = textOldpos.y();
        m_ascii.nTextWidth = textOldpos.width();
        m_ascii.nTextHeight = textOldpos.height();
    }
    else if(DATETIMEINPUT == m_etabPag)
    {
        m_time.nStartX = oldpos.x();
        m_time.nStartY = oldpos.y();
        m_time.nWidth = oldpos.width();
        m_time.nHeight = oldpos.height();

        m_time.nTextStartX = textOldpos.x();
        m_time.nTextStartY = textOldpos.y();
        m_time.nTextWidth = textOldpos.width();
        m_time.nTextHeight = textOldpos.height();
    }
}

/*****************************************************************************
  �������ƣ�SetTextAlign(int nAlignType)
  �������壺�����ı��Ķ��뷽ʽ
  �������壺nAlignType
  nAlignType=1:���ϽǶ���
  nAlignType=2:�ϱ߶���
  nAlignType=3:���ϽǶ���
  nAlignType=4:��߶���
  nAlignType=5:���ж���
  nAlignType=6:�ұ߶���
  nAlignType=7:���½Ƕ���
  nAlignType=8:�±߶���
  nAlignType=9:���½Ƕ���
*****************************************************************************/
void DataDisplayItem::SetTextAlign(int nAlignType)
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->m_Alianment = nAlignType;
        switch(pText->m_Alianment)
        {
            //case 1: AlianmentFlag = Qt::AlignLeft | Qt::AlignTop; break;
            //case 2: AlianmentFlag = Qt::AlignTop | Qt::AlignHCenter; break;
            //case 3: AlianmentFlag = Qt::AlignRight | Qt::AlignTop; break;

            case 4: pText->AlianmentFlag = Qt::AlignLeft | Qt::AlignVCenter; break;
            case 5: pText->AlianmentFlag = Qt::AlignCenter; break;
            case 6: pText->AlianmentFlag = Qt::AlignRight | Qt::AlignCenter; break;

            //case 7: AlianmentFlag = Qt::AlignLeft | Qt::AlignBottom; break;
            //case 8: AlianmentFlag = Qt::AlignBottom | Qt::AlignHCenter; break;
            //case 9: AlianmentFlag = Qt::AlignRight | Qt::AlignBottom; break;
        }
        pText->update(pText->m_rect);
    }
}

int DataDisplayItem::GetTextAlign() //����ı��Ķ��뷽ʽ
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        return pText->m_Alianment;
    }
}

void DataDisplayItem::SetRectBackColor(QColor color) //���ñ������ο�ı���ɫ
{
    QString str = pwnd->ColorTOString(color);
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetRectBackColor(color);
    }
}

void DataDisplayItem::SetFontColor(QColor color) //����������ɫ
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetFontColor(color);
    }
}

void DataDisplayItem::SetText(QString sText) //�����ı�
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetText(sText);
    }
}

void DataDisplayItem::SetPattern(int nType)
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetPattern(nType);
    }
}

void DataDisplayItem::SetAlpha(int nType)
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetAlpha(nType);
    }
}

//�����ı�itemָ��
QGraphicsItem* DataDisplayItem::GetBackItem()
{
    foreach(QGraphicsItem* pItem,childItems())
    {
        if("mFramRect" == pItem->data(GROUP_NAME_KEY).toString())
        {
            return pItem;
        }
    }
    return NULL;
}

int DataDisplayItem::GetPattern() //�����ʽ
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        return pText->GetPattern();
    }
}

QString DataDisplayItem::GetKeyboardName()
{
    if(DATAINPUTSHOW == m_etabPag)
    {
        return m_data.sKeyname;
    }
    else if(ASCIIINPUTSHOW == m_etabPag)
    {
        return m_ascii.sKeyname;
    }
    else
    {
        return "";
    }
}

void DataDisplayItem::SetKeyBoardInfo(QString sName, int index)
{
    if(DATAINPUTSHOW == m_etabPag)
    {
        if(-1 == index)
        {
            m_data.nKeyMark = false;
            m_data.sKeyname = "";
            m_data.nKeyId = 0;
        }
        m_data.sKeyname = sName;
        m_data.nKeyId = index;
    }
    else if(ASCIIINPUTSHOW == m_etabPag)
    {
        if(-1 == index)
        {
            m_ascii.nKeyMark = false;
            m_ascii.sKeyname = "";
            m_ascii.nKeyId = 0;
        }
        m_ascii.sKeyname = sName;
        m_ascii.nKeyId = index;
    }
}

void DataDisplayItem::insertMacroTable(QSqlDatabase &db,int itemId,int &count,int sceneId,QString macroName,QString functionName)
{
        int macroId = count;

        QMap<QString,QVariant> mapQuery;
        //QSqlQuery sqlquery(db);
//        sqlquery.prepare("INSERT INTO macro(MacroID , MacroLibName , MacroName , MacroType ,"
//                "TimeInterval ,ControlAddr ,ControlAddrType ,ExecCondition , nCmpFactor , "
//                "nCompID , SceneID )"
//                "VALUES (:MacroID , :MacroLibName , :MacroName , :MacroType ,"
//                ":TimeInterval ,:ControlAddr ,:ControlAddrType ,:ExecCondition , :nCmpFactor ,"
//                ":nCompID , :SceneID )");

        {
                mapQuery.insert(":MacroID",QVariant(macroId));// ��ı� id
                mapQuery.insert(":MacroLibName",QVariant(macroName));//
                mapQuery.insert(":MacroName",QVariant("MACRO_MAIN"));//
                mapQuery.insert(":MacroType",QVariant(6));//
                mapQuery.insert(":nCompID",QVariant(itemId));// �ؼ���ID
                mapQuery.insert(":SceneID",QVariant(sceneId));//����ID
                mapQuery.insert(":scriptCount",QVariant(1));
//                bool result = false;
//                result = sqlquery.exec();
//                qDebug() << "insert textProp macro :"<<result;
                pwnd->inSertDbQuery("macro",mapQuery);
        }
}

//������ʽ������
void DataDisplayItem::insertExpressTable(QSqlDatabase &db,Expression exp,int &count,int addLength,int itemId)
{
    QMap<QString,QVariant> mapQuery;
    int nItemId = count;

    //express(nItemId ,nFirstSign ,nFirstNumberType ,"
     //                        "nFirstNumber ,nSecondSign ,nSecondNumberType ,nSecondNumber ,"
     //                        "nThirdNumberType ,nThirdNumber, nThirdSign )"

    mapQuery.insert(":nItemId",QVariant(count));// �� id

    mapQuery.insert(":nFirstSign",QVariant(short(exp.op1)));//������
    mapQuery.insert(":nSecondSign",QVariant(short(exp.op2)));//������
    mapQuery.insert(":nThirdSign",QVariant(short(exp.op3)));//������


    ADDR_PARAMENTS stParams;
    stParams.itemId = itemId;
    stParams.eType = OBJ_ITEM;
    stParams.addrNum = -1;
    stParams.eRWtype = SCENE_CONTROL_LOOP_R;

    if(exp.op1 != OPR_NONE)
    {
        mapQuery.insert(":nFirstNumberType",QVariant(exp.bConstant1 + 1));//
        if(!exp.bConstant1)//��ַ
        {
            count++;
            //�޸ĵ�ַ�������
            stParams.id = count;
            exp.var2.Length = addLength;
            exp.var2.compile(db,stParams);
            mapQuery.insert(":nFirstNumber",QVariant(double(count)));
        }
        else
        {
            mapQuery.insert(":nFirstNumber",QVariant(exp.constant1));
        }
    }

    if(exp.op2 != OPR_NONE)
    {
        mapQuery.insert(":nSecondNumberType",QVariant(exp.bConstant2 + 1));//
        if(!exp.bConstant2)//��ַ
        {
            count++;
            //�޸ĵ�ַ�������
            stParams.id = count;
            exp.var3.Length = addLength;
            exp.var3.compile(db,stParams);
            mapQuery.insert(":nSecondNumber",QVariant(double(count)));
        }
        else
        {
            mapQuery.insert(":nSecondNumber",QVariant(exp.constant2));
        }
    }

    if(exp.op3 != OPR_NONE)
    {
        mapQuery.insert(":nThirdNumberType",QVariant(exp.bConstant3 + 1));//
        if(!exp.bConstant3)//��ַ
        {
            count++;
            //�޸ĵ�ַ�������
            stParams.id = count;
            exp.var4.Length = addLength;
            exp.var4.compile(db,stParams);
            mapQuery.insert(":nThirdNumber",QVariant(double(count)));
        }
        else
        {
            mapQuery.insert(":nThirdNumber",QVariant(exp.constant3));
        }
    }

    pwnd->inSertDbQuery("express",mapQuery);


}
//��ò�����ַ
QList<Keyboard> DataDisplayItem::getAddress()
{
    QList<Keyboard> addrs;
    switch(m_etabPag)
    {
    case DATAINPUTSHOW:     //��ֵ��ʾ
        addrs << m_data.addr;
        break;
    case ASCIIINPUTSHOW:     //ascill��ʾ
        addrs << m_ascii.addr;
        break;
    case DATETIMEINPUT:     //ʱ����ʾ
        break;
    }
    return addrs;
}
//���ò�����ַ
void DataDisplayItem::setAddress(QList<Keyboard> addr)
{
    if (addr.size() <= 0)
        return ;
    switch(m_etabPag)
    {
    case DATAINPUTSHOW:     //��ֵ��ʾ
        m_data.addr = addr.first();
        m_data.nAddress = m_data.addr.sShowAddr;
        break;
    case ASCIIINPUTSHOW:     //ascill��ʾ
        m_ascii.addr = addr.first();
        m_ascii.sAddress = m_ascii.addr.sShowAddr;
        break;
    default:
        break;
    }
}

QStringList DataDisplayItem::getAllFonts()
{
    QStringList ls;
    ls.clear();
    switch(m_etabPag)
    {
    case DATAINPUTSHOW:     //��ֵ��ʾ
        ls << m_data.sFontType;
        break;
    case ASCIIINPUTSHOW:     //ascill��ʾ
        ls << m_ascii.sFontType;
        break;
    case DATETIMEINPUT:     //ʱ����ʾ
        ls << m_time.sFontType;
        break;
    }
    return ls;
}

QVector<ADDRPRO> DataDisplayItem::getAllItemAddr()
{
    lsX.clear();
    ADDRPRO Addr;

    switch(m_etabPag)
    {
    case DATAINPUTSHOW:     //��ֵ��ʾ
        Addr.pAddr = &m_data.addr;
        Addr.str   = QObject::tr("��ֵ��ʾ������ֵ�ַ");
        Addr.type  = 1;
        lsX << Addr;

        if(m_data.bIsInput && 1 == m_data.eInputAreaType)
        {
            Addr.pAddr = &m_data.addrInputMax;
            Addr.str   = QObject::tr("��ֵ��ʾ�����뷶Χ���ֵ��ַ");
            Addr.type  = 1;
            lsX << Addr;

            Addr.pAddr = &m_data.addrInputMin;
            Addr.str   = QObject::tr("��ֵ��ʾ�����뷶Χ��Сֵ��ַ");
            Addr.type  = 1;
            lsX << Addr;

        }

        if(1 == m_data.nByteLength)
        {
            Addr.pAddr = &m_data.addrSourceMin;
            Addr.str   = QObject::tr("��ֵ��ʾ��Դ��Χ��Сֵ��ַ");
            Addr.type  = 1;
            lsX << Addr;

            Addr.pAddr = &m_data.addrSourceMax;
            Addr.str   = QObject::tr("��ֵ��ʾ��Դ��Χ���ֵ��ַ");
            Addr.type  = 1;
            lsX << Addr;

        }
        if(1 == m_data.sShow)
        {
            Addr.pAddr = &m_data.addrShowMin;
            Addr.str   = QObject::tr("��ֵ��ʾ����ʾ��Χ��Сֵ��ַ");
            Addr.type  = 1;
            lsX << Addr;

            Addr.pAddr = &m_data.addrShowMax;
            Addr.str   = QObject::tr("��ֵ��ʾ����ʾ��Χ���ֵ��ַ");
            Addr.type  = 1;
            lsX << Addr;

        }
        if(m_data.bIsInput &&(Bit == m_data.eInputTypeId))
        {
            Addr.pAddr = &m_data.addrBit;
            Addr.str   = QObject::tr("��ֵ��ʾ��λ�����ַ");
            Addr.type  = 0;
            lsX << Addr;
        }
        if(1 == m_data.sDecimalType)
        {
            Addr.pAddr = &m_data.addrDicmal;
            Addr.str   = QObject::tr("��ֵ��ʾ��С��λ����ַ");
            Addr.type  = 1;
            lsX << Addr;
        }
        break;
    case ASCIIINPUTSHOW:     //ascill��ʾ
        Addr.pAddr = &m_ascii.addr;
        Addr.str   = QObject::tr("��ֵ��ʾ������ֵ�ַ");
        Addr.type  = 1;
        lsX << Addr;

        if(m_ascii.bIsinput &&(Bit == m_ascii.eInputTypeId))//λ��ַ
        {
            Addr.pAddr = &m_ascii.addrBit;
            Addr.str = QObject::tr("��ֵ��ʾ��λ�����ַ");
            Addr.type  = 0;
            lsX << Addr;
        }
        break;
    case DATETIMEINPUT:     //ʱ����ʾ
        break;
    }

    QVector<ADDRPRO> AddrList;
    AddrList = QVisableItem::getAllItemAddr();
    for(int i = 0; i < AddrList.size(); i++)
    {
        Addr.pAddr = AddrList.at(i).pAddr;
        Addr.str   = QObject::tr("��ֵ��ʾ��") + AddrList.at(i).str;
        Addr.type  = AddrList.at(i).type;
        lsX << Addr;
    }
    return lsX;
}

QString  DataDisplayItem::getItemName()
{
    return QObject::tr("��ֵ��ʾ��");
}

void DataDisplayItem::redrawForChangeStatus(int index, int lan)
{
    QString sPath = "";
    switch(m_etabPag)
    {
    case DATAINPUTSHOW:     //��ֵ��ʾ
        sPath = m_data.nShapId;
        break;
    case ASCIIINPUTSHOW:     //ascill��ʾ
        sPath = m_ascii.nShapId;
        break;
    case DATETIMEINPUT:     //ʱ����ʾ
        sPath = m_time.nShapId;
        break;
    default:
        return;
    }
    foreach(QGraphicsItem *pItem,this->childItems())
    {
        if(SAM_DRAW_OBJECT_PIXMAP == pItem->type())
        {
            int zValue = pItem->zValue();
            QRectF rect = pItem->sceneBoundingRect();
            QPixmap picture = QPixmap(sPath);
            if (!picture)
            {
                return ;
            }
            QPixmapItem *PicItem = new QPixmapItem(picture,rect.size().toSize());
            PicItem->setPos(rect.topLeft());

            PicItem->setZValue(0);
            PicItem->setFlag(QGraphicsItem::ItemIsSelectable,false);
            this->addToGroup(PicItem);

            QGraphicsItem *pTopItem = this->topLevelItem();
            QItemGroup *pArentItem = dynamic_cast<QItemGroup *> (pTopItem);
            if(pArentItem)
            {
                pArentItem->removeFromGroup(pItem);
                //wxy�޸���ֵ��ʾ�ؼ��ڹ����л�״̬ʱ��������Ӱ
                if(pItem)
                {
                    pItem->hide();
                    delete pItem;
                    pItem = NULL;
                }
            }
        }
        else if(SAM_DRAW_OBJECT_TEXT == pItem->type())
        {
            pItem->setZValue(1);
        }
    }
}

int DataDisplayItem::getCurrentState()
{
    return 0;
}

void DataDisplayItem::UpdateKeyboardInfo()
{
    QString sKeyName = GetKeyboardName();
    QStringList sNamelist;
    sNamelist.clear();
    for(int i = 0; i< pwnd->pSceneSheet.size(); i++)
    {
        if(2 == pwnd->pSceneSheet[i]->nIsSceneOrWindow)
        {
            sNamelist.append(pwnd->pSceneSheet[i]->sNewScreenName);
        }
    }
    if(sKeyName == "" || sNamelist.isEmpty())
    {
        SetKeyBoardInfo("",-1);
    }
    else
    {
        int index = sNamelist.indexOf(sKeyName);
        if(index >= 0)
        {
            SetKeyBoardInfo(sKeyName,index);
        }
        else
        {
            SetKeyBoardInfo("",-1);
        }
    }
}
int DataDisplayItem::checkMacroName(QString &msg)
{
    int result = -1;//�ű�������
    switch(m_etabPag)
    {
    case DATAINPUTSHOW:
        {
            msg = m_data.macroName;
            if(!m_data.bUseMacro)//δʹ�ýű�
            {
                return 1;
            }
            foreach(Macro mac,pwnd->macros)
            {
                if(mac.libName == m_data.macroName)
                {
                    if(mac.isCompiled())//�Ѿ�����ͨ��
                    {
                        result = 1;
                    }
                    else//δ����ͨ��
                    {
                        result = 0;
                    }
                    break;
                }
            }
        }
        break;
    case ASCIIINPUTSHOW:
        {
            msg = m_ascii.macroName;
            if(!m_ascii.bUseMacro)//δʹ�ýű�
            {
                return 1;
            }
            foreach(Macro mac,pwnd->macros)
            {
                if(mac.libName == m_ascii.macroName)
                {
                    if(mac.isCompiled())//�Ѿ�����ͨ��
                    {
                        result = 1;
                    }
                    else//δ����ͨ��
                    {
                        result = 0;
                    }
                    break;
                }
            }
        }
        break;
    default:
        result = 1;
        break;
    }

    return result;
}
