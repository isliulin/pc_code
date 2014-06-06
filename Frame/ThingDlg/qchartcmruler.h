#ifndef QCHARTCMRULER_H
#define QCHARTCMRULER_H

#include <QWidget>
#include "color.h"
#include "view/ChartItem.h"

namespace Ui {
    class QChartCMRuler;
}

class QChartCMRuler : public QWidget
{
    Q_OBJECT

public:
    explicit QChartCMRuler(QWidget *parent = 0);
    void Init(ChartItem *pItem);
    void CommonGenSave(struct COMMON_INFORMATION &common_st);
    int onGetMainScale();
    int onGetSubScale();
    ~QChartCMRuler();

    int nMainScale;        //主刻度
    int nSubScale;         //次刻度
    QString sCaleColor;     //刻度颜色
    bool bInitFlag;

signals:
    void scalechange();//刻度发生改变事件
private:
    Ui::QChartCMRuler *ui;

public slots:
    void setScalebtnColor(const QColor &mColor);
    void onGetShowValue(bool &bShow);

private slots:
    void on_m_ShowScalevalueCkBox_clicked(bool checked);
    void on_m_subScaleSpinBox_valueChanged(int );
    void on_m_ScaleColorBtn_clicked();
    void on_m_SubSgroupBox_clicked(bool checked);
    void on_m_mainScaleSpBox_valueChanged(int );
};

#endif // QCHARTCMRULER_H
