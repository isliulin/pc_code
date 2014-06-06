#include "qtrend.h"
#include "ui_qtrend.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

QTrend::QTrend(QTrendAttr *pItem, QWidget *parent):QDialog(parent),ui(new Ui::QTrend)
{
    ui->setupUi(this);

    oId = -1;
    this->setFixedSize(this->size());
    //setWindowOpacity(0.95);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);

    m_pCopyItem = NULL;//拷贝的整个结构体

    m_pTrendAppearDlg   = new QTrendAppearance;
    m_pTrendDisplay     = new QTrendadisplay;
    //m_pTrendColor       = new QTrendaColor;
    m_pTrendTime        = new QTrendaTime;

    ui->tabWidget->addTab(m_pTrendAppearDlg, tr("曲线外观设置"));
    ui->tabWidget->addTab(m_pTrendDisplay, tr("曲线显示区设置"));
    //ui->tabWidget->addTab(m_pTrendColor, tr("曲线颜色设置"));
    ui->tabWidget->addTab(m_pTrendTime, tr("曲线时间设置"));

    pSecurityWight = new SecurityWidget(this);
    ui->tabWidget->addTab(pSecurityWight, tr("权限设置"));
    //pSecurityWight->ui->groupBox_Touch->hide();
    pSecurityWight->setTouchGroupEnabled(false);

    this->setWindowTitle(tr("趋势图"));

    ui->label_ctlType->setText(tr("曲线:趋势图"));
    ui->graphicsView->setScene(&scene);
    QPixmap pic(":/standardtool/images/trend.png");
    scene.addPixmap(pic.scaled(110,110));

    //connect(m_pTrendAppearDlg, SIGNAL(ChnnelChange(int, int)), m_pTrendDisplay, SLOT(set_comboBox_chnnel_num(int, int)));
    //connect(m_pTrendAppearDlg, SIGNAL(ChnnelChange(int, int)), m_pTrendColor, SLOT(set_comboBox_chnnel_num(int, int)));
    connect(m_pTrendAppearDlg, SIGNAL(TrendTypeChange(bool)), m_pTrendTime, SLOT(setTrendType(bool)));

    InitAllProperty(pItem);
}

QTrend::~QTrend()
{
    if(m_pTrendAppearDlg)
    {
        delete m_pTrendAppearDlg;
        m_pTrendAppearDlg = NULL;
    }

    if(m_pTrendDisplay)
    {
        delete m_pTrendDisplay;
        m_pTrendDisplay = NULL;
    }

    if(m_pTrendTime)
    {
        delete m_pTrendTime;
        m_pTrendTime = NULL;
    }

    if(m_pCopyItem)
    {
        delete m_pCopyItem;
        m_pCopyItem = NULL;
    }

    if(pSecurityWight)
    {
        delete pSecurityWight;
        pSecurityWight = NULL;
    }

    delete ui;
}

void QTrend::InitAllProperty(QTrendAttr *pItem)
{
    if (pItem)
    {
        oId = pItem->id();
        ui->spinBox->setValue(oId);
        qDebug() << "m_pTrendAppearDlg->Init(pItem)";
        m_pTrendAppearDlg->Init(pItem);
        qDebug() << "m_pTrendDisplay->Init(pItem)";
        m_pTrendDisplay->Init(pItem);
        qDebug() << "m_pTrendTime->Init(pItem)";
        //m_pTrendColor->Init(pItem);
        m_pTrendTime->Init(pItem);
        qDebug() << "m_pTrendTime->Init(pItem) end";
        pSecurityWight->init(pItem);

    }
    else
    {
        m_pTrendAppearDlg->Init(NULL);
        m_pTrendDisplay->Init(NULL);
        //m_pTrendColor->Init(NULL);
        m_pTrendTime->Init(NULL);
        pSecurityWight->init(NULL);
        ui->spinBox->setValue(pwnd->getNewId());
    }
}

void QTrend::on_accept_clicked()
{
    if(m_pTrendTime->m_eStart == START_ADDR)
    {
        if(!pwnd->IsAddressCheckRight(m_pTrendTime->m_kbFrom, tr("起始地址"), m_pTrendTime->ui->lineEdit_from, 1))
        {
            m_pTrendTime->ui->lineEdit_from->setFocus();
            return ;
        }

        if(!pwnd->IsAddressCheckRight(m_pTrendTime->m_kbTo, tr("起始地址"), m_pTrendTime->ui->lineEdit_to, 1))
        {
            m_pTrendTime->ui->lineEdit_to->setFocus();
            return ;
        }
    }
    else if(m_pTrendTime->m_eStart == START_FROMTO)
    {
        bool bTrueTime = true;
        if(m_pTrendTime->m_dFromDate > m_pTrendTime->m_dToDate)
        {
            bTrueTime = false;
        }
        else if( (m_pTrendTime->m_dFromDate == m_pTrendTime->m_dToDate) &&
                 (m_pTrendTime->m_tFromTime >= m_pTrendTime->m_tToTime))
        {
            bTrueTime = false;
        }
        if(bTrueTime == false)
        {
            QMessageBox box(QMessageBox::Warning,tr("警告"),tr("输入的起始时间不能大于或者等于结束时间！"),QMessageBox::NoButton,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
            box.exec();
            m_pTrendTime->ui->dateEdit->setFocus();
            return ;
        }
    }

    m_pCopyItem = new QTrendAttr;
    if(pSecurityWight && pSecurityWight->Save())
    {
        m_pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    }
    else
        return;

    //曲线外观设置对话框
    if(m_pTrendAppearDlg && m_pTrendAppearDlg->save())
    {
        m_pCopyItem->m_bIsAll       = m_pTrendAppearDlg->m_bIsAll;
        m_pCopyItem->m_nDisplayMax  = m_pTrendAppearDlg->getDisplayMax();
        m_pCopyItem->m_nDisplayMin  = m_pTrendAppearDlg->getDisplayMin();
        m_pCopyItem->m_eTableType   = m_pTrendAppearDlg->m_eTableType;
        m_pCopyItem->m_sGroupNum    = m_pTrendAppearDlg->m_sGroupNum;
        m_pCopyItem->m_nCurChnnelNum= m_pTrendAppearDlg->m_nCurChnnelNum;//当前通道号
        m_pCopyItem->m_nChnnelBegin = m_pTrendAppearDlg->m_nChnnelBegin;//起始通道号

        m_pCopyItem->m_vecChannelGroups.clear();

        m_pCopyItem->m_vecChannelGroups = m_pTrendAppearDlg->m_vecChannelGroups;
        m_pCopyItem->m_nTotalTrendNumber = m_pTrendAppearDlg->m_vecChannelGroups.size();//总通道数
    }
    else
    {
        return;
    }
    //ChannelGroupInfo info_1;
    //for(int i = 0; i < m_pTrendAppearDlg->m_vecChannelGroups.size(); i++)
    //{
        //info_1.m_eDataType    = m_pTrendAppearDlg->m_vecChannelGroups.at(i);
       
        //m_pCopyItem->m_vecChannelGroups.push_back(info_1);
    //}

    //曲线显示区设置
    m_pCopyItem->m_bSelectVertMinor  = m_pTrendDisplay->m_bSelectVertMinor;  //是否显示垂直次标尺
    m_pCopyItem->m_bSelectHorMinor   = m_pTrendDisplay->m_bSelectHorMinor;   //是否显示水平次标尺
    m_pCopyItem->m_bMainHor          = m_pTrendDisplay->m_bMainHor;
    m_pCopyItem->m_bMainVer          = m_pTrendDisplay->m_bMainVer;
    m_pCopyItem->m_nDataSample       = m_pTrendDisplay->m_nDataSample;       //数据样本数
    if(m_pTrendDisplay->m_nScrollSample >m_pTrendDisplay->m_nDataSample)
    {
        m_pCopyItem->m_nScrollSample = m_pTrendDisplay->m_nDataSample;
    }
    else
        m_pCopyItem->m_nScrollSample     = m_pTrendDisplay->m_nScrollSample;     //滚动样本数

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
                         
    //曲线时间设置
    m_pCopyItem->m_eTimeFormat  = m_pTrendTime->m_eTimeFormat;  //日期格式
    m_pCopyItem->m_eDateFormat  = m_pTrendTime->m_eDateFormat;  //日期格式
    m_pCopyItem->m_eFontType    = m_pTrendTime->m_eFontType;    //字体类型
    m_pCopyItem->m_eTxtAttr     = m_pTrendTime->m_eTxtAttr;     //文本属性
    m_pCopyItem->m_eStart       = m_pTrendTime->m_eStart;       //那种时间采集方式
    m_pCopyItem->m_bXMarked     = m_pTrendTime->m_bXMarked;     //是否X轴标注
    m_pCopyItem->m_nFontSize    = m_pTrendTime->m_nFontSize;    //字体大小
    m_pCopyItem->m_nMarkedColor = m_pTrendTime->m_nMarkedColor; //标注颜色
    m_pCopyItem->m_nTimeLen     = m_pTrendTime->getTime_near();     //最近时间
    m_pCopyItem->m_eTimeUnitNear= m_pTrendTime->m_eTimeUnitNear;//最近时间单位
    m_pCopyItem->m_dFromDate    = m_pTrendTime->m_dFromDate;    //起始日期
    m_pCopyItem->m_tFromTime    = m_pTrendTime->m_tFromTime;    //起始时间
    m_pCopyItem->m_dToDate      = m_pTrendTime->m_dToDate;      //终止日期
    m_pCopyItem->m_tToTime      = m_pTrendTime->m_tToTime;      //终止时间
    m_pCopyItem->m_kbFrom       = m_pTrendTime->m_kbFrom;
    m_pCopyItem->m_kbTo         = m_pTrendTime->m_kbTo;
    m_pCopyItem->m_bDateFormat  = m_pTrendTime->m_bDateFormat;
    m_pCopyItem->m_bTimeFormat  = m_pTrendTime->m_bTimeFormat;
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
    pDraw->OnDrawTrendChart(m_pCopyItem);  //加载图形
    if(pDraw)
    {
        delete pDraw;
        pDraw = NULL;
    }

    QDialog::accept();
}

void QTrend::on_cancel_clicked()
{
    this->close();
}

void QTrend::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_TREND);
}


