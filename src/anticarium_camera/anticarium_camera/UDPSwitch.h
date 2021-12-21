#pragma once

#include <QPair>
#include <QThread>
#include <anticarium_camera/UDPSender.h>

class UDPSwitch : public QObject {
    Q_OBJECT
  public:
    UDPSwitch(const Client& udpClientInfo, QObject* parent = nullptr);
    virtual ~UDPSwitch();
    void start();

  public slots:
    void onSendImage(const PiImage& piImage);

  private:
    std::vector<QPair<QThread*, UDPSender*>> udpSenderThreadPairsList;
    const Client& udpClientInfo;
};
