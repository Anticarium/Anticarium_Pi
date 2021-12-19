#pragma once
#include <QObject>
#include <anticarium_camera/PiImage.hpp>
#include <raspicam/raspicam.h>

class Camera : public QObject {
    Q_OBJECT
  public:
    Camera(QObject* parent = nullptr);
    virtual ~Camera();

    // Processes grabbed image
    void grabbed(void* = nullptr);

  signals:
    void sendImageEvent(const PiImage& piImage);

  public slots:
    void start();

  private:
    raspicam::RaspiCam raspicam;

    // Stored image
    std::shared_ptr<unsigned char[]> image;
};
