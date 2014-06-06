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
        setWindowTitle(tr("������ʾ��"));
    }
    else
    {
        setWindowTitle(tr("��ʷ������ʾ��"));
    }
    QSize sz = size();
    setFixedSize(sz);//��ֹ�ϷŴ��ڴ�С

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
    btn->setText(tr("ȷ��"));

    btn = ui->buttonBox->button(QDialogButtonBox::Cancel);
    btn->setText(tr("ȡ��"));

    btn = ui->buttonBox->button(QDialogButtonBox::Help);
    btn->setText(tr("����"));

    pAlarmListGen=new QAlarmControlGenDlg(this);
    pSecurityWight=new SecurityWidget(this);
    ui->tabWidget->addTab(pAlarmListGen, tr("��������"));
	//�ѱ����ؼ�û�еĿؼ�����
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
	

    ui->tabWidget->addTab(pSecurityWight, tr("Ȩ������"));
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
    if (item)//��һ�����е�λ��ť
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
            if(sName.contains("VLine")) //��ֱ��
            {
                vVLine.append(pos.x());
            }
            if(sName.contains("HLine")) //ˮƽ��
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

        //��ֱ��
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
        pAlarmListGen->Init(alarmItem);//��ʼ��һ��ҳ��
        pSecurityWight->init(alarmItem);//��ʼ����ʾҳ��
    }
    else//�½�
    {
        pAlarmListGen->Init(NULL);//��ʼ��һ��ҳ��
        pSecurityWight->init(NULL);//��ʼ��Ȩ��ҳ��
        ui->spinBox->setValue(pwnd->getNewId());
    }
    //pSecurityWight->setTouchDisable(true);

}

void AlarmListDlg::DrawTable()
{
    int i = 0;
    int nVal = 0;
    double mMoveX = 0;                //���̶�X��ʼ��
    double mMoveY = 0;                //���̶�Y��ʼ��
    double mLineX = 0;                //���̶�X��ʼ��
    double mLineY = 0;                //���̶�Y��ʼ��
    QItemGroup *pGroup = NULL;
	
	if (alarmType == 1)
	{
		pGroup = new AlarmItem;
	}
	else
	{
		pGroup = new HisAlarmItem;
	}

    /**************************ȡһ��ҳ�滭ͼ������*****************************/
    QColor mFBackcolor = pAlarmListGen->ui->m_fbackcolorbtn->palette().background().color();         //��ܵı���ɫ
    QColor mFBorderColor = pAlarmListGen->ui->m_fframcolorbtn->palette().background().color();     //��ܵı߿�ɫ
    bool bIfVertical = true; //�Ƿ�ֱ��ʾ
    bool bIfHorizon = true;//�Ƿ�ˮƽ
    QColor mLineColor = QColor(192,192,192);           //������ɫ

    int nLanguageCount = pAlarmListGen->ui->m_languagecmb->count();      //��������
    int iLan = pwnd->qLanguagecmb->currentIndex();
    if(iLan < 0)
        iLan = 0;
    nVal = pAlarmListGen->TitleText[iLan].nFontSize;
    for(i = 1;i < nLanguageCount;i++)                                  //�����������С
    {
        if(nVal <  pAlarmListGen->TitleText[i].nFontSize)
            nVal =  pAlarmListGen->TitleText[i].nFontSize;
    }
    int nTFontSize = pAlarmListGen->TitleText[iLan].nFontSize;              //������1�����С
    QString sTFont = pAlarmListGen->TitleText[iLan].sFont;                  //������1������
    QColor mTBackColor = pAlarmListGen->ui->m_tbackcolorbtn->palette().background().color();         //�����б���ɫ
    QColor mTTextColor = pAlarmListGen->ui->m_ttextcolorbtn->palette().background().color();         //�����е��ı���ɫ
    bool bIfTime = pAlarmListGen->ui->m_timecheck->checkState();         //�Ƿ���ʾʱ����
    QString sTime = pAlarmListGen->TitleText[iLan].sTime;                   //������1��ʾʱ������
    bool bIfDate = pAlarmListGen->ui->m_datecheck->checkState();         //�Ƿ���ʾ������
    QString sDate = pAlarmListGen->TitleText[iLan].sDate;                   //������1��ʾ��������
    QString sMsg = pAlarmListGen->TitleText[iLan].sMessage;                 //��������Ϣ
    int nRow = pAlarmListGen->ui->m_rowspin->value();                    //����

    int nH = 25;       //ÿ��ĸ߶� 10
    int nW = 480;      //��������ܿ��120
    int nTexeW = 120;   //�ı��Ŀ��30
    QString sName = "";
    QLineItem *pLine;

    /**************************����������*****************************/
    QRectF rect(QPointF(0,0), QSize(nW,(nRow+1)*nH));     //���Ʊ�������
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(mFBackcolor);             //������ı���ɫ
    pFramRect->SetLineColor(mFBorderColor);           //������ı߿�ɫ
    pFramRect->setZValue(1);
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetName("mFramRect");
    pGroup->addToGroup(pFramRect);                    //��ӵ���

    /**************************��������******************************/
    rect.setWidth(nW);                                //���Ʊ�����
    rect.setHeight(nH);
    QRectItem *pTitleRect = new QRectItem(rect);
    pTitleRect->SetBackColor(mTBackColor);            //�����о��ο򱳾�ɫ
    pTitleRect->SetLineType(0);
    pTitleRect->setZValue(2);
    pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTitleRect->SetName("mTitleRect");
    pGroup->addToGroup(pTitleRect);                   //��ӵ���

    /**************************�������ı�*****************************/
    rect.setTopLeft(QPointF(0,0));           //����ʱ���ı�
    rect.setSize(QSize(nTexeW,nH));
    QSimpleTextItem *pTime = new QSimpleTextItem(rect,sTime);
    pTime->SetFontSize(nTFontSize);
    pTime->SetFontName(sTFont);
    pTime->SetFontColor(mTTextColor); //������ɫ
    pTime->SetName(tr("Time"));
    pTime->SetRectOutLine(false);
    pTime->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTime->setZValue(4);
    pGroup->addToGroup(pTime);                   //��ӵ���

    rect.setSize(QSize(nTexeW,nH));   //���������ı�
    QSimpleTextItem *pDate = new QSimpleTextItem(rect,sDate);
    pDate->SetFontSize(nTFontSize);
    pDate->SetFontName(sTFont);
    pDate->SetFontColor(mTTextColor); //������ɫ
    pDate->SetName(tr("Date"));
    pDate->SetRectOutLine(false);
    pDate->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pDate->setZValue(4);
    pGroup->addToGroup(pDate);                   //��ӵ���

    rect.setSize(QSize(2*nTexeW,nH));   //������Ϣ�ı�
    QSimpleTextItem *pMsg = new QSimpleTextItem(rect,sMsg);
    pMsg->SetFontSize(nTFontSize);
    pMsg->SetFontName(sTFont);
    pMsg->SetFontColor(mTTextColor); //������ɫ
    pMsg->SetName(tr("Message"));
    pMsg->SetRectOutLine(false);
    pMsg->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pMsg->setZValue(4);
    pGroup->addToGroup(pMsg);                   //��ӵ���

    /**************************��ˮƽ��******************************/
    if(bIfHorizon)   //ѡ����ˮƽѡ���
    {
        for(i = 0; i < nRow; i++)
        {
            QPainterPath mPath;
            mMoveX = 0;
            mMoveY = i*nH+nH;
            mLineX = 0+nW;
            mLineY = i*nH+nH;
            mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
            mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
            pLine = new QLineItem(mPath);        //��ϸֱ��
            pLine->setLineColor(mLineColor);     //����ֱ����ɫ
            pLine->setZValue(3);                 //���ò��
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "HLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //��ӵ���
        }
    }
    /**************************����ֱ��******************************/
    //if(bIfVertical)  //ѡ���˴�ֱ
    //{
    if(bIfTime == true && bIfDate == true)         //��ʾʱ��������Ϣ
    {
        if(bIfVertical)  //ѡ���˴�ֱ
        {
            for(i = 1; i <= 2; i++)
            {
                QPainterPath mPath;
                mMoveX = nTexeW*i;
                mMoveY = 0;
                mLineX = nTexeW*i;
                mLineY = (nRow+1)*nH;
                mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
                mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
                pLine = new QLineItem(mPath);        //��ϸֱ��
                pLine->setLineColor(mLineColor);     //����ֱ����ɫ
                pLine->setZValue(5);                 //���ò��
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

                sName = QString("%1").arg(i);
                sName = "VLine"+sName;
                pLine->SetName(sName);
                pGroup->addToGroup(pLine);                   //��ӵ���
            }
        }
        pTime->setPos(0,0);
        pDate->setPos(nTexeW,0);
        pMsg->setPos(nTexeW*2,0);
    }
    else if(bIfTime == true && bIfDate == false)   //��ʾʱ����Ϣ
    {
        if(bIfVertical)  //ѡ���˴�ֱ
        {
            QPainterPath mPath;
            mMoveX = nTexeW;
            mMoveY = 0;
            mLineX = nTexeW;
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
            mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
            pLine = new QLineItem(mPath);        //��ϸֱ��
            pLine->setLineColor(mLineColor);     //����ֱ����ɫ
            pLine->setZValue(5);                 //���ò��
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "VLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //��ӵ���
        }
        pTime->setPos(0,0);
        pDate->setVisible(false);
        pDate->SetText("");
        rect.setSize(QSize(3*nTexeW,nH));
        pMsg->setRect(rect);
        pMsg->setPos(nTexeW,0);
    }
    else if(bIfTime == false && bIfDate == true)   //��ʾ������Ϣ
    {
        if(bIfVertical)  //ѡ���˴�ֱ
        {
            QPainterPath mPath;
            mMoveX = nTexeW;
            mMoveY = 0;
            mLineX = nTexeW;
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
            mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
            pLine = new QLineItem(mPath);        //��ϸֱ��
            pLine->setLineColor(mLineColor);     //����ֱ����ɫ
            pLine->setZValue(5);                 //���ò��
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "VLine"+sName;
            pLine->SetName(sName);
            pGroup->addToGroup(pLine);                   //��ӵ���
        }
        pTime->setVisible(false);
        pTime->SetText("");
        pDate->setPos(0,0);
        rect.setSize(QSize(3*nTexeW,nH));
        pMsg->setRect(rect);
        pMsg->setPos(nTexeW,0);
    }
    else if(bIfTime == false && bIfDate == false)  //��ʾ��Ϣ
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
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID�ظ������޸�ID��"),
                            0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
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
	double mMoveX = 0;                //���̶�X��ʼ��
	double mMoveY = 0;                //���̶�Y��ʼ��
	double mLineX = 0;                //���̶�X��ʼ��
	double mLineY = 0;                //���̶�Y��ʼ��
	QItemGroup *pGroup = NULL;

	if (alarmType == 1)
	{
		pGroup = new AlarmItem;
	}
	else
	{
		pGroup = new HisAlarmItem;
	}

	/**************************ȡһ��ҳ�滭ͼ������*****************************/
	QColor mFBackcolor = pAlarmListGen->ui->m_fbackcolorbtn->palette().background().color();         //��ܵı���ɫ
	QColor mFBorderColor = pAlarmListGen->ui->m_fframcolorbtn->palette().background().color();     //��ܵı߿�ɫ
	bool bIfVertical = true; //�Ƿ�ֱ��ʾ
	bool bIfHorizon = true;//�Ƿ�ˮƽ
	QColor mLineColor = QColor(192,192,192);           //������ɫ

	int nLanguageCount = pAlarmListGen->ui->m_languagecmb->count();      //��������
    int iLan = pAlarmListGen->ui->m_languagecmb->currentIndex();
	if(iLan < 0)
		iLan = 0;

	nVal = pAlarmListGen->TitleText[iLan].nFontSize;
	for(i = 1;i < nLanguageCount;i++)                                  //�����������С
	{
		if(nVal <  pAlarmListGen->TitleText[i].nFontSize)
			nVal =  pAlarmListGen->TitleText[i].nFontSize;
	}
	int nTFontSize = pAlarmListGen->TitleText[iLan].nFontSize;              //������1�����С
	QString sTFont = pAlarmListGen->TitleText[iLan].sFont;                  //������1������
	QColor mTBackColor = pAlarmListGen->ui->m_tbackcolorbtn->palette().background().color();         //�����б���ɫ
	QColor mTTextColor = pAlarmListGen->ui->m_ttextcolorbtn->palette().background().color();         //�����е��ı���ɫ
	bool bIfTime = pAlarmListGen->ui->m_timecheck->checkState();         //�Ƿ���ʾʱ����
	QString sTime = pAlarmListGen->TitleText[iLan].sTime;                   //������1��ʾʱ������
	bool bIfDate = pAlarmListGen->ui->m_datecheck->checkState();         //�Ƿ���ʾ������
	QString sDate = pAlarmListGen->TitleText[iLan].sDate;                   //������1��ʾ��������
	QString sMsg = pAlarmListGen->TitleText[iLan].sMessage;                 //��������Ϣ
	int nRow = pAlarmListGen->ui->m_rowspin->value();                    //����

	bool bClearDate = pAlarmListGen->ui->If_Clean_Alarm_Data->isChecked();
	QString sClearDate = pAlarmListGen->TitleText[iLan].sClearDate;
	bool bClearTime = pAlarmListGen->ui->If_Clean_Alarm_Time->isChecked();
	QString sClearTime = pAlarmListGen->TitleText[iLan].sClearTime;

	bool bIfNumber = pAlarmListGen->ui->IFNO->isChecked(); //�Ƿ�ѡ������ʾ���
	int nValue = 0;
        bool bDoubleClick = false;

	int nH = 25;       //ÿ��ĸ߶� 10
	int nW = 480;      //��������ܿ��120
	int nTexeW = 120;   //�ı��Ŀ��30
        int nTotalH = (nRow+1)*nH;
	QString sName = "";
	QLineItem *pLine;

	/**************************����������*****************************/
	QRectF rect(QPointF(0,0), QSize(nW,(nRow+1)*nH));     //���Ʊ�������
	QRectItem *pFramRect = new QRectItem(rect);
	pFramRect->SetBackColor(mFBackcolor);             //������ı���ɫ
	pFramRect->SetLineColor(mFBorderColor);           //������ı߿�ɫ
	pFramRect->SetName("mFramRect");
	pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
	pGroup->addToGroup(pFramRect);                    //��ӵ���

	/**************************�������ı�*****************************/
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
	nTexeW = nW/nValue;//nUseCount; //�ı�ƽ�����

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

        /**************************��������******************************/
        rect.setWidth(nW);                                //���Ʊ�����
        rect.setHeight(nH);
        if(bDoubleClick)
        {
           rect.setHeight(vHLine.at(1)- vHLine.at(0));
        }
        QRectItem *pTitleRect = new QRectItem(rect);
        pTitleRect->SetBackColor(mTBackColor);            //�����о��ο򱳾�ɫ
        pTitleRect->SetLineType(0);
        pTitleRect->SetName("mTitleRect");
        pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pGroup->addToGroup(pTitleRect);                   //��ӵ���

        if(1 == i)//�����
        {
            rect.setTopLeft(QPointF(0,0));           //�����ı�pText
            rect.setSize(QSize(nTexeW,nH));
            if(bDoubleClick)
            {
                rect.setSize(QSize(vVLine.at(1) - vVLine.at(0),vHLine.at(1) - vHLine.at(0)));
            }

            //if(bIfNumber)��ʱ��仰һ������
            pText = new QSimpleTextItem(rect,"");

            pText->SetFontSize(nTFontSize);
            pText->SetFontName(sTFont);
            pText->SetFontColor(mTTextColor); //������ɫ
            pText->SetName("NoText0");
            pText->SetRectOutLine(false);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            //pText->SetAlpha(alpha);
            pGroup->addToGroup(pText);
        }

	for(i; i < nValue;i++)//for(i = 0; i < nValue;i++) //nUseCount
	{
		rect.setTopLeft(QPointF(i*nTexeW,0));           //�����ı�pText
		rect.setSize(QSize(nTexeW,nH));
                if(bDoubleClick)
                {
                    rect.setTopLeft(QPointF(vVLine.at(i),0));           //�����ı�pText
                    rect.setSize(QSize(vVLine.at(i+1)-vVLine.at(i),vHLine.at(1)- vHLine.at(0)));
                }
		if(bIfNumber)
			pText = new QSimpleTextItem(rect,sDataName.at(i-1));
		else
			pText = new QSimpleTextItem(rect,sDataName.at(i));
		pText->SetFontSize(nTFontSize);
		pText->SetFontName(sTFont);
		pText->SetFontColor(mTTextColor); //������ɫ
		pText->SetName(QString("Text%1").arg(i));
		pText->SetRectOutLine(false);
		pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
		pGroup->addToGroup(pText);                   //��ӵ���
	}
	/**************************��ˮƽ��******************************/
	if(bIfHorizon)   //ѡ����ˮƽѡ���
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
			mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
			mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
			pLine = new QLineItem(mPath);        //��ϸֱ��
			pLine->setLineColor(mLineColor);     //����ֱ����ɫ
			pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

			sName = QString("%1").arg(i);
			sName = "HLine"+sName;
			pLine->SetName(sName);
			pGroup->addToGroup(pLine);                   //��ӵ���

			if(bIfNumber)
			{
				rect.setTopLeft(QPointF(0, (i+1)*nH));           //�����ı�pText
				rect.setSize(QSize(nTexeW,nH));
                                if(bDoubleClick)
                                {
                                    rect.setTopLeft(QPointF(0, vHLine.at(i+1)));           //�����ı�pText
                                    rect.setSize(QSize(vVLine.at(1)- vVLine.at(0),vHLine.at(i+2) -vHLine.at(i+1)));
                                }
				pText = new QSimpleTextItem(rect,QString("%1").arg(i+1));
				pText->SetFontSize(nTFontSize);
				pText->SetFontName(sTFont);
				//pText->SetFontColor(mTTextColor); //������ɫ
                                pText->SetName(QString("NoText%1").arg(i + 1));
				pText->SetRectOutLine(false);
				pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
				pGroup->addToGroup(pText);                   //��ӵ���
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
        rect.setTopLeft(QPointF(nTexeW * k, nH));           //�����ı�pText
        rect.setSize(QSize(nTexeW,nH));
        if(bDoubleClick)
        {
            rect.setTopLeft(QPointF(vVLine.at(k), vHLine.at(1)));           //�����ı�pText
            rect.setSize(QSize(vVLine.at(k+1) - vVLine.at(k),vHLine.at(2) - vHLine.at(1)));
        }
        pText = new QSimpleTextItem(rect,strTime);
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(tr("����"));
        //pText->SetFontColor(mTTextColor); //������ɫ
        pText->SetName("DateText1");
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        //pText->SetAlpha(alpha);
        pGroup->addToGroup(pText);                   //��ӵ���

        //--------------------------------------------------------------
        k++;
        rect.setTopLeft(QPointF(nTexeW * k, nH));           //�����ı�pText
        rect.setSize(QSize(nTexeW,nH));
        if(bDoubleClick)
        {
            rect.setTopLeft(QPointF(vVLine.at(k), vHLine.at(1)));           //�����ı�pText
            rect.setSize(QSize(vVLine.at(k+1) - vVLine.at(k),vHLine.at(2) - vHLine.at(1)));
        }
        pText = new QSimpleTextItem(rect,strDate);
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(tr("����"));
        //pText->SetFontColor(mTTextColor); //������ɫ
        pText->SetName("DateText2");
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        //pText->SetAlpha(alpha);
        pGroup->addToGroup(pText);                   //��ӵ���
        k++;
    }
    else if(bIfTime && !bIfDate)
    {
        rect.setTopLeft(QPointF(nTexeW * k, nH));           //�����ı�pText
        rect.setSize(QSize(nTexeW,nH));
        if(bDoubleClick)
        {
            rect.setTopLeft(QPointF(vVLine.at(k), vHLine.at(1)));           //�����ı�pText
            rect.setSize(QSize(vVLine.at(k+1) - vVLine.at(k),vHLine.at(2) - vHLine.at(1)));
        }
        pText = new QSimpleTextItem(rect,strTime);
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(tr("����"));
        //pText->SetFontColor(mTTextColor); //������ɫ
        pText->SetName("DateText1");
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        //pText->SetAlpha(alpha);
        pGroup->addToGroup(pText);                   //��ӵ���
        k++;
    }
    else if(!bIfTime && bIfDate)
    {
        rect.setTopLeft(QPointF(nTexeW * k, nH));           //�����ı�pText
        rect.setSize(QSize(nTexeW,nH));
        if(bDoubleClick)
        {
            rect.setTopLeft(QPointF(vVLine.at(k), vHLine.at(1)));           //�����ı�pText
            rect.setSize(QSize(vVLine.at(k+1) - vVLine.at(k),vHLine.at(2) - vHLine.at(1)));
        }
        pText = new QSimpleTextItem(rect,strDate);
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(tr("����"));
        //pText->SetFontColor(mTTextColor); //������ɫ
        pText->SetName("DateText1");
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        //pText->SetAlpha(alpha);
        pGroup->addToGroup(pText);                   //��ӵ���
        k++;
    }
    for(k; k < nValue; k++)
    {
        rect.setTopLeft(QPointF(nTexeW * k, nH));           //�����ı�pText
        rect.setSize(QSize(nTexeW,nH));
        if(bDoubleClick)
        {
            rect.setTopLeft(QPointF(vVLine.at(k), vHLine.at(1)));           //�����ı�pText
            rect.setSize(QSize(vVLine.at(k+1) - vVLine.at(k),vHLine.at(2) - vHLine.at(1)));
        }
        pText = new QSimpleTextItem(rect,"");
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(tr("����"));
        //pText->SetFontColor(mTTextColor); //������ɫ
        pText->SetName(QString("DateText%1").arg(k));
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pGroup->addToGroup(pText);
    }

	/**************************����ֱ��******************************/
	if(bIfVertical)  //ѡ���˴�ֱ
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
			mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
			mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
			pLine = new QLineItem(mPath);        //��ϸֱ��
			pLine->setLineColor(mLineColor);     //����ֱ����ɫ
			pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

			sName = QString("%1").arg(i);
			sName = "VLine"+sName;
			pLine->SetName(sName);
			pGroup->addToGroup(pLine);                   //��ӵ���
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
        pwnd->loadHelpHtm(SAM_DRAW_GROUP_ALARMITEM);//������ʾ��
    }else{
        pwnd->loadHelpHtm(SAM_DRAW_GROUP_HISALARMITEM);//��ʷ������ʾ��
    }

}
