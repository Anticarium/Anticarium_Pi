#pragma once
#include <QTimer>
#include <QUdpSocket>
#include <memory>
#include <raspicam/raspicam.h>

class AnticariumStream : public QObject {
    Q_OBJECT
  public:
    AnticariumStream(QObject* parent = nullptr);
    void run();
    virtual ~AnticariumStream();

  private:
    raspicam::RaspiCam camera;
    QTimer* captureTimer = nullptr;

    // Takes picture and stores it
    void grab();

    QUdpSocket* udpSocket;
};
