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
 *�������ƣ�OnDrawRectAndText(QGraphicsScene *pScene)
 *�������ܣ�����ֻ��һ��״̬��ͼ��
 *�������壺
 *pScene���ѻ��õ�ͼ����ӵ��ĳ���
 *edit by zqh
 **************************************************************/
QGraphicsItem* QDrawGraphics::OnDrawRectAndText(QGraphicsScene *pScene)
{    
    pGroup = new QItemGroup;//QGraphicsItemGroup;
    int nSpace = 4; //5
    int nWidth = 100-2*nSpace;

    QRectF rect(QPointF(0,0), QSize(100,100));     //���Ʊ߿�ɫ���ο�
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(QColor(224,224,224));
    pFramRect->SetLineType(0);
    //  pFramRect->setZValue(1);
    pFramRect->SetName("mFramRect");
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetAlpha(255);

    rect.setTopLeft(QPointF(nSpace,nSpace));       //���Ʊ������ο�
    rect.setSize(QSize(nWidth,nWidth));
    QRectItem *pBackRect = new QRectItem(rect);
    pBackRect->SetBackColor(QColor(192,192,192));
    pBackRect->SetLineType(0);
    //  pBackRect->setZValue(2);
    pBackRect->SetName("mBackRect");
    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pBackRect->SetAlpha(255);

    rect.setTopLeft(QPointF(nSpace,nSpace));           //������
    rect.setSize(QSize(nWidth,nWidth));
    QSimpleTextItem *pText = new QSimpleTextItem(rect,"");
    pText->SetName("mText");
    pText->SetRectOutLine(false);
    // pText->setZValue(4);
    pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pText->SetAlpha(255);

    pGroup->addToGroup(pFramRect);   //��ӵ���
    pGroup->addToGroup(pBackRect);
    pGroup->addToGroup(pText);

    if(pScene)
        pScene->addItem(pGroup);        //��ӵ�����

    // QList<QGraphicsItem *> Items = pScene->items();
    // QList<QGraphicsItem *> Item1 = pGroup->childItems();

    pGroup->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->setFlag(QGraphicsItem::ItemIsMovable, false);

    //  QGraphicsItem *pItem = dynamic_cast<QGraphicsItem *>(pGroup);   //��һ����ǿ��ת��ΪQGraphicsItem����

    return pGroup;
}
QList<QGraphicsItem*> QDrawGraphics::OnDrawRectAndText()
{
    QList<QGraphicsItem*> pGroup;
    int nSpace = 4; //5
    int nWidth = 100-2*nSpace;

    QRectF rect(QPointF(0,0), QSize(100,100));     //���Ʊ߿�ɫ���ο�
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(QColor(224,224,224));
    pFramRect->SetLineType(0);
    //  pFramRect->setZValue(1);
    pFramRect->SetName("mFramRect");
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    rect.setTopLeft(QPointF(nSpace,nSpace));       //���Ʊ������ο�
    rect.setSize(QSize(nWidth,nWidth));
    QRectItem *pBackRect = new QRectItem(rect);
    pBackRect->SetBackColor(QColor(192,192,192));
    pBackRect->SetLineType(0);
    //  pBackRect->setZValue(2);
    pBackRect->SetName("mBackRect");
    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    rect.setTopLeft(QPointF(nSpace,nSpace));           //������
    rect.setSize(QSize(nWidth,nWidth));
    QSimpleTextItem *pText = new QSimpleTextItem(rect,"");
    pText->SetName("mText");
    pText->SetRectOutLine(false);
    // pText->setZValue(4);
    pText->setFlag(QGraphicsItem::ItemIsSelectable, false);

    pGroup<<pFramRect;   //��ӵ���
    pGroup<<pBackRect;
    pGroup<<pText;

    return pGroup;
}

/***************************************************************
 *�������ƣ�AlterGraphics
 *�������ܣ��ڱ�ʾҳ�����ͼƬ���ߵ���ͼƬ�����ͼ����λ��
 *�������壺
 *pOldItem������������Ҫ����ͼƬ��item
 *pictrue�� �����ص�ͼƬָ��
 *nPicPosition��ͼƬ��λ��,��Χ��1-9֮�䣬  
 *ifDeletePic���Ƿ�ɾ��ͼƬ��trueΪɾ��ͼƬ��false��ɾ��
   ---(pictrue == NULL && ifDeletePic == true)��ʾɾ��ͼƬ����
   ---(pictrue == NULL && ifDeletePic == false)��ʾ����ͼƬλ�ò���
 *nBorderInterval:ͼƬ�ı߾�
 *ifFit:�Ƿ�������С
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
        newPicItem->setData(GROUP_NAME_KEY,QVariant("mLibrary"));//��������
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

        if (pLibItem->type() == SAM_DRAW_OBJECT_PIXMAP && nKey != LIBRARY_LIB_GROUP) //��ͼƬ
        {
            piclist = pLibItem->data(GROUP_DATALIST_KEY).toStringList();
            QSize picSize =QSize(rect.width(),rect.height());
            newPicItem = new QPixmapItem(*pictrue,picSize);
            pNewItem = newPicItem;
            newPicItem->setPos(rect.x(),rect.y());
            pNewItem->setData(GROUP_DATALIST_KEY,QVariant(piclist));
        }
        else if(nKey == LIBRARY_LIB_GROUP || nKey == USER_DEFINE_GROUP)//ͼ�����
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

        pNewItem->setData(GROUP_NAME_KEY,QVariant("mLibrary"));//��������
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
 *�������ƣ�SetPicPosition
 *�������ܣ��ڱ�ʾҳ�����ͼƬλ��
 *�������壺
 *pPicItem������������Ҫ����ͼƬ��item
 *nPicPosition��ͼƬ��λ��,��Χ��1-9֮�䣬
 *nBorderInterval:ͼƬ�ı߾�
 *ifFit:�Ƿ�������С
 *edit by zqh
 **************************************************************/
QRectF QDrawGraphics::SetPicPosition(QGraphicsItem *pPicItem, int nPicPosition,
                                     int nBorderInterval,bool ifFit,int nSpace,QRectF rect)
{
    if( nPicPosition < 1 || nPicPosition > 9) //λ�ò���1-9��Χ֮���˳�
        return rect;
    if(ifFit)  //ѡ����������С��ʱ�򲻴���
        return rect;

    QRectF rc;
    double nWidth = rect.width();
    double nPicWidth = nWidth/2;
    double nX = 0;
    double nY = 0;
    switch(nPicPosition)
    {
    case 1: //���϶���
        nX = nBorderInterval;
        nY = nBorderInterval;
        break;
    case 2: //�϶���
        nX = (nWidth-nPicWidth)/2;
        nY = nBorderInterval;
        break;
    case 3: //���϶���
        nX = nWidth -nPicWidth-nBorderInterval;
        nY = nBorderInterval;
        break;
    case 4: //�����
        nX = nBorderInterval;
        nY = (nWidth-nPicWidth)/2;
        break;
    case 5: //���ж���
        nX = (nWidth-nPicWidth)/2;
        nY = (nWidth-nPicWidth)/2;
        break;
    case 6: //�Ҷ���
        nX = nWidth -nPicWidth-nBorderInterval;
        nY = (nWidth-nPicWidth)/2;
        break;
    case 7: //���½Ƕ���
        nX = nBorderInterval;
        nY = nWidth -nPicWidth-nBorderInterval;
        break;
    case 8: //�ײ�����
        nX = (nWidth-nPicWidth)/2;
        nY = nWidth -nPicWidth-nBorderInterval;
        break;
    case 9: //���½Ƕ���
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
 *�������ƣ�OnDrawMeter(QGraphicsScene *pScene,int nPointerType,int nDirection)
 *�������ܣ������Ǳ�ͼ��
 *�������壺
 *pScene���ѻ��õ�ͼ����ӵ��ĳ���
 *nMeterType:�����Ǳ����ͣ�0--��Բ��1--ȫԲָ�����ϣ�2--ȫԲָ�����£�3--�ķ�֮��Բָ������
 *nPointerType:ָ�����ͣ�0--ϸֱ�ߣ�1--��ֱ�ߣ�2--���Σ�3--������
 *nDirection������0--˳ʱ�룬1--��ʱ��
 *nMainScal:  ���̶�
 *nSubScal:   �ο̶�
 *dMax:       ���ֵ
 *dMin:       ��Сֵ
 *nPointCount:С����λ��
 *nFontSize:  �����С
 *edit by zqh
 ****************************************************************************/
QGraphicsItem* QDrawGraphics::OnDrawMeter(QGraphicsScene *pScene,int nMeterType,
                                          int nPointerType,int nDirection,int nMainScal,int nSubScal,
                                          double dMax, double dMin, int nPointCount,int nFontSize)
{
    int nWidth = 100;      //Բ�Ŀ��
    int nHeight = 100;     //Բ�ĸ߶�

    pGroup = new QItemGroup;
    //pGroup = new QGraphicsItemGroup;

    QRectF mRect(QPoint(0,0),QSize(nWidth,nHeight));    //���ô�С
    QElipseItem *pCircle = new QElipseItem(mRect);      //����һ��Բ
    pCircle->SetName("mMeterCircle");                   //����Բ������

    switch(nMeterType)
    {
    case 0:  //��Բ�Ǳ�
        pCircle->SetStartAngle(0);                  //���ÿ�ʼ�Ƕ�
        pCircle->SetSpanAngle(180);                 //���ÿ��,����һ����Բ
        break;
    case 1:  //ȫԲָ������
    case 2:  //ȫԲָ������
        break;
    case 3:  //�ķ�֮��Բָ������
        pCircle->SetStartAngle(315);               //���ÿ�ʼ�Ƕ�
        pCircle->SetSpanAngle(270);                //���ÿ��,����һ���ķ�֮��Բ
        break;
    default:
        break;
    }
    pCircle->SetBackColor(QColor(0,255,255));           //���ñ���ɫ
    pCircle->setZValue(1);                              //���ò��

    QRectF mBaseRect(QPoint(nWidth/2-2,nHeight/2-2),QSize(4,4)); //����������С
    QElipseItem *pBaseCircle = new QElipseItem(mBaseRect);//��������
    pBaseCircle->SetBackColor(QColor(0,0,0));             //����������ɫ
    pBaseCircle->setZValue(2);                            //���������Ĳ��
    pBaseCircle->SetLineType(0);                          //����������ʽΪ͸��
    pBaseCircle->SetName("mPointerBase");                 //������������
    pGroup->addToGroup(pBaseCircle);                      //��ӵ���

    pGroup->addToGroup(pCircle);              //��ӵ���
    OnDrawPointer(nPointerType,nMeterType);   //��ָ�뺯��
    OnDrawScal(nMeterType,nDirection,nMainScal,nSubScal,dMax,dMin,nPointCount,nFontSize);              //���̶Ⱥ��ı�

    pScene->addItem(pGroup);
    // QGraphicsItem *pItem = dynamic_cast<QGraphicsItem *>(pGroup);   //��һ����ǿ��ת��ΪQGraphicsItem����
    return pGroup;
}
/****************************************************************************
 *�������ƣ�OnDrawPointer(int nPointerType)
 *�������ܣ������Ǳ�ָ������
 *�������壺
 *nMeterType:�����Ǳ����ͣ�0--��Բ��1--ȫԲָ�����ϣ�2--ȫԲָ�����£�3--�ķ�֮��Բָ������
 *nPointerType:ָ�����ͣ�0--ϸֱ�ߣ�1--��ֱ�ߣ�2--���Σ�3--������
 *edit by zqh
 ****************************************************************************/
void QDrawGraphics::OnDrawPointer(int nPointerType,int nMeterType)
{
    int nWidth = 100;             //Բ�Ŀ��
    int nHeight = 100;            //Բ�ĸ߶�
    int nPointerTop = 5;          //ָ���top����
    QPainterPath mPath;           //�����ߵ�path
    QVector <QPoint>mAngle;
    QPoint p1,p2,p3,p4;

    if(nPointerType == 0)      //ϸֱ��
    {
        if(nMeterType != 2) //ָ������
        {
            mPath.moveTo(nWidth/2,nPointerTop);           //��ֱ�ߵ����
            mPath.lineTo(nWidth/2,nHeight/2);             //��ֱ�ߵ��յ�
        }
        else
        {
            mPath.moveTo(nWidth/2,nHeight/2);             //��ֱ�ߵ����
            mPath.lineTo(nWidth/2,nHeight-nPointerTop);   //��ֱ�ߵ��յ�
        }
        QLineItem *pLinePointer = new QLineItem(mPath);   //��ϸֱ��ָ��
        pLinePointer->setLineColor(QColor(255,0,0));      //����ֱ����ɫ
        pLinePointer->setZValue(3);                       //���ò��
        pLinePointer->SetName("Pointer");                 //��������
        pGroup->addToGroup(pLinePointer);
    }
    else if(nPointerType == 1) //��ֱ��
    {
        if(nMeterType != 2) //ָ������
        {
            mPath.moveTo(nWidth/2,nPointerTop);           //��ֱ�ߵ����
            mPath.lineTo(nWidth/2,nHeight/2);             //��ֱ�ߵ��յ�
        }
        else
        {
            mPath.moveTo(nWidth/2,nHeight/2);             //��ֱ�ߵ����
            mPath.lineTo(nWidth/2,nHeight-nPointerTop);   //��ֱ�ߵ��յ�
        }
        QLineItem *pLinePointer = new QLineItem(mPath);   //����ֱ��ָ��
        pLinePointer->setLineWidth(3);                    //���ô�ֱ��ָ��
        pLinePointer->setLineColor(QColor(255,0,0));      //����ֱ����ɫ
        pLinePointer->setZValue(3);                       //���ò��
        pLinePointer->SetName("Pointer");                 //��������
        pGroup->addToGroup(pLinePointer);
    }
    else if(nPointerType == 2) //����
    {
        if(nMeterType != 2) //ָ������
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
        QPolygonItem *pPolyPointer = new QPolygonItem(mAnglePoly);   //������ָ��
        pPolyPointer->setLineType(0);
        pPolyPointer->setBackColor(QColor(255,0,0));
        pPolyPointer->setZValue(3);                       //���ò��
        pPolyPointer->SetName("Pointer");                 //��������
        pGroup->addToGroup(pPolyPointer);
    }
    else if(nPointerType == 3) //������
    {

        if(nMeterType != 2) //ָ������
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
        QPolygonItem *pPolyPointer = new QPolygonItem(mAnglePoly);   //��������ָ��
        pPolyPointer->setLineType(0);
        pPolyPointer->setBackColor(QColor(255,0,0));
        pPolyPointer->setZValue(3);                       //���ò��
        pPolyPointer->SetName("Pointer");                 //��������
        pGroup->addToGroup(pPolyPointer);
    }
}

/****************************************************************************
 *�������ƣ�OnDrawScal
 *�������ܣ������Ǳ�Ŀ̶Ⱥ��ı�
 *�������壺
 *nMeterType: �����Ǳ����ͣ�0--��Բ��1--ȫԲָ�����ϣ�2--ȫԲָ�����£�3--�ķ�֮��Բָ������
 *nDirection: ����0--˳ʱ�룬1--��ʱ��
 *nMainScal:  ���̶�
 *nSubScal:   �ο̶�
 *dMax:       ���ֵ
 *dMin:       ��Сֵ
 *nPointCount:С����λ��
 *nFontSize:  �����С
 *edit by zqh
 ****************************************************************************/
void QDrawGraphics::OnDrawScal(int nMeterType, int nDirection, int nMainScal,
                               int nSubScal, double dMax, double dMin, int nPointCount,
                               int nFontSize)
{
    QLineItem *pLineScal;
    int nWidth = 100;                 //Բ�Ŀ��
    int nHeight = 100;                //Բ�ĸ߶�
    double mMoveX = 0;                //���̶�X��ʼ��
    double mMoveY = 0;                //���̶�Y��ʼ��
    double mLineX = 0;                //���̶�X��ʼ��
    double mLineY = 0;                //���̶�Y��ʼ��
    double mMainAngle = 0;            //���̶�ƫת�Ƕȣ� ������
    double mSubAngle = 0;             //�ο̶�ƫת�Ƕȣ� ������
    double mTextAngle = 0;            //�ı�ƫת�Ƕ�,   �Ƕ���
    double mConst = 3.1415926;        //����
    int nMainScaleL = 6;              //���̶ȵĳ���
    int nSubScaleL = nMainScaleL / 2; //�ο̶ȳ���
    int nSunLineCount = 0;            //�ο̶�������
    int nDrawMainScal = nMainScal;    //���̶���
    double mValue = 0;                //
    double dVal = 0;
 //   int nIndex = 0;                   //С������±�
    QString sText = "";
//    QString sLeft = "";
//    QString sRight = "";
    int i = 0;
    QString sName = "";
    QRectF rect(QPointF(0,0), QSize(50,50));

    mValue = (dMax - dMin) / (nMainScal - 1);
    switch(nMeterType)
    {
    case 0: //��Բ��������
        mMainAngle = mConst / (nMainScal - 1);
        mSubAngle = mConst / (nSubScal*(nMainScal - 1));
        mTextAngle = 180.0 /(nMainScal - 1);
        break;
    case 1: //ȫԲ��������
    case 2: //ȫԲ��������
        mMainAngle = 2*mConst / (nMainScal - 1);
        mSubAngle = 2*mConst / (nSubScal*(nMainScal - 1));
        mTextAngle = 360.0 /(nMainScal - 1);
        nDrawMainScal --;
        break;
    case 3: //�ķ�֮��Բ��������
        mMainAngle = 1.5*mConst / (nMainScal - 1);
        mSubAngle = 1.5*mConst / (nSubScal*(nMainScal - 1));
        mTextAngle = 270.0 /(nMainScal - 1);
        break;
    default:
        return;
    }

    for(i = 0; i < nDrawMainScal; i++)  //�����̶�nMainScal
    {   
        switch(nMeterType)
        {
        case 0: //��Բ��������
            mMoveX = nWidth/2 - nWidth/2 * cos(mMainAngle*i);
            mMoveY = nWidth/2 - nWidth/2 * sin(mMainAngle*i);

            mLineX = nWidth/2 - (nWidth/2+nMainScaleL)*cos(mMainAngle*i);
            mLineY = nHeight/2 - (nWidth/2+nMainScaleL)*sin(mMainAngle*i);
            break;
        case 1: //ȫԲ��������
            mMoveX = nWidth/2 + nWidth/2 * sin(mMainAngle*i);
            mMoveY = nHeight/2 - nWidth/2 * cos(mMainAngle*i);

            mLineX = nWidth/2 + (nWidth/2+nMainScaleL)*sin(mMainAngle*i);
            mLineY = nHeight/2 - (nWidth/2+nMainScaleL)*cos(mMainAngle*i);
            break;
        case 2: //ȫԲ��������
            mMoveX = nWidth/2 - nWidth/2 * sin(mMainAngle*i);
            mMoveY = nHeight/2 + nWidth/2 * cos(mMainAngle*i);

            mLineX = nWidth/2 - (nWidth/2+nMainScaleL)*sin(mMainAngle*i);
            mLineY = nHeight/2 + (nWidth/2+nMainScaleL)*cos(mMainAngle*i);
            break;
        case 3: //�ķ�֮��Բ��������
            mMoveX = nWidth/2 - nWidth/2 * sin(mMainAngle*i+mConst/4);
            mMoveY = nHeight/2 + nWidth/2 * cos(mMainAngle*i+mConst/4);

            mLineX = nWidth/2 - (nWidth/2+nMainScaleL)*sin(mMainAngle*i+mConst/4);
            mLineY = nHeight/2 + (nWidth/2+nMainScaleL)*cos(mMainAngle*i+mConst/4);
            break;
        default:
            return;
        }

        QPainterPath mPath;
        mPath.moveTo(mMoveX,mMoveY);             //��ֱ�ߵ����
        mPath.lineTo(mLineX,mLineY);             //��ֱ�ߵ��յ�
        pLineScal = new QLineItem(mPath);        //��ϸֱ��
        pLineScal->setLineColor(QColor(255,0,0));  //����ֱ����ɫ
        pLineScal->setZValue(4);                 //���ò��

        sName = QString("%1").arg(i);
        sName = "MainLineScal"+sName;
        pLineScal->SetName(sName);               //��������
        pGroup->addToGroup(pLineScal);           //��ӵ���

        /************************************************
         *�����ǻ��ı�
         ***********************************************/
        if(nDirection == 0)     //˳ʱ��
            dVal = dMin + i*mValue;
        else if(nDirection == 1)//��ʱ��
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
            if(sTemp == "-") //�Ǹ�����ʱ��
            {
                sTemp = sText.right(sText.length()-1); //ȡ��ȥ���ŵ�����
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
//        nIndex = sText.indexOf(".");   //����С�����λ��
//        if(nIndex > 0) //��С����
//        {
//            sLeft = sText.mid(0,nIndex);             //ȡС����֮ǰ������
//            sRight = sText.mid(nIndex+1,nPointCount);//ȡС����֮�������
//            if(nPointCount == 0)
//                sText = sLeft;
//            else
//                sText = sLeft +"."+sRight;               //��������
//        }


        rect.setTopLeft(QPointF(0,0));           //������mLineX,mLineY
        rect.setSize(QSize(nWidth,nWidth));
        QSimpleTextItem *pText = new QSimpleTextItem(rect,sText);

        pText->SetFontSize(nFontSize);
        QFont nfont = pText->GetTextFont(); //�����ı����Ĵ�С
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
            case 1: //ȫԲ����
                mLineX = mLineX - rc.width()/2-1;
                mLineY = mLineY -rc.height();
                break;
            case 2: //ȫԲ����
                mLineX = mLineX - rc.width()/2;
                mLineY = mLineY + 1;
                break;
            case 3: //�ķ�֮��Բ��������
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
            case 1: //ȫԲ����
                mLineX = mLineX + 1;
                mLineY = mLineY -rc.height()/2;
                break;
            case 2: //ȫԲ����
                mLineX = mLineX - rc.width()-4;
                mLineY = mLineY - rc.height()/2;
                break;
            case 3: //�ķ�֮��Բ��������
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
            case 1: //ȫԲ����
                mLineX = mLineX - rc.width()/2;
                mLineY = mLineY + 1;
                break;
            case 2: //ȫԲ����
                mLineX = mLineX - rc.width()/2;
                mLineY = mLineY - rc.height();
                break;
            case 3: //�ķ�֮��Բ��������
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
            case 1: //ȫԲ����
                mLineX = mLineX - rc.width()-4;
                mLineY = mLineY - rc.height()/2;
                break;
            case 2: //ȫԲ����
                mLineX = mLineX + 1;
                mLineY = mLineY -rc.height()/2;
                break;
            case 3: //�ķ�֮��Բ��������
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
            case 1: //ȫԲ����
                mLineX = mLineX - rc.width()/2;
                mLineY = mLineY - rc.height();
                break;
            case 2: //ȫԲ����
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

        pGroup->addToGroup(pText);           //��ӵ���

        /***********************���ı����**************************/
    }

    nSunLineCount = nSubScal*(nMainScal - 1);//�ο̶�������
    for(i = 0; i < nSunLineCount; i++)  //���ο̶�
    {
        if( i%nSubScal != 0)
        {
            switch(nMeterType)
            {
            case 0: //��Բ��������
                mMoveX = nWidth/2 - nWidth/2 * cos(mSubAngle*i);
                mMoveY = nWidth/2 - nWidth/2 * sin(mSubAngle*i);

                mLineX = nWidth/2 - (nWidth/2+nSubScaleL)*cos(mSubAngle*i);
                mLineY = nHeight/2 - (nWidth/2+nSubScaleL)*sin(mSubAngle*i);
                break;
            case 1: //ȫԲ��������
                mMoveX = nWidth/2 + nWidth/2 * sin(mSubAngle*i);
                mMoveY = nWidth/2 - nWidth/2 * cos(mSubAngle*i);

                mLineX = nWidth/2 + (nWidth/2+nSubScaleL)*sin(mSubAngle*i);
                mLineY = nHeight/2 - (nWidth/2+nSubScaleL)*cos(mSubAngle*i);
                break;
            case 2: //ȫԲ��������

                mMoveX = nWidth/2 - nWidth/2 * sin(mSubAngle*i);
                mMoveY = nWidth/2 + nWidth/2 * cos(mSubAngle*i);

                mLineX = nWidth/2 - (nWidth/2+nSubScaleL)*sin(mSubAngle*i);
                mLineY = nHeight/2 + (nWidth/2+nSubScaleL)*cos(mSubAngle*i);
                break;
            case 3: //�ķ�֮��Բ��������
                mMoveX = nWidth/2 - nWidth/2 * sin(mSubAngle*i+mConst/4);
                mMoveY = nWidth/2 + nWidth/2 * cos(mSubAngle*i+mConst/4);

                mLineX = nWidth/2 - (nWidth/2+nSubScaleL)*sin(mSubAngle*i+mConst/4);
                mLineY = nHeight/2 + (nWidth/2+nSubScaleL)*cos(mSubAngle*i+mConst/4);
                break;
            default:
                return;
            }

            QPainterPath mPath;
            mPath.moveTo(mMoveX,mMoveY);             //��ֱ�ߵ����
            mPath.lineTo(mLineX,mLineY);             //��ֱ�ߵ��յ�
            pLineScal = new QLineItem(mPath);        //��ϸֱ��
            pLineScal->setLineColor(QColor(255,0,0));  //����ֱ����ɫ
            pLineScal->setZValue(4);                 //���ò��

            sName = QString("%1").arg(i);
            sName = "SubLineScal"+sName;
            pLineScal->SetName(sName);               //��������

            pGroup->addToGroup(pLineScal);
        }
    }
}


/****************************************************************************
 *�������ƣ�OnDrawMeter(QGraphicsScene *pScene,int nPointerType,int nDirection)
 *�������ܣ������Ǳ�ͼ��
 *�������壺
 *pScene���ѻ��õ�ͼ����ӵ��ĳ���
 *nMeterType:�����Ǳ����ͣ�0--��Բ��1--ȫԲָ�����ϣ�2--ȫԲָ�����£�3--�ķ�֮��Բָ������
 *nDirection������0--˳ʱ�룬1--��ʱ��
 *nMainScal:  ���̶�
 *nSubScal:   �ο̶�
 *dMax:       ���ֵ
 *dMin:       ��Сֵ
 *nPointCount:С����λ��
 *nFontSize:  �����С
 *edit by zqh
 ****************************************************************************/
QGraphicsItem* QDrawGraphics::OnDrawPie(QGraphicsScene *pScene, int nMeterType,
                                        int nDirection, int nMainScal, int nSubScal, double dMax,
                                        double dMin, int nPointCount, int nFontSize)
{
    int nWidth = 100;      //Բ�Ŀ��
    int nHeight = 100;     //Բ�ĸ߶�

    pGroup = new QItemGroup;

    QRectF mRect(QPoint(0,0),QSize(nWidth,nHeight));       //���ô�С
    QElipseItem *pBaseCircle = new QElipseItem(mRect);     //����һ����Բ
    pBaseCircle->SetName("mBaseCircle");                   //����Բ������
    pBaseCircle->SetBackColor(QColor(224,224,224));        //���ñ���ɫ
    pBaseCircle->SetLineType(0);
    pBaseCircle->setZValue(1);                             //���ò��

    QElipseItem *pPieCircle = new QElipseItem(mRect);      //����һ����ͼ
    pPieCircle->SetName("mPieCircle");                     //����Բ������
    pPieCircle->SetBackColor(QColor(255,0,0));             //���ñ���ɫ
    pPieCircle->setZValue(2);

    mRect.setTopLeft(QPointF(10,10));
    mRect.setSize(QSize(80,80));
    QElipseItem *pCircle = new QElipseItem(mRect);         //����һ��Բ��ͼ
    pCircle->SetName("mCircle");                           //����Բ������
    pCircle->SetLineType(0);
    pCircle->SetBackColor(QColor(255,255,255));                //���ñ���ɫ
    pCircle->setZValue(3);

    switch(nMeterType)
    {
    case 0:  //��Բ�Ǳ�
        pBaseCircle->SetStartAngle(0);                 //���ÿ�ʼ�Ƕ�
        pBaseCircle->SetSpanAngle(180);                //���ÿ��,����һ����Բ

        pPieCircle->SetStartAngle(0);                  //���ÿ�ʼ�Ƕ�
        pPieCircle->SetSpanAngle(90);                  //���ÿ��,����һ����Բ

        pCircle->SetStartAngle(0);                     //���ÿ�ʼ�Ƕ�
        pCircle->SetSpanAngle(180);                    //���ÿ��,����һ����Բ
        break;
    case 1:  //ȫԲָ������
    case 2:  //ȫԲָ������
        pPieCircle->SetStartAngle(0);                  //���ÿ�ʼ�Ƕ�
        pPieCircle->SetSpanAngle(180);                 //���ÿ��,����һ����Բ
        break;
    case 3:  //�ķ�֮��Բָ������
        pBaseCircle->SetStartAngle(315);               //���ÿ�ʼ�Ƕ�
        pBaseCircle->SetSpanAngle(270);                //���ÿ��,����һ���ķ�֮��Բ

        pPieCircle->SetStartAngle(315);                //���ÿ�ʼ�Ƕ�
        pPieCircle->SetSpanAngle(135);                 //���ÿ��,����һ����Բ

        pCircle->SetStartAngle(315);                   //���ÿ�ʼ�Ƕ�
        pCircle->SetSpanAngle(270);                    //���ÿ��,����һ����Բ
        break;
    default:
        break;
    }

    pGroup->addToGroup(pBaseCircle);              //��ӵ���
    pGroup->addToGroup(pPieCircle);               //��ӵ���
    pGroup->addToGroup(pCircle);                  //��ӵ���
    OnDrawScal(nMeterType,nDirection,nMainScal,nSubScal,dMax,dMin,nPointCount,nFontSize);              //���̶Ⱥ��ı�

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

    if (pictrue)   //��ͼƬ����
    {
        if(ifFit)
            newPic = (*pictrue).scaled(100,100); //������С92
        else
            newPic = (*pictrue).scaled(50,50); //����������С46

        QPixmapItem* newPicItem = new QPixmapItem(newPic,newPic.size());
        newPicItem->setZValue(2);          //���ò��
        newPicItem->setPos(nSpace,nSpace); //���ó�ʼλ��

        for(i=0; i<itemList.size();i++) //�������ͼƬ
        {
            if (itemList.at(i)->type() == SAM_DRAW_OBJECT_PIXMAP)
            {
                IsPictureExist = true;
                itemList.replace(i,newPicItem);
                SetPicPosition(newPicItem,nPicPosition,nBorderInterval,ifFit,0,rect); //����ͼƬ��λ��
                break;
            }
        }
        if (!IsPictureExist)            //�����û��ͼƬ
        {
            itemList.insert(1,newPicItem);
            SetPicPosition(newPicItem,nPicPosition,nBorderInterval,ifFit,0,rect); //����ͼƬ��λ��
        }
    }
    else      //û��ͼƬ���룬�ж���ɾ��ͼƬ���ǵ���ͼƬ��λ��
    {
        for(i=0; i<itemList.size();i++)
        {
            if (itemList.at(i)->type() == SAM_DRAW_OBJECT_PIXMAP)
            {
                if(ifDeletePic) //��ʾ��ɾ��ͼƬ
                    itemList.removeOne(itemList.at(i));
                else            //����ͼƬ��λ��
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
 *�������ƣ�OnDrawTrendChart
 *�������ܣ�������ͼ��XY����ͼ�Լ���ʷ����ͼ����
 *�������壺
 *edit by czq
 **************************************************************/
void QDrawGraphics::OnDrawTrendChart(QTrendAttr *pItem)
{
    if(!pItem)
    {
        return;
    }

    QString sText = "";
    int nFontSizeX = pItem->m_nFontSize;       //�����С
    int nFontSizeY = pItem->m_nFontSize;       //�����С

    //X��
    int nXmain  = pItem->m_nHorMajorScale; //���̶�
    int nXsub   = pItem->m_nHorMinorScale; //�ο̶�

    //Y��
    int nYmain  = pItem->m_nVertMajorScale; //���̶�
    int nYsub   = pItem->m_nVertMinorScale; //�ο̶�

    double m_nDisplayMax = pItem->m_nDisplayMax;
    double m_nDisplayMin = pItem->m_nDisplayMin;

    QDateTime tStart;
    QDateTime tEnd;

    getDateTime(pItem,tStart,tEnd);
    //�����ǻ�ͼ����ı���
    int         nTopSpace   = 20;                           //����ɫ����뱳�����������ƫ����
    int         nLeftSpace  = 60;//80;                      //����ɫ����뱳�����������ƫ����,���������Ҫһ���㷨������
    double      nBGW        = 400-nLeftSpace-nLeftSpace/2;  //��ɫ���εĿ��
    double      nBGH        = 250-nTopSpace-2*nTopSpace;    //��ɫ���εĸ߶�
    if(!pItem->m_bMainVer && !pItem->m_bMainHor)//û��ˮƽ-û�д�ֱ
    {
        nTopSpace   = 0;
        nLeftSpace  = 0;
        nBGW = 400;
        nBGH = 250;
    }
    else if(!pItem->m_bMainVer && pItem->m_bMainHor)//��ˮƽ-û�д�ֱ
    {
        nTopSpace   = 0;
        nLeftSpace  = 30;
        nBGW = 340;
        nBGH = 250;
    }
    else if(pItem->m_bMainVer && !pItem->m_bMainHor)//��ˮƽ-û�д�ֱ
    {
        nTopSpace   = 20;
        nLeftSpace  = 0;
        nBGW = 400;
        nBGH = 210;
    }

    int         ML          = 10;                           //�̶ȳ���
    int         nVal        = nXsub*nXmain;                 //�ο̶�����
    double      mMoveX      = 0;                            //���̶�X��ʼ��
    double      mMoveY      = 0;                            //���̶�Y��ʼ��
    double      mLineX      = 0;                            //���̶�X��ʼ��
    double      mLineY      = 0;                            //���̶�Y��ʼ��
    double      MainSpace   = nBGW/nXmain;                  //���̶ȼ��
    double      SubSpace    = nBGW/(nXsub*nXmain);          //�ο̶ȼ��
    QRectItem*  pBackRect;                                  //�������ο�
    QRectItem*  pBGRect;                                    //��ɫ���ο�
    QLineItem*  pLine;
    QLineItem*  pXLine;
    QSimpleTextItem *pText;

    //----------------------��ʼ����������------------------------
    QRectF rect(QPointF(0,0), QSize(400,250));     //�������ο�480,250
    //pBackRect = new QRectItem(rect);
    //pBackRect->SetBackColor(pItem->m_nBoradColor);
    //pBackRect->SetLineType(0);
    //pBackRect->SetAlpha(100);
    //pBackRect->SetName(pItem->m_nBoradColor.name());
    //pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    //pItem->addToGroup(pBackRect);
    //pBackRect->SetAlpha(255);

    //--------------------��ʼ��ͼ������ɫ����--------------------
    rect.setTopLeft(QPoint(nLeftSpace,nTopSpace));
    rect.setSize(QSizeF(nBGW,nBGH));
    pBGRect = new QRectItem(rect);
    pBGRect->SetBackColor(pItem->m_nGraphColor);
    pBGRect->SetLineColor(pItem->m_nBoradColor);
    pBGRect->SetAlpha(pItem->m_alpha);
    pBGRect->SetName("backRect");
    pBGRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pItem->addToGroup(pBGRect);

    //--------------------��ʼ��X��̶�--------------------
    //if(pItem->m_bMainHor)
    {
        for(int i = 0; i <= nXmain; i++)
        {
            QPainterPath mPath;//�����ߵ�path

            if(pItem->m_bMainHor)
            {
                //�����̶�
                mMoveX = i * MainSpace + nLeftSpace;
                mMoveY = nTopSpace + nBGH;
                mLineX = i * MainSpace + nLeftSpace;
                mLineY = nTopSpace + nBGH + ML;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineType(1);          //��������
                pLine->setLineColor(pItem->m_nScaleColor); //���̶���ɫ
                pLine->SetName(QString("XMainScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //��������
            if(pItem->m_bGrade)//�Ƿ���ʾ����
            {
                if(i != 0 && i != nXmain)
                {
                    QPainterPath mPath1;               //�����ߵ�path
                    mMoveX = i * MainSpace + nLeftSpace;
                    mMoveY = nTopSpace;
                    mLineX = i * MainSpace + nLeftSpace;
                    mLineY = nTopSpace + nBGH;
                    mPath1.moveTo(mMoveX,mMoveY);
                    mPath1.lineTo(mLineX,mLineY);
                    pXLine = new QLineItem(mPath1);
                    pXLine->setLineType(1); //����
                    pXLine->setLineColor(pItem->m_nVerColor); //������ɫ
                    pXLine->SetName(QString("XMainLine%1").arg(i));
                    pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->addToGroup(pXLine);
                }
            }

            if(pItem->m_bMainHor)
            {
                //�Ƿ���ʾ�ı�
                if(pItem->m_bXMarked)
                {
                    mLineX  = i * MainSpace + nLeftSpace;
                    mLineY  = nTopSpace + nBGH + ML;

                    //��ʱ���ı�
                    if(pItem->m_bTimeFormat)
                    {
                        sText   = GetTimeText(tStart, tEnd, nXmain, i, pItem->m_eTimeFormat -1,1);

                        pText   = new QSimpleTextItem(rect,sText);
                        pText   = DrawTrendText(pText, i, mLineX, mLineY, sText, nFontSizeX, pItem->m_nMarkedColor,0);
                        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
                        pItem->addToGroup(pText);
                    }

                    //�������ı�
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
            if(pItem->m_bSelectHorMinor && pItem->m_bMainHor) //��ʾX��̶�
            {
                QPainterPath mPath; //�����ߵ�path

                //���ο̶�
                mMoveX = i * SubSpace + nLeftSpace;
                mMoveY = nTopSpace + nBGH;
                mLineX = mMoveX;
                mLineY = ML / 2 + nTopSpace + nBGH;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineType(1); //����
                pLine->setLineColor(pItem->m_nScaleColor); //������ɫ
                pLine->SetName(QString("XSubScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //���θ���
            if(pItem->m_bGrade && pItem->m_bSelectHorMinor) //�Ƿ���ʾ����
            {
                QPainterPath mPath1;               //�����ߵ�path
                mMoveX = i * SubSpace + nLeftSpace;
                mMoveY = nTopSpace;
                mLineX = mMoveX;
                mLineY = nTopSpace + nBGH;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pXLine = new QLineItem(mPath1);
                pXLine->setLineColor(pItem->m_nVerColor); //������ɫ
                pXLine->setLineType(3); //����Ϊ����
                pXLine->SetName(QString("XSubLine%1").arg(i));
                pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pXLine);
            }
        }
    }

    //--------------------��ʼ��Y��̶�--------------------
    MainSpace   = nBGH / nYmain;          //���̶ȼ��
    SubSpace    = nBGH / (nYsub * nYmain);//�ο̶ȼ��
    nVal        = nYsub * nYmain;         //�ο̶�����

    //if(pItem->m_bMainVer)
    {
        for(int i = 0; i <= nYmain; i++)
        {
            if(pItem->m_bMainVer)
            {
                //�����̶�
                QPainterPath mPath;               //�����ߵ�path
                mMoveX = nLeftSpace - ML;
                mMoveY = i * MainSpace + nTopSpace;
                mLineX = nLeftSpace;
                mLineY = i * MainSpace + nTopSpace;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineColor(pItem->m_nScaleColor); //������ɫ
                pLine->SetName(QString("YMainScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //��������
            if(pItem->m_bGrade) //�Ƿ���ʾ����
            {
                if(i != 0 && i != nYmain)
                {
                    QPainterPath mPath1;               //�����ߵ�path
                    mMoveX = nLeftSpace;
                    mMoveY = i * MainSpace + nTopSpace;
                    mLineX = nLeftSpace + nBGW;
                    mLineY = i * MainSpace + nTopSpace;
                    mPath1.moveTo(mMoveX,mMoveY);
                    mPath1.lineTo(mLineX,mLineY);
                    pLine = new QLineItem(mPath1);
                    pLine->setLineColor(pItem->m_nHorColor); //������ɫ
                    pLine->SetName(QString("YMainLine%1").arg(i)); //YSubScale
                    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->addToGroup(pLine);
                }
            }

            if(pItem->m_bMainVer)
            {
                //��ʾY���ı�
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

        for(int i = 1; i < nVal; i++) //���ο̶�
        {
            if(pItem->m_bSelectVertMinor && pItem->m_bMainVer) //��ʾY��̶�
            {
                QPainterPath mPath; //�����ߵ�path
                mMoveX = nLeftSpace - ML / 2;
                mMoveY = i * SubSpace + nTopSpace;
                mLineX = nLeftSpace;
                mLineY = i * SubSpace + nTopSpace;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineColor(pItem->m_nScaleColor); //������ɫ
                pLine->SetName(QString("YSubScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //��Y��θ���
            if(pItem->m_bGrade && pItem->m_bSelectVertMinor) //�Ƿ���ʾ����
            {
                QPainterPath mPath1;               //�����ߵ�path
                mMoveX = nLeftSpace;
                mMoveY = i * SubSpace + nTopSpace;
                mLineX = nLeftSpace + nBGW;
                mLineY = i * SubSpace + nTopSpace;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath1);
                pLine->setLineType(3);
                pLine->setLineColor(pItem->m_nHorColor); //������ɫ
                pLine->SetName(QString("YSubLine%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }
        }
    }

    //--------------------��ʼ����--------------------
    //double YPenSpace = nBGH / 8; //Y�᷽��ÿ����֮��ļ��,��Ȼ��������ߣ��ǾͲ�Ҫ��
    //double XPenSpace = nBGW / 4; //X�᷽��ÿ����֮��ļ��
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
    srand(time(0));//��ʼ���������ʱ��
    unsigned int addY = 0;
    for(int j = 0;j < pItem->m_vecChannelGroups.size(); j++)//���ٸ�ͨ�����ж�����
    {
        QPainterPath mPenPath = QPainterPath();
        addY = rand() % (int)nBGH;
        mPenPath.moveTo(QPointF(nLeftSpace, nTopSpace + addY));//��һ��
        for(int i = 1; i <= pointNum; i++)
        {
            mPenPath.lineTo(QPointF(nLeftSpace + i * XPenSpace, nTopSpace + (rand() % (int)nBGH)));
        }

        pPenLine = new QFoldLineItem(mPenPath);
        pPenLine->setLineType(pItem->m_vecChannelGroups.at(j).eLineType);
        pPenLine->setLineColor(pItem->m_vecChannelGroups.at(j).nDisplayColor); //������ɫ
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
    int nFontSizeX = pItem->m_textSize;       //�����С
    int nFontSizeY = pItem->m_textSize;       //�����С

    //X��
    int nXmain  = pItem->m_nHorMajorScale; //���̶�
    int nXsub   = pItem->m_nHorMinorScale; //�ο̶�
    double m_nDisplayMinX = pItem->m_nDisplayMinX;
    double m_nDisplayMaxX = pItem->m_nDisplayMaxX;
    qDebug() << "min X:" << m_nDisplayMinX;
    qDebug() << "max X:" << m_nDisplayMaxX;
    //Y��
    int nYmain  = pItem->m_nVertMajorScale; //���̶�
    int nYsub   = pItem->m_nVertMinorScale; //�ο̶�

    double m_nDisplayMin = pItem->m_nDisplayMinY;
    double m_nDisplayMax = pItem->m_nDisplayMaxY;
    qDebug() << "min Y:" << m_nDisplayMin;
    qDebug() << "max Y:" << m_nDisplayMax;

    //getDateTime(pItem,tStart,tEnd);
    //�����ǻ�ͼ����ı���
    int         nTopSpace   = 20;                           //����ɫ����뱳�����������ƫ����
    int         nLeftSpace  = 60;//80;                      //����ɫ����뱳�����������ƫ����,���������Ҫһ���㷨������
    double      nBGW        = 400-nLeftSpace-nLeftSpace/2;  //��ɫ���εĿ��
    double      nBGH        = 250-nTopSpace-2*nTopSpace;    //��ɫ���εĸ߶�
    if(!pItem->m_bMainVer && !pItem->m_bMainHor)//û��ˮƽ-û�д�ֱ
    {
        nTopSpace   = 0;
        nLeftSpace  = 0;
        nBGW = 400;
        nBGH = 250;
    }
    else if(!pItem->m_bMainVer && pItem->m_bMainHor)//��ˮƽ-û�д�ֱ
    {
        nTopSpace   = 0;
        nLeftSpace  = 30;
        nBGW = 340;
        nBGH = 250;
    }
    else if(pItem->m_bMainVer && !pItem->m_bMainHor)//��ˮƽ-û�д�ֱ
    {
        nTopSpace   = 20;
        nLeftSpace  = 0;
        nBGW = 400;
        nBGH = 210;
    }

    int         ML          = 10;                           //�̶ȳ���
    int         nVal        = nXsub*nXmain;                 //�ο̶�����
    double      mMoveX      = 0;                            //���̶�X��ʼ��
    double      mMoveY      = 0;                            //���̶�Y��ʼ��
    double      mLineX      = 0;                            //���̶�X��ʼ��
    double      mLineY      = 0;                            //���̶�Y��ʼ��
    double      MainSpace   = nBGW/nXmain;                  //���̶ȼ��
    double      SubSpace    = nBGW/(nXsub*nXmain);          //�ο̶ȼ��
    QRectItem*  pBackRect;                                  //�������ο�
    QRectItem*  pBGRect;                                    //��ɫ���ο�
    QLineItem*  pLine;
    QLineItem*  pXLine;
    QSimpleTextItem *pText;

    //----------------------��ʼ����������------------------------
    QRectF rect(QPointF(0,0), QSize(400,250));     //�������ο�480,250
    //pBackRect = new QRectItem(rect);
    //pBackRect->SetBackColor(pItem->m_nBoradColor);
    //pBackRect->SetLineType(0);
    //pBackRect->SetAlpha(100);
    //pBackRect->SetName(pItem->m_nBoradColor.name());
    //pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    //pItem->addToGroup(pBackRect);
    //pBackRect->SetAlpha(255);

    //--------------------��ʼ��ͼ������ɫ����--------------------
    rect.setTopLeft(QPoint(nLeftSpace,nTopSpace));
    rect.setSize(QSizeF(nBGW,nBGH));
    pBGRect = new QRectItem(rect);
    pBGRect->SetBackColor(pItem->m_nGraphColor);
    pBGRect->SetLineColor(pItem->m_nBoradColor);
    pBGRect->SetAlpha(pItem->m_alpha);
    pBGRect->SetName("backRect");
    pBGRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pItem->addToGroup(pBGRect);

    //--------------------��ʼ��X��̶�--------------------
    //if(pItem->m_bMainHor)
    {
        for(int i = 0; i <= nXmain; i++)
        {
            QPainterPath mPath;//�����ߵ�path

            if(pItem->m_bMainHor)
            {
                //�����̶�
                mMoveX = i * MainSpace + nLeftSpace;
                mMoveY = nTopSpace + nBGH;
                mLineX = i * MainSpace + nLeftSpace;
                mLineY = nTopSpace + nBGH + ML;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineType(1);          //��������
                pLine->setLineColor(pItem->m_nScaleColor); //���̶���ɫ
                pLine->SetName(QString("XMainScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //��������
            if(pItem->m_bGrade)//�Ƿ���ʾ����
            {
                if(i != 0 && i != nXmain)
                {
                    QPainterPath mPath1;               //�����ߵ�path
                    mMoveX = i * MainSpace + nLeftSpace;
                    mMoveY = nTopSpace;
                    mLineX = i * MainSpace + nLeftSpace;
                    mLineY = nTopSpace + nBGH;
                    mPath1.moveTo(mMoveX,mMoveY);
                    mPath1.lineTo(mLineX,mLineY);
                    pXLine = new QLineItem(mPath1);
                    pXLine->setLineType(1); //����
                    pXLine->setLineColor(pItem->m_nVerColor); //������ɫ
                    pXLine->SetName(QString("XMainLine%1").arg(i));
                    pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->addToGroup(pXLine);
                }
            }

            if(pItem->m_bMainHor)
            {
                //�Ƿ���ʾ�ı�
                if(1)
                {
                    mLineX  = i * MainSpace + nLeftSpace;
                    mLineY  = nTopSpace + nBGH + ML;

                    //��ʱ���ı�
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
            if(pItem->m_bSelectHorMinor && pItem->m_bMainHor) //��ʾX��̶�
            {
                QPainterPath mPath; //�����ߵ�path

                //���ο̶�
                mMoveX = i * SubSpace + nLeftSpace;
                mMoveY = nTopSpace + nBGH;
                mLineX = mMoveX;
                mLineY = ML / 2 + nTopSpace + nBGH;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineType(1); //����
                pLine->setLineColor(pItem->m_nScaleColor); //������ɫ
                pLine->SetName(QString("XSubScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //���θ���
            if(pItem->m_bGrade && pItem->m_bSelectHorMinor) //�Ƿ���ʾ����
            {
                QPainterPath mPath1;               //�����ߵ�path
                mMoveX = i * SubSpace + nLeftSpace;
                mMoveY = nTopSpace;
                mLineX = mMoveX;
                mLineY = nTopSpace + nBGH;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pXLine = new QLineItem(mPath1);
                pXLine->setLineColor(pItem->m_nVerColor); //������ɫ
                pXLine->setLineType(3); //����Ϊ����
                pXLine->SetName(QString("XSubLine%1").arg(i));
                pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pXLine);
            }
        }
    }

    //--------------------��ʼ��Y��̶�--------------------
    MainSpace   = nBGH / nYmain;          //���̶ȼ��
    SubSpace    = nBGH / (nYsub * nYmain);//�ο̶ȼ��
    nVal        = nYsub * nYmain;         //�ο̶�����

    //if(pItem->m_bMainVer)
    {
        for(int i = 0; i <= nYmain; i++)
        {
            if(pItem->m_bMainVer)
            {
                //�����̶�
                QPainterPath mPath;               //�����ߵ�path
                mMoveX = nLeftSpace - ML;
                mMoveY = i * MainSpace + nTopSpace;
                mLineX = nLeftSpace;
                mLineY = i * MainSpace + nTopSpace;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineColor(pItem->m_nScaleColor); //������ɫ
                pLine->SetName(QString("YMainScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //��������
            if(pItem->m_bGrade) //�Ƿ���ʾ����
            {
                if(i != 0 && i != nYmain)
                {
                    QPainterPath mPath1;               //�����ߵ�path
                    mMoveX = nLeftSpace;
                    mMoveY = i * MainSpace + nTopSpace;
                    mLineX = nLeftSpace + nBGW;
                    mLineY = i * MainSpace + nTopSpace;
                    mPath1.moveTo(mMoveX,mMoveY);
                    mPath1.lineTo(mLineX,mLineY);
                    pLine = new QLineItem(mPath1);
                    pLine->setLineColor(pItem->m_nHorColor); //������ɫ
                    pLine->SetName(QString("YMainLine%1").arg(i)); //YSubScale
                    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                    pItem->addToGroup(pLine);
                }
            }

            if(pItem->m_bMainVer)
            {
                //��ʾY���ı�
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

        for(int i = 1; i < nVal; i++) //���ο̶�
        {
            if(pItem->m_bSelectVertMinor && pItem->m_bMainVer) //��ʾY��̶�
            {
                QPainterPath mPath; //�����ߵ�path
                mMoveX = nLeftSpace - ML / 2;
                mMoveY = i * SubSpace + nTopSpace;
                mLineX = nLeftSpace;
                mLineY = i * SubSpace + nTopSpace;

                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);

                pLine = new QLineItem(mPath);
                pLine->setLineColor(pItem->m_nScaleColor); //������ɫ
                pLine->SetName(QString("YSubScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }

            //��Y��θ���
            if(pItem->m_bGrade && pItem->m_bSelectVertMinor) //�Ƿ���ʾ����
            {
                QPainterPath mPath1;               //�����ߵ�path
                mMoveX = nLeftSpace;
                mMoveY = i * SubSpace + nTopSpace;
                mLineX = nLeftSpace + nBGW;
                mLineY = i * SubSpace + nTopSpace;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath1);
                pLine->setLineType(3);
                pLine->setLineColor(pItem->m_nHorColor); //������ɫ
                pLine->SetName(QString("YSubLine%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }
        }
    }

    //--------------------��ʼ����--------------------
    //double YPenSpace = nBGH / 8; //Y�᷽��ÿ����֮��ļ��,��Ȼ��������ߣ��ǾͲ�Ҫ��
    //double XPenSpace = nBGW / 4; //X�᷽��ÿ����֮��ļ��
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
    srand(time(0));//��ʼ���������ʱ��
    unsigned int addY = 0;
    for(int j = 0;j < pItem->m_vecChannels.size(); j++)//���ٸ�ͨ�����ж�����
    {
        QPainterPath mPenPath = QPainterPath();
        addY = rand() % (int)nBGH;
        mPenPath.moveTo(QPointF(nLeftSpace, nTopSpace + addY));//��һ��
        for(int i = 1; i <= pointNum; i++)
        {
            mPenPath.lineTo(QPointF(nLeftSpace + i * XPenSpace, nTopSpace + (rand() % (int)nBGH)));
        }

        pPenLine = new QFoldLineItem(mPenPath);
        pPenLine->setLineType(pItem->m_vecChannels.at(j).eLineType);
        pPenLine->setLineColor(pItem->m_vecChannels.at(j).nDisplayColor); //������ɫ
        pPenLine->SetName(QString("PenLine%1").arg(j));
        pPenLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pItem->addToGroup(pPenLine);
    }
}
/***************************************************************
 *�������ƣ�OnDrawDataGroup
 *�������ܣ�����Ⱥ��
 *�������壺
 *edit by czq
 **************************************************************/
void QDrawGraphics::OnDrawDataGroup(QTrendDataGroupAttr *pItem)//�µ�����Ⱥ����ú���
{
    if(!pItem)
    {
        return;
    }

    QString sText  = "";
    int nFontSizeX = pItem->m_nFontSize;       //�����С
    int nFontSizeY = pItem->m_nFontSize;       //�����С

    //X��
    int nXmain  = pItem->m_nHorMajorScale; //���̶�
    int nXsub   = pItem->m_nHorMinorScale; //�ο̶�

    //Y��
    int nYmain  = pItem->m_nVertMajorScale; //���̶�
    int nYsub   = pItem->m_nVertMinorScale; //�ο̶�

    //�����ǻ�ͼ����ı���
    int         nTopSpace   = 20;                           //����ɫ����뱳�����������ƫ����
    int         nLeftSpace  = 60;//80;                      //����ɫ����뱳�����������ƫ����,���������Ҫһ���㷨������
    int         ML          = 10;                           //�̶ȳ���
    int         nVal        = nXsub*nXmain;                 //�ο̶�����
    double      nBGW        = 400-nLeftSpace-nLeftSpace/2;  //��ɫ���εĿ��
    double      nBGH        = 250-nTopSpace-2*nTopSpace;    //��ɫ���εĸ߶�
    if(!pItem->m_bMainVer && !pItem->m_bMainHor)//û��ˮƽ-û�д�ֱ
    {
        nTopSpace   = 0;
        nLeftSpace  = 0;
        nBGW = 400;
        nBGH = 250;
    }
    else if(!pItem->m_bMainVer && pItem->m_bMainHor)//��ˮƽ-û�д�ֱ
    {
        nTopSpace   = 0;
        nLeftSpace  = 30;
        nBGW = 340;
        nBGH = 250;
    }
    else if(pItem->m_bMainVer && !pItem->m_bMainHor)//��ˮƽ-û�д�ֱ
    {
        nTopSpace   = 20;
        nLeftSpace  = 0;
        nBGW = 400;
        nBGH = 210;
    }
    double      mMoveX      = 0;                            //���̶�X��ʼ��
    double      mMoveY      = 0;                            //���̶�Y��ʼ��
    double      mLineX      = 0;                            //���̶�X��ʼ��
    double      mLineY      = 0;                            //���̶�Y��ʼ��
    double      MainSpace   = nBGW/nXmain;                  //���̶ȼ��
    double      SubSpace    = nBGW/(nXsub*nXmain);          //�ο̶ȼ��
    QRectItem*  pBackRect;                                  //�������ο�
    QRectItem*  pBGRect;                                    //��ɫ���ο�
    QLineItem*  pLine;
    QLineItem*  pXLine;
    QSimpleTextItem *pText;

    //----------------------��ʼ����������------------------------
    QRectF rect(QPointF(0,0), QSize(400,250));     //�������ο�480,250
//    pBackRect = new QRectItem(rect);
//    pBackRect->SetBackColor(pItem->m_nBoradColor);
//    pBackRect->SetAlpha(0);
//    pBackRect->SetLineType(0);
//    pBackRect->SetName(pItem->m_nBoradColor.name());
//    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
//    pItem->addToGroup(pBackRect);
    //pBackRect->SetAlpha(255);

    //--------------------��ʼ��ͼ������ɫ����--------------------
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

    //--------------------��ʼ��X��̶�--------------------
    for(int i = 0; i <= nXmain; i++)
    {
        QPainterPath mPath;//�����ߵ�path

        if(pItem->m_bMainHor)
        {
            //�����̶�
            mMoveX = i * MainSpace + nLeftSpace;
            mMoveY = nTopSpace + nBGH;
            mLineX = i * MainSpace + nLeftSpace;
            mLineY = nTopSpace + nBGH + ML;

            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);

            pLine = new QLineItem(mPath);
            pLine->setLineType(1);          //��������
            pLine->setLineColor(pItem->m_nScaleColor); //���̶���ɫ
            pLine->SetName(QString("XMainScale%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pLine);

            //�Ƿ���ʾ�ı�
            mLineX  = i * MainSpace + nLeftSpace;
            mLineY  = nTopSpace + nBGH + ML;

            sText   = "XX";//�����Ҫ����ʱ����������Լ��Ժ�Ҫдһ��������
            sText   = GetText(0, pItem->m_nDataSample-1, pItem->m_nHorMajorScale, 0, 0, i, 1);

            pText   = new QSimpleTextItem(rect,sText);
            pText   = DrawTrendText(pText, i, mLineX, mLineY, sText, nFontSizeX, pItem->m_nMarkedColor,0);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pText);
        }

        //��������
        if(pItem->m_bGrade)//�Ƿ���ʾ����
        {
            if(i != 0 && i != nXmain)
            {
                QPainterPath mPath1;               //�����ߵ�path
                mMoveX = i * MainSpace + nLeftSpace;
                mMoveY = nTopSpace;
                mLineX = i * MainSpace + nLeftSpace;
                mLineY = nTopSpace + nBGH;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pXLine = new QLineItem(mPath1);
                pXLine->setLineType(1); //����
                pXLine->setLineColor(pItem->m_nVerColor); //������ɫ
                pXLine->SetName(QString("XMainLine%1").arg(i));
                pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pXLine);
            }
        }
    }

    for(int i = 1; i < nVal; i++)
    {
        if(pItem->m_bSelectHorMinor && pItem->m_bMainHor) //��ʾX��̶�
        {
            QPainterPath mPath; //�����ߵ�path

            //���ο̶�
            mMoveX = i * SubSpace + nLeftSpace;
            mMoveY = nTopSpace + nBGH;
            mLineX = mMoveX;
            mLineY = ML / 2 + nTopSpace + nBGH;

            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);

            pLine = new QLineItem(mPath);
            pLine->setLineType(1); //����
            pLine->setLineColor(pItem->m_nScaleColor); //������ɫ
            pLine->SetName(QString("XSubScale%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pLine);
        }

        //���θ���
        if(pItem->m_bGrade &&  pItem->m_bSelectHorMinor) //�Ƿ���ʾ����
        {
            QPainterPath mPath1;               //�����ߵ�path
            mMoveX = i * SubSpace + nLeftSpace;
            mMoveY = nTopSpace;
            mLineX = mMoveX;
            mLineY = nTopSpace + nBGH;
            mPath1.moveTo(mMoveX,mMoveY);
            mPath1.lineTo(mLineX,mLineY);
            pXLine = new QLineItem(mPath1);
            pXLine->setLineColor(pItem->m_nVerColor); //������ɫ
            pXLine->setLineType(3); //����Ϊ����
            pXLine->SetName(QString("XSubLine%1").arg(i));
            pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pXLine);
        }
    }

    //--------------------��ʼ��Y��̶�--------------------
    MainSpace   = nBGH / nYmain;          //���̶ȼ��
    SubSpace    = nBGH / (nYsub * nYmain);//�ο̶ȼ��
    nVal        = nYsub * nYmain;         //�ο̶�����

    for(int i = 0; i <= nYmain; i++)
    {
        //�����̶�
        QPainterPath mPath;               //�����ߵ�path

        if(pItem->m_bMainVer)
        {
            mMoveX = nLeftSpace - ML;
            mMoveY = i * MainSpace + nTopSpace;
            mLineX = nLeftSpace;
            mLineY = i * MainSpace + nTopSpace;

            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);

            pLine = new QLineItem(mPath);
            pLine->setLineColor(pItem->m_nScaleColor); //������ɫ
            pLine->SetName(QString("YMainScale%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pLine);

            //��ʾY���ı�
            mLineX = nLeftSpace - ML;
            mLineY = i * MainSpace + nTopSpace;
            sText = GetText(pItem->m_nDisplayMin,pItem->m_nDisplayMax,pItem->m_nVertMajorScale,2,1,i,1);
            pText = new QSimpleTextItem(rect,sText);
            pText = DrawTrendText(pText, i, mLineX, mLineY, sText, nFontSizeY, pItem->m_nMarkedColor, 1);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pText);
        }

        //��������
        if(pItem->m_bGrade) //�Ƿ���ʾ����
        {
            if(i != 0 && i != nYmain)
            {
                QPainterPath mPath1;               //�����ߵ�path
                mMoveX = nLeftSpace;
                mMoveY = i * MainSpace + nTopSpace;
                mLineX = nLeftSpace + nBGW;
                mLineY = i * MainSpace + nTopSpace;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath1);
                pLine->setLineColor(pItem->m_nHorColor); //������ɫ
                pLine->SetName(QString("YMainLine%1").arg(i)); //YSubScale
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pItem->addToGroup(pLine);
            }
        }
    }

    for(int i = 1; i < nVal; i++) //���ο̶�
    {
        if(pItem->m_bSelectVertMinor && pItem->m_bMainVer) //��ʾY��̶�
        {
            QPainterPath mPath; //�����ߵ�path
            mMoveX = nLeftSpace - ML / 2;
            mMoveY = i * SubSpace + nTopSpace;
            mLineX = nLeftSpace;
            mLineY = i * SubSpace + nTopSpace;

            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);

            pLine = new QLineItem(mPath);
            pLine->setLineColor(pItem->m_nScaleColor); //������ɫ
            pLine->SetName(QString("YSubScale%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pLine);
        }

        //��Y��θ���
        if(pItem->m_bGrade && pItem->m_bSelectVertMinor) //�Ƿ���ʾ����
        {
            QPainterPath mPath1;               //�����ߵ�path
            mMoveX = nLeftSpace;
            mMoveY = i * SubSpace + nTopSpace;
            mLineX = nLeftSpace + nBGW;
            mLineY = i * SubSpace + nTopSpace;
            mPath1.moveTo(mMoveX,mMoveY);
            mPath1.lineTo(mLineX,mLineY);
            pLine = new QLineItem(mPath1);
            pLine->setLineType(3);
            pLine->setLineColor(pItem->m_nHorColor); //������ɫ
            pLine->SetName(QString("YSubLine%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pItem->addToGroup(pLine);
        }
    }

    //--------------------��ʼ����--------------------
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
    srand(time(0));//��ʼ���������ʱ��
    unsigned int addY = 0;
    for(int j = 0;j < pItem->m_vecChannelGroups.size(); j++)//���ٸ�ͨ�����ж�����
    {
        QPainterPath mPenPath = QPainterPath();
        addY = rand() % (int)nBGH;
        mPenPath.moveTo(QPointF(nLeftSpace, nTopSpace + addY));//��һ��
        for(int i = 1; i <= pointNum; i++)
        {
            mPenPath.lineTo(QPointF(nLeftSpace + i * XPenSpace, nTopSpace + (rand() % (int)nBGH)));
        }

        pPenLine = new QFoldLineItem(mPenPath);
        pPenLine->setLineType(pItem->m_vecChannelGroups.at(j).eLineType);
        pPenLine->setLineColor(pItem->m_vecChannelGroups.at(j).nDisplayColor); //������ɫ
        pPenLine->SetName(QString("PenLine%1").arg(j));
        pPenLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pItem->addToGroup(pPenLine);
    }
}

/***************************************************************
 *�������ƣ�OnDrawTrendChart
 *�������ܣ�������ͼ��XY����ͼ�Լ���ʷ����ͼ����
 *�������壺
 *nType������ͼ���ͣ�1--����ͼ��2--XY����ͼ��3--��ʷ����ͼ
 *pList������ҳ��Ĵ洢��Ϣ
 *edit by zqh
 **************************************************************/
QGraphicsItem* QDrawGraphics::OnDrawTrendChart(int nType,
                                               QStringList *pList)
{
    pGroup = new QItemGroup;
    QString sText = "";
    int i = 0;
    int j = 0;

    QColor mBkColor = pwnd->StringTOColor(pList->at(150)); //����ɫ
    int nPenCount = pList->at(154).toInt();                //�ʵ�����

    QColor mBgColor = pwnd->StringTOColor(pList->at(159)); //��ɫ
    int nLineType[8];
    QColor mPenColor[8];

    //X��
    bool bIfShowX = pList->at(50).toInt();    //�Ƿ���ʾ�̶�
    bool bIfShowGridX = pList->at(51).toInt(); //�Ƿ���ʾY�����
    QColor mAGColorX = pwnd->StringTOColor(pList->at(52));   //��/������ɫ
    QColor mGridColorX = pwnd->StringTOColor(pList->at(53)); //������ɫ
    int nXmain = pList->at(54).toInt(); //���̶�
    int nXsub = pList->at(55).toInt();  //�ο̶�
    bool bIfShowMarkX = pList->at(56).toInt();    //�Ƿ���ʾ�̶ȱ�ʾ
    int nFontSizeX = pList->at(57).toInt();       //�����С
    double xMin = 0;      //x����Сֵ
    double xMax = 0;      //x�����ֵ
    int xPointCount = 0;  //С��λ��
    QString sDate = "";  //��ʷ����ͼ������

    //Y��
    bool bIfShowY = pList->at(20).toInt();    //�Ƿ���ʾ�̶�
    bool bIfShowGridY= pList->at(21).toInt(); //�Ƿ���ʾY�����
    QColor mAGColorY = pwnd->StringTOColor(pList->at(22));   //��/������ɫ
    QColor mGridColorY = pwnd->StringTOColor(pList->at(23)); //������ɫ
    int nYmain = pList->at(24).toInt(); //���̶�
    int nYsub = pList->at(25).toInt();  //�ο̶�
    bool bIfShowMarkY = pList->at(26).toInt();    //�Ƿ���ʾ�̶ȱ�ʾ
    int nFontSizeY = pList->at(27).toInt();       //�����С
    double yMin = pList->at(28).toDouble();       //Y����Сֵ
    double yMax = pList->at(29).toDouble();       //Y�����ֵ
    int yPointCount = pList->at(31).toInt();      //С��λ��
    int bkAlpha = pList->at(162).toInt();      //����ɫ͸����

    /***********************�����ǻ�ͼ����ı���************************/

    int nTopSpace = 20;   //����ɫ����뱳�����������ƫ����
    int nLeftSpace = 80;  //����ɫ����뱳�����������ƫ����
    double nBGW = 400-nLeftSpace-nLeftSpace/2; //��ɫ���εĿ��
    double nBGH = 250-nTopSpace-2*nTopSpace;   //��ɫ���εĸ߶�
    QRectItem *pBackRect; //�������ο�
    QRectItem *pBGRect;   //��ɫ���ο�
    double mMoveX = 0;                //���̶�X��ʼ��
    double mMoveY = 0;                //���̶�Y��ʼ��
    double mLineX = 0;                //���̶�X��ʼ��
    double mLineY = 0;                //���̶�Y��ʼ��
    double MainSpace = nBGW/nXmain;           //���̶ȼ��
    double SubSpace = nBGW/(nXsub*nXmain); //�ο̶ȼ��
    QLineItem *pLine;
    QLineItem *pXLine;
    QSimpleTextItem *pText;
    int ML = 10;                     //�̶ȳ���
    int nVal = nXsub*nXmain; //�ο̶�����

    /*****************************end********************************/

    for(i = 0; i < 8; i++)
    {
        nLineType[i] = pList->at(102+i*4).toInt(); //ÿ���ʵ���ʽ
        mPenColor[i] = pwnd->StringTOColor(pList->at(103+i*4));//�ʵ���ɫ
    }

    switch(nType)
    {
    case 1: //����ͼ
        xMin = 0;
        xMax = pList->at(155).toInt();
        xPointCount = 0;
        xMax--;
        break;
    case 2: //XY����ͼ
        xMin = pList->at(58).toDouble();
        xMax = pList->at(59).toDouble();
        xPointCount = pList->at(61).toInt();
        break;
    case 3: //��ʷ����ͼ
        {
            xMin = pList->at(58).toInt(); //��ʱ���ʽ
            xMax = pList->at(59).toInt()*3600+pList->at(60).toInt()*60+pList->at(61).toInt(); //��ʱ����ת��Ϊ��
            QDate date = QDate::fromString(pList->at(62));
            sDate = QString("%1-%2-%3").arg(date.year()).arg(date.month()).arg(date.day());
        }
        break;
    case 4: //����Ⱥ����ʾ
        xMin = 0;
        xMax = pList->at(155).toInt()-1;
        xPointCount = 0;
        break;
    default:
        break;
    }

    /*****************************************************************
  *��ʼ����������
  ****************************************************************/

    QRectF rect(QPointF(0,0), QSize(400,250));     //�������ο�480,250
    pBackRect = new QRectItem(rect);
    pBackRect->SetBackColor(mBkColor);
    pBackRect->SetLineType(0);
    pBackRect->SetName("mBackRect");
    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->addToGroup(pBackRect);
    pBackRect->SetAlpha(bkAlpha);

    /*****************************************************************
   *��ʼ����ɫ����
   ****************************************************************/
    rect.setTopLeft(QPoint(nLeftSpace,nTopSpace));
    rect.setSize(QSizeF(nBGW,nBGH));
    pBGRect = new QRectItem(rect);
    pBGRect->SetBackColor(mBgColor);
    pBGRect->SetName("mBGRect");
    pBGRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->addToGroup(pBGRect);

    /*****************************************************************
   *��ʼ��X��̶�
   ****************************************************************/

    for(i = 0; i <= nXmain;i++)
    {
        if(bIfShowX) //��ʾX��̶�
        {
            QPainterPath mPath;               //�����ߵ�path
            //�����̶�
            mMoveX = i*MainSpace+nLeftSpace;
            mMoveY = nTopSpace+nBGH;
            mLineX = i*MainSpace+nLeftSpace;
            mLineY = nTopSpace+nBGH+ML;
            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);
            pLine = new QLineItem(mPath);
            pLine->setLineType(1); //����
            pLine->setLineColor(mAGColorX); //���̶���ɫ
            pLine->SetName(QString("XMainScale%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pGroup->addToGroup(pLine);
        }

        //��������
        if(bIfShowGridX) //�Ƿ���ʾ����
        {
            if(i != 0 && i != nXmain)
            {
                QPainterPath mPath1;               //�����ߵ�path
                mMoveX = i*MainSpace+nLeftSpace;
                mMoveY = nTopSpace;
                mLineX = i*MainSpace+nLeftSpace;
                mLineY = nTopSpace+nBGH;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pXLine = new QLineItem(mPath1);
                pXLine->setLineType(1); //����
                pXLine->setLineColor(mGridColorX); //������ɫ
                pXLine->SetName(QString("XMainLine%1").arg(i));
                pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pGroup->addToGroup(pXLine);
            }
        }

        if(bIfShowMarkX) //�Ƿ���ʾ�ı�
        {
            mLineX = i*MainSpace+nLeftSpace;
            mLineY = nTopSpace+nBGH+ML;
            sText = GetText(xMin,xMax,nXmain,xPointCount,0,i,nType);
            pText = new QSimpleTextItem(rect,sText);
            pText = DrawTrendText(pText,i,mLineX,mLineY,sText,nFontSizeX,
                                  mAGColorX,0);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pGroup->addToGroup(pText);
            if(nType == 3) //��ʷ����ͼ
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
            if(bIfShowX) //��ʾX��̶�
            {
                QPainterPath mPath;               //�����ߵ�path
                //���ο̶�
                mMoveX = i*SubSpace+nLeftSpace;
                mMoveY = nTopSpace+nBGH;
                mLineX = mMoveX;
                mLineY = ML/2+nTopSpace+nBGH;
                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath);
                pLine->setLineType(1); //����
                pLine->setLineColor(mAGColorX); //������ɫ
                pLine->SetName(QString("XSubScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pGroup->addToGroup(pLine);
            }

            //���θ���
            if(bIfShowGridX) //�Ƿ���ʾ����
            {
                QPainterPath mPath1;               //�����ߵ�path
                mMoveX = i*SubSpace+nLeftSpace;
                mMoveY = nTopSpace;
                mLineX = mMoveX;
                mLineY = nTopSpace+nBGH;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pXLine = new QLineItem(mPath1);
                pXLine->setLineColor(mGridColorX); //������ɫ
                pXLine->setLineType(3); //����Ϊ����
                pXLine->SetName(QString("XSubLine%1").arg(i));
                pXLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pGroup->addToGroup(pXLine);
            }
        }
    }

    /*****************************************************************
     *��ʼ��Y��̶�
     ****************************************************************/

    MainSpace = nBGH/nYmain;           //���̶ȼ��
    SubSpace = nBGH/(nYsub*nYmain); //�ο̶ȼ��
    nVal = nYsub*nYmain; //�ο̶�����

    for(i = 0; i <= nYmain;i++)
    {
        if(bIfShowY)
        {
            //�����̶�
            QPainterPath mPath;               //�����ߵ�path
            mMoveX = nLeftSpace-ML;
            mMoveY = i*MainSpace+nTopSpace;
            mLineX = nLeftSpace;
            mLineY = i*MainSpace+nTopSpace;
            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);
            pLine = new QLineItem(mPath);
            pLine->setLineColor(mAGColorY); //������ɫ
            pLine->SetName(QString("YMainScale%1").arg(i));
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pGroup->addToGroup(pLine);
        }

        //��������
        if(bIfShowGridY) //�Ƿ���ʾ����
        {
            if(i != 0 && i != nYmain)
            {
                QPainterPath mPath1;               //�����ߵ�path
                mMoveX = nLeftSpace;
                mMoveY = i*MainSpace+nTopSpace;
                mLineX = nLeftSpace+nBGW;
                mLineY = i*MainSpace+nTopSpace;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath1);
                pLine->setLineColor(mGridColorY); //������ɫ
                pLine->SetName(QString("YMainLine%1").arg(i)); //YSubScale
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pGroup->addToGroup(pLine);
            }
        }
        if(bIfShowMarkY) //�Ƿ���ʾ�ı�
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

    for(i = 1; i < nVal;i++) //���ο̶�
    {
        if(i%nYsub != 0  && nYsub != 0)
        {
            //��Y��ο̶�
            if(bIfShowY)
            {
                QPainterPath mPath;               //�����ߵ�path
                mMoveX = nLeftSpace-ML/2;
                mMoveY = i*SubSpace+nTopSpace;
                mLineX = nLeftSpace;
                mLineY = i*SubSpace+nTopSpace;
                mPath.moveTo(mMoveX,mMoveY);
                mPath.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mAGColorY); //������ɫ
                pLine->SetName(QString("YSubScale%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pGroup->addToGroup(pLine);
            }

            //��Y��θ���
            if(bIfShowGridY) //�Ƿ���ʾ����
            {
                QPainterPath mPath1;               //�����ߵ�path
                mMoveX = nLeftSpace;
                mMoveY = i*SubSpace+nTopSpace;
                mLineX = nLeftSpace+nBGW;
                mLineY = i*SubSpace+nTopSpace;
                mPath1.moveTo(mMoveX,mMoveY);
                mPath1.lineTo(mLineX,mLineY);
                pLine = new QLineItem(mPath1);
                pLine->setLineType(3);
                pLine->setLineColor(mGridColorY); //������ɫ
                pLine->SetName(QString("YSubLine%1").arg(i));
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pGroup->addToGroup(pLine);
            }
        }
    }
    /*****************************************************************
   *��ʼ����
   ****************************************************************/
    double YPenSpace = nBGH/8; //Y�᷽��ÿ����֮��ļ��
    double XPenSpace = nBGW/4; //X�᷽��ÿ����֮��ļ��
    QFoldLineItem *pPenLine;

    for(j = 0;j < nPenCount;j++)
    {
        QPainterPath mPenPath = QPainterPath();
        if(j <= 3)
            mPenPath.moveTo(QPointF(nLeftSpace,nTopSpace+nBGH-j*YPenSpace));//��һ��
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
        pPenLine->setLineColor(mPenColor[j]); //������ɫ
        pPenLine->SetName(QString("PenLine%1").arg(j));
        pPenLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pGroup->addToGroup(pPenLine);
    }

    return pGroup;
}

/***************************************************************
 *�������ƣ�GetText
 *�������ܣ�������ͼ��XY����ͼ�Լ���ʷ����ͼ��X���Y���е��ı�����
 *�������壺
 *Min�����ϵ���Сֵ
 *Max�����ϵ����ֵ
 *nMain�����̶�
 *nPointNum��С��λ��
 *nType����ʾ��X���ı�����Y���ı���0--X���ı���1--Y���ı�
 *nIndex�����̶��±��ʾ
 *nKey����ʾ�Ƿ�����ʷ����ͼ,nKey=3��ʾ����ʷ����ͼ������1,2����
 *����ֵ������һ������õ��ı�
 *edit by zqh
 **************************************************************/
QString QDrawGraphics::GetText(double Min, double Max, int nMain,
                               int nPointNum, int nType, int nIndex,
                               int nKey)
{
    double mValue = (Max - Min) / nMain ;
    double dVal = 0;
    QString sText = "";

    if(nKey == 1 || nKey == 2 || nKey == 4)//������ͼ��XY����ͼ
    {
        if(nType == 0)     //��X����ʾ���ı�����С������
        {
            dVal = Min + mValue*nIndex;
            if(nIndex == nMain)
                dVal = Max;
        }
        else if(nType == 1)//��Y����ʾ���ı�����С���µ���
        {
            dVal = Max - mValue*nIndex;
            if(nIndex == nMain)
                dVal = Min;
        }
        //sText.sprintf("%.0f", dVal);
		sText = sText.number(dVal,'f',nPointNum);

    }
    else if(nKey == 3) //����ʷ����ͼ
    {
        if(nType == 0)     //��X����ʾ���ı�����С������
        {
            QString strHour, strMin, strSec;
            int nStepSeconds = Max/nMain+0.5;
            int nHour, nMin, nSec;
            int nSpan = nStepSeconds*nIndex;
            nHour = (nSpan / 3600) % 24;    //���㵥��ʱ��ε�Сʱ��0~23
            nSpan = nSpan % 3600;
            nMin = nSpan / 60;              //���㵥��ʱ��εķ�����
            nSec = nSpan % 60;              //���㵥��ʱ��ε�����
            //��ʽ��Сʱ�����Ӻ��룬С��10����
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
        else if(nType == 1)//��Y����ʾ���ı�����С���µ���
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
 *�������ƣ�DrawTrendText
 *�������ܣ�������ͼ��XY����ͼ�Լ���ʷ����ͼ��X���Y���е��ı�����
 *�������壺
 *pText���ı���ָ��
 *nIndex�����̶��±��ʾ
 *LineX���̶��ı����ڵ�X����
 *LineY���̶��ı����ڵ�Y����
 *sText��Ҫ������ı�����
 *nFontSize���ı��������С
 *pText���ı�����
 *mTextColor��������ɫ
 *nType����ʾ��X���ı�����Y���ı���0--X���ı���1--Y���ı�
 *����ֵ�������ı�ָ��
 *edit by zqh
 **************************************************************/
QSimpleTextItem * QDrawGraphics::DrawTrendText(QSimpleTextItem *pText,
                                               int nIndex, double LineX, double LineY,
                                               QString sText, int nFontSize,
                                               QColor mTextColor,int nTtype)
{
    QString sName = "";
    pText->SetFontSize(nFontSize);
    QFont nfont = pText->GetTextFont(); //�����ı����Ĵ�С
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
 *�������ƣ�drawHisTrendDate
 *�������ܣ�����ʷ����ͼX���ϵ����ں���
 *�������壺
 *nIndex�����̶��±��ʾ
 *LineX���̶��ı����ڵ�X����
 *LineY���̶��ı����ڵ�Y����
 *sText������
 *nFontSize���ı��������С
 *mTextColor��������ɫ
 *����ֵ�������ı�ָ��
 *edit by zqh
 *edit time:2011.8.17
 **************************************************************/
QSimpleTextItem * QDrawGraphics::drawHisTrendDate(int nIndex, double LineX, double LineY, QString sText, int nFontSize,
                                                  QColor mTextColor, bool haveTime)
{
    QRectF Rect(QPointF(0,0), QSize(10,10));     //�������ο�480,250
    QSimpleTextItem *pText = new QSimpleTextItem(Rect,sText);
    QString sName = "";
    pText->SetFontSize(nFontSize);
    QFont nfont = pText->GetTextFont(); //�����ı����Ĵ�С
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
 *�������ƣ�DrawSlider
 *�������ܣ�������ģ��������ͼ�κ���
 *sList�������ݺ��壺
 *0������ɫ
 *1��������ɫ
 *2��ָ�걳��ɫ
 *3��ָ��߿�ɫ
 *4���̶�λ��  1--�ϣ�2--�£�3--��4--��
 *5����ʾ����  0--�������ϣ���1--���ң����£�
 //�̶�ҳ��
 *6���Ƿ���ʾ
 *7���̶�������ɫ
 *8�����̶�
 *9���ο̶�
 *10���Ƿ���ʾ��
 *11���Ƿ���ʾ�̶ȱ�ʾ
 *12�������С
 *13����Сֵ
 *14�����ֵ
 *15��С��λ��
 *����ֵ������һ�����ָ��
 *edit by zqh
 *Date:2011-02-17
 **************************************************************/
QItemGroup* QDrawGraphics::DrawSlider(QStringList sList)
{
    //�����Ǳ����Ķ���
    QColor BackColor = pwnd->StringTOColor(sList.at(0));//����ɫ
    QColor LineColor = pwnd->StringTOColor(sList.at(1));//������ɫ
    QColor BkColor = pwnd->StringTOColor(sList.at(2));  //ָ�걳��ɫ
    QColor FrmColor = pwnd->StringTOColor(sList.at(3)); //ָ��߿�ɫ

    int nPos = sList.at(4).toInt();     //�̶�λ��
    int nDirect = sList.at(5).toInt();  //��ʾ����
    bool bIfShow = sList.at(6).toInt(); //�Ƿ���ʾ
    QColor mColor = pwnd->StringTOColor(sList.at(7)); //�̶�������ɫ
    int nMain = sList.at(8).toInt();    // ���̶�
    int nSub = sList.at(9).toInt();     // �ο̶�
    bool bIfShowZ = sList.at(10).toInt();     // �Ƿ���ʾ��
    bool bIfShowM = sList.at(11).toInt();     // �Ƿ���ʾ�̶ȱ�ʾ
    int nFontSize = sList.at(12).toInt();     //�����С
    double Min = sList.at(13).toDouble();     //��Сֵ
    double Max = sList.at(14).toDouble();     //���ֵ
    int nNum = sList.at(15).toDouble();       //С��λ��

    double RectW = 148.0;  //�������εĿ��108.0
    int nRectH = 32;       //�������εĸ߶�
    int nSpace = 10;        //����ƫ�뱳�����α߿�ľ���

    QPainterPath mPath;               //�����ߵ�path
    double mMoveX = 0;                //���̶�X��ʼ��
    double mLineY = 0;                //���̶�Y��ʼ��
    QItemGroup *pGroup = new QItemGroup;
    QLineItem *pLine;
    int i = 0;
    double nLineW = RectW-2*nSpace;
    double MainSpace = nLineW/(nMain-1);           //���̶ȼ��
    double SubSpace = nLineW/((nSub+1)*(nMain-1)); //�ο̶ȼ��
    int ML = 10;                                  //���̶��ߵĳ���
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
    int nTop = 4; //�߿�ָ��ָ��ľ���
    int nTextW = 0; //�ı��Ŀ��

    QVector <QPoint>mAngle;
    QPoint p1,p2,p3,p4,p5;

    //��ʼ����������
    if(nPos == 1 || nPos == 2) //�̶�λ��  1--�ϣ�2--�£�3--��4--��
    {
        rect.setTopLeft(QPointF(nL,nH));
        rect.setSize(QSizeF(RectW,nRectH)); //���Ʊ߿�ɫ���ο�

        mPath.moveTo(nL+nSpace,nH+nRectH/2);
        mPath.lineTo(nL+nSpace+RectW-2*nSpace,nH+nRectH/2);
    }
    else if(nPos == 3 || nPos == 4)
    {
        rect.setTopLeft(QPointF(nL,nH));
        rect.setSize(QSizeF(nRectH,RectW)); //���Ʊ߿�ɫ���ο�

        mPath.moveTo(nL+nRectH/2,nH+nSpace);
        mPath.lineTo(nL+nRectH/2,nH+nSpace+nLineW);
    }

    pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(BackColor);
    pFramRect->SetLineType(0);
    pFramRect->SetName("mFramRect");
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->addToGroup(pFramRect);           //��ӵ���

    //���ƻ���ֱ��
    pMainLine = new QLineItem(mPath);        //��ϸֱ��
    pMainLine->setLineColor(LineColor);      //����ֱ����ɫ
    pMainLine->SetName("MainLine");          //��������
    pMainLine->setLineWidth(3);
    pMainLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->addToGroup(pMainLine);           //��ӵ���

    //����ָ��
    if(nPos == 1)             //�̶ȵķ�������
    {
        if(nDirect == 0)      //�ı���ʶ�ķ�������
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nSpace+nLineW); p1.setY(nH+nTop);
            p2.setX(nL+nSpace/2+nLineW);p2.setY(nH+nRectH/4);
            p3.setX(nL+nSpace/2+nLineW);p3.setY(nH+3*nRectH/4);
            p4.setX(nL+3*nSpace/2+nLineW);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2+nLineW);p5.setY(nH+nRectH/4);
        }
        else if(nDirect == 1) //�ı���ʶ�ķ�������
        {
            p1.setX(nL+nSpace); p1.setY(nH+nTop);
            p2.setX(nL+nSpace/2);p2.setY(nH+nRectH/4);
            p3.setX(nL+nSpace/2);p3.setY(nH+3*nRectH/4);
            p4.setX(nL+3*nSpace/2);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2);p5.setY(nH+nRectH/4);
        }
    }
    else if(nPos == 2)        //�̶ȵķ�������
    {
        if(nDirect == 0)      //�ı���ʶ�ķ�������
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nSpace/2+nLineW); p1.setY(nH+nRectH/4);
            p2.setX(nL+nSpace/2+nLineW);p2.setY(nH+3*nRectH/4);
            p3.setX(nL+nSpace+nLineW);p3.setY(nH+nRectH-nTop);
            p4.setX(nL+3*nSpace/2+nLineW);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2+nLineW);p5.setY(nH+nRectH/4);
        }
        else if(nDirect == 1) //�ı���ʶ�ķ�������
        {
            p1.setX(nL+nSpace/2); p1.setY(nH+nRectH/4);
            p2.setX(nL+nSpace/2);p2.setY(nH+3*nRectH/4);
            p3.setX(nL+nSpace);p3.setY(nH+nRectH-nTop);
            p4.setX(nL+3*nSpace/2);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2);p5.setY(nH+nRectH/4);
        }
    }
    else if(nPos == 3)        //�̶ȵķ�������
    {
        if(nDirect == 0)      //�ı���ʶ�ķ�������
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nTop); p1.setY(nH+nSpace+nLineW);
            p2.setX(nL+nRectH/4);p2.setY(nH+nSpace/2+nLineW);
            p3.setX(nL+3*nRectH/4);p3.setY(nH+nSpace/2+nLineW);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2+nLineW);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2+nLineW);
        }
        else if(nDirect == 1) //�ı���ʶ�ķ�������
        {
            p1.setX(nL+nTop); p1.setY(nH+nSpace);
            p2.setX(nL+nRectH/4);p2.setY(nH+nSpace/2);
            p3.setX(nL+3*nRectH/4);p3.setY(nH+nSpace/2);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2);
        }
    }
    else if(nPos == 4)        //�̶ȵķ�������
    {
        if(nDirect == 0)      //�ı���ʶ�ķ�������
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nRectH/4); p1.setY(nH+nSpace/2+nLineW);
            p2.setX(nL+3*nRectH/4);p2.setY(nH+nSpace/2+nLineW);
            p3.setX(nL+nRectH-nTop);p3.setY(nH+nSpace+nLineW);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2+nLineW);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2+nLineW);
        }
        else if(nDirect == 1) //�ı���ʶ�ķ�������
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
    pPolyPointer = new QPolygonItem(mAnglePoly);   //������ָ��
    pPolyPointer->setLineType(1);
    pPolyPointer->setBackColor(BkColor);
    pPolyPointer->setLineColor(FrmColor);
    pPolyPointer->SetName("Pointer");                 //��������
    pGroup->addToGroup(pPolyPointer);

    //�������ο̶ȼ��ı�
    nLineW = RectW-2*nSpace;

    if(bIfShow)
    {
        switch(nPos)
        {
        case 1://��������3
            if(bIfShowZ)//��ʾ��
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace,nH);
                mPath.lineTo(nL+nSpace+nLineW,nH);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //����ɫ
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace+i*MainSpace,-ML+nH);
                mPath.lineTo(nL+nSpace+i*MainSpace,nH);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //������ɫ
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
            for(i = 1; i < nVal;i++) //���ο̶�
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(nL+nSpace+i*SubSpace,-ML/2+nH);
                    mPath.lineTo(nL+nSpace+i*SubSpace,nH);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //������ɫ
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 2://��������4
            if(bIfShowZ)//��ʾ��
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace,nH+nRectH);
                mPath.lineTo(nL+nSpace+nLineW,nH+nRectH);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //����ɫ
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace+i*MainSpace,nH+nRectH);
                mPath.lineTo(nL+nSpace+i*MainSpace,ML+nH+nRectH);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //������ɫ
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
            for(i = 1; i < nVal;i++) //���ο̶�
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(nL+nSpace+i*SubSpace,nH+nRectH);
                    mPath.lineTo(nL+nSpace+i*SubSpace,ML/2+nH+nRectH);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //������ɫ
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 3://��������
            if(bIfShowZ)//��ʾ��
            {
                QPainterPath mPath;
                mPath.moveTo(nL,nH+nSpace);
                mPath.lineTo(nL,nH+nSpace+nLineW);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //����ɫ
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(-ML+nL,nH+nSpace+i*MainSpace);
                mPath.lineTo(nL,nH+nSpace+i*MainSpace);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //������ɫ
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
            for(i = 1; i < nVal;i++) //���ο̶�
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(-ML/2+nL,nH+nSpace+i*SubSpace);
                    mPath.lineTo(nL,nH+nSpace+i*SubSpace);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //������ɫ
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 4://��������2
            if(bIfShowZ)//��ʾ��
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nRectH,nH+nSpace);
                mPath.lineTo(nL+nRectH,nH+nSpace+nLineW);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //����ɫ
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nRectH,nH+nSpace+i*MainSpace);
                mPath.lineTo(ML+nL+nRectH,nH+nSpace+i*MainSpace);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //������ɫ
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
            for(i = 1; i < nVal;i++) //���ο̶�
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(nL+nRectH,nH+nSpace+i*SubSpace);
                    mPath.lineTo(ML/2+nL+nRectH,nH+nSpace+i*SubSpace);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //������ɫ
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

    if(nTextDirection == 0) //�ı�����
    {
        dVal = Max - mValue*nIndex;
        if(nIndex == nMain-1)
            dVal = Min;
    }
    else                   //�ı�����
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
        if(sTemp == "-") //�Ǹ�����ʱ��
        {
            sTemp = sText.right(sText.length()-1); //ȡ��ȥ���ŵ�����
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
    QFont nfont = pText->GetTextFont(); //�����ı����Ĵ�С
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
    QFont nfont = pText->GetTextFont(); //�����ı����Ĵ�С
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
 *�������ƣ�drawRecipeSelect
 *�������ܣ����䷽ѡ��������
 *�������壺
 *pList���洢��Ϣ
 *edit by zqh
 *edit time:2011.8.18
 **************************************************************/
QItemGroup* QDrawGraphics::drawRecipeSelect(QStringList *pList)
{
    QColor mBkColor = pwnd->StringTOColor(pList->at(43));         //������ɫ
    int nHNum = pList->at(45).toInt();           //����
    int nType = pList->at(40).toInt(); //0��ʾ�б�1��ʾ������

    double mMoveX = 0;                //���̶�X��ʼ��
    double mMoveY = 0;                //���̶�Y��ʼ��
    double mLineX = 0;                //���̶�X��ʼ��
    double mLineY = 0;                //���̶�Y��ʼ��
    QItemGroup *pGroup = new QItemGroup;
    QLineItem *pLine;
    int i = 0;
    int WH = 100;
    double HVal = 100.0/nHNum;
    QString str = "";

    QRectF rect(QPointF(0,0), QSize(WH,WH));        //���Ʊ߿�ɫ���ο�
    QRectItem *pRect = NULL;

    if(nType == 0) //�б�
    {
        pRect = new QRectItem(rect);
        pRect->SetBackColor(mBkColor);                    //���ñ���ɫ
        pRect->SetName("mRect");
        pGroup->addToGroup(pRect);

        /*********************************************************************
     *�����ǻ�ˮƽ����
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
    else if(nType == 1) //�������б�
    {
        rect.setSize(QSize(108,18));//����������
        pRect = new QRectItem(rect);//QRectItem *
        pRect->SetLineColor(QColor(127,157,185));
        pRect->SetPattern(1);
        pRect->SetBackColor(mBkColor);
        pRect->SetName("mFramRect");
        pRect->setZValue(1);
        pGroup->addToGroup(pRect);
        pRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

        rect.setTopLeft(QPointF(84,0));               //���Ʊ������ο�
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
        mPenPath.moveTo(QPointF(90,7));//��һ��
        mPenPath.lineTo(QPointF(96,11));
        mPenPath.lineTo(QPointF(102,7));
        pLine = new QFoldLineItem(mPenPath);
        pLine->setLineType(1);
        pLine->setLineWidth(2); //�����������
        pLine->setLineColor(QColor(77,97,133)); //������ɫ
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
 *�������ƣ�drawRecipeDisplay
 *�������ܣ����䷽��ʾ������
 *�������壺
 *pList���洢��Ϣ
 *edit by zqh
 *edit time:2011.8.20
 **************************************************************/
QItemGroup* QDrawGraphics::drawRecipeDisplay(QStringList *pList)
{
    int i = 0;
    double mMoveX = 0;                //���̶�X��ʼ��
    double mMoveY = 0;                //���̶�Y��ʼ��
    double mLineX = 0;                //���̶�X��ʼ��
    double mLineY = 0;                //���̶�Y��ʼ��
    int nUseCount = 0;                //����ҳ����ʾ������

    QItemGroup *pGroup = new QItemGroup;
    /**************************ȡһ��ҳ�滭ͼ������*****************************/
    QColor mFBackcolor = pwnd->StringTOColor(pList->at(20));          //��ܵı���ɫ
    QColor mFBorderColor = pwnd->StringTOColor(pList->at(21));    //��ܵı߿�ɫ

    int iLan = pwnd->qLanguagecmb->currentIndex();
    if(iLan < 0)
        iLan = 0;

    int nTFontSize = pList->at(35+iLan*3).toInt();              //������1�����С 35
    QString sTFont = pList->at(36+iLan*3);                  //������1������36
    QColor mTBackColor = pwnd->StringTOColor(pList->at(25));        //�����б���ɫ
    QColor mTTextColor = pwnd->StringTOColor(pList->at(26));         //�����е��ı���ɫ

    QString sNo = pList->at(37+iLan*3); //37
    int nRow = pList->at(27).toInt();                 //����
   // int nType = pList->at(24).toInt(); //0ˮƽѡ��  1��ֱѡ��

    double nH = 25;       //ÿ��ĸ߶� 10
    double nW = 480;      //��������ܿ��120
    double nTexeW = 0;   //�ı��Ŀ��120
    QString sName = "";
    QLineItem *pLine;
    QSimpleTextItem *pText;
    QStringList sDataName;

    /**************************����������*****************************/
    QRectF rect(QPointF(0,0), QSize(nW,(nRow+1)*nH));     //���Ʊ�������
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(mFBackcolor);             //������ı���ɫ
    pFramRect->SetLineColor(mFBorderColor);           //������ı߿�ɫ
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetName("mFramRect");
    pGroup->addToGroup(pFramRect);                    //��ӵ���

    /**************************��������******************************/
    rect.setWidth(nW);                                //���Ʊ�����
    rect.setHeight(nH);
    QRectItem *pTitleRect = new QRectItem(rect);
    pTitleRect->SetBackColor(mTBackColor);            //�����о��ο򱳾�ɫ
    pTitleRect->SetLineType(0);
    pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTitleRect->SetName("mTitleRect");
    pGroup->addToGroup(pTitleRect);                   //��ӵ���

    /**************************�������ı�*****************************/
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

    nTexeW = nW/nUseCount; //�ı�ƽ�����
    for(i = 0; i < nUseCount;i++)
    {
        rect.setTopLeft(QPointF(i*nTexeW,0));           //�����ı�pText
        rect.setSize(QSize(nTexeW,nH));
        pText = new QSimpleTextItem(rect,sDataName.at(i));
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(sTFont);
        pText->SetFontColor(mTTextColor); //������ɫ
        pText->SetName(QString("Text%1").arg(i));
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pGroup->addToGroup(pText);                   //��ӵ���
    }

    /**************************��ˮƽ��******************************/
  //  if(bIfHorizon)   //ѡ����ˮƽѡ���
   // {
        for(i = 0; i < nRow; i++)
        {
            QPainterPath mPath;
            mMoveX = 0;
            mMoveY = i*nH+nH;
            mLineX = 0+nW;
            mLineY = i*nH+nH;
            mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
            mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
            pLine = new QLineItem(mPath);        //��ϸֱ��
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "HLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //��ӵ���
        }
   // }
    /**************************����ֱ��******************************/
  //  if(bIfVertical)  //ѡ���˴�ֱ
 //   {
        for(i = 1; i < nUseCount; i++)
        {
            QPainterPath mPath;
            mMoveX = nTexeW*i;
            mMoveY = 0;
            mLineX = nTexeW*i;
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
            mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
            pLine = new QLineItem(mPath);        //��ϸֱ��
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "VLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //��ӵ���
        }
 //   }
    return pGroup;
}

/************************************************************************
  *�������ƣ�drawHistroyDataDisplayItem
  *�������ܣ�������ʷ������ʾ���ؼ�����
  *�������壺
  *pList:�̶�������Ϣ
  *pTree:ָ��ת��������οؼ�ģ�����ָ��
  *����ֵ:���ػ��ƺ����ʷ������ʾ���ؼ�item
  *edit by zqh
  *2011-9-27
************************************************************************/
QGraphicsItem* QDrawGraphics::drawHistroyDataDisplayItem(QStringList *pList)
{
    int i = 0;
    int nVal = 0;
    double mMoveX = 0;                //���̶�X��ʼ��
    double mMoveY = 0;                //���̶�Y��ʼ��
    double mLineX = 0;                //���̶�X��ʼ��
    double mLineY = 0;                //���̶�Y��ʼ��
    int nUseCount = 0;                //����ҳ����ʾ������

    QItemGroup *pGroup = new QItemGroup;
    /**************************ȡһ��ҳ�滭ͼ������*****************************/
    QColor mFBackcolor = pwnd->StringTOColor(pList->at(21));   //��ܵı���ɫ
    QColor mFBorderColor = pwnd->StringTOColor(pList->at(22));    //��ܵı߿�ɫ
    bool bIfVertical = pList->at(27).toInt();  //�Ƿ�ֱ��ʾ
    bool bIfHorizon = pList->at(28).toInt();//�Ƿ�ˮƽ
    QColor mLineColor = pwnd->StringTOColor(pList->at(23));          //������ɫ

    //int nLanguageCount = pGeneralDlg->ui->m_languagecmb->count();      //��������
    nVal = 10;//pGeneralDlg->TitleText[0].nFontSize;
//    for(i = 1;i < nLanguageCount;i++)                                  //�����������С
//    {
//        if(nVal <  pGeneralDlg->TitleText[i].nFontSize)
//            nVal =  pGeneralDlg->TitleText[i].nFontSize;
//    }
    int nTFontSize = pList->at(40).toInt();//pGeneralDlg->TitleText[0].nFontSize;              //������1�����С
    QString sTFont = pList->at(41);//"System";//pGeneralDlg->TitleText[0].sFont;                  //������1������
    QColor mTBackColor = pwnd->StringTOColor(pList->at(24));         //�����б���ɫ
    QColor mTTextColor = pwnd->StringTOColor(pList->at(25));        //�����е��ı���ɫ
    bool bIfTime = pList->at(31).toInt();        //�Ƿ���ʾʱ����
    QString sTime = pList->at(42);//"Time";                   //������1��ʾʱ������
    bool bIfDate = pList->at(32).toInt();         //�Ƿ���ʾ������
    QString sDate = pList->at(43);//"Date";                   //������1��ʾ��������
    int nRow = pList->at(33).toInt();                    //����

    double nH = 25;       //ÿ��ĸ߶� 10
    double nW = 480;      //��������ܿ��120
    double nTexeW = 0;   //�ı��Ŀ��120
    QString sName = "";
    QLineItem *pLine;
    QSimpleTextItem *pText;
    QStringList sDataName;

    /**************************����������*****************************/
    QRectF rect(QPointF(0,0), QSize(nW,(nRow+1)*nH));     //���Ʊ�������
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(mFBackcolor);             //������ı���ɫ
    pFramRect->SetLineColor(mFBorderColor);           //������ı߿�ɫ
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetName("mFramRect");
    pGroup->addToGroup(pFramRect);                    //��ӵ���

    /**************************��������******************************/
    rect.setWidth(nW);                                //���Ʊ�����
    rect.setHeight(nH);
    QRectItem *pTitleRect = new QRectItem(rect);
    pTitleRect->SetBackColor(mTBackColor);            //�����о��ο򱳾�ɫ
    pTitleRect->SetLineType(0);
    pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTitleRect->SetName("mTitleRect");
    pGroup->addToGroup(pTitleRect);                   //��ӵ���

    /**************************�������ı�*****************************/
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
        if(pList->at(kk).toInt()) //��ʾ��������  pDataDlg->bIfUse[i]
        {
            nUseCount++;
//            int index = pGeneralDlg->ui->m_languagecmb->currentIndex();
//            if(pTree->m_pSamSysParame->m_historyLogData.mSampleList.at(i).sNameList.size() < index +1)
//            {
//                pTree->m_pSamSysParame->m_historyLogData.mSampleList[i].sNameList.resize(index +1);
//            }
            sDataName.append(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.at(i).sNameList.at(0));//����ʾ������ index
        }
        kk++;
    }*/

    nTexeW = nW/nUseCount; //�ı�ƽ�����
    for(i = 0; i < nUseCount;i++)
    {
        rect.setTopLeft(QPointF(i*nTexeW,0));           //�����ı�pText
        rect.setSize(QSize(nTexeW,nH));
        pText = new QSimpleTextItem(rect,sDataName.at(i));
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(sTFont);
        pText->SetFontColor(mTTextColor); //������ɫ
        pText->SetName(QString("Text%1").arg(i));
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pGroup->addToGroup(pText);                   //��ӵ���
    }

    /**************************��ˮƽ��******************************/
    if(bIfHorizon)   //ѡ����ˮƽѡ���
    {
        for(i = 0; i < nRow; i++)
        {
            QPainterPath mPath;
            mMoveX = 0;
            mMoveY = i*nH+nH;
            mLineX = 0+nW;
            mLineY = i*nH+nH;
            mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
            mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
            pLine = new QLineItem(mPath);        //��ϸֱ��
            pLine->setLineColor(mLineColor);     //����ֱ����ɫ
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "HLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //��ӵ���
        }
    }
    /**************************����ֱ��******************************/
    if(bIfVertical)  //ѡ���˴�ֱ
    {
        for(i = 1; i < nUseCount; i++)
        {
            QPainterPath mPath;
            mMoveX = nTexeW*i;
            mMoveY = 0;
            mLineX = nTexeW*i;
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
            mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
            pLine = new QLineItem(mPath);        //��ϸֱ��
            pLine->setLineColor(mLineColor);     //����ֱ����ɫ
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "VLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //��ӵ���
        }
    }
    return pGroup;
}

//����X��ʱ��̶Ȳ�����
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
	if (nType == 1)// ����ʱ��
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
	else          //��������
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
		case UNIT_MINUTE://��
			times = 60;
			break;
		case UNIT_HOUR://ʱ
			times = 3600;
			break;
		case UNIT_DAY://��
			times = 86400;
			break;
		case UNIT_MONTH://��
			times = 2592000;
			break;
		case UNIT_YEAR://��
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
