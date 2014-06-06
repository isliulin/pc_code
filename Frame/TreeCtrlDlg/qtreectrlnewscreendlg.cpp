#include "qtreectrlnewscreendlg.h"
#include "view/samdrawscene.h"
#include "Frame\mainwindow.h"
#include "scriptfun.h"
#include <QString>

extern  MainWindow *pwnd;
//extern QList <QGraphicsItem *> CopyList;

QTreeCtrlNewScreenDlg::QTreeCtrlNewScreenDlg(QWidget *parent):QDialog(parent),ui(new Ui::QTreeCtrlNewScreenDlg)
{
    is_property = false;//��ʼ����ע
    ui->setupUi(this);

    setFixedSize(size());

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    ui->newscreen_style_combobox->clear();
    pwnd->OnAddPattern(ui->newscreen_style_combobox);
    ui->newscreen_style_combobox->removeItem(0);
    ui->pushButton_sure->setFocus();

    QRegExp regExp("[^:]{0,50}");
    QValidator *validator = new QRegExpValidator(regExp,this);

    ui->newscreen_name_lineedit->setValidator(validator);
    //this->setWindowTitle(tr("��������"));

    //ui->comboBox_effect->addItem(tr("������ʾ"));
    //ui->comboBox_effect->addItem(tr("���"));
    //ui->comboBox_effect->addItem(tr("���뵭��"));
    //ui->comboBox_effect->addItem(tr("ƽ��"));
    //ui->comboBox_effect->addItem(tr("��ת"));

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void QTreeCtrlNewScreenDlg::InitScreenDlg()//�½�����ʱ���õ�
{
    isNew = true;
    LocalListScript.clear();

    ui->newscreen_style_combobox->clear();
    pwnd->OnAddPattern(ui->newscreen_style_combobox);
    ui->newscreen_style_combobox->removeItem(0);

    //��������
    int totalSceneNum = pwnd->screen->childCount() + pwnd->window->childCount();
    ui->newscreen_name_lineedit->setText(tr("����") + QString::number(totalSceneNum + 1));
    bool is_HaveName = review_Screen_Name(ui->newscreen_name_lineedit->text());
    int i = 0;
    while(is_HaveName)
    {
        ui->newscreen_name_lineedit->setText(tr("����") + QString::number(totalSceneNum + 1 - i));
        //����ID
        //ui->spinBox_windowID->setValue(totalSceneNum + 1 - i);
        is_HaveName = review_Screen_Name(ui->newscreen_name_lineedit->text());
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
    ui->newscreen_pushButton_bk->setStyleSheet(QString("background:%1").arg(QColor(192,192,192).name()));
    //ui->newscreen_pushButton_bk->setEnabled(true);
    ui->newscreen_pushButton_frontcolor->setStyleSheet(QString("background:%1").arg(QColor(0,0,0).name()));
    //ui->newscreen_pushButton_frontcolor->setEnabled(true);
    //ui->newscreen_style_combobox->setEnabled(true);
    ui->newscreen_style_combobox->setCurrentIndex(0);
    //ui->newscreen_picture_lineedit->setEnabled(false);
    ui->newscreen_picture_lineedit->setText("");
    //ui->newscreen_picture_pushButton->setEnabled(false);
    on_newscreen_silence_radiobutton_clicked();
    //����
    ui->radioButton_screen->setChecked(true);
    ui->groupBox_windowtype->setEnabled(false);

    ui->comboBox_effect->clear();
    ui->comboBox_effect->addItem(tr("������ʾ"));
    ui->comboBox_effect->addItem(tr("���"));
    ui->comboBox_effect->addItem(tr("���뵭��"));
    ui->comboBox_effect->addItem(tr("ƽ��"));
    ui->comboBox_effect->addItem(tr("��ת"));

    //�����򿪻���
    ui->groupBox_slider->setEnabled(true);
    ui->groupBox_slider->setChecked(true);
    nCount_Screen=pwnd->screen->childCount();
    item_name = "";
    ui->comboBox_left->clear();
    ui->comboBox_right->clear();
    ui->comboBox_left->addItem(tr("��һ������"));
    ui->comboBox_right->addItem(tr("��һ������"));
    for(int i = 0; i < nCount_Screen; i++)
    {
        item_name = pwnd->screen->child(i)->text(0).split(":").at(1);
        ui->comboBox_left->addItem(item_name);
        ui->comboBox_right->addItem(item_name);
    }
    ui->comboBox_left->setCurrentIndex(0);
    ui->comboBox_right->setCurrentIndex(0);
    ui->checkBox_left->setChecked(true);
    ui->checkBox_right->setChecked(true);
    ui->comboBox_left->setVisible(true);
    ui->comboBox_right->setVisible(true);
    ui->comboBox_effect->clear();
    ui->comboBox_effect->addItem(tr("������ʾ"));
    ui->comboBox_effect->addItem(tr("���"));
    ui->comboBox_effect->addItem(tr("���뵭��"));
    ui->comboBox_effect->addItem(tr("ƽ��"));
    ui->comboBox_effect->addItem(tr("��ת"));
    ui->comboBox_effect->setCurrentIndex(1);

    //������ʾλ��
    //ui->groupBox_pos->setEnabled(false);

    //���ڴ�С
    //ui->groupBox_size->setEnabled(false);

    //��ʼ�����//�ű����Ժ����
    int k = ui->tableWidget->rowCount();
    if(k > 0)
    {
        for(int i = 0; i < k; i++)
        {
            ui->tableWidget->removeRow(0);
        }
    }
}

bool QTreeCtrlNewScreenDlg::review_Screen_Name(QString str)//�жϴ��������Ƿ�ռ��
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

    if(pwnd->window->childCount() >= 1)
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

void QTreeCtrlNewScreenDlg::InitScreenPropertyDlg()//�򿪻���ʱ�õ�
{
    this->setWindowTitle(tr("��������"));

    isNew = false;
    LocalListScript.clear();

    ui->newscreen_style_combobox->clear();
    pwnd->OnAddPattern(ui->newscreen_style_combobox);
    ui->newscreen_style_combobox->removeItem(0);

    ui->comboBox_effect->clear();
    ui->comboBox_effect->addItem(tr("������ʾ"));
    ui->comboBox_effect->addItem(tr("���"));
    ui->comboBox_effect->addItem(tr("���뵭��"));
    ui->comboBox_effect->addItem(tr("ƽ��"));
    ui->comboBox_effect->addItem(tr("��ת"));

    int nCount_Screen=pwnd->screen->childCount();
    QString item_name = "";
    ui->comboBox_left->clear();
    ui->comboBox_right->clear();
    ui->comboBox_left->addItem(tr("��һ������"));
    ui->comboBox_right->addItem(tr("��һ������"));
    for(int i = 0; i < nCount_Screen; i++)
    {
        item_name = pwnd->screen->child(i)->text(0).split(":").at(1);
        ui->comboBox_left->addItem(item_name);
        ui->comboBox_right->addItem(item_name);
    }

    //����
    ui->newscreen_name_lineedit->setText(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName);

    ui->check_logout->setChecked(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bLogout);

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
    ui->newscreen_pushButton_bk->setStyleSheet(QString("background:%1").arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneBackColor.name()));
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
    ui->radioButton_screen->setChecked(true);
    ui->groupBox_windowtype->setEnabled(false);

    //�Ƿ�ѡ�뻭��
    ui->checkBox->setChecked(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bIsAddMenu);

    //�����򿪻���
    ui->groupBox_slider->setChecked(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bSlide);//bSlideΪtrue
    if(0 == pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardLeftId)
    {
        ui->checkBox_left->setChecked(false);
        ui->comboBox_left->setVisible(false);
    }
    else
    {
        ui->checkBox_left->setChecked(true);
        ui->comboBox_left->setVisible(true);
        ui->comboBox_left->setCurrentIndex(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardLeftId - 1);
    }
    if(0 == pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardRIghtId)
    {
        ui->checkBox_right->setChecked(false);
        ui->comboBox_right->setVisible(false);
    }
    else
    {
        ui->checkBox_right->setChecked(true);
        ui->comboBox_right->setVisible(true);
        ui->comboBox_right->setCurrentIndex(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardRIghtId - 1);
    }
    ui->comboBox_effect->setCurrentIndex(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSlideStyle);

    //���ڴ�С������λ��
    //ui->groupBox_size->setEnabled(false);
    //ui->groupBox_pos->setEnabled(false);

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

QTreeCtrlNewScreenDlg::~QTreeCtrlNewScreenDlg()//����
{
    delete ui;
}

//ȷ����ť,ֻ�ж������Ƿ��ظ�����ֵ��mainwindow��
void QTreeCtrlNewScreenDlg::on_pushButton_sure_clicked()
{
    //����
    if(ui->newscreen_name_lineedit->text() == "")
    {
        QMessageBox box(this);
        box.setText(tr("�������ֲ�����λ�գ�������һ������"));
        box.exec();
        ui->newscreen_name_lineedit->setFocus(Qt::ActiveWindowFocusReason);
        return;
    }

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

    //�����
    int number = ui->spinBox->value();
    QVector<int> vecNumber;
    QString item_name = "";
    QString shitName = "";
    int temp;
    int nCount_Screen = pwnd->screen->childCount();
    int nCount_Window = pwnd->window->childCount();

    foreach(SamDrawScene*pScene,pwnd->pSceneSheet)
    {
        if (pScene->nIsSceneOrWindow != 2)
        {
            vecNumber << pScene->sNumberName.toInt();
        }
    }
    if(!isNew)
    {
        shitName = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNumberName;
        int k = shitName.toInt()%1000;
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

    //?????????
    if(pwnd->is_ScreenProperty_Name)
    {
        if(ui->newscreen_name_lineedit->text() == pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName)
        {
            accept();

            pwnd->is_ScreenProperty_Name = false;
            return;
        }
    }
    //�����Ƿ��ظ�
    bool is_HaveName;
    is_HaveName = pwnd->review_ScreenAndWindow_Name(ui->newscreen_name_lineedit->text());
    ui->newscreen_name_lineedit->setFocus(Qt::ActiveWindowFocusReason);
    if(is_HaveName)
    {
        return;
    }

    accept();
}

//ȡ��
void QTreeCtrlNewScreenDlg::on_pushButton_cancel_clicked()
{
    reject();
}

//Ĭ��
void QTreeCtrlNewScreenDlg::on_newscreen_silence_radiobutton_clicked()
{
    ui->label_bk->setVisible(true);
    ui->label_frontcolor->setVisible(true);
    ui->label_style->setVisible(true);

    ui->newscreen_pushButton_bk->setVisible(true);
    ui->newscreen_pushButton_frontcolor->setVisible(true);
    ui->newscreen_style_combobox->setVisible(true);

    ui->newscreen_picture_lineedit->setVisible(false);
    ui->newscreen_picture_pushButton->setVisible(false);
}

//λͼ
void QTreeCtrlNewScreenDlg::on_newscreen_picture_radiobutton_clicked()
{
    ui->label_bk->setVisible(false);
    ui->label_frontcolor->setVisible(false);
    ui->label_style->setVisible(false);

    ui->newscreen_pushButton_bk->setVisible(false);
    ui->newscreen_pushButton_frontcolor->setVisible(false);
    ui->newscreen_style_combobox->setVisible(false);

    ui->newscreen_picture_lineedit->setVisible(true);
    ui->newscreen_picture_pushButton->setVisible(true);
}

//ͼƬѡ��ť
void QTreeCtrlNewScreenDlg::on_newscreen_picture_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),pwnd->picturePath,tr("Images (*.png *.jpeg *.jpg *.bmp)"));

    QPixmap picture = QPixmap(filename);
    if (!picture.isNull())
    {
       ui->newscreen_picture_lineedit->setText(filename);
       pwnd->picturePath=filename;
    }
}

//�½�����󱣴滭�������
void QTreeCtrlNewScreenDlg::newscreen_Assign()
{
    pwnd->DrawScreenSize();
    pwnd->nActiveSheetIndex = pwnd->pSceneSheet.size() - 1;

    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName      = ui->newscreen_name_lineedit->text();

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

    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nIsSceneOrWindow    = 0;//����
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneBackColor    = ui->newscreen_pushButton_bk->palette().background().color();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneStyleColor   = ui->newscreen_pushButton_frontcolor ->palette().background().color();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nPattern            = ui->newscreen_style_combobox->currentIndex();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_picturePath       = ui->newscreen_picture_lineedit->text();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_bChangePicPath    = true;
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bIsAddMenu          = ui->checkBox->isChecked();;
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bSlide              = ui->groupBox_slider->isChecked();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSlideStyle         = ui->comboBox_effect->currentIndex();
    if(isNew)
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript          = LocalListScript;
    }

    if(!ui->checkBox_left->isChecked())
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardLeftId = 0;
    }
    else
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardLeftId = ui->comboBox_left->currentIndex() + 1;
    }

    if(!ui->checkBox_right->isChecked())
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardRIghtId = 0;
    }
    else
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardRIghtId = ui->comboBox_right->currentIndex() + 1;
    }

    if(ui->newscreen_silence_radiobutton->isChecked())
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType = 0;
    }
    else if(ui->newscreen_picture_radiobutton->isChecked())
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType = 1;
    }

    //int totalSceneNum = pwnd->screen->childCount() + pwnd->window->childCount();
    //QString temp = QString("%1%2%3").arg((totalSceneNum)/100).arg((totalSceneNum)%100/10).arg((totalSceneNum)%10);
    //pwnd->newScreen[pwnd->nActiveSheetIndex] = new QTreeWidgetItem(pwnd->screen, QStringList(temp + ":" + pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
    pwnd->newScreen[pwnd->nActiveSheetIndex] = new QTreeWidgetItem(pwnd->screen, QStringList(str + ":" + pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
    pwnd->screen->addChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);
    //pwnd->screen->addChild(str +  ":" + pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName);

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    pwnd->handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);
    //pwnd->setWindowTitle(QString("AKWorkshop--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
}

//�򿪻������Ժ�����Ա���
void QTreeCtrlNewScreenDlg::screenProperty_assign()
{
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName      = ui->newscreen_name_lineedit->text();
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
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNumberName         = str0;
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bLogout             = ui->check_logout->isChecked();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nIsSceneOrWindow    = 0;
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneBackColor    = ui->newscreen_pushButton_bk->palette().background().color();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneStyleColor   = ui->newscreen_pushButton_frontcolor ->palette().background().color();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nPattern            = ui->newscreen_style_combobox->currentIndex();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_picturePath       = ui->newscreen_picture_lineedit->text();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_bChangePicPath    = true;
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bIsAddMenu          = ui->checkBox->isChecked();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bSlide              = ui->groupBox_slider->isChecked();
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSlideStyle         = ui->comboBox_effect->currentIndex();
    if(!ui->checkBox_left->isChecked())
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardLeftId = 0;
    }
    else
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardLeftId = ui->comboBox_left->currentIndex() + 1;
    }

    if(!ui->checkBox_right->isChecked())
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardRIghtId = 0;
    }
    else
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardRIghtId = ui->comboBox_right->currentIndex() + 1;
    }

    if(ui->newscreen_silence_radiobutton->isChecked())
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType = 0;
    }
    else if(ui->newscreen_picture_radiobutton->isChecked())
    {
        pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType = 1;
    }

    //int     nTmp = 0;
    //QString sTmp = "";
    QString str  = "";
    /*if(pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(0).contains("00"))
    {
        nTmp = (pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(0).toInt())%10;
        sTmp = QString::number(nTmp);
        str  = "00" + sTmp + ":" + pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
        pwnd->newScreen[pwnd->nActiveSheetIndex]->setText(0,str);
    }
    else if(!pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(0).contains("0"))//0ge0
    {
        nTmp = (pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(0).toInt())%1000;
        sTmp = QString::number(nTmp);
        str  = sTmp + ":" + pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
        pwnd->newScreen[pwnd->nActiveSheetIndex]->setText(0,str);
    }
    else
    {
        nTmp = (pwnd->newScreen[pwnd->nActiveSheetIndex]->text(0).split(":").at(0).toInt())%100;
        sTmp = QString::number(nTmp);
        str  = "0" + sTmp + ":" + pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
        pwnd->newScreen[pwnd->nActiveSheetIndex]->setText(0, str);
    }*/
    str = str0 + ":" + pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    pwnd->newScreen[pwnd->nActiveSheetIndex]->setText(0, str);

    pwnd->isCheck_ScreenProperty = true;

    if(ui->newscreen_picture_radiobutton->isChecked())
    {
         pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_picturePath      = ui->newscreen_picture_lineedit->text();
         pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_bChangePicPath   = true;
    }
}

//���ƻ���
void QTreeCtrlNewScreenDlg::copyScreen()
{
    pwnd->DrawScreenSize();
    int totalSceneNum = pwnd->pSceneSheet.size();

    pwnd->pSceneSheet[totalSceneNum-1]->sNewScreenName      = pwnd->newCopyScreen->ui->lineEdit->text();
    //pwnd->pSceneSheet[totalSceneNum-1]->sNumberName         =
    pwnd->pSceneSheet[totalSceneNum-1]->nIsSceneOrWindow    = 0;
    pwnd->pSceneSheet[totalSceneNum-1]->m_sceneBackColor    = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneBackColor;
    pwnd->pSceneSheet[totalSceneNum-1]->m_sceneStyleColor   = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneStyleColor;
    pwnd->pSceneSheet[totalSceneNum-1]->nPattern            = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nPattern;
    pwnd->pSceneSheet[totalSceneNum-1]->m_picturePath       = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_picturePath;
    pwnd->pSceneSheet[totalSceneNum-1]->m_bChangePicPath    = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_bChangePicPath;
    pwnd->pSceneSheet[totalSceneNum-1]->nSelectType         = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nSelectType;
    pwnd->pSceneSheet[totalSceneNum-1]->bIsAddMenu          = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bIsAddMenu;
    pwnd->pSceneSheet[totalSceneNum-1]->bSlide              = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bSlide;
    pwnd->pSceneSheet[totalSceneNum-1]->nTowardLeftId       = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardLeftId;
    pwnd->pSceneSheet[totalSceneNum-1]->nTowardRIghtId      = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->nTowardRIghtId;
    pwnd->pSceneSheet[totalSceneNum-1]->nSlideStyle         = ui->comboBox_effect->currentIndex();
    pwnd->pSceneSheet[totalSceneNum-1]->bLogout             = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->bLogout;
    pwnd->pSceneSheet[totalSceneNum-1]->listScript          = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript;

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

    //int     ntemp = pwnd->screen->childCount() + pwnd->window->childCount();
    QString strTemp  = QString("%1%2%3").arg((noUse)/100).arg(((noUse)%100)/10).arg((noUse)%10);
    pwnd->pSceneSheet[totalSceneNum-1]->sNumberName = strTemp;
    pwnd->newScreen[totalSceneNum-1] = new QTreeWidgetItem(pwnd->screen, QStringList(strTemp + ":" + pwnd->pSceneSheet[totalSceneNum-1]->sNewScreenName));
    pwnd->screen->addChild(pwnd->newScreen[totalSceneNum-1]);

    int nPreIndex = pwnd->nActiveSheetIndex;
    pwnd->nActiveSheetIndex = totalSceneNum - 1;
    //���Ƴ���/
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->setBackgroundBrush(pwnd->pSceneSheet[nPreIndex]->backgroundBrush());
    QList<QGraphicsItem*>   selList;
    QPainterPath            path;
    int                     id = 0;
    path.addRect(0, 0, pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->width(), pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->height());
    //pwnd->pSceneSheet[nPreIndex]->setSelectionArea(path);
    selList = pwnd->pSceneSheet[nPreIndex]->TopItems();
    QGraphicsItem*  pItem  = NULL;
    int             zValue = 0;
    if(selList.size() != 0)
    {
        QGraphicsItem* pTem = NULL;
        DrawItemToScene CopyFun;
        for(int i=0;i<selList.size();i++)
        {
            CopyFun.CopyItem(&pTem,selList.at(i));
            zValue = selList.at(i)->zValue();
            id = selList.at(i)->data(GROUP_TYPE_KEY).toInt();
            if(id == USER_DEFINE_GROUP)
            {
                pwnd->IsDefineGroup(pTem);
                QItemGroup *group=new QItemGroup();
                for(int i = 0; i < pwnd->child_userGroupItems.size(); i++)
                {
                   group->addToGroup(pwnd->child_userGroupItems.at(i));
                }
                pwnd->child_userGroupItems.clear();
                pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->addItem(group);
                group->setData(GROUP_TYPE_KEY,QVariant(USER_DEFINE_GROUP)); //�����û��Զ�����ϵ�keyֵ
                pTem = dynamic_cast<QGraphicsItem *>(group);
                pTem->setZValue(zValue);
            }
            else
            {
                pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->addItem(pTem);
                pTem->setZValue(zValue);
                pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->setNewItem_ID(pTem,pItem);
                pwnd->AndTreeSubItem(pTem);
                pwnd->upDatetreeScreenItem();//���»��������
            }
            pTem->setFlag(QGraphicsItemGroup::ItemIsMovable, true);
            pTem->setFlag(QGraphicsItemGroup::ItemIsSelectable, true);
            pTem = NULL;
        }
    }
    pwnd->pView->setScene(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]);
    pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->clearSelection();

    QString strDest;
    QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
    pwnd->handleWinTitle(strDest, strtemp);
    pwnd->setWindowTitle(strDest);
    //pwnd->setWindowTitle(QString("AKWorkshop--%1\%2.ak--%3").arg(pwnd->newpro->newprowizard_path.replace("/","\\")).arg(pwnd->newpro->newprowizard_name).arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));
}

//ɾ������
void QTreeCtrlNewScreenDlg::deleteScreen()
{
    QString str         = "";
    int     nTmp        = 0;
    QString stotal      = "";
    int totalSceneNum   = pwnd->pSceneSheet.size();

    if(pwnd->nActiveSheetIndex+1 > totalSceneNum)
    {
        QMessageBox box(this);
        box.setText(tr("��ѡ��һ��Ҫɾ������"));
        box.exec();
        return;
    }

    if(totalSceneNum == 1)
    {
        QMessageBox box(pwnd);
        box.setText(tr("���һ�����治����ɾ��"));
        box.exec();
        return;
    }

    QMessageBox box(QMessageBox::Information,PRO_FULL_NAME,tr("�Ƿ�ɾ����ѡ���棿"),QMessageBox::Ok|QMessageBox::No,pwnd,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    box.button(QMessageBox::Ok)->setText(tr("��"));
    box.button(QMessageBox::No)->setText(tr("��"));
    box.exec();
    if(box.clickedButton()== box.button(QMessageBox::No))
    {
        return;
    }

    pwnd->screen->removeChild(pwnd->newScreen[pwnd->nActiveSheetIndex]);//ɾ�����ؼ�������Ӳ˵�
    pwnd->pSceneSheet.remove(pwnd->nActiveSheetIndex);//ɾ�������е�����
    pwnd->deleteScreen_upDateIndex();

    for(int i = pwnd->nActiveSheetIndex; i < totalSceneNum - 1; i++)
    {
        pwnd->newScreen[i] = pwnd->newScreen[i+1];
        QTreeWidgetItem *parentItem=pwnd->newScreen[i]->parent();//ȡ��һ��������
        if((parentItem != pwnd->TreeKeyboard) && (parentItem != pwnd->copyUserKeyboard))
        {
            //������Ϊ�Զ�����̵Ļ�
            stotal = pwnd->newScreen[i]->text(0).split(":").at(0);
            nTmp   = stotal.toInt();
            stotal = QString("%1%2%3").arg(nTmp/100).arg((nTmp/10)%10).arg(nTmp%10);
            str    = stotal + ":" + pwnd->newScreen[i]->text(0).split(":").at(1);
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
    //if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneTypeProp.nIsSceneOrWindow ==1)
    //{
        QString strDest;
        QString strtemp = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName;
        pwnd->handleWinTitle(strDest, strtemp);
        pwnd->setWindowTitle(strDest);
        /*pwnd->setWindowTitle(QString("AKWorkshop--%1\%2.ak--%3").
                          arg(pwnd->newpro->newprowizard_path.replace("/","\\")).
                          arg(pwnd->newpro->newprowizard_name).
                          arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->sNewScreenName));*/
    //}
    //else if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneTypeProp.nIsSceneOrWindow ==0)
    //{
    //    pwnd->setWindowTitle(QString("AKWorkshop--%1\%2.ak--%3").
    //                         arg(pwnd->newpro->newprowizard_path.replace("/","\\")).
    //                         arg(pwnd->newpro->newprowizard_name).
    //                         arg(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->m_sceneTypeProp.sNewScreenName));
    //}
    //pwnd->PreviewWindow();
}

//����ɫ��ť���
void QTreeCtrlNewScreenDlg::on_newscreen_pushButton_bk_clicked()
{
    ColorPickerPopup *colorPicker = new ColorPickerPopup(10, true, 0);
    pwnd->OnAddColorDlg(ui->newscreen_pushButton_bk, colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCurrentBKColor(const QColor &)));
}

//����ɫ�źŲ�
void QTreeCtrlNewScreenDlg::setCurrentBKColor(const QColor & currentColor)
{
    ui->newscreen_pushButton_bk->setStyleSheet(QString("background:%1").arg(currentColor.name()));
}

//ǰ��ɫ��ť���
void QTreeCtrlNewScreenDlg::on_newscreen_pushButton_frontcolor_clicked()
{
    ColorPickerPopup *colorPicker=new ColorPickerPopup(10, true,0);
    pwnd->OnAddColorDlg(ui->newscreen_pushButton_frontcolor ,colorPicker);
    connect(colorPicker, SIGNAL(selected(const QColor &)), this, SLOT(setCurrentFrontColor(const QColor &)));
}

//ǰ��ɫ�źŲ�
void QTreeCtrlNewScreenDlg::setCurrentFrontColor(const QColor & currentColor)
{
    ui->newscreen_pushButton_frontcolor->setStyleSheet(QString("background:%1").arg(currentColor.name()));
}

//˫���ű����һ����Ԫ
void QTreeCtrlNewScreenDlg::on_tableWidget_cellDoubleClicked(int row, int column)//˫���ű����һ����Ԫ
{
    if(row < 0 || column < 0)
    {
        return;
    }

    on_pushButton_ch_clicked();//�޸�
}

void QTreeCtrlNewScreenDlg::on_pushButton_new_clicked()//�ű�������
{
    scriptFun ScriptDlg(1, -1, isNew, this);

    if(ScriptDlg.exec() == QDialog::Accepted)
    {
        int count = 0;
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

void QTreeCtrlNewScreenDlg::on_pushButton_del_clicked()//�ű���ɾ��
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

void QTreeCtrlNewScreenDlg::on_pushButton_ch_clicked()//�ű����޸�
{
    int irow = ui->tableWidget->currentRow();
    if(irow < 0)
    {
        return;
    }

    int count = 0;
    if(isNew)
    {
        count = LocalListScript.size();
    }
    else
    {
        count = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.size();
    }

    if(irow >= count)
    {
        return;
    }

    scriptFun ScriptDlg(0, irow, isNew, this);
    if(ScriptDlg.exec() == QDialog::Accepted)
    {
        alterDataToTable(irow);
    }
}

void QTreeCtrlNewScreenDlg::on_pushButton_help_clicked()//�ű������
{
    pwnd->loadHelpHtm(TREE_SCREENS);//����
}

void QTreeCtrlNewScreenDlg::insertDataToTable(int iIndex)
{
    QString sName = "";
    int     count = ui->tableWidget->rowCount();
    int     val   = 0;

    ui->tableWidget->insertRow(count);
    ui->tableWidget->setRowHeight(count,20);

    if(isNew)
    {
        sName = LocalListScript.at(iIndex).scriptName; //������
        ui->tableWidget->setItem(count ,0, new QTableWidgetItem(sName));

        sName = LocalListScript.at(iIndex).scriptFuncName; //��������
        ui->tableWidget->setItem(count ,1, new QTableWidgetItem(sName));

        val = LocalListScript.at(iIndex).scriptFreq;//Ƶ��
        sName = QString("%1").arg(val * 100);
        ui->tableWidget->setItem(count ,2, new QTableWidgetItem(sName));

        val = LocalListScript.at(iIndex).scriptCount;//����
        sName = QString("%1").arg(val);
        ui->tableWidget->setItem(count ,3, new QTableWidgetItem(sName));

        val = LocalListScript.at(iIndex).scriptType;//��������
        if(val == 0)
        {
            sName = tr("λ��ַ");
        }
        else if(val == 1)
        {
            sName = tr("�ֵ�ַ");
        }
        ui->tableWidget->setItem(count ,4, new QTableWidgetItem(sName));

        if(LocalListScript.at(iIndex).scriptBShow == true)
        {
            sName = LocalListScript.at(iIndex).scriptAddr.sShowAddr; //���Ƶ�ַ
            ui->tableWidget->setItem(count ,5, new QTableWidgetItem(sName));

            val = LocalListScript.at(iIndex).scriptCondition;//ִ������
            sName = QString("%1").arg(val);
            ui->tableWidget->setItem(count ,6, new QTableWidgetItem(sName));
        }
        else
        {
            sName = ""; //���Ƶ�ַ
            ui->tableWidget->setItem(count ,5, new QTableWidgetItem(sName));
            ui->tableWidget->setItem(count ,6, new QTableWidgetItem(sName));
        }
    }
    else
    {
        sName = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptName; //������
        ui->tableWidget->setItem(count ,0, new QTableWidgetItem(sName));

        sName = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptFuncName; //��������
        ui->tableWidget->setItem(count ,1, new QTableWidgetItem(sName));

        val = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptFreq;//Ƶ��
        sName = QString("%1").arg(val * 100);
        ui->tableWidget->setItem(count ,2, new QTableWidgetItem(sName));

        val = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptCount;//����
        sName = QString("%1").arg(val);
        ui->tableWidget->setItem(count ,3, new QTableWidgetItem(sName));

        val = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptType;//��������
        if(val == 0)
        {
            sName = tr("λ��ַ");
        }
        else if(val == 1)
        {
            sName = tr("�ֵ�ַ");
        }
        ui->tableWidget->setItem(count ,4, new QTableWidgetItem(sName));

        if(pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptBShow == true)
        {
            sName = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptAddr.sShowAddr; //���Ƶ�ַ
            ui->tableWidget->setItem(count ,5, new QTableWidgetItem(sName));

            val = pwnd->pSceneSheet[pwnd->nActiveSheetIndex]->listScript.at(iIndex).scriptCondition;//ִ������
            sName = QString("%1").arg(val);
            ui->tableWidget->setItem(count ,6, new QTableWidgetItem(sName));
        }
        else
        {
            sName = ""; //���Ƶ�ַ
            ui->tableWidget->setItem(count ,5, new QTableWidgetItem(sName));
            ui->tableWidget->setItem(count ,6, new QTableWidgetItem(sName));
        }
    }
}

void QTreeCtrlNewScreenDlg::alterDataToTable(int iIndex)
{
    QTableWidgetItem* item  = NULL;
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

void QTreeCtrlNewScreenDlg::on_checkBox_left_clicked(bool checked)
{
    ui->comboBox_left->setVisible(checked);
}

void QTreeCtrlNewScreenDlg::on_checkBox_right_clicked(bool checked)
{
    ui->comboBox_right->setVisible(checked);
}
