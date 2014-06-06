#include "SKDrawTool.h"
#include "ui_SKDrawTool.h"
#include <QMessageBox>
#include "color.h"
#include "Frame/DrawDlg/SaveUserDefineLib.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

SKDrawTool::SKDrawTool(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::SKDrawTool)
{
    ui->setupUi(this);

    ui->MainView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->MainView->setDragMode(QGraphicsView::RubberBandDrag);//�ѵ�ѡ�ı���϶�ģʽRubberBandDrag
    QRect rc = ui->MainView->geometry();
    ui->MainView->setSceneRect(0,0,rc.width()-3,rc.height()-3);
    pScene = new SamDrawScene(this);
    pScene->setSceneRect(0,0,rc.width()-3,rc.height()-3);
    ui->MainView->setScene(pScene);
    ui->MainView->setMouseTracking(true);
    connect(pScene,SIGNAL(SingleClickItem()),this,SLOT(onSelectSingleItem()));

    pToolbar = new QToolBar(this);
    pToolbar->addAction(ui->action_DrawLine);
    pToolbar->addAction(ui->action_DrawFoldLine);
    pToolbar->addAction(ui->action_DrawCircleLine);
    pToolbar->addAction(ui->action_DrawFreeLine);
    pToolbar->addAction(ui->action_DrawRect);
    pToolbar->addAction(ui->action_DrawRoundRect);
    pToolbar->addAction(ui->action_Circle);
    pToolbar->addAction(ui->action_PoloyRect);
    pToolbar->addAction(ui->action_Arc);
    pToolbar->addAction(ui->action_DrawText);
    pToolbar->addSeparator();
    pToolbar->addAction(ui->action_Group);
    pToolbar->addAction(ui->action_Disgroup);
    pToolbar->addSeparator();

    pToolbar->addAction(ui->action_movetoplest);
    pToolbar->addAction(ui->action_movedownlest);
    pToolbar->addAction(ui->action_movefore);
    pToolbar->addAction(ui->action_moveback);
    pToolbar->addSeparator();

    pToolbar->addAction(ui->action_LeftAlign);
    pToolbar->addAction(ui->action_RightAlign);
    pToolbar->addAction(ui->action_VCenter);
    pToolbar->addAction(ui->action_TopAlign);

    pToolbar->addAction(ui->action_ButtomAlign);
    pToolbar->addAction(ui->action_HCenter);
    pToolbar->addAction(ui->action_SameWidth);
    pToolbar->addAction(ui->action_SameHeight);
    pToolbar->addAction(ui->action_SameWidthHeight);

    pToolbar->addSeparator();
    pToolbar->addAction(ui->action_HMirror);
    pToolbar->addAction(ui->action_VMirror);
    pToolbar->addSeparator();
    pToolbar->addAction(ui->action_DeleteItem);


    QString str = "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.118644 rgba(200, 200, 200, 255), stop:0.80226 rgba(150, 150, 150, 255));";
    pToolbar->setStyleSheet(str);
    pToolbar->setIconSize(QSize(16,16));

    loadTableWidget();

    QGraphicsItem *pItem = NULL;
    DrawItemToScene FunClass;
    FunClass.CopyItem(&pItem,pwnd->SaveItemToLibList.at(0));
    pScene->addItem(pItem);

    QPointF pos = pItem->boundingRect().topLeft();
    pItem->setPos(250-pos.x(),200-pos.y());

    pItem->setFlag(QGraphicsItem::ItemIsSelectable, true); //�������ͼ�ο�ѡ
    pItem->setFlag(QGraphicsItem::ItemIsMovable, true);

    nSelectClickFlag = false;
    sWidgtContent = "";
}

SKDrawTool::~SKDrawTool()
{
    if(pToolbar)
        delete pToolbar;
    if(pScene)
    {
       delete pScene;
       pScene = NULL;
   }
    delete ui;
}

void SKDrawTool::loadTableWidget()
{
    ui->m_table->setCellWidget(0,0,ui->BackColor);  //����ɫ
    ui->m_table->setCellWidget(1,0,ui->m_pattern);  //��ʽ
    ui->m_table->setCellWidget(2,0,ui->FrontColor); //ǰ��ɫ
    ui->m_table->setCellWidget(3,0,ui->m_linewidth);//�߿��
    ui->m_table->setCellWidget(4,0,ui->LineColor);  //����ɫ
    ui->m_table->setCellWidget(5,0,ui->m_linestyle);//����ʽ
    ui->m_table->setCellWidget(6,0,ui->m_alpha);    //͸����
    ui->m_table->setItem(7,0,new QTableWidgetItem); //���

    pwnd->OnAddPattern(ui->m_pattern);//������ʽ
    ui->BackColor->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
    ui->FrontColor->setStyleSheet(QString("background:%1").arg(QColor(255,255,255).name()));
    ui->LineColor->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
}

void SKDrawTool::on_action_Group_triggered()
{
    pScene->GroupItem();
}

void SKDrawTool::on_action_Disgroup_triggered()
{
    pScene->DisGroupItem();
}

void SKDrawTool::on_BackColor_clicked() //����ɫ
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->BackColor,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBackColor(const QColor &)));
}

void SKDrawTool::setBackColor(const QColor & currentColor)//����ɫ
{
    ui->BackColor->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    setItemProperty(4);
}

void SKDrawTool::on_FrontColor_clicked()//ǰ��ɫ
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->FrontColor,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setFrontColor(const QColor &)));
}

void SKDrawTool::setFrontColor(const QColor &currentColor)//ǰ��ɫ
{
    ui->FrontColor->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    setItemProperty(4);
}

void SKDrawTool::on_LineColor_clicked() //������ɫ
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->LineColor,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setLineColor(const QColor &)));
}

void SKDrawTool::setLineColor(const QColor &currentColor)//������ɫ
{
    ui->LineColor->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    setItemProperty(3);
}

void SKDrawTool::on_m_pattern_currentIndexChanged(int index)//��ʽ
{
    setItemProperty(4);
}

void SKDrawTool::on_m_linewidth_currentIndexChanged(int index)//�߿�
{
    setItemProperty(2);
}

void SKDrawTool::on_m_linestyle_currentIndexChanged(int index)//����ʽ
{
    setItemProperty(1);
}

void SKDrawTool::on_m_alpha_valueChanged(int alpha)//͸����
{
    setItemProperty(4);
}

void SKDrawTool::on_m_table_itemChanged(QTableWidgetItem* item)//table�ı�
{
    int nRow = ui->m_table->row(item);
    if(nRow != 7 && nRow != 8)
        return;

    sWidgtContent = item->text();
    switch(nRow)
    {
    case 7: //���ò��
        setItemProperty(5);
        break;
    case 8: //�����ı�����
        setItemProperty(6);
        break;
    default:break;
    }
}

/*************************************************************
  *�������ƣ�setItemProperty(int nMark)
  *�������ܣ�����item����
  *�������壺
  *nMark = 1����������ʽ
  *nMark = 2�������߿��
  *nMark = 3����������ɫ
  *nMark = 4�����ñ���ɫ��ǰ��ɫ����ʽ,͸����
  *nMark = 5�����ò��
  *nMark = 6�������ı�����

  *edit by zqh
  *2011-03-25
 ************************************************************/
void SKDrawTool::setItemProperty(int nMark)
{
    if(nSelectClickFlag)
        return;
    QList<QGraphicsItem *> sListItem;
    QGraphicsItem *pItem = NULL;
    QColor mColor = ui->LineColor->palette().background().color(); //���������ɫ
    int nLstly = ui->m_linestyle->currentIndex(); //����ʽ
    int nLWidth = ui->m_linewidth->currentIndex();//�߿��
    QColor mBkColor = ui->BackColor->palette().background().color(); //��ñ���ɫ
    QColor mFrColor = ui->FrontColor->palette().background().color(); //���ǰ��ɫ
    int nPattern = ui->m_pattern->currentIndex();//��ʽ
    int nAlapha = ui->m_alpha->value();

    QRectItem *pRect = NULL;
    QElipseItem *pCircle = NULL;
    QPolygonItem *pPolyRect = NULL;
    QRoundedRect *pRoundedRect = NULL;
    QArcItem *pArc = NULL;
    QLineItem *pLine = NULL;
    QFoldLineItem *pFoldLine = NULL;
    QSimpleTextItem *pTxt = NULL;
    QFreeLineItem *pFreeLine = NULL;
    QLineCircleItem *pCirleLine = NULL;


    sListItem = pScene->selectedItems();
    if(sListItem.size() != 1) //����ѡ��һ��ͼ��
        return;

    pItem = sListItem.at(0);

    if(nMark == 5)//���ò��
    {
        pItem->setZValue(sWidgtContent.toInt());
        return;
    }


    switch (pItem->type())
    {
    case SAM_DRAW_OBJECT_RECT:
        pRect = qgraphicsitem_cast<QRectItem*>(pItem);
        if(nMark == 1)
            pRect->SetLineType(nLstly);   //��������ʽ
        else if(nMark == 2)
            pRect->SetLineWidth(nLWidth);   //�����߿��
        else if(nMark == 3)
            pRect->SetLineColor(mColor);   //��������ɫ
        else if(nMark == 4)
        {
            pRect->SetBackColor(mBkColor);   //���ñ���ɫ
            pRect->SetFrontColor(mFrColor);  //����ǰ��ɫ
            pRect->SetPattern(nPattern);     //������ʽ
            pRect->SetAlpha(nAlapha);        //����͸����
        }
        break;
    case SAM_DRAW_OBJECT_ELIPSE:
        pCircle = qgraphicsitem_cast<QElipseItem*>(pItem);
        if(nMark == 1)
            pCircle->SetLineType(nLstly);   //��������ʽ
        else if(nMark == 2)
            pCircle->SetLineWidth(nLWidth);   //�����߿��
        else if(nMark == 3)
            pCircle->SetLineColor(mColor);   //��������ɫ
        else if(nMark == 4)
        {
            pCircle->SetBackColor(mBkColor);   //���ñ���ɫ
            pCircle->SetFrontColor(mFrColor);  //����ǰ��ɫ
            pCircle->SetPattern(nPattern);     //������ʽ
            pCircle->SetAlpha(nAlapha);        //����͸����
        }
        break;
    case SAM_DRAW_OBJECT_POLYGON:
        pPolyRect = qgraphicsitem_cast<QPolygonItem*>(pItem);
        if(nMark == 1)
            pPolyRect->setLineType(nLstly);   //��������ʽ
        else if(nMark == 2)
            pPolyRect->setLineWidth(nLWidth);   //�����߿��
        else if(nMark == 3)
            pPolyRect->setLineColor(mColor);   //��������ɫ
        else if(nMark == 4)
        {
            pPolyRect->setBackColor(mBkColor);   //���ñ���ɫ
            pPolyRect->setFrontColor(mFrColor);  //����ǰ��ɫ
            pPolyRect->setPattern(nPattern);     //������ʽ
            pPolyRect->setAlpha(nAlapha);//����͸����
        }
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
        pRoundedRect = qgraphicsitem_cast<QRoundedRect*>(pItem);
        if(nMark == 1)
            pRoundedRect->SetLineType(nLstly);   //��������ʽ
        else if(nMark == 2)
            pRoundedRect->SetLineWidth(nLWidth);   //�����߿��
        else if(nMark == 3)
            pRoundedRect->SetLineColor(mColor);   //��������ɫ
        else if(nMark == 4)
        {
            pRoundedRect->SetBackColor(mBkColor);   //���ñ���ɫ
            pRoundedRect->SetFrontColor(mFrColor);  //����ǰ��ɫ
            pRoundedRect->SetPattern(nPattern);     //������ʽ
            pRoundedRect->SetAlpha(nAlapha);//����͸����
        }
        break;
    case SAM_DRAW_OBJECT_ARC:
        pArc = qgraphicsitem_cast<QArcItem*>(pItem);
        if(nMark == 1)
            pArc->SetLineType(nLstly);   //��������ʽ
        else if(nMark == 2)
            pArc->SetLineWidth(nLWidth);   //�����߿��
        else if(nMark == 3)
            pArc->SetLineColor(mColor);   //��������ɫ
        else if(nMark == 4)
        {
            pArc->SetBackColor(mBkColor);  //���ñ���ɫ
            pArc->SetFrontColor(mFrColor);  //����ǰ��ɫ
            pArc->SetPattern(nPattern);     //������ʽ
            pArc->SetAlpha(nAlapha);//����͸����
        }
        break;
    case SAM_DRAW_OBJECT_LINE :
        pLine = qgraphicsitem_cast<QLineItem*>(pItem);
        if(nMark == 1)
            pLine->setLineType(nLstly);   //��������ʽ
        else if(nMark == 2)
            pLine->setLineWidth(nLWidth);   //�����߿��
        else if(nMark == 3)
            pLine->setLineColor(mColor);   //��������ɫ
        else if(nMark == 4)
            pLine->setAlpha(nAlapha);//����͸����
        break;
    case SAM_DRAW_OBJECT_FOLDLINE:
        pFoldLine = qgraphicsitem_cast<QFoldLineItem*>(pItem);
        if(nMark == 1)
            pFoldLine->setLineType(nLstly);   //��������ʽ
        else if(nMark == 2)
            pFoldLine->setLineWidth(nLWidth);   //�����߿��
        else if(nMark == 3)
            pFoldLine->setLineColor(mColor);   //��������ɫ
        else if(nMark == 4)
            pFoldLine->setAlpha(nAlapha);//����͸����
        break;
    case SAM_DRAW_OBJECT_TEXT:
        pTxt = qgraphicsitem_cast<QSimpleTextItem*>(pItem);
        if(nMark == 1)//����ʽ
        {
            if(nLstly == 0)
                pTxt->SetRectOutLine(false);
            else
                pTxt->SetRectOutLine(true);
        }
        else if(nMark == 4)
        {
            pTxt->SetRectBackColor(mBkColor);  //���ñ���ɫ
            pTxt->SetRectFrontColor(mFrColor);  //����ǰ��ɫ
            pTxt->SetPattern(nPattern);     //������ʽ
            pTxt->SetAlpha(nAlapha);//����͸����
        }
        else if(nMark == 6)//�����ı�����
        {
            pTxt->SetText(sWidgtContent);
        }
        break;
    case SAM_DRAW_OBJECT_FREELINE: //����ֱ��
        pFreeLine = qgraphicsitem_cast<QFreeLineItem*>(pItem);
        if(nMark == 1)
            pFreeLine->setLineType(nLstly);   //��������ʽ
        else if(nMark == 2)
            pFreeLine->setLineWidth(nLWidth);   //�����߿��
        else if(nMark == 3)
            pFreeLine->setLineColor(mColor);   //��������ɫ
        else if(nMark == 4)
            pFreeLine->setAlpha(nAlapha);//����͸����
        break;
   case SAM_DRAW_OBJECT_LINECIRCLE: //����/Բ��
       pCirleLine = qgraphicsitem_cast<QLineCircleItem*>(pItem);
       if(nMark == 1)
           pCirleLine->setLineType(nLstly);   //��������ʽ
       else if(nMark == 2)
           pCirleLine->setLineWidth(nLWidth);   //�����߿��
       else if(nMark == 3)
           pCirleLine->setLineColor(mColor);   //��������ɫ
       else if(nMark == 4)
           pCirleLine->setAlpha(nAlapha);//����͸����
       break;

   default:     break;
   }
}

void SKDrawTool::onSelectSingleItem() //���������е�item
{
    nSelectClickFlag = true; //����ͼ�α�ʶ
    QList<QGraphicsItem *> sListItem;
    QGraphicsItem *pItem = NULL;

    int nZvalue = 0;
    QString sColor;
    QString sText = "";

    QRectItem *pRect = NULL;
    QElipseItem *pCircle = NULL;
    QLineItem *pLine = NULL;
    QFoldLineItem *pFoldLine = NULL;
    QPolygonItem *pPolyRect = NULL;
    QRoundedRect *pRoundedRect = NULL;
    QArcItem *pArc = NULL;
    QSimpleTextItem *pTxt = NULL;
    QFreeLineItem *pFreeLine = NULL;
    QLineCircleItem *pCirleLine = NULL;

    sListItem = pScene->selectedItems();
    if(sListItem.size() != 1) //����ѡ��һ��ͼ��
        return;

    pItem = sListItem.at(0);

    nZvalue = pItem->zValue();

    switch (pItem->type())
    {
    case SAM_DRAW_OBJECT_RECT:
        pRect = qgraphicsitem_cast<QRectItem*>(pItem);
        sColor = QString("background:%1").arg(pRect->GetBackColor().name());
        ui->BackColor->setStyleSheet(sColor);   //���ñ���ɫ

        ui->m_linestyle->setCurrentIndex(pRect->GetLineType());  //������ʽ
        ui->m_linewidth->setCurrentIndex(pRect->GetLineWidth());//�������

        sColor = QString("background:%1").arg(pRect->GetLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //������ɫ

        sColor = QString("background:%1").arg(pRect->GetFrontColor().name());
        ui->FrontColor->setStyleSheet(sColor);   //ǰ��ɫ

        ui->m_pattern->setCurrentIndex(pRect->GetPattern());    //��ʽ
        ui->m_alpha->setValue(pRect->GetAlpha()); //���͸����

        break;
    case SAM_DRAW_OBJECT_ELIPSE:
        pCircle = qgraphicsitem_cast<QElipseItem*>(pItem);

        sColor = QString("background:%1").arg(pCircle->GetBackColor().name());
        ui->BackColor->setStyleSheet(sColor);   //���ñ���ɫ

        ui->m_linestyle->setCurrentIndex(pCircle->GetLineType());  //������ʽ
        ui->m_linewidth->setCurrentIndex(pCircle->GetLineWidth());//�������

        sColor = QString("background:%1").arg(pCircle->GetLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //������ɫ

        sColor = QString("background:%1").arg(pCircle->GetFrontColor().name());
        ui->FrontColor->setStyleSheet(sColor);   //ǰ��ɫ

        ui->m_pattern->setCurrentIndex(pCircle->GetPattern());    //��ʽ
        ui->m_alpha->setValue(pCircle->GetAlpha()); //���͸����
        break;
    case SAM_DRAW_OBJECT_POLYGON:
        pPolyRect = qgraphicsitem_cast<QPolygonItem*>(pItem);
        sColor = QString("background:%1").arg(pPolyRect->getBackColor().name());
        ui->BackColor->setStyleSheet(sColor);   //���ñ���ɫ

        ui->m_linestyle->setCurrentIndex(pPolyRect->getLineType());  //������ʽ
        ui->m_linewidth->setCurrentIndex(pPolyRect->getLineWidth());//�������

        sColor = QString("background:%1").arg(pPolyRect->getLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //������ɫ

        sColor = QString("background:%1").arg(pPolyRect->getFrontColor().name());
        ui->FrontColor->setStyleSheet(sColor);   //ǰ��ɫ

        ui->m_pattern->setCurrentIndex(pPolyRect->getPattern());    //��ʽ
        ui->m_alpha->setValue(pPolyRect->getAlpha()); //���͸����
        break;
    case SAM_DRAW_OBJECT_LINE :
        pLine = qgraphicsitem_cast<QLineItem*>(pItem);
        ui->m_linestyle->setCurrentIndex(pLine->getLineType());  //������ʽ
        ui->m_linewidth->setCurrentIndex(pLine->getLineWidth());//�������

        sColor = QString("background:%1").arg(pLine->getLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //������ɫ
        ui->m_alpha->setValue(pLine->getAlpha()); //���͸����
        break;
    case SAM_DRAW_OBJECT_FOLDLINE:
        pFoldLine = qgraphicsitem_cast<QFoldLineItem*>(pItem);

        ui->m_linestyle->setCurrentIndex(pFoldLine->getLineType());  //������ʽ
        ui->m_linewidth->setCurrentIndex(pFoldLine->getLineWidth());//�������

        sColor = QString("background:%1").arg(pFoldLine->getLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //������ɫ
        ui->m_alpha->setValue(pFoldLine->getAlpha()); //���͸����
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
        pRoundedRect = qgraphicsitem_cast<QRoundedRect*>(pItem);
        sColor = QString("background:%1").arg(pRoundedRect->GetBackColor().name());
        ui->BackColor->setStyleSheet(sColor);   //���ñ���ɫ

        ui->m_linestyle->setCurrentIndex(pRoundedRect->GetLineType());  //������ʽ
        ui->m_linewidth->setCurrentIndex(pRoundedRect->GetLineWidth());//�������

        sColor = QString("background:%1").arg(pRoundedRect->GetLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //������ɫ

        sColor = QString("background:%1").arg(pRoundedRect->GetFrontColor().name());
        ui->FrontColor->setStyleSheet(sColor);   //ǰ��ɫ

        ui->m_pattern->setCurrentIndex(pRoundedRect->GetPattern());    //��ʽ
        ui->m_alpha->setValue(pRoundedRect->GetAlpha()); //���͸����
        break;
    case SAM_DRAW_OBJECT_ARC:
        pArc = qgraphicsitem_cast<QArcItem*>(pItem);
        sColor = QString("background:%1").arg(pArc->GetBackColor().name());
        ui->BackColor->setStyleSheet(sColor);   //���ñ���ɫ

        ui->m_linestyle->setCurrentIndex(pArc->GetLineType());  //������ʽ
        ui->m_linewidth->setCurrentIndex(pArc->GetLineWidth());//�������

        sColor = QString("background:%1").arg(pArc->GetLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //������ɫ

        sColor = QString("background:%1").arg(pArc->GetFrontColor().name());
        ui->FrontColor->setStyleSheet(sColor);   //ǰ��ɫ

        ui->m_pattern->setCurrentIndex(pArc->GetPattern());    //��ʽ
        ui->m_alpha->setValue(pArc->GetAlpha()); //���͸����
        break;
    case SAM_DRAW_OBJECT_TEXT:
        pTxt = qgraphicsitem_cast<QSimpleTextItem*>(pItem);
        sColor = QString("background:%1").arg(pTxt->GetRectBackColor().name());
        ui->BackColor->setStyleSheet(sColor);   //���ñ���ɫ

        sColor = QString("background:%1").arg(pTxt->GetRectFrontColor().name());
        ui->FrontColor->setStyleSheet(sColor);   //ǰ��ɫ
        sText = pTxt->GetText();
        ui->m_pattern->setCurrentIndex(pTxt->GetPattern());    //��ʽ
        ui->m_alpha->setValue(pTxt->GetAlpha()); //���͸����
        if(pTxt->GetRectOutLine()) //�Ƿ��б��߿�
            ui->m_linestyle->setCurrentIndex(1);
        else
            ui->m_linestyle->setCurrentIndex(0);
        break;
    case SAM_DRAW_OBJECT_FREELINE: //����ֱ��
        pFreeLine = qgraphicsitem_cast<QFreeLineItem*>(pItem);
        ui->m_linestyle->setCurrentIndex(pFreeLine->getLineType());  //������ʽ
        ui->m_linewidth->setCurrentIndex(pFreeLine->getLineWidth());//�������

        sColor = QString("background:%1").arg(pFreeLine->getLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //������ɫ
        ui->m_alpha->setValue(pFreeLine->getAlpha()); //���͸����
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE: //����/Բ��
        pCirleLine = qgraphicsitem_cast<QLineCircleItem*>(pItem);
        ui->m_linestyle->setCurrentIndex(pCirleLine->getLineType());  //������ʽ
        ui->m_linewidth->setCurrentIndex(pCirleLine->getLineWidth());//�������

        sColor = QString("background:%1").arg(pCirleLine->getLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //������ɫ
        ui->m_alpha->setValue(pCirleLine->getAlpha()); //���͸����
        break;
    default:     break;
    }
    ui->m_table->setItem(7,0,new QTableWidgetItem(QString("%1").arg(nZvalue)));//���
    ui->m_table->setItem(8,0,new QTableWidgetItem(sText));//�ı�����
    nSelectClickFlag = false; //����ͼ�α�ʶ
}

void SKDrawTool::on_action_LeftAlign_triggered() //�����
{
    pScene->OnSetLeftAlign();
}

void SKDrawTool::on_action_RightAlign_triggered()//�Ҷ���
{
    pScene->OnSetRightAlign();
}

void SKDrawTool::on_action_VCenter_triggered()//��ֱ����
{
    pScene->OnSetVCenterAlign();
}

void SKDrawTool::on_action_TopAlign_triggered()//�϶���
{
    pScene->OnSetTopAlign();
}

void SKDrawTool::on_action_ButtomAlign_triggered()//�¶���
{
    pScene->OnSetButtomAlign();
}

void SKDrawTool::on_action_HCenter_triggered()//ˮƽ����
{
    pScene->OnSetHCenterAlign();
}

void SKDrawTool::on_action_SameWidth_triggered()//�ȿ��
{
    pScene->setWidthSame();
}

void SKDrawTool::on_action_SameHeight_triggered()//�ȸ߶�
{
    pScene->setHeightSame();
}

void SKDrawTool::on_action_SameWidthHeight_triggered()//�ȿ�ȸ�
{
    pScene->setWidthHeightSame();
}

void SKDrawTool::on_action_VMirror_triggered()//��ֱ����
{
    pScene->SetBaseItemMirror(2);
}

void SKDrawTool::on_action_HMirror_triggered()//ˮƽ����
{
    pScene->SetBaseItemMirror(1);
}

void SKDrawTool::on_action_DrawLine_triggered()//����ֱ��
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_LINE;
}

void SKDrawTool::on_action_DrawFoldLine_triggered()//��������
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_FOLDLINE;
}

void SKDrawTool::on_action_DrawCircleLine_triggered()//��������Բ��
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_LINE_CIRCLE;
}

void SKDrawTool::on_action_DrawFreeLine_triggered()//��������
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_FREELINE;
}

void SKDrawTool::on_action_DrawRect_triggered()//����
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_RECT;
}

void SKDrawTool::on_action_DrawRoundRect_triggered()//Բ�Ǿ���
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_ROUNDED_RECT;
}

void SKDrawTool::on_action_Circle_triggered()//Բ/��Բ
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_ELLIPSE;
}

void SKDrawTool::on_action_PoloyRect_triggered()//�����
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_POLYGON;
}

void SKDrawTool::on_action_Arc_triggered()//����
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_ARC;
}

void SKDrawTool::on_action_DeleteItem_triggered()//ɾ��ͼ��
{
    QList <QGraphicsItem *> sList;
    sList = pScene->selectedItems();
    if (sList.isEmpty())
        return;

    foreach(QGraphicsItem *pItem,sList)
        pScene->removeItem(pItem);
}

void SKDrawTool::on_m_SaveItemBtn_clicked()//����
{
    pwnd->SaveItemToLibList.clear();
    QList<QGraphicsItem *> item_list=pScene->selectedItems();
    QMessageBox box(this);
    if(item_list.size() < 1)
    {
        box.setText(tr("ûͼ����Ҫ����!"));
        box.exec();
        return;
    }
    else if(item_list.size() > 1)
    {
        box.setText(tr("һ��ֻ�ܱ���һ��ͼ��!"));
        box.exec();
        return;
    }

    QGraphicsItem *pItem = item_list.at(0);
    pwnd->SaveItemToLibList.append(pItem);

    SaveUserDefineLib *pDlg =  new SaveUserDefineLib(this);
    if(pDlg->exec() == QDialog::close())
    {
        QDialog::close();
    }
    pDlg->deleteLater();
    pDlg = NULL;
}

void SKDrawTool::on_m_Cancel_clicked()//ȡ��
{
    pwnd->SaveItemToLibList.clear();
    QDialog::close();
}

void SKDrawTool::on_action_DrawText_triggered()//�����ı�
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_SAMPLE_TEXT;
}

void SKDrawTool::on_action_movetoplest_triggered()//�Ƶ����ϲ�
{
    pScene->OnOderTop();
}

void SKDrawTool::on_action_movedownlest_triggered()//�Ƶ���Ͳ�
{
    pScene->OnOderBotton();
}

void SKDrawTool::on_action_movefore_triggered()//����һ��
{
    pScene->OnOderUp();
}

void SKDrawTool::on_action_moveback_triggered()//����һ��
{
    pScene->OnOderDown();
}
