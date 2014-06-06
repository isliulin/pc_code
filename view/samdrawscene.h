/********************************************************************
  ���ã������������࣬���л�ͼ�������ڴ�����д
  ���ߣ�֣����
  ʱ�䣺2010-10-28
********************************************************************/

#ifndef SAMDRAWSCENE_H
#define SAMDRAWSCENE_H

#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include <QKeyEvent>
//#include "HeadFile/DefineGlobalVariable.h" //ȫ�ֱ�������ͷ�ļ�
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
    bool    bShowMiddle;               //�Ƿ���ʾ������
    bool    bShowOtherPos;             //��ʾ�������ط�
    bool    bUseTitleStr;              //�Ƿ���Ҫ����
    bool    bUseCloseBtn;              //�Ƿ���Ҫ�رհ�ť
    quint8  nIsSceneOrWindow;          //0���ǻ��棬1���Ǵ���
    QString sNewScreenName;            //�½����������
    QString sTitleStr;                 //����
    QPoint  mWindownShowPos;           //�������ڵ�λ��
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

public://���ڻ�������
    //��������
    QString sNewScreenName;     //sNewScreenName---���������
    QString sNumberName;        //�������
    quint8  nIsSceneOrWindow;   //nIsSceneOrWindow---0���ǻ��棬1���Ǵ��ڣ�2 ���Զ������
    QString m_picturePath;      //m_picturePath---����ͼƬ·��
    QColor  m_sceneBackColor;   //m_sceneBackColor---��ͼ������ɫ
    QColor  m_sceneStyleColor;  //m_sceneStyleColor---ǰ��ɫ
    int     nSelectType;        //nSelectType---ѡ�񱳾���ʽ������ɫ����ͼƬ
    int     nPattern;           //nPattern---������ʽ
    bool    bLogout;            //�뿪�����Զ�ע��
    QList<SCRIPT_PROP> listScript;//���нű�
    //list items;//���пؼ�

    //��������
    bool    bIsAddMenu;         //---�Ƿ���뻭��˵�
    bool    bSlide;             //---�Ƿ�����������ת
    int     nTowardLeftId;      //---����id��ûѡ��Ϊ0
    int     nTowardRIghtId;     //---����id��ûѡ��Ϊ0
    int     nSlideStyle;        //---�л�Ч��

    //��������
    bool    bShowMiddle;        //bShowMiddle---�Ƿ���ʾ������
    bool    bshowTitle;         //�Ƿ���ʾ���ڱ���
    QPoint  mWindownShowPos;    //mWindownShowPos---����λ��
    QRectF  m_sceneRect;        //m_sceneRect---��ͼ��С

    /*bool    bShowMiddle;      //�Ƿ���ʾ������
    bool    bShowOtherPos;    //��ʾ�������ط�
    bool    bUseTitleStr;     //�Ƿ���Ҫ����
    bool    bUseCloseBtn;     //�Ƿ���Ҫ�رհ�ť
    quint8  nIsSceneOrWindow; //0���ǻ��棬1���Ǵ���
    QString sNewScreenName;   //�½����������
    QString sTitleStr;        //����
    QPoint  mWindownShowPos;  //�������ڵ�λ��
    QRectF  m_sceneRect;      //��ͼ��С
    QColor  m_sceneBackColor; //��ͼ������ɫ
    QColor  m_sceneStyleColor;//��ͼ��ʽ��ɫ��������ɫ�õ�
    int     nSelectType;      //ѡ�񱳾���ʽ������ɫ����ͼƬ
    int     nPattern;         //������ʽ
    QString m_picturePath;    //ͼƬ·��*/

public:
    void SetPattern(QPainter *painter); //add by tanghaiguo
    void setSceneRect(qreal x, qreal y, qreal w, qreal h);
    void upDate_stutas();//����״̬��
    //void deleteSamItem(QGraphicsItem *pItem);
    //end add by tanghaiguo
    QList<QGraphicsItem *> loadItems(QDataStream &stream);
    QList<QGraphicsItem *> TopItems();//ȡ�����е�����Item������������е�Item��8��С����
    void reBondingTrackers(bool bKeepSelected = false);
    QGraphicsSceneMouseEvent *mouse_Event;
    void setNewItem_ID(QGraphicsItem *,QGraphicsItem *);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void setStatus_LineValue(QGraphicsItem *);//����״̬���༭���ֵ
    void DrawScreenSize();//���ü��̴�С
    void load(QDataStream &stream, SamDrawScene *pScene);//ͼ���ļ�����ʹ�����load
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
    QList<QRectF>           oItemRects;//�ƶ�ǰ��item ��rect
    bool                    bIsLibrary; //��ʾ�Ƿ�ͼ�ⳡ�� false��ͼ��  true:��ͨ����

public:
    QPointF startPos;
    QPointF MousePressPos; //��갴���ڳ����е�����
    QPointF MouseReleasePos; //��갴���ڳ����е�����
    QPointF LastMousePoint;//��¼����ƶ���λ��
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
    //�����ı���
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
    QList<QGraphicsItem *> parentItem_list;//ճ��ʱ�ĸ�Item
    /*****************************************************
    * set the base graphic Mirror
    *****************************************************/
    void  SetBaseItemMirror(int nType);
    QList <QGraphicsItem *> pasteList;//ճ����ITEM
    bool  is_paste_singleItem;//��ճ�����Ƿ���ϵ�Item
	
public slots:
    void selItemsChanged();
    void multiStatus();
    void Thing_property();//�ؼ�������
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

    QGraphicsItem *pAniMageItam;          //��¼����ͼƬָ��
//�����������϶����ʹ�õı���
    int iVHFlag;                                      //��¼���ƶ�ˮƽ���Ǵ�ֱ�ߣ�1Ϊ�ƶ���ֱ�ߣ�2Ϊ�ƶ�ˮƽ��
    QRectF TabeRect;                            //��¼���Ĵ�С
    QGraphicsItem *pTableItam;          //��¼���ƶ����ָ��
    bool bMoveFlag;                     //��¼���ƶ�����Ƿ�����
    QLineItem *pTableLine;                  //��¼�ƶ��ߵ�ָ��

    QVector<TablePro> vVLine;              //�����洹ֱ�ߵ�����
    QVector<TablePro> vHLine;             //������ˮƽ�ߵ�����
    QVector<TablePro> vTileTex;            //���������к����ı�������
    QGraphicsItem *pBackItam;           //�����������������ο�ָ��
    QGraphicsItem *pRecipeItem ;       //�����䷽��ʾ���б��ⱳ�����ο�ָ��
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
