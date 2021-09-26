#include <QCoreApplication>
#include <QDebug>
#include <shared_types/Control.h>
int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);
    qDebug() << "Hello, User!";
    return a.exec();
}
