#include "SaveToLibrary.h"
#include "ui_SaveToLibrary.h"
#include "Frame/DrawDlg/SaveUserDefineLib.h"
#include <QBitmap>
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
int g_LibSelectType = 1; //

SaveToLibrary::SaveToLibrary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveToLibrary)
{
    ui->setupUi(this);
    pwnd->SaveItemToLibList.clear();
    this->setWindowTitle(tr("����ͼ��"));
    ui->MainView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    QRect rc = ui->MainView->geometry();
    ui->MainView->setSceneRect(0,0,1000,1000);
    pScene = new SamDrawScene(this);
   // pScene->setSceneRect(0,0,rc.width()-3,rc.height()-3);
    ui->MainView->setScene(pScene);

    Radio_Group = new QButtonGroup(this);
    Radio_Group->addButton(ui->m_radio1,1);
    Radio_Group->addButton(ui->m_radio2,2);
    Radio_Group->addButton(ui->m_radio3,3);
    connect(Radio_Group,SIGNAL(buttonClicked(int)),this,SLOT(selectFunction(int)));

    ui->m_lable->setVisible(false);
    ui->m_color->setVisible(false);
    ui->m_transparentcheck->setVisible(false);
    ui->m_color->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
    pPix = NULL;
}

SaveToLibrary::~SaveToLibrary()
{
    delete ui;
}

void SaveToLibrary::selectFunction(int nCheckId)
{
    QList<QGraphicsItem *> Items;
    QGraphicsItem *pItem = NULL;
    DrawItemToScene FunClass;
    int nIndex = pwnd->nActiveSheetIndex; //��ǰ�������
    Items.clear();
    QMessageBox box(this);
    QString filename = "";
    pScene->clear();

    g_LibSelectType = nCheckId;

    switch(nCheckId)
    {
    case 1: //��ѡ��ͼ����Ϊͼ��
        ui->m_lable->setVisible(false);
        ui->m_color->setVisible(false);
        ui->m_transparentcheck->setVisible(false);
        Items = pwnd->pSceneSheet[nIndex]->selectedItems();
        if(Items.size() == 0)
        {
            box.setText(tr("��ǰ����û��ѡ��ͼ��!"));
            box.exec();
            return;
        }
        foreach(QGraphicsItem *item,Items)
        {
            FunClass.CopyItem(&pItem,item);
            pItem->setFlag(QGraphicsItem::ItemIsMovable, false);
            pScene->addItem(pItem);
        }
        break;
    case 2: //���ļ�����ͼ����Ϊͼ��
        {
            filename=QFileDialog::getOpenFileName(this,
                                  tr("Open File"),"/home",
                                  tr("Images (*.png *.jpg *.bmp)"));
            pPix = QPixmap(filename);//QPixmap picture
            if (!pPix)
            {
                return ;
            }
            ui->m_transparentcheck->setVisible(true);

            QPixmap picture = pPix.scaled(QSize(100,100));
            pScene->clear();
            on_m_transparentcheck_clicked(ui->m_transparentcheck->isChecked());

            QPixmapItem *PicItem = new QPixmapItem(pPix,picture.size());
            qDebug()<<"SaveToLibrary::selectFunction"<<pPix.size();
            //pItem = PicItem;
            pScene->addItem(PicItem);
        }
        break;
    case 3: //���ⲿ����ͼ��
        {
            filename = QFileDialog::getOpenFileName(this,tr("open file"),tr("c:\\"),tr("*.sk"));
            if(filename.isEmpty())
                return;
            QFile file(filename);
            if(!file.open(QIODevice::ReadOnly))
                return ;
            QDataStream openData(&file);
            int sceneSize = 0;
            openData >> sceneSize;
            for(int i =0; i< sceneSize; i++)
            {
                openData >> pScene;
            }
            file.close();
        }
        break;
    }
}

void SaveToLibrary::on_m_SaveTo_clicked() //���浽
{
    QList<QGraphicsItem *> Items;
    QMessageBox box(this);
    Items = pScene->items();
    if(Items.size() < 1) //û��ͼ��
    {
        box.setText(tr("��ѡ����Ҫ�����ͼ��!"));
        box.exec();
        return;
    }

    if(Radio_Group->checkedId() != 1 && Radio_Group->checkedId() != 2 && Radio_Group->checkedId() != 3)//û��ѡ����ѡ��
    {
        box.setText(tr("��ѡ������һ���!"));
        box.exec();
        return;
    }

    QGraphicsItem *pItem = NULL;
    if(Radio_Group->checkedId() == 1)//����������ѡ��ͼ��
    {
        DrawItemToScene FunClass;
        int nIndex = pwnd->nActiveSheetIndex; //��ǰ�������
        Items = pwnd->pSceneSheet[nIndex]->selectedItems();
        if(Items.size() == 1)
        {
            if(Items.at(0)->childItems().size() == 0) //is base item
            {
                box.setText(tr("The base item can not add to the library!"));
                box.exec();
                return;
            }
        }
        foreach(QGraphicsItem *item,Items)
        {
            FunClass.CopyItem(&pItem,item);
            pwnd->SaveItemToLibList.append(pItem);
        }
    }
    else if(Radio_Group->checkedId() == 2)//���ļ��е���ͼƬ
    {
        QPixmapItem *PicItem = new QPixmapItem(pPix,QSize(100,100)); //pPix.size()
        pItem = PicItem;
        pwnd->SaveItemToLibList.append(pItem);
    }
    else if(Radio_Group->checkedId() == 3)//���ⲿ����ͼƬ
    {
        DrawItemToScene FunClass;
        selectAll(pScene);//ȫѡ
        Items = pScene->selectedItems();

        QGraphicsItem * pTem_leftMin = NULL;
        QGraphicsItem * pTem_origin = NULL;
        qreal nleftPos;
        if (Items.size() != 0)
        {
            for(int i=0;i<Items.size();i++)//ѡ��������xֵ�����ŵ���
            {
                nleftPos=Items.at(i)->zValue();
                for(int j=i+1;j<Items.size();j++)
                {
                    if(Items.at(j)->zValue()<=nleftPos)
                    {
                        nleftPos=Items.at(j)->zValue();
                        pTem_leftMin=Items.at(j);
                        pTem_origin=Items.at(i);
                        Items.replace(i,pTem_leftMin);
                        Items.replace(j,pTem_origin);
                    }
                }
            }
        }

        foreach(QGraphicsItem *item,Items)
        {
            FunClass.CopyItem(&pItem,item);
            pwnd->SaveItemToLibList.append(pItem);
        }
        reverseSelect(pScene);//���ѡ��
    }

    SaveUserDefineLib *pDlg =  new SaveUserDefineLib(this);
    if(pDlg->exec() == QDialog::close())
    {      
        QDialog::close();
    }
    pDlg->deleteLater();
    pDlg = NULL;
}

void SaveToLibrary::on_m_Cancel_clicked() //ȡ��
{
    QDialog::close();
}

void SaveToLibrary::on_m_transparentcheck_clicked(bool checked)//�Ƿ�͸��
{
    if(checked)
    {
        ui->m_lable->setVisible(true);
        ui->m_color->setVisible(true);
        if(!pPix)
            return;
        else
        {
            QColor mColor = ui->m_color->palette().background().color();
            QBitmap bmp=pPix.createMaskFromColor(mColor,Qt::MaskInColor);
            pPix.setMask(bmp); //���ô�����mask
        }
    }
    else
    {
        ui->m_lable->setVisible(false);
        ui->m_color->setVisible(false);
    }    
}

void SaveToLibrary::on_m_color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_color,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setColor(const QColor &)));

}
void SaveToLibrary::setColor(const QColor & currentColor)
{
    ui->m_color->setStyleSheet(QString("background:%1").arg(currentColor.name()));
    if(!pPix)
        return;
    else
    {
        QColor mColor = ui->m_color->palette().background().color();
        QBitmap bmp=pPix.createMaskFromColor(mColor,Qt::MaskInColor);
        pPix.setMask(bmp); //���ô�����mask
    }
}

void SaveToLibrary::on_HelpButton_clicked()
{
    pwnd->loadHelpHtm(TOOLBAR_SAVELIBRARY);
}


void SaveToLibrary::selectAll(SamDrawScene *pScene)
{
    QList <QGraphicsItem *> selList;
    selList=pScene->items();
    QPainterPath path;
    path.addRect(0,0,pScene->width(),pScene->height());
    pScene->setSelectionArea(path);
    selList=pScene->selectedItems();
    foreach(QGraphicsItem *item,selList)
        item->setSelected(true);
}

void SaveToLibrary::reverseSelect(SamDrawScene *pScene)
{
    QPainterPath path;
    QList<QGraphicsItem *> item_list=pScene->selectedItems();
    for(int i=0;i<item_list.size();i++)
    {
        item_list.at(i)->setFlag(QGraphicsItem::ItemIsSelectable,false);
    }
    path.addRect(0,0,pScene->width(),pScene->height());
    pScene->setSelectionArea(path);
    for(int i=0;i<item_list.size();i++)
    {
        item_list.at(i)->setFlag(QGraphicsItem::ItemIsSelectable,true);
    }
}
