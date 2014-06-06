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
    if(0 == index)//散点轨迹
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
        if(1 == aninfo.nMoveCondition)//按预设值切换
        {
            ui->m_MoveAddrlineEdit->setText(aninfo.mMoveCtrlAddr.sShowAddr);
        }
        on_m_MoveCondtionCmBox_currentIndexChanged(aninfo.nMoveCondition);
        ui->m_MoveCondtionCmBox->setCurrentIndex(aninfo.nMoveCondition);//按时间切换 index
        //aninfo = ui->m_AlignmentTypeCmBox->currentIndex();//轨迹点对齐方式
        ui->m_LocusTotallineEdit->setText(QString::number(aninfo.nTrackPointTotal));//轨迹点总数
        ui->m_moveTypecmBox->setCurrentIndex(aninfo.nMoveType);//移动方式
        ui->m_MoveTimeSpBox->setValue(aninfo.nMoveTimeInterval);//移动时间间隔
        stMoveInfo = aninfo.stMoveInfo;//轨迹点预设值

        pItem->onGetTrackInfo(m_Tinfo);//获取轨迹点坐标
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
            stMoveInfo.resize(m_Tinfo.size());//轨迹点预设固定值
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

           //stMoveInfo.resize(nTotalTrack);//轨迹点预设固定值
        }
        else
        {
            ui->m_TrackspBox->setRange(0,0);
            ui->m_LocusTotallineEdit->setText(QString::number(0));
            onSetTrack(1);
            stMoveInfo.resize(0);
        }
        ui->m_StartCmBox->setCurrentIndex(aninfo.nStartTrackPoint); //初始轨迹点

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
    if(1 == ui->m_MoveCondtionCmBox->currentIndex())//按预设值切换
    {
        if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("移动控制地址"),ui->m_MoveAddrlineEdit,1))
        {
            ui->m_MoveAddrlineEdit->setFocus();
            return false;
        }
    }
    aninfo.sMoveCtrlAddr = ui->m_MoveAddrlineEdit->text();
    aninfo.mMoveCtrlAddr = Monitor_Address_Keyboard;//移动控制地址
    aninfo.nMoveCondition = ui->m_MoveCondtionCmBox->currentIndex();//按时间切换 index
    //aninfo = ui->m_AlignmentTypeCmBox->currentIndex();//轨迹点对齐方式
    aninfo.nTrackPointTotal = ui->m_LocusTotallineEdit->text().toInt();//轨迹点总数
    aninfo.nMoveType = ui->m_moveTypecmBox->currentIndex();//移动方式
    aninfo.nMoveTimeInterval = ui->m_MoveTimeSpBox->value();//移动时间间隔
    aninfo.nStartTrackPoint = ui->m_StartCmBox->currentIndex(); //初始轨迹点
    aninfo.stMoveInfo = stMoveInfo;//轨迹点预设值
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

void ScatterWidget::onSetTrack(int index)//初始轨迹点
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

        if(sName == tr("mMain")) //向量图控件
        {
//            rc = group->boundingRect();
//            ui->m_width->setValue(rc.width()); //初始化向量图的的宽度
//            ui->m_height->setValue(rc.height());//初始化向量图的的高度
//            iWidth = rc.width();
//            iHeight = rc.height();
        }
        else if(ikey == SAM_DRAW_OBJECT_ELIPSE) //记录每个点的位置
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
    ui->m_TrackspBox->setValue(0); //初始化轨迹点
    ui->m_xTracklineEdit->setText(QString::number(m_Tinfo.at(0).nXPos)); //初始化位置0的x坐标
    ui->m_yTracklineEdit->setText(QString::number(m_Tinfo.at(0).nYPos));//初始化位置1的y坐标
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
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("轨迹点个数为0"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
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
