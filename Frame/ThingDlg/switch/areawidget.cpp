#include "areawidget.h"
#include "ui_areawidget.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;
AreaWidget::AreaWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AreaWidget)
{
    ui->setupUi(this);
    ui->m_xMoveAddrlineEdit->setText("LW0");
    ui->m_yMoveAddrlineEdit->setText("LW0");
}

AreaWidget::~AreaWidget()
{
    delete ui;
}

void AreaWidget::Init(AnimationItem *pItem)
{
    m_Tinfo.clear();
    if(pItem)
    {
        AnInfo aninfo;
        pItem->onGetAnimatInfo(aninfo);
        ui->m_xMoveAddrlineEdit->setText(aninfo.mXPosCtrlAddr.sShowAddr);
        ui->m_yMoveAddrlineEdit->setText(aninfo.mYPosCtrlAddr.sShowAddr);

        ui->m_MoveTimeSpBox->setValue(aninfo.nXMoveStepScale);
        ui->m_yMoveTimeSpBox->setValue(aninfo.nYMoveStepScale);
        doubleClickInit(pItem);
    }
    else
    {

    }
}

bool AreaWidget::onAnimatInfosave(AnInfo &aninfo)
{
    if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("X坐标控制地址"),ui->m_xMoveAddrlineEdit,1))
    {
        ui->m_xMoveAddrlineEdit->setFocus();
        return false;
    }
    aninfo.mXPosCtrlAddr = Monitor_Address_Keyboard;

    if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("Y坐标控制地址"),ui->m_yMoveAddrlineEdit,1))
    {
        ui->m_yMoveAddrlineEdit->setFocus();
        return false;
    }
    aninfo.mYPosCtrlAddr = Monitor_Address_Keyboard;
    aninfo.sAddrX = ui->m_xMoveAddrlineEdit->text();
    aninfo.sAddrY = ui->m_yMoveAddrlineEdit->text();

    aninfo.nXMoveStepScale = ui->m_MoveTimeSpBox->value();
    aninfo.nYMoveStepScale = ui->m_yMoveTimeSpBox->value();

    aninfo.nTrackPointTotal = m_Tinfo.size();//轨迹点总数

    return true;
}

void AreaWidget::doubleClickInit(AnimationItem *pItem)
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

    if(2 != m_Tinfo.size())
    {
        return;
    }

    ui->m_XlineEdit->setText(QString::number(m_Tinfo[0].nXPos));
    ui->M_YlineEdit->setText(QString::number(m_Tinfo[0].nYPos));
    ui->m_WlineEdit->setText(QString::number(qAbs(m_Tinfo[1].nXPos - m_Tinfo[0].nXPos)));
    ui->m_HlineEdit->setText(QString::number(qAbs(m_Tinfo[1].nYPos - m_Tinfo[0].nYPos)));
}

void AreaWidget::on_m_XAddressEntryBtn_clicked()
{
    QString addrStr = ui->m_xMoveAddrlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_xMoveAddrlineEdit->setText(Monitor_Address_Keyboard.sShowAddr);
    }
}

void AreaWidget::on_m_YAddressEntryBtn_clicked()
{
    QString addrStr = ui->m_yMoveAddrlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_yMoveAddrlineEdit->setText(Monitor_Address_Keyboard.sShowAddr);
    }
}
