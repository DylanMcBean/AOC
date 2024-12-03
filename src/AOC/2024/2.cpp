#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <limits>
#include "AOC/Manager.hpp"

namespace
{

#define DAY 2

std::string test_input_1 = 
    "7 6 4 2 1\n"
    "1 3 6 7 9\n"
    "1 2 7 8 9\n"
    "9 7 6 2 1\n"
    "1 3 2 4 5\n"
    "8 6 4 4 1";

REGISTER_TEST(2024, DAY, 1, test_input_1, "2");

bool is_safe(const std::vector<int>& numbers) {
    int prev = numbers[0];
    int dir_sign = 0;
    for (size_t i = 1; i < numbers.size(); ++i) {
        int diff = numbers[i] - prev;
        int current_sign = (diff > 0) - (diff < 0);
        if (std::abs(diff) == 0 || std::abs(diff) > 3 || (dir_sign != 0 && current_sign != dir_sign)) {
            return false;
        }
        dir_sign = current_sign;
        prev = numbers[i];
    }
    return true;
}

bool is_safe_iterative(const std::vector<int>& report) {
    for (size_t i = 0; i < report.size(); ++i) {
        std::vector<int> modified_report(report.begin(), report.end());
        modified_report.erase(modified_report.begin() + i);
        if (is_safe(modified_report)) {
            return true;
        }
    }
    return false;
}

REGISTER_SOLUTION(2024, DAY, 1, {
    std::vector<std::string> lines = FileUtil::readLines(input, -1);
    PROFILE_FUNCTION();
    int safe_count = 0;
    for (const auto& line : lines) {
        std::istringstream line_stream(line);
        std::vector<int> numbers;
        int num;
        while (line_stream >> num) {
            numbers.push_back(num);
        }
        if (is_safe(numbers)) {
            ++safe_count;
        }
    }
    return std::to_string(safe_count);
});

std::string test_input_2 = 
    "7 6 4 2 1\n"
    "1 3 6 7 9\n"
    "1 2 7 8 9\n"
    "9 7 6 2 1\n"
    "1 3 2 4 5\n"
    "8 6 4 4 1";

REGISTER_TEST(2024, DAY, 2, test_input_2, "4");

REGISTER_SOLUTION(2024, DAY, 2, {
    std::vector<std::string> lines = FileUtil::readLines(input, -1);
    PROFILE_FUNCTION();
    int safe_count = 0;
    for (const auto& line : lines) {
        std::istringstream line_stream(line);
        std::vector<int> numbers;
        int num;
        while (line_stream >> num) {
            numbers.push_back(num);
        }
        if (is_safe_iterative(numbers)) {
            ++safe_count;
        }
    }
    return std::to_string(safe_count);
});

} // namespace
