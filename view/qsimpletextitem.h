/********************************************************************
������QSimpleTextItem
���ã������ı��Ļ���
���ߣ�֣����
ʱ�䣺2010-11-9
********************************************************************/
#ifndef QSIMPLETEXTITEM_H
#define QSIMPLETEXTITEM_H

#include <QGraphicsItem>
#include <QRectF>
#include <QString>
#include <QColor>
#include <QBrush>
#include <QLinearGradient>
#include <QRadialGradient>
#include "view/graphicsitemsamext.h"

class QSimpleTextItem : public GraphicsSimpleTextItemSamExt
{
public:
    QSimpleTextItem();
    QSimpleTextItem(QString sText);
    QSimpleTextItem(QRectF Rect,QString sText);

    enum { Type = UserType + 22 };
    int type() const	{ return Type; }

public:
    QRectF m_rect;           //�������δ�С
    QString sTEXT;           //�ı�
    QColor m_FontColor;      //������ɫ
    QColor m_RectBackColor;  //���ο�ı���ɫ
    QColor m_RectFrontColor; //���ο��ǰ��ɫ
    int m_Alianment;         //�ı��Ķ��뷽ʽ
    Qt::Alignment AlianmentFlag; //�ı��Ķ��뷽ʽ
    QBrush m_brush;              //�������λ�ˢ
    QLinearGradient m_gradient;    //���Թ���ɫ����
    QRadialGradient m_radial;      //���ǹ���ɫ����
    int nPtternType;             //ѡ����ʽ������
    bool m_RectOutLine;          //�������ο��Ƿ��б���
    QColor m_RectOutLineColor;   //�������ο�ɫ��ɫ
    int m_LineInterval;          //�о�

public:
    virtual QRectF boundingRect() const
    {
        return m_rect;
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void InitParameters();

    void SetName(QString sName);
    QString GetName();

    void SetID(int nID);
    int GetID();

    void SetText(QString sText);
    QString GetText();

    void SetFontColor(QColor color);
    QColor GetFontColor();

    void SetRectBackColor(QColor color);
    QColor GetRectBackColor();

    void SetRectFrontColor(QColor color);
    QColor GetRectFrontColor();

    void SetAlpha(int nAlpha);
    int GetAlpha();

    void SetFontSize(int nFontSize);
    int GetFontSize();

    void SetFontName(QString sName);
    QString GetFontName();

    void SetFontBold(bool nFlag);
    bool GetFontBold();

    void SetFontItalic(bool nFlag);
    bool GetFontItalic();

    void SetFontUnderLine(bool nFlag);
    bool GetFontUnderLine();

    void SetFontWordInterval(int nInterval);
    int GetFontWordInterval();

    void SetTextAlign(int nAlignType);
    int GetTextAlign();

    void SetPattern(int nType);
    int GetPattern();

    void SetRectOutLine(bool nFlag);
    bool GetRectOutLine();

    void SetRectOutLineColor(QColor color);
    QColor GetRectOutLineColor();

    void SetLineInterval(int nInterval);
    int GetLineInterval();

    void SetWidth(int nWidth);
    int GetWidth();

    void SetHeight(int nHeight);
    int GetHeight();

    void SetDescription(QStringList sText);
    QStringList GetDescription();

	QFont GetTextFont();

    void setRect(const QRectF &qrcRect);
    QSimpleTextItem* Clone();

    void compile(QSqlDatabase &db, int nSceneId,int &count,int index);

    void SetFitSize(bool bfit);
    QFont m_font;
    bool bFitSize;
    friend QDataStream &operator<<(QDataStream &stream, QSimpleTextItem *psimpleTextItem);
    friend QDataStream &operator>>(QDataStream &stream, QSimpleTextItem *psimpleTextItem);
};

#endif // QSIMPLETEXTITEM_H
