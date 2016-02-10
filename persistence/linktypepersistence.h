#ifndef DMC_LINKTYPEPERSISTENCE_H
#define DMC_LINKTYPEPERSISTENCE_H

#include "LinkType.h"
#include <string>
#include "jsonxx.h"
#include "filehelper.h"

namespace DMC {

class LinkTypePersistence
{
public:
    static void Save(PDC::LinkType* linkType);
    static PDC::LinkType* Load(const std::string& linkTypeId);
    static PDC::LinkType* LoadFromFile(const std::string& fileName);
    static void Remove(PDC::LinkType* linkType);

protected:
    static void GenerateFileNameFromLinkTypeId(std::string& linkTypeId,std::string& fileName);
    static UTILS::FileHelper _fileHelper;
};

} // namespace DMC

#endif // DMC_LINKTYPEPERSISTENCE_H
