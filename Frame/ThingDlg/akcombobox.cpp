#include "akcombobox.h"
#include "ui_akcombobox.h"
#include "Macro/macroedit.h"
#include "../mainwindow.h"
#include "Frame/DrawDlg/OpenLibrary.h"

extern MainWindow *pwnd;

AkComboBox::AkComboBox(AkComboItem* pItem, QWidget *parent):QDialog(parent),ui(new Ui::AkComboBox)
{
    ui->setupUi(this);

    m_pCopyItem = NULL;
    pSceneItem = NULL;
    pEdit = NULL;
    bInit = false;
    oId = -1;

    this->m_nEditRow = -1;
    this->m_nEditCol = -1;

    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    this->setWindowTitle(tr("下拉框"));

    pBaseItem = NULL;
    //pCopyItem = NULL;
    pScene    = NULL;//场景
    pTempItem = NULL;
    pRect     = NULL;
    pBackRect = NULL;
    pLine     = NULL;

    pScene = new QGraphicsScene(this); //建场景
    ui->graphicsView->setScene(pScene);//贴图区域

    pSecurityWight = new SecurityWidget(this);
    ui->tabWidget->addTab(pSecurityWight, tr("权限设置"));

    ui->comboBox_fontType->addItems(QFontDatabase().families(QFontDatabase::Any));

    ui->label_color->setEnabled(false);
    ui->btn_backcolor->setEnabled(false);
    ui->label_Trans->setEnabled(false);
    ui->spin_Trans->setEnabled(false);
    ui->edit_path->setEnabled(false);

    ui->label_type_5->setVisible(false);
    ui->combo_Alignment->setVisible(false);

    ui->combo_Language->clear();
    int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    for(int i = 0; i < lanNum; i++)
    {
        ui->combo_Language->addItem(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }

    foreach(Macro lib, pwnd->macros)
    {
        if (lib.type && lib.isCompiled())
        {
            ui->comboBox_script_2->addItem(lib.libName);
            //ui->comboBox_function->addItems(lib.functions);
        }
    }

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setColumnWidth(0, ui->tableWidget->sizeHint().width()/2);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一行拉伸

    curLan = 0;
    InitProperty(pItem);

    bInit = true;

    drawScene();
}

AkComboBox::~AkComboBox()
{
    if(pSecurityWight)
    {
        delete pSecurityWight;
        pSecurityWight = NULL;
    }

    /*if(m_pCopyItem)
    {
        delete m_pCopyItem;
        m_pCopyItem = NULL;
    }*/

    /*if(pRect)
    {
        delete pRect;
        pRect = NULL;
    }

    if(pBackRect)
    {
        delete pBackRect;
        pBackRect = NULL;
    }

    if(pLine)
    {
        delete pLine;
        pLine = NULL;
    }*/

    /*if(pTempItem)
    {
        delete pTempItem;
        pTempItem = NULL;
    }*/

    /*if(pScene)
    {
        delete pScene;
        pScene = NULL;
    }*/

    delete ui;
}

void AkComboBox::InitProperty(AkComboItem* pItem)
{
    pSecurityWight->init(pItem);

    if(pItem)
    {
        key           = pItem->dataCombo.m_keyCtrlAddr;
        eLibType      = pItem->dataCombo.m_eLibType;
        path          = pItem->dataCombo.m_strPath;
        BkColor       = pItem->dataCombo.m_nBKColor;
        TextColor     = pItem->dataCombo.m_vecLanguage[curLan].m_nTextColor;
        m_vecStatus   = pItem->dataCombo.m_vecStatus;
        m_vecLanguage = pItem->dataCombo.m_vecLanguage;

        ui->m_DataTypefontCmbBox->setCurrentIndex((int)pItem->dataCombo.m_eDataType - 2);
        ui->lineEdit_timeAddr->setText(key.sShowAddr);
        ui->groupBox_5->setChecked(pItem->dataCombo.m_bUseMacro);
        //设置脚本部分
        if(pItem->dataCombo.m_bUseMacro)
        {
            if(pItem->dataCombo.m_strMacroName != "")
            {
                int macroIndex = ui->comboBox_script_2->findText(pItem->dataCombo.m_strMacroName);
               // if (macroIndex >= 0)
                {
                    ui->comboBox_script_2->setCurrentIndex(macroIndex);
                }
            }
            else
            {
               // ui->comboBox_script_2->setCurrentIndex(0);
            }
        }
        if(NO_PIC != eLibType)//图库
        {
            ui->label_color->setEnabled(false);
            ui->btn_backcolor->setEnabled(false);
            ui->label_Trans->setEnabled(false);
            ui->spin_Trans->setEnabled(false);
            ui->edit_path->setText(path);
        }
        else//背景色
        {
            ui->label_color->setEnabled(true);
            ui->btn_backcolor->setEnabled(true);
            ui->label_Trans->setEnabled(true);
            ui->spin_Trans->setEnabled(true);
            ui->edit_path->setText("");
            ui->btn_backcolor->setStyleSheet(QString("background:%1").arg(BkColor.name()));
            ui->spin_Trans->setValue(pItem->dataCombo.m_nAlpha);
        }

        ui->spinBox->setValue(pItem->dataCombo.m_nStatuNum);
        ui->checkBox_lanFirst->setChecked(pItem->dataCombo.m_bFirstLan);

        ui->combo_Language->setCurrentIndex(curLan);

        int num = QFontDatabase().families(QFontDatabase::Any).size();
        for(int i = 0; i < num; i++)
        {
            if(m_vecLanguage[curLan].m_strFontName == QFontDatabase().families(QFontDatabase::Any).at(i))
            {
                ui->comboBox_fontType->setCurrentIndex(i);
                break;
            }
        }

        ui->combo_Alignment->setCurrentIndex(m_vecLanguage[curLan].m_nAlign);
        ui->spinBox_2->setValue(m_vecLanguage[curLan].m_nFontSize);

        ui->btn_backcolor_2->setStyleSheet(QString("background:%1").arg(TextColor.name()));
        ui->checkBox->setChecked(m_vecLanguage[curLan].m_bCuTi);
        ui->checkBox_2->setChecked(m_vecLanguage[curLan].m_bXieTi);
        ui->checkBox_3->setChecked(m_vecLanguage[curLan].m_bXiaHuaXian);
        oId = pItem->id();
        ui->spinBox_3->setValue(oId);
    }
    else
    {
        path     = "";
        eLibType = NO_PIC;
        key.sShowAddr = "LW0";

        int lanNum = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
        ComboLanguage lanAttr;
        lanAttr.m_nAlign        = 0;
        lanAttr.m_nFontSize     = 10;
        lanAttr.m_nTextColor    = QColor(0,0,0);
        lanAttr.m_strFontName   = tr("Droid Sans Fallback");
        lanAttr.m_bXieTi        = false;
        lanAttr.m_bCuTi         = false;
        lanAttr.m_bXiaHuaXian   = false;
        for(int i = 0; i < lanNum; i++)
        {
            m_vecLanguage.push_back(lanAttr);
        }

        ComboStatu state;
        QString str = "state_";
        state.m_vecText.resize(lanNum);
        for(int i = 0; i < 2; i++)//2个状态
        {
            state.m_value = i;
            for(int j = 0; j < lanNum; j++)
            {
                state.m_vecText[j] = str + QString::number(i);
            }
            m_vecStatus.push_back(state);
        }

        BkColor = QColor(100, 100, 100);

        //默认不需要图片
        ui->label_color->setEnabled(true);
        ui->btn_backcolor->setEnabled(true);
        ui->label_Trans->setEnabled(true);
        ui->spin_Trans->setEnabled(true);
        ui->spinBox_3->setValue(pwnd->getNewId());

        //背景色
        ui->btn_backcolor->setStyleSheet(QString("background:%1").arg(BkColor.name()));

        //字体名字
        int num = QFontDatabase().families(QFontDatabase::Any).size();
        for(int i = 0; i < num; i++)
        {
            if(m_vecLanguage[curLan].m_strFontName == QFontDatabase().families(QFontDatabase::Any).at(i))
            {
                ui->comboBox_fontType->setCurrentIndex(i);
                break;
            }
        }

        //字体大小
        ui->spinBox_2->setValue(m_vecLanguage[curLan].m_nFontSize);
        //对齐
        //ui->combo_Alignment->setCurrentIndex(m_vecLanguage[curLan].m_nAlign);
        //文本色
        ui->btn_backcolor_2->setStyleSheet(QString("background:%1").arg(m_vecLanguage[curLan].m_nTextColor.name()));
    }

    int num = m_vecStatus.size();
    ui->tableWidget->setRowCount(num);
    for(int i = 0; i < num; i++)
    {
        if(i != num - 1)//如果不是最后一行
        {
            QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(m_vecStatus[i].m_value));
            ui->tableWidget->setItem(i, 0, newItem1);
        }
        else//如果是最后一行
        {
            QTableWidgetItem *newItem1;
            if(pItem)
            {
                newItem1 = new QTableWidgetItem(QString::number(m_vecStatus[i].m_value));
            }
            else
            {
                newItem1 = new QTableWidgetItem("error");
            }

            ui->tableWidget->setItem(i, 0, newItem1);
        }

        QTableWidgetItem *newItem2 = new QTableWidgetItem(m_vecStatus[i].m_vecText[curLan]);
        ui->tableWidget->setItem(i, 1, newItem2);
    }
}

void AkComboBox::on_btn_new_2_clicked()//写脚本
{
    Macro lib;
    AddLib addWzrd(pwnd->macros,this);
    addWzrd.setWindowTitle(tr("添加脚本"));
    if(addWzrd.exec() == QDialog::Accepted)
    {
        lib.libName = addWzrd.libName;
        lib.type = true;
        lib.setCompipiled(false);
        lib.setCode(SCRIPT_HEADER);
        pwnd->macros.append(lib);
        MacroEdit *dlg = new MacroEdit(lib.libName,this);
        dlg->exec();
        pwnd->is_Save=false;
        pwnd->is_NeedCompiled = true;
        pwnd->ui->action_save->setDisabled(false);//当打开工程时改变保存按钮的颜色
    }
    QString libname = ui->comboBox_script_2->currentText();
    ui->comboBox_script_2->clear();
    foreach(Macro lib,pwnd->macros) //初始化库名称
    {
        if (lib.type && lib.isCompiled())
        {
            ui->comboBox_script_2->addItem(lib.libName);
        }
    }
    int index = ui->comboBox_script_2->findText(libname);
    if(index >= 0)
    {
        ui->comboBox_script_2->setCurrentIndex(index);
    }
}

void AkComboBox::on_pushButton_timeAddr_clicked()//控制地址按钮
{
    QString str = ui->lineEdit_timeAddr->text();
    AddressInputDialog dlg_readaddress(key,str,1,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit_timeAddr->setText(key.sShowAddr);
    }
}

void AkComboBox::on_spinBox_valueChanged(int value)//总状态数
{
    if(value < 2)
    {
        return;
    }

    if(value < m_vecStatus.size())//当前有的状态要删去
    {
        int del = m_vecStatus.size() - value;
        for(int i = 0; i < del; i++)
        {
            m_vecStatus.pop_back();
        }
    }
    else if(value > m_vecStatus.size())//增加状态
    {
        int add     = value - m_vecStatus.size();
        int temp    = m_vecStatus.size();
        bool bFirst = ui->checkBox_lanFirst->isChecked();
        int lanNum  = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
        for(int i = 0; i < add; i++)
        {
            ComboStatu state;

            state.m_value = temp + i;
            if(bFirst)//所有语言同第一种语言
            {
                state.m_vecText = m_vecStatus[0].m_vecText;
            }
            else
            {
                //state.m_vecText.resize(lanNum);
                QString str = "state_" + QString::number(state.m_value);
                for(int j = 0; j < lanNum; j++)
                {
                    state.m_vecText.push_back(str);
                }
            }
            m_vecStatus.push_back(state);
        }
    }

    //刷新列表
    int count = ui->tableWidget->rowCount();
    while(count > 0)//清空表格显示的数据
    {
        ui->tableWidget->removeRow(0);
        count--;
    }
    count = m_vecStatus.size();
    ui->tableWidget->setRowCount(count);
    for(int i = 0; i < count; i++)
    {
        if(i != count - 1)//如果不是最后一行
        {
            QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(m_vecStatus[i].m_value));
            ui->tableWidget->setItem(i, 0, newItem1);
        }
        else//如果是最后一行
        {
            QTableWidgetItem *newItem1 = new QTableWidgetItem("error");
            ui->tableWidget->setItem(i, 0, newItem1);
        }

        QTableWidgetItem *newItem2 = new QTableWidgetItem(m_vecStatus[i].m_vecText[curLan]);
        ui->tableWidget->setItem(i, 1, newItem2);
    }
}

void AkComboBox::on_checkBox_lanFirst_clicked(bool checked)//所有语言都使用第一种语言
{
    if(!checked)
    {
        ui->combo_Language->setEnabled(true);
        return;
    }

    curLan = 0;

    ui->combo_Language->setCurrentIndex(0);
    ui->combo_Language->setEnabled(false);
    int num = QFontDatabase().families(QFontDatabase::Any).size();
    for(int i = 0; i < num; i++)
    {
        if(m_vecLanguage[0].m_strFontName == QFontDatabase().families(QFontDatabase::Any).at(i))
        {
            ui->comboBox_fontType->setCurrentIndex(i);
            break;
        }
    }
    ui->combo_Alignment->setCurrentIndex(m_vecLanguage[0].m_nAlign);
    ui->spinBox_2->setValue(m_vecLanguage[0].m_nFontSize);
    ui->btn_backcolor_2->setStyleSheet(QString("background:%1").arg(m_vecLanguage[0].m_nTextColor.name()));
    ui->checkBox->setChecked(m_vecLanguage[0].m_bCuTi);
    ui->checkBox_2->setChecked(m_vecLanguage[0].m_bXieTi);
    ui->checkBox_3->setChecked(m_vecLanguage[0].m_bXiaHuaXian);

    int temp = m_vecLanguage.size();
    ComboLanguage language = m_vecLanguage[0];
    for(int i = 1; i < temp; i++)
    {
        m_vecLanguage[i] = language;
    }

    temp = m_vecStatus.size();
    for(int i = 0; i < temp; i++)
    {
        int num = m_vecStatus[i].m_vecText.size();
        QString str = m_vecStatus[i].m_vecText[0];
        QTableWidgetItem *item = ui->tableWidget->item(i, 1);
        if(item->text() != str)
        {
            item->setText(str);
        }
        for(int j  = 1; j < num; j++)
        {
            m_vecStatus[i].m_vecText[j] = str;
        }
    }
}

void AkComboBox::on_btn_lib_clicked()//选择图库
{
    QGraphicsItem *pCopyItem = NULL;

    DrawItemToScene GroupFunction;
    OpenLibrary *pDlg = new OpenLibrary(this);
    if(pDlg->exec() == QDialog::Accepted)
    {
        if(LIBRARY_LIB_GROUP == pDlg->pCopyItem->data(GROUP_TYPE_KEY).toInt())
        {
            eLibType = LIBRARY;
        }
        else
        {
            eLibType = PIC;
        }
        //eLibType = LIBRARY;

        if(pDlg->pCopyItem)
        {
            GroupFunction.CopyItem(&pCopyItem,pDlg->pCopyItem);
        }
        else
        {
            return;
        }

        path = pCopyItem->data(GROUP_NAME_KEY).toString();

        ui->label_color->setEnabled(false);
        ui->btn_backcolor->setEnabled(false);
        ui->label_Trans->setEnabled(false);
        ui->spin_Trans->setEnabled(false);
        ui->edit_path->setText(path);

        drawScene();
    }
    else
    {
        pDlg->deleteLater();
        pDlg = NULL;
        return;
    }

    //刷新图片
    qDebug()<<"UpdatePic start..";
    //UpdatePic(index);
}

void AkComboBox::on_btn_no_clicked()//不使用图片
{
    eLibType = NO_PIC;

    ui->label_color->setEnabled(true);
    ui->btn_backcolor->setEnabled(true);
    ui->label_Trans->setEnabled(true);
    ui->spin_Trans->setEnabled(true);

    //刷新图片
    qDebug()<<"UpdatePic start..";
    //UpdatePic(index);

    drawScene();
}

void AkComboBox::on_btn_picture_clicked()//外部图片
{
    QString filename=QFileDialog::getOpenFileName(this,
            tr("Open File"),pwnd->picturePath,
            tr("Images (*.png *.jpg *.bmp)"));
    QPixmap picture = QPixmap(filename);
    if(!picture.isNull())
    {
        eLibType = PIC;
        path     = filename;
        //UpdatePic(index);
        pwnd->picturePath = filename;

        ui->label_color->setEnabled(false);
        ui->btn_backcolor->setEnabled(false);
        ui->label_Trans->setEnabled(false);
        ui->spin_Trans->setEnabled(false);
        ui->edit_path->setText(path);

        drawScene();
    }
}

void AkComboBox::on_btn_backcolor_clicked()//背景色
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//
    pwnd->OnAddColorDlg(ui->btn_backcolor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_fill(const QColor &)));
}

void AkComboBox::set_pushButton_fill(const QColor & mColor)//背景色
{
    ui->btn_backcolor->setStyleSheet(QString("background:%1").arg(mColor.name()));
    BkColor = mColor;
    drawScene();
}

void AkComboBox::on_accept_clicked()
{
    m_pCopyItem = new AkComboItem;

    if(!pwnd->IsAddressCheckRight(key, tr("地址"), ui->lineEdit_timeAddr, 1))
    {
        ui->lineEdit_timeAddr->setFocus();
        return ;
    }

    int num = m_vecStatus.size();
    int index = ui->m_DataTypefontCmbBox->currentIndex();
    double tempMax;
    double tempMin;
    switch(index)
    {
        case 0://16位整数
        {
            tempMax = 32767;
            tempMin = -32768;
        }
        break;
        case 1://32位整数
        {
            tempMax = 2147483648L;
            tempMin = -2147483647L;
        }
        break;
        case 2://16位正整数
        {
            tempMax = 65535;
            tempMin = 0;
        }
        break;
        case 3://32位正整数
        {
            tempMax = 4294967295L;
            tempMin = 0;
        }
        break;
        case 4://16位BCD码
        {
            tempMax = 9999;
            tempMin = 0;
        }
        break;
        case 5://32位BCD码
        {
            tempMax = 99999999;
            tempMin = 0;
        }
        break;
        case 6://32位浮点数
        {
            tempMax = 2147483648L;
            tempMin = -2147483647L;
        }
        break;
    }

    for(int i = 0; i < num - 1; i++)//最后一行的值不检测
    {
        if(m_vecStatus[i].m_value < tempMin || m_vecStatus[i].m_value > tempMax)
        {
            QString str = tr("状态值") + QString::number(i) + tr("超出范围");
            QMessageBox box(QMessageBox::Information,tr("错误"),str,QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("确定"));
            box.exec();
            return;
        }
    }

    //m_pCopyItem = new qMessageBoradAttr;
    if(pSecurityWight && pSecurityWight->Save())
    {
        m_pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    }
    else
    {
        return;
    }

    m_pCopyItem->dataCombo.m_nStatuNum      = ui->spinBox->value();
    int k = ui->m_DataTypefontCmbBox->currentIndex();
    m_pCopyItem->dataCombo.m_eDataType      = (DATA_TYPE)(k + 2);
    m_pCopyItem->dataCombo.m_keyCtrlAddr    = key;
    m_pCopyItem->dataCombo.m_nAlpha         = ui->spin_Trans->value();
    m_pCopyItem->dataCombo.m_nBKColor       = BkColor;
    m_pCopyItem->dataCombo.m_eLibType       = eLibType;
    m_pCopyItem->dataCombo.m_strPath        = path;
    m_pCopyItem->dataCombo.m_bUseMacro      = ui->groupBox_5->isChecked();
    m_pCopyItem->dataCombo.m_strMacroName   = ui->comboBox_script_2->currentText();
    m_pCopyItem->dataCombo.m_bFirstLan      = ui->checkBox_lanFirst->isChecked();
    m_pCopyItem->dataCombo.m_vecStatus      = m_vecStatus;
    m_pCopyItem->dataCombo.m_vecLanguage    = m_vecLanguage;
    m_pCopyItem->setId(ui->spinBox_3->value());

    if(ui->spinBox_3->value() != oId && !pwnd->insertId(ui->spinBox_3->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox_3->setFocus();
        return ;
    }

    draw();

    this->accept();
}

void AkComboBox::on_cancel_clicked()
{
    this->close();
}

void AkComboBox::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_COMBOBOX);
}

void AkComboBox::on_btn_backcolor_2_clicked()//文本色
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);//
    pwnd->OnAddColorDlg(ui->btn_backcolor_2, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_text_color(const QColor &)));
}

void AkComboBox::set_text_color(const QColor & mColor)//文本色
{
    ui->btn_backcolor_2->setStyleSheet(QString("background:%1").arg(mColor.name()));

    TextColor = mColor;
    int k = ui->combo_Language->currentIndex();
    if(m_vecLanguage.size() > k)
    {
        m_vecLanguage[k].m_nTextColor = TextColor;
    }
    else
    {
        //k越界
        QMessageBox::about(this, tr("文本色"), tr("m_vecLanguage越界"));
    }
}

void AkComboBox::on_combo_Language_currentIndexChanged(int index)//语言切换
{
    if(!bInit)
    {
        return;
    }

    curLan = index;

    int num = QFontDatabase().families(QFontDatabase::Any).size();
    for(int i = 0; i < num; i++)
    {
        if(m_vecLanguage[index].m_strFontName == QFontDatabase().families(QFontDatabase::Any).at(i))
        {
            ui->comboBox_fontType->setCurrentIndex(i);
            break;
        }
    }
    ui->combo_Alignment->setCurrentIndex(m_vecLanguage[index].m_nAlign);
    ui->spinBox_2->setValue(m_vecLanguage[index].m_nFontSize);
    ui->btn_backcolor_2->setStyleSheet(QString("background:%1").arg(m_vecLanguage[index].m_nTextColor.name()));
    ui->checkBox->setChecked(m_vecLanguage[index].m_bCuTi);
    ui->checkBox_2->setChecked(m_vecLanguage[index].m_bXieTi);
    ui->checkBox_3->setChecked(m_vecLanguage[index].m_bXiaHuaXian);

    int temp = m_vecStatus.size();
    for(int i = 0; i < temp; i++)
    {
        int k = m_vecStatus[i].m_vecText.size();
        if(k < index)
        {
            QMessageBox::about(this, tr("错误"), tr("越界"));
            return;
        }
        QTableWidgetItem *item = ui->tableWidget->item(i, 1);
        item->setText(m_vecStatus[i].m_vecText[index]);

        if((ui->tableWidget->currentRow() == i) && pEdit && (ui->tableWidget->currentColumn() == 1))
        {
            pEdit->setText(m_vecStatus[i].m_vecText[index]);
        }
    }
}

void AkComboBox::on_combo_Alignment_activated(int index)//对齐
{
    if(!bInit)
    {
        return;
    }
    m_vecLanguage[curLan].m_nAlign = index;
}

void AkComboBox::on_comboBox_fontType_currentIndexChanged(QString str)//字体
{
    if(!bInit)
    {
        return;
    }
    m_vecLanguage[curLan].m_strFontName = str;
}

void AkComboBox::on_spinBox_2_valueChanged(int value)//字体大小
{
    if(!bInit)
    {
        return;
    }
    m_vecLanguage[curLan].m_nFontSize = value;
}

void AkComboBox::on_checkBox_clicked(bool checked)//粗体
{
    if(!bInit)
    {
        return;
    }
    m_vecLanguage[curLan].m_bCuTi = checked;
}

void AkComboBox::on_checkBox_2_clicked(bool checked)//斜体
{
    if(!bInit)
    {
        return;
    }
    m_vecLanguage[curLan].m_bXieTi = checked;
}

void AkComboBox::on_checkBox_3_clicked(bool checked)//下划线
{
    if(!bInit)
    {
        return;
    }
    m_vecLanguage[curLan].m_bXiaHuaXian = checked;
}

void AkComboBox::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if(!bInit)
    {
        return;
    }

    int row = currentRow;
    int column = currentColumn;
    if(row < 0 || column < 0)
    {
        //QMessageBox::about(this, tr("错误"), tr("越界1"));
        return;
    }

    int stateNum = m_vecStatus.size();
    if(row > stateNum - 1)
    {
        //QMessageBox::about(this, tr("错误"), tr("越界1"));
        return;
    }

    if(1 == previousColumn)//前一次
    {
        if(pEdit == NULL)
        {
            return;
        }
        m_str = pEdit->text();
        ui->tableWidget->removeCellWidget(previousRow, previousColumn);
        delete pEdit;
        pEdit = NULL;
        if(m_str != "")
        {
            ui->tableWidget->item(previousRow, previousColumn)->setText(m_str);
        }
        //emit redrawSence();
    }
    else if(0 == previousColumn)
    {
        if(pEdit == NULL)
        {
            return;
        }
        m_str = pEdit->text();
        ui->tableWidget->removeCellWidget(previousRow, previousColumn);
        delete pEdit;
        pEdit = NULL;
        //--检查m_str是不是数字
        if(m_str != "")
        {
            ui->tableWidget->item(previousRow, previousColumn)->setText(m_str);
        }
    }

    if(1 == currentColumn || 0 == currentColumn)//文本列
    {
        this->m_nEditRow = currentRow;
        this->m_nEditCol = currentColumn;

        pEdit = new QLineEdit;
        if(0 == currentColumn)
        {
            on_m_DataTypefontCmbBox_currentIndexChanged(ui->m_DataTypefontCmbBox->currentIndex());
        }

        int  width      = ui->tableWidget->columnWidth(currentColumn);
        int  height     = ui->tableWidget->rowHeight(currentRow);
        pEdit->resize(width, height);
        pEdit->setText(ui->tableWidget->item(currentRow, currentColumn)->text());
        ui->tableWidget->setCellWidget(currentRow, currentColumn, pEdit);

        connect(pEdit, SIGNAL(editingFinished()), this, SLOT(shit()));
    }
}

void AkComboBox::shit()//编辑完成LineEdit
{
    m_str = pEdit->text();
    if(0 == m_nEditCol)
    {
        m_vecStatus[m_nEditRow].m_value = m_str.toDouble();
    }
    else if(1 == m_nEditCol)
    {
        m_vecStatus[m_nEditRow].m_vecText[curLan] = m_str;
    }
}

void AkComboBox::draw()
{
    if(eLibType == NO_PIC)
    {
        QLineItem *pLineTemp;

        QPainterPath mPath1;
        mPath1.moveTo(0,0);         //画直线的起点
        mPath1.lineTo(108,0);         //画直线的终点
        pLineTemp = new QLineItem(mPath1);        //画细直线
        pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
        //pLineTemp->setAlpha(alpha);
        m_pCopyItem->addToGroup(pLineTemp);                   //添加到组
        pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QPainterPath mPath2;
        mPath2.moveTo(0,0);         //画直线的起点
        mPath2.lineTo(0,18);         //画直线的终点
        pLineTemp = new QLineItem(mPath2);        //画细直线
        pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
        //pLineTemp->setAlpha(alpha);
        m_pCopyItem->addToGroup(pLineTemp);                   //添加到组
        pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QPainterPath mPath3;
        mPath3.moveTo(108,0);         //画直线的起点
        mPath3.lineTo(108,18);         //画直线的终点
        pLineTemp = new QLineItem(mPath3);        //画细直线
        pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
        //pLineTemp->setAlpha(alpha);
        m_pCopyItem->addToGroup(pLineTemp);                   //添加到组
        pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QPainterPath mPath4;
        mPath4.moveTo(0,18);         //画直线的起点
        mPath4.lineTo(108,18);         //画直线的终点
        pLineTemp = new QLineItem(mPath4);        //画细直线
        pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
        //pLineTemp->setAlpha(alpha);
        m_pCopyItem->addToGroup(pLineTemp);                   //添加到组
        pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QRectF rect = QRectF(0,0,108,18);
        //rect = QRectF(0,0,108,18);
        //rect.setSize(QSize(108,18));//绘制外框矩形
        QRectItem* pRect = new QRectItem(rect);//
        pRect = new QRectItem(rect);
        pRect->SetLineColor(QColor(127,157,185));
        pRect->SetPattern(1);
        pRect->SetBackColor(BkColor);
        pRect->SetName("mFramRect");
        pRect->setZValue(1);
        pRect->SetAlpha(m_pCopyItem->dataCombo.m_nAlpha);
        //pRect->SetAlpha(250);
        m_pCopyItem->addToGroup(pRect);
        pRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

        rect.setTopLeft(QPointF(84,0));               //绘制背景矩形框
        rect.setSize(QSize(24,18));
        QRectItem* pBackRect = new QRectItem(rect);
        pBackRect->SetBackColor(QColor(183,211,252));
        pBackRect->SetLineType(0);
        pBackRect->SetName("mBackRect");
        pBackRect->setZValue(2);
        //pRect->SetBackColor(mColor);
        pBackRect->SetAlpha(m_pCopyItem->dataCombo.m_nAlpha);
        //pRect->SetAlpha(250);
        m_pCopyItem->addToGroup(pBackRect);
        pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QPainterPath mPenPath = QPainterPath();
        mPenPath.moveTo(QPointF(90,7));//第一点
        mPenPath.lineTo(QPointF(96,11));
        mPenPath.lineTo(QPointF(102,7));
        QFoldLineItem* pLine = new QFoldLineItem(mPenPath);
        pLine->setLineType(1);
        pLine->setLineWidth(2); //设置线条宽度
        pLine->setLineColor(QColor(77,97,133)); //线条颜色
        pLine->SetName("mLine");
        pLine->setZValue(4);
        //pLine->setAlpha(alpha);
        m_pCopyItem->addToGroup(pLine);
        pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
    else if(eLibType == PIC)
    {
        QRectF rect = QRectF(0,0,100,100);
        if(!m_pCopyItem->backItem)//背景图片指针为空，不操作直接返回
        {
            QRectItem *rectItem = new QRectItem(rect);
            m_pCopyItem->backItem = rectItem;
        }

        QPixmap picture(path);
        if(picture.isNull())
        {
            picture.load(":/btn/images/default.png");
            if(picture.isNull())
            {
                return;
            }
        }
        QPixmapItem *pixItem = new QPixmapItem(picture,QSize(rect.width(),rect.height()));

        QPointF pos = m_pCopyItem->backItem->sceneBoundingRect().topLeft();
        QPointF pt = pixItem->boundingRect().topLeft();
        pixItem->setPos(pos-pt);

        QGraphicsItem *pItem = m_pCopyItem->topLevelItem();
        QItemGroup *pArentItem = dynamic_cast<QItemGroup *> (pItem);
        if(pArentItem)
        {
            pArentItem->removeFromGroup(m_pCopyItem->backItem);
        }

        m_pCopyItem->backItem = pixItem;
        m_pCopyItem->addToGroup(m_pCopyItem->backItem);
    }
    else
    {
        QRectF rect = QRectF(0,0,100,100);
        if(!m_pCopyItem->backItem)//背景图片指针为空，不操作直接返回
        {
            QRectItem *rectItem = new QRectItem(rect);
            m_pCopyItem->backItem = rectItem;
        }

        DrawItemToScene GroupFunction;
        QList <QGraphicsItem*> listItem;
        QStringList str = path.split('-');
        if(str.isEmpty())
        {
            return;
        }
        QGraphicsItem *pCopyItem = NULL;
        int nLoadPag = str.at(0).toInt();

        if(1 == str.at(2).toInt())
        {
            if(pwnd->vBaseLibraryScene.isEmpty())
            {
                return;
            }
            listItem = pwnd->vBaseLibraryScene.at(nLoadPag)->TopItems();
            foreach (QGraphicsItem *pItem, listItem)
            {
                QString sname = pItem->data(GROUP_NAME_KEY).toString();
                if (path == sname)
                {
                    GroupFunction.CopyItem(&pCopyItem, pItem);
                    break;
                }
            }
        }

        if(!pCopyItem)
        {
            return;
        }

        QGroupItem *pBaseItem = new QGroupItem(pCopyItem);
        pBaseItem->SetWidth(m_pCopyItem->backItem->boundingRect().width());
        pBaseItem->SetHeigth(m_pCopyItem->backItem->boundingRect().height());
        QPointF pos = m_pCopyItem->backItem->sceneBoundingRect().topLeft();
        QPointF pt = pCopyItem->boundingRect().topLeft();
        pCopyItem->setPos(pos-pt);
        //pCopyItem->setData(GROUP_NAME_KEY,QVariant(SWITCH_BACK_TYPE));

        QGraphicsItem *pItem = m_pCopyItem->topLevelItem();
        QItemGroup *pArentItem = dynamic_cast<QItemGroup *> (pItem);
        if(pArentItem)
        {
            pArentItem->removeFromGroup(m_pCopyItem->backItem);
        }

        /*if(scene())
        {
            scene()->removeItem(backItem);
            scene()->removeItem(textItem);
        }*/

        m_pCopyItem->backItem = pCopyItem;
        m_pCopyItem->backItem->setFlag(QGraphicsItem::ItemIsMovable,true);
        m_pCopyItem->backItem->setFlag(QGraphicsItem::ItemIsSelectable,false);
        m_pCopyItem->addToGroup(m_pCopyItem->backItem);
    }
}

void AkComboBox::drawScene()
{
    if(eLibType == NO_PIC)
    {
        /*if(pTempItem)
        {
            delete pTempItem;
            pTempItem = NULL;
        }*/
        pTempItem = new AkComboItem;

        QRectF rect = QRectF(0,0,108,18);
        //rect.setSize(QSize(108,18));//绘制外框矩形
        pRect = new QRectItem(rect);//
        pRect->SetLineColor(QColor(127,157,185));
        pRect->SetPattern(1);
        pRect->SetBackColor(BkColor);
        pRect->SetName("mFramRect");
        pRect->setZValue(1);
        pRect->SetAlpha(ui->spin_Trans->value());
        pTempItem->addToGroup(pRect);
        //addToGroup(pRect);
        pRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

        rect.setTopLeft(QPointF(84,0));               //绘制背景矩形框
        rect.setSize(QSize(24,18));
        pBackRect = new QRectItem(rect);
        pBackRect->SetBackColor(QColor(183,211,252));
        pBackRect->SetLineType(0);
        pBackRect->SetName("mBackRect");
        pBackRect->setZValue(2);
        pBackRect->SetAlpha(ui->spin_Trans->value());
        pTempItem->addToGroup(pBackRect);
        //addToGroup(pBackRect);
        pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QPainterPath mPenPath = QPainterPath();
        mPenPath.moveTo(QPointF(90,7));//第一点
        mPenPath.lineTo(QPointF(96,11));
        mPenPath.lineTo(QPointF(102,7));
        pLine = new QFoldLineItem(mPenPath);
        pLine->setLineType(1);
        pLine->setLineWidth(2); //设置线条宽度
        pLine->setLineColor(QColor(77,97,133)); //线条颜色
        pLine->SetName("mLine");
        pLine->setZValue(4);
        //pLine->setAlpha(alpha);
        pTempItem->addToGroup(pLine);
        //addToGroup(pLine);
        pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

        QLineItem *pLineTemp;

        QPainterPath mPath1;
        mPath1.moveTo(0,0);         //画直线的起点
        mPath1.lineTo(108,0);         //画直线的终点
        pLineTemp = new QLineItem(mPath1);        //画细直线
        pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
        pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pTempItem->addToGroup(pLineTemp);                   //添加到组

        QPainterPath mPath2;
        mPath2.moveTo(0,0);         //画直线的起点
        mPath2.lineTo(0,18);         //画直线的终点
        pLineTemp = new QLineItem(mPath2);        //画细直线
        pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
        pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pTempItem->addToGroup(pLineTemp);                   //添加到组

        QPainterPath mPath3;
        mPath3.moveTo(108,0);         //画直线的起点
        mPath3.lineTo(108,18);         //画直线的终点
        pLineTemp = new QLineItem(mPath3);        //画细直线
        pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
        pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pTempItem->addToGroup(pLineTemp);                   //添加到组

        QPainterPath mPath4;
        mPath4.moveTo(0,18);         //画直线的起点
        mPath4.lineTo(108,18);         //画直线的终点
        pLineTemp = new QLineItem(mPath4);        //画细直线
        pLineTemp->setLineColor(QColor(127,157,185));     //设置直线颜色
        pLineTemp->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pTempItem->addToGroup(pLineTemp);                   //添加到组

        if(pScene)
        {
            pScene->clear();
            pScene->addItem(pTempItem);        //添加到场景
        }

        pTempItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pTempItem->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
    else if(eLibType == PIC)
    {
        QPixmap picture(path);
        picture = picture.scaled(108,18);
        pScene->clear();
        pScene->addPixmap(picture);
    }
    else//
    {
        QGraphicsItem *pCopyItem = NULL;
        QGraphicsItem *pNewItem = NULL;
        //QPointF pos = pCopyItem->sceneBoundingRect().topLeft();
        //QString path = path;
        DrawItemToScene GroupFunction;
        QList <QGraphicsItem*> listItem;
        QStringList str = path.split('-');
        if(str.isEmpty())
        {
            return;
        }
        int nLoadPag = str.at(0).toInt();

        if(1 == str.at(2).toInt())
        {
            if(pwnd->vBaseLibraryScene.isEmpty())
            {
                return;
            }
            listItem = pwnd->vBaseLibraryScene.at(nLoadPag)->TopItems();
            foreach (QGraphicsItem * pItem, listItem)
            {
                QString sname = pItem->data(GROUP_NAME_KEY).toString();
                if (path == sname)
                {
                    GroupFunction.CopyItem(&pNewItem,pItem);
                    break;
                }
            }
        }
        if(!pNewItem)
        {
            return;
        }
        QPointF newpos(0,0);
        pScene->clear();
        pCopyItem = pNewItem;
        pBaseItem = new QGroupItem(pCopyItem);
        pBaseItem->SetWidth(108);
        pBaseItem->SetHeigth(18);
        pScene->addItem(pCopyItem);
        pCopyItem->setPos(newpos - pCopyItem->boundingRect().topLeft());
    }
}

void AkComboBox::on_spin_Trans_valueChanged(int value)
{
    drawScene();
}

void AkComboBox::on_m_DataTypefontCmbBox_currentIndexChanged(int index)
{
    DoubleValidator *validator = new DoubleValidator(-32768,32767,5,this);

    switch(index)
    {
        case 0://16位整数
        {
            validator = new DoubleValidator(-32768,32767,5,this);
        }
        break;
        case 1://32位整数
        {
            double dMax=2147483648L;
            double dMin=-2147483647L;
            validator = new DoubleValidator(dMin,dMax,5,this);
        }
        break;
        case 2://16位正整数
        {
            validator = new DoubleValidator(0,65535,5,this);
        }
        break;
        case 3://32位正整数
        {
            double dMax=4294967295L;
            double dMin=0;
            validator = new DoubleValidator(dMin,dMax,5,this);
        }
        break;
        case 4://16位BCD码
        {
            validator = new DoubleValidator(0,9999,4,this);
        }
        break;
        case 5://32位BCD码
        {
            validator = new DoubleValidator(0,99999999,8,this);
        }
        break;
        case 6://32位浮点数
        {
            double dMax=2147483648L;
            double dMin=-2147483647L;
            validator = new DoubleValidator(dMin,dMax,5,this);
        }
        break;
    }

    if(pEdit && (0 == m_nEditCol))
    {
        this->pEdit->setValidator(validator);
    }
    //ui->inputMax->setValidator(validator);
    //ui->inputMin->setValidator(validator);
    //ui->outputMax->setValidator(validator);
    //ui->outputMin->setValidator(validator);
}
