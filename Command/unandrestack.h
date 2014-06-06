#ifndef UNANDRESTACK_H
#define UNANDRESTACK_H
#include "View/samdrawscene.h"
#include <QUndoCommand>
void update_edgepoints(SamDrawScene  *,QGraphicsItem * );
class pasteCommand: public QUndoCommand //粘贴ITEM到场景的撤销和删除
{
public:
       pasteCommand(SamDrawScene *samdrawscene,QList<QGraphicsItem *> pastItems,bool bflag=true);
       void undo();
       void redo();
private:
       QList<QGraphicsItem *> myDiagramItems;
       SamDrawScene           *myGraphicsScene;
       bool                   b_flag;
};

class groupCommand: public QUndoCommand //组合的撤销和恢复
{
public:
    groupCommand(SamDrawScene *samdrawscene);
    void undo();
    void redo();
private:
       QList<QGraphicsItem *> selectedChildItems;
       QGraphicsItem    *selectedItem;
       QItemGroup        *selectedGroup;
       SamDrawScene           *myGraphicsScene;
};

class disgroupCommand: public QUndoCommand //拆分的撤销和恢复
{
public:
    disgroupCommand(SamDrawScene *samdrawscene);
    void undo();
    void redo();
private:
       QList<QGraphicsItem *>    selectedlist;
       QList<QGraphicsItem *> disgroupCommand_childitemList;
       SamDrawScene           *myGraphicsScene;
       QItemGroup * selectedGroup;
       qreal z;
};

class addItemToScence: public QUndoCommand  //控件新建的撤销和恢复
{
public:
    addItemToScence(SamDrawScene *samdrawscene,QGraphicsItem *pItem,bool bflag=true);
    void redo();
    void undo();
private:
    SamDrawScene *myGraphicsScene;
    QGraphicsItem *pAddItem;
    bool         b_flag;
};

class cutItemCommand: public QUndoCommand //剪切的撤销和恢复
{
public :
        cutItemCommand(SamDrawScene *samdrawscene,QList<QGraphicsItem *>,bool bflag=true);
        void redo();
        void undo();
private:
        SamDrawScene *myGraphicsScene;
        QList<QGraphicsItem *> CutItemList;
        bool         b_flag;
};

class zValueDownChangeCommand: public QUndoCommand ////当前控件item下移一层的撤销和恢复
{
public :
       zValueDownChangeCommand(SamDrawScene * samdrawscene);
       void redo();
       void undo();
private :
        SamDrawScene *myGraphicsScene;
        QGraphicsItem *  pSelectItem;
        QMap<QGraphicsItem *,qreal> oder;
};

class zValueUpChangeCommand: public QUndoCommand //当前控件item下移一层的撤销和恢复
{
public :
       zValueUpChangeCommand(SamDrawScene * samdrawscene);
       void redo();
       void undo();
private :
        SamDrawScene *myGraphicsScene;
        QGraphicsItem *  pSelectItem;
        QMap<QGraphicsItem *,qreal> oder;
};

class bringtopCommand: public QUndoCommand //当前控件item移到顶层的撤销和恢复
{
public:
    bringtopCommand(SamDrawScene * samdrawscene);
    void redo();
    void undo();
    qreal   nVal;
private :
     SamDrawScene * myGraphicsScene;
     QGraphicsItem *  pSelectItem;
     QMap<QGraphicsItem *,qreal> oder;
};

class bringBottomCommand: public QUndoCommand //当前控件item移到底层的撤销和恢复
{
public:
    bringBottomCommand(SamDrawScene * samdrawscene);
    void redo();
    void undo();
     qreal   nVal;
private :
     SamDrawScene * myGraphicsScene;
     QGraphicsItem *  pSelectItem;
     QMap<QGraphicsItem *,qreal> oder;
};

class multiCopyCommand: public QUndoCommand  //多重复制
{
public :
        multiCopyCommand(SamDrawScene *samdrawscene,QList<QGraphicsItem *>,QGraphicsItem *,bool bflag=true);
        void redo();
        void undo();
private:
        SamDrawScene *myGraphicsScene;
        QList<QGraphicsItem *> addList;
        QGraphicsItem *  pSelectItem;
        bool         b_flag;
};

class ModifyBaseItemCommand: public QUndoCommand  //修改基本图形
{
public :
        ModifyBaseItemCommand(SamDrawScene *samdrawscene,QGraphicsItem *oldItem,QGraphicsItem *newItem);
        void redo();
        void undo();
private:
        SamDrawScene *Scene;
        QGraphicsItem * oItem;
        QGraphicsItem * nItem;
        qreal z;
        //bool         b_flag;
};

class ModifyItemsCommand: public QUndoCommand  //修改基本图形
{
public :
        ModifyItemsCommand(SamDrawScene *samdrawscene,QList<bool>selValues,
                           QList<QGraphicsItem *>oldItems,QList<QGraphicsItem *>newItems);
        void redo();
        void undo();
private:
        SamDrawScene *Scene;
        QList<QGraphicsItem *>oItems;
        QList<QGraphicsItem *>nItems;
        QList<bool>values;
        //qreal z;
        bool         b_flag;
};

class AddSceneCommand: public QUndoCommand //新建、复制画面
{
public:
    AddSceneCommand(SamDrawScene *samdrawscene, int iActiveSheetIndex, int iTreeIndex, bool bflag = true);
    void redo();
    void undo();
private:
    SamDrawScene* Scene;
    int m_iActiveSheetIndex;
    int m_iTreeIndex;
    bool m_bFlag;
};

class DeleteSceneCommand: public QUndoCommand //删除画面
{
public:
    DeleteSceneCommand(SamDrawScene *samdrawscene, int iActiveSheetIndex, int iTreeIndex, bool bflag = true);
    void redo();
    void undo();
private:
    SamDrawScene* Scene;
    int m_iActiveSheetIndex;
    int m_iTreeIndex;
    bool m_bFlag;
};

class AddWindowCommand: public QUndoCommand//新建、复制窗口
{
public:
    AddWindowCommand(SamDrawScene *samdrawscene, int iActiveSheetIndex, int iTreeIndex, bool bflag = true);
    void redo();
    void undo();
private:
    SamDrawScene* Scene;
    int m_iActiveSheetIndex;
    int m_iTreeIndex;
    bool m_bFlag;
};

class DeleteWindowCommand: public QUndoCommand//删除窗口
{
public:
    DeleteWindowCommand(SamDrawScene *samdrawscene, int iActiveSheetIndex, int iTreeIndex, bool bflag = true);
    void redo();
    void undo();
private:
    SamDrawScene* Scene;
    int m_iActiveSheetIndex;
    int m_iTreeIndex;
    bool m_bFlag;
};

class AddKeyBoardCommand: public QUndoCommand//新建键盘
{
public:
    AddKeyBoardCommand(SamDrawScene *samdrawscene, int iActiveSheetIndex, int iTreeIndex, QString strNum, bool bflag = true);
    void redo();
    void undo();
private:
    SamDrawScene* Scene;
    int m_iActiveSheetIndex;
    int m_iTreeIndex;
    bool m_bFlag;
    QString m_strNum;
};

class DeleteKeyBoardCommand: public QUndoCommand//删除键盘
{
public:
    DeleteKeyBoardCommand(SamDrawScene *samdrawscene, int iActiveSheetIndex, int iTreeIndex, QString strNum, bool bflag = true);
    void redo();
    void undo();
private:
    SamDrawScene* Scene;
    int m_iActiveSheetIndex;
    int m_iTreeIndex;
    bool m_bFlag;
    QString m_strNum;
};

class tableMovedCommand: public QUndoCommand //剪切的撤销和恢复
{
public :
        tableMovedCommand(SamDrawScene *samdrawscene,QGraphicsItem *movedItem,QList<QRectF >nRects,QList<QRectF> oRects,bool bflag = true);
        void redo();
        void undo();
private:
        SamDrawScene *Scene;
        QGraphicsItem * m_movedItem;
        QList<QRectF > nItemRects;
        QList<QRectF > oItemRects;
        bool         b_flag;
};
#endif // UNANDRESTACK_H
