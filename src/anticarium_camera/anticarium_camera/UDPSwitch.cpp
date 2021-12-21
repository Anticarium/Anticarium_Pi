#include <anticarium_camera/UDPSwitch.h>
#include <config/ApplicationSettings.h>

UDPSwitch::UDPSwitch(const Client& udpClientInfo, QObject* parent) : QObject(parent), udpClientInfo(udpClientInfo) {
    auto settings = ApplicationSettings::instance();

    int maxThreads = settings->getUDPThreadsAmount();

    for (int i = 0; i < maxThreads; i++) {
        QThread* thread   = new QThread(this);
        UDPSender* sender = new UDPSender(udpClientInfo);

        sender->moveToThread(thread);

        QPair<QThread*, UDPSender*> pair;
        pair.first  = thread;
        pair.second = sender;

        udpSenderThreadPairsList.push_back(pair);
    }
}

void UDPSwitch::start() {
    for (auto i : udpSenderThreadPairsList) {
        i.first->start();
    }
}

UDPSwitch::~UDPSwitch() {
    for (auto i : udpSenderThreadPairsList) {
        i.first->quit();
        i.first->wait();
    }
}

void UDPSwitch::onSendImage(const PiImage& piImage) {
    // return if no image
    if (piImage.data.expired()) {
        return;
    }

    auto settings  = ApplicationSettings::instance();
    int maxThreads = settings->getUDPThreadsAmount();

    int remainderHeight = piImage.size.height() % maxThreads;
    int heightPart      = (piImage.size.height() - remainderHeight) / maxThreads;

    int rowWidth = piImage.size.width();

    unsigned int iterations = udpSenderThreadPairsList.size();

    for (unsigned int i = 0; i < iterations; i++) {
        auto sender = udpSenderThreadPairsList.at(i).second;

        RawPiImage imagePart;
        imagePart.size.setWidth(piImage.size.width());

        if (i + 1 != iterations) {
            imagePart.size.setHeight(heightPart);
        } else {
            if (remainderHeight == 0) {
                imagePart.size.setHeight(heightPart);
            } else {
                imagePart.size.setHeight(remainderHeight);
            }
        }

        imagePart.data = piImage.data.lock().get() + rowWidth * 3 * (heightPart * i);

        QMetaObject::invokeMethod(sender, "onSendImage", Qt::QueuedConnection, Q_ARG(RawPiImage, imagePart));
    }
}
