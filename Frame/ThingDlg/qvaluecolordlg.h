#ifndef QVALUECOLORDLG_H
#define QVALUECOLORDLG_H

#include <QWidget>
#include <QGraphicsItem>
#include "view/DataDisplayItem.h"

namespace Ui {
    class QValueColorDlg;
}

class QValueColorDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QValueColorDlg(QWidget *parent = 0);
    void onGetValueColor(QColor &mColor);
    void onGetValueBackColor(QColor &mColor);
    void onGetLowColor(QColor &mColor);
    void onGetHightColor(QColor &mColor);
    void onDataGenSave(DataInfo &data_st);
    void onAsciiGenSave(ASCIIINFO &ascii_st);
    void onTimeGenSave(TIMEINFO &time_st);//保存时间显示信息
    void onSelectpicbtn(int nType);//0:外部图片 1：图库图片
    int onGetTransparent();
    ~QValueColorDlg();

public slots:
    void setdataRange(double dMax, double dMin,int type,int base);
    void onTabWightSwitch(int eType);
    void Init(DataDisplayItem *pItem = NULL);

private:
    Ui::QValueColorDlg *ui;
    bool bInitFlag;
    QGraphicsItem *pLibItem;
    QPixmap newimage;

private slots:
    void on_m_TransparentspBox_valueChanged(int );
    void on_m_SelectPicpushBtn_clicked();
    void on_m_SelectLibpushBtn_clicked();
    void on_m_deletepicbtn_clicked();
    void on_m_HightColorBtn_clicked();
    void on_m_LowColorBtn_clicked();
    void on_m_DataBackColorBtn_clicked();
    void on_m_DataColorBtn_clicked();
signals:
    void onDrawSence(QString sName);
    void addPicture(QGraphicsItem* pItem,QPixmap* picture,QString sPath,EITEM_TYPE eIspic);
public slots:
    void onSetValueColor(const QColor &mColor);
    void onSetValueBackColor(const QColor &mColor);
    void onSetLowColor(const QColor &mColor);
    void onSetHightColor(const QColor &mColor);
};

#endif // QVALUECOLORDLG_H
