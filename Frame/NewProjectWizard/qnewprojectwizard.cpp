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
    ui->showmodel_2->addItem(tr("�����ߴ�"));
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

    /*************��ȡ�ļ�*********************/
    QFile file("modle.dat");//���ļ������ļ��洢����HMI�ͺŵ������Ϣ
    QStringList list;//��������б��list
    int a7inch = 0;//�ñ����洢����10���������ļ��е�λ��
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString line;//��ʱ�������洢���ļ�ȡ����һ������
        QTextStream stream(&file);//��������ļ��ı���
        line=stream.readLine();//�ļ���һ�д洢�����ͺŵĸ���
        bool ok;
        int hmimodelcount=line.toInt(&ok,10);//�ѵõ���QString���͵�����ת��Ϊ����
        //forѭ��ִ�е��ǰѴ������ͺ���Ϣȡ����Ȼ����ӵ��ؼ�����ʾ
        int count = -1;
        for(int temp=0;temp<hmimodelcount;temp++)
        {
            line=stream.readLine().split("(").at(0);
            if(line.contains("-070"))//7��Ļ���
            {
                count++;
                if(line == (PRO_TYPE))//�õ�7�紥������λ�ã����ͺ���Ĭ���ͺ�
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
        box.setText(tr("�ļ����𻵣������°�װ�����"));
        box.exec();
        return;
    }
    //����10����Ϊ�½���ʱ���Ĭ���ͺ�
    if(a7inch < 0)
    {
        ui->HMImodel->setCurrentIndex(0);
    }
    else
    {
        ui->HMImodel->setCurrentIndex(a7inch);
    }

    list << QObject::tr("ˮƽ") << QObject::tr("��ֱ");
    ui->showmodel->addItems(list);//��ʾ��ʽ
    ui->showmodel->setCurrentIndex(0);
    file.close();
}

QNewProjectWizard::~QNewProjectWizard()
{
    delete ui;

}

/***********************************************************************************
  *�½�����ҳ�������ť��������ۺ���
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
    QFile file("modle.dat");//���ļ������ļ��洢����HMI�ͺŵ������Ϣ
    QString dataindex="#"+index;

    QString line;//��ʱ�������洢���ļ�ȡ����һ������
    QTextStream stream(&file);//��������ļ��ı���

    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        while(!stream.atEnd())
        {
            line=stream.readLine();//�ļ���һ�д洢�����ͺŵĸ���
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
    initHIMSetting();//������һ��������ó�ʼ��
}

////������һ��������ó�ʼ��
void QNewProjectWizard::initHIMSetting()
{
    pwnd->m_pSamSysParame->m_projectProp.sPjtModel =ui->HMImodel->currentText();//�����ͺ�
    pwnd->m_pSamSysParame->m_projectProp.nDisplayMode =0;//��ʾģʽ
    pwnd->m_pSamSysParame->m_projectProp.nStartScreenIndex =0;//��������
    pwnd->m_pSamSysParame->m_projectProp.nScreensaverTimer =1;//����ʱ��
    pwnd->m_pSamSysParame->m_projectProp.nFlickerFqc =10;//��˸Ƶ��
    pwnd->m_pSamSysParame->m_projectProp.bHaveAlarmVoice =0;//�Ƿ񱨾�����
    pwnd->m_pSamSysParame->m_projectProp.bHaveTouchVoice =1;//�Ƿ�������
    pwnd->m_pSamSysParame->m_projectProp.nDefautUserId =0;//Ĭ���û��ȼ�
    pwnd->m_pSamSysParame->m_projectProp.bScreensaver =0;//�Ƿ�����
    pwnd->m_pSamSysParame->m_projectProp.nScreensaverIndex =0;//��������
    pwnd->m_pSamSysParame->m_projectProp.bLoadInitScene =0;//�Ƿ����뻭��
    pwnd->m_pSamSysParame->m_projectProp.nLoadSceneIndex =0;   //���뻭��
    pwnd->m_pSamSysParame->m_projectProp.nLoadSceneTime =0;//����ʱ��
    pwnd->m_pSamSysParame->m_projectProp.bUseHighLevelPWD = false;//�Ƿ�ʹ�����Ȩ������
    pwnd->m_pSamSysParame->m_projectProp.bNeedUpLoad =0; //ʹ������
    pwnd->m_pSamSysParame->m_projectProp.bAccessOperate =0;//Ȩ�޲���
    pwnd->m_pSamSysParame->m_projectProp.sHighLevelPWD ="";//���Ȩ������
    pwnd->m_pSamSysParame->m_projectProp.bUploadComNeedPWD =0;//�Ƿ�ʹ����������
    pwnd->m_pSamSysParame->m_projectProp.sUploadComPWD ="";//��������
    DrawScreenSize();
}
void QNewProjectWizard::DrawScreenSize()
{
    QFile file("modle.dat");//���ļ������ļ��洢����HMI�ͺŵ������Ϣ
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString line;//��ʱ�������洢���ļ�ȡ����һ������
        QString sModel;//�ļ�����
        QTextStream stream(&file);//��������ļ��ı���
        line=stream.readLine();//�ļ���һ�д洢�����ͺŵĸ���
        int hmimodelcount=line.toInt();//�ѵõ���QString���͵�����ת��Ϊ���͸��д洢���������ͺŵĸ���
        for(int temp=0;temp<hmimodelcount;temp++)
        {
            sModel=stream.readLine();
            line=sModel.split("(").at(0);
            if(line==ui->HMImodel->currentText())//�õ���ǰѡ����ͺ�λ�� �Ա���ȡ�ֱ���
            {
                break;
            }
        }
        QString sWidth ; //SA�Ŀ��
        QString sHeight; //SA�߶�
        int nIndex = 0;      //������(��(��)���ַ������±�λ��
        int nStarIndex = 0;  //*�Ǻ����ַ������±�λ��
        int nSpaceIndex = 0; //*�Ǻź�ո����ַ������±�λ��

        int nWidth = 0 ;    //SA�Ŀ��
        int nHeight = 0;    //SA�߶�

        nIndex = sModel.indexOf("(");             //������(��(��)���ַ������±�λ��
        nStarIndex = sModel.indexOf("*");         //*�Ǻ����ַ������±�λ��
        nSpaceIndex = sModel.indexOf(" ",nStarIndex); //*�Ǻź�ո����ַ������±�λ��

        sWidth = sModel.mid(nIndex+1,nStarIndex - (nIndex+1));
        nWidth = sWidth.toInt();   //�ѿ���ַ���ת��Ϊint
        sHeight = sModel.mid(nStarIndex+1,nSpaceIndex - (nStarIndex+1));
        nHeight = sHeight.toInt(); //�Ѹ߶��ַ���ת��Ϊint
        pwnd->m_pSamSysParame->m_projectProp.nSceneWidth =nWidth;
        pwnd->m_pSamSysParame->m_projectProp.nSceneHeight =nHeight;
    }
}

void QNewProjectWizard::on_showmodel_currentIndexChanged(int index)
{
    QFile file("modle.dat");//���ļ������ļ��洢����HMI�ͺŵ������Ϣ
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString line;//��ʱ�������洢���ļ�ȡ����һ������
        QString sModel;//�ļ�����
        QTextStream stream(&file);//��������ļ��ı���
        line=stream.readLine();//�ļ���һ�д洢�����ͺŵĸ���
        int hmimodelcount=line.toInt();//�ѵõ���QString���͵�����ת��Ϊ���͸��д洢���������ͺŵĸ���
        for(int temp=0;temp<hmimodelcount;temp++)
        {
            sModel=stream.readLine();
            line=sModel.split("(").at(0);
            if(line==ui->HMImodel->currentText())//�õ���ǰѡ����ͺ�λ�� �Ա���ȡ�ֱ���
            {
                break;
            }
        }
        QString sWidth ; //SA�Ŀ��
        QString sHeight; //SA�߶�
        int nIndex = 0;      //������(��(��)���ַ������±�λ��
        int nStarIndex = 0;  //*�Ǻ����ַ������±�λ��
        int nSpaceIndex = 0; //*�Ǻź�ո����ַ������±�λ��

        int nWidth = 0 ;    //SA�Ŀ��
        int nHeight = 0;    //SA�߶�

        nIndex = sModel.indexOf("(");             //������(��(��)���ַ������±�λ��
        nStarIndex = sModel.indexOf("*");         //*�Ǻ����ַ������±�λ��
        nSpaceIndex = sModel.indexOf(" ",nStarIndex); //*�Ǻź�ո����ַ������±�λ��

        sWidth = sModel.mid(nIndex+1,nStarIndex - (nIndex+1));
        nWidth = sWidth.toInt();   //�ѿ���ַ���ת��Ϊint
        sHeight = sModel.mid(nStarIndex+1,nSpaceIndex - (nStarIndex+1));
        nHeight = sHeight.toInt(); //�Ѹ߶��ַ���ת��Ϊint
        if(index == 0)//ˮƽģʽ
        {
            pwnd->m_pSamSysParame->m_projectProp.nSceneWidth =nWidth;
            pwnd->m_pSamSysParame->m_projectProp.nSceneHeight =nHeight;
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_eScreenDir = scrHorizontal;
        }
        else if(index == 1)//��ֱģʽ
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
    QFile file("modle.dat");//���ļ������ļ��洢����HMI�ͺŵ������Ϣ
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString     line;//��ʱ�������洢���ļ�ȡ����һ������
        bool        ok;
        QTextStream stream(&file);//��������ļ��ı���

        line = stream.readLine();//�ļ���һ�д洢�����ͺŵĸ���
        int hmimodelcount = line.toInt(&ok,10);//�ѵõ���QString���͵�����ת��Ϊ����
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
        box.setText(tr("�ļ����𻵣������°�װ�����"));
        box.exec();
        return;
    }

    ui->HMImodel->setCurrentIndex(0);
    file.close();

    QString strs = ui->HMImodel->currentText();
    on_HMImodel_currentIndexChanged(strs);
}














