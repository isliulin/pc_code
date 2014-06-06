#ifndef QXYTRENDCHARGENTDLG_H
#define QXYTRENDCHARGENTDLG_H

#include <QWidget>
#include "qpickercolor.h"
#include "Frame/qprogectmanager.h"
#include "ui_qxytrendchargentdlg.h"
#include "view/qgroupitem.h"

namespace Ui {
    class QXYTrendCharGentDlg;
}

class QXYTrendCharGentDlg : public QWidget
{
    Q_OBJECT

public:
    explicit QXYTrendCharGentDlg(QWidget *parent = 0);
    ~QXYTrendCharGentDlg();
    Keyboard kTrigged_address;
    Keyboard kRead_address;
    Keyboard kClear_Triggre_address;
    Keyboard checkaddr;
    QGraphicsItem *pOldItem;
    QGraphicsScene *pScene;
    QGroupItem *pBaseItem ;
    QPickerColor *pBackColor ;
    QPickerColor *pBGColor;
    Ui::QXYTrendCharGentDlg *ui;
    void Init(QGraphicsItem *pItem);
    public slots:

private:
signals:
    void GenNomberofDataChange();

private slots:
    void on_m_checkcolor_clicked();
    void on_m_ifuse_clicked(bool checked);
    void on_m_checkbtn_clicked();
    void setCheckLineColor(const QColor &mColor);
    void on_BG_Color_clicked();
    void on_BackColor_clicked();
    void on_Number_Data_valueChanged(int );
    void on_Clear_Trigged_Keybord_clicked();
    void on_Read_Address_Keybord_clicked();
    void on_Read_Triggre_Keybord_clicked();
    void setBackColorColor(const QColor & mColor);       //背景色
    void setBGColor(const QColor & mColor);       //文本色
public:
    void SaveGeneralPage(QStringList *datalist, int index);
    void InitParament();
};

#endif // QXYTRENDCHARGENTDLG_H
