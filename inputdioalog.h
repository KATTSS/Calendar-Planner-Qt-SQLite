#ifndef INPUTDIOALOG_H
#define INPUTDIOALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

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
};

#endif // INPUTDIOALOG_H
