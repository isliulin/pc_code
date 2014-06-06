#ifndef QHISTRENDDISPLAYGENDLG_H
#define QHISTRENDDISPLAYGENDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include "ui_qhistrenddisplaygendlg.h"
#include "view/qgroupitem.h"
namespace Ui {
    class QHisTrendDisplayGenDlg;
}

class QHisTrendDisplayGenDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QHisTrendDisplayGenDlg(QWidget *parent = 0);
    ~QHisTrendDisplayGenDlg();
    ///ÑÕÉ«
    void Init(QGraphicsItem *pItem);

    Ui::QHisTrendDisplayGenDlg *ui;

    QGraphicsItem *pOldItem;
    Keyboard checkaddr;
    Keyboard kControl_Address_Keyboard;
private:
signals:
    void GenNomberofDataChange();
public slots:

private slots:
    void on_bIfControlAddress_clicked();
    void on_kControlbtn_clicked();
    void on_m_checkbtn_clicked();
    void on_m_checkcolor_clicked();
    void on_m_ifuse_clicked(bool checked);
    void on_BGColor_clicked();
    void on_BackColor_clicked();
    void on_NumberofCurve_currentIndexChanged(int index);
    void setBackColor(const QColor & mColor);       //±³¾°É«
    void setBGColor(const QColor & mColor);       //µ×É«
    void setCheckLineColor(const QColor &mColor);
public:
    void InitParament();
    void SaveGeneralPage(QStringList *datalist, int index);
};

#endif // QHISTRENDDISPLAYGENDLG_H
