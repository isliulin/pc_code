#include "qtimedisplaydlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QTimeDisplayDlg::QTimeDisplayDlg(QGraphicsItem *pItem,QWidget *parent) :
        QDialog(parent)
{
    tabWidget = new QTabWidget();
    pTimeDisplayGen=new QTimeDisplayGeneralDLg();

    tabWidget->addTab(pTimeDisplayGen , tr("时间显示"));
    datalist = new QStringList();
    int i = 0;
    for (i=0; i<200; i++)
    {
        datalist->append("");
    }

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("确定"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("取消"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("帮助"),QDialogButtonBox::HelpRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(confyButton()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    this->setWindowTitle(tr("时间显示"));
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
    if (pItem)//打开一个已有的位按钮
    {
        *datalist = qVariantValue<QStringList>(pItem->data(GROUP_DATALIST_KEY));
        pTimeDisplayGen->Init(pItem);//初始化一般页面
    }
    else//新建
    {
        pTimeDisplayGen->Init(NULL);//初始化一般页面
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
