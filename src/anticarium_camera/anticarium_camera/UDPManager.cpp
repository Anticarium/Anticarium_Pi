#include <QNetworkDatagram>
#include <anticarium_camera/UDPManager.h>
#include <spdlog/spdlog.h>

UDPManager::UDPManager(QObject* parent) : QObject(parent) {
    udpSocket = new QUdpSocket(this);
    udpSocket->connectToHost(QHostAddress("192.168.1.101"), 62933);
}

void UDPManager::onSendImage(const PiImage& piImage) {
    // return if no image
    if (piImage.data.expired()) {
        return;
    }

    // Send image row by row
    const auto length = piImage.size.width();
    for (int i = 0; i < piImage.size.height(); i++) {
        auto data = piImage.data.lock().get() + length * i;

        auto row = QByteArray(reinterpret_cast<char*>(data), length);

        udpSocket->writeDatagram(row);
    }

    SPDLOG_INFO("Image sent using UDP");
    emit dataSentEvent();
}


UDPManager::~UDPManager() {
}
