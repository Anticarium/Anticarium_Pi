#include <anticarium_camera/UDPSwitch.h>
#include <config/ApplicationSettings.h>

UDPSwitch::UDPSwitch(const Client& udpClientInfo, QObject* parent) : QObject(parent), udpClientInfo(udpClientInfo) {
    auto settings = ApplicationSettings::instance();

    int maxThreads = settings->getUDPThreadsAmount();

    // Create thread and sender pairs
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

    auto settings = ApplicationSettings::instance();

    // Calculate rows per thread
    int maxThreads      = settings->getUDPThreadsAmount();
    int remainderHeight = piImage.size.height() % maxThreads;
    int heightPart      = (piImage.size.height() - remainderHeight) / maxThreads;

    int rowWidth = piImage.size.width();

    unsigned int iterations = udpSenderThreadPairsList.size();
    for (unsigned int i = 0; i < iterations; i++) {
        auto sender = udpSenderThreadPairsList.at(i).second;

        RawPiImage imagePart;
        imagePart.size.setWidth(piImage.size.width());

        // Set standard row amount to send for all threads except for last thread, that
        // might have less rows to send
        if (i + 1 != iterations) {
            imagePart.size.setHeight(heightPart);
        } else {
            if (remainderHeight == 0) {
                imagePart.size.setHeight(heightPart);
            } else {
                imagePart.size.setHeight(heightPart - remainderHeight + (remainderHeight * maxThreads));
            }
        }

        // Calculate pointer position
        imagePart.data = piImage.data.lock().get() + rowWidth * 3 * (heightPart * i);

        QMetaObject::invokeMethod(sender, "onSendImage", Qt::QueuedConnection, Q_ARG(RawPiImage, imagePart));
    }
}
