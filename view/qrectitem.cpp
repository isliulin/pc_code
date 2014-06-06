#include "view/qrectitem.h"
#include "QPainter"
#include <QVariant>
#include <QLinearGradient>
#include "headfile/global_types.h"
#include "Frame/mainwindow.h"
extern  MainWindow *pwnd;

QRectItem::QRectItem()
    :GraphicsRectItemSamExt()
{
    setRect(QRectF(QPointF(0,0),QSize(100,100)));
    nBackColor = QColor(255,255,255);    //��ʼ��������ɫ
    nFrontColor = QColor(0,0,0);   //��ʼ��ǰ��ɫ
    nPatternType = 1;              //��ʽ���ʼ��Ϊ��ɫ
    nLineType = 1;
    this->SetLineType(nLineType);  //������ʽ����Ϊʵ��
    this->SetPattern(nPatternType);
    this->SetId(0);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QRectItem::QRectItem(const QRectF &rect, QGraphicsItem *parent)
    :GraphicsRectItemSamExt(rect, parent)
{
    nBackColor = QColor(255,255,255);    //��ʼ��������ɫ
    nFrontColor = QColor(0,0,0);   //��ʼ��ǰ��ɫ
    nPatternType = 1;              //��ʽ���ʼ��Ϊ��ɫ
    nLineType = 1;
    this->SetLineType(nLineType);  //������ʽ����Ϊʵ��
    this->SetPattern(nPatternType);
    this->SetId(0);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void QRectItem::SetName(QString qstr)//set the name
{
    setData(GROUP_NAME_KEY,QVariant(qstr));
}

QString QRectItem::GetName()//get the name of item
{
    return this->data(GROUP_NAME_KEY).toString();
}
void QRectItem::SetId(int nID) //set the item id
{
   // int ntype=type();
    QPen pen = this->pen();
    switch(nID)
    {
    case 0: //ֱ��
        pen.setJoinStyle(Qt::MiterJoin); break;
    case 1: //�ؽ�
        pen.setJoinStyle(Qt::BevelJoin); break;
    case 2: //Բ��
        pen.setJoinStyle(Qt::RoundJoin); break;
    default:pen.setJoinStyle(Qt::MiterJoin); break;
    }
    this->setPen(pen);
   // setData(ITEM_ID_KEY,QVariant(nID));
}
int QRectItem::GetID()//get the item id
{
    int nID=0;
    //nID=data(ITEM_ID_KEY).toInt();
    QPen pen = this->pen();
    Qt::PenJoinStyle style ;
    style = pen.joinStyle();
    if(style == Qt::MiterJoin)
        nID = 0;
    else if(style == Qt::BevelJoin)
        nID = 1;
    else if(style == Qt::RoundJoin)
        nID = 2;
    return nID;
}
void QRectItem::SetPattern(int nPATTERN) //set the line pattern
{
    nPatternType = nPATTERN; //��ʽ����
    QRectF nrect=rect();
    QLinearGradient gradient(nrect.topLeft(),nrect.bottomRight());
    QRadialGradient Radial(nrect.center(),nrect.width()/2,nrect.center());
    // Conical.setSpread(QGradient::ReflectSpread);
    gradient.setSpread(QGradient::PadSpread);//	RepeatSpread

    QBrush br=brush();
    br.setColor(nFrontColor); //����ǰ��ɫ����ʽ��ɫ

    switch(nPATTERN)
    {

//    case 2:br.setStyle(Qt::Dense1Pattern);break;
//    case 3:br.setStyle(Qt::Dense2Pattern);break;
//    case 4:br.setStyle(Qt::Dense3Pattern);break;
//    case 5:br.setStyle(Qt::Dense4Pattern);break;
//    case 6:br.setStyle(Qt::Dense5Pattern);break;
//    case 7:br.setStyle(Qt::Dense6Pattern);break;
//    case 8:br.setStyle(Qt::Dense7Pattern);break;

//    case 9:br.setStyle(Qt::HorPattern);break;//setBrush(Qt::HorPattern);break;
//    case 10:br.setStyle(Qt::VerPattern);break;
//    case 11:br.setStyle(Qt::CrossPattern);break;

//    case 12:br.setStyle(Qt::BDiagPattern);break;
//    case 13:br.setStyle(Qt::FDiagPattern);break;
//    case 14:br.setStyle(Qt::DiagCrossPattern);break;
    case 0:br.setStyle(Qt::NoBrush);break;//͸��
    case 1:br.setColor(nBackColor);br.setStyle(Qt::SolidPattern);break;//��ɫ
    case 2: //�������
        gradient.setStart(nrect.x(),nrect.y()+nrect.height());
        gradient.setColorAt(0,nFrontColor );
        gradient.setColorAt(1,nBackColor );
        break;
    case 3: //����Գƹ���
        gradient.setStart(nrect.x(),nrect.y()+nrect.height());
        gradient.setColorAt(0,nFrontColor );
        gradient.setColorAt(0.5,nBackColor );
        gradient.setColorAt(1,nFrontColor );
        break;
    case 4: //�������
        gradient.setStart(nrect.x()+nrect.width(),nrect.y());
        gradient.setColorAt(0,nFrontColor  );
        gradient.setColorAt(1,nBackColor);
        break;
    case 5: //����Գƹ���
        gradient.setStart(nrect.x()+nrect.width(),nrect.y());
        gradient.setColorAt(0,nFrontColor  );
        gradient.setColorAt(0.5,nBackColor);
        gradient.setColorAt(1,nFrontColor );
        break;
    case 6: //б�Ϲ���
        gradient.setColorAt(0,nFrontColor );
        gradient.setColorAt(1,nBackColor );
        break;
    case 7: //б�϶Գƹ���
        gradient.setColorAt(0,nFrontColor );
        gradient.setColorAt(0.5,nBackColor );
        gradient.setColorAt(1,nFrontColor );
        break;
    case 8: //б�¹���
        gradient.setStart(nrect.x(),nrect.y()+nrect.height());
        gradient.setFinalStop(nrect.x()+nrect.width(),nrect.y());
        gradient.setColorAt(0,nBackColor );
        gradient.setColorAt(1,nFrontColor);
        break;
    case 9: //б�¶Գƹ���
        gradient.setStart(nrect.x(),nrect.y()+nrect.height());
        gradient.setFinalStop(nrect.x()+nrect.width(),nrect.y());
        gradient.setColorAt(0,nFrontColor );
        gradient.setColorAt(0.5,nBackColor );
        gradient.setColorAt(1,nFrontColor );
        break;
    case 10: //���ϽǷ���
        gradient.setStart(nrect.x()+nrect.width(),nrect.y());
        gradient.setFinalStop(nrect.x(),nrect.y()+nrect.height());
        gradient.setColorAt(0,nBackColor );
        gradient.setColorAt(1,nFrontColor );
        break;
    case 11: //���ϽǷ���
        gradient.setColorAt(0,nBackColor );
        gradient.setColorAt(1, nFrontColor);
        break;
    case 12: //���ķ���
        Radial.setColorAt(0,nBackColor );
        Radial.setColorAt(1,nFrontColor );
        setBrush(Radial);
        return;
        break;
    case 13: //������
        Radial.setFocalPoint(nrect.x(),nrect.y()+nrect.height()/2);
        Radial.setColorAt(0,nBackColor );
        Radial.setColorAt(1,nFrontColor );
        setBrush(Radial);
        return;
        break;

    default:
        break;
    }

    if(nPATTERN >= 2 )
    {
        setBrush(gradient);
    }
    else
    {
        setBrush(br);
    }
}

int QRectItem::GetPattern() //�����ʽ
{
    return nPatternType;
}

void QRectItem::SetLineType(int nTYPE) //set the line style
{
    nLineType = nTYPE;
    QPen pen = this->pen();
    switch(nLineType)
    {
    case 0:
        pen.setStyle(Qt::NoPen); break;//color.setAlpha(0); break; //���ø���ɫ��͸����,��������͸��
    case 1:
        pen.setStyle(Qt::SolidLine); break;//ʵ��
    case 2:
        pen.setStyle(Qt::DashLine); break; //s Qt::NoPen
    case 3:
        pen.setStyle(Qt::DotLine);break;
    case 4:
        pen.setStyle(Qt::DashDotLine);break;
    case 5:
        pen.setStyle(Qt::DashDotDotLine);break;
    case 6:
        pen.setStyle(Qt::CustomDashLine);break;
    default:
        break;
    }
    this->setPen(pen);
}

int QRectItem::GetLineType() //���������ʽ
{
    return nLineType;
}

void QRectItem::SetLineWidth(int nWidth) //set the line width
{
	int width = nWidth;
	if (nWidth == 1)
	{
		width = 0;
	}
    QPen pen = this->pen();
    pen.setWidth(width);
    setPen(pen);

}

int QRectItem::GetLineWidth() //��������Ŀ��
{
	int width = pen().width();
	if (width == 0)
	{
		width = 1;
	}
    return width;
}

void QRectItem::SetHeight(qreal nHeight) //set the rect height
{
    QRectF rect = this->rect();
    rect.setHeight(nHeight);
    setRect(rect); //
    SetPattern(nPatternType);
}

qreal QRectItem::GetHeight()//��þ��εĸ߶�
{
    return rect().height();
}

void QRectItem::SetWidth(qreal nWIDTH)//set the rect width
{
    QRectF rect = this->rect();
    rect.setWidth(nWIDTH);
    setRect(rect);
    SetPattern(nPatternType);
}

qreal QRectItem::GetWidth()//��þ��εĿ��
{
    return rect().width();
}

void QRectItem::SetLeft(qreal nLeft) //set the rect left
{
    QRectF rect = this->rect();
    rect.setLeft(nLeft);
    setRect(rect);
}

qreal QRectItem::GetLeft()//��þ��ε�������
{
    return rect().left();
}

void QRectItem::SetTop(qreal nTop) //set the rect top
{
    QRectF rect = this->rect();
    rect.setTop(nTop);
    setRect(rect);
}

qreal QRectItem::GetTop() //��þ��ε�������
{
    return rect().top();
}

void QRectItem::SetLineColor(QColor nColor) //set the rect outline color
{
    QPen pen = this->pen();
    pen.setColor(nColor);
    setPen(pen);
}

QColor QRectItem::GetLineColor()//���������ɫ
{
    return pen().color();
}

void QRectItem::SetAlpha(int nAlpha) //����͸���� nAlpha 0-255��ֵԽС��Խ͸��
{
    nFrontColor.setAlpha(nAlpha);
    nBackColor.setAlpha(nAlpha);
    this->SetPattern(nPatternType);

    QPen pen = this->pen();
    QColor penColor = pen.color();
    penColor.setAlpha(nAlpha);
    pen.setColor(penColor);
    this->setPen(pen);
}

int QRectItem::GetAlpha() //��ñ���ɫ��͸����
{
    return nFrontColor.alpha();
}

void QRectItem::SetAngle(qreal nAngle)//������ת�Ƕȣ���ͼ�ε����ĵ�Ϊ��ת����
{
    qreal nMiddleX=rect().center().x(); //��þ������ĵ��x����ֵ
    qreal nMiddley=rect().center().y();//��þ������ĵ��y����ֵ

    //������ϵ�ƶ���(nMiddleX,nMiddley)λ�ú���ת�Ƕ�nAngle֮����������ָ���ԭ����λ��
    setTransform(QTransform().translate(nMiddleX, nMiddley).rotate(nAngle).translate(-nMiddleX, -nMiddley));
}

qreal QRectItem::GetAngle() //��ø�ͼ�ε���ת�Ƕ�
{
    return rotation();
}

void QRectItem::SetBackColor(QColor nColor) //���ñ���ɫ
{
    nBackColor = nColor;
    SetPattern(nPatternType);
}

QColor QRectItem::GetBackColor()//��ñ���ɫ
{
    return nBackColor;
}

void QRectItem::SetFrontColor(QColor nColor)
{
    nFrontColor = nColor;
    SetPattern(nPatternType);
}

QColor QRectItem::GetFrontColor()
{
    return nFrontColor;
}

void QRectItem::SetDescription(QStringList sListStr) //�������洢ͼ�ε�����
{
    //int ntype=type();
    setData(GROUP_DATALIST_KEY,QVariant(sListStr));
}

QStringList QRectItem::GetDescription() //���ͼ�εĴ洢����
{
   // int ntype=type();
    return data(GROUP_DATALIST_KEY).toStringList();
}

void QRectItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    count++;
    //QBasicGraphicsItem::compile(db, nSceneId, count, index);
    QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO polygon(nItemId ,nSceneId,ePolygonClass,eLineType ,nLineWidth,nLineColor,"
                     "eStyle,nBackColor,nForeColor,nAlpha,nPointX,nPointY,nWidth,nHeight,nRadius,eCornerType,"
                     "nZvalue,nCollidindId)"
                "VALUES (:nItemId,:nSceneId,:ePolygonClass ,:eLineType ,:nLineWidth,:nLineColor,:eStyle,"
                ":nBackColor,:nForeColor,:nAlpha,:nPointX,:nPointY,:nWidth,:nHeight,:nRadius,:eCornerType,"
                ":nZvalue,:nCollidindId)");
    sqlquery.bindValue(":nItemId",QVariant(count));// �� id
    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));// ���ڳ��� id
    sqlquery.bindValue(":ePolygonClass",QVariant(3)); //3 ��������Ϊ����
    sqlquery.bindValue(":eLineType",QVariant(nLineType+1));// ����
    sqlquery.bindValue(":nLineWidth",QVariant(GetLineWidth()));// �߿�
    sqlquery.bindValue(":nLineColor",QVariant(ColorToInt(GetLineColor()))); //��ɫ
    sqlquery.bindValue(":eStyle",QVariant(GetPattern()+1));// ��ʽ
    sqlquery.bindValue(":nBackColor",QVariant(ColorToInt(GetBackColor()))); //����ɫ
    sqlquery.bindValue(":nForeColor",QVariant(ColorToInt(GetFrontColor()))); //ǰ��ɫ
    sqlquery.bindValue(":nAlpha",QVariant(GetAlpha()));// ͸����

    QRect rect = this->sceneBoundingRect().toRect();
    sqlquery.bindValue(":nStartX",QVariant(rect.x()));//x
    sqlquery.bindValue(":nStartY",QVariant(rect.y()));//y
    sqlquery.bindValue(":nWidth",QVariant(rect.width()));//w
    sqlquery.bindValue(":nHeight",QVariant(rect.height()));//h

    sqlquery.bindValue(":eCornerType",QVariant(GetID()+1)); //ת������

    sqlquery.bindValue(":nZvalue",QVariant(zValue()));//���

    sqlquery.bindValue(":nCollidindId",QVariant(index));//��ײID

    bool result = false;
    result = sqlquery.exec();
    qDebug() << "insert rect table :"<<result;

    SamDrawScene *pScene = dynamic_cast<SamDrawScene *>(scene());
    if(pScene && pScene->nIsSceneOrWindow == 2)
    {
        //���Զ�����̵�item
        //���½����̡���item������ item�����������д���

        //QSqlQuery sqlquery(db);

        sqlquery.prepare("INSERT INTO kbAndItem(nKeyBoardId , nItemId ,nId,nItemTableType ) "
                         "VALUES (:nKeyBoardId ,:nItemId ,:nId,:nItemTableType)");
        sqlquery.bindValue(":nKeyBoardId",QVariant(nSceneId));
        sqlquery.bindValue(":nItemId",QVariant(count));
        sqlquery.bindValue(":nId",QVariant(id()));
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_RECT));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert kbAndItem table :"<<result;

    }
    if(pScene && pScene->nIsSceneOrWindow != 2)
    {
        //���ڻ��߳���item
        //���½����̡���item������
        //item�����������д���

        //QSqlQuery sqlquery(db);

        sqlquery.prepare("INSERT INTO sceneAndItem(nSceneId,nItemId,nId,nItemTableType)"
                         "VALUES(:nSceneId,:nItemId,:nId,:nItemTableType)");
        sqlquery.bindValue(":nSceneId",QVariant(nSceneId));
        sqlquery.bindValue(":nItemId",QVariant(count));
        sqlquery.bindValue(":nId",QVariant(id()));
        //int t = this->GroupType();
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_RECT));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert sceneAndItem table :"<<result;
    }
}


//��¡һ�� RectItem
//QRectItem *QRectItem::Clone()
QGraphicsItem *QRectItem::Clone()
{
    QRectItem *pClone = new QRectItem();
    if (!pClone)
    {
        return NULL;
    }

    QRectF qrcRect = this->rect();
    pClone->setRect(this->mapRectToScene(qrcRect));
    pClone->SetBackColor(this->GetBackColor());
    pClone->SetFrontColor(this->GetFrontColor());
    pClone->SetPattern(this->GetPattern());
    pClone->SetLineType(this->GetLineType());
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->SetName(this->GetName());
    pClone->SetLineColor(this->GetLineColor());
    pClone->SetLineWidth(this->GetLineWidth());
    pClone->SetId(this->GetID());
    pClone->setId(id());

    //pClone->SaveSecurityPro(&(this->sPro));
    return pClone;
}

void QRectItem::setRectA(const QRectF &rect)
{
    QRectF rectA = rect;
    qreal dDelta = 0.0;

    QPen pen = this->pen();
    int iPenWidth = pen.width();
    if (iPenWidth > 0)
    {
        dDelta = (iPenWidth * 1.0) / 2;
        rectA.setTop(rectA.top() + dDelta);
        rectA.setLeft(rectA.left() + dDelta);
        rectA.setWidth(rectA.width() - dDelta);
        rectA.setHeight(rectA.height() - dDelta);
    }

    this->setRect(rectA);
    SetPattern(nPatternType);
}

QDataStream &operator<<(QDataStream &stream, QRectItem *pRectItem)
{
//    stream << pRectItem->rect() << pRectItem->pen();
    stream << pRectItem->rect().topLeft() << pRectItem->rect().bottomRight();
    stream << pRectItem->pen().color() << pRectItem->pen().width();
    stream << pRectItem->nBackColor << pRectItem->nFrontColor;
    stream << pRectItem->nPatternType << pRectItem->scenePos();
    stream << pRectItem->nLineType;
    stream << pRectItem->isVisible();
    stream << pRectItem->GetName() << pRectItem->GetID();
    stream << pRectItem->data(GROUP_TYPE_KEY).toInt();
    stream << pRectItem->data(GROUP_DATALIST_KEY).toStringList();
//    if(pwnd->getProVersion() >= 3257)
//    {
//        pRectItem->save(stream);
//    }
    stream << pRectItem->id();
    return stream ;
}

QDataStream &operator>>(QDataStream &stream, QRectItem *pRectItem)
{
    QString name;
    int id ;
    QColor penColor;
    int penWidth;
    QPen  pen;
    QPointF pos;
    QPointF ptopLeft,pbottomRight;
    int typeKey = 0;
    QStringList dataList;
    bool bVisible = true;
   // stream >> rect >> pen;
    stream >> ptopLeft >> pbottomRight >> penColor >> penWidth;
    stream >> pRectItem->nBackColor >> pRectItem->nFrontColor;
    stream >> pRectItem->nPatternType >> pos >> pRectItem->nLineType;
    stream >> bVisible >> name >> id >> typeKey >> dataList;
//    if(pwnd->getProVersion() >= 3257)
//    {
//        pRectItem->load(stream);
//    }
    int nId = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> nId;
    }
    QRectF rect = QRectF(ptopLeft,pbottomRight);
    pen.setColor(penColor);
    pen.setWidth(penWidth);

    pRectItem->setPen(pen);
    pRectItem->setRect(rect);
    pRectItem->SetPattern(pRectItem->nPatternType);
    pRectItem->setPos(pos);
    pRectItem->SetLineType(pRectItem->nLineType);
    pRectItem->SetName(name);
    pRectItem->setVisible(bVisible);
    pRectItem->SetId(id);
    pRectItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pRectItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pRectItem->setId(nId);
    return stream ;
}

void QRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                              QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->drawRect(this->rect());

    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);
}
