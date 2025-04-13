#ifndef TASKSLIST_H
#define TASKSLIST_H
#include <QListWidget>
#include <QTimer>


#include "databasemanager.h"

class TasksList: public QListWidget
{
public:
    TasksList(QWidget *parent=nullptr);
    // QMap<QTime, QString> updateList(QDate &date);

    void updateTasks(QMap<QTime, QString> toDo);
    QString getItemByCategory(int x);

public slots:
    void handleItemChange(QListWidgetItem* item);

private:
    Database *tasksDb;
};

#endif // TASKSLIST_H
