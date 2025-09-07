#include "addtaskdialog.h"
#include "./ui_addtaskdialog.h"

AddTaskDialog::AddTaskDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AddTaskDialog)
{
    ui->setupUi(this);
}

AddTaskDialog::~AddTaskDialog()
{
    delete ui;
}

const QString AddTaskDialog::getTaskName()
{
    return ui->taskNameLineEdit->text();
}

const QString AddTaskDialog::getTaskDescription()
{
    return ui->taskDescriptionLineEdit->text();
}

void AddTaskDialog::setTaskInfo(QString taskName, QString taskDescription)
{
    ui->taskNameLineEdit->setText(taskName);
    ui->taskDescriptionLineEdit->setText(taskDescription);
}
