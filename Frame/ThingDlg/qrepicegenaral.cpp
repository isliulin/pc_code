#include "qrepicegenaral.h"
#include "ui_qrepicegenaral.h"
#include <QFontDatabase>
#include "Frame\MainWindow.h"

extern MainWindow *pwnd;

Qrepicegenaral::Qrepicegenaral(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Qrepicegenaral)
{
    ui->setupUi(this);
    oId = -1;
    bInitFlag = false;
    int i = 0;
     pwnd->InitFontSize(ui->comboBox_text_fontsize); //初始化字体大小选择框
     pwnd->InitFontSize(ui->comboBox_title_fontsize); //初始化字体大小选择框

     pwnd->InitFontSize(ui->m_RowsizecmBox); //标题咧初始化字体大小选择框
     ui->m_RowFontcmBox->addItems(QFontDatabase().families(QFontDatabase::Any)); //标题列初始化字体大小选择框

    ui->comboBox_title_font->addItems(QFontDatabase().families(QFontDatabase::Any));
    QVector<QString> language_vector;
    for( i=0;i<pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();i++)
    {
        language_vector.push_back(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }
    m_sRecipeName.resize(0);
    for( i=0;i< pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();i++)
    {
        m_sRecipeName.push_back(ui->m_RecipeNamelineEdit->text());
        ui->comboBox_lan->addItem(language_vector.at(i));
    }

 //   ui->comboBox_title_font->setCurrentIndex( ui->comboBox_title_font->findText(tr("宋体")));
    QString sFontName = tr("Droid Sans Fallback");
    i = ui->comboBox_title_font->findText(sFontName);//字体设置默认为宋体
    if(i < 0)
    {
        sFontName = "System";
        i = ui->comboBox_title_font->findText(sFontName);
    }
    ui->comboBox_title_font->setCurrentIndex(i);
    ui->m_RowFontcmBox->setCurrentIndex(i);

    ui->m_GroupRecipecmBox->clear();
    for(int i = 0; i < pwnd->m_pSamSysParame->m_qvcRecipe.size(); i++)
    {
        QString sName = pwnd->m_pSamSysParame->m_qvcRecipe[i].sName;
        ui->m_GroupRecipecmBox->addItem(sName);
    }
    for(i = 0; i < 5;i++)
    {
        sRecipeName[i] = tr("编号");
        sFont[i] = sFontName;//tr("宋体");
        nFontSize[i] = 10;
    }

    ui->m_ShowDescriptckBox->hide();
    bInitFlag = true;
}

void Qrepicegenaral::Init(QRecipeTableItem *pItem)//初始化函数
{
    bInitFlag = false;
    if(pItem)
    {
        RECIPESHOW Info;
        pItem->GetInfo(Info);

        ui->comboBox_lan->setCurrentIndex(Info.nLanguaId);//语言
        if(-1 == Info.nRecipeGroupId)
        {
            Info.nRecipeGroupId = 0;
        }

        for(int i = 0; i < m_sRecipeName.size() && i < Info.sRecipeName.size(); i++)
        {
            m_sRecipeName[i] = Info.sRecipeName.at(i);
        }
        if(Info.nLanguaId < m_sRecipeName.size())
        {
            ui->m_RecipeNamelineEdit->setText(m_sRecipeName.at(Info.nLanguaId));
        }
        ui->m_noedit->setText(QString::number(Info.nRecipeGroupId));//配方组编号
        ui->m_GroupRecipecmBox->setCurrentIndex(Info.nRecipeGroupId);
        //文本
        ui->comboBox_text_fontsize->setCurrentIndex(Info.nDataFontSize);//字体大小
        ui->m_AligentcmBox->setCurrentIndex(Info.eTextAlignType);//对齐方式
        ui->btn_bk->setStyleSheet(QString("background:%1").arg(Info.nDataBackColor.name()));//背景颜色
        ui->btn_textcolor->setStyleSheet(QString("background:%1").arg(Info.nDataTextColor.name()));//文字颜色

        ui->m_row->setValue(Info.nRowShowNum);//行数
        ui->m_Coloum->setValue(Info.nColumShowNum);//列数

        //标题列
        ui->comboBox_title_fontsize->setCurrentIndex(Info.nHHeadFontSize);//横列字体大小
        int i = ui->comboBox_title_font->findText(Info.sHHeadFontFamily);
        if(i >= 0)
        {
            ui->comboBox_title_font->setCurrentIndex(i);//横 列字体
        }
        else
        {
            ui->comboBox_title_font->setCurrentIndex(ui->comboBox_title_font->findText(tr("System")));
        }
        ui->btn_title_bk->setStyleSheet(QString("background:%1").arg(Info.nHHeadBackColor.name()));//横 列背景色
        ui->btn_title_color->setStyleSheet(QString("background:%1").arg(Info.nHHeadTextColor.name()));//横 列文字颜色
        ui->m_ShowRecipeIDCkBox->setChecked(Info.bShowRecipeID);//显示配方ID
        ui->m_ShowDescriptckBox->setChecked(Info.bShowDescrip);//显示配方描述

        //标题行
        ui->m_RowsizecmBox->setCurrentIndex(Info.nVHeadFontSize);//字体大小
        i = ui->m_RowFontcmBox->findText(Info.sVHeadFontFamily);
        if(i >= 0)
        {
            ui->m_RowFontcmBox->setCurrentIndex(i);//字体
        }
        else
        {
            ui->m_RowFontcmBox->setCurrentIndex(ui->m_RowFontcmBox->findText(tr("System")));
        }
        ui->m_RowBackColorBtn->setStyleSheet(QString("background:%1").arg(Info.nVHeadBackColor.name()));//背景色
        ui->m_RowTextcolorBtn->setStyleSheet(QString("background:%1").arg(Info.nVHeadTextColor.name()));//文字颜色

        ui->btn_Linecolor->setStyleSheet(QString("background:%1").arg(Info.nLineColor.name()));//文字颜色

        ui->m_TransparentspBox->setValue(Info.nTransparent);
        oId = pItem->id();
        ui->spinBox->setValue(oId);
    }
    else
    {
        ui->m_noedit->setText("0");//配方组编号
        ui->spinBox->setValue(pwnd->getNewId());

        //横标题
        QColor mColor(0,0,0);
        QColor mBkColor(255,255,255);
        setTitleColor(mColor);
        settitle_BKColor(QColor(160,255,255));

        //竖标题
        setRowBackColor(QColor(255,255,160));
        setRowTextColor(mColor);

        //文本
        setBKColor(mBkColor);
        setTextColor(mColor);

        //线条颜色
        setLineBtnColor(QColor(192,192,192));//格线颜色;
    }
    bInitFlag = true;
}

Qrepicegenaral::~Qrepicegenaral()
{
    delete ui;
}

void Qrepicegenaral::on_btn_bk_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->btn_bk,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBKColor(const QColor &)));
}

void Qrepicegenaral::setBKColor(const QColor & mColor)       //设置框的背景色
{
     ui->btn_bk->setStyleSheet(QString("background:%1").arg(mColor.name()));
}//

void Qrepicegenaral::on_btn_board_clicked()
{
}
void Qrepicegenaral::on_btn_textcolor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->btn_textcolor,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setTextColor(const QColor &)));
}

void Qrepicegenaral::setTextColor(const QColor & mColor)       //设置框的边框色
{
     ui->btn_textcolor->setStyleSheet(QString("background:%1").arg(mColor.name()));
}//

void Qrepicegenaral::on_btn_title_bk_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->btn_title_bk,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(settitle_BKColor(const QColor &)));
}

void Qrepicegenaral::settitle_BKColor(const QColor & mColor)       //设置框的边框色
{
     ui->btn_title_bk->setStyleSheet(QString("background:%1").arg(mColor.name()));
}//

void Qrepicegenaral::on_btn_title_color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->btn_title_color,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setTitleColor(const QColor &)));
}

void Qrepicegenaral::setTitleColor(const QColor & mColor)       //设置框的边框色
{
     ui->btn_title_color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}//

//语言的改变
void Qrepicegenaral::on_comboBox_lan_activated(int index)
{
}

int Qrepicegenaral::getId()
{
    return ui->spinBox->value();
}
bool Qrepicegenaral::GeneralSave(RECIPESHOW &Info)
{
    Info.sRecipeName = m_sRecipeName;
    Info.nLanguaId = ui->comboBox_lan->currentIndex();//语言
    Info.nRecipeGroupId = ui->m_noedit->text().toInt();//配方组编号
    //文本
    Info.nDataFontSize = ui->comboBox_text_fontsize->currentIndex();//字体大小
    Info.eTextAlignType = ui->m_AligentcmBox->currentIndex();//对齐方式
    Info.nDataBackColor = ui->btn_bk->palette().background().color();//背景颜色
    Info.nDataTextColor = ui->btn_textcolor->palette().background().color();//文字颜色
    Info.nRowShowNum = ui->m_row->value();//行数
    Info.nColumShowNum = ui->m_Coloum->value();//列数

    //标题列
    Info.nHHeadFontSize = ui->comboBox_title_fontsize->currentIndex();//横列字体大小
    Info.sHHeadFontFamily = ui->comboBox_title_font->currentText();//横 列字体
    Info.nHHeadBackColor = ui->btn_title_bk->palette().background().color();//横 列背景色
    Info.nHHeadTextColor = ui->btn_title_color->palette().background().color();//横 列文字颜色
    Info.bShowRecipeID = ui->m_ShowRecipeIDCkBox->isChecked();//显示配方ID
    Info.bShowDescrip = ui->m_ShowDescriptckBox->isChecked();//显示配方描述

    //标题行
    Info.nVHeadFontSize = ui->m_RowsizecmBox->currentIndex();//字体大小
    Info.sVHeadFontFamily = ui->m_RowFontcmBox->currentText();//字体
    Info.nVHeadBackColor = ui->m_RowBackColorBtn->palette().background().color();//背景色
    Info.nVHeadTextColor = ui->m_RowTextcolorBtn->palette().background().color();//文字颜色

    Info.nLineColor = ui->btn_Linecolor->palette().background().color();//线颜色

    Info.nTransparent = ui->m_TransparentspBox->value();
    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return false;
    }
    return true;
}

QColor Qrepicegenaral::GetBackColor()//获取文本框背景色
{
    return ui->btn_bk->palette().background().color();
}

QColor Qrepicegenaral::GetTitleBackColor()//获取标题列背景色
{
    return ui->btn_title_bk->palette().background().color();
}

QColor Qrepicegenaral::GetTitleTextColor()//获取标题列文本色
{
    return ui->btn_title_color->palette().background().color();
}

int Qrepicegenaral::GetTitletextSize()//获取标题列字体大小
{
    return ui->comboBox_title_fontsize->currentText().toInt();
}

QString Qrepicegenaral::GetTitletextFont()//获取标题列字体
{
    return ui->comboBox_title_font->currentText();
}

int Qrepicegenaral::GetRowCount()//获取行数
{
    return ui->m_row->value();
}

int Qrepicegenaral::GetColoumCount()//获取列数
{
    return ui->m_Coloum->value();
}

bool Qrepicegenaral::showDeschecked()//是否显示配方描述
{
    return ui->m_ShowDescriptckBox->isChecked();
}

bool Qrepicegenaral::showIDChecked()//是否显示配方ID
{
    return ui->m_ShowRecipeIDCkBox->isChecked();
}

void Qrepicegenaral::on_recipename_textChanged(QString sName)
{
    int nLang = ui->comboBox_lan->currentIndex();
    if(nLang < 0)
        return;
    sRecipeName[nLang] = sName;
}

void Qrepicegenaral::on_comboBox_title_fontsize_activated(QString sFont)
{
    int nLang = ui->comboBox_lan->currentIndex();
    if(nLang < 0)
        return;
    nFontSize[nLang] = sFont.toInt();
}

void Qrepicegenaral::on_comboBox_title_font_activated(QString sfont)
{
    int nLang = ui->comboBox_lan->currentIndex();
    if(nLang < 0)
        return;
    sFont[nLang] = sfont;
}
void Qrepicegenaral::on_m_RowBackColorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_RowBackColorBtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setRowBackColor(const QColor &)));
}

void Qrepicegenaral::setRowBackColor(const QColor &mColor)
{
    ui->m_RowBackColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void Qrepicegenaral::on_m_RowTextcolorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_RowTextcolorBtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setRowTextColor(const QColor &)));
}

void Qrepicegenaral::setRowTextColor(const QColor &mColor)
{
    ui->m_RowTextcolorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

QString Qrepicegenaral::GetRowtextFont()//获取标题列字体
{
    return ui->m_RowFontcmBox->currentText();
}
QString Qrepicegenaral::GetRowText()      //获取列标题名称，有多语言
{
    return ui->m_RecipeNamelineEdit->text();
}

int Qrepicegenaral::GetRowtextSize()     //获取标题列字体大小
{
    return ui->m_RowsizecmBox->currentText().toInt();
}

QColor Qrepicegenaral::GetRowBackColor()
{
    return ui->m_RowBackColorBtn->palette().background().color();
}

QColor Qrepicegenaral::GetRowTextColor()//获取标题列文本色
{
    return ui->m_RowTextcolorBtn->palette().background().color();
}

int Qrepicegenaral::GetRecipeIndex()//获取当前显示的配方组ID
{
    QString sName = ui->m_GroupRecipecmBox->currentText();
    int index = -1;
    for(int i = 0; i < pwnd->m_pSamSysParame->m_qvcRecipe.size(); i++)
    {
        if(sName == pwnd->m_pSamSysParame->m_qvcRecipe[i].sName)
        {
            index = i;
            break;
        }
    }
    return index;
}

int Qrepicegenaral::GetLangIndex()//获取语言ID
{
    return ui->comboBox_lan->currentIndex();
}

int Qrepicegenaral::GetAligentType()//获取文本对齐方式
{
    int nType = ui->m_AligentcmBox->currentIndex();
    int nAligent = 5;
    switch(nType)
    {
    case 0:
        nAligent = 5;
        break;
    case 1:
        nAligent = 4;
        break;
    case 2:
        nAligent = 6;
        break;
    default:
        break;
    }
    return nAligent;
}

void Qrepicegenaral::on_m_GroupRecipecmBox_currentIndexChanged(int index)
{
    QString str = QString::number(index);
    ui->m_noedit->setText(str);
}

void Qrepicegenaral::on_btn_Linecolor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->btn_Linecolor ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setLineBtnColor(const QColor &)));
}

void Qrepicegenaral::setLineBtnColor(const QColor &mColor)
{
    ui->btn_Linecolor->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

QColor Qrepicegenaral::GetLineColor()//获取表格线颜色
{
    return ui->btn_Linecolor->palette().background().color();
}

int Qrepicegenaral::GetTransparentValue()
{
    return ui->m_TransparentspBox->value();
}

void Qrepicegenaral::on_m_RecipeNamelineEdit_textChanged(QString )
{
    int index = ui->comboBox_lan->currentIndex();
    if(index < m_sRecipeName.size())
    {
        m_sRecipeName[index] = ui->m_RecipeNamelineEdit->text();
    }
}

void Qrepicegenaral::on_comboBox_lan_currentIndexChanged(int index)
{
    if(index < m_sRecipeName.size())
    {
        ui->m_RecipeNamelineEdit->setText(m_sRecipeName.at(index));
    }
}
