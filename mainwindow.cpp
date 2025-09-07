#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addtaskdialog.h"

#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    APIClient = new TaskAPIClient(this);
    connect(APIClient, &TaskAPIClient::tasksReceived, this, &MainWindow::displayTasks);
    APIClient->fetchTasks();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
    AddTaskDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        QString taskName = dialog.getTaskName();
        QString taskDescription = dialog.getTaskDescription();

        qDebug() << "New Task:" << taskName;
        APIClient->addTask(taskName, taskDescription);
    }
    // TODO:Open a new window for typing task info
    // TODO: Send new task to Django backend
}
void MainWindow::on_deleteButton_clicked()
{
    // TODO: Send task to delete to Django backend
}
void MainWindow::on_editButton_clicked()
{
    // TODO: Send update task to Django backend
}
void MainWindow::displayTasks(const QJsonArray &tasks)
{
    ui->taskListWidget->clear();
    for (const QJsonValue &taskVal : tasks)
    {
        QJsonObject task = taskVal.toObject();
        QString title = task["title"].toString();
        bool completed = task["completed"].toBool();

        QString itemText = title;

        QListWidgetItem *item = new QListWidgetItem(itemText);
        ui->taskListWidget->addItem(item);
    }
}
