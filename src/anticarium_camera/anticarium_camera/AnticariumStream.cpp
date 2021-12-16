#include <anticarium_camera/AnticariumStream.h>
#include <spdlog/spdlog.h>

AnticariumStream::AnticariumStream(QObject* parent) : QObject(parent) {
    udpManager    = new UDPManager(this);
    cameraThread  = new QThread(this);
    cameraManager = new CameraManager();

    cameraManager->moveToThread(cameraThread);

    connect(cameraManager, &CameraManager::sendImageEvent, this, &AnticariumStream::sendImageEvent);
    connect(this, &AnticariumStream::sendImageEvent, udpManager, &UDPManager::onSendImage);
    connect(cameraThread, &QThread::started, cameraManager, &CameraManager::start);
}

void AnticariumStream::run() {
    cameraThread->start();
    cameraThread->setPriority(QThread::LowestPriority);
}


AnticariumStream::~AnticariumStream() {
    cameraThread->quit();
    cameraThread->wait();
}
