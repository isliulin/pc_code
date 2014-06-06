#include "qmulticopy.h"
#include "ui_qmulticopy.h"
#include  "Frame\mainwindow.h"
#include <QPointF>
#include "Command/unandrestack.h"
extern  MainWindow *pwnd;
QMultiCopy::QMultiCopy(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::QMultiCopy)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    on_if_Increse_Address_clicked(false);

    R_Alignment_Group = new QButtonGroup(this);
    R_Alignment_Group->addButton(ui->Increse_Right,1);
    R_Alignment_Group->addButton(ui->Increse_Down,2);
    this->setWindowTitle(tr("���ظ���"));
}

QMultiCopy::~QMultiCopy()
{
    delete ui;
}

void QMultiCopy::on_if_Increse_Address_clicked(bool checked)
{
    if(checked)
    {
        ui->Increse_Down->setHidden(false);
        ui->Increse_Right->setHidden(false);
        ui->label_5->setHidden(false);
        ui->Increse_Interval->setHidden(false);
    }
    else
    {
        ui->Increse_Down->setHidden(true);
        ui->Increse_Right->setHidden(true);
        ui->label_5->setHidden(true);
        ui->Increse_Interval->setHidden(true);
    }
}

//ȷ����ť���¼�
void QMultiCopy::on_OK_clicked()
{
    // QPLC_Struct *PLC_P=NULL;
    QList<QGraphicsItem *> selList=pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->selectedItems();
    if(selList.size()!=1)//ѡ��������û��
    {
        accept();
        return;
    }
    else{
        DrawItemToScene CopyFun;

        int nItemWidth=0;
        int nItemHeight=0;
        if(ui->Overlap->isChecked())
        {
            nItemWidth=0;
            nItemHeight=0;
        }
        else
        {
            nItemWidth=selList.at(0)->boundingRect().width();
            nItemHeight=selList.at(0)->boundingRect().height();
        }
        qreal bottom;//��׼�ؼ��ĵױ߽�ֵ
        qreal right;//��׼�ؼ����ұ߽�ֵ
        int nColumn=ui->Column->value();//����
        int nColumn_Interval=ui->Column_Interval->value();//�м��
        int nRow=ui->Row->value();//����
        int nRow_Interval=ui->Row_Interval->value();//�м��

        qreal scence_h=pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sceneRect().height();
        qreal scence_w=pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sceneRect().width();
        QGraphicsItem * pCopyTem = NULL;
        QGraphicsItem * pTem = NULL;
        QList<QGraphicsItem *> addItemsList;
        CopyFun.CopyItem(&pCopyTem,selList.at(0));
        if(R_Alignment_Group->checkedId() == 1)//Ĭ������£�ѡ�е������ҵ���
        {
            for(int j=0;j<nRow;j++)
            {
                for(int i=0;i<nColumn-1;i++)
                {
                    if((pCopyTem->type()==SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)||(pCopyTem->type() ==SAM_DRAW_OBJECT_ARC_NEW))//�ж��Ƿ�ΪԲ�Ǿ��λ�������
                    {
                        right=pCopyTem->sceneBoundingRect().right();
                    }
                    else
                    {
                        right=pCopyTem->boundingRect().right();
                    }
                    qreal item_x=right+(i+1)*(nColumn_Interval+nItemWidth);//����߽�ֵ�Ƿ�Խ��
                    if(item_x>scence_w)//�����ƵĴ�СԽ��Ļ�
                    {//�˳�ѭ��
                        break;
                    }
                    CopyFun.CopyItem(&pTem,pCopyTem);

                    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->addItem(pTem);
                    addItemsList.push_back(pTem);
                    if((pCopyTem->type()==SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)||(pCopyTem->type() ==SAM_DRAW_OBJECT_ARC_NEW))//�ж��Ƿ�ΪԲ�Ǿ��λ�������
                    {
                        pTem->setPos(pTem->sceneBoundingRect().topLeft().x()+(nItemWidth+nColumn_Interval)*(i+1), pTem->sceneBoundingRect().topLeft().y());
                    }
                    else
                    {
                        pTem->setPos((nItemWidth+nColumn_Interval)*(i+1),0);
                    }
                    pTem->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
                    pTem->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
                    pTem=NULL;
                }
                if(j<nRow-1)
                {
                    qreal item_y;
                    // int hight=pCopyTem->sceneBoundingRect().height();
                    if((pCopyTem->type()==SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)||(pCopyTem->type() ==SAM_DRAW_OBJECT_ARC_NEW))//�ж��Ƿ�ΪԲ�Ǿ��λ�������
                    {
                        bottom=pCopyTem->sceneBoundingRect().bottom();
                        item_y=bottom+(nRow_Interval+nItemHeight);//����߽�ֵ�Ƿ�Խ��
                    }
                    else
                    {
                        bottom=pCopyTem->boundingRect().bottom();
                        item_y=bottom+(nRow_Interval+nItemHeight)*(j+1);//����߽�ֵ�Ƿ�Խ��
                    }
                    if(item_y>scence_h)//�����ƵĴ�СԽ��Ļ�
                    {//�˳�ѭ��
                        break;
                    }
                    CopyFun.CopyItem(&pCopyTem,selList.at(0));

                    //MuCopyList(*pCopyTem,CopyCount,NormKeyboardstr);
                    //pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->setNewItem_ID(pCopyTem,NouseItem );
                    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->addItem(pCopyTem);
                    addItemsList.push_back(pCopyTem);
                    if((pCopyTem->type()==SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)||(pCopyTem->type() ==SAM_DRAW_OBJECT_ARC_NEW))//�ж��Ƿ�ΪԲ�Ǿ��λ�������
                    {
                        pCopyTem->setPos(pCopyTem->sceneBoundingRect().topLeft().x(),(nItemHeight+nRow_Interval)*(j+1)+ pCopyTem->sceneBoundingRect().topLeft().y());
                    }
                    else
                    {
                        pCopyTem->setPos(0,(nItemHeight+nRow_Interval)*(j+1));
                    }
                    pCopyTem->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
                    pCopyTem->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
                    //pwnd->AndTreeSubItem(pCopyTem);
                    //pwnd->upDatetreeScreenItem();//���»��������

                }
            }
        }
        else if(R_Alignment_Group->checkedId() == 2)//ѡ�е������µ���
        {
            for(int i=0;i<nColumn;i++)
            {
                for(int j=0;j<nRow-1;j++)
                {
                    if((pCopyTem->type()==SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)||(pCopyTem->type() ==SAM_DRAW_OBJECT_ARC_NEW))//�ж��Ƿ�ΪԲ�Ǿ��λ�������
                    {
                        bottom=pCopyTem->sceneBoundingRect().bottom();
                    }
                    else
                    {
                        bottom=pCopyTem->boundingRect().bottom();
                    }
                    qreal item_y=bottom+(j+1)*(nRow_Interval+nItemHeight);//����߽�ֵ�Ƿ�Խ��
                    // �����ƵĴ�СԽ��Ļ�
                    if(item_y>scence_h) break;

                    CopyFun.CopyItem(&pTem,pCopyTem);

                    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->addItem(pTem);
                    addItemsList.push_back(pTem);
                    if((pCopyTem->type()==SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)||(pCopyTem->type() ==SAM_DRAW_OBJECT_ARC_NEW))//�ж��Ƿ�ΪԲ�Ǿ��λ�������
                    {
                        pTem->setPos(pTem->sceneBoundingRect().topLeft().x(),(nItemHeight+nRow_Interval)*(j+1)+ pTem->sceneBoundingRect().topLeft().y());
                    }
                    else
                    {
                        pTem->setPos(0,(nItemHeight+nRow_Interval)*(j+1));
                    }
                    pTem->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
                    pTem->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
                    pTem=NULL;
                }
                if(i<nColumn-1)
                {
                    qreal item_x;
                    if((pCopyTem->type()==SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)||(pCopyTem->type() ==SAM_DRAW_OBJECT_ARC_NEW))//�ж��Ƿ�ΪԲ�Ǿ��λ�������
                    {
                        right=pCopyTem->sceneBoundingRect().right();
                        item_x=right+(nColumn_Interval+nItemWidth);//����߽�ֵ�Ƿ�Խ��
                    }
                    else
                    {
                        right=pCopyTem->boundingRect().right();
                        item_x=right+(i+1)*(nColumn_Interval+nItemWidth);//����߽�ֵ�Ƿ�Խ��
                    }
                    //�����ƵĴ�СԽ��Ļ�
                    if(item_x>scence_w) break;

                    CopyFun.CopyItem(&pCopyTem,selList.at(0));

                    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->addItem(pCopyTem);
                    addItemsList.push_back(pCopyTem);
                    if((pCopyTem->type()==SAM_DRAW_OBJECT_ROUNDEDRECT_NEW)||(pCopyTem->type() ==SAM_DRAW_OBJECT_ARC_NEW))//�ж��Ƿ�ΪԲ�Ǿ��λ�������
                    {
                        pCopyTem->setPos(pCopyTem->sceneBoundingRect().topLeft().x()+(nItemWidth+nColumn_Interval)*(i+1), pCopyTem->sceneBoundingRect().topLeft().y());
                    }
                    else
                    {
                        pCopyTem->setPos((nItemWidth+nColumn_Interval)*(i+1),0);
                    }

                    pCopyTem->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
                    pCopyTem->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
                }
            }
        }
        if(ui->if_Increse_Address->isChecked())
        {
            //���õ�ַ����
            QList<QGraphicsItem *> itemList = addItemsList;
            qDebug() << "multiCopy size ----"<< itemList.size();

            setMulitAddrs(itemList,selList.at(0));
        }
        pwnd->undoStack->push(new multiCopyCommand(pwnd->pSceneSheet[pwnd->nActiveSheetIndex],addItemsList,selList[0],true));
    }
    pwnd->PreviewWindow();
    accept();
}


//ȡ����ť���¼�
void QMultiCopy::on_cancel_clicked()
{
    reject ();
}
//���ƺ�
void QMultiCopy::MuCopyList(QGraphicsItem &pItem,int &CopyCount,QStringList NormKeyboardstr)
{

    QMessageBox msg(QMessageBox::Warning,PRO_FULL_NAME,tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("ȷ��"),QMessageBox::AcceptRole);

    QLibrary  lib("MultiCopy.dll");
    if (!lib.load())
    {
        msg.setText(tr("MultiCopy.dllδ�ҵ���"));
        msg.exec();
    }
    typedef Keyboard (*ADDPROC)( QStringList *,Keyboard ,int , int *, int *,int );
    ADDPROC muliticopy = NULL;
    muliticopy = (ADDPROC)lib.resolve("Multicpy");
    if (NULL == muliticopy)
    {
        msg.setText(tr("�ļ��������°�װӦ�ó���"));
        msg.exec();
    }
    datalist = qVariantValue<QStringList>(pItem.data(GROUP_DATALIST_KEY));
    QStringList keyboardid=GetKeyboardID(pItem);
    QStringList lFactoryandModel;//�洢���Һ��ͺ�
    for(int i=0;i<NormKeyboardstr.length();i++)
    {
        pwnd->StringToKeyboard(TempKeyboard,NormKeyboardstr.at(i));
        if(TempKeyboard.nConnectType==1)
        {
            if(pwnd->m_pSamSysParame->m_qvcPlcCommunicate.size()>0)
            {
                lFactoryandModel.append(pwnd->m_pSamSysParame->m_qvcPlcCommunicate.at(0).sDiviceType);//����
                lFactoryandModel.append(pwnd->m_pSamSysParame->m_qvcPlcCommunicate.at(0).sDiviceModel);//�ͺ�
            }
            else//���Ӳ�����
            {
                msg.setText(tr("�ÿؼ���ʹ�õ����Ӳ����ڻ��ѱ�ɾ����"));
                msg.exec();
                return;
            }
        }
        else if(TempKeyboard.nConnectType==2)
        {
            if(pwnd->m_pSamSysParame->m_qvcPlcCommunicate.size()>1)
            {
                lFactoryandModel.append(pwnd->m_pSamSysParame->m_qvcPlcCommunicate.at(1).sDiviceType);//����
                lFactoryandModel.append(pwnd->m_pSamSysParame->m_qvcPlcCommunicate.at(1).sDiviceModel);//�ͺ�
            }
            else//���Ӳ�����
            {
                msg.setText(tr("�ÿؼ���ʹ�õ����Ӳ����ڻ��ѱ�ɾ����"));
                msg.exec();
                return;
            }
        }
        else if(TempKeyboard.nConnectType==3)
        {
            if(pwnd->m_pSamSysParame->m_qvcPlcCommunicate.size()>2)
            {
                lFactoryandModel.append(pwnd->m_pSamSysParame->m_qvcPlcCommunicate.at(2).sDiviceType);//����
                lFactoryandModel.append(pwnd->m_pSamSysParame->m_qvcPlcCommunicate.at(2).sDiviceModel);//�ͺ�
            }
            else//���Ӳ�����
            {
                msg.setText(tr("�ÿؼ���ʹ�õ����Ӳ����ڻ��ѱ�ɾ����"));
                msg.exec();
                return;
            }

        }
        Keyboard Getkeyboard=muliticopy(&lFactoryandModel,TempKeyboard,ui->Increse_Interval->value(),&CopyCount,0,0);
        datalist.replace(keyboardid.at(i).toInt(),pwnd->KeyboardToString(Getkeyboard));
        if(NormKeyboardstr.length()-i>1)//Ϊ�˷�ֹ����һ���ؼ��Ķ��Keyboardֵʱ��CopyCount��Ӧ���ۼӼӵ����
        {
            CopyCount--;
        }
    }
    pItem.setData(GROUP_DATALIST_KEY,datalist);

    lib.unload();//�ͷ�dll�ļ�
}
//�õ���׼Keyboard
QStringList QMultiCopy::GetNormKeyboard(QGraphicsItem &pItem)
{
    QStringList NormKeyboardstr;

    return NormKeyboardstr;
}
//���ݱ����Ƶ�itemȡ������ַlist
QList<Keyboard > QMultiCopy::getItemAddrs(QGraphicsItem *pItem)
{
	QList<Keyboard > addrs;
    QItemGroup *itemGroup = NULL;
    switch(pItem->type())
    {
    case SAM_DRAW_OBJECT_GROUP:
        itemGroup = dynamic_cast<QItemGroup *>(pItem);
        if(itemGroup)
        {
            addrs = itemGroup->getAddress();
        }
        break;
    }
	return addrs;

}
QList<QVector<Keyboard> >QMultiCopy::getMultiAddrs(QList<Keyboard> startAddrs,int nInterval,int count)
{
    QList<QVector<Keyboard > >multiAddrs;
    QVector<Keyboard> addrs;

    foreach(Keyboard startAddr,startAddrs)
    {
        //��ַ�Ķ��ظ���
        addrs = startAddr.copyAddrs(nInterval,count);
        multiAddrs << addrs;
    }
    return multiAddrs;
}
//�������ø��ƺ��item��ַ
void QMultiCopy::setItemsAddrs(QList<QGraphicsItem *>items,QList<QVector<Keyboard> >addrs)
{
    //int i =0;
    QItemGroup *itemGroup =NULL;
    int countOfItem = 0;//item����Ҫ���Ƶĵ�ַ��
    int countOfCopy = 0;//���Ƶĸ���

    countOfItem = addrs.size();
    if(countOfItem>0)
    {
        countOfCopy = addrs[0].size();
    }
    //��������
    QList<QList<Keyboard> >allAddrs;
    for(int i=0; i<countOfCopy; i++)
    {
        QList<Keyboard> addrsOfItem;
        for(int j=0; j<countOfItem; j++)
        {
            addrsOfItem << addrs[j][i];
        }
        allAddrs << addrsOfItem;
    }
    int index = 0;
    foreach(QList<Keyboard > addrsOfItem,allAddrs)
    {
        if(items.size()<= index)
            break;

        itemGroup = dynamic_cast<QItemGroup *>(items.at(index));
        index++;

        if(!itemGroup)
            continue;
        itemGroup->setAddress(addrsOfItem);

    }
}
//�õ�Keyboard��datalist�����λ��
QStringList QMultiCopy::GetKeyboardID(QGraphicsItem &pItem)
{
    QStringList Keyboardlist;

    return Keyboardlist;
}
void QMultiCopy::setMulitAddrs(QList<QGraphicsItem *>items,QGraphicsItem *item)
{
    QList<Keyboard> startAddrs = getItemAddrs(item);
    if(startAddrs.isEmpty())
    {
        return;
    }
    QList<QVector<Keyboard > > allAddrs = getMultiAddrs(startAddrs,ui->Increse_Interval->value(),items.size());
    setItemsAddrs(items,allAddrs);
}
