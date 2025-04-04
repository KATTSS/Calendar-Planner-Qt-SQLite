#include "database.h"

Database::Database(const QString& dbPath) {
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(dbPath);
}
Database::~Database()
{
    close();
}

bool Database::open()
{
    if (!database.open()) {
        qWarning() << "Failed to open database" ;//<< database.lastError().text();
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
