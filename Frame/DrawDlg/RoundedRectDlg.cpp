#include "RoundedRectDlg.h"
#include "Frame/mainwindow.h"
#include "view/qroundedrectbasic.h"
extern MainWindow *pwnd;
RoundedRectDlg::RoundedRectDlg(QGraphicsItem *item,QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);

    pGeneralDlg = new RoundedRectGenDlg;

    tabWidget->addTab(pGeneralDlg, tr("圆角矩形"));
    if(item)
    {
        if(item->type() == SAM_DRAW_OBJECT_ROUNDEDRECT)
        {
            pSecurity = NULL;
        }
        else
        {
            pSecurity = new SecurityWidget(this);
            tabWidget->addTab(pSecurity, tr("权限设置"));
            pSecurity->setGroupVVisible(false);
            pSecurity->setTouchGroupEnabled(false);
        }
        if(pGeneralDlg)
        {
            pGeneralDlg->setItemType(item->type());
        }
    }
    else
    {
        pSecurity = new SecurityWidget(this);
        tabWidget->addTab(pSecurity, tr("权限设置"));
        pSecurity->setGroupVVisible(false);
        pSecurity->setTouchGroupEnabled(false);
    }

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("确定"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("取消"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("帮助"),QDialogButtonBox::HelpRole);


    if(item)
    {
        pGeneralDlg->DoubleClickInit(item);
        if(item->type() == SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)
        {
            QRoundedRectBasic* pRoundedRect = dynamic_cast<QRoundedRectBasic*>(item);
            if(pRoundedRect && pSecurity)
            {
                pSecurity->init(pRoundedRect->sPro);
            }
        }
    }
    else
    {
        pGeneralDlg->InitParament();
    }
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    this->setWindowTitle(tr("圆角矩形"));
    this->setFixedSize(390,435);
    //this->resize(420,500);
}

void RoundedRectDlg::accept()
{
    pGeneralDlg->pCopyItem->setData(GROUP_TYPE_KEY,QVariant(SAM_DRAW_OBJECT_ROUNDEDRECT));//BASEITEM_TYPE_ROUNDEDRECT
    pGeneralDlg->saveId();
    if(pSecurity)
    {
        if(pSecurity->Save())
        {
            QRoundedRectBasic* pRoundedRect = dynamic_cast<QRoundedRectBasic*>(pGeneralDlg->pCopyItem);
            if(pRoundedRect)
            {
                pRoundedRect->SaveSecurityPro(&(pSecurity->sproperty));
            }
        }
        else
        {
            return;
        }
    }
    QDialog::accept();
}

void RoundedRectDlg::loadHelp()
{
    pwnd->loadHelpHtm(SAM_DRAW_OBJECT_ROUNDEDRECT);
}
