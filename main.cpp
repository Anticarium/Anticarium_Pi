#include <QCoreApplication>
#include <QDebug>
//#include "src/TestClass.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Hello, User!";
//    TestClass testClass;
    return a.exec();
}
