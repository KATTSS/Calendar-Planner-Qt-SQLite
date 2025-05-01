#ifndef CONTMENU_H
#define CONTMENU_H
#include <QObject>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>

// #include "inputdialog.h"
// #include "categoriesdialog.h"
#include "inputdialogdeadline.h"

class ContMenu : public QWidget
{
public:
    ContMenu(QWidget *parent = nullptr);
    void showContextMenu(int row, int column);

        void contextMenuEvent(QContextMenuEvent *event) override;
    private slots:
        void addNewTask();
        void sortByCat();
        void setByDeadline();

    private:
        QMenu *menu;
        QAction *addNew;
        QAction *sortByCategory;
        QAction *deadlineSet;

};

#endif // CONTMENU_H
