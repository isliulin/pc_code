#include "qtrendatime.h"

#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

QTrendaTime::QTrendaTime(QWidget *parent):QWidget(parent),ui(new Ui::QTrendaTime)
{
    ui->setupUi(this);

    //��һ���������ĸ���0����������ݿ�ͷ,1����ǰʱ�̴�������.....
    //m_nOldFocus = 0;//��ʼ���������ֵ����Init������

    //X��ʱ�䵥λ
    //ui->comboBox_timeUnit->addItem(tr("��"));
    //ui->comboBox_timeUnit->addItem(tr("��"));
    //ui->comboBox_timeUnit->addItem(tr("ʱ"));
    //ui->comboBox_timeUnit->addItem(tr("��"));
    //ui->comboBox_timeUnit->addItem(tr("��"));
    //ui->comboBox_timeUnit->addItem(tr("��"));
    ui->checkBox_timeFormat->setChecked(true);
    ui->checkBox_dateFormat->setChecked(true);
    //ui->label_3->setVisible(false);
    //ui->label_9->setVisible(false);

    //ʱ���ʽ
    ui->comboBox_timeFormat->addItem(tr("HH:MM"));
    ui->comboBox_timeFormat->addItem(tr("HH:MM:SS"));
    ui->comboBox_timeFormat->addItem(tr("HH-MM"));
    ui->comboBox_timeFormat->addItem(tr("HH-MM-SS"));

    //��������
    /*ui->comboBox_fontType->addItem(tr("����"));
    ui->comboBox_fontType->addItem(tr("ʸ������"));
    ui->label_5->setEnabled(false);
    ui->comboBox_fontType->setEnabled(false);*/

    //���ʱ�䵥λ
    ui->comboBox_near->addItem(tr("��"));
    ui->comboBox_near->addItem(tr("ʱ"));
    ui->comboBox_near->addItem(tr("��"));
    ui->comboBox_near->addItem(tr("��"));

    //���ڸ�ʽ
    ui->comboBox_dateFormat->addItem(tr("YYYY/MM/DD"));
    ui->comboBox_dateFormat->addItem(tr("YYYY.MM.DD"));
    ui->comboBox_dateFormat->addItem(tr("YYYY-MM-DD"));
    ui->comboBox_dateFormat->addItem(tr("MM/DD/YYYY"));
    ui->comboBox_dateFormat->addItem(tr("MM.DD.YYYY"));
    ui->comboBox_dateFormat->addItem(tr("MM-DD-YYYY"));
    ui->comboBox_dateFormat->addItem(tr("DD/MM/YYYY"));
    ui->comboBox_dateFormat->addItem(tr("DD.MM.YYYY"));
    ui->comboBox_dateFormat->addItem(tr("DD-MM-YYYY"));

    //����ûѡ�е�����
    if(ui->radioButton_diskBegin->isChecked())//����ѡ�дӴ������ݿ�ʼ
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

    if(ui->radioButton_near->isChecked())//����ѡ�����
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

    if(ui->radioButton->isChecked())//����ѡ�дӡ�������������
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

    if(ui->radioButton_from->isChecked())//����ѡ�е�ַ
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

/*void QTrendaTime::on_comboBox_timeUnit_currentIndexChanged(int index)//X��ʱ�䵥λ
{
    m_eTimeUnit = (TimeUnitType)index;
}*/

void QTrendaTime::on_comboBox_timeFormat_currentIndexChanged(int index)//ʱ���ʽ
{
    m_eTimeFormat = (TimeType)(index + 1);
}

void QTrendaTime::on_comboBox_fontType_currentIndexChanged(int index)//��������
{
    m_eFontType = (FontType)(index + 1);
}

void QTrendaTime::on_comboBox_fontTxtAttr_currentIndexChanged(int index)//�ı�����
{
    m_eTxtAttr = (TxtAttrType)(index + 1);
}

void QTrendaTime::on_spinBox_fontSize_valueChanged(int value)//�����С
{
    m_nFontSize = value;
}

void QTrendaTime::on_comboBox_near_currentIndexChanged(int index)//���ʱ�䵥λ
{
    m_eTimeUnitNear = (TimeUnitType)(index + 1);
}

void QTrendaTime::on_comboBox_dateFormat_currentIndexChanged(int index)//���ڸ�ʽ
{
    m_eDateFormat = (DateType)(index + 1);
}

void QTrendaTime::on_dateEdit_editingFinished()//�� ����
{
    m_dFromDate = ui->dateEdit->date();
}

void QTrendaTime::on_timeEdit_editingFinished()//�� ʱ��
{
    m_tFromTime = ui->timeEdit->time();
}

void QTrendaTime::on_dateEdit_2_editingFinished()//�� ����
{
    m_dToDate = ui->dateEdit_2->date();
}

void QTrendaTime::on_timeEdit_2_editingFinished()//�� ʱ��
{
    m_tToTime = ui->timeEdit_2->time();
}

void QTrendaTime::on_radioButton_diskBegin_clicked()//�Ӵ������ݿ�ͷ
{
    cleanOldFocus();
    m_nOldFocus = 2;
    m_eStart    = START_DISKBEGIN;  //�������ݿ�ͷ
    //m_eCurTime  = UNIT_MINUTE;      //��ǰ�õ�ʱ�䵥λ
    ui->label_tips->setText(tr("����ÿ��һ����ˢ��һ��"));
}

void QTrendaTime::on_radioButton_near_clicked()//���
{
    cleanOldFocus();
    m_nOldFocus = 0;
    ui->spin_near->setEnabled(true);
    ui->comboBox_near->setEnabled(true);
    m_eStart    = START_NEAR;         //���
    m_eTimeUnitNear  = (TimeUnitType)(ui->comboBox_near->currentIndex() + 1); //��ǰ�õ�ʱ�䵥λ
    ui->label_tips->setText(tr("����ʵʱˢ��"));
}

void QTrendaTime::on_radioButton_clicked()//�ӡ�����������������
{
    cleanOldFocus();
    m_nOldFocus = 1;
    ui->dateEdit->setEnabled(true);
    ui->timeEdit->setEnabled(true);
    ui->dateEdit_2->setEnabled(true);
    ui->timeEdit_2->setEnabled(true);
    m_eStart    = START_FROMTO;         //�ӡ���������������
    ui->label_tips->setText(tr("����ÿ��һ����ˢ��һ��"));
}

void QTrendaTime::on_radioButton_from_clicked()//��ַ
{
    cleanOldFocus();
    m_nOldFocus = 3;
    m_eStart    = START_ADDR;
    ui->lineEdit_from->setEnabled(true);
    ui->lineEdit_to->setEnabled(true);
    ui->pushButton_from->setEnabled(true);
    ui->pushButton_to->setEnabled(true);
    //ui->label_tips->setText(tr("����ÿ��һ����ˢ��һ��"));
}

void QTrendaTime::on_pushButton_color_clicked()//��ע��ɫ
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

void QTrendaTime::on_checkBox_hideMarked_clicked(bool checked)//��ʾX���ע
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
        if(str[i] < '0' || str[i] > '9')//��ʱ����Ĳ�������
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

void QTrendaTime::Init(QTrendAttr *pItem)//���캯��֮�����еĺ���
{
    if(pItem)//��ֵ������
    {
        //m_eTimeUnit     = pItem->m_eTimeUnit;    //X��ʱ�䵥λ
        m_eTimeFormat   = pItem->m_eTimeFormat;  //ʱ���ʽ
        m_eDateFormat   = pItem->m_eDateFormat;  //���ڸ�ʽ
        m_eFontType     = pItem->m_eFontType;    //��������
        m_eTxtAttr      = pItem->m_eTxtAttr;     //�ı�����
        m_eStart        = pItem->m_eStart;       //������ʼ��
        m_bXMarked      = pItem->m_bXMarked;     //�Ƿ�X���ע
        m_nFontSize     = pItem->m_nFontSize;    //�����С
        m_nMarkedColor  = pItem->m_nMarkedColor; //��ע��ɫ
        m_nTimeLen      = pItem->m_nTimeLen;     //�ӿ�ʼ��Ҫ����ʱ��
        m_eTimeUnitNear = pItem->m_eTimeUnitNear;//���ʱ�䵥λ
        m_dFromDate     = pItem->m_dFromDate;    //��ʼ����
        m_tFromTime     = pItem->m_tFromTime;    //��ʼʱ��
        m_dToDate       = pItem->m_dToDate;      //��ֹ����
        m_tToTime       = pItem->m_tToTime;      //��ֹʱ��
        m_kbFrom        = pItem->m_kbFrom;
        m_kbTo          = pItem->m_kbTo;
        m_bDateFormat   = pItem->m_bDateFormat;
        m_bTimeFormat   = pItem->m_bTimeFormat;

        if(pItem->m_eTableType == TypeRealTime)//ʵʱ����
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

        ui->comboBox_timeFormat->setCurrentIndex((int)m_eTimeFormat - 1);   //ʱ���ʽ
        ui->comboBox_dateFormat->setCurrentIndex((int)m_eDateFormat - 1);   //���ڸ�ʽ
        //ui->comboBox_fontType->setCurrentIndex((int)m_eFontType - 1);       //��������
        ui->comboBox_near->setCurrentIndex((int)m_eTimeUnitNear - 1);
        ui->spinBox_fontSize->setValue(m_nFontSize);                    //�����С
        //ui->pushButton_rulerColor->setStyleSheet(QString("background:%1").arg(Color.name()));
        ui->pushButton_color->setStyleSheet(QString("background:%1").arg(m_nMarkedColor.name()));//��ע��ɫ
        ui->checkBox_hideMarked->setChecked(m_bXMarked);                //�Ƿ�X���ע

        //ui->comboBox_timeUnit->setCurrentIndex((int)m_eTimeUnit);//X��ʱ�䵥λ
        m_nOldFocus = (int)m_eStart - 1;//��ǰѡ�е�������������ʼ��
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
                ui->label_tips->setText(tr("����ÿ��һ����ˢ��һ��"));
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
                ui->label_tips->setText(tr("����ÿ��һ����ˢ��һ��"));
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
    else//��ʼ������
    {
        //m_eTimeUnit     = UNIT_MINUTE;          //X��ʱ�䵥λ,Ĭ�ϵ�һ��
        m_eTimeFormat   = TIME_HM1;             //ʱ���ʽ,Ĭ�ϵ�һ��
        m_eDateFormat   = YMD_ONE;              //���ڸ�ʽ,Ĭ�ϵ�һ��
        m_eFontType     = FONT_SONGTI;          //��������,Ĭ�ϵ�һ��
        m_eTxtAttr      = TXT_CUTI;             //�ı�����,Ĭ�ϵ�һ��
        m_eStart        = START_NEAR;      //������ʼ��,Ĭ�ϵ�һ��
        m_bXMarked      = true;                //�Ƿ�X���ע
        m_nFontSize     = 10;                    //�����С
        m_nTimeLen      = 5;                    //�ӿ�ʼ��Ҫ����ʱ�䣬Ĭ��Ϊ0����Ϊѡ���Ǵ������ݿ�ͷ
        m_eTimeUnitNear = UNIT_MINUTE;          //���ʱ�䵥λ
        m_nMarkedColor  = QColor(0,0,0);  //��ע��ɫ
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
        ui->comboBox_timeFormat->setCurrentIndex((int)m_eTimeFormat - 1);//ʱ���ʽ
        ui->comboBox_dateFormat->setCurrentIndex((int)m_eDateFormat - 1);   //���ڸ�ʽ
        //ui->comboBox_fontType->setCurrentIndex((int)m_eFontType - 1);//��������
        ui->spinBox_fontSize->setValue(m_nFontSize);//�����С
        //ui->pushButton_rulerColor->setStyleSheet(QString("background:%1").arg(Color.name()));
        ui->pushButton_color->setStyleSheet(QString("background:%1").arg(m_nMarkedColor.name()));//��ע��ɫ
        ui->checkBox_hideMarked->setChecked(m_bXMarked);

        //ui->comboBox_timeUnit->setCurrentIndex((int)m_eTimeUnit);//X��ʱ�䵥λ
        m_nOldFocus = 0;//��ǰѡ�е�������������ʼ��
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
            ui->comboBox_near->addItem(tr("��"));
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
            ui->comboBox_near->addItem(tr("��"));
            ui->comboBox_near->addItem(tr("ʱ"));
            ui->comboBox_near->addItem(tr("��"));
            ui->comboBox_near->addItem(tr("��"));
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
