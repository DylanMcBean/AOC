#pragma once

#include <fstream>
#include <vector>
#include <string>

namespace FileUtil
{
    std::ifstream readFile(const std::string &filename);
    void skipLines(std::istream &file, int lines);
    std::vector<std::string> readLines(std::istream &stream, int lines);
    std::vector<std::istringstream> readLineStream(std::istream &stream, int lines);
}
