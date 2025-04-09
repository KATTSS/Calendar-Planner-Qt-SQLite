#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDate>

#include <QDebug>


class Database
{
public:
    Database(const QString& dbPath, const QString &connection);
    ~Database();

    bool open();
    void close();
    void cleanTable(const QString& dbName);
    QSqlTableModel *selectCurrentMonthDates(QObject *parent);
    bool createTable(const QString &tableName, const QString &tableSchema);
    QSqlTableModel *createTableModel(const QString& tableName, QObject* parent = nullptr);
    bool createCalendar();

    QVector<QDate> getDatesForMonth(int year, int month);
    //bool addTask(const QDate& date, const QString& description);
    // bool addTask(const QString& description);
    // QVector<QString> getTasksForDate(const QDate& date);
    // bool updateTaskStatus(int taskId, bool completed);

//private :
    QSqlDatabase database;
};

#endif // DATABASE_H
