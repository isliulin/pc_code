#include "qgroupitem.h"
#include "Frame/mainwindow.h"
#include "HeadFile/DefineMacro.h"
#include "QDebug.h"

//#include "view/qlineitem.h"
#include <view/qpolygonitem.h>
#include "view/qlinebasicitem.h"
#include "view/qroundedrectbasic.h"
#include "view/qarcbasicitem.h"

//extern MainWindow *pWnd;
//extern QPointF g_StartPoint;

QGroupItem::QGroupItem(QGraphicsItem *item)
{
    groupItem = item;
}

/*************************************************************************
  �������ƣ�SetPropertyValue(QString qstr, QVariant value)
  �������ܣ������ͼ���е�ָ���Ļ���ͼ�ν��еĲ���
  �������壺
  qstr: �Ի���ͼ�����Բ������������У��磺qstr="shape0.rc1.backcolor",��"."Ϊ�ָ��������ֻ��
        ��������,��������Ĳ�����
  value������ֵ
 *************************************************************************/
void QGroupItem::SetPropertyValue(QString qstr, QVariant value)//��������ֵ QVariant value QColor Color
{
    QString sname1=""; //����ϵ�һ������
    QString sname2=""; //����ϵڶ�������
    QString sname3=""; //�������������
    QString str="";
    int type=0;
    int nSize=0;
    int i=0;
    int nItemCount=0;       //��һ�������item�ĸ���
    int nChilditemCount=0;  //�ڶ��������item�ĸ���
    int j=0;
    QRectItem *RectItem;  //���λ���
    QElipseItem *pCIRCLE; //Բ�����λ���
    QSimpleTextItem *pTEXT;     //�ı�����
    QRoundedRect *pRoundedRect;  //Բ�Ǿ���

    QLineItem * pLine;     //ֱ��
    QPolygonItem *pPoly;   //�����

    QGraphicsItem * newItem;
    QStringList list2 = qstr.split(".", QString::SkipEmptyParts);
    nSize=list2.size();
    if(nSize < 2 && nSize > 3) //exp:"shape0.rc1.backcolor"

        return ;

    QList<QGraphicsItem *> item =groupItem->childItems();//itemAt(StartPoint, pWnd->view->transform()); //����1
    sname1=list2.at(0);
    sname2=list2.at(1);
    nItemCount=item.size();
    if(nItemCount < 1)
        return;

    for(i=0;i < nItemCount;i++)
    {
        if(nSize == 2)
        {
            //type = item.at(i)->type();
            str=item.at(i)->data(GROUP_NAME_KEY).toString();
        }
        else if(nSize == 3)
            str=item.at(i)->data(GROUP_NAME_KEY).toString();

        if(sname1 == str) //����һ�������Ƿ���ͬ
        {
            newItem = item.at(i);

            if(nSize == 2)
            {
                type = newItem->type();
                if(type == SAM_DRAW_OBJECT_RECT) //�ǻ�������
                {
                    RectItem=qgraphicsitem_cast<QRectItem*> (newItem);
                    SetProerty(RectItem,sname2,value);
                    break;
                }
                else if(type == SAM_DRAW_OBJECT_ELIPSE) //�ǻ���Բ������
                {
                    pCIRCLE=qgraphicsitem_cast<QElipseItem*> (newItem);
                    SetProerty(pCIRCLE,sname2,value);
                    break;
                }
                else if(type == SAM_DRAW_OBJECT_TEXT) //�ǻ����ı�
                {
                    pTEXT=qgraphicsitem_cast<QSimpleTextItem *> (newItem);
                    SetProerty(pTEXT,sname2,value);
                    break;
                }
                else if(type == SAM_DRAW_OBJECT_LINE) //ֱ��
                {
                    pLine=qgraphicsitem_cast<QLineItem *> (newItem);
                    SetProerty(pLine,sname2,value);
                    break;
                }

                else if(type == SAM_DRAW_OBJECT_POLYGON) //�����
                {
                    pPoly=qgraphicsitem_cast<QPolygonItem *> (newItem);
                    SetProerty(pPoly,sname2,value);
                    break;
                }
                else if(type == SAM_DRAW_OBJECT_ROUNDEDRECT) //Բ�Ǿ���
                {
                    pRoundedRect=qgraphicsitem_cast<QRoundedRect *> (newItem);
                    SetProerty(pRoundedRect,sname2,value);
                    break;
                }
            }
            else if(nSize == 3)
            {
                nChilditemCount=newItem->childItems().size();
                for(j=0;j < nChilditemCount;j++)
                {
                    type = newItem->childItems().at(j)->type();
                    str=newItem->childItems().at(j)->data(GROUP_NAME_KEY).toString();
                    if(str == sname2) //���ڶ��������Ƿ���ͬ
                    {
                        sname3=list2.at(2);

                        if(type == SAM_DRAW_OBJECT_RECT) //�ǻ�������
                        {
                            RectItem=qgraphicsitem_cast<QRectItem*> (newItem->childItems().at(j));
                            SetProerty(RectItem,sname3,value);
                            break;
                        }
                        else if(type == SAM_DRAW_OBJECT_ELIPSE) //�ǻ���Բ������
                        {
                            pCIRCLE=qgraphicsitem_cast<QElipseItem*> (newItem->childItems().at(j));
                            SetProerty(pCIRCLE,sname3,value);
                            break;
                        }

                        else if(type == SAM_DRAW_OBJECT_TEXT) //�ǻ����ı�
                        {
                            pTEXT=qgraphicsitem_cast<QSimpleTextItem *> (newItem->childItems().at(j));
                            SetProerty(pTEXT,sname3,value);
                            break;
                        }
                        else if(type == SAM_DRAW_OBJECT_LINE) //ֱ��
                        {
                            pLine=qgraphicsitem_cast<QLineItem *> (newItem->childItems().at(j));
                            SetProerty(pLine,sname3,value);
                            break;
                        }
                        else if(type == SAM_DRAW_OBJECT_POLYGON) //�����
                        {
                            pPoly=qgraphicsitem_cast<QPolygonItem *> (newItem->childItems().at(j));
                            SetProerty(pPoly,sname3,value);
                            break;
                        }
                        else if(type == SAM_DRAW_OBJECT_POLYGON) //Բ�Ǿ���
                        {
                            pRoundedRect=qgraphicsitem_cast<QRoundedRect *> (newItem->childItems().at(j));
                            SetProerty(pRoundedRect,sname3,value);
                            break;
                        }
                        break;
                    } //end if
                } //end for
                //SetProerty(RectItem,sname3,value);
            }
        } //end if
    }//end for
}

/*************************************************************************
�������ƣ�SetProerty(QLineItem *pLINE, QString SNAME, QVariant VALUE)
�������ܣ��Ժ���ֱ�ߵ����ͼ�Σ��Ծ��ε����Բ���
�������壺
pLINE��ָ��ֱ�ߵ�ָ��
SNAME����Ҫ���ľ��εĲ�������
VALUE������ֵ
*************************************************************************/
void QGroupItem::SetProerty(QLineItem *pLINE, QString SNAME, QVariant VALUE)
{
    QColor color;

    if(SNAME == "LineColor" || SNAME == "linecolor")       //����������ɫ
    {
        color = StringTOColor(VALUE.toString());
        pLINE->setLineColor(color);
    }
    else if(SNAME == "Visible" || SNAME == "visible")       //�����Ƿ�ɼ�
    {
        pLINE->setVisible(VALUE.toBool());
    }
    else if(SNAME == "LineType" || SNAME == "linetype")       //�����Ƿ�ɼ�
    {
        pLINE->setLineType(VALUE.toInt());
    }
}

/*************************************************************************
�������ƣ�SetProerty(QPolygonItem *pPOLY, QString SNAME, QVariant VALUE)
�������ܣ��Ժ��ж���ε����ͼ�Σ��Ծ��ε����Բ���
�������壺
pPOLY��ָ�����ε�ָ��
SNAME����Ҫ���ľ��εĲ�������
VALUE������ֵ
*************************************************************************/
void QGroupItem::SetProerty(QPolygonItem *pPOLY, QString SNAME, QVariant VALUE)
{
    QColor color;

    if(SNAME == "BackColor" || SNAME == "backcolor")       //���ñ���ɫ
    {
        color = StringTOColor(VALUE.toString());
        pPOLY->setBackColor(color);
    }
}

/*************************************************************************
  �������ƣ�SetProerty(QRectItem *pRECT,QString SNAME, QVariant VALUE)
  �������ܣ��Ժ��о��ε����ͼ�Σ��Ծ��ε����Բ���
  �������壺
  pRECT��ָ����ε�ָ��
  SNAME����Ҫ���ľ��εĲ�������
  VALUE������ֵ
 *************************************************************************/
void QGroupItem::SetProerty(QRectItem *pRECT,QString SNAME, QVariant VALUE)
{
    QColor color;

    if(SNAME == "BackColor" || SNAME == "backcolor")       //���ñ���ɫ
    {
        color = StringTOColor(VALUE.toString());
        pRECT->SetBackColor(color);
    }
    else if(SNAME == "FrontColor" || SNAME == "frontcolor")//����ǰ��ɫ
    {
        color = StringTOColor(VALUE.toString());
        pRECT->SetFrontColor(color);
    }
    else if(SNAME == "LineColor" || SNAME == "linecolor") //����������ɫ
    {
        color = StringTOColor(VALUE.toString());
        pRECT->SetLineColor(color);
    }
    else if(SNAME == "Height" || SNAME == "height")       //���ø߶�
        pRECT->SetHeight(VALUE.toInt());
    else if(SNAME == "Width" || SNAME == "width")         //���ÿ��
        pRECT->SetWidth(VALUE.toInt());
    else if(SNAME == "Left" || SNAME == "left")           //����������
        pRECT->SetLeft(VALUE.toInt());
    else if(SNAME == "Top" || SNAME == "top")             //����������
        pRECT->SetTop(VALUE.toInt());
    else if(SNAME == "Pattern" || SNAME == "pattern")     //������ʽ
        pRECT->SetPattern(VALUE.toInt());
    else if(SNAME == "LineType" || SNAME == "linetype")     //����������ʽ
        pRECT->SetLineType(VALUE.toInt());
    else if(SNAME == "Alpha" || SNAME == "alpha")
        pRECT->SetAlpha(VALUE.toInt());
}

/*************************************************************************
  �������ƣ�SetProerty(QRoundedRect *pRoundRect,QString SNAME, QVariant VALUE)
  �������ܣ��Ժ���Բ�Ǿ��ε����ͼ�Σ���Բ�����Բ���
  �������壺
  pRoundRect��ָ��Բ�Ǿ��ε�ָ��
  SNAME����Ҫ����Բ�Ĳ�������
  VALUE������ֵ
  20110-03-16
 *************************************************************************/
void QGroupItem::SetProerty(QRoundedRect *pRoundRect, QString SNAME, QVariant VALUE)
{
    QColor color;
    if(SNAME == "BackColor" || SNAME == "backcolor")       //���ñ���ɫ
    {
        color = StringTOColor(VALUE.toString());
        pRoundRect->SetBackColor(color);
    }
    else if(SNAME == "FrontColor" || SNAME == "frontcolor")//����ǰ��ɫ
    {
        color = StringTOColor(VALUE.toString());
        pRoundRect->SetFrontColor(color);
    }
    else if(SNAME == "LineColor" || SNAME == "linecolor") //����������ɫ
    {
        color = StringTOColor(VALUE.toString());
        pRoundRect->SetLineColor(color);
    }
    else if(SNAME == "Height" || SNAME == "height")       //���ø߶�
        pRoundRect->SetHeight(VALUE.toInt());
    else if(SNAME == "Width" || SNAME == "width")         //���ÿ��
        pRoundRect->SetWidth(VALUE.toInt());
    else if(SNAME == "Pattern" || SNAME == "pattern")     //������ʽ
        pRoundRect->SetPattern(VALUE.toInt());
    else if(SNAME == "LineType" || SNAME == "linetype")     //����������ʽ
        pRoundRect->SetLineType(VALUE.toInt());
    else if(SNAME == "Alpha" || SNAME == "alpha")
        pRoundRect->SetAlpha(VALUE.toInt());
}

/*************************************************************************
  �������ƣ�SetProerty(QCircleItem *pCIRCLE,QString SNAME, QVariant VALUE)
  �������ܣ��Ժ���Բ�����ͼ�Σ���Բ�����Բ���
  �������壺
  pCIRCLE��ָ��Բ��ָ��
  SNAME����Ҫ����Բ�Ĳ�������
  VALUE������ֵ
 *************************************************************************/
void QGroupItem::SetProerty(QElipseItem *pCIRCLE, QString SNAME, QVariant VALUE)
{
    QColor color;

    if(SNAME == "BackColor" || SNAME == "backcolor")       //���ñ���ɫ
    {
        color = StringTOColor(VALUE.toString());
        pCIRCLE->SetBackColor(color);
    }
    else if(SNAME == "FrontColor" || SNAME == "frontcolor")//����ǰ��ɫ
    {
        color = StringTOColor(VALUE.toString());
        pCIRCLE->SetFrontColor(color);
    }
    else if(SNAME == "LineColor" || SNAME == "linecolor")  //����������ɫ
    {
        color = StringTOColor(VALUE.toString());
        pCIRCLE->SetLineColor(color);
    }
    else if(SNAME == "Height" || SNAME == "height")        //���ø߶�
        pCIRCLE->SetHeight(VALUE.toInt());
    else if(SNAME == "Width" || SNAME == "width")          //���ÿ��
        pCIRCLE->SetWidth(VALUE.toInt());
    else if(SNAME == "Left" || SNAME == "left")            //����������
        pCIRCLE->SetLeft(VALUE.toInt());
    else if(SNAME == "Top" || SNAME == "top")              //����������
        pCIRCLE->SetTop(VALUE.toInt());
    else if(SNAME == "Pattern" || SNAME == "pattern")      //������ʽ
        pCIRCLE->SetPattern(VALUE.toInt());
    else if(SNAME == "SpanAngle" || SNAME == "spanangle")  //���ÿ�ȽǶ�
        pCIRCLE->SetSpanAngle(VALUE.toInt());
    else if(SNAME == "StartAngle" || SNAME == "startangle")//���ÿ�ʼ�Ƕ�
        pCIRCLE->SetStartAngle(VALUE.toInt());
    else if(SNAME == "LineType" || SNAME == "lineTtype")   //����������ʽ
        pCIRCLE->SetLineType(VALUE.toInt());
}

/*************************************************************************
  �������ƣ�SetProerty(QSimpleTextItem *pTEXT,QString SNAME, QVariant VALUE)
  �������ܣ��Ժ����ı������ͼ�Σ����ı������Բ���
  �������壺
  pTEX��ָ���ı���ָ��
  SNAME����Ҫ�����ı��Ĳ�������
  VALUE������ֵ
 *************************************************************************/
void QGroupItem::SetProerty(QSimpleTextItem *pTEXT, QString SNAME, QVariant VALUE)
{
    QColor color;
    
    if(SNAME == "Text" || SNAME == "text")                      //�����ı�
        pTEXT->SetText(VALUE.toString());
    else if(SNAME == "FontSize" || SNAME == "fontsize")         //���������С
        pTEXT->SetFontSize(VALUE.toInt());
    else if(SNAME == "Font" || SNAME == "font")                 //��������
        pTEXT->SetFontName(VALUE.toString());
    else if(SNAME == "FontColor" || SNAME == "fontcolor")       //����������ɫ
    {
        color = StringTOColor(VALUE.toString());
        pTEXT->SetFontColor(color);
    }
    else if(SNAME == "FontBold" || SNAME == "fontbold")         //�����ı�Ϊ����
        pTEXT->SetFontBold(VALUE.toBool());
    else if(SNAME == "FontItalic" || SNAME == "fontitalic")     //�����ı�Ϊб��
        pTEXT->SetFontItalic(VALUE.toBool());
    else if(SNAME == "WordInterval" || SNAME == "wordinterval") //�����־�
        pTEXT->SetFontWordInterval(VALUE.toInt());
    else if(SNAME == "UnderLine" || SNAME == "underline")       //�����ı����»���
        pTEXT->SetFontUnderLine(VALUE.toBool());
    else if(SNAME == "Alignment" || SNAME == "alignment")       //�����ı����뷽ʽ
        pTEXT->SetTextAlign(VALUE.toInt());
    else if(SNAME == "Pattern" || SNAME == "pattern")           //�����ı���ʽ
        pTEXT->SetPattern(VALUE.toInt());
    else if(SNAME == "LineInterval" || SNAME == "lineinterval") //�����ı��о�
        pTEXT->SetLineInterval(VALUE.toInt());
    else if(SNAME == "Alpha" || SNAME == "alpha")           //͸����
        pTEXT->SetAlpha(VALUE.toInt());
    else if(SNAME == "BFitSize" || SNAME == "bFitSize")   //����Ӧ
        pTEXT->SetFitSize(VALUE.toBool());
    else if(SNAME == "Visible" || SNAME == "visible")           //�����Ƿ�ɼ�
    {
        pTEXT->setVisible(VALUE.toBool());
    }
}

QColor QGroupItem::StringTOColor(QString sColor)
{
    QColor color;
    QStringList sList = sColor.split("+", QString::SkipEmptyParts);
    color.setRed(sList.at(0).toInt());
    color.setGreen(sList.at(1).toInt());
    color.setBlue(sList.at(2).toInt());
    return color;
}
void QGroupItem::SetGroupVisible(bool nFLAG) //���ø��������ֻ�������
{
    int nSize=0;
    QGraphicsItem *childitem;
    QList<QGraphicsItem *> item=groupItem->childItems();
    nSize=item.size();
    if(nSize < 1)
        return;

    for(int i=0;i < nSize;i++)
    {
        childitem=item.at(i);
        childitem->setVisible(nFLAG);
    }
}
//���� ��ǰitemĳ��shape��ʾ������
void QGroupItem::SetShapeVisible(QString name,bool nFLAG) //���ø��������ֻ�������
{
    int nSize=0;
    QString str;
    //QGraphicsItem *childitem;
    QList<QGraphicsItem *> item=groupItem->childItems();
    nSize=item.size();
    if(nSize < 1)
        return;

    for(int i=0;i < nSize;i++)
    {
        str=item.at(i)->data(GROUP_NAME_KEY).toString();
        if(name == str) //����һ�������Ƿ���ͬ
        {
            item.at(i)->setVisible(nFLAG);
        }
    }
}
//��ø�ҳ���ͼ��
QPixmap* QGroupItem::Pictrue()
{
    int nSize = 0;
    QPixmap *pTmp = new QPixmap();
    bool bValue = false;

    QPixmapItem *picItem = NULL;
    QList<QGraphicsItem *> itemList=groupItem->childItems();
    nSize=itemList.size();
    if(nSize < 1)
        return NULL;
    for(int i=0;i < nSize;i++)
    {
        if (itemList.at(i)->type() == SAM_DRAW_OBJECT_PIXMAP)
        {
            picItem = qgraphicsitem_cast<QPixmapItem *>(itemList.at(i));
            if (picItem)
            {
                *pTmp = picItem->getPixmap();
                bValue = true;
                break;
            }
        }
    }
    if (!bValue)
    {
        return NULL;
    }
    else
    {
        return pTmp;
    }
}
QPixmap* QGroupItem::PictrueOn()
{
    QPixmap *pTmp = new QPixmap();
    int nSize=0;
    QList<QGraphicsItem *> itemList=groupItem->childItems();
    nSize=itemList.size();
    if(nSize < 1)
        return NULL;
    for(int i=0;i < nSize;i++)
    {
        QGroupItem *childitem = new QGroupItem(itemList.at(i));
        if (childitem->GetName() == "Shape1")
        {
            pTmp = childitem->Pictrue();
            break;
        }
    }
    return pTmp;
}

QPixmap* QGroupItem::PictrueOff()
{
    QPixmap *pTmp = new QPixmap();
    int nSize=0;
    QList<QGraphicsItem *> itemList=groupItem->childItems();
    nSize=itemList.size();
    if(nSize < 1)
        return NULL;
    for(int i=0;i < nSize;i++)
    {
        QGroupItem *childitem = new QGroupItem(itemList.at(i));
        if (childitem->GetName() == "Shape0")
        {
            pTmp = childitem->Pictrue();
            break;
        }
    }
    return pTmp;
}
//���һ��ҳ����ı�
QString QGroupItem::Text()
{
    QString sTmp;
    int nSize = 0;
    QSimpleTextItem *textItem = NULL;
    QList<QGraphicsItem *> itemList=groupItem->childItems();
    nSize=itemList.size();
    if(nSize < 1)
        return sTmp;
    for(int i=0;i < nSize;i++)
    {
        if (itemList.at(i)->type() == SAM_DRAW_OBJECT_TEXT)
        {
            textItem = qgraphicsitem_cast<QSimpleTextItem *>(itemList.at(i));
            if (textItem)
            {
                sTmp = textItem->GetText();
                break;
            }
        }
    }
    return sTmp;
}
QString QGroupItem::TextOn()
{
    QString sTmp;
    int nSize=0;
    QList<QGraphicsItem *> itemList=groupItem->childItems();
    nSize=itemList.size();
    if(nSize < 1)
        return sTmp;
    for(int i=0;i < nSize;i++)
    {
        QGroupItem *childitem = new QGroupItem(itemList.at(i));
        if (childitem->GetName() == "Shape1")
        {
            sTmp = childitem->Text();
            break;
        }
    }
    return sTmp;
}
QString QGroupItem::TextOff()
{
    QString sTmp;
    int nSize=0;
    QList<QGraphicsItem *> itemList=groupItem->childItems();
    nSize=itemList.size();
    if(nSize < 1)
        return sTmp;
    for(int i=0;i < nSize;i++)
    {
        QGroupItem *childitem = new QGroupItem(itemList.at(i));
        if (childitem->GetName() == "Shape0")
        {
            sTmp = childitem->Text();
            break;
        }
    }
    return sTmp;
}
void QGroupItem::SetLeft(int nLeft) //����������
{
    //QGraphicsItem *item=pWnd->scene[pWnd->nActiveSheetIndex]->itemAt(g_StartPoint, pWnd->view->transform()); //����2
    QGraphicsItem *item1=groupItem->parentItem();
    if(item1)
    {
       item1->setX(nLeft);
    }
}

void QGroupItem::SetTop(int nTop) //����������
{
    //QGraphicsItem *item=pWnd->scene[pWnd->nActiveSheetIndex]->itemAt(g_StartPoint, pWnd->view->transform()); //����2
    QGraphicsItem *item1=groupItem->parentItem();
    if(item1)
    {
       item1->setY(nTop);
    }
}

int QGroupItem::GetLeft()
{
    QRectF nRect;
    QGraphicsItem *item1=groupItem->parentItem();
    nRect=item1->sceneBoundingRect();
    return nRect.x();
}
int QGroupItem::GetTop()
{
    QRectF nRect;
    QGraphicsItem *item1=groupItem->parentItem();
    nRect=item1->sceneBoundingRect();
    return nRect.y();
}

void QGroupItem::SetWidth(qreal nWidth)
{
    QItemGroup *pItemGroup =NULL;
    QRectItem *pRect       = NULL;
    QElipseItem *pElipse   = NULL;
    QLineItem *pLine       = NULL;
    QPolygonItem *pPolygon   = NULL;
    QFoldLineItem *pFoldLine = NULL;
    QFreeLineItem *pFreeLine = NULL;
    QLineCircleItem *pLineCircle = 0;
    QSimpleTextItem *pText = NULL;
    QRoundedRect *pRoundedRect = NULL;
    QPixmapItem *pPix = NULL;
    QArcItem *pArc = NULL;

    QRectBasicItem *pRectNew       = NULL;
    QElipseBasicItem *pElipseNew   = NULL;
    QLineBasicItem *pLineNew       = NULL;
    QPolygonBasicItem *pPolygonNew   = NULL;
    QFoldLineBasicItem *pFoldLineNew = NULL;
    QFreeLineBasicItem *pFreeLineNew = NULL;
    QLineCircleBasicItem *pLineCircleNew = 0;
    QRoundedRectBasic *pRoundedRectNew = NULL;
    QArcBasicItem *pArcNew = NULL;

    QList<QPolygonF> polygonList;
    QRectF qrcBndRect, qrcSetRect;
    qrcBndRect=groupItem->sceneBoundingRect();
    if (qrcBndRect.width() <= 0)
    {
        return;
    }
    qreal dXFactor = nWidth / qrcBndRect.width();
    qreal dYFactor = 1;
    switch(groupItem->type())
    {
    case SAM_DRAW_OBJECT_GROUP:
        pItemGroup = dynamic_cast<QItemGroup *>(groupItem);
        m_selectTool.moveGroupHandle(pItemGroup, qrcBndRect, dXFactor, 1, (unsigned long)SAM_DRAW_RECT_BOTTOM_RIGHT);
        break;
    case SAM_DRAW_OBJECT_RECT:
        pRect = dynamic_cast<QRectItem *> (groupItem);
        if (!pRect)
        {
            break;
        }
        qrcSetRect = qrcBndRect;
        qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
        qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
        qrcSetRect = pRect->mapRectFromScene(qrcSetRect);
        pRect->setRectA(qrcSetRect);
        break;
    case SAM_DRAW_OBJECT_ELIPSE:
        pElipse = dynamic_cast<QElipseItem *> (groupItem);
        if (!pElipse)
        {
            break;
        }
        qrcSetRect = qrcBndRect;
        qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
        qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
        qrcSetRect = pElipse->mapRectFromScene(qrcSetRect);
        pElipse->setRect(qrcSetRect);
        break;
    case SAM_DRAW_OBJECT_LINE:
        pLine = dynamic_cast<QLineItem *> (groupItem);
        if (pLine)
        {
            QPainterPath path = pLine->path();
            QList<QPolygonF> polygons = path.toSubpathPolygons();
            if (polygons.size() <= 0)
            {
                break;
            }

            int iSize = polygons[0].size();
            for (int j = 0; j < iSize; j++)
            {
                polygons[0][j] = pLine->mapToScene(polygons[0][j]);
                polygons[0][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                polygons[0][j] = pLine->mapFromScene(polygons[0][j]);
                path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
            }
            pLine->setPath(path);
            pLine->refreshEndArrow();
        }

        break;
    case SAM_DRAW_OBJECT_POLYGON:
        pPolygon = dynamic_cast<QPolygonItem *> (groupItem);
        if (pPolygon)
        {
            QPolygonF polygonPoints = pPolygon->polygon();
            for (int i = 0; i < polygonPoints.size(); i++)
            {
                polygonPoints[i] = pPolygon->mapToScene(polygonPoints[i]);
                polygonPoints[i] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygonPoints[i], qrcBndRect, dXFactor, dYFactor);
                polygonPoints[i] = pPolygon->mapFromScene(polygonPoints[i]);
            }
            pPolygon->setPolygon(polygonPoints);
        }
        break;
    case SAM_DRAW_OBJECT_FOLDLINE:
        pFoldLine = dynamic_cast<QFoldLineItem *> (groupItem);
        if (pFoldLine)
        {
            QPainterPath path = pFoldLine->path();
            QList<QPolygonF> polygons = path.toSubpathPolygons();
            if (polygons.size() <= 0)
            {
                break;
            }

            int iSize = polygons[0].size();
            for (int j = 0; j < iSize; j++)
            {
                polygons[0][j] = pFoldLine->mapToScene(polygons[0][j]);
                polygons[0][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                polygons[0][j] = pFoldLine->mapFromScene(polygons[0][j]);
                path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
            }
            pFoldLine->setPath(path);
            pFoldLine->refreshEndArrow();
        }
        break;
    case SAM_DRAW_OBJECT_FREELINE:
        pFreeLine = dynamic_cast<QFreeLineItem *> (groupItem);
        if (pFreeLine)
        {
            QPainterPath path = pFreeLine->path();
            QList<QPolygonF> polygons = path.toSubpathPolygons();
            if (polygons.size() <= 0)
            {
                break;
            }

            int iSize = polygons[0].size();
            for (int j = 0; j < iSize; j++)
            {
                polygons[0][j] = pFreeLine->mapToScene(polygons[0][j]);
                polygons[0][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                polygons[0][j] = pFreeLine->mapFromScene(polygons[0][j]);
                path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
            }
            pFreeLine->setPath(path);
            pFreeLine->refreshEndArrow();
        }
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE:
        pLineCircle = dynamic_cast<QLineCircleItem *> (groupItem);
        if (pLineCircle)
        {
            QPainterPath ipath = pLineCircle->path();
            polygonList = ipath.toSubpathPolygons();
            int iPolygonListSize = polygonList.size();
            if (pLineCircle->m_eLineEndArrowType != LINE_END_STYLE_NONE)
            {
                iPolygonListSize--;
            }
            for (int i = 0; i < iPolygonListSize; i++)
            {
                for (int j = 0; j < polygonList[i].size(); j++)
                {
                    polygonList[i][j] = pLineCircle->mapToScene(polygonList[i][j]);
                    polygonList[i][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygonList[i][j], qrcBndRect, dXFactor, dYFactor);
                    polygonList[i][j] = pLineCircle->mapFromScene(polygonList[i][j]);
                }
            }

            QPainterPath allPath;
            for(int i = 0; i < iPolygonListSize; i++)
            {
                QPainterPath subPath = QPainterPath();
                subPath.addPolygon(polygonList.at(i));
                allPath.addPath(subPath);
            }
            pLineCircle->setPath(allPath);
            pLineCircle->refreshEndArrow();
        }
        break;
    case SAM_DRAW_OBJECT_TEXT:
        pText = dynamic_cast<QSimpleTextItem *> (groupItem);
        if (pText)
        {
              qrcSetRect = qrcBndRect;

              qreal rWidth = qrcSetRect.width() * dXFactor;
              pText->SetWidth(rWidth);
        }
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
        pRoundedRect = dynamic_cast<QRoundedRect *> (groupItem);
        if (pRoundedRect)
        {
            qrcSetRect = qrcBndRect;
            qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
            qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
            qrcSetRect = pRoundedRect->mapRectFromScene(qrcSetRect);
            pRoundedRect->setRectA(qrcSetRect);

            //pRoundedRect->SetWidth(qrcSetRect.width() * dXFactor);
        }
        break;
    case SAM_DRAW_OBJECT_ARC:
        pArc = dynamic_cast<QArcItem *> (groupItem);
        if (pArc)
        {
            qrcSetRect = qrcBndRect;
            pArc->SetWidth(qrcSetRect.width() * dXFactor);
        }
        break;
/*****************wxy add start */
    case SAM_DRAW_OBJECT_RECT_NEW:
        pRectNew = dynamic_cast<QRectBasicItem *> (groupItem);
        if (!pRectNew)
        {
            break;
        }
        qrcSetRect = qrcBndRect;
        qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
        qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
        qrcSetRect = pRectNew->mapRectFromScene(qrcSetRect);
        pRectNew->setRectA(qrcSetRect);
        break;
    case SAM_DRAW_OBJECT_ELIPSE_NEW:
        pElipseNew = dynamic_cast<QElipseBasicItem *> (groupItem);
        if (!pElipseNew)
        {
            break;
        }
        qrcSetRect = qrcBndRect;
        qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
        qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
        qrcSetRect = pElipseNew->mapRectFromScene(qrcSetRect);
        pElipseNew->setRect(qrcSetRect);
        break;
    case SAM_DRAW_OBJECT_LINE_NEW:
        pLineNew = dynamic_cast<QLineBasicItem *> (groupItem);
        if (pLineNew)
        {
            QPainterPath path = pLineNew->path();
            QList<QPolygonF> polygons = path.toSubpathPolygons();
            if (polygons.size() <= 0)
            {
                break;
            }

            int iSize = polygons[0].size();
            for (int j = 0; j < iSize; j++)
            {
                polygons[0][j] = pLineNew->mapToScene(polygons[0][j]);
                polygons[0][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                polygons[0][j] = pLineNew->mapFromScene(polygons[0][j]);
                path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
            }
            pLineNew->setPath(path);
            pLineNew->refreshEndArrow();
        }

        break;
    case SAM_DRAW_OBJECT_POLYGON_NEW:
        pPolygonNew = dynamic_cast<QPolygonBasicItem *> (groupItem);
        if (pPolygonNew)
        {
            QPolygonF polygonPoints = pPolygonNew->polygon();
            for (int i = 0; i < polygonPoints.size(); i++)
            {
                polygonPoints[i] = pPolygonNew->mapToScene(polygonPoints[i]);
                polygonPoints[i] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygonPoints[i], qrcBndRect, dXFactor, dYFactor);
                polygonPoints[i] = pPolygonNew->mapFromScene(polygonPoints[i]);
            }
            pPolygonNew->setPolygon(polygonPoints);
        }
        break;
    case SAM_DRAW_OBJECT_FOLDLINE_NEW:
        pFoldLineNew = dynamic_cast<QFoldLineBasicItem *> (groupItem);
        if (pFoldLineNew)
        {
            QPainterPath path = pFoldLineNew->path();
            QList<QPolygonF> polygons = path.toSubpathPolygons();
            if (polygons.size() <= 0)
            {
                break;
            }

            int iSize = polygons[0].size();
            for (int j = 0; j < iSize; j++)
            {
                polygons[0][j] = pFoldLineNew->mapToScene(polygons[0][j]);
                polygons[0][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                polygons[0][j] = pFoldLineNew->mapFromScene(polygons[0][j]);
                path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
            }
            pFoldLineNew->setPath(path);
            pFoldLineNew->refreshEndArrow();
        }
        break;
    case SAM_DRAW_OBJECT_FREELINE_NEW:
        pFreeLineNew = dynamic_cast<QFreeLineBasicItem *> (groupItem);
        if (pFreeLineNew)
        {
            QPainterPath path = pFreeLineNew->path();
            QList<QPolygonF> polygons = path.toSubpathPolygons();
            if (polygons.size() <= 0)
            {
                break;
            }

            int iSize = polygons[0].size();
            for (int j = 0; j < iSize; j++)
            {
                polygons[0][j] = pFreeLineNew->mapToScene(polygons[0][j]);
                polygons[0][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                polygons[0][j] = pFreeLineNew->mapFromScene(polygons[0][j]);
                path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
            }
            pFreeLineNew->setPath(path);
            pFreeLineNew->refreshEndArrow();
        }
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
        pLineCircleNew = dynamic_cast<QLineCircleBasicItem *> (groupItem);
        if (pLineCircleNew)
        {
            QPainterPath ipath = pLineCircleNew->path();
            polygonList = ipath.toSubpathPolygons();
            int iPolygonListSize = polygonList.size();
            if (pLineCircleNew->m_eLineEndArrowType != LINE_END_STYLE_NONE)
            {
                iPolygonListSize--;
            }
            for (int i = 0; i < iPolygonListSize; i++)
            {
                for (int j = 0; j < polygonList[i].size(); j++)
                {
                    polygonList[i][j] = pLineCircleNew->mapToScene(polygonList[i][j]);
                    polygonList[i][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygonList[i][j], qrcBndRect, dXFactor, dYFactor);
                    polygonList[i][j] = pLineCircleNew->mapFromScene(polygonList[i][j]);
                }
            }

            QPainterPath allPath;
            for(int i = 0; i < iPolygonListSize; i++)
            {
                QPainterPath subPath = QPainterPath();
                subPath.addPolygon(polygonList.at(i));
                allPath.addPath(subPath);
            }
            pLineCircleNew->setPath(allPath);
            pLineCircleNew->refreshEndArrow();
        }
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
        pRoundedRectNew = dynamic_cast<QRoundedRectBasic *> (groupItem);
        if (pRoundedRectNew)
        {
            qrcSetRect = qrcBndRect;
            qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
            qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
            qrcSetRect = pRoundedRectNew->mapRectFromScene(qrcSetRect);
            pRoundedRectNew->setRectA(qrcSetRect);

            //qrcSetRect = qrcBndRect;
            //pRoundedRectNew->SetWidth(qrcSetRect.width() * dXFactor);
        }
        break;
    case SAM_DRAW_OBJECT_ARC_NEW:
        pArcNew = dynamic_cast<QArcBasicItem *> (groupItem);
        if (pArcNew)
        {
            qrcSetRect = qrcBndRect;
            pArcNew->SetWidth(qrcSetRect.width() * dXFactor);
        }
        break;
/*****************wxy add end*/
    case SAM_DRAW_OBJECT_PIXMAP:
        pPix = dynamic_cast<QPixmapItem *> (groupItem);
        if (pPix)
        {
            QRectF rc = pPix->sceneBoundingRect();
            pPix->updateSize(rc);
            rc = QRectF(rc.top(),rc.left(),nWidth,rc.height());
            pPix->updatePic(rc);
        }
        break;
        default:
            break;
    }
}

void QGroupItem::SetHeigth(qreal nHeight)
{
    QItemGroup *pItemGroup =NULL;
    QRectItem *pRect       = NULL;
    QElipseItem *pElipse   = NULL;
    QLineItem *pLine       = NULL;
    QPolygonItem *pPolygon   = NULL;
    QFoldLineItem *pFoldLine = NULL;
    QFreeLineItem *pFreeLine = NULL;
    QLineCircleItem *pLineCircle = 0;
    QSimpleTextItem *pText = NULL;
    QPixmapItem *pPix = NULL;
    QRoundedRect *pRoundedRect = NULL;
    QArcItem *pArc = NULL;

    QRectBasicItem *pRectNew       = NULL;
    QElipseBasicItem *pElipseNew   = NULL;
    QLineBasicItem *pLineNew       = NULL;
    QPolygonBasicItem *pPolygonNew   = NULL;
    QFoldLineBasicItem *pFoldLineNew = NULL;
    QFreeLineBasicItem *pFreeLineNew = NULL;
    QLineCircleBasicItem *pLineCircleNew = 0;
    QRoundedRectBasic *pRoundedRectNew = NULL;
    QArcBasicItem *pArcNew = NULL;

    QList<QPolygonF> polygonList;
    QRectF qrcBndRect, qrcSetRect;
    qrcBndRect=groupItem->sceneBoundingRect();
    if (qrcBndRect.height() <= 0)
    {
        return;
    }
    qreal dYFactor = nHeight / qrcBndRect.height();
    qreal dXFactor = 1;
    switch(groupItem->type())
    {
    case SAM_DRAW_OBJECT_GROUP:
        pItemGroup = dynamic_cast<QItemGroup *>(groupItem);
        m_selectTool.moveGroupHandle(pItemGroup, qrcBndRect, dXFactor, dYFactor, (unsigned long)SAM_DRAW_RECT_BOTTOM_RIGHT);
        break;
    case SAM_DRAW_OBJECT_RECT:
        pRect = dynamic_cast<QRectItem *> (groupItem);
        if (!pRect)
        {
            break;
        }
        qrcSetRect = qrcBndRect;
        qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
        qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
        qrcSetRect = pRect->mapRectFromScene(qrcSetRect);
        pRect->setRectA(qrcSetRect);
        break;
    case SAM_DRAW_OBJECT_PIXMAP:
        pPix = dynamic_cast<QPixmapItem *> (groupItem);
        if (pPix)
        {
            QRectF rc = pPix->sceneBoundingRect();
            pPix->updateSize(rc);
            rc = QRectF(rc.top(),rc.left(),rc.width(),nHeight);
            pPix->updatePic(rc);
        }
        break;
    case SAM_DRAW_OBJECT_ELIPSE:
        pElipse = dynamic_cast<QElipseItem *> (groupItem);
        if (!pElipse)
        {
            break;
        }
        qrcSetRect = qrcBndRect;
        qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
        qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
        qrcSetRect = pElipse->mapRectFromScene(qrcSetRect);
        pElipse->setRect(qrcSetRect);
        break;
    case SAM_DRAW_OBJECT_LINE:
        pLine = dynamic_cast<QLineItem *> (groupItem);
        if (pLine)
        {
            QPainterPath path = pLine->path();
            QList<QPolygonF> polygons = path.toSubpathPolygons();
            if (polygons.size() <= 0)
            {
                break;
            }

            int iSize = polygons[0].size();
            for (int j = 0; j < iSize; j++)
            {
                polygons[0][j] = pLine->mapToScene(polygons[0][j]);
                polygons[0][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                polygons[0][j] = pLine->mapFromScene(polygons[0][j]);
                path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
            }
            pLine->setPath(path);
            pLine->refreshEndArrow();
        }

        break;
    case SAM_DRAW_OBJECT_POLYGON:
        pPolygon = dynamic_cast<QPolygonItem *> (groupItem);
        if (pPolygon)
        {
            QPolygonF polygonPoints = pPolygon->polygon();
            for (int i = 0; i < polygonPoints.size(); i++)
            {
                polygonPoints[i] = pPolygon->mapToScene(polygonPoints[i]);
                polygonPoints[i] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygonPoints[i], qrcBndRect, dXFactor, dYFactor);
                polygonPoints[i] = pPolygon->mapFromScene(polygonPoints[i]);
            }
            pPolygon->setPolygon(polygonPoints);
        }
        break;
    case SAM_DRAW_OBJECT_FOLDLINE:
        pFoldLine = dynamic_cast<QFoldLineItem *> (groupItem);
        if (pFoldLine)
        {
            QPainterPath path = pFoldLine->path();
            QList<QPolygonF> polygons = path.toSubpathPolygons();
            if (polygons.size() <= 0)
            {
                break;
            }

            int iSize = polygons[0].size();
            for (int j = 0; j < iSize; j++)
            {
                polygons[0][j] = pFoldLine->mapToScene(polygons[0][j]);
                polygons[0][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                polygons[0][j] = pFoldLine->mapFromScene(polygons[0][j]);
                path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
            }
            pFoldLine->setPath(path);
            pFoldLine->refreshEndArrow();
        }
        break;
    case SAM_DRAW_OBJECT_FREELINE:
        pFreeLine = dynamic_cast<QFreeLineItem *> (groupItem);
        if (pFreeLine)
        {
            QPainterPath path = pFreeLine->path();
            QList<QPolygonF> polygons = path.toSubpathPolygons();
            if (polygons.size() <= 0)
            {
                break;
            }

            int iSize = polygons[0].size();
            for (int j = 0; j < iSize; j++)
            {
                polygons[0][j] = pFreeLine->mapToScene(polygons[0][j]);
                polygons[0][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                polygons[0][j] = pFreeLine->mapFromScene(polygons[0][j]);
                path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
            }
            pFreeLine->setPath(path);
            pFreeLine->refreshEndArrow();
        }
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE:
        pLineCircle = dynamic_cast<QLineCircleItem *> (groupItem);
        if (pLineCircle)
        {
            QPainterPath ipath = pLineCircle->path();
            polygonList = ipath.toSubpathPolygons();
            int iPolygonListSize = polygonList.size();
            if (pLineCircle->m_eLineEndArrowType != LINE_END_STYLE_NONE)
            {
                iPolygonListSize--;
            }
            for (int i = 0; i < iPolygonListSize; i++)
            {
                for (int j = 0; j < polygonList[i].size(); j++)
                {
                    polygonList[i][j] = pLineCircle->mapToScene(polygonList[i][j]);
                    polygonList[i][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygonList[i][j], qrcBndRect, dXFactor, dYFactor);
                    polygonList[i][j] = pLineCircle->mapFromScene(polygonList[i][j]);
                }
            }

            QPainterPath allPath;
            for(int i = 0; i < iPolygonListSize; i++)
            {
                QPainterPath subPath = QPainterPath();
                subPath.addPolygon(polygonList.at(i));
                allPath.addPath(subPath);
            }
            pLineCircle->setPath(allPath);
            pLineCircle->refreshEndArrow();
        }
        break;
    case SAM_DRAW_OBJECT_TEXT:
        pText = dynamic_cast<QSimpleTextItem *> (groupItem);
        if (pText)
        {
            qrcSetRect = qrcBndRect;
            pText->SetHeight(qrcSetRect.height() * dYFactor);
        }
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
        pRoundedRect = dynamic_cast<QRoundedRect *> (groupItem);
        if (pRoundedRect)
        {
            qrcSetRect = qrcBndRect;
            pRoundedRect->SetHeight(qrcSetRect.height() * dYFactor);
        }
        break;
    case SAM_DRAW_OBJECT_ARC:
        pArc = dynamic_cast<QArcItem *> (groupItem);
        if (pArc)
        {
            qrcSetRect = qrcBndRect;
            pArc->SetHeight(qrcSetRect.height() * dYFactor);
        }
        break;
 /**************wxy add start*/
    case SAM_DRAW_OBJECT_RECT_NEW:
        pRectNew = dynamic_cast<QRectBasicItem *> (groupItem);
        if (!pRectNew)
        {
            break;
        }
        qrcSetRect = qrcBndRect;
        qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
        qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
        qrcSetRect = pRectNew->mapRectFromScene(qrcSetRect);
        pRectNew->setRectA(qrcSetRect);
        break;
    case SAM_DRAW_OBJECT_ELIPSE_NEW:
        pElipseNew = dynamic_cast<QElipseBasicItem *> (groupItem);
        if (!pElipseNew)
        {
            break;
        }
        qrcSetRect = qrcBndRect;
        qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
        qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
        qrcSetRect = pElipseNew->mapRectFromScene(qrcSetRect);
        pElipseNew->setRect(qrcSetRect);
        break;
    case SAM_DRAW_OBJECT_LINE_NEW:
        pLineNew = dynamic_cast<QLineBasicItem *> (groupItem);
        if (pLineNew)
        {
            QPainterPath path = pLineNew->path();
            QList<QPolygonF> polygons = path.toSubpathPolygons();
            if (polygons.size() <= 0)
            {
                break;
            }

            int iSize = polygons[0].size();
            for (int j = 0; j < iSize; j++)
            {
                polygons[0][j] = pLineNew->mapToScene(polygons[0][j]);
                polygons[0][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                polygons[0][j] = pLineNew->mapFromScene(polygons[0][j]);
                path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
            }
            pLineNew->setPath(path);
            pLineNew->refreshEndArrow();
        }

        break;
    case SAM_DRAW_OBJECT_POLYGON_NEW:
        pPolygonNew = dynamic_cast<QPolygonBasicItem *> (groupItem);
        if (pPolygonNew)
        {
            QPolygonF polygonPoints = pPolygonNew->polygon();
            for (int i = 0; i < polygonPoints.size(); i++)
            {
                polygonPoints[i] = pPolygonNew->mapToScene(polygonPoints[i]);
                polygonPoints[i] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygonPoints[i], qrcBndRect, dXFactor, dYFactor);
                polygonPoints[i] = pPolygonNew->mapFromScene(polygonPoints[i]);
            }
            pPolygonNew->setPolygon(polygonPoints);
        }
        break;
    case SAM_DRAW_OBJECT_FOLDLINE_NEW:
        pFoldLineNew = dynamic_cast<QFoldLineBasicItem *> (groupItem);
        if (pFoldLineNew)
        {
            QPainterPath path = pFoldLineNew->path();
            QList<QPolygonF> polygons = path.toSubpathPolygons();
            if (polygons.size() <= 0)
            {
                break;
            }

            int iSize = polygons[0].size();
            for (int j = 0; j < iSize; j++)
            {
                polygons[0][j] = pFoldLineNew->mapToScene(polygons[0][j]);
                polygons[0][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                polygons[0][j] = pFoldLineNew->mapFromScene(polygons[0][j]);
                path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
            }
            pFoldLineNew->setPath(path);
            pFoldLineNew->refreshEndArrow();
        }
        break;
    case SAM_DRAW_OBJECT_FREELINE_NEW:
        pFreeLineNew = dynamic_cast<QFreeLineBasicItem *> (groupItem);
        if (pFreeLineNew)
        {
            QPainterPath path = pFreeLineNew->path();
            QList<QPolygonF> polygons = path.toSubpathPolygons();
            if (polygons.size() <= 0)
            {
                break;
            }

            int iSize = polygons[0].size();
            for (int j = 0; j < iSize; j++)
            {
                polygons[0][j] = pFreeLineNew->mapToScene(polygons[0][j]);
                polygons[0][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygons[0][j], qrcBndRect, dXFactor, dYFactor);
                polygons[0][j] = pFreeLineNew->mapFromScene(polygons[0][j]);
                path.setElementPositionAt(j, polygons[0][j].x(), polygons[0][j].y());
            }
            pFreeLineNew->setPath(path);
            pFreeLineNew->refreshEndArrow();
        }
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
        pLineCircleNew = dynamic_cast<QLineCircleBasicItem *> (groupItem);
        if (pLineCircleNew)
        {
            QPainterPath ipath = pLineCircleNew->path();
            polygonList = ipath.toSubpathPolygons();
            int iPolygonListSize = polygonList.size();
            if (pLineCircleNew->m_eLineEndArrowType != LINE_END_STYLE_NONE)
            {
                iPolygonListSize--;
            }
            for (int i = 0; i < iPolygonListSize; i++)
            {
                for (int j = 0; j < polygonList[i].size(); j++)
                {
                    polygonList[i][j] = pLineCircleNew->mapToScene(polygonList[i][j]);
                    polygonList[i][j] = m_selectTool.coordTranslateInGrp(SAM_DRAW_RECT_TOP_LEFT, polygonList[i][j], qrcBndRect, dXFactor, dYFactor);
                    polygonList[i][j] = pLineCircleNew->mapFromScene(polygonList[i][j]);
                }
            }

            QPainterPath allPath;
            for(int i = 0; i < iPolygonListSize; i++)
            {
                QPainterPath subPath = QPainterPath();
                subPath.addPolygon(polygonList.at(i));
                allPath.addPath(subPath);
            }
            pLineCircleNew->setPath(allPath);
            pLineCircleNew->refreshEndArrow();
        }
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
        pRoundedRectNew = dynamic_cast<QRoundedRectBasic *> (groupItem);
        if (pRoundedRectNew)
        {
            qrcSetRect = qrcBndRect;
            qrcSetRect.setWidth(qrcSetRect.width() * dXFactor);
            qrcSetRect.setHeight(qrcSetRect.height() * dYFactor);
            qrcSetRect = pRoundedRectNew->mapRectFromScene(qrcSetRect);
            pRoundedRectNew->setRectA(qrcSetRect);
            //qrcSetRect = qrcBndRect;
            //pRoundedRectNew->SetHeight(qrcSetRect.height() * dYFactor);
        }
        break;
    case SAM_DRAW_OBJECT_ARC_NEW:
        pArcNew = dynamic_cast<QArcBasicItem *> (groupItem);
        if (pArcNew)
        {
            qrcSetRect = qrcBndRect;
            pArcNew->SetHeight(qrcSetRect.height() * dYFactor);
        }
        break;
 /**************wxy add end*/
	default:break;
	}
}

void QGroupItem::SetName(QString sName) //�������ͼ�ε�����
{
    groupItem->setData(GROUP_NAME_KEY,QVariant(sName));
}

QString QGroupItem::GetName()//������ͼ�ε�����
{
    return groupItem->data(GROUP_NAME_KEY).toString();
}

void QGroupItem::SetId(int nID) //�������ͼ�ε�id��
{
    int ntype=type();
    groupItem->setData(ntype,QVariant(nID));
}

int QGroupItem::GetId() //������ͼ�ε�id
{
    int ntype=type();
    return groupItem->data(ntype).toInt();
}

void QGroupItem::SetDescription(QStringList sListStr) //�������洢ͼ�ε�����
{
    int ntype=type();
    groupItem->setData(ntype,QVariant(sListStr));
}

QStringList QGroupItem::GetDescription() //���ͼ�εĴ洢����
{
    int ntype=type();
    return groupItem->data(ntype).toStringList();
}

void QGroupItem::setItemPattern(int nPattern)
{
    QString sName = "";
    QList<QGraphicsItem *> item =groupItem->childItems();
    QGraphicsItem *pItem = NULL;
    int type = 0;
    QRectItem *RectItem;  //���λ���
    QElipseItem *pCIRCLE; //Բ�����λ���
    QSimpleTextItem *pTEXT;     //�ı�����
    QRoundedRect *pRoundedRect;  //Բ�Ǿ���

    QLineItem * pLine;     //ֱ��
    QPolygonItem *pPoly;   //�����
    QFoldLineItem *pFoldLine;

    QRectBasicItem *RectItemNew = NULL;
    QElipseBasicItem *pCIRCLENew = NULL;
    QRoundedRectBasic *pRoundedRectNew = NULL;
    QLineBasicItem * pLineNew = NULL;
    QPolygonBasicItem *pPolyNew = NULL;
    QFoldLineBasicItem *pFoldLineNew = NULL;

    foreach(QGraphicsItem *Item,item)
    {
        sName = Item->data(GROUP_NAME_KEY).toString();
        if(sName == "mUnit")
        {
            pItem = Item;
            break;
        }
    }
    if(pItem)
    {
        foreach(QGraphicsItem *newItem,pItem->childItems())
        {
            type = newItem->type();
            if(type == SAM_DRAW_OBJECT_RECT) //�ǻ�������
            {
                RectItem=qgraphicsitem_cast<QRectItem*> (newItem);
                RectItem->SetPattern(nPattern);
            }
            else if(type == SAM_DRAW_OBJECT_ELIPSE) //�ǻ���Բ������
            {
                pCIRCLE=qgraphicsitem_cast<QElipseItem*> (newItem);
                pCIRCLE->SetPattern(nPattern);
            }
            else if(type == SAM_DRAW_OBJECT_TEXT) //�ǻ����ı�
            {
                pTEXT=qgraphicsitem_cast<QSimpleTextItem *> (newItem);
                pTEXT->SetPattern(nPattern);
            }
            else if(type == SAM_DRAW_OBJECT_LINE) //ֱ��
            {
                pLine=qgraphicsitem_cast<QLineItem *> (newItem);
                pLine->setLineType(nPattern);
            }
            else if(type == SAM_DRAW_OBJECT_FOLDLINE) //����
            {
                pFoldLine=qgraphicsitem_cast<QFoldLineItem *> (newItem);
                pFoldLine->setLineType(nPattern);
            }
            else if(type == SAM_DRAW_OBJECT_POLYGON) //�����
            {
                pPoly=qgraphicsitem_cast<QPolygonItem *> (newItem);
                pPoly->setPattern(nPattern);
            }
            else if(type == SAM_DRAW_OBJECT_ROUNDEDRECT) //Բ�Ǿ���
            {
                pRoundedRect=qgraphicsitem_cast<QRoundedRect *> (newItem);
                pRoundedRect->SetPattern(nPattern);
            }
 /********************wxy add start*/
            if(type == SAM_DRAW_OBJECT_RECT_NEW) //�ǻ�������
            {
                RectItemNew=qgraphicsitem_cast<QRectBasicItem*> (newItem);
                RectItemNew->SetPattern(nPattern);
            }
            else if(type == SAM_DRAW_OBJECT_ELIPSE_NEW) //�ǻ���Բ������
            {
                pCIRCLENew=qgraphicsitem_cast<QElipseBasicItem*> (newItem);
                pCIRCLENew->SetPattern(nPattern);
            }
            else if(type == SAM_DRAW_OBJECT_LINE_NEW) //ֱ��
            {
                pLineNew=qgraphicsitem_cast<QLineBasicItem *> (newItem);
                pLineNew->setLineType(nPattern);
            }
            else if(type == SAM_DRAW_OBJECT_FOLDLINE_NEW) //����
            {
                pFoldLineNew=qgraphicsitem_cast<QFoldLineBasicItem *> (newItem);
                pFoldLineNew->setLineType(nPattern);
            }
            else if(type == SAM_DRAW_OBJECT_POLYGON_NEW) //�����
            {
                pPolyNew=qgraphicsitem_cast<QPolygonBasicItem *> (newItem);
                pPolyNew->setPattern(nPattern);
            }
            else if(type == SAM_DRAW_OBJECT_ROUNDEDRECT_NEW) //Բ�Ǿ���
            {
                pRoundedRectNew=qgraphicsitem_cast<QRoundedRectBasic *> (newItem);
                pRoundedRectNew->SetPattern(nPattern);
            }
 /********************wxy add end*/
        }
    }
}

/*************************************************************
������ҳ�浽����
nAppr ����ǰѡ�е�����
pImage: ѡ�е�ͼƬָ��
pScene������ָ��
sTxt���ı�
SName����ҳ�������
*************************************************************/
QItemGroup*  DrawItemToScene::DrawItem(
        int nAppr,QPixmap *pImage,QString sTxt,QString sName)
{
    //QGraphicsItem * item = 0;
    QItemGroup *Group1 = new QItemGroup();
    switch(nAppr)
    {
    case 1:
        break;
    default:
        QList<QGraphicsItem *> list1;
        //QRectItem *item1=new QRectItem(80,82);
        QRectF rect(QPointF(0,0), QSize(80,82));
        QRectItem *item1=new QRectItem(rect);
        Group1->addToGroup(item1);
        item1->SetName("rc1");
        item1->SetBackColor(QColor(0,255,0));
        item1->setFlag(QGraphicsItem::ItemIsSelectable, false);
        QRectF rect2(QPointF(0,0), QSize(78,80));
        QRectItem *item2=new QRectItem(rect2);
        Group1->addToGroup(item2);
        item2->SetBackColor(QColor(0,255,0));
        item2->SetName("rc2");
        QRectF itemRect;
        QRectF textRect;
        itemRect = item2->boundingRect();
        if(pImage )
        {
            QPixmap newimage;
            QSize size = QSize(itemRect.width(),itemRect.height());
            newimage = pImage->scaled(size);
            QPixmapItem *pixmapItem = new QPixmapItem(*pImage,size);
            Group1->addToGroup(pixmapItem);
            pixmapItem->setPos(item2->x(),item2->y());
            pixmapItem->setData(GROUP_NAME_KEY,QVariant("image"));
            pixmapItem->setSelected(false);
            pixmapItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
        }
        QSimpleTextItem *item3=new QSimpleTextItem(item2->boundingRect(),"txt");
        Group1->addToGroup(item3);
        item3->SetName("txt");
        item3->SetText(sTxt);

        textRect = item3->boundingRect();
        //QPoint pt;
        item3->setX(item2->x()+(itemRect.width()-textRect.width())*0.5);
        item3->setY(item2->y()+(itemRect.height()-textRect.height())*0.5);
        item1->setSelected(false);
        item2->setSelected(false);
        item3->setSelected(false);
        //Group1 = pScene->createItemGroup(list1);
        Group1->setData(GROUP_NAME_KEY,QVariant(sName));
        //Group1->setAcceptDrops(true);
        break;
    }
    return Group1;
}

QGraphicsItem*  DrawItemToScene::DrawSamItem(
        int appr,QPixmap* image,SamDrawScene *pScene,int status)
{
    QGraphicsItem * item;
    return item;
}

/*======================================================
����һ��item��һ���µ�item
���� pNewItem���µ�itemָ��
���� pOldItem�������Ƶ�itemָ��
edit by zx
========================================================*/
void DrawItemToScene::CopyItem(QGraphicsItem ** pNewItem,
                               QGraphicsItem *pOldItem)
{
    QRectBasicItem *pItem1New;
    QElipseBasicItem *pItem2New;
    QLineBasicItem *pItem3New = NULL;
    QSimpleTextItem *pItem4;
    QPixmapItem * pItem5;
    QPolygonBasicItem *pPolygonNew;
    QFoldLineBasicItem *pFoldLineNew;
    QRoundedRectBasic *pRoundedRectNew;
    QArcBasicItem *ArcItemNew;
    QFreeLineBasicItem *pFreeLineNew;
    QLineCircleBasicItem *pLineCircleNew;


    QRectItem *pItem1;
    QElipseItem *pItem2;
    QLineItem *pItem3 = NULL;
    QPolygonItem *pPolygon;
    QFoldLineItem *pFoldLine;
    QRoundedRect *pRoundedRect;
    QArcItem *ArcItem;
    QFreeLineItem *pFreeLine;
    QLineCircleItem *pLineCircle;

    QItemGroup *itemGroup;

    switch(pOldItem->type())
    {
    case SAM_DRAW_OBJECT_RECT_NEW://�Ǿ���
        pItem1New = dynamic_cast<QRectBasicItem *>(pOldItem);
        *pNewItem = Clone(pItem1New);
        break;
    case SAM_DRAW_OBJECT_ELIPSE_NEW://��Բ
        pItem2New = dynamic_cast<QElipseBasicItem *>(pOldItem);
        *pNewItem = Clone(pItem2New);
        break;
    case SAM_DRAW_OBJECT_LINE_NEW://��ֱ��
        pItem3New = dynamic_cast<QLineBasicItem *>(pOldItem);
        *pNewItem = Clone(pItem3New);
        break;
    case SAM_DRAW_OBJECT_TEXT://�ı�
        pItem4 = dynamic_cast<QSimpleTextItem *>(pOldItem);
        *pNewItem = Clone(pItem4);
        break;
    case SAM_DRAW_OBJECT_PIXMAP://ͼƬ
        pItem5 = dynamic_cast<QPixmapItem *>(pOldItem);
        *pNewItem = Clone(pItem5);
        break;
    case SAM_DRAW_OBJECT_FOLDLINE_NEW://����
        pFoldLineNew = dynamic_cast<QFoldLineBasicItem *>(pOldItem);
        *pNewItem = Clone(pFoldLineNew);
        break;
    case SAM_DRAW_OBJECT_POLYGON_NEW://�����
        pPolygonNew = dynamic_cast<QPolygonBasicItem *>(pOldItem);
        *pNewItem = Clone(pPolygonNew);
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW: //Բ�Ǿ��� ArcItem
        pRoundedRectNew = dynamic_cast<QRoundedRectBasic *>(pOldItem);
        *pNewItem = Clone(pRoundedRectNew);
        break;
    case SAM_DRAW_OBJECT_ARC_NEW: //����
        ArcItemNew = dynamic_cast<QArcBasicItem *>(pOldItem);
        *pNewItem = Clone(ArcItemNew);
        break;
    case SAM_DRAW_OBJECT_FREELINE_NEW:// ����ֱ��
        pFreeLineNew = dynamic_cast<QFreeLineBasicItem *>(pOldItem);
        *pNewItem = Clone(pFreeLineNew);
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW://����
        pLineCircleNew = dynamic_cast<QLineCircleBasicItem *>(pOldItem);
        *pNewItem = Clone(pLineCircleNew);
        break;
    case SAM_DRAW_OBJECT_GROUP://���
        itemGroup = dynamic_cast<QItemGroup *>(pOldItem);
        *pNewItem = itemGroup->Clone();
        break;
/////////////////wxy add start
    case SAM_DRAW_OBJECT_RECT://�Ǿ���
        pItem1 = dynamic_cast<QRectItem *>(pOldItem);
        *pNewItem = Clone(pItem1);
        break;
    case SAM_DRAW_OBJECT_ELIPSE://��Բ
        pItem2 = dynamic_cast<QElipseItem *>(pOldItem);
        *pNewItem = Clone(pItem2);
        break;
    case SAM_DRAW_OBJECT_LINE://��ֱ��
        pItem3 = dynamic_cast<QLineItem *>(pOldItem);
        *pNewItem = Clone(pItem3);
        break;
    case SAM_DRAW_OBJECT_FOLDLINE://����
        pFoldLine = dynamic_cast<QFoldLineItem *>(pOldItem);
        *pNewItem = Clone(pFoldLine);
        break;
    case SAM_DRAW_OBJECT_POLYGON://�����
        pPolygon = dynamic_cast<QPolygonItem *>(pOldItem);
        *pNewItem = Clone(pPolygon);
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT: //Բ�Ǿ��� ArcItem
        pRoundedRect = dynamic_cast<QRoundedRect *>(pOldItem);
        *pNewItem = Clone(pRoundedRect);
        break;
    case SAM_DRAW_OBJECT_ARC: //����
        ArcItem = dynamic_cast<QArcItem *>(pOldItem);
        *pNewItem = Clone(ArcItem);
        break;
    case SAM_DRAW_OBJECT_FREELINE:// ����ֱ��
        pFreeLine = dynamic_cast<QFreeLineItem *>(pOldItem);
        *pNewItem = Clone(pFreeLine);
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE://����
        pLineCircle = dynamic_cast<QLineCircleItem *>(pOldItem);
        *pNewItem = Clone(pLineCircle);
        break;
/////////////////wxy add end
    default:
        *pNewItem = NULL;
        break;
    }
    if(*pNewItem)
    {
        (*pNewItem)->setFlag(QGraphicsItem::ItemIsSelectable,false);
        QVariant value = pOldItem->data(GROUP_DATALIST_KEY);
        (*pNewItem)->setData(GROUP_DATALIST_KEY,value);
        value = pOldItem->data(GROUP_TYPE_KEY);
        (*pNewItem)->setData(GROUP_TYPE_KEY,value);
        value = pOldItem->data(GROUP_NAME_KEY);
        (*pNewItem)->setData(GROUP_NAME_KEY,value);
    }

}
//��¡һ��QRectItem��QGraphicsItem
QGraphicsItem* DrawItemToScene::Clone(QRectItem *rectItem)
{
    return rectItem->Clone();
}
//��¡һ��QPixmapItem��QGraphicsItem
QGraphicsItem* DrawItemToScene::Clone(QPixmapItem *imageItem)
{
    return imageItem->Clone();
}
//��¡һ��QSimpleTextItem��QGraphicsItem
QGraphicsItem* DrawItemToScene::Clone(QSimpleTextItem *textItem)
{
    return textItem->Clone();
}
//��¡һ��QLineItem��QGraphicsItem
QGraphicsItem* DrawItemToScene::Clone(QLineItem *lineItem)
{
    return lineItem->Clone();
}
//��¡һ��QElipseItem��QGraphicsItem
QGraphicsItem* DrawItemToScene::Clone(QElipseItem *elipseItem)
{
    return elipseItem->Clone();
}
//��¡һ��QFoldLineItem��QGraphicsItem
QGraphicsItem* DrawItemToScene::Clone(QFoldLineItem *FoldLineItem)
{
    return FoldLineItem->Clone();
}
//��¡һ��QPolygonItem��QGraphicsItem
QGraphicsItem* DrawItemToScene::Clone(QPolygonItem *PolygonItem)
{
    return PolygonItem->Clone();
}

//��¡һ��QRoundedRect��QGraphicsItem
QGraphicsItem* DrawItemToScene::Clone(QRoundedRect *RoundedrectItem)
{
    return RoundedrectItem->Clone();
}

//��¡һ��QArcItem��QGraphicsItem
QGraphicsItem* DrawItemToScene::Clone(QArcItem *ArcItem)
{
    return ArcItem->Clone();
}
//��¡һ��QFreeLineItem��QGraphicsItem
QGraphicsItem* DrawItemToScene::Clone(QFreeLineItem *FreeLineItem)
{
    return FreeLineItem->Clone();
}
//��¡һ��QLineCircleItem��QGraphicsItem
QGraphicsItem* DrawItemToScene::Clone(QLineCircleItem *LineCircleItem)
{
    return LineCircleItem->Clone();
}

//wxy
QGraphicsItem* DrawItemToScene::Clone(QLineBasicItem *pItem)
{
    return pItem->Clone();
}

QGraphicsItem* DrawItemToScene::Clone(QRectBasicItem *pItem)
{
    return pItem->Clone();
}

QGraphicsItem* DrawItemToScene::Clone(QElipseBasicItem *pItem)
{
    return pItem->Clone();
}

QGraphicsItem* DrawItemToScene::Clone(QFoldLineBasicItem *pItem)
{
    return pItem->Clone();
}

QGraphicsItem* DrawItemToScene::Clone(QPolygonBasicItem *pItem)
{
    return pItem->Clone();
}

QGraphicsItem* DrawItemToScene::Clone(QRoundedRectBasic *pItem)
{
    return pItem->Clone();
}

QGraphicsItem* DrawItemToScene::Clone(QArcBasicItem *pItem)
{
    return pItem->Clone();
}

QGraphicsItem* DrawItemToScene::Clone(QFreeLineBasicItem *pItem)
{
    return pItem->Clone();
}

QGraphicsItem* DrawItemToScene::Clone(QLineCircleBasicItem *pItem)
{
    return pItem->Clone();
}

//����status״̬��ͼƬ
QItemGroup* DrawItemToScene::ReSetPic(QGraphicsItem *pItem,QPixmap* pictrue,int status,PicPosInfo posinfo)
{
    int nSize;
    QList<QGraphicsItem *> itemList=pItem->childItems();
    QItemGroup *newSahpe = new QItemGroup();
    QItemGroup *newGroup= new QItemGroup();
    QGroupItem *childitem ;
    nSize=itemList.size();
    if(nSize < 1)
    {
        newGroup = dynamic_cast<QItemGroup *>(pItem);
        return newGroup;
    }
    if (status == 0)
    {
        for(int i=0;i < nSize;i++)
        {
            childitem = new QGroupItem(itemList.at(i));
            if (childitem->GetName() == "Shape0")
            {
                newSahpe = ReSetPic(itemList.at(i),pictrue,posinfo);
                itemList.replace(i,newSahpe);
                break;
            }
        }
    }
    else if(status == 1)
    {
        for(int i=0;i < nSize;i++)
        {
            childitem = new QGroupItem(itemList.at(i));
            if (childitem->GetName() == "Shape1")
            {
                newSahpe = ReSetPic(itemList.at(i),pictrue,posinfo);
                itemList.replace(i,newSahpe);
                break;
            }
        }
    }
    else
    {
        newGroup = dynamic_cast<QItemGroup *>(pItem);
        return newGroup;
    }
    foreach(QGraphicsItem *item,itemList)
    {
        newGroup->addToGroup(item);
    }
    QVariant value;
    value = pItem->data(GROUP_NAME_KEY);
    newGroup->setData(GROUP_NAME_KEY,value);
    value = pItem->data(GROUP_TYPE_KEY);
    newGroup->setData(GROUP_TYPE_KEY,value);
    newGroup->setVisible(pItem->isVisible());
    return newGroup;
}
//����ͼƬ
QItemGroup* DrawItemToScene::ReSetPic(QGraphicsItem* pOldItem,QPixmap* pictrue,PicPosInfo posinfo)
{
    QItemGroup *newGroup = new QItemGroup();
    bool IsPictureExist = false;
    int i;
    QList<QGraphicsItem *> itemList = pOldItem->childItems();
    QGraphicsItem * pTmp;
    QRectF rect;
    for (i = 0;i<itemList.size();i++)
    {
        pTmp = itemList.at(i);
        if (pTmp->data(GROUP_NAME_KEY).toString() == "rc2")
        {
            rect = pTmp->sceneBoundingRect();
        }
    }
    if (pictrue)
    {
        rect = TransPicPos(posinfo,rect);
        QSize picSize =QSize(rect.width(),rect.height());
        QPixmapItem* newPicItem = new QPixmapItem(*pictrue,picSize);
        newPicItem->setPos(rect.x(),rect.y());
        for(i=0; i<itemList.size();i++)
        {
            if (itemList.at(i)->type() == SAM_DRAW_OBJECT_PIXMAP)
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
        for(i=0; i<itemList.size();i++)
        {
            if (itemList.at(i)->type() == SAM_DRAW_OBJECT_PIXMAP)
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
    newGroup->setVisible(pOldItem->isVisible());
    return newGroup;
}
//���ݶ��뷽ʽ����ͼƬλ��
QRectF DrawItemToScene::TransPicPos(PicPosInfo posinfo,QRectF rect)
{
    if( posinfo.btnIndex< 1 || posinfo.btnIndex > 9) //λ�ò���1-9��Χ֮���˳�
        return rect;
    if(posinfo.fixrect)  //ѡ����������С��ʱ�򲻴���
        return rect;

    QRectF rc;
    int nWidth = rect.width();
    int nPicWidth = nWidth/2;
    int nX = 0;
    int nY = 0;
    switch(posinfo.btnIndex)
    {
    case 1: //���϶���
        nX = posinfo.space;
        nY = posinfo.space;
        break;
    case 2: //�϶���
        nX = (nWidth-nPicWidth)/2;
        nY = posinfo.space;
        break;
    case 3: //���϶���
        nX = nWidth -nPicWidth-posinfo.space;
        nY = posinfo.space;
        break;
    case 4: //�����
        nX = posinfo.space;
        nY = (nWidth-nPicWidth)/2;
        break;
    case 5: //���ж���
        nX = (nWidth-nPicWidth)/2;
        nY = (nWidth-nPicWidth)/2;
        break;
    case 6: //�Ҷ���
        nX = nWidth -nPicWidth-posinfo.space;
        nY = (nWidth-nPicWidth)/2;
        break;
    case 7: //���½Ƕ���
        nX = posinfo.space;
        nY = nWidth -nPicWidth-posinfo.space;
        break;
    case 8: //�ײ�����
        nX = (nWidth-nPicWidth)/2;
        nY = nWidth -nPicWidth-posinfo.space;
        break;
    case 9: //���½Ƕ���
        nX = nWidth -nPicWidth-posinfo.space;
        nY = nWidth -nPicWidth-posinfo.space;
        break;
    }

    if(nX > (nWidth - nPicWidth) )
        nX = (nWidth - nPicWidth);
    if(nY > (nWidth - nPicWidth))
        nY = (nWidth - nPicWidth);
    rc = QRectF(nX+rect.x(),nY+rect.y(),rect.width()/2,rect.height()/2);
    return rc;
}


void DrawItemToScene::CopyItemForChart(QGraphicsItem ** pNewItem,
                               QGraphicsItem *pOldItem)
{
    QRectItem *pItem1;
    QElipseItem *pItem2;
    QLineItem *pItem3;
    QSimpleTextItem *pItem4;
    QPixmapItem * pItem5;
    QPolygonItem *pPolygon;
    QFoldLineItem *pFoldLine;
    QRoundedRect *pRoundedRect;
    QArcItem *ArcItem;
    QFreeLineItem *pFreeLine;
    QLineCircleItem *pLineCircle;
    QItemGroup *itemGroup;

    switch(pOldItem->type())
    {
    case SAM_DRAW_OBJECT_RECT://�Ǿ���
        pItem1 = dynamic_cast<QRectItem *>(pOldItem);
        *pNewItem = Clone(pItem1);
        break;
    case SAM_DRAW_OBJECT_ELIPSE://��Բ
        pItem2 = dynamic_cast<QElipseItem *>(pOldItem);
        *pNewItem = Clone(pItem2);
        break;
    case SAM_DRAW_OBJECT_LINE://��ֱ��
        pItem3 = dynamic_cast<QLineItem *>(pOldItem);
        *pNewItem = Clone(pItem3);
        break;
    case SAM_DRAW_OBJECT_TEXT://�ı�
        pItem4 = dynamic_cast<QSimpleTextItem *>(pOldItem);
        *pNewItem = Clone(pItem4);
        break;
    case SAM_DRAW_OBJECT_PIXMAP://ͼƬ
        pItem5 = dynamic_cast<QPixmapItem *>(pOldItem);
        *pNewItem = Clone(pItem5);
        break;
    case SAM_DRAW_OBJECT_FOLDLINE://����
        pFoldLine = dynamic_cast<QFoldLineItem *>(pOldItem);
        *pNewItem = Clone(pFoldLine);
        break;
    case SAM_DRAW_OBJECT_POLYGON://�����
        pPolygon = dynamic_cast<QPolygonItem *>(pOldItem);
        *pNewItem = Clone(pPolygon);
        break;

    case SAM_DRAW_OBJECT_ROUNDEDRECT: //Բ�Ǿ��� ArcItem
        pRoundedRect = dynamic_cast<QRoundedRect *>(pOldItem);
        *pNewItem = Clone(pRoundedRect);
        break;
    case SAM_DRAW_OBJECT_ARC: //����
        ArcItem = dynamic_cast<QArcItem *>(pOldItem);
        *pNewItem = Clone(ArcItem);
        break;
    case SAM_DRAW_OBJECT_FREELINE:// ����ֱ��
        pFreeLine = dynamic_cast<QFreeLineItem *>(pOldItem);
        *pNewItem = Clone(pFreeLine);
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE://����
        pLineCircle = dynamic_cast<QLineCircleItem *>(pOldItem);
        *pNewItem = Clone(pLineCircle);
        break;
    case SAM_DRAW_OBJECT_GROUP ://���
        itemGroup = dynamic_cast<QItemGroup *>(pOldItem);
        *pNewItem = itemGroup->Clone();
        break;
    default:
        *pNewItem = NULL;
        break;
    }
    if(*pNewItem)
    {
        (*pNewItem)->setFlag(QGraphicsItem::ItemIsSelectable,false);
        QVariant value = pOldItem->data(GROUP_DATALIST_KEY);
        (*pNewItem)->setData(GROUP_DATALIST_KEY,value);
        value = pOldItem->data(GROUP_TYPE_KEY);
        (*pNewItem)->setData(GROUP_TYPE_KEY,value);
        value = pOldItem->data(GROUP_NAME_KEY);
        (*pNewItem)->setData(GROUP_NAME_KEY,value);
    }
}

