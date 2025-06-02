#include "datemanager.h"

DateManager &DateManager::instance()
{
    static DateManager instance;
    return instance;
}

DateManager::DateManager() : m_selectedDate(QDate::currentDate()) {}

void DateManager::setSelectedDate(const QDate& date)
{
    if (date != m_selectedDate) {
        m_selectedDate = date;
        emit dateChanged(date);
    }
}

QDate DateManager::getSelectedDate() const
{
    return m_selectedDate;
}
