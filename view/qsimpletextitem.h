/********************************************************************
类名：QSimpleTextItem
作用：生成文本的基类
作者：郑启红
时间：2010-11-9
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
    QRectF m_rect;           //背景矩形大小
    QString sTEXT;           //文本
    QColor m_FontColor;      //字体颜色
    QColor m_RectBackColor;  //矩形框的背景色
    QColor m_RectFrontColor; //矩形框的前景色
    int m_Alianment;         //文本的对齐方式
    Qt::Alignment AlianmentFlag; //文本的对齐方式
    QBrush m_brush;              //背景矩形画刷
    QLinearGradient m_gradient;    //线性过度色变量
    QRadialGradient m_radial;      //幅角过度色变量
    int nPtternType;             //选择样式的类型
    bool m_RectOutLine;          //背景矩形框是否有边线
    QColor m_RectOutLineColor;   //背景矩形框色颜色
    int m_LineInterval;          //行距

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
