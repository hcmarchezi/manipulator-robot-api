#ifndef PDC_LINKTYPEFACTORY_H
#define PDC_LINKTYPEFACTORY_H

#include "LinkType.h"
#include <string>

namespace PDC {

class LinkTypeFactory
{
public:
    static PDC::LinkType* Create(std::string jointType,std::string linkTypeId);

private:
    LinkTypeFactory();
};

} // namespace PDC

#endif // PDC_LINKTYPEFACTORY_H
