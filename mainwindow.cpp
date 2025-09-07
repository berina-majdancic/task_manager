#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QJsonObject>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    APIClient = new TaskAPIClient(this);
    connect(APIClient, &TaskAPIClient::tasksReceived, this, &MainWindow::displayTasks);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addButton_clicked()
{
     // TODO: Send new task to Django backend
    APIClient->fetchTasks();
}

void MainWindow::displayTasks(const QJsonArray &tasks) {
    ui->taskListWidget->clear();
    for (const QJsonValue &taskVal : tasks) {
        QJsonObject task = taskVal.toObject();
        QString title = task["title"].toString();
        bool completed = task["completed"].toBool();

        QString itemText = title;
        if (completed) {
            itemText += ">";  // optional: show completed tasks
        }

        QListWidgetItem *item = new QListWidgetItem(itemText);
        ui->taskListWidget->addItem(item);
    }
}

