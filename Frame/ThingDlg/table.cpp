#include "table.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
Table::Table(QGraphicsItem *pItem,QWidget *parent) :
        QDialog(parent)
{
    tabWidget = new QTabWidget(this);

    pGeneralDlg = new TableDlg;

    tabWidget->addTab(pGeneralDlg, tr("外观设置"));
    pSecurity = new SecurityWidget(this);
    tabWidget->addTab(pSecurity, tr("权限设置"));
    pSecurity->setGroupVVisible(false);
    pSecurity->setTouchGroupEnabled(false);

    datalist = new QStringList();
    int i = 0;
    for (i=0; i<= 50; i++)
    {
        datalist->append("");
    }

    if(pItem)
    {
        pGeneralDlg->DoubleClickInit(pItem);
        QTableItem* pTable = dynamic_cast<QTableItem *>(pItem);
        if(pTable)
        {
            pSecurity->init(pTable);
        }
    }
    else
    {
        pGeneralDlg->InitParament();
        pSecurity->init(0);
    }

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("确定"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("取消"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("帮助"),QDialogButtonBox::HelpRole);


    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));


    mainLayout=new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    this->setWindowTitle(tr("表格"));

    this->resize(450,500);
}
Table::~Table()
{
    if(pGeneralDlg)
    {
        delete pGeneralDlg;
        pGeneralDlg=NULL;
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
void Table::accept()
{
    if(!pGeneralDlg->SaveGeneralPage(datalist,20))
    {
        return;
    }

    pGeneralDlg->pOldItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_TABLE));
    pGeneralDlg->pOldItem->setData(GROUP_DATALIST_KEY,*datalist);

    if(pSecurity->Save())
    {
        pGeneralDlg->pOldItem->SaveSecurityPro(&(pSecurity->sproperty));
    }
    else
    {
        return;
    }
    QDialog::accept();
}

void Table::loadHelp()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_TABLE);
}
