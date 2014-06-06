#include "newdynrectdlg.h"
#include "ui_newdynrectdlg.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

newDynRectDlg::newDynRectDlg(DynRectAttr *pItem, QWidget *parent):QDialog(parent),ui(new Ui::newDynRectDlg)
{
    ui->setupUi(this);

    oId = -1;
    setFixedSize(size());
    this->setWindowTitle(tr("��̬����"));
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    ui->comboBox->addItem(tr("����"));
    ui->comboBox->addItem(tr("����"));
    ui->comboBox->addItem(tr("����"));
    ui->comboBox->addItem(tr("����"));

    ui->graphicsView->setScene(&scene);

    ui->tabWidget->setTabText(0, tr("��̬��������"));

    pSecurityWight = new SecurityWidget(this);
    ui->tabWidget->addTab(pSecurityWight, tr("Ȩ������"));
    //pSecurityWight->ui->groupBox_Touch->hide();
    pSecurityWight->setTouchGroupEnabled(false);

    //ui->groupBox_3->hide();

    Keyboard kb;
    kb.sPlcRegTypeStr = "LW";
    kb.sShowAddr      = "LW0";
    m_addrH           = kb;
    m_addrV           = kb;
    m_addrWidth       = kb;
    m_addrHeight      = kb;

    itemTemp = NULL;
    Init(pItem);
}

newDynRectDlg::~newDynRectDlg()
{
    if(pSecurityWight)
    {
        delete pSecurityWight;
        pSecurityWight = NULL;
    }

    delete itemTemp;
    delete ui; 
}

void newDynRectDlg::Init(DynRectAttr *pItem)
{
    if(pItem)
    {
        m_bFillColor    = pItem->m_bFillColor;
        m_nFillColor    = pItem->m_nFillColor;
        m_bFrameColor   = pItem->m_bFrameColor;
        m_nFrameColor   = pItem->m_nFrameColor;
        m_nFrameWidth   = pItem->m_nFrameWidth;
        m_nAlpha        = pItem->m_nAlpha;
        //��ʾ��������
        m_nBeginX       = pItem->m_nBeginX;
        m_nBeginY       = pItem->m_nBeginY;
        m_nWidth        = pItem->m_nWidth;
        m_nHeight       = pItem->m_nHeight;
        m_nBgColor      = pItem->m_nBgColor;
        //λ�ÿ���
        m_bPosCtrl      = pItem->m_bPosCtrl;
        m_addrH         = pItem->m_addrH;
        m_addrV         = pItem->m_addrV;
        //��С����
        m_bSizeCtrl     = pItem->m_bSizeCtrl;
        m_nRefType      = pItem->m_nRefType;//�̶���
        m_addrWidth     = pItem->m_addrWidth;
        m_addrHeight    = pItem->m_addrHeight;

        oId = pItem->id();
        ui->spinBox_2->setValue(oId);
        pSecurityWight->init(pItem);
    }
    else
    {
        //�������
        m_bFillColor    = true;
        m_nFillColor    = QColor(255, 0, 0);
        m_bFrameColor   = true;
        m_nFrameColor   = QColor(0, 0, 0);
        m_nFrameWidth   = 1;
        m_nAlpha        = 255;
        //��ʾ��������
        m_nBeginX       = 0;
        m_nBeginY       = 0;
        if(0 == pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth)
        {
            m_nWidth    = 800;
        }
        else
        {
            m_nWidth    = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth;
        }
        if(0 == pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight)
        {
            m_nHeight   = 480;
        }
        else
        {
            m_nHeight   = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight;
        }
        m_nBgColor      = QColor(0, 0, 0);
        //λ�ÿ���
        m_bPosCtrl      = false;
        //m_addrH=;
        //m_addrV=;
        //��С����
        m_bSizeCtrl     = false;
        m_nRefType      = 0;//�̶���
        //m_addrWidth     = ;
        //m_addrHeight    = ;

        pSecurityWight->init(NULL);
        ui->spinBox_2->setValue(pwnd->getNewId());
    }

    ui->spinBox->setValue(m_nAlpha);
    ui->checkBox_fill->setChecked(m_bFillColor);
    ui->pushButton_fill->setEnabled(m_bFillColor);
    ui->pushButton_fill->setStyleSheet(QString("background:%1").arg(m_nFillColor.name()));
    ui->checkBox_frame->setChecked(m_bFrameColor);
    if(m_bFrameColor)
    {
        ui->pushButton_frame->show();
        ui->label_3->show();
    }
    else
    {
        ui->pushButton_frame->hide();
        ui->label_3->hide();
    }
    ui->pushButton_frame->setStyleSheet(QString("background:%1").arg(m_nFrameColor.name()));

    //ui->spinBox_1->setValue(m_nBeginX);
    //ui->spinBox_2->setValue(m_nBeginY);
    //ui->spinBox_3->setValue(m_nWidth);
    //ui->spinBox_4->setValue(m_nHeight);
    //ui->pushButton_bgColor->setStyleSheet(QString("background:%1").arg(m_nBgColor.name()));

    ui->groupBox_4->setChecked(m_bPosCtrl);
    ui->lineEdit_H->setEnabled(m_bPosCtrl);
    ui->pushButton_AddrH->setEnabled(m_bPosCtrl);
    ui->lineEdit_V->setEnabled(m_bPosCtrl);
    ui->pushButton_AddrV->setEnabled(m_bPosCtrl);
    ui->lineEdit_H->setText(m_addrH.sShowAddr);
    ui->lineEdit_V->setText(m_addrV.sShowAddr);

    ui->groupBox_5->setChecked(m_bSizeCtrl);
    ui->comboBox->setEnabled(m_bSizeCtrl);
    ui->lineEdit_width->setEnabled(m_bSizeCtrl);
    ui->pushButton_AddrWidth->setEnabled(m_bSizeCtrl);
    ui->lineEdit_height->setEnabled(m_bSizeCtrl);
    ui->pushButton_AddrHeight->setEnabled(m_bSizeCtrl);
    ui->comboBox->setCurrentIndex(m_nRefType);
    ui->lineEdit_width->setText(m_addrWidth.sShowAddr);
    ui->lineEdit_height->setText(m_addrHeight.sShowAddr);

    itemTemp = new DynRectAttr;
    itemTemp->resetRect(m_nAlpha, m_nFillColor, m_nFrameColor, m_bFillColor, m_bFrameColor);
    on_checkBox_fill_clicked(m_bFillColor);
    on_checkBox_frame_clicked(m_bFrameColor);
    //itemTemp->frameRect->SetAlpha(m_nAlpha);

    scene.addItem(itemTemp);
}

void newDynRectDlg::on_accept_clicked()//ȷ��
{
    if(ui->groupBox_4->isChecked())//λ�ÿ���
    {
        if(! pwnd->IsAddressCheckRight(m_addrH,tr("�������ַ"),ui->lineEdit_H,1))
        {
            ui->lineEdit_H->setFocus();
            return ;
        }
        if(! pwnd->IsAddressCheckRight(m_addrV,tr("�������ַ"),ui->lineEdit_V,1))
        {
            ui->lineEdit_V->setFocus();
            return ;
        }
    }
    if(ui->groupBox_5->isChecked())//Բ�Ŀ���
    {
        if(! pwnd->IsAddressCheckRight(m_addrWidth,tr("����������ַ"),ui->lineEdit_width,1))
        {
            ui->lineEdit_width->setFocus();
            return ;
        }
        if(! pwnd->IsAddressCheckRight(m_addrHeight,tr("�߶��������ַ"),ui->lineEdit_height,1))
        {
            ui->lineEdit_height->setFocus();
            return ;
        }
    }

    m_pCopyItem = new DynRectAttr;

    if(pSecurityWight && pSecurityWight->Save())
    {
        m_pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    }
    else
    {
        return;
    }

    //�������
    m_pCopyItem->m_bFillColor    = ui->checkBox_fill->isChecked();
    m_pCopyItem->m_nFillColor    = m_nFillColor;
    m_pCopyItem->m_bFrameColor   = ui->checkBox_frame->isChecked();
    m_pCopyItem->m_nFrameColor   = m_nFrameColor;
    if(m_pCopyItem->m_bFrameColor)
    {
        m_pCopyItem->m_nFrameWidth = 1;
    }
    else
    {
        m_pCopyItem->m_nFrameWidth = 0;
    }
    m_pCopyItem->m_nAlpha        = ui->spinBox->value();
    //��ʾ��������
    //m_pCopyItem->m_nBeginX       = ui->spinBox_1->value();
    //m_pCopyItem->m_nBeginY       = ui->spinBox_2->value();
    //m_pCopyItem->m_nWidth        = ui->spinBox_3->value();
    //m_pCopyItem->m_nHeight       = ui->spinBox_4->value();
    m_pCopyItem->m_nBgColor      = m_nBgColor;
    //λ�ÿ���
    m_pCopyItem->m_bPosCtrl      = ui->groupBox_4->isChecked();
    m_addrH.sShowAddr            = ui->lineEdit_H->text();
    m_pCopyItem->m_addrH         = m_addrH;
    m_addrV.sShowAddr            = ui->lineEdit_V->text();
    m_pCopyItem->m_addrV         = m_addrV;
    //��С����
    m_pCopyItem->m_bSizeCtrl     = ui->groupBox_5->isChecked();
    m_pCopyItem->m_nRefType      = ui->comboBox->currentIndex();//�̶���
    m_addrWidth.sShowAddr        = ui->lineEdit_width->text();
    m_pCopyItem->m_addrWidth     = m_addrWidth;
    m_addrHeight.sShowAddr       = ui->lineEdit_height->text();
    m_pCopyItem->m_addrHeight    = m_addrHeight;

    m_pCopyItem->resetRect(m_nAlpha, m_nFillColor, m_nFrameColor, m_bFillColor, m_bFrameColor);
    //m_pCopyItem->resetRect(m_nFillColor, m_nFrameColor);

    m_pCopyItem->setId(ui->spinBox_2->value());

    if(ui->spinBox_2->value() != oId && !pwnd->insertId(ui->spinBox_2->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID�ظ������޸�ID��"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox_2->setFocus();
        return ;
    }

    QDialog::accept();
}

void newDynRectDlg::on_cancel_clicked()//ȡ��
{
    this->close();
}

void newDynRectDlg::on_help_clicked()//����
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_DYNRECT);
}

void newDynRectDlg::on_checkBox_fill_clicked(bool checked)//�Ƿ���Ҫ���ɫ
{
    ui->pushButton_fill->setVisible(checked);
    m_bFillColor = checked;
    /*if(checked)
    {
       itemTemp->frameRect->SetPattern(1);
       itemTemp->frameRect->SetBackColor(m_nFillColor);
    }
    else
       itemTemp->frameRect->SetPattern(0);*/
    itemTemp->resetRect(m_nAlpha, m_nFillColor, m_nFrameColor, m_bFillColor, m_bFrameColor);
}

void newDynRectDlg::on_checkBox_frame_clicked(bool checked)//�Ƿ���Ҫ�߿�ɫ
{
    if(checked)
    {
        ui->pushButton_frame->show();
        ui->label_3->show();
        //itemTemp->frameRect->SetLineType(1);
        //itemTemp->frameRect->SetLineColor(m_nFrameColor);
    }
    else
    {
        ui->pushButton_frame->hide();
        ui->label_3->hide();
        //itemTemp->frameRect->SetLineType(0);
    }
    m_bFrameColor = checked;
    itemTemp->resetRect(m_nAlpha, m_nFillColor, m_nFrameColor, m_bFillColor, m_bFrameColor);
}

void newDynRectDlg::on_pushButton_fill_clicked()//���ɫѡ��
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//����û���ͷŻ᲻�����ڴ�й¶��������ɫҲһ��
    pwnd->OnAddColorDlg(ui->pushButton_fill, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_fill(const QColor &)));
}

void newDynRectDlg::set_pushButton_fill(const QColor & mColor)
{
    ui->pushButton_fill->setStyleSheet(QString("background:%1").arg(mColor.name()));
    m_nFillColor = mColor;
    //itemTemp->resetRect(m_nFillColor, m_nFrameColor);
    //itemTemp->frameRect->SetBackColor(m_nFillColor);
    itemTemp->resetRect(m_nAlpha, m_nFillColor, m_nFrameColor, m_bFillColor, m_bFrameColor);
}

void newDynRectDlg::on_pushButton_frame_clicked()//�߿�ɫѡ��
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//����û���ͷŻ᲻�����ڴ�й¶��������ɫҲһ��
    pwnd->OnAddColorDlg(ui->pushButton_frame, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_frame(const QColor &)));
}

void newDynRectDlg::set_pushButton_frame(const QColor & mColor)
{
    ui->pushButton_frame->setStyleSheet(QString("background:%1").arg(mColor.name()));
    m_nFrameColor = mColor;
    //itemTemp->frameRect->SetLineColor(m_nFrameColor);
    itemTemp->resetRect(m_nAlpha, m_nFillColor, m_nFrameColor, m_bFillColor, m_bFrameColor);
}

void newDynRectDlg::on_pushButton_bgColor_clicked()//���򱳾�ɫѡ��
{
    //ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//����û���ͷŻ᲻�����ڴ�й¶��������ɫҲһ��
    //pwnd->OnAddColorDlg(ui->pushButton_bgColor, colorPicker);

    //connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_bgColor(const QColor &)));
}

void newDynRectDlg::set_pushButton_bgColor(const QColor & mColor)
{
    //ui->pushButton_bgColor->setStyleSheet(QString("background:%1").arg(mColor.name()));
    //m_nBgColor = mColor;
}

void newDynRectDlg::on_pushButton_AddrH_clicked()//��������Ƶ�ַ��ť
{
    QString str = ui->lineEdit_H->text();
    AddressInputDialog dlg_readaddress(m_addrH,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_H->setText(m_addrH.sShowAddr);
    }
}

void newDynRectDlg::on_pushButton_AddrV_clicked()//��������Ƶ�ַ��ť
{
    QString str = ui->lineEdit_V->text();
    AddressInputDialog dlg_readaddress(m_addrV,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_V->setText(m_addrV.sShowAddr);
    }
}

void newDynRectDlg::on_pushButton_AddrWidth_clicked()//��ȵ�ַ����
{
    QString str = ui->lineEdit_width->text();
    AddressInputDialog dlg_readaddress(m_addrWidth,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_width->setText(m_addrWidth.sShowAddr);
    }
}

void newDynRectDlg::on_pushButton_AddrHeight_clicked()//�߶ȵ�ַ����
{
    QString str = ui->lineEdit_height->text();
    AddressInputDialog dlg_readaddress(m_addrHeight,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_height->setText(m_addrHeight.sShowAddr);
    }
}

void newDynRectDlg::on_groupBox_5_clicked(bool checked)//λ�ÿ���
{
    ui->comboBox->setEnabled(checked);
    ui->lineEdit_width->setEnabled(checked);
    ui->pushButton_AddrWidth->setEnabled(checked);
    ui->lineEdit_height->setEnabled(checked);
    ui->pushButton_AddrHeight->setEnabled(checked);
}

void newDynRectDlg::on_groupBox_4_clicked(bool checked)//λ�ÿ���
{
    ui->lineEdit_H->setEnabled(checked);
    ui->pushButton_AddrH->setEnabled(checked);
    ui->lineEdit_V->setEnabled(checked);
    ui->pushButton_AddrV->setEnabled(checked);
}

void newDynRectDlg::on_spinBox_valueChanged(int value)
{
    if(itemTemp)
    {
        m_nAlpha = value;
        itemTemp->resetRect(m_nAlpha, m_nFillColor, m_nFrameColor, m_bFillColor, m_bFrameColor);
        //itemTemp->frameRect->SetAlpha(m_nAlpha);
    }
}
