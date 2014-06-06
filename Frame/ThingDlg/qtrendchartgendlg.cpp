#include "qtrendchartgendlg.h"
#include "Frame/mainwindow.h"
#include "view/qdrawgraphics.h"
extern MainWindow *pwnd;

QTrendChartGenDlg::QTrendChartGenDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QTrendChartGenDlg)
{
    ui->setupUi(this);
    pwnd->InitDateType(ui->DataType);
    R_Direction_Group = new QButtonGroup(this);
    R_Direction_Group->addButton(ui->R_FromLeft,1);
    R_Direction_Group->addButton(ui->R_FromRight,2);
}

QTrendChartGenDlg::~QTrendChartGenDlg()
{
    if(R_Direction_Group)
    {
        delete R_Direction_Group;
        R_Direction_Group=NULL;
    }
    delete ui;
}

void QTrendChartGenDlg::Init(QGraphicsItem *pItem)
{
    DrawItemToScene GroupFunction;
    QStringList dataList;
    if(pItem)
    {
        GroupFunction.CopyItem(&pOldItem,pItem);
        dataList = qVariantValue<QStringList>(pOldItem->data(GROUP_DATALIST_KEY));

        QString sTmp="";
        sTmp=dataList.at(19);
        ui->m_noedit->setText(sTmp);

        ui->BackColor->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(dataList.at(150)).name()));


        int nTmp=dataList.at(151).toInt();
        ui->DataType->setCurrentIndex(nTmp);//datatype 151

        pwnd->StringToKeyboard(kTrigged_address,dataList.at(152));//read Triggre address 152

        pwnd->StringToKeyboard(kRead_address,dataList.at(153));//read  address 153

        nTmp=dataList.at(154).toInt();
        ui->Number_Data->setValue(nTmp); //data number 154

        nTmp=dataList.at(155).toInt();
        ui->Points_Per_Data->setValue(nTmp); //Points_Per_Data 155

        nTmp=dataList.at(156).toInt();
        ui->Sampling_Time->setValue(nTmp); //Sampling_Time 156

        nTmp=dataList.at(157).toInt();
        ui->If_Show_Data_Point->setChecked(nTmp);//If_Show_Data_Point 157

        nTmp=dataList.at(158).toInt();
        ui->Show_Connected_Line->setChecked(nTmp);//Show_Connected_Line 158

        ui->BG_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(dataList.at(159)).name()));

        pwnd->StringToKeyboard(kClear_Triggre_address,dataList.at(160));//kClear_Triggre_address 160


       nTmp=dataList.at(161).toInt();
       R_Direction_Group->button(nTmp)->setChecked(true);// direction 161

       ui->Read_Triggre->setText(kTrigged_address.sShowAddr);

       ui->Read_Address->setText(kRead_address.sShowAddr);

       ui->Clear_Trigged->setText(kClear_Triggre_address.sShowAddr);

       nTmp=dataList.at(165).toInt();
       ui->m_ifuse->setChecked(nTmp); //是否使用 165
       on_m_ifuse_clicked(nTmp);

       ui->m_checkcolor->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(dataList.at(166)).name()));
       pwnd->StringToKeyboard(checkaddr,dataList.at(167));//检测地址 167
       ui->m_checkaddredit->setText(checkaddr.sShowAddr);

       ui->Transparence->setValue(dataList.at(162).toInt());

       ui->If_Per_Data_Variable->setChecked(dataList.at(169).toInt());//每组数据点数是否可变
       pwnd->StringToKeyboard(KPerDataVariableaddr,dataList.at(170));
       ui->Per_Data_Variable_lineEdit->setText(KPerDataVariableaddr.sShowAddr);
       on_If_Per_Data_Variable_clicked();

       ui->bReadAutoOff->setChecked(dataList.at(171).toInt());
       ui->bClearAutoOff->setChecked(dataList.at(172).toInt());

       ui->If_Use_Control_Add->setChecked(dataList.at(173).toInt());//是否使用控制地址
       pwnd->StringToKeyboard(Control_Address_Keyboard,dataList.at(174));

       ui->Control_Add->setText(Control_Address_Keyboard.sShowAddr);
       on_If_Use_Control_Add_clicked(ui->If_Use_Control_Add->isChecked());
   }
    else
    {
        InitParament();
      }

}
void QTrendChartGenDlg::InitParament()
{
  /***************单机初始化**********************/
   ui->m_noedit->setText(pwnd->GetControlNO("LC"));
   ui->m_checkcolor->setStyleSheet( QString("background:%1").arg(QColor(255,0,0).name()));
   on_m_ifuse_clicked(false); //不启用
   ui->BackColor->setStyleSheet( QString("background:%1").arg(QColor(192,192,192).name()));
   ui->BG_Color->setStyleSheet( QString("background:%1").arg(QColor(255,255,0).name()));
   on_If_Per_Data_Variable_clicked();///每组数据点数可变
   on_If_Use_Control_Add_clicked(false);
}

void QTrendChartGenDlg::on_Read_Triggre_Keybord_clicked()
{
    pwnd->Addr_Type=0;
    AddressInputDialog  dlg_triggered(kTrigged_address,this);
    dlg_triggered.exec();
    ui->Read_Triggre->setText(kTrigged_address.sShowAddr);

}

void QTrendChartGenDlg::on_Read_Address_Keybord_clicked()
{
    pwnd->Addr_Type=1;
    AddressInputDialog  dlg_triggered(kRead_address,this);
    dlg_triggered.exec();
    ui->Read_Address->setText(kRead_address.sShowAddr);

}

void QTrendChartGenDlg::on_Clear_Trigged_Keybord_clicked()
{
    pwnd->Addr_Type=0;
    AddressInputDialog  dlg_triggered(kClear_Triggre_address,this);
    dlg_triggered.exec();
    ui->Clear_Trigged->setText(kClear_Triggre_address.sShowAddr);

}

void QTrendChartGenDlg::on_Number_Data_valueChanged(int i)
{
  emit GenNomberofDataChange();
}

void QTrendChartGenDlg::SaveGeneralPage(QStringList *datalist, int index)
{
    QString sTmp = "";
    int nTmp = 0;

    datalist->replace(19,ui->m_noedit->text());
    sTmp=pwnd->ColorTOString(ui->BackColor->palette().background().color());//前景色
    datalist->replace(index,sTmp);

    sTmp.clear();
    nTmp=ui->DataType->currentIndex();
    sTmp=QString::number(nTmp);
    datalist->replace(index+1,sTmp); //datatype 151

    sTmp.clear();
    sTmp=pwnd->KeyboardToString(kTrigged_address);//read Triggre address 152
    datalist->replace(index+2,sTmp);

    sTmp.clear();
    sTmp=pwnd->KeyboardToString(kRead_address);//read  address 153
    datalist->replace(index+3,sTmp);

    sTmp.clear();
    nTmp=ui->Number_Data->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+4,sTmp); //data number 154

    sTmp.clear();
    nTmp=ui->Points_Per_Data->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+5,sTmp); //Points_Per_Data 155

    sTmp.clear();
    nTmp=ui->Sampling_Time->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+6,sTmp); //Sampling_Time 156

    sTmp.clear();
    nTmp=ui->If_Show_Data_Point->isChecked();
    sTmp=QString::number(nTmp);
    datalist->replace(index+7,sTmp); //If_Show_Data_Point 157

    sTmp.clear();
    nTmp=ui->Show_Connected_Line->isChecked();
    sTmp=QString::number(nTmp);
    datalist->replace(index+8,sTmp); //Show_Connected_Line 158

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->BG_Color->palette().background().color());//背景色
    datalist->replace(index+9,sTmp);

    sTmp.clear();
    sTmp=pwnd->KeyboardToString(kClear_Triggre_address);//kClear_Triggre_address 160
    datalist->replace(index+10,sTmp); //

    sTmp.clear();
    sTmp=QString::number(R_Direction_Group->checkedId());
    datalist->replace(index+11,sTmp); // direction 161

    sTmp.clear();
    nTmp=ui->Transparence->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+12,sTmp); //data number 162

    sTmp.clear();
    sTmp=ui->Read_Address->text();
    datalist->replace(index+13,sTmp); //  163


    sTmp.clear();
    sTmp=ui-> Clear_Trigged->text();
    datalist->replace(index+14,sTmp); //  164

    //保存检测模块
    sTmp.clear();
    nTmp=ui->m_ifuse->isChecked(); //是否启用检测
    sTmp=QString::number(nTmp);
    datalist->replace(index+15,sTmp); //If_Show_Data_Point 165

    sTmp=pwnd->ColorTOString(ui->m_checkcolor->palette().background().color());//检测线颜色
    datalist->replace(index+16,sTmp);//166

    sTmp=pwnd->KeyboardToString(checkaddr);//检测地址 167
    datalist->replace(index+17,sTmp);


    nTmp=ui->If_Per_Data_Variable->isChecked(); //每组数据点数是否可变
    sTmp=QString::number(nTmp);
    datalist->replace(index+19,sTmp); //

    sTmp=pwnd->KeyboardToString(KPerDataVariableaddr);//kClear_Triggre_address 170
    datalist->replace(index+20,sTmp); //

    nTmp=ui->bReadAutoOff->isChecked(); //每组数据点数是否可变
    sTmp=QString::number(nTmp);
    datalist->replace(index+21,sTmp); //

    nTmp=ui->bClearAutoOff->isChecked(); //每组数据点数是否可变
    sTmp=QString::number(nTmp);
    datalist->replace(index+22,sTmp); //

    nTmp=ui->If_Use_Control_Add->isChecked();//控制地址
    sTmp=QString::number(nTmp);
    datalist->replace(index+23,sTmp);

    sTmp=pwnd->KeyboardToString(Control_Address_Keyboard);
    datalist->replace(index+24,sTmp);

}


void QTrendChartGenDlg::on_BackColor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->BackColor ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBackColorColor(const QColor &)));

}
void QTrendChartGenDlg::setBackColorColor(const QColor & mColor)       //背景色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->BackColor->setStyleSheet(QString("background:%1").arg(mColor.name()));
 //   pBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(nColor));      //调用设置属性
}
void QTrendChartGenDlg::on_BG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->BG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBGColor(const QColor &)));

}
void QTrendChartGenDlg::setBGColor(const QColor & mColor)       //文本色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->BG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
   // pBaseItem->SetPropertyValue("mText.FontColor",QVariant(nColor));      //调用设置属性
}

void QTrendChartGenDlg::on_m_ifuse_clicked(bool checked)
{
    if(checked)
    {
        ui->m_colorlable->setVisible(true);
        ui->m_checkcolor->setVisible(true);
        ui->m_addrlable->setVisible(true);
        ui->m_checkaddredit->setVisible(true);
        ui->m_checkbtn->setVisible(true);
    }
    else
    {
        ui->m_colorlable->setVisible(false);
        ui->m_checkcolor->setVisible(false);
        ui->m_addrlable->setVisible(false);
        ui->m_checkaddredit->setVisible(false);
        ui->m_checkbtn->setVisible(false);
    }
}

void QTrendChartGenDlg::on_m_checkcolor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->m_checkcolor ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCheckLineColor(const QColor &)));

}

void QTrendChartGenDlg::setCheckLineColor(const QColor &mColor)
{
    ui->m_checkcolor->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QTrendChartGenDlg::on_m_checkbtn_clicked()
{
    pwnd->Addr_Type=1;
    AddressInputDialog  dlg_triggered(checkaddr,this);
    dlg_triggered.exec();
    ui->m_checkaddredit->setText(checkaddr.sShowAddr);

}

void QTrendChartGenDlg::on_If_Per_Data_Variable_clicked()
{
    bool bflg=ui->If_Per_Data_Variable->isChecked();
    if(bflg)
    {
        ui->Per_Data_Variable_keyboardBtn->setHidden(false);
        ui->Per_Data_Variable_lineEdit->setHidden(false);
        ui->Points_Per_Data->setDisabled(true);
    }
    else
    {
        ui->Per_Data_Variable_keyboardBtn->setHidden(true);
        ui->Per_Data_Variable_lineEdit->setHidden(true);
        ui->Points_Per_Data->setDisabled(false);
    }

}

void QTrendChartGenDlg::on_Per_Data_Variable_keyboardBtn_clicked()
{
    pwnd->Addr_Type=1;
    AddressInputDialog  dlg_triggered(KPerDataVariableaddr,this);
    dlg_triggered.exec();
    ui->Per_Data_Variable_lineEdit->setText(KPerDataVariableaddr.sShowAddr);

}

void QTrendChartGenDlg::on_If_Use_Control_Add_clicked(bool checked)
{
    if(checked)
    {
        ui->label_12->setHidden(false);
        ui->Control_Add->setHidden(false);
        ui->Control_Add_Keyboard->setHidden(false);
    }
    else
    {
        ui->label_12->setHidden(true);
        ui->Control_Add->setHidden(true);
        ui->Control_Add_Keyboard->setHidden(true);

    }

}

void QTrendChartGenDlg::on_Control_Add_Keyboard_clicked()
{
    pwnd->Addr_Type=1;
    AddressInputDialog  dlg_triggered(Control_Address_Keyboard,this);
    dlg_triggered.exec();
    ui->Control_Add->setText(Control_Address_Keyboard.sShowAddr);

}
