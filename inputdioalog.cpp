#include "inputdioalog.h"

#include <QDebug>

InputDioalog::InputDioalog(QWidget *parent) : QDialog(parent) {
    layout = new QVBoxLayout(this);

    label = new QLabel("Set task", this);
    taskInputLine = new QLineEdit(this);
    save = new QPushButton("save", this);

    layout->addWidget(label);
    layout->addWidget(taskInputLine);
    layout->addWidget(save);

    connect(save, &QPushButton::clicked, this, &InputDioalog::on_saveButton_clicked);
}

void InputDioalog::on_saveButton_clicked()
{
    qDebug() << "in save button";
    this->close();
}
