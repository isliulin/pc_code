#include "akcomboitem.h"
#include "Macro/macro.h"

extern MainWindow *pwnd;

void AkComboItem::compile(QSqlDatabase &db, int nSceneId, int &count, int index)
{
    count++;
    QVisableItem::compile(db, nSceneId, count, index);

    int base = count;//base不变

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

    int temp = count;

    QSqlQuery sqlquery(db);
    bool result = sqlquery.prepare("INSERT INTO dragdownBox(nItemId,"
                           "nSceneId,nStartX,nStartY,nWidth,nHeight,"
                           "nState,eNumberType,nBaseAddrID,bScriptSet,"
                           "nScriptId,sBackgroundImg,nBackgroundColor,"
                           "Alpha,nFirstLan,nCollidindId,nZvalue)"
                    "VALUES(:nItemId,:nSceneId,:nStartX,:nStartY,"
                           ":nWidth,:nHeight,:nState,:eNumberType,"
                           ":nBaseAddrID,:bScriptSet,:nScriptId,"
                           ":sBackgroundImg,:nBackgroundColor,:Alpha,"
                           ":nFirstLan,:nCollidindId,:nZvalue)");

    qDebug() << "sqlquery.prepare" << result;

    sqlquery.bindValue(":nItemId", QVariant(base));     //表id
    sqlquery.bindValue(":nSceneId", QVariant(nSceneId)); //scene id

    QRectF rect = sceneBoundingRect();//相对场景的坐标及高宽
    sqlquery.bindValue(":nStartX", QVariant((short)rect.left()));//left
    sqlquery.bindValue(":nStartY", QVariant((short)rect.top()));//top
    sqlquery.bindValue(":nWidth", QVariant((short)rect.width()));//width
    sqlquery.bindValue(":nHeight", QVariant((short)rect.height()));//height

    sqlquery.bindValue(":nState", QVariant(dataCombo.m_nStatuNum));
    sqlquery.bindValue(":eNumberType", QVariant((short)dataCombo.m_eDataType));
    temp++;
    sqlquery.bindValue(":nBaseAddrID", QVariant(temp));
    sqlquery.bindValue(":bScriptSet", QVariant(dataCombo.m_bUseMacro));

    bool isExist = false;
    if(dataCombo.m_bUseMacro)
    {
        foreach(Macro lib,pwnd->macros)
        {
            if(lib.libName == dataCombo.m_strMacroName)
            {
                isExist = true;
            }
        }

        if(!isExist)
        {
            pwnd->information(QObject::tr("下拉框使用的宏") + dataCombo.m_strMacroName + QObject::tr("被删掉"), MSG_WARNING);
        }
    }
    if(dataCombo.m_bUseMacro && isExist)
    {
        temp++;
        sqlquery.bindValue(":nScriptId", QVariant(temp));//
    }
    else
    {
        sqlquery.bindValue(":nScriptId", QVariant(-1));//
    }

    if(dataCombo.m_eLibType == NO_PIC)
    {
        sqlquery.bindValue(":sBackgroundImg", QVariant(""));
    }
    else if(dataCombo.m_eLibType == LIBRARY)
    {
        QString newPath = pwnd->SavePath(dataCombo.m_strPath,boundingRect().size(),true);
        if("" != newPath)
        {
            newPath = newPath.replace("\\","/");
            newPath = newPath.section("/",-1);
            newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
        }
        sqlquery.bindValue(":sBackgroundImg", QVariant(newPath));
    }
    else
    {
        QString newPath = pwnd->SavePath(dataCombo.m_strPath,boundingRect().size(),false);
        if("" != newPath)
        {
            newPath = newPath.replace("\\","/");
            newPath = newPath.section("/",-1);
            newPath = "/data/data/com.android.Samkoonhmi/pictures/"+newPath;
        }
        sqlquery.bindValue(":sBackgroundImg", QVariant(newPath));
    }

    int nColor = ColorToInt(dataCombo.m_nBKColor);
    sqlquery.bindValue(":nBackgroundColor", QVariant(nColor));
    sqlquery.bindValue(":Alpha", QVariant(dataCombo.m_nAlpha));
    sqlquery.bindValue(":nFirstLan", QVariant(dataCombo.m_bFirstLan));
    sqlquery.bindValue(":nCollidindId", QVariant(index));
    sqlquery.bindValue(":nZvalue", QVariant(zValue()));

    result = sqlquery.exec();
    qDebug() << "QDropdownAttr" << result << endl;

    count++;
    ADDR_PARAMENTS stParams;
    stParams.id = count;
    stParams.itemId = base;
    stParams.eType = OBJ_ITEM;
    stParams.eRWtype = SCENE_CONTROL_LOOP_R;
    stParams.addrNum = -1;
    if(dataCombo.m_eDataType == POSITIVE_INT_32 ||
       dataCombo.m_eDataType == INT_32 ||
       dataCombo.m_eDataType == BCD_32 ||
       dataCombo.m_eDataType == FLOAT_32)
    {
        dataCombo.m_keyCtrlAddr.Length = 2;
    }
    else
    {
        dataCombo.m_keyCtrlAddr.Length = 1;
    }
    //修改地址编译参数
    dataCombo.m_keyCtrlAddr.compile(db,stParams);

    if(dataCombo.m_bUseMacro && isExist)
    {
        count++;
        sqlquery.prepare("INSERT INTO macro(MacroID,MacroLibName,MacroName,MacroType,"
                "TimeInterval,ControlAddr,ControlAddrType,ExecCondition,nCmpFactor,"
                "nCompID,SceneID,scriptCount)"
         "VALUES(:MacroID,:MacroLibName,:MacroName,:MacroType,"
                ":TimeInterval,:ControlAddr,:ControlAddrType,:ExecCondition,:nCmpFactor,"
                ":nCompID,:SceneID,:scriptCount)");

        sqlquery.bindValue(":MacroID",QVariant(count));// 宏的表 id
        sqlquery.bindValue(":MacroLibName",QVariant(dataCombo.m_strMacroName));//
        sqlquery.bindValue(":MacroName",QVariant("MACRO_MAIN"));//
        sqlquery.bindValue(":MacroType",QVariant(6));//
        sqlquery.bindValue(":nCompID",QVariant(base));// 控件表ID
        sqlquery.bindValue(":SceneID",QVariant(nSceneId));//场景ID
        sqlquery.bindValue(":scriptCount",QVariant(1));//场景ID

        result = false;
        result = sqlquery.exec();
        qDebug() << "insert textProp macro :" << result;
    }

    //QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO switchStatusProp(nItemId ,statusValue,nStatusIndex,eflick,nAlpha,nColor,eLib,sPath)"
                "VALUES (:nItemId,:statusValue,:nStatusIndex,:eflick,:nAlpha,:nColor,:eLib,:sPath)");

    for(int i = 0; i < dataCombo.m_nStatuNum; i++)
    {

        sqlquery.bindValue(":nItemId",QVariant(base));// 控件表 id
        sqlquery.bindValue(":statusValue",QVariant(dataCombo.m_vecStatus[i].m_value));//每个状态值
        sqlquery.bindValue(":nStatusIndex",QVariant(i));//状态序号
        sqlquery.bindValue(":eflick",QVariant(0));// 状态切换值
        sqlquery.bindValue(":eLib",QVariant(0));//是否选择图库
        sqlquery.bindValue(":nAlpha",QVariant(0));//alpha
        sqlquery.bindValue(":nColor",QVariant(0));//背景色
        sqlquery.bindValue(":sPath",QVariant(""));//图片路径

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert switchStatusProp table :"<<result;

        //InsertTextTable(db,itemId,i);
        {
            //如果语言数发生改变，要更新文本vector
            int langCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
            //resizeStatus(mPro.count,langCount);
            QSqlQuery sqlquery(db);
            sqlquery.prepare("INSERT INTO textProp(nItemId,nStatusIndex,nLangIndex,sFont,sText,nSize,nColor,nShowProp)"
                     "VALUES(:nItemId,:nStatusIndex,:nLangIndex,:sFont,:sText,:nSize,:nColor,:nShowProp)");

            //QVector<ComboLanguage> textProList = dataCombo.m_vecStatus[i].m_vecText;
            for(int j = 0; j < langCount; j++)
            {
                sqlquery.bindValue(":nItemId",QVariant(base));// 控件表 id
                sqlquery.bindValue(":nStatusIndex",QVariant(i));// 状态号
                sqlquery.bindValue(":nLangIndex",QVariant(j));// 语言号
                sqlquery.bindValue(":sFont",QVariant(dataCombo.m_vecLanguage[j].m_strFontName));// 字体 font family
                sqlquery.bindValue(":sText",QVariant(dataCombo.m_vecStatus[i].m_vecText[j]));// 文本
                sqlquery.bindValue(":nSize",QVariant(dataCombo.m_vecLanguage[j].m_nFontSize));// 文本大小
                sqlquery.bindValue(":nColor",QVariant(ColorToInt(dataCombo.m_vecLanguage[j].m_nTextColor)));// 文本颜色
                int nAligment = 0;
                if(0 == dataCombo.m_vecLanguage[j].m_nAlign)
                {
                    nAligment = 0x0010;//居中
                }
                else if(1 == dataCombo.m_vecLanguage[j].m_nAlign)
                {
                    nAligment = 0x0020; //10 0000左
                }
                else if(2 == dataCombo.m_vecLanguage[j].m_nAlign)
                {
                    nAligment = 0x0040; //0100 0000 右
                }

                if(dataCombo.m_vecLanguage[j].m_bCuTi)
                {
                    nAligment += 0x0001;
                }

                if(dataCombo.m_vecLanguage[j].m_bXieTi)
                {
                    nAligment += 0x0002;
                }

                if(dataCombo.m_vecLanguage[j].m_bXiaHuaXian)
                {
                    nAligment += 0x0008;
                }
                sqlquery.bindValue(":nShowProp",QVariant(nAligment));// 显示属性:粗体，斜体，下划线，闪烁
                bool result = false;
                result = sqlquery.exec();
                qDebug() << "insert textProp table :"<<result;
            }
        }
    }
}

void AkComboItem::save(QDataStream &stream)//将item存入数据流
{
    QVisableItem::save(stream);

    int type = 0;
    stream << dataCombo.m_nStatuNum;
    type = (int)dataCombo.m_eDataType;
    stream << type;
    stream << dataCombo.m_keyCtrlAddr;
    stream << dataCombo.m_nAlpha;
    stream << dataCombo.m_nBKColor;
    type = (int)dataCombo.m_eLibType;
    stream << type;
    stream << dataCombo.m_strPath;
    stream << dataCombo.m_bUseMacro;
    stream << dataCombo.m_strMacroName;
    stream << dataCombo.m_bFirstLan;

    int num = dataCombo.m_vecLanguage.size();
    stream << num;
    for(int i = 0; i < num; i++)
    {
        stream << dataCombo.m_vecLanguage[i].m_bCuTi;
        stream << dataCombo.m_vecLanguage[i].m_bXiaHuaXian;
        stream << dataCombo.m_vecLanguage[i].m_bXieTi;
        stream << dataCombo.m_vecLanguage[i].m_nAlign;
        stream << dataCombo.m_vecLanguage[i].m_nFontSize;
        stream << dataCombo.m_vecLanguage[i].m_nTextColor;
        stream << dataCombo.m_vecLanguage[i].m_strFontName;
    }

    int stateNum  = dataCombo.m_vecStatus.size();
    stream << stateNum;
    for(int i = 0; i < stateNum; i++)
    {
        stream << dataCombo.m_vecStatus[i].m_value;
        stream << dataCombo.m_vecStatus[i].m_vecText;
    }
}

void AkComboItem::load(QDataStream &stream)//从数据流导出item
{
    QVisableItem::load(stream);

    int type = 0;

    stream >> dataCombo.m_nStatuNum;
    stream >> type;
    dataCombo.m_eDataType = (DATA_TYPE)type;
    stream >> dataCombo.m_keyCtrlAddr;
    stream >> dataCombo.m_nAlpha;
    stream >> dataCombo.m_nBKColor;
    stream >> type;
    dataCombo.m_eLibType = (EITEM_TYPE)type;
    stream >> dataCombo.m_strPath;
    stream >> dataCombo.m_bUseMacro;
    stream >> dataCombo.m_strMacroName;
    stream >> dataCombo.m_bFirstLan;

    int num = 0;
    stream >> num;
    dataCombo.m_vecLanguage.resize(num);
    for(int i = 0; i < num; i++)
    {
        stream >> dataCombo.m_vecLanguage[i].m_bCuTi;
        stream >> dataCombo.m_vecLanguage[i].m_bXiaHuaXian;
        stream >> dataCombo.m_vecLanguage[i].m_bXieTi;
        stream >> dataCombo.m_vecLanguage[i].m_nAlign;
        stream >> dataCombo.m_vecLanguage[i].m_nFontSize;
        stream >> dataCombo.m_vecLanguage[i].m_nTextColor;
        stream >> dataCombo.m_vecLanguage[i].m_strFontName;
    }

    int stateNum  = 0;
    stream >> stateNum;
    dataCombo.m_vecStatus.resize(stateNum);
    for(int i = 0; i < stateNum; i++)
    {
        stream >> dataCombo.m_vecStatus[i].m_value;
        stream >> dataCombo.m_vecStatus[i].m_vecText;
    }
}

AkComboItem::AkComboItem(QGraphicsItem *parent):QVisableItem(parent)
{

}

QString  AkComboItem::getItemName()
{
    return QObject::tr("下拉框");
}

AkComboItem::~AkComboItem()
{

}

int AkComboItem::GroupType()//控件类型
{
    return SAM_DRAW_GROUP_COMBOBOX;
}

AkComboItem* AkComboItem::Clone()//复制item
{
    QGraphicsItem* pCopy = NULL;
    QGraphicsItem* pItem = NULL;

    AkComboItem *itemGroup = new AkComboItem;

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

    itemGroup->dataCombo.m_nStatuNum      = dataCombo.m_nStatuNum;
    itemGroup->dataCombo.m_eDataType      = dataCombo.m_eDataType;
    itemGroup->dataCombo.m_keyCtrlAddr    = dataCombo.m_keyCtrlAddr;
    itemGroup->dataCombo.m_nAlpha         = dataCombo.m_nAlpha;
    itemGroup->dataCombo.m_nBKColor       = dataCombo.m_nBKColor;
    itemGroup->dataCombo.m_eLibType       = dataCombo.m_eLibType;
    itemGroup->dataCombo.m_strPath        = dataCombo.m_strPath;
    itemGroup->dataCombo.m_bUseMacro      = dataCombo.m_bUseMacro;
    itemGroup->dataCombo.m_strMacroName   = dataCombo.m_strMacroName;
    itemGroup->dataCombo.m_bFirstLan      = dataCombo.m_bFirstLan;
    itemGroup->dataCombo.m_vecStatus      = dataCombo.m_vecStatus;
    itemGroup->dataCombo.m_vecLanguage    = dataCombo.m_vecLanguage;
    itemGroup->setId(id());

    return itemGroup;
}

void AkComboItem::changeItemLanguageAttr(int lanNum)
{
    int attrNum = dataCombo.m_vecLanguage.size();

    if(lanNum > attrNum)//增加语言
    {
        ComboLanguage Sub;
        if(dataCombo.m_bFirstLan)
        {
            Sub = dataCombo.m_vecLanguage.at(0);
        }
        else
        {
            Sub.m_nAlign        = 0;
            Sub.m_nFontSize     = 10;
            Sub.m_nTextColor    = QColor(0,0,0);
            Sub.m_strFontName   = QObject::tr("Droid Sans Fallback");
            Sub.m_bXieTi        = false;
            Sub.m_bCuTi         = false;
            Sub.m_bXiaHuaXian   = false;
        }

        int num = lanNum - attrNum;
        for(int i = 0; i < num; i++)
        {
            dataCombo.m_vecLanguage.push_back(Sub);
        }

        int temp = dataCombo.m_vecStatus.size();
        for(int j = 0; j < temp; j++)
        {
            int k = dataCombo.m_vecStatus[j].m_vecText.size();
            if(attrNum != k)
            {
                //出错
            }

            for(int i = attrNum; i < lanNum; i++)
            {
                QString  str = "state_" + QString::number(j);
                dataCombo.m_vecStatus[j].m_vecText.push_back(str);
            }
        }
    }
    else if(lanNum < attrNum)//减少语言
    {
        for(int i = attrNum - 1; i >= lanNum; i--)
        {
            dataCombo.m_vecLanguage.remove(i);
        }

        int temp = dataCombo.m_vecStatus.size();
        for(int j = 0; j < temp; j++)
        {
            int k = dataCombo.m_vecStatus[j].m_vecText.size();
            if(attrNum != k)
            {
                //出错
            }

            for(int i = attrNum - 1; i >= lanNum; i--)
            {
                dataCombo.m_vecStatus[j].m_vecText.remove(i);
            }
        }
    }
}

QStringList AkComboItem::getAllFonts()
{
    QStringList ls;
    ls.clear();

    int temp = dataCombo.m_vecLanguage.size();
    for(int i = 0; i < temp; i++)
    {
        ls << dataCombo.m_vecLanguage[i].m_strFontName;
    }

    return ls;
}

QVector<ADDRPRO> AkComboItem::getAllItemAddr()
{
    addrs.clear();
    ADDRPRO temp;

    temp.pAddr = &dataCombo.m_keyCtrlAddr;
    temp.str   = QObject::tr("下拉框--监视地址");
    temp.type  = 1;
    addrs << temp;

    QVector<ADDRPRO> AddrList;
    AddrList = QVisableItem::getAllItemAddr();
    for(int i = 0; i < AddrList.size(); i++)
    {
        temp.pAddr = AddrList.at(i).pAddr;
        temp.str   = QObject::tr("下拉框--权限地址");
        temp.type  = AddrList.at(i).type;
        addrs << temp;
    }

    return addrs;
}

QStringList AkComboItem::getItemStates()
{
    QStringList ls;
    ls.clear();

    QString str;
    for(int i = 0; i < dataCombo.m_nStatuNum; i++)
    {
        str = QObject::tr("状态") + QString("%1").arg(i);
        ls.append(str);
    }

    return ls;
}

QList<Keyboard> AkComboItem::getAddress()
{
    QList<Keyboard> addrs;

    addrs << dataCombo.m_keyCtrlAddr;

    return addrs;
}

void AkComboItem::setAddress(QList<Keyboard> addr)
{
    if (addr.size() <0)
    {
        return;
    }

    dataCombo.m_keyCtrlAddr = addr.at(0);
}

TEXTPRO AkComboItem::getAllItemText()
{
    int iStaCount = dataCombo.m_nStatuNum; //总状态数目
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
            vText.vText.append(dataCombo.m_vecStatus[j].m_vecText.at(i));
        }
    }
    return vText;
}

void AkComboItem::replaceAllItemText(int iLan, int iSta, QString sNewText)
{
    int iL = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //多语言总数
    int iStaCount = dataCombo.m_nStatuNum; //总状态数目
    if( (iLan >= 0 && iLan < iL) && (iSta >= 0 && iSta < iStaCount))
    {
        dataCombo.m_vecStatus[iSta].m_vecText[iLan] = sNewText;
    }
}

void AkComboItem::redrawForChangeLanguage(int index)
{
    //画标题文本
    /*QStringList sDataName;
    sDataName.clear();
    int iLan = index;//pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan;

    if(this->m_bShowId)
    {
        QString sNum  = m_vecMessage[iLan].m_sNumber;
        sDataName.append(sNum);
    }
    if(m_bShowTime)
    {
        QString sTime = m_vecMessage[iLan].m_sTimeName;   //以语言1显示时间内容
        sDataName.append(sTime);
    }
    if(m_bShowDate)
    {
        QString sDate = m_vecMessage[iLan].m_sDateName;   //以语言1显示日期内容
        sDataName.append(sDate);
    }

    sDataName.append(m_vecMessage[iLan].m_sMessageName);
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
            case SAM_DRAW_OBJECT_TEXT://一个一个的取出文本
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
    }*/
}

void AkComboItem::redrawForChangeStatus(int index, int lan)
{
    QString sPath = "";
    sPath = dataCombo.m_strPath;

    foreach(QGraphicsItem *pItem,this->childItems())
    {
        if(SAM_DRAW_OBJECT_PIXMAP == pItem->type())
        {
            //int zValue = pItem->zValue();
            QRectF rect = pItem->sceneBoundingRect();
            QPixmap picture = QPixmap(sPath);
            if(!picture)
            {
                return ;
            }
            QPixmapItem *PicItem = new QPixmapItem(picture,rect.size().toSize());
            PicItem->setPos(rect.topLeft());

            PicItem->setZValue(0);
            PicItem->setFlag(QGraphicsItem::ItemIsSelectable,false);
            this->addToGroup(PicItem);

            QGraphicsItem *pTopItem = this->topLevelItem();
            QItemGroup *pArentItem = dynamic_cast<QItemGroup *> (pTopItem);
            if(pArentItem)
            {
                pArentItem->removeFromGroup(pItem);
                //wxy修改数值显示控件在工程切换状态时会留下重影
                if(pItem)
                {
                    pItem->hide();
                    delete pItem;
                    pItem = NULL;
                }
            }
        }
        //else if(SAM_DRAW_OBJECT_TEXT == pItem->type())
        //{
        //    pItem->setZValue(1);
        //}
    }
}
int AkComboItem::checkMacroName(QString &msg)
{
    int result = -1;//脚本不存在
    msg = dataCombo.m_strMacroName;
    if(!dataCombo.m_bUseMacro)//未使用脚本
    {
        return 1;
    }
    foreach(Macro mac,pwnd->macros)
    {
        if(mac.libName == dataCombo.m_strMacroName)
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
