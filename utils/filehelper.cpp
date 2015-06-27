#include "filehelper.h"

#include <fstream>
#include <cstdio>
#include <sstream>

bool UTILS::FileHelper::Exists(const std::string& filePath)
{
    std::ifstream inputfile(filePath.c_str());
    return inputfile.good();
}

bool UTILS::FileHelper::Remove(const std::string& filePath)
{
    int result = std::remove(filePath.c_str());
    return (result == 0);
}

const std::string& UTILS::FileHelper::Read(const std::string& filePath)
{
    std::ifstream inputfile(filePath.c_str());
    std::stringstream buffer;
    buffer << inputfile.rdbuf();
    inputfile.close();
    _fileContents = buffer.str();
    return _fileContents;
}

void UTILS::FileHelper::Write(const std::string &filePath, std::string& contents)
{
    std::ofstream outputfile(filePath.c_str());
    outputfile << contents;
    outputfile.close();
}
