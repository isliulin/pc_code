#ifndef QVALUEBASEDLG_H
#define QVALUEBASEDLG_H

#include <QWidget>
#include <QGraphicsItem>
//#include "qvaluedlg.h"
#include "view/DataDisplayItem.h"
#include "qvaluescaledlg.h"
#include "expression.h"

namespace Ui {
    class QValueBaseDlg;
}

class QValueBaseDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QValueBaseDlg(QWidget *parent = 0,QValueScaleDlg* pScaleDlg = 0);
    ~QValueBaseDlg();
    void Init(DataDisplayItem *pItem);
    bool onDateInputState();//获取数据输入checkBox的状态
    int  onGetFontSize();//获取日期的字体大小
    bool onGetFontStyl(int index);
    void onSetPreview();
    bool onDataGenSave(DataInfo &data_st);//保存数值显示信息
    bool onAsciiGenSave(ASCIIINFO &ascii_st);//保存数值显示信息
    bool onTimeGenSave(TIMEINFO &time_st);//保存时间显示信息
    bool isScaleEnable();
    QString onGetpreText();
    QString onGetFontType();
    bool getAllowInputState();
    void setdataRange(double dMax, double dMin, int type,int base);
    bool IsCanInput();
    QValueScaleDlg *pScaleWidget;
    Expression m_outExp;//监视 表达式
    Expression m_inputExp;//输入 表达式

private:
    Ui::QValueBaseDlg *ui;
    Keyboard Monitor_Address_Keyboard;
    Keyboard SMin_Address_Keyboard;
    Keyboard SMax_Address_Keyboard;
    Keyboard vMin_Address_Keyboard;
    Keyboard vMax_Address_Keyboard;
    bool bInitFlag;

signals:
    void onTabWightSwitch(int eType);
    void onDrawSence(QString sName);
    void setRange(double dMax, double dMin, int type,int base);//type: 0浮点型
    void setDataLength(int minlength,int maxlength,bool bInitFlag, bool bEnableDecimal);
    void getDataLength(int &nLength);
    void scaleClicked(bool checked);

public slots:
    void setDatadefault(int nLength, bool bUser);//bUser 表示是否用户改变长度
private slots:
    void on_btn_expression_clicked(bool checked);
    void on_check_expression_clicked(bool checked);
    void on_Offset_Address_EntryBtn_2_clicked();
    void on_Monitor_Address_textChanged(QString );
    void on_checkBox_2_clicked(bool checked);
    void on_checkBox_clicked(bool checked);
    void on_Offset_Address_EntryBtn_clicked();
    void on_btn_new_clicked();
    void on_m_MaxLimitAddress_EntryBtn_clicked();
    void on_m_MinLimitAddress_EntryBtn_clicked();
    void on_m_LimitSourcecbBox_currentIndexChanged(int index);
    void on_m_UnderlineckBox_clicked(bool checked);
    void on_m_ItalicckBox_clicked(bool checked);
    void on_m_BoldckBox_clicked(bool checked);
    void on_m_OrdinaryckBox_clicked(bool checked);
    void on_m_FontSizecbBox_currentIndexChanged(int index);
    void on_m_showMinAddress_EntryBtn_clicked();
    void on_m_showMaxAddress_EntryBtn_clicked();
    void on_m_sMinAddress_EntryBtn_clicked();
    void on_m_sMaxAddress_EntryBtn_clicked();
    void on_m_ShowcbBox_currentIndexChanged(int index);
    void on_m_SourcecbBox_currentIndexChanged(int index);
    void on_m_fontCbBox_currentIndexChanged(int index);
    void on_m_TimecbBox_currentIndexChanged(QString );
    void on_m_DatecbBox_currentIndexChanged(QString );
    void on_m_TimeckBox_clicked(bool checked);
    void on_m_WeekckBox_clicked(bool checked);
    void on_m_DateckBox_clicked(bool checked);
    void on_m_DataTypefontCmbBox_currentIndexChanged(int index);
    void on_Monitor_Address_EntryBtn_clicked();
    void on_m_AllowInputckBox_stateChanged(int );
    void on_m_AllowInputckBox_clicked(bool checked);
    void on_m_scalSetckBox_clicked(bool checked);
    void on_m_timeInputBtn_clicked();
    void on_m_dateInputBtn_clicked();
    void on_m_asciiInputBtn_clicked();
    //void libraryChanged(QString libName);
};

#endif // QVALUEBASEDLG_H
