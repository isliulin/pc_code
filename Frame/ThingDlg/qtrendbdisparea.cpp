#include "qtrendbdisparea.h"
#include "ui_qtrendbdisparea.h"
#include "../mainwindow.h"

extern MainWindow *pwnd;

QTrendbDispArea::QTrendbDispArea(QWidget *parent):QWidget(parent),ui(new Ui::QTrendbDispArea)
{
    ui->setupUi(this);

    //数据样本数，根据分辨率来确定
    int width;
    if(0 == pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth)
    {
        width = 799;
    }
    else
    {
        width = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth - 1;
    }
    //int width = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth - 1;
    ui->spinBox_dataSampleNum->setMaximum(width);
    ui->spinBox_dataSampleNum->setMinimum(2);

    if(ui->checkBox_verticalSub->isChecked())//显示或者隐藏垂直次标尺
    {
        ui->spinBox_verticalSub->setEnabled(true);
    }
    else
    {
        ui->spinBox_verticalSub->setEnabled(false);
    }

    if(ui->checkBox_horizSub->isChecked())//显示或者隐藏水平次标尺
    {
        ui->spinBox_horizSub->setEnabled(true);
    }
    else
    {
        ui->spinBox_horizSub->setEnabled(false);
    }
}

QTrendbDispArea::~QTrendbDispArea()
{
    delete ui;
}

void QTrendbDispArea::on_spinBox_dataSampleNum_valueChanged(int value)//数据样本数
{
     m_nDataSample = value;
}

void QTrendbDispArea::on_spinBox_verticalMain_valueChanged(int value)//垂直主标尺
{
    m_nVertMajorScale = value;
}

void QTrendbDispArea::on_spinBox_horizMain_valueChanged(int value)//水平主标尺
{
    m_nHorMajorScale = value;
}

void QTrendbDispArea::on_checkBox_verticalSub_clicked(bool checked)//垂直次标尺,是否可用
{
    if(checked)
    {
        ui->spinBox_verticalSub->setEnabled(true);
    }
    else
    {
        ui->spinBox_verticalSub->setEnabled(false);
    }

    m_bSelectVertMinor = checked;
}

void QTrendbDispArea::on_checkBox_horizSub_clicked(bool checked)//水平次标尺,是否可用
{
    if(checked)
    {
        ui->spinBox_horizSub->setEnabled(true);
    }
    else
    {
        ui->spinBox_horizSub->setEnabled(false);
    }

    m_bSelectHorMinor = checked;
}

void QTrendbDispArea::on_spinBox_verticalSub_valueChanged(int value)//垂直次标尺
{
    m_nVertMinorScale = value;
}

void QTrendbDispArea::on_spinBox_horizSub_valueChanged(int value)//水平次标尺
{
    m_nHorMinorScale = value;
}

void QTrendbDispArea::Init(QTrendDataGroupAttr *pItem)//
{
    if(pItem)
    {
        m_bSelectVertMinor  = pItem->m_bSelectVertMinor;//是否显示垂直次标尺
        m_bSelectHorMinor   = pItem->m_bSelectHorMinor;	//是否显示水平次标尺
        m_bMainVer          = pItem->m_bMainVer;         //是否显示垂直主标尺
        m_bMainHor          = pItem->m_bMainHor;         //是否显示水平主标
        m_nDataSample       = pItem->m_nDataSample;	//数据样本数
        m_nVertMajorScale   = pItem->m_nVertMajorScale;	//垂直主标尺
        m_nVertMinorScale   = pItem->m_nVertMinorScale;	//垂直次标尺
        m_nHorMajorScale    = pItem->m_nHorMajorScale;	//水平主标尺
        m_nHorMinorScale    = pItem->m_nHorMinorScale;	//水平次标尺

        m_bGrade      = pItem->m_bGrade;        //是否需要网格
        m_nVerColor   = pItem->m_nVerColor;     //水平网格颜色
        m_nHorColor   = pItem->m_nHorColor;     //垂直网格颜色
        m_nBoradColor = pItem->m_nBoradColor;	//边框颜色
        m_nScaleColor = pItem->m_nScaleColor;	//标尺颜色
        m_nGraphColor = pItem->m_nGraphColor;	//图表区颜色
        m_nMarkedColor= pItem->m_nMarkedColor;  //标注颜色
        m_nFontSize   = pItem->m_nFontSize;
        m_alpha       = pItem->m_alpha;
    }
    else
    {
        m_bSelectVertMinor  = false;    //是否显示垂直次标尺
        m_bSelectHorMinor   = false;	//是否显示水平次标尺
        m_bMainVer          = true;     //是否显示垂直主标尺
        m_bMainHor          = true;     //是否显示水平主标
        m_nDataSample       = 10;	//数据样本数
        m_nVertMajorScale   = 2;	//垂直主标尺
        m_nVertMinorScale   = 5;	//垂直次标尺
        m_nHorMajorScale    = 2;	//水平主标尺
        m_nHorMinorScale    = 5;	//水平次标尺

        m_bGrade            = true;                   //是否需要网格
        m_nVerColor         = QColor(192, 192, 192);  //水平网格颜色
        m_nHorColor         = QColor(192, 192, 192);  //垂直网格颜色
        m_nBoradColor       = QColor(0, 0, 255);	//边框颜色
        m_nScaleColor       = QColor(0, 255, 0);	//标尺颜色
        m_nMarkedColor      = QColor(0, 0, 0);	//标尺颜色
        m_nGraphColor       = QColor(0, 0, 255);	//图表区颜色
        m_nFontSize         = 16;
        m_alpha             = 255;
    }

    ///////////////////////////ui/////////////////////////
    ui->spinBox_dataSampleNum->setValue(m_nDataSample);
    ui->spinBox_verticalMain->setValue(m_nVertMajorScale);
    ui->spinBox_horizMain->setValue(m_nHorMajorScale);
    ui->spinBox_verticalSub->setValue(m_nVertMinorScale);
    ui->spinBox_horizSub->setValue(m_nHorMinorScale);
    ui->checkBox_verticalSub->setChecked(m_bSelectVertMinor);
    ui->checkBox_horizSub->setChecked(m_bSelectHorMinor);
    ui->checkBox_vertical->setChecked(m_bMainVer);
    ui->checkBox_horiz->setChecked(m_bMainHor);

    ui->pushButton_verGradeColor->setStyleSheet(QString("background:%1").arg(m_nVerColor.name()));
    ui->pushButton_horGradeColor->setStyleSheet(QString("background:%1").arg(m_nHorColor.name()));
    ui->groupBox_grade->setChecked(m_bGrade);
    ui->pushButton_frameColor->setStyleSheet(QString("background:%1").arg(m_nBoradColor.name()));
    ui->pushButton_rulerColor->setStyleSheet(QString("background:%1").arg(m_nScaleColor.name()));
    ui->pushButton_tableColor->setStyleSheet(QString("background:%1").arg(m_nGraphColor.name()));
    ui->pushButton_markColor->setStyleSheet(QString("background:%1").arg(m_nMarkedColor.name()));

    ui->spinBox_verticalSub->setEnabled(m_bSelectVertMinor);
    ui->spinBox_horizSub->setEnabled(m_bSelectHorMinor);
    ui->spinBox_fontSize->setValue(m_nFontSize);
    ui->spin_alpha->setValue(m_alpha);
    
    /*if(m_bMainVer)
    {
        ui->spinBox_verticalMain->setEnabled(true);
        ui->checkBox_verticalSub->setEnabled(true);
        ui->spinBox_verticalSub->setEnabled(m_bSelectVertMinor);
    }
    else
    {
        ui->spinBox_verticalMain->setEnabled(false);
        ui->checkBox_verticalSub->setEnabled(false);
        ui->spinBox_verticalSub->setEnabled(false);
    }

    if(m_bMainHor)
    {
        ui->spinBox_horizMain->setEnabled(true);
        ui->checkBox_horizSub->setEnabled(true);
        ui->spinBox_horizSub->setEnabled(m_bSelectHorMinor);
    }
    else
    {
        ui->spinBox_horizMain->setEnabled(false);
        ui->checkBox_horizSub->setEnabled(false);
        ui->spinBox_horizSub->setEnabled(false);
    }*/
}

short QTrendbDispArea::getFontSize()
{
    return ui->spinBox_fontSize->value();
}
int QTrendbDispArea::getAlpha()
{
    return ui->spin_alpha->value();
}

void QTrendbDispArea::on_pushButton_frameColor_clicked()//边框颜色
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_frameColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_frameColor(const QColor &)));
}

void QTrendbDispArea::set_pushButton_frameColor(const QColor & Color)
{
    ui->pushButton_frameColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nBoradColor = Color;
}

void QTrendbDispArea::on_pushButton_rulerColor_clicked()//标尺颜色
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_rulerColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_rulerColor(const QColor &)));
}

void QTrendbDispArea::set_pushButton_rulerColor(const QColor & Color)
{
    ui->pushButton_rulerColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nScaleColor = Color;	//标尺颜色
}

void QTrendbDispArea::on_pushButton_tableColor_clicked()//图表区颜色
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_tableColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_tableColor(const QColor &)));
}

void QTrendbDispArea::set_pushButton_tableColor(const QColor & Color)
{
    ui->pushButton_tableColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nGraphColor = Color;
}

void QTrendbDispArea::on_groupBox_grade_clicked(bool checked)
{
    m_bGrade = checked;
    //ui->groupBox_grade->setEnabled(checked);
    ui->pushButton_horGradeColor->setEnabled(checked);
    ui->pushButton_verGradeColor->setEnabled(checked);
}

void QTrendbDispArea::on_pushButton_verGradeColor_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
    pwnd->OnAddColorDlg(ui->pushButton_verGradeColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_verGradeColor(const QColor &)));
}

void QTrendbDispArea::on_pushButton_horGradeColor_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
    pwnd->OnAddColorDlg(ui->pushButton_horGradeColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_horGradeColor(const QColor &)));
}

void QTrendbDispArea::set_pushButton_verGradeColor(const QColor & Color)
{
    ui->pushButton_verGradeColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nVerColor = Color;	//垂直网格颜色
}

void QTrendbDispArea::set_pushButton_horGradeColor(const QColor & Color)
{
    ui->pushButton_horGradeColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nHorColor = Color;	//水平网格颜色
}



void QTrendbDispArea::set_pushButton_markColor(const QColor & Color)
{
    ui->pushButton_markColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nMarkedColor = Color;	//水平网格颜色
    qDebug() << "m_nMarkedColor" << Color;
}

void QTrendbDispArea::on_pushButton_markColor_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_markColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_markColor(const QColor &)));
}

void QTrendbDispArea::on_checkBox_vertical_clicked(bool checked)
{
    m_bMainVer = checked;
    /*if(checked)
    {
        ui->spinBox_verticalMain->setEnabled(true);
        ui->checkBox_verticalSub->setEnabled(true);
        ui->spinBox_verticalSub->setEnabled(m_bSelectVertMinor);
    }
    else
    {
        ui->spinBox_verticalMain->setEnabled(false);
        ui->checkBox_verticalSub->setEnabled(false);
        ui->spinBox_verticalSub->setEnabled(false);
    }*/
}

void QTrendbDispArea::on_checkBox_horiz_clicked(bool checked)
{
    m_bMainHor = checked;
    /*if(checked)
    {
        ui->spinBox_horizMain->setEnabled(true);
        ui->checkBox_horizSub->setEnabled(true);
        ui->spinBox_horizSub->setEnabled(m_bSelectHorMinor);
    }
    else
    {
        ui->spinBox_horizMain->setEnabled(false);
        ui->checkBox_horizSub->setEnabled(false);
        ui->spinBox_horizSub->setEnabled(false);
    }*/
}
