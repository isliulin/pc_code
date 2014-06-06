#ifndef ENUMHEAD_H
#define ENUMHEAD_H

/*�Ĵ���������ö��*/
typedef enum regTypeIndex{
    REG_TYPE_0X          = 0x00,
    REG_TYPE_1X          = 0x01,
    REG_TYPE_3X_BIT      = 0x02,
    REG_TYPE_4X_BIT      = 0x03,
    REG_TYPE_3X          = 0x04,
    REG_TYPE_4X          = 0x05,
    REG_TYPE_3X_DB       = 0x06,
    REG_TYPE_4X_DB       = 0x07,
    REG_TYPE_NULL        = 0xee
}REG_TYPE_INDEX;

/*��ַ���͵�ö�٣�����λ��ַ�������ֵ�ַ*/
typedef enum addrRegType{
    BIT_ADDR_REG = 0x01,            //λ��ַ
    WORT_ADDR_REG = 0x02,           //�ֵ�ַ
    DWORT_ADDR_REG = 0x03,          //˫�ֵ�ַ
    STRING_ADDR_REG = 0x04,         //�ַ�����ַ
    ALL_ADDR_REG = 0x05,            // ���е�ַ
    READ_ADDR_REG = 0x06,           // ����ַ
    WRITE_ADDR_REG = 0x07,          // д��ַ
    OTHER_ADDR_REG_TYE = 0xff
}ADDR_REG_TYPE;

///*���ӿڵĶ���*/
//typedef enum connectType{
//    LOCAL = 0x01,          //�ڲ�
//    COM0 = 0x02,           //����0
//    COM1 = 0x03,           //����1
//    COM2 = 0x04,           //����2
//    COM3 = 0x05,           //����3
//    COM4 = 0x06,           //����4
//    COM5 = 0x07,           //����5
//    NET0 = 0x08,           //����0
//    NET1 = 0x09,           //����1
//    NET2 = 0x10,           //����2
//    NET3 = 0x11,           //����3
//    NET4 = 0x12,           //����4
//    NET5 = 0x13,           //����5
//    OTHER = 0x14           //����
//}CONNECT_TYPE;

/*��ַ��д�����ͣ���ַ��д�����ȼ�*/
typedef enum readWriteComType{
    SCENE_CONTROL_ONCE_W = 0x01,                       // scene Control only write once
    SCENE_CONTROL_LOOP_W = 0x02,                       // scene Control loop write
    GLOBAL_ONCE_W = 0x03,                              // global only write once
    GLOBAL_LOOP_W = 0x04,                              // global loop write
    MACRO_ONCE_W = 0x05,                               // macro only write once
    MACRO_LOOP_W = 0x06,                               // macro loop write
    SCENE_CONTROL_ONCE_R = 0x07,                       // scene Control only read once
    SCENE_CONTROL_LOOP_R = 0x08,                       // scene Control loop read
    ALARM_LOOP_R = 0x09,                               // alarm loop read
    RECIPE_ONCE_R = 0x0a,                              // recipe once read
    GLOBAL_ONCE_R = 0x0b,                              // global only read once
    GLOBAL_LOOP_R = 0x0c,                              // global loop read
    MACRO_ONCE_R = 0x0d,                               // macro only read once
    MACRO_LOOP_R = 0x0e,                               // macro loop read
    DATA_COLLECT_ONCE_R = 0x0f,                        // data collect only read once
    DATA_COLLECT_LOOP_R = 0x10,                        // data collect loop read
    OTHER_CONTROL_TYPE = 0x11                          // other control type
}READ_WRITE_COM_TYPE;

/*��ַ��д��״̬��Ϣ����ʧ����Ϣ*/
typedef enum dataStatusInfo{
    DATA_NORMAL = 0x01,            //��������
    WRITE_FAIL = 0x02,             //д����ʱ��ʧ��
    READ_FAIL = 0x03,              //������ʱ��ʧ��
    WRITE_CHECK_FAIL = 0x04,       //д���غ�У��ʧ��
    READ_CHECK_FAIL = 0x05,        //��ȡ������У��ʧ��
    CMN_FAIL = 0x06,               //ͨ��ʧ�ܣ���������Ƿ���ȷ
    OTHER_STATUS_INFO              //����״̬
}DATA_STATUS_INFO;

/*��һ��ͨ�ŵ�ö�٣������Ƕ���������д������,��Ҫ����ȡ����õĶ�д����ʱ��*/
typedef enum cmnSendType{
    CMN_READ = 0x01,                      //ͨ�Ŷ�����
    CMN_WRITE = 0x02,                     //ͨ��д����
    CMN_READ_BEFORE_WRITE = 0x03,         //д֮ǰ�Ķ�����
    CMN_WRITE_AFTER_READ = 0x04,          //��֮���д����
    CMN_OTHER_TYPE = 0x05                 //������ʽ
}CMN_SEND_TYPE;

/*PLC������ö�٣���վ���Ǵ�վ*/
typedef enum plcFunType{
    PLC_MASTER = 0x01,         //plc��վ
    PLC_SLAVE = 0x02,          //PLC��վ
    PLC_OTHER_TYPE = 0x03      //PLC������ʽ
}PLC_FUN_TYPE;


#endif // ENUMHEAD_H
