#include "qtrendadisplay.h"
#include "ui_qtrendadisplay.h"
#include "../qprogectmanager.h"
#include "../mainwindow.h"

extern MainWindow *pwnd;

QTrendadisplay::QTrendadisplay(QWidget *parent):QWidget(parent),ui(new Ui::QTrendadisplay)
{
    ui->setupUi(this);

    //���������������ݷֱ�����ȷ��
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

    //����������
    //if(ui->spinBox_rollSampleNum->value() > ui->spinBox_dataSampleNum->value())
    //{
    //    ui->spinBox_rollSampleNum->setValue(ui->spinBox_dataSampleNum->value());
    //}

    if(ui->checkBox_vertical->isChecked())
    {
        ui->spinBox_verticalMain->setEnabled(true);

        if(ui->checkBox_verticalSub->isChecked())//��ʾ�������ش�ֱ�α��
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

        if(ui->checkBox_horizSub->isChecked())//��ʾ��������ˮƽ�α��
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

void QTrendadisplay::on_spinBox_dataSampleNum_valueChanged(int value)//����������
{
    /*if(value <= ui->spinBox_rollSampleNum->value())
    {
        ui->spinBox_dataSampleNum->setValue(ui->spinBox_rollSampleNum->value()+1);
    }

    m_nDataSample = ui->spinBox_dataSampleNum->value();*/
}

void QTrendadisplay::on_spinBox_rollSampleNum_valueChanged(int value)//����������
{
    if(value >= ui->spinBox_dataSampleNum->value())
    {
        ui->spinBox_rollSampleNum->setValue(ui->spinBox_dataSampleNum->value()-1);
    }

    m_nScrollSample = ui->spinBox_rollSampleNum->value();
}

void QTrendadisplay::on_comboBox_channelNum_currentIndexChanged(int index)//ͨ����
{
    
}

void QTrendadisplay::on_comboBox_showCondition_currentIndexChanged(int index)//��ʾ����
{
}

void QTrendadisplay::on_pushButton_showAddr_clicked()//��ַ��ť
{
    
}

void QTrendadisplay::on_lineEdit_showAddr_editingFinished()//��ַ
{
    
}

void QTrendadisplay::set_comboBox_chnnel_num(int begin, int total)//ͨ�������ı��Ĳۺ���
{
    
}

void QTrendadisplay::Init(QTrendAttr *pItem)
{
    if(pItem)
    {
        m_bSelectVertMinor  = pItem->m_bSelectVertMinor;//�Ƿ���ʾ��ֱ�α��
        m_bSelectHorMinor   = pItem->m_bSelectHorMinor;	//�Ƿ���ʾˮƽ�α��
        m_bMainVer          = pItem->m_bMainVer;
        m_bMainHor          = pItem->m_bMainHor;
        m_nDataSample       = pItem->m_nDataSample;	//����������
        m_nScrollSample     = pItem->m_nScrollSample;	//����������
        m_nVertMajorScale   = pItem->m_nVertMajorScale;	//��ֱ�����
        m_nVertMinorScale   = pItem->m_nVertMinorScale;	//��ֱ�α��
        m_nHorMajorScale    = pItem->m_nHorMajorScale;	//ˮƽ�����
        m_nHorMinorScale    = pItem->m_nHorMinorScale;	//ˮƽ�α��
        m_bGrade            = pItem->m_bGrade;        //�Ƿ���Ҫ����
        m_nVerColor         = pItem->m_nVerColor;     //ˮƽ������ɫ
        m_nHorColor         = pItem->m_nHorColor;     //��ֱ������ɫ
        m_nBoradColor       = pItem->m_nBoradColor;	//�߿���ɫ
        m_nScaleColor       = pItem->m_nScaleColor;	//�����ɫ
        m_nGraphColor       = pItem->m_nGraphColor;	//ͼ������ɫ
        m_alpha             = pItem->m_alpha;

    }
    else
    {
        m_bSelectVertMinor  = false;    //�Ƿ���ʾ��ֱ�α��
        m_bSelectHorMinor   = false;	//�Ƿ���ʾˮƽ�α��
        m_bMainVer          = true;
        m_bMainHor          = true;
        m_nDataSample       = 100;	//����������
        m_nScrollSample     = 9;	//����������
        m_nVertMajorScale   = 2;	//��ֱ�����
        m_nVertMinorScale   = 5;	//��ֱ�α��
        m_nHorMajorScale    = 2;	//ˮƽ�����
        m_nHorMinorScale    = 5;	//ˮƽ�α��
        m_bGrade            = true;                   //�Ƿ���Ҫ����
        m_nVerColor         = QColor(192, 192, 192);  //ˮƽ������ɫ
        m_nHorColor         = QColor(192, 192, 192);  //��ֱ������ɫ
        m_nBoradColor       = QColor(0, 0, 255);	//�߿���ɫ
        m_nScaleColor       = QColor(0, 255, 0);	//�����ɫ
        m_nGraphColor       = QColor(0, 0, 255);	//ͼ������ɫ
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
        m_bSelectVertMinor  = pItem->m_bSelectVertMinor;//�Ƿ���ʾ��ֱ�α��
        m_bSelectHorMinor   = pItem->m_bSelectHorMinor;	//�Ƿ���ʾˮƽ�α��
        m_bMainVer          = pItem->m_bMainVer;
        m_bMainHor          = pItem->m_bMainHor;
        //m_nDataSample       = pItem->m_nDataSample;	//����������
        //m_nScrollSample     = pItem->m_nScrollSample;	//����������
        m_nVertMajorScale   = pItem->m_nVertMajorScale;	//��ֱ�����
        m_nVertMinorScale   = pItem->m_nVertMinorScale;	//��ֱ�α��
        m_nHorMajorScale    = pItem->m_nHorMajorScale;	//ˮƽ�����
        m_nHorMinorScale    = pItem->m_nHorMinorScale;	//ˮƽ�α��
        m_bGrade            = pItem->m_bGrade;        //�Ƿ���Ҫ����
        m_nVerColor         = pItem->m_nVerColor;     //ˮƽ������ɫ
        m_nHorColor         = pItem->m_nHorColor;     //��ֱ������ɫ
        m_nBoradColor       = pItem->m_nBoradColor;	//�߿���ɫ
        m_nScaleColor       = pItem->m_nScaleColor;	//�����ɫ
        m_nGraphColor       = pItem->m_nGraphColor;	//ͼ������ɫ
        m_alpha             = pItem->m_alpha;
        m_textColor         = pItem->m_TextColor;
        m_textSize          = pItem->m_textSize;
        qDebug()<<"m_textSize" << m_textSize;

    }
    else
    {
        m_bSelectVertMinor  = false;    //�Ƿ���ʾ��ֱ�α��
        m_bSelectHorMinor   = false;	//�Ƿ���ʾˮƽ�α��
        m_bMainVer          = true;
        m_bMainHor          = true;
        m_nDataSample       = 100;	//����������
        m_nScrollSample     = 9;	//����������
        m_nVertMajorScale   = 2;	//��ֱ�����
        m_nVertMinorScale   = 5;	//��ֱ�α��
        m_nHorMajorScale    = 2;	//ˮƽ�����
        m_nHorMinorScale    = 5;	//ˮƽ�α��
        m_bGrade            = true;                   //�Ƿ���Ҫ����
        m_nVerColor         = QColor(192, 192, 192);  //ˮƽ������ɫ
        m_nHorColor         = QColor(192, 192, 192);  //��ֱ������ɫ
        m_nBoradColor       = QColor(0, 0, 255);	//�߿���ɫ
        m_nScaleColor       = QColor(0, 255, 0);	//�����ɫ
        m_nGraphColor       = QColor(0, 0, 255);	//ͼ������ɫ
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
void QTrendadisplay::on_spinBox_verticalMain_valueChanged(int value)//��ֱ�����
{
    m_nVertMajorScale = value;
}

void QTrendadisplay::on_spinBox_horizMain_valueChanged(int value)//ˮƽ�����
{
    m_nHorMajorScale = value;
}

int QTrendadisplay::getAlpha()
{
    //return ui->spin_alpha->value();
}

void QTrendadisplay::on_checkBox_verticalSub_clicked(bool checked)//�Ƿ���ʾ��ֱ�α��
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

void QTrendadisplay::on_checkBox_horizSub_clicked(bool checked)//�Ƿ���ʾˮƽ�α��
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

void QTrendadisplay::on_spinBox_verticalSub_valueChanged(int value)//��ֱ�α��
{
    m_nVertMinorScale = value;
}

void QTrendadisplay::on_spinBox_horizSub_valueChanged(int value)//ˮƽ�α��
{
    m_nHorMinorScale = value;
}

void QTrendadisplay::on_pushButton_frameColor_clicked()//�߿���ɫ
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

void QTrendadisplay::on_pushButton_rulerColor_clicked()//�����ɫ
{
	ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
	pwnd->OnAddColorDlg(ui->pushButton_rulerColor, colorPicker);

	connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_rulerColor(const QColor &)));
}

void QTrendadisplay::set_pushButton_rulerColor(const QColor & Color)
{
	ui->pushButton_rulerColor->setStyleSheet(QString("background:%1").arg(Color.name()));
	m_nScaleColor = Color;	//�����ɫ
}

void QTrendadisplay::on_pushButton_tableColor_clicked()//ͼ������ɫ
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
	ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//����û���ͷŻ᲻�����ڴ�й¶��������ɫҲһ��
	pwnd->OnAddColorDlg(ui->pushButton_verGradeColor, colorPicker);

	connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_verGradeColor(const QColor &)));
}

void QTrendadisplay::on_pushButton_horGradeColor_clicked()
{
	ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//����û���ͷŻ᲻�����ڴ�й¶��������ɫҲһ��
	pwnd->OnAddColorDlg(ui->pushButton_horGradeColor, colorPicker);

	connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_horGradeColor(const QColor &)));
}

void QTrendadisplay::set_pushButton_verGradeColor(const QColor & Color)
{
	ui->pushButton_verGradeColor->setStyleSheet(QString("background:%1").arg(Color.name()));
	m_nVerColor = Color;	//��ֱ������ɫ
}

void QTrendadisplay::set_pushButton_horGradeColor(const QColor & Color)
{
	ui->pushButton_horGradeColor->setStyleSheet(QString("background:%1").arg(Color.name()));
	m_nHorColor = Color;	//ˮƽ������ɫ
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
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//����û���ͷŻ᲻�����ڴ�й¶��������ɫҲһ��
    pwnd->OnAddColorDlg(ui->pushButton, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_BtnTextColor(const QColor &)));

}
void QTrendadisplay::set_BtnTextColor(const QColor &Color)
{
    ui->pushButton->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_textColor = Color;	//ˮƽ������ɫ
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
