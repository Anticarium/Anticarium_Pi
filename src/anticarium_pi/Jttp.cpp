#include <QHttpMultiPart>
#include <anticarium_pi/Jttp.h>
#include <anticarium_pi/config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

JTTP::JTTP(QObject* parent) : QObject(parent) {
    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, &QNetworkAccessManager::finished, this, &JTTP::onDataArrived);
}

JTTP* JTTP::jttp = nullptr;

JTTP* JTTP::instance() {
    return jttp;
}

JTTP* JTTP::instance(QObject* parent) {
    if (jttp == nullptr) {
        jttp = new JTTP(parent);
    }
    return jttp;
}

void JTTP::onDataArrived(QNetworkReply* reply) {
    QString content = "";
    // checks if reply contains legitimate data
    if (reply->error()) {
        SPDLOG_ERROR(QString("QNetworkError: %1").arg(reply->errorString()).toStdString());
        return;
    } else {
        content = reply->rawHeader("Anticarium content description");
    }

    // reads reply into QString
    QString answer = reply->readAll();
    nlohmann::json jsonReply;
    if (content == "Control data") {
        jsonReply = nlohmann::json::parse(answer.toStdString());

        shared_types::Control controlData = jsonReply;
        emit dataReceivedEvent(controlData);
        return;
    }
}

void JTTP::onSendData(const shared_types::SensorData& sensorData) {
    httpSend(REQUEST_TYPE::SEND, REQUEST_DATA::SENSOR_DATA, sensorData);
}

void JTTP::onRequestData(REQUEST_DATA requestType) {
    httpSend(REQUEST_TYPE::REQUEST, requestType);
}

void JTTP::httpSend(REQUEST_TYPE requestType, REQUEST_DATA requestData, const nlohmann::json& passedJson) {
    QString requestTypeString = requestTypeMap[requestType];
    QString requestDataString = requestDataMap[requestData];
    QString url               = QString("http://87.110.30.10:5000/%1/%2").arg(requestTypeString, requestDataString);
    QNetworkRequest networkRequest;
    networkRequest.setUrl(url);

    if (requestType == REQUEST_TYPE::SEND) {
        post(networkAccessManager, networkRequest, passedJson);
    } else if (requestType == REQUEST_TYPE::REQUEST) {
        networkAccessManager->get(networkRequest);
    }
}

void JTTP::post(QNetworkAccessManager* accessManager, const QNetworkRequest& networkRequest, const nlohmann::json& passedJson) {
    QHttpMultiPart* httpMultiPart = new QHttpMultiPart(this);
    QHttpPart http;
    http.setBody(QString::fromStdString(passedJson.dump()).toUtf8());
    httpMultiPart->append(http);
    accessManager->post(networkRequest, httpMultiPart);
}


JTTP::~JTTP() {
}
