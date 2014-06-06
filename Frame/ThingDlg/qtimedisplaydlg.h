#ifndef QTIMEDISPLAYDLG_H
#define QTIMEDISPLAYDLG_H

#include <QDialog>
#include "qtimedisplaygeneraldlg.h"

class QTimeDisplayDlg : public QDialog
{
    Q_OBJECT
public:
    explicit QTimeDisplayDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    ~QTimeDisplayDlg();
    QVBoxLayout *mainLayout;
    QStringList * datalist;
    QTimeDisplayGeneralDLg *pTimeDisplayGen;

signals:

public slots:
    void confyButton();
private slots:
   void loadHelp();
private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    void InitAllProperty(QGraphicsItem *pItem);
};

#endif // QTIMEDISPLAYDLG_H
