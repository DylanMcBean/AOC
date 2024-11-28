#include "AOC/Manager.hpp"

AOCManager& AOCManager::getInstance() {
    static AOCManager instance;
    return instance;
}

AOCManager::AOCManager() = default;

void AOCManager::registerSolution(int year, int day, int index, const std::function<std::string(std::istream&)>& solution) {
    LOG(Logger::LogLevel::Debug, "Registering solution for Year: {}, Day: {}, Index: {}", year, day, index);
    solutions[{year, day}][index] = solution;
}

void AOCManager::registerTest(int year, int day, int index, const std::string& testInput, const std::string& expected) {
    LOG(Logger::LogLevel::Debug, "Registering test for Year: {}, Day: {}, Index: {}", year, day, index);
    tests[{year, day}][index] = {expected, testInput};
}

void AOCManager::run(int year, int day, int index) {
    PROFILE_FUNCTION();
    if (year == -1) {
        runAll();
    } else if (day == -1) {
        runYear(year, index);
    } else {
        runDay(year, day, index);
    }
}

void AOCManager::runAll() {
    PROFILE_FUNCTION();
    LOG(Logger::LogLevel::Info, "Running all challenges and tests");

    for (const auto& [key, _] : solutions) {
        const auto& [year, day] = key;
        runDay(year, day);
    }
}

void AOCManager::runYear(int year, int index) {
    PROFILE_FUNCTION();
    LOG(Logger::LogLevel::Info, "Running all challenges and tests for Year: {}", year);
    for (const auto& [key, _] : solutions) {
        if (key.first == year) {
            runDay(year, key.second, index);
        }
    }
}

void AOCManager::runDay(int year, int day, int index) {
    PROFILE_FUNCTION();

    auto solIt = solutions.find({year, day});
    auto testIt = tests.find({year, day});

    if (solIt == solutions.end() && testIt == tests.end()) {
        LOG(Logger::LogLevel::Info, "No entries registered for Year: {}, Day: {}", year, day);
        return;
    }

    std::set<int> indices;
    if (solIt != solutions.end()) {
        for (const auto& [idx, _] : solIt->second) {
            indices.insert(idx);
        }
    }
    if (testIt != tests.end()) {
        for (const auto& [idx, _] : testIt->second) {
            indices.insert(idx);
        }
    }

    for (int idx : indices) {
        if (index != -1 && idx != index) continue;

        if (testIt != tests.end() && testIt->second.count(idx) && solIt != solutions.end() && solIt->second.count(idx)) {
            const auto& [expected, testInput] = testIt->second[idx];
            executeTest(year, day, idx, solIt->second[idx], expected, testInput);
        }

        if (solIt != solutions.end() && solIt->second.count(idx)) {
            std::ifstream file("../data/AOC/" + std::to_string(year) + "/" + std::to_string(day) + ".txt");
            if (!file) {
                LOG(Logger::LogLevel::Error, "Failed to open file for Year: {}, Day: {}", year, day);
                continue;
            }
            std::string formattedDate = formatDateString(year, day, idx);
            std::string result = solIt->second[idx](file);
            LOG(Logger::LogLevel::Info, "{}: \033[1;36;38mAnswer\033[0m: {}", formattedDate, result);
        }
    }
}

void AOCManager::executeTest(int year, int day, int index, const std::function<std::string(std::istream&)>& solution,
                             const std::string& expected, const std::string& testInput) {
    PROFILE_FUNCTION();
    std::istringstream inputStream(testInput);
    std::string result = solution(inputStream);
    std::string formattedDate = formatDateString(year, day, index);
    if (result == expected) {
        LOG(Logger::LogLevel::Info, "{}: \033[1;37;42m[PASS]\033[0m", formattedDate);
    } else {
        LOG(Logger::LogLevel::Error, "{}: \033[1;37;41m[FAIL]\033[0m: Got: {}, Expected: {}", formattedDate, result, expected);
    }
}

std::string AOCManager::formatDateString(int year, int day, int index) const {
    std::ostringstream oss;
    oss << year << "::" << std::setfill('0') << std::setw(2) << day << "-" << index;
    return oss.str();
}

SolutionRegistrar::SolutionRegistrar(int year, int day, int index, const std::function<std::string(std::istream&)>& solution) {
    AOCManager::getInstance().registerSolution(year, day, index, solution);
}

TestRegistrar::TestRegistrar(int year, int day, int index, const std::string& testInput, const std::string& expected) {
    AOCManager::getInstance().registerTest(year, day, index, testInput, expected);
}
