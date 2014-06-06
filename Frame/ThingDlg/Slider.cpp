#include "Slider.h"
#include "ui_Slider.h"
#include "view/qdrawgraphics.h"
#include "Frame/ThingDlg/SliderDlg.h"
#include "view/switchitem.h"
#include  "Frame\MainWindow.h"
extern MainWindow  *pwnd;
Slider::Slider(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Slider)
{
    ui->setupUi(this);

    oId = -1;
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    //建场景
    pScene = new QGraphicsScene(this);
    ui->MainView->setScene(pScene);
    ui->MainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QGraphicsItem *Item;
    tabWidget = new QTabWidget();
    pGeneralDlg = new SliderGeneralDlg;
    ui->tabWidget->addTab(pGeneralDlg, tr("外观设置"));
    pSecurityWight = new SecurityWidget;
    ui->tabWidget->addTab(pSecurityWight,tr("权限设置"));

    connect(pGeneralDlg, SIGNAL(ReDrawSlider()),this, SLOT(OnReDrawSlider()));

    if(pItem)
    {
        Item = dynamic_cast<SliderItem *> (pItem)->Clone();
        InitAllProperty(dynamic_cast<SliderItem *> (Item));
        pGeneralDlg->DoubleClickInit(dynamic_cast<SliderItem *> (Item));
    }
    else
    {
        InitAllProperty(NULL);
        pSecurityWight->init(0);
    }
    this->setWindowTitle(tr("滑动模拟量开关"));
    ui->accept->setFocus(Qt::MouseFocusReason);
}

Slider::~Slider()
{
    if(pGeneralDlg)
    {
        delete pGeneralDlg;
        pGeneralDlg = NULL;
    }
    delete ui;
}

void Slider::InitAllProperty(SliderItem *pItem)
{
    if(pItem){
        pCopyItem = pItem;
        pScene->clear();
        pScene->addItem(pCopyItem);
        pBaseItem = new QGroupItem(pCopyItem);
        oId = pItem->id();
        ui->spinBox->setValue(oId);

        switch(pItem->m_slider.direction)
        {
        case 1: //向上
        case 2: //向下
            pBaseItem->SetHeigth(55);
            pBaseItem->SetWidth(150);
            break;
        case 3: //向左
        case 4: //向右
            pBaseItem->SetHeigth(150);
            pBaseItem->SetWidth(55);
            break;
        }
        pSecurityWight->init(pItem);

    }else{

        pGeneralDlg->InitParament();
        ui->spinBox->setValue(pwnd->getNewId());
    }
}

void Slider::OnReDrawSlider() //重绘滑动块
{
    pScene->clear();
    SliderItem *slider=new SliderItem;
    slider->m_slider.rectColor = pwnd->ColorTOString(pGeneralDlg->ui->m_backcolorbtn->palette().background().color());//背景色

    slider->m_slider.slideBarColor = pwnd->ColorTOString(pGeneralDlg->ui->m_linecolorbtn->palette().background().color());//滑轨色

    slider->m_slider.fingerBackColor = pwnd->ColorTOString(pGeneralDlg->ui->m_bkcolorbtn ->palette().background().color());//指标背景色

    slider->m_slider.fingerLineColor = pwnd->ColorTOString(pGeneralDlg->ui->m_frmcolorbtn ->palette().background().color());//指标边框色

    slider->m_slider.nPosition=pGeneralDlg->RadioButton->checkedId();//位置

    switch(slider->m_slider.nPosition)
    {
    case 1: //向上
    case 2: //向下
        slider->m_slider.direction=pGeneralDlg->ui->m_directcmb->currentIndex();//方向
        break;
    case 3: //向左
    case 4: //向右
        slider->m_slider.direction=pGeneralDlg->ui->m_directcmb->currentIndex();//方向
        break;
    }


    //刻度页面
    slider->m_slider.isShowCalibration=pGeneralDlg->ui->m_displaycheck->isChecked();//是否显现

    slider->m_slider.nCalibrationColor=pwnd->ColorTOString(pGeneralDlg->ui->m_colorbtn->palette().background().color());//指针颜色

    slider->m_slider.nMaxNumber=pGeneralDlg->ui->m_mainscalspin->value();//主刻度数

    slider->m_slider.nMinNumber=pGeneralDlg->ui->m_subscalspin->value();//副刻度数

    slider->m_slider.bShowText=pGeneralDlg->ui->m_scalemarkcheck->isChecked();//刻度标示

    slider->m_slider.nTextSize=pGeneralDlg->ui->m_fontsizecmb->currentText().toInt();//字体大小

    slider->m_slider.nCalibrationMin=pGeneralDlg->ui->m_minedit_2->text();//最小值;

    slider->m_slider.nCalibrationMax=pGeneralDlg->ui->m_maxedit_2->text();//最大值;

    slider->m_slider.nDecimalCount=pGeneralDlg->ui->m_pointnumberspin->value();//小数位数

    SliderDlg *dlg=new SliderDlg;
    this->pCopyItem=dlg->DrawSlider(slider);
    this->pScene->clear();
    this->pScene->addItem(pCopyItem);
    pCopyItem->setPos(QPointF(0,0)-pCopyItem->sceneBoundingRect().topLeft());
}



void Slider::on_accept_clicked()
{
    bool isFlag=pGeneralDlg->SaveGeneralPage(m_slider);
    if(!isFlag)
        return;
    this->pCopyItem->onSaveSlider(m_slider);


    if(!pSecurityWight->Save())
    {
        return;
    }
    this->pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    this->pCopyItem->onSecurityPro(sproperty);
    this->pCopyItem->setId(ui->spinBox->value());
    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return ;
    }

    QDialog::accept();
}

void Slider::on_cancel_clicked()
{
    this->close();
}

void Slider::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_SLIDER);
}
