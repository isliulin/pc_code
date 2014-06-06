#include "qhistorydatashowattr.h"

extern MainWindow *pwnd;

QHistoryDataShowAttr::QHistoryDataShowAttr(QGraphicsItem *parent):QVisableItem(parent)//QItemGroup(parent)
{
}

QHistoryDataShowAttr::~QHistoryDataShowAttr()
{
}

int QHistoryDataShowAttr::GroupType()                //控件类型 位开关 字开关
{
    return SAM_DRAW_GROUP_HISTORYDATE;
}

QHistoryDataShowAttr* QHistoryDataShowAttr::Clone()            //复制item
{
    QGraphicsItem* pCopy = NULL;
    QGraphicsItem* pItem = NULL;

    QHistoryDataShowAttr *itemGroup = new QHistoryDataShowAttr;

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

    itemGroup->m_nForecolor     = m_nForecolor;
    itemGroup->m_nFrameColor    = m_nFrameColor;
    itemGroup->m_nAlpha         = m_nAlpha;
    //--------------
    itemGroup->m_nTextFontSize  = m_nTextFontSize;
    itemGroup->m_nLine          = m_nLine;
    itemGroup->m_nTextFontColor = m_nTextFontColor;
    //--------------
    itemGroup->m_bShowTime      = m_bShowTime;
    itemGroup->m_bShowDate      = m_bShowDate;
    itemGroup->m_nTitleBackColor= m_nTitleBackColor;
    itemGroup->m_nTitleFontColor= m_nTitleFontColor;
    itemGroup->m_bShowCode      = m_bShowCode;
    itemGroup->m_eTimeFormat    = m_eTimeFormat;
    itemGroup->m_eDateFormat    = m_eDateFormat;
    itemGroup->m_bAddr          = m_bAddr;
    itemGroup->m_KeyAddr        = m_KeyAddr;
    itemGroup->sGroupName       = sGroupName;
    //--------------
    itemGroup->m_vecHisText     = m_vecHisText;
    //数据
    itemGroup->m_vecHisData     = m_vecHisData;
    itemGroup->setId(id());

    return itemGroup;
}

void QHistoryDataShowAttr::compile(QSqlDatabase &db, int nSceneId, int &count, int index)//编译的时候保存item到数据库
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
    bool r1 = sqlquery.prepare("INSERT INTO historyShow(nItemId,nSceneId,nAlpha,sGroupName,"
                          "nForecolor,nFrameColor,nTitleBackColor,nTitleFontColor,"
                          "bShowTime,eTimeFormat,bShowDate,eDateFormat,bShowCode,"
                          "nTextFontSize,nTextFontColor,nLine,nLeftTopX,nLeftTopY,"
                          "nWidth,nHeight,nZvalue,nCollidindId,nShowPropId,bAddr,mAddress)"
                          "VALUES(:nItemId,:nSceneId,:nAlpha,:sGroupName,"
                          ":nForecolor,:nFrameColor,:nTitleBackColor,:nTitleFontColor,"
                          ":bShowTime,:eTimeFormat,:bShowDate,:eDateFormat,:bShowCode,"
                          ":nTextFontSize,:nTextFontColor,:nLine,:nLeftTopX,:nLeftTopY,"
                          ":nWidth,:nHeight,:nZvalue,:nCollidindId,:nShowPropId,:bAddr,:mAddress)");
    qDebug() << r1;

    sqlquery.bindValue(":nItemId", QVariant(itemId));                //表id
    sqlquery.bindValue(":nSceneId", QVariant(nSceneId));            //scene id
    sqlquery.bindValue(":nAlpha", QVariant(m_nAlpha));
    int color;
    int temp = 0;
    sqlquery.bindValue(":sGroupName", QVariant(sGroupName));
    color = ColorToInt(m_nForecolor);
    sqlquery.bindValue(":nForecolor", QVariant(color));
    color = ColorToInt(m_nFrameColor);
    sqlquery.bindValue(":nFrameColor", QVariant(color));
    color = ColorToInt(m_nTitleBackColor);
    sqlquery.bindValue(":nTitleBackColor", QVariant(color));
    color = ColorToInt(m_nTitleFontColor);
    sqlquery.bindValue(":nTitleFontColor", QVariant(color));
    sqlquery.bindValue(":bShowTime", QVariant(m_bShowTime));
    temp = (int)m_eTimeFormat;
    sqlquery.bindValue(":eTimeFormat", QVariant(temp));
    sqlquery.bindValue(":bShowDate", QVariant(m_bShowDate));
    temp = (int)m_eDateFormat;
    sqlquery.bindValue(":eDateFormat", QVariant(temp));
    sqlquery.bindValue(":bShowCode", QVariant(m_bShowCode));
    sqlquery.bindValue(":nTextFontSize", QVariant(m_nTextFontSize));
    color = ColorToInt(m_nTextFontColor);
    sqlquery.bindValue(":nTextFontColor", QVariant(color));
    sqlquery.bindValue(":nLine", QVariant(m_nLine));
    QRectF rect = sceneBoundingRect();//相对场景的坐标及高宽
    sqlquery.bindValue(":nTopLeftX", QVariant((short)rect.left()));//left
    sqlquery.bindValue(":nTopLeftY", QVariant((short)rect.top()));//top
    sqlquery.bindValue(":nWidth", QVariant((short)rect.width()));//width
    sqlquery.bindValue(":nHeight", QVariant((short)rect.height()));//height
    sqlquery.bindValue(":nZvalue", QVariant(zValue()));
    sqlquery.bindValue(":nCollidindId", QVariant(index));
    sqlquery.bindValue(":nShowPropId", QVariant(0));
    sqlquery.bindValue(":bAddr", QVariant(m_bAddr));
    if(m_bAddr)
    {
        int kk = count;
        kk++;
        sqlquery.bindValue(":mAddress", QVariant(kk));
    }
    else
    {
        sqlquery.bindValue(":mAddress", QVariant(-1));
    }

    bool result = sqlquery.exec();
    qDebug() << result << endl;

    bool r2 = sqlquery.prepare("INSERT INTO historyShowText(nItemId,nLanguageId,"
                    "nTitleFontSize,sTitleFontType,sTitleTimeName,sTitleDateName,sTitleNumber)"
                    "VALUES(:nItemId,:nLanguageId,"
                    ":nTitleFontSize,:sTitleFontType,:sTitleTimeName,:sTitleDateName,:sTitleNumber)");
    qDebug() << r2;

    int textNum = m_vecHisText.size();
    for(int i = 0; i < textNum; i++)
    {
        sqlquery.bindValue(":nItemId", QVariant(itemId));
        sqlquery.bindValue(":nLanguageId", QVariant(m_vecHisText[i].m_nTitleLanguage));
        sqlquery.bindValue(":nTitleFontSize", QVariant(m_vecHisText[i].m_nTitleFontSize));
        sqlquery.bindValue(":sTitleFontType", QVariant(m_vecHisText[i].m_sTitleFontType));
        sqlquery.bindValue(":sTitleTimeName", QVariant(m_vecHisText[i].m_sTitleTimeName));
        sqlquery.bindValue(":sTitleDateName", QVariant(m_vecHisText[i].m_sTitleDateName));
        sqlquery.bindValue(":sTitleNumber", QVariant(m_vecHisText[i].m_sTitleNumber));

        result = sqlquery.exec();
        qDebug() << "------sub:" << result << endl;
    }

    bool r3 = sqlquery.prepare("INSERT INTO historyShowData(nItemId,nLanguageId,"
                               "nCode,sTitleDataName,bShowTitleDataName)"
                               "VALUES(:nItemId,:nLanguageId,"
                               ":nCode,:sTitleDataName,:bShowTitleDataName)");
    qDebug() << r3;

    int dataNum = m_vecHisData.size();
    int itemNum = 0;
    for(int i = 0; i < dataNum; i++)
    {
        itemNum = m_vecHisData[i].m_vecInfo.size();
        for(int j = 0; j < itemNum; j++)
        {
            sqlquery.bindValue(":nItemId", QVariant(itemId));
            sqlquery.bindValue(":nLanguageId", QVariant(m_vecHisData[i].m_nLanguage));
            sqlquery.bindValue(":nCode", QVariant(j));
            sqlquery.bindValue(":sTitleDataName", QVariant(m_vecHisData[i].m_vecInfo[j].m_strName));
            sqlquery.bindValue(":bShowTitleDataName", QVariant(m_vecHisData[i].m_vecInfo[j].m_bShow));

            result = sqlquery.exec();
            qDebug() << "---sub:" << result << endl;
        }
    }

    QList<QGraphicsItem *> list = childItems();
    QString sName = "";

    QVector<qreal> vVLine;              //用来存垂直线的数据
    QVector<qreal> vHLine;             //用来存水平线的数据
    vVLine.clear();
    vHLine.clear();
    vVLine.append(rect.x());
    vHLine.append(rect.y());
    //vTileTex.clear();

    foreach(QGraphicsItem *pItem,list)
    {
        QPointF pos = pItem->boundingRect().topLeft()+pItem->scenePos();
        sName = pItem->data(GROUP_NAME_KEY).toString();
        if(sName.contains("VLine")) //垂直线
        {
            vVLine.append(pos.x());
        }
        if(sName.contains("HLine")) //水平线
        {
            vHLine.append(pos.y());
        }
    }

    for(int i = 0; i < vVLine.size(); i++)
    {
        for(int j = i + 1; j < vVLine.size(); j++)
        {
            if(vVLine.at(i) > vVLine.at(j))
            {
                qreal odata;
                odata = vVLine.at(i);
                vVLine.replace(i,vVLine.at(j));
                vVLine.replace(j,odata);
            }
        }
    }
    vVLine.append(rect.x() + rect.width());
    for(int i = 0; i < vVLine.size() - 1; i++)
    {
        //qDebug()<<"i:"<<i<<"pos:"<<vVLine.at(i);
        sqlquery.prepare("INSERT INTO tableProp(nItemId,nIsRow,nNo,nWidth)"
                                    "VALUES (:nItemId,:nIsRow,:nNo,:nWidth)");
            sqlquery.bindValue(":nItemId",QVariant(itemId));
            sqlquery.bindValue(":nIsRow",QVariant(0));
            sqlquery.bindValue(":nNo",QVariant(i));
            sqlquery.bindValue(":nWidth",QVariant(vVLine.at(i + 1) - vVLine.at(i)));
            sqlquery.exec();
    }

    //横直线
    for(int i = 0; i < vHLine.size(); i++)
    {
        for(int j = i + 1; j < vHLine.size(); j++)
        {
            if(vHLine.at(i) > vHLine.at(j))
            {
                qreal odata;
                odata = vHLine.at(i);
                vHLine.replace(i,vHLine.at(j));
                vHLine.replace(j,odata);
            }
        }
    }
    vHLine.append(rect.y() + rect.height());
    for(int i = 0; i < vHLine.size() - 1; i++)
    {
        //qDebug()<<"i:"<<i<<"pos:"<<vHLine.at(i);
        sqlquery.prepare("INSERT INTO tableProp(nItemId,nIsRow,nNo,nWidth)"
                                    "VALUES (:nItemId,:nIsRow,:nNo,:nWidth)");
            sqlquery.bindValue(":nItemId",QVariant(itemId));
            sqlquery.bindValue(":nIsRow",QVariant(1));
            sqlquery.bindValue(":nNo",QVariant(i));
            sqlquery.bindValue(":nWidth",QVariant(vHLine.at(i + 1) - vHLine.at(i)));
            sqlquery.exec();
    }

    if(m_bAddr)
    {
        int kk = count;
        count++;
        ADDR_PARAMENTS stParams;
        stParams.id         = count;
        stParams.itemId     = itemId;
        stParams.eType      = OBJ_ITEM;
        stParams.eRWtype    = SCENE_CONTROL_LOOP_R;
        stParams.addrNum    = -1;
        m_KeyAddr.Length    = 13;
        m_KeyAddr.compile(db,stParams);
    }
}

void QHistoryDataShowAttr::save(QDataStream &stream) //将item存入数据流
{
    QVisableItem::save(stream);
    stream << m_nForecolor;
    stream << m_nFrameColor;
    stream << m_nAlpha;
    stream << m_nTextFontSize;
    stream << m_nLine;
    stream << m_nTextFontColor;
    stream << m_bShowTime;
    stream << m_bShowDate;
    stream << m_nTitleBackColor;
    stream << m_nTitleFontColor;
    stream << m_bShowCode;
    stream << (int)m_eTimeFormat;
    stream << (int)m_eDateFormat;
    stream << this->m_bAddr;
    stream << this->m_KeyAddr;
    stream << sGroupName;

    int list=0;
    list=m_vecHisText.size();
    stream << list;
    for(int i=0;i<list;i++){
        stream << m_vecHisText[i].m_nTitleFontSize;
        stream << m_vecHisText[i].m_nTitleLanguage;
        stream << m_vecHisText[i].m_sTitleDateName;
        stream << m_vecHisText[i].m_sTitleFontType;
        stream << m_vecHisText[i].m_sTitleTimeName;
        stream << m_vecHisText[i].m_sTitleNumber;
    }

    list=m_vecHisData.size();
    stream << list;
    for(int i=0;i<list;i++){
        stream << m_vecHisData[i].m_nLanguage;
        int veclist= m_vecHisData[i].m_vecInfo.size();
        stream << veclist;
        for(int j=0;j<veclist;j++){
            stream << m_vecHisData[i].m_vecInfo[j].m_bShow;
            stream << m_vecHisData[i].m_vecInfo[j].m_strName;
        }
    }
}

void QHistoryDataShowAttr::load(QDataStream &stream) //从数据流导出item
{
    QVisableItem::load(stream);
    int temp=0;
    stream >> m_nForecolor;
    stream >> m_nFrameColor;
    stream >> m_nAlpha;
    stream >> m_nTextFontSize;
    stream >> m_nLine;
    stream >> m_nTextFontColor;
    stream >> m_bShowTime;
    stream >> m_bShowDate;
    stream >> m_nTitleBackColor;
    stream >> m_nTitleFontColor;
    stream >> m_bShowCode;
    stream >> temp;
    m_eTimeFormat=(TIME_FORMAT)temp;
    stream >> temp;
    m_eDateFormat=(DATE_FORMAT)temp;
    if(pwnd->getProVersion() < 3087)//旧版本
    {
        this->m_bAddr = false;
        //this->m_KeyAddr;
    }
    else
    {
        stream >> this->m_bAddr;
        stream >> this->m_KeyAddr;
    }

    stream >> sGroupName;

    int list=0;
    stream >> list;
    m_vecHisText.resize(list);;
    for(int i=0;i<list;i++){
        stream >> m_vecHisText[i].m_nTitleFontSize;
        stream >> m_vecHisText[i].m_nTitleLanguage;
        stream >> m_vecHisText[i].m_sTitleDateName;
        stream >> m_vecHisText[i].m_sTitleFontType;
        stream >> m_vecHisText[i].m_sTitleTimeName;
        stream >> m_vecHisText[i].m_sTitleNumber;
    }

    stream >> list;
    m_vecHisData.resize(list);;
    for(int i=0;i<list;i++){
        stream >> m_vecHisData[i].m_nLanguage;
        int veclist=0;
        stream >> veclist;
        m_vecHisData[i].m_vecInfo.resize(veclist);
        for(int j=0;j<veclist;j++){
            stream >> m_vecHisData[i].m_vecInfo[j].m_bShow;
            stream >> m_vecHisData[i].m_vecInfo[j].m_strName;
        }
    }
}

TEXTPRO QHistoryDataShowAttr::getAllItemText()
{
    //  int iStaCount = 1; //总状态数目
      int iLan = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //多语言总数

      vText.sCtrlName = this->getItemName(); //控件名称
      vText.iLanguage.clear();
      vText.vStatus.clear();
      vText.vText.clear();
      vText.vMsg.clear();

      for(int i = 0; i < iLan; i++) //总的语言扫描
      {
          for(int j = 0; j < 3; j++)
              vText.iLanguage.append(i);

          vText.vStatus.append(10000);
          vText.vMsg.append(QObject::tr("序号:"));
          vText.vText.append(m_vecHisText[i].m_sTitleNumber);

          vText.vStatus.append(10001);
          vText.vMsg.append(QObject::tr("时间:"));
          vText.vText.append(m_vecHisText[i].m_sTitleTimeName);

          vText.vStatus.append(10002);
          vText.vMsg.append(QObject::tr("日期:"));
          vText.vText.append(m_vecHisText[i].m_sTitleDateName);

          if(m_vecHisData.size() != 0) //存数据项条目
          {
              int temp = m_vecHisData[i].m_vecInfo.size();
              for(int k = 0; k < temp; k++)
              {
                  vText.iLanguage.append(i);
                  vText.vStatus.append(k);
                  vText.vMsg.append(QObject::tr("数据:")+QString("%1").arg(k));
                  vText.vText.append(m_vecHisData[i].m_vecInfo[k].m_strName);
              }
          }
      }
      return vText;
}

void QHistoryDataShowAttr::replaceAllItemText(int iLan, int iSta, QString sNewText)
{
    int iL = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //多语言总数

    if( iLan >= 0 && iLan < iL)
    {
        if(iSta == 10000)
            m_vecHisText[iLan].m_sTitleNumber = sNewText;
        else if(iSta == 10001)
            m_vecHisText[iLan].m_sTitleTimeName = sNewText;
        else if(iSta == 10002)
            m_vecHisText[iLan].m_sTitleDateName = sNewText;
        else if(iSta >= 0 && iSta < 10000)
        {
            m_vecHisData[iLan].m_vecInfo[iSta].m_strName = sNewText;
        }
    }
}

void QHistoryDataShowAttr::redrawForChangeLanguage(int index)
{
    //画标题文本
    QStringList sDataName;
    sDataName.clear();
    int iLan = index;//pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan;

    if(this->m_bShowCode)
    {
        QString sNum  = m_vecHisText[iLan].m_sTitleNumber;
        sDataName.append(sNum);
    }
    if(m_bShowTime)
    {
        QString sTime = m_vecHisText[iLan].m_sTitleTimeName;   //以语言1显示时间内容
        sDataName.append(sTime);
    }
    if(m_bShowDate)
    {
        QString sDate = m_vecHisText[iLan].m_sTitleDateName;   //以语言1显示日期内容
        sDataName.append(sDate);
    }

    int XXX  = 0;
    if(m_vecHisData.size() != 0)
    {
        int temp = m_vecHisData[iLan].m_vecInfo.size();

        for(int i = 0; i < temp; i++)
        {
            if(m_vecHisData[iLan].m_vecInfo[i].m_bShow) //显示条数计数
            {
                XXX++;
                if(XXX > 3)
                {
                    sDataName.append(QObject::tr("..."));
                    break;
                }
                else
                {
                    sDataName.append(m_vecHisData[iLan].m_vecInfo[i].m_strName);
                }
            }
        }
    }

    QGraphicsItem* pItem = NULL;
    QList<QGraphicsItem *> itemList;
    itemList = childItems();
    int size = itemList.size();
    int k = 0;

    for(int i=0;i<size;i++)
    {
        pItem = itemList.at(i);

        switch(pItem->type())
        {
            case SAM_DRAW_OBJECT_TEXT://一个一个的取出文本
            {
                QSimpleTextItem* textItem = dynamic_cast<QSimpleTextItem *>(pItem);
                if(textItem)
                {
                    qDebug() << textItem->GetText();
                    textItem->SetText(sDataName.at(k));
                    textItem->SetFontName(m_vecHisText[iLan].m_sTitleFontType);
                    textItem->SetFontSize(m_vecHisText[iLan].m_nTitleFontSize);
                    k++;
                    if(k >= sDataName.size())
                    {
                        return;
                    }
                }
            }
            break;

            default:
            break;
        }
    }
}

void QHistoryDataShowAttr::changeItemLanguageAttr(int lanNum)
{
    int textNum = m_vecHisText.size();
    int dataNum = m_vecHisData.size();
    //if(textNum != dataNum)
    //{
        //QMessageBox::about(this, QObject::tr("错误"), QObject::tr("textNum != dataNum"));
    //    return;
    //}

    if(lanNum > textNum)
    {
        HistoryTextInfo txtInfo;
        HistoryDataInfo datInfo;
        dataInfo        subInfo;
        for(int i = textNum; i < lanNum; i++)
        {
            txtInfo.m_nTitleFontSize = 10;
            txtInfo.m_nTitleLanguage = i;
            txtInfo.m_sTitleDateName = QObject::tr("日期");
            txtInfo.m_sTitleFontType = QObject::tr("Droid Sans Fallback");
            txtInfo.m_sTitleTimeName = QObject::tr("时间");
            txtInfo.m_sTitleNumber   = QObject::tr("序号");

            m_vecHisText.push_back(txtInfo);

            if(dataNum != 0)
            {
                datInfo.m_nLanguage = i;
                int num = m_vecHisData[0].m_vecInfo.size();
                for(int j = 0; j < num; j++)
                {
                    subInfo.m_nSampNum  = m_vecHisData[0].m_vecInfo[j].m_nSampNum;
                    subInfo.m_kb        = m_vecHisData[0].m_vecInfo[j].m_kb;
                    subInfo.m_bShow     = true;
                    subInfo.m_strName   = QString::number(m_vecHisData[0].m_vecInfo[j].m_nSampNum);
                    datInfo.m_vecInfo.push_back(subInfo);
                }
                m_vecHisData.push_back(datInfo);
                datInfo.m_vecInfo.clear();
            }
        }
    }
    else if(lanNum < textNum)
    {
        for(int i = textNum - 1; i >= lanNum; i--)
        {
            m_vecHisText.remove(i);
            if(dataNum != 0)
            {
                m_vecHisData.remove(i);
            }
        }
    }
}

QStringList QHistoryDataShowAttr::getAllFonts()
{
    QStringList ls;
    ls.clear();

    foreach(HistoryTextInfo textPro, m_vecHisText)
    {
        if(!textPro.m_sTitleFontType.isEmpty())
        {
            ls << textPro.m_sTitleFontType;
        }
    }

    return ls;
}

QString  QHistoryDataShowAttr::getItemName()
{
    return QObject::tr("历史数据显示器");
}

void QHistoryDataShowAttr::sampChanged(QString oldName,QString newName,int sampType)
{
	/*//一般
    QColor  m_nForecolor;       //前景色
    QColor  m_nFrameColor;      //边框色
    short   m_nAlpha;
    //---------------
    short   m_nTextFontSize;    //文本字体大小，默认10
    short   m_nLine;            //显示行数，默认5
    QColor  m_nTextFontColor;   //文本字体颜色，默认黑色
    //---------------
    bool    m_bShowTime;	//是否显示时间，默认显示
    bool    m_bShowDate;	//是否显示日期,默认显示
    QColor  m_nTitleBackColor;	//标题背景颜色，默认黄色
    QColor  m_nTitleFontColor;	//标题字体颜色，默认黑色
    bool    m_bShowCode;        //是否显示编号
    TIME_FORMAT	m_eTimeFormat;  //(统一时间格式枚举)时间格式 HH:MM
    DATE_FORMAT	m_eDateFormat;  //(统一时间格式枚举)日期格式 默认：DD/MM/YY
    QString     sGroupName;         //组名
    //---------------
    QVector<HistoryTextInfo> m_vecHisText;//每种语言对应的表里内容的字体属性
    //数据
    QVector<HistoryDataInfo> m_vecHisData;*/
    if((1 == sampType) && (oldName == sGroupName))//类型改变,sampType=1实时曲线
    {
        sGroupName  = "";
        m_bShowTime = true;
        m_bShowDate = true;
        m_bShowCode = true;
        m_vecHisData.clear();
    }
    if((oldName != newName) && (oldName == sGroupName))//名字改变
    {
        sGroupName = newName;
    }

    if(2 == sampType)
    {
        int num  = pwnd->m_pSamSysParame->m_loadDataSampling.size();
        for(int k = 0; k < num; k++)
        {
            //if(sGroupName == newName)
            if(pwnd->m_pSamSysParame->m_vecDataSamplingStr[k] == sGroupName)
            {
                m_vecHisData.clear();
                int lanNum  = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
                int itemNum = pwnd->m_pSamSysParame->m_loadDataSampling[k].m_dataTable.size();

                HistoryDataInfo info;
                dataInfo        item;
                for(int i = 0; i < lanNum; i++)
                {
                    info.m_nLanguage = i;
                    for(int j = 0; j < itemNum; j++)
                    {
                        item.m_kb       = pwnd->m_pSamSysParame->m_loadDataSampling[k].m_dataTable[j].keyAddress;
                        item.m_nSampNum = pwnd->m_pSamSysParame->m_loadDataSampling[k].m_dataTable[j].nAddrNumber;
                        item.m_bShow    = true;
                        item.m_strName  = QString::number(pwnd->m_pSamSysParame->m_loadDataSampling[k].m_dataTable[j].nAddrNumber);
                        info.m_vecInfo.push_back(item);
                    }
                    m_vecHisData.push_back(info);
                    info.m_vecInfo.clear();
                }

                //add  sortHisData();
                int numX = 0;
                dataInfo temp;
                for(int m = 0; m < lanNum; m++)
                {
                    numX = m_vecHisData[m].m_vecInfo.size();
                    if(numX <= 1)
                    {
                        continue;
                    }
                    for(int n = 0; n < numX - 1; n++)
                    {
                        for(int x = n + 1; x < numX; x++)
                        {
                            if(m_vecHisData[m].m_vecInfo[n].m_nSampNum > m_vecHisData[m].m_vecInfo[x].m_nSampNum)
                            {
                                temp = m_vecHisData[m].m_vecInfo[n];
                                m_vecHisData[m].m_vecInfo[n] = m_vecHisData[m].m_vecInfo[x];
                                m_vecHisData[m].m_vecInfo[x] = temp;
                            }
                        }
                    }
                }

                break;
            }//if(m_pSamSysParame->m_vecDataSamplingStr[k] == sGroupName)
        }
    }
}
















