#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QSpinBox>
#include "databasemanager.h"
#include "categoriesdialog.h"

class InputDialog : public CategoriesDialog
{
public:
    InputDialog(QWidget *parent = nullptr);
    void on_okButton_clicked() override;

protected:
    QLineEdit *taskInputLine;
    QLabel *label;
    QVBoxLayout *mainLayout;
    QHBoxLayout *timeLayout;
    QSpinBox *hours;
    QSpinBox *minutes;
    Database* tasksDb;

    QString getTime();
};
#endif // INPUTDIALOG_H

