#include "qimageshowdlg.h"
#include "ui_qimageshowdlg.h"
#include "view/qgroupitem.h"
#include "view/samdrawscene.h"
#include "Frame/mainwindow.h"
#include "Frame/ThingDlg/qmultistategenelcunstomdlg.h"
#include <qfile.h>

extern MainWindow *pwnd;

QImageShowDlg::QImageShowDlg(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QImageShowDlg)
{
    bInitFlag = false;
    QGraphicsItem *Item;
    values.clear();
    ui->setupUi(this);

    oId = -1;
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    pCopyItem = NULL;

    sWorldAddress = "LW0";
    sBitAddress = "LB0";

    pSecurityWight = new SecurityWidget;
    ui->tabWidget->addTab(pSecurityWight,tr("权限设置"));
    pSecurityWight->setTouchGroupEnabled(false);
    pScene = new QGraphicsScene(this);//建场景
    ui->MainView->setScene(pScene);
    ui->m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->m_cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->m_helpBtn, SIGNAL(clicked()), this, SLOT(loadHelp()));
    connect(ui->m_okBtn, SIGNAL(clicked()), this, SLOT(confyButton()));

    if(pItem)
    {
        Item = dynamic_cast<ImageItem *> (pItem)->Clone();
        Init(dynamic_cast<ImageItem *> (Item));
    }
    else
    {
        Init(NULL);
    }

    ui->m_okBtn->setFocus();
    bInitFlag = true;
}

void QImageShowDlg::Init(ImageItem *pItem)
{
    if(pItem)
    {
        ui->groupBox_3->setChecked(pItem->m_SaveInfo.bUseFlicker);//闪烁

        if(0 == pItem->m_SaveInfo.nChangeCondition)
        {
            //ui->m_TimeradioBtn->setChecked(true);//时间切换
            on_m_TimeradioBtn_clicked();
        }
        else if(2 == pItem->m_SaveInfo.nChangeCondition)
        {
            on_m_FixedradioBtn_clicked(true);
            //ui->m_FixedradioBtn->setChecked(true);//固定值切换
        }
        else
        {
            on_m_BitradioBtn_clicked(true);
            //ui->m_BitradioBtn->setChecked(true);//位切换
        }

        if(0 == pItem->m_SaveInfo.nFunType)
        {
            ui->m_SingleradioBtn->setChecked(true);
            on_m_SingleradioBtn_clicked(pItem->m_SaveInfo.bUseFlicker);
        }
        else
        {
            ui->m_MutilradioBtn->setChecked(true);//多幅切换
            on_m_MutilradioBtn_clicked(true);
        }

        ui->m_TimespBox->setValue(pItem->m_SaveInfo.nTimeInterval);//时间间隔
        ui->m_MonitorAddress->setText(pItem->m_SaveInfo.addr.sShowAddr);//监视地址
        if(ui->m_FixedradioBtn->isChecked())
        {
            sWorldAddress = ui->m_MonitorAddress->text();
        }
        else if(ui->m_BitradioBtn->isChecked())
        {
            sBitAddress = ui->m_MonitorAddress->text();
        }
        ui->m_StatuspBox->setValue(pItem->m_SaveInfo.nStatusTotal);//状态总数

        if(pItem->m_SaveInfo.bIsLoopType)
        {
            ui->m_comboBox->setCurrentIndex(0);
        }
        else
        {
            ui->m_comboBox->setCurrentIndex(1);
        }

        //ui->m_BackColorBtn->setStyleSheet(QString("background:%1").arg(pItem->m_SaveInfo.nBackColor.name()));

        PicInfo = pItem->m_PicInfo;
        int nRow = pItem->onGetCurrentNum();
        onItemchange(nRow);


        ui->m_tableWidget->setColumnWidth(0,40);     //设置列宽
        ui->m_tableWidget->setColumnWidth(1,200);
        ui->m_tableWidget->setRowCount(PicInfo.size());
        ui->m_tableWidget->verticalHeader()->setVisible(false);
        for(int i = 0; i< PicInfo.size(); i++)
        {
            QString str = QString("%1").arg(i);
            ui->m_tableWidget->setItem(i,0,new QTableWidgetItem(str));
            ui->m_tableWidget->setItem(i,1,new QTableWidgetItem(PicInfo[i].name));
        }
        onSetStatus(PicInfo.size());
        pSecurityWight->init(pItem);
        oId = pItem->id();
        ui->spinBox->setValue(oId);
    }
    else
    {
        ui->groupBox_3->setCheckable(false);
        on_m_SingleradioBtn_clicked(false);
        ui->groupBox_3->setTitle(tr("闪烁状态"));

        ui->m_SingleradioBtn->setChecked(true);
        on_m_TimeradioBtn_clicked();
        //ui->m_SysImageradioBtn->setChecked(true);

        //ui->m_BackColorBtn->setStyleSheet(QString("background:%1").arg(QColor(255,255,0).name()));

        ui->m_tableWidget->setColumnWidth(0,40);     //设置列宽
        ui->m_tableWidget->setColumnWidth(1,220);
        ui->m_tableWidget->setRowCount(1);
        PicInfo.resize(1);
        PicInfo[0].nCmpFactor = 0;
        PicInfo[0].name = "";
        for(int i = 0; i< 1; i++)
        {
            QString str = QString("%1").arg(i);
            ui->m_tableWidget->setItem(i,0,new QTableWidgetItem(str));
        }
        onSetStatus(1);
        ui->m_tableWidget->setRowHeight(0,25);
        ui->m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->m_tableWidget->verticalHeader()->setVisible(false);
        ui->m_StatuspBox->setEnabled(false);
        onSingleInit();
        ui->spinBox->setValue(pwnd->getNewId());
    }
}

void QImageShowDlg::onSingleInit()
{
    ui->m_FixedradioBtn->setChecked(false);
    ui->m_FixedradioBtn->hide();
}

void QImageShowDlg::onMultInit()
{
    ui->m_FixedradioBtn->show();
}

void QImageShowDlg::onTableNumChange(int nTotalRow)
{
    int nCurrentRow = ui->m_tableWidget->rowCount();
    PicInfo.resize(nTotalRow);//该数组与列表行数保持一致
    if(nCurrentRow < nTotalRow)
    {
        for(int i = nCurrentRow; i < nTotalRow; i++)
        {
            ui->m_tableWidget->insertRow(i);
            QString str = QString("%1").arg(i);
            ui->m_tableWidget->setItem(i,0,new QTableWidgetItem(str));
            ui->m_tableWidget->setRowHeight(i,25);
            PicInfo[i].nCmpFactor = i;
        }
    }
    else
    {
        for(int i = nCurrentRow - 1; i >= nTotalRow; i--)
        {
            ui->m_tableWidget->removeRow(i);
        }
        int i;
        for(i = 0; i<PicInfo.size(); i++)
        {
            if("" != PicInfo[i].name)
            {
                onItemchange(i);
                break;
            }
        }
        if(i >= PicInfo.size())
        {
            pScene->clear();
            pCopyItem = NULL;
        }
    }
    onSetStatus(nTotalRow);
}

QImageShowDlg::~QImageShowDlg()
{
    delete ui;
}

void QImageShowDlg::on_m_SingleradioBtn_clicked(bool checked)
{
    ui->m_FixedradioBtn->hide();
    if(ui->m_FixedradioBtn->isChecked())
    {
        ui->m_TimeradioBtn->setChecked(true);
    }

    ui->groupBox_3->setCheckable(true);
    ui->groupBox_3->setChecked(checked);
    ui->groupBox_3->setTitle(tr("闪烁状态"));
    ui->m_StatuspBox->setEnabled(false);
    on_groupBox_3_clicked();
}

void QImageShowDlg::on_m_MutilradioBtn_clicked(bool checked)
{
    ui->m_FixedradioBtn->show();
    ui->groupBox_3->setCheckable(false);
    ui->groupBox_3->setTitle(tr("状态切换条件"));
    on_groupBox_3_clicked();
}

void QImageShowDlg::on_m_TimeradioBtn_clicked()
{
    ui->m_TimeradioBtn->setChecked(true);
    ui->m_TimespBox->setEnabled(true);
    ui->label_3->setEnabled(true);
    ui->label_4->setEnabled(true);
    if(ui->m_SingleradioBtn->isChecked())
    {
        ui->m_StatuspBox->setRange(1,1);
        ui->m_StatuspBox->setEnabled(false);
        ui->m_label->setEnabled(false);
        ui->m_comboBox->setEnabled(false);
    }
    else
    {
       ui->m_StatuspBox->setRange(2,1000);
       ui->m_StatuspBox->setEnabled(true);
       ui->m_label->setEnabled(true);
       ui->m_comboBox->setEnabled(true);
    }
    ui->m_MonitorAddress->setEnabled(false);
    ui->Monitor_Address_EntryBtn->setEnabled(false);
    ui->label_25->setEnabled(false);
    ui->btn_customValue->setEnabled(false);
}

void QImageShowDlg::on_m_FixedradioBtn_clicked(bool checked)
{
    ui->m_FixedradioBtn->setChecked(true);
    ui->m_TimespBox->setEnabled(false);
    ui->label_3->setEnabled(false);
    ui->label_4->setEnabled(false);
    if(ui->m_SingleradioBtn->isChecked())
    {
        ui->m_StatuspBox->setRange(1,1);
    }
    else
    {
       ui->m_StatuspBox->setRange(2,1000);
       ui->m_StatuspBox->setEnabled(true);
    }
    ui->m_MonitorAddress->setText(sWorldAddress);
    ui->m_MonitorAddress->setEnabled(true);
    ui->Monitor_Address_EntryBtn->setEnabled(true);
    ui->m_label->setEnabled(false);
    ui->m_comboBox->setEnabled(false);
    ui->btn_customValue->setEnabled(true);
    ui->label_25->setEnabled(true);
}

void QImageShowDlg::on_m_BitradioBtn_clicked(bool checked)
{
    ui->m_BitradioBtn->setChecked(true);
    ui->m_TimespBox->setEnabled(false);
    ui->label_3->setEnabled(false);
    ui->label_4->setEnabled(false);
    if(ui->m_SingleradioBtn->isChecked())
    {
        ui->m_StatuspBox->setRange(1,1);
    }
    else
    {
       ui->m_StatuspBox->setRange(2,2);
       ui->m_StatuspBox->setEnabled(false);
    }
    ui->m_MonitorAddress->setText(sBitAddress);
    ui->m_MonitorAddress->setEnabled(true);
    ui->Monitor_Address_EntryBtn->setEnabled(true);
    ui->m_label->setEnabled(false);
    ui->m_comboBox->setEnabled(false);
    ui->label_25->setEnabled(true);

    ui->btn_customValue->setEnabled(false);
}

void QImageShowDlg::on_m_StatuspBox_valueChanged(int )
{
    if(!bInitFlag)
    {
        return;
    }
    int nValue = ui->m_StatuspBox->value();
    onTableNumChange(nValue);
}

void QImageShowDlg::onSelectpicbtn(int nType)
{
    QPointF pos(0,0);
    if(pCopyItem)
        pos = pCopyItem->sceneBoundingRect().topLeft();
    QStringList filename ;

    if(0 == nType) //来自文件的图片
    {
        int nCurrentRow = ui->m_tableWidget->currentRow();
        if(-1 == nCurrentRow)
        {
            nCurrentRow = 0;
        }
        filename=QFileDialog::getOpenFileNames(this,
                tr("Open File"),pwnd->picturePath,
                tr("Images (*.png *.jpg *.bmp)"));
        if(filename.size()==0)
        {
            return;
        }
        QPixmap picture = QPixmap(filename.at(0));
        if (!picture)
        {
           return ;
        }
        pwnd->picturePath=filename.at(0);

        //PicInfo[nCurrentRow].num = nCurrentRow;
        for(int i=0;i<filename.size();i++)
        {
            if(PicInfo.size() <= nCurrentRow + i)
            {
                return;
            }
            PicInfo[nCurrentRow + i].path = filename.at(i);
            PicInfo[nCurrentRow + i].name = GetPicName(filename.at(i));
            PicInfo[nCurrentRow + i].bIspic = PIC;
            //PicInfo[nCurrentRow + i].num = nCurrentRow + i;
            ui->m_tableWidget->setItem(nCurrentRow+i,1,new QTableWidgetItem(PicInfo[nCurrentRow + i].name));

        }
        pScene->clear();
        pScene->addPixmap(picture.scaled(100,86)); //newimage
        pScene->update();

        QPixmapItem *PicItem = new QPixmapItem(picture,QSize(100,86));

        pCopyItem = new ImageItem;
        pCopyItem->onSetCurrentNum(nCurrentRow);//记录当前显示的item下标
        pCopyItem->addToGroup(PicItem);
        //pBaseItem = new QGroupItem(pCopyItem);
        //pBaseItem->SetWidth(100);
        //pBaseItem->SetHeigth(100);
        QPointF newpos = pCopyItem->boundingRect().topLeft();
        pCopyItem->setPos(pos - newpos);

    }
    else if(1 == nType) //来自图库
    {
        QString sname;


        OpenLibrary *pDlg = new OpenLibrary(this);
        if(pDlg->exec() == QDialog::Accepted)
        {
            pCopyItem = onCopyItem(pDlg->pCopyItem);
            int type = pCopyItem->data(GROUP_TYPE_KEY).toInt();
            if(LIBRARY_LIB_GROUP == type)
            {
                //int nKey = pCopyItem->data(GROUP_TYPE_KEY).toInt();
                sname = pCopyItem->data(GROUP_NAME_KEY).toString();
                QStringList strName = sname.split('-');
                int nCurrentIndex = ui->m_tableWidget->currentRow();
                int nKey = strName.at(2).toInt();
                if(-1 == nCurrentIndex)
                {
                    nCurrentIndex = 0;
                }
                ui->m_tableWidget->setItem(nCurrentIndex,1,new QTableWidgetItem("elment"+strName.at(1)));
                if(LIBRARY == nKey)
                {
                   PicInfo[nCurrentIndex] .bIspic = LIBRARY;
                }
                else
                {
                    PicInfo[nCurrentIndex] .bIspic = USERDEFINE;
                }
                //PicInfo[nCurrentIndex].num = nCurrentIndex;
                PicInfo[nCurrentIndex].name = "elment"+strName.at(1);

                PicInfo[nCurrentIndex].path = pCopyItem->data(GROUP_NAME_KEY).toString();
                pCopyItem->onSetCurrentNum(nCurrentIndex);
                pScene->clear();
                QPointF newpos = pCopyItem->boundingRect().topLeft();
                pScene->addItem(pCopyItem);
                pBaseItem = new QGroupItem(pCopyItem);
                pBaseItem->SetWidth(100);
                pBaseItem->SetHeigth(100);
                pCopyItem->setPos(pos - newpos);
            }
            else if(LIBRARY_PIXMAP_GROUP == type)
            {
                int nCurrentRow = ui->m_tableWidget->currentRow();
                if(-1 == nCurrentRow)
                {
                    nCurrentRow = 0;
                }
                QString path = pCopyItem->data(GROUP_NAME_KEY).toString();
                QPixmap picture = QPixmap(path);
                if (!picture)
                {
                   return ;
                }

                PicInfo[nCurrentRow].path = path;
                PicInfo[nCurrentRow].name = GetPicName(path);
                PicInfo[nCurrentRow].bIspic = USERDEFINE;
                ui->m_tableWidget->setItem(nCurrentRow,1,new QTableWidgetItem(PicInfo[nCurrentRow].name));

                pScene->clear();
                pScene->addPixmap(picture.scaled(100,86)); //newimage
                pScene->update();

                QPixmapItem *PicItem = new QPixmapItem(picture,QSize(100,86));

                pCopyItem = new ImageItem;
                pCopyItem->onSetCurrentNum(nCurrentRow);//记录当前显示的item下标
                pCopyItem->addToGroup(PicItem);
                //pBaseItem = new QGroupItem(pCopyItem);
                //pBaseItem->SetWidth(100);
                //pBaseItem->SetHeigth(100);
                QPointF newpos = pCopyItem->boundingRect().topLeft();
                pCopyItem->setPos(pos - newpos);
            }
        }
        pDlg->deleteLater();
        pDlg = NULL;
    }
}

ImageItem *QImageShowDlg::onGetItemFromFile(QString sPath,EITEM_TYPE eType)
{
    QList <QGraphicsItem*> listItem;
    QStringList str = sPath.split('-');
    if(str.isEmpty())
    {
        return NULL;
    }
    ImageItem *pNewItem = NULL;
    int nLoadPag = str.at(0).toInt();

    if(LIBRARY == eType)
    {
        if(pwnd->vBaseLibraryScene.isEmpty())
        {
            return NULL;
        }
        listItem = pwnd->vBaseLibraryScene.at(nLoadPag)->TopItems();
        foreach (QGraphicsItem * pItem, listItem)
        {
            QString sname = pItem->data(GROUP_NAME_KEY).toString();
            if (sPath == sname)
            {
                pNewItem = onCopyItem(pItem);
                break;
            }
        }
    }
    else if(USERDEFINE == eType)
    {
        QString path = sPath;
        QPixmap picture = QPixmap(path);
        if (!picture)
        {
           return NULL;
        }
        QPixmapItem *PicItem = new QPixmapItem(picture,QSize(100,86));

        pNewItem = new ImageItem;
        pNewItem->addToGroup(PicItem);
    }
    return pNewItem;
}

ImageItem *QImageShowDlg::onCopyItem(QGraphicsItem *pItem)
{
    ImageItem *newItem = new ImageItem;
    QGraphicsItem *pOldItem;
    DrawItemToScene GroupFunction;
    QString sname;
    QString nKey;
    sname = pItem->data(GROUP_NAME_KEY).toString();
    nKey = pItem->data(GROUP_TYPE_KEY).toString();
    GroupFunction.CopyItem(&pOldItem,pItem);
    newItem->addToGroup(pOldItem);
    newItem->setData(GROUP_NAME_KEY,QVariant(sname));
    newItem->setData(GROUP_TYPE_KEY,QVariant(nKey));
    return newItem;
}
void QImageShowDlg::onItemchange(int nCurrentRow)
{
    int nrow = nCurrentRow;
    if(nrow > (PicInfo.size() - 1))
    {
        nrow = 0;
    }
    if(PicInfo.size() <0 || "" == PicInfo[nrow].name)
    {
        return;
    }
    QPointF oldpos(0,0);
    if(pCopyItem)
    {
       oldpos =  pCopyItem->sceneBoundingRect().topLeft();
    }
    if(LIBRARY == PicInfo[nrow].bIspic || USERDEFINE == PicInfo[nrow].bIspic)
    {
        if("" != PicInfo[nrow].name)
        {
            pScene->clear();
            pCopyItem = onGetItemFromFile(PicInfo[nrow].path,PicInfo[nrow].bIspic);
            if(!pCopyItem)
            {
                return;
            }
            else
            {
                pCopyItem->onSetCurrentNum(nrow);
                QPointF newpos = pCopyItem->boundingRect().topLeft();
                pScene->addItem(pCopyItem);
                pBaseItem = new QGroupItem(pCopyItem);
                pBaseItem->SetWidth(100);
                pBaseItem->SetHeigth(100);
                pCopyItem->setPos(oldpos - newpos);
                //ui->m_SysImageradioBtn->setChecked(true);
            }
        }
    }
    else
    {
        pScene->clear();
        QPixmap picture = QPixmap(PicInfo[nrow].path);
        pScene->addPixmap(picture.scaled(QSize(100,86)));
        QPixmapItem *PicItem = new QPixmapItem(picture,QSize(100,86));
        pCopyItem = new ImageItem;
        pCopyItem->onSetCurrentNum(nrow);
        pCopyItem->addToGroup(PicItem);
        QPointF newpos = pCopyItem->boundingRect().topLeft();
        pBaseItem = new QGroupItem(pCopyItem);
        pBaseItem->SetWidth(100);
        pBaseItem->SetHeigth(100);
        pCopyItem->setPos(oldpos - newpos);
        //ui->m_FileImageradioBtn->setChecked(true);
    }
}

void QImageShowDlg::on_m_tableWidget_clicked(QModelIndex index)
{
    int nrow = ui->m_tableWidget->currentRow();
    onItemchange(nrow);
}

void QImageShowDlg::on_m_deletepicbtn_clicked()
{
    QModelIndex index;
    int nCurrentRow = ui->m_tableWidget->currentRow();
    if(-1 == nCurrentRow)
    {
        return;
    }
    PicInfo[nCurrentRow].name = "";
    ui->m_tableWidget->setItem(nCurrentRow,1,new QTableWidgetItem(""));
    int i;
    for(i = 0; i<PicInfo.size(); i++)
    {
        if("" != PicInfo[i].name)
        {
            onItemchange(i);
            break;
        }
    }
    if(i >= PicInfo.size())
    {
        pScene->clear();
        pCopyItem = NULL;
    }
}

QString QImageShowDlg::GetPicName(QString sPath)
{
    QString sName = "";
    QStringList sList = sPath.split("/", QString::SkipEmptyParts);
    sName = sList.at(sList.size()-1);
    return sName;
}
void QImageShowDlg::confyButton()
{
    bool bFlag = false;
    for(int i = 0; i<PicInfo.size(); i++)
    {
        if("" != PicInfo[i].name)
        {
            bFlag = true;
            break;
        }
    }
    if(!bFlag)
    {
        QMessageBox msg(QMessageBox::Warning,VERSION_NAME,tr("没有选择图片!"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        msg.addButton(tr("确定"),QMessageBox::AcceptRole);
        msg.exec();
        return;
    }
    if(!onSavePicInfo(pCopyItem->m_SaveInfo))
    {
        return;
    }
    //保存闪现页面属性
    if(!pSecurityWight->Save())
    {
        return;
    }
    pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    pCopyItem->m_PicInfo = PicInfo;
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
    accept();
}

void QImageShowDlg::loadHelp()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_IMAGE);
}

bool QImageShowDlg::onSavePicInfo(INTOSAVE &picInfo)
{
    if(ui->m_SingleradioBtn->isChecked())
    {
        if(ui->groupBox_3->isChecked())
        {
            if(ui->m_BitradioBtn->isChecked())
            {
                if(! pwnd->IsAddressCheckRight(Bit_Address_Keyboard,tr("位地址"),ui->m_MonitorAddress,0))
                {
                    ui->m_MonitorAddress->setFocus();
                    return false;
                }
                picInfo.addr = Bit_Address_Keyboard;
            }
        }
    }
    else
    {
        if(ui->m_FixedradioBtn->isChecked())
        {
            if(! pwnd->IsAddressCheckRight(World_Address_Keyboard,tr("写入地址"),ui->m_MonitorAddress,1))
            {
                ui->m_MonitorAddress->setFocus();
                return false;
            }
            picInfo.addr = World_Address_Keyboard;
        }
        else if(ui->m_BitradioBtn->isChecked())
        {
            if(! pwnd->IsAddressCheckRight(Bit_Address_Keyboard,tr("位地址"),ui->m_MonitorAddress,0))
            {
                ui->m_MonitorAddress->setFocus();
                return false;
            }
            picInfo.addr = Bit_Address_Keyboard;
        }
    }

    if(ui->m_SingleradioBtn->isChecked())
    {
        picInfo.nFunType = 0;
    }
    else
    {
        picInfo.nFunType = 1;//多幅切换
    }
    picInfo.bUseFlicker = ui->groupBox_3->isChecked();//闪烁

    if(ui->m_TimeradioBtn->isChecked())
    {
        picInfo.nChangeCondition = 0;//时间切换
    }
    else if(ui->m_FixedradioBtn->isChecked())
    {
        picInfo.nChangeCondition = 2;//固定值切换
    }
    else
    {
        picInfo.nChangeCondition = 1;//位切换
    }
    //picInfo.nTimeInterval = ui->m_TimespBox->currentText().toInt();//时间间隔
    picInfo.mWatchAddr = ui->m_MonitorAddress->text();//监视地址
    picInfo.nStatusTotal = ui->m_StatuspBox->value();//状态总数
    if(0 == ui->m_comboBox->currentIndex())
    {
        picInfo.bIsLoopType = true;
    }
    else
    {
        picInfo.bIsLoopType = false;
    }
    //picInfo.nCmpFactor = ui->m_CmpspBox->value();
    //picInfo.nBackColor = ui->m_BackColorBtn->palette().background().color();
    picInfo.nTimeInterval = ui->m_TimespBox->value();
    return true;
}

void QImageShowDlg::on_Monitor_Address_EntryBtn_clicked()
{
    Keyboard Address_Keyboard;
    if(ui->m_FixedradioBtn->isChecked())
    {
        QString addrStr = sWorldAddress;
        AddressInputDialog addressintputdlg_writeaddress(Address_Keyboard,addrStr,1,this);
        if(addressintputdlg_writeaddress.exec())
        {
            sWorldAddress = Address_Keyboard.sShowAddr;
            ui->m_MonitorAddress->setText(Address_Keyboard.sShowAddr);
        }
        else
        {
            return;
        }
    }
    else if(ui->m_BitradioBtn->isChecked())
    {
        QString addrStr = sBitAddress;
        AddressInputDialog addressintputdlg_writeaddress(Address_Keyboard,addrStr,0,this);
        if(addressintputdlg_writeaddress.exec())
        {
            sBitAddress = Address_Keyboard.sShowAddr;
            ui->m_MonitorAddress->setText(Address_Keyboard.sShowAddr);
        }
        else
        {
            return;
        }
    }
    else
    {
        return;
    }
}

void QImageShowDlg::on_groupBox_3_clicked()
{
    if(!ui->groupBox_3->isChecked() && ui->m_SingleradioBtn->isChecked())
    {
        ui->m_TimespBox->setEnabled(false);
        ui->m_comboBox->setEnabled(false);
        ui->m_StatuspBox->setEnabled(false);
        ui->m_MonitorAddress->setEnabled(false);
    }
    else
    {
        ui->m_TimespBox->setEnabled(true);
        ui->m_comboBox->setEnabled(true);
        //ui->m_StatuspBox->setEnabled(true);
        ui->m_MonitorAddress->setEnabled(true);
        if(ui->m_TimeradioBtn->isChecked())
        {
            on_m_TimeradioBtn_clicked();
        }
        else if(ui->m_BitradioBtn->isChecked())
        {
            on_m_BitradioBtn_clicked(true);
        }
        else
        {
            on_m_FixedradioBtn_clicked(true);
        }
    }
}

void QImageShowDlg::on_m_BackColorBtn_clicked()
{
    //ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    //pwnd->OnAddColorDlg(ui->m_BackColorBtn ,colorPicker);
    //connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(onSetBackColor(const QColor &)));
}

void QImageShowDlg::onSetBackColor(const QColor &mColor)
{
    //ui->m_BackColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QImageShowDlg::onSetStatus(int maxnum)
{
    //ui->m_StatuscmbBox->clear();
    for(int i = 0; i<maxnum; i++)
    {
        QString str = QString("%1").arg(i);
        //ui->m_StatuscmbBox->addItem(str);
    }
}

void QImageShowDlg::on_m_StatuscmbBox_currentIndexChanged(int index)
{
    if(!bInitFlag ||(index >= ui->m_tableWidget->rowCount()) || (index < 0))
    {
        return;
    }
    onItemchange(index);
    ui->m_tableWidget->clearSelection();      //清楚所有选中项
    QTableWidgetItem *mItem;                     //设置指定项为选中状态
    mItem = ui->m_tableWidget->item(index,0);
    ui->m_tableWidget->setItemSelected(mItem,true);
}

void QImageShowDlg::on_m_CmpspBox_valueChanged(int )
{
}

void QImageShowDlg::on_btn_customValue_clicked()
{
    if(ui->m_StatuspBox->value() <= 0)
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("状态总数为0"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }
    QMultiStateGenelCunstomDlg *customDlg=new QMultiStateGenelCunstomDlg(this);

    values.clear();
    for(int i = 0;i < PicInfo.size(); i++)
    {
        values.append(PicInfo[i].nCmpFactor);
    }
    customDlg->setAllData(values,false);
    if(customDlg->exec() == QDialog::Accepted)
    {
        values = customDlg->allValues;
        for(int i = 0; i < values.size() && i < PicInfo.size(); i++)
        {
            PicInfo[i].nCmpFactor = values[i];
        }
    }
}

void QImageShowDlg::on_m_MonitorAddress_editingFinished()
{
    if(ui->m_FixedradioBtn->isChecked())
    {
        sWorldAddress = ui->m_MonitorAddress->text();
    }
    else if(ui->m_BitradioBtn->isChecked())
    {
        sBitAddress = ui->m_MonitorAddress->text();
    }
}

void QImageShowDlg::on_m_SelectLibpushBtn_clicked()
{
    onSelectpicbtn(1);
}

void QImageShowDlg::on_m_SelectPicpushBtn_clicked()
{
    onSelectpicbtn(0);
}
