#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "taskapiclient.h"
#include <QMainWindow>
#include <QJsonArray>

class QJsonArray;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    TaskAPIClient *APIClient;
    void displayTasks(const QJsonArray &tasks);
private slots:
    void on_addButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
