#include "taskapiclient.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>

#include <QJsonObject>
#include <qeventloop.h>

TaskAPIClient::TaskAPIClient(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
}

void TaskAPIClient::fetchTasks()
{
    QNetworkRequest request(QUrl("http://127.0.0.1:8000/api/tasks/"));
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, [this, reply]()
            {
        if(reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonArray tasks = jsonDoc.array();

            emit tasksReceived(tasks);
        } else {
            qDebug() << "Error fetching tasks:" << reply->errorString();
        }
        reply->deleteLater(); });
}

void TaskAPIClient::addTask(const QString &taskName, const QString &taskDescription)
{
    QNetworkRequest request(QUrl("http://127.0.0.1:8000/api/tasks/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject task;
    task["title"] = taskName;
    task["description"] = taskDescription;
    QJsonDocument doc(task);
    QByteArray data = doc.toJson();

    QNetworkReply *reply = manager->post(request, data);

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, [this, reply]()
            {
        if (reply->error() == QNetworkReply::NoError)
        {
            fetchTasks();
        }
        reply->deleteLater(); });
}
