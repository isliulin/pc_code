#ifndef UNANDRESTACK_H
#define UNANDRESTACK_H
#include "View/samdrawscene.h"
#include <QUndoCommand>
void update_edgepoints(SamDrawScene  *,QGraphicsItem * );
class pasteCommand: public QUndoCommand //ճ��ITEM�������ĳ�����ɾ��
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

class groupCommand: public QUndoCommand //��ϵĳ����ͻָ�
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

class disgroupCommand: public QUndoCommand //��ֵĳ����ͻָ�
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

class addItemToScence: public QUndoCommand  //�ؼ��½��ĳ����ͻָ�
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

class cutItemCommand: public QUndoCommand //���еĳ����ͻָ�
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

class zValueDownChangeCommand: public QUndoCommand ////��ǰ�ؼ�item����һ��ĳ����ͻָ�
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

class zValueUpChangeCommand: public QUndoCommand //��ǰ�ؼ�item����һ��ĳ����ͻָ�
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

class bringtopCommand: public QUndoCommand //��ǰ�ؼ�item�Ƶ�����ĳ����ͻָ�
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

class bringBottomCommand: public QUndoCommand //��ǰ�ؼ�item�Ƶ��ײ�ĳ����ͻָ�
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

class multiCopyCommand: public QUndoCommand  //���ظ���
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

class ModifyBaseItemCommand: public QUndoCommand  //�޸Ļ���ͼ��
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

class ModifyItemsCommand: public QUndoCommand  //�޸Ļ���ͼ��
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

class AddSceneCommand: public QUndoCommand //�½������ƻ���
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

class DeleteSceneCommand: public QUndoCommand //ɾ������
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

class AddWindowCommand: public QUndoCommand//�½������ƴ���
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

class DeleteWindowCommand: public QUndoCommand//ɾ������
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

class AddKeyBoardCommand: public QUndoCommand//�½�����
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

class DeleteKeyBoardCommand: public QUndoCommand//ɾ������
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

class tableMovedCommand: public QUndoCommand //���еĳ����ͻָ�
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
