#include "color.h"

#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QPainter>
#include <QtGui/QPushButton>
#include <QtGui/QColorDialog>
#include <QtCore/QMap>
#include <QtGui/QLayout>
#include <QtGui/QStyle>
#include <QtGui/QLabel>
#include <QtGui/QToolTip>
#include <QtGui/QPixmap>
#include <QtGui/QFocusEvent>
#include <QtGui/QPaintEvent>
#include <QtGui/QGridLayout>
#include <QtGui/QHideEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QShowEvent>
#include <QtGui/QMouseEvent>
#include <math.h>
#include "qpickercolor.h"
#include <qDebug>
#include <QBitmap>
#include <QMessageBox>
#include <QClipboard>

QLabel *labelcolor;
QLabel *labelRGB;

ShapeButton::ShapeButton(int index,QWidget * parent)
    :QLabel(parent)
{
    shapeindex = index;
}
void ShapeButton::mousePressEvent(QMouseEvent *ev)
{
    emit click(shapeindex);
}
ColorPickerPopup::ColorPickerPopup(int width, bool withColorDialog,QWidget *parent)
    : QFrame(parent, Qt::Popup)
{
    setFrameStyle(QFrame::StyledPanel);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setFocusPolicy(Qt::StrongFocus);
    cols = width;

    shapeIndex = 1;

    label1=new ShapeButton(1,this);
    label2=new ShapeButton(2,this);
    label3=new ShapeButton(3,this);

    labelcolor=new QLabel(this);

    labelRGB=new QLabel(this);

    if (withColorDialog)
    {
        moreButton = new ColorPickerButton(this);
        moreButton->setFixedWidth(20);
        moreButton->setFixedHeight(20);
        moreButton->setFrameRect(QRect(1, 1, 20, 20));
        connect(moreButton, SIGNAL(clicked()),this, SLOT(getColorFromDialog()));
    }
    else
    {
        moreButton = 0;
    }
    initColor();
    grid = 0;
    regenerateGrid();

   this->setFrameShape(QFrame::Box);
   this->setMouseTracking(true);

   desk_image=NULL;

   QPixmap desk_Pixmap=QPixmap::grabWindow(QApplication::desktop()->winId());
   desk_image =new QImage(desk_Pixmap.toImage());

   Cursor_pixmap = new QPixmap(":/btn/images/pick.gif");
   QCursor cur(*Cursor_pixmap,1,Cursor_pixmap->height()*0.9);
   QApplication::setOverrideCursor(cur);
}


ColorPickerPopup::~ColorPickerPopup()
{
//    if(labelcolor!=NULL)
//    {
//        delete labelcolor;
//        labelcolor=NULL;
//    }

//    if(labelRGB!=NULL)
//    {
//        delete labelRGB;
//        labelRGB=NULL;
//    }

    if(grid!=NULL)
    {
        delete grid;
        grid=NULL;
    }

    for(int i=0;i<items.size();i++)
    {
        if(items[i])
        {
            delete items[i];
            items[i]=NULL;
        }

    }
    items.clear();
    delete Cursor_pixmap;
    Cursor_pixmap=NULL;
    //image_bits = desk_image->bits();
    //delete image_bits;
    delete desk_image;
    desk_image=NULL;
}

ColorPickerItem *ColorPickerPopup::find(const QColor &col) const
{
    for (int i = 0; i < items.size(); ++i)
    {
        if (items.at(i) && items.at(i)->color() == col)
            return items.at(i);
    }
    return 0;
}


void ColorPickerPopup::insertColor(const QColor &col, const QString &text, int index)
{
    // Don't add colors that we have already.
    ColorPickerItem *existingItem = find(col);
    ColorPickerItem *lastSelectedItem = find(lastSelected());
    if (existingItem)
    {
        if (lastSelectedItem && existingItem != lastSelectedItem)
            lastSelectedItem->setSelected(false);
        existingItem->setFocus();
        existingItem->setSelected(true);
        return;
    }
    ColorPickerItem *item = new ColorPickerItem(index,col, text, this);
    if (lastSelectedItem)
    {
        lastSelectedItem->setSelected(false);
    }
    else
    {
        item->setSelected(true);
        lastSel = col;
    }
    item->setFocus();
    connect(item, SIGNAL(selected()), SLOT(updateSelected()));
	connect(item, SIGNAL(rightClick()), SLOT(reject()));
    if (index == -1)
        index = items.count();

    items.insert((unsigned int)index, item);
   // regenerateGrid();
  //  update();
}

QColor ColorPickerPopup::color(int index) const
{
    if (index < 0 || index > (int) items.count() - 1)
        return QColor();

    ColorPickerPopup *that = (ColorPickerPopup *)this;
    return that->items.at(index)->color();
}

void ColorPickerPopup::updateSelected()
{
    QLayoutItem *layoutItem;
    int i = 0;
    while ((layoutItem = grid->itemAt(i)) != 0)
    {
        QWidget *w = layoutItem->widget();
        if (w && w->inherits("ColorPickerItem"))
        {
            ColorPickerItem *litem = reinterpret_cast<ColorPickerItem *>(layoutItem->widget());
            if (litem != sender())
                litem->setSelected(false);
        }
        ++i;
    }

    if (sender() && sender()->inherits("ColorPickerItem")) {
        ColorPickerItem *item = (ColorPickerItem *)sender();
        lastSel = item->color();
        emit selected(item->color());
    }

	bRight = false;
    hide();
}//
void ColorPickerPopup::reject()
{
	bRight = true;
	hide();
}

bool ColorPickerPopup::event(QEvent *e)
{
	QMouseEvent *mevent = static_cast<QMouseEvent*>(e);
	if (e->type() == QEvent::MouseButtonPress)
	{
		if (mevent->button() == Qt::LeftButton)
		{
			bRight = false;
		}
		else
		{
			bRight = true;
		}
		
	}
	return QFrame::event(e);
}

void ColorPickerPopup::hideEvent ( QHideEvent * event )
{
   QApplication::restoreOverrideCursor();
   QColor cor=labelcolor->palette().background().color();
   if (!bRight)
   {
	   emit selected(cor);
   }
   this->deleteLater();

}

QColor ColorPickerPopup::lastSelected() const
{
    return lastSel;
}

void ColorPickerPopup::focusOutEvent(QFocusEvent *dragLeaveEvent)
{

}
void ColorPickerPopup::mouseMoveEvent(QMouseEvent *e)
{
    QRgb rgb=desk_image->pixel(QCursor::pos());
    int green= qGreen(rgb );
    int blue= qBlue(rgb);
    int red= qRed(rgb);
    QColor cor(red,green,blue);
    labelcolor->setStyleSheet(QString("background:%1").arg(cor.name()));
    labelRGB->setText(QString("(%1,%2,%3)").arg(cor.red()).arg(cor.green()).arg(cor.blue()));

}
void ColorPickerPopup::regenerateGrid()
{
    widgetAt.clear();

    int columns = cols;
    if (columns == -1)
    {
        columns = (int) ceil(sqrt((float) items.count()));
    }

    if (grid) delete grid;
    grid = new QGridLayout(this);
    grid->setMargin(0);
    grid->setSpacing(0);

    int ccol = 0, crow = 0;
    for (int i = 0; i < items.size(); ++i)
    {
        if (items.at(i))
        {
            widgetAt[crow][ccol] = items.at(i);
            grid->addWidget(items.at(i), crow, ccol++);

            if (ccol == columns)
            {
                ++crow;
                ccol = 0;
            }
        }
    }


   labelcolor->setFrameShape(QFrame::Box);
   labelcolor->setStyleSheet("background:#ffffcc");


   label1->setFrameShape(QFrame::Box);
   label1->setStyleSheet("border-style: outset;background:#a0a000");
   label1->setFixedHeight(19);

   label2->setFrameShape(QFrame::Box);
   label2->setStyleSheet("border-style: outset;background:#606040");
   label2->setFixedHeight(19);

   label3->setFrameShape(QFrame::Box);
   label3->setStyleSheet("border-style: outset;background:#8080a0");
   label3->setFixedHeight(19);


   labelRGB->setText("(0,255,255)");
    if (moreButton)
    {
        grid->addWidget(labelcolor, crow+20,0,crow+3,3);
        grid->addWidget(labelRGB, crow+20,4,crow+3,5);
        grid->addWidget(moreButton, crow+20,columns-1,crow+3,columns);

        grid->addWidget(label1,crow+1,0,crow+3,3);
        connect(label1,SIGNAL(click(int)),this,SLOT(Showshape(int )));

        grid->addWidget(label2,crow+1,3,crow+3,3);
        connect(label2,SIGNAL(click(int)),this,SLOT(Showshape(int )));

        grid->addWidget(label3,crow+1,6,crow+3,3);
        connect(label3,SIGNAL(click(int)),this,SLOT(Showshape(int )));

        label1->setFocus();
       // widgetAt[crow][columns] = moreButton;
    }

    updateGeometry();
}

void ColorPickerPopup::getColorFromDialog()
{
    bool ok;
    QRgb rgb = QColorDialog::getRgba(lastSel.rgba(),&ok,this);
    if (!ok)
        return;

    QColor col = QColor::fromRgba(rgb);
    insertColor(col, tr("Custom"), -1);
    lastSel = col;
    emit selected(col);
}

ColorPickerItem::ColorPickerItem(int index,const QColor &color, const QString &text, QWidget *parent)
    : QFrame(parent), c(color), t(text), sel(false)
{
    //setToolTip(t);
    colorIndex = index;
    setFixedWidth(25);
    setFixedHeight(25);
    this->setMouseTracking(true);
}

ColorPickerItem::~ColorPickerItem()
{
}

QColor ColorPickerItem::color() const
{
    return c;
}

QString ColorPickerItem::text() const
{
    return t;
}

bool ColorPickerItem::isSelected() const
{
    return sel;
}

void ColorPickerItem::setSelected(bool selected)
{
    sel = selected;
    update();
}

void ColorPickerItem::setColor(const QColor &color, const QString &text)
{
    c = color;
    t = text;
    //setToolTip(t);
    update();
}


void ColorPickerItem::mouseMoveEvent(QMouseEvent *)
{
    setFocus();
    update();
    QColor col=this->palette().background().color();
    labelcolor->setStyleSheet(QString("background:%1").arg(col.name()));
    QString sRGB = QString("(%1,%2,%3)").arg(col.red()).arg(col.green()).arg(col.blue());
    labelRGB->setText(sRGB);
}


void ColorPickerItem::mouseReleaseEvent(QMouseEvent *ev)
{
	if (ev->button() == Qt::LeftButton)
	{

		sel = true;
		emit selected();
	}
	else
		emit rightClick();
}

void ColorPickerItem::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    int w = width();			// width of cell in pixels
    int h = height();			// height of cell in pixels

    p.setPen( QPen( Qt::gray, 0, Qt::SolidLine ) );

    if (sel)
    {
        p.drawRect(1, 1, w , h );
    }

    p.setPen( QPen( Qt::black, 0, Qt::SolidLine ) );
    p.drawRect(0, 0, w , h );
    p.fillRect(QRect(1, 1, w , h ), QBrush(c));
    this->setStyleSheet(QString("background:%1").arg(QBrush(c).color().name()));

    QColor textcolor = QColor(255-c.red(),255-c.green(),255-c.black());
    int gray = (c.red()*299 + c.green()*587 + c.black()*114 + 500) / 1000;

    if (hasFocus())
        p.drawRect(1, 1, w - 1, h - 1);

    if(gray >50)
        p.setPen(QPen(Qt::black, 0, Qt::SolidLine ));
    else
        p.setPen(QPen(Qt::white, 0, Qt::SolidLine ));


    //p.setPen(QPen(textcolor,Qt::SolidLine));
    p.drawText(QRectF(0,0,w,h),Qt::AlignCenter,QString::number(colorIndex));


}


ColorPickerButton::ColorPickerButton(QWidget *parent): QFrame(parent)
{
    setFrameStyle(StyledPanel);
}


void ColorPickerButton::mouseMoveEvent(QMouseEvent *)
{
    setFocus();
    update();
}


void ColorPickerButton::mouseReleaseEvent(QMouseEvent *)
{
    setFrameShadow(Raised);
    repaint();
    emit clicked();
}

void ColorPickerButton::paintEvent(QPaintEvent *e)
{
    QFrame::paintEvent(e);

    QPainter p(this);
    QRect r = rect();
    p.setPen( QPen( Qt::red, 0, Qt::SolidLine ) );
    p.drawRect(r.x() +4,r.y() +5, 10, 8);
    p.fillRect(QRect(r.x() +4,r.y() +5, 10, 8),QBrush(QColor(255,0,0)));

    p.setPen( QPen( Qt::yellow, 0, Qt::SolidLine ) );
    p.drawRect(r.x() + 8,r.y() +8, 8, 8);
    p.fillRect(QRect(r.x() + 8,r.y() +8, 8, 8),QBrush("#ffff00"));
    if (hasFocus())
    {
        p.setPen( QPen( Qt::black, 0, Qt::SolidLine ) );
        p.drawRect(0, 0, width() - 1, height() - 1);
    }
   this->setFrameShadow(QFrame::Raised);
    p.end();

}

void ColorPickerPopup::initColor()
{
    QColor inserColor;
    QString str = COLORS_SHAPE1 ;

     QStringList sList_color=str.split(",");

     for(int i=0;i<sList_color.size();i++)
     {
         inserColor.setNamedColor(sList_color.at(i));
         this->insertColor(inserColor,sList_color.at(i),i);
     }
}
void ColorPickerPopup::setLabelstyle(const QString style)
{
    if(labelcolor)
        labelcolor->setStyleSheet(style);
}
void ColorPickerPopup::setLabelText(const QString text)
{
    if(labelRGB)
        labelRGB->setText(text);
}
//«–ªª—’…´œ‘ æ
void ColorPickerPopup::Showshape(int index)
{
    QString colors;

    switch(index)
    {
    case 1:
        {
            colors = COLORS_SHAPE1;
            break;
        }
    case 2:
        {
            colors = COLORS_SHAPE2;
            break;
        }
    case 3:
        {
            colors = COLORS_SHAPE3;
            break;
        }
    default:
        colors = COLORS_SHAPE1;
        break;
    }


    QStringList sList_color=colors.split(",");
    QColor color;
    if(sList_color.size() == items.size())
    {
        for(int i =0;i<items.size();i++)
        {
            color.setNamedColor(sList_color.at(i));
            items.at(i)->setColor(color,sList_color.at(i));
        }
    }

}
