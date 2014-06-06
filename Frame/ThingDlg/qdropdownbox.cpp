#include "qdropdownbox.h"
#include "ui_qdropdownbox.h"
#include "view/switchitem.h"
#include "Frame/mainwindow.h"
#include "combopicture.h"

extern MainWindow *pwnd;

qDropDownBox::qDropDownBox(QDropdownAttr *pItem, QWidget *parent):QDialog(parent),ui(new Ui::qDropDownBox)
{
    ui->setupUi(this);

    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    m_pCopyItem = NULL;//拷贝的整个结构体
    pTempItem = NULL;

    m_pDropDownList = new qDropDownList;
    m_pDropDownFont = new qDropDownFont;

	pScene = new QGraphicsScene(this); //建场景
	ui->graphicsView->setScene(pScene);//贴图区域

    ui->tabWidget->addTab(m_pDropDownList, tr("下拉框设置"));
    ui->tabWidget->addTab(m_pDropDownFont, tr("字体设置"));

    m_pPictureList = new ComboPicture();

    pSecurityWight = new SecurityWidget(this);
    ui->tabWidget->addTab(pSecurityWight, tr("权限设置"));

    this->setWindowTitle(tr("功能选择按钮"));

    connect(m_pDropDownFont, SIGNAL(alphaCh(short )), this, SLOT(redraw(short )));

    connect(m_pDropDownList,SIGNAL(picturechecked(bool)),this,SLOT(on_checked_picture(bool)));

    connect(m_pDropDownList,SIGNAL(addFun(QString,QString)),m_pPictureList,SLOT(on_Add(QString,QString)));
    connect(m_pDropDownList,SIGNAL(deleteFun(QString,QString)),m_pPictureList,SLOT(on_Delete(QString,QString)));

    connect(m_pPictureList,SIGNAL(rowChanged(int )),this,SLOT(on_rowChanged(int)));
    connect(m_pPictureList,SIGNAL(picChanged(int ,EITEM_TYPE ,QString)),m_pDropDownList,SLOT(on_sel_pic(int ,EITEM_TYPE ,QString)));
    InitProperty(pItem);

    redraw(m_pDropDownFont->m_nAlpha);
}

void qDropDownBox::redraw(short alpha)
{
    if(pTempItem)
    {
        delete pTempItem;
        pTempItem = NULL;
    }
    pTempItem = new QDropdownAttr;

    QRectF rect = QRectF(0,0,108,18);
    //rect.setSize(QSize(108,18));//绘制外框矩形
    pRect = new QRectItem(rect);//
    pRect->SetLineColor(QColor(127,157,185));
    pRect->SetPattern(1);
    pRect->SetBackColor(m_pDropDownFont->m_nBackColor);
    pRect->SetName("mFramRect");
    pRect->setZValue(1);
    pRect->SetAlpha(alpha);
    pTempItem->addToGroup(pRect);
    //addToGroup(pRect);
    pRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    rect.setTopLeft(QPointF(84,0));               //绘制背景矩形框
    rect.setSize(QSize(24,18));
    pBackRect = new QRectItem(rect);
    pBackRect->SetBackColor(QColor(183,211,252));
    pBackRect->SetLineType(0);
    pBackRect->SetName("mBackRect");
    pBackRect->setZValue(2);
    pBackRect->SetAlpha(alpha);
    pTempItem->addToGroup(pBackRect);
    //addToGroup(pBackRect);
    pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

    QPainterPath mPenPath = QPainterPath();
    mPenPath.moveTo(QPointF(90,7));//第一点
    mPenPath.lineTo(QPointF(96,11));
    mPenPath.lineTo(QPointF(102,7));
    pLine = new QFoldLineItem(mPenPath);
    pLine->setLineType(1);
    pLine->setLineWidth(2); //设置线条宽度
    pLine->setLineColor(QColor(77,97,133)); //线条颜色
    pLine->SetName("mLine");
    pLine->setZValue(4);
    //pLine->setAlpha(alpha);
    pTempItem->addToGroup(pLine);
    //addToGroup(pLine);
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

    QLineItem *pLineTemp;

    QPainterPath mPath1;
    mPath1.moveTo(0,0);         //画直线的起点
    mPath1.lineTo(108,0);         //画直线的终点
    pLineTemp = new QLineItem(mPath1);        //画细直线
    pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
    pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->addToGroup(pLineTemp);                   //添加到组

    QPainterPath mPath2;
    mPath2.moveTo(0,0);         //画直线的起点
    mPath2.lineTo(0,18);         //画直线的终点
    pLineTemp = new QLineItem(mPath2);        //画细直线
    pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
    pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->addToGroup(pLineTemp);                   //添加到组

    QPainterPath mPath3;
    mPath3.moveTo(108,0);         //画直线的起点
    mPath3.lineTo(108,18);         //画直线的终点
    pLineTemp = new QLineItem(mPath3);        //画细直线
    pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
    pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->addToGroup(pLineTemp);                   //添加到组

    QPainterPath mPath4;
    mPath4.moveTo(0,18);         //画直线的起点
    mPath4.lineTo(108,18);         //画直线的终点
    pLineTemp = new QLineItem(mPath4);        //画细直线
    pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
    pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->addToGroup(pLineTemp);                   //添加到组

    if(pScene)
    {
        pScene->addItem(pTempItem);        //添加到场景
    }

    pTempItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->setFlag(QGraphicsItem::ItemIsMovable, false);
}

qDropDownBox::~qDropDownBox()
{  
    if(m_pDropDownList)
    {
        delete m_pDropDownList;
        m_pDropDownList = NULL;
    }

    if(m_pDropDownFont)
    {
        delete m_pDropDownFont;
        m_pDropDownFont = NULL;
    }

    if(pSecurityWight)
    {
        delete pSecurityWight;
        pSecurityWight = NULL;
    }

    if(pRect)
    {
        delete pRect;
        pRect = NULL;
    }

    if(pBackRect)
    {
        delete pBackRect;
        pBackRect = NULL;
    }

    if(pLine)
    {
        delete pLine;
        pLine = NULL;
    }

    if(pTempItem)
    {
        delete pTempItem;
        pTempItem = NULL;
    }

    if(pScene)
    {
        delete pScene;
        pScene = NULL;
    }

    /**/

    delete ui;
}

void qDropDownBox::InitProperty(QDropdownAttr *pItem)
{
    if(pItem)
    {
        m_pDropDownList->Init(pItem);
        m_pDropDownFont->Init(pItem);
        pSecurityWight->init(pItem);
        on_checked_picture(pItem->m_bUsePic);
        oId = pItem->id();
        ui->spinBox->setValue(oId);
    }
    else
    {
        m_pDropDownList->Init(NULL);
        m_pDropDownFont->Init(NULL);
        pSecurityWight->init(NULL);
        on_checked_picture(false);
        ui->spinBox->setValue(pwnd->getNewId());
    }
}

void qDropDownBox::on_accept_clicked()
{
    m_pCopyItem = new QDropdownAttr;

    if(pSecurityWight && pSecurityWight->Save())
    {
        m_pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    }
    else
    {
        return;
    }

    m_pCopyItem->m_nShowNumber      = m_pDropDownList->m_nShowNumber;
    m_pCopyItem->totalScreen        = m_pDropDownList->screenNum;
    m_pCopyItem->isUseScript        = m_pDropDownList->isUseScript;
    m_pCopyItem->macroName          = m_pDropDownList->macroName;
    m_pCopyItem->functionName       = "MACRO_MAIN";
    m_pCopyItem->m_vecSwitchItem    = m_pDropDownList->m_vecSwitchItem;
    m_pCopyItem->m_bUsePic           = m_pDropDownList->getPicCheck();

    m_pCopyItem->m_strFontName      = m_pDropDownFont->m_strFontName;
    m_pCopyItem->m_nFontSize        = m_pDropDownFont->m_nFontSize;
    m_pCopyItem->m_nLanType         = m_pDropDownFont->m_nLanType;
    m_pCopyItem->m_nFontStyle       = m_pDropDownFont->m_nFontStyle;
    m_pCopyItem->m_nFontColor       = m_pDropDownFont->m_nFontColor;
    m_pCopyItem->m_nBackColor       = m_pDropDownFont->m_nBackColor;
    m_pCopyItem->m_nAlpha           = m_pDropDownFont->m_nAlpha;

    m_pCopyItem->resetDropDown(m_pCopyItem->m_nBackColor, m_pDropDownFont->m_nAlpha);
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

    QDialog::accept();
}

void qDropDownBox::on_cancel_clicked()
{
    this->close();
}

void qDropDownBox::on_checked_picture(bool checked)
{
    ui->tabWidget->clear();
    ui->tabWidget->addTab(m_pDropDownList, tr("下拉框设置"));
    ui->tabWidget->addTab(m_pDropDownFont, tr("字体设置"));

    if(checked)
    {
        ui->tabWidget->addTab(m_pPictureList,tr("图片列表"));
        m_pPictureList->Init(m_pDropDownList->m_vecSwitchItem);
    }
    ui->tabWidget->addTab(pSecurityWight, tr("权限设置"));
}
void qDropDownBox::on_rowChanged(int row )
{
    if(m_pDropDownList && m_pDropDownList->getPicCheck())
    {
        QVector<SwitchInfo> vecSwitchItem =  m_pDropDownList->m_vecSwitchItem;
        if(row < vecSwitchItem.size() && m_pPictureList)
        {
            m_pPictureList->showRowPic(vecSwitchItem[row].bLib,vecSwitchItem[row].sPath);
        }
    }
}
void qDropDownBox::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_DROPDOWN);
}











