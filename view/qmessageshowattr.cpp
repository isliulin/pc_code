#include "qmessageshowattr.h"

extern MainWindow *pwnd;

QMessageShowAttr::QMessageShowAttr(QGraphicsItem *parent):QVisableItem(parent)//QItemGroup(parent)
{
    /*QList<QGraphicsItem*> pGroup;
    int nSpace = 4; //5
    int nWidth = 100-2*nSpace;

    QRectF rect(QPointF(0,0), QSize(100,100));     //绘制边框色矩形框
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(QColor(224,224,224));
    pFramRect->SetLineType(0);
    //  pFramRect->setZValue(1);
    pFramRect->SetName("mFramRect");
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    rect.setTopLeft(QPointF(nSpace,nSpace));       //绘制背景矩形框
    rect.setSize(QSize(nWidth,nWidth));
    QRectItem *pBackRect = new QRectItem(rect);
    pBackRect->SetBackColor(QColor(192,192,192));
    pBackRect->SetLineType(0);
    //  pBackRect->setZValue(2);
    pBackRect->SetName("mBackRect");
    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    rect.setTopLeft(QPointF(nSpace,nSpace));           //绘制柱
    rect.setSize(QSize(nWidth,nWidth));
    QSimpleTextItem *pText = new QSimpleTextItem(rect,"");
    pText->SetName("mText");
    pText->SetRectOutLine(false);
    // pText->setZValue(4);
    pText->setFlag(QGraphicsItem::ItemIsSelectable, false);

    pGroup << pFramRect;   //添加到组
    pGroup << pBackRect;
    pGroup << pText;*/
}

QMessageShowAttr::~QMessageShowAttr()
{
}

QString  QMessageShowAttr::getItemName()
{
    return QObject::tr("消息显示器");
}

int QMessageShowAttr::GroupType()//控件类型 位开关 字开关
{
    return SAM_DRAW_GROUP_MESSAGE;
}

QMessageShowAttr* QMessageShowAttr::Clone()//复制item
{
    QGraphicsItem* pCopy = NULL;
    QGraphicsItem* pItem = NULL;

    QMessageShowAttr *itemGroup = new QMessageShowAttr;

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

    itemGroup->curSta           = curSta;
    itemGroup->m_sShape         = m_sShape;
    itemGroup->m_bDataType      = m_bDataType;
    itemGroup->m_keyAddress     = m_keyAddress;
    itemGroup->m_nStateCount    = m_nStateCount;
    itemGroup->m_bFirstLanguage = m_bFirstLanguage;
    itemGroup->m_bStateZero     = m_bStateZero;
    itemGroup->m_eRemove        = m_eRemove;
    itemGroup->m_nSpeed         = m_nSpeed;
    itemGroup->m_nAlpha         = m_nAlpha;
    itemGroup->m_vecMsg         = m_vecMsg;
    itemGroup->setId(id());

    return itemGroup;
}

void QMessageShowAttr::compile(QSqlDatabase &db, int nSceneId, int &count, int index)
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
    bool r1 = sqlquery.prepare("INSERT INTO messageShow(nItemId,nSceneId,nAlpha,nLeftTopX,nLeftTopY,"
                                "nWidth,nHeight,nShowLeftTopX,nShowLeftTopY,nShowWidth,"
                                "nShowHeight,sShape,eDataType,eAddress,nStateCount,"
                                "bFirstLanguage,bStateZero,nZvalue,nCollidindId,nShowPropId)"
                         "VALUES(:nItemId,:nSceneId,:nAlpha,:nLeftTopX,:nLeftTopY,"
                                ":nWidth,:nHeight,:nShowLeftTopX,:nShowLeftTopY,:nShowWidth,"
                                ":nShowHeight,:sShape,:eDataType,:eAddress,:nStateCount,"
                                ":bFirstLanguage,:bStateZero,:nZvalue,:nCollidindId,:nShowPropId)");


    sqlquery.bindValue(":nItemId", QVariant(itemId));      //表id
    sqlquery.bindValue(":nSceneId", QVariant(nSceneId));  //scene id
    sqlquery.bindValue(":nAlpha", QVariant(m_nAlpha));

    QRectF rect = sceneBoundingRect();//相对场景的坐标及高宽
    sqlquery.bindValue(":nLeftTopX", QVariant((short)rect.left()));//left
    sqlquery.bindValue(":nLeftTopY", QVariant((short)rect.top()));//top
    sqlquery.bindValue(":nWidth", QVariant((short)rect.width()));//width
    sqlquery.bindValue(":nHeight", QVariant((short)rect.height()));//height

    //暂时都填0，到画图以后再改
    double width = rect.width();
    double height = rect.height();
    sqlquery.bindValue(":nShowLeftTopX", QVariant(width / 25));
    sqlquery.bindValue(":nShowLeftTopY", QVariant(height / 25));
    sqlquery.bindValue(":nShowWidth", QVariant(width - 2 * width / 25));
    sqlquery.bindValue(":nShowHeight", QVariant(height - 2 * height / 25));

    sqlquery.bindValue(":sShape", QVariant(m_sShape));
    if(0 == m_bDataType)
    {
        sqlquery.bindValue(":eDataType", QVariant(4));
    }
    else
    {
        sqlquery.bindValue(":eDataType", QVariant(5));
    }

    int id = count;
    count++;
    sqlquery.bindValue(":eAddress", QVariant(count));
    sqlquery.bindValue(":nStateCount", QVariant(m_nStateCount));
    sqlquery.bindValue(":bFirstLanguage", QVariant(m_bFirstLanguage));
    sqlquery.bindValue(":bStateZero", QVariant(m_bStateZero));

    sqlquery.bindValue(":nZvalue", QVariant(zValue()));
    sqlquery.bindValue(":nCollidindId", QVariant(index));
    sqlquery.bindValue(":nShowPropId", QVariant(0));

    bool result = sqlquery.exec();
    qDebug() << result << endl;

    //-----------地址-------------
    ADDR_PARAMENTS stParams;
    stParams.id         = count;
    stParams.itemId     = itemId;
    stParams.eType      = OBJ_ITEM;
    stParams.eRWtype = SCENE_CONTROL_LOOP_R;
    stParams.addrNum    = -1;
    if(0 == m_bDataType)//16
    {
        m_keyAddress.Length = 1;
    }
    else
    {
        m_keyAddress.Length = 2;
    }
    m_keyAddress.compile(db,stParams);

    bool r2 = sqlquery.prepare("INSERT INTO msgStatusProp(nItemId,nStatusIndex,sFontType,"
                               "nFontSize,nFontColor,eRemove,nFrameColor,nForecolor,"
                               "nBackcolor,nStyle,sStateMessage,nLanguage,nSpeed)"
                        "VALUES(:nItemId,:nStatusIndex,:sFontType,"
                               ":nFontSize,:nFontColor,:eRemove,:nFrameColor,:nForecolor,"
                               ":nBackcolor,:nStyle,:sStateMessage,:nLanguage,:nSpeed)");
    qDebug() << r2;

    int temp = m_vecMsg.size();
    int tempColor;
    for(int i = 0; i < temp; i++)
    {
        for(int j = 0; j < m_vecMsg[i].m_nVecPage2.size(); j++)
        {
            sqlquery.bindValue(":nItemId", QVariant(itemId));
            sqlquery.bindValue(":nStatusIndex", QVariant(m_vecMsg[i].m_nVecPage2[j].m_nStatusIndex));

            sqlquery.bindValue(":sFontType", QVariant(m_vecMsg[i].m_nVecPage2[j].m_sFontType));
            sqlquery.bindValue(":nFontSize", QVariant(m_vecMsg[i].m_nVecPage2[j].m_nFontSize));
            tempColor = ColorToInt(m_vecMsg[i].m_nVecPage2[j].m_nFontColor);
            sqlquery.bindValue(":nFontColor", QVariant(tempColor));
            //if(1 == m_vecMsg[i].m_nVecPage2[j].m_eRemove)
            if(1 == m_eRemove)
            {
                sqlquery.bindValue(":eRemove", QVariant(3));
            }
            //else if(2 == m_vecMsg[i].m_nVecPage2[j].m_eRemove)
            else if(2 == m_eRemove)
            {
                sqlquery.bindValue(":eRemove", QVariant(1));
            }
            else//不移动
            {
                sqlquery.bindValue(":eRemove", QVariant(7));
            }

            //属性页1的属性
            tempColor = ColorToInt(m_vecMsg[i].m_nFrameColor);
            sqlquery.bindValue(":nFrameColor", QVariant(tempColor));
            tempColor = ColorToInt(m_vecMsg[i].m_nForecolor);
            sqlquery.bindValue(":nForecolor", QVariant(tempColor));
            tempColor = ColorToInt(m_vecMsg[i].m_nBackcolor);
            sqlquery.bindValue(":nBackcolor", QVariant(tempColor));
            sqlquery.bindValue(":nStyle", QVariant(m_vecMsg[i].m_nStyle + 1));
            //-------------------------------

            sqlquery.bindValue(":sStateMessage", QVariant(m_vecMsg[i].m_nVecPage2[j].m_sStateMessage));
            sqlquery.bindValue(":nLanguage", QVariant(m_vecMsg[i].m_nVecPage2[j].m_nLanguage));
            sqlquery.bindValue(":nSpeed", QVariant(m_nSpeed));

            bool result1 = sqlquery.exec();
            qDebug() << result1 << endl;
        }
    }
}

void QMessageShowAttr::save(QDataStream &stream)//将item存入数据流
{
    QVisableItem::save(stream);

    stream << curSta;
    stream << m_sShape;
    stream << m_bDataType;
    stream << m_keyAddress;
    stream << m_nStateCount;
    stream << m_bFirstLanguage;
    stream << m_bStateZero;
    stream << m_eRemove;
    stream << m_nSpeed;
    stream << m_nAlpha;

    int temp = m_vecMsg.size();
    stream << temp;
    for(int i = 0; i < temp; i++)
    {
        int tempSize = m_vecMsg[i].m_nVecPage2.size();
        stream << tempSize;

        stream << m_vecMsg[i].m_nFrameColor;
        stream << m_vecMsg[i].m_nForecolor;
        stream << m_vecMsg[i].m_nBackcolor;
        stream << m_vecMsg[i].m_nStyle;

        for(int j = 0; j < tempSize; j++)
        {
            stream << m_vecMsg[i].m_nVecPage2[j].m_nStatusIndex;
            stream << m_vecMsg[i].m_nVecPage2[j].m_sStateMessage;
            stream << m_vecMsg[i].m_nVecPage2[j].m_nLanguage;
            stream << m_vecMsg[i].m_nVecPage2[j].m_sFontType;
            stream << m_vecMsg[i].m_nVecPage2[j].m_nFontSize;
            stream << m_vecMsg[i].m_nVecPage2[j].m_nFontColor;
            //stream << m_vecMsg[i].m_nVecPage2[j].m_eRemove;
            //stream << m_vecMsg[i].m_nVecPage2[j].m_nSpeed;
        }
    }
}

void QMessageShowAttr::load(QDataStream &stream)//从数据流导出item
{
    QVisableItem::load(stream);

    stream >> curSta;
    stream >> m_sShape;
    stream >> m_bDataType;
    stream >> m_keyAddress;
    stream >> m_nStateCount;
    stream >> m_bFirstLanguage;
    stream >> m_bStateZero;
    stream >> m_eRemove;
    stream >> m_nSpeed;
    stream >> m_nAlpha;

    int temp = 0;
    stream >> temp;
    MsgProp msg;
    LanDiff lan;
    for(int i = 0; i < temp; i++)
    {
        int tempSize = 0;
        stream >> tempSize;
        msg.m_nVecPage2.clear();

        stream >> msg.m_nFrameColor;
        stream >> msg.m_nForecolor;
        stream >> msg.m_nBackcolor;
        stream >> msg.m_nStyle;

        for(int j = 0; j < tempSize; j++)
        {
            stream >> lan.m_nStatusIndex;
            stream >> lan.m_sStateMessage;
            stream >> lan.m_nLanguage;
            stream >> lan.m_sFontType;
            stream >> lan.m_nFontSize;
            stream >> lan.m_nFontColor;

            msg.m_nVecPage2.push_back(lan);
        }

        m_vecMsg.push_back(msg);
    }
}

void QMessageShowAttr::redrawForChangeLanguage(int index)
{
    QGroupItem* pCopyBaseItem = new QGroupItem(this);
    int curLan = index;//pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan;

    pCopyBaseItem->SetPropertyValue("mText.Text",QVariant(m_vecMsg[curSta].m_nVecPage2[curLan].m_sStateMessage));
    pCopyBaseItem->SetPropertyValue("mText.Font",QVariant(m_vecMsg[curSta].m_nVecPage2[curLan].m_sFontType));
    pCopyBaseItem->SetPropertyValue("mText.FontSize",QVariant(m_vecMsg[curSta].m_nVecPage2[curLan].m_nFontSize));
    QString str = pwnd->ColorTOString(m_vecMsg[curSta].m_nVecPage2[curLan].m_nFontColor);
    pCopyBaseItem->SetPropertyValue("mText.FontColor",QVariant(str));
    pCopyBaseItem->SetPropertyValue("mBackRect.Pattern",QVariant(m_vecMsg[curSta].m_nStyle));
    if(m_vecMsg[curSta].m_nStyle == 0)
    {
        pCopyBaseItem->SetPropertyValue("mFramRect.Pattern",QVariant(m_vecMsg[curSta].m_nStyle));
    }

    str = pwnd->ColorTOString(m_vecMsg[curSta].m_nFrameColor);
    pCopyBaseItem->SetPropertyValue("mFramRect.BackColor",QVariant(str));
    str = pwnd->ColorTOString(m_vecMsg[curSta].m_nForecolor);
    pCopyBaseItem->SetPropertyValue("mBackRect.FrontColor",QVariant(str));
    str = pwnd->ColorTOString(m_vecMsg[curSta].m_nBackcolor);
    pCopyBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(str));
    pCopyBaseItem->SetPropertyValue("mFramRect.Alpha", QVariant(m_nAlpha));
    pCopyBaseItem->SetPropertyValue("mBackRect.Alpha", QVariant(m_nAlpha));
}

TEXTPRO QMessageShowAttr::getAllItemText()
{
    int iStaCount = m_nStateCount; //总状态数目
    int iLan = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //多语言总数

    vText.sCtrlName = this->getItemName(); //控件名称
    vText.iLanguage.clear();
    vText.vStatus.clear();
    vText.vText.clear();
    vText.vMsg.clear();

    for(int i = 0; i < iLan; i++) //总的语言扫描
    {
        for(int j = 0; j < iStaCount; j++)//总状态数目扫描
        {
            vText.iLanguage.append(i);
            vText.vStatus.append(j);
            vText.vMsg.append(QObject::tr("状态:")+QString("%1").arg(j));
            vText.vText.append(m_vecMsg[j].m_nVecPage2[i].m_sStateMessage);
        }
    }
    return vText;
}

void QMessageShowAttr::replaceAllItemText(int iLan, int iSta, QString sNewText)
{
    int iL = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //多语言总数
    int iStaCount = m_nStateCount; //总状态数目
    if( (iLan >= 0 && iLan < iL) && (iSta >= 0 && iSta < iStaCount))
    {
        m_vecMsg[iSta].m_nVecPage2[iLan].m_sStateMessage = sNewText;
    }
}

void QMessageShowAttr::redrawForChangeStatus(int index, int lan)
{
    int totalState = this->getItemStates().size();
    if(totalState <= index)
    {
        return;//目前没有这个状态
    }

    QGroupItem* pCopyBaseItem = new QGroupItem(this);
    curSta = index;
    int curLan = lan;//pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan;

    pCopyBaseItem->SetPropertyValue("mText.Text",QVariant(m_vecMsg[index].m_nVecPage2[curLan].m_sStateMessage));
    pCopyBaseItem->SetPropertyValue("mText.Font",QVariant(m_vecMsg[curSta].m_nVecPage2[curLan].m_sFontType));
    pCopyBaseItem->SetPropertyValue("mText.FontSize",QVariant(m_vecMsg[index].m_nVecPage2[curLan].m_nFontSize));
    QString str = pwnd->ColorTOString(m_vecMsg[index].m_nVecPage2[curLan].m_nFontColor);
    pCopyBaseItem->SetPropertyValue("mText.FontColor",QVariant(str));
    pCopyBaseItem->SetPropertyValue("mBackRect.Pattern",QVariant(m_vecMsg[index].m_nStyle));
    if(m_vecMsg[index].m_nStyle == 0)
    {
        pCopyBaseItem->SetPropertyValue("mFramRect.Pattern",QVariant(m_vecMsg[index].m_nStyle));
    }

    str = pwnd->ColorTOString(m_vecMsg[index].m_nFrameColor);
    pCopyBaseItem->SetPropertyValue("mFramRect.BackColor",QVariant(str));
    str = pwnd->ColorTOString(m_vecMsg[index].m_nForecolor);
    pCopyBaseItem->SetPropertyValue("mBackRect.FrontColor",QVariant(str));
    str = pwnd->ColorTOString(m_vecMsg[index].m_nBackcolor);
    pCopyBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(str));
    pCopyBaseItem->SetPropertyValue("mFramRect.Alpha", QVariant(m_nAlpha));
    pCopyBaseItem->SetPropertyValue("mBackRect.Alpha", QVariant(m_nAlpha));
}

QList<Keyboard> QMessageShowAttr::getAddress()
{
    QList<Keyboard> addrs;

    addrs << m_keyAddress;

    return addrs;
}

void QMessageShowAttr::setAddress(QList<Keyboard> addr)
{
    if (addr.size() <0)
    {
        return;
    }

    m_keyAddress = addr.at(0);
}

int QMessageShowAttr::getCurrentState()
{
    return curSta;
}

QStringList QMessageShowAttr::getItemStates()
{
    QStringList ls;
    ls.clear();

    QString str;
    for(int i = 0; i < m_nStateCount; i++)
    {
        str = QObject::tr("状态") + QString("%1").arg(i);
        ls.append(str);
    }

    return ls;
}

QVector<ADDRPRO> QMessageShowAttr::getAllItemAddr()
{
    addrs.clear();
    ADDRPRO temp;

    temp.pAddr = &m_keyAddress;
    temp.str   = QObject::tr("消息显示器--监视地址");
    temp.type  = 1;
    addrs << temp;

    QVector<ADDRPRO> AddrList;
    AddrList = QVisableItem::getAllItemAddr();
    for(int i = 0; i < AddrList.size(); i++)
    {
        temp.pAddr = AddrList.at(i).pAddr;
        temp.str   = QObject::tr("消息显示器--权限地址");
        temp.type  = AddrList.at(i).type;
        addrs << temp;
    }

    return addrs;
}

void QMessageShowAttr::changeItemLanguageAttr(int lanNum)
{
    int itemLanNum  = m_vecMsg[0].m_nVecPage2.size();
    int number      = m_vecMsg.size();
    //int loop        = 0;

    if(lanNum > itemLanNum)//需要增加语言数
    {
        //loop = lanNum - itemLanNum;
        for(int i = 0; i < number; i++)
        {
            LanDiff addItem;
            if(m_bFirstLanguage)
            {
                for(int j = itemLanNum; j < lanNum; j++)
                {
                    addItem.m_nFontColor    = m_vecMsg[i].m_nVecPage2[0].m_nFontColor;
                    addItem.m_nFontSize     = m_vecMsg[i].m_nVecPage2[0].m_nFontSize;
                    addItem.m_nLanguage     = j;
                    addItem.m_nStatusIndex  = i;
                    addItem.m_sFontType     = m_vecMsg[i].m_nVecPage2[0].m_sFontType;
                    addItem.m_sStateMessage = m_vecMsg[i].m_nVecPage2[0].m_sStateMessage;
                    m_vecMsg[i].m_nVecPage2.push_back(addItem);
                }
            }
            else
            {
                for(int j = itemLanNum; j < lanNum; j++)
                {
                    addItem.m_nFontColor    = QColor(0, 0, 0);
                    addItem.m_nFontSize     = 10;
                    addItem.m_nLanguage     = j;
                    addItem.m_nStatusIndex  = i;
                    addItem.m_sFontType     = QObject::tr("宋体");
                    addItem.m_sStateMessage = QString::number(i);
                    m_vecMsg[i].m_nVecPage2.push_back(addItem);
                }
            }
        }
    }
    else if(lanNum < itemLanNum)//需要删除语言
    {
        //loop = itemLanNum - lanNum;
        for(int i = 0; i < number; i++)
        {
            for(int j = itemLanNum - 1; j >= lanNum; j--)
            {
                m_vecMsg[i].m_nVecPage2.remove(j);
            }
        }
    }
}

QStringList QMessageShowAttr::getAllFonts()
{
    QStringList ls;
    ls.clear();

    foreach(MsgProp msgPros, m_vecMsg)
    {
        foreach(LanDiff textPro,msgPros.m_nVecPage2)
        {
            if (!textPro.m_sFontType.isEmpty() && !textPro.m_sStateMessage.isEmpty())
            {
                ls << textPro.m_sFontType;
            }
        }
    }

    return ls;
}
