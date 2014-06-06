#ifndef QTRENDCHARTPENDLG_H
#define QTRENDCHARTPENDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include "ui_qtrendchartpendlg.h"
namespace Ui {
    class QTrendChartPenDlg;
}

class QTrendChartPenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QTrendChartPenDlg(QWidget *parent = 0);
    ~QTrendChartPenDlg();
    Ui::QTrendChartPenDlg *ui;
    int TrendCheckMinMax(int DataType);
    void InitPenType( QComboBox * pComboBox);

    void Init(QGraphicsItem *pItem);
    QGraphicsItem * pCopyItem;
    QGraphicsScene *pScene;

//public:
//    QPickerColor *pP1Color;
//    QPickerColor *pP2Color;
//    QPickerColor *pP3Color;
//    QPickerColor *pP4Color;
//    QPickerColor *pP5Color;
//    QPickerColor *pP6Color;
//    QPickerColor *pP7Color;
//    QPickerColor *pP8Color;
public slots:

public:
    void SetPenHide(int nIndex);
    void SavePenPage(QStringList *datalist, int index);

private slots:
    void on_P8_Color_clicked();
    void on_P7_Color_clicked();
    void on_P6_Color_clicked();
    void on_P5_Color_clicked();
    void on_P4_Color_clicked();
    void on_P3_Color_clicked();
    void on_P2_Color_clicked();
    void on_P1_Color_clicked();
    void setColorP1(const QColor & mColor);       //文本色
    void setColorP2(const QColor & mColor);       //文本色
    void setColorP3(const QColor & mColor);       //文本色
    void setColorP4(const QColor & mColor);       //文本色
    void setColorP5(const QColor & mColor);       //文本色
    void setColorP6(const QColor & mColor);       //文本色
    void setColorP7(const QColor & mColor);       //文本色
    void setColorP8(const QColor & mColor);       //文本色
};

#endif // QTRENDCHARTPENDLG_H
