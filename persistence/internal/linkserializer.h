#ifndef DMC_INTERNAL_LINKSERIALIZER_H
#define DMC_INTERNAL_LINKSERIALIZER_H

#include "../jsonxx.h"
#include "Link.h"

namespace DMC {
namespace Internal {

class LinkSerializer
{
public:
    static jsonxx::Object* Serialize(PDC::Link* link);
    static PDC::Link* Deserialize(jsonxx::Object* json);
};

} // namespace Internal
} // namespace DMC

#endif // DMC_INTERNAL_LINKSERIALIZER_H
