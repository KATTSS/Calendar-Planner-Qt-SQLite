#include "inputdialogdeadline.h"

InputDialogDeadline::InputDialogDeadline(QWidget *parent) : InputDialog(parent)
{
    mainLayout = this->layout;
    if (!mainLayout) {
        mainLayout = new QVBoxLayout(this);
        this->setLayout(mainLayout);
    }

    dateLayout = new QHBoxLayout(this);

    dateLabel = new QLabel("Date: ", this);

    day = new QSpinBox(this);
    day->setMinimum(1);
    day->setMaximum(31);
    month = new QSpinBox(this);
    month->setMinimum(1);
    month->setMaximum(12);

    dateLayout->addWidget(dateLabel);
    dateLayout->addWidget(day);
    dateLayout->addWidget(month);

    mainLayout->insertLayout(1, dateLayout);
}

void InputDialogDeadline::on_okButton_clicked()
{
    QString task = taskInputLine->text();
    if(task.isEmpty()) { this->close(); return;}
    QString time = getTime();
    int cat = this->getCategoiesComboBox();
    QDate deadline = getDeadlineDate();
    if (deadline == QDate()) {this->close(); return;}
    QDate date = tasksDb->getOptimalDate(deadline);

    if(tasksDb->open()) {
        tasksDb->addTask(deadline, time, task, cat);
        task+="(" + getDate() + ")";
        tasksDb->addTask(date, time, task, cat, true, deadline);
        emit DateManager::instance().newTaskAdded();
    }
    this->close();
}

QDate InputDialogDeadline::getDeadlineDate()
{
    QDate deadline(QDate::currentDate().year(), month->value(), day->value());
    if (deadline < QDate::currentDate()) return deadline.addYears(1);
    if (!deadline.isValid()) return QDate();
    return deadline;
}

QString InputDialogDeadline::getDate()
{
    QString dayy = QString("%1").arg(day->value(), 2, 10, QChar('0'));
    QString mmonth = QString("%1").arg(month->value(), 2, 10, QChar('0'));
    return dayy + "-" + mmonth;
}


