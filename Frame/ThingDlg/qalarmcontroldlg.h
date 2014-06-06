#ifndef QALARMCONTROLDLG_H
#define QALARMCONTROLDLG_H

#include <QDialog>
#include "qgraphicsitem.h"
#include "view/alarmitem.h"
#include "Frame/ThingDlg/qalarmcontrolgendlg.h"

class QAlarmControlDlg : public QDialog
{
    Q_OBJECT
public:
    explicit QAlarmControlDlg(QGraphicsItem *item,QWidget *parent = 0);
    QStringList * datalist;
    ~QAlarmControlDlg();

    QVBoxLayout *mainLayout;
signals:

public slots:
    void accept();
private slots:
   void loadHelp();
private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
    void InitAllProperty(QGraphicsItem *pItem);
    SecurityWidget *pVisibilityDlg;
    QAlarmControlGenDlg *pGeneralDlg;
public:
    void DrawTable();
    AlarmItem *pCopyItem;
};

#endif // QALARMCONTROLDLG_H
