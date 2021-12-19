#include <QNetworkDatagram>
#include <anticarium_camera/UDPListener.h>
#include <config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

const QString UDPListener::HEARTBEAT_MESSAGE = "client_ready";

UDPListener::UDPListener(Client& udpClient, QObject* parent) : QObject(parent), udpClient(udpClient) {
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

    if (udpClient.getPort() != clientPort) {
        udpClient.setPort(clientPort);
    }

    if (udpClient.getHostAddress() != clientAddress) {
        udpClient.setHostAddress(clientAddress);
        SPDLOG_INFO(QString("UDP connection established with client %1").arg(clientAddress.toString()).toStdString());
    }

    emit heartbeatEvent();
}

UDPListener::~UDPListener() {
}
