#include "contmenu.h"

#include <QDebug>

ContMenu::ContMenu(QWidget *parent) : QWidget(parent)
{
    menu = new QMenu(this);

    addNew = new QAction("add new task", this);
    sortByCategory = new QAction("sort by event category", this);

    connect(addNew, &QAction::triggered, this, &ContMenu::addNewTask);
    connect(sortByCategory, &QAction::triggered, this, &ContMenu::sortByCat);

    menu->addAction(addNew);
    menu->addAction(sortByCategory);
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

void ContMenu::showContextMenu(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    menu->exec(QCursor::pos());
}
