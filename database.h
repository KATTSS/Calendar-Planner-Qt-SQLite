#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDateTime>

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
    bool addTask(const QDate &date, const QString &time, const QString &description, int category);
    QMap<QDateTime, QString> getTasksAtDate(QDate &date);

    bool updateTaskStatus(int taskId, bool completed);
    bool  deleteTask(int taskId);
    QMap<QDateTime, QString> getTasksByCategory(int cat);
    QDate getOptimalDate(const QDate &deadline);

    QSqlDatabase database;
};

#endif // DATABASE_H
