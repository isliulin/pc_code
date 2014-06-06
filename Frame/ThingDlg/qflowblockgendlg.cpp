#include "qflowblockgendlg.h"
#include "ui_qflowblockgendlg.h"
#include "Frame/mainwindow.h"
#include <QGraphicsItemGroup>
#include "view/FlowBlockItem.h";

extern MainWindow *pwnd;

QFlowBlockGenDlg::QFlowBlockGenDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFlowBlockGenDlg)
{
    ui->setupUi(this);
    nInitFlag = false;
    isPatten = true;//判断样式

    RadioButton_direction_Group=new QButtonGroup(this);
    RadioButton_direction_Group->addButton(ui->m_Hradio,1);
    RadioButton_direction_Group->addButton(ui->m_Vradio,2);

    RadioButtonState = new QButtonGroup(this); //有效状态
    RadioButtonState->addButton(ui->m_radio0,0);
    RadioButtonState->addButton(ui->m_radio1,1);

    FixupFlowSpeed=new QButtonGroup(this);
    FixupFlowSpeed->addButton(ui->low,3);
    FixupFlowSpeed->addButton(ui->middle,4);
    FixupFlowSpeed->addButton(ui->high,5);

    FlowMode=new QButtonGroup(this);
    FlowMode->addButton(ui->FixupFlowspeed,1);
    FlowMode->addButton(ui->DynamicFlowSpeed,2);

    ui->Monitor_Address->setText("LB0");

     /***************************************************
     *以下是单击工具栏的初始化
     **************************************************/
    pwnd->OnAddPattern(ui->m_patterncmb);  //初始化样式组合框

    /***************************************************
     *以下是双击控件初始化
     **************************************************/

    ui->Monitor_Address->setFocus();
    nInitFlag = true; //初始化完成标志
}

QFlowBlockGenDlg::~QFlowBlockGenDlg()
{

     if(RadioButton_direction_Group)
    {
        delete RadioButton_direction_Group;
        RadioButton_direction_Group = NULL;
    }
     if(RadioButtonState)
     {
         delete RadioButtonState;
         RadioButtonState = NULL;
     }
     if(FixupFlowSpeed)
     {
         delete FixupFlowSpeed;
         FixupFlowSpeed = NULL;
     }
     if(FlowMode)
     {
         delete FlowMode;
         FlowMode = NULL;
     }
           delete ui;
}

void QFlowBlockGenDlg::on_m_Hradio_clicked() //水平显示
{
    if(!nInitFlag)
    {
        return;
    }
    ui->m_drectioncmb->clear();
    ui->m_drectioncmb->addItem(tr("向左")); //初始化流动方向
    ui->m_drectioncmb->addItem(tr("向右"));
    ui->m_patterncmb->setCurrentIndex(5);
    if(isPatten){
        //
        isPatten=false;
    }
    nDirection = 0;
    emit DrawFlow();
}

void QFlowBlockGenDlg::on_m_Vradio_clicked()//垂直显示
{
    if(!nInitFlag)
    {
        return;
    }
    ui->m_drectioncmb->clear();
    ui->m_drectioncmb->addItem(tr("向上")); //初始化流动方向
    ui->m_drectioncmb->addItem(tr("向下"));
    ui->m_patterncmb->setCurrentIndex(3);
    if(isPatten){

        isPatten=false;
    }

    nDirection = 1;
    emit DrawFlow();
}


void QFlowBlockGenDlg::on_m_noframcheck_clicked() //有无边线
{

    emit DrawFlow();
}

void QFlowBlockGenDlg::on_m_countspinBox_valueChanged(int ) //流动块数改变
{
    if(!nInitFlag)
        return;
    emit DrawFlow(); //绘制流动块
}

void QFlowBlockGenDlg::OnSetFlowFrontColor(const QColor & nColor)  //设置流动块前景色
{
    int nCount = ui->m_countspinBox->value(); //流动块总数
    ui->m_flowfrontcolorbtn->setStyleSheet(QString("background:%1").arg(nColor.name()));
    int i = 0;
    nCount = nCount*3;

    emit DrawFlow();
}

void QFlowBlockGenDlg::OnSetFlowBackColor(const QColor & nColor)   //设置流动块背景色
{
    int nCount = ui->m_countspinBox->value(); //流动块总数
    ui->m_flowbackcolorbtn->setStyleSheet(QString("background:%1").arg(nColor.name()));
    int i = 0;
    nCount = nCount*3;

    emit DrawFlow();
}

void QFlowBlockGenDlg::OnSetPipeFrontColor(const QColor & nColor)  //设置管道前景色
{
    int nCount = ui->m_countspinBox->value(); //流动块总数
    ui->m_pipefrontcolorbtn->setStyleSheet(QString("background:%1").arg(nColor.name()));
    int i = 0;
    nCount = nCount*3;

    emit DrawFlow();
}

void QFlowBlockGenDlg::OnSetPipeBackColor(const QColor & nColor)   //设置管道背景色
{
    int nCount = ui->m_countspinBox->value(); //流动块总数
    ui->m_pipebackcolorbtn->setStyleSheet(QString("background:%1").arg(nColor.name()));
    int i = 0;
    nCount = nCount*3;

    emit DrawFlow();
}

void QFlowBlockGenDlg::OnSetFramColor(const QColor & nColor)       //设置边框色
{
    int nCount = ui->m_countspinBox->value(); //流动块总数
     ui->m_framcolorbtn->setStyleSheet(QString("background:%1").arg(nColor.name()));
    int i = 0;
    nCount = nCount*3;

    emit DrawFlow();
}

void QFlowBlockGenDlg::on_m_patterncmb_currentIndexChanged(int index) //样式选择
{
    if(!nInitFlag)
        return;
    int nCount = ui->m_countspinBox->value(); //流动块总数
    nCount = nCount*3;
    emit DrawFlow();
}

/****************************************************
 *双击打开对话框的时候调用该函数拆分item
 ***************************************************/
void QFlowBlockGenDlg::SplitItem(QGraphicsItem *pItem)
{
    QList<QGraphicsItem *> childitem;
    QGraphicsItem *item;
    childitem = pItem->childItems();
    int nSize = childitem.size();
    int i = 0;
    QRectItem *pRect;

    if(nSize < 2)
        return;

    for(i = 0; i < nSize; i ++)
    {
        item = childitem.at(i);
        pRect = dynamic_cast<QRectItem *>(item);
        pRectList.append(pRect);
    }
    emit DrawFlow();
}
bool QFlowBlockGenDlg::FlowBlockGenSave(FlowInfo &flow_st)
{
    //flow_st.id=ui->m_noedit->text();//控件ID

    QString str;
    //流动块前景色QString
    flow_st.nFForeColor=pwnd->ColorTOString(ui->m_flowfrontcolorbtn->palette().background().color());


    //流动块背景色QString
    flow_st.nFBackColor=pwnd->ColorTOString(ui->m_flowbackcolorbtn->palette().background().color());


    //管道前景色QString
    flow_st.nDForeColor=pwnd->ColorTOString(ui->m_pipefrontcolorbtn ->palette().background().color());


    //管道背景色QString
    flow_st.nDBackColor=pwnd->ColorTOString(ui->m_pipebackcolorbtn ->palette().background().color());


    //边框色QString
    flow_st.nFrameColor=pwnd->ColorTOString(ui->m_framcolorbtn ->palette().background().color());


    //样式short
    flow_st.eStyle=ui->m_patterncmb->currentIndex();

    //触发地址输入键盘
    if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("写入地址"),ui->Monitor_Address,0))
    {
        ui->Monitor_Address->setFocus();
        return false;
    }
    flow_st.triggerAdd = Monitor_Address_Keyboard;
    //触发地址接收值
    flow_st.nTriggerAddress=ui->Monitor_Address->text();

    //显示方式DIRECTIONS
    flow_st.eShowWay=(DIRECTIONS)RadioButton_direction_Group->checkedId();

    //流动方向DIRECTIONS
    flow_st.eFlowDirection=(DIRECTIONS)ui->m_drectioncmb->currentIndex();
    flow_st.sflowdirection=ui->m_drectioncmb->currentText();
    //流动块数short
    flow_st.nFlowNum=ui->m_countspinBox->value();

    //无边线bool
    flow_st.bSideLine=ui->m_noframcheck->isChecked();

    //使用触控地址把流动方向更改为反方向
    flow_st.bTouchAddress=ui->m_changdircheck->isChecked();
    if(flow_st.bTouchAddress){
        //触控地址输入键盘
        if(! pwnd->IsAddressCheckRight(TouchAddr,tr("写入地址"),ui->m_touchaddredit,0))
        {
            ui->m_touchaddredit->setFocus();
            return false;
        }
        flow_st.touchAdd = TouchAddr;
    }
    //触控地址接收值
    flow_st.eTouchAddress=ui->m_touchaddredit->text();
    //有效状态
    flow_st.nValidState=(int)RadioButtonState->checkedId();

    //流动方式（固定流动速度、动态流动速度）
    flow_st.eFlowSpeedType=(SPEED)FlowMode->checkedId();
    //固定流动速度选择(低、中、高)
    flow_st.eFixedFlowSpeed=(SPEED)FixupFlowSpeed->checkedId();
    if(flow_st.eFlowSpeedType==TRENDFLOWSPEED){
        //动态速度输入键盘
        if(! pwnd->IsAddressCheckRight(Flowspeedkeyboard,tr("写入地址"),ui->FlowSpeed,1))
        {
             ui->FlowSpeed->setFocus();
             return false;
         }
         flow_st.trendSpeed = Flowspeedkeyboard;
    }
     //触控地址接收值
     flow_st.nTrendFlowSpeed=ui->FlowSpeed->text();
}
void QFlowBlockGenDlg::Init(FlowBlockItem *pItem)
{

    nInitFlag = false; //初始化完成标志
    if(pItem)   //从Data 的 stringList中获取属性并设置
    {

        pRectList.clear();
        ui->m_radio1->setChecked(true);
        nFlowCount = pItem->m_flow.nFlowNum;                        //记录之前流动块
        SplitItem(pItem);
        //流动块前景色
        ui->m_flowfrontcolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->m_flow.nFForeColor).name()));
        //流动块背景色
        ui->m_flowbackcolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->m_flow.nFBackColor).name()));
        //管道前景色
        ui->m_pipefrontcolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->m_flow.nDForeColor).name()));
        //管道背景色
        ui->m_pipebackcolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->m_flow.nDBackColor).name()));
        //边框色
        ui->m_framcolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->m_flow.nFrameColor).name()));
        //样式
        ui->m_patterncmb->setCurrentIndex(pItem->m_flow.eStyle);
        //触发地址
        ui->Monitor_Address->setText(pItem->m_flow.triggerAdd.sShowAddr);
        //显示方式
        RadioButton_direction_Group->button((int)pItem->m_flow.eShowWay)->setChecked(true);

        ui->m_countspinBox->setValue(pItem->m_flow.nFlowNum);

         //pwnd->StringToKeyboard(Flowspeedkeyboard,(QString)pItem->m_flow.eFlowSpeedType);
         //ui->FlowSpeed->setText(Flowspeedkeyboard.sShowAddr);
        if(pItem->m_flow.eShowWay == LEVEL){
            nDirection=0;
            ui->m_drectioncmb->addItem(tr("向左")); //初始化流动方向
            ui->m_drectioncmb->addItem(tr("向右"));
        }else if(pItem->m_flow.eShowWay==VERTICAL){
            nDirection=1;
            ui->m_drectioncmb->addItem(tr("向上")); //初始化流动方向
            ui->m_drectioncmb->addItem(tr("向下"));
        }
        ui->m_drectioncmb->setCurrentIndex(pItem->m_flow.eFlowDirection);
        //反方向
        ui->m_changdircheck->setChecked(pItem->m_flow.bTouchAddress);
        on_m_changdircheck_clicked(pItem->m_flow.bTouchAddress);
       //反方向的触控地址
       ui->m_touchaddredit->setText(pItem->m_flow.touchAdd.sShowAddr);
       //有效状态
        RadioButtonState->button((int)pItem->m_flow.nValidState)->setChecked(true);
       //有无边线
       ui->m_noframcheck->setChecked(pItem->m_flow.bSideLine);
        //速度类型
        FlowMode->button((int)pItem->m_flow.eFlowSpeedType)->setChecked(true);
        //固定速度类型
       FixupFlowSpeed->button((int)pItem->m_flow.eFixedFlowSpeed)->setChecked(true);

       //动态速度地址
        ui->FlowSpeed->setText(pItem->m_flow.trendSpeed.sShowAddr);
       on_FixupFlowspeed_clicked();
        on_DynamicFlowSpeed_clicked();
      }
    else//初始化
    {
        nDirection = 0;                        //记录水平方向值
        nFlowCount = 3;                        //记录之前流动块
        ui->m_Hradio->setChecked(true);        //显示方式为水平方向
        ui->m_drectioncmb->addItem(tr("向左")); //初始化流动方向
        ui->m_drectioncmb->addItem(tr("向右"));
        ui->m_countspinBox->setRange(1,30);    //设置流动块的范围
        ui->m_countspinBox->setValue(3);       //流动块数
        ui->m_radio1->setChecked(true);
        ui->m_patterncmb->setCurrentIndex(5);
        ui->Monitor_Address->setFocus();
        ui->m_noframcheck->setChecked(true);


        ui->m_flowfrontcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(255,255,255).name()));
        ui->m_flowbackcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(255,0,0).name()));
        ui->m_pipefrontcolorbtn ->setStyleSheet( QString("background:%1").arg(QColor(255,255,255).name()));
        ui->m_pipebackcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(255,255,255).name()));
        ui->m_framcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));


        on_m_changdircheck_clicked(false);
        on_FixupFlowspeed_clicked();
        on_DynamicFlowSpeed_clicked();
     }
    nInitFlag = true; //初始化完成标志
}

void QFlowBlockGenDlg::on_Monitor_Address_Btn_clicked()
{
    QString addrStr = ui->Monitor_Address->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,0,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->Monitor_Address->setText(Monitor_Address_Keyboard.sShowAddr);
    }
    emit DrawFlow();
}

void QFlowBlockGenDlg::on_m_changdircheck_clicked(bool checked)
{
    if(checked)
    {
        ui->m_label1->setVisible(true);
        ui->m_label2->setVisible(true);
        ui->m_touchaddredit->setVisible(true);
        ui->m_touchbtn->setVisible(true);
        ui->m_radio0->setVisible(true);
        ui->m_radio1->setVisible(true);
        ui->m_touchaddredit->setText("LB0");
    }
    else
    {
        ui->m_label1->setVisible(false);
        ui->m_label2->setVisible(false);
        ui->m_touchaddredit->setVisible(false);
        ui->m_touchbtn->setVisible(false);
        ui->m_radio0->setVisible(false);
        ui->m_radio1->setVisible(false);
    }
}

void QFlowBlockGenDlg::on_m_touchbtn_clicked()
{
    QString addrStr = ui->m_touchaddredit->text();
    AddressInputDialog addressintputdlg_writeaddress(TouchAddr,addrStr,0,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_touchaddredit->setText(TouchAddr.sShowAddr);
    }
    emit DrawFlow();
}

void QFlowBlockGenDlg::on_FlowSpeedKeyboard_clicked()
{
    QString addrStr = ui->FlowSpeed->text();
    AddressInputDialog addressintputdlg_writeaddress(Flowspeedkeyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->FlowSpeed->setText(Flowspeedkeyboard.sShowAddr);
    }
    emit DrawFlow();
}

void QFlowBlockGenDlg::on_m_flowfrontcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_flowfrontcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetFlowFrontColor(const QColor &)));

}

void QFlowBlockGenDlg::on_m_flowbackcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_flowbackcolorbtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetFlowBackColor(const QColor &)));

}

void QFlowBlockGenDlg::on_m_pipefrontcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_pipefrontcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetPipeFrontColor(const QColor &)));

}

void QFlowBlockGenDlg::on_m_pipebackcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_pipebackcolorbtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetPipeBackColor(const QColor &)));

}

void QFlowBlockGenDlg::on_m_framcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_framcolorbtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetFramColor(const QColor &)));

}

void QFlowBlockGenDlg::on_FixupFlowspeed_clicked()
{
    bool bTemp=ui->FixupFlowspeed->isChecked();
    if(bTemp)
    {
        ui->low->setHidden(false);
        ui->high->setHidden(false);
        ui->middle->setHidden(false);
        ui->FlowSpeed->setHidden(true);
        ui->FlowSpeedKeyboard->setHidden(true);
        ui->dongtaifanwei->setHidden(true);
    }
    emit DrawFlow();
}

void QFlowBlockGenDlg::on_DynamicFlowSpeed_clicked()
{
    bool bTemp=ui->DynamicFlowSpeed->isChecked();
    if(bTemp)
    {
        ui->low->setHidden(true);
        ui->high->setHidden(true);
        ui->middle->setHidden(true);
        ui->FlowSpeed->setHidden(false);
        ui->FlowSpeedKeyboard->setHidden(false);
        ui->dongtaifanwei->setHidden(false);
        //ui->FlowSpeed->setText("LW0");
    }
    emit DrawFlow();
}
