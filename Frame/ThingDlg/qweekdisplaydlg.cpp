#include "qweekdisplaydlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QWeekDisplayDlg::QWeekDisplayDlg(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget();

    pGeneralDlg = new QWeekDisplayGenDlg;
    pTextDlg = new QWeekDisplaytextDlg;

    tabWidget->addTab(pGeneralDlg, tr("一般"));
    tabWidget->addTab(pTextDlg, tr("文字"));

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("确定"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("取消"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("帮助"),QDialogButtonBox::HelpRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));

    connect(pGeneralDlg, SIGNAL(GeneralStateChange()), this, SLOT(OnGeneralStateChange()));
    connect(pGeneralDlg, SIGNAL(txtChange()),this, SLOT(OnSetTextProperty()));

    connect(pTextDlg, SIGNAL(SetTextProperty()), this, SLOT(OnSetTextProperty()));
    connect(pTextDlg, SIGNAL(ClickCell()), this, SLOT(OnClickTextCell()));

    datalist = new QStringList();
    int i = 0;
    for (i = 0; i <= 250; i++)
    {
          datalist->append("");
    }
    InitAllProperty(pItem);
    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    this->setWindowTitle(tr("星期显示"));

    this->resize(450,520);
}
QWeekDisplayDlg::~QWeekDisplayDlg()
{
    if(pGeneralDlg)
    {
        delete pGeneralDlg;
        pGeneralDlg = NULL;
    }
    if(pTextDlg)
    {
        delete pTextDlg;
        pTextDlg = NULL;
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
void QWeekDisplayDlg::InitAllProperty(QGraphicsItem *pItem)
{
    if(pItem)
    {
        pGeneralDlg->DoubleClickInit(pItem);
        pTextDlg->DoubleClickInit(pItem);
    }
    else
    {
        pGeneralDlg->InitParament();
        pTextDlg->InitParament();
    }
}

void QWeekDisplayDlg::OnSetTextProperty() //接受来自文本页面发出的SetTextProperty信号槽
{
    int nState = pTextDlg->nCurrentIndex;
    int nLang = pTextDlg->ui->m_languagecmb->currentIndex();  //获得多语言下标
    QString sText = "";
    int nVal = 0;

    sText = pTextDlg->TextProperty[nState].sText[nLang];
    pGeneralDlg->pBaseItem->SetPropertyValue("mText.Text",QVariant(sText));       //设置文本

    sText = pTextDlg->TextProperty[nState].sFont[nLang];
    pGeneralDlg->pBaseItem->SetPropertyValue("mText.Font",QVariant(sText));   //设置字体

    nVal = pTextDlg->TextProperty[nState].nFontSize[nLang];
    pGeneralDlg->pBaseItem->SetPropertyValue("mText.FontSize",QVariant(nVal));    //设置字体大小

    nVal = pTextDlg->TextProperty[nState].nWordInterval;
    pGeneralDlg->pBaseItem->SetPropertyValue("mText.WordInterval",QVariant(nVal));//字距

    nVal = pTextDlg->TextProperty[nState].nPosition;
    pGeneralDlg->pBaseItem->SetPropertyValue("mText.Alignment",QVariant(nVal));   //对齐方式

    sText = pTextDlg->TextProperty[nState].sColor;
    pGeneralDlg->pBaseItem->SetPropertyValue("mText.FontColor",QVariant(sText));  //字体颜色
}

void QWeekDisplayDlg::OnClickTextCell() //接收来自文本页面发出的ClickCell信号槽
{
    int nIndex = pTextDlg->nCurrentIndex;         //当前状态值
    pGeneralDlg->ui->m_statespin->setValue(nIndex);
}

void QWeekDisplayDlg::OnGeneralStateChange() //接收来自一般页面发出的GeneralStateChange信号槽
{
    int nState = pGeneralDlg->ui->m_statespin->value(); //获得当前状态值
    QTableWidgetItem *mItem;
    //以下是设置文本页面列表框的选中项
    pTextDlg->nCurrentIndex = nState;
    pTextDlg->OnClickCell();
    pTextDlg->ui->m_table->clearSelection();
    mItem = pTextDlg->ui->m_table->item(nState,0);
    pTextDlg->ui->m_table->setItemSelected(mItem,true);
}

void QWeekDisplayDlg::accept()
{
    int iLan = pwnd->qLanguagecmb->currentIndex();
    if(iLan < 0)
        iLan = 0;
    pTextDlg->ui->m_languagecmb->setCurrentIndex(iLan);  //设置默认是语言1

    pGeneralDlg->SaveWeekGeneralPage(datalist,190);
    pTextDlg->SaveWeekdayTextPage(datalist,20);

    pGeneralDlg->pOldItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_WEEKBTN));
    pGeneralDlg->pOldItem->setData(GROUP_DATALIST_KEY,*datalist);

    QDialog::accept();
}

void QWeekDisplayDlg::loadHelp()
{
    pwnd->loadHelpHtm(GROUP_TYPE_WEEKBTN);
}
