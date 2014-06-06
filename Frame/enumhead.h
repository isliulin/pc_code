#ifndef ENUMHEAD_H
#define ENUMHEAD_H

/*寄存器索引的枚举*/
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

/*地址类型的枚举，比如位地址，比如字地址*/
typedef enum addrRegType{
    BIT_ADDR_REG = 0x01,            //位地址
    WORT_ADDR_REG = 0x02,           //字地址
    DWORT_ADDR_REG = 0x03,          //双字地址
    STRING_ADDR_REG = 0x04,         //字符串地址
    ALL_ADDR_REG = 0x05,            // 所有地址
    READ_ADDR_REG = 0x06,           // 读地址
    WRITE_ADDR_REG = 0x07,          // 写地址
    OTHER_ADDR_REG_TYE = 0xff
}ADDR_REG_TYPE;

///*连接口的定义*/
//typedef enum connectType{
//    LOCAL = 0x01,          //内部
//    COM0 = 0x02,           //串口0
//    COM1 = 0x03,           //串口1
//    COM2 = 0x04,           //串口2
//    COM3 = 0x05,           //串口3
//    COM4 = 0x06,           //串口4
//    COM5 = 0x07,           //串口5
//    NET0 = 0x08,           //网口0
//    NET1 = 0x09,           //网口1
//    NET2 = 0x10,           //网口2
//    NET3 = 0x11,           //网口3
//    NET4 = 0x12,           //网口4
//    NET5 = 0x13,           //网口5
//    OTHER = 0x14           //其他
//}CONNECT_TYPE;

/*地址读写的类型，地址读写的优先级*/
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

/*地址读写的状态信息，或失败信息*/
typedef enum dataStatusInfo{
    DATA_NORMAL = 0x01,            //数据正常
    WRITE_FAIL = 0x02,             //写数据时候失败
    READ_FAIL = 0x03,              //读数据时候失败
    WRITE_CHECK_FAIL = 0x04,       //写返回后校验失败
    READ_CHECK_FAIL = 0x05,        //读取的数据校验失败
    CMN_FAIL = 0x06,               //通信失败，检查连线是否正确
    OTHER_STATUS_INFO              //其他状态
}DATA_STATUS_INFO;

/*这一次通信的枚举，比如是读操作还是写操作等,主要用于取打包好的读写数据时用*/
typedef enum cmnSendType{
    CMN_READ = 0x01,                      //通信读操作
    CMN_WRITE = 0x02,                     //通信写操作
    CMN_READ_BEFORE_WRITE = 0x03,         //写之前的读操作
    CMN_WRITE_AFTER_READ = 0x04,          //读之后的写操作
    CMN_OTHER_TYPE = 0x05                 //其他方式
}CMN_SEND_TYPE;

/*PLC的类型枚举，主站还是从站*/
typedef enum plcFunType{
    PLC_MASTER = 0x01,         //plc主站
    PLC_SLAVE = 0x02,          //PLC从站
    PLC_OTHER_TYPE = 0x03      //PLC其他方式
}PLC_FUN_TYPE;


#endif // ENUMHEAD_H
