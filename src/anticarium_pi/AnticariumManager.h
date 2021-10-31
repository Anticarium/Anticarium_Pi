#pragma once
#include <anticarium_pi/Jttp.h>
#include <anticarium_pi/WeatherManager.h>

class AnticariumManager : public QObject {
    Q_OBJECT
  public:
    AnticariumManager(QObject* parent = nullptr);
    void run();
    virtual ~AnticariumManager();

  private slots:
    // Puts incoming control data into action
    void applyData(const shared_types::Control& control);

    // Request Control data
    void onRequestControl();

    // Get and send SensorData
    void onSendSensorData();

  signals:
    void requestDataEvent(JTTP::REQUEST_DATA requestData);
    void sendDataEvent(const shared_types::SensorData& sensorData);

  private:
    enum TIMEOUT {
        CONTROL     = 1000, // Fetch timeout for Control
        SENSOR_DATA = 1000  //Fetch timeout for SensorData
    };

    WeatherManager* weatherManager = nullptr;
    QTimer* fetchControlTimer      = nullptr;
    QTimer* sendSensorDataTimer    = nullptr;
};
