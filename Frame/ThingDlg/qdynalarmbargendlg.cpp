#include "qdynalarmbargendlg.h"
#include "ui_qdynalarmbargendlg.h"
#include "view/qdrawgraphics.h"
#include "Frame/qprogectmanager.h"
#include "Frame/mainwindow.h"
#include "groupseldlg.h"

extern MainWindow *pwnd;
#include "Frame/DrawDlg/LoadShape.h"
QDynAlarmBarGenDlg::QDynAlarmBarGenDlg(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::QDynAlarmBarGenDlg)
{
    ui->setupUi(this);
    //ui->Shape->setVisible(false);
    nInitFlag=false;//样式标示
    pwnd->OnAddPattern(ui->Pattern);  //加载样式
    pwnd->InitFontSize(ui->FontSize);//初始化字体大小

    RadioButton_direction_Group=new QButtonGroup(this);
    RadioButton_direction_Group->addButton(ui->Left,1);
    RadioButton_direction_Group->addButton(ui->Right,2);

    RadioButton_AlarmSort_Group=new QButtonGroup(this);
    RadioButton_AlarmSort_Group->addButton(ui->Time,1);
    RadioButton_AlarmSort_Group->addButton(ui->Time_Re,2);

    nInitFlag=true;

    foreach(ALARM_GROUP alarmGrp,pwnd->m_pSamSysParame->m_qvcAlarm)
    {
        //ui->combo_groupname->addItem(alarmGrp.alarmName);
    }

}

QDynAlarmBarGenDlg::~QDynAlarmBarGenDlg()
{

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
void QDynAlarmBarGenDlg::on_Pattern_currentIndexChanged(int index)
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
void QDynAlarmBarGenDlg::DynAlarmBarGenSave(securityPro sproperty)
{

    QString sTmp;

    alarmPro.frameColor = ui->Frame_Color->palette().background().color();//边框色


    alarmPro.frColor = ui->FG_Color->palette().background().color();//前景色


    alarmPro.backColor = ui->BG_Color->palette().background().color();//背景色


    alarmPro.textColor = ui->Text_Color->palette().background().color();//文本色

    int nState=ui->Pattern->currentIndex();//样式索引
    alarmPro.nPattern = nState;

    nState=ui->FontSize->currentIndex();//字体大小
    alarmPro.fontSize = nState;

    nState=ui->Speed->value();//速度
    alarmPro.speed = nState;



    nState=RadioButton_direction_Group->checkedId();//位置
    alarmPro.direction = nState;

    nState=RadioButton_AlarmSort_Group->checkedId();//报警排序
    alarmPro.sort = nState;
    alarmPro.bSelectall = bAll;
    if(!bAll)
    {
        alarmPro.groupName = groupNames;
    }

    //alarmPro.groupName = ui->combo_groupname->currentText();

    AlarmBar *alarmbar = dynamic_cast<AlarmBar *> (pCopyItem);
    if(!alarmbar)
        return;
    alarmbar->stPro = alarmPro;
    alarmbar->SaveSecurityPro(&sproperty);
}
void QDynAlarmBarGenDlg::setid(int id)
{
    AlarmBar *alarmbar = dynamic_cast<AlarmBar *> (pCopyItem);
    if(!alarmbar)
        return;
    alarmbar->setId(id);
}
void QDynAlarmBarGenDlg::Init(QGraphicsItem *pItem)
{
    DrawItemToScene GroupFunction;
    QStringList pdataList;
    if(pItem)
    {
        GroupFunction.CopyItem(&pCopyItem,pItem);
        //pScene->addItem(pCopyItem);
        pBaseItem = new QGroupItem(pCopyItem);
        AlarmBar *alarmbar = dynamic_cast<AlarmBar *> (pItem);
        if(alarmbar)
            alarmPro = alarmbar->stPro;

        ui->Frame_Color->setStyleSheet(QString("background:%1").arg(alarmPro.frameColor.name()));
        ui->FG_Color->setStyleSheet(QString("background:%1").arg(alarmPro.frColor.name()));
        ui->BG_Color->setStyleSheet(QString("background:%1").arg(alarmPro.backColor.name()));
        ui->Text_Color->setStyleSheet(QString("background:%1").arg(alarmPro.textColor.name()));
        ui->Pattern->setCurrentIndex(alarmPro.nPattern);
        ui->FontSize->setCurrentIndex(alarmPro.fontSize);
        ui->Speed->setValue(alarmPro.speed);
        RadioButton_direction_Group->button(alarmPro.direction)->setChecked(true);
        RadioButton_AlarmSort_Group->button(alarmPro.sort)->setChecked(true);
        bAll = alarmPro.bSelectall;
        groupNames = alarmPro.groupName;
        //int index = ui->combo_groupname->findText(alarmPro.groupName);

        //if(index>=0)
        {
            //ui->combo_groupname->setCurrentIndex(index);
        }

    }
    else
    {
        /***************************************************
         *以下是单击工具栏的初始化
         **************************************************/
        //ui->ID->setText(pwnd->GetControlNO("AB"));

        AlarmBar *alarmbar = new AlarmBar;  //
        alarmbar->SetDefault();
        pCopyItem = alarmbar;
        pBaseItem = new QGroupItem(pCopyItem);

        pBaseItem->SetPropertyValue("mText.Text",QVariant("Sample Message"));
        ui->Frame_Color->setStyleSheet( QString("background:%1").arg(QColor(224,224,224).name()));
        ui->FG_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
        ui->BG_Color->setStyleSheet( QString("background:%1").arg(QColor(192,192,192).name()));
        ui->Text_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
        RadioButton_direction_Group->button(1)->setChecked(true);
        RadioButton_AlarmSort_Group->button(1)->setChecked(true);
        bAll = true;
//        ui->m_lable1->setVisible(false);
//        ui->m_label2->setVisible(false);
//        ui->m_spin1->setVisible(false);
//        ui->m_spin2->setVisible(false);
        //ui->m_allalarmcheck->setChecked(true);
        //on_m_allalarmcheck_clicked(true);

        //int digitalSize = pwnd->m_pSamSysParame->m_qvcAlarm.size();
        //ui->m_spin2->setValue(digitalSize-1);
    }
}


void QDynAlarmBarGenDlg::on_FontSize_currentIndexChanged(QString sFontSize)
{
    if(!nInitFlag)
        return;
    int nFontSize = sFontSize.toInt();
    pBaseItem->SetPropertyValue("mText.FontSize",QVariant(nFontSize));      //调用设置属性

}


void QDynAlarmBarGenDlg::on_Frame_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->Frame_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setFrameColor(const QColor &)));

}
void QDynAlarmBarGenDlg::setFrameColor(const QColor & mColor)       //设置边框色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->Frame_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mFramRect.BackColor",QVariant(nColor));      //调用设置属性
}

void QDynAlarmBarGenDlg::on_FG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->FG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setFGColor(const QColor &)));
}
void QDynAlarmBarGenDlg::setFGColor(const QColor & mColor)       //前景色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->FG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mBackRect.FrontColor",QVariant(nColor));      //调用设置属性
}

void QDynAlarmBarGenDlg::on_BG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->BG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBGColor(const QColor &)));

}
void QDynAlarmBarGenDlg::setBGColor(const QColor & mColor)       //背景色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->BG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(nColor));      //调用设置属性
}
void QDynAlarmBarGenDlg::on_Text_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->Text_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setTextColor(const QColor &)));

}
void QDynAlarmBarGenDlg::setTextColor(const QColor & mColor)       //文本色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->Text_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mText.FontColor",QVariant(nColor));      //调用设置属性
}

void QDynAlarmBarGenDlg::on_Shape_clicked()//load shape
{
    LoadShape *pShapeDlg = new LoadShape(this);
    if(pShapeDlg->exec() == QDialog::Accepted)
    {
        DrawItemToScene GroupFunction;
        QPointF oldpos = pCopyItem->sceneBoundingRect().topLeft();

        GroupFunction.CopyItem(&pCopyItem,pShapeDlg->pCopyItem);

        pBaseItem = new QGroupItem(pCopyItem);
        pBaseItem->SetPropertyValue("mText.Text",QVariant("Sample Message"));

        setFrameColor(ui->Frame_Color->palette().background().color());
        setFGColor(ui->FG_Color->palette().background().color());
        setBGColor(ui->BG_Color->palette().background().color());
        setTextColor(ui->Text_Color->palette().background().color());

        on_Pattern_currentIndexChanged(ui->Pattern->currentIndex());
        on_FontSize_currentIndexChanged(ui->FontSize->currentText());//字体大小

        QPointF newpos = pCopyItem->boundingRect().topLeft();
        pCopyItem->setPos(oldpos-newpos);
    }
    pShapeDlg->deleteLater();
    pShapeDlg = NULL;
}



void QDynAlarmBarGenDlg::on_btn_groupset_clicked()
{
    GroupSelDlg dlg(groupNames,bAll,this);
    if(dlg.exec() == QDialog::Accepted)
    {
        groupNames = dlg.getNames(bAll);
    }
}
