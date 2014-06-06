#ifndef ALARMBARDLG_H
#define ALARMBARDLG_H

#include <QDialog>
#include "Frame/ThingDlg/switch/securitywidget.h"
#include "Frame/ThingDlg/qdynalarmbargendlg.h"
namespace Ui {
    class AlarmbarDlg;
}

class AlarmbarDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmbarDlg(QGraphicsItem *pItem,QWidget *parent = 0);
    ~AlarmbarDlg();

    QDynAlarmBarGenDlg * pDynAlarmBarGen;
    SecurityWidget *pSecurityWight;//œ‘œ÷“≥√Ê

    void accept();

private:
    Ui::AlarmbarDlg *ui;
    QGraphicsScene scene;
    QGraphicsItem *item;
    void InitAllProperty();
    int oId;

private slots:
    void on_buttonBox_helpRequested();
    void on_buttonBox_accepted();
};

#endif // ALARMBARDLG_H
