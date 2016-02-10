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
//   "geometry_source": { "file_path" : "file.3ds", "object_name" : "obj" },
//   < "joint_angle":999.99 > if revolute type
//   < "offset:999.99 > if prismatic type
//   "geometry_pose" : [ [0.0, 0.0, 0.0, 0.0],
//                       [0.0, 0.0, 0.0, 0.0],
//                       [0.0, 0.0, 0.0, 0.0],
//                       [0.0, 0.0, 0.0, 0.0] ]
// }

TEST(LinkTypeSerializerTest,serializePrismaticLinkType)
{
    PDC::LinkType* linkType = PDC::LinkTypeFactory::Create("Prismatic","my-id");
    linkType->SetRole(PDC::LinkType::LINK);
    linkType->SetTwist(0.5);
    linkType->SetLength(1.5);
    linkType->SetGeometrySource(PDC::GeometrySource("geometry.3ds","obj3d"));
    ((PDC::PrismaticLinkType*)linkType)->SetJointAngle(0.25);
    double matrix[4][4] = { {  1.0,  2.0,  3.0,  4.0 },
                            {  5.0,  6.0,  7.0,  8.0 },
                            {  9.0, 10.0, 11.0, 12.0 },
                            { 13.0, 14.0, 15.0, 16.0 } };
    linkType->SetGeometryPose(matrix);

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
    jsonxx::Array array = linkTypeJson->get<jsonxx::Array>("geometry_pose");
    ASSERT_STREQ("[\n\t1,\n\t2,\n\t3,\n\t4,\n\t5,\n\t6,\n\t7,\n\t8,\n\t9,\n\t10,\n\t11,\n\t12,\n\t13,\n\t14,\n\t15,\n\t16 \n] \n", array.json().c_str());
}

TEST(LinkTypeSerializerTest,serializeRevoluteLinkType)
{
    PDC::LinkType* linkType = PDC::LinkTypeFactory::Create("Revolute","my-id");
    linkType->SetRole(PDC::LinkType::LINK);
    linkType->SetTwist(0.5);
    linkType->SetLength(1.5);
    linkType->SetGeometrySource(PDC::GeometrySource("geometry.3ds","obj3d"));
    ((PDC::RevoluteLinkType*)linkType)->SetOffset(0.25);
    double matrix[4][4] = { {  1.0,  2.0,  3.0,  4.0 },
                            {  5.0,  6.0,  7.0,  8.0 },
                            {  9.0, 10.0, 11.0, 12.0 },
                            { 13.0, 14.0, 15.0, 16.0 } };
    linkType->SetGeometryPose(matrix);

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
    jsonxx::Array array = linkTypeJson->get<jsonxx::Array>("geometry_pose");
    ASSERT_STREQ("[\n\t1,\n\t2,\n\t3,\n\t4,\n\t5,\n\t6,\n\t7,\n\t8,\n\t9,\n\t10,\n\t11,\n\t12,\n\t13,\n\t14,\n\t15,\n\t16 \n] \n", array.json().c_str());
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
    json.append("\"joint_angle\": 0.25, ");
    json.append("\"geometry_pose\" : [  1.0,  2.0,  3.0,  4.0,  ");
    json.append("                       5.0,  6.0,  7.0,  8.0,  ");
    json.append("                       9.0, 10.0, 11.0, 12.0,  ");
    json.append("                      13.0, 14.0, 15.0, 16.0 ] ");
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
    double pose[4][4];
    linkType->GetGeometryPose(&pose);
    ASSERT_DOUBLE_EQ( 1.0, pose[0][0]);
    ASSERT_DOUBLE_EQ( 2.0, pose[0][1]);
    ASSERT_DOUBLE_EQ( 3.0, pose[0][2]);
    ASSERT_DOUBLE_EQ( 4.0, pose[0][3]);
    ASSERT_DOUBLE_EQ( 5.0, pose[1][0]);
    ASSERT_DOUBLE_EQ( 6.0, pose[1][1]);
    ASSERT_DOUBLE_EQ( 7.0, pose[1][2]);
    ASSERT_DOUBLE_EQ( 8.0, pose[1][3]);
    ASSERT_DOUBLE_EQ( 9.0, pose[2][0]);
    ASSERT_DOUBLE_EQ(10.0, pose[2][1]);
    ASSERT_DOUBLE_EQ(11.0, pose[2][2]);
    ASSERT_DOUBLE_EQ(12.0, pose[2][3]);
    ASSERT_DOUBLE_EQ(13.0, pose[3][0]);
    ASSERT_DOUBLE_EQ(14.0, pose[3][1]);
    ASSERT_DOUBLE_EQ(15.0, pose[3][2]);
    ASSERT_DOUBLE_EQ(16.0, pose[3][3]);
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
    json.append("\"offset\": 0.25, ");
    json.append("\"geometry_pose\" : [  1.0,  2.0,  3.0,  4.0,  ");
    json.append("                       5.0,  6.0,  7.0,  8.0,  ");
    json.append("                       9.0, 10.0, 11.0, 12.0,  ");
    json.append("                      13.0, 14.0, 15.0, 16.0 ] ");
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
    double pose[4][4];
    linkType->GetGeometryPose(&pose);
    ASSERT_DOUBLE_EQ( 1.0, pose[0][0]);
    ASSERT_DOUBLE_EQ( 2.0, pose[0][1]);
    ASSERT_DOUBLE_EQ( 3.0, pose[0][2]);
    ASSERT_DOUBLE_EQ( 4.0, pose[0][3]);
    ASSERT_DOUBLE_EQ( 5.0, pose[1][0]);
    ASSERT_DOUBLE_EQ( 6.0, pose[1][1]);
    ASSERT_DOUBLE_EQ( 7.0, pose[1][2]);
    ASSERT_DOUBLE_EQ( 8.0, pose[1][3]);
    ASSERT_DOUBLE_EQ( 9.0, pose[2][0]);
    ASSERT_DOUBLE_EQ(10.0, pose[2][1]);
    ASSERT_DOUBLE_EQ(11.0, pose[2][2]);
    ASSERT_DOUBLE_EQ(12.0, pose[2][3]);
    ASSERT_DOUBLE_EQ(13.0, pose[3][0]);
    ASSERT_DOUBLE_EQ(14.0, pose[3][1]);
    ASSERT_DOUBLE_EQ(15.0, pose[3][2]);
    ASSERT_DOUBLE_EQ(16.0, pose[3][3]);
}
