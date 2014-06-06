#ifndef ALARMLISTDLG_H
#define ALARMLISTDLG_H

#include <QDialog>
#include "switch/securitywidget.h"
#include "view/alarmitem.h"
#include "Frame/ThingDlg/qalarmcontrolgendlg.h"
namespace Ui {
    class AlarmListDlg;
}

class AlarmListDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AlarmListDlg(QGraphicsItem *pItem,int alarmtype,QWidget *parent = 0);
    ~AlarmListDlg();
    void InitAllProperty();
    void DrawTable();
	void DrawHisTable();
    void accept();
    QString getDateStr(int format,int type);

    QAlarmControlGenDlg *pAlarmListGen;
    SecurityWidget *pSecurityWight;
    QGraphicsItem *item;
private:
	int alarmType;
    Ui::AlarmListDlg *ui;
    QGraphicsScene scene;
    QVector<qreal> vVLine;              //用来存垂直线的数据
    QVector<qreal> vHLine;             //用来存水平线的数据
    int oId;




private slots:
    void on_buttonBox_helpRequested();
};

#endif // ALARMLISTDLG_H
