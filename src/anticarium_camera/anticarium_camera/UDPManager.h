#pragma once
#include <QNetworkDatagram>
#include <QTimer>
#include <QUdpSocket>
#include <anticarium_camera/PiImage.hpp>

class UDPManager : public QObject {
    Q_OBJECT
  public:
    UDPManager(QObject* parent = nullptr);
    virtual ~UDPManager();

  public slots:
    void onSendImage(const PiImage& piImage);

  signals:
    void dataSentEvent();

  private slots:
    // Check if there is handshake attempt
    void checkForHandshake();

  private:
    QUdpSocket* udpSocket = nullptr;

    quint16 clientPort = 0;
    QHostAddress clientAddress;

    static const QString HANDSHAKE_MESSAGE;
};
