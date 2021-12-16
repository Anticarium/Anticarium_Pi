#include <QNetworkDatagram>
#include <anticarium_camera/UDPListener.h>
#include <config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

const QString UDPListener::HANDSHAKE_MESSAGE = "client_ready";

UDPListener::UDPListener(Client& udpClient, QObject* parent) : QObject(parent), udpClient(udpClient) {
    auto settings = ApplicationSettings::instance();

    udpSocket = new QUdpSocket(this);

    QHostAddress anyIp(QHostAddress::AnyIPv4);
    quint16 udpPort = static_cast<quint16>(settings->getAnticariumUDPPort());
    udpSocket->bind(anyIp, udpPort);

    connect(udpSocket, &QUdpSocket::readyRead, this, &UDPListener::checkForHandshake);
}

void UDPListener::checkForHandshake() {
    // Return if no pending datagrams
    if (!udpSocket->hasPendingDatagrams()) {
        SPDLOG_WARN("No handshake datagram!");
        return;
    }

    // Check if correct handshake message
    QNetworkDatagram datagram = udpSocket->receiveDatagram();
    QString payload           = datagram.data();
    if (payload != HANDSHAKE_MESSAGE) {
        SPDLOG_WARN("Invalid handshake message!");
        return;
    }

    // Save client data
    auto clientAddress = datagram.senderAddress();
    auto clientPort    = static_cast<quint16>(datagram.senderPort());

    udpClient.setHostAddress(clientAddress);
    udpClient.setPort(clientPort);

    SPDLOG_INFO(QString("UDP handshake with client %1").arg(clientAddress.toString()).toStdString());
}

UDPListener::~UDPListener() {
}
