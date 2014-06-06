#ifndef SLIDERDLG_H
#define SLIDERDLG_H

#include <QDialog>
#include "SliderGeneralDlg.h"
//#include "qadvanceddlg.h"
//#include "qmeterscaledlg.h"
#include "view/SliderItem.h"

class SliderDlg
{
public:
    SliderDlg();
public:
    /************************************************************
     *画滑动模拟量开关图形函数
     ***********************************************************/
    SliderItem* DrawSlider(SliderItem *slider);
    QString GetSliderText(int nIndex,double Min,double Max,int nMain,
                          int nTextDirection,int nPointNum);
    int GetTextLength(QString sText,QSimpleTextItem* pText,int nFontSize);
    QSimpleTextItem* DrawSliderText(QSimpleTextItem *pText, int nIndex,
                                   double LineX, double LineY,QString sText,
                                   int nFontSize,QColor mTextColor);


};

#endif // SLIDERDLG_H
