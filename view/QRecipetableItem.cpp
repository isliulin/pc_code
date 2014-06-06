#include "QRecipetableItem.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

QRecipeTableItem::QRecipeTableItem()
    :QVisableItem(0)
{
    //Datesave = new struct CHART_INFORMATION;
}



QGraphicsItem *QRecipeTableItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    QRecipeTableItem *itemGroup = new QRecipeTableItem();

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
            pCopy->setFlag(QGraphicsItem::ItemIsSelectable,false);

    }

    itemGroup->SaveSecurityPro(&sPro);
    itemGroup->SaveInfo(m_SaveInfo);

    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    itemGroup->setData(GROUP_TYPE_KEY,data(GROUP_TYPE_KEY).toInt());

    itemGroup->setId(id());

    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }
    return itemGroup;
    //return QItemGroup::Clone();
    //return 0;
    //��Ҫ��������ʵ�������󣬸��Ʋ����޷����û������
}

void QRecipeTableItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    count++;
    QVisableItem::compile(db, nSceneId, count,index);
    int nItemID = count;

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

    QRectF rect = this->sceneBoundingRect();
    QSqlQuery sqlquery(db);

    bool bReasult = false;
    bReasult = sqlquery.prepare("INSERT INTO recipeDisplay(nItemId,nSceneId,nStartPosX,nStartPosY,nWidth,"
                                "nHeight,nRecipeGroupId,bShowRecipeID,bShowDescrip,eTextAlignType,"
                                "nLanguaId,nRowShowNum,nColumShowNum,nHHeadTextColor,nHHeadBackColor,"
                                "nHHeadFontSize,sHHeadFontFamily,nVHeadTextColor,nVHeadBackColor,"
                                "nVHeadFontSize,sVHeadFontFamily,nDataTextColor,nDataBackColor,"
                                "nDataFontSize,nLineColor,nTransparent,nZvalue,nCollidindId,nShowPropId)"
                                "VALUES (:nItemId,:nSceneId,:nStartPosX,:nStartPosY,:nWidth,"
                                ":nHeight,:nRecipeGroupId,:bShowRecipeID,:bShowDescrip,:eTextAlignType,"
                                ":nLanguaId,:nRowShowNum,:nColumShowNum,:nHHeadTextColor,:nHHeadBackColor,"
                                ":nHHeadFontSize,:sHHeadFontFamily,:nVHeadTextColor,:nVHeadBackColor,"
                                ":nVHeadFontSize,:sVHeadFontFamily,:nDataTextColor,:nDataBackColor,"
                                ":nDataFontSize,:nLineColor,:nTransparent,:nZvalue,:nCollidindId,:nShowPropId)");

    sqlquery.bindValue(":nItemId",QVariant(nItemID));
    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));
    sqlquery.bindValue(":nStartPosX",QVariant(rect.x()));
    sqlquery.bindValue(":nStartPosY",QVariant(rect.y()));
    sqlquery.bindValue(":nWidth",QVariant(rect.width()));
    sqlquery.bindValue(":nHeight",QVariant(rect.height()));
    sqlquery.bindValue(":nRecipeGroupId",QVariant(m_SaveInfo.nRecipeGroupId));
    sqlquery.bindValue(":bShowRecipeID",QVariant(m_SaveInfo.bShowRecipeID));
    sqlquery.bindValue(":bShowDescrip",QVariant(m_SaveInfo.bShowDescrip));
    int nAlign = 0;
    if(0 == m_SaveInfo.eTextAlignType)//center
    {
        nAlign = 2;
    }
    else if(1 == m_SaveInfo.eTextAlignType)//left
    {
        nAlign = 1;
    }
    else
    {
        nAlign = 3;
    }
    sqlquery.bindValue(":eTextAlignType",QVariant(nAlign));
    sqlquery.bindValue(":nLanguaId",QVariant(m_SaveInfo.nLanguaId));
    sqlquery.bindValue(":nRowShowNum",QVariant(m_SaveInfo.nRowShowNum));
    sqlquery.bindValue(":nColumShowNum",QVariant(m_SaveInfo.nColumShowNum));
    sqlquery.bindValue(":nHHeadTextColor",QVariant(ColorToInt(m_SaveInfo.nHHeadTextColor)));
    sqlquery.bindValue(":nHHeadBackColor",QVariant(ColorToInt(m_SaveInfo.nHHeadBackColor)));
    sqlquery.bindValue(":nHHeadFontSize",QVariant(m_SaveInfo.nHHeadFontSize + 5));
    sqlquery.bindValue(":sHHeadFontFamily",QVariant(m_SaveInfo.sHHeadFontFamily));
    sqlquery.bindValue(":nVHeadTextColor",QVariant(ColorToInt(m_SaveInfo.nVHeadTextColor)));
    sqlquery.bindValue(":nVHeadBackColor",QVariant(ColorToInt(m_SaveInfo.nVHeadBackColor)));
    sqlquery.bindValue(":nVHeadFontSize",QVariant(m_SaveInfo.nVHeadFontSize + 5));
    sqlquery.bindValue(":sVHeadFontFamily",QVariant(m_SaveInfo.sVHeadFontFamily));
    sqlquery.bindValue(":nDataTextColor",QVariant(ColorToInt(m_SaveInfo.nDataTextColor)));
    sqlquery.bindValue(":nDataBackColor",QVariant(ColorToInt(m_SaveInfo.nDataBackColor)));
    sqlquery.bindValue(":nDataFontSize",QVariant(m_SaveInfo.nDataFontSize + 5));
    sqlquery.bindValue(":nLineColor",QVariant(ColorToInt(m_SaveInfo.nLineColor)));
    sqlquery.bindValue(":nTransparent",QVariant(ColorToInt(m_SaveInfo.nTransparent)));
    sqlquery.bindValue(":nZvalue",QVariant(zValue()));
    sqlquery.bindValue(":nCollidindId",QVariant(index));
    sqlquery.bindValue(":nShowPropId",QVariant(-1));
    bReasult = sqlquery.exec();
    qDebug()<<"INSERT INTO recipeDisplay"<<bReasult;

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
        bReasult = sqlquery.prepare("INSERT INTO tableProp(nItemId,nIsRow,nNo,nWidth)"
                                    "VALUES (:nItemId,:nIsRow,:nNo,:nWidth)");
            sqlquery.bindValue(":nItemId",QVariant(nItemID));
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
        bReasult = sqlquery.prepare("INSERT INTO tableProp(nItemId,nIsRow,nNo,nWidth)"
                                    "VALUES (:nItemId,:nIsRow,:nNo,:nWidth)");
            sqlquery.bindValue(":nItemId",QVariant(nItemID));
            sqlquery.bindValue(":nIsRow",QVariant(1));
            sqlquery.bindValue(":nNo",QVariant(i));
            sqlquery.bindValue(":nWidth",QVariant(vHLine.at(i + 1) - vHLine.at(i)));
            sqlquery.exec();
    }

    for(int i = 0; i < m_SaveInfo.sRecipeName.size(); i++)
    {
        bReasult = sqlquery.prepare("INSERT INTO textProp(nItemId,nStatusIndex,nLangIndex,sFont,sText,nSize,nColor,nShowProp)"
                                    "VALUES (:nItemId,:nStatusIndex,:nLangIndex,:sFont,:sText,:nSize,:nColor,:nShowProp)");
            sqlquery.bindValue(":nItemId",QVariant(nItemID));
            sqlquery.bindValue(":nStatusIndex",QVariant(1));
            sqlquery.bindValue(":nLangIndex",QVariant(i));
            sqlquery.bindValue(":sText",QVariant(m_SaveInfo.sRecipeName.at(i)));
            sqlquery.bindValue(":nShowProp",QVariant(1));
            sqlquery.exec();
    }

//    bReasult = sqlquery.prepare("INSERT INTO tableProp(nItemId,eLineType,nLineNum,nWidth)"
//                                "VALUES (:nItemId,:eLineType,:nLineNum,:nWidth)");
//    sqlquery.bindValue(":nItemId",QVariant(nItemID));
//    sqlquery.bindValue(":eLineType",QVariant(eLineType));
    //�ڴ���ӱ���Ȩ��ҳ�����Դ���
}

int QRecipeTableItem::GroupType()
{
    return SAM_DRAW_GROUP_RECIPESHOW;
}
void QRecipeTableItem::save(QDataStream &stream)
{
    QVisableItem::save(stream);

    stream << m_SaveInfo.nRecipeGroupId;
    stream << m_SaveInfo.bShowRecipeID;
    stream << m_SaveInfo.bShowDescrip;
    stream << m_SaveInfo.eTextAlignType;
    stream << m_SaveInfo.nLanguaId;
    stream << m_SaveInfo.nRowShowNum;
    stream << m_SaveInfo.nColumShowNum;
    stream << m_SaveInfo.nHHeadTextColor;
    stream << m_SaveInfo.nHHeadBackColor;
    stream << m_SaveInfo.nHHeadFontSize;
    stream << m_SaveInfo.sHHeadFontFamily;
    stream << m_SaveInfo.nVHeadTextColor;
    stream << m_SaveInfo.nVHeadBackColor;
    stream << m_SaveInfo.nVHeadFontSize;
    stream << m_SaveInfo.sVHeadFontFamily;
    stream << m_SaveInfo.nDataTextColor;
    stream << m_SaveInfo.nDataBackColor;
    stream << m_SaveInfo.nDataFontSize;
    stream << m_SaveInfo.nLineColor;
    stream << m_SaveInfo.nTransparent;

    int nSize = m_SaveInfo.sRecipeName.size();
    stream << nSize;
    for(int i = 0; i < nSize; i++)
    {
        stream << m_SaveInfo.sRecipeName.at(i);
    }
}
void QRecipeTableItem::load(QDataStream &stream)
{
    QVisableItem::load(stream);

    stream >> m_SaveInfo.nRecipeGroupId;
    stream >> m_SaveInfo.bShowRecipeID;
    stream >> m_SaveInfo.bShowDescrip;
    stream >> m_SaveInfo.eTextAlignType;
    stream >> m_SaveInfo.nLanguaId;
    stream >> m_SaveInfo.nRowShowNum;
    stream >> m_SaveInfo.nColumShowNum;
    stream >> m_SaveInfo.nHHeadTextColor;
    stream >> m_SaveInfo.nHHeadBackColor;
    stream >> m_SaveInfo.nHHeadFontSize;
    stream >> m_SaveInfo.sHHeadFontFamily;
    stream >> m_SaveInfo.nVHeadTextColor;
    stream >> m_SaveInfo.nVHeadBackColor;
    stream >> m_SaveInfo.nVHeadFontSize;
    stream >> m_SaveInfo.sVHeadFontFamily;
    stream >> m_SaveInfo.nDataTextColor;
    stream >> m_SaveInfo.nDataBackColor;
    stream >> m_SaveInfo.nDataFontSize;
    stream >> m_SaveInfo.nLineColor;
    stream >> m_SaveInfo.nTransparent;

    m_SaveInfo.sRecipeName.resize(0);
    if (pwnd->getProVersion() < 2699)
    {
    }
    else
    {
        int nSize = 0;
        stream >> nSize;
        for(int i = 0; i < nSize; i++)
        {
            QString sName = "";
            stream >> sName;
            m_SaveInfo.sRecipeName.push_back(sName);
        }
    }

}


void QRecipeTableItem::SetText(QString sText)
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetText(sText);
    }
}

void QRecipeTableItem::SetFontSize(int nFontSize) //���������С
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->m_font.setPointSize(nFontSize);
        pText->update(pText->m_rect);
    }
}

void QRecipeTableItem::SetFontName(QString sName) //������������
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->m_font.setFamily(sName);
        pText->update(pText->m_rect);
    }
}

/*****************************************************************************
  �������ƣ�SetTextAlign(int nAlignType)
  �������壺�����ı��Ķ��뷽ʽ
  �������壺nAlignType
  nAlignType=1:���ϽǶ���
  nAlignType=2:�ϱ߶���
  nAlignType=3:���ϽǶ���
  nAlignType=4:��߶���
  nAlignType=5:���ж���
  nAlignType=6:�ұ߶���
  nAlignType=7:���½Ƕ���
  nAlignType=8:�±߶���
  nAlignType=9:���½Ƕ���
*****************************************************************************/
void QRecipeTableItem::SetTextAlign(int nAlignType)
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

void QRecipeTableItem::SaveInfo(RECIPESHOW info)
{
    m_SaveInfo = info;
}

void QRecipeTableItem::GetInfo(RECIPESHOW &info)
{
    info = m_SaveInfo;
}

QStringList QRecipeTableItem::getAllFonts()
{
    QStringList ls;
    ls.clear();
    ls << m_SaveInfo.sHHeadFontFamily;
    ls << m_SaveInfo.sVHeadFontFamily;
    return ls;
}

QString  QRecipeTableItem::getItemName()
{
    return QObject::tr("�䷽��ʾ��");
}

void QRecipeTableItem::changeItemLanguageAttr(int lanNum)
{
    if(m_SaveInfo.nLanguaId >= lanNum)
    {
        m_SaveInfo.nLanguaId = 0;//��ɾ�������Ը��� �����µ�ǰ����С���������� ���õ�һ������ΪĬ������
        QList<QGraphicsItem *> list = childItems();
        QString sName = "";
        QVector<QGraphicsItem *> vVTite;              //�����洹ֱ���ı� "Text"
        QVector<QGraphicsItem *> vHTite;             //������ˮƽ���ı� "NoText"
        vVTite.clear();
        vHTite.clear();
        //vTileTex.clear();

        foreach(QGraphicsItem *pItem,list)
        {
            if(SAM_DRAW_OBJECT_TEXT == pItem->type())
            {
                QString sName = pItem->data(GROUP_NAME_KEY).toString();
                if("Text" == sName.left(4))
                {
                    vVTite.append(pItem);
                }
                else if(sName.contains("NoText"))
                {
                   vHTite.append(pItem);
                }
            }
        }

        int nSize = vVTite.size();
        for(int i = 0; i < nSize; i++)
        {
            for(int j = i + 1; j < nSize; j++)
            {
                if(vVTite.at(j)->sceneBoundingRect().topLeft().x() < vVTite.at(i)->sceneBoundingRect().topLeft().x())
                {
                    QGraphicsItem *pItem = vVTite.at(j);
                    vVTite.replace(j,vVTite.at(i));
                    vVTite.replace(i,pItem);
                }
            }
        }

        nSize = vHTite.size();
        for(int i = 0; i < nSize; i++)
        {
            for(int j = i + 1; j < nSize; j++)
            {
                if(vHTite.at(j)->sceneBoundingRect().topLeft().y() < vHTite.at(i)->sceneBoundingRect().topLeft().y())
                {
                    QGraphicsItem *pItem = vHTite.at(j);
                    vHTite.replace(j,vHTite.at(i));
                    vHTite.replace(i,pItem);
                }
            }
        }

        QString sNo = QObject::tr("�䷽����");

        QStringList sDataName;
        sDataName.clear();

        //sDataName.append(sNo);
        //nUseCount++;

        if(m_SaveInfo.bShowRecipeID)
        {
            sDataName.append(QObject::tr("ID��"));
        }

        int index = m_SaveInfo.nRecipeGroupId;
        if(index >= pwnd->m_pSamSysParame->m_qvcRecipe.size())
        {
            return;
        }
        for(int i = 0;i < pwnd->m_pSamSysParame->m_qvcRecipe[index].ElmentName.size() && i < vVTite.size() - 1;i++) //RowHeadName[0].size()
        {
            if(0 < pwnd->m_pSamSysParame->m_qvcRecipe[index].ElmentName[i].size())
            {
                sDataName.append(pwnd->m_pSamSysParame->m_qvcRecipe[index].ElmentName[i][0].sElemName);//0
            }
        }

        for(int i = 0; i < sDataName.size() && i < vVTite.size(); i++)
        {
            QSimpleTextItem *pItem = dynamic_cast<QSimpleTextItem *> (vVTite.at(i));
            if(pItem)
            {
                pItem->SetText(sDataName.at(i));
            }
        }
        //end for��������������

        sDataName.clear();
        if(vHTite.size() > 0)
        {
            QSimpleTextItem *pItem = dynamic_cast<QSimpleTextItem *> (vHTite.at(0));
            if(pItem)
            {
                pItem->SetText(sNo);
            }
        }
        for(int i = 0; i < vHTite.size() - 1; i++)
        {
            QString sName = "";
            if(i < pwnd->m_pSamSysParame->m_qvcRecipe[index].formula.size())
            {
                if(0 < pwnd->m_pSamSysParame->m_qvcRecipe[index].formula[i].RecipeInfo.size())
                {
                    sName = pwnd->m_pSamSysParame->m_qvcRecipe[index].formula[i].RecipeInfo[0].sRecipeName;
                }
            }
            QSimpleTextItem *pItem = dynamic_cast<QSimpleTextItem *> (vHTite.at(i+1));
            if(pItem)
            {
                pItem->SetText(sName);
            }
        }

    }
}

int QRecipeTableItem::GetRicipeGroupId(int index )//�����䷽��Id��
{
    int nRet = m_SaveInfo.nRecipeGroupId;
    if(index < m_SaveInfo.nRecipeGroupId)
    {
        m_SaveInfo.nRecipeGroupId = m_SaveInfo.nRecipeGroupId - 1;
    }
    return nRet;
}

void QRecipeTableItem::setInvalid()
{
    m_SaveInfo.nRecipeGroupId = -1;
}

int QRecipeTableItem::getInvalid()
{
    return m_SaveInfo.nRecipeGroupId;
}

void QRecipeTableItem::RefreshItem(int index)//index �䷽��Id��
{
    if(m_SaveInfo.nRecipeGroupId == index)
    {
        int nLangId = m_SaveInfo.nLanguaId;
        QList<QGraphicsItem *> list = childItems();
        QString sName = "";
        QVector<QGraphicsItem *> vVTite;              //�����洹ֱ���ı� "Text"
        QVector<QGraphicsItem *> vHTite;             //������ˮƽ���ı� "NoText"
        vVTite.clear();
        vHTite.clear();
        //vTileTex.clear();

        foreach(QGraphicsItem *pItem,list)
        {
            if(SAM_DRAW_OBJECT_TEXT == pItem->type())
            {
                QString sName = pItem->data(GROUP_NAME_KEY).toString();
                if("Text" == sName.left(4))
                {
                    vVTite.append(pItem);
                }
                else if(sName.contains("NoText"))
                {
                   vHTite.append(pItem);
                }
            }
        }

        int nSize = vVTite.size();
        for(int i = 0; i < nSize; i++)
        {
            for(int j = i + 1; j < nSize; j++)
            {
                if(vVTite.at(j)->sceneBoundingRect().topLeft().x() < vVTite.at(i)->sceneBoundingRect().topLeft().x())
                {
                    QGraphicsItem *pItem = vVTite.at(j);
                    vVTite.replace(j,vVTite.at(i));
                    vVTite.replace(i,pItem);
                }
            }
        }

        nSize = vHTite.size();
        for(int i = 0; i < nSize; i++)
        {
            for(int j = i + 1; j < nSize; j++)
            {
                if(vHTite.at(j)->sceneBoundingRect().topLeft().y() < vHTite.at(i)->sceneBoundingRect().topLeft().y())
                {
                    QGraphicsItem *pItem = vHTite.at(j);
                    vHTite.replace(j,vHTite.at(i));
                    vHTite.replace(i,pItem);
                }
            }
        }

        QString sNo = QObject::tr("�䷽����");

        QStringList sDataName;
        sDataName.clear();

        //sDataName.append(sNo);
        //nUseCount++;

        if(m_SaveInfo.bShowRecipeID)
        {
            sDataName.append(QObject::tr("ID��"));
        }

        if(index >= pwnd->m_pSamSysParame->m_qvcRecipe.size())
        {
            return;
        }
        for(int i = 0;i < pwnd->m_pSamSysParame->m_qvcRecipe[index].ElmentName.size() && i < vVTite.size();i++) //RowHeadName[0].size()
        {
            if(nLangId < pwnd->m_pSamSysParame->m_qvcRecipe[index].ElmentName[i].size())
            {
                sDataName.append(pwnd->m_pSamSysParame->m_qvcRecipe[index].ElmentName[i][nLangId].sElemName);//0
            }
            else
            {
                return;
            }
        }

        for(int i = 0; i < sDataName.size() && i < vVTite.size(); i++)
        {
            QSimpleTextItem *pItem = dynamic_cast<QSimpleTextItem *> (vVTite.at(i));
            if(pItem)
            {
                pItem->SetText(sDataName.at(i));
            }
        }
        //end for��������������

        sDataName.clear();
        if(vHTite.size() > 0)
        {
            QSimpleTextItem *pItem = dynamic_cast<QSimpleTextItem *> (vHTite.at(0));
            if(pItem)
            {
                pItem->SetText(sNo);
            }
        }
        for(int i = 0; i < vHTite.size() - 1; i++)
        {
            QString sName = "";
            if(i < pwnd->m_pSamSysParame->m_qvcRecipe[index].formula.size())
            {
                if(nLangId < pwnd->m_pSamSysParame->m_qvcRecipe[index].formula[i].RecipeInfo.size())
                {
                    sName = pwnd->m_pSamSysParame->m_qvcRecipe[index].formula[i].RecipeInfo[nLangId].sRecipeName;
                }
                else
                {
                    return;
                }
            }
            QSimpleTextItem *pItem = dynamic_cast<QSimpleTextItem *> (vHTite.at(i+1));
            if(pItem)
            {
                pItem->SetText(sName);
            }
        }

    }
}
