#include "qmessageboradattr.h"
extern MainWindow *pwnd;
qMessageBoradAttr::qMessageBoradAttr(QGraphicsItem *parent):QVisableItem(parent)
{

}

QString  qMessageBoradAttr::getItemName()
{
    return QObject::tr("���԰�");
}

qMessageBoradAttr::~qMessageBoradAttr()
{

}

int qMessageBoradAttr::GroupType()//�ؼ����� λ���� �ֿ���
{
    return SAM_DRAW_GROUP_TEXTBOARD;
}

qMessageBoradAttr* qMessageBoradAttr::Clone()//����item
{
    QGraphicsItem* pCopy = NULL;
    QGraphicsItem* pItem = NULL;

    qMessageBoradAttr *itemGroup = new qMessageBoradAttr;

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

    //����
    itemGroup->m_bShowId    = m_bShowId;      //�Ƿ���ʾ���
    itemGroup->m_bShowTime  = m_bShowTime;    //�Ƿ���ʾʱ��
    itemGroup->m_nTimeType  = m_nTimeType;    //ʱ���ʽ��ö�٣�
    itemGroup->m_bShowDate  = m_bShowDate;    //�Ƿ���ʾ����
    itemGroup->m_nDateType  = m_nDateType;    //���ڸ�ʽ��ö�٣�
    itemGroup->m_nTFontSize = m_nTFontSize;   //��ͷ�����С
    itemGroup->m_sTFontType = m_sTFontType;   //��ͷ��������
    itemGroup->m_nTFontColor= m_nTFontColor;  //��ͷ������ɫ
    itemGroup->m_nTBackColor= m_nTBackColor;  //��ͷ������ɫ
    //���
    itemGroup->m_nAlpha     = m_nAlpha;       //�ؼ�͸����
    itemGroup->m_nLineColor = m_nLineColor;   //�߿���ɫ
    itemGroup->m_nFillCss   = m_nFillCss;     //�����ʽ
    itemGroup->m_nBackColor = m_nBackColor;   //������ɫ
    itemGroup->m_nForeColor = m_nForeColor;   //ǰ��ɫ
    //����
    itemGroup->m_nFontSize  = m_nFontSize;    //���������С
    itemGroup->m_sFontType  = m_sFontType;    //������������
    itemGroup->m_nFontColor = m_nFontColor;   //����������ɫ
    itemGroup->m_nRowNumber = m_nRowNumber;   //��������
    //������
    itemGroup->m_vecMessage = m_vecMessage;

    itemGroup->setId(id());

    return itemGroup;
}

void qMessageBoradAttr::compile(QSqlDatabase &db, int nSceneId, int &count, int index)//�����ʱ�򱣴�item�����ݿ�
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
    bool r1 = sqlquery.prepare("INSERT INTO messageBoard(nItemId,nSceneId,"
                    "nStartX,nStartY,nWidth,nHeight,nAlpha,nLineColor,"
                    "nFillCss,nBackColor,nForeColor,nFontSize,sFontType,"
                    "nFontColor,nTFontSize,sTFontType,nTFontColor,"
                    "nTBackColor,bShowId,bShowTime,nTimeType,bShowDate,"
                    "nDateType,nRowNumber,nZvalue,nCollidindId)"
             "VALUES(:nItemId,:nSceneId,:nStartX,:nStartY,:nWidth,:nHeight,:nAlpha,:nLineColor,"
                    ":nFillCss,:nBackColor,:nForeColor,:nFontSize,:sFontType,"
                    ":nFontColor,:nTFontSize,:sTFontType,:nTFontColor,"
                    ":nTBackColor,:bShowId,:bShowTime,:nTimeType,:bShowDate,"
                    ":nDateType,:nRowNumber,:nZvalue,:nCollidindId)");

    qDebug() << r1;

    int base = count;
    sqlquery.bindValue(":nItemId", QVariant(itemId));      //��id
    sqlquery.bindValue(":nSceneId", QVariant(nSceneId));      //��id

    QRectF rect = sceneBoundingRect();//��Գ��������꼰�߿�
    sqlquery.bindValue(":nStartX", QVariant((short)rect.left()));
    sqlquery.bindValue(":nStartY", QVariant((short)rect.top()));
    sqlquery.bindValue(":nWidth", QVariant((short)rect.width()));
    sqlquery.bindValue(":nHeight", QVariant((short)rect.height()));
    sqlquery.bindValue(":nAlpha", QVariant(m_nAlpha));
    int color = ColorToInt(m_nLineColor);
    sqlquery.bindValue(":nLineColor", QVariant(color));

    sqlquery.bindValue(":nFillCss", QVariant(m_nFillCss + 1));
    color = ColorToInt(m_nBackColor);
    sqlquery.bindValue(":nBackColor", QVariant(color));
    color = ColorToInt(m_nForeColor);
    sqlquery.bindValue(":nForeColor", QVariant(color));
    sqlquery.bindValue(":nFontSize", QVariant(m_nFontSize));
    sqlquery.bindValue(":sFontType", QVariant(m_sFontType));

    color = ColorToInt(m_nFontColor);
    sqlquery.bindValue(":nFontColor", QVariant(color));
    sqlquery.bindValue(":nTFontSize", QVariant(m_nTFontSize));
    sqlquery.bindValue(":sTFontType", QVariant(m_sTFontType));
    color = ColorToInt(m_nTFontColor);
    sqlquery.bindValue(":nTFontColor", QVariant(color));

    color = ColorToInt(m_nTBackColor);
    sqlquery.bindValue(":nTBackColor", QVariant(color));
    sqlquery.bindValue(":bShowId", QVariant(m_bShowId));
    sqlquery.bindValue(":bShowTime", QVariant(m_bShowTime));
    sqlquery.bindValue(":nTimeType", QVariant(m_nTimeType + 1));
    sqlquery.bindValue(":bShowDate", QVariant(m_bShowDate));

    sqlquery.bindValue(":nDateType", QVariant(m_nDateType + 1));
    sqlquery.bindValue(":nRowNumber", QVariant(m_nRowNumber));
    sqlquery.bindValue(":nZvalue", QVariant(zValue()));
    sqlquery.bindValue(":nCollidindId", QVariant(index));

    bool result = sqlquery.exec();
    qDebug() << result << endl;

    bool r2 = sqlquery.prepare("INSERT INTO messageBoardLanguage(nId,"
                               "nItemId,nLanguageIndex,sNumber,"
                               "sDateName,sTimeName,sMessageName)"
                               "VALUES(:nId,"
                               ":nItemId,:nLanguageIndex,:sNumber,"
                               ":sDateName,:sTimeName,:sMessageName)");
    qDebug() << r2;

    int num = m_vecMessage.size();
    for(int i = 0; i < num; i++)
    {
        count++;
        sqlquery.bindValue(":nId", QVariant(count));
        sqlquery.bindValue(":nItemId", QVariant(itemId));
        sqlquery.bindValue(":nLanguageIndex", QVariant(m_vecMessage[i].m_nLanguage));
        sqlquery.bindValue(":sNumber", QVariant(m_vecMessage[i].m_sNumber));
        sqlquery.bindValue(":sDateName", QVariant(m_vecMessage[i].m_sDateName));
        sqlquery.bindValue(":sTimeName", QVariant(m_vecMessage[i].m_sTimeName));
        sqlquery.bindValue(":sMessageName", QVariant(m_vecMessage[i].m_sMessageName));

        result = sqlquery.exec();
        qDebug() << result << endl;
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
}

void qMessageBoradAttr::save(QDataStream &stream)//��item����������
{
    QVisableItem::save(stream);

    //����
    stream << m_bShowId;      //�Ƿ���ʾ���
    stream << m_bShowTime;    //�Ƿ���ʾʱ��
    stream << m_nTimeType;    //ʱ���ʽ��ö�٣�
    stream << m_bShowDate;    //�Ƿ���ʾ����
    stream << m_nDateType;    //���ڸ�ʽ��ö�٣�
    stream << m_nTFontSize;   //��ͷ�����С
    stream << m_sTFontType;   //��ͷ��������
    stream << m_nTFontColor;  //��ͷ������ɫ
    stream << m_nTBackColor;  //��ͷ������ɫ
    //���
    stream << m_nAlpha;       //�ؼ�͸����
    stream << m_nLineColor;   //�߿���ɫ
    stream << m_nFillCss;     //�����ʽ
    stream << m_nBackColor;   //������ɫ
    stream << m_nForeColor;   //ǰ��ɫ
    //����
    stream << m_nFontSize;    //���������С
    stream << m_sFontType;    //������������
    stream << m_nFontColor;   //����������ɫ
    stream << m_nRowNumber;   //��������
    //������
    int temp = m_vecMessage.size();
    stream << temp;
    for(int i = 0; i < temp; i++)
    {
        stream << m_vecMessage[i].m_nLanguage;
        stream << m_vecMessage[i].m_sDateName;
        stream << m_vecMessage[i].m_sMessageName;
        stream << m_vecMessage[i].m_sNumber;
        stream << m_vecMessage[i].m_sTimeName;
    }
}

void qMessageBoradAttr::load(QDataStream &stream)//������������item
{
    QVisableItem::load(stream);

    //����
    stream >> m_bShowId;      //�Ƿ���ʾ���
    stream >> m_bShowTime;    //�Ƿ���ʾʱ��
    stream >> m_nTimeType;    //ʱ���ʽ��ö�٣�
    stream >> m_bShowDate;    //�Ƿ���ʾ����
    stream >> m_nDateType;    //���ڸ�ʽ��ö�٣�
    stream >> m_nTFontSize;   //��ͷ�����С
    stream >> m_sTFontType;   //��ͷ��������
    stream >> m_nTFontColor;  //��ͷ������ɫ
    stream >> m_nTBackColor;  //��ͷ������ɫ
    //���
    stream >> m_nAlpha;       //�ؼ�͸����
    stream >> m_nLineColor;   //�߿���ɫ
    stream >> m_nFillCss;     //�����ʽ
    stream >> m_nBackColor;   //������ɫ
    stream >> m_nForeColor;   //ǰ��ɫ
    //����
    stream >> m_nFontSize;    //���������С
    stream >> m_sFontType;    //������������
    stream >> m_nFontColor;   //����������ɫ
    stream >> m_nRowNumber;   //��������
    //������
    int temp = 0;
    stream >> temp;
    if(temp <= 0)
    {
        QMessageBox::about(0, QObject::tr("111111"), QObject::tr("ooooooo"));
    }
    m_vecMessage.resize(temp);

    for(int i = 0; i < temp; i++)
    {
        stream >> m_vecMessage[i].m_nLanguage;
        stream >> m_vecMessage[i].m_sDateName;
        stream >> m_vecMessage[i].m_sMessageName;
        stream >> m_vecMessage[i].m_sNumber;
        stream >> m_vecMessage[i].m_sTimeName;
    }
}

void qMessageBoradAttr::redrawForChangeLanguage(int index)
{
    //�������ı�
    QStringList sDataName;
    sDataName.clear();
    int iLan = index;//pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan;

    if(this->m_bShowId)
    {
        QString sNum  = m_vecMessage[iLan].m_sNumber;
        sDataName.append(sNum);
    }
    if(m_bShowTime)
    {
        QString sTime = m_vecMessage[iLan].m_sTimeName;   //������1��ʾʱ������
        sDataName.append(sTime);
    }
    if(m_bShowDate)
    {
        QString sDate = m_vecMessage[iLan].m_sDateName;   //������1��ʾ��������
        sDataName.append(sDate);
    }

    sDataName.append(m_vecMessage[iLan].m_sMessageName);
    /*int temp = m_vecHisData[iLan].m_vecInfo.size();
    int XXX  = 0;
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
    }*/

    QGraphicsItem* pItem = NULL;
    QList<QGraphicsItem *> itemList;
    itemList = childItems();
    int size = itemList.size();
    int k = 0;

    for(int i = 0; i < size; i++)
    {
        pItem = itemList.at(i);

        switch(pItem->type())
        {
            case SAM_DRAW_OBJECT_TEXT://һ��һ����ȡ���ı�
            {
                QSimpleTextItem* textItem = dynamic_cast<QSimpleTextItem *>(pItem);
                if(textItem)
                {

                    textItem->SetText(sDataName.at(k));
                    textItem->SetFontName(m_sTFontType);
                    textItem->SetFontSize(m_nTFontSize);
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

TEXTPRO qMessageBoradAttr::getAllItemText()
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
      //  for(int j = 0; j < iStaCount; j++)//��״̬��Ŀɨ��
      //  {
        for(int j = 0; j < 4; j++)
            vText.iLanguage.append(i);

            vText.vStatus.append(0);
            vText.vMsg.append(QObject::tr("����:"));
            vText.vText.append(m_vecMessage[i].m_sDateName);

            vText.vStatus.append(1);
            vText.vMsg.append(QObject::tr("������Ϣ:"));
            vText.vText.append(m_vecMessage[i].m_sMessageName);

            vText.vStatus.append(2);
            vText.vMsg.append(QObject::tr("���:"));
            vText.vText.append(m_vecMessage[i].m_sNumber);

            vText.vStatus.append(3);
            vText.vMsg.append(QObject::tr("ʱ��:"));
            vText.vText.append(m_vecMessage[i].m_sTimeName);
     //   }
    }
    return vText;
}

void qMessageBoradAttr::replaceAllItemText(int iLan, int iSta, QString sNewText)
{
    int iL = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //����������
   // int iStaCount = mPro.count; //��״̬��Ŀ
    if( iLan >= 0 && iLan < iL)
    {
        if(iSta == 0)
            m_vecMessage[iLan].m_sDateName = sNewText;
        else if(iSta == 1)
            m_vecMessage[iLan].m_sMessageName = sNewText;
        else if(iSta == 2)
            m_vecMessage[iLan].m_sNumber = sNewText;
        else if(iSta == 3)
            m_vecMessage[iLan].m_sTimeName = sNewText;
    }
}

void qMessageBoradAttr::changeItemLanguageAttr(int lanNum)
{
    int textNum = m_vecMessage.size();

    if(lanNum > textNum)
    {
        MmessageBoardLanguage txtInfo;
        for(int i = textNum; i < lanNum; i++)
        {
            txtInfo.m_nLanguage    = i;
            txtInfo.m_sNumber      = QObject::tr("���");
            txtInfo.m_sTimeName    = QObject::tr("ʱ��");
            txtInfo.m_sDateName    = QObject::tr("����");
            txtInfo.m_sMessageName = QObject::tr("������Ϣ");

            m_vecMessage.push_back(txtInfo);
        }
    }
    else if(lanNum < textNum)
    {
        for(int i = textNum - 1; i >= lanNum; i--)
        {
            m_vecMessage.remove(i);
        }
    }
}

QStringList qMessageBoradAttr::getAllFonts()
{
    QStringList ls;
    ls.clear();

    ls << m_sTFontType;
    ls << m_sFontType;

    return ls;
}
