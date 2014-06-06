#include "qtrendatime.h"

#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

QTrendaTime::QTrendaTime(QWidget *parent):QWidget(parent),ui(new Ui::QTrendaTime)
{
    ui->setupUi(this);

    //上一个焦点是哪个，0代表存盘数据开头,1代表当前时刻存盘数据.....
    //m_nOldFocus = 0;//初始化就用这个值，在Init中有用

    //X轴时间单位
    //ui->comboBox_timeUnit->addItem(tr("秒"));
    //ui->comboBox_timeUnit->addItem(tr("分"));
    //ui->comboBox_timeUnit->addItem(tr("时"));
    //ui->comboBox_timeUnit->addItem(tr("日"));
    //ui->comboBox_timeUnit->addItem(tr("月"));
    //ui->comboBox_timeUnit->addItem(tr("年"));
    ui->checkBox_timeFormat->setChecked(true);
    ui->checkBox_dateFormat->setChecked(true);
    //ui->label_3->setVisible(false);
    //ui->label_9->setVisible(false);

    //时间格式
    ui->comboBox_timeFormat->addItem(tr("HH:MM"));
    ui->comboBox_timeFormat->addItem(tr("HH:MM:SS"));
    ui->comboBox_timeFormat->addItem(tr("HH-MM"));
    ui->comboBox_timeFormat->addItem(tr("HH-MM-SS"));

    //字体类型
    /*ui->comboBox_fontType->addItem(tr("宋体"));
    ui->comboBox_fontType->addItem(tr("矢量字体"));
    ui->label_5->setEnabled(false);
    ui->comboBox_fontType->setEnabled(false);*/

    //最近时间单位
    ui->comboBox_near->addItem(tr("分"));
    ui->comboBox_near->addItem(tr("时"));
    ui->comboBox_near->addItem(tr("日"));
    ui->comboBox_near->addItem(tr("月"));

    //日期格式
    ui->comboBox_dateFormat->addItem(tr("YYYY/MM/DD"));
    ui->comboBox_dateFormat->addItem(tr("YYYY.MM.DD"));
    ui->comboBox_dateFormat->addItem(tr("YYYY-MM-DD"));
    ui->comboBox_dateFormat->addItem(tr("MM/DD/YYYY"));
    ui->comboBox_dateFormat->addItem(tr("MM.DD.YYYY"));
    ui->comboBox_dateFormat->addItem(tr("MM-DD-YYYY"));
    ui->comboBox_dateFormat->addItem(tr("DD/MM/YYYY"));
    ui->comboBox_dateFormat->addItem(tr("DD.MM.YYYY"));
    ui->comboBox_dateFormat->addItem(tr("DD-MM-YYYY"));

    //灰显没选中的属性
    if(ui->radioButton_diskBegin->isChecked())//假如选中从存盘数据开始
    {
        ui->spin_near->setEnabled(false);
        ui->comboBox_near->setEnabled(false);
        ui->dateEdit->setEnabled(false);
        ui->timeEdit->setEnabled(false);
        ui->dateEdit_2->setEnabled(false);
        ui->timeEdit_2->setEnabled(false);
        ui->lineEdit_from->setEnabled(false);
        ui->lineEdit_to->setEnabled(false);
        ui->pushButton_from->setEnabled(false);
        ui->pushButton_to->setEnabled(false);
    }

    if(ui->radioButton_near->isChecked())//假如选中最近
    {
        ui->spin_near->setEnabled(true);
        ui->comboBox_near->setEnabled(true);
        ui->dateEdit->setEnabled(false);
        ui->timeEdit->setEnabled(false);
        ui->dateEdit_2->setEnabled(false);
        ui->timeEdit_2->setEnabled(false);
        ui->lineEdit_from->setEnabled(false);
        ui->lineEdit_to->setEnabled(false);
        ui->pushButton_from->setEnabled(false);
        ui->pushButton_to->setEnabled(false);
    }

    if(ui->radioButton->isChecked())//假如选中从。。。到。。。
    {
        ui->spin_near->setEnabled(false);
        ui->comboBox_near->setEnabled(false);
        ui->dateEdit->setEnabled(true);
        ui->timeEdit->setEnabled(true);
        ui->dateEdit_2->setEnabled(true);
        ui->timeEdit_2->setEnabled(true);
        ui->lineEdit_from->setEnabled(false);
        ui->lineEdit_to->setEnabled(false);
        ui->pushButton_from->setEnabled(false);
        ui->pushButton_to->setEnabled(false);
    }

    if(ui->radioButton_from->isChecked())//假如选中地址
    {
        ui->spin_near->setEnabled(false);
        ui->comboBox_near->setEnabled(false);
        ui->dateEdit->setEnabled(false);
        ui->timeEdit->setEnabled(false);
        ui->dateEdit_2->setEnabled(false);
        ui->timeEdit_2->setEnabled(false);
        ui->lineEdit_from->setEnabled(true);
        ui->lineEdit_to->setEnabled(true);
        ui->pushButton_from->setEnabled(true);
        ui->pushButton_to->setEnabled(true);
    }
}

QTrendaTime::~QTrendaTime()
{
    delete ui;
}    

/*void QTrendaTime::on_comboBox_timeUnit_currentIndexChanged(int index)//X轴时间单位
{
    m_eTimeUnit = (TimeUnitType)index;
}*/

void QTrendaTime::on_comboBox_timeFormat_currentIndexChanged(int index)//时间格式
{
    m_eTimeFormat = (TimeType)(index + 1);
}

void QTrendaTime::on_comboBox_fontType_currentIndexChanged(int index)//字体类型
{
    m_eFontType = (FontType)(index + 1);
}

void QTrendaTime::on_comboBox_fontTxtAttr_currentIndexChanged(int index)//文本属性
{
    m_eTxtAttr = (TxtAttrType)(index + 1);
}

void QTrendaTime::on_spinBox_fontSize_valueChanged(int value)//字体大小
{
    m_nFontSize = value;
}

void QTrendaTime::on_comboBox_near_currentIndexChanged(int index)//最近时间单位
{
    m_eTimeUnitNear = (TimeUnitType)(index + 1);
}

void QTrendaTime::on_comboBox_dateFormat_currentIndexChanged(int index)//日期格式
{
    m_eDateFormat = (DateType)(index + 1);
}

void QTrendaTime::on_dateEdit_editingFinished()//从 日期
{
    m_dFromDate = ui->dateEdit->date();
}

void QTrendaTime::on_timeEdit_editingFinished()//从 时间
{
    m_tFromTime = ui->timeEdit->time();
}

void QTrendaTime::on_dateEdit_2_editingFinished()//到 日期
{
    m_dToDate = ui->dateEdit_2->date();
}

void QTrendaTime::on_timeEdit_2_editingFinished()//到 时间
{
    m_tToTime = ui->timeEdit_2->time();
}

void QTrendaTime::on_radioButton_diskBegin_clicked()//从存盘数据开头
{
    cleanOldFocus();
    m_nOldFocus = 2;
    m_eStart    = START_DISKBEGIN;  //存盘数据开头
    //m_eCurTime  = UNIT_MINUTE;      //当前用的时间单位
    ui->label_tips->setText(tr("曲线每隔一分钟刷新一次"));
}

void QTrendaTime::on_radioButton_near_clicked()//最近
{
    cleanOldFocus();
    m_nOldFocus = 0;
    ui->spin_near->setEnabled(true);
    ui->comboBox_near->setEnabled(true);
    m_eStart    = START_NEAR;         //最近
    m_eTimeUnitNear  = (TimeUnitType)(ui->comboBox_near->currentIndex() + 1); //当前用的时间单位
    ui->label_tips->setText(tr("曲线实时刷新"));
}

void QTrendaTime::on_radioButton_clicked()//从。。。。到。。。。
{
    cleanOldFocus();
    m_nOldFocus = 1;
    ui->dateEdit->setEnabled(true);
    ui->timeEdit->setEnabled(true);
    ui->dateEdit_2->setEnabled(true);
    ui->timeEdit_2->setEnabled(true);
    m_eStart    = START_FROMTO;         //从。。。。到。。。
    ui->label_tips->setText(tr("曲线每隔一分钟刷新一次"));
}

void QTrendaTime::on_radioButton_from_clicked()//地址
{
    cleanOldFocus();
    m_nOldFocus = 3;
    m_eStart    = START_ADDR;
    ui->lineEdit_from->setEnabled(true);
    ui->lineEdit_to->setEnabled(true);
    ui->pushButton_from->setEnabled(true);
    ui->pushButton_to->setEnabled(true);
    //ui->label_tips->setText(tr("曲线每隔一分钟刷新一次"));
}

void QTrendaTime::on_pushButton_color_clicked()//标注颜色
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_color ,colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_showColor(const QColor &)));
}

void QTrendaTime::set_pushButton_showColor(const QColor & color)
{
    m_nMarkedColor = color;
    ui->pushButton_color->setStyleSheet(QString("background:%1").arg(color.name()));
}

void QTrendaTime::on_checkBox_hideMarked_clicked(bool checked)//显示X轴标注
{
    if(checked)
    {
        m_bXMarked = true;
    }
    else
    {
        m_bXMarked = false;
    }
}

bool QTrendaTime::strIsNumber(QString & str)
{
    bool bRight = true;
    int  k      = str.length();

    for(int i = 0; i < k; i++)
    {
        if(str[i] < '0' || str[i] > '9')//此时输入的不是数字
        {
            bRight = false;
            break;
        }
    }

    return bRight;
}

int QTrendaTime::getTime_near()
{
    return ui->spin_near->value();
}

void QTrendaTime::Init(QTrendAttr *pItem)//构造函数之后运行的函数
{
    if(pItem)//赋值给界面
    {
        //m_eTimeUnit     = pItem->m_eTimeUnit;    //X轴时间单位
        m_eTimeFormat   = pItem->m_eTimeFormat;  //时间格式
        m_eDateFormat   = pItem->m_eDateFormat;  //日期格式
        m_eFontType     = pItem->m_eFontType;    //字体类型
        m_eTxtAttr      = pItem->m_eTxtAttr;     //文本属性
        m_eStart        = pItem->m_eStart;       //曲线起始点
        m_bXMarked      = pItem->m_bXMarked;     //是否X轴标注
        m_nFontSize     = pItem->m_nFontSize;    //字体大小
        m_nMarkedColor  = pItem->m_nMarkedColor; //标注颜色
        m_nTimeLen      = pItem->m_nTimeLen;     //从开始需要多少时间
        m_eTimeUnitNear = pItem->m_eTimeUnitNear;//最近时间单位
        m_dFromDate     = pItem->m_dFromDate;    //起始日期
        m_tFromTime     = pItem->m_tFromTime;    //起始时间
        m_dToDate       = pItem->m_dToDate;      //终止日期
        m_tToTime       = pItem->m_tToTime;      //终止时间
        m_kbFrom        = pItem->m_kbFrom;
        m_kbTo          = pItem->m_kbTo;
        m_bDateFormat   = pItem->m_bDateFormat;
        m_bTimeFormat   = pItem->m_bTimeFormat;

        if(pItem->m_eTableType == TypeRealTime)//实时曲线
        {
            m_bDateFormat = false;
            m_bTimeFormat = true;

            if(m_eTimeUnitNear != UNIT_MINUTE)
            {
                m_eTimeUnitNear = UNIT_MINUTE;
            }
        }
        ui->checkBox_dateFormat->setChecked(m_bDateFormat);
        ui->checkBox_timeFormat->setChecked(m_bTimeFormat);
        ui->comboBox_dateFormat->setEnabled(m_bDateFormat);
        ui->comboBox_timeFormat->setEnabled(m_bTimeFormat);

        ui->comboBox_timeFormat->setCurrentIndex((int)m_eTimeFormat - 1);   //时间格式
        ui->comboBox_dateFormat->setCurrentIndex((int)m_eDateFormat - 1);   //日期格式
        //ui->comboBox_fontType->setCurrentIndex((int)m_eFontType - 1);       //字体类型
        ui->comboBox_near->setCurrentIndex((int)m_eTimeUnitNear - 1);
        ui->spinBox_fontSize->setValue(m_nFontSize);                    //字体大小
        //ui->pushButton_rulerColor->setStyleSheet(QString("background:%1").arg(Color.name()));
        ui->pushButton_color->setStyleSheet(QString("background:%1").arg(m_nMarkedColor.name()));//标注颜色
        ui->checkBox_hideMarked->setChecked(m_bXMarked);                //是否X轴标注

        //ui->comboBox_timeUnit->setCurrentIndex((int)m_eTimeUnit);//X轴时间单位
        m_nOldFocus = (int)m_eStart - 1;//当前选中的是哪种曲线起始点
        ui->radioButton_diskBegin->setChecked(false);
        ui->radioButton_near->setChecked(false);
        ui->radioButton->setChecked(false);
        ui->radioButton_from->setChecked(false);
        ui->spin_near->setEnabled(false);
        ui->comboBox_near->setEnabled(false);
        ui->dateEdit->setEnabled(false);
        ui->timeEdit->setEnabled(false);
        ui->dateEdit_2->setEnabled(false);
        ui->timeEdit_2->setEnabled(false);
        ui->lineEdit_from->setEnabled(false);
        ui->lineEdit_to->setEnabled(false);
        ui->pushButton_from->setEnabled(false);
        ui->pushButton_to->setEnabled(false);
        switch(m_nOldFocus)
        {
            case 2:
            {
                ui->radioButton_diskBegin->setChecked(true);
                ui->label_tips->setText(tr("曲线每隔一分钟刷新一次"));
            }
            break;

            case 0:
            {
                ui->radioButton_near->setChecked(true);
                ui->spin_near->setEnabled(true);
                ui->comboBox_near->setEnabled(true);
                ui->spin_near->setValue(m_nTimeLen);
                ui->comboBox_near->setCurrentIndex((int)m_eTimeUnitNear - 1);
            }
            break;

            case 1:
            {
                ui->radioButton->setChecked(true);
                ui->dateEdit->setEnabled(true);
                ui->timeEdit->setEnabled(true);
                ui->dateEdit_2->setEnabled(true);
                ui->timeEdit_2->setEnabled(true);
                ui->dateEdit->setDate(m_dFromDate);
                ui->timeEdit->setTime(m_tFromTime);
                ui->dateEdit_2->setDate(m_dToDate);
                ui->timeEdit_2->setTime(m_tToTime);
                ui->label_tips->setText(tr("曲线每隔一分钟刷新一次"));
            }
            break;

            case 3:
            {
                ui->radioButton_from->setChecked(true);
                ui->lineEdit_from->setEnabled(true);
                ui->lineEdit_to->setEnabled(true);
                ui->pushButton_from->setEnabled(true);
                ui->pushButton_to->setEnabled(true);
                ui->lineEdit_from->setText(m_kbFrom.sShowAddr);
                ui->lineEdit_to->setText(m_kbTo.sShowAddr);
            }
            break;

            default:
            break;
        }
    }
    else//初始化界面
    {
        //m_eTimeUnit     = UNIT_MINUTE;          //X轴时间单位,默认第一个
        m_eTimeFormat   = TIME_HM1;             //时间格式,默认第一个
        m_eDateFormat   = YMD_ONE;              //日期格式,默认第一个
        m_eFontType     = FONT_SONGTI;          //字体类型,默认第一个
        m_eTxtAttr      = TXT_CUTI;             //文本属性,默认第一个
        m_eStart        = START_NEAR;      //曲线起始点,默认第一个
        m_bXMarked      = true;                //是否X轴标注
        m_nFontSize     = 10;                    //字体大小
        m_nTimeLen      = 5;                    //从开始需要多少时间，默认为0，因为选的是存盘数据开头
        m_eTimeUnitNear = UNIT_MINUTE;          //最近时间单位
        m_nMarkedColor  = QColor(0,0,0);  //标注颜色
        m_dFromDate     = QDate(2012, 1, 12);
        m_tFromTime     = QTime(12, 0);
        m_dToDate       = QDate(2012, 1, 12);;
        m_tToTime       = QTime(12, 1);
        //m_kbFrom        = pItem->m_kbFrom;
        //m_kbTo          = pItem->m_kbTo;
        m_bDateFormat   = true;
        m_bTimeFormat   = true;

        ui->comboBox_dateFormat->setEnabled(true);
        ui->comboBox_timeFormat->setEnabled(true);
        ui->comboBox_timeFormat->setCurrentIndex((int)m_eTimeFormat - 1);//时间格式
        ui->comboBox_dateFormat->setCurrentIndex((int)m_eDateFormat - 1);   //日期格式
        //ui->comboBox_fontType->setCurrentIndex((int)m_eFontType - 1);//字体类型
        ui->spinBox_fontSize->setValue(m_nFontSize);//字体大小
        //ui->pushButton_rulerColor->setStyleSheet(QString("background:%1").arg(Color.name()));
        ui->pushButton_color->setStyleSheet(QString("background:%1").arg(m_nMarkedColor.name()));//标注颜色
        ui->checkBox_hideMarked->setChecked(m_bXMarked);

        //ui->comboBox_timeUnit->setCurrentIndex((int)m_eTimeUnit);//X轴时间单位
        m_nOldFocus = 0;//当前选中的是哪种曲线起始点
        ui->radioButton_diskBegin->setChecked(false);
        ui->radioButton_near->setChecked(true);
        ui->radioButton->setChecked(false);
        ui->radioButton_from->setChecked(false);
        ui->spin_near->setEnabled(true);
        ui->comboBox_near->setEnabled(true);
        ui->dateEdit->setEnabled(false);
        ui->timeEdit->setEnabled(false);
        ui->dateEdit_2->setEnabled(false);
        ui->timeEdit_2->setEnabled(false);
        ui->lineEdit_from->setEnabled(false);
        ui->lineEdit_to->setEnabled(false);
        ui->pushButton_from->setEnabled(false);
        ui->pushButton_to->setEnabled(false);

        ui->spin_near->setValue(m_nTimeLen);
    }
}

void QTrendaTime::cleanOldFocus()
{
    switch(this->m_nOldFocus)
    {
        case 0:
        {
            ui->spin_near->setEnabled(false);
            ui->comboBox_near->setEnabled(false);
        }
        break;

        case 1:
        {
            ui->dateEdit->setEnabled(false);
            ui->timeEdit->setEnabled(false);
            ui->dateEdit_2->setEnabled(false);
            ui->timeEdit_2->setEnabled(false);

        }
        break;

        case 2:
        {

        }
        break;

        case 3:
        {
            ui->lineEdit_from->setEnabled(false);
            ui->lineEdit_to->setEnabled(false);
            ui->pushButton_from->setEnabled(false);
            ui->pushButton_to->setEnabled(false);
        }
        break;
    }
}

void QTrendaTime::setTrendType(bool bIsHistoryTrend)
{
    //ui->groupBox_beginPoint->setEnabled(bIsHistoryTrend);
    //ui->groupBox_XaxisSet->setEnabled(bIsHistoryTrend);

    ui->radioButton->setEnabled(bIsHistoryTrend);
    ui->dateEdit->setEnabled(bIsHistoryTrend);
    ui->timeEdit->setEnabled(bIsHistoryTrend);
    ui->dateEdit_2->setEnabled(bIsHistoryTrend);
    ui->timeEdit_2->setEnabled(bIsHistoryTrend);
    ui->radioButton_diskBegin->setEnabled(bIsHistoryTrend);
    ui->label_2->setEnabled(bIsHistoryTrend);
    ui->lineEdit_from->setEnabled(bIsHistoryTrend);
    ui->lineEdit_to->setEnabled(bIsHistoryTrend);
    ui->pushButton_from->setEnabled(bIsHistoryTrend);
    ui->pushButton_to->setEnabled(bIsHistoryTrend);
    ui->radioButton_from->setEnabled(bIsHistoryTrend);
    ui->label_7->setEnabled(bIsHistoryTrend);

    if (!bIsHistoryTrend)
    {
            ui->radioButton_near->setChecked(true);
            ui->comboBox_near->clear();
            ui->comboBox_near->addItem(tr("分"));
            on_radioButton_near_clicked();
            ui->comboBox_dateFormat->setEnabled(false);
            //ui->label_9->setVisible(false);
            ui->checkBox_dateFormat->setEnabled(false);
            m_bDateFormat = false;
            m_bTimeFormat = true;
            ui->checkBox_timeFormat->setChecked(true);
            ui->comboBox_timeFormat->setEnabled(true);
    }
    else{
            ui->comboBox_near->clear();
            ui->comboBox_near->addItem(tr("分"));
            ui->comboBox_near->addItem(tr("时"));
            ui->comboBox_near->addItem(tr("日"));
            ui->comboBox_near->addItem(tr("月"));
            ui->comboBox_dateFormat->setEnabled(true);
            //ui->label_9->setVisible(true);
            ui->checkBox_dateFormat->setEnabled(true);
            m_bDateFormat = true;
            ui->checkBox_dateFormat->setEnabled(true);
    }
}

void QTrendaTime::on_pushButton_from_clicked()
{
    Keyboard key;
    QString str = ui->lineEdit_from->text();
    AddressInputDialog dlg_readaddress(key, str, 1, this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_from->setText(key.sShowAddr);
    }
    m_kbFrom = key;
}

void QTrendaTime::on_pushButton_to_clicked()
{
    Keyboard key;
    QString str = ui->lineEdit_to->text();
    AddressInputDialog dlg_readaddress(key, str, 1, this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_to->setText(key.sShowAddr);
    }
    m_kbFrom = key;
}

void QTrendaTime::on_checkBox_timeFormat_clicked(bool checked)
{
    if(this->m_bDateFormat)
    {
        ui->checkBox_timeFormat->setChecked(checked);
        this->m_bTimeFormat = checked;
        ui->comboBox_timeFormat->setEnabled(checked);
    }
    else
    {
        ui->checkBox_timeFormat->setChecked(true);
        this->m_bTimeFormat = true;
        ui->comboBox_timeFormat->setEnabled(true);
    }
}

void QTrendaTime::on_checkBox_dateFormat_clicked(bool checked)
{
    if(this->m_bTimeFormat)
    {
        ui->checkBox_dateFormat->setChecked(checked);
        this->m_bDateFormat = checked;
        ui->comboBox_dateFormat->setEnabled(checked);
    }
    else
    {
        ui->checkBox_dateFormat->setChecked(true);
        this->m_bDateFormat = true;
        ui->comboBox_dateFormat->setEnabled(true);
    }
}
