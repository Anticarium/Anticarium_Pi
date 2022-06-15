#include <QTemporaryFile>
#include <anticarium_pi/WeatherEmulator.h>
#include <config/DynamicSettings.h>
#include <gtest/gtest.h>

TEST(TestWeatherEmulator, TestPIDs) {
    QObject p;

    QTemporaryFile file;
    file.open();
    DynamicSettings::instance(file.fileName(), &p);

    WeatherEmulator* weatherEmulator = new WeatherEmulator(&p);
    weatherEmulator->setTargetTemperature(23.4f);
    weatherEmulator->setTargetMoisture(76);

    EXPECT_FALSE(weatherEmulator->calculateMoistureToggle(98));
    EXPECT_FALSE(weatherEmulator->calculateHeatToggle(21.2f));
}

TEST(TestWeatherEmulator, TestPIDGetters) {
    QObject p;

    QTemporaryFile file;
    file.open();
    DynamicSettings::instance(file.fileName(), &p);

    WeatherEmulator* weatherEmulator = new WeatherEmulator(&p);
    weatherEmulator->calculateHeatToggle(20.3f);
    weatherEmulator->calculateMoistureToggle(10);

    EXPECT_EQ(weatherEmulator->getCurrentMoisture(), 10);
    EXPECT_EQ(weatherEmulator->getCurrentTemperatureInt(), static_cast<int>(20.3f * WeatherEmulator::FLOAT_MULTIPLIER));
}
