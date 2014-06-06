#ifndef AREAWIDGET_H
#define AREAWIDGET_H

#include <QWidget>
#include "view/animationitem.h"

namespace Ui {
    class AreaWidget;
}

class AreaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AreaWidget(QWidget *parent = 0);
    void Init(AnimationItem *pItem);
    bool onAnimatInfosave(AnInfo &aninfo);
    void doubleClickInit(AnimationItem *pItem);
    ~AreaWidget();

private:
    QVector<TrackPointInfo> m_Tinfo;//¹ì¼£µã×ø±ê
    Ui::AreaWidget *ui;
    Keyboard Monitor_Address_Keyboard;

private slots:
    void on_m_YAddressEntryBtn_clicked();
    void on_m_XAddressEntryBtn_clicked();
};

#endif // AREAWIDGET_H
