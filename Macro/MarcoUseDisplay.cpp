#include "MarcoUseDisplay.h"
#include "ui_MarcoUseDisplay.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

MarcoUseDisplay::MarcoUseDisplay(QWidget *parent):QDialog(parent),ui(new Ui::MarcoUseDisplay)
{
    ui->setupUi(this);

    setFixedSize(size());

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    QString str = "";
    ui->m_radio1->setChecked(true);
    ui->m_sheetcmb->setVisible(false);
    int totalSceneNum = pwnd->pSceneSheet.size();
    for(int i = 0; i < totalSceneNum;i++)
    {
        str = pwnd->pSceneSheet[i]->sNewScreenName ;//��������
        ui->m_sheetcmb->addItem(str);
    }
    ui->m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);//List�ؼ������Ա༭

    pwnd->findScreenAllMarco(mVecStr);//����ַ��Ϣ
    nSelctType = 0;
    InitTable();
}

MarcoUseDisplay::~MarcoUseDisplay()
{
    delete ui;
}

void MarcoUseDisplay::InitTable()
{
    QGraphicsItem *pItem;
    int     nCount = 0;
    int     nRow   = 0;
    bool    nFlag  = true;
    QString str    = "";
    int     nIndex = 0;

    ui->m_table->setColumnCount(3);
    ui->m_table->setRowCount(0);
    ui->m_table->setColumnWidth(0,230);
    ui->m_table->setColumnWidth(1,200);
    ui->m_table->setColumnWidth(2,200);
    pwnd->mapMsgOutPutItem.clear();
    nCount = mVecStr.size();//����
    ui->m_table->clear();

    QStringList header;
    header.append(tr("��������"));
    header.append(tr("�ؼ�����"));
    header.append(tr("�ű�����"));
    ui->m_table->setHorizontalHeaderLabels(header);

    for(int i = 0; i < nCount; i++)
    {
        if(nSelctType == 1) //��ʾָ������
        {
            str = ui->m_sheetcmb->currentText();//��û�������
            if(str != mVecStr[i].sScreenName)
            {
                nFlag = false;
            }
        }

        if(nFlag)
        {
            ui->m_table->insertRow(nRow);
            ui->m_table->setRowHeight(nRow,20);
            ui->m_table->setItem(nRow, 0, new QTableWidgetItem(mVecStr[i].sScreenName + mVecStr[i].sItemName));//��������
            ui->m_table->setItem(nRow, 1, new QTableWidgetItem(mVecStr[i].sLibName));   //�ؼ�����
            ui->m_table->setItem(nRow, 2, new QTableWidgetItem(mVecStr[i].sFunName));      //ʹ�ú�����

            pwnd->pMsgOutPut = new MsgOutPut ;//��Ϣ�������˫��Ҫ�������
            pwnd->pMsgOutPut->pItem = pItem;
            pwnd->pMsgOutPut->nSheetIndex = nIndex;
            pwnd->mapMsgOutPutItem.insert(nRow, pwnd->pMsgOutPut);
            nRow++;
        }

        nFlag = true;
    }
}

void MarcoUseDisplay::on_m_radio1_clicked()
{
    nSelctType = 0;
    InitTable();
    ui->m_sheetcmb->setVisible(false);
}

void MarcoUseDisplay::on_m_radio2_clicked()
{
    nSelctType = 1;
    InitTable();
    ui->m_sheetcmb->setVisible(true);
}

void MarcoUseDisplay::on_m_sheetcmb_currentIndexChanged(QString )
{
    nSelctType = 1;
    InitTable();
}

void MarcoUseDisplay::on_m_table_cellDoubleClicked(int row, int column)
{
    /*QTableWidgetItem *mItem;         //���������Ϊѡ��״̬
    mItem = ui->m_table->item(row,column); //0

    if(mItem) //!str.isEmpty()
    {
        if(pwnd->vMsgOutPutItem.at(row)->pItem)
        {
            pwnd->nActiveSheetIndex = pwnd->vMsgOutPutItem.at(row)->nSheetIndex;
            pwnd->pView->setScene(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]);
            pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->clearSelection();//�������ѡ��
            pwnd->vMsgOutPutItem.at(row)->pItem->setSelected(true);
        }
    }*/
}
