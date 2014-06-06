#include "quserkeyboard.h"
#include  "Frame\mainwindow.h"
#include "Command/unandrestack.h"
extern MainWindow  *pwnd;
extern bool  is_tanslator;

QUserKeyboard::QUserKeyboard(QWidget *parent) :
        QWizard(parent)
{
    /**********�������ҳ��***********/
    Userkwelcome=new QUserkeyboardwelcome(this);
    Userkselect=new QUserkeyboardselect(this);
    Userknumber=new QUserkeyboardnumber(this);
    Userkascii=new QUserkeyboardASCII(this);

    setPage(Page_Welcome, Userkwelcome);
    setPage(Page_Select, Userkselect);
    setPage(Page_Number, Userknumber);
    setPage(Page_ASCII, Userkascii);
    this->setStyleSheet(QString("background:#f2f2f2"));
    resize(487,420);

    setOption(QWizard::NoBackButtonOnStartPage, true);
    setWindowTitle(tr("�Զ������"));
    setButtonText(QWizard::NextButton,tr("��һ��"));
    setButtonText(QWizard::BackButton,tr("��һ��"));
    setButtonText(QWizard::CancelButton,tr("ȡ��"));
    //     setButtonText(QWizard::FinishButton,tr("���"));

    connect(this,SIGNAL(currentIdChanged(int)),SLOT(setSubTitle(int)));

}
/*****************����ҳ���򵼵ı���******************/
void QUserKeyboard::setSubTitle(int id)
{
    if(currentId()==Page_Number)
    {
        setWindowTitle(tr("���ּ���"));
    }
    else if(currentId()==Page_ASCII)
    {
        setWindowTitle(tr("ASCII����"));
    }
}
bool QUserKeyboard::validateCurrentPage()
{
    QMessageBox box(QMessageBox::Warning,PRO_FULL_NAME,tr("�û��Զ���������ֻ�ܽ�32����"),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.addButton(tr("ȷ��"),QMessageBox::AcceptRole);
    QString str="";
    // QString sTmp="";
    if(currentId()==Page_Select)
    {
        if(Userkselect->ui->CNumberKeyboard->isChecked())
        {
            removePage(Page_ASCII);

            //   Userknumber=new QUserkeyboardnumber(this);
            setPage(Page_Number, Userknumber);
            setButtonText(QWizard::FinishButton,tr("���"));
        }
        else if(Userkselect->ui->CASCIIKeyboard->isChecked())
        {
            removePage(Page_Number);
            setPage(Page_ASCII, Userkascii);
            setButtonText(QWizard::FinishButton,tr("���"));
        }

    }
    if(currentId()==Page_Number)
    {
        for(int i=0;i<9;i++)//�����Զ�����̵ı���
        {
            if(Userknumber == NULL)
            {
                break;
            }
            if(Userknumber->ischecked[i])
            {
                for(int j=0;j<pwnd->pSceneSheet.size();j++)
                {
                    //         if(Userknumber->userKeyboardScene[i]->m_sceneTypeProp.sNewScreenName==pwnd->pSceneSheet.at(j)->m_sceneTypeProp.sNewScreenName)
                    if(tr("���ּ���")+QString("%1").arg(i+1)==pwnd->pSceneSheet.at(j)->sNewScreenName)
                    {
                        str=Userknumber->userKeyboardScene[i]->sNewScreenName;
                        box.setText(tr("���ּ���")+QString("%1").arg(str.mid(4,1))+tr("  �Ѿ����ڣ�"));
                        box.exec();
                        return 0;
                    }
                }
            }
        }
        for(int i=0;i<9;i++)//�����Զ�����̵ı���
        {
            if(!Userknumber->ischecked[i])//��û��ѡ�еĻ�����
            {
                continue;
            }
            if(pwnd->m_pSamSysParame->nUserDefKeyboardCount >31)
            {
                box.exec();
                return 0;
            }
            pwnd->TreeKeyboard->setHidden(false);//��ʾ���οؼ�
            if(is_tanslator)
            {
                pwnd->TreeKeyboard->setText(0,"Customize Keyboard");
            }
            pwnd->pSceneSheet.push_back(Userknumber->userKeyboardScene[i]);//����Զ�����̻��浽������
            pwnd->pSceneSheet[pwnd->pSceneSheet.size() - 1]->nIsSceneOrWindow = 2;
            connect(pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1],SIGNAL(DoubleClickItem(QGraphicsItem *)),pwnd,SLOT(SlotItemDBClick(QGraphicsItem *)));
            connect(pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1],SIGNAL(SingleClickItem()),pwnd,SLOT(OnSingleClickItem()));
            connect(pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1],SIGNAL(SingleClickItem()),pwnd,SLOT(AddItemToScene()));
            connect(pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1], SIGNAL(itemsMoved(SamDrawScene*,QList<QGraphicsItem*>,QList<QPointF>)),
                    pwnd, SLOT(itemsMoved(SamDrawScene *,QList <QGraphicsItem *>,QList <QPointF >)));

            int nscenecount=pwnd->pSceneSheet.size()-1;
            QString stemp;
            unsigned ntemp = pwnd->TreeKeyboard->childCount();
            pwnd->newScreen[nscenecount]=new QTreeWidgetItem(pwnd->TreeKeyboard,QStringList(tr("")));
            stemp=QString("%1%2%3").arg(ntemp/100).arg((ntemp/10)%10).arg(ntemp%10);
            //�����������
            str=pwnd->pSceneSheet[nscenecount]->sNewScreenName;
            //
            pwnd->newScreen[nscenecount]->setText(0,stemp+":"+tr("���ּ���")+QString("%1").arg(str.mid(4,1)));
            pwnd->pSceneSheet[nscenecount]->sNewScreenName=tr("���ּ���")+QString("%1").arg(str.mid(4,1));
            pwnd->TreeKeyboard->addChild(pwnd->newScreen[nscenecount]);
            pwnd->pSceneSheet[nscenecount]->sNewScreenName=pwnd->newScreen[nscenecount]->text(0).split(":").last();
            pwnd->m_pSamSysParame->nUserDefKeyboardCount++;
            pwnd->nActiveSheetIndex=pwnd->pSceneSheet.size()-1;
            pwnd->PreviewWindow();

           SamDrawScene* pSceneTemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex];
           int iActiveSheetIndex = pwnd->nActiveSheetIndex;
           int iTreeIndex = pwnd->TreeKeyboard->indexOfChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);
           QString strNum = pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0);
           pwnd->undoStack->push(new AddKeyBoardCommand(pSceneTemp, iActiveSheetIndex, iTreeIndex, strNum));
        }
        Userknumber->ui->userKeyboardView->setScene(NULL);//��ճ��� �������֮����Զ�����̵ĵ�ǰ�������������� �����Ҽ���ʱ���޷�Ӧ
    }
    else if(currentId()==Page_ASCII)
    {
        for(int i=0;i<9;i++)//ASCII�Զ�����̵ı���
        {
            if(Userkascii == NULL)
            {
                break;
            }
            if(Userkascii->ischecked[i])
            {
                for(int j=0;j<pwnd->pSceneSheet.size();j++)
                {
                    if(tr("ASCII����")+QString("%1").arg(i+1)==pwnd->pSceneSheet.at(j)->sNewScreenName)
                    {
                        str=Userknumber->userKeyboardScene[i+ASCIISTART]->sNewScreenName;
                        box.setText(tr("ASCII����")+QString("%1").arg(str.mid(7,2))+tr("  �Ѿ����ڣ�"));
                        box.exec();
                        return 0;
                    }
                }
            }
        }
        for(int i=0;i<9;i++)//�����Զ�����̵ı���
        {
            if(!Userkascii->ischecked[i])//��û��ѡ�еĻ�����
            {
                continue;
            }
            if(pwnd->m_pSamSysParame->nUserDefKeyboardCount>31)
            {
                box.exec();
                return 0;
            }
            pwnd->TreeKeyboard->setHidden(false);
            if(is_tanslator)
            {
                pwnd->TreeKeyboard->setText(0,"Customize Keyboard");
            }
            pwnd->pSceneSheet.push_back(Userkascii->userKeyboardScene[i+ASCIISTART]);//����Զ�����̻��浽������
            pwnd->pSceneSheet[pwnd->pSceneSheet.size() - 1]->nIsSceneOrWindow = 2;
            connect(pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1],SIGNAL(DoubleClickItem(QGraphicsItem *)),pwnd,SLOT(SlotItemDBClick(QGraphicsItem *)));
            connect(pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1],SIGNAL(SingleClickItem()),pwnd,SLOT(OnSingleClickItem()));
            connect(pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1],SIGNAL(SingleClickItem()),pwnd,SLOT(AddItemToScene()));
            connect(pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1], SIGNAL(itemsMoved(SamDrawScene*,QList<QGraphicsItem*>,QList<QPointF>)),
                    pwnd, SLOT(itemsMoved(SamDrawScene *,QList <QGraphicsItem *>,QList <QPointF >)));
            int nscenecount = pwnd->pSceneSheet.size()-1;
            QString stemp;
            unsigned ntemp = pwnd->TreeKeyboard->childCount();
            pwnd->newScreen[nscenecount]=new QTreeWidgetItem(pwnd->TreeKeyboard,QStringList(tr("")));
            stemp=QString("%1%2%3").arg(ntemp/100).arg((ntemp/10)%10).arg(ntemp%10);
            //�����������
            str=pwnd->pSceneSheet[nscenecount]->sNewScreenName;
            //
            pwnd->newScreen[nscenecount]->setText(0,stemp+":"+tr("ASCII����")+QString("%1").arg(str.mid(7,2)));
            pwnd->pSceneSheet[nscenecount]->sNewScreenName=tr("ASCII����")+QString("%1").arg(str.mid(7,2));
            pwnd->TreeKeyboard->addChild(pwnd->newScreen[nscenecount]);
            pwnd->pSceneSheet[nscenecount]->sNewScreenName=pwnd->newScreen[nscenecount]->text(0).split(":").last();
            pwnd->m_pSamSysParame->nUserDefKeyboardCount++;
            pwnd->nActiveSheetIndex=pwnd->pSceneSheet.size()-1;
            pwnd->PreviewWindow();

            SamDrawScene* pSceneTemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex];
            int iActiveSheetIndex = pwnd->nActiveSheetIndex;
            int iTreeIndex = pwnd->TreeKeyboard->indexOfChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);
            QString strNum = pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0);
            pwnd->undoStack->push(new AddKeyBoardCommand(pSceneTemp, iActiveSheetIndex, iTreeIndex, strNum));
        }

        Userkascii->ui->ASCIIkeyboardview->setScene(NULL);//��ճ���
    }

    pwnd->upDatetreeScreenItem();

    return 1;
}
QUserKeyboard::~QUserKeyboard()
{
    if(Userkwelcome)
    {
        delete Userkwelcome;
        Userkwelcome=NULL;
    }
    if(Userkselect)
    {
        delete Userkselect;
        Userkselect=NULL;
    }
    if(Userknumber)
    {
        delete Userknumber;
        Userknumber=NULL;
    }
    if(Userkascii)
    {
        delete Userkascii;
        Userkascii=NULL;
    }
}
