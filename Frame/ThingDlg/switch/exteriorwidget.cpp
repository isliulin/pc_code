#include "exteriorwidget.h"
#include "ui_exteriorwidget.h"
#include <QFontDatabase>
#include "Frame\MainWindow.h"
#include "color.h"
#include "view/switchitem.h"
#include "Frame/DrawDlg/OpenLibrary.h"
#include "view/mfbtnitem.h"

extern MainWindow *pwnd;

ExteriorWidget::ExteriorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExteriorWidget)
{
    ui->setupUi(this);
    ui->View->setScene(&scene);
    item = NULL;
    pCopyItem = NULL;

    initflg = false;
    defaultText.color = QColor(0,0,0);
    defaultText.showProp = false;
    defaultText.size = 10;
    defaultText.text = "";

    defaultPic.path = ":/btn/images/default.png";
    defaultPic.bLib = PIC;
    defaultPic.eFlick = NO_FLICK;
	defaultPic.color = QColor(160,160,160);
	defaultPic.nAlpha = 255;

    ui->combo_Font->addItems(QFontDatabase().families(QFontDatabase::Any));

    if(ui->combo_Font->findText(tr("Droid Sans Fallback")) == -1)
    {
        ui->combo_Font->setCurrentIndex(ui->combo_Font->findText(tr("System")));
        defaultText.sfont = tr("System");
    }
    else
    {
        ui->combo_Font->setCurrentIndex(ui->combo_Font->findText(tr("Droid Sans Fallback")));
        defaultText.sfont = tr("Droid Sans Fallback");
    }

    QVector<QString>language_vector;
    languageCount = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();

    for(int i=0; i<languageCount; i++)
    {
        language_vector.push_back(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }
    for(int i=0; i<languageCount; i++)
    {
        ui->combo_Language->addItem(language_vector.at(i));
    }
    ui->spin_Size->setValue(10);

    ui->btn_color->setStyleSheet(QString("background:%1").arg("0,0,0"));

    initflg = true;
    statusCount = 1;
    resizeStatus(1);

    UpdatePic(0);
    UpdateText(0,0);
    connect(ui->edit_text,SIGNAL(textChanged()),this,SLOT(on_textChanged()));
    connect(ui->spin_Size,SIGNAL(valueChanged(int)),this,SLOT(textSizeChange(int)));

}

ExteriorWidget::~ExteriorWidget()
{
    delete ui;
}


void ExteriorWidget::init(QItemGroup *pItem,bool bInit)
{
    item = pItem;
    if(!bInit)
    {
        if(pItem->GroupType() == SAM_DRAW_GROUP_SWITCH)
        {
            SwitchItem *switchitem = dynamic_cast<SwitchItem *> (item);
            statusCount = switchitem->mPro.count;

            statusText = switchitem->statusText;
            statusPic = switchitem->statusPic;
        }
        else
        {
            MfBtnItem *mfitem = dynamic_cast<MfBtnItem *> (item);
            statusCount = mfitem->mPro.count;
            statusText.clear();
            statusText << mfitem->statusText;
            statusPic.clear();
            statusPic << mfitem->statusPic;
        }

        int textCount = 0;
        textCount = languageCount - statusText[0].size();
        if (textCount >0)
        {
            for(int i=0; i<statusText.size();i++)
            {
                for (int j=0; j<textCount; j++)
                {
                    statusText[i] << defaultText;
                }
            }
        }

        slotStatusCountChanged(statusCount);
        on_spin_StatusIndex_valueChanged(0);
    }
//    if(item->GroupType() == SAM_DRAW_GROUP_MFBTN)
//    {
//        ui->check_Flick->setEnabled(false);
//    }
}

//监视状态数的改变
void ExteriorWidget::slotStatusCountChanged(int count)
{
    statusCount = count;
    ui->spin_StatusIndex->setValue(0);
    ui->spin_StatusIndex->setMaximum(count-1);

    resizeStatus(count);
}

//状态总数改变 更新相应的状态属性
void ExteriorWidget::resizeStatus(int count)
{
    QVector<ST_TEXT_PROP > textList;
    int size = statusText.size();
    if(size < count)
    {
        //给新增的状态增加默认值
        for(int i = size; i < count; i++)
        {
            textList.resize(0);
            for(int j = 0; j<languageCount; j++)
            {
                textList << defaultText;
                
            }
			statusPic << defaultPic;
            statusText << textList;
        }
    }
    else
    {
        for(int i = size; i > count; i--)
        {
            statusText.remove(i-1);
            statusPic.remove(i-1);
        }
    }

    if(count == 1)
    {
        ui->spin_StatusIndex->setValue(0);
        ui->spin_StatusIndex->setDisabled(true);
    }
    else
        ui->spin_StatusIndex->setDisabled(false);
}

void ExteriorWidget::on_spin_StatusIndex_valueChanged(int index)
{
    if(!initflg)
    {
        return ;
    }
    //文本属性部分的刷新
    //ui->combo_Language->setCurrentIndex(0);
    int langIndex = ui->combo_Language->currentIndex();

    UpdateText(index,langIndex);

    //图片部分的刷新
    UpdatePic(index);


}

//根据属性vector刷新图片部分UI
void ExteriorWidget::UpdatePic(int statusIndex)
{
    qDebug() << "picture path:"<<statusPic[statusIndex].path;
    ui->edit_path->setText(statusPic[statusIndex].path);
	ui->spin_Trans->setValue(statusPic[statusIndex].nAlpha);
	QColor color = statusPic[statusIndex].color;
	ui->btn_backcolor->setStyleSheet(QString("background:%1").arg(color.name()));

    if(statusPic[statusIndex].eFlick == NO_FLICK)
    {
        ui->check_Flick->setChecked(false);
        ui->combo_flick->setEnabled(false);
    }
    else
    {
        ui->check_Flick->setChecked(true);
        ui->combo_flick->setEnabled(true);
        ui->combo_flick->setCurrentIndex(statusPic[statusIndex].eFlick -1);
    }

    bool bValue = (statusPic[statusIndex].bLib == NO_PIC);

    ui->edit_path->setEnabled(!bValue);
    ui->label_color->setEnabled(bValue);
    ui->btn_backcolor->setEnabled(bValue);
    ui->label_Trans->setEnabled(bValue);
    ui->spin_Trans->setEnabled(bValue);
	
    if(LIBRARY == statusPic[statusIndex].bLib)
    {
        if(!pCopyItem)
        {
            QString path = statusPic[statusIndex].path;
            DrawItemToScene GroupFunction;
            QList <QGraphicsItem*> listItem;
            QStringList str = path.split('-');
            if(str.isEmpty())
            {
                return;
            }
            int nLoadPag = str.at(0).toInt();

            if(1 == str.at(2).toInt())
            {
                if(pwnd->vBaseLibraryScene.isEmpty())
                {
                    return;
                }
                listItem = pwnd->vBaseLibraryScene.at(nLoadPag)->TopItems();
                foreach (QGraphicsItem * pItem, listItem)
                {
                    QString sname = pItem->data(GROUP_NAME_KEY).toString();
                    if (path == sname)
                    {
                        GroupFunction.CopyItem(&pCopyItem,pItem);
                        break;
                    }
                }
            }
            else if(2 == str.at(2).toInt())
            {
                    SamDrawScene *pSvene = NULL;
                    QVector <SamDrawScene *> vScene;
                    vScene.clear();
                    QFile file("UserDefineLibraryLib.sk");
                    if(!file.open(QIODevice::ReadOnly))
                    {
                        return;
                    }
                    QDataStream openData(&file);
                    int sceneSize = 0;
                    openData >> sceneSize;
                    for(int i =0; i< sceneSize; i++)
                    {
                        pSvene = new SamDrawScene();
                        openData >> pSvene;
                        vScene.push_back(pSvene);
                    }
                    listItem = vScene.at(nLoadPag)->TopItems();
                    foreach (QGraphicsItem * pItem, listItem)
                    {
                        QString sname = pItem->data(GROUP_NAME_KEY).toString();
                        if (path == sname)
                        {
                            GroupFunction.CopyItem(&pCopyItem,pItem);
                            break;
                        }
                    }
                    file.close();
            }
            pBaseItem = new QGroupItem(pCopyItem);
            pBaseItem->SetWidth(100);
            pBaseItem->SetHeigth(100);
            QPointF pos = pCopyItem->boundingRect().topLeft();
            QPointF newpos(0,0);
            scene.clear();
            scene.addItem(pCopyItem);
            pCopyItem->setPos(newpos - pos);
            //pictureChanged();
        }
        else
        {
            QGraphicsItem *pNewItem = NULL;
            //QPointF pos = pCopyItem->sceneBoundingRect().topLeft();
            QString path = statusPic[statusIndex].path;
            DrawItemToScene GroupFunction;
            QList <QGraphicsItem*> listItem;
            QStringList str = path.split('-');
            if(str.isEmpty())
            {
                return;
            }
            int nLoadPag = str.at(0).toInt();

            if(1 == str.at(2).toInt())
            {
                if(pwnd->vBaseLibraryScene.isEmpty())
                {
                    return;
                }
                listItem = pwnd->vBaseLibraryScene.at(nLoadPag)->TopItems();
                foreach (QGraphicsItem * pItem, listItem)
                {
                    QString sname = pItem->data(GROUP_NAME_KEY).toString();
                    if (path == sname)
                    {
                        GroupFunction.CopyItem(&pNewItem,pItem);
                        break;
                    }
                }
            }
            if(!pNewItem)
            {
                return;
            }
            QPointF newpos(0,0);
            scene.clear();
            pCopyItem = pNewItem;
            pBaseItem = new QGroupItem(pCopyItem);
            pBaseItem->SetWidth(100);
            pBaseItem->SetHeigth(100);
            scene.addItem(pCopyItem);
            pCopyItem->setPos(newpos - pCopyItem->boundingRect().topLeft());
            pictureChanged();
        }
    }
    else 
    {
        QPixmap picture(statusPic[statusIndex].path);
        picture = picture.scaled(100,100);

        scene.clear();
		if (statusPic[statusIndex].bLib != NO_PIC)
		{
			scene.addPixmap(picture);
		}
        
        pictureChanged();

    }
}

//根据属性vector刷新文本部分UI
void ExteriorWidget::UpdateText(int statusIndex,int languageIndex)
{
    QString font = statusText[statusIndex][languageIndex].sfont;
    int fontIndex = ui->combo_Font->findText(font);
    if(fontIndex != -1)
    {
        ui->combo_Font->setCurrentIndex(fontIndex);
    }
    else
    {
        fontIndex = ui->combo_Font->findText("system");
        ui->combo_Font->setCurrentIndex(fontIndex);
    }

    int size = statusText[statusIndex][languageIndex].size;
   
    QColor color = statusText[statusIndex][languageIndex].color;
    

    

    int showProp = statusText[statusIndex][languageIndex].showProp;

    unsigned short alignment = (showProp >>4) & 0xff;
    

    bool underline  = (showProp & 15) >> 3;
    bool flick  = false;
    bool italic = (showProp & 3) >> 1;
    bool bold = showProp & 1;

	ui->btn_color->setStyleSheet(QString("background:%1").arg(color.name()));
    ui->btn_bold->setChecked(bold);
    ui->btn_bold->setDown(bold);

    ui->btn_Italic->setChecked(italic);
    ui->btn_Italic->setDown(italic);

    ui->btn_underline->setChecked(underline);
    ui->btn_underline->setDown(underline);
	
    //ui->check_Flick->setChecked(flick);
	ui->spin_Size->setValue(size);
	ui->edit_text->setPlainText(statusText[statusIndex][languageIndex].text);
	if(alignment <= ui->combo_Alignment->count())
	{
		ui->combo_Alignment->setCurrentIndex(alignment);
	}


	if (item)
	{
		item->SetBold(bold);
		item->SetUnderLine(underline);
        item->SetFontSize(size);
		item->SetItalic(italic);
		item->SetTextColor(color);
	}
}

//语言combox值改变
void ExteriorWidget::on_combo_Language_currentIndexChanged(int index)
{
    if(!initflg)
    {
        return ;
    }

    int statusIndex = ui->spin_StatusIndex->value();
    UpdateText(statusIndex,index);
}

//字体combox值改变
void ExteriorWidget::on_combo_Font_currentIndexChanged(QString string)
{
    int statusIndex = ui->spin_StatusIndex->value();
    int languageIndex = ui->combo_Language->currentIndex();

    if(languageIndex != -1)
        statusText[statusIndex][languageIndex].sfont = string;
    if(item)
        item->SetFontName(string);
}

//对齐combox值改变
void ExteriorWidget::on_combo_Alignment_currentIndexChanged(int index)
{
    ShowPropChanged();
    int align = 5;
    switch(index)
    {
    case 0: align = 5;
        break;
    case 1: align = 4;
        break;
    case 2: align = 6;
        break;
    }
    if(item)
        item->SetTextAlign(align);
}

//文本显示属性的更改，刷新UI
void ExteriorWidget::ShowPropChanged()
{
    int statusIndex = ui->spin_StatusIndex->value();
    int languageIndex = ui->combo_Language->currentIndex();

    int nAligment = ui->combo_Alignment->currentIndex();
    bool bold = ui->btn_bold->isChecked();
    bool italic = ui->btn_Italic->isChecked();
    bool underline = ui->btn_underline->isChecked();
    bool flick = false;

    int showProp = (nAligment << 4)+(underline << 3)+(flick << 2)+(italic << 1)+(bold);
    qDebug() << "showProp  "<<showProp ;
    statusText[statusIndex][languageIndex].showProp = showProp;
}

//颜色选择按钮的点击
void ExteriorWidget::on_btn_color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->btn_color,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setTextColor(const QColor &)));
}

//设置文本色
void ExteriorWidget::setTextColor(const QColor &color)
{
    ui->btn_color->setStyleSheet(QString("background:%1").arg(color.name()));

    int statusIndex = ui->spin_StatusIndex->value();
    int languageIndex = ui->combo_Language->currentIndex();
    statusText[statusIndex][languageIndex].color = color;
    ShowPropChanged();
    if(item)
        item->SetTextColor(color);
}

void ExteriorWidget::on_btn_bold_clicked(bool checked)
{
    ui->btn_bold->setChecked(checked);
    ui->btn_bold->setDown(checked);
    ShowPropChanged();
    if(item)
        item->SetBold(checked);
}

void ExteriorWidget::on_btn_Italic_clicked(bool checked)
{
    ui->btn_Italic->setChecked(checked);
    ui->btn_Italic->setDown(checked);
    ShowPropChanged();
    if(item)
        item->SetItalic(checked);
}

void ExteriorWidget::on_btn_underline_clicked(bool checked)
{
    ui->btn_underline->setChecked(checked);
    ui->btn_underline->setDown(checked);
    ShowPropChanged();
    if(item)
        item->SetUnderLine(checked);
}

void ExteriorWidget::on_check_Flick_clicked(bool checked)
{
    ui->check_Flick->setChecked(checked);
    ui->combo_flick->setEnabled(checked);
    int statusIndex = ui->spin_StatusIndex->value();

    if(checked)
    {
        ui->combo_flick->setCurrentIndex(0);
        int index = ui->combo_flick->currentIndex();
        statusPic[statusIndex].eFlick = (FLICK_TYPE)(index+1);
    }
    else
    {
         statusPic[statusIndex].eFlick = NO_FLICK;
    }
}

//文本改变的响应
void ExteriorWidget::on_textChanged()
{
    int statusIndex = ui->spin_StatusIndex->value();
    int languageIndex = ui->combo_Language->currentIndex();

    QString text = ui->edit_text->toPlainText();
    statusText[statusIndex][languageIndex].text = text;

    if(item)
        item->SetText(text);
}

//图片改变的处理函数
void ExteriorWidget::pictureChanged()
{
    int statusIndex = ui->spin_StatusIndex->value();
    int languageIndex = ui->combo_Language->currentIndex();


    EITEM_TYPE blib = statusPic[statusIndex].bLib;
    QString path = statusPic[statusIndex].path;
	int alpha = statusPic[statusIndex].nAlpha;
	QColor color = statusPic[statusIndex].color;

    if(item) {
        item->SetPicture(path,blib,alpha,color);
    }
}

//选择外部图片
void ExteriorWidget::on_btn_picture_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,
            tr("Open File"),pwnd->picturePath,
            tr("Images (*.png *.jpg *.bmp)"));
    QPixmap picture = QPixmap(filename);
    if(!picture.isNull())
    {
        int index = ui->spin_StatusIndex->value();
        statusPic[index].bLib = PIC;
        statusPic[index].path = filename;
        UpdatePic(index);
        pwnd->picturePath = filename;
    }
}

//从0状态复制图片属性
void ExteriorWidget::on_btn_copyPic_clicked()
{
    int statusIndex = ui->spin_StatusIndex->value();
    statusPic[statusIndex] = statusPic.first();
    //slotStatusCountChanged(statusCount);
    on_spin_StatusIndex_valueChanged(statusIndex);
}

//从0状态复制文本属性
void ExteriorWidget::on_btn_copyText_clicked()
{
    int statusIndex = ui->spin_StatusIndex->value();
    int languageIndex = ui->combo_Language->currentIndex();

    statusText[statusIndex][languageIndex] = statusText[0][languageIndex];
    UpdateText(statusIndex,languageIndex);
}

bool ExteriorWidget::Save()
{
    return true;
}

void ExteriorWidget::textSizeChange(int size)
{
    int statusIndex = ui->spin_StatusIndex->value();
    int languageIndex = ui->combo_Language->currentIndex();
    statusText[statusIndex][languageIndex].size = size;
    ShowPropChanged();
    if(item)
        item->SetFontSize(size);
}
//从图库选择图片
void ExteriorWidget::on_btn_lib_clicked()
{
    int index = ui->spin_StatusIndex->value();
    DrawItemToScene GroupFunction;
    OpenLibrary *pDlg = new OpenLibrary(this);
    if(pDlg->exec() == QDialog::Accepted)
    {
        if(pDlg->pCopyItem)
        {
            GroupFunction.CopyItem(&pCopyItem,pDlg->pCopyItem);
        }
        else
        {
            return;
        }
        if(LIBRARY_LIB_GROUP == pDlg->pCopyItem->data(GROUP_TYPE_KEY).toInt())
        {
            statusPic[index].bLib = LIBRARY;
        }
        else
        {
            statusPic[index].bLib = USERDEFINE;
        }
        pBaseItem = new QGroupItem(pCopyItem);
        pBaseItem->SetWidth(100);
        pBaseItem->SetHeigth(100);
        if(index > statusPic.size() || index < 0)
        {
            return;
        }
        statusPic[index].path = pCopyItem->data(GROUP_NAME_KEY).toString();
        pDlg->deleteLater();
        pDlg = NULL;
    }
    else
    {
        pDlg->deleteLater();
        pDlg = NULL;
        return;
    }
    qDebug()<<"UpdatePic start..";
    UpdatePic(index);
}

//从第一种语言复制
void ExteriorWidget::on_btn_copyText_2_clicked()
{
    int statusIndex = ui->spin_StatusIndex->value();
    int languageIndex = ui->combo_Language->currentIndex();

    statusText[statusIndex][languageIndex] = statusText[statusIndex][0];
    UpdateText(statusIndex,languageIndex);
}

int ExteriorWidget::currentState()
{
	int curState = 0;
	curState = ui->spin_StatusIndex->value();
	if (curState >statusText.size() || curState <0)
	{
		curState = 0;
	}
	return curState;
}

void ExteriorWidget::on_combo_flick_currentIndexChanged(int index)
{
    bool checked = ui->check_Flick->isChecked();

    int statusIndex = ui->spin_StatusIndex->value();

    if(checked)
    {
        statusPic[statusIndex].eFlick = (FLICK_TYPE)(index+1);
    }
    else
    {
         statusPic[statusIndex].eFlick = NO_FLICK;
    }
}

//不使用图片
void ExteriorWidget::on_btn_no_clicked()
{

    int statusIndex = ui->spin_StatusIndex->value();

    statusPic[statusIndex].bLib = NO_PIC;

    UpdatePic(statusIndex);
}

void ExteriorWidget::on_btn_backcolor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->btn_backcolor,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setBackColor(const QColor &)));
}

//设置背景色
void ExteriorWidget::setBackColor(const QColor &color)
{
    ui->btn_backcolor->setStyleSheet(QString("background:%1").arg(color.name()));

	
    int statusIndex = ui->spin_StatusIndex->value();
	statusPic[statusIndex].color = color;
	if (statusPic[statusIndex].bLib == NO_PIC)
	{
		UpdatePic(statusIndex);
	}
	

}

void ExteriorWidget::on_spin_Trans_valueChanged(int alpha)
{
	int statusIndex = ui->spin_StatusIndex->value();
	statusPic[statusIndex].nAlpha = alpha;
	if (statusPic[statusIndex].bLib == NO_PIC)
	{
		UpdatePic(statusIndex);
	}
}

//设置为指示灯，给状态添加默认属性
void ExteriorWidget::slotBitLamp()
{
	statusCount = 2;
	statusText.clear();
	statusPic.clear();
	QVector<ST_TEXT_PROP > textList;
	ST_TEXT_PROP textOn = defaultText;
	ST_TEXT_PROP textOff = defaultText;
	textOn.text = "ON";
	textOff.text = "OFF";

	 ST_PIC_PROP picOn = defaultPic;
	 ST_PIC_PROP picOff= defaultPic;
     picOn.path = ":/btn/images/default.png";
     picOff.path = ":/btn/images/gray.png";
//off状态TEXT
	for(int i=0; i<2;i++)
	{
		textList.clear();
		for(int j = 0; j<languageCount; j++)
		{
			if (i == 0)
			{
				textList << textOff;
			}
			else
			{
				textList << textOn;
			}
		}
		statusText << textList;
		if (i == 0)
		{
			statusPic << picOff;
		}
		else
		{
			statusPic << picOn;
		}
		
	}
	
	
	ui->spin_StatusIndex->setValue(0);
	ui->spin_StatusIndex->setMaximum(1);
	resizeStatus(2);
    on_spin_StatusIndex_valueChanged(0);
}
