#include "databasemanager.h"

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}DatabaseManager::DatabaseManager()
    : m_calendarDatabase(nullptr),
    m_tasksDatabase(nullptr)
{
    QString appDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/MyApp";
    QDir().mkpath(appDataDir);

    QString calendarDbPath = appDataDir + "/testCalendar.db";
    QString tasksDbPath = appDataDir + "/tasks.db";

    if (!QFile::exists(calendarDbPath)) {
        QFile::copy(":/data/testCalendar.db", calendarDbPath);
        QFile::setPermissions(calendarDbPath, QFile::ReadOwner | QFile::WriteOwner);
    }

    m_calendarDatabase = new Database(calendarDbPath, "calendar_connection");
    m_tasksDatabase = new Database(tasksDbPath, "tasks_connection");

    if (!m_calendarDatabase->open() || !m_tasksDatabase->open()) {
        qCritical() << "Ошибка открытия баз данных!";
        return;
    }

    if (!m_calendarDatabase->tableExists("calendar")) {
        m_calendarDatabase->createCalendar();
    }

    if (!m_tasksDatabase->tableExists("tasks")) {
        m_tasksDatabase->createTable("tasks",
                                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                "date TEXT NOT NULL, "
                                "time TEXT, "
                                "description TEXT, "
                                "category INT, "
                                "is_completed BOOLEAN DEFAULT 0, "
                                "is_deadline BOOLEAN DEFAULT 0,"
                                "deadline TEXT, "
                                "FOREIGN KEY(date) REFERENCES calendar(d)");
    }
}

DatabaseManager::~DatabaseManager()
{
    delete m_calendarDatabase;
    delete m_tasksDatabase;
}
