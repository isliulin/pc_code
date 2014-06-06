#include "qdropdownfont.h"
#include "ui_qdropdownfont.h"
#include "Frame/mainwindow.h"
#include <QFontDatabase>

extern MainWindow *pwnd;

qDropDownFont::qDropDownFont(QWidget *parent):QWidget(parent),ui(new Ui::qDropDownFont)
{
    ui->setupUi(this);

    ui->comboBox_fontType->addItems(QFontDatabase().families(QFontDatabase::Any));
    //ui->comboBox_fontType->setCurrentIndex(0);

    /*int num = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    for(int i = 0; i < num; i++) //初始化语言对话框
    {
        ui->comboBox_fontLan->addItem(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }*/
    //ui->comboBox_fontLan->setCurrentIndex(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan);

    //ui->label_3->hide();
    //ui->comboBox_fontLan->hide();
}

qDropDownFont::~qDropDownFont()
{
    delete ui;
}

void qDropDownFont::Init(QDropdownAttr *pItem)
{
    if(pItem)
    {
        m_strFontName   = pItem->m_strFontName;       //字体类型的名字
        m_nFontSize     = pItem->m_nFontSize;         //字体大小
        m_nLanType      = pItem->m_nLanType;          //语言种类
        m_nFontStyle    = pItem->m_nFontStyle;        //文字样式（标准，粗体，斜体）
        m_nFontColor    = pItem->m_nFontColor;        //字体颜色
        m_nBackColor    = pItem->m_nBackColor;        //背景颜色
        m_nAlpha        = pItem->m_nAlpha;
    }
    else
    {                                             //字体类型的名字
        m_strFontName   = tr("Droid Sans Fallback");//QFontDatabase().families(QFontDatabase::Any).at(0);
        m_nFontSize     = 10;                                                //字体大小
        m_nLanType      = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan;  //语言种类
        m_nFontStyle    = 0;//NoEffect;                                     //文字样式（标准，粗体，斜体）
        m_nFontColor    = QColor(0, 0, 0);                                  //字体颜色
        m_nBackColor    = QColor(255, 255, 255);                            //背景颜色
        m_nAlpha        = 255;
    }

    ui->spinBox_tran->setValue(m_nAlpha);

    int num = QFontDatabase().families(QFontDatabase::Any).size();
    for(int i = 0; i < num; i++)
    {
        if(m_strFontName == QFontDatabase().families(QFontDatabase::Any).at(i))
        {
            ui->comboBox_fontType->setCurrentIndex(i);
            break;
        }
    }
    //ui->comboBox_fontLan->setCurrentIndex(m_nLanType);
    ui->spinBox->setValue(m_nFontSize);

    ui->pushButton->setStyleSheet(QString("background:%1").arg(m_nFontColor.name()));
    ui->pushButton_2->setStyleSheet(QString("background:%1").arg(m_nBackColor.name()));

    if(0 == m_nFontStyle)
    {
        ui->checkBox_1->setChecked(true);
        ui->checkBox_2->setChecked(false);
        ui->checkBox_3->setChecked(false);
        ui->checkBox_4->setChecked(false);
    }
    else
    {
        ui->checkBox_1->setChecked(false);
        if(0x01 & m_nFontStyle)
        {
            ui->checkBox_2->setChecked(true);
        }
        if(0x02 & m_nFontStyle)
        {
            ui->checkBox_3->setChecked(true);
        }
        if(0x08 & m_nFontStyle)
        {
            ui->checkBox_4->setChecked(true);
        }
    }

    //emit alphaCh(m_nAlpha);
}

void qDropDownFont::on_pushButton_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_showColor(const QColor &)));
}

void qDropDownFont::set_pushButton_showColor(const QColor & mColor)
{
    ui->pushButton->setStyleSheet(QString("background:%1").arg(mColor.name()));
    m_nFontColor = mColor;
}

void qDropDownFont::on_pushButton_2_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_2, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_2_showColor(const QColor &)));
}

void qDropDownFont::set_pushButton_2_showColor(const QColor & mColor)
{
    ui->pushButton_2->setStyleSheet(QString("background:%1").arg(mColor.name()));
    m_nBackColor = mColor;
    emit alphaCh(m_nAlpha);
}

void qDropDownFont::on_checkBox_1_clicked(bool checked)
{
    if(checked)
    {
        //ui->checkBox_1->setChecked(true);
        ui->checkBox_2->setChecked(false);
        ui->checkBox_3->setChecked(false);
        ui->checkBox_4->setChecked(false);

        m_nFontStyle = 0;
    }
}

void qDropDownFont::on_checkBox_2_clicked(bool checked)
{
    if(ui->checkBox_1->isChecked())
    {
        ui->checkBox_1->setChecked(false);
    }

    if(checked)
    {
        m_nFontStyle |= 0x01;
    }
    else
    {
        m_nFontStyle &= 0xFE;
    }
}

void qDropDownFont::on_checkBox_3_clicked(bool checked)
{
    if(ui->checkBox_1->isChecked())
    {
        ui->checkBox_1->setChecked(false);
    }

    if(checked)
    {
        m_nFontStyle |= 0x02;
    }
    else
    {
        m_nFontStyle &= 0xFD;
    }
}

void qDropDownFont::on_checkBox_4_clicked(bool checked)
{
    if(ui->checkBox_1->isChecked())
    {
        ui->checkBox_1->setChecked(false);
    }

    if(checked)
    {
        m_nFontStyle |= 0x08;
    }
    else
    {
        m_nFontStyle &= 0xF7;
    }
}

void qDropDownFont::on_comboBox_fontType_currentIndexChanged(int index)
{
    m_strFontName = ui->comboBox_fontType->currentText();
}

void qDropDownFont::on_comboBox_fontLan_currentIndexChanged(int index)
{
    m_nLanType = index;
}

void qDropDownFont::on_spinBox_valueChanged(int value)
{
    m_nFontSize = value;
}

void qDropDownFont::on_spinBox_tran_valueChanged(int value)
{
    m_nAlpha = value;
    emit alphaCh(m_nAlpha);
}
