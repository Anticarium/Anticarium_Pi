#include <QNetworkDatagram>
#include <anticarium_camera/UDPSender.h>
#include <spdlog/spdlog.h>

UDPSender::UDPSender(const Client& udpClient, QObject* parent) : QObject(parent), udpClient(udpClient) {
    udpSocket = new QUdpSocket(this);
}

void UDPSender::onSendImage(const PiImage& piImage) {
    // return if no image
    if (piImage.data.expired()) {
        return;
    }

    // Send image row by row
    const auto length = piImage.size.width() * 3;
    for (int i = 0; i < piImage.size.height(); i++) {
        auto data = piImage.data.lock().get() + length * i;

        auto row = QByteArray(reinterpret_cast<char*>(data), length);

        udpSocket->writeDatagram(row, udpClient.getHostAddress(), udpClient.getPort());
    }

    SPDLOG_INFO("Image sent using UDP");
}


UDPSender::~UDPSender() {
}
