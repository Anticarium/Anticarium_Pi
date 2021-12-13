#include <anticarium_camera/CameraManager.h>
#include <anticarium_camera/ImageProcess.h>
#include <spdlog/spdlog.h>

CameraManager::CameraManager(QObject* parent) : QObject(parent) {
    captureTimer = new QTimer(this);
    captureTimer->setInterval(500);
    connect(captureTimer, &QTimer::timeout, this, &CameraManager::grab);

    auto imageSize = camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB);

    // Pre-allocate memory for images
    for (auto& i : images) {
        i = std::shared_ptr<unsigned char[]>(new unsigned char[imageSize]);
    }
}

void CameraManager::start() {
    if (camera.open()) {
        SPDLOG_INFO("Camera opened");
        // Wait for camera to warm up
        QTimer::singleShot(3000, captureTimer, SLOT(start()));
    } else {
        SPDLOG_CRITICAL(QString("Failed to open the camera!").toStdString());
    }
}

void CameraManager::grab() {
    auto image = images[counter];

    camera.grab();

    // Get image into allocated memory
    camera.retrieve(image.get(), raspicam::RASPICAM_FORMAT_IGNORE);

    PiImage piImage;
    int width    = static_cast<int>(camera.getWidth());
    int height   = static_cast<int>(camera.getHeight());
    piImage.size = QSize(width, height);
    piImage.data = image;

    ImageProcess imageProcess;
    imageProcess.writeRowId(piImage);

    if (canSend) {
        SPDLOG_INFO("Send image to udp");
        emit sendImageEvent(piImage);
    }

    if (++counter == MAX_IMAGES) {
        counter = 0;
    }

    canSend = false;
}

void CameraManager::onNextImage() {
    canSend = true;
}

CameraManager::~CameraManager() {
}
