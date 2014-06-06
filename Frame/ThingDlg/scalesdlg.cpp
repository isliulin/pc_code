#include "scalesdlg.h"
#include "ui_scalesdlg.h"
#include "view/qlineitem.h"
#include "view/qsimpletextitem.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

ScalesDlg::ScalesDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScalesDlg)
{
    ui->setupUi(this);
    bInitFlag=false;
    pScene = new QGraphicsScene(this);
    pDirection = new QButtonGroup(this); //����
    pDirection->addButton(ui->m_radio1,1);//��
    pDirection->addButton(ui->m_radio2,2);//��
    pDirection->addButton(ui->m_radio3,3);//��
    pDirection->addButton(ui->m_radio4,4);//��
    QIntValidator* aValidator = new QIntValidator(this);
    ui->m_maxedit->setValidator(aValidator);
    ui->m_minedit->setValidator(aValidator);
    connect(pDirection, SIGNAL(buttonClicked(int)),this,SLOT(OnScaleDirectionChange(int)));

}

ScalesDlg::~ScalesDlg()
{
    if(pDirection)
    {
        delete pDirection;
        pDirection=NULL;
    }
    if(pScene)
    {
        delete pScene;
        pScene=NULL;
    }
    delete ui;
}

void ScalesDlg::InitParament()
{
    QStringList list;

    ui->m_linecolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    ui->m_textcolorbtn->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    //ui->m_showscalecheck->setChecked(true);
    ui->m_showtextcheck->setChecked(true);
    ui->m_fontsizecmb->setCurrentIndex(5);
    ui->m_minedit->setText(tr("0"));
    ui->m_maxedit->setText(tr("100"));
    ui->m_radio2->setChecked(true);

    list << tr("����") << tr("����");
    ui->m_textdirectioncmb->addItems(list);
    ui->m_textdirectioncmb->setCurrentIndex(0);

    bInitFlag = true;
}

void ScalesDlg::OnSetLineColor(const QColor & currentColor) //����������ɫ
{
    ui->m_linecolorbtn->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::OnSetTextColor(const QColor & currentColor) //�����ı���ɫ
{
    ui->m_textcolorbtn->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::OnScaleDirectionChange(int nIndex)
{
    ui->m_textdirectioncmb->clear();
    QStringList list;
    switch(nIndex)
    {
    case 1: //��������
        list << tr("����") << tr("����");
        break;
    case 2: //��������
        list << tr("����") << tr("����");
        break;
    case 3: //��������
        list << tr("����") << tr("����");
        break;
    case 4: //��������
        list << tr("����") << tr("����");
        break;
    default:
        break;
    }
    ui->m_textdirectioncmb->addItems(list);

    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_showscalecheck_clicked(bool checked)//��ʾ������
{
    if(checked)
    {
        ui->label_3->setEnabled(true);
        ui->label_4->setEnabled(true);
        ui->m_mainspin->setEnabled(true);
        ui->m_subspin->setEnabled(true);
    }
    else
    {
        ui->label_3->setEnabled(false);
        ui->label_4->setEnabled(false);
        ui->m_mainspin->setEnabled(false);
        ui->m_subspin->setEnabled(false);
    }

    if(!bInitFlag)
        return;
    emit DrawScales();
}



void ScalesDlg::on_m_textdirectioncmb_currentIndexChanged(int index) //�ı�����
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_mainspin_valueChanged(int )//���̶�
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_subspin_valueChanged(int )//�ο̶�
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_pointnumcmb_highlighted(int index)//С��λ��
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_minedit_textChanged(QString )
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_maxedit_textChanged(QString )
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_fontsizecmb_currentIndexChanged(int index)//�����С
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_pointnumcmb_currentIndexChanged(int index)
{
    if(!bInitFlag)
        return;
    emit DrawScales();
}

void ScalesDlg::on_m_showtextcheck_clicked(bool checked)
{
    if(checked)
    {
        ui->label_5->setEnabled(true);
        ui->label_6->setEnabled(true);
        ui->label_7->setEnabled(true);
        ui->label_8->setEnabled(true);
        ui->m_minedit->setEnabled(true);
        ui->m_maxedit->setEnabled(true);
        ui->m_fontsizecmb->setEnabled(true);
        ui->m_pointnumcmb->setEnabled(true);
    }
    else
    {
        ui->label_5->setEnabled(false);
        ui->label_6->setEnabled(false);
        ui->label_7->setEnabled(false);
        ui->label_8->setEnabled(false);
        ui->m_minedit->setEnabled(false);
        ui->m_maxedit->setEnabled(false);
        ui->m_fontsizecmb->setEnabled(false);
        ui->m_pointnumcmb->setEnabled(false);
    }

    if(!bInitFlag)
        return;

//    emit DrawScales();
}

void ScalesDlg::SaveGeneralPage(Calibration &m_calibration)
{
    QColor mColor;
    //������ɫ
    mColor = ui->m_linecolorbtn->palette().background().color();
    m_calibration.nLineColor=pwnd->ColorTOString(mColor);
    //�ı���ɫ
    mColor = ui-> m_textcolorbtn ->palette().background().color();
    m_calibration.nTextColor=pwnd->ColorTOString(mColor);
    //�̶ȷ���
    m_calibration.nCalibrationDirection = pDirection->checkedId();
    //�ı�����
    m_calibration.nNumberIncreaseDirection = ui->m_textdirectioncmb->currentIndex();
    m_calibration.direction=ui->m_textdirectioncmb->currentText();
    //���̶�
    m_calibration.nMainNumberCount = ui->m_mainspin->value();
    //�ο̶�
    m_calibration.nNextNumberCount = ui->m_subspin->value();
    //�Ƿ���ʾ�ı�
    m_calibration.bShowText = ui->m_showtextcheck->isChecked();
    //��Сֵ
    m_calibration.nMaxNumber = ui->m_maxedit->text();
    //���ֵ
    m_calibration.nMinNumber = ui->m_minedit->text();
    //�����С
    m_calibration.nTextSize = ui->m_fontsizecmb->currentIndex();
    m_calibration.stextsize = ui->m_fontsizecmb->currentText();
    //С��λ��
    m_calibration.nDecimalCount = ui->m_pointnumcmb->currentIndex();
}

void ScalesDlg::DoubleClickInit(CalibrationItem *pItem)
{
    QColor mColor;
    if(pItem)   //��Data �� stringList�л�ȡ���Բ�����
    {
        mColor = pwnd->StringTOColor(pItem->m_calibrations.nLineColor);
        ui->m_linecolorbtn->setStyleSheet( QString("background:%1").arg(mColor.name()));

        mColor = pwnd->StringTOColor(pItem->m_calibrations.nTextColor);
        ui-> m_textcolorbtn->setStyleSheet( QString("background:%1").arg(mColor.name()));

        QAbstractButton *btn=pDirection->button(pItem->m_calibrations.nCalibrationDirection);
        if(btn)
        {
            btn->setChecked(true);
        }
        OnScaleDirectionChange(pItem->m_calibrations.nCalibrationDirection);
        ui->m_textdirectioncmb->setCurrentIndex(pItem->m_calibrations.nNumberIncreaseDirection);

        ui->m_mainspin->setValue(pItem->m_calibrations.nMainNumberCount);

        ui->m_subspin->setValue(pItem->m_calibrations.nNextNumberCount);

        ui->m_showtextcheck->setChecked(pItem->m_calibrations.bShowText);

        ui->m_minedit->setText(pItem->m_calibrations.nMinNumber);
        ui->m_maxedit->setText(pItem->m_calibrations.nMaxNumber);

        ui->m_fontsizecmb->setCurrentIndex(pItem->m_calibrations.nTextSize);

        ui->m_pointnumcmb->setCurrentIndex(pItem->m_calibrations.nDecimalCount);

        on_m_showtextcheck_clicked(pItem->m_calibrations.bShowText);

    }
    bInitFlag = true;
}

void ScalesDlg::on_m_linecolorbtn_clicked()
{

    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_linecolorbtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetLineColor(const QColor &)));
}

void ScalesDlg::on_m_textcolorbtn_clicked()
{

    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_textcolorbtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetTextColor(const QColor &)));
}

void ScalesDlg::on_m_showtextcheck_clicked()
{
    emit DrawScales();
}
