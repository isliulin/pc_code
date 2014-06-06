#include "qtreectrlrecipedlg.h"
#include <QAbstractScrollArea>
#include <QModelIndexList>
#include <QItemSelection>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include  "Frame\mainwindow.h"
#include "alarmdlg.h"
extern MainWindow *pwnd;

#define ELMENTNAME "elment"
#define RICIPENAME "Recipe"
QTreeCtrlRecipeDlg::QTreeCtrlRecipeDlg(QWidget *parent,int index) :
        QDialog(parent),
        ui(new Ui::QTreeCtrlRecipeDlg)
{
    bInitflag = false;
    nIndex = index;
    formula.clear();
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    connect(ui->m_cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->m_helpBtn, SIGNAL(clicked()), this, SLOT(loadHelp()));
    connect(ui->m_okBtn, SIGNAL(clicked()), this, SLOT(confyButton()));

    //ui->m_CopyDatepushBtn->hide();
    ui->m_AddPripushBtn->setEnabled(false);
    ui->m_DeletePripushBtn->setEnabled(false);
    ui->m_AddPripushBtn->setVisible(false);
    ui->m_DeletePripushBtn->setVisible(false);

    //语言
    QVector<QString>language_vector;
        int languageCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();

        for(int i=0; i<languageCount; i++)
        {
            language_vector.push_back(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
        }
        for(int i=0; i<languageCount; i++)
        {
            ui->m_LanguageCmBox->addItem(language_vector.at(i));
        }

    //地址
    ui->m_writeaddresslineEdit->setText("LW0");
    ui->m_BitaddresslineEdit->setText("LB0");
    ui->m_IAddrlineEdit->setText("LW0");

    //表格
    ui->m_tableWidget->verticalHeader()->setVisible(false);

    ui->m_keyspBox->clear();
    int totalNum = pwnd->pSceneSheet.size();
    bool bfalg = false;
    int nWidth = 0;
    int nHight = 0;
    for(int i = 0; i< totalNum; i++)
    {
        if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 2)
        {
            if(!bfalg)
            {
                nWidth = pwnd->pSceneSheet[i]->width();
                nHight = pwnd->pSceneSheet[i]->height();
            }
            bfalg = true;
            ui->m_keyspBox->addItem(pwnd->pSceneSheet[i]->sNewScreenName);
        }
    }
    if(!bfalg)
    {
        ui->m_KeygroupBox->setEnabled(false);
        ui->m_keyspBox->setEnabled(false);
        ui->m_PouupckBox->setChecked(false);
        ui->m_PouupckBox->setEnabled(false);
    }
    else
    {
        ui->m_PouupckBox->setChecked(true);
        ui->m_PouupckBox->setEnabled(true);
        on_m_PouupckBox_clicked(true);
    }
    int nxValue = pwnd->m_pSamSysParame->m_projectProp.nSceneWidth - nWidth;
    int nyValue = pwnd->m_pSamSysParame->m_projectProp.nSceneHeight - nHight ;

    ui->m_xKeyspinBox->setRange(0,nxValue);
    ui->m_yKeyspinBox->setRange(0,nyValue);
    ui->m_xKeyspinBox->setValue(pwnd->m_pSamSysParame->m_projectProp.nSceneWidth/2 - nWidth/2);
    ui->m_yKeyspinBox->setValue(pwnd->m_pSamSysParame->m_projectProp.nSceneHeight/2 - nHight/2);

    Init();
    ui->m_IAddrlineEdit->setReadOnly(true);
    ui->m_okBtn->setFocus();
    ui->m_okBtn->installEventFilter(this);
    //ui->m_cancelBtn->installEventFilter(this);
    //ui->m_helpBtn->installEventFilter(this);
    ui->m_AddPripushBtn->installEventFilter(this);
    ui->m_DeletePripushBtn->installEventFilter(this);
    ui->m_tabWidget->installEventFilter(this);
    ui->recipesize_spinBox->installEventFilter(this);
    ui->m_IradioBtn->installEventFilter(this);
    ui->M_CradioBtn->installEventFilter(this);
    ui->datestyle_comboBox->installEventFilter(this);
    ui->m_IAddrlineEdit->installEventFilter(this);
    ui->m_IaddrpushBtn->installEventFilter(this);
    ui->m_namelineEdit_2->installEventFilter(this);
    ui->recipeoutput_pushButton->installEventFilter(this);
    ui->recipeintput_pushButton->installEventFilter(this);
}

QTreeCtrlRecipeDlg::~QTreeCtrlRecipeDlg()
{
    delete ui;
}

void QTreeCtrlRecipeDlg::Init()
{
    formula = pwnd->m_pSamSysParame->m_qRecipe.formula;
    Pro = pwnd->m_pSamSysParame->m_qRecipe;
    if("" == Pro.sName)
    {
        Pro.ElmentName.clear();
        Pro.formula.clear();
        QString str = ELMENTNAME;
        int nRow = ui->recipesize_spinBox->value();
        if(nRow < 0)
        {
            return;
        }
        if(524288/nRow >= 128)//若所得数值小于128
        {
            ui->recipe_spinBox->setMaximum(512);
        }
        else
        {
            ui->recipe_spinBox->setMaximum(128);//配方长度最大值为128
        }

        ui->m_tableWidget->setRowCount(nRow);
        for(int i = 0; i < nRow; i++)
        {
            str = str + QString("%1").arg(i);
            ui->m_tableWidget->setItem(i,0,new QTableWidgetItem(str));

            //元素多语言begin
            int index = ui->m_LanguageCmBox->count();
            QVector<RECIPEElEMENT> elment;
            elment.resize(index);
            for(int i = 0; i< index; i++)
            {
                elment[i].sElemName = str;
                elment[i].nLanguageId = i;
            }
            Pro.ElmentName.append(elment);
            //元素多语言end

            if(ui->m_IradioBtn->isChecked())
            {
                on_m_IradioBtn_clicked(true);
            }
            else
            {
                on_M_CradioBtn_clicked(true);
            }
            str = ELMENTNAME;
        }
        on_m_AddPripushBtn_clicked();

        if(!ui->m_PouupckBox->isEnabled())
        {
            on_m_PouupckBox_clicked(false);
        }
        on_m_writeaddressCkBox_clicked(ui->m_writeaddressCkBox->isChecked());
        on_m_TransRecipeCkBox_clicked(ui->m_TransRecipeCkBox->isChecked());
    }
    else
    {
        ui->m_namelineEdit->setText(Pro.sName);
        ui->edit_text->setPlainText(Pro.sRecipeGDescri);//描述
        ui->m_LanguageCmBox->setCurrentIndex(Pro.nLanguageId);//语言
        ui->m_writeaddressCkBox->setChecked(Pro.bCtlAddr);//是否需要控制地址
        on_m_writeaddressCkBox_clicked(Pro.bCtlAddr);
        ui->m_writeaddresslineEdit->setText(Pro.addrCtl.sShowAddr);//控制地址
        //ui->m_TrangroupBox->setChecked(Pro.bTransRecipe);
//        if(1 == Pro.eRecipeTransType)//可读写
//        {
//            ui->m_WriteReadradioBtn->setChecked(true);

//        }
//        else if(2 == Pro.eRecipeTransType)//从PLC读
//        {
//            ui->m_ReadPLCradioBtn->setChecked(true);
//        }
//        else
//        {
//            ui->m_WritePLCradioBTN->setChecked(true);
//        }
        ui->m_TransRecipeCkBox->setChecked(Pro.bCompleteNotic);//是否需要传出完成通知地址
        on_m_TransRecipeCkBox_clicked(Pro.bCompleteNotic);
        ui->m_BitaddresslineEdit->setText(Pro.addrNotic.sShowAddr);//位通知地址
        if(1 == Pro.eSaveMedia)//内部存储区
        {
            ui->m_RameradioBtn->setChecked(true);
        }
        else if(2 == Pro.eSaveMedia)//u盘
        {
            ui->m_UradioBtn->setChecked(true);
        }
        else
        {
            ui->m_SDradioBtn->setChecked(true);
        }
        ui->recipesize_spinBox->setValue(Pro.nRecipeLen);
        if(Pro.bContniu)//连续随即
        {
            ui->m_IradioBtn->setChecked(true);
            on_m_IradioBtn_clicked(true);
        }
        else
        {
            ui->M_CradioBtn->setChecked(true);
            on_M_CradioBtn_clicked(true);
        }
        ui->datestyle_comboBox->setCurrentIndex(Pro.eDataType);//数据类别
        ui->m_IAddrlineEdit->setText(Pro.sContniuAddr);//连续地址

        //
        int nColoum = formula.size(); //配方个数
        if(nColoum <= 0)
        {
            on_recipesize_spinBox_valueChanged(4);
            return;
        }
        int nRow = formula[0].elment.size();
        ui->m_tableWidget->setRowCount(nRow);

        int nTotal = 524288/nRow;
        if(nTotal >= 128 && nTotal <= 512)//若所得数值小于128
        {
            ui->recipe_spinBox->setMaximum(nTotal);
        }
        else if(nTotal > 512)
        {
            ui->recipe_spinBox->setMaximum(512);
        }
        else
        {
            ui->recipe_spinBox->setMaximum(128);//配方长度最大值为128
        }
        ui->recipe_spinBox->setValue(nColoum);

        ui->m_tableWidget->setColumnCount(nColoum + 3);;

        for(int i = 0; i < nColoum; i++)
        {

            //QString str = formula[i].sFormulaName;
            QString str = formula[i].RecipeInfo[Pro.nLanguageId].sRecipeName;
            QTableWidgetItem *newitem = new QTableWidgetItem(str);
            ui->m_tableWidget->setHorizontalHeaderItem(i + 3,newitem);
            for(int j = 0; j < nRow; j++)
            {
                if(0 == i)
                {
                    //QString str = formula[i].elment[j].sName;
                    str = Pro.ElmentName[j].at(Pro.nLanguageId).sElemName;
                    QTableWidgetItem *newitem = new QTableWidgetItem(str);
                    ui->m_tableWidget->setItem(j,0,newitem);

                    str = formula[i].elment[j].addr.sShowAddr;
                    newitem = new QTableWidgetItem(str);
                    ui->m_tableWidget->setItem(j,1,newitem);
                    if(ui->m_IradioBtn->isChecked())
                    {
                        newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));
                    }

                    str = formula[i].elment[j].sAddrType;
                    newitem = new QTableWidgetItem(str);
                    ui->m_tableWidget->setItem(j,2,newitem);
                    if(ui->m_IradioBtn->isChecked())
                    {
                        newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));
                    }
                }

//                QString str = QString::number(formula[i].elment[j].sText);
//                if(0 == formula[i].elment[j].sText)
//                {
//                   str = "";
//                }
                QTableWidgetItem *newitem = new QTableWidgetItem(formula[i].elment[j].sText);
                ui->m_tableWidget->setItem(j,i + 3,newitem);
            }
        }

        ui->m_PouupckBox->setChecked(Pro.nKeyMark);
        ui->m_keyspBox->setCurrentIndex(Pro.nKeyId);
        on_m_keyspBox_currentIndexChanged(Pro.nKeyId);
        ui->m_xKeyspinBox->setValue(Pro.nBoardX);
        ui->m_yKeyspinBox->setValue(Pro.nBoardY);

    }
    on_m_PouupckBox_clicked(ui->m_PouupckBox->isChecked());
    refreshTableItem();
    bInitflag = true;
}

void QTreeCtrlRecipeDlg::confyButton()
{
    if(!ui->m_PouupckBox->isChecked())
    {
        QMessageBox box(QMessageBox::Information,tr("警告"),tr("没有选择键盘将默认为系统键盘！"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("确定"));
        box.button(QMessageBox::Cancel)->setText(tr("取消"));
        box.exec();
        if(box.clickedButton() == box.button(QMessageBox::Cancel))
        {
            return;
        }
    }

    if(!onSaveInfo())
    {
        return;
    }
    accept();
}

void QTreeCtrlRecipeDlg::loadHelp()
{

}

void QTreeCtrlRecipeDlg::on_m_TransRecipeCkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->m_Bitaddresslabel->setEnabled(true);
        ui->m_BitaddresslineEdit->setEnabled(true);
        ui->m_BitaddresspushBtn->setEnabled(true);
    }
    else
    {
        ui->m_Bitaddresslabel->setEnabled(false);
        ui->m_BitaddresslineEdit->setEnabled(false);
        ui->m_BitaddresspushBtn->setEnabled(false);
    }
}

void QTreeCtrlRecipeDlg::on_m_AddPripushBtn_clicked()
{
    QString sRecipname = RICIPENAME;
    int nCount = ui->m_tableWidget->columnCount();
    ui->m_tableWidget->insertColumn(nCount);
    sRecipname =sRecipname + QString("%1").arg(nCount - 3);
    QTableWidgetItem *newitem = new QTableWidgetItem(sRecipname);
    ui->m_tableWidget->setHorizontalHeaderItem(nCount,newitem);

    FORMULA_ST recipe;
    int index  = ui->m_LanguageCmBox->count();
    recipe.RecipeInfo.resize(index);
    for(int i = 0; i < index; i++)
    {
        recipe.RecipeInfo[i].nLanguageId = i;
        recipe.RecipeInfo[i].sRecipeDescri = "";
        recipe.RecipeInfo[i].sRecipeName = sRecipname;
    }
    formula.append(recipe);
    return;


    int nRowCount = ui->m_tableWidget->rowCount();
    if(nRowCount <= 0)
    {
        nRowCount = 0;
    }
    ui->m_tableWidget->insertRow(nRowCount);
    QString str = "Recipe";
    str = str + QString("%1").arg(nRowCount);
    ui->m_tableWidget->setItem(nRowCount,0,new QTableWidgetItem(str));

    if(ui->M_CradioBtn->isChecked())
    {
        QTableWidgetItem *newitem = new QTableWidgetItem(tr("16位整数"));
        ui->m_tableWidget->setItem(nRowCount,2,newitem);
        newitem->setFlags(newitem->flags() | Qt::ItemIsEditable);
    }
    else if(ui->m_IradioBtn->isChecked())//连续
    {
        QTableWidgetItem *newitem;
        if(tr("位") == ui->datestyle_comboBox->currentText())
        {
            newitem = new QTableWidgetItem(ui->datestyle_comboBox->currentText());
            ui->m_tableWidget->setItem(nRowCount,2,newitem);
        }
        else
        {
            newitem = new QTableWidgetItem(ui->datestyle_comboBox->currentText());
            ui->m_tableWidget->setItem(nRowCount,2,newitem);
        }
        newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));


        newitem = ui->m_tableWidget->item(nRowCount,1);
        if(newitem)
        {
            newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));
        }
        else
        {
            newitem = new QTableWidgetItem("");
            newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));
            ui->m_tableWidget->setItem(nRowCount,1,newitem);
        }
    }
}

void QTreeCtrlRecipeDlg::on_m_DeletePripushBtn_clicked()
{
    int nCount = ui->m_tableWidget->columnCount();
    int nCurrent = ui->m_tableWidget->currentColumn();
    if(nCount <= 2 || nCurrent <= 2)
    {
        return;
    }
    ui->m_tableWidget->removeColumn(nCurrent);

    if(nCurrent - 3 < formula.size())
    {
        formula.remove(nCurrent - 3);
    }
}

void QTreeCtrlRecipeDlg::on_m_tableWidget_cellDoubleClicked(int row, int column)
{
    QString txt;
    QTableWidgetItem *item = ui->m_tableWidget->item(row,column);

    if(item)
    {
        txt = item->text();
    }

    int  width      = ui->m_tableWidget->columnWidth(column);
    int  height     = ui->m_tableWidget->rowHeight(row);

    if(ui->M_CradioBtn->isChecked())
    {
        if(column == 1)//双击选择地址列
        {
            int type = 1;
            QTableWidgetItem *pItem = ui->m_tableWidget->item(row,2);
            if(pItem)
            {
                if(tr("位") == pItem->text())
                {
                   type = 0;
                }
                else
                {
                    type = 1;
                }
            }
            AddWidget *wgt = new AddWidget(width,height,type,this);
            ui->m_tableWidget->setCellWidget(row,column,wgt);

            if(txt.isEmpty())
            {
                if(1 == type)
                {
                   txt = "LW0";
                }
                else
                {
                    txt = "LB0";
                }
            }
            wgt->setEditFocus(txt);
        }
        else if(column == 2)//双击选择地址类型
        {
            QComboBox *combox = new QComboBox(this);
            combox->setBaseSize(width,height);
            QListView* view = (QListView*)combox->view();
            view->setSpacing(3);
            QStringList values;
            values <<tr("16位整数") <<tr("16位正整数") <<tr("32位整数") <<tr("32位正整数")
                    <<tr("32位浮点数") <<tr("16位BCD码") <<tr("32位BCD码") <<tr("位");
            combox->addItems(values);
            combox->setCurrentIndex(0);

            int index = combox->findText(txt);
            if(index != -1)
            {
                combox->setCurrentIndex(index);
            }
            ui->m_tableWidget->setCellWidget(row,column,combox);

            if(txt.isEmpty()){
                QTableWidgetItem *newitem = new QTableWidgetItem("LW0");
                ui->m_tableWidget->setItem(row,1,newitem);
            }

        }
    }
    else if(ui->m_IradioBtn->isChecked() && 1 == column)
    {
        if(!onSetAddress())
        {
            return;
        }
    }
    if(column >= 3)
    {
        QTableWidgetItem *newitem = ui->m_tableWidget->item(row,2);
        QString str;
        int ntype;
        if(newitem)
        {
            str = newitem->text();
        }
        else
        {
            return;
        }
        if(tr("16位整数") == str)
        {
            ntype = 0;
        }
        else if(tr("16位正整数") == str)
        {
            ntype = 1;
        }
        else if(tr("32位整数") == str)
        {
            ntype = 2;
        }
        else if(tr("32位正整数") == str)
        {
            ntype = 3;
        }
        else if(tr("32位浮点数") == str)
        {
            ntype = 4;
        }
        else if(tr("16位BCD码") == str)
        {
            ntype = 5;
        }
        else if(tr("32位BCD码") == str)
        {
            ntype = 6;
        }
        else if(tr("位") == str)
        {
            ntype = 7;
        }
        onLimitDataInput(ntype,row,column);

    }
}

void QTreeCtrlRecipeDlg::on_m_tableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    QTableWidgetItem *pHitem = NULL;
    if(currentColumn > 2)
    {
        pHitem = ui->m_tableWidget->horizontalHeaderItem(currentColumn);
        if(pHitem)
        {
            ui->m_namelineEdit_2->setText(pHitem->text());
            ui->m_namelineEdit_2->setEnabled(true);
        }
    }
    else
    {
        ui->m_namelineEdit_2->setText("");
        ui->m_namelineEdit_2->setEnabled(false);
    }
    if(currentColumn > 2 && (currentRow != previousRow && currentColumn != previousColumn))
    {
        if(currentRow >= 0)
        {
            pHitem = ui->m_tableWidget->item(currentRow,currentColumn);
            if(pHitem)
            {
                pHitem->setFlags(pHitem->flags() & (~Qt::ItemIsEditable));
            }
            else
            {
                pHitem = new QTableWidgetItem("");
                pHitem->setFlags(pHitem->flags() & (~Qt::ItemIsEditable));
                ui->m_tableWidget->setItem(currentRow,currentColumn,pHitem);
            }
        }
        QTableWidgetItem *newitem = ui->m_tableWidget->item(currentRow,2);
        QString str;
        int ntype;
        if(newitem)
        {
            str = newitem->text();
            if(tr("16位整数") == str)
            {
                ntype = 0;
            }
            else if(tr("16位正整数") == str)
            {
                ntype = 1;
            }
            else if(tr("32位整数") == str)
            {
                ntype = 2;
            }
            else if(tr("32位正整数") == str)
            {
                ntype = 3;
            }
            else if(tr("32位浮点数") == str)
            {
                ntype = 4;
            }
            else if(tr("16位BCD码") == str)
            {
                ntype = 5;
            }
            else if(tr("32位BCD码") == str)
            {
                ntype = 6;
            }
            else if(tr("位") == str)
            {
                ntype = 7;
            }
            onLimitDataInput(ntype,currentRow,currentColumn);
        }

    }
    if(ui->M_CradioBtn->isChecked())//随机
    {
        QTableWidgetItem *oItem = ui->m_tableWidget->item(previousRow,2);
        QString str;
        if(!oItem)
        {
            return;
        }
        else
        {
            str = oItem->text();
        }
        if(tr("16位整数") == str || tr("16位正整数") == str || tr("32位整数") == str
           || tr("32位正整数") == str || tr("32位浮点数") == str || tr("16位BCD码") == str
           || tr("32位BCD码") == str)
        {
            CellChanged_Word(currentRow,currentColumn,previousRow,previousColumn);
        }
        else if(tr("位") == str)
        {
            CellChanged_Bit(currentRow,currentColumn,previousRow,previousColumn);
        }
        else if("" == str)
        {
            QWidget *wgt = ui->m_tableWidget->cellWidget(previousRow,previousColumn);
            if(wgt)
            {
                ui->m_tableWidget->removeCellWidget(previousRow,1);
                wgt->deleteLater();
                wgt = NULL;
            }
        }
    }
    else if(ui->m_IradioBtn->isChecked())//连续
    {

    }
    if(previousColumn >= 3)
    {
        QWidget *wgt = ui->m_tableWidget->cellWidget(previousRow,previousColumn);
        QLineEdit *pEdit = dynamic_cast<QLineEdit *>(wgt);
        if(pEdit)
        {
            QString str = pEdit->text();
            QTableWidgetItem *oItem = ui->m_tableWidget->item(previousRow,previousColumn);
            if(!oItem)
            {
                oItem = new QTableWidgetItem;
            }
            oItem->setText(str);
            ui->m_tableWidget->setItem(previousRow,previousColumn,oItem);
            ui->m_tableWidget->removeCellWidget(previousRow,previousColumn);
            pEdit->deleteLater();
            pEdit = NULL;
        }
    }

}

void QTreeCtrlRecipeDlg::CellChanged_Bit(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if(previousColumn == 1)
    {
        QWidget *wgt = ui->m_tableWidget->cellWidget(previousRow,previousColumn);
        AddWidget *addrWgt = dynamic_cast<AddWidget *>(wgt);
        QString str;
        if(addrWgt)
        {
            if(!addrWgt->check(0))
            {
                ui->m_tableWidget->setCurrentCell(previousRow,previousColumn,QItemSelectionModel::NoUpdate);

                return;
            }
            str = addrWgt->getString();
            ui->m_tableWidget->removeCellWidget(previousRow,previousColumn);
            wgt->deleteLater();
        }
        else
        {
            QTableWidgetItem *oItem = ui->m_tableWidget->item(previousRow,previousColumn);
            if(oItem)
                str = oItem->text();
        }

        if(str.isEmpty())
        {
            //删除一行数据
            QTableWidgetItem *oItem = ui->m_tableWidget->item(previousRow,1);
            if(oItem)
                oItem->setText("");
        }
        else
        {
            QTableWidgetItem *newitem = new QTableWidgetItem(str);
            ui->m_tableWidget->setItem(previousRow,previousColumn,newitem);
        }
    }
    else if(previousColumn == 2)
    {
        QString str;
        QWidget *wgt = ui->m_tableWidget->cellWidget(previousRow,previousColumn);
        QComboBox *combox = dynamic_cast<QComboBox *>(wgt);
        if(combox)
        {
            str = combox->currentText();
            ui->m_tableWidget->removeCellWidget(previousRow,previousColumn);
            wgt->deleteLater();
        }
        else
        {
            QTableWidgetItem *oItem = ui->m_tableWidget->item(previousRow,previousColumn);
            if(oItem)
                str = oItem->text();
        }
        QTableWidgetItem *newitem = new QTableWidgetItem(str);
        ui->m_tableWidget->setItem(previousRow,previousColumn,newitem);
    }
}

//选择字地址报警登录的时候 对itemchanged的处理
void QTreeCtrlRecipeDlg::CellChanged_Word(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    if(previousColumn == 1)
    {
        QWidget *wgt = ui->m_tableWidget->cellWidget(previousRow,previousColumn);
        AddWidget *addrWgt = dynamic_cast<AddWidget *>(wgt);
        QString str;
        if(addrWgt)
        {
            str = addrWgt->getString();
            if(!addrWgt->check(1))
            {
                ui->m_tableWidget->setCurrentCell(previousRow,previousColumn,QItemSelectionModel::NoUpdate);

                return;
            }
            ui->m_tableWidget->removeCellWidget(previousRow,previousColumn);
            wgt->deleteLater();

        }
        else
        {
            QTableWidgetItem *oItem = ui->m_tableWidget->item(previousRow,previousColumn);
            if(oItem)
                str = oItem->text();
        }

        if(str.isEmpty())
        {
            //删除一行数据
            QTableWidgetItem *oItem = ui->m_tableWidget->item(previousRow,1);
            if(oItem)
                oItem->setText("");
        }
        else
        {
            QTableWidgetItem *newitem = new QTableWidgetItem(str);
            ui->m_tableWidget->setItem(previousRow,previousColumn,newitem);
        }
    }
    else if(previousColumn == 2)
    {
        QString str;
        QWidget *wgt = ui->m_tableWidget->cellWidget(previousRow,previousColumn);
        QComboBox *condwgt = dynamic_cast<QComboBox *>(wgt);
        if(condwgt)
        {
            str = condwgt->currentText();
            ui->m_tableWidget->removeCellWidget(previousRow,previousColumn);
            wgt->deleteLater();
        }
        else
        {
            QTableWidgetItem *oItem = ui->m_tableWidget->item(previousRow,previousColumn);
            if(oItem)
                str = oItem->text();
        }
        QTableWidgetItem *newitem = new QTableWidgetItem(str);
        ui->m_tableWidget->setItem(previousRow,previousColumn,newitem);

        /*QLineEdit *lineEdit = new QLineEdit;
        int nAddrType = 0;
        QString sAddr;
        QTableWidgetItem *item = ui->m_tableWidget->item(previousRow,previousColumn -1);
        if(item)
        {
            if("" == item->text())
            {
                lineEdit->deleteLater();
                return;
            }
            lineEdit->setText(item->text());
            item = ui->m_tableWidget->item(previousRow,previousColumn);
            if(item)
            {
                if(tr("位") == item->text())
                {
                    nAddrType = 0;
                    sAddr = tr("位地址");
                }
                else
                {
                    nAddrType = 1;
                    sAddr = tr("字地址");
                }
                if(! pwnd->IsAddressCheckRight(Address_Keyboard,sAddr,lineEdit,nAddrType))
                {
                    ui->m_tableWidget->setCurrentCell(previousRow,previousColumn -1,QItemSelectionModel::NoUpdate);
                    //ui->m_tableWidget->setItem(previousRow,previousColumn-1,new QTableWidgetItem(""));
                    lineEdit->deleteLater();
                    return;
                }
            }
        }
        lineEdit->deleteLater();*/
    }
}

void QTreeCtrlRecipeDlg::on_m_IradioBtn_clicked(bool checked)//连续
{
    int nRow = ui->m_tableWidget->rowCount();
    QString str = "";
    for(int i = 0; i < nRow; i++)
    {
        QWidget *wgt = ui->m_tableWidget->cellWidget(i,2);
        QComboBox *condwgt = dynamic_cast<QComboBox *>(wgt);
        if(condwgt)
        {
            ui->m_tableWidget->removeCellWidget(i,2);
            wgt->deleteLater();
            wgt = NULL;
        }
        wgt = ui->m_tableWidget->cellWidget(i,1);
        AddWidget *addrWgt = dynamic_cast<AddWidget *>(wgt);
        if(addrWgt)
        {
            ui->m_tableWidget->removeCellWidget(i,1);
            wgt->deleteLater();
            wgt = NULL;
        }

        QTableWidgetItem *newitem = ui->m_tableWidget->item(i,1);
//        if(tr("位") == ui->datestyle_comboBox->currentText())
//        {
//            str = tr("位地址");
//        }
//        else
//        {
//            str = tr("字地址");
//        }
        str = ui->datestyle_comboBox->currentText();
        if(newitem)
        {
            newitem->setText("");
            newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));
        }
        else
        {
            newitem = new QTableWidgetItem("");
            newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));
        }
        ui->m_tableWidget->setItem(i,1,newitem);

        newitem = ui->m_tableWidget->item(i,2);
        if(newitem)
        {
            newitem->setText(str);
            newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));
        }
        else
        {
            newitem = new QTableWidgetItem(str);
            newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));
        }
        ui->m_tableWidget->setItem(i,2,newitem);
    }

    ui->datestyle_comboBox->setEnabled(true);
    ui->M_DataTypelabel->setEnabled(true);
    ui->m_IAddrlineEdit->setEnabled(true);
    ui->m_Iaddrlabel->setEnabled(true);
    ui->m_IaddrpushBtn->setEnabled(true);
    onSetAddress();
}

void QTreeCtrlRecipeDlg::on_M_CradioBtn_clicked(bool checked)//随即
{
    int nRow = ui->m_tableWidget->rowCount();
    for(int i = 0; i < nRow; i++)
    {
        QTableWidgetItem *newitem = ui->m_tableWidget->item(i,1);
        if(newitem)
        {
            newitem->setText("LW0");
        }
        else
        {
            newitem = new QTableWidgetItem("LW0");
            ui->m_tableWidget->setItem(i,1,newitem);
        }
        newitem->setFlags(newitem->flags() | Qt::ItemIsEditable);

        newitem = ui->m_tableWidget->item(i,2);
        if(newitem)
        {
            newitem->setText(tr("16位整数"));
        }
        else
        {
            newitem = new QTableWidgetItem(tr("16位整数"));
            ui->m_tableWidget->setItem(i,2,newitem);
        }
        newitem->setFlags(newitem->flags() | Qt::ItemIsEditable);
    }

    ui->datestyle_comboBox->setEnabled(false);
    ui->M_DataTypelabel->setEnabled(false);
    ui->m_IAddrlineEdit->setEnabled(false);
    ui->m_Iaddrlabel->setEnabled(false);
    ui->m_IaddrpushBtn->setEnabled(false);
}

void QTreeCtrlRecipeDlg::on_m_IaddrpushBtn_clicked()
{
    int ntype = 0;
    QString str  = ui->datestyle_comboBox->currentText();
    if(tr("位") == str)
    {
        ntype = 0;
    }
    else
    {
        ntype = 1;
    }

    QString addrStr = ui->m_IAddrlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(I_Address_Keyboard,addrStr,ntype,this);
    if(addressintputdlg_writeaddress.exec())
    {
        if(!I_Address_Keyboard.sShowAddr.isEmpty())
        {
            ui->m_IAddrlineEdit->setText(I_Address_Keyboard.sShowAddr);
            onSetAddress();
        }
    }
}

void QTreeCtrlRecipeDlg::onSetIaddr(Keyboard addr)//设置连续地址
{
    QString sText = "";
    int nTotalRow = ui->m_tableWidget->rowCount();

    int nOffset = 1;
    QString sDataType = ui->datestyle_comboBox->currentText();
    if(tr("32") == sDataType.left(2))
    {
        nOffset = 2;
    }
    QVector <Keyboard> addrKeyboard = getAddrs(addr,nOffset);

    for(int i = 0; i < nTotalRow && i < addrKeyboard.size(); i++ )
    {
        sText = addrKeyboard.at(i).sShowAddr;
        QTableWidgetItem *newitem = ui->m_tableWidget->item(i,1);
        if(newitem)
        {
            newitem->setText(sText);
        }
        else
        {
            newitem = new QTableWidgetItem(sText);
        }
        ui->m_tableWidget->setItem(i,1,newitem);
        sText = "";
    }
}

void QTreeCtrlRecipeDlg::on_datestyle_comboBox_currentIndexChanged(int index)
{
    if(ui->m_IradioBtn->isChecked())
    {
        QString str = ui->datestyle_comboBox->currentText();
        //QString sAddrType = "";
        int nRow = ui->m_tableWidget->rowCount();
        if(nRow <= 0)
        {
            return;
        }
        if(tr("位") == str)
        {
            //sAddrType = tr("位地址");
            ui->m_IAddrlineEdit->setText("LB0");
        }
        else
        {
            //sAddrType = tr("字地址");
            ui->m_IAddrlineEdit->setText("LW0");
        }
        QTableWidgetItem *Item = ui->m_tableWidget->item(0,2);
        on_m_IradioBtn_clicked(true);
    }
}

void QTreeCtrlRecipeDlg::on_m_tableWidget_itemDoubleClicked(QTableWidgetItem* item)
{
}

void QTreeCtrlRecipeDlg::on_recipesize_spinBox_valueChanged(int )
{
    if(!bInitflag)
    {
        return;
    }
    int nValue = ui->recipesize_spinBox->value();
    if(nValue < 0)
    {
        nValue = 0;
    }
    int nRow = ui->m_tableWidget->rowCount();

    if(524288/nValue >= 128)//若所得数值小于128
    {
        int nRecipLength = ui->recipe_spinBox->value();
        if(nRecipLength > 524288/nValue)
        {
            ui->recipe_spinBox->setValue(524288/nValue);
            on_recipe_spinBox_editingFinished();
        }
        ui->recipe_spinBox->setMaximum(524288/nValue);
    }
    else
    {
        int nRecipLength = ui->recipe_spinBox->value();
        if(nRecipLength > 128)
        {
            ui->recipe_spinBox->setValue(128);
            on_recipe_spinBox_editingFinished();
        }
        ui->recipe_spinBox->setMaximum(128);//配方长度最大值为128
    }

    if(nValue > nRow)
    {
        for(int i = nRow; i < nValue; i++)
        {
            QString str = ELMENTNAME;
            ui->m_tableWidget->insertRow(i);
            str = str + QString("%1").arg(i);
            ui->m_tableWidget->setItem(i,0,new QTableWidgetItem(str));

            //元素多语言begin
            int index = ui->m_LanguageCmBox->count();
            QVector<RECIPEElEMENT> elment;
            elment.resize(index);
            for(int i = 0; i< index; i++)
            {
                elment[i].sElemName = str;
                elment[i].nLanguageId = i;
            }
            Pro.ElmentName.append(elment);
            //元素多语言end

            str = ui->datestyle_comboBox->currentText();
            if(ui->m_IradioBtn->isChecked())
            {
                QTableWidgetItem *newitem = new QTableWidgetItem;
                QString sType = ui->datestyle_comboBox->currentText();
                newitem->setText(str);
                ui->m_tableWidget->setItem(i,2,newitem);
                newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));

                newitem = new QTableWidgetItem("");
                ui->m_tableWidget->setItem(i,1,newitem);
                newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));
            }
            else
            {
                QString sAddrType = tr("16位整数");
                QTableWidgetItem *newitem = new QTableWidgetItem(sAddrType);
                ui->m_tableWidget->setItem(i,2,newitem);
                newitem->setFlags(newitem->flags() | Qt::ItemIsEditable);

                newitem = new QTableWidgetItem("LW0");
                ui->m_tableWidget->setItem(i,1,newitem);
                newitem->setFlags(newitem->flags() | Qt::ItemIsEditable);
            }
        }
        if(ui->m_IradioBtn->isChecked())//连续地址设置
        {
            onSetAddress();
        }
    }
    else if(nValue < nRow)
    {
        for(int i = nRow -1; i >= nValue; i--)
        {
            ui->m_tableWidget->removeRow(i);
            Pro.ElmentName.remove(i);
        }
    }
}

bool QTreeCtrlRecipeDlg::onSaveInfo()
{
    int nColum = ui->m_tableWidget->columnCount();
    int nRow = ui->m_tableWidget->rowCount();
    QString sName = ui->m_namelineEdit->text();
    if(nColum <= 3)
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("配方个数不能为0"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return false;
    }
    if(sName.isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("配方组名称不能为空"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->m_namelineEdit->setFocus();
        return false;
    }
    if(-1 != nIndex)//双击打开
    {
        QStringList names;
        for(int i = 0; i <  pwnd->m_pSamSysParame->m_qvcRecipe.size(); i++)
        {
            if(i == nIndex)
            {
                continue;
            }
            names << pwnd->m_pSamSysParame->m_qvcRecipe[i].sName;
        }
        if(names.contains(sName))
        {
            QString warning;
            warning +=tr("配方组 ");
            warning += sName;
            warning +=tr(" 已经存在");
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,warning,0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
            box.exec();
            return false;
        }
    }
    else//新建
    {
        QStringList names;
        for(int i = 0; i <  pwnd->m_pSamSysParame->m_qvcRecipe.size(); i++)
        {
            names << pwnd->m_pSamSysParame->m_qvcRecipe[i].sName;
        }
        if(names.contains(sName))
        {
            QString warning;
            warning +=tr("配方组 ");
            warning += sName;
            warning +=tr(" 已经存在");
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,warning,0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
            box.exec();
            return false;
        }
    }
//    if(ui->m_IradioBtn->isChecked() && !onSetAddress())
//    {
//        return false;
//    }
    for(int i = 0; i < nRow; i++)
    {
        QTableWidgetItem *newitem = ui->m_tableWidget->item(i,1);
        if(!newitem || "" == newitem->text())
        {
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("请输入元素地址"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
                        box.addButton(tr("确定"),QMessageBox::AcceptRole);
                        box.exec();
                        return false;
        }
    }
//    for(int i = 0; i < pwnd->m_pSamSysParame->m_qvcRecipe.size();i++)
//    {
//        if(sName == pwnd->m_pSamSysParame->m_qvcRecipe[i].sName)
//        {
//            QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("配方组已经存在"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
//            box.addButton(tr("确定"),QMessageBox::AcceptRole);
//            box.exec();
//            ui->m_namelineEdit->setFocus();
//            return false;
//        }
//    }
    if(ui->m_writeaddressCkBox->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(Address_Keyboard,tr("控制地址"),ui->m_writeaddresslineEdit,1))
        {
            ui->m_writeaddresslineEdit->setFocus();
            return false;
        }
        Pro.addrCtl = Address_Keyboard;
    }

    if(ui->m_TransRecipeCkBox->isChecked())
    {
        if(! pwnd->IsAddressCheckRight(Bit_Address_Keyboard,tr("位通知地址"),ui->m_BitaddresslineEdit,0))
        {
            ui->m_BitaddresslineEdit->setFocus();
            return false;
        }
        Pro.addrNotic = Bit_Address_Keyboard;
    }
    Pro.sRecipeGDescri = ui->edit_text->toPlainText();//描述
    Pro.nLanguageId = ui->m_LanguageCmBox->currentIndex();//语言
    Pro.bCtlAddr = ui->m_writeaddressCkBox->isChecked();//是否需要控制地址
    Pro.sCtlAddrId = ui->m_writeaddresslineEdit->text();//控制地址
    //Pro.bTransRecipe = ui->m_TrangroupBox->isChecked();//是否传输配方
//    if(ui->m_WriteReadradioBtn->isChecked())//可读写
//    {
//        Pro.eRecipeTransType = 1;
//    }
//    else if(ui->m_ReadPLCradioBtn->isChecked())//从PLC读
//    {
//        Pro.eRecipeTransType = 2;
//    }
//    else
//    {
//        Pro.eRecipeTransType = 3;
//    }
    Pro.bCompleteNotic = ui->m_TransRecipeCkBox->isChecked();//是否需要传出完成通知地址
    Pro.sComNoticAddrId = ui->m_BitaddresslineEdit->text();//位通知地址
    if(ui->m_RameradioBtn->isChecked())//内部存储区
    {
        Pro.eSaveMedia = 1;
    }
    else if(ui->m_UradioBtn->isChecked())//u盘
    {
        Pro.eSaveMedia = 2;
    }
    else
    {
        Pro.eSaveMedia = 3;
    }
    Pro.nRecipeLen = ui->recipesize_spinBox->value();
    if(ui->m_IradioBtn->isChecked())//连续随即
    {
       Pro.bContniu = true;
    }
    else
    {
        Pro.bContniu = false;
    }
    Pro.eDataType = ui->datestyle_comboBox->currentIndex();//数据类别
    Pro.sContniuAddr = ui->m_IAddrlineEdit->text();//连续地址

    QTableWidgetItem *newitem = NULL;
    //formula.resize(nColum - 3);//配方个数
    QLineEdit *lineEdit = new QLineEdit;
    for(int i = 3; i < nColum; i++)
    {
        newitem = ui->m_tableWidget->horizontalHeaderItem(i);
        if(newitem)
        {
            formula[i - 3].sFormulaName = newitem->text();//配方名称
        }
        formula[i - 3].nColum = i;//保存列标号
        formula[i - 3].elment.clear();;
        for(int j = 0; j < nRow; j++)
        {
            ELMENT elment;

            if(i > 3)
            {
                elment = formula[0].elment[j];

                QString str = "";
                newitem = ui->m_tableWidget->item(j,i);
                if(newitem)
                {
                    str = newitem->text();//地址类型
                }
                elment.sText = str;
            }
            else
            {
                int nAddrType = 1;
                QString sAddr;
                QString str = "";
                newitem = ui->m_tableWidget->item(j,0);
                if(newitem)
                {
                    str = newitem->text();//元素名称
                }
                elment.sName = str;
                str = "";

                newitem = ui->m_tableWidget->item(j,1);
                if(newitem)
                {
                    str = newitem->text();//地址
                }
                elment.sAddr = str;
                sAddr = str;
                str = "";

                newitem = ui->m_tableWidget->item(j,2);
                if(newitem)
                {
                    str = newitem->text();//地址类型
                }
                elment.sAddrType = str;
                if(tr("位") == str)
                {
                    nAddrType = 0;
                }
                else
                {
                   nAddrType = 1;
                }
                lineEdit->setText(sAddr);
                if(! pwnd->IsAddressCheckRight(Address_Keyboard,tr("控制地址"),lineEdit,nAddrType))
                {
                    return false;
                }
                elment.addr = Address_Keyboard;
                lineEdit->setText(Address_Keyboard.sShowAddr);
                str = "";

                newitem = ui->m_tableWidget->item(j,i);
                if(newitem)
                {
                    str = newitem->text();//地址类型
                }
                elment.sText = str;
            }
            formula[i - 3].elment.append(elment);
        }
    }
    lineEdit->deleteLater();

    Pro.nKeyMark = ui->m_PouupckBox->isChecked();
    if(Pro.nKeyMark)
    {
        Pro.nBoardX = ui->m_xKeyspinBox->value();
        Pro.nBoardY = ui->m_yKeyspinBox->value();
        Pro.nKeyId = ui->m_keyspBox->currentIndex();
        Pro.sKeyname = ui->m_keyspBox->currentText();
    }
    else
    {
        Pro.nBoardX = ui->m_xKeyspinBox->value();
        Pro.nBoardY = ui->m_yKeyspinBox->value();
        Pro.nKeyId = 0;
        Pro.sKeyname = "";
    }

    Pro.formula = formula;
    Pro.sName = sName;
    return true;
}

void QTreeCtrlRecipeDlg::on_m_writeaddressCkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->m_writeaddresslabel->setEnabled(true);
        ui->m_writeaddresslineEdit->setEnabled(true);
        ui->m_writeaddresspushBtn->setEnabled(true);
    }
    else
    {
        ui->m_writeaddresslabel->setEnabled(false);
        ui->m_writeaddresslineEdit->setEnabled(false);
        ui->m_writeaddresspushBtn->setEnabled(false);
    }
}
void QTreeCtrlRecipeDlg::on_m_tabWidget_currentChanged(int index)
{
    if(index == 0)
    {
        //ui->m_CopyDatepushBtn->hide();
        ui->m_AddPripushBtn->setEnabled(false);
        ui->m_DeletePripushBtn->setEnabled(false);
    }
    else if(index == 1)
    {
        //ui->m_CopyDatepushBtn->show();
        //ui->m_AddPripushBtn->show();
        //ui->m_DeletePripushBtn->show();
    }
}

void QTreeCtrlRecipeDlg::on_recipeoutput_pushButton_clicked()
{
    QString recipeName = ui->m_namelineEdit->text();
    if(recipeName.isEmpty())
    {
        recipeName = "recipe";
    }
    QString path = tr("C:\\Documents and Settings\\Administrator\\桌面\\");
    path += recipeName+".csv";
    QString filePathName = QFileDialog::getSaveFileName(this, tr("另存为"), path,tr("EXCEL(*.csv)"));
    if(filePathName=="")
    {
        return;
    }
    QFile file(filePathName);
    if(file.exists())
    {
        file.remove(filePathName);
    }
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        //保存配方表格数据
        QTableWidgetItem *newitem = NULL;
        int nRow = ui->m_tableWidget->rowCount();
        int nCloum = ui->m_tableWidget->columnCount();
        //保存行列数

        for(int i = 0; i < nCloum; i++)
        {
            if(i == 1 || i == 2)
            {
                continue;
            }
            QString str = "";
            newitem = ui->m_tableWidget->horizontalHeaderItem(i);
            if(newitem)
            {
                str = newitem->text();
            }

            out<<str;
            if(i < nCloum - 1)
            {
               out<<",";
            }
        }
        out<<endl;

        for(int i = 0; i < nRow; i++)
        {
            for(int j = 0; j < nCloum; j++)
            {
                if(j == 1 || j == 2)
                {
                    continue;
                }
                QString str = "";
                newitem = ui->m_tableWidget->item(i,j);
                if(newitem)
                {
                    str = newitem->text();
                }

                out<<str;
                if(j < nCloum - 1)
                {
                    out<<",";
                }
            }
            out<<endl;
        }
    }
    file.close();
}

void QTreeCtrlRecipeDlg::on_recipeintput_pushButton_clicked()
{
    QString recipeName = ui->m_namelineEdit->text();
    if(recipeName.isEmpty())
    {
        recipeName = "recipe";
    }
    QString path = tr("C:\\Documents and Settings\\Administrator\\桌面\\");
    path += recipeName+".csv";

    QMessageBox box(QMessageBox::Warning,tr("提示"),tr(""),QMessageBox::Ok ,this,Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("确定"));
    QString filename=QFileDialog::getOpenFileName(this,tr("打开"),path,tr("EXCEL(*.csv)"));
    QFile file(filename);
    if(filename=="")
    {
        return;
    }
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        box.setText(tr("数据导入失败"));
        box.exec();
        return;
    }
    QTextStream  intput(&file);
    //配方名称和描述
    QString  sReadLine;// = intput.readLine();
    QStringList str;// = sReadLine.split(":");

    QTableWidgetItem *newitem = NULL;
    int iNum = 0;
    while(!intput.atEnd())
    {
        int nRow = ui->m_tableWidget->rowCount() - 2;
        int nColum = ui->m_tableWidget->columnCount();

        sReadLine = intput.readLine();
        str = sReadLine.split(',');
        int num = str.size();
        if(num <= 1)
        {
            continue;
        }
        if(nColum < num + 2)
        {
            ui->m_tableWidget->setColumnCount(num + 2);
            ui->recipe_spinBox->setValue(num - 1);
            formula.resize(num -1);
        }
        if(0 == iNum)
        {
            for(int i = 1; i < num; i++)
            {
                QString sBuffer = str.at(i);
                newitem = ui->m_tableWidget->horizontalHeaderItem(i+2);
                if(!newitem)
                {
                    newitem = new QTableWidgetItem;
                }
                newitem->setText(sBuffer);
                ui->m_tableWidget->setHorizontalHeaderItem(i + 2,newitem);
                //替换语言信息
            }
        }
        else
        {
            if(1 == iNum)
            {
                ui->m_tableWidget->setRowCount(1);
            }
            else
            {
                ui->m_tableWidget->insertRow(iNum - 1);
                QString sAddrType = tr("16位整数");
                newitem = new QTableWidgetItem(sAddrType);
                ui->m_tableWidget->setItem(iNum - 1,2,newitem);
                newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));

                newitem = new QTableWidgetItem("LW0");
                ui->m_tableWidget->setItem(iNum - 1,1,newitem);
                newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));
            }
            QString sElname = str.at(0);
            newitem = ui->m_tableWidget->item(iNum - 1,0);
            if(!newitem)
            {
                newitem = new QTableWidgetItem;
            }
            newitem->setText(sElname);
            ui->m_tableWidget->setItem(iNum - 1,0,newitem);

            for(int i = 1; i < num; i++)
            {
                QString sBuffer = str.at(i);
                newitem = ui->m_tableWidget->item(iNum - 1,i + 2);
                if(!newitem)
                {
                    newitem = new QTableWidgetItem;
                }
                newitem->setText(sBuffer);
                ui->m_tableWidget->setItem(iNum - 1,i + 2,newitem);
            }
        }
        iNum++;//标记行号-1
    }

    if(iNum - 1 > 0)
    {
        ui->recipesize_spinBox->setValue(iNum - 1);
    }

    int nRow = ui->m_tableWidget->rowCount();
    int nColum = ui->m_tableWidget->columnCount();

    QString sElmentName = ELMENTNAME;
    int nLangID = ui->m_LanguageCmBox->currentIndex();
    Pro.ElmentName.clear();
    for(int i = 0; i < nRow; i++)
    {
        sElmentName = sElmentName + QString("%1").arg(i);

        //元素多语言begin
        int index = ui->m_LanguageCmBox->count();
        QVector<RECIPEElEMENT> elment;
        elment.resize(index);
        for(int j = 0; j< index; j++)
        {
            if(nLangID == j && ui->m_tableWidget->item(i,0))
            {
                elment[j].sElemName = ui->m_tableWidget->item(i,0)->text();
            }
            else
            {
                elment[j].sElemName = sElmentName;
            }
            elment[j].nLanguageId = j;
        }
        Pro.ElmentName.append(elment);
        //元素多语言end
        sElmentName = ELMENTNAME;
    }

    formula.clear();
    for(int j = 0; j < nColum - 3; j++)
    {
        FORMULA_ST recipe;
        int index  = ui->m_LanguageCmBox->count();
        recipe.RecipeInfo.resize(index);
        for(int i = 0; i < index; i++)
        {
            QString sRecipname = RICIPENAME;
            sRecipname =sRecipname + QString("%1").arg(j);
            if(i == nLangID)
            {
                recipe.RecipeInfo[i].sRecipeName = ui->m_tableWidget->horizontalHeaderItem(j + 3)->text();
            }
            else
            {
                recipe.RecipeInfo[i].sRecipeName = sRecipname;
            }
            recipe.RecipeInfo[i].nLanguageId = i;
            recipe.RecipeInfo[i].sRecipeDescri = "";
        }
        formula.append(recipe);
    }

//    //读取行列数
//    sReadLine = intput.readLine();
//    str = sReadLine.split(":");
//    int nRow;
//    int nColum;
//    if(2 > str.size())
//    {
//        file.close();
//        return;
//    }
//    else
//    {
//        QString s = str.at(1);
//        s.remove(',');

//        nRow = str.at(0).toInt();
//        nColum = s.toInt();
//    }
//    ui->m_tableWidget->setRowCount(nRow);
//    ui->recipe_spinBox->setValue(nColum);
//    ui->m_tableWidget->setColumnCount(nColum);
//    if(nColum < 3)
//    {
//        return;
//    }
//    formula.resize(nColum - 3);

//    //读取标题列

//    sReadLine = intput.readLine();
//    QString sBuffer;
//    int nLangCout = ui->m_LanguageCmBox->count();
//    for(int i = 0; i < nColum; i++)
//    {
//        sBuffer = sReadLine.section(',',i,i);//第i列标题
//        if(i < 3)
//        {
//            newitem = ui->m_tableWidget->horizontalHeaderItem(i);
//            if(!newitem)
//            {
//                newitem = new QTableWidgetItem;
//            }
//            newitem->setText(sBuffer);
//            ui->m_tableWidget->setHorizontalHeaderItem(i,newitem);
//        }
//        else
//        {
//            str = sBuffer.split(":");
//            if(nLangCout != str.size())
//            {
//                file.close();
//                return;
//            }
//            else
//            {
//                formula[i - 3].RecipeInfo.resize(nLangCout);
//                Pro.ElmentName.resize(nRow);
//                for(int j = 0; j<nLangCout; j++)
//                {
//                   formula[i - 3].RecipeInfo[j].sRecipeName =  str.at(j);
//                }
//                int nIndex = ui->m_LanguageCmBox->currentIndex();
//                newitem = ui->m_tableWidget->horizontalHeaderItem(i);
//                if(!newitem)
//                {
//                    newitem = new QTableWidgetItem;
//                }
//                newitem->setText(formula[i - 3].RecipeInfo.at(nIndex).sRecipeName);
//                ui->m_tableWidget->setHorizontalHeaderItem(i,newitem);
//            }
//        }

//    }

//    for(int i = 0; i < nRow; i++)
//    {
//        sReadLine = intput.readLine();
//        for(int j = 0; j < nColum; j++)
//        {
//            sBuffer = sReadLine.section(',',j,j);
//            if(0 == j)
//            {
//                str = sBuffer.split(":");
//                if(nLangCout != str.size())
//                {
//                    file.close();
//                    return;
//                }
//                else
//                {
//                    Pro.ElmentName[i].resize(nLangCout);
//                    for(int k = 0; k < nLangCout; k++)
//                    {
//                        Pro.ElmentName[i][k].sElemName = str.at(k);
//                    }
//                    int nIndex = ui->m_LanguageCmBox->currentIndex();
//                    newitem = ui->m_tableWidget->item(i,j);
//                    if(!newitem)
//                    {
//                       newitem = new QTableWidgetItem;
//                    }
//                    newitem->setText(Pro.ElmentName[i][nIndex].sElemName);
//                    ui->m_tableWidget->setItem(i,j,newitem);
//                }
//            }
//            else
//            {
//                newitem = ui->m_tableWidget->item(i,j);
//                if(!newitem)
//                {
//                   newitem = new QTableWidgetItem;
//                }
//                if(j > 2 && !sBuffer.isEmpty())
//                {
//                    bool ok = false;
//                    sBuffer.toLong(&ok);
//                    if(!ok)
//                    {
//                        sBuffer = "0";
//                    }
//                }

//                newitem->setText(sBuffer);
//                ui->m_tableWidget->setItem(i,j,newitem);
//            }
//        }
//    }
    file.close();
}

void QTreeCtrlRecipeDlg::on_m_namelineEdit_2_textChanged(QString )
{
    QString sName = ui->m_namelineEdit_2->text();
    int nColum = ui->m_tableWidget->currentColumn();
    if(nColum <= 2)
    {
        return;
    }
    QTableWidgetItem *item = ui->m_tableWidget->horizontalHeaderItem(nColum);
    if(!item)
    {
        item = new QTableWidgetItem;
    }
    item->setText(sName);
    ui->m_tableWidget->setHorizontalHeaderItem(nColum,item);

    int index  = ui->m_LanguageCmBox->currentIndex();
    if(nColum - 3 < formula.size() && index < formula[nColum - 3].RecipeInfo.size())
    {
       formula[nColum - 3].RecipeInfo[index].sRecipeName = sName;
    }
}
void QTreeCtrlRecipeDlg::onLimitDataInput(int type,int row, int column)//限制输入数据
{
    int  width      = ui->m_tableWidget->columnWidth(column);
    int  height     = ui->m_tableWidget->rowHeight(row);

    QString str = "";
    QTableWidgetItem *item = ui->m_tableWidget->item(row,column);
    if(item)
    {
        str = item->text();
    }
    //QIntValidator* aIntValidator = new QIntValidator;
    DoubleValidator *aDoubleValidator = new DoubleValidator(0);
    QLineEdit *pLineEdit = new QLineEdit(str,this);
    pLineEdit->setBaseSize(width,height);

    if(0 == type)//16位整数
    {
        aDoubleValidator->setRange(-32768, 32767,0);
    }
    else if(1 == type)//16位正整数
    {
        aDoubleValidator->setRange(0, 65535,0);
    }
    else if(2 == type)//32位整数
    {
        int max = 2147483647L;
        int min = -1 * 2147483648L;
        aDoubleValidator->setRange(min, max,0);
    }
    else if(3 == type)//32位正整数
    {
        aDoubleValidator->setRange(0, 4294967295UL,0);
    }
    else if(4 == type)//32位浮点数
    {
        int max = 2147483647L;
        int min = -1 * 2147483648L;
        aDoubleValidator->setRange(min,max,4);
    }
    else if(5 == type)//16位BCD
    {
        aDoubleValidator->setRange(0, 9999,0);
    }
    else if(6 == type)//32位BCD
    {
        aDoubleValidator->setRange(0, 99999999L);
    }
    else if(7 == type)//位
    {
        aDoubleValidator->setRange(0, 1);
    }

    pLineEdit->setValidator(aDoubleValidator);
    ui->m_tableWidget->setCellWidget(row,column,pLineEdit);
}

void QTreeCtrlRecipeDlg::on_m_writeaddresspushBtn_clicked()
{
    QString addrStr = ui->m_writeaddresslineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_writeaddresslineEdit->setText(Address_Keyboard.sShowAddr);
    }
}

void QTreeCtrlRecipeDlg::on_m_BitaddresspushBtn_clicked()
{
    QString addrStr = ui->m_BitaddresslineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(Bit_Address_Keyboard,addrStr,0,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_BitaddresslineEdit->setText(Bit_Address_Keyboard.sShowAddr);
    }

}

void QTreeCtrlRecipeDlg::on_m_LanguageCmBox_currentIndexChanged(int index)
{
    for(int i = 0; i< formula.size(); i++)
    {
        if(index < formula[i].RecipeInfo.size())
        {
            QString sName = formula[i].RecipeInfo[index].sRecipeName;
            int nColum = i + 3;
            if(nColum <= 2 || nColum > ui->m_tableWidget->columnCount())
            {
                return;
            }
            QTableWidgetItem *item = ui->m_tableWidget->horizontalHeaderItem(nColum);
            if(!item)
            {
                item = new QTableWidgetItem;
            }
            item->setText(sName);
            ui->m_tableWidget->setHorizontalHeaderItem(nColum,item);
        }
    }
    for(int i = 0; i < Pro.ElmentName.size() && i < ui->m_tableWidget->rowCount(); i++)
    {
        if(index < Pro.ElmentName[i].size())
        {
            QString str = Pro.ElmentName[i].at(index).sElemName;
            QTableWidgetItem *newitem = ui->m_tableWidget->item(i,0);
            if(newitem)
            {
                newitem->setText(str);
            }
            else
            {
                newitem = new QTableWidgetItem(str);
            }
            ui->m_tableWidget->setItem(i,0,newitem);
        }
    }
}

void QTreeCtrlRecipeDlg::on_m_tableWidget_itemChanged(QTableWidgetItem* item)
{
    int nColoum = ui->m_tableWidget->currentColumn();
    if(0 != nColoum || !item || item->column() > 0)
    {
        return;
    }
    int nRow = ui->m_tableWidget->currentRow();
    if(nRow > Pro.ElmentName.size() || nRow != item->row())
    {
        return;
    }

    int index  = ui->m_LanguageCmBox->currentIndex();

    QString str = item->text();
    if(index < Pro.ElmentName[nRow].size())
    {
        Pro.ElmentName[nRow][index].sElemName = str;
    }
}

void QTreeCtrlRecipeDlg::mousePressEvent ( QMouseEvent * event )
{
    QRectF rect = ui->m_tableWidget->geometry();
    QPointF mousePos = event->posF();
    if(!rect.contains(mousePos))
    {
        int row,column;
        row = ui->m_tableWidget->currentRow();
        column = ui->m_tableWidget->currentColumn();
        on_m_tableWidget_currentCellChanged(row,column,row,column);
    }
}

void QTreeCtrlRecipeDlg::mouseMoveEvent ( QMouseEvent * event )
{
    QRectF rect = ui->m_tableWidget->geometry();
    QPointF mousePos = event->posF();
    if(!rect.contains(mousePos))
    {
        int row,column;
        row = ui->m_tableWidget->currentRow();
        column = ui->m_tableWidget->currentColumn();
        on_m_tableWidget_currentCellChanged(row,column,row,column);
    }
}

void QTreeCtrlRecipeDlg::tableFocusOut()
{
    int row,column;
    row = ui->m_tableWidget->currentRow();
    column = ui->m_tableWidget->currentColumn();
    on_m_tableWidget_currentCellChanged(row,column,row,column);
}

bool QTreeCtrlRecipeDlg::eventFilter(QObject * o,QEvent *event)
{
    switch(event->type())
    {
    case QEvent::KeyPress:
        {
            QKeyEvent *kEvent = dynamic_cast<QKeyEvent *>(event);
            if(kEvent && kEvent->key() == Qt::Key_Return)
            {
                int row,column;
                row = ui->m_tableWidget->currentRow();
                column = ui->m_tableWidget->currentColumn();
                on_m_tableWidget_currentCellChanged(row,column,row,column);
                return false;
            }
        }
        break;
    case QEvent::MouseButtonPress:
        {
            QMouseEvent *mEvent = dynamic_cast<QMouseEvent *>(event);
            if(mEvent)
            {
                QRectF rect = ui->m_tableWidget->geometry();
                QPointF mousePos = mEvent->posF();
                if(!rect.contains(mousePos))
                {
                    int row,column;
                    row = ui->m_tableWidget->currentRow();
                    column = ui->m_tableWidget->currentColumn();
                    on_m_tableWidget_currentCellChanged(row,column,row,column);
                    return false;
                }
            }
        }
        break;
    case QEvent::MouseButtonDblClick:
        {
            QMouseEvent *mEvent = dynamic_cast<QMouseEvent *>(event);
            if(mEvent)
            {
                QRectF rect = ui->m_tableWidget->geometry();
                QPointF mousePos = mEvent->posF();
                if(!rect.contains(mousePos))
                {
                    int row,column;
                    row = ui->m_tableWidget->currentRow();
                    column = ui->m_tableWidget->currentColumn();
                    on_m_tableWidget_currentCellChanged(row,column,row,column);
                    return false;
                }
            }
        }
        break;
    case QEvent::HoverMove:
        {
            QHoverEvent *mEvent = dynamic_cast<QHoverEvent *>(event);
            QRectF rect = ui->m_tableWidget->geometry();
            QPointF mousePos = mEvent->pos();
            if(!rect.contains(mousePos))
            {
                int row,column;
                row = ui->m_tableWidget->currentRow();
                column = ui->m_tableWidget->currentColumn();
                on_m_tableWidget_currentCellChanged(row,column,row,column);
                return false;
            }
        }
        break;
    default:
                break;

    }
        return QDialog::eventFilter(o,event);
}

bool QTreeCtrlRecipeDlg::onSetAddress()
{
    Keyboard Check_Address_Keyboard;

    if(tr("位") == ui->datestyle_comboBox->currentText())
    {
        if(! pwnd->IsAddressCheckRight(Check_Address_Keyboard,tr("连续地址"),ui->m_IAddrlineEdit,0))
        {
            ui->m_IAddrlineEdit->setFocus();
            return false;
        }
    }
    else
    {
        if(! pwnd->IsAddressCheckRight(Check_Address_Keyboard,tr("连续地址"),ui->m_IAddrlineEdit,1))
        {
            ui->m_IAddrlineEdit->setFocus();
            return false;
        }
    }
    onSetIaddr(Check_Address_Keyboard);
    return true;
}

void QTreeCtrlRecipeDlg::on_m_IAddrlineEdit_editingFinished()
{
    if(ui->m_IradioBtn->isChecked())
        onSetAddress();
}

QVector <Keyboard> QTreeCtrlRecipeDlg::getAddrs(Keyboard addr,int nIntervl)
{
    Keyboard kb = addr;
    QVector <Keyboard> Vaddrs;
    Vaddrs << kb;

    int count = ui->recipesize_spinBox->value();

    QVector<ADDR_CHECK_SOURCE_PROP> multiAddrs = kb.getMultiAddrs(nIntervl,count-1);
    foreach(ADDR_CHECK_SOURCE_PROP addrPro,multiAddrs)
    {
        kb.sPlcAddrValue = QString::fromStdString(addrPro.sAddrValue);
        kb.refreshShowAddr();
        Vaddrs<< kb;
    }
    return Vaddrs;
}

void QTreeCtrlRecipeDlg::on_recipesize_spinBox_editingFinished()
{
    if(!bInitflag)
    {
        return;
    }
    int nValue = ui->recipesize_spinBox->value();
    if(nValue < 0)
    {
        nValue = 0;
    }
    int nRow = ui->m_tableWidget->rowCount();
    if(nRow == nValue)
    {
        return;
    }


    int nTatol  = 524288/nValue;
    int nRecipLength = ui->recipe_spinBox->value();
    if(nTatol >= 128 && nTatol <= 512)//若所得数值小于128
    {
        if(nRecipLength > nTatol)
        {
            ui->recipe_spinBox->setValue(nTatol);
            on_recipe_spinBox_editingFinished();
        }
        ui->recipe_spinBox->setMaximum(nTatol);
    }
    else if(nTatol >= 128 && nTatol > 512)
    {
        if(nRecipLength > nTatol)
        {
            ui->recipe_spinBox->setValue(512);
            on_recipe_spinBox_editingFinished();
        }
        ui->recipe_spinBox->setMaximum(512);
    }
    else
    {
        if(nRecipLength > 128)
        {
            ui->recipe_spinBox->setValue(128);
            on_recipe_spinBox_editingFinished();
        }
        ui->recipe_spinBox->setMaximum(128);//配方长度最大值为128
    }

    if(nValue > nRow)
    {
        ui->m_tableWidget->setRowCount(nValue);;
        for(int i = nRow; i < nValue; i++)
        {
            QString str = ELMENTNAME;
            //ui->m_tableWidget->insertRow(i);
            str = str + QString("%1").arg(i);
            ui->m_tableWidget->setItem(i,0,new QTableWidgetItem(str));

            //元素多语言begin
            int index = ui->m_LanguageCmBox->count();
            QVector<RECIPEElEMENT> elment;
            elment.resize(index);
            for(int i = 0; i< index; i++)
            {
                elment[i].sElemName = str;
                elment[i].nLanguageId = i;
            }
            Pro.ElmentName.append(elment);
            //元素多语言end

            str = ui->datestyle_comboBox->currentText();
            if(ui->m_IradioBtn->isChecked())
            {
                QTableWidgetItem *newitem = new QTableWidgetItem;
                QString sType = ui->datestyle_comboBox->currentText();
                newitem->setText(str);
                ui->m_tableWidget->setItem(i,2,newitem);
                newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));

                newitem = new QTableWidgetItem("");
                ui->m_tableWidget->setItem(i,1,newitem);
                newitem->setFlags(newitem->flags() & (~Qt::ItemIsEditable));
            }
            else
            {
                QString sAddrType = tr("16位整数");
                QTableWidgetItem *newitem = new QTableWidgetItem(sAddrType);
                ui->m_tableWidget->setItem(i,2,newitem);
                newitem->setFlags(newitem->flags() | Qt::ItemIsEditable);

                newitem = new QTableWidgetItem("LW0");
                ui->m_tableWidget->setItem(i,1,newitem);
                newitem->setFlags(newitem->flags() | Qt::ItemIsEditable);
            }
        }
        if(ui->m_IradioBtn->isChecked())//连续地址设置
        {
            onSetAddress();
        }
    }
    else if(nValue < nRow)
    {
        for(int i = nRow -1; i >= nValue; i--)
        {
            ui->m_tableWidget->removeRow(i);
            Pro.ElmentName.remove(i);
        }
    }
    refreshTableItem();
}

void QTreeCtrlRecipeDlg::on_m_helpBtn_clicked()
{
    pwnd->loadHelpHtm(TREE_RECIPE);
}

void QTreeCtrlRecipeDlg::on_recipe_spinBox_editingFinished()
{
    int nValue = ui->recipe_spinBox->value();
    int nCount = ui->m_tableWidget->columnCount();
    if(nValue == nCount - 3)
    {
        return;
    }

    if(nValue > nCount - 3)
    {
        ui->m_tableWidget->setColumnCount(nValue + 3);
        for(int j = nCount; j < nValue + 3; j++)
        {
            QString sRecipname = RICIPENAME;
            //ui->m_tableWidget->insertColumn(j);
            sRecipname =sRecipname + QString("%1").arg(j - 3);
            QTableWidgetItem *newitem = new QTableWidgetItem(sRecipname);
            ui->m_tableWidget->setHorizontalHeaderItem(j,newitem);

            FORMULA_ST recipe;
            int index  = ui->m_LanguageCmBox->count();
            recipe.RecipeInfo.resize(index);
            for(int i = 0; i < index; i++)
            {
                recipe.RecipeInfo[i].nLanguageId = i;
                recipe.RecipeInfo[i].sRecipeDescri = "";
                recipe.RecipeInfo[i].sRecipeName = sRecipname;
            }
            formula.append(recipe);
        }
    }
    else if(nValue < nCount - 3 && nValue >= 1)
    {
        ui->m_tableWidget->setColumnCount(nValue + 3);

        formula.resize(nValue);
    }
    refreshTableItem();
}

void QTreeCtrlRecipeDlg::on_m_PouupckBox_clicked(bool checked)
{
    if(checked)
    {
        ui->m_keyspBox->setEnabled(true);
        ui->m_KeygroupBox->setEnabled(true);
    }
    else
    {
        ui->m_keyspBox->setEnabled(false);
        ui->m_KeygroupBox->setEnabled(false);
    }
}

void QTreeCtrlRecipeDlg::on_m_keyspBox_currentIndexChanged(int index)
{
    QString sKeyName = ui->m_keyspBox->currentText();
    if("" == sKeyName)
    {
        return ;
    }

    int totalNum = pwnd->pSceneSheet.size();

    for(int i = 0; i< totalNum; i++)
    {
        if(pwnd->pSceneSheet[i]->nIsSceneOrWindow == 2 && sKeyName == pwnd->pSceneSheet[i]->sNewScreenName)
        {
            int nWidth = pwnd->pSceneSheet[i]->width();
            int nHight = pwnd->pSceneSheet[i]->height();
            int nxValue = pwnd->m_pSamSysParame->m_projectProp.nSceneWidth  - nWidth;
            int nyValue = pwnd->m_pSamSysParame->m_projectProp.nSceneHeight - nHight;

            ui->m_xKeyspinBox->setRange(0,nxValue);
            ui->m_yKeyspinBox->setRange(0,nyValue);
            ui->m_xKeyspinBox->setValue(pwnd->m_pSamSysParame->m_projectProp.nSceneWidth/2 - nWidth/2);
            ui->m_yKeyspinBox->setValue(pwnd->m_pSamSysParame->m_projectProp.nSceneHeight/2 - nHight/2);

            break;
        }
    }
}

void QTreeCtrlRecipeDlg::refreshTableItem()
{
    int nRow  = ui->m_tableWidget->rowCount();
    int nColumn = ui->m_tableWidget->columnCount();
    if(nRow < 1 || nColumn < 4)
    {
        return ;
    }
    if(nRow > nColumn - 3)
    {
        for(int i = 3; i < nColumn; i++)
        {
            for(int j = 0; j < nRow; j++)
            {
                QTableWidgetItem *item = ui->m_tableWidget->item(j,i);
                if(item)
                {
                    QString str = item->text();
                    if(str.isEmpty())
                    {
                        item->setText("0");
                    }
                }
                else
                {
                    item = new QTableWidgetItem("0");
                    ui->m_tableWidget->setItem(j,i,item);
                }
            }
        }
    }
    else
    {
        for(int i  = 0; i < nRow; i++)
        {
            for(int j = 3; j < nColumn; j++)
            {
                QTableWidgetItem *item = ui->m_tableWidget->item(i,j);
                if(item)
                {
                    QString str = item->text();
                    if(str.isEmpty())
                    {
                        item->setText("0");
                    }
                }
                else
                {
                    item = new QTableWidgetItem("0");
                    ui->m_tableWidget->setItem(i,j,item);
                }
            }
        }
    }
}
