#include "qchartdlg.h"
#include "ui_qchartdlg.h"

extern MainWindow *pwnd;

QChartDlg::QChartDlg(QGraphicsItem *pItem, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QChartDlg)
{

    //����ͼ��ֻ������ͨͼ����������󣺻�������ɫ�����
    qcommonbase = new QChartCommon;     //��ͨ-����
    qcommoncolor = new QChartCmColor;   //��ͨ-��ɫ
    qcommonruler = new QChartCMRuler;   //��ͨ-���

    //����ͼ�����Ǳ���������󣺻�������ɫ
    qmeterbase = new QChartMeter;
    qmetercolor = new QChartMeColor;
    qmeteruler = new QchartMeRuler;

    //����tabҳ���󣬼����ֹ�����
    tabWidget = new QTabWidget(this);

    oId = -1;
    pSecurityWight = new SecurityWidget;
    pSecurityWight->setTouchGroupEnabled(false);

    //�������tabҳ��
    tabWidget->addTab(qcommonbase,tr("����"));
    tabWidget->addTab(qcommoncolor,tr("����"));
    tabWidget->addTab(qcommonruler,tr("�̶�"));
    tabWidget->addTab(pSecurityWight,tr("Ȩ������"));

    tabWidget->setGeometry(QRect(148, 10, 610,480));

    connect(qcommonbase, SIGNAL(meterclick()),this, SLOT(reload_tabwidget()));//��ͨ�л����Ǳ�
    connect(qmeterbase, SIGNAL(commonclick()),this, SLOT(reload_common()));//�Ǳ��л�����ͨ
    connect(qmeterbase, SIGNAL(onGetShowValue(bool &)),qmeteruler, SLOT(onGetShowValue(bool &)));//�Ǳ��ȡ�Ƿ���ʾ�̶�ֵ����
    connect(qcommonbase, SIGNAL(directionchange()),this, SLOT(change_direction()));//�Ǳ��л�����ͨ
    connect(qmetercolor, SIGNAL(SetMeterPointColor()),this, SLOT(setMeterPointColor()));//
    connect(qmetercolor, SIGNAL(SetMeterBackColor()),this, SLOT(setMeterBackColor()));//
    connect(qmetercolor, SIGNAL(reDrawMeter()),this, SLOT(reDrawMeter()));//�ػ��Ǳ�

    connect(qcommonbase, SIGNAL(setCommonShapeType()),this, SLOT(setCommonShapeType()));//��ͨͼ�����ı���Ϣ����
    connect(qcommonbase, SIGNAL(drawCenterCircle(bool, int)),qcommoncolor, SLOT(drawCenterCircle(bool, int)));//��ͨͼ�����ı���Ϣ����
    connect(qcommonruler, SIGNAL(scalechange()),this, SLOT(setCommonScaleColor()));//��ͨͼ�����ı���Ϣ����

    connect(qmeteruler, SIGNAL(scalechange()),this, SLOT(setMeterScaleColor()));//�Ǳ�ͼ�����ı���Ϣ����

    connect(qcommoncolor, SIGNAL(onGetDirection(int &)),qcommonbase, SLOT(onGetDirection(int &)));//��ͨͼ�����ı���Ϣ����
    connect(qcommoncolor, SIGNAL(onGetPointType(int &)),qcommonbase, SLOT(onGetPointType(int &)));//��ͨͼ�����ı���Ϣ����
    connect(qcommoncolor, SIGNAL(onGetStartAngle(short &,short&)),qcommonbase, SLOT(onGetStartAngle(short &,short&)));//Բ��ͼ��ȡ��ʼ�Ƕ�

    connect(qcommoncolor, SIGNAL(onGetCircleAlpha(short&)), qcommonbase, SLOT(onGetCircleAlpha(short&)));
    connect(qcommoncolor, SIGNAL(onGetShowFrame(bool&)), qcommonbase, SLOT(onGetShowFrame(bool&)));

    connect(qcommonbase, SIGNAL(setRange(double, double, int)),qcommoncolor, SLOT(setdataRange(double, double,int)));
    connect(qmeterbase, SIGNAL(onGetPointType(int &)),qmetercolor, SLOT(onGetPointType(int &)));
    connect(qcommoncolor, SIGNAL(onGetdataRange(double &, double &)),qcommonbase, SLOT(onGetdataRange(double &, double &)));
    connect(qcommoncolor, SIGNAL(onGetShowValue(bool &)),qcommonruler, SLOT(onGetShowValue(bool &)));
    connect(qcommonbase, SIGNAL(reDrawBar()),qcommoncolor, SLOT(reDrawBar()));
    connect(qcommoncolor, SIGNAL(onGetroleCheck(bool &, int &)),qcommonbase, SLOT(onGetroleCheck(bool &, int &)));
    connect(qmeterbase, SIGNAL(setRange(double, double, int)),qmetercolor, SLOT(setdataRange(double, double,int)));
    connect(qcommonbase, SIGNAL(enablePointType(bool)),qcommoncolor, SLOT(enablePointType(bool)));

    ui->setupUi(this);
    this->setFixedSize(783,533);
    ui->m_Titellabel->setText(tr("ͼ��/��ͨͼ��"));
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    this->ui->MainView->setScene(qcommoncolor->pScene);//������ͨͼ�εĳ���

    connect(ui->m_cancelBtn, SIGNAL(clicked()), this, SLOT(cancelButton()));
    connect(ui->m_helpBtn, SIGNAL(clicked()), this, SLOT(loadHelp()));
    connect(ui->m_okBtn, SIGNAL(clicked()), this, SLOT(confyButton()));

    enGrahpType = ENCOMMON_TYPE; //Ĭ����ͨ

    if(pItem)
    {
        pCopyItem= dynamic_cast<ChartItem *> (pItem)->Clone();
        InitAllProperty(dynamic_cast<ChartItem *> (pCopyItem));
    }
    else
    {
        InitAllProperty(NULL);
    }
    ui->m_okBtn->setFocus();
}

QChartDlg::~QChartDlg()
{
    if (qcommonbase)
    {
        delete qcommonbase;
        qcommonbase = NULL;
    }

    if (qcommoncolor)
    {
        delete qcommoncolor;
        qcommoncolor = NULL;
    }

    if (qcommonruler)
    {
        delete qcommonruler;
        qcommonruler = NULL;
    }

    if (qmeterbase)
    {
        delete qmeterbase;
        qmeterbase = NULL;
    }

    if (qmetercolor)
    {
        delete qmetercolor;
        qmetercolor = NULL;
    }

    if (qmeteruler)
    {
        delete qmeteruler;
        qmeteruler = NULL;
    }

    if (tabWidget)
    {
        delete tabWidget;
        tabWidget = NULL;
    }

    delete ui;
}

void QChartDlg::InitAllProperty(ChartItem *pItem)
{
    if (pItem)//��һ�����е�λ��ť
    {
        oId = pItem->id();
        ui->spinBox->setValue(oId);

        pSecurityWight->init(pItem);
        if(ENMETER_TYPE == pItem->m_eGraphType)
        {
            //��ʼ���Ǳ��������ǩҳ��������ɫ
            qmetercolor->Init(pItem);
            qmeteruler->Init(pItem);
            qmeterbase->Init(pItem);
            reload_tabwidget();

            //��ʼ����״ͼ�Ļ�������ɫ�����ҳ��
            qcommonruler->Init(NULL);
            qcommonbase->Init(NULL);
            qcommoncolor->Init(NULL);
        }
        else if(ENCOMMON_TYPE == pItem->m_eGraphType)
        {
            qcommonbase->Init(pItem);
            qcommonruler->Init(pItem);
            qcommoncolor->Init(pItem);
            reload_common();

            //��ʼ���Ǳ��������ǩҳ��������ɫ
            qmeterbase->Init(NULL);
            qmetercolor->Init(NULL);
            qmeteruler->Init(NULL);
        }

    }
    else//�½�
    {
        //��ʼ����״ͼ�Ļ�������ɫ�����ҳ��
        qcommonbase->Init(NULL);
        qcommonruler->Init(NULL);
        qcommoncolor->Init(NULL);

        //��ʼ���Ǳ��������ǩҳ��������ɫ
        qmeterbase->Init(NULL);
        qmetercolor->Init(NULL);
        qmeteruler->Init(NULL);
        ui->spinBox->setValue(pwnd->getNewId());
    }
}

void QChartDlg::reload_tabwidget()
{
    if(NULL == tabWidget)
    {
        return;
    }
    ui->m_Titellabel->setText(tr("ͼ��/�Ǳ�ͼ��"));
    enGrahpType = ENMETER_TYPE;//��ǵ�ǰѡ��Ϊ�Ǳ�
    tabWidget->clear();
    tabWidget->addTab(qmeterbase,tr("����"));
    tabWidget->addTab(qmetercolor,tr("����"));
    tabWidget->addTab(qmeteruler,tr("�̶�"));
    tabWidget->addTab(pSecurityWight,tr("Ȩ������"));

    this->ui->MainView->setScene(qmeterbase->pScene);

    this->update();
}

void QChartDlg::reload_common()
{
    if(NULL == tabWidget)
    {
        return;
    }
    ui->m_Titellabel->setText(tr("ͼ��/��ͨͼ��"));
    enGrahpType = ENCOMMON_TYPE;
    tabWidget->clear();

    tabWidget->addTab(qcommonbase,tr("����"));
    tabWidget->addTab(qcommoncolor,tr("����"));
    tabWidget->addTab(qcommonruler,tr("�̶�"));
    tabWidget->addTab(pSecurityWight,tr("Ȩ������"));

    this->ui->MainView->setScene(qcommoncolor->pScene);//�����Ǳ�ĳ���
    this->update();
}


void QChartDlg::change_direction()
{
    int nDirectionType = qcommonbase->ndirection;
    qcommoncolor->changeDirection(nDirectionType);
}

void QChartDlg::setMeterPointColor()
{
    qmeterbase->sPointColor = qmetercolor->nPointColor;
    qmeterbase->meter.sPointColor = qmetercolor->nPointColor;
    qmeterbase->meter.nMainScal = qmeteruler->onGetMainScale();
    qmeterbase->meter.nSubScal = qmeteruler->onGetSubScale();
    qmeterbase->meter.sCaleColor = qmeteruler->onGetScaleColor();
    qmeterbase->meter.sBackColor = qmetercolor->nBackColor;
    qmeterbase->OnReDrawMeter();
    //qmeterbase->pBaseItem->SetPropertyValue("Pointer.LineColor",QVariant(qmeterbase->sPointColor));//����ָ����ɫ
}

void QChartDlg::setMeterBackColor()
{
    qmeterbase->sBackColor = qmetercolor->nBackColor;
    qmeterbase->meter.sBackColor = qmetercolor->nBackColor;
    qmeterbase->OnReDrawMeter();
}

void QChartDlg::cancelButton()
{
    reject();
}

void QChartDlg::confyButton()
{
    //��������ҳ������
    if(!pSecurityWight->Save())
    {
        return;
    }
    if(ENMETER_TYPE == enGrahpType)//��ǰѡ�����Ǳ�ͼ��
    {
        //pwnd->nPcopyItenType = 1;//�Ǳ�
        qmeterbase->pOldItem->m_eGraphType = ENMETER_TYPE;
        pCopyItem = qmeterbase->pOldItem;
        //�����Ǳ���Ϣ��datalist��
        if(!(qmeterbase->MeterGenSave(meter_st)))
        {
            return;
        }
        if(!qmetercolor->MeterColorSave(meter_st))
        {
            return;
        }
        qmeteruler->MeterGenSave(meter_st);
        //onSaveItemPosition();
        if(meter_st.eDataType >= 2)
        {
            meter_st.addr.Length = 2;
            meter_st.addrSourceMin.Length = 2;
            meter_st.addrSourceMax.Length = 2;
            meter_st.sAlarm.nMaxaddr.Length = 2;
            meter_st.sAlarm.nMinaddr.Length = 2;
        }
        qmeterbase->pOldItem->onSaveMeter(meter_st);
    }
    else
    {
        qcommoncolor->pCommonItem->m_eGraphType = ENCOMMON_TYPE;
        pCopyItem = qcommoncolor->pCopyItem;
        if(!(qcommonbase->CommonGenSave(common_st)))
        {
            return;
        }
        if(!qcommoncolor->CommonGenSave(common_st))
        {
            return;
        }
        qcommonruler->CommonGenSave(common_st);
        if(common_st.eDataType >= 2)
        {
            common_st.addr.Length = 2;
            common_st.addrSourceMin.Length = 2;
            common_st.addrSourceMax.Length = 2;
            common_st.sAlarm.nMaxaddr.Length = 2;
            common_st.sAlarm.nMinaddr.Length = 2;
        }
        qcommoncolor->pCommonItem->onSaveCommon(common_st);
    }
    ChartItem *pItem = dynamic_cast<ChartItem *> (pCopyItem);
    if(pItem)
    {
        pItem->SaveSecurityPro(&(pSecurityWight->sproperty));
        pItem->setId(ui->spinBox->value());
    }
    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID�ظ������޸�ID��"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return ;
    }

    accept();
}
void QChartDlg::reDrawMeter()
{
    qmeterbase->meter.nMeterType = qmetercolor->nMeterType;
    qmeterbase->meter.shapeName = qmetercolor->onGetShapeName();
    qmeterbase->meter.sCaleColor = qmeteruler->onGetScaleColor();
    qmeterbase->meter.nMainScal = qmeteruler->onGetMainScale();
    qmeterbase->meter.nSubScal = qmeteruler->onGetSubScale();
    qmeterbase->meter.sPointColor = qmetercolor->nPointColor;
    switch(qmeterbase->meter.nMeterType)
    {
    case 1://ȫԲ�Ǳ�ͼ ָ������
        qmeterbase->meter.nPointStartAngle = 90;
        qmeterbase->meter.nPointSpanAngel = 360;
        qmeterbase->meter.nstartAngle = 0;
        qmeterbase->meter.nSpanAngle =360;
        break;
    case 2://ȫ԰ָ������
        qmeterbase->meter.nPointStartAngle = 270;
        qmeterbase->meter.nPointSpanAngel = 360;
        qmeterbase->meter.nstartAngle = 0;
        qmeterbase->meter.nSpanAngle =360;
        break;
    case 3://ȫԲָ������
        qmeterbase->meter.nPointStartAngle = 0;
        qmeterbase->meter.nPointSpanAngel = 360;
        qmeterbase->meter.nstartAngle = 0;
        qmeterbase->meter.nSpanAngle =360;
        break;
    case 4://ȫԲָ������
        qmeterbase->meter.nPointStartAngle = 180;
        qmeterbase->meter.nPointSpanAngel = 360;
        qmeterbase->meter.nstartAngle = 0;
        qmeterbase->meter.nSpanAngle =360;
        break;
    case 5://�ķ�֮��Բ��������
        qmeterbase->meter.nPointStartAngle = 315;
        qmeterbase->meter.nPointSpanAngel = 270;
        qmeterbase->meter.nstartAngle = 315;
        qmeterbase->meter.nSpanAngle =270;
        break;
    case 6://�ķ�֮��Բ��������
        qmeterbase->meter.nPointStartAngle = 135;
        qmeterbase->meter.nPointSpanAngel = 270;
        qmeterbase->meter.nstartAngle = 135;
        qmeterbase->meter.nSpanAngle =270;
        break;
    case 7://�ķ�֮��Բ��������
        qmeterbase->meter.nPointStartAngle = 45;
        qmeterbase->meter.nPointSpanAngel = 270;
        qmeterbase->meter.nstartAngle = 225;
        qmeterbase->meter.nSpanAngle =270;
        break;
    case 8://�ķ�֮��Բ��������
        qmeterbase->meter.nPointStartAngle = 225;
        qmeterbase->meter.nPointSpanAngel = 270;
        qmeterbase->meter.nstartAngle = 45;
        qmeterbase->meter.nSpanAngle =270;
        break;
    case 9:
        qmeterbase->meter.nPointStartAngle = 0;
        qmeterbase->meter.nPointSpanAngel = 90;
        qmeterbase->meter.nstartAngle = 90;
        qmeterbase->meter.nSpanAngle =90;
        break;
    case 10:
        qmeterbase->meter.nPointStartAngle = 90;
        qmeterbase->meter.nPointSpanAngel = 90;
        qmeterbase->meter.nstartAngle = 0;
        qmeterbase->meter.nSpanAngle =90;
        break;
    case 11:
        qmeterbase->meter.nPointStartAngle = 0;
        qmeterbase->meter.nPointSpanAngel = 90;
        qmeterbase->meter.nstartAngle = 90;
        qmeterbase->meter.nSpanAngle =90;
        break;
    case 12:
        qmeterbase->meter.nPointStartAngle = 90;
        qmeterbase->meter.nPointSpanAngel = 90;
        qmeterbase->meter.nstartAngle = 0;
        qmeterbase->meter.nSpanAngle =90;
        break;
    case 13:
        qmeterbase->meter.nPointStartAngle = 270;
        qmeterbase->meter.nPointSpanAngel = 90;
        qmeterbase->meter.nstartAngle = 180;
        qmeterbase->meter.nSpanAngle =90;
        break;
    case 14:
        qmeterbase->meter.nPointStartAngle = 180;
        qmeterbase->meter.nPointSpanAngel = 90;
        qmeterbase->meter.nstartAngle = 270;
        qmeterbase->meter.nSpanAngle =90;
        break;
    case 15:
        qmeterbase->meter.nPointStartAngle = 270;
        qmeterbase->meter.nPointSpanAngel = 90;
        qmeterbase->meter.nstartAngle = 180;
        qmeterbase->meter.nSpanAngle =90;
        break;
    case 16:
        qmeterbase->meter.nPointStartAngle = 180;
        qmeterbase->meter.nPointSpanAngel = 90;
        qmeterbase->meter.nstartAngle = 270;
        qmeterbase->meter.nSpanAngle =90;
        break;
    case 17:
    case 18:
        qmeterbase->meter.nPointStartAngle = 0;
        qmeterbase->meter.nPointSpanAngel = 180;
        qmeterbase->meter.nstartAngle = 0;
        qmeterbase->meter.nSpanAngle =180;
        break;
    case 20:
    case 19:
        qmeterbase->meter.nPointStartAngle = 45;
        qmeterbase->meter.nPointSpanAngel = 90;
        qmeterbase->meter.nstartAngle = 45;
        qmeterbase->meter.nSpanAngle =90;
        break;
    case 21:
    case 22:
        qmeterbase->meter.nPointStartAngle = 180;
        qmeterbase->meter.nPointSpanAngel = 180;
        qmeterbase->meter.nstartAngle = 180;
        qmeterbase->meter.nSpanAngle =180;
        break;
    case 23:
    case 24:
        qmeterbase->meter.nPointStartAngle = 225;
        qmeterbase->meter.nPointSpanAngel = 90;
        qmeterbase->meter.nstartAngle = 225;
        qmeterbase->meter.nSpanAngle =90;
        break;
    case 25:
    case 28:
        qmeterbase->meter.nPointStartAngle = 315;
        qmeterbase->meter.nPointSpanAngel = 90;
        qmeterbase->meter.nstartAngle = 135;
        qmeterbase->meter.nSpanAngle =90;
        break;
    case 26:
    case 27:
        qmeterbase->meter.nPointStartAngle = 135;
        qmeterbase->meter.nPointSpanAngel = 90;
        qmeterbase->meter.nstartAngle = 315;
        qmeterbase->meter.nSpanAngle =90;
        break;
    case 29:
    case 31:
        qmeterbase->meter.nPointStartAngle = 270;
        qmeterbase->meter.nPointSpanAngel = 180;
        qmeterbase->meter.nstartAngle = 90;
        qmeterbase->meter.nSpanAngle =180;
        break;
    case 30:
    case 32:
        qmeterbase->meter.nPointStartAngle = 90;
        qmeterbase->meter.nPointSpanAngel = 180;
        qmeterbase->meter.nstartAngle = 270;
        qmeterbase->meter.nSpanAngle =180;
        break;
    default:
        break;
    }
    qmeterbase->OnReDrawMeter();
}

void QChartDlg::loadHelp()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_CHART);
}

void QChartDlg::setCommonShapeType()
{
    qcommoncolor->setCommonShapeType(qcommonbase->nShapeType);
}

void QChartDlg::setCommonScaleColor()
{
    qcommoncolor->circle.nMainScal = qcommonruler->nMainScale;
    qcommoncolor->circle.nSubScal = qcommonruler->nSubScale;
    qcommoncolor->circle.ScaleColor = qcommonruler->sCaleColor;
    qcommoncolor->nMainScale = qcommonruler->nMainScale;
    qcommoncolor->nSubScale = qcommonruler->nSubScale;
    qcommoncolor->sCaleColor = qcommonruler->sCaleColor;
    qcommoncolor->reDrawBar();
}

void QChartDlg::setMeterScaleColor()
{
    qmeterbase->sPointColor = qmetercolor->nPointColor;
    qmeterbase->meter.sPointColor = qmetercolor->nPointColor;
    qmeterbase->meter.nMainScal = qmeteruler->onGetMainScale();
    qmeterbase->meter.nSubScal = qmeteruler->onGetSubScale();
    qmeterbase->meter.sCaleColor = qmeteruler->onGetScaleColor();
    qmeterbase->meter.sBackColor = qmetercolor->nBackColor;
    qmeterbase->OnReDrawMeter();
}

void QChartDlg::onSaveItemPosition()
{
    QRectF oldpos = pCopyItem->sceneBoundingRect();
    if(ENMETER_TYPE == enGrahpType)
    {
        meter_st.nLeftTopX = oldpos.x();
        meter_st.nLeftTopY = oldpos.y();
        meter_st.nWidth = oldpos.width();
        meter_st.nHeight = oldpos.height();
    }
    else
    {
        common_st.nLeftTopX = oldpos.x();
        common_st.nLeftTopY = oldpos.y();
        common_st.nWidth = oldpos.width();
        common_st.nHeight = oldpos.height();
    }
    if(PILLA == common_st.eShapeType)//����
    {
        common_st.nShowLeftTopX = 0;
        common_st.nRulerLeftTopX = 0;
        QList<QGraphicsItem *> childitem;
        childitem = pCopyItem->childItems();
        foreach(QGraphicsItem *pItem,childitem)
        {
            if("MainLine" == pItem->data(GROUP_NAME_KEY).toString())
            {
                oldpos = pItem->sceneBoundingRect();
                common_st.nRulerLeftTopX = oldpos.x();
                common_st.nRulerLeftTopY = oldpos.y();
                common_st.nRulerWidth = oldpos.width();
                common_st.nRulerHigth = oldpos.height();
            }
            if("FrameItem" == pItem->data(GROUP_NAME_KEY).toString())
            {
                oldpos = pItem->sceneBoundingRect();
                common_st.nShowLeftTopX = oldpos.x();
                common_st.nShowLeftTopY = oldpos.y();
                common_st.nShowWidth = oldpos.width();
                common_st.nShowHigth = oldpos.height();
            }
        }
        if(common_st.nRulerLeftTopX > common_st.nShowLeftTopX)
        {
            common_st.eRulerDirectio = TOWARD_RIGHT;//�����ʾ����
        }
        else
        {
            common_st.eRulerDirectio = TOWARD_LEFT;
        }
    }
    if(GROOVE == common_st.eShapeType)//����
    {
        common_st.nShowLeftTopX = 0;
        common_st.nRulerLeftTopX = 0;
        QList<QGraphicsItem *> childitem;
        childitem = pCopyItem->childItems();
        foreach(QGraphicsItem *pItem,childitem)
        {
            if("MainLine" == pItem->data(GROUP_NAME_KEY).toString())
            {
                oldpos = pItem->sceneBoundingRect();
                common_st.nRulerLeftTopX = oldpos.x();
                common_st.nRulerLeftTopY = oldpos.y();
                common_st.nRulerWidth = oldpos.width();
                common_st.nRulerHigth = oldpos.height();
            }
            if("HistogramItem" == pItem->data(GROUP_NAME_KEY).toString())
            {
                oldpos = pItem->sceneBoundingRect();
                common_st.nShowLeftTopX = oldpos.x();
                common_st.nShowLeftTopY = oldpos.y();
                common_st.nShowWidth = oldpos.width();
                common_st.nShowHigth = oldpos.height();
            }
            common_st.eRulerDirectio = TOWARD_RIGHT;
        }
    }
}
