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
   // qDebug() << "size of toDo list: " << toDo.size();
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
        QString itemText;
        if (writeDate==true) {
            itemText = QString("%1 : %2")
            .arg(it.key().toString("dd-MM HH:mm"))
                .arg(taskText);

        }else itemText = QString("%1 : %2")
                               .arg(it.key().toString("HH:mm"))
                               .arg(taskText);

     //   qDebug() << "itemText: " << itemText;

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
  //  qDebug () << "in changing status" << taskId << " " << completed;
    tasksDb->updateTaskStatus(taskId, completed);
}

void TasksList::handleDeletion(QListWidgetItem *item)
{

    if (!item->isSelected()) return;
    int taskId = item->data(Qt::UserRole).toInt();
    tasksDb->deleteTask(taskId);
}
