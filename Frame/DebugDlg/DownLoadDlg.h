#ifndef DOWNLOADDLG_H
#define DOWNLOADDLG_H

#include <QDialog>
#include <QProcess>
#include <QTimer>

class ConnectTrd;
class downloadTrd;
namespace Ui {
    class DownLoadDlg;
}
//class IpAddressWidget;
static unsigned long samkoon_checksum(const unsigned short *pBuffer, const int iSize, const bool bComplete);
class DownLoadDlg : public QDialog
{
    Q_OBJECT

public:
    explicit DownLoadDlg(QWidget *parent = 0);
    ~DownLoadDlg();
	bool isLocked;

        bool SizeAll();
        int GetPort();

        int nfilesSize;
        QProcess *process;

        int bChange;

        void BeforeDownload();

        void detectDevices();

        void startUdisk();

        void startMultiHost();


private:
    Ui::DownLoadDlg *ui;
    downloadTrd *thread;
    QTimer *timer;
    ConnectTrd *cTrd;
    QMap<QString,QString> mHosts;
    //IpAddressWidget *IpEdit;

private slots:
    void on_checkBox_clicked(bool checked);
    void reject();
    void on_btn_destDir_clicked();
    void information(QString str, bool status =true);

    void slotError(int code);
    void on_m_closebtn_clicked();
    void on_m_stopbtn_clicked();
    void on_m_downloadbtn_clicked();
    void ShowIpEdit(int id);
    void TimeOut();
    void SetProgress(int size);
    void DisableUI(bool bValue);
    void closeEvent ( QCloseEvent * cEvent );
    void slotRestart();
    void showBatMsg();

    void connecttoHost(QString ip);
    void onConnect(QString ip,QString name);
};

#endif // DOWNLOADDLG_H
