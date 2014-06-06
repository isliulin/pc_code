#include "ChartItem.h"
#include "Frame/qprogectmanager.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;
ChartItem::ChartItem()
    :QVisableItem(0)
{
    common_st.nStartAngle = 0;
    common_st.nSpanAngle = 360;
    common_st.nTransparent = 255;
    common_st.bShowFrame = true;
    //Datesave = new struct CHART_INFORMATION;
}



QGraphicsItem *ChartItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    ChartItem *itemGroup = new ChartItem();

    QList<QGraphicsItem *> itemList;
    int angle = this->rotation();
    QPointF oldPos = this->transformOriginPoint();
    //this->setTransformOriginPoint(oldPos);
    //this->setRotation(0);
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
    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }

    QPointF newPos = itemGroup->boundingRect().center();
    //itemGroup->setTransformOriginPoint(newPos);
    //itemGroup->setRotation(angle);
    itemGroup->onSaveMeter(meter_st);
    itemGroup->onSaveCommon(common_st);
    itemGroup->m_eGraphType = m_eGraphType;
    itemGroup->SaveSecurityPro(&sPro);
    itemGroup->setId(id());
    //this->setRotation(angle);
    return itemGroup;
    //return QItemGroup::Clone();
    //return 0;
    //需要在派生类实例化对象，复制部分无法重用基类代码
}

void ChartItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    QColor mColor;
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

    int naddrID;
    int naddrMinID;
    int naddrMaxID;//记录源最大值的ID号

    onGetPosition();
    QSqlQuery sqlquery(db);

    if(ENCOMMON_TYPE == m_eGraphType)
    {
        if(PILLA == common_st.eShapeType)
        {
            int nKey = this->data(GROUP_TYPE_KEY).toInt();
            if(2 == nKey || 8 == nKey)
            {
                common_st.eRulerDirectio = TOWARD_RIGHT;
            }
            else
            {
                common_st.eRulerDirectio = TOWARD_LEFT;
            }
        }
        else
        {
            common_st.eRulerDirectio = TOWARD_RIGHT;
        }

        count++;
        naddrID = count;
		//修改地址编译参数
        ADDR_PARAMENTS stParams;
        stParams.id = count;
        stParams.itemId = nItemID;
        stParams.eType = OBJ_ITEM;
        stParams.addrNum = -1;
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
        common_st.addr.compile(db,stParams);

        if(1 == common_st.nSourceRang)//如果选择源范围为地址，保存源范围地址
        {
            count++;
            naddrMinID = count;
			//修改地址编译参数
            stParams.id = count;
            stParams.itemId = nItemID;
            stParams.eType = OBJ_ITEM;
            stParams.addrNum = -1;
            common_st.addrSourceMin.compile(db,stParams);

            count++;
            naddrMaxID = count;
			//修改地址编译参数
            stParams.id = count;
            stParams.itemId = nItemID;
            stParams.eType = OBJ_ITEM;
            stParams.addrNum = -1;
            common_st.addrSourceMax.compile(db,stParams);
        }

        QSqlQuery sqlcommon(db);
        sqlcommon.prepare("INSERT INTO commonGraph(nItemId, nBitLength,nStartAngle,nSpanAngle, bSourceMark, nSourceRang, eSourceMin, eSourceMax, bShowMark,"
                          "eShowMin, eShowMax, eShapeType, bFill, bHole,"
                          "nRadius, bStart, nDesign, nDesignColor, nFrameColor, nTransparent, bShowFrame)"
                          "VALUES (:nItemId, :nBitLength,:nStartAngle,:nSpanAngle, :bSourceMark, :nSourceRang, :eSourceMin, :eSourceMax, :bShowMark,"
                          ":eShowMin, :eShowMax, :eShapeType, :bFill, :bHole,"
                          ":nRadius, :bStart, :nDesign, :nDesignColor, :nFrameColor, :nTransparent, :bShowFrame)");
        sqlcommon.bindValue(":nItemId",QVariant(nItemID));
        sqlcommon.bindValue(":nBitLength",QVariant(16));
        sqlcommon.bindValue(":nStartAngle",QVariant(common_st.nStartAngle));
        sqlcommon.bindValue(":nSpanAngle",QVariant(common_st.nSpanAngle));
        sqlcommon.bindValue(":bSourceMark",QVariant(common_st.bSourceMark));
        sqlcommon.bindValue(":nSourceRang",QVariant(common_st.nSourceRang));
        if(0 == common_st.nSourceRang)
        {
            sqlcommon.bindValue(":eSourceMin",QVariant(common_st.eSourceMin));
            sqlcommon.bindValue(":eSourceMax",QVariant(common_st.eSourceMax));
        }
        else
        {
            sqlcommon.bindValue(":eSourceMin",QVariant(naddrMinID));
            sqlcommon.bindValue(":eSourceMax",QVariant(naddrMaxID));
        }

        sqlcommon.bindValue(":bShowMark",QVariant(common_st.bShowMark));
        sqlcommon.bindValue(":eShowMin",QVariant(common_st.eShowMin));
        sqlcommon.bindValue(":eShowMax",QVariant(common_st.eShowMax));
        sqlcommon.bindValue(":eShapeType",QVariant(common_st.eShapeType + 1));
        sqlcommon.bindValue(":bFill",QVariant(common_st.bFill));
        sqlcommon.bindValue(":bHole",QVariant(common_st.bHole));
        sqlcommon.bindValue(":nRadius",QVariant(common_st.nRadius));
        sqlcommon.bindValue(":bStart",QVariant(common_st.bStart));
        sqlcommon.bindValue(":nDesign",QVariant(common_st.nDesign + 1));
        mColor = pwnd->StringTOColor(common_st.nDesignColor);
        sqlcommon.bindValue(":nDesignColor",QVariant(ColorToInt(mColor)));
        mColor = pwnd->StringTOColor(common_st.nFrameColor);
        //wxy，边框颜色与标尺颜色一致，nFrameColor并没有被赋值
        //mColor = pwnd->StringTOColor(common_st.nRulingColor);
        sqlcommon.bindValue(":nFrameColor",QVariant(ColorToInt(mColor)));

        sqlcommon.bindValue(":nTransparent",QVariant(common_st.nTransparent));
        sqlcommon.bindValue(":bShowFrame",QVariant(common_st.bShowFrame));

        sqlcommon.exec();

        sqlquery.prepare("INSERT INTO graphShow(nItemId, nSceneId, eGraphType, eShapeId,sPic,"
                            "mAddress, eDataType, eDirection, nTextColor, nBackcolor,"
                            "nLeftTopX, nLeftTopY, nWidth, nHeight, nMainRuling,"
                            "bShowRuling,bShowRuleValue,nPointType,nRuling, nRulingColor, nShowLeftTopX, nShowLeftTopY,"
                            "nShowWidth, nShowHigth, nRulerLeftTopX, nRulerLeftTopY, nRulerWidth,"
                            "nRulerHigth, eRulerDirectio, bAlarm, nType, nMin, nMax,"
                            "nAlarmTextColor, nDesignColor, nZvalue, nCollidindId, nShowPropId)"
                            "VALUES (:nItemId, :nSceneId, :eGraphType, :eShapeId, :sPic,"
                            ":mAddress, :eDataType, :eDirection, :nTextColor, :nBackcolor,"
                            ":nLeftTopX, :nLeftTopY, :nWidth, :nHeight, :nMainRuling,"
                            ":bShowRuling,:bShowRuleValue,:nPointType,:nRuling, :nRulingColor, :nShowLeftTopX, :nShowLeftTopY,"
                            ":nShowWidth, :nShowHigth, :nRulerLeftTopX, :nRulerLeftTopY, :nRulerWidth,"
                            ":nRulerHigth, :eRulerDirectio, :bAlarm, :nType, :nMin, :nMax,"
                            ":nAlarmTextColor, :nDesignColor, :nZvalue, :nCollidindId, :nShowPropId)");
        sqlquery.bindValue(":nItemId",QVariant(nItemID));
        sqlquery.bindValue(":nSceneId",QVariant(nSceneId));
        sqlquery.bindValue(":eGraphType",QVariant(m_eGraphType + 1));
        sqlquery.bindValue(":nGraphPropId",QVariant(1));//普通图表的ID号
        int nShapeID;
        nShapeID = this->data(GROUP_NAME_KEY).toInt();

        QString sPath = GetPicPath(this,common_st.eShapeType,nShapeID,common_st.eDirection);

        if("" != sPath)
        {
            sPath = sPath.replace("\\","/");
            sPath = sPath.section("/",-1);
            sPath = "/data/data/com.android.Samkoonhmi/pictures/" + sPath;
        }

        sqlquery.bindValue(":eShapeId",QVariant(nShapeID));
        sqlquery.bindValue(":sPic",QVariant(sPath));
        sqlquery.bindValue(":mAddress",QVariant(naddrID));/////////需要转换

        //数据类型转换成结构体中对应的数据类型
        DATA_TYPE eDataType;
        if(0 == common_st.eDataType)//16位整数
        {
            eDataType = POSITIVE_INT_16;
        }
        else if(1 == common_st.eDataType)//16位 正整数
        {
            eDataType = INT_16;
        }
        else if(2 == common_st.eDataType)//32位整数
        {
            eDataType = POSITIVE_INT_32;
        }
        else if(3 == common_st.eDataType)//32位正整数
        {
            eDataType = INT_32;
        }
        else//32位浮点数
        {
            eDataType = FLOAT_32;
        }
        sqlquery.bindValue(":eDataType",QVariant(eDataType));
        sqlquery.bindValue(":eDirection",QVariant(common_st.eDirection));

        mColor = pwnd->StringTOColor(common_st.nTextColor);
        sqlquery.bindValue(":nTextColor",QVariant(ColorToInt(mColor)));
        mColor = pwnd->StringTOColor(common_st.nBackcolor);
        sqlquery.bindValue(":nBackcolor",QVariant(ColorToInt(mColor)));

        sqlquery.bindValue(":nLeftTopX",QVariant(common_st.nLeftTopX));
        sqlquery.bindValue(":nLeftTopY",QVariant(common_st.nLeftTopY));

        sqlquery.bindValue(":nWidth",QVariant(common_st.nWidth));
        sqlquery.bindValue(":nHeight",QVariant(common_st.nHeight));

        sqlquery.bindValue(":nMainRuling",QVariant(common_st.nMainScale));
        sqlquery.bindValue(":bShowRuling",QVariant(common_st.nScaleMark));
        sqlquery.bindValue(":bShowRuleValue",QVariant(common_st.bShowRuleValue));
        sqlquery.bindValue(":nPointTyp",QVariant(common_st.nPointType + 1));
        sqlquery.bindValue(":nRuling",QVariant(common_st.nSubScale));
        mColor = pwnd->StringTOColor(common_st.nRulingColor);
        sqlquery.bindValue(":nRulingColor",QVariant(ColorToInt(mColor)));
        sqlquery.bindValue(":nShowLeftTopX",QVariant(common_st.nShowLeftTopX));
        sqlquery.bindValue(":nShowLeftTopY",QVariant(common_st.nShowLeftTopY));
        sqlquery.bindValue(":nShowWidth",QVariant(common_st.nShowWidth));
        sqlquery.bindValue(":nShowHigth",QVariant(common_st.nShowHigth));

        sqlquery.bindValue(":nRulerLeftTopX",QVariant(common_st.nRulerLeftTopX));
        sqlquery.bindValue(":nRulerLeftTopY",QVariant(common_st.nRulerLeftTopY));
        if(PILLA == common_st.eShapeType || GROOVE == common_st.eShapeType)
        {
            sqlquery.bindValue(":nRulerWidth",QVariant(common_st.nRulerWidth));
            sqlquery.bindValue(":nRulerHigth",QVariant(common_st.nRulerHigth));
        }
        else
        {
            sqlquery.bindValue(":nRulerWidth",QVariant(common_st.nScaleLength));
            sqlquery.bindValue(":nRulerHigth",QVariant(common_st.nScaleLength));
        }
        sqlquery.bindValue(":eRulerDirectio",QVariant(common_st.eRulerDirectio));

        sqlquery.bindValue(":bAlarm",QVariant(common_st.sAlarm.bAlarm));
        sqlquery.bindValue(":nType",QVariant(common_st.sAlarm.nType));//

        if(1 == common_st.sAlarm.nType)//如果报警为地址，保存地址
        {
            count++;
            int nId = count;
                        //修改地址编译参数
            stParams.id = count;
            stParams.itemId = nItemID;
            stParams.eType = OBJ_ITEM;
            stParams.addrNum = -1;
            common_st.sAlarm.nMinaddr.compile(db,stParams);
            sqlquery.bindValue(":nMin",QVariant(nId));

            count++;
            nId = count;
                        //修改地址编译参数
            stParams.id = count;
            stParams.itemId = nItemID;
            stParams.eType = OBJ_ITEM;
            stParams.addrNum = -1;
            common_st.sAlarm.nMaxaddr.compile(db,stParams);
            sqlquery.bindValue(":nMax",QVariant(nId));
        }
        else
        {
            sqlquery.bindValue(":nMin",QVariant(common_st.sAlarm.nMin));
            sqlquery.bindValue(":nMax",QVariant(common_st.sAlarm.nMax));
        }

        mColor = pwnd->StringTOColor(common_st.sAlarm.nTextColor);
        sqlquery.bindValue(":nAlarmTextColor",QVariant(ColorToInt(mColor)));

        mColor = pwnd->StringTOColor(common_st.sAlarm.nDesignColor);
        sqlquery.bindValue(":nDesignColor",QVariant(ColorToInt(mColor)));

        sqlquery.bindValue(":nZvalue",QVariant(zValue()));

        sqlquery.bindValue(":nCollidindId",QVariant(index));

        sqlquery.bindValue(":nShowPropId",QVariant(count));

        sqlquery.exec();
    }
    else if(ENMETER_TYPE == m_eGraphType)
    {
        count++;
        naddrID = count;
        ADDR_PARAMENTS stParams;
        stParams.id = count;
        stParams.itemId = nItemID;
        stParams.eType = OBJ_ITEM;
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
        stParams.addrNum = -1;
		//修改地址编译参数
        meter_st.addr.compile(db,stParams);

        if(1 == meter_st.nSourceRang)//如果选择源范围为地址，保存源范围地址
        {
            count++;
            naddrMinID = count;
            stParams.id = count;
			//修改地址编译参数
            meter_st.addrSourceMin.compile(db,stParams);

            count++;
            naddrMaxID = count;
            stParams.id = count;
			//修改地址编译参数
            meter_st.addrSourceMax.compile(db,stParams);
        }

        QSqlQuery sqlmeter(db);
        sqlmeter.prepare("INSERT INTO meterGraph(nItemId, nBitLength, nSourceMark, nSourceRang, eSourceMin, eSourceMax, bShowMark,"
                          "eShowMin, eShowMax, nTransparent, bShowFrame)"
                          "VALUES (:nItemId, :nBitLength, :nSourceMark, :nSourceRang, :eSourceMin, :eSourceMax, :bShowMark,"
                          ":eShowMin, :eShowMax, :nTransparent, :bShowFrame)");
        sqlmeter.bindValue(":nItemId",QVariant(nItemID));
        sqlmeter.bindValue(":nBitLength",QVariant(16));
        sqlmeter.bindValue(":nSourceMark",QVariant(meter_st.nSourceMark));
        sqlmeter.bindValue(":nSourceRang",QVariant(meter_st.nSourceRang));
        if(0 == meter_st.nSourceRang)
        {
            sqlmeter.bindValue(":eSourceMin",QVariant(meter_st.eSourceMin));
            sqlmeter.bindValue(":eSourceMax",QVariant(meter_st.eSourceMax));
        }
        else
        {
            sqlmeter.bindValue(":eSourceMin",QVariant(naddrMinID));
            sqlmeter.bindValue(":eSourceMax",QVariant(naddrMaxID));
        }

        sqlmeter.bindValue(":bShowMark",QVariant(meter_st.bShowMark));
        sqlmeter.bindValue(":eShowMin",QVariant(meter_st.eShowMin));
        sqlmeter.bindValue(":eShowMax",QVariant(meter_st.eShowMax));
        sqlmeter.bindValue(":nTransparent",QVariant(meter_st.nTransparent));
        sqlmeter.bindValue(":bShowFrame",QVariant(meter_st.bShowFrame));
        sqlmeter.exec();

        sqlquery.prepare("INSERT INTO graphShow(nItemId, nSceneId, eGraphType, eShapeId, sPic,"
                                      "mAddress, eDataType, eDirection, nTextColor, nBackcolor,"
                                      "nLeftTopX, nLeftTopY, nWidth, nHeight, nMainRuling,"
                                      "bShowRuling, bShowRuleValue,nPointType,nRuling, nRulingColor, nShowLeftTopX, nShowLeftTopY,"
                                      "nShowWidth, nShowHigth, nRulerLeftTopX, nRulerLeftTopY, nRulerWidth,"
                                      "nRulerHigth, eRulerDirectio, bAlarm, nType, nMin, nMax,"
                                      "nAlarmTextColor, nDesignColor, nZvalue, nCollidindId, nShowPropId)"
                                      "VALUES (:nItemId, :nSceneId, :eGraphType, :eShapeId, :sPic,"
                                      ":mAddress, :eDataType, :eDirection, :nTextColor, :nBackcolor,"
                                      ":nLeftTopX, :nLeftTopY, :nWidth, :nHeight, :nMainRuling,"
                                      ":bShowRuling, :bShowRuleValue,:nPointType,:nRuling, :nRulingColor, :nShowLeftTopX, :nShowLeftTopY,"
                                      ":nShowWidth, :nShowHigth, :nRulerLeftTopX, :nRulerLeftTopY, :nRulerWidth,"
                                      ":nRulerHigth, :eRulerDirectio, :bAlarm, :nType, :nMin, :nMax,"
                                      ":nAlarmTextColor, :nDesignColor, :nZvalue, :nCollidindId, :nShowPropId)");
        sqlquery.bindValue(":nItemId",QVariant(nItemID));
        sqlquery.bindValue(":nSceneId",QVariant(nSceneId));
        sqlquery.bindValue(":eGraphType",QVariant(m_eGraphType + 1));
        sqlquery.bindValue(":nGraphPropId",QVariant(count));//仪表图表数据库ID号
        int nShapeID;
        nShapeID = this->data(GROUP_NAME_KEY).toInt();
        sqlquery.bindValue(":eShapeId",QVariant(nShapeID));
        sqlquery.bindValue(":sPic",QVariant(""));
        sqlquery.bindValue(":mAddress",QVariant(naddrID));/////////需要转换

        //数据类型转换成结构体中对应的数据类型
        DATA_TYPE eDataType;
        if(0 == meter_st.eDataType)//16位整数
        {
            eDataType = POSITIVE_INT_16;
        }
        else if(1 == meter_st.eDataType)//16位 正整数
        {
            eDataType = INT_16;
        }
        else if(2 == meter_st.eDataType)//32位整数
        {
            eDataType = POSITIVE_INT_32;
        }
        else if(3 == meter_st.eDataType)//32位正整数
        {
            eDataType = INT_32;
        }
        else//32位浮点数
        {
            eDataType = FLOAT_32;
        }
        sqlquery.bindValue(":eDataType",QVariant(eDataType));
        sqlquery.bindValue(":eDirection",QVariant(meter_st.eDirection));

        mColor = pwnd->StringTOColor(meter_st.nTextColor);
        sqlquery.bindValue(":nTextColor",QVariant(ColorToInt(mColor)));
        mColor = pwnd->StringTOColor(meter_st.nDesignColor);
        sqlquery.bindValue(":nBackcolor",QVariant(ColorToInt(mColor)));

        sqlquery.bindValue(":nLeftTopX",QVariant(meter_st.nLeftTopX));
        sqlquery.bindValue(":nLeftTopY",QVariant(meter_st.nLeftTopY));

        sqlquery.bindValue(":nWidth",QVariant(meter_st.nWidth));
        sqlquery.bindValue(":nHeight",QVariant(meter_st.nHeight));

        sqlquery.bindValue(":nMainRuling",QVariant(meter_st.nMainScale));
        sqlquery.bindValue(":bShowRuling",QVariant(meter_st.nScaleMark));
        sqlquery.bindValue(":bShowRuleValue",QVariant(meter_st.bShowRuleValue));
        sqlquery.bindValue(":nPointTyp",QVariant(meter_st.nPointType + 1));
        sqlquery.bindValue(":nRuling",QVariant(meter_st.nSubScale));
        mColor = pwnd->StringTOColor(meter_st.nScaleColor);
        sqlquery.bindValue(":nRulingColor",QVariant(ColorToInt(mColor)));
        sqlquery.bindValue(":nShowLeftTopX",QVariant(meter_st.nShowLeftTopX));
        sqlquery.bindValue(":nShowLeftTopY",QVariant(meter_st.nShowLeftTopY));
        sqlquery.bindValue(":nShowWidth",QVariant(meter_st.nShowWidth));
        sqlquery.bindValue(":nShowHigth",QVariant(meter_st.nShowHigth));

        sqlquery.bindValue(":nRulerLeftTopX",QVariant(0));//标尺仪表不需要
        sqlquery.bindValue(":nRulerLeftTopY",QVariant(0));
        sqlquery.bindValue(":nRulerWidth",QVariant(meter_st.nScaleLength));
        sqlquery.bindValue(":nRulerHigth",QVariant(meter_st.nScaleLength));
        sqlquery.bindValue(":eRulerDirectio",QVariant(0));

        sqlquery.bindValue(":bAlarm",QVariant(meter_st.sAlarm.bAlarm));
        sqlquery.bindValue(":nType",QVariant(meter_st.sAlarm.nType));//

        if(1 == meter_st.sAlarm.nType)//如果报警为地址，保存地址
        {
            count++;
            int nId = count;
                        //修改地址编译参数
            stParams.id = count;
            stParams.itemId = nItemID;
            stParams.eType = OBJ_ITEM;
            stParams.addrNum = -1;
            meter_st.sAlarm.nMinaddr.compile(db,stParams);
            sqlquery.bindValue(":nMin",QVariant(nId));

            count++;
            nId = count;
                        //修改地址编译参数
            stParams.id = count;
            stParams.itemId = nItemID;
            stParams.eType = OBJ_ITEM;
            stParams.addrNum = -1;
            meter_st.sAlarm.nMaxaddr.compile(db,stParams);
            sqlquery.bindValue(":nMax",QVariant(nId));
        }
        else
        {
            sqlquery.bindValue(":nMin",QVariant(meter_st.sAlarm.nMin));
            sqlquery.bindValue(":nMax",QVariant(meter_st.sAlarm.nMax));
        }

        mColor = pwnd->StringTOColor(meter_st.sAlarm.nTextColor);
        sqlquery.bindValue(":nAlarmTextColor",QVariant(ColorToInt(mColor)));

        mColor = pwnd->StringTOColor(meter_st.sAlarm.nDesignColor);
        sqlquery.bindValue(":nDesignColor",QVariant(ColorToInt(mColor)));

        sqlquery.bindValue(":nZvalue",QVariant(zValue()));

        sqlquery.bindValue(":nCollidindId",QVariant(index));

        sqlquery.bindValue(":nShowPropId",QVariant(count));

        sqlquery.exec();

    }
    //在此添加编译权限页面属性代码
}

int ChartItem::GroupType()
{
    return SAM_DRAW_GROUP_CHART;
}
void ChartItem::save(QDataStream &stream)
{
    QVisableItem::save(stream);

    stream << (int)m_eGraphType;
    if(ENCOMMON_TYPE == m_eGraphType)
    {
        stream << (int)common_st.eGraphType;
        stream << (int)common_st.eShapeId;
        stream << common_st.mAddress;
        stream << common_st.addr;
        stream << common_st.addrSourceMax;
        stream << common_st.addrSourceMin;
        stream << common_st.eDataType;
        stream << common_st.nSourceRang;
        stream << (int)common_st.eDirection;
        stream << common_st.nTextColor;
        stream << common_st.nBackcolor;
        stream << common_st.nMainRuling;
        stream << common_st.bShowRuling;
        stream << common_st.bShowRuleValue;
        stream << common_st.nPointType;
        stream << common_st.nRuling;
        stream << common_st.nRulingColor;
        stream << (int)common_st.eRulerDirectio;
        stream << common_st.nScaleLength;
        stream << common_st.bSourceMark;
        stream << common_st.eSourceMin;
        stream << common_st.eSourceMax;
        stream << common_st.bShowMark;
        stream << common_st.eShowMin;
        stream << common_st.eShowMax;
        stream << (int)common_st.eShapeType;
        stream << common_st.bFill;
        stream << common_st.bHole;
        stream << common_st.nRadius;
        stream << common_st.bStart;
        stream << common_st.nDesign;
        stream << common_st.nDesignColor;
        stream << common_st.nFrameColor;
        stream << common_st.nScaleMark;
        stream << common_st.nMainScale;
        stream << common_st.nSubScale;

        stream << common_st.nCircle.FirstPos;
        stream << common_st.nCircle.SecondPos;
        stream << common_st.nCircle.num;
        stream << common_st.nCircle.FirstColor;
        stream << common_st.nCircle.SecondColor;
        stream << common_st.nCircle.ScaleColor;
        stream << common_st.nCircle.nstartAngle;
        stream << common_st.nCircle.nSpanAngle;
        stream << common_st.nCircle.nScaleStartAngle;
        stream << common_st.nCircle.nScaleSpanAngle;
        stream << common_st.nCircle.nMainScal;
        stream << common_st.nCircle.nSubScal;
        stream << common_st.nCircle.bPoint;
        stream << common_st.nCircle.nRadiu;

        stream << common_st.sAlarm.bAlarm;
        stream << common_st.sAlarm.nType;
        stream << common_st.sAlarm.nMin;
        stream << common_st.sAlarm.nMax;
        stream << common_st.sAlarm.nTextColor;
        stream << common_st.sAlarm.nDesignColor;
        stream << common_st.sAlarm.nMinaddr;
        stream << common_st.sAlarm.nMaxaddr;
        stream << common_st.nStartAngle;
        stream << common_st.nSpanAngle;

        stream << common_st.nTransparent;
        stream << common_st.bShowFrame;
    }
    else if(ENMETER_TYPE == m_eGraphType)
    {
        stream << (int)meter_st.eShapeId;
        stream << (int)meter_st.eDirection;
        stream << meter_st.mAddress;
        stream << meter_st.eDataType;
        stream << meter_st.nSourceMark;
        stream << meter_st.nSourceRang;
        stream << meter_st.eSourceMin;
        stream << meter_st.eSourceMax;
        stream << meter_st.bShowMark;
        stream << meter_st.eShowMin;
        stream << meter_st.eShowMax;
        stream << meter_st.bAlarm;
        stream << meter_st.nTextColor;
        stream << meter_st.nDesignColor;
        stream << meter_st.nScaleColor;
        stream << meter_st.nMainScale;
        stream << meter_st.nSubScale;
        stream << meter_st.nScaleLength;
        stream << meter_st.nScaleMark;
        stream << meter_st.bShowRuleValue;
        stream << meter_st.nPointType;
        stream << meter_st.nTransparent;
        stream << meter_st.nstartAngle;
        stream << meter_st.nSpanAngle;
        stream << meter_st.nPointStartAngle;
        stream << meter_st.nPointSpanAngel;
        stream << meter_st.sAlarm.bAlarm;
        stream << meter_st.sAlarm.nType;
        stream << meter_st.sAlarm.nMin;
        stream << meter_st.sAlarm.nMax;
        stream << meter_st.sAlarm.nTextColor;
        stream << meter_st.sAlarm.nDesignColor;
        stream << meter_st.sAlarm.nMinaddr;
        stream << meter_st.sAlarm.nMaxaddr;
        stream << meter_st.addr;
        stream << meter_st.addrSourceMax;
        stream << meter_st.addrSourceMin;

        stream << meter_st.bShowFrame;
    }
}
void ChartItem::load(QDataStream &stream)
{
    QVisableItem::load(stream);

    int nType = 0;
    stream >> nType;
    m_eGraphType = GRAPH_TYPE(nType);
    if(ENCOMMON_TYPE == m_eGraphType)
    {
        stream >> nType;
        common_st.eGraphType = GRAPH_TYPE(nType);
        stream >> nType;
        common_st.eShapeId = GRAPH_SHAPE(nType);
        stream >> common_st.mAddress;
        stream >> common_st.addr;
        stream >> common_st.addrSourceMax;
        stream >> common_st.addrSourceMin;
        stream >> common_st.eDataType;
        stream >> common_st.nSourceRang;
        stream >> nType;
        common_st.eDirection = DIRECTION(nType);
        stream >> common_st.nTextColor;
        stream >> common_st.nBackcolor;
        stream >> common_st.nMainRuling;
        stream >> common_st.bShowRuling;
        stream >> common_st.bShowRuleValue;
        stream >> common_st.nPointType;
        stream >> common_st.nRuling;
        stream >> common_st.nRulingColor;
        stream >> nType;
        common_st.eRulerDirectio = DIRECTION(nType);
        stream >> common_st.nScaleLength;
        stream >> common_st.bSourceMark;
        stream >> common_st.eSourceMin;
        stream >> common_st.eSourceMax;
        stream >> common_st.bShowMark;
        stream >> common_st.eShowMin;
        stream >> common_st.eShowMax;
        stream >> nType;
        common_st.eShapeType = SHAPE_TYPE(nType);
        stream >> common_st.bFill;
        stream >> common_st.bHole;
        stream >> common_st.nRadius;
        stream >> common_st.bStart;
        stream >> common_st.nDesign;
        stream >> common_st.nDesignColor;
        stream >> common_st.nFrameColor;
        stream >> common_st.nScaleMark;
        stream >> common_st.nMainScale;
        stream >> common_st.nSubScale;

        stream >> common_st.nCircle.FirstPos;
        stream >> common_st.nCircle.SecondPos;
        stream >> common_st.nCircle.num;
        stream >> common_st.nCircle.FirstColor;
        stream >> common_st.nCircle.SecondColor;
        stream >> common_st.nCircle.ScaleColor;
        stream >> common_st.nCircle.nstartAngle;
        stream >> common_st.nCircle.nSpanAngle;
        stream >> common_st.nCircle.nScaleStartAngle;
        stream >> common_st.nCircle.nScaleSpanAngle;
        stream >> common_st.nCircle.nMainScal;
        stream >> common_st.nCircle.nSubScal;
        stream >> common_st.nCircle.bPoint;
        stream >> common_st.nCircle.nRadiu;

        stream >> common_st.sAlarm.bAlarm;
        stream >> common_st.sAlarm.nType;
        stream >> common_st.sAlarm.nMin;
        stream >> common_st.sAlarm.nMax;
        stream >> common_st.sAlarm.nTextColor;
        stream >> common_st.sAlarm.nDesignColor;
        stream >> common_st.sAlarm.nMinaddr;
        stream >> common_st.sAlarm.nMaxaddr;
        if(pwnd->getProVersion() < 3020)
        {
            common_st.nStartAngle = 0;
            common_st.nSpanAngle = 360;
        }
        else
        {
            stream >> common_st.nStartAngle;
            stream >> common_st.nSpanAngle;
        }
        //add by wxy,这个地方还要兼容低版本
        if(pwnd->getProVersion() < 3098)
        {
            common_st.nTransparent = 255;
            common_st.bShowFrame = true;
        }
        else
        {
            stream >> common_st.nTransparent;
            stream >> common_st.bShowFrame;
        }
    }
    else if(ENMETER_TYPE == m_eGraphType)
    {
        stream >> nType;
        meter_st.eShapeId = GRAPH_SHAPE(nType);
        stream >> nType;
        meter_st.eDirection = DIRECTION(nType);
        stream >> meter_st.mAddress;
        stream >> meter_st.eDataType;
        stream >> meter_st.nSourceMark;
        stream >> meter_st.nSourceRang;
        stream >> meter_st.eSourceMin;
        stream >> meter_st.eSourceMax;
        stream >> meter_st.bShowMark;
        stream >> meter_st.eShowMin;
        stream >> meter_st.eShowMax;
        stream >> meter_st.bAlarm;
        stream >> meter_st.nTextColor;
        stream >> meter_st.nDesignColor;
        stream >> meter_st.nScaleColor;
        stream >> meter_st.nMainScale;
        stream >> meter_st.nSubScale;
        stream >> meter_st.nScaleLength;
        stream >> meter_st.nScaleMark;
        stream >> meter_st.bShowRuleValue;
        stream >> meter_st.nPointType;
        stream >> meter_st.nTransparent;
        stream >> meter_st.nstartAngle;
        stream >> meter_st.nSpanAngle;
        stream >> meter_st.nPointStartAngle;
        stream >> meter_st.nPointSpanAngel;
        stream >> meter_st.sAlarm.bAlarm;
        stream >> meter_st.sAlarm.nType;
        stream >> meter_st.sAlarm.nMin;
        stream >> meter_st.sAlarm.nMax;
        stream >> meter_st.sAlarm.nTextColor;
        stream >> meter_st.sAlarm.nDesignColor;
        stream >> meter_st.sAlarm.nMinaddr;
        stream >> meter_st.sAlarm.nMaxaddr;
        stream >> meter_st.addr;
        stream >> meter_st.addrSourceMax;
        stream >> meter_st.addrSourceMin;

        if(pwnd->getProVersion() < 3098)
        {
            meter_st.bShowFrame = true;
        }
        else
        {
            stream >> meter_st.bShowFrame;
        }
    }
}

void ChartItem::onSaveMeter(struct METER_INFORMATION meter)
{
    meter_st = meter;
    //保存仪表属性值
}

void ChartItem::onSaveCommon(struct COMMON_INFORMATION common)
{
    //保存普通图形属性值
    common_st = common;
}

void ChartItem::onGetPosition()
{
    QRectF oldpos = sceneBoundingRect();
    if(ENMETER_TYPE == m_eGraphType)
    {
        meter_st.nLeftTopX = oldpos.x() + 0.5;
        meter_st.nLeftTopY = oldpos.y() + 0.5;
        meter_st.nWidth = oldpos.width() + 0.5;
        meter_st.nHeight = oldpos.height() + 0.5;
        QList<QGraphicsItem *> ItemList;
        ItemList = childItems();
        foreach(QGraphicsItem *pItem,ItemList)
        {
            if(SAM_DRAW_OBJECT_ELIPSE == pItem->type())
            {
                oldpos = pItem->sceneBoundingRect();
                meter_st.nShowLeftTopX = oldpos.x() + 0.5;
                meter_st.nShowLeftTopY = oldpos.y() + 0.5;
                meter_st.nShowWidth = oldpos.width() + 0.5;
                meter_st.nShowHigth = oldpos.height() + 0.5;
                break;
            }
        }
        foreach(QGraphicsItem *pItem,childItems())
        {
            if(SAM_DRAW_OBJECT_GROUP == pItem->type())
            {
                foreach(QGraphicsItem *Item,pItem->childItems())
                {
                    QString str = Item->data(GROUP_NAME_KEY).toString();
                    if(SAM_DRAW_OBJECT_LINE == Item->type()
                        && str.contains("MainLineScal"))
                    {
                        oldpos = Item->boundingRect();
                        meter_st.nScaleLength = (oldpos.width() * oldpos.width())+(oldpos.height() * oldpos.height());
                        meter_st.nScaleLength = sqrt(meter_st.nScaleLength);
                        break;
                    }
                }
            }
        }
    }
    else
    {
        common_st.nLeftTopX = oldpos.x() + 0.5;
        common_st.nLeftTopY = oldpos.y() + 0.5;
        common_st.nWidth = oldpos.width() + 0.5;
        common_st.nHeight = oldpos.height() + 0.5;

        if(PILLA == common_st.eShapeType)//柱形
        {
            common_st.nShowLeftTopX = 0;
            common_st.nRulerLeftTopX = 0;
            QList<QGraphicsItem *> ItemList;
            ItemList = childItems();
            foreach(QGraphicsItem *pItem,ItemList)
            {
                if("ScaleItem" == pItem->data(GROUP_NAME_KEY).toString())
                {
                    oldpos = pItem->sceneBoundingRect();
                    qDebug()<<"rulerpos"<<oldpos;
                    common_st.nRulerLeftTopX = oldpos.x() + 0.5;
                    common_st.nRulerLeftTopY = oldpos.y() + 0.5;
                    common_st.nRulerWidth = oldpos.width() + 0.5;
                    common_st.nRulerHigth = oldpos.height() + 0.5;
                }
                if("FrameItem" == pItem->data(GROUP_NAME_KEY).toString())
                {
                    oldpos = pItem->sceneBoundingRect();
                    qDebug()<<"FrameItempos"<<oldpos;
                    common_st.nShowLeftTopX = oldpos.x() + 0.5;
                    common_st.nShowLeftTopY = oldpos.y() + 0.5;
                    common_st.nShowWidth = oldpos.width() + 0.5;
                    common_st.nShowHigth = oldpos.height() + 0.5;
                }
            }
        }
        if(GROOVE == common_st.eShapeType)//槽型
        {
            common_st.nShowLeftTopX = 0;
            common_st.nRulerLeftTopX = 0;
            QList<QGraphicsItem *> ItemList;
            ItemList = childItems();
            foreach(QGraphicsItem *pItem,ItemList)
            {
                if("ScaleItem" == pItem->data(GROUP_NAME_KEY).toString())
                {
                    oldpos = pItem->sceneBoundingRect();
                    common_st.nRulerLeftTopX = oldpos.x() + 0.5;
                    common_st.nRulerLeftTopY = oldpos.y() + 0.5;
                    common_st.nRulerWidth = oldpos.width() + 0.5;
                    common_st.nRulerHigth = oldpos.height() + 0.5;
                }
                if("HistogramItem" == pItem->data(GROUP_NAME_KEY).toString())
                {
                    oldpos = pItem->sceneBoundingRect();
                    common_st.nShowLeftTopX = oldpos.x() + 0.5;
                    common_st.nShowLeftTopY = oldpos.y() + 0.5;
                    common_st.nShowWidth = oldpos.width() + 0.5;
                    common_st.nShowHigth = oldpos.height() + 0.5;
                }
                common_st.eRulerDirectio = TOWARD_RIGHT;
            }
        }
        if(CIRCLE == common_st.eShapeType || SECTOR == common_st.eShapeType)
        {
            QList<QGraphicsItem *> ItemList;
            ItemList = childItems();
            foreach(QGraphicsItem *pItem,ItemList)
            {
                if(SAM_DRAW_OBJECT_ELIPSE == pItem->type()
                    && "mFirstCircle" == pItem->data(GROUP_NAME_KEY).toString())
                {
                    oldpos = pItem->sceneBoundingRect();
                    //QElipseItem *pCircle = dynamic_cast<QElipseItem *> (pItem);
                    common_st.nShowLeftTopX = oldpos.x() + 0.5;
                    common_st.nShowLeftTopY = oldpos.y() + 0.5;
                    common_st.nShowWidth = oldpos.width() + 0.5;
                    common_st.nShowHigth = oldpos.height() + 0.5;
                }
            }
        }
        foreach(QGraphicsItem *pItem,childItems())
        {
            if(SAM_DRAW_OBJECT_GROUP == pItem->type())
            {
                foreach(QGraphicsItem *Item,pItem->childItems())
                {
                    QString str = Item->data(GROUP_NAME_KEY).toString();
                    if(SAM_DRAW_OBJECT_LINE == Item->type()
                        && str.contains("MainLineScal"))
                    {
                        oldpos = Item->boundingRect();
                        common_st.nScaleLength = (oldpos.width() * oldpos.width())+(oldpos.height() * oldpos.height());
                        common_st.nScaleLength = sqrt(common_st.nScaleLength);
                        break;
                    }
                }
            }
            else
            {
                QString str = pItem->data(GROUP_NAME_KEY).toString();
                if(SAM_DRAW_OBJECT_LINE == pItem->type()
                    && str.contains("MainLineScal"))
                {
                    oldpos = pItem->boundingRect();
                    common_st.nScaleLength = (oldpos.width() * oldpos.width())+(oldpos.height() * oldpos.height());
                    common_st.nScaleLength = sqrt(common_st.nScaleLength);
                    break;
                }
            }
        }
    }

}

QString ChartItem::GetPicPath(ChartItem *libItem,SHAPE_TYPE nType,int nkey,DIRECTION derection)
{
    QString sPath;
    QGraphicsItem *pBackItem = NULL;

    if(PILLA == nType)//柱状
    {
        foreach(QGraphicsItem *pItem,libItem->childItems())
        {
            if("BackItem" == pItem->data(GROUP_NAME_KEY).toString())
            {
                pBackItem = pItem;
                break;
            }
        }

        if(!pBackItem)
        {
            return "";
        }

        sPath = "sheet2-";
        if(3 == nkey)
        {
            sPath = sPath + "1";
        }
        else if(6 == nkey)
        {
            sPath = sPath + "2";
        }
        else if(7 == nkey)
        {
            sPath = sPath + "3";
        }
        else if(8 == nkey)
        {
            sPath = sPath + "4";
        }
        else if(9 == nkey)
        {
            sPath = sPath + "5";
        }
        else if(10 == nkey)
        {
            sPath = sPath + "6";
        }
        else
        {
            return "";
        }
        sPath = sPath + QString::number(int(derection));
    }
    else if(GROOVE == nType)
    {
        foreach(QGraphicsItem *pItem,libItem->childItems())
        {
            if("Vector" == pItem->data(GROUP_NAME_KEY).toString())
            {
                pBackItem = pItem;
                break;
            }
        }

        if(!pBackItem)
        {
            return "";
        }
        sPath = "sheet1-";

        switch(nkey)
        {
        case 21:
            sPath = sPath + "14";
            break;
        case 41:
            sPath = sPath + "1";
            break;
        case 22:
            sPath = sPath + "15";//后面的数字在同一类型中不重复就行
            break;
        case 42:
            sPath = sPath + "2";
            break;
        case 23:
            sPath = sPath + "16";//后面的数字在同一类型中不重复就行
            break;
        case 43:
            sPath = sPath + "3";
            break;
        case 24:
            sPath = sPath + "17";//后面的数字在同一类型中不重复就行
            break;
        case 44:
            sPath = sPath + "4";
            break;
        case 25:
            sPath = sPath + "18";//后面的数字在同一类型中不重复就行
            break;
        case 26:
            sPath = sPath + "19";//后面的数字在同一类型中不重复就行
            break;
        case 27:
            sPath = sPath + "20";//后面的数字在同一类型中不重复就行
            break;
        case 28:
            sPath = sPath + "21";//后面的数字在同一类型中不重复就行
            break;
        case 33:
            sPath = sPath + "22";//后面的数字在同一类型中不重复就行
            break;
        case 36:
            sPath = sPath + "23";//后面的数字在同一类型中不重复就行
            break;
        case 39:
            sPath = sPath + "24";//后面的数字在同一类型中不重复就行
            break;
        case 40:
            sPath = sPath + "25";//后面的数字在同一类型中不重复就行
            break;
        case 45:
            sPath = sPath + "26";//后面的数字在同一类型中不重复就行
            break;
        case 46:
            sPath = sPath + "27";//后面的数字在同一类型中不重复就行
            break;
        case 47:
            sPath = sPath + "28";//后面的数字在同一类型中不重复就行
            break;
        case 48:
            sPath = sPath + "29";//后面的数字在同一类型中不重复就行
            break;
        case 53:
            sPath = sPath + "5";
            break;
        case 29:
            sPath = sPath + "30";//后面的数字在同一类型中不重复就行
            break;
        case 49:
            sPath = sPath + "6";
            break;
        case 30:
            sPath = sPath + "31";//后面的数字在同一类型中不重复就行
            break;
        case 50:
            sPath = sPath + "7";
            break;
        case 31:
            sPath = sPath + "32";//后面的数字在同一类型中不重复就行
            break;
        case 51:
            sPath = sPath + "8";
            break;
        case 32:
            sPath = sPath + "33";//后面的数字在同一类型中不重复就行
            break;
        case 52:
            sPath = sPath + "9";
            break;
        case 34:
            sPath = sPath + "34";//后面的数字在同一类型中不重复就行
            break;
        case 54:
            sPath = sPath + "10";
            break;
        case 35:
            sPath = sPath + "11";
            break;
        case 37:
            sPath = sPath + "12";
            break;
        case 38:
            sPath = sPath + "13";
            break;
        default:
            return "";
        }
        sPath = sPath + QString::number(int(derection));
    }
    else if(CIRCLE == nType || SECTOR == nType)
    {
        foreach(QGraphicsItem *pItem,libItem->childItems())
        {
            if("BackItem" == pItem->data(GROUP_NAME_KEY).toString())
            {
                pBackItem = pItem;
                break;
            }
        }

        if(!pBackItem)
        {
            return "";
        }
        sPath = "sheet3-";

        switch(nkey)
        {
        case 3:
            sPath = sPath + "5";
            break;
        case 4:
            sPath = sPath + "1";
            break;
        case 5:
            sPath = sPath + "6";
            break;
        case 6:
            sPath = sPath + "2";
            break;
        case 10:
            sPath = sPath + "7";
            break;
        case 11:
            sPath = sPath + "8";
            break;
        case 12:
            sPath = sPath + "3";
            break;
        case 13:
            sPath = sPath + "9";
            break;
        case 14:
            sPath = sPath + "10";
            break;
        case 15:
            sPath = sPath + "4";
            break;
        default:
            return "";
        }
    }
    else
    {
        return "";
    }
    return SaveLibPath(pBackItem,sPath,pBackItem->boundingRect().size());
}

QString ChartItem::SaveLibPath(QGraphicsItem *pItem,QString path,QSizeF size)
{
    QString date = QDateTime::currentDateTime().toString("yyMMddhhmmss");
    QString newPath;

    //从图库取得libItem并按照size进行缩放
    QGraphicsScene tmpScene;
    QGraphicsItem *libItem = NULL;
    DrawItemToScene dfun;
    dfun.CopyItemForChart(&libItem,pItem);

    if(!libItem)
    {
        qDebug() << "lib item not exist!: " << path;
        return "";
    }

    tmpScene.addItem(libItem);
    QGroupItem gfun(libItem);
    gfun.SetWidth(size.width());
    gfun.SetHeigth(size.height());

    //将item保存到pixmap
    QRectF rect = libItem->sceneBoundingRect();

    QPixmap pixmap(rect.width(),rect.height());
    pixmap.fill(QColor(0,0,0,0));
    QPainter painter(&pixmap);

    QRectF target = QRectF(0,0,rect.width(),rect.height());
    rect = QRectF(rect.x(),rect.y(),rect.width()+1,rect.height()+1);
    tmpScene.render(&painter,target,rect,Qt::IgnoreAspectRatio);

    //如果已经存在该item在mLibPath中，则比较大小，并判断是否需要重新保存
    if(pwnd->mLibPathInfo.mLibPath.contains(path))
    {
        QString sName = pwnd->mLibPathInfo.mLibPath.value(path);
        QString format = sName.section(".",-1);
        QByteArray ba = format.toLatin1();
        const char *fmt = ba.data();

        QSizeF sizeO = pwnd->mLibPathInfo.mLibSize.value(path);
        QImage img = pixmap.toImage();
        QSizeF newSize = pwnd->ScalePicture(sizeO,size,img.size());
        if(sizeO != newSize)
        {
            //重新缩放后保存图片

            if(!img.isNull())
            {
                img = img.scaled(QSize(newSize.width(),newSize.height()));
                img.save(sName,fmt);
            }
        }
        return sName;
    }
    //不存在该图片，分配文件名并保存图片，将path 插入mLibPath
    else
    {
        QImage picture = pixmap.toImage();
        QString newpath;
        QStringList list;
        int count;
        list<<"*.JPEG";
        list<<"*.gif";
        list<<"*.png";
        list<<"*.bmp";
        list<<"*.jpg";
        QString proName = "resource";
        QDir dir = QDir(proName);
        QString sName;
        if(!dir.exists())
        {
            dir.mkpath(dir.absolutePath());
        }
        count = dir.entryList(list).count();
        newpath = newpath.number(count);
        newpath = date+"_"+newpath;
        QString sTmp;
        sTmp = path.section(".",-1);


        //if(isCompiled && m_pSamSysParame->m_projectProp.nDownLoadPicCheck)
        {
           // sName = newpath+".JPEG";
           // newpath = proName+"/" +newpath+".JPEG";
        }
        //else
        {
            sName = newpath+"."+"PNG";
            newpath = proName+"/" +newpath+"."+"PNG";
        }
        long lWidth,lHeight;
        double dW,dH;
        double dScale = 1;
        lWidth = picture.width();
        dW = (double)lWidth/size.width();
        lHeight = picture.height();
        dH = (double)lHeight/size.height();
        dScale = dH>dW ? dH:dW;
        if (dScale>1)
        {
                picture = picture.scaled(lWidth/dScale,lHeight/dScale);
        }
        picture.save(newpath,"PNG");


        pwnd->mLibPathInfo.mLibPath.insert(path,newpath);
        pwnd->mLibPathInfo.mLibSize.insert(path,size.toSize());
        sName = newpath;
        return sName;
    }
}

//获得操作地址
QList<Keyboard> ChartItem::getAddress()
{
    QList<Keyboard> addrs;
    addrs.clear();
    if(ENCOMMON_TYPE == m_eGraphType)
    {
        addrs << common_st.addr;
    }
    else if(ENMETER_TYPE == m_eGraphType)
    {
        addrs << meter_st.addr;
    }
    return addrs;
}
//设置操作地址
void ChartItem::setAddress(QList<Keyboard> addr)
{
    if (addr.size() <= 0)
        return ;
    if(ENCOMMON_TYPE == m_eGraphType)
    {
        common_st.addr = addr.first();
        common_st.mAddress = common_st.addr.sShowAddr;
    }
    else if(ENMETER_TYPE == m_eGraphType)
    {
        meter_st.addr = addr.first();
        meter_st.mAddress = meter_st.addr.sShowAddr;
    }
}

QVector<ADDRPRO> ChartItem::getAllItemAddr()
{
    lsX.clear();
    ADDRPRO Addr;

    if(ENCOMMON_TYPE == m_eGraphType)
    {
        Addr.pAddr = &common_st.addr;
        Addr.str   = QObject::tr("图表监控字地址");
        Addr.type  = 1;
        lsX << Addr;

        if(1 == common_st.nSourceRang)
        {
            Addr.pAddr = &common_st.addrSourceMin;
            Addr.str   = QObject::tr("图表源范围最小值地址");
            Addr.type  = 1;
            lsX << Addr;

            Addr.pAddr = &common_st.addrSourceMax;
            Addr.str   = QObject::tr("图表源范围最大值地址");
            Addr.type  = 1;
            lsX << Addr;
        }

        if(1 == common_st.sAlarm.nType)//如果报警为地址，保存地址
        {
            Addr.pAddr = &common_st.sAlarm.nMinaddr;
            Addr.str   = QObject::tr("图表报警最小值地址");
            Addr.type  = 1;
            lsX << Addr;

            Addr.pAddr = &common_st.sAlarm.nMaxaddr;
            Addr.str   = QObject::tr("图表报警最大值地址");
            Addr.type  = 1;
            lsX << Addr;

        }
    }
    else if(ENMETER_TYPE == m_eGraphType)
    {
        Addr.pAddr = &meter_st.addr;
        Addr.str   = QObject::tr("图表监控字地址");
        Addr.type  = 1;
        lsX << Addr;

        if(1 == meter_st.nSourceRang)//如果选择源范围为地址，保存源范围地址
        {
            Addr.pAddr = &meter_st.addrSourceMin;
            Addr.str   = QObject::tr("图表源范围最小值地址");
            Addr.type  = 1;
            lsX << Addr;

            Addr.pAddr = &meter_st.addrSourceMax;
            Addr.str   = QObject::tr("图表源范围最大值地址");
            Addr.type  = 1;
            lsX << Addr;
        }

        if(1 == meter_st.sAlarm.nType)//如果报警为地址，保存地址
        {
            Addr.pAddr = &meter_st.sAlarm.nMinaddr;
            Addr.str   = QObject::tr("图表报警最小值地址");
            Addr.type  = 1;
            lsX << Addr;

            Addr.pAddr = &meter_st.sAlarm.nMaxaddr;
            Addr.str   = QObject::tr("图表报警最大值地址");
            Addr.type  = 1;
            lsX << Addr;
        }
    }

    QVector<ADDRPRO> AddrList;
    AddrList = QVisableItem::getAllItemAddr();
    for(int i = 0; i < AddrList.size(); i++)
    {
        Addr.pAddr = AddrList.at(i).pAddr;
        Addr.str   = QObject::tr("图表") + AddrList.at(i).str;
        Addr.type  = AddrList.at(i).type;
        lsX << Addr;
    }

    return lsX;
}

QString  ChartItem::getItemName()
{
    return QObject::tr("图表");
}

