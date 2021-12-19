#pragma once
#include <QThread>
#include <QTimer>
#include <anticarium_camera/Camera.h>
#include <anticarium_camera/Client.hpp>
#include <anticarium_camera/UDPListener.h>
#include <anticarium_camera/UDPSender.h>

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

    UDPSender* udpSender     = nullptr;
    UDPListener* udpListener = nullptr;
    Camera* camera           = nullptr;
    QThread* cameraThread    = nullptr;
    QThread* udpSenderThread = nullptr;
    QTimer* heartbeatTimer   = nullptr;

    Client udpClient;
};
