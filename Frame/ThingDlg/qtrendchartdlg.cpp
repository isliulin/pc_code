#include "qtrendchartdlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
#include "view/qdrawgraphics.h"

QTrendChartDlg::QTrendChartDlg(QGraphicsItem *pItem,QWidget *parent) :
        QDialog(parent)
{
    tabWidget = new QTabWidget();
    TrendChartGenDlg=new QTrendChartGenDlg;
    TrendChartPenDlg=new QTrendChartPenDlg;
    TrendChartXYDlg=new QTrendChartXYDlg;

    VisibilityDlg=new QVisibilityDlg;

    datalist = new QStringList();
    int i = 0;
    for (i=0; i <= 200; i++)
    {
        datalist->append("");
    }

    InitAllProperty(pItem);

    tabWidget->addTab(TrendChartGenDlg, tr("一般"));
    tabWidget->addTab(TrendChartPenDlg, tr("笔"));
    tabWidget->addTab(TrendChartXYDlg, tr("XY轴"));
    tabWidget->addTab(VisibilityDlg, tr("显现"));

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
    this->setWindowTitle(tr("趋势图"));

    this->resize(750,600);
}//
QTrendChartDlg::~QTrendChartDlg()
{
    if(TrendChartGenDlg)
    {
        delete TrendChartGenDlg;
        TrendChartGenDlg = NULL;
    }
    if(TrendChartPenDlg)
    {
        delete TrendChartPenDlg;
        TrendChartPenDlg = NULL;
    }
    if(TrendChartXYDlg)
    {
        delete TrendChartXYDlg;
        TrendChartXYDlg = NULL;
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
void QTrendChartDlg::InitAllProperty(QGraphicsItem *pItem)
{
    if (pItem)
    {              
        *datalist = qVariantValue<QStringList>(pItem->data(GROUP_DATALIST_KEY));
        TrendChartGenDlg->Init(pItem);
        TrendChartPenDlg->Init(pItem);
        TrendChartXYDlg->Init(pItem);
        VisibilityDlg->Init(pItem);
    }
    else
    {
        TrendChartGenDlg->Init(NULL);
        TrendChartPenDlg->Init(NULL);
        TrendChartXYDlg->Init(NULL);
        VisibilityDlg->Init(NULL);
    }   
}//

void QTrendChartDlg::ChangePenAmount()
{
    int nPenCount = TrendChartGenDlg->ui->Number_Data->value();
    TrendChartPenDlg->SetPenHide(nPenCount);
}

void QTrendChartDlg::confyButton()
{
    if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->kTrigged_address,tr("读取之触发位"),TrendChartGenDlg->ui->Read_Triggre,0))
    {
        return;
    }
    if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->kRead_address,tr("读取地址"),TrendChartGenDlg->ui->Read_Address,1))
    {
        return;
    }
    if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->kClear_Triggre_address,tr("清除之触发位"),TrendChartGenDlg->ui->Clear_Trigged,0))
    {
        return;
    }
    if(TrendChartGenDlg->ui->m_ifuse->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->checkaddr,tr("检测地址"),TrendChartGenDlg->ui->m_checkaddredit,1))
        {
            return;
        }
    }
    if(TrendChartGenDlg->ui->If_Use_Control_Add->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->Control_Address_Keyboard,tr("控制地址"),TrendChartGenDlg->ui->Control_Add,1))
        {
            return;
        }
        if(TrendChartGenDlg->Control_Address_Keyboard.nConnectType!=0)
        {
            QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr("控制地址必须为内部地址，请重新选择！"),
                            0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            msg.addButton(tr("确定"),QMessageBox::AcceptRole);
            msg.exec();
            TrendChartGenDlg->ui->Control_Add->setFocus();
            TrendChartGenDlg->ui->Control_Add->selectAll();
            return;
        }
    }

    if(TrendChartGenDlg->ui->If_Per_Data_Variable->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->KPerDataVariableaddr,tr("每组数据点数可变地址"),TrendChartGenDlg->ui->Per_Data_Variable_lineEdit,1))
        {
            return;
        }
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
    pCopyItem = pDraw->OnDrawTrendChart(1,datalist);  //加载图形

    pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_TRENDCHART));
    pCopyItem->setData(GROUP_DATALIST_KEY,*datalist);

    if(pDraw)
    {
        delete pDraw;
        pDraw = NULL;
    }
    QDialog::accept();
}

void QTrendChartDlg::loadHelp()
{
    pwnd->loadHelpHtm(GROUP_TYPE_TRENDCHART);
}
