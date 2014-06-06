#include "SliderDlg.h"
#include "view/qdrawgraphics.h"
#include "view/SliderItem.h"
#include  "Frame\MainWindow.h"
#include "Frame/ThingDlg/Slider.h"
extern MainWindow  *pwnd;


SliderDlg::SliderDlg()
{
//    slider=new Slider;
}

/***************************************************************
 *函数名称：DrawSlider
 *函数功能：画滑动模拟量开关图形函数
 *sList所含内容含义：
 *0：背景色
 *1：滑轨颜色
 *2：指标背景色
 *3：指标边框色
 *4：刻度位置  1--上；2--下；3--左；4--右
 *5：标示方向  0--向左（向上）；1--向右（向下）
 //刻度页面
 *6：是否显示
 *7：刻度字体颜色
 *8：主刻度
 *9：次刻度
 *10：是否显示轴
 *11：是否显示刻度标示
 *12：字体大小
 *13：最小值
 *14：最大值
 *15：小数位数
 *返回值：返回一个组合指针
 *edit by zqh
 *Date:2011-02-17
 **************************************************************/
SliderItem* SliderDlg::DrawSlider(SliderItem *slider)
{
    //以下是变量的定义
    QColor BackColor = pwnd->StringTOColor(slider->m_slider.rectColor);//背景色
    QColor LineColor = pwnd->StringTOColor(slider->m_slider.slideBarColor);//滑轨颜色
    QColor BkColor = pwnd->StringTOColor(slider->m_slider.fingerBackColor);  //指标背景色
    QColor FrmColor = pwnd->StringTOColor(slider->m_slider.fingerLineColor); //指标边框色

    int nPos = slider->m_slider.nPosition;     //刻度位置
    int nDirect = slider->m_slider.direction;  //标示方向
    bool bIfShow = slider->m_slider.isShowCalibration; //是否显示
    QColor mColor = pwnd->StringTOColor(slider->m_slider.nCalibrationColor); //刻度字体颜色
    int nMain = slider->m_slider.nMaxNumber;    // 主刻度
    int nSub = slider->m_slider.nMinNumber;     // 次刻度
    bool bIfShowZ = true;     // 是否显示轴
    bool bIfShowM = slider->m_slider.bShowText;     // 是否显示刻度标示
    int nFontSize = slider->m_slider.nTextSize;     //字体大小
    double Min = slider->m_slider.nCalibrationMin.toDouble();     //最小值
    double Max = slider->m_slider.nCalibrationMax.toDouble();     //最大值
    int nNum = slider->m_slider.nDecimalCount;       //小数位数

    double RectW = 120.0;  //背景矩形的宽度108.0
    int nRectH = 32;       //背景矩形的高度
    int nSpace = 10;        //滑轨偏离背景矩形边框的距离

    QPainterPath mPath;               //生成线的path
    double mMoveX = 0;                //主刻度X起始点
    double mLineY = 0;                //主刻度Y起始点
    SliderItem *pGroup = new SliderItem;

    QLineItem *pLine;
    int i = 0;
    double nLineW = RectW-2*nSpace;
    double MainSpace = nLineW/(nMain-1);           //主刻度间隔
    double SubSpace = nLineW/((nSub+1)*(nMain-1)); //次刻度间隔
    int ML = 10;                                  //主刻度线的长度
    int nVal = (nSub+1)*(nMain-1);

    QSimpleTextItem *pText;
    QRectItem *pFramRect;
    QLineItem *pMainLine;
    QPolygonItem *pPolyPointer;
    QLineItem *pZLine;

    QString sText = "";
    QRectF rect(QPointF(0,0), QSize(50,50));
    int nH = 0;
    int nL = 0;//80
    int nTop = 4; //边框到指标指尖的距离
    int nTextW = 0; //文本的宽度

    QVector <QPoint>mAngle;
    QPoint p1,p2,p3,p4,p5;

    //开始画背景矩形
    if(nPos == 1 || nPos == 2) //刻度位置  1--上；2--下；3--左；4--右
    {
        rect.setTopLeft(QPointF(nL,nH));
        rect.setSize(QSizeF(RectW,nRectH)); //绘制边框色矩形框
        mPath.moveTo(nL+nSpace,nH+nRectH/2);
        mPath.lineTo(nL+nSpace+RectW-2*nSpace,nH+nRectH/2);

    }
    else if(nPos == 3 || nPos == 4)
    {
        rect.setTopLeft(QPointF(nL,nH));
        rect.setSize(QSizeF(nRectH,RectW)); //绘制边框色矩形框
        mPath.moveTo(nL+nRectH/2,nH+nSpace);
        mPath.lineTo(nL+nRectH/2,nH+nSpace+nLineW);
    }

    pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(BackColor);
    pFramRect->SetLineType(0);
    pFramRect->SetName("mFramRect");
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->addToGroup(pFramRect);           //添加到组

    //绘制滑轨直线
    pMainLine = new QLineItem(mPath);        //画细直线
    pMainLine->setLineColor(LineColor);      //设置直线颜色
    pMainLine->SetName("MainLine");          //设置名称
    pMainLine->setLineWidth(3);
    pMainLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->addToGroup(pMainLine);           //添加到组

    //绘制指标
    if(nPos == 1)             //刻度的方向向上
    {
        if(nDirect == 0)      //文本标识的方向向左
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nSpace+nLineW); p1.setY(nH+nTop);
            p2.setX(nL+nSpace/2+nLineW);p2.setY(nH+nRectH/4);
            p3.setX(nL+nSpace/2+nLineW);p3.setY(nH+3*nRectH/4);
            p4.setX(nL+3*nSpace/2+nLineW);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2+nLineW);p5.setY(nH+nRectH/4);
        }
        else if(nDirect == 1) //文本标识的方向向右
        {
            p1.setX(nL+nSpace); p1.setY(nH+nTop);
            p2.setX(nL+nSpace/2);p2.setY(nH+nRectH/4);
            p3.setX(nL+nSpace/2);p3.setY(nH+3*nRectH/4);
            p4.setX(nL+3*nSpace/2);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2);p5.setY(nH+nRectH/4);
        }
    }
    else if(nPos == 2)        //刻度的方向向下
    {
        if(nDirect == 0)      //文本标识的方向向左
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nSpace/2+nLineW); p1.setY(nH+nRectH/4);
            p2.setX(nL+nSpace/2+nLineW);p2.setY(nH+3*nRectH/4);
            p3.setX(nL+nSpace+nLineW);p3.setY(nH+nRectH-nTop);
            p4.setX(nL+3*nSpace/2+nLineW);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2+nLineW);p5.setY(nH+nRectH/4);
        }
        else if(nDirect == 1) //文本标识的方向向右
        {
            p1.setX(nL+nSpace/2); p1.setY(nH+nRectH/4);
            p2.setX(nL+nSpace/2);p2.setY(nH+3*nRectH/4);
            p3.setX(nL+nSpace);p3.setY(nH+nRectH-nTop);
            p4.setX(nL+3*nSpace/2);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2);p5.setY(nH+nRectH/4);
        }
    }
    else if(nPos == 3)        //刻度的方向向左
    {
        if(nDirect == 0)      //文本标识的方向向上
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nTop); p1.setY(nH+nSpace+nLineW);
            p2.setX(nL+nRectH/4);p2.setY(nH+nSpace/2+nLineW);
            p3.setX(nL+3*nRectH/4);p3.setY(nH+nSpace/2+nLineW);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2+nLineW);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2+nLineW);
        }
        else if(nDirect == 1) //文本标识的方向向下
        {
            p1.setX(nL+nTop); p1.setY(nH+nSpace);
            p2.setX(nL+nRectH/4);p2.setY(nH+nSpace/2);
            p3.setX(nL+3*nRectH/4);p3.setY(nH+nSpace/2);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2);
        }
    }
    else if(nPos == 4)        //刻度的方向向右
    {
        if(nDirect == 0)      //文本标识的方向向上
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nRectH/4); p1.setY(nH+nSpace/2+nLineW);
            p2.setX(nL+3*nRectH/4);p2.setY(nH+nSpace/2+nLineW);
            p3.setX(nL+nRectH-nTop);p3.setY(nH+nSpace+nLineW);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2+nLineW);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2+nLineW);
        }
        else if(nDirect == 1) //文本标识的方向向下
        {
            p1.setX(nL+nRectH/4); p1.setY(nH+nSpace/2);
            p2.setX(nL+3*nRectH/4);p2.setY(nH+nSpace/2);
            p3.setX(nL+nRectH-nTop);p3.setY(nH+nSpace);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2);
        }
    }
    mAngle.append(p1);
    mAngle.append(p2);
    mAngle.append(p3);
    mAngle.append(p4);
    mAngle.append(p5);
    QPolygonF mAnglePoly(mAngle);
    pPolyPointer = new QPolygonItem(mAnglePoly);   //画菱形指针
    pPolyPointer->setLineType(1);
    pPolyPointer->setBackColor(BkColor);
    pPolyPointer->setLineColor(FrmColor);
    pPolyPointer->SetName("Pointer");                 //设置名称
    pGroup->addToGroup(pPolyPointer);

    //绘制主次刻度即文本
    nLineW = RectW-2*nSpace;

    if(bIfShow)
    {
        switch(nPos)
        {
        case 1://方向向上
            if(bIfShowZ)//显示轴
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace,nH);
                mPath.lineTo(nL+nSpace+nLineW,nH);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //轴颜色
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace+i*MainSpace,-ML+nH);
                mPath.lineTo(nL+nSpace+i*MainSpace,nH);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //线条颜色
                pLine->SetName(QString("SubLine%1").arg(i));
                pGroup->addToGroup(pLine);

                mMoveX = nL+nSpace+i*MainSpace;
                if(bIfShowM)
                {
                    sText = GetSliderText(i,Min,Max,nMain,nDirect,nNum);
                    pText = new QSimpleTextItem(rect,sText);
                    nTextW = GetTextLength(sText,pText,nFontSize);
                    pText = DrawSliderText(pText,i,mMoveX-nTextW/2-2,-ML+nH-13,
                                           sText,nFontSize,mColor);
                    pGroup->addToGroup(pText);
                }
            }
            for(i = 1; i < nVal;i++) //画次刻度
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(nL+nSpace+i*SubSpace,-ML/2+nH);
                    mPath.lineTo(nL+nSpace+i*SubSpace,nH);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //线条颜色
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 2://方向向下
            if(bIfShowZ)//显示轴
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace,nH+nRectH);
                mPath.lineTo(nL+nSpace+nLineW,nH+nRectH);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //轴颜色
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace+i*MainSpace,nH+nRectH);
                mPath.lineTo(nL+nSpace+i*MainSpace,ML+nH+nRectH);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //线条颜色
                pLine->SetName(QString("SubLine%1").arg(i));
                pGroup->addToGroup(pLine);

                mMoveX = nL+nSpace+i*MainSpace;
                mLineY = ML+nH+nRectH;
                if(bIfShowM)
                {
                    sText = GetSliderText(i,Min,Max,nMain,nDirect,nNum);
                    pText = new QSimpleTextItem(rect,sText); //rect,
                    nTextW = GetTextLength(sText,pText,nFontSize);
                    pText = DrawSliderText(pText,i,mMoveX-nTextW/2-2,mLineY+4,
                                           sText,nFontSize,mColor);
                    pGroup->addToGroup(pText);
                }
            }
            for(i = 1; i < nVal;i++) //画次刻度
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(nL+nSpace+i*SubSpace,nH+nRectH);
                    mPath.lineTo(nL+nSpace+i*SubSpace,ML/2+nH+nRectH);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //线条颜色
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 3://方向向左
            if(bIfShowZ)//显示轴
            {
                QPainterPath mPath;
                mPath.moveTo(nL,nH+nSpace);
                mPath.lineTo(nL,nH+nSpace+nLineW);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //轴颜色
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(-ML+nL,nH+nSpace+i*MainSpace);
                mPath.lineTo(nL,nH+nSpace+i*MainSpace);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //线条颜色
                pLine->SetName(QString("MLine%1").arg(i));
                pGroup->addToGroup(pLine);

                mMoveX = -ML+nL;
                mLineY = nH+nSpace+i*MainSpace;
                if(bIfShowM)
                {
                    sText = GetSliderText(i,Min,Max,nMain,nDirect,nNum);
                    pText = new QSimpleTextItem(rect,sText); //rect,
                    nTextW = GetTextLength(sText,pText,nFontSize);
                    if(slider->m_slider.sTextSize.toInt()<15)
                        pText = DrawSliderText(pText,i,mMoveX-nTextW-4,mLineY-8,sText,nFontSize,mColor);
                    else
                        pText = DrawSliderText(pText,i,mMoveX-nTextW-4,mLineY-9,sText,nFontSize,mColor);
                    if(slider->m_slider.sTextSize.toInt()==20)
                        pText = DrawSliderText(pText,i,mMoveX-nTextW-4,mLineY-20,sText,nFontSize,mColor);

                    pGroup->addToGroup(pText);
                }
            }
            for(i = 1; i < nVal;i++) //画次刻度
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(-ML/2+nL,nH+nSpace+i*SubSpace);
                    mPath.lineTo(nL,nH+nSpace+i*SubSpace);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //线条颜色
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 4://方向向右
            if(bIfShowZ)//显示轴
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nRectH,nH+nSpace);
                mPath.lineTo(nL+nRectH,nH+nSpace+nLineW);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //轴颜色
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nRectH,nH+nSpace+i*MainSpace);
                mPath.lineTo(ML+nL+nRectH,nH+nSpace+i*MainSpace);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //线条颜色
                pLine->SetName(QString("SubLine%1").arg(i));
                pGroup->addToGroup(pLine);

                mMoveX = ML+nL+nRectH;
                mLineY = nH+nSpace+i*MainSpace;
                if(bIfShowM)
                {
                    sText = GetSliderText(i,Min,Max,nMain,nDirect,nNum);
                    pText = new QSimpleTextItem(rect,sText); //rect,
                    if(slider->m_slider.sTextSize.toInt()<15)
                        pText = DrawSliderText(pText,i,mMoveX+4,mLineY-8,sText,nFontSize,mColor);
                    else
                        pText = DrawSliderText(pText,i,mMoveX+4,mLineY-9,sText,nFontSize,mColor);
                    if(slider->m_slider.sTextSize.toInt()==20)
                        pText = DrawSliderText(pText,i,mMoveX+4,mLineY-20,sText,nFontSize,mColor);
                    pGroup->addToGroup(pText);
                }
            }
            for(i = 1; i < nVal;i++) //画次刻度
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(nL+nRectH,nH+nSpace+i*SubSpace);
                    mPath.lineTo(ML/2+nL+nRectH,nH+nSpace+i*SubSpace);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //线条颜色
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;

            default:
            break;
        } //end switch
    } //end if
    return pGroup;
}

int SliderDlg::GetTextLength(QString sText, QSimpleTextItem *pText,
                                 int nFontSize)
{
    QFont nfont = pText->GetTextFont(); //设置文本外框的大小
    nfont.setPointSize(nFontSize);
    QFontMetrics fontM(nfont);
    QRect rc = fontM.boundingRect(sText);
    return rc.width();
}

QSimpleTextItem* SliderDlg::DrawSliderText(QSimpleTextItem *pText,
                                               int nIndex, double LineX, double LineY,
                                               QString sText, int nFontSize,QColor mTextColor)
{
    QString sName = "";

    pText->SetFontSize(nFontSize);
    QFont nfont = pText->GetTextFont(); //设置文本外框的大小
    nfont.setPointSize(nFontSize);
    QFontMetrics fontM(nfont);
    QRect rc = fontM.boundingRect(sText);

    QRectF rect(QPointF(0,0), QSize(50,50));
    rect.setSize(QSize(rc.width()+5,rc.height()));
    pText->setRect(rect);
    pText->setPos(LineX,LineY);
    pText->SetFontColor(mTextColor);
    sName = QString("%1").arg(nIndex);
    sName = "Txt"+sName;
    pText->SetName(sName);
    pText->SetRectOutLine(false);
    return pText;
}

QString SliderDlg::GetSliderText(int nIndex, double Min, double Max,
                                     int nMain, int nTextDirection,
                                     int nPointNum)
{
    double mValue = (Max - Min) / (nMain - 1);
    double dVal = 0;
    QString sText = "";

    if(nTextDirection == 0) //文本向左
    {
        dVal = Max - mValue*nIndex;
        if(nIndex == nMain-1)
            dVal = Min;
    }
    else                   //文本向右
    {
        dVal = Min + mValue*nIndex;
        if(nIndex == nMain-1)
            dVal = Max;
    }
    if(dVal == -0)
        dVal = 0;

    int iTemp = 1;
    for(int i = 0; i < nPointNum; i++)
    {
        iTemp = iTemp * 10;
    }
    dVal = dVal/(double)iTemp;
    sText.sprintf("%.0f", dVal);
    sText = QString::number(dVal,'f',nPointNum);
    if(sText == "-0" || sText.toDouble() == 0)
    {
        sText.remove("-");
    }
    return sText;

}
