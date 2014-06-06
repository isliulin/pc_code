#include "qtrenddatagroup.h"
#include "ui_qtrenddatagroup.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

QTrendDataGroup::QTrendDataGroup(QTrendDataGroupAttr *pItem, QWidget *parent):QDialog(parent),ui(new Ui::QTrendDataGroup)
{
    ui->setupUi(this);

    oId = -1;
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    m_pCopyItem = NULL;

    m_pTrendTableDlg    = new QTrendbTable;
    m_pTrendDispAreaDlg = new QTrendbDispArea;
    //m_pTrendColor       = new QTrendbColor;

    ui->tabWidget->addTab(m_pTrendTableDlg, tr("数据群组外观"));
    ui->tabWidget->addTab(m_pTrendDispAreaDlg, tr("数据群组显示"));
    //ui->tabWidget->addTab(m_pTrendColor, tr("数据群组颜色"));

    pSecurityWight = new SecurityWidget(this);
    ui->tabWidget->addTab(pSecurityWight, tr("权限设置"));
    //pSecurityWight->ui->groupBox_Touch->hide();
    pSecurityWight->setTouchGroupEnabled(false);

    this->setWindowTitle(tr("数据群组显示"));

    ui->label_ctlType->setText(tr("曲线:数据群组"));
    ui->graphicsView->setScene(&scene);
    QPixmap pic(":/standardtool/images/datagroup.png");
    scene.addPixmap(pic.scaled(110,110));

    //connect(m_pTrendTableDlg, SIGNAL(ChnnelChange(int, int)), m_pTrendColor, SLOT(set_comboBox_chnnel_num(int, int)));

    InitAllProperty(pItem);
}

void QTrendDataGroup::InitAllProperty(QTrendDataGroupAttr *pItem)
{
    if(pItem)
    {
        oId = pItem->id();
        ui->spinBox->setValue(oId);

        m_pTrendTableDlg->Init(pItem);
        m_pTrendDispAreaDlg->Init(pItem);
        //m_pTrendColor->Init(pItem);
        pSecurityWight->init(pItem);

    }
    else
    {
        ui->spinBox->setValue(pwnd->getNewId());
        m_pTrendTableDlg->Init(NULL);
        m_pTrendDispAreaDlg->Init(NULL);
        //m_pTrendColor->Init(NULL);
        pSecurityWight->init(NULL);
    }
}

QTrendDataGroup::~QTrendDataGroup()
{
    if(m_pTrendTableDlg)
    {
        delete m_pTrendTableDlg;
        m_pTrendTableDlg = NULL;
    }

    if(m_pTrendDispAreaDlg)
    {
        delete m_pTrendDispAreaDlg;
        m_pTrendDispAreaDlg = NULL;
    }

    if(pSecurityWight)
    {
        delete pSecurityWight;
        pSecurityWight = NULL;
    }

    if(m_pCopyItem)
    {
        delete m_pCopyItem;
        m_pCopyItem = NULL;
    }

    delete ui;
}

void QTrendDataGroup::on_accept_clicked()
{
    m_pCopyItem = new QTrendDataGroupAttr;

    if(pSecurityWight && pSecurityWight->Save())
    {
        m_pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    }
    else
    {
        return;
    }

    //曲线外观设置对话框
    if(m_pTrendTableDlg && m_pTrendTableDlg->save())
    {
        m_pCopyItem->m_bIsAll           = m_pTrendTableDlg->m_bIsAll;
        m_pCopyItem->m_sCurChnnel    = m_pTrendTableDlg->m_sCurChnnel;
        m_pCopyItem->m_nDisplayMax      = m_pTrendTableDlg->getDisplayMax();
        m_pCopyItem->m_nDisplayMin      = m_pTrendTableDlg->getDisplayMin();
        m_pCopyItem->m_sChnnelBegin     = m_pTrendTableDlg->m_sChnnelBegin;
        m_pCopyItem->m_nTotalTrendNumber= m_pTrendTableDlg->m_vecChannelGroups.size();
        m_pCopyItem->m_selGroups        = m_pTrendTableDlg->m_selGroups;
        m_pCopyItem->m_vecChannelGroups.clear();
        m_pCopyItem->m_vecChannelGroups = m_pTrendTableDlg->m_vecChannelGroups;

        m_pCopyItem->m_vecDisplayGroups.clear();
    }
    else
    {
        return;
    }

    //QTrendadisplay*     m_pTrendDisplay;//曲线显示区设置
    m_pCopyItem->m_bSelectVertMinor  = m_pTrendDispAreaDlg->m_bSelectVertMinor;  //是否显示垂直次标尺
    m_pCopyItem->m_bSelectHorMinor   = m_pTrendDispAreaDlg->m_bSelectHorMinor;   //是否显示水平次标尺
    m_pCopyItem->m_bMainHor          = m_pTrendDispAreaDlg->m_bMainHor;
    m_pCopyItem->m_bMainVer          = m_pTrendDispAreaDlg->m_bMainVer;
    m_pCopyItem->m_nDataSample       = m_pTrendDispAreaDlg->m_nDataSample;       //数据样本数
    m_pCopyItem->m_nVertMajorScale   = m_pTrendDispAreaDlg->m_nVertMajorScale;   //垂直主标尺
    m_pCopyItem->m_nVertMinorScale   = m_pTrendDispAreaDlg->m_nVertMinorScale;   //垂直次标尺
    m_pCopyItem->m_nHorMajorScale    = m_pTrendDispAreaDlg->m_nHorMajorScale;    //水平主标尺
    m_pCopyItem->m_nHorMinorScale    = m_pTrendDispAreaDlg->m_nHorMinorScale;    //水平次标尺

    //QTrendbColor*       m_pTrendDispAreaDlg;//曲线颜色设置
    m_pCopyItem->m_bGrade      = m_pTrendDispAreaDlg->m_bGrade;
    m_pCopyItem->m_nVerColor   = m_pTrendDispAreaDlg->m_nVerColor;
    m_pCopyItem->m_nHorColor   = m_pTrendDispAreaDlg->m_nHorColor;
    m_pCopyItem->m_nBoradColor = m_pTrendDispAreaDlg->m_nBoradColor;	//边框颜色
    m_pCopyItem->m_nScaleColor = m_pTrendDispAreaDlg->m_nScaleColor;	//标尺颜色
    m_pCopyItem->m_nGraphColor = m_pTrendDispAreaDlg->m_nGraphColor;	//图表区颜色
    m_pCopyItem->m_nMarkedColor = m_pTrendDispAreaDlg->m_nMarkedColor;	//标注颜色
    m_pCopyItem->m_nFontSize   = m_pTrendDispAreaDlg->getFontSize();
    m_pCopyItem->m_alpha       = m_pTrendDispAreaDlg->getAlpha();
    m_pCopyItem->m_vecGroupColor.clear();                //各个通道颜色设置

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
    QDrawGraphics *pDraw = new QDrawGraphics;
    pDraw->OnDrawDataGroup(m_pCopyItem);  //加载图形
    if(pDraw)
    {
        delete pDraw;
        pDraw = NULL;
    }

    QDialog::accept();
}

void QTrendDataGroup::on_cancel_clicked()
{
    this->close();
}

void QTrendDataGroup::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_GROUPDATA);
}



















