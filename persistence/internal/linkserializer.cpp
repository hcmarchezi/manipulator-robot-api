#include "linkserializer.h"
#include "linktyperepository.h"

namespace DMC {
namespace Internal {

// {
//   "link_type_id":"",
//   "joint_move":999.99,
// }

jsonxx::Object* LinkSerializer::Serialize(PDC::Link* link)
{
    jsonxx::Object* linkJson = new jsonxx::Object();
    *linkJson << "link_type_id" << link->GetLinkType()->GetId();
    *linkJson << "joint_move" << link->GetJointMove();
    return linkJson;
}

PDC::Link* LinkSerializer::Deserialize(jsonxx::Object* json)
{
    std::string linkTypeId = json->get<jsonxx::String>("link_type_id");
    double jointMove = json->get<jsonxx::Number>("joint_move");
    PDC::LinkType* linkType = PDC::LinkTypeRepository::Get(linkTypeId);
    PDC::Link* link = new PDC::Link(linkType);
    link->SetJointMove(jointMove);
    return link;
}

} // namespace Internal
} // namespace DMC
