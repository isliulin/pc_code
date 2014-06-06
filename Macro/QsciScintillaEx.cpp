#include "QsciScintillaEx.h"
#include "Qsci/qscicommandset.h"
#include <QMenu>

QsciScintillaEx::QsciScintillaEx(QWidget *parent) :
    QsciScintilla(parent)
{

}

void QsciScintillaEx::mousePressEvent (QMouseEvent *e )
{
    if( e->button() == Qt::RightButton)
    {
        QMenu *menu = createStandardContextMenu();

        if (menu)
        {
            menu->setAttribute(Qt::WA_DeleteOnClose);
            menu->popup(e->globalPos());
        }
    }
    QsciScintilla::mousePressEvent(e);
}

QMenu *QsciScintillaEx::createStandardContextMenu()
{
    bool read_only = isReadOnly();
    bool has_selection = hasSelectedText();
    QMenu *menu = new QMenu(this);
    QAction *action;

    if (!read_only)
    {
        action = menu->addAction(tr("����"), this, SLOT(undo()));
        set_shortcut(action, QsciCommand::Undo);
        action->setEnabled(isUndoAvailable());

        action = menu->addAction(tr("�ָ�"), this, SLOT(redo()));
        set_shortcut(action, QsciCommand::Redo);
        action->setEnabled(isRedoAvailable());

        menu->addSeparator();

        action = menu->addAction(tr("����"), this, SLOT(cut()));
        set_shortcut(action, QsciCommand::SelectionCut);
        action->setEnabled(has_selection);
    }

    action = menu->addAction(tr("����"), this, SLOT(copy()));
    set_shortcut(action, QsciCommand::SelectionCopy);
    action->setEnabled(has_selection);

    if (!read_only)
    {
        action = menu->addAction(tr("ճ��"), this, SLOT(paste()));
        set_shortcut(action, QsciCommand::Paste);
        action->setEnabled(SendScintilla(SCI_CANPASTE));

        action = menu->addAction(tr("ɾ��"), this, SLOT(delete_selection()));
        action->setEnabled(has_selection);
    }

    if (!menu->isEmpty())
        menu->addSeparator();

    action = menu->addAction(tr("ȫѡ"), this, SLOT(selectAll()));
    set_shortcut(action, QsciCommand::SelectAll);
    action->setEnabled(length() != 0);

    //���Ӳ����ı��˵���
    if (!menu->isEmpty())
        menu->addSeparator();
    action = menu->addAction(tr("����"), this, SIGNAL(findAction()));
    action->setShortcut(QKeySequence::Find);
    //action->setEnabled(length() != 0); Ӧ��ʵ�ֵģ���������û�иù��ܣ���ע��

    return menu;
}

void QsciScintillaEx::set_shortcut(QAction *action, QsciCommand::Command cmd_id) const
{
    QsciCommand *cmd = standardCommands()->find(cmd_id);

    if (cmd && cmd->key())
        action->setShortcut(QKeySequence(cmd->key()));
}
