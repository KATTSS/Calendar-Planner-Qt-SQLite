#ifndef CONTMENU_H
#define CONTMENU_H
#include <QObject>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>

#include "inputdioalog.h"
#include "categoriesdialog.h"

class ContMenu : public QWidget
{
public:
    ContMenu(QWidget *parent = nullptr);
    void showContextMenu(int row, int column);

        void contextMenuEvent(QContextMenuEvent *event) override;
    private slots:
        void addNewTask();
        void sortByCat();

    private:
        QMenu *menu;
        QAction *addNew;
        QAction *sortByCategory;

};

#endif // CONTMENU_H
