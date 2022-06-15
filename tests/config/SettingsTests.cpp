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
        dynamicSettings->setP(0.123456789);
        dynamicSettings->setI(0.94129049012);
        dynamicSettings->setD(0.2328742142);
    }

    QObject p;
    auto dynamicSettings = DynamicSettings::instance(file.fileName(), &p);

    EXPECT_EQ(0.123456789, dynamicSettings->getP());
    EXPECT_EQ(0.94129049012, dynamicSettings->getI());
    EXPECT_EQ(0.2328742142, dynamicSettings->getD());
}
