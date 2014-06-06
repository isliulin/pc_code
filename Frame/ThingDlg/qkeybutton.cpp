#include "qkeybutton.h"
#include "ui_qkeybutton.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
qkeybutton::qkeybutton(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qkeybutton)
{
    pCopyItem = NULL;
    ui->setupUi(this);
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    oId = -1;
    QGraphicsItem *Item;
    bInitFlag=false;
    tabWidget = new QTabWidget();
    pASCIIInputgen=new QKeyboardASCIIGen();

    ui->tabWidget->addTab(pASCIIInputgen, tr("外观设置"));
    pSecurityWight = new SecurityWidget;
    ui->tabWidget->addTab(pSecurityWight,tr("权限设置"));

    this->setWindowTitle(tr("键盘组件"));
    //建场景
    pScene = new QGraphicsScene(this);
    ui->LView->setScene(pScene);

    connect(pASCIIInputgen, SIGNAL(onDrawSence()),this, SLOT(onTextChange()));
    connect(pASCIIInputgen, SIGNAL(onKeypress(int)),this, SLOT(onKeypress(int)));
    connect(pASCIIInputgen, SIGNAL(addPicture(QGraphicsItem*,QPixmap*)),this, SLOT(onAddPicture(QGraphicsItem*,QPixmap*)));
    if(pItem)
    {
        Item = dynamic_cast<KeyBoardItem *> (pItem)->Clone();
        InitAllProperty(dynamic_cast<KeyBoardItem *> (Item));
    }
    else
    {
        InitAllProperty(NULL);
    }
    ui->accept->setFocus(Qt::MouseFocusReason);
    bInitFlag=true;
}

qkeybutton::~qkeybutton()
{
    delete ui;
}
void qkeybutton::InitAllProperty(KeyBoardItem *pItem)
{
    if (pItem)//打开一个已有的位按钮
    {
        pCopyItem = pItem;
        pScene->clear();
        pScene->addItem(pCopyItem);
        pBaseItem = new QGroupItem(pCopyItem);
        pBaseItem->SetHeigth(100);
        pBaseItem->SetWidth(100);
        pASCIIInputgen->Init(pItem);//初始化一般页面
        pSecurityWight->init(pItem);
        oId = pItem->id();
        ui->spinBox->setValue(oId);
    }
    else//新建
    {
        pASCIIInputgen->Init(NULL);//初始化一般页面

        KeyInfo key;
        pASCIIInputgen->onGetinfo(key);

        KeyBoardItem *pGroupItem = new KeyBoardItem;
        QRectItem *pBackRect;
        QRectItem *pFramRect;
        QSimpleTextItem *pTextRect;

        QRectF brect(QPointF(5,5), QSize(90,90));
        pBackRect = new QRectItem(brect);
        //pQvalueColor->onGetValueBackColor(mColor);
        pBackRect->SetBackColor(key.nUpBackColor);
        pBackRect->SetLineType(0);
        pBackRect->setZValue(2);
        pBackRect->SetName(tr("mBackRect"));
        pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pBackRect->setFlag(QGraphicsItem::ItemIsMovable, false);

        QRectF frect(QPointF(0,0), QSize(100,100));
        pFramRect = new QRectItem(frect);
        pFramRect->SetBackColor(key.nUpFrameColor);
        pFramRect->SetLineType(0);
        pFramRect->setZValue(1);
        pFramRect->SetName(tr("mFramRect"));
        pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pFramRect->setFlag(QGraphicsItem::ItemIsMovable, false);

        QRectF mrect(QPointF(5,5), QSize(90,90));
        pTextRect = new QSimpleTextItem(mrect,key.sText);
        pTextRect->SetName("mText");
        pTextRect->SetRectOutLine(false);
        pTextRect->setZValue(5);
        pTextRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pTextRect->SetFontColor(pASCIIInputgen->sColor);

        pGroupItem->addToGroup(pFramRect);
        pGroupItem->addToGroup(pBackRect);
        pGroupItem->addToGroup(pTextRect);

        pCopyItem = pGroupItem;
        pCopyItem->textItem = pTextRect;
        pCopyItem->pBackRect = pBackRect;
        pCopyItem->frameRect = pFramRect;
        pScene->clear();
        pScene->addItem(pCopyItem);
        pBaseItem = new QGroupItem(pCopyItem);
        pBaseItem->SetHeigth(100);
        pBaseItem->SetWidth(100);
        ui->spinBox->setValue(pwnd->getNewId());
    }
}

void qkeybutton::on_accept_clicked()
{
    pASCIIInputgen->ASCIIEntryGenSave(m_key);
    pCopyItem->onSaveKey(m_key);

    //保存闪现页面属性
    if(!pSecurityWight->Save())
    {
        return;
    }
    pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
   //pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_ASCII_KEYBOARD));
   // QDialog::
    onUpkeyKeypress(m_key);
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

   accept();
}


void qkeybutton::onTextChange()
{
    KeyInfo key;
    pASCIIInputgen->onGetinfo(key);

    if(pCopyItem)
    {
        pCopyItem->SetText(key.sText);
        pCopyItem->SetFontName(key.sFontFamily);
        pCopyItem->SetFontSize(key.nFontSize + 5);

        //粗体、斜体和下划线
        if((1&(key.eFontCss)))
        {
            pCopyItem->SetFontBold(true);
        }
        else
        {
            pCopyItem->SetFontBold(false);
        }
        if((2&(key.eFontCss)))
        {
            pCopyItem->SetFontItalic(true);
        }
        else
        {
            pCopyItem->SetFontItalic(false);
        }
        if((8&(key.eFontCss)))
        {
            pCopyItem->SetFontUnderLine(true);
        }
        else
        {
            pCopyItem->SetFontUnderLine(false);
        }

        int nAligent = 4;
        if(0 == key.nPosition)
        {
            nAligent = 5;//中
        }
        else if(1 == key.nPosition)
        {
            nAligent = 4; //左
        }
        else
        {
            nAligent = 6;//右
        }
        pCopyItem->SetTextAlign(nAligent);
        pCopyItem->SetFontColor(key.sColor);

        QSimpleTextItem * item = dynamic_cast<QSimpleTextItem *> (pCopyItem->textItem);
        QString str = item->GetText();
        int i;
    }
}

void qkeybutton::onKeypress(int iFlag)//0 按下前
{
    KeyInfo key;
    pASCIIInputgen->onGetinfo(key);
    if(0 == iFlag)
    {
        onUpkeyKeypress(key);
    }
    else if(1 == iFlag)
    {
        onDownkeyKeypress(key);
    }
}

void qkeybutton::onUpkeyKeypress(KeyInfo key)//按下前 按钮按下
{
    if(pCopyItem)
    {
        pCopyItem->SetBackColor(key.nUpBackColor);
        pCopyItem->SetFramColor(key.nUpFrameColor);
        pCopyItem->SetPattern(key.eUpStyle);
        pCopyItem->SetFrontColor(key.nUpForeColor);
        if(0 == key.eUpStyle)
        {
            pCopyItem->frameRect->SetPattern(key.eUpStyle);
        }
        else
        {
            pCopyItem->frameRect->SetPattern(1);
        }
    }
}

void qkeybutton::onDownkeyKeypress(KeyInfo key)//按下后 按钮按下
{
    if(pCopyItem)
    {
        pCopyItem->SetBackColor(key.nDownBackColor);
        pCopyItem->SetFramColor(key.nDownFrameColor);
        pCopyItem->SetPattern(key.eDownStyle);
        pCopyItem->SetFrontColor(key.nDownForeColor);
        if(0 == key.eDownStyle)
        {
            pCopyItem->frameRect->SetPattern(key.eDownStyle);
        }
        else
        {
            pCopyItem->frameRect->SetPattern(1);
        }
    }
}
void qkeybutton::onAddPicture(QGraphicsItem *pItem,QPixmap* pPix)
{
    QRectF pos = pCopyItem->pBackRect->sceneBoundingRect();
    if(pItem)
    {
        QGroupItem *pBaseItem = new QGroupItem(pItem);
        pBaseItem->SetHeigth(pos.height());
        pBaseItem->SetWidth(pos.width());
        pItem->setZValue(3);
        pItem->setPos(pos.x()- pItem->boundingRect().x(),pos.y() - pItem->boundingRect().y());

        KeyBoardItem *newGroup = new KeyBoardItem;
        newGroup->pBackRect = pCopyItem->pBackRect;
        newGroup->textItem = pCopyItem->textItem;
        newGroup->frameRect = pCopyItem->frameRect;
        pCopyItem->removeFromGroup(pCopyItem->pBackRect);
        pCopyItem->removeFromGroup(pCopyItem->textItem);
        pCopyItem->removeFromGroup(pCopyItem->frameRect);

        pCopyItem->frameRect->setZValue(1);
        pCopyItem->pBackRect->setZValue(2);
        pCopyItem->textItem->setZValue(5);
        newGroup->addToGroup(pCopyItem->pBackRect);
        newGroup->addToGroup(pCopyItem->textItem);
        newGroup->addToGroup(pCopyItem->frameRect);
        newGroup->addToGroup(pItem);

        delete pCopyItem;
        pCopyItem = newGroup;
        pScene->clear();
        pScene->addItem(pCopyItem);
    }
    else if(pPix)
    {
        QGroupItem *pBaseItem = new QGroupItem(pItem);
        pBaseItem->SetHeigth(pos.height());
        pBaseItem->SetWidth(pos.width());
        pItem->setZValue(3);
        pItem->setPos(pos.x()- pItem->boundingRect().x(),pos.y() - pItem->boundingRect().y());

        KeyBoardItem *newGroup = new KeyBoardItem;
        newGroup->pBackRect = pCopyItem->pBackRect;
        newGroup->textItem = pCopyItem->textItem;
        newGroup->frameRect = pCopyItem->frameRect;
        pCopyItem->removeFromGroup(pCopyItem->pBackRect);
        pCopyItem->removeFromGroup(pCopyItem->textItem);
        pCopyItem->removeFromGroup(pCopyItem->frameRect);

        pCopyItem->frameRect->setZValue(1);
        pCopyItem->pBackRect->setZValue(2);
        pCopyItem->textItem->setZValue(5);

        newGroup->addToGroup(pCopyItem->pBackRect);
        newGroup->addToGroup(pCopyItem->textItem);
        newGroup->addToGroup(pCopyItem->frameRect);
        newGroup->addToGroup(pItem);

        delete pCopyItem;
        pCopyItem = newGroup;
        pScene->clear();
        pScene->addItem(pCopyItem);
    }
    else
    {
        KeyBoardItem *newGroup = new KeyBoardItem;
        newGroup->pBackRect = pCopyItem->pBackRect;
        newGroup->textItem = pCopyItem->textItem;
        newGroup->frameRect = pCopyItem->frameRect;
        pCopyItem->removeFromGroup(pCopyItem->pBackRect);
        pCopyItem->removeFromGroup(pCopyItem->textItem);
        pCopyItem->removeFromGroup(pCopyItem->frameRect);

        pCopyItem->frameRect->setZValue(1);
        pCopyItem->pBackRect->setZValue(2);
        pCopyItem->textItem->setZValue(5);

        newGroup->addToGroup(pCopyItem->pBackRect);
        newGroup->addToGroup(pCopyItem->textItem);
        newGroup->addToGroup(pCopyItem->frameRect);
        newGroup->addToGroup(pItem);

        delete pCopyItem;
        pCopyItem = newGroup;
        pScene->clear();
        pScene->addItem(pCopyItem);
    }
    pBaseItem = new QGroupItem(pCopyItem);
}
void qkeybutton::on_cancel_clicked()
{
    this->close();
}

void qkeybutton::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_KEY);
}
