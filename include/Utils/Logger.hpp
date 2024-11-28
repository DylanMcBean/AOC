#pragma once

#include <cstdint>
#include <format>
#include <fstream>
#include <memory>
#include <source_location>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

struct SourceLocationHash
{
    std::size_t operator()(const std::source_location &loc) const noexcept
    {
        std::size_t hash = std::hash<std::string_view>{}(loc.file_name());
        hash ^= std::hash<unsigned int>{}(loc.line()) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<unsigned int>{}(loc.column()) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        hash ^= std::hash<std::string_view>{}(loc.function_name()) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        return hash;
    }
};

struct SourceLocationEqual
{
    bool operator()(const std::source_location &lhs, const std::source_location &rhs) const noexcept
    {
        return lhs.file_name() == rhs.file_name() && lhs.line() == rhs.line() && lhs.column() == rhs.column() &&
               lhs.function_name() == rhs.function_name();
    }
};

class Logger
{
  public:
    enum class LogLevel
    {
        Debug,
        Info,
        Warning,
        Error
    };
    static Logger &Instance();

    void InitializeLogFile(const std::string &logFilePath, LogLevel logLevel);

    template <typename... Args>
    std::runtime_error Log(LogLevel level, const std::string &formatStr,
                           const std::source_location location = std::source_location::current(), Args &&...args)
    {
        if (level >= logLevel)
        {
            std::string formattedMessage = std::vformat(formatStr, std::make_format_args(std::forward<Args>(args)...));

            outputLog(level, formattedMessage, location);

            std::ostringstream errorStream;
            errorStream << "[" << location.file_name() << ":" << location.line() << "] "
                        << "Level: " << static_cast<int>(level) << " - " << formattedMessage;

            // should only throw with log level: Error
            return std::runtime_error(errorStream.str());
        }
        // should not get here if log level is Error
        return std::runtime_error("");
    }

    static std::string toByteEncoded(const uint8_t *data, size_t length);
    void SetLogLevel(LogLevel logLevel)
    {
        this->logLevel = logLevel;
    }

  private:
    Logger() = default;
    void outputLog(LogLevel level, const std::string &message, const std::source_location &location);

    std::ofstream logFile;
    bool logFileInitialized = false;
    LogLevel logLevel = LogLevel::Info;
    std::unordered_map<std::source_location, uint64_t, SourceLocationHash, SourceLocationEqual> logDict;
};

#define LOG(level, format, ...) Logger::Instance().Log(level, format, std::source_location::current(), ##__VA_ARGS__)
#define LOG_THROW(level, format, ...)                                                                                  \
    throw Logger::Instance().Log(level, format, std::source_location::current(), ##__VA_ARGS__)
#define LOG_INIT(logFilePath, logLevel) Logger::Instance().InitializeLogFile(logFilePath, logLevel)