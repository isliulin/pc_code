#include "qkeyboardasciigen.h"
#include "ui_qkeyboardasciigen.h"
#include "Frame/DrawDlg/LoadShape.h"
#include "Frame/mainwindow.h"
//#include "qwordbtngeneraldlg.h"
#include "view/keyboarditem.h"
#include "Frame/DrawDlg/OpenLibrary.h"
#include <QFontDatabase>
extern MainWindow *pwnd;

QKeyboardASCIIGen::QKeyboardASCIIGen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QKeyboardASCIIGen)
{
    key.sPath = "";
    bState = false;
    ui->setupUi(this);
    ui->comboBox_font->addItems(QFontDatabase().families(QFontDatabase::Any));
    pwnd->InitFontSize(ui->m_fontsizecmb);//初始化字体大小下拉列表框
    //图片单选按钮（系统、本地图片）
    RadioButton_screen_Group = new QButtonGroup(this);
    RadioButton_screen_Group->addButton(ui->m_sysradio,1);
    RadioButton_screen_Group->addButton(ui->m_fileradio,2);
    pCopyItem=new KeyBoardItem;
    nInitFlag=false;//样式标示
    ui->State0->setEnabled(false);
    //pScene = new QGraphicsScene(this);
    //ui->graphicsView->setScene(pScene);          //用视图显示场景
    pwnd->OnAddPattern(ui->Pattern);  //加载样式
    TypeCheck=new QButtonGroup(this);
    TypeCheck->addButton(ui->ENTER,1);
    TypeCheck->addButton(ui->BACKSPACE,2);
    TypeCheck->addButton(ui->CLEAR,3);
    TypeCheck->addButton(ui->ESC,4);
    TypeCheck->addButton(ui->ASCII,5);
    TypeCheck->addButton(ui->CAPSLOCK,6);

    //语言
    QVector<QString>language_vector;
    ui->combo_Language->clear();
    int languageCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();

    for(int i=0; i<languageCount; i++)
    {
        language_vector.push_back(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }
    for(int i=0; i<languageCount; i++)
    {
        ui->combo_Language->addItem(language_vector.at(i));
    }
    //隐藏多语言
    ui->label_type_2->setDisabled(false);
    ui->combo_Language->setDisabled(false);
    nInitFlag=true;

}

QKeyboardASCIIGen::~QKeyboardASCIIGen()
{
//    if(pScene)
//    {
//        delete pScene;
//        pScene = NULL;
//    }
//    if(pBaseItem)
//    {
//        delete pBaseItem;
//        pBaseItem = NULL;
//    }
    if(TypeCheck)
    {
        delete TypeCheck;
        TypeCheck = NULL;
    }

    delete ui;
}

void QKeyboardASCIIGen::on_Pattern_activated(int index)
{
        return;
    pBaseItem->SetPropertyValue("mBackRect.Pattern",QVariant(index));

    if(index == 0)
    {
        pBaseItem->SetPropertyValue("mFramRect.Pattern",QVariant(0));
        pBaseItem->setItemPattern(0);
    }
    else
    {
        pBaseItem->SetPropertyValue("mFramRect.Pattern",QVariant(1));
        pBaseItem->setItemPattern(1);
    }
}
void QKeyboardASCIIGen::ASCIIEntryGenSave(KeyInfo &keyInfo)
{
    key.nLanguage = ui->combo_Language->currentIndex();//语言
    key.sFontFamily = ui->comboBox_font->currentText();//字体
    key.nPosition = ui->combo_Alignment->currentIndex();//位置 居中 左对齐 右对齐
    key.nFontSize = ui->m_fontsizecmb->currentIndex(); //字体大小
    key.sColor = ui->m_textbtn->palette().background().color();//字体颜色

    if(ui->ENTER->isChecked())
    {
        key.keyOperation = ENTER;
    }
    else if(ui->ESC->isChecked())
    {
        key.keyOperation = ESC;
    }
    else if(ui->CLEAR->isChecked())
    {
        key.keyOperation = CLEAR;
    }
    else if(ui->BACKSPACE->isChecked())
    {
        key.keyOperation = BACKSPACE;
    }
    else if(ui->CAPSLOCK->isChecked())
    {
        key.keyOperation = CAPSLOCK;
    }
    else if(ui->ASCII->isChecked())
    {
        key.keyOperation = ASCII;
    }

    key.ASCIIStr = ui->ASCIIText->text();//
    if(ui->m_sysradio->isChecked())
    {
        key.nPicChecked = 0;
    }
    else
    {
        key.nPicChecked = 1;
    }

    key.sText = ui->m_text->toPlainText();//文本

    key.eFontCss = 0;
    if(ui->m_boldcheck->isChecked())
    {
        key.eFontCss = (key.eFontCss | 1);
    }
    if(ui->m_italiccheck->isChecked())
    {
        key.eFontCss = (key.eFontCss | 2);
    }
    if(ui->m_underlinecheck->isChecked())
    {
        key.eFontCss = (key.eFontCss | 8);
    }
    keyInfo = key;
}
void QKeyboardASCIIGen::Init(KeyBoardItem *pItem)
{

    isflag=false;
    if(pItem)   //从Data 的 stringList中获取属性并设置
    {
        key = pItem->m_key;

        ui->combo_Language->setCurrentIndex(key.nLanguage);//语言
        int index = ui->comboBox_font->findText(key.sFontFamily);
        if(index >= 0)
        {
            ui->comboBox_font->setCurrentIndex(index);//字体
        }
        ui->combo_Alignment->setCurrentIndex(key.nPosition);//位置 居中 左对齐 右对齐
        ui->m_fontsizecmb->setCurrentIndex(key.nFontSize); //字体大小
        ui->m_textbtn->setStyleSheet(QString("background:%1").arg(key.sColor.name()));//字体颜色

        if(ENTER == key.keyOperation)
        {
            ui->ENTER->setChecked(true);
            ui->ASCIIText->hide();
        }
        else if(ESC == key.keyOperation)
        {
            ui->ESC->setChecked(true);
            ui->ASCIIText->hide();
        }
        else if(CLEAR == key.keyOperation)
        {
            ui->CLEAR->setChecked(true);
            ui->ASCIIText->hide();
        }
        else if(BACKSPACE == key.keyOperation)
        {
            ui->BACKSPACE->setChecked(true);
            ui->ASCIIText->hide();
        }
        else if(CAPSLOCK == key.keyOperation)
        {
            ui->CAPSLOCK->setChecked(true);
            ui->ASCIIText->hide();
        }
        else if(ASCII == key.keyOperation)
        {
            ui->ASCII->setChecked(true);
            ui->ASCIIText->show();
        }

        ui->ASCIIText->setText(key.ASCIIStr);//
        if(0 == key.nPicChecked)
        {
            ui->m_sysradio->setChecked(true);
        }
        else
        {
            ui->m_fileradio->setChecked(true);
        }

        ui->m_text->setPlainText(key.sText);//文本

        ui->Frame_Color->setStyleSheet(QString("background:%1").arg(key.nUpFrameColor.name()));
        ui->FG_Color->setStyleSheet(QString("background:%1").arg(key.nUpForeColor.name()));
        ui->BG_Color->setStyleSheet(QString("background:%1").arg(key.nUpBackColor.name()));

         //粗体、斜体和下划线
         if((1&(key.eFontCss)))
         {
             ui->m_boldcheck->setChecked(true);
         }
         if((2&(key.eFontCss)))
         {
             ui->m_italiccheck->setChecked(true);
         }
         if((8&(key.eFontCss)))
         {
             ui->m_underlinecheck->setChecked(true);
         }

         ui->Pattern->setCurrentIndex(key.eUpStyle);//样式

    }
    else
    {
        /***************************************************
         *以下是单击工具栏的初始化
         **************************************************/
        ui->ASCII->setChecked(true);
        //ui->ID->setText(pwnd->GetControlNO("KB"));

        key.nDownBackColor = QColor(192,192,192);
        key.nDownForeColor = QColor(0,0,0);
        key.nDownFrameColor = QColor(224,224,224);

        key.nUpBackColor = QColor(192,192,192);
        key.nUpForeColor = QColor(0,0,0);
        key.nUpFrameColor = QColor(224,224,224);

        key.eUpStyle = 1;
        key.eDownStyle = 1;

        ui->m_text->setPlainText(tr("输入文本"));
        key.sText = tr("输入文本");

        ui->Frame_Color->setStyleSheet( QString("background:%1").arg(QColor(224,224,224).name()));
        ui->FG_Color->setStyleSheet( QString("background:%1").arg(QColor(0,0,0).name()));
        ui->BG_Color->setStyleSheet( QString("background:%1").arg(QColor(192,192,192).name()));
        TypeCheck->button(5)->setChecked(true);
        //on_State0_clicked();
        //文本
        int index = ui->comboBox_font->findText(tr("宋体"));
        if(index >= 0)
        {
           ui->comboBox_font->setCurrentIndex(index);
        }
        key.sFontFamily = ui->comboBox_font->currentText();

        ui->m_textbtn->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
        key.sColor = QColor(0,0,0);
        ui->m_fontsizecmb->setCurrentIndex(5);
        key.nFontSize = 5;

        key.eFontCss = 0;
        key.nPosition = 0;
    }
    isflag=true;
}


void QKeyboardASCIIGen::on_ASCIIText_textChanged(QString str)
{
    if(ui->ASCII->isChecked())
    {
        str=str.left(1);
    }
 }

void QKeyboardASCIIGen::on_Frame_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->Frame_Color,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setFrameColor(const QColor &)));
}

//设置边框色
void QKeyboardASCIIGen::setFrameColor(const QColor & mColor)
{
    int iFlag = 0;
    ui->Frame_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(bState)//after
    {
        iFlag = 1;
        key.nDownFrameColor = mColor;
    }
    else
    {
        iFlag = 0;
        key.nUpFrameColor = mColor;
    }
    emit onKeypress(iFlag);
}

void QKeyboardASCIIGen::on_FG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->FG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setFGColor(const QColor &)));
}

//前景色
void QKeyboardASCIIGen::setFGColor(const QColor & mColor)       //前景色
{
    int iFlag = 0;
    QString nColor = pwnd->ColorTOString(mColor);
    ui->FG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(bState)//after
    {
        iFlag = 1;
        key.nDownForeColor = mColor;
    }
    else
    {
        iFlag = 0;
        key.nUpForeColor = mColor;
    }
    emit onKeypress(iFlag);
}

void QKeyboardASCIIGen::on_BG_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->BG_Color ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBGColor(const QColor &)));

}
//背景色
void QKeyboardASCIIGen::setBGColor(const QColor & mColor)
{
    int iFlag = 0;
    QString nColor = pwnd->ColorTOString(mColor);
    ui->BG_Color->setStyleSheet(QString("background:%1").arg(mColor.name()));
    if(bState)//after
    {
        iFlag = 1;
        key.nDownBackColor = mColor;
    }
    else
    {
        iFlag = 0;
        key.nUpBackColor = mColor;
    }
    emit onKeypress(iFlag);
}

//ENTER
void QKeyboardASCIIGen::on_ENTER_clicked(bool checked)
{
    if(checked)
    {
    ui->ASCIIText->setHidden(true);
    }
}

//BACKSPACE
void QKeyboardASCIIGen::on_BACKSPACE_clicked(bool checked)
{
    if(checked)
    {
        ui->ASCIIText->setHidden(true);
    }
}

//CLEAR
void QKeyboardASCIIGen::on_CLEAR_clicked(bool checked)
{
    if(checked)
    {
        ui->ASCIIText->setHidden(true);

    }
}

//ESC
void QKeyboardASCIIGen::on_ESC_clicked(bool checked)
{
    if(checked)
    {
        ui->ASCIIText->setHidden(true);
    }
}

//ASCII
void QKeyboardASCIIGen::on_ASCII_clicked(bool checked)
{
    if(checked)
    {
        ui->ASCIIText->setHidden(false);

    }
}

//void QKeyboardASCIIGen::on_LoadShape_clicked()
//{
//    LoadShape *pShapeDlg = new LoadShape(this);
//    if(pShapeDlg->exec() == QDialog::Accepted)
//    {
//        DrawItemToScene GroupFunction;
//        QPixmap *pic = NULL;
//        pic = pBaseItem->Pictrue();
//        QPointF oldpos = pOldItem->sceneBoundingRect().topLeft();
//        QGraphicsItem *pLibItem  = pwnd->IsHaveLibraryItem(pOldItem);

//        GroupFunction.CopyItem(&pOldItem,pShapeDlg->pCopyItem);
//        pScene->clear();
//        pScene->addItem(pOldItem);
//        pBaseItem = new QGroupItem(pOldItem);

//        setFrameColor(ui->Frame_Color->palette().background().color());       //设置边框色
//        setFGColor(ui->FG_Color->palette().background().color());       //前景色
//        setBGColor(ui->BG_Color->palette().background().color());       //背景色
//        on_Pattern_currentIndexChanged(ui->Pattern->currentIndex());//样式
//        //setTextColor(ui->Text_Color->palette().background().color());       //文本色
//               emit txtChange();
//        if(pic)
//        {
//            QPixmapItem *PicItem = new QPixmapItem(*pic,pic->size());
//            pLibItem = PicItem;
//            emit picChange(pLibItem,pic);
//        }
//        else
//        {
//            if(pLibItem)
//            {
//                emit picChange(pLibItem,NULL);
//            }
//        }

//        QPointF newpos = pOldItem->boundingRect().topLeft();
//        pOldItem->setPos(oldpos-newpos);
//    }
//    pShapeDlg->deleteLater();
//    pShapeDlg = NULL;
//}
//按下前
void QKeyboardASCIIGen::on_State0_clicked()
{
    //按下前
    ui->Frame_Color->setStyleSheet(QString("background:%1").arg(key.nUpFrameColor.name()));
    ui->FG_Color->setStyleSheet(QString("background:%1").arg(key.nUpForeColor.name()));
    ui->BG_Color->setStyleSheet(QString("background:%1").arg(key.nUpBackColor.name()));
    bState = false;
    ui->Pattern->setCurrentIndex(key.eUpStyle);
    ui->State1->setEnabled(true);
    ui->State0->setEnabled(false);
    emit onKeypress(0);
}
//按下后
void QKeyboardASCIIGen::on_State1_clicked()
{
    //按下后   
    ui->Frame_Color->setStyleSheet(QString("background:%1").arg(key.nDownFrameColor.name()));
    ui->FG_Color->setStyleSheet(QString("background:%1").arg(key.nDownForeColor.name()));
    ui->BG_Color->setStyleSheet(QString("background:%1").arg(key.nDownBackColor.name()));
    bState = true;
    ui->Pattern->setCurrentIndex(key.eDownStyle);

    ui->State1->setEnabled(false);
    ui->State0->setEnabled(true);
    emit onKeypress(1);
}
//文本
void QKeyboardASCIIGen::on_m_text_textChanged()
{
    if(!isflag)
        return;
   key.sText = ui->m_text->toPlainText();
   emit onDrawSence();
}


//粗体
void QKeyboardASCIIGen::on_m_boldcheck_clicked(bool checked)
{
    if(!isflag)
        return;
    key.eFontCss = 0;
    if(ui->m_boldcheck->isChecked())
    {
        key.eFontCss = (key.eFontCss | 1);
    }
    if(ui->m_italiccheck->isChecked())
    {
        key.eFontCss = (key.eFontCss | 2);
    }
    if(ui->m_underlinecheck->isChecked())
    {
        key.eFontCss = (key.eFontCss | 8);
    }
    emit onDrawSence();
}
//斜体
void QKeyboardASCIIGen::on_m_italiccheck_clicked(bool checked)
{
    if(!isflag)
        return;
    key.eFontCss = 0;
    if(ui->m_boldcheck->isChecked())
    {
        key.eFontCss = (key.eFontCss | 1);
    }
    if(ui->m_italiccheck->isChecked())
    {
        key.eFontCss = (key.eFontCss | 2);
    }
    if(ui->m_underlinecheck->isChecked())
    {
        key.eFontCss = (key.eFontCss | 8);
    }
    emit onDrawSence();
}
//下划线
void QKeyboardASCIIGen::on_m_underlinecheck_clicked(bool checked)
{
    if(!isflag)
        return;
    key.eFontCss = 0;
    if(ui->m_boldcheck->isChecked())
    {
        key.eFontCss = (key.eFontCss | 1);
    }
    if(ui->m_italiccheck->isChecked())
    {
        key.eFontCss = (key.eFontCss | 2);
    }
    if(ui->m_underlinecheck->isChecked())
    {
        key.eFontCss = (key.eFontCss | 8);
    }
    emit onDrawSence();
}
QString QKeyboardASCIIGen::onGetText()
{
    return ui->m_text->toPlainText();
}
//字体大小
void QKeyboardASCIIGen::on_m_fontsizecmb_currentIndexChanged(int index)
{
    if(!isflag)
        return;
    key.nFontSize =  index;
    emit onDrawSence();
}
//字体颜色
void QKeyboardASCIIGen::on_m_textbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_textbtn,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(OnSetTextColor(const QColor &)));
}
void QKeyboardASCIIGen::OnSetTextColor(const QColor & mColor)   //设置字体颜色
{
    if(!isflag)
        return;
    ui->m_textbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
    key.sColor = mColor;
    emit onDrawSence();
}
//字体属性
void QKeyboardASCIIGen::on_comboBox_font_currentIndexChanged(QString )
{
    if(!isflag)
        return;
    key.sFontFamily =ui->comboBox_font->currentText();
    emit onDrawSence();
}
//字体位置
void QKeyboardASCIIGen::on_combo_Alignment_currentIndexChanged(int index)
{
    if(!isflag)
        return;
    key.nPosition = index;
    emit onDrawSence();
}
//样式
void QKeyboardASCIIGen::on_Pattern_currentIndexChanged(int index)
{
    if(!isflag)
    {
        return;
    }
    int nType = 0;
    if(bState)//按下后
    {
        nType = 1;
        key.eDownStyle = index;
    }
    else
    {
        nType = 0;
        key.eUpStyle = index;
    }
    emit onKeypress(nType);
}
//图片
void QKeyboardASCIIGen::on_m_slectpicbtn_clicked()
{
    pLibItem=NULL;
    //QPixmapItem *PicItem = new QPixmapItem(picture,QSize(100,86));
    //pLibItem = PicItem;
    int nCheckId = RadioButton_screen_Group->checkedId();
    QPointF pos;
    if(pLibItem)
        pos = pLibItem->sceneBoundingRect().topLeft();

    if(nCheckId == 2) //从文件读取图片
    {
        QString filename=QFileDialog::getOpenFileName(this,
                                                      tr("Open File"),pwnd->picturePath,
                                                      tr("Images (*.png *.jpg *.bmp)"));
        QPixmap picture = QPixmap(filename);
        if (!picture)
        {
            return ;
        }
        //ui->m_transparantcheck->setVisible(true);

        sPath = filename;
        pwnd->picturePath=filename;
        newimage = picture;
//        pScene->clear();
//        pScene->addPixmap(newimage.scaled(100,86));
//        pScene->update();
        //newimage = this->TransparentPic(picture);//newimage

        QPixmapItem *PicItem = new QPixmapItem(newimage,QSize(100,100));

        pLibItem = PicItem;
        key.bisPic = true;
        key.sPath = sPath;
        emit addPicture(pLibItem,&newimage);
        //pLibItem->setPos(pos-pLibItem->boundingRect().topLeft());
    }
    else if(nCheckId == 1) //系统图库
    {
        //ui->m_transparantcheck->setVisible(false);
        //ui->m_lable->setVisible(false);
        //ui->m_trasparantcolorbtn->setVisible(false);

        OpenLibrary *pDlg = new OpenLibrary(this);
        if(pDlg->exec() == QDialog::Accepted)
        {
            DrawItemToScene GroupFunction;
            if(pLibItem)
            {
                delete pLibItem;
                pLibItem = NULL;
            }
            GroupFunction.CopyItem(&pLibItem,pDlg->pCopyItem);

            if(LIBRARY_LIB_GROUP == pDlg->pCopyItem->data(GROUP_TYPE_KEY).toInt())
            {
                key.bisPic = false;
            }
            else
            {
                key.bisPic = true;
            }

            QGroupItem *pBaseItem = new QGroupItem(pLibItem);
            pBaseItem->SetWidth(100);
            pBaseItem->SetHeigth(100);

            newimage = NULL;
            //isPixOrItem(pLibItem);

            key.sPath = pLibItem->data(GROUP_NAME_KEY).toString();
            emit addPicture(pLibItem,&newimage);
            sPath = ""; //清空图片地址
            //pLibItem->setPos(pos-pLibItem->boundingRect().topLeft());
        }
        pDlg->deleteLater();
        pDlg = NULL;
    }
    //PicPosChanged(RadioButton_screen_pos_Group->checkedId());
}
void QKeyboardASCIIGen::isPixOrItem(QGraphicsItem *pItem)
{
    return;
    QStringList sList = pItem->data(GROUP_DATALIST_KEY).toStringList();
    if(sList.isEmpty())
    {
        newimage = NULL;
        return;
    }
    sList = sList.at(0).split("-", QString::SkipEmptyParts);
    if(sList.isEmpty())//if(sList.size() != 3)
    {
        newimage = NULL;
        return;
    }
    int nMark = sList.at(2).toInt();//取标示
    if(nMark == 1) //表示是图片
    {
        QPixmapItem *PicItem = dynamic_cast<QPixmapItem *> (pItem);
        newimage = PicItem->getPixmap();
    }
}
void QKeyboardASCIIGen::PicPosChanged(int nCheckId)
{
    if(!pLibItem) //没有图片的时候返回
        return;
    nPicPosition = nCheckId;
    emit addPicture(pLibItem,&newimage);
}

void QKeyboardASCIIGen::onGetinfo(KeyInfo &keyInfo)
{
    keyInfo = key;
}

void QKeyboardASCIIGen::on_m_deletepicbtn_clicked()
{
    key.sPath = "";
    emit addPicture(NULL,NULL);
}

void QKeyboardASCIIGen::on_CAPSLOCK_clicked(bool checked)
{
    if(checked)
    {
        ui->ASCIIText->setHidden(true);
    }
}
