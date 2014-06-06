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

    tabWidget->addTab(TrendChartGenDlg, tr("һ��"));
    tabWidget->addTab(TrendChartPenDlg, tr("��"));
    tabWidget->addTab(TrendChartXYDlg, tr("XY��"));
    tabWidget->addTab(VisibilityDlg, tr("����"));

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
    buttonBox->addButton(tr("ȷ��"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("ȡ��"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("����"),QDialogButtonBox::HelpRole);


    connect(buttonBox, SIGNAL(accepted()), this, SLOT(confyButton()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));
    connect(TrendChartGenDlg, SIGNAL(GenNomberofDataChange()), this, SLOT(ChangePenAmount()));
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    this->setWindowTitle(tr("����Ⱥ����ʾԪ��"));

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
    if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->kTrigged_address,tr("��ȡ֮����λ"),TrendChartGenDlg->ui->Read_Triggre,0))
    {
        return;
    }
    if(TrendChartGenDlg->ui->m_ifuse->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->checkaddr,tr("���Ƶ�ַ"),TrendChartGenDlg->ui->m_checkaddredit,1))
        {
            return;
        }
    }
    for(int i = 0 ; i <TrendChartGenDlg->ui->Number_Data->value();i++ )
    {
        QString str = tr("ͨ��")+QString("%1").arg(i+1)+tr("���Ƶ�ַ");
        if(! pwnd->IsCheckAddressRight(TrendChartGenDlg->kRead_address[i],str,TrendChartGenDlg->ui->Read_Address,1,TrendChartGenDlg->sReadAddr[i]))
        {
            return;
        }
    }
    if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->kClear_Triggre_address,tr("���֮����λ"),TrendChartGenDlg->ui->Clear_Trigged,0))
    {
        return;
    }

    if(!TrendChartPenDlg->TrendCheckMinMax(TrendChartGenDlg->ui->DataType->currentIndex()))
    {
        return;//�����Сֵ�ж�����
    }

    if(!TrendChartXYDlg->checkMaxMin())
    {
        return;//�����Сֵ�ж�����
    }

    TrendChartGenDlg->SaveGeneralPage(datalist,150);//150-200
    TrendChartPenDlg->SavePenPage(datalist,100);    //100-149
    TrendChartXYDlg->SaveXYPage(datalist,20);       //20-99
    if(!VisibilityDlg->visibleSave(datalist,0))         //0-19
    {
        return;
    }

    QDrawGraphics *pDraw = new QDrawGraphics;
    pCopyItem = pDraw->OnDrawTrendChart(4,datalist);  //����ͼ��

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
