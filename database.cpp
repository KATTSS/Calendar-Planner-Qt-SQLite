#include "database.h"
#include <QSqlError>

Database::Database(const QString& dbPath, const QString &connection) {
    database = QSqlDatabase::addDatabase("QSQLITE", connection);
    database.setDatabaseName(dbPath);
}

Database::~Database()
{
    close();
}

bool Database::open()
{
    if (!database.open()) {
        qWarning() << "Failed to open database" ;
        return false;
    }
    qInfo() << "Database opened successfully";
    return true;
}

void Database::close()
{
    if (database.isOpen()) {
        database.close();
        qInfo() << "Database closed";
    }
}

void Database::cleanTable(const QString &dbName)
{
    QSqlQuery query(database);
    query.exec(QString("DELETE FROM %1").arg(dbName));
}

QSqlTableModel* Database::selectCurrentMonthDates(QObject *parent)
{
    QSqlTableModel* model = new QSqlTableModel(parent, database);
    model->setTable("calendar");

    QDate current = QDate::currentDate();
    QDate nextMonth = current.addMonths(1);


    model->setFilter(QString("d BETWEEN '%1' AND '%2'")
                         .arg(current.toString("yyyy-MM-dd"),
                              nextMonth.toString("yyyy-MM-dd")));


    model->setHeaderData(0, Qt::Horizontal, ("Date"));
    model->setHeaderData(1, Qt::Horizontal, ("Day of Week"));

    if (!model->select()) {
       delete model;
        return nullptr;
    }

    return model;
}

bool Database::createTable(const QString &tableName, const QString &tableSchema)
{
    QSqlQuery query(database);
    return query.exec(QString("CREATE TABLE IF NOT EXISTS %1 (%2)").arg(tableName).arg(tableSchema));
}

QSqlTableModel *Database::createTableModel(const QString &tableName, QObject *parent)
{
    QSqlTableModel* model = new QSqlTableModel(parent, database);
    model->setTable(tableName);
    model->select();
    return model;
}

bool Database::createCalendar() {

    createTable("calendar", "d TEXT UNIQUE NOT NULL,"
                            "year INT NOT NULL,"
                            "month INT NOT NULL,"
                            "day INT NOT NULL"
                );


    QSqlQuery query(database);
    QDate startDate(2000, 1, 1);
    QDate endDate(2050, 1, 1);
    query.exec("BEGIN TRANSACTION");
    for (QDate date = startDate; date <= endDate; date = date.addDays(1)) {
        query.prepare(R"(
            INSERT OR IGNORE INTO calendar
            (d,  year, month, day)
            VALUES (?, ?, ?, ?)
        )");
        query.addBindValue(date.toString("yyyy-MM-dd"));
        query.addBindValue(date.year());
        query.addBindValue(date.month());
        query.addBindValue(date.day());
        if (!query.exec()) {
            query.exec("ROLLBACK");
            return false;
        }
    }
    query.exec("COMMIT");
    return true;
}

QVector<QDate> Database::getDatesForMonth(int year, int month) {
    QVector<QDate> dates;
    QSqlQuery query(database);
    query.prepare(
        "SELECT year, month, day FROM calendar "
        "WHERE year = ? AND month = ? "
        "ORDER BY day ASC"
        );
    query.addBindValue(year);
    query.addBindValue(month);
    if (query.exec()) {
        while (query.next()) {
            dates.append(QDate(
                query.value(0).toInt(),
                query.value(1).toInt(),
                query.value(2).toInt()
                ));
        }
    }
    return dates;
}

bool Database::addTask(const QDate &date, const QString &time, const QString &description, int category, bool is_deadline,  const QDate &deadline)
{
    QSqlQuery query(database);
    query.prepare(R"(
        INSERT INTO tasks (date, time, description, category, is_completed, is_deadline, deadline)
        VALUES (?, ?, ?, ?, ?, ?, ?)
    )");
    query.addBindValue(date.toString("yyyy-MM-dd"));
    query.addBindValue(time);
    query.addBindValue(description);
    query.addBindValue(category);
    query.addBindValue(0);
    query.addBindValue(is_deadline? 1 : 0);
    query.addBindValue(deadline.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qWarning() << "Failed to add task:" << query.lastError().text();
        return false;
    }
    return true;
}


QMap<QDateTime, QString> Database::getTasksAtDate(QDate &date)
{
    QMap<QDateTime, QString> toDo;
    QSqlQuery taskQuery(this->database);
    taskQuery.prepare("SELECT description, time, category, is_completed, deadline, id FROM tasks WHERE date = ?");
    taskQuery.addBindValue(date.toString("yyyy-MM-dd"));
    if (taskQuery.exec()) {
        while (taskQuery.next()) {
            QString description = taskQuery.value("description").toString()+"|"+taskQuery.value("category").toString()
                                  +"|"+taskQuery.value("is_completed").toString()+"|"+taskQuery.value("deadline").toString()
                                  +"|"+taskQuery.value("id").toString();
            QString timeStr = taskQuery.value("time").toString();

            QDateTime time = QDateTime::fromString(timeStr, "HH:mm");

            if (time.isValid()) {
                toDo.insert(time, description);
            } else {
                qWarning() << "Invalid time format:" << timeStr;
            }
        }
    }
    return toDo;
}

bool Database::updateTaskStatus(int taskId, bool completed)
{
    QSqlQuery query(database);
    query.prepare("UPDATE tasks SET is_completed = ? WHERE id = ?");
    query.addBindValue(completed ? 1 : 0);
    query.addBindValue(taskId);
    return query.exec();
}

bool Database::deleteTask(int taskId)
{
    QSqlQuery query(database);
    query.prepare("DELETE FROM tasks WHERE id = ?");
    query.addBindValue(taskId);
    return query.exec();
}

QMap<QDateTime, QString> Database::getTasksByCategory(int cat)
{
    QMap<QDateTime, QString> toDo;

    QSqlQuery taskQuery(this->database);
    taskQuery.prepare("SELECT description, is_completed, id, date, time, is_deadline FROM tasks WHERE category = ?");
    taskQuery.addBindValue(cat);

    if (taskQuery.exec()) {
        while (taskQuery.next()) {
            QString description = taskQuery.value("description").toString()+"|"+QString::number(cat)
            +"|"+taskQuery.value("is_completed").toString()+"|"+taskQuery.value("is_deadline").toString()+"|"+taskQuery.value("id").toString();

            QString timeStr = taskQuery.value("date").toString()+taskQuery.value("time").toString();

            QDateTime dateTime = QDateTime::fromString(timeStr, "yyyy-MM-ddHH:mm");

            if (dateTime.isValid()) {
                toDo.insert(dateTime, description);
            } else {
                qWarning() << "Invalid time format:" << timeStr;
                continue;
            }
        }
    }
    return toDo;
}
QDate Database::getOptimalDate(const QDate &deadline) {
    if (!database.isOpen() && !open()) {
        qWarning() << "Failed to open database";
        return QDate();
    }

    QDate tomorrow = QDate::currentDate().addDays(1);
    QDate bestDate = tomorrow;
    int minTaskCount = INT_MAX;

    QDate dead = deadline.addDays(-1);
    QSqlQuery query(database);
    query.prepare("SELECT date, COUNT(*) as task_count FROM tasks "
                  "WHERE date BETWEEN ? AND ? "
                  "GROUP BY date");
    query.addBindValue(tomorrow.toString("yyyy-MM-dd"));
    query.addBindValue(dead.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        qWarning() << "Query error:" << query.lastError().text();
        return QDate();
    }

    QMap<QDate, int> dateTaskCounts;
    while (query.next()) {
        QDate date = QDate::fromString(query.value(0).toString(), "yyyy-MM-dd");
        int count = query.value(1).toInt();
        dateTaskCounts[date] = count;
    }

    for (QDate date = tomorrow; date <= dead; date = date.addDays(1)) {
        int currentCount = dateTaskCounts.value(date, 0);
        if (currentCount < minTaskCount) {
            minTaskCount = currentCount;
            bestDate = date;
        }
    }
    return bestDate;
}

void Database::moveDeadlineTasks()
{
    QDate yesterday = QDate::currentDate().addDays(-1);
    QDate current = QDate::currentDate();

    database.transaction();

    try {

    QSqlQuery taskQuery(database);
    taskQuery.prepare("SELECT description, time, category, id, deadline FROM tasks WHERE date = ? AND  is_deadline = ?  AND is_completed = ? AND deadline != ?");
    taskQuery.addBindValue(yesterday.toString("yyyy-MM-dd"));
    taskQuery.addBindValue(1);
    taskQuery.addBindValue(0);
    taskQuery.addBindValue(current.toString("yyyy-MM-dd"));

    if (!taskQuery.exec()) {
        throw std::runtime_error(taskQuery.lastError().text().toStdString());
    }

    QVector<QStringList> tasksToAdd;
    QVector<int> tasksToDelete;

        while (taskQuery.next()) {
        tasksToDelete.append(taskQuery.value("id").toInt());

        tasksToAdd.append({
            taskQuery.value("description").toString(),
            taskQuery.value("category").toString(),
            taskQuery.value("time").toString(),
            taskQuery.value("deadline").toString()
        });
        }
        for (int id : tasksToDelete) {
            if (!deleteTask(id)) {
                qWarning() << "Failed to delete task:" << id;
            }
        }

        for (const auto& task : tasksToAdd) {
            addTask(
                current,
                task[2],
                task[0],
                task[1].toInt(),
                true,
                QDate::fromString(task[3], "yyyy-MM-dd")
                );
        } if (!database.commit()) {
            throw std::runtime_error("Commit failed");
        }

    } catch (const std::exception& e) {
        database.rollback();
        qCritical() << "Error moving tasks:" << e.what();
    }
}

bool Database::tableExists(const QString &tableName) {
    QSqlQuery query(database);
    query.prepare("SELECT name FROM sqlite_master WHERE type='table' AND name=?");
    query.addBindValue(tableName);
    return query.exec() && query.next();
}
