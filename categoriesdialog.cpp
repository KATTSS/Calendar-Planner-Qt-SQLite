#include "categoriesdialog.h"

CategoriesDialog::CategoriesDialog(QWidget *parent): QDialog(parent) {
    layout = new QVBoxLayout(this);
    category = new QComboBox(this);

    category->addItem("Entertainment", 1);
    category->addItem("Meeting", 2);
    category->addItem("Sport", 3);
    category->addItem("Work", 4);
    category->addItem("HealthCare", 5);
    category->addItem("Other", 6);

    ok = new QPushButton("ok", this);
    layout->addWidget(category);
    layout->addWidget(ok);

   // tasksDb = DatabaseManager::instance().tasksDatabase();

    connect(ok, &QPushButton::clicked, this, &CategoriesDialog::on_okButton_clicked);
}

void CategoriesDialog::on_okButton_clicked()
{
    int cat = this->getCategoiesComboBox();
    emit DateManager::instance().categorySelected(cat);
    this->close();
}

int CategoriesDialog::getCategoiesComboBox()
{
    QVariant data = category->currentData();
    if (data.isValid() && data.canConvert<int>()) {
        int id = data.toInt();
        return id;
    }
    return 0;
}

void CategoriesDialog::initialiseCategory()
{
    category->addItem("Entertainment", 1);
    category->addItem("Meeting", 2);
    category->addItem("Sport", 3);
    category->addItem("Work", 4);
    category->addItem("HealthCare", 5);
    category->addItem("Other", 6);
}
