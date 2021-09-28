#include <QDebug>
#include <QFile>
#include <anticarium_pi/config/ApplicationSettings.h>
#include <shared_types/ControlSerializer.hpp>

ApplicationSettings* ApplicationSettings::applicationSettings = nullptr;

ApplicationSettings::ApplicationSettings(const QString& directoryPath, QObject* parent) : QObject(parent) {
    this->directoryPath = directoryPath;
    readControl();
}

ApplicationSettings* ApplicationSettings::instance(const QString& directoryPath, QObject* parent) {
    if (!applicationSettings) {
        applicationSettings = new ApplicationSettings(directoryPath, parent);
    }
    return applicationSettings;
}

ApplicationSettings* ApplicationSettings::instance() {
    return applicationSettings;
}

shared_types::Control ApplicationSettings::getControl() {
    return control;
}

void ApplicationSettings::readControl() {
    QString filePath = QString("%1/%2").arg(directoryPath).arg(CONTROL_FILE);
    QFile jsonFile(filePath);
    bool fileOpened = jsonFile.open(QIODevice::ReadOnly);
    if (fileOpened) {
        try {
            nlohmann::json json = nlohmann::json::parse(QString(jsonFile.readAll()).toStdString());
            control             = json;
        } catch (nlohmann::json::exception& e) {
            qWarning() << e.what();
        }
    }
    jsonFile.close();
}

void ApplicationSettings::saveControl(const shared_types::Control& control) {
    QString filePath = QString("%1/%2").arg(directoryPath).arg(CONTROL_FILE);
    QFile jsonFile(filePath);
    bool fileOpened = jsonFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
    if (fileOpened) {
        nlohmann::json json;
        try {
            json = control;
            jsonFile.write(QString::fromStdString(json.dump()).toUtf8());
        } catch (nlohmann::json::exception& e) {
            qWarning() << e.what();
        }
    }
    jsonFile.close();
}

ApplicationSettings::~ApplicationSettings() {
}
