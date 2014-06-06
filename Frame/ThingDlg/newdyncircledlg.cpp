#include "newdyncircledlg.h"
#include "ui_newdyncircledlg.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

newDynCircleDlg::newDynCircleDlg(DynCircleAttr *pItem, QWidget *parent):QDialog(parent),ui(new Ui::newDynCircleDlg)
{
    ui->setupUi(this);

    oId = -1;
    setFixedSize(size());
    this->setWindowTitle(tr("动态圆"));
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    ui->graphicsView->setScene(&scene);

    //ui->groupBox_3->hide();

    pSecurityWight = new SecurityWidget(this);
    ui->tabWidget->addTab(pSecurityWight, tr("权限设置"));
    //pSecurityWight->ui->groupBox_Touch->hide();
    pSecurityWight->setTouchGroupEnabled(false);

    Keyboard kb;
    kb.sPlcRegTypeStr = "LW";
    kb.sShowAddr      = "LW0";
    m_addrH           = kb;
    m_addrV           = kb;
    m_addrCircle      = kb;

    itemTemp = NULL;
    Init(pItem);
}

newDynCircleDlg::~newDynCircleDlg()
{
    delete itemTemp;
    delete ui;

    if(pSecurityWight)
    {
        delete pSecurityWight;
        pSecurityWight = NULL;
    }
}

void newDynCircleDlg::Init(DynCircleAttr *pItem)
{
    if(pItem)
    {
        pSecurityWight->init(pItem);

        //矩形外观
        m_bFillColor    = pItem->m_bFillColor;
        m_nFillColor    = pItem->m_nFillColor;
        m_bFrameColor   = pItem->m_bFrameColor;
        m_nFrameColor   = pItem->m_nFrameColor;
        m_nFrameWidth   = pItem->m_nFrameWidth;
        m_nAlpha        = pItem->m_nAlpha;
        //显示区域设置
        m_nBeginX       = pItem->m_nBeginX;
        m_nBeginY       = pItem->m_nBeginY;
        m_nWidth        = pItem->m_nWidth;
        m_nHeight       = pItem->m_nHeight;
        m_nBgColor      = pItem->m_nBgColor;
        //位置控制
        m_bPosCtrl      = pItem->m_bPosCtrl;
        m_addrH         = pItem->m_addrH;
        m_addrV         = pItem->m_addrV;
        //大小控制
        m_bSizeCtrl     = pItem->m_bSizeCtrl;
        m_addrCircle    = pItem->m_addrCircle;
        oId = pItem->id();
        ui->spinBox_2->setValue(oId);
    }
    else
    {
        pSecurityWight->init(NULL);

        //矩形外观
        m_bFillColor    = true;
        m_nFillColor    = QColor(255, 0, 0);
        m_bFrameColor   = true;
        m_nFrameColor   = QColor(0, 0, 0);
        m_nFrameWidth   = 0;
        m_nAlpha        = 255;

        //显示区域设置
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
        m_nBgColor      = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneBackColor;
        //位置控制
        m_bPosCtrl      = false;
        //m_addrH=;
        //m_addrV=;
        //大小控制
        m_bSizeCtrl     = false;
        ui->spinBox_2->setValue(pwnd->getNewId());
        //m_addrCircle=;
    }

    ui->spinBox->setValue(m_nAlpha);
    ui->checkBox_fill->setChecked(m_bFillColor);
    ui->pushButton_fill->setVisible(m_bFillColor);
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
    //ui->spinBox_1->setEnabled(false);
    //ui->spinBox_2->setEnabled(false);
    //ui->spinBox_3->setEnabled(false);
    //ui->spinBox_4->setEnabled(false);
    //ui->pushButton_bgColor->setEnabled(false);

    ui->groupBox_4->setChecked(m_bPosCtrl);
    ui->lineEdit_H->setEnabled(m_bPosCtrl);
    ui->pushButton_AddrH->setEnabled(m_bPosCtrl);
    ui->lineEdit_V->setEnabled(m_bPosCtrl);
    ui->pushButton_AddrV->setEnabled(m_bPosCtrl);
    ui->lineEdit_H->setText(m_addrH.sShowAddr);
    ui->lineEdit_V->setText(m_addrV.sShowAddr);

    ui->groupBox_5->setChecked(m_bSizeCtrl);
    ui->lineEdit_width->setEnabled(m_bSizeCtrl);
    ui->pushButton_AddrWidth->setEnabled(m_bSizeCtrl);
    ui->lineEdit_width->setText(m_addrCircle.sShowAddr);

    ///itemTemp->pCircle->SetAlpha(m_nAlpha);
    itemTemp = new DynCircleAttr;
    itemTemp->resetCircle(m_nAlpha, m_bFillColor, m_bFrameColor, m_nFillColor, m_nFrameColor);
    on_checkBox_fill_clicked(m_bFillColor);
    on_checkBox_frame_clicked(m_bFrameColor);
    //itemTemp->resetCircle(m_nAlpha);

    scene.addItem(itemTemp);
}

void newDynCircleDlg::on_accept_clicked()
{
    if(ui->groupBox_4->isChecked())//位置控制
    {
        if(! pwnd->IsAddressCheckRight(m_addrH,tr("圆心横坐标地址"),ui->lineEdit_H,1))
        {
            ui->lineEdit_H->setFocus();
            return ;
        }
        if(! pwnd->IsAddressCheckRight(m_addrV,tr("圆心纵坐标地址"),ui->lineEdit_V,1))
        {
            ui->lineEdit_V->setFocus();
            return ;
        }
    }
    if(ui->groupBox_5->isChecked())//圆心控制
    {
        if(! pwnd->IsAddressCheckRight(m_addrCircle,tr("圆心纵坐标地址"),ui->lineEdit_width,1))
        {
            ui->lineEdit_width->setFocus();
            return ;
        }
    }

    m_pCopyItem = new DynCircleAttr;

    if(pSecurityWight && pSecurityWight->Save())
    {
        m_pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    }
    else
    {
        return;
    }

    //矩形外观
    m_pCopyItem->m_nAlpha        = ui->spinBox->value();
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
    //显示区域设置
    //m_pCopyItem->m_nBeginX       = ui->spinBox_1->value();
    //m_pCopyItem->m_nBeginY       = ui->spinBox_2->value();
    //m_pCopyItem->m_nWidth        = ui->spinBox_3->value();
    //m_pCopyItem->m_nHeight       = ui->spinBox_4->value();
    m_pCopyItem->m_nBgColor      = m_nBgColor;
    //位置控制
    m_pCopyItem->m_bPosCtrl      = ui->groupBox_4->isChecked();
    m_addrH.sShowAddr            = ui->lineEdit_H->text();
    m_pCopyItem->m_addrH         = m_addrH;
    m_addrV.sShowAddr            = ui->lineEdit_V->text();
    m_pCopyItem->m_addrV         = m_addrV;
    //大小控制
    m_pCopyItem->m_bSizeCtrl     = ui->groupBox_5->isChecked();
    m_addrCircle.sShowAddr       = ui->lineEdit_width->text();
    m_pCopyItem->m_addrCircle    = m_addrCircle;

    /*QDrawGraphics *pDraw = new QDrawGraphics;
    pDraw->OnDrawTrendChart(m_pCopyItem);  //加载图形
    if(pDraw)
    {
        delete pDraw;
        pDraw = NULL;
    }*/

    m_pCopyItem->resetCircle(m_nAlpha, m_bFillColor, m_bFrameColor, m_nFillColor, m_nFrameColor);
    //m_pCopyItem->resetCircle(m_pCopyItem->m_nAlpha);

    m_pCopyItem->setId(ui->spinBox_2->value());

    if(ui->spinBox_2->value() != oId && !pwnd->insertId(ui->spinBox_2->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return ;
    }
    QDialog::accept();
}

void newDynCircleDlg::on_cancel_clicked()
{
    this->close();
}

void newDynCircleDlg::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_DYNCIRCLE);
}

void newDynCircleDlg::on_checkBox_fill_clicked(bool checked)
{
    ui->pushButton_fill->setVisible(checked);
    m_bFillColor = checked;
    itemTemp->resetCircle(m_nAlpha, m_bFillColor, m_bFrameColor, m_nFillColor, m_nFrameColor);
    /*if(checked)
    {
        itemTemp->pCircle->SetPattern(1);
        itemTemp->pCircle->SetBackColor(m_nFillColor);
    }
    else
        itemTemp->pCircle->SetPattern(0);*/
}

void newDynCircleDlg::on_checkBox_frame_clicked(bool checked)
{
    if(checked)
    {
        ui->pushButton_frame->show();
        ui->label_3->show();
        //itemTemp->pCircle->SetLineType(1);
        //itemTemp->pCircle->SetLineColor(m_nFrameColor);
    }
    else
    {
        ui->pushButton_frame->hide();
        ui->label_3->hide();
        //itemTemp->pCircle->SetLineType(0);
    }
    m_bFrameColor = checked;
    itemTemp->resetCircle(m_nAlpha, m_bFillColor, m_bFrameColor, m_nFillColor, m_nFrameColor);
}

void newDynCircleDlg::on_pushButton_fill_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
    pwnd->OnAddColorDlg(ui->pushButton_fill, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_fill(const QColor &)));
}

void newDynCircleDlg::set_pushButton_fill(const QColor & mColor)
{
    ui->pushButton_fill->setStyleSheet(QString("background:%1").arg(mColor.name()));
    m_nFillColor = mColor;
    itemTemp->resetCircle(m_nAlpha, m_bFillColor, m_bFrameColor, m_nFillColor, m_nFrameColor);
}

void newDynCircleDlg::on_pushButton_frame_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
    pwnd->OnAddColorDlg(ui->pushButton_frame, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_frame(const QColor &)));
}

void newDynCircleDlg::set_pushButton_frame(const QColor & mColor)
{
    ui->pushButton_frame->setStyleSheet(QString("background:%1").arg(mColor.name()));
    m_nFrameColor = mColor;
    itemTemp->resetCircle(m_nAlpha, m_bFillColor, m_bFrameColor, m_nFillColor, m_nFrameColor);
}

void newDynCircleDlg::on_pushButton_bgColor_clicked()
{
    //ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//这里没有释放会不会有内存泄露，其他颜色也一样
    //pwnd->OnAddColorDlg(ui->pushButton_bgColor, colorPicker);

    //connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_bgColor(const QColor &)));
}

void newDynCircleDlg::set_pushButton_bgColor(const QColor & mColor)
{
    //ui->pushButton_bgColor->setStyleSheet(QString("background:%1").arg(mColor.name()));
    //m_nBgColor = mColor;
}

void newDynCircleDlg::on_pushButton_AddrH_clicked()
{
    QString str = ui->lineEdit_H->text();
    AddressInputDialog dlg_readaddress(m_addrH,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_H->setText(m_addrH.sShowAddr);
    }
}

void newDynCircleDlg::on_pushButton_AddrV_clicked()
{
    QString str = ui->lineEdit_V->text();
    AddressInputDialog dlg_readaddress(m_addrV,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_V->setText(m_addrV.sShowAddr);
    }
}

void newDynCircleDlg::on_pushButton_AddrWidth_clicked()
{
    QString str = ui->lineEdit_width->text();
    AddressInputDialog dlg_readaddress(m_addrCircle,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_width->setText(m_addrCircle.sShowAddr);
    }
}

void newDynCircleDlg::on_groupBox_4_clicked(bool checked)
{
    ui->lineEdit_H->setEnabled(checked);
    ui->pushButton_AddrH->setEnabled(checked);
    ui->lineEdit_V->setEnabled(checked);
    ui->pushButton_AddrV->setEnabled(checked);
}

void newDynCircleDlg::on_groupBox_5_clicked(bool checked)
{
    ui->lineEdit_width->setEnabled(checked);
    ui->pushButton_AddrWidth->setEnabled(checked);
}

void newDynCircleDlg::on_spinBox_valueChanged(int value)
{
    if(itemTemp)
    {
        itemTemp->resetCircle(value, m_bFillColor, m_bFrameColor, m_nFillColor, m_nFrameColor);
        m_nAlpha = value;
    }
}
