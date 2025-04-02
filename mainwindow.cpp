#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("./testDatabase.db");
    if(database.open()) {
        qDebug() << "open";
    }

    query = new QSqlQuery(database);
    query->exec("CREATE TABLE DatesTable(Date DATE, Task TEXT);");

    model = new QSqlTableModel(this, database);
    model->setTable("DatesTable");
    model->select();
    ui->Calendar->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    model->insertRow(model->rowCount());

}


void MainWindow::on_pushButton_2_clicked()
{
    model->removeRow(row);
    model->select();
}


void MainWindow::on_Calendar_clicked(const QModelIndex &index)
{
    row = index.row();
}

