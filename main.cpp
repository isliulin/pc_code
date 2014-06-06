#include <QtGui/QApplication>
#include "Frame/mainwindow.h"
#include <qtextcodec.h>
#include <QTranslator>
//#include <QCleanlooksStyle>
#include <QSplashScreen>
#include <QThread>
#include "transparent.h"
#include <windows.h>
#include "Frame/qmystyle.h"

#define CURRENT_SVN_VERSION 3455
QTranslator *translator ;
bool  is_tanslator;
QString exePath;
class MyThread : public QThread
{
   public:
       virtual void run();
 };
void MyThread::run()
{
   for( int count = 0; count < 2; count++ ) {
       sleep(0.5 );
   }
}
bool IsAdministrator();
//
int main(int argc, char *argv[])
{

    qDebug()<<"VERSION"<< CURRENT_SVN_VERSION;
    for(int i=0; i< argc; i++)
    {
        //qDebug() <<QString("arg %1:").arg(i)<< QString::fromLocal8Bit(argv[i]);
    }

    exePath = QDir::currentPath();
    if(argc>0)//设置当前程序路径为安装路径而不是文档路径
    {
        exePath = QString::fromLocal8Bit(argv[0]);
        exePath = exePath.left(exePath.lastIndexOf("\\"));
        QDir::setCurrent(exePath);
        //qDebug() <<"set current path :"<<exePath;
    }
    //wxy 修改win7下工具栏多行显示背景颜色不一致的问题
    if(QSysInfo::windowsVersion() == QSysInfo::WV_VISTA
       || QSysInfo::windowsVersion() == QSysInfo::WV_WINDOWS7)
    {
        QApplication::setStyle(new QMyStyleVista());
    }
//    else
//    {
//        QApplication::setStyle(new QMyStyleXP());
//    }
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    a.setOrganizationName(PRO_FULL_NAME);
    a.setApplicationName("recent pro files");


    translator = new QTranslator();

    //根据安装选择语言设置打开软件默认语言
    QSettings *readIni = new QSettings("language.ini", QSettings::IniFormat, 0);
    readIni->beginGroup("language");
    QStringList keys = readIni->allKeys();
    qDebug()<<keys.size();
    for(int i=0; i<keys.size(); i++)
    {
        qDebug()<<keys[i]<<endl;
        QString str = readIni->value(keys[i]).toString();
        qDebug()<<"str = "<<str<<endl;
       // str ="";
        if(str=="chinese" || str == "ChineseTrad")
        {
            is_tanslator=0;
        }
        else
        {
            is_tanslator=1;
        }

    }

    if(!IsAdministrator())
    {
        QString str1;
        QString str2;
        QString str3;
        if(0 == is_tanslator)//中文
        {
            str1 = QObject::tr("提示");
            str2 = PRO_FULL_NAME + QObject::tr(" 需要以管理员身份运行");
            str3 = QObject::tr("确定");
        }
        else
        {
            str1 = QObject::tr("Tips");
            str2 = PRO_FULL_NAME + QObject::tr(" Need To Run As Administrator");
            str3 = QObject::tr("OK");
        }

        QMessageBox box(QMessageBox::Information, str1, str2, QMessageBox::Ok,0,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(str3);
        box.exec();

        return 0;
    }

    QSplashScreen *splash;
    splash= new QSplashScreen;

#ifdef AK_SAMKOON
    splash->setPixmap(QPixmap(":/splash/images/setup3.4.jpg"));
#else define LA_DEBINUO
    splash->setPixmap(QPixmap(":/standardtool/images/setup_debinuo.jpg"));
#endif

    splash->show();

    qRegisterMetaType<MSG_TYPE>("MSG_TYPE");

    MainWindow w;

    w.SetCurrentPath(exePath);
    MyThread aa;
    aa.start();
    aa.wait();
    if(argc>1)
    {
        QString path;
        path = QString::fromLocal8Bit(argv[1]);//argv[1];
        w.createopenprodlg(path);
    }
    w.show();
    w.showMaximized() ;
    splash->finish(&w);
    delete splash;

    return a.exec();
}

bool IsAdministrator()
{//判断是否管理员模式

    bool bIsElevated = FALSE;
    HANDLE hToken = NULL;
    unsigned short uWinVer = LOWORD(GetVersion());
    uWinVer = MAKEWORD(HIBYTE(uWinVer),LOBYTE(uWinVer));

    if(uWinVer < 0x0600)//不是VISTA、Windows7
        return(true);

    if (OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY,&hToken))
    {
        qDebug() << "OpenProcessToken";
        struct {
            DWORD TokenIsElevated;
        } /*TOKEN_ELEVATION*/te;
        DWORD dwReturnLength = 0;

        if (GetTokenInformation(hToken,(_TOKEN_INFORMATION_CLASS)20,&te,sizeof(te),&dwReturnLength))
        {
            qDebug() << "GetTokenInformation";
            if (dwReturnLength == sizeof(te))
                bIsElevated = te.TokenIsElevated;
        }
        CloseHandle( hToken );
        qDebug() << "CloseHandle";
    }
    return bIsElevated;
}
