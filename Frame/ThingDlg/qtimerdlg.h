#ifndef QTIMERDLG_H
#define QTIMERDLG_H

#include <QDialog>
#include "qtimergendlg.h"
class QTimerDlg : public QDialog
{
    Q_OBJECT
public:
    explicit QTimerDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    ~QTimerDlg();
    QTimerGenDlg *pGeneralDlg;
    QVBoxLayout *mainLayout;
signals:

public slots:
    void accept();
private slots:
   void loadHelp();
private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;


    QStringList * datalist;

};

#endif // QTIMERDLG_H
