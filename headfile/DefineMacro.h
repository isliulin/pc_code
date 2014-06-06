#ifndef DEFINEMACRO_H
#define DEFINEMACRO_H

/********************************************************************
  作用：定义宏
  作者：郑启红
  时间：2010-10-28
********************************************************************/
#define MAX_SCRNCNT 300 //画面总数

/* QGraphicsItem::UserType */
#define Qt_USER_TYPE_BASE 65536

/* Sam draw 3.4 item object type define */
enum eSamDrawObjQtType
{
    SAM_DRAW_OBJECT_RECT     = Qt_USER_TYPE_BASE + 15,
    SAM_DRAW_OBJECT_ELIPSE   = Qt_USER_TYPE_BASE + 16,
    SAM_DRAW_OBJECT_LINE     = Qt_USER_TYPE_BASE + 17,
    SAM_DRAW_OBJECT_POLYGON  = Qt_USER_TYPE_BASE + 18,
    SAM_DRAW_OBJECT_FOLDLINE = Qt_USER_TYPE_BASE + 19,
    SAM_DRAW_OBJECT_FREELINE = Qt_USER_TYPE_BASE + 20,
    SAM_DRAW_OBJECT_ARCLINE  = Qt_USER_TYPE_BASE + 21,
    SAM_DRAW_OBJECT_TEXT     = Qt_USER_TYPE_BASE + 22,
    SAM_DRAW_OBJECT_GROUP    = Qt_USER_TYPE_BASE + 23,
    SAM_DRAW_OBJECT_TRACKER  = Qt_USER_TYPE_BASE + 999,
    SAM_DRAW_OBJECT_QT_TYPE_BUTT
};
typedef enum eSamDrawObjQtType SAM_DRAW_OBJECT_TYPE_E;

/*******************************************************************
Group中保存NAME属性的key
即对于GROUP 通过setData(GROUP_NAME_KEY,name)来保存该组合的名字
*******************************************************************/
#define GROUP_NAME_KEY 66535

//该data位置保存组合控件的类型描述，不同于基本item类型的type
//即 key值为66536 的data区保存组合控件的类型描述
#define GROUP_TYPE_KEY 66536

// 以下宏定义了组合控件的类型值
#define GROUP_TYPE_SHAPE 10 // shape类型的组合
#define GROUP_TYPE_CTRL  11 // 基本控件，即shape的组合

#endif // DEFINEMACRO_H
