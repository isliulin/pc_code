#include "qhistrenddisplaygendlg.h"
#include "Frame/mainwindow.h"
#include "view/qdrawgraphics.h"
extern MainWindow *pwnd;

QHisTrendDisplayGenDlg::QHisTrendDisplayGenDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QHisTrendDisplayGenDlg)
{
    ui->setupUi(this);
    on_NumberofCurve_currentIndexChanged(1);
    ui->DataLagger->addItem(pwnd->m_pSamSysParame->m_historyLogData.sHistoryDataName);

}

QHisTrendDisplayGenDlg::~QHisTrendDisplayGenDlg()
{
    delete ui;
}

void QHisTrendDisplayGenDlg::InitParament()
{
    ui->m_noedit->setText(pwnd->GetControlNO("HT"));
    ui->BackColor->setStyleSheet( QString("background:%1").arg(QColor(192,192,192).name()));
    ui->BGColor->setStyleSheet( QString("background:%1").arg(QColor(255,255,0).name()));
    ui->m_checkcolor->setStyleSheet( QString("background:%1").arg(QColor(255,0,0).name()));
    on_m_ifuse_clicked(false); //������
    on_bIfControlAddress_clicked();
}

void QHisTrendDisplayGenDlg::on_NumberofCurve_currentIndexChanged(int index)
{
    emit GenNomberofDataChange();
}

void QHisTrendDisplayGenDlg::SaveGeneralPage(QStringList *datalist, int index)
{
    QString sTmp = "";
    int nTmp = 0;

    datalist->replace(19,ui->m_noedit->text());

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->BackColor->palette().background().color());//���ÿ�ܵı���ɫ
    datalist->replace(index,sTmp);

    nTmp=ui->DataLagger->currentIndex();
    sTmp=QString::number(nTmp);
    datalist->replace(index+1,sTmp);//�����ռ� 151

    sTmp=pwnd->KeyboardToString(kControl_Address_Keyboard);//���ƼĴ���Keyboard
    datalist->replace(index+2,sTmp);

    nTmp=ui->bIfControlAddress->isChecked();
    sTmp=QString::number(nTmp);
    datalist->replace(index+3,sTmp); //�Ƿ����ÿ��Ƶ�ַ 153

    nTmp=ui->NumberofCurve->currentIndex()+1;
    sTmp=QString::number(nTmp);
    datalist->replace(index+4,sTmp); //�������� 154

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->BGColor->palette().background().color());//���ÿ�ܵı߿�ɫ
    datalist->replace(index+9,sTmp);
    //������ģ��
    sTmp.clear();
    nTmp=ui->m_ifuse->isChecked(); //�Ƿ����ü��
    sTmp=QString::number(nTmp);
    datalist->replace(index+15,sTmp); //If_Show_Data_Point 156

    sTmp=pwnd->ColorTOString(ui->m_checkcolor->palette().background().color());//�������ɫ
    datalist->replace(index+16,sTmp);//157

    sTmp=pwnd->KeyboardToString(checkaddr);//����ַ 158
    datalist->replace(index+17,sTmp);

    sTmp.clear();
    nTmp=ui->Transparence->value();//�Ƿ����ü��
    sTmp=QString::number(nTmp);
    datalist->replace(index+12,sTmp); //If_Show_Data_Point 164


}
void QHisTrendDisplayGenDlg::Init(QGraphicsItem *pItem)
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
        ui->BackColor->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(dataList.at(150)).name()));//����ɫ
        ui->BGColor->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(dataList.at(159)).name()));//��ɫ
        ui->NumberofCurve->setCurrentIndex(dataList.at(154).toInt()-1);
        emit GenNomberofDataChange();//ˢ�±�ҳ��
        ui->DataLagger->setCurrentIndex(dataList.at(151).toInt());
        ui->bIfControlAddress->setChecked(dataList.at(153).toInt());//�Ƿ�ʹ�ÿ��Ƶ�ַ
        pwnd->StringToKeyboard(kControl_Address_Keyboard,dataList.at(152));//���ƼĴ�����ַ
        ui->kControlRs->setText(kControl_Address_Keyboard.sShowAddr);
        ui->m_ifuse->setChecked(dataList.at(165).toInt()); //�Ƿ�ʹ��
        on_m_ifuse_clicked(dataList.at(165).toInt());

        ui->m_checkcolor->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(dataList.at(166)).name()));
        pwnd->StringToKeyboard(checkaddr,dataList.at(167));//����ַ
        ui->m_checkaddredit->setText(checkaddr.sShowAddr);
        ui->Transparence->setValue(dataList.at(162).toInt());
        on_bIfControlAddress_clicked();
    }
    else
    {
        InitParament();
    }
}
void QHisTrendDisplayGenDlg::on_BackColor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->BackColor ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBackColor(const QColor &)));

}
void QHisTrendDisplayGenDlg::setBackColor(const QColor & mColor)       //�ı�ɫ
{
    ui->BackColor->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QHisTrendDisplayGenDlg::on_BGColor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->BGColor ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBGColor(const QColor &)));

}
void QHisTrendDisplayGenDlg::setBGColor(const QColor & mColor)       //�ı�ɫ
{
    ui->BGColor->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QHisTrendDisplayGenDlg::on_m_ifuse_clicked(bool checked)
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
void QHisTrendDisplayGenDlg::setCheckLineColor(const QColor &mColor)
{
    ui->m_checkcolor->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QHisTrendDisplayGenDlg::on_m_checkbtn_clicked()
{
    pwnd->Addr_Type=1;
    AddressInputDialog  dlg_triggered(checkaddr,this);
    dlg_triggered.exec();
    ui->m_checkaddredit->setText(checkaddr.sShowAddr);

}

void QHisTrendDisplayGenDlg::on_m_checkcolor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->m_checkcolor ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCheckLineColor(const QColor &)));
}


void QHisTrendDisplayGenDlg::on_kControlbtn_clicked()
{
    pwnd->Addr_Type=1;
    AddressInputDialog  dlg_triggered(kControl_Address_Keyboard,this);
    dlg_triggered.exec();
    ui->kControlRs->setText(kControl_Address_Keyboard.sShowAddr);

}

void QHisTrendDisplayGenDlg::on_bIfControlAddress_clicked()
{
    bool bTemp=ui->bIfControlAddress->isChecked();
    if(bTemp)
    {
        ui->label_8->setHidden(false);
        ui->kControlbtn->setHidden(false);
        ui->kControlRs->setHidden(false);
    }
    else
    {
        ui->label_8->setHidden(true);
        ui->kControlbtn->setHidden(true);
        ui->kControlRs->setHidden(true);
    }
}
