#include "geometrysource.h"

#include <sstream>

namespace PDC {

GeometrySource::GeometrySource(const char *filePath, const char *objectName)
{
    _filePath = filePath;
    _objectName = objectName;
}

GeometrySource::GeometrySource(const char* serializedGeometrySource)
{
    std::string geometrySource = serializedGeometrySource;
    int index = geometrySource.find_first_of(":");
    _filePath = geometrySource.substr(0,index);
    _objectName = geometrySource.substr(index+1);
}

std::string GeometrySource::GetFilePath()
{
    return _filePath;
}

std::string GeometrySource::GetObjectName()
{
    return _objectName;
}

std::string GeometrySource::Serialize()
{
    std::string text;
    text.append(GetFilePath());
    text.append(":");
    text.append(GetObjectName());
    return text;
}

bool operator==(GeometrySource obj1,GeometrySource obj2)
{
    return ((obj1.GetFilePath() == obj2.GetFilePath())&&
            (obj1.GetObjectName() == obj2.GetObjectName()));
}


} // namespace PDC
