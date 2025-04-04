#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dat = new Database("./testDatabase.db");
    if (!dat->open()) {
        qCritical() << "Cannot proceed without database!";
        return;
    }
    dat->createTable("DatesTable", "Date TEXT, Task TEXT");

    model=dat->createTableModel("DatesTable", this);
    ui->Calendar->setModel(model);

}

MainWindow::~MainWindow()
{
    delete dat;
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

