#include <TestDataDirectory.h>
#include <anticarium_pi/config/ApplicationSettings.h>
#include <gtest/gtest.h>

TEST(TestApplicationSettings, TestRead) {
    QObject parent;

    QString testSettingsPath(TEST_DATA_DIR);
    testSettingsPath.append("/config/TestSettings.ini");
    ApplicationSettings* applicationSettings = ApplicationSettings::instance(testSettingsPath, &parent);

    EXPECT_EQ(applicationSettings->getAnticariumUrl(), "http://127.0.0.1:5000");
    EXPECT_EQ(applicationSettings->getSensorDataSendTimeout(), 10);
    EXPECT_EQ(applicationSettings->getControlDataFetchTimeout(), 20);
    EXPECT_EQ(applicationSettings->getPIDSampleTimeout(), 30);
    EXPECT_EQ(applicationSettings->getI2CFetchTimeout(), 40);
}
