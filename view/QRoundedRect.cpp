#include "QRoundedRect.h"
#include <QPainterPath>
#include <QLinearGradient>
#include <QPen>
#include "Frame/mainwindow.h"
extern  MainWindow *pwnd;

QRoundedRect::QRoundedRect()
{
    xRadius = 10;
    yRadius = 10;
    qWidth = 100;
    qHeight = 100;
    nBackColor = QColor(255,255,255);    //初始化背景颜色
    nFrontColor = QColor(0,0,0);   //初始化前景色
    nPatternType = 1;              //样式类初始化为纯色
    nLineType = 1;
    Rpos.setX(0);
    Rpos.setY(0);

    RectPath.addRoundedRect(QRectF(0,0,100,100),10,10,Qt::AbsoluteSize);//AbsoluteSize  RelativeSize
    setPath(RectPath);
    setFlag(QGraphicsItem::ItemIsSelectable, true); //设置组合图形可选
    setFlag(QGraphicsItem::ItemIsMovable, true);
}

void QRoundedRect::SetWidth(qreal Width)
{
    qWidth = Width;
    QRectF rc(0,0,Width,qHeight);
    QPainterPath path;
    path.addRoundedRect(rc,xRadius,yRadius,Qt::AbsoluteSize);
    RectPath = path;
    setPath(RectPath);
    SetPattern(nPatternType);
}

qreal QRoundedRect::GetWidth()
{
    return qWidth;
}

void QRoundedRect::SetHeight(qreal Height)
{
    qHeight = Height;
    QRectF rc(0,0,qWidth,Height);
    QPainterPath path;
    path.addRoundedRect(rc,xRadius,yRadius,Qt::AbsoluteSize);
    RectPath = path;
    setPath(RectPath);
    SetPattern(nPatternType);
}

qreal QRoundedRect::GetHeight()
{
    return qHeight;
}

void QRoundedRect::SetxRadius(qreal qxRadius)
{
    xRadius = qxRadius;
    QRectF rc(0,0,qWidth,qHeight);
    QPainterPath path;
    path.addRoundedRect(rc,qxRadius,yRadius,Qt::AbsoluteSize);
    RectPath = path;
    setPath(RectPath);
    SetPattern(nPatternType);
}

qreal QRoundedRect::GetxRadius()
{
    return xRadius;
}

void QRoundedRect::SetyRadius(qreal qyRadius)
{
    yRadius = qyRadius;
    QRectF rc(0,0,qWidth,qHeight);
    QPainterPath path;
    path.addRoundedRect(rc,xRadius,qyRadius,Qt::AbsoluteSize);
    RectPath = path;
    setPath(RectPath);
    SetPattern(nPatternType);
}

qreal QRoundedRect::GetyRadius()
{
    return yRadius;
}

void QRoundedRect::SetName(QString qstr)
{
    setData(GROUP_NAME_KEY,QVariant(qstr));
}

QString QRoundedRect::GetName()
{
    return data(GROUP_NAME_KEY).toString();
}

void QRoundedRect::SetPattern(int nPATTERN)
{
    nPatternType = nPATTERN; //样式类型
    QRectF nrect(Rpos.x(),Rpos.y(),qWidth,qHeight);
    QLinearGradient gradient(nrect.topLeft(),nrect.bottomRight());
    QRadialGradient Radial(nrect.center(),nrect.width()/2,nrect.center());
    gradient.setSpread(QGradient::PadSpread);//	RepeatSpread

    QBrush br=brush();
    br.setColor(nFrontColor); //设置前景色即样式颜色

    switch(nPATTERN)
    {
    case 0:br.setStyle(Qt::NoBrush);break;
    case 1:br.setColor(nBackColor);br.setStyle(Qt::SolidPattern);break;
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
        gradient.setStart(nrect.x(),nrect.y()+nrect.height());
        gradient.setColorAt(0,nFrontColor );
        gradient.setColorAt(1,nBackColor );
        break;
    case 3: //横向对称过度
        gradient.setStart(nrect.x(),nrect.y()+nrect.height());
        gradient.setColorAt(0,nFrontColor );
        gradient.setColorAt(0.5,nBackColor );
        gradient.setColorAt(1,nFrontColor );
        break;
    case 4: //纵向过度
        gradient.setStart(nrect.x()+nrect.width(),nrect.y());
        gradient.setColorAt(0,nFrontColor  );
        gradient.setColorAt(1,nBackColor);
        break;
    case 5: //纵向对称过度
        gradient.setStart(nrect.x()+nrect.width(),nrect.y());
        gradient.setColorAt(0,nFrontColor  );
        gradient.setColorAt(0.5,nBackColor);
        gradient.setColorAt(1,nFrontColor );
        break;
    case 6: //斜上过度
        gradient.setColorAt(0,nFrontColor );
        gradient.setColorAt(1,nBackColor );
        break;
    case 7: //斜上对称过度
        gradient.setColorAt(0,nFrontColor );
        gradient.setColorAt(0.5,nBackColor );
        gradient.setColorAt(1,nFrontColor );
        break;
    case 8: //斜下过度
        gradient.setStart(nrect.x(),nrect.y()+nrect.height());
        gradient.setFinalStop(nrect.x()+nrect.width(),nrect.y());
        gradient.setColorAt(0,nBackColor );
        gradient.setColorAt(1,nFrontColor);
        break;
    case 9: //斜下对称过度
        gradient.setStart(nrect.x(),nrect.y()+nrect.height());
        gradient.setFinalStop(nrect.x()+nrect.width(),nrect.y());
        gradient.setColorAt(0,nFrontColor );
        gradient.setColorAt(0.5,nBackColor );
        gradient.setColorAt(1,nFrontColor );
        break;
    case 10: //右上角辐射
        gradient.setStart(nrect.x()+nrect.width(),nrect.y());
        gradient.setFinalStop(nrect.x(),nrect.y()+nrect.height());
        gradient.setColorAt(0,nBackColor );
        gradient.setColorAt(1,nFrontColor );
        break;
    case 11: //左上角辐射
        gradient.setColorAt(0,nBackColor );
        gradient.setColorAt(1, nFrontColor);
        break;
    case 12: //中心辐射
        Radial.setColorAt(0,nBackColor );
        Radial.setColorAt(1,nFrontColor );
        setBrush(Radial);
        return;
        break;
    case 13: //待操作
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

int QRoundedRect::GetPattern()
{
    return nPatternType;
}

void QRoundedRect::SetLineType(int nTYPE)
{
    nLineType = nTYPE;
    QPen pen = this->pen();
    switch(nLineType)
    {
    case 0:
        pen.setStyle(Qt::NoPen); break;//color.setAlpha(0); break; //设置该颜色的透明度,设置线条透明
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

int QRoundedRect::GetLineType()
{
    return nLineType;
}

void QRoundedRect::SetLineWidth(int nWidth)
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

int QRoundedRect::GetLineWidth()
{
    int width = pen().width();
    if (width == 0)
    {
        width = 1;
    }
    return width;
}

void QRoundedRect::SetLineColor(QColor nColor)
{
    QPen pen = this->pen();
    pen.setColor(nColor);
    setPen(pen);
}

QColor QRoundedRect::GetLineColor()
{
    return pen().color();
}

void QRoundedRect::SetAlpha(int nAlpha)
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

int QRoundedRect::GetAlpha()
{
    return nFrontColor.alpha();
}

void QRoundedRect::SetBackColor(QColor nColor)
{
    nBackColor = nColor;
    SetPattern(nPatternType);
}

QColor QRoundedRect::GetBackColor()
{
    return nBackColor;
}

void QRoundedRect::SetFrontColor(QColor nColor)
{
    nFrontColor = nColor;
    SetPattern(nPatternType);
}

QColor QRoundedRect::GetFrontColor()
{
    return nFrontColor;
}

void QRoundedRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                              QWidget *widget)
{
    //Q_D(QGraphicsPathItem);
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->drawPath(this->path());

    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);
}

void QRoundedRect::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
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
    sqlquery.bindValue(":ePolygonClass",QVariant(4)); //4 代表类型为圆角矩形
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

    sqlquery.bindValue(":nRadius",QVariant(GetxRadius())); //
    sqlquery.bindValue(":eCornerType",QVariant(GetyRadius())); //

    sqlquery.bindValue(":nZvalue",QVariant(zValue()));//层次

    sqlquery.bindValue(":nCollidindId",QVariant(index));//碰撞ID

    bool result = false;
    result = sqlquery.exec();
    qDebug() << "insert RoundedRect table :"<<result;

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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_ROUNDEDRECT));

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
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_ROUNDEDRECT));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert sceneAndItem table :"<<result;
    }
}

QGraphicsItem *QRoundedRect::Clone()
{
    QRoundedRect *pClone = new QRoundedRect();
    if (!pClone)
    {
        return NULL;
    }

    QRectF qrcRect = this->sceneBoundingRect();
    pClone->setPath(RectPath);
    pClone->SetxRadius(this->GetxRadius());
    pClone->SetyRadius(this->GetyRadius());
    pClone->SetBackColor(this->GetBackColor());
    pClone->SetFrontColor(this->GetFrontColor());
    pClone->SetPattern(this->GetPattern());
    pClone->SetLineType(this->GetLineType());
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->SetName(this->GetName());
    pClone->SetLineColor(this->GetLineColor());
    pClone->SetLineWidth(this->GetLineWidth());
    pClone->SetHeight(this->GetHeight());
    pClone->SetWidth(this->GetWidth());
    QPointF pt = pClone->boundingRect().topLeft();
    pClone->setPos(qrcRect.topLeft()-pt);
    pClone->SetAlpha(pClone->GetAlpha());
    pClone->setId(id());

    //pClone->SaveSecurityPro(&(this->sPro));
    return pClone;
}


void QRoundedRect::setRectA(const QRectF &rect)
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

    qHeight = rectA.height();
    qWidth = rectA.width();
    Rpos.setX(rectA.x());
    Rpos.setY(rectA.y());

    QPainterPath path;
    path.addRoundedRect(rectA,xRadius,yRadius,Qt::AbsoluteSize);
    RectPath = path;
    setPath(RectPath);
    SetPattern(nPatternType);
}

QDataStream &operator<<(QDataStream &stream, QRoundedRect *pRoundRectItem)
{
    stream << pRoundRectItem->path();
    stream << pRoundRectItem->qWidth << pRoundRectItem->qHeight;
    stream << pRoundRectItem->xRadius << pRoundRectItem->yRadius;
    stream << pRoundRectItem->pen().color() << pRoundRectItem->pen().width();
    stream << pRoundRectItem->nBackColor << pRoundRectItem->nFrontColor;
    stream << pRoundRectItem->nPatternType << pRoundRectItem->scenePos();
    stream << pRoundRectItem->nLineType;
    stream << pRoundRectItem->GetName();
    stream << pRoundRectItem->isVisible();
    stream << pRoundRectItem->data(GROUP_TYPE_KEY).toInt();
    stream << pRoundRectItem->data(GROUP_DATALIST_KEY).toStringList();
    stream << pRoundRectItem->id();

//    if(pwnd->getProVersion() >= 3257)
//    {
//        pRoundRectItem->save(stream);
//    }
    return stream ;
}

QDataStream &operator>>(QDataStream &stream, QRoundedRect *pRoundRectItem)
{
    QPainterPath rectPath;
    QString name;
    QColor penColor;
    int penWidth;
    QPen  pen;
    QPointF pos;
    int typeKey = 0;
    QStringList dataList;
    bool bVisible = true;

    stream >> rectPath;
    stream >> pRoundRectItem->qWidth >> pRoundRectItem->qHeight;
    stream >> pRoundRectItem->xRadius >> pRoundRectItem->yRadius;
    stream >> penColor >> penWidth;
    stream >> pRoundRectItem->nBackColor >> pRoundRectItem->nFrontColor;
    stream >> pRoundRectItem->nPatternType >> pos >> pRoundRectItem->nLineType;
    stream >> name >> bVisible >> typeKey >> dataList;

//    if(pwnd->getProVersion() >= 3257)
//    {
//        pRoundRectItem->load(stream);
//    }
    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }

    pen.setColor(penColor);
    pen.setWidth(penWidth);

    pRoundRectItem->setPath(rectPath);
//    pRoundRectItem->SetWidth(pRoundRectItem->qWidth);
//    pRoundRectItem->SetHeight(pRoundRectItem->qHeight);
//    pRoundRectItem->SetxRadius(pRoundRectItem->xRadius);
//    pRoundRectItem->SetyRadius(pRoundRectItem->yRadius);
    pRoundRectItem->setPen(pen);
    pRoundRectItem->SetPattern(pRoundRectItem->nPatternType);
    pRoundRectItem->setPos(pos);
    pRoundRectItem->SetLineType(pRoundRectItem->nLineType);
    pRoundRectItem->SetName(name);
    pRoundRectItem->setVisible(bVisible);
    pRoundRectItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pRoundRectItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pRoundRectItem->setId(id);
    return stream ;
}

