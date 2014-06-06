#ifndef SCATTERWIDGET_H
#define SCATTERWIDGET_H

#include <QWidget>
#include "view/animationitem.h"

namespace Ui {
    class ScatterWidget;
}

class ScatterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScatterWidget(QWidget *parent = 0);
    void Init(AnimationItem *pItem);
    bool onAnimatInfosave(AnInfo &aninfo);
    void onSetTrack(int index);//初始轨迹点
    void doubleClickInit(AnimationItem *pItem);
    QVector<TrackPointInfo> m_Tinfo;//轨迹点坐标
    ~ScatterWidget();

private:
    Ui::ScatterWidget *ui;
    bool bInitFlag;
    Keyboard Monitor_Address_Keyboard;
    QVector <TPMoveInfo> stMoveInfo;//移动预设值列表
    QVector <int> values;

signals:
    void onResetpoint(int index,QPointF pos);//重新设置轨迹点坐标

private slots:
    void on_btn_customValue_clicked();
    void on_m_MoveCtrlAddressEntryBtn_clicked();
    void on_m_TrackspBox_valueChanged(int );
    void on_m_MoveCondtionCmBox_currentIndexChanged(int index);
};

#endif // SCATTERWIDGET_H
