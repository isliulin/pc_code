#include "qdropdownattr.h"
#include "Frame/mainwindow.h"
#include "Macro/macro.h"

extern MainWindow *pwnd;

QDropdownAttr::QDropdownAttr(QGraphicsItem *parent):QVisableItem(parent)
{
    pRect     = NULL;
    pBackRect = NULL;
    pLine     = NULL;
    /*QRectF rect = QRectF(0,0,100,100);
    frameRect = new QRectItem(rect);
    frameRect->SetBackColor(QColor(100,100,100));
    addToGroup(frameRect);*/
    /*QRectF rect = QRectF(0,0,108,18);
    //rect.setSize(QSize(108,18));//����������
    pRect = new QRectItem(rect);//
    pRect->SetLineColor(QColor(127,157,185));
    //pRect->SetPattern(1);
    pRect->SetBackColor(m_nBackColor);
    pRect->SetName("mFramRect");
    //pRect->setZValue(1);
    addToGroup(pRect);
    pRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    rect.setTopLeft(QPointF(84,0));               //���Ʊ������ο�
    rect.setSize(QSize(24,18));
    pBackRect = new QRectItem(rect);
    pBackRect->SetBackColor(QColor(183,211,252));
    pBackRect->SetLineType(0);
    pBackRect->SetName("mBackRect");
    pBackRect->setZValue(2);
    addToGroup(pBackRect);
    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    QPainterPath mPenPath = QPainterPath();
    mPenPath.moveTo(QPointF(90,7));//��һ��
    mPenPath.lineTo(QPointF(96,11));
    mPenPath.lineTo(QPointF(102,7));
    pLine = new QFoldLineItem(mPenPath);
    pLine->setLineType(1);
    pLine->setLineWidth(2); //�����������
    pLine->setLineColor(QColor(77,97,133)); //������ɫ
    pLine->SetName("mLine");
    pLine->setZValue(4);
    addToGroup(pLine);
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);*/
}

QDropdownAttr::~QDropdownAttr()
{
    delete pRect;
    delete pBackRect;
    delete pLine;
}

QString QDropdownAttr::getItemName()
{
    return QObject::tr("����ѡ��ť");
}

void QDropdownAttr::resetDropDown(QColor mColor, short alpha)
{
    //pRect->SetBackColor(mColor);

    if(pRect)
    {
        delete pRect;
        pRect = NULL;
    }

    if(pBackRect)
    {
        delete pBackRect;
        pBackRect = NULL;
    }

    if(pLine)
    {
        delete pLine;
        pLine = NULL;
    }

    QLineItem *pLineTemp;

    QPainterPath mPath1;
    mPath1.moveTo(0,0);         //��ֱ�ߵ����
    mPath1.lineTo(108,0);         //��ֱ�ߵ��յ�
    pLineTemp = new QLineItem(mPath1);        //��ϸֱ��
    pLineTemp->setLineColor(QColor(127,157,185));     //����ֱ����ɫ
    //pLineTemp->setAlpha(alpha);
    addToGroup(pLineTemp);                   //��ӵ���
    pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);

    QPainterPath mPath2;
    mPath2.moveTo(0,0);         //��ֱ�ߵ����
    mPath2.lineTo(0,18);         //��ֱ�ߵ��յ�
    pLineTemp = new QLineItem(mPath2);        //��ϸֱ��
    pLineTemp->setLineColor(QColor(127,157,185));     //����ֱ����ɫ
    //pLineTemp->setAlpha(alpha);
    addToGroup(pLineTemp);                   //��ӵ���
    pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);

    QPainterPath mPath3;
    mPath3.moveTo(108,0);         //��ֱ�ߵ����
    mPath3.lineTo(108,18);         //��ֱ�ߵ��յ�
    pLineTemp = new QLineItem(mPath3);        //��ϸֱ��
    pLineTemp->setLineColor(QColor(127,157,185));     //����ֱ����ɫ
    //pLineTemp->setAlpha(alpha);
    addToGroup(pLineTemp);                   //��ӵ���
    pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);

    QPainterPath mPath4;
    mPath4.moveTo(0,18);         //��ֱ�ߵ����
    mPath4.lineTo(108,18);         //��ֱ�ߵ��յ�
    pLineTemp = new QLineItem(mPath4);        //��ϸֱ��
    pLineTemp->setLineColor(QColor(127,157,185));     //����ֱ����ɫ
    //pLineTemp->setAlpha(alpha);
    addToGroup(pLineTemp);                   //��ӵ���
    pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);

    QRectF rect = QRectF(0,0,108,18);
    //rect.setSize(QSize(108,18));//����������
    pRect = new QRectItem(rect);//
    pRect->SetLineColor(QColor(127,157,185));
    pRect->SetPattern(1);
    pRect->SetBackColor(mColor);
    pRect->SetName("mFramRect");
    pRect->setZValue(1);
    pRect->SetAlpha(alpha);
    addToGroup(pRect);
    pRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    /*QRectF rect = QRectF(0,0,108,18);
    //rect.setSize(QSize(108,18));//����������
    pRect = new QRectItem(rect);//
    pRect->SetLineColor(QColor(127,157,185));
    pRect->SetPattern(1);
    pRect->SetBackColor(m_pDropDownFont->m_nBackColor);
    pRect->SetName("mFramRect");
    pRect->setZValue(1);
    pRect->SetAlpha(alpha);
    pTempItem->addToGroup(pRect);
    //addToGroup(pRect);
    pRect->setFlag(QGraphicsItem::ItemIsSelectable, false);*/

    rect.setTopLeft(QPointF(84,0));               //���Ʊ������ο�
    rect.setSize(QSize(24,18));
    pBackRect = new QRectItem(rect);
    pBackRect->SetBackColor(QColor(183,211,252));
    pBackRect->SetLineType(0);
    pBackRect->SetName("mBackRect");
    pBackRect->setZValue(2);
    //pRect->SetBackColor(mColor);
    pBackRect->SetAlpha(alpha);
    addToGroup(pBackRect);
    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    QPainterPath mPenPath = QPainterPath();
    mPenPath.moveTo(QPointF(90,7));//��һ��
    mPenPath.lineTo(QPointF(96,11));
    mPenPath.lineTo(QPointF(102,7));
    pLine = new QFoldLineItem(mPenPath);
    pLine->setLineType(1);
    pLine->setLineWidth(2); //�����������
    pLine->setLineColor(QColor(77,97,133)); //������ɫ
    pLine->SetName("mLine");
    pLine->setZValue(4);
    //pLine->setAlpha(alpha);
    addToGroup(pLine);
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
}

int QDropdownAttr::GroupType()//�ؼ����� λ���� �ֿ���
{
    return SAM_DRAW_GROUP_DROPDOWN;
}

QDropdownAttr* QDropdownAttr::Clone()//����item
{
    QGraphicsItem* pCopy = NULL;
    QGraphicsItem* pItem = NULL;

    QDropdownAttr *itemGroup = new QDropdownAttr;

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

    itemGroup->m_nShowNumber    = m_nShowNumber;          //������ʾ����
    itemGroup->totalScreen      = totalScreen;            //
    itemGroup->isUseScript      = isUseScript;
    itemGroup->macroName        = macroName;
    itemGroup->functionName     = functionName;
    itemGroup->m_vecSwitchItem  = m_vecSwitchItem;        //�б��ĸ�ֵ

    itemGroup->m_strFontName    = m_strFontName;          //�������͵�����
    itemGroup->m_nFontSize      = m_nFontSize;            //�����С
    itemGroup->m_nLanType       = m_nLanType;             //��������
    itemGroup->m_nFontStyle     = m_nFontStyle;           //������ʽ����׼�����壬б�壩
    itemGroup->m_nFontColor     = m_nFontColor;           //������ɫ
    itemGroup->m_nBackColor     = m_nBackColor;
    itemGroup->m_nAlpha         = m_nAlpha;
    itemGroup->m_bUsePic        = m_bUsePic;
    itemGroup->setId(id());

    return itemGroup;
}

void QDropdownAttr::compile(QSqlDatabase &db, int nSceneId, int &count,int index)//�����ʱ�򱣴�item�����ݿ�
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

    //int baseId = count;

    QSqlQuery sqlquery(db);
    /////////////////////////////////������Id////////////////////////////////////////////
    bool r = sqlquery.prepare("INSERT INTO combobox(nItemId,nSceneId,nStartX,nStartY,nWidth,nHeight,"
                              "nShowNumber,sFontType,nfontSize,nLanguageTypeId,nFontColor,"
                              "eFontCss,nBackColor,nTouchPropId,nShowPropId,nZvalue,nCollidindId,bUsePic ,bIsStartStatement,nScriptId,nAlpha)"
                       "VALUES(:nItemId,:nSceneId,:nStartX,:nStartY,:nWidth,:nHeight,"
                              ":nShowNumber,:sFontType,:nfontSize,:nLanguageTypeId,:nFontColor,"
                              ":eFontCss,:nBackColor,:nTouchPropId,:nShowPropId,:nZvalue,:nCollidindId,:bUsePic ,:bIsStartStatement,:nScriptId,:nAlpha)");

    qDebug() << "sqlquery.prepare" << r;

    sqlquery.bindValue(":nItemId", QVariant(itemId));                //��id
    sqlquery.bindValue(":nSceneId", QVariant(nSceneId));            //scene id

    QRectF rect = sceneBoundingRect();//��Գ��������꼰�߿�
    sqlquery.bindValue(":nStartX", QVariant((short)rect.left()));//left
    sqlquery.bindValue(":nStartY", QVariant((short)rect.top()));//top
    sqlquery.bindValue(":nWidth", QVariant((short)rect.width()));//width
    sqlquery.bindValue(":nHeight", QVariant((short)rect.height()));//height

    sqlquery.bindValue(":nShowNumber", QVariant(m_nShowNumber));//
    sqlquery.bindValue(":sFontType", QVariant(m_strFontName));//
    sqlquery.bindValue(":nfontSize", QVariant(m_nFontSize));//
    sqlquery.bindValue(":nLanguageTypeId", QVariant(m_nLanType));//
    int temp = ColorToInt(m_nFontColor);
    sqlquery.bindValue(":nFontColor", QVariant(temp));//
    sqlquery.bindValue(":eFontCss", QVariant(m_nFontStyle));//
    temp = ColorToInt(m_nBackColor);
    sqlquery.bindValue(":nBackColor", QVariant(temp));//
    sqlquery.bindValue(":nTouchPropId", QVariant(0));//????????????????
    sqlquery.bindValue(":nShowPropId", QVariant(0));//????????????????
    sqlquery.bindValue(":nZvalue", QVariant(zValue()));//
    sqlquery.bindValue(":nCollidindId", QVariant(index));//
    sqlquery.bindValue(":bUsePic", QVariant(m_bUsePic));//
    sqlquery.bindValue(":bIsStartStatement", QVariant(isUseScript));//

    bool isExist = false;
    if(isUseScript)
    {
        foreach(Macro lib,pwnd->macros)
        {
            if(lib.libName == macroName)
            {
                isExist = true;
            }
        }

        if(!isExist)
        {
            //pwnd->information(QObject::tr("������걻ɾ��"));
            pwnd->information(QObject::tr("������ʹ�õĺ�") + macroName +QObject::tr("����") + functionName + QObject::tr("��ɾ��"), MSG_WARNING);
            //QMessageBox::about(this, QObject::tr("����"), QObject::tr("������걻ɾ��"));
        }
    }
    if(isUseScript && isExist)
    {
        count++;
        sqlquery.bindValue(":nScriptId", QVariant(count));//
    }
    else
    {
        sqlquery.bindValue(":nScriptId", QVariant(-1));//
    }

    sqlquery.bindValue(":nAlpha", QVariant(m_nAlpha));//

    bool result = sqlquery.exec();
    qDebug() << "QDropdownAttr" << result << endl;

    if(isUseScript && isExist)
    {
        sqlquery.prepare("INSERT INTO macro(MacroID,MacroLibName,MacroName,MacroType,"
                "TimeInterval,ControlAddr,ControlAddrType,ExecCondition,nCmpFactor,"
                "nCompID,SceneID,scriptCount)"
         "VALUES(:MacroID,:MacroLibName,:MacroName,:MacroType,"
                ":TimeInterval,:ControlAddr,:ControlAddrType,:ExecCondition,:nCmpFactor,"
                ":nCompID,:SceneID,:scriptCount)");

        sqlquery.bindValue(":MacroID",QVariant(count));// ��ı� id
        sqlquery.bindValue(":MacroLibName",QVariant(macroName));//
        sqlquery.bindValue(":MacroName",QVariant("MACRO_MAIN"));//
        sqlquery.bindValue(":MacroType",QVariant(6));//
        sqlquery.bindValue(":nCompID",QVariant(itemId));// �ؼ���ID
        sqlquery.bindValue(":SceneID",QVariant(nSceneId));//����ID
        sqlquery.bindValue(":scriptCount",QVariant(1));//����ID

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert textProp macro :"<<result;
    }

    /*if(isUseScript && isExist)
    {
        baseId = count - 1;
    }
    else
    {
        baseId = count;
    }*/

    int baseId =  count;
    /////////////////////////////////ÿ�����ܵ�functionId////////////////////////////////////////////
    bool t = sqlquery.prepare("INSERT INTO comboboxFun"
                              "(nItemId,eFunctionType,sPath,nFunctionId,bSaveIndex ,sFunctionName)"
                              "VALUES(:nItemId,:eFunctionType,:sPath,:nFunctionId,:bSaveIndex ,:sFunctionName)");
    qDebug() << "QDropdownAttr" << t << endl;

    int kk = m_vecSwitchItem.size();
    int numBit = 0;
    int numWord = 0;
    int numExtend = 0;
    int numWordbDynamicControl = 0;
    for(int i = 0; i < kk; i++)
    {
        if(1 == m_vecSwitchItem[i].switchType)
        {
            numBit++;
        }
        else if(2 == m_vecSwitchItem[i].switchType)
        {
            numWord++;
            if(m_vecSwitchItem[i].bDynamicControl)
            {
                numWordbDynamicControl++;
            }
        }
        else if(3 == m_vecSwitchItem[i].switchType)
        {
            numExtend++;
        }
    }
    int curBit = 0;
    int curWord = 0;
    int curEx = 0;
    for(int i = 0; i < kk; i++)
    {
        //count++;
        sqlquery.bindValue(":nItemId", QVariant(itemId));
        sqlquery.bindValue(":eFunctionType", QVariant(m_vecSwitchItem[i].switchType));
        if(1 == m_vecSwitchItem[i].switchType)
        {
            curBit++;
            sqlquery.bindValue(":nFunctionId", QVariant(baseId + curBit));
        }
        else if(2 == m_vecSwitchItem[i].switchType)
        {
            curWord++;
            sqlquery.bindValue(":nFunctionId", QVariant(baseId + numBit + curWord));
        }
        else if(3 == m_vecSwitchItem[i].switchType)
        {
            curEx++;
            sqlquery.bindValue(":nFunctionId", QVariant(baseId + numBit + numWord + curEx));
        }

        if(m_bUsePic)
        {
            QString picpath;
            bool bPic = false;
            if(PIC == m_vecSwitchItem[i].bLib || USERDEFINE == m_vecSwitchItem[i].bLib)
            {
                bPic = false;
            }
            else
            {
                bPic = true;
            }

            if (m_vecSwitchItem[i].bLib == NO_PIC)
            {

            }
            else
            {
                QString newPath = pwnd->SavePath(m_vecSwitchItem[i].sPath,boundingRect().size(),bPic);
                if(newPath != "")
                {
                    newPath = newPath.replace("\\","/");
                    newPath = newPath.section("/",-1);
                    newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
                }
                sqlquery.bindValue(":sPath",QVariant(newPath));//ͼƬ·��
            }
        }

        /*sqlquery.bindValue(":sFunctionName", QVariant(m_vecSwitchItem[i].switchFunName));
        int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
        for(int j = 0; j < lanNum; j++)
        {
            //sqlquery.bindValue(":sFunctionName", QVariant(baseId + kk + numBit + numWord + j));

        }*/
        sqlquery.bindValue(":bSaveIndex",QVariant(false));
        sqlquery.bindValue(":sFunctionName", QVariant(baseId + kk + numBit + numWord + i + numWordbDynamicControl));

        result = sqlquery.exec();
        qDebug() << "QDropdownAttr-m_vecSwitchItem" << result << endl;
    }

    /////////////////////////////////λ����Id////////////////////////////////////////////
    t = sqlquery.prepare("INSERT INTO bitSwitch"
                         "(nItemId,eOperType,bDownZero,nBitAddress)"
                  "VALUES(:nItemId,:eOperType,:bDownZero,:nBitAddress)");
    qDebug() << "bitSwitch" << t << endl;

    curBit = 0;
    for(int i = 0; i < kk; i++)
    {
        if(1 == m_vecSwitchItem[i].switchType)
        {
            count++;//����һ��
            curBit++;
            sqlquery.bindValue(":nItemId", QVariant(baseId + curBit));
            sqlquery.bindValue(":eOperType", QVariant((int)m_vecSwitchItem[i].operTypeB));
            sqlquery.bindValue(":bDownZero", QVariant(false));
            sqlquery.bindValue(":nBitAddress", QVariant(baseId + kk + curBit));

            result = sqlquery.exec();
            qDebug() << "-----QDropdownAttr-switchType------" << result << endl;

            /////////////////λ���� ��ַId//////////////////
            count++;//��ַһ��
            ADDR_PARAMENTS stParams;
            stParams.id = baseId + kk + curBit;
            stParams.itemId = baseId + curBit;
            stParams.eType = OBJ_ITEM;
            stParams.eRWtype = SCENE_CONTROL_LOOP_R;
            stParams.addrNum = -1;
            if(m_vecSwitchItem[i].operTypeB <3)
            {
                stParams.eRWtype = SCENE_CONTROL_ONCE_W;
            }
            m_vecSwitchItem[i].addrBit.compile(db,stParams);

            //result = sqlquery.exec();
            //qDebug() << "-----QDropdownAttr-switchType------" << result << endl;
        }
    }

    /////////////////////////////////�ֿ���Id////////////////////////////////////////////
    t = sqlquery.prepare("INSERT INTO wordSwitch"
                         "(nItemId,eOperType,nAddress,nDataType,bCycle,nMax,nMin,nFinalValue,bDynamicControl,nAddressConst)"
                         "VALUES(:nItemId,:eOperType,:nAddress,:nDataType,:bCycle,:nMax,:nMin,:nFinalValue,:bDynamicControl,:nAddressConst)");
    qDebug() << "wordSwitch" << t << endl;
    curWord = 0;
    int icurConstAddr = 0;
    for(int i = 0; i < kk; i++)
    {
        if(2 == m_vecSwitchItem[i].switchType)
        {
            count++;
            curWord++;
            icurConstAddr++;
            sqlquery.bindValue(":nItemId", QVariant(baseId + numBit + curWord));
            sqlquery.bindValue(":eOperType", QVariant((int)m_vecSwitchItem[i].operTypeW));
            sqlquery.bindValue(":nAddress", QVariant(baseId + kk + numBit + curWord + icurConstAddr));
            int temp = (int)m_vecSwitchItem[i].dataType;
            sqlquery.bindValue(":nDataType", QVariant(temp + 1));
            //sqlquery.bindValue(":nDataType", QVariant((int)m_vecSwitchItem[i].dataType));
            sqlquery.bindValue(":bCycle", QVariant(false));

            double max,min;
            getRange(temp,max,min);
            sqlquery.bindValue(":nMax",QVariant(max));// ����
            sqlquery.bindValue(":nMin",QVariant(min));// ����

            sqlquery.bindValue(":nFinalValue", QVariant(m_vecSwitchItem[i].value));

            qDebug() << "=========QDropdownAttr-switchType=========" << result << endl;

            /////////////////�ֿ��� ��ַId//////////////////
            count++;
            ADDR_PARAMENTS stParams;
            stParams.id = baseId + numBit + kk + curWord + icurConstAddr;
            stParams.itemId = baseId + numBit + curWord;
            stParams.eType = OBJ_ITEM;
            stParams.eRWtype = SCENE_CONTROL_LOOP_R;
            stParams.addrNum = -1;
            if(m_vecSwitchItem[i].operTypeW == 1)
            {
                stParams.eRWtype = SCENE_CONTROL_ONCE_W;
            }
			temp += 1;
            if(0x03 == temp || 0x05 == temp || 0x07 == temp || 0x08 == temp)
            {
                m_vecSwitchItem[i].addrWord.Length = 2;
                m_vecSwitchItem[i].addrConst.Length = 2;
            }
            else
            {
                m_vecSwitchItem[i].addrWord.Length = 1;
                m_vecSwitchItem[i].addrConst.Length = 1;
            }
            m_vecSwitchItem[i].addrWord.compile(db,stParams);
            //add by wxy
            sqlquery.bindValue(":bDynamicControl",QVariant(m_vecSwitchItem[i].bDynamicControl));
            if(m_vecSwitchItem[i].bDynamicControl)
            {
               count++;
               icurConstAddr++;
               ADDR_PARAMENTS stParamsConst;
               stParamsConst.id = baseId + numBit + kk + curWord + icurConstAddr;
               stParamsConst.itemId = baseId + numBit + curWord;
               stParamsConst.eType = OBJ_ITEM;
               stParamsConst.addrNum = -1;
               stParamsConst.eRWtype = SCENE_CONTROL_ONCE_R;
               m_vecSwitchItem[i].addrConst.compile(db,stParamsConst);//�����ַ��
            }
            sqlquery.bindValue(":nAddressConst",QVariant(baseId + numBit + kk + curWord + icurConstAddr));
            result = sqlquery.exec();
            //qDebug() << "=========QDropdownAttr-switchType=========" << result << endl;
        }
    }

    /////////////////////////////////�����л�Id////////////////////////////////////////////
    t = sqlquery.prepare("INSERT INTO screenSwitch"
                         "(nItemId,eOperScene,nTargetPage,bLogout,nSceneType)"
                  "VALUES(:nItemId,:eOperScene,:nTargetPage,:bLogout,:nSceneType)");

    qDebug() << "-----screenSwitch-----" << t << endl;
    curEx = 0;
    for(int i = 0; i < kk; i++)
    {
        if(3 == m_vecSwitchItem[i].switchType)
        {
            count++;
            curEx++;
            sqlquery.bindValue(":nItemId", QVariant(baseId + numBit + numWord + curEx));
            short pxcv = (short)m_vecSwitchItem[i].operType;
            sqlquery.bindValue(":eOperScene", QVariant(pxcv));
            //sqlquery.bindValue(":eOperScene", QVariant((short)m_vecSwitchItem[i].operType));
            sqlquery.bindValue(":bLogout", QVariant(m_vecSwitchItem[i].bLogout));

            int sceneIndex = 0;
            int windowIndex = 0;

            for(int j = 0; j < pwnd->pSceneSheet.size(); j++)
            {
                if(pwnd->pSceneSheet[j]->nIsSceneOrWindow == 0)
                {
                    if(pwnd->pSceneSheet[j]->sNewScreenName == m_vecSwitchItem[i].sceneName)
                    {
                        sqlquery.bindValue(":nTargetPage",QVariant(sceneIndex));// ������ַ�� id
                        break;
                    }
                    sceneIndex++;
                }
                if(pwnd->pSceneSheet[j]->nIsSceneOrWindow == 1)
                {
                    if(pwnd->pSceneSheet[j]->sNewScreenName == m_vecSwitchItem[i].sceneName)
                    {
                        sqlquery.bindValue(":nTargetPage",QVariant(windowIndex));// ������ַ�� id
                        break;
                    }
                    windowIndex++;
                }

            }
            /*if(m_vecSwitchItem[i].nSceneType < totalScreen)//����ǻ���
            {
                bool bIsScene = false;
                int XX = pwnd->copyScreen_Item->childCount();
                int j = 0;
                for(j = 0; j < XX; j++)
                {
                    if(m_vecSwitchItem[i].sceneName == pwnd->copyScreen_Item->child(j)->text(0))
                    {
                        sqlquery.bindValue(":nTargetPage", QVariant(j));
                        bIsScene = true;
                        break;
                    }
                }

                if(j == XX)
                {
                    sqlquery.bindValue(":nTargetPage", QVariant(-1));
                }
                sqlquery.bindValue(":nSceneType", QVariant(0));
            }
            else//����Ǵ���
            {
                int XX = pwnd->copyWindow_Item->childCount();
                int j = 0;
                for(j = 0; j < XX; j++)
                {
                    if(m_vecSwitchItem[i].sceneName == pwnd->copyWindow_Item->child(j)->text(0))
                    {
                        sqlquery.bindValue(":nTargetPage", QVariant(j));
                        break;
                    }
                }

                if(j == XX)
                {
                    sqlquery.bindValue(":nTargetPage", QVariant(-1));
                }

                sqlquery.bindValue(":nSceneType", QVariant(1));
            }*/

            int scenetype = 0;
            if((int)m_vecSwitchItem[i].operType > 2 && (int)m_vecSwitchItem[i].operType < 5)
            {
                scenetype = 1;
            }
            sqlquery.bindValue(":nSceneType",QVariant(scenetype));// ����

            result = sqlquery.exec();
            qDebug() << "QDropdownAttr-screenSwitch" << result << endl;
        }
    }

    ////////////////////////�����Ա�////////////////////////////////////
    t = sqlquery.prepare("INSERT INTO itemMutilLanguage"
                         "(nItemId,nStatusId,nLanguageId,sText,sFontType,nFontSize)"
                   "VALUES(:nItemId,:nStatusId,:nLanguageId,:sText,:sFontType,:nFontSize)");

    int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    for(int i = 0; i < kk; i++)
    {
        for(int j = 0; j < lanNum; j++)
        {
            /*if(isUseScript && isExist)
            {
                //baseId = count - 1;
                sqlquery.bindValue(":nItemId", QVariant(count - 1));
            }
            else
            {
                //baseId = count;
                sqlquery.bindValue(":nItemId", QVariant(count));
            }*/
            sqlquery.bindValue(":nItemId", QVariant(count));

            //sqlquery.bindValue(":nItemId", QVariant(baseId));
            sqlquery.bindValue(":nStatusId", QVariant(0));
            sqlquery.bindValue(":nLanguageId", QVariant(j));
            if(j >= m_vecSwitchItem[i].vecSwitchFunName.size())
            {
                sqlquery.bindValue(":sText", QVariant(QObject::tr("����1")));
            }
            else
            {
                sqlquery.bindValue(":sText", QVariant(m_vecSwitchItem[i].vecSwitchFunName[j]));
            }
            sqlquery.bindValue(":sFontType", QVariant(0));
            sqlquery.bindValue(":nFontSize", QVariant(0));

            result = sqlquery.exec();
            qDebug() << "AAAAAAAAAAAAAAAAAAAAA" << result << endl;
        }
        count++;
    }

    /*if(isUseScript && isExist)
    {
        count++;
        sqlquery.prepare("INSERT INTO macro(MacroID,MacroLibName,MacroName,MacroType,"
                "TimeInterval,ControlAddr,ControlAddrType,ExecCondition,nCmpFactor,"
                "nCompID,SceneID)"
         "VALUES(:MacroID,:MacroLibName,:MacroName,:MacroType,"
                ":TimeInterval,:ControlAddr,:ControlAddrType,:ExecCondition,:nCmpFactor,"
                ":nCompID,:SceneID)");

        sqlquery.bindValue(":MacroID",QVariant(count));// ��ı� id
        sqlquery.bindValue(":MacroLibName",QVariant(macroName));//
        sqlquery.bindValue(":MacroName",QVariant(functionName));//
        sqlquery.bindValue(":MacroType",QVariant(6));//
        sqlquery.bindValue(":nCompID",QVariant(baseId));// �ؼ���ID
        sqlquery.bindValue(":SceneID",QVariant(nSceneId));//����ID

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert textProp macro :"<<result;
    }*/
}

void QDropdownAttr::getRange(int dataType,double &nMax,double &nMin)
{
    nMax = 0;
    nMin = 0;
    int decLen = 0;
    switch(dataType)
    {
    case 1://16λ����
    case 5://16λBCD��
        {
            nMax = 32767;
            nMin = -32768;
            decLen = 0;
        }
        break;
    case 2://32λ����
    case 6://32λBCD��
        {
            nMax = 2147483647L;
            nMin = -2147483648L;
            decLen = 0;
        }
        break;
    case 3://16λ������
        {
            nMax = 65535;
            nMin = 0;
            decLen = 0;
        }
        break;
    case 4://32λ������
        {
            nMax = 4294967295UL;
            nMin = 0;
            decLen = 0;
        }
        break;
    case 7://32λ������
        {
            nMax = 2147483647L;
            nMin = -2147483648L;
            decLen = 10;
        }
        break;
    }
    if (nMin>0)
    {
        nMin = nMin*-1;
    }
}

void QDropdownAttr::save(QDataStream &stream)//��item����������
{
    QVisableItem::save(stream);

    stream << m_nShowNumber;
    stream << totalScreen;
    stream << isUseScript;
    stream << macroName;
    stream << functionName;

    stream << m_strFontName;          //�������͵�����
    stream << m_nFontSize;            //�����С
    stream << m_nLanType;             //��������
    stream << m_nFontStyle;           //������ʽ����׼�����壬б�壩
    stream << m_nFontColor;           //������ɫ
    stream << m_nBackColor;           //������ɫ
    stream << m_nAlpha;

    stream << m_bUsePic;
    //�б��
    SwitchInfo item;
    item = m_vecSwitchItem[0];
    int lanNum = item.vecSwitchFunName.size();
    stream << lanNum;
    for(int i = 0; i < m_nShowNumber; i++)
    {
        item = m_vecSwitchItem.at(i);

        stream << item.switchType;
        for(int j = 0; j < lanNum; j++)
        {
            //stream << item.switchFunName[j];
            stream << item.vecSwitchFunName[j];
        }

        stream << item.addrBit;
        stream << (short)item.operTypeB;

        stream << item.addrWord;
        stream << (short)item.operTypeW;
        stream << (short)item.dataType;
        stream << item.value;
        if(pwnd->getProVersion() >= 3163)//wxy
        {
            stream << item.bDynamicControl;
            if(item.bDynamicControl)
            {
                stream << item.addrConst;
            }
        }

        stream << (short)item.operType;
        //stream << item.nSceneType;
        stream << item.sceneName;
        stream << item.bLogout;
        stream << (short)item.bLib;
        stream << item.sPath;
    }
}

void QDropdownAttr::load(QDataStream &stream)//������������item
{
    QVisableItem::load(stream);

    stream >> m_nShowNumber;
    stream >> totalScreen;
    stream >> isUseScript;
    stream >> macroName;
    stream >> functionName;

    stream >> m_strFontName;          //�������͵�����
    stream >> m_nFontSize;            //�����С
    stream >> m_nLanType;             //��������
    stream >> m_nFontStyle;           //������ʽ����׼�����壬б�壩
    stream >> m_nFontColor;           //������ɫ
    stream >> m_nBackColor;           //������ɫ
    stream >> m_nAlpha;

    if(pwnd->getProVersion() >= 3170)
    {
        stream >> m_bUsePic;
    }
    else
        m_bUsePic = false;

    SwitchInfo item;
    int lanNum;
    stream >> lanNum;
    short temp;
    QString strTemp;
    for(int i = 0; i < m_nShowNumber; i++)
    {
        stream >> item.switchType;
        for(int j = 0; j < lanNum; j++)
        {
            //stream >> item.switchFunName;
            stream >> strTemp;
            item.vecSwitchFunName.push_back(strTemp);
        }

        stream >> item.addrBit;
        stream >> temp;
        item.operTypeB = (BIT_OPER_TYPE)temp;

        stream >> item.addrWord;
        stream >> temp;
        item.operTypeW = (WORD_OPER_TYPE)temp;
        stream >> temp;
        item.dataType  = (DATA_TYPE)temp;
        stream >> item.value;
        if(pwnd->getProVersion() >= 3163)//wxy
        {
            bool bDynamicControl;
            stream >> bDynamicControl;
            item.bDynamicControl = bDynamicControl;
            if(bDynamicControl)
            {
               stream >> item.addrConst;
            }
        }
        else
        {
            item.bDynamicControl = false;
            item.addrConst.sShowAddr = "LW0";
        }

        stream >> temp;
        item.operType = (SCENE_OPER_TYPE)temp;
        //stream >> item.nSceneType;
        stream >> item.sceneName;
        stream >> item.bLogout;
        if(pwnd->getProVersion() >= 3170)
        {
            stream >> temp;
            item.bLib = (EITEM_TYPE)temp;
            stream >> item.sPath;
        }
        else
        {
            item.bLib = NO_PIC;
            item.sPath = QString("");
        }



        m_vecSwitchItem.push_back(item);
        item.vecSwitchFunName.clear();
    }
}

QList<Keyboard> QDropdownAttr::getAddress()
{
    QList<Keyboard> addrs;

    int kk = m_vecSwitchItem.size();
    for(int i = 0; i < kk; i++)
    {
        if(1 == m_vecSwitchItem[i].switchType)
        {
            addrs << m_vecSwitchItem[i].addrBit;
        }
        else if(2 == m_vecSwitchItem[i].switchType)
        {
            addrs << m_vecSwitchItem[i].addrWord;
        }
    }

    return addrs;
}

void QDropdownAttr::setAddress(QList<Keyboard> addr)
{
    if (addr.size() <0)
    {
        return;
    }

    int j = 0;
    int kk = m_vecSwitchItem.size();
    for(int i = 0; i < kk; i++)
    {
        if(1 == m_vecSwitchItem[i].switchType)
        {
            m_vecSwitchItem[i].addrBit = addr.at(j);
            j++;
        }
        else if(2 == m_vecSwitchItem[i].switchType)
        {
            m_vecSwitchItem[i].addrWord = addr.at(j);
            j++;
        }
    }
}

QVector<ADDRPRO> QDropdownAttr::getAllItemAddr()
{
    addrs.clear();
    ADDRPRO temp;

    int kk = m_vecSwitchItem.size();
    for(int i = 0; i < kk; i++)
    {
        if(1 == m_vecSwitchItem[i].switchType)
        {
            temp.pAddr = &m_vecSwitchItem[i].addrBit;
            temp.str   = QObject::tr("������--λ����");
            temp.type  = 0;
            addrs << temp;
        }
        else if(2 == m_vecSwitchItem[i].switchType)
        {
            temp.pAddr = &m_vecSwitchItem[i].addrWord;
            temp.str   = QObject::tr("������--�ֿ���");
            temp.type  = 1;
            addrs << temp;
        }
    }

    QVector<ADDRPRO> AddrList;
    AddrList = QVisableItem::getAllItemAddr();
    for(int i = 0; i < AddrList.size(); i++)
    {
        temp.pAddr = AddrList.at(i).pAddr;
        temp.str   = QObject::tr("������--Ȩ�޵�ַ");
        temp.type  = AddrList.at(i).type;
        addrs << temp;
    }
    return addrs;
}

void QDropdownAttr::changeItemLanguageAttr(int lanNum)
{
    int itemLanNum  = m_vecSwitchItem[0].vecSwitchFunName.size();
    int number      = m_vecSwitchItem.size();

    if(lanNum > itemLanNum)//��Ҫ����������
    {
        for(int i = 0; i < number; i++)
        {
            QString str =  QObject::tr("����1");
            for(int j = itemLanNum; j < lanNum; j++)
            {
                m_vecSwitchItem[i].vecSwitchFunName.push_back(str);
            }
        }
    }
    else if(lanNum < itemLanNum)//��Ҫɾ������
    {
        for(int i = 0; i < number; i++)
        {
            for(int j = itemLanNum - 1; j >= lanNum; j--)
            {
                m_vecSwitchItem[i].vecSwitchFunName.remove(j);
            }
        }
    }
}

QStringList QDropdownAttr::getAllFonts()
{
    QStringList ls;
    ls.clear();
    ls << m_strFontName;
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

int QDropdownAttr::checkMacroName(QString &msg)
{
    int result = -1;//�ű�������
    msg = macroName;
    if(!isUseScript)//δʹ�ýű�
    {
        return 1;
    }
    foreach(Macro mac,pwnd->macros)
    {
        if(mac.libName == macroName)
        {
            if(mac.isCompiled())//�Ѿ�����ͨ��
            {
                result = 1;
            }
            else//δ����ͨ��
            {
                result = 0;
            }
            break;
        }
    }
    return result;
}

TEXTPRO QDropdownAttr::getAllItemText()
{
    //m_vecSwitchItem[i].vecSwitchFunName
    int iStaCount = m_nShowNumber; //��״̬��Ŀ
    int iLan = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //����������

    vText.sCtrlName = this->getItemName(); //�ؼ�����
    vText.iLanguage.clear();
    vText.vStatus.clear();
    vText.vText.clear();
    vText.vMsg.clear();

    for(int i = 0; i < iLan; i++) //�ܵ�����ɨ��
    {
        for(int j = 0; j < iStaCount; j++)//��״̬��Ŀɨ��
        {
            vText.iLanguage.append(i);
            vText.vStatus.append(j);
            vText.vMsg.append(QObject::tr("�����б�:")+QString("%1").arg(j));
            vText.vText.append(m_vecSwitchItem[j].vecSwitchFunName[i]);
        }
    }
    return vText;
}

void QDropdownAttr::replaceAllItemText(int iLan, int iSta, QString sNewText)
{
    int iL = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //����������
    int iStaCount = m_nShowNumber; //��״̬��Ŀ
    if( (iLan >= 0 && iLan < iL) && (iSta >= 0 && iSta < iStaCount))
    {
        m_vecSwitchItem[iSta].vecSwitchFunName[iLan] = sNewText;
    }
}
