#include "view/flowblockitem.h"
#include "flowblockitem.h"
#include "qpixmapitem.h"
#include "Frame/mainwindow.h"
#include "Frame/qprogectmanager.h"

extern MainWindow *pwnd;
FlowBlockItem::FlowBlockItem()
    :QVisableItem(0)
{

}

QString FlowBlockItem::getItemName()
{
    return QObject::tr("流动块");
}

int FlowBlockItem::GroupType()
{
    return SAM_DRAW_GROUP_FLOW;
}

QGraphicsItem *FlowBlockItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    FlowBlockItem *itemGroup = new FlowBlockItem();

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

    itemGroup->m_flow=m_flow;
    itemGroup->m_sproperty=m_sproperty;
    itemGroup->onSaveFlow(m_flow);
    itemGroup->SaveSecurityPro(&sPro);
    itemGroup->setId(id());

//    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }
    return itemGroup;

}

void FlowBlockItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    count++;
    QColor mColor;
    int triggerAddId;
    int touchAddId;
    int trendSpeedId;
    QVisableItem::compile(db,nSceneId,count,index);
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
    //触发地址
    count++;
    triggerAddId = count;
    ADDR_PARAMENTS stParams;
    stParams.id = count;
    stParams.itemId = itemId;
    stParams.eType = OBJ_ITEM;
    stParams.addrNum = -1;
    stParams.eRWtype = SCENE_CONTROL_LOOP_R;
    m_flow.triggerAdd.Length=1;
    m_flow.triggerAdd.compile(db,stParams);

    //触控地址
    if(m_flow.bTouchAddress){
        count++;
        touchAddId = count;
        stParams.id = count;
        stParams.eRWtype = SCENE_CONTROL_ONCE_W;
        m_flow.touchAdd.Length=1;
        m_flow.touchAdd.compile(db,stParams);
    }

    //动态速度地址
    if(m_flow.eFlowSpeedType==TRENDFLOWSPEED){
        count++;
        trendSpeedId = count;
        stParams.id = count;
        stParams.eRWtype = SCENE_CONTROL_ONCE_W;
        m_flow.trendSpeed.Length=1;
        m_flow.trendSpeed.compile(db,stParams);
    }

    //开关item表
    QSqlQuery sqlquery(db);
        bool flag=sqlquery.prepare("INSERT INTO floawBar(nItemId,nSceneId,nStartX,nStartY,nRectWidth,nRectHeight,"
                         "nFForeColor,nFBackColor,nDForeColor,nDBackColor,nFrameColor,eStyle,"
                         "nTriggerAddress,eShowWay,eFlowDirection,bTouchAddress,nTouchAddress,nFlowNum,"
                         "bSideLine,eFlowSpeedType,eFixedFlowSpeed,nTrendFlowSpeed,nZvalue,nCollidindId,nValidState)"
                         "VALUES(:nItemId,:nSceneId,:nStartX,:nStartY,:nRectWidth,:nRectHeight,"
                         ":nFForeColor,:nFBackColor,:nDForeColor,:nDBackColor,:nFrameColor,:eStyle,"
                         ":nTriggerAddress,:eShowWay,:eFlowDirection,:bTouchAddress,:nTouchAddress,:nFlowNum,"
                         ":bSideLine,:eFlowSpeedType,:eFixedFlowSpeed,:nTrendFlowSpeed,:nZvalue,:nCollidindId,:nValidState)");
        sqlquery.bindValue(":nItemId",QVariant(itemId));// 表 id
        sqlquery.bindValue(":nSceneId",QVariant(nSceneId));// scene id

        mColor = pwnd->StringTOColor(m_flow.nFForeColor);
        sqlquery.bindValue(":nFForeColor",QVariant(ColorToInt(mColor)));
        mColor = pwnd->StringTOColor(m_flow.nFBackColor);
        sqlquery.bindValue(":nFBackColor",QVariant(ColorToInt(mColor)));
        mColor = pwnd->StringTOColor(m_flow.nDForeColor);
        sqlquery.bindValue(":nDForeColor",QVariant(ColorToInt(mColor)));
        mColor = pwnd->StringTOColor(m_flow.nDBackColor);
        sqlquery.bindValue(":nDBackColor",QVariant(ColorToInt(mColor)));
        mColor = pwnd->StringTOColor(m_flow.nFrameColor);
        sqlquery.bindValue(":nFrameColor",QVariant(ColorToInt(mColor)));
        sqlquery.bindValue(":eStyle",QVariant(m_flow.eStyle+1));
        sqlquery.bindValue(":nTriggerAddress",QVariant(triggerAddId));

        sqlquery.bindValue(":eShowWay",QVariant(m_flow.eShowWay));
        short num;
        if(m_flow.sflowdirection==QDialog::tr("向上")){
            num=5;
        }else if(m_flow.sflowdirection==QDialog::tr("向下")){
            num=6;
        }else if(m_flow.sflowdirection==QDialog::tr("向左")){
            num=3;
        }else if(m_flow.sflowdirection==QDialog::tr("向右")){
            num=4;
        }
        sqlquery.bindValue(":eFlowDirection",QVariant(num));
        sqlquery.bindValue(":bTouchAddress",QVariant(m_flow.bTouchAddress));
        if(m_flow.bTouchAddress){
                sqlquery.bindValue(":nTouchAddress",QVariant(touchAddId));
            }else{
                sqlquery.bindValue(":nTouchAddress",QVariant(-1));
            }
        sqlquery.bindValue(":nValidState",QVariant(m_flow.nValidState));
        sqlquery.bindValue(":nFlowNum",QVariant(m_flow.nFlowNum));
        sqlquery.bindValue(":bSideLine",QVariant(m_flow.bSideLine));
        sqlquery.bindValue(":eFlowSpeedType",QVariant(m_flow.eFlowSpeedType));
        sqlquery.bindValue(":eFixedFlowSpeed",QVariant(m_flow.eFixedFlowSpeed));
        if(m_flow.eFlowSpeedType==TRENDFLOWSPEED){
                sqlquery.bindValue(":nTrendFlowSpeed",QVariant(trendSpeedId));
            }else{
                sqlquery.bindValue(":nTrendFlowSpeed",QVariant(-1));
            }
        sqlquery.bindValue(":nZvalue",QVariant(zValue()));
        sqlquery.bindValue(":nCollidindId",QVariant(index));
        //相对场景的坐标及高宽
        QRectF rect = sceneBoundingRect();
        sqlquery.bindValue(":nStartX", QVariant((short)rect.x()));//left
        sqlquery.bindValue(":nStartY", QVariant((short)rect.y()));//top
        sqlquery.bindValue(":nRectWidth", QVariant((short)rect.width()));//width
        sqlquery.bindValue(":nRectHeight", QVariant((short)rect.height()));//height
        flag=sqlquery.exec();
        int a;
    }

void FlowBlockItem::save(QDataStream &stream)
{
    QVisableItem::save(stream);
    int nTypes = 0;
    stream << m_flow.bTouchAddress;

    nTypes=int(m_flow.eFixedFlowSpeed);
    stream << nTypes;

    nTypes=int(m_flow.eFlowDirection);
    stream << nTypes;

    nTypes=int(m_flow.eFlowSpeedType);
    stream << nTypes;

    nTypes=int(m_flow.eShowWay);
    stream << nTypes;

    stream << m_flow.eStyle;
    stream << m_flow.eTouchAddress;
    stream << m_flow.id;
    stream << m_flow.nDBackColor;
    stream << m_flow.nDForeColor;
    stream << m_flow.nFBackColor;
    stream << m_flow.nFForeColor;
    stream << m_flow.nFlowNum;
    stream << m_flow.nFrameColor;
    stream << m_flow.nRectHeight;
    stream << m_flow.nRectWidth;
    stream << m_flow.nStartX;
    stream << m_flow.nStartY;
    stream << m_flow.nTrendFlowSpeed;
    stream << m_flow.nTriggerAddress;
    stream << m_flow.nValidState;
    stream << m_flow.sflowdirection;
    stream << m_flow.touchAdd;
    stream << m_flow.trendSpeed;
    stream << m_flow.triggerAdd;
    stream << m_flow.bSideLine;
    stream << m_flow.nZvalue;
    stream << m_flow.nCollidindId;
}
void FlowBlockItem::load(QDataStream &stream)
{
    QVisableItem::load(stream);
    int nType = 0;
    stream >> m_flow.bTouchAddress;
    stream >> nType;
    m_flow.eFixedFlowSpeed=SPEED(nType);
    stream >> nType;
    m_flow.eFlowDirection=DIRECTIONS(nType);
    stream >> nType;
    m_flow.eFlowSpeedType=SPEED(nType);
    stream >> nType;
    m_flow.eShowWay=DIRECTIONS(nType);

    stream >> m_flow.eStyle;
    stream >> m_flow.eTouchAddress;
    stream >> m_flow.id;
    stream >> m_flow.nDBackColor;
    stream >> m_flow.nDForeColor;
    stream >> m_flow.nFBackColor;
    stream >> m_flow.nFForeColor;
    stream >> m_flow.nFlowNum;
    stream >> m_flow.nFrameColor;
    stream >> m_flow.nRectHeight;
    stream >> m_flow.nRectWidth;
    stream >> m_flow.nStartX;
    stream >> m_flow.nStartY;
    stream >> m_flow.nTrendFlowSpeed;
    stream >> m_flow.nTriggerAddress;
    stream >> m_flow.nValidState;
    stream >> m_flow.sflowdirection;
    stream >> m_flow.touchAdd;
    stream >> m_flow.trendSpeed;
    stream >> m_flow.triggerAdd;
    stream >> m_flow.bSideLine;
    stream >> m_flow.nZvalue;
    stream >> m_flow.nCollidindId;
}

void FlowBlockItem::onSaveFlow(FlowInfo flow_st)    //保存流动块显示信息
{
    m_flow = flow_st;
}

void FlowBlockItem::onSecurityPro(securityPro sproperty){
    m_sproperty=sproperty;
}

//获得操作地址
QList<Keyboard> FlowBlockItem::getAddress()
{
    QList<Keyboard> addrs;
    addrs << m_flow.trendSpeed;
    return addrs;
}
//设置操作地址
void FlowBlockItem::setAddress(QList<Keyboard> addr)
{
    if (addr.size() <= 0)
        return ;
    m_flow.trendSpeed=addr.first();
    m_flow.nTriggerAddress=m_flow.trendSpeed.sShowAddr;
}
//查找地址函数
QVector<ADDRPRO> FlowBlockItem::getAllItemAddr()
{
    addrs.clear();
    ADDRPRO temp;

    temp.pAddr = &m_flow.triggerAdd;
    temp.str   = QObject::tr("流动块--触发地址");
    temp.type  = 0;
    addrs << temp;

    if(m_flow.bTouchAddress){
        temp.pAddr = &m_flow.touchAdd;
        temp.str   = QObject::tr("流动块--触控地址");
        temp.type  = 0;
        addrs << temp;
    }

    if(m_flow.eFlowSpeedType==2){
        temp.pAddr = &m_flow.trendSpeed;
        temp.str   = QObject::tr("流动块--动态流动速度地址");
        temp.type  = 1;
        addrs << temp;
    }

    QVector<ADDRPRO> AddrList;
    AddrList = QVisableItem::getAllItemAddr();
    for(int i = 0; i < AddrList.size(); i++)
    {
        temp.pAddr = AddrList.at(i).pAddr;
        temp.str = QObject::tr("流动块--权限地址");
        temp.type  = AddrList.at(i).type;
        addrs << temp;
    }

    return addrs;
}
