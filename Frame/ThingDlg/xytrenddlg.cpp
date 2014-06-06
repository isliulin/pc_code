#include "xytrenddlg.h"
#include "ui_xytrenddlg.h"
#include "Frame/mainwindow.h"
#include "xytrendgendlg.h"
#include "qtrendadisplay.h"
#include "switch/securitywidget.h"

extern MainWindow *pwnd;
XYTrendDlg::XYTrendDlg(XYtrend *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::XYTrendDlg)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    //setWindowOpacity(0.95);
    oId = -1;
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);

    m_pCopyItem = NULL;//

    m_pGenDlg        = new XYTrendGenDlg;
    m_pTrendDisplay     = new QTrendadisplay;

    ui->tabWidget->addTab(m_pGenDlg, tr("通道设置"));
    ui->tabWidget->addTab(m_pTrendDisplay, tr("显示设置"));

    pSecurityWight = new SecurityWidget(this);
    ui->tabWidget->addTab(pSecurityWight, tr("权限设置"));
    //pSecurityWight->ui->groupBox_Touch->hide();
    pSecurityWight->setTouchGroupEnabled(false);

    this->setWindowTitle(tr("X-Y曲线"));

    ui->label_ctlType->setText(tr("曲线:X-Y曲线"));
    ui->graphicsView->setScene(&scene);
    QPixmap pic(":/standardtool/images/trend.png");
    scene.addPixmap(pic.scaled(110,110));
    InitAllProperty(pItem);
}

XYTrendDlg::~XYTrendDlg()
{
    delete ui;
}

void XYTrendDlg::InitAllProperty(XYtrend *pItem)
{
    if (pItem)
    {
        m_pGenDlg->Init(pItem);
        m_pTrendDisplay->InitXY(pItem);
        pSecurityWight->init(pItem);
        oId = pItem->id();
        ui->spinBox->setValue(oId);
    }
    else
    {
        m_pGenDlg->Init(NULL);
        qDebug() << "m_pTrendDisplay::InitXY";
        m_pTrendDisplay->InitXY(NULL);
        qDebug() << "pSecurityWight::init";
        pSecurityWight->init(NULL);
        ui->spinBox->setValue(pwnd->getNewId());
    }
}

void XYTrendDlg::on_accept_clicked()
{
    m_pCopyItem = new XYtrend;
    if(m_pGenDlg && m_pGenDlg->save())
    {
        m_pCopyItem->m_bIsAll        = m_pGenDlg->m_bIsAll;
        m_pCopyItem->chlCount        = m_pGenDlg->chlCount;//通道总数
        m_pCopyItem->addrLength      = m_pGenDlg->addrLength;//地址长度，相当于采样点数
        m_pCopyItem->m_dataType      = m_pGenDlg->m_dataType;//数据类型
        m_pCopyItem->m_TriggerAddr   = m_pGenDlg->m_TriggerAddr;//触发地址
        m_pCopyItem->m_bReset        = m_pGenDlg->m_bReset;//是否自动复位

        m_pCopyItem->m_bScale        = m_pGenDlg->m_bScale;//是否缩放

        m_pCopyItem->m_bDisplayConst   = m_pGenDlg->m_bDisplayConst;	//是否常量范围
        m_pCopyItem->m_DisplayMaxAddrX = m_pGenDlg->m_DisplayMaxAddrX;
        m_pCopyItem->m_DisplayMinAddrX = m_pGenDlg->m_DisplayMinAddrX;
        m_pCopyItem->m_nDisplayMinX   = m_pGenDlg->m_nDisplayMinX;	//显示最小值
        m_pCopyItem->m_nDisplayMaxX   = m_pGenDlg->m_nDisplayMaxX;	//显示最大值
        m_pCopyItem->m_bConstX        = m_pGenDlg->m_bConstX;//是否常量范围
        m_pCopyItem->m_SourceMaxAddrX = m_pGenDlg->m_SourceMaxAddrX;//源范围最大值 地址
        m_pCopyItem->m_SourceMinAddrX = m_pGenDlg->m_SourceMinAddrX;//源范围最小值 地址
        m_pCopyItem->m_nSourceMaxX    = m_pGenDlg->m_nSourceMaxX;	//源范围最大值
        m_pCopyItem->m_nSourceMinX    = m_pGenDlg->m_nSourceMinX;	//源范围最小值

        m_pCopyItem->m_bDisplayConstY   = m_pGenDlg->m_bDisplayConstY;	//是否常量范围
        m_pCopyItem->m_DisplayMaxAddrY = m_pGenDlg->m_DisplayMaxAddrY;
        m_pCopyItem->m_DisplayMinAddrY = m_pGenDlg->m_DisplayMinAddrY;
        m_pCopyItem->m_nDisplayMinY   = m_pGenDlg->m_nDisplayMinY;	//显示最小值
        m_pCopyItem->m_nDisplayMaxY   = m_pGenDlg->m_nDisplayMaxY;	//显示最大值
        m_pCopyItem->m_bConstY        = m_pGenDlg->m_bConstY;//是否常量范围
        m_pCopyItem->m_SourceMaxAddrY = m_pGenDlg->m_SourceMaxAddrY;//源范围最大值 地址
        m_pCopyItem->m_SourceMinAddrY = m_pGenDlg->m_SourceMinAddrY;//源范围最小值 地址
        m_pCopyItem->m_nSourceMaxY    = m_pGenDlg->m_nSourceMaxY;	//源范围最大值
        m_pCopyItem->m_nSourceMinY    = m_pGenDlg->m_nSourceMinY;	//源范围最小值

        m_pCopyItem->m_vecChannels   = m_pGenDlg->m_vecChannels;//各个通道曲线外观设置
    }
    else
        return;
    //曲线显示区设置
    m_pCopyItem->m_bSelectVertMinor  = m_pTrendDisplay->m_bSelectVertMinor;  //是否显示垂直次标尺
    m_pCopyItem->m_bSelectHorMinor   = m_pTrendDisplay->m_bSelectHorMinor;   //是否显示水平次标尺
    m_pCopyItem->m_bMainHor          = m_pTrendDisplay->m_bMainHor;
    m_pCopyItem->m_bMainVer          = m_pTrendDisplay->m_bMainVer;
    m_pCopyItem->m_TextColor         = m_pTrendDisplay->m_textColor;
    m_pCopyItem->m_textSize          = m_pTrendDisplay->textSize();
    m_pCopyItem->m_nVertMajorScale   = m_pTrendDisplay->m_nVertMajorScale;   //垂直主标尺
    m_pCopyItem->m_nVertMinorScale   = m_pTrendDisplay->m_nVertMinorScale;   //垂直次标尺
    m_pCopyItem->m_nHorMajorScale    = m_pTrendDisplay->m_nHorMajorScale;    //水平主标尺
    m_pCopyItem->m_nHorMinorScale    = m_pTrendDisplay->m_nHorMinorScale;    //水平次标尺

    //曲线颜色设置
    m_pCopyItem->m_bGrade      = m_pTrendDisplay->m_bGrade;       //是否需要网格
    m_pCopyItem->m_nVerColor   = m_pTrendDisplay->m_nVerColor;    //垂直网格颜色
    m_pCopyItem->m_nHorColor   = m_pTrendDisplay->m_nHorColor;    //水平网格颜色
    m_pCopyItem->m_nBoradColor = m_pTrendDisplay->m_nBoradColor;	//边框颜色
    m_pCopyItem->m_nScaleColor = m_pTrendDisplay->m_nScaleColor;	//标尺颜色
    m_pCopyItem->m_nGraphColor = m_pTrendDisplay->m_nGraphColor;	//图表区颜色
    m_pCopyItem->m_alpha       = m_pTrendDisplay->getAlpha();	//图表区透明度
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

    if(pSecurityWight && pSecurityWight->Save())
    {
        m_pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    }
    else
        return;

    QDrawGraphics *pDraw = new QDrawGraphics;
    pDraw->OnDrawXYTrend(m_pCopyItem);  //加载图形
    if(pDraw)
    {
        delete pDraw;
        pDraw = NULL;
    }

    QDialog::accept();
}

void XYTrendDlg::on_cancel_clicked()
{
    reject();
}

void XYTrendDlg::on_help_clicked()
{

}
