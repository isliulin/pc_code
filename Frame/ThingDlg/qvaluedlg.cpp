#include "qvaluedlg.h"
#include "ui_qvaluedlg.h"
#include "qvaluescaledlg.h"

extern MainWindow *pwnd;

QValueDlg::QValueDlg(QGraphicsItem *pItem,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QValueDlg)
{
    QGraphicsItem *Item;
    bInitFlag = false;
    oId = -1;
    pScaleWidget = new QValueScaleDlg;
    pQvalueBace = new QValueBaseDlg(0,pScaleWidget);
    pQvalueShow = new QValueShowDlg;
    pQvalueColor = new QValueColorDlg;
    pSecurityWight = new SecurityWidget;
    pValueDateInput = new QValueDateInputDlg;

    pTabWidget = new QTabWidget(this);

    pTabWidget->addTab(pQvalueBace,tr("����"));
    pTabWidget->addTab(pQvalueShow,tr("��ʾ"));
    pTabWidget->addTab(pQvalueColor,tr("�������"));
    pTabWidget->addTab(pSecurityWight,tr("Ȩ������"));
    pSecurityWight->setTouchGroupEnabled(false);
    eDataType = DATAINPUTSHOW;
    pTabWidget->setGeometry(QRect(155,10,610,485));

    connect(pQvalueBace, SIGNAL(onTabWightSwitch(int)),this, SLOT(onTabWightSwitch(int)));//���ջ���ҳ�淢�͵�ҳ���л���Ϣ
    connect(pQvalueColor, SIGNAL(onDrawSence(QString)),this, SLOT(onDrawSence(QString)));//������ɫҳ��������ɫ�ı���Ϣ
    connect(pQvalueBace, SIGNAL(onDrawSence(QString)),this, SLOT(onDrawSence(QString)));//����ʱ��ҳ���ַ����ı���Ϣ
    connect(pQvalueShow, SIGNAL(onDrawSence(QString)),this, SLOT(onDrawSence(QString)));//������ʾҳ��С��λ���ı���Ϣ
    connect(pQvalueBace, SIGNAL(onTabWightSwitch(int)),pQvalueShow, SLOT(onTabWightSwitch(int)));//���ջ���ҳ�淢�͵�ҳ���л���Ϣ
    connect(pQvalueBace, SIGNAL(onTabWightSwitch(int)),pQvalueColor, SLOT(onTabWightSwitch(int)));//���ջ���ҳ�淢�͵�ҳ���л���Ϣ
    connect(pQvalueColor, SIGNAL(addPicture(QGraphicsItem*,QPixmap*,QString,EITEM_TYPE)),this, SLOT(onAddPicture(QGraphicsItem*,QPixmap*,QString,EITEM_TYPE)));
    connect(pQvalueBace, SIGNAL(setRange(double, double, int,int)),pQvalueColor, SLOT(setdataRange(double, double,int,int)));//����ʱ��ҳ���ַ����ı���Ϣ
    connect(pQvalueBace, SIGNAL(setDataLength(int,int,bool,bool)),pQvalueShow, SLOT(setDataLength(int,int,bool,bool)));
    connect(pQvalueBace, SIGNAL(getDataLength(int &)),pQvalueShow, SLOT(getDataLength( int &)));
    connect(pQvalueShow, SIGNAL(setDatadefault(int, bool)),pQvalueBace, SLOT(setDatadefault( int ,bool)));

    connect(pQvalueBace, SIGNAL(setRange(double, double, int,int)),pScaleWidget, SLOT(onSetRange(double, double,int,int)));//����ʱ��ҳ���ַ����ı���Ϣ

    connect(pQvalueBace, SIGNAL(scaleClicked(bool )),this, SLOT(onScaleClicked(bool )));//���ջ���ҳ�淢�͵�������Ϣ
    ui->setupUi(this);
    this->setFixedSize(this->size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    connect(ui->m_cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->m_helpBtn, SIGNAL(clicked()), this, SLOT(loadHelp()));
    connect(ui->m_okBtn, SIGNAL(clicked()), this, SLOT(confyButton()));

    pScene = new QGraphicsScene(this);//������
    ui->MainView->setScene(pScene);

    if(pItem)
    {
        pQvalueShow->Init(NULL);
        pQvalueColor->Init(NULL);
        //pQvalueBace->Init(NULL);
        Item = dynamic_cast<DataDisplayItem *> (pItem)->Clone();
        InitAllProperty(dynamic_cast<DataDisplayItem *> (Item));
    }
    else
    {
        InitAllProperty(NULL);
        ui->m_Titellabel->setText(tr("��ֵ����/��ʾ"));
    }
    ui->m_okBtn->setFocus();
    bInitFlag = true;
}

void QValueDlg::confyButton()
{
    //onSaveItemPosition();//����Item������

    if(eDataType == DATAINPUTSHOW)
    {
        if(pQvalueBace->IsCanInput() && !pValueDateInput->IsHaveKeyboard())//��������,ûѡ�м���
        {
            QMessageBox box(QMessageBox::Information,tr("����"),tr("û��ѡ����̽�Ĭ��Ϊϵͳ���̣�"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
            box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
            box.exec();
            if(box.clickedButton() == box.button(QMessageBox::Cancel))
            {
                return;
            }
        }
    }

    if(eDataType == ASCIIINPUTSHOW)
    {
        if(pQvalueBace->IsCanInput() && !pValueDateInput->IsHaveKeyboard())//��������,ûѡ�м���
        {
            QMessageBox box(QMessageBox::Information,tr("����"),tr("û��ѡ����̽�Ĭ��Ϊϵͳ���̣�"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
            box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
            box.exec();
            if(box.clickedButton() == box.button(QMessageBox::Cancel))
            {
                return;
            }
        }
    }

    //��������ҳ������
    if(!pSecurityWight->Save() /*&& eDataType != DATETIMEINPUT*/)
    {
        return;
    }
    pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));

    if(DATAINPUTSHOW == eDataType)
    {
        if(!(pQvalueBace->onDataGenSave(data_st)))
        {
            return;
        }
        if(!pQvalueShow->onDataGenSave(data_st))
        {
            return;
        }
        pQvalueColor->onDataGenSave(data_st);
        if(!pValueDateInput->onDataGenSave(data_st))
        {
            return;
        }
        pCopyItem->onSaveDataInfo(data_st);

        pCopyItem->m_time.nShapId = data_st.nShapId;
        pCopyItem->m_ascii.nShapId = data_st.nShapId;
    }
    else if(ASCIIINPUTSHOW == eDataType)
    {
        if(!(pQvalueBace->onAsciiGenSave(ascii_st)))
        {
            return;
        }
        if(!(pValueDateInput->onAsciiGenSave(ascii_st)))
        {
            return;
        }
        if(!pQvalueShow->onAsciiGenSave(ascii_st))
        {
            return ;
        }
        pQvalueColor->onAsciiGenSave(ascii_st);
        pCopyItem->onSaveAsciiInfo(ascii_st);

        pCopyItem->m_time.nShapId = ascii_st.nShapId;
        pCopyItem->m_data.nShapId = ascii_st.nShapId;
    }
    else if(DATETIMEINPUT == eDataType)
    {
        if(!(pQvalueBace->onTimeGenSave(time_st)))
        {
            return;
        }
        pQvalueColor->onTimeGenSave(time_st);
        pCopyItem->onSaveTimeInfo(time_st);
        pCopyItem->m_ascii.nShapId = time_st.nShapId;
        pCopyItem->m_data.nShapId = time_st.nShapId;
    }
    pCopyItem->setId(ui->spinBox->value());
    if(ui->spinBox->value() != oId && !pwnd->insertId(ui->spinBox->value()))
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ID�ظ������޸�ID��"),
                        0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        ui->spinBox->setFocus();
        return ;
    }

    accept();
}

void QValueDlg::loadHelp()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_VALUE);
}

QValueDlg::~QValueDlg()
{
    if(pQvalueBace)
    {
        delete pQvalueBace;
        pQvalueBace = NULL;
    }

    if(pQvalueShow)
    {
        delete pQvalueShow;
        pQvalueShow = NULL;
    }

    if(pQvalueColor)
    {
        delete pQvalueColor;
        pQvalueColor = NULL;
    }

    if(pValueDateInput)
    {
        delete pValueDateInput;
        pValueDateInput = NULL;
    }

    if (pTabWidget)
    {
        delete pTabWidget;
        pTabWidget = NULL;
    }
    delete ui;
}

void QValueDlg::onTabWightSwitch(int eType)
{
    if(NULL == pTabWidget)
    {
        return;
    }
    if(pQvalueBace->getAllowInputState())
    {
        pSecurityWight->setTouchGroupEnabled(true);
    }
    else
    {
        pSecurityWight->setTouchGroupEnabled(false);
    }
    switch(eType)
    {
    case DATAINPUTSHOW:
        pTabWidget->clear();
        pTabWidget->addTab(pQvalueBace,tr("����"));
        pTabWidget->addTab(pQvalueShow,tr("��ʾ"));
        pTabWidget->addTab(pQvalueColor,tr("�������"));
        pTabWidget->addTab(pSecurityWight,tr("Ȩ������"));

        if(pQvalueBace->onDateInputState())
        {
            pTabWidget->addTab(pValueDateInput,tr("��������"));
        }
        if(pQvalueBace->isScaleEnable())
        {
            pTabWidget->addTab(pScaleWidget,tr("��������"));
        }
        eDataType = (VALUESHOWTYPE)eType;
        ui->m_Titellabel->setText(tr("��ֵ����/��ʾ"));
        pSecurityWight->setGroupVVisible(true);
        break;
    case ASCIIINPUTSHOW:
        pTabWidget->clear();
        pTabWidget->addTab(pQvalueBace,tr("����"));
        pTabWidget->addTab(pQvalueShow,tr("��ʾ"));
        pTabWidget->addTab(pQvalueColor,tr("�������"));
        pTabWidget->addTab(pSecurityWight,tr("Ȩ������"));
        if(pQvalueBace->onDateInputState())
        {
            pTabWidget->addTab(pValueDateInput,tr("��������"));
        }
        eDataType = (VALUESHOWTYPE)eType;
        ui->m_Titellabel->setText(tr("ASCII����/��ʾ"));
        pSecurityWight->setGroupVVisible(true);
        break;
    case DATETIMEINPUT:
        pTabWidget->clear();
        pTabWidget->addTab(pQvalueBace,tr("����"));
        pTabWidget->addTab(pQvalueColor,tr("�������"));
        pTabWidget->addTab(pSecurityWight,tr("Ȩ������"));
        eDataType = (VALUESHOWTYPE)eType;
        ui->m_Titellabel->setText(tr("����/ʱ����ʾ"));
        pSecurityWight->setGroupVVisible(false);
        break;
    default:
        return;
    }
    onDrawSence("Text");
}

void QValueDlg::InitAllProperty(DataDisplayItem *pItem)
{
    if(pItem)
    {
        pCopyItem = pItem;
        data_st.nShapId = pItem->m_data.nShapId;
        ascii_st.nShapId = pItem->m_ascii.nShapId;
        time_st.nShapId = pItem->m_time.nShapId;
        pBaseItem = new QGroupItem(pCopyItem);
        if(pCopyItem->childItems().size() > 1)
        {
            pBaseItem->SetWidth(70);
            pBaseItem->SetHeigth(50);
            pCopyItem->setPos(0-pCopyItem->boundingRect().x(),0-pCopyItem->boundingRect().y());
        }
        else
        {
            pBaseItem->SetWidth(70);
            pBaseItem->SetHeigth(50);
            pCopyItem->setPos(0-pCopyItem->boundingRect().x(),0-pCopyItem->boundingRect().y());
        }
        pScene->clear();
        pScene->addItem(pCopyItem);
        if(DATAINPUTSHOW == pItem->m_etabPag)
        {
            data_st.nShapId = pItem->m_data.nShapId;

            if(pItem->m_data.bIsInput)
            {
                pSecurityWight->setTouchGroupEnabled(true);
            }
        }
        else if(ASCIIINPUTSHOW == pItem->m_etabPag)
        {
            ascii_st.nShapId = pItem->m_ascii.nShapId;
        }
        else if(DATETIMEINPUT == pItem->m_etabPag)
        {
            time_st.nShapId = pItem->m_time.nShapId;
        }
        pQvalueShow->Init(pItem);
        pQvalueBace->Init(pItem);
        pQvalueColor->Init(pItem);
        pValueDateInput->Init(pItem);
        pSecurityWight->init(pItem);
        oId = pItem->id();
        ui->spinBox->setValue(oId);
    }
    else//��ȡ������ɫ��������
    {
        pQvalueShow->Init(NULL);
        pQvalueColor->Init(NULL);
        pQvalueBace->Init(NULL);
        pValueDateInput->Init(NULL);
        data_st.eShowStyle = CStart;
        ascii_st.nShowStyle = CStart;
        time_st.nShowStyle = CStart;
        onDrawSence("");
        ui->spinBox->setValue(pwnd->getNewId());
    }
}

void QValueDlg::onDrawSence(QString sName)
{
    QString sText = "";
    QColor mColor(0,0,0);
    if(bInitFlag)//��ʼ����ɺ���þ����ػ���������
    {
        if("FontColor" == sName)
        {
            pQvalueColor->onGetValueColor(mColor);
            pCopyItem->SetFontColor(mColor);
            //pBaseItem->SetPropertyValue("mText.FontColor",QVariant(nColor));
        }
        else if("BackColor" == sName)
        {
            pQvalueColor->onGetValueBackColor(mColor);
            pCopyItem->SetRectBackColor(mColor);
            //pBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(nColor));
        }
        else if("Text" == sName)
        {
            if(DATAINPUTSHOW == eDataType)
            {
                sText.clear();
                int nTotaldigit = pQvalueShow->onGetTotaldigit();
                for(int i = 0; i < nTotaldigit;i++)
                {
                    sText = sText + "8";
                }
                int nPoint = pQvalueShow->onGetDecimaldigit();
                if(nPoint > 0 && nPoint < nTotaldigit)
                {
                    sText.insert(nTotaldigit - nPoint,'.');
                }
                int nfontsize = pQvalueShow->onGetFontSize();
                QString sFont = pQvalueShow->onGetFont(eDataType);
                pBaseItem->SetPropertyValue("mText.Font",QVariant(sFont));
                pBaseItem->SetPropertyValue("mText.FontSize",QVariant(nfontsize));
            }
            else if(ASCIIINPUTSHOW == eDataType)
            {
                for(int i = 0; i <pQvalueShow->onGetTotaldigit(); i++)
                {
                    int nChar = i%26;
                    sText.insert(i,'A'+nChar);
                }
                int nfontsize = pQvalueShow->onGetFontSize();
                QString sFont = pQvalueShow->onGetFont(eDataType);
                pBaseItem->SetPropertyValue("mText.Font",QVariant(sFont));
                pBaseItem->SetPropertyValue("mText.FontSize",QVariant(nfontsize));
            }
            else if(DATETIMEINPUT == eDataType)
            {
                sText = pQvalueBace->onGetpreText();
                pCopyItem->SetTextAlign(5);
                QString sFont = pQvalueBace->onGetFontType();
                pBaseItem->SetPropertyValue("mText.Font",QVariant(sFont));
                int nfontsize = pQvalueBace->onGetFontSize();
                pBaseItem->SetPropertyValue("mText.FontSize",QVariant(nfontsize));
                //pBaseItem->SetPropertyValue("mText.Alignment",QVariant(5)); //���ж���
            }
            pCopyItem->SetText(sText);
            //pBaseItem->SetPropertyValue("mText.Text",QVariant(sText));
        }
        else if("4" == sName)
        {
            if(pCopyItem)
            {
                pCopyItem->SetTextAlign(4);
            }
//            pBaseItem->SetPropertyValue("mText.Alignment",QVariant(4)); //�����
//            data_st.eShowStyle = LStart;
//            ascii_st.nShowStyle = LStart;
//            time_st.nShowStyle = LStart;
        }
        else if("5" == sName)
        {
            if(pCopyItem)
            {
                pCopyItem->SetTextAlign(5);
            }
//            pBaseItem->SetPropertyValue("mText.Alignment",QVariant(5)); //���ж���
//            data_st.eShowStyle = CStart;
//            ascii_st.nShowStyle = CStart;
//            time_st.nShowStyle = CStart;
        }
        else if("6" == sName)
        {
            if(pCopyItem)
            {
                pCopyItem->SetTextAlign(6);
            }
//            pBaseItem->SetPropertyValue("mText.Alignment",QVariant(6)); //�Ҷ���
//            data_st.eShowStyle = RStart;
//            ascii_st.nShowStyle = RStart;
//            time_st.nShowStyle = RStart;
        }
        else if("Font" == sName)
        {
            QString sFont = "";
            if(DATAINPUTSHOW == eDataType || ASCIIINPUTSHOW == eDataType)
            {
                sFont = pQvalueShow->onGetFont(eDataType);
            }
            else
            {
                sFont = pQvalueBace->onGetFontType();
            }
            pBaseItem->SetPropertyValue("mText.Font",QVariant(sFont));
        }
        else if("FontSize" == sName)
        {
            int nfontsize = 10;
            if(DATAINPUTSHOW == eDataType || ASCIIINPUTSHOW == eDataType)
            {
                nfontsize = pQvalueShow->onGetFontSize();
            }
            else
            {
                nfontsize = pQvalueBace->onGetFontSize();
            }
            pBaseItem->SetPropertyValue("mText.FontSize",QVariant(nfontsize));
        }
        else if("FontType" == sName)
        {
            onSetFontType();
        }
    }
    else
    {
        if("" != sName)
        {
            return;//�ǳ�ʼ������ֱ�ӷ���
        }
        DataDisplayItem *pGroupItem = new DataDisplayItem;
        QRectItem *pBackRect;
        QRectItem *pFramRect;
        QSimpleTextItem *pTextRect;

        QRectF brect(QPointF(5,5), QSize(90,90));
        pBackRect = new QRectItem(brect);
        pQvalueColor->onGetValueBackColor(mColor);
        pBackRect->SetBackColor(mColor);
        pBackRect->SetLineType(0);
        pBackRect->setZValue(2);
        pBackRect->SetName(tr("mBackRect"));
        pBackRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pBackRect->setFlag(QGraphicsItem::ItemIsMovable, false);

        QRectF frect(QPointF(0,0), QSize(100,100));
        pFramRect = new QRectItem(frect);
        pFramRect->SetBackColor(QColor(224,224,224));
        pFramRect->SetLineType(0);
        pFramRect->setZValue(1);
        pFramRect->SetName(tr("mFramRect"));
        pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pFramRect->setFlag(QGraphicsItem::ItemIsMovable, false);
        pFramRect->SetPattern(0);

        QRectF mrect(QPointF(15,25), QSize(70,50));
        pTextRect = new QSimpleTextItem(mrect,"");
        pTextRect->SetName("mText");
        pTextRect->SetRectOutLine(false);
        pTextRect->setZValue(3);
        pTextRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pTextRect->SetPattern(1);
        pTextRect->SetFontSize(pQvalueShow->onGetFontSize());
        int nTotaldigit = pQvalueShow->onGetTotaldigit();
        for(int i = 0; i < nTotaldigit;i++)
        {
            sText = sText + "8";
        }
        int nPoint = pQvalueShow->onGetDecimaldigit();
        if(nPoint > 0 && nPoint < nTotaldigit)
        {
            sText.insert(nTotaldigit - nPoint,'.');
        }
        pTextRect->SetText(sText);
        pQvalueColor->onGetValueColor(mColor);
        pTextRect->SetFontColor(mColor);
        pQvalueColor->onGetValueBackColor(mColor);
        pTextRect->SetRectBackColor(mColor);

        QString sFont = pQvalueShow->onGetFont(eDataType);
        pTextRect->SetFontName(sFont);
        //pGroupItem->addToGroup(pFramRect);
        //pGroupItem->addToGroup(pBackRect);
        pGroupItem->addToGroup(pTextRect);

        pCopyItem = pGroupItem;
        pCopyItem->textItem = pTextRect;
        pScene->clear();
        pScene->addItem(pCopyItem);
        pBaseItem = new QGroupItem(pCopyItem);
        //pBaseItem->SetHeigth(100);
        //pBaseItem->SetWidth(100);
    }
    setTransparent();
}

void QValueDlg::onSetColor(QString sName)
{
    if("mBackRect" == sName)
    {
        QColor mColor(0,0,0);
        QString scolor = pwnd->ColorTOString(mColor);
        pQvalueColor->onGetValueBackColor(mColor);
        QString nColor = pwnd->ColorTOString(mColor);
        pBaseItem->SetPropertyValue("mBackRect.BackColor",QVariant(nColor));
    }
    else if("mFramRect" == sName)
    {
        QColor mColor(0,0,0);
        QString scolor = pwnd->ColorTOString(mColor);
        pQvalueColor->onGetValueColor(mColor);
        QString nColor = pwnd->ColorTOString(mColor);
        pBaseItem->SetPropertyValue("mFramRect.BackColor",QVariant(nColor));
    }
}

void QValueDlg::onSetFontType()//������������ ���塢б�塢�»���
{
    bool bchecked;
    bool bfont = false;
    QString sfontType;
    if(DATAINPUTSHOW == eDataType || ASCIIINPUTSHOW == eDataType)
    {
        bchecked = pQvalueShow->onGetFontType(0);
        if(bchecked)
        {
            bfont = false;
            sfontType.clear();
            sfontType = sfontType + "mText";
            sfontType = sfontType + ".";
            sfontType = sfontType + "FontBold";
            pBaseItem->SetPropertyValue(sfontType,QVariant(bfont));
            sfontType.clear();
            sfontType = sfontType + "mText";
            sfontType = sfontType + ".";
            sfontType = sfontType + "FontItalic";
            pBaseItem->SetPropertyValue(sfontType,QVariant(bfont));
            sfontType.clear();
            sfontType = sfontType + "mText";
            sfontType = sfontType + ".";
            sfontType = sfontType + "UnderLine";
            pBaseItem->SetPropertyValue(sfontType,QVariant(bfont));
        }
        else
        {
            bchecked = pQvalueShow->onGetFontType(1);
            sfontType.clear();
            sfontType = sfontType + "mText";
            sfontType = sfontType + ".";
            sfontType = sfontType + "FontBold";
            pBaseItem->SetPropertyValue(sfontType,QVariant(bchecked));
            sfontType.clear();
            bchecked = pQvalueShow->onGetFontType(2);
            sfontType = sfontType + "mText";
            sfontType = sfontType + ".";
            sfontType = sfontType + "FontItalic";
            pBaseItem->SetPropertyValue(sfontType,QVariant(bchecked));
            sfontType.clear();
            bchecked = pQvalueShow->onGetFontType(3);
            sfontType = sfontType + "mText";
            sfontType = sfontType + ".";
            sfontType = sfontType + "UnderLine";
            pBaseItem->SetPropertyValue(sfontType,QVariant(bchecked));
        }
    }
    else
    {
        bchecked = pQvalueBace->onGetFontStyl(0);
        if(bchecked)
        {
            bfont = false;
            sfontType.clear();
            sfontType = sfontType + "mText";
            sfontType = sfontType + ".";
            sfontType = sfontType + "FontBold";
            pBaseItem->SetPropertyValue(sfontType,QVariant(bfont));
            sfontType.clear();
            sfontType = sfontType + "mText";
            sfontType = sfontType + ".";
            sfontType = sfontType + "FontItalic";
            pBaseItem->SetPropertyValue(sfontType,QVariant(bfont));
            sfontType.clear();
            sfontType = sfontType + "mText";
            sfontType = sfontType + ".";
            sfontType = sfontType + "UnderLine";
            pBaseItem->SetPropertyValue(sfontType,QVariant(bfont));
        }
        else
        {
            bchecked = pQvalueBace->onGetFontStyl(1);
            sfontType.clear();
            sfontType = sfontType + "mText";
            sfontType = sfontType + ".";
            sfontType = sfontType + "FontBold";
            pBaseItem->SetPropertyValue(sfontType,QVariant(bchecked));
            sfontType.clear();
            bchecked = pQvalueBace->onGetFontStyl(2);
            sfontType = sfontType + "mText";
            sfontType = sfontType + ".";
            sfontType = sfontType + "FontItalic";
            pBaseItem->SetPropertyValue(sfontType,QVariant(bchecked));
            sfontType.clear();
            bchecked = pQvalueBace->onGetFontStyl(3);
            sfontType = sfontType + "mText";
            sfontType = sfontType + ".";
            sfontType = sfontType + "UnderLine";
            pBaseItem->SetPropertyValue(sfontType,QVariant(bchecked));
        }
    }

}

void QValueDlg::onSaveItemPosition()
{
    QRectF oldpos = pCopyItem->sceneBoundingRect();
    QRectF textOldpos;

    QList <QGraphicsItem *> childItems;
    childItems = pCopyItem->childItems();
    foreach(QGraphicsItem *pItem,childItems)
    {
        if("mText" == pItem->data(GROUP_NAME_KEY).toString())
        {
           textOldpos = pItem->sceneBoundingRect();
           break;
        }
    }

    if(DATAINPUTSHOW == eDataType)
    {
        data_st.nStartX = oldpos.x();
        data_st.nStartY = oldpos.y();
        data_st.nWidth = oldpos.width();
        data_st.nHeight = oldpos.height();

        data_st.nTextStartX = textOldpos.x();
        data_st.nTextStartY = textOldpos.y();
        data_st.nTextWidth = textOldpos.width();
        data_st.nTextHeight = textOldpos.height();
    }
    else if(ASCIIINPUTSHOW == eDataType)
    {
        ascii_st.nStartX = oldpos.x();
        ascii_st.nStartY = oldpos.y();
        ascii_st.nWidth = oldpos.width();
        ascii_st.nHeight = oldpos.height();

        ascii_st.nTextStartX = textOldpos.x();
        ascii_st.nTextStartY = textOldpos.y();
        ascii_st.nTextWidth = textOldpos.width();
        ascii_st.nTextHeight = textOldpos.height();
    }
    else if(DATETIMEINPUT == eDataType)
    {
        time_st.nStartX = oldpos.x();
        time_st.nStartY = oldpos.y();
        time_st.nWidth = oldpos.width();
        time_st.nHeight = oldpos.height();

        time_st.nTextStartX = textOldpos.x();
        time_st.nTextStartY = textOldpos.y();
        time_st.nTextWidth = textOldpos.width();
        time_st.nTextHeight = textOldpos.height();
    }
}

void QValueDlg::onAddPicture(QGraphicsItem *pItem,QPixmap* pPix,QString sPath,EITEM_TYPE eIspic)
{
    if(!pCopyItem)
    {
        return;
    }
    QRectF pos = pCopyItem->textItem->sceneBoundingRect();
    DataDisplayItem *newGroup = new DataDisplayItem;
    newGroup->textItem = pCopyItem->textItem;
    pCopyItem->removeFromGroup(pCopyItem->textItem);
    pCopyItem->textItem->setZValue(3);
    newGroup->addToGroup(newGroup->textItem);

    data_st.nShapId = sPath;
    ascii_st.nShapId = sPath;
    time_st.nShapId = sPath;
    if(pItem)
    {
        QGroupItem *pGroupItem = new QGroupItem(pItem);
        pGroupItem->SetWidth(pCopyItem->textItem->boundingRect().width());
        pGroupItem->SetHeigth(pCopyItem->textItem->boundingRect().height());
        pItem->setZValue(1);
        pItem->setPos(pos.x() - pItem->boundingRect().x(),pos.y() - pItem->boundingRect().y());
        newGroup->addToGroup(pItem);
        newGroup->SetPattern(0);
        newGroup->m_eIspic = eIspic;
        QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(newGroup->textItem);
        if(pText)
        {
            pText->SetRectOutLine(false);
        }
    }
    else
    {
        int nPatener  = pQvalueColor->onGetTransparent();
        newGroup->SetAlpha(nPatener);
        newGroup->SetPattern(1);
        newGroup->m_eIspic = PIC;
    }
    delete pCopyItem;
    pCopyItem = newGroup;
    pBaseItem = new QGroupItem(pCopyItem);
    pScene->clear();
    pScene->addItem(pCopyItem);
    setTransparent();
}
void QValueDlg::onScaleClicked(bool checked)
{
    if(checked)
    {
        pTabWidget->addTab(pScaleWidget,tr("��������"));
    }
    else
    {
        int index = pTabWidget->indexOf(pScaleWidget);
        if(index >= 0)
            pTabWidget->removeTab(index);
    }
}
void QValueDlg::on_m_PatternckBox_clicked(bool checked)
{
    if(!bInitFlag || !pCopyItem)
    {
        return;
    }
    if(checked)
    {
        pCopyItem->SetPattern(0);
    }
    else
    {
        pCopyItem->SetPattern(1);
    }
}

void QValueDlg::setTransparent()
{
    if(pCopyItem)
    {
        if(pCopyItem->childItems().size() > 1)
        {
            return;
        }
        else
        {
            int nPatener  = pQvalueColor->onGetTransparent();
            pCopyItem->SetAlpha(nPatener);
        }
    }
}
