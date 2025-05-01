#ifndef INPUTDIALOGDEADLINE_H
#define INPUTDIALOGDEADLINE_H
#include "inputdialog.h"

class InputDialogDeadline : public InputDialog
{
public:
    InputDialogDeadline(QWidget *parent = nullptr);
    void on_okButton_clicked() override;

private :
    QSpinBox *day;
    QSpinBox *month;
    QLabel *dateLabel;

    QHBoxLayout *dateLayout;

    QDate getDeadlineDate();
    void saveTaskByDeadline(const QDate deadline);

    QString getDate();
};

#endif // INPUTDIALOGDEADLINE_H
