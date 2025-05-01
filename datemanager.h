#ifndef DATEMANAGER_H
#define DATEMANAGER_H

#include <QObject>
#include <QDate>

class DateManager : public QObject
{
    Q_OBJECT
public:
    static DateManager& instance();

    void setSelectedDate(const QDate& date);
    QDate getSelectedDate() const;

signals:
    void dateChanged(const QDate& date);
    void newTaskAdded();
    void categorySelected(const int id);
   // void newDeadline(const QDate& date);

private:
    DateManager();
    QDate m_selectedDate;
};

#endif // DATEMANAGER_H
