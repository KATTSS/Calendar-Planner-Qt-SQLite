#include "inputdialog.h"
#include <QDebug>

InputDialog::InputDialog(QWidget *parent) : CategoriesDialog(parent) {
    mainLayout = this->layout;
    if (!mainLayout) {
        mainLayout = new QVBoxLayout(this);
        this->setLayout(mainLayout);
    }

    timeLayout = new QHBoxLayout();
    label = new QLabel("Set task", this);
    taskInputLine = new QLineEdit(this);

    hours = new QSpinBox(this);
    hours->setMaximum(23);
    hours->setMinimum(0);
    minutes = new QSpinBox(this);
    minutes->setMinimum(0);
    minutes->setMaximum(59);

    QLabel *timeLabel = new QLabel("Time:", this);

    timeLayout->addWidget(timeLabel);
    timeLayout->addWidget(hours);
    timeLayout->addWidget(minutes);

    // Добавляем новые элементы перед кнопкой OK из базового класса
    mainLayout->insertWidget(0, label);
    mainLayout->insertLayout(1, timeLayout);
    mainLayout->insertWidget(2, taskInputLine);

    tasksDb = DatabaseManager::instance().tasksDatabase();
}

void InputDialog::on_okButton_clicked()
{
    //qDebug() << "in save button";
    QString task = taskInputLine->text();
    if(task.isEmpty()) { this->close(); return;}
    QString time = getTime();
    int cat = this->getCategoiesComboBox();
    QDate date = DateManager::instance().getSelectedDate();

   // qDebug() << "Date:" << date << "Time:" << time << "Task:" << task << "Category:" << cat;

    if(tasksDb->open()) {
       // qDebug() << "database opened";
        tasksDb->addTask(date, time, task, cat, false, QDate(0,0,0));
        emit DateManager::instance().newTaskAdded();
    }
    this->close();
   // qDebug() << "saving was done";
}

QString InputDialog::getTime()
{
    QString hour = QString("%1").arg(hours->value(), 2, 10, QChar('0'));
    QString minute = QString("%1").arg(minutes->value(), 2, 10, QChar('0'));
    return hour + ":" + minute;
}

