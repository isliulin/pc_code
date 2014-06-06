#ifndef QDATEDISPLAYDLG_H
#define QDATEDISPLAYDLG_H

#include <QDialog>
#include "qdatedisplaygeneraldlg.h"

class QDateDisplayDlg : public QDialog
{
    Q_OBJECT
public:
    explicit QDateDisplayDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    ~QDateDisplayDlg();
    QStringList * datalist;
    QDateDisplayGeneralDlg *pDateDisplayGen;
    QVBoxLayout *mainLayout;
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

#endif // QDATEDISPLAYDLG_H
