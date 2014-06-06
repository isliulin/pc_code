#include "qstaticpicturedlg.h"
#include "ui_qstaticpicturedlg.h"
#include "Frame/mainwindow.h"
#include "Frame/DrawDlg/OpenLibrary.h"
#include <QTimer>
#include <QMovie>

extern MainWindow *pwnd;

QStaticPictureDlg::QStaticPictureDlg(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QStaticPictureDlg)
{
    QGraphicsItem * Item;
    pCopyItem = NULL;
    nCurrentFram = 0;
    oId = -1;
    mMove = new QMovie;
    PTimer = new QTimer;
    pSecurityWight = new SecurityWidget;
    ui->setupUi(this);

    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    ui->tabWidget->addTab(pSecurityWight,tr("权限设置"));
    pSecurityWight->setTouchGroupEnabled(false);

    //connect(ui->m_cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->m_helpBtn, SIGNAL(clicked()), this, SLOT(loadHelp()));
    connect(ui->m_okBtn, SIGNAL(clicked()), this, SLOT(confyButton()));

    connect(PTimer, SIGNAL(timeout()),this, SLOT(OnGifRun()));

    pScene = new QGraphicsScene(this);//建场景
    ui->MainView->setScene(pScene);

    this->setFixedSize(783,533);
    ui->ControlBit->setText("LB0");

    if(pItem)
    {
        Item = dynamic_cast<QStaticPictureItem *> (pItem)->Clone();
        Init(dynamic_cast<QStaticPictureItem *> (Item));
    }
    else
    {
        Init(NULL);
    }
    ui->m_okBtn->setFocus();
}

void QStaticPictureDlg::Init(QStaticPictureItem *pItem)
{
    if(pItem)
    {
        ui->m_nRCountspBox->setValue(pItem->m_PicInfo.nRCount);
        if(1 == pItem->m_PicInfo.nIsBitCtrl)
        {
            ui->IfBitControl->setChecked(true);
            if(! pwnd->IsAddressCheckRight(CtrlAddr,tr("控制位地址"),ui->ControlBit,0))
            {
                ui->ControlBit->setFocus();
                return;
            }
            CtrlAddr = pItem->m_PicInfo.CtrlAddr;
            ui->ControlBit->setText(pItem->m_PicInfo.CtrlAddr.sShowAddr);

            if(pItem->m_PicInfo.nValidBit == 1)
            {
                ui->available_1->setChecked(true);
            }
            else
            {
                ui->available_0->setChecked(true);
            }
            on_IfBitControl_clicked(true);
        }
        else
        {
            ui->IfBitControl->setChecked(false);//不受位控制
            on_IfBitControl_clicked(false);
        }

        pSecurityWight->init(pItem);
        QString sPath = pItem->m_PicInfo.sPicPath;
        mMove->setFileName(sPath);
        nFramCount = mMove->frameCount(); //得到帧的总数
        QPixmap picture = QPixmap(sPath);
        QPixmap newimage = picture.scaled(QSize(100,100));
        QRectItem *rectItem1 = new QRectItem(QRectF(0,0,100,100));
        rectItem1->SetBackColor(Qt::black);
        rectItem1->SetFrontColor(Qt::black);
        rectItem1->SetLineType(0);
        pScene->addItem(rectItem1);
        pPic = pScene->addPixmap(newimage);
        nCurrentFram = 0;
        mMove->jumpToFrame(nCurrentFram); //跳到第一帧
        pPixmap = new QPixmapItem(picture,newimage.size());
        pCopyItem = new QStaticPictureItem;
        pCopyItem->m_PicInfo = pItem->m_PicInfo;
        QRectItem *rectItem = new QRectItem(QRectF(0,0,100,100));
        rectItem->SetBackColor(Qt::black);
        rectItem->SetFrontColor(Qt::black);
        rectItem->SetLineType(0);
        pCopyItem->addToGroup(rectItem);
        pCopyItem->addToGroup(pPixmap);
        oId = pItem->id();
        ui->spinBox->setValue(oId);

        //ui->m_BackColorpushBtn->setStyleSheet(QString("background:%1").arg(pCopyItem->m_PicInfo.nBackColor.name()));
    }
    else
    {
        on_IfBitControl_clicked(false);
        ui->spinBox->setValue(pwnd->getNewId());
        //ui->m_BackColorpushBtn->setStyleSheet(QString("background:%1").arg(QColor(199,199,199).name()));
    }
}

QStaticPictureDlg::~QStaticPictureDlg()
{
    if(PTimer)
    {
        PTimer->stop();
        delete PTimer;
    }
    delete ui;
}

void QStaticPictureDlg::on_m_pathbtn_clicked()
{
    int nWidth = 0;
    int nHight = 0;
    QString sName = "";
    QString filename=QFileDialog::getOpenFileName(this,
            tr("Open File"),pwnd->picturePath,
            tr("Images (*.gif)"));
    QPixmap picture = QPixmap(filename);
    if (!picture)
    {
       return ;
    }
    nWidth = picture.width();
    nHight = picture.height();
    QPixmap newimage = picture.scaled(QSize(100,100));

    QStringList sList = filename.split("/", QString::SkipEmptyParts);
    sName = sList.at(sList.size() - 1);
    pwnd->picturePath=filename.left(filename.length()-sName.length()-1);

    pScene->clear();
    QRectItem *rectItem1 = new QRectItem(QRectF(0,0,100,100));
    rectItem1->SetBackColor(Qt::black);
    rectItem1->SetFrontColor(Qt::black);
    rectItem1->SetLineType(0);
    pScene->addItem(rectItem1);
    pPic = pScene->addPixmap(newimage);
    pScene->update();

    mMove->setFileName(filename);
    nFramCount = mMove->frameCount(); //得到帧的总数
    nCurrentFram = 0;
    mMove->jumpToFrame(nCurrentFram); //跳到第一帧


    pPixmap = new QPixmapItem(picture,newimage.size());



    QRectItem *rectItem = new QRectItem(QRectF(0,0,100,100));
    rectItem->SetBackColor(Qt::black);
    rectItem->SetFrontColor(Qt::black);
    rectItem->SetLineType(0);
    pCopyItem = new QStaticPictureItem;
    pCopyItem->addToGroup(rectItem);
    pCopyItem->addToGroup(pPixmap);
    pCopyItem->m_PicInfo.sPicPath = filename;
    pCopyItem->m_PicInfo.nOrigHeight = nHight;
    pCopyItem->m_PicInfo.nOrigWidth = nWidth;
}

void QStaticPictureDlg::on_m_BackColorpushBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    //pwnd->OnAddColorDlg(ui->m_BackColorpushBtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(onSetBackColor(const QColor &)));
}

void QStaticPictureDlg::onSetBackColor(const QColor &mColor)
{
    //ui->m_BackColorpushBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QStaticPictureDlg::confyButton()
{
    if(pCopyItem)
    {
        PTimer->stop();
        if(ui->IfBitControl->isChecked())
        {
            if(! pwnd->IsAddressCheckRight(CtrlAddr,tr("控制位地址"),ui->ControlBit,0))
            {
                ui->ControlBit->setFocus();
                return;
            }
            pCopyItem->m_PicInfo.CtrlAddr = CtrlAddr;
            pCopyItem->m_PicInfo.sCtrlAddr = ui->ControlBit->text();
            pCopyItem->m_PicInfo.nIsBitCtrl = 1;//受位控制

            if(ui->available_1->isChecked())
            {
                pCopyItem->m_PicInfo.nValidBit = 1;
            }
            else
            {
                pCopyItem->m_PicInfo.nValidBit = 0;
            }
        }
        else
        {
            pCopyItem->m_PicInfo.nIsBitCtrl = 0;//不受位控制
        }
        pCopyItem->m_PicInfo.nRCount = ui->m_nRCountspBox->value();
        pCopyItem->setId(ui->spinBox->value());
        if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
        {
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                            0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
            box.exec();
            ui->spinBox->setFocus();
            return ;
        }

        //pCopyItem->m_PicInfo.nBackColor = ui->m_BackColorpushBtn->palette().background().color();
            //pCopyItem->m_PicInfo.nPicorLib = 0;
    }
    else
    {
        QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr("没有选择图片!"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        msg.addButton(tr("确定"),QMessageBox::AcceptRole);
        msg.exec();
        return;
    }
    if(!pSecurityWight->Save())
    {
        return;
    }
    pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    accept();
}
void QStaticPictureDlg::loadHelp()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_STATICPIC);
}

void QStaticPictureDlg::on_m_runstopbtn_clicked() //运行测试
{
    QString str = "";
    str = ui->m_runstopbtn->text();
    if(str == tr("运行测试"))
    {
        qDebug()<<tr("运行测试");
        ui->m_runstopbtn->setText(tr("停止运行"));
        OnAddMovie();
    }
    else if(str == tr("停止运行"))
    {
        ui->m_runstopbtn->setText(tr("运行测试"));
        PTimer->stop();
    }
}

void QStaticPictureDlg::OnAddMovie()
{
    QList<QGraphicsItem *> items = pScene->items();
    if(items.size() < 1)  //没有图片的时候返回
    {
        ui->m_runstopbtn->setText(tr("运行测试"));
        return;
    }

    qDebug()<<"OnAddMovie run";
    PTimer->start(100);
    mMove->jumpToFrame(nCurrentFram); //跳到第一帧
    QPixmap pPix = mMove->currentPixmap();
    pPix = pPix.scaled(QSize(100,100));
    pPic->setPixmap(pPix);
   /* */
}

void QStaticPictureDlg::OnGifRun()
{
    qDebug()<<"OnGifRun run nCurrentFram = "<<nCurrentFram;
    nCurrentFram++;
    if(nCurrentFram < nFramCount)
    {
        mMove->jumpToFrame(nCurrentFram); //跳到下一帧
    }
    else
    {
        nCurrentFram = 0;
        mMove->jumpToFrame(nCurrentFram); //跳到下一帧
    }

    QPixmap pPix = mMove->currentPixmap();
    pPix = pPix.scaled(QSize(100,100));
    pPic->setPixmap(pPix);

}

void QStaticPictureDlg::on_m_cancelBtn_clicked()
{
    PTimer->stop();
    reject();
}

void QStaticPictureDlg::on_pushButton_clicked()
{
    QString addrStr = ui->ControlBit->text();
    AddressInputDialog addressintputdlg_writeaddress(CtrlAddr,addrStr,0,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->ControlBit->setText(CtrlAddr.sShowAddr);
    }
}

void QStaticPictureDlg::on_IfBitControl_clicked(bool checked)
{
    if(checked)
    {
        ui->label_3->setEnabled(true);
        ui->ControlBit->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->label_4->setEnabled(true);
        ui->available_1->setEnabled(true);
        ui->available_0->setEnabled(true);
    }
    else
    {
        ui->label_3->setEnabled(false);
        ui->ControlBit->setEnabled(false);
        ui->pushButton->setEnabled(false);
        ui->label_4->setEnabled(false);
        ui->available_1->setEnabled(false);
        ui->available_0->setEnabled(false);
    }
}
