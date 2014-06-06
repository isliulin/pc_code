#include "qmessageshow.h"
#include "ui_qmessageshow.h"
#include "Frame/mainwindow.h"
#include "view/qgroupitem.h"

extern MainWindow *pwnd;

qMessageShow::qMessageShow(QMessageShowAttr* pItem, QWidget *parent):QDialog(parent),ui(new Ui::qMessageShow)
{
    ui->setupUi(this);

    oId = -1;
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    this->m_pCopyItem = NULL;

    page1 = new qMessageShowOne;

    ui->tabWidget->addTab(page1, tr("一般"));

    pSecurityWight = new SecurityWidget(this);
    ui->tabWidget->addTab(pSecurityWight, tr("权限设置"));
    //pSecurityWight->ui->groupBox_Touch->hide();
    pSecurityWight->setTouchGroupEnabled(false);

    this->setWindowTitle(tr("消息显示器"));

    pScene = new QGraphicsScene(this); //建场景
    ui->graphicsView->setScene(pScene);//贴图区域

    connect(page1, SIGNAL(changeCondition()), this, SLOT(redraw()));

    InitPropertys(pItem);
}

qMessageShow::~qMessageShow()
{
    if(page1)
    {
        delete page1;
        page1 = NULL;
    }
    if(m_pCopyItem)
    {
        delete m_pCopyItem;
        m_pCopyItem = NULL;
    }
    if(pScene)
    {
        delete pScene;
        pScene=NULL;
    }
    if(pBaseItem)
    {
        delete pBaseItem;
        pBaseItem=NULL;
    }
    /*if(pCopyBaseItem)
    {
        delete pCopyBaseItem;
        pCopyBaseItem=NULL;
    }*/
    if(pSecurityWight)
    {
        delete pSecurityWight;
        pSecurityWight = NULL;
    }
    //delete itemTemp;
    delete ui;
}

void qMessageShow::on_accept_clicked()
{
    if(!pwnd->IsAddressCheckRight(page1->m_keyAddress,tr("监视地址"),page1->ui->lineEdit_addr,1))
    {
        page1->ui->lineEdit_addr->setFocus();
        return ;
    }

    m_pCopyItem = new QMessageShowAttr;

    if(pSecurityWight && pSecurityWight->Save())
    {
        m_pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    }
    else
    {
        return;
    }

    m_pCopyItem->curSta             = page1->curSta;
    m_pCopyItem->m_sShape           = page1->m_sShape;
    m_pCopyItem->m_bDataType        = page1->m_bDataType;
    m_pCopyItem->m_keyAddress       = page1->m_keyAddress;
    m_pCopyItem->m_nStateCount      = page1->m_nStateCount;

    m_pCopyItem->m_bFirstLanguage   = page1->m_bFirstLanguage;
    m_pCopyItem->m_bStateZero       = page1->m_bStateZero;
    m_pCopyItem->m_eRemove          = page1->m_eRemove;
    m_pCopyItem->m_nSpeed           = page1->m_nSpeed;
    m_pCopyItem->m_nAlpha           = page1->m_nAlpha;

    MsgProp msg;
    LanDiff lan;
    for(int i = 0; i < page1->m_nStateCount; i++)
    {
        //page1
        msg.m_nFrameColor   = page1->m_vecMsg[i].m_nFrameColor;
        msg.m_nForecolor    = page1->m_vecMsg[i].m_nForecolor;
        msg.m_nBackcolor    = page1->m_vecMsg[i].m_nBackcolor;
        msg.m_nStyle        = page1->m_vecMsg[i].m_nStyle;

        //page2
        int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
        for(int j = 0; j < lanNum; j++)
        {
            lan.m_nStatusIndex  = page1->m_vecMsg[i].m_nVecPage2[j].m_nStatusIndex;
            lan.m_sStateMessage = page1->m_vecMsg[i].m_nVecPage2[j].m_sStateMessage;
            lan.m_nLanguage     = page1->m_vecMsg[i].m_nVecPage2[j].m_nLanguage;
            lan.m_sFontType     = page1->m_vecMsg[i].m_nVecPage2[j].m_sFontType;
            lan.m_nFontSize     = page1->m_vecMsg[i].m_nVecPage2[j].m_nFontSize;
            lan.m_nFontColor    = page1->m_vecMsg[i].m_nVecPage2[j].m_nFontColor;

            msg.m_nVecPage2.push_back(lan);
        }

        m_pCopyItem->m_vecMsg.push_back(msg);
        msg.m_nVecPage2.clear();
    }

    QDrawGraphics *pDraw = new QDrawGraphics;     //由基类生成一个对象
    listItem = pDraw->OnDrawRectAndText();
    int num = listItem.size();
    for(int i = 0; i < num; i++)
    {
        m_pCopyItem->addToGroup(listItem.at(i));
    }

    pCopyBaseItem = new QGroupItem(m_pCopyItem);
    int curSta = page1->curSta;//0;m_curLan
    int curLan = page1->m_curLan;//pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan;
    pCopyBaseItem->SetPropertyValue("mText.Text",QVariant(page1->m_vecMsg[curSta].m_nVecPage2[curLan].m_sStateMessage));
    pCopyBaseItem->SetPropertyValue("mText.Font",QVariant(page1->m_vecMsg[curSta].m_nVecPage2[curLan].m_sFontType));
    pCopyBaseItem->SetPropertyValue("mText.FontSize",QVariant(page1->m_vecMsg[curSta].m_nVecPage2[curLan].m_nFontSize));
    QString str = pwnd->ColorTOString(page1->m_vecMsg[curSta].m_nVecPage2[curLan].m_nFontColor);
    pCopyBaseItem->SetPropertyValue("mText.FontColor",QVariant(str));
    pCopyBaseItem->SetPropertyValue("mBackRect.Pattern",QVariant(page1->m_vecMsg[curSta].m_nStyle));
    if(page1->m_vecMsg[curSta].m_nStyle == 0)
    {
        pCopyBaseItem->SetPropertyValue("mFramRect.Pattern",QVariant(page1->m_vecMsg[curSta].m_nStyle));
    }

    str = pwnd->ColorTOString(page1->m_vecMsg[curSta].m_nFrameColor);
    pCopyBaseItem->SetPropertyValue("mFramRect.BackColor",QVariant(str));
    str = pwnd->ColorTOString(page1->m_vecMsg[curSta].m_nForecolor);
    pCopyBaseItem->SetPropertyValue("mBackRect.FrontColor",QVariant(str));
    str = pwnd->ColorTOString(page1->m_vecMsg[curSta].m_nBackcolor);
    pCopyBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(str));
    pCopyBaseItem->SetPropertyValue("mFramRect.Alpha", QVariant(page1->m_nAlpha));
    pCopyBaseItem->SetPropertyValue("mBackRect.Alpha", QVariant(page1->m_nAlpha));


    m_pCopyItem->setId(ui->spinBox->value());
    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return ;
    }

    if(pDraw)
    {
        delete pDraw;
        pDraw = NULL;
    }

    QDialog::accept();
}

void qMessageShow::on_cancel_clicked()
{
    this->close();
}

void qMessageShow::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_MESSAGE);
}

void qMessageShow::InitPropertys(QMessageShowAttr* pItem)
{
    if(pItem)
    {
        page1->Init(pItem);
        pSecurityWight->init(pItem);
        oId = pItem->id();
        ui->spinBox->setValue(oId);
    }
    else
    {
        page1->Init(NULL);
        pSecurityWight->init(NULL);
        ui->spinBox->setValue(pwnd->getNewId());
    }

    QDrawGraphics *pDraw = new QDrawGraphics;     //由基类生成一个对象
    pOldItem = pDraw->OnDrawRectAndText(pScene);  //加载图形
    pBaseItem = new QGroupItem(pOldItem);

    int curSta = page1->curSta;
    int curLan = page1->m_curLan;
    pBaseItem->SetPropertyValue("mText.Text",QVariant(page1->m_vecMsg[curSta].m_nVecPage2[curLan].m_sStateMessage));
    pBaseItem->SetPropertyValue("mText.Font",QVariant(page1->m_vecMsg[curSta].m_nVecPage2[curLan].m_sFontType));
    pBaseItem->SetPropertyValue("mText.FontSize",QVariant(page1->m_vecMsg[curSta].m_nVecPage2[curLan].m_nFontSize));
    QString str = pwnd->ColorTOString(page1->m_vecMsg[curSta].m_nVecPage2[curLan].m_nFontColor);
    pBaseItem->SetPropertyValue("mText.FontColor",QVariant(str));
    pBaseItem->SetPropertyValue("mBackRect.Pattern",QVariant(page1->m_vecMsg[curSta].m_nStyle));
    if(page1->m_vecMsg[curSta].m_nStyle == 0)
    {
        pBaseItem->SetPropertyValue("mFramRect.Pattern",QVariant(page1->m_vecMsg[curSta].m_nStyle));
    }

    str = pwnd->ColorTOString(page1->m_vecMsg[curSta].m_nFrameColor);
    pBaseItem->SetPropertyValue("mFramRect.BackColor",QVariant(str));
    str = pwnd->ColorTOString(page1->m_vecMsg[curSta].m_nForecolor);
    pBaseItem->SetPropertyValue("mBackRect.FrontColor",QVariant(str));
    str = pwnd->ColorTOString(page1->m_vecMsg[curSta].m_nBackcolor);
    pBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(str));
    pBaseItem->SetPropertyValue("mFramRect.Alpha", QVariant(page1->m_nAlpha));
    pBaseItem->SetPropertyValue("mBackRect.Alpha", QVariant(page1->m_nAlpha));

    if(pDraw)
    {
        delete pDraw;
        pDraw = NULL;
    }
}

void qMessageShow::redraw()
{
    int curSta = page1->curSta;
    int curLan = page1->m_curLan;
    pBaseItem->SetPropertyValue("mText.Text",QVariant(page1->m_vecMsg[curSta].m_nVecPage2[curLan].m_sStateMessage));
    pBaseItem->SetPropertyValue("mText.Font",QVariant(page1->m_vecMsg[curSta].m_nVecPage2[curLan].m_sFontType));
    pBaseItem->SetPropertyValue("mText.FontSize",QVariant(page1->m_vecMsg[curSta].m_nVecPage2[curLan].m_nFontSize));
    QString str = pwnd->ColorTOString(page1->m_vecMsg[curSta].m_nVecPage2[curLan].m_nFontColor);
    pBaseItem->SetPropertyValue("mText.FontColor",QVariant(str));
    pBaseItem->SetPropertyValue("mBackRect.Pattern",QVariant(page1->m_vecMsg[curSta].m_nStyle));
    if(page1->m_vecMsg[curSta].m_nStyle == 0)
    {
        pBaseItem->SetPropertyValue("mFramRect.Pattern",QVariant(page1->m_vecMsg[curSta].m_nStyle));
    }
    else
    {
        pBaseItem->SetPropertyValue("mFramRect.Pattern",QVariant(1));
    }

    str = pwnd->ColorTOString(page1->m_vecMsg[curSta].m_nFrameColor);
    pBaseItem->SetPropertyValue("mFramRect.BackColor",QVariant(str));
    str = pwnd->ColorTOString(page1->m_vecMsg[curSta].m_nForecolor);
    pBaseItem->SetPropertyValue("mBackRect.FrontColor",QVariant(str));
    str = pwnd->ColorTOString(page1->m_vecMsg[curSta].m_nBackcolor);
    pBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(str));
    pBaseItem->SetPropertyValue("mFramRect.Alpha", QVariant(page1->m_nAlpha));
    pBaseItem->SetPropertyValue("mBackRect.Alpha", QVariant(page1->m_nAlpha));
}
