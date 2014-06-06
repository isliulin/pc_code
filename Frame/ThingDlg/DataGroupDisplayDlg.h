#ifndef DATAGROUPDISPLAYDLG_H
#define DATAGROUPDISPLAYDLG_H

#include <QDialog>
#include "DataGroupDisplayGenDlg.h"
#include "qtrendchartpendlg.h"
#include "qtrendchartxydlg.h"
#include "qvisibilitydlg.h"
#include <QGraphicsItem>

class DataGroupDisplayDlg : public QDialog
{
    Q_OBJECT
public:
    explicit DataGroupDisplayDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    ~DataGroupDisplayDlg();

signals:   
public:
    DataGroupDisplayGenDlg *TrendChartGenDlg;
    QTrendChartPenDlg *TrendChartPenDlg;
    QTrendChartXYDlg *TrendChartXYDlg;
    QVisibilityDlg *VisibilityDlg;
    QVBoxLayout *mainLayout;
    QGraphicsItem* pCopyItem;
private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    QStringList * datalist;
public slots:
    void ChangePenAmount();
    void confyButton();
private slots:
   void loadHelp();

};

#endif // DATAGROUPDISPLAYDLG_H
