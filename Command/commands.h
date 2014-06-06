/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>

#include "View/samdrawscene.h"
//#include "stdafx.h"

class DiagramItem
{
public:
      enum DiagramType { Elipse, Line, Polygon,Rect};
      union uDiagramItem
      {
          QElipseItem  *ElipseItem;
          QLineItem    *LineItem;
          QPolygonItem *PolygonItem;
          QRectItem    *RectItem;
      } ;

};
//! [0]
#if 1
class MoveCommand : public QUndoCommand
{

public:
    enum { Id = 1234 };

    MoveCommand(SamDrawScene *scene,QGraphicsItem *diagramItem, const QPointF &oldPos,
                QUndoCommand *parent = 0);

    void undo();
    void redo();
    bool mergeWith(const QUndoCommand *command);
    int id() const { return Id; }


private:
    QGraphicsItem *myDiagramItem;
    QPointF myOldPos;
    QPointF newPos;


};
#endif
//! [0]

//! [1]
class DeleteCommand : public QUndoCommand
{

public:
    DeleteCommand(SamDrawScene *graphicsScene, QUndoCommand *parent = 0);

    void undo();
    void redo();
    //QList <QPointF> mylist;
private:
    QList<QGraphicsItem *> myDiagramItems;
    SamDrawScene *myGraphicsScene;

};
//! [1]

//! [2]
/*
class AddCommand : public QUndoCommand
{
public:
    AddCommand(DiagramItem::DiagramType addType, QGraphicsScene *graphicsScene,
               QUndoCommand *parent = 0);

    void undo();
    void redo();

private:
    DiagramItem *myDiagramItem;
    QGraphicsScene *myGraphicsScene;
    QPointF initialPosition;
};
*/
//! [2]

QString createCommandString(QGraphicsItem *item, const QPointF &point);


class MovesCommand : public QUndoCommand
 {

 public:
     enum { Id = 12345 };

     MovesCommand(SamDrawScene *scene,QList <QGraphicsItem *> movingItems,QList <QPointF >oldPoss,
                 QUndoCommand *parent = 0);

     void undo();
     void redo();
     //bool mergeWith(const QUndoCommand *command);
     int id() const { return Id; }

 private:
     QList <QGraphicsItem *>myDiagramItems;
     QList <QPointF> myOldPoss;
     QList <QPointF> mynewPoss;
     SamDrawScene *myScene;

 };

class SizeCommand : public QUndoCommand
 {

 public:

     SizeCommand(SamDrawScene *scene,QGraphicsItem * pItem,QSizeF size,QPointF oldPos);

     void undo();
     void redo();
     //bool mergeWith(const QUndoCommand *command);
     //int id() const { return Id; }

 private:
     QGraphicsItem *item;
     QSizeF oldSize;
     QSizeF newSize;
     QPointF oPos;
     QPointF nPos;
     SamDrawScene *myScene;

 };

class AlignCommand : public QUndoCommand
 {

 public:

     AlignCommand(SamDrawScene *scene,QList <QGraphicsItem *> movingItems,
                  QList <QSizeF > oldSize,QList <QPointF >oldPoss);

     void undo();
     void redo();

 private:
     QList <QGraphicsItem *>myDiagramItems;
     QList <QPointF> myOldPoss;
     QList <QPointF> mynewPoss;
     QList <QSizeF > myoldSize;
     QList <QSizeF > mynewSize;
     SamDrawScene *myScene;

 };

class AddCommand : public QUndoCommand
{
public:

    AddCommand(QGraphicsItem *pItem,QGraphicsScene *graphicsScene,QString itemName,
               QUndoCommand *parent = 0);
    QString createCommandString(DiagramItem *item, const QPointF &pos);
    void undo();
    void redo();

private:

    QGraphicsItem *myDiagramItem;

    QGraphicsScene *myGraphicsScene;
    //QPointF initialPosition;
    QString commandName;

};





class AssembleCommand : public QUndoCommand
{
public:

    AssembleCommand(QGraphicsItem *pAssembleItem,  QList<QGraphicsItem *> pUnAssembleItems, QGraphicsScene *graphicsScene,QString AssembleCommand="Assemble action",
               QUndoCommand *parent = 0);

    void undo();
    void redo();

private:

    QGraphicsItem *myAssembleItem;

    QList<QGraphicsItem *> myUnAssembleItems;

    QString strCommandName;

};


class CopyCommand: public QUndoCommand
{
public:

    CopyCommand(QGraphicsItem *pAssembleItem,  QList<QGraphicsItem *> pUnAssembleItems, QGraphicsScene *graphicsScene,QString itemName,
               QUndoCommand *parent = 0);

    void undo();
    void redo();

private:

    QGraphicsItem *myAssembleItem;

    QList<QGraphicsItem *> myUnAssembleItems;

    QString strCommandName;
};

class ModifyItemCommand: public QUndoCommand
{
public:

	ModifyItemCommand(QGraphicsItem *poldItem,QGraphicsItem *pnewItem,SamDrawScene *samdrawscene,QString itemName,
		QUndoCommand *parent = 0);

	void undo();
	void redo();

private:
	SamDrawScene *mySamDrawScene;
	QGraphicsItem *myoldItem;
	QGraphicsItem *mynewItem;
	QGraphicsItem *tempOldItem;
	QGraphicsItem *tempNewItem;
	QString strCommandName;
};
class LineItemCommand: public QUndoCommand
{
public:

        LineItemCommand(SamDrawScene *scene,QGraphicsItem *item,
                        QPainterPath oldPath,QPainterPath newPath);

        void undo();
        void redo();

private:
        SamDrawScene *myScene;
        QGraphicsItem *myItem;
        QPainterPath oPath;
        QPainterPath nPath;
};
class PolygonItemCommand: public QUndoCommand
{
public:

        PolygonItemCommand(SamDrawScene *scene,QGraphicsItem *item,
                           QPolygonF oldPolygon,QPolygonF newPolygon);

        void undo();
        void redo();

private:
        SamDrawScene *myScene;
        QGraphicsItem *myItem;
        QPolygonF oPolygon;
        QPolygonF nPolygon;
};
#endif
