#include "dyncircleattr.h"

DynCircleAttr::DynCircleAttr(QGraphicsItem *parent):QVisableItem(parent)//QItemGroup(parent)
{
    pCircle = NULL;
    /*QRectF rect = QRectF(0,0,100,100);
    pCircle   = new QElipseItem(rect);
    pCircle->SetBackColor(m_nFillColor);
    if(m_bFrameColor)
    {
        pCircle->SetLineColor(m_nFrameColor);
        pCircle->SetLineType(1);
        pCircle->SetLineWidth(1);
    }
    else
    {
        pCircle->SetLineColor(m_nFillColor);
        //pCircle->SetLineType(0);
    }
    addToGroup(pCircle);*/
}

QString DynCircleAttr::getItemName()
{
    return QObject::tr("动态圆");
}

void DynCircleAttr::resetCircle(short alpha, bool fill, bool frame, QColor cFill, QColor cFrame)
{
    if(pCircle)
    {
        delete pCircle;
        pCircle = NULL;
    }

    QRectF rect = QRectF(0,0,100,100);
    pCircle   = new QElipseItem(rect);
    pCircle->SetBackColor(cFill);
    if(fill)
    {
        pCircle->SetPattern(1);
        pCircle->SetBackColor(cFill);
    }
    else
    {
        pCircle->SetPattern(0);
    }
    pCircle->SetAlpha(alpha);

    if(frame)
    {
        pCircle->SetLineType(1);
        pCircle->SetLineWidth(1);
        pCircle->SetLineColor(cFrame);
    }
    else
    {
        pCircle->SetLineType(0);
    }

    addToGroup(pCircle);
}

DynCircleAttr::~DynCircleAttr()
{
    delete pCircle;
}

int DynCircleAttr::GroupType()                //控件类型 位开关 字开关
{
    return SAM_DRAW_GROUP_DYNCIRCLE;
}

DynCircleAttr* DynCircleAttr::Clone()         //复制item
{
    QGraphicsItem* pCopy = NULL;
    QGraphicsItem* pItem = NULL;

    DynCircleAttr *itemGroup = new DynCircleAttr;

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

    //矩形外观
    itemGroup->m_bFillColor     = m_bFillColor;
    itemGroup->m_nFillColor     = m_nFillColor;
    itemGroup->m_bFrameColor    = m_bFrameColor;
    itemGroup->m_nFrameColor    = m_nFrameColor;
    itemGroup->m_nFrameWidth    = m_nFrameWidth;
    itemGroup->m_nAlpha         = m_nAlpha;
    //显示区域设置
    itemGroup->m_nBeginX        = m_nBeginX;
    itemGroup->m_nBeginY        = m_nBeginY;
    itemGroup->m_nWidth         = m_nWidth;
    itemGroup->m_nHeight        = m_nHeight;
    itemGroup->m_nBgColor       = m_nBgColor;
    //位置控制
    itemGroup->m_bPosCtrl       = m_bPosCtrl;
    itemGroup->m_addrH          = m_addrH;
    itemGroup->m_addrV          = m_addrV;
    //大小控制
    itemGroup->m_bSizeCtrl      = m_bSizeCtrl;
    itemGroup->m_addrCircle     = m_addrCircle;
    itemGroup->setId(id());

    return itemGroup;
}

void DynCircleAttr::compile(QSqlDatabase &db, int nSceneId, int &count, int index)//编译的时候保存item到数据库
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
    bool result = sqlquery.prepare("INSERT INTO dynamicRound(nItemId,nSceneId,nAlpha,"
                           "nCpXpos,nCpYpos,nRadius,nFillColor,nUseFill,nRimColor,"
                           "nRimWidth,nUsePosCtrl,mCpXDataAddr,mCpYDataAddr,"
                           "mRadiusDataAddr,nUseSizeCtrl,nAreaLp,nAreaTp,nAreaWidth,"
                           "nAreaHeight,nAreaColor,nZvalue,nCollidindId,nShowPropId)"
                    "VALUES(:nItemId,:nSceneId,:nAlpha,"
                           ":nCpXpos,:nCpYpos,:nRadius,:nFillColor,:nUseFill,:nRimColor,"
                           ":nRimWidth,:nUsePosCtrl,:mCpXDataAddr,:mCpYDataAddr,"
                           ":mRadiusDataAddr,:nUseSizeCtrl,:nAreaLp,:nAreaTp,:nAreaWidth,"
                           ":nAreaHeight,:nAreaColor,:nZvalue,:nCollidindId,:nShowPropId)");

    qDebug() << "sqlquery.prepare" << result;

    int num  = count;
    int temp;
    short leftCp;
    short topCp;
    short width;
    short height;
    short radius;

    sqlquery.bindValue(":nItemId", QVariant(itemId));     //表id
    sqlquery.bindValue(":nSceneId", QVariant(nSceneId)); //scene id
    sqlquery.bindValue(":nAlpha", QVariant(m_nAlpha));   //alpha

    QRectF rect = sceneBoundingRect();//相对场景的坐标及高宽
    width       = rect.width();
    height      = rect.height();
    leftCp      = rect.left() + width/2;
    topCp       = rect.top() + height/2;
    radius      = width < height ? (width/2) : (height/2);
    sqlquery.bindValue(":nCpXpos", QVariant(leftCp));//left
    sqlquery.bindValue(":nCpYpos", QVariant(topCp));//top
    sqlquery.bindValue(":nRadius", QVariant(radius));//radius

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
        sqlquery.bindValue(":mCpXDataAddr", QVariant(num));//
        num++;
        sqlquery.bindValue(":mCpYDataAddr", QVariant(num));//
    }
    else
    {
        sqlquery.bindValue(":nUsePosCtrl", QVariant(0));//
        sqlquery.bindValue(":mCpXDataAddr", QVariant(0));//
        sqlquery.bindValue(":mCpYDataAddr", QVariant(0));//
    }

    if(m_bSizeCtrl)
    {
        sqlquery.bindValue(":nUseSizeCtrl", QVariant(1));//
        num++;
        sqlquery.bindValue(":mRadiusDataAddr", QVariant(num));//
    }
    else
    {
        sqlquery.bindValue(":nUseSizeCtrl", QVariant(0));//
        sqlquery.bindValue(":mRadiusDataAddr", QVariant(0));//
    }

    //sqlquery.bindValue(":nAreaLp", QVariant(m_nBeginX));//
    //sqlquery.bindValue(":nAreaTp", QVariant(m_nBeginY));//
    //sqlquery.bindValue(":nAreaWidth", QVariant(m_nWidth));//
    //sqlquery.bindValue(":nAreaHeight", QVariant(m_nHeight));//
    sqlquery.bindValue(":nAreaLp", QVariant(rect.left()));//
    sqlquery.bindValue(":nAreaTp", QVariant(rect.top()));//
    sqlquery.bindValue(":nAreaWidth", QVariant(rect.width()));//
    sqlquery.bindValue(":nAreaHeight", QVariant(rect.height()));//

    temp =ColorToInt(m_nBgColor);
    sqlquery.bindValue(":nAreaColor", QVariant(temp));//

    sqlquery.bindValue(":nZvalue", QVariant(zValue()));//
    sqlquery.bindValue(":nCollidindId", QVariant(index));//
    sqlquery.bindValue(":nShowPropId", QVariant(0));//

    bool result1 = false;
    result1 = sqlquery.exec();
    qDebug() << "insert table :" << result1 << endl;

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

        count++;
        //修改地址编译参数
        //ADDR_PARAMENTS stParams;
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
        m_addrCircle.compile(db, stParams);
        //m_addrCircle.compile(db, count, 0, OBJ_ITEM);
    }
}

void DynCircleAttr::save(QDataStream &stream)//将item存入数据流
{
    QVisableItem::save(stream);

    //矩形外观
    stream << m_bFillColor;
    stream << m_nFillColor;
    stream << m_bFrameColor;
    stream << m_nFrameColor;
    stream << m_nFrameWidth;
    stream << m_nAlpha;
    //显示区域设置
    stream << m_nBeginX;
    stream << m_nBeginY;
    stream << m_nWidth;
    stream << m_nHeight;
    stream << m_nBgColor;
    //位置控制
    stream << m_bPosCtrl;
    stream << m_addrH;
    stream << m_addrV;
    //大小控制
    stream << m_bSizeCtrl;
    stream << m_addrCircle;
}

void DynCircleAttr::load(QDataStream &stream)//从数据流导出item
{
    QVisableItem::load(stream);

    //矩形外观
    stream >> m_bFillColor;
    stream >> m_nFillColor;
    stream >> m_bFrameColor;
    stream >> m_nFrameColor;
    stream >> m_nFrameWidth;
    stream >> m_nAlpha;
    //显示区域设置
    stream >> m_nBeginX;
    stream >> m_nBeginY;
    stream >> m_nWidth;
    stream >> m_nHeight;
    stream >> m_nBgColor;
    //位置控制
    stream >> m_bPosCtrl;
    stream >> m_addrH;
    stream >> m_addrV;
    //大小控制
    stream >> m_bSizeCtrl;
    stream >> m_addrCircle;
}

QList<Keyboard> DynCircleAttr::getAddress()
{
    QList<Keyboard> addrs;

    if(m_bPosCtrl)
    {
        addrs << m_addrH;
        addrs << m_addrV;
    }

    if(m_bSizeCtrl)
    {
        addrs << m_addrCircle;
    }

    return addrs;
}

void DynCircleAttr::setAddress(QList<Keyboard> addr)
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
            m_addrCircle = addr.at(2);
        }
    }
    else
    {
        if(m_bSizeCtrl)
        {
            m_addrCircle = addr.at(0);
        }
    }
}

QVector<ADDRPRO> DynCircleAttr::getAllItemAddr()
{
    kb.clear();
    ADDRPRO temp;

    if(m_bPosCtrl)
    {
        temp.pAddr = &m_addrH;
        temp.str   = QObject::tr("动态圆--圆心横坐标数据控制地址");
        temp.type  = 1;//字地址
        kb << temp;

        temp.pAddr = &m_addrV;
        temp.str   = QObject::tr("动态圆--圆心纵坐标数据控制地址");
        temp.type  = 1;
        kb << temp;
    }

    if(m_bSizeCtrl)
    {
        temp.pAddr = &m_addrCircle;
        temp.str   = QObject::tr("动态圆--圆心半径数据控制地址");
        temp.type  = 1;
        kb << temp;
    }

    QVector<ADDRPRO> AddrList;
    AddrList = QVisableItem::getAllItemAddr();
    for(int i = 0; i < AddrList.size(); i++)
    {
        temp.pAddr = AddrList.at(i).pAddr;
        temp.str   = QObject::tr("动态圆--权限地址");
        temp.type  = AddrList.at(i).type;
        kb << temp;
    }

    return kb;
}

QStringList DynCircleAttr::getAllFonts()
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
















