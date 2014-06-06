#include "qtrendacolor.h"
#include "ui_qtrendacolor.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

//////////////////////////////////QTrendaColor////////////////////////////////
QTrendaColor::QTrendaColor(QWidget *parent):QWidget(parent),ui(new Ui::QTrendaColor)
{
    ui->setupUi(this);

    //线型,图像现在没有，以后加图像，现在看效果，加文字就可以//当数据显示空间不足16点时，可能不能正确显示非实线线型
    ui->comboBox_lineStyle->addItem(tr("实线"));
    //ui->comboBox_lineStyle->addItem(tr("虚线"));
    //ui->comboBox_lineStyle->addItem(tr("短划线"));
    //ui->comboBox_lineStyle->addItem(tr("点划线"));
    //ui->comboBox_lineStyle->addItem(tr("2点划线"));
    //ui->comboBox_lineStyle->addItem(QIcon);
}

QTrendaColor::~QTrendaColor()
{
    delete ui;
}

void QTrendaColor::on_comboBox_chNum_currentIndexChanged(int index)//当前通道号
{
    //增加这个判断因为刚开始为0的时候系统会调用这个,这个是最shit的
    if(m_vecGroupColor.size() > 0)
    {
        ui->comboBox_lineStyle->setCurrentIndex((int)m_vecGroupColor.at(index).eLineType - 1);//线型
        ui->spinBox_lineWidth->setValue(m_vecGroupColor.at(index).nLineThickness);//线条宽度
        ui->pushButton_showColor->setStyleSheet(
                QString("background:%1").arg(m_vecGroupColor.at(index).nDisplayColor.name()));//颜色
        //m_vecGroupColor通道号是顺序的，不用改
    }
}

void QTrendaColor::on_comboBox_lineStyle_currentIndexChanged(int index)//线型
{
    if(m_vecGroupColor.size() > 0)
    {
        m_vecGroupColor.at(ui->comboBox_chNum->currentIndex()).eLineType = (LineStyleType)(index + 1);
    }
}

void QTrendaColor::on_spinBox_lineWidth_valueChanged(int value)//线条宽度
{
    if(m_vecGroupColor.size() > 0)
    {
        m_vecGroupColor.at(ui->comboBox_chNum->currentIndex()).nLineThickness = value;
    }
}

void QTrendaColor::on_pushButton_showColor_clicked()//显示颜色
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_showColor ,colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_showColor(const QColor &)));
}

void QTrendaColor::set_pushButton_showColor(const QColor & Color)
{
    ui->pushButton_showColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    if(m_vecGroupColor.size() > 0)
    {
        m_vecGroupColor.at(ui->comboBox_chNum->currentIndex()).nDisplayColor = Color;
    }
}

void QTrendaColor::on_pushButton_frameColor_clicked()//边框颜色
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_frameColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_frameColor(const QColor &)));
}

void QTrendaColor::set_pushButton_frameColor(const QColor & Color)
{
    ui->pushButton_frameColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nBoradColor = Color;
}

void QTrendaColor::on_pushButton_rulerColor_clicked()//标尺颜色
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_rulerColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_rulerColor(const QColor &)));
}

void QTrendaColor::set_pushButton_rulerColor(const QColor & Color)
{
    ui->pushButton_rulerColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nScaleColor = Color;	//标尺颜色
}

void QTrendaColor::on_pushButton_tableColor_clicked()//图表区颜色
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_tableColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_tableColor(const QColor &)));
}

void QTrendaColor::set_pushButton_tableColor(const QColor & Color)
{
    ui->pushButton_tableColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nGraphColor = Color;
}

void QTrendaColor::set_comboBox_chnnel_num(int begin, int total)//更改通道数触发的槽函数
{
    m_nTotalTrendNum    = total;
    m_nChnnelBegin      = begin;

    int chNum   = ui->comboBox_chNum->count();
    int shit    = 0;
    if(chNum < m_nTotalTrendNum)//要加ITEM
    {
        shit = m_nTotalTrendNum - chNum;
        for(int i = 0; i < shit; i++)
        {
            ui->comboBox_chNum->addItem(QString::number(chNum + i + begin));
        }
    }
    else if(chNum > m_nTotalTrendNum)//要去掉ITEM
    {
        shit = chNum - m_nTotalTrendNum;
        for(int i = 0; i < shit; i++)
        {
            ui->comboBox_chNum->removeItem(chNum - i - 1);
        }
    }
    //修改以上项的内容不对的现象
    int uiCount = ui->comboBox_chNum->count();
    for(int i = 0; i < uiCount; i++)
    {
        ui->comboBox_chNum->setItemText(i, QString::number(i + begin));
    }

    int temp = 0;
    int num = 0;
    ColorGroupInfo info;
    if(m_vecGroupColor.size() < m_nTotalTrendNum)//需要增加m_vecGroupColor项
    {
        temp = m_nTotalTrendNum - m_vecGroupColor.size();
        num = m_vecGroupColor.size();
        for(int i = 0; i < temp; i++)
        {
            info.eLineType      = LineSolid;
            info.nChannelNum    = i + m_nChnnelBegin;
            info.nLineThickness = 1;
            info.nDisplayColor  = QColor(192, 192, 192);
            m_vecGroupColor.push_back(info);
        }
    }
    else if(m_vecGroupColor.size() > m_nTotalTrendNum)//需要删去一些m_vecGroupColor项
    {
        temp = m_vecGroupColor.size() - m_nTotalTrendNum;
        for(int i = 0; i < temp; i++)
        {
            m_vecGroupColor.pop_back();
        }
    }  
    //修改以上项的内容不对的现象
    for(int i = 0; i < m_vecGroupColor.size(); i++)
    {
        m_vecGroupColor.at(i).nChannelNum = i + begin;
    }
}

void QTrendaColor::Init(QTrendAttr *pItem)
{
    if(pItem)
    {
        m_bGrade      = pItem->m_bGrade;        //是否需要网格
        m_nVerColor   = pItem->m_nVerColor;     //水平网格颜色
        m_nHorColor   = pItem->m_nHorColor;     //垂直网格颜色
        m_nBoradColor = pItem->m_nBoradColor;	//边框颜色
        m_nScaleColor = pItem->m_nScaleColor;	//标尺颜色
        m_nGraphColor = pItem->m_nGraphColor;	//图表区颜色
        m_vecGroupColor.clear();                //各个通道颜色设置

        ColorGroupInfo info;
        for(int i = 0; i < m_nTotalTrendNum; i++)
        {
            info.eLineType      = pItem->m_vecGroupColor.at(i).eLineType;
            info.nChannelNum    = pItem->m_vecGroupColor.at(i).nChannelNum;
            info.nLineThickness = pItem->m_vecGroupColor.at(i).nLineThickness;
            info.nDisplayColor  = pItem->m_vecGroupColor.at(i).nDisplayColor;
            m_vecGroupColor.push_back(info);
        }
    }
    else
    {
        m_bGrade      = true;                   //是否需要网格
        m_nVerColor   = QColor(192, 192, 192);  //水平网格颜色
        m_nHorColor   = QColor(192, 192, 192);  //垂直网格颜色
        m_nBoradColor = QColor(255, 0, 0);	//边框颜色
        m_nScaleColor = QColor(0, 255, 0);	//标尺颜色
        m_nGraphColor = QColor(0, 0, 255);	//图表区颜色
        m_vecGroupColor.clear();                //各个通道颜色设置

        ColorGroupInfo info;
        for(int i = 0; i < m_nTotalTrendNum; i++)
        {
            info.eLineType      = LineSolid;
            info.nChannelNum    = i + m_nChnnelBegin;//通道号要加上初始通道号
            info.nLineThickness = 1;
            info.nDisplayColor  = QColor(192, 192, 192);
            m_vecGroupColor.push_back(info);
        }
    }

    ui->pushButton_verGradeColor->setStyleSheet(QString("background:%1").arg(m_nVerColor.name()));
    ui->pushButton_horGradeColor->setStyleSheet(QString("background:%1").arg(m_nHorColor.name()));
    ui->groupBox_grade->setChecked(m_bGrade);
    ui->groupBox_grade->setEnabled(m_bGrade);
    ui->pushButton_frameColor->setStyleSheet(QString("background:%1").arg(m_nBoradColor.name()));
    ui->pushButton_rulerColor->setStyleSheet(QString("background:%1").arg(m_nScaleColor.name()));
    ui->pushButton_tableColor->setStyleSheet(QString("background:%1").arg(m_nGraphColor.name()));

    ui->comboBox_chNum->setCurrentIndex(0);
    ui->comboBox_lineStyle->setCurrentIndex((int)m_vecGroupColor.at(0).eLineType - 1);
    ui->spinBox_lineWidth->setValue(m_vecGroupColor.at(0).nLineThickness);
    ui->pushButton_showColor->setStyleSheet(QString("background:%1").arg(m_vecGroupColor.at(0).nDisplayColor.name()));
}

void QTrendaColor::on_groupBox_grade_clicked(bool checked)
{
    m_bGrade = checked;
    ui->groupBox_grade->setEnabled(checked);
}

void QTrendaColor::on_pushButton_verGradeColor_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
    pwnd->OnAddColorDlg(ui->pushButton_verGradeColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_verGradeColor(const QColor &)));
}

void QTrendaColor::on_pushButton_horGradeColor_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
    pwnd->OnAddColorDlg(ui->pushButton_horGradeColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_horGradeColor(const QColor &)));
}

void QTrendaColor::set_pushButton_verGradeColor(const QColor & Color)
{
    ui->pushButton_verGradeColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nVerColor = Color;	//垂直网格颜色
}

void QTrendaColor::set_pushButton_horGradeColor(const QColor & Color)
{
    ui->pushButton_horGradeColor->setStyleSheet(QString("background:%1").arg(Color.name()));
    m_nHorColor = Color;	//水平网格颜色
}





