#include "animationdlg.h"
#include "ui_animationdlg.h"
#include "Frame/mainwindow.h"
#include "Frame/DrawDlg/OpenLibrary.h"
#include <QFontDatabase>
#include "Frame/ThingDlg/qmultistategenelcunstomdlg.h"
#include <qfile.h>

#define STATUS_NUM      1  //初始状态数量
extern MainWindow *pwnd;
AnimationDlg::AnimationDlg(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnimationDlg)
{
    bSave = true;
    bInitflag = false;
    oId = -1;
    m_Text.clear();
    pStatusItem = NULL;
    QGraphicsItem *Item;
    pAreaWidget = new AreaWidget;
    pScatWidget = new ScatterWidget;
    pSecurityWight = new SecurityWidget;
    pSecurityWight->setTouchGroupEnabled(false);

    ui->setupUi(this);
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    ui->tabWidget->addTab(pSecurityWight,tr("权限设置"));
    ui->m_fontCbBox->addItems(QFontDatabase().families(QFontDatabase::Any));
    pwnd->InitFontSize(ui->m_fontSizecbBox);//初始化字体大小下拉列表框

    ui->m_vLayout->addWidget(pScatWidget);
    cWidget = pScatWidget;

    pScene = new QGraphicsScene(this);//建场景
    ui->MainView->setScene(pScene);
    ui->m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->m_cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->m_helpBtn, SIGNAL(clicked()), this, SLOT(loadHelp()));
    connect(ui->m_okBtn, SIGNAL(clicked()), this, SLOT(confyButton()));
    //connect(pScatWidget, SIGNAL(onResetpoint(int,QPointF)), this, SLOT(onResetpoint(int,QPointF)));

    ui->Monitor_Address->setText("LW0");

    if(pItem)
    {
        Item = dynamic_cast<AnimationItem *> (pItem)->Clone();
        pCopyItem = dynamic_cast<AnimationItem *> (Item);
        InitAllProperty(pCopyItem);
        pOldItem = pItem;
    }
    else
    {
        InitAllProperty(NULL);
        pCopyItem = new AnimationItem;
        pOldItem = NULL;
    }
    ui->m_okBtn->setFocus();
}

AnimationDlg::~AnimationDlg()
{
    delete ui;
}

void AnimationDlg::InitAllProperty(AnimationItem *pItem)
{
    ui->m_tableWidget->setColumnWidth(0,40);     //设置列宽
    ui->m_tableWidget->setColumnWidth(1,220);
    ui->m_tableWidget->verticalHeader()->setVisible(false);

    if(pItem)
    {
        oId = pItem->id();
        qDebug() <<"id : " <<oId;
        ui->spinBox_3->setValue(oId);
        pSecurityWight->init(pItem);

        AnInfo aninfo;
        pItem->onGetAnimatInfo(aninfo);
        ui->m_LocusTypecmBox->setCurrentIndex(aninfo.nTrackType);//散点轨迹
        if(1 == aninfo.nTrackType)
        {
            pAreaWidget->Init(pItem);
            pScatWidget->Init(NULL);
        }
        else
        {
            pScatWidget->Init(pItem);
            pAreaWidget->Init(NULL);
        }
        on_m_LocusTypecmBox_currentIndexChanged(aninfo.nTrackType);

        //状态页面
        ui->m_StatusTotalSpBox->setValue(aninfo.nStateTotal);//状态总数
        ui->m_ConditionCmBox->setCurrentIndex(aninfo.nChangeCondition);//状态切换方式 时间 固定值
        ui->m_CycleCmBox->setCurrentIndex(aninfo.nChangeType);//循环方式
        ui->m_TimespinBox->setValue(aninfo.nChangeTimeinterval);//时间
        ui->Monitor_Address->setText(aninfo.mChangeCtrlAddr.sShowAddr);

        on_m_ConditionCmBox_currentIndexChanged(aninfo.nChangeCondition);

        ui->m_StartStatusCmBox->setCurrentIndex(aninfo.nInitState);//初始状态

        m_Text = aninfo.Text;//文本



        PicInfo = aninfo.PicInfo;//图片
        ui->m_tableWidget->setRowCount(aninfo.nStateTotal);
        on_m_StatusTotalSpBox_valueChanged(aninfo.nStateTotal);
        //ui->m_EnableTextCkBox->setChecked(aninfo.bEnableText);
        //on_m_EnableTextCkBox_clicked(aninfo.bEnableText);

        //ui->checkBox_2->setChecked(aninfo.bEnablePic);
        //on_checkBox_2_clicked(aninfo.bEnablePic);//外形选择
        //onPicBackColor(pwnd->StringTOColor(aninfo.sPicBackColor));
        //ui->m_tableWidget->setRowCount(PicInfo.size());
        values.resize(PicInfo.size());
        for(int i = 0; i< PicInfo.size(); i++)
        {
            values[i] = PicInfo[i].nCmpFactor;
            QString str = QString("%1").arg(i);
            ui->m_tableWidget->setItem(i,0,new QTableWidgetItem(str));
            ui->m_tableWidget->setItem(i,1,new QTableWidgetItem(PicInfo[i].name));
        }

        int nRow = pItem->onGetCurrentNum();
        ui->m_StatusTextCmBox->setCurrentIndex(nRow);
        on_m_StatusTextCmBox_currentIndexChanged(nRow);
        //ui->spinBox_3->setValue(pItem->id());
    }
    else
    {
        ui->spinBox_3->setValue(pwnd->getNewId());
        pAreaWidget->Init(NULL);
        pScatWidget->Init(NULL);

        on_m_ConditionCmBox_currentIndexChanged(0);

        onPicBackColor(QColor(255,0,0));
        //设置状态数量
        ui->m_StatusTotalSpBox->setValue(STATUS_NUM);
        on_m_StatusTotalSpBox_valueChanged(0);
        on_m_StatusTextCmBox_currentIndexChanged(0);
        ui->m_tableWidget->setRowCount(STATUS_NUM);
        PicInfo.resize(STATUS_NUM);
        for(int i = 0; i< STATUS_NUM; i++)
        {
            QString str = QString("%1").arg(i);
            ui->m_tableWidget->setItem(i,0,new QTableWidgetItem(str));
        }
        onItemchange(0);
    }
    bInitflag = true;
}


void AnimationDlg::on_m_LocusTypecmBox_currentIndexChanged(int index)
{
    if(0 == index)
    {
        if(cWidget)
        {
            ui->m_vLayout->removeWidget(cWidget);
            cWidget->hide();
            ui->m_vLayout->addWidget(pScatWidget);
            cWidget = pScatWidget;
            cWidget->show();
        }
    }
    else if(1 == index)
    {
        if(cWidget)
        {
            ui->m_vLayout->removeWidget(cWidget);
            cWidget->hide();
            ui->m_vLayout->addWidget(pAreaWidget);
            cWidget = pAreaWidget;
            cWidget->show();
        }
    }
}

void AnimationDlg::on_m_BackColorBtn_clicked()
{
    //ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    //pwnd->OnAddColorDlg(ui->m_BackColorBtn ,colorPicker);
    //connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(onPicBackColor(const QColor &)));
}

void AnimationDlg::on_m_deletepicbtn_clicked()
{
    QModelIndex index;
    int nCurrentRow = ui->m_tableWidget->currentRow();
    if(-1 == nCurrentRow)
    {
        return;
    }
    if("" == PicInfo[nCurrentRow].name)
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
        pStatusItem = NULL;
    }
}

void AnimationDlg::onSelectpicbtn(int nType)
{
    QPointF pos(0,0);
    if(pStatusItem)
        pos = pStatusItem->sceneBoundingRect().topLeft();
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
            PicInfo[nCurrentRow + i].sPath = filename.at(i);
            PicInfo[nCurrentRow + i].name = GetPicName(filename.at(i));
            PicInfo[nCurrentRow + i].bIspic = PIC;
            //PicInfo[nCurrentRow + i].num = nCurrentRow + i;
            ui->m_tableWidget->setItem(nCurrentRow+i,1,new QTableWidgetItem(PicInfo[nCurrentRow + i].name));

        }
//        pScene->clear();
//        pScene->addPixmap(picture.scaled(100,86)); //newimage
//        pScene->update();

        QPixmapItem *PicItem = new QPixmapItem(picture,QSize(100,86));

        pStatusItem = new AnimationItem;
        pStatusItem->onSetCurrentNum(nCurrentRow);//记录当前显示的item下标
        pStatusItem->addToGroup(PicItem);
        onAddText(nCurrentRow);
        pScene->clear();
        pScene->addItem(pStatusItem);
        pBaseItem = new QGroupItem(pCopyItem);
        pBaseItem->SetWidth(100);
        pBaseItem->SetHeigth(100);
        QPointF newpos = pStatusItem->boundingRect().topLeft();
        pStatusItem->setPos(pos - newpos);

    }
    else if(1 == nType) //来自图库
    {
        QString sname;

        OpenLibrary *pDlg = new OpenLibrary(this);
        if(pDlg->exec() == QDialog::Accepted)
        {
            pStatusItem = onCopyItem(pDlg->pCopyItem);
            int type = pStatusItem->data(GROUP_TYPE_KEY).toInt();
            if(LIBRARY_LIB_GROUP == type)
            {
                sname = pStatusItem->data(GROUP_NAME_KEY).toString();
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

                PicInfo[nCurrentIndex].sPath = pStatusItem->data(GROUP_NAME_KEY).toString();
                pStatusItem->onSetCurrentNum(nCurrentIndex);
                onAddText(nCurrentIndex);
                pScene->clear();
                QPointF newpos = pStatusItem->boundingRect().topLeft();
                pScene->addItem(pStatusItem);
                pBaseItem = new QGroupItem(pStatusItem);
                pBaseItem->SetWidth(100);
                pBaseItem->SetHeigth(100);
                pStatusItem->setPos(pos - newpos);
            }
            else if(LIBRARY_PIXMAP_GROUP == type)
            {
                int nCurrentRow = ui->m_tableWidget->currentRow();
                if(-1 == nCurrentRow)
                {
                    nCurrentRow = 0;
                }
                QString path = pStatusItem->data(GROUP_NAME_KEY).toString();
                QPixmap picture = QPixmap(path);
                if (!picture)
                {
                   return ;
                }

                PicInfo[nCurrentRow].sPath = path;
                PicInfo[nCurrentRow].name = GetPicName(path);
                PicInfo[nCurrentRow].bIspic = USERDEFINE;
                ui->m_tableWidget->setItem(nCurrentRow,1,new QTableWidgetItem(PicInfo[nCurrentRow].name));

                QPixmapItem *PicItem = new QPixmapItem(picture,QSize(100,86));

                pStatusItem = new AnimationItem;
                pStatusItem->onSetCurrentNum(nCurrentRow);//记录当前显示的item下标
                pStatusItem->addToGroup(PicItem);
                onAddText(nCurrentRow);
                pScene->clear();
                pScene->addItem(pStatusItem);
                pBaseItem = new QGroupItem(pCopyItem);
                pBaseItem->SetWidth(100);
                pBaseItem->SetHeigth(100);
                QPointF newpos = pStatusItem->boundingRect().topLeft();
                pStatusItem->setPos(pos - newpos);
            }
        }
        pDlg->deleteLater();
        pDlg = NULL;
    }
}

void AnimationDlg::on_checkBox_2_clicked(bool checked)//外形选择
{
    if(checked)
    {
        ui->m_tableWidget->show();
        ui->groupBox_10->show();
    }
    else
    {
        ui->m_tableWidget->hide();
        ui->groupBox_10->hide();
    }
}

void AnimationDlg::on_checkBox_clicked()
{

}

AnimationItem *AnimationDlg::onCopyItem(QGraphicsItem *pItem)
{
    AnimationItem *newItem = new AnimationItem;
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

QString AnimationDlg::GetPicName(QString sPath)
{
    QString sName = "";
    QStringList sList = sPath.split("/", QString::SkipEmptyParts);
    sName = sList.at(sList.size()-1);
    return sName;
}

void AnimationDlg::on_m_DrawpushBtn_clicked()
{
    //保存闪现页面属性
    if(!pSecurityWight->Save())
    {
        return;
    }
    pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));

    if(pStatusItem)
    {
        pStatusItem->setData(GROUP_NAME_KEY,QVariant("mMain"));
        pCopyItem->addToGroup(pStatusItem);
    }
    if(pCopyItem)
    {
        pwnd->pOldItem = pCopyItem;
    }
    onAnimatInfosave(m_AnimatInfo);//保存属性
    if(1 == ui->m_LocusTypecmBox->currentIndex())
    {
        if(!pAreaWidget->onAnimatInfosave(m_AnimatInfo))
        {
            return;
        }
    }
    else
    {
        if(!pScatWidget->onAnimatInfosave(m_AnimatInfo))
        {
            return;
        }
    }
    if(pStatusItem)//保存当前图片下标
    {
        int nRow = pStatusItem->onGetCurrentNum();
        pCopyItem->onSetCurrentNum(nRow);
    }
    m_AnimatInfo.stMoveInfo.clear();//重新录制轨迹点 清楚轨迹点预设值
    pCopyItem->onSaveAnimatInfo(m_AnimatInfo);

    pCopyItem->setId(ui->spinBox_3->value());

    if(ui->spinBox_3->value() != oId && !pwnd->insertId(ui->spinBox_3->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox_3->setFocus();
        return ;
    }

    pwnd->OnCreateAnimation();
    pCopyItem = NULL;
    pStatusItem = NULL;
    this->accept();
}

bool AnimationDlg::onAnimatInfosave(AnInfo &aninfo)
{
    aninfo.nTrackType = ui->m_LocusTypecmBox->currentIndex();//散点轨迹

    //状态页面
    if(1 == ui->m_ConditionCmBox->currentIndex())
    {
        if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("状态控制地址"),ui->Monitor_Address,1))
        {
            ui->Monitor_Address->setFocus();
            return false;
        }
        else
        {
            aninfo.mChangeCtrlAddr = Monitor_Address_Keyboard;
        }
    }
    aninfo.sChangeCtrlAddr = ui->Monitor_Address->text();
    aninfo.nStateTotal = ui->m_StatusTotalSpBox->value();//状态总数
    aninfo.nChangeCondition =  ui->m_ConditionCmBox->currentIndex();//状态切换方式 时间 固定值
    aninfo.nChangeType = ui->m_CycleCmBox->currentIndex();//循环方式
    aninfo.nChangeTimeinterval = ui->m_TimespinBox->value();//时间
    aninfo.nInitState = ui->m_StartStatusCmBox->currentIndex();//初始状态

    for(int i = 0; i < values.size() && i < PicInfo.size(); i++)
    {
        PicInfo[i].nCmpFactor = values[i];
        PicInfo[i].nStatusId = i;
    }

    //文本
    //aninfo.bEnableText = ui->m_EnableTextCkBox->isChecked();
    aninfo.Text = m_Text;

    //图片
    //aninfo.bEnablePic = ui->checkBox_2->isChecked();
    //aninfo.sPicBackColor = pwnd->ColorTOString(ui->m_BackColorBtn->palette().background().color());
    aninfo.PicInfo = PicInfo;
    return true;
}

void AnimationDlg::confyButton()
{
    if(!onAnimatInfosave(m_AnimatInfo))
    {
        return;
    }
    if(1 == ui->m_LocusTypecmBox->currentIndex())
    {
        if(!pAreaWidget->onAnimatInfosave(m_AnimatInfo))
        {
            return;
        }
    }
    else
    {
        if(!pScatWidget->onAnimatInfosave(m_AnimatInfo))
        {
            return;
        }

        //pCopyItem->TrackInfo = pScatWidget->m_Tinfo;
    }

    //保存闪现页面属性
    if(!pSecurityWight->Save())
    {
        return;
    }
    pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));

    pCopyItem->onSaveAnimatInfo(m_AnimatInfo);

    if(m_AnimatInfo.nTrackPointTotal < 1)
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("没有录制轨迹点"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }
    if(pStatusItem)
    {
        int nRow = pStatusItem->onGetCurrentNum();
        pCopyItem->onSetCurrentNum(nRow);
    }
    pCopyItem->setId(ui->spinBox_3->value());
    onReplaceItem();
    if(ui->spinBox_3->value() != oId && !pwnd->insertId(ui->spinBox_3->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox_3->setFocus();
        return ;
    }
    accept();
}

void AnimationDlg::loadHelp()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_ANIMATION);
}

void AnimationDlg::on_comboBox_5_currentIndexChanged(int index)
{
    if(0 == index)
    {
        ui->m_Startlabel->setEnabled(true);
        ui->m_StartStatusCmBox->setEnabled(true);
        ui->btn_customValue->setEnabled(false);
        ui->label_25->setEnabled(false);
        ui->Monitor_Address->setEnabled(false);
        ui->Monitor_Address_EntryBtn->setEnabled(false);
    }
    else if(1 == index)
    {
        ui->m_Startlabel->setEnabled(false);
        ui->m_StartStatusCmBox->setEnabled(false);
        ui->btn_customValue->setEnabled(true);
        ui->label_25->setEnabled(true);
        ui->Monitor_Address->setEnabled(true);
        ui->Monitor_Address_EntryBtn->setEnabled(true);
    }
}

void AnimationDlg::on_m_StatusTotalSpBox_valueChanged(int index)
{
    int nValue = ui->m_StatusTotalSpBox->value();
    int nSize = m_Text.size();
    if(nValue >= 0)
    {
        m_Text.resize(nValue);//设置文本数组大小
        if(nSize < nValue)
        {
            for(int i = nSize; i < nValue; i++)
            {
                m_Text[i].bValid = true;
                m_Text[i].nStatusId = i;
                int iFont = ui->m_fontCbBox->findText(tr("Droid Sans Fallback"));
                if(iFont >= 0)
                {
                    m_Text[i].sFontIndex = iFont;
                }
                else
                {
                    m_Text[i].sFontIndex = ui->m_fontCbBox->findText(tr("System"));
                }
                //m_Text[i].sFontIndex = ui->m_fontCbBox->findText(tr("Droid Sans Fallback"));
                m_Text[i].sFontFamily = ui->m_fontCbBox->itemText(m_Text[i].sFontIndex);
                m_Text[i].nSize = 5;
                QColor mColor(0,0,0);
                m_Text[i].nColor = pwnd->ColorTOString(mColor);
                QColor mBackColor(255,0,0);
                m_Text[i].nBColor = pwnd->ColorTOString(mBackColor);
                m_Text[i].sText = tr("状态");
                m_Text[i].sText = m_Text[i].sText + QString::number(i);
                m_Text[i].nStyle = 0;
                m_Text[i].eAlign = Cpoint;
            }

        }
        onSetStatus(nValue);
        //设置图片数量
        onTableNumChange(nValue);
    }
}

void AnimationDlg::onSetStatus(int maxnum)//预设固定值状态下拉列表
{
    ui->m_StartStatusCmBox->clear();
    ui->m_StatusTextCmBox->clear();
    values.resize(maxnum);
    for(int i = 0; i<maxnum; i++)
    {
        values[i] = i;
        QString str = QString("%1").arg(i);
        ui->m_StartStatusCmBox->addItem(str);
        ui->m_StatusTextCmBox->addItem(str);
    }
}

void AnimationDlg::onSaveTextInfo()//保存文本属性
{
    int index  = ui->m_StatusTextCmBox->currentIndex();
    if(index < m_Text.size() && index >= 0)
    {
        m_Text[index].bValid = true;
        m_Text[index].nStatusId = index;
        m_Text[index].nSize = ui->m_fontSizecbBox->currentIndex();
        if(0 == ui->m_AligmentCbBox->currentIndex())
        {
            m_Text[index].eAlign = Cpoint;
        }
        else if(1 == ui->m_AligmentCbBox->currentIndex())
        {
            m_Text[index].eAlign = Rpoint;
        }
        else
        {
            m_Text[index].eAlign = Lpoint;
        }
        m_Text[index].sFontFamily = ui->m_fontCbBox->currentText();
        m_Text[index].sFontIndex = ui->m_fontCbBox->currentIndex();
        QString mColor;
        mColor = pwnd->ColorTOString(ui->m_TextColorpushBtn->palette().background().color());
        m_Text[index].nColor = mColor;
        //mColor = pwnd->ColorTOString(ui->m_BackColorpushBtn->palette().background().color());
        m_Text[index].nBColor = mColor;
        //m_Text[index].sText = ui->m_TextlineEdit->text();
        m_Text[index].sText = ui->m_TextlineEdit->toPlainText();


        if(ui->m_OrdinaryckBox->isChecked())
        {
            m_Text[index].nStyle = 0;
        }
        else
        {
            m_Text[index].nStyle = 0;
            short int nflag = 0;
            if(ui->m_BoldckBox->isChecked())
            {
                nflag = 1;//粗体
                m_Text[index].nStyle = (m_Text[index].nStyle)|nflag;
            }
            if(ui->m_ItalicckBox->isChecked())
            {
                nflag = 2;//斜体
                m_Text[index].nStyle = (m_Text[index].nStyle)|nflag;
            }
            if(ui->m_UnderlineckBox->isChecked())
            {
                nflag = 8;//下划线
                m_Text[index].nStyle = (m_Text[index].nStyle)|nflag;
            }
        }
    }
}

void AnimationDlg::on_m_OrdinaryckBox_clicked(bool checked)
{
    if(checked)
    {
        ui->m_BoldckBox->setChecked(false);
        ui->m_ItalicckBox->setChecked(false);
        ui->m_UnderlineckBox->setChecked(false);
    }
    on_m_SaveTextpushBtn_clicked();
}

void AnimationDlg::on_m_BoldckBox_clicked(bool checked)
{
    if(checked)
    {
        ui->m_OrdinaryckBox->setChecked(false);
    }
    on_m_SaveTextpushBtn_clicked();
}

void AnimationDlg::on_m_ItalicckBox_clicked(bool checked)
{
    if(checked)
    {
        ui->m_OrdinaryckBox->setChecked(false);
    }
    on_m_SaveTextpushBtn_clicked();
}

void AnimationDlg::on_m_UnderlineckBox_clicked(bool checked)
{
    if(checked)
    {
        ui->m_OrdinaryckBox->setChecked(false);
    }
    on_m_SaveTextpushBtn_clicked();
}

void AnimationDlg::on_m_fontSizecbBox_currentIndexChanged(int index)
{
    on_m_SaveTextpushBtn_clicked();
}

void AnimationDlg::on_m_AligmentCbBox_currentIndexChanged(int index)
{
    on_m_SaveTextpushBtn_clicked();
}

void AnimationDlg::on_m_fontCbBox_currentIndexChanged(int index)
{
    on_m_SaveTextpushBtn_clicked();
}

void AnimationDlg::onPicBackColor(const QColor &mColor)
{
    //ui->m_BackColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void AnimationDlg::onSetTextColor(const QColor &mColor)
{
    ui->m_TextColorpushBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    on_m_SaveTextpushBtn_clicked();
}

void AnimationDlg::on_m_TextColorpushBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_TextColorpushBtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(onSetTextColor(const QColor &)));
}

void AnimationDlg::on_m_StatusTextCmBox_currentIndexChanged(int index)
{
    bSave = false;
    if(index != ui->m_tableWidget->currentRow() && index >= 0 && index < ui->m_tableWidget->rowCount())
    {
        ui->m_tableWidget->setCurrentCell(index,1);
        onItemchange(index);
    }
    if(index >= 0 && index < m_Text.size())
    {
        if(m_Text[index].bValid)
        {
            ui->m_fontSizecbBox->setCurrentIndex(m_Text[index].nSize);
            if(Cpoint == m_Text[index].eAlign)
            {
                ui->m_AligmentCbBox->setCurrentIndex(0);
            }
            else if(Rpoint == m_Text[index].eAlign)
            {
                ui->m_AligmentCbBox->setCurrentIndex(1);
            }
            else
            {
                ui->m_AligmentCbBox->setCurrentIndex(2);
            }
            ui->m_fontCbBox->setCurrentIndex(m_Text[index].sFontIndex);
            QColor mColor;
            mColor = pwnd->StringTOColor(m_Text[index].nColor);
            ui->m_TextColorpushBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));

            mColor = pwnd->StringTOColor(m_Text[index].nBColor);
            //ui->m_BackColorpushBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
            ui->m_TextlineEdit->setPlainText(m_Text[index].sText);

            if(0 == m_Text[index].nStyle)
            {
                ui->m_OrdinaryckBox->setChecked(true);
                on_m_OrdinaryckBox_clicked(true);
            }
            else
            {
                ui->m_OrdinaryckBox->setChecked(false);
                if((1&(m_Text[index].nStyle)))
                {
                    ui->m_BoldckBox->setChecked(true);
                }
                else
                {
                    ui->m_BoldckBox->setChecked(false);
                }
                if((2&(m_Text[index].nStyle)))
                {
                    ui->m_ItalicckBox->setChecked(true);
                }
                else
                {
                    ui->m_ItalicckBox->setChecked(false);
                }
                if((8&(m_Text[index].nStyle)))
                {
                    ui->m_UnderlineckBox->setChecked(true);
                }
                else
                {
                    ui->m_UnderlineckBox->setChecked(false);
                }
            }
        }
    }
    bSave = true;
}

void AnimationDlg::on_edit_text_textChanged()
{
    on_m_SaveTextpushBtn_clicked();
}

void AnimationDlg::onInitText()
{
    ui->m_fontSizecbBox->setCurrentIndex(0);
    ui->m_AligmentCbBox->setCurrentIndex(0);
    ui->m_fontCbBox->setCurrentIndex(0);
    QColor mColor(0,0,0);
    ui->m_TextColorpushBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));

    QColor mBackColor(255,0,0);
    //ui->m_BackColorpushBtn->setStyleSheet(QString("background:%1").arg(mBackColor.name()));
    ui->m_TextlineEdit->setPlainText(tr("输入文本"));
    ui->m_OrdinaryckBox->setChecked(false);
    ui->m_UnderlineckBox->setChecked(false);
    ui->m_ItalicckBox->setChecked(false);
    ui->m_BoldckBox->setChecked(false);
}

void AnimationDlg::on_m_SaveTextpushBtn_clicked()
{
    if(!bInitflag || !bSave)
    {
        return;
    }
    onSaveTextInfo();
    OnSetTextProperty();
}

void AnimationDlg::on_m_tableWidget_clicked(QModelIndex index)
{
    int nRow = ui->m_tableWidget->currentRow();
    onItemchange(nRow);
    if(nRow != ui->m_StatusTextCmBox->currentIndex() && nRow < ui->m_StatusTextCmBox->count())
    {
        ui->m_StatusTextCmBox->setCurrentIndex(nRow);
    }
}

void AnimationDlg::onItemchange(int nCurrentRow)
{
    int nrow = nCurrentRow;
    if(nrow > PicInfo.size() || nrow < 0 || "" == PicInfo[nrow].name)
    {
        return;
    }
    QPointF oldpos(0,0);
    if(pStatusItem)
    {
       oldpos =  pStatusItem->sceneBoundingRect().topLeft();
    }
    if(LIBRARY == PicInfo[nrow].bIspic || USERDEFINE == PicInfo[nrow].bIspic)
    {
        if("" != PicInfo[nrow].name)
        {
            pScene->clear();
            pStatusItem = onGetItemFromFile(PicInfo[nrow].sPath,PicInfo[nrow].bIspic);
            if(!pStatusItem)
            {
                return;
            }
            else
            {
                pStatusItem->onSetCurrentNum(nrow);
                onAddText(nrow);
                QPointF newpos = pStatusItem->boundingRect().topLeft();
                pScene->addItem(pStatusItem);
                pBaseItem = new QGroupItem(pStatusItem);
                pBaseItem->SetWidth(100);
                pBaseItem->SetHeigth(100);
                pStatusItem->setPos(oldpos - newpos);
                //ui->m_SysImageradioBtn->setChecked(true);
            }
        }
    }
    else
    {
        QPixmap picture = QPixmap(PicInfo[nrow].sPath);
        //pScene->addPixmap(picture.scaled(QSize(100,86)));
        QPixmapItem *PicItem = new QPixmapItem(picture,QSize(100,86));
        pStatusItem = new AnimationItem;
        pStatusItem->onSetCurrentNum(nrow);
        pStatusItem->addToGroup(PicItem);
        onAddText(nrow);
        pScene->clear();
        pScene->addItem(pStatusItem);
        QPointF newpos = pStatusItem->boundingRect().topLeft();
        pBaseItem = new QGroupItem(pStatusItem);
        pBaseItem->SetWidth(100);
        pBaseItem->SetHeigth(100);
        pStatusItem->setPos(oldpos - newpos);
        //ui->m_FileImageradioBtn->setChecked(true);
    }
    OnSetTextProperty();
}

AnimationItem *AnimationDlg::onGetItemFromFile(QString sPath,EITEM_TYPE eType)
{
    QList <QGraphicsItem*> listItem;
    QStringList str = sPath.split('-');
    if(str.isEmpty())
    {
        return NULL;
    }
    AnimationItem *pNewItem = NULL;
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

        pNewItem = new AnimationItem;
        pNewItem->addToGroup(PicItem);
    }
    return pNewItem;
}

void AnimationDlg::onTableNumChange(int nTotalRow)
{
    int nCurrentRow = ui->m_tableWidget->rowCount();
    PicInfo.resize(nTotalRow);//该数组与列表行数保持一致
    if(nCurrentRow < nTotalRow)
    {
        for(int i = nCurrentRow; i < nTotalRow; i++)
        {
            PicInfo[i].name = "default.png";
            PicInfo[i].bIspic = PIC;
            PicInfo[i].sPath = ":/btn/images/AnimationDefault.png";
            PicInfo[i].nStatusId = i;
            ui->m_tableWidget->insertRow(i);
            QString str = QString("%1").arg(i);
            ui->m_tableWidget->setItem(i,0,new QTableWidgetItem(str));
            ui->m_tableWidget->setItem(i,1,new QTableWidgetItem(PicInfo[i].name));
            ui->m_tableWidget->setRowHeight(i,25);
        }
    }
    else
    {
        for(int i = nCurrentRow - 1; i >= nTotalRow; i--)
        {
            ui->m_tableWidget->removeRow(i);
        }
    }
}

void AnimationDlg::onAddText(int nRow)
{
    if(nRow > m_Text.size() || nRow < 0 || !pStatusItem)
    {
        return;
    }
    QString sText = "";
    if(m_Text[nRow].bValid)
    {
        sText = m_Text[nRow].sText;
    }
    else
    {
        sText = QString("%1").arg(nRow);
    }
    QRectF rect = pStatusItem->boundingRect();
    QSimpleTextItem *pText = new QSimpleTextItem(rect,sText);
    pText->SetName("mText");
    pText->SetRectOutLine(false);
    pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pStatusItem->addToGroup(pText);
    pStatusItem->textItem = pText;

    OnSetTextProperty();
}

void AnimationDlg::OnSetTextProperty()
{
    if(!pStatusItem)
    {
        return;
    }
    int nRow = pStatusItem->onGetCurrentNum();
    if(nRow > m_Text.size() || nRow < 0 || !m_Text[nRow].bValid)
    {
        return;
    }

    QColor mColor = pwnd->StringTOColor(m_Text[nRow].nColor);
    pStatusItem->SetTextColor(mColor);

    pStatusItem->SetText(m_Text[nRow].sText);

    pStatusItem->SetFontSize(m_Text[nRow].nSize + 5);
    pStatusItem->SetFontName(m_Text[nRow].sFontFamily);
    if(Lpoint == m_Text[nRow].eAlign)
    {
        pStatusItem->SetTextAlign(4);
    }
    else if(Cpoint == m_Text[nRow].eAlign)
    {
        pStatusItem->SetTextAlign(5);
    }
    else if(Rpoint == m_Text[nRow].eAlign)
    {
        pStatusItem->SetTextAlign(6);
    }

    pStatusItem->SetBold(false);
    pStatusItem->SetItalic(false);
    pStatusItem->SetUnderLine(false);

    if((1&(m_Text[nRow].nStyle)))
    {
        pStatusItem->SetBold(true);
    }
    if((2&(m_Text[nRow].nStyle)))
    {
        pStatusItem->SetItalic(true);
    }
    if((8&(m_Text[nRow].nStyle)))
    {
        pStatusItem->SetUnderLine(true);
    }
}

void AnimationDlg::onReplaceItem()
{
    if(!pCopyItem || !pStatusItem)
    {
        return;
    }
    DrawItemToScene GroupFunction;
    QList<QGraphicsItem *> itemList;
    itemList = pCopyItem->childItems();
    foreach(QGraphicsItem *pItem,itemList)
    {
        if("mMain" == pItem->data(GROUP_NAME_KEY).toString())
        {
            QVector<TrackPointInfo> TrackInfo;//轨迹点列表
            pCopyItem->onGetTrackInfo(TrackInfo);
            if(TrackInfo.size() <= 0)
            {
                return;
            }

            QGroupItem *pBaseItem   = NULL;
            QPointF pos = pItem->sceneBoundingRect().topLeft();
            //QPointF newpos = pStatusItem->boundingRect().topLeft();

            QItemGroup *pItemGoup = new QItemGroup;
            foreach(QGraphicsItem *pChildItem,pStatusItem->childItems())
            {
                QGraphicsItem *item;
                GroupFunction.CopyItem(&item,pChildItem);
                pItemGoup->addToGroup(item);
            }
            pItemGoup->setData(GROUP_NAME_KEY,QVariant("mMain"));
            //pItemGoup->setData(GROUP_TYPE_KEY,pItem->data(GROUP_TYPE_KEY).toInt());
            QPointF newpos = pItemGoup->boundingRect().topLeft();


            //pStatusItem->setData(GROUP_NAME_KEY,QVariant("mMain"));

            pBaseItem = new QGroupItem(pItemGoup);
            pBaseItem->SetHeigth(pItem->sceneBoundingRect().height());
            pBaseItem->SetWidth(pItem->sceneBoundingRect().width());
            pItemGoup->setPos(pos.x() - newpos.x(),pos.y() - newpos.y());
            pCopyItem->removeFromGroup(pItem);
            pCopyItem->addToGroup(pItemGoup);
            break;
        }
    }
}

void AnimationDlg::on_m_TextlineEdit_lostFocus()
{
    //on_m_SaveTextpushBtn_clicked();
}

void AnimationDlg::on_m_EnableTextCkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->groupBox_7->show();
        ui->groupBox_8->show();
        ui->groupBox_9->show();
        ui->label_10->show();
        ui->m_TextlineEdit->show();
    }
    else
    {
        ui->groupBox_7->hide();
        ui->groupBox_8->hide();
        ui->groupBox_9->hide();
        ui->label_10->hide();
        ui->m_TextlineEdit->hide();
    }
}

void AnimationDlg::on_m_ConditionCmBox_currentIndexChanged(int index)
{
    if(0 == index)
    {
        ui->m_Timelabel->setEnabled(true);
        ui->m_TimespinBox->setEnabled(true);
        ui->m_Timemlabel->setEnabled(true);
        ui->m_Startlabel->setEnabled(true);
        ui->m_StartStatusCmBox->setEnabled(true);
        ui->btn_customValue->setEnabled(false);
        ui->label_25->setEnabled(false);
        ui->Monitor_Address->setEnabled(false);
        ui->Monitor_Address_EntryBtn->setEnabled(false);
    }
    else if(1 == index)
    {
        ui->m_Timelabel->setEnabled(false);
        ui->m_TimespinBox->setEnabled(false);
        ui->m_Timemlabel->setEnabled(false);
        ui->m_Startlabel->setEnabled(false);
        ui->m_StartStatusCmBox->setEnabled(false);
        ui->btn_customValue->setEnabled(true);
        ui->label_25->setEnabled(true);
        ui->Monitor_Address->setEnabled(true);
        ui->Monitor_Address_EntryBtn->setEnabled(true);
    }
}

void AnimationDlg::onResetpoint(int index,QPointF pos)//重新设置轨迹点坐标
{
    if(!pCopyItem)
    {
        return;
    }
    pCopyItem->onSetTrackInfo(pScatWidget->m_Tinfo);
    QList <QGraphicsItem *> items = pCopyItem->childItems();
    QGraphicsItem *pBackItem = NULL;
    QString sName;
    int ikey;
    foreach(QGraphicsItem *pItem,items)
    {
        sName = pItem->data(GROUP_NAME_KEY).toString();
        ikey = pItem->type(); //new
        if(sName == tr("mMain"))
        {
            pBackItem = pItem;
        }
        else
        {
            int index = sName.toInt();
            if(index >= pScatWidget->m_Tinfo.size() || index > 0)
            {
                return;
            }
            pos.setX(pScatWidget->m_Tinfo[index].nXPos);
            pos.setY(pScatWidget->m_Tinfo[index].nYPos);

            if(ikey == SAM_DRAW_OBJECT_ELIPSE)
            {
                pItem->setPos(pos - pItem->boundingRect().topLeft());
                if(sName.toInt() == 0 && pBackItem)
                {
                    pos.setX(pos.x() + 5);
                    QGroupItem *pBaseItem = new QGroupItem(pBackItem);
                    pBaseItem->SetWidth(pBackItem->boundingRect().width());
                    pBaseItem->SetHeigth(pBackItem->boundingRect().height());
                    pBackItem->setPos(pos - pBackItem->boundingRect().topLeft());
                }
            }
            if(ikey == SAM_DRAW_OBJECT_TEXT)
            {
                pos.setY(pos.y() + 5);
                pItem->setPos(pos - pItem->boundingRect().topLeft());
            }

        }

//        if(QString::number(index) == sName)
//        {
//            if(ikey == SAM_DRAW_OBJECT_ELIPSE)
//            {
//                pItem->setPos(pos - pItem->boundingRect().topLeft());
//                if(sName.toInt() == 0 && pBackItem)
//                {
//                    pos.setX(pos.x() + 5);
//                    QGroupItem *pBaseItem = new QGroupItem(pBackItem);
//                    pBaseItem->SetWidth(pBackItem->boundingRect().width());
//                    pBaseItem->SetHeigth(pBackItem->boundingRect().height());
//                    pBackItem->setPos(pos - pBackItem->boundingRect().topLeft());
//                }
//            }
//            if(ikey == SAM_DRAW_OBJECT_TEXT)
//            {
//                pos.setY(pos.y() - 5);
//                pItem->setPos(pos - pItem->boundingRect().topLeft());
//            }
//        }
    }
//    AnimationItem *newGroup = new AnimationItem;
//    foreach(QGraphicsItem *pItem,items)
//    {
//        //pCopyItem->removeFromGroup(pItem);
//        newGroup->addToGroup(pItem);
//    }
//    pCopyItem = newGroup;
}

void AnimationDlg::on_btn_customValue_clicked()
{
    if(values.size() <= 0)
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("状态个数为0"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return;
    }
    QMultiStateGenelCunstomDlg *customDlg=new QMultiStateGenelCunstomDlg(this);

    customDlg->setAllData(values,false);
    if(customDlg->exec() == QDialog::Accepted)
    {
        values = customDlg->allValues;
    }
}

void AnimationDlg::on_Monitor_Address_EntryBtn_clicked()
{
    QString addrStr = ui->Monitor_Address->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->Monitor_Address->setText(Monitor_Address_Keyboard.sShowAddr);
    }
}

void AnimationDlg::on_m_TextlineEdit_textChanged(QString )
{
    if(bInitflag)
    {
        //on_m_SaveTextpushBtn_clicked();
    }
}

void AnimationDlg::on_m_TextlineEdit_textChanged()
{
    if(bInitflag)
    {
        on_m_SaveTextpushBtn_clicked();
    }
}

void AnimationDlg::on_m_SelectLibpushBtn_2_clicked()
{
    onSelectpicbtn(1);
}

void AnimationDlg::on_m_SelectPicpushBtn_2_clicked()
{
    onSelectpicbtn(0);
}
