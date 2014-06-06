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

    ui->m_table->setRowCount(7);                 //设置行数
    ui->m_table->setColumnWidth(0,40);           //设置列宽
    ui->m_table->setColumnWidth(1,120);

    ui->m_fontcmb->addItems(QFontDatabase().families(QFontDatabase::Any));

    pwnd->InitFontSize(ui->m_fontsizecmb);//初始化字体大小选择框
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
    for(i= 0;i < pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();i++)    //初始化语言选择框
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
    QString sFontName = tr("宋体");
    InitFlag = false;
    i = ui->m_fontcmb->findText(sFontName);//字体设置默认为宋体
    if(i < 0)
    {
        sFontName = "System";
        i = ui->m_fontcmb->findText(sFontName);
    }
    ui->m_fontcmb->setCurrentIndex(i);

    for(i = 0; i < 7; i++)                     //初始化结构体
    {
        TextProperty[i].sColor = tr("0+0+0");  //字体颜色
        TextProperty[i].nWordInterval = 0;     //字距
        TextProperty[i].nPosition = 5;         //文本位置
        TextProperty[i].bIfFlick = false;      //是否闪烁
        for(j = 0; j < 5; j++)
        {
            TextProperty[i].nFontSize[j] = 10;    //字体大小
            TextProperty[i].sFont[j] = sFontName;//tr("宋体");

            if( j != 0)
            {
                str = QString("%1").arg(j+1);
                str = tr("lang")+str;
                TextProperty[i].sText[j] = str;
            }
        }
    } //end for

    ui->m_radio5->setChecked(true);        //居中对齐
    ui->m_fontsizecmb->setCurrentIndex(5); //字体大小



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
    ui->m_languagecmb->setCurrentIndex(0);   //初始化设置多语言

    QTableWidgetItem *mItem;                     //设置指定项为选中状态
    mItem = ui->m_table->item(0,0);
    ui->m_table->setItemSelected(mItem,true);

    ui->m_textedit->setPlainText(tr("Sunday"));
    ui->m_textedit->setFocus();
    ui->m_textedit->selectAll();
    InitFlag = true;
}
void QWeekDisplaytextDlg::on_m_languagecmb_currentIndexChanged(int index)//语言
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
        ui->m_fontsizecmb->setCurrentIndex(nIndex);                  //设置字体大小

    str = TextProperty[nCurrentIndex].sFont[nLanguageIndex]; //设置字体
    nIndex = ui->m_fontcmb->findText(str);
    if(nIndex != -1)
        ui->m_fontcmb->setCurrentIndex(nIndex);

    emit SetTextProperty();
}

void QWeekDisplaytextDlg::on_m_fontsizecmb_currentIndexChanged(int index) //字体大小
{
    if(!InitFlag)
        return;

    QString sFontSize;
    int nLanguageIndex = ui->m_languagecmb->currentIndex();            //获得多语言下标
    sFontSize = ui->m_fontsizecmb->currentText();
    TextProperty[nCurrentIndex].nFontSize[nLanguageIndex] = sFontSize.toInt();
    emit SetTextProperty();
}
void QWeekDisplaytextDlg::on_m_wordintervalspin_valueChanged(int )//字距
{
    //判断输入是否正确
    TextProperty[nCurrentIndex].nWordInterval = ui->m_wordintervalspin->value();
    emit SetTextProperty();
}

void QWeekDisplaytextDlg::on_m_textedit_textChanged() //文本输入
{
    if(!InitFlag)
        return;
    int nLanguageIndex = ui->m_languagecmb->currentIndex();            //获得多语言下标
    QString sText = ui->m_textedit->toPlainText();                     //获得文本
    TextProperty[nCurrentIndex].sText[nLanguageIndex] = sText;         //存储文本
    ui->m_table->setItem(nCurrentIndex,1,new QTableWidgetItem(sText)); //在列表框中设置文本
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
    int nLanguageIndex = ui->m_languagecmb->currentIndex();            //获得多语言下标
    int nIndex = 0;
    QColor nColor;

    str = QString("%1").arg(TextProperty[nCurrentIndex].nFontSize[nLanguageIndex]);
    nIndex = ui->m_fontsizecmb->findText(str);
    if(nIndex != -1)
        ui->m_fontsizecmb->setCurrentIndex(nIndex);                  //设置字体大小

    str = TextProperty[nCurrentIndex].sFont[nLanguageIndex]; //设置字体
    nIndex = ui->m_fontcmb->findText(str);
    if(nIndex != -1)
        ui->m_fontcmb->setCurrentIndex(nIndex);

    nColor = pwnd->StringTOColor(TextProperty[nCurrentIndex].sColor);//设置字体颜色
 //   pTextColor->setCurrentColor(nColor);
    ui->Text_Color->setStyleSheet( QString("background:%1").arg(nColor.name()));

    ui->m_wordintervalspin->setValue(TextProperty[nCurrentIndex].nWordInterval);//设置字距
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

    switch(TextProperty[nCurrentIndex].nPosition)                    //文本位置
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
        datalist->replace(index+i*4,TextProperty[i].sColor);        //字体颜色

        sTmp=QString::number(TextProperty[i].nWordInterval);
        datalist->replace(index+1+i*4,sTmp);                        //字距

        sTmp=QString::number(TextProperty[i].nPosition);        //文本位置
        datalist->replace(index+2+i*4,sTmp);

        sTmp=QString::number(TextProperty[i].bIfFlick);         //是否闪烁
        datalist->replace(index+3+i*4,sTmp);
    }

    nTemp = index+28;
    for(i = 0; i < 7;i++)
    {
        for(int j = 0; j < 5; j++)
        {
            sTmp=QString::number(TextProperty[i].nFontSize[j]); //字体大小
            datalist->replace(nTemp,sTmp);
            nTemp++;

            datalist->replace(nTemp,TextProperty[i].sText[j]);//文本
            nTemp++;

            datalist->replace(nTemp,TextProperty[i].sFont[j]);//字体
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
        nCurrentIndex  = datalist.at(190).toInt(); //当前状态
        for(i = 0; i < 7;i++)
        {
            TextProperty[i].sColor = datalist.at(index+i*4);   //字体颜色

            sTmp = datalist.at(index+1+i*4);
            TextProperty[i].nWordInterval = sTmp.toInt();//字距

            sTmp = datalist.at(index+2+i*4);
            TextProperty[i].nPosition = sTmp.toInt();   //文本位置

            sTmp = datalist.at(index+3+i*4);
            TextProperty[i].bIfFlick = sTmp.toInt();    //是否闪烁
        }

        nTemp = index+28;
        for(i = 0; i < 7;i++)
        {
            for(int j = 0; j < 5; j++)
            {
                sTmp = datalist.at(nTemp);
                TextProperty[i].nFontSize[j] = sTmp.toInt();  //字体大小
                nTemp++;

                TextProperty[i].sText[j] = datalist.at(nTemp);//文本
                nTemp++;

                TextProperty[i].sFont[j] = datalist.at(nTemp);//字体
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
            ui->m_fontsizecmb->setCurrentIndex(nTemp);                  //设置字体大小

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

        switch(TextProperty[nCurrentIndex].nPosition)                    //文本位置
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

        QTableWidgetItem *mItem;                     //设置指定项为选中状态
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
    int nLanguageIndex = ui->m_languagecmb->currentIndex();            //获得多语言下标
    TextProperty[nCurrentIndex].sFont[nLanguageIndex] = sFont;
    emit SetTextProperty();
}
void QWeekDisplaytextDlg::on_Text_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->Text_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setTextColor(const QColor &)));

}
void QWeekDisplaytextDlg::setTextColor(const QColor & mColor)       //文本色
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
                TextProperty[i].nFontSize[j] = TextProperty[0].nFontSize[j];// 字体大小
                TextProperty[i].sFont[j] = TextProperty[0].sFont[j];// 字体类别
            }
            TextProperty[i].sColor = TextProperty[0].sColor;//字体颜色
            TextProperty[i].nWordInterval = TextProperty[0].nWordInterval;//字距
            TextProperty[i].nPosition = TextProperty[0].nPosition;//文本位置
            TextProperty[i].bIfFlick = TextProperty[0].bIfFlick;//是否闪烁
        }
        OnClickCell();
    }
    else
    {
        ui->groupBox_3->setEnabled(true);
    }
}
