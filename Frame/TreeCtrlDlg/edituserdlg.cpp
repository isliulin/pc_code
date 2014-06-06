#include "edituserdlg.h"
#include "ui_edituserdlg.h"
#include "Frame/mainwindow.h"

extern MainWindow *pwnd;

EditUserDlg::EditUserDlg(int iType,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserDlg)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    QRegExp regExp("[0-9A-Za-z_]*");
    QValidator *validator = new QRegExpValidator(regExp, this);
    ui->edit_password->setValidator(validator);
    ui->edit_password->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));

    ui->edit_name->setValidator(validator);
    ui->edit_name->setToolTip(tr("有效字符:A-Z,a-z,0-9,_"));


    ui->label_confirm->hide();
    ui->edit_confirm->hide();

    setFixedSize(size());
    iOpenType = iType; //-1标示新建，大于等于0的数表示打开属性修改
    setWindowTitle(tr("用户属性"));
    ui->edit_name->setFocus();
    init();
}

EditUserDlg::~EditUserDlg()
{
    delete ui;
}

void EditUserDlg::init()
{
    //初始化用户组 列表
    QVector<GroupPermiss> groups;
    QVector<UserPermiss> users;
    groups = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup;
    users = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser;

    //初始化用户信息
    if(iOpenType == -1) //标示新建用户
    {
        ui->edit_name->setText("");
        ui->edit_description->setText("");
        ui->edit_password->setText("");
        ui->edit_confirm->setText("");
    }
    else if(iOpenType >= 0)//标示打开用户属性设置对话框
    {
        ui->edit_name->setText(users[iOpenType].m_strName);
        ui->edit_description->setText(users[iOpenType].m_strDescrip);
        ui->edit_password->setText(users[iOpenType].m_strPassword);
        ui->edit_confirm->setText(users[iOpenType].m_strPassword);
    }

    QString strUserName = ui->edit_name->text();
    for(int i=0; i<groups.size(); i++)
    {
        QString text = groups[i].m_strName;
        QListWidgetItem *item = new QListWidgetItem(text);
        ui->listWidget->addItem(item);
        item->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);

        int num = groups.at(i).m_vecMember.size();
        bool bIs = false;
        for(int j = 0; j < num; j++)
        {
            if(groups[i].m_vecMember.at(j).m_strUser == strUserName)
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
}

void EditUserDlg::on_btn_ok_clicked()
{
    if( !isNameRight() )
        return;

    m_user.m_strName = ui->edit_name->text();
    m_user.m_strPassword = ui->edit_password->text();
    m_user.m_strDescrip = ui->edit_description->text();
    m_groupNames.clear();

    //需要添加用户组隶属信息
    for(int i=0; i<ui->listWidget->count(); i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        if(item && item->checkState() == Qt::Checked)
        {
            m_groupNames << item->text();
        }
    }

    if(m_groupNames.size() == 0 && iOpenType == 0)
    {
        QMessageBox box(QMessageBox::Warning,tr("警告"),tr("默认用户没有相应的组对应！"),QMessageBox::Ok|QMessageBox::No,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("确定"));
        box.button(QMessageBox::No)->setText(tr("取消"));
        box.exec();
        if(box.clickedButton()== box.button(QMessageBox::No))
        {
            return;
        }
    }

    accept();
}

void EditUserDlg::on_btn_cancel_clicked()
{
    reject();
}

/***************************************************************
 *函数名称：isNameRight
 *函数功能：判断用户名称是否重命名
 *参数含义：
 *返回值:       bool
 *编辑作者：郑启红
 *编辑日期：2012.9.17
 **************************************************************/
bool EditUserDlg::isNameRight()
{
    QString strUserName = ui->edit_name->text();
    int num = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser.size();

    if(strUserName.isEmpty())
    {
        ui->edit_name->setFocus();
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("用户名不能为空"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return false;
    }
    if(strUserName.contains("\ "))
    {
        ui->edit_name->setFocus();
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("用户名不能有空格"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return false;
    }

    for(int i = 0; i < num; i++)
    {
        if( i == iOpenType)
            continue;
        if(strUserName == pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser[i].m_strName)
        {
            ui->edit_name->setFocus();
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("用户名重名!"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("确定"),QMessageBox::AcceptRole);
            box.exec();
            return false;
        }
    }

    /*if(ui->edit_confirm->text() != ui->edit_password->text())
    {
        ui->edit_confirm->setFocus();
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("确认密码有误!"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("确定"),QMessageBox::AcceptRole);
        box.exec();
        return false;
    }*/

    return true;
}

