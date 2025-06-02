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
    InputDialog *newInput = new InputDialog();
    setStyle(newInput);
    newInput->show();
}

void ContMenu::sortByCat()
{
    CategoriesDialog *newDialog = new CategoriesDialog();
    setStyle(newDialog);
    newDialog->show();
}

void ContMenu::setByDeadline()
{
    InputDialogDeadline *newDeadline = new InputDialogDeadline();
    setStyle(newDeadline);
    newDeadline->show();
}

void ContMenu::setStyle(CategoriesDialog *dialog)
{
    dialog->setStyleSheet(R"(
    QDialog {
        background-color: #FFF5CD;

    }
    QComboBox, QSpinBox, QLineEdit, QLabel, QPushButton {
        background-color: #F2F0FC;
        border: 1px solid #8F77FF;
        color: #0C042F;
        padding: 5px;
        border-radius: 4px;
    }
    QPushButton {
        background-color: #AC9AFF;
        font: bold 15px;
    }
    QSpinBox::up-button, QSpinBox::down-button {
        background-color: #C2B5FF;
        border-left: 1px solid #8F77FF;
        width: 20px;
    }
    QSpinBox::up-arrow { text: "↑"; }
    QSpinBox::down-arrow { text: "↓"; }
    QComboBox::drop-down {
        width: 20px;
        border-left: 1px solid #8F77FF;
        background-color: #C2B5FF;
    }

    QComboBox::down-arrow { text: "▼"; }
     )");
}

void ContMenu::showContextMenu(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);
    menu->exec(QCursor::pos());
}
