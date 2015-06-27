#ifndef DMC_GEOMETRYREADER_H
#define DMC_GEOMETRYREADER_H

#include "geometry.h"
#include "geometrysource.h"

#include <string>

namespace DMC {

class GeometryReader
{
public:
    GeometryReader();
    PDC::Geometry* read3DSFile(PDC::GeometrySource geometrySource);
};

} // namespace DMC

#endif // DMC_GEOMETRYREADER_H
