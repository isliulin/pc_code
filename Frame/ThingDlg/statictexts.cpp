#include "Frame/ThingDlg/statictexts.h"
#include "ui_StaticTexts.h"
#include "view/qsimpletextitem.h"
#include "view/switchitem.h"
#include "Frame\MainWindow.h"

extern MainWindow *pwnd;

StaticTexts::StaticTexts(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StaticTexts)
{
    sText = "";
    QGraphicsItem *Item;
    ui->setupUi(this);
    oId = -1;
    this->setFixedSize(this->size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    pScene = new QGraphicsScene(this);
    ui->MainView->setScene(pScene);

    tabWidget = new QTabWidget();

    pGeneralDlg = new StaticTextDlg ;
    securitywidget = new SecurityWidget;

    ui->tabWidget->addTab(pGeneralDlg, tr("外观设置"));
    ui->tabWidget->addTab(securitywidget, tr("权限设置"));

    connect(pGeneralDlg, SIGNAL(DrawTextView()),this, SLOT(DrawStaticTexts()));
    if(pItem)
    {
        sText = pItem->data(GROUP_NAME_KEY).toString();//判断键盘
        Item = dynamic_cast<StaticTextItem *> (pItem)->Clone();
        pGeneralDlg->OnDoubleClickInit(dynamic_cast<StaticTextItem *> (Item));//外观

        securitywidget->init(dynamic_cast<StaticTextItem *> (Item));//权限
        pScene->clear();
        DrawStaticTexts();
        oId = dynamic_cast<StaticTextItem *> (pItem)->id();
        ui->spinBox->setValue(oId);
    }
    else
    {
        pGeneralDlg->InitParament();
        securitywidget->init(0);
        pScene->clear();
        DrawStaticTexts();
        ui->spinBox->setValue(pwnd->getNewId());
    }
    this->setWindowTitle(tr("静态文本"));
    securitywidget->setTouchGroupEnabled(false);
}
StaticTexts::~StaticTexts()
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
    if(tabWidget)
    {
        delete tabWidget;
        tabWidget = NULL;
    }
}

void StaticTexts::DrawStaticTexts()
{
    pScene->clear();
    int iLan = pGeneralDlg->ui->m_languagecmb->currentIndex();
    if(iLan < 0)
        iLan = 0;
    QSimpleTextItem *pTxt = new QSimpleTextItem;
    pTxt->SetText(pGeneralDlg->TxtProperty[iLan].sText);
    int align=pGeneralDlg->ui->combo_Alignment->currentIndex();
    if(pGeneralDlg->TxtProperty[iLan].adapt){
        pTxt->SetFontSize(5);
        pTxt->SetTextAlign(5);
    }else{
        pTxt->SetFontSize(pGeneralDlg->TxtProperty[iLan].nFontSize);
        if(align==0){
            pTxt->SetTextAlign(5);
        }else if(align==1){
            pTxt->SetTextAlign(4);
        }else if(align==2){
            pTxt->SetTextAlign(6);
        }
    }
    pTxt->SetFontName(pGeneralDlg->ui->font->currentText());
    pTxt->SetFitSize(pGeneralDlg->TxtProperty[iLan].adapt);

    pTxt->SetFontColor(pGeneralDlg->ui->FontColor->palette().background().color());
    pTxt->SetFontBold(pGeneralDlg->ui->IfBold->isChecked());
    pTxt->SetFontItalic(pGeneralDlg->ui->IfItalic->isChecked());
    pTxt->SetFontWordInterval(pGeneralDlg->ui->WordInterval->value());
    pTxt->SetFontUnderLine(pGeneralDlg->ui->m_underlinecheck->isChecked());



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

    pScene->addItem(pCopyItem);        //添加到场景
    pCopyItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pCopyItem->setFlag(QGraphicsItem::ItemIsMovable, false);
    pBaseItem = new QGroupItem(pCopyItem);
    pBaseItem->SetHeigth(100);
    pBaseItem->SetWidth(100);
}

void StaticTexts::on_accept_clicked()
{
    //画文本
    DrawStaticTexts();
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
    pCopyItem->setData(GROUP_NAME_KEY,QVariant(sText));
    pCopyItem->setId(ui->spinBox->value());

    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return ;
    }

    QDialog::accept();
}

void StaticTexts::on_cancel_clicked()
{
    this->close();
}

void StaticTexts::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_STATICTEXT);
}
