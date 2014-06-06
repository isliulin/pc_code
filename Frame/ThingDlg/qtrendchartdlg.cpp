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

    tabWidget->addTab(TrendChartGenDlg, tr("һ��"));
    tabWidget->addTab(TrendChartPenDlg, tr("��"));
    tabWidget->addTab(TrendChartXYDlg, tr("XY��"));
    tabWidget->addTab(VisibilityDlg, tr("����"));

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
    this->setWindowTitle(tr("����ͼ"));

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
    if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->kTrigged_address,tr("��ȡ֮����λ"),TrendChartGenDlg->ui->Read_Triggre,0))
    {
        return;
    }
    if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->kRead_address,tr("��ȡ��ַ"),TrendChartGenDlg->ui->Read_Address,1))
    {
        return;
    }
    if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->kClear_Triggre_address,tr("���֮����λ"),TrendChartGenDlg->ui->Clear_Trigged,0))
    {
        return;
    }
    if(TrendChartGenDlg->ui->m_ifuse->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->checkaddr,tr("����ַ"),TrendChartGenDlg->ui->m_checkaddredit,1))
        {
            return;
        }
    }
    if(TrendChartGenDlg->ui->If_Use_Control_Add->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->Control_Address_Keyboard,tr("���Ƶ�ַ"),TrendChartGenDlg->ui->Control_Add,1))
        {
            return;
        }
        if(TrendChartGenDlg->Control_Address_Keyboard.nConnectType!=0)
        {
            QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr("���Ƶ�ַ����Ϊ�ڲ���ַ��������ѡ��"),
                            0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
            msg.exec();
            TrendChartGenDlg->ui->Control_Add->setFocus();
            TrendChartGenDlg->ui->Control_Add->selectAll();
            return;
        }
    }

    if(TrendChartGenDlg->ui->If_Per_Data_Variable->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(TrendChartGenDlg->KPerDataVariableaddr,tr("ÿ�����ݵ����ɱ��ַ"),TrendChartGenDlg->ui->Per_Data_Variable_lineEdit,1))
        {
            return;
        }
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
    pCopyItem = pDraw->OnDrawTrendChart(1,datalist);  //����ͼ��

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
