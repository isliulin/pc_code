/************************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2010
 *
 * Description: SamDrawTool class define .h file.
 *
 * Functions: None.
 *
 * Modification Log:
 * Date             Name             Description Of Change
 * 2010-10-30       Bruce nie        Creation.
 ***********************************************************************/
#ifndef SAMDRAWTOOL_H
#define SAMDRAWTOOL_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QVector>
#include <QGraphicsView>
#include "view/qitemgroup.h"
#include "headfile/global_types.h"
#include <qmath.h>
#include "view/qdrawgraphics.h"
#include "view/qsimpletextitem.h"

//#include "view/qelipseitem.h"
//#include "view/qrectitem.h"
//#include "view/qlineitem.h"
//#include "view/qpolygonitem.h"
//#include "view/QRoundedRect.h"
//#include "view/QArcItem.h"

#include "view/qelipsebasicitem.h"
#include "view/qrectbasicitem.h"
#include "view/qlinebasicitem.h"
#include "view/qpolygonbasicitem.h"
#include "view/qroundedrectbasic.h"
#include "view/qarcbasicitem.h"
#include "view/qfoldlinebasicitem.h"
#include "view/qfreelinebasicitem.h"
#include "view/qlinecirclebasicitem.h"
#include "view/qarcbasicitem.h"

enum eSamDrawActionType
{
    SAM_DRAW_INVALID   = -1,
    SAM_DRAW_SELECTION = 0x00,    // selection
    SAM_DRAW_ELLIPSE   = 0x01,    // draw elipse
    SAM_DRAW_RECT      = 0x02,    // draw rect
    SAM_DRAW_LINE      = 0x03,    // draw line
    SAM_DRAW_POLYGON   = 0x04,    // draw polygon
    SAM_DRAW_FOLDLINE  = 0x05,    // draw fold line
    SAM_DRAW_FREELINE  = 0x06,    // draw free curve line
    SAM_DRAW_LINE_CIRCLE = 0x07,  // draw line-circle
    SAM_DRAW_SAMPLE_TEXT = 0x08,  // draw text
    SAM_DRAW_ANIMATION   = 0x09,   // draw animation

    SAM_DRAW_ROUNDED_RECT = 0x10,  // draw rounded rect
    SAM_DRAW_ARC = 0x11,           // draw Arc

    SAM_DRAW_ASSY_COMPONENT   = 0x20,

    SAM_DRAW_ACT_TYPE_BUTT
};
typedef enum eSamDrawActionType SAM_DRAW_ACT_TYPE_E;

enum eSamDrawRectPointType
{
    SAM_DRAW_RECT_TOP_LEFT      = 0x01,
    SAM_DRAW_RECT_TOP_CENTER    = 0x02,
    SAM_DRAW_RECT_TOP_RIGHT     = 0x03,
    SAM_DRAW_RECT_CENTER_RIGHT  = 0x04,
    SAM_DRAW_RECT_BOTTOM_RIGHT  = 0x05,
    SAM_DRAW_RECT_BOTTOM_CENTER = 0x06,
    SAM_DRAW_RECT_BOTTOM_LEFT   = 0x07,
    SAM_DRAW_RECT_CENTER_LEFT   = 0x08,
    SAM_DRAW_RECT_POINT_TYPE_BUTT
};
typedef enum eSamDrawRectPointType SAM_DRAW_RECT_POINT_TYPE_E;

enum eSamDrawToolStatus
{
    SAM_DRAW_TOOL_UNLOCKED = 0x00,
    SAM_DRAW_TOOL_LOCKED   = 0x01,
    SAM_DRAW_TOOL_STATUS_BUTT
};
typedef enum eSamDrawToolStatus SAM_DRAW_TOOL_STATUS_E;

/*Class SamDrawTool, base class for tools*/
class SamDrawTool
{
public:
    SamDrawTool(SAM_DRAW_ACT_TYPE_E m_DrawActType);
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void onCancel(QGraphicsScene *pScene);
    static SamDrawTool* FindTool(SAM_DRAW_ACT_TYPE_E eDrawActType);
    void   onReDrawRect(QPointF pos,QGraphicsScene *pScene);
    QPointF coordTranslateInGrp(const SAM_DRAW_RECT_POINT_TYPE_E &eRefPoint,
        const QPointF &qpPoint, const QRectF &qrcGrpBndRect, const qreal &dXfactor, const qreal &dYfactor);
    SAM_DRAW_ACT_TYPE_E m_eDrawActType;
    static SAM_DRAW_ACT_TYPE_E s_eDrawActType;
    static QVector<SamDrawTool *> m_drawTools;
    static SAM_DRAW_TOOL_STATUS_E s_eToolStat;
    QRectItem *pBackRect;
};

/*Class SamDrawRectTool*/
class SamDrawRectTool : public SamDrawTool
{
public:
    SamDrawRectTool();
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    QGraphicsItem *drawRect(const QPointF qpPressedPt, QGraphicsScene *pScene);
};

/*Class SamDrawElipseTool*/
class SamDrawElipseTool : public SamDrawTool
{
public:
    SamDrawElipseTool();
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    QGraphicsItem *drawElipse(const QPointF qpPressedPt, QGraphicsScene *pScene);
};

/*Class SamDrawLineTool*/
class SamDrawLineTool : public SamDrawTool
{
public:
    SamDrawLineTool();
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    QGraphicsItem *drawLine(const QPointF qpPressedPt, const QPointF qpReleasedPt,QGraphicsScene *pScene);
};

/*Class SamDrawPolygonTool*/
class SamDrawPolygonTool : public SamDrawTool
{
public:
    SamDrawPolygonTool();
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void onCancel(QGraphicsScene *pScene);
    QGraphicsItem *drawPolygon(const QPointF qpPressedPt, QGraphicsScene *pScene);
private:
    QPolygonF m_qpsPolygon;
    QPolygonBasicItem *m_pPolygonItem;
    unsigned long m_ulPressedCnt;
    QPointF m_qpLastPt;
};

/*Class SamDrawFoldLineTool*/
class SamDrawFoldLineTool : public SamDrawTool
{
public:
    SamDrawFoldLineTool();
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void onCancel(QGraphicsScene *pScene);
    QGraphicsItem *drawFoldLine(const QPointF qpPressedPt, QGraphicsScene *pScene);
private:
    //QPainterPath m_Path;
    QVector<QPointF> m_qpPoints;
    QFoldLineBasicItem *m_pFoldLineItem;
    unsigned long m_ulPressedCnt;
    QPointF m_qpLastPt;
};

/*Class SamDrawFreeLineTool*/
class SamDrawFreeLineTool : public SamDrawTool
{
public:
    SamDrawFreeLineTool();
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void onCancel(QGraphicsScene *pScene);
    QGraphicsItem *drawFreeLine(const QPointF qpPressedPt, QGraphicsScene *pScene);
private:
    //QPainterPath m_Path;
    QVector<QPointF> m_qpPoints;
    QFreeLineBasicItem *m_pFreeLineItem;
    unsigned long m_ulPressedCnt;
};

/*Class SamDrawLineLinkTool*/

/*Class SamDrawArcLineTool*/
/*class SamDrawArcLineTool : public SamDrawTool
{
public:
    SamDrawArcLineTool();
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    QGraphicsItem *drawArcLine(const QPointF qpPressedPt, QGraphicsScene *pScene);
private:
    QArcLineItem *m_pArcLineItem;
    QVector<QPointF> m_qpPoints;
    unsigned long m_ulPressedCnt;
};*/

/*Class SamDrawTextTool*/
class SamDrawTextTool : public SamDrawTool
{
public:
    SamDrawTextTool();
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    QGraphicsItem *drawText(const QPointF qpPressedPt, QGraphicsScene *pScene);
};

/*Class SamDrawSelectTool*/
enum eSelectMode
{
    SEL_MOD_NONE,
    SEL_MOD_NET_SELECT,  // net selection
    SEL_MOD_MOVE,       // move objects
    SEL_MOD_SIZE        // resize object
};
typedef enum eSelectMode SELECT_MODE_E;

enum eAdjustObjWidthHeight
{
    ADJUST_OBJ_WIDTH        = 0x01,
    ADJUST_OBJ_HEIGHT       = 0x10,
    ADJUST_OBJ_WIDTH_HEIGHT = 0x11,
    ADJUST_OBJ_SIZE_TYPE_BUTT
};
typedef enum eAdjustObjWidthHeight ADJUST_OBJ_SIZE_TYPE_E;

class SamDrawSelectTool : public SamDrawTool
{
public:
    enum eExpandRefType {EXPD_HEIGHT = 0x01, EXPD_WIDTH = 0x10, EXPD_ALL = 0x11, EXPD_BUTT};
    typedef enum eExpandRefType SAMDRAW_EXPAND_TYPE_E;
    SamDrawSelectTool();
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    void exchgDraghandle(DRAG_CROSS_TYPE_E eCrossType);
    void moveGroupHandle(QItemGroup *pItemGroup, const QRectF &qrcGrpBndRect,
        const qreal &dFactorX, const qreal &dFactorY, unsigned long ulDragHdl);

    /*Set the selected items' same width/height*/
    void setSelSameWidth(QGraphicsScene *pScene);
    void setSelSameheight(QGraphicsScene *pScene);
    void setSelSameWidthHeight(QGraphicsScene *pScene);
    QGraphicsItem *getTheLeftmostItem(QGraphicsScene *pScene);
    void adjustObjectSize(ADJUST_OBJ_SIZE_TYPE_E eAdjustType, QGraphicsScene *pScene);
    qreal getMaxLinWidthInGrp(QItemGroup *pGrp);

    SELECT_MODE_E m_eSelectMode;
    unsigned long m_ulDragHandle;

private:
    SAMDRAW_EXPAND_TYPE_E m_eExpType;
    uint m_uiGrpTypeKey;//等于1等比例拉大，等于0不处理
};

/*********************************************************************************
 * Class SamDrawLineCircleTool for SamDraw multi path item(line-circle)
 * Design by tanghaiguo at 2010.11.8
 *
 ********************************************************************************/
class SamDrawLineCircleTool : public SamDrawTool
{
public:
    SamDrawLineCircleTool();
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void onCancel(QGraphicsScene *pScene);
    QLineCircleBasicItem *drawLineCircle(const QPointF qpPressedPt, QGraphicsScene *pScene);
private:
    QPointF           qPressPoint;
    QVector<QPointF>  m_points;
    QPainterPath      *m_pPath;
    QLineCircleBasicItem   *m_pLineCircleItem;
    QLineCircleBasicItem   *pMoveItem;
    bool bMousePressed;
    bool bMouseMove;
    bool bMouseMovePressed;
};

/*Class SamDrawRoundedRectTool*/
class SamDrawRoundedRectTool : public SamDrawTool
{
public:
    SamDrawRoundedRectTool();
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    QGraphicsItem *drawRoundedRect(const QPointF qpPressedPt, QGraphicsScene *pScene);
};

/*Class SamDrawArcTool*/
class SamDrawArcTool : public SamDrawTool
{
public:
    SamDrawArcTool();
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    QGraphicsItem *drawArc(const QPointF qpPressedPt, QGraphicsScene *pScene);
};


/*********************************************************************************
 * Class SamDrawAnimationTool for animation.
 ********************************************************************************/
class SamDrawAnimationTool : public SamDrawTool
{
public:
    SamDrawAnimationTool();
    ~SamDrawAnimationTool();
    virtual void mousePressEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *mouseEvent);
    virtual void mouseMoveEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsScene *pScene, QGraphicsSceneMouseEvent *event);
    virtual void onCancel(QGraphicsScene *pScene);
    void finishAnimation(QGraphicsScene *pScene);
private:
    QVector<QElipseItem *> m_pEllipseItems;
    QPointF m_qpLastPt;
};

#endif // SAMDRAWTOOL_H
