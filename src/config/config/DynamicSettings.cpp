#include "DynamicSettings.h"

DynamicSettings* DynamicSettings::dynamicSettings = nullptr;

DynamicSettings::DynamicSettings(const QString& directoryPath, QObject* parent) : QObject(parent) {
    settings = new QSettings(directoryPath, QSettings::IniFormat, this);
    p        = settings->value("P", 0).toDouble();
    i        = settings->value("I", 0).toDouble();
    d        = settings->value("D", 0).toDouble();
}

DynamicSettings* DynamicSettings::instance(const QString& directoryPath, QObject* parent) {
    if (dynamicSettings == nullptr) {
        dynamicSettings = new DynamicSettings(directoryPath, parent);
    }
    return instance();
}

DynamicSettings* DynamicSettings::instance() {
    return dynamicSettings;
}

double DynamicSettings::getP() const {
    return p;
}

void DynamicSettings::setP(double p) {
    this->p = p;
    settings->setValue("P", p);
}

double DynamicSettings::getI() const {
    return i;
}

void DynamicSettings::setI(double i) {
    this->i = i;
    settings->setValue("I", i);
}

double DynamicSettings::getD() const {
    return d;
}

void DynamicSettings::setD(double d) {
    this->d = d;
    settings->setValue("D", d);
}

DynamicSettings::~DynamicSettings() {
    dynamicSettings = nullptr;
}
