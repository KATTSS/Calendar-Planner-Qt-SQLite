#ifndef TASKSLIST_H
#define TASKSLIST_H
#include <QListWidget>
#include <QKeyEvent>


#include "databasemanager.h"

class TasksList: public QListWidget
{
public:
    TasksList(QWidget *parent=nullptr);

    void updateTasks(QMap<QDateTime, QString> toDo);
    QString getItemByCategory(int x);
    void keyPressEvent(QKeyEvent *event) override;
    void setWriteDateTrue() {writeDate=true;};

    using DeleteHandler = std::function<void(int taskId)>;
    void setDeleteHandler(DeleteHandler handler) {
        m_deleteHandler = handler;
    }

public slots:
    void handleItemChange(QListWidgetItem* item);
    void handleDeletion(QListWidgetItem* item);

private:
    Database *tasksDb;
    DeleteHandler m_deleteHandler;

    bool writeDate=false;
};

#endif // TASKSLIST_H
