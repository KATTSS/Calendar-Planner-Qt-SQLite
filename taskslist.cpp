#include "taskslist.h"

TasksList::TasksList(QWidget *parent) : QListWidget(parent){

    connect(this, &QListWidget::itemChanged,
            this, &TasksList::handleItemChange);
    tasksDb = DatabaseManager::instance().tasksDatabase();
}

void TasksList::updateTasks(QMap<QTime, QString> toDo)
{
    clear();
    QMapIterator<QTime, QString> it(toDo);
    qDebug() << "size of toDo list: " << toDo.size();
    while (it.hasNext()) {
        it.next();

        QString taskText;
        int cat, isComp=0, taskId;

        QStringList task=it.value().split("|");
        if (task.size()>=4) {
            taskText=task[0];
            cat=task[1].toInt();
            isComp=task[2].toInt();
            taskId=task[3].toInt();
        } else {continue;}

        QString itemText = QString("%1 : %2")
                               .arg(it.key().toString("HH:mm"))
                               .arg(taskText);

        qDebug() << "itemText: " << itemText;

        QListWidgetItem* item = new QListWidgetItem(itemText, this);
        item->setData(Qt::UserRole, taskId);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);

        if (isComp==0) {
            item->setCheckState(Qt::Unchecked);
        } else {
            item->setCheckState(Qt::Checked);
        }

        item->setIcon(QIcon(getItemByCategory(cat)));

        item->setData(Qt::UserRole + 1, taskText);

        addItem(item);
    }
}

QString TasksList::getItemByCategory(int x)
{
    switch (x) {
    case 1:
        return "/home/katya/курсач)/images.png";
    case 2:
        return "/home/katya/курсач)/images (1).png";
    case 3:
        return "/home/katya/курсач)/images (2).png";
    case 4:
        return "/home/katya/курсач)/lamp.png";
    case 5:
        return "/home/katya/курсач)/hospital.png";
    default:
        return "/home/katya/курсач)/question.png";
    }
}

void TasksList::handleItemChange(QListWidgetItem *item)
{
    int taskId = item->data(Qt::UserRole).toInt();
    bool completed = (item->checkState() == Qt::Checked);
    qDebug () << "in changing status" << taskId << " " << completed;
    tasksDb->updateTaskStatus(taskId, completed);
}
