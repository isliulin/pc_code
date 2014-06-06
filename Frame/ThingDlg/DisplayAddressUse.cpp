#include "DisplayAddressUse.h"
#include "ui_DisplayAddressUse.h"
#include "addrchangedlg.h"

#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

DisplayAddressUse::DisplayAddressUse(QWidget *parent) :QDialog(parent),ui(new Ui::DisplayAddressUse)
{
    ui->setupUi(this);
    QString str = "";

    //setFixedSize(size());
    this->setWindowTitle(tr("��ַʹ��һ����"));

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    pwnd->vAddrMsg.clear();
    pwnd->OnFillAddressMsgClass();        //����ַ��Ϣ

    ui->m_radio1->setChecked(true);
    ui->m_sheetcmb->setVisible(false);
    int totalSceneNum = pwnd->pSceneSheet.size();
    for(int i = 0; i < totalSceneNum;i++)
    {
        str = pwnd->pSceneSheet[i]->sNewScreenName;//��������
        ui->m_sheetcmb->addItem(str);
    }
    ui->m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);//List�ؼ������Ա༭


    nSelctType = 0;

    InitTable();

    qDebug() << "fourth\n";
}

DisplayAddressUse::~DisplayAddressUse()
{
    delete ui;
}

void DisplayAddressUse::InitTable()
{
    QGraphicsItem *pItem;
    int nCount = 0;
    int i = 0;
    int j = 0;
    int nIndex = 0;
    QString sAddr = "";
    QString sScreenName = "";
    QString sAddrUse = "";
    int nRow = 0;
    QString str = "";
    //bool nFlag = true;
    int temp;
    int addrCount = 0;

    ui->m_table->setColumnCount(3);
    ui->m_table->setRowCount(0);
    ui->m_table->setColumnWidth(0,180);
    ui->m_table->setColumnWidth(1,270);
    ui->m_table->setColumnWidth(2,180);
    pwnd->mapMsgOutPutItem.clear();
    nCount = pwnd->vAddrMsg.size();//����
    ui->m_table->clear();
    QStringList header;
    header.append(tr("��������"));
    header.append(tr("�ؼ�����"));
    header.append(tr("���õ�ַ"));
    ui->m_table->setHorizontalHeaderLabels(header);

    if(1 == nSelctType)
    {
        str = ui->m_sheetcmb->currentText();  //��û�������
    }

    qDebug() << "first\n";
    for(int m = 0; m < nCount; m++)
    {
        pItem       = pwnd->vAddrMsg.at(m)->pItem;
        temp        = pwnd->vAddrMsg.at(m)->Address.size();
        sScreenName = "";
        if(pItem)//�ؼ���ַ
        {
            nIndex      = pwnd->vAddrMsg.at(m)->nSheetIndex;//�������
            sScreenName = pwnd->pSceneSheet[nIndex]->sNewScreenName;//��������
        }

        switch(nSelctType)
        {
            case 0:
            {
                addrCount += temp;
            }
            break;

            case 1:
            {
                if(str == sScreenName)
                {
                    addrCount += temp;
                }
            }
            break;

            default:
            QMessageBox::about(this, tr("waring"), tr("error"));
            break;
        }
    }
    ui->m_table->setRowCount(addrCount);

    qDebug() << "second\n";
    for(i = 0; i < nCount; i++)
    {
        pItem       = pwnd->vAddrMsg.at(i)->pItem;
        temp        = pwnd->vAddrMsg.at(i)->Address.size();
        if(pItem)//�ؼ���ַ
        {
            nIndex      = pwnd->vAddrMsg.at(i)->nSheetIndex; //�������
            sScreenName = pwnd->pSceneSheet[nIndex]->sNewScreenName;//��������
        }
        else
        {
            sScreenName = tr("���̹����� ");
        }

        switch(nSelctType)
        {
            case 0:
            {
                for(j = 0; j < temp; j++)
                {
                    sAddrUse = pwnd->vAddrMsg.at(i)->Address[j].str;
                    sAddr    = pwnd->vAddrMsg.at(i)->Address[j].pAddr->sShowAddr;//ȡ��ַ
                    ui->m_table->setItem(nRow,0,new QTableWidgetItem(sScreenName)); //��������
                    ui->m_table->setItem(nRow,1,new QTableWidgetItem(sAddrUse)); //�ؼ�����
                    ui->m_table->setItem(nRow,2,new QTableWidgetItem(sAddr)); //��ַ

                    pwnd->pMsgOutPut = new MsgOutPut ;//��Ϣ�������˫��Ҫ�������
                    pwnd->pMsgOutPut->pItem = pItem;
                    pwnd->pMsgOutPut->nSheetIndex = nIndex;
                    pwnd->mapMsgOutPutItem.insert(nRow,pwnd->pMsgOutPut);

                    nRow++;
                }
            }
            break;

            case 1:
            {
                if(str == sScreenName)
                {
                    for(j = 0; j < temp; j++)
                    {
                        sAddrUse = pwnd->vAddrMsg.at(i)->Address[j].str;
                        sAddr    = pwnd->vAddrMsg.at(i)->Address[j].pAddr->sShowAddr;//ȡ��ַ
                        //ui->m_table->setRowHeight(nRow,20);
                        ui->m_table->setItem(nRow,0,new QTableWidgetItem(sScreenName)); //��������
                        ui->m_table->setItem(nRow,1,new QTableWidgetItem(sAddrUse)); //�ؼ�����
                        ui->m_table->setItem(nRow,2,new QTableWidgetItem(sAddr)); //��ַ

                        pwnd->pMsgOutPut = new MsgOutPut ;//��Ϣ�������˫��Ҫ�������
                        pwnd->pMsgOutPut->pItem = pItem;
                        pwnd->pMsgOutPut->nSheetIndex = nIndex;
                        pwnd->mapMsgOutPutItem.insert(nRow, pwnd->pMsgOutPut);
                        nRow++;
                    }
                }
            }
            break;

            default:
            QMessageBox::about(this, tr("waring"), tr("error"));
            break;
        }
    }
    qDebug() << "third\n";
    /*for(i = 0; i < nCount; i++)
    {
        pItem = pwnd->vAddrMsg.at(i)->pItem;

        temp = pwnd->vAddrMsg.at(i)->Address.size();
        for(j = 0; j < temp; j++)
        {
            nIndex = pwnd->vAddrMsg.at(i)->nSheetIndex; //�������
            sAddr = pwnd->vAddrMsg.at(i)->Address[j].pAddr->sShowAddr;//ȡ��ַ

            if(nSelctType == 0) //��ʾȫ������
            {
                if(sAddr.isEmpty())
                {
                    nFlag = false;
                }
                else
                {
                    nFlag = true;
                }
            }
            else if(nSelctType == 1)//��ʾָ������
            {
                str = ui->m_sheetcmb->currentText();  //��û�������
                sScreenName = pwnd->pSceneSheet[nIndex]->sNewScreenName;//��������
                if(str == sScreenName && !sAddr.isEmpty())
                {
                    nFlag = true;
                }
                else
                {
                    nFlag = false;
                }
            }
            if(nFlag)//!sAddr.isEmpty()
            {
                sAddrUse = pwnd->vAddrMsg.at(i)->Address[j].str;//.sAddrName;
                if(pItem)//�ǿؼ��ĵ�ַ
                {
                    sScreenName = pwnd->pSceneSheet[nIndex]->sNewScreenName;//��������
                }
                else     //�ǹ��̹������е�ַ
                {
                    sScreenName=tr("���̹����� "); //�����Ϣ
                }

                //ui->m_table->insertRow(nRow);
                ui->m_table->setRowHeight(nRow,20);
                ui->m_table->setItem(nRow,0,new QTableWidgetItem(sScreenName)); //��������
                ui->m_table->setItem(nRow,1,new QTableWidgetItem(sAddrUse)); //��������
                ui->m_table->setItem(nRow,2,new QTableWidgetItem(sAddr)); //��������
                nRow++;

                pwnd->pMsgOutPut = new MsgOutPut ;//��Ϣ�������˫��Ҫ�������
                pwnd->pMsgOutPut->pItem = pItem;
                pwnd->pMsgOutPut->nSheetIndex = nIndex;
                pwnd->vMsgOutPutItem.append(pwnd->pMsgOutPut);
            }
        }//end  the second for
    }//end  the first for*/
}

void DisplayAddressUse::on_m_radio1_clicked()
{
    nSelctType = 0;
    InitTable();
    ui->m_sheetcmb->setVisible(false);
}

void DisplayAddressUse::on_m_radio2_clicked()//��ʾָ������
{
    nSelctType = 1;
    InitTable();
    ui->m_sheetcmb->setVisible(true);
}

void DisplayAddressUse::on_m_sheetcmb_currentIndexChanged(QString )
{
    nSelctType = 1;
    InitTable();
}

void DisplayAddressUse::on_m_table_cellDoubleClicked(int row, int column)
{
    QTableWidgetItem *mItem;         //���������Ϊѡ��״̬
    mItem = ui->m_table->item(row,column); //0

    if(mItem) //!str.isEmpty()
    {
        QMap<int, MsgOutPut*>::const_iterator itor = pwnd->mapMsgOutPutItem.find(row);
        if(itor != pwnd->mapMsgOutPutItem.end() && itor.value()->pItem)
        {
            pwnd->nActiveSheetIndex = itor.value()->nSheetIndex;
            pwnd->pView->setScene(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]);
            pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->clearSelection();//�������ѡ��
            itor.value()->pItem->setSelected(true);
        }
    }

    //int num = totalAddrCount();
    //if(row >= num)
    //{
    //    return;//error
    //}

    int numItem = pwnd->vAddrMsg.size();
    int curNum  = 0;
    AddrMsg* pAMsg;
    ADDRPRO  pro;
    int      temp;

    if(1 == nSelctType)
    {
        QGraphicsItem *pItem;
        int nIndex = 0;
        QMap<int,MsgOutPut*>::const_iterator itor = pwnd->mapMsgOutPutItem.find(row);
        if(itor != pwnd->mapMsgOutPutItem.end() && itor.value()->pItem)
        {
            pItem  = itor.value()->pItem;
            nIndex = itor.value()->nSheetIndex;//�������
        }
        for(int i = 0; i < numItem; i++)
        {
            if(nIndex == pwnd->vAddrMsg[i]->nSheetIndex)
            {
                temp = curNum;
                curNum += pwnd->vAddrMsg[i]->Address.size();
                if(row < curNum)
                {
                    pAMsg = pwnd->vAddrMsg[i];
                    pro   = pwnd->vAddrMsg[i]->Address[row - temp];
                    break;
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < numItem; i++)
        {
            temp = curNum;
            curNum += pwnd->vAddrMsg[i]->Address.size();
            if(row < curNum)
            {
                pAMsg = pwnd->vAddrMsg[i];
                pro   = pwnd->vAddrMsg[i]->Address[row - temp];
                break;
            }
        }
    }

    addrChangeDlg dlg(pAMsg, row - temp);
    //������ȷ�����޸ĵ�ַ����ʾ��ĵ�ַ
    short    replaceType;//���ַ�ʽ�滻
    short    type;       //Ҫ�滻������
    QString  replaceAddr;//�滻��ַ
    QString  oldAddr = pAMsg->Address[row - temp].pAddr->sShowAddr;//�ϵ�ַ�ַ���
    Keyboard key;
    int      screenId = pAMsg->nSheetIndex;//�������
    if(dlg.exec() == QDialog::Accepted)
    {
        replaceType = dlg.replaceType;
        type        = dlg.type;
        replaceAddr = dlg.replaceAddr;
        key         = dlg.key;

        if(oldAddr == replaceAddr)//��ַû�б��
        {
            return;
        }

        if(0 == replaceType)
        {
            *(pAMsg->Address[row - temp].pAddr) = key;
            if(pAMsg->Address[row - temp].nRecipe > 0)
            {
                int k = pAMsg->Address[row - temp].nRecipe;
                if(k <= pwnd->m_pSamSysParame->m_qvcRecipe.size())
                {
                     pwnd->m_pSamSysParame->m_qvcRecipe[k-1].bContniu = false;//��Ϊ������
                }
            }
        }
        else if(1 == replaceType)
        {
            for(int i = temp; i < curNum; i++)
            {
                if(oldAddr == pAMsg->Address[i - temp].pAddr->sShowAddr && type == pAMsg->Address[i - temp].pAddr->nAddrType)
                {
                    *(pAMsg->Address[i - temp].pAddr) = key;
                    if(pAMsg->Address[i - temp].nRecipe > 0)
                    {
                        int k = pAMsg->Address[i - temp].nRecipe;
                        if(k <= pwnd->m_pSamSysParame->m_qvcRecipe.size())
                        {
                             pwnd->m_pSamSysParame->m_qvcRecipe[k-1].bContniu = false;//��Ϊ������
                        }
                    }
                }
            }
        }
        else if(2 == replaceType)//��������
        {
            int itemNum = pwnd->vAddrMsg.size();
            for(int i = 0; i < itemNum; i++)
            {
                int addrNum = pwnd->vAddrMsg[i]->Address.size();
                if(screenId == pwnd->vAddrMsg[i]->nSheetIndex)
                {
                    for(int j = 0; j < addrNum; j++)
                    {
                        if((oldAddr == pwnd->vAddrMsg[i]->Address[j].pAddr->sShowAddr) && (type == pwnd->vAddrMsg[i]->Address[j].pAddr->nAddrType))
                        {
                            *(pwnd->vAddrMsg[i]->Address[j].pAddr) = key;
                            if(pwnd->vAddrMsg[i]->Address[j].nRecipe > 0)
                            {
                                int k = pwnd->vAddrMsg[i]->Address[j].nRecipe;
                                if(k <= pwnd->m_pSamSysParame->m_qvcRecipe.size())
                                {
                                     pwnd->m_pSamSysParame->m_qvcRecipe[k-1].bContniu = false;//��Ϊ������
                                }
                            }
                        }
                    }
                }
            }
        }
        else if(3 == replaceType)//��������
        {
            int itemNum = pwnd->vAddrMsg.size();
            for(int i = 0; i < itemNum; i++)
            {
                int addrNum = pwnd->vAddrMsg[i]->Address.size();
                for(int j = 0; j < addrNum; j++)
                {
                    if(oldAddr == pwnd->vAddrMsg[i]->Address[j].pAddr->sShowAddr && type == pwnd->vAddrMsg[i]->Address[j].pAddr->nAddrType)
                    {
                        *(pwnd->vAddrMsg[i]->Address[j].pAddr) = key;
                        if(pwnd->vAddrMsg[i]->Address[j].nRecipe > 0)
                        {
                            int k = pwnd->vAddrMsg[i]->Address[j].nRecipe;
                            if(k <= pwnd->m_pSamSysParame->m_qvcRecipe.size())
                            {
                                 pwnd->m_pSamSysParame->m_qvcRecipe[k-1].bContniu = false;//��Ϊ������
                            }
                        }
                    }
                }
            }
        }

        InitTable();
    }
}

int DisplayAddressUse::totalAddrCount()
{
    int numItem = pwnd->vAddrMsg.size();
    int total = 0;

    for(int i = 0; i < numItem; i++)
    {
        total += pwnd->vAddrMsg[i]->Address.size();
    }

    return total;
}
