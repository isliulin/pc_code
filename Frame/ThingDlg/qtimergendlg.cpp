#include "qtimergendlg.h"


#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QTimerGenDlg::QTimerGenDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QTimerGenDlg)
{
    ui->setupUi(this);
    pCopyItem = NULL;
    pScene = new QGraphicsScene(this);     //建场景
    ui->MainView->setScene(pScene);
    sMarcoName.clear();
}

QTimerGenDlg::~QTimerGenDlg()
{
    if(pScene)
    {
        delete pScene;
        pScene=NULL;
    }
     delete ui;
}

void QTimerGenDlg::LoadTimerShape()
{
    QFile file("shape.sk");
    if(!file.open(QIODevice::ReadOnly))
        return ;
    QDataStream openData(&file);
    SamDrawScene *pSvene = NULL;
    QVector <SamDrawScene *> vScene;  //存画面的容器
    vScene.clear();
    int sceneSize = 0;
    openData >> sceneSize;
    int i = 0;
    for(i =0; i< sceneSize; i++)
    {
        pSvene = new SamDrawScene();
        openData >> pSvene;
        vScene.push_back(pSvene);
    }
    file.close();

    QPainterPath path;
    //扫描基本图库
    path.addRect(0,0,vScene.at(3)->width(),vScene.at(3)->height());
    vScene.at(3)->setSelectionArea(path);
    QList<QGraphicsItem *> item_list=vScene.at(3)->selectedItems();
    DrawItemToScene GroupFunction;
    GroupFunction.CopyItem(&pCopyItem,item_list.at(0));
    pScene->clear();
    pScene->addItem(pCopyItem);
    for(i =0; i< sceneSize; i++)
        delete vScene[i];
    vScene.clear();
}

void QTimerGenDlg::InitParament()
{
    ui->m_Noedit->setText(pwnd->GetControlNO("T"));//编号
    on_comboBox_currentIndexChanged(0);//初始化始终执行
    on_comboBox_2_currentIndexChanged(0);//初始化执行宏指令
    ui->m_numcountedit->setValue(0);//执行次数
    LoadTimerShape(); //加载图形
}

void QTimerGenDlg::on_comboBox_currentIndexChanged(int index)//控制方式
{
    if(index == 0) //始终执行
    {
        ui->m_addrlable->setVisible(false);
        ui->m_addredit->setVisible(false);
        ui->m_addrbtn->setVisible(false);
        ui->label_warning->setText(tr("注意：若执行次数为0，则表示宏指令\n一直执行"));
    }
    else if(index == 1)//地址触发
    {
        ui->m_addrlable->setVisible(true);
        ui->m_addredit->setVisible(true);
        ui->m_addrbtn->setVisible(true);
        ui->label_warning->setText(tr("注意：若执行次数为0且满足触发条件，\n则表示宏指令一直执行"));
    }
}

void QTimerGenDlg::on_m_addrbtn_clicked()//触发地址
{
    pwnd->Addr_Type=0;
    AddressInputDialog  dlg_triggered(BitAddr,this);
    dlg_triggered.exec();
    ui->m_addredit->setText(BitAddr.sShowAddr);
}

void QTimerGenDlg::on_comboBox_2_currentIndexChanged(int index)//功能类型
{
    ui->m_namecmb->clear();
    switch(index)
    {
    case 0://执行宏指令
        if(!sMarcoName.isEmpty())
           ui->m_namecmb->addItems(sMarcoName);
        break;
    default:
        break;
    }
}

void QTimerGenDlg::GeneralSave(QStringList *datalist)
{
    QString sTmp;
    int nTmp = 0;

    datalist->replace(19,ui->m_Noedit->text()); //编号

    nTmp = ui->comboBox->currentIndex();//控制方式
    sTmp = QString::number(nTmp);
    datalist->append(sTmp);// 20

    sTmp=pwnd->KeyboardToString(BitAddr);//触发地址
    datalist->append(sTmp);// 21

    nTmp = ui->spinBox->value();//执行频率
    sTmp = QString::number(nTmp);
    datalist->append(sTmp);// 22

    nTmp = ui->m_numcountedit->value(); //执行次数
    sTmp = QString::number(nTmp);
    datalist->append(sTmp);// 23

    nTmp = ui->comboBox_2->currentIndex();//功能类型
    sTmp = QString::number(nTmp);
    datalist->append(sTmp);// 24

    sTmp = ui->m_namecmb->currentText(); //工程名称
    datalist->append(sTmp);// 25
}

void QTimerGenDlg::DoubleClickInit(QGraphicsItem *pItem)
{
    DrawItemToScene GroupFunction;
    QStringList pdataList;
    int val = 20;
    QString sTmp = "";
    if(pItem)   //从Data 的 stringList中获取属性并设置
    {
        GroupFunction.CopyItem(&pCopyItem,pItem);
        pdataList = pCopyItem->data(GROUP_DATALIST_KEY).toStringList();

        pScene->addItem(pCopyItem);

        sTmp = pdataList.at(19);//编号
        ui->m_Noedit->setText(sTmp);

        sTmp = pdataList.at(val);//控制方式
        ui->comboBox->setCurrentIndex(sTmp.toInt());
        on_comboBox_currentIndexChanged(sTmp.toInt());

        sTmp = pdataList.at(val+1);//触发地址
        pwnd->StringToKeyboard(BitAddr,sTmp);
        ui->m_addredit->setText(BitAddr.sShowAddr);

        sTmp = pdataList.at(val+2);//执行频率
        ui->spinBox->setValue(sTmp.toInt());

        sTmp = pdataList.at(val+3);//执行次数
        ui->m_numcountedit->setValue(sTmp.toInt());

        sTmp = pdataList.at(val+4);//功能类型
        ui->comboBox_2->setCurrentIndex(sTmp.toInt());
        on_comboBox_2_currentIndexChanged(sTmp.toInt());

        sTmp = pdataList.at(val+5);//功能名称
        int nIndex = ui->m_namecmb->findText(sTmp);
        ui->m_namecmb->setCurrentIndex(nIndex);
    }
}
