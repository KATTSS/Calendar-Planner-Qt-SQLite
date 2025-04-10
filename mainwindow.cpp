#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    layout = new QHBoxLayout(centralWidget);

    menu = new QMenuBar(this);
    setMenuWidget(menu);

    add = menu->addAction("add");
    remove = menu->addAction("remove");

    calendarDb = DatabaseManager::instance().calendarDatabase();
    tasksDb = DatabaseManager::instance().tasksDatabase();

    calendar = new QTableWidget(6, 7, this);
    calendar->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    calendar->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    updateCalendar();

    calendarLayout = new QVBoxLayout(this);
    layout->addLayout(calendarLayout, 6);

    buttonLayout = new QHBoxLayout(this);
    calendarLayout->addLayout(buttonLayout);

    calendarLayout->addWidget(calendar);


    previousMonth = new QPushButton("<", this);
    monthAndYear = new QLineEdit(this);
    monthAndYear->setReadOnly(true);
    monthAndYear->setFocusPolicy(Qt::NoFocus);
    nextMonth = new QPushButton(">", this);
    buttonLayout->addWidget(previousMonth);
    buttonLayout->addWidget(monthAndYear);
    buttonLayout->addWidget(nextMonth);

    list = new TasksList(this);
    layout->addWidget(list);

    contMenu = new ContMenu(this);

    connect(previousMonth, &QPushButton::clicked, this, &MainWindow::on_previousMonth_clicked);
    connect(nextMonth, &QPushButton::clicked, this, &MainWindow::on_nextMonth_clicked);

    connect(calendar, &QTableWidget::doubleClicked, this, &MainWindow::getSelectedDateText);
    connect(calendar, &QTableWidget::cellDoubleClicked, contMenu, &ContMenu::showContextMenu);

    connect(calendar, &QTableWidget::cellDoubleClicked, this, [this](int row, int col) {
        QTableWidgetItem* item = calendar->item(row, col);
        if (item && !item->text().isEmpty()) {
            int day = item->text().toInt();
            QDate selectedDate(currentMonth.year(), currentMonth.month(), day);
            DateManager::instance().setSelectedDate(selectedDate);
            contMenu->showContextMenu(row, col);
             list->updateTasks(tasksDb->getTasksAtDate(selectedDate));
        }
    });

    connect(&DateManager::instance(), &DateManager::newTaskAdded, this, &MainWindow::updateCalendar);

    updateMonthAndYearLineEdit(getDateMonthYear(QDate::currentDate()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_previousMonth_clicked()
{
    currentMonth= currentMonth.addMonths(-1);
    updateCalendar();
    updateMonthAndYearLineEdit(getDateMonthYear(currentMonth));
}

void MainWindow::on_nextMonth_clicked()
{
    currentMonth= currentMonth.addMonths(1);
    updateCalendar();
    updateMonthAndYearLineEdit(getDateMonthYear(currentMonth));
}

QString MainWindow::getSelectedDateText()
{
    qDebug() << calendar->selectedItems()[0]->text();
    return calendar->selectedItems()[0]->text();
}


void MainWindow::updateCalendar()
{
    calendar->clear();
    calendar->setRowCount(6);
    calendar->setColumnCount(7);
    calendar->setHorizontalHeaderLabels({"Пн", "Вт", "Ср", "Чт", "Пт", "Сб", "Вс"});
    QDate currentDate1 = QDate::currentDate();
    QDate currentDate = currentDate1.addMonths(currentMonth.month() - currentDate1.month());
    QVector<QDate> dates = calendarDb->getDatesForMonth(currentDate.year(), currentDate.month());

    int firstDay = currentDate.addDays(-(currentDate.day() - 1)).dayOfWeek() % 7;
    if (firstDay == 0) firstDay = 7;

    int row = 0, col = firstDay - 1;
    for (const QDate &date : dates) {
        if (col >= 7) {
            col = 0;
            row++;
        }

        QTableWidgetItem *item = new QTableWidgetItem(QString::number(date.day()));

        QSqlQuery taskQuery(tasksDb->database);
        taskQuery.prepare("SELECT description FROM tasks WHERE date = ?");
        taskQuery.addBindValue(date.toString("yyyy-MM-dd"));
        if (taskQuery.exec() && taskQuery.next()) {
            item->setBackground(Qt::yellow);
            item->setToolTip(taskQuery.value(0).toString());
        }
        calendar->setItem(row, col, item);
        col++;
    }

   // updateMonthAndYearLineEdit(getDateMonthYear(currentDate));
}


QString MainWindow::getDateMonthYear(const QDate date)
{
    monthAndYear->clear();
    int x=date.month();
    QString monthYear;
    switch (x) {
    case 1:
        monthYear="january";
        break;
    case 2:
        monthYear="february";
        break;
    case 3:
        monthYear="march";
        break;
    case 4:
        monthYear="april";
        break;
    case 5:
        monthYear="may";
        break;
    case 6:
        monthYear="june";
        break;
    case 7:
        monthYear="july";
        break;
    case 8:
        monthYear="august";
        break;
    case 9:
        monthYear="september";
        break;
    case 10:
        monthYear="october";
        break;
    case 11:
        monthYear="november";
        break;
    case 12:
        monthYear="december";
        break;
    }
    monthYear += " " + QString::number(date.year());
    return monthYear;
}

void MainWindow::updateMonthAndYearLineEdit(const QString &monthandyear)
{
    monthAndYear->clear();
    monthAndYear->setText(monthandyear);
}

