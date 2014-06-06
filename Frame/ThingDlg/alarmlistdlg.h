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
    QVector<qreal> vVLine;              //�����洹ֱ�ߵ�����
    QVector<qreal> vHLine;             //������ˮƽ�ߵ�����
    int oId;




private slots:
    void on_buttonBox_helpRequested();
};

#endif // ALARMLISTDLG_H
