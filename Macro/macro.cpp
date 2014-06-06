#include "macro.h"
#include "MacroCmptrd.h"
#include "Frame/mainwindow.h"


extern MainWindow *pwnd;
Macro::Macro()
{
    m_Compiled = false;
}
Macro::Macro(QString code,QString name)
{
    m_code = code;
    libName = name;
    m_Compiled = false;
}
bool Macro::compile(MacroCmptrd thread)
{
    //thread.pushMacro(*this);
    return false;
}
bool Macro::setCode(QString code)
{
    m_code = code;

    return true;
}

QString Macro::code()
{
    return m_code;
}
void Macro::setVar(QVector <VarPro> variants)//重新设置变量
{
    m_Vars = variants;
}
bool Macro::appendVar(VarPro variant)//增加一个变量
{
    foreach(VarPro var,m_Vars)
    {
        if(var.varName == variant.varName)
        {
            return false;
        }
    }
    m_Vars.append(variant);
    return true;
}
QVector <VarPro> Macro::vars()
{
    return m_Vars;
}
void Macro::setModified()//修改代码之后，更新状态为未通过编译
{
    m_Compiled = false;
}

bool Macro::isCompiled()//返回编译状态
{
    return m_Compiled;
}
void Macro::setCompipiled(bool iscompiled)
{
    m_Compiled = iscompiled;
    if(!m_Compiled)
    {
        setMD5(QByteArray());
    }
}
QByteArray Macro::MD5()
{
    return md5;
}
void Macro::setMD5(QByteArray md)
{
     md5 = md;
}
bool Macro::checkMD5()
{
    if(md5.isEmpty())
    {
        return false;
    }
    QByteArray nmd;
    QString classFile;
    if(type)
    {
        classFile = "sdmacro\\ml\\class\\jml\\";
    }
    else
    {
        classFile = "sdmacro\\ml\\class\\jrl\\";
    }
    classFile += libName;
    classFile += ".class";
    nmd = MacroCmptrd::getFileMd5(classFile);
    qDebug() << "new md5 :" << nmd;
    if(nmd.isEmpty())
    {
        return false;
    }
    return (md5 == nmd);

}
void Macro::save(QDataStream &stream)
{
    stream << m_code;
    stream << functions;
    stream << m_Compiled;
    stream << libName;
    stream << type;
    stream << md5;

    int variantList=m_Vars.size();
    stream << variantList;
    for(int j=0;j<variantList;j++)
    {
        stream << m_Vars[j].addr;
        stream << m_Vars[j].dataType;
        stream << m_Vars[j].RWPerm;
        stream << m_Vars[j].varName;
        stream << m_Vars[j].count;
        stream << m_Vars[j].bOffset;
        if(m_Vars[j].bOffset)
        {
            stream << m_Vars[j].offsetAddr;
        }
    }
}
void Macro::load(QDataStream &stream)
{
    stream >> m_code;
    stream >> functions;
    stream >> m_Compiled;
    stream >> libName;
    stream >> type;
    stream >> md5;

    int variantList=0;
    stream >> variantList;
    m_Vars.resize(variantList);
    for(int j=0;j<variantList;j++)
    {
        stream >> m_Vars[j].addr;
        stream >> m_Vars[j].dataType;
        stream >> m_Vars[j].RWPerm;
        stream >> m_Vars[j].varName;
        stream >> m_Vars[j].count;
        if(pwnd->getProVersion() >= 2914)//新版本
        {
            stream >> m_Vars[j].bOffset;
            if(m_Vars[j].bOffset)
            {
                stream >> m_Vars[j].offsetAddr;
            }
        }
        else
        {
            m_Vars[j].bOffset = false;
        }
    }
}
