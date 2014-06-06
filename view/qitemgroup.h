#ifndef QITEMGROUP_H
#define QITEMGROUP_H
#include <view/graphicsitemsamext.h>
#include <QtSql/QSqlDatabase>
#include "qsimpletextitem.h"
#include "qrectitem.h"

struct securityPro;

class QItemGroup : public GraphicsItemGroupSamExt
{
public:
    QItemGroup(QGraphicsItem *parent = 0);
    enum { Type = UserType + 23 };
    int type() const { return Type;}

    enum { gType = SAM_DRAW_GROUP_USER };
    virtual int GroupType();//�ؼ�����


    virtual QGraphicsItem *Clone();//����item

    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,
                               QWidget *widget);

    virtual void compile(QSqlDatabase &db, int nSceneId,int &count,int index);//�����ʱ�򱣴�item�����ݿ�

    virtual void save(QDataStream &stream);//��item����������

    virtual void load(QDataStream &stream);//������������item

    virtual void SetText(QString text);
    virtual void SetFontSize(int nFontSize);
    virtual void SetFontName(QString sName); //������������
    virtual void SetTextAlign(int nAlignType);

    virtual void SetPicture(QString path,EITEM_TYPE blib,int alpha = 255,QColor color = QColor(0,0,0));

    virtual void SaveSecurityPro(securityPro *pro);

    virtual QGraphicsItem* GetTextItem();

    virtual QGraphicsItem* GetPicItem();
    virtual QList<Keyboard> getAddress();
    virtual void setAddress(QList<Keyboard> addr);

    virtual void SetBold(bool flag);
    virtual void SetItalic(bool flag);
    virtual void SetUnderLine(bool flag);
    virtual void SetTextColor(QColor color);

    virtual void redrawForChangeLanguage(int index);
    virtual void changeItemLanguageAttr(int lanNum);
    virtual void redrawForChangeStatus(int index, int lan);
    virtual int  getCurrentState();
	virtual int  checkMacroName(QString &msg);
    virtual QString  getItemName();
    virtual QStringList getItemStates();
	virtual QStringList getAllFonts();
	virtual void sampChanged(QString oldName,QString newName,int sampType);
	QString bitShot();

    virtual QVector<ADDRPRO> getAllItemAddr();

    virtual TEXTPRO getAllItemText();
    virtual void replaceAllItemText(int iLan,int iSta,QString sNewText);

public:
    QRectItem * frameRect;
    QGraphicsItem *backItem;
    QGraphicsItem *textItem;
    /*
public:
    void saveEx(QDataStream &stream);//wxyר�������Զ�����ϵĵ��롢���
    void loadEx(QDataStream &stream);
    QGraphicsItem *CloneEx();
    */
};

#endif // QITEMGROUP_H
