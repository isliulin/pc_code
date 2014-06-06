#include "compress.h"
#include "ui_compress.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;
Compress::Compress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Compress)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("ѹ��/��ѹ"));

    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(100);
}

Compress::~Compress()
{
    delete ui;
}

void Compress::on_close_clicked()
{
    this->close();
}

void Compress::DisableCompress( bool bValue)
{
    this->ui->groupBox->setDisabled(bValue);
}
void Compress::on_FilePathBTN_clicked()
{
    QFileDialog::Options options = QFileDialog::DontConfirmOverwrite;
    QString selectedFilter;
    QString dir = QFileDialog::getSaveFileName(this,
                                               tr("ѡ��Ҫ�洢��λ��"),
                                                pwnd->sFilePath,
                                                tr("AKR Files (*.akr)"),
                                                &selectedFilter,
                                                options);
    if("" != dir)
    {
        QString sTemp = dir;
        QString str = sTemp.section("/",-1);
        pwnd->sFilePath = sTemp.remove(str);
    }
    if(!dir.isEmpty())
    {
        dir.replace("/","\\");
        //dir = dir +pwnd->newpro->newprowizard_name+".sip";
        ui->EditFileName->setText(dir);
    }

}


//��ʼѹ��
void Compress::on_StartCompress_clicked()
{
    QString sFilePath = ui->EditFileName->text();

    if(sFilePath.isEmpty())
    {
        return;
    }
    QRegExp re("*.akr");
     re.setPatternSyntax(QRegExp::Wildcard);

     QString sTmp;
     sTmp = sFilePath.section("\\",-1);
    if(!re.exactMatch(sTmp) || !sTmp.at(0).isLetterOrNumber())
    {
        QMessageBox box(QMessageBox::Information,tr("�ļ�������ȷ"),tr("�뱣��Ϊ��.akr����ʽ"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
        box.exec();
        return;
    }

    sTmp =sFilePath.left(sFilePath.lastIndexOf("\\"));
    QDir dir(sTmp);

    if(!dir.exists())
    {
        QMessageBox box(QMessageBox::Information,tr("·��������"),tr("�Ƿ񴴽���·��"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));

        box.exec();
        if(box.clickedButton() == box.button(QMessageBox::Ok))
        {
            dir.mkdir(dir.absolutePath());
        }
        else
        {
            return;
        }

    }
    QFileInfo info(sFilePath);
    if(info.exists())
    {
        QMessageBox box(QMessageBox::Information,tr("�ļ��Ѵ���"),tr("�Ƿ񸲸Ǹ��ļ�"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
        box.exec();
        if(box.clickedButton() == box.button(QMessageBox::Cancel))
        {
            return;
        }
    }
    connect(pwnd,SIGNAL(SignalGetvalue(int &)),this,SLOT(SignalGetvalue(int &)));
    connect(pwnd,SIGNAL(SignalCompressProgress(int )),this,SLOT(SetProgress(int )));
    pwnd->compressFile(ui->EditFileName->text());
    disconnect(pwnd,SIGNAL(SignalCompressProgress(int )),this,SLOT(SetProgress(int )));
    disconnect(pwnd,SIGNAL(SignalGetvalue(int &)),this,SLOT(SignalGetvalue(int &)));
    //ui->progressBar->setValue(100);
}

//ѡ��Ҫ��ѹ���ļ���
void Compress::on_FileNameBTN_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("ѡ��Ҫ��ѹ���ļ�"),
                                                    pwnd->sFilePath,
                                                    tr("AKWorkshop (*.akr )"));
    if("" != filename)
    {
        QString sTemp = filename;
        QString str = sTemp.section("/",-1);
        pwnd->sFilePath = sTemp.remove(str);
    }
    if(!filename.isEmpty())
    {
        filename.replace("/","\\");
        ui->EditFilePath_2->setText(filename);
    }
}

//ѡ��Ҫ�洢����̬��
void Compress::on_FilePathBTN_2_clicked()
{
    QFileDialog::Options options = QFileDialog::DontConfirmOverwrite;
    QString selectedFilter;
    QString dir = QFileDialog::getSaveFileName(this,
                                               tr("ѡ��Ҫ�洢��λ��"),
                                                pwnd->sFilePath,
                                                tr(SAVE_FILE_STR),
                                                &selectedFilter,
                                                options);
    if("" != dir)
    {
        QString sTemp = dir;
        QString str = sTemp.section("/",-1);
        pwnd->sFilePath = sTemp.remove(str);
    }
    if(!dir.isEmpty())
    {
        dir.replace("/","\\");
        ui->EditFileName_2->setText(dir);
    }
}

//��ʼ��ѹ��
void Compress::on_StartUncompress_clicked()
{
    QString sSource,sDest;

    sSource = ui->EditFilePath_2->text();
    //sSource = sSource.replace("\\","/");

    sDest = ui->EditFileName_2->text();
    //sDest = sDest.replace("\\","/");

    QFileInfo fi(sSource);
    if(!fi.exists())
    {
        QMessageBox box(QMessageBox::Information,tr("�ļ�������"),tr("����·���Ƿ���ȷ"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
        box.exec();

        return;
    }
    if(sDest.isEmpty() || sSource.isEmpty())
    {
        return;
    }
    QRegExp re(SUFFIX);
    re.setPatternSyntax(QRegExp::Wildcard);

    QString sTmp;
    sTmp = sDest.section("\\",-1);

    if(!re.exactMatch(sTmp) || !sTmp.at(0).isLetterOrNumber())
    {
        QMessageBox box(QMessageBox::Information,tr("�ļ�������ȷ"),tr("�뱣��Ϊ��") + SUFFIX + tr("����ʽ"),QMessageBox::Ok,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("ȷ��"));
        box.exec();
        return;
    }

    sTmp =sDest.left(sDest.lastIndexOf("\\"));

    QDir dir(sTmp);
    if(!dir.exists())
    {
        QMessageBox box(QMessageBox::Information,tr("·��������"),tr("�Ƿ񴴽���·��"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));

        box.exec();
        if(box.clickedButton() == box.button(QMessageBox::Ok))
        {
            dir.mkdir(dir.absolutePath());
        }
        else
        {
            return;
        }

    }
    QFileInfo info(sDest);
    if(info.exists())
    {
        QMessageBox box(QMessageBox::Information,tr("�ļ��Ѵ���"),tr("�Ƿ񸲸Ǹ��ļ�"),QMessageBox::Ok|QMessageBox::Cancel,this,Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        box.button(QMessageBox::Ok)->setText(tr("��"));
        box.button(QMessageBox::Cancel)->setText(tr("ȡ��"));
        box.exec();
        if(box.clickedButton() == box.button(QMessageBox::Cancel))
        {
            return;
        }
    }

    connect(pwnd,SIGNAL(SignalCompressProgress(int )),this,SLOT(SetProgress(int )));

    pwnd->uncompressFile(sSource,sDest);
    ui->progressBar->setValue(100);
    disconnect(pwnd,SIGNAL(SignalCompressProgress(int )),this,SLOT(SetProgress(int )));
}
void Compress::SetProgress(int nProgress)
{
    if(nProgress == -1)
    {
        ui->progressBar->setValue(ui->progressBar->value()+1);
    }
    else
    {
        ui->progressBar->setValue(nProgress);
    }
}

void Compress::SignalGetvalue(int & nValue)
{
    nValue = ui->progressBar->value();
}
