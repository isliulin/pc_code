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
    sTEXT = "Text";                       //Ĭ���ı�

    m_rect.setRect(0,0,100,100);                         //���������θ���ʼֵ
    InitParameters();
}

QSimpleTextItem::QSimpleTextItem(QString sText)
{
    sTEXT = sText;                       //Ĭ���ı�
    m_rect.setRect(0,0,100,100);         //���������θ���ʼֵ
    InitParameters();
}


/*****************************************************************************
  �������ƣ�QSimpleTextItem(QRectF Rect, QString sText)
  �������壺���������캯��
  �������壺Rect�ı��ı������ο��С��sText��ʼ�ı�
*****************************************************************************/
QSimpleTextItem::QSimpleTextItem(QRectF Rect, QString sText)
{
    sTEXT = sText;                        //Ĭ���ı�
    m_rect = Rect;                        //���������θ���ʼֵ
    InitParameters();
}

void QSimpleTextItem::InitParameters()
{
    m_FontColor = QColor(0,0,0);          //������ɫ
    m_RectBackColor=QColor(255,0,0);          //���ο�ı���ɫ
    m_RectFrontColor=QColor(0,0,255);   //���ο��ǰ��ɫ
    m_Alianment = 5;                      //�ı��Ķ��뷽ʽ,Ĭ���Ǿ��ж���
    nPtternType = 0;                      //ѡ����ʽ������
    m_RectOutLine = true;                 //�������ο��Ƿ��б���
    m_RectOutLineColor = Qt::blue;         //�������ο�ɫ��ɫ
    m_LineInterval = 0;                   //�о�

    //add by tanghaiguo
    this->SetTextAlign(m_Alianment);
    this->SetPattern(nPtternType);

    m_font.setFamily("Droid Sans Fallback");//System
    m_font.setPointSize(9);
    m_font.setBold(false);
    m_font.setItalic(false);
    m_font.setUnderline(false);   //�����Ƿ����»���
    m_font.setLetterSpacing(QFont::AbsoluteSpacing,0); //����������־�

    this->setFlag(QGraphicsItem::ItemIsMovable,true);
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);

    bFitSize = false;
    ///for test
//    this->SetAlpha(0);
}

void QSimpleTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QString sContent = "" ; //��ʱ���ı�����,�ı��о�ʱ��
    QString sStr = "\n";
    int i=0;

    sContent = sTEXT;

    //�����о�
    for(i = 0; i < m_LineInterval;i++)
    {
        sStr= sStr + "\n";
    }
    sContent.replace("\n",sStr);

    //���þ��εı���ɫ
    if(nPtternType >= 0 && nPtternType <15)        //����Ϊһ��Qt�ṩ����ʽ
        painter->setBrush(m_brush);
    else if(nPtternType >= 15 && nPtternType <= 24) //����Ϊ���Թ���ɫ
        painter->setBrush(m_gradient);
    else if(nPtternType >= 25 && nPtternType <= 26) //����Ϊ���ǹ���ɫ
        painter->setBrush(m_radial);

    if(m_RectOutLine) //�����ı��б߿�
    {
        QPen npen(Qt::SolidLine);
        npen.setColor(m_RectOutLineColor);
        painter->setPen(npen);
    }
    else             //�����ı�û�б߿�
    {
        painter->setPen(Qt::NoPen);
    }
    painter->drawRect(m_rect);          //���ı��ı������ο�

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
        painter->setPen(m_FontColor);       //��������������ɫ�;��ο�ı߿�ɫ
        painter->drawText(rc,sContent); //�ھ��ο��л��ı�
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

void QSimpleTextItem::SetText(QString sText) //�����ı�
{
    sTEXT= sText;
    this->update(m_rect);
}

QString QSimpleTextItem::GetText()  //����ı�
{
    return sTEXT;
}

void QSimpleTextItem::SetFontColor(QColor color) //����������ɫ
{
    m_FontColor = color;
    this->update(m_rect);
}

QColor QSimpleTextItem::GetFontColor() //���������ɫ
{
    return m_FontColor;
}

void QSimpleTextItem::SetRectBackColor(QColor color) //���ñ������ο�ı���ɫ
{
    m_RectBackColor = color;
    SetPattern(nPtternType);
    this->update(m_rect);
}

QColor QSimpleTextItem::GetRectBackColor() //��ñ������ο�ı���ɫ
{
    return m_RectBackColor;
}

void QSimpleTextItem::SetRectFrontColor(QColor color) //���ñ������ο��ǰ��ɫ
{
    m_RectFrontColor = color;
    SetPattern(nPtternType);
    this->update(m_rect);
}

QColor QSimpleTextItem::GetRectFrontColor()          //��ñ������ο��ǰ��ɫ
{
    return m_RectFrontColor;
}

void QSimpleTextItem::SetAlpha(int nAlpha) //����͸���� nAlpha 0-255��ֵԽС��Խ͸��
{
    m_RectFrontColor.setAlpha(nAlpha);
    m_RectBackColor.setAlpha(nAlpha);
    this->SetPattern(nPtternType);
    this->update(m_rect);
}

int QSimpleTextItem::GetAlpha() //��ñ���ɫ��͸����
{
    return m_RectFrontColor.alpha();
}

void QSimpleTextItem::SetFontSize(int nFontSize) //���������С
{
    m_font.setPointSize(nFontSize);
    this->update(m_rect);
}

int QSimpleTextItem::GetFontSize() //��������С
{
    return m_font.pointSize();
}

void QSimpleTextItem::SetFontName(QString sName) //������������
{
    m_font.setFamily(sName);
    this->update(m_rect);
}

QString QSimpleTextItem::GetFontName() //�����������
{
    return m_font.family();
}

void QSimpleTextItem::SetFontBold(bool nFlag) //true��������Ϊ�����������
{
    m_font.setBold(nFlag);
    this->update(m_rect);
}

bool QSimpleTextItem::GetFontBold() //��������Ƿ��Ǵ���
{
    return m_font.bold();
}

void QSimpleTextItem::SetFontItalic(bool nFlag) //true��������Ϊб���������
{
    m_font.setItalic(nFlag);
    this->update(m_rect);
}

bool QSimpleTextItem::GetFontItalic() //��������Ƿ���б��
{
    return m_font.italic();
}

void QSimpleTextItem::SetFontUnderLine(bool nFlag) //true���������Ƿ����»���
{
    m_font.setUnderline(nFlag);
    this->update(m_rect);
}

bool QSimpleTextItem::GetFontUnderLine() //��������Ƿ����»���
{
    return m_font.underline();
}

void QSimpleTextItem::SetFontWordInterval(int nInterval) //�����ı����־�
{
    m_font.setLetterSpacing(QFont::AbsoluteSpacing,nInterval);
    this->update(m_rect);
}

int QSimpleTextItem::GetFontWordInterval() //����ı����־�
{
    return m_font.letterSpacing();
}

/*****************************************************************************
  �������ƣ�SetTextAlign(int nAlignType)
  �������壺�����ı��Ķ��뷽ʽ
  �������壺nAlignType
  nAlignType=1:���ϽǶ���
  nAlignType=2:�ϱ߶���
  nAlignType=3:���ϽǶ���
  nAlignType=4:��߶���
  nAlignType=5:���ж���
  nAlignType=6:�ұ߶���
  nAlignType=7:���½Ƕ���
  nAlignType=8:�±߶���
  nAlignType=9:���½Ƕ���
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

int QSimpleTextItem::GetTextAlign() //����ı��Ķ��뷽ʽ
{
    return m_Alianment;
}

void QSimpleTextItem::SetPattern(int nType) //���ñ������ε���ʽ
{
    nPtternType = nType;
    m_gradient.setStart(m_rect.topLeft());
    m_gradient.setFinalStop(m_rect.bottomRight());
    m_gradient.setSpread(QGradient::PadSpread);

    m_radial.setCenter(m_rect.center());
    m_radial.setRadius(m_rect.width()*(0.5));
    m_radial.setFocalPoint(m_rect.center());

    m_brush.setColor(m_RectFrontColor); //����ǰ��ɫ����ʽ��ɫ

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

        case 2: //�������
            m_gradient.setStart(m_rect.bottomLeft());
            m_gradient.setColorAt(0,m_RectFrontColor );
            m_gradient.setColorAt(1,m_RectBackColor );
            break;
        case 3: //����Գƹ���
            m_gradient.setStart(m_rect.bottomLeft());
            m_gradient.setColorAt(0,m_RectFrontColor );
            m_gradient.setColorAt(0.5,m_RectBackColor );
            m_gradient.setColorAt(1,m_RectFrontColor );
            break;
        case 4: //�������
            m_gradient.setStart(m_rect.topRight());
            m_gradient.setColorAt(0,m_RectFrontColor  );
            m_gradient.setColorAt(1,m_RectBackColor);
            break;
        case 5: //����Գƹ���
            m_gradient.setStart(m_rect.topRight());
            m_gradient.setColorAt(0,m_RectFrontColor  );
            m_gradient.setColorAt(0.5,m_RectBackColor);
            m_gradient.setColorAt(1,m_RectFrontColor );
            break;
        case 6: //б�Ϲ���
            m_gradient.setColorAt(0,m_RectFrontColor );
            m_gradient.setColorAt(1,m_RectBackColor );
            break;
        case 7: //б�϶Գƹ���
            m_gradient.setColorAt(0,m_RectFrontColor );
            m_gradient.setColorAt(0.5,m_RectBackColor );
            m_gradient.setColorAt(1,m_RectFrontColor );
            break;
        case 8: //б�¹���
            m_gradient.setStart(m_rect.bottomLeft());
            m_gradient.setFinalStop(m_rect.topRight());
            m_gradient.setColorAt(0,m_RectBackColor );
            m_gradient.setColorAt(1,m_RectFrontColor);
            break;
        case 9: //б�¶Գƹ���
            m_gradient.setStart(m_rect.bottomLeft());
            m_gradient.setFinalStop(m_rect.topRight());
            m_gradient.setColorAt(0,m_RectFrontColor );
            m_gradient.setColorAt(0.5,m_RectBackColor );
            m_gradient.setColorAt(1,m_RectFrontColor );
            break;
        case 10: //���ϽǷ���

            m_gradient.setStart(m_rect.topRight());
            m_gradient.setFinalStop(m_rect.bottomLeft());
            m_gradient.setColorAt(0,m_RectBackColor );
            m_gradient.setColorAt(1,m_RectFrontColor );
            break;
        case 11: //���ϽǷ���
            m_gradient.setColorAt(0,m_RectBackColor );
            m_gradient.setColorAt(1, m_RectFrontColor);
            break;
        case 12: //���ķ���
            m_radial.setColorAt(0,m_RectBackColor );
            m_radial.setColorAt(1,m_RectFrontColor );
            break;
        case 13: //������
            m_radial.setFocalPoint(m_rect.x(),m_rect.center().y());
            m_radial.setColorAt(0,m_RectBackColor );
            m_radial.setColorAt(1,m_RectFrontColor );
            break;
        default:
            break;
     }
    this->update(m_rect);
}

int QSimpleTextItem::GetPattern() //�����ʽ
{
    return nPtternType;
}

/*****************************************************************************
  �������ƣ�SetRectOutLine(bool nFlag)
  �������壺�����ı����������Ƿ��б���
  �������壺nFlag=true��ʾ�б��ߣ�nFlag=false��ʾû�б���
*****************************************************************************/
void QSimpleTextItem::SetRectOutLine(bool nFlag) //�����ı��Ƿ��б߿�
{
    m_RectOutLine = nFlag;
    this->update(m_rect);
}

bool QSimpleTextItem::GetRectOutLine()  //����ı��Ƿ��б߿�
{
    return m_RectOutLine;
}

void QSimpleTextItem::SetRectOutLineColor(QColor color)//�����ı��߿�ɫ
{
    m_RectOutLineColor = color;
    this->update(m_rect);
}

QColor QSimpleTextItem::GetRectOutLineColor()  //����ı��ı߿�ɫ
{
    return m_RectOutLineColor;
}

void QSimpleTextItem::SetLineInterval(int nInterval) //�����о�
{
    m_LineInterval = nInterval;
    this->update(m_rect);
}

int QSimpleTextItem::GetLineInterval() //����о�
{
    return m_LineInterval;
}

QFont QSimpleTextItem::GetTextFont() //�������
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

void QSimpleTextItem::SetWidth(int nWidth) //���ñ�����Ŀ��
{
    m_rect.setWidth(nWidth);
    SetPattern(nPtternType);
    this->update(m_rect);
}

int QSimpleTextItem::GetWidth()
{
    return m_rect.width();
}

void QSimpleTextItem::SetHeight(int nHeight) //���ñ����ĸ߶�
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
