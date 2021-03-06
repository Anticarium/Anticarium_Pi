#include <QCoreApplication>
#include <anticarium_camera/StreamManager.h>
#include <config/ApplicationSettings.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

static void exceptionHandler() {
    try {
        std::rethrow_exception(std::current_exception());
    } catch (const std::exception& e) {
        SPDLOG_CRITICAL(e.what());
    } catch (...) {
        SPDLOG_CRITICAL("Unhandled exception occurred!");
    }

    // Exception can occur anywhere, so it is unsafe to try to terminate qt application
    exit(-1);
}

static void initializeLogger() {
    auto settings = ApplicationSettings::instance();

    auto loggerPath = QString("%1/%2").arg(QCoreApplication::applicationDirPath(), "logs/AnticariumCameraLog.log").toStdString();

    auto dailySink    = std::make_shared<spdlog::sinks::daily_file_sink_mt>(loggerPath, 0, 0, false, 10);
    auto rotatingSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(dailySink->filename(), 1048576 * 1, 20);
    auto consoleSink  = std::make_shared<spdlog::sinks::stdout_sink_mt>();

    std::vector<spdlog::sink_ptr> loggerSinks;

    loggerSinks.push_back(dailySink);
    loggerSinks.push_back(rotatingSink);
    loggerSinks.push_back(consoleSink);
    auto combinedLogger = std::make_shared<spdlog::logger>("logger", begin(loggerSinks), end(loggerSinks));

    spdlog::register_logger(combinedLogger);
    spdlog::set_default_logger(combinedLogger);
    spdlog::set_pattern("%5l | %D %T | %-25s %-4# | %v");
    spdlog::flush_on(spdlog::level::trace);
    spdlog::set_level(settings->getLogLevel());
}

int main(int argc, char* argv[]) {
    std::set_terminate(exceptionHandler);

    qRegisterMetaType<PiImage>("PiImage");
    qRegisterMetaType<RawPiImage>("RawPiImage");

    QCoreApplication a(argc, argv);

    ApplicationSettings::instance(QCoreApplication::applicationDirPath() + "/settings.ini", QCoreApplication::instance());

    initializeLogger();

    SPDLOG_INFO("Program started");

    StreamManager streamManager;
    streamManager.run();

    int exit = a.exec();

    SPDLOG_INFO(QString("Program exited with exit code: %1 \n\n").arg(exit).toStdString());

    return exit;
}
