#ifndef QTRENDCHARTGENDLG_H
#define QTRENDCHARTGENDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include "Frame/qprogectmanager.h"
#include "ui_qtrendchartgendlg.h"
#include <QGraphicsScene>
#include "view/qgroupitem.h"
#include <QGraphicsItem>
namespace Ui {
    class QTrendChartGenDlg;
}

class QTrendChartGenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QTrendChartGenDlg(QWidget *parent = 0);
    ~QTrendChartGenDlg();
    ///颜色
    QPickerColor *pBackColor ;
    QPickerColor *pBGColor;

    Ui::QTrendChartGenDlg *ui;
    Keyboard kTrigged_address;
    Keyboard kRead_address;
    Keyboard kClear_Triggre_address;
    Keyboard checkaddr;
    Keyboard KPerDataVariableaddr;
    Keyboard Control_Address_Keyboard;

    void Init(QGraphicsItem *pItem);

    QGraphicsItem *pOldItem;
  private:
    QButtonGroup *R_Direction_Group;
signals:
    void GenNomberofDataChange();
public slots:

private slots:
    void on_Control_Add_Keyboard_clicked();
    void on_If_Use_Control_Add_clicked(bool checked);
    void on_Per_Data_Variable_keyboardBtn_clicked();
    void on_If_Per_Data_Variable_clicked();
    void on_m_checkbtn_clicked();
    void on_m_checkcolor_clicked();
    void on_m_ifuse_clicked(bool checked);
    void on_BG_Color_clicked();
    void on_BackColor_clicked();
    void on_Number_Data_valueChanged(int );
    void on_Clear_Trigged_Keybord_clicked();
    void on_Read_Address_Keybord_clicked();
    void on_Read_Triggre_Keybord_clicked();
    void setBackColorColor(const QColor & mColor);       //背景色
    void setBGColor(const QColor & mColor);       //文本色
    void setCheckLineColor(const QColor &mColor);

public:
    void SaveGeneralPage(QStringList *datalist, int index);
    void InitParament();
};

#endif // QTRENDCHARTGENDLG_H
