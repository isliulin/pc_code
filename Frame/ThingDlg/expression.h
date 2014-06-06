#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <QString>
#include <QObject>
#include <Frame/qprogectmanager.h>
typedef enum E_Operation
{
    OPR_NONE = 0,
    OPR_ADD ,//加
    OPR_SUB,//减
    OPR_MUL,//乘
    OPR_DIV,//除
    OPR_XOR,//异或
    OPR_MOD,//取余
    OPR_AND,//与
    OPR_OR, //或
    OPR_SAL,//左移
    OPR_SAR,//右移
    OPR_OTHER,


}E_OPERATION;
static QString strOpera[] =
{
    QObject::tr("无"),
    "+",
    "-",
    "*",
    "/",
    "^",
    "%",
    "&",
    "|",
    "<<",
    ">>",
    "NONE"
};

class Expression
{
public:
    Expression();
    Expression(Keyboard v1);
    QString getExpString();

public:

public:
    Keyboard var1;
    Keyboard var2;
    Keyboard var3;
    Keyboard var4;

    bool bConstant1;
    bool bConstant2;
    bool bConstant3;

    double constant1;
    double constant2;
    double constant3;

    E_OPERATION op1;
    E_OPERATION op2;
    E_OPERATION op3;
private:
    friend QDataStream &operator<<(QDataStream &stream, Expression &exp);
    friend QDataStream &operator>>(QDataStream &stream, Expression &exp);
};

#endif // EXPRESSION_H
