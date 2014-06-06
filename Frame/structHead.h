#ifndef STRUCTHEAD_H
#define STRUCTHEAD_H

#include "enumhead.h"
using namespace std;
/*检查地址的源地址*/
typedef struct addrCheckSourceProp{
    short nUserPlcId;                        // 用户定义的PLC号
    int nAddrLen;                            //地址的长度
    int nPlcStationIndex;                    //PLC的站号
    string sRegName;                         //寄存器的名字
    string sAddrValue;                       //地址值的字符串
    READ_WRITE_COM_TYPE eAddrRWprop;         //地址的读写权限
}ADDR_CHECK_SOURCE_PROP;

/*校验和转换成功后的地址结构体*/
typedef struct addrTargetProp{
    short nUserPlcId;                        // 用户定义的PLC号
    short nRegIndex;                         //寄存器的索引号
    int nAddrLen;                            //地址的长度
    int nPlcStationIndex;                    //PLC的站号
    int nAddrValue;                          //地址值
    READ_WRITE_COM_TYPE eAddrRWprop;         //地址的读写权限
}ADDR_TARGET_PROP;




#endif