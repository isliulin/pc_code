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

public://曲线外观,注意这个在save时必须最先保存，因为m_nCurChnnelNum这个数据的特殊性
    bool        m_bIsAll;       //个别，全部
    CurveType   m_eTableType;   //图表类型
    QString     m_sGroupNum;    //组号
    short       m_nCurChnnelNum;//当前通道号
    short       m_nChnnelBegin; //起始通道号
    int         m_nTotalTrendNumber;   //曲线总通道数
    double      m_nDisplayMax;
    double      m_nDisplayMin;
	QList<int > m_channels;//所有选择的通道号
    QVector<ChannelGroupInfo> m_vecChannelGroups;//
	ChannelGroupInfo m_defaultChl;

//public:
    //bool bInit;
    //QVector<int> vecTrendTypeNum;//历史曲线或者实时曲线的当前的编号，起始可以是0

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
    void on_radioButton_single_clicked();                   //单一
    void on_radioButton_all_clicked();                      //全部
    void on_comboBox_groupNum_currentIndexChanged(int index);//当前组号
    //void on_radioButton_history_clicked();                  //历史
    //void on_radioButton_realTime_clicked();                 //实时
    void on_doubleSpinBox_inputMax_valueChanged(double );   //1
    void on_doubleSpinBox_inputMin_valueChanged(double );   //2
    void on_comboBox_dataType_currentIndexChanged(int index);//5
    void on_pushButton_pipeSet_clicked();//通道设置
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
