#include "MarcoFindDlg.h"
#include "ui_MarcoFindDlg.h"
#include "newGlobalScriptDlg.h"
#include  "Frame\MainWindow.h"
#include "Macro/macro.h"

extern MainWindow  *pwnd;

MarcoFindDlg::MarcoFindDlg(QWidget *parent):QDialog(parent),ui(new Ui::MarcoFindDlg)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(224,237,254));
    setPalette(palette);
    //setWindowOpacity(0.95);

    setFixedSize(size());

    ui->comboBox_lib->clear();
    ui->comboBox_lib->addItem(tr("任意"));

    foreach(Macro lib,pwnd->macros) //初始化库名称
    {
        //if (lib.type && lib.isCompiled())
        if (lib.type)
        {
            ui->comboBox_lib->addItem(lib.libName);
        }
    }

    libName  = "";
    funcName = "";
}

MarcoFindDlg::~MarcoFindDlg()
{
    delete ui;
}



void MarcoFindDlg::on_m_Ok_clicked()
{
    libName  = ui->comboBox_lib->currentText();
    //funcName = ui->comboBox_function->currentText();

    this->accept();
}

void MarcoFindDlg::on_pushButton_cancel_clicked()
{
    this->close();
}
