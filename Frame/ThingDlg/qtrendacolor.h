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
    int m_nTotalTrendNum;   //��ͨ����
    int m_nChnnelBegin;     //��ʼͨ����

public://��ɫ�Ի���Ҫ�洢������
    bool   m_bGrade;            //�Ƿ���Ҫ����
    QColor m_nVerColor;         //ˮƽ������ɫ
    QColor m_nHorColor;         //��ֱ������ɫ
    QColor m_nBoradColor;	//�߿���ɫ
    QColor m_nScaleColor;	//�����ɫ
    QColor m_nGraphColor;	//ͼ������ɫ
    vector<ColorGroupInfo> m_vecGroupColor;//����ͨ����ɫ����

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
