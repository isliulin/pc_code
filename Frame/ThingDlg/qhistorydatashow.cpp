#include "qhistorydatashow.h"
#include "ui_qhistorydatashow.h"
#include "Frame/mainwindow.h"
#include <iostream>
#include <fstream>

using namespace std;

extern MainWindow *pwnd;

QHistoryDataShow::QHistoryDataShow(QHistoryDataShowAttr* pItem, QWidget *parent):QDialog(parent),ui(new Ui::QHistoryDataShow)
{
    ui->setupUi(this);

    oId = -1;
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    this->m_pCopyItem = NULL;
    pTempItem = NULL;

    this->page1 = new QHistoryDataShowOne;
    this->page2 = new QHistoryDataShowTwo;

    ui->tabWidget->addTab(page1, tr("一般"));
    ui->tabWidget->addTab(page2, tr("数据"));

    pSecurityWight = new SecurityWidget(this);
    ui->tabWidget->addTab(pSecurityWight, tr("权限设置"));
    //pSecurityWight->ui->groupBox_Touch->hide();
    pSecurityWight->setTouchGroupEnabled(false);

    this->setWindowTitle(tr("历史数据显示器"));

    pScene = new QGraphicsScene(this); //建场景
    ui->graphicsView->setScene(pScene);//贴图区域

    InitPropertys(pItem);

    drawSence();

    connect(page1, SIGNAL(redrawSence()), this, SLOT(drawSence()));
    connect(page2, SIGNAL(redrawSence()), this, SLOT(drawSence()));

    connect(page1, SIGNAL(sigLanguageCh(int)), page2, SLOT(slotLan(int)));
    connect(page2, SIGNAL(sigLanguageCh(int)), page1, SLOT(slotLan(int)));

    connect(page2, SIGNAL(groupCh()), page1, SLOT(groupCh()));//
}

QHistoryDataShow::~QHistoryDataShow()
{
    if(page1)
    {
        delete page1;
        page1 = NULL;
    }

    if(page2)
    {
        delete page2;
        page2 = NULL;
    }

    if(m_pCopyItem)
    {
        delete m_pCopyItem;
        m_pCopyItem = NULL;
    }

    if(pSecurityWight)
    {
        delete pSecurityWight;
        pSecurityWight = NULL;
    }

    if(pTempItem)
    {
        delete pTempItem;
        pTempItem = NULL;
    }

    if(pScene)
    {
        delete pScene;
        pScene = NULL;
    }

    delete ui;
}

void QHistoryDataShow::on_accept_clicked()
{
    if(page1->m_bAddr)
    {
        if(! pwnd->IsAddressCheckRight(page1->m_KeyAddr,tr("历史数据显示器控制地址"),page1->ui->lineEdit_Ctrl,1))
        {
            page1->ui->lineEdit_Ctrl->setFocus();
            return ;
        }
    }

    m_pCopyItem = new QHistoryDataShowAttr;

    if(pSecurityWight && pSecurityWight->Save())
    {
        m_pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    }
    else
    {
        return;
    }

    m_pCopyItem->m_nForecolor       = page1->m_nForecolor;
    m_pCopyItem->m_nFrameColor      = page1->m_nFrameColor;
    m_pCopyItem->m_nAlpha           = page1->m_nAlpha;

    m_pCopyItem->m_nTextFontSize    = page1->m_nTextFontSize;
    m_pCopyItem->m_nLine            = page1->m_nLine;
    m_pCopyItem->m_nTextFontColor   = page1->m_nTextFontColor;

    m_pCopyItem->m_bShowTime        = page1->m_bShowTime;
    m_pCopyItem->m_bShowDate        = page1->m_bShowDate;
    m_pCopyItem->m_nTitleBackColor  = page1->m_nTitleBackColor;
    m_pCopyItem->m_nTitleFontColor  = page1->m_nTitleFontColor;
    m_pCopyItem->m_bShowCode        = page1->m_bShowCode;
    m_pCopyItem->m_eTimeFormat      = page1->m_eTimeFormat;
    m_pCopyItem->m_eDateFormat      = page1->m_eDateFormat;
    m_pCopyItem->m_bAddr            = page1->m_bAddr;
    m_pCopyItem->m_KeyAddr          = page1->m_KeyAddr;

    m_pCopyItem->m_vecHisText       = page1->m_vecHisText;

    m_pCopyItem->sGroupName         = page2->sGroupName;
    m_pCopyItem->m_vecHisData       = page2->m_vecHisData;

    m_pCopyItem->setId(ui->spinBox->value());
    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return ;
    }

    DrawTable();
    //m_pCopyItem->sDataName          = sDataName;

    QDialog::accept();
}

void QHistoryDataShow::on_cancel_clicked()
{
    this->close();
}

void QHistoryDataShow::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_HISTORYDATE);
}

void QHistoryDataShow::InitPropertys(QHistoryDataShowAttr* pItem)
{
    if(pItem)
    {
        QList<QGraphicsItem *> list = pItem->childItems();
        QRectF rect = pItem->sceneBoundingRect();
        QString sName = "";
        vVLine.clear();
        vHLine.clear();
        vVLine.append(rect.x());
        vHLine.append(rect.y());
        //vTileTex.clear();

        foreach(QGraphicsItem *pItem,list)
        {
            QPointF pos = pItem->boundingRect().topLeft()+pItem->scenePos();
            sName = pItem->data(GROUP_NAME_KEY).toString();
            if(sName.contains("VLine")) //垂直线
            {
                vVLine.append(pos.x());
            }
            if(sName.contains("HLine")) //水平线
            {
                vHLine.append(pos.y());
            }
        }

        for(int i = 0; i < vVLine.size(); i++)
        {
            for(int j = i + 1; j < vVLine.size(); j++)
            {
                if(vVLine.at(i) > vVLine.at(j))
                {
                    qreal odata;
                    odata = vVLine.at(i);
                    vVLine.replace(i,vVLine.at(j));
                    vVLine.replace(j,odata);
                }
            }
        }
        vVLine.append(rect.x() + rect.width());

        //横直线
        for(int i = 0; i < vHLine.size(); i++)
        {
            for(int j = i + 1; j < vHLine.size(); j++)
            {
                if(vHLine.at(i) > vHLine.at(j))
                {
                    qreal odata;
                    odata = vHLine.at(i);
                    vHLine.replace(i,vHLine.at(j));
                    vHLine.replace(j,odata);
                }
            }
        }
        vHLine.append(rect.y() + rect.height());

        page1->Init(pItem);
        page2->Init(pItem);
        pSecurityWight->init(pItem);
        oId = pItem->id();
        ui->spinBox->setValue(oId);
    }
    else
    {
        page1->Init(NULL);
        page2->Init(NULL);
        pSecurityWight->init(NULL);
        ui->spinBox->setValue(pwnd->getNewId());
    }
}

void QHistoryDataShow::DrawTable()
{
    int     i           = 0;
    int     nVal        = 0;
    double  mMoveX      = 0;                //主刻度X起始点
    double  mMoveY      = 0;                //主刻度Y起始点
    double  mLineX      = 0;                //主刻度X起始点
    double  mLineY      = 0;                //主刻度Y起始点
    int     nUseCount   = 0;                //数据页面显示的条数

    //ofstream of("D:\\BBB.txt", ios::app);
    //m_pCopyItem = new QHistoryDataShowAttr;
    //of << "X" << endl;
    //取一般页面画图的属性
    QColor  mFBackcolor    = page1->m_nForecolor;  //框架的背景色
    QColor  mFBorderColor  = page1->m_nFrameColor; //框架的边框色
    short   alpha          = page1->m_nAlpha;
    bool    bIfVertical    = true;                //是否垂直显示
    bool    bIfHorizon     = true;                //是否水平
    QColor  mLineColor     = page1->m_nFrameColor; //格线颜色,跟边框色一样
    int     nLanguageCount = page1->m_vecHisText.size();//语言总数
    QColor  nTextColor     = page1->m_nTextFontColor;
    int     nTextfSize     = page1->m_nTextFontSize;

    int iLan = page1->m_nCurLanNum;//pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan;
    if(iLan < 0)
    {
        iLan = 0;
    }
    nVal = page1->m_vecHisText[iLan].m_nTitleFontSize;
    for(i = 1; i < nLanguageCount; i++)                                  //求最大的字体大小
    {
        if(nVal <  page1->m_vecHisText[i].m_nTitleFontSize)
        {
            nVal = page1->m_vecHisText[i].m_nTitleFontSize;
        }
    }
    int     nTFontSize  = page1->m_vecHisText[iLan].m_nTitleFontSize;   //以语言1字体大小
    QString sTFont      = page1->m_vecHisText[iLan].m_sTitleFontType;   //以语言1的字体
    QColor  mTBackColor = page1->m_nTitleBackColor;                     //标题列背景色
    QColor  mTTextColor = page1->m_nTitleFontColor;                     //标题列的文本颜色
    bool    bIfTime     = page1->m_bShowTime;                           //是否显示时间列

    QString sTime       = page1->m_vecHisText[iLan].m_sTitleTimeName;   //以语言1显示时间内容
    bool    bIfDate     = page1->m_bShowDate;                           //是否显示日期列
    QString sDate       = page1->m_vecHisText[iLan].m_sTitleDateName;   //以语言1显示日期内容
    int     nRow        = page1->m_nLine;                               //行数

    int             nH      = 25;  //每格的高度 10
    int             nTotalH = nH*(nRow + 1);
    int             nW      = 480; //背景框的总宽度120
    int             nTexeW  = 0;   //文本的宽度120
    QString         sName   = "";
    QLineItem       *pLine;
    QSimpleTextItem *pText;
    QStringList     sDataName;
    bool            bIfNumber   = page1->m_bShowCode; //是否选择了显示编号
    int             nValue      = 0;
    bool            bDoubleClick = false;

    //画背景矩形
    QRectF rect(QPointF(0,0), QSize(nW,(nRow+1)*nH));     //绘制背景矩形
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(mFBackcolor);             //背景框的背景色
    pFramRect->SetLineColor(mFBorderColor);           //背景框的边框色
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetName("mFramRect");
    pFramRect->SetAlpha(alpha);
    m_pCopyItem->addToGroup(pFramRect);                    //添加到组

    /*QPainterPath mPath1;
    mMoveX = 0;
    mMoveY = 0;
    mLineX = nW;
    mLineY = 0;
    mPath1.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath1.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath1);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_pCopyItem->addToGroup(pLine);                   //添加到组

    QPainterPath mPath2;
    mMoveX = 0;
    mMoveY = nTotalH;
    mLineX = nW;
    mLineY = nTotalH;
    mPath2.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath2.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath2);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_pCopyItem->addToGroup(pLine);                   //添加到组

    QPainterPath mPath3;
    mMoveX = 0;
    mMoveY = 0;
    mLineX = 0;
    mLineY = nTotalH;
    mPath3.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath3.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath3);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_pCopyItem->addToGroup(pLine);                   //添加到组

    QPainterPath mPath4;
    mMoveX = nW;
    mMoveY = 0;
    mLineX = nW;
    mLineY = nTotalH;
    mPath4.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath4.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath4);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_pCopyItem->addToGroup(pLine);                   //添加到组*/

    //画标题文本
    sDataName.clear();
    if(bIfTime)
    {
        nUseCount++;
        sDataName.append(sTime);
    }
    if(bIfDate)
    {
        nUseCount++;
        sDataName.append(sDate);
    }

	int nshow = 0;
    if(page2->sGroupName != "")
    {
        int temp = page2->m_vecHisData[page2->m_nCurLanNum].m_vecInfo.size();
        
        for(i = 0; i < temp; i++)
        {
            if(page2->m_vecHisData[page2->m_nCurLanNum].m_vecInfo[i].m_bShow) //显示条数计数
            {
                //nUseCount++;
                nshow++;
                //int index = page1->ui->comboBox_titleLan->currentIndex();
                //if(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.at(i).sNameList.size() < index +1)
                //{
                //    pwnd->m_pSamSysParame->m_historyLogData.mSampleList[i].sNameList.resize(index +1);
                //}
                //sDataName.append(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.at(i).sNameList.at(index));//存显示的名称
                if(nshow > 3)
                {
                    sDataName.append(tr("..."));
                    break;
                }
                else
                {
                    sDataName.append(page2->m_vecHisData[page2->m_nCurLanNum].m_vecInfo[i].m_strName);
                }
            }
        }
    }

    if(bIfNumber)
    {
        if(nshow > 3)//3个以上要画的
        {
            nValue = nUseCount + 1 + 3 + 1;
        }
        else
        {
            nValue = nUseCount + 1 + nshow;
        }
        i = 1;
    }
    else
    {
        if(nshow > 3)
        {
            nValue = nUseCount + 3 + 1;
        }
        else
        {
            nValue = nUseCount + nshow;
        }
        i = 0;
    }
    nTexeW = nW/nValue;//nUseCount; //文本平均宽度

    if(nValue == (vVLine.size() - 1) && nRow == (vHLine.size() - 2))
    {
        bDoubleClick = true;
        qreal Width = vVLine.at(vVLine.size()-1) - vVLine.at(0);
        qreal Hight = vHLine.at(vHLine.size()-1) - vHLine.at(0);

        qreal n = vVLine.at(0);
        for(int i = 0; i < vVLine.size(); i++ )
        {
            vVLine[i] = vVLine[i] - n;
            vVLine[i] = vVLine[i] * nW/Width;
        }

        n = vHLine.at(0);
        for(int i = 0; i < vHLine.size(); i++ )
        {
            vHLine[i] = vHLine[i] - n;
            vHLine[i] = vHLine[i] * nTotalH/Hight;
        }
    }

    //画标题列
    rect.setWidth(nW);                                //绘制标题列
    rect.setHeight(nH);
    if(bDoubleClick)
    {
        rect.setHeight(vHLine.at(1) - vHLine.at(0));
    }
    QRectItem *pTitleRect = new QRectItem(rect);
    pTitleRect->SetBackColor(mTBackColor);            //标题列矩形框背景色
    pTitleRect->SetLineType(0);
    pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTitleRect->SetName("mTitleRect");
    pTitleRect->SetAlpha(alpha);
    m_pCopyItem->addToGroup(pTitleRect);                   //添加到组

    if(1 == i)//画序号
    {
        rect.setTopLeft(QPointF(0,0));           //绘制文本pText
        rect.setSize(QSize(nTexeW,nH));
        if(bDoubleClick)
        {
            rect.setSize(QSize(vVLine.at(1) - vVLine.at(0),vHLine.at(1) - vHLine.at(0)));
        }

        //if(bIfNumber)此时这句话一定成立
        pText = new QSimpleTextItem(rect,page1->m_vecHisText[iLan].m_sTitleNumber);

        pText->SetFontSize(nTFontSize);
        pText->SetFontName(sTFont);
        pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName("NoText0");
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pText->SetAlpha(alpha);
        m_pCopyItem->addToGroup(pText);
    }

    for(i; i < nValue;i++)// for(i = 0; i < nUseCount;i++)
    {
        rect.setTopLeft(QPointF(i*nTexeW,0));           //绘制文本pText
        rect.setSize(QSize(nTexeW,nH));
        if(bDoubleClick)
        {
            rect.setTopLeft(QPointF(vVLine.at(i),0));           //绘制文本pText
            rect.setSize(QSize(vVLine.at(i+1) - vVLine.at(i),vHLine.at(1) - vHLine.at(0)));
        }
        //pText = new QSimpleTextItem(rect,sDataName.at(i));
        if(bIfNumber)
            pText = new QSimpleTextItem(rect,sDataName.at(i-1));
        else
            pText = new QSimpleTextItem(rect,sDataName.at(i));
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(sTFont);
        pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName(QString("Text%1").arg(i));
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pText->SetAlpha(alpha);
        m_pCopyItem->addToGroup(pText);                   //添加到组
    }

    //画水平线
    if(bIfHorizon)   //选中了水平选择框
    {
        for(i = 0; i < nRow; i++)
        {
            QPainterPath mPath;
            mMoveX = 0;
            mMoveY = i*nH+nH;
            mLineX = 0+nW;
            mLineY = i*nH+nH;
            if(bDoubleClick)
            {
                mMoveY = vHLine.at(i+1);
                mLineY = vHLine.at(i+1);
            }
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            pLine->setLineColor(mLineColor);     //设置直线颜色
            //pLine->setAlpha(alpha);
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "HLine"+sName;
            pLine->SetName(sName);
            m_pCopyItem->addToGroup(pLine);                   //添加到组

            if(bIfNumber)
            {
                rect.setTopLeft(QPointF(0, (i+1)*nH));           //绘制文本pText
                rect.setSize(QSize(nTexeW,nH));
                if(bDoubleClick)
                {
                    rect.setTopLeft(QPointF(0,vHLine.at(i+1)));           //绘制文本pText
                    rect.setSize(QSize(vVLine.at(1) - vVLine.at(0),vHLine.at(i+2) - vHLine.at(i+1)));
                }
                pText = new QSimpleTextItem(rect,QString("%1").arg(i+1));
                pText->SetFontSize(nTFontSize);
                pText->SetFontName(tr("Droid Sans Fallback"));
                //pText->SetFontColor(mTTextColor); //字体颜色
                pText->SetName(QString("NoText%1").arg(i + 1));
                pText->SetRectOutLine(false);
                pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pText->SetAlpha(alpha);
                m_pCopyItem->addToGroup(pText);                   //添加到组
            }
        }
    }

    //画垂直线
    if(bIfVertical)  //选中了垂直
    {
        for(i = 1; i < nValue; i++) //nUseCount
        {
            QPainterPath mPath;
            mMoveX = nTexeW*i;
            mMoveY = 0;
            mLineX = nTexeW*i;
            mLineY = (nRow+1)*nH;
            if(bDoubleClick)
            {
                mMoveX = vVLine.at(i);
                mLineX = vVLine.at(i);
            }
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            pLine->setLineColor(mLineColor);     //设置直线颜色
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "VLine"+sName;
            pLine->SetName(sName);
            //pLine->setAlpha(alpha);
            m_pCopyItem->addToGroup(pLine);                   //添加到组
        }

        int k = 0;
        if(bIfNumber)
        {
            k++;
        }
        QTime tm;
        QString strTime;
        QDate dt;
        QString strDate;
        tm = QTime::currentTime();
        dt = QDate::currentDate();
        if(page1->m_eTimeFormat == HHMM_COLON)
        {
            strTime = tm.toString("hh:mm");
        }
        else if(page1->m_eTimeFormat == HHMMSS_COLON)
        {
            strTime = tm.toString("hh:mm:ss");
        }
        else if(page1->m_eTimeFormat == HHMM_ACROSS)
        {
            strTime = tm.toString("hh-mm");
        }
        else
        {
            strTime = tm.toString("hh-mm-ss");
        }

        if(page1->m_eDateFormat == YYYYMMDD_SLASH)
        {
            strDate = dt.toString("yyyy/MM/dd");
        }
        else if(page1->m_eDateFormat == YYYYMMDD_POINT)
        {
            strDate = dt.toString("yyyy.MM.dd");
        }
        else if(page1->m_eDateFormat == YYYYMMDD_ACROSS)
        {
            strDate = dt.toString("yyyy-MM-dd");
        }
        else if(page1->m_eDateFormat == MMDDYYYY_SLASH)
        {
            strDate = dt.toString("MM/dd/yyyy");
        }
        else if(page1->m_eDateFormat == MMDDYYYY_POINT)
        {
            strDate = dt.toString("MM.dd.yyyy");
        }
        else if(page1->m_eDateFormat == MMDDYYYY_ACROSS)
        {
            strDate = dt.toString("MM-dd-yyyy");
        }
        else if(page1->m_eDateFormat == DDMMYYYY_SLASH)
        {
            strDate = dt.toString("dd/MM/yyyy");
        }
        else if(page1->m_eDateFormat == DDMMYYYY_ACROSS)
        {
            strDate = dt.toString("dd-MM-yyyy");
        }
        else
        {
            strDate = dt.toString("dd.MM.yyyy");
        }

        if(bIfTime && bIfDate)
        {
            rect.setTopLeft(QPointF(nTexeW * k, nH));           //绘制文本pText
            rect.setSize(QSize(nTexeW,nH));
            if(bDoubleClick)
            {
                rect.setTopLeft(QPointF(vVLine.at(k), vHLine.at(1)));           //绘制文本pText
                rect.setSize(QSize(vVLine.at(k+1) - vVLine.at(k),vHLine.at(2) - vHLine.at(1)));
            }
            pText = new QSimpleTextItem(rect,strTime);
            pText->SetFontSize(nTextfSize);
            pText->SetFontName(tr("Droid Sans Fallback"));
            pText->SetFontColor(nTextColor); //字体颜色
            pText->SetName("DateText1");
            pText->SetRectOutLine(false);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pText->SetAlpha(alpha);
            m_pCopyItem->addToGroup(pText);                   //添加到组

            //--------------------------------------------------------------
            k++;
            rect.setTopLeft(QPointF(nTexeW * k, nH));           //绘制文本pText
            rect.setSize(QSize(nTexeW,nH));
            if(bDoubleClick)
            {
                rect.setTopLeft(QPointF(vVLine.at(k), vHLine.at(1)));           //绘制文本pText
                rect.setSize(QSize(vVLine.at(k+1) - vVLine.at(k),vHLine.at(2) - vHLine.at(1)));
            }
            pText = new QSimpleTextItem(rect,strDate);
            pText->SetFontSize(nTextfSize);
            pText->SetFontName(tr("Droid Sans Fallback"));
            pText->SetFontColor(nTextColor); //字体颜色
            pText->SetName("DateText2");
            pText->SetRectOutLine(false);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pText->SetAlpha(alpha);
            m_pCopyItem->addToGroup(pText);                   //添加到组
            k++;
        }
        else if(bIfTime && !bIfDate)
        {
            rect.setTopLeft(QPointF(nTexeW * k, nH));           //绘制文本pText
            rect.setSize(QSize(nTexeW,nH));
            if(bDoubleClick)
            {
                rect.setTopLeft(QPointF(vVLine.at(k), vHLine.at(1)));           //绘制文本pText
                rect.setSize(QSize(vVLine.at(k+1) - vVLine.at(k),vHLine.at(2) - vHLine.at(1)));
            }
            pText = new QSimpleTextItem(rect,strTime);
            pText->SetFontSize(nTextfSize);
            pText->SetFontName(tr("Droid Sans Fallback"));
            pText->SetFontColor(nTextColor); //字体颜色
            pText->SetName("DateText1");
            pText->SetRectOutLine(false);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pText->SetAlpha(alpha);
            m_pCopyItem->addToGroup(pText);                   //添加到组
            k++;
        }
        else if(!bIfTime && bIfDate)
        {
            rect.setTopLeft(QPointF(nTexeW * k, nH));           //绘制文本pText
            rect.setSize(QSize(nTexeW,nH));
            if(bDoubleClick)
            {
                rect.setTopLeft(QPointF(vVLine.at(k), vHLine.at(1)));           //绘制文本pText
                rect.setSize(QSize(vVLine.at(k+1) - vVLine.at(k),vHLine.at(2) - vHLine.at(1)));
            }
            pText = new QSimpleTextItem(rect,strDate);
            pText->SetFontSize(nTextfSize);
            pText->SetFontName(tr("Droid Sans Fallback"));
            pText->SetFontColor(nTextColor); //字体颜色
            pText->SetName("DateText1");
            pText->SetRectOutLine(false);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pText->SetAlpha(alpha);
            m_pCopyItem->addToGroup(pText);                   //添加到组
            k++;
        }
        for(k; k < nValue; k++)
        {
            rect.setTopLeft(QPointF(nTexeW * k, nH));           //绘制文本pText
            rect.setSize(QSize(nTexeW,nH));
            if(bDoubleClick)
            {
                rect.setTopLeft(QPointF(vVLine.at(k), vHLine.at(1)));           //绘制文本pText
                rect.setSize(QSize(vVLine.at(k+1) - vVLine.at(k),vHLine.at(2) - vHLine.at(1)));
            }
            pText = new QSimpleTextItem(rect,"");
            pText->SetFontSize(nTextfSize);
            pText->SetFontName(tr("Droid Sans Fallback"));
            pText->SetFontColor(nTextColor); //字体颜色
            pText->SetName(QString("DateText%1").arg(k));
            pText->SetRectOutLine(false);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pText->SetAlpha(alpha);
            m_pCopyItem->addToGroup(pText);
        }
    }

    QPainterPath mPath1;
    mMoveX = 0;
    mMoveY = 0;
    mLineX = nW;
    mLineY = 0;
    mPath1.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath1.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath1);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_pCopyItem->addToGroup(pLine);                   //添加到组

    QPainterPath mPath2;
    mMoveX = 0;
    mMoveY = nTotalH;
    mLineX = nW;
    mLineY = nTotalH;
    mPath2.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath2.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath2);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_pCopyItem->addToGroup(pLine);                   //添加到组

    QPainterPath mPath3;
    mMoveX = 0;
    mMoveY = 0;
    mLineX = 0;
    mLineY = nTotalH;
    mPath3.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath3.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath3);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_pCopyItem->addToGroup(pLine);                   //添加到组

    QPainterPath mPath4;
    mMoveX = nW;
    mMoveY = 0;
    mLineX = nW;
    mLineY = nTotalH;
    mPath4.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath4.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath4);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    m_pCopyItem->addToGroup(pLine);                   //添加到组
}

void QHistoryDataShow::drawSence()
{
    if(pTempItem)
    {
        delete pTempItem;
    }
    pTempItem = new QHistoryDataShowAttr;

    int     i           = 0;
    int     nVal        = 0;
    double  mMoveX      = 0;                //主刻度X起始点
    double  mMoveY      = 0;                //主刻度Y起始点
    double  mLineX      = 0;                //主刻度X起始点
    double  mLineY      = 0;                //主刻度Y起始点
    int     nUseCount   = 0;                //数据页面显示的条数

    int             nTexeW  = 0;   //文本的宽度120
    QString         sName   = "";
    QLineItem       *pLine;
    QSimpleTextItem *pText;
    QStringList     sDataName;
    bool            bIfNumber   = page1->m_bShowCode; //是否选择了显示编号
    int             nValue      = 0;

    //取一般页面画图的属性
    QColor  mFBackcolor    = page1->m_nForecolor;  //框架的背景色
    QColor  mFBorderColor  = page1->m_nFrameColor; //框架的边框色
    short   alpha          = page1->m_nAlpha;
    bool    bIfVertical    = true;                //是否垂直显示
    bool    bIfHorizon     = true;                //是否水平
    QColor  mLineColor     = page1->m_nFrameColor; //格线颜色,跟边框色一样
    int     nLanguageCount = page1->m_vecHisText.size();//语言总数
    QColor  nTextColor     = page1->m_nTextFontColor;
    int     nTextfSize     = page1->m_nTextFontSize;

    int iLan = page1->m_nCurLanNum;//pwnd->m_pSamSysParame->m_mixGlobalVar.m_nCurLan;
    if(iLan < 0)
    {
        iLan = 0;
    }
    nVal = page1->m_vecHisText[iLan].m_nTitleFontSize;
    for(i = 1; i < nLanguageCount; i++)                                  //求最大的字体大小
    {
        if(nVal <  page1->m_vecHisText[i].m_nTitleFontSize)
        {
            nVal = page1->m_vecHisText[i].m_nTitleFontSize;
        }
    }
    int     nTFontSize  = page1->m_vecHisText[iLan].m_nTitleFontSize;   //以语言1字体大小
    QString sTFont      = page1->m_vecHisText[iLan].m_sTitleFontType;   //以语言1的字体
    QColor  mTBackColor = page1->m_nTitleBackColor;                     //标题列背景色
    QColor  mTTextColor = page1->m_nTitleFontColor;                     //标题列的文本颜色
    bool    bIfTime     = page1->m_bShowTime;                           //是否显示时间列

    QString sTime       = page1->m_vecHisText[iLan].m_sTitleTimeName;   //以语言1显示时间内容
    bool    bIfDate     = page1->m_bShowDate;                           //是否显示日期列
    QString sDate       = page1->m_vecHisText[iLan].m_sTitleDateName;   //以语言1显示日期内容
    int     nRow        = page1->m_nLine;                               //行数

    sDataName.clear();
    if(bIfTime)
    {
        nUseCount++;
        sDataName.append(sTime);
    }
    if(bIfDate)
    {
        nUseCount++;
        sDataName.append(sDate);
    }

	int nshow = 0;
    if(page2->sGroupName != "")
    {
        int temp = page2->m_vecHisData[page2->m_nCurLanNum].m_vecInfo.size();
        
        for(i = 0; i < temp; i++)
        {
            if(page2->m_vecHisData[page2->m_nCurLanNum].m_vecInfo[i].m_bShow) //显示条数计数
            {
                //nUseCount++;
                nshow++;
                //int index = page1->ui->comboBox_titleLan->currentIndex();
                //if(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.at(i).sNameList.size() < index +1)
                //{
                //    pwnd->m_pSamSysParame->m_historyLogData.mSampleList[i].sNameList.resize(index +1);
                //}
                //sDataName.append(pwnd->m_pSamSysParame->m_historyLogData.mSampleList.at(i).sNameList.at(index));//存显示的名称
                if(nshow > 3)
                {
                    sDataName.append(tr("..."));
                    break;
                }
                else
                {
                    sDataName.append(page2->m_vecHisData[page2->m_nCurLanNum].m_vecInfo[i].m_strName);
                }
                //sDataName.append(page2->m_vecHisData[page2->m_nCurLanNum].m_vecInfo[i].m_strName);
            }
        }
    }

    int totalWidth  = ui->graphicsView->size().width();
    int totalHeight = ui->graphicsView->size().height();
    int             nH      = (totalHeight - 20) / (nRow + 1);  //每格的高度 10
    int             nTotalH = nH*(nRow + 1);
    int             nW      = 120; //背景框的总宽度120

    //画背景矩形
    QRectF rect(QPointF(0,0), QSize(nW,(nRow+1)*nH));     //绘制背景矩形
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(mFBackcolor);             //背景框的背景色
    pFramRect->SetLineColor(mFBorderColor);           //背景框的边框色
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetName("mFramRect");
    pFramRect->SetAlpha(alpha);
    pTempItem->addToGroup(pFramRect);                    //添加到组

    /*QPainterPath mPath1;
    mMoveX = 0;
    mMoveY = 0;
    mLineX = nW;
    mLineY = 0;
    mPath1.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath1.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath1);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->addToGroup(pLine);                   //添加到组

    QPainterPath mPath2;
    mMoveX = 0;
    mMoveY = nTotalH;
    mLineX = nW;
    mLineY = nTotalH;
    mPath2.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath2.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath2);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->addToGroup(pLine);                   //添加到组

    QPainterPath mPath3;
    mMoveX = 0;
    mMoveY = 0;
    mLineX = 0;
    mLineY = nTotalH;
    mPath3.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath3.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath3);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->addToGroup(pLine);                   //添加到组

    QPainterPath mPath4;
    mMoveX = nW;
    mMoveY = 0;
    mLineX = nW;
    mLineY = nTotalH;
    mPath4.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath4.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath4);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->addToGroup(pLine);                   //添加到组*/

    //画标题列
    rect.setWidth(nW);                                //绘制标题列
    rect.setHeight(nH);
    QRectItem *pTitleRect = new QRectItem(rect);
    pTitleRect->SetBackColor(mTBackColor);            //标题列矩形框背景色
    pTitleRect->SetLineType(0);
    pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTitleRect->SetName("mTitleRect");
    pTitleRect->SetAlpha(alpha);
    pTempItem->addToGroup(pTitleRect);                   //添加到组

    //画标题文本
    if(bIfNumber)
    {
        //nValue = nUseCount + 1;
        if(nshow > 3)//3个以上要画的
        {
            nValue = nUseCount + 1 + 3 + 1;
        }
        else
        {
            nValue = nUseCount + 1 + nshow;
        }
        i = 1;
    }
    else
    {
        //nValue = nUseCount;
        if(nshow > 3)
        {
            nValue = nUseCount + 3 + 1;
        }
        else
        {
            nValue = nUseCount + nshow;
        }
        i = 0;
    }
    nTexeW = nW/nValue;//nUseCount; //文本平均宽度

    if(1 == i)//画序号
    {
        rect.setTopLeft(QPointF(0,0));           //绘制文本pText
        rect.setSize(QSize(nTexeW,nH));

        //if(bIfNumber)此时这句话一定成立
        pText = new QSimpleTextItem(rect,page1->m_vecHisText[iLan].m_sTitleNumber);

        pText->SetFontSize(nTFontSize);
        pText->SetFontName(sTFont);
        pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName(QString("Text0"));
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pText->SetAlpha(alpha);
        pTempItem->addToGroup(pText);
    }
    for(i; i < nValue;i++)// for(i = 0; i < nUseCount;i++)
    {
        rect.setTopLeft(QPointF(i*nTexeW,0));           //绘制文本pText
        rect.setSize(QSize(nTexeW,nH));
        //pText = new QSimpleTextItem(rect,sDataName.at(i));
        if(bIfNumber)
            pText = new QSimpleTextItem(rect,sDataName.at(i-1));
        else
            pText = new QSimpleTextItem(rect,sDataName.at(i));
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(sTFont);
        pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName(QString("Text%1").arg(i));
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pText->SetAlpha(alpha);
        pTempItem->addToGroup(pText);                   //添加到组
    }

    //画水平线
    if(bIfHorizon)   //选中了水平选择框
    {
        for(i = 0; i < nRow; i++)
        {
            QPainterPath mPath;
            mMoveX = 0;
            mMoveY = i*nH+nH;
            mLineX = 0+nW;
            mLineY = i*nH+nH;
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            pLine->setLineColor(mLineColor);     //设置直线颜色
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "HLine"+sName;
            pLine->SetName(sName);
            //pLine->setAlpha(alpha);
            pTempItem->addToGroup(pLine);                   //添加到组

            if(bIfNumber)
            {
                rect.setTopLeft(QPointF(0, (i+1)*nH));           //绘制文本pText
                rect.setSize(QSize(nTexeW,nH));
                pText = new QSimpleTextItem(rect,QString("%1").arg(i+1));
                pText->SetFontSize(nTFontSize);
                pText->SetFontName(tr("Droid Sans Fallback"));
                //pText->SetFontColor(mTTextColor); //字体颜色
                pText->SetName(QString("NoText%1").arg(i + 1));
                pText->SetRectOutLine(false);
                pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
                pText->SetAlpha(alpha);
                pTempItem->addToGroup(pText);                   //添加到组
            }
        }
    }

    //画垂直线
    if(bIfVertical)  //选中了垂直
    {
        for(i = 1; i < nValue; i++) //nUseCount
        {
            QPainterPath mPath;
            mMoveX = nTexeW*i;
            mMoveY = 0;
            mLineX = nTexeW*i;
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            pLine->setLineColor(mLineColor);     //设置直线颜色
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "VLine"+sName;
            pLine->SetName(sName);
            //pLine->setAlpha(alpha);
            pTempItem->addToGroup(pLine);                   //添加到组
        }

        int k = 0;
        if(bIfNumber)
        {
            k++;
        }
        QTime tm;
        QString strTime;
        QDate dt;
        QString strDate;
        tm = QTime::currentTime();
        dt = QDate::currentDate();
        if(page1->m_eTimeFormat == HHMM_COLON)
        {
            strTime = tm.toString("hh:mm");
        }
        else if(page1->m_eTimeFormat == HHMMSS_COLON)
        {
            strTime = tm.toString("hh:mm:ss");
        }
        else if(page1->m_eTimeFormat == HHMM_ACROSS)
        {
            strTime = tm.toString("hh-mm");
        }
        else
        {
            strTime = tm.toString("hh-mm-ss");
        }

        if(page1->m_eDateFormat == YYYYMMDD_SLASH)
        {
            strDate = dt.toString("yyyy/MM/dd");
        }
        else if(page1->m_eDateFormat == YYYYMMDD_POINT)
        {
            strDate = dt.toString("yyyy.MM.dd");
        }
        else if(page1->m_eDateFormat == YYYYMMDD_ACROSS)
        {
            strDate = dt.toString("yyyy-MM-dd");
        }
        else if(page1->m_eDateFormat == MMDDYYYY_SLASH)
        {
            strDate = dt.toString("MM/dd/yyyy");
        }
        else if(page1->m_eDateFormat == MMDDYYYY_POINT)
        {
            strDate = dt.toString("MM.dd.yyyy");
        }
        else if(page1->m_eDateFormat == MMDDYYYY_ACROSS)
        {
            strDate = dt.toString("MM-dd-yyyy");
        }
        else if(page1->m_eDateFormat == DDMMYYYY_SLASH)
        {
            strDate = dt.toString("dd/MM/yyyy");
        }
        else if(page1->m_eDateFormat == DDMMYYYY_ACROSS)
        {
            strDate = dt.toString("dd-MM-yyyy");
        }
        else
        {
            strDate = dt.toString("dd.MM.yyyy");
        }

        if(bIfTime && bIfDate)
        {
            rect.setTopLeft(QPointF(nTexeW * k, nH));           //绘制文本pText
            rect.setSize(QSize(nTexeW,nH));
            pText = new QSimpleTextItem(rect,strTime);
            pText->SetFontSize(nTextfSize);
            pText->SetFontName(tr("Droid Sans Fallback"));
            pText->SetFontColor(nTextColor); //字体颜色
            pText->SetName(QString("NoText%1").arg(i));
            pText->SetRectOutLine(false);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pText->SetAlpha(alpha);
            pTempItem->addToGroup(pText);                   //添加到组

            //--------------------------------------------------------------
            k++;
            rect.setTopLeft(QPointF(nTexeW * k, nH));           //绘制文本pText
            rect.setSize(QSize(nTexeW,nH));
            pText = new QSimpleTextItem(rect,strDate);
            pText->SetFontSize(nTextfSize);
            pText->SetFontName(tr("Droid Sans Fallback"));
            pText->SetFontColor(nTextColor); //字体颜色
            pText->SetName(QString("NoText%1").arg(i));
            pText->SetRectOutLine(false);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pText->SetAlpha(alpha);
            pTempItem->addToGroup(pText);                   //添加到组
        }
        else if(bIfTime && !bIfDate)
        {
            rect.setTopLeft(QPointF(nTexeW * k, nH));           //绘制文本pText
            rect.setSize(QSize(nTexeW,nH));
            pText = new QSimpleTextItem(rect,strTime);
            pText->SetFontSize(nTextfSize);
            pText->SetFontName(tr("Droid Sans Fallback"));
            pText->SetFontColor(nTextColor); //字体颜色
            pText->SetName(QString("NoText%1").arg(i));
            pText->SetRectOutLine(false);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pText->SetAlpha(alpha);
            pTempItem->addToGroup(pText);                   //添加到组
        }
        else if(!bIfTime && bIfDate)
        {
            rect.setTopLeft(QPointF(nTexeW * k, nH));           //绘制文本pText
            rect.setSize(QSize(nTexeW,nH));
            pText = new QSimpleTextItem(rect,strDate);
            pText->SetFontSize(nTextfSize);
            pText->SetFontName(tr("Droid Sans Fallback"));
            pText->SetFontColor(nTextColor); //字体颜色
            pText->SetName(QString("NoText%1").arg(i));
            pText->SetRectOutLine(false);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pText->SetAlpha(alpha);
            pTempItem->addToGroup(pText);                   //添加到组
        }
    }

    QPainterPath mPath1;
    mMoveX = 0;
    mMoveY = 0;
    mLineX = nW;
    mLineY = 0;
    mPath1.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath1.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath1);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->addToGroup(pLine);                   //添加到组

    QPainterPath mPath2;
    mMoveX = 0;
    mMoveY = nTotalH;
    mLineX = nW;
    mLineY = nTotalH;
    mPath2.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath2.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath2);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->addToGroup(pLine);                   //添加到组

    QPainterPath mPath3;
    mMoveX = 0;
    mMoveY = 0;
    mLineX = 0;
    mLineY = nTotalH;
    mPath3.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath3.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath3);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->addToGroup(pLine);                   //添加到组

    QPainterPath mPath4;
    mMoveX = nW;
    mMoveY = 0;
    mLineX = nW;
    mLineY = nTotalH;
    mPath4.moveTo(mMoveX,mMoveY);         //画直线的起点
    mPath4.lineTo(mLineX,mLineY);         //画直线的终点
    pLine = new QLineItem(mPath4);        //画细直线
    pLine->setLineColor(mFBorderColor);     //设置直线颜色
    pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->addToGroup(pLine);                   //添加到组

    if(pScene)
    {
        pScene->addItem(pTempItem);        //添加到场景
    }

    pTempItem->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTempItem->setFlag(QGraphicsItem::ItemIsMovable, false);
}
