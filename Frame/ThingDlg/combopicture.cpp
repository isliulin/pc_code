#include "combopicture.h"
#include "ui_combopicture.h"
#include "view/qdropdownattr.h"
#include "Frame/DrawDlg/OpenLibrary.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

typedef QPair<QString,QString> Pair;
ComboPicture::ComboPicture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ComboPicture)
{
    ui->setupUi(this);

    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    ui->m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->m_tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一行拉伸
    mpaths.clear();
    pScene = new QGraphicsScene();
    ui->graphicsView->setScene(pScene);
    connect(ui->m_tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(on_cellChanged()));
}

ComboPicture::~ComboPicture()
{
    delete ui;
}

void ComboPicture::on_m_SelectLibpushBtn_clicked()
{    
    int index = ui->m_tableWidget->currentRow();
    if(index < 0)
    {
        return ;
    }

    QString sname;
    OpenLibrary *pDlg = new OpenLibrary(this);
    EITEM_TYPE libtype = NO_PIC;
    if(pDlg->exec() == QDialog::Accepted)
    {
        QGraphicsItem *pCopyItem = NULL;
        DrawItemToScene GroupFunction;
        GroupFunction.CopyItem(&pCopyItem,pDlg->pCopyItem);
        int type = pCopyItem->data(GROUP_TYPE_KEY).toInt();
        if(LIBRARY_LIB_GROUP == type)
        {
            sname = pCopyItem->data(GROUP_NAME_KEY).toString();
            QStringList strName = sname.split('-');
            int nCurrentIndex = ui->m_tableWidget->currentRow();
            int nKey = strName.at(2).toInt();

            if(LIBRARY == nKey)
            {
               libtype = LIBRARY;
            }
            else
            {
                libtype = USERDEFINE;
            }

            QTableWidgetItem * tabitem = ui->m_tableWidget->item(index,1);
            if(tabitem)
            {
                tabitem->setText("elment"+strName.at(1));
            }

            QString path = pCopyItem->data(GROUP_NAME_KEY).toString();

            QPointF pos = pCopyItem->boundingRect().topLeft();
            QPointF newpos(0,0);
            pScene->clear();
            pScene->addItem(pCopyItem);
            pCopyItem->setPos(newpos - pos);

            emit picChanged(index,libtype,path);


        }
        else if(LIBRARY_PIXMAP_GROUP == type)
        {

            QString path = pCopyItem->data(GROUP_NAME_KEY).toString();
            QPixmap picture = QPixmap(path);
            if (!picture)
            {
               return ;
            }

            sname = GetPicName(path);
            libtype = USERDEFINE;
            QTableWidgetItem * tabitem = ui->m_tableWidget->item(index,1);
            if(tabitem)
            {
                tabitem->setText(sname);
            }

            pScene->clear();
            pScene->addPixmap(picture.scaled(120,120)); //newimage
            pScene->update();

            emit picChanged(index,libtype,path);

        }
    }
    pDlg->deleteLater();
    pDlg = NULL;

}

void ComboPicture::on_m_deletepicbtn_clicked()
{
    int index = ui->m_tableWidget->currentRow();
    if(index < 0)
    {
        return ;
    }
    QTableWidgetItem * tabitem = ui->m_tableWidget->item(index,1);
    if(tabitem)
    {
        tabitem->setText("");
    }
    if(pScene)
    {
        pScene->clear();
    }
    emit picChanged(index,NO_PIC,"");
}

void ComboPicture::on_m_SelectPicpushBtn_clicked()
{
    int index = ui->m_tableWidget->currentRow();
    if(index < 0)
    {
        return ;
    }
    QString filename=QFileDialog::getOpenFileName(this,
            tr("Open File"),pwnd->picturePath,
            tr("Images (*.png *.jpg *.bmp)"));
    QPixmap picture = QPixmap(filename);
    if(!picture.isNull())
    {
        QTableWidgetItem * tabitem = ui->m_tableWidget->item(index,1);
        if(tabitem)
        {
            tabitem->setText(filename);
        }
        emit picChanged(index,PIC,filename);

        pScene->clear();
        pScene->addPixmap(picture.scaled(120,120));

        pwnd->picturePath = filename;
    }
}
void ComboPicture::on_Add(QString funcName,QString path)//功能增加
{
    mpaths.append(Pair(funcName,path));
    refreshTab(mpaths.size());
}
void ComboPicture::refreshTab(int index)//刷新列表
{
    int size = mpaths.size();
    ui->m_tableWidget->setRowCount(size);
    ui->m_tableWidget->verticalHeader()->setVisible(false);

    for(int i = 0; i< size; i++)
    {
        QString str = QString("%1").arg(i);
        ui->m_tableWidget->setItem(i,0,new QTableWidgetItem(mpaths[i].first));
        ui->m_tableWidget->setItem(i,1,new QTableWidgetItem(mpaths[i].second));
    }
    if(ui->m_tableWidget->currentRow() < 0)
    {
        ui->m_tableWidget->setCurrentCell(0,0);
    }
}

void ComboPicture::on_cellChanged()
{
    int row = ui->m_tableWidget->currentRow();
    if(row < 0)
    {
        row = 0;
    }
    emit rowChanged(row);
}

void ComboPicture::showRowPic(EITEM_TYPE libtype,QString path)
{
    if(LIBRARY == libtype || USERDEFINE == libtype)
    {
        if("" != path)
        {
            pScene->clear();
            QGraphicsItem *pCopyItem = onGetItemFromFile(path,libtype);
            if(!pCopyItem)
            {
                return;
            }
            else
            {
                QPointF newpos = pCopyItem->boundingRect().topLeft();
                pScene->addItem(pCopyItem);
                QGroupItem *pBaseItem = new QGroupItem(pCopyItem);
                pBaseItem->SetWidth(120);
                pBaseItem->SetHeigth(120);
                pCopyItem->setPos(QPointF(0,0) - newpos);
                //ui->m_SysImageradioBtn->setChecked(true);
            }
        }
    }
    else
    {
        pScene->clear();
        QPixmap picture = QPixmap(path);
        pScene->addPixmap(picture.scaled(QSize(120,120)));
    }
}
void ComboPicture::on_Delete(QString funcName,QString path)//删除功能
{
    mpaths.pop_back();
    refreshTab(mpaths.size());
}
void ComboPicture::Init(QVector<SwitchInfo> m_vecSwitchItem)
{
    //if(item && item->m_bUsePic)
    {
        //初始化图片列表
        mpaths.clear();
        for(int i= 0;i < m_vecSwitchItem.size();i++)
        {
            qDebug() <<"m_vecSwitchItem __path:"<< m_vecSwitchItem[i].sPath;

            QString sPath = m_vecSwitchItem[i].sPath;
            if(m_vecSwitchItem[i].bLib == LIBRARY)
            {
                QStringList strName = m_vecSwitchItem[i].sPath.split('-');

                if(strName.size()>1)
                {
                    sPath = QString("elment"+strName.at(1));
                }

            }
            else if(m_vecSwitchItem[i].bLib == USERDEFINE)
            {
                QString sName = m_vecSwitchItem[i].sPath;
                sPath = GetPicName(sName);
            }
            else
            {
                sPath = m_vecSwitchItem[i].sPath;
            }

            mpaths.append(Pair(m_vecSwitchItem[i].vecSwitchFunName.first()
                               ,sPath));
            refreshTab(0);
        }
    }
}
QString ComboPicture::GetPicName(QString sPath)
{
    QString sName = "";
    QStringList sList = sPath.split("/", QString::SkipEmptyParts);
    sName = sList.at(sList.size()-1);
    return sName;
}
QGraphicsItem *ComboPicture::onGetItemFromFile(QString sPath,EITEM_TYPE eType)
{
    QList <QGraphicsItem*> listItem;
    QStringList str = sPath.split('-');
    if(str.isEmpty())
    {
        return NULL;
    }
    QGraphicsItem *pNewItem = NULL;
    int nLoadPag = str.at(0).toInt();

    if(LIBRARY == eType)
    {
        if(pwnd->vBaseLibraryScene.isEmpty())
        {
            return NULL;
        }
        listItem = pwnd->vBaseLibraryScene.at(nLoadPag)->TopItems();
        foreach (QGraphicsItem * pItem, listItem)
        {
            QString sname = pItem->data(GROUP_NAME_KEY).toString();
            if (sPath == sname)
            {
                DrawItemToScene GroupFunction;
                GroupFunction.CopyItem(&pNewItem,pItem);
                break;
            }
        }
    }
    else if(USERDEFINE == eType)
    {
        QString path = sPath;
        QPixmap picture = QPixmap(path);
        if (!picture)
        {
           return NULL;
        }
        pNewItem = new QPixmapItem(picture,QSize(100,86));

    }
    return pNewItem;
}
