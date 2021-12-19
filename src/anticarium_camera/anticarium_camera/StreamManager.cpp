#include <anticarium_camera/StreamManager.h>
#include <spdlog/spdlog.h>

StreamManager::StreamManager(QObject* parent) : QObject(parent) {
    udpListener     = new UDPListener(udpClient, this);
    udpSender       = new UDPSender(udpClient);
    udpSenderThread = new QThread(this);
    camera          = new Camera();
    cameraThread    = new QThread(this);

    udpSender->moveToThread(udpSenderThread);
    camera->moveToThread(cameraThread);

    connect(camera, &Camera::sendImageEvent, udpSender, &UDPSender::onSendImage);
    connect(cameraThread, &QThread::started, camera, &Camera::start);
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
