#include "qtimergendlg.h"


#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QTimerGenDlg::QTimerGenDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QTimerGenDlg)
{
    ui->setupUi(this);
    pCopyItem = NULL;
    pScene = new QGraphicsScene(this);     //������
    ui->MainView->setScene(pScene);
    sMarcoName.clear();
}

QTimerGenDlg::~QTimerGenDlg()
{
    if(pScene)
    {
        delete pScene;
        pScene=NULL;
    }
     delete ui;
}

void QTimerGenDlg::LoadTimerShape()
{
    QFile file("shape.sk");
    if(!file.open(QIODevice::ReadOnly))
        return ;
    QDataStream openData(&file);
    SamDrawScene *pSvene = NULL;
    QVector <SamDrawScene *> vScene;  //�滭�������
    vScene.clear();
    int sceneSize = 0;
    openData >> sceneSize;
    int i = 0;
    for(i =0; i< sceneSize; i++)
    {
        pSvene = new SamDrawScene();
        openData >> pSvene;
        vScene.push_back(pSvene);
    }
    file.close();

    QPainterPath path;
    //ɨ�����ͼ��
    path.addRect(0,0,vScene.at(3)->width(),vScene.at(3)->height());
    vScene.at(3)->setSelectionArea(path);
    QList<QGraphicsItem *> item_list=vScene.at(3)->selectedItems();
    DrawItemToScene GroupFunction;
    GroupFunction.CopyItem(&pCopyItem,item_list.at(0));
    pScene->clear();
    pScene->addItem(pCopyItem);
    for(i =0; i< sceneSize; i++)
        delete vScene[i];
    vScene.clear();
}

void QTimerGenDlg::InitParament()
{
    ui->m_Noedit->setText(pwnd->GetControlNO("T"));//���
    on_comboBox_currentIndexChanged(0);//��ʼ��ʼ��ִ��
    on_comboBox_2_currentIndexChanged(0);//��ʼ��ִ�к�ָ��
    ui->m_numcountedit->setValue(0);//ִ�д���
    LoadTimerShape(); //����ͼ��
}

void QTimerGenDlg::on_comboBox_currentIndexChanged(int index)//���Ʒ�ʽ
{
    if(index == 0) //ʼ��ִ��
    {
        ui->m_addrlable->setVisible(false);
        ui->m_addredit->setVisible(false);
        ui->m_addrbtn->setVisible(false);
        ui->label_warning->setText(tr("ע�⣺��ִ�д���Ϊ0�����ʾ��ָ��\nһֱִ��"));
    }
    else if(index == 1)//��ַ����
    {
        ui->m_addrlable->setVisible(true);
        ui->m_addredit->setVisible(true);
        ui->m_addrbtn->setVisible(true);
        ui->label_warning->setText(tr("ע�⣺��ִ�д���Ϊ0�����㴥��������\n���ʾ��ָ��һֱִ��"));
    }
}

void QTimerGenDlg::on_m_addrbtn_clicked()//������ַ
{
    pwnd->Addr_Type=0;
    AddressInputDialog  dlg_triggered(BitAddr,this);
    dlg_triggered.exec();
    ui->m_addredit->setText(BitAddr.sShowAddr);
}

void QTimerGenDlg::on_comboBox_2_currentIndexChanged(int index)//��������
{
    ui->m_namecmb->clear();
    switch(index)
    {
    case 0://ִ�к�ָ��
        if(!sMarcoName.isEmpty())
           ui->m_namecmb->addItems(sMarcoName);
        break;
    default:
        break;
    }
}

void QTimerGenDlg::GeneralSave(QStringList *datalist)
{
    QString sTmp;
    int nTmp = 0;

    datalist->replace(19,ui->m_Noedit->text()); //���

    nTmp = ui->comboBox->currentIndex();//���Ʒ�ʽ
    sTmp = QString::number(nTmp);
    datalist->append(sTmp);// 20

    sTmp=pwnd->KeyboardToString(BitAddr);//������ַ
    datalist->append(sTmp);// 21

    nTmp = ui->spinBox->value();//ִ��Ƶ��
    sTmp = QString::number(nTmp);
    datalist->append(sTmp);// 22

    nTmp = ui->m_numcountedit->value(); //ִ�д���
    sTmp = QString::number(nTmp);
    datalist->append(sTmp);// 23

    nTmp = ui->comboBox_2->currentIndex();//��������
    sTmp = QString::number(nTmp);
    datalist->append(sTmp);// 24

    sTmp = ui->m_namecmb->currentText(); //��������
    datalist->append(sTmp);// 25
}

void QTimerGenDlg::DoubleClickInit(QGraphicsItem *pItem)
{
    DrawItemToScene GroupFunction;
    QStringList pdataList;
    int val = 20;
    QString sTmp = "";
    if(pItem)   //��Data �� stringList�л�ȡ���Բ�����
    {
        GroupFunction.CopyItem(&pCopyItem,pItem);
        pdataList = pCopyItem->data(GROUP_DATALIST_KEY).toStringList();

        pScene->addItem(pCopyItem);

        sTmp = pdataList.at(19);//���
        ui->m_Noedit->setText(sTmp);

        sTmp = pdataList.at(val);//���Ʒ�ʽ
        ui->comboBox->setCurrentIndex(sTmp.toInt());
        on_comboBox_currentIndexChanged(sTmp.toInt());

        sTmp = pdataList.at(val+1);//������ַ
        pwnd->StringToKeyboard(BitAddr,sTmp);
        ui->m_addredit->setText(BitAddr.sShowAddr);

        sTmp = pdataList.at(val+2);//ִ��Ƶ��
        ui->spinBox->setValue(sTmp.toInt());

        sTmp = pdataList.at(val+3);//ִ�д���
        ui->m_numcountedit->setValue(sTmp.toInt());

        sTmp = pdataList.at(val+4);//��������
        ui->comboBox_2->setCurrentIndex(sTmp.toInt());
        on_comboBox_2_currentIndexChanged(sTmp.toInt());

        sTmp = pdataList.at(val+5);//��������
        int nIndex = ui->m_namecmb->findText(sTmp);
        ui->m_namecmb->setCurrentIndex(nIndex);
    }
}
