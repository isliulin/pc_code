#ifndef QPICKERCOLOR_H
#define QPICKERCOLOR_H

#include <QPushButton>
#include <QRect>

class QPickerColor : public QPushButton
{
    Q_OBJECT
public:
    QPickerColor();
    QPickerColor(QWidget *parent = 0 );

    QColor GetColor();
    QRect m_Rect;
private slots:
    void slotChangeColor();
protected:
    void paintEvent(QPaintEvent *painter);
public:
    void setCurrentColor(const QColor &tColor);
    inline QColor currentColor() const { return mCurrentColor; }
private:
    QColor mCurrentColor;
};

#endif // QPICKERCOLOR_H
