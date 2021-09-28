#pragma once
#include <QObject>
#include <shared_types/Control.h>

class ApplicationSettings : public QObject {
    Q_OBJECT
  public:
    ApplicationSettings() = delete;
    void operator=(const ApplicationSettings&) = delete;
    static ApplicationSettings* instance(const QString& directoryPath, QObject* parent);
    static ApplicationSettings* instance();
    virtual ~ApplicationSettings();

    shared_types::Control getControl();
    void saveControl(const shared_types::Control& control);

  private:
    static ApplicationSettings* applicationSettings;
    ApplicationSettings(const QString& directoryPath, QObject* parent = nullptr);

    shared_types::Control control;

    /*
     * Reads shared_types::Control saved in json file and writes it to control variable
     */
    void readControl();
    QString directoryPath;

    const QString CONTROL_FILE = "Control.json";
};
