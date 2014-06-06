#include "qnewwindowdlg.h"
#include "Frame\mainwindow.h"
#include "Frame/TreeCtrlDlg/scriptfun.h"

extern  MainWindow *pwnd;
//extern QList <QGraphicsItem *> CopyList;

QNewWindowDlg::QNewWindowDlg(QWidget *parent):QDialog(parent),ui(new Ui::QNewWindowDlg)
{
    is_property = false;//��ʼ����ע
    ui->setupUi(this);

    setFixedSize(size());
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    LocalListScript.clear();

    QRegExp regExp("[^:]{0,50}");
    QValidator *validator = new QRegExpValidator(regExp, this);

    ui->lineEdit_name->setValidator(validator);

    ui->newscreen_style_combobox->clear();
    pwnd->OnAddPattern(ui->newscreen_style_combobox);
    ui->newscreen_style_combobox->removeItem(0);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

//�½�����ʱ���õ�
void QNewWindowDlg::InitWindowDlg()
{
    isNew = true;
    LocalListScript.clear();
    this->setWindowTitle(tr("�½�����"));

    ui->newscreen_style_combobox->clear();
    pwnd->OnAddPattern(ui->newscreen_style_combobox);
    ui->newscreen_style_combobox->removeItem(0);

    //��������
    int totalSceneNum = pwnd->screen->childCount() + pwnd->window->childCount();
    ui->lineEdit_name->setText(tr("����") + QString::number(totalSceneNum + 1));
    bool is_HaveName = review_Window_Name(ui->lineEdit_name->text());
    int  i = 0;
    while(is_HaveName)
    {
        ui->lineEdit_name->setText(tr("����") + QString::number(totalSceneNum + 1 - i));
        is_HaveName = review_Window_Name(ui->lineEdit_name->text());
        i++;
    }

    //�����
    int noUse = 0;
    QVector<int> vecNumber;
    QString item_name = "";
    int temp;
    int nCount_Screen = pwnd->screen->childCount();
    int nCount_Window = pwnd->window->childCount();

    for(int i = 0; i < nCount_Screen; i++)
    {
        item_name = pwnd->screen->child(i)->text(0).split(":").at(0);
        temp = item_name.toInt()%1000;
        vecNumber.push_back(temp);
    }
    if(pwnd->window->childCount() >= 1)
    {
        for(int i = 0; i < nCount_Window; i++)
        {
            item_name = pwnd->window->child(i)->text(0).split(":").at(0);
            temp = item_name.toInt()%1000;
            vecNumber.push_back(temp);
        }
    }
    for(int i = 0; i < 1000; i++)
    {
        if(!vecNumber.contains(i))
        {
            noUse = i;
            break;
        }
    }
    ui->spinBox->setValue(noUse);

    //����
    ui->newscreen_silence_radiobutton->setChecked(true);
    ui->BK_Color->setStyleSheet(QString("background:%1").arg(QColor(192,192,192).name()));
    //ui->BK_Color->setEnabled(true);
    ui->newscreen_pushButton_frontcolor->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
    //ui->newscreen_pushButton_frontcolor->setEnabled(true);
    //ui->newscreen_style_combobox->setEnabled(true);
    ui->newscreen_style_combobox->setCurrentIndex(0);
    //ui->newscreen_picture_lineedit->setEnabled(false);
    ui->newscreen_picture_lineedit->setText("");
    //ui->newscreen_picture_pushButton->setEnabled(false);
    on_newscreen_silence_radiobutton_clicked();

    //����
    ui->radioButton_screen->setChecked(false);
    ui->radioButton_window->setChecked(true);
    ui->groupBox_windowtype->setEnabled(false);

    //�����򿪻���
    //ui->groupBox_slider->setVisible(false);//ֻ�л�����У�����û��

    //������ʾλ��
    ui->radioButton_center->setChecked(true);
    ui->radioButton_pos->setChecked(false);
    ui->spinBox_x->hide();
    ui->spinBox_y->hide();
    ui->label_x->hide();
    ui->label_y->hide();

    //���ڴ�С
    ui->check_title->setChecked(true);
    ui->spinBox_w->setRange(0,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth);
    ui->spinBox_h->setRange(0,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight - 30);
    ui->spinBox_w->setValue(240);
    ui->spinBox_h->setValue(180);

    int k = ui->tableWidget->rowCount();
    if(k > 0)
    {
        for(int i = 0; i < k; i++)
        {
            ui->tableWidget->removeRow(0);
        }
    }
}

//�жϴ��������Ƿ�ռ��
bool QNewWindowDlg::review_Window_Name(QString str)
{
    int nCount_Screen = pwnd->screen->childCount();
    int nCount_Window = pwnd->window->childCount();

    QVector<QString> name_vector;
    QString item_name = "";

    for(int i = 0; i < nCount_Screen; i++)
    {
        item_name = pwnd->screen->child(i)->text(0).split(":").at(1);
        name_vector.push_back(item_name);
    }

    if(pwnd->window->childCount()>=1)
    {
        for(int i = 0; i < nCount_Window; i++)
        {
            item_name = pwnd->window->child(i)->text(0).split(":").at(1);
            name_vector.push_back(item_name);
        }
    }

    if(name_vector.contains(str))
    {
        return 1;
    }

    return 0;
}

//�򿪻���ʱ�õ�
void QNewWindowDlg::InitWindowPropertyDlg()
{
    isNew = false;
    LocalListScript.clear();
    this->setWindowTitle(tr("��������"));

    ui->newscreen_style_combobox->clear();
    pwnd->OnAddPattern(ui->newscreen_style_combobox);
    ui->newscreen_style_combobox->removeItem(0);

    //����
    ui->lineEdit_name->setText(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName);
    ui->check_logout->setChecked(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bLogout);
    ui->check_title->setChecked(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bshowTitle);

    //�����
    ui->spinBox->setValue(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNumberName.toInt()%1000);

    //����
    if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType == 0)//Ĭ��
    {
        ui->newscreen_silence_radiobutton->setChecked(true);
        ui->newscreen_picture_radiobutton->setChecked(false);
    }
    else if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType == 1)//λͼ
    {
        ui->newscreen_picture_radiobutton->setChecked(true);
        ui->newscreen_silence_radiobutton->setChecked(false);
    }
    ui->BK_Color->setStyleSheet(QString("background:%1").arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneBackColor.name()));
    ui->newscreen_pushButton_frontcolor->setStyleSheet( QString("background:%1").arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneStyleColor.name()));
    ui->newscreen_style_combobox->setCurrentIndex(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nPattern);
    ui->newscreen_picture_lineedit->setText(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_picturePath);
    //UI�������ã����ػ�����ʾ
    if(ui->newscreen_silence_radiobutton->isChecked())
    {
        on_newscreen_silence_radiobutton_clicked();
    }
    else
    {
        on_newscreen_picture_radiobutton_clicked();
    }

    //����
    ui->radioButton_screen->setChecked(false);
    ui->radioButton_window->setChecked(true);
    ui->groupBox_windowtype->setEnabled(false);

    //�����򿪻���
    //ui->groupBox_slider->setEnabled(false);//ֻ�л�����У�����û��

    //������ʾλ��
    if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bShowMiddle)//��ʾ������
    {
        ui->radioButton_center->setChecked(true);
        ui->radioButton_pos->setChecked(false);
        ui->spinBox_x->hide();
        ui->spinBox_y->hide();
        ui->label_x->hide();
        ui->label_y->hide();
    }
    else//��ʾ��ָ��λ��
    {
        ui->radioButton_center->setChecked(false);
        ui->radioButton_pos->setChecked(true);
        ui->spinBox_x->show();
        ui->spinBox_y->show();
        ui->label_x->show();
        ui->label_y->show();
        ui->spinBox_x->setValue(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->mWindownShowPos.x());
        ui->spinBox_y->setValue(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->mWindownShowPos.y());
    }

    //���ڴ�С
    if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bshowTitle)
    {
        ui->spinBox_h->setRange(0,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight - 30);
    }
    else
    {
        ui->spinBox_h->setRange(0,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight);
    }
    ui->spinBox_w->setRange(0,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth);
    ui->spinBox_w->setValue(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneRect.width());
    ui->spinBox_h->setValue(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneRect.height());

    //��ʼ�����//�ű����Ժ����
    int k = ui->tableWidget->rowCount();
    if(k > 0)
    {
        for(int i = 0; i < k; i++)
        {
            ui->tableWidget->removeRow(0);
        }
    }
    int count = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.size();
    for(int i = 0; i < count; i++)
    {
        insertDataToTable(i);
    }

    is_property = true;//��ʼ�����
}

QNewWindowDlg::~QNewWindowDlg()
{
    delete ui;
}

//�½�����󱣴滭�������
void QNewWindowDlg::newwindow_Assign()
{
    pwnd->DrawWindowSize();

    int totalSceneNum       = pwnd->screen->childCount() + pwnd->window->childCount();
    pwnd->nActiveSheetIndex = pwnd->pSceneSheet.size() - 1;

    //SamDrawScene *pLastScene        = pwnd->pSceneSheet.last();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName      = ui->lineEdit_name->text();
    int number = ui->spinBox->value();
    QString str = QString::number(number);
    if(str.size() == 1)
    {
        str = "00" + str;
    }
    else if(str.size() == 2)
    {
        str = "0" + str;
    }
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNumberName         = str;
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bLogout         = ui->check_logout->isChecked();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bshowTitle      = ui->check_title->isChecked();

    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nIsSceneOrWindow    = 1;
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneBackColor    = ui->BK_Color ->palette().background().color();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneStyleColor   = ui->newscreen_pushButton_frontcolor ->palette().background().color();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nPattern            = ui->newscreen_style_combobox->currentIndex(); //=0
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_picturePath       = ui->newscreen_picture_lineedit->text();
    //pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType       = 0;
    if(isNew)
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript      = LocalListScript;
    }

    if(ui->newscreen_silence_radiobutton->isChecked())
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType = 0;
    }
    else if(ui->newscreen_picture_radiobutton->isChecked())
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType = 1;
    }

    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bShowMiddle         = ui->radioButton_center->isChecked();

    int width  = ui->spinBox_w->value();
    int height = ui->spinBox_h->value();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneRect.setWidth(width);
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneRect.setHeight(height);

    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->setSceneRect(0, 0, pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneRect.width(), pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneRect.height());

    if(!pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bShowMiddle)
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->mWindownShowPos.setX(ui->spinBox_x->value());
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->mWindownShowPos.setY(ui->spinBox_y->value());
    }

    //QString temp=QString("%1%2%3").arg((totalSceneNum)/100).arg(((totalSceneNum)%100)/10).arg((totalSceneNum)%10);
    //pwnd->newScreen[pwnd->nActiveSheetIndex]=new QTreeWidgetItem(pwnd->window,QStringList(temp+":"+pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
    pwnd->newScreen[pwnd->nActiveSheetIndex] = new QTreeWidgetItem(pwnd->window,QStringList(str + ":" + pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
    pwnd->window->addChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    pwnd->handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);
    //pwnd->setWindowTitle(QString("AKWorkshop--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
}

//�򿪻������Ժ�����Ա���
void QNewWindowDlg::windowProperty_assign()
{
    int sceneWidth  = ui->spinBox_w->value();
    int sceneHeight = ui->spinBox_h->value();
    SamDrawScene *pActiveScene = pwnd->pSceneSheet[pwnd->nActiveSheetIndex];
    pActiveScene->setSceneRect(0, 0, sceneWidth, sceneHeight);
    qDebug() << pwnd->nActiveSheetIndex;

    pActiveScene->sNewScreenName    = ui->lineEdit_name->text();
    int number = ui->spinBox->value();
    QString str0 = QString::number(number);
    if(str0.size() == 1)
    {
        str0 = "00" + str0;
    }
    else if(str0.size() == 2)
    {
        str0 = "0" + str0;
    }
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNumberName = str0;
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bLogout     = ui->check_logout->isChecked();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bshowTitle  = ui->check_title->isChecked();

    pActiveScene->nIsSceneOrWindow  = 1;
    pActiveScene->m_sceneBackColor  = ui->BK_Color->palette().background().color();
    pActiveScene->m_sceneStyleColor = ui->newscreen_pushButton_frontcolor ->palette().background().color();
    pActiveScene->nPattern          = ui->newscreen_style_combobox->currentIndex();
    pActiveScene->m_picturePath     = ui->newscreen_picture_lineedit->text();
    pActiveScene->m_bChangePicPath    = true;

    pActiveScene->bShowMiddle       = ui->radioButton_center->isChecked();
    if(!pActiveScene->bShowMiddle)
    {
        pActiveScene->mWindownShowPos.setX(ui->spinBox_x->value());
        pActiveScene->mWindownShowPos.setY(ui->spinBox_y->value());
    }

    if(ui->newscreen_silence_radiobutton->isChecked())
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType = 0;
    }
    else if(ui->newscreen_picture_radiobutton->isChecked())
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType = 1;
    }

    //pwnd->DrawWindowSize();

    //int nTmp=0;
    //QString sTmp="";
    QString str = "";
    /*if(pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(0).contains("00"))
    {
        nTmp=(pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(0).toInt())%10;
        sTmp=QString::number(nTmp);
        str="00"+sTmp+":"+pActiveScene->sNewScreenName;
        pwnd->newScreen[pwnd->nActiveSheetIndex]->setText(0,str);

    }
    else if(!pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(0).contains("0"))//0ge0
    {
        nTmp=(pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(0).toInt())%1000;
        sTmp=QString::number(nTmp);
        str=sTmp+":"+pActiveScene->sNewScreenName;
        pwnd->newScreen[pwnd->nActiveSheetIndex]->setText(0,str);
    }
    else//
    {
        nTmp=(pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(0).toInt())%100;
        sTmp=QString::number(nTmp);
        str="0"+sTmp+":"+pActiveScene->sNewScreenName;
        pwnd->newScreen[pwnd->nActiveSheetIndex]->setText(0,str);
    }*/
    str = str0 + ":" + pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    pwnd->newScreen[pwnd->nActiveSheetIndex]->setText(0, str);

    pwnd->isCheck_WindowProperty=true;
}

//���ƻ���
void QNewWindowDlg::copyWindow()
{
    pwnd->DrawWindowSize();

    int totalSceneNum = pwnd->screen->childCount()+pwnd->window->childCount();

    int sceneWidth  = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->width();
    int sceneHeight = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->height();
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->setSceneRect(0, 0, sceneWidth, sceneHeight);

    ui->spinBox_w->setValue(sceneWidth);//SA�Ŀ��
    ui->spinBox_h->setValue(sceneHeight);//SA�߶�
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->sNewScreenName   = pwnd->newCopyWindow->ui->lineEdit->text();
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->nIsSceneOrWindow = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nIsSceneOrWindow;
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->m_sceneBackColor = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneBackColor;
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->m_sceneStyleColor= pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneStyleColor;
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->nPattern         = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nPattern;
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->m_picturePath    = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_picturePath;
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->nSelectType      = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType;
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->bShowMiddle      = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bShowMiddle;
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->bshowTitle       = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bshowTitle;
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->mWindownShowPos  = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->mWindownShowPos;
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->bLogout          = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bLogout;
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->listScript       = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript;
    //�����
    int noUse = 0;
    QVector<int> vecNumber;
    QString item_name = "";
    int temp;
    int nCount_Screen = pwnd->screen->childCount();
    int nCount_Window = pwnd->window->childCount();

    for(int i = 0; i < nCount_Screen; i++)
    {
        item_name = pwnd->screen->child(i)->text(0).split(":").at(0);
        temp = item_name.toInt()%1000;
        vecNumber.push_back(temp);
    }
    if(pwnd->window->childCount() >= 1)
    {
        for(int i = 0; i < nCount_Window; i++)
        {
            item_name = pwnd->window->child(i)->text(0).split(":").at(0);
            temp = item_name.toInt()%1000;
            vecNumber.push_back(temp);
        }
    }
    for(int i = 0; i < 1000; i++)
    {
        if(!vecNumber.contains(i))
        {
            noUse = i;
            break;
        }
    }

    QString strTemp = QString("%1%2%3").arg((noUse)/100).arg(((noUse)%100)/10).arg((noUse)%10);
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->sNumberName = strTemp;
    pwnd->newScreen[pwnd->pSceneSheet.size()-1] = new QTreeWidgetItem(pwnd->window, QStringList(strTemp + ":" + pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->sNewScreenName));
    pwnd->window->addChild(pwnd->newScreen[pwnd->pSceneSheet.size()-1]);
    int nPreIndex=pwnd->nActiveSheetIndex;
    pwnd->nActiveSheetIndex=/*totalSceneNum*/pwnd->pSceneSheet.size()-1;

    /***********************���Ƴ���****************************/
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->setBackgroundBrush(pwnd->pSceneSheet[nPreIndex]->backgroundBrush());

    QList <QGraphicsItem *> selList;
    QPainterPath path;
    int id=0;
    path.addRect(0,0,pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->width(),pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->height());
    //pwnd->pSceneSheet[nPreIndex]->setSelectionArea(path);
    selList=pwnd->pSceneSheet[nPreIndex]->TopItems();
    QGraphicsItem * pItem = NULL;
    int  zValue=0;
    if (selList.size() != 0)
    {
        QGraphicsItem * pTem = NULL;
        DrawItemToScene CopyFun;
        for(int i=0;i<selList.size();i++)
        {
            CopyFun.CopyItem(&pTem,selList.at(i));
            zValue = selList.at(i)->zValue();
            id=selList.at(i)->data(GROUP_TYPE_KEY).toInt();
            if(id==USER_DEFINE_GROUP)
            {
                pwnd->IsDefineGroup(pTem);
                QItemGroup *group=new QItemGroup();
                for(int i=0;i<pwnd->child_userGroupItems.size();i++)
                {
                    group->addToGroup(pwnd->child_userGroupItems.at(i));
                }
                pwnd->child_userGroupItems.clear();
                pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->addItem(group);
                group->setData(GROUP_TYPE_KEY,QVariant(USER_DEFINE_GROUP)); //�����û��Զ�����ϵ�keyֵ
                pTem=dynamic_cast<QGraphicsItem *>(group);;
                pTem->setZValue(zValue);
            }
            else
            {
                pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->addItem(pTem);
                pTem->setZValue(zValue);
                pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->setNewItem_ID(pTem,pItem);
                pwnd->AndTreeSubItem(pTem);
                pwnd->upDatetreeScreenItem();//���»��������
            }
            pTem->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
            pTem->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
            pTem = NULL;
        }
    }
    pwnd->pView->setScene(pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]);
    pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->clearSelection();

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->sNewScreenName;
    pwnd->handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);
    //pwnd->setWindowTitle(QString("AKWorkshop--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(pwnd->pSceneSheet[pwnd->pSceneSheet.size()-1]->sNewScreenName));
}

//ɾ������
void QNewWindowDlg::deleteWindow()
{
    QString str     = "";
    QString stotal  = "";
    int     nTmp    = 0;

    int totalSceneNum = pwnd->pSceneSheet.size();
    QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("�Ƿ�ɾ����ѡ���ڣ�"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("��"));
    box.button(QMessageBox::No)->setText(tr("��"));
    box.exec();
    if(box.clickedButton()== box.button(QMessageBox::No))
    {
        return;
    }

    pwnd->window->removeChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);//ɾ�����ؼ�������Ӳ˵�
    pwnd->pSceneSheet.remove(pwnd->nActiveSheetIndex);
    pwnd->deleteScreen_upDateIndex();
    for(int i=pwnd->nActiveSheetIndex;i<totalSceneNum-1;i++)
    {
        pwnd->newScreen[i]=pwnd->newScreen[i+1];
        QTreeWidgetItem *parentItem=pwnd->newScreen[i]->parent();//ȡ��һ��������
        if(parentItem->text(0)!=tr("�Զ������"))
        {
            //������Ϊ�Զ�����̵Ļ�
            stotal=pwnd->newScreen[i]->text(0).split(":").at(0);
            nTmp=stotal.toInt();
            stotal=QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
            str=stotal+":"+pwnd->newScreen[i]->text(0).split(":").at(1);
            pwnd->newScreen[i]->setText(0,str);
        }
    }

    if(!pwnd->label.isEmpty() && pwnd->nActiveSheetIndex < pwnd->label.size())
    {
        pwnd->label.remove(pwnd->nActiveSheetIndex);
    }
    if(!pwnd->titlelabel.isEmpty() && pwnd->nActiveSheetIndex < pwnd->titlelabel.size())
    {
        pwnd->titlelabel.remove(pwnd->nActiveSheetIndex);
    }
    if(!pwnd->priviewWidget.isEmpty() && pwnd->nActiveSheetIndex < pwnd->priviewWidget.size())
    {
        pwnd->priviewWidget.remove(pwnd->nActiveSheetIndex);
    }

    pwnd->DealWithDeleteScreen();//����ɾ�����洰���Զ�����̵�ʱ�����οؼ�ˢ������

    if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nIsSceneOrWindow ==1)
    {
        QString strDest;
        QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
        pwnd->handleWinTitle(strDest, strtemp);
        pwnd->setWindowTitle(strDest);
        //pwnd->setWindowTitle(QString("AKWorkshop--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).
                             //arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
    }
    else  if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nIsSceneOrWindow == 0)
    {
        QString strDest;
        QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
        pwnd->handleWinTitle(strDest, strtemp);
        pwnd->setWindowTitle(strDest);
        //pwnd->setWindowTitle(QString("AKWorkshop--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).
                             //arg(pwnd->newpro->newprowizard_name).arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
    }
    //pwnd->PreviewWindow();
}

//ǰ��ɫ��ť���
void QNewWindowDlg::on_newscreen_pushButton_frontcolor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->newscreen_pushButton_frontcolor ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCurrentFrontColor(const QColor &)));
}

//ǰ��ɫ�źŲ�
void QNewWindowDlg::setCurrentFrontColor(const QColor & currentColor)
{
    ui->newscreen_pushButton_frontcolor->setStyleSheet(QString("background:%1").arg(currentColor.name()));
}

//����ɫ��ť���
void QNewWindowDlg::on_BK_Color_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->BK_Color,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCurrentBKColor(const QColor &)));
}

//����ɫ�źŲ�
void QNewWindowDlg::setCurrentBKColor(const QColor & currentColor )
{
    ui->BK_Color->setStyleSheet(QString("background:%1").arg(currentColor.name()));
}

//ȡ��
void QNewWindowDlg::on_pushButton_cancel_clicked()
{
    reject();
}

//ȷ��
void QNewWindowDlg::on_pushButton_ok_clicked()
{
    int nxValue;
    int nyValue;

    //λͼ�ַ���Ϊ��
    if(ui->newscreen_picture_radiobutton->isChecked())
    {
        //������������ַ��������Թ�������Ҫ�ѱ༭����ã���û��
        if(ui->newscreen_picture_lineedit->text() == "")
        {
            QMessageBox box(this);
            box.setText(tr("��ѡ��һ��ͼƬ��"));
            QPushButton *button = new QPushButton(tr("ȷ��"),this);
            box.addButton(button,QMessageBox::AcceptRole);
            box.exec();
            return;
        }
    }

    if(ui->radioButton_pos->isChecked())
    {
        nxValue = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenWidth  - ui->spinBox_w->value();
        if(ui->check_title->isChecked())
        {
            nyValue = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight - 30 - ui->spinBox_h->value();
        }
        else
        {
            nyValue = pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight - ui->spinBox_h->value();
        }
        if(ui->spinBox_x->value() > nxValue)
        {
            QMessageBox msgBox;
             msgBox.setText(tr("X���볬����Χ"));
             msgBox.addButton(QMessageBox::Ok);
             msgBox.button(QMessageBox::Ok)->setText(tr("ȷ��"));
             msgBox.exec();
             ui->spinBox_x->setFocus(Qt::MouseFocusReason);
             ui->spinBox_x->selectAll() ;
             return;
        }
        if(ui->spinBox_y->value() > nyValue)
        {
            QMessageBox msgBox;
             msgBox.setText(tr("Y���볬����Χ"));
             msgBox.addButton(QMessageBox::Ok);
             msgBox.button(QMessageBox::Ok)->setText(tr("ȷ��"));
             msgBox.exec();
             ui->spinBox_y->setFocus(Qt::MouseFocusReason);
             ui->spinBox_y->selectAll() ;
             return;
        }
    }

    //�����
    int number = ui->spinBox->value();
    QVector<int> vecNumber;

    foreach(SamDrawScene*pScene,pwnd->pSceneSheet)
    {
        if (pScene->nIsSceneOrWindow != 2)
        {
            vecNumber << pScene->sNumberName.toInt();
        }
    }
    if(!isNew)
    {
        int k = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNumberName.toInt()%1000;
        for(int i = 0; i < vecNumber.size(); i++)
        {
            if(vecNumber[i] == k)
            {
                vecNumber.remove(i);
                break;
            }
        }
    }
    if(vecNumber.contains(number))
    {
        QMessageBox::about(this, tr("��ʾ"), tr("����ʹ��ڱ�Ų����ظ�"));
        ui->spinBox->setFocus();
        return;
    }

    bool is_HaveName;
    if(ui->lineEdit_name->text() == "")
    {
        QMessageBox box(this);
        box.setText(tr("�������ֲ�����λ�գ�������һ������"));
        box.exec();
        ui->lineEdit_name->setFocus(Qt::ActiveWindowFocusReason);
        return;
    }
    if(pwnd->is_WindowProperty_Name)
    {
        if(ui->lineEdit_name->text() == pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName)
        {
            accept();
            pwnd->is_WindowProperty_Name=false;
            return;
        }
    }
    is_HaveName=pwnd->review_ScreenAndWindow_Name(ui->lineEdit_name->text());
    ui->lineEdit_name->setFocus(Qt::ActiveWindowFocusReason);

    if(is_HaveName)
    {
        return;
    }
    else
    {
        //pwnd->reScreenorwindowName(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneTypeProp.sNewScreenName,ui->lineEdit->text());
        accept();
    }
}

//Ĭ��
void QNewWindowDlg::on_newscreen_silence_radiobutton_clicked()
{
    ui->label_8->setVisible(true);
    ui->label_frontcolor->setVisible(true);
    ui->label_style->setVisible(true);

    ui->BK_Color->setVisible(true);
    ui->newscreen_pushButton_frontcolor->setVisible(true);
    ui->newscreen_style_combobox->setVisible(true);

    ui->newscreen_picture_lineedit->setVisible(false);
    ui->newscreen_picture_pushButton->setVisible(false);
}

//λͼ
void QNewWindowDlg::on_newscreen_picture_radiobutton_clicked()
{
    ui->label_8->setVisible(false);
    ui->label_frontcolor->setVisible(false);
    ui->label_style->setVisible(false);

    ui->BK_Color->setVisible(false);
    ui->newscreen_pushButton_frontcolor->setVisible(false);
    ui->newscreen_style_combobox->setVisible(false);

    ui->newscreen_picture_lineedit->setVisible(true);
    ui->newscreen_picture_pushButton->setVisible(true);
}

//ͼƬѡ��ť
void QNewWindowDlg::on_newscreen_picture_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),pwnd->picturePath,tr("Images (*.png *.jpeg *.jpg *.bmp)"));
    //ui->newscreen_picture_lineedit->setText(filename);
    QPixmap picture = QPixmap(filename);
    if (!picture.isNull())
    {
       ui->newscreen_picture_lineedit->setText(filename);
       pwnd->picturePath=filename;
    }
}

void QNewWindowDlg::on_pushButton_new_clicked()//�ű�������
{
    scriptFun ScriptDlg(1, -1, isNew, this);

    int count = 0;
    if(ScriptDlg.exec() == QDialog::Accepted)
    {
        if(isNew)
        {
            LocalListScript.push_back(ScriptDlg.script);
            count = LocalListScript.size();
        }
        else
        {
            count = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.size();
        }
        insertDataToTable(count - 1);
    }

}

void QNewWindowDlg::on_pushButton_del_clicked()//�ű���ɾ��
{
    int irow = ui->tableWidget->currentRow();
    if(irow < 0)
    {
        return;
    }

    ui->tableWidget->removeRow(irow);
    if(isNew)
    {
        LocalListScript.removeAt(irow);
    }
    else
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.removeAt(irow);
    }

    irow--;
    if(irow >= 0)
    {
        ui->tableWidget->setCurrentCell(irow,0);
        QTableWidgetItem *item = ui->tableWidget->item(irow,0);
        item->setSelected(true);
    }
}

void QNewWindowDlg::on_pushButton_ch_clicked()//�ű����޸�
{
    int irow = ui->tableWidget->currentRow();
    if(irow < 0) return;

    int count = isNew ? LocalListScript.size():pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.size();
    if(irow >= count) return;

    scriptFun ScriptDlg(0, irow, this);
    if(ScriptDlg.exec() == QDialog::Accepted)
    {
        alterDataToTable(irow);
    }
}

void QNewWindowDlg::on_helpbtn_clicked()//�ű������
{
    pwnd->loadHelpHtm(TREE_WINDOWS);
}

void QNewWindowDlg::on_tableWidget_cellDoubleClicked(int row, int column)//˫���ű����һ����Ԫ
{
    if(row < 0 || column < 0)
    {
        return;
    }

    on_pushButton_ch_clicked();//�޸�
}

void QNewWindowDlg::insertDataToTable(int iIndex)
{
    QString sName = "";
    int     count = ui->tableWidget->rowCount();
    int     val   = 0;

    ui->tableWidget->insertRow(count);
    ui->tableWidget->setRowHeight(count,20);

    if(isNew)
    {
        sName = LocalListScript.at(iIndex).scriptName; //������
        ui->tableWidget->setItem(count ,0,new QTableWidgetItem(sName));

        sName = LocalListScript.at(iIndex).scriptFuncName; //��������
        ui->tableWidget->setItem(count ,1,new QTableWidgetItem(sName));

        val = LocalListScript.at(iIndex).scriptFreq;//Ƶ��
        sName = QString("%1").arg(val * 100);
        ui->tableWidget->setItem(count ,2,new QTableWidgetItem(sName));

        val = LocalListScript.at(iIndex).scriptCount;//����
        sName = QString("%1").arg(val);
        ui->tableWidget->setItem(count ,3,new QTableWidgetItem(sName));

        val = LocalListScript.at(iIndex).scriptType;//��������
        if(val == 0)
        {
            sName = tr("λ��ַ");
        }
        else if(val == 1)
        {
            sName = tr("�ֵ�ַ");
        }
        ui->tableWidget->setItem(count ,4,new QTableWidgetItem(sName));

        if(LocalListScript.at(iIndex).scriptBShow == true)
        {
            sName = LocalListScript.at(iIndex).scriptAddr.sShowAddr; //���Ƶ�ַ
            ui->tableWidget->setItem(count ,5,new QTableWidgetItem(sName));

            val = LocalListScript.at(iIndex).scriptCondition;//ִ������
            sName = QString("%1").arg(val);
            ui->tableWidget->setItem(count ,6,new QTableWidgetItem(sName));
        }
        else
        {
            sName = ""; //���Ƶ�ַ
            ui->tableWidget->setItem(count ,5,new QTableWidgetItem(sName));
            ui->tableWidget->setItem(count ,6,new QTableWidgetItem(sName));
        }
    }
    else
    {
        sName = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptName; //������
        ui->tableWidget->setItem(count ,0,new QTableWidgetItem(sName));

        sName = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptFuncName; //��������
        ui->tableWidget->setItem(count ,1,new QTableWidgetItem(sName));

        val = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptFreq;//Ƶ��
        sName = QString("%1").arg(val * 100);
        ui->tableWidget->setItem(count ,2,new QTableWidgetItem(sName));

        val = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptCount;//����
        sName = QString("%1").arg(val);
        ui->tableWidget->setItem(count ,3,new QTableWidgetItem(sName));

        val = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptType;//��������
        if(val == 0)
        {
            sName = tr("λ��ַ");
        }
        else if(val == 1)
        {
            sName = tr("�ֵ�ַ");
        }
        ui->tableWidget->setItem(count ,4,new QTableWidgetItem(sName));

        if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptBShow == true)
        {
            sName = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptAddr.sShowAddr; //���Ƶ�ַ
            ui->tableWidget->setItem(count ,5,new QTableWidgetItem(sName));

            val = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptCondition;//ִ������
            sName = QString("%1").arg(val);
            ui->tableWidget->setItem(count ,6,new QTableWidgetItem(sName));
        }
        else
        {
            sName = ""; //���Ƶ�ַ
            ui->tableWidget->setItem(count ,5,new QTableWidgetItem(sName));
            ui->tableWidget->setItem(count ,6,new QTableWidgetItem(sName));
        }
    }

}

void QNewWindowDlg::alterDataToTable(int iIndex)
{
    QTableWidgetItem *item  = NULL;
    QString           sName = "";
    int               val   = 0;

    item = ui->tableWidget->item(iIndex,0);

    if(isNew)
    {
        if(item)
        {
            sName = LocalListScript.at(iIndex).scriptName; //������
            item->setText(sName);
        }

        item = ui->tableWidget->item(iIndex,1);
        if(item)
        {
            sName = LocalListScript.at(iIndex).scriptFuncName; //��������
            item->setText(sName);
        }

        item = ui->tableWidget->item(iIndex,2);
        if(item)
        {
           val = LocalListScript.at(iIndex).scriptFreq;//Ƶ��
           sName = QString("%1").arg(val * 100);
           item->setText(sName);
        }

        item = ui->tableWidget->item(iIndex,3);
        if(item)
        {
           val = LocalListScript.at(iIndex).scriptCount;//����
           sName = QString("%1").arg(val);
           item->setText(sName);
        }

        item = ui->tableWidget->item(iIndex,4);
        if(item)
        {
            val = LocalListScript.at(iIndex).scriptType;//��������
            if(val == 0)
            {
               sName = tr("λ��ַ");
            }
            else if(val == 1)
            {
               sName = tr("�ֵ�ַ");
            }
            item->setText(sName);
        }

        if(LocalListScript.at(iIndex).scriptBShow == true)
        {
            item = ui->tableWidget->item(iIndex,5);
            if(item)
            {
               sName = LocalListScript.at(iIndex).scriptAddr.sShowAddr; //���Ƶ�ַ
               item->setText(sName);
            }

            item = ui->tableWidget->item(iIndex,6);
            if(item)
            {
               val = LocalListScript.at(iIndex).scriptCondition;//ִ������
               sName = QString("%1").arg(val);
               item->setText(sName);
            }
        }
        else
        {
            item = ui->tableWidget->item(iIndex,5);
            if(item)
            {
               sName = ""; //���Ƶ�ַ
               item->setText(sName);
            }

            item = ui->tableWidget->item(iIndex,6);
            if(item)
            {
               sName = "";
               item->setText(sName);
            }
        }
    }
    else
    {
        if(item)
        {
            sName = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptName; //������
            item->setText(sName);
        }

        item = ui->tableWidget->item(iIndex,1);
        if(item)
        {
            sName = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptFuncName; //��������
            item->setText(sName);
        }

        item = ui->tableWidget->item(iIndex,2);
        if(item)
        {
           val = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptFreq;//Ƶ��
           sName = QString("%1").arg(val * 100);
           item->setText(sName);
        }

        item = ui->tableWidget->item(iIndex,3);
        if(item)
        {
           val = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptCount;//����
           sName = QString("%1").arg(val);
           item->setText(sName);
        }

        item = ui->tableWidget->item(iIndex,4);
        if(item)
        {
            val = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptType;//��������
            if(val == 0)
            {
               sName = tr("λ��ַ");
            }
            else if(val == 1)
            {
               sName = tr("�ֵ�ַ");
            }
            item->setText(sName);
        }

        if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptBShow == true)
        {
            item = ui->tableWidget->item(iIndex,5);
            if(item)
            {
               sName = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptAddr.sShowAddr; //���Ƶ�ַ
               item->setText(sName);
            }

            item = ui->tableWidget->item(iIndex,6);
            if(item)
            {
               val = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptCondition;//ִ������
               sName = QString("%1").arg(val);
               item->setText(sName);
            }
        }
        else
        {
            item = ui->tableWidget->item(iIndex,5);
            if(item)
            {
               sName = ""; //���Ƶ�ַ
               item->setText(sName);
            }

            item = ui->tableWidget->item(iIndex,6);
            if(item)
            {
               sName = "";
               item->setText(sName);
            }
        }
    }
}

void QNewWindowDlg::on_radioButton_pos_clicked()//�����������һЩ�ռ�
{
    ui->radioButton_center->setChecked(false);
    ui->radioButton_pos->setChecked(true);
    ui->spinBox_x->show();
    ui->spinBox_y->show();
    ui->label_x->show();
    ui->label_y->show();
}

void QNewWindowDlg::on_radioButton_center_clicked()//ѡ�в��Ǿ��У���ʾһЩ�ռ�
{
    ui->radioButton_center->setChecked(true);
    ui->radioButton_pos->setChecked(false);
    ui->spinBox_x->hide();
    ui->spinBox_y->hide();
    ui->label_x->hide();
    ui->label_y->hide();
}

void QNewWindowDlg::on_check_title_clicked(bool checked)
{
    if(checked)
    {
        if(ui->spinBox_h->value() > pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight - 30)
        {
            ui->spinBox_h->setValue(pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight - 30);
        }
        ui->spinBox_h->setRange(0,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight - 30);
        //pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneRect.setHeight(height);
    }
    else
    {
        ui->spinBox_h->setRange(0,pwnd->m_pSamSysParame->m_mixGlobalVar.m_nScreenHeight);
    }
}
