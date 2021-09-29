#include <QTemporaryDir>
#include <TestDataDirectory.h>
#include <anticarium_pi/config/ApplicationSettings.h>
#include <gtest/gtest.h>

TEST(TestApplicationSettings, TestRead) {
    QObject parent; // so static singleton gets deleted and does not outlive to next test
    QString filePath = TEST_DATA_DIR;
    filePath.append("/json_files");
    ApplicationSettings* applicationSettings = ApplicationSettings::instance(filePath, &parent);
    shared_types::Control savedControl       = applicationSettings->getControl();
    ASSERT_EQ(savedControl.getTemperature(), 32.4f);
    ASSERT_EQ(savedControl.getWindPercentage(), 12);
    ASSERT_EQ(savedControl.getMoisturePercentage(), 76);
}

TEST(TestApplicationSettings, TestSave) {
    QObject parent;

    const float TEMPERATURE    = 56.2f;
    const bool IS_RAINING      = true;
    const int LIGHT_PERCENTAGE = 100;

    shared_types::Control control;
    control.setTemperature(TEMPERATURE);
    control.setIsRaining(IS_RAINING);
    control.setLightPercentage(LIGHT_PERCENTAGE);

    QTemporaryDir tmpDir("/tmp/");
    ApplicationSettings* applicationSettings = ApplicationSettings::instance(tmpDir.path(), &parent);

    applicationSettings->saveControl(control);
    applicationSettings->readControl();

    QFile settingsFile(tmpDir.path().append("/ControlSettings.json"));
    ASSERT_EQ(settingsFile.open(QIODevice::ReadOnly), true);
    settingsFile.close();

    shared_types::Control savedControl = applicationSettings->getControl();
    ASSERT_EQ(savedControl.getTemperature(), TEMPERATURE);
    ASSERT_EQ(savedControl.isRaining(), IS_RAINING);
    ASSERT_EQ(savedControl.getLightPercentage(), LIGHT_PERCENTAGE);
}
