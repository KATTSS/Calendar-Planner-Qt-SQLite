#ifndef CATEGORIESDIALOG_H
#define CATEGORIESDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>

#include "datemanager.h"
class CategoriesDialog : public QDialog
{
public:
    CategoriesDialog(QWidget *parent = nullptr);
    virtual void on_okButton_clicked();
    int getCategoiesComboBox();
    void initialiseCategory();

//private:
protected:
    QComboBox *category;
    QPushButton *ok;
    QVBoxLayout *layout;


};

#endif // CATEGORIESDIALOG_H
