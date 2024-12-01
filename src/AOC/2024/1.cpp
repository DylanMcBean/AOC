#include <iostream>

#include "AOC/Manager.hpp"

namespace
{

std::string test_input_1 = "3   4"
                           "\n4   3"
                           "\n2   5"
                           "\n1   3"
                           "\n3   9"
                           "\n3   3";

REGISTER_TEST(2024, 1, 1, test_input_1, "11");

REGISTER_SOLUTION(2024, 1, 1, {
    PROFILE_FUNCTION();
    std::vector<std::string> lines = FileUtil::readLines(input, -1);

    std::vector<int> left_nums;
    std::vector<int> right_nums;

    for (std::string &line : lines)
    {
        std::istringstream stream(line);
        int left;
        int right;
        stream >> left >> right;
        left_nums.push_back(left);
        right_nums.push_back(right);
    }

    std::sort(left_nums.begin(), left_nums.end());
    std::sort(right_nums.begin(), right_nums.end());

    int sum = 0;

    for (size_t i = 0; i < left_nums.size(); i++)
    {
        sum += std::abs(right_nums[i] - left_nums[i]);
    }

    return std::to_string(sum);
});

std::string test_input_2 = "3   4"
                           "\n4   3"
                           "\n2   5"
                           "\n1   3"
                           "\n3   9"
                           "\n3   3";

REGISTER_TEST(2024, 1, 2, test_input_2, "31");

REGISTER_SOLUTION(2024, 1, 2, {
    PROFILE_FUNCTION();
    std::vector<std::string> lines = FileUtil::readLines(input, -1);

    std::vector<int> left_nums;
    std::vector<int> right_nums;

    for (std::string &line : lines)
    {
        std::istringstream stream(line);
        int left;
        int right;
        stream >> left >> right;
        left_nums.push_back(left);
        right_nums.push_back(right);
    }

    std::map<int, int> num_counts;

    for (int num : left_nums)
    {
        num_counts.try_emplace(num, 0);
    }

    for (int num : right_nums)
    {
        num_counts[num]++;
    }

    uint64_t sum = 0;

    for (int num : left_nums)
    {
        sum += num * num_counts[num];
    }

    return std::to_string(sum);
});

} // namespace
