#ifndef QHISTORYDATASHOWONE_H
#define QHISTORYDATASHOWONE_H

#include <QWidget>
#include "view/qhistorydatashowattr.h"
#include "ui_qhistorydatashowone.h"

namespace Ui {
    class QHistoryDataShowOne;
}

class QHistoryDataShowOne : public QWidget
{
    Q_OBJECT

public:
    explicit QHistoryDataShowOne(QWidget *parent = 0);
    ~QHistoryDataShowOne();

//private:
    Ui::QHistoryDataShowOne *ui;

public:
    void Init(QHistoryDataShowAttr* pItem);

public:
    int m_nCurLanNum;//当前语言号
    bool bInit;

public:
    //一般
    QColor  m_nForecolor;       //前景色
    QColor  m_nFrameColor;      //边框色
    short   m_nAlpha;
    //---------------
    short   m_nTextFontSize;    //文本字体大小，默认10
    short   m_nLine;            //显示行数，默认5
    QColor  m_nTextFontColor;   //文本字体颜色，默认黑色
    //---------------
    bool    m_bShowTime;	//是否显示时间，默认显示
    bool    m_bShowDate;	//是否显示日期,默认显示
    QColor  m_nTitleBackColor;	//标题背景颜色，默认黄色
    QColor  m_nTitleFontColor;	//标题字体颜色，默认黑色
    bool    m_bShowCode;        //是否显示编号
    TIME_FORMAT	m_eTimeFormat;  //(统一时间格式枚举)时间格式 HH:MM
    DATE_FORMAT	m_eDateFormat;  //(统一时间格式枚举)日期格式 默认：DD/MM/YY
    bool    m_bAddr;            //是否需要控制地址
    Keyboard m_KeyAddr;         //控制地址
    //---------------
    QVector<HistoryTextInfo> m_vecHisText;//每种语言对应的表里内容的字体属性

private slots:
    //数据
    void on_pushButton_Ctrl_clicked();
    void on_checkBox_Ctrl_clicked(bool checked);
    void on_spinBox_valueChanged(int );
    void on_lineEdit_number_editingFinished();
    void on_spinBox_dataLine_valueChanged(int value);
    void on_spinBox_dataFontSize_valueChanged(int value);
    void on_pushButton_dataColor_clicked();
    void set_pushButton_dataColor(const QColor & mColor);

    //框
    void on_pushButton_frameColor_clicked();
    void set_pushButton_frameColor(const QColor & mColor);
    void on_pushButton_frontColor_clicked();
    void set_pushButton_frontColor(const QColor & mColor);

    //文本列
    void on_comboBox_textDateType_currentIndexChanged(int index);
    void on_checkBox_textDateb_clicked(bool checked);
    void on_comboBox_textTimeType_currentIndexChanged(int index);
    void on_checkBox_textTimeb_clicked(bool checked);
    void on_pushButton_textWordColor_clicked();
    void set_pushButton_textWordColor(const QColor & mColor);
    void on_pushButton_textBk_clicked();
    void set_pushButton_textBk(const QColor & mColor);
    void on_checkBox_textNum_clicked(bool checked);

    //标题列
    void on_lineEdit_titleDate_editingFinished();
    void on_lineEdit_titleTime_editingFinished();
    void on_comboBox_titleFontType_currentIndexChanged(int index);
    void on_spinBox_titleFontSize_valueChanged(int );
    void on_comboBox_titleLan_currentIndexChanged(int index);

signals:
    void redrawSence();
    void sigLanguageCh(int);

public slots:
    void groupCh();
    void slotLan(int lan);
};

#endif // QHISTORYDATASHOWONE_H
