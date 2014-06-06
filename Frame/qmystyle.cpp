#include "qmystyle.h"

QMyStyleVista::QMyStyleVista()
{
}

void QMyStyleVista::drawPrimitive(PrimitiveElement pe,
                   const QStyleOption *opt,
                   QPainter *p,
                   const QWidget *w) const
{
    switch(pe)
    {
    case PE_FrameMenu:
        {
            p->fillRect(opt->rect, QBrush(QColor(197, 222, 255)));
            return;
        }
    default:
        {
            break;
        }
    }
    QWindowsVistaStyle::drawPrimitive(pe, opt, p, w);
}



QMyStyleXP::QMyStyleXP()
{
}

void QMyStyleXP::drawPrimitive(PrimitiveElement pe,
                   const QStyleOption *opt,
                   QPainter *p,
                   const QWidget *w) const
{
    switch(pe)
    {
    case PE_FrameMenu:
        {
            p->fillRect(opt->rect, QBrush(QColor(197, 222, 255)));
            return;
        }
    default:
        {
            break;
        }
    }
    QWindowsXPStyle::drawPrimitive(pe, opt, p, w);
}

