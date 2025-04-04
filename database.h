#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>

#include <QDebug>

class Database
{
public:
    Database(const QString& dbPath);
    ~Database();

    bool open();
    void close();

    bool createTable(const QString &tableName, const QString &tableSchema);
    QSqlTableModel *createTableModel(const QString& tableName, QObject* parent = nullptr);


private :
    QSqlDatabase database;
};

#endif // DATABASE_H
