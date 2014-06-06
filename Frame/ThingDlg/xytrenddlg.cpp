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

    ui->tabWidget->addTab(m_pGenDlg, tr("ͨ������"));
    ui->tabWidget->addTab(m_pTrendDisplay, tr("��ʾ����"));

    pSecurityWight = new SecurityWidget(this);
    ui->tabWidget->addTab(pSecurityWight, tr("Ȩ������"));
    //pSecurityWight->ui->groupBox_Touch->hide();
    pSecurityWight->setTouchGroupEnabled(false);

    this->setWindowTitle(tr("X-Y����"));

    ui->label_ctlType->setText(tr("����:X-Y����"));
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
        m_pCopyItem->chlCount        = m_pGenDlg->chlCount;//ͨ������
        m_pCopyItem->addrLength      = m_pGenDlg->addrLength;//��ַ���ȣ��൱�ڲ�������
        m_pCopyItem->m_dataType      = m_pGenDlg->m_dataType;//��������
        m_pCopyItem->m_TriggerAddr   = m_pGenDlg->m_TriggerAddr;//������ַ
        m_pCopyItem->m_bReset        = m_pGenDlg->m_bReset;//�Ƿ��Զ���λ

        m_pCopyItem->m_bScale        = m_pGenDlg->m_bScale;//�Ƿ�����

        m_pCopyItem->m_bDisplayConst   = m_pGenDlg->m_bDisplayConst;	//�Ƿ�����Χ
        m_pCopyItem->m_DisplayMaxAddrX = m_pGenDlg->m_DisplayMaxAddrX;
        m_pCopyItem->m_DisplayMinAddrX = m_pGenDlg->m_DisplayMinAddrX;
        m_pCopyItem->m_nDisplayMinX   = m_pGenDlg->m_nDisplayMinX;	//��ʾ��Сֵ
        m_pCopyItem->m_nDisplayMaxX   = m_pGenDlg->m_nDisplayMaxX;	//��ʾ���ֵ
        m_pCopyItem->m_bConstX        = m_pGenDlg->m_bConstX;//�Ƿ�����Χ
        m_pCopyItem->m_SourceMaxAddrX = m_pGenDlg->m_SourceMaxAddrX;//Դ��Χ���ֵ ��ַ
        m_pCopyItem->m_SourceMinAddrX = m_pGenDlg->m_SourceMinAddrX;//Դ��Χ��Сֵ ��ַ
        m_pCopyItem->m_nSourceMaxX    = m_pGenDlg->m_nSourceMaxX;	//Դ��Χ���ֵ
        m_pCopyItem->m_nSourceMinX    = m_pGenDlg->m_nSourceMinX;	//Դ��Χ��Сֵ

        m_pCopyItem->m_bDisplayConstY   = m_pGenDlg->m_bDisplayConstY;	//�Ƿ�����Χ
        m_pCopyItem->m_DisplayMaxAddrY = m_pGenDlg->m_DisplayMaxAddrY;
        m_pCopyItem->m_DisplayMinAddrY = m_pGenDlg->m_DisplayMinAddrY;
        m_pCopyItem->m_nDisplayMinY   = m_pGenDlg->m_nDisplayMinY;	//��ʾ��Сֵ
        m_pCopyItem->m_nDisplayMaxY   = m_pGenDlg->m_nDisplayMaxY;	//��ʾ���ֵ
        m_pCopyItem->m_bConstY        = m_pGenDlg->m_bConstY;//�Ƿ�����Χ
        m_pCopyItem->m_SourceMaxAddrY = m_pGenDlg->m_SourceMaxAddrY;//Դ��Χ���ֵ ��ַ
        m_pCopyItem->m_SourceMinAddrY = m_pGenDlg->m_SourceMinAddrY;//Դ��Χ��Сֵ ��ַ
        m_pCopyItem->m_nSourceMaxY    = m_pGenDlg->m_nSourceMaxY;	//Դ��Χ���ֵ
        m_pCopyItem->m_nSourceMinY    = m_pGenDlg->m_nSourceMinY;	//Դ��Χ��Сֵ

        m_pCopyItem->m_vecChannels   = m_pGenDlg->m_vecChannels;//����ͨ�������������
    }
    else
        return;
    //������ʾ������
    m_pCopyItem->m_bSelectVertMinor  = m_pTrendDisplay->m_bSelectVertMinor;  //�Ƿ���ʾ��ֱ�α��
    m_pCopyItem->m_bSelectHorMinor   = m_pTrendDisplay->m_bSelectHorMinor;   //�Ƿ���ʾˮƽ�α��
    m_pCopyItem->m_bMainHor          = m_pTrendDisplay->m_bMainHor;
    m_pCopyItem->m_bMainVer          = m_pTrendDisplay->m_bMainVer;
    m_pCopyItem->m_TextColor         = m_pTrendDisplay->m_textColor;
    m_pCopyItem->m_textSize          = m_pTrendDisplay->textSize();
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

    if(pSecurityWight && pSecurityWight->Save())
    {
        m_pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    }
    else
        return;

    QDrawGraphics *pDraw = new QDrawGraphics;
    pDraw->OnDrawXYTrend(m_pCopyItem);  //����ͼ��
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
