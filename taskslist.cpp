#include "taskslist.h"

TasksList::TasksList(QWidget *parent) : QListWidget(parent)
{
    tasksDb = DatabaseManager::instance().tasksDatabase();
    connect(this, &QListWidget::itemChanged,
            this, &TasksList::handleItemChange);
}

void TasksList::updateTasks(QMap<QDateTime, QString> toDo)
{
    clear();
    QMapIterator<QDateTime, QString> it(toDo);
    while (it.hasNext()) {
        it.next();

        QString taskText;
        int cat, isComp=0,isDeadline, taskId;

        QStringList task=it.value().split("|");
        if (task.size()>=5) {
            taskText=task[0];
            cat=task[1].toInt();
            isComp=task[2].toInt();
            isDeadline=task[3].toInt();
            taskId=task[4].toInt();
        } else {continue;}
        QString itemText;
        if (writeDate==true) {
            itemText = QString("%1 : %2")
            .arg(it.key().toString("dd-MM HH:mm"))
                .arg(taskText);

        }else {
            if (isDeadline)    itemText = QString("!!! %1 : %2")
                               .arg(it.key().toString("HH:mm"))
                               .arg(taskText);

            else  itemText = QString("%1 : %2")
                               .arg(it.key().toString("HH:mm"))
                               .arg(taskText);
        }

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
    writeDate=false;
}

QString TasksList::getItemByCategory(int x)
{
    switch (x) {
    case 1:
        return ":/images/images.png";
    case 2:
        return ":/images/images (1).png";
    case 3:
        return ":/images/images (2).png";
    case 4:
        return ":/images/lamp.png";
    case 5:
        return ":/images/hospital.png";
    default:
        return ":/images/question.png";
    }
}

void TasksList::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete && m_deleteHandler) {
        if (auto item = currentItem()) {
            m_deleteHandler(item->data(Qt::UserRole).toInt());
            delete item;
        }
    }
    QListWidget::keyPressEvent(event);
}

void TasksList::handleItemChange(QListWidgetItem *item)
{
    int taskId = item->data(Qt::UserRole).toInt();
    bool completed = (item->checkState() == Qt::Checked);
    tasksDb->updateTaskStatus(taskId, completed);
}

void TasksList::handleDeletion(QListWidgetItem *item)
{

    if (!item->isSelected()) return;
    int taskId = item->data(Qt::UserRole).toInt();
    tasksDb->deleteTask(taskId);
}
