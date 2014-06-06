#include "qhistrenddisplaydlg.h"
#include "view/qdrawgraphics.h"
#include <QGraphicsItemGroup>
extern MainWindow *pwnd;

QHisTrendDisplayDlg::QHisTrendDisplayDlg(QGraphicsItem *pItem,QWidget *parent) :
        QDialog(parent)
{
    tabWidget = new QTabWidget();
    HisTrendDisplayGenDlg=new QHisTrendDisplayGenDlg;
    HisTrendDisplayPenDlg=new QHisTrendDisplayPenDlg;
    HisTrendDisplayXYDlg=new QHisTrendDisplayXYDlg;
    VisibilityDlg=new QVisibilityDlg;


    datalist = new QStringList();
    int i = 0;
    for (i=0; i <= 200; i++)
    {
        datalist->append("");
    }
    InitAllProperty(pItem);
    tabWidget->addTab(HisTrendDisplayGenDlg, tr("һ��"));
    tabWidget->addTab(HisTrendDisplayPenDlg, tr("��"));
    tabWidget->addTab(HisTrendDisplayXYDlg, tr("XY��"));
    tabWidget->addTab(VisibilityDlg, tr("����"));

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("ȷ��"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("ȡ��"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("����"),QDialogButtonBox::HelpRole);

    // buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
    //                                 | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));
    connect(HisTrendDisplayGenDlg, SIGNAL(GenNomberofDataChange()), this, SLOT(ChangePenAmount()));

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    this->setWindowTitle(tr("��ʷ����ͼ"));

    this->resize(750,530);

}
QHisTrendDisplayDlg::~QHisTrendDisplayDlg()
{
    if(HisTrendDisplayGenDlg)
    {
        delete HisTrendDisplayGenDlg;
        HisTrendDisplayGenDlg = NULL;
    }
    if(HisTrendDisplayPenDlg)
    {
        delete HisTrendDisplayPenDlg;
        HisTrendDisplayPenDlg = NULL;
    }
    if(HisTrendDisplayXYDlg)
    {
        delete HisTrendDisplayXYDlg;
        HisTrendDisplayXYDlg = NULL;
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
void QHisTrendDisplayDlg::InitAllProperty(QGraphicsItem *pItem)
{
    if (pItem)
    {
        *datalist = qVariantValue<QStringList>(pItem->data(GROUP_DATALIST_KEY));
        HisTrendDisplayGenDlg->Init(pItem);
        HisTrendDisplayPenDlg->Init(pItem);
        HisTrendDisplayXYDlg->Init(pItem);
        VisibilityDlg->Init(pItem);

    }
    else
    {
        HisTrendDisplayGenDlg->Init(NULL);
        HisTrendDisplayPenDlg->Init(NULL);
        HisTrendDisplayXYDlg->Init(NULL);
        VisibilityDlg->Init(NULL);
        ChangePenAmount();//��ʼ����������
    }

}//
void QHisTrendDisplayDlg::ChangePenAmount()
{
    int nIndex = HisTrendDisplayGenDlg->ui->NumberofCurve->currentIndex();
    HisTrendDisplayPenDlg->SetPenHide(nIndex);
}

void QHisTrendDisplayDlg::accept()
{

    if(!HisTrendDisplayPenDlg->TrendCheckMinMax(3))
    {
        return;//��� ��Сֵ����
    }

    if(!HisTrendDisplayXYDlg->CheckMinMax(3))
    {
        return;//��� ��Сֵ����
    }
    if(HisTrendDisplayGenDlg->ui->m_ifuse->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(HisTrendDisplayGenDlg->checkaddr,tr("����ַ"),HisTrendDisplayGenDlg->ui->m_checkaddredit,1))
        {
            return;
        }
    }
    if(HisTrendDisplayGenDlg->ui->bIfControlAddress->isChecked())//ѡ�����ÿ��Ƶ�ַ
    {
        if(! pwnd->IsAddressCheckRight(HisTrendDisplayGenDlg->kControl_Address_Keyboard,tr("���ƼĴ�����ַ"),HisTrendDisplayGenDlg->ui->kControlRs,1))
        {
            return;
        }
        if(HisTrendDisplayGenDlg->kControl_Address_Keyboard.nConnectType!=0)
        {
            QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr("���Ƶ�ַ����Ϊ�ڲ���ַ��������ѡ��"),
                            0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
            msg.exec();
            HisTrendDisplayGenDlg->ui->kControlRs->setFocus();
            HisTrendDisplayGenDlg->ui->kControlRs->selectAll();
            return;
        }
    }
    HisTrendDisplayGenDlg->SaveGeneralPage(datalist,150);//150-200
    HisTrendDisplayPenDlg->SavePenPage(datalist,100);    //100-149
    HisTrendDisplayXYDlg->SaveXYPage(datalist,20);       //20-99
    if(!VisibilityDlg->visibleSave(datalist,0))         //0-19
    {
        return;
    }
    QDrawGraphics *pDraw = new QDrawGraphics;
    pCopyItem = pDraw->OnDrawTrendChart(3,datalist);  //����ͼ��

    pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_HISTRENDCHART));
    pCopyItem->setData(GROUP_DATALIST_KEY,*datalist);
    if(pDraw)
    {
        delete pDraw;
        pDraw = NULL;
    }
    QDialog::accept();
}

void QHisTrendDisplayDlg::loadHelp()
{
    pwnd->loadHelpHtm(GROUP_TYPE_HISTRENDCHART);
}
