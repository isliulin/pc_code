#include "qpickercolor.h"
#include <QColorDialog>
#include <QEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QCDEStyle>
//#include <QFrame>

QPickerColor::QPickerColor()
{
    connect( this, SIGNAL(clicked()), SLOT( slotChangeColor()));//���������ťִ��slotChangeColor
    this->setFlat(true);
    this->setAutoFillBackground(true);
    m_Rect = this->geometry();
    this->setFixedWidth(m_Rect.width());
    this->setFixedHeight(m_Rect.height());
    setCurrentColor( "#ffffff" );
}

QPickerColor::QPickerColor(QWidget *parent)
{
    this->setFlat(true);
    this->setAutoFillBackground(true);
    this->setStyle(new QCDEStyle);

    m_Rect = this->geometry();
    this->setFixedWidth(m_Rect.width());
    this->setFixedHeight(m_Rect.height());


    setCurrentColor( "#ffffff" );

    connect( this, SIGNAL(clicked()), SLOT( slotChangeColor()));//���������ťִ��slotChangeColor
}

void QPickerColor::slotChangeColor()
{
    //������ɫ�Ի��򣬳�ʼֵ����ΪmCurrentColor
    QColor newColor = QColorDialog::getColor( mCurrentColor, this );
    if ( newColor.isValid() )
        setCurrentColor( newColor );//�����ɫֵ�Ϸ�
}

void QPickerColor::setCurrentColor(const QColor &tColor)
{
    //���û�иı���ɫ�򷵻�

    if ( mCurrentColor == tColor ) //currentColor()
        return;

    mCurrentColor = tColor;

    QPalette pal=this->palette();
    pal.setColor(QPalette::Button, tColor);

    this->setPalette(pal);
}


void QPickerColor::paintEvent(QPaintEvent *painter) //draw back rect
{
    QPainter Painter(this);
    QBrush br(Qt::SolidPattern);
    br.setColor(mCurrentColor);

    Painter.drawRect(0,0,m_Rect.width(),m_Rect.height());
    Painter.setBrush(br);
}

QColor QPickerColor::GetColor()
{
    return mCurrentColor;
}

