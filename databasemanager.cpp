#include "databasemanager.h"

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager()
    : m_calendarDatabase(new Database("./testCalendar.db", "dates")),
    m_tasksDatabase(new Database("./tasks.db", "tasks"))
{
    if (!m_calendarDatabase->open()) {
        qCritical() << "Failed to open calendar database!";
    }

    if (!m_tasksDatabase->open()) {
        qCritical() << "Failed to open tasks database!";
    }

    m_calendarDatabase->createCalendar();
    m_tasksDatabase->createTable("tasks",
                                 "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                 "date TEXT NOT NULL, "
                                 "time TEXT, "
                                 "description TEXT, "
                                 "category INT, "
                                 "is_completed BOOLEAN DEFAULT 0, "
                                 "FOREIGN KEY(date) REFERENCES calendar(d)"
                                 );
}

DatabaseManager::~DatabaseManager()
{
    delete m_calendarDatabase;
    delete m_tasksDatabase;
}
