#include <view/qpolygonitem.h>
#include "samdrawscene.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
/***************************************************************************
  *
  *class for QPolygonItem
  *
  **************************************************************************/
QPolygonItem::QPolygonItem()
    :GraphicsPolygonItemSamExt()
{
    nLineType = 1;
    m_backColor = QColor(0,0,0);
    m_frontColor = QColor(255,255,255);
    int m_nPattern = 1;
    this->setPattern(m_nPattern);
    this->setLineType(nLineType);
}
void QPolygonItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
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
    sqlquery.bindValue(":ePolygonClass",QVariant(5)); //5 代表类型为多边形
    sqlquery.bindValue(":eLineType",QVariant(nLineType+1));// 线形
    sqlquery.bindValue(":nLineWidth",QVariant(getLineWidth()));// 线宽
    sqlquery.bindValue(":nLineColor",QVariant(ColorToInt(getLineColor()))); //颜色
    sqlquery.bindValue(":eStyle",QVariant(m_nPattern+1));// 样式
    sqlquery.bindValue(":nBackColor",QVariant(ColorToInt(getBackColor()))); //背景色
    sqlquery.bindValue(":nForeColor",QVariant(ColorToInt(getFrontColor()))); //前景色
    sqlquery.bindValue(":nAlpha",QVariant(getAlpha()));// 透明度
    QRect rect = this->sceneBoundingRect().toRect();
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

    sqlquery.bindValue(":nZvalue",QVariant(zValue()));//层次

    sqlquery.bindValue(":nCollidindId",QVariant(index));//碰撞ID

    bool result = false;
    result = sqlquery.exec();
    qDebug() << "insert Polygon table :"<<result;

    sqlquery.prepare("INSERT INTO point(nItemId,nPosX,nPosY,nOrder,ePointType)"
                     "VALUES (:nItemId ,:nPosX ,:nPosY ,:nOrder ,:ePointType )");
    QPolygonF pointlist = polygon();
    for(int i=0; i<pointlist.size(); i++)
    {
        QPointF qpPoint = mapToScene(pointlist.at(i));
        int x = qpPoint.x();
        int y = qpPoint.y();
        sqlquery.bindValue(":nItemId",QVariant(count));// item表 id
        sqlquery.bindValue(":nPosX",QVariant(x));// X
        sqlquery.bindValue(":nPosY",QVariant(y)); //Y
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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_POLYGON));

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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_POLYGON));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert sceneAndItem table :"<<result;
    }
}



QPolygonItem::QPolygonItem(QPolygonF &qpsPolygonF)
    :GraphicsPolygonItemSamExt(qpsPolygonF)
{
    nLineType = 1;
    m_backColor = QColor(0,0,0);
    m_frontColor = QColor(255,255,255);
    int m_nPattern = 1;
    this->setPattern(m_nPattern);
    this->setLineType(nLineType);
}

QPolygonItem *QPolygonItem::Clone()
{
    QPolygonItem *pClone = new QPolygonItem();
    if (!pClone)
    {
        return NULL;
    }

    QPolygonF polygon = this->polygon();
    polygon = this->mapToScene(polygon);
    pClone->SetName(this->GetName());
    pClone->setPolygon(polygon);
    pClone->setPen(this->pen());
    pClone->setLineType(this->getLineType());
    pClone->setBackColor(this->getBackColor());
    pClone->setFrontColor(this->getFrontColor());
    pClone->setPattern(this->getPattern());
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->setId(id());

    //pClone->SaveSecurityPro(&(this->sPro));

    return pClone;
}


int QPolygonItem::getAlpha()
{
    return m_frontColor.alpha();
}

void QPolygonItem::setAlpha(int nAlpha)
{
    m_frontColor.setAlpha(nAlpha);
    m_backColor.setAlpha(nAlpha);
    this->setPattern(m_nPattern);

    QPen pen = this->pen();
    QColor color = pen.color();
    color.setAlpha(nAlpha);
    pen.setColor(color);
    this->setPen(pen);
}

int QPolygonItem::getLineType()
{
    return nLineType;
}

void QPolygonItem::setLineType(int nType)
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

int QPolygonItem::getLineWidth()
{
    int width = pen().width();
    if (width == 0)
    {
        width = 1;
    }
    return width;
}

void QPolygonItem::setLineWidth(int nWidth)
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

QColor QPolygonItem::getLineColor()
{
    return this->pen().color();
}

void QPolygonItem::setLineColor(QColor color)
{
    QPen pen = this->pen();
    pen.setColor(color);
    this->setPen(pen);
}

QColor QPolygonItem::getBackColor()
{
    return m_backColor;
}

void QPolygonItem::setBackColor(QColor color)
{
    m_backColor = color;
    this->setPattern(m_nPattern);
}

QColor QPolygonItem::getFrontColor()
{
    return m_frontColor;
}

void QPolygonItem::setFrontColor(QColor color)
{
    m_frontColor = color;
    this->setPattern(m_nPattern);
}

int QPolygonItem::getPattern()
{
    return m_nPattern;
}

void QPolygonItem::SetName(QString sName)
{
        //int ntype=type();
        setData(GROUP_NAME_KEY,QVariant(sName));
}

QString QPolygonItem::GetName()
{
        //int ntype=type();
	QString sName="";
        sName=data(GROUP_NAME_KEY).toString();
	return sName;
}

void QPolygonItem::setPattern(int nPattern)
{
    m_nPattern = nPattern;
    QRectF rect = this->boundingRect();
    QLinearGradient gradient(rect.topLeft(),rect.bottomRight());
    QRadialGradient radial(rect.center(),rect.width()/2,rect.center());
    // Conical.setSpread(QGradient::ReflectSpread);
    gradient.setSpread(QGradient::PadSpread);//	RepeatSpread

    QBrush br=brush();
    br.setColor(m_frontColor); //设置前景色即样式颜色

    switch(m_nPattern)
    {
    case 0:br.setStyle(Qt::NoBrush);break;
    case 1:br.setColor(m_backColor);br.setStyle(Qt::SolidPattern);break;
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
        gradient.setStart(rect.bottomLeft());
        gradient.setColorAt(0,m_frontColor);
        gradient.setColorAt(1,m_backColor);
        this->setBrush(gradient);
        break;
    case 3: //横向对称过度
        gradient.setStart(rect.bottomLeft());
        gradient.setColorAt(0,m_frontColor);
        gradient.setColorAt(0.5,m_backColor);
        gradient.setColorAt(1,m_frontColor);
        this->setBrush(gradient);
        break;
    case 4: //纵向过度
        gradient.setStart(rect.topRight());
        gradient.setColorAt(0,m_frontColor);
        gradient.setColorAt(1,m_backColor);
        this->setBrush(gradient);
        break;
    case 5: //纵向对称过度
        gradient.setStart(rect.topRight());
        gradient.setColorAt(0,m_frontColor);
        gradient.setColorAt(0.5,m_backColor);
        gradient.setColorAt(1,m_frontColor);
        this->setBrush(gradient);
        break;
    case 6: //斜上过度
        gradient.setColorAt(0,m_frontColor);
        gradient.setColorAt(1,m_backColor);
        this->setBrush(gradient);
        break;
    case 7: //斜上对称过度
        gradient.setColorAt(0,m_frontColor);
        gradient.setColorAt(0.5,m_backColor);
        gradient.setColorAt(1,m_frontColor);
        this->setBrush(gradient);
        break;
    case 8: //斜下过度
        gradient.setStart(rect.bottomLeft());
        gradient.setFinalStop(rect.topRight());
        gradient.setColorAt(0,m_backColor);
        gradient.setColorAt(1,m_frontColor);
        this->setBrush(gradient);
        break;
    case 9: //斜下对称过度
        gradient.setStart(rect.bottomLeft());
        gradient.setFinalStop(rect.topRight());
        gradient.setColorAt(0,m_frontColor);
        gradient.setColorAt(0.5,m_backColor);
        gradient.setColorAt(1,m_frontColor);
        this->setBrush(gradient);
        break;
    case 10: //右上角辐射
        gradient.setStart(rect.topRight());
        gradient.setFinalStop(rect.bottomLeft());
        gradient.setColorAt(0,m_backColor);
        gradient.setColorAt(1,m_frontColor);
        this->setBrush(gradient);
        break;
    case 11: //左上角辐射
        gradient.setColorAt(0,m_backColor);
        gradient.setColorAt(1, m_frontColor);
        this->setBrush(gradient);
        break;
    case 12: //中心辐射
        radial.setColorAt(0,m_backColor);
        radial.setColorAt(1,m_frontColor);
        this->setBrush(radial);
        break;
    case 13: //待操作
        radial.setFocalPoint(rect.x(),rect.center().y());
        radial.setColorAt(0,m_backColor);
        radial.setColorAt(1,m_frontColor);
        this->setBrush(radial);
        break;
    default:
        break;
    }

    if(0 <= m_nPattern && m_nPattern < 2)
        this->setBrush(br);
}

QDataStream &operator<<(QDataStream &stream, QPolygonItem *pPolygonItem)
{
    stream << pPolygonItem->GetName();
    stream << pPolygonItem->polygon();
    stream << pPolygonItem->getAlpha();
    stream << pPolygonItem->getLineType();
    stream << pPolygonItem->getLineWidth();
    stream << pPolygonItem->getLineColor();
    stream << pPolygonItem->getBackColor();
    stream << pPolygonItem->getFrontColor();
    stream << pPolygonItem->getPattern();
    stream << pPolygonItem->scenePos();
    stream << pPolygonItem->isVisible();
    stream << pPolygonItem->data(GROUP_TYPE_KEY).toInt();
    stream << pPolygonItem->data(GROUP_DATALIST_KEY).toStringList();
    stream << pPolygonItem->id();
//    if(pwnd->getProVersion() >= 3257)
//    {
//        pPolygonItem->save(stream);
//    }
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QPolygonItem *pPolygonItem)
{
    int nAlpha, lineType,lineWidth;
    QColor lineColor;
    QPointF pos;
    QPolygonF polygon;
    QString name ;
    int typeKey = 0;
    QStringList dataList;
    dataList.clear();
    bool bVisible = true;

    stream >> name ;
    stream >> polygon >> nAlpha >> lineType >> lineWidth >> lineColor;
    stream >> pPolygonItem->m_backColor >> pPolygonItem->m_frontColor;
    stream >> pPolygonItem->m_nPattern >> pos >> bVisible >> typeKey >> dataList;
//    if(pwnd->getProVersion()>= 3257)
//    {
//        pPolygonItem->load(stream);
//    }
    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }
    pPolygonItem->SetName(name);
    pPolygonItem->setPolygon(polygon);
    pPolygonItem->setAlpha(nAlpha);
    pPolygonItem->setLineType(lineType);
    pPolygonItem->setLineWidth(lineWidth);
    pPolygonItem->setLineColor(lineColor);
    pPolygonItem->setPattern(pPolygonItem->m_nPattern);
    pPolygonItem->setPos(pos);
    pPolygonItem->setVisible(bVisible);
    pPolygonItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pPolygonItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pPolygonItem->setId(id);

    return stream;
}

void QPolygonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->drawPolygon(this->polygon(), this->fillRule());
    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);
}

/***************************************************************************
  *
  *class for QFoldLineItem
  *
  **************************************************************************/
QFoldLineItem::QFoldLineItem()
    :GraphicsPathItemExt()
{
    nLineType = 1;
    nEndArrow = 0;
    nEndPointShape = 0;
    this->setLineType(nLineType);
}

QFoldLineItem::QFoldLineItem(const QPainterPath &path, QGraphicsItem *parent)
    :GraphicsPathItemExt(path, parent)
{
    nLineType = 1;
    nEndArrow = 0;
    nEndPointShape = 0;
    this->setLineType(nLineType);
}

void QFoldLineItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
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
    sqlquery.bindValue(":eLineClass",QVariant(2)); //2 代表类型为折线
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
    qDebug() << "insert FoldLine table :"<<result;

    sqlquery.prepare("INSERT INTO point(nItemId,nPosX,nPosY,nOrder,ePointType)"
                     "VALUES (:nItemId ,:nPosX ,:nPosY ,:nOrder ,:ePointType )");
    QList<QPointF > pointlist = points();
    for(int i=0; i<pointlist.size(); i++)
    {
        int x = pointlist.at(i).x();
        int y = pointlist.at(i).y();
        sqlquery.bindValue(":nItemId",QVariant(count));// item表 id
        sqlquery.bindValue(":nPosX",QVariant(x));// X
        sqlquery.bindValue(":nPosY",QVariant(y)); //Y
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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_FOLDLINE));

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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_FOLDLINE));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert sceneAndItem table :"<<result;
    }
}
//获取所有的点
QList<QPointF > QFoldLineItem::points()
{
    QList<QPointF> pointList;
    QList<QPolygonF> polygonList;

    polygonList = path().toSubpathPolygons();
        if(polygonList.isEmpty())
            return pointList;
        int size = polygonList.first().size();
        QPolygonF subPathPoints = polygonList.first();
        subPathPoints = mapToScene(subPathPoints);
        for (int i = 0; i < size; i++)
        {
            pointList << subPathPoints[i];
        }

    return pointList;
}

QFoldLineItem* QFoldLineItem::Clone()
{
    QFoldLineItem *pClone = new QFoldLineItem();
    if (!pClone)
    {
        return NULL;
    }

    QPainterPath path = this->path();
    path = this->mapToScene(path);
    pClone->SetName(this->GetName());
    pClone->setPath(path);
    pClone->setPen(this->pen());
    pClone->setLineType(this->getLineType());
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->m_eLineEndArrowType = this->m_eLineEndArrowType;
    pClone->setId(id());

    //pClone->SaveSecurityPro(&(this->sPro));
    return pClone;
}


int QFoldLineItem::getAlpha()
{
    return this->pen().color().alpha();
}

void QFoldLineItem::setAlpha(int nAlpha)
{
    QPen pen = this->pen();
    QColor color = pen.color();
    color.setAlpha(nAlpha);
    pen.setColor(color);
    this->setPen(pen);
}

int QFoldLineItem::getLineType()
{
    return nLineType;
}

void QFoldLineItem::setLineType(int nType)
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

int QFoldLineItem::getLineWidth()
{
    int width = pen().width();
    if (width == 0)
    {
        width = 1;
    }
    return width;
}

void QFoldLineItem::setLineWidth(int nWidth)
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

QColor QFoldLineItem::getLineColor()
{
    return this->pen().color();
}

void QFoldLineItem::setLineColor(QColor color)
{
    QPen pen = this->pen();
    pen.setColor(color);
    this->setPen(pen);
}

void QFoldLineItem::SetName(QString sName)
{
    setData(GROUP_NAME_KEY,QVariant(sName));
}

QString QFoldLineItem::GetName()
{
    return data(GROUP_NAME_KEY).toString();
}

int QFoldLineItem::getEndArrow()
{
    return (int)this->m_eLineEndArrowType;
}

void QFoldLineItem::setEndArrow(int nArrow)
{
    this->setLineEndArrow((LINE_END_ARROW_STYLE_E)nArrow);
}

int QFoldLineItem::getEndPointShape()
{
    QPen pen = this->pen();
    Qt::PenJoinStyle style ;
    style = pen.joinStyle();
    if(style == Qt::MiterJoin)
        nEndPointShape = 0;
    else if(style == Qt::BevelJoin)
        nEndPointShape = 1;
    else if(style == Qt::RoundJoin)
        nEndPointShape = 2;
    else
        nEndPointShape = 0;
    return nEndPointShape;
}

void QFoldLineItem::setEndPointShape(int pShape)
{
    nEndPointShape = pShape;
    QPen pen = this->pen();
    switch(pShape)
    {
    case 0: //直角
        pen.setJoinStyle(Qt::MiterJoin); pen.setCapStyle(Qt::FlatCap);break;
    case 1: //截角
        pen.setJoinStyle(Qt::BevelJoin);pen.setCapStyle(Qt::SquareCap); break;
    case 2: //圆角
        pen.setJoinStyle(Qt::RoundJoin); pen.setCapStyle(Qt::RoundCap); break;
    default:pen.setJoinStyle(Qt::MiterJoin);pen.setCapStyle(Qt::FlatCap); break;
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

void QFoldLineItem::paint(QPainter *painter,
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

QDataStream &operator<<(QDataStream &stream, QFoldLineItem *pFoldLineItem)
{
    stream << pFoldLineItem->path();
    stream << pFoldLineItem->getAlpha();
    stream << pFoldLineItem->pen().width() << pFoldLineItem->pen().color();
    stream << pFoldLineItem->scenePos();
    stream << pFoldLineItem->isVisible();
    stream << pFoldLineItem->GetName() << pFoldLineItem->nLineType;
    stream << pFoldLineItem->getEndArrow() << pFoldLineItem->getEndPointShape();
    stream << pFoldLineItem->data(GROUP_TYPE_KEY).toInt();
    stream << pFoldLineItem->data(GROUP_DATALIST_KEY).toStringList();
    stream << pFoldLineItem->id();
//    if(pwnd->getProVersion() >= 3257)
//    {
//       pFoldLineItem->save(stream);
//    }
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QFoldLineItem *pFoldLineItem)
{
    QPainterPath path;
    QColor penColor;
    int penWidth;
    QPen pen;
    int alpha;
    QPointF pos;
    QString name ;
    int nEndArrow, nEndShape;
    int typeKey = 0;
    QStringList dataList;
    dataList.clear();
    bool bVisible = true;

    stream >> path >> alpha >> penWidth >> penColor;
    stream >> pos >> bVisible >> name >> pFoldLineItem->nLineType;
    stream >> nEndArrow >> nEndShape >> typeKey >> dataList;
//    if(pwnd->getProVersion() >= 3257)
//    {
//        pFoldLineItem->load(stream);
//    }

    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }
    pen.setWidth(penWidth);
    pen.setColor(penColor);
    pFoldLineItem->setPath(path);
    pFoldLineItem->setPen(pen);
    pFoldLineItem->setAlpha(alpha);
    pFoldLineItem->setPos(pos);
    pFoldLineItem->setVisible(bVisible);
    pFoldLineItem->SetName(name);
    pFoldLineItem->setLineType(pFoldLineItem->nLineType);
    pFoldLineItem->setEndArrow(nEndArrow);
    pFoldLineItem->setEndPointShape(nEndShape);
    pFoldLineItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pFoldLineItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pFoldLineItem->setId(id);
    return stream;
}


/***************************************************************************
  *
  *class for QFreeLineItem
  *
  **************************************************************************/
QFreeLineItem::QFreeLineItem()
    :GraphicsPathItemExt()
{
    nLineType = 1;
    nEndArrow = 0;
    nEndPointShape = 0;
    this->setLineType(nLineType);
}

QFreeLineItem::QFreeLineItem(const QPainterPath &path, QGraphicsItem *parent)
    :GraphicsPathItemExt(path, parent)
{
    nLineType = 1;
    nEndArrow = 0;
    nEndPointShape = 0;
    this->setLineType(nLineType);
}

void QFreeLineItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
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
    sqlquery.bindValue(":eLineClass",QVariant(3)); //3 代表类型为自由直线
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
    qDebug() << "insert FreeLine table :"<<result;

    sqlquery.prepare("INSERT INTO point(nItemId,nPosX,nPosY,nOrder,ePointType)"
                     "VALUES (:nItemId ,:nPosX ,:nPosY ,:nOrder ,:ePointType )");
    QList<QPointF > pointlist = points();
    for(int i=0; i<pointlist.size(); i++)
    {
        int x = pointlist.at(i).x();
        int y = pointlist.at(i).y();
        sqlquery.bindValue(":nItemId",QVariant(count));// item表 id
        sqlquery.bindValue(":nPosX",QVariant(x));// X
        sqlquery.bindValue(":nPosY",QVariant(y)); //Y
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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_FREELINE));

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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_FREELINE));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert sceneAndItem table :"<<result;
    }
}

QList<QPointF > QFreeLineItem::points()
{
    QList<QPointF> pointList;
    QList<QPolygonF> polygonList;

    polygonList = path().toSubpathPolygons();
        if(polygonList.isEmpty())
            return pointList;
        int size = polygonList.first().size();
        QPolygonF subPathPoints = polygonList.first();
        subPathPoints = mapToScene(subPathPoints);
        for (int i = 0; i < size; i++)
        {
            pointList << subPathPoints[i];
        }

    return pointList;
}

QFreeLineItem* QFreeLineItem::Clone()
{
    QFreeLineItem *pClone = new QFreeLineItem();
    if (!pClone)
    {
        return NULL;
    }

    QPainterPath path = this->path();
    path = this->mapToScene(path);
//    pClone->SetName(this->GetName());
    pClone->setPath(path);
    pClone->setPen(this->pen());
    pClone->setLineType(this->getLineType());
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->m_eLineEndArrowType = this->m_eLineEndArrowType;
    pClone->setId(id());

    //pClone->SaveSecurityPro(&(this->sPro));
    return pClone;
}


int QFreeLineItem::getAlpha()
{
    return this->pen().color().alpha();
}

void QFreeLineItem::setAlpha(int nAlpha)
{
    QPen pen = this->pen();
    QColor color = pen.color();
    color.setAlpha(nAlpha);
    pen.setColor(color);
    this->setPen(pen);
}

int QFreeLineItem::getLineType()
{
    return nLineType;
}

void QFreeLineItem::setLineType(int nType)
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

int QFreeLineItem::getLineWidth()
{
    int width = pen().width();
    if (width == 0)
    {
        width = 1;
    }
    return width;
}

void QFreeLineItem::setLineWidth(int nWidth)
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

QColor QFreeLineItem::getLineColor()
{
    return this->pen().color();
}

void QFreeLineItem::setLineColor(QColor color)
{
    QPen pen = this->pen();
    pen.setColor(color);
    this->setPen(pen);
}

int QFreeLineItem::getEndArrow()
{
    return (int)this->m_eLineEndArrowType;
}

void QFreeLineItem::setEndArrow(int nArrow)
{
    this->setLineEndArrow((LINE_END_ARROW_STYLE_E)nArrow);
}

int QFreeLineItem::getEndPointShape()
{
    QPen pen = this->pen();
    Qt::PenJoinStyle style ;
    style = pen.joinStyle();
    if(style == Qt::MiterJoin)
        nEndPointShape = 0;
    else if(style == Qt::BevelJoin)
        nEndPointShape = 1;
    else if(style == Qt::RoundJoin)
        nEndPointShape = 2;
    else
        nEndPointShape = 0;
    return nEndPointShape;
}

void QFreeLineItem::setEndPointShape(int pShape)
{
    nEndPointShape = pShape;
    QPen pen = this->pen();
    switch(pShape)
    {
    case 0: //直角
        pen.setJoinStyle(Qt::MiterJoin); pen.setCapStyle(Qt::FlatCap);break;
    case 1: //截角
        pen.setJoinStyle(Qt::BevelJoin);pen.setCapStyle(Qt::SquareCap); break;
    case 2: //圆角
        pen.setJoinStyle(Qt::RoundJoin); pen.setCapStyle(Qt::RoundCap); break;
    default:pen.setJoinStyle(Qt::MiterJoin);pen.setCapStyle(Qt::FlatCap); break;
    }
    this->setPen(pen);
}

void QFreeLineItem::setName(QString sName)
{
    setData(GROUP_NAME_KEY,QVariant(sName));
}

QString QFreeLineItem::getName()
{
    return data(GROUP_NAME_KEY).toString();
}

void QFreeLineItem::paint(QPainter *painter,
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
QDataStream &operator<<(QDataStream &stream, QFreeLineItem *pFreeLineItem)
{
    stream << pFreeLineItem->path();
    stream << pFreeLineItem->getAlpha();
    stream << pFreeLineItem->pen().width() << pFreeLineItem->pen().color();
    stream << pFreeLineItem->scenePos();
    stream << pFreeLineItem->isVisible();
    stream << pFreeLineItem->getName() << pFreeLineItem->nLineType;
    stream << pFreeLineItem->getEndArrow() << pFreeLineItem->getEndPointShape();
    stream << pFreeLineItem->data(GROUP_TYPE_KEY).toInt();
    stream << pFreeLineItem->data(GROUP_DATALIST_KEY).toStringList();
    stream << pFreeLineItem->id();

//    if(pwnd->getProVersion() >= 3257)
//    {
//        pFreeLineItem->save(stream);
//    }
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QFreeLineItem *pFreeLineItem)
{
    QPainterPath path;
    QColor penColor;
    int penWidth;
    QPen pen;
    int alpha;
    QPointF pos;
    QString name ;
    int nEndArrow, nEndShape;
    int typeKey = 0;
    QStringList dataList;
    dataList.clear();
    bool bVisible = true;

    stream >> path >> alpha >> penWidth >> penColor;
    stream >> pos >> bVisible >> name >> pFreeLineItem->nLineType;
    stream >> nEndArrow >> nEndShape >> typeKey >> dataList;
//    if(pwnd->getProVersion() >= 3257)
//    {
//         pFreeLineItem->load(stream);
//    }
    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }
    pen.setWidth(penWidth);
    pen.setColor(penColor);
    pFreeLineItem->setPath(path);
    pFreeLineItem->setPen(pen);
    pFreeLineItem->setAlpha(alpha);
    pFreeLineItem->setPos(pos);
    pFreeLineItem->setVisible(bVisible);
    pFreeLineItem->setName(name);
    pFreeLineItem->setLineType(pFreeLineItem->nLineType);
    pFreeLineItem->setEndArrow(nEndArrow);
    pFreeLineItem->setEndPointShape(nEndShape);
    pFreeLineItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pFreeLineItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pFreeLineItem->setId(id);
    return stream;
}


/***************************************************************************
  *
  *class for QLineCircleItem
  *
  **************************************************************************/
QLineCircleItem::QLineCircleItem()
{
    nLineType = 1;
    nEndArrow = 0;
    nEndPointShape = 0;
    this->setLineType(nLineType);
    this->setLineWidth(1);
}

QLineCircleItem::QLineCircleItem(const QPainterPath &path, QGraphicsItem *parent)
    :GraphicsMultiPathItem(path, parent)
{
    nLineType = 1;
    nEndArrow = 0;
    nEndPointShape = 0;
    this->setLineType(nLineType);
    this->setLineWidth(1);
}

int QLineCircleItem::getAlpha()
{
    return this->pen().color().alpha();
}

void QLineCircleItem::setAlpha(int nAlpha)
{
    QPen pen = this->pen();
    QColor color = pen.color();
    color.setAlpha(nAlpha);
    pen.setColor(color);
    this->setPen(pen);
}

int QLineCircleItem::getLineType()
{
    return nLineType;
}

void QLineCircleItem::setLineType(int nType)
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

int QLineCircleItem::getLineWidth()
{
    int width = pen().width();
    if (width == 0)
    {
        width = 1;
    }
    return width;
}

void QLineCircleItem::setLineWidth(int nWidth)
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

QColor QLineCircleItem::getLineColor()
{
    return this->pen().color();
}

void QLineCircleItem::setLineColor(QColor color)
{
    QPen pen = this->pen();
    pen.setColor(color);
    this->setPen(pen);
}

int QLineCircleItem::getEndArrow()
{
    return (int)this->m_eLineEndArrowType;
}

void QLineCircleItem::setEndArrow(int nArrow)
{
    this->setLineEndArrow((LINE_END_ARROW_STYLE_E)nArrow);
}

int QLineCircleItem::getEndPointShape()
{
    return nEndPointShape;
}

void QLineCircleItem::setEndPointShape(int pShape)
{
    nEndPointShape = pShape;
    if(nEndPointShape == 0)
    {
        //
    }
    else if(nEndPointShape == 1)
    {
        //
    }
}

void QLineCircleItem::setName(QString sName)
{
    setData(GROUP_NAME_KEY,QVariant(sName));
}

QString QLineCircleItem::getName()
{
    return data(GROUP_NAME_KEY).toString();
}

void QLineCircleItem::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget)
 {
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->drawPath(this->path());
    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);
 }

QDataStream &operator<<(QDataStream &stream, QLineCircleItem *pLineCircleItem)
{
    stream << pLineCircleItem->path();
    stream << pLineCircleItem->getAlpha();
    stream << pLineCircleItem->pen().width() << pLineCircleItem->pen().color();
    stream << pLineCircleItem->scenePos();
    stream << pLineCircleItem->isVisible();
    stream << pLineCircleItem->getName() << pLineCircleItem->nLineType;
    stream << pLineCircleItem->getEndArrow() << pLineCircleItem->getEndPointShape();
    stream << pLineCircleItem->data(GROUP_TYPE_KEY).toInt();
    stream << pLineCircleItem->data(GROUP_DATALIST_KEY).toStringList();
    stream << pLineCircleItem->id();
//    if(pwnd->getProVersion() >= 3257)
//    {
//        pLineCircleItem->save(stream);
//    }
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QLineCircleItem *pLineCircleItem)
{
    QPainterPath path;
    QColor penColor;
    int penWidth;
    QPen pen;
    int alpha;
    QPointF pos;
    QString name ;
    int nEndArrow, nEndShape;
    int typeKey = 0;
    QStringList dataList;
    dataList.clear();
    bool bVisible = true;

    stream >> path >> alpha >> penWidth >> penColor;
    stream >> pos >> bVisible >> name >> pLineCircleItem->nLineType;
    stream >> nEndArrow >> nEndShape >> typeKey >> dataList;
//    if(pwnd->getProVersion() >= 3257)
//    {
//        pLineCircleItem->load(stream);
//    }

    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }
    pen.setWidth(penWidth);
    pen.setColor(penColor);
    pLineCircleItem->setPath(path);
    pLineCircleItem->setPen(pen);
    pLineCircleItem->setAlpha(alpha);
    pLineCircleItem->setPos(pos);
    pLineCircleItem->setVisible(bVisible);
    pLineCircleItem->setName(name);
    pLineCircleItem->setLineType(pLineCircleItem->nLineType);
    pLineCircleItem->m_eLineEndArrowType = (LINE_END_ARROW_STYLE_E)nEndArrow;
    pLineCircleItem->setEndArrow(nEndArrow);
//    pLineCircleItem->setEndPointShape(nEndShape);
    pLineCircleItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pLineCircleItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pLineCircleItem->setId(id);
    return stream;
}

void QLineCircleItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
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
    sqlquery.bindValue(":eLineClass",QVariant(4)); //4 代表类型为曲线圆弧
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
    qDebug() << "insert LineCircle table :"<<result;

    QList<QPolygonF > pointlist = getHandleList();
    //QList<QPointF >  lst = points();
    int nOrder = 0;
    for(int i=0; i<pointlist.size(); i++)
    {
        InsertPointTable(db,count,pointlist.at(i),nOrder);
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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_LINECIRCLE));

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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_LINECIRCLE));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert sceneAndItem table :"<<result;
    }
}

void QLineCircleItem::InsertPointTable(QSqlDatabase &db, int nItemId,QPolygonF polygon,int &order)
{
    bool result;
    QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO point(nItemId,nPosX,nPosY,nOrder,ePointType)"
                     "VALUES (:nItemId ,:nPosX ,:nPosY ,:nOrder ,:ePointType )");
    QPointF pt;
    if(polygon.size() == 2)
    {
        for(int i=0;i<2;i++)
        {
            pt = this->mapToScene( polygon.at(i));
            int x = pt.x();
            int y = pt.y();
            sqlquery.bindValue(":nItemId",QVariant(nItemId));// item表 id
            sqlquery.bindValue(":nPosX",QVariant(x));// X
            sqlquery.bindValue(":nPosY",QVariant(y)); //Y
            sqlquery.bindValue(":nOrder",QVariant(order++));// 顺序
            sqlquery.bindValue(":ePointType",QVariant(1));// 显示点
            result = sqlquery.exec();
            qDebug() << "insert point table :"<<result;
        }

    }
    else if(polygon.size() == 3)
    {
        for(int i=0;i<3;i++)
        {
            if(i == 1)
            {
                pt = this->mapToScene( polygon.at(i));
                int x = pt.x();
                int y = pt.y();
                sqlquery.bindValue(":nItemId",QVariant(nItemId));// item表 id
                sqlquery.bindValue(":nPosX",QVariant(x));// X
                sqlquery.bindValue(":nPosY",QVariant(y)); //Y
                sqlquery.bindValue(":nOrder",QVariant(order++));// 顺序
                sqlquery.bindValue(":ePointType",QVariant(2));// 控制点
                result = sqlquery.exec();
                qDebug() << "insert point table :"<<result;
            }
            else
            {
                pt = this->mapToScene( polygon.at(i));
                int x = pt.x();
                int y = pt.y();
                sqlquery.bindValue(":nItemId",QVariant(nItemId));// item表 id
                sqlquery.bindValue(":nPosX",QVariant(x));// X
                sqlquery.bindValue(":nPosY",QVariant(y)); //Y
                sqlquery.bindValue(":nOrder",QVariant(order++));// 顺序
                sqlquery.bindValue(":ePointType",QVariant(1));// 显示点
                result = sqlquery.exec();
                qDebug() << "insert point table :"<<result;
            }
        }
    }
}

QList<QPointF > QLineCircleItem::points()
{
    QList<QPointF> pointList;
    QList<QPolygonF> polygonList;

    polygonList = getHandleList();
    if(polygonList.isEmpty())
        return pointList;
    int size = polygonList.size();

    for(int i = 0;i<size; i++)
    {
        QPolygonF subPathPoints = polygonList.at(i);
        subPathPoints = mapToScene(subPathPoints);
        if(i==0)
        {
            pointList << subPathPoints.first();
            pointList << subPathPoints.back();
        }
        else
        {
            pointList << subPathPoints.back();
        }
    }

    return pointList;
}
QLineCircleItem *QLineCircleItem::Clone()
{
    QPainterPath path = this->path();
    path = this->mapToScene(path);
    QLineCircleItem *pCircleItem = new QLineCircleItem(path);
    pCircleItem->setPen(this->pen());
    pCircleItem->setLineType(this->getLineType());
    pCircleItem->m_eLineEndArrowType = this->m_eLineEndArrowType;
    pCircleItem->setId(id());

    //pCircleItem->SaveSecurityPro(&(this->sPro));
    return pCircleItem;
}
