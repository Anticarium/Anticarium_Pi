#include <anticarium_pi/WeatherEmulator.h>
#include <gtest/gtest.h>

TEST(TestWeatherEmulator, TestPIDs) {
    WeatherEmulator* weatherEmulator = new WeatherEmulator();
    weatherEmulator->setTargetTemperature(23.4f);
    weatherEmulator->setTargetMoisture(76);

    ASSERT_FALSE(weatherEmulator->calculateMoistureToggle(98));
    ASSERT_TRUE(weatherEmulator->calculateHeatToggle(21.2f));
}
