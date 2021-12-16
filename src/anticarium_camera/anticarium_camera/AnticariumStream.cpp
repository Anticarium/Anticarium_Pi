#include <anticarium_camera/AnticariumStream.h>
#include <spdlog/spdlog.h>

AnticariumStream::AnticariumStream(QObject* parent) : QObject(parent) {
    udpListener     = new UDPListener(udpClient, this);
    udpSender       = new UDPSender(udpClient);
    udpSenderThread = new QThread(this);
    cameraManager   = new CameraManager();
    cameraThread    = new QThread(this);

    udpSender->moveToThread(udpSenderThread);
    cameraManager->moveToThread(cameraThread);

    connect(cameraManager, &CameraManager::sendImageEvent, udpSender, &UDPSender::onSendImage);
    connect(cameraThread, &QThread::started, cameraManager, &CameraManager::start);
}

void AnticariumStream::run() {
    udpSenderThread->start();
    cameraThread->start();
}

AnticariumStream::~AnticariumStream() {
    cameraThread->quit();
    cameraThread->wait();

    udpSenderThread->quit();
    udpSenderThread->wait();
}
