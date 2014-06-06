#include "SliderItem.h"
#include "Frame/mainwindow.h"
#include "Frame/qprogectmanager.h"

extern MainWindow *pwnd;
SliderItem::SliderItem() :QVisableItem(0)
{

}
QString SliderItem::getItemName()
{
    return QObject::tr("滑动模拟量开关");
}

int SliderItem::GroupType()
{
    return SAM_DRAW_GROUP_SLIDER;
}
QGraphicsItem *SliderItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    SliderItem *itemGroup = new SliderItem();

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

    itemGroup->m_slider=m_slider;
    itemGroup->onSaveSlider(m_slider);
    itemGroup->m_sproperty=m_sproperty;
    itemGroup->SaveSecurityPro(&sPro);
    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    itemGroup->setId(id());
    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }
    return itemGroup;

}
void SliderItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    count++;
    int WriteAddrID;
    int MinAddrID;
    int MaxAddrID;
    QColor mColor;
    short num;
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

    //数据类别
    int lengDate=0;
    if(m_slider.dataType==0){//16正整数
        lengDate=1;
    }else if(m_slider.dataType==1){//32正整数
        lengDate=2;
    }else if(m_slider.dataType==2){//16整数
        lengDate=1;
    }else if(m_slider.dataType==3){//32整数
        lengDate=2;
    }else if(m_slider.dataType==4){//32浮点数
        lengDate=2;
    }
    //触发地址
    count++;
    WriteAddrID = count;
    ADDR_PARAMENTS stParams;
    stParams.id = count;
    stParams.itemId = itemId;
    stParams.eType = OBJ_ITEM;
    stParams.addrNum = -1;
    stParams.eRWtype = SCENE_CONTROL_ONCE_W;
    //SCENE_CONTROL_LOOP_R
    m_slider.keyWriteAddress.Length=lengDate;
    m_slider.keyWriteAddress.compile(db,stParams);

    if(m_slider.isTrend){
        //最大值
        count++;
        MaxAddrID = count;
        stParams.id = count;
        stParams.eRWtype = SCENE_CONTROL_ONCE_W;
        m_slider.MaxAddress.Length=lengDate;
        m_slider.MaxAddress.compile(db,stParams);

        //最小值
        count++;
        MinAddrID = count;
        stParams.id = count;
        stParams.eRWtype = SCENE_CONTROL_ONCE_W;
        m_slider.MinAddress.Length=lengDate;
        m_slider.MinAddress.compile(db,stParams);
    }

    QSqlQuery sqlquery(db);
        bool flag=sqlquery.prepare("INSERT INTO sliding(nItemId,nSceneId,nWidth,nHeight,nStartX,nStartY,"
                         "nRectColor,nSlideBarColor,nFingerBackColor,nFingerLineColor,nDirection,nPosition,"
                         "bShowCalibration,eDataType,nWirteAddress,bShowTrend,nMaxTrend,"
                         "nMinTrend,nCalibrationColor,nMaxNumber,nMinNumber,bShowShaft,"
                         "nDecimalCount,nTextSize,bShowText,nTotalCount,nCalibrationMax,nCalibrationMin,"
                         "nSlideWidth,nSlideHeight,nZvalue,nCollidindId,nShowPropId,nTouchPropId)"
                         "VALUES(:nItemId,:nSceneId,:nWidth,:nHeight,:nStartX,:nStartY,"
                         ":nRectColor,:nSlideBarColor,:nFingerBackColor,:nFingerLineColor,:nDirection,:nPosition,"
                         ":bShowCalibration,:eDataType,:nWirteAddress,:bShowTrend,:nMaxTrend,"
                         ":nMinTrend,:nCalibrationColor,:nMaxNumber,:nMinNumber,:bShowShaft,"
                         ":nDecimalCount,:nTextSize,:bShowText,:nTotalCount,:nCalibrationMax,:nCalibrationMin,"
                         ":nSlideWidth,:nSlideHeight,:nZvalue,:nCollidindId,:nShowPropId,:nTouchPropId)");
        sqlquery.bindValue(":nItemId",QVariant(itemId));// 表 id
        sqlquery.bindValue(":nSceneId",QVariant(nSceneId));// scene id
        //相对场景的坐标及高宽
        QRectF rect = boundingRect();
        rect = this->mapRectToScene(rect);

        int widths=0;
        int height=0;
        int startX=0;
        int startY=0;
        QList<QGraphicsItem *> childs = childItems();
        foreach(QGraphicsItem *pItem,childs)
        {
            if(pItem->data(GROUP_NAME_KEY).toString() == "mFramRect")
            {
                startX=pItem->sceneBoundingRect().x();
                startY=pItem->sceneBoundingRect().y();
                widths=pItem->sceneBoundingRect().width();
                height=pItem->sceneBoundingRect().height();
            }
        }
        if(m_slider.direction==1){//上
            sqlquery.bindValue(":nStartX", QVariant(startX));//left
            sqlquery.bindValue(":nStartY", QVariant((short)rect.y()));//top
            sqlquery.bindValue(":nWidth", QVariant(widths));//width
            sqlquery.bindValue(":nHeight", QVariant((short)rect.height()));//height
        }else if(m_slider.direction==2){//下
            sqlquery.bindValue(":nStartX", QVariant(startX));//left
            sqlquery.bindValue(":nStartY", QVariant((short)rect.y()));//top
            sqlquery.bindValue(":nWidth", QVariant(widths));//width
            sqlquery.bindValue(":nHeight", QVariant((short)rect.height()));//height
        }else{
            sqlquery.bindValue(":nStartX", QVariant((short)rect.x()));//left
            sqlquery.bindValue(":nStartY", QVariant((short)rect.y()));//top
            sqlquery.bindValue(":nWidth", QVariant((short)rect.width()));//width
            sqlquery.bindValue(":nHeight", QVariant((short)rect.height()));//height
        }


        mColor=pwnd->StringTOColor(m_slider.rectColor);
        sqlquery.bindValue(":nRectColor",QVariant(ColorToInt(mColor)));
        mColor=pwnd->StringTOColor(m_slider.slideBarColor);
        sqlquery.bindValue(":nSlideBarColor",QVariant(ColorToInt(mColor)));
        mColor=pwnd->StringTOColor(m_slider.fingerBackColor);
        sqlquery.bindValue(":nFingerBackColor",QVariant(ColorToInt(mColor)));
        mColor=pwnd->StringTOColor(m_slider.fingerLineColor);
        sqlquery.bindValue(":nFingerLineColor",QVariant(ColorToInt(mColor)));
        sqlquery.bindValue(":nDirection",QVariant(m_slider.direction));

        /*if( (m_slider.sPosition==QDialog::tr("向下")) || (m_slider.sPosition=="Down"))
        {
            num=2;
        }
        else if( (m_slider.sPosition==QDialog::tr("向上")) || (m_slider.sPosition=="Up"))
        {
            num=1;
        }
        else if( (m_slider.sPosition==QDialog::tr("向右")) || (m_slider.sPosition=="Right"))
        {
            num=4;
        }
        else if( (m_slider.sPosition==QDialog::tr("向左")) || (m_slider.sPosition=="Left"))
        {
            num=3;
        }*/

        if(m_slider.direction == 1 || m_slider.direction ==  2)
        {
            num = m_slider.nPosition + 3;
        }
        else
        {
            num = m_slider.nPosition + 1;
        }
        //num = m_slider.nPosition + 1;
        sqlquery.bindValue(":nPosition",QVariant(num));
        sqlquery.bindValue(":bShowCalibration",QVariant(m_slider.isShowCalibration));

        if(m_slider.dataType==0){//
            num=4;
        }else if(m_slider.dataType==1){//
            num=5;
        }else if(m_slider.dataType==2){//
            num=2;
        }else if(m_slider.dataType==3){//
            num=3;
        }else if(m_slider.dataType==4){//
            num=8;
        }
        sqlquery.bindValue(":eDataType",QVariant(num));
        sqlquery.bindValue(":nWirteAddress",QVariant(WriteAddrID));
        sqlquery.bindValue(":bShowTrend",QVariant(m_slider.isTrend));
        if(m_slider.isTrend){
            sqlquery.bindValue(":nMaxTrend",QVariant(MaxAddrID));
            sqlquery.bindValue(":nMinTrend",QVariant(MinAddrID));
        }else{
            sqlquery.bindValue(":nMaxTrend",QVariant(m_slider.maxTrend.toDouble()));
            sqlquery.bindValue(":nMinTrend",QVariant(m_slider.minTrend.toDouble()));
        }

        mColor=pwnd->StringTOColor(m_slider.nCalibrationColor);
        sqlquery.bindValue(":nCalibrationColor",QVariant(ColorToInt(mColor)));
        sqlquery.bindValue(":nMaxNumber",QVariant(m_slider.nMaxNumber));
        sqlquery.bindValue(":nMinNumber",QVariant(m_slider.nMinNumber));
        sqlquery.bindValue(":bShowShaft",QVariant(true));
        sqlquery.bindValue(":nDecimalCount",QVariant(m_slider.nDecimalCount));
        sqlquery.bindValue(":nTextSize",QVariant(m_slider.sTextSize));
        sqlquery.bindValue(":bShowText",QVariant(m_slider.bShowText));
        sqlquery.bindValue(":nTotalCount",QVariant(m_slider.nTotalCount));
        sqlquery.bindValue(":nCalibrationMax",QVariant(m_slider.nCalibrationMax.toDouble()));
        sqlquery.bindValue(":nCalibrationMin",QVariant(m_slider.nCalibrationMin.toDouble()));

        int nSlideWidht=0;
        int nSlideHeight=0;
        QList<QGraphicsItem *> childes = childItems();
        foreach(QGraphicsItem *pItem,childes)
        {
            if(pItem->data(GROUP_NAME_KEY).toString() == "mFramRect")
            {
                nSlideWidht=pItem->sceneBoundingRect().width();
                nSlideHeight=pItem->sceneBoundingRect().height();
            }
        }
        sqlquery.bindValue(":nSlideWidth",QVariant(nSlideWidht));
        sqlquery.bindValue(":nSlideHeight",QVariant(nSlideHeight));
        sqlquery.bindValue(":nZvalue",QVariant(zValue()));
        sqlquery.bindValue(":nCollidindId",QVariant(index));
        sqlquery.bindValue(":nShowPropId",QVariant(1));
        sqlquery.bindValue(":nTouchPropId",QVariant(1));
        flag=sqlquery.exec();
        int a;
    }

void SliderItem::save(QDataStream &stream)
{
    QVisableItem::save(stream);
    stream << m_slider.bShowShaft;
    stream << m_slider.bShowText;
    stream << m_slider.dataType;
    stream << m_slider.direction;
    stream << m_slider.fingerBackColor;
    stream << m_slider.fingerLineColor;
    stream << m_slider.isShowCalibration;
    stream << m_slider.isTrend;
    stream << m_slider.keyWriteAddress;
    stream << m_slider.MaxAddress;
    stream << m_slider.maxTrend;
    stream << m_slider.mHeight;
    stream << m_slider.MinAddress;
    stream << m_slider.minTrend;
    stream << m_slider.mWidth;
    stream << m_slider.nCalibrationColor;
    stream << m_slider.nCalibrationMax;
    stream << m_slider.nCalibrationMin;
    stream << m_slider.nDecimalCount;
    stream << m_slider.nMaxNumber;
    stream << m_slider.nMinNumber;
    stream << m_slider.nPosition;
    stream << m_slider.nTextSize;
    stream << m_slider.nTotalCount;
    stream << m_slider.rectColor;
    stream << m_slider.slideBarColor;
    stream << m_slider.sPosition;
    stream << m_slider.writeAddress;
    stream << m_slider.sTextSize;
    stream << m_slider.startY;
    stream << m_slider.startX;
}
void SliderItem::load(QDataStream &stream)
{
    QVisableItem::load(stream);
    stream >> m_slider.bShowShaft;
    stream >> m_slider.bShowText;
    stream >> m_slider.dataType;
    stream >> m_slider.direction;
    stream >> m_slider.fingerBackColor;
    stream >> m_slider.fingerLineColor;
    stream >> m_slider.isShowCalibration;
    stream >> m_slider.isTrend;
    stream >> m_slider.keyWriteAddress;
    stream >> m_slider.MaxAddress;
    stream >> m_slider.maxTrend;
    stream >> m_slider.mHeight;
    stream >> m_slider.MinAddress;
    stream >> m_slider.minTrend;
    stream >> m_slider.mWidth;
    stream >> m_slider.nCalibrationColor;
    stream >> m_slider.nCalibrationMax;
    stream >> m_slider.nCalibrationMin;
    stream >> m_slider.nDecimalCount;
    stream >> m_slider.nMaxNumber;
    stream >> m_slider.nMinNumber;
    stream >> m_slider.nPosition;
    stream >> m_slider.nTextSize;
    stream >> m_slider.nTotalCount;
    stream >> m_slider.rectColor;
    stream >> m_slider.slideBarColor;
    stream >> m_slider.sPosition;
    stream >> m_slider.writeAddress;
    stream >> m_slider.sTextSize;
    stream >> m_slider.startY;
    stream >> m_slider.startX;
}

void SliderItem::onSaveSlider(SliderInfo slider)    //保存静态文本显示信息
{
    m_slider = slider;
}

void SliderItem::onSecurityPro(securityPro sproperty){
    m_sproperty=sproperty;
}

//获得操作地址
QList<Keyboard> SliderItem::getAddress()
{
    QList<Keyboard> addrs;
    addrs << m_slider.keyWriteAddress;
    return addrs;
}
//设置操作地址
void SliderItem::setAddress(QList<Keyboard> addr)
{
    if (addr.size() <= 0)
        return ;
    m_slider.keyWriteAddress=addr.first();
    m_slider.writeAddress=m_slider.keyWriteAddress.sShowAddr;
}
//查找地址函数
QVector<ADDRPRO> SliderItem::getAllItemAddr()
{
    addrs.clear();
    ADDRPRO temp;

    temp.pAddr = &m_slider.keyWriteAddress;
    temp.str   = QObject::tr("滑动块--写入地址");
    temp.type  = 1;
    addrs << temp;

    if(m_slider.isTrend){
        temp.pAddr = &m_slider.MaxAddress;
        temp.str   = QObject::tr("滑动块--动态范围最大值地址");
        temp.type  = 1;
        addrs << temp;

        temp.pAddr = &m_slider.MinAddress;
        temp.str   = QObject::tr("滑动块--动态范围最小值地址");
        temp.type  = 1;
        addrs << temp;
    }

    QVector<ADDRPRO> AddrList;
    AddrList = QVisableItem::getAllItemAddr();
    for(int i = 0; i < AddrList.size(); i++)
    {
        temp.pAddr = AddrList.at(i).pAddr;
        temp.str = QObject::tr("滑动块--权限地址");
        temp.type  = AddrList.at(i).type;
        addrs << temp;
    }

    return addrs;
}
