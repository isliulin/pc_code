#ifndef QSCISCINTILLAEX_H
#define QSCISCINTILLAEX_H

#include <QtGui/QMouseEvent>
#include <Qsci/qsciscintilla.h>

/*
 QsciScintilla扩展类，使右键菜单项可扩充、翻译
 Add by wuxiyang
 */
class QsciScintillaEx : public QsciScintilla
{
    Q_OBJECT
public:
     QsciScintillaEx(QWidget *parent = 0);
signals:
     void findAction();
protected slots:
     virtual void mousePressEvent(QMouseEvent *e);
     virtual QMenu *createStandardContextMenu();
private:
     void set_shortcut(QAction *action, QsciCommand::Command cmd_id) const;
};

#endif // QSCISCINTILLAEX_H
