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

    QString getDate();
};

#endif // INPUTDIALOGDEADLINE_H
