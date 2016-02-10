#include "linktyperepository.h"

namespace PDC
{
    std::map<std::string,PDC::LinkType*> LinkTypeRepository::_repository;

    void LinkTypeRepository::Add(PDC::LinkType* linkType)
    {
        _repository[linkType->GetId()] = linkType;
    }

    PDC::LinkType* LinkTypeRepository::Get(std::string linkTypeId)
    {
        return _repository[linkTypeId];
    }

    void LinkTypeRepository::Clear()
    {
        _repository.clear();
    }

} // namespace PDC
