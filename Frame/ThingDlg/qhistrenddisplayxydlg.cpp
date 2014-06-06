#include "qhistrenddisplayxydlg.h"
#include "ui_qhistrenddisplayxydlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QHisTrendDisplayXYDlg::QHisTrendDisplayXYDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QHisTrendDisplayXYDlg)
{
    ui->setupUi(this);
    max=new QIntValidator(this);
    ui->Y_Max->setValidator(max);
    ui->Y_Min->setValidator(max);
    ui->dateEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->calendarWidget()->setGridVisible(true);
    QDate sdate=QDate::currentDate();
    ui->dateEdit->setDate(sdate);
}

QHisTrendDisplayXYDlg::~QHisTrendDisplayXYDlg()
{
    if(max!=NULL)
    {
        delete max;
        max=NULL;
    }
    delete ui;
}

void QHisTrendDisplayXYDlg::on_X_DisplayTime_clicked(bool checked)
{
    if(checked)
    {
        ui->label_5->setHidden(false);
        ui->X_Time->setHidden(false);
        ui->X_Font->setHidden(false);
        ui->label_15->setHidden(false);
        ui->groupBox_3->setHidden(false);
    }
    else
    {
        ui->label_5->setHidden(true);
        ui->X_Time->setHidden(true);
        ui->X_Font->setHidden(true);
        ui->label_15->setHidden(true);
        ui->groupBox_3->setHidden(true);

    }
}

void QHisTrendDisplayXYDlg::on_Y_DisplayMarks_clicked(bool checked)
{
    if(checked)
    {
        ui->groupBox_4->setHidden(false);
    }
    else
    {
        ui->groupBox_4->setHidden(true);
    }
}

void QHisTrendDisplayXYDlg::on_X_Show_Ticks_clicked(bool checked)
{
    bool IfShowY_Axis=ui->X_Show_Y_Axis->isChecked();

    if(checked)
    {
        ui->label->setHidden(false);
        ui->X_Axis_Color->setHidden(false);

        ui->label_3->setHidden(false);
        ui->X_Major->setHidden(false);
        ui->label_4->setHidden(false);
        ui->X_Sub->setHidden(false);
        ui->X_DisplayTime->setHidden(false);
        on_X_DisplayTime_clicked(ui->X_DisplayTime->isChecked());
    }
    else
    {
        if(!IfShowY_Axis)
        {
            ui->label->setHidden(true);
            ui->X_Axis_Color->setHidden(true);
            ui->label_2->setHidden(true);
            ui->X_Grid_Color->setHidden(true);

            ui->label_3->setHidden(true);
            ui->X_Major->setHidden(true);
            ui->label_4->setHidden(true);
            ui->X_Sub->setHidden(true);
            ui->X_DisplayTime->setHidden(true);
            ui->label_5->setHidden(true);
            ui->X_Time->setHidden(true);
            ui->label_15->setHidden(true);
            ui->X_Font->setHidden(true);
            ui->groupBox_3->setHidden(true);
        }
        ui->label->setHidden(true);
        ui->X_Axis_Color->setHidden(true);

    }
}

void QHisTrendDisplayXYDlg::on_X_Show_Y_Axis_clicked(bool checked)
{
    bool IfShowTicks=ui->X_Show_Ticks->isChecked();
    if(checked)
    {
        ui->label_2->setHidden(false);
        ui->X_Grid_Color->setHidden(false);
        ui->label_3->setHidden(false);
        ui->X_Major->setHidden(false);
        ui->label_4->setHidden(false);
        ui->X_Sub->setHidden(false);
        ui->X_DisplayTime->setHidden(false);
        on_X_DisplayTime_clicked(ui->X_DisplayTime->isChecked());
    }
    else
    {
        if(!IfShowTicks)
        {
            ui->label->setHidden(true);
            ui->X_Axis_Color->setHidden(true);
            ui->label_2->setHidden(true);
            ui->X_Grid_Color->setHidden(true);
            ui->label_3->setHidden(true);
            ui->X_Major->setHidden(true);
            ui->label_4->setHidden(true);
            ui->X_Sub->setHidden(true);
            ui->X_DisplayTime->setHidden(true);
            ui->label_5->setHidden(true);
            ui->X_Time->setHidden(true);
            ui->label_15->setHidden(true);
            ui->X_Font->setHidden(true);
            ui->groupBox_3->setHidden(true);
           }
        ui->label_2->setHidden(true);
        ui->X_Grid_Color->setHidden(true);
     }
}

void QHisTrendDisplayXYDlg::on_Y_Show_Ticks_clicked(bool checked)
{
    bool IfShowX_Axis=ui->Y_Show_X_Axis->isChecked();

    if(checked)
    {
        ui->label_6->setHidden(false);
        ui->Y_Axis_Color->setHidden(false);

        ui->label_8->setHidden(false);
        ui->Y_Major->setHidden(false);
        ui->label_9->setHidden(false);
        ui->Y_Sub->setHidden(false);
        ui->Y_DisplayMarks->setHidden(false);
        on_Y_DisplayMarks_clicked(ui->Y_DisplayMarks->isChecked());
    }
    else
    {
        if(!IfShowX_Axis)
        {
            ui->label_6->setHidden(true);
            ui->Y_Axis_Color->setHidden(true);
            ui->label_7->setHidden(true);
            ui->Y_Grid_Color->setHidden(true);

            ui->label_8->setHidden(true);
            ui->Y_Major->setHidden(true);
            ui->label_9->setHidden(true);
            ui->Y_Sub->setHidden(true);
            ui->Y_DisplayMarks->setHidden(true);
            ui->groupBox_4->setHidden(true);
        }
        ui->label_6->setHidden(true);
        ui->Y_Axis_Color->setHidden(true);
    }
}

void QHisTrendDisplayXYDlg::on_Y_Show_X_Axis_clicked(bool checked)
{
    bool IfShowTicks=ui->Y_Show_Ticks->isChecked();
    if(checked)
    {
        ui->label_7->setHidden(false);
        ui->Y_Grid_Color->setHidden(false);

        ui->label_8->setHidden(false);
        ui->Y_Major->setHidden(false);
        ui->label_9->setHidden(false);
        ui->Y_Sub->setHidden(false);
        ui->Y_DisplayMarks->setHidden(false);
        on_Y_DisplayMarks_clicked(ui->Y_DisplayMarks->isChecked());

    }
    else
    {
        if(!IfShowTicks)
        {
            ui->label_6->setHidden(true);
            ui->Y_Axis_Color->setHidden(true);
            ui->label_7->setHidden(true);
            ui->Y_Grid_Color->setHidden(true);
            ui->label_8->setHidden(true);
            ui->Y_Major->setHidden(true);
            ui->label_9->setHidden(true);
            ui->Y_Sub->setHidden(true);
            ui->Y_DisplayMarks->setHidden(true);
            ui->groupBox_4->setHidden(true);
          }
        ui->label_7->setHidden(true);
        ui->Y_Grid_Color->setHidden(true);
     }
}

void QHisTrendDisplayXYDlg::SaveXYPage(QStringList *datalist, int index)
{
    QString sTmp = "";
    int nTmp = 0;

    //存Y轴
    nTmp=ui->Y_Show_Ticks->isChecked();
    sTmp=QString::number(nTmp);
    datalist->replace(index,sTmp);//显示刻度20

    nTmp=ui->Y_Show_X_Axis->isChecked();
    sTmp=QString::number(nTmp);
    datalist->replace(index+1,sTmp);//显示X轴曲线21

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->Y_Axis_Color->palette().background().color());//边框色
    datalist->replace(index+2,sTmp);

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->Y_Grid_Color->palette().background().color());//前景色
    datalist->replace(index+3,sTmp);

    nTmp=ui->Y_Major->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+4,sTmp);//主分刻度24

    nTmp=ui->Y_Sub->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+5,sTmp);//次分刻度25

    nTmp=ui->Y_DisplayMarks->isChecked();
    sTmp=QString::number(nTmp);
    datalist->replace(index+6,sTmp);//显示刻度标示26

    sTmp = ui->Y_FontSize->currentText();
    datalist->replace(index+7,sTmp);//字体大小27

    sTmp = ui->Y_Min->text();
    datalist->replace(index+8,sTmp);//最小值28

    sTmp = ui->Y_Max->text();
    datalist->replace(index+9,sTmp);//最大值29

    nTmp=ui->Y_TotalDigits->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+10,sTmp);//总位数30

    nTmp=ui->Y_Fractional->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+11,sTmp);//小数位数31

//    nTmp=ui->Y_Position->currentIndex(); //位置
//    sTmp=QString::number(nTmp);
//    datalist->replace(index+12,sTmp);//32

    //存X轴,从index+30开始存
    nTmp=ui->X_Show_Ticks->isChecked();
    sTmp=QString::number(nTmp);
    datalist->replace(index+30,sTmp);//显示刻度50

    nTmp=ui->X_Show_Y_Axis->isChecked();
    sTmp=QString::number(nTmp);
    datalist->replace(index+31,sTmp);//显示Y轴曲线51

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->X_Axis_Color->palette().background().color());//边框色
    datalist->replace(index+32,sTmp);

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->X_Grid_Color->palette().background().color());//前景色
    datalist->replace(index+33,sTmp);

    nTmp=ui->X_Major->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+34,sTmp);//主分刻度54

    nTmp=ui->X_Sub->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+35,sTmp);//次分刻度55

    nTmp=ui->X_DisplayTime->isChecked();
    sTmp=QString::number(nTmp);
    datalist->replace(index+36,sTmp);//显示时间56

    sTmp = ui->X_Font->currentText();
    datalist->replace(index+37,sTmp);//字体大小57

    nTmp = ui->X_Time->currentIndex();
    sTmp=QString::number(nTmp);
    datalist->replace(index+38,sTmp);//时间格式58

    nTmp=ui->X_Hour->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+39,sTmp);//时59

    nTmp=ui->X_Minute->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+40,sTmp);//分60

    nTmp=ui->X_Second->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+41,sTmp);//秒61

    sTmp=ui->dateEdit->date().toString();
    datalist->replace(index+42,sTmp);//日期

    nTmp=ui->bMultyAxes->isChecked();//是否多坐标轴
    sTmp=QString::number(nTmp);
    datalist->replace(index+43,sTmp);//秒61
}
int QHisTrendDisplayXYDlg::CheckMinMax(int DataType)
{
    int nmax=ui->Y_Max->text().toInt();
    int nmin= ui->Y_Min->text().toInt();
    QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr("Y轴最小值大于最大值！"),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("确定"),QMessageBox::AcceptRole);
    if(nmin>nmax)
    {
         msg.exec();
         ui->Y_Min->setFocus();
         ui->Y_Min->selectAll();
        return 0;
    }
       return 1;
}
void QHisTrendDisplayXYDlg::Init(QGraphicsItem *pItem)
{
    QStringList datalist;
    if(pItem)
    {

            datalist = qVariantValue<QStringList>(pItem->data(GROUP_DATALIST_KEY));
            //存Y轴
            QString sTmp="";

            int nTmp=datalist.at(20).toInt();
            ui->Y_Show_Ticks->setChecked(nTmp);//显示刻度20


            nTmp=datalist.at(21).toInt();
            ui->Y_Show_X_Axis->setChecked(nTmp);//显示X轴曲线21

            ui->Y_Axis_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(22)).name()));
            ui->Y_Grid_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(23)).name()));

            nTmp=datalist.at(24).toInt();//主分刻度24
            ui->Y_Major->setValue(nTmp);

            nTmp=datalist.at(25).toInt();//次分刻度25
            ui->Y_Sub->setValue(nTmp);

            nTmp=datalist.at(26).toInt();
            ui->Y_DisplayMarks->setChecked(nTmp);//显示刻度标示26

            sTmp=datalist.at(27);//字体大小27
            nTmp=ui->Y_FontSize->findText(sTmp);
            ui->Y_FontSize->setCurrentIndex(nTmp);


            sTmp=datalist.at(28);//最小值28
            ui->Y_Min->setText(sTmp);

            sTmp=datalist.at(29);//最大值29
            ui->Y_Max->setText(sTmp);

            nTmp=datalist.at(30).toInt();//总位数30
            ui->Y_TotalDigits->setValue(nTmp);

            nTmp=datalist.at(31).toInt();//小数位数31
            ui->Y_Fractional->setValue(nTmp);

         //   ui->Y_Position->setCurrentIndex(datalist.at(32).toInt());//位置32


            //存X轴,从index+30开始存
            nTmp=datalist.at(50).toInt();//显示刻度50
            ui->X_Show_Ticks->setChecked(nTmp);

            nTmp=datalist.at(51).toInt();//显示Y轴曲线51
            ui->X_Show_Y_Axis->setChecked(nTmp);

            ui->X_Axis_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(52)).name()));
            ui->X_Grid_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(53)).name()));


            nTmp=datalist.at(54).toInt();//主分刻度54
            ui->X_Major->setValue(nTmp);

            nTmp=datalist.at(55).toInt();//次分刻度55
            ui->X_Sub->setValue(nTmp);

            nTmp=datalist.at(56).toInt();//显示时间56
            ui->X_DisplayTime->setChecked(nTmp);

            sTmp=datalist.at(57);//字体大小57
            nTmp=ui->X_Font->findText(sTmp);
            ui->X_Font->setCurrentIndex(nTmp);

            ui->X_Time->setCurrentIndex(datalist.at(58).toInt());//时间格式58

            ui->X_Hour->setValue(datalist.at(59).toInt());//时59

            ui->X_Minute->setValue(datalist.at(60).toInt());//分60

            ui->X_Second->setValue(datalist.at(61).toInt());//秒61
            QString sTemp=datalist.at(62);
            QDate date=QDate::fromString(sTemp);
            ui->dateEdit->setDate(date);

            ui->bMultyAxes->setChecked(datalist.at(63).toInt());
            on_X_DisplayTime_clicked(ui->X_DisplayTime->isChecked());
            on_X_Show_Y_Axis_clicked(ui->X_Show_Y_Axis->isChecked());
            on_X_Show_Ticks_clicked(ui->X_Show_Ticks->isChecked());
            on_Y_Show_Ticks_clicked(ui->Y_Show_Ticks->isChecked());
            on_Y_Show_X_Axis_clicked(ui->Y_Show_X_Axis->isChecked());
            on_Y_DisplayMarks_clicked(ui->Y_DisplayMarks->isChecked());
            if((!ui->Y_Show_Ticks->isChecked())&&(!ui->Y_Show_X_Axis->isChecked()))//若两个都没选中
            {
                ui->groupBox_4->setHidden(true);
            }
    }
    else
    {
        ui->X_Axis_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
        ui->X_Grid_Color->setStyleSheet( QString("background:%1").arg(QColor(0,128,0).name()));
        ui->Y_Axis_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
        ui->Y_Grid_Color->setStyleSheet( QString("background:%1").arg(QColor(0,128,0).name()));

    }

}


void QHisTrendDisplayXYDlg::on_X_Axis_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->X_Axis_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setXAxisColor(const QColor &)));
}
void QHisTrendDisplayXYDlg::setXAxisColor(const QColor & mColor)       //文本色
{
    ui->X_Axis_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QHisTrendDisplayXYDlg::on_X_Grid_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->X_Grid_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setXGridColor(const QColor &)));

}
void QHisTrendDisplayXYDlg::setXGridColor(const QColor & mColor)       //文本色
{
    ui->X_Grid_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QHisTrendDisplayXYDlg::on_Y_Axis_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->Y_Axis_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setYAxisColor(const QColor &)));

}
void QHisTrendDisplayXYDlg::setYAxisColor(const QColor & mColor)       //文本色
{
    ui->Y_Axis_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QHisTrendDisplayXYDlg::on_Y_Grid_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->Y_Grid_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setYGridColor(const QColor &)));

}
void QHisTrendDisplayXYDlg::setYGridColor(const QColor & mColor)       //文本色
{
    ui->Y_Grid_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
