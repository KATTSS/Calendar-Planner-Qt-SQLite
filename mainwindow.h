#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QMenuBar>
#include <QPushButton>

#include <QDate>

// #include <QDebug>
// #include <QSqlQuery>
// #include <QSqlTableModel>

#include "database.h"
#include "taskslist.h"

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
    QMenuBar *menu;

    QHBoxLayout *layout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *calendarLayout;

    QAction *add;
    QAction *remove;

    Database *dat;
    Database *tasks;
    QSqlTableModel *model;
    QTableWidget *calendar;

    QDate currentMonth = QDate::currentDate();
    QPushButton *nextMonth;
    QPushButton *previousMonth;

    TasksList *list;

    void updateCalendar();
};
#endif // MAINWINDOW_H
