#include <anticarium_camera/UDPManager.h>
#include <config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

const QString UDPManager::HANDSHAKE_MESSAGE = "client_ready";

UDPManager::UDPManager(QObject* parent) : QObject(parent) {
    auto settings = ApplicationSettings::instance();

    udpSocket = new QUdpSocket(this);

    QHostAddress anyIp(QHostAddress::AnyIPv4);
    quint16 udpPort = static_cast<quint16>(settings->getAnticariumUDPPort());
    udpSocket->bind(anyIp, udpPort);

    connect(udpSocket, &QUdpSocket::readyRead, this, &UDPManager::checkForHandshake);
}

void UDPManager::onSendImage(const PiImage& piImage) {
    // return if no image
    if (piImage.data.expired()) {
        return;
    }

    // Send image row by row
    const auto length = piImage.size.width() * 3;
    for (int i = 0; i < piImage.size.height(); i++) {
        auto data = piImage.data.lock().get() + length * i;

        auto row = QByteArray(reinterpret_cast<char*>(data), length);

        udpSocket->writeDatagram(row, clientAddress, clientPort);
    }

    SPDLOG_INFO("Image sent using UDP");
    emit dataSentEvent();
}

void UDPManager::checkForHandshake() {
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
    clientAddress = datagram.senderAddress();
    clientPort    = static_cast<quint16>(datagram.senderPort());

    SPDLOG_INFO(QString("UDP handshake with client %1").arg(clientAddress.toString()).toStdString());
}

UDPManager::~UDPManager() {
}
