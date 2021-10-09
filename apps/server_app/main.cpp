#include <QCoreApplication>
#include <anticarium_pi/AnticariumManager.h>
#include <anticarium_pi/config/ApplicationSettings.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>

#include <spdlog/spdlog.h>

int main(int argc, char* argv[]) {
    std::shared_ptr<spdlog::sinks::rotating_file_sink_st> rotatingLogger = std::make_shared<spdlog::sinks::rotating_file_sink_st>("logs/mylogfile", 1048576 * 5, 3);
    std::shared_ptr<spdlog::sinks::daily_file_sink_st> dailyLogger       = std::make_shared<spdlog::sinks::daily_file_sink_st>("logs/mylogfile", 0, 0, false, 10);
    std::shared_ptr<spdlog::sinks::stdout_sink_st> consoleLogger         = std::make_shared<spdlog::sinks::stdout_sink_st>();

    std::vector<spdlog::sink_ptr> loggerSinks;

    loggerSinks.push_back(rotatingLogger);
    loggerSinks.push_back(dailyLogger);
    loggerSinks.push_back(consoleLogger);
    std::shared_ptr<spdlog::logger> combined_logger = std::make_shared<spdlog::logger>("logger", begin(loggerSinks), end(loggerSinks));

    spdlog::register_logger(combined_logger);
    spdlog::set_default_logger(combined_logger);

    spdlog::info("Hello, World!");

    QCoreApplication a(argc, argv);
    ApplicationSettings::instance(QCoreApplication::applicationDirPath(), QCoreApplication::instance());
    AnticariumManager anticariumManager;
    anticariumManager.run();
    return a.exec();
}
