#ifndef QCHARTMETER_H
#define QCHARTMETER_H

#include <QWidget>
#include "Frame/addressinputdialog.h"
#include "Frame/mainwindow.h"
#include "view/ChartItem.h"



namespace Ui {
    class QChartMeter;
}

class QChartMeter : public QWidget
{
    Q_OBJECT

public:
    explicit QChartMeter(QWidget *parent = 0);
    ~QChartMeter();
    void Init(ChartItem *pItem);
    void OnReDrawMeter();//���Ǳ�����ػ溯��
    void OnSetMeterProperty();//�����Ǳ���ɫ����ָ����ɫ�ı���Ϣ
    bool MeterGenSave(struct METER_INFORMATION &meter_st);
    void OnDrawScal(QGraphicsItemGroup *pGroup,METER_STRU meter, int nPointCount,int nFontSize,bool bShow);
    void OnDrawPointer(QGraphicsItemGroup *pGroup,METER_STRU meter,bool bShow);
    ChartItem* OnDrawMeter(QGraphicsScene *pScene,METER_STRU meter, int nPointCount,int nFontSize);
    void setdataRange(double dMax, double dMin,int type);
    Keyboard Monitor_Address_Keyboard;
    Keyboard m_minAddress_EntryBtn;
    Keyboard m_maxAddress_EntryBtn;
    QGraphicsScene *pScene;
    ChartItem *pOldItem;
    ChartItem *pChartItem;
    QGroupItem *pBaseItem;

    int nMeterType;         //�Ǳ�����
    int nPointType;         //�Ǳ�ָ������
    int nDirection;         //����
    int nMainScal;          //���̶���
    int nSubScal;           //�ο̶���
    double dMax;            //���ֵ
    double dMin;            //��Сֵ
    QString sPointColor;    //�Ǳ�ָ����ɫ
    QString sBackColor;     //�Ǳ�����ɫ

    METER_STRU meter;        //�Ǳ���Ϣ�ṹ��

signals:
  void  commonclick();
  void setRange(double dMax, double dMin, int type);//type: 0������
  void onGetShowValue(bool &bShow);//��ȡ�Ƿ���ʾ�̶�ֵ
  void onGetPointType(int &nType);//��ȡָ������

private:
    Ui::QChartMeter *ui;
    QGraphicsItem * pCopyItem;
    bool nInitFlag;

private slots:
    void on_m_TransparentspBox_valueChanged(int );
    void on_m_TransparentCKBox_clicked(bool checked);
    void on_max_numEdit_textChanged(QString );
    void on_min_numEdit_textChanged(QString );
    void on_datatype_comboBox_currentIndexChanged(int index);
    void on_m_maxAddress_EntryBtn_clicked();
    void on_m_minAddress_EntryBtn_clicked();
    void on_rang_comboBox_currentIndexChanged(int index);
    void on_direction_comboBox_currentIndexChanged(int index);
    void on_max_numEdit_lostFocus();
    void on_min_numEdit_lostFocus();
    void on_symbol_checkBox_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_Monitor_Address_EntryBtn_clicked();
    void on_m_CommonButton_2_clicked();
    void on_m_checkBox_showFrame_clicked(bool checked);
};

#endif // QCHARTMETER_H
