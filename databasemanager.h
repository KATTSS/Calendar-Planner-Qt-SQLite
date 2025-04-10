#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "database.h"

class DatabaseManager {
public:
    static DatabaseManager& instance();

    Database* calendarDatabase() const { return m_calendarDatabase; }
    Database* tasksDatabase() const { return m_tasksDatabase; }

private:
    DatabaseManager();
    ~DatabaseManager();

    Database* m_calendarDatabase;
    Database* m_tasksDatabase;
};
#endif // DATABASEMANAGER_H
