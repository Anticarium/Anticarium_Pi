#pragma once
#include <QObject>
#include <memory>
#include <pid/PID.h>

class WeatherEmulator : public QObject {
    Q_OBJECT
  public:
    WeatherEmulator(QObject* parent = nullptr);

    /*
     * Sets target temperature for temperature PID
     */
    void setTargetTemperature(float targetTemperature);

    /*
     * Sets target moisture for moisture PID
     */
    void setTargetMoisture(int targetMoisture);

    /*
     * Returns true if PID calculated to heat
     */
    bool calculateHeatToggle(float currentTempearture);

    /*
     * Returns true if PID calculated to water
     */
    bool calculateMoistureToggle(int currentMoisture);

    void setHeat(bool heat);
    void setWater(bool water);
    float getCurrentTemperature();
    int getCurrentMoisture();
    virtual ~WeatherEmulator();

  private:
    float currentTemperature = 0.0f;
    int currentMoisture      = 0;

    bool heat  = false;
    bool water = false;
    std::unique_ptr<PIDController<float>> temperaturePid;
    std::unique_ptr<PIDController<int>> moisturePid;
};
