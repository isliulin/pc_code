#ifndef QTRENDAPPEARANCE_H
#define QTRENDAPPEARANCE_H

#include <QWidget>
#include "qtrendachset.h"
#include "view/qtrendattr.h"

namespace Ui {
    class QTrendAppearance;
}

class QTrendAppearance : public QWidget
{
    Q_OBJECT

public:
    explicit QTrendAppearance(QWidget *parent = 0);
    ~QTrendAppearance();

private:
    Ui::QTrendAppearance *ui;

public://�������,ע�������saveʱ�������ȱ��棬��Ϊm_nCurChnnelNum������ݵ�������
    bool        m_bIsAll;       //����ȫ��
    CurveType   m_eTableType;   //ͼ������
    QString     m_sGroupNum;    //���
    short       m_nCurChnnelNum;//��ǰͨ����
    short       m_nChnnelBegin; //��ʼͨ����
    int         m_nTotalTrendNumber;   //������ͨ����
    double      m_nDisplayMax;
    double      m_nDisplayMin;
	QList<int > m_channels;//����ѡ���ͨ����
    QVector<ChannelGroupInfo> m_vecChannelGroups;//
	ChannelGroupInfo m_defaultChl;

//public:
    //bool bInit;
    //QVector<int> vecTrendTypeNum;//��ʷ���߻���ʵʱ���ߵĵ�ǰ�ı�ţ���ʼ������0

public:
    void Init(QTrendAttr *pItem);
	double getDisplayMax();
	
	double getDisplayMin();
	void initChannelPro();
	void setDefaultChl();
    bool save();
public:
        QColor cc;

private slots:
    void on_doubleSpinBox_outputMax_valueChanged(double );
    void on_doubleSpinBox_outputMin_valueChanged(double );
    void on_radioButton_single_clicked();                   //��һ
    void on_radioButton_all_clicked();                      //ȫ��
    void on_comboBox_groupNum_currentIndexChanged(int index);//��ǰ���
    //void on_radioButton_history_clicked();                  //��ʷ
    //void on_radioButton_realTime_clicked();                 //ʵʱ
    void on_doubleSpinBox_inputMax_valueChanged(double );   //1
    void on_doubleSpinBox_inputMin_valueChanged(double );   //2
    void on_comboBox_dataType_currentIndexChanged(int index);//5
    void on_pushButton_pipeSet_clicked();//ͨ������
	void setCurrentChl();
	void channelIndexChanged(QString sNumber);
	void btncolorClicked();
	void btnAddrClicked();
	void setBtnColor(const QColor &color);
	void conditionChanged(int index);
    void setAllChl(bool checked);

signals:
    void ChnnelChange(QList<int > channels);
    void TrendTypeChange(bool bIsHistoryTrend);
};

#endif // QTRENDAPPEARANCE_H
