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
    void onSetTrack(int index);//��ʼ�켣��
    void doubleClickInit(AnimationItem *pItem);
    QVector<TrackPointInfo> m_Tinfo;//�켣������
    ~ScatterWidget();

private:
    Ui::ScatterWidget *ui;
    bool bInitFlag;
    Keyboard Monitor_Address_Keyboard;
    QVector <TPMoveInfo> stMoveInfo;//�ƶ�Ԥ��ֵ�б�
    QVector <int> values;

signals:
    void onResetpoint(int index,QPointF pos);//�������ù켣������

private slots:
    void on_btn_customValue_clicked();
    void on_m_MoveCtrlAddressEntryBtn_clicked();
    void on_m_TrackspBox_valueChanged(int );
    void on_m_MoveCondtionCmBox_currentIndexChanged(int index);
};

#endif // SCATTERWIDGET_H
