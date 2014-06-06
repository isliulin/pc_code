#ifndef COMPRESS_H
#define COMPRESS_H

#include <QDialog>
#include <QFileDialog>
namespace Ui {
    class Compress;
}

class Compress : public QDialog
{
    Q_OBJECT

public:
    explicit Compress(QWidget *parent = 0);
    ~Compress();
    void DisableCompress( bool bValue);

private:
    Ui::Compress *ui;

private slots:
    void on_StartUncompress_clicked();
    void on_FilePathBTN_2_clicked();
    void on_FileNameBTN_2_clicked();
    void on_StartCompress_clicked();
    void on_FilePathBTN_clicked();
    //void on_FileNameBTN_clicked();
    void on_close_clicked();
    void SetProgress(int nProgress);
    void SignalGetvalue(int & nValue);
};

#endif // COMPRESS_H
