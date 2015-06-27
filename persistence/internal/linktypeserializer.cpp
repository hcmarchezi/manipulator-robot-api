#include "linktypeserializer.h"

#include <typeinfo>

#include "PrismaticLinkType.h"
#include "RevoluteLinkType.h"

namespace DMC {
namespace Internal {

jsonxx::Object* LinkTypeSerializer::Serialize(PDC::LinkType* linkType)
{
    jsonxx::Object* linkTypeJson = new jsonxx::Object();
    *linkTypeJson << "id" << linkType->GetId();
    *linkTypeJson << "type" << linkType->GetJointType();
    *linkTypeJson << "role" << linkType->GetRole();
    *linkTypeJson << "twist" << linkType->GetTwist();
    *linkTypeJson << "length" << linkType->GetLength();

    jsonxx::Object geometrySource;
    geometrySource << "file_path" << linkType->GetGeometrySource().GetFilePath();
    geometrySource << "object_name" << linkType->GetGeometrySource().GetObjectName();
    *linkTypeJson << "geometry_source" << geometrySource;

    std::string jointType = linkType->GetJointType();

    if (jointType == "prismatic")
    {
        *linkTypeJson << "joint_angle" << ((PDC::PrismaticLinkType*)linkType)->GetJointAngle();
    }
    else if (jointType == "revolute")
    {
        *linkTypeJson << "offset" << ((PDC::RevoluteLinkType*)linkType)->GetOffset();
    }

    return linkTypeJson;
}

PDC::LinkType* LinkTypeSerializer::Deserialize(jsonxx::Object* linkTypeJson)
{
    std::string id   = linkTypeJson->get<jsonxx::String>("id");
    std::string type = linkTypeJson->get<jsonxx::String>("type");
    std::string role = linkTypeJson->get<jsonxx::String>("role");
    double twist  = linkTypeJson->get<jsonxx::Number>("twist");
    double length = linkTypeJson->get<jsonxx::Number>("length");
    std::string filePath = "";
    std::string objectName = "";
    jsonxx::Object geometrySource = linkTypeJson->get<jsonxx::Object>("geometry_source");
    if (!geometrySource.empty())
    {
        filePath   = geometrySource.get<jsonxx::String>("file_path");
        objectName = geometrySource.get<jsonxx::String>("object_name");
    }
    double jointAngle = 0.0;
    double offset = 0.0;
    if (type == "prismatic")
    {
        jointAngle = linkTypeJson->get<jsonxx::Number>("joint_angle");
    }
    else if (type == "revolute")
    {
        offset = linkTypeJson->get<jsonxx::Number>("offset");
    }

    PDC::LinkType* linkType = NULL;
    if (type == "prismatic")
    {
        linkType = new PDC::PrismaticLinkType(id);
        ((PDC::PrismaticLinkType*)linkType)->SetJointAngle(jointAngle);
    }
    else if (type == "revolute")
    {
        linkType = new PDC::RevoluteLinkType(id);
        ((PDC::RevoluteLinkType*)linkType)->SetOffset(offset);
    }
    linkType->SetRole(StringToLinkTypeRole(role));
    linkType->SetTwist(twist);
    linkType->SetLength(length);
    linkType->SetGeometrySource(PDC::GeometrySource(filePath.c_str(),objectName.c_str()));

    return linkType;
}

PDC::LinkType::Role LinkTypeSerializer::StringToLinkTypeRole(std::string role)
{
    PDC::LinkType::Role linkTypeRole;
    if (role == "base")
    {
        linkTypeRole = PDC::LinkType::BASE;
    }
    else if (role == "link")
    {
        linkTypeRole = PDC::LinkType::LINK;
    }
    else if (role == "end_effector")
    {
        linkTypeRole = PDC::LinkType::END_EFFECTOR;
    }
    else
    {
        linkTypeRole = PDC::LinkType::UNKNOWN;
    }
    return linkTypeRole;
}


} // namespace Internal
} // namespace DMC
