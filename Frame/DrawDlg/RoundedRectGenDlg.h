#ifndef ROUNDEDRECTGENDLG_H
#define ROUNDEDRECTGENDLG_H

#include <QWidget>
//#include "view/QRoundedRect.h"
#include "qpickercolor.h"
#include "view/qroundedrectbasic.h"

namespace Ui {
    class RoundedRectGenDlg;
}

class RoundedRectGenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit RoundedRectGenDlg(QWidget *parent = 0);
    ~RoundedRectGenDlg();

private:
    Ui::RoundedRectGenDlg *ui;
public:
    QRoundedRectBasic *pRoundRect;
    QRoundedRect *pRoundRectOld;
    QGraphicsItem *pCopyItem;
private:
    QPickerColor *pFrontColor;
    QPickerColor *pBackColor;
    QPickerColor *pLineColor;
    bool bInitFlag ;
private slots:
    void on_m_FrontColorBtn_clicked();
    void on_m_BackColorBtn_clicked();
    void on_m_LineColorBtn_clicked();
    void SetLineColor(const QColor &);
    void SetBackColor(const QColor &);
    void SetFrontColor(const QColor &);
public:
    void InitParament();
    void DoubleClickInit(QGraphicsItem *pItem);
    void setItemType(int iType);
    void saveId();
private:
    int m_iType;
private slots:
    void on_m_Pattern_currentIndexChanged(int index);
    void on_m_LineWidth_currentIndexChanged(int index);
    void on_m_LineType_currentIndexChanged(int index);
    void on_m_Alpha_valueChanged(int nAlpha);
    void on_m_YR_valueChanged(int nValue);
    void on_m_XR_valueChanged(int nValue);
};

#endif // ROUNDEDRECTGENDLG_H
