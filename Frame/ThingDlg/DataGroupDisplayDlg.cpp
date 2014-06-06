#include "DataGroupDisplayDlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
#include "view/qdrawgraphics.h"

DataGroupDisplayDlg::DataGroupDisplayDlg(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget();
    TrendChartGenDlg=new DataGroupDisplayGenDlg;
    TrendChartPenDlg=new QTrendChartPenDlg;
    TrendChartXYDlg=new QTrendChartXYDlg;
    VisibilityDlg=new QVisibilityDlg;

    datalist = new QStringList();
    int i = 0;
    for (i=0; i <= 200; i++)
    {
       datalist->append("");
    }

    tabWidget->addTab(TrendChartGenDlg, tr("一般"));
    tabWidget->addTab(TrendChartPenDlg, tr("笔"));
    tabWidget->addTab(TrendChartXYDlg, tr("XY轴"));
    tabWidget->addTab(VisibilityDlg, tr("显现"));

    if(pItem)
    {
        TrendChartGenDlg->DoubleClickInit(pItem);
        TrendChartPenDlg->Init(pItem);
        TrendChartXYDlg->Init(pItem);
        VisibilityDlg->Init(pItem);
    }
    else
    {
        TrendChartGenDlg->InitParament();
        TrendChartPenDlg->Init(NULL);
        TrendChartXYDlg->Init(NULL);
        VisibilityDlg->Init(NULL);
    }
    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("确定"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("取消"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("帮助"),QDialogButtonBox::HelpRole);


    connect(buttonBox, SIGNAL(accepted()), this, SLOT(confyButton()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));
    connect(TrendChartGenDlg, SIGNAL(GenNomberofDataChange()), this, SLOT(ChangePenAmount()));
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    this->setWindowTitle(tr("数据群组显示元件"));

    this->resize(750,600);
}
DataGroupDisplayDlg::~DataGroupDisplayDlg()
{

    if(TrendChartGenDlg)
    {
        delete TrendChartGenDlg;
        TrendChartGenDlg=NULL;
    }
    if(TrendChartPenDlg)
    {
        delete TrendChartPenDlg;
        TrendChartPenDlg=NULL;
    }
    if(TrendChartXYDlg)
    {
        delete TrendChartXYDlg;
        TrendChartXYDlg=NULL;
    }
    if(VisibilityDlg)
    {
        delete VisibilityDlg;
        VisibilityDlg = NULL;
    }
    if(mainLayout)
    {
        delete mainLayout;
        mainLayout=NULL;
    }
    if(buttonBox)
    {
        delete buttonBox;
        buttonBox=NULL;
    }
    if(tabWidget)
    {
        delete tabWidget;
        tabWidget=NULL;
    }
    datalist->clear();
    delete datalist;
}
void DataGroupDisplayDlg::ChangePenAmount()
{
    int nPenCount = TrendChartGenDlg->ui->Number_Data->value();
    TrendChartPenDlg->SetPenHide(nPenCount);
}

void DataGroupDisplayDlg::confyButton()
{
    TrendChartGenDlg->bClickFlag = true;
    if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->kTrigged_address,tr("读取之触发位"),TrendChartGenDlg->ui->Read_Triggre,0))
    {
        return;
    }
    if(TrendChartGenDlg->ui->m_ifuse->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->checkaddr,tr("控制地址"),TrendChartGenDlg->ui->m_checkaddredit,1))
        {
            return;
        }
    }
    for(int i = 0 ; i <TrendChartGenDlg->ui->Number_Data->value();i++ )
    {
        QString str = tr("通道")+QString("%1").arg(i+1)+tr("控制地址");
        if(! pwnd->IsCheckAddressRight(TrendChartGenDlg->kRead_address[i],str,TrendChartGenDlg->ui->Read_Address,1,TrendChartGenDlg->sReadAddr[i]))
        {
            return;
        }
    }
    if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->kClear_Triggre_address,tr("清除之触发位"),TrendChartGenDlg->ui->Clear_Trigged,0))
    {
        return;
    }

    if(!TrendChartPenDlg->TrendCheckMinMax(TrendChartGenDlg->ui->DataType->currentIndex()))
    {
        return;//最大最小值判断有误
    }

    if(!TrendChartXYDlg->checkMaxMin())
    {
        return;//最大最小值判断有误
    }

    TrendChartGenDlg->SaveGeneralPage(datalist,150);//150-200
    TrendChartPenDlg->SavePenPage(datalist,100);    //100-149
    TrendChartXYDlg->SaveXYPage(datalist,20);       //20-99
    if(!VisibilityDlg->visibleSave(datalist,0))         //0-19
    {
        return;
    }

    QDrawGraphics *pDraw = new QDrawGraphics;
    pCopyItem = pDraw->OnDrawTrendChart(4,datalist);  //加载图形

    pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_DATAGROUPDISPLAY));
    pCopyItem->setData(GROUP_DATALIST_KEY,*datalist);

    if(pDraw)
    {
        delete pDraw;
        pDraw=NULL;
    }
    QDialog::accept();
}

void DataGroupDisplayDlg::loadHelp()
{
    pwnd->loadHelpHtm(GROUP_TYPE_DATAGROUPDISPLAY);
}
