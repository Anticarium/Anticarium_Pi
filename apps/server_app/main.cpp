#include <QCoreApplication>
#include <anticarium_pi/AnticariumManager.h>
#include <anticarium_pi/config/ApplicationSettings.h>

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);
    ApplicationSettings::instance(QCoreApplication::applicationDirPath(), QCoreApplication::instance());
    AnticariumManager anticariumManager;
    anticariumManager.run();
    return a.exec();
}
