#include "scriptlib.h"


QVector<stScriptLib> getSysLibs()
{
    QVector<stScriptLib> libs;
    stScriptLib lib;
    QVector <stMemberFun> functions;
    stMemberFun function;


    lib.LibName = "FMath";
    //Atan()
    function.funName = QString("Atan");
    function.importCode = QString("Atan( )");
    function.daemon = QString("double Atan(double a)\r\n"
                               "Returns the arc tangent of a value\r\n"
                               "Parameters:\r\n"
                               "   a - the value whose arc tangent is to be returned.\r\n"
                               "Returns:\r\n"
                               "   the arc tangent of the argument\r\n"
                               "Sample:\r\n"
                               "double r = FMath.Atan(1);");
    functions << function;

    //Asin
    function.funName = QString("Asin");
    function.importCode = QString("Asin( )");
    function.daemon = QString("double Asin(double a)\r\n"
                               "Returns the arc sine of a value\r\n"
                               "Parameters:\r\n"
                               "   a - the value whose arc sine is to be returned.\r\n"
                               "Returns:\r\n"
                               "   the arc sine of the argument\r\n"
                               "Sample:\r\n"
                               "double r = FMath.Asin(0.5);");
    functions << function;

    //Acos
    function.funName = QString("Acos");
    function.importCode = QString("Acos( )");
    function.daemon = QString("double Acos(double a)\r\n"
                               "Returns the arc cosine of a value\r\n"
                               "Parameters:\r\n"
                               "   a - the value whose arc cosine is to be returned.\r\n"
                               "Returns:\r\n"
                               "   the arc cosine of the argument\r\n"
                               "Sample:\r\n"
                               "double r = FMath.Acos(0.5);");
    functions << function;

    //Cos
    function.funName = QString("Cos");
    function.importCode = QString("Cos( )");
    function.daemon = QString("double Cos(double a)\r\n"
                               "Returns the cosine of an angle\r\n"
                               "Parameters:\r\n"
                               "   a - an angle, in radians.\r\n"
                               "Returns:\r\n"
                               "   the cosine of the argument\r\n"
                               "Sample:\r\n"
                               "double r = FMath.Cos(60);");
    functions << function;

    //Sin
    function.funName = QString("Sin");
    function.importCode = QString("Sin( )");
    function.daemon = QString("double Sin(double a)\r\n"
                               "Returns the sine of an angle\r\n"
                               "Parameters:\r\n"
                               "   a - an angle, in radians\r\n"
                               "Returns:\r\n"
                               "   the sine of the argument\r\n"
                               "Sample:\r\n"
                               "double r = FMath.Sin(60);");
    functions << function;

    //Tan
    function.funName = QString("Tan");
    function.importCode = QString("Tan( )");
    function.daemon = QString("double Tan(double a)\r\n"
                               "Returns the tangent of an angle\r\n"
                               "Parameters:\r\n"
                               "   a - an angle, in radians.\r\n"
                               "Returns:\r\n"
                               "   the tangent of the argument\r\n"
                               "Sample:\r\n"
                               "double r = FMath.Tan(60);");
    functions << function;

    //Exp
    function.funName = QString("Exp");
    function.importCode = QString("Exp( )");
    function.daemon = QString("double Sin(double a)\r\n"
                               "Returns number e raised to the power of a value\r\n"
                               "Parameters:\r\n"
                               "   a - the exponent to raise e to\r\n"
                               "Returns:\r\n"
                               "   the value \r\n"
                               "Sample:\r\n"
                               "double r = FMath.Exp(2);");
    functions << function;

    //Log
    function.funName = QString("Log");
    function.importCode = QString("Log( )");
    function.daemon = QString("double Asin(double a)\r\n"
                               "Returns the natural logarithm (base e) of a value\r\n"
                               "Parameters:\r\n"
                               "   a - a value\r\n"
                               "Returns:\r\n"
                               "   the value ln a, the natural logarithm of a\r\n"
                               "Sample:\r\n"
                               "double r = FMath.Log(7.39);");
    functions << function;

    //Sqrt
    function.funName = QString("Sqrt");
    function.importCode = QString("Sqrt( )");
    function.daemon = QString("double Sqrt(double a)\r\n"
                               "Returns the positive square root of a value\r\n"
                               "Parameters:\r\n"
                               "   a - a value\r\n"
                               "Returns:\r\n"
                               "   the positive square root of a\r\n"
                               "Sample:\r\n"
                               "double r = FMath.Sqrt(9);");
    functions << function;

    //Pow
    function.funName = QString("Pow");
    function.importCode = QString("Pow( )");
    function.daemon = QString("int  Pow(int x, int y)\r\n"
                               "Returns the value of the first argument raised to the power of the second argument\r\n"
                               "Parameters:\r\n"
                               "   x - the base\r\n"
                               "   y - the exponent\r\n"
                               "Returns:\r\n"
                               "   the value\r\n"
                               "Sample:\r\n"
                               "int r = FMath.Pow(9,2);");
    functions << function;

    //Abs
    function.funName = QString("Abs");
    function.importCode = QString("Abs( )");
    function.daemon = QString("double Abs(double a)\r\n"
                               "Returns the absolute value of a value\r\n"
                               "Parameters:\r\n"
                               "   a - the argument whose absolute value is to be determined\r\n"
                               "Returns:\r\n"
                               "   the absolute value of the argument\r\n"
                               "Sample:\r\n"
                               "double r = FMath.Abs(-1.3759);");
    functions << function;

    //Sign
    function.funName = QString("Sign");
    function.importCode = QString("Sign( )");
    function.daemon = QString("int Sign(double a)\r\n"
                               "Returns the signum of the argument\r\n"
                               "Parameters:\r\n"
                               "   a - the value whose signum is to be returned\r\n"
                               "Returns:\r\n"
                               "   the signum of the argument, positive returns 1 else retuns -1\r\n"
                               "Sample:\r\n"
                               "int r = FMath.Sign(-189);");
    functions << function;

    //BitAnd
    function.funName = QString("BitAnd");
    function.importCode = QString("BitAnd( )");
    function.daemon = QString("int  BitAnd(int a, int b)\r\n"
                               "Returns the value of a & b\r\n"
                               "Parameters:\r\n"
                               "   a - value to be AND'ed with b\r\n"
                               "   b - value to be AND'ed with a\r\n"
                               "Returns:\r\n"
                               "   the value of a & b\r\n"
                               "Sample:\r\n"
                               "int r = FMath.BitAnd(0x01,0x02);");
    functions << function;

    //BitOr
    function.funName = QString("BitOr");
    function.importCode = QString("BitOr( )");
    function.daemon = QString("int BitOr(int a, int b)\r\n"
                               "Returns the value of a | b\r\n"
                               "Parameters:\r\n"
                               "   a - value to be OR'ed with b\r\n"
                               "   b - value to be OR'ed with a\r\n"
                               "Returns:\r\n"
                               "   the value of a | b\r\n"
                               "Sample:\r\n"
                               "int r = FMath.BitOr(0x01,0x02);");
    functions << function;

    //BitXor
    function.funName = QString("BitXor");
    function.importCode = QString("BitXor( )");
    function.daemon = QString("int BitXor(int a, int b)\r\n"
                               "Returns the value of a ^ b\r\n"
                               "Parameters:\r\n"
                               "   a - value to be XOR'ed with b\r\n"
                               "   b - value to be XOR'ed with a\r\n"
                               "Returns:\r\n"
                               "   the value of a ^ b\r\n"
                               "Sample:\r\n"
                               "int r = FMath.BitXor(0x03,0x02);");
    functions << function;

    //BitClear
    function.funName = QString("BitClear");
    function.importCode = QString("BitClear( )");
    function.daemon = QString("int BitClear(int a, int idx)\r\n"
                               "Returns the value equivalent to a value with the designated bit cleared\r\n"
                               "Parameters:\r\n"
                               "   a -   value to be bit cleared\r\n"
                               "   idx - index of bit to clear\r\n"
                               "Returns:\r\n"
                               "   the value of (a & ~(1<<idx))\r\n"
                               "Sample:\r\n"
                               "int r = FMath.BitClear(0x03,0);"
                               "the result r=0x02;");
    functions << function;

    //BitSet
    function.funName = QString("BitSet");
    function.importCode = QString("BitSet( )");
    function.daemon = QString("int BitSet(int a, int idx)\r\n"
                               "Returns the value equivalent to a value with the designated bit set\r\n"
                               "Parameters:\r\n"
                               "   a -   value to be bit set\r\n"
                               "   idx - index of bit to set\r\n"
                               "Returns:\r\n"
                               "   the value of (a | (1<<idx))\r\n"
                               "Sample:\r\n"
                               "int r = FMath.BitSet(0x01,1);"
                               "the result r=0x03");
    functions << function;

    //BitInv
    function.funName = QString("BitInv");
    function.importCode = QString("BitInv( )");
    function.daemon = QString("int BitInv(int a, int idx)\r\n"
                               "Returns the value equivalent to a value with the designated bit flipped\r\n"
                               "Parameters:\r\n"
                               "   a -   value to be bit flip\r\n"
                               "   idx - index of bit to flip\r\n"
                               "Returns:\r\n"
                               "   the value of (a ^ (1<<idx))\r\n"
                               "Sample:\r\n"
                               "int r = FMath.BitInv(0x03,1);\r\n"
                               "the result r=0x01");
    functions << function;



    lib.functions = functions;

    libs << lib;

    return libs;
}
