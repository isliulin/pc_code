#include "qweekdisplaytextdlg.h"
#include <QFontDatabase>
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QWeekDisplaytextDlg::QWeekDisplaytextDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QWeekDisplaytextDlg)
{
    ui->setupUi(this);

    int i = 0;
    QString str = "";
    InitFlag = false;

    ui->m_table->setRowCount(7);                 //��������
    ui->m_table->setColumnWidth(0,40);           //�����п�
    ui->m_table->setColumnWidth(1,120);

    ui->m_fontcmb->addItems(QFontDatabase().families(QFontDatabase::Any));

    pwnd->InitFontSize(ui->m_fontsizecmb);//��ʼ�������Сѡ���
     for(i = 0; i < 7; i++)
    {
        ui->m_table->setRowHeight(i,25);
        str = QString("%1").arg(i);
        ui->m_table->setItem(i,0,new QTableWidgetItem(str));
    }

    QVector<QString>language_vector;
    for(int i=0;i < pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();i++)
    {
        language_vector.push_back(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }
    for(i= 0;i < pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();i++)    //��ʼ������ѡ���
    {
        ui->m_languagecmb->addItem(language_vector.at(i));
    }

    ui->m_table->verticalHeader()->setVisible(false);

    ui->m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    InitFlag = true;
}

QWeekDisplaytextDlg::~QWeekDisplaytextDlg()
{
    delete ui;
}

void QWeekDisplaytextDlg::InitParament()
{
    int i = 0;
    int j = 0;
    QString str = "";
    nCurrentIndex = 0;
    QString sFontName = tr("����");
    InitFlag = false;
    i = ui->m_fontcmb->findText(sFontName);//��������Ĭ��Ϊ����
    if(i < 0)
    {
        sFontName = "System";
        i = ui->m_fontcmb->findText(sFontName);
    }
    ui->m_fontcmb->setCurrentIndex(i);

    for(i = 0; i < 7; i++)                     //��ʼ���ṹ��
    {
        TextProperty[i].sColor = tr("0+0+0");  //������ɫ
        TextProperty[i].nWordInterval = 0;     //�־�
        TextProperty[i].nPosition = 5;         //�ı�λ��
        TextProperty[i].bIfFlick = false;      //�Ƿ���˸
        for(j = 0; j < 5; j++)
        {
            TextProperty[i].nFontSize[j] = 10;    //�����С
            TextProperty[i].sFont[j] = sFontName;//tr("����");

            if( j != 0)
            {
                str = QString("%1").arg(j+1);
                str = tr("lang")+str;
                TextProperty[i].sText[j] = str;
            }
        }
    } //end for

    ui->m_radio5->setChecked(true);        //���ж���
    ui->m_fontsizecmb->setCurrentIndex(5); //�����С



    ui->checkBox->setChecked(false);
    TextProperty[0].sText[0] = tr("Sunday");
    TextProperty[1].sText[0] = tr("Monday");
    TextProperty[2].sText[0] = tr("Tuesday");
    TextProperty[3].sText[0] = tr("Wednesday");
    TextProperty[4].sText[0] = tr("Thursday");
    TextProperty[5].sText[0] = tr("Friday");
    TextProperty[6].sText[0] = tr("Saturday");

    for(i = 0; i < 7; i++)
    {
        ui->m_table->setItem(i,1,new QTableWidgetItem(TextProperty[i].sText[0]));
    }

//    pTextColor->setCurrentColor(QColor(0,0,0));
    ui->Text_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));

    QModelIndex index;
    index.child(0,0);
    ui->m_table->setCurrentIndex(index);
    nCurrentIndex = 0;
    ui->m_languagecmb->setCurrentIndex(0);   //��ʼ�����ö�����

    QTableWidgetItem *mItem;                     //����ָ����Ϊѡ��״̬
    mItem = ui->m_table->item(0,0);
    ui->m_table->setItemSelected(mItem,true);

    ui->m_textedit->setPlainText(tr("Sunday"));
    ui->m_textedit->setFocus();
    ui->m_textedit->selectAll();
    InitFlag = true;
}
void QWeekDisplaytextDlg::on_m_languagecmb_currentIndexChanged(int index)//����
{
    if(index == 0)
    {
        ui->label_19->setEnabled(true);
        ui->Text_Color->setEnabled(true);
        ui->label_2->setEnabled(true);
        ui->m_flickcheck->setEnabled(true);
        ui->label_3->setEnabled(true);
        ui->m_wordintervalspin->setEnabled(true);
        ui->groupBox_6->setEnabled(true);
    }
    else
    {
        ui->label_19->setEnabled(false);
        ui->Text_Color->setEnabled(false);
        ui->label_2->setEnabled(false);
        ui->m_flickcheck->setEnabled(false);
        ui->label_3->setEnabled(false);
        ui->m_wordintervalspin->setEnabled(false);
        ui->groupBox_6->setEnabled(false);
    }

    if(!InitFlag)
        return;
    int nLanguageIndex = ui->m_languagecmb->currentIndex();
    int i = 0;
    int nIndex = 0;
    QString str = "";

    for(i = 0; i < 7; i++)
    {
        ui->m_table->setItem(i,1,new QTableWidgetItem(TextProperty[i].sText[nLanguageIndex]));
    }
    ui->m_textedit->setPlainText(TextProperty[nCurrentIndex].sText[nLanguageIndex]);
    ui->m_textedit->setFocus();

    str = QString("%1").arg(TextProperty[nCurrentIndex].nFontSize[nLanguageIndex]);
    nIndex = ui->m_fontsizecmb->findText(str);
    if(nIndex != -1)
        ui->m_fontsizecmb->setCurrentIndex(nIndex);                  //���������С

    str = TextProperty[nCurrentIndex].sFont[nLanguageIndex]; //��������
    nIndex = ui->m_fontcmb->findText(str);
    if(nIndex != -1)
        ui->m_fontcmb->setCurrentIndex(nIndex);

    emit SetTextProperty();
}

void QWeekDisplaytextDlg::on_m_fontsizecmb_currentIndexChanged(int index) //�����С
{
    if(!InitFlag)
        return;

    QString sFontSize;
    int nLanguageIndex = ui->m_languagecmb->currentIndex();            //��ö������±�
    sFontSize = ui->m_fontsizecmb->currentText();
    TextProperty[nCurrentIndex].nFontSize[nLanguageIndex] = sFontSize.toInt();
    emit SetTextProperty();
}
void QWeekDisplaytextDlg::on_m_wordintervalspin_valueChanged(int )//�־�
{
    //�ж������Ƿ���ȷ
    TextProperty[nCurrentIndex].nWordInterval = ui->m_wordintervalspin->value();
    emit SetTextProperty();
}

void QWeekDisplaytextDlg::on_m_textedit_textChanged() //�ı�����
{
    if(!InitFlag)
        return;
    int nLanguageIndex = ui->m_languagecmb->currentIndex();            //��ö������±�
    QString sText = ui->m_textedit->toPlainText();                     //����ı�
    TextProperty[nCurrentIndex].sText[nLanguageIndex] = sText;         //�洢�ı�
    ui->m_table->setItem(nCurrentIndex,1,new QTableWidgetItem(sText)); //���б���������ı�
    emit SetTextProperty();
}

void QWeekDisplaytextDlg::on_m_table_clicked(QModelIndex index)
{
    nCurrentIndex = ui->m_table->currentIndex().row();
    OnClickCell();
}

void QWeekDisplaytextDlg::OnClickCell()
{
    QString str = "";
    int nLanguageIndex = ui->m_languagecmb->currentIndex();            //��ö������±�
    int nIndex = 0;
    QColor nColor;

    str = QString("%1").arg(TextProperty[nCurrentIndex].nFontSize[nLanguageIndex]);
    nIndex = ui->m_fontsizecmb->findText(str);
    if(nIndex != -1)
        ui->m_fontsizecmb->setCurrentIndex(nIndex);                  //���������С

    str = TextProperty[nCurrentIndex].sFont[nLanguageIndex]; //��������
    nIndex = ui->m_fontcmb->findText(str);
    if(nIndex != -1)
        ui->m_fontcmb->setCurrentIndex(nIndex);

    nColor = pwnd->StringTOColor(TextProperty[nCurrentIndex].sColor);//����������ɫ
 //   pTextColor->setCurrentColor(nColor);
    ui->Text_Color->setStyleSheet( QString("background:%1").arg(nColor.name()));

    ui->m_wordintervalspin->setValue(TextProperty[nCurrentIndex].nWordInterval);//�����־�
    ui->m_flickcheck->setCurrentIndex(TextProperty[nCurrentIndex].bIfFlick);
    ui->m_radio1->setChecked(false);
    ui->m_radio2->setChecked(false);
    ui->m_radio3->setChecked(false);
    ui->m_radio4->setChecked(false);
    ui->m_radio5->setChecked(false);
    ui->m_radio6->setChecked(false);
    ui->m_radio7->setChecked(false);
    ui->m_radio8->setChecked(false);
    ui->m_radio9->setChecked(false);

    switch(TextProperty[nCurrentIndex].nPosition)                    //�ı�λ��
    {
        case 1:ui->m_radio1->setChecked(true);break;
        case 2:ui->m_radio2->setChecked(true);break;
        case 3:ui->m_radio3->setChecked(true);break;
        case 4:ui->m_radio4->setChecked(true);break;
        case 5:ui->m_radio5->setChecked(true);break;
        case 6:ui->m_radio6->setChecked(true);break;
        case 7:ui->m_radio7->setChecked(true);break;
        case 8:ui->m_radio8->setChecked(true);break;
        case 9:ui->m_radio9->setChecked(true);break;
        default:ui->m_radio5->setChecked(true);break;
    }

    ui->m_textedit->setPlainText(TextProperty[nCurrentIndex].sText[nLanguageIndex]);
    ui->m_textedit->setFocus();
    ui->m_textedit->selectAll();

    emit SetTextProperty();
    emit ClickCell();
}
void QWeekDisplaytextDlg::on_m_radio1_clicked()
{
    TextProperty[nCurrentIndex].nPosition = 1;
    emit SetTextProperty();
}

void QWeekDisplaytextDlg::on_m_radio2_clicked()
{
    TextProperty[nCurrentIndex].nPosition = 2;
    emit SetTextProperty();
}

void QWeekDisplaytextDlg::on_m_radio3_clicked()
{
    TextProperty[nCurrentIndex].nPosition = 3;
    emit SetTextProperty();
}

void QWeekDisplaytextDlg::on_m_radio4_clicked()
{
    TextProperty[nCurrentIndex].nPosition = 4;
    emit SetTextProperty();
}

void QWeekDisplaytextDlg::on_m_radio5_clicked()
{
    TextProperty[nCurrentIndex].nPosition = 5;
    emit SetTextProperty();
}

void QWeekDisplaytextDlg::on_m_radio6_clicked()
{
    TextProperty[nCurrentIndex].nPosition = 6;
    emit SetTextProperty();
}

void QWeekDisplaytextDlg::on_m_radio7_clicked()
{
    TextProperty[nCurrentIndex].nPosition = 7;
    emit SetTextProperty();
}

void QWeekDisplaytextDlg::on_m_radio8_clicked()
{
    TextProperty[nCurrentIndex].nPosition = 8;
    emit SetTextProperty();
}

void QWeekDisplaytextDlg::on_m_radio9_clicked()
{
    TextProperty[nCurrentIndex].nPosition = 9;
    emit SetTextProperty();
}

void QWeekDisplaytextDlg::SaveWeekdayTextPage(QStringList *datalist, int index)
{
    QString sTmp;
    int i = 0;
    int nTemp = 0;

    for(i = 0; i < 7;i++)
    {
        datalist->replace(index+i*4,TextProperty[i].sColor);        //������ɫ

        sTmp=QString::number(TextProperty[i].nWordInterval);
        datalist->replace(index+1+i*4,sTmp);                        //�־�

        sTmp=QString::number(TextProperty[i].nPosition);        //�ı�λ��
        datalist->replace(index+2+i*4,sTmp);

        sTmp=QString::number(TextProperty[i].bIfFlick);         //�Ƿ���˸
        datalist->replace(index+3+i*4,sTmp);
    }

    nTemp = index+28;
    for(i = 0; i < 7;i++)
    {
        for(int j = 0; j < 5; j++)
        {
            sTmp=QString::number(TextProperty[i].nFontSize[j]); //�����С
            datalist->replace(nTemp,sTmp);
            nTemp++;

            datalist->replace(nTemp,TextProperty[i].sText[j]);//�ı�
            nTemp++;

            datalist->replace(nTemp,TextProperty[i].sFont[j]);//����
            nTemp++;
        }
    }

    i=ui->m_check->isChecked();
    sTmp=QString::number(i);
    datalist->replace(nTemp,sTmp);

    nTemp++;
    sTmp=QString::number(ui->checkBox->isChecked());
    datalist->replace(nTemp,sTmp);
}

void QWeekDisplaytextDlg::DoubleClickInit(QGraphicsItem *pItem)
{
    QStringList datalist;
    QString sTmp;
    int i = 0;
    int nTemp = 0;
    int index = 20;
    QColor mColor;

    if(pItem)
    {
        InitFlag = false;
        datalist = pItem->data(GROUP_DATALIST_KEY).toStringList();
        on_m_languagecmb_currentIndexChanged(0);
        nCurrentIndex  = datalist.at(190).toInt(); //��ǰ״̬
        for(i = 0; i < 7;i++)
        {
            TextProperty[i].sColor = datalist.at(index+i*4);   //������ɫ

            sTmp = datalist.at(index+1+i*4);
            TextProperty[i].nWordInterval = sTmp.toInt();//�־�

            sTmp = datalist.at(index+2+i*4);
            TextProperty[i].nPosition = sTmp.toInt();   //�ı�λ��

            sTmp = datalist.at(index+3+i*4);
            TextProperty[i].bIfFlick = sTmp.toInt();    //�Ƿ���˸
        }

        nTemp = index+28;
        for(i = 0; i < 7;i++)
        {
            for(int j = 0; j < 5; j++)
            {
                sTmp = datalist.at(nTemp);
                TextProperty[i].nFontSize[j] = sTmp.toInt();  //�����С
                nTemp++;

                TextProperty[i].sText[j] = datalist.at(nTemp);//�ı�
                nTemp++;

                TextProperty[i].sFont[j] = datalist.at(nTemp);//����
                nTemp++;
            }
        }

        ui->m_check->setChecked(datalist.at(nTemp).toInt());
        on_m_check_clicked(datalist.at(nTemp).toInt());

        nTemp++;
        ui->checkBox->setChecked(datalist.at(nTemp).toInt());
        if(datalist.at(nTemp).toInt())
            ui->groupBox_3->setEnabled(false);
        else
            ui->groupBox_3->setEnabled(true);


        sTmp = QString("%1").arg(TextProperty[nCurrentIndex].nFontSize[0]);
        nTemp = ui->m_fontsizecmb->findText(sTmp);
        if(nTemp != -1)
            ui->m_fontsizecmb->setCurrentIndex(nTemp);                  //���������С

        sTmp = TextProperty[nCurrentIndex].sFont[0];
        nTemp = ui->m_fontcmb->findText(sTmp);
        if(nTemp != -1)
            ui->m_fontcmb->setCurrentIndex(nTemp);

        mColor = pwnd->StringTOColor(TextProperty[nCurrentIndex].sColor);
        ui->Text_Color->setStyleSheet( QString("background:%1").arg(mColor.name()));

        ui->m_flickcheck->setCurrentIndex(TextProperty[nCurrentIndex].bIfFlick);

        ui->m_wordintervalspin->setValue(TextProperty[nCurrentIndex].nWordInterval);

        ui->m_radio1->setChecked(false); //nCurrentIndex
        ui->m_radio2->setChecked(false);
        ui->m_radio3->setChecked(false);
        ui->m_radio4->setChecked(false);
        ui->m_radio5->setChecked(false);
        ui->m_radio6->setChecked(false);
        ui->m_radio7->setChecked(false);
        ui->m_radio8->setChecked(false);
        ui->m_radio9->setChecked(false);

        switch(TextProperty[nCurrentIndex].nPosition)                    //�ı�λ��
        {
            case 1:ui->m_radio1->setChecked(true);break;
            case 2:ui->m_radio2->setChecked(true);break;
            case 3:ui->m_radio3->setChecked(true);break;
            case 4:ui->m_radio4->setChecked(true);break;
            case 5:ui->m_radio5->setChecked(true);break;
            case 6:ui->m_radio6->setChecked(true);break;
            case 7:ui->m_radio7->setChecked(true);break;
            case 8:ui->m_radio8->setChecked(true);break;
            case 9:ui->m_radio9->setChecked(true);break;
            default:ui->m_radio5->setChecked(true);break;
        }

        for(i = 0; i < 7; i++)
        {
            ui->m_table->setItem(i,1,new QTableWidgetItem(TextProperty[i].sText[0]));
        }

        QTableWidgetItem *mItem;                     //����ָ����Ϊѡ��״̬
        mItem = ui->m_table->item(nCurrentIndex,0);
        ui->m_table->setItemSelected(mItem,true);

        InitFlag = true;
    }
}

void QWeekDisplaytextDlg::on_m_flickcheck_currentIndexChanged(int index)
{
    TextProperty[nCurrentIndex].bIfFlick = index;
}

void QWeekDisplaytextDlg::on_m_check_clicked(bool checked)
{
    if(checked)
    {
        ui->m_languagecmb->setEnabled(false);
        ui->m_languagecmb->setCurrentIndex(0);
    }
    else
    {
        ui->m_languagecmb->setEnabled(true);
    }
}

void QWeekDisplaytextDlg::on_m_fontcmb_currentIndexChanged(QString sFont)
{
    if(!InitFlag)
        return;
    int nLanguageIndex = ui->m_languagecmb->currentIndex();            //��ö������±�
    TextProperty[nCurrentIndex].sFont[nLanguageIndex] = sFont;
    emit SetTextProperty();
}
void QWeekDisplaytextDlg::on_Text_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->Text_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setTextColor(const QColor &)));

}
void QWeekDisplaytextDlg::setTextColor(const QColor & mColor)       //�ı�ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    TextProperty[nCurrentIndex].sColor = pwnd->ColorTOString(mColor);
    ui->Text_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    emit SetTextProperty();
}


void QWeekDisplaytextDlg::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->groupBox_3->setEnabled(false);
        for(int i= 1; i < 7;i++)
        {
            for(int j= 0; j < 5;j++)
            {
                TextProperty[i].nFontSize[j] = TextProperty[0].nFontSize[j];// �����С
                TextProperty[i].sFont[j] = TextProperty[0].sFont[j];// �������
            }
            TextProperty[i].sColor = TextProperty[0].sColor;//������ɫ
            TextProperty[i].nWordInterval = TextProperty[0].nWordInterval;//�־�
            TextProperty[i].nPosition = TextProperty[0].nPosition;//�ı�λ��
            TextProperty[i].bIfFlick = TextProperty[0].bIfFlick;//�Ƿ���˸
        }
        OnClickCell();
    }
    else
    {
        ui->groupBox_3->setEnabled(true);
    }
}
