#ifndef MACRO_H
#define MACRO_H
#include<QString>
#include<QVector>
#include "Frame/qprogectmanager.h"

class MacroCmptrd ;
class Macro
{
public:
    Macro();
    Macro(QString code,QString name);
    //fuction
    bool compile(MacroCmptrd thread);//编译当前代码
    bool setCode(QString code);//修改函数代码
    QString code(); //返回当前函数的代码
    void setVar(QVector <VarPro> variants);//重新设置变量
    bool appendVar(VarPro variant);
    QVector <VarPro> vars();
    bool isCompiled();
    void setModified();
    void setCompipiled(bool iscompiled);
    QByteArray MD5();
    bool checkMD5();
    void save(QDataStream &stream);
    void load(QDataStream &stream);
    void setMD5(QByteArray md);
public:
    QString libName; //函数名称
    bool type; //库类型：脚本或者是自定义库
    QStringList functions;//自定义库有多个函数
    QVector <VarPro> m_Vars; //变量组
private:
    //Enum MACRO_TYPE m_type;//类型：全局脚本，画面脚本，初始化脚本，控件脚本

    QString m_code; //函数代码

    QByteArray md5; //编译后的class文件校验码
    bool m_Compiled; //是否通过编译




};

#endif // MACRO_H
