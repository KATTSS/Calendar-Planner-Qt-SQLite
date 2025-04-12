#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QMenuBar>
#include <QPushButton>
#include <QLineEdit>
#include <QDate>
#include <QHeaderView>
#include <QMutex>
#include <QScrollBar>
#include <QTimer>

#include "taskslist.h"
#include "contmenu.h"
#include "datemanager.h"
#include "databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_previousMonth_clicked();

    void on_nextMonth_clicked();

    QString getSelectedDateText();

private:
    Ui::MainWindow *ui;
    QMenuBar *menu;

    QHBoxLayout *layout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *calendarLayout;

    QAction *add;
    QAction *remove;

    Database* calendarDb;
    Database* tasksDb;
    QSqlTableModel *model;
    QTableWidget *calendar;

    QDate currentMonth = QDate::currentDate();
    QPushButton *nextMonth;
    QPushButton *previousMonth;
    QLineEdit *monthAndYear;
    TasksList *list;

    ContMenu *contMenu;

   // QDate m_lastSelectedDate;
    QMutex m_updateMutex;
    bool m_isUpdating = false;

    void updateAll();
    void updateCalendar();
    void updateTasksList(QDate date);
    QDate getSelectedDate();
    void selectDateInCalendar(const QDate &date);
    QString getDateMonthYear(const QDate date);
    void updateMonthAndYearLineEdit(const QString &monthandyear);


};
#endif // MAINWINDOW_H
