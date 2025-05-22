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
  //  qDebug() << "ready to place before deadline time(" << getDate() << ")";
    //emit DateManager::instance().newDeadline(getDeadlineDate());
    QString task = taskInputLine->text();
    QString time = getTime();
    int cat = this->getCategoiesComboBox();
    QDate date = tasksDb->getOptimalDate(getDeadlineDate());
    QDate deadline = getDeadlineDate();

    //qDebug() << "Date:" << date << "Time:" << time << "Task:" << task << "Category:" << cat;

    if(tasksDb->open()) {
        //qDebug() << "database opened";
        tasksDb->addTask(deadline, time, task, cat, true);
        task+="(" + getDate() + ")";
        tasksDb->addTask(date, time, task, cat);
        emit DateManager::instance().newTaskAdded();
    }
    //qDebug() << "saving was done";
    this->close();
}

QDate InputDialogDeadline::getDeadlineDate()
{
    QDate deadline(QDate::currentDate().year(), month->value(), day->value());
    return (deadline < QDate::currentDate() || !deadline.isValid()) ? QDate::currentDate() : deadline;
}

QString InputDialogDeadline::getDate()
{
    QString dayy = QString("%1").arg(day->value(), 2, 10, QChar('0'));
    QString mmonth = QString("%1").arg(month->value(), 2, 10, QChar('0'));
    return dayy + "-" + mmonth;
}


