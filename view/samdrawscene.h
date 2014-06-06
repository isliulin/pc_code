/********************************************************************
  作用：场景的派生类，所有绘图操作都在此类中写
  作者：郑启红
  时间：2010-10-28
********************************************************************/

#ifndef SAMDRAWSCENE_H
#define SAMDRAWSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QKeyEvent>
//#include "HeadFile/DefineGlobalVariable.h" //全局变量定义头文件
#include "view/qelipseitem.h"
#include "view/qlineitem.h"
#include "view/qrectitem.h"
#include <QGraphicsItem>
#include "view/samdrawitembase.h"
#include "view/samdrawtool.h"
//#include "Frame/enumhead.h"
//#include "Frame/structHead.h"
#include "Frame/qprogectmanager.h"

/*typedef struct sceneTypeProp{
    bool    bShowMiddle;               //是否显示在正中
    bool    bShowOtherPos;             //显示在其他地方
    bool    bUseTitleStr;              //是否需要标题
    bool    bUseCloseBtn;              //是否需要关闭按钮
    quint8  nIsSceneOrWindow;          //0：是画面，1：是窗口
    QString sNewScreenName;            //新建画面的名字
    QString sTitleStr;                 //标题
    QPoint  mWindownShowPos;           //窗口现在的位置
}SCENE_TYPE_PROP;*/

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
//class MainWindow
QT_END_NAMESPACE

typedef struct _scriptPro_
{
    QString  scriptName;
    QString  scriptFuncName;
    int      scriptFreq;
    int      scriptCount;
    short    scriptType;
    Keyboard scriptAddr;
    int      scriptCondition;
    bool     scriptBShow;
}SCRIPT_PROP;

class TablePro
{
public:
    QGraphicsItem *pItem;
    QPointF pos;
    bool bMark;
};

extern SamDrawSelectTool m_selectTool;

class SamDrawScene : public QGraphicsScene
{
    Q_OBJECT

public:
    SamDrawScene(QObject *parent = 0);
    ~SamDrawScene();

public:
    QGraphicsPathItem*   pSelectOutline;
    QPointF              roateStartPoint;
    QPointF              qpoint;
    QVector<qreal>       m_pressVale;
    bool                 bMousePress;
    bool                 m_bChangePicPath;
    QImage               m_backPicPixmap;

public://窗口画面属性
    //公共属性
    QString sNewScreenName;     //sNewScreenName---画面的名字
    QString sNumberName;        //编号名字
    quint8  nIsSceneOrWindow;   //nIsSceneOrWindow---0：是画面，1：是窗口，2 是自定义键盘
    QString m_picturePath;      //m_picturePath---背景图片路径
    QColor  m_sceneBackColor;   //m_sceneBackColor---视图背景颜色
    QColor  m_sceneStyleColor;  //m_sceneStyleColor---前景色
    int     nSelectType;        //nSelectType---选择背景方式，背景色还是图片
    int     nPattern;           //nPattern---背景样式
    bool    bLogout;            //离开画面自动注销
    QList<SCRIPT_PROP> listScript;//所有脚本
    //list items;//所有控件

    //画面属性
    bool    bIsAddMenu;         //---是否加入画面菜单
    bool    bSlide;             //---是否启动滑动跳转
    int     nTowardLeftId;      //---向左id，没选择为0
    int     nTowardRIghtId;     //---向右id，没选择为0
    int     nSlideStyle;        //---切换效果

    //窗口属性
    bool    bShowMiddle;        //bShowMiddle---是否显示在正中
    bool    bshowTitle;         //是否显示窗口标题
    QPoint  mWindownShowPos;    //mWindownShowPos---所在位置
    QRectF  m_sceneRect;        //m_sceneRect---视图大小

    /*bool    bShowMiddle;      //是否显示在正中
    bool    bShowOtherPos;    //显示在其他地方
    bool    bUseTitleStr;     //是否需要标题
    bool    bUseCloseBtn;     //是否需要关闭按钮
    quint8  nIsSceneOrWindow; //0：是画面，1：是窗口
    QString sNewScreenName;   //新建画面的名字
    QString sTitleStr;        //标题
    QPoint  mWindownShowPos;  //窗口现在的位置
    QRectF  m_sceneRect;      //视图大小
    QColor  m_sceneBackColor; //视图背景颜色
    QColor  m_sceneStyleColor;//视图样式颜色，做过渡色用的
    int     nSelectType;      //选择背景方式，背景色还是图片
    int     nPattern;         //背景样式
    QString m_picturePath;    //图片路径*/

public:
    void SetPattern(QPainter *painter); //add by tanghaiguo
    void setSceneRect(qreal x, qreal y, qreal w, qreal h);
    void upDate_stutas();//更新状态栏
    //void deleteSamItem(QGraphicsItem *pItem);
    //end add by tanghaiguo
    QList<QGraphicsItem *> loadItems(QDataStream &stream);
    QList<QGraphicsItem *> TopItems();//取得所有单个的Item，不包括组合中的Item和8个小矩形
    void reBondingTrackers(bool bKeepSelected = false);
    QGraphicsSceneMouseEvent *mouse_Event;
    void setNewItem_ID(QGraphicsItem *,QGraphicsItem *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void setStatus_LineValue(QGraphicsItem *);//设置状态栏编辑框的值
    void DrawScreenSize();//设置键盘大小
    void load(QDataStream &stream, SamDrawScene *pScene);//图库文件加载使用这个load
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent ( QGraphicsSceneWheelEvent * wheelEvent );
    //void keyPressEvent(QKeyEvent *event);
    virtual void drawBackground(QPainter *painter, const QRectF &rect); //add by tanghaiguo
    void mousePressEventForUndo(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEventForUndo(SamDrawScene *scene,QGraphicsSceneMouseEvent *event);
    void SamDrawSceneForUndo(void);
    void SamDrawScene_rightMenu(QGraphicsSceneMouseEvent *mouseEvent);

signals:
    void itemsMoved(SamDrawScene *scene,QList <QGraphicsItem *> movingItems,QList <QPointF >oldPoss);
    void itemResize(SamDrawScene *scene,QGraphicsItem * resizeItem,QSizeF oldSize,QPointF oldPos);
    void lineItemDrag(SamDrawScene *scene,QGraphicsItem * item,QPainterPath oldPath,QPainterPath newPath);
    void polygonDrag(SamDrawScene *scene,QGraphicsItem * item,QPolygonF oldPolygon,QPolygonF newPolygon);
    void key_paste(QGraphicsItem *,QGraphicsItem *);

public:
    QGraphicsItem*  movingItem;
    QPointF         oldPos;
    QPointF         oldMousePoint;
    QPointF         newMousePoint;
    QPainterPath    oldPath;
    QPainterPath    newPath;
    QPolygonF       oldPolygon;
    QPolygonF       newPolygon;
    bool            bResize;
    bool            bMove;
    QSizeF          oldSize;

public:
    QList<QGraphicsItem*>   movingItems;
    QList<QLineItem*>       pShowLineItems;
    QList<QPointF>          oldPoss;
    QList<QPointF>          newPoss;
    QList<QRectF>           oItemRects;//移动前子item 的rect
    bool                    bIsLibrary; //表示是否图库场景 false：图库  true:普通场景

public:
    QPointF startPos;
    QPointF MousePressPos; //鼠标按下在场景中的坐标
    QPointF MouseReleasePos; //鼠标按下在场景中的坐标
    QPointF LastMousePoint;//记录鼠标移动的位置
    QPointF CurMousePoint;
    QPointF prMousePoint;

    inline void setTopOrder(qreal dZvalue)
    {
        m_dTopZValue = dZvalue;
    }

public:
    QGraphicsItemGroup* createItemGroup(const QList<QGraphicsItem *> &items);
    QGraphicsItem* loadItemFromStream(QDataStream &stream,int type);
    void actionCopy();
    void actionCut();
    void actionPaste();
    void GroupItem();
    void DisGroupItem();
    void addItem(QGraphicsItem *item, qreal zValue = -1);
    void ResetOder(QGraphicsItem *item,int op);
    void sendSelectionChangeSignal(void);
    QGraphicsItem * ItemSelected();
    QGraphicsItem * TopmostParentItem (QGraphicsItem * item);
    void removeItem(QGraphicsItem *item);
    bool event ( QEvent * event ) ;
    /*Get & set top Zvalue in current scene*/
    qreal getTopOrder();
    void OnOderTop();
    void OnOderBotton();
    void OnOderUp();
    void OnOderDown();
    //场景的编译
    bool compile(QSqlDatabase &db, int nSceneId, int &count);
    void compileScreen(int &count, QSqlDatabase &db, int nSceneId);
    void compileWindow(int &count, QSqlDatabase &db, int nSceneId);
    void compileKeyboard(QSqlDatabase &db, int nSceneId);
    void compileItem(QGraphicsItem* pItem,QSqlDatabase &db, int nSceneId,int &count,int index);
    void addCollidItems(QGraphicsItem* pItem,QList <QGraphicsItem *> &list);
    void SetSelectFlag(QGraphicsItem* pItem,bool flag);
    bool GetSelectFlag(QGraphicsItem* pItem);
    QList<QGraphicsItem*> SDCollidItems(QGraphicsItem *pItem);
    //void save(QDataStream &stream);//save
    //void load(QDataStream &stream);//load
    /*****************************************************
    * set the graphic alignment
    *****************************************************/
    void OnSetLeftAlign();
    void OnSetRightAlign();
    void OnSetTopAlign();
    void OnSetButtomAlign();
    void OnSetHCenterAlign();
    void OnSetVCenterAlign();
    void OnSetHSpacingAlign();
    void OnSetVSpacingAlign();
    /*****************************************************
    * set the graphic same width/height/all
    *****************************************************/
    void setWidthSame();
    void setHeightSame();
    void setWidthHeightSame();
    QGraphicsItem *getTheLeftmostItem();
    QList<QGraphicsItem *> parentItem_list;//粘贴时的父Item
    /*****************************************************
    * set the base graphic Mirror
    *****************************************************/
    void  SetBaseItemMirror(int nType);
    QList <QGraphicsItem *> pasteList;//粘贴的ITEM
    bool  is_paste_singleItem;//当粘贴的是非组合的Item
	
public slots:
    void selItemsChanged();
    void multiStatus();
    void Thing_property();//控件的属性
    void Onkey_paste(QGraphicsItem *,QGraphicsItem *);

signals:
    void DoubleClickItem(QGraphicsItem *item);
    void SingleClickItem();//QGraphicsItem *item
    void Messageout(QString str, MSG_TYPE eType, MsgOutPut* pOutPut);
private:
    qreal m_dTopZValue;
    QVector <QGraphicsItem *> m_qvecPrimaryItems;
	
    friend QDataStream &operator<<(QDataStream &stream, SamDrawScene *pScene);
    friend QDataStream &operator>>(QDataStream &stream, SamDrawScene *pScene);

    QGraphicsItem *pAniMageItam;          //记录动画图片指针
//以下是用于拖动表格使用的变量
    int iVHFlag;                                      //记录是移动水平还是垂直线，1为移动垂直线，2为移动水平线
    QRectF TabeRect;                            //记录表格的大小
    QGraphicsItem *pTableItam;          //记录待移动表格指针
    bool bMoveFlag;                     //记录待移动表格是否锁定
    QLineItem *pTableLine;                  //记录移动线的指针

    QVector<TablePro> vVLine;              //用来存垂直线的数据
    QVector<TablePro> vHLine;             //用来存水平线的数据
    QVector<TablePro> vTileTex;            //用来存表格中含有文本的数据
    QGraphicsItem *pBackItam;           //用来标题栏背景矩形框指针
    QGraphicsItem *pRecipeItem ;       //用来配方显示器列标题背景矩形框指针
    void mousePressMove();
    void moveLineWhenMouseMove();
    void setTextPosVWhenMouseMove(qreal mMoveX,int index,int isize);
    void setTextPosHWhenMouseMove(qreal mMoveY,int index,int isize);
};

class LibRaryScene : public QGraphicsScene
{
    Q_OBJECT

public:
    LibRaryScene(QObject *parent = 0);
    ~LibRaryScene();

public:
    QGraphicsItem * TopmostParentItem (QGraphicsItem * item);

signals:
    void DoubleClickItem(QGraphicsItem *item);
    void SingleClickItem();//QGraphicsItem *item

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SAMDRAWSCENE_H
