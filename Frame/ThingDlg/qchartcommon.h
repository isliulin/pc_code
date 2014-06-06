#ifndef QCHARTCOMMON_H
#define QCHARTCOMMON_H

#include <QWidget>
#include "Frame/addressinputdialog.h"
#include "view/ChartItem.h"


namespace Ui {
    class QChartCommon;
}

class QChartCommon : public QWidget
{
    Q_OBJECT

public:
    explicit QChartCommon(QWidget *parent = 0);
    ~QChartCommon();
    void Init(ChartItem *pItem = NULL);
    bool CommonGenSave(struct COMMON_INFORMATION &common_st);
    void setdataRange(double dMax, double dMin,int type);
    QGraphicsItem * pCopyItem;
    Keyboard Monitor_Address_Keyboard;
    Keyboard m_minAddress_EntryBtn;
    Keyboard m_maxAddress_EntryBtn;
    bool holecheck;
    int ndirection;//��״ͼ��ʾ����
    int nShapeType;//ͼ������ 0��[��״ͼ]��1��[Բ��ͼ]��2��[��Բͼ]�� 3��[��״ͼ]

signals:
    void meterclick();//�Ǳ�ťѡ�з��͸���Ϣ����tab��ǩҳ
    void directionchange();//����ı䷢����Ϣ
    void setCommonShapeType();//������ͨͼ�����͸ı���Ϣ
    void drawCenterCircle(bool bCircle, int nRadiu);
    void setRange(double dMax, double dMin, int type);//type: 0������
    void reDrawBar();//�������»�����״ͼ����ͼ��Ϣ
    void enablePointType(bool bable);//true ����   false ����

private:
    Ui::QChartCommon *ui;
    bool bInitFlag;
    bool bValueChange;//�Ƿ��Ͱ뾶�ı���Ϣ

public slots:
    void onGetDirection(int &nIndex);
    void onGetroleCheck(bool &bCheck, int &nRadius);
    void onGetdataRange(double &dMin, double &dMax);//��ȡ�����Сֵ
    void onGetPointType(int &nType);//��ȡԲ�Ƿ�ָ�룬0����ʾ��䣬1����ʾָ��
    void onGetStartAngle(short &nStart,short &nSpan);
    void onGetCircleAlpha(short &nAlpha);
    void onGetShowFrame(bool &bShowFrame);
private slots:
    void on_m_SpanAngleSpBox_valueChanged(int );
    void on_m_StartAngleSpBox_valueChanged(int );
    void on_max_numEdit_textChanged(QString );
    void on_min_numEdit_textChanged(QString );
    void on_start_Checkbox_clicked(bool checked);
    void on_Date_type_currentIndexChanged(int index);
    void on_hole_Checkbox_clicked(bool checked);
    void on_radiu_Spinbox_valueChanged(int );
    void on_filling_Checkbox_clicked(bool checked);
    void on_m_maxAddress_EntryBtn_clicked();
    void on_m_minAddress_EntryBtn_clicked();
    void on_range_Combox_currentIndexChanged(int index);
    void on_direct_Combobox_currentIndexChanged(int index);
    void on_type_Combobox_currentIndexChanged(int index);
    void on_symbol_checkBox_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_Monitor_Address_EntryBtn_clicked();
    void on_m_CommonButton_2_clicked();
    void on_m_MeterButton_2_clicked();

    void on_m_checkBox_showFrame_clicked(bool checked);
    void on_m_TransparentspBox_valueChanged(int );
};

#endif // QCHARTCOMMON_H
