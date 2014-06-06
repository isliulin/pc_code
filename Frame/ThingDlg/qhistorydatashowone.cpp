#include "qhistorydatashowone.h"
//#include "ui_qhistorydatashowone.h"

#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

QHistoryDataShowOne::QHistoryDataShowOne(QWidget *parent):QWidget(parent),ui(new Ui::QHistoryDataShowOne)
{
    bInit = false;
    ui->setupUi(this);

    //语言
    int temp = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    for(int i = 0; i < temp; i++)
    {
        ui->comboBox_titleLan->addItem(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList[i]);
    }

    //字体
    ui->comboBox_titleFontType->addItems(QFontDatabase().families(QFontDatabase::Any));

    //时间格式
    ui->comboBox_textTimeType->addItem(tr("HH:MM"));
    ui->comboBox_textTimeType->addItem(tr("HH:MM:SS"));
    ui->comboBox_textTimeType->addItem(tr("HH-MM"));
    ui->comboBox_textTimeType->addItem(tr("HH-MM-SS"));

    //日期格式
    ui->comboBox_textDateType->addItem(tr("YYYY/MM/DD"));
    ui->comboBox_textDateType->addItem(tr("YYYY.MM.DD"));
    ui->comboBox_textDateType->addItem(tr("YYYY-MM-DD"));
    ui->comboBox_textDateType->addItem(tr("MM/DD/YYYY"));
    ui->comboBox_textDateType->addItem(tr("MM.DD.YYYY"));
    ui->comboBox_textDateType->addItem(tr("MM-DD-YYYY"));
    ui->comboBox_textDateType->addItem(tr("DD/MM/YYYY"));
    ui->comboBox_textDateType->addItem(tr("DD.MM.YYYY"));
    ui->comboBox_textDateType->addItem(tr("DD-MM-YYYY"));

    bInit = true;
}

QHistoryDataShowOne::~QHistoryDataShowOne()
{
    delete ui;
}

void QHistoryDataShowOne::Init(QHistoryDataShowAttr* pItem)
{
    if(pItem)
    {
        m_nForecolor        = pItem->m_nForecolor;
        m_nFrameColor       = pItem->m_nFrameColor;
        m_nAlpha            = pItem->m_nAlpha;

        m_nTextFontSize     = pItem->m_nTextFontSize;
        m_nLine             = pItem->m_nLine;
        m_nTextFontColor    = pItem->m_nTextFontColor;

        m_bShowTime         = pItem->m_bShowTime;
        m_bShowDate         = pItem->m_bShowDate;
        m_nTitleBackColor   = pItem->m_nTitleBackColor;
        m_nTitleFontColor   = pItem->m_nTitleFontColor;
        m_bShowCode         = pItem->m_bShowCode;
        m_eTimeFormat       = pItem->m_eTimeFormat;
        m_eDateFormat       = pItem->m_eDateFormat;
        m_bAddr             = pItem->m_bAddr;
        m_KeyAddr           = pItem->m_KeyAddr;

        m_vecHisText        = pItem->m_vecHisText;
    }
    else
    {
        m_nForecolor        = QColor(192,192,192);
        m_nFrameColor       = QColor(0,0,0);
        m_nAlpha            = 255;
        m_nTextFontSize     = 10;
        m_nLine             = 5;
        m_nTextFontColor    = QColor(0,0,0);
        m_bShowTime         = true;
        m_bShowDate         = true;
        m_nTitleBackColor   = QColor(255,255,0);
        m_nTitleFontColor   = QColor(0,0,0);
        m_bShowCode         = false;
        m_eTimeFormat       = HHMM_COLON;
        m_eDateFormat       = DDMMYYYY_SLASH;
        m_bAddr             = false;
        m_KeyAddr.sShowAddr = "LW0";
        m_vecHisText.clear();
    }

    if(pItem && (pItem->sGroupName == ""))//数据采集被删掉或者修改为实时的时候的处理方式
    {
        ui->checkBox_textTimeb->setEnabled(false);
        ui->checkBox_textDateb->setEnabled(false);
        ui->checkBox_textNum->setEnabled(false);
        //return;
    }

    //当前语言数与上面初始化的语言数不吻合的时候
    //即已经形成了图形后改变语言数，然后再进入这里，或者初始化赋值为0肯定进这里
    if(m_vecHisText.size() != pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size())
    {
        m_vecHisText.clear();

        int lanNum =  pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
        HistoryTextInfo info;
        for(int i = 0; i < lanNum; i++)
        {
            info.m_nTitleFontSize = 10;
            info.m_nTitleLanguage = i;
            info.m_sTitleDateName = tr("日期");
            info.m_sTitleFontType = tr("Droid Sans Fallback");
            info.m_sTitleTimeName = tr("时间");
            info.m_sTitleNumber   = tr("序号");

            m_vecHisText.push_back(info);
        }
    }

    ui->spinBox_dataFontSize->setValue(m_nTextFontSize);
    ui->pushButton_dataColor->setStyleSheet(QString("background:%1").arg(m_nTextFontColor.name()));
    ui->spinBox_dataLine->setValue(m_nLine);

    ui->pushButton_frontColor->setStyleSheet(QString("background:%1").arg(m_nForecolor.name()));
    ui->pushButton_frameColor->setStyleSheet(QString("background:%1").arg(m_nFrameColor.name()));
    ui->spinBox->setValue(m_nAlpha);

    ui->pushButton_textBk->setStyleSheet(QString("background:%1").arg(m_nTitleBackColor.name()));
    ui->pushButton_textWordColor->setStyleSheet(QString("background:%1").arg(m_nTitleFontColor.name()));
    ui->checkBox_textTimeb->setChecked(m_bShowTime);
    ui->comboBox_textTimeType->setCurrentIndex((int)m_eTimeFormat - 1);
    ui->comboBox_textTimeType->setEnabled(m_bShowTime);
    ui->checkBox_textDateb->setChecked(m_bShowDate);
    ui->comboBox_textDateType->setCurrentIndex((int)m_eDateFormat - 1);
    ui->comboBox_textDateType->setEnabled(m_bShowDate);
    ui->checkBox_textNum->setChecked(m_bShowCode);

    ui->checkBox_Ctrl->setChecked(m_bAddr);
    ui->lineEdit_Ctrl->setText(m_KeyAddr.sShowAddr);
    ui->lineEdit_Ctrl->setEnabled(m_bAddr);
    ui->pushButton_Ctrl->setEnabled(m_bAddr);

    //默认语言设置为第一项
    m_nCurLanNum = 0;
    ui->comboBox_titleLan->setCurrentIndex(0);
    ui->spinBox_titleFontSize->setValue(m_vecHisText[0].m_nTitleFontSize);
    int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
    for(int i = 0; i < fontNum; i++)
    {
        if(QFontDatabase().families(QFontDatabase::Any).at(i) == m_vecHisText[0].m_sTitleFontType)
        {
            ui->comboBox_titleFontType->setCurrentIndex(i);
            break;
        }
    }
    ui->lineEdit_titleTime->setText(m_vecHisText[0].m_sTitleTimeName);
    ui->lineEdit_titleDate->setText(m_vecHisText[0].m_sTitleDateName);
    ui->lineEdit_number->setText(m_vecHisText[0].m_sTitleNumber);
}

//数据
void QHistoryDataShowOne::on_spinBox_dataFontSize_valueChanged(int value)
{
    m_nTextFontSize = value;
    emit redrawSence();
}

void QHistoryDataShowOne::on_spinBox_dataLine_valueChanged(int value)
{
    m_nLine = value;
    emit redrawSence();
}

void QHistoryDataShowOne::on_pushButton_dataColor_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
    pwnd->OnAddColorDlg(ui->pushButton_dataColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_dataColor(const QColor &)));
}

void QHistoryDataShowOne::set_pushButton_dataColor(const QColor & mColor)
{
    ui->pushButton_dataColor->setStyleSheet(QString("background:%1").arg(mColor.name()));
    m_nTextFontColor = mColor;
    emit redrawSence();
}

//框
void QHistoryDataShowOne::on_pushButton_frontColor_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
    pwnd->OnAddColorDlg(ui->pushButton_frontColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_frontColor(const QColor &)));
}

void QHistoryDataShowOne::set_pushButton_frontColor(const QColor & mColor)
{
    ui->pushButton_frontColor->setStyleSheet(QString("background:%1").arg(mColor.name()));
    m_nForecolor = mColor;
    emit redrawSence();
}

void QHistoryDataShowOne::on_pushButton_frameColor_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
    pwnd->OnAddColorDlg(ui->pushButton_frameColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_frameColor(const QColor &)));
}

void QHistoryDataShowOne::set_pushButton_frameColor(const QColor & mColor)
{
    ui->pushButton_frameColor->setStyleSheet(QString("background:%1").arg(mColor.name()));
    m_nFrameColor = mColor;
    emit redrawSence();
}

//文本列
void QHistoryDataShowOne::on_pushButton_textBk_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
    pwnd->OnAddColorDlg(ui->pushButton_textBk, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_textBk(const QColor &)));
}

void QHistoryDataShowOne::set_pushButton_textBk(const QColor & mColor)
{
    ui->pushButton_textBk->setStyleSheet(QString("background:%1").arg(mColor.name()));
    m_nTitleBackColor = mColor;
    emit redrawSence();
}

void QHistoryDataShowOne::on_pushButton_textWordColor_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
    pwnd->OnAddColorDlg(ui->pushButton_textWordColor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_textWordColor(const QColor &)));
}

void QHistoryDataShowOne::set_pushButton_textWordColor(const QColor & mColor)
{
    ui->pushButton_textWordColor->setStyleSheet(QString("background:%1").arg(mColor.name()));
    m_nTitleFontColor = mColor;
    emit redrawSence();
}

void QHistoryDataShowOne::on_checkBox_textTimeb_clicked(bool checked)
{
    m_bShowTime = checked;
    ui->comboBox_textTimeType->setEnabled(checked);
    emit redrawSence();
}

void QHistoryDataShowOne::on_comboBox_textTimeType_currentIndexChanged(int index)
{
    m_eTimeFormat = (TIME_FORMAT)(index + 1);
    emit redrawSence();
}

void QHistoryDataShowOne::on_checkBox_textDateb_clicked(bool checked)
{
    m_bShowDate = checked;
    ui->comboBox_textDateType->setEnabled(checked);
    emit redrawSence();
}

void QHistoryDataShowOne::on_comboBox_textDateType_currentIndexChanged(int index)
{
    m_eDateFormat = (DATE_FORMAT)(index + 1);
    emit redrawSence();
}

void QHistoryDataShowOne::on_checkBox_textNum_clicked(bool checked)
{
    m_bShowCode = checked;
    emit redrawSence();
}

//标题列
void QHistoryDataShowOne::on_comboBox_titleLan_currentIndexChanged(int index)
{
    if(bInit == false)
    {
        return;
    }

    m_nCurLanNum = index;

    ui->spinBox_titleFontSize->setValue(m_vecHisText[index].m_nTitleFontSize);
    int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
    for(int i = 0; i < fontNum; i++)
    {
        if(QFontDatabase().families(QFontDatabase::Any).at(i) == m_vecHisText[index].m_sTitleFontType)
        {
            ui->comboBox_titleFontType->setCurrentIndex(i);
            break;
        }
    }
    ui->lineEdit_titleTime->setText(m_vecHisText[index].m_sTitleTimeName);
    ui->lineEdit_titleDate->setText(m_vecHisText[index].m_sTitleDateName);
    ui->lineEdit_number->setText(m_vecHisText[index].m_sTitleNumber);

    emit redrawSence();
    emit sigLanguageCh(index);
}

void QHistoryDataShowOne::on_spinBox_titleFontSize_valueChanged(int value)
{
    m_vecHisText[m_nCurLanNum].m_nTitleFontSize =  value;
    emit redrawSence();
}

void QHistoryDataShowOne::on_comboBox_titleFontType_currentIndexChanged(int index)
{
    if(bInit == false)
    {
        return;
    }

    m_vecHisText[m_nCurLanNum].m_sTitleFontType = ui->comboBox_titleFontType->currentText();

    emit redrawSence();
}

void QHistoryDataShowOne::on_lineEdit_titleTime_editingFinished()
{
    if(bInit == false)
    {
        return;
    }

    m_vecHisText[m_nCurLanNum].m_sTitleTimeName = ui->lineEdit_titleTime->text();
    emit redrawSence();
}

void QHistoryDataShowOne::on_lineEdit_titleDate_editingFinished()
{
    if(bInit == false)
    {
        return;
    }

    m_vecHisText[m_nCurLanNum].m_sTitleDateName = ui->lineEdit_titleDate->text();

    emit redrawSence();
}

void QHistoryDataShowOne::on_lineEdit_number_editingFinished()
{
    if(bInit == false)
    {
        return;
    }

    m_vecHisText[m_nCurLanNum].m_sTitleNumber = ui->lineEdit_number->text();

    if(m_bShowCode)
    {
        emit redrawSence();
    }
}

void QHistoryDataShowOne::on_spinBox_valueChanged(int value)
{
    if(bInit == false)
    {
        return;
    }

    m_nAlpha = value;
    emit redrawSence();
}

void QHistoryDataShowOne::slotLan(int lan)
{
    ui->comboBox_titleLan->setCurrentIndex(lan);

    m_nCurLanNum = lan;

    ui->spinBox_titleFontSize->setValue(m_vecHisText[lan].m_nTitleFontSize);
    int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
    for(int i = 0; i < fontNum; i++)
    {
        if(QFontDatabase().families(QFontDatabase::Any).at(i) == m_vecHisText[lan].m_sTitleFontType)
        {
            ui->comboBox_titleFontType->setCurrentIndex(i);
            break;
        }
    }
    ui->lineEdit_titleTime->setText(m_vecHisText[lan].m_sTitleTimeName);
    ui->lineEdit_titleDate->setText(m_vecHisText[lan].m_sTitleDateName);
    ui->lineEdit_number->setText(m_vecHisText[lan].m_sTitleNumber);

    emit redrawSence();
}

void QHistoryDataShowOne::groupCh()
{
    ui->checkBox_textTimeb->setEnabled(true);
    ui->checkBox_textDateb->setEnabled(true);
    ui->checkBox_textNum->setEnabled(true);
}

void QHistoryDataShowOne::on_checkBox_Ctrl_clicked(bool checked)
{
    m_bAddr = checked;
    ui->lineEdit_Ctrl->setEnabled(checked);
    ui->pushButton_Ctrl->setEnabled(checked);
}

void QHistoryDataShowOne::on_pushButton_Ctrl_clicked()
{
    QString str = ui->lineEdit_Ctrl->text();
    AddressInputDialog dlg_readaddress(m_KeyAddr,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_Ctrl->setText(m_KeyAddr.sShowAddr);
    }
}
