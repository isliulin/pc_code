#include "qxytrendchargentdlg.h"
#include "Frame/mainwindow.h"
#include "view/qdrawgraphics.h"
extern MainWindow *pwnd;

QXYTrendCharGentDlg::QXYTrendCharGentDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QXYTrendCharGentDlg)
{
    ui->setupUi(this);
    pScene = new QGraphicsScene(this);
    ui->groupBox->setHidden(true);
    pwnd->InitDateType(ui->DataType);
}

QXYTrendCharGentDlg::~QXYTrendCharGentDlg()
{
    if(pScene)
    {
        delete pScene;
        pScene=NULL;
    }
    if(pBaseItem)
    {
        delete pBaseItem;
        pBaseItem=NULL;
    }
    delete ui;
}

void QXYTrendCharGentDlg::InitParament()
{
    ui->ID->setText(pwnd->GetControlNO("SC"));
    ui->BackColor->setStyleSheet( QString("background:%1").arg(QColor(192,192,192).name()));
    ui->BG_Color->setStyleSheet( QString("background:%1").arg(QColor(255,255,0).name()));
    ui->m_checkcolor->setStyleSheet( QString("background:%1").arg(QColor(255,0,0).name()));
    on_m_ifuse_clicked(false); //������
}

void QXYTrendCharGentDlg::on_Read_Triggre_Keybord_clicked()
{
    pwnd->Addr_Type=0;
    AddressInputDialog  dlg_triggered(kTrigged_address,this);
    dlg_triggered.exec();
    ui->Read_Triggre->setText(kTrigged_address.sShowAddr);


}

void QXYTrendCharGentDlg::on_Read_Address_Keybord_clicked()
{
    pwnd->Addr_Type=1;
    AddressInputDialog  dlg_triggered(kRead_address,this);
    dlg_triggered.exec();
    ui->Read_Address->setText(kRead_address.sShowAddr);


}

void QXYTrendCharGentDlg::on_Clear_Trigged_Keybord_clicked()
{
    pwnd->Addr_Type=0;
    AddressInputDialog  dlg_triggered(kClear_Triggre_address,this);
    dlg_triggered.exec();
    ui->Clear_Trigged->setText(kClear_Triggre_address.sShowAddr);

}

void QXYTrendCharGentDlg::SaveGeneralPage(QStringList *datalist, int index)
{
    QString sTmp = "";
    int nTmp = 0;

    datalist->replace(19,ui->ID->text());

//    sTmp = pwnd->ColorTOString(pBackColor->GetColor());
//    datalist->replace(index,sTmp);//back color 150
    sTmp=pwnd->ColorTOString(ui->BackColor->palette().background().color());//ǰ��ɫ
    datalist->replace(index,sTmp);

    nTmp=ui->DataType->currentIndex();
    sTmp=QString::number(nTmp);
    datalist->replace(index+1,sTmp); //datatype 151

    sTmp=pwnd->KeyboardToString(kTrigged_address);//read Triggre address 152
    datalist->replace(index+2,sTmp);

    sTmp=pwnd->KeyboardToString(kRead_address);//read  address 153
    datalist->replace(index+3,sTmp);

    nTmp=ui->Number_Data->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+4,sTmp); //data number 154

    nTmp=ui->Points_Per_Data->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+5,sTmp); //Points_Per_Data 155

    nTmp=ui->Sampling_Time->value();
    sTmp=QString::number(nTmp);
    datalist->replace(index+6,sTmp); //Sampling_Time 156

    nTmp=ui->If_Show_Data_Point->isChecked();
    sTmp=QString::number(nTmp);
    datalist->replace(index+7,sTmp); //If_Show_Data_Point 157

    nTmp=ui->Show_Connected_Line->isChecked();
    sTmp=QString::number(nTmp);
    datalist->replace(index+8,sTmp); //Show_Connected_Line 158

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->BG_Color->palette().background().color());//����ɫ
    datalist->replace(index+9,sTmp);

    sTmp=pwnd->KeyboardToString(kClear_Triggre_address);//kClear_Triggre_address 160
    datalist->replace(index+10,sTmp); //

    datalist->replace(index+11,ui->Read_Triggre->text());//��ȡ����λ-û�õ� �ɲ���

    sTmp.clear();
    nTmp=ui->Transparence->value(); //
    sTmp=QString::number(nTmp);
    datalist->replace(index+12,sTmp); // 162

    datalist->replace(index+13,ui->Clear_Trigged->text());//�������λ-û�õ� �ɲ���

    //������ģ��
    sTmp.clear();
    nTmp=ui->m_ifuse->isChecked(); //�Ƿ����ü��
    sTmp=QString::number(nTmp);
    datalist->replace(index+15,sTmp); //If_Show_Data_Point 165

    sTmp=pwnd->ColorTOString(ui->m_checkcolor->palette().background().color());//�������ɫ
    datalist->replace(index+16,sTmp);//157

    sTmp=pwnd->KeyboardToString(checkaddr);//����ַ 158
    datalist->replace(index+17,sTmp);

    sTmp=ui->m_checkaddredit->text();
    datalist->replace(index+18,sTmp); //  161

    nTmp=ui->bReadAutoOff->isChecked(); //ÿ�����ݵ����Ƿ�ɱ�
    sTmp=QString::number(nTmp);
    datalist->replace(index+21,sTmp); //

    nTmp=ui->bClearAutoOff->isChecked(); //ÿ�����ݵ����Ƿ�ɱ�
    sTmp=QString::number(nTmp);
    datalist->replace(index+22,sTmp); //

}
void QXYTrendCharGentDlg::Init(QGraphicsItem *pItem)
{
    DrawItemToScene GroupFunction;
    QList<QGraphicsItem *>list;
    QStringList dataList;
    if(pItem)
    {
        GroupFunction.CopyItem(&pOldItem,pItem);
        pScene->addItem(pOldItem);
        dataList = qVariantValue<QStringList>(pOldItem->data(GROUP_DATALIST_KEY));
        pBaseItem = new QGroupItem(pOldItem);

        QString sTmp="";
        sTmp=dataList.at(19);
        ui->ID->setText(sTmp);

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

        ui->Transparence->setValue(dataList.at(162).toInt());
        ui->Read_Triggre->setText(kTrigged_address.sShowAddr);//��ȡ����λ
        ui->Read_Address->setText(kRead_address.sShowAddr);//��ȡ��ַ
        ui->Clear_Trigged->setText(kClear_Triggre_address.sShowAddr);//�������λ
        nTmp=dataList.at(165).toInt();
        ui->m_ifuse->setChecked(nTmp); //�Ƿ�ʹ�� 165
        on_m_ifuse_clicked(nTmp);

        ui->m_checkcolor->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(dataList.at(166)).name()));
        pwnd->StringToKeyboard(checkaddr,dataList.at(167));//����ַ 158
        ui->m_checkaddredit->setText(checkaddr.sShowAddr);
        ui->bReadAutoOff->setChecked(dataList.at(171).toInt());
        ui->bClearAutoOff->setChecked(dataList.at(172).toInt());

    }
    else
    {

        QDrawGraphics *pDraw = new QDrawGraphics;  //�ɻ�������һ������
        pOldItem = pDraw->OnDrawRectAndText(pScene);  //����ͼ��
        pBaseItem = new QGroupItem(pOldItem);
        pBaseItem->SetPropertyValue("mText.Text",QVariant(""));
        pOldItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_XYTRENDCHART));

        InitParament();
    }

}

void QXYTrendCharGentDlg::on_Number_Data_valueChanged(int )
{
    emit GenNomberofDataChange();
}

void QXYTrendCharGentDlg::on_BackColor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->BackColor ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBackColorColor(const QColor &)));

}
void QXYTrendCharGentDlg::setBackColorColor(const QColor & mColor)       //����ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->BackColor->setStyleSheet(QString("background:%1").arg(mColor.name()));
 //   pBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(nColor));      //������������
}
void QXYTrendCharGentDlg::on_BG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->BG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBGColor(const QColor &)));

}
void QXYTrendCharGentDlg::setBGColor(const QColor & mColor)       //�ı�ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->BG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
   // pBaseItem->SetPropertyValue("mText.FontColor",QVariant(nColor));      //������������
}

void QXYTrendCharGentDlg::on_m_ifuse_clicked(bool checked)
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
void QXYTrendCharGentDlg::setCheckLineColor(const QColor &mColor)
{
    ui->m_checkcolor->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QXYTrendCharGentDlg::on_m_checkbtn_clicked()
{
    pwnd->Addr_Type=1;
    AddressInputDialog  dlg_triggered(checkaddr,this);
    dlg_triggered.exec();
    ui->m_checkaddredit->setText(checkaddr.sShowAddr);

}

void QXYTrendCharGentDlg::on_m_checkcolor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->m_checkcolor ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCheckLineColor(const QColor &)));

}
