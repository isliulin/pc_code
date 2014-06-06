#ifndef QCHARTMERULER_H
#define QCHARTMERULER_H

#include <QWidget>
#include "color.h"
#include "view/ChartItem.h"

namespace Ui {
    class QchartMeRuler;
}

class QchartMeRuler : public QWidget
{
    Q_OBJECT

public:
    explicit QchartMeRuler(QWidget *parent = 0);
    void Init(ChartItem *pItem);
    void MeterGenSave(struct METER_INFORMATION &meter_st);
    int onGetMainScale();
    int onGetSubScale();
    QString onGetScaleColor();
    ~QchartMeRuler();

    //int nMainScale;        //主刻度
    //int nSubScale;         //次刻度
    QString sCaleColor;     //刻度颜色
    bool bInitFlag;

private:
    Ui::QchartMeRuler *ui;

signals:
    void scalechange();

public slots:
    void setScalebtnColor(const QColor &mColor);
    void onGetShowValue(bool &bShow);

private slots:
    void on_m_ShowScalevalueCkBox_clicked(bool checked);
    void on_m_ScaleColorBtn_clicked();
    void on_m_subScaleSpinBox_valueChanged(int );
    void on_m_SubSgroupBox_clicked(bool checked);
    void on_m_mainScaleSpBox_valueChanged(int );
};

#endif // QCHARTMERULER_H
