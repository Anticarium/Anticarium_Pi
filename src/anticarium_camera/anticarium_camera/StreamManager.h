#pragma once
#include <QThread>
#include <QTimer>
#include <anticarium_camera/Camera.h>
#include <anticarium_camera/Client.hpp>
#include <anticarium_camera/UDPListener.h>
#include <anticarium_camera/UDPSwitch.h>

class StreamManager : public QObject {
    Q_OBJECT
  public:
    StreamManager(QObject* parent = nullptr);
    void run();
    virtual ~StreamManager();

  private slots:
    void onStartAcquisition();
    void onStopAcquisition();

  private:
    enum Timeout { HEARTBEAT = 10000 };

    UDPSwitch* udpSwitch     = nullptr;
    UDPListener* udpListener = nullptr;
    Camera* camera           = nullptr;
    QThread* cameraThread    = nullptr;
    QTimer* heartbeatTimer   = nullptr;

    Client udpClientInfo;
};
