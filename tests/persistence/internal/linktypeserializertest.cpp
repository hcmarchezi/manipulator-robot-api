#include <gtest/gtest.h>
#include <typeinfo>

#include "jsonxx.h"
#include "LinkType.h"
#include "linktypefactory.h"
#include "PrismaticLinkType.h"
#include "RevoluteLinkType.h"
#include "internal/linktypeserializer.h"


// {
//   "id":"some-id",
//   "type":"",
//   "role":"",
//   "twist":9999.99,
//   "legnth":9999.99,
//   "geometry_source": { "file_path" : "file.3ds", "object_name" : "obj" }
//   < "joint_angle":999.99 > if revolute type
//   < "offset:999.99 > if prismatic type
// }

TEST(LinkTypeSerializerTest,serializePrismaticLinkType)
{
    PDC::LinkType* linkType = PDC::LinkTypeFactory::Create("Prismatic","my-id");
    linkType->SetRole(PDC::LinkType::LINK);
    linkType->SetTwist(0.5);
    linkType->SetLength(1.5);
    linkType->SetGeometrySource(PDC::GeometrySource("geometry.3ds","obj3d"));
    ((PDC::PrismaticLinkType*)linkType)->SetJointAngle(0.25);

    jsonxx::Object* linkTypeJson = DMC::Internal::LinkTypeSerializer::Serialize(linkType);

    ASSERT_STREQ("my-id",linkTypeJson->get<jsonxx::String>("id").c_str());
    ASSERT_STREQ("prismatic",linkTypeJson->get<jsonxx::String>("type").c_str());
    ASSERT_STREQ("link",linkTypeJson->get<jsonxx::String>("role").c_str());
    ASSERT_DOUBLE_EQ(0.5,linkTypeJson->get<jsonxx::Number>("twist"));
    ASSERT_DOUBLE_EQ(1.5,linkTypeJson->get<jsonxx::Number>("length"));
    jsonxx::Object geometrySourceJson = linkTypeJson->get<jsonxx::Object>("geometry_source");
    ASSERT_STREQ("geometry.3ds", geometrySourceJson.get<jsonxx::String>("file_path").c_str());
    ASSERT_STREQ("obj3d", geometrySourceJson.get<jsonxx::String>("object_name").c_str());
    ASSERT_DOUBLE_EQ(0.25,linkTypeJson->get<jsonxx::Number>("joint_angle"));
}

TEST(LinkTypeSerializerTest,serializeRevoluteLinkType)
{
    PDC::LinkType* linkType = PDC::LinkTypeFactory::Create("Revolute","my-id");
    linkType->SetRole(PDC::LinkType::LINK);
    linkType->SetTwist(0.5);
    linkType->SetLength(1.5);
    linkType->SetGeometrySource(PDC::GeometrySource("geometry.3ds","obj3d"));
    ((PDC::RevoluteLinkType*)linkType)->SetOffset(0.25);

    jsonxx::Object* linkTypeJson = DMC::Internal::LinkTypeSerializer::Serialize(linkType);

    ASSERT_STREQ("my-id",linkTypeJson->get<jsonxx::String>("id").c_str());
    ASSERT_STREQ("revolute",linkTypeJson->get<jsonxx::String>("type").c_str());
    ASSERT_STREQ("link",linkTypeJson->get<jsonxx::String>("role").c_str());
    ASSERT_DOUBLE_EQ(0.5,linkTypeJson->get<jsonxx::Number>("twist"));
    ASSERT_DOUBLE_EQ(1.5,linkTypeJson->get<jsonxx::Number>("length"));
    jsonxx::Object geometrySource = linkTypeJson->get<jsonxx::Object>("geometry_source");
    ASSERT_STREQ("geometry.3ds", geometrySource.get<jsonxx::String>("file_path").c_str());
    ASSERT_STREQ("obj3d", geometrySource.get<jsonxx::String>("object_name").c_str());
    ASSERT_DOUBLE_EQ(0.25,linkTypeJson->get<jsonxx::Number>("offset"));
}

TEST(LinkTypeSerializerTest,deserializePrismaticLinkType)
{
    std::string json = "";
    json.append("{");
    json.append("\"id\":\"some-id\",");
    json.append("\"type\":\"prismatic\",");
    json.append("\"role\":\"link\",");
    json.append("\"twist\" : 0.5,");
    json.append("\"length\": 1.5,");
    json.append("\"geometry_source\": { \"file_path\":\"geometry.3ds\", \"object_name\":\"obj3d\" },");
    json.append("\"joint_angle\": 0.25 ");
    json.append("}");
    jsonxx::Object linkTypeJson;
    linkTypeJson.parse(json);

    PDC::LinkType* linkType = DMC::Internal::LinkTypeSerializer::Deserialize(&linkTypeJson);

    ASSERT_STREQ("prismatic",linkType->GetJointType().c_str());
    ASSERT_EQ("some-id",linkType->GetId());
    ASSERT_EQ("link",linkType->GetRole());
    ASSERT_DOUBLE_EQ(0.5,linkType->GetTwist());
    ASSERT_DOUBLE_EQ(1.5,linkType->GetLength());
    ASSERT_STREQ("geometry.3ds",linkType->GetGeometrySource().GetFilePath().c_str());
    ASSERT_STREQ("obj3d",linkType->GetGeometrySource().GetObjectName().c_str());
    ASSERT_DOUBLE_EQ(0.25,((PDC::PrismaticLinkType*)linkType)->GetJointAngle());
}

TEST(LinkTypeSerializerTest,deserializeRevoluteLinkType)
{
    std::string json = "";
    json.append("{");
    json.append("\"id\":\"some-id\",");
    json.append("\"type\":\"revolute\",");
    json.append("\"role\":\"link\",");
    json.append("\"twist\" : 0.5,");
    json.append("\"length\": 1.5,");
    json.append("\"geometry_source\": { \"file_path\":\"geometry.3ds\", \"object_name\":\"obj3d\" },");
    json.append("\"offset\": 0.25 ");
    json.append("}");
    jsonxx::Object linkTypeJson;
    linkTypeJson.parse(json);

    PDC::LinkType* linkType = DMC::Internal::LinkTypeSerializer::Deserialize(&linkTypeJson);

    ASSERT_STREQ("revolute",linkType->GetJointType().c_str());
    ASSERT_EQ("some-id",linkType->GetId());
    ASSERT_EQ("link",linkType->GetRole());
    ASSERT_DOUBLE_EQ(0.5,linkType->GetTwist());
    ASSERT_DOUBLE_EQ(1.5,linkType->GetLength());
    ASSERT_STREQ("geometry.3ds",linkType->GetGeometrySource().GetFilePath().c_str());
    ASSERT_STREQ("obj3d",linkType->GetGeometrySource().GetObjectName().c_str());
    ASSERT_DOUBLE_EQ(0.25,((PDC::RevoluteLinkType*)linkType)->GetOffset());
}
