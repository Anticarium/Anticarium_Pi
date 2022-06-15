#include "DynamicSettings.h"

DynamicSettings* DynamicSettings::dynamicSettings = nullptr;

DynamicSettings::DynamicSettings(const QString& directoryPath, QObject* parent) : QObject(parent) {
    settings = new QSettings(directoryPath, QSettings::IniFormat, this);

    temperaturePID.setP(settings->value("TemperatureP", 1).toInt());
    temperaturePID.setI(settings->value("TemperatureI", 1).toInt());
    temperaturePID.setD(settings->value("TemperatureD", 1).toInt());

    moisturePID.setP(settings->value("MoistureP", 1).toInt());
    moisturePID.setI(settings->value("MoistureI", 1).toInt());
    moisturePID.setD(settings->value("MoistureD", 1).toInt());
}

void DynamicSettings::savePID(const PIDValues& pid, PIDType pidType) {
    QString settingName;
    if (pidType == PIDType::Temperature) {
        settingName = "Temperature";
    } else if (pidType == PIDType::Moisture) {
        settingName = "Moisture";
    }

    settings->setValue(settingName + 'P', pid.getP());
    settings->setValue(settingName + 'I', pid.getI());
    settings->setValue(settingName + 'D', pid.getD());
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

void DynamicSettings::setTemperaturePID(const PIDValues& pid) {
    temperaturePID = pid;
    savePID(pid, PIDType::Temperature);
}

void DynamicSettings::setMoisturePID(const PIDValues& pid) {
    moisturePID = pid;
    savePID(pid, PIDType::Moisture);
}

const PIDValues& DynamicSettings::getTemperaturePID() const {
    return temperaturePID;
}

const PIDValues& DynamicSettings::getMoisturePID() const {
    return moisturePID;
}

DynamicSettings::~DynamicSettings() {
    dynamicSettings = nullptr;
}
