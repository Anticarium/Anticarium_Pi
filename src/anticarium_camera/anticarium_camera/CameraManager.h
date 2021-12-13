#pragma once
#include <QTimer>
#include <anticarium_camera/PiImage.hpp>
#include <raspicam/raspicam.h>

class CameraManager : public QObject {
    Q_OBJECT
  public:
    CameraManager(QObject* parent = nullptr);
    virtual ~CameraManager();

  signals:
    void sendImageEvent(const PiImage& piImage);

  public slots:
    // Allows to send image
    void onNextImage();

    void start();

  private slots:
    // Takes picture and stores it
    void grab();


  private:
    raspicam::RaspiCam camera;
    QTimer* captureTimer = nullptr;

    bool canSend = true;

    // Keeps track on which image must be sent next
    unsigned int counter = 0;

    static const int MAX_IMAGES = 5;

    // Stored images
    std::array<std::shared_ptr<unsigned char[]>, MAX_IMAGES> images;
};
