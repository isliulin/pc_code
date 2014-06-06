#ifndef TABLEDLG_H
#define TABLEDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include <QGraphicsScene>
#include "view/qgroupitem.h"
#include "view/QtableItem.h"

namespace Ui {
    class TableDlg;
}

class TableDlg : public QWidget
{
    Q_OBJECT

public:
    explicit TableDlg(QWidget *parent = 0);
    ~TableDlg();

private:
    Ui::TableDlg *ui;
    int oId;
private:

    QPickerColor *pBorderColor;
    QPickerColor *pLineColor;
    QPickerColor *pBackColor ;
    QVector<qreal> vVLine;              //用来存垂直线的数据
    QVector<qreal> vHLine;             //用来存水平线的数据

private:
    bool bInitFlag;
    QGraphicsScene *pScene;
    QGroupItem *pBaseItem;

public:
    QTableItem *pOldItem;
    void InitParament();
    void DrawTable();
    bool SaveGeneralPage(QStringList *datalist,int index);
    void DoubleClickInit(QGraphicsItem *pItem);
private slots:
    void on_m_TransparentspBox_valueChanged(int );
    void on_m_linecolorbtn_clicked();
    void on_m_bordercolorbtn_clicked();
    void on_m_backcolorbtn_clicked();
    void on_m_linetypecmb_currentIndexChanged(int index);
    void on_m_vcheck_clicked(bool checked);
    void on_m_hcheck_clicked(bool checked);
    void on_m_Vnumberspin_valueChanged(int );
    void on_m_hnumberspin_valueChanged(int );
    void on_m_bordercheck_clicked();
    void OnSetBackColor(const QColor &);
    void OnSetBorderColor(const QColor &);
    void OnSetLineColor(const QColor &);
    void on_btnAddr_const_H_clicked();
    void on_btnAddr_const_V_clicked();
    void on_check_const_H_clicked();
    void on_check_const_V_clicked();
};

#endif // TABLEDLG_H
