#include "qtimedisplaygeneraldlg.h"
#include "ui_qtimedisplaygeneraldlg.h"

#include "Frame/DrawDlg/LoadShape.h"
#include "view/qdrawgraphics.h"
#include "Frame/mainwindow.h"
#include <QFontDatabase>

#include <QGraphicsItem>
#include <QTime>

extern MainWindow *pwnd;

QTimeDisplayGeneralDLg::QTimeDisplayGeneralDLg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QTimeDisplayGeneralDLg)
{
    ui->setupUi(this);
    QTime time = QTime::currentTime();      //��õ�ǰʱ��
    sHour = QString("%1").arg(time.hour());
    if(sHour.length()==1)
    {
        sHour="0"+sHour;
    }
    sMinute = QString("%1").arg(time.minute());
    if(sMinute.length()==1)
    {
        sMinute="0"+sMinute;
    }
    sSecond = QString("%1").arg(time.second());
    if(sSecond.length()==1)
    {
        sSecond="0"+sSecond;
    }
    nInitFlag = false;

    pScene = new QGraphicsScene(this);     //������
    ui->LView->setScene(pScene);           //����ͼ��ʾ����
    pwnd->OnAddPattern(ui->m_patterncmb);  //������ʽ
    pwnd->InitFontSize(ui->m_fontsizecmb);//��ʼ�������Сѡ���
    ui->m_fontcmb->addItems(QFontDatabase().families(QFontDatabase::Any));

    RadioButton_direction_Group=new QButtonGroup(this);
    RadioButton_direction_Group->addButton(ui->m_leftradio,1);
    RadioButton_direction_Group->addButton(ui->m_middleradio,2);
    RadioButton_direction_Group->addButton(ui->m_rightradio,3);
    nInitFlag = true;
}

QTimeDisplayGeneralDLg::~QTimeDisplayGeneralDLg()
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
    if(RadioButton_direction_Group)
    {
        delete RadioButton_direction_Group;
        RadioButton_direction_Group=NULL;
    }
    delete ui;
}


void QTimeDisplayGeneralDLg::on_m_fontsizecmb_currentIndexChanged(int ) //�����С�ı�
{
    if(!nInitFlag)//��ʽ
        return;

    QString sFontSize = ui->m_fontsizecmb->currentText();
    int nFontSize = sFontSize.toInt();
    pBaseItem->SetPropertyValue("mText.FontSize",QVariant(nFontSize));      //������������
}



void QTimeDisplayGeneralDLg::on_m_leftradio_clicked() //�ı�����
{
    nAlignment = 0;
    pBaseItem->SetPropertyValue("mText.Alignment",QVariant(4)); //������������
}

void QTimeDisplayGeneralDLg::on_m_middleradio_clicked() //�ı�����
{
    nAlignment = 1;
    pBaseItem->SetPropertyValue("mText.Alignment",QVariant(5)); //������������
}

void QTimeDisplayGeneralDLg::on_m_rightradio_clicked() //�ı�����
{
    nAlignment = 2;
    pBaseItem->SetPropertyValue("mText.Alignment",QVariant(6)); //������������
}

void QTimeDisplayGeneralDLg::on_m_formatcmb_currentIndexChanged(int index) //ʱ���ʽ
{
    if(!nInitFlag)//��ʽ
    return;

    QString sHour = "";
    QString sMinute = "";
    QString sSecond = "";
    QString sTime = "";
    int nIndex = ui->m_formatcmb->currentIndex();

    QTime time = QTime::currentTime();      //��õ�ǰʱ��
    sHour = QString("%1").arg(time.hour());
    sMinute = QString("%1").arg(time.minute());
    sSecond = QString("%1").arg(time.second());
    if(sHour.length()==1)
    {
        sHour="0"+sHour;
    }
    if(sMinute.length()==1)
    {
        sMinute="0"+sMinute;
    }
    if(sSecond.length()==1)
    {
        sSecond="0"+sSecond;
    }

    if(nIndex == 0)       //hh:mm
    {
        sTime = sHour +":"+sMinute;
    }
    else if(nIndex == 1)  //hh:mm:ss
    {
        sTime = sHour +":"+sMinute+":"+sSecond;
    }
    else if(nIndex == 2)  //hh:mm:ss
    {
        sTime = sHour +"-"+sMinute+"-"+sSecond;
    } else if(nIndex == 3)  //hh:mm:ss
    {
        sTime = sHour +"-"+sMinute;
    }
    pBaseItem->SetPropertyValue("mText.Text",QVariant(sTime));      //������������
}
void QTimeDisplayGeneralDLg::on_m_patterncmb_currentIndexChanged(int index) //������ʽ
{
    if(!nInitFlag)
        return;
    int nIndex = ui->m_patterncmb->currentIndex();
    pBaseItem->SetPropertyValue("mBackRect.Pattern",QVariant(nIndex));
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
void QTimeDisplayGeneralDLg::TimeDisplayGenSave(QStringList *datalist, int index)
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
    int nState=ui->m_patterncmb->currentIndex();//��ʽ����
    sTmp=QString::number(nState);
    datalist->replace(index+5,sTmp);

    sTmp.clear();
    nState=ui->m_formatcmb->currentIndex();//��ʽ
    sTmp=QString::number(nState);
    datalist->replace(index+6,sTmp);

    sTmp.clear();
    sTmp=ui->m_fontcmb->currentText();//����
    datalist->replace(index+7,sTmp);

    sTmp.clear();
  //  nState=ui->m_fontsizecmb->currentIndex();//�����С
    sTmp=ui->m_fontsizecmb->currentText();
    datalist->replace(index+8,sTmp);

    sTmp.clear();
    nState=RadioButton_direction_Group->checkedId();//λ��
    sTmp=QString::number(nState);
    datalist->replace(index+9,sTmp);

}
void QTimeDisplayGeneralDLg::Init(QGraphicsItem *pItem)
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

        ui->m_patterncmb->setCurrentIndex(pdataList.at(45).toInt());
        ui->m_formatcmb->setCurrentIndex(pdataList.at(46).toInt());
        on_m_formatcmb_currentIndexChanged(pdataList.at(46).toInt());
        if(ui->m_fontcmb->findText(pdataList.at(47))==-1)
        {
            ui->m_fontcmb->setCurrentIndex(0);
        }
        else
        {
            ui->m_fontcmb->setCurrentIndex(ui->m_fontcmb->findText(pdataList.at(47)));
        }

        ui->m_fontsizecmb->setCurrentIndex(ui->m_fontsizecmb->findText(pdataList.at(48)));
        RadioButton_direction_Group->button(pdataList.at(49).toInt())->setChecked(true);
        if(RadioButton_direction_Group->checkedId()==1)
        {
            on_m_leftradio_clicked();
        }
        else if(RadioButton_direction_Group->checkedId()==2)
        {
            on_m_middleradio_clicked();
        }
        else if(RadioButton_direction_Group->checkedId()==3)
        {
            on_m_rightradio_clicked();
        }
     }
    else
    {
        /***************************************************
         *�����ǵ����������ĳ�ʼ��
         **************************************************/
        QDrawGraphics *pDraw = new QDrawGraphics;                       //�ɻ�������һ������
        pCopyItem = pDraw->OnDrawRectAndText(pScene);  //����ͼ��
        pBaseItem = new QGroupItem(pCopyItem);
        nAlignment=1;
        ui->ID->setText(pwnd->GetControlNO("TS"));
        ui->Frame_Color->setStyleSheet( QString("background:%1").arg(QColor(224,224,224).name()));
        ui->FG_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
        ui->BG_Color->setStyleSheet( QString("background:%1").arg(QColor(192,192,192).name()));
        ui->Text_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
        if(ui->m_fontcmb->findText(tr("����"))==-1)
        {
            ui->m_fontcmb->setCurrentIndex(0);
        }
        else
        {
            ui->m_fontcmb->setCurrentIndex(ui->m_fontcmb->findText(tr("����")));
        }

        ui->m_middleradio->setChecked(true);
        sTime = sHour +":"+sMinute;
        pBaseItem->SetPropertyValue("mText.Text",QVariant(sTime));      //������������
        pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_TIMEDISPLAY));
        if(pDraw)
        {
            delete pDraw;
            pDraw = NULL;
        }
    }
}


void QTimeDisplayGeneralDLg::on_LoadShape_clicked()
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
         on_m_patterncmb_currentIndexChanged(ui->m_patterncmb->currentIndex());

        on_m_fontcmb_currentIndexChanged(ui->m_fontcmb->currentText());//����
        on_m_fontsizecmb_currentIndexChanged(ui->m_fontsizecmb->currentIndex());//�����С
        on_m_formatcmb_currentIndexChanged(ui->m_formatcmb->currentIndex());//��ʽ

        if(nAlignment == 0)
            on_m_leftradio_clicked();
        else if(nAlignment == 1)
            on_m_middleradio_clicked();
        else if(nAlignment == 2)
            on_m_rightradio_clicked();

        QPointF newpos = pCopyItem->boundingRect().topLeft();
        pCopyItem->setPos(oldpos-newpos);
    }
    pShapeDlg->deleteLater();
    pShapeDlg = NULL;
}

void QTimeDisplayGeneralDLg::on_Frame_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->Frame_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setFrameColor(const QColor &)));

}
void QTimeDisplayGeneralDLg::setFrameColor(const QColor & mColor)       //���ñ߿�ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->Frame_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mFramRect.BackColor",QVariant(nColor));      //������������
}

void QTimeDisplayGeneralDLg::on_FG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->FG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setFGColor(const QColor &)));
}
void QTimeDisplayGeneralDLg::setFGColor(const QColor & mColor)       //ǰ��ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->FG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mBackRect.FrontColor",QVariant(nColor));      //������������
}

void QTimeDisplayGeneralDLg::on_BG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->BG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBGColor(const QColor &)));

}
void QTimeDisplayGeneralDLg::setBGColor(const QColor & mColor)       //����ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->BG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(nColor));      //������������
}
void QTimeDisplayGeneralDLg::on_Text_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->Text_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setTextColor(const QColor &)));

}
void QTimeDisplayGeneralDLg::setTextColor(const QColor & mColor)       //�ı�ɫ
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->Text_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    pBaseItem->SetPropertyValue("mText.FontColor",QVariant(nColor));      //������������
}

void QTimeDisplayGeneralDLg::on_m_fontcmb_currentIndexChanged(QString sFont)
{
    if(nInitFlag)
    {
        pBaseItem->SetPropertyValue("mText.Font",QVariant(sFont));
    }

}
