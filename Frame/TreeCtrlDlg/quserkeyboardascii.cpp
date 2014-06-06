#include "quserkeyboardascii.h"
QUserkeyboardASCII::QUserkeyboardASCII(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::QUserkeyboardASCII)
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
ui->ASCIIpattern1->setChecked(true);
on_ASCIIpattern1_clicked();
}

QUserkeyboardASCII::~QUserkeyboardASCII()
{
    for(int i=0;i<9 && i < userKeyboardScene.size();i++)//前9个是数值输入型键盘
    {
        delete userKeyboardScene[i];
    }
    for(int i=9;i<userKeyboardScene.size();i++)
    {
        if(!ischecked[i-9])//表示删除没有选中的场景
        {
            delete userKeyboardScene[i];
        }
    }
    userKeyboardScene.clear();
    ui->ASCIIkeyboardview->setScene(NULL);
    delete ui;
}

void QUserkeyboardASCII::on_ASCIIpattern1_clicked()
{
    ischecked[0]=ui->ASCIIpattern1->isChecked();
   if(ischecked[0])
    {
       ui->ASCIIkeyboardview->setScene((QGraphicsScene *)userKeyboardScene[ASCIISTART]);
   }
   else
   {
       this->ReView();
   }
}

void QUserkeyboardASCII::on_ASCIIpattern2_clicked()
{
    ischecked[1]=ui->ASCIIpattern2->isChecked();
    if(ischecked[1])
     {
        ui->ASCIIkeyboardview->setScene((QGraphicsScene *)userKeyboardScene[ASCIISTART+1]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardASCII::on_ASCIIpattern3_clicked()
{
    ischecked[2]=ui->ASCIIpattern3->isChecked();
    if(ischecked[2])
     {
        ui->ASCIIkeyboardview->setScene((QGraphicsScene *)userKeyboardScene[ASCIISTART+2]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardASCII::on_ASCIIpattern4_clicked()
{
    ischecked[3]=ui->ASCIIpattern4->isChecked();
    if(ischecked[3])
     {
        ui->ASCIIkeyboardview->setScene((QGraphicsScene *)userKeyboardScene[ASCIISTART+3]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardASCII::on_ASCIIpattern5_clicked()
{
    ischecked[4]=ui->ASCIIpattern5->isChecked();
    if(ischecked[4])
     {
        ui->ASCIIkeyboardview->setScene((QGraphicsScene *)userKeyboardScene[ASCIISTART+4]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardASCII::on_ASCIIpattern6_clicked()
{
    ischecked[5]=ui->ASCIIpattern6->isChecked();
    if(ischecked[5])
     {
        ui->ASCIIkeyboardview->setScene((QGraphicsScene *)userKeyboardScene[ASCIISTART+5]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardASCII::on_ASCIIpattern7_clicked()
{
    ischecked[6]=ui->ASCIIpattern7->isChecked();
    if(ischecked[7])
     {
        ui->ASCIIkeyboardview->setScene((QGraphicsScene *)userKeyboardScene[ASCIISTART+6]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardASCII::on_ASCIIpattern8_clicked()
{
    ischecked[7]=ui->ASCIIpattern8->isChecked();
    if(ischecked[7])
     {
        ui->ASCIIkeyboardview->setScene((QGraphicsScene *)userKeyboardScene[ASCIISTART+7]);
    }
    else
    {
        this->ReView();
    }

}

void QUserkeyboardASCII::on_ASCIIpattern9_clicked()
{
    ischecked[8]=ui->ASCIIpattern9->isChecked();
    if(ischecked[8])
     {
        ui->ASCIIkeyboardview->setScene((QGraphicsScene *)userKeyboardScene[ASCIISTART+8]);
    }
    else
    {
        this->ReView();
    }

}
void QUserkeyboardASCII::ReView()
{
    ui->ASCIIkeyboardview->setScene(NULL);
    for(int i=0;i<9;i++)
    {
        if(ischecked[i])
        {
            ui->ASCIIkeyboardview->setScene((QGraphicsScene *)userKeyboardScene[ASCIISTART+i]);
            break;
        }
    }
}
