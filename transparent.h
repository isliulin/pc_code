#ifndef TRANSPARENT_H
#define TRANSPARENT_H
#include "Frame/mainwindow.h"
class transparent
{
public:
    transparent();
    void toChinese();
    void toEnglish();
    void translate_cn(MainWindow *mw);
    void translate(MainWindow *mw);

    //void translate_MF_toEn(QMFunctionBtnGenDlg *MF);
};

#endif // TRANSPARENT_H
