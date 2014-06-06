#include "view/keyboarditem.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;
KeyBoardItem::KeyBoardItem()
    :QVisableItem(0)
{
    pBackRect = NULL;
}

QString  KeyBoardItem::getItemName()
{
    return QObject::tr("键盘组件");
}
int KeyBoardItem::GroupType()
{
    return SAM_DRAW_GROUP_KEY;
}

QGraphicsItem *KeyBoardItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    KeyBoardItem *itemGroup = new KeyBoardItem();

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

    itemGroup->m_key=m_key;
    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    itemGroup->SaveSecurityPro(&sPro);
    itemGroup->textItem = itemGroup->GetTextItem();
    itemGroup->pBackRect = itemGroup->getBackItem();
    itemGroup->frameRect = itemGroup->getFarmItem();

    itemGroup->setId(id());

    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }
    return itemGroup;

}

void KeyBoardItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    count++;
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

    count++;
    bool bResult = false;
    QSqlQuery sqlquery(db);
    bResult = sqlquery.prepare("INSERT INTO UDFKkeyBoard(nItemId,nSceneId,nStartX,nStartY,nWidth,"
                     "nHeight,nUpFrameColor,nUpForeColor,nUpBackColor,eUpStyle,"
                     "nDownFrameColor,nDownForeColor,nDownBackColor,eDownStyle,"
                     "eKeyOperation,sText,nFontSize,nFontColor,nFontPro,eFontAlign,"
                     "sImagePath,nShowImage,sASCIIText,sFontFamily)"
                     "VALUES(:nItemId,:nSceneId,:nStartX,:nStartY,:nWidth,"
                     ":nHeight,:nUpFrameColor,:nUpForeColor,:nUpBackColor,:eUpStyle,"
                     ":nDownFrameColor,:nDownForeColor,:nDownBackColor,:eDownStyle,"
                     ":eKeyOperation,:sText,:nFontSize,:nFontColor,:nFontPro,:eFontAlign,"
                     ":sImagePath,:nShowImage,:sASCIIText,:sFontFamily)");
    qDebug()<<"INSERT INTO UDFKkeyBoard"<<bResult;

    sqlquery.bindValue(":nItemId",QVariant(itemId));// 表 id
    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));// scene id
    //相对场景的坐标及高宽
    QRectF rect = sceneBoundingRect();
    QString sw = "";
    QString sh = "";
    sw.setNum(sceneBoundingRect().width(),'f',1);
    sh.setNum(sceneBoundingRect().height(),'f',1);
    sqlquery.bindValue(":nStartX", QVariant(rect.x()));//left
    sqlquery.bindValue(":nStartY", QVariant(rect.y()));//top
    sqlquery.bindValue(":nWidth", QVariant(sw));//width
    sqlquery.bindValue(":nHeight", QVariant(sh));//height
    sqlquery.bindValue(":nUpFrameColor",QVariant(ColorToInt(m_key.nUpFrameColor)));
    sqlquery.bindValue(":nUpForeColor",QVariant(ColorToInt(m_key.nUpForeColor)));
    sqlquery.bindValue(":nUpBackColor",QVariant(ColorToInt(m_key.nUpBackColor)));
    sqlquery.bindValue(":eUpStyle",QVariant(m_key.eUpStyle+1));
    sqlquery.bindValue(":nDownFrameColor",QVariant(ColorToInt(m_key.nDownFrameColor)));
    sqlquery.bindValue(":nDownForeColor",QVariant(ColorToInt(m_key.nDownForeColor)));
    sqlquery.bindValue(":nDownBackColor",QVariant(ColorToInt(m_key.nDownBackColor)));
    sqlquery.bindValue(":eDownStyle",QVariant(m_key.eDownStyle+1));
    sqlquery.bindValue(":eKeyOperation",QVariant(m_key.keyOperation));
    sqlquery.bindValue(":sText",QVariant(m_key.sText));
    sqlquery.bindValue(":nFontSize",QVariant(m_key.nFontSize + 5));
    sqlquery.bindValue(":nFontColor",QVariant(ColorToInt(m_key.sColor)));
    sqlquery.bindValue(":nFontPro",QVariant(m_key.eFontCss));
    int nAlign = 2;
    if(0 == m_key.nPosition)
    {
        nAlign = 2;
    }
    else if(1 == m_key.nPosition)
    {
        nAlign = 1;
    }
    else
    {
        nAlign = 3;
    }
    sqlquery.bindValue(":eFontAlign",QVariant(nAlign));
    QString str = "";
    if("" != m_key.sPath)
    {
        QGraphicsItem *pItem = NULL;
        foreach(QGraphicsItem *item,childItems())
        {
            if("mBackRect" == item->data(GROUP_NAME_KEY).toString())
            {
                pItem = item;
                break;
            }
        }
        if(pItem)
        {
            QString newPath = pwnd->SavePath(m_key.sPath,pItem->boundingRect().size(),!(m_key.bisPic));
            if("" != newPath)
            {
                newPath = newPath.replace("\\","/");
                newPath = newPath.section("/",-1);
                newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
            }
            str = newPath;
            //sqlquery.bindValue(":sImagePath",QVariant(newPath));
        }
    }
    sqlquery.bindValue(":sImagePath",QVariant(str));
    sqlquery.bindValue(":nShowImage",QVariant(1));//////
    sqlquery.bindValue(":sASCIIText",QVariant(m_key.ASCIIStr));
    sqlquery.bindValue(":sFontFamily",QVariant(m_key.sFontFamily));
    sqlquery.exec();
    qDebug()<<"INSERT INTO UDFKkeyBoard end"<<bResult;
}

void KeyBoardItem::save(QDataStream &stream)
{
    QVisableItem::save(stream);

    stream << m_key.nUpFrameColor;
    stream << m_key.nUpForeColor;
    stream << m_key.nUpBackColor;
    stream << m_key.eUpStyle;
    stream << m_key.nDownFrameColor;
    stream << m_key.nDownForeColor;
    stream << m_key.nDownBackColor;
    stream << m_key.eDownStyle;
    int nKeyopera = 0;
    nKeyopera = int(m_key.keyOperation);
    stream << nKeyopera;
    stream << m_key.ASCIIStr;
    stream << m_key.nLanguage;
    stream << m_key.sText;
    stream << m_key.sFontFamily;
    stream << m_key.nFontSize;
    stream << m_key.sColor;
    stream << m_key.eFontCss;
    stream << m_key.nPosition;
    stream << m_key.nPicChecked;
    stream << m_key.bisPic;
    stream << m_key.sPath;
}
void KeyBoardItem::load(QDataStream &stream)
{
    QVisableItem::load(stream);

    stream >> m_key.nUpFrameColor;
    stream >> m_key.nUpForeColor;
    stream >> m_key.nUpBackColor;
    stream >> m_key.eUpStyle;
    stream >> m_key.nDownFrameColor;
    stream >> m_key.nDownForeColor;
    stream >> m_key.nDownBackColor;
    stream >> m_key.eDownStyle;
    int nKeyopera = 0;
    stream >> nKeyopera;
    m_key.keyOperation = (KEY_OPERATION)nKeyopera;
    stream >> m_key.ASCIIStr;
    stream >> m_key.nLanguage;
    stream >> m_key.sText;
    stream >> m_key.sFontFamily;
    stream >> m_key.nFontSize;
    stream >> m_key.sColor;
    stream >> m_key.eFontCss;
    stream >> m_key.nPosition;
    stream >> m_key.nPicChecked;
    stream >> m_key.bisPic;
    stream >> m_key.sPath;

    textItem = GetTextItem();
    pBackRect = getBackItem();
    frameRect = getFarmItem();
}

void KeyBoardItem::onSaveKey(KeyInfo key_st)    //保存流动块显示信息
{
    m_key = key_st;
}

void KeyBoardItem::SetText(QString sText)
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetText(sText);
    }
}

void KeyBoardItem::SetFontSize(int nFontSize) //设置字体大小
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->m_font.setPointSize(nFontSize);
        pText->update(pText->m_rect);
    }
}

void KeyBoardItem::SetFontName(QString sName) //设置字体名称
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
void KeyBoardItem::SetTextAlign(int nAlignType)
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

void KeyBoardItem::SetBackColor(QColor mColor)
{
    QRectItem* pRect = dynamic_cast<QRectItem *>(pBackRect);
    if(pRect)
    {
        pRect->SetBackColor(mColor);
    }
}

void KeyBoardItem::SetFrontColor(QColor mColor)
{
    QRectItem* pRect = dynamic_cast<QRectItem *>(pBackRect);
    if(pRect)
    {
        pRect->SetFrontColor(mColor);
    }
}

void KeyBoardItem::SetPattern(int nPATTERN)
{
    QRectItem* pRect = dynamic_cast<QRectItem *>(pBackRect);
    if(pRect)
    {
        pRect->SetPattern(nPATTERN);
    }
}

void KeyBoardItem::SetFramColor(QColor mColor)
{
    QRectItem* pRect = dynamic_cast<QRectItem *>(frameRect);
    if(pRect)
    {
        pRect->SetBackColor(mColor);
    }
}

QRectItem* KeyBoardItem::getBackItem()
{
    foreach(QGraphicsItem* pItem,childItems())
    {
        if("mBackRect" == pItem->data(GROUP_NAME_KEY).toString())
        {
            return dynamic_cast<QRectItem *> (pItem);
        }
    }
    return NULL;
}

QRectItem* KeyBoardItem::getFarmItem()
{
    foreach(QGraphicsItem* pItem,childItems())
    {
        if("mFramRect" == pItem->data(GROUP_NAME_KEY).toString())
        {
            return dynamic_cast<QRectItem *> (pItem);
        }
    }
    return NULL;
}

void KeyBoardItem::SetFontBold(bool nFlag) //true设置字体为粗体否则不设置
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->m_font.setBold(nFlag);
        pText->update(pText->m_rect);
    }
}

void KeyBoardItem::SetFontItalic(bool nFlag) //true设置字体为斜体否则不设置
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->m_font.setItalic(nFlag);
        pText->update(pText->m_rect);
    }
}

void KeyBoardItem::SetFontUnderLine(bool nFlag) //true设置字体是否有下划线
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->m_font.setUnderline(nFlag);
        pText->update(pText->m_rect);
    }
}

void KeyBoardItem::SetFontColor(QColor color) //设置字体颜色
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->m_FontColor = color;
        pText->update(pText->m_rect);
    }
}

void KeyBoardItem::redrawForChangeStatus(int index, int lan)
{

    if(!m_key.bisPic || "" == m_key.sPath)
    {
        return;
    }

    if(!pBackRect || !textItem || !frameRect)
    {
        return;
    }
    QRectF rect = textItem->sceneBoundingRect();
    QString sPath = m_key.sPath;

    QPixmap picture = QPixmap(sPath);
    if (!picture)
    {
        return ;
    }
    QPixmapItem *PicItem = new QPixmapItem(picture,rect.size().toSize());
    PicItem->setPos(rect.topLeft());
    PicItem->setZValue(3);

    this->removeFromGroup(pBackRect);
    this->removeFromGroup(textItem);
    this->removeFromGroup(frameRect);

    QGraphicsScene *pSence = this->scene();
    if(pSence)
    {
        foreach(QGraphicsItem *pItem,this->childItems())
        {
            this->removeFromGroup(pItem);
            pSence->removeItem(pItem);
        }
    }

    frameRect->setZValue(1);
    pBackRect->setZValue(2);
    textItem->setZValue(5);
    addToGroup(frameRect);
    addToGroup(pBackRect);
    addToGroup(PicItem);
    addToGroup(textItem);
}


