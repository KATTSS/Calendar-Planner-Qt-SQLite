#include "contmenu.h"

#include <QDebug>

ContMenu::ContMenu(QWidget *parent) : QWidget(parent)
{
    menu = new QMenu(this);

    addNew = new QAction("add new task", this);
    sortByCategory = new QAction("sort by event category", this);
    deadlineSet = new QAction("set event before deadline", this);

    connect(addNew, &QAction::triggered, this, &ContMenu::addNewTask);
    connect(sortByCategory, &QAction::triggered, this, &ContMenu::sortByCat);
    connect(deadlineSet, &QAction::triggered, this, &ContMenu::setByDeadline);

    menu->addAction(addNew);
    menu->addAction(sortByCategory);
    menu->addAction(deadlineSet);
}

void ContMenu::contextMenuEvent(QContextMenuEvent *event)
{
    menu->exec(event->globalPos());
}

void ContMenu::addNewTask()
{
    qDebug() << "adding opened";
    InputDialog *newInput = new InputDialog();
    newInput->show();

}

void ContMenu::sortByCat()
{
    qDebug() << "in adding tasks";
    CategoriesDialog *newDialog = new CategoriesDialog();
    newDialog->show();
}

void ContMenu::setByDeadline()
{
    InputDialogDeadline *newDeadline = new InputDialogDeadline();
    newDeadline->show();
}

void ContMenu::showContextMenu(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    menu->exec(QCursor::pos());
}
