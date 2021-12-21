#include <QCoreApplication>
#include <QNetworkDatagram>
#include <anticarium_camera/UDPSender.h>
#include <spdlog/spdlog.h>

UDPSender::UDPSender(const Client& udpClient, QObject* parent) : QObject(parent), udpClient(udpClient) {
    udpSocket = new QUdpSocket(this);
}

void UDPSender::onSendImage(const RawPiImage& piImage) {
    // Send image row by row
    const auto length = piImage.size.width() * 3;
    for (int i = 0; i < piImage.size.height(); i++) {
        auto data = piImage.data + length * i;

        auto row = QByteArray(reinterpret_cast<char*>(data), length);

        udpSocket->writeDatagram(row, udpClient.getHostAddress(), udpClient.getPort());
    }

    QCoreApplication::processEvents();

    SPDLOG_INFO("Image sent using UDP");
}

UDPSender::~UDPSender() {
}
