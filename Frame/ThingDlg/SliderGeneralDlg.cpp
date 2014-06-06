#include "SliderGeneralDlg.h"

#include "view/qdrawgraphics.h"
#include  "Frame\MainWindow.h"
extern MainWindow  *pwnd;

SliderGeneralDlg::SliderGeneralDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliderGeneralDlg)
{
    ui->setupUi(this);

    pScene = new QGraphicsScene(this);     //建场景
    //ui->MainView->setScene(pScene);           //用视图显示场景

    pwnd->InitDateType(ui->m_datatypecmb);//加载数据类型
    ui->m_datatypecmb->removeItem(4);//删除16位、32位BCD码
    ui->m_datatypecmb->removeItem(4);

    RadioButton=new QButtonGroup(this);
    RadioButton->addButton(ui->m_radiop1,1);
    RadioButton->addButton(ui->m_radiop2,2);
    RadioButton->addButton(ui->m_radiop3,3);
    RadioButton->addButton(ui->m_radiop4,4);

    connect(RadioButton,SIGNAL(buttonClicked(int)),this,SLOT(OnDirectRadioChange(int)));
    ui->m_addredit->setText("LW0");

    DoubleValidator *aDoubleValidator = new DoubleValidator(this);
    aDoubleValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->m_maxedit_2->setValidator(aDoubleValidator);
    ui->m_minedit_2->setValidator(aDoubleValidator);
    ui->checkBox->setChecked(false);
    if(ui->checkBox->isChecked()==false)//动态范围未勾选
    {
        ui->m_maxedit->setValidator(aDoubleValidator);
        ui->m_minedit->setValidator(aDoubleValidator);
    }
}

SliderGeneralDlg::~SliderGeneralDlg()
{
    if(pScene)
    {
        delete pScene;
        pScene = NULL;
    }
    if(RadioButton)
    {
        delete RadioButton;
        RadioButton = NULL;
    }
    delete ui;
}


void SliderGeneralDlg::InitParament()
{
    bInitFlag = false;
    ui->m_datatypecmb->setCurrentIndex(0); //设置数据类别
    ui->m_radiop1->setChecked(true); //设置为向上

    ui->m_directcmb->addItem(tr("向左"));
    ui->m_directcmb->addItem(tr("向右"));
    ui->m_minbtn->setVisible(false);
    ui->m_maxbtn->setVisible(false);

    ui->m_backcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(128,160,160).name()));
    ui->m_linecolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    ui->m_bkcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(131,0,131).name()));
    ui->m_frmcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,129,131).name()));
    ui->m_maxedit->setText(tr("0"));
    ui->m_maxedit->setText(tr("65535"));


    //刻度
    bIfShow = true;         //是否显现
    bIfSelectColor = false; //颜色是否发生改变
    bIfAxis = true;         //是否选择了轴
    sColor = pwnd->ColorTOString(QColor(255,0,0));     //颜色
    bScaleMark = true;      //是否选择了刻度标示
    nMainScal = 7;          //主刻度数
    nSubScal = 2;           //次刻度数
    dMax = 100;             //最大值
    dMin = 0;               //最小值
    nTotalNum = 3;          //总位数
    nPointNum = 0;          //小数位数
    nFontIndex = 2;         //所选字体大小下标
    nFontSize =10;

    ui->m_fontsizecmb->setCurrentIndex(nFontIndex);
    nFontSize = ui->m_fontsizecmb->currentText().toInt();

    ui->m_displaycheck->setChecked(bIfShow);
    ui->m_colorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(sColor).name()));

    ui->m_mainscalspin->setValue(nMainScal);
    ui->m_subscalspin->setValue(nSubScal);
    //ui->m_axischeck->setChecked(bIfAxis);
    ui->m_scalemarkcheck->setChecked(bScaleMark);

    ui->m_minedit_2->setText(tr("0"));
    ui->m_maxedit_2->setText(tr("100"));
    ui->m_totalnumberspin->setValue(nTotalNum);
    ui->m_pointnumberspin->setValue(nPointNum);
    on_m_scalemarkcheck_clicked();
    on_m_displaycheck_clicked();
    bInitFlag = true;


}

void SliderGeneralDlg::OnSetBackColor(const QColor & currentColor)
{
    ui->m_backcolorbtn ->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    if(!bInitFlag)
        return;

    emit ReDrawSlider();
}

void SliderGeneralDlg::OnSetLineColor(const QColor & currentColor)
{
     ui-> m_linecolorbtn ->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    if(!bInitFlag)
        return;

    emit ReDrawSlider();
}

void SliderGeneralDlg::OnSetBkColor(const QColor & currentColor)//设置指标背景色
{
     ui->m_bkcolorbtn ->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    if(!bInitFlag)
        return;

    emit ReDrawSlider();
}

void SliderGeneralDlg::OnSetFrmColor(const QColor & currentColor)
{
     ui->m_frmcolorbtn ->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    if(!bInitFlag)
        return;

    emit ReDrawSlider();
}

void SliderGeneralDlg::OnDirectRadioChange(int nChecked)//刻度位置发生改变
{
    if(!bInitFlag)
        return;

    ui->m_directcmb->clear();
    switch(nChecked)
    {
    case 1:
    case 2:
        ui->m_directcmb->addItem(tr("向左"));
        ui->m_directcmb->addItem(tr("向右"));
        break;
    case 3:
    case 4:
        ui->m_directcmb->addItem(tr("向上"));
        ui->m_directcmb->addItem(tr("向下"));
        break;
    }
    emit ReDrawSlider();
}

void SliderGeneralDlg::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->m_minbtn->setVisible(true);
        ui->m_maxbtn->setVisible(true);

        ui->m_minedit->setText(tr("LW0"));
        ui->m_maxedit->setText(tr("LW0"));
        ui->m_maxedit->setValidator(NULL);
        ui->m_minedit->setValidator(NULL);
    }
    else
    {
        ui->m_minbtn->setVisible(false);
        ui->m_maxbtn->setVisible(false);
        DoubleValidator *aDoubleValidator = new DoubleValidator(this);
        aDoubleValidator->setNotation(QDoubleValidator::StandardNotation);
        ui->checkBox->setChecked(false);
        ui->m_maxedit->setValidator(aDoubleValidator);
        ui->m_minedit->setValidator(aDoubleValidator);
        int nIndex = ui->m_datatypecmb->currentIndex();
        on_m_datatypecmb_currentIndexChanged(nIndex);
    }
}

void SliderGeneralDlg::on_m_addrbtn_clicked()//写入地址
{
//    pwnd->Addr_Type=1;
//    AddressInputDialog  dlg_triggered(WriteAddr,this);
//    dlg_triggered.exec();
//    ui->m_addredit->setText(WriteAddr.sShowAddr);

    QString addrStr = ui->m_addredit->text();
    AddressInputDialog addressintputdlg_writeaddress(WriteAddr,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_addredit->setText(WriteAddr.sShowAddr);
    }
}





void SliderGeneralDlg::on_m_directcmb_currentIndexChanged(int index)//方向
{
    if(!bInitFlag)
        return;

    emit ReDrawSlider();
}

bool SliderGeneralDlg::SaveGeneralPage(SliderInfo &m_slider)
{
    //背景色
    m_slider.rectColor = pwnd->ColorTOString(ui->m_backcolorbtn->palette().background().color());
    //滑轨色
    m_slider.slideBarColor = pwnd->ColorTOString(ui->m_linecolorbtn ->palette().background().color());
    //指标背景色
    m_slider.fingerBackColor = pwnd->ColorTOString(ui->m_bkcolorbtn ->palette().background().color());
    //指标边框色
    m_slider.fingerLineColor = pwnd->ColorTOString(ui->m_frmcolorbtn ->palette().background().color());
    //位置
    m_slider.direction = RadioButton->checkedId();
    //方向
    m_slider.nPosition = ui->m_directcmb->currentIndex();
    /*if(m_slider.direction == 3 || m_slider.direction == 4)
    {
        m_slider.nPosition = ui->m_directcmb->currentIndex();
    }
    else
    {
        m_slider.nPosition = ui->m_directcmb->currentIndex();
    }*/
    //m_slider.sPosition = ui->m_directcmb->currentText();
    //数据类别
    m_slider.dataType = ui->m_datatypecmb->currentIndex();
    //写入地址文本
    m_slider.writeAddress=ui->m_addredit->text();
    //写入地址
    if(! pwnd->IsAddressCheckRight(WriteAddr,tr("写入地址"),ui->m_addredit,1))
    {
        ui->m_addredit->setFocus();
        return false;
    }
    m_slider.keyWriteAddress = WriteAddr;
    //动态范围
    m_slider.isTrend = ui->checkBox->isChecked();


    if(ui->checkBox->isChecked()){
        if(! pwnd->IsAddressCheckRight(MinAddr,tr("最小值地址"),ui->m_minedit,1))
        {
            ui->m_minedit->setFocus();
            return false;
        }
        m_slider.MinAddress = MinAddr;

        if(! pwnd->IsAddressCheckRight(MaxAddr,tr("最大值地址"),ui->m_maxedit,1))
        {
            ui->m_maxedit->setFocus();
            return false;
        }
        m_slider.MaxAddress = MaxAddr;
    }

    m_slider.minTrend=ui->m_minedit->text();//最小值范围文本
    m_slider.maxTrend=ui->m_maxedit->text();//最大值范围文本
    //刻度
    //是否显现
    m_slider.isShowCalibration=ui->m_displaycheck->isChecked();
    //指针颜色
    m_slider.nCalibrationColor=pwnd->ColorTOString(ui->m_colorbtn->palette().background().color());
    //主刻度数
    m_slider.nMaxNumber=ui->m_mainscalspin->value();
    //副刻度数
    m_slider.nMinNumber=ui->m_subscalspin->value();
    //刻度标示
    m_slider.bShowText=ui->m_scalemarkcheck->isChecked();
    //字体大小
    m_slider.nTextSize=ui->m_fontsizecmb->currentIndex();
    m_slider.sTextSize=ui->m_fontsizecmb->currentText();
    //最小值;
    m_slider.nCalibrationMin=ui->m_minedit_2->text();
    //最大值;
    m_slider.nCalibrationMax=ui->m_maxedit_2->text();
    //总位数
    m_slider.nTotalCount=ui->m_totalnumberspin->value();
    //小数位数
    m_slider.nDecimalCount=ui->m_pointnumberspin->value();


    if(ui->m_minedit_2->text().toDouble()>ui->m_maxedit_2->text().toDouble()){
        QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("最小值不能大于最大值"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("确定"));
        box.exec();
        ui->m_minedit_2->setFocus();
        ui->m_minedit_2->selectAll();
        return false;
    }

    if(m_slider.isTrend==false){
        if(ui->m_minedit->text().toDouble()>ui->m_maxedit->text().toDouble()){
            QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("范围最小值不能大于最大值"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("确定"));
            box.exec();
            ui->m_minedit->setFocus();
            ui->m_minedit->selectAll();
            return false;
        }
        //判断数据类型的值
        if(ui->m_datatypecmb->currentIndex()==0){
            maxNum=65535;
            minNum=0;
        }else if(ui->m_datatypecmb->currentIndex()==1){
            maxNum=4294967295L;
            minNum=0;
        }else if(ui->m_datatypecmb->currentIndex()==2){
            maxNum=32768;
            minNum=-32768;
        }else if(ui->m_datatypecmb->currentIndex()==3){
            maxNum=2147483647;
            minNum=-2147483647;
        }else if(ui->m_datatypecmb->currentIndex()==4){
            maxNum=2147483647;
            minNum=-2147483647;
        }
        if(ui->m_minedit->text().toDouble()<minNum){
            QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("范围最小值与数据类型不对应"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("确定"));
            box.exec();
            ui->m_minedit->setFocus();
            ui->m_minedit->selectAll();
            return false;
        }else if(ui->m_maxedit->text().toDouble()>maxNum){
            QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("范围最大值与数据类型不对应"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("确定"));
            box.exec();
            ui->m_minedit->setFocus();
            ui->m_minedit->selectAll();
            return false;
        }
    }
    return true;
}

void SliderGeneralDlg::DoubleClickInit(SliderItem *pItem)
{
    bInitFlag = false;
    if(pItem)
    {
        QColor mColor;
        mColor = pwnd->StringTOColor(pItem->m_slider.rectColor);
        ui->m_backcolorbtn->setStyleSheet( QString("background:%1").arg(mColor.name()));

        mColor = pwnd->StringTOColor(pItem->m_slider.slideBarColor);
        ui->m_linecolorbtn->setStyleSheet( QString("background:%1").arg(mColor.name()));

        mColor = pwnd->StringTOColor(pItem->m_slider.fingerBackColor);
        ui->m_bkcolorbtn ->setStyleSheet( QString("background:%1").arg(mColor.name()));

        mColor = pwnd->StringTOColor(pItem->m_slider.fingerLineColor);
        ui->m_frmcolorbtn ->setStyleSheet( QString("background:%1").arg(mColor.name()));

        OnDirectRadioChange(pItem->m_slider.direction);

        switch(pItem->m_slider.direction)
        {
        case 1:
        case 2:
            ui->m_directcmb->addItem(tr("向左"));
            ui->m_directcmb->addItem(tr("向右"));
            break;
        case 3:
        case 4:
            ui->m_directcmb->addItem(tr("向上"));
            ui->m_directcmb->addItem(tr("向下"));
            break;
        }
        ui->m_directcmb->setCurrentIndex(pItem->m_slider.nPosition);
        QAbstractButton *btn=RadioButton->button(pItem->m_slider.direction);
        if(btn)
        {
            btn->setChecked(true);
        }
        ui->m_datatypecmb->setCurrentIndex(pItem->m_slider.dataType);
        pwnd->StringToKeyboard(WriteAddr,pItem->m_slider.writeAddress);
        ui->m_addredit->setText(pItem->m_slider.keyWriteAddress.sShowAddr);
        ui->checkBox->setChecked(pItem->m_slider.isTrend);
        on_checkBox_clicked(pItem->m_slider.isTrend);
        pwnd->StringToKeyboard(MinAddr,pItem->m_slider.minTrend);
        pwnd->StringToKeyboard(MaxAddr,pItem->m_slider.maxTrend);
        //动态范围
        //ui->m_minedit->setText(pItem->m_slider.MinAddress.sShowAddr);
        //ui->m_maxedit->setText(pItem->m_slider.MaxAddress.sShowAddr);
        ui->m_minedit->setText(pItem->m_slider.minTrend);
        ui->m_maxedit->setText(pItem->m_slider.maxTrend);
        //刻度字体大小
        ui->m_fontsizecmb->setCurrentIndex(pItem->m_slider.nTextSize);
        //刻度显示
        ui->m_displaycheck->setChecked(pItem->m_slider.isShowCalibration);
        //刻度颜色
        ui->m_colorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->m_slider.nCalibrationColor).name()));
        //刻度主刻度
        ui->m_mainscalspin->setValue(pItem->m_slider.nMaxNumber);
        //刻度副刻度
        ui->m_subscalspin->setValue(pItem->m_slider.nMinNumber);
        //刻度显示文本
        ui->m_scalemarkcheck->setChecked(pItem->m_slider.bShowText);
        //刻度最小值
        ui->m_minedit_2->setText(pItem->m_slider.nCalibrationMin);
        //刻度最大值
        ui->m_maxedit_2->setText(pItem->m_slider.nCalibrationMax);
        //刻度总位数
        ui->m_totalnumberspin->setValue(pItem->m_slider.nTotalCount);
        //刻度最小位数
        ui->m_pointnumberspin->setValue(pItem->m_slider.nDecimalCount);
        on_m_displaycheck_clicked();
    }
    bInitFlag = true;
}

void SliderGeneralDlg::on_m_datatypecmb_currentIndexChanged(int index)
{
    if(!ui->checkBox->checkState())
    {
        switch(index)
        {
        case 0://16位正
            ui->m_minedit->setText("0");
            ui->m_maxedit->setText("65535");
            break;
        case 1://32位正
            ui->m_minedit->setText("0");
            ui->m_maxedit->setText("4294967295");
            break;
        case 2://16位整
            ui->m_minedit->setText("-32768");
            ui->m_maxedit->setText("32767");
            break;
        case 3://32位整
            ui->m_minedit->setText("-2147483647");
            ui->m_maxedit->setText("2147483647");
            break;
        case 4://32位浮
            ui->m_minedit->setText("-2147482647");
            ui->m_maxedit->setText("2147482648");
            break;
        default:
            break;
        }
    }
}

void SliderGeneralDlg::on_m_backcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_backcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetBackColor(const QColor &)));
}

void SliderGeneralDlg::on_m_linecolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_linecolorbtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetLineColor(const QColor &)));
}

void SliderGeneralDlg::on_m_bkcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_bkcolorbtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetBkColor(const QColor &)));
}

void SliderGeneralDlg::on_m_frmcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_frmcolorbtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetFrmColor(const QColor &)));
}

void SliderGeneralDlg::on_checkBox_clicked()
{
    on_checkBox_clicked(ui->checkBox->isChecked());
}

void SliderGeneralDlg::on_m_totalnumberspin_valueChanged(int nIndex)
{
    if(nIndex < ui->m_pointnumberspin->value())
    {
        ui->m_pointnumberspin->setValue(nIndex);
    }
}

void SliderGeneralDlg::on_m_colorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_colorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetColor(const QColor &)));
}




void SliderGeneralDlg::on_m_displaycheck_clicked()
{
     bIfShow = ui->m_displaycheck->isChecked();
    if(bIfShow)
    {
        ui->label_1->setEnabled(true);
        ui->label_9->setEnabled(true);
        ui->label_10->setEnabled(true);
        ui->m_colorbtn->setEnabled(true);
        ui->m_mainscalspin->setEnabled(true);
        ui->m_subscalspin->setEnabled(true);

        ui->m_maxedit_2->setEnabled(true);
        ui->m_minedit_2->setEnabled(true);
        ui->m_scalemarkcheck->setEnabled(true);//刻度标示隐藏
        on_m_scalemarkcheck_clicked();
    }
    else
    {
        ui->label_1->setEnabled(false);
        ui->label_9->setEnabled(false);
        ui->label_10->setEnabled(false);
        ui->m_colorbtn->setEnabled(false);
        ui->m_mainscalspin->setEnabled(false);
        ui->m_subscalspin->setEnabled(false);

        ui->m_scalemarkcheck->setEnabled(false);//刻度标示隐藏
        ui->label_11->setEnabled(false);
        ui->label_12->setEnabled(false);
        ui->label_13->setEnabled(false);
        ui->label_14->setEnabled(false);
        ui->label_15->setEnabled(false);

        ui->m_fontsizecmb->setEnabled(false);
        ui->m_maxedit_2->setEnabled(false);
        ui->m_minedit_2->setEnabled(false);
        ui->m_totalnumberspin->setEnabled(false);
        ui->m_pointnumberspin->setEnabled(false);
    }
    emit ReDrawSlider();
}

void SliderGeneralDlg::on_m_scalemarkcheck_clicked()
{
    bScaleMark = ui->m_scalemarkcheck->isChecked();
    if(bScaleMark)
    {
        ui->label_11->setEnabled(true);
        ui->label_12->setEnabled(true);
        ui->label_13->setEnabled(true);
        ui->label_14->setEnabled(true);
        ui->label_15->setEnabled(true);

        ui->m_fontsizecmb->setEnabled(true);
        ui->m_minedit_2->setEnabled(true);
        ui->m_maxedit_2->setEnabled(true);
        ui->m_totalnumberspin->setEnabled(true);
        ui->m_pointnumberspin->setEnabled(true);
    }
    else
    {
        ui->label_11->setEnabled(false);
        ui->label_12->setEnabled(false);
        ui->label_13->setEnabled(false);
        ui->label_14->setEnabled(false);
        ui->label_15->setEnabled(false);

        ui->m_fontsizecmb->setEnabled(false);
        ui->m_minedit_2->setEnabled(false);
        ui->m_maxedit_2->setEnabled(false);
        ui->m_totalnumberspin->setEnabled(false);
        ui->m_pointnumberspin->setEnabled(false);
    }
    emit ReDrawSlider();
}

void SliderGeneralDlg::OnSetColor(const QColor & nColor ) //set the color
{
    ui->m_colorbtn ->setStyleSheet(QString("background:%1").arg(nColor.name()));
    bIfSelectColor = true;
    sColor = pwnd->ColorTOString(nColor);
    emit ReDrawSlider();
    bIfSelectColor = false;
}

void SliderGeneralDlg::on_m_mainscalspin_valueChanged(int ) //主刻度
{
    if(!bInitFlag)
    {
        return;
    }
    //如果输入非法数据的话返回
    // encode
    nMainScal = ui->m_mainscalspin->value();  //主刻度数
    emit ReDrawSlider();                       //重绘仪表
}

void SliderGeneralDlg::on_m_subscalspin_valueChanged(int )
{
    if(!bInitFlag)
    {
        return;
    }
    //如果输入非法数据的话返回
    // encode
    nSubScal = ui->m_subscalspin->value();  //主刻度数
    emit ReDrawSlider();                     //重绘仪表
}

void SliderGeneralDlg::on_m_fontsizecmb_currentIndexChanged(int index) //字体大小
{
    if(!bInitFlag)
    {
        return;
    }
    nFontIndex = ui->m_fontsizecmb->currentIndex();   //所选字体下标
    QString sFont = ui->m_fontsizecmb->currentText(); //字体大小
    nFontSize = sFont.toInt();
    emit ReDrawSlider();                               //重绘仪表
}

void SliderGeneralDlg::on_m_pointnumberspin_valueChanged(int  nIndex) //小数位数
{
    if(!bInitFlag)
    {
        return;
    }
    if(nIndex > ui->m_totalnumberspin->value())
    {
        ui->m_pointnumberspin->setValue(ui->m_totalnumberspin->value());
    }
    //如果输入非法数据的话返回
    // encode
    nPointNum = ui->m_pointnumberspin->value();  //小数位数
    emit ReDrawSlider();                          //重绘仪表
}


//最小值
void SliderGeneralDlg::on_m_minedit_2_textChanged(QString )
{
    if(!bInitFlag)
    {
        return;
    }
    //如果输入非法数据的话返回
    // encode
    QString sMin = ui->m_minedit_2->text();
    dMin = sMin.toDouble();
    emit ReDrawSlider();
}

//最大值
void SliderGeneralDlg::on_m_maxedit_2_textChanged(QString )
{
    if(!bInitFlag)
    {
        return;
    }
    //如果输入非法数据的话返回
    // encode
    QString sMax = ui->m_maxedit_2->text();
    dMax = sMax.toDouble();
    emit ReDrawSlider();
}
//最小值地址
void SliderGeneralDlg::on_m_minbtn_clicked()
{
    QString addrStr = ui->m_minedit->text();
    AddressInputDialog addressintputdlg_writeaddress(MinAddr,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_minedit->setText(MinAddr.sShowAddr);
    }
}
//最大值地址
void SliderGeneralDlg::on_m_maxbtn_clicked()
{
    QString addrStr = ui->m_maxedit->text();
    AddressInputDialog addressintputdlg_writeaddress(MaxAddr,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_maxedit->setText(MaxAddr.sShowAddr);
    }
}
