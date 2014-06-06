#include "view/qlineitem.h"
#include <math.h>
#include "Frame/mainwindow.h"
extern  MainWindow *pwnd;

#define PI 3.14159265
QLineItem::QLineItem()
    :GraphicsPathItemExt()
{
    nLineType = 1;
    nEndArrow = 0;
    nEndPointShape = 0;
    this->setLineType(nLineType);
    setLineWidth(1);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QLineItem::QLineItem(const QPainterPath &path, QGraphicsItem *parent)
    :GraphicsPathItemExt(path, parent)
{
    nLineType = 1;
    nEndArrow = 0;
    nEndPointShape = 0;
    this->setLineType(nLineType);
    setLineWidth(1);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void QLineItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    count++;

    //QBasicGraphicsItem::compile(db, nSceneId, count, index);

    QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO line(nItemNumber ,nSceneId ,eLineClass ,eLineType ,nLineWidth ,"
                     "nLineColor ,eLineArrow ,nAlpha , eLinePointType ,nZvalue,nCollidindId,"
                     "nStartX ,nStartY ,nWidth ,nHeight )"
                     "VALUES (:nItemNumber ,:nSceneId ,:eLineClass ,:eLineType ,:nLineWidth ,"
                     ":nLineColor ,:eLineArrow ,:nAlpha , :eLinePointType,:nZvalue,:nCollidindId,"
                     ":nStartX ,:nStartY ,:nWidth ,:nHeight)");
    sqlquery.bindValue(":nItemNumber",QVariant(count));// 表 id
    sqlquery.bindValue(":nSceneId",QVariant(nSceneId));// 所在场景 id
    sqlquery.bindValue(":eLineClass",QVariant(1)); //1 代表类型为直线
    sqlquery.bindValue(":eLineType",QVariant(nLineType+1));// 线形
    sqlquery.bindValue(":nLineWidth",QVariant(getLineWidth()));// 线宽
    sqlquery.bindValue(":nLineColor",QVariant(ColorToInt(getLineColor()))); //颜色
    sqlquery.bindValue(":eLineArrow",QVariant(m_eLineEndArrowType+1));// 箭头
    sqlquery.bindValue(":nAlpha",QVariant(getAlpha()));// 透明度
    sqlquery.bindValue(":eLinePointType",QVariant(m_eLineEndArrowType+1)); //端点类型

    sqlquery.bindValue(":nZvalue",QVariant(zValue()));//层次

    sqlquery.bindValue(":nCollidindId",QVariant(index));//碰撞ID

    QRectF rect = sceneBoundingRect();
    if(getLineWidth() == 1)
    {
        sqlquery.bindValue(":nStartX",QVariant(rect.x()-1));//x
        sqlquery.bindValue(":nStartY",QVariant(rect.y()-1));//y
        sqlquery.bindValue(":nWidth",QVariant(rect.width()+2));//w
        sqlquery.bindValue(":nHeight",QVariant(rect.height()+2));//h
    }
    else
    {
        sqlquery.bindValue(":nStartX",QVariant(rect.x()));//x
        sqlquery.bindValue(":nStartY",QVariant(rect.y()));//y
        sqlquery.bindValue(":nWidth",QVariant(rect.width()));//w
        sqlquery.bindValue(":nHeight",QVariant(rect.height()));//h
    }

    bool result = false;
    result = sqlquery.exec();
    qDebug() << "insert line table :"<<result;

    sqlquery.prepare("INSERT INTO point(nItemId,nPosX,nPosY,nOrder,ePointType)"
                     "VALUES (:nItemId ,:nPosX ,:nPosY ,:nOrder ,:ePointType )");
    for(int i=0; i<2; i++)
    {
        QPointF pt = this->path().pointAtPercent(i);
        pt = mapToScene(pt);
        sqlquery.bindValue(":nItemId",QVariant(count));// item表 id
        sqlquery.bindValue(":nPosX",QVariant((int)pt.x()));// X
        sqlquery.bindValue(":nPosY",QVariant((int)pt.y())); //Y
        sqlquery.bindValue(":nOrder",QVariant(i));// 顺序
        sqlquery.bindValue(":ePointType",QVariant(1));// 显示点
        result = sqlquery.exec();
        qDebug() << "insert point table :"<<result;
    }

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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_LINE));

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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_LINE));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert sceneAndItem table :"<<result;
    }
}

QLineItem *QLineItem::Clone()
{
    QLineItem *pClone = new QLineItem();
    if (!pClone)
    {
        return NULL;
    }

    QPainterPath path = this->path();
    pClone->setPath(this->mapToScene(path));
    pClone->setPen(this->pen());

    pClone->setLineType(this->nLineType);
    pClone->setLineWidth(this->getLineWidth());
    //pClone->setEndArrow(this->getEndArrow());

    pClone->SetName(this->GetName());
    pClone->setPos(this->mapFromScene(this->scenePos()));
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->setVisible(this->isVisible());
    pClone->m_eLineEndArrowType = this->m_eLineEndArrowType;
    pClone->setId(id());

    //pClone->SaveSecurityPro(&(this->sPro));
    return pClone;
}

int QLineItem::getAlpha()
{
    return this->pen().color().alpha();
}

void QLineItem::setAlpha(int nAlpha)
{
    QPen pen = this->pen();
    QColor color = pen.color();
    color.setAlpha(nAlpha);
    pen.setColor(color);
    this->setPen(pen);
}

int QLineItem::getLineType()
{
    return nLineType;
}

void QLineItem::setLineType(int nType)
{
    nLineType = nType;
    QPen pen = this->pen();
    switch(nType)
    {
    case 0:
        pen.setStyle(Qt::NoPen); break;
    case 1:
        pen.setStyle(Qt::SolidLine); break;//实线
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

int QLineItem::getLineWidth()
{
    int width = pen().width();
    if (width == 0)
    {
        width = 1;
    }
    return width;
}

void QLineItem::setLineWidth(int nWidth)
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

QColor QLineItem::getLineColor()
{
    return this->pen().color();
}

void QLineItem::setLineColor(QColor color)
{
    QPen pen = this->pen();
    pen.setColor(color);
    this->setPen(pen);
}

int QLineItem::getEndArrow()
{
    return (int)this->m_eLineEndArrowType;
}

void QLineItem::setEndArrow(int nArrow)
{
    this->setLineEndArrow((LINE_END_ARROW_STYLE_E)nArrow);
}

void QLineItem::SetName(QString sName)
{
    //int ntype=type();
    setData(GROUP_NAME_KEY,QVariant(sName));
}

QString QLineItem::GetName()
{
    //int ntype=type();
    QString sName="";
    sName=data(GROUP_NAME_KEY).toString();
    return sName;
}

QPainterPath  QLineItem::shape () const
{
    QPainterPathStroker pps;
    pps.setWidth(7);
    return pps.createStroke(this->path());
}

//reDraw lineitem by shift mode
QRectF QLineItem::moveHandleTo(int iDragHandle, QPointF qpLocal, QRectF &qrcBondingRect)
{
    QRectF qrcRect = QRectF();
    qpLocal = mapFromScene(qpLocal);
	QPointF actPos = qpLocal;
    int iHandleIdx = iDragHandle - 1;

	if (bShiftMode)//shift mode 对齐模式
	{
		QPointF startPos;
		int iStartIndex = 0;
		if(iHandleIdx == 0)//终点
		{
			iStartIndex = 0;
		}
		startPos = path().elementAt(iStartIndex);
		double ang = atan2(qpLocal.y()-startPos.y(),qpLocal.x()-startPos.x())*6/PI;

		qDebug() << "ang = " << ang;
		if (ang >(-1) && ang < 1)
		{
			actPos = QPointF(qpLocal.x(),startPos.y());
		}
		else if (ang >2 && ang <4)
		{
			actPos = QPointF(startPos.x(),qpLocal.y());
		}
		else if ((ang >5 && ang <6) || (ang <-5 && ang >-6))
		{
			actPos = QPointF(qpLocal.x(),startPos.y());
		} 
		else if (ang >-4 && ang <-2)
		{
			actPos = QPointF(startPos.x(),qpLocal.y());
		}
	}
	QPainterPath path = this->path();
	path.setElementPositionAt(iHandleIdx, actPos.x(), actPos.y());
	this->setPath(path);
	

    


    return qrcRect;
}
int QLineItem::getEndPointShape()
{
    QPen pen = this->pen();
     Qt::PenCapStyle style ;
    style = pen.capStyle();
    if(style == Qt::FlatCap)
        nEndPointShape = 0;
    else if(style == Qt::SquareCap)
        nEndPointShape = 1;
    else if(style == Qt::RoundCap)
        nEndPointShape = 2;
    else
        nEndPointShape = 0;
    return nEndPointShape;
}

void QLineItem::setEndPointShape(int pShape)
{
    nEndPointShape = pShape;
    QPen pen = this->pen();
    switch(pShape)
    {
    case 0: //直角
        pen.setCapStyle(Qt::FlatCap);break;
    case 1: //截角
        pen.setCapStyle(Qt::SquareCap); break;
    case 2: //圆角
         pen.setCapStyle(Qt::RoundCap); break;
    default:pen.setCapStyle(Qt::FlatCap); break;
    }
    this->setPen(pen);
//    if(nEndPointShape == 0)
//    {
//        //
//    }
//    else if(nEndPointShape == 1)
//    {
//        //
//    }
}

QDataStream &operator<<(QDataStream &stream, QLineItem *pLineItem)
{
    stream << pLineItem->path();
    stream << pLineItem->getAlpha();
    stream << pLineItem->pen().width() << pLineItem->pen().color();
    stream << pLineItem->scenePos();
    stream << pLineItem->isVisible();
    stream << pLineItem->GetName() << pLineItem->nLineType;
    stream << pLineItem->getEndArrow() << pLineItem->getEndPointShape();
    stream << pLineItem->data(GROUP_TYPE_KEY).toInt();
    stream << pLineItem->data(GROUP_DATALIST_KEY).toStringList();

//    if(pwnd->getProVersion() >= 3257)
//    {
//       pLineItem->save(stream);
//    }

    stream << pLineItem->id();
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QLineItem *pLineItem)
{
    QPainterPath path;
    QPen pen;
    QColor penColor;
    int penWidth;
    int alpha;
    QPointF pos;
    QString name ;
    int nEndArrow, nEndShape;
    int typeKey = 0;
    QStringList dataList;
    dataList.clear();
    bool bVisible = true;

    stream >> path >> alpha >> penWidth >>penColor;
    stream >> pos >> bVisible >> name >> pLineItem->nLineType;
    stream >> nEndArrow >> nEndShape >> typeKey >> dataList;

//    if(pwnd->getProVersion() >= 3257)
//    {
//        pLineItem->load(stream);
//    }

    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }
    pen.setColor(penColor);
    pen.setWidth(penWidth);
    pLineItem->setPath(path);
    pLineItem->setPen(pen);
    pLineItem->setAlpha(alpha);
    pLineItem->setPos(pos);
    pLineItem->setVisible(bVisible);
    pLineItem->SetName(name);
    pLineItem->setLineType(pLineItem->nLineType);
    pLineItem->setEndArrow(nEndArrow);
    pLineItem->setEndPointShape(nEndShape);
    pLineItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pLineItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pLineItem->setId(id);
    return stream;
}

void QLineItem::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget)
 {
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->drawPath(this->path());
    QPainterPath endArrowPath = getEndArrowPath();
    if(!endArrowPath.isEmpty())
    {
        qDebug() << endArrowPath;
        painter->fillPath(endArrowPath,QBrush(getLineColor()));
    }
    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);
 }
