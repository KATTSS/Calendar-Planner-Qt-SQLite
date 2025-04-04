#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// #include <QDebug>
// #include <QSqlQuery>
// #include <QSqlTableModel>

#include "database.h"
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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Calendar_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Database *dat;
    QSqlTableModel *model;

    int row=-1;
};
#endif // MAINWINDOW_H
