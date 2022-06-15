#include <QTemporaryFile>
#include <TestDataDirectory.h>
#include <config/ApplicationSettings.h>
#include <config/DynamicSettings.h>
#include <gtest/gtest.h>

TEST(TestApplicationSettings, TestRead) {
    QObject p;

    QString testSettingsPath(TEST_DATA_DIR);
    testSettingsPath.append("/config/TestSettings.ini");
    ApplicationSettings* applicationSettings = ApplicationSettings::instance(testSettingsPath, &p);

    EXPECT_EQ(applicationSettings->getAnticariumUrl(), "http://127.0.0.1:5000");
    EXPECT_EQ(applicationSettings->getAnticariumUDPPort(), 9999);
    EXPECT_EQ(applicationSettings->getSensorDataSendTimeout(), 10);
    EXPECT_EQ(applicationSettings->getControlDataFetchTimeout(), 20);
    EXPECT_EQ(applicationSettings->getPIDSampleTimeout(), 30);
    EXPECT_EQ(applicationSettings->getI2CFetchTimeout(), 40);
    EXPECT_EQ(applicationSettings->getFps(), 10);
    EXPECT_EQ(applicationSettings->getLogLevel(), 2);
    EXPECT_EQ(applicationSettings->getUDPThreadsAmount(), 1);
}

TEST(TestApplicationSettings, TestWrite) {
    QTemporaryFile file;
    file.open();

    {
        QObject p;
        auto dynamicSettings = DynamicSettings::instance(file.fileName(), &p);

        auto temperaturePID = dynamicSettings->getTemperaturePID();
        temperaturePID.setP(2);
        temperaturePID.setI(10000);
        temperaturePID.setD(0);
        dynamicSettings->setTemperaturePID(temperaturePID);

        auto moisturePID = dynamicSettings->getTemperaturePID();
        moisturePID.setP(4242);
        moisturePID.setI(1245);
        moisturePID.setD(23);
        dynamicSettings->setMoisturePID(moisturePID);
    }

    QObject p;
    const auto dynamicSettings = DynamicSettings::instance(file.fileName(), &p);

    const auto& temperaturePID = dynamicSettings->getTemperaturePID();
    EXPECT_EQ(temperaturePID.getP(), 2);
    EXPECT_EQ(temperaturePID.getI(), 10000);
    EXPECT_EQ(temperaturePID.getD(), 0);

    const auto& moisturePID = dynamicSettings->getMoisturePID();
    EXPECT_EQ(moisturePID.getP(), 4242);
    EXPECT_EQ(moisturePID.getI(), 1245);
    EXPECT_EQ(moisturePID.getD(), 23);
}
