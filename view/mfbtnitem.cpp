#include "mfbtnitem.h"
#include "Frame/mainwindow.h"
#include "Macro/macro.h"
#include <QSqlError>

extern MainWindow *pwnd;

MfBtnItem::MfBtnItem()
    :QVisableItem(0)
{
    mPro.monitorType = NONE;
    curSta = 0;
    statusIndex = 0;
}
MfBtnItem::~MfBtnItem()
{
}
//画一个默认的开关
void MfBtnItem::SetDefault()
{
    QRectF rect = QRectF(0,0,100,100);
    frameRect = new QRectItem(rect);
    frameRect->SetBackColor(QColor(192,192,192));
    frameRect->SetLineType(0);
    frameRect->SetAlpha(0);


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

int MfBtnItem::GroupType()//控件类型
{
    return SAM_DRAW_GROUP_MFBTN;
}

void MfBtnItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    count++;
    QVisableItem::compile(db,nSceneId,count,index);
    //int tablecount = 0;
    int itemId = count;
    //在权限页面已经增加了地址表，需要再这里计算并重新设定count

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
    sqlquery.prepare("INSERT INTO MFbtn(nItemId ,nSceneId ,nStartX,"
                     "nStartY ,nWidth ,nHeight, eflick ,nAlpha ,nColor ,eLib ,sPath ,nZvalue ,nCollidindId,"
                     "bIsStartStatement ,nScriptId, nStatTotal, nAddrType, nBitIndex, nCondition, eWatchDataType, nWatchAddr, eWatchType)"
                "VALUES (:nItemId ,:nSceneId ,:nStartX,"
				":nStartY ,:nWidth ,:nHeight, :eflick ,:nAlpha ,:nColor ,:eLib ,:sPath ,:nZvalue ,:nCollidindId,"
                ":bIsStartStatement ,:nScriptId, :nStatTotal, :nAddrType, :nBitIndex, :nCondition, :eWatchDataType, :nWatchAddr, :eWatchType)");

    sqlquery.bindValue(":nItemId",QVariant(itemId));// 表 id
    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));// scene id

    /*short flicktype = picPro.eFlick;
    sqlquery.bindValue(":eflick",QVariant(flicktype+1));// 状态切换值
    sqlquery.bindValue(":eLib",QVariant(picPro.bLib+1));//是否选择图库
    bool bPic = false;
    if(0 == picPro.bLib || USERDEFINE == picPro.bLib)
    {
        bPic = false;
    }
    else
    {
        bPic = true;
    }
	if (picPro.bLib == NO_PIC)
	{
		sqlquery.bindValue(":nAlpha",QVariant(picPro.nAlpha));//alpha
        sqlquery.bindValue(":nColor",QVariant(ColorToInt(picPro.color)));//背景色
	}
	else
	{
		QString newPath = pwnd->SavePath(picPro.path,boundingRect().size(),bPic);
                if("" != newPath)
                {
                    newPath = newPath.replace("\\","/");
                    newPath = newPath.section("/",-1);
                    newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
                }
		sqlquery.bindValue(":sPath",QVariant(newPath));//图片路径
    }*/

    QRectF rect = sceneBoundingRect();
    sqlquery.bindValue(":nStartX",QVariant((short)rect.left()));//left
    sqlquery.bindValue(":nStartY",QVariant((short)rect.top()));//top
    sqlquery.bindValue(":nWidth",QVariant((short)rect.width()));//width
    sqlquery.bindValue(":nHeight",QVariant((short)rect.height()));//height

    sqlquery.bindValue(":bIsStartStatement",QVariant(isUseScript));//是否使用宏指令

    sqlquery.bindValue(":nZvalue",QVariant(zValue()));//层次

    sqlquery.bindValue(":nCollidindId",QVariant(index));//碰撞ID

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
            //pwnd->information(QObject::tr("多功能开关宏被删掉"));
            pwnd->information(QObject::tr("多功能开关使用的宏") + macroName +QObject::tr("方法") + functionName + QObject::tr("被删掉"), MSG_WARNING);
            //QMessageBox::about(this, QObject::tr("警告"), QObject::tr("下拉框宏被删掉"));
        }
    }
    if(isUseScript && isExist)
    {
        count++;
        insertMacroTable(db,itemId,count,nSceneId);
        sqlquery.bindValue(":nStatementId",QVariant(count));//宏指令序号
    }
    else
        sqlquery.bindValue(":nScriptId",QVariant(0));//宏指令序号

    short monitorType = mPro.monitorType;
    sqlquery.bindValue(":eWatchType",QVariant(monitorType+1));//监视类型
    //插入多状态表
    //if(monitorType != NONE)
        InsertStatusTable(db,itemId,count);
    int monitorDataType = mPro.dataType;
    qDebug() << "monitorDataType: "<< monitorDataType;
    sqlquery.bindValue(":eWatchDataType",QVariant(monitorDataType+4));//监视数据类型
    short statusSount = mPro.count;
    sqlquery.bindValue(":nStatTotal",QVariant(statusSount));//监视的总状态数
    sqlquery.bindValue(":nAddrType",QVariant(mPro.bBitAddr));//监视的地址类型 是否为位地址
    sqlquery.bindValue(":nBitIndex",QVariant(mPro.bitIndex));//监视的字地址 位号
    sqlquery.bindValue(":nCondition",QVariant(mPro.valueType));//状态切换条件
    //插入监视地址表
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
        sqlquery.bindValue(":nWatchAddr",QVariant(count));//监视地址ID
    }

    bool result = false;
    result = sqlquery.exec();
    qDebug()<<"insert MFbtn table :" <<result;

    //InsertTextTable(db,itemId);

    foreach(SwitchInfo info,m_vecSwitchItem)
    {
        sqlquery.prepare("INSERT INTO comboboxFun"
                      "(nItemId,eFunctionType,sPath,nFunctionId,bSaveIndex ,sFunctionName)"
                      "VALUES(:nItemId,:eFunctionType,:sPath,:nFunctionId,:bSaveIndex ,:sFunctionName)");
        sqlquery.bindValue(":nItemId",QVariant(itemId));
        sqlquery.bindValue(":eFunctionType",QVariant(info.switchType));
        count++;
        sqlquery.bindValue(":nFunctionId",QVariant(count));
        InsertSwitchTable(db,info.switchType-1,count,info);

        sqlquery.bindValue(":bSaveIndex",QVariant(false));
        sqlquery.bindValue(":sFunctionName",QVariant(0));
        result = false;
        result = sqlquery.exec();
        qDebug() << "insert comboboxFun table :"<<result;
    }
}
MfBtnItem* MfBtnItem::Clone()//复制item
{
    QGraphicsItem* pCopy = NULL;
    QGraphicsItem* pItem = NULL;

    MfBtnItem *itemGroup = new MfBtnItem;

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
    itemGroup->SaveSecurityPro(&sPro);
    itemGroup->isUseScript      = isUseScript;
    itemGroup->macroName        = macroName;
    itemGroup->functionName     = functionName;
    itemGroup->m_vecSwitchItem  = m_vecSwitchItem;        //列表框的赋值

    //itemGroup->textPros    = textPros;          //文本属性
    //itemGroup->picPro      = picPro;            //外观属性
    itemGroup->statusText = statusText;
    itemGroup->statusPic = statusPic;
    itemGroup->statusIndex = statusIndex;
    itemGroup->curSta = curSta;

    itemGroup->backItem = backItem;
    itemGroup->backItem = itemGroup->GetPicItem();
    itemGroup->textItem = itemGroup->GetTextItem();

    itemGroup->SaveMonitorPage(mPro);
    itemGroup->setId(id());

    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }
    return itemGroup;
}


void MfBtnItem::save(QDataStream &stream)//将item存入数据流
{
    QVisableItem::save(stream);

    //脚本
    stream << isUseScript;
    stream << macroName;
    stream << functionName;

    if(pwnd->getProVersion() >= 3321)
    {
        //文本
        stream << statusIndex;
        int statusTextSize=statusText.size();
        stream << statusTextSize;
        for(int i=0;i<statusTextSize;i++)//第一层循环
        {
            int listSize = statusText[i].size();
            stream << listSize;
            for(int j=0;j<listSize;j++){//第二层循环
                stream << statusText[i][j].color;
                stream << statusText[i][j].sfont;
                stream << statusText[i][j].showProp;
                stream << statusText[i][j].size;
                stream << statusText[i][j].text;
            }
        }
        //图片
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

    //列表框
    SwitchInfo item;
    stream << m_vecSwitchItem.size();
    for(int i = 0; i < m_vecSwitchItem.size(); i++)
    {
        item = m_vecSwitchItem.at(i);

        stream << item.switchType;


        stream << item.addrBit;
        stream << (short)item.operTypeB;

        stream << item.addrWord;
        stream << (short)item.operTypeW;
        stream << (short)item.dataType;
        stream << item.value;

        stream << (short)item.operType;
        //stream << item.nSceneType;
        stream << item.sceneName;
        stream << item.bLogout;
        if(pwnd->getProVersion() >= 3163)//wxy
        {
            stream << item.bDynamicControl;
            if(item.bDynamicControl)
            {
                stream << item.addrConst;
            }
        }
        if(pwnd->getProVersion() >= 3240) //wxy
        {
            stream << item.bDown;
        }
    }

    if(pwnd->getProVersion() >= 3321)
    {
        //监视页面属性
        int nType = -1;
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
    }
}

void MfBtnItem::load(QDataStream &stream)//从数据流导出item
{
    QVisableItem::load(stream);

    //脚本属性
    stream >> isUseScript;
    stream >> macroName;
    stream >> functionName;

    if(pwnd->getProVersion() >= 3321)
    {
        //文本
        stream >> statusIndex;
        int statusTextSize=0;
        stream >> statusTextSize;
        statusText.resize(statusTextSize);
        for(int i=0;i<statusTextSize;i++)//第一层循环
        {
            int listSize=0;
            stream >> listSize;
            statusText[i].resize(listSize);
            for(int j=0;j<listSize;j++){//第二层循环
                stream >> statusText[i][j].color;
                stream >> statusText[i][j].sfont;
                stream >> statusText[i][j].showProp;
                stream >> statusText[i][j].size;
                stream >> statusText[i][j].text;
            }
        }
        //图片
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
    }
    else
    {
        statusIndex = 0;
        int statusTextSize=1; //wxy老版本只有一个状态
        statusText.resize(statusTextSize);
        for(int i=0;i<statusTextSize;i++)//第一层循环
        {
            int listSize=0;
            stream >> listSize;
            statusText[i].resize(listSize);
            for(int j=0;j<listSize;j++){//第二层循环
                stream >> statusText[i][j].color;
                stream >> statusText[i][j].sfont;
                stream >> statusText[i][j].showProp;
                stream >> statusText[i][j].size;
                stream >> statusText[i][j].text;
            }
        }
        //图片
        int pictureSize=1;
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
    }

    SwitchInfo item;
    short temp;
    int nSwitchNumber = 0;
    stream >> nSwitchNumber;
    //wxy 避免nSwitchNumber值读取错误，过大导致程序卡死
    for(int i = 0; i < qMin(nSwitchNumber,16); i++)
    {
        stream >> item.switchType;
        stream >> item.addrBit;
        stream >> temp;
        item.operTypeB = (BIT_OPER_TYPE)temp;

        stream >> item.addrWord;
        stream >> temp;
        item.operTypeW = (WORD_OPER_TYPE)temp;
        stream >> temp;
        item.dataType  = (DATA_TYPE)temp;
        stream >> item.value;

        stream >> temp;
        item.operType = (SCENE_OPER_TYPE)temp;
        //stream >> item.nSceneType;
        stream >> item.sceneName;
        stream >> item.bLogout;
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
        if(pwnd->getProVersion() >= 3240)//wxy
        {
            stream >> item.bDown;
        }
        else
        {
            item.bDown = false;//wxy 按下为1
        }
        m_vecSwitchItem.push_back(item);
    }
	backItem = GetPicItem();
	textItem = GetTextItem();
    if(pwnd->getProVersion() >= 3321)
    {
        //监视页面属性
        int nType = -1;
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
    }
    else
    {
        mPro.bSameAddr = false;
        mPro.count = 1;
        mPro.dataType = INT_16;
        mPro.monitorType = NONE;
        mPro.values.clear();
        mPro.valueType = -1;
        curSta = 0;
    }
}

QList<Keyboard> MfBtnItem::getAddress()
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

void MfBtnItem::setAddress(QList<Keyboard> addr)
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

QVector<ADDRPRO> MfBtnItem::getAllItemAddr()
{
    addrs.clear();
    ADDRPRO temp;

    int kk = m_vecSwitchItem.size();
    for(int i = 0; i < kk; i++)
    {
        if(1 == m_vecSwitchItem[i].switchType)
        {
            temp.pAddr = &m_vecSwitchItem[i].addrBit;
            temp.str   = QObject::tr("多功能按钮--位开关");
            temp.type  = 0;
            addrs << temp;
        }
        else if(2 == m_vecSwitchItem[i].switchType)
        {
            temp.pAddr = &m_vecSwitchItem[i].addrWord;
            temp.str   = QObject::tr("多功能按钮--字开关");
            temp.type  = 1;
            addrs << temp;
        }
    }

    QVector<ADDRPRO> AddrList;
    AddrList = QVisableItem::getAllItemAddr();
    for(int i = 0; i < AddrList.size(); i++)
    {
        temp.pAddr = AddrList.at(i).pAddr;
        temp.str   = QObject::tr("多功能按钮--权限地址");
        temp.type  = AddrList.at(i).type;
        addrs << temp;
    }
    return addrs;
}

void MfBtnItem::insertMacroTable(QSqlDatabase &db,int itemId,int &count,int sceneId)
{
    int macroId = count;

    QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO macro(MacroID , MacroLibName , MacroName , MacroType ,"
        "TimeInterval ,ControlAddr ,ControlAddrType ,ExecCondition , nCmpFactor , "
        "nCompID , SceneID,scriptCount )"
        "VALUES (:MacroID , :MacroLibName , :MacroName , :MacroType ,"
        ":TimeInterval ,:ControlAddr ,:ControlAddrType ,:ExecCondition , :nCmpFactor ,"
        ":nCompID , :SceneID,:scriptCount )");

    {
        sqlquery.bindValue(":MacroID",QVariant(macroId));// 宏的表 id
        sqlquery.bindValue(":MacroLibName",QVariant(macroName));//
        sqlquery.bindValue(":MacroName",QVariant("MACRO_MAIN"));//
        sqlquery.bindValue(":MacroType",QVariant(6));//
        sqlquery.bindValue(":nCompID",QVariant(itemId));// 控件表ID
        sqlquery.bindValue(":SceneID",QVariant(sceneId));//场景ID
        sqlquery.bindValue(":scriptCount",QVariant(1));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert  macro table:"<<result;
    }
}
void MfBtnItem::changeItemLanguageAttr(int lanNum)
{

}

QStringList MfBtnItem::getAllFonts()
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

//插入一个表,可能是位开关、字开关、功能开关、画面开关， id 为count
void MfBtnItem::InsertSwitchTable(QSqlDatabase &db,int type, int &count,SwitchInfo info)
{
    int itemId = count;
    QSqlQuery sqlquery(db);
    switch(type)
    {
        case BIT_SWITCH:     //位开关
            {
                sqlquery.prepare("INSERT INTO bitSwitch(nItemId,eOperType ,bDownZero,nBitAddress,nTimeout, bConfirm)"
                    "VALUES (:nItemId ,:eOperType, :bDownZero,:nBitAddress,:nTimeout,:bConfirm)");
                sqlquery.bindValue(":nItemId",QVariant(itemId));// 表 id
                short opertType = info.operTypeB;
                sqlquery.bindValue(":eOperType",QVariant(opertType));//位操作类型
                sqlquery.bindValue(":bDownZero",QVariant(info.bDown));// 是否按下为1
                count++;
                ADDR_PARAMENTS stParams;
                stParams.id = count;
                stParams.itemId = itemId;
                stParams.eType = OBJ_ITEM;
                stParams.addrNum = -1;
                stParams.eRWtype = SCENE_CONTROL_LOOP_R;
                if(opertType <3)
                {
                    stParams.eRWtype = SCENE_CONTROL_ONCE_W;
                }

                sqlquery.bindValue(":nBitAddress",QVariant(count));// 操作地址表 id
                info.addrBit.compile(db,stParams);//插入地址表
                //if (bitPro.bConfirm)
                {
                    //sqlquery.bindValue(":nTimeout",QVariant(bitPro.nTimeout));//最长等待时间
                }
                sqlquery.bindValue(":bConfirm",QVariant(false));//是否需要操作者确认
            }
            break;
        case WORD_SWITCH:    //字开关
            {
                sqlquery.prepare("INSERT INTO wordSwitch(nItemId,eOperType,nAddress,nDataType,"
                    "bCycle ,nMax ,nMin ,nFinalValue, bDynamicControl, nAddressConst)"
                    "VALUES (:nItemId,:eOperType,:nAddress,:nDataType,"
                    ":bCycle ,:nMax ,:nMin ,:nFinalValue, :bDynamicControl, :nAddressConst)");
                sqlquery.bindValue(":nItemId",QVariant(itemId));// 表 id
                short opertType = info.operTypeW;
                sqlquery.bindValue(":eOperType",QVariant(opertType));//字操作类型
                short dataType = info.dataType+1;
                sqlquery.bindValue(":nDataType",QVariant(dataType));// 数据类型
                count++;
                sqlquery.bindValue(":nAddress",QVariant(count));// 操作地址表 id
                ADDR_PARAMENTS stParams;
                stParams.id = count;
                stParams.itemId = itemId;
                stParams.eType = OBJ_ITEM;
                stParams.addrNum = -1;
                stParams.eRWtype = SCENE_CONTROL_LOOP_R;
                if(opertType == 1)
                {
                    stParams.eRWtype = SCENE_CONTROL_ONCE_W;
                }
                info.addrWord.compile(db,stParams);//插入地址表

                sqlquery.bindValue(":bCycle",QVariant(false));// 是否绕回
                double max,min;
                getRange(info.dataType,max,min);

                sqlquery.bindValue(":nMax",QVariant(max));// 上限
                sqlquery.bindValue(":nMin",QVariant(min));// 下限

                sqlquery.bindValue(":nFinalValue",QVariant(info.value));// 写入值

                //add by wxy
                sqlquery.bindValue(":bDynamicControl",QVariant(info.bDynamicControl));
                if(info.bDynamicControl)
                {
                   count++;
                   ADDR_PARAMENTS stParams;
                   stParams.id = count;
                   stParams.itemId = itemId;
                   stParams.eType = OBJ_ITEM;
                   stParams.addrNum = -1;
                   stParams.eRWtype = SCENE_CONTROL_ONCE_R;
                   info.addrConst.compile(db,stParams);//插入地址表
                }
                sqlquery.bindValue(":nAddressConst",QVariant(count));
            }
            break;
        case SCENE_SWITCH:    //画面开关
            {
                sqlquery.prepare("INSERT INTO screenSwitch(nItemId, eOperScene,nTargetPage ,bLogout ,nSceneType)"
                                 "VALUES (:nItemId, :eOperScene,:nTargetPage ,:bLogout,:nSceneType)");
                sqlquery.bindValue(":nItemId",QVariant(count));// 表 id
                short opertType = info.operType;
                sqlquery.bindValue(":eOperScene",QVariant(opertType));//操作类型
                sqlquery.bindValue(":bLogout",QVariant(info.bLogout));// 是否注销
                int sceneIndex = 0;
                int windowIndex = 0;

                for(int i = 0;i<pwnd->pSceneSheet.size();i++)
                {

                    if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 0)
                    {
                        if(pwnd->pSceneSheet[i]->sNewScreenName == info.sceneName)
                        {
                            sqlquery.bindValue(":nTargetPage",QVariant(sceneIndex));// 操作地址表 id

                            break;
                        }
                        sceneIndex++;
                    }
                    if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 1)
                    {
                        if(pwnd->pSceneSheet[i]->sNewScreenName == info.sceneName)
                        {
                            sqlquery.bindValue(":nTargetPage",QVariant(windowIndex));// 操作地址表 id

                            break;
                        }
                        windowIndex++;
                    }
                }

                int scenetype = 0;
                if(opertType > 2 && opertType < 5)
                {
                    scenetype = 1;
                }
                sqlquery.bindValue(":nSceneType",QVariant(scenetype));// 窗口

            }
            break;

    default:
            break;
    }
    bool result = false;
    result = sqlquery.exec();
    qDebug() << "insert switchXX table :"<<result;
}

//插入多语言表
//itemId为当前item(多功能按钮)的id，index为状态号
/*
void MfBtnItem::InsertTextTable(QSqlDatabase &db,int itemId)
{
	//如果语言数发生改变，要更新文本vector
	int langCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
	
	resizeLan(langCount);
	QSqlQuery sqlquery(db);
	sqlquery.prepare("INSERT INTO textProp(nItemId,nStatusIndex,nLangIndex,sFont,sText,nSize,nColor,nShowProp)"
		"VALUES (:nItemId ,:nStatusIndex ,:nLangIndex,:sFont,:sText,:nSize,:nColor,:nShowProp)");

	QVector<ST_TEXT_PROP > textProList = textPros;
	for(int i=0; i<langCount;i++)
	{
		sqlquery.bindValue(":nItemId",QVariant(itemId));// 控件表 id
		sqlquery.bindValue(":nStatusIndex",QVariant(0));// 状态号
		sqlquery.bindValue(":nLangIndex",QVariant(i));// 语言号
		sqlquery.bindValue(":sFont",QVariant(textProList[i].sfont));// 字体 font family
		sqlquery.bindValue(":sText",QVariant(textProList[i].text));// 文本
		sqlquery.bindValue(":nSize",QVariant(textProList[i].size));// 文本大小
		sqlquery.bindValue(":nColor",QVariant(ColorToInt(textProList[i].color)));// 文本颜色
		int nAligment = textProList[i].showProp >> 4;
		if(0 == nAligment)
		{
			nAligment = 0x0010;//居中
		}
		else if(1 == nAligment)
		{
			nAligment = 0x0020; //10 0000左
		}
		else if(2 == nAligment)
		{
			nAligment = 0x0040; //0100 0000 右
		}
		int nshowProp = (0x000F & textProList[i].showProp);
		nshowProp = (nshowProp | nAligment);
		sqlquery.bindValue(":nShowProp",QVariant(nshowProp));// 显示属性:粗体，斜体，下划线，闪烁
		bool result = false;
		result = sqlquery.exec();
		qDebug() << "insert textProp table :"<<result;
	}
}
void MfBtnItem::resizeLan(int count)
{
	ST_TEXT_PROP defaultText;
	defaultText.color = QColor(0,0,0);
	defaultText.showProp = false;
	defaultText.size = 10;
	defaultText.text = "";
	int textCount = count -textPros.size();
	if ( textCount>0)
	{
		for (int j=0; j<textCount; j++)
		{
			textPros << defaultText;
		}
	}
}
*/

void MfBtnItem::SetPicture(QString path,EITEM_TYPE blib,int alpha,QColor color)
{
	if (!textItem)
	{
		return;
	}
	if(!backItem)//背景图片指针为空，不操作直接返回
    {
		QRectF rect = textItem->sceneBoundingRect();

		QRectItem *rectItem = new QRectItem(rect);
		QPointF pos = rectItem->boundingRect().topLeft();

		rectItem->setPos(rect.topLeft()-pos);
		rectItem->setData(GROUP_NAME_KEY,QVariant(SWITCH_BACK_TYPE));
        rectItem->setFlag(QGraphicsItem::ItemIsMovable, false);
        rectItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
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
		QGroupItem *pBaseItem = new QGroupItem(pCopyItem);
                pBaseItem->SetWidth(this->boundingRect().width());
                pBaseItem->SetHeigth(this->boundingRect().height());
                QPointF pos = this->sceneBoundingRect().topLeft();
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
		//重新选择图片
	{
		QPixmap picture(path);

                QRectF rect = this->boundingRect();

		QPixmapItem *pixItem = new QPixmapItem(picture,QSize(rect.width(),rect.height()));

		QPointF pos = backItem->sceneBoundingRect().topLeft();
		QPointF pt = pixItem->boundingRect().topLeft();
		pixItem->setPos(pos-pt);

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
                QRectF rect = this->sceneBoundingRect();

		QRectItem *rectItem = new QRectItem(rect);
		QPointF pos = rectItem->boundingRect().topLeft();

		rectItem->setPos(rect.topLeft()-pos);
		rectItem->SetBackColor(color);
		rectItem->SetAlpha(alpha);
		rectItem->SetLineType(1);
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


		backItem = rectItem;
		addToGroup(backItem);
		addToGroup(textItem);
	}
}


QString  MfBtnItem::getItemName()
{
    return QObject::tr("多功能按钮");
}

void MfBtnItem::getRange(int dataType,double &nMax,double &nMin)
{
    nMax = 0;
    nMin = 0;
    int decLen = 0;
    switch(dataType)
    {
    case 1://16位整数
    case 5://16位BCD码
        {
            nMax = 32767;
            nMin = -32768;
             decLen = 0;
        }
        break;
    case 2://32位整数
    case 6://32位BCD码
        {
            nMax = 2147483647L;
            nMin = -2147483648L;
             decLen = 0;
        }
        break;
    case 3://16位正整数
        {
            nMax = 65535;
            nMin = 0;
             decLen = 0;
        }
        break;
    case 4://32位正整数
        {
            nMax = 4294967295UL;
            nMin = 0;
            decLen = 0;
        }
        break;
    case 7://32位浮点数
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

//void MfBtnItem::redrawForChangeStatus(int index, int lan)
//{
//    /*int totalState = this->getItemStates().size();
//    if(totalState <= index)
//    {
//        return;//目前没有这个状态
//    }*/

//    SetPicture(picPro.path,picPro.bLib,picPro.nAlpha,picPro.color);
//}

void MfBtnItem::SaveMonitorPage(monitorPro mProperty)
{
    mPro = mProperty;
}

//插入多状态表， id 为count itemId为控件表的id
void MfBtnItem::InsertStatusTable(QSqlDatabase &db,int itemId,int &count)
{
    QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO switchStatusProp(nItemId ,statusValue,nStatusIndex,eflick ,nAlpha,nColor,eLib ,sPath)"
        "VALUES (:nItemId ,:statusValue,:nStatusIndex,:eflick ,:nAlpha ,:nColor,:eLib ,:sPath)");

    for(int i =0; i< mPro.count;i++)
    {

        sqlquery.bindValue(":nItemId",QVariant(itemId));// 控件表 id

        if(mPro.monitorType == POLY && mPro.values.size()== mPro.count)//选择多态监视
            sqlquery.bindValue(":statusValue",QVariant(mPro.values[i]));// 状态切换值
        else
            sqlquery.bindValue(":statusValue",QVariant(i));// 状态切换值
        sqlquery.bindValue(":nStatusIndex",QVariant(i));// 状态切换值
        short flicktype = statusPic[i].eFlick;
        sqlquery.bindValue(":eflick",QVariant(flicktype+1));// 状态切换值
        sqlquery.bindValue(":eLib",QVariant(statusPic[i].bLib+1));//是否选择图库



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
            sqlquery.bindValue(":nAlpha",QVariant(statusPic[i].nAlpha));//alpha
            sqlquery.bindValue(":nColor",QVariant(ColorToInt(statusPic[i].color)));//背景色
            sqlquery.bindValue(":sPath",QVariant(newPath));//图片路径
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
            sqlquery.bindValue(":sPath",QVariant(newPath));//图片路径
        }


        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert switchStatusProp table :"<<result;
        InsertTextTable(db,itemId,i);
    }
}

//插入多语言表
//itemId为当前item(开关表)的id，index为状态号
void MfBtnItem::InsertTextTable(QSqlDatabase &db,int itemId,int index)
{
    //如果语言数发生改变，要更新文本vector
    int langCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    resizeStatus(mPro.count,langCount);
    QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO textProp(nItemId,nStatusIndex,nLangIndex,sFont,sText,nSize,nColor,nShowProp)"
                 "VALUES (:nItemId ,:nStatusIndex ,:nLangIndex,:sFont,:sText,:nSize,:nColor,:nShowProp)");

    QVector<ST_TEXT_PROP > textProList = statusText[index];
    for(int i=0; i<langCount;i++)
    {
        sqlquery.bindValue(":nItemId",QVariant(itemId));// 控件表 id
        sqlquery.bindValue(":nStatusIndex",QVariant(index));// 状态号
        sqlquery.bindValue(":nLangIndex",QVariant(i));// 语言号
        sqlquery.bindValue(":sFont",QVariant(textProList[i].sfont));// 字体 font family
        sqlquery.bindValue(":sText",QVariant(textProList[i].text));// 文本
        sqlquery.bindValue(":nSize",QVariant(textProList[i].size));// 文本大小
        sqlquery.bindValue(":nColor",QVariant(ColorToInt(textProList[i].color)));// 文本颜色
        int nAligment = textProList[i].showProp >> 4;
        if(0 == nAligment)
        {
            nAligment = 0x0010;//居中
        }
        else if(1 == nAligment)
        {
            nAligment = 0x0020; //10 0000左
        }
        else if(2 == nAligment)
        {
            nAligment = 0x0040; //0100 0000 右
        }
        int nshowProp = (0x000F & textProList[i].showProp);
        nshowProp = (nshowProp | nAligment);
        sqlquery.bindValue(":nShowProp",QVariant(nshowProp));// 显示属性:粗体，斜体，下划线，闪烁
        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert textProp table :"<<result;
    }
}

TEXTPRO MfBtnItem::getAllItemText()
{
    int iStaCount = mPro.count; //总状态数目
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
            vText.vMsg.append(QObject::tr("状态:")+QString("%1").arg(j));
            vText.vText.append(statusText[j][i].text);
        }
    }
    return vText;
}

void MfBtnItem::replaceAllItemText(int iLan, int iSta, QString sNewText)
{
    int iL = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //多语言总数
    int iStaCount = mPro.count; //总状态数目
    if( (iLan >= 0 && iLan < iL) && (iSta >= 0 && iSta < iStaCount))
    {
        statusText[iSta][iLan].text = sNewText;
    }
}

void MfBtnItem::redrawForChangeLanguage(int index)
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

void MfBtnItem::redrawForChangeStatus(int index, int lan)
{
    int totalState = this->getItemStates().size();
    if(totalState <= index)
    {
        return;//目前没有这个状态
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

QStringList MfBtnItem::getItemStates()
{
    QStringList ls;
    ls.clear();

    QString str;
    for(int i = 0; i < mPro.count; i++)
    {
        str = QObject::tr("状态") + QString("%1").arg(i);
        ls.append(str);
    }
    return ls;
}

void MfBtnItem::resizeStatus(int statuCount,int lanCount)
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

int MfBtnItem::getCurrentState()
{
    if(mPro.monitorType != NONE)
        return curSta;
    else
        return 0;
}
int MfBtnItem::checkMacroName(QString &msg)
{
    int result = -1;//脚本不存在
    msg = macroName;
    if(!isUseScript)//未使用脚本
    {
        return 1;
    }
    foreach(Macro mac,pwnd->macros)
    {
        if(mac.libName == macroName)
        {
            if(mac.isCompiled())//已经编译通过
            {
                result = 1;
            }
            else//未编译通过
            {
                result = 0;
            }
            break;
        }
    }
    return result;
}
