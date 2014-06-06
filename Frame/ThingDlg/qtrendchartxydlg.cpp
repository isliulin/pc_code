#include "qtrendchartxydlg.h"

#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
QTrendChartXYDlg::QTrendChartXYDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QTrendChartXYDlg)
{
    ui->setupUi(this);
    pwnd->InitFontSize(ui->X_Font_Size);//初始化字体大小
    pwnd->InitFontSize(ui->Y_Font_Size);//初始化字体大小
    vIntval = new QIntValidator;
    ui->m_y_max->setValidator(vIntval);
    ui->m_y_min->setValidator(vIntval);
}

QTrendChartXYDlg::~QTrendChartXYDlg()
{
    if(vIntval)
    {
        delete vIntval;
        vIntval=NULL;
    }
    delete ui;
}//

void QTrendChartXYDlg::Init(QGraphicsItem *pItem)
{
    QStringList datalist;
    if(pItem)
    {

            datalist = qVariantValue<QStringList>(pItem->data(GROUP_DATALIST_KEY));
            //存Y轴
            QString sTmp="";

            int nTmp=datalist.at(20).toInt();
            ui->Y_Show_Ticks->setChecked(nTmp);//显示刻度20
            on_Y_Show_Ticks_clicked(ui->Y_Show_Ticks->isChecked());
            nTmp=datalist.at(21).toInt();
            ui->Y_Show_X_Axis->setChecked(nTmp);//显示X轴曲线21
            on_Y_Show_X_Axis_clicked(ui->Y_Show_X_Axis->isChecked());
            ui->Y_Axis_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(22)).name()));
            ui->Y_Grid_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(23)).name()));


            nTmp=datalist.at(24).toInt();//主分刻度24
            ui->Y_Major->setValue(nTmp);

            nTmp=datalist.at(25).toInt();//次分刻度25
            ui->Y_Sub->setValue(nTmp);

            nTmp=datalist.at(26).toInt();
            ui->Y_If_Show_Marks->setChecked(nTmp);//显示刻度标示26
            on_Y_If_Show_Marks_clicked(ui->Y_If_Show_Marks->isChecked());
            sTmp=datalist.at(27);//字体大小27
            nTmp=ui->Y_Font_Size->findText(sTmp);
            ui->Y_Font_Size->setCurrentIndex(nTmp);


            sTmp=datalist.at(28);//最小值28
            ui->m_y_min->setText(sTmp);

            sTmp=datalist.at(29);//最大值29
            ui->m_y_max->setText(sTmp);

            nTmp=datalist.at(30).toInt();//总位数30
            ui->m_y_totalnum->setValue(nTmp);

            nTmp=datalist.at(31).toInt();//小数位数31
            ui->m_y_pointnum->setValue(nTmp);


            //存X轴,从index+30开始存
            nTmp=datalist.at(50).toInt();//显示刻度50
            ui->X_Show_Ticks->setChecked(nTmp);
            on_X_Show_Ticks_clicked(ui->X_Show_Ticks->isChecked());
            nTmp=datalist.at(51).toInt();//显示Y轴曲线51
            ui->X_Show_Y_Axis->setChecked(nTmp);
            on_X_Show_Y_Axis_clicked(ui->X_Show_Y_Axis->isChecked());
            ui->X_Axis_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(52)).name()));
            ui->X_Grid_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(datalist.at(53)).name()));

            nTmp=datalist.at(54).toInt();//主分刻度54
            ui->X_Major->setValue(nTmp);

            nTmp=datalist.at(55).toInt();//次分刻度55
            ui->X_Sub->setValue(nTmp);

            nTmp=datalist.at(56).toInt();//显示刻度标示56
            ui->X_If_Show_Marks->setChecked(nTmp);

            sTmp=datalist.at(57);//字体大小57
            nTmp=ui->X_Font_Size->findText(sTmp);
            ui->X_Font_Size->setCurrentIndex(nTmp);

            on_X_If_Show_Marks_clicked(ui->X_If_Show_Marks->isChecked());
            if((!ui->Y_Show_Ticks->isChecked())&&(!ui->Y_Show_X_Axis->isChecked()))//若两个都没选中
            {
                ui->groupBox_3->setHidden(true);
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


void QTrendChartXYDlg::on_X_Show_Ticks_clicked(bool checked)
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
        ui->X_If_Show_Marks->setHidden(false);
        on_X_If_Show_Marks_clicked(ui->X_If_Show_Marks->isChecked());
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
            ui->X_If_Show_Marks->setHidden(true);
            ui->label_5->setHidden(true);
            ui->X_Font_Size->setHidden(true);
        }
        ui->label->setHidden(true);
        ui->X_Axis_Color->setHidden(true);
    }
}

void QTrendChartXYDlg::on_X_Show_Y_Axis_clicked(bool checked)
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
        ui->X_If_Show_Marks->setHidden(false);
        on_X_If_Show_Marks_clicked(ui->X_If_Show_Marks->isChecked());
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
            ui->X_If_Show_Marks->setHidden(true);
            ui->label_5->setHidden(true);
            ui->X_Font_Size->setHidden(true);
         }
        ui->label_2->setHidden(true);
        ui->X_Grid_Color->setHidden(true);
     }
}

void QTrendChartXYDlg::on_X_If_Show_Marks_clicked(bool checked)
{

    if(checked)
    {
        ui->label_5->setHidden(false);
        ui->X_Font_Size->setHidden(false);
    }
    else
    {
        ui->label_5->setHidden(true);
        ui->X_Font_Size->setHidden(true);
    }
}

void QTrendChartXYDlg::on_Y_Show_Ticks_clicked(bool checked)
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
        ui->Y_If_Show_Marks->setHidden(false);
        on_Y_If_Show_Marks_clicked(ui->Y_If_Show_Marks->isChecked());
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
            ui->Y_If_Show_Marks->setHidden(true);
            on_Y_If_Show_Marks_clicked(false);
        }
        ui->label_6->setHidden(true);
        ui->Y_Axis_Color->setHidden(true);
    }
}

void QTrendChartXYDlg::on_Y_Show_X_Axis_clicked(bool checked)
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
        ui->Y_If_Show_Marks->setHidden(false);
        on_Y_If_Show_Marks_clicked(ui->Y_If_Show_Marks->isChecked());

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
            ui->Y_If_Show_Marks->setHidden(true);
            on_Y_If_Show_Marks_clicked(false);

          }
        ui->label_7->setHidden(true);
        ui->Y_Grid_Color->setHidden(true);
     }
}

void QTrendChartXYDlg::on_Y_If_Show_Marks_clicked(bool checked)
{
    if(checked)
    {
        ui->groupBox_3->setHidden(false);
    }
    else
    {
        ui->groupBox_3->setHidden(true);
    }
}


void QTrendChartXYDlg::SaveXYPage(QStringList *datalist, int index)
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

    nTmp=ui->Y_If_Show_Marks->isChecked();
    sTmp=QString::number(nTmp);
    datalist->replace(index+6,sTmp);//显示刻度标示26

    sTmp = ui->Y_Font_Size->currentText();
    datalist->replace(index+7,sTmp);//字体大小27

    sTmp = ui->m_y_min->text();
    datalist->replace(index+8,sTmp);//最小值28

    sTmp = ui->m_y_max->text();
    datalist->replace(index+9,sTmp);//最大值29

    nTmp=ui->m_y_totalnum->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+10,sTmp);//总位数30

    nTmp=ui->m_y_pointnum->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+11,sTmp);//小数位数31

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

    nTmp=ui->X_If_Show_Marks->isChecked();
    sTmp=QString::number(nTmp);
    datalist->replace(index+36,sTmp);//显示刻度标示56

    sTmp = ui->X_Font_Size->currentText();
    datalist->replace(index+37,sTmp);//字体大小57
}
int  QTrendChartXYDlg::TrendCheckMinMax(int DataType)
{
    int tempFlg=pwnd->CheckMinMax(ui->m_y_min->text(),ui->m_y_max->text(),DataType,0);
    if(tempFlg)
    {
        if(tempFlg==1||tempFlg==2||tempFlg==4)
        {
            ui->m_y_max->setFocus();
            ui->m_y_max->selectAll();

        }
        else if(tempFlg==3||tempFlg==5)
        {
            ui->m_y_max->setFocus();
            ui->m_y_max->selectAll();
        }
        return 0;
    }
    return 1;
}

void QTrendChartXYDlg::on_X_Axis_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->X_Axis_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setXAxisColor(const QColor &)));
}
void QTrendChartXYDlg::setXAxisColor(const QColor & mColor)       //文本色
{
    ui->X_Axis_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QTrendChartXYDlg::on_X_Grid_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->X_Grid_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setXGridColor(const QColor &)));

}
void QTrendChartXYDlg::setXGridColor(const QColor & mColor)       //文本色
{
    ui->X_Grid_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QTrendChartXYDlg::on_Y_Axis_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->Y_Axis_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setYAxisColor(const QColor &)));

}
void QTrendChartXYDlg::setYAxisColor(const QColor & mColor)       //文本色
{
    ui->Y_Axis_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QTrendChartXYDlg::on_Y_Grid_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->Y_Grid_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setYGridColor(const QColor &)));

}
void QTrendChartXYDlg::setYGridColor(const QColor & mColor)       //文本色
{
    ui->Y_Grid_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
/************************************************************************
  *Functions:检查最大最小值是否有误
  ************************************************************************
  *Value：
  *无
  ************************************************************************
  *returns:
  *0 --------最大最小值有误
  *1 --------正确无误
  ************************************************************************
  *Edit time：2011.12.16
  *Edit by    ：Dylan
  *************************************************************************/
int QTrendChartXYDlg::checkMaxMin()
{
    int nmax=ui->m_y_max->text().toInt();
    int nmin= ui->m_y_min->text().toInt();
    QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr("Y轴最小值大于最大值！"),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("确定"),QMessageBox::AcceptRole);
    if(nmin>nmax)
    {
         msg.exec();
         ui->m_y_min->setFocus();
         ui->m_y_min->selectAll();
        return 0;
    }
       return 1;
}
