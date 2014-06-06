#ifndef QUSERKEYBOARD_H
#define QUSERKEYBOARD_H

#include <QWizard>

#include "quserkeyboardascii.h"
#include "quserkeyboardnumber.h"
#include "quserkeyboardselect.h"
#include "quserkeyboardwelcome.h"

class QUserKeyboard : public QWizard
{
    Q_OBJECT
public:
    explicit QUserKeyboard(QWidget *parent = 0);
    ~QUserKeyboard();
    QUserkeyboardwelcome  *Userkwelcome;
    QUserkeyboardselect  *Userkselect;
    QUserkeyboardnumber  *Userknumber;
    QUserkeyboardASCII *Userkascii;

    enum{Page_Welcome,
          Page_Select,
          Page_Number,
            Page_ASCII};
    bool validateCurrentPage();

signals:

public slots:
    void setSubTitle(int);

};

#endif // QUSERKEYBOARD_H
