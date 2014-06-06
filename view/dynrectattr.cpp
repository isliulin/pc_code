#include "dynrectattr.h"

DynRectAttr::DynRectAttr(QGraphicsItem *parent):QVisableItem(parent)//QItemGroup(parent)//
{
    frameRect = NULL;
    /*QRectF rect = QRectF(0,0,100,100);
    frameRect = new QRectItem(rect);
    frameRect->SetBackColor(m_nFillColor);
    if(m_bFrameColor)
    {
        frameRect->SetLineColor(m_nFrameColor);
        frameRect->SetLineType(1);
        frameRect->SetLineWidth(1);
    }
    else
    {
        frameRect->SetLineColor(m_nFillColor);
        //frameRect->SetLineType(0);
    }
    addToGroup(frameRect);*/
}

QString DynRectAttr::getItemName()
{
    return QObject::tr("动态矩形");
}

void DynRectAttr::resetRect(short alpha, QColor mBkColor, QColor mFrmColor, bool bBack, bool bFrame)
{
    if(frameRect)
    {
        delete frameRect;
        frameRect = NULL;
    }

    QRectF rect = QRectF(0,0,100,100);
    frameRect = new QRectItem(rect);
    frameRect->SetBackColor(mBkColor);
    if(bBack)
    {
        frameRect->SetPattern(1);
        frameRect->SetBackColor(mBkColor);
    }
    else
    {
        frameRect->SetPattern(0);
    }
    frameRect->SetAlpha(alpha);

    if(bFrame)
    {
        frameRect->SetLineType(1);
        frameRect->SetLineWidth(1);
        frameRect->SetLineColor(mFrmColor);
    }
    else
    {
        frameRect->SetLineType(0);
    }

    addToGroup(frameRect);
}

DynRectAttr::~DynRectAttr()
{
}

int DynRectAttr::GroupType()                //控件类型 位开关 字开关
{
    return SAM_DRAW_GROUP_DYNRECT;
}

DynRectAttr* DynRectAttr::Clone()           //复制item
{
    QGraphicsItem* pCopy = NULL;
    QGraphicsItem* pItem = NULL;

    DynRectAttr *itemGroup = new DynRectAttr;

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

    itemGroup->m_bFillColor     = m_bFillColor;
    itemGroup->m_nFillColor     = m_nFillColor;
    itemGroup->m_bFrameColor    = m_bFrameColor;
    itemGroup->m_nFrameColor    = m_nFrameColor;
    itemGroup->m_nFrameWidth    = m_nFrameWidth;
    itemGroup->m_nAlpha         = m_nAlpha;
    itemGroup->m_nBeginX        = m_nBeginX;
    itemGroup->m_nBeginY        = m_nBeginY;
    itemGroup->m_nWidth         = m_nWidth;
    itemGroup->m_nHeight        = m_nHeight;
    itemGroup->m_nBgColor       = m_nBgColor;
    itemGroup->m_bPosCtrl       = m_bPosCtrl;
    itemGroup->m_addrH          = m_addrH;
    itemGroup->m_addrV          = m_addrV;
    itemGroup->m_bSizeCtrl      = m_bSizeCtrl;
    itemGroup->m_nRefType       = m_nRefType;//固定点
    itemGroup->m_addrWidth      = m_addrWidth;
    itemGroup->m_addrHeight     = m_addrHeight;
    itemGroup->setId(id());

    return itemGroup;
}

void DynRectAttr::compile(QSqlDatabase &db, int nSceneId, int &count, int index)//编译的时候保存item到数据库
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

    QSqlQuery sqlquery(db);
    bool result = sqlquery.prepare("INSERT INTO dynamicRect(nItemId,nSceneId,nAlpha,"
                       "nXPos,nYPos,nWidth,nHeight,nFillColor,nUseFill,nRimColor,"
                       "nRimWidth,mXDataAddr,mYDataAddr,nUsePosCtrl,nRefType,mWDataAddr,"
                       "mHDataAddr,nUseSizeCtrl,nAreaLp,nAreaTp,nAreaWidth,nAreaHeight,"
                       "nAreaColor,nZvalue,nCollidindId,nShowPropId)"
                       "VALUES(:nItemId,:nSceneId,:nAlpha,"
                       ":nXPos,:nYPos,:nWidth,:nHeight,:nFillColor,:nUseFill,:nRimColor,"
                       ":nRimWidth,:mXDataAddr,:mYDataAddr,:nUsePosCtrl,:nRefType,:mWDataAddr,"
                       ":mHDataAddr,:nUseSizeCtrl,:nAreaLp,:nAreaTp,:nAreaWidth,:nAreaHeight,"
                       ":nAreaColor,:nZvalue,:nCollidindId,:nShowPropId)");

    qDebug() << result;

    int num  = count;
    int temp;
    sqlquery.bindValue(":nItemId", QVariant(itemId));                //表id
    sqlquery.bindValue(":nSceneId", QVariant(nSceneId));            //scene id
    sqlquery.bindValue(":nAlpha", QVariant(m_nAlpha));            //scene id

    QRectF rect = sceneBoundingRect();//相对场景的坐标及高宽
    if(0 == m_nRefType)//左上
    {
        sqlquery.bindValue(":nXPos", QVariant((short)rect.left()));//left
        sqlquery.bindValue(":nYPos", QVariant((short)rect.top()));//top
    }
    else if(1 == m_nRefType)//右上
    {
        sqlquery.bindValue(":nXPos", QVariant((short)rect.left() + (short)rect.width()));//left
        sqlquery.bindValue(":nYPos", QVariant((short)rect.top()));//top
    }
    else if(2 == m_nRefType)//右下
    {
        sqlquery.bindValue(":nXPos", QVariant((short)rect.left() + (short)rect.width()));//left
        sqlquery.bindValue(":nYPos", QVariant((short)rect.top() + (short)rect.height()));//top
    }
    else//左下
    {
        sqlquery.bindValue(":nXPos", QVariant((short)rect.left()));//left
        sqlquery.bindValue(":nYPos", QVariant((short)rect.top() + (short)rect.height()));//top
    }
    sqlquery.bindValue(":nWidth", QVariant((short)rect.width()));//width
    sqlquery.bindValue(":nHeight", QVariant((short)rect.height()));//height

    temp =ColorToInt(m_nFillColor);
    sqlquery.bindValue(":nFillColor", QVariant(temp));//
    if(m_bFillColor)
    {
        sqlquery.bindValue(":nUseFill", QVariant(1));//
    }
    else
    {
        sqlquery.bindValue(":nUseFill", QVariant(0));//
    }
    temp =ColorToInt(m_nFrameColor);
    sqlquery.bindValue(":nRimColor", QVariant(temp));//
    sqlquery.bindValue(":nRimWidth", QVariant(m_nFrameWidth));//
    if(m_bPosCtrl)//位置控制开
    {
        sqlquery.bindValue(":nUsePosCtrl", QVariant(1));//
        num++;
        sqlquery.bindValue(":mXDataAddr", QVariant(num));//
        num++;
        sqlquery.bindValue(":mYDataAddr", QVariant(num));//
    }
    else
    {
        sqlquery.bindValue(":nUsePosCtrl", QVariant(0));//
        sqlquery.bindValue(":mXDataAddr", QVariant(0));//
        sqlquery.bindValue(":mYDataAddr", QVariant(0));//
    }

    sqlquery.bindValue(":nRefType", QVariant(m_nRefType));//

    if(m_bSizeCtrl)
    {
        sqlquery.bindValue(":nUseSizeCtrl", QVariant(1));//
        num++;
        sqlquery.bindValue(":mWDataAddr", QVariant(num));//
        num++;
        sqlquery.bindValue(":mHDataAddr", QVariant(num));//
    }
    else
    {
        sqlquery.bindValue(":nUseSizeCtrl", QVariant(0));//
        sqlquery.bindValue(":mWDataAddr", QVariant(0));//
        sqlquery.bindValue(":mHDataAddr", QVariant(0));//
    }
    sqlquery.bindValue(":nAreaLp", QVariant(m_nBeginX));//
    sqlquery.bindValue(":nAreaTp", QVariant(m_nBeginY));//
    sqlquery.bindValue(":nAreaWidth", QVariant(m_nWidth));//
    sqlquery.bindValue(":nAreaHeight", QVariant(m_nHeight));//
    temp = ColorToInt(m_nBgColor);
    sqlquery.bindValue(":nAreaColor", QVariant(temp));//
    sqlquery.bindValue(":nZvalue", QVariant(zValue()));//
    sqlquery.bindValue(":nCollidindId", QVariant(index));//
    sqlquery.bindValue(":nShowPropId", QVariant(0));//

    bool result1 = false;
    result1 = sqlquery.exec();
    qDebug() << result1 << endl;

    int id = count;

    if(m_bPosCtrl)//位置控制开
    {
        count++;
        //修改地址编译参数
        ADDR_PARAMENTS stParams;
        stParams.id         = count;
        stParams.itemId     = itemId;
        stParams.eType      = OBJ_ITEM;
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
        stParams.addrNum    = -1;
        m_addrH.compile(db, stParams);
        //m_addrH.compile(db, count, 0, OBJ_ITEM);
        //sqlquery.exec();

        count++;
        //修改地址编译参数
        stParams.id         = count;
        stParams.itemId     = itemId;
        stParams.eType      = OBJ_ITEM;
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
        stParams.addrNum    = -1;
        m_addrV.compile(db, stParams);
        //m_addrV.compile(db, count, 0, OBJ_ITEM);
    }

    if(m_bSizeCtrl)
    {
        count++;
        //修改地址编译参数
        ADDR_PARAMENTS stParams;
        stParams.id         = count;
        stParams.itemId     = itemId;
        stParams.eType      = OBJ_ITEM;
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
        stParams.addrNum    = -1;
        m_addrWidth.compile(db, stParams);
        //m_addrWidth.compile(db, count, 0, OBJ_ITEM);

        count++;
        //修改地址编译参数
        stParams.id         = count;
        stParams.itemId     = itemId;
        stParams.eType      = OBJ_ITEM;
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
        stParams.addrNum    = -1;
        m_addrHeight.compile(db, stParams);
        //m_addrHeight.compile(db, count, 0, OBJ_ITEM);
    }
}

void DynRectAttr::save(QDataStream &stream) //将item存入数据流
{
    QVisableItem::save(stream);

    stream << m_bFillColor;
    stream << m_nFillColor;
    stream << m_bFrameColor;
    stream << m_nFrameColor;
    stream << m_nFrameWidth;
    stream << m_nAlpha;
    stream << m_nBeginX;
    stream << m_nBeginY;
    stream << m_nWidth;
    stream << m_nHeight;
    stream << m_nBgColor;
    stream << m_bPosCtrl;
    stream << m_addrH;
    stream << m_addrV;
    stream << m_bSizeCtrl;
    stream << m_nRefType;//固定点
    stream << m_addrWidth;
    stream << m_addrHeight;
}

void DynRectAttr::load(QDataStream &stream) //从数据流导出item
{
    QVisableItem::load(stream);

    stream >> m_bFillColor;
    stream >> m_nFillColor;
    stream >> m_bFrameColor;
    stream >> m_nFrameColor;
    stream >> m_nFrameWidth;
    stream >> m_nAlpha;
    stream >> m_nBeginX;
    stream >> m_nBeginY;
    stream >> m_nWidth;
    stream >> m_nHeight;
    stream >> m_nBgColor;
    stream >> m_bPosCtrl;
    stream >> m_addrH;
    stream >> m_addrV;
    stream >> m_bSizeCtrl;
    stream >> m_nRefType;//固定点
    stream >> m_addrWidth;
    stream >> m_addrHeight;
}

QList<Keyboard> DynRectAttr::getAddress()
{
    QList<Keyboard> addrs;

    if(m_bPosCtrl)
    {
        addrs << m_addrH;
        addrs << m_addrV;
    }

    if(m_bSizeCtrl)
    {
        addrs << m_addrWidth;
        addrs << m_addrHeight;
    }

    return addrs;
}

void DynRectAttr::setAddress(QList<Keyboard> addr)
{
    if (addr.size() <0)
    {
        return;
    }

    if(m_bPosCtrl)
    {
        m_addrH = addr.at(0);
        m_addrV = addr.at(1);
        if(m_bSizeCtrl)
        {
            m_addrWidth = addr.at(2);
            m_addrHeight = addr.at(3);
        }
    }
    else
    {
        if(m_bSizeCtrl)
        {
            m_addrWidth = addr.at(0);
            m_addrHeight = addr.at(1);
        }
    }
}

QVector<ADDRPRO> DynRectAttr::getAllItemAddr()
{
    addrs.clear();
    ADDRPRO temp;

    if(m_bPosCtrl)
    {
        temp.pAddr = &m_addrH;
        temp.str   = QObject::tr("动态矩形横坐标控制地址");
        temp.type  = 1;
        addrs << temp;

        temp.pAddr = &m_addrV;
        temp.str   = QObject::tr("动态矩形--纵坐标控制地址");
        temp.type  = 1;
        addrs << temp;
    }

    if(m_bSizeCtrl)
    {
        temp.pAddr = &m_addrWidth;
        temp.str   = QObject::tr("动态矩形--宽度地址控制");
        temp.type  = 1;
        addrs << temp;

        temp.pAddr = &m_addrHeight;
        temp.str   = QObject::tr("动态矩形--高度地址控制");
        temp.type  = 1;
        addrs << temp;
    }

    QVector<ADDRPRO> AddrList;
    AddrList = QVisableItem::getAllItemAddr();
    for(int i = 0; i < AddrList.size(); i++)
    {
        temp.pAddr = AddrList.at(i).pAddr;
        temp.str   = QObject::tr("动态矩形--权限地址");
        temp.type  = AddrList.at(i).type;
        addrs << temp;
    }

    return addrs;
}

QStringList DynRectAttr::getAllFonts()
{
    QStringList ls;
    ls.clear();
    /*foreach(QVector<ST_TEXT_PROP> textPros,statusText)
    {
            foreach(ST_TEXT_PROP textPro,textPros)
            {
                    if (!textPro.sfont.isEmpty())
                    {
                            ls << textPro.sfont;
                    }
            }

    }*/
    return ls;
}
