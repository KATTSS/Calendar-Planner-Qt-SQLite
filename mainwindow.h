#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDate>
#include <QHeaderView>
#include <QMutex>
#include <QScrollBar>
#include <QTimer>
#include <QGridLayout>
#include "taskslist.h"
#include "contmenu.h"

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

private:
    Ui::MainWindow *ui;

   // QHBoxLayout *layout;
    QHBoxLayout *buttonLayout;
   // QVBoxLayout *calendarLayout;
    QGridLayout *dataLayout;

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
