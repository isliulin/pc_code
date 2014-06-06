#include "scalesdlg.h"
#include "ui_scalesdlg.h"
#include "view/qlineitem.h"
#include "view/qsimpletextitem.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

ScalesDlg::ScalesDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScalesDlg)
{
    ui->setupUi(this);
    bInitFlag=false;
    pScene = new QGraphicsScene(this);
    pDirection = new QButtonGroup(this); //方向
    pDirection->addButton(ui->m_radio1,1);//左
    pDirection->addButton(ui->m_radio2,2);//右
    pDirection->addButton(ui->m_radio3,3);//上
    pDirection->addButton(ui->m_radio4,4);//下
    QIntValidator* aValidator = new QIntValidator(this);
    ui->m_maxedit->setValidator(aValidator);
    ui->m_minedit->setValidator(aValidator);
    connect(pDirection, SIGNAL(buttonClicked(int)),this,SLOT(OnScaleDirectionChange(int)));

}

ScalesDlg::~ScalesDlg()
{
    if(pDirection)
    {
        delete pDirection;
        pDirection=NULL;
    }
    if(pScene)
    {
        delete pScene;
        pScene=NULL;
    }
    delete ui;
}

void ScalesDlg::InitParament()
{
    QStringList list;

    ui->m_linecolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    ui->m_textcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    //ui->m_showscalecheck->setChecked(true);
    ui->m_showtextcheck->setChecked(true);
    ui->m_fontsizecmb->setCurrentIndex(5);
    ui->m_minedit->setText(tr("0"));
    ui->m_maxedit->setText(tr("100"));
    ui->m_radio2->setChecked(true);

    list << tr("向上") << tr("向下");
    ui->m_textdirectioncmb->addItems(list);
    ui->m_textdirectioncmb->setCurrentIndex(0);

    bInitFlag = true;
}

void ScalesDlg::OnSetLineColor(const QColor & currentColor) //设置线条颜色
{
    ui->m_linecolorbtn->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::OnSetTextColor(const QColor & currentColor) //设置文本颜色
{
    ui->m_textcolorbtn->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::OnScaleDirectionChange(int nIndex)
{
    ui->m_textdirectioncmb->clear();
    QStringList list;
    switch(nIndex)
    {
    case 1: //方向向左
        list << tr("向上") << tr("向下");
        break;
    case 2: //方向向右
        list << tr("向上") << tr("向下");
        break;
    case 3: //方向向上
        list << tr("向左") << tr("向右");
        break;
    case 4: //方向向下
        list << tr("向左") << tr("向右");
        break;
    default:
        break;
    }
    ui->m_textdirectioncmb->addItems(list);

    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_showscalecheck_clicked(bool checked)//显示坐标轴
{
    if(checked)
    {
        ui->label_3->setEnabled(true);
        ui->label_4->setEnabled(true);
        ui->m_mainspin->setEnabled(true);
        ui->m_subspin->setEnabled(true);
    }
    else
    {
        ui->label_3->setEnabled(false);
        ui->label_4->setEnabled(false);
        ui->m_mainspin->setEnabled(false);
        ui->m_subspin->setEnabled(false);
    }

    if(!bInitFlag)
        return;
    emit DrawScales();
}



void ScalesDlg::on_m_textdirectioncmb_currentIndexChanged(int index) //文本方向
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_mainspin_valueChanged(int )//主刻度
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_subspin_valueChanged(int )//次刻度
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_pointnumcmb_highlighted(int index)//小数位数
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_minedit_textChanged(QString )
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_maxedit_textChanged(QString )
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_fontsizecmb_currentIndexChanged(int index)//字体大小
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_pointnumcmb_currentIndexChanged(int index)
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_showtextcheck_clicked(bool checked)
{
    if(checked)
    {
        ui->label_5->setEnabled(true);
        ui->label_6->setEnabled(true);
        ui->label_7->setEnabled(true);
        ui->label_8->setEnabled(true);
        ui->m_minedit->setEnabled(true);
        ui->m_maxedit->setEnabled(true);
        ui->m_fontsizecmb->setEnabled(true);
        ui->m_pointnumcmb->setEnabled(true);
    }
    else
    {
        ui->label_5->setEnabled(false);
        ui->label_6->setEnabled(false);
        ui->label_7->setEnabled(false);
        ui->label_8->setEnabled(false);
        ui->m_minedit->setEnabled(false);
        ui->m_maxedit->setEnabled(false);
        ui->m_fontsizecmb->setEnabled(false);
        ui->m_pointnumcmb->setEnabled(false);
    }

    if(!bInitFlag)
        return;

//    emit DrawScales();
}

void ScalesDlg::SaveGeneralPage(Calibration &m_calibration)
{
    QColor mColor;
    //线条颜色
    mColor = ui->m_linecolorbtn->palette().background().color();
    m_calibration.nLineColor=pwnd->ColorTOString(mColor);
    //文本颜色
    mColor = ui-> m_textcolorbtn ->palette().background().color();
    m_calibration.nTextColor=pwnd->ColorTOString(mColor);
    //刻度方向
    m_calibration.nCalibrationDirection = pDirection->checkedId();
    //文本方向
    m_calibration.nNumberIncreaseDirection = ui->m_textdirectioncmb->currentIndex();
    m_calibration.direction=ui->m_textdirectioncmb->currentText();
    //主刻度
    m_calibration.nMainNumberCount = ui->m_mainspin->value();
    //次刻度
    m_calibration.nNextNumberCount = ui->m_subspin->value();
    //是否显示文本
    m_calibration.bShowText = ui->m_showtextcheck->isChecked();
    //最小值
    m_calibration.nMaxNumber = ui->m_maxedit->text();
    //最大值
    m_calibration.nMinNumber = ui->m_minedit->text();
    //字体大小
    m_calibration.nTextSize = ui->m_fontsizecmb->currentIndex();
    m_calibration.stextsize = ui->m_fontsizecmb->currentText();
    //小数位数
    m_calibration.nDecimalCount = ui->m_pointnumcmb->currentIndex();
}

void ScalesDlg::DoubleClickInit(CalibrationItem *pItem)
{
    QColor mColor;
    if(pItem)   //从Data 的 stringList中获取属性并设置
    {
        mColor = pwnd->StringTOColor(pItem->m_calibrations.nLineColor);
        ui->m_linecolorbtn->setStyleSheet( QString("background:%1").arg(mColor.name()));

        mColor = pwnd->StringTOColor(pItem->m_calibrations.nTextColor);
        ui-> m_textcolorbtn->setStyleSheet( QString("background:%1").arg(mColor.name()));

        QAbstractButton *btn=pDirection->button(pItem->m_calibrations.nCalibrationDirection);
        if(btn)
        {
            btn->setChecked(true);
        }
        OnScaleDirectionChange(pItem->m_calibrations.nCalibrationDirection);
        ui->m_textdirectioncmb->setCurrentIndex(pItem->m_calibrations.nNumberIncreaseDirection);

        ui->m_mainspin->setValue(pItem->m_calibrations.nMainNumberCount);

        ui->m_subspin->setValue(pItem->m_calibrations.nNextNumberCount);

        ui->m_showtextcheck->setChecked(pItem->m_calibrations.bShowText);

        ui->m_minedit->setText(pItem->m_calibrations.nMinNumber);
        ui->m_maxedit->setText(pItem->m_calibrations.nMaxNumber);

        ui->m_fontsizecmb->setCurrentIndex(pItem->m_calibrations.nTextSize);

        ui->m_pointnumcmb->setCurrentIndex(pItem->m_calibrations.nDecimalCount);

        on_m_showtextcheck_clicked(pItem->m_calibrations.bShowText);

    }
    bInitFlag = true;
}

void ScalesDlg::on_m_linecolorbtn_clicked()
{

    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_linecolorbtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetLineColor(const QColor &)));
}

void ScalesDlg::on_m_textcolorbtn_clicked()
{

    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_textcolorbtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetTextColor(const QColor &)));
}

void ScalesDlg::on_m_showtextcheck_clicked()
{
    emit DrawScales();
}
