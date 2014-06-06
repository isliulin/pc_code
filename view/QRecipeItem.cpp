#include "QRecipeItem.h"
#include "Frame/mainwindow.h"
#include "Macro/macro.h"

extern MainWindow *pwnd;

QRcipeItem::QRcipeItem():QVisableItem(0)
{

}

void QRcipeItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    count++;
    QVisableItem::compile(db,nSceneId,count, index);
    int nItemId = count;

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

    QRectF pos = this->sceneBoundingRect();
    bool bResult = sqlquery.prepare("INSERT INTO recipeSelect(nItemId,nSceneId,nStartPosX,nStartPosY,nWidth,"
                     "nHeight,eShowType,sShowRecipeId,sFontFamily,nFontSize,"
                     "nTextColor,nBackColor,nCurrShowRow,bUseMacro,nMacroId,"
                     "nTouchPropId,nShowPropId,nTransparent,nZvalue,nCollidindId)"
                     "VALUES (:nItemId,:nSceneId,:nStartPosX,:nStartPosY,:nWidth,"
                     ":nHeight,:eShowType,:sShowRecipeId,:sFontFamily,:nFontSize,"
                     ":nTextColor,:nBackColor,:nCurrShowRow,:bUseMacro,:nMacroId,"
                     ":nTouchPropId,:nShowPropId,:nTransparent,:nZvalue,:nCollidindId)");
    sqlquery.bindValue(":nItemId",QVariant(nItemId));
    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));
    sqlquery.bindValue(":nStartPosX",QVariant(pos.x()));
    sqlquery.bindValue(":nStartPosY",QVariant(pos.y()));
    sqlquery.bindValue(":nWidth",QVariant(pos.width()));
    sqlquery.bindValue(":nHeight",QVariant(pos.height()));
    sqlquery.bindValue(":eShowType",QVariant(m_Rcipe.eShowType));
    sqlquery.bindValue(":sShowRecipeId",QVariant(m_Rcipe.sShowRecipeId));
    sqlquery.bindValue(":sFontFamily",QVariant(m_Rcipe.sFontFamily));
    sqlquery.bindValue(":nFontSize",QVariant(m_Rcipe.nFontSize + 5));
    sqlquery.bindValue(":nTextColor",QVariant(ColorToInt(m_Rcipe.nTextColor)));
    sqlquery.bindValue(":nBackColor",QVariant(ColorToInt(m_Rcipe.nBackColor)));
    sqlquery.bindValue(":nCurrShowRow",QVariant(m_Rcipe.nCurrShowRow));
    sqlquery.bindValue(":bUseMacro",QVariant(m_Rcipe.bUseMacro));

    bool isExist = false;
    if(m_Rcipe.bUseMacro)
    {
        foreach(Macro lib,pwnd->macros)
        {
            if(lib.libName == m_Rcipe.macroName)
            {
                isExist = true;
            }
        }

        if(!isExist)
        {
            //pwnd->information(QObject::tr("配方显示器宏被删掉"));
            pwnd->information(QObject::tr("配方显示器使用的宏") + m_Rcipe.macroName +QObject::tr("方法") + m_Rcipe.functionName + QObject::tr("被删掉"), MSG_WARNING);
            //QMessageBox::about(this, QObject::tr("警告"), QObject::tr("下拉框宏被删掉"));
        }
    }

    if(m_Rcipe.bUseMacro && isExist)
    {
        count++;
        insertMacroTable(db,nItemId,count,nSceneId);
        sqlquery.bindValue(":nMacroId",QVariant(count));//宏指令序号
    }
    else
        sqlquery.bindValue(":nMacroId",QVariant(0));//宏指令序号

    //sqlquery.bindValue(":nScriptFuncId",QVariant(m_Rcipe.nScriptFuncId));
    //sqlquery.bindValue(":nMacroId",QVariant(m_Rcipe.nMacroId));
    sqlquery.bindValue(":nTouchPropId",QVariant(-1));
    sqlquery.bindValue(":nShowPropId",QVariant(-1));
    sqlquery.bindValue(":nTransparent",QVariant(m_Rcipe.nTransparent));
    sqlquery.bindValue(":nZvalue",QVariant(zValue()));
    sqlquery.bindValue(":nCollidindId",QVariant(index));
    bResult = sqlquery.exec();
    qDebug()<<"INSERT INTO recipeSelect "<<bResult;
}

QGraphicsItem *QRcipeItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    QRcipeItem *itemGroup = new QRcipeItem();

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

    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    itemGroup->setData(GROUP_TYPE_KEY,data(GROUP_TYPE_KEY).toInt());
    itemGroup->SaveSecurityPro(&sPro);
    itemGroup->m_Rcipe = m_Rcipe;
    itemGroup->setId(id());
    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }

    return itemGroup;
}

int QRcipeItem::GroupType()
{
    return SAM_DRAW_GROUP_RECIPE;
}

void QRcipeItem::save(QDataStream &stream)
{
    QVisableItem::save(stream);

    stream << m_Rcipe.eShowType;
    stream << m_Rcipe.sShowRecipeId;
    stream << m_Rcipe.sFontFamily;
    stream << m_Rcipe.nFontSize;
    stream << m_Rcipe.nTextColor;
    stream << m_Rcipe.nBackColor;
    stream << m_Rcipe.nCurrShowRow;
    stream << m_Rcipe.bUseMacro;
    stream << m_Rcipe.macroName;
    stream << m_Rcipe.functionName;
    stream << m_Rcipe.nTransparent;
}
void QRcipeItem::load(QDataStream &stream)
{
    QVisableItem::load(stream);

    stream >> m_Rcipe.eShowType;
    stream >> m_Rcipe.sShowRecipeId;
    stream >> m_Rcipe.sFontFamily;
    stream >> m_Rcipe.nFontSize;
    stream >> m_Rcipe.nTextColor;
    stream >> m_Rcipe.nBackColor;
    stream >> m_Rcipe.nCurrShowRow;
    stream >> m_Rcipe.bUseMacro;
    stream >> m_Rcipe.macroName;
    stream >> m_Rcipe.functionName;
    stream >> m_Rcipe.nTransparent;
}

void QRcipeItem::onSaveInfo(RCIPEINFO &Rcipe)
{
    m_Rcipe = Rcipe;
}

void QRcipeItem::insertMacroTable(QSqlDatabase &db,int itemId,int &count,int sceneId)
{
        int macroId = count;

        QSqlQuery sqlquery(db);
        sqlquery.prepare("INSERT INTO macro(MacroID , MacroLibName , MacroName , MacroType ,"
                "TimeInterval ,ControlAddr ,ControlAddrType ,ExecCondition , nCmpFactor , "
                "nCompID , SceneID ,scriptCount)"
                "VALUES (:MacroID , :MacroLibName , :MacroName , :MacroType ,"
                ":TimeInterval ,:ControlAddr ,:ControlAddrType ,:ExecCondition , :nCmpFactor ,"
                ":nCompID , :SceneID ,:scriptCount)");

        {
                sqlquery.bindValue(":MacroID",QVariant(macroId));// 宏的表 id
                sqlquery.bindValue(":MacroLibName",QVariant(m_Rcipe.macroName));//
                sqlquery.bindValue(":MacroName",QVariant("MACRO_MAIN"));//
                sqlquery.bindValue(":MacroType",QVariant(6));//
                sqlquery.bindValue(":nCompID",QVariant(itemId));// 控件表ID
                sqlquery.bindValue(":SceneID",QVariant(sceneId));//场景ID
                sqlquery.bindValue(":scriptCount",QVariant(1));//

                bool result = false;
                result = sqlquery.exec();
                qDebug() << "insert textProp macro :"<<result;
        }
}
QStringList QRcipeItem::getAllFonts()
{
    QStringList ls;
    ls.clear();
    ls << m_Rcipe.sFontFamily;
    return ls;
}

QString  QRcipeItem::getItemName()
{
    return QObject::tr("配方选择器");
}

int QRcipeItem::GetRicipeGroupId(int index)//返回配方组Id号
{
    int nRet = m_Rcipe.sShowRecipeId;
    if(index < m_Rcipe.sShowRecipeId)
    {
        m_Rcipe.sShowRecipeId = m_Rcipe.sShowRecipeId -1;
    }
    return nRet;
}

void QRcipeItem::setInvalid()
{
    m_Rcipe.sShowRecipeId = -1;
}

int QRcipeItem::getInvalid()
{
    return m_Rcipe.sShowRecipeId;
}
int QRcipeItem::checkMacroName(QString &msg)
{
    int result = -1;//脚本不存在
    msg = m_Rcipe.macroName;
    if(!m_Rcipe.bUseMacro)//未使用脚本
    {
        return 1;
    }
    foreach(Macro mac,pwnd->macros)
    {
        if(mac.libName == m_Rcipe.macroName)
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
