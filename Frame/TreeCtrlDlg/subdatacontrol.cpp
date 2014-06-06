#include "subdatacontrol.h"
#include  "Frame/mainwindow.h"

extern MainWindow *pwnd;

subDataControl::subDataControl(QWidget *parent):QDialog(parent),ui(new Ui::subDataControl)
{
    ui->setupUi(this);

    setFixedSize(size());

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    sel_group= new QButtonGroup(this);
    sel_group->addButton(ui->radioButton, 0);
    sel_group->addButton(ui->radioButton_2, 1);
    sel_group->button(0)->setChecked(true);

    QStringList sList;
    sList.clear();
    QString str = "";
    ui->comboBox->clear();
    QTreeWidgetItem *treeItem;
    int totalSceneNum = pwnd->pSceneSheet.size();
    for(int i = 0; i < totalSceneNum; i++)
    {
        treeItem = pwnd->newScreen[i];
        if(treeItem->parent() == pwnd->TreeKeyboard || treeItem->parent() == pwnd->copyUserKeyboard)//自定义菜单
        {
            continue;
        }
        str=pwnd->newScreen[i]->text(0).split(":").at(1);
        sList.append(str);
    }
    ui->comboBox->addItems(sList);
}

subDataControl::~subDataControl()
{
    delete ui;
}

void subDataControl::on_pushButton_clicked()
{
    Keyboard key;
    QString str = ui->lineEdit->text();
    AddressInputDialog dlg_readaddress(key,str,0,this);
    if(dlg_readaddress.exec())
    {
        ui->lineEdit->setText(key.sShowAddr);
    }
    kaddress = key;
}

void subDataControl::on_pushButton_2_clicked()
{
    if(!pwnd->IsAddressCheckRight(kaddress,tr("写入地址"), ui->lineEdit,0))
    {
        return;
    }
    QDialog::accept();
}

void subDataControl::on_pushButton_3_clicked()
{
    QDialog::reject();
}

void subDataControl::on_comboBox_currentIndexChanged(int iIndex)
{
    QString str = ui->comboBox->itemText(iIndex);
    QMap<QString, int>::const_iterator itor = pwnd->m_ChScreenMap.find(str);
    if(itor != pwnd->m_ChScreenMap.end())
    {
       int nActiveSheetIndex = itor.value();
       if(0 == pwnd->pSceneSheet[nActiveSheetIndex]->nIsSceneOrWindow)//画面
       {
           ui->checkBox->setDisabled(false);
           ui->checkBox_close->setDisabled(true);
           ui->checkBox_close->setChecked(false);
       }
       else if(1 == pwnd->pSceneSheet[nActiveSheetIndex]->nIsSceneOrWindow)
       {
           if(ui->checkBox->isChecked())
           {
              ui->checkBox_close->setDisabled(true);
              ui->checkBox_close->setChecked(false);
           }
           else
           {
              ui->checkBox_close->setDisabled(false);
           }
       }
    }
}

void subDataControl::on_checkBox_close_stateChanged(int iState)
{
    if(ui->checkBox_close->isChecked())
    {
        ui->checkBox->setDisabled(true);
    }
    else
    {
        ui->checkBox->setDisabled(false);
    }
}

void subDataControl::on_checkBox_stateChanged(int iState)
{
    QString str = ui->comboBox->itemText(ui->comboBox->currentIndex());
    QMap<QString, int>::const_iterator itor = pwnd->m_ChScreenMap.find(str);
    if(itor != pwnd->m_ChScreenMap.end())
    {
       int nActiveSheetIndex = itor.value();
       if(1 == pwnd->pSceneSheet[nActiveSheetIndex]->nIsSceneOrWindow)
       {
           if(ui->checkBox->isChecked())
           {
               ui->checkBox_close->setDisabled(true);
           }
           else
           {
               ui->checkBox_close->setDisabled(false);
           }
       }
    }
}
