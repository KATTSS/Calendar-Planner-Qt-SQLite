#include "taskslist.h"

TasksList::TasksList(QWidget *parent) : QListWidget(parent){}

void TasksList::updateTasks(QMap<QTime, QString> toDo)
{
    clear();
    QMapIterator<QTime, QString> it(toDo);
    while (it.hasNext()) {
        it.next();

        QString itemText = QString("%1 : %2")
                               .arg(it.key().toString("HH:mm"))
                               .arg(it.value());

        QListWidgetItem* item = new QListWidgetItem(itemText, this);

        item->setData(Qt::UserRole, it.key());
        item->setData(Qt::UserRole + 1, it.value());

        addItem(item);
    }
}

// QMap<QTime, QString> TasksList::updateList(QDate &date)
// {
//     Database* tasksDb = DatabaseManager::instance().tasksDatabase();
//     QMap<QTime, QString> toDo;
//     QSqlQuery taskQuery(tasksDb->database);
//     taskQuery.prepare("SELECT description, time FROM tasks WHERE date = ?");
//     taskQuery.addBindValue(date.toString("yyyy-MM-dd"));
//     if (taskQuery.exec()) {
//         while (taskQuery.next()) {
//             QString description = taskQuery.value("description").toString();
//             QString timeStr = taskQuery.value("time").toString();

//             QTime time = QTime::fromString(timeStr, "HH:mm");

//             if (time.isValid()) {
//                 toDo.insert(time, description);
//             } else {
//                 qWarning() << "Invalid time format:" << timeStr;
//             }
//         }
//     }
//     return toDo;
// }
