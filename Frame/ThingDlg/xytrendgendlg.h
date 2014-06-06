#ifndef XYTRENDGENDLG_H
#define XYTRENDGENDLG_H

#include <QWidget>
#include "view/xytrend.h"


namespace Ui {
    class XYTrendGenDlg;
}

class XYTrendGenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit XYTrendGenDlg(QWidget *parent = 0);
    ~XYTrendGenDlg();
    void Init(XYtrend *pItem);
    void setDefaultChl();
    void setChlinfoUi(ChannelInfo chl);

    bool save();

private:
    Ui::XYTrendGenDlg *ui;
public:
    int m_chlnum;
    bool        m_bIsAll;           //����ȫ��
    int chlCount;//ͨ������
    int addrLength;//��ַ���ȣ��൱�ڲ�������

    DATA_TYPE m_dataType;//��������
    Keyboard    m_TriggerAddr;//������ַ
    bool        m_bReset;//�Ƿ��Զ���λ

    bool        m_bScale;//�Ƿ�����
    bool m_bDisplayConst;//��ʾ��Χ�Ƿ���
    Keyboard    m_DisplayMaxAddrX;//��ʾ��Χ���ֵ ��ַ
    Keyboard    m_DisplayMinAddrX;//��ʾ��Χ��Сֵ ��ַ
    double          m_nDisplayMinX;	//��ʾ��Сֵ
    double          m_nDisplayMaxX;	//��ʾ���ֵ
    bool        m_bConstX;//�Ƿ�����Χ
    Keyboard    m_SourceMaxAddrX;//Դ��Χ���ֵ ��ַ
    Keyboard    m_SourceMinAddrX;//Դ��Χ��Сֵ ��ַ
    double      m_nSourceMaxX;	//Դ��Χ���ֵ
    double      m_nSourceMinX;	//Դ��Χ��Сֵ

    bool m_bDisplayConstY;//Y��ʾ��Χ�Ƿ���
    Keyboard    m_DisplayMaxAddrY;//Y��ʾ��Χ���ֵ ��ַ
    Keyboard    m_DisplayMinAddrY;//Y��ʾ��Χ��Сֵ ��ַ
    double          m_nDisplayMinY;	//��ʾ��Сֵ
    double          m_nDisplayMaxY;	//��ʾ���ֵ
    bool        m_bConstY;//�Ƿ�����Χ
    Keyboard    m_SourceMaxAddrY;//Դ��Χ���ֵ ��ַ
    Keyboard    m_SourceMinAddrY;//Դ��Χ��Сֵ ��ַ
    double      m_nSourceMaxY;	//Դ��Χ���ֵ
    double      m_nSourceMinY;	//Դ��Χ��Сֵ

    ChannelInfo m_defaultChl;//Ĭ��ͨ������

    QVector<ChannelInfo> m_vecChannels;//����ͨ�������������
private slots:
    void on_m_BtnDisplayMaxAddrY_clicked();
    void on_m_BtnDisplayMinAddrY_clicked();
    void on_m_BtnDisplayMaxAddrX_clicked();
    void on_m_BtnDisplayMinAddrX_clicked();
    void on_m_DisplayBox_Y_currentIndexChanged(int index);
    void on_m_DisplayBox_currentIndexChanged(int index);
    void on_comboBox_dataType_currentIndexChanged(int index);
    void on_lineEdit_ctlAddr_editingFinished();
    void on_lineEdit_AddrY_editingFinished();
    void on_lineEdit_AddrX_editingFinished();
    void on_m_SourcecbBox_currentIndexChanged(int index);
    void on_m_SourcecbBox_Y_currentIndexChanged(int index);
    void on_m_sMinAddress_EntryBtn_Y_clicked();
    void on_m_sMaxAddress_EntryBtn_Y_clicked();
    void on_m_sMinAddress_EntryBtn_clicked();
    void on_m_sMaxAddress_EntryBtn_clicked();
    void on_pushButton_trigAddr_clicked();
    void on_checkBox_clicked(bool checked);
    void on_pushButton_showColor_clicked();
    void on_pushButton_ctlAddr_clicked();
    void on_pushButton_AddrY_clicked();
    void on_pushButton_AddrX_clicked();
    void onChlNumChange(int index);
    void onChlCountChange(int count);
    void onConditionChange(int index);
    void setBtnColor(const QColor &color);
    void setCurrentChl();
};

#endif // XYTRENDGENDLG_H
