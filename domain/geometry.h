#ifndef PDC_GEOMETRY_H
#define PDC_GEOMETRY_H

#include "Face.h"

#include <vector>

namespace PDC
{
    class Geometry
    {
    public:
        Geometry();
        unsigned long FacesCount();
        void AddFace(PDC::Face face);
        const Face &GetFace(unsigned long index);

    protected:
        std::vector<PDC::Face> _faces;
    };
} // namespace PDC

#endif // PDC_GEOMETRY_H
