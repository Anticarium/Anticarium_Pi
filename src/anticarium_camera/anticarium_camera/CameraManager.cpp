#include <QTimer>
#include <anticarium_camera/CameraManager.h>
#include <anticarium_camera/ImageProcess.h>
#include <config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

static CameraManager* cameraManager = nullptr;

static void imageGrabbed(void*) {
    cameraManager->grabbed();
}

CameraManager::CameraManager(QObject* parent) : QObject(parent) {
    cameraManager = this;

    auto settings  = ApplicationSettings::instance();
    auto imageSize = camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB);

    // Pre-allocate memory for image
    image = std::shared_ptr<unsigned char[]>(new unsigned char[imageSize]);

    camera.setFormat(raspicam::RASPICAM_FORMAT_BGR);
    camera.setUserCallback(imageGrabbed, image.get());
    camera.setFrameRate(settings->getFps());
}

void CameraManager::start() {
    if (camera.open()) {
        SPDLOG_INFO("Camera opened");
        // Wait for camera to warm up
        QTimer::singleShot(3000, this, SLOT(startCapture()));
    } else {
        SPDLOG_CRITICAL(QString("Failed to open the camera!").toStdString());
    }
}

void CameraManager::grabbed(void*) {
    camera.retrieve(image.get());

    // Construct PiImage for image processing and sending
    PiImage piImage;
    int width    = static_cast<int>(camera.getWidth());
    int height   = static_cast<int>(camera.getHeight());
    piImage.size = QSize(width, height);
    piImage.data = image;

    ImageProcess imageProcess;
    imageProcess.writeRowId(piImage);

    SPDLOG_INFO("Image ready to be sent");
    emit sendImageEvent(piImage);
}

void CameraManager::startCapture() {
    camera.startCapture();
}

CameraManager::~CameraManager() {
}
