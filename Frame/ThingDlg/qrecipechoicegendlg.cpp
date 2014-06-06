#include "qrecipechoicegendlg.h"
#include "ui_qrecipechoicegendlg.h"
#include "Frame/mainwindow.h"
#include <QFontDatabase>
extern MainWindow *pwnd;

QRecipeChoiceGenDlg::QRecipeChoiceGenDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QRecipeChoiceGenDlg)
{
    ui->setupUi(this);
    R_Lyaout_Group=new QButtonGroup(this);
    R_Lyaout_Group->addButton(ui->radioButton,0);
    R_Lyaout_Group->addButton(ui->radioButton_2,1);
    connect(R_Lyaout_Group,SIGNAL(buttonClicked(int)),this,SLOT(typeSelect(int)));
    pwnd->InitFontSize(ui->FontSize); //初始化字体大小选择框
    ui->Font->addItems(QFontDatabase().families(QFontDatabase::Any));
}

QRecipeChoiceGenDlg::~QRecipeChoiceGenDlg()
{
    if(R_Lyaout_Group)
    {
        delete R_Lyaout_Group;
        R_Lyaout_Group = NULL;
    }
    delete ui;
}
void QRecipeChoiceGenDlg::on_Text_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->Text_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setTextColor(const QColor &)));
}
void QRecipeChoiceGenDlg::setTextColor(const QColor & mColor)       //前景色
{
    ui->Text_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QRecipeChoiceGenDlg::on_BG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->BG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBGColor(const QColor &)));
}
void QRecipeChoiceGenDlg::setBGColor(const QColor & mColor)       //前景色
{
    ui->BG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QRecipeChoiceGenDlg::Init(QGraphicsItem *pItem)
{
    DrawItemToScene GroupFunction;
    QStringList pdataList;

    if(pItem)   //从Data 的 stringList中获取属性并设置
    {
        GroupFunction.CopyItem(&pCopyItem,pItem);
       // pScene->addItem(pCopyItem);
        pdataList = qVariantValue<QStringList>(pCopyItem->data(GROUP_DATALIST_KEY));
        ui->ID->setText(pdataList.at(19));
       R_Lyaout_Group->button(pdataList.at(40).toInt())->setChecked(true);//显示风格
       typeSelect(pdataList.at(40).toInt());

       ui->Font->setCurrentIndex(ui->Font->findText(pdataList.at(41)));//字体

      int value = ui->FontSize->findText(pdataList.at(42));
       ui->FontSize->setCurrentIndex(value);//字体大小

       ui->m_row->setValue(pdataList.at(45).toInt());//行数

       ui->BG_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(pdataList.at(43)).name()));
       ui->Text_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(pdataList.at(44)).name()));

       value = pdataList.at(50).toInt();//是否使用宏指令

       ui->Ifuse_Macro->setChecked(value);
       on_Ifuse_Macro_clicked(value);

       value = ui->Macro_Name->findText(pdataList.at(51));//宏指令名称
       ui->Macro_Name->setCurrentIndex(value);

     }
    else
    {
        /***************************************************
         *以下是单击工具栏的初始化
         **************************************************/
        ui->ID->setText(pwnd->GetControlNO("RS"));
        ui->Font->setCurrentIndex(ui->Font->findText(tr("宋体")));
        ui->BG_Color->setStyleSheet( QString("background:%1").arg(QColor(192,192,192).name()));
        ui->Text_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
        R_Lyaout_Group->button(0)->setChecked(true);
        on_Ifuse_Macro_clicked(false);
    }
}

void QRecipeChoiceGenDlg::on_Ifuse_Macro_clicked(bool checked)
{
    if(checked)
    {
        ui->label_6->setHidden(false);
        ui->Macro_Name->setHidden(false);
    }
    else
    {
        ui->label_6->setHidden(true);
        ui->Macro_Name->setHidden(true);
    }
}

void QRecipeChoiceGenDlg::typeSelect(int nCheckId)
{
    if(nCheckId == 0)
    {
        ui->label_3->setVisible(true);
        ui->m_row->setVisible(true);
    }
    else
    {
        ui->label_3->setVisible(false);
        ui->m_row->setVisible(false);
    }
}
 void QRecipeChoiceGenDlg::GeneralSave(QStringList *datalist, int index)
 {
     QString sTmp;
     sTmp=ui->ID->text();//控件ID
     datalist->replace(19,sTmp);

     sTmp.clear();
     int nState=R_Lyaout_Group->checkedId();//显示风格
     sTmp=QString::number(nState);
     datalist->replace(index,sTmp);

     sTmp.clear();
     sTmp=ui->Font->currentText();//字体
     datalist->replace(index+1,sTmp);

     sTmp.clear();
     sTmp=ui->FontSize->currentText();//字体大小
     datalist->replace(index+2,sTmp);

     sTmp.clear();
     sTmp=pwnd->ColorTOString(ui->BG_Color->palette().background().color());//背景色
     datalist->replace(index+3,sTmp);

     sTmp.clear();
     sTmp=pwnd->ColorTOString(ui->Text_Color->palette().background().color());//文本色
     datalist->replace(index+4,sTmp);

     sTmp=QString::number(ui->m_row->value());//行数
     datalist->replace(index+5,sTmp);

     sTmp.clear();
     nState=ui->Ifuse_Macro->isChecked();//是否使用宏指令
     sTmp=QString::number(nState);
     datalist->replace(index+10,sTmp);

     sTmp.clear();
     sTmp=ui->Macro_Name->currentText();
     datalist->replace(index+11,sTmp);

 }

