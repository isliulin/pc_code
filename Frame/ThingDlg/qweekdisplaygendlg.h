#ifndef QWEEKDISPLAYGENDLG_H
#define QWEEKDISPLAYGENDLG_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "view/qgroupitem.h"
#include "qpickercolor.h"
#include "ui_qweekdisplaygendlg.h"
namespace Ui {
    class QWeekDisplayGenDlg;
}

class QWeekDisplayGenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QWeekDisplayGenDlg(QWidget *parent = 0);
    ~QWeekDisplayGenDlg();

public://private:
    Ui::QWeekDisplayGenDlg *ui;
signals:
    void GeneralStateChange();   //状态改变发出的信号
    void txtChange();
private slots:
    void on_BG_Color_clicked();
    void on_FG_Color_clicked();
    void on_Frame_Color_clicked();
    void on_LoadShape_clicked();
    void on_m_patterncmb_currentIndexChanged(int index);
    void on_m_statespin_valueChanged(int );
    void setFrameColor(const QColor & mColor);       //设置边框色
    void setFGColor(const QColor & mColor);       //前景色
    void setBGColor(const QColor & mColor);       //背景色


//    void OnSetBorderColor();
//    void OnSetFrontColor();
//    void OnSetBackColor();

public:
    QGraphicsScene *pScene; //场景
    QGraphicsItem *pOldItem;
    QGroupItem *pBaseItem;

//    QPickerColor *pBorderColor;
//    QPickerColor *pFrontColor;
//    QPickerColor *pBackColor ;
    bool InitFlag;

    struct Week
    {
        QString sBorderColor;      //边框色
        QString sFrontColor;       //前景色
        QString sBackColor;        //背景色
        int nPattern;              //样式
    }WeekDay[7];

public:
    void InitParament();
    void SaveWeekGeneralPage(QStringList *datalist, int index);
    void DoubleClickInit(QGraphicsItem *pItem);
};

#endif // QWEEKDISPLAYGENDLG_H
