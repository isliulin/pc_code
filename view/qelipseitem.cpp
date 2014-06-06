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
    nBackColor = QColor(255,255,255);          //初始化背景颜色
    nFrontColor = QColor(0,0,0);   //初始化前景色
    nPatternType = 1;              //样式类初始化为纯色
    this->SetPattern(nPatternType);
    nLineType = 1;                 //线条样式类型为实线
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
    sqlquery.bindValue(":nItemId",QVariant(count));// 表 id
    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));// 所在场景 id
    sqlquery.bindValue(":ePolygonClass",QVariant(1)); //1 代表类型为圆
    sqlquery.bindValue(":eLineType",QVariant(nLineType+1));// 线形
    sqlquery.bindValue(":nLineWidth",QVariant(GetLineWidth()));// 线宽
    sqlquery.bindValue(":nLineColor",QVariant(ColorToInt(GetLineColor()))); //颜色
    sqlquery.bindValue(":eStyle",QVariant(GetPattern()+1));// 样式
    sqlquery.bindValue(":nBackColor",QVariant(ColorToInt(GetBackColor()))); //背景色
    sqlquery.bindValue(":nForeColor",QVariant(ColorToInt(GetFrontColor()))); //前景色
    sqlquery.bindValue(":nAlpha",QVariant(GetAlpha()));// 透明度

    QRect rect = this->sceneBoundingRect().toRect();
    sqlquery.bindValue(":nStartX",QVariant(rect.x()));//x
    sqlquery.bindValue(":nStartY",QVariant(rect.y()));//y
    sqlquery.bindValue(":nWidth",QVariant(rect.width()));//w
    sqlquery.bindValue(":nHeight",QVariant(rect.height()));//h

    sqlquery.bindValue(":nZvalue",QVariant(zValue()));//层次

    sqlquery.bindValue(":nCollidindId",QVariant(index));//碰撞ID

    bool result = false;
    result = sqlquery.exec();
    qDebug() << "insert Elipse table :"<<result;

    SamDrawScene *pScene = dynamic_cast<SamDrawScene *>(scene());
    if(pScene && pScene->nIsSceneOrWindow == 2)
    {
        //是自定义键盘的item
        //先新建键盘——item关联表 item表在派生类中创建

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
        //窗口或者场景item
        //先新建键盘——item关联表
        //item表在派生类中创建

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
	if (angle != 360)//扇形
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
	else//圆
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
    br.setColor(nFrontColor); //设置前景色即样式颜色

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

    case 2: //横向过度
        gradient.setStart(nrect.bottomLeft());
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(1,nBackColor);
        this->setBrush(gradient);
        break;
    case 3: //横向对称过度
        gradient.setStart(nrect.bottomLeft());
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(0.5,nBackColor);
        gradient.setColorAt(1,nFrontColor);
        this->setBrush(gradient);
        break;
    case 4: //纵向过度
        gradient.setStart(nrect.topRight());
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(1,nBackColor);
        this->setBrush(gradient);
        break;
    case 5: //纵向对称过度
        gradient.setStart(nrect.topRight());
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(0.5,nBackColor);
        gradient.setColorAt(1,nFrontColor);
        this->setBrush(gradient);
        break;
    case 6: //斜上过度
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(1,nBackColor);
        this->setBrush(gradient);
        break;
    case 7: //斜上对称过度
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(0.5,nBackColor);
        gradient.setColorAt(1,nFrontColor);
        this->setBrush(gradient);
        break;
    case 8: //斜下过度
        gradient.setStart(nrect.bottomLeft());
        gradient.setFinalStop(nrect.topRight());
        gradient.setColorAt(0,nBackColor);
        gradient.setColorAt(1,nFrontColor);
        this->setBrush(gradient);
        break;
    case 9: //斜下对称过度
        gradient.setStart(nrect.bottomLeft());
        gradient.setFinalStop(nrect.topRight());
        gradient.setColorAt(0,nFrontColor);
        gradient.setColorAt(0.5,nBackColor);
        gradient.setColorAt(1,nFrontColor);
        this->setBrush(gradient);
        break;
    case 10: //右上角辐射
        gradient.setStart(nrect.topRight());
        gradient.setFinalStop(nrect.bottomLeft());
        gradient.setColorAt(0,nBackColor);
        gradient.setColorAt(1,nFrontColor);
        this->setBrush(gradient);
        break;
    case 11: //左上角辐射
        gradient.setColorAt(0,nBackColor);
        gradient.setColorAt(1, nFrontColor);
        this->setBrush(gradient);
        break;
    case 12: //中心辐射
        radial.setColorAt(0,nBackColor);
        radial.setColorAt(1,nFrontColor);
        this->setBrush(radial);
        break;
    case 13: //待操作
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

int QElipseItem::GetPattern() //获得样式
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

int QElipseItem::GetLineType() //获得线条样式类型
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

int QElipseItem::GetLineWidth() //获得线条的宽度
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

qreal QElipseItem::GetHeight()//获得圆的高度
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

qreal QElipseItem::GetWidth()//获得圆的宽度
{
    return this->rect().width();
}

void QElipseItem::SetLeft(qreal nLeft) //set the rect left
{
    QRectF nrect=rect(); //get the current rect position
    nrect.setLeft(nLeft);
    setRect(nrect);
}

qreal QElipseItem::GetLeft()//获得圆的左坐标
{
    return this->rect().x();
}

void QElipseItem::SetTop(qreal nTop) //set the rect top
{
    QRectF nrect=rect(); //get the current rect position
    nrect.setTop(nTop);
    setRect(nrect);
}

qreal QElipseItem::GetTop() //获得圆的上坐标
{
    return this->rect().y();
}

void QElipseItem::SetLineColor(QColor nColor) //set the rect outline color
{
    QPen pen = this->pen();
    pen.setColor(nColor);
    setPen(pen);
}

QColor QElipseItem::GetLineColor()//获得线条颜色
{
    return this->pen().color();
}

void QElipseItem::SetAlpha(int nAlpha) //设置透明度 nAlpha 0-255，值越小，越透明
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

int QElipseItem::GetAlpha() //获得背景色的透明度
{
    return nFrontColor.alpha();
}

void QElipseItem::SetAngle(qreal nAngle)//设置旋转角度，以图形的中心点为旋转中心
{
    QRectF nrect=rect(); //获得所选图形的坐标位置及宽和高
    qreal nMiddleX=nrect.x()+nrect.width()/2; //获得圆中心点的x坐标值
    qreal nMiddley=nrect.y()+nrect.height()/2;//获得圆中心点的y坐标值

    //把坐标系移动到(nMiddleX,nMiddley)位置后，旋转角度nAngle之后，最后把坐标恢复到原来的位置
    setTransform(QTransform().translate(nMiddleX, nMiddley).rotate(nAngle).translate(-nMiddleX, -nMiddley));
}

qreal QElipseItem::GetAngle() //获得该图形的旋转角度
{
    return rotation();
}

void QElipseItem::SetBackColor(QColor nColor) //设置背景色
{
    nBackColor=nColor;
    this->SetPattern(nPatternType);
}

QColor QElipseItem::GetBackColor()//获得背景色
{
    return nBackColor;
}

/*************************************************************************
  函数名称：SetSpanAngle(int nAngle)
  nAngle：一个跨度角度，坐标系，x方向向右为0度，往逆时针方向角度逐渐变大
  函数作用：设置一个跨度角度，获得不同形状的扇形
 *************************************************************************/
void QElipseItem::SetSpanAngle(int nAngle) //设置跨度角度，要乘16
{
   int nspanAngle = nAngle * 16;
   setSpanAngle(nspanAngle);
}

int QElipseItem::GetSpanAngle() //获得跨度角度值
{
    int nspanAngle=spanAngle();
    return nspanAngle/16;
}

/*************************************************************************
  函数名称：SetStartAngle(int nAngle)
  nAngle：一个开始角度，坐标系，x方向向右为0度，往逆时针方向角度逐渐变大
  函数作用：设置一个开始角度，获得不同形状的扇形
 *************************************************************************/
void QElipseItem::SetStartAngle(int nAngle) //设置开始度角度，要乘16
{
    int nstartAngle = nAngle * 16;
    setStartAngle(nstartAngle);
}

int QElipseItem::GetStartAngle()  //获得开始度角度值
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

void QElipseItem::SetDescription(QStringList sListStr) //可用来存储图形的属性
{
    //int ntype=type();
    setData(GROUP_DATALIST_KEY,QVariant(sListStr));
}

QStringList QElipseItem::GetDescription() //获得图形的存储属性
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
