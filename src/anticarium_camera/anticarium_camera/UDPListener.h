#pragma once
#include <QUdpSocket>
#include <anticarium_camera/Client.hpp>

class UDPListener : public QObject {
    Q_OBJECT
  public:
    UDPListener(Client& udpClient, QObject* parent = nullptr);
    virtual ~UDPListener();


  signals:
    void heartbeatEvent();

  private slots:
    // Client requests data
    void onHeartbeat();

  private:
    QUdpSocket* udpSocket = nullptr;

    static const QString HEARTBEAT_MESSAGE;

    Client& udpClient;
};
