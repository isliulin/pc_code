#ifndef QMYSTYLE_H
#define QMYSTYLE_H

#include <QWindowsStyle>
#include <QWindowsXPStyle>
#include <QWindowsVistaStyle>

class QMyStyleVista :  public QWindowsVistaStyle
{
public:
    QMyStyleVista();
    void drawPrimitive(PrimitiveElement pe,
                       const QStyleOption *opt,
                       QPainter *p,
                       const QWidget *w) const;
};

class QMyStyleXP : public QWindowsXPStyle
{
public:
    QMyStyleXP();
    void drawPrimitive(PrimitiveElement pe,
                       const QStyleOption *opt,
                       QPainter *p,
                       const QWidget *w) const;
};
#endif // QMYSTYLE_H
