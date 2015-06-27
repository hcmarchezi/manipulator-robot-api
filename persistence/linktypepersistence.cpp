#include "linktypepersistence.h"

#include "PrismaticLinkType.h"
#include "RevoluteLinkType.h"
#include "linktypefactory.h"
#include "internal/linktypeserializer.h"
#include <jsonxx.h>
#include "filehelper.h"

#include <fstream>

namespace DMC {

UTILS::FileHelper DMC::LinkTypePersistence::_fileHelper;

void DMC::LinkTypePersistence::Save(PDC::LinkType* linkType)
{
    jsonxx::Object* obj = Internal::LinkTypeSerializer::Serialize(linkType);
    std::string fileName;
    std::string linkTypeId = linkType->GetId();
    GenerateFileNameFromLinkTypeId(linkTypeId,fileName);
    std::string json = obj->json();
    _fileHelper.Write(fileName,json);
}

PDC::LinkType* DMC::LinkTypePersistence::Load(const std::string& linkTypeId)
{        
    std::string fileName;
    std::string id = linkTypeId;
    GenerateFileNameFromLinkTypeId(id,fileName);
    std::string json = _fileHelper.Read(fileName);
    jsonxx::Object obj;
    obj.parse(json);
    PDC::LinkType* linkType = Internal::LinkTypeSerializer::Deserialize(&obj);
    return linkType;
}

void DMC::LinkTypePersistence::Remove(PDC::LinkType* linkType)
{
    std::string fileName;
    std::string linkTypeId = linkType->GetId();
    GenerateFileNameFromLinkTypeId(linkTypeId,fileName);
    _fileHelper.Remove(fileName);
}

void DMC::LinkTypePersistence::GenerateFileNameFromLinkTypeId(std::string& linkTypeId,std::string& fileName)
{
    fileName.append(linkTypeId);
    fileName.append(".linktype");
}

} // namespace DMC
