#ifndef __GUNEODROS_LOGGER_HPP__
#define __GUNEODROS_LOGGER_HPP__

#include <chrono>
#include <ctime>

class Logger {
    public:
        static void logError(const std::string& error) {
#ifndef DEBUG
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);
            auto time = strtok(std::ctime(&in_time_t), "\n");
            std::cout << time << " - [ERROR] " << error << std::endl;
#endif
        };
        static void logWarning(const std::string& warning) {
#ifndef DEBUG
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);
            auto time = strtok(std::ctime(&in_time_t), "\n");
            std::cout << time << " - [WARNING] " << warning << std::endl;
#endif
        };
        static void logInfo(const std::string& info) {
#ifndef DEBUG
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);
            auto time = strtok(std::ctime(&in_time_t), "\n");
            std::cout << time << " - [INFO] " << info << std::endl;
#endif
        };
};

#endif // __GUNEODROS_LOGGER_HPP__
