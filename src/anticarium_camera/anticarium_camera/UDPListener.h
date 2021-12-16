#pragma once
#include <QUdpSocket>
#include <anticarium_camera/Client.hpp>

class UDPListener : public QObject {
    Q_OBJECT
  public:
    UDPListener(Client& udpClient, QObject* parent = nullptr);
    virtual ~UDPListener();

  private slots:
    // Check if there is handshake attempt
    void checkForHandshake();

  private:
    QUdpSocket* udpSocket = nullptr;

    static const QString HANDSHAKE_MESSAGE;

    Client& udpClient;
};
