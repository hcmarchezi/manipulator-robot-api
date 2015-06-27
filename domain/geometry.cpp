#include "geometry.h"

namespace PDC {

Geometry::Geometry()
{
}

unsigned long Geometry::FacesCount()
{
    return _faces.size();
}

void Geometry::AddFace(PDC::Face face)
{
    _faces.push_back(face);
}

const PDC::Face& Geometry::GetFace(unsigned long index)
{
    return _faces[index];
}

} // namespace PDC
