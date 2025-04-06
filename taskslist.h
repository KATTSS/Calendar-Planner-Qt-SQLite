#ifndef TASKSLIST_H
#define TASKSLIST_H
#include <QListWidget>

class TasksList: public QListWidget
{
public:
    TasksList(QWidget *parent=nullptr);

private:
   // QListWidget *list;
};

#endif // TASKSLIST_H
