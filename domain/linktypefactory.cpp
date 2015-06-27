#include "linktypefactory.h"

#include "PrismaticLinkType.h"
#include "RevoluteLinkType.h"

namespace PDC {

LinkTypeFactory::LinkTypeFactory()
{
}

PDC::LinkType* LinkTypeFactory::Create(std::string jointType,std::string linkTypeId)
{
    PDC::LinkType* linkType = NULL;
    if (jointType == "Prismatic")
    {
        linkType = new PDC::PrismaticLinkType(linkTypeId);
    }
    else if (jointType == "Revolute")
    {
        linkType = new PDC::RevoluteLinkType(linkTypeId);
    }
    return linkType;
}


} // namespace PDC
