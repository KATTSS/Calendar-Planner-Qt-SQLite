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
    layout->addWidget(taskInputLine);
    layout->addWidget(save);

    connect(save, &QPushButton::clicked, this, &InputDioalog::on_saveButton_clicked);

    workWithData = new Database("./tasks.db", "taskss");
}

void InputDioalog::on_saveButton_clicked()
{
    qDebug() << "in save button";
    QString time = this->getTime();
    QString task = taskInputLine->text();
    QDate date = DateManager::instance().getSelectedDate();
    qDebug() << date;
    this->close();
}

QString InputDioalog::getTime()
{
    return QString::number(hours->value()) + ":" + QString::number(minutes->value());
}


