#include "switchitem.h"
#include "qpixmapitem.h"
#include "Frame/mainwindow.h"
#include "Macro/macro.h"

extern MainWindow *pwnd;
SwitchItem::SwitchItem()
    :QVisableItem(0)
{
	curSta = 0;
}

//��һ��Ĭ�ϵĿ���
void SwitchItem::SetDefault()
{
    QRectF rect = QRectF(0,0,100,100);
    frameRect = new QRectItem(rect);
    frameRect->SetBackColor(QColor(192,192,192));
    frameRect->SetLineType(0);
    frameRect->SetAlpha(0);

    //rect = QRectF(5,5,90,90);
    //backRect = new QRectItem(rect);
    //backRect->SetBackColor(QColor(192,192,192));

    QPixmap picture(":/btn/images/default.png");
    //picture = picture.scaled(100,100);

    QPixmapItem *pixItem = new QPixmapItem(picture,QSize(100,100));
    backItem = pixItem;

    QSimpleTextItem *text = new QSimpleTextItem(rect,"");

    text->SetRectOutLine(false);
    textItem = text;

    addToGroup(frameRect);
    addToGroup(backItem);
    addToGroup(textItem);
}

int SwitchItem::GroupType()
{
    return SAM_DRAW_GROUP_SWITCH;
}

QGraphicsItem *SwitchItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    SwitchItem *itemGroup = new SwitchItem();

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

    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    //��Ӹ��ƻ������ԵĴ���
    //itemGroup->gType = gType;
    itemGroup->SavefunctionPage(switchType,bitPro,wordPro,scenePro,funPro);
    itemGroup->SaveMonitorPage(mPro);
    itemGroup->SaveExteriorPage(mPro.count,statusText,statusPic);
    itemGroup->SaveSecurityPro(&sPro);
    itemGroup->bMacro = bMacro;
    itemGroup->bSlid  = bSlid;
    itemGroup->macroName = macroName;
    itemGroup->functionName = functionName;
    itemGroup->bMacroUp = bMacroUp;
    itemGroup->macroNameUp = macroNameUp;

    qDebug() << itemGroup->GroupType();
    //��������������ͼ����ı�itemָ�룬��ͼ�⣬�ı����ĵ�ʱ��remove
    itemGroup->backItem = itemGroup->GetPicItem();
    itemGroup->textItem = itemGroup->GetTextItem();
    itemGroup->curSta = curSta;

    itemGroup->setId(id());

    if(itemGroup->childItems().size() == 0)
    {
        //delete itemGroup;
        //itemGroup = NULL;
    }
    return itemGroup;

}

void SwitchItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    count++;
    QVisableItem::compile(db,nSceneId,count,index);
    //int tablecount = 0;
    int itemId = count;
    //��Ȩ��ҳ���Ѿ������˵�ַ����Ҫ��������㲢�����趨count

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
    QMap<QString,QVariant> mapQuery;
    //����item��
//    QSqlQuery sqlquery(db);
//    sqlquery.prepare("INSERT INTO switchButton(nItemId,nSceneId,eButtonType,eWatchType,nLp,nTp,nWidth,nHeight,"
//                "nShowLp,nShowTp,nShowWidth,nShowHeight,nSwitchFunId,bSameLanguage,bSlid,bIsStartStatement,"
//                " nStatementId,eWatchDataType ,nStatTotal,nWatchAddr,nAddrType,nBitIndex,nCondition,"
//                "nZvalue,nCollidindId) "
//				"VALUES (:nItemId,:nSceneId,:eButtonType,:eWatchType,:nLp,:nTp,:nWidth,:nHeight ,:nShowLp,"
//                ":nShowTp,:nShowWidth,:nShowHeight,:nSwitchFunId,:bSameLanguage ,:bSlid,:bIsStartStatement,"
//                ":nStatementId,:eWatchDataType,:nStatTotal,:nWatchAddr,:nAddrType,:nBitIndex,"
//                ":nCondition,:nZvalue ,:nCollidindId )");
    mapQuery.insert(":nItemId",QVariant(itemId));// �� id
    mapQuery.insert(":nSceneId",QVariant(nSceneId));// scene id
    short btnType = switchType;
    mapQuery.insert(":eButtonType",QVariant(btnType+1));//��������
    short monitorType = mPro.monitorType;
    mapQuery.insert(":eWatchType",QVariant(monitorType+1));//��������
    //�����״̬��
    //if(monitorType != NONE)
        InsertStatusTable(db,itemId,count);

    QRectF rect = sceneBoundingRect();
    mapQuery.insert(":nLp",QVariant((short)(rect.left()+0.5)));//left
    mapQuery.insert(":nTp",QVariant((short)(rect.top()+0.5)));//top
    mapQuery.insert(":nWidth",QVariant((short)(rect.width()+0.5)));//width
    mapQuery.insert(":nHeight",QVariant((short)(rect.height()+0.5)));//height
    if(textItem)
        rect = textItem->sceneBoundingRect();
    mapQuery.insert(":nShowLp",QVariant((short)(rect.left()+0.5)));//�ı�����left
    mapQuery.insert(":nShowTp",QVariant((short)(rect.top()+0.5)));//�ı�����top
    mapQuery.insert(":nShowWidth",QVariant((short)(rect.width()+0.5)));//�ı�����width
    mapQuery.insert(":nShowHeight",QVariant((short)(rect.height()+0.5)));//�ı�����height

    //������Ҫ����һ����,������λ���ء��ֿ��ء����ܿ��ء����濪�أ� id Ϊtablecount+count
    if(switchType != INDICATOR_SWITCH)
    {
        count++;
        mapQuery.insert(":nSwitchFunId",QVariant(count));//�������ͱ�
        InsertSwitchTable(db,btnType,count);
    }
    else
    {
        mapQuery.insert(":nSwitchFunId",QVariant(-1));//�������ͱ�
    }
    
    mapQuery.insert(":bSlid",QVariant(bSlid));//��������
    mapQuery.insert(":bSameLanguage",QVariant(false));//�Ƿ�ʹ��ͬһ�����ԣ���ȡ����û������

    mapQuery.insert(":bIsStartStatement",QVariant(bMacro));//�Ƿ�ʹ�ú�ָ��

    mapQuery.insert(":bIsStartStatementUp",QVariant(bMacroUp));//�Ƿ�ʹ�ú�ָ��
    bool isExist = false;
    if(bMacro)
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
            //pwnd->information(QObject::tr("���غ걻ɾ��"));
            pwnd->information(QObject::tr("����ʹ�õĺ�") + macroName +QObject::tr("����") + functionName + QObject::tr("��ɾ��"), MSG_WARNING);
            //QMessageBox::about(this, QObject::tr("����"), QObject::tr("������걻ɾ��"));
        }
    }

    if(bMacro && isExist)
    {
        count++;
        insertMacroTable(db,itemId,count,nSceneId,macroName);
        mapQuery.insert(":nStatementId",QVariant(count));//��ָ�����
    }
    else
    {
        mapQuery.insert(":nStatementId",QVariant(0));//��ָ�����
    }

    isExist = false;
    if(bMacroUp)
    {
        foreach(Macro lib,pwnd->macros)
        {
            if(lib.libName == macroNameUp)
            {
                isExist = true;
            }
        }

        if(!isExist)
        {
            pwnd->information(QObject::tr("����ʹ�õĺ�") + macroNameUp  + QObject::tr("��ɾ��"), MSG_WARNING);
        }
    }

    if(bMacroUp && isExist)
    {
        count++;
        insertMacroTable(db,itemId,count,nSceneId,macroNameUp);
        mapQuery.insert(":nStatementIdUp",QVariant(count));//��ָ�����
    }
    else
    {
        mapQuery.insert(":nStatementIdUp",QVariant(0));//��ָ�����
    }

    int monitorDataType = mPro.dataType;
    //qDebug() << "monitorDataType: "<< monitorDataType;
    switch(mPro.dataType)
    {
    case 0:
    case 1:
        monitorDataType = monitorDataType+4;
        break;
    case 2:
    case 3:
        break;
    case 4:
        monitorDataType = (int)FLOAT_32;
        break;
    }
    mapQuery.insert(":eWatchDataType",QVariant(monitorDataType));//������������
    short statusSount = mPro.count;
    mapQuery.insert(":nStatTotal",QVariant(statusSount));//���ӵ���״̬��
    mapQuery.insert(":nAddrType",QVariant(mPro.bBitAddr));//���ӵĵ�ַ���� �Ƿ�Ϊλ��ַ
    mapQuery.insert(":nBitIndex",QVariant(mPro.bitIndex));//���ӵ��ֵ�ַ λ��
    mapQuery.insert(":nCondition",QVariant(mPro.valueType));//״̬�л�����
    //������ӵ�ַ��
    if(monitorType != NONE)
    {
        count++;
        ADDR_PARAMENTS stParams;
        stParams.id = count;
        stParams.itemId = itemId;
        stParams.eType = OBJ_ITEM;
        stParams.addrNum = -1;
        stParams.eRWtype = SCENE_CONTROL_LOOP_R;
        mPro.addr.compile(db,stParams);
        mapQuery.insert(":nWatchAddr",QVariant(count));//���ӵ�ַID
    }
    else
        mapQuery.insert(":nWatchAddr",QVariant());//���ӵ�ַID

    mapQuery.insert(":nZvalue",QVariant(zValue()));//���

    mapQuery.insert(":nCollidindId",QVariant(index));//��ײID

    pwnd->inSertDbQuery("switchButton",mapQuery);
    //bool result = false;
    //result = sqlquery.exec();
    //qDebug() << "insert switchButton table :"<<result;
}

void SwitchItem::redrawForChangeLanguage(int index)
{
    int curLan = index;
    QSimpleTextItem *pTextItem = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pTextItem && curLan >= 0 && curSta >= 0
		&& curSta<mPro.count&& curLan < statusText[curSta].size())
    {
        pTextItem->SetText(statusText[curSta][curLan].text);
        pTextItem->SetFontColor(statusText[curSta][curLan].color);
        pTextItem->SetFontSize(statusText[curSta][curLan].size);
        pTextItem->SetFontName(statusText[curSta][curLan].sfont);
        int showProp = statusText[curSta][curLan].showProp;
        bool underline  = (showProp & 15) >> 3;
        bool italic = (showProp & 3) >> 1;
        bool bold = showProp & 1;
        pTextItem->SetFontBold(bold);
        pTextItem->SetFontUnderLine(underline);
        pTextItem->SetFontItalic(italic);
    }
}

void SwitchItem::redrawForChangeStatus(int index, int lan)
{
    int totalState = this->getItemStates().size();
    if(totalState <= index)
    {
        return;//Ŀǰû�����״̬
    }

    if(backItem && lan >= 0 && index >= 0
            && index < statusPic.size() && lan < statusText[index].size())
    {
    if(curSta == index)
    {
        //return;
    }
        curSta = index;
        EITEM_TYPE bLib = statusPic[index].bLib;
        SetPicture(statusPic[index].path,bLib,statusPic[index].nAlpha,statusPic[index].color);
        redrawForChangeLanguage(lan);
    }
	
}

int SwitchItem::getCurrentState()
{
    if(mPro.monitorType != NONE)
        return curSta;
    else
        return 0;
}

QStringList SwitchItem::getItemStates()
{
    QStringList ls;
    ls.clear();


    QString str;
    for(int i = 0; i < mPro.count; i++)
    {
        str = QObject::tr("״̬") + QString("%1").arg(i);
        ls.append(str);
    }

    return ls;
}

void SwitchItem::save(QDataStream &stream)
{
    QVisableItem::save(stream);
    //��������ҳ������
    int nType = 0;
    nType=(int)switchType;
    stream << nType;
    if(switchType==BIT_SWITCH)//λ����
    {
        stream << bitPro.addr;
        nType=(int)bitPro.operType;
        stream << nType;
        stream << bitPro.bDown;
		stream << bitPro.bConfirm;
		stream << bitPro.nTimeout;

    }
    if(switchType==WORD_SWITCH)//�ֿ���
    {
        stream << wordPro.addr;
        nType=(int)wordPro.dataType;
        stream << nType;
        nType=(int)wordPro.operType;
        stream << nType;
        stream << wordPro.value;
		stream << wordPro.bCycle;
		stream << wordPro.nMax;
		stream << wordPro.nMin;
        if(pwnd->getProVersion() >= 3163)
        {
            stream << wordPro.bDynamicControl;
            if(wordPro.bDynamicControl)
            {
               stream << wordPro.addrConst;
            }
        }
    }
    if(switchType==SCENE_SWITCH)//���濪��
    {
        stream << scenePro.sceneName;
        nType=(int)scenePro.operType;
        stream << nType;
        stream << scenePro.bLogout;
        stream << scenePro.nSlideStyle;
    }
    if(switchType==PECULIAR_SWITCH)//���ⰴť
    {
        nType=(int)funPro.operType;
        stream << nType;
        stream << funPro.functionIndex;
        stream << funPro.windowName;
        stream << funPro.IsCheckX;
        stream << funPro.IsCheckY;
    }
    //�ű�����
    stream << bSlid;
    stream << bMacro;
    stream << macroName;
    stream << functionName;

    stream << bMacroUp;
    stream << macroNameUp;

    //����ҳ������
    stream << mPro.addr;
    stream << mPro.bBitAddr;
    stream << mPro.bitIndex;
    stream << mPro.bSameAddr;
    stream << mPro.count;
    nType=(int)mPro.dataType;
    stream << nType;
    nType=(int)mPro.monitorType;
    stream << nType;
    stream << mPro.values;
    stream << mPro.valueType;
    stream << curSta;

    //�������
    //�ı�
    stream << statusIndex;

    int statusTextSize=statusText.size();
    stream << statusTextSize;
    for(int i=0;i<statusTextSize;i++)//��һ��ѭ��
    {
        int listSize = statusText[i].size();
        stream << listSize;
        for(int j=0;j<listSize;j++){//�ڶ���ѭ��
            stream << statusText[i][j].color;
            stream << statusText[i][j].sfont;
            stream << statusText[i][j].showProp;
            stream << statusText[i][j].size;
            stream << statusText[i][j].text;
        }
    }
    //ͼƬ
    int pictureSize=statusPic.size();
    stream << pictureSize;
    for(int i=0;i<pictureSize;i++)
    {
        int type = int(statusPic[i].bLib);
        stream << type;
        stream << statusPic[i].path;
		type = statusPic[i].eFlick;
		stream << type;
        stream << statusPic[i].nAlpha;
		stream << statusPic[i].color;
    }
}

void SwitchItem::load(QDataStream &stream)
{
    QVisableItem::load(stream);
    //��������ҳ������
    int nType = 0;
    stream >> nType;
    switchType=(SWITCH_TYPE)nType;

    if(switchType==BIT_SWITCH)//λ����
    {
        stream >> bitPro.addr;
        stream >> nType;
        bitPro.operType=(BIT_OPER_TYPE)nType;
        stream >> bitPro.bDown;
		stream >> bitPro.bConfirm;
		stream >> bitPro.nTimeout;

    }
    if(switchType==WORD_SWITCH)//�ֿ���
    {
        stream >> wordPro.addr;
        stream >> nType;
        wordPro.dataType=(DATA_TYPE)nType;
        stream >> nType;
        wordPro.operType=(WORD_OPER_TYPE)nType;

        stream >> wordPro.value;
		stream >> wordPro.bCycle;
		stream >> wordPro.nMax;
		stream >> wordPro.nMin;
        if(pwnd->getProVersion() >= 3163)
        {
            bool bDynamicControl;
            stream >> bDynamicControl;
            wordPro.bDynamicControl = bDynamicControl;
            if(bDynamicControl)
            {
                stream >> wordPro.addrConst;
            }
        }
        else
        {
            wordPro.bDynamicControl = false;
            wordPro.addrConst.sShowAddr = "LW0";
        }
    }
    if(switchType==SCENE_SWITCH)//���濪��
    {
        stream >> scenePro.sceneName;
        stream >> nType;
        scenePro.operType=(SCENE_OPER_TYPE)nType;

        stream >> scenePro.bLogout;
        if(pwnd->getProVersion() < 3125)//�ɰ汾
        {
            scenePro.nSlideStyle = 0;
        }
        else
        {
            stream >> scenePro.nSlideStyle;
        }
    }
    if(switchType==PECULIAR_SWITCH)//���ⰴť
    {
        stream >> nType;
        funPro.operType=(PECULIAR_TYPE)nType;
        stream >> funPro.functionIndex;
        stream >> funPro.windowName;
        if(pwnd->getProVersion() < 3020)//�ɰ汾
        {
            funPro.IsCheckX = false;
            funPro.IsCheckY = false;
        }
        else
        {
            stream >> funPro.IsCheckX;
            stream >> funPro.IsCheckY;
        }
    }
    if(pwnd->getProVersion() >= 2564)
    {
        stream >> bSlid;
    }
    else
    {
        bSlid = false;
    }
    //�ű�����
    stream >> bMacro;
    stream >> macroName;
    stream >> functionName;

    if(pwnd->getProVersion() >= 3457)
    {
        stream >> bMacroUp;
        stream >> macroNameUp;
    }
    else
    {
        bMacroUp = false;
    }


    //����ҳ������
    stream >> mPro.addr;
    stream >> mPro.bBitAddr;
    stream >> mPro.bitIndex;
    stream >> mPro.bSameAddr;
    stream >> mPro.count;
    stream >> nType;
    mPro.dataType=(DATA_TYPE)nType;
    stream >> nType;
    mPro.monitorType=(MONITOR_TYPE)nType;
    if(pwnd->getProVersion() >= 3452)
    {
        stream >> mPro.values;
    }
    else
    {
        QVector<int >values;
        stream >> values;
        QVector<double>dValues;
        foreach(int v,values)
        {
            dValues << v;
        }
        mPro.values = dValues;
    }


    stream >> mPro.valueType;
    stream >> curSta;

    //�������
    //�ı�
    stream >> statusIndex;

    int statusTextSize=0;
    stream >> statusTextSize;
    statusText.resize(statusTextSize);
    for(int i=0;i<statusTextSize;i++)//��һ��ѭ��
    {
        int listSize=0;
        stream >> listSize;
        statusText[i].resize(listSize);
        for(int j=0;j<listSize;j++){//�ڶ���ѭ��
            stream >> statusText[i][j].color;
            stream >> statusText[i][j].sfont;
            stream >> statusText[i][j].showProp;
            stream >> statusText[i][j].size;
            stream >> statusText[i][j].text;
        }
    }
    //ͼƬ
    int pictureSize=0;
    stream >> pictureSize;
    statusPic.resize(pictureSize);
    for(int i=0;i<pictureSize;i++)
    {
        int type = 0;
        stream >> type;
        statusPic[i].bLib = EITEM_TYPE(type);
        stream >> statusPic[i].path;
		stream >> type;
		statusPic[i].eFlick = FLICK_TYPE(type);

        stream >> statusPic[i].nAlpha;
		stream >> statusPic[i].color;
    }
	backItem = GetPicItem();
	textItem = GetTextItem();
}

void SwitchItem::SetPicture(QString path,EITEM_TYPE blib,int alpha,QColor color)
{
	if (!textItem)
	{
		return;
	}
    if(!backItem)//����ͼƬָ��Ϊ�գ�������ֱ�ӷ���
    {
		QRectF rect = textItem->sceneBoundingRect();

		QRectItem *rectItem = new QRectItem(rect);
		QPointF pos = rectItem->boundingRect().topLeft();

		rectItem->setPos(rect.topLeft()-pos);
		rectItem->setData(GROUP_NAME_KEY,QVariant(SWITCH_BACK_TYPE));
		backItem = rectItem;
    }
    if(LIBRARY == blib)
    {
        DrawItemToScene GroupFunction;
        QList <QGraphicsItem*> listItem;
        QStringList str = path.split('-');
        if(str.isEmpty())
        {
            return;
        }
        QGraphicsItem *pCopyItem = NULL;
        int nLoadPag = str.at(0).toInt();

        if(1 == str.at(2).toInt())
        {
            if(pwnd->vBaseLibraryScene.isEmpty())
            {
                return;
            }
            listItem = pwnd->vBaseLibraryScene.at(nLoadPag)->TopItems();
            foreach (QGraphicsItem * pItem, listItem)
            {
                QString sname = pItem->data(GROUP_NAME_KEY).toString();
                if (path == sname)
                {
                    GroupFunction.CopyItem(&pCopyItem,pItem);
                    break;
                }
            }
        }
        else if(2 == str.at(2).toInt())
        {
                SamDrawScene *pSvene = NULL;
                QVector <SamDrawScene *> vScene;
                vScene.clear();
                QFile file("UserDefineLibraryLib.sk");
                if(!file.open(QIODevice::ReadOnly))
                {
                    return;
                }
                QDataStream openData(&file);
                int sceneSize = 0;
                openData >> sceneSize;
                for(int i =0; i< sceneSize; i++)
                {
                    pSvene = new SamDrawScene();
                    openData >> pSvene;
                    vScene.push_back(pSvene);
                }
                listItem = vScene.at(nLoadPag)->TopItems();
                foreach (QGraphicsItem * pItem, listItem)
                {
                    QString sname = pItem->data(GROUP_NAME_KEY).toString();
                    if (path == sname)
                    {
                        GroupFunction.CopyItem(&pCopyItem,pItem);
                        break;
                    }
                }
                file.close();
        }
        if(!pCopyItem) return ;
        QGroupItem *pBaseItem = new QGroupItem(pCopyItem);
        pBaseItem->SetWidth(backItem->boundingRect().width());
        pBaseItem->SetHeigth(backItem->boundingRect().height());
        QPointF pos = backItem->sceneBoundingRect().topLeft();
        QPointF pt = pCopyItem->boundingRect().topLeft();
        pCopyItem->setPos(pos-pt);
        pCopyItem->setData(GROUP_NAME_KEY,QVariant(SWITCH_BACK_TYPE));

        QGraphicsItem *pItem = this->topLevelItem();
        QItemGroup *pArentItem = dynamic_cast<QItemGroup *> (pItem);
        if(pArentItem)
        {
            pArentItem->removeFromGroup(textItem);
            pArentItem->removeFromGroup(backItem);
        }

        if(scene())
        {
            scene()->removeItem(backItem);
            scene()->removeItem(textItem);
        }
        backItem = pCopyItem;

        backItem->setFlag(QGraphicsItem::ItemIsMovable,true);
        backItem->setFlag(QGraphicsItem::ItemIsSelectable,false);
        addToGroup(backItem);
        addToGroup(textItem);
    }
    else if (blib == USERDEFINE || blib == PIC)
    //����ѡ��ͼƬ
    {
        QPixmap picture(path);
        if(picture.isNull())
        {
            picture.load(":/btn/images/default.png");
            if(picture.isNull())
            {
                return;
            }
            else if(curSta < statusPic.size())
            {
                qDebug() << "status "<< curSta <<"picture not Exist! load default";
                qDebug() <<"path:"<< path;
                statusPic[curSta].path = ":/btn/images/default.png";
            }
        }

        QRectF rect = backItem->boundingRect();

        QPixmapItem *pixItem = new QPixmapItem(picture,QSize(rect.width(),rect.height()));

        QPointF pos = backItem->sceneBoundingRect().topLeft();
        QPointF pt = pixItem->boundingRect().topLeft();
        pixItem->setPos(pos-pt);

        //removeFromGroup(backItem);
        //removeFromGroup(textItem);

        QGraphicsItem *pItem = this->topLevelItem();
        QItemGroup *pArentItem = dynamic_cast<QItemGroup *> (pItem);
        if(pArentItem)
        {
            pArentItem->removeFromGroup(textItem);
            pArentItem->removeFromGroup(backItem);
        }

        if(scene())
        {
            scene()->removeItem(backItem);
            scene()->removeItem(textItem);
        }


        backItem = pixItem;
        addToGroup(backItem);
        addToGroup(textItem);

    }
	else
	{
		QRectF rect = backItem->sceneBoundingRect();

		QRectItem *rectItem = new QRectItem(rect);
		QPointF pos = rectItem->boundingRect().topLeft();

		rectItem->setPos(rect.topLeft()-pos);
        rectItem->SetBackColor(color);
		rectItem->SetAlpha(alpha);
        if(alpha != 0)
        {
            rectItem->SetLineType(1);
        }
        else//wxy ͸����Ϊ0��Ϊ����
        {
            rectItem->SetLineType(2);
        }
		rectItem->SetLineColor(Qt::black);
		rectItem->setData(GROUP_NAME_KEY,QVariant(SWITCH_BACK_TYPE));
        rectItem->setFlag(QGraphicsItem::ItemIsSelectable,false);

                QGraphicsItem *pItem = this->topLevelItem();
                QItemGroup *pArentItem = dynamic_cast<QItemGroup *> (pItem);
                if(pArentItem)
                {
                    pArentItem->removeFromGroup(textItem);
                    pArentItem->removeFromGroup(backItem);
                }

		if(scene())
		{
			scene()->removeItem(backItem);
			scene()->removeItem(textItem);
		}

                rectItem->setFlag(QGraphicsItem::ItemIsSelectable,false);
		backItem = rectItem;
		addToGroup(backItem);
		addToGroup(textItem);
	}
}

//�����������ҳ������
void SwitchItem::SavefunctionPage(
        SWITCH_TYPE Type,
        bitSwitchPro bitProperty,
        wordSwitchPro wordProperty,
        sceneSwitchPro sceneProperty,
        functionSwitchPro funProperty
        )
{
    switchType = Type;

    switch(switchType)
    {
    case BIT_SWITCH:
        SaveBitPro(bitProperty);
        break;
    case WORD_SWITCH:
        SaveWordPro(wordProperty);
        break;
    case SCENE_SWITCH:
        SaveScenePro(sceneProperty);
        break;
    case PECULIAR_SWITCH:
        SaveFunctionPro(funProperty);
        break;
    default:
        break;
    }
}

//�����������ҳ��λ��������
void SwitchItem::SaveBitPro(bitSwitchPro bitProperty)
{
    switchType = BIT_SWITCH;
    bitPro =  bitProperty;
}

//�����������ҳ���ֿ�������
void SwitchItem::SaveWordPro(wordSwitchPro wordProperty)
{
    switchType = WORD_SWITCH;
    wordPro = wordProperty;
}

//�����������ҳ�滭�濪������
void SwitchItem::SaveScenePro(sceneSwitchPro sceneProperty)
{
    switchType = SCENE_SWITCH;
    scenePro = sceneProperty;
}

//�����������ҳ�湦�ܿ�������
void SwitchItem::SaveFunctionPro(functionSwitchPro funProperty)
{
    switchType = PECULIAR_SWITCH;
    funPro = funProperty;
}

void SwitchItem::SaveIndicatorPro()
{
	switchType = INDICATOR_SWITCH;
}

void SwitchItem::SaveMonitorPage(monitorPro mProperty)
{
    mPro = mProperty;
}

void SwitchItem::SaveExteriorPage(int statusCount,textProList textpro,picProList picpro)
{
    statusText = textpro;
    statusPic = picpro;
}

//����һ����,������λ���ء��ֿ��ء����ܿ��ء����濪�أ� id Ϊcount
void SwitchItem::InsertSwitchTable(QSqlDatabase &db,int type, int &count)
{
    int itemId = count;
    //QSqlQuery sqlquery(db);
    QMap<QString,QVariant> mapQuery;
    switch(type)
    {
        case BIT_SWITCH:     //λ����
            {
//                sqlquery.prepare("INSERT INTO bitSwitch(nItemId,eOperType ,bDownZero,nBitAddress,nTimeout, bConfirm)"
//					"VALUES (:nItemId ,:eOperType, :bDownZero,:nBitAddress,:nTimeout,:bConfirm)");
                mapQuery.insert(":nItemId",QVariant(itemId));// �� id
                short opertType = bitPro.operType;
                mapQuery.insert(":eOperType",QVariant(opertType+1));//λ��������
                mapQuery.insert(":bDownZero",QVariant(bitPro.bDown));// �Ƿ���Ϊ1
                count++;
				ADDR_PARAMENTS stParams;
				stParams.id = count;
				stParams.itemId = itemId;
				stParams.eType = OBJ_ITEM;
				stParams.addrNum = -1;
                stParams.eRWtype = SCENE_CONTROL_LOOP_R;
                if(bitPro.operType == SET_BIT || bitPro.operType == RESET)
                {
                    stParams.eRWtype = SCENE_CONTROL_ONCE_W;
                }
                mapQuery.insert(":nBitAddress",QVariant(count));// ������ַ�� id
                bitPro.addr.compile(db,stParams);//�����ַ��
				if (bitPro.bConfirm)
				{
                    mapQuery.insert(":nTimeout",QVariant(bitPro.nTimeout));//��ȴ�ʱ��
				}
                mapQuery.insert(":bConfirm",QVariant(bitPro.bConfirm));//�Ƿ���Ҫ������ȷ��
                pwnd->inSertDbQuery("bitSwitch",mapQuery);
            }
            break;
        case WORD_SWITCH:    //�ֿ���
            {
//                sqlquery.prepare("INSERT INTO wordSwitch(nItemId,eOperType,nAddress,nDataType,"
//                    "bCycle ,nMax ,nMin ,nFinalValue,bDynamicControl,nAddressConst)"
//					"VALUES (:nItemId,:eOperType,:nAddress,:nDataType,"
//                    ":bCycle ,:nMax ,:nMin ,:nFinalValue, :bDynamicControl, :nAddressConst)");
                mapQuery.insert(":nItemId",QVariant(itemId));// �� id
                short opertType = wordPro.operType;
                mapQuery.insert(":eOperType",QVariant(opertType+1));//�ֲ�������
                short dataType = wordPro.dataType+2;
                mapQuery.insert(":nDataType",QVariant(dataType));// ��������
                count++;
                mapQuery.insert(":nAddress",QVariant(count));// ������ַ�� id
				ADDR_PARAMENTS stParams;
				stParams.id = count;
				stParams.itemId = itemId;
				stParams.eType = OBJ_ITEM;
				stParams.addrNum = -1;
                stParams.eRWtype = SCENE_CONTROL_LOOP_R;
                if(wordPro.operType == INPUT_VALUE)
                {
                    stParams.eRWtype = SCENE_CONTROL_ONCE_W;
                }
                wordPro.addr.compile(db,stParams);//�����ַ��

                mapQuery.insert(":bCycle",QVariant(wordPro.bCycle));// д��ֵ
                mapQuery.insert(":nMax",QVariant(wordPro.nMax));// д��ֵ
                mapQuery.insert(":nMin",QVariant(wordPro.nMin));// д��ֵ
                mapQuery.insert(":nFinalValue",QVariant(wordPro.value));// д��ֵ

                //add by wxy
                mapQuery.insert(":bDynamicControl",QVariant(wordPro.bDynamicControl));
                if(wordPro.bDynamicControl)
                {
                   count++;
                   ADDR_PARAMENTS stParams;
                   stParams.id = count;
                   stParams.itemId = itemId;
                   stParams.eType = OBJ_ITEM;
                   stParams.addrNum = -1;
                   stParams.eRWtype = SCENE_CONTROL_ONCE_R;
                   wordPro.addrConst.compile(db,stParams);//�����ַ��
                }
                mapQuery.insert(":nAddressConst",QVariant(count));
                pwnd->inSertDbQuery("wordSwitch",mapQuery);
            }
            break;
        case SCENE_SWITCH:    //���濪��
            {
//                sqlquery.prepare("INSERT INTO screenSwitch(nItemId, eOperScene,nSlideStyle,nTargetPage ,bLogout ,nSceneType)"
//                                 "VALUES (:nItemId, :eOperScene,:nSlideStyle,:nTargetPage ,:bLogout,:nSceneType)");
                mapQuery.insert(":nItemId",QVariant(count));// �� id
                short opertType = scenePro.operType;
                mapQuery.insert(":eOperScene",QVariant(opertType+1));//��������
                mapQuery.insert(":bLogout",QVariant(scenePro.bLogout));// �Ƿ�ע��
                mapQuery.insert(":nSlideStyle",QVariant(scenePro.nSlideStyle + 1));
                int sceneIndex = 0;
                int windowIndex = 0;

                for(int i = 0;i<pwnd->pSceneSheet.size();i++)
                {

                    if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 0)
                    {
                        if(pwnd->pSceneSheet[i]->sNewScreenName == scenePro.sceneName)
                        {
                            mapQuery.insert(":nTargetPage",QVariant(sceneIndex));// ������ַ�� id

                            break;
                        }
                        sceneIndex++;
                    }
                    if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 1)
                    {
                        if(pwnd->pSceneSheet[i]->sNewScreenName == scenePro.sceneName)
                        {
                            mapQuery.insert(":nTargetPage",QVariant(windowIndex));// ������ַ�� id

                            break;
                        }
                        windowIndex++;
                    }
                }
                int scenetype = 0;
                if(opertType > 1 && opertType < 4)
                {
                    scenetype = 1;
                }
                mapQuery.insert(":nSceneType",QVariant(scenetype));// ����
                pwnd->inSertDbQuery("screenSwitch",mapQuery);

            }
            break;
        case PECULIAR_SWITCH://���⿪��
            {
//                sqlquery.prepare("INSERT INTO funSwitch(nItemId,ePeculiarType ,nActionId ,nWindowID, bX, bY)"
//                                 "VALUES (:nItemId,:ePeculiarType, :nActionId,:nWindowID,:bX,:bY)");
                mapQuery.insert(":nItemId",QVariant(count));// �� id
                short opertType = funPro.operType;
                mapQuery.insert(":ePeculiarType",QVariant(opertType+1));//��������
                int funIndex = -1;
                qDebug() << "opertType "<<opertType;
                switch (opertType)
                {
                    case OPER_WINDOW:
                        funIndex =funPro.functionIndex+1;
                        break;
                    case CHANGE_LANGUAGE:
                        funIndex =funPro.functionIndex;
                        break;
                    case SAMPLING:
                        funIndex =funPro.functionIndex+3;
                        if(funIndex >14)//������ӵĹ��ܣ�ö�ټӵ������
                        {
                            funIndex = 5+funIndex;
                        }
                        break;
                    case ALARM:
                        funIndex =funPro.functionIndex+15;
                        break;
                }
                mapQuery.insert(":nActionId",QVariant(funIndex));
                int sceneIndex = 0;
                for(int i = 0;i<pwnd->pSceneSheet.size();i++)
                {
                    if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 1)
                    {
                        if(pwnd->pSceneSheet[i]->sNewScreenName == funPro.windowName)
                        {
                            break;
                        }
                        sceneIndex++;
                    }
                }

                mapQuery.insert(":nWindowID",QVariant(sceneIndex));// ��������index
                mapQuery.insert(":bX",QVariant(funPro.IsCheckX));
                mapQuery.insert(":bY",QVariant(funPro.IsCheckY));
                pwnd->inSertDbQuery("funSwitch",mapQuery);

            }
            break;
    default:
            break;
    }

//    bool result = false;
//    result = sqlquery.exec();
//    qDebug() << "insert switchXX table :"<<result;
}

//�����״̬�� id Ϊcount itemIdΪ�ؼ����id
void SwitchItem::InsertStatusTable(QSqlDatabase &db,int itemId,int &count)
{
    QMap<QString,QVariant> mapQuery;
    //QSqlQuery sqlquery(db);
//    sqlquery.prepare("INSERT INTO switchStatusProp(nItemId ,statusValue,nStatusIndex,eflick ,nAlpha,nColor,eLib ,sPath)"
//		"VALUES (:nItemId ,:statusValue,:nStatusIndex,:eflick ,:nAlpha ,:nColor,:eLib ,:sPath)");

    for(int i =0; i< mPro.count;i++)
    {

        mapQuery.insert(":nItemId",QVariant(itemId));// �ؼ��� id

        if(mPro.monitorType == POLY && mPro.values.size()== mPro.count)//ѡ���̬����
            mapQuery.insert(":statusValue",QVariant(mPro.values[i]));// ״̬�л�ֵ
        else
            mapQuery.insert(":statusValue",QVariant(i));// ״̬�л�ֵ
        mapQuery.insert(":nStatusIndex",QVariant(i));// ״̬�л�ֵ
		short flicktype = statusPic[i].eFlick;
        mapQuery.insert(":eflick",QVariant(flicktype+1));// ״̬�л�ֵ
        mapQuery.insert(":eLib",QVariant(statusPic[i].bLib+1));//�Ƿ�ѡ��ͼ��


		
        bool bPic = false;
        if(0 == statusPic[i].bLib || USERDEFINE == statusPic[i].bLib)
        {
            bPic = false;
        }
        else
        {
            bPic = true;
        }

		if (statusPic[i].bLib == NO_PIC)
		{
            QString newPath;
            mapQuery.insert(":nAlpha",QVariant(statusPic[i].nAlpha));//alpha
            mapQuery.insert(":nColor",QVariant(ColorToInt(statusPic[i].color)));//����ɫ
            mapQuery.insert(":sPath",QVariant(newPath));//ͼƬ·��
		}
		else
		{
			QString newPath = pwnd->SavePath(statusPic[i].path,boundingRect().size(),bPic);
                        if(newPath != "")
                        {
                            newPath = newPath.replace("\\","/");
                            newPath = newPath.section("/",-1);
                            newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
                        }
            mapQuery.insert(":sPath",QVariant(newPath));//ͼƬ·��
		}

        pwnd->inSertDbQuery("switchStatusProp",mapQuery);
//        bool result = false;
//        result = sqlquery.exec();
//        qDebug() << "insert switchStatusProp table :"<<result;
        InsertTextTable(db,itemId,i);
    }
}

//��������Ա�
//itemIdΪ��ǰitem(���ر�)��id��indexΪ״̬��
void SwitchItem::InsertTextTable(QSqlDatabase &db,int itemId,int index)
{
	//��������������ı䣬Ҫ�����ı�vector
	int langCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
	resizeStatus(mPro.count,langCount);
    QMap<QString,QVariant> mapQuery;
    //QSqlQuery sqlquery(db);
//    sqlquery.prepare("INSERT INTO textProp(nItemId,nStatusIndex,nLangIndex,sFont,sText,nSize,nColor,nShowProp)"
//                 "VALUES (:nItemId ,:nStatusIndex ,:nLangIndex,:sFont,:sText,:nSize,:nColor,:nShowProp)");
    
    QVector<ST_TEXT_PROP > textProList = statusText[index];
    for(int i=0; i<langCount;i++)
    {
        mapQuery.insert(":nItemId",QVariant(itemId));// �ؼ��� id
        mapQuery.insert(":nStatusIndex",QVariant(index));// ״̬��
        mapQuery.insert(":nLangIndex",QVariant(i));// ���Ժ�
        mapQuery.insert(":sFont",QVariant(textProList[i].sfont));// ���� font family
        mapQuery.insert(":sText",QVariant(textProList[i].text));// �ı�
        mapQuery.insert(":nSize",QVariant(textProList[i].size));// �ı���С
        mapQuery.insert(":nColor",QVariant(ColorToInt(textProList[i].color)));// �ı���ɫ
        int nAligment = textProList[i].showProp >> 4;
        if(0 == nAligment)
        {
            nAligment = 0x0010;//����
        }
        else if(1 == nAligment)
        {
            nAligment = 0x0020; //10 0000��
        }
        else if(2 == nAligment)
        {
            nAligment = 0x0040; //0100 0000 ��
        }
        int nshowProp = (0x000F & textProList[i].showProp);
        nshowProp = (nshowProp | nAligment);
        mapQuery.insert(":nShowProp",QVariant(nshowProp));// ��ʾ����:���壬б�壬�»��ߣ���˸
//        bool result = false;
//        result = sqlquery.exec();
//        qDebug() << "insert textProp table :"<<result;
        pwnd->inSertDbQuery("textProp",mapQuery);
    }
}

void SwitchItem::insertMacroTable(QSqlDatabase &db,int itemId,int &count,int sceneId,QString name)
{
    int macroId = count;

    QMap<QString,QVariant> mapQuery;
 //   QSqlQuery sqlquery(db);
//    sqlquery.prepare("INSERT INTO macro(MacroID , MacroLibName , MacroName , MacroType ,"
//        "TimeInterval ,ControlAddr ,ControlAddrType ,ExecCondition , nCmpFactor , "
//        "nCompID , SceneID )"
//        "VALUES (:MacroID , :MacroLibName , :MacroName , :MacroType ,"
//        ":TimeInterval ,:ControlAddr ,:ControlAddrType ,:ExecCondition , :nCmpFactor ,"
//        ":nCompID , :SceneID )");

    {
        mapQuery.insert(":MacroID",QVariant(macroId));// ��ı� id
        mapQuery.insert(":MacroLibName",QVariant(name));//
        mapQuery.insert(":MacroName",QVariant("MACRO_MAIN"));//
        mapQuery.insert(":MacroType",QVariant(6));//
        mapQuery.insert(":nCompID",QVariant(itemId));// �ؼ���ID
        mapQuery.insert(":SceneID",QVariant(sceneId));//����ID
        mapQuery.insert(":scriptCount",QVariant(1));
        pwnd->inSertDbQuery("macro",mapQuery);
//        bool result = false;
//        result = sqlquery.exec();
//        qDebug() << "insert textProp macro :"<<result;
    }
}

void SwitchItem::resizeStatus(int statuCount,int lanCount)
{
	ST_TEXT_PROP defaultText;
	defaultText.color = QColor(0,0,0);
	defaultText.showProp = false;
	defaultText.size = 10;
	defaultText.text = "";
	
	int size = statusText.size();
	int textCount = 0;

	for (int i =0; i< statuCount; i++)
	{
		textCount = lanCount -statusText[i].size();
		if ( textCount>0)
		{
			for (int j=0; j<textCount; j++)
			{
				statusText[i] << defaultText;
			}
		}
	}	
}

//��ò�����ַ
QList<Keyboard> SwitchItem::getAddress()
{
    QList<Keyboard> addrs;
    switch(switchType)
    {
    case BIT_SWITCH:     //λ����
        addrs << bitPro.addr;
        break;
    case WORD_SWITCH:     //�ֿ���
        addrs << wordPro.addr;
        break;
    case SCENE_SWITCH:     //���濪��

        break;
    case PECULIAR_SWITCH:     //�๦�ܿ���
        break;
	case INDICATOR_SWITCH:     //ָʾ��
		addrs << mPro.addr;
		break;
    }
    return addrs;
}

//���ò�����ַ
void SwitchItem::setAddress(QList<Keyboard> addr)
{
    if (addr.size() <1)
        return ;
    switch(switchType)
    {
    case BIT_SWITCH:     //λ����
        bitPro.addr = addr.first();
        if(mPro.bSameAddr && mPro.monitorType == BIT_MONITOR)
        {
            mPro.addr = addr.first();
        }
        break;
    case WORD_SWITCH:     //�ֿ���
        wordPro.addr = addr.first();
        if(mPro.bSameAddr && mPro.monitorType == POLY)
        {
            mPro.addr = addr.first();
        }
        break;
    case SCENE_SWITCH:     //���濪��

        break;
    case PECULIAR_SWITCH:     //�๦�ܿ���
        break;
	case INDICATOR_SWITCH:     //ָʾ��
		mPro.addr = addr.first();
		break;
    }
}

QStringList SwitchItem::getAllFonts()
{
    QStringList ls;
    ls.clear();
    foreach(QVector<ST_TEXT_PROP> textPros,statusText)
    {
        foreach(ST_TEXT_PROP textPro,textPros)
        {
            if (!textPro.sfont.isEmpty() && !textPro.text.isEmpty())
            {
                ls << textPro.sfont;
            }
        }
    }
    return ls;
}

void SwitchItem::replaceAllItemText(int iLan,int iSta,QString sNewText)
{
    int iL = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //����������
    int iStaCount = mPro.count; //��״̬��Ŀ
    if( (iLan >= 0 && iLan < iL) && (iSta >= 0 && iSta < iStaCount))
    {
        statusText[iSta][iLan].text = sNewText;
    }
}

TEXTPRO SwitchItem::getAllItemText() //������пؼ����ı�����
{
    int iStaCount = mPro.count; //��״̬��Ŀ
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
            vText.vMsg.append(QObject::tr("״̬:")+QString("%1").arg(j));
            vText.vText.append(statusText[j][i].text);
        }
    }
    return vText;
}

QVector<ADDRPRO> SwitchItem::getAllItemAddr()
{
    kb.clear();
    kb = QVisableItem::getAllItemAddr();
    ADDRPRO addrp;
    switch(switchType)
    {
    case BIT_SWITCH:     //λ����
         addrp.pAddr = &bitPro.addr;
         addrp.str   = QObject::tr("����--λ��ַ");
         addrp.type  = 0;
         kb << addrp;
         break;
    case WORD_SWITCH:     //�ֿ���
        addrp.pAddr = &wordPro.addr;
        addrp.str   = QObject::tr("����--�ֵ�ַ");
        addrp.type  = 1;
        kb << addrp;
        break;
    }
    switch (mPro.monitorType)
    {
    case BIT_MONITOR:
        addrp.pAddr = &mPro.addr;
        addrp.str   = QObject::tr("����--λ���ӵ�ַ");
        addrp.type  = 0;
        kb << addrp;
        break;
    case POLY:
        addrp.pAddr = &mPro.addr;
        addrp.str   = QObject::tr("����--�ּ��ӵ�ַ");
        addrp.type  = 1;
        kb << addrp;
        break;
    }
    return kb;
}

QString SwitchItem::getItemName()
{
    return QObject::tr("����");
}
int SwitchItem::checkMacroName(QString &msg)
{
    int result = -1;//�ű�������
    msg = macroName;
    if(!bMacro)//δʹ�ýű�
    {
        return 1;
    }
    foreach(Macro mac,pwnd->macros)
    {
        if(mac.libName == macroName || mac.libName == macroNameUp)
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
