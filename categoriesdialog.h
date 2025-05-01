#ifndef CATEGORIESDIALOG_H
#define CATEGORIESDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>

//#include "databasemanager.h"
#include "datemanager.h"
class CategoriesDialog : public QDialog
{
public:
    CategoriesDialog(QWidget *parent = nullptr);
private slots:
    void on_okButton_clicked();

private:
    QComboBox *category;
    QPushButton *ok;
    QVBoxLayout *layout;

    //Database* tasksDb;

    int getCategoiesComboBox();

};

#endif // CATEGORIESDIALOG_H
