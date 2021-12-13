#include <QCoreApplication>
#include <anticarium_camera/AnticariumStream.h>
#include <config/ApplicationSettings.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

static void initializeLogger() {
    QString qStringPath    = QString("%1/%2").arg(QCoreApplication::applicationDirPath(), "logs/AnticariumCaneraLog.log");
    std::string loggerPath = qStringPath.toStdString();

    std::shared_ptr<spdlog::sinks::daily_file_sink_st> dailyLogger = std::make_shared<spdlog::sinks::daily_file_sink_st>(loggerPath, 0, 0, false, 10);
    std::shared_ptr<spdlog::sinks::stdout_sink_st> consoleLogger   = std::make_shared<spdlog::sinks::stdout_sink_st>();

    std::vector<spdlog::sink_ptr> loggerSinks;

    loggerSinks.push_back(dailyLogger);
    loggerSinks.push_back(consoleLogger);
    std::shared_ptr<spdlog::logger> combined_logger = std::make_shared<spdlog::logger>("logger", begin(loggerSinks), end(loggerSinks));

    spdlog::register_logger(combined_logger);
    spdlog::set_default_logger(combined_logger);
    spdlog::set_pattern("%l | %D %T | %s %# | %v");
    spdlog::flush_on(spdlog::level::trace);
}

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    initializeLogger();

    SPDLOG_INFO("Program started");

    ApplicationSettings::instance(QCoreApplication::applicationDirPath() + "/settings.ini", QCoreApplication::instance());

    AnticariumStream anticariumStream;
    anticariumStream.run();

    int exit = a.exec();

    SPDLOG_INFO(QString("Program exited with exit code: %1 \n\n").arg(exit).toStdString());

    return exit;
}
