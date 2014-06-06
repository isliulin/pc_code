#include "qchartcmcolor.h"
#include "ui_qchartcmcolor.h"
#include "view/samdrawscene.h"
#include "view/qpolygonitem.h"
#include "Frame/addressinputdialog.h"
#include <QGraphicsOpacityEffect>

extern MainWindow *pwnd;

QChartCmColor::QChartCmColor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QChartCmColor)
{
    pCopyItem = NULL;
    bScaleFlag = true;
    m_nLoadShapeType = 1;
    nDirectionType = TOWARD_TOP;          //默认现实方向向上
    nMeterType = 0;          //所选择的圆和半圆的key值
    nLocation = 0;
    nInitFlag = false;
    ui->setupUi(this);
    pScene = new QGraphicsScene(this);//建场景
    ui->MainView->setScene(pScene);
    pwnd->OnAddPattern(ui->m_patterncmbox);
    ui->m_framecolorbtn->setEnabled(false);
    ui->m_framecolorlabel->setEnabled(false);
    ui->m_PointTypecbBox->setEnabled(false);
    ui->m_PointTypelabel->setEnabled(false);
    nInitFlag = true;
}

QChartCmColor::~QChartCmColor()
{
    if (pScene)
    {
        delete pScene;
        pScene = NULL;
    }
    delete ui;
}

void QChartCmColor::Init(ChartItem *pItem)
{
    bInitFlag = false;
    if(pItem)
    {
        //报警设置
        ui->m_AlarmckBox->setChecked(pItem->common_st.sAlarm.bAlarm);
        if(pItem->common_st.sAlarm.bAlarm)
        {
            ui->m_AlarmgroupBox->setEnabled(true);
        }
        else
        {
            ui->m_AlarmgroupBox->setEnabled(false);
        }

        ui->m_AlarmcbBox->setCurrentIndex(pItem->common_st.sAlarm.nType);
        on_m_AlarmcbBox_currentIndexChanged(pItem->common_st.sAlarm.nType);

        if(0 == pItem->common_st.sAlarm.nType)
        {
            ui->m_AlarmMinspBox->setText(pItem->common_st.sAlarm.nMin);
            ui->m_AlarmMaxspBox->setText(pItem->common_st.sAlarm.nMax);
        }
        else
        {
            ui->m_AddressMaxlineEdit->setText(pItem->common_st.sAlarm.nMax);
            ui->m_AddressMinlineEdit->setText(pItem->common_st.sAlarm.nMin);
            ui->m_AlarmMinspBox->setText("0");
            ui->m_AlarmMaxspBox->setText("100");
        }
        ui->m_Alarmshowcolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->common_st.sAlarm.nTextColor).name()));
        ui->m_Alarmshapecolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->common_st.sAlarm.nDesignColor).name()));

        ui->m_showcolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->common_st.nTextColor).name()));
        ui->m_backgroudcolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->common_st.nBackcolor).name()));
        ui->m_shapecolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->common_st.nDesignColor).name()));
        ui->m_framecolorbtn->setStyleSheet( QString("background:%1").arg(pwnd->StringTOColor(pItem->common_st.nFrameColor).name()));
        ui->m_patterncmbox->setCurrentIndex(pItem->common_st.nDesign);//图案

        setshowcolorbtnColor(pwnd->StringTOColor(pItem->common_st.nTextColor));
        setbackgroudbtnColor(pwnd->StringTOColor(pItem->common_st.nBackcolor));
        setshapecolorbtnColor(pwnd->StringTOColor(pItem->common_st.nDesignColor));
        setshowframebtnColor(pwnd->StringTOColor(pItem->common_st.nFrameColor));

        nMainScale = pItem->common_st.nMainScale;
        ui->m_PointTypecbBox->setCurrentIndex(pItem->common_st.nPointType);
        if(pItem->common_st.nScaleMark)
        {
            nSubScale = pItem->common_st.nSubScale;
        }
        else
        {
            nSubScale = 1;
        }
        sCaleColor = pItem->common_st.nRulingColor;
        circle = pItem->common_st.nCircle;

        pCommonItem = pItem;
        pCopyItem = pItem;
        pBaseItem = new QGroupItem(pCopyItem);
        pScene->clear();
        pScene->addItem(pCopyItem);
        QPointF pos(0,0);
        pCopyItem->setPos(pos - pCopyItem->boundingRect().topLeft());
        pBaseItem->SetWidth(100);
        pBaseItem->SetHeigth(100);

        switch(pItem->common_st.eShapeType)
        {
        case PILLA:    //普通图类型 柱状图、
            bScaleFlag = true;
            ui->m_framecolorbtn->setEnabled(false);
            ui->m_framecolorlabel->setEnabled(false);
            ui->m_PointTypecbBox->setEnabled(false);
            ui->m_PointTypelabel->setEnabled(false);
            m_nLoadShapeType = 1;
            break;
        case CIRCLE:
            ui->m_framecolorbtn->setEnabled(false);
            ui->m_framecolorlabel->setEnabled(false);
            ui->m_PointTypecbBox->setEnabled(true);
            ui->m_PointTypelabel->setEnabled(true);
            m_nLoadShapeType = 3;
            break;
        case SECTOR:
            ui->m_framecolorbtn->setEnabled(false);
            ui->m_framecolorlabel->setEnabled(false);
            ui->m_PointTypecbBox->setEnabled(false);
            ui->m_PointTypelabel->setEnabled(false);
            m_nLoadShapeType = 2;
            break;
        case GROOVE:
            ui->m_framecolorbtn->setEnabled(true);
            ui->m_framecolorlabel->setEnabled(true);
            ui->m_PointTypecbBox->setEnabled(false);
            ui->m_PointTypelabel->setEnabled(false);
            m_nLoadShapeType = 0;
            break;
        default:
            break;
        }
        bInitFlag = true;
        reDrawBar();
    }
    else
    {
        //初始化各控件属性
        nDirectionType = TOWARD_TOP;
        ui->m_AlarmckBox->setChecked(false);
        ui->m_AlarmgroupBox->setEnabled(false);//隐藏报警设置
        ui->m_AlarmMinspBox->setText("0");
        ui->m_AlarmMaxspBox->setText("100");
        on_m_AlarmcbBox_currentIndexChanged(0);
        ui->m_Alarmshowcolorbtn->setStyleSheet(QString("background:%1").arg(QColor(166,166,255).name()));
        ui->m_Alarmshapecolorbtn->setStyleSheet(QString("background:%1").arg(QColor(255,255,255).name()));

        ui->m_backgroudcolorbtn->setStyleSheet(QString("background:%1").arg(QColor(255,255,0).name()));
        ui->m_framecolorbtn->setStyleSheet(QString("background:%1").arg(QColor(224,224,224).name()));
        ui->m_shapecolorbtn->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
        ui->m_showcolorbtn->setStyleSheet(QString("background:%1").arg(QColor(255,0,0).name()));
        ui->m_backgroudcolorbtn->setStyleSheet(QString("background:%1").arg(QColor(255,255,0).name()));
        ui->m_framecolorbtn->setStyleSheet(QString("background:%1").arg(QColor(224,224,224).name()));
        ui->m_shapecolorbtn->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
        ui->m_showcolorbtn->setStyleSheet(QString("background:%1").arg(QColor(255,0,0).name()));

        circle.nstartAngle = 0;
        circle.nSpanAngle = 180;
        circle.nScaleStartAngle = 90;
        circle.nScaleSpanAngle = 180;
        circle.nMainScal = 4;
        circle.nSubScal = 0;
        circle.nRadiu = 0;
        circle.FirstPos = QPoint(0,0);
        circle.SecondPos = QPoint(25,25);
        circle.FirstColor = pwnd->ColorTOString(QColor(255,0,0));
        circle.SecondColor = pwnd->ColorTOString(QColor(255,255,255));
        circle.ScaleColor = sCaleColor;//pwnd->ColorTOString(QColor(255,0,0));
        circle.num = 0;

        nMainScale = 4;
        nSubScale = 1;
        sCaleColor = pwnd->ColorTOString(QColor(255,0,0));

        DrawBar();
        bInitFlag = true;
    }
}
void QChartCmColor::reDrawBar()
{
    ChartItem *newGroup = new ChartItem();
    QGraphicsItem * pVctorItem ;
    DrawItemToScene GroupFunction;
    QString sname;
    QRectF Rect;

    if(!pCopyItem)
    {
        return;
    }

    bool bBackPic = false;//标记是否有背景图片
    bool bShow = false;
    emit onGetShowValue(bShow);

    pCopyItem->resetTransform();
    sname = pCopyItem->data(GROUP_NAME_KEY).toString();
    int nKey = pCopyItem->data(GROUP_TYPE_KEY).toInt();


    QPointF oldpos = pCopyItem->sceneBoundingRect().topLeft();

    pCopyItem = getItemFromFile(nKey,"android.sk");
    if(!pCopyItem)
    {
        return;
    }

    GroupFunction.CopyItemForChart(&pVctorItem,pCopyItem);
    if (1 == m_nLoadShapeType || 0 == m_nLoadShapeType)
    {
        if (1 == m_nLoadShapeType)//柱形图。。
        {
            if (1 == nKey || 3 == nKey
                || 7 == nKey || 9 == nKey || 10 == nKey)
            {
                nLocation = 0;
            }
            else
            {
                nLocation = 1;
            }
            if(SplitItem(&pVctorItem,"BackItem"))
            {
                bBackPic = true;
                newGroup->addToGroup(pVctorItem);
            }
            else
            {
                delete pVctorItem;
                pVctorItem = NULL;
            }
            SplitItem(&pCopyItem,"FrameItem");
            if(bBackPic && !bShow)//有背景图片且不显示刻度，需要调整大小和位置
            {
                QPointF sPos = pCopyItem->sceneBoundingRect().topLeft();
                pCopyItem->setPos(sPos - QPointF(12,0) - pCopyItem->boundingRect().topLeft());
            }
            Rect = pCopyItem->sceneBoundingRect();
        }
        else if (0 == m_nLoadShapeType)
        {
            if (nKey >= 41)
            {
                bScaleFlag = false;
            }
            else
            {
                bScaleFlag = true;
            }
            nLocation = 1;
            if(SplitItem(&pVctorItem,"Vector"))
            {
                bBackPic = true;
                newGroup->addToGroup(pVctorItem);
            }
            else
            {
                delete pVctorItem;
                pVctorItem = NULL;
            }
            SplitItem(&pCopyItem,"HistogramItem");
            foreach(QGraphicsItem *pItem,pCopyItem->childItems())
            {
                if("BackItem" == pItem->data(GROUP_NAME_KEY).toString())
                {
                    if(bBackPic && !bShow && bScaleFlag)//有背景图片且不显示刻度，需要调整大小和位置
                    {
                        QPointF sPos = pCopyItem->sceneBoundingRect().topLeft();
                        pCopyItem->setPos(sPos - QPointF(-8,0) - pCopyItem->boundingRect().topLeft());
                    }
                    Rect = pItem->sceneBoundingRect();
                    break;
                }
            }
        }

        if (1 == m_nLoadShapeType)
        {
            onDrawFrontRect(&newGroup,Rect);
        }

        newGroup->addToGroup(pCopyItem);

        if (bScaleFlag)
        {
            OnDrawScal(&newGroup,nMainScale,nSubScale,nLocation,Rect.topLeft(),Rect.bottomRight());
        }
    }
    else if(2 == m_nLoadShapeType || 3 == m_nLoadShapeType)
    {
        circle.FirstColor = pwnd->ColorTOString(ui->m_backgroudcolorbtn->palette().background().color());
        nMeterType = nKey;
        onDrawBackRect(&newGroup,pVctorItem);
        DrawCircal(&newGroup,circle);
        onDrawCirclePoint(&newGroup,circle,nKey);
        onDrawCircleScale(&newGroup,circle);
    }

    newGroup->setData(GROUP_NAME_KEY,QVariant(sname));
    newGroup->setData(GROUP_TYPE_KEY,QVariant(nKey));
    pCommonItem = newGroup;
    pCopyItem = newGroup;
    pScene->clear();
    pScene->addItem(pCopyItem);

    QPointF newpos = pCopyItem->boundingRect().topLeft();
    pCopyItem->setPos(oldpos-newpos);

    if(0 == m_nLoadShapeType || 1 == m_nLoadShapeType)
    {
        int index = 0;
        emit onGetDirection(index );
        changeDirection(index);
    }

    pBaseItem = new QGroupItem(pCopyItem);
    if (1 == m_nLoadShapeType || 0 == m_nLoadShapeType)
    {
        pBaseItem->SetWidth(100);
        pBaseItem->SetHeigth(100);
    }
    else
    {
        qreal dWsize = pCopyItem->boundingRect().width();
        qreal dHsize = pCopyItem->boundingRect().height();
        qreal dDelta = dWsize/dHsize;
        if(dDelta > 1)//宽大于高
        {
            dWsize = 100.0;
            dHsize = abs(dWsize / dDelta);
        }
        else
        {
            dHsize = 100.0;
            dWsize = abs(dHsize * dDelta);
        }
        pBaseItem->SetWidth(dWsize);
        pBaseItem->SetHeigth(dHsize);
    }
}

void QChartCmColor::DrawBar()
{
    bScaleFlag = true;
    QPointF oldpos(0,0);
    QRectF rect;
    ChartItem *newGroup = new ChartItem();
    if (bInitFlag)
    {
        if (!pCopyItem)
        {
            return;
        }
        oldpos = pCopyItem->sceneBoundingRect().topLeft();
        if(3 == m_nLoadShapeType || 2 == m_nLoadShapeType)//选择圆形或者半圆形图形，根据图形index自己画图
        {
            //circle.FirstColor = pwnd->ColorTOString(ui->m_showcolorbtn->palette().background().color());
            if (2 == m_nLoadShapeType)//半圆
            {
                setCircleProperty(&newGroup,1);//画默认的第一个图形
                newGroup->setData(GROUP_NAME_KEY,QVariant(1));//设置第一个半圆名称
                newGroup->setData(GROUP_TYPE_KEY,QVariant(1));
            }
            else
            {
                circle.nstartAngle = 0;
                circle.nSpanAngle = 360;
                circle.nScaleStartAngle = 90;
                circle.nScaleSpanAngle = 360;
                circle.FirstPos = QPoint(0,0);
                circle.SecondPos = QPoint(25,25);
                setCircleProperty(&newGroup,7);//画默认的第一个图形
                newGroup->setData(GROUP_NAME_KEY,QVariant(7));//设置第一个圆名称
                newGroup->setData(GROUP_TYPE_KEY,QVariant(7));//设置第一个圆名称
            }
        }
        else//从SK文件中取第一个图形
        {
            QString sname;
            int nKey;
            if(!InitScene("android.sk"))
            {
                return;
            }
            sname = pCopyItem->data(GROUP_NAME_KEY).toString();
            nKey = pCopyItem->data(GROUP_TYPE_KEY).toInt();
            if (1 == m_nLoadShapeType)//柱形图。。
            {
                if (1 == nKey || 3 == nKey
                    || 7 == nKey || 9 == nKey || 10 == nKey)
                {
                    nLocation = 0;
                }
                else
                {
                    nLocation = 1;
                }
                SplitItem(&pCopyItem,"FrameItem");
                rect = pCopyItem->sceneBoundingRect();
            }
            else if (0 == m_nLoadShapeType)
            {
                nLocation = 1;
                SplitItem(&pCopyItem,"HistogramItem");
                foreach(QGraphicsItem *pItem,pCopyItem->childItems())
                {
                    if("BackItem" == pItem->data(GROUP_NAME_KEY).toString())
                    {
                        rect = pItem->sceneBoundingRect();
                        break;
                    }
                }
            }
            newGroup->addToGroup(pCopyItem);

            if (1 == m_nLoadShapeType)
            {
                onDrawFrontRect(&newGroup,rect);
            }

            OnDrawScal(&newGroup,nMainScale,nSubScale,nLocation,rect.topLeft(),rect.bottomRight());
            newGroup->setData(GROUP_NAME_KEY,QVariant(sname));
            newGroup->setData(GROUP_TYPE_KEY,QVariant(nKey));
        }
    }
    else
    {
        if(!InitScene("android.sk"))
        {
            return;
        }
        QString sname;
        int nKey;
        sname = pCopyItem->data(GROUP_NAME_KEY).toString();
        nKey =pCopyItem->data(GROUP_TYPE_KEY).toInt();
        if (1 == m_nLoadShapeType)//柱形图。。
        {
            SplitItem(&pCopyItem,"FrameItem");
            rect = pCopyItem->sceneBoundingRect();
        }
        else if (0 == m_nLoadShapeType)
        {
            int index = pCopyItem->data(GROUP_TYPE_KEY).toInt();
            if (index >= 41)
            {
                bScaleFlag = false;
            }
            SplitItem(&pCopyItem,"HistogramItem");
            foreach(QGraphicsItem *pItem,pCopyItem->childItems())
            {
                if("BackItem" == pItem->data(GROUP_NAME_KEY).toString())
                {
                    rect = pItem->sceneBoundingRect();
                    break;
                }
            }
        }

        newGroup->addToGroup(pCopyItem);
        if (1 == m_nLoadShapeType)
        {
            onDrawFrontRect(&newGroup,rect);
        }
        if (bScaleFlag)
        {
            OnDrawScal(&newGroup,nMainScale,nSubScale,0,rect.topLeft(),rect.bottomRight());
        }
        newGroup->setData(GROUP_NAME_KEY,QVariant(sname));
        newGroup->setData(GROUP_TYPE_KEY,QVariant(nKey));
    }
    pCommonItem = newGroup;
    pCopyItem = newGroup;
    pScene->clear();
    pScene->addItem(pCopyItem);

    QPointF newpos = pCopyItem->boundingRect().topLeft();
    pCopyItem->setPos(oldpos-newpos);

    pBaseItem = new QGroupItem(pCopyItem);
    if (1 == m_nLoadShapeType || 0 == m_nLoadShapeType)
    {
        pBaseItem->SetWidth(100);
        pBaseItem->SetHeigth(100);
    }
    else
    {
        qreal dWsize = pCopyItem->boundingRect().width();
        qreal dHsize = pCopyItem->boundingRect().height();
        qreal dDelta = dWsize/dHsize;
        if(dDelta > 1)//宽大于高
        {
            dWsize = 100.0;
            dHsize = abs(dWsize / dDelta);
        }
        else
        {
            dHsize = 100.0;
            dWsize = abs(dHsize * dDelta);
        }
        pBaseItem->SetWidth(dWsize);
        pBaseItem->SetHeigth(dHsize);
    }
}

void QChartCmColor::on_m_showcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_showcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setshowcolorbtnColor(const QColor &)));
}

void QChartCmColor::setshowcolorbtnColor(const QColor &mColor)//设置显示颜色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_showcolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(bInitFlag)
    {
        reDrawBar();
    }
}

void QChartCmColor::on_m_framecolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_framecolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setshowframebtnColor(const QColor &)));
}

void QChartCmColor::setshowframebtnColor(const QColor &mColor)//设置边框色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_framecolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(bInitFlag)
    {
        reDrawBar();
    }
}

void QChartCmColor::on_m_backgroudcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_showcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setbackgroudbtnColor(const QColor &)));
}

void QChartCmColor::setbackgroudbtnColor(const QColor &mColor)//设置背景色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_backgroudcolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(bInitFlag)
    {
        reDrawBar();
    }
}

void QChartCmColor::on_m_shapecolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_shapecolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setshapecolorbtnColor(const QColor &)));
}

void QChartCmColor::setshapecolorbtnColor(const QColor &mColor)//设置图案颜色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_shapecolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(bInitFlag)
    {
        reDrawBar();
    }
}

void QChartCmColor::on_m_patterncmbox_currentIndexChanged(int index)
{
    if(0 == index)
    {
        ui->label_10->setEnabled(false);
        ui->m_shapecolorbtn->setEnabled(false);
    }
    else
    {
        ui->label_10->setEnabled(true);
        ui->m_shapecolorbtn->setEnabled(true);
    }
    if (!nInitFlag)//防止pBarRect对象构造没完成就使用
    {
        return;
    }
    int nIndex = ui->m_patterncmbox->currentIndex();
    if(bInitFlag)
    {
        reDrawBar();
    }
}

void QChartCmColor::changeDirection(int nDirection)
{
    if(!bInitFlag)
    {
        return;
    }
    nDirectionType = nDirection;
    int angel = 0;
    pCopyItem->resetTransform();
    switch (nDirection)
    {
    case 0:
        nDirectionType = TOWARD_TOP;
        angel = 0;
        break;
    case 1:
        nDirectionType = TOWARD_BOTTOM;
        angel = 180;
        break;
    case 2:
        nDirectionType = TOWARD_LEFT;
        angel = 270;
        break;
    case 3:
        nDirectionType = TOWARD_RIGHT;
        angel = 90;
        break;
    default:
        return;
    }
    QPointF oldLeft(0,0);
    QPointF oldpos = pCopyItem->boundingRect().center();
    oldpos = pCopyItem->boundingRect().center();
    pCopyItem->setTransform(QTransform().translate(oldpos.x(), oldpos.y()).rotate(angel).translate(-oldpos.x(), -oldpos.y()));
    QPointF newLeft = pCopyItem->boundingRect().topLeft();
    pCopyItem->setPos(oldLeft - newLeft);

    //重新克隆一个新刻度是为了旋转后文本不旋转显示
    foreach(QGraphicsItem *pChildItem,pCopyItem->childItems())
    {
        if("ScaleText" == pChildItem->data(GROUP_NAME_KEY))
        {
            QGraphicsItem *pTextGroup = dynamic_cast<QItemGroup *> (pChildItem)->Clone();
            QItemGroup *pItem = dynamic_cast<QItemGroup *> (pCopyItem);
            pItem->removeFromGroup(pChildItem);
            pItem->addToGroup(pTextGroup);
            pScene->removeItem(pChildItem);
            break;
        }
    }
}

void QChartCmColor::setCommonShapeType(int nType)
{
    switch(nType)
    {
    case PILLA:    //普通图类型 柱状图、
        bScaleFlag = true;
        ui->m_framecolorbtn->setEnabled(false);
        ui->m_framecolorlabel->setEnabled(false);
        ui->m_PointTypecbBox->setEnabled(false);
        ui->m_PointTypelabel->setEnabled(false);
        m_nLoadShapeType = 1;
        break;
    case CIRCLE:
        ui->m_framecolorbtn->setEnabled(false);
        ui->m_framecolorlabel->setEnabled(false);
        ui->m_PointTypecbBox->setEnabled(true);
        ui->m_PointTypelabel->setEnabled(true);
        m_nLoadShapeType = 3;
        break;
    case SECTOR:
        ui->m_framecolorbtn->setEnabled(false);
        ui->m_framecolorlabel->setEnabled(false);
        ui->m_PointTypecbBox->setEnabled(false);
        ui->m_PointTypelabel->setEnabled(false);
        m_nLoadShapeType = 2;
        break;
    case GROOVE:
        ui->m_framecolorbtn->setEnabled(true);
        ui->m_framecolorlabel->setEnabled(true);
        ui->m_PointTypecbBox->setEnabled(false);
        ui->m_PointTypelabel->setEnabled(false);
        m_nLoadShapeType = 0;
        break;
    default:
        break;
    }
    DrawBar();
    //on_shape_selectBtn_clicked();
}

void QChartCmColor::on_shape_selectBtn_clicked()
{
    QString sname = "";
    int nKey;
    QGraphicsItem * pVctorItem ;
    pwnd->nLoadShapeFlag = 1;//加载图表的图形文件
    pwnd->nLoadShapeType = m_nLoadShapeType;//加载sk文件的第几个页面
    LoadShape *pShapeDlg = new LoadShape(this);
    int nAngle = 0;
    QRectF rect;

    bool bBackPic = false;//标记是否有背景图片
    bool bShow = false;
    emit onGetShowValue(bShow);
    if(pShapeDlg->exec() == QDialog::Accepted)
    {
        ChartItem *newGroup = new ChartItem();
        DrawItemToScene GroupFunction;
        QPointF oldpos = pCopyItem->sceneBoundingRect().topLeft();

        sname = pShapeDlg->pCopyItem->data(GROUP_NAME_KEY).toString();//保存ITem的名称
        nKey = pShapeDlg->pCopyItem->data(GROUP_TYPE_KEY).toInt();//保存ITem的名称
        if(3 == m_nLoadShapeType || 2 == m_nLoadShapeType)//圆或者半圆图形，自己画，不用文件中获取的ite
        {
            nMeterType = pShapeDlg->pCopyItem->data(GROUP_TYPE_KEY).toInt();
            onDrawBackRect(&newGroup,pShapeDlg->pCopyItem);
            if(2 == nMeterType || 3 == nMeterType || 5 == nMeterType || 9 == nMeterType || 12 == nMeterType || 15 == nMeterType)
            {
                bool bCheck = true;
                int nRadiu = 4;
                emit onGetroleCheck(bCheck, nRadiu);//true 是去设置 圆心半径和显示圆半径
            }
            setCircleProperty(&newGroup,nMeterType);
        }
        else
        {
            nAngle = pCopyItem->rotation();
            GroupFunction.CopyItemForChart(&pCopyItem,pShapeDlg->pCopyItem);
            GroupFunction.CopyItemForChart(&pVctorItem,pShapeDlg->pCopyItem);
            //QString sname = pVctorItem->data(GROUP_NAME_KEY).toString();
            int index  = pVctorItem->data(GROUP_TYPE_KEY).toInt();
            if (index >= 41)
            {
                bScaleFlag = false;
            }
            else
            {
                bScaleFlag = true;
            }
            if (1 == m_nLoadShapeType)
            {
                //sname = pVctorItem->data(GROUP_NAME_KEY).toString();
                int index = pVctorItem->data(GROUP_TYPE_KEY).toInt();
                if (1 == index || 3 == index
                    || 7 == index || 9 == index || 10 == index)
                {
                    nLocation = 0;
                }
                else
                {
                    nLocation = 1;
                }
                if(SplitItem(&pVctorItem,"BackItem"))
                {
                    bBackPic = true;
                    newGroup->addToGroup(pVctorItem);
                }
                else
                {
                    delete pVctorItem;
                }
                SplitItem(&pCopyItem,"FrameItem");

                if(bBackPic && !bShow)//有背景图片且不显示刻度，需要调整大小和位置
                {
                    QPointF sPos = pCopyItem->sceneBoundingRect().topLeft();
                    pCopyItem->setPos(sPos - QPointF(12,0) - pCopyItem->boundingRect().topLeft());
                }
                rect = pCopyItem->sceneBoundingRect();
            }
            else if (0 == m_nLoadShapeType)
            {
                nLocation = 1;
                if(SplitItem(&pVctorItem,"Vector"))
                {
                    bBackPic = true;
                    newGroup->addToGroup(pVctorItem);
                }
                else
                {
                    delete pVctorItem;
                }
                SplitItem(&pCopyItem,"HistogramItem");
                foreach(QGraphicsItem *pItem,pCopyItem->childItems())
                {
                    if("BackItem" == pItem->data(GROUP_NAME_KEY).toString())
                    {
                        if(bBackPic && !bShow && bScaleFlag)//有背景图片且不显示刻度，需要调整大小和位置
                        {
                            QPointF sPos = pCopyItem->sceneBoundingRect().topLeft();
                            pCopyItem->setPos(sPos - QPointF(-8,0) - pCopyItem->boundingRect().topLeft());
                        }
                        rect = pItem->sceneBoundingRect();
                        break;
                    }
                }
            }

            newGroup->addToGroup(pCopyItem);

            if (1 == m_nLoadShapeType)
            {
                onDrawFrontRect(&newGroup,rect);
            }

            if(bScaleFlag)
            {
                OnDrawScal(&newGroup,nMainScale,nSubScale,nLocation,rect.topLeft(),rect.bottomRight());
            }
        }
        pCommonItem = newGroup;
        pCopyItem = newGroup;
        pCopyItem->setData(GROUP_NAME_KEY,QVariant(sname));
        pCopyItem->setData(GROUP_TYPE_KEY,QVariant(nKey));
        pScene->clear();
        pScene->addItem(pCopyItem);

        QPointF newpos = pCopyItem->boundingRect().topLeft();
        pCopyItem->setPos(oldpos-newpos);
        if(0 == m_nLoadShapeType || 1 == m_nLoadShapeType)
        {
            int index = 0;
            emit onGetDirection(index );
            changeDirection(index);
        }

        pBaseItem = new QGroupItem(pCopyItem);
        pBaseItem = new QGroupItem(pCopyItem);
        if (1 == m_nLoadShapeType || 0 == m_nLoadShapeType)
        {
            pBaseItem->SetWidth(100);
            pBaseItem->SetHeigth(100);
        }
        else
        {
            qreal dWsize = pCopyItem->boundingRect().width();
            qreal dHsize = pCopyItem->boundingRect().height();
            qreal dDelta = dWsize/dHsize;
            if(dDelta > 1)//宽大于高
            {
                dWsize = 100.0;
                dHsize = abs(dWsize / dDelta);
            }
            else
            {
                dHsize = 100.0;
                dWsize = abs(dHsize * dDelta);
            }
            pBaseItem->SetWidth(dWsize);
            pBaseItem->SetHeigth(dHsize);
        }
    }
    pwnd->nLoadShapeType = 0;
    pwnd->nLoadShapeFlag = 0;
    pShapeDlg->deleteLater();
    pShapeDlg = NULL;
}

bool QChartCmColor::SplitItem(QGraphicsItem **pItem,QString sname)
{
    QList<QGraphicsItem *> childitem;
    QGraphicsItem *item;
    childitem = (*pItem)->childItems();
    int nSize = childitem.size();
    int i = 0;
    QString sPartName = "";
    DrawItemToScene GroupFunction;

    if(nSize < 2)
        return false;

    if ("HistogramItem" == sname)
    {
        for (i = 0; i < nSize; i++)
        {
            item = childitem.at(i);
            sPartName = item->data(GROUP_NAME_KEY).toString(); //取得名次
            if (sPartName == "HistogramItem")
            {
                //add for 多边形设置颜色 begin
                childitem = item->childItems();
                nSize = childitem.size();
                for (int j = 0; j < nSize; j++)
                {
                    QGraphicsItem *pitem = childitem.at(j);
                    sPartName = pitem->data(GROUP_NAME_KEY).toString();
                    if ("BackItem" == sPartName)
                    {
                        if (SAM_DRAW_OBJECT_POLYGON == pitem->type())
                        {
                            QPolygonItem *pBackItem = dynamic_cast<QPolygonItem *>(pitem);
                            pBackItem->setBackColor(ui->m_showcolorbtn->palette().background().color());
                            pBackItem->setPattern(ui->m_patterncmbox->currentIndex());
                            pBackItem->setFrontColor(ui->m_shapecolorbtn->palette().background().color());
                        }
                        else if (SAM_DRAW_OBJECT_ELIPSE == pitem->type())
                        {
                            QElipseItem *pBackItem = dynamic_cast<QElipseItem *> (pitem);
                            pBackItem->SetBackColor(ui->m_showcolorbtn->palette().background().color());
                            pBackItem->SetPattern(ui->m_patterncmbox->currentIndex());
                            pBackItem->SetFrontColor(ui->m_shapecolorbtn->palette().background().color());
                        }
                    }
                    if ("FrameItem" == sPartName)
                    {
                        if (SAM_DRAW_OBJECT_POLYGON == pitem->type())
                        {
                            QPolygonItem *pFramItem = dynamic_cast<QPolygonItem *>(pitem);
                            pFramItem->setBackColor(ui->m_framecolorbtn->palette().background().color());
                        }
                        else if (SAM_DRAW_OBJECT_ELIPSE == pitem->type())
                        {
                            QElipseItem *pFramItem = dynamic_cast<QElipseItem *> (pitem);
                            pFramItem->SetBackColor(ui->m_framecolorbtn->palette().background().color());
                        }
                    }
                }
                //add for 多边形设置颜色 end
                GroupFunction.CopyItemForChart(pItem,item);
                break;
            }
            else if("FrameItem" == sPartName)
            {
                if (SAM_DRAW_OBJECT_POLYGON == item->type())
                {
                    QPolygonItem *pFramItem = dynamic_cast<QPolygonItem *>(item);
                    pFramItem->setBackColor(ui->m_framecolorbtn->palette().background().color());
                }
                else if (SAM_DRAW_OBJECT_ELIPSE == item->type())
                {
                    QElipseItem *pFramItem = dynamic_cast<QElipseItem *> (item);
                    pFramItem->SetBackColor(ui->m_framecolorbtn->palette().background().color());
                }
            }
            else if("BackItem" == sPartName)
            {
                if (SAM_DRAW_OBJECT_POLYGON == item->type())
                {
                    QPolygonItem *pBackItem = dynamic_cast<QPolygonItem *>(item);
                    pBackItem->setBackColor(ui->m_showcolorbtn->palette().background().color());
                    pBackItem->setPattern(ui->m_patterncmbox->currentIndex());
                    pBackItem->setFrontColor(ui->m_shapecolorbtn->palette().background().color());
                }
                else if (SAM_DRAW_OBJECT_ELIPSE == item->type())
                {
                    QElipseItem *pBackItem = dynamic_cast<QElipseItem *> (item);
                    pBackItem->SetBackColor(ui->m_showcolorbtn->palette().background().color());
                    pBackItem->SetPattern(ui->m_patterncmbox->currentIndex());
                    pBackItem->SetFrontColor(ui->m_shapecolorbtn->palette().background().color());
                }
            }
        }
    }
    else if("Vector" == sname)
    {
        for (i = 0; i < nSize; i++)
        {
            item = childitem.at(i);
            sPartName = item->data(GROUP_NAME_KEY).toString(); //取得名次
            if (sPartName == "Vector")
            {
                GroupFunction.CopyItemForChart(pItem,item);
                return true;
            }
        }
    }
    else if("BackItem" == sname)
    {
        for (i = 0; i < nSize; i++)
        {
            item = childitem.at(i);
            sPartName = item->data(GROUP_NAME_KEY).toString(); //取得名次
            if (sPartName == "BackItem")
            {
                GroupFunction.CopyItemForChart(pItem,item);
                return true;
            }
        }
    }
    else if("FrameItem" == sname)
    {
        for (i = 0; i < nSize; i++)
        {
            item = childitem.at(i);
            sPartName = item->data(GROUP_NAME_KEY).toString(); //取得名次
            if (sPartName == "FrameItem")
            {
                QRectItem *pRectItem = dynamic_cast<QRectItem *>(item);
                pRectItem->SetLineType(0);
                pRectItem->SetBackColor(ui->m_backgroudcolorbtn->palette().background().color());
                GroupFunction.CopyItemForChart(pItem,item);
                return true;
            }
        }
    }
    else if("ScaleItem" == sname)
    {
        for (i = 0; i < nSize; i++)
        {
            item = childitem.at(i);
            sPartName = item->data(GROUP_NAME_KEY).toString(); //取得名次
            if (sPartName == "ScaleItem")
            {
                GroupFunction.CopyItemForChart(pItem,item);
                return true;
            }
        }
    }
    return false;
}
/**/
void QChartCmColor::OnDrawScal(ChartItem **pGroupItem,int iDrawMain,int iDrawSun,int iDerection,QPointF leftPoint,QPointF rbottomPoint)
{
    if(iDrawMain < 2 || iDrawSun < 1)
    {
        return;
    }
    QItemGroup *pIten = new QItemGroup;
    QItemGroup *pTextGroup = new QItemGroup;
    QLineItem *pLineScal;
    QString sName = "";
    double mMoveX = 0;                     //主刻度X起始点
    double mMoveY = 0;                     //主刻度Y起始点
    double mLineX = 0;                     //主刻度X终点
    double mLineY = 0;                     //主刻度Y终点
    int nMainScaleLength = 6;              //主刻度的长度
    int nSubScaleL = nMainScaleLength / 2; //次刻度长度
    double nPerScaleLength = 0;                 //每刻度跨长度
    int nTotalScale = 0;                     //总刻度数
    bool bIsMainscal = false;
    short nGrooveScale = 10;              //槽型图刻度与框的距离
    iDrawMain = iDrawMain + 1;
    iDrawSun = iDrawSun - 1;
    double dMin = 0;
    double dMax = 100;
    QRectF rect;
    bool bShow = false;
    emit onGetShowValue(bShow);

    if(!bShow)
    {
        return;
    }
    emit onGetdataRange(dMin, dMax);
    int dValue = (dMax - dMin)/(iDrawMain - 1);
    int dFirst = dMax;

    nTotalScale = (iDrawMain - 1) * iDrawSun + iDrawMain;


    nPerScaleLength = (rbottomPoint.y() - leftPoint.y()) / (nTotalScale - 1.0);

    if (0 == iDerection)//画到柱形的左边
    {
        QPainterPath mPath;

        mPath.moveTo(leftPoint.x() - 6.0,leftPoint.y());             //画直线的起点
        mPath.lineTo(leftPoint.x() - 6.0,rbottomPoint.y());             //画直线的终点

        pLineScal = new QLineItem(mPath);        //画细直线
        pLineScal->setLineColor(pwnd->StringTOColor(sCaleColor));  //设置直线颜色
        pLineScal->setZValue(4);                 //设置层次

        sName = "MainLine";
        pLineScal->SetName(sName);               //设置名称
        pIten->addToGroup(pLineScal);           //添加到组
    }
    else
    {
        QPainterPath mPath;

        if(1 == m_nLoadShapeType)
        {
            mPath.moveTo(rbottomPoint.x() + 6.0,leftPoint.y());             //画直线的起点
            mPath.lineTo(rbottomPoint.x() + 6.0,rbottomPoint.y());             //画直线的终点
        }
        else
        {
            mPath.moveTo(rbottomPoint.x() + nGrooveScale,leftPoint.y());             //画直线的起点
            mPath.lineTo(rbottomPoint.x() + nGrooveScale,rbottomPoint.y());             //画直线的终点
        }

        pLineScal = new QLineItem(mPath);        //画细直线
        pLineScal->setLineColor(pwnd->StringTOColor(sCaleColor));  //设置直线颜色
        pLineScal->setZValue(4);                 //设置层次

        sName = "MainLine";
        pLineScal->SetName(sName);               //设置名称
        pIten->addToGroup(pLineScal);           //添加到组
    }

    int k = 0;//当前属于第几条主刻度记录，为计算刻度值做记录
    for (int i = 0; i < nTotalScale; i ++)
    {
        //画主刻度
        if (0 == iDerection)
        {

            mMoveX = leftPoint.x() - 6.0;
            mMoveY = i * nPerScaleLength + leftPoint.y();

            if (i % (iDrawSun + 1) == 0)
            {
                bIsMainscal = true;
                mLineX = mMoveX - nMainScaleLength;//住刻度长度
                rect.setTopLeft(QPointF(mLineX-22, mMoveY - 10));
            }
            else
            {
                bIsMainscal = false;
                mLineX = mMoveX - nSubScaleL;//次刻度长度
            }

            mLineY = i * nPerScaleLength + leftPoint.y();
        }
        else
        {
            if(1 == m_nLoadShapeType)
            {
                mMoveX = rbottomPoint.x() + 6.0;
            }
            else
            {
                mMoveX = rbottomPoint.x() + nGrooveScale;
            }

            mMoveY = i * nPerScaleLength + leftPoint.y();

            if (i % (iDrawSun + 1) == 0)
            {
                bIsMainscal = true;
                mLineX = mMoveX + nMainScaleLength;//住刻度长度
                rect.setTopLeft(QPointF(mLineX + 2, mMoveY - 10));
            }
            else
            {
                bIsMainscal = false;
                mLineX = mMoveX + nSubScaleL;//次刻度长度
            }

            mLineY = i * nPerScaleLength + leftPoint.y();
        }

        QPainterPath mPath;
        mPath.moveTo(mMoveX,mMoveY);             //画直线的起点
        mPath.lineTo(mLineX,mLineY);             //画直线的终点
        pLineScal = new QLineItem(mPath);        //画细直线
        pLineScal->setLineColor(pwnd->StringTOColor(sCaleColor));  //设置直线颜色
        pLineScal->setZValue(4);                 //设置层次

        sName = QString("%1").arg(i);
        if(bIsMainscal)
        {
            sName = "MainLineScal"+sName;
        }
        else
        {
            sName = "SubLineScal"+sName;
        }
        pLineScal->SetName(sName);               //设置名称
        pIten->addToGroup(pLineScal);           //添加到组

        //画刻度数值
        if (i % (iDrawSun + 1) == 0 && bShow)
        {
            QString sText = GetText(iDrawMain - k -1,dMin, dMax,iDrawMain);//QString::number(dFirst);
            if("-0" == sText) sText = "0";
            rect.setSize(QSize(20,20));
            QSimpleTextItem *pText = new QSimpleTextItem(rect,sText);

            pText->SetFontSize(8);
            pText->SetFontColor(pwnd->StringTOColor(sCaleColor));
            pText->SetRectOutLine(false);
            if(0 == iDerection)
            {
                //pText->SetTextAlign(6);//刻度在左边则文字右边对齐
            }
            else
            {
                //pText->SetTextAlign(4);//刻度在右边则文字左边对齐
            }
            pTextGroup->addToGroup(pText);
            k++;
        }
    }
    pTextGroup->setData(GROUP_NAME_KEY,"ScaleText");
    pIten->setData(GROUP_NAME_KEY,"ScaleItem");
    (*pGroupItem)->addToGroup(pIten);
    if(bShow)
    (*pGroupItem)->addToGroup(pTextGroup);
}

//void QChartCmColor::InitScene(QString sPath)
bool QChartCmColor::InitScene(QString sPath)
{
    bool bfind = false;
    //QString sname = "";
    SamDrawScene *pSvene = NULL;
    DrawItemToScene GroupFunction;
    QList <QGraphicsItem*> listItem;
    QVector <SamDrawScene *> vScene;
    vScene.clear();
    QFile file(sPath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return bfind;
    }
    QDataStream openData(&file);
    int sceneSize = 0;
    openData >> sceneSize;
    for(int i =0; i< sceneSize; i++)
    {
        pSvene = new SamDrawScene();
        //openData >> pSvene;
        pSvene->load(openData,pSvene);
        vScene.push_back(pSvene);
    }
    //listItem = pSvene->TopItems();
    listItem = vScene.at(m_nLoadShapeType)->TopItems();
    foreach (QGraphicsItem * pItem, listItem)
    {
        //nShapeID = pItem->data(GROUP_NAME_KEY).toInt();
        int index = pItem->data(GROUP_TYPE_KEY).toInt();
        if (index == 1)//四种形状图形第一个默认图形的名称
        {
            GroupFunction.CopyItemForChart(&pCopyItem,pItem);
            bfind = true;
            break;
        }
    }
    file.close();
    return bfind;
}

void QChartCmColor::setCircleProperty(ChartItem **newGroup,int index)
{
    if(7 == index || 10 == index || 13 == index)
    {
        circle.bPoint = true;
    }
    else
    {
        circle.bPoint = false;
    }
    bool bCheck = false;
    int nRadiu = 0;
    emit onGetroleCheck(bCheck, nRadiu);
    if(bCheck)
    {
        circle.num = 1;
        circle.nRadiu = nRadiu;
    }
    else
    {
        circle.num = 0;
    }
//    if(2 == index || 3 == index || 5 == index || 9 == index || 12 == index || 15 == index)
//    {
//        circle.num = 1;
//    }
//    else
//    {
//        circle.num = 0;
//    }
    switch(index)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        circle.nstartAngle = 0;
        circle.nSpanAngle = 180;
        circle.nScaleStartAngle = 0;
        circle.nScaleSpanAngle = 180;
        circle.nMainScal = nMainScale;
        circle.nSubScal = nSubScale;
        //circle.FirstPos = QPoint(0,0);
        //circle.SecondPos = QPoint(5,5);
        circle.FirstColor = pwnd->ColorTOString(ui->m_backgroudcolorbtn->palette().background().color());
        circle.SecondColor = pwnd->ColorTOString(QColor(0,0,255));
        circle.ScaleColor = sCaleColor;
        //circle.num = 0;
        break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        circle.nstartAngle = 0;
        circle.nSpanAngle = 360;
        circle.nScaleStartAngle = 90;
        circle.nScaleSpanAngle = 360;
        circle.nMainScal = nMainScale;
        circle.nSubScal = nSubScale;
        //circle.FirstPos = QPoint(0,0);
        //circle.SecondPos = QPoint(5,5);
        circle.FirstColor = pwnd->ColorTOString(ui->m_backgroudcolorbtn->palette().background().color());
        circle.SecondColor = pwnd->ColorTOString(QColor(0,0,255));
        circle.ScaleColor = sCaleColor;
        //circle.num = 0;
        break;
    default:
        break;

    }

    DrawCircal(newGroup,circle);
    onDrawCircleScale(newGroup,circle);
    onDrawCirclePoint(newGroup,circle,index);
}

void QChartCmColor::DrawCircal(ChartItem **pGroupItem,CIRCLE_TYPE circle)
{
    int nWidth = 90;      //圆的宽度
    int nHeight = 90;     //圆的高度
    bool bShow = false;
    int nPointType = 1;
    QElipseItem *pBackCircle = NULL;
    QElipseItem *pCircle = NULL;

    emit onGetPointType(nPointType);

    emit onGetShowValue(bShow);
    if(bShow)//显示圆刻度值
    {
       nWidth = 60;
       nHeight = 60;
    }

    if(3 == m_nLoadShapeType)
    {
        short nStart = 0;
        short nSpan = 360;
        emit onGetStartAngle(nStart,nSpan);
        circle.nstartAngle =90 + 360 - nSpan - nStart;//逆时针跨度
        circle.nSpanAngle = nSpan;

        short nTransparent = 255;
        bool bShowFrame = true;
        emit onGetCircleAlpha(nTransparent);
        emit onGetShowFrame(bShowFrame);
        circle.nTransparent = nTransparent;
        circle.bShowFrame = bShowFrame;
    }

    QRectF fRect(circle.FirstPos,QSize(nWidth,nHeight));    //设置大小

    pBackCircle = new QElipseItem(fRect);      //绘制一个圆
    pBackCircle->SetStartAngle(circle.nstartAngle);                  //设置开始角度
    pBackCircle->SetSpanAngle(circle.nSpanAngle);
    pBackCircle->SetBackColor(pwnd->StringTOColor(circle.FirstColor));
    pBackCircle->SetName("mFirstCircle");                   //设置圆的名称
    pBackCircle->SetLineColor(pwnd->StringTOColor(circle.ScaleColor));
    if(3 == m_nLoadShapeType)
    {
        pBackCircle->SetAlpha(circle.nTransparent);
        pBackCircle->SetLineColor(pwnd->StringTOColor(circle.ScaleColor));
        if(circle.bShowFrame == false)
        {
            pBackCircle->SetLineType(0);
        }
    }
    (*pGroupItem)->addToGroup(pBackCircle);              //添加到组

    if(0 == nPointType || 2 == m_nLoadShapeType)//显示填充
    {
        pCircle = new QElipseItem(fRect);      //绘制一个圆

        pCircle->SetStartAngle(circle.nstartAngle);                  //设置开始角度
        pCircle->SetSpanAngle(circle.nSpanAngle);
        pCircle->SetBackColor(ui->m_showcolorbtn->palette().background().color());           //设置背景色
        pCircle->setZValue(4);                              //设置层次

        pCircle->SetPattern(ui->m_patterncmbox->currentIndex());
        pCircle->SetFrontColor(ui->m_shapecolorbtn->palette().background().color());
        pCircle->SetLineColor(pwnd->StringTOColor(circle.ScaleColor));
        (*pGroupItem)->addToGroup(pCircle);              //添加到组
    }


    if (0 == circle.num || 0 == circle.nRadiu)
    {
        return;
    }
    else
    {
        float nR = 0;
        if(circle.nRadiu >= 10 || circle.nRadiu < 0)
        {
            return;
        }
        nR = circle.nRadiu * 0.1;
        pBackCircle->setPropor(nR,27);

        if(NULL != pCircle)
            pCircle->setPropor(nR,27);
    }

}

void QChartCmColor::onDrawCircleScale(ChartItem **pGroupItem,CIRCLE_TYPE circle)
{
    QItemGroup *pTextGroup = new QItemGroup;
    QLineItem *pLineScal;
    int nWidth = 90;                 //圆的宽度
    int nHeight = 90;                //圆的高度
    double mMoveX = 0;                //主刻度X起始点
    double mMoveY = 0;                //主刻度Y起始点
    double mLineX = 0;                //主刻度X起始点
    double mLineY = 0;                //主刻度Y起始点
    double mMainAngle = 0;            //主刻度偏转角度， 弧度制
    double mSubAngle = 0;             //次刻度偏转角度， 弧度制
    double mConst = 3.1415926;        //常量
    int nMainScaleL = 6;              //主刻度的长度
    int nSubScaleL = nMainScaleL / 2; //次刻度长度
    int nSunLineCount = 0;            //次刻度线总数
    int nDrawMainScal = circle.nMainScal;    //主刻度数
    double dTotalAngle;               //仪表刻度跨的角度大小，角度制
    int i = 0;
    QString sName = "";
    QRectF rect(QPointF(0,0), QSize(50,50));

    //获取圆的起始角度和跨角度
    short nStartAngle = 0;   //圆形图的刻度开始角度
    short nSpan = 360;
    if(3 == m_nLoadShapeType)
    {
        emit onGetStartAngle(nStartAngle,nSpan);
        circle.nScaleSpanAngle = nSpan;
        circle.nScaleStartAngle = nStartAngle + 90;
    }

    bool bShow = false;
    emit onGetShowValue(bShow);
    if(bShow)//显示圆刻度值
    {
       nWidth = 60;
       nHeight = 60;
    }
    else
    {
        return;
    }

    nDrawMainScal++;

    dTotalAngle = ((circle.nScaleSpanAngle) * mConst) / 180;
    double dRotation = circle.nScaleSpanAngle/(nDrawMainScal - 1.0);
    mMainAngle = dTotalAngle / (nDrawMainScal - 1);
    mSubAngle = dTotalAngle / (circle.nSubScal*(nDrawMainScal - 1));

    if(360 == (circle.nScaleSpanAngle))
    {
        nDrawMainScal--;
    }

    double dMin = 0;
    double dMax = 100;
    emit onGetdataRange(dMin, dMax);
    double dValue = 0;
    if(360 == (circle.nScaleSpanAngle))
    {
        dValue = (dMax - dMin)/(nDrawMainScal);
    }
    else
    {
        dValue = (dMax - dMin)/(nDrawMainScal - 1);
    }
    double dFirst = dMin;

    for(i = 0; i < nDrawMainScal; i++)  //画主刻度nMainScal
    {
        mMoveX = nWidth/2 - nWidth/2 * cos(mMainAngle*i + ((circle.nScaleStartAngle) * mConst) / 180);
        mMoveY = nWidth/2 - nWidth/2 * sin(mMainAngle*i + ((circle.nScaleStartAngle) * mConst) / 180);

        mLineX = nWidth/2 - (nWidth/2+nMainScaleL)*cos(mMainAngle*i + ((circle.nScaleStartAngle)* mConst) / 180);
        mLineY = nHeight/2 - (nWidth/2+nMainScaleL)*sin(mMainAngle*i + ((circle.nScaleStartAngle) * mConst) / 180);

        QPainterPath mPath;
        mPath.moveTo(mMoveX,mMoveY);             //画直线的起点
        mPath.lineTo(mLineX,mLineY);             //画直线的终点
        pLineScal = new QLineItem(mPath);        //画细直线
        pLineScal->setLineColor(pwnd->StringTOColor(circle.ScaleColor));  //设置直线颜色
        pLineScal->setZValue(3);                 //设置层次

        sName = QString("%1").arg(i);
        sName = "MainLineScal"+sName;
        pLineScal->SetName(sName);               //设置名称
        (*pGroupItem)->addToGroup(pLineScal);           //添加到组


        //画圆的刻度值
        if(bShow)//显示圆刻度值
        {
            QString sText;//QString::number(dFirst);
            sText.sprintf("%.0f", dFirst);
            if(360 != (circle.nScaleSpanAngle) && i == (nDrawMainScal -1))
            {
                sText = QString::number(dMax);
            }
            rect.setTopLeft(QPointF(nWidth/2 - 10, -26));//离圆顶点24个坐标，宽高为20个坐标
            rect.setSize(QSize(20,20));
            QSimpleTextItem *pText = new QSimpleTextItem(rect,sText);

            pText->SetFontSize(8);
            pText->SetFontColor(pwnd->StringTOColor(sCaleColor));
            pText->SetRectOutLine(false);
            pText->setTransformOriginPoint(nWidth/2,nHeight/2);
            pText->setRotation(dRotation*i + circle.nScaleStartAngle - 90.0);
            QSimpleTextItem *pnew = pText->Clone();//暂时clone一个处理旋转后字符也旋转了的问题
            delete pText;
            pText = NULL;
            pTextGroup->addToGroup(pnew);
            dFirst = dMin + (i + 1) * dValue;
        }
    }

    if(bShow)
    (*pGroupItem)->addToGroup(pTextGroup);

    nSunLineCount = circle.nSubScal*(nDrawMainScal -1);//次刻度线总数
    if(360 == (circle.nScaleSpanAngle))
    {
        nSunLineCount = circle.nSubScal*(nDrawMainScal);//次刻度线总数
    }
    for(i = 0; i < nSunLineCount; i++)  //画次刻度
    {
        if( i%(circle.nSubScal) != 0)
        {
            mMoveX = nWidth/2 - nWidth/2 * cos(mSubAngle*i + ((circle.nScaleStartAngle) * mConst) / 180);
            mMoveY = nWidth/2 - nWidth/2 * sin(mSubAngle*i + ((circle.nScaleStartAngle) * mConst) / 180);

            mLineX = nWidth/2 - (nWidth/2+nSubScaleL)*cos(mSubAngle*i + ((circle.nScaleStartAngle) * mConst) / 180);
            mLineY = nHeight/2 - (nWidth/2+nSubScaleL)*sin(mSubAngle*i + ((circle.nScaleStartAngle) * mConst) / 180);

            QPainterPath mPath;
            mPath.moveTo(mMoveX,mMoveY);             //画直线的起点
            mPath.lineTo(mLineX,mLineY);             //画直线的终点
            pLineScal = new QLineItem(mPath);        //画细直线
            pLineScal->setLineColor(pwnd->StringTOColor(circle.ScaleColor));  //设置直线颜色
            pLineScal->setZValue(5);                 //设置层次

            sName = QString("%1").arg(i);
            sName = "SubLineScal"+sName;
            pLineScal->SetName(sName);               //设置名称

            (*pGroupItem)->addToGroup(pLineScal);
        }
    }
}

void QChartCmColor::onDrawBackRect(ChartItem **pGroupItem ,QGraphicsItem *pBackItem)
{
    if ((nMeterType >= 1 && nMeterType <= 2) || (nMeterType >= 7 && nMeterType <= 9) || !pBackItem)
    {
        return;
    }

    QGraphicsItem *pNewItem = NULL;
    DrawItemToScene GroupFunction;
    foreach(QGraphicsItem *pItem,pBackItem->childItems())
    {
        if("BackItem" == pItem->data(GROUP_NAME_KEY).toString())
        {
            GroupFunction.CopyItemForChart(&pNewItem,pItem);
            QGroupItem *pBaseItem = new QGroupItem(pNewItem);
            if(nMeterType >= 3 && nMeterType <= 6)
            {
                pBaseItem->SetWidth(126);
                pBaseItem->SetHeigth(70);
            }
            else
            {
                pBaseItem->SetWidth(126);
                pBaseItem->SetHeigth(126);
            }
            break;
        }
    }
    if(pNewItem)
    {
        bool bShow = false;
        emit onGetShowValue(bShow);
        QPointF pos(-18,-18);
        if(bShow)
        {
            pos.setX(-32);
            pos.setY(-32);
        }
        pos = (*pGroupItem)->mapFromParent(pos);
        pNewItem->setPos(pos - pNewItem->boundingRect().topLeft());
        (*pGroupItem)->addToGroup(pNewItem);
    }
    return;
}

void QChartCmColor::onDrawFrontRect(ChartItem **pGroupItem,QRectF rect)
{
    QRectItem *pFrontRect;
    QRectF pos = rect;
    pos.setY(rect.topLeft().y() + rect.height()/2);
    pos.setHeight(rect.height()/2);

    pFrontRect = new QRectItem(pos);
    pFrontRect->SetBackColor(ui->m_showcolorbtn->palette().background().color());
    pFrontRect->SetLineType(0);
    pFrontRect->setZValue(2);
    pFrontRect->SetName(tr("mShowRect"));
    pFrontRect->SetPattern(ui->m_patterncmbox->currentIndex());
    pFrontRect->SetFrontColor(ui->m_shapecolorbtn->palette().background().color());
    pFrontRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFrontRect->setFlag(QGraphicsItem::ItemIsMovable, false);

    (*pGroupItem)->addToGroup(pFrontRect);

}

bool QChartCmColor::CommonGenSave(struct COMMON_INFORMATION &common_st)
{
    common_st.nTextColor = pwnd->ColorTOString(ui->m_showcolorbtn->palette().background().color());
    common_st.nBackcolor = pwnd->ColorTOString(ui->m_backgroudcolorbtn->palette().background().color());
    common_st.nDesignColor = pwnd->ColorTOString(ui->m_shapecolorbtn->palette().background().color());
    common_st.nFrameColor = pwnd->ColorTOString(ui->m_framecolorbtn->palette().background().color());
    common_st.nDesign = ui->m_patterncmbox->currentIndex();//图案
    common_st.eShapeId = (GRAPH_SHAPE)(pCommonItem->data(GROUP_NAME_KEY).toInt());
    //报警设置
    common_st.sAlarm.bAlarm = ui->m_AlarmckBox->isChecked();
    common_st.sAlarm.nType = ui->m_AlarmcbBox->currentIndex();
    if(0 == ui->m_AlarmcbBox->currentIndex())
    {
        common_st.sAlarm.nMin = ui->m_AlarmMinspBox->text();
        common_st.sAlarm.nMax = ui->m_AlarmMaxspBox->text();
    }
    else
    {
        if(! pwnd->IsAddressCheckRight(Max_Address_Keyboard,tr("上限地址"),ui->m_AddressMaxlineEdit,1))
        {
            ui->m_AddressMaxlineEdit->setFocus();
            return false;
        }
        common_st.sAlarm.nMaxaddr = Max_Address_Keyboard;

        if(! pwnd->IsAddressCheckRight(Min_Address_Keyboard,tr("下限地址"),ui->m_AddressMinlineEdit,1))
        {
            ui->m_AddressMinlineEdit->setFocus();
            return false;
        }
        common_st.sAlarm.nMinaddr = Min_Address_Keyboard;

        common_st.sAlarm.nMin = ui->m_AddressMinlineEdit->text();
        common_st.sAlarm.nMax = ui->m_AddressMaxlineEdit->text();
    }
    common_st.sAlarm.nTextColor = pwnd->ColorTOString(ui->m_Alarmshowcolorbtn->palette().background().color());
    common_st.sAlarm.nDesignColor = pwnd->ColorTOString(ui->m_Alarmshapecolorbtn->palette().background().color());
    common_st.nCircle = circle;

    common_st.nPointType = ui->m_PointTypecbBox->currentIndex();
    return true;
}

void QChartCmColor::on_m_Alarmshowcolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_Alarmshowcolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setAlarmShowBtnColor(const QColor &)));
}

void QChartCmColor::on_m_Alarmshapecolorbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_Alarmshapecolorbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setAlarmShapeBtnColor(const QColor &)));
}

void QChartCmColor::setAlarmShowBtnColor(const QColor &mColor)//设置报警显示颜色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_Alarmshowcolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}
void QChartCmColor::setAlarmShapeBtnColor(const QColor &mColor)//设置报警图案颜色
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_Alarmshapecolorbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QChartCmColor::on_m_AlarmckBox_clicked()
{
    if(ui->m_AlarmckBox->isChecked())
    {
        ui->m_AlarmgroupBox->setEnabled(true);
    }
    else
    {
        ui->m_AlarmgroupBox->setEnabled(false);
    }
}

void QChartCmColor::on_m_AddressMin_EntryBtn_clicked()
{
    QString addrStr = ui->m_AddressMinlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(Min_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_AddressMinlineEdit->setText(Min_Address_Keyboard.sShowAddr);
    }
}

void QChartCmColor::on_m_AddressMax_EntryBtn_clicked()
{
    QString addrStr = ui->m_AddressMaxlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(Max_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_AddressMaxlineEdit->setText(Max_Address_Keyboard.sShowAddr);
    }
}

void QChartCmColor::on_m_AlarmcbBox_currentIndexChanged(int index)
{
    if(0 == index)
    {
        ui->m_AddressMinlineEdit->hide();
        ui->m_AddressMaxlineEdit->hide();
        ui->m_AddressMax_EntryBtn->hide();
        ui->m_AddressMin_EntryBtn->hide();
        ui->m_AlarmMaxspBox->show();
        ui->m_AlarmMinspBox->show();
    }
    else
    {
        ui->m_AddressMinlineEdit->show();
        ui->m_AddressMaxlineEdit->show();
        ui->m_AddressMax_EntryBtn->show();
        ui->m_AddressMin_EntryBtn->show();
        ui->m_AlarmMaxspBox->hide();
        ui->m_AlarmMinspBox->hide();
    }
}

void QChartCmColor::onDrawCirclePoint(ChartItem **pGroupItem,CIRCLE_TYPE circle,int index)
{
    int nPointType = 1;
    emit onGetPointType(nPointType);
    if(0 == nPointType || 2 == m_nLoadShapeType)//半圆不画指针，圆只有要求画指针才画
    {
        return;
    }
    int nWidth = 90;             //圆的宽度
    int nHeight = 90;            //圆的高度
    QVector <QPoint>mAngle;
    QPoint p1,p2,p3,p4;
    int nPointerTop = 10; //指针top坐标

    bool bShow = false;
    emit onGetShowValue(bShow);
    if(bShow)//显示圆刻度值
    {
       nWidth = 60;
       nHeight = 60;
    }

    short nStartAngle = 0;   //圆形图的刻度开始角度
    short nSpan = 360;
    if(3 == m_nLoadShapeType)
    {
        emit onGetStartAngle(nStartAngle,nSpan);
    }

    double mConst = 3.1415926;        //常量
    int nType = ui->m_PointTypecbBox->currentIndex();
    if(0 == nType)//细直线
    {
        int mLineX = nWidth/2;
        int mLineY = nPointerTop;

        QPainterPath mPath;           //生成线的path
        mPath.moveTo(nWidth/2,nHeight/2); //设置直线的起点
        mPath.lineTo(mLineX,mLineY);

        QLineItem *pLinePointer = new QLineItem(mPath);   //画细直线指针
        pLinePointer->setLineColor(ui->m_showcolorbtn->palette().background().color());      //设置直线颜色
        //pLinePointer->setLineWidth(1);                    //设置粗直线指针
        pLinePointer->setZValue(6);
        pLinePointer->SetName("Pointer");                 //设置名称
        pLinePointer->setTransformOriginPoint(nWidth/2,nHeight/2);
        pLinePointer->setRotation(nStartAngle);
        (*pGroupItem)->addToGroup(pLinePointer);
    }
    else if(1 == nType)//粗直线
    {
        int mLineX = nWidth/2;
        int mLineY = 10;

        QPainterPath mPath;           //生成线的path
        mPath.moveTo(nWidth/2,nHeight/2); //设置直线的起点
        mPath.lineTo(mLineX,mLineY);

        QLineItem *pLinePointer = new QLineItem(mPath);   //画细直线指针
        pLinePointer->setLineColor(ui->m_showcolorbtn->palette().background().color());      //设置直线颜色
        pLinePointer->setLineWidth(3);                    //设置粗直线指针
        pLinePointer->setZValue(6);
        pLinePointer->SetName("Pointer");                 //设置名称
        pLinePointer->setTransformOriginPoint(nWidth/2,nHeight/2);
        pLinePointer->setRotation(nStartAngle);
        (*pGroupItem)->addToGroup(pLinePointer);
    }
    else if(2 == nType)
    {
        p1.setX(nWidth/2);
        p1.setY(nHeight/2);

        p2.setX(nWidth/2-3);
        p2.setY(nHeight/2-8);

        p3.setX(nWidth/2);
        p3.setY(nPointerTop);

        p4.setX(nWidth/2+3);
        p4.setY(nHeight/2-8);

        mAngle.append(p1);
        mAngle.append(p2);
        mAngle.append(p3);
        mAngle.append(p4);
        QPolygonF mAnglePoly(mAngle);
        QPolygonItem *pPolyPointer = new QPolygonItem(mAnglePoly);   //画菱形指针
        pPolyPointer->setLineType(0);
        pPolyPointer->setBackColor(ui->m_showcolorbtn->palette().background().color());
        pPolyPointer->setZValue(3);                       //设置层次
        pPolyPointer->SetName("Pointer");                 //设置名称
        pPolyPointer->setTransformOriginPoint(nWidth/2,nHeight/2);
        pPolyPointer->setRotation(nStartAngle);
        (*pGroupItem)->addToGroup(pPolyPointer);
    }
    else if(3 == nType)
    {
        p1.setX(nWidth/2-2);
        p1.setY(nHeight/2);

        p2.setX(nWidth/2);
        p2.setY(nPointerTop);

        p3.setX(nWidth/2+2);
        p3.setY(nHeight/2);

        mAngle.append(p1);
        mAngle.append(p2);
        mAngle.append(p3);
        QPolygonF mAnglePoly(mAngle);
        QPolygonItem *pPolyPointer = new QPolygonItem(mAnglePoly);   //画菱形指针
        pPolyPointer->setLineType(0);
        pPolyPointer->setBackColor(ui->m_showcolorbtn->palette().background().color());
        pPolyPointer->setZValue(3);                       //设置层次
        pPolyPointer->SetName("Pointer");                 //设置名称
        pPolyPointer->setTransformOriginPoint(nWidth/2,nHeight/2);
        pPolyPointer->setRotation(nStartAngle);
        (*pGroupItem)->addToGroup(pPolyPointer);
    }
}

void QChartCmColor::drawCenterCircle(bool bCircle, int nRadiu)
{
    if(bCircle)
    {
        circle.num = 1;
    }
    else
    {
        circle.num = 0;
    }
    circle.nRadiu = nRadiu;
    reDrawBar();
}

QGraphicsItem *QChartCmColor::getItemFromFile(const int nIndex,QString sPath)
{
    QGraphicsItem *pNewItem = NULL;

    SamDrawScene *pSvene = NULL;
    DrawItemToScene GroupFunction;
    QList <QGraphicsItem*> listItem;
    QVector <SamDrawScene *> vScene;
    vScene.clear();
    QFile file(sPath);
    if(!file.open(QIODevice::ReadOnly))
    {
        return NULL;
    }
    QDataStream openData(&file);
    int sceneSize = 0;
    openData >> sceneSize;
    for(int i =0; i< sceneSize; i++)
    {
        pSvene = new SamDrawScene();
        //openData >> pSvene;
        pSvene->load(openData,pSvene);
        vScene.push_back(pSvene);
    }
    //listItem = pSvene->TopItems();
    listItem = vScene.at(m_nLoadShapeType)->TopItems();
    foreach (QGraphicsItem * pItem, listItem)
    {
        int index = pItem->data(GROUP_TYPE_KEY).toInt();
        if (index == nIndex)//四种形状图形第一个默认图形的名称
        {
            GroupFunction.CopyItemForChart(&pNewItem,pItem);
            break;
        }
    }
    file.close();
    return pNewItem;
}

void QChartCmColor::setdataRange(double dMax, double dMin,int type)
{
    QIntValidator* aIntValidator = new QIntValidator(this);
    DoubleValidator *aDoubleValidator = new DoubleValidator(this);
    aDoubleValidator->setNotation(QDoubleValidator::StandardNotation);

    if(0 == type)
    {
        aDoubleValidator->setRange(dMin,dMax,4);
        ui->m_AlarmMinspBox->setValidator(aDoubleValidator);
        ui->m_AlarmMaxspBox->setValidator(aDoubleValidator);
    }
    else
    {
        aDoubleValidator->setRange(dMin, dMax,0);
        ui->m_AlarmMinspBox->setValidator(aDoubleValidator);
        ui->m_AlarmMaxspBox->setValidator(aDoubleValidator);
    }

    if(ui->m_AlarmMaxspBox->text().isEmpty()
        || ui->m_AlarmMaxspBox->text().toDouble() > dMax
                || ui->m_AlarmMaxspBox->text().toDouble() < dMin)
    {
       ui->m_AlarmMaxspBox->setText(QString::number(dMax,'g',10));
    }
    if(ui->m_AlarmMinspBox->text().isEmpty()
        || ui->m_AlarmMinspBox->text().toDouble() > dMax
                || ui->m_AlarmMinspBox->text().toDouble() < dMin)
    {
        ui->m_AlarmMinspBox->setText(QString::number(dMin,'g',10));
    }
}
/***************************************************************
 *函数名称：GetText
 *函数功能：获取柱状图刻度值
 *参数含义：Min:最小值  Max:最大值 nPointNum：小数点位数   nMain：刻度数 nIndex:第几条刻度
 *返回值:  QString 刻度值字符串
 *编辑作者：
 *编辑日期：2012.11.06
 **************************************************************/
QString QChartCmColor::GetText(int nIndex,double Min, double Max,int nMain)
{
    double mValue = (Max - Min) / (nMain - 1);
    double dVal = 0;
    QString sText = "";
    int nPointNum = 0;

    dVal = Min + mValue*nIndex;
    if(nIndex == nMain-1)
        dVal = Max;


    if(dVal == -0)
        dVal = 0;
    sText.sprintf("%.0f", dVal);
    QString sTemp = "";
    if(nPointNum != 0)
    {
        sTemp = sText.left(1);
        if(sTemp == "-") //是负数的时候
        {
            sTemp = sText.right(sText.length()-1); //取除去负号的数据
            while(sTemp.length()-nPointNum <= 0)
                  sTemp = "0"+sTemp;
              sTemp = sTemp.insert(sTemp.length()-nPointNum,".");
              sText = "-"+sTemp;
        }
        else
        {
               while(sText.length()-nPointNum <= 0)
                     sText = "0"+sText;
                 sText = sText.insert(sText.length()-nPointNum,".");
        }
    }
    return sText;
}

void QChartCmColor::on_m_PointTypecbBox_currentIndexChanged(int index)
{
    if(bInitFlag)
    {
        reDrawBar();
    }
}

void QChartCmColor::enablePointType(bool bable)
{
    if(bable)
    {
        ui->m_PointTypecbBox->setEnabled(true);
    }
    else
    {
        ui->m_PointTypecbBox->setEnabled(false);
    }
}
