#ifndef TASKAPICLIENT_H
#define TASKAPICLIENT_H
#include <QJsonArray>
#include <QObject>
class QNetworkAccessManager;

class TaskAPIClient : public QObject
{
    Q_OBJECT
public:
    TaskAPIClient(QObject *parent = nullptr);

    void fetchTasks();
    void addTask(const QString &taskName, const QString &taskDescription);
    QNetworkAccessManager *manager;
    void deleteTask(const QString &taskName);
    void editTask(const QString &taskId, const QString &taskName, const QString &taskDescription);

signals:
    void tasksReceived(QJsonArray tasks);
};

#endif // TASKAPICLIENT_H
