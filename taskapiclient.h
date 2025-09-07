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
    QNetworkAccessManager *manager;
signals:
    void tasksReceived(QJsonArray tasks);
};

#endif // TASKAPICLIENT_H
