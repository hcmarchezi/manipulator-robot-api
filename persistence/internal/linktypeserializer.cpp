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

    jsonxx::Array geometryPose;
    double pose[4][4];
    linkType->GetGeometryPose(&pose);
    geometryPose << pose[0][0] << pose[0][1] << pose[0][2] << pose[0][3];
    geometryPose << pose[1][0] << pose[1][1] << pose[1][2] << pose[1][3];
    geometryPose << pose[2][0] << pose[2][1] << pose[2][2] << pose[2][3];
    geometryPose << pose[3][0] << pose[3][1] << pose[3][2] << pose[3][3];
    *linkTypeJson << "geometry_pose" << geometryPose;

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
    double pose[4][4];
    jsonxx::Array jsonPose = linkTypeJson->get<jsonxx::Array>("geometry_pose");
    unsigned int index=0;
    for(unsigned int i=0; i < 4; i++)
    {
        for (unsigned int j=0; j < 4; j++)
        {
            index = i*4+j;
            pose[i][j] = jsonPose.get<jsonxx::Number>(index);
        }
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
    linkType->SetGeometryPose(pose);

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
