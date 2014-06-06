#ifndef COLOR_H
#define COLOR_H

#include <QtGui/QPushButton>
#include <QtCore/QString>
#include <QtGui/QColor>

#include <QtGui/QLabel>
#include <QtCore/QEvent>
#include <QtGui/QFocusEvent>
#include <QGridLayout>
#include <QEventLoop>

#define COLORS_SHAPE1 "#000000,#0000ff,#00ff00,#00ffff,#ff0000,#ff00ff,#ffff00,#ffffff,#000040,#0000a0,"\
                        "#004000,#004040,#0040a0,#0040ff,#00a000,#00a040,#00a0a0,#00a0ff,#00ff40,#00ffa0,"\
                        "#400000,#400040,#4000a0,#4000ff,#404000,#404040,#4040a0,#4040ff,#40a000,#40a040,"\
                        "#40a0a0,#40a0ff,#40ff00,#40ff40,#40ffa0,#40ffff,#a00000,#a00040,#a000a0,#a000ff,"\
                        "#a04000,#a04040,#a040a0,#a040ff,#a0a000,#a0a040,#a0a0a0,#a0a0ff,#a0ff00,#a0ff40,"\
                        "#a0ffa0,#a0ffff,#ff0040,#ff00a0,#ff4000,#ff4040,#ff40a0,#ff40ff,#ffa000,#ffa040,"\
                        "#ffa0a0,#ffa0ff,#ffff40,#ffffa0,#80a000,#80a040,#80a0a0,#80a0ff,#c0a000,#c0a040,"\
                        "#c0a0a0,#c0a0ff,#00c000,#00c040,#00c0a0,#00c0ff,#20c000,#20c040,#20c0a0,#20c0ff,"\
                        "#40c000,#40c040,#40c0a0,#40c0ff,#60c000,#60c040,#60c0a0,#60c0ff,#80c000,#80c040,"\
                        "#80c0a0,#80c0ff,#a0c000,#a0c040,#a0c0a0,#a0c0ff,#c0c000,#c0c040,#c0c0a0,#c0c0ff"

#define COLORS_SHAPE2 "#ffc000,#ffc040,#ffc0a0,#ffc0ff,#20ff00,#20ff40,#20ffa0,#20ffff,#60ff00,#60ff40,"\
                        "#60ffa0,#60ffff,#80ff00,#80ff40,#80ffa0,#80ffff,#c0ff00,#c0ff40,#c0ffa0,#c0ffff,"\
                        "#402000,#402040,#4020a0,#4020ff,#602000,#602040,#6020a0,#6020ff,#802000,#802040,"\
                        "#8020a0,#8020ff,#a02000,#a02040,#a020a0,#a020ff,#c02000,#c02040,#c020a0,#c020ff,"\
                        "#ff2000,#ff2040,#ff20a0,#ff20ff,#204000,#204040,#2040a0,#2040ff,#604000,#604040,"\
                        "#6040a0,#6040ff,#804000,#804040,#8040a0,#8040ff,#c04000,#c04040,#c040a0,#c040ff,"\
                        "#006000,#006040,#0060a0,#0060ff,#206000,#206040,#2060a0,#2060ff,#406000,#406040,"\
                        "#4060a0,#4060ff,#606000,#606040,#6060a0,#6060ff,#806000,#806040,#8060a0,#8060ff,"\
                        "#a06000,#a06040,#a060a0,#a060ff,#c06000,#c06040,#c060a0,#c060ff,#ff6000,#ff6040,"\
                        "#ff60a0,#ff60ff,#008000,#008040,#0080a0,#0080ff,#208000,#208040,#2080a0,#2080ff"

#define COLORS_SHAPE3 "#408000,#408040,#4080a0,#4080ff,#608000,#608040,#6080a0,#6080ff,#808000,#808040,"\
                        "#8080a0,#8080ff,#a08000,#a08040,#a080a0,#a080ff,#c08000,#c08040,#c080a0,#c080ff,"\
                        "#ff8000,#ff8040,#ff80a0,#ff80ff,#20a000,#20a040,#20a0a0,#20a0ff,#60a000,#60a040,"\
                        "#60a0a0,#60a0ff,#200000,#200040,#2000a0,#2000ff,#600000,#600040,#6000a0,#6000ff,"\
                        "#800000,#800040,#8000a0,#8000ff,#c00000,#c00040,#c000a0,#c000ff,#002040,#0020a0,"\
                        "#0020ff,#202000,#202040,#2020a0,#2020ff,#002000,#ece9d8,#ece9d8,#ece9d8,#ece9d8,"\
                        "#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,"\
                        "#ece9d8,#101010,#202020,#303030,#505050,#606060,#707070,#808080,#909090,#b0b0b0,"\
                        "#c0c0c0,#d0d0d0,#e0e0e0,#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,"\
                       "#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8,#ece9d8"


class ShapeButton : public QLabel
{
    Q_OBJECT
public:
    ShapeButton(int index,QWidget * parent = 0);
signals:
    void click(int index);
private:
    int shapeindex;
    void mousePressEvent(QMouseEvent *ev);
};
class   ColorPickerItem : public QFrame
{
    Q_OBJECT
public:
    ColorPickerItem(int index,const QColor &color = Qt::white, const QString &text = QString::null,QWidget *parent = 0);
    ~ColorPickerItem();
    QColor color() const;
    QString text() const;
    void setSelected(bool);
    bool isSelected() const;
signals:
    void clicked();
    void selected();
	void rightClick();
public slots:
    void setColor(const QColor &color, const QString &text = QString());
protected:

    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);

private:
    QColor c;
    QString t;
    bool sel;
    int colorIndex;
};

class  ColorPickerButton : public QFrame
{
    Q_OBJECT
public:
    ColorPickerButton(QWidget *parent);
signals:
    void clicked();
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
};

class ColorPickerPopup : public QFrame
{
    Q_OBJECT

public:
    ColorPickerPopup(int width, bool withColorDialog, QWidget *parent = 0);
    ~ColorPickerPopup();
    void insertColor(const QColor &col, const QString &text, int index);

    void setExecFlag();
    QColor lastSelected() const;
    ColorPickerItem *find(const QColor &col) const;
    QColor color(int index) const;
    void initColor();

    void setLabelstyle(const QString style);
    void setLabelText(const QString text);

    QPixmap *Cursor_pixmap;

    ShapeButton *label1;
    ShapeButton *label2;
    ShapeButton *label3;

signals:
    void selected(const QColor &);
    void hid();
public slots:
    void getColorFromDialog();
	void reject();
protected slots:
    void updateSelected();
    void Showshape(int index);
protected:
    void regenerateGrid();
    void focusOutEvent(QFocusEvent *);
    void mouseMoveEvent(QMouseEvent *e);
    void hideEvent ( QHideEvent * event ) ;
	bool event(QEvent *e);
private:
    QMap<int, QMap<int, QWidget *> > widgetAt;
    QList<ColorPickerItem *> items;
    QGridLayout *grid;
    QImage  *desk_image;
    const uchar * image_bits;
    int shapeIndex;
	bool bRight;



   // QLabel *labelcolor;
    ColorPickerButton *moreButton;

    int lastPos;
    int cols;
    QColor lastSel;
};

#endif // COLOR_H
