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
}
void MainWindow::on_deleteButton_clicked()
{
    QList taskList(ui->taskListWidget->selectedItems());
    if (taskList.isEmpty())
        return;

    QListWidgetItem task = *taskList[0];
    APIClient->deleteTask(task.data(Qt::UserRole + 2).value<QString>());
}
void MainWindow::on_editButton_clicked()
{
    QList taskList(ui->taskListWidget->selectedItems());
    if (taskList.isEmpty())
        return;
    QListWidgetItem task = *taskList[0];
    AddTaskDialog dialog(this);
    QString taskName = task.text();
    QString taskDescription = task.data(Qt::UserRole).value<QString>();
    QString taskId = task.data(Qt::UserRole + 2).value<QString>();

    dialog.setTaskInfo(taskName, taskDescription);
    dialog.setWindowTitle("Edit Task");
    if (dialog.exec() == QDialog::Accepted)
    {
        APIClient->editTask(taskId, dialog.getTaskName(), dialog.getTaskDescription());
    }
}
void MainWindow::displayTasks(const QJsonArray &tasks)
{
    ui->taskListWidget->clear();
    for (const QJsonValue &taskVal : tasks)
    {
        QJsonObject task = taskVal.toObject();
        QVariant idVariant = task["id"].toVariant();
        QString id = idVariant.toString();
        QString title = task["title"].toString();
        QString description = task["description"].toString();
        bool completed = task["completed"].toBool();

        QString itemText = title;

        QListWidgetItem *item = new QListWidgetItem(itemText);
        item->setData(Qt::UserRole, description);
        item->setData(Qt::UserRole + 1, completed);
        item->setData(Qt::UserRole + 2, id);

        ui->taskListWidget->addItem(item);
    }
}
