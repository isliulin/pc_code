#include "expression.h"

Expression::Expression()
{
    var1.sShowAddr = "LW0";
    bConstant1 = true;
    bConstant2 = true;
    bConstant3 = true;

    constant1 = 0;
    constant2 = 0;
    constant3 = 0;

    op1 = OPR_NONE;
    op2 = OPR_NONE;
    op3 = OPR_NONE;
}
Expression::Expression(Keyboard v1)
{
    var1 = v1;
    bConstant1 = true;
    bConstant2 = true;
    bConstant3 = true;

    constant1 = 0;
    constant2 = 0;
    constant3 = 0;

    op1 = OPR_NONE;
    op2 = OPR_NONE;
    op3 = OPR_NONE;
}

QString Expression::getExpString()
{
    QString strExp = var1.sShowAddr;
    if(op1 > OPR_NONE && op1 < OPR_OTHER)
    {
        strExp += strOpera[op1];
        if(bConstant1)
        {
            strExp += QString::number(constant1);
        }
        else
            strExp += var2.sShowAddr;
    }

    if(op2 > OPR_NONE && op2 < OPR_OTHER)
    {
        strExp += strOpera[op2];
        if(bConstant2)
        {
            strExp += QString::number(constant2);
        }
        else
            strExp += var3.sShowAddr;
    }

    if(op3 > OPR_NONE && op3 < OPR_OTHER)
    {
        strExp += strOpera[op3];
        if(bConstant3)
        {
            strExp += QString::number(constant3);
        }
        else
            strExp += var4.sShowAddr;
    }


    return strExp;
}
QDataStream &operator<<(QDataStream &stream, Expression &exp)
{
    stream << exp.var1;
    stream << exp.var2;
    stream << exp.var3;
    stream << exp.var4;

    stream << exp.bConstant1;
    stream << exp.bConstant2;
    stream << exp.bConstant3;

    stream << exp.constant1;
    stream << exp.constant2;
    stream << exp.constant3;

    stream << (int)exp.op1;
    stream << (int)exp.op2;
    stream << (int)exp.op3;

    return stream;
}

QDataStream &operator>>(QDataStream &stream, Expression &exp)
{

    stream >> exp.var1;
    stream >> exp.var2;
    stream >> exp.var3;
    stream >> exp.var4;

    stream >> exp.bConstant1;
    stream >> exp.bConstant2;
    stream >> exp.bConstant3;

    stream >> exp.constant1;
    stream >> exp.constant2;
    stream >> exp.constant3;

    int temp = 0;
    stream >> temp;
    exp.op1 = (E_OPERATION)temp;
    stream >> temp;
    exp.op2 = (E_OPERATION)temp;
    stream >> temp;
    exp.op3 = (E_OPERATION)temp;

    return stream;
}
