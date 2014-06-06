#include "newuserright.h"
#include "ui_newuserright.h"
#include "editgroupdlg.h"
#include "edituserdlg.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

NewUserRight::NewUserRight(QWidget *parent):QDialog(parent),ui(new Ui::NewUserRight)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setFixedSize(size());
    setWindowTitle(tr("用户权限"));

    init();
}

NewUserRight::~NewUserRight()
{
    delete ui;
}

void NewUserRight::init()
{

    ui->tableWidget_group->setColumnWidth(0, ui->tableWidget_group->sizeHint().width()*2/3);
    ui->tableWidget_group->setColumnWidth(1, ui->tableWidget_group->sizeHint().width()*4/3);

    ui->tableWidget_user->setColumnWidth(0, ui->tableWidget_user->sizeHint().width()*2/3);
    ui->tableWidget_user->setColumnWidth(1, ui->tableWidget_user->sizeHint().width()*4/3);
    QVector<GroupPermiss> groups;
    QVector<UserPermiss> users;
    groups  = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup;
    users   = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser;
    QTableWidgetItem *item = NULL;
    QString text;

    //没有用户和组的时候的情况，初始组和用户不能删除只能改变
    if(groups.size() == 0 || users.size() == 0)
    {
        UserPermiss     user0;
        GroupPermiss    group0;

        users.clear();
        user0.m_strName     = tr("默认用户");
        user0.m_strDescrip  = tr("此用户禁止删除");
        user0.m_strPassword = "";
        users.push_back(user0);

        groups.clear();
        group0.m_strName    = tr("默认组");
        group0.m_strDescrip = tr("此组禁止删除");

        Admin administrtor;
        administrtor.m_strUser = user0.m_strName;
        administrtor.m_bIsAdmin = false;
        group0.m_vecMember.push_back(administrtor);
        groups.push_back(group0);

        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup.clear();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser.clear();

        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup.push_back(group0);
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser.push_back(user0);
    }

    ui->tableWidget_group->setRowCount(groups.size());
    for(int i = 0; i < groups.size(); i++)
    {
        ui->tableWidget_group->setRowHeight(i,20);
        text = groups[i].m_strName;
        item = new QTableWidgetItem(text);
        ui->tableWidget_group->setItem(i,0,item);

        text = groups[i].m_strDescrip;
        item = new QTableWidgetItem(text);
        ui->tableWidget_group->setItem(i,1,item);
    }
    ui->tableWidget_user->setRowCount(users.size());
    for(int i=0; i<users.size(); i++)
    {
        ui->tableWidget_user->setRowHeight(i,20);
        text = users[i].m_strName;
        item = new QTableWidgetItem(text);
        ui->tableWidget_user->setItem(i,0,item);

        text = users[i].m_strDescrip;
        item = new QTableWidgetItem(text);
        ui->tableWidget_user->setItem(i,1,item);
    }
}

void NewUserRight::on_pushButton_quit_clicked()
{
    QVector<GroupPermiss> groups;
    QVector<UserPermiss> users;
    groups  = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup;
    users   = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser;
    if(groups.size() == 1 && users.size() == 1)
    {
        if(groups.at(0).m_vecMember.size() == 0)//组和用户没有关系
        {
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("唯一的用户没有对应组!"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
            box.exec();
          //  QMessageBox::about(this, tr("warning"), tr("唯一的用户没有对应组"));
            return;
        }
        else if(groups.at(0).m_vecMember.at(0).m_strUser != users.at(0).m_strName)//组和用户没有关系（错误的情况下，一般不发生）
        {
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("唯一的用户没有对应组!"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
            box.exec();
          //  QMessageBox::about(this, tr("warning"), tr("唯一的用户没有对应组"));
            return;
        }
    }
    this->accept();
}

//添加用户
void NewUserRight::on_pushButton_addUser_clicked()
{
    EditUserDlg userdlg(-1,this);
    QVector<GroupPermiss> groups;
    groups = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup;
    if(userdlg.exec() == QDialog::Accepted)
    {
        //添加用户数据到系统参数
        int size = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser.size();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser.append(userdlg.m_user);

        QStringList names = userdlg.m_groupNames;
        for(int i=0; i<groups.size(); i++)
        {
            if(names.contains(groups[i].m_strName))//属于该组
            {
                int num = groups[i].m_vecMember.size();
                bool bIs = false;
                for(int j = 0; j < num; j++)
                {
                    if(groups[i].m_vecMember.at(j).m_strUser == userdlg.m_user.m_strName)
                    {
                        bIs = true;
                    }
                }
                if(bIs == false)
                {
                    Admin administrator;
                    administrator.m_strUser = userdlg.m_user.m_strName;
                    administrator.m_bIsAdmin = false;
                    pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_vecMember << administrator;
                }
            }
            else//不属于该组
            {
                int num = groups[i].m_vecMember.size();
                bool bIs = false;
                int temp;
                for(int j = 0; j < num; j++)
                {
                    if(groups[i].m_vecMember.at(j).m_strUser == userdlg.m_user.m_strName)
                    {
                        bIs = true;
                        temp = j;
                    }
                }
                if(bIs == true)
                {
                    pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_vecMember.remove(temp);
                }
            }
        }

        //ui->tableWidget_user->setRowCount(size+1);
        ui->tableWidget_user->insertRow(size);
        ui->tableWidget_user->setRowHeight(size,20);
        QTableWidgetItem *item = new QTableWidgetItem(userdlg.m_user.m_strName);
        ui->tableWidget_user->setItem(size,0,item);
        ui->tableWidget_user->setItem(size,1,new QTableWidgetItem(userdlg.m_user.m_strDescrip));

        ui->tableWidget_user->setCurrentCell(size,0);//设置选择状态
        item->setSelected(true);
    }
}

//编辑用户
void NewUserRight::on_pushButton_attrUser_clicked()
{
    QVector<GroupPermiss> groups;
    groups = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup;
    QString user;
    int row = ui->tableWidget_user->currentRow();
    QTableWidgetItem *item = ui->tableWidget_user->item(row,0);
    if(item && !item->text().isEmpty())
    {
        user = item->text();
        EditUserDlg userdlg(row,this);
        if(userdlg.exec() == QDialog::Accepted)
        {
            //修改用户里的该条参数
            int size = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser.size();
            if(size >= row)
                pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser.replace(row,userdlg.m_user);
            item->setText(userdlg.m_user.m_strName);
            item = ui->tableWidget_user->item(row,1);
            if(item)
            {
                item->setText(userdlg.m_user.m_strDescrip);
            }
            QStringList names = userdlg.m_groupNames;
            for(int i=0; i<groups.size(); i++)
            {
                if(names.contains(groups[i].m_strName))//属于该组
                {
                    int num = groups[i].m_vecMember.size();
                    bool bIs = false;
                    for(int j = 0; j < num; j++)
                    {
                        if(groups[i].m_vecMember.at(j).m_strUser == userdlg.m_user.m_strName)
                        {
                            bIs = true;
                        }
                    }
                    if(bIs == false)
                    {
                        Admin administrator;
                        administrator.m_strUser = userdlg.m_user.m_strName;
                        administrator.m_bIsAdmin = false;
                        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_vecMember << administrator;
                    }
                }
                else//不属于该组
                {
                    int num = groups[i].m_vecMember.size();
                    bool bIs = false;
                    int temp;
                    for(int j = 0; j < num; j++)
                    {
                        if(groups[i].m_vecMember.at(j).m_strUser == userdlg.m_user.m_strName)
                        {
                            bIs = true;
                            temp = j;
                        }
                    }
                    if(bIs == true)
                    {
                        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_vecMember.remove(temp);
                    }
                }
            }
        }
    }
}

//删除用户
void NewUserRight::on_pushButton_delUser_clicked()
{
    QString user;

    int row = ui->tableWidget_user->currentRow();
    if(0 == row)//不允许删除第一个用户
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("禁止删除此用户!"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        //QMessageBox::about(this, tr("warning"), tr("禁止删除此用户"));
        return;
    }

    QTableWidgetItem *item = ui->tableWidget_user->item(row,0);
    if(item && !item->text().isEmpty())
    {
        //删除所有用户中的一条
        int size = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser.size();
        if(size >= row)
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser.remove(row);
        ui->tableWidget_user->removeRow(row);
    }
}

//添加组
void NewUserRight::on_pushButton_addGroup_clicked()
{
    EditGroupDlg groupdlg(-1,this);
    if(groupdlg.exec() == QDialog::Accepted)
    {
        //添加用户组数据到系统参数
        int size = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup.size();
        pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup.append(groupdlg.m_group);


      //  ui->tableWidget_group->setRowCount(size+1);
         ui->tableWidget_group->insertRow(size);
         ui->tableWidget_group->setRowHeight(size,20);
         QTableWidgetItem *item = new QTableWidgetItem(groupdlg.m_group.m_strName);
        ui->tableWidget_group->setItem(size,0,item);
        ui->tableWidget_group->setItem(size,1,new QTableWidgetItem(groupdlg.m_group.m_strDescrip));

        ui->tableWidget_group->setCurrentCell(size,0); //设置选择状态
        item->setSelected(true);
    }
}

//编辑组
void NewUserRight::on_pushButton_attrGroup_clicked()
{
    QString group;

    int row = ui->tableWidget_group->currentRow();
    QTableWidgetItem *item = ui->tableWidget_group->item(row,0);
    if(item && !item->text().isEmpty())
    {
        group = item->text();
        EditGroupDlg groupdlg(row,this);
        if(groupdlg.exec() == QDialog::Accepted)
        {
            //修改所有用户组中的一条
            int size = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup.size();
            if(size >= row)
                pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup.replace(row,groupdlg.m_group);
            item->setText(groupdlg.m_group.m_strName);
            item = ui->tableWidget_group->item(row,1);
            if(item)
            {
                item->setText(groupdlg.m_group.m_strDescrip);
            }
        }
    }
}

//删除组
void NewUserRight::on_pushButton_delGroup_clicked()
{
    QString group;

    int row = ui->tableWidget_group->currentRow();
    if(0 == row)//不允许删除第一个组
    {
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("禁止删除此组!"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        //QMessageBox::about(this, tr("warning"), tr("禁止删除此组"));
        return;
    }

    QTableWidgetItem *item = ui->tableWidget_group->item(row,0);
    if(item && !item->text().isEmpty())
    {
        //删除一条用户组
        int size = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup.size();
        if(size >= row)
            pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup.remove(row);
        ui->tableWidget_group->removeRow(row);
    }
}

void NewUserRight::on_tableWidget_user_cellDoubleClicked(int row, int column)//添加双击用户处理
{
    if(row < 0 || column < 0)
        return;
    on_pushButton_attrUser_clicked();
}

void NewUserRight::on_tableWidget_group_cellDoubleClicked(int row, int column)//添加双击用户组处理
{
        on_pushButton_attrGroup_clicked();
}

void NewUserRight::on_pushButton_help_clicked()
{
        pwnd->loadHelpHtm(TREE_USERPOWER);
}
