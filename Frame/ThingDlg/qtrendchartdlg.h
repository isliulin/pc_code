#ifndef QTRENDCHARTDLG_H
#define QTRENDCHARTDLG_H

#include <QDialog>
#include "qtrendchartgendlg.h"
#include "qtrendchartpendlg.h"
#include "qtrendchartxydlg.h"
#include "qvisibilitydlg.h"

class QTrendChartDlg : public QDialog
{
    Q_OBJECT
public:
    explicit QTrendChartDlg(QGraphicsItem *pItem, QWidget *parent = 0);
    ~QTrendChartDlg();
    QVBoxLayout *mainLayout;
    QTrendChartGenDlg *TrendChartGenDlg;
    QTrendChartPenDlg *TrendChartPenDlg;
    QTrendChartXYDlg *TrendChartXYDlg;

    QVisibilityDlg *VisibilityDlg;

signals:
public slots:
    void ChangePenAmount();
    void confyButton();
private slots:
   void loadHelp();
private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    QStringList * datalist;
public :
        QGraphicsItem* pCopyItem;

         void InitAllProperty(QGraphicsItem *pItem);
};

#endif // QTRENDCHARTDLG_H
