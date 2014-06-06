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
    bool        m_bIsAll;                       //个别，全部
    QString     m_sCurChnnel;                   //当前组名
    double      m_nDisplayMax;
    double      m_nDisplayMin;
    QString     m_sChnnelBegin;                 //起始组名
    int         m_nTotalTrendNumber;            //曲线总组数
    QVector<ChannelGroupInfo> m_vecChannelGroups;//各个通道曲线外观设置
    QVector<DisplayGroupInfo> m_vecDisplayGroups;//各个通道控制字地址设置

    ChannelGroupInfo m_defaultChl;

    QVector<QString >m_selGroups;//选中的组号
public:
    int begin;
    QVector<int> vecGroupNum;//每个实时曲线的组号保存在里面，所有数据采集的，数据群组只针对实时曲线

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
    //void on_pushButton_ctlAddr_clicked();                   //显示ON/OFF地址按钮
    //void on_lineEdit_ctlAddr_editingFinished();             //显示ON/OFF地址
    //void on_comboBox_showCondition_currentIndexChanged(int index);//显示条件
   // void on_comboBox_pipeNum_currentIndexChanged(int index);//当前组号
    void on_radioButton_single_clicked();                   //个别
    void on_radioButton_all_clicked();                      //全部
    void on_doubleSpinBox_inputMax_valueChanged(double );   //1
    void on_doubleSpinBox_inputMin_valueChanged(double );   //2
    void on_comboBox_dataType_currentIndexChanged(int index);//5
    void on_pushButton_groupSet_clicked();//组设置
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
