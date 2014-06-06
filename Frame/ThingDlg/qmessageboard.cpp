#include "qmessageboard.h"
#include "ui_qmessageboard.h"
#include "Frame/mainwindow.h"

extern  MainWindow *pwnd;

qMessageBoard::qMessageBoard(qMessageBoradAttr* pItem, QWidget *parent):QDialog(parent),ui(new Ui::qMessageBoard)
{
    ui->setupUi(this);

    oId = -1;
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    bInit       = false;
    m_pCopyItem = NULL;
    pTempItem   = NULL;
    curLan = 0;

    pSecurityWight = new SecurityWidget(this);
    ui->tabWidget->addTab(pSecurityWight, tr("权限设置"));
    //pSecurityWight->ui->groupBox_Touch->hide();

    pScene = new QGraphicsScene(this); //建场景
    ui->graphicsView->setScene(pScene);//贴图区域

    this->setWindowTitle(tr("留言板"));

    //语言
    ui->comboBox_language->clear();
    int temp = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    for(int i = 0; i < temp; i++)
    {
        ui->comboBox_language->addItem(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList[i]);
    }

    //字体
    ui->comboBox_Tfonttype->clear();
    ui->comboBox_type->clear();
    ui->comboBox_Tfonttype->addItems(QFontDatabase().families(QFontDatabase::Any));
    ui->comboBox_type->addItems(QFontDatabase().families(QFontDatabase::Any));

    //时间格式
    ui->comboBox_time->clear();
    ui->comboBox_time->addItem(tr("HH:MM"));
    ui->comboBox_time->addItem(tr("HH:MM:SS"));
    ui->comboBox_time->addItem(tr("HH-MM"));
    ui->comboBox_time->addItem(tr("HH-MM-SS"));

    //日期格式
    ui->comboBox_date->clear();
    ui->comboBox_date->addItem(tr("YYYY/MM/DD"));
    ui->comboBox_date->addItem(tr("YYYY.MM.DD"));
    ui->comboBox_date->addItem(tr("YYYY-MM-DD"));
    ui->comboBox_date->addItem(tr("MM/DD/YYYY"));
    ui->comboBox_date->addItem(tr("MM.DD.YYYY"));
    ui->comboBox_date->addItem(tr("MM-DD-YYYY"));
    ui->comboBox_date->addItem(tr("DD/MM/YYYY"));
    ui->comboBox_date->addItem(tr("DD.MM.YYYY"));
    ui->comboBox_date->addItem(tr("DD-MM-YYYY"));

    //样式
    //ui->comboBox_style->clear();
    //pwnd->OnAddPattern(ui->comboBox_style);

    //ui->label_4->hide();
    //ui->comboBox_style->hide();

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

        int fontNum = QFontDatabase().families(QFontDatabase::Any).size();
        pSecurityWight->init(pItem);

        //标题
        ui->checkBox_number->setChecked(pItem->m_bShowId);
        ui->checkBox_time->setChecked(pItem->m_bShowTime);
        ui->comboBox_time->setCurrentIndex(pItem->m_nTimeType);
        ui->checkBox_date->setChecked(pItem->m_bShowDate);
        ui->comboBox_date->setCurrentIndex(pItem->m_nDateType);
        ui->spinBox_Tfontsize->setValue(pItem->m_nTFontSize);
        for(int i = 0; i < fontNum; i++)
        {
            if(QFontDatabase().families(QFontDatabase::Any).at(i) == pItem->m_sTFontType)
            {
                ui->comboBox_Tfonttype->setCurrentIndex(i);
                break;
            }
        }
        ui->pushButton_Tfontcolor->setStyleSheet(QString("background:%1").arg(pItem->m_nTFontColor.name()));
        ui->pushButton_BKcolor->setStyleSheet(QString("background:%1").arg(pItem->m_nTBackColor.name()));
        //填充
        ui->spinBox_transparency->setValue(pItem->m_nAlpha);
        ui->pushButton_framecolor->setStyleSheet(QString("background:%1").arg(pItem->m_nLineColor.name()));
        //ui->comboBox_style->setCurrentIndex(pItem->m_nFillCss);
        ui->pushButton_backcolor->setStyleSheet(QString("background:%1").arg(pItem->m_nBackColor.name()));
        ui->pushButton_frontcolor->setStyleSheet(QString("background:%1").arg(pItem->m_nForeColor.name()));
        //字体
        ui->spinBox_size->setValue(pItem->m_nFontSize);
        for(int i = 0; i < fontNum; i++)
        {
            if(QFontDatabase().families(QFontDatabase::Any).at(i) == pItem->m_sFontType)
            {
                ui->comboBox_type->setCurrentIndex(i);
                break;
            }
        }
        ui->pushButton_color->setStyleSheet(QString("background:%1").arg(pItem->m_nFontColor.name()));
        ui->spinBox_line->setValue(pItem->m_nRowNumber);

        //多语言,这些都没有考虑外界的语言变化的情况
        m_vecMessage = pItem->m_vecMessage;
        int vecNum   = m_vecMessage.size();
        if(vecNum > temp)
        {
            int tt = vecNum - temp;
            for(int i = 0; i < tt; i++)
            {
                m_vecMessage.pop_back();
            }
        }
        else if(vecNum < temp)
        {
            int tt = temp - vecNum;
            MmessageBoardLanguage MBLan;
            for(int i = 0; i < tt; i++)
            {
                MBLan.m_nLanguage    = vecNum + i;
                MBLan.m_sNumber      = tr("编号");
                MBLan.m_sTimeName    = tr("时间");
                MBLan.m_sDateName    = tr("日期");
                MBLan.m_sMessageName = tr("留言信息");
                m_vecMessage.push_back(MBLan);
            }
        }
        oId = pItem->id();
        ui->spinBox->setValue(oId);
    }
    else
    {
        pSecurityWight->init(NULL);
        int fontNum = QFontDatabase().families(QFontDatabase::Any).size();

        //标题
        ui->checkBox_number->setChecked(false);
        ui->checkBox_time->setChecked(false);
        ui->comboBox_time->setCurrentIndex(0);
        ui->checkBox_date->setChecked(false);
        ui->comboBox_date->setCurrentIndex(0);
        ui->spinBox_Tfontsize->setValue(10);
        for(int i = 0; i < fontNum; i++)
        {
            if(QFontDatabase().families(QFontDatabase::Any).at(i) == tr("Droid Sans Fallback"))
            {
                ui->comboBox_Tfonttype->setCurrentIndex(i);
                break;
            }
        }
        ui->pushButton_Tfontcolor->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
        ui->pushButton_BKcolor->setStyleSheet(QString("background:%1").arg(QColor(255,255,0).name()));
        //填充
        ui->spinBox_transparency->setValue(255);
        ui->pushButton_framecolor->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
        //ui->comboBox_style->setCurrentIndex(0);
        ui->pushButton_backcolor->setStyleSheet(QString("background:%1").arg(QColor(224,224,224).name()));
        ui->pushButton_frontcolor->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
        //字体
        ui->spinBox_size->setValue(10);
        for(int i = 0; i < fontNum; i++)
        {
            if(QFontDatabase().families(QFontDatabase::Any).at(i) == tr("Droid Sans Fallback"))
            {
                ui->comboBox_type->setCurrentIndex(i);
                break;
            }
        }
        ui->pushButton_color->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
        ui->spinBox_line->setValue(5);

        MmessageBoardLanguage MBLan;
        for(int i = 0; i < temp; i++)
        {
            MBLan.m_nLanguage    = i;
            MBLan.m_sNumber      = tr("编号");
            MBLan.m_sTimeName    = tr("时间");
            MBLan.m_sDateName    = tr("日期");
            MBLan.m_sMessageName = tr("留言信息");
            m_vecMessage.push_back(MBLan);
        }
        ui->spinBox->setValue(pwnd->getNewId());
    }

    if(m_vecMessage.size() != 0)
    {
        ui->comboBox_language->setCurrentIndex(curLan);
        ui->lineEdit_number->setText(m_vecMessage[curLan].m_sNumber);
        ui->lineEdit_time->setText(m_vecMessage[curLan].m_sTimeName);
        ui->lineEdit_date->setText(m_vecMessage[curLan].m_sDateName);
        ui->lineEdit_message->setText(m_vecMessage[curLan].m_sMessageName);
    }
    else
    {
        //QDebug() << "出错";
    }

    drawSence();
    bInit = true;
}

qMessageBoard::~qMessageBoard()
{
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

    if(pScene)
    {
        delete pScene;
        pScene = NULL;
    }

    delete ui;
}

void qMessageBoard::on_pushButton_Tfontcolor_clicked()
{
    if(bInit == false)
    {
        return;
    }

    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_Tfontcolor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_Tfontcolor(const QColor &)));
}

void qMessageBoard::set_pushButton_Tfontcolor(const QColor & mColor)
{
    ui->pushButton_Tfontcolor->setStyleSheet(QString("background:%1").arg(mColor.name()));
    //发送重画信号
    drawSence();
}

void qMessageBoard::on_pushButton_BKcolor_clicked()
{
    if(bInit == false)
    {
        return;
    }

    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_BKcolor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_BKcolor(const QColor &)));
}

void qMessageBoard::set_pushButton_BKcolor(const QColor & mColor)
{
    ui->pushButton_BKcolor->setStyleSheet(QString("background:%1").arg(mColor.name()));
    //发送重画信号
    drawSence();
}

void qMessageBoard::on_pushButton_framecolor_clicked()
{
    if(bInit == false)
    {
        return;
    }

    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_framecolor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_framecolor(const QColor &)));
}

void qMessageBoard::set_pushButton_framecolor(const QColor & mColor)
{    
    ui->pushButton_framecolor->setStyleSheet(QString("background:%1").arg(mColor.name()));
    //发送重画信号
    drawSence();
}

void qMessageBoard::on_pushButton_backcolor_clicked()
{
    if(bInit == false)
    {
        return;
    }

    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_backcolor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_backcolor(const QColor &)));
}

void qMessageBoard::set_pushButton_backcolor(const QColor & mColor)
{
    ui->pushButton_backcolor->setStyleSheet(QString("background:%1").arg(mColor.name()));
    //发送重画信号
    drawSence();
}

void qMessageBoard::on_pushButton_frontcolor_clicked()
{
    if(bInit == false)
    {
        return;
    }

    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_frontcolor, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_frontcolor(const QColor &)));
}

void qMessageBoard::set_pushButton_frontcolor(const QColor & mColor)
{
    ui->pushButton_frontcolor->setStyleSheet(QString("background:%1").arg(mColor.name()));
    //发送重画信号
    drawSence();
}

void qMessageBoard::on_pushButton_color_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->pushButton_color, colorPicker);

    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(set_pushButton_color(const QColor &)));
}

void qMessageBoard::set_pushButton_color(const QColor & mColor)
{
    ui->pushButton_color->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

//////////////////////////////多语言////////////////////////////////////
void qMessageBoard::on_comboBox_language_currentIndexChanged(int index)
{
    if(bInit == false)
    {
        return;
    }

    if(index < m_vecMessage.size())
    {
        curLan = index;
        ui->lineEdit_number->setText(m_vecMessage[index].m_sNumber);
        ui->lineEdit_time->setText(m_vecMessage[index].m_sTimeName);
        ui->lineEdit_date->setText(m_vecMessage[index].m_sDateName);
        ui->lineEdit_message->setText(m_vecMessage[index].m_sMessageName);
        //发送重画信号
        drawSence();
    }
    else
    {
        //QMessageBox::about(this, tr("111111111"), tr("index不对"));
        curLan = 0;
    }
}

void qMessageBoard::on_lineEdit_number_editingFinished()
{
    if(bInit == false)
    {
        return;
    }

    if(curLan < m_vecMessage.size())
    {
        m_vecMessage[curLan].m_sNumber = ui->lineEdit_number->text();
        drawSence();
    }
    else
    {
        QMessageBox::about(this, tr("222222222"), tr("curLan不对"));
    }
}

void qMessageBoard::on_lineEdit_time_editingFinished()
{
    if(bInit == false)
    {
        return;
    }

    if(curLan < m_vecMessage.size())
    {
        m_vecMessage[curLan].m_sTimeName = ui->lineEdit_time->text();
        drawSence();
    }
    else
    {
        QMessageBox::about(this, tr("333333333"), tr("curLan不对"));
    }
}

void qMessageBoard::on_lineEdit_date_editingFinished()
{
    if(bInit == false)
    {
        return;
    }

    if(curLan < m_vecMessage.size())
    {
        m_vecMessage[curLan].m_sDateName = ui->lineEdit_date->text();
        drawSence();
    }
    else
    {
        QMessageBox::about(this, tr("444444444"), tr("curLan不对"));
    }
}

void qMessageBoard::on_lineEdit_message_editingFinished()
{
    if(bInit == false)
    {
        return;
    }

    if(curLan < m_vecMessage.size())
    {
        m_vecMessage[curLan].m_sMessageName = ui->lineEdit_message->text();
        drawSence();
    }
    else
    {
        QMessageBox::about(this, tr("55555555"), tr("curLan不对"));
    }
}

/////////////////////////snece重画///////////////////////////////
void qMessageBoard::on_checkBox_number_clicked()
{
    if(bInit == false)
    {
        return;
    }
    //只发送重画信号
    drawSence();
}

void qMessageBoard::on_checkBox_time_clicked()
{
    if(bInit == false)
    {
        return;
    }
    //只发送重画信号
    drawSence();
}

void qMessageBoard::on_checkBox_date_clicked()
{
    if(bInit == false)
    {
        return;
    }
    //只发送重画信号
    drawSence();
}

void qMessageBoard::on_spinBox_transparency_valueChanged(int )
{
    if(bInit == false)
    {
        return;
    }
    //只发送重画信号
    drawSence();
}

void qMessageBoard::on_spinBox_Tfontsize_valueChanged(int )
{
    if(bInit == false)
    {
        return;
    }
    //只发送重画信号
    drawSence();
}

void qMessageBoard::on_comboBox_Tfonttype_currentIndexChanged(int index)
{
    if(bInit == false)
    {
        return;
    }
    //只发送重画信号
    drawSence();
}

void qMessageBoard::on_comboBox_style_currentIndexChanged(int index)
{
    if(bInit == false)
    {
        return;
    }
    //只发送重画信号
    drawSence();
}

void qMessageBoard::on_spinBox_line_valueChanged(int value)
{
    if(bInit == false)
    {
        return;
    }
    //只发送重画信号
    drawSence();
}

////////////////////////////////////////////////////////////////
void qMessageBoard::on_help_clicked()
{
    pwnd->loadHelpHtm(SAM_DRAW_GROUP_TEXTBOARD);
}

void qMessageBoard::on_cancel_clicked()
{
    this->close();
}

void qMessageBoard::on_accept_clicked()
{
    m_pCopyItem = new qMessageBoradAttr;

    if(pSecurityWight && pSecurityWight->Save())
    {
        m_pCopyItem->SaveSecurityPro(&(pSecurityWight->sproperty));
    }
    else
    {
        return;
    }

    //标题
    m_pCopyItem->m_bShowId      = ui->checkBox_number->isChecked();         //是否显示编号
    m_pCopyItem->m_bShowTime    = ui->checkBox_time->isChecked();           //是否显示时间
    m_pCopyItem->m_nTimeType    = ui->comboBox_time->currentIndex();        //时间格式（枚举）
    m_pCopyItem->m_bShowDate    = ui->checkBox_date->isChecked();           //是否显示日期
    m_pCopyItem->m_nDateType    = ui->comboBox_date->currentIndex();        //日期格式（枚举）
    m_pCopyItem->m_nTFontSize   = ui->spinBox_Tfontsize->value();           //表头字体大小
    m_pCopyItem->m_sTFontType   = ui->comboBox_Tfonttype->currentText();    //表头字体类型
    m_pCopyItem->m_nTFontColor  = ui->pushButton_Tfontcolor->palette().background().color();    //表头字体颜色
    m_pCopyItem->m_nTBackColor  = ui->pushButton_BKcolor->palette().background().color();       //表头背景颜色
    //填充
    m_pCopyItem->m_nAlpha       = ui->spinBox_transparency->value();       //控件透明度
    m_pCopyItem->m_nLineColor   = ui->pushButton_framecolor->palette().background().color();    //边框颜色
    //m_pCopyItem->m_nFillCss     = ui->comboBox_style->currentIndex();      //填充样式
    m_pCopyItem->m_nBackColor   = ui->pushButton_backcolor->palette().background().color();     //背景颜色
    m_pCopyItem->m_nForeColor   = ui->pushButton_frontcolor->palette().background().color();    //前景色
    //字体
    m_pCopyItem->m_nFontSize    = ui->spinBox_size->value();       //内容字体大小
    m_pCopyItem->m_sFontType    = ui->comboBox_type->currentText();//内容字体类型
    m_pCopyItem->m_nFontColor   = ui->pushButton_color->palette().background().color();;        //内容字体颜色
    m_pCopyItem->m_nRowNumber   = ui->spinBox_line->value();       //内容行数
    //多语言
    m_pCopyItem->m_vecMessage   = m_vecMessage;
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

    drawTable();

    accept();
}

void qMessageBoard::drawTable()
{
    int     i           = 0;
    int     nVal        = 0;
    double  mMoveX      = 0;                //主刻度X起始点
    double  mMoveY      = 0;                //主刻度Y起始点
    double  mLineX      = 0;                //主刻度X起始点
    double  mLineY      = 0;                //主刻度Y起始点
    int     nUseCount   = 0;                //数据页面显示的条数

    //取一般页面画图的属性
    QColor  mFBackcolor    = ui->pushButton_backcolor->palette().background().color(); //框架的背景色
    QColor  mFBorderColor  = ui->pushButton_framecolor->palette().background().color();//框架的边框色
    bool    bIfVertical    = true;                 //是否垂直显示
    bool    bIfHorizon     = true;                 //是否水平
    QColor  mLineColor     = ui->pushButton_frontcolor->palette().background().color(); //格线颜色,跟边框色一样
    //int     nLanguageCount = ui->comboBox_language->count();//语言总数

    int iLan = curLan;//pwnd->qLanguagecmb->currentIndex();
    if(iLan < 0)
    {
        iLan = 0;
    }
    nVal = ui->spinBox_Tfontsize->value();
    /*for(i = 1; i < nLanguageCount; i++)                                  //求最大的字体大小
    {
        if(nVal <  page1->m_vecHisText[i].m_nTitleFontSize)
        {
            nVal = page1->m_vecHisText[i].m_nTitleFontSize;
        }
    }*/

    int     nTFontSize  = ui->spinBox_Tfontsize->value();                           //以语言1字体大小
    QString sTFont      = ui->comboBox_Tfonttype->currentText();                    //以语言1的字体
    QColor  mTBackColor = ui->pushButton_BKcolor->palette().background().color();   //标题列背景色
    QColor  mTTextColor = ui->pushButton_Tfontcolor->palette().background().color();//标题列的文本颜色
    bool    bIfTime     = ui->checkBox_time->isChecked();                         //是否显示时间列
    QString sTime       = m_vecMessage[iLan].m_sTimeName;                           //以语言1显示时间内容
    bool    bIfDate     = ui->checkBox_date->isChecked();                           //是否显示日期列
    QString sDate       = m_vecMessage[iLan].m_sDateName;                           //以语言1显示日期内容
    int     nRow        = ui->spinBox_line->value();                                //行数
    int     aph         = ui->spinBox_transparency->value();                        //透明度

    int             nH      = 25;  //每格的高度 10
    int             nTotalH = nH*(nRow + 1);
    int             nW      = 480; //背景框的总宽度120
    int             nTexeW  = 0;   //文本的宽度120
    QString         sName   = "";
    QLineItem       *pLine;
    QSimpleTextItem *pText;
    QStringList     sDataName;
    bool            bIfNumber    = ui->checkBox_number->isChecked(); //是否选择了显示编号
    int             nValue       = 0;
    bool            bDoubleClick = false;

    //画背景矩形
    QRectF rect(QPointF(0,0), QSize(nW,(nRow+1)*nH));   //绘制背景矩形
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(mFBackcolor);               //背景框的背景色
    pFramRect->SetLineColor(mFBorderColor);             //背景框的边框色
    pFramRect->SetAlpha(aph);
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetName("mFramRect");
    m_pCopyItem->addToGroup(pFramRect);                 //添加到组

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

    sDataName.append(m_vecMessage[iLan].m_sMessageName);
    int nshow = 1;
    /*int temp = page2->m_vecHisData[page2->m_nCurLanNum].m_vecInfo.size();
    int nshow = 0;
    for(i = 0; i < temp; i++)
    {
        if(page2->m_vecHisData[page2->m_nCurLanNum].m_vecInfo[i].m_bShow) //显示条数计数
        {
            nshow++;
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
    }*/

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
    pTitleRect->SetAlpha(aph);
    pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTitleRect->SetName("mTitleRect");
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
        pText = new QSimpleTextItem(rect, m_vecMessage[iLan].m_sNumber);
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(sTFont);
        pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetAlpha(aph);
        pText->SetName("NoText0");
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        m_pCopyItem->addToGroup(pText);
    }

    for(i; i < nValue; i++)// for(i = 0; i < nUseCount;i++)
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
        {
            pText = new QSimpleTextItem(rect,sDataName.at(i-1));
        }
        else
        {
            pText = new QSimpleTextItem(rect,sDataName.at(i));
        }
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(sTFont);
        pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName(QString("Text%1").arg(i));
        pText->SetRectOutLine(false);
        pText->SetAlpha(aph);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        m_pCopyItem->addToGroup(pText);                   //添加到组
    }

    //画水平线
    if(bIfHorizon)//选中了水平选择框
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
            //pLine->setAlpha(aph);
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
                pText->SetFontName(tr("宋体"));
                //pText->SetFontColor(mTTextColor); //字体颜色
                pText->SetName(QString("NoText%1").arg(i + 1));
                pText->SetRectOutLine(false);
                pText->SetAlpha(aph);
                pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
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
            //pLine->setAlpha(aph);
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "VLine"+sName;
            pLine->SetName(sName);
            m_pCopyItem->addToGroup(pLine);                   //添加到组
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

void qMessageBoard::drawSence()
{
    if(pTempItem)
    {
        delete pTempItem;
    }
    pTempItem = new qMessageBoradAttr;

    int     i           = 0;
    int     nVal        = 0;
    double  mMoveX      = 0;                //主刻度X起始点
    double  mMoveY      = 0;                //主刻度Y起始点
    double  mLineX      = 0;                //主刻度X起始点
    double  mLineY      = 0;                //主刻度Y起始点
    int     nUseCount   = 0;                //数据页面显示的条数

    //取一般页面画图的属性
    QColor  mFBackcolor    = ui->pushButton_backcolor->palette().background().color(); //框架的背景色
    QColor  mFBorderColor  = ui->pushButton_framecolor->palette().background().color();//框架的边框色
    bool    bIfVertical    = true;                 //是否垂直显示
    bool    bIfHorizon     = true;                 //是否水平
    QColor  mLineColor     = ui->pushButton_frontcolor->palette().background().color(); //格线颜色,跟边框色一样
    //int     nLanguageCount = ui->comboBox_language->count();//语言总数

    int iLan = curLan;
    if(iLan < 0)
    {
        iLan = 0;
    }
    nVal = ui->spinBox_Tfontsize->value();
    /*for(i = 1; i < nLanguageCount; i++)                                  //求最大的字体大小
    {
        if(nVal <  page1->m_vecHisText[i].m_nTitleFontSize)
        {
            nVal = page1->m_vecHisText[i].m_nTitleFontSize;
        }
    }*/

    int     nTFontSize  = ui->spinBox_Tfontsize->value();                           //以语言1字体大小
    QString sTFont      = ui->comboBox_Tfonttype->currentText();                    //以语言1的字体
    QColor  mTBackColor = ui->pushButton_BKcolor->palette().background().color();   //标题列背景色
    QColor  mTTextColor = ui->pushButton_Tfontcolor->palette().background().color();//标题列的文本颜色
    bool    bIfTime     = ui->checkBox_time->isChecked();                         //是否显示时间列
    QString sTime       = m_vecMessage[iLan].m_sTimeName;                           //以语言1显示时间内容
    bool    bIfDate     = ui->checkBox_date->isChecked();                           //是否显示日期列
    QString sDate       = m_vecMessage[iLan].m_sDateName;                           //以语言1显示日期内容
    int     nRow        = ui->spinBox_line->value();                                //行数
    int     aph         = ui->spinBox_transparency->value();                        //透明度
    //if(nRow > 20)//最多显示20行，多的不显示
    //{
    //    nRow = 20;
    //}
    int totalHeight         = ui->graphicsView->size().height();
    int             nH      = (totalHeight - 10) / (nRow + 1);  //每格的高度 10
    int             nTotalH = nH*(nRow + 1);
    int             nW      = 120; //背景框的总宽度120
    int             nTexeW  = 0;   //文本的宽度120
    QString         sName   = "";
    QLineItem       *pLine;
    QSimpleTextItem *pText;
    QStringList     sDataName;
    bool            bIfNumber    = ui->checkBox_number->isChecked(); //是否选择了显示编号
    int             nValue       = 0;
    //bool            bDoubleClick = false;

    //画背景矩形
    QRectF rect(QPointF(0,0), QSize(nW,(nRow+1)*nH));   //绘制背景矩形
    QRectItem *pFramRect = new QRectItem(rect);
    pFramRect->SetBackColor(mFBackcolor);               //背景框的背景色
    pFramRect->SetLineColor(mFBorderColor);             //背景框的边框色
    pFramRect->SetAlpha(aph);
    pFramRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pFramRect->SetName("mFramRect");
    pTempItem->addToGroup(pFramRect);                 //添加到组

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

    sDataName.append(m_vecMessage[iLan].m_sMessageName);
    int nshow = 1;
    /*int temp = page2->m_vecHisData[page2->m_nCurLanNum].m_vecInfo.size();
    int nshow = 0;
    for(i = 0; i < temp; i++)
    {
        if(page2->m_vecHisData[page2->m_nCurLanNum].m_vecInfo[i].m_bShow) //显示条数计数
        {
            nshow++;
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
    }*/

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

    /*if(nValue == (vVLine.size() - 1) && nRow == (vHLine.size() - 2))
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
    }*/

    //画标题列
    rect.setWidth(nW);                                //绘制标题列
    rect.setHeight(nH);
    /*if(bDoubleClick)
    {
        rect.setHeight(vHLine.at(1) - vHLine.at(0));
    }*/
    QRectItem *pTitleRect = new QRectItem(rect);
    pTitleRect->SetBackColor(mTBackColor);            //标题列矩形框背景色
    pTitleRect->SetLineType(0);
    pTitleRect->SetAlpha(aph);
    pTitleRect->setFlag(QGraphicsItem::ItemIsSelectable, false);
    pTitleRect->SetName("mTitleRect");
    pTempItem->addToGroup(pTitleRect);                   //添加到组

    if(1 == i)//画序号
    {
        rect.setTopLeft(QPointF(0,0));           //绘制文本pText
        rect.setSize(QSize(nTexeW,nH));
        /*if(bDoubleClick)
        {
            rect.setSize(QSize(vVLine.at(1) - vVLine.at(0),vHLine.at(1) - vHLine.at(0)));
        }*/

        //if(bIfNumber)此时这句话一定成立
        pText = new QSimpleTextItem(rect, m_vecMessage[iLan].m_sNumber);
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(sTFont);
        pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName("NoText0");
        pText->SetAlpha(aph);
        pText->SetRectOutLine(false);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pTempItem->addToGroup(pText);
    }

    for(i; i < nValue; i++)// for(i = 0; i < nUseCount;i++)
    {
        rect.setTopLeft(QPointF(i*nTexeW,0));           //绘制文本pText
        rect.setSize(QSize(nTexeW,nH));
        /*if(bDoubleClick)
        {
            rect.setTopLeft(QPointF(vVLine.at(i),0));           //绘制文本pText
            rect.setSize(QSize(vVLine.at(i+1) - vVLine.at(i),vHLine.at(1) - vHLine.at(0)));
        }*/
        //pText = new QSimpleTextItem(rect,sDataName.at(i));
        if(bIfNumber)
        {
            pText = new QSimpleTextItem(rect,sDataName.at(i-1));
        }
        else
        {
            pText = new QSimpleTextItem(rect,sDataName.at(i));
        }
        pText->SetFontSize(nTFontSize);
        pText->SetFontName(sTFont);
        pText->SetFontColor(mTTextColor); //字体颜色
        pText->SetName(QString("Text%1").arg(i));
        pText->SetRectOutLine(false);
        pText->SetAlpha(aph);
        pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
        pTempItem->addToGroup(pText);                   //添加到组
    }

    //画水平线
    if(bIfHorizon)//选中了水平选择框
    {
        for(i = 0; i < nRow; i++)
        {
            QPainterPath mPath;
            mMoveX = 0;
            mMoveY = i*nH+nH;
            mLineX = 0+nW;
            mLineY = i*nH+nH;
            /*if(bDoubleClick)
            {
                mMoveY = vHLine.at(i+1);
                mLineY = vHLine.at(i+1);
            }*/
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            pLine->setLineColor(mLineColor);     //设置直线颜色
            //pLine->setAlpha(aph);
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "HLine"+sName;
            pLine->SetName(sName);
            pTempItem->addToGroup(pLine);                   //添加到组

            if(bIfNumber)
            {
                rect.setTopLeft(QPointF(0, (i+1)*nH));           //绘制文本pText
                rect.setSize(QSize(nTexeW,nH));
                /*if(bDoubleClick)
                {
                    rect.setTopLeft(QPointF(0,vHLine.at(i+1)));           //绘制文本pText
                    rect.setSize(QSize(vVLine.at(1) - vVLine.at(0),vHLine.at(i+2) - vHLine.at(i+1)));
                }*/
                pText = new QSimpleTextItem(rect,QString("%1").arg(i+1));
                pText->SetFontSize(nTFontSize);
                pText->SetFontName(tr("宋体"));
                //pText->SetFontColor(mTTextColor); //字体颜色
                pText->SetName(QString("NoText%1").arg(i + 1));
                pText->SetRectOutLine(false);
                pText->SetAlpha(aph);
                pText->setFlag(QGraphicsItem::ItemIsSelectable, false);
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
            /*if(bDoubleClick)
            {
                mMoveX = vVLine.at(i);
                mLineX = vVLine.at(i);
            }*/
            mPath.moveTo(mMoveX,mMoveY);         //画直线的起点
            mPath.lineTo(mLineX,mLineY);         //画直线的终点
            pLine = new QLineItem(mPath);        //画细直线
            pLine->setLineColor(mLineColor);     //设置直线颜色
            //pLine->setAlpha(aph);
            pLine->setFlag(QGraphicsItem::ItemIsSelectable, false);

            sName = QString("%1").arg(i);
            sName = "VLine"+sName;
            pLine->SetName(sName);
            pTempItem->addToGroup(pLine);                   //添加到组
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
}




