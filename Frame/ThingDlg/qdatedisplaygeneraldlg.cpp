#include "qdatedisplaygeneraldlg.h"
#include "ui_qdatedisplaygeneraldlg.h"
#include "view/qdrawgraphics.h"
#include "Frame/DrawDlg/LoadShape.h"
#include "QDate"
#include <QFontDatabase>
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QDateDisplayGeneralDlg::QDateDisplayGeneralDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDateDisplayGeneralDlg)
{
    ui->setupUi(this);
    nInitFlag = false;
    date=QDate::currentDate();

    sDate=QString("%1").arg(date.day());
    sMonth=QString("%1").arg(date.month());
    sYear=QString("%1").arg(date.year());

    if(sMonth.length()==1)
    {
        sMonth="0"+sMonth;
    }
    if(sDate.length()==1)
    {
        sDate="0"+sDate;
    }
    pScene = new QGraphicsScene(this);     //������
    ui->LView->setScene(pScene);           //����ͼ��ʾ����
    pwnd->OnAddPattern(ui->Pattern);  //������ʽ
    pwnd->InitFontSize(ui->FontSize);//��ʼ�������Сѡ���
    ui->Font->addItems(QFontDatabase().families(QFontDatabase::Any));

    RadioButton_direction_Group=new QButtonGroup(this);
    RadioButton_direction_Group->addButton(ui->Alignment_Left,1);
    RadioButton_direction_Group->addButton(ui->Alignment_Center,2);
    RadioButton_direction_Group->addButton(ui->Alignment_Right,3);

    nInitFlag = true;

}

QDateDisplayGeneralDlg::~QDateDisplayGeneralDlg()
{
    if(pScene)
    {
        delete pScene;
        pScene = NULL;
    }
    if(pBaseItem)
    {
        delete pBaseItem;
        pBaseItem = NULL;
    }
    if(RadioButton_direction_Group)
    {
        delete RadioButton_direction_Group;
        RadioButton_direction_Group = NULL;
    }
    delete ui;
}
void QDateDisplayGeneralDlg::on_Format_currentIndexChanged(int index)
{
    QString temp=ui->Separative_Sign->currentText();//ȡ�ָ���
    if(index==0)//YY MM DD
    {
        pBaseItem->SetPropertyValue("mText.Text",QVariant(sYear.right(2)+temp+sMonth+temp+sDate));      //������������
    }
    if(index==1)//YYYY MM DD
    {
        pBaseItem->SetPropertyValue("mText.Text",QVariant(sYear+temp+sMonth+temp+sDate));      //������������
    }
     else if(index==2)//MM-DD-YY
    {
        pBaseItem->SetPropertyValue("mText.Text",QVariant(sMonth+temp+sDate+temp+sYear.right(2)));      //������������
    }
     else if(index==3)//MM-DD-YYYY
     {
         pBaseItem->SetPropertyValue("mText.Text",QVariant(sMonth+temp+sDate+temp+sYear));      //������������
     }
     else if(index==4)//DD MM YY
     {
         pBaseItem->SetPropertyValue("mText.Text",QVariant(sDate+temp+sMonth+temp+sYear.right(2)));      //������������
     }
     else if(index==5)//DD MM YYYY
     {
         pBaseItem->SetPropertyValue("mText.Text",QVariant(sDate+temp+sMonth+temp+sYear));      //������������
     }
 }

void QDateDisplayGeneralDlg::on_Separative_Sign_currentIndexChanged(QString d)
{
    int index=ui->Format->currentIndex();

    QString temp=ui->Separative_Sign->currentText();//ȡ�ָ���
    if(index==0)//YY MM DD
    {
        pBaseItem->SetPropertyValue("mText.Text",QVariant(sYear.right(2)+temp+sMonth+temp+sDate));      //������������
    }
    if(index==1)//YYYY MM DD
    {
        pBaseItem->SetPropertyValue("mText.Text",QVariant(sYear+temp+sMonth+temp+sDate));      //������������
    }
     else if(index==2)//MM-DD-YY
    {
        pBaseItem->SetPropertyValue("mText.Text",QVariant(sMonth+temp+sDate+temp+sYear.right(2)));      //������������
    }
     else if(index==3)//MM-DD-YYYY
     {
         pBaseItem->SetPropertyValue("mText.Text",QVariant(sMonth+temp+sDate+temp+sYear));      //������������
     }
     else if(index==4)//DD MM YY
     {
         pBaseItem->SetPropertyValue("mText.Text",QVariant(sDate+temp+sMonth+temp+sYear.right(2)));      //������������
     }
     else if(index==5)//DD MM YYYY
     {
         pBaseItem->SetPropertyValue("mText.Text",QVariant(sDate+temp+sMonth+temp+sYear));      //������������
     }
 }

void QDateDisplayGeneralDlg::on_Pattern_currentIndexChanged(int index)
{
    if(!nInitFlag)//��ʽ
        return;

    pBaseItem->SetPropertyValue("mBackRect.Pattern",QVariant(index));

    if(index == 0)
    {
        pBaseItem->SetPropertyValue("mFramRect.Pattern",QVariant(0));
        pBaseItem->setItemPattern(0);
    }
    else
    {
        pBaseItem->SetPropertyValue("mFramRect.Pattern",QVariant(1));
        pBaseItem->setItemPattern(1);
    }

}

void QDateDisplayGeneralDlg::on_Alignment_Left_clicked(bool checked)
{//�����
    if(checked)
    {
        pBaseItem->SetPropertyValue("mText.Alignment",QVariant(4)); //������������
    }
}

void QDateDisplayGeneralDlg::on_Alignment_Center_clicked(bool checked)
{//���ж���
    if(checked)
    {
        pBaseItem->SetPropertyValue("mText.Alignment",QVariant(5)); //������������
    }
}

void QDateDisplayGeneralDlg::on_Alignment_Right_clicked(bool checked)
{//�Ҷ���
    if(checked)
    {
        pBaseItem->SetPropertyValue("mText.Alignment",QVariant(6)); //������������
    }
}

void QDateDisplayGeneralDlg::on_FontSize_currentIndexChanged(QString sFontSize)
{//���������С
    if(!nInitFlag)
    {
        return;
    }
    int nFontSize = sFontSize.toInt();
    pBaseItem->SetPropertyValue("mText.FontSize",QVariant(nFontSize));      //������������
}
void QDateDisplayGeneralDlg::TimeDisplayGenSave(QStringList *datalist, int index)
{
    QString sTmp;
    sTmp=ui->ID->text();//�ؼ�ID
    datalist->replace(index,sTmp);
    datalist->replace(19,sTmp);

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->Frame_Color->palette().background().color());//�߿�ɫ
    datalist->replace(index+1,sTmp);

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->FG_Color->palette().background().color());//ǰ��ɫ
    datalist->replace(index+2,sTmp);

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->BG_Color->palette().background().color());//����ɫ
    datalist->replace(index+3,sTmp);

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->Text_Color->palette().background().color());//�ı�ɫ
    datalist->replace(index+4,sTmp);

    sTmp.clear();
    int nState=ui->Pattern->currentIndex();//��ʽ����
    sTmp=QString::number(nState);
    datalist->replace(index+5,sTmp);

    sTmp.clear();
    nState=ui->Format->currentIndex();//��ʽ
    sTmp=QString::number(nState);
    datalist->replace(index+6,sTmp);

    sTmp.clear();
    nState=ui->Separative_Sign->currentIndex();//�ָ���
    sTmp=QString::number(nState);
    datalist->replace(index+7,sTmp);

    sTmp.clear();
    sTmp=ui->Font->currentText();//����
    datalist->replace(index+8,sTmp);

    sTmp.clear();
   // nState=ui->FontSize->currentIndex();//�����С
    sTmp=ui->FontSize->currentText();
    datalist->replace(index+9,sTmp);

    sTmp.clear();
    nState=RadioButton_direction_Group->checkedId();//λ��
    sTmp=QString::number(nState);
    datalist->replace(index+10,sTmp);

}
void QDateDisplayGeneralDlg::Init(QGraphicsItem *pItem)
{
    DrawItemToScene GroupFunction;
    QStringList pdataList;
    if(pItem)   //��Data �� stringList�л�ȡ���Բ�����
    {
        GroupFunction.CopyItem(&pCopyItem,pItem);
        pScene->addItem(pCopyItem);
        pBaseItem = new QGroupItem(pCopyItem);
        pBaseItem->SetWidth(100);
        pBaseItem->SetHeigth(100);
        pdataList = qVariantValue<QStringList>(pCopyItem->data(GROUP_DATALIST_KEY));
        ui->ID->setText(pdataList.at(19));
        ui->Frame_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(pdataList.at(41)).name()));
        ui->FG_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(pdataList.at(42)).name()));
        ui->BG_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(pdataList.at(43)).name()));
        ui->Text_Color->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(pdataList.at(44)).name()));
        ui->Pattern->setCurrentIndex(pdataList.at(45).toInt());
        ui->Format->setCurrentIndex(pdataList.at(46).toInt());
        ui->Separative_Sign->setCurrentIndex(pdataList.at(47).toInt());
        if(ui->Font->findText(pdataList.at(48))==-1)
        {
            ui->Font->setCurrentIndex(0);
        }
        else
        {
            ui->Font->setCurrentIndex(ui->Font->findText(pdataList.at(48)));
        }
        ui->FontSize->setCurrentIndex(ui->FontSize->findText(pdataList.at(49)));
        RadioButton_direction_Group->button(pdataList.at(50).toInt())->setChecked(true);
        if(RadioButton_direction_Group->checkedId()==1)
        {
            on_Alignment_Left_clicked(true);
        }
        else if(RadioButton_direction_Group->checkedId()==2)
        {
            on_Alignment_Center_clicked(true);
        }
        else if(RadioButton_direction_Group->checkedId()==3)
        {
            on_Alignment_Right_clicked(true);
        }
        on_Format_currentIndexChanged(pdataList.at(46).toInt());
     }
    else
    {
        /***************************************************
         *�����ǵ����������ĳ�ʼ��
         **************************************************/
        QDrawGraphics *pDraw = new QDrawGraphics;                       //�ɻ�������һ������
        pCopyItem = pDraw->OnDrawRectAndText(pScene);  //����ͼ��
        pBaseItem = new QGroupItem(pCopyItem);

        ui->ID->setText(pwnd->GetControlNO("DD"));
        ui->Frame_Color->setStyleSheet( QString("background:%1").arg(QColor(224,224,224).name()));
        ui->FG_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
        ui->BG_Color->setStyleSheet( QString("background:%1").arg(QColor(192,192,192).name()));
        ui->Text_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
        if(ui->Font->findText(tr("����"))==-1)
        {
            ui->Font->setCurrentIndex(0);
        }
        else
        {
            ui->Font->setCurrentIndex(ui->Font->findText(tr("����")));
        }
        ui->Alignment_Center->setChecked(true);


        pBaseItem->SetPropertyValue("mText.Text",QVariant(sYear.right(2)+"/"+sMonth+"/"+sDate));      //������������
        delete pDraw;
        pDraw=NULL;
//        pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_DATEDISPLAY));
    }
}
void QDateDisplayGeneralDlg::on_LoadShape_clicked()
{
    LoadShape *pShapeDlg = new LoadShape(this);
    if(pShapeDlg->exec() == QDialog::Accepted)
    {
        DrawItemToScene GroupFunction;
        QPointF oldpos = pCopyItem->sceneBoundingRect().topLeft();

        GroupFunction.CopyItem(&pCopyItem,pShapeDlg->pCopyItem);
        pScene->clear();
        pScene->addItem(pCopyItem);
        pBaseItem = new QGroupItem(pCopyItem);

        setFrameColor(ui->Frame_Color->palette().background().color());
        setFGColor(ui->FG_Color->palette().background().color());
        setBGColor(ui->BG_Color->palette().background().color());
        setTextColor(ui->Text_Color->palette().background().color());
        on_Pattern_currentIndexChanged(ui->Pattern->currentIndex());

        on_Font_currentIndexChanged(ui->Font->currentText());//����
        on_FontSize_currentIndexChanged(ui->FontSize->currentText());//�����С
        on_Format_currentIndexChanged(ui->Format->currentIndex());//��ʽ
        on_Separative_Sign_currentIndexChanged(ui->Separative_Sign->currentText()); //�ָ���

        if(ui->Alignment_Left->isChecked())
            on_Alignment_Left_clicked(true);
        else if(ui->Alignment_Center->isChecked())
            on_Alignment_Center_clicked(true);
        else if(ui->Alignment_Right->isChecked())
            on_Alignment_Right_clicked(true);

        QPointF newpos = pCopyItem->boundingRect().topLeft();
        pCopyItem->setPos(oldpos-newpos);
    }
    pShapeDlg->deleteLater();
    pShapeDlg = NULL;
}

void QDateDisplayGeneralDlg::on_Frame_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->Frame_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setFrameColor(const QColor &)));

}
void QDateDisplayGeneralDlg::setFrameColor(const QColor & mColor)       //���ñ߿�ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->Frame_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mFramRect.BackColor",QVariant(nColor));      //������������
}

void QDateDisplayGeneralDlg::on_FG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->FG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setFGColor(const QColor &)));
}
void QDateDisplayGeneralDlg::setFGColor(const QColor & mColor)       //ǰ��ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->FG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mBackRect.FrontColor",QVariant(nColor));      //������������
}

void QDateDisplayGeneralDlg::on_BG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->BG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBGColor(const QColor &)));

}
void QDateDisplayGeneralDlg::setBGColor(const QColor & mColor)       //����ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->BG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(nColor));      //������������
}
void QDateDisplayGeneralDlg::on_Text_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->Text_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setTextColor(const QColor &)));
}
void QDateDisplayGeneralDlg::setTextColor(const QColor & mColor)       //�ı�ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->Text_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mText.FontColor",QVariant(nColor));      //������������
}


void QDateDisplayGeneralDlg::on_Font_currentIndexChanged(QString sFont)
{
    if(nInitFlag)
    {
        pBaseItem->SetPropertyValue("mText.Font",QVariant(sFont));
    }
}
