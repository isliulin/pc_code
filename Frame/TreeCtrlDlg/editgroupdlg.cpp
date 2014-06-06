#include "editgroupdlg.h"
#include "ui_editgroupdlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;


EditGroupDlg::EditGroupDlg(int iType,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditGroupDlg)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setFixedSize(size());
    iOpenType = iType; //-1标示新建，大于等于0的数表示打开属性修改
    setWindowTitle(tr("组属性"));
    ui->edit_name->setFocus();

    QRegExp regExp("[0-9A-Za-z_]*");
    QValidator *validator = new QRegExpValidator(regExp, this);

    ui->edit_name->setValidator(validator);
    ui->edit_name->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));


    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止编辑
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一行拉伸
    ui->tableWidget->verticalHeader()->setVisible(false);

    init();
    on_checkBox_clicked(ui->checkBox->isChecked());
}

void EditGroupDlg::init( )
{
    QVector<GroupPermiss> groups;
    QVector<UserPermiss> users;
    QString sName = "";
    groups = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup;
    users = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser;

    //初始化用户组信息
    if(iOpenType == -1) //标示新建用户组
    {
        ui->edit_name->setText("");
        ui->edit_description->setText("");
        ui->checkBox->setChecked(false);
    }
    else if(iOpenType >= 0)//标示打开用户组属性设置对话框
    {
        sName = groups.at(iOpenType).m_strName;
        ui->edit_name->setText(sName);

        sName = groups.at(iOpenType).m_strDescrip;
        ui->edit_description->setText(sName);

        ui->checkBox->setChecked(groups.at(iOpenType).m_bNeedAdmin);

        m_group = groups[iOpenType];
    }

    //初始化用户 列表 ListWidget
    /*for(int i=0; i<users.size(); i++)
    {
        QString text = users[i].m_strName;

        QListWidgetItem *item = new QListWidgetItem(text);
        ui->listWidget->addItem(item);
        item->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        if(iOpenType >= 0)//标示打开用户组属性设置对话框
        {
            int num = m_group.m_vecMember.size();
            bool bIs = false;
            for(int j = 0; j < num; j++)
            {
                if(m_group.m_vecMember.at(j).m_strUser == text)
                {
                    bIs = true;
                }
            }

            if(bIs)
            {
                item->setCheckState(Qt::Checked);
            }
            else
            {
                item->setCheckState(Qt::Unchecked);
            }
        }
        else
        {
            item->setCheckState(Qt::Unchecked);
        }
    }*/

    //初始化用户 列表 TableWidget
    for(int i=0; i < users.size(); i++)
    {
        //int curRow = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(i);

        QString text = users[i].m_strName;
        QTableWidgetItem *tabItem1 = new QTableWidgetItem(text);
        tabItem1->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        ui->tableWidget->setItem(i,0,tabItem1);

        QTableWidgetItem *tabItem2 = new QTableWidgetItem("");
        tabItem2->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        tabItem2->setCheckState(Qt::Unchecked);
        ui->tableWidget->setItem(i,1,tabItem2);

        if(iOpenType >= 0)//标示打开用户组属性设置对话框
        {
            int num = m_group.m_vecMember.size();
            bool bIs = false;
            for(int j = 0; j < num; j++)
            {
                if(m_group.m_vecMember.at(j).m_strUser == text)
                {
                    bIs = true;
                    if(m_group.m_vecMember.at(j).m_bIsAdmin)
                    {
                        tabItem2->setCheckState(Qt::Checked);
                    }
                    else
                    {
                        tabItem2->setCheckState(Qt::Unchecked);
                    }
                }
            }

            if(bIs)
            {
                tabItem1->setCheckState(Qt::Checked);
            }
            else
            {
                tabItem1->setCheckState(Qt::Unchecked);
            }
        }
        else
        {
            tabItem1->setCheckState(Qt::Unchecked);
        }
    }
}

EditGroupDlg::~EditGroupDlg()
{
    delete ui;
}

void EditGroupDlg::on_btn_ok_clicked()
{
    if(!isNameRight())
    {
        return;
    }

    m_group.m_strName = ui->edit_name->text();
    m_group.m_strDescrip = ui->edit_description->text();
    m_group.m_bNeedAdmin = ui->checkBox->isChecked();

    //初始化用户 列表 ListWidget
    /*m_group.m_vecMember.clear();
    for(int i=0; i<ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);

        int num = m_group.m_vecMember.size();
        bool bIs = false;
        for(int j = 0; j < num; j++)
        {
            if(m_group.m_vecMember.at(j).m_strUser == item->text())
            {
                bIs = true;
            }
        }

        if(item && item->checkState() == Qt::Checked && (bIs == false))
        {
            Admin administrator;
            administrator.m_strUser = item->text();
            administrator.m_bIsAdmin = false;
            m_group.m_vecMember << administrator;
        }
    }*/

    //初始化用户 列表 TableWidget
    m_group.m_vecMember.clear();
    for(int i=0; i<ui->tableWidget->rowCount(); i++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i, 0);
        QTableWidgetItem *item1;

        if(item && item->checkState() == Qt::Checked)
        {
            Admin administrator;
            administrator.m_strUser = item->text();

            item1 = ui->tableWidget->item(i, 1);
            if(item1->checkState() == Qt::Checked)
            {
                administrator.m_bIsAdmin = true;
            }
            else
            {
                administrator.m_bIsAdmin = false;
            }
            m_group.m_vecMember << administrator;
        }
    }

    accept();
}

void EditGroupDlg::on_btn_cancel_clicked()
{
    QDialog::close();
}

/***************************************************************
 *函数名称：isNameRight
 *函数功能：判断用户组名称是否重命名
 *参数含义：
 *返回值:       bool
 *编辑作者：郑启红
 *编辑日期：2012.9.17
 **************************************************************/
bool EditGroupDlg::isNameRight()
{
    QString strGroupName = ui->edit_name->text();
    int num = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup.size();

    if(strGroupName.isEmpty())
    {
        ui->edit_name->setFocus();
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("用户组名不能为空"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return false;
    }
    if(strGroupName.contains("\ "))
    {
        ui->edit_name->setFocus();
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("用户组名不能有空格"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return false;
    }

    for(int i = 0; i < num; i++)
    {
        if( i == iOpenType)
            continue;
        if(strGroupName == pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_strName)
        {
            ui->edit_name->setFocus();
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("用户组名重名!"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
            box.exec();
            return false;
        }
    }
    return true;
}


void EditGroupDlg::on_checkBox_clicked(bool checked)
{
    int count = ui->tableWidget->rowCount();
    if(checked)
    {
        ui->tableWidget->setColumnWidth(1, 100);
        ui->tableWidget->setColumnWidth(0, 180);
        for(int i = 0; i < count; i++)
        {

            ui->tableWidget->showColumn(1);
        }
    }
    else
    {
        ui->tableWidget->setColumnWidth(0, 200);
        for(int i = 0; i < count; i++)
        {
            ui->tableWidget->item(i, 1)->setCheckState(Qt::Unchecked);
            ui->tableWidget->hideColumn(1);
        }
    }
}

void EditGroupDlg::on_tableWidget_cellClicked(int row, int column)
{
    QTableWidgetItem *item = ui->tableWidget->item(row, 0);
    QTableWidgetItem *item1 = ui->tableWidget->item(row, 1);

    //if(1 == column)
    {
        if(item->checkState() == Qt::Unchecked)
        {
            item1->setCheckState(Qt::Unchecked);
        }
    }
}
