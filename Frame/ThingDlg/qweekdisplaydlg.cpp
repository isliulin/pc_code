#include "qweekdisplaydlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QWeekDisplayDlg::QWeekDisplayDlg(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget();

    pGeneralDlg = new QWeekDisplayGenDlg;
    pTextDlg = new QWeekDisplaytextDlg;

    tabWidget->addTab(pGeneralDlg, tr("һ��"));
    tabWidget->addTab(pTextDlg, tr("����"));

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("ȷ��"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("ȡ��"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("����"),QDialogButtonBox::HelpRole);

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
    this->setWindowTitle(tr("������ʾ"));

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

void QWeekDisplayDlg::OnSetTextProperty() //���������ı�ҳ�淢����SetTextProperty�źŲ�
{
    int nState = pTextDlg->nCurrentIndex;
    int nLang = pTextDlg->ui->m_languagecmb->currentIndex();  //��ö������±�
    QString sText = "";
    int nVal = 0;

    sText = pTextDlg->TextProperty[nState].sText[nLang];
    pGeneralDlg->pBaseItem->SetPropertyValue("mText.Text",QVariant(sText));       //�����ı�

    sText = pTextDlg->TextProperty[nState].sFont[nLang];
    pGeneralDlg->pBaseItem->SetPropertyValue("mText.Font",QVariant(sText));   //��������

    nVal = pTextDlg->TextProperty[nState].nFontSize[nLang];
    pGeneralDlg->pBaseItem->SetPropertyValue("mText.FontSize",QVariant(nVal));    //���������С

    nVal = pTextDlg->TextProperty[nState].nWordInterval;
    pGeneralDlg->pBaseItem->SetPropertyValue("mText.WordInterval",QVariant(nVal));//�־�

    nVal = pTextDlg->TextProperty[nState].nPosition;
    pGeneralDlg->pBaseItem->SetPropertyValue("mText.Alignment",QVariant(nVal));   //���뷽ʽ

    sText = pTextDlg->TextProperty[nState].sColor;
    pGeneralDlg->pBaseItem->SetPropertyValue("mText.FontColor",QVariant(sText));  //������ɫ
}

void QWeekDisplayDlg::OnClickTextCell() //���������ı�ҳ�淢����ClickCell�źŲ�
{
    int nIndex = pTextDlg->nCurrentIndex;         //��ǰ״ֵ̬
    pGeneralDlg->ui->m_statespin->setValue(nIndex);
}

void QWeekDisplayDlg::OnGeneralStateChange() //��������һ��ҳ�淢����GeneralStateChange�źŲ�
{
    int nState = pGeneralDlg->ui->m_statespin->value(); //��õ�ǰ״ֵ̬
    QTableWidgetItem *mItem;
    //�����������ı�ҳ���б���ѡ����
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
    pTextDlg->ui->m_languagecmb->setCurrentIndex(iLan);  //����Ĭ��������1

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
