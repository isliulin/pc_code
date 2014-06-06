#include "qdrawgraphics.h"
#include <QGraphicsItemGroup>
#include <QPainterPath>
#include <QRectF>
#include <QPolygonF>
#include <QVector>
#include <time.h>
#include "qelipseitem.h"
#include "qlineitem.h"
#include "qpolygonitem.h"
#include "qgroupitem.h"
#include <math.h>
#include "Frame/mainwindow.h"
#include "view/qtrendattr.h"
#include "view/qtrenddatagroupattr.h"
#include "Frame/ThingDlg/qtrendappearance.h"
#include "Frame/ThingDlg/qtrendbtable.h"
#include "view/xytrend.h"
extern MainWindow *pwnd;

#include<QDate>

QDrawGraphics::QDrawGraphics()
{
}

/***************************************************************
 *函数名称：OnDrawRectAndText(QGraphicsScene *pScene)
 *函数功能：绘制只有一个状态的图形
 *参数含义：
 *pScene：把画好的图形添加到的场景
 *edit by zqh
 **************************************************************/
QGraphicsItem* QDrawGraphics::OnDrawRectAndText(QGraphicsScene *pScene)
{    
    pGroup = new QItemGroup;//QGraphicsItemGroup;
    int nSpace = 4; //5
    int nWidth = 100-2*nSpace;

    QRectF rect(QPointF(0,0), QSize(100,100));     //绘制边框色矩形框
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(QColor(224,224,224));
    pFramRect->SetLineType(0);
    //  pFramRect->setZValue(1);
    pFramRect->SetName("mFramRect");
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetAlpha(255);

    rect.setTopLeft(QPointF(nSpace,nSpace));       //绘制背景矩形框
    rect.setSize(QSize(nWidth,nWidth));
    QRectItem *pBackRect = new QRectItem(rect);
    pBackRect->SetBackColor(QColor(192,192,192));
    pBackRect->SetLineType(0);
    //  pBackRect->setZValue(2);
    pBackRect->SetName("mBackRect");
    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pBackRect->SetAlpha(255);

    rect.setTopLeft(QPointF(nSpace,nSpace));           //绘制柱
    rect.setSize(QSize(nWidth,nWidth));
    QSimpleTextItem *pText = new QSimpleTextItem(rect,"");
    pText->SetName("mText");
    pText->SetRectOutLine(false);
    // pText->setZValue(4);
    pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pText->SetAlpha(255);

    pGroup->addToGroup(pFramRect);   //添加到组
    pGroup->addToGroup(pBackRect);
    pGroup->addToGroup(pText);

    if(pScene)
        pScene->addItem(pGroup);        //添加到场景

    // QList<QGraphicsItem *> Items = pScene->items();
    // QList<QGraphicsItem *> Item1 = pGroup->childItems();

    pGroup->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->setFlag(QGraphicsItem::ItemIsMovable, false);

    //  QGraphicsItem *pItem = dynamic_cast<QGraphicsItem *>(pGroup);   //把一个组强制转换为QGraphicsItem类型

    return pGroup;
}
QList<QGraphicsItem*> QDrawGraphics::OnDrawRectAndText()
{
    QList<QGraphicsItem*> pGroup;
    int nSpace = 4; //5
    int nWidth = 100-2*nSpace;

    QRectF rect(QPointF(0,0), QSize(100,100));     //绘制边框色矩形框
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(QColor(224,224,224));
    pFramRect->SetLineType(0);
    //  pFramRect->setZValue(1);
    pFramRect->SetName("mFramRect");
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    rect.setTopLeft(QPointF(nSpace,nSpace));       //绘制背景矩形框
    rect.setSize(QSize(nWidth,nWidth));
    QRectItem *pBackRect = new QRectItem(rect);
    pBackRect->SetBackColor(QColor(192,192,192));
    pBackRect->SetLineType(0);
    //  pBackRect->setZValue(2);
    pBackRect->SetName("mBackRect");
    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    rect.setTopLeft(QPointF(nSpace,nSpace));           //绘制柱
    rect.setSize(QSize(nWidth,nWidth));
    QSimpleTextItem *pText = new QSimpleTextItem(rect,"");
    pText->SetName("mText");
    pText->SetRectOutLine(false);
    // pText->setZValue(4);
    pText->setFlag(QGraphicsItem::ItemIsSelectable, false);

    pGroup<<pFramRect;   //添加到组
    pGroup<<pBackRect;
    pGroup<<pText;

    return pGroup;
}

/***************************************************************
 *函数名称：AlterGraphics
 *函数功能：在标示页面加载图片或者调整图片在组合图形中位置
 *参数含义：
 *pOldItem：传过来的需要加载图片的item
 *pictrue： 待加载的图片指针
 *nPicPosition：图片的位置,范围在1-9之间，  
 *ifDeletePic：是否删除图片，true为删除图片，false不删除
   ---(pictrue == NULL && ifDeletePic == true)表示删除图片操作
   ---(pictrue == NULL && ifDeletePic == false)表示调整图片位置操作
 *nBorderInterval:图片的边距
 *ifFit:是否配合物大小
 *edit by zqh
 **************************************************************/
QItemGroup* QDrawGraphics::AlterGraphics(QGraphicsItem *pOldItem, QPixmap *pictrue,
                                         int nPicPosition,int nBorderInterval,bool ifFit,bool ifDeletePic)
{
    QItemGroup *newGroup = new QItemGroup();
    bool IsPictureExist = false;
    int i;
    QList<QGraphicsItem *> itemList = pOldItem->childItems();
    QGraphicsItem * pTmp = NULL;
    QRectF rect;
    for (i = 0;i<itemList.size();i++)
    {
        pTmp = itemList.at(i);
        if (pTmp->data(GROUP_NAME_KEY).toString() == "mBackRect")
        {
            rect = pTmp->sceneBoundingRect();
            break;
        }
    }
    if (pictrue)
    {
        rect = SetPicPosition(pTmp,nPicPosition,nBorderInterval,ifFit,0,rect);

        QSize picSize =QSize(rect.width(),rect.height());
        QPixmapItem* newPicItem = new QPixmapItem(*pictrue,picSize);
        newPicItem->setData(GROUP_NAME_KEY,QVariant("mLibrary"));//设置名字
        newPicItem->setPos(rect.x(),rect.y());
        for(i=0; i<itemList.size();i++)
        {
            if (itemList.at(i)->data(GROUP_NAME_KEY).toString() == "mLibrary")//if (itemList.at(i)->type() == SAM_DRAW_OBJECT_PIXMAP)
            {
                IsPictureExist = true;
                itemList.replace(i,newPicItem);
                break;
            }
        }
        if (!IsPictureExist)
        {
            QList<QGraphicsItem *>::iterator it;
            for (it = itemList.begin(),i=0;i<itemList.size()-1;i++)
            {
                it++;
            }
            itemList.insert(it,newPicItem);
        }
    }
    else
    {
        if(ifDeletePic)
        {
            for(i=0; i<itemList.size();i++)
            {
                if (itemList.at(i)->data(GROUP_NAME_KEY).toString() == "mLibrary")//if (itemList.at(i)->type() == SAM_DRAW_OBJECT_PIXMAP)
                {
                    itemList.removeOne(itemList.at(i));
                }
            }
        }
        else
        {
        }
    }
    foreach (QGraphicsItem * pItem, itemList)
    {
        newGroup->addToGroup(pItem);
    }
    QVariant value;
    value = pOldItem->data(GROUP_NAME_KEY);
    newGroup->setData(GROUP_NAME_KEY,value);
    value = pOldItem->data(GROUP_TYPE_KEY);
    newGroup->setData(GROUP_TYPE_KEY,value);
    return newGroup; 
}

QItemGroup* QDrawGraphics::AlterGraphics(QGraphicsItem *pOldItem,
                                         QPixmap* pictrue,QGraphicsItem *pLibItem,
                                         int nPicPosition, int nBorderInterval,
                                         bool ifFit)
{
    QItemGroup *newGroup = new QItemGroup();
    bool IsPictureExist = false;
    int i;
    QList<QGraphicsItem *> itemList = pOldItem->childItems();
    QGraphicsItem * pTmp = NULL;;
    QGraphicsItem * Item = NULL;
    QGraphicsItem * pNewItem = NULL;
    QRectF rect;
    int nKey = 0;
    DrawItemToScene GroupFunction;

    QGroupItem *pBaseItem = NULL;
    QPixmapItem* newPicItem = NULL;
    QStringList piclist;
    piclist.clear();

    for (i = 0;i<itemList.size();i++)
    {
        pTmp = itemList.at(i);
        if (pTmp->data(GROUP_NAME_KEY).toString() == "mBackRect")
        {
            rect = pTmp->sceneBoundingRect();
            break;
        }
    }
    if (pLibItem)
    {
        rect = SetPicPosition(pTmp,nPicPosition,nBorderInterval,ifFit,0,rect);

        nKey = pLibItem->data(GROUP_TYPE_KEY).toInt();

        if (pLibItem->type() == SAM_DRAW_OBJECT_PIXMAP && nKey != LIBRARY_LIB_GROUP) //是图片
        {
            piclist = pLibItem->data(GROUP_DATALIST_KEY).toStringList();
            QSize picSize =QSize(rect.width(),rect.height());
            newPicItem = new QPixmapItem(*pictrue,picSize);
            pNewItem = newPicItem;
            newPicItem->setPos(rect.x(),rect.y());
            pNewItem->setData(GROUP_DATALIST_KEY,QVariant(piclist));
        }
        else if(nKey == LIBRARY_LIB_GROUP || nKey == USER_DEFINE_GROUP)//图库组合
        {
            if(pLibItem->type() == SAM_DRAW_OBJECT_PIXMAP)
            {
                piclist = pLibItem->data(GROUP_DATALIST_KEY).toStringList();
                QSize picSize =QSize(rect.width(),rect.height());
                QPixmapItem *picItem = dynamic_cast<QPixmapItem *> (pLibItem);
                QPixmap pic = picItem->getPixmap();
                newPicItem = new QPixmapItem(pic,picSize);
                pNewItem = newPicItem;
                newPicItem->setPos(rect.x(),rect.y());
                pNewItem->setData(GROUP_DATALIST_KEY,QVariant(piclist));

            }
            else
            {
                GroupFunction.CopyItem(&Item,pLibItem);
                pBaseItem = new QGroupItem(Item);
                pBaseItem->SetWidth(rect.width());//rect.width()
                pBaseItem->SetHeigth(rect.height());
                QPointF pos = Item->boundingRect().topLeft();
                Item->setPos(rect.topLeft()-pos);

                pNewItem=Item;

            }


            //            QPointF pos = pLibItem->boundingRect().topLeft();
            //            if(ifFit)
            //                pNewItem->setPos(rect.x()-pos.x(),rect.y()-pos.y());
            //            else
            //            {
            //                if(!pictrue)
            //                    pNewItem->setPos(rect.x()-pos.x(),rect.y()-pos.y());
            //                else
            //                    pNewItem->setPos(rect.x(),rect.y());
            //            }

        }

        pNewItem->setData(GROUP_NAME_KEY,QVariant("mLibrary"));//设置名字
        for(i=0; i<itemList.size();i++)
        {
            if (itemList.at(i)->data(GROUP_NAME_KEY).toString() == "mLibrary")
            {
                IsPictureExist = true;
                itemList.replace(i,pNewItem);
                break;
            }
        }
        if (!IsPictureExist)
        {
            QList<QGraphicsItem *>::iterator it;
            for (it = itemList.begin(),i=0;i<itemList.size()-1;i++)
            {
                it++;
            }
            itemList.insert(it,pNewItem);
        }
    }
    else
    {
        for(i=0; i<itemList.size();i++)
        {
            if (itemList.at(i)->data(GROUP_NAME_KEY).toString() == "mLibrary")
            {

                itemList.removeOne(itemList.at(i));
            }

        }
    }
    foreach (QGraphicsItem * pItem, itemList)
    {
        newGroup->addToGroup(pItem);
    }

    QVariant value;
    value = pOldItem->data(GROUP_NAME_KEY);
    newGroup->setData(GROUP_NAME_KEY,value);
    value = pOldItem->data(GROUP_TYPE_KEY);
    newGroup->setData(GROUP_TYPE_KEY,value);
    return newGroup;
}

/***************************************************************
 *函数名称：SetPicPosition
 *函数功能：在标示页面调整图片位置
 *参数含义：
 *pPicItem：传过来的需要加载图片的item
 *nPicPosition：图片的位置,范围在1-9之间，
 *nBorderInterval:图片的边距
 *ifFit:是否配合物大小
 *edit by zqh
 **************************************************************/
QRectF QDrawGraphics::SetPicPosition(QGraphicsItem *pPicItem, int nPicPosition,
                                     int nBorderInterval,bool ifFit,int nSpace,QRectF rect)
{
    if( nPicPosition < 1 || nPicPosition > 9) //位置不在1-9范围之内退出
        return rect;
    if(ifFit)  //选择了配合物大小的时候不处理
        return rect;

    QRectF rc;
    double nWidth = rect.width();
    double nPicWidth = nWidth/2;
    double nX = 0;
    double nY = 0;
    switch(nPicPosition)
    {
    case 1: //左上对齐
        nX = nBorderInterval;
        nY = nBorderInterval;
        break;
    case 2: //上对齐
        nX = (nWidth-nPicWidth)/2;
        nY = nBorderInterval;
        break;
    case 3: //右上对齐
        nX = nWidth -nPicWidth-nBorderInterval;
        nY = nBorderInterval;
        break;
    case 4: //左对齐
        nX = nBorderInterval;
        nY = (nWidth-nPicWidth)/2;
        break;
    case 5: //居中对齐
        nX = (nWidth-nPicWidth)/2;
        nY = (nWidth-nPicWidth)/2;
        break;
    case 6: //右对齐
        nX = nWidth -nPicWidth-nBorderInterval;
        nY = (nWidth-nPicWidth)/2;
        break;
    case 7: //左下角对齐
        nX = nBorderInterval;
        nY = nWidth -nPicWidth-nBorderInterval;
        break;
    case 8: //底部对齐
        nX = (nWidth-nPicWidth)/2;
        nY = nWidth -nPicWidth-nBorderInterval;
        break;
    case 9: //右下角对齐
        nX = nWidth -nPicWidth-nBorderInterval;
        nY = nWidth -nPicWidth-nBorderInterval;
        break;
    }

    if(nX > (nWidth - nPicWidth) )
        nX = (nWidth - nPicWidth);
    if(nY > (nWidth - nPicWidth))
        nY = (nWidth - nPicWidth);
    rc = QRectF(nX+rect.x(),nY+rect.y(),rect.width()/2,rect.height()/2);
    return rc;  
}

/****************************************************************************
 *函数名称：OnDrawMeter(QGraphicsScene *pScene,int nPointerType,int nDirection)
 *函数功能：绘制仪表图形
 *参数含义：
 *pScene：把画好的图形添加到的场景
 *nMeterType:加载仪表类型，0--半圆，1--全圆指针向上，2--全圆指针向下，3--四分之三圆指针向上
 *nPointerType:指针类型；0--细直线，1--粗直线，2--菱形，3--三角形
 *nDirection：方向；0--顺时针，1--逆时针
 *nMainScal:  主刻度
 *nSubScal:   次刻度
 *dMax:       最大值
 *dMin:       最小值
 *nPointCount:小数点位数
 *nFontSize:  字体大小
 *edit by zqh
 ****************************************************************************/
QGraphicsItem* QDrawGraphics::OnDrawMeter(QGraphicsScene *pScene,int nMeterType,
                                          int nPointerType,int nDirection,int nMainScal,int nSubScal,
                                          double dMax, double dMin, int nPointCount,int nFontSize)
{
    int nWidth = 100;      //圆的宽度
    int nHeight = 100;     //圆的高度

    pGroup = new QItemGroup;
    //pGroup = new QGraphicsItemGroup;

    QRectF mRect(QPoint(0,0),QSize(nWidth,nHeight));    //设置大小
    QElipseItem *pCircle = new QElipseItem(mRect);      //绘制一个圆
    pCircle->SetName("mMeterCircle");                   //设置圆的名称

    switch(nMeterType)
    {
    case 0:  //半圆仪表
        pCircle->SetStartAngle(0);                  //设置开始角度
        pCircle->SetSpanAngle(180);                 //设置跨度,绘制一个半圆
        break;
    case 1:  //全圆指针向上
    case 2:  //全圆指针向下
        break;
    case 3:  //四分之三圆指针向上
        pCircle->SetStartAngle(315);               //设置开始角度
        pCircle->SetSpanAngle(270);                //设置跨度,绘制一个四分之三圆
        break;
    default:
        break;
    }
    pCircle->SetBackColor(QColor(0,255,255));           //设置背景色
    pCircle->setZValue(1);                              //设置层次

    QRectF mBaseRect(QPoint(nWidth/2-2,nHeight/2-2),QSize(4,4)); //设置针座大小
    QElipseItem *pBaseCircle = new QElipseItem(mBaseRect);//绘制针座
    pBaseCircle->SetBackColor(QColor(0,0,0));             //设置针座颜色
    pBaseCircle->setZValue(2);                            //设置针座的层次
    pBaseCircle->SetLineType(0);                          //设置线条样式为透明
    pBaseCircle->SetName("mPointerBase");                 //设置针座名称
    pGroup->addToGroup(pBaseCircle);                      //添加到组

    pGroup->addToGroup(pCircle);              //添加到组
    OnDrawPointer(nPointerType,nMeterType);   //画指针函数
    OnDrawScal(nMeterType,nDirection,nMainScal,nSubScal,dMax,dMin,nPointCount,nFontSize);              //画刻度和文本

    pScene->addItem(pGroup);
    // QGraphicsItem *pItem = dynamic_cast<QGraphicsItem *>(pGroup);   //把一个组强制转换为QGraphicsItem类型
    return pGroup;
}
/****************************************************************************
 *函数名称：OnDrawPointer(int nPointerType)
 *函数功能：绘制仪表指针类型
 *参数含义：
 *nMeterType:加载仪表类型，0--半圆，1--全圆指针向上，2--全圆指针向下，3--四分之三圆指针向上
 *nPointerType:指针类型；0--细直线，1--粗直线，2--菱形，3--三角形
 *edit by zqh
 ****************************************************************************/
void QDrawGraphics::OnDrawPointer(int nPointerType,int nMeterType)
{
    int nWidth = 100;             //圆的宽度
    int nHeight = 100;            //圆的高度
    int nPointerTop = 5;          //指针的top坐标
    QPainterPath mPath;           //生成线的path
    QVector <QPoint>mAngle;
    QPoint p1,p2,p3,p4;

    if(nPointerType == 0)      //细直线
    {
        if(nMeterType != 2) //指针向上
        {
            mPath.moveTo(nWidth/2,nPointerTop);           //画直线的起点
            mPath.lineTo(nWidth/2,nHeight/2);             //画直线的终点
        }
        else
        {
            mPath.moveTo(nWidth/2,nHeight/2);             //画直线的起点
            mPath.lineTo(nWidth/2,nHeight-nPointerTop);   //画直线的终点
        }
        QLineItem *pLinePointer = new QLineItem(mPath);   //画细直线指针
        pLinePointer->setLineColor(QColor(255,0,0));      //设置直线颜色
        pLinePointer->setZValue(3);                       //设置层次
        pLinePointer->SetName("Pointer");                 //设置名称
        pGroup->addToGroup(pLinePointer);
    }
    else if(nPointerType == 1) //粗直线
    {
        if(nMeterType != 2) //指针向上
        {
            mPath.moveTo(nWidth/2,nPointerTop);           //画直线的起点
            mPath.lineTo(nWidth/2,nHeight/2);             //画直线的终点
        }
        else
        {
            mPath.moveTo(nWidth/2,nHeight/2);             //画直线的起点
            mPath.lineTo(nWidth/2,nHeight-nPointerTop);   //画直线的终点
        }
        QLineItem *pLinePointer = new QLineItem(mPath);   //画粗直线指针
        pLinePointer->setLineWidth(3);                    //设置粗直线指针
        pLinePointer->setLineColor(QColor(255,0,0));      //设置直线颜色
        pLinePointer->setZValue(3);                       //设置层次
        pLinePointer->SetName("Pointer");                 //设置名称
        pGroup->addToGroup(pLinePointer);
    }
    else if(nPointerType == 2) //菱形
    {
        if(nMeterType != 2) //指针向上
        {
            p1.setX(nWidth/2);
            p1.setY(nHeight/2);

            p2.setX(nWidth/2-5);
            p2.setY(nHeight/2-10);

            p3.setX(nWidth/2);
            p3.setY(nPointerTop);

            p4.setX(nWidth/2+5);
            p4.setY(nHeight/2-10);
        }
        else
        {
            p1.setX(nWidth/2);
            p1.setY(nHeight/2);

            p2.setX(nWidth/2-5);
            p2.setY(nHeight/2+10);

            p3.setX(nWidth/2);
            p3.setY(nHeight -nPointerTop );

            p4.setX(nWidth/2+5);
            p4.setY(nHeight/2+10);
        }

        mAngle.append(p1);
        mAngle.append(p2);
        mAngle.append(p3);
        mAngle.append(p4);
        QPolygonF mAnglePoly(mAngle);
        QPolygonItem *pPolyPointer = new QPolygonItem(mAnglePoly);   //画菱形指针
        pPolyPointer->setLineType(0);
        pPolyPointer->setBackColor(QColor(255,0,0));
        pPolyPointer->setZValue(3);                       //设置层次
        pPolyPointer->SetName("Pointer");                 //设置名称
        pGroup->addToGroup(pPolyPointer);
    }
    else if(nPointerType == 3) //三角形
    {

        if(nMeterType != 2) //指针向上
        {
            p1.setX(nWidth/2-3);
            p1.setY(nHeight/2);

            p2.setX(nWidth/2);
            p2.setY(nPointerTop);

            p3.setX(nWidth/2+3);
            p3.setY(nHeight/2);
        }
        else
        {
            p1.setX(nWidth/2-3);
            p1.setY(nHeight/2);

            p2.setX(nWidth/2);
            p2.setY(nHeight-nPointerTop);

            p3.setX(nWidth/2+3);
            p3.setY(nHeight/2);
        }

        mAngle.append(p1);
        mAngle.append(p2);
        mAngle.append(p3);
        QPolygonF mAnglePoly(mAngle);
        QPolygonItem *pPolyPointer = new QPolygonItem(mAnglePoly);   //画三角形指针
        pPolyPointer->setLineType(0);
        pPolyPointer->setBackColor(QColor(255,0,0));
        pPolyPointer->setZValue(3);                       //设置层次
        pPolyPointer->SetName("Pointer");                 //设置名称
        pGroup->addToGroup(pPolyPointer);
    }
}

/****************************************************************************
 *函数名称：OnDrawScal
 *函数功能：绘制仪表的刻度和文本
 *参数含义：
 *nMeterType: 加载仪表类型，0--半圆，1--全圆指针向上，2--全圆指针向下，3--四分之三圆指针向上
 *nDirection: 方向，0--顺时针，1--逆时针
 *nMainScal:  主刻度
 *nSubScal:   次刻度
 *dMax:       最大值
 *dMin:       最小值
 *nPointCount:小数点位数
 *nFontSize:  字体大小
 *edit by zqh
 ****************************************************************************/
void QDrawGraphics::OnDrawScal(int nMeterType, int nDirection, int nMainScal,
                               int nSubScal, double dMax, double dMin, int nPointCount,
                               int nFontSize)
{
    QLineItem *pLineScal;
    int nWidth = 100;                 //圆的宽度
    int nHeight = 100;                //圆的高度
    double mMoveX = 0;                //主刻度X起始点
    double mMoveY = 0;                //主刻度Y起始点
    double mLineX = 0;                //主刻度X起始点
    double mLineY = 0;                //主刻度Y起始点
    double mMainAngle = 0;            //主刻度偏转角度， 弧度制
    double mSubAngle = 0;             //次刻度偏转角度， 弧度制
    double mTextAngle = 0;            //文本偏转角度,   角度制
    double mConst = 3.1415926;        //常量
    int nMainScaleL = 6;              //主刻度的长度
    int nSubScaleL = nMainScaleL / 2; //次刻度长度
    int nSunLineCount = 0;            //次刻度线总数
    int nDrawMainScal = nMainScal;    //主刻度数
    double mValue = 0;                //
    double dVal = 0;
 //   int nIndex = 0;                   //小数点的下标
    QString sText = "";
//    QString sLeft = "";
//    QString sRight = "";
    int i = 0;
    QString sName = "";
    QRectF rect(QPointF(0,0), QSize(50,50));

    mValue = (dMax - dMin) / (nMainScal - 1);
    switch(nMeterType)
    {
    case 0: //半圆方向向上
        mMainAngle = mConst / (nMainScal - 1);
        mSubAngle = mConst / (nSubScal*(nMainScal - 1));
        mTextAngle = 180.0 /(nMainScal - 1);
        break;
    case 1: //全圆方向向上
    case 2: //全圆方向向下
        mMainAngle = 2*mConst / (nMainScal - 1);
        mSubAngle = 2*mConst / (nSubScal*(nMainScal - 1));
        mTextAngle = 360.0 /(nMainScal - 1);
        nDrawMainScal --;
        break;
    case 3: //四分之三圆方向向上
        mMainAngle = 1.5*mConst / (nMainScal - 1);
        mSubAngle = 1.5*mConst / (nSubScal*(nMainScal - 1));
        mTextAngle = 270.0 /(nMainScal - 1);
        break;
    default:
        return;
    }

    for(i = 0; i < nDrawMainScal; i++)  //画主刻度nMainScal
    {   
        switch(nMeterType)
        {
        case 0: //半圆方向向上
            mMoveX = nWidth/2 - nWidth/2 * cos(mMainAngle*i);
            mMoveY = nWidth/2 - nWidth/2 * sin(mMainAngle*i);

            mLineX = nWidth/2 - (nWidth/2+nMainScaleL)*cos(mMainAngle*i);
            mLineY = nHeight/2 - (nWidth/2+nMainScaleL)*sin(mMainAngle*i);
            break;
        case 1: //全圆方向向上
            mMoveX = nWidth/2 + nWidth/2 * sin(mMainAngle*i);
            mMoveY = nHeight/2 - nWidth/2 * cos(mMainAngle*i);

            mLineX = nWidth/2 + (nWidth/2+nMainScaleL)*sin(mMainAngle*i);
            mLineY = nHeight/2 - (nWidth/2+nMainScaleL)*cos(mMainAngle*i);
            break;
        case 2: //全圆方向向下
            mMoveX = nWidth/2 - nWidth/2 * sin(mMainAngle*i);
            mMoveY = nHeight/2 + nWidth/2 * cos(mMainAngle*i);

            mLineX = nWidth/2 - (nWidth/2+nMainScaleL)*sin(mMainAngle*i);
            mLineY = nHeight/2 + (nWidth/2+nMainScaleL)*cos(mMainAngle*i);
            break;
        case 3: //四分之三圆方向向上
            mMoveX = nWidth/2 - nWidth/2 * sin(mMainAngle*i+mConst/4);
            mMoveY = nHeight/2 + nWidth/2 * cos(mMainAngle*i+mConst/4);

            mLineX = nWidth/2 - (nWidth/2+nMainScaleL)*sin(mMainAngle*i+mConst/4);
            mLineY = nHeight/2 + (nWidth/2+nMainScaleL)*cos(mMainAngle*i+mConst/4);
            break;
        default:
            return;
        }

        QPainterPath mPath;
        mPath.moveTo(mMoveX,mMoveY);             //画直线的起点
        mPath.lineTo(mLineX,mLineY);             //画直线的终点
        pLineScal = new QLineItem(mPath);        //画细直线
        pLineScal->setLineColor(QColor(255,0,0));  //设置直线颜色
        pLineScal->setZValue(4);                 //设置层次

        sName = QString("%1").arg(i);
        sName = "MainLineScal"+sName;
        pLineScal->SetName(sName);               //设置名称
        pGroup->addToGroup(pLineScal);           //添加到组

        /************************************************
         *以下是画文本
         ***********************************************/
        if(nDirection == 0)     //顺时针
            dVal = dMin + i*mValue;
        else if(nDirection == 1)//逆时针
        {
            dVal = dMax - i*mValue;
            if((nMeterType == 1 || nMeterType == 2) && i == 0)
                dVal = dMin;
            if((i == nDrawMainScal - 1) && (nMeterType == 0 || nMeterType == 3))
                dVal = dMin;
        }

        if(dVal == -0)
            dVal = 0;
        sText.sprintf("%.0f", dVal);
        QString sTemp = "";
        if(nPointCount != 0)
        {
            sTemp = sText.left(1);
            if(sTemp == "-") //是负数的时候
            {
                sTemp = sText.right(sText.length()-1); //取除去负号的数据
                while(sTemp.length()-nPointCount <= 0)
                      sTemp = "0"+sTemp;
                  sTemp = sTemp.insert(sTemp.length()-nPointCount,".");
                  sText = "-"+sTemp;
            }
            else
            {
                   while(sText.length()-nPointCount <= 0)
                         sText = "0"+sText;
                     sText = sText.insert(sText.length()-nPointCount,".");
            }
        }
//        if(nPointCount != 0)
//        {
//            while(sText.length()-nPointCount <= 0)
//                sText = "0"+sText;
//            sText = sText.insert(sText.length()-nPointCount,".");
//        }
//        sText = QString("%1").arg(dVal);
//        nIndex = sText.indexOf(".");   //查找小数点的位置
//        if(nIndex > 0) //有小数点
//        {
//            sLeft = sText.mid(0,nIndex);             //取小数点之前的数据
//            sRight = sText.mid(nIndex+1,nPointCount);//取小数点之后的数据
//            if(nPointCount == 0)
//                sText = sLeft;
//            else
//                sText = sLeft +"."+sRight;               //最终数据
//        }


        rect.setTopLeft(QPointF(0,0));           //绘制柱mLineX,mLineY
        rect.setSize(QSize(nWidth,nWidth));
        QSimpleTextItem *pText = new QSimpleTextItem(rect,sText);

        pText->SetFontSize(nFontSize);
        QFont nfont = pText->GetTextFont(); //设置文本外框的大小
        nfont.setPointSize(nFontSize);
        QFontMetrics fontM(nfont);
        QRect rc = fontM.boundingRect(sText);

        rect.setSize(QSize(rc.width()+5,rc.height()));

        if(mTextAngle*i >= 0 && mTextAngle*i < 45)
        {
            switch(nMeterType)
            {
            case 0:
                mLineX = mLineX - rc.width()-4;
                mLineY = mLineY - rc.height()/2;
                break;
            case 1: //全圆向上
                mLineX = mLineX - rc.width()/2-1;
                mLineY = mLineY -rc.height();
                break;
            case 2: //全圆向下
                mLineX = mLineX - rc.width()/2;
                mLineY = mLineY + 1;
                break;
            case 3: //四分之三圆方向向上
                mLineX = mLineX - rc.width()-4;
                mLineY = mLineY - rc.height()/2;
                break;
            }
        }
        else if(mTextAngle*i >= 45 && mTextAngle*i < 135)
        {
            switch(nMeterType)
            {
            case 0:
                mLineX = mLineX - rc.width()/2-3;
                mLineY = mLineY - rc.height();
                break;
            case 1: //全圆向上
                mLineX = mLineX + 1;
                mLineY = mLineY -rc.height()/2;
                break;
            case 2: //全圆向下
                mLineX = mLineX - rc.width()-4;
                mLineY = mLineY - rc.height()/2;
                break;
            case 3: //四分之三圆方向向上
                if(mTextAngle*i >= 45 && mTextAngle*i < 90)
                {
                    mLineX = mLineX - rc.width()-4;
                    mLineY = mLineY - rc.height()/2;
                }
                else
                {
                    mLineX = mLineX - rc.width()/2-4;
                    mLineY = mLineY - rc.height();
                }
                break;
            }
        }
        else if(mTextAngle*i >= 135 && mTextAngle*i < 225)
        {
            switch(nMeterType)
            {
            case 0:
                mLineX = mLineX + 1;
                mLineY = mLineY -rc.height()/2;
                break;
            case 1: //全圆向上
                mLineX = mLineX - rc.width()/2;
                mLineY = mLineY + 1;
                break;
            case 2: //全圆向下
                mLineX = mLineX - rc.width()/2;
                mLineY = mLineY - rc.height();
                break;
            case 3: //四分之三圆方向向上
                if(mTextAngle*i >= 135 && mTextAngle*i < 180)
                {
                    mLineX = mLineX - rc.width()/2;
                    mLineY = mLineY -rc.height();
                }
                else
                {
                    mLineX = mLineX + 1;
                    mLineY = mLineY -rc.height()/2;
                }
                break;
            }
        }
        else if(mTextAngle*i >= 225 && mTextAngle*i < 315)
        {
            switch(nMeterType)
            {
            case 0:
                break;
            case 1: //全圆向上
                mLineX = mLineX - rc.width()-4;
                mLineY = mLineY - rc.height()/2;
                break;
            case 2: //全圆向下
                mLineX = mLineX + 1;
                mLineY = mLineY -rc.height()/2;
                break;
            case 3: //四分之三圆方向向上
                mLineX = mLineX + 1;
                mLineY = mLineY -rc.height()/2;
                break;
            }

        }
        else
        {
            switch(nMeterType)
            {
            case 0:
                break;
            case 1: //全圆向上
                mLineX = mLineX - rc.width()/2;
                mLineY = mLineY - rc.height();
                break;
            case 2: //全圆向下
                mLineX = mLineX - rc.width()/2;
                mLineY = mLineY +1;
                break;
            }
        }

        pText->setRect(rect);
        pText->setPos(mLineX,mLineY);
        pText->SetFontColor(QColor(255,0,0));
        sName = QString("%1").arg(i);
        sName = "MeterTxt"+sName;
        pText->SetName(sName);
        pText->SetRectOutLine(false);
        pText->setZValue(4);

        pGroup->addToGroup(pText);           //添加到组

        /***********************画文本完毕**************************/
    }

    nSunLineCount = nSubScal*(nMainScal - 1);//次刻度线总数
    for(i = 0; i < nSunLineCount; i++)  //画次刻度
    {
        if( i%nSubScal != 0)
        {
            switch(nMeterType)
            {
            case 0: //半圆方向向上
                mMoveX = nWidth/2 - nWidth/2 * cos(mSubAngle*i);
                mMoveY = nWidth/2 - nWidth/2 * sin(mSubAngle*i);

                mLineX = nWidth/2 - (nWidth/2+nSubScaleL)*cos(mSubAngle*i);
                mLineY = nHeight/2 - (nWidth/2+nSubScaleL)*sin(mSubAngle*i);
                break;
            case 1: //全圆方向向上
                mMoveX = nWidth/2 + nWidth/2 * sin(mSubAngle*i);
                mMoveY = nWidth/2 - nWidth/2 * cos(mSubAngle*i);

                mLineX = nWidth/2 + (nWidth/2+nSubScaleL)*sin(mSubAngle*i);
                mLineY = nHeight/2 - (nWidth/2+nSubScaleL)*cos(mSubAngle*i);
                break;
            case 2: //全圆方向向下

                mMoveX = nWidth/2 - nWidth/2 * sin(mSubAngle*i);
                mMoveY = nWidth/2 + nWidth/2 * cos(mSubAngle*i);

                mLineX = nWidth/2 - (nWidth/2+nSubScaleL)*sin(mSubAngle*i);
                mLineY = nHeight/2 + (nWidth/2+nSubScaleL)*cos(mSubAngle*i);
                break;
            case 3: //四分之三圆方向向上
                mMoveX = nWidth/2 - nWidth/2 * sin(mSubAngle*i+mConst/4);
                mMoveY = nWidth/2 + nWidth/2 * cos(mSubAngle*i+mConst/4);

                mLineX = nWidth/2 - (nWidth/2+nSubScaleL)*sin(mSubAngle*i+mConst/4);
                mLineY = nHeight/2 + (nWidth/2+nSubScaleL)*cos(mSubAngle*i+mConst/4);
                break;
            default:
                return;
            }

            QPainterPath mPath;
            mPath.moveTo(mMoveX,mMoveY);             //画直线的起点
            mPath.lineTo(mLineX,mLineY);             //画直线的终点
            pLineScal = new QLineItem(mPath);        //画细直线
            pLineScal->setLineColor(QColor(255,0,0));  //设置直线颜色
            pLineScal->setZValue(4);                 //设置层次

            sName = QString("%1").arg(i);
            sName = "SubLineScal"+sName;
            pLineScal->SetName(sName);               //设置名称

            pGroup->addToGroup(pLineScal);
        }
    }
}


/****************************************************************************
 *函数名称：OnDrawMeter(QGraphicsScene *pScene,int nPointerType,int nDirection)
 *函数功能：绘制仪表图形
 *参数含义：
 *pScene：把画好的图形添加到的场景
 *nMeterType:加载仪表类型，0--半圆，1--全圆指针向上，2--全圆指针向下，3--四分之三圆指针向上
 *nDirection：方向；0--顺时针，1--逆时针
 *nMainScal:  主刻度
 *nSubScal:   次刻度
 *dMax:       最大值
 *dMin:       最小值
 *nPointCount:小数点位数
 *nFontSize:  字体大小
 *edit by zqh
 ****************************************************************************/
QGraphicsItem* QDrawGraphics::OnDrawPie(QGraphicsScene *pScene, int nMeterType,
                                        int nDirection, int nMainScal, int nSubScal, double dMax,
                                        double dMin, int nPointCount, int nFontSize)
{
    int nWidth = 100;      //圆的宽度
    int nHeight = 100;     //圆的高度

    pGroup = new QItemGroup;

    QRectF mRect(QPoint(0,0),QSize(nWidth,nHeight));       //设置大小
    QElipseItem *pBaseCircle = new QElipseItem(mRect);     //绘制一个底圆
    pBaseCircle->SetName("mBaseCircle");                   //设置圆的名称
    pBaseCircle->SetBackColor(QColor(224,224,224));        //设置背景色
    pBaseCircle->SetLineType(0);
    pBaseCircle->setZValue(1);                             //设置层次

    QElipseItem *pPieCircle = new QElipseItem(mRect);      //绘制一个饼图
    pPieCircle->SetName("mPieCircle");                     //设置圆的名称
    pPieCircle->SetBackColor(QColor(255,0,0));             //设置背景色
    pPieCircle->setZValue(2);

    mRect.setTopLeft(QPointF(10,10));
    mRect.setSize(QSize(80,80));
    QElipseItem *pCircle = new QElipseItem(mRect);         //绘制一个圆心图
    pCircle->SetName("mCircle");                           //设置圆的名称
    pCircle->SetLineType(0);
    pCircle->SetBackColor(QColor(255,255,255));                //设置背景色
    pCircle->setZValue(3);

    switch(nMeterType)
    {
    case 0:  //半圆仪表
        pBaseCircle->SetStartAngle(0);                 //设置开始角度
        pBaseCircle->SetSpanAngle(180);                //设置跨度,绘制一个半圆

        pPieCircle->SetStartAngle(0);                  //设置开始角度
        pPieCircle->SetSpanAngle(90);                  //设置跨度,绘制一个半圆

        pCircle->SetStartAngle(0);                     //设置开始角度
        pCircle->SetSpanAngle(180);                    //设置跨度,绘制一个半圆
        break;
    case 1:  //全圆指针向上
    case 2:  //全圆指针向下
        pPieCircle->SetStartAngle(0);                  //设置开始角度
        pPieCircle->SetSpanAngle(180);                 //设置跨度,绘制一个半圆
        break;
    case 3:  //四分之三圆指针向上
        pBaseCircle->SetStartAngle(315);               //设置开始角度
        pBaseCircle->SetSpanAngle(270);                //设置跨度,绘制一个四分之三圆

        pPieCircle->SetStartAngle(315);                //设置开始角度
        pPieCircle->SetSpanAngle(135);                 //设置跨度,绘制一个半圆

        pCircle->SetStartAngle(315);                   //设置开始角度
        pCircle->SetSpanAngle(270);                    //设置跨度,绘制一个半圆
        break;
    default:
        break;
    }

    pGroup->addToGroup(pBaseCircle);              //添加到组
    pGroup->addToGroup(pPieCircle);               //添加到组
    pGroup->addToGroup(pCircle);                  //添加到组
    OnDrawScal(nMeterType,nDirection,nMainScal,nSubScal,dMax,dMin,nPointCount,nFontSize);              //画刻度和文本

    pScene->addItem(pGroup);
    return pGroup;
}

QItemGroup* QDrawGraphics::OnAddPicture(QGraphicsItem *pOldItem, QPixmap *pictrue,
                                        int nPicPosition, int nBorderInterval, bool ifFit,
                                        bool ifDeletePic)
{
    QRectF rect = pOldItem->sceneBoundingRect();
    QItemGroup *newGroup = new QItemGroup();
    bool IsPictureExist = false;
    QPixmap newPic;
    int nSpace = 0;
    int i;

    QList<QGraphicsItem *> itemList = pOldItem->childItems();

    if (pictrue)   //有图片加入
    {
        if(ifFit)
            newPic = (*pictrue).scaled(100,100); //配合物大小92
        else
            newPic = (*pictrue).scaled(50,50); //不是配合物大小46

        QPixmapItem* newPicItem = new QPixmapItem(newPic,newPic.size());
        newPicItem->setZValue(2);          //设置层次
        newPicItem->setPos(nSpace,nSpace); //设置初始位置

        for(i=0; i<itemList.size();i++) //组合中有图片
        {
            if (itemList.at(i)->type() == SAM_DRAW_OBJECT_PIXMAP)
            {
                IsPictureExist = true;
                itemList.replace(i,newPicItem);
                SetPicPosition(newPicItem,nPicPosition,nBorderInterval,ifFit,0,rect); //调整图片的位置
                break;
            }
        }
        if (!IsPictureExist)            //组合中没有图片
        {
            itemList.insert(1,newPicItem);
            SetPicPosition(newPicItem,nPicPosition,nBorderInterval,ifFit,0,rect); //调整图片的位置
        }
    }
    else      //没有图片加入，判断是删除图片还是调整图片的位置
    {
        for(i=0; i<itemList.size();i++)
        {
            if (itemList.at(i)->type() == SAM_DRAW_OBJECT_PIXMAP)
            {
                if(ifDeletePic) //表示是删除图片
                    itemList.removeOne(itemList.at(i));
                else            //调整图片的位置
                    SetPicPosition(itemList.at(i),nPicPosition,nBorderInterval,ifFit,0,rect);
            }
        }
    }

    foreach (QGraphicsItem * pItem, itemList)
    {
        newGroup->addToGroup(pItem);
    }
    return newGroup;
}

/***************************************************************
 *函数名称：OnDrawTrendChart
 *函数功能：画趋势图、XY趋势图以及历史趋势图函数
 *参数含义：
 *edit by czq
 **************************************************************/
void QDrawGraphics::OnDrawTrendChart(QTrendAttr *pItem)
{
    if(!pItem)
    {
        return;
    }

    QString sText = "";
    int nFontSizeX = pItem->m_nFontSize;       //字体大小
    int nFontSizeY = pItem->m_nFontSize;       //字体大小

    //X轴
    int nXmain  = pItem->m_nHorMajorScale; //主刻度
    int nXsub   = pItem->m_nHorMinorScale; //次刻度

    //Y轴
    int nYmain  = pItem->m_nVertMajorScale; //主刻度
    int nYsub   = pItem->m_nVertMinorScale; //次刻度

    double m_nDisplayMax = pItem->m_nDisplayMax;
    double m_nDisplayMin = pItem->m_nDisplayMin;

    QDateTime tStart;
    QDateTime tEnd;

    getDateTime(pItem,tStart,tEnd);
    //以下是画图所需的变量
    int         nTopSpace   = 20;                           //画底色框距离背景框的上坐标偏移量
    int         nLeftSpace  = 60;//80;                      //画底色框距离背景框的左坐标偏移量,这个长度需要一种算法来计算
    double      nBGW        = 400-nLeftSpace-nLeftSpace/2;  //底色矩形的宽度
    double      nBGH        = 250-nTopSpace-2*nTopSpace;    //底色矩形的高度
    if(!pItem->m_bMainVer && !pItem->m_bMainHor)//没有水平-没有垂直
    {
        nTopSpace   = 0;
        nLeftSpace  = 0;
        nBGW = 400;
        nBGH = 250;
    }
    else if(!pItem->m_bMainVer && pItem->m_bMainHor)//有水平-没有垂直
    {
        nTopSpace   = 0;
        nLeftSpace  = 30;
        nBGW = 340;
        nBGH = 250;
    }
    else if(pItem->m_bMainVer && !pItem->m_bMainHor)//有水平-没有垂直
    {
        nTopSpace   = 20;
        nLeftSpace  = 0;
        nBGW = 400;
        nBGH = 210;
    }

    int         ML          = 10;                           //刻度长度
    int         nVal        = nXsub*nXmain;                 //次刻度总数
    double      mMoveX      = 0;                            //主刻度X起始点
    double      mMoveY      = 0;                            //主刻度Y起始点
    double      mLineX      = 0;                            //主刻度X起始点
    double      mLineY      = 0;                            //主刻度Y起始点
    double      MainSpace   = nBGW/nXmain;                  //主刻度间隔
    double      SubSpace    = nBGW/(nXsub*nXmain);          //次刻度间隔
    QRectItem*  pBackRect;                                  //背景矩形框
    QRectItem*  pBGRect;                                    //底色矩形框
    QLineItem*  pLine;
    QLineItem*  pXLine;
    QSimpleTextItem *pText;

    //----------------------开始画背景矩形------------------------
    QRectF rect(QPointF(0,0), QSize(400,250));     //背景矩形框480,250
    //pBackRect = new QRectItem(rect);
    //pBackRect->SetBackColor(pItem->m_nBoradColor);
    //pBackRect->SetLineType(0);
    //pBackRect->SetAlpha(100);
    //pBackRect->SetName(pItem->m_nBoradColor.name());
    //pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    //pItem->addToGroup(pBackRect);
    //pBackRect->SetAlpha(255);

    //--------------------开始画图表区底色矩形--------------------
    rect.setTopLeft(QPoint(nLeftSpace,nTopSpace));
    rect.setSize(QSizeF(nBGW,nBGH));
    pBGRect = new QRectItem(rect);
    pBGRect->SetBackColor(pItem->m_nGraphColor);
    pBGRect->SetLineColor(pItem->m_nBoradColor);
    pBGRect->SetAlpha(pItem->m_alpha);
    pBGRect->SetName("backRect");
    pBGRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pItem->addToGroup(pBGRect);

    //--------------------开始画X轴刻度--------------------
    //if(pItem->m_bMainHor)
    {
        for(int i = 0; i <= nXmain; i++)
        {
            QPainterPath mPath;//生成线的path

            if(pItem->m_bMainHor)
            {
                //画主刻度
                mMoveX = i * MainSpace + nLeftSpace;
                mMoveY = nTopSpace + nBGH;
                mLineX = i * MainSpace + nLeftSpace;
                mLineY = nTopSpace + nBGH + ML;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineType(1);          //字体类型
                pLine->setLineColor(pItem->m_nScaleColor); //主刻度颜色
                pLine->SetName(QString("XMainScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //画主格线
            if(pItem->m_bGrade)//是否显示格线
            {
                if(i != 0 && i != nXmain)
                {
                    QPainterPath mPath1;               //生成线的path
                    mMoveX = i * MainSpace + nLeftSpace;
                    mMoveY = nTopSpace;
                    mLineX = i * MainSpace + nLeftSpace;
                    mLineY = nTopSpace + nBGH;
                    mPath1.moveTo(mMoveX,mMoveY);
                    mPath1.lineTo(mLineX,mLineY);
                    pXLine = new QLineItem(mPath1);
                    pXLine->setLineType(1); //设置
                    pXLine->setLineColor(pItem->m_nVerColor); //格线颜色
                    pXLine->SetName(QString("XMainLine%1").arg(i));
                    pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->addToGroup(pXLine);
                }
            }

            if(pItem->m_bMainHor)
            {
                //是否显示文本
                if(pItem->m_bXMarked)
                {
                    mLineX  = i * MainSpace + nLeftSpace;
                    mLineY  = nTopSpace + nBGH + ML;

                    //画时间文本
                    if(pItem->m_bTimeFormat)
                    {
                        sText   = GetTimeText(tStart, tEnd, nXmain, i, pItem->m_eTimeFormat -1,1);

                        pText   = new QSimpleTextItem(rect,sText);
                        pText   = DrawTrendText(pText, i, mLineX, mLineY, sText, nFontSizeX, pItem->m_nMarkedColor,0);
                        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
                        pItem->addToGroup(pText);
                    }

                    //画日期文本
                    if((pItem->m_eTableType == TypeHistory) && (pItem->m_bDateFormat))
                    {
                        sText   = GetTimeText(tStart, tEnd, nXmain, i, pItem->m_eDateFormat -1,2);

                        pText   = new QSimpleTextItem(rect,sText);
                        pText   = drawHisTrendDate(i, mLineX, mLineY, sText, nFontSizeX, pItem->m_nMarkedColor, pItem->m_bTimeFormat);
                        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
                        pItem->addToGroup(pText);
                    }
                }
            }
        }

        for(int i = 1; i < nVal; i++)
        {
            if(pItem->m_bSelectHorMinor && pItem->m_bMainHor) //显示X轴刻度
            {
                QPainterPath mPath; //生成线的path

                //画次刻度
                mMoveX = i * SubSpace + nLeftSpace;
                mMoveY = nTopSpace + nBGH;
                mLineX = mMoveX;
                mLineY = ML / 2 + nTopSpace + nBGH;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineType(1); //设置
                pLine->setLineColor(pItem->m_nScaleColor); //线条颜色
                pLine->SetName(QString("XSubScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //画次格线
            if(pItem->m_bGrade && pItem->m_bSelectHorMinor) //是否显示格线
            {
                QPainterPath mPath1;               //生成线的path
                mMoveX = i * SubSpace + nLeftSpace;
                mMoveY = nTopSpace;
                mLineX = mMoveX;
                mLineY = nTopSpace + nBGH;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pXLine = new QLineItem(mPath1);
                pXLine->setLineColor(pItem->m_nVerColor); //格线颜色
                pXLine->setLineType(3); //设置为虚线
                pXLine->SetName(QString("XSubLine%1").arg(i));
                pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pXLine);
            }
        }
    }

    //--------------------开始画Y轴刻度--------------------
    MainSpace   = nBGH / nYmain;          //主刻度间隔
    SubSpace    = nBGH / (nYsub * nYmain);//次刻度间隔
    nVal        = nYsub * nYmain;         //次刻度总数

    //if(pItem->m_bMainVer)
    {
        for(int i = 0; i <= nYmain; i++)
        {
            if(pItem->m_bMainVer)
            {
                //画主刻度
                QPainterPath mPath;               //生成线的path
                mMoveX = nLeftSpace - ML;
                mMoveY = i * MainSpace + nTopSpace;
                mLineX = nLeftSpace;
                mLineY = i * MainSpace + nTopSpace;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineColor(pItem->m_nScaleColor); //线条颜色
                pLine->SetName(QString("YMainScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //画主格线
            if(pItem->m_bGrade) //是否显示格线
            {
                if(i != 0 && i != nYmain)
                {
                    QPainterPath mPath1;               //生成线的path
                    mMoveX = nLeftSpace;
                    mMoveY = i * MainSpace + nTopSpace;
                    mLineX = nLeftSpace + nBGW;
                    mLineY = i * MainSpace + nTopSpace;
                    mPath1.moveTo(mMoveX,mMoveY);
                    mPath1.lineTo(mLineX,mLineY);
                    pLine = new QLineItem(mPath1);
                    pLine->setLineColor(pItem->m_nHorColor); //线条颜色
                    pLine->SetName(QString("YMainLine%1").arg(i)); //YSubScale
                    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->addToGroup(pLine);
                }
            }

            if(pItem->m_bMainVer)
            {
                //显示Y轴文本
                mLineX = nLeftSpace - ML;
                mLineY = i * MainSpace + nTopSpace;
                sText = "YY";//GetText(yMin,yMax,nYmain,yPointCount,1,i,nType);
                        sText   = GetText(m_nDisplayMin, m_nDisplayMax, nYmain, 2, 1, i, 2);
                pText = new QSimpleTextItem(rect,sText);
                pText = DrawTrendText(pText, i, mLineX, mLineY, sText, nFontSizeY, pItem->m_nMarkedColor, 1);
                pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pText);
            }
        }

        for(int i = 1; i < nVal; i++) //画次刻度
        {
            if(pItem->m_bSelectVertMinor && pItem->m_bMainVer) //显示Y轴刻度
            {
                QPainterPath mPath; //生成线的path
                mMoveX = nLeftSpace - ML / 2;
                mMoveY = i * SubSpace + nTopSpace;
                mLineX = nLeftSpace;
                mLineY = i * SubSpace + nTopSpace;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineColor(pItem->m_nScaleColor); //线条颜色
                pLine->SetName(QString("YSubScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //画Y轴次格线
            if(pItem->m_bGrade && pItem->m_bSelectVertMinor) //是否显示格线
            {
                QPainterPath mPath1;               //生成线的path
                mMoveX = nLeftSpace;
                mMoveY = i * SubSpace + nTopSpace;
                mLineX = nLeftSpace + nBGW;
                mLineY = i * SubSpace + nTopSpace;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath1);
                pLine->setLineType(3);
                pLine->setLineColor(pItem->m_nHorColor); //线条颜色
                pLine->SetName(QString("YSubLine%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }
        }
    }

    //--------------------开始画笔--------------------
    //double YPenSpace = nBGH / 8; //Y轴方向每条笔之间的间隔,既然是随机的线，那就不要了
    //double XPenSpace = nBGW / 4; //X轴方向每条笔之间的间隔
    double XPenSpace = 0;
    int pointNum = (4 > nXmain) ? 4 : nXmain;
    if(nXmain < 4)
    {
        XPenSpace = nBGW / 4;
    }
    else
    {
        XPenSpace = nBGW / nXmain;
    }
    QFoldLineItem *pPenLine;
    srand(time(0));//初始化随机函数时间
    unsigned int addY = 0;
    for(int j = 0;j < pItem->m_vecChannelGroups.size(); j++)//多少个通道就有多少线
    {
        QPainterPath mPenPath = QPainterPath();
        addY = rand() % (int)nBGH;
        mPenPath.moveTo(QPointF(nLeftSpace, nTopSpace + addY));//第一点
        for(int i = 1; i <= pointNum; i++)
        {
            mPenPath.lineTo(QPointF(nLeftSpace + i * XPenSpace, nTopSpace + (rand() % (int)nBGH)));
        }

        pPenLine = new QFoldLineItem(mPenPath);
        pPenLine->setLineType(pItem->m_vecChannelGroups.at(j).eLineType);
        pPenLine->setLineColor(pItem->m_vecChannelGroups.at(j).nDisplayColor); //线条颜色
        pPenLine->SetName(QString("PenLine%1").arg(j));
        pPenLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pItem->addToGroup(pPenLine);
    }
}

void QDrawGraphics::OnDrawXYTrend(XYtrend *pItem)
{
    if(!pItem)
    {
        return;
    }

    QString sText = "";
    int nFontSizeX = pItem->m_textSize;       //字体大小
    int nFontSizeY = pItem->m_textSize;       //字体大小

    //X轴
    int nXmain  = pItem->m_nHorMajorScale; //主刻度
    int nXsub   = pItem->m_nHorMinorScale; //次刻度
    double m_nDisplayMinX = pItem->m_nDisplayMinX;
    double m_nDisplayMaxX = pItem->m_nDisplayMaxX;
    qDebug() << "min X:" << m_nDisplayMinX;
    qDebug() << "max X:" << m_nDisplayMaxX;
    //Y轴
    int nYmain  = pItem->m_nVertMajorScale; //主刻度
    int nYsub   = pItem->m_nVertMinorScale; //次刻度

    double m_nDisplayMin = pItem->m_nDisplayMinY;
    double m_nDisplayMax = pItem->m_nDisplayMaxY;
    qDebug() << "min Y:" << m_nDisplayMin;
    qDebug() << "max Y:" << m_nDisplayMax;

    //getDateTime(pItem,tStart,tEnd);
    //以下是画图所需的变量
    int         nTopSpace   = 20;                           //画底色框距离背景框的上坐标偏移量
    int         nLeftSpace  = 60;//80;                      //画底色框距离背景框的左坐标偏移量,这个长度需要一种算法来计算
    double      nBGW        = 400-nLeftSpace-nLeftSpace/2;  //底色矩形的宽度
    double      nBGH        = 250-nTopSpace-2*nTopSpace;    //底色矩形的高度
    if(!pItem->m_bMainVer && !pItem->m_bMainHor)//没有水平-没有垂直
    {
        nTopSpace   = 0;
        nLeftSpace  = 0;
        nBGW = 400;
        nBGH = 250;
    }
    else if(!pItem->m_bMainVer && pItem->m_bMainHor)//有水平-没有垂直
    {
        nTopSpace   = 0;
        nLeftSpace  = 30;
        nBGW = 340;
        nBGH = 250;
    }
    else if(pItem->m_bMainVer && !pItem->m_bMainHor)//有水平-没有垂直
    {
        nTopSpace   = 20;
        nLeftSpace  = 0;
        nBGW = 400;
        nBGH = 210;
    }

    int         ML          = 10;                           //刻度长度
    int         nVal        = nXsub*nXmain;                 //次刻度总数
    double      mMoveX      = 0;                            //主刻度X起始点
    double      mMoveY      = 0;                            //主刻度Y起始点
    double      mLineX      = 0;                            //主刻度X起始点
    double      mLineY      = 0;                            //主刻度Y起始点
    double      MainSpace   = nBGW/nXmain;                  //主刻度间隔
    double      SubSpace    = nBGW/(nXsub*nXmain);          //次刻度间隔
    QRectItem*  pBackRect;                                  //背景矩形框
    QRectItem*  pBGRect;                                    //底色矩形框
    QLineItem*  pLine;
    QLineItem*  pXLine;
    QSimpleTextItem *pText;

    //----------------------开始画背景矩形------------------------
    QRectF rect(QPointF(0,0), QSize(400,250));     //背景矩形框480,250
    //pBackRect = new QRectItem(rect);
    //pBackRect->SetBackColor(pItem->m_nBoradColor);
    //pBackRect->SetLineType(0);
    //pBackRect->SetAlpha(100);
    //pBackRect->SetName(pItem->m_nBoradColor.name());
    //pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    //pItem->addToGroup(pBackRect);
    //pBackRect->SetAlpha(255);

    //--------------------开始画图表区底色矩形--------------------
    rect.setTopLeft(QPoint(nLeftSpace,nTopSpace));
    rect.setSize(QSizeF(nBGW,nBGH));
    pBGRect = new QRectItem(rect);
    pBGRect->SetBackColor(pItem->m_nGraphColor);
    pBGRect->SetLineColor(pItem->m_nBoradColor);
    pBGRect->SetAlpha(pItem->m_alpha);
    pBGRect->SetName("backRect");
    pBGRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pItem->addToGroup(pBGRect);

    //--------------------开始画X轴刻度--------------------
    //if(pItem->m_bMainHor)
    {
        for(int i = 0; i <= nXmain; i++)
        {
            QPainterPath mPath;//生成线的path

            if(pItem->m_bMainHor)
            {
                //画主刻度
                mMoveX = i * MainSpace + nLeftSpace;
                mMoveY = nTopSpace + nBGH;
                mLineX = i * MainSpace + nLeftSpace;
                mLineY = nTopSpace + nBGH + ML;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineType(1);          //字体类型
                pLine->setLineColor(pItem->m_nScaleColor); //主刻度颜色
                pLine->SetName(QString("XMainScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //画主格线
            if(pItem->m_bGrade)//是否显示格线
            {
                if(i != 0 && i != nXmain)
                {
                    QPainterPath mPath1;               //生成线的path
                    mMoveX = i * MainSpace + nLeftSpace;
                    mMoveY = nTopSpace;
                    mLineX = i * MainSpace + nLeftSpace;
                    mLineY = nTopSpace + nBGH;
                    mPath1.moveTo(mMoveX,mMoveY);
                    mPath1.lineTo(mLineX,mLineY);
                    pXLine = new QLineItem(mPath1);
                    pXLine->setLineType(1); //设置
                    pXLine->setLineColor(pItem->m_nVerColor); //格线颜色
                    pXLine->SetName(QString("XMainLine%1").arg(i));
                    pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->addToGroup(pXLine);
                }
            }

            if(pItem->m_bMainHor)
            {
                //是否显示文本
                if(1)
                {
                    mLineX  = i * MainSpace + nLeftSpace;
                    mLineY  = nTopSpace + nBGH + ML;

                    //画时间文本
                    if(1)
                    {
                        sText   = GetText(m_nDisplayMaxX, m_nDisplayMinX, nXmain, 2, 1, i, 2);

                        pText   = new QSimpleTextItem(rect,sText);
                        pText   = DrawTrendText(pText, i, mLineX, mLineY, sText, nFontSizeX, pItem->m_TextColor,0);
                        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
                        pItem->addToGroup(pText);
                    }

                }
            }
        }

        for(int i = 1; i < nVal; i++)
        {
            if(pItem->m_bSelectHorMinor && pItem->m_bMainHor) //显示X轴刻度
            {
                QPainterPath mPath; //生成线的path

                //画次刻度
                mMoveX = i * SubSpace + nLeftSpace;
                mMoveY = nTopSpace + nBGH;
                mLineX = mMoveX;
                mLineY = ML / 2 + nTopSpace + nBGH;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineType(1); //设置
                pLine->setLineColor(pItem->m_nScaleColor); //线条颜色
                pLine->SetName(QString("XSubScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //画次格线
            if(pItem->m_bGrade && pItem->m_bSelectHorMinor) //是否显示格线
            {
                QPainterPath mPath1;               //生成线的path
                mMoveX = i * SubSpace + nLeftSpace;
                mMoveY = nTopSpace;
                mLineX = mMoveX;
                mLineY = nTopSpace + nBGH;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pXLine = new QLineItem(mPath1);
                pXLine->setLineColor(pItem->m_nVerColor); //格线颜色
                pXLine->setLineType(3); //设置为虚线
                pXLine->SetName(QString("XSubLine%1").arg(i));
                pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pXLine);
            }
        }
    }

    //--------------------开始画Y轴刻度--------------------
    MainSpace   = nBGH / nYmain;          //主刻度间隔
    SubSpace    = nBGH / (nYsub * nYmain);//次刻度间隔
    nVal        = nYsub * nYmain;         //次刻度总数

    //if(pItem->m_bMainVer)
    {
        for(int i = 0; i <= nYmain; i++)
        {
            if(pItem->m_bMainVer)
            {
                //画主刻度
                QPainterPath mPath;               //生成线的path
                mMoveX = nLeftSpace - ML;
                mMoveY = i * MainSpace + nTopSpace;
                mLineX = nLeftSpace;
                mLineY = i * MainSpace + nTopSpace;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineColor(pItem->m_nScaleColor); //线条颜色
                pLine->SetName(QString("YMainScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //画主格线
            if(pItem->m_bGrade) //是否显示格线
            {
                if(i != 0 && i != nYmain)
                {
                    QPainterPath mPath1;               //生成线的path
                    mMoveX = nLeftSpace;
                    mMoveY = i * MainSpace + nTopSpace;
                    mLineX = nLeftSpace + nBGW;
                    mLineY = i * MainSpace + nTopSpace;
                    mPath1.moveTo(mMoveX,mMoveY);
                    mPath1.lineTo(mLineX,mLineY);
                    pLine = new QLineItem(mPath1);
                    pLine->setLineColor(pItem->m_nHorColor); //线条颜色
                    pLine->SetName(QString("YMainLine%1").arg(i)); //YSubScale
                    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->addToGroup(pLine);
                }
            }

            if(pItem->m_bMainVer)
            {
                //显示Y轴文本
                mLineX = nLeftSpace - ML;
                mLineY = i * MainSpace + nTopSpace;
                sText = "YY";//GetText(yMin,yMax,nYmain,yPointCount,1,i,nType);
                sText   = GetText(m_nDisplayMin, m_nDisplayMax, nYmain, 2, 1, i, 2);
                pText = new QSimpleTextItem(rect,sText);
                pText = DrawTrendText(pText, i, mLineX, mLineY, sText, nFontSizeY, pItem->m_TextColor, 1);
                pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pText);
            }
        }

        for(int i = 1; i < nVal; i++) //画次刻度
        {
            if(pItem->m_bSelectVertMinor && pItem->m_bMainVer) //显示Y轴刻度
            {
                QPainterPath mPath; //生成线的path
                mMoveX = nLeftSpace - ML / 2;
                mMoveY = i * SubSpace + nTopSpace;
                mLineX = nLeftSpace;
                mLineY = i * SubSpace + nTopSpace;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineColor(pItem->m_nScaleColor); //线条颜色
                pLine->SetName(QString("YSubScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //画Y轴次格线
            if(pItem->m_bGrade && pItem->m_bSelectVertMinor) //是否显示格线
            {
                QPainterPath mPath1;               //生成线的path
                mMoveX = nLeftSpace;
                mMoveY = i * SubSpace + nTopSpace;
                mLineX = nLeftSpace + nBGW;
                mLineY = i * SubSpace + nTopSpace;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath1);
                pLine->setLineType(3);
                pLine->setLineColor(pItem->m_nHorColor); //线条颜色
                pLine->SetName(QString("YSubLine%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }
        }
    }

    //--------------------开始画笔--------------------
    //double YPenSpace = nBGH / 8; //Y轴方向每条笔之间的间隔,既然是随机的线，那就不要了
    //double XPenSpace = nBGW / 4; //X轴方向每条笔之间的间隔
    double XPenSpace = 0;
    int pointNum = (4 > nXmain) ? 4 : nXmain;
    if(nXmain < 4)
    {
        XPenSpace = nBGW / 4;
    }
    else
    {
        XPenSpace = nBGW / nXmain;
    }
    QFoldLineItem *pPenLine;
    srand(time(0));//初始化随机函数时间
    unsigned int addY = 0;
    for(int j = 0;j < pItem->m_vecChannels.size(); j++)//多少个通道就有多少线
    {
        QPainterPath mPenPath = QPainterPath();
        addY = rand() % (int)nBGH;
        mPenPath.moveTo(QPointF(nLeftSpace, nTopSpace + addY));//第一点
        for(int i = 1; i <= pointNum; i++)
        {
            mPenPath.lineTo(QPointF(nLeftSpace + i * XPenSpace, nTopSpace + (rand() % (int)nBGH)));
        }

        pPenLine = new QFoldLineItem(mPenPath);
        pPenLine->setLineType(pItem->m_vecChannels.at(j).eLineType);
        pPenLine->setLineColor(pItem->m_vecChannels.at(j).nDisplayColor); //线条颜色
        pPenLine->SetName(QString("PenLine%1").arg(j));
        pPenLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pItem->addToGroup(pPenLine);
    }
}
/***************************************************************
 *函数名称：OnDrawDataGroup
 *函数功能：数据群组
 *参数含义：
 *edit by czq
 **************************************************************/
void QDrawGraphics::OnDrawDataGroup(QTrendDataGroupAttr *pItem)//新的数据群组调用函数
{
    if(!pItem)
    {
        return;
    }

    QString sText  = "";
    int nFontSizeX = pItem->m_nFontSize;       //字体大小
    int nFontSizeY = pItem->m_nFontSize;       //字体大小

    //X轴
    int nXmain  = pItem->m_nHorMajorScale; //主刻度
    int nXsub   = pItem->m_nHorMinorScale; //次刻度

    //Y轴
    int nYmain  = pItem->m_nVertMajorScale; //主刻度
    int nYsub   = pItem->m_nVertMinorScale; //次刻度

    //以下是画图所需的变量
    int         nTopSpace   = 20;                           //画底色框距离背景框的上坐标偏移量
    int         nLeftSpace  = 60;//80;                      //画底色框距离背景框的左坐标偏移量,这个长度需要一种算法来计算
    int         ML          = 10;                           //刻度长度
    int         nVal        = nXsub*nXmain;                 //次刻度总数
    double      nBGW        = 400-nLeftSpace-nLeftSpace/2;  //底色矩形的宽度
    double      nBGH        = 250-nTopSpace-2*nTopSpace;    //底色矩形的高度
    if(!pItem->m_bMainVer && !pItem->m_bMainHor)//没有水平-没有垂直
    {
        nTopSpace   = 0;
        nLeftSpace  = 0;
        nBGW = 400;
        nBGH = 250;
    }
    else if(!pItem->m_bMainVer && pItem->m_bMainHor)//有水平-没有垂直
    {
        nTopSpace   = 0;
        nLeftSpace  = 30;
        nBGW = 340;
        nBGH = 250;
    }
    else if(pItem->m_bMainVer && !pItem->m_bMainHor)//有水平-没有垂直
    {
        nTopSpace   = 20;
        nLeftSpace  = 0;
        nBGW = 400;
        nBGH = 210;
    }
    double      mMoveX      = 0;                            //主刻度X起始点
    double      mMoveY      = 0;                            //主刻度Y起始点
    double      mLineX      = 0;                            //主刻度X起始点
    double      mLineY      = 0;                            //主刻度Y起始点
    double      MainSpace   = nBGW/nXmain;                  //主刻度间隔
    double      SubSpace    = nBGW/(nXsub*nXmain);          //次刻度间隔
    QRectItem*  pBackRect;                                  //背景矩形框
    QRectItem*  pBGRect;                                    //底色矩形框
    QLineItem*  pLine;
    QLineItem*  pXLine;
    QSimpleTextItem *pText;

    //----------------------开始画背景矩形------------------------
    QRectF rect(QPointF(0,0), QSize(400,250));     //背景矩形框480,250
//    pBackRect = new QRectItem(rect);
//    pBackRect->SetBackColor(pItem->m_nBoradColor);
//    pBackRect->SetAlpha(0);
//    pBackRect->SetLineType(0);
//    pBackRect->SetName(pItem->m_nBoradColor.name());
//    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
//    pItem->addToGroup(pBackRect);
    //pBackRect->SetAlpha(255);

    //--------------------开始画图表区底色矩形--------------------
    rect.setTopLeft(QPoint(nLeftSpace,nTopSpace));
    rect.setSize(QSizeF(nBGW,nBGH));
    pBGRect = new QRectItem(rect);
    pBGRect->SetBackColor(pItem->m_nGraphColor);
    pBGRect->SetLineColor(pItem->m_nBoradColor);
    pBGRect->SetAlpha(pItem->m_alpha);
    pBGRect->SetName("backRect");
    //pBGRect->SetName(pItem->m_nGraphColor.name());
    pBGRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pItem->addToGroup(pBGRect);

    //--------------------开始画X轴刻度--------------------
    for(int i = 0; i <= nXmain; i++)
    {
        QPainterPath mPath;//生成线的path

        if(pItem->m_bMainHor)
        {
            //画主刻度
            mMoveX = i * MainSpace + nLeftSpace;
            mMoveY = nTopSpace + nBGH;
            mLineX = i * MainSpace + nLeftSpace;
            mLineY = nTopSpace + nBGH + ML;

            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);

            pLine = new QLineItem(mPath);
            pLine->setLineType(1);          //字体类型
            pLine->setLineColor(pItem->m_nScaleColor); //主刻度颜色
            pLine->SetName(QString("XMainScale%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pLine);

            //是否显示文本
            mLineX  = i * MainSpace + nLeftSpace;
            mLineY  = nTopSpace + nBGH + ML;

            sText   = "XX";//这个需要根据时间算出来，自己以后要写一个函数的
            sText   = GetText(0, pItem->m_nDataSample-1, pItem->m_nHorMajorScale, 0, 0, i, 1);

            pText   = new QSimpleTextItem(rect,sText);
            pText   = DrawTrendText(pText, i, mLineX, mLineY, sText, nFontSizeX, pItem->m_nMarkedColor,0);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pText);
        }

        //画主格线
        if(pItem->m_bGrade)//是否显示格线
        {
            if(i != 0 && i != nXmain)
            {
                QPainterPath mPath1;               //生成线的path
                mMoveX = i * MainSpace + nLeftSpace;
                mMoveY = nTopSpace;
                mLineX = i * MainSpace + nLeftSpace;
                mLineY = nTopSpace + nBGH;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pXLine = new QLineItem(mPath1);
                pXLine->setLineType(1); //设置
                pXLine->setLineColor(pItem->m_nVerColor); //格线颜色
                pXLine->SetName(QString("XMainLine%1").arg(i));
                pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pXLine);
            }
        }
    }

    for(int i = 1; i < nVal; i++)
    {
        if(pItem->m_bSelectHorMinor && pItem->m_bMainHor) //显示X轴刻度
        {
            QPainterPath mPath; //生成线的path

            //画次刻度
            mMoveX = i * SubSpace + nLeftSpace;
            mMoveY = nTopSpace + nBGH;
            mLineX = mMoveX;
            mLineY = ML / 2 + nTopSpace + nBGH;

            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);

            pLine = new QLineItem(mPath);
            pLine->setLineType(1); //设置
            pLine->setLineColor(pItem->m_nScaleColor); //线条颜色
            pLine->SetName(QString("XSubScale%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pLine);
        }

        //画次格线
        if(pItem->m_bGrade &&  pItem->m_bSelectHorMinor) //是否显示格线
        {
            QPainterPath mPath1;               //生成线的path
            mMoveX = i * SubSpace + nLeftSpace;
            mMoveY = nTopSpace;
            mLineX = mMoveX;
            mLineY = nTopSpace + nBGH;
            mPath1.moveTo(mMoveX,mMoveY);
            mPath1.lineTo(mLineX,mLineY);
            pXLine = new QLineItem(mPath1);
            pXLine->setLineColor(pItem->m_nVerColor); //格线颜色
            pXLine->setLineType(3); //设置为虚线
            pXLine->SetName(QString("XSubLine%1").arg(i));
            pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pXLine);
        }
    }

    //--------------------开始画Y轴刻度--------------------
    MainSpace   = nBGH / nYmain;          //主刻度间隔
    SubSpace    = nBGH / (nYsub * nYmain);//次刻度间隔
    nVal        = nYsub * nYmain;         //次刻度总数

    for(int i = 0; i <= nYmain; i++)
    {
        //画主刻度
        QPainterPath mPath;               //生成线的path

        if(pItem->m_bMainVer)
        {
            mMoveX = nLeftSpace - ML;
            mMoveY = i * MainSpace + nTopSpace;
            mLineX = nLeftSpace;
            mLineY = i * MainSpace + nTopSpace;

            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);

            pLine = new QLineItem(mPath);
            pLine->setLineColor(pItem->m_nScaleColor); //线条颜色
            pLine->SetName(QString("YMainScale%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pLine);

            //显示Y轴文本
            mLineX = nLeftSpace - ML;
            mLineY = i * MainSpace + nTopSpace;
            sText = GetText(pItem->m_nDisplayMin,pItem->m_nDisplayMax,pItem->m_nVertMajorScale,2,1,i,1);
            pText = new QSimpleTextItem(rect,sText);
            pText = DrawTrendText(pText, i, mLineX, mLineY, sText, nFontSizeY, pItem->m_nMarkedColor, 1);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pText);
        }

        //画主格线
        if(pItem->m_bGrade) //是否显示格线
        {
            if(i != 0 && i != nYmain)
            {
                QPainterPath mPath1;               //生成线的path
                mMoveX = nLeftSpace;
                mMoveY = i * MainSpace + nTopSpace;
                mLineX = nLeftSpace + nBGW;
                mLineY = i * MainSpace + nTopSpace;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath1);
                pLine->setLineColor(pItem->m_nHorColor); //线条颜色
                pLine->SetName(QString("YMainLine%1").arg(i)); //YSubScale
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }
        }
    }

    for(int i = 1; i < nVal; i++) //画次刻度
    {
        if(pItem->m_bSelectVertMinor && pItem->m_bMainVer) //显示Y轴刻度
        {
            QPainterPath mPath; //生成线的path
            mMoveX = nLeftSpace - ML / 2;
            mMoveY = i * SubSpace + nTopSpace;
            mLineX = nLeftSpace;
            mLineY = i * SubSpace + nTopSpace;

            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);

            pLine = new QLineItem(mPath);
            pLine->setLineColor(pItem->m_nScaleColor); //线条颜色
            pLine->SetName(QString("YSubScale%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pLine);
        }

        //画Y轴次格线
        if(pItem->m_bGrade && pItem->m_bSelectVertMinor) //是否显示格线
        {
            QPainterPath mPath1;               //生成线的path
            mMoveX = nLeftSpace;
            mMoveY = i * SubSpace + nTopSpace;
            mLineX = nLeftSpace + nBGW;
            mLineY = i * SubSpace + nTopSpace;
            mPath1.moveTo(mMoveX,mMoveY);
            mPath1.lineTo(mLineX,mLineY);
            pLine = new QLineItem(mPath1);
            pLine->setLineType(3);
            pLine->setLineColor(pItem->m_nHorColor); //线条颜色
            pLine->SetName(QString("YSubLine%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pLine);
        }
    }

    //--------------------开始画笔--------------------
    double XPenSpace = 0;
    int pointNum = (4 > nXmain) ? 4 : nXmain;
    if(nXmain < 4)
    {
        XPenSpace = nBGW / 4;
    }
    else
    {
        XPenSpace = nBGW / nXmain;
    }
    QFoldLineItem *pPenLine;
    srand(time(0));//初始化随机函数时间
    unsigned int addY = 0;
    for(int j = 0;j < pItem->m_vecChannelGroups.size(); j++)//多少个通道就有多少线
    {
        QPainterPath mPenPath = QPainterPath();
        addY = rand() % (int)nBGH;
        mPenPath.moveTo(QPointF(nLeftSpace, nTopSpace + addY));//第一点
        for(int i = 1; i <= pointNum; i++)
        {
            mPenPath.lineTo(QPointF(nLeftSpace + i * XPenSpace, nTopSpace + (rand() % (int)nBGH)));
        }

        pPenLine = new QFoldLineItem(mPenPath);
        pPenLine->setLineType(pItem->m_vecChannelGroups.at(j).eLineType);
        pPenLine->setLineColor(pItem->m_vecChannelGroups.at(j).nDisplayColor); //线条颜色
        pPenLine->SetName(QString("PenLine%1").arg(j));
        pPenLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pItem->addToGroup(pPenLine);
    }
}

/***************************************************************
 *函数名称：OnDrawTrendChart
 *函数功能：画趋势图、XY趋势图以及历史趋势图函数
 *参数含义：
 *nType：趋势图类型，1--趋势图；2--XY趋势图，3--历史趋势图
 *pList：各个页面的存储信息
 *edit by zqh
 **************************************************************/
QGraphicsItem* QDrawGraphics::OnDrawTrendChart(int nType,
                                               QStringList *pList)
{
    pGroup = new QItemGroup;
    QString sText = "";
    int i = 0;
    int j = 0;

    QColor mBkColor = pwnd->StringTOColor(pList->at(150)); //背景色
    int nPenCount = pList->at(154).toInt();                //笔的总数

    QColor mBgColor = pwnd->StringTOColor(pList->at(159)); //底色
    int nLineType[8];
    QColor mPenColor[8];

    //X轴
    bool bIfShowX = pList->at(50).toInt();    //是否显示刻度
    bool bIfShowGridX = pList->at(51).toInt(); //是否显示Y轴格线
    QColor mAGColorX = pwnd->StringTOColor(pList->at(52));   //轴/格线颜色
    QColor mGridColorX = pwnd->StringTOColor(pList->at(53)); //格线颜色
    int nXmain = pList->at(54).toInt(); //主刻度
    int nXsub = pList->at(55).toInt();  //次刻度
    bool bIfShowMarkX = pList->at(56).toInt();    //是否显示刻度标示
    int nFontSizeX = pList->at(57).toInt();       //字体大小
    double xMin = 0;      //x轴最小值
    double xMax = 0;      //x轴最大值
    int xPointCount = 0;  //小数位数
    QString sDate = "";  //历史趋势图的日期

    //Y轴
    bool bIfShowY = pList->at(20).toInt();    //是否显示刻度
    bool bIfShowGridY= pList->at(21).toInt(); //是否显示Y轴格线
    QColor mAGColorY = pwnd->StringTOColor(pList->at(22));   //轴/格线颜色
    QColor mGridColorY = pwnd->StringTOColor(pList->at(23)); //格线颜色
    int nYmain = pList->at(24).toInt(); //主刻度
    int nYsub = pList->at(25).toInt();  //次刻度
    bool bIfShowMarkY = pList->at(26).toInt();    //是否显示刻度标示
    int nFontSizeY = pList->at(27).toInt();       //字体大小
    double yMin = pList->at(28).toDouble();       //Y轴最小值
    double yMax = pList->at(29).toDouble();       //Y轴最大值
    int yPointCount = pList->at(31).toInt();      //小数位数
    int bkAlpha = pList->at(162).toInt();      //背景色透明度

    /***********************以下是画图所需的变量************************/

    int nTopSpace = 20;   //画底色框距离背景框的上坐标偏移量
    int nLeftSpace = 80;  //画底色框距离背景框的左坐标偏移量
    double nBGW = 400-nLeftSpace-nLeftSpace/2; //底色矩形的宽度
    double nBGH = 250-nTopSpace-2*nTopSpace;   //底色矩形的高度
    QRectItem *pBackRect; //背景矩形框
    QRectItem *pBGRect;   //底色矩形框
    double mMoveX = 0;                //主刻度X起始点
    double mMoveY = 0;                //主刻度Y起始点
    double mLineX = 0;                //主刻度X起始点
    double mLineY = 0;                //主刻度Y起始点
    double MainSpace = nBGW/nXmain;           //主刻度间隔
    double SubSpace = nBGW/(nXsub*nXmain); //次刻度间隔
    QLineItem *pLine;
    QLineItem *pXLine;
    QSimpleTextItem *pText;
    int ML = 10;                     //刻度长度
    int nVal = nXsub*nXmain; //次刻度总数

    /*****************************end********************************/

    for(i = 0; i < 8; i++)
    {
        nLineType[i] = pList->at(102+i*4).toInt(); //每条笔的样式
        mPenColor[i] = pwnd->StringTOColor(pList->at(103+i*4));//笔的颜色
    }

    switch(nType)
    {
    case 1: //趋势图
        xMin = 0;
        xMax = pList->at(155).toInt();
        xPointCount = 0;
        xMax--;
        break;
    case 2: //XY趋势图
        xMin = pList->at(58).toDouble();
        xMax = pList->at(59).toDouble();
        xPointCount = pList->at(61).toInt();
        break;
    case 3: //历史趋势图
        {
            xMin = pList->at(58).toInt(); //存时间格式
            xMax = pList->at(59).toInt()*3600+pList->at(60).toInt()*60+pList->at(61).toInt(); //把时分秒转化为秒
            QDate date = QDate::fromString(pList->at(62));
            sDate = QString("%1-%2-%3").arg(date.year()).arg(date.month()).arg(date.day());
        }
        break;
    case 4: //数据群组显示
        xMin = 0;
        xMax = pList->at(155).toInt()-1;
        xPointCount = 0;
        break;
    default:
        break;
    }

    /*****************************************************************
  *开始画背景矩形
  ****************************************************************/

    QRectF rect(QPointF(0,0), QSize(400,250));     //背景矩形框480,250
    pBackRect = new QRectItem(rect);
    pBackRect->SetBackColor(mBkColor);
    pBackRect->SetLineType(0);
    pBackRect->SetName("mBackRect");
    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->addToGroup(pBackRect);
    pBackRect->SetAlpha(bkAlpha);

    /*****************************************************************
   *开始画底色矩形
   ****************************************************************/
    rect.setTopLeft(QPoint(nLeftSpace,nTopSpace));
    rect.setSize(QSizeF(nBGW,nBGH));
    pBGRect = new QRectItem(rect);
    pBGRect->SetBackColor(mBgColor);
    pBGRect->SetName("mBGRect");
    pBGRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->addToGroup(pBGRect);

    /*****************************************************************
   *开始画X轴刻度
   ****************************************************************/

    for(i = 0; i <= nXmain;i++)
    {
        if(bIfShowX) //显示X轴刻度
        {
            QPainterPath mPath;               //生成线的path
            //画主刻度
            mMoveX = i*MainSpace+nLeftSpace;
            mMoveY = nTopSpace+nBGH;
            mLineX = i*MainSpace+nLeftSpace;
            mLineY = nTopSpace+nBGH+ML;
            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);
            pLine = new QLineItem(mPath);
            pLine->setLineType(1); //设置
            pLine->setLineColor(mAGColorX); //主刻度颜色
            pLine->SetName(QString("XMainScale%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pGroup->addToGroup(pLine);
        }

        //画主格线
        if(bIfShowGridX) //是否显示格线
        {
            if(i != 0 && i != nXmain)
            {
                QPainterPath mPath1;               //生成线的path
                mMoveX = i*MainSpace+nLeftSpace;
                mMoveY = nTopSpace;
                mLineX = i*MainSpace+nLeftSpace;
                mLineY = nTopSpace+nBGH;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pXLine = new QLineItem(mPath1);
                pXLine->setLineType(1); //设置
                pXLine->setLineColor(mGridColorX); //格线颜色
                pXLine->SetName(QString("XMainLine%1").arg(i));
                pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pGroup->addToGroup(pXLine);
            }
        }

        if(bIfShowMarkX) //是否显示文本
        {
            mLineX = i*MainSpace+nLeftSpace;
            mLineY = nTopSpace+nBGH+ML;
            sText = GetText(xMin,xMax,nXmain,xPointCount,0,i,nType);
            pText = new QSimpleTextItem(rect,sText);
            pText = DrawTrendText(pText,i,mLineX,mLineY,sText,nFontSizeX,
                                  mAGColorX,0);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pGroup->addToGroup(pText);
            if(nType == 3) //历史趋势图
            {

                pText = drawHisTrendDate(i,mLineX,mLineY,sDate,nFontSizeX,
                                         mAGColorX,false);
                pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pGroup->addToGroup(pText);
            }
        }
    } //end for


    for(i = 1; i < nVal;i++)
    {
        if(i%nXsub != 0 && nXsub != 0)
        {
            if(bIfShowX) //显示X轴刻度
            {
                QPainterPath mPath;               //生成线的path
                //画次刻度
                mMoveX = i*SubSpace+nLeftSpace;
                mMoveY = nTopSpace+nBGH;
                mLineX = mMoveX;
                mLineY = ML/2+nTopSpace+nBGH;
                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath);
                pLine->setLineType(1); //设置
                pLine->setLineColor(mAGColorX); //线条颜色
                pLine->SetName(QString("XSubScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pGroup->addToGroup(pLine);
            }

            //画次格线
            if(bIfShowGridX) //是否显示格线
            {
                QPainterPath mPath1;               //生成线的path
                mMoveX = i*SubSpace+nLeftSpace;
                mMoveY = nTopSpace;
                mLineX = mMoveX;
                mLineY = nTopSpace+nBGH;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pXLine = new QLineItem(mPath1);
                pXLine->setLineColor(mGridColorX); //格线颜色
                pXLine->setLineType(3); //设置为虚线
                pXLine->SetName(QString("XSubLine%1").arg(i));
                pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pGroup->addToGroup(pXLine);
            }
        }
    }

    /*****************************************************************
     *开始画Y轴刻度
     ****************************************************************/

    MainSpace = nBGH/nYmain;           //主刻度间隔
    SubSpace = nBGH/(nYsub*nYmain); //次刻度间隔
    nVal = nYsub*nYmain; //次刻度总数

    for(i = 0; i <= nYmain;i++)
    {
        if(bIfShowY)
        {
            //画主刻度
            QPainterPath mPath;               //生成线的path
            mMoveX = nLeftSpace-ML;
            mMoveY = i*MainSpace+nTopSpace;
            mLineX = nLeftSpace;
            mLineY = i*MainSpace+nTopSpace;
            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);
            pLine = new QLineItem(mPath);
            pLine->setLineColor(mAGColorY); //线条颜色
            pLine->SetName(QString("YMainScale%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pGroup->addToGroup(pLine);
        }

        //画主格线
        if(bIfShowGridY) //是否显示格线
        {
            if(i != 0 && i != nYmain)
            {
                QPainterPath mPath1;               //生成线的path
                mMoveX = nLeftSpace;
                mMoveY = i*MainSpace+nTopSpace;
                mLineX = nLeftSpace+nBGW;
                mLineY = i*MainSpace+nTopSpace;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath1);
                pLine->setLineColor(mGridColorY); //线条颜色
                pLine->SetName(QString("YMainLine%1").arg(i)); //YSubScale
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pGroup->addToGroup(pLine);
            }
        }
        if(bIfShowMarkY) //是否显示文本
        {
            mLineX = nLeftSpace-ML;
            mLineY = i*MainSpace+nTopSpace;
            sText = GetText(yMin,yMax,nYmain,yPointCount,1,i,nType);
            pText = new QSimpleTextItem(rect,sText);
            pText = DrawTrendText(pText,i,mLineX,mLineY,sText,nFontSizeY,
                                  mAGColorY,1);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pGroup->addToGroup(pText);
        }
    }

    for(i = 1; i < nVal;i++) //画次刻度
    {
        if(i%nYsub != 0  && nYsub != 0)
        {
            //画Y轴次刻度
            if(bIfShowY)
            {
                QPainterPath mPath;               //生成线的path
                mMoveX = nLeftSpace-ML/2;
                mMoveY = i*SubSpace+nTopSpace;
                mLineX = nLeftSpace;
                mLineY = i*SubSpace+nTopSpace;
                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mAGColorY); //线条颜色
                pLine->SetName(QString("YSubScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pGroup->addToGroup(pLine);
            }

            //画Y轴次格线
            if(bIfShowGridY) //是否显示格线
            {
                QPainterPath mPath1;               //生成线的path
                mMoveX = nLeftSpace;
                mMoveY = i*SubSpace+nTopSpace;
                mLineX = nLeftSpace+nBGW;
                mLineY = i*SubSpace+nTopSpace;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath1);
                pLine->setLineType(3);
                pLine->setLineColor(mGridColorY); //线条颜色
                pLine->SetName(QString("YSubLine%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pGroup->addToGroup(pLine);
            }
        }
    }
    /*****************************************************************
   *开始画笔
   ****************************************************************/
    double YPenSpace = nBGH/8; //Y轴方向每条笔之间的间隔
    double XPenSpace = nBGW/4; //X轴方向每条笔之间的间隔
    QFoldLineItem *pPenLine;

    for(j = 0;j < nPenCount;j++)
    {
        QPainterPath mPenPath = QPainterPath();
        if(j <= 3)
            mPenPath.moveTo(QPointF(nLeftSpace,nTopSpace+nBGH-j*YPenSpace));//第一点
        else
            mPenPath.moveTo(QPointF(nLeftSpace,nTopSpace+(7-j)*YPenSpace));
        for(i = 1; i <= 4;i++)
        {
            if(i == 1 || i == 3)
            {
                if(j <= 3)
                    mPenPath.lineTo(QPointF(nLeftSpace+i*XPenSpace,
                                            nTopSpace+j*YPenSpace));
                else
                    mPenPath.lineTo(QPointF(nLeftSpace+i*XPenSpace,
                                            nTopSpace+(j+1)*YPenSpace)); //+nBGH
            }
            else if(i == 2 || i == 4)
            {
                if(j <= 3)
                    mPenPath.lineTo(QPointF(nLeftSpace+i*XPenSpace,
                                            nTopSpace+nBGH-j*YPenSpace));
                else
                    mPenPath.lineTo(QPointF(nLeftSpace+i*XPenSpace,
                                            nTopSpace+(7-j)*YPenSpace));
            }
        }
        pPenLine = new QFoldLineItem(mPenPath);
        pPenLine->setLineType(nLineType[j]);
        pPenLine->setLineColor(mPenColor[j]); //线条颜色
        pPenLine->SetName(QString("PenLine%1").arg(j));
        pPenLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pGroup->addToGroup(pPenLine);
    }

    return pGroup;
}

/***************************************************************
 *函数名称：GetText
 *函数功能：画趋势图、XY趋势图以及历史趋势图中X轴和Y轴中的文本函数
 *参数含义：
 *Min：轴上的最小值
 *Max：轴上的最大值
 *nMain：主刻度
 *nPointNum：小数位数
 *nType：标示是X轴文本还是Y轴文本，0--X轴文本，1--Y轴文本
 *nIndex：主刻度下标标示
 *nKey：标示是否是历史趋势图,nKey=3表示是历史趋势图，等于1,2则不是
 *返回值：返回一个计算好的文本
 *edit by zqh
 **************************************************************/
QString QDrawGraphics::GetText(double Min, double Max, int nMain,
                               int nPointNum, int nType, int nIndex,
                               int nKey)
{
    double mValue = (Max - Min) / nMain ;
    double dVal = 0;
    QString sText = "";

    if(nKey == 1 || nKey == 2 || nKey == 4)//是趋势图和XY趋势图
    {
        if(nType == 0)     //求X轴显示的文本，大小从左到右
        {
            dVal = Min + mValue*nIndex;
            if(nIndex == nMain)
                dVal = Max;
        }
        else if(nType == 1)//求Y轴显示的文本，大小从下到上
        {
            dVal = Max - mValue*nIndex;
            if(nIndex == nMain)
                dVal = Min;
        }
        //sText.sprintf("%.0f", dVal);
		sText = sText.number(dVal,'f',nPointNum);

    }
    else if(nKey == 3) //是历史趋势图
    {
        if(nType == 0)     //求X轴显示的文本，大小从左到右
        {
            QString strHour, strMin, strSec;
            int nStepSeconds = Max/nMain+0.5;
            int nHour, nMin, nSec;
            int nSpan = nStepSeconds*nIndex;
            nHour = (nSpan / 3600) % 24;    //计算单个时间段的小时数0~23
            nSpan = nSpan % 3600;
            nMin = nSpan / 60;              //计算单个时间段的分钟数
            nSec = nSpan % 60;              //计算单个时间段的秒数
            //格式化小时、分钟和秒，小于10则补零
            if (nHour < 10)
                strHour.sprintf("0%d",nHour);
            else
                strHour.sprintf("%d",nHour);

            if (nMin < 10)
                strMin.sprintf("0%d",nMin);
            else
                strMin.sprintf("%d",nMin);

            if (nSec < 10)
                strSec.sprintf("0%d",nSec);
            else
                strSec.sprintf("%d",nSec);

            if (Min == 0)
            {
                sText = strHour+":"+strMin;
            }
            else if (Min == 1)
            {
                sText = strHour+":"+strMin+":"+strSec;
            }
        }
        else if(nType == 1)//求Y轴显示的文本，大小从下到上
        {
            dVal = Max - mValue*nIndex;
            if(nIndex == nMain)
                dVal = Min;
            if(dVal == -0)
                dVal = 0;
            //sText.sprintf("%.0f", dVal);
            sText = sText.number(dVal,'f',nPointNum);

        }
    }
    return sText;
}

/***************************************************************
 *函数名称：DrawTrendText
 *函数功能：画趋势图、XY趋势图以及历史趋势图中X轴和Y轴中的文本函数
 *参数含义：
 *pText：文本类指针
 *nIndex：主刻度下标标示
 *LineX：刻度文本所在的X坐标
 *LineY：刻度文本所在的Y坐标
 *sText：要计算的文本内容
 *nFontSize：文本的字体大小
 *pText：文本对象
 *mTextColor：字体颜色
 *nType：标示是X轴文本还是Y轴文本，0--X轴文本，1--Y轴文本
 *返回值：返回文本指针
 *edit by zqh
 **************************************************************/
QSimpleTextItem * QDrawGraphics::DrawTrendText(QSimpleTextItem *pText,
                                               int nIndex, double LineX, double LineY,
                                               QString sText, int nFontSize,
                                               QColor mTextColor,int nTtype)
{
    QString sName = "";
    pText->SetFontSize(nFontSize);
    QFont nfont = pText->GetTextFont(); //设置文本外框的大小
    nfont.setPointSize(nFontSize);
    QFontMetrics fontM(nfont);
    QRect rc = fontM.boundingRect(sText);

    QRectF rect(QPointF(0,0), QSize(50,50));
    rect.setSize(QSize(rc.width()+5,rc.height()));
    pText->setRect(rect);

    sName = QString("%1").arg(nIndex);
    if(nTtype == 0)
    {
        pText->setPos(LineX-rc.width()/2-2,LineY+4);
        sName = "HTxt"+sName;
    }
    else
    {
        pText->setPos(LineX-rc.width()-4,LineY-rc.height()/2);
        sName = "VTxt"+sName;
    }
    pText->SetFontColor(mTextColor);  
    pText->SetName(sName);
    pText->SetRectOutLine(false);
    return pText;
}

/***************************************************************
 *函数名称：drawHisTrendDate
 *函数功能：画历史趋势图X轴上的日期函数
 *参数含义：
 *nIndex：主刻度下标标示
 *LineX：刻度文本所在的X坐标
 *LineY：刻度文本所在的Y坐标
 *sText：日期
 *nFontSize：文本的字体大小
 *mTextColor：字体颜色
 *返回值：返回文本指针
 *edit by zqh
 *edit time:2011.8.17
 **************************************************************/
QSimpleTextItem * QDrawGraphics::drawHisTrendDate(int nIndex, double LineX, double LineY, QString sText, int nFontSize,
                                                  QColor mTextColor, bool haveTime)
{
    QRectF Rect(QPointF(0,0), QSize(10,10));     //背景矩形框480,250
    QSimpleTextItem *pText = new QSimpleTextItem(Rect,sText);
    QString sName = "";
    pText->SetFontSize(nFontSize);
    QFont nfont = pText->GetTextFont(); //设置文本外框的大小
    nfont.setPointSize(nFontSize);
    QFontMetrics fontM(nfont);
    QRect rc = fontM.boundingRect(sText);

    QRectF rect(QPointF(0,0), QSize(50,50));
    rect.setSize(QSize(rc.width()+5,rc.height()));
    pText->setRect(rect);

    if(haveTime)
    {
        pText->setPos(LineX-rc.width()/2-2,LineY+4+rc.height()+2);
    }
    else
    {
        pText->setPos(LineX-rc.width()/2-2,LineY+4/*-rc.height()*/+2);
    }

    pText->SetFontColor(mTextColor);
    sName = QString("%1").arg(nIndex);
    sName = "Date"+sName;
    pText->SetName(sName);
    pText->SetRectOutLine(false);
    return pText;
}

/***************************************************************
 *函数名称：DrawSlider
 *函数功能：画滑动模拟量开关图形函数
 *sList所含内容含义：
 *0：背景色
 *1：滑轨颜色
 *2：指标背景色
 *3：指标边框色
 *4：刻度位置  1--上；2--下；3--左；4--右
 *5：标示方向  0--向左（向上）；1--向右（向下）
 //刻度页面
 *6：是否显示
 *7：刻度字体颜色
 *8：主刻度
 *9：次刻度
 *10：是否显示轴
 *11：是否显示刻度标示
 *12：字体大小
 *13：最小值
 *14：最大值
 *15：小数位数
 *返回值：返回一个组合指针
 *edit by zqh
 *Date:2011-02-17
 **************************************************************/
QItemGroup* QDrawGraphics::DrawSlider(QStringList sList)
{
    //以下是变量的定义
    QColor BackColor = pwnd->StringTOColor(sList.at(0));//背景色
    QColor LineColor = pwnd->StringTOColor(sList.at(1));//滑轨颜色
    QColor BkColor = pwnd->StringTOColor(sList.at(2));  //指标背景色
    QColor FrmColor = pwnd->StringTOColor(sList.at(3)); //指标边框色

    int nPos = sList.at(4).toInt();     //刻度位置
    int nDirect = sList.at(5).toInt();  //标示方向
    bool bIfShow = sList.at(6).toInt(); //是否显示
    QColor mColor = pwnd->StringTOColor(sList.at(7)); //刻度字体颜色
    int nMain = sList.at(8).toInt();    // 主刻度
    int nSub = sList.at(9).toInt();     // 次刻度
    bool bIfShowZ = sList.at(10).toInt();     // 是否显示轴
    bool bIfShowM = sList.at(11).toInt();     // 是否显示刻度标示
    int nFontSize = sList.at(12).toInt();     //字体大小
    double Min = sList.at(13).toDouble();     //最小值
    double Max = sList.at(14).toDouble();     //最大值
    int nNum = sList.at(15).toDouble();       //小数位数

    double RectW = 148.0;  //背景矩形的宽度108.0
    int nRectH = 32;       //背景矩形的高度
    int nSpace = 10;        //滑轨偏离背景矩形边框的距离

    QPainterPath mPath;               //生成线的path
    double mMoveX = 0;                //主刻度X起始点
    double mLineY = 0;                //主刻度Y起始点
    QItemGroup *pGroup = new QItemGroup;
    QLineItem *pLine;
    int i = 0;
    double nLineW = RectW-2*nSpace;
    double MainSpace = nLineW/(nMain-1);           //主刻度间隔
    double SubSpace = nLineW/((nSub+1)*(nMain-1)); //次刻度间隔
    int ML = 10;                                  //主刻度线的长度
    int nVal = (nSub+1)*(nMain-1);

    QSimpleTextItem *pText;
    QRectItem *pFramRect;
    QLineItem *pMainLine;
    QPolygonItem *pPolyPointer;
    QLineItem *pZLine;

    QString sText = "";
    QRectF rect(QPointF(0,0), QSize(50,50));
    int nH = 0;
    int nL = 0;//80
    int nTop = 4; //边框到指标指尖的距离
    int nTextW = 0; //文本的宽度

    QVector <QPoint>mAngle;
    QPoint p1,p2,p3,p4,p5;

    //开始画背景矩形
    if(nPos == 1 || nPos == 2) //刻度位置  1--上；2--下；3--左；4--右
    {
        rect.setTopLeft(QPointF(nL,nH));
        rect.setSize(QSizeF(RectW,nRectH)); //绘制边框色矩形框

        mPath.moveTo(nL+nSpace,nH+nRectH/2);
        mPath.lineTo(nL+nSpace+RectW-2*nSpace,nH+nRectH/2);
    }
    else if(nPos == 3 || nPos == 4)
    {
        rect.setTopLeft(QPointF(nL,nH));
        rect.setSize(QSizeF(nRectH,RectW)); //绘制边框色矩形框

        mPath.moveTo(nL+nRectH/2,nH+nSpace);
        mPath.lineTo(nL+nRectH/2,nH+nSpace+nLineW);
    }

    pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(BackColor);
    pFramRect->SetLineType(0);
    pFramRect->SetName("mFramRect");
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->addToGroup(pFramRect);           //添加到组

    //绘制滑轨直线
    pMainLine = new QLineItem(mPath);        //画细直线
    pMainLine->setLineColor(LineColor);      //设置直线颜色
    pMainLine->SetName("MainLine");          //设置名称
    pMainLine->setLineWidth(3);
    pMainLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->addToGroup(pMainLine);           //添加到组

    //绘制指标
    if(nPos == 1)             //刻度的方向向上
    {
        if(nDirect == 0)      //文本标识的方向向左
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nSpace+nLineW); p1.setY(nH+nTop);
            p2.setX(nL+nSpace/2+nLineW);p2.setY(nH+nRectH/4);
            p3.setX(nL+nSpace/2+nLineW);p3.setY(nH+3*nRectH/4);
            p4.setX(nL+3*nSpace/2+nLineW);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2+nLineW);p5.setY(nH+nRectH/4);
        }
        else if(nDirect == 1) //文本标识的方向向右
        {
            p1.setX(nL+nSpace); p1.setY(nH+nTop);
            p2.setX(nL+nSpace/2);p2.setY(nH+nRectH/4);
            p3.setX(nL+nSpace/2);p3.setY(nH+3*nRectH/4);
            p4.setX(nL+3*nSpace/2);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2);p5.setY(nH+nRectH/4);
        }
    }
    else if(nPos == 2)        //刻度的方向向下
    {
        if(nDirect == 0)      //文本标识的方向向左
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nSpace/2+nLineW); p1.setY(nH+nRectH/4);
            p2.setX(nL+nSpace/2+nLineW);p2.setY(nH+3*nRectH/4);
            p3.setX(nL+nSpace+nLineW);p3.setY(nH+nRectH-nTop);
            p4.setX(nL+3*nSpace/2+nLineW);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2+nLineW);p5.setY(nH+nRectH/4);
        }
        else if(nDirect == 1) //文本标识的方向向右
        {
            p1.setX(nL+nSpace/2); p1.setY(nH+nRectH/4);
            p2.setX(nL+nSpace/2);p2.setY(nH+3*nRectH/4);
            p3.setX(nL+nSpace);p3.setY(nH+nRectH-nTop);
            p4.setX(nL+3*nSpace/2);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2);p5.setY(nH+nRectH/4);
        }
    }
    else if(nPos == 3)        //刻度的方向向左
    {
        if(nDirect == 0)      //文本标识的方向向上
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nTop); p1.setY(nH+nSpace+nLineW);
            p2.setX(nL+nRectH/4);p2.setY(nH+nSpace/2+nLineW);
            p3.setX(nL+3*nRectH/4);p3.setY(nH+nSpace/2+nLineW);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2+nLineW);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2+nLineW);
        }
        else if(nDirect == 1) //文本标识的方向向下
        {
            p1.setX(nL+nTop); p1.setY(nH+nSpace);
            p2.setX(nL+nRectH/4);p2.setY(nH+nSpace/2);
            p3.setX(nL+3*nRectH/4);p3.setY(nH+nSpace/2);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2);
        }
    }
    else if(nPos == 4)        //刻度的方向向右
    {
        if(nDirect == 0)      //文本标识的方向向上
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nRectH/4); p1.setY(nH+nSpace/2+nLineW);
            p2.setX(nL+3*nRectH/4);p2.setY(nH+nSpace/2+nLineW);
            p3.setX(nL+nRectH-nTop);p3.setY(nH+nSpace+nLineW);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2+nLineW);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2+nLineW);
        }
        else if(nDirect == 1) //文本标识的方向向下
        {
            p1.setX(nL+nRectH/4); p1.setY(nH+nSpace/2);
            p2.setX(nL+3*nRectH/4);p2.setY(nH+nSpace/2);
            p3.setX(nL+nRectH-nTop);p3.setY(nH+nSpace);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2);
        }
    }
    mAngle.append(p1);
    mAngle.append(p2);
    mAngle.append(p3);
    mAngle.append(p4);
    mAngle.append(p5);
    QPolygonF mAnglePoly(mAngle);
    pPolyPointer = new QPolygonItem(mAnglePoly);   //画菱形指针
    pPolyPointer->setLineType(1);
    pPolyPointer->setBackColor(BkColor);
    pPolyPointer->setLineColor(FrmColor);
    pPolyPointer->SetName("Pointer");                 //设置名称
    pGroup->addToGroup(pPolyPointer);

    //绘制主次刻度即文本
    nLineW = RectW-2*nSpace;

    if(bIfShow)
    {
        switch(nPos)
        {
        case 1://方向向上3
            if(bIfShowZ)//显示轴
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace,nH);
                mPath.lineTo(nL+nSpace+nLineW,nH);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //轴颜色
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace+i*MainSpace,-ML+nH);
                mPath.lineTo(nL+nSpace+i*MainSpace,nH);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //线条颜色
                pLine->SetName(QString("SubLine%1").arg(i));
                pGroup->addToGroup(pLine);

                mMoveX = nL+nSpace+i*MainSpace;
                if(bIfShowM)
                {
                    sText = GetSliderText(i,Min,Max,nMain,nDirect,nNum);
                    pText = new QSimpleTextItem(rect,sText);
                    nTextW = GetTextLength(sText,pText,nFontSize);
                    pText = DrawSliderText(pText,i,mMoveX-nTextW/2-2,-ML+nH-13,
                                           sText,nFontSize,mColor);
                    pGroup->addToGroup(pText);
                }
            }
            for(i = 1; i < nVal;i++) //画次刻度
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(nL+nSpace+i*SubSpace,-ML/2+nH);
                    mPath.lineTo(nL+nSpace+i*SubSpace,nH);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //线条颜色
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 2://方向向下4
            if(bIfShowZ)//显示轴
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace,nH+nRectH);
                mPath.lineTo(nL+nSpace+nLineW,nH+nRectH);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //轴颜色
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace+i*MainSpace,nH+nRectH);
                mPath.lineTo(nL+nSpace+i*MainSpace,ML+nH+nRectH);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //线条颜色
                pLine->SetName(QString("SubLine%1").arg(i));
                pGroup->addToGroup(pLine);

                mMoveX = nL+nSpace+i*MainSpace;
                mLineY = ML+nH+nRectH;
                if(bIfShowM)
                {
                    sText = GetSliderText(i,Min,Max,nMain,nDirect,nNum);
                    pText = new QSimpleTextItem(rect,sText); //rect,
                    nTextW = GetTextLength(sText,pText,nFontSize);
                    pText = DrawSliderText(pText,i,mMoveX-nTextW/2-2,mLineY+4,
                                           sText,nFontSize,mColor);
                    pGroup->addToGroup(pText);
                }
            }
            for(i = 1; i < nVal;i++) //画次刻度
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(nL+nSpace+i*SubSpace,nH+nRectH);
                    mPath.lineTo(nL+nSpace+i*SubSpace,ML/2+nH+nRectH);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //线条颜色
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 3://方向向左
            if(bIfShowZ)//显示轴
            {
                QPainterPath mPath;
                mPath.moveTo(nL,nH+nSpace);
                mPath.lineTo(nL,nH+nSpace+nLineW);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //轴颜色
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(-ML+nL,nH+nSpace+i*MainSpace);
                mPath.lineTo(nL,nH+nSpace+i*MainSpace);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //线条颜色
                pLine->SetName(QString("MLine%1").arg(i));
                pGroup->addToGroup(pLine);

                mMoveX = -ML+nL;
                mLineY = nH+nSpace+i*MainSpace;
                if(bIfShowM)
                {
                    sText = GetSliderText(i,Min,Max,nMain,nDirect,nNum);
                    pText = new QSimpleTextItem(rect,sText); //rect,
                    nTextW = GetTextLength(sText,pText,nFontSize);
                    pText = DrawSliderText(pText,i,mMoveX-nTextW-4,mLineY-6,
                                           sText,nFontSize,mColor);
                    pGroup->addToGroup(pText);
                }
            }
            for(i = 1; i < nVal;i++) //画次刻度
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(-ML/2+nL,nH+nSpace+i*SubSpace);
                    mPath.lineTo(nL,nH+nSpace+i*SubSpace);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //线条颜色
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 4://方向向右2
            if(bIfShowZ)//显示轴
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nRectH,nH+nSpace);
                mPath.lineTo(nL+nRectH,nH+nSpace+nLineW);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //轴颜色
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nRectH,nH+nSpace+i*MainSpace);
                mPath.lineTo(ML+nL+nRectH,nH+nSpace+i*MainSpace);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //线条颜色
                pLine->SetName(QString("SubLine%1").arg(i));
                pGroup->addToGroup(pLine);

                mMoveX = ML+nL+nRectH;
                mLineY = nH+nSpace+i*MainSpace;
                if(bIfShowM)
                {
                    sText = GetSliderText(i,Min,Max,nMain,nDirect,nNum);
                    pText = new QSimpleTextItem(rect,sText); //rect,
                    pText = DrawSliderText(pText,i,mMoveX+4,mLineY-6,sText,
                                           nFontSize,mColor);
                    pGroup->addToGroup(pText);
                }
            }
            for(i = 1; i < nVal;i++) //画次刻度
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(nL+nRectH,nH+nSpace+i*SubSpace);
                    mPath.lineTo(ML/2+nL+nRectH,nH+nSpace+i*SubSpace);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //线条颜色
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
         default:
            break;
        } //end switch
    } //end if
    return pGroup;
}

QString QDrawGraphics::GetSliderText(int nIndex, double Min, double Max,
                                     int nMain, int nTextDirection,
                                     int nPointNum)
{
    double mValue = (Max - Min) / (nMain - 1);
    double dVal = 0;
    QString sText = "";

    if(nTextDirection == 0) //文本向左
    {
        dVal = Max - mValue*nIndex;
        if(nIndex == nMain-1)
            dVal = Min;
    }
    else                   //文本向右
    {
        dVal = Min + mValue*nIndex;
        if(nIndex == nMain-1)
            dVal = Max;
    }
    if(dVal == -0)
        dVal = 0;
    sText.sprintf("%.0f", dVal);
    QString sTemp = "";
    if(nPointNum != 0)
    {
        sTemp = sText.left(1);
        if(sTemp == "-") //是负数的时候
        {
            sTemp = sText.right(sText.length()-1); //取除去负号的数据
            while(sTemp.length()-nPointNum <= 0)
                  sTemp = "0"+sTemp;
              sTemp = sTemp.insert(sTemp.length()-nPointNum,".");
              sText = "-"+sTemp;
        }
        else
        {
               while(sText.length()-nPointNum <= 0)
                     sText = "0"+sText;
                 sText = sText.insert(sText.length()-nPointNum,".");
        }
    }
//    if(nPointNum != 0)
//    {
//        while(sText.length()-nPointNum <= 0)
//            sText = "0"+sText;
//        sText = sText.insert(sText.length()-nPointNum,".");
//    }
    //sText.sprintf("%.*f", nPointNum, dVal);
    return sText;
}

int QDrawGraphics::GetTextLength(QString sText, QSimpleTextItem *pText,
                                 int nFontSize)
{
    QFont nfont = pText->GetTextFont(); //设置文本外框的大小
    nfont.setPointSize(nFontSize);
    QFontMetrics fontM(nfont);
    QRect rc = fontM.boundingRect(sText);
    return rc.width();
}

QSimpleTextItem* QDrawGraphics::DrawSliderText(QSimpleTextItem *pText,
                                               int nIndex, double LineX, double LineY,
                                               QString sText, int nFontSize,QColor mTextColor)
{
    QString sName = "";

    pText->SetFontSize(nFontSize);
    QFont nfont = pText->GetTextFont(); //设置文本外框的大小
    nfont.setPointSize(nFontSize);
    QFontMetrics fontM(nfont);
    QRect rc = fontM.boundingRect(sText);

    QRectF rect(QPointF(0,0), QSize(50,50));
    rect.setSize(QSize(rc.width()+5,rc.height()));
    pText->setRect(rect);
    pText->setPos(LineX,LineY);
    pText->SetFontColor(mTextColor);
    sName = QString("%1").arg(nIndex);
    sName = "Txt"+sName;
    pText->SetName(sName);
    pText->SetRectOutLine(false);
    return pText;
}

/***************************************************************
 *函数名称：drawRecipeSelect
 *函数功能：画配方选择器函数
 *参数含义：
 *pList：存储信息
 *edit by zqh
 *edit time:2011.8.18
 **************************************************************/
QItemGroup* QDrawGraphics::drawRecipeSelect(QStringList *pList)
{
    QColor mBkColor = pwnd->StringTOColor(pList->at(43));         //背景颜色
    int nHNum = pList->at(45).toInt();           //行数
    int nType = pList->at(40).toInt(); //0表示列表，1表示下拉框

    double mMoveX = 0;                //主刻度X起始点
    double mMoveY = 0;                //主刻度Y起始点
    double mLineX = 0;                //主刻度X起始点
    double mLineY = 0;                //主刻度Y起始点
    QItemGroup *pGroup = new QItemGroup;
    QLineItem *pLine;
    int i = 0;
    int WH = 100;
    double HVal = 100.0/nHNum;
    QString str = "";

    QRectF rect(QPointF(0,0), QSize(WH,WH));        //绘制边框色矩形框
    QRectItem *pRect = NULL;

    if(nType == 0) //列表
    {
        pRect = new QRectItem(rect);
        pRect->SetBackColor(mBkColor);                    //设置背景色
        pRect->SetName("mRect");
        pGroup->addToGroup(pRect);

        /*********************************************************************
     *以下是画水平格线
     ********************************************************************/
        for(i = 1; i < nHNum; i++)
        {
            QPainterPath mPath;
            mMoveX = 0;
            mMoveY = i*HVal;
            mLineX = WH;
            mLineY = i*HVal;
            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);
            pLine = new QLineItem(mPath);
            str = QString("%1").arg(i);
            str = "HLine"+str;
            pLine->SetName(str);
            pGroup->addToGroup(pLine);
        }
    }
    else if(nType == 1) //下拉框列表
    {
        rect.setSize(QSize(108,18));//绘制外框矩形
        pRect = new QRectItem(rect);//QRectItem *
        pRect->SetLineColor(QColor(127,157,185));
        pRect->SetPattern(1);
        pRect->SetBackColor(mBkColor);
        pRect->SetName("mFramRect");
        pRect->setZValue(1);
        pGroup->addToGroup(pRect);
        pRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

        rect.setTopLeft(QPointF(84,0));               //绘制背景矩形框
        rect.setSize(QSize(24,18));
        QRectItem *pBackRect = new QRectItem(rect);
        pBackRect->SetBackColor(QColor(183,211,252));
        pBackRect->SetLineType(0);
        pBackRect->SetName("mBackRect");
        pBackRect->setZValue(2);
        pGroup->addToGroup(pBackRect);
        pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QFoldLineItem *pLine;
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
        pGroup->addToGroup(pLine);
        pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }

    pGroup->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->setFlag(QGraphicsItem::ItemIsMovable, false);

    return pGroup;
}

/***************************************************************
 *函数名称：drawRecipeDisplay
 *函数功能：画配方显示器函数
 *参数含义：
 *pList：存储信息
 *edit by zqh
 *edit time:2011.8.20
 **************************************************************/
QItemGroup* QDrawGraphics::drawRecipeDisplay(QStringList *pList)
{
    int i = 0;
    double mMoveX = 0;                //主刻度X起始点
    double mMoveY = 0;                //主刻度Y起始点
    double mLineX = 0;                //主刻度X起始点
    double mLineY = 0;                //主刻度Y起始点
    int nUseCount = 0;                //数据页面显示的条数

    QItemGroup *pGroup = new QItemGroup;
    /**************************取一般页面画图的属性*****************************/
    QColor mFBackcolor = pwnd->StringTOColor(pList->at(20));          //框架的背景色
    QColor mFBorderColor = pwnd->StringTOColor(pList->at(21));    //框架的边框色

    int iLan = pwnd->qLanguagecmb->currentIndex();
    if(iLan < 0)
        iLan = 0;

    int nTFontSize = pList->at(35+iLan*3).toInt();              //以语言1字体大小 35
    QString sTFont = pList->at(36+iLan*3);                  //以语言1的字体36
    QColor mTBackColor = pwnd->StringTOColor(pList->at(25));        //标题列背景色
    QColor mTTextColor = pwnd->StringTOColor(pList->at(26));         //标题列的文本颜色

    QString sNo = pList->at(37+iLan*3); //37
    int nRow = pList->at(27).toInt();                 //行数
   // int nType = pList->at(24).toInt(); //0水平选择  1垂直选择

    double nH = 25;       //每格的高度 10
    double nW = 480;      //背景框的总宽度120
    double nTexeW = 0;   //文本的宽度120
    QString sName = "";
    QLineItem *pLine;
    QSimpleTextItem *pText;
    QStringList sDataName;

    /**************************画背景矩形*****************************/
    QRectF rect(QPointF(0,0), QSize(nW,(nRow+1)*nH));     //绘制背景矩形
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(mFBackcolor);             //背景框的背景色
    pFramRect->SetLineColor(mFBorderColor);           //背景框的边框色
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetName("mFramRect");
    pGroup->addToGroup(pFramRect);                    //添加到组

    /**************************画标题列******************************/
    rect.setWidth(nW);                                //绘制标题列
    rect.setHeight(nH);
    QRectItem *pTitleRect = new QRectItem(rect);
    pTitleRect->SetBackColor(mTBackColor);            //标题列矩形框背景色
    pTitleRect->SetLineType(0);
    pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTitleRect->SetName("mTitleRect");
    pGroup->addToGroup(pTitleRect);                   //添加到组

    /**************************画标题文本*****************************/
    sDataName.clear();
    sDataName.append(sNo);
    nUseCount++;
    int nIndex = 100;
    int nVal = 0;
    for(i = 0;i < pwnd->m_pSamSysParame->m_recipeProp.nRecipeTotalNum;i++) //RowHeadName[0].size()
    {
        nVal = pList->at(nIndex).toInt();
        if(nVal == 1)
        {
            nUseCount++;
            sDataName.append(pwnd->m_pSamSysParame->m_recipeProp.sRowHeadName[iLan].at(i));//0
        }
        nIndex++;
    }

    nTexeW = nW/nUseCount; //文本平均宽度
    for(i = 0; i < nUseCount;i++)
    {
        rect.setTopLeft(QPointF(i*nTexeW,0));           //绘制文本pText
        rect.setSize(QSize(nTexeW,nH));
        pText = new QSimpleTextItem(rect,sDataName.at(i));
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(sTFont);
        pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName(QString("Text%1").arg(i));
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pGroup->addToGroup(pText);                   //添加到组
    }

    /**************************画水平线******************************/
  //  if(bIfHorizon)   //选中了水平选择框
   // {
        for(i = 0; i < nRow; i++)
        {
            QPainterPath mPath;
            mMoveX = 0;
            mMoveY = i*nH+nH;
            mLineX = 0+nW;
            mLineY = i*nH+nH;
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "HLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //添加到组
        }
   // }
    /**************************画垂直线******************************/
  //  if(bIfVertical)  //选中了垂直
 //   {
        for(i = 1; i < nUseCount; i++)
        {
            QPainterPath mPath;
            mMoveX = nTexeW*i;
            mMoveY = 0;
            mLineX = nTexeW*i;
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "VLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //添加到组
        }
 //   }
    return pGroup;
}

/************************************************************************
  *函数名称：drawHistroyDataDisplayItem
  *函数功能：绘制历史数据显示器控件函数
  *参数含义：
  *pList:刻度属性信息
  *pTree:指向转换后的树形控件模块类得指针
  *返回值:返回绘制后的历史数据显示器控件item
  *edit by zqh
  *2011-9-27
************************************************************************/
QGraphicsItem* QDrawGraphics::drawHistroyDataDisplayItem(QStringList *pList)
{
    int i = 0;
    int nVal = 0;
    double mMoveX = 0;                //主刻度X起始点
    double mMoveY = 0;                //主刻度Y起始点
    double mLineX = 0;                //主刻度X起始点
    double mLineY = 0;                //主刻度Y起始点
    int nUseCount = 0;                //数据页面显示的条数

    QItemGroup *pGroup = new QItemGroup;
    /**************************取一般页面画图的属性*****************************/
    QColor mFBackcolor = pwnd->StringTOColor(pList->at(21));   //框架的背景色
    QColor mFBorderColor = pwnd->StringTOColor(pList->at(22));    //框架的边框色
    bool bIfVertical = pList->at(27).toInt();  //是否垂直显示
    bool bIfHorizon = pList->at(28).toInt();//是否水平
    QColor mLineColor = pwnd->StringTOColor(pList->at(23));          //格线颜色

    //int nLanguageCount = pGeneralDlg->ui->m_languagecmb->count();      //语言总数
    nVal = 10;//pGeneralDlg->TitleText[0].nFontSize;
//    for(i = 1;i < nLanguageCount;i++)                                  //求最大的字体大小
//    {
//        if(nVal <  pGeneralDlg->TitleText[i].nFontSize)
//            nVal =  pGeneralDlg->TitleText[i].nFontSize;
//    }
    int nTFontSize = pList->at(40).toInt();//pGeneralDlg->TitleText[0].nFontSize;              //以语言1字体大小
    QString sTFont = pList->at(41);//"System";//pGeneralDlg->TitleText[0].sFont;                  //以语言1的字体
    QColor mTBackColor = pwnd->StringTOColor(pList->at(24));         //标题列背景色
    QColor mTTextColor = pwnd->StringTOColor(pList->at(25));        //标题列的文本颜色
    bool bIfTime = pList->at(31).toInt();        //是否显示时间列
    QString sTime = pList->at(42);//"Time";                   //以语言1显示时间内容
    bool bIfDate = pList->at(32).toInt();         //是否显示日期列
    QString sDate = pList->at(43);//"Date";                   //以语言1显示日期内容
    int nRow = pList->at(33).toInt();                    //行数

    double nH = 25;       //每格的高度 10
    double nW = 480;      //背景框的总宽度120
    double nTexeW = 0;   //文本的宽度120
    QString sName = "";
    QLineItem *pLine;
    QSimpleTextItem *pText;
    QStringList sDataName;

    /**************************画背景矩形*****************************/
    QRectF rect(QPointF(0,0), QSize(nW,(nRow+1)*nH));     //绘制背景矩形
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(mFBackcolor);             //背景框的背景色
    pFramRect->SetLineColor(mFBorderColor);           //背景框的边框色
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetName("mFramRect");
    pGroup->addToGroup(pFramRect);                    //添加到组

    /**************************画标题列******************************/
    rect.setWidth(nW);                                //绘制标题列
    rect.setHeight(nH);
    QRectItem *pTitleRect = new QRectItem(rect);
    pTitleRect->SetBackColor(mTBackColor);            //标题列矩形框背景色
    pTitleRect->SetLineType(0);
    pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTitleRect->SetName("mTitleRect");
    pGroup->addToGroup(pTitleRect);                   //添加到组

    /**************************画标题文本*****************************/
    sDataName.clear();
    if(bIfTime)
    {
        nUseCount++;
        sDataName.append(sTime);
    }
    if(bIfDate)
    {
        nUseCount++;
        sDataName.append(sDate);
    }

    //czq
    /*int kk = 100; //30
    for(i = 0;i < pwnd->m_pSamSysParame->m_historyLogData.nSampleLen;i++)
    {
        if(pList->at(kk).toInt()) //显示条数计数  pDataDlg->bIfUse[i]
        {
            nUseCount++;
//            int index = pGeneralDlg->ui->m_languagecmb->currentIndex();
//            if(pTree->m_pSamSysParame->m_historyLogData.mSampleList.at(i).sNameList.size() < index +1)
//            {
//                pTree->m_pSamSysParame->m_historyLogData.mSampleList[i].sNameList.resize(index +1);
//            }
            sDataName.append(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.at(i).sNameList.at(0));//存显示的名称 index
        }
        kk++;
    }*/

    nTexeW = nW/nUseCount; //文本平均宽度
    for(i = 0; i < nUseCount;i++)
    {
        rect.setTopLeft(QPointF(i*nTexeW,0));           //绘制文本pText
        rect.setSize(QSize(nTexeW,nH));
        pText = new QSimpleTextItem(rect,sDataName.at(i));
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(sTFont);
        pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName(QString("Text%1").arg(i));
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pGroup->addToGroup(pText);                   //添加到组
    }

    /**************************画水平线******************************/
    if(bIfHorizon)   //选中了水平选择框
    {
        for(i = 0; i < nRow; i++)
        {
            QPainterPath mPath;
            mMoveX = 0;
            mMoveY = i*nH+nH;
            mLineX = 0+nW;
            mLineY = i*nH+nH;
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            pLine->setLineColor(mLineColor);     //设置直线颜色
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "HLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //添加到组
        }
    }
    /**************************画垂直线******************************/
    if(bIfVertical)  //选中了垂直
    {
        for(i = 1; i < nUseCount; i++)
        {
            QPainterPath mPath;
            mMoveX = nTexeW*i;
            mMoveY = 0;
            mLineX = nTexeW*i;
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            pLine->setLineColor(mLineColor);     //设置直线颜色
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "VLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //添加到组
        }
    }
    return pGroup;
}

//计算X轴时间刻度并返回
QString QDrawGraphics::GetTimeText(QDateTime tStart, QDateTime tEnd, int nMain,
							   int nIndex,int format,int nType)
{
	QDateTime datetime;
	QString sformat;

	QStringList dateFormats;
    dateFormats << ("yyyy/MM/dd")
		<<("yyyy.MM.dd")
		<<("yyyy-MM-dd")
        <<("MM/dd/yyyy")
		<<("MM.dd.yyyy")
		<<("MM-dd-yyyy")
        <<("dd/MM/yyyy")
		<<("dd.MM.yyyy")
		<<("dd-MM-yyyy");
	QStringList timeFormats;

	timeFormats << ("hh:mm")
		<<("hh:mm:ss")
		<<("hh-mm")
		<<("hh-mm-ss");

	float nstep = (float)tStart.secsTo(tEnd)/nMain;
	
	int nSecond = nstep*nIndex;

	datetime = tStart.addSecs(nSecond);
	if (nMain == nIndex)
	{
		datetime = tEnd;
	}
	if (nType == 1)// 返回时间
	{
		if (timeFormats.size() >format)
		{
			sformat = timeFormats.at(format);
		}
		else
			sformat = timeFormats.first();

		QTime time = datetime.time();

		return time.toString(sformat);
	}
	else          //返回日期
	{
		if (dateFormats.size() >format)
		{
			sformat = dateFormats.at(format);
		}
		else
			sformat = dateFormats.first();

		QDate date = datetime.date();
		return date.toString(sformat);
	}
}
void QDrawGraphics::getDateTime(QTrendAttr *pItem,QDateTime &tStart,QDateTime &tEnd)
{
	tStart = QDateTime::currentDateTime();
	tEnd = tStart;
	if (!pItem)
	{
		return ;
	}
	int nSecond = 0;
	int times = 60;
	switch (pItem->m_eStart)
	{
	case START_NEAR:
		switch (pItem->m_eTimeUnitNear)
		{
		case UNIT_MINUTE://分
			times = 60;
			break;
		case UNIT_HOUR://时
			times = 3600;
			break;
		case UNIT_DAY://日
			times = 86400;
			break;
		case UNIT_MONTH://月
			times = 2592000;
			break;
		case UNIT_YEAR://年
			times = 31104000;
			break;
		}
		nSecond = pItem->m_nTimeLen * times;
		tEnd = tStart.addSecs(nSecond);
		break;
	case START_FROMTO:
		tStart = QDateTime(pItem->m_dFromDate,pItem->m_tFromTime);
		tEnd = QDateTime(pItem->m_dToDate,pItem->m_tToTime);
		break;
	case START_DISKBEGIN:
		nSecond = pItem->m_nTimeLen * times;
		tEnd = tStart.addSecs(nSecond);
		break;
	}
	qDebug() << tEnd.toString();
	qDebug() << tStart.toString();
}
