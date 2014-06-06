#ifndef QHISTRENDDISPLAYDLG_H
#define QHISTRENDDISPLAYDLG_H

#include <QDialog>
#include "qhistrenddisplaygendlg.h"
#include "qhistrenddisplaypendlg.h"
#include "qhistrenddisplayxydlg.h"
#include <QGraphicsItem>
#include "Frame/ThingDlg/qvisibilitydlg.h"
class QHisTrendDisplayDlg : public QDialog
{
    Q_OBJECT
public:
    explicit QHisTrendDisplayDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    ~QHisTrendDisplayDlg();
    QVBoxLayout *mainLayout;
    QHisTrendDisplayGenDlg *HisTrendDisplayGenDlg;
    QHisTrendDisplayPenDlg *HisTrendDisplayPenDlg;
    QHisTrendDisplayXYDlg  *HisTrendDisplayXYDlg;
    QVisibilityDlg *VisibilityDlg;


    void InitAllProperty(QGraphicsItem *pItem);

signals:

public slots:
   void ChangePenAmount();
   void accept();
private slots:
   void loadHelp();
private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    QStringList * datalist;
public:
    QGraphicsItem *pCopyItem;

};

#endif // QHISTRENDDISPLAYDLG_H
