#include <QThread>
#include <QTimer>
#include <anticarium_camera/Camera.h>
#include <anticarium_camera/ImageProcess.h>
#include <config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

static Camera* cameraManager = nullptr;

static void imageGrabbed(void*) {
    cameraManager->grabbed();
}

Camera::Camera(QObject* parent) : QObject(parent) {
    cameraManager = this;

    auto settings  = ApplicationSettings::instance();
    auto imageSize = raspicam.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB);

    // Pre-allocate memory for image
    image = std::shared_ptr<unsigned char[]>(new unsigned char[imageSize]);

    raspicam.setFormat(raspicam::RASPICAM_FORMAT_BGR);
    raspicam.setUserCallback(imageGrabbed, image.get());
    raspicam.setFrameRate(settings->getFps());
}

void Camera::start() {
    if (raspicam.open()) {
        SPDLOG_INFO("Camera opened");
        // Wait for camera to warm up
        QThread::sleep(3);
        raspicam.startCapture();
    } else {
        SPDLOG_CRITICAL(QString("Failed to open the camera!").toStdString());
    }
}

void Camera::grabbed(void*) {
    raspicam.retrieve(image.get());

    // Construct PiImage for image processing and sending
    PiImage piImage;
    int width    = static_cast<int>(raspicam.getWidth());
    int height   = static_cast<int>(raspicam.getHeight());
    piImage.size = QSize(width, height);
    piImage.data = image;

    ImageProcess::writeRowId(piImage);

    SPDLOG_INFO("Image ready to be sent");
    emit sendImageEvent(piImage);
}

Camera::~Camera() {
}
