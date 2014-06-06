#ifndef DEFINEMACRO_H
#define DEFINEMACRO_H

/********************************************************************
  ���ã������
  ���ߣ�֣����
  ʱ�䣺2010-10-28
********************************************************************/
#define MAX_SCRNCNT 300 //��������

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
Group�б���NAME���Ե�key
������GROUP ͨ��setData(GROUP_NAME_KEY,name)���������ϵ�����
*******************************************************************/
#define GROUP_NAME_KEY 66535

//��dataλ�ñ�����Ͽؼ���������������ͬ�ڻ���item���͵�type
//�� keyֵΪ66536 ��data��������Ͽؼ�����������
#define GROUP_TYPE_KEY 66536

// ���º궨������Ͽؼ�������ֵ
#define GROUP_TYPE_SHAPE 10 // shape���͵����
#define GROUP_TYPE_CTRL  11 // �����ؼ�����shape�����

#endif // DEFINEMACRO_H
