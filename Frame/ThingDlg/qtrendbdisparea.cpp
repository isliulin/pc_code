#include "qtrendbdisparea.h"
#include "ui_qtrendbdisparea.h"
#include "../mainwindow.h"

extern MainWindow *pwnd;

QTrendbDispArea::QTrendbDispArea(QWidget *parent):QWidget(parent),ui(new Ui::QTrendbDispArea)
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
    ui->spinBox_dataSampleNum->setMaximum(width);
    ui->spinBox_dataSampleNum->setMinimum(2);

    if(ui->checkBox_verticalSub->isChecked())//��ʾ�������ش�ֱ�α��
    {
        ui->spinBox_verticalSub->setEnabled(true);
    }
    else
    {
        ui->spinBox_verticalSub->setEnabled(false);
    }

    if(ui->checkBox_horizSub->isChecked())//��ʾ��������ˮƽ�α��
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

void QTrendbDispArea::on_spinBox_dataSampleNum_valueChanged(int value)//����������
{
     m_nDataSample = value;
}

void QTrendbDispArea::on_spinBox_verticalMain_valueChanged(int value)//��ֱ�����
{
    m_nVertMajorScale = value;
}

void QTrendbDispArea::on_spinBox_horizMain_valueChanged(int value)//ˮƽ�����
{
    m_nHorMajorScale = value;
}

void QTrendbDispArea::on_checkBox_verticalSub_clicked(bool checked)//��ֱ�α��,�Ƿ����
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

void QTrendbDispArea::on_checkBox_horizSub_clicked(bool checked)//ˮƽ�α��,�Ƿ����
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

void QTrendbDispArea::on_spinBox_verticalSub_valueChanged(int value)//��ֱ�α��
{
    m_nVertMinorScale = value;
}

void QTrendbDispArea::on_spinBox_horizSub_valueChanged(int value)//ˮƽ�α��
{
    m_nHorMinorScale = value;
}

void QTrendbDispArea::Init(QTrendDataGroupAttr *pItem)//
{
    if(pItem)
    {
        m_bSelectVertMinor  = pItem->m_bSelectVertMinor;//�Ƿ���ʾ��ֱ�α��
        m_bSelectHorMinor   = pItem->m_bSelectHorMinor;	//�Ƿ���ʾˮƽ�α��
        m_bMainVer          = pItem->m_bMainVer;         //�Ƿ���ʾ��ֱ�����
        m_bMainHor          = pItem->m_bMainHor;         //�Ƿ���ʾˮƽ����
        m_nDataSample       = pItem->m_nDataSample;	//����������
        m_nVertMajorScale   = pItem->m_nVertMajorScale;	//��ֱ�����
        m_nVertMinorScale   = pItem->m_nVertMinorScale;	//��ֱ�α��
        m_nHorMajorScale    = pItem->m_nHorMajorScale;	//ˮƽ�����
        m_nHorMinorScale    = pItem->m_nHorMinorScale;	//ˮƽ�α��

        m_bGrade      = pItem->m_bGrade;        //�Ƿ���Ҫ����
        m_nVerColor   = pItem->m_nVerColor;     //ˮƽ������ɫ
        m_nHorColor   = pItem->m_nHorColor;     //��ֱ������ɫ
        m_nBoradColor = pItem->m_nBoradColor;	//�߿���ɫ
        m_nScaleColor = pItem->m_nScaleColor;	//�����ɫ
        m_nGraphColor = pItem->m_nGraphColor;	//ͼ������ɫ
        m_nMarkedColor= pItem->m_nMarkedColor;  //��ע��ɫ
        m_nFontSize   = pItem->m_nFontSize;
        m_alpha       = pItem->m_alpha;
    }
    else
    {
        m_bSelectVertMinor  = false;    //�Ƿ���ʾ��ֱ�α��
        m_bSelectHorMinor   = false;	//�Ƿ���ʾˮƽ�α��
        m_bMainVer          = true;     //�Ƿ���ʾ��ֱ�����
        m_bMainHor          = true;     //�Ƿ���ʾˮƽ����
        m_nDataSample       = 10;	//����������
        m_nVertMajorScale   = 2;	//��ֱ�����
        m_nVertMinorScale   = 5;	//��ֱ�α��
        m_nHorMajorScale    = 2;	//ˮƽ�����
        m_nHorMinorScale    = 5;	//ˮƽ�α��

        m_bGrade            = true;                   //�Ƿ���Ҫ����
        m_nVerColor         = QColor(192, 192, 192);  //ˮƽ������ɫ
        m_nHorColor         = QColor(192, 192, 192);  //��ֱ������ɫ
        m_nBoradColor       = QColor(0, 0, 255);	//�߿���ɫ
        m_nScaleColor       = QColor(0, 255, 0);	//�����ɫ
        m_nMarkedColor      = QColor(0, 0, 0);	//�����ɫ
        m_nGraphColor       = QColor(0, 0, 255);	//ͼ������ɫ
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

void QTrendbDispArea::on_pushButton_frameColor_clicked()//�߿���ɫ
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

void QTrendbDispArea::on_pushButton_rulerColor_clicked()//�����ɫ
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_rulerColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_rulerColor(const QColor &)));
}

void QTrendbDispArea::set_pushButton_rulerColor(const QColor & Color)
{
    ui->pushButton_rulerColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nScaleColor = Color;	//�����ɫ
}

void QTrendbDispArea::on_pushButton_tableColor_clicked()//ͼ������ɫ
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
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//����û���ͷŻ᲻�����ڴ�й¶��������ɫҲһ��
    pwnd->OnAddColorDlg(ui->pushButton_verGradeColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_verGradeColor(const QColor &)));
}

void QTrendbDispArea::on_pushButton_horGradeColor_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//����û���ͷŻ᲻�����ڴ�й¶��������ɫҲһ��
    pwnd->OnAddColorDlg(ui->pushButton_horGradeColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_horGradeColor(const QColor &)));
}

void QTrendbDispArea::set_pushButton_verGradeColor(const QColor & Color)
{
    ui->pushButton_verGradeColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nVerColor = Color;	//��ֱ������ɫ
}

void QTrendbDispArea::set_pushButton_horGradeColor(const QColor & Color)
{
    ui->pushButton_horGradeColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nHorColor = Color;	//ˮƽ������ɫ
}



void QTrendbDispArea::set_pushButton_markColor(const QColor & Color)
{
    ui->pushButton_markColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nMarkedColor = Color;	//ˮƽ������ɫ
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
