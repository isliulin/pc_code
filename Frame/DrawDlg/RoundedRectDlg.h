#ifndef ROUNDEDRECTDLG_H
#define ROUNDEDRECTDLG_H

#include <QDialog>
#include "RoundedRectGenDlg.h"

class RoundedRectDlg : public QDialog
{
    Q_OBJECT
public:
    explicit RoundedRectDlg(QGraphicsItem *item,QWidget *parent = 0);

    RoundedRectGenDlg *pGeneralDlg; //◊¥Ã¨…Ë÷√“≥√Ê

private:

    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;

    SecurityWidget* pSecurity;
signals:

public slots:
    void accept();
private slots:
   void loadHelp();
};

#endif // ROUNDEDRECTDLG_H
