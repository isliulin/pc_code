#ifndef QTRENDCHARTXYDLG_H
#define QTRENDCHARTXYDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include "ui_qtrendchartxydlg.h"

namespace Ui {
    class QTrendChartXYDlg;
}

class QTrendChartXYDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QTrendChartXYDlg(QWidget *parent = 0);
    ~QTrendChartXYDlg();

    void Init(QGraphicsItem *pItem);
    QGraphicsItem * pCopyItem;
    QGraphicsScene *pScene;
    QIntValidator *vIntval;
    int checkMaxMin();

public:
    Ui::QTrendChartXYDlg *ui;
    QPickerColor *pX_Axis_Color;
    QPickerColor *pX_Grid_Color;
    QPickerColor *pY_Axis_Color;
    QPickerColor *pY_Grid_Color;
    int  TrendCheckMinMax(int DataType);

private slots:
    void on_Y_Grid_Color_clicked();
    void on_Y_Axis_Color_clicked();
    void on_X_Grid_Color_clicked();
    void on_X_Axis_Color_clicked();
    void on_Y_If_Show_Marks_clicked(bool checked);
    void on_Y_Show_X_Axis_clicked(bool checked);
    void on_Y_Show_Ticks_clicked(bool checked);
    void on_X_If_Show_Marks_clicked(bool checked);
    void on_X_Show_Y_Axis_clicked(bool checked);
    void on_X_Show_Ticks_clicked(bool checked);
//    void OnSetXAxisColor();
//    void OnSetXGridColor();
//    void OnSetYAxisColor();
//    void OnSetYGridColor();
    void setXAxisColor(const QColor & mColor);       //
    void setXGridColor(const QColor & mColor);      //
    void setYAxisColor(const QColor & mColor);       //
    void setYGridColor(const QColor & mColor);      //

public:
    void SaveXYPage(QStringList *datalist,int index);
};

#endif // QTRENDCHARTXYDLG_H
