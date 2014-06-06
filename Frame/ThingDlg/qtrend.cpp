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

    m_pCopyItem = NULL;//�����������ṹ��

    m_pTrendAppearDlg   = new QTrendAppearance;
    m_pTrendDisplay     = new QTrendadisplay;
    //m_pTrendColor       = new QTrendaColor;
    m_pTrendTime        = new QTrendaTime;

    ui->tabWidget->addTab(m_pTrendAppearDlg, tr("�����������"));
    ui->tabWidget->addTab(m_pTrendDisplay, tr("������ʾ������"));
    //ui->tabWidget->addTab(m_pTrendColor, tr("������ɫ����"));
    ui->tabWidget->addTab(m_pTrendTime, tr("����ʱ������"));

    pSecurityWight = new SecurityWidget(this);
    ui->tabWidget->addTab(pSecurityWight, tr("Ȩ������"));
    //pSecurityWight->ui->groupBox_Touch->hide();
    pSecurityWight->setTouchGroupEnabled(false);

    this->setWindowTitle(tr("����ͼ"));

    ui->label_ctlType->setText(tr("����:����ͼ"));
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
        if(!pwnd->IsAddressCheckRight(m_pTrendTime->m_kbFrom, tr("��ʼ��ַ"), m_pTrendTime->ui->lineEdit_from, 1))
        {
            m_pTrendTime->ui->lineEdit_from->setFocus();
            return ;
        }

        if(!pwnd->IsAddressCheckRight(m_pTrendTime->m_kbTo, tr("��ʼ��ַ"), m_pTrendTime->ui->lineEdit_to, 1))
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
            QMessageBox box(QMessageBox::Warning,tr("����"),tr("�������ʼʱ�䲻�ܴ��ڻ��ߵ��ڽ���ʱ�䣡"),QMessageBox::NoButton,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
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

    //����������öԻ���
    if(m_pTrendAppearDlg && m_pTrendAppearDlg->save())
    {
        m_pCopyItem->m_bIsAll       = m_pTrendAppearDlg->m_bIsAll;
        m_pCopyItem->m_nDisplayMax  = m_pTrendAppearDlg->getDisplayMax();
        m_pCopyItem->m_nDisplayMin  = m_pTrendAppearDlg->getDisplayMin();
        m_pCopyItem->m_eTableType   = m_pTrendAppearDlg->m_eTableType;
        m_pCopyItem->m_sGroupNum    = m_pTrendAppearDlg->m_sGroupNum;
        m_pCopyItem->m_nCurChnnelNum= m_pTrendAppearDlg->m_nCurChnnelNum;//��ǰͨ����
        m_pCopyItem->m_nChnnelBegin = m_pTrendAppearDlg->m_nChnnelBegin;//��ʼͨ����

        m_pCopyItem->m_vecChannelGroups.clear();

        m_pCopyItem->m_vecChannelGroups = m_pTrendAppearDlg->m_vecChannelGroups;
        m_pCopyItem->m_nTotalTrendNumber = m_pTrendAppearDlg->m_vecChannelGroups.size();//��ͨ����
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

    //������ʾ������
    m_pCopyItem->m_bSelectVertMinor  = m_pTrendDisplay->m_bSelectVertMinor;  //�Ƿ���ʾ��ֱ�α��
    m_pCopyItem->m_bSelectHorMinor   = m_pTrendDisplay->m_bSelectHorMinor;   //�Ƿ���ʾˮƽ�α��
    m_pCopyItem->m_bMainHor          = m_pTrendDisplay->m_bMainHor;
    m_pCopyItem->m_bMainVer          = m_pTrendDisplay->m_bMainVer;
    m_pCopyItem->m_nDataSample       = m_pTrendDisplay->m_nDataSample;       //����������
    if(m_pTrendDisplay->m_nScrollSample >m_pTrendDisplay->m_nDataSample)
    {
        m_pCopyItem->m_nScrollSample = m_pTrendDisplay->m_nDataSample;
    }
    else
        m_pCopyItem->m_nScrollSample     = m_pTrendDisplay->m_nScrollSample;     //����������

    m_pCopyItem->m_nVertMajorScale   = m_pTrendDisplay->m_nVertMajorScale;   //��ֱ�����
    m_pCopyItem->m_nVertMinorScale   = m_pTrendDisplay->m_nVertMinorScale;   //��ֱ�α��
    m_pCopyItem->m_nHorMajorScale    = m_pTrendDisplay->m_nHorMajorScale;    //ˮƽ�����
    m_pCopyItem->m_nHorMinorScale    = m_pTrendDisplay->m_nHorMinorScale;    //ˮƽ�α��

    //������ɫ����
    m_pCopyItem->m_bGrade      = m_pTrendDisplay->m_bGrade;       //�Ƿ���Ҫ����
    m_pCopyItem->m_nVerColor   = m_pTrendDisplay->m_nVerColor;    //��ֱ������ɫ
    m_pCopyItem->m_nHorColor   = m_pTrendDisplay->m_nHorColor;    //ˮƽ������ɫ
    m_pCopyItem->m_nBoradColor = m_pTrendDisplay->m_nBoradColor;	//�߿���ɫ
    m_pCopyItem->m_nScaleColor = m_pTrendDisplay->m_nScaleColor;	//�����ɫ
    m_pCopyItem->m_nGraphColor = m_pTrendDisplay->m_nGraphColor;	//ͼ������ɫ
    m_pCopyItem->m_alpha       = m_pTrendDisplay->getAlpha();	//ͼ����͸����
                         
    //����ʱ������
    m_pCopyItem->m_eTimeFormat  = m_pTrendTime->m_eTimeFormat;  //���ڸ�ʽ
    m_pCopyItem->m_eDateFormat  = m_pTrendTime->m_eDateFormat;  //���ڸ�ʽ
    m_pCopyItem->m_eFontType    = m_pTrendTime->m_eFontType;    //��������
    m_pCopyItem->m_eTxtAttr     = m_pTrendTime->m_eTxtAttr;     //�ı�����
    m_pCopyItem->m_eStart       = m_pTrendTime->m_eStart;       //����ʱ��ɼ���ʽ
    m_pCopyItem->m_bXMarked     = m_pTrendTime->m_bXMarked;     //�Ƿ�X���ע
    m_pCopyItem->m_nFontSize    = m_pTrendTime->m_nFontSize;    //�����С
    m_pCopyItem->m_nMarkedColor = m_pTrendTime->m_nMarkedColor; //��ע��ɫ
    m_pCopyItem->m_nTimeLen     = m_pTrendTime->getTime_near();     //���ʱ��
    m_pCopyItem->m_eTimeUnitNear= m_pTrendTime->m_eTimeUnitNear;//���ʱ�䵥λ
    m_pCopyItem->m_dFromDate    = m_pTrendTime->m_dFromDate;    //��ʼ����
    m_pCopyItem->m_tFromTime    = m_pTrendTime->m_tFromTime;    //��ʼʱ��
    m_pCopyItem->m_dToDate      = m_pTrendTime->m_dToDate;      //��ֹ����
    m_pCopyItem->m_tToTime      = m_pTrendTime->m_tToTime;      //��ֹʱ��
    m_pCopyItem->m_kbFrom       = m_pTrendTime->m_kbFrom;
    m_pCopyItem->m_kbTo         = m_pTrendTime->m_kbTo;
    m_pCopyItem->m_bDateFormat  = m_pTrendTime->m_bDateFormat;
    m_pCopyItem->m_bTimeFormat  = m_pTrendTime->m_bTimeFormat;
    m_pCopyItem->setId(ui->spinBox->value());

    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID�ظ������޸�ID��"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return ;
    }

    QDrawGraphics *pDraw = new QDrawGraphics;
    pDraw->OnDrawTrendChart(m_pCopyItem);  //����ͼ��
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


