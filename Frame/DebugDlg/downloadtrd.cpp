#include "downloadtrd.h"
#include <QProcess>
#include <QDir>
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

#define APK_PATH "com.android.Samkoonhmi"
#define APK_NAME "com.android.Samkoonhmi/com.android.Samkoonhmi.activity.LoginActivity"
#define HMI_PICTRUE_DIR "/data/data/com.android.Samkoonhmi/pictures/"
#define HMI_UPLOAD_DIR "/data/data/com.samkoon.sklauncher/vFiHpd/"
#define HMI_INFO_FILE "/data/data/com.android.Samkoonhmi/information.txt"
#define HMI_MODEL_FILE "/data/model.dat"
#define HMI_SERIAL_FILE "/data/serial"
#define HMI_ML_FILE "/data/data/com.android.Samkoonhmi/files/ml.dex"
#define HMI_SHARED_PREFS "/data/data/com.android.Samkoonhmi/shared_prefs/information.xml"
#define PC_LOCALDRV_DIR "Drivers\\armeabi"
#define PC_VBOXDRV_DIR "Drivers\\x86"
#define PC_DOWNLOAD_FILE "compile\\samkoonhmi.akz"
#define LOCALDRV_DIR_NAME "armeabi"
#define VBOXDRV_DIR_NAME "x86"
#define PC_LOGO_FILE "usranipro\\bootanimation.zip"
#define LOGO_FILE_NAME "bootanimation.zip"
#define HMI_POWERSAVE_FILE "powersave.bin"
#define HMI_LOGO_FILE "/data/data/com.android.Samkoonhmi/usranipro/"
#define VBOX_DRV_DIR "Drivers\\x86"
#define HMI_SAMKOON_DIR "/data/data/com.android.Samkoonhmi/"
#define HMI_DATABASE_DIR "/data/data/com.android.Samkoonhmi/databases/"
#define HMI_LIBRARY_DIR "/data/data/com.android.Samkoonhmi/macro/"
#define HMI_DRIVER_DIR "/data/data/com.android.Samkoonhmi/lib/"
#define HMI_FONTS_DIR "/data/data/com.android.Samkoonhmi/fonts/"
#define HMI_RECIPE_DIR "/data/data/com.android.Samkoonhmi/formula/"
#define HMI_ALARM_DIR "/data/data/com.android.Samkoonhmi/alarm/"
#define PC_PICTURE_DIR "resource"

#define PC_PLC_DIR "temp\\soar"
#define PLC_DIR_NAME "soar"
#define HMI_PLC_DIR "/data/data/com.android.Samkoonhmi/plc/"

#define PC_DATABASE_FILE "sd.dat"
#define PC_RECIPE_FILE "recipe.dat"
#define PC_ALARM_FILE "alarm.db"
#define PC_LIBRARY_FILE "sdmacro\\ml\\ml.jar"
#define PC_ZIP_DIR "compile\\Udisk\\"
#define PC_RC_DIR "rcfile"
#define PC_APK_FIRE "samkoonhmi.apk"

#define PC_ML_FIRE "ml.jar"
#define PC_UPLOAD_FILE "vXkIp.m"
#define PC_RESETPORT_FILE "port.bat"

#define FILE_LIBSKCOMMON "libskcommon.so"
#define FILE_LIBPMEN "libpmem.so"
#define FILE_DRIVERS_CENTER "libplc_drives_center.so"
#define FILE_SERIAL_PORT "libserial_port.so"
#define FILE_CAN_BUS "libcan_port.so"

#ifndef PC_COMPRESS_FILE
#define PC_COMPRESS_FILE "compile\\upLoad.akr"
#endif

downloadTrd::downloadTrd(QObject *parent) :
    QThread(parent)
{
    process = NULL;
    process = new QProcess();

    bTransmit = false;
    needCompress = true;
    fontFiles = pwnd->getFontMap().values();
    QFile::remove(PC_DOWNLOAD_FILE);

    m_type = 1;
}
downloadTrd::~downloadTrd()
{
    if(process)
        process->deleteLater();
}
void downloadTrd::showBatMsg()
{
    qDebug() << "showBatMsg";
    QString text = process->readAllStandardOutput();

    QStringList lst = text.split("\r\n");
    for(int i=0; i<lst.size();i++)
    {
        QString line = lst.at(i);
        if(!line.isEmpty())
            information(line);
    }
}

//�Ƿ����ڴ���
bool downloadTrd::isTransmitting()
{
    return bTransmit;
}
//���USB�豸������
void downloadTrd::startAdb_Usb()
{

    QString devName;
    QStringList devices = adb_listAllDevice();

    if(devices.size()>0)
    {
        devName = devices.first();
       // ��ʼ����
        startAdb(devName);
    }
}

//������̫��������
void downloadTrd::startAdb_Ethernet(QString Ip)
{
    QString devName;
    bool isExist = adb_connect(Ip);

    if(isExist)
    {
        devName = Ip+":5555";
       // ��ʼ����
        startAdb(devName);
        adb_disconnect();
    }

}

//����
void downloadTrd::startAdb(QString device)
{
    bool bUpdate = false;
    bTransmit = true;
    bool bSucess = false;
	process->start("adb devices");
	process->waitForFinished();

	//ȡö�ٽ�����ж��Ƿ��з����������豸
	QString text = process->readAllStandardOutput();
    qDebug() << "adb devices:" << text;
    text = adb_checkAppRun(device,"com.samkoon.sklauncher");
    if(!m_vbox && text.isEmpty())
    {
        information(tr("HMIδ����"));
        bTransmit = false;
        return ;
    }
    if(!m_vbox && !adb_checkModel(device))
    {
        information(tr("HMI�ͺ�����̬��һ�£�ֹͣ����"));
        bTransmit = false;
        return ;
    }
    if(!adb_CheckApkVerion(device))
    {
        information(tr("HMI�汾����̬��ͬ�����ڸ���"));
        bUpdate = true;
        //return ;
    }
    else if(m_bUpdate)//ǿ�Ƹ���
    {
        information(tr("ǿ�Ƹ���HMI"));
        bUpdate = true;
    }

    //����HMIʱ��ΪPC��ϵͳʱ��
    adb_setTime(device);

	if (!m_vbox)
	{
		//������λ����
		adb_sendCmd(device,"setprop ak.need.run no");

        adb_killProcess(device);
        adb_killProcess(device);
	}
	else
	{
        adb_sendCmd(device,"am startservice -n com.android.Samkoonhmi/.util.AkZipService --es update start");
        //adb_sendCmd(device,"am broadcast -a com.android.Samkoonhmi.download.start");
		adb_stopApk(device,APK_PATH);
	}
    
    //connect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(showBatMsg()));

    if(bUpdate)
    {
        QString apkfile = curDir()+PC_APK_FIRE;
        if(QFile::exists(apkfile))
        {
            adb_installApk(device,apkfile);

        }
        else
        {
            qDebug() << "error: " << "APK not exist!";
        }
    }

    //����Ȩ��
    adb_sendCmd(device,"chmod 777 /data/data/com.android.Samkoonhmi");
    adb_sendCmd(device,"chmod 777 /data/data/com.android.Samkoonhmi/*");
    adb_sendCmd(device,"chmod 777 /data/data/com.samkoon.sklauncher");


    qDebug()<<"needCompress = " <<needCompress;
    int compressResult = 1;
    if(needCompress)
    {
        if(!QFile::exists(PC_DOWNLOAD_FILE))
        {
            compressResult = start_Udisk(PC_DOWNLOAD_FILE);
        }

    }
    if(compressResult == 1)
    {
        QString akzfile = curDir()+PC_DOWNLOAD_FILE;
        akzfile.replace("/","\\");
        qDebug() << "before adb_removeFile:lib";
        adb_removeFile(device,"/data/data/com.android.Samkoonhmi/lib");
        qDebug() << "before adb_pushFile";
        bSucess = adb_pushFile(device,akzfile,HMI_SAMKOON_DIR);
        qDebug() << "before adb_removeFile:powersave_file";
        adb_removeFile(device, HMI_POWERSAVE_FILE);

    }

    adb_sendCmd(device,"am startservice -n com.android.Samkoonhmi/.util.AkZipService --es update start");
    adb_sendCmd(device,"am startservice -n com.android.Samkoonhmi/.util.AkZipService --es update true");
    //����������λ����
    if (m_vbox)
	{
        adb_sendCmd(device,"am startservice -n com.android.Samkoonhmi/.util.AkZipService --es update stop");
        //adb_sendCmd(device,"am broadcast -a com.android.Samkoonhmi.download.stop");
		//adb_stopServer();
                //adb_startApk(device,APK_NAME);
	}
    process->start("adb akkill-server");
    bTransmit = false;
    //adb_startApk(device,APK_NAME);
    if(bSucess)
        information(tr("�������"));
    else
        information(tr("����ʧ��"));
    //disconnect(process,SIGNAL(readyReadStandardOutput()),this,SLOT(showBatMsg()));
}

//�������ڽ��е�ADB����
void downloadTrd::adb_stopServer()
{
    QString cmd = PC_RESETPORT_FILE;

    process->start(cmd);
    process->waitForFinished();

    process->readAllStandardOutput();

}
void downloadTrd::adb_disconnect()
{
	QString cmd = "adb disconnect ";
	process->start(cmd);
	process->waitForFinished();
}

//ͨ����̫������HMI�豸
bool downloadTrd::adb_connect(QString Ip)
{
	adb_disconnect();
    QString info = tr("�������ӵ� ");
    info += Ip;
    information(info);
    QString cmd = "adb connect "+ Ip;
    //cmd="\""+cmd;
    //cmd=cmd+"\"";
    process->start(cmd);
    process->waitForFinished();

    //ȡö�ٽ�����ж��Ƿ��з����������豸
    QString text = process->readAllStandardOutput();
	QString error = process->readAllStandardError();
    //qDebug() << "error---connect" << error;
    //qDebug() << "text---connect" << text;
    QStringList lst = text.split("\r\n");
    for(int i=0; i<lst.size();i++)
    {
        QString line = lst.at(i);
        if(text.size() == 0 || line.startsWith("unable"))// �Ƿ�δ����
        {
            information(tr("���ӵ� ")+ Ip +tr(" ʧ��"));
            return false;
        }

    }
    information(tr("���ӵ� ")+ Ip +tr(" �ɹ�"));
    return true;
}

bool downloadTrd::adb_creatDir(QString device,QString path)
{
    //this->adb_removeDir(device,path);
    QString cmd = QString("adb -s %1 akshell \"mkdir \"%2\" 2>/dev/null \"").arg(device).arg(path);
    process->start(cmd);
    process->waitForFinished();

	QString log = process->readAllStandardError();
    //qDebug() << "adb_creatDir" << cmd;
    //qDebug() << "error__________"<<log;
    return true;
}
bool downloadTrd::adb_pushFile(QString device,QString fullpath,QString destDir)
{
    adb_creatDir(device,destDir);

    QString cmd = QString("adb -s %1 push \"%2\" \"%3\"").arg(device).arg(fullpath).arg(destDir);
    process->start(cmd);
    process->waitForFinished();

    QString log = process->readAllStandardError();
    qDebug() << "adb_pushFile:"<< log;
    bool result = log.contains("bytes",Qt::CaseInsensitive) || log.isEmpty();
    return result;


}
bool downloadTrd::adb_pushDir(QString device,QString fullpath,QString destDir)
{
    adb_creatDir(device,destDir);

    QString cmd = QString("adb -s %1 push \"%2\" \"%3\"").arg(device).arg(fullpath).arg(destDir);
    process->start(cmd);
    process->waitForFinished();

    //qDebug() << "adb_pushDir" << cmd;
    return true;
}
bool downloadTrd::adb_removeDir(QString device,QString path)
{
    QString cmd = QString("adb -s %1 akshell \" rm \"%2\" 2>/dev/null\"").arg(device).arg(path);
    process->start(cmd);
    process->waitForFinished();

    //qDebug() << "adb_removeDir" << cmd;
    return true;
}
bool downloadTrd::adb_removeFile(QString device,QString fullpath)
{
    QString cmd = QString("adb -s %1 akshell \"rm \"%2\"  2>/dev/null\" ").arg(device).arg(fullpath);
    process->start(cmd);
    process->waitForFinished();

    //qDebug() << "adb_removeFile" << cmd;
    return true;
}
bool downloadTrd::adb_installApk(QString device,QString path)
{
    QString cmd = QString("adb -s %1 install -r \"%2\" ").arg(device).arg(path);
    process->start(cmd);
    process->waitForFinished();

    qDebug() << "adb_installApk" << cmd;
    return true;
}
bool downloadTrd::adb_stopApk(QString device,QString path)
{
    QString cmd = QString("adb -s %1 akshell \"am force-stop  \"%2\"\" ").arg(device).arg(path);
    process->start(cmd);
    process->waitForFinished();

    //qDebug() << "adb_stopApk" << cmd;
    return true;
}
bool downloadTrd::adb_startApk(QString device,QString path)
{

    QString cmd = QString("adb -s %1 akshell \"am start -n  \"%2\"\" ").arg(device).arg(path);
    process->start(cmd);
    process->waitForFinished();
    //qDebug() << "adb_startApk" << cmd;
    return true;

}
bool downloadTrd::adb_sendCmd(QString device,QString cmd)
{
    QString bash = QString("adb -s %1 akshell \"%2\" ").arg(device).arg(cmd);
    process->start(bash);
    process->waitForFinished();
    //qDebug() << "adb_sendCmd" << bash;
    return true;

}
QString downloadTrd::curDir()
{
    return QDir::currentPath()+"/";
}
QStringList downloadTrd::getDriverPath()
{
    QStringList paths;
    foreach (stConnect cnt,pwnd->m_pSamSysParame->m_qvcConnect)
    {
        foreach(stProtocol model,cnt.vProtocols)
        {
            QString path = "Drivers/qtdll/"+model.sFactoryName +"/"+model.sProtocolName+".so";
            paths << path;
        }

    }
    return paths;
}
//ͨ��USB �����豸
QStringList downloadTrd::adb_listAllDevice()
{
    process->start("adb akkill-server");
    process->waitForFinished();
    //���read������
    process->readAllStandardOutput();


    //��ʼö���豸
    process->start("adb devices");
    process->waitForFinished();

    //ȡö�ٽ�����ж��Ƿ��з����������豸
    QString text = process->readAllStandardOutput();
    QString error = process->readAllStandardError();

    qDebug() <<"list all devices" <<text;
    qDebug() <<"list all devices:error " <<error;
    QStringList lst = text.split("\r\n");
    QStringList devices;
    for(int i=0; i<lst.size();i++)
    {
        QString line = lst.at(i);
        if(line.endsWith("device") && line.contains(STRING_DEVICE_ID))// �Ǻ��й�˾��ʾ���豸
        {
            line.remove("device");
            line.remove("\ ");
            devices << line;
        }

    }


    if(devices.isEmpty())
    {
        this->information(tr("û�����ӵ�HMI�豸"));
    }
    return devices;
}
bool downloadTrd::adb_CheckApkVerion(QString device)
{
    bool result = false;
    //���read������


    QString cmd = QString("adb -s %1 akshell \"am broadcast -a com.android.Samkoonhmi.init.version\"").arg(device);
    process->start(cmd);
    process->waitForFinished();

    qDebug() << "after broadcast version:"<< process->readAllStandardOutput();
    //��ʼö���豸
    QString path = HMI_INFO_FILE;
    cmd = QString("adb -s %1 akshell \"cat \"%2\"\" ").arg(device).arg(path);
    process->start(cmd);
    process->waitForFinished();

    //ȡ��ȡAPK�汾������ж��Ƿ��з����������豸
    QString text = process->readAllStandardOutput();
    qDebug() << "read version file:"<< process->readAllStandardOutput();
    QStringList lst = text.split("\r\n");
    QStringList lines;
    for(int i=0; i<lst.size();i++)
    {
        QString line = lst.at(i);
        if(line.startsWith(APK_VERSION_CODE))// �Ǻ��й�˾��ʾ���豸
        {
            //result = true;
            return true;
        }

    }
    return result;
}
void downloadTrd::run()
{
    fontFiles = pwnd->getFontMap().values();
    if(m_type == 999)
    {
        //��ֹͣ�Ѿ��򿪵�ADB ����
        adb_stopServer();
        //��ȡ���к�
        getSerial();
    }
    else if(m_type == 1)//usb
    {
        //��ֹͣ�Ѿ��򿪵�ADB ����
        adb_stopServer();
        startAdb_Usb();
    }
    else if(m_type == 0)//��̫��
    {
        //��ֹͣ�Ѿ��򿪵�ADB ����
        adb_stopServer();
        startAdb_Ethernet(m_Ip);
    }
    else if(m_type == 3)
    {
        //��̫���������
        qDebug() << tr("��̫���������");
        adb_stopServer();
        startMutilHost(hosts);
        bTransmit = false;
    }
    else
    {
        start_Udisk(m_Ip);
        bTransmit = false;
        //���ص�U��
    }
}
//���ص�U��
int downloadTrd::start_Udisk(QString sPath)
{

	QLibrary  lib("kZd.dll");
    if (!lib.load())
    {
        information(tr("�ļ�ȱʧ������ʧ��"));
        return 0;
    }
    typedef bool (*ADDPROC)( QString ,QString,int );
    ADDPROC zip= (ADDPROC)lib.resolve("zipDirectory");
    if (!zip)
    {
        information(tr("�ļ�ȱʧ������ʧ��"));
        return 0;
    }

    //����������̬
    QString drvDir = PC_ZIP_DIR;
    drvDir += LOCALDRV_DIR_NAME;
    QDir compiledir = QDir(drvDir);
    if(!compiledir.exists())
    {
        compiledir.mkpath(compiledir.absolutePath());
    }
#ifdef AKPLC
    QString sPlcdir = PC_ZIP_DIR;
    sPlcdir += PLC_DIR_NAME;
    QDir plcdir = QDir(sPlcdir);
    if(!plcdir.exists())
    {
        plcdir.mkpath(plcdir.absolutePath());
    }
#endif
	QString fpath = PC_ZIP_DIR+QString("fileMap.bin");
	QFile file(fpath);
	if(!file.open(QIODevice::WriteOnly))
	{
		//���ļ�ʧ�ܵĴ�����
		return 0;
	}
	QTextStream txtstream(&file);

    bTransmit = true;
    //�Ƿ񸲸��䷽
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bWriteFormula)
    {
        txtstream << "CoverRecipe,true" <<endl;
    }
    else
    {
        txtstream << "CoverRecipe,false" <<endl;
    }

    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bClearAlarm)
    {
        txtstream << "ClearAlarm,true" <<endl;
    }
    else
    {
        txtstream << "ClearAlarm,false" <<endl;
    }

    if(!m_vbox && pwnd->m_pSamSysParame->m_mixGlobalVar.m_bUpLoad) //wxy�����ģ��������ѹ���ļ�
    {
        QString sUpfile = PC_ZIP_DIR;
        sUpfile += PC_UPLOAD_FILE;
        cmpfile(PC_COMPRESS_FILE,sUpfile);
        txtstream << PC_UPLOAD_FILE << "," << HMI_UPLOAD_DIR <<endl;
    }

    //��ʼ�������������ļ���������·��

    //���ݿ�
    QString dbfile = curDir()+PC_DATABASE_FILE;
    dbfile.replace("/","\\");
    QString sDest = PC_ZIP_DIR;
    sDest += PC_DATABASE_FILE;
    if (copyFileToPath(dbfile,sDest))
    {
		txtstream << PC_DATABASE_FILE << "," << HMI_DATABASE_DIR <<endl;
    }

    

    //�䷽���ݿ��ļ�
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bWriteFormula)
    {
        //�����µ��䷽����
        dbfile = curDir()+PC_RECIPE_FILE;
        dbfile.replace("/","\\");
        sDest = PC_ZIP_DIR;
        sDest += PC_RECIPE_FILE;
        if(copyFileToPath(dbfile,sDest))
			txtstream << PC_RECIPE_FILE << "," << HMI_RECIPE_DIR <<endl;
    }
    //��������
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bUseLogo && QFile::exists(PC_LOGO_FILE))
    {

        QString zfile = curDir()+PC_LOGO_FILE;
        zfile.replace("/","\\");
        sDest = PC_ZIP_DIR;
        sDest += LOGO_FILE_NAME;
        if(copyFileToPath(zfile,sDest))
            txtstream << LOGO_FILE_NAME << "," << HMI_LOGO_FILE <<endl;

    }

    //ͼƬ
    QString pictures = curDir()+PC_PICTURE_DIR;
    pictures.replace("/","\\");
    sDest = PC_ZIP_DIR;
    sDest += PC_PICTURE_DIR;
    if(copyDirectoryFiles(pictures,sDest))
		txtstream << PC_PICTURE_DIR << "," << HMI_PICTRUE_DIR <<endl;

    //ͼƬ
    pictures = curDir()+PC_RC_DIR;
    pictures.replace("/","\\");
    sDest = PC_ZIP_DIR;
    sDest += PC_PICTURE_DIR;
    if(copyDirectoryFiles(pictures,sDest))
        txtstream << PC_RC_DIR << "," << HMI_PICTRUE_DIR <<endl;

    //�ű�
    QString libfile = curDir()+PC_LIBRARY_FILE;
    libfile.replace("/","\\");
    sDest = PC_ZIP_DIR;
    sDest+= PC_ML_FIRE;
    if(copyFileToPath(libfile,sDest))
        txtstream << PC_ML_FIRE << "," << HMI_LIBRARY_DIR <<endl;

    //�ڲ�����
    QString localDriver;
    if(m_vbox)
    {
        localDriver = curDir()+PC_VBOXDRV_DIR;
    }
    else
    {
        localDriver = curDir()+PC_LOCALDRV_DIR;
    }

    localDriver.replace("/","\\");
    QStringList drvfiles;
    drvfiles << FILE_LIBSKCOMMON;
    drvfiles << FILE_LIBPMEN;
    drvfiles << FILE_DRIVERS_CENTER;
    drvfiles << FILE_SERIAL_PORT;
    drvfiles << FILE_CAN_BUS;

    foreach(stConnect cnt,pwnd->m_pSamSysParame->m_qvcConnect)
    {
        foreach(stProtocol proc,cnt.vProtocols)
        {
            QString filename = "lib"+proc.sProtocolName+".so";
            if(!drvfiles.contains(filename))
            {
                drvfiles << filename;
            }
        }
    }
    qDebug() << drvfiles;

    foreach(QString drvfile,drvfiles)
    {
        sDest = PC_ZIP_DIR;
        sDest += LOCALDRV_DIR_NAME;
        sDest += "\\";
        sDest += drvfile;

        qDebug() << localDriver+"\\"+drvfile;
        qDebug() << sDest;

        if(!copyFileToPath(localDriver+"\\"+drvfile,sDest))
        {

            QString errormsg = QString(tr("ͨ�������ļ� %1δ�ҵ�").arg(drvfile));
            information(errormsg);
        }

    }
    //sDest = PC_ZIP_DIR;
    //sDest += LOCALDRV_DIR_NAME;
    //if(copyDirectoryFiles(localDriver,sDest))
    txtstream << LOCALDRV_DIR_NAME << "," << HMI_DRIVER_DIR <<endl;



    //����

    int fontsize = 0;
    foreach(QString fontfile,fontFiles)
    {
        QString path = getWinFontDir()+"/Fonts/"+fontfile;
        path.replace("/","\\");
        QFile file(path);
        //qDebug() << file.size();
        fontsize += file.size();
        if(fontsize < 40000000)
        {
            QString name = path.section("\\",-1);
            sDest = PC_ZIP_DIR;
            sDest += name;
            if(copyFileToPath(path,sDest))
				txtstream << name << "," << HMI_FONTS_DIR <<endl;
            else
                qDebug() << "COPY font file error";
        }
        else
        {
            information(tr("�����ļ���С���ޣ��Ѻ���"));
        }

    }
#ifdef AKPLC
    //PLC�����ļ�
    QString plcfiles = curDir()+PC_PLC_DIR;
    plcfiles.replace("/","\\");

    information(plcfiles);
    information(sPlcdir);
    if(copyDirectoryFiles(plcfiles,sPlcdir))
        txtstream << PLC_DIR_NAME << "," << HMI_PLC_DIR <<endl;
#endif
    file.close();

    //qDebug()<< "m_vbox"<< m_vbox;
    if(!m_vbox) //wxy�����ģ��������ѹ���ļ�
    {
        if(!sPath.endsWith(".akz",Qt::CaseInsensitive))
        {
            sPath.append(".akz");
        }
        if(!zip(curDir()+PC_ZIP_DIR,sPath,9) || !QFile::exists(sPath))
        {
            information(tr("ѹ��ʧ��"));
            lib.unload();
            bTransmit = false;
            return 0;
        }
        information(tr("ѹ�����"));
        lib.unload();
    }

    return 1;
}
void downloadTrd::setprarm(int type,QString Ip,bool bVbox,bool bUpdate)
{
    m_type = type;
    m_Ip = Ip;
	m_vbox = bVbox;
    m_bUpdate = bUpdate;
}
QString downloadTrd::adb_checkAppRun(QString device,QString app)
{
    process->readAllStandardOutput();
    QString cmd = QString("ps | busybox grep %1 | busybox awk '{print $2}'").arg(app);
    adb_sendCmd(device,cmd);

    QString text = process->readAllStandardOutput();

   //qDebug() <<"xxxxxxxxxxxxxxxxxxxxxxxxx   " <<text;

   return text;
}

QString downloadTrd::getWinFontDir()
{
	char *p;
	int size = ::GetWindowsDirectoryA(NULL,0);
	p = new char[size];
	::GetWindowsDirectoryA(p,size);
	QString sPath = QString(p);
	delete []p;
	return sPath;
}

//����ǰ������λ�ļ�
void downloadTrd::adb_clear(QString device)
{
    QString sTmp;
    sTmp = HMI_PICTRUE_DIR;
    sTmp += "*";
    adb_removeFile(device,sTmp);

    sTmp = HMI_DATABASE_DIR;
    sTmp += "*";
    adb_removeFile(device,sTmp);

    sTmp = HMI_LIBRARY_DIR;
    sTmp += "*";
    adb_removeFile(device,sTmp);

    sTmp = HMI_DRIVER_DIR;
    sTmp += "*";
    adb_removeFile(device,sTmp);

    sTmp = HMI_SHARED_PREFS;
    adb_removeFile(device,sTmp);

    sTmp = HMI_FONTS_DIR;
    sTmp += "*";
    adb_removeFile(device,sTmp);

    sTmp = HMI_ML_FILE;
    adb_removeFile(device,sTmp);

    //�����ļ����Ŀ¼
    sTmp = HMI_UPLOAD_DIR;
    sTmp += "*";
    adb_removeFile(device,sTmp);

}

//����ϵͳʱ�䵽HMI
void downloadTrd::adb_setTime(QString device)
{
    if(pwnd->m_pSamSysParame->m_clockProp.bDownLoadTime)
    {
        //double time = (double)QDateTime::currentDateTime().toTime_t() *1000;
        //QString stime = QString::number(time,'f',0);
        QString stime = QDateTime::currentDateTime().toString("yyyy,MM,dd,hh,mm,ss");
        //qDebug()<<"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF" <<stime;
        QString cmd = QString("am broadcast -a com.samkoon.syntime  --es time %1").arg(stime);
        adb_sendCmd(device,cmd);
    }
}

//�����ļ���Ŀ¼
int downloadTrd::adb_find(QString device,QString file)
{
   process->readAllStandardOutput();
   adb_sendCmd(device,QString("akfind.sh \"%1\"").arg(file));

   QString text = process->readAllStandardOutput();
   qDebug() <<"adb_find() result---" << text;
   return text.toInt();
}

//�����ļ���Ŀ¼
bool downloadTrd::adb_checkModel(QString device)
{
    process->readAllStandardOutput();

    QString path = HMI_MODEL_FILE;
    QString cmd = QString("adb -s %1 akshell \"cat \"%2\"\" ").arg(device).arg(path);
    process->start(cmd);
    process->waitForFinished();

    //ȡ��ȡAPK�汾������ж��Ƿ��з����������豸
    QString text = process->readAllStandardOutput();

    qDebug() << "------------"<< text <<"---------------";
    QString cModel = pwnd->newpro->newprowizard_model;
    information(tr("��ǰ��̬��Ӧ�Ļ���Ϊ��%1").arg(cModel));
    if(text.contains("AK-",Qt::CaseInsensitive) || text.contains("AKMID-",Qt::CaseInsensitive))
    {
        information(tr("��ǰ�������Ļ���Ϊ��%1").arg(text));
    }
    qDebug() << "------------"<< cModel <<"---------------";

    if(text == "AK-035AET" || text == "AK-035AE-T")
    {
        text = "AK-035A-T";
    }
    if(cModel == "AK-035AET" || cModel == "AK-035AE-T")
    {
        cModel = "AK-035A-T";
    }
    return (text == cModel);

}
//��������
void downloadTrd::adb_killProcess(QString device)
{
    int count =5;
    QString pid = adb_checkAppRun(device,"com.android.Samkoon");
    qDebug() << pid;
    while(!pid.isEmpty())
    {

        msleep(1000);
        count --;
        if(count <= 0)
        {
            QString sId = pid;

            sId.replace("\r\n"," ");
            sId.replace("\r"," ");
            sId.replace("\n"," ");
            qDebug() << "PROCESS ID======" << sId;
            QStringList sIds = sId.split(QRegExp("\\W+"), QString::SkipEmptyParts);
            foreach(QString id,sIds)
            {
                QString cmd = QString("kill %1").arg(id);
                adb_sendCmd(device,cmd);
                qDebug() << "PROCESS ID======" << id;
            }

            break;
        }
        pid = adb_checkAppRun(device,"com.android.Samkoon");

    }
}

bool downloadTrd::cmpfile(QString src,QString dest)
{
    QDir compiledir = QDir("compile\\UDisk");
    if(!compiledir.exists())
    {
        compiledir.mkpath(compiledir.absolutePath());
    }
    QFile sfile(src);
    QFile dfile(dest);
    if(dfile.open(QIODevice::WriteOnly) &&
       sfile.open(QIODevice::ReadOnly))
    {
        QByteArray data;

        QByteArray s = sfile.readAll();
        sfile.close();

        data = qCompress(s,5);
        dfile.write(data);
        dfile.close();
		return true;
    }
	else{
		return false;
	}

}

bool downloadTrd::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist) 
{ 
	QDir sourceDir(fromDir); 
	QDir targetDir(toDir); 
	if(!targetDir.exists()){    /**< ���Ŀ��Ŀ¼�����ڣ�����д��� */ 
		if(!targetDir.mkdir(targetDir.absolutePath())) 
			return false; 
	} 

	QFileInfoList fileInfoList = sourceDir.entryInfoList(); 
	foreach(QFileInfo fileInfo, fileInfoList){ 
		if(fileInfo.fileName() == "." || fileInfo.fileName() == "..") 
			continue; 

		if(fileInfo.isDir()){    /**< ��ΪĿ¼ʱ���ݹ�Ľ���copy */ 
			if(!copyDirectoryFiles(fileInfo.filePath(),  
				targetDir.filePath(fileInfo.fileName()), 
				coverFileIfExist)) 
				return false; 
		} 
		else{            /**< �������ǲ���ʱ�������ļ�����ɾ������ */ 
			if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){ 
				targetDir.remove(fileInfo.fileName());  
			} 

			/// �����ļ�copy 
			if(!QFile::copy(fileInfo.filePath(),  
				targetDir.filePath(fileInfo.fileName()))){ 
					return false; 
			} 
		} 
	} 
	return true; 
} 
void downloadTrd::getSerial()
{
    QString devName;
    QStringList devices = adb_listAllDevice();

    if(devices.size()>0)
    {
        devName = devices.first();
    }
    else
    {
        emit serial("",5);
        return;
    }
    process->start("adb devices");
    process->waitForFinished();

    //ȡö�ٽ�����ж��Ƿ��з����������豸
    QString text = process->readAllStandardOutput();
    //qDebug() << "~~~~~~~~~~~~~~~~" << text;
    QString path = HMI_MODEL_FILE;
    QString cmd = QString("adb -s %1 akshell \"cat \"%2\"\" ").arg(devName).arg(path);
    process->start(cmd);
    process->waitForFinished();

    text = process->readAllStandardOutput();
    qDebug() << "~~~~~~~~~~~~~~~~" << text;
    if(text.isEmpty() || text.size() >30)
    {
        emit serial("",4);
        return ;
    }
    else
    {
        emit serial(text,2);
    }

    path = HMI_SERIAL_FILE;
    cmd = QString("adb -s %1 akshell \"cat \"%2\"\" ").arg(devName).arg(path);
    process->start(cmd);
    process->waitForFinished();

    text = process->readAllStandardOutput();
    qDebug() << "~~~~~~~~~~~~~~~~" << text;
    if(text.isEmpty() || text.size() >30)
    {
        emit serial("",3);
        return ;
    }
    else
    {
        emit serial(text,1);
    }
}

void downloadTrd::startMutilHost(QStringList hostIps)
{
    m_vbox = false;
    //QFile::remove(PC_DOWNLOAD_FILE);
    bool bCompressed = true;
    if(!QFile::exists(PC_DOWNLOAD_FILE))
    {
        bCompressed = start_Udisk(PC_DOWNLOAD_FILE);
    }
    if(bCompressed)
    {
        needCompress = false;
        foreach(QString ip,hostIps)
        {
            startAdb_Ethernet(ip);
        }
        needCompress = true;
    }

}
bool downloadTrd::copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist) 
{ 
	toDir.replace("\\","/"); 
	if (sourceDir == toDir){ 
		return true; 
	} 
	if (!QFile::exists(sourceDir)){ 
		return false; 
	} 
	QDir *createfile     = new QDir; 
	bool exist = createfile->exists(toDir); 
	if (exist){ 
		if(coverFileIfExist){ 
			createfile->remove(toDir); 
		} 
	}//end if 

	if(!QFile::copy(sourceDir, toDir)) 
	{ 
		return false; 
	} 
	return true; 
}
