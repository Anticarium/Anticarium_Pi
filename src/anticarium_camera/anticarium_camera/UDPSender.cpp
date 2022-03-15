#include <QCoreApplication>
#include <QNetworkDatagram>
#include <anticarium_camera/UDPSender.h>
#include <config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

UDPSender::UDPSender(const Client& udpClientInfo, QObject* parent) : QObject(parent), udpClientInfo(udpClientInfo) {
    udpSocket = new QUdpSocket(this);

    const auto& settings = *ApplicationSettings::instance();
    const auto udpPort   = static_cast<quint16>(settings.getAnticariumUDPPort());

    // We also bind to same port at UDPListener, that is why we need to use ShareAddress
    udpSocket->bind(udpPort, QAbstractSocket::ShareAddress);
}


void UDPSender::onSendImage(const RawPiImage& piImage) const {
    // There are three colors in pixel, red, green, blue
    constexpr int pixelColors = 3;

    // Send image row by row
    const auto length = piImage.size.width() * pixelColors;
    for (int i = 0; i < piImage.size.height(); i++) {
        const auto data = piImage.data + length * i;
        const auto row  = QByteArray(reinterpret_cast<char*>(data), length);

        udpSocket->writeDatagram(row, udpClientInfo.getHostAddress(), udpClientInfo.getPort());
    }

    QCoreApplication::processEvents();

    SPDLOG_INFO("Image sent using UDP");
}
