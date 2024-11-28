#pragma once

#include "Instrumentation/Instrumentor.hpp"
#include "Utils/Logger.hpp"
#include "Utils/File.hpp"

#include <functional>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iomanip>

class AOCManager {
public:
    static AOCManager& getInstance();

    void registerSolution(int year, int day, int index, const std::function<std::string(std::istream&)>& solution);
    void registerTest(int year, int day, int index, const std::string& testInput, const std::string& expected);

    void run(int year = -1, int day = -1, int index = -1);

private:
    AOCManager();

    void runAll();
    void runYear(int year, int index);
    void runDay(int year, int day, int index = -1);
    void executeTest(int year, int day, int index, const std::function<std::string(std::istream&)>& solution,
                     const std::string& expected, const std::string& testInput);
    std::string formatDateString(int year, int day, int index) const;

    using YearDay = std::pair<int, int>;
    using SolutionFunc = std::function<std::string(std::istream&)>;
    using TestPair = std::pair<std::string, std::string>;

    std::map<YearDay, std::map<int, SolutionFunc>> solutions;
    std::map<YearDay, std::map<int, TestPair>> tests;
};

class SolutionRegistrar {
public:
    SolutionRegistrar(int year, int day, int index, const std::function<std::string(std::istream&)>& solution);
};

class TestRegistrar {
public:
    TestRegistrar(int year, int day, int index, const std::string& testInput, const std::string& expected);
};

#define FUNC_NAME_IMPL(year, day, index, line) AOC ## _ ## year ## _ ## day ## _ ## index ## _ ## line
#define FUNC_NAME(year, day, index, line) FUNC_NAME_IMPL(year, day, index, line)

#define REGISTER_SOLUTION_BODY(year, day, index, name, ...)                         \
    static std::string name([[maybe_unused]] std::istream& input) { __VA_ARGS__ }   \
    static SolutionRegistrar FUNC_NAME(year, day, index, __COUNTER__)(year, day, index, name)

#define REGISTER_SOLUTION(year, day, index, ...) \
    REGISTER_SOLUTION_BODY(year, day, index, FUNC_NAME(year, day, index, __COUNTER__), __VA_ARGS__)

#define REGISTER_TEST(year, day, index, testInputStr, expected) \
    static TestRegistrar FUNC_NAME(year, day, index, __COUNTER__)(year, day, index, testInputStr, expected)
