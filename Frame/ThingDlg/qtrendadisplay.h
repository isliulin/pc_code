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
    int m_nTotalTrendNum;   //��ͨ����,��ʱ���������洢
    int m_nChnnelBegin;     //��ʼͨ����,��ʱ���������洢

private:
    Ui::QTrendadisplay *ui;

public://��ʾ������
    bool    m_bSelectVertMinor;	//�Ƿ���ʾ��ֱ�α��
    bool    m_bSelectHorMinor;	//�Ƿ���ʾˮƽ�α��
    bool    m_bMainVer;         //�Ƿ���ʾ��ֱ�����
    bool    m_bMainHor;         //�Ƿ���ʾˮƽ�����
    short   m_nDataSample;	//����������
    short   m_nScrollSample;	//����������
    short   m_nVertMajorScale;	//��ֱ�����
    short   m_nVertMinorScale;	//��ֱ�α��
    short   m_nHorMajorScale;	//ˮƽ�����
    short   m_nHorMinorScale;	//ˮƽ�α��

    bool   m_bGrade;            //�Ƿ���Ҫ����
    QColor m_nVerColor;         //ˮƽ������ɫ
    QColor m_nHorColor;         //��ֱ������ɫ
    QColor m_nBoradColor;	//�߿���ɫ
    QColor m_nScaleColor;	//�����ɫ
    QColor m_nGraphColor;	//ͼ������ɫ
    QColor m_textColor;//�̶ȵ��ı�ɫ
    int    m_textSize;//�̶ȵ��ı���С
    int    m_alpha;

    vector<DisplayGroupInfo> m_vecDisplayGroups;//����ͨ�������������

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
