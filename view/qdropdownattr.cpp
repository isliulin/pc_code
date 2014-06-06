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
    //rect.setSize(QSize(108,18));//绘制外框矩形
    pRect = new QRectItem(rect);//
    pRect->SetLineColor(QColor(127,157,185));
    //pRect->SetPattern(1);
    pRect->SetBackColor(m_nBackColor);
    pRect->SetName("mFramRect");
    //pRect->setZValue(1);
    addToGroup(pRect);
    pRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    rect.setTopLeft(QPointF(84,0));               //绘制背景矩形框
    rect.setSize(QSize(24,18));
    pBackRect = new QRectItem(rect);
    pBackRect->SetBackColor(QColor(183,211,252));
    pBackRect->SetLineType(0);
    pBackRect->SetName("mBackRect");
    pBackRect->setZValue(2);
    addToGroup(pBackRect);
    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    QPainterPath mPenPath = QPainterPath();
    mPenPath.moveTo(QPointF(90,7));//第一点
    mPenPath.lineTo(QPointF(96,11));
    mPenPath.lineTo(QPointF(102,7));
    pLine = new QFoldLineItem(mPenPath);
    pLine->setLineType(1);
    pLine->setLineWidth(2); //设置线条宽度
    pLine->setLineColor(QColor(77,97,133)); //线条颜色
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
    return QObject::tr("功能选择按钮");
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
    mPath1.moveTo(0,0);         //画直线的起点
    mPath1.lineTo(108,0);         //画直线的终点
    pLineTemp = new QLineItem(mPath1);        //画细直线
    pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
    //pLineTemp->setAlpha(alpha);
    addToGroup(pLineTemp);                   //添加到组
    pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);

    QPainterPath mPath2;
    mPath2.moveTo(0,0);         //画直线的起点
    mPath2.lineTo(0,18);         //画直线的终点
    pLineTemp = new QLineItem(mPath2);        //画细直线
    pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
    //pLineTemp->setAlpha(alpha);
    addToGroup(pLineTemp);                   //添加到组
    pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);

    QPainterPath mPath3;
    mPath3.moveTo(108,0);         //画直线的起点
    mPath3.lineTo(108,18);         //画直线的终点
    pLineTemp = new QLineItem(mPath3);        //画细直线
    pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
    //pLineTemp->setAlpha(alpha);
    addToGroup(pLineTemp);                   //添加到组
    pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);

    QPainterPath mPath4;
    mPath4.moveTo(0,18);         //画直线的起点
    mPath4.lineTo(108,18);         //画直线的终点
    pLineTemp = new QLineItem(mPath4);        //画细直线
    pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
    //pLineTemp->setAlpha(alpha);
    addToGroup(pLineTemp);                   //添加到组
    pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);

    QRectF rect = QRectF(0,0,108,18);
    //rect.setSize(QSize(108,18));//绘制外框矩形
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
    //rect.setSize(QSize(108,18));//绘制外框矩形
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

    rect.setTopLeft(QPointF(84,0));               //绘制背景矩形框
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
    mPenPath.moveTo(QPointF(90,7));//第一点
    mPenPath.lineTo(QPointF(96,11));
    mPenPath.lineTo(QPointF(102,7));
    pLine = new QFoldLineItem(mPenPath);
    pLine->setLineType(1);
    pLine->setLineWidth(2); //设置线条宽度
    pLine->setLineColor(QColor(77,97,133)); //线条颜色
    pLine->SetName("mLine");
    pLine->setZValue(4);
    //pLine->setAlpha(alpha);
    addToGroup(pLine);
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
}

int QDropdownAttr::GroupType()//控件类型 位开关 字开关
{
    return SAM_DRAW_GROUP_DROPDOWN;
}

QDropdownAttr* QDropdownAttr::Clone()//复制item
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

    itemGroup->m_nShowNumber    = m_nShowNumber;          //下拉显示数量
    itemGroup->totalScreen      = totalScreen;            //
    itemGroup->isUseScript      = isUseScript;
    itemGroup->macroName        = macroName;
    itemGroup->functionName     = functionName;
    itemGroup->m_vecSwitchItem  = m_vecSwitchItem;        //列表框的赋值

    itemGroup->m_strFontName    = m_strFontName;          //字体类型的名字
    itemGroup->m_nFontSize      = m_nFontSize;            //字体大小
    itemGroup->m_nLanType       = m_nLanType;             //语言种类
    itemGroup->m_nFontStyle     = m_nFontStyle;           //文字样式（标准，粗体，斜体）
    itemGroup->m_nFontColor     = m_nFontColor;           //字体颜色
    itemGroup->m_nBackColor     = m_nBackColor;
    itemGroup->m_nAlpha         = m_nAlpha;
    itemGroup->m_bUsePic        = m_bUsePic;
    itemGroup->setId(id());

    return itemGroup;
}

void QDropdownAttr::compile(QSqlDatabase &db, int nSceneId, int &count,int index)//编译的时候保存item到数据库
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

    //int baseId = count;

    QSqlQuery sqlquery(db);
    /////////////////////////////////下拉框Id////////////////////////////////////////////
    bool r = sqlquery.prepare("INSERT INTO combobox(nItemId,nSceneId,nStartX,nStartY,nWidth,nHeight,"
                              "nShowNumber,sFontType,nfontSize,nLanguageTypeId,nFontColor,"
                              "eFontCss,nBackColor,nTouchPropId,nShowPropId,nZvalue,nCollidindId,bUsePic ,bIsStartStatement,nScriptId,nAlpha)"
                       "VALUES(:nItemId,:nSceneId,:nStartX,:nStartY,:nWidth,:nHeight,"
                              ":nShowNumber,:sFontType,:nfontSize,:nLanguageTypeId,:nFontColor,"
                              ":eFontCss,:nBackColor,:nTouchPropId,:nShowPropId,:nZvalue,:nCollidindId,:bUsePic ,:bIsStartStatement,:nScriptId,:nAlpha)");

    qDebug() << "sqlquery.prepare" << r;

    sqlquery.bindValue(":nItemId", QVariant(itemId));                //表id
    sqlquery.bindValue(":nSceneId", QVariant(nSceneId));            //scene id

    QRectF rect = sceneBoundingRect();//相对场景的坐标及高宽
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
            //pwnd->information(QObject::tr("下拉框宏被删掉"));
            pwnd->information(QObject::tr("下拉框使用的宏") + macroName +QObject::tr("方法") + functionName + QObject::tr("被删掉"), MSG_WARNING);
            //QMessageBox::about(this, QObject::tr("警告"), QObject::tr("下拉框宏被删掉"));
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

        sqlquery.bindValue(":MacroID",QVariant(count));// 宏的表 id
        sqlquery.bindValue(":MacroLibName",QVariant(macroName));//
        sqlquery.bindValue(":MacroName",QVariant("MACRO_MAIN"));//
        sqlquery.bindValue(":MacroType",QVariant(6));//
        sqlquery.bindValue(":nCompID",QVariant(itemId));// 控件表ID
        sqlquery.bindValue(":SceneID",QVariant(nSceneId));//场景ID
        sqlquery.bindValue(":scriptCount",QVariant(1));//场景ID

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
    /////////////////////////////////每个功能的functionId////////////////////////////////////////////
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
                sqlquery.bindValue(":sPath",QVariant(newPath));//图片路径
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

    /////////////////////////////////位开关Id////////////////////////////////////////////
    t = sqlquery.prepare("INSERT INTO bitSwitch"
                         "(nItemId,eOperType,bDownZero,nBitAddress)"
                  "VALUES(:nItemId,:eOperType,:bDownZero,:nBitAddress)");
    qDebug() << "bitSwitch" << t << endl;

    curBit = 0;
    for(int i = 0; i < kk; i++)
    {
        if(1 == m_vecSwitchItem[i].switchType)
        {
            count++;//插入一次
            curBit++;
            sqlquery.bindValue(":nItemId", QVariant(baseId + curBit));
            sqlquery.bindValue(":eOperType", QVariant((int)m_vecSwitchItem[i].operTypeB));
            sqlquery.bindValue(":bDownZero", QVariant(false));
            sqlquery.bindValue(":nBitAddress", QVariant(baseId + kk + curBit));

            result = sqlquery.exec();
            qDebug() << "-----QDropdownAttr-switchType------" << result << endl;

            /////////////////位开关 地址Id//////////////////
            count++;//地址一次
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

    /////////////////////////////////字开关Id////////////////////////////////////////////
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
            sqlquery.bindValue(":nMax",QVariant(max));// 上限
            sqlquery.bindValue(":nMin",QVariant(min));// 下限

            sqlquery.bindValue(":nFinalValue", QVariant(m_vecSwitchItem[i].value));

            qDebug() << "=========QDropdownAttr-switchType=========" << result << endl;

            /////////////////字开关 地址Id//////////////////
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
               m_vecSwitchItem[i].addrConst.compile(db,stParamsConst);//插入地址表
            }
            sqlquery.bindValue(":nAddressConst",QVariant(baseId + numBit + kk + curWord + icurConstAddr));
            result = sqlquery.exec();
            //qDebug() << "=========QDropdownAttr-switchType=========" << result << endl;
        }
    }

    /////////////////////////////////画面切换Id////////////////////////////////////////////
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
                        sqlquery.bindValue(":nTargetPage",QVariant(sceneIndex));// 操作地址表 id
                        break;
                    }
                    sceneIndex++;
                }
                if(pwnd->pSceneSheet[j]->nIsSceneOrWindow == 1)
                {
                    if(pwnd->pSceneSheet[j]->sNewScreenName == m_vecSwitchItem[i].sceneName)
                    {
                        sqlquery.bindValue(":nTargetPage",QVariant(windowIndex));// 操作地址表 id
                        break;
                    }
                    windowIndex++;
                }

            }
            /*if(m_vecSwitchItem[i].nSceneType < totalScreen)//存的是画面
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
            else//存的是窗口
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
            sqlquery.bindValue(":nSceneType",QVariant(scenetype));// 窗口

            result = sqlquery.exec();
            qDebug() << "QDropdownAttr-screenSwitch" << result << endl;
        }
    }

    ////////////////////////多语言表////////////////////////////////////
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
                sqlquery.bindValue(":sText", QVariant(QObject::tr("功能1")));
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

        sqlquery.bindValue(":MacroID",QVariant(count));// 宏的表 id
        sqlquery.bindValue(":MacroLibName",QVariant(macroName));//
        sqlquery.bindValue(":MacroName",QVariant(functionName));//
        sqlquery.bindValue(":MacroType",QVariant(6));//
        sqlquery.bindValue(":nCompID",QVariant(baseId));// 控件表ID
        sqlquery.bindValue(":SceneID",QVariant(nSceneId));//场景ID

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

void QDropdownAttr::save(QDataStream &stream)//将item存入数据流
{
    QVisableItem::save(stream);

    stream << m_nShowNumber;
    stream << totalScreen;
    stream << isUseScript;
    stream << macroName;
    stream << functionName;

    stream << m_strFontName;          //字体类型的名字
    stream << m_nFontSize;            //字体大小
    stream << m_nLanType;             //语言种类
    stream << m_nFontStyle;           //文字样式（标准，粗体，斜体）
    stream << m_nFontColor;           //字体颜色
    stream << m_nBackColor;           //背景颜色
    stream << m_nAlpha;

    stream << m_bUsePic;
    //列表框
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

void QDropdownAttr::load(QDataStream &stream)//从数据流导出item
{
    QVisableItem::load(stream);

    stream >> m_nShowNumber;
    stream >> totalScreen;
    stream >> isUseScript;
    stream >> macroName;
    stream >> functionName;

    stream >> m_strFontName;          //字体类型的名字
    stream >> m_nFontSize;            //字体大小
    stream >> m_nLanType;             //语言种类
    stream >> m_nFontStyle;           //文字样式（标准，粗体，斜体）
    stream >> m_nFontColor;           //字体颜色
    stream >> m_nBackColor;           //背景颜色
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
            temp.str   = QObject::tr("下拉框--位开关");
            temp.type  = 0;
            addrs << temp;
        }
        else if(2 == m_vecSwitchItem[i].switchType)
        {
            temp.pAddr = &m_vecSwitchItem[i].addrWord;
            temp.str   = QObject::tr("下拉框--字开关");
            temp.type  = 1;
            addrs << temp;
        }
    }

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

void QDropdownAttr::changeItemLanguageAttr(int lanNum)
{
    int itemLanNum  = m_vecSwitchItem[0].vecSwitchFunName.size();
    int number      = m_vecSwitchItem.size();

    if(lanNum > itemLanNum)//需要增加语言数
    {
        for(int i = 0; i < number; i++)
        {
            QString str =  QObject::tr("功能1");
            for(int j = itemLanNum; j < lanNum; j++)
            {
                m_vecSwitchItem[i].vecSwitchFunName.push_back(str);
            }
        }
    }
    else if(lanNum < itemLanNum)//需要删除语言
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

TEXTPRO QDropdownAttr::getAllItemText()
{
    //m_vecSwitchItem[i].vecSwitchFunName
    int iStaCount = m_nShowNumber; //总状态数目
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
            vText.vMsg.append(QObject::tr("下拉列表:")+QString("%1").arg(j));
            vText.vText.append(m_vecSwitchItem[j].vecSwitchFunName[i]);
        }
    }
    return vText;
}

void QDropdownAttr::replaceAllItemText(int iLan, int iSta, QString sNewText)
{
    int iL = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nLanNum; //多语言总数
    int iStaCount = m_nShowNumber; //总状态数目
    if( (iLan >= 0 && iLan < iL) && (iSta >= 0 && iSta < iStaCount))
    {
        m_vecSwitchItem[iSta].vecSwitchFunName[iLan] = sNewText;
    }
}
