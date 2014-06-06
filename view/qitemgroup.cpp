#include <view/qitemgroup.h>
#include "headfile/allgraphics.h"
#include "Frame/mainwindow.h"
#include "view/statictextitem.h"
#include "view/qmessageshowattr.h"
#include "view/flowblockitem.h"
#include "view/calibrationitem.h"
#include "view/SliderItem.h"
#include "view/alarmbar.h"
#include "view/alarmitem.h"
#include "view/hisalarmitem.h"
#include "view/switchitem.h"
#include "view/QRecipeItem.h"
#include "view/QRecipetableItem.h"
#include "view/ImageItem.h"
#include "view/animationitem.h"
#include "view/dyncircleattr.h"
#include "view/dynrectattr.h"
#include "view/qtrendattr.h"
#include "view/qtrenddatagroupattr.h"
#include "view/QtableItem.h"
#include "view/qdropdownattr.h"
#include "view/qhistorydatashowattr.h"
#include "view/qmessageboradattr.h"
#include "view/mfbtnitem.h"
#include "view/DataDisplayItem.h"
#include "view/ChartItem.h"
#include "view/akcomboitem.h"
#include "view/xytrend.h"

extern  MainWindow *pwnd;
QItemGroup::QItemGroup(QGraphicsItem *parent)
    :GraphicsItemGroupSamExt(parent)
{
    frameRect = NULL;
    backItem = NULL;
    textItem = NULL;
}

//复制当前itemGroup到新的item
QGraphicsItem *QItemGroup::Clone()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    QItemGroup *itemGroup = new QItemGroup();

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
////////////////wxy add start
        case SAM_DRAW_OBJECT_RECT_NEW:              //矩形
            {
                QRectBasicItem *rectItem = dynamic_cast<QRectBasicItem *>(pItem);
                if(rectItem)
                {
                    pCopy = rectItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_ELIPSE_NEW:              //圆
            {
                QElipseBasicItem *elipseItem = dynamic_cast<QElipseBasicItem *>(pItem);
                if(elipseItem)
                {
                    pCopy = elipseItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_LINE_NEW:                 //直线
            {
                QLineBasicItem * lineItem = dynamic_cast<QLineBasicItem *>(pItem);
                if(lineItem)
                {
                    pCopy = lineItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_POLYGON_NEW:              //多边形
            {
                QPolygonBasicItem *polygonItem = dynamic_cast<QPolygonBasicItem *>(pItem);
                if(polygonItem)
                {
                    pCopy = polygonItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:             //19
            {
                QFoldLineBasicItem *foldlineItem = dynamic_cast<QFoldLineBasicItem *>(pItem);
                if(foldlineItem)
                {
                    pCopy = foldlineItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_FREELINE_NEW:             //20
            {
                QFreeLineBasicItem * freelineItem = dynamic_cast<QFreeLineBasicItem *>(pItem);
                if(freelineItem)
                {
                    pCopy = freelineItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_LINECIRCLE_NEW:           //25
            {
                QLineCircleBasicItem *circleItem = dynamic_cast<QLineCircleBasicItem *>(pItem);
                if(circleItem)
                {
                    pCopy = circleItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
            {
                QRoundedRectBasic *roundedrectItem = dynamic_cast<QRoundedRectBasic *>(pItem);
                if(roundedrectItem)
                {
                    pCopy = roundedrectItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_ARC_NEW:
            {
                QArcBasicItem *arcItem = dynamic_cast<QArcBasicItem *>(pItem);
                if(arcItem)
                {
                    pCopy = arcItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
///////////////wxy add end
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
    itemGroup->setId(id());
    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }
    return itemGroup;
}

//编译的时候存储item 属性到数据库
void QItemGroup::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    //count++;
    //QSqlQuery sqlquery(db);
    QMap<QString,QVariant> mapQuery;
	if (GroupType() == SAM_DRAW_GROUP_USER)
	{
		count++;
//		sqlquery.prepare("INSERT INTO userGroup(nItemId ,nSceneId ,sPath ,nLp ,"
//			"nTp ,nWidth ,nHeight ,nZvalue , nCollidindId )"
//			"VALUES(:nItemId ,:nSceneId ,:sPath ,:nLp ,"
//			":nTp ,:nWidth ,:nHeight ,:nZvalue ,:nCollidindId)");
        mapQuery.insert(":nSceneId",QVariant(nSceneId));
        mapQuery.insert(":nItemId",QVariant(count));

		QString path = bitShot();
        mapQuery.insert(":sPath",QVariant(path));

		QRect rect = sceneBoundingRect().toRect();
        mapQuery.insert(":nLp",QVariant(rect.x())); //X
        mapQuery.insert(":nTp",QVariant(rect.y())); //Y
        mapQuery.insert(":nWidth",QVariant(rect.width())); //W
        mapQuery.insert(":nHeight",QVariant(rect.height())); //H
        mapQuery.insert(":nZvalue",QVariant(zValue()));//层次

        mapQuery.insert(":nCollidindId",QVariant(index));//碰撞ID
        pwnd->inSertDbQuery("userGroup",mapQuery);
        //bool result = false;
        //result = sqlquery.exec();
        //qDebug() << "insert userGroup table :"<<result;
	}

    SamDrawScene *pScene = dynamic_cast<SamDrawScene *>(scene());
    if(pScene && pScene->nIsSceneOrWindow == 2)
    {
        //是自定义键盘的item
        //先新建键盘——item关联表 item表在派生类中创建

        mapQuery.clear();
        //QSqlQuery sqlquery(db);

//        sqlquery.prepare("INSERT INTO kbAndItem(nKeyBoardId , nItemId ,nItemTableType ) "
//                         "VALUES (:nKeyBoardId ,:nItemId ,:nItemTableType)");
        mapQuery.insert(":nKeyBoardId",QVariant(nSceneId));
        mapQuery.insert(":nItemId",QVariant(count));
        mapQuery.insert(":nId",QVariant(id()));
        mapQuery.insert(":nItemTableType",QVariant(GroupType()));

        pwnd->inSertDbQuery("kbAndItem",mapQuery);
//        bool result = false;
//        result = sqlquery.exec();
//        qDebug() << "insert kbAndItem table :"<<result;

    }
    if(pScene && pScene->nIsSceneOrWindow != 2)
    {
        //窗口或者场景item
        //先新建键盘——item关联表
        //item表在派生类中创建

        mapQuery.clear();
//        QSqlQuery sqlquery(db);

//        sqlquery.prepare("INSERT INTO sceneAndItem(nSceneId,nItemId,nItemTableType)"
//                         "VALUES(:nSceneId,:nItemId,:nItemTableType)");
        mapQuery.insert(":nSceneId",QVariant(nSceneId));
        mapQuery.insert(":nItemId",QVariant(count));
        mapQuery.insert(":nId",QVariant(id()));
        //int t = this->GroupType();
        mapQuery.insert(":nItemTableType",QVariant(GroupType()));

        pwnd->inSertDbQuery("sceneAndItem",mapQuery);
//        bool result = false;
//        result = sqlquery.exec();
//        qDebug() << "insert sceneAndItem table :"<<result;
    }
	
}

int QItemGroup::GroupType()
{
    //在派生类实现
    return gType;
}
int QItemGroup::checkMacroName(QString &msg)
{
    //在派生类实现
    return 1;
}
void QItemGroup::SetText(QString text)
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetText(text);
    }
}
void QItemGroup::SetFontSize(int nFontSize) //设置字体大小
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->m_font.setPointSize(nFontSize);
        pText->update(pText->m_rect);
    }
}

void QItemGroup::SetFontName(QString sName) //设置字体
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->m_font.setFamily(sName);
        pText->update(pText->m_rect);
    }
}
void QItemGroup::SetTextAlign(int nAlignType)
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

//设置粗体
void QItemGroup::SetBold(bool flag)
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetFontBold(flag);
    }
}

//设置斜体
void QItemGroup::SetItalic(bool flag)
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetFontItalic(flag);
    }
}

//设置下划线
void QItemGroup::SetUnderLine(bool flag)
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetFontUnderLine(flag);
    }
}

//设置文本色
void QItemGroup::SetTextColor(QColor color)
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetFontColor(color);
    }
}
void QItemGroup::SetPicture(QString path,EITEM_TYPE bLib,int alpha,QColor color)
{

}
void QItemGroup::SaveSecurityPro(securityPro *pro)
{
}

void QItemGroup::save(QDataStream &stream)
{

    int size = childItems().size();
    stream << size;


    QList<QGraphicsItem *> itemList;
    itemList.clear();
    itemList = childItems();
    for(int i=0;i<itemList.size();i++)
    {
        switch(itemList.at(i)->type())
        {
        case SAM_DRAW_OBJECT_RECT:              //15
            {
                stream << QRectItem::Type;
                stream << dynamic_cast<QRectItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_ELIPSE:              //16
            {
                stream << QElipseItem::Type;
                stream << dynamic_cast<QElipseItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_LINE:                 //17
            {
                stream << QLineItem::Type;
                stream << dynamic_cast<QLineItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_POLYGON:              //18
            {
                stream << QPolygonItem::Type;
                stream << dynamic_cast<QPolygonItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_FOLDLINE:             //19
            {
                stream << QFoldLineItem::Type;
                stream << dynamic_cast<QFoldLineItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_FREELINE:             //20
            {
                stream << QFreeLineItem::Type;
                stream << dynamic_cast<QFreeLineItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_TEXT:                 //22
            {
                stream << QSimpleTextItem::Type;
                stream << dynamic_cast<QSimpleTextItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_PIXMAP:
            {
                stream << QPixmapItem::Type;
                QPixmapItem *pPixmap = dynamic_cast<QPixmapItem *>(itemList.at(i));
                QRectF rect = pPixmap->sceneBoundingRect();
                stream << rect;
                break;
            }
        case SAM_DRAW_OBJECT_LINECIRCLE:           //25
            {
                stream << QLineCircleItem::Type;
                stream << dynamic_cast<QLineCircleItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
            {
                stream << QRoundedRect::Type;
                stream << dynamic_cast<QRoundedRect *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_ARC:
            {
                stream << QArcItem::Type;
                stream << dynamic_cast<QArcItem *>(itemList.at(i));
                break;
            }
////////////////wxy add start
        case SAM_DRAW_OBJECT_RECT_NEW:              //15
            {
                stream << QRectBasicItem::Type;
                stream << dynamic_cast<QRectBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_ELIPSE_NEW:              //16
            {
                stream << QElipseBasicItem::Type;
                stream << dynamic_cast<QElipseBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_LINE_NEW:                 //17
            {
                stream << QLineBasicItem::Type;
                stream << dynamic_cast<QLineBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_POLYGON_NEW:              //18
            {
                stream << QPolygonBasicItem::Type;
                stream << dynamic_cast<QPolygonBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:             //19
            {
                stream << QFoldLineBasicItem::Type;
                stream << dynamic_cast<QFoldLineBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_FREELINE_NEW:             //20
            {
                stream << QFreeLineBasicItem::Type;
                stream << dynamic_cast<QFreeLineBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_LINECIRCLE_NEW:           //25
            {
                stream << QLineCircleBasicItem::Type;
                stream << dynamic_cast<QLineCircleBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
            {
                stream << QRoundedRectBasic::Type;
                stream << dynamic_cast<QRoundedRectBasic *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_ARC_NEW:
            {
                stream << QArcBasicItem::Type;
                stream << dynamic_cast<QArcBasicItem *>(itemList.at(i));
                break;
            }
///////////////wxy add end
        case SAM_DRAW_OBJECT_GROUP:                //23
            {
            //    stream << ((dynamic_cast<QItemGroup *>(itemList.at(i)))->childItems()).size();
                QItemGroup *group = dynamic_cast<QItemGroup *>(itemList.at(i));
				stream << group->GroupType();
                group->save(stream);
                break;
            }
        default:
            break;
        }
    }

    int typeKey = data(GROUP_TYPE_KEY).toInt();
    QString name = data(GROUP_NAME_KEY).toString();
    stream << typeKey;
    stream << name;
    if(0 <= typeKey && typeKey < 200)
    {
        if(typeKey == GROUP_TYPE_STATICPIC || typeKey == GROUP_TYPE_GIFPIC)
        {
            stream << sceneBoundingRect().toRect();
        }
    }
    stream << id();
}
void QItemGroup::load(QDataStream &stream)
{
    int size =0;
    stream >> size;

    while(size>0 && !stream.atEnd())
    {
        size--;
        int type = -1;
        stream >> type;
        switch(type)
        {
        case SAM_DRAW_OBJECT_RECT:              //15
            {
                QRectItem *rectItem = new QRectItem();
                stream >> rectItem;
                addToGroup(rectItem);
                break;
            }
        case SAM_DRAW_OBJECT_ELIPSE:              //16
            {
                QElipseItem *elipseItem = new QElipseItem();
                stream >> elipseItem;
                addToGroup(elipseItem);
                break;
            }
        case SAM_DRAW_OBJECT_LINE:                 //17
            {
                QLineItem *lineItem = new QLineItem();
                stream >> lineItem;
                addToGroup(lineItem);
                break;
            }
        case SAM_DRAW_OBJECT_POLYGON:              //18
            {
                QPolygonItem *polygonItem = new QPolygonItem();
                stream >> polygonItem;
                addToGroup(polygonItem);
                break;
            }
        case SAM_DRAW_OBJECT_FOLDLINE:             //19
            {
                QFoldLineItem *foldLineItem = new QFoldLineItem();
                stream >> foldLineItem;
                addToGroup(foldLineItem);
                break;
            }
        case SAM_DRAW_OBJECT_FREELINE:             //20
            {
                QFreeLineItem *freeLineItem = new QFreeLineItem();
                stream >> freeLineItem;
                addToGroup(freeLineItem);
                break;
            }
        case SAM_DRAW_OBJECT_TEXT:                 //22
            {
                QSimpleTextItem *textItem = new QSimpleTextItem();
                stream >> textItem;
                addToGroup(textItem);
                break;
            }
        case SAM_DRAW_OBJECT_PIXMAP:
            {
                QPixmapItem *pPixmap = new QPixmapItem();
                QRectF rect;
                stream >> rect;
                QPixmap pixmap(rect.size().toSize());
                pPixmap->setPixmap(pixmap);
                pPixmap->setPos(rect.topLeft());
                //stream >> pPixmap;
                addToGroup(pPixmap);
                break;
            }
        case SAM_DRAW_OBJECT_LINECIRCLE:           //25
            {
                QLineCircleItem *lineCircleItem = new QLineCircleItem();
                stream >> lineCircleItem;
                addToGroup(lineCircleItem);
                break;
            }
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
            {
                QRoundedRect *pRoundItem = new QRoundedRect();
                stream >> pRoundItem;
                addToGroup(pRoundItem);
                break;
            }
        case SAM_DRAW_OBJECT_ARC:
            {
                QArcItem *pArcItem = new QArcItem();
                stream >> pArcItem;
                addToGroup(pArcItem);
                break;
            }
 ///////////////wxy add start
        case SAM_DRAW_OBJECT_RECT_NEW:              //35
            {
                QRectBasicItem *rectItem = new QRectBasicItem();
                stream >> rectItem;
                addToGroup(rectItem);
                break;
            }
        case SAM_DRAW_OBJECT_ELIPSE_NEW:              //36
            {
                QElipseBasicItem *elipseItem = new QElipseBasicItem();
                stream >> elipseItem;
                addToGroup(elipseItem);
                break;
            }
        case SAM_DRAW_OBJECT_LINE_NEW:                 //37
            {
                QLineBasicItem *lineItem = new QLineBasicItem();
                stream >> lineItem;
                addToGroup(lineItem);
                break;
            }
        case SAM_DRAW_OBJECT_POLYGON_NEW:              //38
            {
                QPolygonBasicItem *polygonItem = new QPolygonBasicItem();
                stream >> polygonItem;
                addToGroup(polygonItem);
                break;
            }
        case SAM_DRAW_OBJECT_FOLDLINE_NEW:             //39
            {
                QFoldLineBasicItem *foldLineItem = new QFoldLineBasicItem();
                stream >> foldLineItem;
                addToGroup(foldLineItem);
                break;
            }
        case SAM_DRAW_OBJECT_FREELINE_NEW:             //40
            {
                QFreeLineBasicItem *freeLineItem = new QFreeLineBasicItem();
                stream >> freeLineItem;
                addToGroup(freeLineItem);
                break;
            }
        case SAM_DRAW_OBJECT_LINECIRCLE_NEW:           //42
            {
                QLineCircleBasicItem *lineCircleItem = new QLineCircleBasicItem();
                stream >> lineCircleItem;
                addToGroup(lineCircleItem);
                break;
            }
        case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:           //43
            {
                QRoundedRectBasic *pRoundItem = new QRoundedRectBasic();
                stream >> pRoundItem;
                addToGroup(pRoundItem);
                break;
            }
        case SAM_DRAW_OBJECT_ARC_NEW:                   //44
            {
                QArcBasicItem *pArcItem = new QArcBasicItem();
                stream >> pArcItem;
                addToGroup(pArcItem);
                break;
            }
 ///////////////wxy add end
        case SAM_DRAW_OBJECT_GROUP:                //23
		case SAM_DRAW_GROUP_USER: 
            {
                QItemGroup *groupItem = new QItemGroup();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }		    
		case SAM_DRAW_GROUP_KEY:
			{
				KeyBoardItem *groupItem = new KeyBoardItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_STATICTEXT:
			{
				StaticTextItem *groupItem = new StaticTextItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_MESSAGE:
			{
				QMessageShowAttr *groupItem = new QMessageShowAttr;
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_FLOW://流动块
			{
				FlowBlockItem *groupItem = new FlowBlockItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_CALIBRATION://刻度
			{
				CalibrationItem *groupItem = new CalibrationItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_SLIDER://滑动块
			{
				SliderItem *groupItem = new SliderItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_ALARMBAR://动态报警条
			{
				AlarmBar *groupItem = new AlarmBar();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_ALARMITEM://动态报警条item
			{
				AlarmItem *groupItem = new AlarmItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_HISALARMITEM://动态报警条item
			{
				HisAlarmItem *groupItem = new HisAlarmItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_SWITCH://开关
			{
				SwitchItem *groupItem = new SwitchItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
                        }
        case SAM_DRAW_GROUP_MFBTN://多功能开关
                {
                        MfBtnItem *groupItem = new MfBtnItem();
                        groupItem->load(stream);
                        addToGroup(groupItem);
                        break;
                }
		case SAM_DRAW_GROUP_VALUE:
		case SAM_DRAW_GROUP_TIME:
		case SAM_DRAW_GROUP_ASCII:
			{
				DataDisplayItem *groupItem = new DataDisplayItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_RECIPE:
			{
				QRcipeItem *groupItem = new QRcipeItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_RECIPESHOW:
			{
				QRecipeTableItem *groupItem = new QRecipeTableItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_STATICPIC:
			{
				QStaticPictureItem *groupItem = new QStaticPictureItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_IMAGE:
			{
				ImageItem *groupItem = new ImageItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_ANIMATION:
			{
				AnimationItem *groupItem = new AnimationItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_CHART:
			{
				ChartItem *groupItem = new ChartItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_DYNCIRCLE://动态圆
			{
				DynCircleAttr *groupItem = new DynCircleAttr();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_DYNRECT://动态矩形
			{
				DynRectAttr *groupItem = new DynRectAttr();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_TREND://曲线
			{
				QTrendAttr *groupItem = new QTrendAttr();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_GROUPDATA://数据群组
			{
				QTrendDataGroupAttr *groupItem = new QTrendDataGroupAttr();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_TABLE://表格
			{
				QTableItem *groupItem = new QTableItem();
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_DROPDOWN://下拉框
			{
				QDropdownAttr *groupItem = new QDropdownAttr;
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
		case SAM_DRAW_GROUP_HISTORYDATE://历史数据显示器
			{
				QHistoryDataShowAttr *groupItem = new QHistoryDataShowAttr;
				groupItem->load(stream);
				addToGroup(groupItem);
				break;
			}
        case SAM_DRAW_GROUP_TEXTBOARD://留言板
                {
                        qMessageBoradAttr *groupItem = new qMessageBoradAttr;
                        groupItem->load(stream);
                        addToGroup(groupItem);
                        break;
                }
        case SAM_DRAW_GROUP_COMBOBOX://留言板
                {
                        AkComboItem *groupItem = new AkComboItem;
                        groupItem->load(stream);
                        addToGroup(groupItem);
                        break;
                }
        case SAM_DRAW_GROUP_XYTREND://X-Y曲线
            {
                XYtrend *groupItem = new XYtrend();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        default:
            break;
        }
    }

    int typeKey = 0;
    QString name ;
    stream >> typeKey;
    stream >> name;
    setData(GROUP_TYPE_KEY,typeKey);
    setData(GROUP_NAME_KEY,QVariant(name));
    if(0 <= typeKey && typeKey < 200)
    {
        if(typeKey == GROUP_TYPE_STATICPIC || typeKey == GROUP_TYPE_GIFPIC)
        {
            QRectF rc;
            stream >> rc;

    //        stream << sceneBoundingRect().toRect();
        }
    }
    if(pwnd->getProVersion() >= 3456)
    {
        int id;
        stream >> id;
        setId(id);
    }
    else
    {
        setId(-1);
    }


    foreach(QGraphicsItem *pItem,childItems())
    {
            pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
            pItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }


}

//返回文本item指针
QGraphicsItem* QItemGroup::GetTextItem()
{
    foreach(QGraphicsItem* pItem,childItems())
    {
        if(pItem->type() == SAM_DRAW_OBJECT_TEXT)
        {
            return pItem;
        }
    }
    return NULL;
}

//返回图库或者图片item指针
QGraphicsItem* QItemGroup::GetPicItem()
{
    foreach(QGraphicsItem* pItem,childItems())
    {
        if(pItem->type() == SAM_DRAW_OBJECT_GROUP)
        {
            int type = pItem->data(GROUP_TYPE_KEY).toInt();
            if(type == USER_DEFINE_GROUP || type == LIBRARY_LIB_GROUP
               || type == LIBRARY_PIXMAP_GROUP)
                return pItem;
        }
        else if(pItem->type() == SAM_DRAW_OBJECT_PIXMAP)
        {
            return pItem;
        }
        else if(SWITCH_BACK_TYPE == pItem->data(GROUP_NAME_KEY).toInt())
        {
            return pItem;
        }

    }
    return NULL;
}
//获得操作地址
QList<Keyboard> QItemGroup::getAddress()
{
    QList<Keyboard> kb;
    return kb;
}
//设置操作地址
void QItemGroup::setAddress(QList<Keyboard> addr)
{}
void QItemGroup::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
 {
    QPen pen = painter->pen();
    pen.setStyle(Qt::NoPen);
    painter->setPen(pen);
    QGraphicsItemGroup::paint(painter,option,widget);
 }

void QItemGroup::redrawForChangeLanguage(int index)
{
}

void QItemGroup::sampChanged(QString oldName,QString newName,int sampType)
{}

void QItemGroup::changeItemLanguageAttr(int lanNum)
{
}

void QItemGroup::redrawForChangeStatus(int index, int lan)
{
    foreach(QGraphicsItem *item,this->childItems())
    {
        if (item)
        {
            if(SAM_DRAW_OBJECT_GROUP == item->type())
            {
                QItemGroup *pItem = dynamic_cast<QItemGroup *> (item);
                if(pItem)
                {
                    pItem->redrawForChangeStatus(pItem->getCurrentState(),0);
                }
            }
        }
    }
}

int QItemGroup::getCurrentState()
{
    return -1;
}

QString  QItemGroup::getItemName()
{
    return QObject::tr("组合图形");
}

QStringList QItemGroup::getItemStates()
{
    QStringList ls;
    ls.clear();
    return ls;
}
QStringList QItemGroup::getAllFonts()
{
	QStringList ls;
	ls.clear();
	return ls;
}
QVector<ADDRPRO> QItemGroup::getAllItemAddr()
{
    QVector<ADDRPRO> kb;
    kb.clear();
    return kb;
}

void QItemGroup::replaceAllItemText(int iLan,int iSta,QString sNewText)
{

}

TEXTPRO QItemGroup::getAllItemText()
{
    TEXTPRO sText;
   // sText.clear();
    return sText;
}

QString QItemGroup::bitShot()
{
	QString path;
	QGraphicsScene tmpScene;
	QGraphicsItem *item = Clone();
	if (!item)
	{
		return path;
	}
	tmpScene.addItem(item);
	QRectF rect = item->sceneBoundingRect();

	QPixmap pixmap(rect.width(),rect.height());
	pixmap.fill(QColor(0,0,0,0));
	QPainter painter(&pixmap);

	QRectF target = QRectF(0,0,rect.width(),rect.height());
	rect = QRectF(rect.x(),rect.y(),rect.width()+1,rect.height()+1);
	tmpScene.render(&painter,target,rect,Qt::IgnoreAspectRatio);

	QString date = QDateTime::currentDateTime().toString("yyMMddhhmmss");
	QImage picture = pixmap.toImage();
	QString newpath;
	QStringList list;
	int count;
	list<<"*.JPEG";
	list<<"*.gif";
	list<<"*.png";
	list<<"*.bmp";
	list<<"*.jpg";
	QString proName = "resource";
	QDir dir = QDir(proName);
	QString sName;
	if(!dir.exists())
	{
		dir.mkpath(dir.absolutePath());
	}
	count = dir.entryList(list).count();
	newpath = newpath.number(count);
	newpath = proName+"/"+date+"_"+newpath+".png";
	if (picture.save(newpath,"PNG"))
	{
		newpath = newpath.replace("\\","/");
		newpath = newpath.section("/",-1);
		newpath = "/data/data/com.android.Samkoonhmi/pictures/"+newpath;
		path = newpath;
	}
	return path;
}



/*
void QItemGroup::saveEx(QDataStream &stream)
{
    int size = childItems().size();
    stream << size;

    QList<QGraphicsItem *> itemList;
    itemList.clear();
    itemList = childItems();
    for(int i=0;i<itemList.size();i++)
    {
        switch(itemList.at(i)->type())
        {
        case SAM_DRAW_OBJECT_RECT:              //15
            {
                stream << QRectBasicItem::Type;
                stream << dynamic_cast<QRectBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_ELIPSE:              //16
            {
                stream << QElipseBasicItem::Type;
                stream << dynamic_cast<QElipseBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_LINE:                 //17
            {
                stream << QLineBasicItem::Type;
                stream << dynamic_cast<QLineBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_POLYGON:              //18
            {
                stream << QPolygonBasicItem::Type;
                stream << dynamic_cast<QPolygonBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_FOLDLINE:             //19
            {
                stream << QFoldLineBasicItem::Type;
                stream << dynamic_cast<QFoldLineBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_FREELINE:             //20
            {
                stream << QFreeLineBasicItem::Type;
                stream << dynamic_cast<QFreeLineBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_TEXT:                 //22
            {
                stream << QSimpleTextItem::Type;
                stream << dynamic_cast<QSimpleTextItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_PIXMAP:
            {
                stream << QPixmapItem::Type;
                QPixmapItem *pPixmap = dynamic_cast<QPixmapItem *>(itemList.at(i));
                QRectF rect = pPixmap->sceneBoundingRect();
                stream << rect;
                break;
            }
        case SAM_DRAW_OBJECT_LINECIRCLE:           //25
            {
                stream << QLineCircleBasicItem::Type;
                stream << dynamic_cast<QLineCircleBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
            {
                stream << QRoundedRectBasic::Type;
                stream << dynamic_cast<QRoundedRectBasic *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_ARC:
            {
                stream << QArcBasicItem::Type;
                stream << dynamic_cast<QArcBasicItem *>(itemList.at(i));
                break;
            }
        case SAM_DRAW_OBJECT_GROUP:                //23
            {
                QItemGroup *group = dynamic_cast<QItemGroup *>(itemList.at(i));
                stream << group->GroupType();
                if(group->GroupType() == SAM_DRAW_GROUP_USER)
                {
                    group->saveEx(stream);
                }
                else
                {
                    group->save(stream);
                }
                break;
            }
        default:
            break;
        }
    }

    int typeKey = data(GROUP_TYPE_KEY).toInt();
    QString name = data(GROUP_NAME_KEY).toString();
    stream << typeKey;
    stream << name;
    if(0 <= typeKey && typeKey < 200)
    {
        if(typeKey == GROUP_TYPE_STATICPIC || typeKey == GROUP_TYPE_GIFPIC)
        {
            stream << sceneBoundingRect().toRect();
        }
    }
}

void QItemGroup::loadEx(QDataStream &stream)
{
    int size =0;
    stream >> size;

    while(size>0 && !stream.atEnd())
    {
        size--;
        int type = -1;
        stream >> type;
        switch(type)
        {
        case SAM_DRAW_OBJECT_RECT:              //15
            {
                QRectBasicItem *rectItem = new QRectBasicItem();
                stream >> rectItem;
                addToGroup(rectItem);
                break;
            }
        case SAM_DRAW_OBJECT_ELIPSE:              //16
            {
                QElipseBasicItem *elipseItem = new QElipseBasicItem();
                stream >> elipseItem;
                addToGroup(elipseItem);
                break;
            }
        case SAM_DRAW_OBJECT_LINE:                 //17
            {
                QLineBasicItem *lineItem = new QLineBasicItem();
                stream >> lineItem;
                addToGroup(lineItem);
                break;
            }
        case SAM_DRAW_OBJECT_POLYGON:              //18
            {
                QPolygonBasicItem *polygonItem = new QPolygonBasicItem();
                stream >> polygonItem;
                addToGroup(polygonItem);
                break;
            }
        case SAM_DRAW_OBJECT_FOLDLINE:             //19
            {
                QFoldLineBasicItem *foldLineItem = new QFoldLineBasicItem();
                stream >> foldLineItem;
                addToGroup(foldLineItem);
                break;
            }
        case SAM_DRAW_OBJECT_FREELINE:             //20
            {
                QFreeLineBasicItem *freeLineItem = new QFreeLineBasicItem();
                stream >> freeLineItem;
                addToGroup(freeLineItem);
                break;
            }
        case SAM_DRAW_OBJECT_TEXT:                 //22
            {
                QSimpleTextItem *textItem = new QSimpleTextItem();
                stream >> textItem;
                addToGroup(textItem);
                break;
            }
        case SAM_DRAW_OBJECT_PIXMAP:
            {
                QPixmapItem *pPixmap = new QPixmapItem();
                QRectF rect;
                stream >> rect;
                QPixmap pixmap(rect.size().toSize());
                pPixmap->setPixmap(pixmap);
                pPixmap->setPos(rect.topLeft());
                //stream >> pPixmap;
                addToGroup(pPixmap);
                break;
            }
        case SAM_DRAW_OBJECT_LINECIRCLE:           //25
            {
                QLineCircleBasicItem *lineCircleItem = new QLineCircleBasicItem();
                stream >> lineCircleItem;
                addToGroup(lineCircleItem);
                break;
            }
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
            {
                QRoundedRectBasic *pRoundItem = new QRoundedRectBasic();
                stream >> pRoundItem;
                addToGroup(pRoundItem);
                break;
            }
        case SAM_DRAW_OBJECT_ARC:
            {
                QArcBasicItem *pArcItem = new QArcBasicItem();
                stream >> pArcItem;
                addToGroup(pArcItem);
                break;
            }
        case SAM_DRAW_OBJECT_GROUP:                //23
        case SAM_DRAW_GROUP_USER:
            {
                QItemGroup *groupItem = new QItemGroup();
                groupItem->loadEx(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_KEY:
            {
                KeyBoardItem *groupItem = new KeyBoardItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_STATICTEXT:
            {
                StaticTextItem *groupItem = new StaticTextItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_MESSAGE:
            {
                QMessageShowAttr *groupItem = new QMessageShowAttr;
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_FLOW://流动块
            {
                FlowBlockItem *groupItem = new FlowBlockItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_CALIBRATION://刻度
            {
                CalibrationItem *groupItem = new CalibrationItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_SLIDER://滑动块
            {
                SliderItem *groupItem = new SliderItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_ALARMBAR://动态报警条
            {
                AlarmBar *groupItem = new AlarmBar();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_ALARMITEM://动态报警条item
            {
                AlarmItem *groupItem = new AlarmItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_HISALARMITEM://动态报警条item
            {
                HisAlarmItem *groupItem = new HisAlarmItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_SWITCH://开关
            {
                SwitchItem *groupItem = new SwitchItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
                        }
        case SAM_DRAW_GROUP_MFBTN://开关
                {
                        MfBtnItem *groupItem = new MfBtnItem();
                        groupItem->load(stream);
                        addToGroup(groupItem);
                        break;
                }
        case SAM_DRAW_GROUP_VALUE:
        case SAM_DRAW_GROUP_TIME:
        case SAM_DRAW_GROUP_ASCII:
            {
                DataDisplayItem *groupItem = new DataDisplayItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_RECIPE:
            {
                QRcipeItem *groupItem = new QRcipeItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_RECIPESHOW:
            {
                QRecipeTableItem *groupItem = new QRecipeTableItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_STATICPIC:
            {
                QStaticPictureItem *groupItem = new QStaticPictureItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_IMAGE:
            {
                ImageItem *groupItem = new ImageItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_ANIMATION:
            {
                AnimationItem *groupItem = new AnimationItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_CHART:
            {
                ChartItem *groupItem = new ChartItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_DYNCIRCLE://动态圆
            {
                DynCircleAttr *groupItem = new DynCircleAttr();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_DYNRECT://动态矩形
            {
                DynRectAttr *groupItem = new DynRectAttr();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_TREND://曲线
            {
                QTrendAttr *groupItem = new QTrendAttr();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_GROUPDATA://数据群组
            {
                QTrendDataGroupAttr *groupItem = new QTrendDataGroupAttr();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_TABLE://表格
            {
                QTableItem *groupItem = new QTableItem();
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_DROPDOWN://下拉框
            {
                QDropdownAttr *groupItem = new QDropdownAttr;
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
        case SAM_DRAW_GROUP_HISTORYDATE://历史数据显示器
            {
                QHistoryDataShowAttr *groupItem = new QHistoryDataShowAttr;
                groupItem->load(stream);
                addToGroup(groupItem);
                break;
            }
                case SAM_DRAW_GROUP_TEXTBOARD://留言板
                        {
                                qMessageBoradAttr *groupItem = new qMessageBoradAttr;
                                groupItem->load(stream);
                                addToGroup(groupItem);
                                break;
                        }
                case SAM_DRAW_GROUP_COMBOBOX://留言板
                        {
                                AkComboItem *groupItem = new AkComboItem;
                                groupItem->load(stream);
                                addToGroup(groupItem);
                                break;
                        }
        default:
            break;
        }
    }

    int typeKey = 0;
    QString name ;
    stream >> typeKey;
    stream >> name;
    setData(GROUP_TYPE_KEY,typeKey);
    setData(GROUP_NAME_KEY,QVariant(name));
    if(0 <= typeKey && typeKey < 200)
    {
        if(typeKey == GROUP_TYPE_STATICPIC || typeKey == GROUP_TYPE_GIFPIC)
        {
            QRectF rc;
            stream >> rc;
    //        stream << sceneBoundingRect().toRect();
        }
    }

    foreach(QGraphicsItem *pItem,childItems())
    {
            pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
            pItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}

QGraphicsItem *QItemGroup::CloneEx()
{
    QGraphicsItem *pCopy = NULL;
    QGraphicsItem * pItem= NULL;

    QItemGroup *itemGroup = new QItemGroup();

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
                QRectBasicItem *rectItem = dynamic_cast<QRectBasicItem *>(pItem);
                if(rectItem)
                {
                    pCopy = rectItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_ELIPSE:              //圆
            {
                QElipseBasicItem *elipseItem = dynamic_cast<QElipseBasicItem *>(pItem);
                if(elipseItem)
                {
                    pCopy = elipseItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_LINE:                 //直线
            {
                QLineBasicItem * lineItem = dynamic_cast<QLineBasicItem *>(pItem);
                if(lineItem)
                {
                    pCopy = lineItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_POLYGON:              //多边形
            {
                QPolygonBasicItem *polygonItem = dynamic_cast<QPolygonBasicItem *>(pItem);
                if(polygonItem)
                {
                    pCopy = polygonItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_FOLDLINE:             //19
            {
                QFoldLineBasicItem *foldlineItem = dynamic_cast<QFoldLineBasicItem *>(pItem);
                if(foldlineItem)
                {
                    pCopy = foldlineItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_FREELINE:             //20
            {
                QFreeLineBasicItem * freelineItem = dynamic_cast<QFreeLineBasicItem *>(pItem);
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
                QLineCircleBasicItem *circleItem = dynamic_cast<QLineCircleBasicItem *>(pItem);
                if(circleItem)
                {
                    pCopy = circleItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_ROUNDEDRECT:
            {
                QRoundedRectBasic *roundedrectItem = dynamic_cast<QRoundedRectBasic *>(pItem);
                if(roundedrectItem)
                {
                    pCopy = roundedrectItem->Clone();
                    itemGroup->addToGroup(pCopy);
                }
                break;
            }
        case SAM_DRAW_OBJECT_ARC:
            {
                QArcBasicItem *arcItem = dynamic_cast<QArcBasicItem *>(pItem);
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
                    qDebug()<<"wxy_test@"<<pItem->data(GROUP_TYPE_KEY).toInt();
                    if(group->GroupType() == SAM_DRAW_GROUP_USER
                       && (pItem->data(GROUP_TYPE_KEY).toInt() != LIBRARY_LIB_GROUP)
                       && (pItem->data(GROUP_TYPE_KEY).toInt() != LIBRARY_PIXMAP_GROUP))
                    {
                        pCopy = group->CloneEx();
                    }
                    else
                    {
                        pCopy = group->Clone();
                    }
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
    if(itemGroup->childItems().size() == 0)
    {
        delete itemGroup;
        itemGroup = NULL;
    }
    return itemGroup;
}
*/
