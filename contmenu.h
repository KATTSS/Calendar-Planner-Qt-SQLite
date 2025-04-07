#ifndef CONTMENU_H
#define CONTMENU_H
#include <QObject>
#include <QWidget>
#include <QAction>
#include <QMenu>
#include <QContextMenuEvent>

class ContMenu : public QWidget
{
public:
    ContMenu(QWidget *parent = nullptr);
    void showContextMenu(int row, int column);

  //  protected:
        void contextMenuEvent(QContextMenuEvent *event) override;
    private slots:
        void addNewTask();
        // void showContextMenu(int row, int column);

    private:
        QMenu *menu;
        QAction *addNew;

};

#endif // CONTMENU_H
