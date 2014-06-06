#include "alarmlistdlg.h"
#include "ui_alarmlistdlg.h"
#include "view/alarmitem.h"
#include "view/qgroupitem.h"
#include "view/qlineitem.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

AlarmListDlg::AlarmListDlg(QGraphicsItem *pItem,int alarmtype,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlarmListDlg)
{
    ui->setupUi(this);

    oId = -1;
    alarmType = alarmtype;
    if (alarmType == 1)
    {
        setWindowTitle(tr("报警显示器"));
    }
    else
    {
        setWindowTitle(tr("历史报警显示器"));
    }
    QSize sz = size();
    setFixedSize(sz);//禁止拖放窗口大小

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    ui->View->setScene(&scene);
    QPixmap pic(":/standardtool/images/hisAlarm.png");
    scene.addPixmap(pic.scaled(110,110));

    if(pItem && (pItem->type() == SAM_DRAW_OBJECT_GROUP))
    {
        item = dynamic_cast<QItemGroup *> (pItem)->Clone();
    }
    else
        item = NULL;

    QPushButton *btn = ui->buttonBox->button(QDialogButtonBox::Ok);
    btn->setText(tr("确定"));

    btn = ui->buttonBox->button(QDialogButtonBox::Cancel);
    btn->setText(tr("取消"));

    btn = ui->buttonBox->button(QDialogButtonBox::Help);
    btn->setText(tr("帮助"));

    pAlarmListGen=new QAlarmControlGenDlg(this);
    pSecurityWight=new SecurityWidget(this);
    ui->tabWidget->addTab(pAlarmListGen, tr("基本设置"));
	//把报警控件没有的控件隐藏
	if (alarmType == 1)
	{
                pAlarmListGen->ui->If_Use_Control_Add->setVisible(false);
                pAlarmListGen->ui->label_12->setVisible(false);
                pAlarmListGen->ui->Control_Add->setVisible(false);
                pAlarmListGen->ui->Control_Add_Keyboard->setVisible(false);

		pAlarmListGen->on_If_Use_Control_Add_clicked(false);
                pAlarmListGen->ui->If_Clean_Alarm_Data->setEnabled(false);
                pAlarmListGen->ui->If_Clean_Alarm_Time->setEnabled(false);

                pAlarmListGen->ui->label_10->setEnabled(false);
                pAlarmListGen->ui->label_11->setEnabled(false);
                pAlarmListGen->ui->Clear_Alarm_Color->setEnabled(false);
                pAlarmListGen->ui->Receive_Note_Color->setEnabled(false);
                pAlarmListGen->ui->IFNO->setEnabled(false);
	}
	else
	{
        //pAlarmListGen->ui->label_9->setVisible(false);
        pAlarmListGen->ui->btn_groupset->setVisible(false);

	}
	

    ui->tabWidget->addTab(pSecurityWight, tr("权限设置"));
    //pSecurityWight->ui->groupBox_Touch->hide();
    pSecurityWight->setTouchGroupEnabled(alarmType != 1);
    InitAllProperty();
}

AlarmListDlg::~AlarmListDlg()
{
    delete ui;
}
void AlarmListDlg::InitAllProperty()
{
    if (item)//打开一个已有的位按钮
    {
        QList<QGraphicsItem *> list = item->childItems();
        QRectF rect = item->sceneBoundingRect();
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

        QGroupItem groupfunction(item);
        groupfunction.SetWidth(100);
        groupfunction.SetHeigth(100);

        //scene.addItem(item);

		QItemGroup *alarmItem = NULL;
		if (alarmType == 1)
		{
			alarmItem = dynamic_cast<AlarmItem *> (item);
		}
		else
			alarmItem = dynamic_cast<HisAlarmItem *>(item);
        
        //InitUi();

        oId = alarmItem->id();
        ui->spinBox->setValue(oId);
        pAlarmListGen->Init(alarmItem);//初始化一般页面
        pSecurityWight->init(alarmItem);//初始化标示页面
    }
    else//新建
    {
        pAlarmListGen->Init(NULL);//初始化一般页面
        pSecurityWight->init(NULL);//初始化权限页面
        ui->spinBox->setValue(pwnd->getNewId());
    }
    //pSecurityWight->setTouchDisable(true);

}

void AlarmListDlg::DrawTable()
{
    int i = 0;
    int nVal = 0;
    double mMoveX = 0;                //主刻度X起始点
    double mMoveY = 0;                //主刻度Y起始点
    double mLineX = 0;                //主刻度X起始点
    double mLineY = 0;                //主刻度Y起始点
    QItemGroup *pGroup = NULL;
	
	if (alarmType == 1)
	{
		pGroup = new AlarmItem;
	}
	else
	{
		pGroup = new HisAlarmItem;
	}

    /**************************取一般页面画图的属性*****************************/
    QColor mFBackcolor = pAlarmListGen->ui->m_fbackcolorbtn->palette().background().color();         //框架的背景色
    QColor mFBorderColor = pAlarmListGen->ui->m_fframcolorbtn->palette().background().color();     //框架的边框色
    bool bIfVertical = true; //是否垂直显示
    bool bIfHorizon = true;//是否水平
    QColor mLineColor = QColor(192,192,192);           //格线颜色

    int nLanguageCount = pAlarmListGen->ui->m_languagecmb->count();      //语言总数
    int iLan = pwnd->qLanguagecmb->currentIndex();
    if(iLan < 0)
        iLan = 0;
    nVal = pAlarmListGen->TitleText[iLan].nFontSize;
    for(i = 1;i < nLanguageCount;i++)                                  //求最大的字体大小
    {
        if(nVal <  pAlarmListGen->TitleText[i].nFontSize)
            nVal =  pAlarmListGen->TitleText[i].nFontSize;
    }
    int nTFontSize = pAlarmListGen->TitleText[iLan].nFontSize;              //以语言1字体大小
    QString sTFont = pAlarmListGen->TitleText[iLan].sFont;                  //以语言1的字体
    QColor mTBackColor = pAlarmListGen->ui->m_tbackcolorbtn->palette().background().color();         //标题列背景色
    QColor mTTextColor = pAlarmListGen->ui->m_ttextcolorbtn->palette().background().color();         //标题列的文本颜色
    bool bIfTime = pAlarmListGen->ui->m_timecheck->checkState();         //是否显示时间列
    QString sTime = pAlarmListGen->TitleText[iLan].sTime;                   //以语言1显示时间内容
    bool bIfDate = pAlarmListGen->ui->m_datecheck->checkState();         //是否显示日期列
    QString sDate = pAlarmListGen->TitleText[iLan].sDate;                   //以语言1显示日期内容
    QString sMsg = pAlarmListGen->TitleText[iLan].sMessage;                 //标题列消息
    int nRow = pAlarmListGen->ui->m_rowspin->value();                    //行数

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
        if(bIfVertical)  //选中了垂直
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
                pLine->setLineColor(mLineColor);     //设置直线颜色
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
        if(bIfVertical)  //选中了垂直
        {
            QPainterPath mPath;
            mMoveX = nTexeW;
            mMoveY = 0;
            mLineX = nTexeW;
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            pLine->setLineColor(mLineColor);     //设置直线颜色
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
        if(bIfVertical)  //选中了垂直
        {
            QPainterPath mPath;
            mMoveX = nTexeW;
            mMoveY = 0;
            mLineX = nTexeW;
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            pLine->setLineColor(mLineColor);     //设置直线颜色
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
    item = pGroup;
}
void AlarmListDlg::accept()
{
	if(pSecurityWight->Save())
	{
        if(alarmType != 1 && !pAlarmListGen->isAllRight())
        {
            return;
        }
		pAlarmListGen->AlarmControlGenSave();

		
		if (alarmType == 1)
		{
            DrawHisTable();
			AlarmItem *alarmItem = dynamic_cast<AlarmItem *>(item);
			if (alarmItem)
			{
				alarmItem->alarmPro = pAlarmListGen->alarmPro;
				alarmItem->SaveSecurityPro(&(pSecurityWight->sproperty));
			}
            alarmItem->setId(ui->spinBox->value());
		}
		else
		{
			DrawHisTable();
			HisAlarmItem *alarmItem = dynamic_cast<HisAlarmItem *>(item);
			if (alarmItem)
			{
				alarmItem->alarmPro = pAlarmListGen->alarmPro;
				alarmItem->SaveSecurityPro(&(pSecurityWight->sproperty));
			}
            alarmItem->setId(ui->spinBox->value());
		}
        if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
        {
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID重复，请修改ID！"),
                            0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
            box.exec();
            ui->spinBox->setFocus();
            return ;
        }
			
		
		QDialog::accept();
	}
}
void AlarmListDlg::DrawHisTable()
{
	int i = 0;
	int nVal = 0;
	double mMoveX = 0;                //主刻度X起始点
	double mMoveY = 0;                //主刻度Y起始点
	double mLineX = 0;                //主刻度X起始点
	double mLineY = 0;                //主刻度Y起始点
	QItemGroup *pGroup = NULL;

	if (alarmType == 1)
	{
		pGroup = new AlarmItem;
	}
	else
	{
		pGroup = new HisAlarmItem;
	}

	/**************************取一般页面画图的属性*****************************/
	QColor mFBackcolor = pAlarmListGen->ui->m_fbackcolorbtn->palette().background().color();         //框架的背景色
	QColor mFBorderColor = pAlarmListGen->ui->m_fframcolorbtn->palette().background().color();     //框架的边框色
	bool bIfVertical = true; //是否垂直显示
	bool bIfHorizon = true;//是否水平
	QColor mLineColor = QColor(192,192,192);           //格线颜色

	int nLanguageCount = pAlarmListGen->ui->m_languagecmb->count();      //语言总数
    int iLan = pAlarmListGen->ui->m_languagecmb->currentIndex();
	if(iLan < 0)
		iLan = 0;

	nVal = pAlarmListGen->TitleText[iLan].nFontSize;
	for(i = 1;i < nLanguageCount;i++)                                  //求最大的字体大小
	{
		if(nVal <  pAlarmListGen->TitleText[i].nFontSize)
			nVal =  pAlarmListGen->TitleText[i].nFontSize;
	}
	int nTFontSize = pAlarmListGen->TitleText[iLan].nFontSize;              //以语言1字体大小
	QString sTFont = pAlarmListGen->TitleText[iLan].sFont;                  //以语言1的字体
	QColor mTBackColor = pAlarmListGen->ui->m_tbackcolorbtn->palette().background().color();         //标题列背景色
	QColor mTTextColor = pAlarmListGen->ui->m_ttextcolorbtn->palette().background().color();         //标题列的文本颜色
	bool bIfTime = pAlarmListGen->ui->m_timecheck->checkState();         //是否显示时间列
	QString sTime = pAlarmListGen->TitleText[iLan].sTime;                   //以语言1显示时间内容
	bool bIfDate = pAlarmListGen->ui->m_datecheck->checkState();         //是否显示日期列
	QString sDate = pAlarmListGen->TitleText[iLan].sDate;                   //以语言1显示日期内容
	QString sMsg = pAlarmListGen->TitleText[iLan].sMessage;                 //标题列消息
	int nRow = pAlarmListGen->ui->m_rowspin->value();                    //行数

	bool bClearDate = pAlarmListGen->ui->If_Clean_Alarm_Data->isChecked();
	QString sClearDate = pAlarmListGen->TitleText[iLan].sClearDate;
	bool bClearTime = pAlarmListGen->ui->If_Clean_Alarm_Time->isChecked();
	QString sClearTime = pAlarmListGen->TitleText[iLan].sClearTime;

	bool bIfNumber = pAlarmListGen->ui->IFNO->isChecked(); //是否选择了显示编号
	int nValue = 0;
        bool bDoubleClick = false;

	int nH = 25;       //每格的高度 10
	int nW = 480;      //背景框的总宽度120
	int nTexeW = 120;   //文本的宽度30
        int nTotalH = (nRow+1)*nH;
	QString sName = "";
	QLineItem *pLine;

	/**************************画背景矩形*****************************/
	QRectF rect(QPointF(0,0), QSize(nW,(nRow+1)*nH));     //绘制背景矩形
	QRectItem *pFramRect = new QRectItem(rect);
	pFramRect->SetBackColor(mFBackcolor);             //背景框的背景色
	pFramRect->SetLineColor(mFBorderColor);           //背景框的边框色
	pFramRect->SetName("mFramRect");
	pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
	pGroup->addToGroup(pFramRect);                    //添加到组

	/**************************画标题文本*****************************/
	QStringList sDataName;
	int nUseCount = 0;
	QSimpleTextItem *pText;

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
	if(bClearDate)
	{
		nUseCount++;
		sDataName.append(sClearDate);
	}
	if(bClearTime)
	{
		nUseCount++;
		sDataName.append(sClearTime);
	}
	sDataName.append(sMsg);
	nUseCount++;

	if(bIfNumber)
	{
		nValue = nUseCount+1;
		i = 1;
	}
	else
	{
		nValue = nUseCount;
		i = 0;
	}
	nTexeW = nW/nValue;//nUseCount; //文本平均宽度

        if(nValue == (vVLine.size() - 1) && nRow == (vHLine.size() - 2))
        {
            bDoubleClick= true;
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

        /**************************画标题列******************************/
        rect.setWidth(nW);                                //绘制标题列
        rect.setHeight(nH);
        if(bDoubleClick)
        {
           rect.setHeight(vHLine.at(1)- vHLine.at(0));
        }
        QRectItem *pTitleRect = new QRectItem(rect);
        pTitleRect->SetBackColor(mTBackColor);            //标题列矩形框背景色
        pTitleRect->SetLineType(0);
        pTitleRect->SetName("mTitleRect");
        pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pGroup->addToGroup(pTitleRect);                   //添加到组

        if(1 == i)//画序号
        {
            rect.setTopLeft(QPointF(0,0));           //绘制文本pText
            rect.setSize(QSize(nTexeW,nH));
            if(bDoubleClick)
            {
                rect.setSize(QSize(vVLine.at(1) - vVLine.at(0),vHLine.at(1) - vHLine.at(0)));
            }

            //if(bIfNumber)此时这句话一定成立
            pText = new QSimpleTextItem(rect,"");

            pText->SetFontSize(nTFontSize);
            pText->SetFontName(sTFont);
            pText->SetFontColor(mTTextColor); //字体颜色
            pText->SetName("NoText0");
            pText->SetRectOutLine(false);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            //pText->SetAlpha(alpha);
            pGroup->addToGroup(pText);
        }

	for(i; i < nValue;i++)//for(i = 0; i < nValue;i++) //nUseCount
	{
		rect.setTopLeft(QPointF(i*nTexeW,0));           //绘制文本pText
		rect.setSize(QSize(nTexeW,nH));
                if(bDoubleClick)
                {
                    rect.setTopLeft(QPointF(vVLine.at(i),0));           //绘制文本pText
                    rect.setSize(QSize(vVLine.at(i+1)-vVLine.at(i),vHLine.at(1)- vHLine.at(0)));
                }
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
		pGroup->addToGroup(pText);                   //添加到组
	}
	/**************************画水平线******************************/
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
			pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

			sName = QString("%1").arg(i);
			sName = "HLine"+sName;
			pLine->SetName(sName);
			pGroup->addToGroup(pLine);                   //添加到组

			if(bIfNumber)
			{
				rect.setTopLeft(QPointF(0, (i+1)*nH));           //绘制文本pText
				rect.setSize(QSize(nTexeW,nH));
                                if(bDoubleClick)
                                {
                                    rect.setTopLeft(QPointF(0, vHLine.at(i+1)));           //绘制文本pText
                                    rect.setSize(QSize(vVLine.at(1)- vVLine.at(0),vHLine.at(i+2) -vHLine.at(i+1)));
                                }
				pText = new QSimpleTextItem(rect,QString("%1").arg(i+1));
				pText->SetFontSize(nTFontSize);
				pText->SetFontName(sTFont);
				//pText->SetFontColor(mTTextColor); //字体颜色
                                pText->SetName(QString("NoText%1").arg(i + 1));
				pText->SetRectOutLine(false);
				pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
				pGroup->addToGroup(pText);                   //添加到组
			}
		}
	}
    int k= 0;
    if(bIfNumber)
    {
        k++;
    }
    QString strTime = this->getDateStr(pAlarmListGen->ui->m_timecmb->currentIndex(),0);
    QString strDate = this->getDateStr(pAlarmListGen->ui->m_datacmb->currentIndex(),1);
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
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(tr("宋体"));
        //pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName("DateText1");
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        //pText->SetAlpha(alpha);
        pGroup->addToGroup(pText);                   //添加到组

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
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(tr("宋体"));
        //pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName("DateText2");
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        //pText->SetAlpha(alpha);
        pGroup->addToGroup(pText);                   //添加到组
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
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(tr("宋体"));
        //pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName("DateText1");
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        //pText->SetAlpha(alpha);
        pGroup->addToGroup(pText);                   //添加到组
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
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(tr("宋体"));
        //pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName("DateText1");
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        //pText->SetAlpha(alpha);
        pGroup->addToGroup(pText);                   //添加到组
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
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(tr("宋体"));
        //pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName(QString("DateText%1").arg(k));
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pGroup->addToGroup(pText);
    }

	/**************************画垂直线******************************/
	if(bIfVertical)  //选中了垂直
	{
		for(i = 1; i < nValue; i++)
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
			pGroup->addToGroup(pLine);                   //添加到组
		}
	}

	item = pGroup;
}

QString AlarmListDlg::getDateStr(int format,int type)
{
    QString sformat;
    if(type == 0)
    {
        switch(format)
        {
        case 0:sformat = "hh:mm";
            break;
        case 1:sformat = "hh:mm:ss";
            break;
        case 2:sformat = "hh-mm";
            break;
        case 3:sformat = "hh-mm-ss";
            break;
        default:sformat = "hh:mm:ss";
            break;
        }
    }
    else
    {
        switch(format)
        {
        case 0:sformat = "yyyy/MM/dd";
            break;
        case 1:sformat = "yyyy.MM.dd";
            break;
        case 2:sformat = "yyyy-MM-dd";
            break;
        case 3:sformat = "MM/dd/yyyy";
            break;
        case 4:sformat = "MM.dd.yyyy";
            break;
        case 5:sformat = "MM-dd-yyyy";
            break;
        case 6:sformat = "dd/MM/yyyy";
            break;
        case 7:sformat = "dd.MM.yyyy";
            break;
        case 8:sformat = "dd-MM-yyyy";
            break;
        default:sformat = "yyyy/MM/dd";

            break;
        }

    }
    QString time = QDateTime::currentDateTime().toString(sformat);
    return time;
}

void AlarmListDlg::on_buttonBox_helpRequested()
{
    if (alarmType == 1){
        pwnd->loadHelpHtm(SAM_DRAW_GROUP_ALARMITEM);//报警显示器
    }else{
        pwnd->loadHelpHtm(SAM_DRAW_GROUP_HISALARMITEM);//历史报警显示器
    }

}
