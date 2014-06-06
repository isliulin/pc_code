#include "qrecipedate.h"
#include "ui_qrecipedate.h"
#include "Frame\MainWindow.h"
extern MainWindow *pwnd;


Qrecipedate::Qrecipedate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Qrecipedate)
{
    ui->setupUi(this);
    bInitFlag = false;
    int i = 0;
    ui->m_table->setRowCount(0);
    if(pwnd->m_pSamSysParame->m_recipeProp.bRecipeExist)
    {
        for(int j = 0;j < pwnd->m_pSamSysParame->m_recipeProp.nRecipeTotalNum;j++) //sRowHeadName[0].size()
        {
            int nTmp=pwnd->m_pSamSysParame->m_recipeProp.nRecipeTotalNum;//sRowHeadName[0].size();
            ui->m_table->setRowCount(nTmp);
            QTableWidgetItem *newItem = new QTableWidgetItem(pwnd->m_pSamSysParame->m_recipeProp.sRowHeadName[0][j]);
            ui->m_table->setItem(j,0,newItem);//添加到表格中

            QTableWidgetItem * item=new QTableWidgetItem();
            item->setCheckState(Qt::Checked);
            ui->m_table->setItem(j,1,item);
        }
    }

    QVector<QString> language_vector; //初始化语言下拉框
    for( i=0;i<pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();i++)
    {
        language_vector.push_back(pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i));
    }
    for( i=0;i< pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();i++)
    {
        ui->m_language->addItem(language_vector.at(i));
    }
    ui->m_language->setCurrentIndex(0);

    ui->m_table->verticalHeader()->setHidden(true);
    ui->m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    bInitFlag = true;
}

void Qrecipedate::Init(QGraphicsItem *pItem)//初始化函数
{
    bInitFlag = false;
    if(pItem)
    {
        QStringList datalist = pItem->data(GROUP_DATALIST_KEY).toStringList();
        int index = 100;
        int val = 1;
        int count = datalist.at(28).toInt();//原配方总数pwnd->m_pSamSysParame->m_recipeProp.sRowHeadName[0].size();
        int nNewCount = pwnd->m_pSamSysParame->m_recipeProp.nRecipeTotalNum; //新建配方总数
        if(nNewCount < count)
            count = nNewCount;

        for(int i = 0; i < count;i++)
        {
            QTableWidgetItem * item = ui->m_table->item(i,1);
            val = datalist.at(index).toInt();
            if(val == 0)
                item->setCheckState(Qt::Unchecked);
            else if(val == 1)
                item->setCheckState(Qt::Checked);
            index++;
        }
    }
    bInitFlag = true;
}

Qrecipedate::~Qrecipedate()
{
    delete ui;
}

void Qrecipedate::GeneralSave(QStringList *datalist)
{
    int count = pwnd->m_pSamSysParame->m_recipeProp.nRecipeTotalNum;//sRowHeadName[0].size();
    for(int i = 0; i < count;i++)
    {
        if( ui->m_table->item(i,1)->checkState() == Qt::Unchecked )
        {
            datalist->append("0");
        }
        else if( ui->m_table->item(i,1)->checkState() == Qt::Checked )
        {
            datalist->append("1");
        }
    }
}


void Qrecipedate::on_m_language_currentIndexChanged(int index)
{
    if(!bInitFlag)
        return;

    QString sName = "";
    for(int j = 0;j < pwnd->m_pSamSysParame->m_recipeProp.nRecipeTotalNum;j++) //sRowHeadName[index].size()
    {
        int iLancount = pwnd->m_pSamSysParame->m_recipeProp.sRowHeadName.size();
        if( iLancount < index+1)
            sName = pwnd->m_pSamSysParame->m_recipeProp.sRowHeadName[iLancount-1][j];
        else
            sName = pwnd->m_pSamSysParame->m_recipeProp.sRowHeadName[index][j];

        QTableWidgetItem *newItem = ui->m_table->item(j,0);
        if(newItem)
        {
            newItem->setText(sName);
        }
    }
}
