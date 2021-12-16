#pragma once
#include <QHostAddress>
#include <QMutex>

class Client {
  public:
    Client() = default;

    QHostAddress getHostAddress() const {
        return address;
    }

    quint16 getPort() const {
        return port;
    }

    void setHostAddress(const QHostAddress& address) {
        mutex.lock();
        this->address = address;
        mutex.unlock();
    }

    void setPort(quint16 port) {
        mutex.lock();
        this->port = port;
        mutex.unlock();
    }

  private:
    QHostAddress address;
    quint16 port = 0;

    QMutex mutex;
};
