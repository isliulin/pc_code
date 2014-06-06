#include "quserkeyboardnumber.h"
QUserkeyboardnumber::QUserkeyboardnumber(QWidget *parent) :
        QWizardPage(parent),
        ui(new Ui::QUserkeyboardnumber)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);
    QMessageBox msg(QMessageBox::Warning,PRO_FULL_NAME,tr(""),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    msg.addButton(tr("确定"),QMessageBox::AcceptRole);

    QFile file("userkeyboard.dat");
    if(!file.open(QIODevice::ReadOnly))
    {
        msg.setText(tr("userkeyboard.dat未找到！"));
        msg.exec();
        return ;//返回参数不对，应该重新设置出错返回参数
    }
    QDataStream out(&file);
    userKeyboardScene.clear();
    SamDrawScene *pScene = NULL;
    for(int i=0;i<9;i++)
    {
        ischecked[i]=false;
    }
    for(int num = 0; !out.atEnd(); num++)
    {
        pScene = new SamDrawScene;
        //out >> pScene;
        pScene->load(out,pScene);
        pScene->DrawScreenSize();
        userKeyboardScene.push_back(pScene);
    }
    file.close();
    ui->NOpattern1->setChecked(true);
    on_NOpattern1_clicked();
}

QUserkeyboardnumber::~QUserkeyboardnumber()
{
    for(int i=0;i<9;i++)
    {
        if(!ischecked[i] && i < userKeyboardScene.size())//表示删除没有选中的场景
        {
            delete userKeyboardScene[i];
        }
    }
    for(int i=9;i<userKeyboardScene.size();i++)
    {
        //后9个是ASCII型键盘
        delete userKeyboardScene[i];
    }
    userKeyboardScene.clear();
    ui->userKeyboardView->setScene(NULL);

    delete ui;
}

void QUserkeyboardnumber::on_NOpattern1_clicked()
{
    ischecked[0]=ui->NOpattern1->isChecked();
    if(ischecked[0])
     {
        ui->userKeyboardView->setScene((QGraphicsScene *)userKeyboardScene[0]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardnumber::on_NOpattern2_clicked()
{
    ischecked[1]=ui->NOpattern2->isChecked();
    if(ischecked[1])
     {
        ui->userKeyboardView->setScene((QGraphicsScene *)userKeyboardScene[1]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardnumber::on_NOpattern3_clicked()
{
    ischecked[2]=ui->NOpattern3->isChecked();
    if(ischecked[2])
     {
        ui->userKeyboardView->setScene((QGraphicsScene *)userKeyboardScene[2]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardnumber::on_NOpattern4_clicked()
{
    ischecked[3]=ui->NOpattern4->isChecked();
    if(ischecked[3])
     {
        ui->userKeyboardView->setScene((QGraphicsScene *)userKeyboardScene[3]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardnumber::on_NOpattern5_clicked()
{
    ischecked[4]=ui->NOpattern5->isChecked();
    if(ischecked[4])
     {
        ui->userKeyboardView->setScene((QGraphicsScene *)userKeyboardScene[4]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardnumber::on_NOpattern6_clicked()
{
    ischecked[5]=ui->NOpattern6->isChecked();
    if(ischecked[5])
     {
        ui->userKeyboardView->setScene((QGraphicsScene *)userKeyboardScene[5]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardnumber::on_NOpattern7_clicked()
{
    ischecked[6]=ui->NOpattern7->isChecked();
    if(ischecked[6])
     {
        ui->userKeyboardView->setScene((QGraphicsScene *)userKeyboardScene[6]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardnumber::on_NOpattern8_clicked()
{
    ischecked[7]=ui->NOpattern8->isChecked();
    if(ischecked[7])
     {
        ui->userKeyboardView->setScene((QGraphicsScene *)userKeyboardScene[7]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardnumber::on_NOpattern9_clicked()
{
    ischecked[8]=ui->NOpattern9->isChecked();
    if(ischecked[8])
     {
        ui->userKeyboardView->setScene((QGraphicsScene *)userKeyboardScene[8]);
    }
    else
    {
        this->ReView();
    }

}
void QUserkeyboardnumber::ReView()
{
    ui->userKeyboardView->setScene(NULL);
    for(int i=0;i<9;i++)
    {
        if(ischecked[i])
        {
            ui->userKeyboardView->setScene((QGraphicsScene *)userKeyboardScene[i]);
            break;
        }
    }
}
