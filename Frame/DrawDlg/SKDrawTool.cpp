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
    ui->MainView->setDragMode(QGraphicsView::RubberBandDrag);//把单选改变给拖动模式RubberBandDrag
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

    pItem->setFlag(QGraphicsItem::ItemIsSelectable, true); //设置组合图形可选
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
    ui->m_table->setCellWidget(0,0,ui->BackColor);  //背景色
    ui->m_table->setCellWidget(1,0,ui->m_pattern);  //样式
    ui->m_table->setCellWidget(2,0,ui->FrontColor); //前景色
    ui->m_table->setCellWidget(3,0,ui->m_linewidth);//线宽度
    ui->m_table->setCellWidget(4,0,ui->LineColor);  //线颜色
    ui->m_table->setCellWidget(5,0,ui->m_linestyle);//线样式
    ui->m_table->setCellWidget(6,0,ui->m_alpha);    //透明度
    ui->m_table->setItem(7,0,new QTableWidgetItem); //层次

    pwnd->OnAddPattern(ui->m_pattern);//加载样式
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

void SKDrawTool::on_BackColor_clicked() //背景色
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->BackColor,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBackColor(const QColor &)));
}

void SKDrawTool::setBackColor(const QColor & currentColor)//背景色
{
    ui->BackColor->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    setItemProperty(4);
}

void SKDrawTool::on_FrontColor_clicked()//前景色
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->FrontColor,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setFrontColor(const QColor &)));
}

void SKDrawTool::setFrontColor(const QColor &currentColor)//前景色
{
    ui->FrontColor->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    setItemProperty(4);
}

void SKDrawTool::on_LineColor_clicked() //线条颜色
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->LineColor,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setLineColor(const QColor &)));
}

void SKDrawTool::setLineColor(const QColor &currentColor)//线条颜色
{
    ui->LineColor->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    setItemProperty(3);
}

void SKDrawTool::on_m_pattern_currentIndexChanged(int index)//样式
{
    setItemProperty(4);
}

void SKDrawTool::on_m_linewidth_currentIndexChanged(int index)//线宽
{
    setItemProperty(2);
}

void SKDrawTool::on_m_linestyle_currentIndexChanged(int index)//线样式
{
    setItemProperty(1);
}

void SKDrawTool::on_m_alpha_valueChanged(int alpha)//透明度
{
    setItemProperty(4);
}

void SKDrawTool::on_m_table_itemChanged(QTableWidgetItem* item)//table改变
{
    int nRow = ui->m_table->row(item);
    if(nRow != 7 && nRow != 8)
        return;

    sWidgtContent = item->text();
    switch(nRow)
    {
    case 7: //设置层次
        setItemProperty(5);
        break;
    case 8: //设置文本内容
        setItemProperty(6);
        break;
    default:break;
    }
}

/*************************************************************
  *函数名称：setItemProperty(int nMark)
  *函数功能：设置item属性
  *参数含义：
  *nMark = 1：设置线样式
  *nMark = 2：设置线宽度
  *nMark = 3：设置线颜色
  *nMark = 4：设置背景色、前景色、样式,透明度
  *nMark = 5：设置层次
  *nMark = 6：设置文本内容

  *edit by zqh
  *2011-03-25
 ************************************************************/
void SKDrawTool::setItemProperty(int nMark)
{
    if(nSelectClickFlag)
        return;
    QList<QGraphicsItem *> sListItem;
    QGraphicsItem *pItem = NULL;
    QColor mColor = ui->LineColor->palette().background().color(); //获得线条颜色
    int nLstly = ui->m_linestyle->currentIndex(); //线样式
    int nLWidth = ui->m_linewidth->currentIndex();//线宽度
    QColor mBkColor = ui->BackColor->palette().background().color(); //获得背景色
    QColor mFrColor = ui->FrontColor->palette().background().color(); //获得前景色
    int nPattern = ui->m_pattern->currentIndex();//样式
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
    if(sListItem.size() != 1) //不是选择一个图形
        return;

    pItem = sListItem.at(0);

    if(nMark == 5)//设置层次
    {
        pItem->setZValue(sWidgtContent.toInt());
        return;
    }


    switch (pItem->type())
    {
    case SAM_DRAW_OBJECT_RECT:
        pRect = qgraphicsitem_cast<QRectItem*>(pItem);
        if(nMark == 1)
            pRect->SetLineType(nLstly);   //设置线样式
        else if(nMark == 2)
            pRect->SetLineWidth(nLWidth);   //设置线宽度
        else if(nMark == 3)
            pRect->SetLineColor(mColor);   //设置线条色
        else if(nMark == 4)
        {
            pRect->SetBackColor(mBkColor);   //设置背景色
            pRect->SetFrontColor(mFrColor);  //设置前景色
            pRect->SetPattern(nPattern);     //设置样式
            pRect->SetAlpha(nAlapha);        //设置透明度
        }
        break;
    case SAM_DRAW_OBJECT_ELIPSE:
        pCircle = qgraphicsitem_cast<QElipseItem*>(pItem);
        if(nMark == 1)
            pCircle->SetLineType(nLstly);   //设置线样式
        else if(nMark == 2)
            pCircle->SetLineWidth(nLWidth);   //设置线宽度
        else if(nMark == 3)
            pCircle->SetLineColor(mColor);   //设置线条色
        else if(nMark == 4)
        {
            pCircle->SetBackColor(mBkColor);   //设置背景色
            pCircle->SetFrontColor(mFrColor);  //设置前景色
            pCircle->SetPattern(nPattern);     //设置样式
            pCircle->SetAlpha(nAlapha);        //设置透明度
        }
        break;
    case SAM_DRAW_OBJECT_POLYGON:
        pPolyRect = qgraphicsitem_cast<QPolygonItem*>(pItem);
        if(nMark == 1)
            pPolyRect->setLineType(nLstly);   //设置线样式
        else if(nMark == 2)
            pPolyRect->setLineWidth(nLWidth);   //设置线宽度
        else if(nMark == 3)
            pPolyRect->setLineColor(mColor);   //设置线条色
        else if(nMark == 4)
        {
            pPolyRect->setBackColor(mBkColor);   //设置背景色
            pPolyRect->setFrontColor(mFrColor);  //设置前景色
            pPolyRect->setPattern(nPattern);     //设置样式
            pPolyRect->setAlpha(nAlapha);//设置透明度
        }
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
        pRoundedRect = qgraphicsitem_cast<QRoundedRect*>(pItem);
        if(nMark == 1)
            pRoundedRect->SetLineType(nLstly);   //设置线样式
        else if(nMark == 2)
            pRoundedRect->SetLineWidth(nLWidth);   //设置线宽度
        else if(nMark == 3)
            pRoundedRect->SetLineColor(mColor);   //设置线条色
        else if(nMark == 4)
        {
            pRoundedRect->SetBackColor(mBkColor);   //设置背景色
            pRoundedRect->SetFrontColor(mFrColor);  //设置前景色
            pRoundedRect->SetPattern(nPattern);     //设置样式
            pRoundedRect->SetAlpha(nAlapha);//设置透明度
        }
        break;
    case SAM_DRAW_OBJECT_ARC:
        pArc = qgraphicsitem_cast<QArcItem*>(pItem);
        if(nMark == 1)
            pArc->SetLineType(nLstly);   //设置线样式
        else if(nMark == 2)
            pArc->SetLineWidth(nLWidth);   //设置线宽度
        else if(nMark == 3)
            pArc->SetLineColor(mColor);   //设置线条色
        else if(nMark == 4)
        {
            pArc->SetBackColor(mBkColor);  //设置背景色
            pArc->SetFrontColor(mFrColor);  //设置前景色
            pArc->SetPattern(nPattern);     //设置样式
            pArc->SetAlpha(nAlapha);//设置透明度
        }
        break;
    case SAM_DRAW_OBJECT_LINE :
        pLine = qgraphicsitem_cast<QLineItem*>(pItem);
        if(nMark == 1)
            pLine->setLineType(nLstly);   //设置线样式
        else if(nMark == 2)
            pLine->setLineWidth(nLWidth);   //设置线宽度
        else if(nMark == 3)
            pLine->setLineColor(mColor);   //设置线条色
        else if(nMark == 4)
            pLine->setAlpha(nAlapha);//设置透明度
        break;
    case SAM_DRAW_OBJECT_FOLDLINE:
        pFoldLine = qgraphicsitem_cast<QFoldLineItem*>(pItem);
        if(nMark == 1)
            pFoldLine->setLineType(nLstly);   //设置线样式
        else if(nMark == 2)
            pFoldLine->setLineWidth(nLWidth);   //设置线宽度
        else if(nMark == 3)
            pFoldLine->setLineColor(mColor);   //设置线条色
        else if(nMark == 4)
            pFoldLine->setAlpha(nAlapha);//设置透明度
        break;
    case SAM_DRAW_OBJECT_TEXT:
        pTxt = qgraphicsitem_cast<QSimpleTextItem*>(pItem);
        if(nMark == 1)//线样式
        {
            if(nLstly == 0)
                pTxt->SetRectOutLine(false);
            else
                pTxt->SetRectOutLine(true);
        }
        else if(nMark == 4)
        {
            pTxt->SetRectBackColor(mBkColor);  //设置背景色
            pTxt->SetRectFrontColor(mFrColor);  //设置前景色
            pTxt->SetPattern(nPattern);     //设置样式
            pTxt->SetAlpha(nAlapha);//设置透明度
        }
        else if(nMark == 6)//设置文本内容
        {
            pTxt->SetText(sWidgtContent);
        }
        break;
    case SAM_DRAW_OBJECT_FREELINE: //自由直线
        pFreeLine = qgraphicsitem_cast<QFreeLineItem*>(pItem);
        if(nMark == 1)
            pFreeLine->setLineType(nLstly);   //设置线样式
        else if(nMark == 2)
            pFreeLine->setLineWidth(nLWidth);   //设置线宽度
        else if(nMark == 3)
            pFreeLine->setLineColor(mColor);   //设置线条色
        else if(nMark == 4)
            pFreeLine->setAlpha(nAlapha);//设置透明度
        break;
   case SAM_DRAW_OBJECT_LINECIRCLE: //曲线/圆弧
       pCirleLine = qgraphicsitem_cast<QLineCircleItem*>(pItem);
       if(nMark == 1)
           pCirleLine->setLineType(nLstly);   //设置线样式
       else if(nMark == 2)
           pCirleLine->setLineWidth(nLWidth);   //设置线宽度
       else if(nMark == 3)
           pCirleLine->setLineColor(mColor);   //设置线条色
       else if(nMark == 4)
           pCirleLine->setAlpha(nAlapha);//设置透明度
       break;

   default:     break;
   }
}

void SKDrawTool::onSelectSingleItem() //单击场景中的item
{
    nSelectClickFlag = true; //单击图形标识
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
    if(sListItem.size() != 1) //不是选择一个图形
        return;

    pItem = sListItem.at(0);

    nZvalue = pItem->zValue();

    switch (pItem->type())
    {
    case SAM_DRAW_OBJECT_RECT:
        pRect = qgraphicsitem_cast<QRectItem*>(pItem);
        sColor = QString("background:%1").arg(pRect->GetBackColor().name());
        ui->BackColor->setStyleSheet(sColor);   //设置背景色

        ui->m_linestyle->setCurrentIndex(pRect->GetLineType());  //线条样式
        ui->m_linewidth->setCurrentIndex(pRect->GetLineWidth());//线条宽度

        sColor = QString("background:%1").arg(pRect->GetLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //线条颜色

        sColor = QString("background:%1").arg(pRect->GetFrontColor().name());
        ui->FrontColor->setStyleSheet(sColor);   //前景色

        ui->m_pattern->setCurrentIndex(pRect->GetPattern());    //样式
        ui->m_alpha->setValue(pRect->GetAlpha()); //获得透明度

        break;
    case SAM_DRAW_OBJECT_ELIPSE:
        pCircle = qgraphicsitem_cast<QElipseItem*>(pItem);

        sColor = QString("background:%1").arg(pCircle->GetBackColor().name());
        ui->BackColor->setStyleSheet(sColor);   //设置背景色

        ui->m_linestyle->setCurrentIndex(pCircle->GetLineType());  //线条样式
        ui->m_linewidth->setCurrentIndex(pCircle->GetLineWidth());//线条宽度

        sColor = QString("background:%1").arg(pCircle->GetLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //线条颜色

        sColor = QString("background:%1").arg(pCircle->GetFrontColor().name());
        ui->FrontColor->setStyleSheet(sColor);   //前景色

        ui->m_pattern->setCurrentIndex(pCircle->GetPattern());    //样式
        ui->m_alpha->setValue(pCircle->GetAlpha()); //获得透明度
        break;
    case SAM_DRAW_OBJECT_POLYGON:
        pPolyRect = qgraphicsitem_cast<QPolygonItem*>(pItem);
        sColor = QString("background:%1").arg(pPolyRect->getBackColor().name());
        ui->BackColor->setStyleSheet(sColor);   //设置背景色

        ui->m_linestyle->setCurrentIndex(pPolyRect->getLineType());  //线条样式
        ui->m_linewidth->setCurrentIndex(pPolyRect->getLineWidth());//线条宽度

        sColor = QString("background:%1").arg(pPolyRect->getLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //线条颜色

        sColor = QString("background:%1").arg(pPolyRect->getFrontColor().name());
        ui->FrontColor->setStyleSheet(sColor);   //前景色

        ui->m_pattern->setCurrentIndex(pPolyRect->getPattern());    //样式
        ui->m_alpha->setValue(pPolyRect->getAlpha()); //获得透明度
        break;
    case SAM_DRAW_OBJECT_LINE :
        pLine = qgraphicsitem_cast<QLineItem*>(pItem);
        ui->m_linestyle->setCurrentIndex(pLine->getLineType());  //线条样式
        ui->m_linewidth->setCurrentIndex(pLine->getLineWidth());//线条宽度

        sColor = QString("background:%1").arg(pLine->getLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //线条颜色
        ui->m_alpha->setValue(pLine->getAlpha()); //获得透明度
        break;
    case SAM_DRAW_OBJECT_FOLDLINE:
        pFoldLine = qgraphicsitem_cast<QFoldLineItem*>(pItem);

        ui->m_linestyle->setCurrentIndex(pFoldLine->getLineType());  //线条样式
        ui->m_linewidth->setCurrentIndex(pFoldLine->getLineWidth());//线条宽度

        sColor = QString("background:%1").arg(pFoldLine->getLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //线条颜色
        ui->m_alpha->setValue(pFoldLine->getAlpha()); //获得透明度
        break;
    case SAM_DRAW_OBJECT_ROUNDEDRECT:
        pRoundedRect = qgraphicsitem_cast<QRoundedRect*>(pItem);
        sColor = QString("background:%1").arg(pRoundedRect->GetBackColor().name());
        ui->BackColor->setStyleSheet(sColor);   //设置背景色

        ui->m_linestyle->setCurrentIndex(pRoundedRect->GetLineType());  //线条样式
        ui->m_linewidth->setCurrentIndex(pRoundedRect->GetLineWidth());//线条宽度

        sColor = QString("background:%1").arg(pRoundedRect->GetLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //线条颜色

        sColor = QString("background:%1").arg(pRoundedRect->GetFrontColor().name());
        ui->FrontColor->setStyleSheet(sColor);   //前景色

        ui->m_pattern->setCurrentIndex(pRoundedRect->GetPattern());    //样式
        ui->m_alpha->setValue(pRoundedRect->GetAlpha()); //获得透明度
        break;
    case SAM_DRAW_OBJECT_ARC:
        pArc = qgraphicsitem_cast<QArcItem*>(pItem);
        sColor = QString("background:%1").arg(pArc->GetBackColor().name());
        ui->BackColor->setStyleSheet(sColor);   //设置背景色

        ui->m_linestyle->setCurrentIndex(pArc->GetLineType());  //线条样式
        ui->m_linewidth->setCurrentIndex(pArc->GetLineWidth());//线条宽度

        sColor = QString("background:%1").arg(pArc->GetLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //线条颜色

        sColor = QString("background:%1").arg(pArc->GetFrontColor().name());
        ui->FrontColor->setStyleSheet(sColor);   //前景色

        ui->m_pattern->setCurrentIndex(pArc->GetPattern());    //样式
        ui->m_alpha->setValue(pArc->GetAlpha()); //获得透明度
        break;
    case SAM_DRAW_OBJECT_TEXT:
        pTxt = qgraphicsitem_cast<QSimpleTextItem*>(pItem);
        sColor = QString("background:%1").arg(pTxt->GetRectBackColor().name());
        ui->BackColor->setStyleSheet(sColor);   //设置背景色

        sColor = QString("background:%1").arg(pTxt->GetRectFrontColor().name());
        ui->FrontColor->setStyleSheet(sColor);   //前景色
        sText = pTxt->GetText();
        ui->m_pattern->setCurrentIndex(pTxt->GetPattern());    //样式
        ui->m_alpha->setValue(pTxt->GetAlpha()); //获得透明度
        if(pTxt->GetRectOutLine()) //是否有边线框
            ui->m_linestyle->setCurrentIndex(1);
        else
            ui->m_linestyle->setCurrentIndex(0);
        break;
    case SAM_DRAW_OBJECT_FREELINE: //自由直线
        pFreeLine = qgraphicsitem_cast<QFreeLineItem*>(pItem);
        ui->m_linestyle->setCurrentIndex(pFreeLine->getLineType());  //线条样式
        ui->m_linewidth->setCurrentIndex(pFreeLine->getLineWidth());//线条宽度

        sColor = QString("background:%1").arg(pFreeLine->getLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //线条颜色
        ui->m_alpha->setValue(pFreeLine->getAlpha()); //获得透明度
        break;
    case SAM_DRAW_OBJECT_LINECIRCLE: //曲线/圆弧
        pCirleLine = qgraphicsitem_cast<QLineCircleItem*>(pItem);
        ui->m_linestyle->setCurrentIndex(pCirleLine->getLineType());  //线条样式
        ui->m_linewidth->setCurrentIndex(pCirleLine->getLineWidth());//线条宽度

        sColor = QString("background:%1").arg(pCirleLine->getLineColor().name());
        ui->LineColor->setStyleSheet(sColor);   //线条颜色
        ui->m_alpha->setValue(pCirleLine->getAlpha()); //获得透明度
        break;
    default:     break;
    }
    ui->m_table->setItem(7,0,new QTableWidgetItem(QString("%1").arg(nZvalue)));//层次
    ui->m_table->setItem(8,0,new QTableWidgetItem(sText));//文本内容
    nSelectClickFlag = false; //单击图形标识
}

void SKDrawTool::on_action_LeftAlign_triggered() //左对齐
{
    pScene->OnSetLeftAlign();
}

void SKDrawTool::on_action_RightAlign_triggered()//右对齐
{
    pScene->OnSetRightAlign();
}

void SKDrawTool::on_action_VCenter_triggered()//垂直居中
{
    pScene->OnSetVCenterAlign();
}

void SKDrawTool::on_action_TopAlign_triggered()//上对齐
{
    pScene->OnSetTopAlign();
}

void SKDrawTool::on_action_ButtomAlign_triggered()//下对齐
{
    pScene->OnSetButtomAlign();
}

void SKDrawTool::on_action_HCenter_triggered()//水平居中
{
    pScene->OnSetHCenterAlign();
}

void SKDrawTool::on_action_SameWidth_triggered()//等宽度
{
    pScene->setWidthSame();
}

void SKDrawTool::on_action_SameHeight_triggered()//等高度
{
    pScene->setHeightSame();
}

void SKDrawTool::on_action_SameWidthHeight_triggered()//等宽等高
{
    pScene->setWidthHeightSame();
}

void SKDrawTool::on_action_VMirror_triggered()//垂直镜像
{
    pScene->SetBaseItemMirror(2);
}

void SKDrawTool::on_action_HMirror_triggered()//水平镜像
{
    pScene->SetBaseItemMirror(1);
}

void SKDrawTool::on_action_DrawLine_triggered()//绘制直线
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_LINE;
}

void SKDrawTool::on_action_DrawFoldLine_triggered()//绘制折线
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_FOLDLINE;
}

void SKDrawTool::on_action_DrawCircleLine_triggered()//绘制曲线圆弧
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_LINE_CIRCLE;
}

void SKDrawTool::on_action_DrawFreeLine_triggered()//自由曲线
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_FREELINE;
}

void SKDrawTool::on_action_DrawRect_triggered()//矩形
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_RECT;
}

void SKDrawTool::on_action_DrawRoundRect_triggered()//圆角矩形
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_ROUNDED_RECT;
}

void SKDrawTool::on_action_Circle_triggered()//圆/椭圆
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_ELLIPSE;
}

void SKDrawTool::on_action_PoloyRect_triggered()//多边形
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_POLYGON;
}

void SKDrawTool::on_action_Arc_triggered()//扇形
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_ARC;
}

void SKDrawTool::on_action_DeleteItem_triggered()//删除图形
{
    QList <QGraphicsItem *> sList;
    sList = pScene->selectedItems();
    if (sList.isEmpty())
        return;

    foreach(QGraphicsItem *pItem,sList)
        pScene->removeItem(pItem);
}

void SKDrawTool::on_m_SaveItemBtn_clicked()//保存
{
    pwnd->SaveItemToLibList.clear();
    QList<QGraphicsItem *> item_list=pScene->selectedItems();
    QMessageBox box(this);
    if(item_list.size() < 1)
    {
        box.setText(tr("没图形需要保存!"));
        box.exec();
        return;
    }
    else if(item_list.size() > 1)
    {
        box.setText(tr("一次只能保存一个图形!"));
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

void SKDrawTool::on_m_Cancel_clicked()//取消
{
    pwnd->SaveItemToLibList.clear();
    QDialog::close();
}

void SKDrawTool::on_action_DrawText_triggered()//绘制文本
{
    SamDrawTool::s_eDrawActType = SAM_DRAW_SAMPLE_TEXT;
}

void SKDrawTool::on_action_movetoplest_triggered()//移到最上层
{
    pScene->OnOderTop();
}

void SKDrawTool::on_action_movedownlest_triggered()//移到最低层
{
    pScene->OnOderBotton();
}

void SKDrawTool::on_action_movefore_triggered()//上移一层
{
    pScene->OnOderUp();
}

void SKDrawTool::on_action_moveback_triggered()//下移一层
{
    pScene->OnOderDown();
}
