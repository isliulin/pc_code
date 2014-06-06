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
    void onSaveItemPosition();//保存Item坐标
    QGraphicsItem * pCopyItem;
    struct METER_INFORMATION meter_st;
    struct COMMON_INFORMATION common_st;

    QVBoxLayout *mainLayout;
    //普通柱状图的基本、颜色、标尺对象
    QChartCommon *qcommonbase;
    QChartCmColor *qcommoncolor;
    QChartCMRuler *qcommonruler;
    SecurityWidget *pSecurityWight;//显现页面

    //仪表的基本、颜色、标尺对象
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
    void setCommonShapeType();//普通图形柱状图、半圆、圆、槽型图选择处理槽
    void setCommonScaleColor();    //普通图形刻度页面刻度、颜色改变槽处理
    void setMeterScaleColor();    //仪表图形刻度页面刻度、颜色改变槽处理
    void cancelButton();
    //void onRotateAngle(bool bflag);//柱形图和槽型图旋转角度

private:
    Ui::QChartDlg *ui;
    QTabWidget *tabWidget;
    GRAPH_TYPE enGrahpType;
    int oId;

};

#endif // QCHARTDLG_H
