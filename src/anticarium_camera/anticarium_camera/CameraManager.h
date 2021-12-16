#pragma once
#include <QObject>
#include <anticarium_camera/PiImage.hpp>
#include <raspicam/raspicam.h>

class CameraManager : public QObject {
    Q_OBJECT
  public:
    CameraManager(QObject* parent = nullptr);
    virtual ~CameraManager();

    // Processes grabbed image
    void grabbed(void* = nullptr);

  signals:
    void sendImageEvent(const PiImage& piImage);

  public slots:
    void start();

    void startCapture();

  private:
    raspicam::RaspiCam camera;

    // Stored image
    std::shared_ptr<unsigned char[]> image;
};
