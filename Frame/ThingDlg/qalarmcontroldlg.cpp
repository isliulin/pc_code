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
    tabWidget->addTab(pGeneralDlg, tr("һ��"));
    //�ѱ����ؼ�û�еĿؼ�����
    pGeneralDlg->ui->If_Use_Control_Add->setHidden(true);
    pGeneralDlg->on_If_Use_Control_Add_clicked(false);
    pGeneralDlg->ui->If_Clean_Alarm_Data->setHidden(true);
    pGeneralDlg->ui->If_Clean_Alarm_Time->setHidden(true);

    pGeneralDlg->ui->label_10->setHidden(true);
    pGeneralDlg->ui->label_11->setHidden(true);
    pGeneralDlg->ui->Clear_Alarm_Color->setHidden(true);
    pGeneralDlg->ui->Receive_Note_Color->setHidden(true);
    pGeneralDlg->ui->IFNO->setHidden(true);
    tabWidget->addTab(pVisibilityDlg , tr("����"));

    datalist = new QStringList();
    int i = 0;
    for (i=0; i < 100; i++)
    {
        datalist->append("");
    }

    //pGeneralDlg->ui->ID->setText(pwnd->GetControlNO("AD"));

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("ȷ��"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("ȡ��"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("����"),QDialogButtonBox::HelpRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));

    // connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    //connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    this->setWindowTitle(tr("������ʾ��"));
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
    if (alarmitem)//��һ�����е�λ��ť
    {
        pGeneralDlg->Init(alarmitem);//��ʼ��һ��ҳ��
        pVisibilityDlg->init(alarmitem);
    }
    else//�½�
    {
        pGeneralDlg->Init(NULL);//��ʼ��һ��ҳ��
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
    double mMoveX = 0;                //���̶�X��ʼ��
    double mMoveY = 0;                //���̶�Y��ʼ��
    double mLineX = 0;                //���̶�X��ʼ��
    double mLineY = 0;                //���̶�Y��ʼ��
    AlarmItem *pGroup = new AlarmItem;


    /**************************ȡһ��ҳ�滭ͼ������*****************************/
    QColor mFBackcolor = pGeneralDlg->ui->m_fbackcolorbtn->palette().background().color();         //��ܵı���ɫ
    QColor mFBorderColor = pGeneralDlg->ui->m_fframcolorbtn->palette().background().color();     //��ܵı߿�ɫ
    //bool bIfVertical = pGeneralDlg->ui->m_verticalcheck->checkState(); //�Ƿ�ֱ��ʾ
    //bool bIfHorizon = pGeneralDlg->ui->m_horizontalcheck->checkState();//�Ƿ�ˮƽ
    //QColor mLineColor = pGeneralDlg->ui->m_linecolorbtn->palette().background().color();           //������ɫ

    int nLanguageCount = pGeneralDlg->ui->m_languagecmb->count();      //��������
    int iLan = pwnd->qLanguagecmb->currentIndex();
    if(iLan < 0)
        iLan = 0;
    nVal = pGeneralDlg->TitleText[iLan].nFontSize;
    for(i = 1;i < nLanguageCount;i++)                                  //�����������С
    {
        if(nVal <  pGeneralDlg->TitleText[i].nFontSize)
            nVal =  pGeneralDlg->TitleText[i].nFontSize;
    }
    int nTFontSize = pGeneralDlg->TitleText[iLan].nFontSize;              //������1�����С
    QString sTFont = pGeneralDlg->TitleText[iLan].sFont;                  //������1������
    QColor mTBackColor = pGeneralDlg->ui->m_tbackcolorbtn->palette().background().color();         //�����б���ɫ
    QColor mTTextColor = pGeneralDlg->ui->m_ttextcolorbtn->palette().background().color();         //�����е��ı���ɫ
    bool bIfTime = pGeneralDlg->ui->m_timecheck->checkState();         //�Ƿ���ʾʱ����
    QString sTime = pGeneralDlg->TitleText[iLan].sTime;                   //������1��ʾʱ������
    bool bIfDate = pGeneralDlg->ui->m_datecheck->checkState();         //�Ƿ���ʾ������
    QString sDate = pGeneralDlg->TitleText[iLan].sDate;                   //������1��ʾ��������
    QString sMsg = pGeneralDlg->TitleText[iLan].sMessage;                 //��������Ϣ
    int nRow = pGeneralDlg->ui->m_rowspin->value();                    //����

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
    //if(bIfHorizon)   //ѡ����ˮƽѡ���
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
            //pLine->setLineColor(mLineColor);     //����ֱ����ɫ
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
        //if(bIfVertical)  //ѡ���˴�ֱ
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
                //pLine->setLineColor(mLineColor);     //����ֱ����ɫ
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
        //if(bIfVertical)  //ѡ���˴�ֱ
        {
            QPainterPath mPath;
            mMoveX = nTexeW;
            mMoveY = 0;
            mLineX = nTexeW;
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
            mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
            pLine = new QLineItem(mPath);        //��ϸֱ��
            //pLine->setLineColor(mLineColor);     //����ֱ����ɫ
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
        //if(bIfVertical)  //ѡ���˴�ֱ
        {
            QPainterPath mPath;
            mMoveX = nTexeW;
            mMoveY = 0;
            mLineX = nTexeW;
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
            mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
            pLine = new QLineItem(mPath);        //��ϸֱ��
            //pLine->setLineColor(mLineColor);     //����ֱ����ɫ
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
    pCopyItem = pGroup;
    pCopyItem->setData(GROUP_TYPE_KEY,QVariant(GROUP_TYPE_ALARMCONTROL));
    pCopyItem->setData(GROUP_DATALIST_KEY,*datalist);    
}

void QAlarmControlDlg::loadHelp()
{
    pwnd->loadHelpHtm(GROUP_TYPE_ALARMCONTROL);
}
