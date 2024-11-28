#include "Instrumentation/Instrumentor.hpp"
#include "Utils/Logger.hpp"
#include "AOC/Manager.hpp"

int main() {
    LOG_INIT("../logs/output.log", Logger::LogLevel::Debug);
    Instrumentor::Get().BeginSession("Profile", "profile.json", false);

    try {
        LOG(Logger::LogLevel::Info, "Starting the program");

        AOCManager::getInstance().run();

        InstrumentorPrinting::PrintSessionData(
            Instrumentor::Get().GetFunctionTimes(),
            Instrumentor::Get().GetRuntime()
        );
    } catch (const std::exception& e) {
        LOG(Logger::LogLevel::Error, "Error occurred: " + std::string(e.what()));
    } catch (...) {
        LOG(Logger::LogLevel::Error, "Unknown error occurred!");
    }

    Instrumentor::Get().EndSession();
    return 0;
}
