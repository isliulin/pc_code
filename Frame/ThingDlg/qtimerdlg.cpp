#include "qtimerdlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QTimerDlg::QTimerDlg(QGraphicsItem *pItem,QWidget *parent) :
        QDialog(parent)
{
    tabWidget = new QTabWidget();

    pGeneralDlg = new QTimerGenDlg;
    tabWidget->addTab(pGeneralDlg,tr("定时器"));

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("确定"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("取消"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("帮助"),QDialogButtonBox::HelpRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
   connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));

    datalist = new QStringList();
    int i = 0;
    for (i=0; i < 20; i++)
    {
        datalist->append("");
    }
    if(pItem)
    {
        pGeneralDlg->DoubleClickInit(pItem);
    }
    else
    {
        pGeneralDlg->InitParament();
    }

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    this->setWindowTitle(tr("定时器"));

    this->resize(470,600);
}
QTimerDlg::~QTimerDlg()
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
void QTimerDlg::accept()
{
    if(pGeneralDlg->ui->comboBox->currentIndex() == 1)
    {
        if(! pwnd->IsAddressCheckRight(pGeneralDlg->BitAddr,tr("触发地址"),pGeneralDlg->ui->m_addredit,0))
        {
            return;
        }
    }

    if(pGeneralDlg->ui->m_namecmb->currentText() == "")
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("没有选择功能名称!"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }

    datalist->clear();
    for (int i = 0; i < 20; i++)
    {
        datalist->append("");
    }
    pGeneralDlg->GeneralSave(datalist);
    if( !pGeneralDlg->pCopyItem )
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("缺少shape.sk文件!"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }
    pGeneralDlg->pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_TIMER));
    pGeneralDlg->pCopyItem->setData(GROUP_DATALIST_KEY,*datalist);
    QDialog::accept();
}

void QTimerDlg::loadHelp()
{
    pwnd->loadHelpHtm(GROUP_TYPE_TIMER);
}
