#ifndef TASKSLIST_H
#define TASKSLIST_H
#include <QListWidget>
//#include <QTimer>
#include <QKeyEvent>


#include "databasemanager.h"

class TasksList: public QListWidget
{
public:
    TasksList(QWidget *parent=nullptr);
    // QMap<QTime, QString> updateList(QDate &date);

    void updateTasks(QMap<QTime, QString> toDo);
    QString getItemByCategory(int x);
    void keyPressEvent(QKeyEvent *event) override;

    using DeleteHandler = std::function<void(int taskId)>;
    void setDeleteHandler(DeleteHandler handler) {
        m_deleteHandler = handler;
    }


// signals:
//     void  deletionPressed();

public slots:
    void handleItemChange(QListWidgetItem* item);
    void handleDeletion(QListWidgetItem* item);

private:
    Database *tasksDb;
    DeleteHandler m_deleteHandler;
};

#endif // TASKSLIST_H
