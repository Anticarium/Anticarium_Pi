#pragma once
#include <QTimer>
#include <raspicam/raspicam.h>

class AnticariumCameraManager : public QObject {
    Q_OBJECT
  public:
    AnticariumCameraManager(QObject* parent = nullptr);
    void run();
    virtual ~AnticariumCameraManager();

  private:
    raspicam::RaspiCam camera;
    QTimer* cameraCaptureTimeout = nullptr;
};
