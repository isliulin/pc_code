#include "SliderGeneralDlg.h"

#include "view/qdrawgraphics.h"
#include  "Frame\MainWindow.h"
extern MainWindow  *pwnd;

SliderGeneralDlg::SliderGeneralDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliderGeneralDlg)
{
    ui->setupUi(this);

    pScene = new QGraphicsScene(this);     //������
    //ui->MainView->setScene(pScene);           //����ͼ��ʾ����

    pwnd->InitDateType(ui->m_datatypecmb);//������������
    ui->m_datatypecmb->removeItem(4);//ɾ��16λ��32λBCD��
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
    if(ui->checkBox->isChecked()==false)//��̬��Χδ��ѡ
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
    ui->m_datatypecmb->setCurrentIndex(0); //�����������
    ui->m_radiop1->setChecked(true); //����Ϊ����

    ui->m_directcmb->addItem(tr("����"));
    ui->m_directcmb->addItem(tr("����"));
    ui->m_minbtn->setVisible(false);
    ui->m_maxbtn->setVisible(false);

    ui->m_backcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(128,160,160).name()));
    ui->m_linecolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    ui->m_bkcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(131,0,131).name()));
    ui->m_frmcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,129,131).name()));
    ui->m_maxedit->setText(tr("0"));
    ui->m_maxedit->setText(tr("65535"));


    //�̶�
    bIfShow = true;         //�Ƿ�����
    bIfSelectColor = false; //��ɫ�Ƿ����ı�
    bIfAxis = true;         //�Ƿ�ѡ������
    sColor = pwnd->ColorTOString(QColor(255,0,0));     //��ɫ
    bScaleMark = true;      //�Ƿ�ѡ���˿̶ȱ�ʾ
    nMainScal = 7;          //���̶���
    nSubScal = 2;           //�ο̶���
    dMax = 100;             //���ֵ
    dMin = 0;               //��Сֵ
    nTotalNum = 3;          //��λ��
    nPointNum = 0;          //С��λ��
    nFontIndex = 2;         //��ѡ�����С�±�
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

void SliderGeneralDlg::OnSetBkColor(const QColor & currentColor)//����ָ�걳��ɫ
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

void SliderGeneralDlg::OnDirectRadioChange(int nChecked)//�̶�λ�÷����ı�
{
    if(!bInitFlag)
        return;

    ui->m_directcmb->clear();
    switch(nChecked)
    {
    case 1:
    case 2:
        ui->m_directcmb->addItem(tr("����"));
        ui->m_directcmb->addItem(tr("����"));
        break;
    case 3:
    case 4:
        ui->m_directcmb->addItem(tr("����"));
        ui->m_directcmb->addItem(tr("����"));
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

void SliderGeneralDlg::on_m_addrbtn_clicked()//д���ַ
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





void SliderGeneralDlg::on_m_directcmb_currentIndexChanged(int index)//����
{
    if(!bInitFlag)
        return;

    emit ReDrawSlider();
}

bool SliderGeneralDlg::SaveGeneralPage(SliderInfo &m_slider)
{
    //����ɫ
    m_slider.rectColor = pwnd->ColorTOString(ui->m_backcolorbtn->palette().background().color());
    //����ɫ
    m_slider.slideBarColor = pwnd->ColorTOString(ui->m_linecolorbtn ->palette().background().color());
    //ָ�걳��ɫ
    m_slider.fingerBackColor = pwnd->ColorTOString(ui->m_bkcolorbtn ->palette().background().color());
    //ָ��߿�ɫ
    m_slider.fingerLineColor = pwnd->ColorTOString(ui->m_frmcolorbtn ->palette().background().color());
    //λ��
    m_slider.direction = RadioButton->checkedId();
    //����
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
    //�������
    m_slider.dataType = ui->m_datatypecmb->currentIndex();
    //д���ַ�ı�
    m_slider.writeAddress=ui->m_addredit->text();
    //д���ַ
    if(! pwnd->IsAddressCheckRight(WriteAddr,tr("д���ַ"),ui->m_addredit,1))
    {
        ui->m_addredit->setFocus();
        return false;
    }
    m_slider.keyWriteAddress = WriteAddr;
    //��̬��Χ
    m_slider.isTrend = ui->checkBox->isChecked();


    if(ui->checkBox->isChecked()){
        if(! pwnd->IsAddressCheckRight(MinAddr,tr("��Сֵ��ַ"),ui->m_minedit,1))
        {
            ui->m_minedit->setFocus();
            return false;
        }
        m_slider.MinAddress = MinAddr;

        if(! pwnd->IsAddressCheckRight(MaxAddr,tr("���ֵ��ַ"),ui->m_maxedit,1))
        {
            ui->m_maxedit->setFocus();
            return false;
        }
        m_slider.MaxAddress = MaxAddr;
    }

    m_slider.minTrend=ui->m_minedit->text();//��Сֵ��Χ�ı�
    m_slider.maxTrend=ui->m_maxedit->text();//���ֵ��Χ�ı�
    //�̶�
    //�Ƿ�����
    m_slider.isShowCalibration=ui->m_displaycheck->isChecked();
    //ָ����ɫ
    m_slider.nCalibrationColor=pwnd->ColorTOString(ui->m_colorbtn->palette().background().color());
    //���̶���
    m_slider.nMaxNumber=ui->m_mainscalspin->value();
    //���̶���
    m_slider.nMinNumber=ui->m_subscalspin->value();
    //�̶ȱ�ʾ
    m_slider.bShowText=ui->m_scalemarkcheck->isChecked();
    //�����С
    m_slider.nTextSize=ui->m_fontsizecmb->currentIndex();
    m_slider.sTextSize=ui->m_fontsizecmb->currentText();
    //��Сֵ;
    m_slider.nCalibrationMin=ui->m_minedit_2->text();
    //���ֵ;
    m_slider.nCalibrationMax=ui->m_maxedit_2->text();
    //��λ��
    m_slider.nTotalCount=ui->m_totalnumberspin->value();
    //С��λ��
    m_slider.nDecimalCount=ui->m_pointnumberspin->value();


    if(ui->m_minedit_2->text().toDouble()>ui->m_maxedit_2->text().toDouble()){
        QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("��Сֵ���ܴ������ֵ"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
        box.exec();
        ui->m_minedit_2->setFocus();
        ui->m_minedit_2->selectAll();
        return false;
    }

    if(m_slider.isTrend==false){
        if(ui->m_minedit->text().toDouble()>ui->m_maxedit->text().toDouble()){
            QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("��Χ��Сֵ���ܴ������ֵ"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
            box.exec();
            ui->m_minedit->setFocus();
            ui->m_minedit->selectAll();
            return false;
        }
        //�ж��������͵�ֵ
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
            QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("��Χ��Сֵ���������Ͳ���Ӧ"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
            box.exec();
            ui->m_minedit->setFocus();
            ui->m_minedit->selectAll();
            return false;
        }else if(ui->m_maxedit->text().toDouble()>maxNum){
            QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("��Χ���ֵ���������Ͳ���Ӧ"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
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
            ui->m_directcmb->addItem(tr("����"));
            ui->m_directcmb->addItem(tr("����"));
            break;
        case 3:
        case 4:
            ui->m_directcmb->addItem(tr("����"));
            ui->m_directcmb->addItem(tr("����"));
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
        //��̬��Χ
        //ui->m_minedit->setText(pItem->m_slider.MinAddress.sShowAddr);
        //ui->m_maxedit->setText(pItem->m_slider.MaxAddress.sShowAddr);
        ui->m_minedit->setText(pItem->m_slider.minTrend);
        ui->m_maxedit->setText(pItem->m_slider.maxTrend);
        //�̶������С
        ui->m_fontsizecmb->setCurrentIndex(pItem->m_slider.nTextSize);
        //�̶���ʾ
        ui->m_displaycheck->setChecked(pItem->m_slider.isShowCalibration);
        //�̶���ɫ
        ui->m_colorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->m_slider.nCalibrationColor).name()));
        //�̶����̶�
        ui->m_mainscalspin->setValue(pItem->m_slider.nMaxNumber);
        //�̶ȸ��̶�
        ui->m_subscalspin->setValue(pItem->m_slider.nMinNumber);
        //�̶���ʾ�ı�
        ui->m_scalemarkcheck->setChecked(pItem->m_slider.bShowText);
        //�̶���Сֵ
        ui->m_minedit_2->setText(pItem->m_slider.nCalibrationMin);
        //�̶����ֵ
        ui->m_maxedit_2->setText(pItem->m_slider.nCalibrationMax);
        //�̶���λ��
        ui->m_totalnumberspin->setValue(pItem->m_slider.nTotalCount);
        //�̶���Сλ��
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
        case 0://16λ��
            ui->m_minedit->setText("0");
            ui->m_maxedit->setText("65535");
            break;
        case 1://32λ��
            ui->m_minedit->setText("0");
            ui->m_maxedit->setText("4294967295");
            break;
        case 2://16λ��
            ui->m_minedit->setText("-32768");
            ui->m_maxedit->setText("32767");
            break;
        case 3://32λ��
            ui->m_minedit->setText("-2147483647");
            ui->m_maxedit->setText("2147483647");
            break;
        case 4://32λ��
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
        ui->m_scalemarkcheck->setEnabled(true);//�̶ȱ�ʾ����
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

        ui->m_scalemarkcheck->setEnabled(false);//�̶ȱ�ʾ����
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

void SliderGeneralDlg::on_m_mainscalspin_valueChanged(int ) //���̶�
{
    if(!bInitFlag)
    {
        return;
    }
    //�������Ƿ����ݵĻ�����
    // encode
    nMainScal = ui->m_mainscalspin->value();  //���̶���
    emit ReDrawSlider();                       //�ػ��Ǳ�
}

void SliderGeneralDlg::on_m_subscalspin_valueChanged(int )
{
    if(!bInitFlag)
    {
        return;
    }
    //�������Ƿ����ݵĻ�����
    // encode
    nSubScal = ui->m_subscalspin->value();  //���̶���
    emit ReDrawSlider();                     //�ػ��Ǳ�
}

void SliderGeneralDlg::on_m_fontsizecmb_currentIndexChanged(int index) //�����С
{
    if(!bInitFlag)
    {
        return;
    }
    nFontIndex = ui->m_fontsizecmb->currentIndex();   //��ѡ�����±�
    QString sFont = ui->m_fontsizecmb->currentText(); //�����С
    nFontSize = sFont.toInt();
    emit ReDrawSlider();                               //�ػ��Ǳ�
}

void SliderGeneralDlg::on_m_pointnumberspin_valueChanged(int  nIndex) //С��λ��
{
    if(!bInitFlag)
    {
        return;
    }
    if(nIndex > ui->m_totalnumberspin->value())
    {
        ui->m_pointnumberspin->setValue(ui->m_totalnumberspin->value());
    }
    //�������Ƿ����ݵĻ�����
    // encode
    nPointNum = ui->m_pointnumberspin->value();  //С��λ��
    emit ReDrawSlider();                          //�ػ��Ǳ�
}


//��Сֵ
void SliderGeneralDlg::on_m_minedit_2_textChanged(QString )
{
    if(!bInitFlag)
    {
        return;
    }
    //�������Ƿ����ݵĻ�����
    // encode
    QString sMin = ui->m_minedit_2->text();
    dMin = sMin.toDouble();
    emit ReDrawSlider();
}

//���ֵ
void SliderGeneralDlg::on_m_maxedit_2_textChanged(QString )
{
    if(!bInitFlag)
    {
        return;
    }
    //�������Ƿ����ݵĻ�����
    // encode
    QString sMax = ui->m_maxedit_2->text();
    dMax = sMax.toDouble();
    emit ReDrawSlider();
}
//��Сֵ��ַ
void SliderGeneralDlg::on_m_minbtn_clicked()
{
    QString addrStr = ui->m_minedit->text();
    AddressInputDialog addressintputdlg_writeaddress(MinAddr,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_minedit->setText(MinAddr.sShowAddr);
    }
}
//���ֵ��ַ
void SliderGeneralDlg::on_m_maxbtn_clicked()
{
    QString addrStr = ui->m_maxedit->text();
    AddressInputDialog addressintputdlg_writeaddress(MaxAddr,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_maxedit->setText(MaxAddr.sShowAddr);
    }
}
