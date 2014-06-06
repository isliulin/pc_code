#include "qvaluecolordlg.h"
#include "ui_qvaluecolordlg.h"
#include "qvaluedlg.h"
#include "Frame/DrawDlg/OpenLibrary.h"

extern MainWindow *pwnd;

QValueColorDlg::QValueColorDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QValueColorDlg)
{
    bInitFlag = false;
    ui->setupUi(this);
    pLibItem = NULL;
    newimage = NULL;
}

void QValueColorDlg::Init(DataDisplayItem *pItem)
{
    if(pItem)
    {
        if(DATAINPUTSHOW == pItem->m_etabPag)
        {
            onSetValueColor(pwnd->StringTOColor(pItem->m_data.nFontColor));
            onSetValueBackColor(pwnd->StringTOColor(pItem->m_data.nBackColor));
            onSetLowColor(pwnd->StringTOColor(pItem->m_data.nLowerColor));
            onSetHightColor(pwnd->StringTOColor(pItem->m_data.nHightColor));

            ui->m_nHightNumberspBox->setText(pItem->m_data.nHightNumber);
            ui->m_nLowerNumberspBox->setText(pItem->m_data.nLowerNumber);
            ui->m_TransparentspBox->setValue(pItem->m_data.nTransparent);
        }
        else if(ASCIIINPUTSHOW == pItem->m_etabPag)
        {
            onSetValueColor(pwnd->StringTOColor(pItem->m_ascii.nFontColor));
            onSetValueBackColor(pwnd->StringTOColor(pItem->m_ascii.nBackColor));
            ui->m_TransparentspBox->setValue(pItem->m_ascii.nTransparent);
        }
        else if(DATETIMEINPUT == pItem->m_etabPag)
        {
            onSetValueColor(pwnd->StringTOColor(pItem->m_time.nFontColor));
            onSetValueBackColor(pwnd->StringTOColor(pItem->m_time.nBackground));
            ui->m_TransparentspBox->setValue(pItem->m_time.nTransparent);
        }

        if(0 == pItem->GetPattern())
        {
            ui->m_DataBackColorlabel->setEnabled(false);
            ui->m_DataBackColorBtn->setEnabled(false);
        }
        if(pItem->childItems().size() > 1)
        {
            ui->m_TransparentspBox->setEnabled(false);
            ui->m_Transparentlabel->setEnabled(false);
        }
    }
    else
    {
        onSetValueColor(QColor(0,0,0));
        onSetValueBackColor(QColor(160,160,255));
        onSetLowColor(QColor(255,0,0));
        onSetHightColor(QColor(0,255,255));
        ui->m_DataColorBtn->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
        ui->m_DataBackColorBtn->setStyleSheet(QString("background:%1").arg(QColor(160,160,255).name()));
        ui->m_LowColorBtn->setStyleSheet(QString("background:%1").arg(QColor(255,0,0).name()));
        ui->m_HightColorBtn->setStyleSheet(QString("background:%1").arg(QColor(0,255,255).name()));
    }
    bInitFlag = true;
}

QValueColorDlg::~QValueColorDlg()
{
    delete ui;
}

void QValueColorDlg::onTabWightSwitch(int eType)
{
    switch(eType)
    {
    case DATAINPUTSHOW:
        ui->m_LowColorlabel->setEnabled(true);
        ui->m_LowColorBtn->setEnabled(true);
        ui->m_HightColorlabel->setEnabled(true);
        ui->m_HightColorBtn->setEnabled(true);
        ui->m_DataColorlabel->setText(tr("数值颜色"));
        ui->m_DataBackColorlabel->setText(tr("数值背景颜色"));

        ui->m_nLowerNumberspBox->setEnabled(true);
        ui->m_nHightNumberspBox->setEnabled(true);
        ui->m_nHightNumberlabel->setEnabled(true);
        ui->m_nLowerNumberlabel->setEnabled(true);
        break;
    case ASCIIINPUTSHOW:
        ui->m_LowColorlabel->setEnabled(false);
        ui->m_LowColorBtn->setEnabled(false);
        ui->m_HightColorlabel->setEnabled(false);
        ui->m_HightColorBtn->setEnabled(false);
        ui->m_DataColorlabel->setText(tr("文本颜色"));
        ui->m_DataBackColorlabel->setText(tr("文本背景颜色"));

        ui->m_nLowerNumberspBox->setEnabled(false);
        ui->m_nHightNumberspBox->setEnabled(false);
        ui->m_nHightNumberlabel->setEnabled(false);
        ui->m_nLowerNumberlabel->setEnabled(false);
        break;
    case DATETIMEINPUT:
        ui->m_LowColorlabel->setEnabled(false);
        ui->m_LowColorBtn->setEnabled(false);
        ui->m_HightColorlabel->setEnabled(false);
        ui->m_HightColorBtn->setEnabled(false);
        ui->m_DataColorlabel->setText(tr("数值颜色"));
        ui->m_DataBackColorlabel->setText(tr("数值背景颜色"));

        ui->m_nLowerNumberspBox->setEnabled(false);
        ui->m_nHightNumberspBox->setEnabled(false);
        ui->m_nHightNumberlabel->setEnabled(false);
        ui->m_nLowerNumberlabel->setEnabled(false);
        break;
    default:
        return;
    }
}

void QValueColorDlg::onSetValueColor(const QColor &mColor)
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_DataColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(bInitFlag)
    {
        emit onDrawSence("FontColor");
    }
}

void QValueColorDlg::onSetValueBackColor(const QColor &mColor)
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_DataBackColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(bInitFlag)
    {
        emit onDrawSence("BackColor");
    }
}

void QValueColorDlg::onSetLowColor(const QColor &mColor)
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_LowColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QValueColorDlg::onSetHightColor(const QColor &mColor)
{
    QString nColor = pwnd->ColorTOString(mColor);
    ui->m_HightColorBtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
}

void QValueColorDlg::on_m_DataColorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_DataColorBtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(onSetValueColor(const QColor &)));
}

void QValueColorDlg::on_m_DataBackColorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_DataBackColorBtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(onSetValueBackColor(const QColor &)));
}

void QValueColorDlg::on_m_LowColorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_LowColorBtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(onSetLowColor(const QColor &)));
}

void QValueColorDlg::on_m_HightColorBtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_HightColorBtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(onSetHightColor(const QColor &)));
}

void QValueColorDlg::onGetValueColor(QColor &mColor)
{
   mColor = ui->m_DataColorBtn->palette().background().color();
}

void QValueColorDlg::onGetValueBackColor(QColor &mColor)
{
    mColor = ui->m_DataBackColorBtn->palette().background().color();
    //QString sname = pwnd->ColorTOString(Color);
}

void QValueColorDlg::onGetLowColor(QColor &mColor)
{
    mColor = ui->m_LowColorBtn->palette().background().color();
}

void QValueColorDlg::onGetHightColor(QColor &mColor)
{
    mColor = ui->m_HightColorBtn->palette().background().color();
}

void QValueColorDlg::onDataGenSave(DataInfo &data_st)
{
    data_st.nFontColor = pwnd->ColorTOString(ui->m_DataColorBtn->palette().background().color());//字体颜色
    data_st.nBackColor = pwnd->ColorTOString(ui->m_DataBackColorBtn->palette().background().color());//字体背景颜色
    data_st.nLowerColor = pwnd->ColorTOString(ui->m_LowColorBtn->palette().background().color());//低位背景颜色
    data_st.nHightColor = pwnd->ColorTOString(ui->m_HightColorBtn->palette().background().color());//高位背景颜色

    data_st.nHightNumber = ui->m_nHightNumberspBox->text();
    data_st.nLowerNumber = ui->m_nLowerNumberspBox->text();
    data_st.nTransparent = ui->m_TransparentspBox->value();
}
void QValueColorDlg::onAsciiGenSave(ASCIIINFO &ascii_st)
{
    ascii_st.nFontColor = pwnd->ColorTOString(ui->m_DataColorBtn->palette().background().color());//字体颜色
    ascii_st.nBackColor = pwnd->ColorTOString(ui->m_DataBackColorBtn->palette().background().color());//字体背景颜色
    ascii_st.nTransparent = ui->m_TransparentspBox->value();
}
void QValueColorDlg::onTimeGenSave(TIMEINFO &time_st)//保存时间显示信息
{
    time_st.nFontColor = pwnd->ColorTOString(ui->m_DataColorBtn->palette().background().color());//字体颜色
    time_st.nBackground = pwnd->ColorTOString(ui->m_DataBackColorBtn->palette().background().color());//字体背景颜色
    time_st.nTransparent = ui->m_TransparentspBox->value();
}

void QValueColorDlg::onSelectpicbtn(int nType)
{
    pLibItem=NULL;
    QString sPath = "";
    QPointF pos;

    if(0 == nType) //从文件读取图片
    {
        EITEM_TYPE eIspic = PIC;
        QString filename=QFileDialog::getOpenFileName(this,
                                                      tr("Open File"),pwnd->picturePath,
                                                      tr("Images (*.png *.jpg *.bmp)"));
        QPixmap picture = QPixmap(filename);
        if (!picture)
        {
            return ;
        }

        sPath = filename;
        pwnd->picturePath=filename;
        newimage = picture;
        QPixmapItem *PicItem = new QPixmapItem(newimage,QSize(100,100));

        pLibItem = PicItem;
        sPath = sPath;
        emit addPicture(pLibItem,&newimage,sPath,eIspic);
        ui->m_TransparentspBox->hide();
        ui->m_Transparentlabel->hide();
    }
    else if(1 == nType) //系统图库
    {

        OpenLibrary *pDlg = new OpenLibrary(this);
        if(pDlg->exec() == QDialog::Accepted)
        {
            DrawItemToScene GroupFunction;
            if(pLibItem)
            {
                delete pLibItem;
                pLibItem = NULL;
            }
            EITEM_TYPE eIspic;
            if(LIBRARY_LIB_GROUP == pDlg->pCopyItem->data(GROUP_TYPE_KEY).toInt())
            {
                eIspic = LIBRARY;
            }
            else
            {
                eIspic = USERDEFINE;
            }
            GroupFunction.CopyItem(&pLibItem,pDlg->pCopyItem);

            QGroupItem *pBaseItem = new QGroupItem(pLibItem);
            pBaseItem->SetWidth(100);
            pBaseItem->SetHeigth(100);

            newimage = NULL;

            sPath = pLibItem->data(GROUP_NAME_KEY).toString();
            emit addPicture(pLibItem,&newimage,sPath,eIspic);
            ui->m_DataBackColorlabel->setEnabled(false);
            ui->m_DataBackColorBtn->setEnabled(false);
            ui->m_TransparentspBox->setEnabled(false);
            ui->m_Transparentlabel->setEnabled(false);
        }
        pDlg->deleteLater();
        pDlg = NULL;
    }
}

void QValueColorDlg::on_m_deletepicbtn_clicked()
{
    EITEM_TYPE eIspic = PIC;
    emit addPicture(NULL,NULL,"",eIspic);
    ui->m_DataBackColorlabel->setEnabled(true);
    ui->m_DataBackColorBtn->setEnabled(true);
    ui->m_TransparentspBox->setEnabled(true);
    ui->m_Transparentlabel->setEnabled(true);
}

void QValueColorDlg::setdataRange(double dMax, double dMin, int type, int base)
{
    DoubleValidator *aDoubleValidator = new DoubleValidator(this,base);
    aDoubleValidator->setNotation(QDoubleValidator::StandardNotation);
    if(0 == type)
    {
        aDoubleValidator->setRange(dMin,dMax,4);
    }
    else
    {
        aDoubleValidator->setRange(dMin,dMax);
    }

    ui->m_nHightNumberspBox->setValidator(aDoubleValidator);
    ui->m_nLowerNumberspBox->setValidator(aDoubleValidator);

    if(10 == base)
    {
        ui->m_nHightNumberspBox->setText(QString::number(dMax,'g',10));
        ui->m_nLowerNumberspBox->setText(QString::number(dMin,'g',10));
    }
    else if(16 == base || 8 == base)
    {
        unsigned int nMin = dMin;
        unsigned int nMax = dMax;

        ui->m_nLowerNumberspBox->setText(QString::number(nMin,base));

        ui->m_nHightNumberspBox->setText(QString::number(nMax,base));
    }
}
void QValueColorDlg::on_m_SelectLibpushBtn_clicked()
{
    onSelectpicbtn(1);
}

void QValueColorDlg::on_m_SelectPicpushBtn_clicked()
{
    onSelectpicbtn(0);
}

int QValueColorDlg::onGetTransparent()
{
    return ui->m_TransparentspBox->value();
}

void QValueColorDlg::on_m_TransparentspBox_valueChanged(int )
{
    if(bInitFlag)
    {
        emit onDrawSence("BackColor");
    }
}
