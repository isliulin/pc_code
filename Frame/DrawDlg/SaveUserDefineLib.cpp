#include "SaveUserDefineLib.h"
#include "ui_SaveUserDefineLib.h"
#include <QFile>

#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
extern int g_LibSelectType;

SaveUserDefineLib::SaveUserDefineLib(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveUserDefineLib)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("���浽�Զ���ͼ��"));
    ui->treeWidget->expandAll();
    ui->MainView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    QRect rc = ui->MainView->geometry();
    ui->MainView->setSceneRect(0,0,rc.width()-3,rc.height()-3);
    loadUserDefineLib("UserDefineLibraryLib.sk");//�����û��Զ���ͼ��
    sPath.clear();
}

SaveUserDefineLib::~SaveUserDefineLib()
{
    for(int i = 0;i < vUserScene.size();i++)
        delete vUserScene[i];
    vUserScene.clear();

    delete ui;
}

void SaveUserDefineLib::loadUserDefineLib(QString sPath)
{
    QFile file(sPath);
    if(!file.open(QIODevice::ReadOnly))
        return ;
    QDataStream openData(&file);
    SamDrawScene *pSvene = NULL;
    vUserScene.clear();
    int sceneSize = 0;
    openData >> sceneSize;
    vUserScene.clear();

    QRect rc = ui->MainView->geometry();
    for(int i =0; i< sceneSize; i++)
    {
        pSvene = new SamDrawScene();
        openData >> pSvene;
        pSvene->setSceneRect(0,0,rc.width()-3,rc.height()-3);
        vUserScene.push_back(pSvene);
        nActiveIndex = i;
        lockCurrentSheetItem();
      //  connect(pSvene,SIGNAL(SingleClickItem()),this,SLOT(onSelectSingleItem()));
    }
    file.close();
    if(ui->MainView && !vUserScene.isEmpty())
    {
        ui->MainView->setScene(vUserScene.first());
    }
    nActiveIndex = 0;
}

void SaveUserDefineLib::lockCurrentSheetItem()
{
    QPainterPath path;
    QList<QGraphicsItem *> item_list;
    item_list.clear();

    path.addRect(0,0,vUserScene.at(nActiveIndex)->width(),vUserScene.at(nActiveIndex)->height());
    vUserScene.at(nActiveIndex)->setSelectionArea(path);
    item_list=vUserScene.at(nActiveIndex)->selectedItems();

    if(!item_list.isEmpty())
    {
        QItemGroup *pItemGroup = NULL;
        foreach (QGraphicsItem *item, item_list)
        {
            item->setFlag(QGraphicsItem::ItemIsMovable, false);
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item->setSelected(false);
            pItemGroup = dynamic_cast<QItemGroup *> (item);
            if(pItemGroup)
                pItemGroup->setResizableOff();
        }
    }
}

void SaveUserDefineLib::on_treeWidget_itemClicked(QTreeWidgetItem* item, int column)
{
    QString str = "";
    str = item->text(column);
    QMessageBox box(this);

    if(vUserScene.isEmpty())
    {
        box.setText(tr("Lack of UserDefineLibraryLib.sk file!"));
        box.exec();
        return;
    }

    if(str == tr("ͼ��һ"))
    {
        ui->MainView->setScene(vUserScene.at(0));
        nActiveIndex = 0;
    }
    else if(str == tr("ͼ���"))
    {
        ui->MainView->setScene(vUserScene.at(1));
        nActiveIndex = 1;
    }

    else if(str == tr("ͼ����"))
    {
        ui->MainView->setScene(vUserScene.at(2));
        nActiveIndex = 2;
    }
    else if(str == tr("ͼ����"))
    {
        ui->MainView->setScene(vUserScene.at(3));
        nActiveIndex = 3;
    }
    else if(str == tr("ͼ����"))
    {
        ui->MainView->setScene(vUserScene.at(4));
        nActiveIndex = 4;
    }
    else if(str == tr("ͼ����"))
    {
        ui->MainView->setScene(vUserScene.at(5));
        nActiveIndex = 5;
    }
    else if(str == tr("ͼ����"))
    {
        ui->MainView->setScene(vUserScene.at(6));
        nActiveIndex = 6;
    }
    else if(str == tr("ͼ���"))
    {
        ui->MainView->setScene(vUserScene.at(7));
        nActiveIndex = 7;
    }
    else if(str == tr("ͼ���"))
    {
        ui->MainView->setScene(vUserScene.at(8));
        nActiveIndex = 8;
    }
    else if(str == tr("ͼ��ʮ"))
    {
        ui->MainView->setScene(vUserScene.at(9));
        nActiveIndex = 9;
    }
    else if(str == tr("ͼ��ʮһ"))
    {
        ui->MainView->setScene(vUserScene.at(10));
        nActiveIndex = 10;
    }
    else if(str == tr("ͼ��ʮ��"))
    {
        ui->MainView->setScene(vUserScene.at(11));
        nActiveIndex = 11;
    }
    else if(str == tr("ͼ��ʮ��"))
    {
        ui->MainView->setScene(vUserScene.at(12));
        nActiveIndex = 12;
    }
    else if(str == tr("ͼ��ʮ��"))
    {
        ui->MainView->setScene(vUserScene.at(13));
        nActiveIndex = 13;
    }
    else if(str == tr("ͼ��ʮ��"))
    {
        ui->MainView->setScene(vUserScene.at(14));
        nActiveIndex = 14;
    }
}

void SaveUserDefineLib::on_m_DeleteItem_clicked()//ɾ������
{
    QList <QGraphicsItem *> sList;
    QPointF deletepos;
    QRectF rect;
    sList = vUserScene.at(nActiveIndex)->selectedItems();
    if (sList.isEmpty())
        return;

    foreach(QGraphicsItem *pItem,sList)
    {
        rect = pItem->boundingRect();
        deletepos = pItem->boundingRect().topLeft()+pItem->scenePos();//��¼ɾ����λ��
        vUserScene.at(nActiveIndex)->removeItem(pItem);
    }

    //��������������item��λ��
    QPainterPath path;
    QPointF pos;
    int nItemCount = 0;
    int nSpace = rect.width()+10;

    QGraphicsItem *item = NULL;
    double width = vUserScene.at(nActiveIndex)->width(); //�����Ŀ��
    double heigth = vUserScene.at(nActiveIndex)->height();//�����ĸ���
    path.addRect(0,0,width,heigth);
    vUserScene.at(nActiveIndex)->setSelectionArea(path);
    QList<QGraphicsItem *> item_list=vUserScene.at(nActiveIndex)->selectedItems();
    nItemCount = item_list.size();
    for(int i = 0;i < nItemCount;i++)
    {
        item = item_list.at(i);
        item->setSelected(false);
        pos = item->boundingRect().topLeft()+item->scenePos();
        if(pos.x() > deletepos.x() && pos.y() >= deletepos.y()) //ͬ�д���
        {
            pos.setX(pos.x()-nSpace);//-110
        }
        else if(pos.x() ==0 && pos.y() > deletepos.y()) //��ͬ�д���
        {
            pos.setX(440);
            pos.setY((pos.y()/nSpace-1)*nSpace);
        }
        else if(pos.y() > deletepos.y())
            pos.setX(pos.x()-nSpace);
        item->setPos(pos- item->boundingRect().topLeft());
    }
    //���н���
    SaveDefineLib("UserDefineLibraryLib.sk"); //���±����Զ���ͼ��
}

void SaveUserDefineLib::on_m_SaveItem_clicked() //����
{
    QMessageBox box(this);
    if(pwnd->SaveItemToLibList.isEmpty())
    {
        box.setText(tr("û��ѡ��ͼ��!"));
        box.exec();
        return;
    }


    QPainterPath path;
    QGraphicsItem *item = NULL;
    QGraphicsItem *pPastitem = NULL;
    QRectF itemrect;
    QStringList sStrList;

    int i = 0;
    double top = 0;
    QPointF maxpos;
    QPointF pos;
    double space = 10;//ͼ��֮��ļ��
    int nItemCount = 0; //item����
    int nTotalItem = 0;
    double width = vUserScene.at(nActiveIndex)->width(); //�����Ŀ��
    double heigth = vUserScene.at(nActiveIndex)->height();//�����ĸ���
    DrawItemToScene GroupFunction;
    maxpos.setX(0);
    maxpos.setY(0);
    itemrect.setSize(QSizeF(100,100));
    itemrect.setTopLeft(QPointF(0,0));

    path.addRect(0,0,width,heigth);
    vUserScene.at(nActiveIndex)->setSelectionArea(path);
    QList<QGraphicsItem *> item_list=vUserScene.at(nActiveIndex)->selectedItems();

    nItemCount = item_list.size();
    nTotalItem = vUserScene.at(nActiveIndex)->TopItems().size();
    sPath.clear();
    sStrList.clear();

    if(g_LibSelectType == 3) //ѡ����Ǵ��ⲿ�ļ�����ͼ�����
    {
        if( nItemCount > 0 )
        {
            box.setText(tr("��ѡ��һ���յ�ͼ�����洢!"));
            box.exec();
            return;
        }
        for(i=0;i < pwnd->SaveItemToLibList.size();i++)
        {
            maxpos = getMaxPoint();
            item = pwnd->SaveItemToLibList.at(i);//CreateGroupItem();
            GroupFunction.CopyItem(&pPastitem,item);

            SetItemPath(pPastitem); //����·��
            vUserScene.at(nActiveIndex)->clearSelection();
            vUserScene.at(nActiveIndex)->addItem(pPastitem);

            QItemGroup *pItemGroup = NULL;
            pItemGroup = dynamic_cast<QItemGroup *> (pPastitem);
            if(pItemGroup)
                pItemGroup->setResizableOff();

            pPastitem->setData(GROUP_TYPE_KEY,QVariant(LIBRARY_LIB_GROUP)); //����ͼ���Keyֵ
            pPastitem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            pPastitem->setFlag(QGraphicsItem::ItemIsMovable, false);
            pPastitem->setPos(maxpos- pPastitem->boundingRect().topLeft());
        }
        SaveDefineLib("UserDefineLibraryLib.sk"); //���±����Զ���ͼ��
        return;
    }
    //ͼ���ڳ����ϵ��������boundingRect���õ���x�������scenePos��x����
    if(nItemCount > 0) //����ڵ�ǰ����������ͼ�ε������������
    {
        item = item_list.at(0);
        itemrect = item->boundingRect();
        maxpos = item->boundingRect().topLeft()+item->scenePos();
        sStrList = item->data(GROUP_DATALIST_KEY).toStringList();
        if(!sStrList.isEmpty())
        {
            sPath.append(sStrList.at(0)); //��ͼ��·��
        }

        for(i = 1;i < nItemCount;i++)
        {
            item = item_list.at(i);
            item->setSelected(false);
            pos = item->boundingRect().topLeft()+item->scenePos();

            sStrList = item->data(GROUP_DATALIST_KEY).toStringList();
            if(!sStrList.isEmpty())
            {
                sPath.append(sStrList.at(0)); //��ͼ��·��
            }

            if(maxpos.x() < pos.x() && maxpos.y() <= pos.y())//ͬ�д���
                maxpos = pos;
            if(maxpos.x() > pos.x() && maxpos.y() < pos.y()) //���д���
                maxpos = pos;
        }
    }
    //���¿�ʼ��ͼ�μ��ص�ָ��ͼ��ҳ��

    if(nItemCount >= 1)
        maxpos.setX(maxpos.x()+itemrect.width() +space);

    if(maxpos.x() >= width) //ˮƽ���򳬳������Ŀ�ȵ�ʱ��
    {
        top = maxpos.y() + itemrect.height() + space;
        maxpos.setX(0);
        maxpos.setY(top);
        if(top >= heigth) //��ֱ���򳬳���ǰ�����ĸ߶�
        {
            box.setText(tr("��ͼ��ҳ���Ѵ�������ѡ������ͼ��ҳ��洢!"));
            box.exec();
            return;
        }      
    }

    item = CreateGroupItem();
    GroupFunction.CopyItem(&pPastitem,item);
    SetItemPath(pPastitem); //����·��
    vUserScene.at(nActiveIndex)->clearSelection();
    vUserScene.at(nActiveIndex)->addItem(pPastitem);
    QItemGroup *pItemGroup = NULL;
    pItemGroup = dynamic_cast<QItemGroup *> (pPastitem);
    if(pItemGroup)
        pItemGroup->setResizableOff();

    pPastitem->setData(GROUP_TYPE_KEY,QVariant(LIBRARY_LIB_GROUP)); //����ͼ���Keyֵ
    QString sname = QString::number(nActiveIndex);
    sname = sname+"-";
    sname = sname+ QString::number(nTotalItem+1);
    sname = sname+"-";
    sname = sname+ "2";//�û��Զ���item
    pPastitem->setData(GROUP_NAME_KEY,QVariant(sname));
    pPastitem->setFlag(QGraphicsItem::ItemIsSelectable, true);
    pPastitem->setFlag(QGraphicsItem::ItemIsMovable, false);
    pPastitem->setPos(maxpos- pPastitem->boundingRect().topLeft()); // - item->boundingRect().topLeft()
    SaveDefineLib("UserDefineLibraryLib.sk"); //���±����Զ���ͼ��
}

void SaveUserDefineLib::SetItemPath(QGraphicsItem *pItem)//���ͼ�ε�·��x-x-x��ʽ
{
    int nMark = 0; //0��ʾitem��1��ʾͼƬ
    int nVal = 1;   //ͼ�α��
    int nIndex = 0;
    int i = 0;
    QStringList sList ;
    QString str = "";
    QVector <int>ID;
    ID.clear();

    if (pItem->type() == SAM_DRAW_OBJECT_PIXMAP) //��ͼƬ
    {
        nMark = 1;
    }

//    for(i = 0; i < sPath.size(); i++)
//    {
//        sList = sPath.at(i).split("-", QString::SkipEmptyParts);
//        if(sList.size() != 4)
//            return ;
//        nIndex = sList.at(1).toInt(); //ȡ���
//        if(nVal == nIndex)
//        {
//            nVal++;
//            i = 0;
//        }
//    }
    for(i = 0; i < sPath.size(); i++)
    {
        sList = sPath.at(i).split("-", QString::SkipEmptyParts);
        if(sList.size() != 4)
            return ;
        nIndex = sList.at(1).toInt(); //ȡ���
        ID.append(nIndex);
    }

    for(i = 0; i < ID.size(); )
    {
        if(nVal == ID.at(i))
        {
            nVal++;
            i = 0;
        }
        else
            i++;
    }

    str = QString("%1-%2-%3").arg(nActiveIndex).arg(nVal).arg(nMark);
    str = str+tr("-2"); //��ʾ���Զ���ͼ��

    sList.clear();
    sList.append(str);
    pItem->setData(GROUP_DATALIST_KEY,QVariant(sList));
}

void SaveUserDefineLib::on_m_Cancel_clicked() //ȡ��
{
    QDialog::close();
}

//������ͼ����ϳ�һ��ͼ��
QGraphicsItem * SaveUserDefineLib::CreateGroupItem()
{
    QItemGroup *Group = new QItemGroup();
    int i = 0;
    QGraphicsItem *pItem = NULL;
    QGroupItem *pBaseItem = NULL;
    QStringList slist;
    slist.clear();
    if(pwnd->SaveItemToLibList.size() == 1)
    {
        pItem = pwnd->SaveItemToLibList.at(0);
        slist = pItem->data(GROUP_DATALIST_KEY).toStringList();
        if(pItem->type() == SAM_DRAW_OBJECT_PIXMAP)
        {
           // QPixmapItem *PicItem = dynamic_cast<QPixmapItem *> (pItem);
           // PicItem->scale(100,100);
           // pItem = PicItem;
        }
        else
        {
            pBaseItem = new QGroupItem(pItem);
            pBaseItem->SetWidth(100);
            pBaseItem->SetHeigth(100);
        }
        pItem->setData(GROUP_TYPE_KEY,QVariant(USER_DEFINE_GROUP));
        pItem->setData(GROUP_DATALIST_KEY,QVariant(slist));
        return pItem;
    }
    for(i=0;i < pwnd->SaveItemToLibList.size();i++)
    {
        //�����֮ǰ���ѡ��״̬��
        pwnd->SaveItemToLibList.at(i)->setFlag(QGraphicsItem::ItemIsSelectable, false);
        Group->addToGroup(pwnd->SaveItemToLibList.at(i));
    }

    Group->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
    Group->setFlag(QGraphicsItemGroup::ItemIsMovable, false);
    /*Create the handle rects when a new group borned*/
    //QRectF qrcBndRect = Group->sceneBoundingRect();
   // Group->drawTracker(TRK_SELECTED, (QGraphicsScene *)this, qrcBndRect);
    Group->setData(GROUP_TYPE_KEY,QVariant(USER_DEFINE_GROUP)); //�����û��Զ�����ϵ�keyֵ
    pItem = Group;
    pBaseItem = new QGroupItem(pItem);
    pBaseItem->SetWidth(100);
    pBaseItem->SetHeigth(100);
    return pItem;
}

void SaveUserDefineLib::SaveDefineLib(QString sPath)
{
    QFile file;
    QString sFilePath = sPath;  
    if(sFilePath.isEmpty())
        return;
    file.setFileName(sFilePath);
    if(!file.open(QIODevice::WriteOnly))
        return ;
    QDataStream saveData(&file);
    SamDrawScene *pSvene = NULL;
    int sceneSize = vUserScene.size();
    saveData << sceneSize;
    for(int i =0; i< sceneSize; i++)
    {
        pSvene = vUserScene.at(i);
        saveData << pSvene;
    }
    file.close();
}

QPointF SaveUserDefineLib::getMaxPoint()
{
    QPainterPath path;
    QGraphicsItem *item = NULL;
    QRectF itemrect;
    QStringList sStrList;

    int i = 0;
    double top = 0;
    QPointF maxpos;
    QPointF pos;
    double space = 10;//ͼ��֮��ļ��
    int nItemCount = 0; //item����
    double width = vUserScene.at(nActiveIndex)->width(); //�����Ŀ��
    double heigth = vUserScene.at(nActiveIndex)->height();//�����ĸ���
    maxpos.setX(0);
    maxpos.setY(0);
    itemrect.setSize(QSizeF(100,100));
    itemrect.setTopLeft(QPointF(0,0));

    path.addRect(0,0,width,heigth);
    vUserScene.at(nActiveIndex)->setSelectionArea(path);
    QList<QGraphicsItem *> item_list=vUserScene.at(nActiveIndex)->selectedItems();

    nItemCount = item_list.size();
    sPath.clear();
    sStrList.clear();


    //ͼ���ڳ����ϵ��������boundingRect���õ���x�������scenePos��x����
    if(nItemCount > 0) //����ڵ�ǰ����������ͼ�ε������������
    {
        item = item_list.at(0);
        itemrect = item->boundingRect();
        maxpos = item->boundingRect().topLeft()+item->scenePos();
        sStrList = item->data(GROUP_DATALIST_KEY).toStringList();
        if(!sStrList.isEmpty())
        {
            sPath.append(sStrList.at(0)); //��ͼ��·��
        }

        for(i = 1;i < nItemCount;i++)
        {
            item = item_list.at(i);
            item->setSelected(false);
            pos = item->boundingRect().topLeft()+item->scenePos();

            sStrList = item->data(GROUP_DATALIST_KEY).toStringList();
            if(!sStrList.isEmpty())
            {
                sPath.append(sStrList.at(0)); //��ͼ��·��
            }

            if(maxpos.x() < pos.x() && maxpos.y() <= pos.y())//ͬ�д���
                maxpos = pos;
            if(maxpos.x() > pos.x() && maxpos.y() < pos.y()) //���д���
                maxpos = pos;
        }
    }
    //���¿�ʼ��ͼ�μ��ص�ָ��ͼ��ҳ��

    if(nItemCount >= 1)
        maxpos.setX(maxpos.x()+itemrect.width() +space);

    if(maxpos.x() >= width) //ˮƽ���򳬳������Ŀ�ȵ�ʱ��
    {
        top = maxpos.y() + itemrect.height() + space;
        maxpos.setX(0);
        maxpos.setY(top);
        if(top >= heigth) //��ֱ���򳬳���ǰ�����ĸ߶�
        {
            QMessageBox box(this);
            box.setText(tr("��ͼ��ҳ���Ѵ�������ѡ������ͼ��ҳ��洢!"));
            box.exec();
            return QPointF(0,0);
        }
    }
    return maxpos;
}

