#include "contmenu.h"

#include <QDebug>

ContMenu::ContMenu(QWidget *parent) : QWidget(parent)
{
    menu = new QMenu(this);

    addNew = new QAction("add new task", this);

    connect(addNew, &QAction::triggered, this, &ContMenu::addNewTask);

    menu->addAction(addNew);
}

void ContMenu::contextMenuEvent(QContextMenuEvent *event)
{
    menu->exec(event->globalPos());
}

void ContMenu::addNewTask()
{
    qDebug() << "adding opened";
}

void ContMenu::showContextMenu(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    menu->exec(QCursor::pos());
}
