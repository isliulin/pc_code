#include "modelsel.h"
#include "ui_modelsel.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

ModelSel::ModelSel(QWidget *parent):QDialog(parent),ui(new Ui::ModelSel)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setFixedSize(size());
    setWindowTitle(tr("机型选择"));

    ui->HMImodel_2->addItem(tr("3.5 inch"));
    ui->HMImodel_2->addItem(tr("4.0 inch"));
    ui->HMImodel_2->addItem(tr("4.3 inch"));
    ui->HMImodel_2->addItem(tr("5.0 inch"));
    ui->HMImodel_2->addItem(tr("7.0 inch"));
    ui->HMImodel_2->addItem(tr("10.2 inch"));
    ui->HMImodel_2->addItem(tr("其他尺寸"));

    /*************读取文件*********************/
    QFile       file("modle.dat");  //打开文件，该文件存储的是HMI型号的相关信息
    QStringList list;               //定义插入列表的list

    QString strName = pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName;
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QString     line;           //临时变量，存储从文件取出的一行数据
        QTextStream stream(&file);  //定义操作文件的变量
        line = stream.readLine();   //文件第一行存储的是型号的个数
        bool ok;
        int hmimodelcount=line.toInt(&ok,10);//把得到的QString类型的数据转换为整型

        //for循环执行的是把触摸屏型号信息取出，然后添加到控件上显示
#ifdef AK_SAMKOON
        if(strName.contains("-035"))
        {
            ui->HMImodel_2->setCurrentIndex(0);
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line = stream.readLine().split("(").at(0);
                if(line.contains("-035"))
                {
                    //ui->HMImodel->addItem(line);
                }
            }
        }
        else if(strName.contains("-040"))
        {
            ui->HMImodel_2->setCurrentIndex(1);
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line = stream.readLine().split("(").at(0);
                if(line.contains("-040"))
                {
                    //ui->HMImodel->addItem(line);
                }
            }
        }
        else if(strName.contains("-043"))
        {
            ui->HMImodel_2->setCurrentIndex(2);
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line = stream.readLine().split("(").at(0);
                if(line.contains("-043"))
                {
                    //ui->HMImodel->addItem(line);
                }
            }
        }
        else if(strName.contains("-050"))
        {
            ui->HMImodel_2->setCurrentIndex(3);
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line = stream.readLine().split("(").at(0);
                if(line.contains("-050"))
                {
                    //ui->HMImodel->addItem(line);
                }
            }
        }
        else if(strName.contains("-070"))
        {
            ui->HMImodel_2->setCurrentIndex(4);
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line = stream.readLine().split("(").at(0);
                if(line.contains("-070"))
                {
                    //ui->HMImodel->addItem(line);
                }
            }
        }
        else if(strName.contains("-102"))
        {
            ui->HMImodel_2->setCurrentIndex(5);
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line = stream.readLine().split("(").at(0);
                if(line.contains("-102"))
                {
                    //ui->HMImodel->addItem(line);
                }
            }
        }
        else//其他尺寸
        {
            ui->HMImodel_2->setCurrentIndex(6);

        }
#else define LA_DEBINUO
        if(strName.contains("-1035"))
        {
            ui->HMImodel_2->setCurrentIndex(0);
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line = stream.readLine().split("(").at(0);
                if(line.contains("-1035"))
                {
                    //ui->HMImodel->addItem(line);
                }
            }
        }
        else if(strName.contains("-1040"))
        {
            ui->HMImodel_2->setCurrentIndex(1);
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line = stream.readLine().split("(").at(0);
                if(line.contains("-1040"))
                {
                    //ui->HMImodel->addItem(line);
                }
            }
        }
        else if(strName.contains("-1043"))
        {
            ui->HMImodel_2->setCurrentIndex(2);
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line = stream.readLine().split("(").at(0);
                if(line.contains("-1043"))
                {
                    //ui->HMImodel->addItem(line);
                }
            }
        }
        else if(strName.contains("-1050"))
        {
            ui->HMImodel_2->setCurrentIndex(3);
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line = stream.readLine().split("(").at(0);
                if(line.contains("-1050"))
                {
                    //ui->HMImodel->addItem(line);
                }
            }
        }
        else if(strName.contains("-1070"))
        {
            ui->HMImodel_2->setCurrentIndex(4);
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line = stream.readLine().split("(").at(0);
                if(line.contains("-1070"))
                {
                    //ui->HMImodel->addItem(line);
                }
            }
        }
        else if(strName.contains("-1102"))
        {
            ui->HMImodel_2->setCurrentIndex(5);
            for(int temp = 0; temp < hmimodelcount; temp++)
            {
                line = stream.readLine().split("(").at(0);
                if(line.contains("-1102"))
                {
                    //ui->HMImodel->addItem(line);
                }
            }
        }
        else//其他尺寸
        {
            ui->HMImodel_2->setCurrentIndex(6);
        }
#endif

    }
    else
    {
        QMessageBox box(this);
        box.setText(tr("文件被损坏，请重新安装软件！"));
        box.exec();
        return;
    }

    //设置10寸屏为新建的时候的默认型号
    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName == "")
    {
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName = pwnd->newpro->newprowizard_model;
        if(pwnd->newpro->newprowizard_showmodel == tr("垂直"))
        {
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_eScreenDir = scrVertical;
        }
        else
        {
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_eScreenDir = scrHorizontal;
        }
    }
    int index = ui->HMImodel->findText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName);
    if(index < 0)
    {
        ui->HMImodel->setCurrentIndex(0);
    }
    else
    {
        ui->HMImodel->setCurrentIndex(index);
    }

    list << QObject::tr("水平") << QObject::tr("垂直");

    ui->showmodel->addItems(list);//显示方式

    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_eScreenDir == scrVertical)//垂直
    {
        ui->showmodel->setCurrentIndex(1);
    }
    else
    {
        ui->showmodel->setCurrentIndex(0);
    }

    ui->lineEdit->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_strHmiName);//hmi别名

    file.close();
}

ModelSel::~ModelSel()
{
    delete ui;
}

void ModelSel::on_HMImodel_currentIndexChanged(QString index)
{
    QFile file("modle.dat");//打开文件，该文件存储的是HMI型号的相关信息
    QString dataindex = "#" + index;

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

    //initHIMSetting();//触摸屏一般参数设置初始化
}

void ModelSel::on_showmodel_currentIndexChanged(int index)
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

        QString sWidth ;        //SA的宽度
        QString sHeight;        //SA高度
        int nIndex      = 0;    //左括号(‘(’)在字符串的下标位置
        int nStarIndex  = 0;    //*星号在字符串中下标位置
        int nSpaceIndex = 0;    //*星号后空格在字符串中下标位置
        int nWidth      = 0;    //SA的宽度
        int nHeight     = 0;    //SA高度

        nIndex      = sModel.indexOf("(");              //左括号(‘(’)在字符串的下标位置
        nStarIndex  = sModel.indexOf("*");              //*星号在字符串中下标位置
        nSpaceIndex = sModel.indexOf(" ",nStarIndex);   //*星号后空格在字符串中下标位置

        sWidth  = sModel.mid(nIndex+1,nStarIndex - (nIndex+1));
        nWidth  = sWidth.toInt();   //把宽度字符串转化为int
        sHeight = sModel.mid(nStarIndex+1,nSpaceIndex - (nStarIndex+1));
        nHeight = sHeight.toInt(); //把高度字符串转化为int

        /*int totalSceneNum = pwnd->pSceneSheet.size();
        for(int icount = 0; icount < totalSceneNum; icount++)
        {
            if(pwnd->pSceneSheet[icount]->nIsSceneOrWindow == 2)//自定义键盘不操作
            {
                continue;
            }
            pwnd->OnNewGraphicsScene(index, nWidth, nHeight); //调用主框架中的画画面函数
        }

        if(index == 0)//水平模式
        {
            pwnd->m_pSamSysParame->m_projectProp.nSceneWidth =nWidth;
            pwnd->m_pSamSysParame->m_projectProp.nSceneHeight =nHeight;
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth = nWidth;
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight = nHeight;
        }
        else if(index == 1)//垂直模式
        {
            pwnd->m_pSamSysParame->m_projectProp.nSceneWidth =nHeight;
            pwnd->m_pSamSysParame->m_projectProp.nSceneHeight =nWidth;
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth = nHeight;
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight = nWidth;
        }*/
    }
    file.close();//add by wuxiyang
}

void ModelSel::on_pushButton_quit_clicked()
{
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelName = ui->HMImodel->currentText();//->itemText(ui->HMImodel->currentIndex());

    if(0 == ui->showmodel->currentIndex())
    {
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_eScreenDir = scrHorizontal;
    }
    else
    {
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_eScreenDir = scrVertical;
    }

    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strModelSize        = ui->modelsize->text();    //屏幕尺寸
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strResolution       = ui->resolution->text();   //分辨率
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strColor            = ui->color->text();        //色彩
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strUsermemory       = ui->usermemory->text();   //用户内存
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strNandFlash        = ui->usermemory_2->text();   //用户内存
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strPowersupply      = ui->powersupply->text();  //供电电源
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom1             = ui->com1->text();         //com口
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strCom2             = ui->com2->text();         //CAN总线
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strUsb              = ui->usb->text();          //USB
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strMaxscreennumber  = ui->maxscreennumber->text();//以太网
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_strHmiName          = ui->lineEdit->text();//hmi
    /*QString strResolution = ui->resolution->text();
    if(0 == ui->showmodel->currentIndex())
    {
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth  = strResolution.left(3).toInt();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight = strResolution.mid(4, 3).toInt();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth  = strResolution.left(3).toInt();  //分辨率宽
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight = strResolution.mid(4, 3).toInt();//分辨率高
    }
    else
    {
        pwnd->m_pSamSysParame->m_projectProp.nSceneWidth      = strResolution.mid(4, 3).toInt();
        pwnd->m_pSamSysParame->m_projectProp.nSceneHeight     = strResolution.left(3).toInt();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth  = strResolution.mid(4, 3).toInt();//分辨率高
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight = strResolution.left(3).toInt();  //分辨率宽
    }*/

    DrawScreenSize();

    accept();
}

void ModelSel::DrawScreenSize()
{
    QString sModel;//SA型号例如：SA--10.4A (800*600 10.4')

    QFile file("modle.dat");//打开文件，该文件存储的是HMI型号的相关信息
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QString line;//临时变量，存储从文件取出的一行数据
    QTextStream stream(&file);//定义操作文件的变量
    line=stream.readLine();//文件第一行存储的是型号的个数
    int hmimodelcount=line.toInt();//把得到的QString类型的数据转换为整型该行存储的是所有型号的个数
    for(int temp=0;temp<hmimodelcount;temp++)
    {
        sModel = stream.readLine();
        line = sModel.split("(").at(0);
        if(line == ui->HMImodel->currentText())//得到当前选择的型号位置 以便于取分辨率
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
    qreal qPointx = 0; //左坐标
    qreal qPointy = 0; //右坐标
    qreal qVal = 0; //临时变量
    QGraphicsItem *item = NULL;

    nIndex      = sModel.indexOf("(");             //左括号(‘(’)在字符串的下标位置
    nStarIndex  = sModel.indexOf("*");         //*星号在字符串中下标位置
    nSpaceIndex = sModel.indexOf(" ",nStarIndex); //*星号后空格在字符串中下标位置

    sWidth  = sModel.mid(nIndex+1,nStarIndex - (nIndex+1));
    nWidth  = sWidth.toInt();   //把宽度字符串转化为int
    sHeight = sModel.mid(nStarIndex+1,nSpaceIndex - (nStarIndex+1));
    nHeight = sHeight.toInt(); //把高度字符串转化为int

    double iScalex;//X方向的缩放比例
    double iScaley;//Y方向的缩放比例

    pwnd->newpro->newprowizard_model=ui->HMImodel->currentText();
    if(ui->showmodel->currentIndex() == 0)//水平模式
    {
        //计算水平模式下的缩放比例
        //iScalex = (double)pwnd->m_pSamSysParame->m_projectProp.nSceneWidth/nWidth;//X方向的缩放比例
        //iScaley = (double)pwnd->m_pSamSysParame->m_projectProp.nSceneHeight/nHeight;//Y方向的缩放比例
        iScalex = (double)pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth/nWidth;//X方向的缩放比例
        iScaley = (double)pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight/nHeight;//Y方向的缩放比例
        //pwnd->m_pSamSysParame->m_projectProp.nSceneWidth  = nWidth;//保存新的分辨率
        //pwnd->m_pSamSysParame->m_projectProp.nSceneHeight = nHeight;//保存新的分辨率
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth  = nWidth;//保存新的分辨率
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight = nHeight;//保存新的分辨率

        pwnd->m_pSamSysParame->m_projectProp.nSceneWidth = nWidth;
        pwnd->m_pSamSysParame->m_projectProp.nSceneHeight = nHeight ;
    }
    else if(ui->showmodel->currentIndex() == 1)//垂直模式-如果新选择的型号的垂直模式和之前选择的型号的水平模式分辨率一样的话
    {
        //计算垂直模式下的缩放比例
        //iScalex=(double)pwnd->m_pSamSysParame->m_projectProp.nSceneWidth/nHeight;//X方向的缩放比例
        //iScaley=(double)pwnd->m_pSamSysParame->m_projectProp.nSceneHeight/nWidth;//Y方向的缩放比例
        //pwnd->m_pSamSysParame->m_projectProp.nSceneWidth = nHeight;//保存新的分辨率
        //pwnd->m_pSamSysParame->m_projectProp.nSceneHeight = nWidth;//保存新的分辨率
        iScalex = (double)pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth/nHeight;//nHeight;//X方向的缩放比例
        iScaley = (double)pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight/nWidth;////Y方向的缩放比例

        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth  = nHeight;//保存新的分辨率
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight = nWidth;//保存新的分辨率

        pwnd->m_pSamSysParame->m_projectProp.nSceneWidth = nWidth;
        pwnd->m_pSamSysParame->m_projectProp.nSceneHeight = nHeight;
    }
    QList <QGraphicsItem *> selList;
    QGroupItem * group;
    int totalSceneNum = pwnd->pSceneSheet.size();
    for(int icount=0;icount<totalSceneNum;icount++)
    {
        if(pwnd->pSceneSheet[icount]->nIsSceneOrWindow == 2)//自定义键盘不操作
        {
            pwnd->pSceneSheet[icount]->DrawScreenSize();
            continue;
        }

        QPainterPath path;
        path.addRect(0,0,pwnd->pSceneSheet[icount]->width(),pwnd->pSceneSheet[icount]->height());
        //pwnd->pSceneSheet[icount]->setSelectionArea(path);
        selList = pwnd->pSceneSheet[icount]->TopItems();
        foreach(QGraphicsItem *pitem, selList)
        {
            pitem->setSelected(false);
        }

        for(int i = 0; i < selList.size(); i++)  //根据缩放比例重新调整控件的位置和大小
        {
            item    = selList.at(i);
            qPointx = item->boundingRect().left() + item->scenePos().x();//得到当前X坐标
            qPointx = qPointx / iScalex;//除缩放比例，得到新的位置
            qVal    = qPointx - item->boundingRect().x();
            selList.at(i)->setX(qVal);

            qPointy=item->boundingRect().top()+item->scenePos().y();//得到当前y坐标
            qPointy=qPointy/iScaley;//除缩放比例，得到新的位置
            qVal = qPointy - item->boundingRect().y();
            selList.at(i)->setY(qVal);
        }

            foreach(QGraphicsItem *pItem,pwnd->pSceneSheet[icount]->items())
            {
                if (pItem->type() == SAM_DRAW_OBJECT_PIXMAP)
                {
                    QPixmapItem *pTmp = NULL;
                    pTmp = dynamic_cast<QPixmapItem *> (pItem);
                    pTmp->boundRect = pTmp->sceneBoundingRect();
                }

            }
        for(int i = 0; i < selList.size(); i++)
        {
            if(selList.at(i)->data(GROUP_TYPE_KEY)==GROUP_TYPE_TIMER)//定时器不改变大小
            {
                continue;
            }
            item = selList.at(i);
            //begin 防止曲线 有箭头，矩形边框线不为1导致丢失曲线和矩形位置不对问题
            int nLineWidtch = 1;
            LINE_END_ARROW_STYLE_E eEndType = LINE_END_STYLE_NONE;
            if(SAM_DRAW_OBJECT_LINECIRCLE == item->type())
            {
                QLineCircleItem *pLineCircle = dynamic_cast<QLineCircleItem *> (item);
                if(pLineCircle)
                {
                    eEndType = (LINE_END_ARROW_STYLE_E)pLineCircle->getEndArrow();
                    pLineCircle->setEndArrow(LINE_END_STYLE_NONE);
                }
            }
            else  if(SAM_DRAW_OBJECT_LINECIRCLE_NEW == item->type())
            {
                QLineCircleBasicItem *pLineCircle = dynamic_cast<QLineCircleBasicItem *> (item);
                if(pLineCircle)
                {
                    eEndType = (LINE_END_ARROW_STYLE_E)pLineCircle->getEndArrow();
                    pLineCircle->setEndArrow(LINE_END_STYLE_NONE);
                }
            }
            else if(SAM_DRAW_OBJECT_RECT == item->type())
            {
                QRectItem *pRectItem = dynamic_cast<QRectItem *> (item);
                if(pRectItem)
                {
                    nLineWidtch = pRectItem->GetLineWidth();
                    if(1 != nLineWidtch)
                    {
                        pRectItem->SetLineWidth(1);
                    }
                }
            }
            else if(SAM_DRAW_OBJECT_RECT_NEW == item->type())
            {
                QRectBasicItem *pRectItem = dynamic_cast<QRectBasicItem *> (item);
                if(pRectItem)
                {
                    nLineWidtch = pRectItem->GetLineWidth();
                    if(1 != nLineWidtch)
                    {
                        pRectItem->SetLineWidth(1);
                    }
                }
            }
            //end 防止曲线 有箭头，矩形边框线不为1导致丢失曲线和矩形位置不对问题

            group=new QGroupItem(selList.at(i));
            group->SetWidth(item->sceneBoundingRect().width()/iScalex);
            group->SetHeigth(item->sceneBoundingRect().height()/iScaley);

            //begin 防止曲线 有箭头，矩形边框线不为1导致丢失曲线和矩形位置不对问题
            if(SAM_DRAW_OBJECT_LINECIRCLE == item->type()
                && LINE_END_STYLE_NONE != eEndType)
                {
                QLineCircleItem *pLineCircle = dynamic_cast<QLineCircleItem *> (item);
                if(pLineCircle)
                {
                    pLineCircle->setEndArrow(eEndType);
                }
            }
            else if(SAM_DRAW_OBJECT_LINECIRCLE_NEW == item->type()
                && LINE_END_STYLE_NONE != eEndType)
                {
                QLineCircleBasicItem *pLineCircle = dynamic_cast<QLineCircleBasicItem *> (item);
                if(pLineCircle)
                {
                    pLineCircle->setEndArrow(eEndType);
                }
            }
            else if(SAM_DRAW_OBJECT_RECT == item->type() && 1 != nLineWidtch)
            {
                QRectItem *pRectItem = dynamic_cast<QRectItem *> (item);
                if(pRectItem)
                {
                    pRectItem->SetLineWidth(nLineWidtch);
                }
            }
            else if(SAM_DRAW_OBJECT_RECT_NEW == item->type() && 1 != nLineWidtch)
            {
                QRectBasicItem *pRectItem = dynamic_cast<QRectBasicItem *> (item);
                if(pRectItem)
                {
                    pRectItem->SetLineWidth(nLineWidtch);
                }
            }
            //end 防止曲线 有箭头，矩形边框线不为1导致丢失曲线和矩形位置不对问题

            if(item->sceneBoundingRect().bottom() > 722)
            {
                item->setY(722 - item->sceneBoundingRect().height() - item->boundingRect().y());
            }
            if(item->sceneBoundingRect().right() > 1174)
            {
                item->setX(1174 - item->sceneBoundingRect().width() - item->boundingRect().x());
            }

            pwnd->ResetPic(item);
            bool bIsLocked = !(item->flags() & QGraphicsItem::ItemIsMovable);
            if(bIsLocked)
                reBondingTrackers(item,pwnd->pSceneSheet[icount]);
            delete group;
            group=NULL;
        }

        pwnd->pSceneSheet[icount]->reBondingTrackers();
        double tempWindowwidth;
        double tempWindowheigh;
        if(pwnd->pSceneSheet[icount]->nIsSceneOrWindow==0)
        {
            //tempWindowwidth=pwnd->m_pSamSysParame->m_projectProp.nSceneWidth;
            //tempWindowheigh=pwnd->m_pSamSysParame->m_projectProp.nSceneHeight;
            tempWindowwidth=pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth;
            tempWindowheigh=pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight;
        }
        else if(pwnd->pSceneSheet[icount]->nIsSceneOrWindow == 1)
        {
            tempWindowwidth=pwnd->pSceneSheet[icount]->width()/iScalex;
            tempWindowheigh=pwnd->pSceneSheet[icount]->height()/iScaley;
        }
        pwnd->pSceneSheet[icount]->setSceneRect(0,0,tempWindowwidth,tempWindowheigh);//设置场景大小
        pwnd->pSceneSheet[icount]->m_sceneRect = QRectF(0,0,tempWindowwidth,tempWindowheigh);
    }
    pwnd->newpro->newprowizard_showmodel=ui->showmodel->currentText();
    //pwnd->pView->setSceneRect(0,0,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight+100);//+100不要删除edit by zqh
}

void ModelSel::on_pushButton_help_clicked()
{
    pwnd->loadHelpHtm(TREE_MODELCHOICE);
}

void ModelSel::reBondingTrackers(QGraphicsItem *pselItem,QGraphicsScene *pScene)
{
    QRectItem *pRect     = 0;
    QElipseItem *pElipse = 0;
    QLineItem *pLine     = 0;
    QPolygonItem *pPolygon   = 0;
    QFoldLineItem *pFoldLine = 0;
    QFreeLineItem *pFreeLine = 0;
    QItemGroup *pItemGroup   = 0;
    QLineCircleItem *pLineCircle = 0;   //add by tanghaiguo
    QSimpleTextItem *pText = 0;
    QRoundedRect *pRoundedRect = 0;
    QArcItem *pArc = 0;

    QRectBasicItem *pRectNew     = 0;
    QElipseBasicItem *pElipseNew = 0;
    QLineBasicItem *pLineNew     = 0;
    QPolygonBasicItem *pPolygonNew   = 0;
    QFoldLineBasicItem *pFoldLineNew = 0;
    QFreeLineBasicItem *pFreeLineNew = 0;
    QLineCircleBasicItem *pLineCircleNew = 0;   //add by tanghaiguo
    QRoundedRectBasic *pRoundedRectNew = 0;
    QArcBasicItem *pArcNew = 0;

    bool bSelected = false;
    QRectF qrcBndRect;
    bool bIsLocked = true;

    if(!pselItem || !pScene)
    {
        return ;
    }

    qrcBndRect = pselItem->sceneBoundingRect();
    switch (pselItem->type())
    {
    case SAM_DRAW_OBJECT_RECT:
        pRect = dynamic_cast<QRectItem *> (pselItem);
        if (pRect)
        {
            pRect->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_ELIPSE:
        pElipse = dynamic_cast<QElipseItem *> (pselItem);
        if (pElipse)
        {
            pElipse->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_LINE:
        pLine = dynamic_cast<QLineItem *> (pselItem);
        if (pLine)
        {
            pLine->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_POLYGON:
        pPolygon = dynamic_cast<QPolygonItem *> (pselItem);
        if (pPolygon)
        {
            pPolygon->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_FOLDLINE:
        pFoldLine = dynamic_cast<QFoldLineItem *> (pselItem);
        if (pFoldLine)
        {
            pFoldLine->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_FREELINE:
        pFreeLine = dynamic_cast<QFreeLineItem *> (pselItem);
        if (pFreeLine)
        {
            pFreeLine->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_GROUP:
        pItemGroup = dynamic_cast<QItemGroup *> (pselItem);
        if (pItemGroup)
        {
            pItemGroup->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE:
        pLineCircle = dynamic_cast<QLineCircleItem *> (pselItem);
        if (pLineCircle)
        {
            pLineCircle->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_TEXT:
        pText = dynamic_cast<QSimpleTextItem *> (pselItem);
        if (pText)
        {
            pText->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
        pRoundedRect = dynamic_cast<QRoundedRect *> (pselItem);
        if (pRoundedRect)
        {
            pRoundedRect->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_ARC:
        pArc = dynamic_cast<QArcItem *> (pselItem);
        if (pArc)
        {
            qrcBndRect = pArc->getEllipseRect();
            qrcBndRect = pArc->mapRectToScene(qrcBndRect);
            pArc->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
/////////////////wxy add start
    case SAM_DRAW_OBJECT_RECT_NEW:
        pRectNew = dynamic_cast<QRectBasicItem *> (pselItem);
        if (pRectNew)
        {
            pRectNew->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_ELIPSE_NEW:
        pElipseNew = dynamic_cast<QElipseBasicItem *> (pselItem);
        if (pElipseNew)
        {
            pElipseNew->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_LINE_NEW:
        pLineNew = dynamic_cast<QLineBasicItem *> (pselItem);
        if (pLineNew)
        {
            pLineNew->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_POLYGON_NEW:
        pPolygonNew = dynamic_cast<QPolygonBasicItem *> (pselItem);
        if (pPolygonNew)
        {
            pPolygonNew->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_FOLDLINE_NEW:
        pFoldLineNew = dynamic_cast<QFoldLineBasicItem *> (pselItem);
        if (pFoldLineNew)
        {
            pFoldLineNew->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_FREELINE_NEW:
        pFreeLineNew = dynamic_cast<QFreeLineBasicItem *> (pselItem);
        if (pFreeLineNew)
        {
            pFreeLineNew->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE_NEW:
        pLineCircleNew = dynamic_cast<QLineCircleBasicItem *> (pselItem);
        if (pLineCircleNew)
        {
            pLineCircleNew->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT_NEW:
        pRoundedRectNew = dynamic_cast<QRoundedRectBasic *> (pselItem);
        if (pRoundedRectNew)
        {
            pRoundedRectNew->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
    case SAM_DRAW_OBJECT_ARC_NEW:
        pArcNew = dynamic_cast<QArcBasicItem *> (pselItem);
        if (pArcNew)
        {
            qrcBndRect = pArcNew->getEllipseRect();
            qrcBndRect = pArcNew->mapRectToScene(qrcBndRect);
            pArcNew->refreshLockRect(qrcBndRect.topLeft(),pScene,bIsLocked);
        }
        break;
/////////////////wxy add end
    default:
        break;
    }
}

void ModelSel::on_HMImodel_2_currentIndexChanged(QString str)
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
