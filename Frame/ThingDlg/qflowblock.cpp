#include "Frame/ThingDlg/qflowblock.h"
#include "ui_qflowblock.h"
#include "Frame/mainwindow.h"
#include "view/flowblockitem.h"
extern MainWindow *pwnd;

qFlowBlock::qFlowBlock(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qFlowBlock)
{
    ui->setupUi(this);
    oId = -1;
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    pScene = new QGraphicsScene(this);     //������
    ui->LView->setScene(pScene);           //����ͼ��ʾ����
    QGraphicsItem *Item;

    pQFlowBlockGen=new QFlowBlockGenDlg();
    securitywidgets=new SecurityWidget();


    ui->tabWidget->addTab(pQFlowBlockGen, tr("�������"));
    ui->tabWidget->addTab(securitywidgets, tr("Ȩ������"));

    //connect(pQFlowBlockGen, SIGNAL(DrawFlow()),this, SLOT(onDrawFlow()));
    if(pItem)
    {
        connect(pQFlowBlockGen, SIGNAL(DrawFlow()),this, SLOT(onDrawFlow()));
        Item = dynamic_cast<FlowBlockItem *> (pItem)->Clone();
        InitAllProperty(dynamic_cast<FlowBlockItem *> (Item));
        securitywidgets->init(dynamic_cast<FlowBlockItem *> (Item));//Ȩ��
        pRectList.clear();
        pScene->clear();
        onDrawFlow();
        oId = dynamic_cast<FlowBlockItem *> (Item)->id();
        ui->spinBox->setValue(oId);
    }
    else
    {
        InitAllProperty(NULL);
        securitywidgets->setTouchDisable(false);
        securitywidgets->init(0);
        pScene->clear();
        onDrawFlow();
        connect(pQFlowBlockGen, SIGNAL(DrawFlow()),this, SLOT(onDrawFlow()));
        ui->spinBox->setValue(pwnd->getNewId());
    }
    this->setWindowTitle(tr("������"));
    securitywidgets->setTouchGroupEnabled(false);
}

qFlowBlock::~qFlowBlock()
{
    delete ui;
}

void qFlowBlock::InitAllProperty(FlowBlockItem *pItem)
{
    if (pItem)//��һ�����е�λ��ť
    {
        pQFlowBlockGen->Init(pItem);//��ʼ��һ��ҳ��
    }
    else//�½�
    {
        pQFlowBlockGen->Init(NULL);//��ʼ��һ��ҳ��
    }

}
void qFlowBlock::on_accept_clicked()
{
    if(! pwnd->IsAddressCheckRight(pQFlowBlockGen->Monitor_Address_Keyboard,tr("������ַ"),pQFlowBlockGen->ui->Monitor_Address,0))
     {
         return;
     }
    if(pQFlowBlockGen->ui->DynamicFlowSpeed->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(pQFlowBlockGen->Flowspeedkeyboard,tr("�����ٶȵ�ַ"),pQFlowBlockGen->ui->FlowSpeed,1))
        {
            return;
        }
    }
    if(pQFlowBlockGen->ui->m_changdircheck->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(pQFlowBlockGen->TouchAddr,tr("���ص�ַ"),pQFlowBlockGen->ui->m_touchaddredit,0))
        {
            return;
        }
    }
    pQFlowBlockGen->FlowBlockGenSave(m_flow);
    this->pCopyItem->onSaveFlow(m_flow);
    //Ȩ��
    if(!securitywidgets->Save())
    {
        return;
    }
    pCopyItem->SaveSecurityPro(&(securitywidgets->sproperty));
    pCopyItem->onSecurityPro(sproperty);
    pCopyItem->setId(ui->spinBox->value());
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

void qFlowBlock::on_cancel_clicked()
{
    this->close();
}

void qFlowBlock::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_FLOW);
}
//����������
void qFlowBlock::onDrawFlow()
{
    if(pQFlowBlockGen->ui->m_Vradio->isChecked()){//ifˮƽ
        nDirection = 1;
    }else{
        nDirection = 0;
    }

    nFlowCount = 3;
    int nCount = pQFlowBlockGen->ui->m_countspinBox->value(); //����������
    int i = 0;
    QRectF mRect;
    QRectItem *pSubRect;
    double nWidth = 0.0; //ÿ����Ŀ��
    QString sName = "";

    QColor mFlowFrontColor = pQFlowBlockGen->ui->m_flowfrontcolorbtn->palette().background().color();
    QColor mFlowBackColor = pQFlowBlockGen->ui->m_flowbackcolorbtn->palette().background().color();
    QColor mPipeFrontColor = pQFlowBlockGen->ui->m_pipefrontcolorbtn ->palette().background().color();
    QColor mPipebackColor = pQFlowBlockGen->ui->m_pipebackcolorbtn->palette().background().color();
    QColor mFramColor = pQFlowBlockGen->ui->m_framcolorbtn->palette().background().color();

    FlowBlockItem *pGroup = new FlowBlockItem;//new QGraphicsItemGroup;
    nCount = nCount*3;
    nFlowCount = nFlowCount;
    nWidth = 108.0 / nCount;   //ÿ����Ŀ��

    if(!pRectList.empty()) //�ж��Ƿ�Ϊ��
    {
        for(i = 0; i < nFlowCount; i++)
        {
            pScene->removeItem(pRectList.at(i));
            delete pRectList.at(i);
        }

        pScene->clear();
        pRectList.clear();
    }


    if(nDirection == 0)      //ˮƽ����
    {
        for(i = 0; i < nCount; i++) //��С������
        {
            mRect.setTopLeft(QPointF(i*nWidth,50));
            mRect.setSize(QSizeF(nWidth,18));
            pSubRect = new QRectItem(mRect);

          //  pSubRect->SetId(i+1);
            pSubRect->setZValue(i+2);
            pRectList.append(pSubRect);
        }
    }
    else if(nDirection == 1) //��ֱ����
    {
        for(i = 0; i < nCount; i++) //��С������
        {
            mRect.setTopLeft(QPointF(50,i*nWidth));
            mRect.setSize(QSizeF(18,nWidth));
            pSubRect = new QRectItem(mRect);
          //  pSubRect->SetId(i+1);
            pSubRect->setZValue(i+2);
            pRectList.append(pSubRect);
        }
    }

    for(i = 0; i < nCount; i++)
    {
        pRectList.at(i)->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pRectList.at(i)->setFlag(QGraphicsItem::ItemIsMovable, false);
        if( i % 3 == 2)
        {
            pRectList.at(i)->SetBackColor(mPipebackColor);
            pRectList.at(i)->SetFrontColor(mPipeFrontColor);
        }
        else
        {
            pRectList.at(i)->SetBackColor(mFlowBackColor);
            pRectList.at(i)->SetFrontColor(mFlowFrontColor);
        }

        sName = QString("%1").arg(i); //����ÿ���������
        sName = "Flow"+sName;
        pRectList.at(i)->SetName(sName);

        pRectList.at(i)->SetLineColor(mFramColor);                      //���ñ߿�ɫ
        pRectList.at(i)->SetPattern(pQFlowBlockGen->ui->m_patterncmb->currentIndex());  //������ʽ
        pGroup->addToGroup(pRectList.at(i));  //��ӵ�һ����
    }

    bool nChecks = pQFlowBlockGen->ui->m_noframcheck->checkState();
    int nCounts = pQFlowBlockGen->ui->m_countspinBox->value(); //����������
    int k = 0;
    nCounts = nCounts*3;

    if(nChecks) //û�б���
    {
        for(k = 0; k < nCounts; k++)
        {
            pRectList.at(k)->SetLineType(0);
            pGroup->addToGroup(pRectList.at(k));
        }
    }
    else       //�б���
    {
        for(k = 0; k < nCounts; k++)
        {
            pRectList.at(k)->SetLineType(1);
            pGroup->addToGroup(pRectList.at(k));
        }
    }


    pScene->addItem(pGroup);
    this->pCopyItem = pGroup;
//    pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_FLOWBLOCK));
    nFlowCount = nCount;        //���¸�ֵ
}
