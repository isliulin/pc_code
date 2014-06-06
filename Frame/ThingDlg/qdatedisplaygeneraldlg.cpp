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
    pScene = new QGraphicsScene(this);     //建场景
    ui->LView->setScene(pScene);           //用视图显示场景
    pwnd->OnAddPattern(ui->Pattern);  //加载样式
    pwnd->InitFontSize(ui->FontSize);//初始化字体大小选择框
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
    QString temp=ui->Separative_Sign->currentText();//取分隔符
    if(index==0)//YY MM DD
    {
        pBaseItem->SetPropertyValue("mText.Text",QVariant(sYear.right(2)+temp+sMonth+temp+sDate));      //调用设置属性
    }
    if(index==1)//YYYY MM DD
    {
        pBaseItem->SetPropertyValue("mText.Text",QVariant(sYear+temp+sMonth+temp+sDate));      //调用设置属性
    }
     else if(index==2)//MM-DD-YY
    {
        pBaseItem->SetPropertyValue("mText.Text",QVariant(sMonth+temp+sDate+temp+sYear.right(2)));      //调用设置属性
    }
     else if(index==3)//MM-DD-YYYY
     {
         pBaseItem->SetPropertyValue("mText.Text",QVariant(sMonth+temp+sDate+temp+sYear));      //调用设置属性
     }
     else if(index==4)//DD MM YY
     {
         pBaseItem->SetPropertyValue("mText.Text",QVariant(sDate+temp+sMonth+temp+sYear.right(2)));      //调用设置属性
     }
     else if(index==5)//DD MM YYYY
     {
         pBaseItem->SetPropertyValue("mText.Text",QVariant(sDate+temp+sMonth+temp+sYear));      //调用设置属性
     }
 }

void QDateDisplayGeneralDlg::on_Separative_Sign_currentIndexChanged(QString d)
{
    int index=ui->Format->currentIndex();

    QString temp=ui->Separative_Sign->currentText();//取分隔符
    if(index==0)//YY MM DD
    {
        pBaseItem->SetPropertyValue("mText.Text",QVariant(sYear.right(2)+temp+sMonth+temp+sDate));      //调用设置属性
    }
    if(index==1)//YYYY MM DD
    {
        pBaseItem->SetPropertyValue("mText.Text",QVariant(sYear+temp+sMonth+temp+sDate));      //调用设置属性
    }
     else if(index==2)//MM-DD-YY
    {
        pBaseItem->SetPropertyValue("mText.Text",QVariant(sMonth+temp+sDate+temp+sYear.right(2)));      //调用设置属性
    }
     else if(index==3)//MM-DD-YYYY
     {
         pBaseItem->SetPropertyValue("mText.Text",QVariant(sMonth+temp+sDate+temp+sYear));      //调用设置属性
     }
     else if(index==4)//DD MM YY
     {
         pBaseItem->SetPropertyValue("mText.Text",QVariant(sDate+temp+sMonth+temp+sYear.right(2)));      //调用设置属性
     }
     else if(index==5)//DD MM YYYY
     {
         pBaseItem->SetPropertyValue("mText.Text",QVariant(sDate+temp+sMonth+temp+sYear));      //调用设置属性
     }
 }

void QDateDisplayGeneralDlg::on_Pattern_currentIndexChanged(int index)
{
    if(!nInitFlag)//样式
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
{//左对齐
    if(checked)
    {
        pBaseItem->SetPropertyValue("mText.Alignment",QVariant(4)); //调用设置属性
    }
}

void QDateDisplayGeneralDlg::on_Alignment_Center_clicked(bool checked)
{//居中对齐
    if(checked)
    {
        pBaseItem->SetPropertyValue("mText.Alignment",QVariant(5)); //调用设置属性
    }
}

void QDateDisplayGeneralDlg::on_Alignment_Right_clicked(bool checked)
{//右对齐
    if(checked)
    {
        pBaseItem->SetPropertyValue("mText.Alignment",QVariant(6)); //调用设置属性
    }
}

void QDateDisplayGeneralDlg::on_FontSize_currentIndexChanged(QString sFontSize)
{//设置字体大小
    if(!nInitFlag)
    {
        return;
    }
    int nFontSize = sFontSize.toInt();
    pBaseItem->SetPropertyValue("mText.FontSize",QVariant(nFontSize));      //调用设置属性
}
void QDateDisplayGeneralDlg::TimeDisplayGenSave(QStringList *datalist, int index)
{
    QString sTmp;
    sTmp=ui->ID->text();//控件ID
    datalist->replace(index,sTmp);
    datalist->replace(19,sTmp);

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->Frame_Color->palette().background().color());//边框色
    datalist->replace(index+1,sTmp);

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->FG_Color->palette().background().color());//前景色
    datalist->replace(index+2,sTmp);

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->BG_Color->palette().background().color());//背景色
    datalist->replace(index+3,sTmp);

    sTmp.clear();
    sTmp=pwnd->ColorTOString(ui->Text_Color->palette().background().color());//文本色
    datalist->replace(index+4,sTmp);

    sTmp.clear();
    int nState=ui->Pattern->currentIndex();//样式索引
    sTmp=QString::number(nState);
    datalist->replace(index+5,sTmp);

    sTmp.clear();
    nState=ui->Format->currentIndex();//格式
    sTmp=QString::number(nState);
    datalist->replace(index+6,sTmp);

    sTmp.clear();
    nState=ui->Separative_Sign->currentIndex();//分隔符
    sTmp=QString::number(nState);
    datalist->replace(index+7,sTmp);

    sTmp.clear();
    sTmp=ui->Font->currentText();//字体
    datalist->replace(index+8,sTmp);

    sTmp.clear();
   // nState=ui->FontSize->currentIndex();//字体大小
    sTmp=ui->FontSize->currentText();
    datalist->replace(index+9,sTmp);

    sTmp.clear();
    nState=RadioButton_direction_Group->checkedId();//位置
    sTmp=QString::number(nState);
    datalist->replace(index+10,sTmp);

}
void QDateDisplayGeneralDlg::Init(QGraphicsItem *pItem)
{
    DrawItemToScene GroupFunction;
    QStringList pdataList;
    if(pItem)   //从Data 的 stringList中获取属性并设置
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
         *以下是单击工具栏的初始化
         **************************************************/
        QDrawGraphics *pDraw = new QDrawGraphics;                       //由基类生成一个对象
        pCopyItem = pDraw->OnDrawRectAndText(pScene);  //加载图形
        pBaseItem = new QGroupItem(pCopyItem);

        ui->ID->setText(pwnd->GetControlNO("DD"));
        ui->Frame_Color->setStyleSheet( QString("background:%1").arg(QColor(224,224,224).name()));
        ui->FG_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
        ui->BG_Color->setStyleSheet( QString("background:%1").arg(QColor(192,192,192).name()));
        ui->Text_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
        if(ui->Font->findText(tr("宋体"))==-1)
        {
            ui->Font->setCurrentIndex(0);
        }
        else
        {
            ui->Font->setCurrentIndex(ui->Font->findText(tr("宋体")));
        }
        ui->Alignment_Center->setChecked(true);


        pBaseItem->SetPropertyValue("mText.Text",QVariant(sYear.right(2)+"/"+sMonth+"/"+sDate));      //调用设置属性
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

        on_Font_currentIndexChanged(ui->Font->currentText());//字体
        on_FontSize_currentIndexChanged(ui->FontSize->currentText());//字体大小
        on_Format_currentIndexChanged(ui->Format->currentIndex());//格式
        on_Separative_Sign_currentIndexChanged(ui->Separative_Sign->currentText()); //分隔符

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
void QDateDisplayGeneralDlg::setFrameColor(const QColor & mColor)       //设置边框色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->Frame_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mFramRect.BackColor",QVariant(nColor));      //调用设置属性
}

void QDateDisplayGeneralDlg::on_FG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->FG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setFGColor(const QColor &)));
}
void QDateDisplayGeneralDlg::setFGColor(const QColor & mColor)       //前景色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->FG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mBackRect.FrontColor",QVariant(nColor));      //调用设置属性
}

void QDateDisplayGeneralDlg::on_BG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->BG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBGColor(const QColor &)));

}
void QDateDisplayGeneralDlg::setBGColor(const QColor & mColor)       //背景色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->BG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(nColor));      //调用设置属性
}
void QDateDisplayGeneralDlg::on_Text_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->Text_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setTextColor(const QColor &)));
}
void QDateDisplayGeneralDlg::setTextColor(const QColor & mColor)       //文本色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->Text_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mText.FontColor",QVariant(nColor));      //调用设置属性
}


void QDateDisplayGeneralDlg::on_Font_currentIndexChanged(QString sFont)
{
    if(nInitFlag)
    {
        pBaseItem->SetPropertyValue("mText.Font",QVariant(sFont));
    }
}
