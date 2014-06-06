#include "newdatacontrol.h"
#include "ui_newdatacontrol.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

NewDataControl::NewDataControl(QWidget *parent):QDialog(parent),ui(new Ui::NewDataControl)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setFixedSize(size());
    setWindowTitle(tr("数据控制"));

    ui->checkBox_1->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bCurScreenNum);
    ui->checkBox_2->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bCurFormulaNum);
    ui->checkBox_3->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bCurLanguageNum);

    ui->groupBox_2->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bWordAddrScreenNum);

    on_checkBox_1_clicked(ui->checkBox_1->isChecked());
    on_checkBox_2_clicked(ui->checkBox_2->isChecked());
    on_checkBox_3_clicked(ui->checkBox_3->isChecked());
    on_groupBox_2_clicked(ui->groupBox_2->isChecked());

    ui->lineEdit_screen->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_keyCurScreen.sShowAddr);
    ui->lineEdit_formula->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_keyCurFormula.sShowAddr);
    ui->lineEdit_language->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_keyCurLanguage.sShowAddr);
    ui->lineEdit_wordAddr->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_keyWordAddrScreen.sShowAddr);

    ScreenAddr = pwnd->m_pSamSysParame->m_mixGlobalVar.m_keyCurScreen;
    RecipeAddr = pwnd->m_pSamSysParame->m_mixGlobalVar.m_keyCurFormula;
    LanguageAddr = pwnd->m_pSamSysParame->m_mixGlobalVar.m_keyCurLanguage;
    WCtrlAddr = pwnd->m_pSamSysParame->m_mixGlobalVar.m_keyWordAddrScreen;

    model=new QStandardItemModel(this);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    model->setColumnCount(3);
    model->setHeaderData(2,Qt::Horizontal,tr("画面名称"));
    model->setHeaderData(1,Qt::Horizontal,tr("位地址"));
    model->setHeaderData(0,Qt::Horizontal,tr("条件"));
    ui->tableView->setColumnWidth(0,60);
    ui->tableView->setColumnWidth(1,80);
    //ui->tableView->setColumnWidth(2,200);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);//最后一行拉伸
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    model->setRowCount(1);

    New_action = new QAction(this);
    New_action->setText(tr("新建(&N)"));
    Edit_action = new QAction(this);
    Edit_action->setText(tr("编辑(&E)"));
    Del_action = new QAction(this);
    Del_action->setText(tr("删除(&D)"));
    Del_action->setShortcuts(QKeySequence::Delete);
    connect(New_action,SIGNAL(triggered()),this,SLOT(newTableItem()));
    connect(Edit_action,SIGNAL(triggered()),this,SLOT(editTableItem()));
    connect(Del_action,SIGNAL(triggered()),this,SLOT(delTableItem()));
    ui->tableView->addAction(New_action);
    ui->tableView->addAction(Edit_action);
    ui->tableView->addAction(Del_action);
    ui->tableView->setMouseTracking(true);
    currentRow = 0;
    connect(ui->tableView,SIGNAL(viewportEntered()),this,SLOT(tableThing()));
    connect(ui->tableView,SIGNAL(doubleClicked(QModelIndex)), this,SLOT(TableDouble(QModelIndex)));
    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(table_rightMenu(QModelIndex)));

    ui->checkBox->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_bBitSenceExch);
    if(ui->checkBox->isChecked())
    {
        ui->tableView->setEnabled(true);
    }
    else
    {
        ui->tableView->setEnabled(false);
    }

    int row = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence.size();
    model->setRowCount(row + 1);
    for(int i = 0; i < row; i++)
    {
        model->setData(model->index(i, 0, QModelIndex()), pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].nCtlStatus);
        model->setData(model->index(i, 1, QModelIndex()), pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].mCtlSceneAddr.sShowAddr);
        model->setData(model->index(i, 2, QModelIndex()), pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].sCtlSceneId);
        ui->tableView->setRowHeight(i, 25);
    }
    model->setHeaderData(row,Qt::Vertical,tr("新建"));
    ui->tableView->setRowHeight(row,25);
}

//void NewDataControl::InitScreenIndex(QComboBox *Cbox,int nCurrentIndex)
void NewDataControl::InitScreenIndex(QComboBox *Cbox, QString str)
{
    int nScreenCount = 0;
    int count = pwnd->pSceneSheet.size();
    bool bHave = false;
    for(int i = 0; i < count; i++)
    {
        if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 0 || pwnd->pSceneSheet[i]->nIsSceneOrWindow == 1)
        {
            nScreenCount++;
            if(pwnd->pSceneSheet[i]->sNewScreenName == str)
            {
                bHave = true;
                break;
            }
        }
    }

    if(bHave == true)
    {
        Cbox->setCurrentIndex(nScreenCount - 1);
    }
    else
    {
        Cbox->setCurrentIndex(0);
    }
    /*int nindex;
    int nScreenCount;
    for(nindex = 0,nScreenCount = 0;(nindex <= nCurrentIndex) && (nindex < pwnd->pSceneSheet.size()); nindex++)
    {
        if(pwnd->pSceneSheet[nindex]->nIsSceneOrWindow == 0 || pwnd->pSceneSheet[nindex]->nIsSceneOrWindow == 1)
        {
            nScreenCount++;
        }
    }
    Cbox->setCurrentIndex(nScreenCount - 1);*/
}

/*int NewDataControl::getScreenIndex(QString str)
{
    for(int i = 0; i < pwnd->pSceneSheet.size(); i++)
    {
        if(str == pwnd->pSceneSheet[i]->sNewScreenName)
        {
            return i;//找到的话返回该值
        }
    }
    return 0;//找不到返回0
}*/

void NewDataControl::newTableItem()
{
    int rows = model->rowCount();
    subDataControl screenSettingDlg(this);
    screenSettingDlg.setWindowTitle(tr("新建"));
    screenSettingDlg.ui->lineEdit->setText("");
    screenSettingDlg.kaddress.nConnectType     = 0;
    screenSettingDlg.kaddress.nPlcRegTypeIndex = 0;
    screenSettingDlg.kaddress.nPlcStationIndex = 0;
    screenSettingDlg.kaddress.nAddrType        = 0;
    screenSettingDlg.kaddress.sShowAddr        = "";
    screenSettingDlg.kaddress.sPlcAddrValue    = "";
    screenSettingDlg.kaddress.sPlcRegTypeStr   = "LB";
    screenSettingDlg.kaddress.Length           = 0;

    screenSettingDlg.sel_group->button(1)->setChecked(true);
    screenSettingDlg.ui->comboBox->setCurrentIndex(0);
    screenSettingDlg.ui->checkBox->setChecked(false);
    screenSettingDlg.ui->checkBox_close->setChecked(false);
    int res = screenSettingDlg.exec();
    if(res == QDialog::Accepted)
    {
        BitSenceItem sceneCtlByBit;
        sceneCtlByBit.mCtlSceneAddr = screenSettingDlg.kaddress;
        sceneCtlByBit.sCtlSceneId   = screenSettingDlg.ui->comboBox->currentText();
        sceneCtlByBit.nCtlStatus    = screenSettingDlg.sel_group->checkedId();
        if(screenSettingDlg.ui->checkBox->isEnabled())
        {
            sceneCtlByBit.bReset        = screenSettingDlg.ui->checkBox->isChecked();
        }
        else
        {
            sceneCtlByBit.bReset = false;
        }
        if(screenSettingDlg.ui->checkBox_close->isEnabled())
        {
            sceneCtlByBit.bClose = screenSettingDlg.ui->checkBox_close->isChecked();
        }
        else
        {
            sceneCtlByBit.bClose = false;
        }
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence.push_back(sceneCtlByBit);

        model->setRowCount(rows + 1);
        model->setData(model->index(rows - 1, 0, QModelIndex()), pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence.last().nCtlStatus);
        model->setData(model->index(rows - 1, 1, QModelIndex()), pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence.last().mCtlSceneAddr.sShowAddr);
        model->setData(model->index(rows - 1, 2, QModelIndex()), pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence.last().sCtlSceneId);
        model->setHeaderData(rows - 1, Qt::Vertical, rows);
        model->setHeaderData(rows, Qt::Vertical,tr("新建"));
        ui->tableView->setRowHeight(rows, 25);
    }
}

void NewDataControl::editTableItem()
{
    subDataControl screenSettingDlg(this);
    screenSettingDlg.setWindowTitle(tr("编辑"));
    screenSettingDlg.ui->lineEdit->setText(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].mCtlSceneAddr.sShowAddr);
    screenSettingDlg.kaddress = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].mCtlSceneAddr;
    screenSettingDlg.ui->checkBox->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].bReset);
    screenSettingDlg.sel_group->button(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].nCtlStatus)->setChecked(true);
    screenSettingDlg.ui->checkBox_close->setChecked(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].bClose);
    //InitScreenIndex(screenSettingDlg.ui->comboBox,pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].sCtlSceneId);
    //screenSettingDlg.ui->comboBox->setCurrentIndex(0);
    int nScreenCount = 0;
    int count = pwnd->pSceneSheet.size();
    bool bHave = false;
    for(int i = 0; i < count; i++)
    {
        if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 0 || pwnd->pSceneSheet[i]->nIsSceneOrWindow == 1)
        {
            nScreenCount++;
            //QString strT = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].sCtlSceneId;
            QString strItem = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].sCtlSceneId;
            if(pwnd->pSceneSheet[i]->sNewScreenName == strItem)
            {
                bHave = true;
                screenSettingDlg.ui->comboBox->setCurrentIndex(nScreenCount - 1);
                if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 0)
                {
                    screenSettingDlg.ui->checkBox->setDisabled(false);
                    screenSettingDlg.ui->checkBox_close->setDisabled(true);
                    screenSettingDlg.ui->checkBox_close->setChecked(false);
                }
                else if(1 == pwnd->pSceneSheet[i]->nIsSceneOrWindow)
                {
                    if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].bReset)
                    {
                        screenSettingDlg.ui->checkBox->setDisabled(false);
                        screenSettingDlg.ui->checkBox_close->setDisabled(true);
                        screenSettingDlg.ui->checkBox_close->setChecked(false);
                    }
                    else
                    {
                        if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].bClose)
                        {
                            screenSettingDlg.ui->checkBox->setDisabled(true);
                            screenSettingDlg.ui->checkBox->setChecked(false);
                        }
                        else
                        {
                           screenSettingDlg.ui->checkBox->setDisabled(false);
                        }
                        screenSettingDlg.ui->checkBox_close->setDisabled(false);
                    }
                }
                break;
            }
        }
    }
    if(bHave == false)
    {
        screenSettingDlg.ui->comboBox->setCurrentIndex(0);
        if(0 == pwnd->pSceneSheet[0]->nIsSceneOrWindow)
        {
            screenSettingDlg.ui->checkBox->setDisabled(false);
            screenSettingDlg.ui->checkBox_close->setDisabled(true);
        }
        else if(1 == pwnd->pSceneSheet[0]->nIsSceneOrWindow)
        {
            if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].bReset)
            {
                screenSettingDlg.ui->checkBox->setDisabled(false);
                screenSettingDlg.ui->checkBox_close->setDisabled(true);
            }
            else
            {
                if(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].bClose)
                {
                    screenSettingDlg.ui->checkBox->setDisabled(true);
                }
                else
                {
                   screenSettingDlg.ui->checkBox->setDisabled(false);
                }
                screenSettingDlg.ui->checkBox_close->setDisabled(false);
            }
        }
    }

    //int k = screenSettingDlg.ui->comboBox->count();
    //QString stri = screenSettingDlg.ui->comboBox->itemText(0);

    int res = screenSettingDlg.exec();
    if(res==QDialog::Accepted)
    {
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].mCtlSceneAddr = screenSettingDlg.kaddress;
        //QString hhh = screenSettingDlg.ui->comboBox->currentText();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].sCtlSceneId   = screenSettingDlg.ui->comboBox->currentText();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].nCtlStatus    = screenSettingDlg.sel_group->checkedId();
        if(screenSettingDlg.ui->checkBox->isEnabled())
        {
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].bReset        = screenSettingDlg.ui->checkBox->isChecked();
        }
        else
        {
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].bReset = false;
        }
        if(screenSettingDlg.ui->checkBox_close->isEnabled())
        {
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].bClose = screenSettingDlg.ui->checkBox_close->isChecked();
        }
        else
        {
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].bClose = false;
        }

        model->setData(model->index(currentRow, 0, QModelIndex()), pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].nCtlStatus);
        model->setData(model->index(currentRow, 1, QModelIndex()), pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].mCtlSceneAddr.sShowAddr);
        model->setData(model->index(currentRow, 2, QModelIndex()), pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[currentRow].sCtlSceneId);
    }
}

void NewDataControl::delTableItem()
{
    QString str = model->headerData(currentRow,Qt::Vertical, Qt::DisplayRole).toString();
    if(str == tr("新建"))
    {
         return;
    }
    model->takeRow(currentRow);
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence.remove(currentRow);
    for(int i = 0; i < model->rowCount() - 1; i++)
    {
        model->setHeaderData(i,Qt::Vertical,i+1,Qt::EditRole);
        model->setData(model->index(i,0,QModelIndex()),pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].nCtlStatus);
        model->setData(model->index(i,1,QModelIndex()),pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].mCtlSceneAddr.sShowAddr );
        model->setData(model->index(i,2,QModelIndex()),pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].sCtlSceneId);
    }
}

void NewDataControl::table_rightMenu(QModelIndex modelIndex)
{
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    currentRow = modelIndex.row();
    QString str = model->headerData(currentRow,Qt::Vertical,Qt::DisplayRole).toString();
    if(str == tr("新建"))
    {
        New_action->setEnabled(true);
        Edit_action->setEnabled(false);
        Del_action->setEnabled(false);
    }
    else
    {
         New_action->setEnabled(false);
         Edit_action->setEnabled(true);
         Del_action->setEnabled(true);
    }
}

void NewDataControl::tableThing()
{
    ui->tableView->setContextMenuPolicy(Qt::NoContextMenu);
}

void NewDataControl::TableDouble(QModelIndex modelIndex)
{
    QString str = model->headerData(modelIndex.row(),Qt::Vertical,Qt::DisplayRole).toString();
    if(str == tr("新建"))
    {
        currentRow = modelIndex.row();
        newTableItem();
    }
    else
    {
        currentRow = modelIndex.row();
        editTableItem();
    }
}

NewDataControl::~NewDataControl()
{
    delete ui;
}

void NewDataControl::on_pushButton_sure_clicked()
{
    if( ui->checkBox_1->isChecked() )
    {
        if(!pwnd->IsAddressCheckRight(ScreenAddr,tr("画面地址"),ui->lineEdit_screen,1))
        {
            return;
        }
    }

    if( ui->checkBox_2->isChecked() )
    {
        if(!pwnd->IsAddressCheckRight(RecipeAddr,tr("配方地址"),ui->lineEdit_formula,1))
        {
            return;
        }
    }

    if( ui->checkBox_3->isChecked() )
    {
        if(!pwnd->IsAddressCheckRight(LanguageAddr,tr("语言地址"),ui->lineEdit_language,1))
        {
            return;
        }
    }

    if( ui->groupBox_2->isChecked())
    {
        if(!pwnd->IsAddressCheckRight(WCtrlAddr,tr("画面切换地址"),ui->lineEdit_wordAddr,1))
        {
            return;
        }
    }

    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bCurScreenNum       = ui->checkBox_1->isChecked();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bCurFormulaNum      = ui->checkBox_2->isChecked();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bCurLanguageNum     = ui->checkBox_3->isChecked();
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bWordAddrScreenNum  = ui->groupBox_2->isChecked();

    pwnd->m_pSamSysParame->m_mixGlobalVar.m_keyCurScreen        = ScreenAddr;
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_keyCurFormula       = RecipeAddr;
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_keyCurLanguage      = LanguageAddr;
    pwnd->m_pSamSysParame->m_mixGlobalVar.m_keyWordAddrScreen   = WCtrlAddr;

    pwnd->m_pSamSysParame->m_mixGlobalVar.m_bBitSenceExch       = ui->checkBox->isChecked();

    accept();
}

void NewDataControl::on_pushButton_cancel_clicked()
{
    close();
}

void NewDataControl::on_checkBox_1_clicked(bool checked)
{
    ui->lineEdit_screen->setEnabled(checked);
    ui->pushButton_addrBegin->setEnabled(checked);
}

void NewDataControl::on_checkBox_2_clicked(bool checked)
{
    ui->lineEdit_formula->setEnabled(checked);
    ui->pushButton_addrBegin_2->setEnabled(checked);
}

void NewDataControl::on_checkBox_3_clicked(bool checked)
{
    ui->lineEdit_language->setEnabled(checked);
    ui->pushButton_addrBegin_3->setEnabled(checked);
}

void NewDataControl::on_groupBox_2_clicked(bool checked)
{
    ui->label_4->setEnabled(checked);
    ui->lineEdit_wordAddr->setEnabled(checked);
    ui->pushButton_addrBegin_4->setEnabled(checked);
}

void NewDataControl::on_pushButton_addrBegin_clicked()
{
    pwnd->Addr_Type = 1;
    AddressInputDialog dlg_readaddress(ScreenAddr,this);
    dlg_readaddress.exec();
    ui->lineEdit_screen->setText(ScreenAddr.sShowAddr);
}

void NewDataControl::on_pushButton_addrBegin_2_clicked()
{
    pwnd->Addr_Type = 1;
    AddressInputDialog dlg_readaddress(RecipeAddr,this);
    dlg_readaddress.exec();
    ui->lineEdit_formula->setText(RecipeAddr.sShowAddr);
}

void NewDataControl::on_pushButton_addrBegin_3_clicked()
{
    pwnd->Addr_Type = 1;
    AddressInputDialog dlg_readaddress(LanguageAddr,this);
    dlg_readaddress.exec();
    ui->lineEdit_language->setText(LanguageAddr.sShowAddr);
}

void NewDataControl::on_pushButton_addrBegin_4_clicked()
{
    pwnd->Addr_Type = 1;
    AddressInputDialog dlg_readaddress(WCtrlAddr,this);
    dlg_readaddress.exec();
    ui->lineEdit_wordAddr->setText(WCtrlAddr.sShowAddr);
}

void NewDataControl::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->tableView->setEnabled(true);
    }
    else
    {
        ui->tableView->setEnabled(false);
    }
}

void NewDataControl::on_pushButton_help_clicked()
{
    pwnd->loadHelpHtm(TREE_DATACONTROL);
}
