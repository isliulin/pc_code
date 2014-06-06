#include "qmultistategenelcunstomdlg.h"
#include "headfile/global_types.h"

QMultiStateGenelCunstomDlg::QMultiStateGenelCunstomDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMultiStateGenelCunstomDlg)
{
    ui->setupUi(this);
    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    nCurrentRow=0;
    this->setWindowTitle(tr("自定状态值"));
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->columnWidth(5);
    ui->tableWidget->setCurrentCell(0,1);
    ui->tableWidget->setColumnWidth(0,40);           //设置列宽
    ui->tableWidget->setColumnWidth(1,140);

    ui->pushButton_up->setDisabled(true);
    ui->pushButton_down->setDisabled(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //QValidator *validator = new QIntValidator(0, 65535, this);
    //ui->sData->setValidator(validator);

    connect( ui->tableWidget,SIGNAL(cellClicked(int,int)),this,SLOT(setBtn(int,int)));

}

QMultiStateGenelCunstomDlg::~QMultiStateGenelCunstomDlg()
{
    delete ui;
}//

//
void QMultiStateGenelCunstomDlg::setAllData(QVector<double > values,bool bInit = true)
{
    int rowCount = values.size();
    if(rowCount > 512)
    {
        rowCount = 512;
    }
    ui->tableWidget->setRowCount(rowCount);
    for(int i = 0;i<rowCount;i++)
    {
        QString  sTmp=QString("%1").arg(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(sTmp));

        if(!bInit)
        {
            //sTmp=QString("%1").arg(values[i]);
            sTmp = QString::number(values[i],'g',10);
        }
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(sTmp));
    }
    setBtn(0,1);
}
void QMultiStateGenelCunstomDlg::setAllData(QVector<int > values,bool bInit = true)
{
    int rowCount = values.size();
    if(rowCount > 512)
    {
        rowCount = 512;
    }
    ui->tableWidget->setRowCount(rowCount);
    for(int i = 0;i<rowCount;i++)
    {
        QString  sTmp=QString("%1").arg(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(sTmp));

        if(!bInit)
        {
            sTmp=QString("%1").arg(values[i]);
        }
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(sTmp));
    }
    setBtn(0,1);
}

QVector<double > QMultiStateGenelCunstomDlg::getValues()
{
    QVector<double > vcValues;
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        QTableWidgetItem * item = ui->tableWidget->item(i,1);
        if(item)
        {
            QString string = item->text();
            vcValues << string.toDouble();
        }
    }
    return vcValues;
}

void QMultiStateGenelCunstomDlg::setBtn(int row,int col)
{
    nCurrentRow=row;

    if(col==0)
    {
        ui->pushButton_up->setDisabled(false);
        ui->pushButton_down->setDisabled(false);

        ui->tableWidget->item(row,1)->setBackground(QBrush(QColor(125,0,0)));
        for(int i=0;i<row;i++)
        {
            ui->tableWidget->item(i,1)->setBackground(QBrush(QColor(255,255,255)));
        }
        for(int i=row+1;i<ui->tableWidget->rowCount();i++)
        {
            ui->tableWidget->item(i,1)->setBackground(QBrush(QColor(255,255,255)));
        }

        if(row==ui->tableWidget->rowCount()-1)
        {
            //ui->pushButton_up->setDisabled(true);
            ui->pushButton_down->setDisabled(true);
        }
        if(row==0)
        {
            ui->pushButton_up->setDisabled(true);
        }
     }
    else if(col==1)
    {
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            ui->tableWidget->item(i,1)->setBackground(QBrush(QColor(255,255,255)));
            ui->pushButton_up->setDisabled(true);
            ui->pushButton_down->setDisabled(true);
        }

     }
    ui->sData->setText(ui->tableWidget->item(row,1)->text());
    ui->sData->setFocus();
 }//

void QMultiStateGenelCunstomDlg::on_pushButton_ok_clicked()
{
    allValues.resize(0);
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        QTableWidgetItem * item = ui->tableWidget->item(i,1);
        if(item)
        {
            QString string = item->text();
            allValues << string.toDouble();
        }
    }
    accept();
}

void QMultiStateGenelCunstomDlg::on_pushButton_cancle_clicked()
{
    reject();
}//


//向上移动
void QMultiStateGenelCunstomDlg::on_pushButton_up_clicked()
{

    int index=nCurrentRow;
    index--;
    nCurrentRow--;
    ui->tableWidget->item(index,1)->setBackground(QBrush(QColor(125,0,0)));

    QString nDown=ui->tableWidget->item(index,1)->data(Qt::DisplayRole).toString();
    QString nUp=ui->tableWidget->item(index+1,1)->data(Qt::DisplayRole).toString();
    ui->tableWidget->item(index,1)->setData(Qt::EditRole,nUp);
    ui->tableWidget->item(index+1,1)->setData(Qt::EditRole,nDown);

    for(int i=0;i<index;i++)
    {
        ui->tableWidget->item(i,1)->setBackground(QBrush(QColor(255,255,255)));
    }

    for(int i=index+1;i<ui->tableWidget->rowCount();i++)
    {
        ui->tableWidget->item(i,1)->setBackground(QBrush(QColor(255,255,255)));
    }

    if(nCurrentRow==0)
    {
        ui->pushButton_up->setDisabled(true);
    }

    ui->pushButton_down->setDisabled(false);
}//

//点击下移
void QMultiStateGenelCunstomDlg::on_pushButton_down_clicked()
{
    int index=nCurrentRow;
    index++;
    nCurrentRow++;
    ui->tableWidget->item(index,1)->setBackground(QBrush(QColor(125,0,0)));

    QString nDown=ui->tableWidget->item(index,1)->data(Qt::DisplayRole).toString();
    QString nUp=ui->tableWidget->item(index-1,1)->data(Qt::DisplayRole).toString();
    ui->tableWidget->item(index,1)->setData(Qt::EditRole,nUp);
    ui->tableWidget->item(index-1,1)->setData(Qt::EditRole,nDown);

    for(int i=0;i<index&&i<ui->tableWidget->rowCount();i++)
    {
        ui->tableWidget->item(i,1)->setBackground(QBrush(QColor(255,255,255)));
    }

    if(nCurrentRow==ui->tableWidget->rowCount()-1)
    {
        ui->pushButton_down->setDisabled(true);
    }

    ui->pushButton_up->setDisabled(false);
}//

void QMultiStateGenelCunstomDlg::on_sData_textChanged(QString sString)
{
    if(ui->tableWidget->item(nCurrentRow,1))
    {
      ui->tableWidget->item(nCurrentRow,1)->setText(sString);
    }

}
void QMultiStateGenelCunstomDlg::setRange(int type)
{
    double nMax = 2147483647L;
    double nMin = -2147483648L;
    int decLen = 0;

    switch(type)
    {
    case 0://16位正整数
        nMax = 65535;
        nMin = 0;
        decLen = 0;
        break;
    case 1://32位正整数
        nMax = 4294967295UL;
        nMin = 0;
        decLen = 0;
        break;
    case 2://16位整数
        nMax = 32767;
        nMin = -32768;
         decLen = 0;
        break;
    case 3://32位整数
        nMax = 2147483647L;
        nMin = -2147483648L;
         decLen = 0;
        break;
    case 4://32位浮点数
        nMax = 2147483647L;
        nMin = -2147483648L;
        decLen = 10;
        break;
    default:
         break;
    }
    if (nMin>0)
    {
        nMin = nMin*-1;
    }
    DoubleValidator *validator = new DoubleValidator(nMin,nMax,decLen,this);
    ui->sData->setValidator(validator);
}
