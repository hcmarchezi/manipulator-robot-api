#include <gtest/gtest.h>
#include "jsonxx.h"
#include "Link.h"
#include "internal/linkserializer.h"
#include "linktyperepository.h"

// {
//   "link_type_id":"",
//   "joint_move":999.99,
// }

TEST(LinkSerializerTest,serializeLink)
{
    class FakeLinkType : public PDC::LinkType
    {
    public:
        FakeLinkType(std::string id):LinkType(id) {}
        void CalculateFrame(double jointMove,double (* frame)[4][4]) { }
        std::string GetJointType() { }
    };
    PDC::LinkType* fakeLinkType = new FakeLinkType("fake-link-type");
    PDC::Link* link = new PDC::Link(fakeLinkType);
    link->SetJointMove(0.5);

    jsonxx::Object* linkJson = DMC::Internal::LinkSerializer::Serialize(link);

    ASSERT_STREQ("fake-link-type",linkJson->get<jsonxx::String>("link_type_id").c_str());
    ASSERT_DOUBLE_EQ(0.5,linkJson->get<jsonxx::Number>("joint_move"));

    delete link;
    delete fakeLinkType;
}

TEST(LinkSerializerTest,deserializeLink)
{
    class ConcreteLinkType : public PDC::LinkType
    {
    public:
        ConcreteLinkType(std::string id):LinkType(id) { }
        void CalculateFrame(double variableparam,double (* frame)[4][4]) { }
        std::string GetJointType() { return "concrete"; }
    };

    std::string json = "{ \"link_type_id\":\"fake-link-type\", \"joint_move\": 0.5 }";
    jsonxx::Object linkJson;
    linkJson.parse(json);

    PDC::LinkTypeRepository::Add(new ConcreteLinkType("fake-link-type"));

    PDC::Link* link = DMC::Internal::LinkSerializer::Deserialize(&linkJson);

    ASSERT_STREQ("fake-link-type", link->GetLinkType()->GetId().c_str());
    ASSERT_DOUBLE_EQ(0.5, link->GetJointMove());

    PDC::LinkType* linkType = link->GetLinkType();
    delete link;
    delete linkType;
}

