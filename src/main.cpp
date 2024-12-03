#include "Utils/Logger.hpp"
#include "AOC/Manager.hpp"

int main() {
    LOG_INIT("../logs/output.log", Logger::LogLevel::Debug);

    try {
        LOG(Logger::LogLevel::Info, "Starting the program");

        AOCManager::getInstance().run(2024, 2);

    } catch (const std::exception& e) {
        LOG(Logger::LogLevel::Error, "Error occurred: " + std::string(e.what()));
    } catch (...) {
        LOG(Logger::LogLevel::Error, "Unknown error occurred!");
    }
    return 0;
}
