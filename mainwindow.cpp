#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // menu = this->menuBar();
    // sortMenu = menu->addMenu("Sort");
    // sortByCategory = sortMenu->addAction("Sort by event category");

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    layout = new QHBoxLayout(centralWidget);

    calendarDb = DatabaseManager::instance().calendarDatabase();
    tasksDb = DatabaseManager::instance().tasksDatabase();

    calendar = new QTableWidget(6, 7, this);
    calendar->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
    list->setStyleSheet("font-size : 16px;");

    contMenu = new ContMenu(this);

   // connect(sortByCategory, &QAction::triggered, this, &MainWindow::on_sortByCategory_clicked);

    connect(previousMonth, &QPushButton::clicked, this, &MainWindow::on_previousMonth_clicked);
    connect(nextMonth, &QPushButton::clicked, this, &MainWindow::on_nextMonth_clicked);

    //connect(calendar, &QTableWidget::doubleClicked, this, &MainWindow::getSelectedDateText);

    connect(calendar, &QTableWidget::cellClicked, this, [this](int row, int col) {
        QTableWidgetItem* item = calendar->item(row, col);
        if (item && !item->text().isEmpty()) {
            int day = item->text().toInt();
            QDate selectedDate(currentMonth.year(), currentMonth.month(), day);
            updateTasksList(selectedDate);
        }
    });


    connect(calendar, &QTableWidget::cellDoubleClicked, this, [this](int row, int col) {
        getSelectedDateText();
        QTableWidgetItem* item = calendar->item(row, col);
        if (item && !item->text().isEmpty()) {
            int day = item->text().toInt();
            QDate selectedDate(currentMonth.year(), currentMonth.month(), day);
            DateManager::instance().setSelectedDate(selectedDate);
            contMenu->showContextMenu(row, col);
        }
    });

    connect(&DateManager::instance(), &DateManager::newTaskAdded, this, [this]() {
        QTimer::singleShot(0, this, &MainWindow::updateAll);
    }, Qt::QueuedConnection);

    connect(&DateManager::instance(), &DateManager::categorySelected, this, [this](int id) {
        qDebug() << "there will be updation ot categorised tasks";
        QMap<QDateTime, QString> tasks = tasksDb->getTasksByCategory(id);
        list->setWriteDateTrue();
        list->updateTasks(tasks);
    });

    // connect(&DateManager::instance(), &DateManager::newDeadline, this, [this](QDate deadline){
    //     QDate date = tasksDb->getOptimalDate(deadline);

    // })

    list->setDeleteHandler([this](int taskId) {
        tasksDb->deleteTask(taskId);
        updateCalendar();
    });

    updateMonthAndYearLineEdit(getDateMonthYear(QDate::currentDate()));
    // centralWidget->setGeometry(0, menu->height(), window()->width(), window()->height()-menu->height());
    // qDebug() << "Calendar geometry:" << calendar->geometry();
    // qDebug() << "MenuBar geometry:" << menu->geometry();
    // qDebug () << centralWidget->geometry()
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

// void MainWindow::on_sortByCategory_clicked()
// {
//     qDebug() << "in action";
// }

QString MainWindow::getSelectedDateText()
{
    if(!calendar->selectedItems()[0]->text().isEmpty()) {
    qDebug() << calendar->selectedItems()[0]->text();
    return calendar->selectedItems()[0]->text();
    }
    else
        qDebug() << "no items in this calendar slot";
    return QString::number(QDate::currentDate().day());
}

void MainWindow::updateAll()
{
    if (m_isUpdating) return;
    m_isUpdating = true;
    if (m_updateMutex.tryLock()) {
        QDate currentDate = getSelectedDate();

        updateCalendar();

        if (currentDate.isValid()) {
            updateTasksList(currentDate);
        }

        m_updateMutex.unlock();
    }
    m_isUpdating=false;
}

void MainWindow::updateCalendar()
{

   // if (!m_updateMutex.tryLock()) return;

    QScrollBar *vScroll = calendar->verticalScrollBar();
    QScrollBar *hScroll = calendar->horizontalScrollBar();
    int vValue = vScroll->value();
    int hValue = hScroll->value();

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
        if(date==currentDate1) item->setBackground(QColor("#191970"));
        calendar->setItem(row, col, item);
        col++;
    }
    vScroll->setValue(vValue);
    hScroll->setValue(hValue);

    m_updateMutex.unlock();
}

void MainWindow::updateTasksList(QDate date)
{
    qDebug() << "Updating tasks for:" << date;
    QMap<QDateTime, QString> tasks = tasksDb->getTasksAtDate(date);
    list->updateTasks(tasks);
}

QDate MainWindow::getSelectedDate()
{
    auto items = calendar->selectedItems();
    if (items.isEmpty()) return QDate();

    bool ok;
    int day = items.first()->text().toInt(&ok);
    return ok ? QDate(currentMonth.year(), currentMonth.month(), day) : QDate();
}

void MainWindow::selectDateInCalendar(const QDate &date)
{
    for (int row = 0; row < calendar->rowCount(); ++row) {
        for (int col = 0; col < calendar->columnCount(); ++col) {
            if (auto item = calendar->item(row, col)) {
                if (item->text().toInt() == date.day()) {
                    calendar->setCurrentCell(row, col);
                    return;
                }
            }
        }
    }
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

