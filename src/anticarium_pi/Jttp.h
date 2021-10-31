#pragma once

#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <nlohmann/json.hpp>
#include <shared_types/Control.h>
#include <shared_types/SensorData.h>

class JTTP : public QObject {
    Q_OBJECT
  public:
    enum class REQUEST_DATA {
        CONTROL_DATA, // Request Control json
        SENSOR_DATA   // Request SensorData json
    };

    enum class REQUEST_TYPE {
        REQUEST, // Request json
        SEND     // Send json
    };

    // singleton design pattern
    JTTP()       = delete;
    void operator=(const JTTP&) = delete;

    // Constructs and returns pointer to objet
    static JTTP* instance(QObject* parent);
    // Returns pointer to object
    static JTTP* instance();

  private:
    // private constructor for singleton
    JTTP(QObject* parent = nullptr);
    static JTTP* jttp;
    ~JTTP();

    // HTTP communication objects
    QNetworkAccessManager* networkAccessManager = nullptr;
    QNetworkRequest networkRequest;

    QMap<REQUEST_DATA, QString> requestDataMap = {
        { REQUEST_DATA::CONTROL_DATA, "control" },   // Request Control json url expansion
        { REQUEST_DATA::SENSOR_DATA, "sensor_data" } // Request SensorData json url expansion
    };

    QMap<REQUEST_TYPE, QString> requestTypeMap = {
        { REQUEST_TYPE::REQUEST, "request" }, // Request url expansion
        { REQUEST_TYPE::SEND, "send" }        // Send url expansion
    };

    // Builds url and does HTTP GET or POST
    void httpSend(REQUEST_TYPE requestType, REQUEST_DATA requestData, const nlohmann::json& passedJson = nlohmann::json());

  signals:
    void dataReceivedEvent(const shared_types::Control& control);
  private slots:
    void onDataArrived(QNetworkReply* reply);
  public slots:
    void onSendData(const shared_types::SensorData& newSensorData);
    void onRequestData(REQUEST_DATA requestType);
};
