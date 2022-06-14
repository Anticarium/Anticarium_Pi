#pragma once
#include <QSettings>

class DynamicSettings : public QObject {
    Q_OBJECT
  public:
    DynamicSettings()        = delete;
    DynamicSettings& operator=(const DynamicSettings&) = delete;
    static DynamicSettings* instance(const QString& directoryPath, QObject* parent = nullptr);
    static DynamicSettings* instance();
    ~DynamicSettings();

    double getP() const;
    void setP(double p);

    double getI() const;
    void setI(double i);

    double getD() const;
    void setD(double d);

  private:
    static DynamicSettings* dynamicSettings;
    DynamicSettings(const QString& directoryPath, QObject* parent = nullptr);

    QSettings* settings = nullptr;

    // PID values
    double p = 0;
    double i = 0;
    double d = 0;
};
