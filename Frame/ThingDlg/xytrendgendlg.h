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
    bool        m_bIsAll;           //个别，全部
    int chlCount;//通道总数
    int addrLength;//地址长度，相当于采样点数

    DATA_TYPE m_dataType;//数据类型
    Keyboard    m_TriggerAddr;//触发地址
    bool        m_bReset;//是否自动复位

    bool        m_bScale;//是否缩放
    bool m_bDisplayConst;//显示范围是否常量
    Keyboard    m_DisplayMaxAddrX;//显示范围最大值 地址
    Keyboard    m_DisplayMinAddrX;//显示范围最小值 地址
    double          m_nDisplayMinX;	//显示最小值
    double          m_nDisplayMaxX;	//显示最大值
    bool        m_bConstX;//是否常量范围
    Keyboard    m_SourceMaxAddrX;//源范围最大值 地址
    Keyboard    m_SourceMinAddrX;//源范围最小值 地址
    double      m_nSourceMaxX;	//源范围最大值
    double      m_nSourceMinX;	//源范围最小值

    bool m_bDisplayConstY;//Y显示范围是否常量
    Keyboard    m_DisplayMaxAddrY;//Y显示范围最大值 地址
    Keyboard    m_DisplayMinAddrY;//Y显示范围最小值 地址
    double          m_nDisplayMinY;	//显示最小值
    double          m_nDisplayMaxY;	//显示最大值
    bool        m_bConstY;//是否常量范围
    Keyboard    m_SourceMaxAddrY;//源范围最大值 地址
    Keyboard    m_SourceMinAddrY;//源范围最小值 地址
    double      m_nSourceMaxY;	//源范围最大值
    double      m_nSourceMinY;	//源范围最小值

    ChannelInfo m_defaultChl;//默认通道属性

    QVector<ChannelInfo> m_vecChannels;//各个通道曲线外观设置
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
