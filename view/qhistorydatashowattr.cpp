#include "qhistorydatashowattr.h"

extern MainWindow *pwnd;

QHistoryDataShowAttr::QHistoryDataShowAttr(QGraphicsItem *parent):QVisableItem(parent)//QItemGroup(parent)
{
}

QHistoryDataShowAttr::~QHistoryDataShowAttr()
{
}

int QHistoryDataShowAttr::GroupType()                //�ؼ����� λ���� �ֿ���
{
    return SAM_DRAW_GROUP_HISTORYDATE;
}

QHistoryDataShowAttr* QHistoryDataShowAttr::Clone()            //����item
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
        case SAM_DRAW_OBJECT_RECT:              //����
            {
                QRectItem *rectItem = dynamic_cast<QRectItem *>(pItem);
                if(rectItem)
                {
                    pCopy = rectItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_ELIPSE:              //Բ
            {
                QElipseItem *elipseItem = dynamic_cast<QElipseItem *>(pItem);
                if(elipseItem)
                {
                    pCopy = elipseItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_LINE:                 //ֱ��
            {
                QLineItem * lineItem = dynamic_cast<QLineItem *>(pItem);
                if(lineItem)
                {
                    pCopy = lineItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_POLYGON:              //�����
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
    //����
    itemGroup->m_vecHisData     = m_vecHisData;
    itemGroup->setId(id());

    return itemGroup;
}

void QHistoryDataShowAttr::compile(QSqlDatabase &db, int nSceneId, int &count, int index)//�����ʱ�򱣴�item�����ݿ�
{
    count++;
    QVisableItem::compile(db, nSceneId, count, index);

    int itemId = count;
    if(sPro.enableTouch && !sPro.byGroups_T)
    {
        //������λ���� ��һ����ַ��
        count++;
    }
    if(sPro.bNotice)
    {
        //���ؽ���֪ͨ����ַ ����һ����ַ��
        count++;
    }
    if(sPro.enableVisable && !sPro.byGroups_V)
    {
        //������λ���� ����һ����ַ��
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

    sqlquery.bindValue(":nItemId", QVariant(itemId));                //��id
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
    QRectF rect = sceneBoundingRect();//��Գ��������꼰�߿�
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

    QVector<qreal> vVLine;              //�����洹ֱ�ߵ�����
    QVector<qreal> vHLine;             //������ˮƽ�ߵ�����
    vVLine.clear();
    vHLine.clear();
    vVLine.append(rect.x());
    vHLine.append(rect.y());
    //vTileTex.clear();

    foreach(QGraphicsItem *pItem,list)
    {
        QPointF pos = pItem->boundingRect().topLeft()+pItem->scenePos();
        sName = pItem->data(GROUP_NAME_KEY).toString();
        if(sName.contains("VLine")) //��ֱ��
        {
            vVLine.append(pos.x());
        }
        if(sName.contains("HLine")) //ˮƽ��
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

    //��ֱ��
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

void QHistoryDataShowAttr::save(QDataStream &stream) //��item����������
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

void QHistoryDataShowAttr::load(QDataStream &stream) //������������item
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
    if(pwnd->getProVersion() < 3087)//�ɰ汾
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
    //  int iStaCount = 1; //��״̬��Ŀ
      int iLan = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //����������

      vText.sCtrlName = this->getItemName(); //�ؼ�����
      vText.iLanguage.clear();
      vText.vStatus.clear();
      vText.vText.clear();
      vText.vMsg.clear();

      for(int i = 0; i < iLan; i++) //�ܵ�����ɨ��
      {
          for(int j = 0; j < 3; j++)
              vText.iLanguage.append(i);

          vText.vStatus.append(10000);
          vText.vMsg.append(QObject::tr("���:"));
          vText.vText.append(m_vecHisText[i].m_sTitleNumber);

          vText.vStatus.append(10001);
          vText.vMsg.append(QObject::tr("ʱ��:"));
          vText.vText.append(m_vecHisText[i].m_sTitleTimeName);

          vText.vStatus.append(10002);
          vText.vMsg.append(QObject::tr("����:"));
          vText.vText.append(m_vecHisText[i].m_sTitleDateName);

          if(m_vecHisData.size() != 0) //����������Ŀ
          {
              int temp = m_vecHisData[i].m_vecInfo.size();
              for(int k = 0; k < temp; k++)
              {
                  vText.iLanguage.append(i);
                  vText.vStatus.append(k);
                  vText.vMsg.append(QObject::tr("����:")+QString("%1").arg(k));
                  vText.vText.append(m_vecHisData[i].m_vecInfo[k].m_strName);
              }
          }
      }
      return vText;
}

void QHistoryDataShowAttr::replaceAllItemText(int iLan, int iSta, QString sNewText)
{
    int iL = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //����������

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
    //�������ı�
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
        QString sTime = m_vecHisText[iLan].m_sTitleTimeName;   //������1��ʾʱ������
        sDataName.append(sTime);
    }
    if(m_bShowDate)
    {
        QString sDate = m_vecHisText[iLan].m_sTitleDateName;   //������1��ʾ��������
        sDataName.append(sDate);
    }

    int XXX  = 0;
    if(m_vecHisData.size() != 0)
    {
        int temp = m_vecHisData[iLan].m_vecInfo.size();

        for(int i = 0; i < temp; i++)
        {
            if(m_vecHisData[iLan].m_vecInfo[i].m_bShow) //��ʾ��������
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
            case SAM_DRAW_OBJECT_TEXT://һ��һ����ȡ���ı�
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
        //QMessageBox::about(this, QObject::tr("����"), QObject::tr("textNum != dataNum"));
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
            txtInfo.m_sTitleDateName = QObject::tr("����");
            txtInfo.m_sTitleFontType = QObject::tr("Droid Sans Fallback");
            txtInfo.m_sTitleTimeName = QObject::tr("ʱ��");
            txtInfo.m_sTitleNumber   = QObject::tr("���");

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
    return QObject::tr("��ʷ������ʾ��");
}

void QHistoryDataShowAttr::sampChanged(QString oldName,QString newName,int sampType)
{
	/*//һ��
    QColor  m_nForecolor;       //ǰ��ɫ
    QColor  m_nFrameColor;      //�߿�ɫ
    short   m_nAlpha;
    //---------------
    short   m_nTextFontSize;    //�ı������С��Ĭ��10
    short   m_nLine;            //��ʾ������Ĭ��5
    QColor  m_nTextFontColor;   //�ı�������ɫ��Ĭ�Ϻ�ɫ
    //---------------
    bool    m_bShowTime;	//�Ƿ���ʾʱ�䣬Ĭ����ʾ
    bool    m_bShowDate;	//�Ƿ���ʾ����,Ĭ����ʾ
    QColor  m_nTitleBackColor;	//���ⱳ����ɫ��Ĭ�ϻ�ɫ
    QColor  m_nTitleFontColor;	//����������ɫ��Ĭ�Ϻ�ɫ
    bool    m_bShowCode;        //�Ƿ���ʾ���
    TIME_FORMAT	m_eTimeFormat;  //(ͳһʱ���ʽö��)ʱ���ʽ HH:MM
    DATE_FORMAT	m_eDateFormat;  //(ͳһʱ���ʽö��)���ڸ�ʽ Ĭ�ϣ�DD/MM/YY
    QString     sGroupName;         //����
    //---------------
    QVector<HistoryTextInfo> m_vecHisText;//ÿ�����Զ�Ӧ�ı������ݵ���������
    //����
    QVector<HistoryDataInfo> m_vecHisData;*/
    if((1 == sampType) && (oldName == sGroupName))//���͸ı�,sampType=1ʵʱ����
    {
        sGroupName  = "";
        m_bShowTime = true;
        m_bShowDate = true;
        m_bShowCode = true;
        m_vecHisData.clear();
    }
    if((oldName != newName) && (oldName == sGroupName))//���ָı�
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
















