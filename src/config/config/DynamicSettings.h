#pragma once
#include <QSettings>
#include <config/PIDValues.h>

class DynamicSettings : public QObject {
    Q_OBJECT
  public:
    DynamicSettings()        = delete;
    DynamicSettings& operator=(const DynamicSettings&) = delete;
    static DynamicSettings* instance(const QString& directoryPath, QObject* parent = nullptr);
    static DynamicSettings* instance();
    ~DynamicSettings();

    const PIDValues& getTemperaturePID() const;
    const PIDValues& getMoisturePID() const;

    void setTemperaturePID(const PIDValues& pid);
    void setMoisturePID(const PIDValues& pid);

  private:
    static DynamicSettings* dynamicSettings;
    DynamicSettings(const QString& directoryPath, QObject* parent = nullptr);

    QSettings* settings = nullptr;

    // PID values
    PIDValues temperaturePID;
    PIDValues moisturePID;

    enum class PIDType { Temperature, Moisture };

    void savePID(const PIDValues& pid, PIDType pidType);
};
