#include "simulatordlg.h"
#include "ui_simulatordlg.h"
#include "Frame/DebugDlg/downloadtrd.h"
#include <QProcess>
#include <Windows.h>
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;
extern bool  is_tanslator;

#define  VBOX_IP "192.168.56.101"
#define  vShareDir "/vdisk/"
#define  vShareAkz "samkoonhmi.akz"
#define  vShareIni "/vdisk/start.ini"


SimulatorDlg::SimulatorDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimulatorDlg)
{
    ui->setupUi(this);
	setWindowTitle(tr("ģ��"));
    start();

    //timer.setInterval(1);
	
    //bStop = false;
    //m_times = 0;
    //thread = new downloadTrd();
    //connect(thread,SIGNAL(finished()),this,SLOT(downFinished()));
    //timer.start();
    //connect(&timer,SIGNAL(timeout()),this,SLOT(onTimer()));
    //cThd = new connectThd();
}

SimulatorDlg::~SimulatorDlg()
{
    QFile::remove("gEKip");
    delete ui;
/*    if(thread)
    {
        thread->deleteLater();
        thread = NULL;
    }
*/
}
bool SimulatorDlg::start()
{
    //eState = START_VBOX;
    ui->label->setText(tr("����ģ����"));
	
	QString cmd;
    QString cDir = QDir::currentPath();
	cDir.replace("/","\\");
	cmd = QString("vboxManage  modifyvm  AKEmu --bioslogoimagepath\"%1\\logo.bmp\"").arg(cDir);
	runCmd(cmd);

	cmd = QString("vboxManage  modifyvm  AKEmu --biosbootmenu menuonly");
	runCmd(cmd);
    //cmd = QString("VBoxManage modifyvm \"AKEmu\" --mouse ps2");
    //runCmd(cmd);

    QString LanguageId = "zh_CN";
    if(is_tanslator)
    {
        LanguageId = "C";
    }
    cmd = QString("VBoxManage.exe setextradata global GUI/LanguageID %1").arg(LanguageId);
    runCmd(cmd);

	int width = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth;
	int height = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight;
    qDebug() << "currentModel.width" << width;
    qDebug() << "currentModel.height" << height;
    cmd = QString("VBoxManage setextradata \"AKEmu\" CustomVideoMode1 %1x%2x16").arg
		(QString::number(width)).arg(QString::number(height));
	runCmd(cmd);

	cmd = QString("VBoxManage guestproperty  set \"AKEmu\"  vbox_graph_mode %1x%2-16").arg
		(QString::number(width)).arg(QString::number(height));
	runCmd(cmd);

	cmd = QString("VBoxManage guestproperty  set \"AKEmu\" vbox_dpi 160");
	runCmd(cmd);
    QProcess::execute("VBoxManage startvm \"AKEmu\"");
    //eState = VBOX_READY;
	return true;
}

bool SimulatorDlg::runCmd(QString cmd)
{
	QProcess process;
	process.start(cmd);
	process.waitForFinished();
	return true;

}
void SimulatorDlg::closeEvent(QCloseEvent * cEvent )
{
    if(pwnd->thread && pwnd->thread->isRunning())
    {
        QString strTemp = "";
        if(pwnd->thread->bDatabaseClosed)
        {
            strTemp = tr("�رնԻ���ǿ���˳�����ģ�⣡");
        }
        else
        {
            strTemp = tr("�����ĵȴ�������ɣ�");
        }
        QMessageBox box(QMessageBox::Warning,tr("����"),strTemp,QMessageBox::NoButton,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        if(pwnd->thread->bDatabaseClosed)
        {
          box.addButton(tr("ȡ��"),QMessageBox::RejectRole);
        }
        if(box.exec() == QMessageBox::AcceptRole)
        {
            if(!pwnd->thread->bDatabaseClosed)
            {
                cEvent->ignore();
            }
            else
            {
                QFile::remove("gEKip");
                if(pwnd->pSimDlg)
                {
                    pwnd->pSimDlg = NULL;
                }
                if(pwnd->thread && pwnd->thread->isRunning())
                {
                    QFile::remove("vdisk/prepare_OK.ini");
                    QFile::remove("vdisk/prepare.ini");
                    pwnd->isCompiled = false;
                    pwnd->thread->terminate();
                }
                cEvent->accept();
            }
        }
        else
        {
            cEvent->ignore();
        }
    }
}
void SimulatorDlg::reject()
{

    QDialog::close();
}
/*
void SimulatorDlg::onTimer()
{
	
	switch (eState)
	{
	case START_VBOX:
        connect_vbox();
		break;
	case VBOX_READY:
		setprogress();
        download_vbox();
			
		break;
	case CONNECT_ADB:
		break;
	case DOWLOAD_FILE:
		break;
	case RUNNING:
        //run_vbox();
		break;
	}
}
//���������
void SimulatorDlg::connect_vbox()
{


}
//���������߳�
void SimulatorDlg::download_vbox()
{
	ui->label->setText(tr("���ڴ�����̬����"));

	if (thread && !thread->isRunning())
	{
        QString vdisk = pwnd->currentPath();
        vdisk += vShareDir;
        vdisk += vShareAkz;
        vdisk.replace("\\","/");
        thread->setprarm(2,vdisk,true);
		thread->start();
        //bStop = true;
	}
}

//���ؽ����У�ˢ��UI
void SimulatorDlg::run_vbox()
{
	ui->label->setText(tr("ģ��������"));
	ui->progressBar->setValue(100);
}

//������أ������������
void SimulatorDlg::downFinished()
{
    QFile::remove("gEKip");
	ui->label->setText(tr("������ɣ�����ģ����"));
	ui->progressBar->setValue(0);

    //bStop = false;
	eState = RUNNING;
    QString vdisk = pwnd->currentPath();
    vdisk += vShareIni;
    vdisk.replace("\\","/");
    QSettings *readIni = new QSettings(vdisk, QSettings::IniFormat, 0);
    readIni->setValue("StartVM", "true");
    //д��APK�汾�ţ�ģ�������ݴ˰汾�ž����Ƿ����
    readIni->setValue("updateVer", QVariant(APK_VERSION_CODE));

    setWindowFirst();

	accept();
}

void SimulatorDlg::setprogress()
{
	int value = ui->progressBar->value();
	value += 5;
	if (value >100)
	{
		value = 0;
	}
	ui->progressBar->setValue(value);
}

bool SimulatorDlg::adb_connect(QString Ip)
{
    adb_disconnect();
    QProcess process;
    QString info = tr("�������ӵ� ");
    info += Ip;
    QString cmd = "adb connect "+ Ip;
    //cmd="\""+cmd;
    //cmd=cmd+"\"";
    process.start(cmd);
    process.waitForFinished();

    //ȡö�ٽ�����ж��Ƿ��з����������豸
    QString text = process.readAllStandardOutput();
    QString error = process.readAllStandardError();
    //qDebug() << "error---connect" << error;
    //qDebug() << "text---connect" << text;
    QStringList lst = text.split("\r\n");
    for(int i=0; i<lst.size();i++)
    {
        QString line = lst.at(i);
        if(text.size() == 0 || line.startsWith("unable"))// �Ƿ�δ����
        {
            return false;
        }

    }
    return true;
}
void SimulatorDlg::adb_disconnect()
{
    QString cmd = "adb disconnect ";
    QProcess process;
    process.start(cmd);
    process.waitForFinished();
}
void SimulatorDlg::setWindowFirst()
{
    wchar_t strTitle[20];
    HWND hwnd=NULL;
    HWND AfterHwnd = NULL;
    while(true)
    {
    hwnd=::FindWindowEx(NULL,AfterHwnd,NULL,NULL);
    if(!hwnd)
    break;
    else
    {
        if(::GetWindowText(hwnd,strTitle,20))
        {
            qDebug() << strTitle;
            QString str;
            str = str.fromWCharArray(strTitle);
            if(strstr(str.toLatin1(),"AKEmu")!=0)
            {
                qDebug() << "before set SetWindowPos";
                //
                ::SetForegroundWindow(hwnd);
                ::ShowWindow(hwnd, SW_RESTORE);
                //::SetWindowPos(hwnd,HWND_TOP ,0,0,600,400,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
                break;
            }
        }

    }
    AfterHwnd = hwnd;
    }
}
*/
void SimulatorDlg::setLabelText(QString str, int value)
{
    ui->label->setText(str);
    ui->progressBar->setValue(value);
}
