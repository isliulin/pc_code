#ifndef SLIDERGENERALDLG_H
#define SLIDERGENERALDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include <QGraphicsScene>
#include "ui_SliderGeneralDlg.h"
#include "view/SliderItem.h"
//#include "Frame/ThingDlg/Slider.h"

namespace Ui {
    class SliderGeneralDlg;
}

class SliderGeneralDlg : public QWidget
{
    Q_OBJECT

public:
    explicit SliderGeneralDlg(QWidget *parent = 0);
    ~SliderGeneralDlg();
signals:
    void ReDrawSlider();
public:
    Ui::SliderGeneralDlg *ui;
private:
    bool bInitFlag;

public:
    ///颜色
    QPickerColor *pBackColor;
    QPickerColor *pLineColor;
    QPickerColor *pBkColor ;
    QPickerColor *pFrmColor;
    QGraphicsScene *pScene;
    QButtonGroup *RadioButton;

    Keyboard WriteAddr;
    Keyboard MinAddr;
    Keyboard MaxAddr;
    SliderItem *pCopyItem;


    bool bIfShow;        //是否显现
    bool bIfSelectColor; //颜色是否发生改变
    bool bIfAxis;        //是否选择了轴
    bool bScaleMark;     //是否选择了刻度标示

    QString sColor;       //颜色
    int nMainScal;       //主刻度数
    int nSubScal;        //次刻度数
    double dMax;         //最大值
    double dMin;         //最小值
    int nTotalNum;       //总位数
    int nPointNum;       //小数位数
    int nFontSize;       //字体大小
    int nFontIndex;      //所选字体下标

    double maxNum;
    double minNum;
private slots:
    void on_m_maxedit_2_textChanged(QString );
    void on_m_minedit_2_textChanged(QString );
    void on_checkBox_clicked();
    void on_m_frmcolorbtn_clicked();
    void on_m_bkcolorbtn_clicked();
    void on_m_linecolorbtn_clicked();
    void on_m_backcolorbtn_clicked();
    void on_m_datatypecmb_currentIndexChanged(int index);
    void on_m_directcmb_currentIndexChanged(int index);
    void on_m_addrbtn_clicked();
    void on_m_minbtn_clicked();
    void on_m_maxbtn_clicked();
    void OnDirectRadioChange(int nChecked);
    //刻度
    void on_m_totalnumberspin_valueChanged(int );
    void on_m_colorbtn_clicked();
    void on_m_pointnumberspin_valueChanged(int );
    void on_m_fontsizecmb_currentIndexChanged(int index);
    void on_m_subscalspin_valueChanged(int );
    void on_m_mainscalspin_valueChanged(int );
    void on_m_scalemarkcheck_clicked();
    void on_m_displaycheck_clicked();

    void OnSetColor(const QColor &);

private slots:
    void on_checkBox_clicked(bool checked);
    void OnSetBackColor(const QColor &);
    void OnSetLineColor(const QColor &);
    void OnSetBkColor(const QColor &);
    void OnSetFrmColor(const QColor &);
public:
    void InitParament();
    bool SaveGeneralPage(SliderInfo &m_slider);
    void DoubleClickInit(SliderItem *pItem);
};

#endif // SLIDERGENERALDLG_H
