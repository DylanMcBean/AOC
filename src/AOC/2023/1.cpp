#include "AOC/Manager.hpp"

const std::string test_input_1 =
    "1abc2\n"
    "pqr3stu8vwx\n"
    "a1b2c3d4e5f\n"
    "treb7uchet\n";

REGISTER_TEST(2023, 1, 1, test_input_1, "142");

REGISTER_SOLUTION(2023, 1, 1, {
    PROFILE_FUNCTION();
    std::vector<std::string> lines = FileUtil::readLines(input, -1);
    
    int sum = 0;
    for (const auto& line : lines) {
        int left = -1;
        int right = -1;
        for (const char c : line) {
            if (!std::isdigit(c)) continue;
            right = c - '0';
            if (left < 0) left = c - '0';
        }
        sum += (left * 10) + right;
    }

    return std::to_string(sum);
});

const std::string test_input_2 = 
    "two1nine\n"
    "eightwothree\n"
    "abcone2threexyz\n"
    "xtwone3four\n"
    "4nineeightseven2\n"
    "zoneight234\n"
    "7pqrstsixteen\n";

REGISTER_TEST(2023, 1, 2, test_input_2, "281");

int getDigit(const std::string_view& sv, int i) {
    PROFILE_FUNCTION();
    std::vector<std::string> digits = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    if (std::isdigit(sv[i])) {
        return sv[i] - '0';
    } else {
        for (size_t j = 0; j < digits.size(); j++) {
            if (sv.substr(i, digits[j].size()) == digits[j]) {
                return j;
            }
        }
    }
    return -1;
}

REGISTER_SOLUTION(2023, 1, 2, {
    PROFILE_FUNCTION();
    std::vector<std::string> lines = FileUtil::readLines(input, -1);

    int sum = 0;
    for (const auto& line : lines) {
        int left = -1;
        int right = -1;
        std::string_view sv(line);
        for (size_t i = 0; i < sv.size(); i++) {
            int digit = getDigit(sv, i);
            if (digit < 0) continue;
            right = digit;
            if (left < 0) left = digit;
        }
        sum += (left * 10) + right;
    }

    return std::to_string(sum);
});