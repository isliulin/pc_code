#include "OpenLibrary.h"
#include "ui_OpenLibrary.h"
#include <QMessageBox>
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
#include <QGraphicsScene>
#include <QScrollBar>

extern bool  is_tanslator;

#include "SKDrawTool.h"
#define EXTERN_PICTURE_DIR "extern"
OpenLibrary::OpenLibrary(QWidget *parent) :
        EXTERN_LIB_NODE(tr("��չͼ��")),
        SELF_DEF_NODE("UserDefined"),
        QDialog(parent), ui(new Ui::OpenLibrary)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("ͼ���б�"));
    ui->treeWidget->expandAll();

    ui->MainView->setAlignment(Qt::AlignTop | Qt::AlignLeft);

//    QRect rc = ui->MainView->geometry();
//    if(pwnd->vBaseLibraryScene.isEmpty())
//    {
//        loadBaseLibAndUserDefineLib(rc);
//    }

    loadUserDefineLib();//�����û��Զ���ͼ��
	

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    nSelectLibType = 1;//1��ʾѡ����ǻ���ͼ�⣬2��ʾ�û��Զ���ͼ��
    nActiveIndex = 0;
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->clearSelection();
    setCurrentLibSheet(1,9);

    int count = pwnd->vBaseLibraryScene.size();
    for(int i = 0; i < count; i++)
    {
        connect(pwnd->vBaseLibraryScene.at(i),SIGNAL(DoubleClickItem(QGraphicsItem*)),this,SLOT(onDoublClickLibraryItem(QGraphicsItem*)));
    }

    //���ϴδ򿪵�ͼ������
    if(pwnd->sLibraryPath.size() == 2)
    {
        QTreeWidgetItem * pItem = NULL;
        QString str  = pwnd->sLibraryPath.at(0);
        QList<QTreeWidgetItem*> pList = ui->treeWidget->findItems(str,Qt::MatchExactly);
        if(pList.size() == 1)
        {
            pItem = pList.at(0);
        }
        if(NULL == pItem)
        {
            return;
        }
        for(int i = 0; i < pItem->childCount(); i++)
        {
            QString sName = pItem->child(i)->text(0);

            QString sFileName = pwnd->sLibraryPath.at(1);
            if(1 == is_tanslator)//Ӣ��
            {
                //ע�� ����Щ���Ĳ��÷��룬��ͼƬ�ļ��ж������ļ�������
                if(sFileName == tr("��ͨ"))
                {
                    sFileName = "Traffic";
                }
                else if(sFileName == tr("����"))
                {
                    sFileName = "Other";
                }
                else if(sFileName == tr("ͼ�갴ť"))
                {
                    sFileName = "Icon Button";
                }
                else if(sFileName == tr("����"))
                {
                    sFileName = "Switch";
                }
                else if(sFileName == tr("��ť��ָʾ��"))
                {
                    sFileName = "Button And Light";
                }
                else if(sFileName == tr("����"))
                {
                    sFileName = "Digital";
                }
                else if(sFileName == tr("����ť"))
                {
                    sFileName = "Directional Button";
                }
                else if(sFileName == tr("���ΰ�ť"))
                {
                    sFileName = "Square Button";
                }
                else if(sFileName == tr("Ӳ��"))
                {
                    sFileName = "Hardware";
                }
                else if(sFileName == (tr("��") + tr("����ɫ")))
                {
                    sFileName = "Pipeline Gray";
                }
                else if(sFileName == (tr("��") + tr("����ɫ")))
                {
                    sFileName = "Pipeline Yellow";
                }
                else if(sFileName == tr("Ӣ���ַ���ɫ"))
                {
                    sFileName = "Character Gray";
                }
                else if(sFileName == tr("Ӣ���ַ���ɫ"))
                {
                    sFileName = "Character Red";
                }
                else if(sFileName == tr("Ӣ���ַ���ɫ"))
                {
                    sFileName = "Character Blue";
                }
            }

            if(sName == sFileName)
            {
                pItem->child(i)->setSelected(true);
                on_treeWidget_currentItemChanged(pItem->child(i), NULL);
                break;
            }
        }
    }
}

OpenLibrary::~OpenLibrary()
{
    for(int i = 0;i < vUserScene.size();i++)
        delete vUserScene[i];
    vUserScene.clear();    
    int count = pwnd->vBaseLibraryScene.size();
    for(int i = 0; i < count; i++)
    {
        disconnect(pwnd->vBaseLibraryScene.at(i),SIGNAL(DoubleClickItem(QGraphicsItem*)),this,SLOT(onDoublClickLibraryItem(QGraphicsItem*)));
    }
	if (userScene)
	{
		userScene->deleteLater();
	}
    delete ui;
}

//void OpenLibrary::loadBaseLibAndUserDefineLib(QRect rect)
//{
//    if(pwnd->vBaseLibraryScene.size() > 0)
//        return;

//    QFile file("LibraryLib.sk");
//    if(!file.open(QIODevice::ReadOnly))
//        return ;

//    QDataStream openData(&file);
//    SamDrawScene *pSvene = NULL;
//    pwnd->vBaseLibraryScene.clear();
//    int sceneSize = 0;
//    openData >> sceneSize;
//    nSelectLibType = 1;
//    for(int i =0; i< sceneSize; i++)
//    {
//        pSvene = new SamDrawScene();
//        openData >> pSvene;
//        pSvene->setSceneRect(0,0,rect.width()-3,rect.height()-3);
//        pwnd->vBaseLibraryScene.push_back(pSvene);
//        nActiveIndex = i;
//        lockCurrentSheetItem();
//    }
//    file.close();
//}

void OpenLibrary::loadUserDefineLib()
{
    userScene = new LibRaryScene(this);
    nSelectLibType = 2;
    
    connect(userScene,SIGNAL(DoubleClickItem(QGraphicsItem*)),this,SLOT(onDoublClickLibraryItem(QGraphicsItem*)));
    QTreeWidgetItem * userLibTree = new QTreeWidgetItem(QStringList(EXTERN_LIB_NODE));
    ui->treeWidget->insertTopLevelItem(1,userLibTree);
    QDir picDir(EXTERN_PICTURE_DIR);
    if(picDir.exists())
    {
        QFileInfoList fileList = picDir.entryInfoList(QDir::NoDotAndDotDot|QDir::Dirs);
        qDebug() <<tr("��չͼ��·��");
        foreach(QFileInfo inf,fileList)
        {
            qDebug() << inf.absoluteFilePath();
            QString sFileName = inf.baseName();
            if(sFileName == tr("����ͼƬ"))
            {
                continue;//�Ѽ���ͼƬ�ļ����ų�
            }
            if(1 == is_tanslator)//Ӣ��
            {
                //ע�� ����Щ���Ĳ��÷��룬��ͼƬ�ļ��ж������ļ�������
                if(sFileName == tr("��ͨ"))
                {
                    sFileName = "Traffic";
                }
                else if(sFileName == tr("����"))
                {
                    sFileName = "Other";
                }
                else if(sFileName == tr("ͼ�갴ť"))
                {
                    sFileName = "Icon Button";
                }
                else if(sFileName == tr("����"))
                {
                    sFileName = "Switch";
                }
                else if(sFileName == tr("��ť��ָʾ��"))
                {
                    sFileName = "Button And Light";
                }
                else if(sFileName == tr("����"))
                {
                    sFileName = "Digital";
                }
                else if(sFileName == tr("����ť"))
                {
                    sFileName = "Directional Button";
                }
                else if(sFileName == tr("���ΰ�ť"))
                {
                    sFileName = "Square Button";
                }
                else if(sFileName == tr("Ӳ��"))
                {
                    sFileName = "Hardware";
                }
                else if(sFileName.contains(tr("����ɫ")))//�ܵ���ɫ
                {
                    sFileName = "Pipeline Gray";
                }
                else if(sFileName.contains(tr("����ɫ")))
                {
                    sFileName = "Pipeline Yellow";
                }
                else if(sFileName == tr("Ӣ���ַ���ɫ"))
                {
                    sFileName = "Character Gray";
                }
                else if(sFileName == tr("Ӣ���ַ���ɫ"))
                {
                    sFileName = "Character Red";
                }
                else if(sFileName == tr("Ӣ���ַ���ɫ"))
                {
                    sFileName = "Character Blue";
                }
            }
            QTreeWidgetItem * item = new QTreeWidgetItem(QStringList(sFileName));
            userLibTree->addChild(item);
        }
        userLibTree->setExpanded(true);
    }

}

void OpenLibrary::on_treeWidget_itemClicked(QTreeWidgetItem* item, int column)
{
    return;
    QString str = "";
    str = item->text(column);
    QTreeWidgetItem* pitem;
    pitem =item->parent();
    QString parent = "";
    if(pitem)
    {
        parent = pitem->text(column);
    }
    qDebug() << "on_treeWidget_itemClicked:"<<str;
    //�����ǰ�ť��
    if("" != parent && tr("��ť") == parent)
    {
        if(str == tr("��־һ"))
        {
            setCurrentLibSheet(1,9);
        }
        else if(str == tr("��־��"))
        {
            setCurrentLibSheet(1,23);
        }
        else if(str == tr("��־��"))
        {
            setCurrentLibSheet(1,24);
        }
        else if(str == tr("����"))
        {
            setCurrentLibSheet(1,25);
        }
        else if(str == tr("¥��һ"))
        {
            setCurrentLibSheet(1,12);
        }
        else if(str == tr("¥���"))
        {
            setCurrentLibSheet(1,13);
        }
        else if(str == tr("¥����"))
        {
            setCurrentLibSheet(1,14);
        }
        else if(str == tr("¥����"))
        {
            setCurrentLibSheet(1,15);
        }
        else if(str == tr("����ťһ"))
        {
            setCurrentLibSheet(1,16);
        }
        else if(str == tr("����ť��"))
        {
            setCurrentLibSheet(1,17);
        }
        else if(str == tr("������ɫ"))
        {
            setCurrentLibSheet(1,40);
        }
        else if(str == tr("������ɫ"))
        {
            setCurrentLibSheet(1,41);
        }
        else if(str == tr("�����ɫ"))
        {
            setCurrentLibSheet(1,42);
        }
        else if(str == tr("�����ɫ"))
        {
            setCurrentLibSheet(1,43);
        }
        else if(str == tr("�����ɫ"))
        {
            setCurrentLibSheet(1,44);
        }
        else if(str == tr("�����ɫ"))
        {
            setCurrentLibSheet(1,45);
        }
        else if(str == tr("��־״̬��ɫ"))
        {
            setCurrentLibSheet(1,46);
        }
        else if(str == tr("��־״̬��ɫ"))
        {
            setCurrentLibSheet(1,47);
        }
        else if(str == tr("��־״̬��ɫ"))
        {
            setCurrentLibSheet(1,48);
        }
        else if(str == tr("����ɫһ"))
        {
            setCurrentLibSheet(1,51);
        }
        else if(str == tr("����ɫ��"))
        {
            setCurrentLibSheet(1,73);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,52);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,74);
        }
        else if(str == tr("���ɫһ"))
        {
            setCurrentLibSheet(1,49);
        }
        else if(str == tr("���ɫ��"))
        {
            setCurrentLibSheet(1,75);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,50);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,76);
        }
        else if(str == tr("����ɫһ"))
        {
            setCurrentLibSheet(1,53);
        }
        else if(str == tr("����ɫ��"))
        {
            setCurrentLibSheet(1,77);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,54);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,78);
        }
        else if(str == tr("���ɫһ"))
        {
            setCurrentLibSheet(1,55);
        }
        else if(str == tr("���ɫ��"))
        {
            setCurrentLibSheet(1,79);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,56);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,80);
        }
        else if(str == tr("���ɫһ"))
        {
            setCurrentLibSheet(1,57);
        }
        else if(str == tr("���ɫ��"))
        {
            setCurrentLibSheet(1,81);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,58);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,82);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,59);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,83);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,60);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,84);
        }
        else if(str == tr("����һ"))
        {
            setCurrentLibSheet(1,11);
        }
        else if(str == tr("���ض�"))
        {
            setCurrentLibSheet(1,20);
        }
        else if(str == tr("��ǩһ"))
        {
            setCurrentLibSheet(1,34);
        }
        else if(str == tr("��ǩ��"))
        {
            setCurrentLibSheet(1,36);
        }
        else if(str == tr("״̬"))
        {
            setCurrentLibSheet(1,35);
        }
        else if(str == tr("����һ"))
        {
            setCurrentLibSheet(1,37);
        }
        else if(str == tr("�����"))
        {
            setCurrentLibSheet(1,38);
        }

        nSelectLibType = 1;
    }
        if("" != parent && EXTERN_LIB_NODE == parent)
	{
		userScene->clear();
                userScene->update();
        QString picpath = QDir::currentPath();
		picpath += "/";
		picpath += EXTERN_PICTURE_DIR;
		picpath += "/";
		picpath += str;
		picpath.replace("\\","/");
		QDir picDir(picpath);
                QSize size = ui->MainView->size();
                QPointF pos(0,0);
                int nWidth = 10;
                int nHight = 10;
                int i = 0;
		if (picDir.exists())
		{
			QStringList nameFilters = QStringList(".png");
            QFileInfoList infolist = picDir.entryInfoList();
            for(int iLen = 0; i < infolist.size(); iLen++)
			{
                QString path = QString("%1/%2-01.png").arg(picpath).arg(iLen);
				QPixmap picture(path);
				if (!picture.isNull())
				{
                                    if(nWidth + 100 < size.width())
                                    {
                                        pos.setX(nWidth);
                                        pos.setY(nHight);
                                        nWidth = nWidth + 110;
                                    }
                                    else
                                    {
                                        nHight = nHight + 110;
                                        nWidth = 10;
                                        pos.setX(nWidth);
                                        pos.setY(nHight);
                                        nWidth = nWidth + 110;
                                    }
                                    //qDebug()<<"befor "<<i<<":pos"<<pos;
                                        //userScene->addPixmap(picture);
                                        QPixmapItem *PicItem = new QPixmapItem(picture,QSize(100,100));
                                        path = path.section(EXTERN_PICTURE_DIR,1);
                                        path = EXTERN_PICTURE_DIR + path;
                                        qDebug()<<"path:"<<path;
                                        PicItem->setData(GROUP_TYPE_KEY,QVariant(LIBRARY_PIXMAP_GROUP));
                                        PicItem->setData(GROUP_NAME_KEY,QVariant(path));
                                        PicItem->setPos(pos - PicItem->boundingRect().topLeft());
                                        PicItem->setFlag(QGraphicsItem::ItemIsMovable, false);
                                        PicItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                                        PicItem->setSelected(false);
                                        userScene->addItem(PicItem);
				}
			}
		}
		ui->MainView->setScene(userScene);
                nSelectLibType = 2;
//                QScrollBar *bar = ui->MainView->verticalScrollBar();
//               int val = bar->pageStep();
//                bar->setMinimum(val);
	}


//    if(str == tr("��ť1"))
//    {
//        setCurrentLibSheet(1,0);
//    }
//    else if(str == tr("��ť2"))
//    {
//        setCurrentLibSheet(1,1);
//    }
//    else if(str == tr("��ť3"))
//    {
//        setCurrentLibSheet(1,4);
//    }
//    else if(str == tr("��ť4"))
//    {
//        setCurrentLibSheet(1,5);
//    }
//    else if(str == tr("��ť5"))
//    {
//        setCurrentLibSheet(1,7);
//    }
//    else if(str == tr("��ť6"))
//    {
//        setCurrentLibSheet(1,9);
//    }
//    else if(str == tr("��ť7"))
//    {
//        setCurrentLibSheet(1,10);
//    }
//    else if(str == tr("��ť8"))
//    {
//        setCurrentLibSheet(1,20);
//    }
//    else if(str == tr("��ť9"))
//    {
//        setCurrentLibSheet(1,23);
//    }
//    else if(str == tr("��ť10"))
//    {
//        setCurrentLibSheet(1,27);
//    }
//    else if(str == tr("��ť11"))
//    {
//        setCurrentLibSheet(1,28);
//    }
//    else if(str == tr("��ť12"))
//    {
//        setCurrentLibSheet(1,29);
//    }
//    else if(str == tr("��ť13"))
//    {
//        setCurrentLibSheet(1,30);
//    }
//    //������ָʾ�ƿ�
//    else if(str == tr("ָʾ��1"))
//    {
//        setCurrentLibSheet(1,2);
//    }
//    else if(str == tr("ָʾ��2"))
//    {
//        setCurrentLibSheet(1,3);
//    }
//    else if(str == tr("ָʾ��3"))
//    {
//        setCurrentLibSheet(1,6);
//    }
//    else if(str == tr("ָʾ��4"))
//    {
//        setCurrentLibSheet(1,8);
//    }
//    else if(str == tr("ָʾ��5"))
//    {
//        setCurrentLibSheet(1,11);
//    }
//    else if(str == tr("ָʾ��6"))
//    {
//        setCurrentLibSheet(1,12);
//    }
//    else if(str == tr("ָʾ��7"))
//    {
//        setCurrentLibSheet(1,13);
//    }
//    else if(str == tr("ָʾ��8"))
//    {
//        setCurrentLibSheet(1,15);
//    }
//    else if(str == tr("ָʾ��9"))
//    {
//        setCurrentLibSheet(1,16);
//    }
//    else if(str == tr("ָʾ��10"))
//    {
//        setCurrentLibSheet(1,25);
//    }
//    else if(str == tr("ָʾ��11"))
//    {
//        setCurrentLibSheet(1,49);
//    }
//    //�����Ƿ����ͷ��
//    else if(str == tr("��ͷ��1"))
//    {
//        setCurrentLibSheet(1,14);
//    }
//    else if(str == tr("��ͷ��2"))
//    {
//        setCurrentLibSheet(1,22);
//    }
//    //���������Կ��
//    else if(str == tr("���Կ�1"))
//    {
//        setCurrentLibSheet(1,17);
//    }
//    else if(str == tr("���Կ�2"))
//    {
//        setCurrentLibSheet(1,18);
//    }
//    else if(str == tr("���Կ�3")) //new add
//    {
//        setCurrentLibSheet(1,41);
//    }
//    else if(str == tr("��Ŀ��"))
//    {
//        setCurrentLibSheet(1,31);
//    }
//    //�����Ƿ��򿪹ؿ�
//    else if(str == tr("���ؿ�1"))
//    {
//        setCurrentLibSheet(1,24);
//    }
//    else if(str == tr("���ؿ�2"))
//    {
//        setCurrentLibSheet(1,26);
//    }
//    //�����Ƿ�����ת��
//    else if(str == tr("��ת��"))
//    {
//        setCurrentLibSheet(1,19);
//    }
//    //�����Ƿ����ʶ��
//    else if(str == tr("�����ʶ1"))
//    {
//        setCurrentLibSheet(1,32);
//    }
//    else if(str == tr("�����ʶ2"))
//    {
//        setCurrentLibSheet(1,33);
//    }
//    //�����Ƿ�������
//    else if(str == tr("�����1"))
//    {
//        setCurrentLibSheet(1,21);
//    }
//    else if(str == tr("�����2"))//new add
//    {
//        setCurrentLibSheet(1,34);
//    }
//    //�����ǹܵ�
//    else if(str == tr("�ܵ�"))
//    {
//        setCurrentLibSheet(1,35);
//    }
//    //�����ǵ������
//    else if(str == tr("�������1"))
//    {
//        setCurrentLibSheet(1,36);
//    }
//    else if(str == tr("�������2"))
//    {
//        setCurrentLibSheet(1,42);
//    }
//    else if(str == tr("�������3"))
//    {
//        setCurrentLibSheet(1,44);
//    }
//    //�����Ƿ���
//    else if(str == tr("����1"))
//    {
//        setCurrentLibSheet(1,37);
//    }
//    else if(str == tr("����2"))
//    {
//        setCurrentLibSheet(1,46);
//    }
//    else if(str == tr("����3"))
//    {
//        setCurrentLibSheet(1,47);
//    }
//    else if(str == tr("����4"))
//    {
//        setCurrentLibSheet(1,48);
//    }
//    //�������Ǳ��α�
//    else if(str == tr("�Ǳ��α�"))
//    {
//        setCurrentLibSheet(1,38);
//    }
//    //�����ǽ��贫����
//    else if(str == tr("���贫����"))
//    {
//        setCurrentLibSheet(1,39);
//    }
//    //�����ǵ�������
//    else if(str == tr("��������"))
//    {
//        setCurrentLibSheet(1,40);
//    }
//    //�����ǵ���
//    else if(str == tr("����"))
//    {
//        setCurrentLibSheet(1,43);
//    }
    //������ѡ���û��Զ���ͼ��
    if("" != parent && tr("�Զ���ͼ��") == parent)
    {
        if(str == tr("ͼ��һ"))
        {
            setCurrentLibSheet(2,0);
        }
        else if(str == tr("ͼ���"))
        {
            setCurrentLibSheet(2,1);
        }

        else if(str == tr("ͼ����"))
        {
            setCurrentLibSheet(2,2);
        }
        else if(str == tr("ͼ����"))
        {
            setCurrentLibSheet(2,3);
        }
        else if(str == tr("ͼ����"))
        {
            setCurrentLibSheet(2,4);
        }
        else if(str == tr("ͼ����"))
        {
            setCurrentLibSheet(2,5);
        }
        else if(str == tr("ͼ����"))
        {
            setCurrentLibSheet(2,6);
        }
        else if(str == tr("ͼ���"))
        {
            setCurrentLibSheet(2,7);
        }
        else if(str == tr("ͼ���"))
        {
            setCurrentLibSheet(2,8);
        }
        else if(str == tr("ͼ��ʮ"))
        {
            setCurrentLibSheet(2,9);
        }
        else if(str == tr("ͼ��ʮһ"))
        {
            setCurrentLibSheet(2,10);
        }
        else if(str == tr("ͼ��ʮ��"))
        {
            setCurrentLibSheet(2,11);
        }
        else if(str == tr("ͼ��ʮ��"))
        {
            setCurrentLibSheet(2,12);
        }
        else if(str == tr("ͼ��ʮ��"))
        {
            setCurrentLibSheet(2,13);
        }
        else if(str == tr("ͼ��ʮ��"))
        {
            setCurrentLibSheet(2,14);
        }
    }
}

void OpenLibrary::setCurrentLibSheet(int nSelectType,int nIndex)
{
    if(pwnd->vBaseLibraryScene.isEmpty())
    {
        QMessageBox box(QMessageBox::Warning,tr("����"),tr("ȱ��LibraryLib.sk�ļ�,ͼ���ʧ��!"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
        box.exec();
         return ;
    }
    
    qDebug() << "setCurrentLibSheet:"<< nIndex;
    if(nSelectType == 1)
    {
        if(nIndex >= pwnd->vBaseLibraryScene.size())
        {
            return;
        }
        ui->MainView->setScene(pwnd->vBaseLibraryScene.at(nIndex));
        pwnd->vBaseLibraryScene.at(nIndex)->clearSelection();
        pwnd->vBaseLibraryScene.at(nIndex)->reBondingTrackers();
        QRectF rc = ui->MainView->scene()->sceneRect();
        ui->MainView->scene()->setSceneRect(0,0,rc.width(),1000);
    }
    else if(nSelectType == 2)
    {
        //ui->MainView->setScene(vUserScene.at(nIndex));
    }

    nActiveIndex = nIndex;
    nSelectLibType = nSelectType;
}

void OpenLibrary::on_m_OkBtn_clicked()//ȷ��
{
    if(!getSaveItem())
        return;
    if(pwnd->SaveItemToLibList.isEmpty())
    {
        QMessageBox box(this);
        box.setText(tr("û��ѡ��ͼ��!"));
        box.exec();
        return;
    }  
    QDialog::accept();
}

bool OpenLibrary::getSaveItem()
{
    QList<QGraphicsItem *> Items;
    if(nSelectLibType == 1)     //����ͼ��
        Items = pwnd->vBaseLibraryScene.at(nActiveIndex)->selectedItems();
    else if(nSelectLibType == 2)//�û��Զ���ͼ��
        Items = userScene->selectedItems();
    if(Items.size() != 1 ) //ѡ��������û��ѡ���ʱ�򷵻�
        return false;
    DrawItemToScene FunClass;
    if(nSelectLibType == 1)     //����ͼ��
        Items.at(0)->setData(GROUP_TYPE_KEY,QVariant(LIBRARY_LIB_GROUP)); //����ͼ���Keyֵ
    else if(nSelectLibType == 2)//�û��Զ���ͼ��
        Items.at(0)->setData(GROUP_TYPE_KEY,QVariant(LIBRARY_PIXMAP_GROUP)); //����ͼ���Keyֵ
    FunClass.CopyItem(&pCopyItem,Items.at(0));

    pwnd->SaveItemToLibList.clear();
    pwnd->SaveItemToLibList.append(pCopyItem);

    if(nSelectLibType == 1)     //����ͼ��
    {
        pwnd->vBaseLibraryScene.at(nActiveIndex)->clearSelection();
        pwnd->vBaseLibraryScene.at(nActiveIndex)->reBondingTrackers();
    }
    return true;
}

void OpenLibrary::on_m_Cancel_clicked()//ȡ��
{
    QDialog::close();
}

void OpenLibrary::on_m_AlterItem_clicked()//�޸�
{
    if(!getSaveItem())
        return;
    if(!pwnd->SaveItemToLibList.isEmpty())
    {
        SKDrawTool *pDlg = new SKDrawTool(this);
        pDlg->exec();
        pDlg->deleteLater();
        pDlg = NULL;
    }
    else
    {
        QMessageBox box(this);
        box.setText(tr("û��ѡ��ͼ��!"));
        box.exec();
        return;
    }
}

void OpenLibrary::lockCurrentSheetItem()
{
    QPainterPath path;
    QList<QGraphicsItem *> item_list;
    item_list.clear();

    if(nSelectLibType == 1)//����ͼ��
    {
        path.addRect(0,0,pwnd->vBaseLibraryScene.at(nActiveIndex)->width(),pwnd->vBaseLibraryScene.at(nActiveIndex)->height());
        pwnd->vBaseLibraryScene.at(nActiveIndex)->setSelectionArea(path);
        item_list=pwnd->vBaseLibraryScene.at(nActiveIndex)->selectedItems();
    }
    else if(nSelectLibType == 2)//�û��Զ���ͼ��
    {
        path.addRect(0,0,vUserScene.at(nActiveIndex)->width(),vUserScene.at(nActiveIndex)->height());
        vUserScene.at(nActiveIndex)->setSelectionArea(path);
        item_list=vUserScene.at(nActiveIndex)->selectedItems();
    }
    if(!item_list.isEmpty())
    {
        foreach (QGraphicsItem *item, item_list)
        {
            item->setFlag(QGraphicsItem::ItemIsMovable, false);
            item->setFlag(QGraphicsItem::ItemIsSelectable, true);
            item->setSelected(false);
            switch(item->type())
            {
            case SAM_DRAW_OBJECT_RECT:              //15
                {
                    QRectItem *rectItem = dynamic_cast<QRectItem *>(item);
                    if(rectItem)
                        rectItem->setResizableOff();
                    break;
                }
            case SAM_DRAW_OBJECT_ELIPSE:              //16
                {
                    QElipseItem *elipseItem = dynamic_cast<QElipseItem *>(item);
                    if(elipseItem)
                       elipseItem->setResizableOff();
                    break;
                }
            case SAM_DRAW_OBJECT_LINE:                 //17
                {
                    QLineItem *lineItem = dynamic_cast<QLineItem *>(item);
                    if(lineItem)
                        lineItem->setResizableOff();
                    break;
                }
            case SAM_DRAW_OBJECT_POLYGON:              //18
                {
                    QPolygonItem *polygonItem = dynamic_cast<QPolygonItem *>(item);
                    if(polygonItem)
                        polygonItem->setResizableOff();
                    break;
                }
            case SAM_DRAW_OBJECT_FOLDLINE:             //19
                {
                    QFoldLineItem *foldLineItem = dynamic_cast<QFoldLineItem *>(item);
                    if(foldLineItem)
                        foldLineItem->setResizableOff();
                    break;
                }
            case SAM_DRAW_OBJECT_FREELINE:             //20
                {
                    QFreeLineItem *freeLineItem = dynamic_cast<QFreeLineItem *>(item);
                    if(freeLineItem)
                        freeLineItem->setResizableOff();
                    break;
                }
            case SAM_DRAW_OBJECT_TEXT:                 //22
                {
                    QSimpleTextItem *textItem = dynamic_cast<QSimpleTextItem *>(item);
                    if(textItem)
                        textItem->setResizableOff();
                    break;
                }
            case SAM_DRAW_OBJECT_LINECIRCLE:           //25
                {
                    QLineCircleItem *lineCircleItem = dynamic_cast<QLineCircleItem *>(item);
                    if(lineCircleItem)
                        lineCircleItem->setResizableOff();
                    break;
                }
            case SAM_DRAW_OBJECT_ROUNDEDRECT:
                {
                    QRoundedRect *pRoundItem = dynamic_cast<QRoundedRect *>(item);
                    if(pRoundItem)
                        pRoundItem->setResizableOff();
                    break;
                }
            case SAM_DRAW_OBJECT_ARC:
                {
                    QArcItem *pArcItem = dynamic_cast<QArcItem *>(item);
                    if(pArcItem)
                        pArcItem->setResizableOff();
                    break;
                }
            case SAM_DRAW_OBJECT_GROUP:                //23
                {
                    QItemGroup *groupItem = dynamic_cast<QItemGroup *>(item);
                    if(groupItem)
                        groupItem->setResizableOff();

                    break;
                }
            default:
                break;
            }
        }
    }
}

void OpenLibrary::onDoublClickLibraryItem(QGraphicsItem *pItem)
{
    on_m_OkBtn_clicked();
}


void OpenLibrary::on_HelpButton_clicked()
{
    pwnd->loadHelpHtm(TOOLBAR_OPENLIBRARY);
}

void OpenLibrary::on_treeWidget_currentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous)
{
    QString str = "";
    str = current->text(0);
    QTreeWidgetItem* pitem;
    pitem =current->parent();
    QString parent = "";
    if(pitem)
    {
        parent = pitem->text(0);
    }

    //�����ǰ�ť��
    if("" != parent && tr("��ť") == parent)
    {
        if(str == tr("��־һ"))
        {
            setCurrentLibSheet(1,9);
        }
        else if(str == tr("��־��"))
        {
            setCurrentLibSheet(1,23);
        }
        else if(str == tr("��־��"))
        {
            setCurrentLibSheet(1,24);
        }
        else if(str == tr("����"))
        {
            setCurrentLibSheet(1,25);
        }
        else if(str == tr("¥��һ"))
        {
            setCurrentLibSheet(1,12);
        }
        else if(str == tr("¥���"))
        {
            setCurrentLibSheet(1,13);
        }
        else if(str == tr("¥����"))
        {
            setCurrentLibSheet(1,14);
        }
        else if(str == tr("¥����"))
        {
            setCurrentLibSheet(1,15);
        }
        else if(str == tr("����ťһ"))
        {
            setCurrentLibSheet(1,16);
        }
        else if(str == tr("����ť��"))
        {
            setCurrentLibSheet(1,17);
        }
        else if(str == tr("������ɫ"))
        {
            setCurrentLibSheet(1,40);
        }
        else if(str == tr("������ɫ"))
        {
            setCurrentLibSheet(1,41);
        }
        else if(str == tr("�����ɫ"))
        {
            setCurrentLibSheet(1,42);
        }
        else if(str == tr("�����ɫ"))
        {
            setCurrentLibSheet(1,43);
        }
        else if(str == tr("�����ɫ"))
        {
            setCurrentLibSheet(1,44);
        }
        else if(str == tr("�����ɫ"))
        {
            setCurrentLibSheet(1,45);
        }
        else if(str == tr("��־״̬��ɫ"))
        {
            setCurrentLibSheet(1,46);
        }
        else if(str == tr("��־״̬��ɫ"))
        {
            setCurrentLibSheet(1,47);
        }
        else if(str == tr("��־״̬��ɫ"))
        {
            setCurrentLibSheet(1,48);
        }
        else if(str == tr("����ɫһ"))
        {
            setCurrentLibSheet(1,51);
        }
        else if(str == tr("����ɫ��"))
        {
            setCurrentLibSheet(1,73);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,52);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,74);
        }
        else if(str == tr("���ɫһ"))
        {
            setCurrentLibSheet(1,49);
        }
        else if(str == tr("���ɫ��"))
        {
            setCurrentLibSheet(1,75);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,50);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,76);
        }
        else if(str == tr("����ɫһ"))
        {
            setCurrentLibSheet(1,53);
        }
        else if(str == tr("����ɫ��"))
        {
            setCurrentLibSheet(1,77);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,54);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,78);
        }
        else if(str == tr("���ɫһ"))
        {
            setCurrentLibSheet(1,55);
        }
        else if(str == tr("���ɫ��"))
        {
            setCurrentLibSheet(1,79);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,56);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,80);
        }
        else if(str == tr("���ɫһ"))
        {
            setCurrentLibSheet(1,57);
        }
        else if(str == tr("���ɫ��"))
        {
            setCurrentLibSheet(1,81);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,58);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,82);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,59);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,83);
        }
        else if(str == tr("��ɫһ"))
        {
            setCurrentLibSheet(1,60);
        }
        else if(str == tr("��ɫ��"))
        {
            setCurrentLibSheet(1,84);
        }
        else if(str == tr("�ܵ�һ"))
        {
            setCurrentLibSheet(1,85);
        }
        else if(str == tr("����"))
        {
            setCurrentLibSheet(1,86);
        }
        else if(str == tr("���"))
        {
            setCurrentLibSheet(1,87);
        }
        else if(str == tr("��������"))
        {
            setCurrentLibSheet(1,88);
        }
        else if(str == tr("�ܵ���"))
        {
            setCurrentLibSheet(1,89);
        }
        else if(str == tr("�ܵ���ɫ"))
        {
            setCurrentLibSheet(1,90);
        }
        else if(str == tr("�ܵ���ɫ"))
        {
            setCurrentLibSheet(1,91);
        }
        else if(str == tr("�ܵ���ɫ"))
        {
            setCurrentLibSheet(1,92);
        }
        else if(str == tr("�ܵ���ɫ"))
        {
            setCurrentLibSheet(1,93);
        }
        else if(str == tr("�ܵ���ɫ"))
        {
            setCurrentLibSheet(1,94);
        }
        else if(str == tr("�ܵ���ɫ"))
        {
            setCurrentLibSheet(1,95);
        }
        else if(str == tr("�Ǳ�"))
        {
            setCurrentLibSheet(1,96);
        }
        else if(str == tr("Ԫ����"))
        {
            setCurrentLibSheet(1,97);
        }
        else if(str == tr("������"))
        {
            setCurrentLibSheet(1,98);
        }
        else if(str == tr("����һ"))
        {
            setCurrentLibSheet(1,11);
        }
        else if(str == tr("���ض�"))
        {
            setCurrentLibSheet(1,20);
        }
        else if(str == tr("��ǩһ"))
        {
            setCurrentLibSheet(1,34);
        }
        else if(str == tr("��ǩ��"))
        {
            setCurrentLibSheet(1,36);
        }
        else if(str == tr("״̬"))
        {
            setCurrentLibSheet(1,35);
        }
        else if(str == tr("����һ"))
        {
            setCurrentLibSheet(1,37);
        }
        else if(str == tr("�����"))
        {
            setCurrentLibSheet(1,38);
        }
    }
    if("" != parent && EXTERN_LIB_NODE == parent)
    {
            userScene->clear();
            userScene->update();

            if(1 == is_tanslator)//Ӣ��
            {
                QString sFileName = str;
                //ע�� ����Щ���Ĳ��÷��룬��ͼƬ�ļ��ж������ļ�������
                if(sFileName == "Traffic")
                {
                    sFileName = tr("��ͨ");
                }
                else if(sFileName == "Other")
                {
                    sFileName = tr("����");
                }
                else if(sFileName == "Icon Button")
                {
                    sFileName = tr("ͼ�갴ť");
                }
                else if(sFileName == "Switch")
                {
                    sFileName = tr("����");
                }
                else if(sFileName == "Button And Light")
                {
                    sFileName = tr("��ť��ָʾ��");
                }
                else if(sFileName == "Digital")
                {
                    sFileName = tr("����");
                }
                else if(sFileName == "Directional Button")
                {
                    sFileName = tr("����ť");
                }
                else if(sFileName == "Square Button")
                {
                    sFileName = tr("���ΰ�ť");
                }
                else if(sFileName == "Hardware")
                {
                    sFileName = tr("Ӳ��");
                }
                else if(sFileName == "Pipeline Gray")
                {
                    sFileName = tr("��") + tr("����ɫ");
                }
                else if(sFileName == "Pipeline Yellow")
                {
                    sFileName = tr("��") + tr("����ɫ");
                }
                else if(sFileName == "Character Gray")
                {
                    sFileName = tr("Ӣ���ַ���ɫ");
                }
                else if(sFileName == "Character Red")
                {
                    sFileName = tr("Ӣ���ַ���ɫ");
                }
                else if(sFileName == "Character Blue")
                {
                    sFileName = tr("Ӣ���ַ���ɫ");
                }
                str = sFileName;
            }


            QString picpath = QDir::currentPath();
            picpath += "/";
            picpath += EXTERN_PICTURE_DIR;
            picpath += "/";
            picpath += str;//str �ڶ���Ŀ¼���� �硰���֡�
            picpath.replace("\\","/");
            QDir picDir(picpath);
            QSize size = ui->MainView->size();
            QPointF pos(0,0);
            int nWidth = 10;
            int nHight = 10;
            int i = 0;
            if (picDir.exists())
            {
                    QStringList nameFilters = QStringList(".png");
                    QFileInfoList infolist = picDir.entryInfoList();
                    for(int iLen = 0; iLen < infolist.size(); iLen++)
                    {
                            QString path = QString("%1/%2-01.png").arg(picpath).arg(iLen);
                            QPixmap picture(path);
                            if (!picture.isNull())
                            {
                                if(nWidth + 100 < size.width())
                                {
                                    pos.setX(nWidth);
                                    pos.setY(nHight);
                                    nWidth = nWidth + 110;
                                }
                                else
                                {
                                    nHight = nHight + 110;
                                    nWidth = 10;
                                    pos.setX(nWidth);
                                    pos.setY(nHight);
                                    nWidth = nWidth + 110;
                                }
                                //qDebug()<<"befor "<<i<<":pos"<<pos;
                                    //userScene->addPixmap(picture);
                                    QPixmapItem *PicItem = new QPixmapItem(picture,QSize(100,100));
                                    path = path.section(EXTERN_PICTURE_DIR,1);
                                    path = EXTERN_PICTURE_DIR + path;
                                    qDebug()<<"path:"<<path;
                                    PicItem->setData(GROUP_TYPE_KEY,QVariant(LIBRARY_PIXMAP_GROUP));
                                    PicItem->setData(GROUP_NAME_KEY,QVariant(path));
                                    PicItem->setPos(pos - PicItem->boundingRect().topLeft());
                                    PicItem->setFlag(QGraphicsItem::ItemIsMovable, false);
                                    PicItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
                                    PicItem->setSelected(false);
                                    userScene->addItem(PicItem);
                            }
                    }
            }
            ui->MainView->setScene(userScene);
            nSelectLibType = 2;
    }
    if(EXTERN_LIB_NODE == parent || tr("��ť") == parent)
    {
        pwnd->sLibraryPath.clear();
        pwnd->sLibraryPath.append(parent);
        pwnd->sLibraryPath.append(str);
    }

}

//**********************�Զ���ͼ�⵼�뿪��*********************
void OpenLibrary::on_treeWidget_itemPressed(QTreeWidgetItem* item, int column)
{
    if (qApp->mouseButtons() == Qt::RightButton)
    {
        if(item->text(column) == EXTERN_LIB_NODE)
        {
            QMenu   menu(this);
            QAction *action = menu.addAction(tr("�½�"));
            connect(action,SIGNAL(triggered()),SLOT(createNewFolder()));
            menu.exec(QCursor::pos());
        }
        else if(item->parent()->text(column) == EXTERN_LIB_NODE)
        {
            QMenu   menu(this);
            QAction *loadAction = menu.addAction(tr("����"));
            connect(loadAction,SIGNAL(triggered()),SLOT(loadSelfDefImages()));
            QAction *delAction = menu.addAction(tr("ɾ��"));
            connect(delAction,SIGNAL(triggered()),SLOT(delSelfDefImages()));
            menu.exec(QCursor::pos());
        }
    }
}

void OpenLibrary::createNewFolder()
{
    QString fileName;
    QString temp;
    int i;
    int j;
    bool useunable;
    int count = ui->treeWidget->currentItem()->childCount();
    for(i = 0; i < count; i++)
    {
        temp = SELF_DEF_NODE + QString::number(i);
        useunable = false;

        for(j = 0; j < count; j++)
        {
            if(ui->treeWidget->currentItem()->child(j)->text(0) == temp)
            {
                useunable = true;
                break;
            }
        }

        if(useunable == false)
        {
            fileName = temp;
            break;
        }
    }
    if(i == count)
    {
        fileName = SELF_DEF_NODE + QString::number(count);
    }

    // ������ʾ
    QTreeWidgetItem *item = new QTreeWidgetItem(QStringList(temp));
    QTreeWidgetItem *tree = ui->treeWidget->currentItem();
    tree->addChild(item);
    tree->setExpanded(true);

    // ����Ŀ¼
    QString absPath = QString("%1/%2").arg(EXTERN_PICTURE_DIR).arg(temp);
    QDir dir;
    dir.mkpath(absPath);
}

void OpenLibrary::loadSelfDefImages()
{
    QStringList fileList = QFileDialog::getOpenFileNames(this,tr("����"),QString(),"Image Files(*.jpg *.png)");
    QString dicPath(QString("%1/%2").arg(EXTERN_PICTURE_DIR).arg(ui->treeWidget->currentItem()->text(0)));

    loadImages2Extern(fileList,dicPath);
    drawNewScene(dicPath);
}

void OpenLibrary::delSelfDefImages()
{
    QMessageBox box(QMessageBox::Information,VERSION_NAME,tr("ɾ����Ŀ¼��"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("��"));
    box.button(QMessageBox::No)->setText(tr("��"));
    box.exec();
    if(box.clickedButton()== box.button(QMessageBox::No)) return;

    QTreeWidgetItem *pChild = ui->treeWidget->currentItem();

    // ɾ���ļ�Ŀ¼
    QString path(QDir::currentPath());
    QDir::setCurrent(EXTERN_PICTURE_DIR);
    deleteDir(pChild->text(0));
    QDir::setCurrent(path);

    // ɾ�������
    ui->treeWidget->removeItemWidget(pChild,0);
    delete pChild;
    pChild = NULL;
}

void OpenLibrary::loadImages2Extern(const QStringList &srcFiles,const QString &desPath)
{
    for(int i = 0; i != srcFiles.count();i++)
    {
        // ͼƬѹ������
        QPixmap prePic(srcFiles[i]);
        QPixmap newPic = prePic.scaled(800,600,Qt::KeepAspectRatio);
        newPic.save(QString("%1/%2-01.png").arg(desPath).arg(i+1),"PNG");
    }
}

bool OpenLibrary::deleteDir(const QString &dirName)
{
    QDir directory(dirName);
    if (!directory.exists())
    {
        return true;
    }

    QString srcPath = QDir::toNativeSeparators(dirName);
    if (!srcPath.endsWith(QDir::separator()))
        srcPath += QDir::separator();

    QStringList fileNames = directory.entryList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    bool error = false;
    for (QStringList::size_type i=0; i != fileNames.size(); ++i)
    {
        QString filePath = srcPath + fileNames.at(i);
        QFileInfo fileInfo(filePath);
        if (fileInfo.isFile() || fileInfo.isSymLink())
        {
            QFile::setPermissions(filePath, QFile::WriteOwner);
            if (!QFile::remove(filePath))
            {
                qDebug() << "remove file" << filePath << " faild!";
                error = true;
            }
        }
        else if (fileInfo.isDir())
        {
            if (!deleteDir(filePath))
            {
                error = true;
            }
        }
    }

    QDir dir;
    if (!dir.rmdir(dirName))
    {
        qDebug() << "remove dir" << dirName << " faild!";
        error = true;
    }

    return !error;
}

void OpenLibrary::drawNewScene(const QString &dirPath)
{
    QSize size = ui->MainView->size();
    QPointF pos(0,0);
    int nWidth = 10;
    int nHight = 10;

    QDir dir(dirPath);
    dir.setFilter(QDir::Files);
    QFileInfoList fileInfo = dir.entryInfoList();

    foreach(QFileInfo file,fileInfo)
    {
        QString path = file.absoluteFilePath();
        QPixmap pic(path);
        if (!pic.isNull())
        {
            if(nWidth + 100 >= size.width())
            {
                nHight =+ 110;
                nWidth = 10;
            }
            pos.setX(nWidth);
            pos.setY(nHight);
            nWidth =+ 110;

            QPixmapItem *picItem = new QPixmapItem(pic,QSize(100,100));
            path = path.section(EXTERN_PICTURE_DIR,1);
            path = EXTERN_PICTURE_DIR + path;
            picItem->setData(GROUP_TYPE_KEY,QVariant(LIBRARY_PIXMAP_GROUP));
            picItem->setData(GROUP_NAME_KEY,QVariant(path));
            picItem->setPos(pos - picItem->boundingRect().topLeft());
            picItem->setFlag(QGraphicsItem::ItemIsMovable, false);
            picItem->setFlag(QGraphicsItem::ItemIsSelectable, true);
            picItem->setSelected(false);
            userScene->addItem(picItem);
        }
    }
    ui->MainView->setScene(userScene);
    nSelectLibType = 2;
}
//*******************************************************END
