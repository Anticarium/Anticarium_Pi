#include <QCoreApplication>
#include <anticarium_pi/AnticariumManager.h>
#include <anticarium_pi/Jttp.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

int main(int argc, char* argv[]) {
    std::shared_ptr<spdlog::sinks::daily_file_sink_st> dailyLogger = std::make_shared<spdlog::sinks::daily_file_sink_st>("logs/AnticariumLog", 0, 0, false, 10);
    std::shared_ptr<spdlog::sinks::stdout_sink_st> consoleLogger = std::make_shared<spdlog::sinks::stdout_sink_st>();

    std::vector<spdlog::sink_ptr> loggerSinks;

    loggerSinks.push_back(dailyLogger);
    loggerSinks.push_back(consoleLogger);
    std::shared_ptr<spdlog::logger> combined_logger = std::make_shared<spdlog::logger>("logger", begin(loggerSinks), end(loggerSinks));

    spdlog::register_logger(combined_logger);
    spdlog::set_default_logger(combined_logger);
    spdlog::set_pattern("%l | %D %T | %s %# | %v");
    spdlog::flush_on(spdlog::level::trace);

    SPDLOG_INFO("Program started");

    QCoreApplication a(argc, argv);
    JTTP::instance(QCoreApplication::instance());
    AnticariumManager anticariumManager;
    anticariumManager.run();

    int exit = a.exec();

    SPDLOG_INFO(QString("Program exited with exit code: %1 \n\n").arg(exit).toStdString());

    return exit;
}
