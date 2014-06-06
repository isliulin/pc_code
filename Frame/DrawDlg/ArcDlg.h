#ifndef ARCDLG_H
#define ARCDLG_H

#include <QDialog>
#include "ArcGenDlg.h"

class ArcDlg : public QDialog
{
    Q_OBJECT
public:
    explicit ArcDlg(QGraphicsItem *item,QWidget *parent = 0);

    ArcGenDlg *pGeneralDlg;
private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    SecurityWidget* pSecurity;
    int oId;
signals:

public slots:
    void accept();
private slots:
   void loadHelp();

};

#endif // ARCDLG_H
