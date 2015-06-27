#ifndef DMC_INTERNAL_TRAJECTORYSERIALIZER_H
#define DMC_INTERNAL_TRAJECTORYSERIALIZER_H

#include "trajectory.h"
#include "../jsonxx.h"

namespace DMC {
namespace Internal {

class TrajectorySerializer
{
public:
    static jsonxx::Object* serialize(PDC::Trajectory* trajectory);
    static PDC::Trajectory* deserialize(jsonxx::Object& json);
};

} // namespace Internal
} // namespace DMC

#endif // DMC_INTERNAL_TRAJECTORYSERIALIZER_H
