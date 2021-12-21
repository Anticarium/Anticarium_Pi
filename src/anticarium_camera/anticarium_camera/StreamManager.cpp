#include <anticarium_camera/StreamManager.h>
#include <config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

StreamManager::StreamManager(QObject* parent) : QObject(parent) {
    udpListener    = new UDPListener(udpClientInfo, this);
    camera         = new Camera();
    cameraThread   = new QThread(this);
    heartbeatTimer = new QTimer(this);
    udpSwitch      = new UDPSwitch(udpClientInfo, this);

    camera->moveToThread(cameraThread);

    heartbeatTimer->setSingleShot(true);
    heartbeatTimer->setInterval(Timeout::HEARTBEAT);

    connect(cameraThread, &QThread::started, camera, &Camera::start);
    connect(udpListener, &UDPListener::heartbeatEvent, this, &StreamManager::onStartAcquisition);
    connect(heartbeatTimer, &QTimer::timeout, this, &StreamManager::onStopAcquisition);
}

void StreamManager::onStartAcquisition() {
    // Start acquisition on new user connection
    if (!heartbeatTimer->isActive()) {
        heartbeatTimer->start();
        connect(camera, &Camera::sendImageEvent, udpSwitch, &UDPSwitch::onSendImage);
    } else {
        // Restart timer on heartbeat of same user
        heartbeatTimer->stop();
        heartbeatTimer->start();
    }
}

void StreamManager::onStopAcquisition() {
    disconnect(camera, &Camera::sendImageEvent, udpSwitch, &UDPSwitch::onSendImage);
}

void StreamManager::run() {
    udpSwitch->start();
    cameraThread->start();
}

StreamManager::~StreamManager() {
    cameraThread->quit();
    cameraThread->wait();
}
