#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>

namespace UTILS
{
class FileHelper
{
public:
    FileHelper() {}
    bool Exists(const std::string& filePath);
    bool Remove(const std::string& filePath);
    const std::string& Read(const std::string& filePath);
    void Write(const std::string& filePath, std::string& contents);

private: 
    std::string _fileContents;
};

}

#endif // FILEUTILS_H
