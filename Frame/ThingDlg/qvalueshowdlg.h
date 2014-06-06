#ifndef QVALUESHOWDLG_H
#define QVALUESHOWDLG_H

#include <QWidget>
#include <QGraphicsItem>
#include "view/DataDisplayItem.h"

namespace Ui {
    class QValueShowDlg;
}

class QValueShowDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QValueShowDlg(QWidget *parent = 0);
    void Init(DataDisplayItem *pItem = NULL);
    int onGetTotaldigit();
    int onGetDecimaldigit();
    int onGetFontSize();//获取字体大小
    bool onGetFontType(int index);//获取字体属性 粗体 斜体 下划线
    QString onGetFont(VALUESHOWTYPE type);
    bool onDataGenSave(DataInfo &data_st);//保存数值显示信息
    bool onAsciiGenSave(ASCIIINFO &ascii_st);  //保存ascii显示信息
    ~QValueShowDlg();

public slots:
    void onTabWightSwitch(int eType);
    void setDataLength(int minlength,int naxlength,bool bInitFlag, bool bEnableDecimal);
    void getDataLength(int &nLength);

private:
    Ui::QValueShowDlg *ui;
    bool bInitFlag;
    Keyboard Monitor_Address_Keyboard;

signals:
    void onDrawSence(QString sName);
    void setDatadefault(int nLength,bool bUser);
private slots:
    void on_m_AligentCbBox_currentIndexChanged(int index);
    void on_Monitor_Address_EntryBtn_clicked();
    void on_m_sDecimalTypecbBox_currentIndexChanged(int index);
    void on_m_UnderlineckBox_clicked(bool checked);
    void on_m_ItalicckBox_clicked(bool checked);
    void on_m_BoldckBox_clicked(bool checked);
    void on_m_OrdinaryckBox_clicked(bool checked);
    void on_m_fontCbBox_currentIndexChanged(int index);
    void on_m_codeFomatcmbBox_currentIndexChanged(int index);
    void on_m_textcbBox_currentIndexChanged(int index);
    void on_m_fontSizecbBox_currentIndexChanged(int index);
    void on_m_rightAlignBtn_clicked();
    void on_m_centerAlignBtn_clicked();
    void on_m_LeftAlignBtn_clicked();
    void on_m_DecimalspBox_valueChanged(int );
    void on_m_totalspBox_valueChanged(int );
};

#endif // QVALUESHOWDLG_H
