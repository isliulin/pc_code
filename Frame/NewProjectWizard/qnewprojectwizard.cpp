#include "qnewprojectwizard.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include  "Frame\mainwindow.h"
extern MainWindow *pwnd;
QNewProjectWizard::QNewProjectWizard(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::QNewProjectWizard)
{
    ui->setupUi(this);

    ui->showmodel_2->addItem(tr("3.5 inch"));
    ui->showmodel_2->addItem(tr("4.0 inch"));
    ui->showmodel_2->addItem(tr("4.3 inch"));
    ui->showmodel_2->addItem(tr("5.0 inch"));
    ui->showmodel_2->addItem(tr("7.0 inch"));
    ui->showmodel_2->addItem(tr("10.2 inch"));
    ui->showmodel_2->addItem(tr("其他尺寸"));
    ui->showmodel_2->setCurrentIndex(4);

    QString currentPath = QDir::currentPath();
    currentPath += "\\Project\\";
    currentPath.replace("/","\\");
    QDir dir(currentPath);
    if(!dir.exists())
    {
        dir.mkdir(dir.absolutePath());
    }
    ui->newpro_label_pos->setText(currentPath);

    /*************读取文件*********************/
    QFile file("modle.dat");//打开文件，该文件存储的是HMI型号的相关信息
    QStringList list;//定义插入列表的list
    int a7inch = 0;//该变量存储的是10寸屏所在文件中的位置
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString line;//临时变量，存储从文件取出的一行数据
        QTextStream stream(&file);//定义操作文件的变量
        line=stream.readLine();//文件第一行存储的是型号的个数
        bool ok;
        int hmimodelcount=line.toInt(&ok,10);//把得到的QString类型的数据转换为整型
        //for循环执行的是把触摸屏型号信息取出，然后添加到控件上显示
        int count = -1;
        for(int temp=0;temp<hmimodelcount;temp++)
        {
            line=stream.readLine().split("(").at(0);
            if(line.contains("-070"))//7寸的机器
            {
                count++;
                if(line == (PRO_TYPE))//得到7寸触摸屏的位置，该型号是默认型号
                {
                    a7inch = count;
                }
                //ui->HMImodel->addItem(line);
            }
        }
    }
    else
    {
        QMessageBox box(this);
        box.setText(tr("文件被损坏，请重新安装软件！"));
        box.exec();
        return;
    }
    //设置10寸屏为新建的时候的默认型号
    if(a7inch < 0)
    {
        ui->HMImodel->setCurrentIndex(0);
    }
    else
    {
        ui->HMImodel->setCurrentIndex(a7inch);
    }

    list << QObject::tr("水平") << QObject::tr("垂直");
    ui->showmodel->addItems(list);//显示方式
    ui->showmodel->setCurrentIndex(0);
    file.close();
}

QNewProjectWizard::~QNewProjectWizard()
{
    delete ui;

}

/***********************************************************************************
  *新建工程页面浏览按钮的鼠标点击槽函数
************************************************************************************/
void QNewProjectWizard::on_newpro_pushButton_clicked()
{
   QString dir = QFileDialog::getExistingDirectory(this,0,"/home",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);

   if(dir=="")
   {
       return;
   }
   else
   {
       QString ss=QString("%1\\").arg(dir.replace("/","\\")); //changed by zqh on 2011.8.10
       ui->newpro_label_pos->setText(ss);
   }
}


void QNewProjectWizard::on_HMImodel_currentIndexChanged(QString index)
{
    QFile file("modle.dat");//打开文件，该文件存储的是HMI型号的相关信息
    QString dataindex="#"+index;

    QString line;//临时变量，存储从文件取出的一行数据
    QTextStream stream(&file);//定义操作文件的变量

    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        while(!stream.atEnd())
        {
            line=stream.readLine();//文件第一行存储的是型号的个数
            if(line==dataindex)
            {
                break;
             }
        }
    }

    line=stream.readLine();
    ui->modelsize->setText(line);
    line=stream.readLine();
    ui->resolution->setText(line);
    line=stream.readLine();
    ui->color->setText(line);
    line=stream.readLine();
    ui->usermemory->setText(line);
    line=stream.readLine();
    ui->usermemory_2->setText(line);
    line=stream.readLine();
    ui->powersupply->setText(line);
    line=stream.readLine();
    ui->com1->setText(line);
    line=stream.readLine();
    ui->com2->setText(line);
    line=stream.readLine();
    ui->usb->setText(line);
    line=stream.readLine();
    ui->maxscreennumber->setText(line);
    file.close();
    initHIMSetting();//触摸屏一般参数设置初始化
}

////触摸屏一般参数设置初始化
void QNewProjectWizard::initHIMSetting()
{
    pwnd->m_pSamSysParame->m_projectProp.sPjtModel =ui->HMImodel->currentText();//工程型号
    pwnd->m_pSamSysParame->m_projectProp.nDisplayMode =0;//显示模式
    pwnd->m_pSamSysParame->m_projectProp.nStartScreenIndex =0;//启动画面
    pwnd->m_pSamSysParame->m_projectProp.nScreensaverTimer =1;//屏保时间
    pwnd->m_pSamSysParame->m_projectProp.nFlickerFqc =10;//闪烁频率
    pwnd->m_pSamSysParame->m_projectProp.bHaveAlarmVoice =0;//是否报警声音
    pwnd->m_pSamSysParame->m_projectProp.bHaveTouchVoice =1;//是否触摸声音
    pwnd->m_pSamSysParame->m_projectProp.nDefautUserId =0;//默认用户等级
    pwnd->m_pSamSysParame->m_projectProp.bScreensaver =0;//是否屏保
    pwnd->m_pSamSysParame->m_projectProp.nScreensaverIndex =0;//屏保画面
    pwnd->m_pSamSysParame->m_projectProp.bLoadInitScene =0;//是否载入画面
    pwnd->m_pSamSysParame->m_projectProp.nLoadSceneIndex =0;   //载入画面
    pwnd->m_pSamSysParame->m_projectProp.nLoadSceneTime =0;//载入时间
    pwnd->m_pSamSysParame->m_projectProp.bUseHighLevelPWD = false;//是否使用最高权限密码
    pwnd->m_pSamSysParame->m_projectProp.bNeedUpLoad =0; //使能上载
    pwnd->m_pSamSysParame->m_projectProp.bAccessOperate =0;//权限操作
    pwnd->m_pSamSysParame->m_projectProp.sHighLevelPWD ="";//最高权限密码
    pwnd->m_pSamSysParame->m_projectProp.bUploadComNeedPWD =0;//是否使用上载密码
    pwnd->m_pSamSysParame->m_projectProp.sUploadComPWD ="";//上载密码
    DrawScreenSize();
}
void QNewProjectWizard::DrawScreenSize()
{
    QFile file("modle.dat");//打开文件，该文件存储的是HMI型号的相关信息
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString line;//临时变量，存储从文件取出的一行数据
        QString sModel;//文件变量
        QTextStream stream(&file);//定义操作文件的变量
        line=stream.readLine();//文件第一行存储的是型号的个数
        int hmimodelcount=line.toInt();//把得到的QString类型的数据转换为整型该行存储的是所有型号的个数
        for(int temp=0;temp<hmimodelcount;temp++)
        {
            sModel=stream.readLine();
            line=sModel.split("(").at(0);
            if(line==ui->HMImodel->currentText())//得到当前选择的型号位置 以便于取分辨率
            {
                break;
            }
        }
        QString sWidth ; //SA的宽度
        QString sHeight; //SA高度
        int nIndex = 0;      //左括号(‘(’)在字符串的下标位置
        int nStarIndex = 0;  //*星号在字符串中下标位置
        int nSpaceIndex = 0; //*星号后空格在字符串中下标位置

        int nWidth = 0 ;    //SA的宽度
        int nHeight = 0;    //SA高度

        nIndex = sModel.indexOf("(");             //左括号(‘(’)在字符串的下标位置
        nStarIndex = sModel.indexOf("*");         //*星号在字符串中下标位置
        nSpaceIndex = sModel.indexOf(" ",nStarIndex); //*星号后空格在字符串中下标位置

        sWidth = sModel.mid(nIndex+1,nStarIndex - (nIndex+1));
        nWidth = sWidth.toInt();   //把宽度字符串转化为int
        sHeight = sModel.mid(nStarIndex+1,nSpaceIndex - (nStarIndex+1));
        nHeight = sHeight.toInt(); //把高度字符串转化为int
        pwnd->m_pSamSysParame->m_projectProp.nSceneWidth =nWidth;
        pwnd->m_pSamSysParame->m_projectProp.nSceneHeight =nHeight;
    }
}

void QNewProjectWizard::on_showmodel_currentIndexChanged(int index)
{
    QFile file("modle.dat");//打开文件，该文件存储的是HMI型号的相关信息
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString line;//临时变量，存储从文件取出的一行数据
        QString sModel;//文件变量
        QTextStream stream(&file);//定义操作文件的变量
        line=stream.readLine();//文件第一行存储的是型号的个数
        int hmimodelcount=line.toInt();//把得到的QString类型的数据转换为整型该行存储的是所有型号的个数
        for(int temp=0;temp<hmimodelcount;temp++)
        {
            sModel=stream.readLine();
            line=sModel.split("(").at(0);
            if(line==ui->HMImodel->currentText())//得到当前选择的型号位置 以便于取分辨率
            {
                break;
            }
        }
        QString sWidth ; //SA的宽度
        QString sHeight; //SA高度
        int nIndex = 0;      //左括号(‘(’)在字符串的下标位置
        int nStarIndex = 0;  //*星号在字符串中下标位置
        int nSpaceIndex = 0; //*星号后空格在字符串中下标位置

        int nWidth = 0 ;    //SA的宽度
        int nHeight = 0;    //SA高度

        nIndex = sModel.indexOf("(");             //左括号(‘(’)在字符串的下标位置
        nStarIndex = sModel.indexOf("*");         //*星号在字符串中下标位置
        nSpaceIndex = sModel.indexOf(" ",nStarIndex); //*星号后空格在字符串中下标位置

        sWidth = sModel.mid(nIndex+1,nStarIndex - (nIndex+1));
        nWidth = sWidth.toInt();   //把宽度字符串转化为int
        sHeight = sModel.mid(nStarIndex+1,nSpaceIndex - (nStarIndex+1));
        nHeight = sHeight.toInt(); //把高度字符串转化为int
        if(index == 0)//水平模式
        {
            pwnd->m_pSamSysParame->m_projectProp.nSceneWidth =nWidth;
            pwnd->m_pSamSysParame->m_projectProp.nSceneHeight =nHeight;
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_eScreenDir = scrHorizontal;
        }
        else if(index == 1)//垂直模式
        {
            pwnd->m_pSamSysParame->m_projectProp.nSceneWidth =nHeight;
            pwnd->m_pSamSysParame->m_projectProp.nSceneHeight =nWidth;
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_eScreenDir = scrVertical;
        }
    }
}

void QNewProjectWizard::on_showmodel_2_currentIndexChanged(QString str)
{
    ui->HMImodel->clear();
    QFile file("modle.dat");//打开文件，该文件存储的是HMI型号的相关信息
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString     line;//临时变量，存储从文件取出的一行数据
        bool        ok;
        QTextStream stream(&file);//定义操作文件的变量

        line = stream.readLine();//文件第一行存储的是型号的个数
        int hmimodelcount = line.toInt(&ok,10);//把得到的QString类型的数据转换为整型
        if(str == "3.5 inch")
        {
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line=stream.readLine().split("(").at(0);
                #ifdef AK_SAMKOON
                    if(line.contains("-035"))
                #else define LA_DEBINUO
                    if(line.contains("-1035"))
                #endif
                {
                    ui->HMImodel->addItem(line);
                }
            }
        }
        else if(str == "4.0 inch")
        {
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line=stream.readLine().split("(").at(0);
                #ifdef AK_SAMKOON
                if(line.contains("-040"))
                #else define LA_DEBINUO
                if(line.contains("-1040"))
                #endif
                {
                    ui->HMImodel->addItem(line);
                }
            }
        }
        else if(str == "4.3 inch")
        {
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line=stream.readLine().split("(").at(0);
                #ifdef AK_SAMKOON
                if(line.contains("-043"))
                #else define LA_DEBINUO
                if(line.contains("-1043"))
                #endif
                {
                    ui->HMImodel->addItem(line);
                }
            }
        }
        else if(str == "5.0 inch")
        {
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line=stream.readLine().split("(").at(0);
                #ifdef AK_SAMKOON
                if(line.contains("-050"))
                #else define LA_DEBINUO
                if(line.contains("-1050"))
                #endif
                {
                    ui->HMImodel->addItem(line);
                }
            }
        }
        else if(str == "7.0 inch")
        {
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line=stream.readLine().split("(").at(0);
                #ifdef AK_SAMKOON
                if(line.contains("-070"))
                #else define LA_DEBINUO
                if(line.contains("-1070"))
                #endif
                {
                    ui->HMImodel->addItem(line);
                }
            }
        }
        else if(str == "10.2 inch")//"10.2 inch"
        {
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line=stream.readLine().split("(").at(0);
                #ifdef AK_SAMKOON
                if(line.contains("-102"))
                #else define LA_DEBINUO
                if(line.contains("-1102"))
                #endif
                {
                    ui->HMImodel->addItem(line);
                }
            }
        }
        else
        {
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line=stream.readLine().split("(").at(0);
                #ifdef AK_SAMKOON
                if(!line.contains("-102") && !line.contains("-070") && !line.contains("-050")
                    && !line.contains("-043") && !line.contains("-040") && !line.contains("-035"))
                #else define LA_DEBINUO
                    if(!line.contains("-1102") && !line.contains("-1070") && !line.contains("-1050")
                        && !line.contains("-1043") && !line.contains("-1040") && !line.contains("-1035"))
                #endif
                {
                    ui->HMImodel->addItem(line);
                }
            }
        }
    }
    else
    {
        QMessageBox box(this);
        box.setText(tr("文件被损坏，请重新安装软件！"));
        box.exec();
        return;
    }

    ui->HMImodel->setCurrentIndex(0);
    file.close();

    QString strs = ui->HMImodel->currentText();
    on_HMImodel_currentIndexChanged(strs);
}














