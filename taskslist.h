#ifndef TASKSLIST_H
#define TASKSLIST_H
#include <QListWidget>

#include "databasemanager.h"

class TasksList: public QListWidget
{
public:
    TasksList(QWidget *parent=nullptr);
    // QMap<QTime, QString> updateList(QDate &date);

    void updateTasks(QMap<QTime, QString> toDo);
};

#endif // TASKSLIST_H
