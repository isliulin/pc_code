#include "xytrend.h"

extern MainWindow *pwnd;

XYtrend::XYtrend(QGraphicsItem *parent):QVisableItem(parent)//QItemGroup(parent)//
{

}

XYtrend::~XYtrend()
{

}

int XYtrend::GroupType()//控件类型 趋势图
{
    //return GROUP_TYPE_TRENDCHART;
    return SAM_DRAW_GROUP_XYTREND;
}

XYtrend* XYtrend::Clone()//复制item
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
    itemGroup->m_bIsAll        = m_bIsAll;
    itemGroup->chlCount        = chlCount;//通道总数
    itemGroup->addrLength      = addrLength;//地址长度，相当于采样点数
    itemGroup->m_dataType      = m_dataType;//数据类型
    itemGroup->m_TriggerAddr   = m_TriggerAddr;//触发地址
    itemGroup->m_bReset        = m_bReset;//是否自动复位

    itemGroup->m_bScale        = m_bScale;//是否缩放

    itemGroup->m_bDisplayConst  = m_bDisplayConst;
    itemGroup->m_DisplayMaxAddrX= m_DisplayMaxAddrX;
    itemGroup->m_DisplayMinAddrX= m_DisplayMinAddrX;

    itemGroup->m_nDisplayMinX   = m_nDisplayMinX;	//显示最小值
    itemGroup->m_nDisplayMaxX   = m_nDisplayMaxX;	//显示最大值
    itemGroup->m_bConstX        = m_bConstX;//是否常量范围
    itemGroup->m_SourceMaxAddrX = m_SourceMaxAddrX;//源范围最大值 地址
    itemGroup->m_SourceMinAddrX = m_SourceMinAddrX;//源范围最小值 地址
    itemGroup->m_nSourceMaxX    = m_nSourceMaxX;	//源范围最大值
    itemGroup->m_nSourceMinX    = m_nSourceMinX;	//源范围最小值

    itemGroup->m_bDisplayConstY  = m_bDisplayConstY;
    itemGroup->m_DisplayMaxAddrY= m_DisplayMaxAddrY;
    itemGroup->m_DisplayMinAddrY= m_DisplayMinAddrY;
    itemGroup->m_nDisplayMinY   = m_nDisplayMinY;	//显示最小值
    itemGroup->m_nDisplayMaxY   = m_nDisplayMaxY;	//显示最大值
    itemGroup->m_bConstY        = m_bConstY;//是否常量范围
    itemGroup->m_SourceMaxAddrY = m_SourceMaxAddrY;//源范围最大值 地址
    itemGroup->m_SourceMinAddrY = m_SourceMinAddrY;//源范围最小值 地址
    itemGroup->m_nSourceMaxY    = m_nSourceMaxY;	//源范围最大值
    itemGroup->m_nSourceMinY    = m_nSourceMinY;	//源范围最小值

    itemGroup->m_vecChannels   = m_vecChannels;//各个通道曲线外观设置

    //曲线显示区设置
    itemGroup->m_bSelectVertMinor  = m_bSelectVertMinor;  //是否显示垂直次标尺
    itemGroup->m_bSelectHorMinor   = m_bSelectHorMinor;   //是否显示水平次标尺
    itemGroup->m_bMainHor          = m_bMainHor;
    itemGroup->m_bMainVer          = m_bMainVer;
    itemGroup->m_TextColor         = m_TextColor;
    itemGroup->m_textSize          = m_textSize;
    itemGroup->m_nVertMajorScale   = m_nVertMajorScale;   //垂直主标尺
    itemGroup->m_nVertMinorScale   = m_nVertMinorScale;   //垂直次标尺
    itemGroup->m_nHorMajorScale    = m_nHorMajorScale;    //水平主标尺
    itemGroup->m_nHorMinorScale    = m_nHorMinorScale;    //水平次标尺

    //曲线颜色设置
    itemGroup->m_bGrade      = m_bGrade;       //是否需要网格
    itemGroup->m_nVerColor   = m_nVerColor;    //垂直网格颜色
    itemGroup->m_nHorColor   = m_nHorColor;    //水平网格颜色
    itemGroup->m_nBoradColor = m_nBoradColor;	//边框颜色
    itemGroup->m_nScaleColor = m_nScaleColor;	//标尺颜色
    itemGroup->m_nGraphColor = m_nGraphColor;	//图表区颜色
    itemGroup->m_alpha       = m_alpha;	//图表区透明度


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

void XYtrend::compile(QSqlDatabase &db, int nSceneId, int &count, int index)//编译的时候保存item到数据库
{
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
    sqlquery.bindValue(":nItemId", QVariant(itemId));                //表id
    sqlquery.bindValue(":nSceneId", QVariant(nSceneId));            //scene id

    QRectF rect = sceneBoundingRect();//相对场景的坐标及高宽
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


    sqlquery.bindValue(":nAddrLength", QVariant(addrLength));     //点数
    sqlquery.bindValue(":nChannelNum", QVariant(chlCount));     //通道数
    count++;
    ADDR_PARAMENTS stParams;
    stParams.id         = count;
    stParams.itemId     = itemId;
    stParams.eType      = OBJ_ITEM;
    stParams.eRWtype    = SCENE_CONTROL_LOOP_R;
    stParams.addrNum    = -1;
    m_TriggerAddr.compile(db,stParams);
    sqlquery.bindValue(":nTrigAddr", QVariant(count));     //触发地址
    sqlquery.bindValue(":bAutoReset", QVariant(m_bReset));     //是否自动复位
    short datatype = m_dataType + 2 ;
    sqlquery.bindValue(":eDataType", QVariant(datatype));     //数据类型

    sqlquery.bindValue(":bDisplayConst", QVariant(m_bDisplayConst+1));     //是否为常量
    if(!m_bDisplayConst)//常量
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
    else//地址
    {
        sqlquery.bindValue(":nDisplayMaxX", QVariant(m_nDisplayMaxX));
        sqlquery.bindValue(":nDisplayMinX", QVariant(m_nDisplayMinX));
    }
    sqlquery.bindValue(":bDisplayConstY", QVariant(m_bDisplayConstY+1));     //是否为常量
    if(!m_bDisplayConstY)//常量
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
    else//地址
    {
        sqlquery.bindValue(":nDisplayMaxY", QVariant(m_nDisplayMaxY));
        sqlquery.bindValue(":nDisplayMinY", QVariant(m_nDisplayMinY));
    }

    sqlquery.bindValue(":bScale", QVariant(m_bScale));     //是否缩放
    if(m_bScale)//缩放
    {
        sqlquery.bindValue(":eNumberTypeX", QVariant(m_bConstX+1));     //是否为常量
        if(!m_bConstX)//常量
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
        else//地址
        {
            sqlquery.bindValue(":nSourceMaxX", QVariant(m_nSourceMaxX));
            sqlquery.bindValue(":nSourceMinX", QVariant(m_nSourceMinX));
        }
        sqlquery.bindValue(":eNumberTypeY", QVariant(m_bConstY+1));     //是否为常量
        if(!m_bConstY)//常量
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
        else//地址
        {
            sqlquery.bindValue(":nSourceMaxY", QVariant(m_nSourceMaxY));
            sqlquery.bindValue(":nSourceMinY", QVariant(m_nSourceMinY));
        }
    }
    sqlquery.bindValue(":nVertMajorScale", QVariant(m_nVertMajorScale)); //垂直主标尺
    sqlquery.bindValue(":bMainVer", QVariant(m_bMainVer)); //是否垂直主标尺
    sqlquery.bindValue(":bSelectVertMinor", QVariant(m_bSelectVertMinor));//是否显示垂直次标尺
    sqlquery.bindValue(":nVertMinorScale", QVariant(m_nVertMinorScale)); //垂直次标尺
    sqlquery.bindValue(":bMainHor", QVariant(m_bMainHor)); //是否垂直主标尺
    sqlquery.bindValue(":nHorMajorScale", QVariant(m_nHorMajorScale));  //水平主标尺
    sqlquery.bindValue(":bSelectHorMinor", QVariant(m_bSelectHorMinor)); //是否显示水平次标尺
    sqlquery.bindValue(":nHorMinorScale", QVariant(m_nHorMinorScale));  //水平次标尺

    sqlquery.bindValue(":bSelectNet", QVariant(m_bGrade));  //是否需要网格
    ck = ColorToInt(m_nVerColor);
    sqlquery.bindValue(":nVertNetColor", QVariant(ck));  //水平网格颜色
    ck = ColorToInt(m_nHorColor);
    sqlquery.bindValue(":nHorNetColor", QVariant(ck));  //垂直网格颜色
    ck = ColorToInt(m_nBoradColor);
    sqlquery.bindValue(":nBoradColor", QVariant(ck));      //边框颜色
    ck = ColorToInt(m_nScaleColor);
    sqlquery.bindValue(":nScaleColor", QVariant(ck));      //标尺颜色
    ck = ColorToInt(m_nGraphColor);
    sqlquery.bindValue(":nGraphColor", QVariant(ck));      //图表区颜色

    sqlquery.bindValue(":nFontSize", QVariant(m_textSize));    //字体大小
    sqlquery.bindValue(":nMarkColor", QVariant(ColorToInt(m_TextColor)));//标注颜色

    sqlquery.bindValue(":nZvalue", QVariant(zValue()));      //Z序
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

        sqlquery.bindValue(":nItemId", QVariant(itemId));             //表id
        count++;
        stParams.id         = count;
        stParams.addrNum    = i;
        info.m_AddrX.compile(db,stParams);
        sqlquery.bindValue(":nStartAddrX", QVariant(count));
        count++;
        stParams.id         = count;
        info.m_AddrY.compile(db,stParams);
        sqlquery.bindValue(":nStartAddrY", QVariant(count));
        sqlquery.bindValue(":nNumOfChannel", QVariant(info.m_nNumOfChannel));      //通道号

        sqlquery.bindValue(":nDisplayCondition", QVariant(info.eDisplayCondition));      //显示条件

        count++;
        stParams.id         = count;
        info.KeyAddr.compile(db,stParams);
        sqlquery.bindValue(":nDisplayAddr", QVariant(count));//显示ON/OFF地址

        sqlquery.bindValue(":nLineType", QVariant(info.eLineType));      //线型
        sqlquery.bindValue(":nLineThickness", QVariant(info.nLineThickness));      //线条宽度
        ck = ColorToInt(info.nDisplayColor);
        sqlquery.bindValue(":nDisplayColor", QVariant(ck));      //显示颜色

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "-------------insert nDisplayColor table :" << result << endl;
    }


}

void XYtrend::save(QDataStream &stream)//将item存入数据流
{
    QVisableItem::save(stream);
    //QItemGroup::save(stream);

    stream <<  m_bIsAll;
    stream <<  chlCount;//通道总数
    stream <<  addrLength;//地址长度，相当于采样点数
    stream <<  (int)m_dataType;//数据类型
    stream <<  m_TriggerAddr;//触发地址
    stream <<  m_bReset;//是否自动复位

    stream <<  m_bScale;//是否缩放

    stream <<  m_bDisplayConst;
    stream <<  m_DisplayMaxAddrX;
    stream <<  m_DisplayMinAddrX;
    stream <<  m_nDisplayMinX;	//显示最小值
    stream <<  m_nDisplayMaxX;	//显示最大值
    stream <<  m_bConstX;//是否常量范围
    stream <<  m_SourceMaxAddrX;//源范围最大值 地址
    stream <<  m_SourceMinAddrX;//源范围最小值 地址
    stream <<  m_nSourceMaxX;	//源范围最大值
    stream <<  m_nSourceMinX;	//源范围最小值

    stream <<  m_bDisplayConstY;
    stream <<  m_DisplayMaxAddrY;
    stream <<  m_DisplayMinAddrY;
    stream <<  m_nDisplayMinY;	//显示最小值
    stream <<  m_nDisplayMaxY;	//显示最大值
    stream <<  m_bConstY;//是否常量范围
    stream <<  m_SourceMaxAddrY;//源范围最大值 地址
    stream <<  m_SourceMinAddrY;//源范围最小值 地址
    stream <<  m_nSourceMaxY;	//源范围最大值
    stream <<  m_nSourceMinY;	//源范围最小值

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

    //曲线显示区设置
    stream <<  m_bSelectVertMinor;  //是否显示垂直次标尺
    stream <<  m_bSelectHorMinor;   //是否显示水平次标尺
    stream <<  m_bMainHor;
    stream <<  m_bMainVer;
    stream <<  m_TextColor;
    stream <<  m_textSize;
    stream <<  m_nVertMajorScale;   //垂直主标尺
    stream <<  m_nVertMinorScale;   //垂直次标尺
    stream <<  m_nHorMajorScale;    //水平主标尺
    stream <<  m_nHorMinorScale;    //水平次标尺

    //曲线颜色设置
    stream <<  m_bGrade;       //是否需要网格
    stream <<  m_nVerColor;    //垂直网格颜色
    stream <<  m_nHorColor;    //水平网格颜色
    stream <<  m_nBoradColor;	//边框颜色
    stream <<  m_nScaleColor;	//标尺颜色
    stream <<  m_nGraphColor;	//图表区颜色
    stream <<  m_alpha;	//图表区透明度


}

void XYtrend::load(QDataStream &stream)//从数据流导出item
{
    int temp;
    QVisableItem::load(stream);
    //QItemGroup::load(stream);

    stream >>  m_bIsAll;
    stream >>  chlCount;//通道总数
    stream >>  addrLength;//地址长度，相当于采样点数
    stream >>  temp;
    m_dataType = (DATA_TYPE)temp;//数据类型
    stream >>  m_TriggerAddr;//触发地址
    stream >>  m_bReset;//是否自动复位

    stream >>  m_bScale;//是否缩放

    stream >>  m_bDisplayConst;
    stream >>  m_DisplayMaxAddrX;
    stream >>  m_DisplayMinAddrX;
    stream >>  m_nDisplayMinX;	//显示最小值
    stream >>  m_nDisplayMaxX;	//显示最大值
    stream >>  m_bConstX;//是否常量范围
    stream >>  m_SourceMaxAddrX;//源范围最大值 地址
    stream >>  m_SourceMinAddrX;//源范围最小值 地址
    stream >>  m_nSourceMaxX;	//源范围最大值
    stream >>  m_nSourceMinX;	//源范围最小值

    stream >>  m_bDisplayConstY;
    stream >>  m_DisplayMaxAddrY;
    stream >>  m_DisplayMinAddrY;
    stream >>  m_nDisplayMinY;	//显示最小值
    stream >>  m_nDisplayMaxY;	//显示最大值
    stream >>  m_bConstY;//是否常量范围
    stream >>  m_SourceMaxAddrY;//源范围最大值 地址
    stream >>  m_SourceMinAddrY;//源范围最小值 地址
    stream >>  m_nSourceMaxY;	//源范围最大值
    stream >>  m_nSourceMinY;	//源范围最小值

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

    //曲线显示区设置
    stream >>  m_bSelectVertMinor;  //是否显示垂直次标尺
    stream >>  m_bSelectHorMinor;   //是否显示水平次标尺
    stream >>  m_bMainHor;
    stream >>  m_bMainVer;
    stream >>  m_TextColor;
    stream >>  m_textSize;
    stream >>  m_nVertMajorScale;   //垂直主标尺
    stream >>  m_nVertMinorScale;   //垂直次标尺
    stream >>  m_nHorMajorScale;    //水平主标尺
    stream >>  m_nHorMinorScale;    //水平次标尺

    //曲线颜色设置
    stream >>  m_bGrade;       //是否需要网格
    stream >>  m_nVerColor;    //垂直网格颜色
    stream >>  m_nHorColor;    //水平网格颜色
    stream >>  m_nBoradColor;	//边框颜色
    stream >>  m_nScaleColor;	//标尺颜色
    stream >>  m_nGraphColor;	//图表区颜色
    stream >>  m_alpha;	//图表区透明度



}

QVector<ADDRPRO> XYtrend::getAllItemAddr()
{
    kb.clear();
    kb = QVisableItem::getAllItemAddr();

    ADDRPRO addrPro;

    addrPro.pAddr = &m_TriggerAddr;
    addrPro.str   = QObject::tr("X-Y曲线刷新触发地址");
    addrPro.type  = 0;
    kb << addrPro;

    if(m_bScale)//缩放
    {
        if(!m_bConstX)
        {
            addrPro.pAddr = &m_SourceMaxAddrX;
            addrPro.str   = QObject::tr("X轴源范围最大值地址");
            addrPro.type  = 1;
            kb << addrPro;
            addrPro.pAddr = &m_SourceMinAddrX;
            addrPro.str   = QObject::tr("X轴源范围最小值地址");
            kb << addrPro;
        }
        if(!m_bConstY)
        {
            addrPro.pAddr = &m_SourceMaxAddrY;
            addrPro.str   = QObject::tr("Y轴源范围最大值地址");
            addrPro.type  = 1;
            kb << addrPro;
            addrPro.pAddr = &m_SourceMinAddrY;
            addrPro.str   = QObject::tr("Y轴源范围最小值地址");
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
            addrPro.str   = QObject::tr("通道")+QString::number(m_vecChannels[i].m_nNumOfChannel)+QObject::tr("控制地址");
            addrPro.type  = 0;
            kb << addrPro;
        }
        addrPro.pAddr = &m_vecChannels[i].m_AddrX;
        addrPro.str   = QObject::tr("通道")+QString::number(m_vecChannels[i].m_nNumOfChannel)+QObject::tr("X轴起始地址");
        addrPro.type  = 1;
        kb << addrPro;
        addrPro.pAddr = &m_vecChannels[i].m_AddrY;
        addrPro.str   = QObject::tr("通道")+QString::number(m_vecChannels[i].m_nNumOfChannel)+QObject::tr("Y轴起始地址");
        kb << addrPro;
    }
    return kb;
}

QString  XYtrend::getItemName()
{
    return QObject::tr("X-Y曲线");
}


