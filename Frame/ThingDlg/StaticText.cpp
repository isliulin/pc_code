#include "StaticText.h"
#include "view/qsimpletextitem.h"
#include "view/switchitem.h"
#include "Frame\MainWindow.h"
extern MainWindow *pwnd;

StaticText::StaticText(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent)
{
    QGraphicsItem *Item;

    tabWidget = new QTabWidget(this);

    pGeneralDlg = new StaticTextDlg ;
    securitywidget = new SecurityWidget;

    tabWidget->addTab(pGeneralDlg, tr("外观设置"));
    tabWidget->addTab(securitywidget, tr("权限设置"));
    if(pItem)
    {
        //pGeneralDlg->OnDoubleClickInit(pItem);
        //pVisibleDlg->Init(pItem);
        Item = dynamic_cast<StaticTextItem *> (pItem)->Clone();
        pGeneralDlg->OnDoubleClickInit(dynamic_cast<StaticTextItem *> (Item));//外观

        securitywidget->init(dynamic_cast<StaticTextItem *> (Item));//权限
    }
    else
    {
        pGeneralDlg->InitParament();
        securitywidget->init(0);
    }

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("确定"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("取消"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("帮助"),QDialogButtonBox::HelpRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));


    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    this->setWindowTitle(tr("静态文本"));
    this->setFixedSize(625,510);
    securitywidget->setTouchGroupEnabled(false);
}
StaticText::~StaticText()
{
    if(pGeneralDlg)
    {
        delete pGeneralDlg;
        pGeneralDlg = NULL;
    }
    if(securitywidget)
    {
        delete securitywidget;
        securitywidget = NULL;
    }
    if(buttonBox)
    {
        delete buttonBox;
        buttonBox=NULL;
    } if(mainLayout)
    {
        delete mainLayout;
        mainLayout=NULL;
    }
    if(tabWidget)
    {
        delete tabWidget;
        tabWidget = NULL;
    }
//    datalist->clear();
//    delete datalist;
}
void StaticText::accept()
{

    int iLan = pGeneralDlg->ui->m_languagecmb->currentIndex();
    if(iLan < 0)
        iLan = 0;
    QSimpleTextItem *pTxt = new QSimpleTextItem;//();
    pTxt->SetText(pGeneralDlg->TxtProperty[iLan].sText);
    pTxt->SetFontSize(pGeneralDlg->TxtProperty[iLan].nFontSize);
    pTxt->SetFontName(pGeneralDlg->TxtProperty[iLan].sFont);
    pTxt->SetFitSize(pGeneralDlg->TxtProperty[iLan].adapt);

    pTxt->SetFontColor(pwnd->StringTOColor(pGeneralDlg->TxtProperty[iLan].nFontColor));
    pTxt->SetFontBold(pGeneralDlg->ui->IfBold->isChecked());
    pTxt->SetFontItalic(pGeneralDlg->ui->IfItalic->isChecked());
    pTxt->SetFontWordInterval(pGeneralDlg->ui->WordInterval->value());
    pTxt->SetFontUnderLine(pGeneralDlg->ui->m_underlinecheck->isChecked());

    int align=pGeneralDlg->ui->combo_Alignment->currentIndex();
    if(align==0){
        pTxt->SetTextAlign(5);
    }else if(align==1){
        pTxt->SetTextAlign(4);
    }else if(align==2){
        pTxt->SetTextAlign(6);
    }
    pTxt->SetRectOutLine(false);
    pTxt->SetName("mText");

    pTxt->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTxt->setZValue(2);

    QRectF rect(QPointF(0,0), QSize(100,100));     //绘制边框色矩形框
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(QColor(224,224,224));
    pFramRect->SetLineType(0);
    pFramRect->SetPattern(0);
    pFramRect->setZValue(1);
    pFramRect->SetName("mFramRect");
    pFramRect->SetFrontColor(pGeneralDlg->ui->FrontColor->palette().background().color());
    pFramRect->SetBackColor(pGeneralDlg->ui->BackColor->palette().background().color());
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetAlpha(pGeneralDlg->ui->Alpha->value());
    pFramRect->SetPattern(pGeneralDlg->ui->Pattern->currentIndex());

    pCopyItem = new StaticTextItem;
    pCopyItem->addToGroup(pTxt);
    pCopyItem->addToGroup(pFramRect);

    //权限
    if(!securitywidget->Save())
    {
        return;
    }
    pCopyItem->SaveSecurityPro(&(securitywidget->sproperty));
    //外观
    pGeneralDlg->SaveText(textInfo);
    //pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_STATICTEXT));

    pCopyItem->onSaveText(textInfo);
    pCopyItem->onSecurityPro(sproperty);
    QDialog::accept();
}

void StaticText::loadHelp()
{
    pwnd->loadHelpHtm(SAM_DRAW_OBJECT_TEXT);
}
