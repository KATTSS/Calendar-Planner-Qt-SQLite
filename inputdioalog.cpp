#include "inputdioalog.h"

#include <QDebug>

InputDioalog::InputDioalog(QWidget *parent) : QDialog(parent) {
    layout = new QVBoxLayout(this);
    QHBoxLayout *timeLayout = new QHBoxLayout(this);
    layout->addLayout(timeLayout);

    label = new QLabel("Set task", this);
    taskInputLine = new QLineEdit(this);
    save = new QPushButton("save", this);

    layout->addWidget(label);

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

    category=new QComboBox(this);
    layout->addWidget(category);

    category->addItem("Entertainment", 1);
    category->addItem("Meeting", 2);
    category->addItem("Sport", 3);
    category->addItem("Work", 4);
    category->addItem("HealthCare", 5);
    category->addItem("Other", 6);
    layout->addWidget(taskInputLine);
    layout->addWidget(save);

    connect(save, &QPushButton::clicked, this, &InputDioalog::on_saveButton_clicked);

    tasksDb = DatabaseManager::instance().tasksDatabase();
}

void InputDioalog::on_saveButton_clicked()
{
    qDebug() << "in save button";
    QString time = this->getTime();
    QString task = taskInputLine->text();
    int cat = this->getCategoiesComboBox();
    QDate date = DateManager::instance().getSelectedDate();
    qDebug() << date;
    if(tasksDb->open()) {
        qDebug() << "database opened)";
        tasksDb->addTask(date, time, task, cat);
        emit DateManager::instance().newTaskAdded();
    }
    this->close();
}

QString InputDioalog::getTime()
{
    QString min = QString::number(minutes->value());
    if(min.length()==1) {
    min.at(0)=='0' ? min.append('0') : min.insert(0, '0');
    }
    QString hour = QString::number(hours->value());
    if(hour.length()==1) {
        hour.insert(0, '0');
    }
    return hour + ":" + min;
}

int InputDioalog::getCategoiesComboBox()
{
    QVariant data = category->currentData();
    if (data.isValid() && data.canConvert<int>()) {
        int id = data.toInt();
        return id;
    }
    return 0;
}




