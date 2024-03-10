#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <iostream>
#include <format>
#include <string>
#include <chrono>
#include <ctime>

#define INFO_PREFIX "[INFO]"
#define WARNING_PREFIX "[WARNING]"
#define ERROR_PREFIX "[ERROR]"

namespace prim
{
    enum class LogLevel { NoLog, Error, Warning, Info };

    class Logger
    {
    private:
        static std::string currentDateTimeString(const char* format = "%d-%m-%Y %H:%M:%S")
        {
            std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::string timeStr(30, '\0');
            std::strftime(&timeStr[0], timeStr.size(), format, std::localtime(&time));
            return timeStr;
        }

        static std::string buildMessagePrefix(const char* messageTypePrefix)
        {
            return std::string(messageTypePrefix) + ' ' + currentDateTimeString() + ": ";
        }

    public:
        LogLevel logLevel = LogLevel::Info;

        static const Logger& inst()
        {
            static Logger defaultInstanceLogger;
            return defaultInstanceLogger;
        }

        template<class... Args>
        void logInfo(std::string messageTemplate, Args&&... args) const noexcept
        {
            if(static_cast<int>(logLevel) < static_cast<int>(LogLevel::Info)) return;

            std::string message = std::vformat(buildMessagePrefix(INFO_PREFIX) + messageTemplate, std::make_format_args(args...));
            std::cout << message << std::endl;
        }

        template<class... Args>
        void logWarning(std::string messageTemplate, Args&&... args) const noexcept
        {
            if(static_cast<int>(logLevel) < static_cast<int>(LogLevel::Warning)) return;

            std::string message = std::vformat(buildMessagePrefix(WARNING_PREFIX) + messageTemplate, std::make_format_args(args...));
            std::cout << message << std::endl;
        }

        template<class... Args>
        void logError(std::string messageTemplate, Args&&... args) const noexcept
        {
            if(static_cast<int>(logLevel) < static_cast<int>(LogLevel::Error)) return;

            std::string message = std::vformat(buildMessagePrefix(ERROR_PREFIX) + messageTemplate, std::make_format_args(args...));
            std::cout << message << std::endl;
        }
    };
}

#endif // __LOGGER_HPP__