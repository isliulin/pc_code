#include "StaticTextDlg.h"
#include "color.h"
#include <QFontDatabase>
#include "Frame\MainWindow.h"
extern MainWindow *pwnd;

StaticTextDlg::StaticTextDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StaticTextDlg)
{
    ui->setupUi(this);
    int i = 0;
    isFlag=false;
    pwnd->InitFontSize(ui->FontSize); //��ʼ�������С

    QVector<QString> language_vector;
    for(int i=0;i<pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();i++)
    {
        language_vector.push_back(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }
    for(i = 0;i < pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size() ;i++) //��ʼ�����ԶԻ���
    {
        ui->m_languagecmb->addItem(language_vector.at(i));
    }
    ui->font->addItems(QFontDatabase().families(QFontDatabase::Any));//��ʼ������
    pwnd->OnAddPattern(ui->Pattern);  //��ʼ����ʽ
    ui->plainTextEdit->setFocus();
}

StaticTextDlg::~StaticTextDlg()
{
    delete ui;
}

void StaticTextDlg::InitParament()
{
    ui->plainTextEdit->setPlainText("TEXT");
    //�����С
    ui->FontSize->setCurrentIndex(ui->FontSize->findText(tr("10")));
    //����
    if(ui->font->findText(tr("Droid Sans Fallback")) >=0)
    {
        ui->font->setCurrentIndex(ui->font->findText(tr("Droid Sans Fallback")));
    }
    else
    {
        ui->font->setCurrentIndex(ui->font->findText(tr("System")));
    }
    //����λ��
    ui->combo_Alignment->setCurrentIndex(0);

    //����
    ui->IfBold->setChecked(false);
    //б��
    ui->IfItalic->setChecked(false);
    //�־�
    ui->WordInterval->setValue(0);
    //�»���
    ui->m_underlinecheck->setChecked(false);
    //����ɫ
    ui->BackColor ->setStyleSheet( QString("background:%1").arg(QColor(255,255,255).name()));
    //ǰ��ɫ
    ui->FrontColor->setStyleSheet( QString("background:%1").arg(QColor(255,0,0).name()));
    //����͸��
    ui->Pattern->setCurrentIndex(0);
    //����Ӧ
    ui->adaptText->setChecked(false);

    for(int i = 0; i < ui->m_languagecmb->count(); i++)
    {
        TxtProperty[i].sText = "TEXT";
        TxtProperty[i].nFontSize = 10;
        TxtProperty[i].nfontsizeindex=ui->FontSize->currentIndex();
        TxtProperty[i].sFont = tr("Droid Sans Fallback");
        TxtProperty[i].nfont = ui->font->currentIndex();
        TxtProperty[i].TextAlignIndex=0;
        TxtProperty[i].nFontColor=QColor(0,0,0).name();
        TxtProperty[i].adapt=false;
        TxtProperty[i].bold=false;
        TxtProperty[i].italic=false;
        TxtProperty[i].underline=false;
        TxtProperty[i].newColors=pwnd->ColorTOString(QColor(0,0,0));
    }
    //�ı���ɫ
    ui->FontColor->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    isFlag=true;

}

void StaticTextDlg::on_m_languagecmb_currentIndexChanged(int index)//����
{
    if(!isFlag){
        return;
    }
    if(index == 0)
    {
        ui->groupBox_3->setEnabled(true);
        //�־�
        ui->WordInterval->setEnabled(true);
        ui->label_6->setEnabled(true);
    }
    else
    {
        ui->groupBox_3->setEnabled(false);
        //�־�
        ui->WordInterval->setEnabled(false);
        ui->label_6->setEnabled(true);
    }
    if(TxtProperty[index].TextAlignIndex==0 || TxtProperty[index].TextAlignIndex==1 ||TxtProperty[index].TextAlignIndex==2){
        ui->combo_Alignment->setCurrentIndex(TxtProperty[index].TextAlignIndex);
    }else{
        ui->combo_Alignment->setCurrentIndex(0);
    }
    ui->plainTextEdit->setPlainText(TxtProperty[index].sText);
    ui->FontSize->setCurrentIndex(TxtProperty[index].nfontsizeindex);
    if(TxtProperty[index].sFont==""){
        ui->font->setCurrentIndex(ui->font->findText(tr("Droid Sans Fallback")));
    }else{
        ui->font->setCurrentIndex(ui->font->findText(TxtProperty[index].sFont));
    }
    ui->adaptText->setChecked(TxtProperty[index].adapt);
    ui->FontColor->setStyleSheet(QString("background:%1").arg(TxtProperty[index].nFontColor));
    if(TxtProperty[index].adapt){
            ui->FontSize->setEnabled(false);
            ui->label_4->setEnabled(false);
            ui->combo_Alignment->setEnabled(false);
            ui->label_type_5->setEnabled(false);
        }else{
            ui->FontSize->setEnabled(true);
            ui->label_4->setEnabled(true);
            ui->combo_Alignment->setEnabled(true);
            ui->label_type_5->setEnabled(true);
        }
    ui->IfBold->setChecked(TxtProperty[index].bold);
    ui->IfItalic->setChecked(TxtProperty[index].italic);
    ui->m_underlinecheck->setChecked(TxtProperty[index].underline);
    emit DrawTextView();

}

void StaticTextDlg::SaveText(TextInfos &m_text)
{
    m_text.isKeyDown=true;
    //����Ӧ
    m_text.adaptTexts=ui->adaptText->isChecked();
    m_text.nFontFamly=ui->font->currentIndex();

    //����ID
    m_text.nLanguageId=ui->m_languagecmb->currentIndex();
    //�ı���ʽ�����塢б����»��ߣ�
    m_text.eTextPro = 0;
    short int nflag = 0;
    if(ui->IfBold->isChecked())
    {
        nflag = 1;
        m_text.eTextPro = (m_text.eTextPro)|nflag;
    }
    if(ui->IfItalic->isChecked())
    {
        nflag = 2;
        m_text.eTextPro = (m_text.eTextPro)|nflag;
    }
    if(ui->m_underlinecheck->isChecked())
    {
        nflag = 8;
        m_text.eTextPro = (m_text.eTextPro)|nflag;
    }

    //�־�
    m_text.sFontSpace=ui->WordInterval->value();

    //��ʽ
    m_text.nStylePadding=ui->Pattern->currentIndex();//��ʽ

    //͸����
    m_text.nAlphaPadding=ui->Alpha->value();

    m_text.nBackColorPadding=pwnd->ColorTOString(ui->BackColor->palette().background().color());//����ɫ28

    m_text.nForeColorPadding=pwnd->ColorTOString(ui->FrontColor->palette().background().color());//ǰ��ɫ29

    m_text.bFristLanguage=ui->m_check->isChecked();//�������Զ�ʹ�õ�һ�����Ե��ı�

    //��������
    for(int i=0;i<ui->m_languagecmb->count();i++){
        TextItemLists text;
//        text.textList.resize(ui->m_languagecmb->count());
        text.texts=TxtProperty[i].sText;
        text.fonts=TxtProperty[i].sFont;
        text.fontIndexs=TxtProperty[i].nfont;
        text.fontSizes=TxtProperty[i].nFontSize;
        text.fontSizeIndexs=TxtProperty[i].nfontsizeindex;
        if(TxtProperty[i].TextAlignIndex==0){
            text.TextAlignIndexs=5;
        }else if(TxtProperty[i].TextAlignIndex==1){
            text.TextAlignIndexs=4;
        }else if(TxtProperty[i].TextAlignIndex==2){
            text.TextAlignIndexs=6;
        }
        text.nFontColors=TxtProperty[i].nFontColor;
        text.adapts=TxtProperty[i].adapt;
        text.bolds=TxtProperty[i].bold;
        text.italics=TxtProperty[i].italic;
        text.underlines=TxtProperty[i].underline;
        text.newColor=TxtProperty[i].newColors;
        m_text.textList.push_back(text);

    }
    int langId=ui->m_languagecmb->currentIndex();
    m_text.sFontFamly=TxtProperty[langId].sFont;
//    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size()>1){
//        m_text.sStextStr=TxtProperty[0].sText;
//    }else{
//        m_text.sStextStr=ui->plainTextEdit->toPlainText();
//    }

    m_text.nFontFamly=TxtProperty[langId].nfont;
    m_text.sFontSize=TxtProperty[langId].nFontSize;
    m_text.nFontSize=TxtProperty[langId].nfontsizeindex;
    m_text.eTextAlign=TxtProperty[langId].TextAlignIndex;
    m_text.nFontColor=TxtProperty[langId].nFontColor;
    m_text.adaptTexts=TxtProperty[langId].adapt;
    m_text.mbolds=TxtProperty[langId].bold;
    m_text.mitalics=TxtProperty[langId].italic;
    m_text.munderlines=TxtProperty[langId].underline;
    if(TxtProperty[langId].adapt==false){
        m_text.sFontSize=TxtProperty[langId].nFontSize;
        m_text.nFontSize=TxtProperty[langId].nfontsizeindex;
    }
    //�ı���ɫ
    m_text.nFontColor=pwnd->ColorTOString(ui->FontColor->palette().background().color());
    //�ı�λ��
    int indexs=ui->combo_Alignment->currentIndex();
    switch(indexs){
    case 0:
        m_text.eTextAlign=0;//��
        break;
    case 1:
        m_text.eTextAlign=1;//��
        break;
    case 2:
        m_text.eTextAlign=2;//��
        break;
    }
    m_text.sFontFamly=ui->font->currentText();
    m_text.sStextStr=ui->plainTextEdit->toPlainText();
}

void StaticTextDlg::OnDoubleClickInit(StaticTextItem *item)
{
    QString sName = item->data(GROUP_NAME_KEY).toString();//�жϼ���
    item->m_text.isText=true;

    QColor mColor;
    //ѡ���һ������
    if(item->m_text.bFristLanguage){
        ui->m_languagecmb->setEnabled(false);
        ui->m_languagecmb->setCurrentIndex(0);
    }
    if(item)//item��Ϊ��
    {
//        if(item->m_text.nLanguageId == 0)//��һ������
//        {
//            ui->groupBox_3->setEnabled(true);//���
//            ui->WordInterval->setEnabled(true);//�־�
//        }
//        else
//        {
//            ui->groupBox_3->setEnabled(false);//���
//            ui->WordInterval->setEnabled(false);//�־�
//        }
        //��������
        for(int i=0;i<item->m_text.textList.size();i++){
            TxtProperty[i].sText = item->m_text.textList[i].texts;//�ı�
            TxtProperty[i].nfont = item->m_text.textList[i].fontIndexs;//����index
            TxtProperty[i].sFont = item->m_text.textList[i].fonts;//����
            TxtProperty[i].nfontsizeindex = item->m_text.textList[i].fontSizeIndexs;//�����Сindex
            TxtProperty[i].nFontSize = item->m_text.textList[i].fontSizes;//�����С
            if(item->m_text.textList[i].TextAlignIndexs==5){
                TxtProperty[i].TextAlignIndex=0;
            }else if(item->m_text.textList[i].TextAlignIndexs==4){
                TxtProperty[i].TextAlignIndex=1;
            }else if(item->m_text.textList[i].TextAlignIndexs==6){
                TxtProperty[i].TextAlignIndex=2;
            }

            TxtProperty[i].nFontColor=item->m_text.textList[i].nFontColors;//�ı���ɫ
            TxtProperty[i].adapt=item->m_text.textList[i].adapts;//����Ӧ
            TxtProperty[i].bold = item->m_text.textList[i].bolds;//����
            TxtProperty[i].italic = item->m_text.textList[i].italics;//б��
            TxtProperty[i].underline = item->m_text.textList[i].underlines;//�»���
            TxtProperty[i].newColors = item->m_text.textList[i].newColor;

        }
        if("TEXT" == sName || "MIN" == sName || "MAX" == sName){//�����ϵ��ı�
            ui->FontSize->setCurrentIndex(item->m_text.nFontSize);
            //ui->font->setCurrentIndex(ui->font->findText(item->m_text.sFontFamly));

            int index = ui->font->findText(item->m_text.sFontFamly);
            if(index >= 0)
            {
                ui->font->setCurrentIndex(index);
            }
            else
            {
                ui->font->setCurrentIndex(ui->font->findText(tr("System")));

            }

            ui->plainTextEdit->setPlainText(item->m_text.sStextStr);
            ui->combo_Alignment->setCurrentIndex(item->m_text.eTextAlign);

            mColor = pwnd->StringTOColor(item->m_text.nFontColor);
            ui->FontColor->setStyleSheet(QString("background:%1").arg(mColor.name()));

            ui->adaptText->setChecked(item->m_text.adaptTexts);
            //���塢б����»���
            ui->IfBold->setChecked(item->m_text.mbolds);
            ui->IfItalic->setChecked(item->m_text.mitalics);
            ui->m_underlinecheck->setChecked(item->m_text.munderlines);
        }else{
            ui->FontSize->setCurrentIndex(TxtProperty[0].nfontsizeindex);
            int index = ui->font->findText(TxtProperty[0].sFont);
            if(index >= 0)
            {
                ui->font->setCurrentIndex(index);
            }
            else
            {
                ui->font->setCurrentIndex(ui->font->findText(tr("System")));

            }
            ui->font->setCurrentIndex(ui->font->findText(TxtProperty[0].sFont));
            ui->plainTextEdit->setPlainText(TxtProperty[0].sText);
            ui->combo_Alignment->setCurrentIndex(TxtProperty[0].TextAlignIndex);
            //qDebug() << TxtProperty[0].nFontColor;
            //mColor = pwnd->StringTOColor(TxtProperty[0].nFontColor);
            ui->FontColor->setStyleSheet(QString("background:%1").arg(TxtProperty[0].nFontColor));
            qDebug() << "ui->adaptText->setChecked(TxtProperty[0].adapt);";
            ui->adaptText->setChecked(TxtProperty[0].adapt);
            //���塢б����»���
            ui->IfBold->setChecked(TxtProperty[0].bold);
            ui->IfItalic->setChecked(TxtProperty[0].italic);
            ui->m_underlinecheck->setChecked(TxtProperty[0].underline);
        }

        if(TxtProperty[0].adapt){
            ui->FontSize->setEnabled(false);
            ui->label_4->setEnabled(false);
            ui->combo_Alignment->setEnabled(false);
            ui->label_type_5->setEnabled(false);
        }else{
            ui->FontSize->setEnabled(true);
            ui->label_4->setEnabled(true);
            ui->combo_Alignment->setEnabled(true);
            ui->label_type_5->setEnabled(true);
        }
        //�־�
        ui->WordInterval->setValue(item->m_text.sFontSpace);
        //��ʽ
        ui->Pattern->setCurrentIndex(item->m_text.nStylePadding);
        //͸��ɫ
        ui->Alpha->setValue(item->m_text.nAlphaPadding);
        //����ɫ
        mColor = pwnd->StringTOColor(item->m_text.nBackColorPadding);
         ui->BackColor->setStyleSheet(QString("background:%1").arg(mColor.name()));
        //ǰ��ɫ
        mColor = pwnd->StringTOColor(item->m_text.nForeColorPadding);
         ui->FrontColor->setStyleSheet(QString("background:%1").arg(mColor.name()));
        //����
        ui->m_languagecmb->setCurrentIndex(0);
        if(ui->m_languagecmb->currentIndex()==0){
            ui->WordInterval->setEnabled(true);
            ui->groupBox_3->setEnabled(true);//���
        }
        qDebug() << item->m_text.bFristLanguage;


    }
    isFlag=true;

    if("TEXT" == sName || "MIN" == sName || "MAX" == sName){
        ui->m_languagecmb->setEnabled(false);
        ui->m_check->setEnabled(false);
    }else{
        ui->m_languagecmb->setEnabled(true);
        ui->m_check->setEnabled(true);
    }
    if(item)
    {
        ui->m_check->setChecked(item->m_text.bFristLanguage);
        on_m_check_clicked(item->m_text.bFristLanguage);
    }
}

void StaticTextDlg::on_plainTextEdit_textChanged()
{
    if(!isFlag){
        return;
    }
    QString sTxt;
    int nIndex = ui->m_languagecmb->currentIndex();
    sTxt = ui->plainTextEdit->toPlainText();
    if(nIndex==NULL){
        TxtProperty[0].sText = sTxt;
    }else
    TxtProperty[nIndex].sText = sTxt;
    emit DrawTextView();
}

void StaticTextDlg::on_FontSize_currentIndexChanged(QString sFontSize)
{
    if(!isFlag){
        return;
    }
    int nIndex = ui->m_languagecmb->currentIndex();
    int sizeIndex=ui->FontSize->currentIndex();
    TxtProperty[nIndex].nfontsizeindex=sizeIndex;
    if(nIndex<0){
        nIndex=0;
    }
    TxtProperty[nIndex].nFontSize = sFontSize.toInt();
    emit DrawTextView();
}

void StaticTextDlg::on_font_currentIndexChanged(QString sFont)
{
    if(!isFlag){
        return;
    }
    int nIndex = ui->m_languagecmb->currentIndex();
    int nFont=ui->font->currentIndex();
    TxtProperty[nIndex].nfont=nFont;
    TxtProperty[nIndex].sFont = ui->font->currentText();
    emit DrawTextView();
}

void StaticTextDlg::on_m_check_clicked(bool checked)
{
    if(!isFlag){
        return;
    }
    qDebug() << "on_m_check_clicked--" <<checked;
    if(checked)
    {
        ui->m_languagecmb->setEnabled(false);
        ui->m_languagecmb->setCurrentIndex(0);
    }
    else
    {
        ui->m_languagecmb->setEnabled(true);
    }
    emit DrawTextView();
}



void StaticTextDlg::on_FontColor_clicked()
{
    if(!isFlag){
        return;
    }
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->FontColor,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCurrentFontColor(const QColor &)));
}

void StaticTextDlg::on_BackColor_clicked()
{
    if(!isFlag){
        return;
    }
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->BackColor,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCurrentBKColor(const QColor &)));

}

void StaticTextDlg::on_FrontColor_clicked()
{
    if(!isFlag){
        return;
    }
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->FrontColor,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCurrentFrontColor(const QColor &)));

}

void StaticTextDlg::setCurrentFontColor(const QColor & currentColor)
{
    if(!isFlag){
        return;
    }
    ui->FontColor->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    int nIndex = ui->m_languagecmb->currentIndex();
    TxtProperty[nIndex].nFontColor=currentColor.name();
    TxtProperty[nIndex].newColors=pwnd->ColorTOString(currentColor);
    emit DrawTextView();
}

void StaticTextDlg::setCurrentBKColor(const QColor & currentColor)
{
    if(!isFlag){
        return;
    }
    ui->BackColor->setStyleSheet(QString("background:%1").arg(currentColor.name()));
   emit DrawTextView();
}

void StaticTextDlg::setCurrentFrontColor(const QColor & currentColor)
{
    if(!isFlag){
        return;
    }
    ui->FrontColor->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    emit DrawTextView();
}

//����Ӧ
void StaticTextDlg::on_adaptText_clicked(bool checked)
{
    if(!isFlag){
        return;
    }
    int nIndex = ui->m_languagecmb->currentIndex();
    TxtProperty[nIndex].adapt=checked;
    if(checked){
            ui->FontSize->setEnabled(false);
            ui->label_4->setEnabled(false);
            ui->combo_Alignment->setEnabled(false);
            ui->label_type_5->setEnabled(false);
            ui->combo_Alignment->setCurrentIndex(0);
//            ui->FontSize->setEditText("5");
        }else{
            ui->FontSize->setEnabled(true);
            ui->label_4->setEnabled(true);
            ui->combo_Alignment->setEnabled(true);
            ui->label_type_5->setEnabled(true);
        }
    emit DrawTextView();
}
//�ı�λ��
void StaticTextDlg::on_combo_Alignment_currentIndexChanged(int index)
{
    if(!isFlag){
        return;
    }
    int nIndex = ui->m_languagecmb->currentIndex();
    TxtProperty[nIndex].TextAlignIndex=index;
    emit DrawTextView();
}
//����
void StaticTextDlg::on_IfBold_clicked(bool checked)
{
    if(!isFlag){
        return;
    }
    int nIndex = ui->m_languagecmb->currentIndex();
    TxtProperty[nIndex].bold=checked;
    emit DrawTextView();
}
//б��
void StaticTextDlg::on_IfItalic_clicked(bool checked)
{
    if(!isFlag){
        return;
    }
    int nIndex = ui->m_languagecmb->currentIndex();
    TxtProperty[nIndex].italic=checked;
    emit DrawTextView();
}
//�»���
void StaticTextDlg::on_m_underlinecheck_clicked(bool checked)
{
    if(!isFlag){
        return;
    }
    int nIndex = ui->m_languagecmb->currentIndex();
    TxtProperty[nIndex].underline=checked;
    emit DrawTextView();
}

//��ʽ
void StaticTextDlg::on_Pattern_currentIndexChanged(int index)
{
    if(!isFlag){
        return;
    }
    emit DrawTextView();
}
//͸����
void StaticTextDlg::on_Alpha_valueChanged(int )
{
    if(!isFlag){
        return;
    }
    emit DrawTextView();
}


void StaticTextDlg::on_WordInterval_valueChanged(int )
{
    emit DrawTextView();
}
