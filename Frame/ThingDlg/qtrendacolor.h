#ifndef QTRENDACOLOR_H
#define QTRENDACOLOR_H

#include <QWidget>
#include <color.h>
#include "Frame/ThingDlg/qtrendappearance.h"
#include "view/qtrendattr.h"

namespace Ui {
    class QTrendaColor;
}

class QTrendaColor:public QWidget
{
    Q_OBJECT

public:
    explicit QTrendaColor(QWidget *parent = 0);
    ~QTrendaColor();

private:
    Ui::QTrendaColor *ui;

public:
    int m_nTotalTrendNum;   //总通道数
    int m_nChnnelBegin;     //起始通道号

public://颜色对话框要存储的数据
    bool   m_bGrade;            //是否需要网格
    QColor m_nVerColor;         //水平网格颜色
    QColor m_nHorColor;         //垂直网格颜色
    QColor m_nBoradColor;	//边框颜色
    QColor m_nScaleColor;	//标尺颜色
    QColor m_nGraphColor;	//图表区颜色
    vector<ColorGroupInfo> m_vecGroupColor;//各个通道颜色设置

public:
    void Init(QTrendAttr *pItem);

private slots:
    void on_pushButton_horGradeColor_clicked();
    void on_pushButton_verGradeColor_clicked();
    void on_groupBox_grade_clicked(bool checked);
    void on_pushButton_tableColor_clicked();
    void on_pushButton_rulerColor_clicked();
    void on_pushButton_frameColor_clicked();
    void on_pushButton_showColor_clicked();
    void on_spinBox_lineWidth_valueChanged(int index);
    void on_comboBox_lineStyle_currentIndexChanged(int index);
    void on_comboBox_chNum_currentIndexChanged(int index);
    void set_pushButton_showColor(const QColor & mColor);
    void set_pushButton_frameColor(const QColor & mColor);
    void set_pushButton_rulerColor(const QColor & mColor);
    void set_pushButton_tableColor(const QColor & mColor);
    void set_pushButton_verGradeColor(const QColor & mColor);
    void set_pushButton_horGradeColor(const QColor & mColor);

public slots:
    void set_comboBox_chnnel_num(int, int);
};

#endif // QTRENDACOLOR_H
