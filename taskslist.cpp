#include "taskslist.h"

TasksList::TasksList(QWidget *parent) : QListWidget(parent){}

void TasksList::updateTasks(QMap<QTime, QString> toDo)
{
    clear();
    QMapIterator<QTime, QString> it(toDo);
    qDebug() << "size of toDo list: " << toDo.size();
    while (it.hasNext()) {
        it.next();

        QString taskText = it.value();
        if (taskText.length() >= 2) {
            taskText.chop(2);
        }

        QString itemText = QString("%1 : %2")
                               .arg(it.key().toString("HH:mm"))
                               .arg(taskText);

        qDebug() << "itemText: " << itemText;

        QListWidgetItem* item = new QListWidgetItem(itemText, this);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);

        if (it.value().endsWith("0")) {
            item->setCheckState(Qt::Unchecked);
        } else {
            item->setCheckState(Qt::Checked);
        }

        item->setIcon(QIcon(getItemByCategory(it.value())));

        item->setData(Qt::UserRole, it.key());
        item->setData(Qt::UserRole + 1, taskText);

        addItem(item);
    }
}

QString TasksList::getItemByCategory(const QString &str)
{
    int x = QString(str[str.size()-2]).toInt();
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
