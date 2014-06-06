#include "quserkeyboard.h"
#include  "Frame\mainwindow.h"
#include "Command/unandrestack.h"
extern MainWindow  *pwnd;
extern bool  is_tanslator;

QUserKeyboard::QUserKeyboard(QWidget *parent) :
        QWizard(parent)
{
    /**********添加三个页面***********/
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
    setWindowTitle(tr("自定义键盘"));
    setButtonText(QWizard::NextButton,tr("下一步"));
    setButtonText(QWizard::BackButton,tr("上一步"));
    setButtonText(QWizard::CancelButton,tr("取消"));
    //     setButtonText(QWizard::FinishButton,tr("完成"));

    connect(this,SIGNAL(currentIdChanged(int)),SLOT(setSubTitle(int)));

}
/*****************设置页面向导的标题******************/
void QUserKeyboard::setSubTitle(int id)
{
    if(currentId()==Page_Number)
    {
        setWindowTitle(tr("数字键盘"));
    }
    else if(currentId()==Page_ASCII)
    {
        setWindowTitle(tr("ASCII键盘"));
    }
}
bool QUserKeyboard::validateCurrentPage()
{
    QMessageBox box(QMessageBox::Warning,PRO_FULL_NAME,tr("用户自定义键盘最多只能建32个！"),
                    0,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.addButton(tr("确定"),QMessageBox::AcceptRole);
    QString str="";
    // QString sTmp="";
    if(currentId()==Page_Select)
    {
        if(Userkselect->ui->CNumberKeyboard->isChecked())
        {
            removePage(Page_ASCII);

            //   Userknumber=new QUserkeyboardnumber(this);
            setPage(Page_Number, Userknumber);
            setButtonText(QWizard::FinishButton,tr("完成"));
        }
        else if(Userkselect->ui->CASCIIKeyboard->isChecked())
        {
            removePage(Page_Number);
            setPage(Page_ASCII, Userkascii);
            setButtonText(QWizard::FinishButton,tr("完成"));
        }

    }
    if(currentId()==Page_Number)
    {
        for(int i=0;i<9;i++)//数字自定义键盘的遍历
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
                    if(tr("数字键盘")+QString("%1").arg(i+1)==pwnd->pSceneSheet.at(j)->sNewScreenName)
                    {
                        str=Userknumber->userKeyboardScene[i]->sNewScreenName;
                        box.setText(tr("数字键盘")+QString("%1").arg(str.mid(4,1))+tr("  已经存在！"));
                        box.exec();
                        return 0;
                    }
                }
            }
        }
        for(int i=0;i<9;i++)//数字自定义键盘的遍历
        {
            if(!Userknumber->ischecked[i])//若没有选中的话返回
            {
                continue;
            }
            if(pwnd->m_pSamSysParame->nUserDefKeyboardCount >31)
            {
                box.exec();
                return 0;
            }
            pwnd->TreeKeyboard->setHidden(false);//显示树形控件
            if(is_tanslator)
            {
                pwnd->TreeKeyboard->setText(0,"Customize Keyboard");
            }
            pwnd->pSceneSheet.push_back(Userknumber->userKeyboardScene[i]);//添加自定义键盘画面到容器中
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
            //改正翻译错误
            str=pwnd->pSceneSheet[nscenecount]->sNewScreenName;
            //
            pwnd->newScreen[nscenecount]->setText(0,stemp+":"+tr("数字键盘")+QString("%1").arg(str.mid(4,1)));
            pwnd->pSceneSheet[nscenecount]->sNewScreenName=tr("数字键盘")+QString("%1").arg(str.mid(4,1));
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
        Userknumber->ui->userKeyboardView->setScene(NULL);//清空场景 否则添加之后的自定义键盘的当前场景不是主场景 倒置右键的时候无反应
    }
    else if(currentId()==Page_ASCII)
    {
        for(int i=0;i<9;i++)//ASCII自定义键盘的遍历
        {
            if(Userkascii == NULL)
            {
                break;
            }
            if(Userkascii->ischecked[i])
            {
                for(int j=0;j<pwnd->pSceneSheet.size();j++)
                {
                    if(tr("ASCII键盘")+QString("%1").arg(i+1)==pwnd->pSceneSheet.at(j)->sNewScreenName)
                    {
                        str=Userknumber->userKeyboardScene[i+ASCIISTART]->sNewScreenName;
                        box.setText(tr("ASCII键盘")+QString("%1").arg(str.mid(7,2))+tr("  已经存在！"));
                        box.exec();
                        return 0;
                    }
                }
            }
        }
        for(int i=0;i<9;i++)//数字自定义键盘的遍历
        {
            if(!Userkascii->ischecked[i])//若没有选中的话返回
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
            pwnd->pSceneSheet.push_back(Userkascii->userKeyboardScene[i+ASCIISTART]);//添加自定义键盘画面到容器中
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
            //改正翻译错误
            str=pwnd->pSceneSheet[nscenecount]->sNewScreenName;
            //
            pwnd->newScreen[nscenecount]->setText(0,stemp+":"+tr("ASCII键盘")+QString("%1").arg(str.mid(7,2)));
            pwnd->pSceneSheet[nscenecount]->sNewScreenName=tr("ASCII键盘")+QString("%1").arg(str.mid(7,2));
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

        Userkascii->ui->ASCIIkeyboardview->setScene(NULL);//清空场景
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
