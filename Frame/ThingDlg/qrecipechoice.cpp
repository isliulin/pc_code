#include "qrecipechoice.h"
#include "view/qdrawgraphics.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QRecipeChoice::QRecipeChoice(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);
    pRecipeChoiceGen=new QRecipeChoiceGenDlg(this);
    Advancedlg = new QAdvancedDlg(this);
    visibilitydlg = new QVisibilityDlg(this);
    tabWidget->addTab(pRecipeChoiceGen, tr("һ��"));
    tabWidget->addTab(Advancedlg, tr("�߼�"));
    tabWidget->addTab(visibilitydlg, tr("����"));

    datalist = new QStringList();
    int i = 0;
    for (i=0; i < 150; i++)
    {
            datalist->append("");
    }

    pCopyItem = NULL;

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
    this->setWindowTitle(tr("�䷽ѡ����"));

    this->resize(450,500);
    InitAllProperty(pItem);

}
QRecipeChoice::~QRecipeChoice()
{
    if(pRecipeChoiceGen)
    {
        delete pRecipeChoiceGen;
        pRecipeChoiceGen = NULL;
    }
    if(Advancedlg)
    {
        delete Advancedlg;
        Advancedlg = NULL;
    }
    if(visibilitydlg)
    {
        delete visibilitydlg;
        visibilitydlg = NULL;
    }
  }
void QRecipeChoice::confyButton()
{
    pRecipeChoiceGen->GeneralSave(datalist,40);
    if(!Advancedlg->advancedSave(datalist,20))
    {
        return;
    }
    if(!visibilitydlg->visibleSave(datalist,0))
    {
        return;
    }

    QDrawGraphics *pDraw = new QDrawGraphics;
    pCopyItem = pDraw->drawRecipeSelect(datalist);  //����ͼ��
    pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_RECIPE_CHOICE));
    pCopyItem->setData(GROUP_DATALIST_KEY,*datalist);

    if(pDraw)
    {
        delete pDraw;
        pDraw = NULL;
    }

    accept();
}
void QRecipeChoice::loadHelp()
{
    pwnd->loadHelpHtm(GROUP_TYPE_RECIPE_CHOICE);
}

void QRecipeChoice::InitAllProperty(QGraphicsItem *pItem)
{
    if (pItem)//��һ�����е�λ��ť
    {
        *datalist = qVariantValue<QStringList>(pItem->data(GROUP_DATALIST_KEY));
        pRecipeChoiceGen->Init(pItem);//��ʼ��һ��ҳ��
        Advancedlg->Init(pItem);//��ʼ����ʾҳ��
        visibilitydlg->Init(pItem);//��ʼ��ͼƬҳ��
    }
    else//�½�
    {
        pRecipeChoiceGen->Init(NULL);//��ʼ��һ��ҳ��
        Advancedlg->Init(NULL);//��ʼ����ʾҳ��
        visibilitydlg->Init(NULL);//��ʼ��ͼƬҳ��
    }
}
