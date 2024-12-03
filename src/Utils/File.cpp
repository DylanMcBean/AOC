#include "Utils/File.hpp"
#include "Utils/Logger.hpp"

#include <limits>

namespace FileUtil
{
    std::ifstream readFile(const std::string &filename)
    {
        std::ifstream inputFile(filename, std::ios::binary);

        if (!inputFile.is_open())
        {
            LOG_THROW(Logger::LogLevel::Error, "Failed to open the file: {}", filename);
        }

        return inputFile;
    }

    void skipLines(std::istream &stream, int lines)
    {
        for (int i = 0; i < lines; ++i)
        {
            stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    std::vector<std::string> readLines(std::istream &stream, int lines = -1)
    {
        std::vector<std::string> linesRead;
        std::string line;

        while (std::getline(stream, line) && (lines == -1 || lines != 0))
        {
            linesRead.push_back(line);
            if (lines != -1)
                --lines;
        }

        return linesRead;
    }
}
