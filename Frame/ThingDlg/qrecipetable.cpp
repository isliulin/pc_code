#include "qrecipetable.h"
#include <QGraphicsItem>
#include "view/qdrawgraphics.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

Qrecipetable::Qrecipetable(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent)
{
    QGraphicsItem *Item = NULL;
    tabWidget = new QTabWidget(this);
    ptab1 = new Qrepicegenaral;
    pSecurityWight = new SecurityWidget;
    tabWidget->addTab(ptab1, tr("һ��"));
    tabWidget->addTab(pSecurityWight, tr("Ȩ������"));
    //pSecurityWight->setTouchGroupEnabled(false);

    buttonBox = new QDialogButtonBox();
    buttonBox->addButton(tr("ȷ��"),QDialogButtonBox::AcceptRole);
    buttonBox->addButton(tr("ȡ��"),QDialogButtonBox::RejectRole);
    buttonBox->addButton(tr("����"),QDialogButtonBox::HelpRole);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(confyButton()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(buttonBox, SIGNAL(helpRequested ()), this, SLOT(loadHelp()));

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    this->setWindowTitle(tr("�䷽������ʾ��"));
    this->setFixedSize(613,513);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    if(pItem)
    {
        Item = dynamic_cast<QRecipeTableItem *> (pItem)->Clone();
        pCopyItem = dynamic_cast<QRecipeTableItem *> (Item);
        InitAllProperty(pCopyItem);
    }
    else
    {
        InitAllProperty(NULL);
        pCopyItem = NULL;
    }
    buttonBox->setFocus();
}

Qrecipetable::~Qrecipetable()
{
    if(pSecurityWight)
    {
        delete pSecurityWight;
        pSecurityWight=NULL;
    }
    if(ptab1)
    {
        delete ptab1;
        ptab1=NULL;
    }
    if(mainLayout)
    {
        delete mainLayout;
        mainLayout=NULL;
    }
    if(buttonBox)
    {
        delete buttonBox;
        buttonBox=NULL;
    }
    if(tabWidget)
    {
        delete tabWidget;
        tabWidget=NULL;
    }
}

void Qrecipetable::InitAllProperty(QRecipeTableItem *pItem)
{
    if (pItem)//��һ�����е�λ��ť
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

        ptab1->Init(pItem);
        pSecurityWight->init(pItem);
    }
    else//�½�
    {
        ptab1->Init(NULL);
    }
}//

void Qrecipetable::confyButton()
{
    //��������ҳ������
    if(!pSecurityWight->Save())
    {
        return;
    }
    drawRecipeDisplay();  //����ͼ��

    pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));

    if(!ptab1->GeneralSave(m_SaveInfo))
    {
        return;
    }

    pCopyItem->SaveInfo(m_SaveInfo);
    pCopyItem->setId(ptab1->getId());


    accept();
}//

void Qrecipetable::loadHelp()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_RECIPESHOW);
}
void Qrecipetable::drawRecipeDisplay()
{
    double mMoveX = 0;                //���̶�X��ʼ��
    double mMoveY = 0;                //���̶�Y��ʼ��
    double mLineX = 0;                //���̶�X��ʼ��
    double mLineY = 0;                //���̶�Y��ʼ��
    int nUseCount = 0;                //����ҳ����ʾ������

    pCopyItem = new QRecipeTableItem;
    /**************************ȡһ��ҳ�滭ͼ������*****************************/
    QColor mFBackcolor = ptab1->GetBackColor();          //��ܵı���ɫ
    QColor mFBorderColor(0,0,0);    //��ܵı߿�ɫ

    int iLan = pwnd->qLanguagecmb->currentIndex();
    if(iLan < 0)
        iLan = 0;

    int nTFontSize = ptab1->GetTitletextSize();              //������1�����С 35
    QString sTFont = ptab1->GetTitletextFont();                  //������1������36
    QColor mTBackColor = ptab1->GetTitleBackColor();        //�����б���ɫ
    QColor mTTextColor = ptab1->GetTitleTextColor();         //�����е��ı���ɫ
    QColor mLineColor = ptab1->GetLineColor();

    int index  = ptab1->GetRecipeIndex();
    int nAligent = ptab1->GetAligentType();
    QString sNo = tr("�䷽����"); //37
    sNo = ptab1->GetRowText();
    int nRow = ptab1->GetRowCount();                 //����
    int nColoum = ptab1->GetColoumCount();           //����
    int nLangID = ptab1->GetLangIndex();
    short nTransparent = ptab1->GetTransparentValue();//͸����

    double nH = 25;       //ÿ��ĸ߶� 25
    double nTotalH = (nRow+1)*nH;//�ܹ��߶�
    double nW = 480;      //��������ܿ��120
    double nTexeW = 0;   //�ı��Ŀ��120
    QString sName = "";
    QLineItem *pLine;
    QSimpleTextItem *pText;
    QStringList sDataName;
    QVector<int> xPos;
    QVector<int> yPos;
    xPos.clear();
    yPos.clear();
    bool bDoubleClick = false;
    /**************************����������*****************************/
    QRectF rect(QPointF(0,0), QSize(nW,(nRow+1)*nH));     //���Ʊ�������
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(mFBackcolor);             //������ı���ɫ
    pFramRect->SetLineColor(mFBorderColor);           //������ı߿�ɫ
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetName("mFramRect");
    pFramRect->SetAlpha(nTransparent);
    pFramRect->SetLineColor(mLineColor);
    pCopyItem->addToGroup(pFramRect);                    //��ӵ���

    if(nColoum == (vVLine.size() - 2) && nRow == (vHLine.size() - 2))
    {
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

        /**************************��������******************************/
        rect.setWidth(nW);                                //���Ʊ�����
        rect.setHeight(vHLine.at(1) - vHLine.at(0));
        QRectItem *pTitleRect = new QRectItem(rect);
        pTitleRect->SetBackColor(mTBackColor);            //�����о��ο򱳾�ɫ
        pTitleRect->SetLineType(0);
        pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pTitleRect->SetName("mTitleRect");
        pTitleRect->SetAlpha(nTransparent);
        pCopyItem->addToGroup(pTitleRect);                   //��ӵ���

        /**************************�������ı�*****************************/
        sDataName.clear();
        sDataName.append(sNo);
        nUseCount++;

        if(ptab1->showIDChecked())
        {
           sDataName.append(tr("ID"));
           nUseCount++;
        }
        if(ptab1->showDeschecked())
        {
           sDataName.append(tr("�䷽����"));
           nUseCount++;
        }

        for(int i = 0;i < pwnd->m_pSamSysParame->m_qvcRecipe[index].ElmentName.size();i++) //RowHeadName[0].size()
        {
            if(nLangID < pwnd->m_pSamSysParame->m_qvcRecipe[index].ElmentName[i].size())
            {
                nUseCount++;
                sDataName.append(pwnd->m_pSamSysParame->m_qvcRecipe[index].ElmentName[i][nLangID].sElemName);//0
            }
        }

        nTexeW = nW/(nColoum + 1); //�ı�ƽ�����
        for(int i = 0; i< nColoum + 1;i++)//for(i = 0; i < nUseCount && i< nColoum + 1;i++)
        {
            qreal nTexeW = vVLine.at(i + 1) - vVLine.at(i);
            rect.setTopLeft(QPointF(vVLine.at(i),0));           //�����ı�pText
            rect.setSize(QSize(nTexeW,vHLine.at(1) - vHLine.at(0)));
            if(i < nUseCount)
                pText = new QSimpleTextItem(rect,sDataName.at(i));
            else
                pText = new QSimpleTextItem(rect,"");
            pText->SetFontSize(nTFontSize);
            pText->SetTextAlign(nAligent);
            pText->SetFontName(sTFont);
            pText->SetFontColor(mTTextColor); //������ɫ
            if(i == 0)
                pText->SetName(QString("NoText%1").arg(i));//�ɡ��䷽���ơ����ı�����ΪNoText0
            else
                pText->SetName(QString("Text%1").arg(i));
            pText->SetRectOutLine(false);
            pText->SetAlpha(nTransparent);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pCopyItem->addToGroup(pText);                   //��ӵ���
        }

        /**************************��������******************************/
        QColor mCBackColor = ptab1->GetRowBackColor();
        rect.setTopLeft(QPointF(0,vHLine.at(1)));
        rect.setSize(QSize(vVLine.at(1) - vVLine.at(0),vHLine.at(vHLine.size()-1) - vHLine.at(1)));
        QRectItem *pColoumRect = new QRectItem(rect);
        pColoumRect->SetBackColor(mCBackColor);            //�����о��ο򱳾�ɫ
        pColoumRect->SetLineType(0);
        pColoumRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pColoumRect->SetName("mCloumRect");
        pColoumRect->SetAlpha(nTransparent);
        pCopyItem->addToGroup(pColoumRect);                   //��ӵ���

        int nCFontSize = ptab1->GetRowtextSize();
        QString sCFont = ptab1->GetRowtextFont();
        QColor mCTextColor = ptab1->GetRowTextColor();
        for(int i = 0; i < nRow; i++)
        {
            QString sName = "";
            if(i < pwnd->m_pSamSysParame->m_qvcRecipe[index].formula.size())
            {
                if(nLangID < pwnd->m_pSamSysParame->m_qvcRecipe[index].formula[i].RecipeInfo.size())
                {
                    sName = pwnd->m_pSamSysParame->m_qvcRecipe[index].formula[i].RecipeInfo[nLangID].sRecipeName;
                }
            }
            rect.setTopLeft(QPointF(0,vHLine.at(i+1)));           //�����ı�pText
            rect.setSize(QSize(vVLine.at(1) - vVLine.at(0),vHLine.at(i+2) -vHLine.at(i+1)));
            pText = new QSimpleTextItem(rect,sName);
            pText->SetFontSize(nCFontSize);
            pText->SetTextAlign(nAligent);
            pText->SetFontName(sCFont);
            pText->SetFontColor(mCTextColor); //������ɫ
            pText->SetName(QString("NoText%1").arg(i+1));
            pText->SetRectOutLine(false);
            pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
            pText->SetAlpha(nTransparent);
            pCopyItem->addToGroup(pText);
        }

        /**************************��ˮƽ��******************************/
      //  if(bIfHorizon)   //ѡ����ˮƽѡ���
       // {
           for(int i = 0; i < nRow + 1; i++)// for(i = 0; i < nRow + 2; i++)
            {
                QPainterPath mPath;
                mMoveX = 0;
                mMoveY = vHLine.at(i);
                mLineX = 0+nW;
                mLineY = vHLine.at(i);
                mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
                mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
                pLine = new QLineItem(mPath);        //��ϸֱ��
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

                sName = QString("%1").arg(i);
                if(i > 0)
                sName = "HLine"+sName;
                pLine->setLineColor(mLineColor);
                pLine->SetName(sName);
                pCopyItem->addToGroup(pLine);                   //��ӵ���
            }
       // }
        /**************************����ֱ��******************************/
      //  if(bIfVertical)  //ѡ���˴�ֱ
     //   {
            for(int i = 0; i < nColoum + 1; i++)//for(i = 0; i < nColoum + 2; i++)
            {
                QPainterPath mPath;
                mMoveX = vVLine.at(i);
                mMoveY = 0;
                mLineX = vVLine.at(i);
                mLineY = (nRow+1)*nH;
                mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
                mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
                pLine = new QLineItem(mPath);        //��ϸֱ��
                pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

                sName = QString("%1").arg(i);
                if( i > 0)
                sName = "VLine"+sName;
                pLine->setLineColor(mLineColor);
                pLine->SetName(sName);
                pCopyItem->addToGroup(pLine);                   //��ӵ���
            }
            return;
    }

    int i = 0;
    /**************************��������******************************/
    rect.setWidth(nW);                                //���Ʊ�����
    rect.setHeight(nH);
    QRectItem *pTitleRect = new QRectItem(rect);
    pTitleRect->SetBackColor(mTBackColor);            //�����о��ο򱳾�ɫ
    pTitleRect->SetLineType(0);
    pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTitleRect->SetName("mTitleRect");
    pTitleRect->SetAlpha(nTransparent);
    pCopyItem->addToGroup(pTitleRect);                   //��ӵ���


    /**************************�������ı�*****************************/
    sDataName.clear();
    sDataName.append(sNo);
    nUseCount++;

    if(ptab1->showIDChecked())
    {
       sDataName.append(tr("ID��"));
       nUseCount++;
    }
    if(ptab1->showDeschecked())
    {
       sDataName.append(tr("�䷽����"));
       nUseCount++;
    }

    for(i = 0;i < pwnd->m_pSamSysParame->m_qvcRecipe[index].ElmentName.size();i++) //RowHeadName[0].size()
    {
        if(nLangID < pwnd->m_pSamSysParame->m_qvcRecipe[index].ElmentName[i].size())
        {
            nUseCount++;
            sDataName.append(pwnd->m_pSamSysParame->m_qvcRecipe[index].ElmentName[i][nLangID].sElemName);//0
        }
    }

    nTexeW = nW/(nColoum + 1); //�ı�ƽ�����
    for(i = 0; i< nColoum + 1;i++)//for(i = 0; i < nUseCount && i< nColoum + 1;i++)
    {
        rect.setTopLeft(QPointF(i*nTexeW,0));           //�����ı�pText
        rect.setSize(QSize(nTexeW,nH));
        if(i < nUseCount)
            pText = new QSimpleTextItem(rect,sDataName.at(i));
        else
            pText = new QSimpleTextItem(rect,"");
        pText->SetFontSize(nTFontSize);
        pText->SetTextAlign(nAligent);
        pText->SetFontName(sTFont);
        pText->SetFontColor(mTTextColor); //������ɫ
        if(i == 0)
            pText->SetName(QString("NoText%1").arg(i));//�ɡ��䷽���ơ����ı�����ΪNoText0
        else
            pText->SetName(QString("Text%1").arg(i));
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pText->SetAlpha(nTransparent);
        pCopyItem->addToGroup(pText);                   //��ӵ���
    }

    /**************************��������******************************/
    QColor mCBackColor = ptab1->GetRowBackColor();
    rect.setTopLeft(QPointF(0,nH));
    rect.setSize(QSize(nTexeW,nH * nRow));
    QRectItem *pColoumRect = new QRectItem(rect);
    pColoumRect->SetBackColor(mCBackColor);            //�����о��ο򱳾�ɫ
    pColoumRect->SetLineType(0);
    pColoumRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pColoumRect->SetName("mCloumRect");
    pColoumRect->SetAlpha(nTransparent);
    pCopyItem->addToGroup(pColoumRect);                   //��ӵ���

    int nCFontSize = ptab1->GetRowtextSize();
    QString sCFont = ptab1->GetRowtextFont();
    QColor mCTextColor = ptab1->GetRowTextColor();
    for(int i = 0; i < nRow; i++)
    {
        QString sName = "";
        if(i < pwnd->m_pSamSysParame->m_qvcRecipe[index].formula.size())
        {
            if(nLangID < pwnd->m_pSamSysParame->m_qvcRecipe[index].formula[i].RecipeInfo.size())
            {
                sName = pwnd->m_pSamSysParame->m_qvcRecipe[index].formula[i].RecipeInfo[nLangID].sRecipeName;
            }
        }
        rect.setTopLeft(QPointF(0,(i+1)*nH));           //�����ı�pText
        rect.setSize(QSize(nTexeW,nH));
        pText = new QSimpleTextItem(rect,sName);
        pText->SetFontSize(nCFontSize);
        pText->SetTextAlign(nAligent);
        pText->SetFontName(sCFont);
        pText->SetFontColor(mCTextColor); //������ɫ
        pText->SetName(QString("NoText%1").arg(i+1));
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pText->SetAlpha(nTransparent);
        pCopyItem->addToGroup(pText);
    }

    /**************************��ˮƽ��******************************/
  //  if(bIfHorizon)   //ѡ����ˮƽѡ���
   // {
       for(i = 0; i < nRow + 1; i++)// for(i = 0; i < nRow + 2; i++)
        {
            QPainterPath mPath;
            mMoveX = 0;
            mMoveY = (i)*nH;
            mLineX = 0+nW;
            mLineY = (i)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
            mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
            pLine = new QLineItem(mPath);        //��ϸֱ��
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            if(i > 0)
            sName = "HLine"+sName;
            pLine->setLineColor(mLineColor);
            pLine->SetName(sName);
            pCopyItem->addToGroup(pLine);                   //��ӵ���
        }
   // }
    /**************************����ֱ��******************************/
  //  if(bIfVertical)  //ѡ���˴�ֱ
 //   {
        for(i = 0; i < nColoum + 1; i++)//for(i = 0; i < nColoum + 2; i++)
        {
            QPainterPath mPath;
            mMoveX = nTexeW*(i);
            mMoveY = 0;
            mLineX = nTexeW*(i);
            mLineY = (nRow+1)*nH;
            mPath.moveTo(mMoveX,mMoveY);         //��ֱ�ߵ����
            mPath.lineTo(mLineX,mLineY);         //��ֱ�ߵ��յ�
            pLine = new QLineItem(mPath);        //��ϸֱ��
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            if(i > 0)
            sName = "VLine"+sName;
            pLine->setLineColor(mLineColor);
            pLine->SetName(sName);
            pCopyItem->addToGroup(pLine);                   //��ӵ���
        }
 //   }
}
