#include "TestsUtility.h"
#include <QFile>

nlohmann::json getJsonFromPath(const QString& path) {
    QFile jsonFile(path);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        return nlohmann::json();
    }

    std::string jsonString = jsonFile.readAll().toStdString();
    return nlohmann::json::parse(jsonString);
}
