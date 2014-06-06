#ifndef STRUCTHEAD_H
#define STRUCTHEAD_H

#include "enumhead.h"
using namespace std;
/*����ַ��Դ��ַ*/
typedef struct addrCheckSourceProp{
    short nUserPlcId;                        // �û������PLC��
    int nAddrLen;                            //��ַ�ĳ���
    int nPlcStationIndex;                    //PLC��վ��
    string sRegName;                         //�Ĵ���������
    string sAddrValue;                       //��ֵַ���ַ���
    READ_WRITE_COM_TYPE eAddrRWprop;         //��ַ�Ķ�дȨ��
}ADDR_CHECK_SOURCE_PROP;

/*У���ת���ɹ���ĵ�ַ�ṹ��*/
typedef struct addrTargetProp{
    short nUserPlcId;                        // �û������PLC��
    short nRegIndex;                         //�Ĵ�����������
    int nAddrLen;                            //��ַ�ĳ���
    int nPlcStationIndex;                    //PLC��վ��
    int nAddrValue;                          //��ֵַ
    READ_WRITE_COM_TYPE eAddrRWprop;         //��ַ�Ķ�дȨ��
}ADDR_TARGET_PROP;




#endif