#ifndef QHISTRENDDISPLAYXYDLG_H
#define QHISTRENDDISPLAYXYDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include "qgraphicsitem.h"
namespace Ui {
    class QHisTrendDisplayXYDlg;
}

class QHisTrendDisplayXYDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QHisTrendDisplayXYDlg(QWidget *parent = 0);
    ~QHisTrendDisplayXYDlg();
    int CheckMinMax(int DataType);
    void Init(QGraphicsItem *pItem);
    QIntValidator *max;
private:
    Ui::QHisTrendDisplayXYDlg *ui;
//    QPickerColor *pX_Axis_Color;
//    QPickerColor *pX_Grid_Color;
//    QPickerColor *pY_Axis_Color;
//    QPickerColor *pY_Grid_Color;

private slots:
    void on_Y_Grid_Color_clicked();
    void on_Y_Axis_Color_clicked();
    void on_X_Grid_Color_clicked();
    void on_X_Axis_Color_clicked();
    void on_Y_Show_X_Axis_clicked(bool checked);
    void on_Y_Show_Ticks_clicked(bool checked);
    void on_X_Show_Y_Axis_clicked(bool checked);
    void on_X_Show_Ticks_clicked(bool checked);
    void on_Y_DisplayMarks_clicked(bool checked);
    void on_X_DisplayTime_clicked(bool checked);
    void setXAxisColor(const QColor & mColor);       //
    void setXGridColor(const QColor & mColor);      //
    void setYAxisColor(const QColor & mColor);       //
    void setYGridColor(const QColor & mColor);      //
public:
    void SaveXYPage(QStringList *datalist, int index);
};

#endif // QHISTRENDDISPLAYXYDLG_H
