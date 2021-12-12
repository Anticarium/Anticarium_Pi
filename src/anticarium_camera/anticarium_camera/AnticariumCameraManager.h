#pragma once
#include <QObject>

class AnticariumCameraManager : public QObject {
    Q_OBJECT
  public:
    AnticariumCameraManager(QObject* parent = nullptr);
    void run();
    virtual ~AnticariumCameraManager();
};
