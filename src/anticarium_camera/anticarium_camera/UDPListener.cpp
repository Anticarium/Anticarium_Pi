#include <QNetworkDatagram>
#include <anticarium_camera/UDPListener.h>
#include <config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

const QString UDPListener::HEARTBEAT_MESSAGE = "client_ready";

UDPListener::UDPListener(Client& udpClientInfo, QObject* parent) : QObject(parent), udpClientInfo(udpClientInfo) {
    const auto& settings = *ApplicationSettings::instance();

    udpSocket = new QUdpSocket(this);

    const QHostAddress anyIp(QHostAddress::AnyIPv4);
    const auto udpPort = static_cast<quint16>(settings.getAnticariumUDPPort());

    // We also bind to same port at UDPSender, that is why we need to use ShareAddress
    udpSocket->bind(anyIp, udpPort, QAbstractSocket::ShareAddress);

    connect(udpSocket, &QUdpSocket::readyRead, this, &UDPListener::onHeartbeat);
}

void UDPListener::onHeartbeat() {
    // Check if correct heartbeat message
    const auto datagram = udpSocket->receiveDatagram();
    const auto payload  = datagram.data();
    if (payload != HEARTBEAT_MESSAGE) {
        SPDLOG_WARN("Invalid heartbeat message!");
        return;
    }

    const auto clientAddress = datagram.senderAddress();
    const auto clientPort    = static_cast<quint16>(datagram.senderPort());

    if (udpClientInfo.getPort() != clientPort) {
        udpClientInfo.setPort(clientPort);
    }

    if (udpClientInfo.getHostAddress() != clientAddress) {
        udpClientInfo.setHostAddress(clientAddress);
        SPDLOG_INFO(QString("UDP connection established with client %1 port %2").arg(clientAddress.toString()).arg(clientPort).toStdString());
    }

    emit heartbeatEvent();
}
