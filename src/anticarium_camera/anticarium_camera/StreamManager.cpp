#include <anticarium_camera/StreamManager.h>
#include <spdlog/spdlog.h>

StreamManager::StreamManager(QObject* parent) : QObject(parent) {
    udpListener     = new UDPListener(udpClient, this);
    udpSender       = new UDPSender(udpClient);
    udpSenderThread = new QThread(this);
    camera          = new Camera();
    cameraThread    = new QThread(this);
    heartbeatTimer  = new QTimer(this);

    udpSender->moveToThread(udpSenderThread);
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
        connect(camera, &Camera::sendImageEvent, udpSender, &UDPSender::onSendImage);
    } else {
        // Restart timer on heartbeat of same user
        heartbeatTimer->stop();
        heartbeatTimer->start();
    }
}

void StreamManager::onStopAcquisition() {
    disconnect(camera, &Camera::sendImageEvent, udpSender, &UDPSender::onSendImage);
}

void StreamManager::run() {
    udpSenderThread->start();
    cameraThread->start();
}

StreamManager::~StreamManager() {
    cameraThread->quit();
    cameraThread->wait();

    udpSenderThread->quit();
    udpSenderThread->wait();
}
