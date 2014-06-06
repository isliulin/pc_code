#ifndef QTRENDADISPLAY_H
#define QTRENDADISPLAY_H

#include <QWidget>
#include "view/qtrendattr.h"
#include "view/xytrend.h"
#include "Frame/ThingDlg/qtrendappearance.h"

namespace Ui {
    class QTrendadisplay;
}

class QTrendadisplay : public QWidget
{
    Q_OBJECT

public:
    explicit QTrendadisplay(QWidget *parent = 0);
    ~QTrendadisplay();

public:
    int m_nTotalTrendNum;   //总通道数,临时变量，不存储
    int m_nChnnelBegin;     //起始通道号,临时变量，不存储

private:
    Ui::QTrendadisplay *ui;

public://显示区设置
    bool    m_bSelectVertMinor;	//是否显示垂直次标尺
    bool    m_bSelectHorMinor;	//是否显示水平次标尺
    bool    m_bMainVer;         //是否显示垂直主标尺
    bool    m_bMainHor;         //是否显示水平主标尺
    short   m_nDataSample;	//数据样本数
    short   m_nScrollSample;	//滚动样本数
    short   m_nVertMajorScale;	//垂直主标尺
    short   m_nVertMinorScale;	//垂直次标尺
    short   m_nHorMajorScale;	//水平主标尺
    short   m_nHorMinorScale;	//水平次标尺

    bool   m_bGrade;            //是否需要网格
    QColor m_nVerColor;         //水平网格颜色
    QColor m_nHorColor;         //垂直网格颜色
    QColor m_nBoradColor;	//边框颜色
    QColor m_nScaleColor;	//标尺颜色
    QColor m_nGraphColor;	//图表区颜色
    QColor m_textColor;//刻度的文本色
    int    m_textSize;//刻度的文本大小
    int    m_alpha;

    vector<DisplayGroupInfo> m_vecDisplayGroups;//各个通道曲线外观设置

public:
    void Init(QTrendAttr *pItem);
    void InitXY(XYtrend *pItem);
    int getAlpha();
    void set_TextProVisible(bool bValue);
    int textSize();
private slots:
    void on_pushButton_clicked();
    void on_spinBox_dataSampleNum_editingFinished();
    void on_checkBox_horiz_clicked(bool checked);
    void on_checkBox_vertical_clicked(bool checked);
    void on_spinBox_horizSub_valueChanged(int );
    void on_spinBox_verticalSub_valueChanged(int );
    void on_checkBox_horizSub_clicked(bool checked);
    void on_checkBox_verticalSub_clicked(bool checked);
    void on_spinBox_horizMain_valueChanged(int );
    void on_spinBox_verticalMain_valueChanged(int );
    void on_lineEdit_showAddr_editingFinished();
    void on_pushButton_showAddr_clicked();
    void on_comboBox_showCondition_currentIndexChanged(int index);
    void on_comboBox_channelNum_currentIndexChanged(int index);
    void on_spinBox_rollSampleNum_valueChanged(int value);
    void on_spinBox_dataSampleNum_valueChanged(int value);

private slots:
	void on_pushButton_horGradeColor_clicked();
	void on_pushButton_verGradeColor_clicked();
	void set_pushButton_verGradeColor(const QColor & mColor);
	void set_pushButton_horGradeColor(const QColor & mColor);

	void on_groupBox_grade_clicked(bool checked);
	void on_pushButton_tableColor_clicked();
	void on_pushButton_rulerColor_clicked();
	void on_pushButton_frameColor_clicked();
	void set_pushButton_frameColor(const QColor & mColor);
	void set_pushButton_rulerColor(const QColor & mColor);
	void set_pushButton_tableColor(const QColor & mColor);
    void set_BtnTextColor(const QColor &Color);
	
	

public slots:
    void set_comboBox_chnnel_num(int, int);
};

#endif // QTRENDADISPLAY_H
