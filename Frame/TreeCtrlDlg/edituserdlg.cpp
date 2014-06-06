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
    ui->edit_password->setToolTip(tr("��Ч�ַ�:A-Z,a-z,0-9,_"));

    ui->edit_name->setValidator(validator);
    ui->edit_name->setToolTip(tr("��Ч�ַ�:A-Z,a-z,0-9,_"));


    ui->label_confirm->hide();
    ui->edit_confirm->hide();

    setFixedSize(size());
    iOpenType = iType; //-1��ʾ�½������ڵ���0������ʾ�������޸�
    setWindowTitle(tr("�û�����"));
    ui->edit_name->setFocus();
    init();
}

EditUserDlg::~EditUserDlg()
{
    delete ui;
}

void EditUserDlg::init()
{
    //��ʼ���û��� �б�
    QVector<GroupPermiss> groups;
    QVector<UserPermiss> users;
    groups = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup;
    users = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser;

    //��ʼ���û���Ϣ
    if(iOpenType == -1) //��ʾ�½��û�
    {
        ui->edit_name->setText("");
        ui->edit_description->setText("");
        ui->edit_password->setText("");
        ui->edit_confirm->setText("");
    }
    else if(iOpenType >= 0)//��ʾ���û��������öԻ���
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

    //��Ҫ����û���������Ϣ
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
        QMessageBox box(QMessageBox::Warning,tr("����"),tr("Ĭ���û�û����Ӧ�����Ӧ��"),QMessageBox::Ok|QMessageBox::No,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
        box.button(QMessageBox::No)->setText(tr("ȡ��"));
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
 *�������ƣ�isNameRight
 *�������ܣ��ж��û������Ƿ�������
 *�������壺
 *����ֵ:       bool
 *�༭���ߣ�֣����
 *�༭���ڣ�2012.9.17
 **************************************************************/
bool EditUserDlg::isNameRight()
{
    QString strUserName = ui->edit_name->text();
    int num = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecUser.size();

    if(strUserName.isEmpty())
    {
        ui->edit_name->setFocus();
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("�û�������Ϊ��"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        return false;
    }
    if(strUserName.contains("\ "))
    {
        ui->edit_name->setFocus();
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("�û��������пո�"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
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
            QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("�û�������!"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
            box.exec();
            return false;
        }
    }

    /*if(ui->edit_confirm->text() != ui->edit_password->text())
    {
        ui->edit_confirm->setFocus();
        QMessageBox box(QMessageBox::Warning,VERSION_NAME,tr("ȷ����������!"),0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
        box.exec();
        return false;
    }*/

    return true;
}

