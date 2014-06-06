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
     pwnd->InitFontSize(ui->comboBox_text_fontsize); //��ʼ�������Сѡ���
     pwnd->InitFontSize(ui->comboBox_title_fontsize); //��ʼ�������Сѡ���

     pwnd->InitFontSize(ui->m_RowsizecmBox); //�����ֳ�ʼ�������Сѡ���
     ui->m_RowFontcmBox->addItems(QFontDatabase().families(QFontDatabase::Any)); //�����г�ʼ�������Сѡ���

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

 //   ui->comboBox_title_font->setCurrentIndex( ui->comboBox_title_font->findText(tr("����")));
    QString sFontName = tr("Droid Sans Fallback");
    i = ui->comboBox_title_font->findText(sFontName);//��������Ĭ��Ϊ����
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
        sRecipeName[i] = tr("���");
        sFont[i] = sFontName;//tr("����");
        nFontSize[i] = 10;
    }

    ui->m_ShowDescriptckBox->hide();
    bInitFlag = true;
}

void Qrepicegenaral::Init(QRecipeTableItem *pItem)//��ʼ������
{
    bInitFlag = false;
    if(pItem)
    {
        RECIPESHOW Info;
        pItem->GetInfo(Info);

        ui->comboBox_lan->setCurrentIndex(Info.nLanguaId);//����
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
        ui->m_noedit->setText(QString::number(Info.nRecipeGroupId));//�䷽����
        ui->m_GroupRecipecmBox->setCurrentIndex(Info.nRecipeGroupId);
        //�ı�
        ui->comboBox_text_fontsize->setCurrentIndex(Info.nDataFontSize);//�����С
        ui->m_AligentcmBox->setCurrentIndex(Info.eTextAlignType);//���뷽ʽ
        ui->btn_bk->setStyleSheet(QString("background:%1").arg(Info.nDataBackColor.name()));//������ɫ
        ui->btn_textcolor->setStyleSheet(QString("background:%1").arg(Info.nDataTextColor.name()));//������ɫ

        ui->m_row->setValue(Info.nRowShowNum);//����
        ui->m_Coloum->setValue(Info.nColumShowNum);//����

        //������
        ui->comboBox_title_fontsize->setCurrentIndex(Info.nHHeadFontSize);//���������С
        int i = ui->comboBox_title_font->findText(Info.sHHeadFontFamily);
        if(i >= 0)
        {
            ui->comboBox_title_font->setCurrentIndex(i);//�� ������
        }
        else
        {
            ui->comboBox_title_font->setCurrentIndex(ui->comboBox_title_font->findText(tr("System")));
        }
        ui->btn_title_bk->setStyleSheet(QString("background:%1").arg(Info.nHHeadBackColor.name()));//�� �б���ɫ
        ui->btn_title_color->setStyleSheet(QString("background:%1").arg(Info.nHHeadTextColor.name()));//�� ��������ɫ
        ui->m_ShowRecipeIDCkBox->setChecked(Info.bShowRecipeID);//��ʾ�䷽ID
        ui->m_ShowDescriptckBox->setChecked(Info.bShowDescrip);//��ʾ�䷽����

        //������
        ui->m_RowsizecmBox->setCurrentIndex(Info.nVHeadFontSize);//�����С
        i = ui->m_RowFontcmBox->findText(Info.sVHeadFontFamily);
        if(i >= 0)
        {
            ui->m_RowFontcmBox->setCurrentIndex(i);//����
        }
        else
        {
            ui->m_RowFontcmBox->setCurrentIndex(ui->m_RowFontcmBox->findText(tr("System")));
        }
        ui->m_RowBackColorBtn->setStyleSheet(QString("background:%1").arg(Info.nVHeadBackColor.name()));//����ɫ
        ui->m_RowTextcolorBtn->setStyleSheet(QString("background:%1").arg(Info.nVHeadTextColor.name()));//������ɫ

        ui->btn_Linecolor->setStyleSheet(QString("background:%1").arg(Info.nLineColor.name()));//������ɫ

        ui->m_TransparentspBox->setValue(Info.nTransparent);
        oId = pItem->id();
        ui->spinBox->setValue(oId);
    }
    else
    {
        ui->m_noedit->setText("0");//�䷽����
        ui->spinBox->setValue(pwnd->getNewId());

        //�����
        QColor mColor(0,0,0);
        QColor mBkColor(255,255,255);
        setTitleColor(mColor);
        settitle_BKColor(QColor(160,255,255));

        //������
        setRowBackColor(QColor(255,255,160));
        setRowTextColor(mColor);

        //�ı�
        setBKColor(mBkColor);
        setTextColor(mColor);

        //������ɫ
        setLineBtnColor(QColor(192,192,192));//������ɫ;
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

void Qrepicegenaral::setBKColor(const QColor & mColor)       //���ÿ�ı���ɫ
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

void Qrepicegenaral::setTextColor(const QColor & mColor)       //���ÿ�ı߿�ɫ
{
     ui->btn_textcolor->setStyleSheet(QString("background:%1").arg(mColor.name()));
}//

void Qrepicegenaral::on_btn_title_bk_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->btn_title_bk,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(settitle_BKColor(const QColor &)));
}

void Qrepicegenaral::settitle_BKColor(const QColor & mColor)       //���ÿ�ı߿�ɫ
{
     ui->btn_title_bk->setStyleSheet(QString("background:%1").arg(mColor.name()));
}//

void Qrepicegenaral::on_btn_title_color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->btn_title_color,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setTitleColor(const QColor &)));
}

void Qrepicegenaral::setTitleColor(const QColor & mColor)       //���ÿ�ı߿�ɫ
{
     ui->btn_title_color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}//

//���Եĸı�
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
    Info.nLanguaId = ui->comboBox_lan->currentIndex();//����
    Info.nRecipeGroupId = ui->m_noedit->text().toInt();//�䷽����
    //�ı�
    Info.nDataFontSize = ui->comboBox_text_fontsize->currentIndex();//�����С
    Info.eTextAlignType = ui->m_AligentcmBox->currentIndex();//���뷽ʽ
    Info.nDataBackColor = ui->btn_bk->palette().background().color();//������ɫ
    Info.nDataTextColor = ui->btn_textcolor->palette().background().color();//������ɫ
    Info.nRowShowNum = ui->m_row->value();//����
    Info.nColumShowNum = ui->m_Coloum->value();//����

    //������
    Info.nHHeadFontSize = ui->comboBox_title_fontsize->currentIndex();//���������С
    Info.sHHeadFontFamily = ui->comboBox_title_font->currentText();//�� ������
    Info.nHHeadBackColor = ui->btn_title_bk->palette().background().color();//�� �б���ɫ
    Info.nHHeadTextColor = ui->btn_title_color->palette().background().color();//�� ��������ɫ
    Info.bShowRecipeID = ui->m_ShowRecipeIDCkBox->isChecked();//��ʾ�䷽ID
    Info.bShowDescrip = ui->m_ShowDescriptckBox->isChecked();//��ʾ�䷽����

    //������
    Info.nVHeadFontSize = ui->m_RowsizecmBox->currentIndex();//�����С
    Info.sVHeadFontFamily = ui->m_RowFontcmBox->currentText();//����
    Info.nVHeadBackColor = ui->m_RowBackColorBtn->palette().background().color();//����ɫ
    Info.nVHeadTextColor = ui->m_RowTextcolorBtn->palette().background().color();//������ɫ

    Info.nLineColor = ui->btn_Linecolor->palette().background().color();//����ɫ

    Info.nTransparent = ui->m_TransparentspBox->value();
    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID�ظ������޸�ID��"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return false;
    }
    return true;
}

QColor Qrepicegenaral::GetBackColor()//��ȡ�ı��򱳾�ɫ
{
    return ui->btn_bk->palette().background().color();
}

QColor Qrepicegenaral::GetTitleBackColor()//��ȡ�����б���ɫ
{
    return ui->btn_title_bk->palette().background().color();
}

QColor Qrepicegenaral::GetTitleTextColor()//��ȡ�������ı�ɫ
{
    return ui->btn_title_color->palette().background().color();
}

int Qrepicegenaral::GetTitletextSize()//��ȡ�����������С
{
    return ui->comboBox_title_fontsize->currentText().toInt();
}

QString Qrepicegenaral::GetTitletextFont()//��ȡ����������
{
    return ui->comboBox_title_font->currentText();
}

int Qrepicegenaral::GetRowCount()//��ȡ����
{
    return ui->m_row->value();
}

int Qrepicegenaral::GetColoumCount()//��ȡ����
{
    return ui->m_Coloum->value();
}

bool Qrepicegenaral::showDeschecked()//�Ƿ���ʾ�䷽����
{
    return ui->m_ShowDescriptckBox->isChecked();
}

bool Qrepicegenaral::showIDChecked()//�Ƿ���ʾ�䷽ID
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

QString Qrepicegenaral::GetRowtextFont()//��ȡ����������
{
    return ui->m_RowFontcmBox->currentText();
}
QString Qrepicegenaral::GetRowText()      //��ȡ�б������ƣ��ж�����
{
    return ui->m_RecipeNamelineEdit->text();
}

int Qrepicegenaral::GetRowtextSize()     //��ȡ�����������С
{
    return ui->m_RowsizecmBox->currentText().toInt();
}

QColor Qrepicegenaral::GetRowBackColor()
{
    return ui->m_RowBackColorBtn->palette().background().color();
}

QColor Qrepicegenaral::GetRowTextColor()//��ȡ�������ı�ɫ
{
    return ui->m_RowTextcolorBtn->palette().background().color();
}

int Qrepicegenaral::GetRecipeIndex()//��ȡ��ǰ��ʾ���䷽��ID
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

int Qrepicegenaral::GetLangIndex()//��ȡ����ID
{
    return ui->comboBox_lan->currentIndex();
}

int Qrepicegenaral::GetAligentType()//��ȡ�ı����뷽ʽ
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

QColor Qrepicegenaral::GetLineColor()//��ȡ�������ɫ
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
