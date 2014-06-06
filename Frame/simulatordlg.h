#ifndef SIMULATORDLG_H
#define SIMULATORDLG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
    class SimulatorDlg;
}
class downloadTrd;

class SimulatorDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SimulatorDlg(QWidget *parent = 0);
    ~SimulatorDlg();
	bool start();
	bool runCmd(QString cmd);
/*
    void download_vbox();
	void connect_vbox();
	void run_vbox();
	void setprogress();
    static void adb_disconnect();
    static bool adb_connect(QString Ip);
*/
    //wxy
    void setLabelText(QString str, int value);
    void reject();
private slots:
    //void onTimer();
    //void downFinished();
private:
    Ui::SimulatorDlg *ui;
    void closeEvent(QCloseEvent *cEvent);
/*
    bool bStop ;
    SIMULAT_STATE eState;
    QTimer timer;
    downloadTrd *thread;
    connectThd *cThd;
    int m_times;
    void setWindowFirst();
*/
};

#endif // SIMULATORDLG_H
