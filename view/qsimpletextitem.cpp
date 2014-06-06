#include "qsimpletextitem.h"
#include "QFont"
#include <QTextBlock>
#include <QTextBlockFormat>
#include <QTextDocument>
#include <QRect>
#include <QString>
#include <QFontMetrics>
#include <QPainter>
#include "headfile/global_types.h"


QSimpleTextItem::QSimpleTextItem()
{
    sTEXT = "Text";                       //默认文本

    m_rect.setRect(0,0,100,100);                         //给背景矩形赋初始值
    InitParameters();
}

QSimpleTextItem::QSimpleTextItem(QString sText)
{
    sTEXT = sText;                       //默认文本
    m_rect.setRect(0,0,100,100);         //给背景矩形赋初始值
    InitParameters();
}


/*****************************************************************************
  函数名称：QSimpleTextItem(QRectF Rect, QString sText)
  函数意义：带参数构造函数
  参数含义：Rect文本的背景矩形框大小，sText初始文本
*****************************************************************************/
QSimpleTextItem::QSimpleTextItem(QRectF Rect, QString sText)
{
    sTEXT = sText;                        //默认文本
    m_rect = Rect;                        //给背景矩形赋初始值
    InitParameters();
}

void QSimpleTextItem::InitParameters()
{
    m_FontColor = QColor(0,0,0);          //字体颜色
    m_RectBackColor=QColor(255,0,0);          //矩形框的背景色
    m_RectFrontColor=QColor(0,0,255);   //矩形框的前景色
    m_Alianment = 5;                      //文本的对齐方式,默认是剧中对齐
    nPtternType = 0;                      //选择样式的类型
    m_RectOutLine = true;                 //背景矩形框是否有边线
    m_RectOutLineColor = Qt::blue;         //背景矩形框色颜色
    m_LineInterval = 0;                   //行距

    //add by tanghaiguo
    this->SetTextAlign(m_Alianment);
    this->SetPattern(nPtternType);

    m_font.setFamily("Droid Sans Fallback");//System
    m_font.setPointSize(9);
    m_font.setBold(false);
    m_font.setItalic(false);
    m_font.setUnderline(false);   //字体是否有下划线
    m_font.setLetterSpacing(QFont::AbsoluteSpacing,0); //设置字体的字距

    this->setFlag(QGraphicsItem::ItemIsMovable,true);
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);

    bFitSize = false;
    ///for test
//    this->SetAlpha(0);
}

void QSimpleTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QString sContent = "" ; //临时存文本内容,改变行距时用
    QString sStr = "\n";
    int i=0;

    sContent = sTEXT;

    //设置行距
    for(i = 0; i < m_LineInterval;i++)
    {
        sStr= sStr + "\n";
    }
    sContent.replace("\n",sStr);

    //设置矩形的背景色
    if(nPtternType >= 0 && nPtternType <15)        //设置为一般Qt提供的样式
        painter->setBrush(m_brush);
    else if(nPtternType >= 15 && nPtternType <= 24) //设置为线性过度色
        painter->setBrush(m_gradient);
    else if(nPtternType >= 25 && nPtternType <= 26) //设置为幅角过度色
        painter->setBrush(m_radial);

    if(m_RectOutLine) //设置文本有边框
    {
        QPen npen(Qt::SolidLine);
        npen.setColor(m_RectOutLineColor);
        painter->setPen(npen);
    }
    else             //设置文本没有边框
    {
        painter->setPen(Qt::NoPen);
    }
    painter->drawRect(m_rect);          //画文本的背景矩形框

    painter->setFont(m_font);
    painter->setPen(m_FontColor);

    if(bFitSize)
    {
        QFontMetrics metrics(m_font);
        int lineWidth = 0;
        int width = metrics.size(Qt::TextDontClip,sContent).width();
        int height = metrics.size(Qt::TextDontClip,sContent).height();

        qreal xScale = (qreal)m_rect.width() / (qreal)width;
        qreal yScale = (qreal)m_rect.height() / (qreal)height;

        QPointF pos = boundingRect().topLeft();
        QPointF pt = QPointF(m_rect.topLeft());
        painter->translate(pt);


        painter->scale(xScale,yScale);

        QRectF rc = QRectF(0,0,m_rect.width(),m_rect.height());
        painter->setPen(m_FontColor);       //可以设置字体颜色和矩形框的边框色
        painter->drawText(rc,sContent); //在矩形框中画文本
    }
    else
    {
        painter->drawText(m_rect, AlianmentFlag, sContent);
    }


}

void QSimpleTextItem::SetName(QString sName)
{
   // int ntype=type();
    setData(GROUP_NAME_KEY,QVariant(sName));
}

QString QSimpleTextItem::GetName()
{
    //int ntype=type();
    QString sName="";
    sName=data(GROUP_NAME_KEY).toString();
    return sName;
}

void QSimpleTextItem::SetID(int nID)
{
   // int ntype=type();
    setData(ITEM_ID_KEY,QVariant(nID));
}

int QSimpleTextItem::GetID()
{
   // int ntype=type();
    return data(ITEM_ID_KEY).toInt();
}

void QSimpleTextItem::SetText(QString sText) //设置文本
{
    sTEXT= sText;
    this->update(m_rect);
}

QString QSimpleTextItem::GetText()  //获得文本
{
    return sTEXT;
}

void QSimpleTextItem::SetFontColor(QColor color) //设置字体颜色
{
    m_FontColor = color;
    this->update(m_rect);
}

QColor QSimpleTextItem::GetFontColor() //获得字体颜色
{
    return m_FontColor;
}

void QSimpleTextItem::SetRectBackColor(QColor color) //设置背景矩形框的背景色
{
    m_RectBackColor = color;
    SetPattern(nPtternType);
    this->update(m_rect);
}

QColor QSimpleTextItem::GetRectBackColor() //获得背景矩形框的背景色
{
    return m_RectBackColor;
}

void QSimpleTextItem::SetRectFrontColor(QColor color) //设置背景矩形框的前景色
{
    m_RectFrontColor = color;
    SetPattern(nPtternType);
    this->update(m_rect);
}

QColor QSimpleTextItem::GetRectFrontColor()          //获得背景矩形框的前景色
{
    return m_RectFrontColor;
}

void QSimpleTextItem::SetAlpha(int nAlpha) //设置透明度 nAlpha 0-255，值越小，越透明
{
    m_RectFrontColor.setAlpha(nAlpha);
    m_RectBackColor.setAlpha(nAlpha);
    this->SetPattern(nPtternType);
    this->update(m_rect);
}

int QSimpleTextItem::GetAlpha() //获得背景色的透明度
{
    return m_RectFrontColor.alpha();
}

void QSimpleTextItem::SetFontSize(int nFontSize) //设置字体大小
{
    m_font.setPointSize(nFontSize);
    this->update(m_rect);
}

int QSimpleTextItem::GetFontSize() //获得字体大小
{
    return m_font.pointSize();
}

void QSimpleTextItem::SetFontName(QString sName) //设置字体名称
{
    m_font.setFamily(sName);
    this->update(m_rect);
}

QString QSimpleTextItem::GetFontName() //获得字体名称
{
    return m_font.family();
}

void QSimpleTextItem::SetFontBold(bool nFlag) //true设置字体为粗体否则不设置
{
    m_font.setBold(nFlag);
    this->update(m_rect);
}

bool QSimpleTextItem::GetFontBold() //获得字体是否是粗体
{
    return m_font.bold();
}

void QSimpleTextItem::SetFontItalic(bool nFlag) //true设置字体为斜体否则不设置
{
    m_font.setItalic(nFlag);
    this->update(m_rect);
}

bool QSimpleTextItem::GetFontItalic() //获得字体是否是斜体
{
    return m_font.italic();
}

void QSimpleTextItem::SetFontUnderLine(bool nFlag) //true设置字体是否有下划线
{
    m_font.setUnderline(nFlag);
    this->update(m_rect);
}

bool QSimpleTextItem::GetFontUnderLine() //获得字体是否有下划线
{
    return m_font.underline();
}

void QSimpleTextItem::SetFontWordInterval(int nInterval) //设置文本的字距
{
    m_font.setLetterSpacing(QFont::AbsoluteSpacing,nInterval);
    this->update(m_rect);
}

int QSimpleTextItem::GetFontWordInterval() //获得文本的字距
{
    return m_font.letterSpacing();
}

/*****************************************************************************
  函数名称：SetTextAlign(int nAlignType)
  函数意义：设置文本的对齐方式
  参数含义：nAlignType
  nAlignType=1:左上角对齐
  nAlignType=2:上边对齐
  nAlignType=3:右上角对齐
  nAlignType=4:左边对齐
  nAlignType=5:剧中对齐
  nAlignType=6:右边对齐
  nAlignType=7:左下角对齐
  nAlignType=8:下边对齐
  nAlignType=9:右下角对齐
*****************************************************************************/
void QSimpleTextItem::SetTextAlign(int nAlignType)
{
    m_Alianment = nAlignType;
    switch(m_Alianment)
    {
        case 1: AlianmentFlag = Qt::AlignLeft | Qt::AlignTop; break;
        case 2: AlianmentFlag = Qt::AlignTop | Qt::AlignHCenter; break;
        case 3: AlianmentFlag = Qt::AlignRight | Qt::AlignTop; break;

        case 4: AlianmentFlag = Qt::AlignLeft | Qt::AlignVCenter; break;
        case 5: AlianmentFlag = Qt::AlignCenter; break;
        case 6: AlianmentFlag = Qt::AlignRight | Qt::AlignCenter; break;

        case 7: AlianmentFlag = Qt::AlignLeft | Qt::AlignBottom; break;
        case 8: AlianmentFlag = Qt::AlignBottom | Qt::AlignHCenter; break;
        case 9: AlianmentFlag = Qt::AlignRight | Qt::AlignBottom; break;
    }
    this->update(m_rect);
}

int QSimpleTextItem::GetTextAlign() //获得文本的对齐方式
{
    return m_Alianment;
}

void QSimpleTextItem::SetPattern(int nType) //设置背景矩形的样式
{
    nPtternType = nType;
    m_gradient.setStart(m_rect.topLeft());
    m_gradient.setFinalStop(m_rect.bottomRight());
    m_gradient.setSpread(QGradient::PadSpread);

    m_radial.setCenter(m_rect.center());
    m_radial.setRadius(m_rect.width()*(0.5));
    m_radial.setFocalPoint(m_rect.center());

    m_brush.setColor(m_RectFrontColor); //设置前景色即样式颜色

    switch(nPtternType)
    {
        case 0:m_brush.setStyle(Qt::NoBrush);break;
        case 1:m_brush.setColor(m_RectBackColor);m_brush.setStyle(Qt::SolidPattern);break;
//        case 2:m_brush.setStyle(Qt::Dense1Pattern);break;
//        case 3:m_brush.setStyle(Qt::Dense2Pattern);break;
//        case 4:m_brush.setStyle(Qt::Dense3Pattern);break;
//        case 5:m_brush.setStyle(Qt::Dense4Pattern);break;
//        case 6:m_brush.setStyle(Qt::Dense5Pattern);break;
//        case 7:m_brush.setStyle(Qt::Dense6Pattern);break;
//        case 8:m_brush.setStyle(Qt::Dense7Pattern);break;

//        case 9:m_brush.setStyle(Qt::HorPattern);break;
//        case 10:m_brush.setStyle(Qt::VerPattern);break;
//        case 11:m_brush.setStyle(Qt::CrossPattern);break;

//        case 12:m_brush.setStyle(Qt::BDiagPattern);break;
//        case 13:m_brush.setStyle(Qt::FDiagPattern);break;
//        case 14:m_brush.setStyle(Qt::DiagCrossPattern);break;

        case 2: //横向过度
            m_gradient.setStart(m_rect.bottomLeft());
            m_gradient.setColorAt(0,m_RectFrontColor );
            m_gradient.setColorAt(1,m_RectBackColor );
            break;
        case 3: //横向对称过度
            m_gradient.setStart(m_rect.bottomLeft());
            m_gradient.setColorAt(0,m_RectFrontColor );
            m_gradient.setColorAt(0.5,m_RectBackColor );
            m_gradient.setColorAt(1,m_RectFrontColor );
            break;
        case 4: //纵向过度
            m_gradient.setStart(m_rect.topRight());
            m_gradient.setColorAt(0,m_RectFrontColor  );
            m_gradient.setColorAt(1,m_RectBackColor);
            break;
        case 5: //纵向对称过度
            m_gradient.setStart(m_rect.topRight());
            m_gradient.setColorAt(0,m_RectFrontColor  );
            m_gradient.setColorAt(0.5,m_RectBackColor);
            m_gradient.setColorAt(1,m_RectFrontColor );
            break;
        case 6: //斜上过度
            m_gradient.setColorAt(0,m_RectFrontColor );
            m_gradient.setColorAt(1,m_RectBackColor );
            break;
        case 7: //斜上对称过度
            m_gradient.setColorAt(0,m_RectFrontColor );
            m_gradient.setColorAt(0.5,m_RectBackColor );
            m_gradient.setColorAt(1,m_RectFrontColor );
            break;
        case 8: //斜下过度
            m_gradient.setStart(m_rect.bottomLeft());
            m_gradient.setFinalStop(m_rect.topRight());
            m_gradient.setColorAt(0,m_RectBackColor );
            m_gradient.setColorAt(1,m_RectFrontColor);
            break;
        case 9: //斜下对称过度
            m_gradient.setStart(m_rect.bottomLeft());
            m_gradient.setFinalStop(m_rect.topRight());
            m_gradient.setColorAt(0,m_RectFrontColor );
            m_gradient.setColorAt(0.5,m_RectBackColor );
            m_gradient.setColorAt(1,m_RectFrontColor );
            break;
        case 10: //右上角辐射

            m_gradient.setStart(m_rect.topRight());
            m_gradient.setFinalStop(m_rect.bottomLeft());
            m_gradient.setColorAt(0,m_RectBackColor );
            m_gradient.setColorAt(1,m_RectFrontColor );
            break;
        case 11: //左上角辐射
            m_gradient.setColorAt(0,m_RectBackColor );
            m_gradient.setColorAt(1, m_RectFrontColor);
            break;
        case 12: //中心辐射
            m_radial.setColorAt(0,m_RectBackColor );
            m_radial.setColorAt(1,m_RectFrontColor );
            break;
        case 13: //待操作
            m_radial.setFocalPoint(m_rect.x(),m_rect.center().y());
            m_radial.setColorAt(0,m_RectBackColor );
            m_radial.setColorAt(1,m_RectFrontColor );
            break;
        default:
            break;
     }
    this->update(m_rect);
}

int QSimpleTextItem::GetPattern() //获得样式
{
    return nPtternType;
}

/*****************************************************************************
  函数名称：SetRectOutLine(bool nFlag)
  函数意义：设置文本背景矩形是否有边线
  参数含义：nFlag=true表示有边线，nFlag=false表示没有边线
*****************************************************************************/
void QSimpleTextItem::SetRectOutLine(bool nFlag) //设置文本是否有边框
{
    m_RectOutLine = nFlag;
    this->update(m_rect);
}

bool QSimpleTextItem::GetRectOutLine()  //获得文本是否有边框
{
    return m_RectOutLine;
}

void QSimpleTextItem::SetRectOutLineColor(QColor color)//设置文本边框色
{
    m_RectOutLineColor = color;
    this->update(m_rect);
}

QColor QSimpleTextItem::GetRectOutLineColor()  //获得文本的边框色
{
    return m_RectOutLineColor;
}

void QSimpleTextItem::SetLineInterval(int nInterval) //设置行距
{
    m_LineInterval = nInterval;
    this->update(m_rect);
}

int QSimpleTextItem::GetLineInterval() //获得行距
{
    return m_LineInterval;
}

QFont QSimpleTextItem::GetTextFont() //获得字体
{
	return m_font;
}

void QSimpleTextItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{

}

QSimpleTextItem* QSimpleTextItem::Clone()
{
	QSimpleTextItem *pClone = new QSimpleTextItem(this->sceneBoundingRect(),this->GetText());
	//QSimpleTextItem *pClone = new QSimpleTextItem(this->boundingRect(),this->GetText());
	if (!pClone)
	{
		return NULL;
	}

	pClone->SetFontColor(this->GetFontColor());
	pClone->SetRectOutLineColor(this->GetRectOutLineColor());
	pClone->SetRectBackColor(this->GetRectBackColor());
	pClone->SetRectFrontColor(this->GetRectFrontColor());
	pClone->SetFontSize(this->GetFontSize());
	pClone->SetFontName(this->GetFontName());
	pClone->SetFontBold(this->GetFontBold());
	pClone->SetFontItalic(this->GetFontItalic());
	pClone->SetFontUnderLine(this->GetFontUnderLine());
	pClone->SetFontWordInterval(this->GetFontWordInterval());
	pClone->SetRectOutLine(this->GetRectOutLine());
	pClone->SetLineInterval(this->GetLineInterval());
	pClone->setFlag(QGraphicsItem::ItemIsSelectable, true);
	pClone->setFlag(QGraphicsItem::ItemIsMovable, true);
	pClone->SetName(this->GetName());
	pClone->SetText(this->GetText());
        pClone->SetTextAlign(this->GetTextAlign());

        pClone->setVisible(this->isVisible());
        pClone->SetPattern(this->GetPattern());
		pClone->bFitSize = bFitSize;
        pClone->setId(id());

	// pClone->setRect(this->sceneBoundingRect());
	return pClone;
}

void QSimpleTextItem::SetWidth(int nWidth) //设置背景框的宽度
{
    m_rect.setWidth(nWidth);
    SetPattern(nPtternType);
    this->update(m_rect);
}

int QSimpleTextItem::GetWidth()
{
    return m_rect.width();
}

void QSimpleTextItem::SetHeight(int nHeight) //设置背景的高度
{
    m_rect.setHeight(nHeight);
    SetPattern(nPtternType);
    this->update(m_rect);
}

int QSimpleTextItem::GetHeight()
{
    return m_rect.height();
}

void QSimpleTextItem::setRect(const QRectF &qrcRect)
{
    m_rect = qrcRect;
    SetPattern(nPtternType);
    this->update(m_rect);
}

QDataStream &operator<<(QDataStream &stream, QSimpleTextItem *psimpleTextItem)
{
    stream << psimpleTextItem->m_rect << psimpleTextItem->sTEXT;
    stream << psimpleTextItem->m_font << psimpleTextItem->m_FontColor;
    stream << psimpleTextItem->m_RectBackColor << psimpleTextItem->m_RectFrontColor;
    stream << psimpleTextItem->m_Alianment;
    stream << psimpleTextItem->nPtternType << psimpleTextItem->m_RectOutLine;
    stream << psimpleTextItem->m_RectOutLineColor << psimpleTextItem->m_LineInterval;
    stream << psimpleTextItem->GetName() << psimpleTextItem->GetID();
    stream << psimpleTextItem->scenePos();
    stream << psimpleTextItem->isVisible();

    stream << psimpleTextItem->data(GROUP_TYPE_KEY).toInt();
    stream << psimpleTextItem->data(GROUP_DATALIST_KEY).toStringList();
    stream << psimpleTextItem->bFitSize;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QSimpleTextItem *psimpleTextItem)
{
    QString name ;
    int id;
    QPointF pos;
    bool bVisible = false;
    int typeKey = 0;
    QStringList dataList;
    stream >> psimpleTextItem->m_rect >> psimpleTextItem->sTEXT;
    stream >> psimpleTextItem->m_font >> psimpleTextItem->m_FontColor;
    stream >> psimpleTextItem->m_RectBackColor >> psimpleTextItem->m_RectFrontColor;
    stream >> psimpleTextItem->m_Alianment;
    stream >> psimpleTextItem->nPtternType >> psimpleTextItem->m_RectOutLine;
    stream >> psimpleTextItem->m_RectOutLineColor >> psimpleTextItem->m_LineInterval;
    stream >> name >> id >> pos >> bVisible >> typeKey >> dataList>> psimpleTextItem->bFitSize;

    psimpleTextItem->SetTextAlign(psimpleTextItem->m_Alianment);
    psimpleTextItem->SetPattern(psimpleTextItem->nPtternType);
    psimpleTextItem->SetName(name);
    psimpleTextItem->SetID(id);
    psimpleTextItem->setPos(pos);
    psimpleTextItem->setVisible(bVisible);
    psimpleTextItem->setData(GROUP_TYPE_KEY,QVariant(typeKey));
    psimpleTextItem->setData(GROUP_DATALIST_KEY,QVariant(dataList));
    return stream;
}
void QSimpleTextItem::SetDescription(QStringList sText)
{
    this->setData(GROUP_DATALIST_KEY,QVariant(sText));
}

QStringList QSimpleTextItem::GetDescription()
{
    return this->data(GROUP_DATALIST_KEY).toStringList();
}
void QSimpleTextItem::SetFitSize(bool bfit = false)
{
    bFitSize = bfit;
}
