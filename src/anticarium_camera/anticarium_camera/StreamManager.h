#pragma once
#include <QThread>
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

  signals:
    void requestNewImageEvent();

  private:
    UDPSender* udpSender     = nullptr;
    UDPListener* udpListener = nullptr;
    Camera* camera           = nullptr;
    QThread* cameraThread    = nullptr;
    QThread* udpSenderThread = nullptr;

    Client udpClient;
};
