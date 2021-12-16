#pragma once
#include <QThread>
#include <anticarium_camera/CameraManager.h>
#include <anticarium_camera/Client.hpp>
#include <anticarium_camera/UDPListener.h>
#include <anticarium_camera/UDPSender.h>

class AnticariumStream : public QObject {
    Q_OBJECT
  public:
    AnticariumStream(QObject* parent = nullptr);
    void run();
    virtual ~AnticariumStream();

  signals:
    void requestNewImageEvent();

  private:
    UDPSender* udpSender         = nullptr;
    UDPListener* udpListener     = nullptr;
    CameraManager* cameraManager = nullptr;
    QThread* cameraThread        = nullptr;
    QThread* udpSenderThread     = nullptr;

    Client udpClient;
};
