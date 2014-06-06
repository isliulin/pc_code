#ifndef QFLOWBLOCKGENDLG_H
#define QFLOWBLOCKGENDLG_H

#include <QWidget>
#include <QGraphicsScene>
#include "qpickercolor.h"
#include "view/qrectitem.h"
#include "view/qitemgroup.h"
#include "Frame/qprogectmanager.h"
#include "ui_qflowblockgendlg.h"
#include "view/FlowBlockItem.h"

namespace Ui {
    class QFlowBlockGenDlg;
}

class QFlowBlockGenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QFlowBlockGenDlg(QWidget *parent = 0);
    ~QFlowBlockGenDlg();
    void Init(FlowBlockItem *pItem);
    bool FlowBlockGenSave(FlowInfo &flow_st);
    FlowBlockItem *pCopyItem;
    QButtonGroup *RadioButton_direction_Group;
    QButtonGroup *RadioButton_speed_Group;
    QButtonGroup *RadioButtonState;
    QButtonGroup *FixupFlowSpeed;
    QButtonGroup *FlowMode;
    Ui::QFlowBlockGenDlg *ui;
    Keyboard Monitor_Address_Keyboard;
    Keyboard TouchAddr;
    Keyboard Flowspeedkeyboard;
private slots:
    void on_DynamicFlowSpeed_clicked();
    void on_FixupFlowspeed_clicked();
    void on_m_framcolorbtn_clicked();
    void on_m_pipebackcolorbtn_clicked();
    void on_m_pipefrontcolorbtn_clicked();
    void on_m_flowbackcolorbtn_clicked();
    void on_m_flowfrontcolorbtn_clicked();
    void on_FlowSpeedKeyboard_clicked();
    void on_m_touchbtn_clicked();
    void on_m_changdircheck_clicked(bool checked);
    void on_Monitor_Address_Btn_clicked();
    void on_m_patterncmb_currentIndexChanged(int index);
    void on_m_countspinBox_valueChanged(int );
    void on_m_noframcheck_clicked();
    void on_m_Vradio_clicked();
    void on_m_Hradio_clicked();

    void OnSetFlowFrontColor(const QColor &);
    void OnSetFlowBackColor(const QColor &);
    void OnSetPipeFrontColor(const QColor &);
    void OnSetPipeBackColor(const QColor &);
    void OnSetFramColor(const QColor &);

public:
    FlowBlockItem *pGroup;
    QGraphicsItem *pOldItem;
public:
    void SplitItem(QGraphicsItem *pItem);

signals:
    void DrawFlow();
private:
    int nDirection;
    int nFlowCount;
    bool nInitFlag;
    bool isPatten;

   // QRectItem *pMainRect;
    QList<QRectItem *> pRectList;

};

#endif // QFLOWBLOCKGENDLG_H
