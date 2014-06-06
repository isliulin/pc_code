#include "ArcDlg.h"
#include "Frame/mainwindow.h"
#include "view/qarcbasicitem.h"
extern MainWindow *pwnd;

ArcDlg::ArcDlg(QGraphicsItem *item,QWidget *parent) :
    QDialog(parent)
{
    tabWidget = new QTabWidget(this);

    oId = -1;
    pGeneralDlg = new ArcGenDlg;


    tabWidget->addTab(pGeneralDlg, tr("扇形"));
    if(item)
    {
        if(item->type() == SAM_DRAW_OBJECT_ARC)
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
        SamDrawItemBase *baseitem = dynamic_cast<SamDrawItemBase *> (item);
        if(baseitem)
        {
            oId = baseitem->id();
        }

        pGeneralDlg->DoubleClickInit(item);
        if(item->type() == SAM_DRAW_OBJECT_ARC_NEW)
        {
            QArcBasicItem* pArc = dynamic_cast<QArcBasicItem*>(item);
            if(pArc && pSecurity)
            {
                pSecurity->init(pArc->sPro);
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

    this->setWindowTitle(tr("扇形"));

    this->setFixedSize(380,370);
    //this->resize(420,500);
}

void ArcDlg::accept()
{
    pGeneralDlg->pCopyItem->setData(GROUP_TYPE_KEY,QVariant(SAM_DRAW_OBJECT_ARC));//BASEITEM_TYPE_ARC
    pGeneralDlg->saveId();
    if(pSecurity)
    {
        if(pSecurity->Save())
        {
            QArcBasicItem* pArc = dynamic_cast<QArcBasicItem*>(pGeneralDlg->pCopyItem);
            if(pArc)
            {
                pArc->SaveSecurityPro(&(pSecurity->sproperty));
            }
        }
        else
        {
            return;
        }
    }
    if(pGeneralDlg->getId() != oId && !pwnd->insertId(pGeneralDlg->getId()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return ;
    }

    QDialog::accept();
}

void ArcDlg::loadHelp()
{
    pwnd->loadHelpHtm(SAM_DRAW_OBJECT_ARC);
}
