#include "qtrendadisplay.h"
#include "ui_qtrendadisplay.h"
#include "../qprogectmanager.h"
#include "../mainwindow.h"

extern MainWindow *pwnd;

QTrendadisplay::QTrendadisplay(QWidget *parent):QWidget(parent),ui(new Ui::QTrendadisplay)
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
    //ui->spinBox_dataSampleNum->setMaximum(width);
    //ui->spinBox_dataSampleNum->setMinimum(0);

    //滚动样本数
    //if(ui->spinBox_rollSampleNum->value() > ui->spinBox_dataSampleNum->value())
    //{
    //    ui->spinBox_rollSampleNum->setValue(ui->spinBox_dataSampleNum->value());
    //}

    if(ui->checkBox_vertical->isChecked())
    {
        ui->spinBox_verticalMain->setEnabled(true);

        if(ui->checkBox_verticalSub->isChecked())//显示或者隐藏垂直次标尺
        {
            ui->spinBox_verticalSub->setEnabled(true);
        }
        else
        {
            ui->spinBox_verticalSub->setEnabled(false);
        }
    }
    else
    {
        ui->spinBox_verticalMain->setEnabled(false);
        ui->spinBox_verticalSub->setEnabled(false);
    }

    if(ui->checkBox_horiz->isChecked())
    {
        ui->spinBox_horizMain->setEnabled(true);

        if(ui->checkBox_horizSub->isChecked())//显示或者隐藏水平次标尺
        {
            ui->spinBox_horizSub->setEnabled(true);
        }
        else
        {
            ui->spinBox_horizSub->setEnabled(false);
        }
    }
    else
    {
        ui->spinBox_horizMain->setEnabled(false);
        ui->spinBox_horizSub->setEnabled(false);
    }
}

QTrendadisplay::~QTrendadisplay()
{
    delete ui;
}

void QTrendadisplay::on_spinBox_dataSampleNum_valueChanged(int value)//采样样本数
{
    /*if(value <= ui->spinBox_rollSampleNum->value())
    {
        ui->spinBox_dataSampleNum->setValue(ui->spinBox_rollSampleNum->value()+1);
    }

    m_nDataSample = ui->spinBox_dataSampleNum->value();*/
}

void QTrendadisplay::on_spinBox_rollSampleNum_valueChanged(int value)//滚动样本数
{
    if(value >= ui->spinBox_dataSampleNum->value())
    {
        ui->spinBox_rollSampleNum->setValue(ui->spinBox_dataSampleNum->value()-1);
    }

    m_nScrollSample = ui->spinBox_rollSampleNum->value();
}

void QTrendadisplay::on_comboBox_channelNum_currentIndexChanged(int index)//通道号
{
    
}

void QTrendadisplay::on_comboBox_showCondition_currentIndexChanged(int index)//显示条件
{
}

void QTrendadisplay::on_pushButton_showAddr_clicked()//地址按钮
{
    
}

void QTrendadisplay::on_lineEdit_showAddr_editingFinished()//地址
{
    
}

void QTrendadisplay::set_comboBox_chnnel_num(int begin, int total)//通道数量改变后的槽函数
{
    
}

void QTrendadisplay::Init(QTrendAttr *pItem)
{
    if(pItem)
    {
        m_bSelectVertMinor  = pItem->m_bSelectVertMinor;//是否显示垂直次标尺
        m_bSelectHorMinor   = pItem->m_bSelectHorMinor;	//是否显示水平次标尺
        m_bMainVer          = pItem->m_bMainVer;
        m_bMainHor          = pItem->m_bMainHor;
        m_nDataSample       = pItem->m_nDataSample;	//数据样本数
        m_nScrollSample     = pItem->m_nScrollSample;	//滚动样本数
        m_nVertMajorScale   = pItem->m_nVertMajorScale;	//垂直主标尺
        m_nVertMinorScale   = pItem->m_nVertMinorScale;	//垂直次标尺
        m_nHorMajorScale    = pItem->m_nHorMajorScale;	//水平主标尺
        m_nHorMinorScale    = pItem->m_nHorMinorScale;	//水平次标尺
        m_bGrade            = pItem->m_bGrade;        //是否需要网格
        m_nVerColor         = pItem->m_nVerColor;     //水平网格颜色
        m_nHorColor         = pItem->m_nHorColor;     //垂直网格颜色
        m_nBoradColor       = pItem->m_nBoradColor;	//边框颜色
        m_nScaleColor       = pItem->m_nScaleColor;	//标尺颜色
        m_nGraphColor       = pItem->m_nGraphColor;	//图表区颜色
        m_alpha             = pItem->m_alpha;

    }
    else
    {
        m_bSelectVertMinor  = false;    //是否显示垂直次标尺
        m_bSelectHorMinor   = false;	//是否显示水平次标尺
        m_bMainVer          = true;
        m_bMainHor          = true;
        m_nDataSample       = 100;	//数据样本数
        m_nScrollSample     = 9;	//滚动样本数
        m_nVertMajorScale   = 2;	//垂直主标尺
        m_nVertMinorScale   = 5;	//垂直次标尺
        m_nHorMajorScale    = 2;	//水平主标尺
        m_nHorMinorScale    = 5;	//水平次标尺
        m_bGrade            = true;                   //是否需要网格
        m_nVerColor         = QColor(192, 192, 192);  //水平网格颜色
        m_nHorColor         = QColor(192, 192, 192);  //垂直网格颜色
        m_nBoradColor       = QColor(0, 0, 255);	//边框颜色
        m_nScaleColor       = QColor(0, 255, 0);	//标尺颜色
        m_nGraphColor       = QColor(0, 0, 255);	//图表区颜色
        m_alpha             = 255;
    }

    ui->spinBox_dataSampleNum->setValue(m_nDataSample);
    ui->spinBox_rollSampleNum->setValue(m_nScrollSample);
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
    ui->spinBox_verticalSub->setEnabled(m_bSelectVertMinor);
    ui->spinBox_horizSub->setEnabled(m_bSelectHorMinor);
    set_TextProVisible(false);
    //ui->spin_alpha->setValue(m_alpha);
    //ui->spin_alpha->hide();
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
void QTrendadisplay::InitXY(XYtrend *pItem)
{
    if(pItem)
    {
        m_bSelectVertMinor  = pItem->m_bSelectVertMinor;//是否显示垂直次标尺
        m_bSelectHorMinor   = pItem->m_bSelectHorMinor;	//是否显示水平次标尺
        m_bMainVer          = pItem->m_bMainVer;
        m_bMainHor          = pItem->m_bMainHor;
        //m_nDataSample       = pItem->m_nDataSample;	//数据样本数
        //m_nScrollSample     = pItem->m_nScrollSample;	//滚动样本数
        m_nVertMajorScale   = pItem->m_nVertMajorScale;	//垂直主标尺
        m_nVertMinorScale   = pItem->m_nVertMinorScale;	//垂直次标尺
        m_nHorMajorScale    = pItem->m_nHorMajorScale;	//水平主标尺
        m_nHorMinorScale    = pItem->m_nHorMinorScale;	//水平次标尺
        m_bGrade            = pItem->m_bGrade;        //是否需要网格
        m_nVerColor         = pItem->m_nVerColor;     //水平网格颜色
        m_nHorColor         = pItem->m_nHorColor;     //垂直网格颜色
        m_nBoradColor       = pItem->m_nBoradColor;	//边框颜色
        m_nScaleColor       = pItem->m_nScaleColor;	//标尺颜色
        m_nGraphColor       = pItem->m_nGraphColor;	//图表区颜色
        m_alpha             = pItem->m_alpha;
        m_textColor         = pItem->m_TextColor;
        m_textSize          = pItem->m_textSize;
        qDebug()<<"m_textSize" << m_textSize;

    }
    else
    {
        m_bSelectVertMinor  = false;    //是否显示垂直次标尺
        m_bSelectHorMinor   = false;	//是否显示水平次标尺
        m_bMainVer          = true;
        m_bMainHor          = true;
        m_nDataSample       = 100;	//数据样本数
        m_nScrollSample     = 9;	//滚动样本数
        m_nVertMajorScale   = 2;	//垂直主标尺
        m_nVertMinorScale   = 5;	//垂直次标尺
        m_nHorMajorScale    = 2;	//水平主标尺
        m_nHorMinorScale    = 5;	//水平次标尺
        m_bGrade            = true;                   //是否需要网格
        m_nVerColor         = QColor(192, 192, 192);  //水平网格颜色
        m_nHorColor         = QColor(192, 192, 192);  //垂直网格颜色
        m_nBoradColor       = QColor(0, 0, 255);	//边框颜色
        m_nScaleColor       = QColor(0, 255, 0);	//标尺颜色
        m_nGraphColor       = QColor(0, 0, 255);	//图表区颜色
        m_alpha             = 255;
        m_textColor         = QColor(0, 0, 0);;
        m_textSize          = 10;
    }

    ui->spinBox_dataSampleNum->setValue(m_nDataSample);
    ui->spinBox_rollSampleNum->setValue(m_nScrollSample);
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
    ui->pushButton->setStyleSheet(QString("background:%1").arg(m_textColor.name()));
    ui->spinBox_verticalSub->setEnabled(m_bSelectVertMinor);
    ui->spinBox_horizSub->setEnabled(m_bSelectHorMinor);
    ui->spinBox_rollSampleNum_2->setValue(m_textSize);
    set_TextProVisible(true);;

}
void QTrendadisplay::on_spinBox_verticalMain_valueChanged(int value)//垂直主标尺
{
    m_nVertMajorScale = value;
}

void QTrendadisplay::on_spinBox_horizMain_valueChanged(int value)//水平主标尺
{
    m_nHorMajorScale = value;
}

int QTrendadisplay::getAlpha()
{
    //return ui->spin_alpha->value();
}

void QTrendadisplay::on_checkBox_verticalSub_clicked(bool checked)//是否显示垂直次标尺
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

void QTrendadisplay::on_checkBox_horizSub_clicked(bool checked)//是否显示水平次标尺
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

void QTrendadisplay::on_spinBox_verticalSub_valueChanged(int value)//垂直次标尺
{
    m_nVertMinorScale = value;
}

void QTrendadisplay::on_spinBox_horizSub_valueChanged(int value)//水平次标尺
{
    m_nHorMinorScale = value;
}

void QTrendadisplay::on_pushButton_frameColor_clicked()//边框颜色
{
	ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
	pwnd->OnAddColorDlg(ui->pushButton_frameColor, colorPicker);

	connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_frameColor(const QColor &)));
}

void QTrendadisplay::set_pushButton_frameColor(const QColor & Color)
{
	ui->pushButton_frameColor->setStyleSheet(QString("background:%1").arg(Color.name()));
	m_nBoradColor = Color;
}

void QTrendadisplay::on_pushButton_rulerColor_clicked()//标尺颜色
{
	ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
	pwnd->OnAddColorDlg(ui->pushButton_rulerColor, colorPicker);

	connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_rulerColor(const QColor &)));
}

void QTrendadisplay::set_pushButton_rulerColor(const QColor & Color)
{
	ui->pushButton_rulerColor->setStyleSheet(QString("background:%1").arg(Color.name()));
	m_nScaleColor = Color;	//标尺颜色
}

void QTrendadisplay::on_pushButton_tableColor_clicked()//图表区颜色
{
	ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
	pwnd->OnAddColorDlg(ui->pushButton_tableColor, colorPicker);

	connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_tableColor(const QColor &)));
}

void QTrendadisplay::set_pushButton_tableColor(const QColor & Color)
{
	ui->pushButton_tableColor->setStyleSheet(QString("background:%1").arg(Color.name()));
	m_nGraphColor = Color;
}

void QTrendadisplay::on_groupBox_grade_clicked(bool checked)
{
	m_bGrade = checked;
	//ui->groupBox_grade->setEnabled(checked);
	ui->pushButton_horGradeColor->setEnabled(checked);
	ui->pushButton_verGradeColor->setEnabled(checked);
}

void QTrendadisplay::on_pushButton_verGradeColor_clicked()
{
	ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
	pwnd->OnAddColorDlg(ui->pushButton_verGradeColor, colorPicker);

	connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_verGradeColor(const QColor &)));
}

void QTrendadisplay::on_pushButton_horGradeColor_clicked()
{
	ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
	pwnd->OnAddColorDlg(ui->pushButton_horGradeColor, colorPicker);

	connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_horGradeColor(const QColor &)));
}

void QTrendadisplay::set_pushButton_verGradeColor(const QColor & Color)
{
	ui->pushButton_verGradeColor->setStyleSheet(QString("background:%1").arg(Color.name()));
	m_nVerColor = Color;	//垂直网格颜色
}

void QTrendadisplay::set_pushButton_horGradeColor(const QColor & Color)
{
	ui->pushButton_horGradeColor->setStyleSheet(QString("background:%1").arg(Color.name()));
	m_nHorColor = Color;	//水平网格颜色
}

void QTrendadisplay::on_checkBox_vertical_clicked(bool checked)
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

void QTrendadisplay::on_checkBox_horiz_clicked(bool checked)
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

void QTrendadisplay::on_spinBox_dataSampleNum_editingFinished()
{
    int value = ui->spinBox_dataSampleNum->value();
    if(value <= ui->spinBox_rollSampleNum->value())
    {
        ui->spinBox_dataSampleNum->setValue(ui->spinBox_rollSampleNum->value()+1);
    }

    m_nDataSample = ui->spinBox_dataSampleNum->value();
}

void QTrendadisplay::on_pushButton_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
    pwnd->OnAddColorDlg(ui->pushButton, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_BtnTextColor(const QColor &)));

}
void QTrendadisplay::set_BtnTextColor(const QColor &Color)
{
    ui->pushButton->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_textColor = Color;	//水平网格颜色
}
void QTrendadisplay::set_TextProVisible(bool bValue)
{
    ui->groupBox_2->setVisible(bValue);
    ui->groupBox->setVisible(!bValue);
}
int QTrendadisplay::textSize()
{
    return ui->spinBox_rollSampleNum_2->value();
}
