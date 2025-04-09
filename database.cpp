#include "database.h"


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
                            "dayofweek INT NOT NULL,"
            "weekday TEXT NOT NULL,"
            "year INT NOT NULL,"
            "month INT NOT NULL,"
                            "day INT NOT NULL");


    QSqlQuery query(database);
    QDate startDate(1980, 1, 1);
    QDate endDate(2039, 1, 1);
    query.exec("BEGIN TRANSACTION");
    for (QDate date = startDate; date <= endDate; date = date.addDays(1)) {
        query.prepare(R"(
            INSERT OR IGNORE INTO calendar
            (d, dayofweek, weekday, year, month, day)
            VALUES (?, ?, ?, ?, ?, ?)
        )");
        query.addBindValue(date.toString("yyyy-MM-dd"));
        query.addBindValue((date.dayOfWeek() + 5) % 7);
        query.addBindValue(QLocale::system().dayName(date.dayOfWeek(), QLocale::LongFormat));
        query.addBindValue(date.year());
        query.addBindValue(date.month());
        query.addBindValue(date.day());
        if (!query.exec()) {
            //qWarning() << "Insert error:" << query.lastError().text();
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
