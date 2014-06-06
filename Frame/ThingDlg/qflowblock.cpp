#include "Frame/ThingDlg/qflowblock.h"
#include "ui_qflowblock.h"
#include "Frame/mainwindow.h"
#include "view/flowblockitem.h"
extern MainWindow *pwnd;

qFlowBlock::qFlowBlock(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qFlowBlock)
{
    ui->setupUi(this);
    oId = -1;
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    pScene = new QGraphicsScene(this);     //建场景
    ui->LView->setScene(pScene);           //用视图显示场景
    QGraphicsItem *Item;

    pQFlowBlockGen=new QFlowBlockGenDlg();
    securitywidgets=new SecurityWidget();


    ui->tabWidget->addTab(pQFlowBlockGen, tr("外观设置"));
    ui->tabWidget->addTab(securitywidgets, tr("权限设置"));

    //connect(pQFlowBlockGen, SIGNAL(DrawFlow()),this, SLOT(onDrawFlow()));
    if(pItem)
    {
        connect(pQFlowBlockGen, SIGNAL(DrawFlow()),this, SLOT(onDrawFlow()));
        Item = dynamic_cast<FlowBlockItem *> (pItem)->Clone();
        InitAllProperty(dynamic_cast<FlowBlockItem *> (Item));
        securitywidgets->init(dynamic_cast<FlowBlockItem *> (Item));//权限
        pRectList.clear();
        pScene->clear();
        onDrawFlow();
        oId = dynamic_cast<FlowBlockItem *> (Item)->id();
        ui->spinBox->setValue(oId);
    }
    else
    {
        InitAllProperty(NULL);
        securitywidgets->setTouchDisable(false);
        securitywidgets->init(0);
        pScene->clear();
        onDrawFlow();
        connect(pQFlowBlockGen, SIGNAL(DrawFlow()),this, SLOT(onDrawFlow()));
        ui->spinBox->setValue(pwnd->getNewId());
    }
    this->setWindowTitle(tr("流动块"));
    securitywidgets->setTouchGroupEnabled(false);
}

qFlowBlock::~qFlowBlock()
{
    delete ui;
}

void qFlowBlock::InitAllProperty(FlowBlockItem *pItem)
{
    if (pItem)//打开一个已有的位按钮
    {
        pQFlowBlockGen->Init(pItem);//初始化一般页面
    }
    else//新建
    {
        pQFlowBlockGen->Init(NULL);//初始化一般页面
    }

}
void qFlowBlock::on_accept_clicked()
{
    if(! pwnd->IsAddressCheckRight(pQFlowBlockGen->Monitor_Address_Keyboard,tr("触发地址"),pQFlowBlockGen->ui->Monitor_Address,0))
     {
         return;
     }
    if(pQFlowBlockGen->ui->DynamicFlowSpeed->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(pQFlowBlockGen->Flowspeedkeyboard,tr("流动速度地址"),pQFlowBlockGen->ui->FlowSpeed,1))
        {
            return;
        }
    }
    if(pQFlowBlockGen->ui->m_changdircheck->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(pQFlowBlockGen->TouchAddr,tr("触控地址"),pQFlowBlockGen->ui->m_touchaddredit,0))
        {
            return;
        }
    }
    pQFlowBlockGen->FlowBlockGenSave(m_flow);
    this->pCopyItem->onSaveFlow(m_flow);
    //权限
    if(!securitywidgets->Save())
    {
        return;
    }
    pCopyItem->SaveSecurityPro(&(securitywidgets->sproperty));
    pCopyItem->onSecurityPro(sproperty);
    pCopyItem->setId(ui->spinBox->value());
    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return ;
    }

    accept();
}

void qFlowBlock::on_cancel_clicked()
{
    this->close();
}

void qFlowBlock::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_FLOW);
}
//绘制流动块
void qFlowBlock::onDrawFlow()
{
    if(pQFlowBlockGen->ui->m_Vradio->isChecked()){//if水平
        nDirection = 1;
    }else{
        nDirection = 0;
    }

    nFlowCount = 3;
    int nCount = pQFlowBlockGen->ui->m_countspinBox->value(); //流动块总数
    int i = 0;
    QRectF mRect;
    QRectItem *pSubRect;
    double nWidth = 0.0; //每个块的宽度
    QString sName = "";

    QColor mFlowFrontColor = pQFlowBlockGen->ui->m_flowfrontcolorbtn->palette().background().color();
    QColor mFlowBackColor = pQFlowBlockGen->ui->m_flowbackcolorbtn->palette().background().color();
    QColor mPipeFrontColor = pQFlowBlockGen->ui->m_pipefrontcolorbtn ->palette().background().color();
    QColor mPipebackColor = pQFlowBlockGen->ui->m_pipebackcolorbtn->palette().background().color();
    QColor mFramColor = pQFlowBlockGen->ui->m_framcolorbtn->palette().background().color();

    FlowBlockItem *pGroup = new FlowBlockItem;//new QGraphicsItemGroup;
    nCount = nCount*3;
    nFlowCount = nFlowCount;
    nWidth = 108.0 / nCount;   //每个块的宽度

    if(!pRectList.empty()) //判断是否为空
    {
        for(i = 0; i < nFlowCount; i++)
        {
            pScene->removeItem(pRectList.at(i));
            delete pRectList.at(i);
        }

        pScene->clear();
        pRectList.clear();
    }


    if(nDirection == 0)      //水平方向
    {
        for(i = 0; i < nCount; i++) //画小流动块
        {
            mRect.setTopLeft(QPointF(i*nWidth,50));
            mRect.setSize(QSizeF(nWidth,18));
            pSubRect = new QRectItem(mRect);

          //  pSubRect->SetId(i+1);
            pSubRect->setZValue(i+2);
            pRectList.append(pSubRect);
        }
    }
    else if(nDirection == 1) //垂直方向
    {
        for(i = 0; i < nCount; i++) //画小流动块
        {
            mRect.setTopLeft(QPointF(50,i*nWidth));
            mRect.setSize(QSizeF(18,nWidth));
            pSubRect = new QRectItem(mRect);
          //  pSubRect->SetId(i+1);
            pSubRect->setZValue(i+2);
            pRectList.append(pSubRect);
        }
    }

    for(i = 0; i < nCount; i++)
    {
        pRectList.at(i)->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pRectList.at(i)->setFlag(QGraphicsItem::ItemIsMovable, false);
        if( i % 3 == 2)
        {
            pRectList.at(i)->SetBackColor(mPipebackColor);
            pRectList.at(i)->SetFrontColor(mPipeFrontColor);
        }
        else
        {
            pRectList.at(i)->SetBackColor(mFlowBackColor);
            pRectList.at(i)->SetFrontColor(mFlowFrontColor);
        }

        sName = QString("%1").arg(i); //设置每个块的名称
        sName = "Flow"+sName;
        pRectList.at(i)->SetName(sName);

        pRectList.at(i)->SetLineColor(mFramColor);                      //设置边框色
        pRectList.at(i)->SetPattern(pQFlowBlockGen->ui->m_patterncmb->currentIndex());  //设置样式
        pGroup->addToGroup(pRectList.at(i));  //添加到一个组
    }

    bool nChecks = pQFlowBlockGen->ui->m_noframcheck->checkState();
    int nCounts = pQFlowBlockGen->ui->m_countspinBox->value(); //流动块总数
    int k = 0;
    nCounts = nCounts*3;

    if(nChecks) //没有边线
    {
        for(k = 0; k < nCounts; k++)
        {
            pRectList.at(k)->SetLineType(0);
            pGroup->addToGroup(pRectList.at(k));
        }
    }
    else       //有边线
    {
        for(k = 0; k < nCounts; k++)
        {
            pRectList.at(k)->SetLineType(1);
            pGroup->addToGroup(pRectList.at(k));
        }
    }


    pScene->addItem(pGroup);
    this->pCopyItem = pGroup;
//    pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_FLOWBLOCK));
    nFlowCount = nCount;        //重新赋值
}
