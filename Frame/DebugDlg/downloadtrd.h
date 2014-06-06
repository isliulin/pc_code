#ifndef DOWNLOADTRD_H
#define DOWNLOADTRD_H

#include <QThread>
#include <windows.h>
#define FILE_DOWNLOAD "compile/project.bin"
#define STRING_DEVICE_ID  "samkoon"
#define APK_VERSION_CODE "VERSIONCODE=57"
#define PC_AKZ_FIRE "samkoonhmi.akz"

class QProcess;


class downloadTrd : public QThread
{
    Q_OBJECT
public:
    explicit downloadTrd(QObject *parent = 0);
    ~downloadTrd();
    void startAdb(QString device);
    void startAdb_Usb();
    void startAdb_Ethernet(QString Ip);
    bool adb_connect(QString Ip);
    bool adb_creatDir(QString device,QString path);
    bool adb_pushFile(QString device,QString fullpath,QString destDir);
    bool adb_pushDir(QString device,QString fullpath,QString destDir);
    bool adb_removeDir(QString device,QString path);
    bool adb_removeFile(QString device,QString fullpath);
    bool adb_installApk(QString device,QString path);
    bool adb_startApk(QString device,QString path);
    bool adb_stopApk(QString device,QString path);
    QStringList adb_listAllDevice();
    bool adb_CheckApkVerion(QString device);
    bool adb_sendCmd(QString device,QString cmd);
	void adb_disconnect();
    QString adb_checkAppRun(QString device,QString app);
    int start_Udisk(QString sPath);
	static bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist = true);
	static bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist = true);
    void adb_stopServer();
    void adb_clear(QString device);
    void adb_setTime(QString device);
    void adb_killProcess(QString device);
    int adb_find(QString device,QString file);
	bool adb_checkModel(QString device);
    bool isTransmitting();
    QString curDir();
    void run();

    QStringList getDriverPath();
    bool cmpfile(QString src,QString dest);

    void setprarm(int type,QString Ip,bool bVbox = false,bool bUpdate = false);
	QString getWinFontDir();
    void getSerial();
    void startMutilHost(QStringList hostIps);
    inline void setHostIps(QStringList hostIps,bool bUpdate )
    {
        m_type = 3;
        hosts = hostIps;
        m_bUpdate = bUpdate;
    }
private:
    int m_type;
	bool m_vbox;
    QString m_Ip;
    QProcess *process;
    QStringList fontFiles;
    bool bTransmit;
    QStringList hosts;
    bool needCompress;
    bool m_bUpdate;
signals:
    void information(QString msg);
    void serial(QString serial,int type);
public slots:
    void showBatMsg();

};

#endif // DOWNLOADTRD_H
