#include <QNetworkDatagram>
#include <anticarium_camera/AnticariumStream.h>
#include <spdlog/spdlog.h>

AnticariumStream::AnticariumStream(QObject* parent) : QObject(parent) {
    captureTimer = new QTimer(this);
    captureTimer->setInterval(500);
    connect(captureTimer, &QTimer::timeout, this, &AnticariumStream::grab);

    udpSocket = new QUdpSocket(this);
}

void AnticariumStream::run() {
    if (camera.open()) {
        SPDLOG_INFO(QString("Camera opened").toStdString());

        // Wait for camera to warm up
        QTimer::singleShot(3000, captureTimer, SLOT(start()));
    } else {
        SPDLOG_CRITICAL(QString("Failed to open the camera!").toStdString());
    }


    udpSocket->connectToHost(QHostAddress("192.168.1.101"), 62933);
}

AnticariumStream::~AnticariumStream() {
}

void AnticariumStream::grab() {
    camera.grab();

    const auto imageSize = camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB);

    // Image data pointer
    auto image = std::make_unique<unsigned char[]>(imageSize);

    // Get image into allocated memory
    camera.retrieve(image.get(), raspicam::RASPICAM_FORMAT_IGNORE);

    static int counter = 0;
    counter++;
    QNetworkDatagram datagram(QByteArray(QString("some data %1").arg(counter).toUtf8()));
    udpSocket->writeDatagram(datagram);
}
