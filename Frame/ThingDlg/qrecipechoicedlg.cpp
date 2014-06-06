#include "qrecipechoicedlg.h"
#include "Frame/mainwindow.h"
#include "ui_qrecipechoicedlg.h"
#include "Macro/macroedit.h"

extern MainWindow *pwnd;

QRecipeChoiceDlg::QRecipeChoiceDlg(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRecipeChoiceDlg)
{
    ui->setupUi(this);

    oId = -1;
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    QGraphicsItem *Item;
    ui->m_fontCbBox->addItems(QFontDatabase().families(QFontDatabase::Any));
    pwnd->InitFontSize(ui->m_FontSizecbBox);//初始化字体大小下拉列表框

    pSecurityWight = new SecurityWidget;
    ui->m_tabWidget->addTab(pSecurityWight,tr("权限设置"));

    connect(ui->m_cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->m_helpBtn, SIGNAL(clicked()), this, SLOT(loadHelp()));
    connect(ui->m_okBtn, SIGNAL(clicked()), this, SLOT(confyButton()));

    QColor mBackColor(255,255,255);
    onSetBackColor(mBackColor);
    QColor mTextColor(0,0,0);
    onSetTextColor(mTextColor);
    this->setFixedSize(609,517);
    pCopyItem = NULL;

    ui->comboBox->clear();
    for(int i = 0; i < pwnd->m_pSamSysParame->m_qvcRecipe.size(); i++)
    {
        ui->comboBox->addItem(pwnd->m_pSamSysParame->m_qvcRecipe[i].sName);
    }
    int index = ui->m_fontCbBox->findText(tr("Droid Sans Fallback"));
    if(index >= 0)
    {
        ui->m_fontCbBox->setCurrentIndex(index);
    }
    else
    {
        ui->m_fontCbBox->setCurrentIndex(ui->m_fontCbBox->findText(tr("System")));

    }

    foreach(Macro lib,pwnd->macros)
    {
        if (lib.type && lib.isCompiled())
        {
            ui->m_MacroCmBox->addItem(lib.libName);
        }
    }

    //connect(ui->m_MacroCmBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(libraryChanged(QString)));
    if(pItem)
    {
        Item = dynamic_cast<QRcipeItem *> (pItem)->Clone();
        Init(dynamic_cast<QRcipeItem *> (Item));
    }
    else
    {
        Init(NULL);
        ui->spinBox->setValue(pwnd->getNewId());
    }
    ui->m_okBtn->setFocus();
}

QRecipeChoiceDlg::~QRecipeChoiceDlg()
{
    delete ui;
}

void QRecipeChoiceDlg::confyButton()
{
    drawRecipeSelect();

    if(!pCopyItem)
    {
        return;
    }
    //保存权限页面属性
    if(!pSecurityWight->Save())
    {
        return;
    }
    pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));

    onSaveInfo();
    pCopyItem->onSaveInfo(m_Rcipe);
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

void QRecipeChoiceDlg::loadHelp()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_RECIPE);
}

void QRecipeChoiceDlg::Init(QRcipeItem *pItem)
{
    if(pItem)
    {
        pSecurityWight->init(pItem);
        m_Rcipe = pItem->m_Rcipe;
        if(1 == m_Rcipe.eShowType)
        {
            ui->m_TableradioBtn->setChecked(true);
            on_m_TableradioBtn_clicked(true);
        }
        else
        {
            ui->m_ComboradioBtn->setChecked(true);//列表
            on_m_ComboradioBtn_clicked(true);
        }
        if(-1 == m_Rcipe.sShowRecipeId)
        {
            m_Rcipe.sShowRecipeId = 0;
        }
        ui->comboBox->setCurrentIndex(m_Rcipe.sShowRecipeId);//配方组ID
        int index = ui->m_fontCbBox->findText(m_Rcipe.sFontFamily);
        if(-1 != index)
        {
            ui->m_fontCbBox->setCurrentIndex(index);
        }
        ui->m_FontSizecbBox->setCurrentIndex(m_Rcipe.nFontSize);  //字体大小
        onSetTextColor(m_Rcipe.nTextColor);
        onSetBackColor(m_Rcipe.nBackColor);
        ui->m_RowCountSpBox->setValue(m_Rcipe.nCurrShowRow);
        ui->m_UseMacroCkkgroupBox->setChecked(m_Rcipe.bUseMacro);


        index = ui->m_MacroCmBox->findText(m_Rcipe.macroName);
        //if(index >= 0)
        {
            ui->m_MacroCmBox->setCurrentIndex(index);
        }

        ui->m_TransparentspBox->setValue(m_Rcipe.nTransparent);
        oId = pItem->id();
        ui->spinBox->setValue(oId);

    }
}

void QRecipeChoiceDlg::on_m_TextColorpushBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_TextColorpushBtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(onSetTextColor(const QColor &)));
}

void QRecipeChoiceDlg::onSetTextColor(const QColor &mColor)
{
    ui->m_TextColorpushBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QRecipeChoiceDlg::on_m_BackColorpushBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_BackColorpushBtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(onSetBackColor(const QColor &)));
}

void QRecipeChoiceDlg::onSetBackColor(const QColor &mColor)
{
   ui->m_BackColorpushBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QRecipeChoiceDlg::onSaveInfo()
{
    if(ui->m_TableradioBtn->isChecked())
    {
        m_Rcipe.eShowType = 1;
    }
    else
    {
        m_Rcipe.eShowType = 2;//列表
    }
    m_Rcipe.sShowRecipeId = ui->comboBox->currentIndex();//配方组ID
    m_Rcipe.sFontFamily = ui->m_fontCbBox->currentText();//字体类型
    m_Rcipe.nFontSize = ui->m_FontSizecbBox->currentIndex();  //字体大小
    m_Rcipe.nTextColor = ui->m_TextColorpushBtn->palette().background().color();
    m_Rcipe.nBackColor = ui->m_BackColorpushBtn->palette().background().color();
    m_Rcipe.nCurrShowRow = ui->m_RowCountSpBox->value();
    m_Rcipe.bUseMacro = ui->m_UseMacroCkkgroupBox->isChecked();
    m_Rcipe.macroName = ui->m_MacroCmBox->currentText();
    m_Rcipe.functionName = "MACRO_MAIN";
    m_Rcipe.nTransparent = ui->m_TransparentspBox->value();
}

void QRecipeChoiceDlg::drawRecipeSelect()
{
    if(pCopyItem)
    {
        delete pCopyItem;
        pCopyItem = NULL;
    }
    QColor mBkColor = ui->m_BackColorpushBtn->palette().background().color();         //背景颜色
    short nTransparent  = ui->m_TransparentspBox->value();
    int nHNum = ui->m_RowCountSpBox->value();           //行数
    int nType = 0;
    if(ui->m_TableradioBtn->isChecked())//0表示列表，1表示下拉框
    {
        nType = 0;
    }
    else
    {
       nType = 1;
    }

    double mMoveX = 0;                //主刻度X起始点
    double mMoveY = 0;                //主刻度Y起始点
    double mLineX = 0;                //主刻度X起始点
    double mLineY = 0;                //主刻度Y起始点
    pCopyItem  = new QRcipeItem;
    QLineItem *pLine;
    int i = 0;
    int WH = 100;
    double HVal = 100.0/nHNum;
    QString str = "";

    QRectF rect(QPointF(0,0), QSize(WH,WH));        //绘制边框色矩形框
    QRectItem *pRect = NULL;

    if(nType == 0) //列表
    {
        pRect = new QRectItem(rect);
        pRect->SetBackColor(mBkColor);                    //设置背景色
        pRect->SetName("mRect");
        pRect->SetAlpha(nTransparent);
        pRect->SetLineColor(Qt::black);
        pCopyItem->addToGroup(pRect);

        /*********************************************************************
     *以下是画水平格线
     ********************************************************************/
        for(i = 1; i < nHNum; i++)
        {
            QPainterPath mPath;
            mMoveX = 0;
            mMoveY = i*HVal;
            mLineX = WH;
            mLineY = i*HVal;
            mPath.moveTo(mMoveX,mMoveY);
            mPath.lineTo(mLineX,mLineY);
            pLine = new QLineItem(mPath);
            str = QString("%1").arg(i);
            str = "HLine"+str;
            pLine->SetName(str);
            pCopyItem->addToGroup(pLine);
        }
    }
    else if(nType == 1) //下拉框列表
    {
        rect.setSize(QSize(108,18));//绘制外框矩形
        pRect = new QRectItem(rect);//QRectItem *
        pRect->SetPattern(1);
        pRect->SetBackColor(mBkColor);
        pRect->SetName("mFramRect");
        pRect->setZValue(1);
        pRect->SetAlpha(nTransparent);
        pRect->SetLineType(1);
        pRect->SetLineColor(QColor(183,211,252));
        pCopyItem->addToGroup(pRect);
        pRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

        rect.setTopLeft(QPointF(84,0));               //绘制背景矩形框
        rect.setSize(QSize(24,18));
        QRectItem *pBackRect = new QRectItem(rect);
        pBackRect->SetBackColor(QColor(183,211,252));
        pBackRect->SetLineType(0);
        pBackRect->SetName("mBackRect");
        pBackRect->setZValue(2);
        pBackRect->SetAlpha(nTransparent);
        pCopyItem->addToGroup(pBackRect);
        pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QFoldLineItem *pLine;
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
        pCopyItem->addToGroup(pLine);
        pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }

    //pCopyItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    //pCopyItem->setFlag(QGraphicsItem::ItemIsMovable, false);

}

void QRecipeChoiceDlg::on_m_TableradioBtn_clicked(bool checked)
{
    if(checked)
    {
//        ui->m_RowCountSpBox->show();
//        ui->m_RowCountlabel->show();
    }
}

void QRecipeChoiceDlg::on_m_ComboradioBtn_clicked(bool checked)
{
    if(checked)
    {
//        ui->m_RowCountSpBox->hide();
//        ui->m_RowCountlabel->hide();
    }
}



void QRecipeChoiceDlg::on_btn_new_clicked()
{
    Macro lib;
    AddLib addWzrd(pwnd->macros,this);
    addWzrd.setWindowTitle(tr("添加脚本"));
    if(addWzrd.exec() == QDialog::Accepted)
    {
        lib.libName = addWzrd.libName;
        lib.type = true;
        lib.setCompipiled(false);
        lib.setCode(SCRIPT_HEADER);
        pwnd->macros.append(lib);
        MacroEdit *dlg = new MacroEdit(lib.libName,this);
        dlg->exec();
        pwnd->is_Save=false;
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
    }
    QString libname = ui->m_MacroCmBox->currentText();
    ui->m_MacroCmBox->clear();
    foreach(Macro lib,pwnd->macros) //初始化库名称
    {
        if (lib.type && lib.isCompiled())
        {
            ui->m_MacroCmBox->addItem(lib.libName);
        }
    }
    int index = ui->m_MacroCmBox->findText(libname);
    if(index >= 0)
    {
        ui->m_MacroCmBox->setCurrentIndex(index);
    }
}
