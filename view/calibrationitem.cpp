#include "view/calibrationitem.h"
#include "qpixmapitem.h"
#include "Frame/mainwindow.h"
#include "Frame/qprogectmanager.h"


extern MainWindow *pwnd;
CalibrationItem::CalibrationItem(QGraphicsItem *parent)
    :QVisableItem(parent)
{

}

int CalibrationItem::GroupType()
{
    return SAM_DRAW_GROUP_CALIBRATION;
}
QString CalibrationItem::getItemName()
{
    return QObject::tr("刻度");
}

QGraphicsItem *CalibrationItem::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    CalibrationItem *itemGroup = new CalibrationItem();

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

    itemGroup->m_calibrations=m_calibrations;
    itemGroup->onSaveCalibration(m_calibrations);
    itemGroup->SaveSecurityPro(&(this->sPro));
    itemGroup->setData(GROUP_NAME_KEY,data(GROUP_NAME_KEY).toString());
    itemGroup->setData(GROUP_TYPE_KEY,data(GROUP_TYPE_KEY).toString());
    itemGroup->setId(id());
    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }
    return itemGroup;

}

void CalibrationItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    count++;
    QColor mColor;
    QVisableItem::compile(db,nSceneId,count,index);
    int itemId = count;

    QSqlQuery sqlquery(db);
    bool flag=sqlquery.prepare("INSERT INTO calibration(nItemId,nSceneId,nLineColor,nTextColor,nCalibrationDirection,nNumberIncreaseDirection,"
                     "nMainNumberCount,nNextNumberCount,bShowText,nMaxNumber,nMinNumber,nDecimalCount,"
                     "nTextSize,nStartX,nStartY,nCalibrationWidth,nCalibrationHeight,"
                     "nZvalue,nCollidindId)"
                     "VALUES(:nItemId,:nSceneId,:nLineColor,:nTextColor,:nCalibrationDirection,:nNumberIncreaseDirection,"
                     ":nMainNumberCount,:nNextNumberCount,:bShowText,:nMaxNumber,:nMinNumber,:nDecimalCount,"
                     ":nTextSize,:nStartX,:nStartY,:nCalibrationWidth,:nCalibrationHeight,"
                     ":nZvalue,:nCollidindId)");
    sqlquery.bindValue(":nItemId",QVariant(itemId));// 表 id
    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));// scene id
    //相对场景的坐标及高宽
    QRectF rect = boundingRect();
    rect = this->mapRectToScene(rect);
    int startX=0;
    int startY=0;
    int widht=0;
    int height=0;
    QList<QGraphicsItem *> childs = childItems();
    //QRectItem *rectItem = NULL;
    foreach(QGraphicsItem *pItem,childs)
    {
        if(pItem->data(GROUP_NAME_KEY).toString() == "MainLine")
        {
            startX=pItem->sceneBoundingRect().x();
            startY=pItem->sceneBoundingRect().y();
            widht=pItem->sceneBoundingRect().width();
            height=pItem->sceneBoundingRect().height();
        }
    }
    //rect = this->mapToScene(rect.x(),rect.y(),rect.width(),rect.height());


    mColor=pwnd->StringTOColor(m_calibrations.nLineColor);
    sqlquery.bindValue(":nLineColor",QVariant(ColorToInt(mColor)));
    mColor=pwnd->StringTOColor(m_calibrations.nTextColor);
    sqlquery.bindValue(":nTextColor",QVariant(ColorToInt(mColor)));
    //刻度方向
    int num;
    if(m_calibrations.nCalibrationDirection==1){//左
        num=3;
        sqlquery.bindValue(":nStartX", QVariant((short)rect.x()-1));//left
        sqlquery.bindValue(":nStartY", QVariant(startY-1));//top
        sqlquery.bindValue(":nCalibrationWidth", QVariant((short)rect.width()+2));//width
        sqlquery.bindValue(":nCalibrationHeight", QVariant(height+2));//height
    }else if(m_calibrations.nCalibrationDirection==2){//右
        num=4;
        sqlquery.bindValue(":nStartX", QVariant((short)rect.x()-1));//left
        sqlquery.bindValue(":nStartY", QVariant(startY-1));//top
        sqlquery.bindValue(":nCalibrationWidth", QVariant((short)rect.width()+2));//width
        sqlquery.bindValue(":nCalibrationHeight", QVariant(height+2));//height
    }else if(m_calibrations.nCalibrationDirection==3){//上
        num=1;
        sqlquery.bindValue(":nStartX", QVariant(startX-1));//left
        sqlquery.bindValue(":nStartY", QVariant((short)rect.y()-1));//top
        sqlquery.bindValue(":nCalibrationWidth", QVariant(widht+2));//width
        sqlquery.bindValue(":nCalibrationHeight", QVariant((short)rect.height()+2));//height
    }else if(m_calibrations.nCalibrationDirection==4){//下
        num=2;
        sqlquery.bindValue(":nStartX", QVariant(startX-1));//left
        sqlquery.bindValue(":nStartY", QVariant((short)rect.y()-1));//top
        sqlquery.bindValue(":nCalibrationWidth", QVariant(widht+2));//width
        sqlquery.bindValue(":nCalibrationHeight", QVariant((short)rect.height()+2));//height
    }
    sqlquery.bindValue(":nCalibrationDirection",QVariant(num));

    if(m_calibrations.direction==QDialog::tr("向上")){
        num=1;
    }else if(m_calibrations.direction==QDialog::tr("向下")){
        num=2;
    }else if(m_calibrations.direction==QDialog::tr("向左")){
        num=3;
    }else if(m_calibrations.direction==QDialog::tr("向右")){
        num=4;
    }
    sqlquery.bindValue(":nNumberIncreaseDirection",QVariant(num));
    sqlquery.bindValue(":nMainNumberCount",QVariant(m_calibrations.nMainNumberCount));
    sqlquery.bindValue(":nNextNumberCount",QVariant(m_calibrations.nNextNumberCount));
    sqlquery.bindValue(":bShowText",QVariant(m_calibrations.bShowText));

    sqlquery.bindValue(":nMaxNumber",QVariant(m_calibrations.nMaxNumber.toDouble()));

    sqlquery.bindValue(":nMinNumber",QVariant(m_calibrations.nMinNumber.toDouble()));

    sqlquery.bindValue(":nDecimalCount",QVariant(m_calibrations.nDecimalCount));
    sqlquery.bindValue(":nTextSize",QVariant(m_calibrations.stextsize.toInt()));

    sqlquery.bindValue(":nZvalue",QVariant(zValue()));
    sqlquery.bindValue(":nCollidindId",QVariant(index));
    flag=sqlquery.exec();
}

void CalibrationItem::save(QDataStream &stream)
{
    if(pwnd->getProVersion() >= 3271)
    {
        QVisableItem::save(stream);
    }
    else
    {
        QItemGroup::save(stream);
    }

    stream << m_calibrations.bShowText;
    stream << m_calibrations.direction;
    stream << m_calibrations.id;
    stream << m_calibrations.nCalibrationDirection;
    stream << m_calibrations.nCalibrationHeight;
    stream << m_calibrations.nCalibrationWidth;
    stream << m_calibrations.nDecimalCount;
    stream << m_calibrations.nLineColor;
    stream << m_calibrations.nMainNumberCount;
    stream << m_calibrations.nMaxNumber;
    stream << m_calibrations.nMinNumber;
    stream << m_calibrations.nNextNumberCount;
    stream << m_calibrations.nNumberIncreaseDirection;
    stream << m_calibrations.nStartX;
    stream << m_calibrations.nStartY;
    stream << m_calibrations.nTextColor;
    stream << m_calibrations.nTextSize;
    stream << m_calibrations.stextsize;

}
void CalibrationItem::load(QDataStream &stream)
{
    if(pwnd->getProVersion() >= 3271)
    {
        QVisableItem::load(stream);
    }
    else
    {
        QItemGroup::load(stream);
        sPro.bNotice = false;
        sPro.bDelay = false;
        sPro.enableTouch = false;
        sPro.enableVisable = false;
    }
    stream >> m_calibrations.bShowText;
    stream >> m_calibrations.direction;
    stream >> m_calibrations.id;
    stream >> m_calibrations.nCalibrationDirection;
    stream >> m_calibrations.nCalibrationHeight;
    stream >> m_calibrations.nCalibrationWidth;
    stream >> m_calibrations.nDecimalCount;
    stream >> m_calibrations.nLineColor;
    stream >> m_calibrations.nMainNumberCount;
    stream >> m_calibrations.nMaxNumber;
    stream >> m_calibrations.nMinNumber;
    stream >> m_calibrations.nNextNumberCount;
    stream >> m_calibrations.nNumberIncreaseDirection;
    stream >> m_calibrations.nStartX;
    stream >> m_calibrations.nStartY;
    stream >> m_calibrations.nTextColor;
    stream >> m_calibrations.nTextSize;
    stream >> m_calibrations.stextsize;
}

void CalibrationItem::onSaveCalibration(Calibration cali_st)    //保存刻度显示信息
{
    m_calibrations = cali_st;
}
