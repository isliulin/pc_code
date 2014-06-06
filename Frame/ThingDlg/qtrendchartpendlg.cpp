#include "qtrendchartpendlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QTrendChartPenDlg::QTrendChartPenDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QTrendChartPenDlg)
{
    ui->setupUi(this);
    InitPenType(ui->P1_Line);
    InitPenType(ui->P2_Line);
    InitPenType(ui->P3_Line);
    InitPenType(ui->P4_Line);
    InitPenType(ui->P5_Line);
    InitPenType(ui->P6_Line);
    InitPenType(ui->P7_Line);
    InitPenType(ui->P8_Line);
}

QTrendChartPenDlg::~QTrendChartPenDlg()
{
    delete ui;
}

void QTrendChartPenDlg::Init(QGraphicsItem *pItem)
{
    QStringList datalist;
    if(pItem)
    {

            datalist = qVariantValue<QStringList>(pItem->data(GROUP_DATALIST_KEY));
            SetPenHide(datalist.at(154).toInt());
            // Pen1
            QString sTmp="";
            sTmp=datalist.at(100);
            ui->P1_Min->setText(sTmp); //the min of Pen1 100

            sTmp=datalist.at(101);
            ui->P1_Max->setText(sTmp); //the max of Pen1 101

            int nTmp=datalist.at(102).toInt();
            ui->P1_Line->setCurrentIndex(nTmp);//the line pattern 102
            ui->P1_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(103)).name()));

            // Pen2
            sTmp=datalist.at(104);
            ui->P2_Min->setText(sTmp); //the min of Pen2 104

            sTmp=datalist.at(105);
            ui->P2_Max->setText(sTmp); //the max of Pen2 105

            nTmp=datalist.at(106).toInt();
            ui->P2_Line->setCurrentIndex(nTmp);//the line pattern 106

            ui->P2_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(107)).name()));

            // Pen3
            sTmp=datalist.at(108);
            ui->P3_Min->setText(sTmp);//the min of Pen3 108


            sTmp=datalist.at(109);
            ui->P3_Max->setText(sTmp);//the max of Pen3 109

            nTmp=datalist.at(110).toInt();
            ui->P3_Line->setCurrentIndex(nTmp);//the line pattern 110

            ui->P3_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(111)).name()));

            // Pen4
            sTmp=datalist.at(112);
            ui->P4_Min->setText(sTmp); //the min of Pen4 112

            sTmp=datalist.at(113);
            ui->P4_Max->setText(sTmp); //the max of Pen4 113

            nTmp=datalist.at(114).toInt();
            ui->P4_Line->setCurrentIndex(nTmp);//the line pattern 114

            ui->P4_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(115)).name()));


            // Pen5
            sTmp=datalist.at(116);
            ui->P5_Min->setText(sTmp); //the min of Pen5 116

            sTmp=datalist.at(117);
            ui->P5_Max->setText(sTmp); //the max of Pen5 117

            nTmp=datalist.at(118).toInt();
            ui->P5_Line->setCurrentIndex(nTmp);//the line pattern 118

            ui->P5_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(119)).name()));


            // Pen6
            sTmp=datalist.at(120);
            ui->P6_Min->setText(sTmp); //the min of Pen6 120

            sTmp=datalist.at(121);
            ui->P6_Max->setText(sTmp); //the max of Pen6 121

            nTmp=datalist.at(122).toInt();
            ui->P6_Line->setCurrentIndex(nTmp);//the line pattern 122

            ui->P6_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(123)).name()));

            // Pen7
            sTmp=datalist.at(124);
            ui->P7_Min->setText(sTmp); //the min of Pen7 124

            sTmp=datalist.at(125);
            ui->P7_Max->setText(sTmp);//the max of Pen7 125

            nTmp=datalist.at(126).toInt();
            ui->P7_Line->setCurrentIndex(nTmp);//the line pattern 126
            ui->P7_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(127)).name()));


            // Pen8
            sTmp=datalist.at(128);
            ui->P8_Min->setText(sTmp);  //the min of Pen8 128

            sTmp=datalist.at(129);
            ui->P8_Max->setText(sTmp);  //the max of Pen7 129


            nTmp=datalist.at(130).toInt();
            ui->P8_Line->setCurrentIndex(nTmp);//the line pattern 130

            ui->P8_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(131)).name()));

    }
    else
    {/////////单击初始化
        ui->P1_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,255).name()));
        ui->P2_Color->setStyleSheet( QString("background:%1").arg(QColor(255,0,0).name()));
        ui->P3_Color->setStyleSheet( QString("background:%1").arg(QColor(0,255,0).name()));
        ui->P4_Color->setStyleSheet( QString("background:%1").arg(QColor(255,0,255).name()));
        ui->P5_Color->setStyleSheet( QString("background:%1").arg(QColor(192,192,192).name()));
        ui->P6_Color->setStyleSheet( QString("background:%1").arg(QColor(0,255,255).name()));
        ui->P7_Color->setStyleSheet( QString("background:%1").arg(QColor(85,0,0).name()));
        ui->P8_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));

        ui->P1_Line->setCurrentIndex(1);
        ui->P2_Line->setCurrentIndex(1);
        ui->P3_Line->setCurrentIndex(1);
        ui->P4_Line->setCurrentIndex(1);
        ui->P5_Line->setCurrentIndex(1);
        ui->P6_Line->setCurrentIndex(1);
        ui->P7_Line->setCurrentIndex(1);
        ui->P8_Line->setCurrentIndex(1);

        ui->groupBox_5->setHidden(true);
        ui->groupBox_6->setHidden(true);
        ui->groupBox_7->setHidden(true);
        ui->groupBox_8->setHidden(true);

    }

}

void QTrendChartPenDlg::SetPenHide(int nIndex)
{
    switch(nIndex)
    {
    case 1:
        ui->groupBox->setHidden(false);
        ui->groupBox_2->setHidden(true);
        ui->groupBox_3->setHidden(true);
        ui->groupBox_4->setHidden(true);
        ui->groupBox_5->setHidden(true);
        ui->groupBox_6->setHidden(true);
        ui->groupBox_7->setHidden(true);
        ui->groupBox_8->setHidden(true);
        break;
    case 2:
        ui->groupBox->setHidden(false);
        ui->groupBox_2->setHidden(false);
        ui->groupBox_3->setHidden(true);
        ui->groupBox_4->setHidden(true);
        ui->groupBox_5->setHidden(true);
        ui->groupBox_6->setHidden(true);
        ui->groupBox_7->setHidden(true);
        ui->groupBox_8->setHidden(true);
        break;
    case 3:
        ui->groupBox->setHidden(false);
        ui->groupBox_2->setHidden(false);
        ui->groupBox_3->setHidden(false);
        ui->groupBox_4->setHidden(true);
        ui->groupBox_5->setHidden(true);
        ui->groupBox_6->setHidden(true);
        ui->groupBox_7->setHidden(true);
        ui->groupBox_8->setHidden(true);
        break;
    case 4:
        ui->groupBox->setHidden(false);
        ui->groupBox_2->setHidden(false);
        ui->groupBox_3->setHidden(false);
        ui->groupBox_4->setHidden(false);
        ui->groupBox_5->setHidden(true);
        ui->groupBox_6->setHidden(true);
        ui->groupBox_7->setHidden(true);
        ui->groupBox_8->setHidden(true);
        break;
    case 5:
        ui->groupBox->setHidden(false);
        ui->groupBox_2->setHidden(false);
        ui->groupBox_3->setHidden(false);
        ui->groupBox_4->setHidden(false);
        ui->groupBox_5->setHidden(false);
        ui->groupBox_6->setHidden(true);
        ui->groupBox_7->setHidden(true);
        ui->groupBox_8->setHidden(true);
        break;
    case 6:
        ui->groupBox->setHidden(false);
        ui->groupBox_2->setHidden(false);
        ui->groupBox_3->setHidden(false);
        ui->groupBox_4->setHidden(false);
        ui->groupBox_5->setHidden(false);
        ui->groupBox_6->setHidden(false);
        ui->groupBox_7->setHidden(true);
        ui->groupBox_8->setHidden(true);
        break;
    case 7:
        ui->groupBox->setHidden(false);
        ui->groupBox_2->setHidden(false);
        ui->groupBox_3->setHidden(false);
        ui->groupBox_4->setHidden(false);
        ui->groupBox_5->setHidden(false);
        ui->groupBox_6->setHidden(false);
        ui->groupBox_7->setHidden(false);
        ui->groupBox_8->setHidden(true);
        break;
    case 8:
        ui->groupBox->setHidden(false);
        ui->groupBox_2->setHidden(false);
        ui->groupBox_3->setHidden(false);
        ui->groupBox_4->setHidden(false);
        ui->groupBox_5->setHidden(false);
        ui->groupBox_6->setHidden(false);
        ui->groupBox_7->setHidden(false);
        ui->groupBox_8->setHidden(false);
        break;
    }
}

void QTrendChartPenDlg::SavePenPage(QStringList *datalist, int index)
{
    QString sTmp = "";
    int nTmp = 0;

    // Pen1
    sTmp = ui->P1_Min->text();
    datalist->replace(index,sTmp);  //the min of Pen1 100

    sTmp = ui->P1_Max->text();
    datalist->replace(index+1,sTmp);//the max of Pen1 101

    nTmp=ui->P1_Line->currentIndex();
    sTmp=QString::number(nTmp);
    datalist->replace(index+2,sTmp);//the line pattern 102

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->P1_Color->palette().background().color());//线颜色
    datalist->replace(index+3,sTmp);


    // Pen2
    sTmp = ui->P2_Min->text();
    datalist->replace(index+4,sTmp);  //the min of Pen2 104

    sTmp = ui->P2_Max->text();
    datalist->replace(index+5,sTmp);//the max of Pen2 105

    nTmp=ui->P2_Line->currentIndex();
    sTmp=QString::number(nTmp);
    datalist->replace(index+6,sTmp);//the line pattern 106

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->P2_Color->palette().background().color());//线颜色
    datalist->replace(index+7,sTmp);

    // Pen3
    sTmp = ui->P3_Min->text();
    datalist->replace(index+8,sTmp);  //the min of Pen3 108

    sTmp = ui->P3_Max->text();
    datalist->replace(index+9,sTmp);//the max of Pen3 109

    nTmp=ui->P3_Line->currentIndex();
    sTmp=QString::number(nTmp);
    datalist->replace(index+10,sTmp);//the line pattern 110

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->P3_Color->palette().background().color());//线颜色
    datalist->replace(index+11,sTmp);

    // Pen4
    sTmp = ui->P4_Min->text();
    datalist->replace(index+12,sTmp);  //the min of Pen4 112

    sTmp = ui->P4_Max->text();
    datalist->replace(index+13,sTmp);//the max of Pen4 113

    nTmp=ui->P4_Line->currentIndex();
    sTmp=QString::number(nTmp);
    datalist->replace(index+14,sTmp);//the line pattern 114

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->P4_Color->palette().background().color());//线颜色
    datalist->replace(index+15,sTmp);

    // Pen5
    sTmp = ui->P5_Min->text();
    datalist->replace(index+16,sTmp);  //the min of Pen5 116

    sTmp = ui->P5_Max->text();
    datalist->replace(index+17,sTmp);//the max of Pen5 117

    nTmp=ui->P5_Line->currentIndex();
    sTmp=QString::number(nTmp);
    datalist->replace(index+18,sTmp);//the line pattern 118

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->P5_Color->palette().background().color());//线颜色
    datalist->replace(index+19,sTmp);

    // Pen6
    sTmp = ui->P6_Min->text();
    datalist->replace(index+20,sTmp);  //the min of Pen6 120

    sTmp = ui->P6_Max->text();
    datalist->replace(index+21,sTmp);//the max of Pen6 121

    nTmp=ui->P6_Line->currentIndex();
    sTmp=QString::number(nTmp);
    datalist->replace(index+22,sTmp);//the line pattern 122

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->P6_Color->palette().background().color());//线颜色
    datalist->replace(index+23,sTmp);

    // Pen7
    sTmp = ui->P7_Min->text();
    datalist->replace(index+24,sTmp);  //the min of Pen7 124

    sTmp = ui->P7_Max->text();
    datalist->replace(index+25,sTmp);//the max of Pen7 125

    nTmp=ui->P7_Line->currentIndex();
    sTmp=QString::number(nTmp);
    datalist->replace(index+26,sTmp);//the line pattern 126

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->P7_Color->palette().background().color());//线颜色
    datalist->replace(index+27,sTmp);

    // Pen8
    sTmp = ui->P8_Min->text();
    datalist->replace(index+28,sTmp);  //the min of Pen7 128

    sTmp = ui->P8_Max->text();
    datalist->replace(index+29,sTmp);//the max of Pen7 129

    nTmp=ui->P8_Line->currentIndex();
    sTmp=QString::number(nTmp);
    datalist->replace(index+30,sTmp);//the line pattern 130

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->P8_Color->palette().background().color());//线颜色
    datalist->replace(index+31,sTmp);
 }
int  QTrendChartPenDlg::TrendCheckMinMax(int DataType)
{
    int tempFlg=pwnd->CheckMinMax(ui->P1_Min->text(),ui->P1_Max->text(),DataType,0);
    if(tempFlg)
    {
        if(tempFlg==1||tempFlg==2||tempFlg==4)
        {
            ui->P1_Min->setFocus();
            ui->P1_Min->selectAll();

        }
        else if(tempFlg==3||tempFlg==5)
        {
            ui->P1_Max->setFocus();
            ui->P1_Max->selectAll();
        }
        return 0;
    }
    tempFlg=pwnd->CheckMinMax(ui->P2_Min->text(),ui->P2_Max->text(),DataType,0);
    if(tempFlg)
    {
        if(tempFlg==1||tempFlg==2||tempFlg==4)
        {
            ui->P2_Min->setFocus();
            ui->P2_Min->selectAll();

        }
        else if(tempFlg==3||tempFlg==5)
        {
            ui->P2_Max->setFocus();
            ui->P2_Max->selectAll();
        }
        return 0;
    }
     tempFlg=pwnd->CheckMinMax(ui->P3_Min->text(),ui->P3_Max->text(),DataType,0);
    if(tempFlg)
    {
        if(tempFlg==1||tempFlg==2||tempFlg==4)
        {
            ui->P3_Min->setFocus();
            ui->P3_Min->selectAll();

        }
        else if(tempFlg==3||tempFlg==5)
        {
            ui->P3_Max->setFocus();
            ui->P3_Max->selectAll();
        }
        return 0;
    }
     tempFlg=pwnd->CheckMinMax(ui->P4_Min->text(),ui->P4_Max->text(),DataType,0);
    if(tempFlg)
    {
        if(tempFlg==1||tempFlg==2||tempFlg==4)
        {
            ui->P4_Min->setFocus();
            ui->P4_Min->selectAll();

        }
        else if(tempFlg==3||tempFlg==5)
        {
            ui->P4_Max->setFocus();
            ui->P4_Max->selectAll();
        }
        return 0;
    }
     tempFlg=pwnd->CheckMinMax(ui->P5_Min->text(),ui->P5_Max->text(),DataType,0);
    if(tempFlg)
    {
        if(tempFlg==1||tempFlg==2||tempFlg==4)
        {
            ui->P5_Min->setFocus();
            ui->P5_Min->selectAll();

        }
        else if(tempFlg==3||tempFlg==5)
        {
            ui->P5_Max->setFocus();
            ui->P5_Max->selectAll();
        }
        return 0;
    }
     tempFlg=pwnd->CheckMinMax(ui->P6_Min->text(),ui->P6_Max->text(),DataType,0);
    if(tempFlg)
    {
        if(tempFlg==1||tempFlg==2||tempFlg==4)
        {
            ui->P6_Min->setFocus();
            ui->P6_Min->selectAll();

        }
        else if(tempFlg==3||tempFlg==5)
        {
            ui->P6_Max->setFocus();
            ui->P6_Max->selectAll();
        }
        return 0;
    }
     tempFlg=pwnd->CheckMinMax(ui->P7_Min->text(),ui->P7_Max->text(),DataType,0);
    if(tempFlg)
    {
        if(tempFlg==1||tempFlg==2||tempFlg==4)
        {
            ui->P7_Min->setFocus();
            ui->P7_Min->selectAll();

        }
        else if(tempFlg==3||tempFlg==5)
        {
            ui->P7_Max->setFocus();
            ui->P7_Max->selectAll();
        }
        return 0;
    }
    tempFlg=pwnd->CheckMinMax(ui->P8_Min->text(),ui->P8_Max->text(),DataType,0);
    if(tempFlg)
    {
        if(tempFlg==1||tempFlg==2||tempFlg==4)
        {
            ui->P8_Min->setFocus();
            ui->P8_Min->selectAll();

        }
        else if(tempFlg==3||tempFlg==5)
        {
            ui->P8_Max->setFocus();
            ui->P8_Max->selectAll();
        }
        return 0;
    }
    return 1;
  }

void QTrendChartPenDlg::on_P1_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->P1_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setColorP1(const QColor &)));

}
void QTrendChartPenDlg::setColorP1(const QColor & mColor)       //文本色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->P1_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QTrendChartPenDlg::on_P2_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->P2_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setColorP2(const QColor &)));

}
void QTrendChartPenDlg::setColorP2(const QColor & mColor)       //文本色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->P2_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QTrendChartPenDlg::on_P3_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->P3_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setColorP3(const QColor &)));

}
void QTrendChartPenDlg::setColorP3(const QColor & mColor)       //文本色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->P3_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QTrendChartPenDlg::on_P4_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->P4_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setColorP4(const QColor &)));

}
void QTrendChartPenDlg::setColorP4(const QColor & mColor)       //文本色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->P4_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QTrendChartPenDlg::on_P5_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->P5_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setColorP5(const QColor &)));

}
void QTrendChartPenDlg::setColorP5(const QColor & mColor)       //文本色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->P5_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QTrendChartPenDlg::on_P6_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->P6_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setColorP6(const QColor &)));

}
void QTrendChartPenDlg::setColorP6(const QColor & mColor)       //文本色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->P6_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QTrendChartPenDlg::on_P7_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->P7_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setColorP7(const QColor &)));

}
void QTrendChartPenDlg::setColorP7(const QColor & mColor)       //文本色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->P7_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QTrendChartPenDlg::on_P8_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->P8_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setColorP8(const QColor &)));

}
void QTrendChartPenDlg::setColorP8(const QColor & mColor)       //文本色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->P8_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QTrendChartPenDlg::InitPenType( QComboBox * pComboBox)       //笔的线条样式
{
    pComboBox->addItem(QIcon(":/linetype/images/LineType/L0.ico"),tr("0"));
    pComboBox->addItem(QIcon(":/linetype/images/LineType/L1.ico"),tr("1"));
    pComboBox->addItem(QIcon(":/linetype/images/LineType/L2.ico"),tr("2"));
    pComboBox->addItem(QIcon(":/linetype/images/LineType/L3.ico"),tr("3"));
    pComboBox->addItem(QIcon(":/linetype/images/LineType/L4.ico"),tr("4"));
    pComboBox->addItem(QIcon(":/linetype/images/LineType/L5.ico"),tr("5"));
    pComboBox->addItem(QIcon(":/linetype/images/LineType/L6.ico"),tr("6"));
    pComboBox->addItem(QIcon(":/linetype/images/LineType/L7.ico"),tr("7"));
    pComboBox->addItem(QIcon(":/linetype/images/LineType/L8.ico"),tr("8"));

}
