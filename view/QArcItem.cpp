/************************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2010
 *
 * Description: Implementation of QArcItem class.
 *
 * Functions:
 *
 * Modification Log:
 * Date             Name             Description Of Change
 * 2010-10-30       zqh              Creation.
 * 2011-05-05       Bruce nie        Update for resize functiones.
 ***********************************************************************/
#include "QArcItem.h"
#include <QBrush>
#include <QPen>
#include "Frame/mainwindow.h"
extern  MainWindow *pwnd;

QArcItem::QArcItem()
{
    m_dStartAngle = 45;     //起始角度
    m_dSpanAngle = 90;       //跨度

    nBackColor = QColor(255,255,255);    //初始化背景颜色
    nFrontColor = QColor(0,0,0);   //初始化前景色
    nPatternType = 1;              //样式类初始化为纯色
    nLineType = 1;

    QRectF rc(0, 0, 100, 100);
    this->m_qrcEllipseBndRect = rc;
    this->refreshArc();

    setFlag(QGraphicsItem::ItemIsSelectable, true); //设置组合图形可选
    setFlag(QGraphicsItem::ItemIsMovable, true);
    QBrush br(Qt::SolidPattern);
    br.setColor(QColor(255,0,0));
    this->setBrush(br);
}

void QArcItem::SetStartAngle(qreal qStartAngle) //设置起始角度
{
    m_dStartAngle = qStartAngle;
    refreshArc();
}

qreal QArcItem::GetStartAngle()
{
    return m_dStartAngle;
}

void QArcItem::SetSpanAngle(qreal qSpanAngle) //设置跨度
{
    m_dSpanAngle = qSpanAngle;
    refreshArc();
}

qreal QArcItem::GetSpanAngle()
{
    return m_dSpanAngle;
}

void QArcItem::SetWidth(qreal Width)
{
    this->m_qrcEllipseBndRect.setWidth(Width);
    refreshArc();
}

qreal QArcItem::GetWidth()
{
    return (this->m_qrcEllipseBndRect.width());
}

void QArcItem::SetHeight(qreal Height)
{
    this->m_qrcEllipseBndRect.setHeight(Height);
    refreshArc();
}

qreal QArcItem::GetHeight()
{
    return (this->m_qrcEllipseBndRect.height());
}

void QArcItem::SetName(QString qstr)
{
    setData(GROUP_NAME_KEY,QVariant(qstr));
}

QString QArcItem::GetName()
{
    return data(GROUP_NAME_KEY).toString();
}

void QArcItem::SetPattern(int nPATTERN)
{
    nPatternType = nPATTERN; //样式类型
    //QRectF nrect(0,0,qWidth,qHeight);
    QRectF nrect = this->m_qrcEllipseBndRect;
    QLinearGradient gradient(nrect.topLeft(),nrect.bottomRight());
    QRadialGradient Radial(nrect.center(),nrect.width()/2,nrect.center());
    gradient.setSpread(QGradient::PadSpread);//	RepeatSpread

    QBrush br=brush();
    br.setColor(nFrontColor); //设置前景色即样式颜色

    switch(nPATTERN)
    {
//    case 0:br.setStyle(Qt::NoBrush);break;
//    case 1:br.setColor(nBackColor);br.setStyle(Qt::SolidPattern);break;
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
    case 0:br.setStyle(Qt::NoBrush);break;//透明
    case 1:br.setColor(nBackColor);br.setStyle(Qt::SolidPattern);break;//纯色

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

int QArcItem::GetPattern()
{
    return nPatternType;
}

void QArcItem::SetLineType(int nTYPE)
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

int QArcItem::GetLineType()
{
    return nLineType;
}

void QArcItem::SetLineWidth(int nWidth)
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

int QArcItem::GetLineWidth()
{
    int width = pen().width();
    if (width == 0)
    {
        width = 1;
    }
    return width;
}

void QArcItem::SetLineColor(QColor nColor)
{
    QPen pen = this->pen();
    pen.setColor(nColor);
    setPen(pen);
}

QColor QArcItem::GetLineColor()
{
    return pen().color();
}

void QArcItem::SetAlpha(int nAlpha)
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

int QArcItem::GetAlpha()
{
    return nFrontColor.alpha();
}

void QArcItem::SetBackColor(QColor nColor)
{
    nBackColor = nColor;
    SetPattern(nPatternType);
}

QColor QArcItem::GetBackColor()
{
    return nBackColor;
}

void QArcItem::SetFrontColor(QColor nColor)
{
    nFrontColor = nColor;
    SetPattern(nPatternType);
}

QColor QArcItem::GetFrontColor()
{
    return nFrontColor;
}

void QArcItem::refreshArc()
{
    QPointF qpMid;
    qpMid.rx() = (m_qrcEllipseBndRect.topLeft().x() + m_qrcEllipseBndRect.bottomRight().x()) / 2;
    qpMid.ry() = (m_qrcEllipseBndRect.topLeft().y() + m_qrcEllipseBndRect.bottomRight().y()) / 2;
    QPainterPath path;
    path.moveTo(qpMid);
    path.arcTo(m_qrcEllipseBndRect, m_dStartAngle, m_dSpanAngle);
    path.lineTo(qpMid);
    m_ArcPath = path;
    setPath(m_ArcPath);
    SetPattern(nPatternType);
}

void QArcItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
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
    sqlquery.bindValue(":ePolygonClass",QVariant(6)); //6 代表类型为扇形
    sqlquery.bindValue(":eLineType",QVariant(nLineType+1));// 线形
    sqlquery.bindValue(":nLineWidth",QVariant(GetLineWidth()));// 线宽
    sqlquery.bindValue(":nLineColor",QVariant(ColorToInt(GetLineColor()))); //颜色
    sqlquery.bindValue(":eStyle",QVariant(GetPattern()+1));// 样式
    sqlquery.bindValue(":nBackColor",QVariant(ColorToInt(GetBackColor()))); //背景色
    sqlquery.bindValue(":nForeColor",QVariant(ColorToInt(GetFrontColor()))); //前景色
    sqlquery.bindValue(":nAlpha",QVariant(GetAlpha()));// 透明度

    QRect rect = this->sceneBoundingRect().toRect();

    sqlquery.bindValue(":nWidth",QVariant(GetStartAngle())); //起始角度
    sqlquery.bindValue(":nHeight",QVariant(GetSpanAngle())); //角度

    sqlquery.bindValue(":nPointX",QVariant(rect.x())); //X
    sqlquery.bindValue(":nPointY",QVariant(rect.y())); //Y
    sqlquery.bindValue(":nRadius",QVariant(rect.height()/2)); //半径

    sqlquery.bindValue(":nZvalue",QVariant(zValue()));//层次

    sqlquery.bindValue(":nCollidindId",QVariant(index));//碰撞ID

    bool result = false;
    result = sqlquery.exec();
    qDebug() << "insert ArcItem table :"<<result;

    SamDrawScene *pScene = dynamic_cast<SamDrawScene *>(scene());
    if(pScene && pScene->nIsSceneOrWindow == 2)
    {
        //是自定义键盘的item
        //先新建键盘——item关联表 item表在派生类中创建

        //QSqlQuery sqlquery(db);

        sqlquery.prepare("INSERT INTO kbAndItem(nKeyBoardId , nItemId ,nItemTableType ) "
                         "VALUES (:nKeyBoardId ,:nItemId ,:nItemTableType)");
        sqlquery.bindValue(":nKeyBoardId",QVariant(nSceneId));
        sqlquery.bindValue(":nItemId",QVariant(count));
        sqlquery.bindValue(":nId",QVariant(id()));// 控件ID
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_ARC));

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

        sqlquery.prepare("INSERT INTO sceneAndItem(nSceneId,nId,nItemId,nItemTableType)"
                         "VALUES(:nSceneId,:nId,:nItemId,:nItemTableType)");
        sqlquery.bindValue(":nSceneId",QVariant(nSceneId));
        sqlquery.bindValue(":nItemId",QVariant(count));
        sqlquery.bindValue(":nId",QVariant(id()));// 控件ID
        //int t = this->GroupType();
        sqlquery.bindValue(":nItemTableType",QVariant((int)SAM_DRAW_OBJECT_ARC));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert sceneAndItem table :"<<result;
    }
}
QGraphicsItem *QArcItem::Clone()
{
    QArcItem *pClone = new QArcItem();
    if (!pClone)
    {
        return NULL;
    }

    QRectF qrcRect = this->sceneBoundingRect();
    pClone->setPath(this->m_ArcPath);
//    pClone->qHeight = this->qHeight;
//    pClone->qWidth = this->qWidth;
    pClone->m_qrcEllipseBndRect = this->m_qrcEllipseBndRect;
    pClone->SetStartAngle(this->GetStartAngle());
    pClone->SetSpanAngle(this->GetSpanAngle());
    pClone->SetBackColor(this->GetBackColor());
    pClone->SetFrontColor(this->GetFrontColor());
    pClone->SetPattern(this->GetPattern());
    pClone->SetLineType(this->GetLineType());
    pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
    pClone->SetName(this->GetName());
    pClone->SetLineColor(this->GetLineColor());
    pClone->SetLineWidth(this->GetLineWidth());
    QPointF pt = pClone->boundingRect().topLeft();
    pClone->setPos(qrcRect.topLeft()-pt);
    pClone->SetAlpha(this->GetAlpha());
    pClone->setId(id());

    //pClone->SaveSecurityPro(&(this->sPro));
    return pClone;
}

/**********************************************************************
 * Function: update the ellipse bonding rect which this arc in.
 * Parameters: new bonding rect
 * Return: none
 **********************************************************************/
void QArcItem::setRectA(const QRectF &rect)
{
    QRectF rectA = rect;
//    qreal dDelta = 0.0;

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

    this->m_qrcEllipseBndRect = rectA;
    refreshArc();
}

/**********************************************************************
 * Function: get handle count, inherit from SamDrawItemBase
 * Parameters: none
 * Return: handle count
 **********************************************************************/
int QArcItem::getHandleCount() const
{
    return (int)ARC_ITEM_HANDLE_COUNT;
}

/**********************************************************************
 * Function: get handle point
 * Parameters: handle id, bound rect
 * Return: none
 **********************************************************************/
QPointF QArcItem::getHandle(int iHandle, QRectF &qrcBondingRect) const
{
    QPointF qpPoint;

    if (iHandle > 8)
    {
        QList<QPolygonF> polygonfs = m_ArcPath.toSubpathPolygons();
        int iSize = polygonfs.size();
        if (iSize <= 0 || iSize > 1)
        {
            return qpPoint;
        }
        QPolygonF polygonf = polygonfs.at(0);
        int j = polygonf.size();
        if (j <= 1)
        {
            return qpPoint;;
        }

        /*Get the key points*/
        QPointF qpDimCenter;
        qpDimCenter = polygonf.at(0);
        switch (iHandle)
        {
        case 9:
            qpPoint = polygonf.at(1);
            qpPoint.rx() = (qpPoint.x() + qpDimCenter.x()) / 2;
            qpPoint.ry() = (qpPoint.y() + qpDimCenter.y()) / 2;
            break;
        case 10:
            qpPoint = polygonf.at(j - 1);
            qpPoint.rx() = (qpPoint.x() + qpDimCenter.x()) / 2;
            qpPoint.ry() = (qpPoint.y() + qpDimCenter.y()) / 2;
            break;
        default:
            break;
        }

        qpPoint = this->mapToScene(qpPoint);
        qpPoint.rx() = qpPoint.x();
        return qpPoint;
    }
    else
    {
        return SamDrawItemBase::getHandle(iHandle, qrcBondingRect);
    }
}

/*********************************************************************************
 * Function: Get mouse cursor
 * Parameters: handle id (not used)
 * Return: mouse cursor
 ********************************************************************************/
QCursor QArcItem::getHandleCursor(int iHandle) const
{
    if (iHandle > 8)
    {
        QString sMapFile = ":cursor/images/cursor/sizeall.ico";
        QPixmap qmapMap(sMapFile);
        return QCursor(qmapMap);
    }
    else
    {
        return SamDrawItemBase::getHandleCursor(iHandle);
    }
}

#if 0
/**********************************************************************
 * Function: move arc handle to a new place.
 * Parameters: none
 * Return: handle id, point, bound rect
 **********************************************************************/
QRectF QArcItem::moveHandleTo(int iDragHandle, QPointF qpLocal, QRectF &qrcBondingRect)
{
    const qreal dDelta = 0.1;
    qreal dDeltaX = 0.0, dDeltaY = 0.0;
    QPointF qpDimCenter, qpEndPoint;

    /*If move handle is 9 or 10 (to expand the arc)*/
    if (iDragHandle > 8)
    {
        QRectF rect;

        QList<QPolygonF> polygonfs = m_ArcPath.toSubpathPolygons();
        int iSize = polygonfs.size();
        if (iSize <= 0 || iSize > 1)
        {
            return rect;
        }
        QPolygonF polygonf = polygonfs.at(0);
        int j = polygonf.size();
        if (j <= 1)
        {
            return rect;
        }
        qpDimCenter = polygonf.at(0);
        qpDimCenter = this->mapToScene(qpDimCenter);

        qpEndPoint = polygonf.at(j - 1);
        qpEndPoint = this->mapToScene(qpEndPoint);

        /*Reset the arc when draged the related handle*/
        switch (iDragHandle)
        {
        /*The start angle side handle*/
        case 9:
            {
                dDeltaX = qpLocal.x() - qpDimCenter.x();
                if (qFabs(dDeltaX) > dDelta)
                {
                    dDeltaY = qpDimCenter.y() - qpLocal.y();
                    qreal dAngle = getAngle(dDeltaX, dDeltaY);

                    dDeltaX = qpEndPoint.x() - qpDimCenter.x();
                    dDeltaY = qpDimCenter.y() - qpEndPoint.y();
                    qreal dEndAngle = getAngle(dDeltaX, dDeltaY);
                    qreal dStartAngle = 0.0, dSpanAngle = 0.0;

                    /*Get the start angle and span angle*/
                    if (this->GetSpanAngle() <= 0)
                    {
                        dStartAngle = dAngle;
                        dSpanAngle = PI_ANGLE - (dStartAngle - dEndAngle);
                    }
                    else if (this->GetSpanAngle() > 0)
                    {
                        /*Get the new span angle*/
                        if (dAngle > dEndAngle)
                        {
                            qreal dAngleTemp = -(PI_ANGLE - dAngle);
                            dSpanAngle = this->GetSpanAngle() - dAngleTemp;
                            dStartAngle = dAngle;
                        }
                        else
                        {
                            dSpanAngle = dEndAngle - dAngle;
                            dStartAngle = dAngle;
                        }
                    }

                    /*Set start angle and span angle*/
//                    this->SetStartAngle(dStartAngle);
//                    this->SetSpanAngle(dSpanAngle);

//                    this->m_dSpanAngle = dSpanAngle;
                    this->m_dSpanAngle = this->m_dSpanAngle - (dStartAngle - this->m_dStartAngle);
                    this->m_dStartAngle = dStartAngle;
                    refreshArc();
                }
            }
            break;
        /*The end angle side handle*/
        case 10:
            {
                if (qFabs(qpLocal.x() - qpDimCenter.x()) > dDelta)
                {
                    dDeltaX = qpLocal.x() - qpDimCenter.x();
                    dDeltaY = qpDimCenter.y() - qpLocal.y();
                    qreal dAngle = getAngle(dDeltaX, dDeltaY);
                    qreal dSpanAngle = 0.0;
                    if (this->GetSpanAngle() < 0)
                    {
                        dAngle = PI_ANGLE - dAngle;
                        dSpanAngle = this->m_dStartAngle - dAngle;

                    }
                    else if (this->GetSpanAngle() >= 0)
                    {
                        /*Get the new span angle*/
                        if (dAngle < this->m_dStartAngle)
                        {
                            dSpanAngle = PI_ANGLE - (this->m_dStartAngle - dAngle);
                        }
                        else
                        {
                            dSpanAngle = dAngle - this->m_dStartAngle;
                        }
                    }

                    /*Set span angle*/
                    this->SetSpanAngle(dSpanAngle);
                }
            }
            break;
        default :
            break;
        }

        return rect;
    }
    else
    {
        return SamDrawItemBase::moveHandleTo(iDragHandle, qpLocal, qrcBondingRect);
    }
}
#endif
/**********************************************************************
 * Function: move arc handle to a new place.
 * Parameters: none
 * Return: handle id, point, bound rect
 **********************************************************************/
QRectF QArcItem::moveHandleTo(int iDragHandle, QPointF qpLocal, QRectF &qrcBondingRect, bool bFoursquare)
{
    const qreal dDelta = 0.1;
    qreal dDeltaX = 0.0, dDeltaY = 0.0;
    QPointF qpDimCenter, qpEndPoint;

    /*If move handle is 9 or 10 (to expand the arc)*/
    if (iDragHandle > 8)
    {
        QRectF rect;

        QList<QPolygonF> polygonfs = m_ArcPath.toSubpathPolygons();
        int iSize = polygonfs.size();
        if (iSize <= 0 || iSize > 1)
        {
            return rect;
        }
        QPolygonF polygonf = polygonfs.at(0);
        int j = polygonf.size();
        if (j <= 1)
        {
            return rect;
        }
        qpDimCenter = polygonf.at(0);
        qpDimCenter = this->mapToScene(qpDimCenter);

        qpEndPoint = polygonf.at(j - 1);
        qpEndPoint = this->mapToScene(qpEndPoint);

        /*Reset the arc when draged the related handle*/
        switch (iDragHandle)
        {
        /*The start angle side handle*/
        case 9:
            {
                dDeltaX = qpLocal.x() - qpDimCenter.x();
                if (qFabs(dDeltaX) > dDelta)
                {
                    dDeltaY = qpDimCenter.y() - qpLocal.y();
                    qreal dAngle = getAngle(dDeltaX, dDeltaY);

                    qreal dStartAngle = 0.0, dSpanAngle = 0.0, dDeltaStartAngle = 0.0;

                    /*Get the start angle and span angle*/
                    dStartAngle = dAngle;
                    dDeltaStartAngle = dStartAngle - this->m_dStartAngle;
                    if (dDeltaStartAngle < 0) dDeltaStartAngle += PI_ANGLE;

                    dSpanAngle = this->m_dSpanAngle - dDeltaStartAngle;
                    if (dSpanAngle < 0) dSpanAngle += PI_ANGLE;

                    /*Set start angle and span angle, refresh arc.*/
                    this->m_dSpanAngle = dSpanAngle;
                    this->m_dStartAngle = dStartAngle;
                    refreshArc();
                }
            }
            break;
        /*The end angle side handle*/
        case 10:
            {
                if (qFabs(qpLocal.x() - qpDimCenter.x()) > dDelta)
                {
                    dDeltaX = qpLocal.x() - qpDimCenter.x();
                    dDeltaY = qpDimCenter.y() - qpLocal.y();
                    qreal dAngle = getAngle(dDeltaX, dDeltaY);
                    qreal dSpanAngle = 0.0;
                    if (this->GetSpanAngle() < 0)
                    {
                        dAngle = PI_ANGLE - dAngle;
                        dSpanAngle = this->m_dStartAngle - dAngle;

                    }
                    else if (this->GetSpanAngle() >= 0)
                    {
                        /*Get the new span angle*/
                        if (dAngle < this->m_dStartAngle)
                        {
                            dSpanAngle = PI_ANGLE - (this->m_dStartAngle - dAngle);
                        }
                        else
                        {
                            dSpanAngle = dAngle - this->m_dStartAngle;
                        }
                    }

                    /*Set span angle*/
                    this->SetSpanAngle(dSpanAngle);
                }
            }
            break;
        default :
            break;
        }

        return rect;
    }
    else
    {
        return SamDrawItemBase::moveHandleTo(iDragHandle, qpLocal, qrcBondingRect, bFoursquare);
    }
}

/**********************************************************************
 * Function: get the angle from the deltax and deltay.
 * Parameters: deltax, deltay
 * Return: angle
 **********************************************************************/
qreal QArcItem::getAngle(qreal dDeltaX, qreal dDeltaY) const
{
    qreal dAngle = 0.0, dK = 0.0;
    const qreal dDelta = 0.01;

    /*dDeltaX --> 0*/
    if (dDeltaX > -dDelta && dDeltaX < dDelta)
    {
        if (dDeltaY > 0)
        {
            dAngle = 90;
        }
        else if (dDeltaY < 0)
        {
            dAngle = 270;
        }
    }
    /*dDeltaY --> 0*/
    else if (dDeltaY > -dDelta && dDeltaY < dDelta)
    {
        if (dDeltaX > 0)
        {
            dAngle = 0;
        }
        else if (dDeltaX < 0)
        {
            dAngle = 180;
        }
    }
    else
    {
        dK = dDeltaY / dDeltaX;
        dAngle = qAtan(dK);
        dAngle *= ((PI_ANGLE * 0.5) / M_PI);

        /*Quadrant 2*/
        if (dDeltaY > 0 && dDeltaX < 0)
        {
            dAngle += 180;
        }
        /*Quadrant 3*/
        else if (dDeltaY < 0 && dDeltaX < 0)
        {
            dAngle = 270 - (90 - dAngle);
        }
        /*Quadrant 4*/
        else if (dDeltaY < 0 && dDeltaX > 0)
        {
            dAngle += 360;
        }
    }

    return dAngle;
}

void QArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                              QWidget *widget)
{
    Q_UNUSED(widget);
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->drawPath(this->path());

    if (option->state & QStyle::State_Selected)
        qt_graphicsItem_highlightSelected(this, painter, option);
}
QDataStream &operator<<(QDataStream &stream, QArcItem *pArcItem)
{
    stream << pArcItem->path();
    //stream << pArcItem->GetWidth() << pArcItem->GetHeight();
    stream << pArcItem->getEllipseRect();
    stream << pArcItem->GetStartAngle() << pArcItem->GetSpanAngle();
    stream << pArcItem->pen().color() << pArcItem->pen().width();
    stream << pArcItem->nBackColor << pArcItem->nFrontColor;
    stream << pArcItem->nPatternType << pArcItem->scenePos();
    stream << pArcItem->nLineType << pArcItem->GetAlpha();
    stream << pArcItem->GetName();
    stream << pArcItem->isVisible();
    stream << pArcItem->data(GROUP_TYPE_KEY).toInt();
    stream << pArcItem->data(GROUP_DATALIST_KEY).toStringList();
//    if(pwnd->getProVersion() >= 3257)
//    {
//        pArcItem->save(stream);
//    }
    stream << pArcItem->id();
    return stream ;
}

QDataStream &operator>>(QDataStream &stream, QArcItem *pArcItem)
{
    QPainterPath path;
    QColor lineColor;
    int lineWidth,patternType,alpha;
    qreal startAngle,spanAngle;
    QPointF scenePos;
    QString name ;
    int typeKey = 0;
    QStringList dataList;
    QRectF qrcRect;
    bool bVisible = true;

    stream >> path;
    //stream >> pArcItem->qWidth >> pArcItem->qHeight;
    stream >> qrcRect;
    stream >> startAngle >> spanAngle;
    stream >> lineColor >> lineWidth;
    stream >> pArcItem->nBackColor >> pArcItem->nFrontColor;
    stream >> patternType >> scenePos;
    stream >> pArcItem->nLineType >> alpha;
    stream >> name >> bVisible >> typeKey >> dataList;
//    if(pwnd->getProVersion() >= 3257)
//    {
//        pArcItem->load(stream);
//    }
    int id = -1;
    if(pwnd->getProVersion() >= 3456)
    {
        stream >> id;
    }

    pArcItem->setRectA(qrcRect);
    pArcItem->setPath(path);
    pArcItem->SetSpanAngle(spanAngle);
    pArcItem->SetStartAngle(startAngle);
    pArcItem->SetLineColor(lineColor);
    pArcItem->SetLineWidth(lineWidth);
    pArcItem->SetLineType(pArcItem->nLineType);
    pArcItem->SetAlpha(alpha);
    pArcItem->setPos(scenePos);
    pArcItem->SetName(name);
    pArcItem->setVisible(bVisible);
    pArcItem->SetPattern(patternType);
    pArcItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    pArcItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    pArcItem->setId(id);
    return stream ;
}
