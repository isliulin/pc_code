#include "qstaticpicturegendlg.h"
#include "ui_qstaticpicturegendlg.h"
#include <QFileDialog>
#include <QBitmap>
#include "Frame/DrawDlg/OpenLibrary.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QStaticPictureGenDlg::QStaticPictureGenDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QStaticPictureGenDlg)
{
    ui->setupUi(this);

    pScene = new QGraphicsScene;
    ui->MainView->setScene(pScene);

    ui->m_pathedit->setVisible(false);
    pPixmap = new QPixmapItem() ;
    sDataList.clear();
    pOldItem = NULL;
}

QStaticPictureGenDlg::~QStaticPictureGenDlg()
{
    if(pScene)
    {
        delete pScene;
        pScene=NULL;
    }
    delete ui;
}

void QStaticPictureGenDlg::on_m_trasparantcheck_clicked() //���͸��ѡ���
{
    if(!pOldItem )
        return;

    if(pOldItem)
    {
        int nKey = pOldItem->data(GROUP_TYPE_KEY).toInt();
        if(nKey == LIBRARY_LIB_GROUP)
            return;
    }

    bool nFlag = ui->m_trasparantcheck->checkState();

    QPixmap picture = QPixmap(sPath);
    if (!picture)
    {
        ui->m_trasparantcheck->setChecked(false);
       return ;
    }
    QPixmap newimage = picture.scaled(QSize(100,86));
    pScene->clear();

    if(nFlag)
    {
        ui->label_2->setVisible(true);
        ui->m_transparantbtn->setVisible(true);
        //pTransparantColor->setVisible(true);

        newimage = this->TransparentPic(newimage);
    }
    else
    {
        ui->label_2->setVisible(false);
        ui->m_transparantbtn->setVisible(false);
       // pTransparantColor->setVisible(false);
    }

    //newimage = this->TransparentPic(newimage);
    picture = this->TransparentPic(picture);
    pScene->addPixmap(newimage);
    pScene->update();
   // pPixmap ->setPixmap(newimage);
    pPixmap = new QPixmapItem(picture,newimage.size());
    pOldItem = pPixmap;
}


void QStaticPictureGenDlg::InitParament()        //��ʼ������
{

    ui->m_trasparantcheck->setChecked(false);           //����͸��ѡ��Ϊ��ѡ��
    ui->label_2->setVisible(false);
    ui->m_transparantbtn->setVisible(false);
    ui->m_trasparantcheck->setVisible(false);

    ui->m_noedit->setText(pwnd->GetControlNO("ST"));
    nSelectType = 0;
    sPath = "";
    ui->m_sysradio->setChecked(true);                   //Ĭ�ϴ�ϵͳ��ѡ��ͼƬ
    ui->m_transparantbtn->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
}
void QStaticPictureGenDlg::on_m_pathbtn_clicked()   //ѡ��ͼƬ��ť
{
    QString sName = "";
    QPointF pos;
    if(pOldItem)
        pos = pOldItem->sceneBoundingRect().topLeft();
    if(nSelectType == 1)  //���ļ���ѡ��ͼƬ
    {
        QString filename=QFileDialog::getOpenFileName(this,
                tr("Open File"),pwnd->picturePath,
                tr("Images (*.png *.jpg *.bmp)"));
        QPixmap picture = QPixmap(filename);
        if (!picture)
        {
           return ;
        }
        pwnd->picturePath=filename;

        ui->m_trasparantcheck->setVisible(true);
        QPixmap newimage = picture.scaled(QSize(100,86));

        sPath = filename;  //��·��
        ui->m_pathedit->setText(filename);            //��������
        sName = this->GetPicName(filename);
        ui->m_pathedit->setText(sName);

        pScene->clear();
        //newimage = this->TransparentPic(newimage);
        //pScene->addPixmap(newimage);
        picture = this->TransparentPic(picture);
        pScene->addPixmap(newimage);
        pScene->update();

        pPixmap = new QPixmapItem(picture,newimage.size());
        pOldItem = pPixmap;
        pOldItem->setPos(pos-pOldItem->boundingRect().topLeft());
    }
    else if(nSelectType == 0)
    {
        ui->m_trasparantcheck->setVisible(false);
        ui->label_2->setVisible(false);
        ui->m_transparantbtn->setVisible(false);
        //pTransparantColor->setVisible(false);

        OpenLibrary *pDlg = new OpenLibrary(this);
        if(pDlg->exec() == QDialog::Accepted)
        {
            DrawItemToScene GroupFunction;
            QGraphicsItem* pLibItem = NULL;
            GroupFunction.CopyItem(&pLibItem,pDlg->pCopyItem);

//            pLibItem->setData(GROUP_TYPE_KEY,QVariant(LIBRARY_LIB_GROUP)); //����ͼ���Keyֵ
            QGroupItem *pBaseItem = new QGroupItem(pLibItem);
            pBaseItem->SetWidth(100);
            pBaseItem->SetHeigth(100);

            pScene->clear();
            pScene->addItem(pLibItem);

            QString sCountent = "";
            sPath = sCountent; //���ͼƬ��ַ
            QStringList sList = pLibItem->data(GROUP_DATALIST_KEY).toStringList();
            if(!sList.isEmpty())
                sCountent = sList.at(0);
           // sPath = sCountent; //���ͼƬ��ַ

            sList = sCountent.split("-", QString::SkipEmptyParts);
            if(sList.size() == 3)
                sName = QString("element%1").arg(sList.at(1));//tr("element")
            ui->m_pathedit->setText(sName);            //��������
            pOldItem = pLibItem;
            pLibItem->setPos(pos-pOldItem->boundingRect().topLeft());
        }
        pDlg->deleteLater();
        pDlg = NULL;
    }
}

void QStaticPictureGenDlg::on_m_sysradio_clicked() //ϵͳѡ��
{
    nSelectType = 0;
}

void QStaticPictureGenDlg::on_m_fileradio_clicked()//���ļ�ѡ��
{
    nSelectType = 1;
}

QString QStaticPictureGenDlg::GetPicName(QString sPath)
{
    QString sName = "";
    if(sPath == "")
        return sName;

    QStringList sList = sPath.split("/", QString::SkipEmptyParts);
    sName = sList.at(sList.size() - 1);
    return sName;
}

QPixmap QStaticPictureGenDlg::TransparentPic(QPixmap pPic)
{
    if(ui->m_trasparantcheck->checkState())
    {
        QBitmap bmp=pPic.createMaskFromColor(ui->m_transparantbtn->palette().background().color(),Qt::MaskInColor);
        pPic.setMask(bmp); //���ô�����mask
    }
    return pPic;
}

void QStaticPictureGenDlg::OnDoubleClickOpenInit(QGraphicsItem *pItem) //˫���򿪳�ʼ��
{
    QString str = "";
    pScene->update();

    if(sDataList.empty())
        return;

    sDataList = pItem->data(GROUP_DATALIST_KEY).toStringList();
    ui->m_noedit->setText(sDataList.at(19));  //ȡ���
    str = sDataList.at(1);
    if(str == tr("1"))
        ui->m_trasparantcheck->setChecked(true); //�����Ƿ�͸��
    else if(str == tr("0"))
        ui->m_trasparantcheck->setChecked(false);

    ui->m_transparantbtn->setStyleSheet(QString("background:%1").arg(pwnd->StringTOColor(sDataList.at(2)).name()));

    str = sDataList.at(3);   //����ͼƬ��Դ
    nSelectType = str.toInt();
    if(nSelectType == 0)
        ui->m_sysradio->setChecked(true);
    else
        ui->m_fileradio->setChecked(true);

    str = sDataList.at(4);  //����ͼƬ����
    sPath = str;
    str = this->GetPicName(str);
    ui->m_pathedit->setText(str);

    if(sPath != "")//if(nSelectType == 1)
    {
        QPixmap picture = QPixmap(sPath);
        pPixmap = new QPixmapItem(picture,picture.size());
        pOldItem = pPixmap;
        on_m_trasparantcheck_clicked();
    }
    else //else if(nSelectType == 0)
    {
        DrawItemToScene GroupFunction;
        GroupFunction.CopyItem(&pOldItem,pItem);

        //pOldItem = pwnd->IsHaveLibraryItem(pItem);
        if(pOldItem)
        {
            QGroupItem *pBaseItem = new QGroupItem(pOldItem);
            pBaseItem->SetWidth(100);
            pBaseItem->SetHeigth(100);
            pScene->clear();
            pScene->addItem(pOldItem);
            QPointF pos = pOldItem->boundingRect().topLeft();
            pOldItem->setPos(0-pos.x(),0-pos.y());
           // ui->m_pathedit->setText(GetLibItemName(sPath));
        }
        ui->m_trasparantcheck->setChecked(false);           //����͸��ѡ��Ϊ��ѡ��
        ui->label_2->setVisible(false);
        ui->m_transparantbtn->setVisible(false);
        ui->m_trasparantcheck->setVisible(false);
    }
}

void QStaticPictureGenDlg::OnSaveProperty()
{
    QString str = "";
    bool flag;
    sDataList.clear();
    str = ui->m_noedit->text();  //���� 0
    sDataList.append(str);

    flag = ui->m_trasparantcheck->checkState(); //�Ƿ�͸�� 1
    if(flag)
        sDataList.append(tr("1"));
    else
        sDataList.append(tr("0"));

    str.clear();
    str=pwnd->ColorTOString(ui->m_transparantbtn->palette().background().color());//�߿�ɫ
    sDataList.append(str);

    str = QString("%1").arg(nSelectType); //��ͼƬ��Դ3
    sDataList.append(str);

    sDataList.append(sPath);   //��ͼƬ·��4


    for(int i = 5; i <= 30;i++)   //����
        sDataList.append(tr(""));

    sDataList.replace(19,ui->m_noedit->text());

}

QString QStaticPictureGenDlg::GetLibItemName(QString str)
{
    QString sName = "";
    if(str.isEmpty())
        return sName;

    QStringList sList = str.split("-", QString::SkipEmptyParts);
    if(sList.size() != 3)
        return sName;

    sName = QString("element%1").arg(sList.at(1));
    return sName;
}


void QStaticPictureGenDlg::on_m_transparantbtn_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->m_transparantbtn ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setAlphaColor(const QColor &)));

}
void QStaticPictureGenDlg::setAlphaColor(const QColor & mColor)       //���ñ߿�ɫ
{
    ui->m_transparantbtn->setStyleSheet(QString("background:%1").arg(mColor.name()));
 //   pBarRect->SetBackColor(mColor);      //������������
    if(!pOldItem )
        return;

    if(pOldItem)
    {
        int nKey = pOldItem->data(GROUP_TYPE_KEY).toInt();
        if(nKey == LIBRARY_LIB_GROUP)
            return;
    }

    QPixmap picture = QPixmap(sPath);
    if (!picture)
    {
       return ;
    }
    QPixmap newimage = picture.scaled(QSize(100,86));

    pScene->clear();
    //newimage = this->TransparentPic(newimage);
    picture = this->TransparentPic(picture);
    pScene->addPixmap(newimage);
    pScene->update();
    //pPixmap ->setPixmap(newimage);
    pPixmap = new QPixmapItem(picture,newimage.size());
    pOldItem = pPixmap;
}
