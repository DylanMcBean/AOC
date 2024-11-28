#include "Utils/Logger.hpp"
#include <cstdarg>
#include <iomanip>
#include <iostream>
#include <sstream>

Logger &Logger::Instance()
{
    static Logger instance;
    return instance;
}

void Logger::InitializeLogFile(const std::string &logFilePath, LogLevel logLevel)
{
    if (!logFileInitialized)
    {
        logFile.open(logFilePath, std::ios::app);
        if (!logFile.is_open())
        {
            throw std::runtime_error("Failed to open log file: " + logFilePath);
        }
        logFileInitialized = true;
        Instance().SetLogLevel(logLevel);
    }
}

void Logger::outputLog(LogLevel level, const std::string &message, const std::source_location &location)
{
    static const std::unordered_map<LogLevel, std::tuple<std::string, std::string, FILE *>> logLevelMap = {
        {LogLevel::Debug, {"Debug", "\033[36m", stdout}},
        {LogLevel::Info, {"Info", "\033[32m", stdout}},
        {LogLevel::Warning, {"Warning", "\033[33m", stdout}},
        {LogLevel::Error, {"Error", "\033[31m", stderr}}};

    const auto &[levelStr, colorCode, stream] = logLevelMap.at(level);

    if (logDict.find(location) == logDict.end())
    {
        logDict[location] = logDict.size() + 1;
    }
    uint64_t logDictIndex = logDict[location];

    std::ostringstream logStream;
    logStream << colorCode << "[" << std::hex << std::setw(4) << std::setfill('0') << logDictIndex << "] " << levelStr
              << "\033[0m: " << message;

    fprintf(stream, "%s\n", logStream.str().c_str());

    if (logFile.is_open())
    {
        logFile << "[" << location.file_name() << ":" << location.function_name() << ":" << location.line() << "] "
                << levelStr << ": " << message << std::endl;
        logFile.flush();
    }
}

std::string Logger::toByteEncoded(const uint8_t *data, size_t length)
{
    static const char hexChars[] = "0123456789ABCDEF";
    std::string result;
    result.reserve(length * 4);

    for (size_t i = 0; i < length; ++i)
    {
        if (data[i] < 0x20 || data[i] > 0x7E)
        {
            result += "\\x";
            result += hexChars[(data[i] >> 4) & 0x0F];
            result += hexChars[data[i] & 0x0F];
        }
        else
        {
            result += static_cast<char>(data[i]);
        }
    }
    return result;
}