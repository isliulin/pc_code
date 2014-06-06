#include "qchartmeter.h"
#include "ui_qchartmeter.h"

extern MainWindow *pwnd;
QChartMeter::QChartMeter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QChartMeter)
{
    nInitFlag = false;
    ui->setupUi(this);
    ui->Monitor_Address->setText("LW0");
    pScene = new QGraphicsScene(this);
    ui->m_MeterButton_2->setEnabled(false);
}

QChartMeter::~QChartMeter()
{

    delete ui;
}

void QChartMeter::Init(ChartItem *pItem)
{
    if(pItem)
    {
        meter.shapeName = pItem->data(GROUP_NAME_KEY).toString();

        //初始化一般页面控件属性

        meter.nMeterType = 0;//仪表类型 先写死
        meter.nPointType = 1;//写死、仪表指针类型
        if(TO_RIGHT_ROTATE == pItem->meter_st.eDirection)
        {
            meter.nDirection = 0;//指针方向
        }
        else
        {
            meter.nDirection = 1;
        }
        if(pItem->meter_st.nScaleMark)
        {
            meter.nSubScal = pItem->meter_st.nSubScale;  //次刻度数
        }
        else
        {
            meter.nSubScal = 0;  //次刻度数
        }
        ui->m_TransparentspBox->setValue(pItem->meter_st.nTransparent);

        ui->m_checkBox_showFrame->setChecked(pItem->meter_st.bShowFrame);

        meter.nMainScal = pItem->meter_st.nMainScale; //主刻度数
        meter.dMax = pItem->meter_st.eShowMax;
        meter.dMin = pItem->meter_st.eShowMin;//最大值
        meter.nstartAngle = pItem->meter_st.nstartAngle;
        meter.nSpanAngle = pItem->meter_st.nSpanAngle;
        meter.nPointStartAngle = pItem->meter_st.nPointStartAngle;
        meter.nPointSpanAngel = pItem->meter_st.nPointSpanAngel;

        ui->Monitor_Address->setText(pItem->meter_st.addr.sShowAddr);
        ui->datatype_comboBox->setCurrentIndex(pItem->meter_st.eDataType);
        //ui->symbol_comboBox->setCurrentIndex(pItem->meter_st.nSourceMark);
        ui->rang_comboBox->setCurrentIndex(pItem->meter_st.nSourceRang);
        on_rang_comboBox_currentIndexChanged(pItem->meter_st.nSourceRang);
        if(0 == pItem->meter_st.nSourceRang)
        {
            ui->min_spinBox->setText(pItem->meter_st.eSourceMin);
            ui->max_spinBox->setText(pItem->meter_st.eSourceMax);
        }
        else
        {
            ui->min_spinBox->setText("0");
            ui->max_spinBox->setText("100");
            ui->m_sMinlineEdit->setText(pItem->meter_st.addrSourceMin.sShowAddr);
            ui->m_sMaxlineEdit->setText(pItem->meter_st.addrSourceMax.sShowAddr);
        }
        //ui->symbol_checkBox->setChecked(pItem->meter_st.bShowMark);
        ui->min_numEdit->setText(QString::number(pItem->meter_st.eShowMin,'g',10));
        ui->max_numEdit->setText(QString::number(pItem->meter_st.eShowMax,'g',10));
        if(TO_RIGHT_ROTATE == pItem->meter_st.eDirection)
        {
           ui->direction_comboBox->setCurrentIndex(0);
        }
        else
        {
            ui->direction_comboBox->setCurrentIndex(1);
        }
        meter.sPointColor = pItem->meter_st.nTextColor;
        meter.sBackColor = pItem->meter_st.nDesignColor;
        meter.sCaleColor = pItem->meter_st.nScaleColor;

        pChartItem = OnDrawMeter(pScene,meter,0,10);
        pChartItem->setData(GROUP_NAME_KEY,QVariant(meter.shapeName));
        pOldItem = pChartItem;
        pScene->addItem(pOldItem);
        pBaseItem = new QGroupItem(pOldItem);
    }
    else
    {
        //初始化控件属性
        ui->min_numEdit->setText("0");
        ui->max_numEdit->setText("100");
        ui->min_spinBox->setText("0");
        ui->max_spinBox->setText("100");
        on_rang_comboBox_currentIndexChanged(0);
        nMeterType = 0;  //仪表类型 0--半圆向上，1--全圆向上，2--全圆向下，3--四分之三圆向上
        nPointType = 1;  //写死、仪表指针类型,0--细直线，1--粗直线，2--菱形，3--三角形
        nDirection = 0;  //方向,0--顺时针，1--逆时针
        nSubScal = 2;    //次刻度数
        nMainScal = 4;    //主刻度数
        dMax = 100;
        dMin = 0;

        meter.nMeterType = 0;//仪表类型 先写死
        meter.nPointType = 1;//写死、仪表指针类型
        meter.nDirection = 0;//指针方向
        meter.nSubScal = 2;  //次刻度数
        meter.nMainScal = 4; //主刻度数
        meter.dMax = 100;
        meter.dMin = 0;//最大值
        meter.nPointStartAngle = 90;
        meter.nPointSpanAngel = 360;
        meter.nstartAngle = 0;
        meter.nSpanAngle = 360;
        meter.shapeName = "001";
        meter.sPointColor = pwnd->ColorTOString(QColor(255,0,0));
        meter.sBackColor = pwnd->ColorTOString(QColor(0,255,255));
        meter.sCaleColor = pwnd->ColorTOString(QColor(255,0,0));

        pChartItem = OnDrawMeter(pScene,meter,0,10);
        pChartItem->setData(GROUP_NAME_KEY,QVariant(meter.shapeName));
        pScene->addItem(pChartItem);
        pOldItem = pChartItem;
        pBaseItem = new QGroupItem(pOldItem);
//        pBaseItem->SetWidth(100);
//        pBaseItem->SetHeigth(100);

        sPointColor = pwnd->ColorTOString(QColor(255,0,0));
        sBackColor = pwnd->ColorTOString(QColor(0,255,255));
        ui->direction_comboBox->setCurrentIndex(0);
        ui->datatype_comboBox->setCurrentIndex(1);
    }
    nInitFlag = true;
    on_datatype_comboBox_currentIndexChanged(ui->datatype_comboBox->currentIndex());
}


void QChartMeter::OnReDrawMeter()
{
    QPointF oldpos(0,0);
    oldpos = pChartItem->sceneBoundingRect().topLeft();
    if(pOldItem)
    {
        pScene->removeItem(pOldItem);
    }
    pChartItem = OnDrawMeter(pScene,meter,0,10);
    pChartItem->setData(GROUP_NAME_KEY,QVariant(meter.shapeName));
    pScene->addItem(pChartItem);
    QPointF newpos = pChartItem->boundingRect().topLeft();
    //pChartItem->setPos(oldpos-newpos);
    pOldItem = pChartItem;
    pBaseItem = new QGroupItem(pOldItem);

}
void QChartMeter::on_m_CommonButton_2_clicked()
{
    emit commonclick();
}

void QChartMeter::on_Monitor_Address_EntryBtn_clicked()
{
    QString addrStr = ui->Monitor_Address->text();
    AddressInputDialog addressintputdlg_writeaddress(Monitor_Address_Keyboard,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->Monitor_Address->setText(Monitor_Address_Keyboard.sShowAddr);
    }
}

void QChartMeter::on_comboBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0://数据类型为浮点和bin类型时菜可以设置符号
    case 2:
    case 4:
        //ui->symbol_checkBox->setEnabled(true);;
        break;
    case 1:
    case 3:
        //ui->symbol_checkBox->setEnabled(false);
        break;
    default:
        break;
    }
}

void QChartMeter::on_symbol_checkBox_clicked()
{
}
void QChartMeter::on_min_numEdit_lostFocus()
{
    if(!nInitFlag)
    {
        return;
    }
    QString sMin = ui->min_numEdit->text();
    meter.dMin = sMin.toDouble();
    dMin = sMin.toDouble();
    OnReDrawMeter();
}

void QChartMeter::on_max_numEdit_lostFocus()
{
    if(!nInitFlag)
    {
        return;
    }

    QString sMax = ui->max_numEdit->text();
    meter.dMax = sMax.toDouble();
    dMax = sMax.toDouble();
    OnReDrawMeter();
}

void QChartMeter::on_direction_comboBox_currentIndexChanged(int index)
{
    if(!nInitFlag)
    {
        return;
    }
    meter.nDirection = index;
    nDirection = index;
    meter.nDirection = index;
    OnReDrawMeter();
}

void QChartMeter::OnSetMeterProperty()
{
    int mMeterType = nMeterType; //仪表类型 0--半圆向上，1--全圆向上，2--全圆向下，3--四分之三圆向上
    int mMainScal = nMainScal; //主刻度
    int mSubScal = nSubScal;   //次刻度
    int nSunLineCount = 0;                   //次刻度总数
    int i = 0;
    //QString sColor = nColor;
    QString sName = "";
    QString str = "";
    //bool bFlag = false;

//    pBaseItem->SetPropertyValue("Pointer.LineColor",QVariant(sPointColor));//更新指针颜色
//    pBaseItem->SetPropertyValue("mMeterCircle.BackColor",QVariant(sBackColor));//更新背景颜色

    /**********************************************************
     *以下是刻度页面设置颜色操作
     *********************************************************/
    //if(pQMeterScale->bIfSelectColor)
    /*{
        if(mMeterType == 1 || mMeterType == 2)
            mMainScal -- ;
        for(i = 0;i < mMainScal; i++)
        {
            str = QString("%1").arg(i);
            sName = "MeterTxt"+str;
            sName = sName + ".FontColor";
            pBaseItem->SetPropertyValue(sName,QVariant(sColor));
        }
        nSunLineCount = mSubScal*(nMainScal - 1);//次刻度线总数
        for(i = 0; i < nSunLineCount; i++)  //画次刻度
        {
            if( i%mSubScal != 0)
            {
                str = QString("%1").arg(i);
                sName = "SubLineScal"+str;
                sName = sName + ".LineColor";
                pBaseItem->SetPropertyValue(sName,QVariant(sColor));
            }
        }
    }*/

    /**********************************************************
     *以下是刻度页面是否设置轴操作
     *********************************************************/
    /*if(pQMeterScale->bIfAxis) //是否显示轴
    {
        sName = "mMeterCircle.LineType";
        pQMeterGen->pBaseItem->SetPropertyValue(sName,QVariant(1));
    }
    else
    {
        sName = "mMeterCircle.LineType";
        pQMeterGen->pBaseItem->SetPropertyValue(sName,QVariant(0));
    }

    if( !pQMeterScale->bIfShow)
    {
        sName = "mMeterCircle.LineType";
        pQMeterGen->pBaseItem->SetPropertyValue(sName,QVariant(0));
    }/*
    /**********************************************************
     *以下是刻度页面是否显现
     *********************************************************/
    /*if(mMeterType == 1 || mMeterType == 2)
        mMainScal = pQMeterScale->nMainScal - 1 ;
    for(i = 0;i < mMainScal; i++)
    {
        str = QString("%1").arg(i);
        sName = "MeterTxt"+str;
        sName = sName + ".Visible";
        pQMeterGen->pBaseItem->SetPropertyValue(sName,QVariant(pQMeterScale->bIfShow));

        sName = "MainLineScal"+str;
        sName = sName + ".Visible";
        pQMeterGen->pBaseItem->SetPropertyValue(sName,QVariant(pQMeterScale->bIfShow));
    }
    nSunLineCount = mSubScal*(pQMeterScale->nMainScal - 1);//次刻度线总数
    for(i = 0; i < nSunLineCount; i++)  //画次刻度
    {
        if( i%mSubScal != 0)
        {
            str = QString("%1").arg(i);
            sName = "SubLineScal"+str;
            sName = sName + ".Visible";
            pQMeterGen->pBaseItem->SetPropertyValue(sName,QVariant(pQMeterScale->bIfShow));
        }
    }*/

    /**********************************************************
     *以下是刻度页面是否显示刻度标示
     *********************************************************/
    /*if( !pQMeterScale->bIfShow)
        bFlag = false;
    else
        bFlag = pQMeterScale->bScaleMark;
    for(i = 0;i < mMainScal; i++)
    {
        str = QString("%1").arg(i);
        sName = "MeterTxt"+str;
        sName = sName + ".Visible";
        pQMeterGen->pBaseItem->SetPropertyValue(sName,QVariant(bFlag));
    }*/
}

bool QChartMeter::MeterGenSave(struct METER_INFORMATION &meter_st)
{
    QString sTmp;
    int nState;

    if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("写入地址"),ui->Monitor_Address,1))
    {
        ui->Monitor_Address->setFocus();
        return false;
    }

    meter_st.addr = Monitor_Address_Keyboard;

    if(1 == ui->rang_comboBox->currentIndex())
    {
        if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("最小值地址"),ui->m_sMinlineEdit,1))
        {
            ui->m_sMinlineEdit->setFocus();
            return false;
        }

        meter_st.addrSourceMin = Monitor_Address_Keyboard;

        if(! pwnd->IsAddressCheckRight(Monitor_Address_Keyboard,tr("最大值地址"),ui->m_sMaxlineEdit,1))
        {
            ui->m_sMaxlineEdit->setFocus();
            return false;
        }

        meter_st.addrSourceMax = Monitor_Address_Keyboard;
    }

    sTmp=ui->Monitor_Address->text();//控制字地址
    meter_st.mAddress = sTmp;

    sTmp.clear();                    //数据类型
    nState = ui->datatype_comboBox->currentIndex();
    meter_st.eDataType = nState;

    sTmp.clear();                    //指定源范围
    nState = ui->rang_comboBox->currentIndex();
    meter_st.nSourceRang = nState;

    //sTmp.clear();                     //源范围显示+/-
    //nState = ui->symbol_comboBox->currentIndex();
    //meter_st.nSourceMark = nState;

    if(0 == ui->rang_comboBox->currentIndex())
    {
        meter_st.eSourceMin = ui->min_spinBox->text();//源范围最小值
        meter_st.eSourceMax = ui->max_spinBox->text();//源范围最大值
    }
    else
    {
        meter_st.eSourceMin = ui->m_sMinlineEdit->text();
        meter_st.eSourceMax = ui->m_sMaxlineEdit->text();
    }

    //meter_st.bShowMark = ui->symbol_checkBox->isChecked();//显示符号+、-

    sTmp.clear();                    //显示范围最小值
    sTmp = ui->min_numEdit->text();
    meter_st.eShowMin = sTmp.toDouble();

    sTmp.clear();                    //显示范围最大值
    sTmp = ui->max_numEdit->text();
    meter_st.eShowMax = sTmp.toDouble();

    sTmp.clear();
    nState = ui->direction_comboBox->currentIndex();
    if(0 == nState)
    {
       meter_st.eDirection = TO_RIGHT_ROTATE;
    }
    else
    {
        meter_st.eDirection = TO_LEFT_ROTATE;
    }
    meter_st.nstartAngle = meter.nstartAngle;
    meter_st.nSpanAngle = meter.nSpanAngle;
    meter_st.nPointStartAngle = meter.nPointStartAngle;
    meter_st.nPointSpanAngel  = meter.nPointSpanAngel;
    meter_st.nTransparent  = ui->m_TransparentspBox->value();
    meter_st.bShowFrame    = ui->m_checkBox_showFrame->isChecked();
    return true;
}

/****************************************************************************

 ****************************************************************************/
ChartItem* QChartMeter::OnDrawMeter(QGraphicsScene *pScene,METER_STRU meter, int nPointCount,int nFontSize)
{
    int nWidth = 60;      //圆的宽度
    int nHeight = 60;     //圆的高度

    bool bShow = false;
    emit onGetShowValue(bShow);
    if(bShow)//显示仪表刻度值
    {
       nWidth = 60;
       nHeight = 60;
    }

    ChartItem *pItem = new ChartItem;
    QItemGroup *pGroup = new QItemGroup;

    QRectF mRect(QPoint(0,0),QSize(nWidth,nHeight));    //设置大小
    QElipseItem *pCircle = new QElipseItem(mRect);      //绘制一个圆
    pCircle->SetName("mMeterCircle");                   //设置圆的名称

    pCircle->SetStartAngle(meter.nstartAngle);                  //设置开始角度
    pCircle->SetSpanAngle(meter.nSpanAngle);

    pCircle->SetBackColor(pwnd->StringTOColor(meter.sBackColor));           //设置背景色
    pCircle->setZValue(1);                              //设置层次
    pCircle->SetAlpha(ui->m_TransparentspBox->value());
    pCircle->SetLineColor(pwnd->StringTOColor(meter.sCaleColor));
    if(ui->m_checkBox_showFrame->isChecked() == false)//wxy 显示边框
    {
         pCircle->SetLineType(0);
    }

    QRectF mBaseRect(QPoint(nWidth/2-2,nHeight/2-2),QSize(4,4)); //设置针座大小
    QElipseItem *pBaseCircle = new QElipseItem(mBaseRect);//绘制针座
    pBaseCircle->SetBackColor(pwnd->StringTOColor(meter.sCaleColor));             //设置针座颜色
    pBaseCircle->setZValue(2);                            //设置针座的层次
    pBaseCircle->SetLineType(0);                          //设置线条样式为透明
    pBaseCircle->SetName("mPointerBase");                 //设置针座名称
    pGroup->addToGroup(pBaseCircle);                       //添加到组

    pItem->addToGroup(pCircle);                            //添加到组
    OnDrawPointer(pGroup,meter,bShow);
    OnDrawScal(pGroup,meter,nPointCount,nFontSize,bShow);
    pGroup->setZValue(3);

    pItem->addToGroup(pGroup);
    //pScene->addItem(pItem);
    return pItem;
}

/****************************************************************************

 ****************************************************************************/
void QChartMeter::OnDrawPointer(QGraphicsItemGroup *pGroup,METER_STRU meter,bool bShow)
{
    double nWidth = 60.0;             //圆的宽度
    double nHeight = 60.0;            //圆的高度
    if(bShow)
    {
        nWidth = 60.0;             //圆的宽度
        nHeight = 60.0;            //圆的高度
    }
    QVector <QPoint>mAngle;
    QPoint p1,p2,p3,p4;
    int nPointerTop = 5; //指针top坐标

    int nType = 0;
    emit onGetPointType(nType);
    if(0 == nType)//细直线
    {
        int mLineX = nWidth/2;
        int mLineY = nPointerTop;

        QPainterPath mPath;           //生成线的path
        mPath.moveTo(nWidth/2,nHeight/2); //设置直线的起点
        mPath.lineTo(mLineX,mLineY);

        QLineItem *pLinePointer = new QLineItem(mPath);   //画细直线指针
        pLinePointer->setLineColor(pwnd->StringTOColor(meter.sPointColor));      //设置直线颜色
        //pLinePointer->setLineWidth(1);                    //设置粗直线指针
        pLinePointer->setZValue(6);
        pLinePointer->SetName("Pointer");
        if(0 == meter.nDirection)
        {
            pLinePointer->setTransformOriginPoint(nWidth/2,nHeight/2);
            pLinePointer->setRotation(meter.nPointStartAngle - 90);
        }
        else
        {
            pLinePointer->setTransformOriginPoint(nWidth/2,nHeight/2);
            pLinePointer->setRotation(meter.nPointSpanAngel + meter.nPointStartAngle - 90);
        }
        pGroup->addToGroup(pLinePointer);
    }
    else if(1 == nType)//粗直线
    {
        int mLineX = nWidth/2;
        int mLineY = 10;

        QPainterPath mPath;           //生成线的path
        mPath.moveTo(nWidth/2,nHeight/2); //设置直线的起点
        mPath.lineTo(mLineX,mLineY);

        QLineItem *pLinePointer = new QLineItem(mPath);   //画细直线指针
        pLinePointer->setLineColor(pwnd->StringTOColor(meter.sPointColor));      //设置直线颜色
        pLinePointer->setLineWidth(3);                    //设置粗直线指针
        pLinePointer->setZValue(6);
        pLinePointer->SetName("Pointer");                 //设置名称
        if(0 == meter.nDirection)
        {
            pLinePointer->setTransformOriginPoint(nWidth/2,nHeight/2);
            pLinePointer->setRotation(meter.nPointStartAngle - 90);
        }
        else
        {
            pLinePointer->setTransformOriginPoint(nWidth/2,nHeight/2);
            pLinePointer->setRotation(meter.nPointSpanAngel + meter.nPointStartAngle - 90);
        }
        pGroup->addToGroup(pLinePointer);
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
        pPolyPointer->setBackColor(pwnd->StringTOColor(meter.sPointColor));
        pPolyPointer->setZValue(3);                       //设置层次
        pPolyPointer->SetName("Pointer");                 //设置名称
        if(0 == meter.nDirection)
        {
            pPolyPointer->setTransformOriginPoint(nWidth/2,nHeight/2);
            pPolyPointer->setRotation(meter.nPointStartAngle - 90);
        }
        else
        {
            pPolyPointer->setTransformOriginPoint(nWidth/2,nHeight/2);
            pPolyPointer->setRotation(meter.nPointSpanAngel + meter.nPointStartAngle - 90);
        }
        pGroup->addToGroup(pPolyPointer);
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
        pPolyPointer->setBackColor(pwnd->StringTOColor(meter.sPointColor));
        pPolyPointer->setZValue(3);                       //设置层次
        pPolyPointer->SetName("Pointer");                 //设置名称
        if(0 == meter.nDirection)
        {
            pPolyPointer->setTransformOriginPoint(nWidth/2,nHeight/2);
            pPolyPointer->setRotation(meter.nPointStartAngle - 90);
        }
        else
        {
            pPolyPointer->setTransformOriginPoint(nWidth/2,nHeight/2);
            pPolyPointer->setRotation(meter.nPointSpanAngel + meter.nPointStartAngle - 90);
        }
        pGroup->addToGroup(pPolyPointer);
    }
}
/****************************************************************************

 ****************************************************************************/
void QChartMeter::OnDrawScal(QGraphicsItemGroup *pGroup,METER_STRU meter, int nPointCount,
                               int nFontSize,bool bShow)
{
    QItemGroup *pTextGroup = new QItemGroup;
    QLineItem *pLineScal;
    int nWidth = 90;                 //圆的宽度
    int nHeight = 90;                //圆的高度
    if(bShow)
    {
        nWidth = 60;                 //圆的宽度
        nHeight = 60;                //圆的高度
    }
    else
    {
        return;
    }
    double mMoveX = 0;                //主刻度X起始点
    double mMoveY = 0;                //主刻度Y起始点
    double mLineX = 0;                //主刻度X起始点
    double mLineY = 0;                //主刻度Y起始点
    double mMainAngle = 0;            //主刻度偏转角度， 弧度制
    double mSubAngle = 0;             //次刻度偏转角度， 弧度制
    double mTextAngle = 0;            //文本偏转角度,   角度制
    double mConst = 3.1415926;        //常量
    int nMainScaleL = 6;              //主刻度的长度
    int nSubScaleL = nMainScaleL / 2; //次刻度长度
    int nSunLineCount = 0;            //次刻度线总数
    int nDrawMainScal = meter.nMainScal;    //主刻度数
    int nTextX = 0;
    int nTextY = 0;
    double mValue = 0;                //
    double dTotalAngle;               //仪表刻度跨的角度大小，角度制
    double dVal = 0;
    QString sText = "";
    int i = 0;
    QString sName = "";
    QRectF rect(QPointF(0,0), QSize(50,50));
    nDrawMainScal++;

    mValue = (meter.dMax - meter.dMin) / (nDrawMainScal - 1); //每刻度显示的数值大小

    dTotalAngle = ((meter.nPointSpanAngel) * mConst) / 180;
    mMainAngle = dTotalAngle / (nDrawMainScal - 1);
    double dRotation = meter.nPointSpanAngel / (nDrawMainScal - 1.0);
    mSubAngle = dTotalAngle / (meter.nSubScal*(nDrawMainScal - 1));
    mTextAngle = (meter.nPointSpanAngel) / (nDrawMainScal - 1);

    if(360 == (meter.nPointSpanAngel))
    {
        nDrawMainScal--;
    }

    double dMin = meter.dMin;
    double dMax = meter.dMax;
    double dValue = 0;
    if(360 == (meter.nPointSpanAngel))
    {
        dValue = (dMax - dMin)/(nDrawMainScal);
    }
    else
    {
        dValue = (dMax - dMin)/(nDrawMainScal - 1);
    }
    double dFirst = dMin;
    if(1 == meter.nDirection)
    {
        dFirst = dMax;
    }

    for(i = 0; i < nDrawMainScal; i++)  //画主刻度nMainScal
    {
        mMoveX = nWidth/2 - nWidth/2 * cos(mMainAngle*i + (meter.nPointStartAngle * mConst) / 180);
        mMoveY = nWidth/2 - nWidth/2 * sin(mMainAngle*i + (meter.nPointStartAngle * mConst) / 180);

        mLineX = nWidth/2 - (nWidth/2+nMainScaleL)*cos(mMainAngle*i + (meter.nPointStartAngle * mConst) / 180);
        mLineY = nHeight/2 - (nWidth/2+nMainScaleL)*sin(mMainAngle*i + (meter.nPointStartAngle * mConst) / 180);

        nTextX = (nWidth + 6)/2 - (nWidth + 6)/2 * cos(mMainAngle*i + (meter.nPointStartAngle * mConst) / 180);
        nTextY = (nWidth)/2 - (nWidth)/2 * sin(mMainAngle*i + (meter.nPointStartAngle * mConst) / 180);
        QPainterPath mPath;
        mPath.moveTo(mMoveX,mMoveY);             //画直线的起点
        mPath.lineTo(mLineX,mLineY);             //画直线的终点
        pLineScal = new QLineItem(mPath);        //画细直线
        pLineScal->setLineColor(pwnd->StringTOColor(meter.sCaleColor));  //设置直线颜色
        pLineScal->setZValue(4);                 //设置层次

        sName = QString("%1").arg(i);
        sName = "MainLineScal"+sName;
        pLineScal->SetName(sName);               //设置名称
        pGroup->addToGroup(pLineScal);           //添加到组

        //画文本
        //画仪表的刻度值
        if(bShow)//显示仪表刻度值
        {
            QString sText;//QString::number(dFirst);
            sText.sprintf("%.0f", dFirst);
            if(360 != (meter.nPointSpanAngel) && i == (nDrawMainScal -1))
            {
                if(0 == meter.nDirection)
                {
                    sText = QString::number(dMax);
                }
                else
                {
                    sText = QString::number(dMin);
                }
            }
            else if(360 == (meter.nPointSpanAngel))
            {
                if(1 == meter.nDirection && i == 0)
                {
                    sText = QString::number(dMin);
                }
            }
            rect.setTopLeft(QPointF(nWidth/2 - 10, -26));//离圆顶点24个坐标，宽高为20个坐标
            rect.setSize(QSize(20,20));
            QSimpleTextItem *pText = new QSimpleTextItem(rect,sText);

            pText->SetFontSize(8);
            pText->SetFontColor(pwnd->StringTOColor(meter.sCaleColor));
            pText->SetRectOutLine(false);
            pText->setTransformOriginPoint(nWidth/2,nHeight/2);
            pText->setRotation(dRotation*i + meter.nPointStartAngle - 90.0);
            QSimpleTextItem *pnew = pText->Clone();//暂时clone一个处理旋转后字符也旋转了的问题
            delete pText;
            pText = NULL;
            pTextGroup->addToGroup(pnew);
            if(0 == meter.nDirection)
            {
                dFirst =dMin + (i +1) * dValue;
            }
            else
            {
                dFirst = dMax - (i + 1) * dValue;
            }

        }
        /***********************画文本完毕**************************/
    }

    if(bShow)
    {
        pGroup->addToGroup(pTextGroup);           //添加到组
    }
    else
    {
        delete pTextGroup;
        pTextGroup = NULL;
    }

    nSunLineCount = meter.nSubScal*(nDrawMainScal - 1);//次刻度线总数
    if(360 == (meter.nPointSpanAngel))
    {
        nSunLineCount = meter.nSubScal*(nDrawMainScal);//次刻度线总数
    }
    for(i = 0; i < nSunLineCount; i++)  //画次刻度
    {
        if( i%(meter.nSubScal) != 0)
        {
            mMoveX = nWidth/2 - nWidth/2 * cos(mSubAngle*i + (meter.nPointStartAngle * mConst) / 180);
            mMoveY = nWidth/2 - nWidth/2 * sin(mSubAngle*i + (meter.nPointStartAngle * mConst) / 180);

            mLineX = nWidth/2 - (nWidth/2+nSubScaleL)*cos(mSubAngle*i + (meter.nPointStartAngle * mConst) / 180);
            mLineY = nHeight/2 - (nWidth/2+nSubScaleL)*sin(mSubAngle*i + (meter.nPointStartAngle * mConst) / 180);

            QPainterPath mPath;
            mPath.moveTo(mMoveX,mMoveY);             //画直线的起点
            mPath.lineTo(mLineX,mLineY);             //画直线的终点
            pLineScal = new QLineItem(mPath);        //画细直线
            pLineScal->setLineColor(pwnd->StringTOColor(meter.sCaleColor));  //设置直线颜色
            pLineScal->setZValue(4);                 //设置层次

            sName = QString("%1").arg(i);
            sName = "SubLineScal"+sName;
            pLineScal->SetName(sName);               //设置名称

            pGroup->addToGroup(pLineScal);
        }
    }
}



void QChartMeter::on_rang_comboBox_currentIndexChanged(int index)
{
    if(0 == index)
    {
        ui->m_sMinlineEdit->hide();
        ui->m_sMaxlineEdit->hide();
        ui->m_minAddress_EntryBtn->hide();
        ui->m_maxAddress_EntryBtn->hide();
        ui->min_spinBox->show();
        ui->max_spinBox->show();
    }
    else if(1 == index)
    {
        ui->m_sMinlineEdit->show();
        ui->m_sMaxlineEdit->show();
        ui->m_minAddress_EntryBtn->show();
        ui->m_maxAddress_EntryBtn->show();
        ui->min_spinBox->hide();
        ui->max_spinBox->hide();
    }
}

void QChartMeter::on_m_minAddress_EntryBtn_clicked()
{
    QString addrStr = ui->m_sMinlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(m_minAddress_EntryBtn,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_sMinlineEdit->setText(m_minAddress_EntryBtn.sShowAddr);
    }
}


void QChartMeter::on_m_maxAddress_EntryBtn_clicked()
{
    QString addrStr = ui->m_sMaxlineEdit->text();
    AddressInputDialog addressintputdlg_writeaddress(m_maxAddress_EntryBtn,addrStr,1,this);
    if(addressintputdlg_writeaddress.exec())
    {
        ui->m_sMaxlineEdit->setText(m_maxAddress_EntryBtn.sShowAddr);
    }
}

void QChartMeter::on_datatype_comboBox_currentIndexChanged(int index)
{
    if(!nInitFlag)
    {
        return;
    }
    double nMax = 100;
    double nMin = 0;
    int type  = 1;
    switch(index)
    {
    case 0://16位整数
        {
            nMin = -32768;
            nMax = 32767;
            break;
        }
        break;
    case 1://16位正整数
        {
            nMin = 0;
            nMax = 65535;
        }
        break;
    case 2://32位整数
        nMin = -2147483648L;
        nMax = 2147483647L;
        break;
    case 3://32位正整数
        nMin = 0;
        nMax = 4294967295UL;
        break;
    case 4://32位浮点数
        nMin = -2147483648L;
        nMax = 2147483647L;
        type = 0;
        break;
    default:
        return;
    }

    if(nMin > 0) nMin = -1*nMin;
    setdataRange(nMax, nMin,type);
    emit setRange(nMax, nMin, type);
}

void QChartMeter::setdataRange(double dMax, double dMin,int type)
{
    //QIntValidator* aIntValidator = new QIntValidator(this);
    DoubleValidator *aDoubleValidator = new DoubleValidator(this);
    aDoubleValidator->setNotation(QDoubleValidator::StandardNotation);

    if(0 == type)
    {
        aDoubleValidator->setRange(dMin,dMax,4);
        ui->min_spinBox->setValidator(aDoubleValidator);
        ui->max_spinBox->setValidator(aDoubleValidator);
        ui->min_numEdit->setValidator(aDoubleValidator);
        ui->max_numEdit->setValidator(aDoubleValidator);
    }
    else
    {
        aDoubleValidator->setRange(dMin, dMax,0);
        ui->min_spinBox->setValidator(aDoubleValidator);
        ui->max_spinBox->setValidator(aDoubleValidator);
        ui->min_numEdit->setValidator(aDoubleValidator);
        ui->max_numEdit->setValidator(aDoubleValidator);
    }

    if(ui->max_spinBox->text().isEmpty()
        || ui->max_spinBox->text().toDouble() > dMax
                || ui->max_spinBox->text().toDouble() < dMin)
    {
       ui->max_spinBox->setText(QString::number(dMax,'g',10));
    }
    if(ui->min_spinBox->text().isEmpty()
        || ui->min_spinBox->text().toDouble() > dMax
                || ui->min_spinBox->text().toDouble() < dMin)
    {
        ui->min_spinBox->setText(QString::number(dMin,'g',10));
    }

    if(ui->max_numEdit->text().isEmpty()
        || ui->max_numEdit->text().toDouble() > dMax
                || ui->max_numEdit->text().toDouble() < dMin)
    {
       ui->max_numEdit->setText(QString::number(dMax,'g',10));
    }
    if(ui->min_numEdit->text().isEmpty()
        || ui->min_numEdit->text().toDouble() > dMax
                || ui->min_numEdit->text().toDouble() < dMin)
    {
        ui->min_numEdit->setText(QString::number(dMin,'g',10));
    }
}

void QChartMeter::on_min_numEdit_textChanged(QString )
{
    if(!nInitFlag)
    {
        return;
    }
    if(ui->min_numEdit->text().toDouble() > ui->max_numEdit->text().toDouble())
    {
        return;
    }
    OnReDrawMeter();
}

void QChartMeter::on_max_numEdit_textChanged(QString )
{
    if(!nInitFlag)
    {
        return;
    }
    if(ui->min_numEdit->text().toDouble() > ui->max_numEdit->text().toDouble())
    {
        return;
    }
    OnReDrawMeter();
}

void QChartMeter::on_m_TransparentCKBox_clicked(bool checked)
{
    if(!nInitFlag)
    {
        return;
    }
    OnReDrawMeter();
}

void QChartMeter::on_m_TransparentspBox_valueChanged(int )
{
    if(!nInitFlag)
    {
        return;
    }
    OnReDrawMeter();
}

void QChartMeter::on_m_checkBox_showFrame_clicked(bool checked)
{
    if(!nInitFlag)
    {
        return;
    }
    OnReDrawMeter();
}
