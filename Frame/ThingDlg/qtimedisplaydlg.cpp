#include "qtimedisplaydlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QTimeDisplayDlg::QTimeDisplayDlg(QGraphicsItem *pItem,QWidget *parent) :
        QDialog(parent)
{
    tabWidget = new QTabWidget();
    pTimeDisplayGen=new QTimeDisplayGeneralDLg();

    tabWidget->addTab(pTimeDisplayGen , tr("ʱ����ʾ"));
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
    this->setWindowTitle(tr("ʱ����ʾ"));
    InitAllProperty(pItem);
    this->resize(420,500);
}
QTimeDisplayDlg::~QTimeDisplayDlg()
{
    if(pTimeDisplayGen)
    {
        delete pTimeDisplayGen;
        pTimeDisplayGen = NULL;
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
void QTimeDisplayDlg::InitAllProperty(QGraphicsItem *pItem)
{
    if (pItem)//��һ�����е�λ��ť
    {
        *datalist = qVariantValue<QStringList>(pItem->data(GROUP_DATALIST_KEY));
        pTimeDisplayGen->Init(pItem);//��ʼ��һ��ҳ��
    }
    else//�½�
    {
        pTimeDisplayGen->Init(NULL);//��ʼ��һ��ҳ��
    }

}//
void QTimeDisplayDlg::confyButton()
{
    pTimeDisplayGen->TimeDisplayGenSave(datalist,40);
    pTimeDisplayGen->pCopyItem->setData(GROUP_DATALIST_KEY,*datalist);
    pTimeDisplayGen->pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_TIMEDISPLAY));
    accept();
}

void QTimeDisplayDlg::loadHelp()
{
    pwnd->loadHelpHtm(GROUP_TYPE_TIMEDISPLAY);
}
