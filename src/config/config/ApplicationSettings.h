#pragma once
#include <QSettings>

class ApplicationSettings : public QObject {
    Q_OBJECT
  public:
    ApplicationSettings() = delete;
    void operator=(const ApplicationSettings&) = delete;
    static ApplicationSettings* instance(const QString& directoryPath, QObject* parent = nullptr);
    static ApplicationSettings* instance();
    virtual ~ApplicationSettings();

    QString getAnticariumUrl() const;
    int getSensorDataSendTimeout() const;
    int getControlDataFetchTimeout() const;
    int getPIDSampleTimeout() const;
    int getI2CFetchTimeout() const;

  private:
    static ApplicationSettings* applicationSettings;
    ApplicationSettings(const QString& directoryPath, QObject* parent = nullptr);

    QSettings* settings = nullptr;

    QString anticariumUrl;
    int sensorDataSendTimeout   = 0;
    int controlDataFetchTimeout = 0;
    int pidSampleTimeout        = 0;
    int i2cFetchTimeout         = 0;
};
