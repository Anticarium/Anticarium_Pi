#include <QNetworkDatagram>
#include <anticarium_camera/UDPListener.h>
#include <config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

const QString UDPListener::HEARTBEAT_MESSAGE = "client_ready";

UDPListener::UDPListener(Client& udpClientInfo, QObject* parent) : QObject(parent), udpClientInfo(udpClientInfo) {
    auto settings = ApplicationSettings::instance();

    udpSocket = new QUdpSocket(this);

    QHostAddress anyIp(QHostAddress::AnyIPv4);
    quint16 udpPort = static_cast<quint16>(settings->getAnticariumUDPPort());
    udpSocket->bind(anyIp, udpPort);

    connect(udpSocket, &QUdpSocket::readyRead, this, &UDPListener::onHeartbeat);
}

void UDPListener::onHeartbeat() {
    // Check if correct heartbeat message
    QNetworkDatagram datagram = udpSocket->receiveDatagram();
    QString payload           = datagram.data();
    if (payload != HEARTBEAT_MESSAGE) {
        SPDLOG_WARN("Invalid heartbeat message!");
        return;
    }

    auto clientAddress = datagram.senderAddress();
    auto clientPort    = static_cast<quint16>(datagram.senderPort());

    if (udpClientInfo.getPort() != clientPort) {
        udpClientInfo.setPort(clientPort);
    }

    if (udpClientInfo.getHostAddress() != clientAddress) {
        udpClientInfo.setHostAddress(clientAddress);
        SPDLOG_INFO(QString("UDP connection established with client %1").arg(clientAddress.toString()).toStdString());
    }

    emit heartbeatEvent();
}

UDPListener::~UDPListener() {
}
