#include "qalarmcontroldlg.h"

#include "view/qrectitem.h"
#include "view/qlineitem.h"
#include "view/qsimpletextitem.h"
#include "Frame/ThingDlg/qalarmcontrolgendlg.h"
#include "Frame/mainwindow.h"
#include <QGraphicsItemGroup>
extern MainWindow *pwnd;

QAlarmControlDlg::QAlarmControlDlg(QGraphicsItem *item,QWidget *parent) :
        QDialog(parent)
{
    tabWidget = new QTabWidget();

    pGeneralDlg = new QAlarmControlGenDlg;
    pVisibilityDlg = new SecurityWidget(this);;
    tabWidget->addTab(pGeneralDlg, tr("一般"));
    //把报警控件没有的控件隐藏
    pGeneralDlg->ui->If_Use_Control_Add->setHidden(true);
    pGeneralDlg->on_If_Use_Control_Add_clicked(false);
    pGeneralDlg->ui->If_Clean_Alarm_Data->setHidden(true);
    pGeneralDlg->ui->If_Clean_Alarm_Time->setHidden(true);

    pGeneralDlg->ui->label_10->setHidden(true);
    pGeneralDlg->ui->label_11->setHidden(true);
    pGeneralDlg->ui->Clear_Alarm_Color->setHidden(true);
    pGeneralDlg->ui->Receive_Note_Color->setHidden(true);
    pGeneralDlg->ui->IFNO->setHidden(true);
    tabWidget->addTab(pVisibilityDlg , tr("显现"));

    datalist = new QStringList();
    int i = 0;
    for (i=0; i < 100; i++)
    {
        datalist->append("");
    }

    //pGeneralDlg->ui->ID->setText(pwnd->GetControlNO("AD"));

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("确定"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("取消"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("帮助"),QDialogButtonBox::HelpRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));

    // connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    //connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    this->setWindowTitle(tr("报警显示器"));
    InitAllProperty(item);

    this->resize(610,520);
}
QAlarmControlDlg::~QAlarmControlDlg()
{
    if(pGeneralDlg)
    {
        delete pGeneralDlg;
        pGeneralDlg = NULL;
    }
    if(pVisibilityDlg)
    {
        delete pVisibilityDlg;
        pVisibilityDlg = NULL;
    }
    if(mainLayout)
    {
        delete mainLayout;
        mainLayout=NULL;
    }
    if(mainLayout)
    {
        delete mainLayout;
        mainLayout=NULL;
    }
    if(tabWidget)
    {
        delete tabWidget;
        tabWidget=NULL;
    }
    datalist->clear();
    delete datalist;
}
void QAlarmControlDlg::InitAllProperty(QGraphicsItem *pItem)
{
	AlarmItem *alarmitem = dynamic_cast<AlarmItem*>(pItem);
    if (alarmitem)//打开一个已有的位按钮
    {
        pGeneralDlg->Init(alarmitem);//初始化一般页面
        pVisibilityDlg->init(alarmitem);
    }
    else//新建
    {
        pGeneralDlg->Init(NULL);//初始化一般页面
        pVisibilityDlg->init(NULL);
    }

}
void QAlarmControlDlg::accept()
{
	if(pVisibilityDlg->Save())
	{
		pGeneralDlg->AlarmControlGenSave();

		pCopyItem->alarmPro = pGeneralDlg->alarmPro;
		DrawTable();
		QDialog::accept();
	}

}

void QAlarmControlDlg::DrawTable()
{
    int i = 0;
    int nVal = 0;
    double mMoveX = 0;                //主刻度X起始点
    double mMoveY = 0;                //主刻度Y起始点
    double mLineX = 0;                //主刻度X起始点
    double mLineY = 0;                //主刻度Y起始点
    AlarmItem *pGroup = new AlarmItem;


    /**************************取一般页面画图的属性*****************************/
    QColor mFBackcolor = pGeneralDlg->ui->m_fbackcolorbtn->palette().background().color();         //框架的背景色
    QColor mFBorderColor = pGeneralDlg->ui->m_fframcolorbtn->palette().background().color();     //框架的边框色
    //bool bIfVertical = pGeneralDlg->ui->m_verticalcheck->checkState(); //是否垂直显示
    //bool bIfHorizon = pGeneralDlg->ui->m_horizontalcheck->checkState();//是否水平
    //QColor mLineColor = pGeneralDlg->ui->m_linecolorbtn->palette().background().color();           //格线颜色

    int nLanguageCount = pGeneralDlg->ui->m_languagecmb->count();      //语言总数
    int iLan = pwnd->qLanguagecmb->currentIndex();
    if(iLan < 0)
        iLan = 0;
    nVal = pGeneralDlg->TitleText[iLan].nFontSize;
    for(i = 1;i < nLanguageCount;i++)                                  //求最大的字体大小
    {
        if(nVal <  pGeneralDlg->TitleText[i].nFontSize)
            nVal =  pGeneralDlg->TitleText[i].nFontSize;
    }
    int nTFontSize = pGeneralDlg->TitleText[iLan].nFontSize;              //以语言1字体大小
    QString sTFont = pGeneralDlg->TitleText[iLan].sFont;                  //以语言1的字体
    QColor mTBackColor = pGeneralDlg->ui->m_tbackcolorbtn->palette().background().color();         //标题列背景色
    QColor mTTextColor = pGeneralDlg->ui->m_ttextcolorbtn->palette().background().color();         //标题列的文本颜色
    bool bIfTime = pGeneralDlg->ui->m_timecheck->checkState();         //是否显示时间列
    QString sTime = pGeneralDlg->TitleText[iLan].sTime;                   //以语言1显示时间内容
    bool bIfDate = pGeneralDlg->ui->m_datecheck->checkState();         //是否显示日期列
    QString sDate = pGeneralDlg->TitleText[iLan].sDate;                   //以语言1显示日期内容
    QString sMsg = pGeneralDlg->TitleText[iLan].sMessage;                 //标题列消息
    int nRow = pGeneralDlg->ui->m_rowspin->value();                    //行数

    int nH = 25;       //每格的高度 10
    int nW = 480;      //背景框的总宽度120
    int nTexeW = 120;   //文本的宽度30
    QString sName = "";
    QLineItem *pLine;

    /**************************画背景矩形*****************************/
    QRectF rect(QPointF(0,0), QSize(nW,(nRow+1)*nH));     //绘制背景矩形
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(mFBackcolor);             //背景框的背景色
    pFramRect->SetLineColor(mFBorderColor);           //背景框的边框色
    pFramRect->setZValue(1);
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetName("mFramRect");
    pGroup->addToGroup(pFramRect);                    //添加到组

    /**************************画标题列******************************/
    rect.setWidth(nW);                                //绘制标题列
    rect.setHeight(nH);
    QRectItem *pTitleRect = new QRectItem(rect);
    pTitleRect->SetBackColor(mTBackColor);            //标题列矩形框背景色
    pTitleRect->SetLineType(0);
    pTitleRect->setZValue(2);
    pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTitleRect->SetName("mTitleRect");
    pGroup->addToGroup(pTitleRect);                   //添加到组

    /**************************画标题文本*****************************/
    rect.setTopLeft(QPointF(0,0));           //绘制时间文本
    rect.setSize(QSize(nTexeW,nH));
    QSimpleTextItem *pTime = new QSimpleTextItem(rect,sTime);
    pTime->SetFontSize(nTFontSize);
    pTime->SetFontName(sTFont);
    pTime->SetFontColor(mTTextColor); //字体颜色
    pTime->SetName(tr("Time"));
    pTime->SetRectOutLine(false);
    pTime->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTime->setZValue(4);
    pGroup->addToGroup(pTime);                   //添加到组

    rect.setSize(QSize(nTexeW,nH));   //绘制日期文本
    QSimpleTextItem *pDate = new QSimpleTextItem(rect,sDate);
    pDate->SetFontSize(nTFontSize);
    pDate->SetFontName(sTFont);
    pDate->SetFontColor(mTTextColor); //字体颜色
    pDate->SetName(tr("Date"));
    pDate->SetRectOutLine(false);
    pDate->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pDate->setZValue(4);
    pGroup->addToGroup(pDate);                   //添加到组

    rect.setSize(QSize(2*nTexeW,nH));   //绘制消息文本
    QSimpleTextItem *pMsg = new QSimpleTextItem(rect,sMsg);
    pMsg->SetFontSize(nTFontSize);
    pMsg->SetFontName(sTFont);
    pMsg->SetFontColor(mTTextColor); //字体颜色
    pMsg->SetName(tr("Message"));
    pMsg->SetRectOutLine(false);
    pMsg->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pMsg->setZValue(4);
    pGroup->addToGroup(pMsg);                   //添加到组

    /**************************画水平线******************************/
    //if(bIfHorizon)   //选中了水平选择框
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
            //pLine->setLineColor(mLineColor);     //设置直线颜色
            pLine->setZValue(3);                 //设置层次
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "HLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //添加到组
        }
    }
    /**************************画垂直线******************************/
    //if(bIfVertical)  //选中了垂直
    //{
    if(bIfTime == true && bIfDate == true)         //显示时间日期消息
    {
        //if(bIfVertical)  //选中了垂直
        {
            for(i = 1; i <= 2; i++)
            {
                QPainterPath mPath;
                mMoveX = nTexeW*i;
                mMoveY = 0;
                mLineX = nTexeW*i;
                mLineY = (nRow+1)*nH;
                mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
                mPath.lineTo(mLineX,mLineY);         //画直线的终点
                pLine = new QLineItem(mPath);        //画细直线
                //pLine->setLineColor(mLineColor);     //设置直线颜色
                pLine->setZValue(5);                 //设置层次
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

                sName = QString("%1").arg(i);
                sName = "VLine"+sName;
                pLine->SetName(sName);
                pGroup->addToGroup(pLine);                   //添加到组
            }
        }
        pTime->setPos(0,0);
        pDate->setPos(nTexeW,0);
        pMsg->setPos(nTexeW*2,0);
    }
    else if(bIfTime == true && bIfDate == false)   //显示时间消息
    {
        //if(bIfVertical)  //选中了垂直
        {
            QPainterPath mPath;
            mMoveX = nTexeW;
            mMoveY = 0;
            mLineX = nTexeW;
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            //pLine->setLineColor(mLineColor);     //设置直线颜色
            pLine->setZValue(5);                 //设置层次
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "VLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //添加到组
        }
        pTime->setPos(0,0);
        pDate->setVisible(false);
        pDate->SetText("");
        rect.setSize(QSize(3*nTexeW,nH));
        pMsg->setRect(rect);
        pMsg->setPos(nTexeW,0);
    }
    else if(bIfTime == false && bIfDate == true)   //显示日期消息
    {
        //if(bIfVertical)  //选中了垂直
        {
            QPainterPath mPath;
            mMoveX = nTexeW;
            mMoveY = 0;
            mLineX = nTexeW;
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            //pLine->setLineColor(mLineColor);     //设置直线颜色
            pLine->setZValue(5);                 //设置层次
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "VLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //添加到组
        }
        pTime->setVisible(false);
        pTime->SetText("");
        pDate->setPos(0,0);
        rect.setSize(QSize(3*nTexeW,nH));
        pMsg->setRect(rect);
        pMsg->setPos(nTexeW,0);
    }
    else if(bIfTime == false && bIfDate == false)  //显示消息
    {
        pTime->setVisible(false);
        pDate->setVisible(false);
        pTime->SetText("");
        pDate->SetText("");
        rect.setSize(QSize(4*nTexeW,nH));
        pMsg->setRect(rect);
        pMsg->setPos(0,0);
    }
    pCopyItem = pGroup;
    pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_ALARMCONTROL));
    pCopyItem->setData(GROUP_DATALIST_KEY,*datalist);    
}

void QAlarmControlDlg::loadHelp()
{
    pwnd->loadHelpHtm(GROUP_TYPE_ALARMCONTROL);
}
