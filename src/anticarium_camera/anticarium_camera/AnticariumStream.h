#pragma once
#include <QThread>
#include <anticarium_camera/CameraManager.h>
#include <anticarium_camera/UDPManager.h>

class AnticariumStream : public QObject {
    Q_OBJECT
  public:
    AnticariumStream(QObject* parent = nullptr);
    void run();
    virtual ~AnticariumStream();

  signals:
    void sendImageEvent(const PiImage& image);
    void requestNewImageEvent();

  private:
    UDPManager* udpManager       = nullptr;
    CameraManager* cameraManager = nullptr;
    QThread* cameraThread        = nullptr;
};
