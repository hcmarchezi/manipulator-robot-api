#include <gtest/gtest.h>
#include "geometry.h"
#include "geometryreader.h"
#include "geometrysource.h"

TEST(GeometryReaderTest,readFrom3DSFile)
{
    DMC::GeometryReader geometryReader;
    PDC::Geometry* geometry = geometryReader.read3DSFile(PDC::GeometrySource("robotarm.3ds","Base"));
    ASSERT_EQ(108,geometry->FacesCount());
}
