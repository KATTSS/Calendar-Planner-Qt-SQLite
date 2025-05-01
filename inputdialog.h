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



// #ifndef INPUTDIALOG_H
// #define INPUTDIALOG_H

// //#include <QDialog>
// #include <QLineEdit>
// //#include <QPushButton>
// #include <QLabel>
// //#include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QSpinBox>
// //#include <QComboBox>

// //#include "datemanager.h"
// #include "databasemanager.h"
// #include "categoriesdialog.h"

// class InputDioalog : public CategoriesDialog
// {
// public:
//     InputDioalog(QWidget *parent = nullptr);
//     //InputDioalog(int x, QWidget *parent = nullptr);

//     void on_okButton_clicked() override;

// private:
//     QLineEdit *taskInputLine;
//     QLabel *label;
//     //QPushButton *save;
//     QVBoxLayout *layout;
//     QSpinBox *hours;
//     QSpinBox *minutes;
//    // QComboBox *category;

//     Database* tasksDb;

//     QString getTime();
//     //int getCategoiesComboBox();
//     //void initialiseCategory();
// };

// #endif // INPUTDIALOG_H
