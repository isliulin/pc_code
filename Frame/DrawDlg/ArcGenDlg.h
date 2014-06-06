#ifndef ARCGENDLG_H
#define ARCGENDLG_H

#include <QWidget>
#include "qpickercolor.h"
//#include "view/QArcItem.h"
#include "view/qarcbasicitem.h"
namespace Ui {
    class ArcGenDlg;
}

class ArcGenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit ArcGenDlg(QWidget *parent = 0);
    ~ArcGenDlg();

private:
    Ui::ArcGenDlg *ui;
public:
    QArcBasicItem *pArc;
    QArcItem *pArcOld;
    QGraphicsItem *pCopyItem;
    void saveId();
    int getId();
private:
    QPickerColor *pFrontColor;
    QPickerColor *pBackColor;
    QPickerColor *pLineColor;
    bool bInitFlag ;
private slots:
    void on_m_FrontColorBtn_clicked();
    void on_m_BackColorBtn_clicked();
    void on_m_LineColorBtn_clicked();
    void on_m_Pattern_currentIndexChanged(int index);
    void on_m_LineWidth_currentIndexChanged(int index);
    void on_m_LineType_currentIndexChanged(int index);
    void on_m_Alpha_valueChanged(int nAlpha);
    void SetLineColor(const QColor &);
    void SetBackColor(const QColor &);
    void SetFrontColor(const QColor &);
public:
    void InitParament();
    void DoubleClickInit(QGraphicsItem *pItem);
    void setItemType(int iType);
private:
    int m_iType;
};

#endif // ARCGENDLG_H
