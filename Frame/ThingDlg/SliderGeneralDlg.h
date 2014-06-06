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
    ///��ɫ
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


    bool bIfShow;        //�Ƿ�����
    bool bIfSelectColor; //��ɫ�Ƿ����ı�
    bool bIfAxis;        //�Ƿ�ѡ������
    bool bScaleMark;     //�Ƿ�ѡ���˿̶ȱ�ʾ

    QString sColor;       //��ɫ
    int nMainScal;       //���̶���
    int nSubScal;        //�ο̶���
    double dMax;         //���ֵ
    double dMin;         //��Сֵ
    int nTotalNum;       //��λ��
    int nPointNum;       //С��λ��
    int nFontSize;       //�����С
    int nFontIndex;      //��ѡ�����±�

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
    //�̶�
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
