#include "qdatedisplaydlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QDateDisplayDlg::QDateDisplayDlg(QGraphicsItem *pItem,QWidget *parent) :
        QDialog(parent)
{
    tabWidget = new QTabWidget();
    pDateDisplayGen=new QDateDisplayGeneralDlg();

    tabWidget->addTab(pDateDisplayGen, tr("������ʾ"));

    datalist = new QStringList();
    int i = 0;
    for (i=0; i<200; i++)
    {
        datalist->append("");
    }

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("ȷ��"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("ȡ��"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("����"),QDialogButtonBox::HelpRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(confyButton()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    InitAllProperty(pItem);
    this->setWindowTitle(tr("������ʾ"));
    this->resize(420,500);
}
QDateDisplayDlg::~QDateDisplayDlg()
{
    if(pDateDisplayGen)
    {
        delete pDateDisplayGen;
        pDateDisplayGen = NULL;
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
void QDateDisplayDlg::InitAllProperty(QGraphicsItem *pItem)
{
    if (pItem)//��һ�����е�λ��ť
    {
        *datalist = qVariantValue<QStringList>(pItem->data(GROUP_DATALIST_KEY));
        pDateDisplayGen->Init(pItem);//��ʼ��һ��ҳ��
    }
    else//�½�
    {
        pDateDisplayGen->Init(NULL);//��ʼ��һ��ҳ��
    }

}//
void QDateDisplayDlg::confyButton()
{

    pDateDisplayGen->TimeDisplayGenSave(datalist,40);
    pDateDisplayGen->pCopyItem->setData(GROUP_DATALIST_KEY,*datalist);
    pDateDisplayGen->pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_DATEDISPLAY));
    accept();
}

void QDateDisplayDlg::loadHelp()
{
    pwnd->loadHelpHtm(GROUP_TYPE_DATEDISPLAY);
}
