#ifndef QTRENDBTABLE_H
#define QTRENDBTABLE_H

#include <QWidget>
#include "qtrendappearance.h"
#include "view/qtrenddatagroupattr.h"

namespace Ui {
    class QTrendbTable;
}

class QTrendbTable : public QWidget
{
    Q_OBJECT

public:
    explicit QTrendbTable(QWidget *parent = 0);
    ~QTrendbTable();

private:
    Ui::QTrendbTable *ui;

public:
    bool        m_bIsAll;                       //����ȫ��
    QString     m_sCurChnnel;                   //��ǰ����
    double      m_nDisplayMax;
    double      m_nDisplayMin;
    QString     m_sChnnelBegin;                 //��ʼ����
    int         m_nTotalTrendNumber;            //����������
    QVector<ChannelGroupInfo> m_vecChannelGroups;//����ͨ�������������
    QVector<DisplayGroupInfo> m_vecDisplayGroups;//����ͨ�������ֵ�ַ����

    ChannelGroupInfo m_defaultChl;

    QVector<QString >m_selGroups;//ѡ�е����
public:
    int begin;
    QVector<int> vecGroupNum;//ÿ��ʵʱ���ߵ���ű��������棬�������ݲɼ��ģ�����Ⱥ��ֻ���ʵʱ����

public:
    void Init(QTrendDataGroupAttr *pItem);
    void initChannelPro();
    void setDefaultChl();
	double getDisplayMax();
	double getDisplayMin();
    bool save();
private slots:
    void on_doubleSpinBox_outputMax_valueChanged(double );
    void on_doubleSpinBox_outputMin_valueChanged(double );
    //void on_pushButton_ctlAddr_clicked();                   //��ʾON/OFF��ַ��ť
    //void on_lineEdit_ctlAddr_editingFinished();             //��ʾON/OFF��ַ
    //void on_comboBox_showCondition_currentIndexChanged(int index);//��ʾ����
   // void on_comboBox_pipeNum_currentIndexChanged(int index);//��ǰ���
    void on_radioButton_single_clicked();                   //����
    void on_radioButton_all_clicked();                      //ȫ��
    void on_doubleSpinBox_inputMax_valueChanged(double );   //1
    void on_doubleSpinBox_inputMin_valueChanged(double );   //2
    void on_comboBox_dataType_currentIndexChanged(int index);//5
    void on_pushButton_groupSet_clicked();//������
    void setCurrentChl();
    void channelIndexChanged(QString sNumber);
    void btncolorClicked();
    void btnAddrClicked();
    void setBtnColor(const QColor &color);
    void conditionChanged(int index);
    void setAllChl(bool checked);
signals:
    void ChnnelChange(int groupBegin, int totalGroupNum);
};

#endif // QTRENDBTABLE_H
