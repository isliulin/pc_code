#ifndef QTRENDBDISPAREA_H
#define QTRENDBDISPAREA_H

#include <QWidget>
#include "view/qtrenddatagroupattr.h"

namespace Ui {
    class QTrendbDispArea;
}

class QTrendbDispArea : public QWidget
{
    Q_OBJECT

public:
    explicit QTrendbDispArea(QWidget *parent = 0);
    ~QTrendbDispArea();

private:
    Ui::QTrendbDispArea *ui;

public://��ʾ������
    bool    m_bSelectVertMinor;	//�Ƿ���ʾ��ֱ�α��
    bool    m_bSelectHorMinor;	//�Ƿ���ʾˮƽ�α��
    bool    m_bMainVer;         //�Ƿ���ʾ��ֱ�����
    bool    m_bMainHor;         //�Ƿ���ʾˮƽ�����
    short   m_nDataSample;	//����������
    short   m_nVertMajorScale;	//��ֱ�����
    short   m_nVertMinorScale;	//��ֱ�α��
    short   m_nHorMajorScale;	//ˮƽ�����
    short   m_nHorMinorScale;	//ˮƽ�α��

public://��ɫ�Ի���Ҫ�洢������
    bool   m_bGrade;            //�Ƿ���Ҫ����
    QColor m_nVerColor;         //ˮƽ������ɫ
    QColor m_nHorColor;         //��ֱ������ɫ
    QColor m_nBoradColor;	//�߿���ɫ
    QColor m_nScaleColor;	//�����ɫ
    QColor m_nGraphColor;	//ͼ������ɫ
    QColor m_nMarkedColor; //��ע��ɫ
    short   m_nFontSize;    //�����С
    int    m_alpha;

public:
    void Init(QTrendDataGroupAttr *pItem);
    short getFontSize();
    int getAlpha();
private slots:
    void on_checkBox_horiz_clicked(bool checked);
    void on_checkBox_vertical_clicked(bool checked);
    void set_pushButton_markColor(const QColor & Color);
    void on_pushButton_markColor_clicked();
    void on_spinBox_horizSub_valueChanged(int );
    void on_spinBox_verticalSub_valueChanged(int );
    void on_checkBox_horizSub_clicked(bool checked);
    void on_checkBox_verticalSub_clicked(bool checked);
    void on_spinBox_horizMain_valueChanged(int );
    void on_spinBox_verticalMain_valueChanged(int );
    void on_spinBox_dataSampleNum_valueChanged(int );
private slots:
    void on_pushButton_horGradeColor_clicked();
    void on_pushButton_verGradeColor_clicked();
    void on_groupBox_grade_clicked(bool checked);
    void on_pushButton_tableColor_clicked();
    void on_pushButton_rulerColor_clicked();
    void on_pushButton_frameColor_clicked();

    void set_pushButton_frameColor(const QColor & mColor);
    void set_pushButton_rulerColor(const QColor & mColor);
    void set_pushButton_tableColor(const QColor & mColor);
    void set_pushButton_verGradeColor(const QColor & mColor);
    void set_pushButton_horGradeColor(const QColor & mColor);

};

#endif // QTRENDBDISPAREA_H
