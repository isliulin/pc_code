#include "view/qelipseitem.h"
#include "Frame/mainwindow.h"
extern  MainWindow *pwnd;

QElipseItem::QElipseItem()
    :GraphicsEllipseItemSamExt()
{
    this->setRect(0,0,100,100);
    init();
}

QElipseItem::QElipseItem(QRectF &rect)
    :GraphicsEllipseItemSamExt(rect)
{
    init();
}

void QElipseItem::init()
{
    nBackColor = QColor(255,255,255);          //��ʼ��������ɫ
    nFrontColor = QColor(0,0,0);   //��ʼ��ǰ��ɫ
    nPatternType = 1;              //��ʽ���ʼ��Ϊ��ɫ
    this->SetPattern(nPatternType);
    nLineType = 1;                 //������ʽ����Ϊʵ��
    nPropor = 0;
    this->SetLineType(nLineType);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);

    //for test

}

void QElipseItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
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
    sqlquery.bindValue(":ePolygonClass",QVariant(1)); //1 ��������ΪԲ
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

    sqlquery.bindValue(":nZvalue",QVariant(zValue()));//���

    sqlquery.bindValue(":nCollidindId",QVariant(index));//��ײID

    bool result = false;
    result = sqlquery.exec();
    qDebug() << "insert Elipse table :"<<result;

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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_ELIPSE));

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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_ELIPSE));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert sceneAndItem table :"<<result;
    }
}


QElipseItem *QElipseItem::Clone()
{
	QElipseItem *pClone = NULL;
	int angle = this->GetSpanAngle();
	if (angle != 360)//����
	{
		
		QRectF qrcRect = this->rect();
                //qrcRect = this->mapRectToScene(qrcRect);
                QRectF rc = this->sceneBoundingRect();
                //QPointF ItemPos = this->mapFromScene(rc.topLeft());
                 //ItemPos = this->mapToParent(ItemPos);
		pClone = new QElipseItem(qrcRect);
		if (!pClone)
		{
			return NULL;
		}
		pClone->SetSpanAngle(this->GetSpanAngle());
                pClone->SetStartAngle(this->GetStartAngle());
                QRectF rect = pClone->boundingRect();
                pClone->setPos(rc.topLeft()-rect.topLeft());
	}
	else//Բ
	{
		QRectF rc = this->sceneBoundingRect();
		pClone = new QElipseItem(rc);
		if (!pClone)
		{
			return NULL;
		}
	}

        pClone->setPen(this->pen());
	pClone->SetBackColor(this->GetBackColor());
	pClone->SetFrontColor(this->GetFrontColor());
        pClone->SetPattern(this->GetPattern());
        pClone->SetName(this->GetName());

        pClone->SetLineType(this->GetLineType());
        pClone->setPropor(this->getPropor(),this->GetPattern());
       // pClone->SetLineWidth(this->GetLineWidth());
        //pClone->SetLineColor(this->GetLineColor());

    //pClone->SaveSecurityPro(&(this->sPro));
        pClone->setId(id());

    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
	
    return pClone;
}

void QElipseItem::SetName(QString qstr)//set the name
{
   // int ntype=type();
    setData(GROUP_NAME_KEY,QVariant(qstr));
}

QString QElipseItem::GetName()//get the name of item
{
   // int ntype=type();
    QString sName="";
    sName=data(GROUP_NAME_KEY).toString();
    return sName;
}
void QElipseItem::SetId(int nID) //set the item id
{
   // int ntype=type();
    setData(ITEM_ID_KEY,QVariant(nID));
}
int QElipseItem::GetID()//get the item id
{
    int nID=0;
   // int ntype=type();
    nID=data(ITEM_ID_KEY).toInt();
    return nID;
}
void QElipseItem::SetPattern(int nPATTERN) //set the line pattern
{
    nPatternType = nPATTERN;
    QRectF nrect=rect();
    QLinearGradient gradient(nrect.topLeft(),nrect.bottomRight());
    QRadialGradient radial(nrect.center(),nrect.width()/2,nrect.center());
    // Conical.setSpread(QGradient::ReflectSpread);
    gradient.setSpread(QGradient::PadSpread);//	RepeatSpread

    QBrush br=brush();
    br.setColor(nFrontColor); //����ǰ��ɫ����ʽ��ɫ

    switch(nPatternType)
    {
    case 0:br.setStyle(Qt::NoBrush);break;
    case 1:br.setColor(nBackColor); br.setStyle(Qt::SolidPattern);break;
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

    case 2: //�������
        gradient.setStart(nrect.bottomLeft());
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(1,nBackColor);
        this->setBrush(gradient);
        break;
    case 3: //����Գƹ���
        gradient.setStart(nrect.bottomLeft());
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(0.5,nBackColor);
        gradient.setColorAt(1,nFrontColor);
        this->setBrush(gradient);
        break;
    case 4: //�������
        gradient.setStart(nrect.topRight());
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(1,nBackColor);
        this->setBrush(gradient);
        break;
    case 5: //����Գƹ���
        gradient.setStart(nrect.topRight());
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(0.5,nBackColor);
        gradient.setColorAt(1,nFrontColor);
        this->setBrush(gradient);
        break;
    case 6: //б�Ϲ���
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(1,nBackColor);
        this->setBrush(gradient);
        break;
    case 7: //б�϶Գƹ���
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(0.5,nBackColor);
        gradient.setColorAt(1,nFrontColor);
        this->setBrush(gradient);
        break;
    case 8: //б�¹���
        gradient.setStart(nrect.bottomLeft());
        gradient.setFinalStop(nrect.topRight());
        gradient.setColorAt(0,nBackColor);
        gradient.setColorAt(1,nFrontColor);
        this->setBrush(gradient);
        break;
    case 9: //б�¶Գƹ���
        gradient.setStart(nrect.bottomLeft());
        gradient.setFinalStop(nrect.topRight());
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(0.5,nBackColor);
        gradient.setColorAt(1,nFrontColor);
        this->setBrush(gradient);
        break;
    case 10: //���ϽǷ���
        gradient.setStart(nrect.topRight());
        gradient.setFinalStop(nrect.bottomLeft());
        gradient.setColorAt(0,nBackColor);
        gradient.setColorAt(1,nFrontColor);
        this->setBrush(gradient);
        break;
    case 11: //���ϽǷ���
        gradient.setColorAt(0,nBackColor);
        gradient.setColorAt(1, nFrontColor);
        this->setBrush(gradient);
        break;
    case 12: //���ķ���
        radial.setColorAt(0,nBackColor);
        radial.setColorAt(1,nFrontColor);
        this->setBrush(radial);
        break;
    case 13: //������
        radial.setFocalPoint(nrect.x(),nrect.center().y());
        radial.setColorAt(0,nBackColor);
        radial.setColorAt(1,nFrontColor);
        this->setBrush(radial);
        break;
    case 27://kong
        radial.setFocalPoint(nrect.center().x(),nrect.center().y());
        radial.setColorAt(0,QColor(255,0,0,0));
        radial.setColorAt(nPropor,QColor(255,0,0,0));
        radial.setColorAt(nPropor + 0.01,nBackColor);
        radial.setColorAt(1,nBackColor);
        this->setBrush(radial);
        break;
    default:
        break;
    }
    if(0 == nPatternType || 1 == nPatternType)
    {
        setBrush(br);
    }
}

int QElipseItem::GetPattern() //�����ʽ
{
    return nPatternType;
}

void QElipseItem::SetLineType(int nTYPE) //set the line style
{
    nLineType = nTYPE;
    QPen pen = this->pen();
    switch(nLineType)
    {
    case 0:
        pen.setStyle(Qt::NoPen);
        break;
    case 1:
        pen.setStyle(Qt::SolidLine);
        break;
    case 2:
        pen.setStyle(Qt::DashLine);
        break;
    case 3:
        pen.setStyle(Qt::DotLine);
        break;
    case 4:
        pen.setStyle(Qt::DashDotLine);
        break;
    case 5:
        pen.setStyle(Qt::DashDotDotLine);
        break;
    case 6:
        pen.setStyle(Qt::CustomDashLine);
        break;
    default:
        break;
    }
    this->setPen(pen);
}

int QElipseItem::GetLineType() //���������ʽ����
{
    return nLineType;
}

void QElipseItem::SetLineWidth(int nWidth) //set the line width
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

int QElipseItem::GetLineWidth() //��������Ŀ��
{
	int width = pen().width();
	if (width == 0)
	{
		width = 1;
	}
	return width;
}

void QElipseItem::SetHeight(qreal nHeight) //set the rect height
{
    QRectF nrect=rect(); //get the current rect position
    nrect.setHeight(nHeight);
    setRect(nrect); //
    this->SetPattern(nPatternType);
}

qreal QElipseItem::GetHeight()//���Բ�ĸ߶�
{
    return this->rect().height();
}

void QElipseItem::SetWidth(qreal nWIDTH)//set the rect width
{
    QRectF nrect=rect(); //get the current rect position
    nrect.setWidth(nWIDTH);
    setRect(nrect);
    this->SetPattern(nPatternType);
}

qreal QElipseItem::GetWidth()//���Բ�Ŀ��
{
    return this->rect().width();
}

void QElipseItem::SetLeft(qreal nLeft) //set the rect left
{
    QRectF nrect=rect(); //get the current rect position
    nrect.setLeft(nLeft);
    setRect(nrect);
}

qreal QElipseItem::GetLeft()//���Բ��������
{
    return this->rect().x();
}

void QElipseItem::SetTop(qreal nTop) //set the rect top
{
    QRectF nrect=rect(); //get the current rect position
    nrect.setTop(nTop);
    setRect(nrect);
}

qreal QElipseItem::GetTop() //���Բ��������
{
    return this->rect().y();
}

void QElipseItem::SetLineColor(QColor nColor) //set the rect outline color
{
    QPen pen = this->pen();
    pen.setColor(nColor);
    setPen(pen);
}

QColor QElipseItem::GetLineColor()//���������ɫ
{
    return this->pen().color();
}

void QElipseItem::SetAlpha(int nAlpha) //����͸���� nAlpha 0-255��ֵԽС��Խ͸��
{
    nBackColor.setAlpha(nAlpha);
    nFrontColor.setAlpha(nAlpha);
    this->SetPattern(nPatternType);
    QPen pen = this->pen();
    QColor penColor = pen.color();
    penColor.setAlpha(nAlpha);
    pen.setColor(penColor);
    this->setPen(pen);
}

int QElipseItem::GetAlpha() //��ñ���ɫ��͸����
{
    return nFrontColor.alpha();
}

void QElipseItem::SetAngle(qreal nAngle)//������ת�Ƕȣ���ͼ�ε����ĵ�Ϊ��ת����
{
    QRectF nrect=rect(); //�����ѡͼ�ε�����λ�ü���͸�
    qreal nMiddleX=nrect.x()+nrect.width()/2; //���Բ���ĵ��x����ֵ
    qreal nMiddley=nrect.y()+nrect.height()/2;//���Բ���ĵ��y����ֵ

    //������ϵ�ƶ���(nMiddleX,nMiddley)λ�ú���ת�Ƕ�nAngle֮����������ָ���ԭ����λ��
    setTransform(QTransform().translate(nMiddleX, nMiddley).rotate(nAngle).translate(-nMiddleX, -nMiddley));
}

qreal QElipseItem::GetAngle() //��ø�ͼ�ε���ת�Ƕ�
{
    return rotation();
}

void QElipseItem::SetBackColor(QColor nColor) //���ñ���ɫ
{
    nBackColor=nColor;
    this->SetPattern(nPatternType);
}

QColor QElipseItem::GetBackColor()//��ñ���ɫ
{
    return nBackColor;
}

/*************************************************************************
  �������ƣ�SetSpanAngle(int nAngle)
  nAngle��һ����ȽǶȣ�����ϵ��x��������Ϊ0�ȣ�����ʱ�뷽��Ƕ��𽥱��
  �������ã�����һ����ȽǶȣ���ò�ͬ��״������
 *************************************************************************/
void QElipseItem::SetSpanAngle(int nAngle) //���ÿ�ȽǶȣ�Ҫ��16
{
   int nspanAngle = nAngle * 16;
   setSpanAngle(nspanAngle);
}

int QElipseItem::GetSpanAngle() //��ÿ�ȽǶ�ֵ
{
    int nspanAngle=spanAngle();
    return nspanAngle/16;
}

/*************************************************************************
  �������ƣ�SetStartAngle(int nAngle)
  nAngle��һ����ʼ�Ƕȣ�����ϵ��x��������Ϊ0�ȣ�����ʱ�뷽��Ƕ��𽥱��
  �������ã�����һ����ʼ�Ƕȣ���ò�ͬ��״������
 *************************************************************************/
void QElipseItem::SetStartAngle(int nAngle) //���ÿ�ʼ�ȽǶȣ�Ҫ��16
{
    int nstartAngle = nAngle * 16;
    setStartAngle(nstartAngle);
}

int QElipseItem::GetStartAngle()  //��ÿ�ʼ�ȽǶ�ֵ
{
    int nstartAngle=startAngle();
    return nstartAngle/16;
}

void QElipseItem::SetFrontColor(QColor nColor)
{
    nFrontColor = nColor;
    this->SetPattern(nPatternType);
}

QColor QElipseItem::GetFrontColor()
{
    return nFrontColor;
}

void QElipseItem::SetDescription(QStringList sListStr) //�������洢ͼ�ε�����
{
    //int ntype=type();
    setData(GROUP_DATALIST_KEY,QVariant(sListStr));
}

QStringList QElipseItem::GetDescription() //���ͼ�εĴ洢����
{
    //int ntype=type();
    return data(GROUP_DATALIST_KEY).toStringList();
}

void QElipseItem::setRectA(const QRectF &rect)
{
    QRectF rectA = rect;
//    qreal dDelta = 0.0;

//    if (this->GetSpanAngle() < 360)
//    {
//        rectA.setHeight(rectA.height() * 2);
//    }

//    QPen pen = this->pen();
//    int iPenWidth = pen.width();
//    if (iPenWidth > 0)
//    {
//        dDelta = (iPenWidth * 1.0) / 2;
//        rectA.setTop(rectA.top() + dDelta);
//        rectA.setLeft(rectA.left() + dDelta);
//        rectA.setWidth(rectA.width() - dDelta);
//        rectA.setHeight(rectA.height() - dDelta);
//    }

    this->setRect(rectA);

//    if (this->GetSpanAngle() < 360)
//    {
//        this->SetStartAngle(this->GetStartAngle());
//        this->SetSpanAngle(this->GetSpanAngle());
//    }

    SetPattern(nPatternType);
}

//add by tanghaiguo

QDataStream &operator<<(QDataStream &stream, QElipseItem *pElipseItem)
{
    stream << pElipseItem->pen().color();
    stream << pElipseItem->pen().width();
    stream << pElipseItem->rect().topLeft();
    stream << pElipseItem->rect().bottomRight();
    stream << pElipseItem->GetName(); //get item name, type:QString;
    stream << pElipseItem->GetID();   //get the item id,type:int
    stream << pElipseItem->GetPattern();  //get style,type:int
//    stream << pElipseItem->pen();         //get pen ,type:QPen
    stream << pElipseItem->GetLineType();
    stream << pElipseItem->GetAngle();    //get circle Rotation type:qreal
    stream << pElipseItem->nBackColor;    //get backcolor
    stream << pElipseItem->nFrontColor;   //get frontcolor
    stream << pElipseItem->GetSpanAngle(); //get Span Angle,need by 16,type:int
    stream << pElipseItem->GetStartAngle(); //get start angle, type:int
    stream << pElipseItem->GetDescription(); //get Graphic storage properties, type:QStringList
//    stream << pElipseItem->rect();           //get the circle Bounding rectangle,type:QRectF
    stream << pElipseItem->scenePos();
    stream << pElipseItem->isVisible();
    stream << pElipseItem->data(GROUP_TYPE_KEY).toInt();
    stream << pElipseItem->data(GROUP_DATALIST_KEY).toStringList();
    stream << pElipseItem->getPropor();

//    if(pwnd->getProVersion() >= 3257)
//    {
//        pElipseItem->save(stream);
//    }
    stream << pElipseItem->id();
    return stream;
}
QDataStream &operator>>(QDataStream &stream, QElipseItem *pElipseItem)
{
    QString name;
    int id,pattern;
    float nPropor;
    QPen pen;
    int lineType;
    qreal angle;
    QColor penColor;
    int penWidth;
    int spanAngle,startAngle;
    QStringList description;
    QPointF pos, topLeft, bottomRight;
    int typeKey = 0;
    QStringList dataList;
    dataList.clear();
    bool bVisible = true;

    stream >> penColor >> penWidth >> topLeft >> bottomRight;
    stream >> name >> id >> pattern >> lineType >> angle >> pElipseItem->nBackColor;
    stream >> pElipseItem->nFrontColor >> spanAngle >> startAngle >> description >> pos;
    stream >> bVisible >> typeKey >> dataList;
    stream >> nPropor;

//    if(pwnd->getProVersion() >= 3257)
//    {
//        pElipseItem->load(stream);
//    }

    int nId = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> nId;
    }
    pen.setColor(penColor);
    pen.setWidth(penWidth);
    pElipseItem->setRect(QRectF(topLeft, bottomRight));
    pElipseItem->SetName(name);
    pElipseItem->SetId(id);
    pElipseItem->SetPattern(pattern);
    pElipseItem->setPen(pen);
    pElipseItem->SetLineType(lineType);
    pElipseItem->SetAngle(angle);
    pElipseItem->SetSpanAngle(spanAngle);
    pElipseItem->SetStartAngle(startAngle);
    pElipseItem->SetDescription(description);
    pElipseItem->setPos(pos);
    pElipseItem->setVisible(bVisible);
    pElipseItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pElipseItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pElipseItem->setPropor(nPropor,pattern);
    pElipseItem->setId(nId);
    return stream;
}

void QElipseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                                 QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    if ((this->spanAngle() != 0) && (qAbs(this->spanAngle()) % (360 * 16) == 0))
        painter->drawEllipse(this->rect());
    else
        painter->drawPie(this->rect(), this->startAngle(), this->spanAngle());

    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);
}

float QElipseItem::getPropor()
{
   return nPropor;
}
void QElipseItem::setPropor(float nPro,int nPatternType)
{
    nPropor = nPro;
    SetPattern(nPatternType);
}
