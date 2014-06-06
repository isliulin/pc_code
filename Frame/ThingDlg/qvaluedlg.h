#ifndef QVALUEDLG_H
#define QVALUEDLG_H

#include <QDialog>
#include <QGraphicsItem>
#include <QTabWidget>
#include "qvalueshowdlg.h"
#include "qvaluebasedlg.h"
#include "qvaluedateinputdlg.h"
#include "qvaluecolordlg.h"
#include "Frame/mainwindow.h"
#include "view/qsimpletextitem.h"
#include "view/DataDisplayItem.h"
#include "Frame/ThingDlg/switch/securitywidget.h"


namespace Ui {
    class QValueDlg;
}
class QValueScaleDlg;
class QValueDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QValueDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    void InitAllProperty(DataDisplayItem *pItem = NULL);
    void onSetFontType();
    void onSaveItemPosition();//保存控件坐标
    void setTransparent();
    ~QValueDlg();

public:
    DataDisplayItem *pCopyItem;
    QValueBaseDlg *pQvalueBace;
    QValueShowDlg *pQvalueShow;
    QValueColorDlg *pQvalueColor;
    SecurityWidget *pSecurityWight;//显现页面
    QValueDateInputDlg *pValueDateInput;
    QValueScaleDlg *pScaleWidget;

private:
    Ui::QValueDlg *ui;
    QGraphicsScene *pScene;
    QGroupItem *pBaseItem;
    bool bInitFlag;
    VALUESHOWTYPE eDataType;
    DataInfo data_st;
    ASCIIINFO ascii_st;
    TIMEINFO time_st;
    int oId;

public slots:
    void onTabWightSwitch(int eType);
    void onSetColor(QString sName);
    void onDrawSence(QString sName);
    void onAddPicture(QGraphicsItem *pItem,QPixmap* pPix,QString sPath,EITEM_TYPE eIspic);
    void confyButton();
    void loadHelp();
    void onScaleClicked(bool checked);

private:
    QTabWidget *pTabWidget;

private slots:
    void on_m_PatternckBox_clicked(bool checked);
};

#endif // QVALUEDLG_H
