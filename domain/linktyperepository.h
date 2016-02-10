#ifndef PDC_LINKTYPEREPOSITORY_H
#define PDC_LINKTYPEREPOSITORY_H

#include "LinkType.h"

#include <map>

namespace PDC {

class LinkTypeRepository
{
public:
    static void Add(PDC::LinkType* linkType);
    static PDC::LinkType* Get(std::string linkTypeId);
    static void Clear();

protected:
    LinkTypeRepository() { }
    static std::map<std::string,PDC::LinkType*> _repository;
};

} // namespace PDC

#endif // PDC_LINKTYPEREPOSITORY_H
