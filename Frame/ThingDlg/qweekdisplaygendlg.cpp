#include "qweekdisplaygendlg.h"
#include "Frame/DrawDlg/LoadShape.h"
#include "view/qdrawgraphics.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QWeekDisplayGenDlg::QWeekDisplayGenDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QWeekDisplayGenDlg)
{
    ui->setupUi(this);

    InitFlag = false;
    pScene = new QGraphicsScene(this);     //������
    ui->MainView->setScene(pScene);

    pwnd->OnAddPattern(ui->m_patterncmb);

    InitFlag = true;
}

void QWeekDisplayGenDlg::InitParament()
{
    int i = 0;

    ui->lineEdit->setText(pwnd->GetControlNO("DW"));
    QDrawGraphics *pDraw = new QDrawGraphics;     //�ɻ�������һ������
    pOldItem = pDraw->OnDrawRectAndText(pScene);  //����ͼ��
    pBaseItem = new QGroupItem(pOldItem);

    pBaseItem->SetPropertyValue("mText.Text",QVariant(tr("Sunday")));
    pBaseItem->SetPropertyValue("mText.FontSize",QVariant(10));

    for(i = 0; i < 7; i++)                                  //��ʼ���ṹ��
    {
        WeekDay[i].sBorderColor = "224+224+224";     //�߿�ɫ
        WeekDay[i].sFrontColor = "0+0+0";      //ǰ��ɫ
        WeekDay[i].sBackColor = "192+192+192";       //����ɫ
        WeekDay[i].nPattern = 1;                     //��ʽ
    }
    ui->Frame_Color->setStyleSheet( QString("background:%1").arg(QColor(224,224,224).name()));
    ui->FG_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
    ui->BG_Color->setStyleSheet( QString("background:%1").arg(QColor(192,192,192).name()));
}

QWeekDisplayGenDlg::~QWeekDisplayGenDlg()
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

void QWeekDisplayGenDlg::on_m_statespin_valueChanged(int ) //״̬
{
    if(!InitFlag)
        return;
    int nState = ui->m_statespin->value();
    emit GeneralStateChange();

    pBaseItem->SetPropertyValue("mFramRect.BackColor",QVariant(WeekDay[nState].sBorderColor));
    pBaseItem->SetPropertyValue("mBackRect.FrontColor",QVariant(WeekDay[nState].sFrontColor));
    pBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(WeekDay[nState].sBackColor));
    pBaseItem->SetPropertyValue("mBackRect.Pattern",QVariant(WeekDay[nState].nPattern));

    QColor mColor;
    mColor = pwnd->StringTOColor(WeekDay[nState].sBorderColor);
    ui->Frame_Color->setStyleSheet( QString("background:%1").arg(mColor.name()));
          //��ʼ����ɫѡ���

    mColor = pwnd->StringTOColor(WeekDay[nState].sFrontColor);
    ui->FG_Color->setStyleSheet( QString("background:%1").arg(mColor.name()));

    mColor = pwnd->StringTOColor(WeekDay[nState].sBackColor);
    ui->BG_Color->setStyleSheet( QString("background:%1").arg(mColor.name()));

    ui->m_patterncmb->setCurrentIndex(WeekDay[nState].nPattern);
}
void QWeekDisplayGenDlg::on_m_patterncmb_currentIndexChanged(int index)//��ʽ
{
    if(!InitFlag)
        return;

    int nState = ui->m_statespin->value();
    int nIndex = ui->m_patterncmb->currentIndex();
    WeekDay[nState].nPattern = nIndex;
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

void QWeekDisplayGenDlg::SaveWeekGeneralPage(QStringList *datalist, int index)
{
    QString sTmp;
    int i = 0;

    datalist->replace(19,ui->lineEdit->text()); //���

    sTmp=QString::number(ui->m_statespin->value());  //��ǰ״̬
    datalist->replace(index,sTmp);

    for(i = 0; i < 7;i++)
    {
        datalist->replace(index+1+i*4,WeekDay[i].sBorderColor);        //������ɫ
        datalist->replace(index+2+i*4,WeekDay[i].sFrontColor);
        datalist->replace(index+3+i*4,WeekDay[i].sBackColor);

        sTmp=QString::number(WeekDay[i].nPattern);         //�Ƿ���˸
        datalist->replace(index+4+i*4,sTmp);
    }
}

void QWeekDisplayGenDlg::DoubleClickInit(QGraphicsItem *pItem)
{
    QStringList datalist;
    QString sTmp;
    int i = 0;
    int nTemp = 0;
    int index = 190;
    QColor mColor;
    DrawItemToScene GroupFunction;

    if(pItem)
    {
        InitFlag = false;

        GroupFunction.CopyItem(&pOldItem,pItem);
        pScene->addItem(pOldItem);
        pBaseItem = new QGroupItem(pOldItem);
        pBaseItem->SetWidth(100);
        pBaseItem->SetHeigth(100);

        datalist = pItem->data(GROUP_DATALIST_KEY).toStringList();
        ui->lineEdit->setText(datalist.at(19));


        for(i = 0; i < 7;i++)
        {
            WeekDay[i].sBorderColor = datalist.at(index+1+i*4);
            WeekDay[i].sFrontColor = datalist.at(index+2+i*4);
            WeekDay[i].sBackColor = datalist.at(index+3+i*4);

            WeekDay[i].nPattern = datalist.at(index+4+i*4).toInt();
        }


        sTmp = datalist.at(index);
        nTemp = sTmp.toInt();
        mColor = pwnd->StringTOColor(WeekDay[nTemp].sBorderColor);
        setFrameColor(mColor);       //���ñ߿�ɫ



        mColor = pwnd->StringTOColor(WeekDay[nTemp].sFrontColor);
        setFGColor(mColor);       //ǰ��ɫ
        mColor = pwnd->StringTOColor(WeekDay[nTemp].sBackColor);
        setBGColor(mColor);       //����ɫ

        ui->m_patterncmb->setCurrentIndex(WeekDay[nTemp].nPattern);


        ui->m_statespin->setValue(sTmp.toInt());
        InitFlag = true;
    }
}

void QWeekDisplayGenDlg::on_LoadShape_clicked()//��������
{
    LoadShape *pShapeDlg = new LoadShape(this);
    if(pShapeDlg->exec() == QDialog::Accepted)
    {
        DrawItemToScene GroupFunction;
        QPointF oldpos = pOldItem->sceneBoundingRect().topLeft();

        GroupFunction.CopyItem(&pOldItem,pShapeDlg->pCopyItem);
        pScene->clear();
        pScene->addItem(pOldItem);
        pBaseItem = new QGroupItem(pOldItem);

        setFrameColor(ui->Frame_Color->palette().background().color());
        setFGColor(ui->FG_Color->palette().background().color());
        setBGColor(ui->BG_Color->palette().background().color());
         on_m_patterncmb_currentIndexChanged(ui->m_patterncmb->currentIndex());
        emit txtChange();

        QPointF newpos = pOldItem->boundingRect().topLeft();
        pOldItem->setPos(oldpos-newpos);
    }
    pShapeDlg->deleteLater();
    pShapeDlg = NULL;
}

void QWeekDisplayGenDlg::on_Frame_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->Frame_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setFrameColor(const QColor &)));

}
void QWeekDisplayGenDlg::setFrameColor(const QColor & mColor)       //���ñ߿�ɫ
{
    int nState = ui->m_statespin->value();
    QString nColor = pwnd->ColorTOString(mColor);
    ui->Frame_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    WeekDay[nState].sBorderColor = nColor;
    pBaseItem->SetPropertyValue("mFramRect.BackColor",QVariant(nColor));      //������������
}

void QWeekDisplayGenDlg::on_FG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->FG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setFGColor(const QColor &)));
}
void QWeekDisplayGenDlg::setFGColor(const QColor & mColor)       //ǰ��ɫ
{
    int nState = ui->m_statespin->value();
    QString nColor = pwnd->ColorTOString(mColor);
    ui->FG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    WeekDay[nState].sFrontColor = nColor;
    pBaseItem->SetPropertyValue("mBackRect.FrontColor",QVariant(nColor));      //������������
}

void QWeekDisplayGenDlg::on_BG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(19, true,0);
    pwnd->OnAddColorDlg(ui->BG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBGColor(const QColor &)));

}
void QWeekDisplayGenDlg::setBGColor(const QColor & mColor)       //����ɫ
{
    int nState = ui->m_statespin->value();
    QString nColor = pwnd->ColorTOString(mColor);
    ui->BG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    WeekDay[nState].sBackColor = nColor;
    pBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(nColor));      //������������
}
