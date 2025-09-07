#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class AddTaskDialog;
}
QT_END_NAMESPACE

class AddTaskDialog : public QDialog
{
    Q_OBJECT

public:
    AddTaskDialog(QWidget *parent = nullptr);
    ~AddTaskDialog();

    const QString getTaskName();

    const QString getTaskDescription();

    void setTaskInfo(QString taskName, QString taskDescription);

private:
    Ui::AddTaskDialog *ui;
};

#endif // ADDTASKDIALOG_H