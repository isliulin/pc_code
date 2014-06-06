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
    tabWidget->addTab(pRecipeChoiceGen, tr("一般"));
    tabWidget->addTab(Advancedlg, tr("高级"));
    tabWidget->addTab(visibilitydlg, tr("显现"));

    datalist = new QStringList();
    int i = 0;
    for (i=0; i < 150; i++)
    {
            datalist->append("");
    }

    pCopyItem = NULL;

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
    this->setWindowTitle(tr("配方选择器"));

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
    pCopyItem = pDraw->drawRecipeSelect(datalist);  //加载图形
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
    if (pItem)//打开一个已有的位按钮
    {
        *datalist = qVariantValue<QStringList>(pItem->data(GROUP_DATALIST_KEY));
        pRecipeChoiceGen->Init(pItem);//初始化一般页面
        Advancedlg->Init(pItem);//初始化标示页面
        visibilitydlg->Init(pItem);//初始化图片页面
    }
    else//新建
    {
        pRecipeChoiceGen->Init(NULL);//初始化一般页面
        Advancedlg->Init(NULL);//初始化标示页面
        visibilitydlg->Init(NULL);//初始化图片页面
    }
}
