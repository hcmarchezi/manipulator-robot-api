#ifndef PDC_GEOMETRYSOURCE_H
#define PDC_GEOMETRYSOURCE_H

#include <string>

namespace PDC {

class GeometrySource
{
public:
    GeometrySource(const char* filePath, const char* objectName);
    GeometrySource(const char* serializedGeometrySource);
    std::string GetFilePath();
    std::string GetObjectName();
    std::string Serialize();
protected:
    std::string _filePath;
    std::string _objectName;
};

bool operator==(PDC::GeometrySource obj1, PDC::GeometrySource obj2);

} // namespace PDC

#endif // PDC_GEOMETRYSOURCE_H
