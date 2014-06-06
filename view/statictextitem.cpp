#include "statictextitem.h"
#include "qpixmapitem.h"
#include "Frame/mainwindow.h"
#include "Frame/qprogectmanager.h"

extern MainWindow *pwnd;
StaticTextItem::StaticTextItem()
    :QVisableItem(0)
{

}

QString  StaticTextItem::getItemName()
{
    return QObject::tr("静态文本");
}

int StaticTextItem::GroupType()
{
    return SAM_DRAW_GROUP_STATICTEXT;
}

QGraphicsItem *StaticTextItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    StaticTextItem *itemGroup = new StaticTextItem();

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

    itemGroup->m_text=m_text;
    itemGroup->onSaveText(m_text);

    itemGroup->m_sproperty=m_sproperty;
    itemGroup->SaveSecurityPro(&sPro);

    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    itemGroup->setData(GROUP_TYPE_KEY,data(GROUP_TYPE_KEY).toString());

    itemGroup->setId(id());

    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }
    return itemGroup;

}

void StaticTextItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    count++;
    QColor mColor;
    QVisableItem::compile(db,nSceneId,count,index);
    int itemId = count;
    int langCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();//多语言ListSize

    QString sName = this->data(GROUP_NAME_KEY).toString();//键盘文本关键字
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
    QGraphicsScene *pScene = this->scene();
    SamDrawScene *pSamDramScene = NULL;
    int nIsScene = 0;//0：画面 1：窗口  2:键盘
    if(pScene)
    {
        pSamDramScene = dynamic_cast<SamDrawScene *>(pScene);
    }
    if(pSamDramScene)
    {
        nIsScene = pSamDramScene->nIsSceneOrWindow;
    }

    int nLangId = m_text.nLanguageId;//语言序号
    if(2 == nIsScene)
    {

    }
    else
    {
        QString sFirstPath = "";
        QString path = "";
        QSqlQuery sqlquerys(db);
        bool d=sqlquerys.prepare("INSERT INTO textProp(nItemId,nStatusIndex,nLangIndex,sFont,sText,nSize,nColor,nShowProp)"
                     "VALUES (:nItemId ,:nStatusIndex ,:nLangIndex,:sFont,:sText,:nSize,:nColor,:nShowProp)");
        for(int i = 0; i < langCount; i++)
        {
            this->redrawForChangeLanguage(i);
            if(m_text.bFristLanguage)
            {

                if(0 == i)
                {
                    path = bitShot(i);
                    sFirstPath = path;
                }
                else
                {
                    path = sFirstPath;
                }

            }
            else
            {
                path = bitShot(i);
            }
            sqlquerys.bindValue(":nItemId",QVariant(itemId));// 控件表 id
            sqlquerys.bindValue(":nLangIndex",QVariant(i));// 语言号
            sqlquerys.bindValue(":sText",QVariant(path));
            sqlquerys.bindValue(":nShowProp",QVariant(0));
            sqlquerys.exec();
        }
        this->redrawForChangeLanguage(nLangId);
    }

    QSqlQuery sqlquery(db);
    bool flag=sqlquery.prepare("INSERT INTO staticText(nItemId,nSceneId,sStextStr,sFontFamly,nFontSize,bFristLanguage,"
                     "nLanguageId,eTextPro,sFontSpace,eTextAlign,nFontColor,nStylePadding,"
                     "nAlphaPadding,nBackColorPadding,nForeColorPadding,nStartX,nStartY,nRectWidth,"
                     "nRectHeight,nLineWidth,nLineColor,nZvalue,nCollidindId)"
                     "VALUES(:nItemId,:nSceneId,:sStextStr,:sFontFamly,:nFontSize,:bFristLanguage,"
                     ":nLanguageId,:eTextPro,:sFontSpace,:eTextAlign,:nFontColor,:nStylePadding,"
                     ":nAlphaPadding,:nBackColorPadding,:nForeColorPadding,:nStartX,:nStartY,:nRectWidth,"
                     ":nRectHeight,:nLineWidth,:nLineColor,:nZvalue,:nCollidindId)");
    sqlquery.bindValue(":nItemId",QVariant(itemId));// 表 id
    //如果是键盘上的文本，sceneid为-1
    if("TEXT" == sName || "MIN" == sName || "MAX" == sName){
        sqlquery.bindValue(":nSceneId",QVariant(-1));// scene id
    }else{
        sqlquery.bindValue(":nSceneId",QVariant(nSceneId));// scene id
    }
    //相对场景的坐标及高宽
//    QRectF rect = sceneBoundingRect();
    QRectF rect = boundingRect();
    rect = this->mapRectToScene(rect);
    sqlquery.bindValue(":nStartX", QVariant((short)rect.x()));//left
    sqlquery.bindValue(":nStartY", QVariant((short)rect.y()));//top
    sqlquery.bindValue(":nRectWidth", QVariant((short)rect.width()));//width
    sqlquery.bindValue(":nRectHeight", QVariant((short)rect.height()));//height

    int strLength;
    QString str;
    QVector <QString> stringList;
    //字距
    if(m_text.sFontSpace==0){
        sqlquery.bindValue(":sStextStr",QVariant(m_text.sStextStr));
    }else{
        if(langCount>1)
            strLength=m_text.textList[0].texts.length();
        else
            strLength=m_text.sStextStr.length();
        stringList.resize(strLength);
        for(int i=0;i<strLength;i++){
            if(langCount>1){
                stringList[i]=m_text.textList[0].texts.at(i);
            }else
                stringList[i]=m_text.sStextStr.at(i);

            for(int j=0;j<m_text.sFontSpace/3;j++){
                if(m_text.eTextAlign==2){//向右
                    stringList[i]=stringList[i]+" ";
                }else{
                    if(i==0)
                        stringList[i]=" "+stringList[i]+" ";
                    else
                        stringList[i]=stringList[i]+" ";
                }

            }
            str+=stringList[i];
        }
        sqlquery.bindValue(":sStextStr",QVariant(str));
        str.clear();
    }
    sqlquery.bindValue(":sFontFamly",QVariant(m_text.sFontFamly));
    if(m_text.adaptTexts)
        sqlquery.bindValue(":nFontSize",QVariant(-1));
    else
        sqlquery.bindValue(":nFontSize",QVariant(m_text.sFontSize));
    sqlquery.bindValue(":bFristLanguage",QVariant(m_text.bFristLanguage));
    sqlquery.bindValue(":nLanguageId",QVariant(m_text.nLanguageId));
    sqlquery.bindValue(":eTextPro",QVariant(m_text.eTextPro));
    sqlquery.bindValue(":sFontSpace",QVariant(m_text.sFontSpace));
    int align;
    if(m_text.eTextAlign==0){
        align=2;
    }else if(m_text.eTextAlign==1){
        align=1;
    }else if(m_text.eTextAlign==2){
        align=3;
    }
    sqlquery.bindValue(":eTextAlign",QVariant(align));
    mColor=pwnd->StringTOColor(m_text.nFontColor);
    sqlquery.bindValue(":nFontColor",QVariant(ColorToInt(mColor)));

    sqlquery.bindValue(":nStylePadding",QVariant(m_text.nStylePadding+1));
    sqlquery.bindValue(":nAlphaPadding",QVariant(m_text.nAlphaPadding));

    mColor=pwnd->StringTOColor(m_text.nBackColorPadding);
    sqlquery.bindValue(":nBackColorPadding",QVariant(ColorToInt(mColor)));

    mColor=pwnd->StringTOColor(m_text.nForeColorPadding);
    sqlquery.bindValue(":nForeColorPadding",QVariant(ColorToInt(mColor)));

    sqlquery.bindValue(":nLineWidth",QVariant(1));
    mColor=pwnd->StringTOColor(m_text.nLineColor);
    sqlquery.bindValue(":nLineColor",QVariant(ColorToInt(mColor)));
    sqlquery.bindValue(":nZvalue",QVariant(zValue()));
    sqlquery.bindValue(":nCollidindId",QVariant(index));
    flag=sqlquery.exec();
    return;
}

void StaticTextItem::save(QDataStream &stream)
{
    QVisableItem::save(stream);

    stream << m_text.adaptTexts;//自适应
    stream << m_text.bFristLanguage;//是否选择第一种语言
    stream << m_text.eTextAlign;//位置
    stream << m_text.eTextPro;//文本属性（粗体斜体下划线）
    stream << m_text.nAlphaPadding;//透明色
    stream << m_text.sStextStr;//文本
    stream << m_text.sFontSpace;//字距
    stream << m_text.sFontSize;//字大小
    stream << m_text.nFontColor;//字体颜色
    stream << m_text.sFontFamly;//字样式（宋体）
    stream << m_text.nStylePadding;//样式
    stream << m_text.nForeColorPadding;//前景色
    stream << m_text.nBackColorPadding;//背景色
    stream << m_text.nLanguageId;//语言ID

    stream << m_text.mbolds;
    stream << m_text.mitalics;
    stream << m_text.munderlines;
    stream << m_text.nCollidindId;
    stream << m_text.nFontFamly;
    stream << m_text.nFontSize;
    stream << m_text.nHeight;
    stream << m_text.nStartX;
    stream << m_text.nStartY;
    stream << m_text.nWidth;
    stream << m_text.nZvalue;

    int list=m_text.textList.size();
    stream << list;
    for(int i=0;i<list;i++){
        stream << m_text.textList[i].adapts;
        stream << m_text.textList[i].bolds;
        stream << m_text.textList[i].fontIndexs;
        stream << m_text.textList[i].fonts;
        stream << m_text.textList[i].fontSizeIndexs;
        stream << m_text.textList[i].fontSizes;
        stream << m_text.textList[i].italics;
        stream << m_text.textList[i].nFontColors;
        stream << m_text.textList[i].TextAlignIndexs;
        stream << m_text.textList[i].underlines;
        stream << m_text.textList[i].texts;
        stream << m_text.textList[i].newColor;
    }
}
void StaticTextItem::load(QDataStream &stream)
{
    QVisableItem::load(stream);

    stream >> m_text.adaptTexts;
    stream >> m_text.bFristLanguage;
    stream >> m_text.eTextAlign;
    stream >> m_text.eTextPro;
    stream >> m_text.nAlphaPadding;
    stream >> m_text.sStextStr;
    stream >> m_text.sFontSpace;
    stream >> m_text.sFontSize;
    stream >> m_text.nFontColor;
    stream >> m_text.sFontFamly;
    stream >> m_text.nStylePadding;
    stream >> m_text.nForeColorPadding;
    stream >> m_text.nBackColorPadding;
    stream >> m_text.nLanguageId;

    stream >> m_text.mbolds;
    stream >> m_text.mitalics;
    stream >> m_text.munderlines;
    stream >> m_text.nCollidindId;
    stream >> m_text.nFontFamly;
    stream >> m_text.nFontSize;
    stream >> m_text.nHeight;
    stream >> m_text.nStartX;
    stream >> m_text.nStartY;
    stream >> m_text.nWidth;
    stream >> m_text.nZvalue;

    int list=0;
    stream >> list;
    m_text.textList.resize(list);
    for(int i=0;i<list;i++){
        stream >> m_text.textList[i].adapts;
        stream >> m_text.textList[i].bolds;
        stream >> m_text.textList[i].fontIndexs;
        stream >> m_text.textList[i].fonts;
        stream >> m_text.textList[i].fontSizeIndexs;
        stream >> m_text.textList[i].fontSizes;
        stream >> m_text.textList[i].italics;
        stream >> m_text.textList[i].nFontColors;
        stream >> m_text.textList[i].TextAlignIndexs;
        stream >> m_text.textList[i].underlines;
        stream >> m_text.textList[i].texts;
        if (pwnd->getProVersion() < 2052)
        {
            m_text.textList[i].newColor=pwnd->ColorTOString(QColor(0,0,0));
        }
        else
        {
            stream >> m_text.textList[i].newColor;
        }
    }
}

void StaticTextItem::onSaveText(TextInfos text)    //保存静态文本显示信息
{
    m_text = text;
}

void StaticTextItem::onSecurityPro(securityPro sproperty)
{
    m_sproperty=sproperty;
}

void StaticTextItem::redrawForChangeLanguage(int index)
{
    if(index >= m_text.textList.size()){
        return;
    }
//    if(m_text.isText){
        //pTEXT=new QSimpleTextItem();

        QGroupItem* pCopyBaseItem = new QGroupItem(this);
        int curLan = index;//pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan;
        if(m_text.bFristLanguage)
        {
            curLan = 0;
        }

        pCopyBaseItem->SetPropertyValue("mText.bFitSize",QVariant(m_text.textList[curLan].adapts));//自适应
        pCopyBaseItem->SetPropertyValue("mText.Text",QVariant(m_text.textList[curLan].texts));//文本
        pCopyBaseItem->SetPropertyValue("mText.FontSize",QVariant(m_text.textList[curLan].fontSizes));//字体大小
        QString str = pwnd->ColorTOString(m_text.textList[curLan].nFontColors);
        pCopyBaseItem->SetPropertyValue("mText.FontColor",QVariant(str));//字体颜色
        pCopyBaseItem->SetPropertyValue("mBackRect.Pattern",QVariant(m_text.nStylePadding));//样式
        pCopyBaseItem->SetPropertyValue("mText.FontBold",QVariant(m_text.textList[curLan].bolds));//粗体
        pCopyBaseItem->SetPropertyValue("mText.FontItalic",QVariant(m_text.textList[curLan].italics));//斜体
        pCopyBaseItem->SetPropertyValue("mText.UnderLine",QVariant(m_text.textList[curLan].underlines));//下划线
        pCopyBaseItem->SetPropertyValue("mText.Alignment",QVariant(m_text.textList[curLan].TextAlignIndexs));//位置
        str = pwnd->ColorTOString(m_text.nForeColorPadding);
        pCopyBaseItem->SetPropertyValue("mBackRect.FrontColor",QVariant(str));//前景色
        str = pwnd->ColorTOString(m_text.nBackColorPadding);
        pCopyBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(str));//背景色

        pCopyBaseItem->SetPropertyValue("mText.Font",QVariant(m_text.textList[curLan].fonts));//字体
}

TEXTPRO  StaticTextItem::getAllItemText()
{
    int iStaCount = 1; //总状态数目
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
            vText.vMsg.append(QObject::tr("文本内容:"));
            vText.vText.append(m_text.textList[i].texts);
        }
    }
    return vText;
}

void StaticTextItem::replaceAllItemText(int iLan, int iSta, QString sNewText)
{
    int iL = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //多语言总数
    if( iLan >= 0 && iLan < iL)
    {
        m_text.textList[iLan].texts = sNewText;
    }
}

void StaticTextItem::changeItemLanguageAttr(int lanNum)
{
    int itemLanNum  = m_text.textList.size();

    if(lanNum > itemLanNum)//需要增加语言数
    {
            TextItemLists addItem;
            if(m_text.bFristLanguage)
            {
                for(int j = itemLanNum; j < lanNum; j++)
                {
                    addItem.adapts    = m_text.textList[0].adapts;
                    addItem.bolds     = m_text.textList[0].bolds;
                    addItem.fontIndexs     = m_text.textList[0].fontIndexs;
                    addItem.fonts  = m_text.textList[0].fonts;
                    addItem.fontSizeIndexs     = m_text.textList[0].fontSizeIndexs;
                    addItem.fontSizes = m_text.textList[0].fontSizes;
                    addItem.italics=m_text.textList[0].italics;
                    addItem.nFontColors=m_text.textList[0].nFontColors;
                    addItem.TextAlignIndexs=m_text.textList[0].TextAlignIndexs;
                    addItem.texts=m_text.textList[0].texts;
                    addItem.underlines=m_text.textList[0].underlines;
                    m_text.textList.push_back(addItem);
                }
            }
            else
            {
                for(int j = itemLanNum; j < lanNum; j++)
                {
                    addItem.adapts    = false;
                    addItem.bolds     = false;
                    addItem.fontIndexs     = 51;
                    addItem.fonts  = "Droid Sans Fallback";
                    addItem.fontSizeIndexs     = 5;
                    addItem.fontSizes = 10;
                    addItem.italics   = false;
                    addItem.nFontColors=QColor(0,0,0).name();
                    addItem.TextAlignIndexs=0;
                    addItem.texts="TEXT";
                    addItem.underlines=false;
                    m_text.textList.push_back(addItem);
                }
            }
    }
    else if(lanNum < itemLanNum)//需要删除语言
    {
        for(int j = itemLanNum - 1; j >= lanNum; j--)
        {
            m_text.textList.remove(j);
        }
    }
}
QStringList StaticTextItem::getAllFonts()
{
	QStringList ls;
	ls.clear();
        QString sName = this->data(GROUP_NAME_KEY).toString();//键盘文本关键字
        if("TEXT" == sName || "MIN" == sName || "MAX" == sName)
        {
            foreach(TextItemLists textPro,m_text.textList)
            {
                if(!textPro.fonts.isEmpty() && !textPro.texts.isEmpty())
                {
                    ls << textPro.fonts;
                }
            }
            return ls;
        }
        else
        {
            return ls;
        }
}

QString StaticTextItem::bitShot(int id)
{
        QString path;
        QGraphicsScene tmpScene;
        QGraphicsItem *item = Clone();
        if (!item)
        {
                return path;
        }
        tmpScene.addItem(item);
        QRectF rect = item->sceneBoundingRect();

        QPixmap pixmap(rect.width(),rect.height());
        pixmap.fill(QColor(0,0,0,0));
        QPainter painter(&pixmap);

        QRectF target = QRectF(0,0,rect.width(),rect.height());
        rect = QRectF(rect.x(),rect.y(),rect.width()+1,rect.height()+1);
        tmpScene.render(&painter,target,rect,Qt::IgnoreAspectRatio);

        QString date = QDateTime::currentDateTime().toString("yyMMddhhmmss");
        date  =  date + QString::number(id);
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
        newpath = proName+"/"+date+"_"+newpath+".png";
        if (picture.save(newpath,"PNG"))
        {
                newpath = newpath.replace("\\","/");
                newpath = newpath.section("/",-1);
                newpath = "/data/data/com.android.Samkoonhmi/pictures/"+newpath;
                path = newpath;
        }
        return path;
}
