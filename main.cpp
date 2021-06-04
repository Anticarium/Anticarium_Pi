#include <QCoreApplication>
#include <QDebug>
//#include <wiringPi.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Hello, User!";
    return a.exec();
}
