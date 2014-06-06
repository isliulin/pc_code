#ifndef QCHARTDLG_H
#define QCHARTDLG_H

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <qgraphicsitem.h>
#include "qchartcmcolor.h"
#include "qchartcmruler.h"
#include "qchartcommon.h"
#include "qchartmeter.h"
#include "qchartmecolor.h"
#include "qchartmeruler.h"
#include "view/qgroupitem.h"
#include "view/qpolygonitem.h"
#include "Frame/ThingDlg/switch/securitywidget.h"

namespace Ui {
    class QChartDlg;
}

class QChartDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QChartDlg(QGraphicsItem *pItem, QWidget *parent = 0);
    void InitAllProperty(ChartItem *pItem = NULL);
    void onSaveItemPosition();//����Item����
    QGraphicsItem * pCopyItem;
    struct METER_INFORMATION meter_st;
    struct COMMON_INFORMATION common_st;

    QVBoxLayout *mainLayout;
    //��ͨ��״ͼ�Ļ�������ɫ����߶���
    QChartCommon *qcommonbase;
    QChartCmColor *qcommoncolor;
    QChartCMRuler *qcommonruler;
    SecurityWidget *pSecurityWight;//����ҳ��

    //�Ǳ�Ļ�������ɫ����߶���
    QChartMeter *qmeterbase;
    QChartMeColor *qmetercolor;
    QchartMeRuler *qmeteruler;

    ~QChartDlg();

public slots:
    void reload_tabwidget();
    void reload_common();
    void change_direction();
    void setMeterPointColor();
    void setMeterBackColor();
    void reDrawMeter();
    void confyButton();
    void loadHelp();
    void setCommonShapeType();//��ͨͼ����״ͼ����Բ��Բ������ͼѡ�����
    void setCommonScaleColor();    //��ͨͼ�ο̶�ҳ��̶ȡ���ɫ�ı�۴���
    void setMeterScaleColor();    //�Ǳ�ͼ�ο̶�ҳ��̶ȡ���ɫ�ı�۴���
    void cancelButton();
    //void onRotateAngle(bool bflag);//����ͼ�Ͳ���ͼ��ת�Ƕ�

private:
    Ui::QChartDlg *ui;
    QTabWidget *tabWidget;
    GRAPH_TYPE enGrahpType;
    int oId;

};

#endif // QCHARTDLG_H
