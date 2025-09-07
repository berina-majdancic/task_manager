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

void TaskAPIClient::editTask(const QString &taskID, const QString &taskName, const QString &taskDescription)
{
    QNetworkRequest request(QUrl(QString("http://127.0.0.1:8000/api/tasks/%1/").arg(taskID)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json;
    json["title"] = taskName;
    json["description"] = taskDescription;
    json["completed"] = false;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();
    QNetworkReply *reply = manager->put(request, data);

    connect(reply, &QNetworkReply::finished, [this, reply]()
            {
            fetchTasks();
        reply->deleteLater(); });
}

void TaskAPIClient::deleteTask(const QString &taskId)
{
    QNetworkRequest request(QUrl(QString("http://127.0.0.1:8000/api/tasks/%1/").arg(taskId)));

    QNetworkReply *reply = manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, [this, reply]()
            {
            fetchTasks();
        reply->deleteLater(); });
}