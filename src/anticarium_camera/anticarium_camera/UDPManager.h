#pragma once
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

  private:
    QUdpSocket* udpSocket;
};
