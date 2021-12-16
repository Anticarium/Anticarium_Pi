#pragma once
#include <QUdpSocket>
#include <anticarium_camera/Client.hpp>
#include <anticarium_camera/PiImage.hpp>

class UDPSender : public QObject {
    Q_OBJECT
  public:
    UDPSender(const Client& udpClient, QObject* parent = nullptr);
    virtual ~UDPSender();

  public slots:
    void onSendImage(const PiImage& piImage);

  private:
    QUdpSocket* udpSocket = nullptr;

    const Client& udpClient;
};
