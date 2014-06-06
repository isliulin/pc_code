#include "scatterwidget.h"
#include "ui_scatterwidget.h"
#include "Frame/mainwindow.h"
#include "Frame/ThingDlg/qmultistategenelcunstomdlg.h"
extern MainWindow *pwnd;

ScatterWidget::ScatterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScatterWidget)
{
    values.clear();
    ui->setupUi(this);
    ui->m_MoveAddrlineEdit->setText("LW0");
}

ScatterWidget::~ScatterWidget()
{
    delete ui;
}

void ScatterWidget::on_m_MoveCondtionCmBox_currentIndexChanged(int index)
{
    if(0 == index)//ɢ��켣
    {
        //ui->m_MoneModelabel->show();
        //ui->m_MoneModeCmBox->show();
        ui->m_moveTypelabel->setEnabled(true);
        ui->m_moveTypecmBox->setEnabled(true);
        ui->m_Movelabel->setEnabled(true);
        ui->m_MoveTimelabel->setEnabled(true);
        ui->m_MoveTimeSpBox->setEnabled(true);
        ui->m_Startlabel->setEnabled(true);
        ui->m_StartCmBox->setEnabled(true);

        ui->m_MoveAddrlabel->setEnabled(false);
        ui->m_MoveAddrlineEdit->setEnabled(false);
        ui->m_MoveCtrlAddressEntryBtn->setEnabled(false);
        ui->btn_customValue->setEnabled(false);
    }
    else if(1 == index)
    {
        //ui->m_MoneModelabel->hide();
        //ui->m_MoneModeCmBox->hide();
        ui->m_moveTypelabel->setEnabled(false);
        ui->m_moveTypecmBox->setEnabled(false);
        ui->m_Movelabel->setEnabled(false);
        ui->m_MoveTimelabel->setEnabled(false);
        ui->m_MoveTimeSpBox->setEnabled(false);
        ui->m_Startlabel->setEnabled(false);
        ui->m_StartCmBox->setEnabled(false);

        ui->m_MoveAddrlabel->setEnabled(true);
        ui->m_MoveAddrlineEdit->setEnabled(true);
        ui->m_MoveCtrlAddressEntryBtn->setEnabled(true);
        ui->btn_customValue->setEnabled(true);
    }
}

void ScatterWidget::Init(AnimationItem *pItem)
{
    bInitFlag = false;
    if(pItem)
    {
        AnInfo aninfo;
        pItem->onGetAnimatInfo(aninfo);
        if(1 == aninfo.nMoveCondition)//��Ԥ��ֵ�л�
        {
            ui->m_MoveAddrlineEdit->setText(aninfo.mMoveCtrlAddr.sShowAddr);
        }
        on_m_MoveCondtionCmBox_currentIndexChanged(aninfo.nMoveCondition);
        ui->m_MoveCondtionCmBox->setCurrentIndex(aninfo.nMoveCondition);//��ʱ���л� index
        //aninfo = ui->m_AlignmentTypeCmBox->currentIndex();//�켣����뷽ʽ
        ui->m_LocusTotallineEdit->setText(QString::number(aninfo.nTrackPointTotal));//�켣������
        ui->m_moveTypecmBox->setCurrentIndex(aninfo.nMoveType);//�ƶ���ʽ
        ui->m_MoveTimeSpBox->setValue(aninfo.nMoveTimeInterval);//�ƶ�ʱ����
        stMoveInfo = aninfo.stMoveInfo;//�켣��Ԥ��ֵ

        pItem->onGetTrackInfo(m_Tinfo);//��ȡ�켣������
        if(stMoveInfo.size() > 0)
        {
            values.resize(stMoveInfo.size());
            for(int i = 0; i < stMoveInfo.size(); i++)
            {
                values[i] = stMoveInfo[i].nMCmpFactor;
            }
        }
        else
        {
            values.resize(m_Tinfo.size());
            stMoveInfo.resize(m_Tinfo.size());//�켣��Ԥ��̶�ֵ
            for(int i = 0; i < m_Tinfo.size(); i++)
            {
                values[i] = i;
                stMoveInfo[i].nMCmpFactor = i;
                stMoveInfo[i].nTrackPointNo = i;
            }
        }
        int nTotalTrack = m_Tinfo.size();
        if(nTotalTrack > 0)
        {
           ui->m_TrackspBox->setRange(0,nTotalTrack - 1);
           ui->m_LocusTotallineEdit->setText(QString::number(nTotalTrack));
           onSetTrack(nTotalTrack);

           //stMoveInfo.resize(nTotalTrack);//�켣��Ԥ��̶�ֵ
        }
        else
        {
            ui->m_TrackspBox->setRange(0,0);
            ui->m_LocusTotallineEdit->setText(QString::number(0));
            onSetTrack(1);
            stMoveInfo.resize(0);
        }
        ui->m_StartCmBox->setCurrentIndex(aninfo.nStartTrackPoint); //��ʼ�켣��

        doubleClickInit(pItem);
    }
    else
    {
        on_m_MoveCondtionCmBox_currentIndexChanged(0);
        m_Tinfo.resize(0);
        ui->m_LocusTotallineEdit->setText("0");
        ui->m_TrackspBox->setRange(0,0);
        onSetTrack(1);
    }
    bInitFlag = true;
}

bool ScatterWidget::onAnimatInfosave(AnInfo &aninfo)
{
    if(1 == ui->m_MoveCondtionCmBox->currentIndex())//��Ԥ��ֵ�л�
    {
        if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("�ƶ����Ƶ�ַ"),ui->m_MoveAddrlineEdit,1))
        {
            ui->m_MoveAddrlineEdit->setFocus();
            return false;
        }
    }
    aninfo.sMoveCtrlAddr = ui->m_MoveAddrlineEdit->text();
    aninfo.mMoveCtrlAddr = Monitor_Address_Keyboard;//�ƶ����Ƶ�ַ
    aninfo.nMoveCondition = ui->m_MoveCondtionCmBox->currentIndex();//��ʱ���л� index
    //aninfo = ui->m_AlignmentTypeCmBox->currentIndex();//�켣����뷽ʽ
    aninfo.nTrackPointTotal = ui->m_LocusTotallineEdit->text().toInt();//�켣������
    aninfo.nMoveType = ui->m_moveTypecmBox->currentIndex();//�ƶ���ʽ
    aninfo.nMoveTimeInterval = ui->m_MoveTimeSpBox->value();//�ƶ�ʱ����
    aninfo.nStartTrackPoint = ui->m_StartCmBox->currentIndex(); //��ʼ�켣��
    aninfo.stMoveInfo = stMoveInfo;//�켣��Ԥ��ֵ
    return true;
}

void ScatterWidget::on_m_TrackspBox_valueChanged(int )
{
    int index = ui->m_TrackspBox->value();
    if(index < m_Tinfo.size() && index >=0 && m_Tinfo.size() > 0)
    {
        ui->m_xTracklineEdit->setText(QString::number(m_Tinfo[index].nXPos));
        ui->m_yTracklineEdit->setText(QString::number(m_Tinfo[index].nYPos));
    }
}

void ScatterWidget::onSetTrack(int index)//��ʼ�켣��
{
    ui->m_StartCmBox->clear();
    for(int i = 0; i<index; i++)
    {
        QString str = QString("%1").arg(i);
        ui->m_StartCmBox->addItem(str);
    }
}

void ScatterWidget::doubleClickInit(AnimationItem *pItem)
{
    if(!pItem)
        return;
    QList <QGraphicsItem *> items = pItem->childItems();
    QGraphicsItem *group = NULL;
    int nCount = items.size();
    int i = 0;
    QString sName = "";
    int ikey = 0;
    m_Tinfo.clear();

    QRectF rc;
    for(i  = 0;i < nCount;i++)
    {
        group = items.at(i);
        sName = group->data(GROUP_NAME_KEY).toString();
        ikey = group->type();

        if(sName == tr("mMain")) //����ͼ�ؼ�
        {
//            rc = group->boundingRect();
//            ui->m_width->setValue(rc.width()); //��ʼ������ͼ�ĵĿ��
//            ui->m_height->setValue(rc.height());//��ʼ������ͼ�ĵĸ߶�
//            iWidth = rc.width();
//            iHeight = rc.height();
        }
        else if(ikey == SAM_DRAW_OBJECT_ELIPSE) //��¼ÿ�����λ��
        {
            QPointF pos = group->boundingRect().topLeft()+group->scenePos();
            TrackPointInfo TrackPoint;
            TrackPoint.nXPos = pos.x();
            TrackPoint.nYPos = pos.y();
            m_Tinfo.append(TrackPoint);
        }
    }//end for

    ui->m_TrackspBox->setRange(0,m_Tinfo.size() - 1);
    for(i  = 0;i < m_Tinfo.size();i++)
    {
        m_Tinfo[i].nOrbitId = i;
    }
    ui->m_TrackspBox->setValue(0); //��ʼ���켣��
    ui->m_xTracklineEdit->setText(QString::number(m_Tinfo.at(0).nXPos)); //��ʼ��λ��0��x����
    ui->m_yTracklineEdit->setText(QString::number(m_Tinfo.at(0).nYPos));//��ʼ��λ��1��y����
}

void ScatterWidget::on_m_MoveCtrlAddressEntryBtn_clicked()
{
    QString addrStr = ui->m_MoveAddrlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_MoveAddrlineEdit->setText(Monitor_Address_Keyboard.sShowAddr);
    }
}

void ScatterWidget::on_btn_customValue_clicked()
{
    if(m_Tinfo.size() <= 0)
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("�켣�����Ϊ0"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }
    QMultiStateGenelCunstomDlg *customDlg=new QMultiStateGenelCunstomDlg(this);

    customDlg->setAllData(values,false);
    if(customDlg->exec() == QDialog::Accepted)
    {
        values = customDlg->allValues;
        for(int i = 0; i < values.size() && i < stMoveInfo.size(); i++)
        {
            stMoveInfo[i].nMCmpFactor = values[i];
        }
    }
}
