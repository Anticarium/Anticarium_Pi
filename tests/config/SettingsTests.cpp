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
        temperaturePID.setP(0.123456789);
        temperaturePID.setI(0.94129049012);
        temperaturePID.setD(0.2328742142);
        dynamicSettings->setTemperaturePID(temperaturePID);

        auto moisturePID = dynamicSettings->getTemperaturePID();
        moisturePID.setP(0.24710274972);
        moisturePID.setI(0.6093496344976);
        moisturePID.setD(0.9375097557957);
        dynamicSettings->setMoisturePID(moisturePID);
    }

    QObject p;
    const auto dynamicSettings = DynamicSettings::instance(file.fileName(), &p);

    const auto& temperaturePID = dynamicSettings->getTemperaturePID();
    EXPECT_EQ(temperaturePID.getP(), 0.123456789);
    EXPECT_EQ(temperaturePID.getI(), 0.94129049012);
    EXPECT_EQ(temperaturePID.getD(), 0.2328742142);

    const auto& moisturePID = dynamicSettings->getMoisturePID();
    EXPECT_EQ(moisturePID.getP(), 0.24710274972);
    EXPECT_EQ(moisturePID.getI(), 0.6093496344976);
    EXPECT_EQ(moisturePID.getD(), 0.9375097557957);
}
