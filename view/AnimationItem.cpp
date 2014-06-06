#include "AnimationItem.h"
#include "Frame/qprogectmanager.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;


AnimationItem::AnimationItem()
    :QVisableItem(0)
{
    //Datesave = new struct CHART_INFORMATION;
}



QGraphicsItem *AnimationItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    AnimationItem *itemGroup = new AnimationItem();

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

    itemGroup->SaveSecurityPro(&sPro);

    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    itemGroup->setData(GROUP_TYPE_KEY,data(GROUP_TYPE_KEY).toInt());
    QVector<TrackPointInfo> Tinfo;
    onGetTrackInfo(Tinfo);
    itemGroup->onSetTrackInfo(Tinfo);

    AnInfo aninfo;
    onGetAnimatInfo(aninfo);
    itemGroup->onSaveAnimatInfo(aninfo);

    int num = onGetCurrentNum();
    itemGroup->onSetCurrentNum(num);
    itemGroup->setId(id());

    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }
    return itemGroup;
    //return QItemGroup::Clone();
    //return 0;
    //需要在派生类实例化对象，复制部分无法重用基类代码
}

void AnimationItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
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

    onGetTrakpos();
    QList <QGraphicsItem *> pList;
    pList = this->childItems();
    QSizeF size(60,60);
    foreach(QGraphicsItem *item, pList)
    {
        if("mMain" == item->data(GROUP_NAME_KEY).toString())
        {
            size.setWidth(item->boundingRect().width());
            size.setHeight(item->boundingRect().height());
            break;
        }
    }

    QSqlQuery sqlquery(db);

    bool bReasult = false;

    QRectF pos = sceneBoundingRect();
    bReasult = sqlquery.prepare("INSERT INTO animation(nItemId,nSceneId,nLp,nTp,nWidth,nHeight,nTrackType,nBackColor,"
                     "nMoveCondition ,nMoveType,nMoveTimeInterval,nStartTrackPoint,"
                     "nTrackPointTotal,mMoveCtrlAddr,mXPosCtrlAddr,mYPosCtrlAddr,"
                     "nXMoveStepScale,nYMoveStepScale,nAreaOrigXPos,nAreaOrigYPos,"
                     "nAreaWidth,nAreaHeight,nStateTotal,nChangeCondition,nChangeType,"
                     "nChangeTimeinterval,nInitState,mChangeCtrlAddr,nZvalue,"
                     "nCollidindId,nShowPropId)"
                     "VALUES (:nItemId,:nSceneId,:nLp,:nTp,:nWidth,:nHeight,:nTrackType,:nBackColor,"
                     ":nMoveCondition ,:nMoveType,:nMoveTimeInterval,:nStartTrackPoint,"
                     ":nTrackPointTotal,:mMoveCtrlAddr,:mXPosCtrlAddr,:mYPosCtrlAddr,"
                     ":nXMoveStepScale,:nYMoveStepScale,:nAreaOrigXPos,:nAreaOrigYPos,"
                     ":nAreaWidth,:nAreaHeight,:nStateTotal,:nChangeCondition,:nChangeType,"
                     ":nChangeTimeinterval,:nInitState,:mChangeCtrlAddr,:nZvalue,"
                     ":nCollidindId,:nShowPropId)");

    sqlquery.bindValue(":nItemId",QVariant(nItemID));
    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));
    sqlquery.bindValue(":nLp",QVariant(pos.x()));
    sqlquery.bindValue(":nTp",QVariant(pos.y()));
    sqlquery.bindValue(":nWidth",QVariant(size.width()));
    sqlquery.bindValue(":nHeight",QVariant(size.height()));

    QColor mColor = pwnd->StringTOColor(m_AnimatInfo.nBackColor);
    sqlquery.bindValue(":nBackColor",QVariant(ColorToInt(mColor)));
    sqlquery.bindValue(":nTrackType",QVariant(m_AnimatInfo.nTrackType));
    sqlquery.bindValue(":nMoveCondition",QVariant(m_AnimatInfo.nMoveCondition));
    sqlquery.bindValue(":nMoveType",QVariant(m_AnimatInfo.nMoveType));
    sqlquery.bindValue(":nMoveTimeInterval",QVariant(m_AnimatInfo.nMoveTimeInterval * 100));
    sqlquery.bindValue(":nStartTrackPoint",QVariant(m_AnimatInfo.nStartTrackPoint));
    sqlquery.bindValue(":nTrackPointTotal",QVariant(m_AnimatInfo.nTrackPointTotal));
    sqlquery.bindValue(":nXMoveStepScale",QVariant(m_AnimatInfo.nXMoveStepScale));
    sqlquery.bindValue(":nYMoveStepScale",QVariant(m_AnimatInfo.nYMoveStepScale));
    sqlquery.bindValue(":nAreaOrigXPos",QVariant(pos.x()));
    sqlquery.bindValue(":nAreaOrigYPos",QVariant(pos.y()));
    sqlquery.bindValue(":nAreaWidth",QVariant(pos.width()));
    sqlquery.bindValue(":nAreaHeight",QVariant(pos.height()));
    sqlquery.bindValue(":nStateTotal",QVariant(m_AnimatInfo.nStateTotal));
    sqlquery.bindValue(":nChangeCondition",QVariant(m_AnimatInfo.nChangeCondition));
    sqlquery.bindValue(":nChangeType",QVariant(m_AnimatInfo.nChangeType + 1));
    sqlquery.bindValue(":nChangeTimeinterval",QVariant(m_AnimatInfo.nChangeTimeinterval * 100));
    sqlquery.bindValue(":nInitState",QVariant(m_AnimatInfo.nInitState));
    count ++;
	//修改地址编译参数
    ADDR_PARAMENTS stParams;
    stParams.id = count;
    stParams.itemId = nItemID;
    stParams.eType = OBJ_ITEM;
    stParams.addrNum = -1;
    stParams.eRWtype = SCENE_CONTROL_LOOP_R;
    m_AnimatInfo.mMoveCtrlAddr.compile(db,stParams);
    sqlquery.bindValue(":mMoveCtrlAddr",QVariant(count));

    if(1 == m_AnimatInfo.nTrackType)
    {
        //x控制地址
        count++;
        stParams.id = count;
        m_AnimatInfo.mXPosCtrlAddr.compile(db,stParams);
        sqlquery.bindValue(":mXPosCtrlAddr",QVariant(count));

        //y控制地址
        count++;
        stParams.id = count;
        m_AnimatInfo.mYPosCtrlAddr.compile(db,stParams);
        sqlquery.bindValue(":mYPosCtrlAddr",QVariant(count));
    }
    else
    {
        sqlquery.bindValue(":mXPosCtrlAddr",QVariant(-1));
        sqlquery.bindValue(":mYPosCtrlAddr",QVariant(-1));
    }

    sqlquery.bindValue(":nShowPropId",QVariant(1));//////////////
    if(1 == m_AnimatInfo.nChangeCondition)
    {
        count++;
        stParams.id = count;
        m_AnimatInfo.mChangeCtrlAddr.Length = 2;
        m_AnimatInfo.mChangeCtrlAddr.compile(db,stParams);
        sqlquery.bindValue(":mChangeCtrlAddr",QVariant(count));
    }
    else
    {
        sqlquery.bindValue(":mChangeCtrlAddr",QVariant(-1));
    }
    sqlquery.bindValue(":nZvalue",QVariant(zValue()));
    sqlquery.bindValue(":nCollidindId",QVariant(index));
    bReasult = sqlquery.exec();
    qDebug()<<"INSERT INTO animation"<<bReasult;


    for(int i = 0; i < TrackInfo.size(); i++)
    {
        bReasult = sqlquery.prepare("INSERT INTO animationOrbit(nItemId,nOrbitId,nXPos,nYPos,nMCmpFactor)"
                                    "VALUES (:nItemId,:nOrbitId,:nXPos,:nYPos,:nMCmpFactor)");
        sqlquery.bindValue(":nItemId",QVariant(nItemID));
        sqlquery.bindValue(":nOrbitId",QVariant(i));
        sqlquery.bindValue(":nXPos",QVariant(TrackInfo[i].nXPos));
        sqlquery.bindValue(":nYPos",QVariant(TrackInfo[i].nYPos));
        if(i < m_AnimatInfo.stMoveInfo.size())
        {
            sqlquery.bindValue(":nMCmpFactor",QVariant(m_AnimatInfo.stMoveInfo[i].nMCmpFactor));
        }
        else
        {
            sqlquery.bindValue(":nMCmpFactor",QVariant(-1));
        }
        bReasult = sqlquery.exec();
        qDebug()<<"INSERT INTO animationOrbit i="<<i<<bReasult;
    }

    for(int i = 0; i < m_AnimatInfo.PicInfo.size(); i++)
    {
        bReasult = sqlquery.prepare("INSERT INTO switchStatusProp(nItemId,statusValue,nStatusIndex,eflick,nAlpha,eLib,sPath)"
                                    "VALUES (:nItemId,:statusValue,:nStatusIndex,:eflick,:nAlpha,:eLib,:sPath)");
        sqlquery.bindValue(":nItemId",QVariant(nItemID));
        sqlquery.bindValue(":statusValue",QVariant(m_AnimatInfo.PicInfo[i].nCmpFactor));
        sqlquery.bindValue(":nStatusIndex",QVariant(i));
        bool bPic = false;
        if(0 == m_AnimatInfo.PicInfo[i].bIspic || USERDEFINE == m_AnimatInfo.PicInfo[i].bIspic)
        {
            bPic = false;
        }
        else
        {
            bPic = true;
        }

        QString newPath = pwnd->SavePath(m_AnimatInfo.PicInfo[i].sPath,size,bPic);
        if("" != newPath)
        {
            newPath = newPath.replace("\\","/");
            newPath = newPath.section("/",-1);
            newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
        }
        sqlquery.bindValue(":eLib",QVariant(bPic));
        sqlquery.bindValue(":sPath",QVariant(newPath));
        bReasult = sqlquery.exec();
        qDebug()<<"INSERT INTO switchStatusProp"<<bReasult;
    }
    for(int i = 0; i < m_AnimatInfo.Text.size(); i++)
    {
        bReasult = sqlquery.prepare("INSERT INTO textProp(nItemId,nStatusIndex,nLangIndex,sFont,sText,nSize,nColor,nShowProp)"
                                    "VALUES (:nItemId,:nStatusIndex,:nLangIndex,:sFont,:sText,:nSize,:nColor,:nShowProp)");
        sqlquery.bindValue(":nItemId",QVariant(nItemID));
        sqlquery.bindValue(":nStatusIndex",QVariant(i));
        sqlquery.bindValue(":nLangIndex",QVariant(-1));
        sqlquery.bindValue(":sFont",QVariant(m_AnimatInfo.Text[i].sFontFamily));
        sqlquery.bindValue(":sText",QVariant(m_AnimatInfo.Text[i].sText));
        sqlquery.bindValue(":nSize",QVariant(m_AnimatInfo.Text[i].nSize + 5));
        QColor mColor = pwnd->StringTOColor(m_AnimatInfo.Text[i].nColor);
        sqlquery.bindValue(":nColor",QVariant(ColorToInt(mColor)));
        int nShowProp = 0;
        nShowProp = nShowProp | m_AnimatInfo.Text[i].nStyle;

        if(Lpoint == m_AnimatInfo.Text[i].eAlign)//左
        {
            nShowProp = nShowProp | 0x0020; //10 0000左
        }
        else if(Cpoint == m_AnimatInfo.Text[i].eAlign)//中
        {
            nShowProp = nShowProp | 0x0010; //01 0000 中
        }
        else//右
        {
            nShowProp = nShowProp | 0x0040; //0100 0000 右
        }
        sqlquery.bindValue(":nShowProp",QVariant(nShowProp));
        bReasult = sqlquery.exec();
        qDebug()<<"INSERT INTO textProp"<<bReasult;
    }
    //在此添加编译权限页面属性代码
}

int AnimationItem::GroupType()
{
    return SAM_DRAW_GROUP_ANIMATION;
}
void AnimationItem::save(QDataStream &stream)
{
    QVisableItem::save(stream);

    stream << number;
    int nTrack = TrackInfo.size();
    stream << nTrack;
    for(int i = 0; i < nTrack; i++)
    {
        stream << TrackInfo[i].nOrbitId;
        stream << TrackInfo[i].nXPos;
        stream << TrackInfo[i].nYPos;
    }

    stream << m_AnimatInfo.nTrackType;
    stream << m_AnimatInfo.nBackColor;
    stream << m_AnimatInfo.nMoveCondition;
    stream << m_AnimatInfo.nMoveType;
    stream << m_AnimatInfo.nMoveTimeInterval;
    stream << m_AnimatInfo.nStartTrackPoint;
    stream << m_AnimatInfo.nTrackPointTotal;
    stream << m_AnimatInfo.sMoveCtrlAddr;
    stream << m_AnimatInfo.mMoveCtrlAddr;

    int nMove = m_AnimatInfo.stMoveInfo.size();
    stream << nMove;
    for(int i = 0; i < nMove; i++)
    {
        stream << m_AnimatInfo.stMoveInfo[i].nTrackPointNo;
        stream << m_AnimatInfo.stMoveInfo[i].nMCmpFactor;
    }

    stream << m_AnimatInfo.mXPosCtrlAddr;
    stream << m_AnimatInfo.mYPosCtrlAddr;
    stream << m_AnimatInfo.sAddrX;
    stream << m_AnimatInfo.sAddrY;
    stream << m_AnimatInfo.nXMoveStepScale;
    stream << m_AnimatInfo.nYMoveStepScale;
    stream << m_AnimatInfo.nAreaOrigXPos;
    stream << m_AnimatInfo.nAreaOrigYPos;
    stream << m_AnimatInfo.nAreaWidth;
    stream << m_AnimatInfo.nAreaHeight;
    stream << m_AnimatInfo.nStateTotal;
    stream << m_AnimatInfo.nChangeCondition;
    stream << m_AnimatInfo.nChangeType;
    stream << m_AnimatInfo.nChangeTimeinterval;
    stream << m_AnimatInfo.nInitState;
    stream << m_AnimatInfo.mChangeCtrlAddr;
    stream << m_AnimatInfo.sChangeCtrlAddr;

    int nPre = m_AnimatInfo.mSPreSetVList.size();
    stream << nPre;
    for(int i = 0; i < nPre; i++)
    {
        stream << m_AnimatInfo.mSPreSetVList[i].nStateNo;
        stream << m_AnimatInfo.mSPreSetVList[i].nSCmpFactor;
    }

    int nText = m_AnimatInfo.Text.size();
    stream << nText;
    for(int i = 0; i < nText; i++)
    {
        stream << m_AnimatInfo.Text[i].bValid;
        stream << m_AnimatInfo.Text[i].nStatusId;
        stream << m_AnimatInfo.Text[i].sFontFamily;
        stream << m_AnimatInfo.Text[i].sFontIndex;
        stream << m_AnimatInfo.Text[i].nSize;
        stream << m_AnimatInfo.Text[i].nColor;
        stream << m_AnimatInfo.Text[i].nBColor;
        stream << m_AnimatInfo.Text[i].sText;
        stream << m_AnimatInfo.Text[i].nStyle;
        stream << int(m_AnimatInfo.Text[i].eAlign);
        stream << m_AnimatInfo.Text[i].nSpace;
    }

    //stream << m_AnimatInfo.sPicBackColor;
    int nPic = m_AnimatInfo.PicInfo.size();
    stream << nPic;
    for(int i = 0; i < nPic; i++)
    {
        stream << m_AnimatInfo.PicInfo[i].name;
        stream << m_AnimatInfo.PicInfo[i].nStatusId;
        stream << m_AnimatInfo.PicInfo[i].sPath;
        stream << int(m_AnimatInfo.PicInfo[i].bIspic);
        stream << m_AnimatInfo.PicInfo[i].nCmpFactor;
    }


}
void AnimationItem::load(QDataStream &stream)
{
    QVisableItem::load(stream);

    stream >> number;
    int nTrack = 0;
    stream >> nTrack;
    TrackInfo.resize(nTrack);
    for(int i = 0; i < nTrack; i++)
    {
        stream >> TrackInfo[i].nOrbitId;
        stream >> TrackInfo[i].nXPos;
        stream >> TrackInfo[i].nYPos;
    }

    stream >> m_AnimatInfo.nTrackType;
    stream >> m_AnimatInfo.nBackColor;
    stream >> m_AnimatInfo.nMoveCondition;
    stream >> m_AnimatInfo.nMoveType;
    stream >> m_AnimatInfo.nMoveTimeInterval;
    stream >> m_AnimatInfo.nStartTrackPoint;
    stream >> m_AnimatInfo.nTrackPointTotal;
    stream >> m_AnimatInfo.sMoveCtrlAddr;
    stream >> m_AnimatInfo.mMoveCtrlAddr;

    int nMove = 0;
    stream >> nMove;
    m_AnimatInfo.stMoveInfo.resize(nMove);
    for(int i = 0; i < nMove; i++)
    {
        stream >> m_AnimatInfo.stMoveInfo[i].nTrackPointNo;
        stream >> m_AnimatInfo.stMoveInfo[i].nMCmpFactor;
    }

    stream >> m_AnimatInfo.mXPosCtrlAddr;
    stream >> m_AnimatInfo.mYPosCtrlAddr;
    stream >> m_AnimatInfo.sAddrX;
    stream >> m_AnimatInfo.sAddrY;
    stream >> m_AnimatInfo.nXMoveStepScale;
    stream >> m_AnimatInfo.nYMoveStepScale;
    stream >> m_AnimatInfo.nAreaOrigXPos;
    stream >> m_AnimatInfo.nAreaOrigYPos;
    stream >> m_AnimatInfo.nAreaWidth;
    stream >> m_AnimatInfo.nAreaHeight;
    stream >> m_AnimatInfo.nStateTotal;
    stream >> m_AnimatInfo.nChangeCondition;
    stream >> m_AnimatInfo.nChangeType;
    stream >> m_AnimatInfo.nChangeTimeinterval;
    stream >> m_AnimatInfo.nInitState;
    stream >> m_AnimatInfo.mChangeCtrlAddr;
    stream >> m_AnimatInfo.sChangeCtrlAddr;

    int nPre = 0;
    stream >> nPre;
    m_AnimatInfo.mSPreSetVList.resize(nPre);
    for(int i = 0; i < nPre; i++)
    {
        stream >> m_AnimatInfo.mSPreSetVList[i].nStateNo;
        stream >> m_AnimatInfo.mSPreSetVList[i].nSCmpFactor;
    }

    int nText = 0;
    stream >> nText;
    m_AnimatInfo.Text.resize(nText);;
    for(int i = 0; i < nText; i++)
    {
        stream >> m_AnimatInfo.Text[i].bValid;
        stream >> m_AnimatInfo.Text[i].nStatusId;
        stream >> m_AnimatInfo.Text[i].sFontFamily;
        stream >> m_AnimatInfo.Text[i].sFontIndex;
        stream >> m_AnimatInfo.Text[i].nSize;
        stream >> m_AnimatInfo.Text[i].nColor;
        stream >> m_AnimatInfo.Text[i].nBColor;
        stream >> m_AnimatInfo.Text[i].sText;
        stream >> m_AnimatInfo.Text[i].nStyle;
        int nAlign;
        stream >> nAlign;
        m_AnimatInfo.Text[i].eAlign = TEXT_PIC_ALIGN(nAlign);
        stream >> m_AnimatInfo.Text[i].nSpace;
    }

    //stream >> m_AnimatInfo.sPicBackColor;
    int nPic = 0;
    stream >> nPic;
    m_AnimatInfo.PicInfo.resize(nPic);
    for(int i = 0; i < nPic; i++)
    {
        stream >> m_AnimatInfo.PicInfo[i].name;
        stream >> m_AnimatInfo.PicInfo[i].nStatusId;
        stream >> m_AnimatInfo.PicInfo[i].sPath;
        int nPicType = 0;
        stream >> nPicType;
        m_AnimatInfo.PicInfo[i].bIspic = EITEM_TYPE(nPicType);
        stream >> m_AnimatInfo.PicInfo[i].nCmpFactor;
    }
}

void AnimationItem::onSetCurrentNum(short int num)
{
    number = num;
}

void AnimationItem::onSetTrackInfo(QVector<TrackPointInfo> &Tinfo)
{
    TrackInfo = Tinfo;
}

void AnimationItem::onGetTrackInfo(QVector<TrackPointInfo> &Tinfo)
{
    Tinfo = TrackInfo;
}


void AnimationItem::onSaveAnimatInfo(AnInfo &aninfo)
{
    m_AnimatInfo = aninfo;
}

void AnimationItem::onGetAnimatInfo(AnInfo &aninfo)
{
    aninfo = m_AnimatInfo;
}

int AnimationItem::onGetCurrentNum()
{
    return number;
}

void AnimationItem::SetText(QString sText)
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetText(sText);
    }
}

void AnimationItem::SetFontSize(int nFontSize) //设置字体大小
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->m_font.setPointSize(nFontSize);
        pText->update(pText->m_rect);
    }
}

void AnimationItem::SetFontName(QString sName) //设置字体名称
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->m_font.setFamily(sName);
        pText->update(pText->m_rect);
    }
}

/*****************************************************************************
  函数名称：SetTextAlign(int nAlignType)
  函数意义：设置文本的对齐方式
  参数含义：nAlignType
  nAlignType=1:左上角对齐
  nAlignType=2:上边对齐
  nAlignType=3:右上角对齐
  nAlignType=4:左边对齐
  nAlignType=5:剧中对齐
  nAlignType=6:右边对齐
  nAlignType=7:左下角对齐
  nAlignType=8:下边对齐
  nAlignType=9:右下角对齐
*****************************************************************************/
void AnimationItem::SetTextAlign(int nAlignType)
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
QStringList AnimationItem::getAllFonts()
{
    QStringList ls;
    ls.clear();
    for(int i = 0; i < m_AnimatInfo.Text.size(); i++)
    {
        if(m_AnimatInfo.Text.at(i).sText != "")
        {
            ls << m_AnimatInfo.Text.at(i).sFontFamily;

        }
    }
    return ls;
}

QVector<ADDRPRO> AnimationItem::getAllItemAddr()
{
    lsX.clear();
    ADDRPRO Addr;

    if(0 == m_AnimatInfo.nTrackType && 1 == m_AnimatInfo.nMoveCondition)
    {
        Addr.pAddr = &m_AnimatInfo.mMoveCtrlAddr;
        Addr.str   = QObject::tr("动画移动控制地址");
        Addr.type  = 1;
        lsX << Addr;
    }

    if(1 == m_AnimatInfo.nTrackType)
    {
        //x控制地址
        Addr.pAddr = &m_AnimatInfo.mXPosCtrlAddr;
        Addr.str   = QObject::tr("动画X坐标控制地址");
        Addr.type  = 1;
        lsX << Addr;

        //y控制地址
        Addr.pAddr = &m_AnimatInfo.mYPosCtrlAddr;
        Addr.str   = QObject::tr("动画Y坐标控制地址");
        Addr.type  = 1;
        lsX << Addr;
    }

    if(1 == m_AnimatInfo.nChangeCondition)
    {
        Addr.pAddr = &m_AnimatInfo.mChangeCtrlAddr;
        Addr.str   = QObject::tr("动画状态切换控制地址");
        Addr.type  = 1;
        lsX << Addr;
    }

    QVector<ADDRPRO> AddrList;
    AddrList = QVisableItem::getAllItemAddr();
    for(int i = 0; i < AddrList.size(); i++)
    {
        Addr.pAddr = AddrList.at(i).pAddr;
        Addr.str   = QObject::tr("动画") + AddrList.at(i).str;
        Addr.type  = AddrList.at(i).type;
        lsX << Addr;
    }
    return lsX;
}

void AnimationItem::onGetTrakpos()
{
    QList <QGraphicsItem *> items = childItems();
    QGraphicsItem *group = NULL;
    int nCount = items.size();
    int i = 0;
    QString sName = "";
    int ikey = 0;
    QVector<TrackPointInfo> m_Tinfo;//轨迹点坐标
    m_Tinfo.clear();

    QRectF rc;
    for(i  = 0;i < nCount;i++)
    {
        group = items.at(i);
        sName = group->data(GROUP_NAME_KEY).toString();
        ikey = group->type();

        if(sName == QObject::tr("mMain")) //向量图控件
        {
        }
        else if(ikey == SAM_DRAW_OBJECT_ELIPSE) //记录每个点的位置
        {
            QPointF pos = group->boundingRect().topLeft()+group->scenePos();
            TrackPointInfo TrackPoint;
            TrackPoint.nXPos = pos.x();
            TrackPoint.nYPos = pos.y();
            m_Tinfo.append(TrackPoint);
        }
    }//end for

    for(int i = 0; i < m_Tinfo.size() && i < TrackInfo.size(); i++)
    {
        TrackInfo[i].nXPos = m_Tinfo[i].nXPos;
        TrackInfo[i].nYPos = m_Tinfo[i].nYPos;
    }
}

QString  AnimationItem::getItemName()
{
    return QObject::tr("动画");
}

void AnimationItem::redrawForChangeStatus(int index, int lan)
{
    int totalState = this->getItemStates().size();
    if(totalState <= index)
    {
        return;//目前没有这个状态
    }

    QGraphicsItem *pNewItem = NULL;
    QGraphicsItem *pOldItem = NULL;
    DrawItemToScene GroupFunction;
    if(index >= m_AnimatInfo.PicInfo.size())
    {
        return;
    }
    foreach(QGraphicsItem *pItem,this->childItems())
    {
        if("mMain" == pItem->data(GROUP_NAME_KEY).toString())
        {
            pOldItem = pItem;
            break;
        }
    }
    if(!pOldItem)
    {
        return;
    }
    QRectF rect = pOldItem->sceneBoundingRect();

    QString sPath = m_AnimatInfo.PicInfo.at(index).sPath;
    if(LIBRARY == m_AnimatInfo.PicInfo.at(index).bIspic)
    {
        QList <QGraphicsItem*> listItem;
        QStringList str = sPath.split('-');
        if(str.isEmpty())
        {
            return;
        }
        int nLoadPag = str.at(0).toInt();
        if(pwnd->vBaseLibraryScene.isEmpty())
        {
            return;
        }
        listItem = pwnd->vBaseLibraryScene.at(nLoadPag)->TopItems();
        foreach (QGraphicsItem * pItem, listItem)
        {
            QString sname = pItem->data(GROUP_NAME_KEY).toString();
            if (sPath == sname)
            {
                GroupFunction.CopyItem(&pNewItem,pItem);
                QGroupItem *pBaseItem = new QGroupItem(pNewItem);
                pBaseItem->SetHeigth(rect.height());
                pBaseItem->SetWidth(rect.width());
                break;
            }
        }
    }
    else if(PIC == m_AnimatInfo.PicInfo.at(index).bIspic || USERDEFINE == m_AnimatInfo.PicInfo.at(index).bIspic)
    {
        QPixmap picture = QPixmap(sPath);
        QPixmapItem *PicItem = new QPixmapItem(picture,QSize(rect.width(),rect.height()));
        pNewItem = PicItem;
    }
    if(pNewItem)
    {
        pNewItem->setFlag(QGraphicsItem::ItemIsMovable,true);
        pNewItem->setFlag(QGraphicsItem::ItemIsSelectable,false);
    }
    else
    {
        return;
    }
    QItemGroup *pItemGoup = new QItemGroup;
    pNewItem->setPos(rect.topLeft() - pNewItem->boundingRect().topLeft());
    pItemGoup->addToGroup(pNewItem);
    qDebug()<<"pItemGoup rect:"<<pItemGoup->sceneBoundingRect();
    foreach(QGraphicsItem *pItem,pOldItem->childItems())
    {
        if(SAM_DRAW_OBJECT_TEXT == pItem->type())
        {
            QGraphicsItem *item;
            GroupFunction.CopyItem(&item,pItem);

            QSimpleTextItem *textItem = dynamic_cast<QSimpleTextItem *>(item);
            if(textItem && m_AnimatInfo.Text.size() > index)
            {
                textItem->SetText(m_AnimatInfo.Text.at(index).sText);
            }
            QGroupItem *pBaseItem = new QGroupItem(item);
            pBaseItem->SetHeigth(rect.height());
            pBaseItem->SetWidth(rect.width());
            item->setPos(rect.topLeft() - item->boundingRect().topLeft());
            pItemGoup->addToGroup(item);
            break;
        }
    }
    pItemGoup->setData(GROUP_NAME_KEY,QVariant("mMain"));

   //this->removeFromGroup(pOldItem);

    QGraphicsItem *pItem = this->topLevelItem();
    QItemGroup *pArentItem = dynamic_cast<QItemGroup *> (pItem);
    if(pArentItem)
    {
        pArentItem->removeFromGroup(pOldItem);
    }

    this->addToGroup(pItemGoup);
    if(this->scene())
    {
        this->scene()->removeItem(pOldItem);
    }
    number = index;
}

int AnimationItem::getCurrentState()
{
    return number;
}

QStringList AnimationItem::getItemStates()
{
    QStringList ls;
    ls.clear();
    for(int i = 0; i < m_AnimatInfo.nStateTotal; i++)
    {
        ls.append(QString("%1").arg(i));
    }
    return ls;
}
