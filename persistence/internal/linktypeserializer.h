#ifndef DMC_INTERNAL_LINKTYPESERIALIZER_H
#define DMC_INTERNAL_LINKTYPESERIALIZER_H

#include "../jsonxx.h"
#include "LinkType.h"

namespace DMC {
    namespace Internal {
        class LinkTypeSerializer
        {
        public:
            static jsonxx::Object* Serialize(PDC::LinkType* linkType);
            static PDC::LinkType* Deserialize(jsonxx::Object* linkTypeJson);
        private:
            static PDC::LinkType::Role StringToLinkTypeRole(std::string role);
        };
    } // namespace Internal
} // namespace DMC

#endif // DMC_INTERNAL_LINKTYPESERIALIZER_H
