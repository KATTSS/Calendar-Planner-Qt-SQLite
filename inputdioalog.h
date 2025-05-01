#ifndef INPUTDIOALOG_H
#define INPUTDIOALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QComboBox>

#include "datemanager.h"
#include "databasemanager.h"

class InputDioalog : public QDialog
{
public:
    InputDioalog(QWidget *parent = nullptr);

private slots:
    void on_saveButton_clicked();

private:
    QLineEdit *taskInputLine;
    QLabel *label;
    QPushButton *save;
    QVBoxLayout *layout;
    QSpinBox *hours;
    QSpinBox *minutes;
    QComboBox *category;

    Database* tasksDb;

    QString getTime();
    int getCategoiesComboBox();
};

#endif // INPUTDIOALOG_H
