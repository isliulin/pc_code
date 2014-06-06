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
 *�������ƣ�DrawSlider
 *�������ܣ�������ģ��������ͼ�κ���
 *sList�������ݺ��壺
 *0������ɫ
 *1��������ɫ
 *2��ָ�걳��ɫ
 *3��ָ��߿�ɫ
 *4���̶�λ��  1--�ϣ�2--�£�3--��4--��
 *5����ʾ����  0--�������ϣ���1--���ң����£�
 //�̶�ҳ��
 *6���Ƿ���ʾ
 *7���̶�������ɫ
 *8�����̶�
 *9���ο̶�
 *10���Ƿ���ʾ��
 *11���Ƿ���ʾ�̶ȱ�ʾ
 *12�������С
 *13����Сֵ
 *14�����ֵ
 *15��С��λ��
 *����ֵ������һ�����ָ��
 *edit by zqh
 *Date:2011-02-17
 **************************************************************/
SliderItem* SliderDlg::DrawSlider(SliderItem *slider)
{
    //�����Ǳ����Ķ���
    QColor BackColor = pwnd->StringTOColor(slider->m_slider.rectColor);//����ɫ
    QColor LineColor = pwnd->StringTOColor(slider->m_slider.slideBarColor);//������ɫ
    QColor BkColor = pwnd->StringTOColor(slider->m_slider.fingerBackColor);  //ָ�걳��ɫ
    QColor FrmColor = pwnd->StringTOColor(slider->m_slider.fingerLineColor); //ָ��߿�ɫ

    int nPos = slider->m_slider.nPosition;     //�̶�λ��
    int nDirect = slider->m_slider.direction;  //��ʾ����
    bool bIfShow = slider->m_slider.isShowCalibration; //�Ƿ���ʾ
    QColor mColor = pwnd->StringTOColor(slider->m_slider.nCalibrationColor); //�̶�������ɫ
    int nMain = slider->m_slider.nMaxNumber;    // ���̶�
    int nSub = slider->m_slider.nMinNumber;     // �ο̶�
    bool bIfShowZ = true;     // �Ƿ���ʾ��
    bool bIfShowM = slider->m_slider.bShowText;     // �Ƿ���ʾ�̶ȱ�ʾ
    int nFontSize = slider->m_slider.nTextSize;     //�����С
    double Min = slider->m_slider.nCalibrationMin.toDouble();     //��Сֵ
    double Max = slider->m_slider.nCalibrationMax.toDouble();     //���ֵ
    int nNum = slider->m_slider.nDecimalCount;       //С��λ��

    double RectW = 120.0;  //�������εĿ��108.0
    int nRectH = 32;       //�������εĸ߶�
    int nSpace = 10;        //����ƫ�뱳�����α߿�ľ���

    QPainterPath mPath;               //�����ߵ�path
    double mMoveX = 0;                //���̶�X��ʼ��
    double mLineY = 0;                //���̶�Y��ʼ��
    SliderItem *pGroup = new SliderItem;

    QLineItem *pLine;
    int i = 0;
    double nLineW = RectW-2*nSpace;
    double MainSpace = nLineW/(nMain-1);           //���̶ȼ��
    double SubSpace = nLineW/((nSub+1)*(nMain-1)); //�ο̶ȼ��
    int ML = 10;                                  //���̶��ߵĳ���
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
    int nTop = 4; //�߿�ָ��ָ��ľ���
    int nTextW = 0; //�ı��Ŀ��

    QVector <QPoint>mAngle;
    QPoint p1,p2,p3,p4,p5;

    //��ʼ����������
    if(nPos == 1 || nPos == 2) //�̶�λ��  1--�ϣ�2--�£�3--��4--��
    {
        rect.setTopLeft(QPointF(nL,nH));
        rect.setSize(QSizeF(RectW,nRectH)); //���Ʊ߿�ɫ���ο�
        mPath.moveTo(nL+nSpace,nH+nRectH/2);
        mPath.lineTo(nL+nSpace+RectW-2*nSpace,nH+nRectH/2);

    }
    else if(nPos == 3 || nPos == 4)
    {
        rect.setTopLeft(QPointF(nL,nH));
        rect.setSize(QSizeF(nRectH,RectW)); //���Ʊ߿�ɫ���ο�
        mPath.moveTo(nL+nRectH/2,nH+nSpace);
        mPath.lineTo(nL+nRectH/2,nH+nSpace+nLineW);
    }

    pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(BackColor);
    pFramRect->SetLineType(0);
    pFramRect->SetName("mFramRect");
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->addToGroup(pFramRect);           //��ӵ���

    //���ƻ���ֱ��
    pMainLine = new QLineItem(mPath);        //��ϸֱ��
    pMainLine->setLineColor(LineColor);      //����ֱ����ɫ
    pMainLine->SetName("MainLine");          //��������
    pMainLine->setLineWidth(3);
    pMainLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pGroup->addToGroup(pMainLine);           //��ӵ���

    //����ָ��
    if(nPos == 1)             //�̶ȵķ�������
    {
        if(nDirect == 0)      //�ı���ʶ�ķ�������
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nSpace+nLineW); p1.setY(nH+nTop);
            p2.setX(nL+nSpace/2+nLineW);p2.setY(nH+nRectH/4);
            p3.setX(nL+nSpace/2+nLineW);p3.setY(nH+3*nRectH/4);
            p4.setX(nL+3*nSpace/2+nLineW);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2+nLineW);p5.setY(nH+nRectH/4);
        }
        else if(nDirect == 1) //�ı���ʶ�ķ�������
        {
            p1.setX(nL+nSpace); p1.setY(nH+nTop);
            p2.setX(nL+nSpace/2);p2.setY(nH+nRectH/4);
            p3.setX(nL+nSpace/2);p3.setY(nH+3*nRectH/4);
            p4.setX(nL+3*nSpace/2);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2);p5.setY(nH+nRectH/4);
        }
    }
    else if(nPos == 2)        //�̶ȵķ�������
    {
        if(nDirect == 0)      //�ı���ʶ�ķ�������
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nSpace/2+nLineW); p1.setY(nH+nRectH/4);
            p2.setX(nL+nSpace/2+nLineW);p2.setY(nH+3*nRectH/4);
            p3.setX(nL+nSpace+nLineW);p3.setY(nH+nRectH-nTop);
            p4.setX(nL+3*nSpace/2+nLineW);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2+nLineW);p5.setY(nH+nRectH/4);
        }
        else if(nDirect == 1) //�ı���ʶ�ķ�������
        {
            p1.setX(nL+nSpace/2); p1.setY(nH+nRectH/4);
            p2.setX(nL+nSpace/2);p2.setY(nH+3*nRectH/4);
            p3.setX(nL+nSpace);p3.setY(nH+nRectH-nTop);
            p4.setX(nL+3*nSpace/2);p4.setY(nH+3*nRectH/4);
            p5.setX(nL+3*nSpace/2);p5.setY(nH+nRectH/4);
        }
    }
    else if(nPos == 3)        //�̶ȵķ�������
    {
        if(nDirect == 0)      //�ı���ʶ�ķ�������
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nTop); p1.setY(nH+nSpace+nLineW);
            p2.setX(nL+nRectH/4);p2.setY(nH+nSpace/2+nLineW);
            p3.setX(nL+3*nRectH/4);p3.setY(nH+nSpace/2+nLineW);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2+nLineW);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2+nLineW);
        }
        else if(nDirect == 1) //�ı���ʶ�ķ�������
        {
            p1.setX(nL+nTop); p1.setY(nH+nSpace);
            p2.setX(nL+nRectH/4);p2.setY(nH+nSpace/2);
            p3.setX(nL+3*nRectH/4);p3.setY(nH+nSpace/2);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2);
        }
    }
    else if(nPos == 4)        //�̶ȵķ�������
    {
        if(nDirect == 0)      //�ı���ʶ�ķ�������
        {
            nLineW = RectW-2*nSpace;
            p1.setX(nL+nRectH/4); p1.setY(nH+nSpace/2+nLineW);
            p2.setX(nL+3*nRectH/4);p2.setY(nH+nSpace/2+nLineW);
            p3.setX(nL+nRectH-nTop);p3.setY(nH+nSpace+nLineW);
            p4.setX(nL+3*nRectH/4);p4.setY(nH+3*nSpace/2+nLineW);
            p5.setX(nL+nRectH/4);p5.setY(nH+3*nSpace/2+nLineW);
        }
        else if(nDirect == 1) //�ı���ʶ�ķ�������
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
    pPolyPointer = new QPolygonItem(mAnglePoly);   //������ָ��
    pPolyPointer->setLineType(1);
    pPolyPointer->setBackColor(BkColor);
    pPolyPointer->setLineColor(FrmColor);
    pPolyPointer->SetName("Pointer");                 //��������
    pGroup->addToGroup(pPolyPointer);

    //�������ο̶ȼ��ı�
    nLineW = RectW-2*nSpace;

    if(bIfShow)
    {
        switch(nPos)
        {
        case 1://��������
            if(bIfShowZ)//��ʾ��
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace,nH);
                mPath.lineTo(nL+nSpace+nLineW,nH);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //����ɫ
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace+i*MainSpace,-ML+nH);
                mPath.lineTo(nL+nSpace+i*MainSpace,nH);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //������ɫ
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
            for(i = 1; i < nVal;i++) //���ο̶�
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(nL+nSpace+i*SubSpace,-ML/2+nH);
                    mPath.lineTo(nL+nSpace+i*SubSpace,nH);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //������ɫ
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 2://��������
            if(bIfShowZ)//��ʾ��
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace,nH+nRectH);
                mPath.lineTo(nL+nSpace+nLineW,nH+nRectH);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //����ɫ
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nSpace+i*MainSpace,nH+nRectH);
                mPath.lineTo(nL+nSpace+i*MainSpace,ML+nH+nRectH);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //������ɫ
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
            for(i = 1; i < nVal;i++) //���ο̶�
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(nL+nSpace+i*SubSpace,nH+nRectH);
                    mPath.lineTo(nL+nSpace+i*SubSpace,ML/2+nH+nRectH);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //������ɫ
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 3://��������
            if(bIfShowZ)//��ʾ��
            {
                QPainterPath mPath;
                mPath.moveTo(nL,nH+nSpace);
                mPath.lineTo(nL,nH+nSpace+nLineW);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //����ɫ
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(-ML+nL,nH+nSpace+i*MainSpace);
                mPath.lineTo(nL,nH+nSpace+i*MainSpace);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //������ɫ
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
            for(i = 1; i < nVal;i++) //���ο̶�
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(-ML/2+nL,nH+nSpace+i*SubSpace);
                    mPath.lineTo(nL,nH+nSpace+i*SubSpace);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //������ɫ
                    pLine->SetName(QString("SLine%1").arg(i));
                    pGroup->addToGroup(pLine);
                }
            }
            break;
        case 4://��������
            if(bIfShowZ)//��ʾ��
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nRectH,nH+nSpace);
                mPath.lineTo(nL+nRectH,nH+nSpace+nLineW);
                pZLine = new QLineItem(mPath);
                pZLine->setLineColor(mColor); //����ɫ
                pZLine->SetName("ZLine");
                pGroup->addToGroup(pZLine);
            }
            for(i = 0; i < nMain;i++)
            {
                QPainterPath mPath;
                mPath.moveTo(nL+nRectH,nH+nSpace+i*MainSpace);
                mPath.lineTo(ML+nL+nRectH,nH+nSpace+i*MainSpace);
                pLine = new QLineItem(mPath);
                pLine->setLineColor(mColor); //������ɫ
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
            for(i = 1; i < nVal;i++) //���ο̶�
            {
                if(i%(nSub+1) != 0)
                {
                    QPainterPath mPath;
                    mPath.moveTo(nL+nRectH,nH+nSpace+i*SubSpace);
                    mPath.lineTo(ML/2+nL+nRectH,nH+nSpace+i*SubSpace);
                    pLine = new QLineItem(mPath);
                    pLine->setLineColor(mColor); //������ɫ
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
    QFont nfont = pText->GetTextFont(); //�����ı����Ĵ�С
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
    QFont nfont = pText->GetTextFont(); //�����ı����Ĵ�С
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

    if(nTextDirection == 0) //�ı�����
    {
        dVal = Max - mValue*nIndex;
        if(nIndex == nMain-1)
            dVal = Min;
    }
    else                   //�ı�����
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
